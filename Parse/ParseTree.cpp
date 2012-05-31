//---------------------------------------------------------------------------


#pragma hdrstop

#include "ParseTree.h"
#include "SourceData.h"
#include "CountTime.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

#define		MAX_ARRAY_VAR		5000
static	int				m_iParseState	= 0;
//����״̬:
//0:��ͨ״̬
//1:����̫��,�����ж�
//2:����̫��ȷ��, ��������

ParseTreeNode::ParseTreeNode(IParseEngine	*	engine, IClassMember	*	classMember, IClassManager * classManager)
{
	Clear();
	m_Engine	= engine;
	m_ClassMember = classMember;
	m_ClassManager = classManager;
}

void				ParseTreeNode::Clear()
{
	m_lpData = NULL;
	m_Len = 0;
	m_CurPos = 0;
	m_ParseLen = 0;
	m_ParseResult = "";

	m_ParseTreeNodes.Clear();
	m_Prev = NULL;
	m_Next = NULL;
	m_Parent = NULL;

	m_bParsed = 0;
}

ParseTreeNode::~ParseTreeNode()
{
}

void				ParseTreeNode::SetPrev(ParseTreeNode *prev)
{
	m_Prev = prev;
}

void				ParseTreeNode::SetNext(ParseTreeNode *next)
{
	m_Next = next;
}

void				ParseTreeNode::SetParent(ParseTreeNode *parent)
{
	m_Parent = parent;
}

ParseTreeNode	*	ParseTreeNode::AddChild(IClassMember	*	classMember)
{
	ParseTreeNode	*	curNode = new ParseTreeNode(m_Engine, classMember, m_ClassManager);
	curNode->SetParent(this);
	curNode->SetPrev(m_ParseTreeNodes[m_ParseTreeNodes.Count()-1]);

	m_ParseTreeNodes.Add(curNode);
	return	curNode;
}

void				ParseTreeNode::SetParseData(char *lpData, int Len, int pos)
{
	m_lpData = lpData;
	m_Len = Len;
	m_CurPos = 0;
//	if(m_CurPos != pos || m_CurPos == 0)
	m_bParsed = 0;
		
	m_CurPos = pos;
}

void				ParseTreeNode::ParseCurNode()
{
	if(m_ParseTreeNodes.Count() != 0 && m_ClassMember->GetType() == "char")
	{
		//char �ַ������⴦��
		if(m_CurPos + m_ParseLen <= m_Len)
		{
			m_ParseResult = GetLangText(m_lpData+m_CurPos, m_ParseLen);
		}
		else
		{
			m_ParseResult = "Խ��, �޷�����";
		}
		m_bParsed = 1;
		return;
	}
	
	if(m_Engine->IsVarExist(m_ClassMember->GetType()) == 0)
		return;

	m_bParsed = 1;
	int parsePos = m_CurPos;

	int key=0;
	if(GetUseGlobalKey())
	{
		key = GetKey();
	}
	else
	{
		key = m_Key;
	}
	m_ParseResult = m_Engine->Parse(m_ClassMember->GetType(), m_lpData, m_Len, parsePos, key);
	
}

String				ParseTreeNode::GetParseResult()
{
	return	m_ParseResult;
}
int					ParseTreeNode::GetParseLen()
{
	return	m_ParseLen;
}

ParseTreeNode	*		ParseTreeNode::FindArrayVarPre(String	arrayVar)
{
	ParseTreeNode	* curSearchNode = m_Prev;
	while(curSearchNode != NULL)
	{
		if(curSearchNode->GetClassMember()->GetName() == arrayVar)
			return	curSearchNode;
		curSearchNode = curSearchNode->GetPrev();
	}
	return		NULL;
}

void				ParseTreeNode::BalanceChildTreeCount(int curCount)
{
	while(m_ParseTreeNodes.Count() > curCount)
	{
		m_ParseTreeNodes.Delete(curCount);
	}
	while(m_ParseTreeNodes.Count() < curCount)
	{
	 	AddChild(NULL);
	}
}

void				ParseTreeNode::SetExNodeName()
{
	for(int i=0; i<m_NodesExtData.Count(); i++)
	{
		m_NodesExtData[i]->SetName(FormatStr("%s[%d]", m_ClassMember->GetName(), i)); 
	}
}

void				ParseTreeNode::UnPackData(char *lpData, int Len, int& pos, int Key)
{
	m_lpData = lpData;
	m_Len = Len;
	m_CurPos = pos;
	m_Key = Key;

    if(pos < 0 || pos >= Len)
    {
        m_iParseState = 1;
        return;
    }
	if(m_iParseState == 1)
	{
		//̫��, ��������
		return;
	}
    
	//�⿪��
	//1.����ǲ�������
	if(m_ClassMember->GetArrayVar() != "")
	{
		int arrayVar = m_ClassMember->GetArrayVar().ToIntDef(0);
		if(arrayVar == 0)
		{
			//��̬����
			ParseTreeNode	*	needParseNode = FindArrayVarPre(m_ClassMember->GetArrayVar());
			if(needParseNode == NULL)
			{
				ErrorOutput("��������: %s������", m_ClassMember->GetArrayVar());
				return;
			}
			needParseNode->ParseCurNode();
			arrayVar = needParseNode->GetParseResult().ToIntDef(0);

			if(arrayVar > MAX_ARRAY_VAR)
			{
				int result = Application->MessageBox(FormatStr(L"��̬���鳤�ȴ���%d��, �Ƿ��������?", MAX_ARRAY_VAR).c_str(),L"����ȷ��",MB_OKCANCEL);
				if(result == IDCANCEL)
				{
					m_iParseState = 1;
					return;
				}
				m_iParseState = 2;
			}

			if(arrayVar < 0)
			{
				//��������
				return;
			}
		}

		ClassMember	*	curMember;
		int curPos = pos;

		BalanceChildTreeCount(arrayVar);

		String name;
		for(int i=0; i<arrayVar; i++)
		{
			curMember = new ClassMember();
			name = FormatStr("%s[%d]", m_ClassMember->GetName(), i);
			curMember->Init(m_ClassMember->GetType(), name, m_ClassMember->GetComment(), "");
			m_NodesExtData.Add(curMember);

			m_ParseTreeNodes[i]->SetClassMember(curMember);
			m_ParseTreeNodes[i]->SetParseData(lpData, Len, pos);
			m_ParseTreeNodes[i]->UnPackData(lpData, Len, pos);		//�����ڵ�, չ������
		}

		m_ParseLen = pos - curPos;

		return;
	}


	//2.����Ա�ǲ�����
	IClassData * curClass = m_ClassManager->GetClassByName(m_ClassMember->GetType());
	if(curClass)
	{
		//������е�����
		IClassMember	*	curClassMember;
		int curPos = pos;
		BalanceChildTreeCount(curClass->GetMemberDataCount());
		for(int i=0; i<curClass->GetMemberDataCount(); i++)
		{
			curClassMember = curClass->GetMemberData(i);
			m_ParseTreeNodes[i]->SetClassMember(curClassMember);
			m_ParseTreeNodes[i]->SetParseData(lpData, Len, pos);
			m_ParseTreeNodes[i]->UnPackData(lpData, Len, pos);		//�����ڵ�, չ������
		}
		m_ParseLen = pos - curPos;

		return;
	}

	//��������, Ҳ���ǽṹ��, ��ͨ����
	DWORD size = m_Engine->GetSize(m_ClassMember->GetType(), lpData, Len, pos);
	if(size == 0)
	{
		ErrorOutput("��������: %s ���ͳ���Ϊ0", m_ClassMember->GetType());
		return;
	}
	
	pos += size;
	m_ParseLen = size;
}

bool				ParseTreeNode::IsNeedParse()
{
	if(m_ParseTreeNodes.Count() == 0)
		return true;
	if(m_ClassMember->GetType() == "char" && m_ClassMember->GetArrayVar() != "")
	{
		return true;
	}
	return false;
}

void				ParseTreeNode::Parse()
{
    m_bParsed = 0;
    m_ParseResult = "";
	if(IsNeedParse())
	{
		ParseCurNode();
	}

	for(int i=0; i<m_ParseTreeNodes.Count(); i++)
	{
		m_ParseTreeNodes[i]->Parse();
	}

}

String			   	ParseTreeNode::GetTreeText()
{
	String posHex = IntToHex(m_CurPos, 0);
	if(m_bParsed == 0)
	{
		return	FormatStr("0x%-10s%-20s%-25s", posHex, m_ClassMember->GetType(), m_ClassMember->GetFullName());
	}
	return	FormatStr("0x%-10s%-20s%-25s%s", posHex, m_ClassMember->GetType(), m_ClassMember->GetFullName(),
							m_ParseResult);	
}

//==============================================================================

ParseTree::ParseTree(IParseEngine	*	engine, IClassManager * classManager)
{
	m_Engine	= engine;
	m_ClassManager = classManager;
	m_lpData	= NULL;
	m_CurPos = 0;
	m_bUnpacked = 0;
	m_bParsed = 0;
	m_TreeNodes = NULL;
	m_ClassData = NULL;
	m_Key = 0;
}

ParseTree::~ParseTree()
{
}

void			ParseTree::BindClass(IClassData	*	curClass)
{
	//��, �����
	m_bUnpacked = 0;
	m_bParsed = 0;
	
	m_ParseTreeNodes.Clear();
	m_ClassData = curClass;
	if(m_ClassData != NULL)
	{
		IClassMember	*	curClassMember;
		ParseTreeNode	*	curParseTreeNode;
		for(int i=0; i<curClass->GetMemberDataCount(); i++)
		{
			curClassMember = curClass->GetMemberData(i);
			curParseTreeNode = new ParseTreeNode(m_Engine, curClassMember, m_ClassManager);
			curParseTreeNode->SetPrev(m_ParseTreeNodes[m_ParseTreeNodes.Count()-1]);

			m_ParseTreeNodes.Add(curParseTreeNode);
		}
	}

	SetView();
}

void			ParseTree::SetParseData(char	*	lpData, int Len, int Key)
{
	m_lpData = lpData;
	m_Len = Len;
	m_Key = Key;
}

//չ������, ����ÿ�����ݵĽ���λ��, �����ܳ���
void			ParseTree::UnPackData(int pos, int needRefresh)
{
	m_iParseState = 0;
	if(m_ClassData == NULL)
		return;
//	if(m_CurPos != pos || m_CurPos == 0)
//	{
	m_bUnpacked = 0;
	m_bParsed = 0;
//	}
	m_CurPos = pos;

	if(m_bUnpacked == 0)
	{
		for(int i=0; i<m_ParseTreeNodes.Count(); i++)
		{
			m_ParseTreeNodes[i]->UnPackData(m_lpData, m_Len, pos, m_Key);
		}
	}
	m_bUnpacked = 1;
	if(needRefresh)
		SetView();
}

void			ParseTree::ParseData()
{
	if(m_ClassData == NULL)
		return;


	for(int i=0; i<m_ParseTreeNodes.Count(); i++)
	{
		m_ParseTreeNodes[i]->Parse();
	}

	m_bParsed = 1;
	RefreshViewText();
}

int					ParseTree::GetSize()
{
	int size = 0;
	for(int i=0; i<m_ParseTreeNodes.Count(); i++)
	{
		size += m_ParseTreeNodes[i]->GetParseLen();
	}
	return size;
}

void			ParseTree::BindView(TTreeNodes * curTreeNodes)
{
	m_TreeNodes = curTreeNodes;
}

String				ParseTree::GetStructText()
{
	if(m_ClassData->GetComment() != "")
	{
		return FormatStr("struct%20s%20s%s", m_ClassData->GetName(), "//", m_ClassData->GetComment());
	}
	else
		return FormatStr("struct%20s", m_ClassData->GetName());
}

void				ParseTree::SetView()
{
	if(m_TreeNodes == NULL)
		return;

	if(m_ClassData == NULL)
	{
		m_TreeNodes->Clear();
		return;
	}

	m_TreeNodes->BeginUpdate();
	TTreeNode * StructNode;
	if(m_TreeNodes->Count == 0)
	{
		m_TreeNodes->AddChild(NULL, "");
	}

//	while(m_TreeNodes->Count > 1)
//	{
//		int a = m_TreeNodes->Count;
//		m_TreeNodes->Delete(m_TreeNodes->Item[1]);
//	}
	StructNode = m_TreeNodes->Item[0];

	StructNode->Text = GetStructText();

	StructNode->Data = NULL;		
	//������ͼ�����ݵ���������ͬ
	while(StructNode->Count < m_ClassData->GetMemberDataCount())
	{
		m_TreeNodes->AddChild(StructNode, "");
	}

	while(StructNode->Count > m_ClassData->GetMemberDataCount())
	{
		m_TreeNodes->Delete(StructNode->Item[m_ClassData->GetMemberDataCount()]);
	}

	AddUnVisibleNode(StructNode, NULL, 0);

	m_TreeNodes->EndUpdate();
}

void				ParseTree::RefreshViewText()
{
	if(m_TreeNodes == NULL || m_TreeNodes->Count == 0)
		return;

	m_TreeNodes->BeginUpdate();
	RefreshTreeText(m_TreeNodes->Item[0]);
	m_TreeNodes->EndUpdate();
}

void				ParseTree::RefreshTreeText(TTreeNode * curNode)
{
	ParseTreeNode * curTreeData = (ParseTreeNode *)curNode->Data;
	if(curTreeData)
	{
		curNode->Text = curTreeData->GetTreeText();
	}
	else
		curNode->Text = GetStructText();

	if(curNode->Expanded == false)
		return;
	
	TTreeNode * curChildNode = curNode->getFirstChild();
	while(curChildNode)
	{
		RefreshTreeText(curChildNode);
		curChildNode = curChildNode->getNextSibling();
	}
}

void				ParseTree::AddUnVisibleNode(TTreeNode * parent, ParseTreeNode * parentData, int type)
{
	TTreeNode * curNode = parent->getFirstChild();
	ParseTreeNode	*	curDataNode;
	int traceIndex = 0;
	while(curNode)
	{
		//������ʾ����
		if(type == 0)
		{
			//��Ա����
			curDataNode = m_ParseTreeNodes[traceIndex];
		}
		else
		{
			//�ӳ�Ա����
			curDataNode = parentData->GetChild(traceIndex);
		}
		curNode->Text = curDataNode->GetTreeText();
		curNode->Data = curDataNode;

		//����Ƿ����ӽڵ�, �о����
		if(curNode->Expanded == false)
		{
			if(curDataNode->GetChildCount() != 0)
			{
				//��ʾ��û���ӽڵ�, ���, ��ʾչ����ť
				if(curNode->Count == 0)
					m_TreeNodes->AddChild(curNode, "");
			}
			else
			{
				//��ʾ�����ӽڵ������������û��, ��ʾ�����
				if(curNode->Count != 0)
				{
					curNode->DeleteChildren();
				}
			}
		}
		else
		{
			ViewCurNode(curDataNode, curNode);
		}

		curNode = curNode->getNextSibling();
		traceIndex++;
	}
}

void				ParseTree::ViewCurNode(ParseTreeNode * parseTreeNode, TTreeNode * treeNode)
{
	//1.�������ڵ�������ӽڵ�, ����������ʾ����
	//2.���һ���ӽڵ㻹�к��ӵĻ�, ֻ���һ��, Ŀ������ʾ�Ӻ�

	
	while(treeNode->Count < parseTreeNode->GetChildCount())
	{
		m_TreeNodes->AddChild(treeNode, "");
	}

	while(treeNode->Count > parseTreeNode->GetChildCount())
	{
		m_TreeNodes->Delete(treeNode->Item[parseTreeNode->GetChildCount()]);
	}

	AddUnVisibleNode(treeNode, parseTreeNode, 1);
}

IClassData	*			ParseTree::GetClassData()
{
	return	m_ClassData;
}

IClassManager	*ParseTree::GetClassManager()
{
	return	m_ClassManager;
}
