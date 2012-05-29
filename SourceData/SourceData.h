//---------------------------------------------------------------------------

#ifndef SourceDataH
#define SourceDataH
//---------------------------------------------------------------------------
#include "ISourceData.h"

//类数据定义

class	ClassMember : public IClassMember
{
private:
	String		m_Type;
	String		m_Name;
	String		m_Comment;
	String		m_ArrayVar;
	
public:
	ClassMember(){}
	~ClassMember(){}
	virtual		String	GetType(){return	m_Type;}
	virtual		String	GetName(){return	m_Name;}
	virtual		String	GetComment(){return	m_Comment;}
	virtual		String	GetArrayVar(){return	m_ArrayVar;}
	void				SetName(String name){m_Name = name;}
    void                SetComment(String comment){m_Comment = comment;}
	void		Init(String	type, String name, String comment, String arrayVar);
};

class	ClassData : public IClassData
{
private:
	AList<ClassMember>		m_ClassMember;
	String						m_Name;
	String						m_Comment;
public:
	ClassData(){}
	~ClassData(){}
	virtual		String				GetName(){return	m_Name;}
	virtual		String				GetComment(){return	m_Comment;}
	virtual		int					GetMemberDataCount(){return	m_ClassMember.Count();}
	virtual		IClassMember	*   GetMemberData(int index){return	m_ClassMember[index];}

	ClassMember	*   				GetMemberByIndex(int index){return	m_ClassMember[index];}
	ClassMember	*		AddMember();
	void				DeleteMember(int index);
	void				DeleteMember(IClassMember * curMember);
	void				SetName(String name){m_Name = name;}
    void                SetComment(String comment){m_Comment = comment;}
	void		        Init(String name, String comment);
};

class	ClassManager : public IClassManager
{
private:
	AList<ClassData>			m_Classes;
public:
	ClassManager(){}
	~ClassManager(){}
	virtual	IClassData		*			GetClassByName(String name);
	virtual	IClassData		*			GetClassByIndex(int index){return	m_Classes[index];}
	virtual	int							GetClassCount(){return	m_Classes.Count();}
	void				Clear();
	ClassData	*		AddClass();
	ClassData		*	GetClassDataByIndex(int index){return	m_Classes[index];}
	void				DeleteClass(int index){m_Classes.Delete(index);}
    int                 GetClassIndexByClassData(ClassData * curClass);
};
#endif
