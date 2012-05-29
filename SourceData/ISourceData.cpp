//---------------------------------------------------------------------------


#pragma hdrstop

#include "ISourceData.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

String			IClassMember::GetFullName()
{
	if(GetArrayVar() == "")
		return	GetName();
	return	FormatStr("%s[%s]", GetName(), GetArrayVar());
}
