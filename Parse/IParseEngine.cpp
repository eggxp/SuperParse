//---------------------------------------------------------------------------


#pragma hdrstop

#include "IParseEngine.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

String		IParseVar::Parse(char *lpData, int Len, int &pos, int key)
{
	String result;
	try
	{
		if(pos < Len)
			result = OnParse(lpData, Len, pos, key);
		else
			return	"越界, 无法解析";
	}
	catch(...)
	{
	}

	return	result;
}

bool		IsNormalType(String	type)
{
	if(type == "char" || type == "BYTE" || type == "short" || type == "WORD"
			|| type == "int" || type == "DWORD" || type == "float"
			|| type == "double")
	{                      
		return	true;
	}
	return	false;
}

