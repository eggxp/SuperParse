//---------------------------------------------------------------------------


#pragma hdrstop

#include "SourceData.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//===========================================================================
void		ClassMember::Init(String	type, String name, String comment, String arrayVar)
{
	m_Type = type;
	m_Name = name;
	m_Comment = comment;
	m_ArrayVar = arrayVar;
}

//===========================================================================
void		ClassData::Init(String name, String comment)
{
	m_Name = name;
	m_Comment = comment;
}

ClassMember	*	  	ClassData::AddMember()
{
	ClassMember	*	curMember = new ClassMember;
	m_ClassMember.Add(curMember);
	return	curMember;
}

void				ClassData::DeleteMember(int index)
{
	m_ClassMember.Delete(index);
}

void				ClassData::DeleteMember(IClassMember * curMember)
{
	IClassMember	* member;
	for(int i=0; i<m_ClassMember.Count(); i++)
	{
		member = (IClassMember *)m_ClassMember[i];
		if(member == curMember)
		{
			DeleteMember(i);
		}
	}
}

//===========================================================================
ClassData		*		ClassManager::AddClass()
{
	ClassData	*	curClass = new ClassData;
	m_Classes.Add(curClass);
	return	curClass;
}

IClassData		*			ClassManager::GetClassByName(String name)
{
	for(int i=0; i<m_Classes.Count(); i++)
	{
		if(m_Classes[i]->GetName() == name)
			return	m_Classes[i];
	}
	return NULL;
}

void				ClassManager::Clear()
{
	m_Classes.Clear();
}

int                 ClassManager::GetClassIndexByClassData(ClassData * curClass)
{
    for(int i=0; i<m_Classes.Count(); i++)
	{
		if(m_Classes[i] == curClass)
			return	i;
	}
	return -1;
}
