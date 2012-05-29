//---------------------------------------------------------------------------

#ifndef ParseTreeH
#define ParseTreeH
//---------------------------------------------------------------------------
#include "IParseEngine.h"
#include "ISourceData.h"

class	ParseTree;
class	ClassMember;

class	ParseTreeNode
{
friend	ParseTree;
private:
	//�ر�����
	IParseEngine	*	m_Engine;
	IClassManager 	* 	m_ClassManager;
	IClassMember	*	m_ClassMember;

	//����������
	char		*		m_lpData;		//��������
	int					m_Len;			//�������ݳ���
	int					m_CurPos;
	int					m_ParseLen;
	String				m_ParseResult;
	int					m_bParsed;		//�Ƿ������
	int					m_Key;

	void				ParseCurNode();

	//������������
	AList<ParseTreeNode>	m_ParseTreeNodes;
	AList<ClassMember>		m_NodesExtData;		//���鴴���ĸ��ӽڵ�, ����, ��������
	ParseTreeNode	*		m_Prev;
	ParseTreeNode	*		m_Next;
	ParseTreeNode	*		m_Parent;

	ParseTreeNode	*		FindArrayVarPre(String	arrayVar);	//[��̬����]��ǰ�ҵ���������
	void					SetParseData(char *lpData, int Len, int pos);

	void					BalanceChildTreeCount(int curCount);
	void					SetClassMember(IClassMember	*	member){m_ClassMember = member;}
	
protected:
	void					SetPrev(ParseTreeNode *prev);
	void					SetNext(ParseTreeNode *next);
	void					SetParent(ParseTreeNode *parent);
	ParseTreeNode	*		AddChild(IClassMember	*	classMember);
public:
	ParseTreeNode(IParseEngine	*	engine, IClassMember	*	classMember, IClassManager * classManager);
	~ParseTreeNode();

	IClassMember	*	GetClassMember(){return		m_ClassMember;}

	//Ҷ�ӽڵ�ʹ��, ��������
	String				GetParseResult();
	int					GetParseLen();
	int					GetCurPos(){return	m_CurPos;}

	void				Clear();
	//���ο���
	int					GetChildCount(){return	m_ParseTreeNodes.Count();}
	ParseTreeNode	*	GetChild(int index){return	m_ParseTreeNodes[index];}
	ParseTreeNode	*	GetPrev(){return	m_Prev;}
	ParseTreeNode	*	GetNext(){return	m_Next;}
	ParseTreeNode	*	GetParent(){return	m_Parent;}

	//��������
	void				UnPackData(char *lpData, int Len, int& pos, int Key=0);
	void				Parse();
	bool				IsNeedParse();

	//�������
	String			   	GetTreeText();
	void				SetExNodeName();
};

/////////////////////////////////////////////////////////////////////////////

class	ParseTree
{
private:
	IParseEngine	*	m_Engine;
	IClassManager	*	m_ClassManager;
	IClassData		*	m_ClassData;
	TTreeNodes 		*	m_TreeNodes;	 

	char			*	m_lpData;
	int					m_Len;
	int					m_CurPos;

	int					m_Key;
	//����
	int					m_bUnpacked;   	//�Ƿ��Ѿ�չ����
	int					m_bParsed;		//�Ƿ��Ѿ�������
	
	//��������
	AList<ParseTreeNode>	m_ParseTreeNodes;

	String				GetStructText();
	void				SetView();
	void				RefreshTreeText(TTreeNode * curNode);
	void				AddUnVisibleNode(TTreeNode * parent, ParseTreeNode * parentData, int type);//0: ��Ϊ�ṹ�� 1:��ͨ

public:
	ParseTree(IParseEngine	*	engine, IClassManager * classManager);
	~ParseTree();

	//��ʼ��
	void			BindClass(IClassData	*	curClass);
	void			SetParseData(char	*	lpData, int Len, int Key=0);

	
	void			UnPackData(int pos, int needRefresh = 0);			//��һ��: չ������, ����ÿ�����ݵĽ���λ��, �����ܳ���
	void			ParseData();			//�ڶ���: ��������
	int				GetSize();
	int				GetCurPos(){return	m_CurPos;}

	//����ͼ
	void			BindView(TTreeNodes * curTreeNodes);
	void			ViewCurNode(ParseTreeNode * parseTreeNode, TTreeNode * treeNode);
	void			RefreshViewText();
	IClassData	*	GetClassData();
	IClassManager	*GetClassManager();

	//��������
	ParseTreeNode	*	GetParseTreeNode(int index){return	m_ParseTreeNodes[index];}
	int					GetParseTreeNodeCount(){return	m_ParseTreeNodes.Count();}	
};



#endif
