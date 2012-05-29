//---------------------------------------------------------------------------

#ifndef TreeToClientDataH
#define TreeToClientDataH
//---------------------------------------------------------------------------

#include "ParseTree.h"
#include <DBClient.hpp>
#include "cspin.h"


//过程 :
//1:解析一次, 存到自己的数据结构中
//2:把自己的数据显示在DataSet上
//3:DataSet导出XML

/////////////////////////////////////////////////////
//单元格
struct	tagParseItem
{
	int		ColumnIndex;
	String	Result;
};

/////////////////////////////////////////////////////
//一行
class	ParseLineData
{
private:
	int						m_LineIndex;
	AList<tagParseItem>		m_ItemResult;
public:
	ParseLineData(int lineIndex, int columnCount);
	~ParseLineData();
	tagParseItem	*	At(int index){return	m_ItemResult[index];}
	int					GetLineIndex(){return	m_LineIndex;}
};

/////////////////////////////////////////////////////
//所有解析数据
class	ParseResultData
{
private:
	AList<ParseLineData> 		m_Lines;
	TStringList				*	m_ColumnNames;
	bool						m_bIsDataLocked;		//还未设定列数, 表格不能生成

	bool						AddLine();
public:
	ParseResultData();
	~ParseResultData();
	void						AddColumn(String name);
	void						PostColumn();		//提交列的更改, 生成表格
	void						Clear();

	tagParseItem	*			At(int line, int column);
	int							GetLineCount(){return	m_Lines.Count();}
	int							GetColumnCount(){return	m_ColumnNames->Count;}
	String						GetColumnAt(int	index){return	m_ColumnNames->Strings[index];}
	int							GetColumnMaxLength(int col);	
};


/////////////////////////////////////////////////////
//算法, 树导出到数据
class	TreeToClientData
{
private:
	ParseResultData			m_ParseResultData;
	ParseTree		*		m_ParseTree;
	TCSpinEdit *			m_Process;
	int						m_FileSize;
	int						m_Pos;

	int					   	m_CurParseLine;
	int						m_CurParseColumn;

	int						m_GetType;   	//0: 输出列 1:输出数据
	void					StartGetDetail(int pos);
	void					GetCurNodeDetail(ParseTreeNode	*	parseTreeNode);
	void					OutputDetail(ParseTreeNode	*	parseNode);

	String					GetNodeText(ParseTreeNode	*	parseNode);
public:
	TreeToClientData();
	~TreeToClientData();
	void					Init(ParseTree *parseTree, int fileSize, int pos);
	void					SetColumn();
	void					StartParse(int count, TCSpinEdit *process);

	ParseResultData	*		GetParseData(){return	&m_ParseResultData;}
};
#endif
