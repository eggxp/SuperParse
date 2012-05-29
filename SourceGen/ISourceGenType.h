//---------------------------------------------------------------------------

#ifndef ISourceGenTypeH
#define ISourceGenTypeH
//---------------------------------------------------------------------------
#include "SPCommon.h"
#include "ISourceData.h"

int			ContainStr(String from, String to);
bool        IsDataSetKeyName(String    name);
bool        IsADOStoreInputName(String name);


/////////////////////////////////////////////

class		ISourceGenType
{
protected:
	String			m_GenType;
public:
	ISourceGenType(){}
	virtual	~ISourceGenType(){}
	virtual String	GetGenType(){return	m_GenType;}
	
	virtual	String	NeedToStringGen(IClassMember * curMember) = 0;
	virtual	String	NormalTypeGen(IClassMember * curMember) = 0;
	virtual	String	ExTypeGen(IClassMember * curMember) = 0;
	virtual	String	ExTypeArrayGen(IClassMember * curMember) = 0;
	virtual	String	NormalArrayGen(IClassMember * curMember) = 0;
	virtual	String	NormalDArrayGen(IClassMember * curMember) = 0;
	virtual	String	DArrayGen(IClassMember * curMember) = 0;
};

//////////////////////////////////////////////////////////////////////////////

class	ReadDataGen	: public ISourceGenType
{
public:
	ReadDataGen();
	~ReadDataGen();
	virtual	String	NeedToStringGen(IClassMember * curMember);
	virtual	String	NormalTypeGen(IClassMember * curMember);
	virtual	String	ExTypeGen(IClassMember * curMember);
	virtual	String	ExTypeArrayGen(IClassMember * curMember);
	virtual	String	NormalArrayGen(IClassMember * curMember);
	virtual	String	NormalDArrayGen(IClassMember * curMember);
	virtual	String	DArrayGen(IClassMember * curMember);
};

class	ClearGen	: public ISourceGenType
{
public:
	ClearGen();
	~ClearGen();
	virtual	String	NeedToStringGen(IClassMember * curMember);
	virtual	String	NormalTypeGen(IClassMember * curMember);
	virtual	String	ExTypeGen(IClassMember * curMember);
	virtual	String	ExTypeArrayGen(IClassMember * curMember);
	virtual	String	NormalArrayGen(IClassMember * curMember);
	virtual	String	NormalDArrayGen(IClassMember * curMember);
	virtual	String	DArrayGen(IClassMember * curMember);
};

class	GetLengthGen	: public ISourceGenType
{
private:
	String			m_CurLength;
public:
	GetLengthGen();
	~GetLengthGen();
	virtual	String	NeedToStringGen(IClassMember * curMember);
	virtual	String	NormalTypeGen(IClassMember * curMember);
	virtual	String	ExTypeGen(IClassMember * curMember);
	virtual	String	ExTypeArrayGen(IClassMember * curMember);
	virtual	String	NormalArrayGen(IClassMember * curMember);
	virtual	String	NormalDArrayGen(IClassMember * curMember);
	virtual	String	DArrayGen(IClassMember * curMember);
};

class	WriteBufferGen	: public ISourceGenType
{
private:
	String			m_Data;
public:
	WriteBufferGen();
	~WriteBufferGen();
	virtual	String	NeedToStringGen(IClassMember * curMember);
	virtual	String	NormalTypeGen(IClassMember * curMember);
	virtual	String	ExTypeGen(IClassMember * curMember);
	virtual	String	ExTypeArrayGen(IClassMember * curMember);
	virtual	String	NormalArrayGen(IClassMember * curMember);
	virtual	String	NormalDArrayGen(IClassMember * curMember);
	virtual	String	DArrayGen(IClassMember * curMember);
};

class	MemberGetFuncGen	: public ISourceGenType
{
public:
	MemberGetFuncGen();
	~MemberGetFuncGen();
	virtual	String	NeedToStringGen(IClassMember * curMember);
	virtual	String	NormalTypeGen(IClassMember * curMember);
	virtual	String	ExTypeGen(IClassMember * curMember);
	virtual	String	ExTypeArrayGen(IClassMember * curMember);
	virtual	String	NormalArrayGen(IClassMember * curMember);
	virtual	String	NormalDArrayGen(IClassMember * curMember);
	virtual	String	DArrayGen(IClassMember * curMember);
};

class	MemberReturnGetFunc	: public ISourceGenType
{
public:
	MemberReturnGetFunc();
	~MemberReturnGetFunc();
	virtual	String	NeedToStringGen(IClassMember * curMember);
	virtual	String	NormalTypeGen(IClassMember * curMember);
	virtual	String	ExTypeGen(IClassMember * curMember);
	virtual	String	ExTypeArrayGen(IClassMember * curMember);
	virtual	String	NormalArrayGen(IClassMember * curMember);
	virtual	String	NormalDArrayGen(IClassMember * curMember);
	virtual	String	DArrayGen(IClassMember * curMember);
};

class	ADOStoreCreateGen	: public ISourceGenType
{
public:
	ADOStoreCreateGen();
	~ADOStoreCreateGen();
	virtual	String	NeedToStringGen(IClassMember * curMember);
	virtual	String	NormalTypeGen(IClassMember * curMember);
	virtual	String	ExTypeGen(IClassMember * curMember);
	virtual	String	ExTypeArrayGen(IClassMember * curMember);
	virtual	String	NormalArrayGen(IClassMember * curMember);
	virtual	String	NormalDArrayGen(IClassMember * curMember);
	virtual	String	DArrayGen(IClassMember * curMember);
};

class	ADOStoreReadGen	: public ISourceGenType
{
public:
	ADOStoreReadGen();
	~ADOStoreReadGen();
	virtual	String	NeedToStringGen(IClassMember * curMember);
	virtual	String	NormalTypeGen(IClassMember * curMember);
	virtual	String	ExTypeGen(IClassMember * curMember);
	virtual	String	ExTypeArrayGen(IClassMember * curMember);
	virtual	String	NormalArrayGen(IClassMember * curMember);
	virtual	String	NormalDArrayGen(IClassMember * curMember);
	virtual	String	DArrayGen(IClassMember * curMember);
};


class	DataSetCreateGen	: public ISourceGenType
{
private:
public:
	DataSetCreateGen();
	~DataSetCreateGen();
	virtual	String	NeedToStringGen(IClassMember * curMember);
	virtual	String	NormalTypeGen(IClassMember * curMember);
	virtual	String	ExTypeGen(IClassMember * curMember);
	virtual	String	ExTypeArrayGen(IClassMember * curMember);
	virtual	String	NormalArrayGen(IClassMember * curMember);
	virtual	String	NormalDArrayGen(IClassMember * curMember);
	virtual	String	DArrayGen(IClassMember * curMember);
};

class	MemberADOProcNameGen	: public ISourceGenType
{
private:
public:
	MemberADOProcNameGen();
	~MemberADOProcNameGen();
	virtual	String	NeedToStringGen(IClassMember * curMember);
	virtual	String	NormalTypeGen(IClassMember * curMember);
	virtual	String	ExTypeGen(IClassMember * curMember);
	virtual	String	ExTypeArrayGen(IClassMember * curMember);
	virtual	String	NormalArrayGen(IClassMember * curMember);
	virtual	String	NormalDArrayGen(IClassMember * curMember);
	virtual	String	DArrayGen(IClassMember * curMember);
};

class	MemberADOProcNoOutputGen	: public ISourceGenType
{
private:
public:
	MemberADOProcNoOutputGen();
	~MemberADOProcNoOutputGen();
	virtual	String	NeedToStringGen(IClassMember * curMember);
	virtual	String	NormalTypeGen(IClassMember * curMember);
	virtual	String	ExTypeGen(IClassMember * curMember);
	virtual	String	ExTypeArrayGen(IClassMember * curMember);
	virtual	String	NormalArrayGen(IClassMember * curMember);
	virtual	String	NormalDArrayGen(IClassMember * curMember);
	virtual	String	DArrayGen(IClassMember * curMember);
};

class		ADOQueryReadFunc : public ISourceGenType
{
public:
	ADOQueryReadFunc();
	virtual	~ADOQueryReadFunc();
    
	virtual	String	NeedToStringGen(IClassMember * curMember);
	virtual	String	NormalTypeGen(IClassMember * curMember);
	virtual	String	ExTypeGen(IClassMember * curMember);
	virtual	String	ExTypeArrayGen(IClassMember * curMember);
	virtual	String	NormalArrayGen(IClassMember * curMember);
	virtual	String	NormalDArrayGen(IClassMember * curMember);
	virtual	String	DArrayGen(IClassMember * curMember);
};

#endif
