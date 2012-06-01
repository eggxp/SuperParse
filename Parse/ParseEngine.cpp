//---------------------------------------------------------------------------


#pragma hdrstop

#include "ParseEngine.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


NormalVar::NormalVar(String type)
{
	m_Type = type;
}

NormalVar::~NormalVar()
{
}

String		NormalVar::OnParse(char *lpData, int Len, int &pos, int key)
{
	String resultStr;
	if(m_Type == "int")
	{
		int result = (int)ReadDWORD(lpData, pos);
		resultStr = IntToStr(result);
	}
	else	if(m_Type == "DWORD")
	{
		if(GetParseAsHex())
		{
			DWORD	result = ReadDWORD(lpData, pos);
			resultStr = IntToHex((int)result, 8);
		}
		else
		{
			DWORD	result = (DWORD)ReadDWORD(lpData, pos);
			resultStr = IntToStr((__int64)result);
		}
	}
	else	if(m_Type == "short")
	{
		short	result = (short)ReadWORD(lpData, pos);
		resultStr = IntToStr(result);
	}
	else	if(m_Type == "WORD")
	{
		if(GetParseAsHex())
		{
			WORD	result = ReadWORD(lpData, pos);
			resultStr = IntToHex((int)result, 4);
		}
		else
		{
			WORD	result = (WORD)ReadWORD(lpData, pos);
			resultStr = IntToStr(result);
		}
	}
	else	if(m_Type == "char")
	{
		char	result = (char)ReadBYTE(lpData, pos);
		resultStr = result;
	}
	else	if(m_Type == "BYTE")
	{
		if(GetParseAsHex())
		{
			BYTE	result = ReadBYTE(lpData, pos);
			resultStr = IntToHex((int)result, 2);
		}
		else
		{
			BYTE	result = (BYTE)ReadBYTE(lpData, pos);
			resultStr = IntToStr(result);
		}
	}
	else	if(m_Type == "float")
	{
		float result = ReadFloat(lpData, pos);
		resultStr = FloatToStr(result);
	}
	else	if(m_Type == "double")
	{
		double	result = ReadDouble(lpData, pos);
		String date = "";
		try
		{
			date = DateTimeToStr(FloatToDateTime(result));
			resultStr = FormatStr("%s(%s)", FloatToStr(result), date);
		}
		catch(...)
		{
			resultStr = FormatStr("%s", FloatToStr(result));
		}
	}
	else	if(m_Type == "DateTime")
	{
		double	result = ReadDouble(lpData, pos);
		String date = DateTimeToStr(FloatToDateTime(result));
		resultStr = FormatStr("%s", date);
	}

	return	resultStr;
}

DWORD		   	NormalVar::GetSize(char * lpData, int Len, int pos)
{
	String resultStr;
	if(m_Type == "int" || m_Type == "DWORD" || m_Type == "float")
	{
		return	4;
	}
	else	if(m_Type == "short" || m_Type == "WORD")
	{
		return	2;
	}
	else	if(m_Type == "BYTE" || m_Type == "char")
	{
		return 1;
	}
	else	if(m_Type == "double")
	{
		return 8;
	}
	return 0;
}

//=============================================================================

ParseEngine::ParseEngine()
{
	//注册默认变量
	NormalVar	*	curVar = new NormalVar("int");
	RegisterVar(curVar);
	curVar = new NormalVar("DWORD");
	RegisterVar(curVar);
	curVar = new NormalVar("short");
	RegisterVar(curVar);
	curVar = new NormalVar("WORD");
	RegisterVar(curVar);
	curVar = new NormalVar("char");
	RegisterVar(curVar);
	curVar = new NormalVar("BYTE");
	RegisterVar(curVar);
	curVar = new NormalVar("float");
	RegisterVar(curVar);
	curVar = new NormalVar("double");
	RegisterVar(curVar);
	curVar = new NormalVar("DateTime");
	RegisterVar(curVar);
}

ParseEngine::~ParseEngine()
{
}

IParseVar	*	ParseEngine::GetVarByTypeName(String name)
{
	for(int i=0; i<m_ParseVars.Count(); i++)
	{
		if(m_ParseVars[i]->GetVarName() == name)
			return	m_ParseVars[i];
	}
	return	NULL;
}

String		ParseEngine::Parse(String	type, char *lpData, int Len, int &pos, int key)
{
	if(pos >= Len)
	{
		pos = Len;
		return	"越界, 无法解析";
	}
	IParseVar	* curVar = GetVarByTypeName(type);
	if(curVar == NULL)
	{
		ErrorOutput("ParseEngine找不到%s变量!", type);
		return	"";
	}
	return	curVar->Parse(lpData, Len, pos, key);
}

int			ParseEngine::IsVarExist(String type)
{
	IParseVar	* curVar = GetVarByTypeName(type);
	if(curVar)
		return	1;
	return	0;
}

void		ParseEngine::RegisterVar(IParseVar *	parseVar)
{
	if(IsVarExist(parseVar->GetVarName()))
	{
		ErrorOutput("%s已存在, ParseEngine变量注册失败!", parseVar->GetVarName());
		return;
	}

	m_ParseVars.Add(parseVar);
}

DWORD			ParseEngine::GetSize(String type, char * lpData, int Len, int pos)
{
	IParseVar	* curVar = GetVarByTypeName(type);
	if(curVar == NULL)
	{
		return 0;
	}
	return	curVar->GetSize(lpData, Len, pos);
}

IParseVar	*	ParseEngine::GetVarByIndex(int index)
{
	return	m_ParseVars[index];
}

int				ParseEngine::GetVarCount()
{
	return	m_ParseVars.Count();
}
