//---------------------------------------------------------------------------

#ifndef IParseEngineH
#define IParseEngineH
//---------------------------------------------------------------------------

#include <vcl.h>
#include "AList.h"

//解析结果
struct	tagParseResult
{
	String	Result;
	int		ReadLen;
	tagParseResult()
	{
		ReadLen = 0;
	}

};


//单个解析变量类
class	IParseVar
{
protected:
	String		m_Type;
	virtual	String		OnParse(char *lpData, int Len, int &pos, int key=0) = 0;
public:
	IParseVar(){}
	virtual	~IParseVar(){}

	virtual	String		GetVarName(){return	m_Type;}
	String		Parse(char *lpData, int Len, int &pos, int key=0);
	virtual	DWORD			GetSize(char * lpData = NULL, int Len = 0, int pos=0) = 0;
};

//解析引擎接口
class	IParseEngine
{
protected:
	AList<IParseVar>		m_ParseVars;

public:
	IParseEngine(){}
	virtual	~IParseEngine(){}

	virtual	String		Parse(String	type, char *lpData, int Len, int &pos, int key=0) = 0;
	virtual	int			IsVarExist(String type) = 0;
	virtual	DWORD			GetSize(String type, char * lpData = NULL, int Len=0, int pos=0) = 0;
	virtual	IParseVar	*	GetVarByIndex(int index) = 0;
	virtual	int				GetVarCount() = 0;
};

bool		IsNormalType(String	type);

#endif
