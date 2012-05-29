//---------------------------------------------------------------------------

#ifndef ParseEngineH
#define ParseEngineH
//---------------------------------------------------------------------------

#include "SPCommon.h"

class	 NormalVar	:	public	IParseVar
{
private:
protected:
	String		OnParse(char *lpData, int Len, int &pos, int key=0);
public:
	NormalVar(String type);
	~NormalVar();

	DWORD		   	GetSize(char * lpData, int Len=0, int pos=0);
};


//==============================================================================

class	ParseEngine	:	public	IParseEngine
{
private:
	IParseVar	*	GetVarByTypeName(String name);
public:
	ParseEngine();
	~ParseEngine();
	String		Parse(String	type, char *lpData, int Len, int &pos, int key=0);
	DWORD		GetSize(String type, char * lpData = NULL, int Len=0, int pos=0);
	int			IsVarExist(String type);


	void		RegisterVar(IParseVar *	parseVar);

	IParseVar	*	GetVarByIndex(int index);
	int				GetVarCount();
};

#endif
