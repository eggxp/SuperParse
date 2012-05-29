//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#include "PlugInterface.h"
#include "CommFunc.h"

#pragma hdrstop

#pragma argsused


int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
	return 1;
}
//---------------------------------------------------------------------------

char* 	GetVarName()
{
	return	"tagHead";
}

int 	GetSize(char *lpData, int Len, int pos)
{
	return 2;
}

bool	OnParse(char *lpData, int Len, int &pos, char * result, DWORD	userData)
{
	if(pos + GetSize(NULL, 0, 0)>= Len)
		return false;

	String 	resultStr = BinToStr(lpData+pos, 2);
	pos += GetSize(NULL, 0, 0);
	memcpy(result, resultStr.c_str(), resultStr.Length());
	return	true;
}


VCIN_API VOID WINAPI exeGetTypeInfo(tagTypeInfo *typeInfo)
{
	typeInfo->version = 1;
	char descript[] = "tagHead类型, 2个BYTE表示命令头和子命令";
	memcpy(typeInfo->description, descript, sizeof(descript));
	typeInfo->GetSize = GetSize;
	typeInfo->GetVarName = GetVarName;
	typeInfo->OnParse = OnParse;
}