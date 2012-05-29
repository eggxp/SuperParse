//---------------------------------------------------------------------------
#ifndef PlugInterfaceH
#define PlugInterfaceH
//---------------------------------------------------------------------------

#define	MAX_RESULT_LEN				500

#ifdef EXPORT_API
	#define VCIN_API extern "C" __declspec(dllexport)
#else
	#define VCIN_API __declspec(dllimport)
#endif
//---------------------------------------------------------------------------
#include <windows.h>
//---------------------------------------------------------------------------
struct	tagTypeInfo
{
	int version;				// module type (IN_VER)
	char description[MAX_RESULT_LEN];			// description of module, with version string

	bool	(*OnParse)(char *lpData, int Len, int &pos, char * result, DWORD	userData);
	char 	*(*GetVarName)();
	DWORD 	(*GetSize)(char *lpData, int Len, int pos);
	tagTypeInfo()
	{
		version = 0;
		memset(description, '\0', MAX_RESULT_LEN);
	}
};

VCIN_API VOID WINAPI exeGetTypeInfo(tagTypeInfo *typeInfo);
typedef VOID WINAPI (*getTypeInfo)(tagTypeInfo *typeInfo);


#endif
