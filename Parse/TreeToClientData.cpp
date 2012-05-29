//---------------------------------------------------------------------------


#pragma hdrstop

#include "TreeToClientData.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

ParseLineData::ParseLineData(int lineIndex, int columnCount)
{
	m_LineIndex = lineIndex;

	tagParseItem	*	curItem;
	for(int i=0; i<columnCount; i++)
	{
		curItem = new  tagParseItem;
		curItem->ColumnIndex = i;
		m_ItemResult.Add(curItem);
	}
}

ParseLineData::~ParseLineData()
{
}

//============================================================================
///////////////////////////////////////////////////////////////////////////////
ParseResultData::ParseResultData()
{
	m_ColumnNames = new TStringList;
	m_bIsDataLocked = true;
}

ParseResultData::~ParseResultData()
{
	delete	m_ColumnNames;
}

bool					ParseResultData::AddLine()
{
	if(m_bIsDataLocked)
		return	false;


	ParseLineData	*	parseLineData = new ParseLineData(m_Lines.Count(), m_ColumnNames->Count);
	m_Lines.Add(parseLineData);
	return	true;
}

void						ParseResultData::Clear()
{
	m_Lines.Clear();
	m_ColumnNames->Clear();
	m_bIsDataLocked = true;
}

void						ParseResultData::AddColumn(String name)
{
	m_ColumnNames->Add(name);
}

//提交列的更改, 生成表格
void						ParseResultData::PostColumn()
{
	m_bIsDataLocked = false;
}

tagParseItem	*			ParseResultData::At(int line, int column)
{
	//平衡表格
	while(m_Lines.Count() <= line)
	{
		if(AddLine() == false)
			return NULL;
	}

	return	m_Lines[line]->At(column);
}

int							ParseResultData::GetColumnMaxLength(int col)
{
	int maxLength = 0;
	for(int i=0; i<m_Lines.Count(); i++)
	{
		if(At(i, col)->Result.Length() > maxLength)
			maxLength = At(i, col)->Result.Length();
	}
	return	maxLength;
}

//============================================================================
///////////////////////////////////////////////////////////////////////////////

TreeToClientData::TreeToClientData()
{
	m_ParseTree = NULL;
	m_FileSize = 0;
	m_Pos = NULL;
	m_GetType = 0;
	m_Process = NULL;

}

TreeToClientData::~TreeToClientData()
{
}

void			TreeToClientData::Init(ParseTree *parseTree,
								int fileSize, int pos)
{
	m_ParseTree = parseTree;
	m_FileSize = fileSize;
	m_Pos = pos;
	m_Process = NULL;
	m_ParseResultData.Clear();
}

void				TreeToClientData::SetColumn()
{
	m_GetType = 0;
	StartGetDetail(m_Pos);
	m_ParseResultData.PostColumn();
}

void				TreeToClientData::StartParse(int count, TCSpinEdit *process)
{
	m_GetType = 1;

	m_CurParseLine = 0;
	m_CurParseColumn = 0;
	m_Process = process;

	int parsePos = m_Pos;
	while(parsePos < m_FileSize)
	{
		if(count != 0 && m_CurParseLine == count)
			break;
		StartGetDetail(parsePos);
		int parseSize = m_ParseTree->GetSize();
		if(parseSize == 0)
			return;
		parsePos += parseSize;
		m_CurParseLine++;
		m_Process->Value = m_CurParseLine;
		m_CurParseColumn = 0;
		Application->ProcessMessages();
	}
}

void				TreeToClientData::StartGetDetail(int pos)
{
	m_ParseTree->UnPackData(pos, 0);

	if(m_GetType == 1)
	{
		//如果要取得解析数据, 那么需要解析
		m_ParseTree->ParseData();
	}
	for(int i=0; i<m_ParseTree->GetParseTreeNodeCount(); i++)
	{
		GetCurNodeDetail(m_ParseTree->GetParseTreeNode(i));
	}
}

void				TreeToClientData::GetCurNodeDetail(ParseTreeNode	*	parseTreeNode)
{
	IClassManager	*	classManager = m_ParseTree->GetClassManager();
	IClassMember		*	classMember = parseTreeNode->GetClassMember();
	if(classMember->GetArrayVar() == "")
	{
		//不是数组
		IClassData * curClass = classManager->GetClassByName(classMember->GetType());
		if(curClass)
		{
			//是结构体, 展开
			for(int i=0; i<parseTreeNode->GetChildCount(); i++)
			{
				GetCurNodeDetail(parseTreeNode->GetChild(i));
			}
		}
		else
		{
			//普通数据
			OutputDetail(parseTreeNode);
		}
	}
	else
	{
		//数组
		OutputDetail(parseTreeNode);
	}
}

void					TreeToClientData::OutputDetail(ParseTreeNode	*	parseNode)
{
	if(m_GetType == 0)
	{
		//取得头
		String headName = FormatStr("%s_%s", parseNode->GetClassMember()->GetType(),
											parseNode->GetClassMember()->GetName());
		headName = ReplaceStr(headName, "[", "_");
		headName = ReplaceStr(headName, "]", "_");

		m_ParseResultData.AddColumn(headName);
	}
	else
	{
		//取得解析结果
		String result = GetNodeText(parseNode);
		m_ParseResultData.At(m_CurParseLine, m_CurParseColumn)->Result = result;
	}


	m_CurParseColumn++;
}

String					TreeToClientData::GetNodeText(ParseTreeNode	*	parseNode)
{
	String	curResult, result;
	result = parseNode->GetParseResult();
	if(result == "")
	{
		for(int i=0; i<parseNode->GetChildCount(); i++)
		{
			if(i != parseNode->GetChildCount()-1)
			{
				curResult += FormatStr("%s, ", GetNodeText(parseNode->GetChild(i)));
			}
			else
				curResult += GetNodeText(parseNode->GetChild(i));
		}
		result = FormatStr("[ %s ]", curResult);
	}

	return	result;
}
