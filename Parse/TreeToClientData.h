//---------------------------------------------------------------------------

#ifndef TreeToClientDataH
#define TreeToClientDataH
//---------------------------------------------------------------------------

#include "ParseTree.h"
#include <DBClient.hpp>
#include "cspin.h"


//���� :
//1:����һ��, �浽�Լ������ݽṹ��
//2:���Լ���������ʾ��DataSet��
//3:DataSet����XML

/////////////////////////////////////////////////////
//��Ԫ��
struct	tagParseItem
{
	int		ColumnIndex;
	String	Result;
};

/////////////////////////////////////////////////////
//һ��
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
//���н�������
class	ParseResultData
{
private:
	AList<ParseLineData> 		m_Lines;
	TStringList				*	m_ColumnNames;
	bool						m_bIsDataLocked;		//��δ�趨����, ���������

	bool						AddLine();
public:
	ParseResultData();
	~ParseResultData();
	void						AddColumn(String name);
	void						PostColumn();		//�ύ�еĸ���, ���ɱ��
	void						Clear();

	tagParseItem	*			At(int line, int column);
	int							GetLineCount(){return	m_Lines.Count();}
	int							GetColumnCount(){return	m_ColumnNames->Count;}
	String						GetColumnAt(int	index){return	m_ColumnNames->Strings[index];}
	int							GetColumnMaxLength(int col);	
};


/////////////////////////////////////////////////////
//�㷨, ������������
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

	int						m_GetType;   	//0: ����� 1:�������
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
