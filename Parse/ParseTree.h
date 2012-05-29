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
	//必备数据
	IParseEngine	*	m_Engine;
	IClassManager 	* 	m_ClassManager;
	IClassMember	*	m_ClassMember;

	//解析用数据
	char		*		m_lpData;		//完整数据
	int					m_Len;			//完整数据长度
	int					m_CurPos;
	int					m_ParseLen;
	String				m_ParseResult;
	int					m_bParsed;		//是否解析过
	int					m_Key;

	void				ParseCurNode();

	//构建树的数据
	AList<ParseTreeNode>	m_ParseTreeNodes;
	AList<ClassMember>		m_NodesExtData;		//数组创建的附加节点, 无用, 回收垃圾
	ParseTreeNode	*		m_Prev;
	ParseTreeNode	*		m_Next;
	ParseTreeNode	*		m_Parent;

	ParseTreeNode	*		FindArrayVarPre(String	arrayVar);	//[动态数组]向前找到变量内容
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

	//叶子节点使用, 解析数据
	String				GetParseResult();
	int					GetParseLen();
	int					GetCurPos(){return	m_CurPos;}

	void				Clear();
	//树形控制
	int					GetChildCount(){return	m_ParseTreeNodes.Count();}
	ParseTreeNode	*	GetChild(int index){return	m_ParseTreeNodes[index];}
	ParseTreeNode	*	GetPrev(){return	m_Prev;}
	ParseTreeNode	*	GetNext(){return	m_Next;}
	ParseTreeNode	*	GetParent(){return	m_Parent;}

	//解析控制
	void				UnPackData(char *lpData, int Len, int& pos, int Key=0);
	void				Parse();
	bool				IsNeedParse();

	//界面控制
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
	//解析
	int					m_bUnpacked;   	//是否已经展开过
	int					m_bParsed;		//是否已经解析过
	
	//树的数据
	AList<ParseTreeNode>	m_ParseTreeNodes;

	String				GetStructText();
	void				SetView();
	void				RefreshTreeText(TTreeNode * curNode);
	void				AddUnVisibleNode(TTreeNode * parent, ParseTreeNode * parentData, int type);//0: 父为结构体 1:普通

public:
	ParseTree(IParseEngine	*	engine, IClassManager * classManager);
	~ParseTree();

	//初始化
	void			BindClass(IClassData	*	curClass);
	void			SetParseData(char	*	lpData, int Len, int Key=0);

	
	void			UnPackData(int pos, int needRefresh = 0);			//第一步: 展开数据, 分配每个数据的解析位置, 计算总长度
	void			ParseData();			//第二步: 解析数据
	int				GetSize();
	int				GetCurPos(){return	m_CurPos;}

	//树视图
	void			BindView(TTreeNodes * curTreeNodes);
	void			ViewCurNode(ParseTreeNode * parseTreeNode, TTreeNode * treeNode);
	void			RefreshViewText();
	IClassData	*	GetClassData();
	IClassManager	*GetClassManager();

	//导出数据
	ParseTreeNode	*	GetParseTreeNode(int index){return	m_ParseTreeNodes[index];}
	int					GetParseTreeNodeCount(){return	m_ParseTreeNodes.Count();}	
};



#endif
