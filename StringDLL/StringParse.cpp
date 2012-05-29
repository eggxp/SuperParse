//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#include "PlugInterface.h"
#include "CommFunc.h"
#include <algorithm>
using namespace std;

#pragma hdrstop

#pragma argsused


int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
	return 1;
}
//---------------------------------------------------------------------------


char* 	GetVarName()
{
	return	"BString";
}

int 	GetSize(char *lpData, int Len, int pos)
{
	if(lpData && pos < Len)
    {
		return 	(BYTE)lpData[pos] + 1;
    }
	return 0;
}

bool	OnParse(char *lpData, int Len, int &pos, char * result, DWORD	userData)
{
	if(pos >= Len)
		return false;

	int oldPos = pos;		
	int length = ReadBYTE(lpData, pos);
	if(pos+length > Len)
	{
		pos = oldPos;
		return false;
	}

	int minLen = min(MAX_RESULT_LEN, length);
	memcpy(result, lpData+pos, minLen);
	pos += length;		
	return	true;
}




VCIN_API VOID WINAPI exeGetTypeInfo(tagTypeInfo *typeInfo)
{
	typeInfo->version = 1;
	char descript[] = "BYTE_String类型, 第一个BYTE为长度, 后面为内容";
	memcpy(typeInfo->description, descript, sizeof(descript));
	typeInfo->GetSize = GetSize;
	typeInfo->GetVarName = GetVarName;
	typeInfo->OnParse = OnParse;
}
