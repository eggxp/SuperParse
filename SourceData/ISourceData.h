//---------------------------------------------------------------------------

#ifndef ISourceDataH
#define ISourceDataH
//---------------------------------------------------------------------------
#include "SPCommon.h"

class	IClassMember
{
public:
	IClassMember(){}
	virtual	~IClassMember(){}
	virtual		String	GetType() = 0;
	virtual		String	GetName() = 0;
	virtual		String	GetComment() = 0;
	virtual		String	GetArrayVar() = 0;
	virtual		String	GetFullName();
};

class	IClassData
{
protected:
	
public:
	IClassData(){}
	virtual	~IClassData(){}
	virtual		String				GetName() = 0;
	virtual		String				GetComment() = 0;
	virtual		int					GetMemberDataCount() = 0;
	virtual		IClassMember	*   GetMemberData(int index) = 0;
};

class	IClassManager
{
protected:
	AList<IClassData>			m_Classes;
public:
	IClassManager(){}
	virtual	~IClassManager(){}
	virtual	IClassData		*			GetClassByName(String name) = 0;
	virtual	IClassData		*			GetClassByIndex(int index) = 0;
	virtual	int							GetClassCount() = 0;
};

#endif
