//---------------------------------------------------------------------------


#pragma hdrstop

#include "ISourceGenType.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


int			ContainStr(String from, String to)
{
	String	fromLowerCase = from.LowerCase();
	String	toLowerCase = to.LowerCase();
   	return	fromLowerCase.AnsiPos(toLowerCase);
}


bool        IsDataSetKeyName(String    name)
{
    if(ContainStr(name, "_KEY_"))
        return  true;
    return false;
}

bool        IsADOStoreInputName(String name)
{
    if(ContainStr(name, "_I_"))
        return  true;
    return false;
}

String      GetADOType(String   type)
{
    if(type == "float" || type == "char")
        return type;
    else
        return "int";
}


/////////////////////////////////////////////////////////////////////

ReadDataGen::ReadDataGen()
{
	m_GenType = "ReadData";
}

ReadDataGen::~ReadDataGen()
{
}

String	ReadDataGen::NeedToStringGen(IClassMember * curMember)
{
    return	FormatStr("%s.SetLength(%s);ReadBuf(_lpData, pos, %s.c_str(), %s);",
							curMember->GetName(), curMember->GetArrayVar(),
							curMember->GetName(), curMember->GetArrayVar());
}

String	ReadDataGen::NormalTypeGen(IClassMember * curMember)
{
	String type = curMember->GetType();
	if(type == "char" || type == "BYTE")
	{
		return	FormatStr("%s = ReadBYTE(_lpData, pos);", curMember->GetName());
	}
	else if(type == "short" || type == "WORD")
	{
		return	FormatStr("%s = ReadWORD(_lpData, pos);", curMember->GetName());
	}
	else if(type == "int" || type == "DWORD")
	{
		return	FormatStr("%s = ReadDWORD(_lpData, pos);", curMember->GetName());
	}
	else if(type == "float")
	{
		return	FormatStr("%s = ReadFloat(_lpData, pos);", curMember->GetName());
	}
	else if(type == "double")
	{
		return	FormatStr("%s = ReadDouble(_lpData, pos);", curMember->GetName());
	}
	return "?";
}

String	ReadDataGen::ExTypeGen(IClassMember * curMember)
{
	return	FormatStr("pos+=%s.ReadData(_lpData+pos, _Len-pos, Key);", curMember->GetName());
}

String	ReadDataGen::ExTypeArrayGen(IClassMember * curMember)
{
	return  FormatStr("for(int i=0; i<%s; i++) pos+=%s[i].ReadData(_lpData+pos, _Len-pos, Key);",
					curMember->GetArrayVar(), curMember->GetName());
}

String	ReadDataGen::NormalArrayGen(IClassMember * curMember)
{
	return	FormatStr("ReadBuf(_lpData, pos, &%s[0], %s * sizeof(%s));",
							curMember->GetName(), curMember->GetArrayVar(),
							curMember->GetType()); 	
}

String	ReadDataGen::NormalDArrayGen(IClassMember * curMember)
{                      
	return	FormatStr("%s.resize(%s);memcpy(&%s[0],_lpData+pos,%s*sizeof(%s));pos+=%s*sizeof(%s);",
						curMember->GetName(), curMember->GetArrayVar(),
						curMember->GetName(), curMember->GetArrayVar(), curMember->GetType(),
                        curMember->GetArrayVar(), curMember->GetType());
}

String	ReadDataGen::DArrayGen(IClassMember * curMember)
{
	return  FormatStr("while(%s.Count()<%s) %s.Add(new %s);for(int i=0; i<%s; i++) pos+=%s[i]->ReadData(_lpData+pos, _Len-pos, Key);",
					curMember->GetName(), curMember->GetArrayVar(),
					curMember->GetName(), curMember->GetType(), 
					curMember->GetArrayVar(), curMember->GetName());
}

///////////////////////////////////////////////////////////////////////

ClearGen::ClearGen()
{
	m_GenType = "Clear";
}

ClearGen::~ClearGen()
{
}

String	ClearGen::NeedToStringGen(IClassMember * curMember)
{
	return	FormatStr("%s = \"\";", curMember->GetName());
}

String	ClearGen::NormalTypeGen(IClassMember * curMember)
{
	return	FormatStr("%s = 0;", curMember->GetName());
}

String	ClearGen::ExTypeGen(IClassMember * curMember)
{
	return	FormatStr("%s.Clear();", curMember->GetName());
}

String	ClearGen::ExTypeArrayGen(IClassMember * curMember)
{
	return  FormatStr("for(int i=0; i<%s; i++) %s[i].Clear();",
					curMember->GetArrayVar(), curMember->GetName());
}

String	ClearGen::NormalArrayGen(IClassMember * curMember)
{
	return	FormatStr("memset(%s, 0, %s * sizeof(%s));",
							curMember->GetName(), curMember->GetArrayVar(),
							curMember->GetType()); 	
}

String	ClearGen::NormalDArrayGen(IClassMember * curMember)
{
	return FormatStr("%s.clear();", curMember->GetName());
}

String	ClearGen::DArrayGen(IClassMember * curMember)
{
	return FormatStr("%s.Clear();", curMember->GetName());
}

///////////////////////////////////////////////////////////////////////

GetLengthGen::GetLengthGen()
{
	m_GenType = "GetLength";
	m_CurLength = "length";
}

GetLengthGen::~GetLengthGen()
{
}

String	GetLengthGen::NeedToStringGen(IClassMember * curMember)
{
    int length = curMember->GetArrayVar().ToIntDef(-1);
    if(length == -1)
    {
        //动态
    	return	FormatStr("%s += %s.Length();", m_CurLength, curMember->GetName());
    }
    else
    {
        //静态
        return	FormatStr("%s += %d;", m_CurLength, length);
    }
}

String	GetLengthGen::NormalTypeGen(IClassMember * curMember)
{
	return	FormatStr("%s += sizeof(%s);", m_CurLength, curMember->GetType());
}

String	GetLengthGen::ExTypeGen(IClassMember * curMember)
{
	return	FormatStr("%s += %s.GetLength();", m_CurLength, curMember->GetName());
}

String	GetLengthGen::ExTypeArrayGen(IClassMember * curMember)
{
	return	FormatStr("for(int i=0; i<%s; i++) %s += %s[i].GetLength();",
						curMember->GetArrayVar(), m_CurLength, curMember->GetName());
}

String	GetLengthGen::NormalArrayGen(IClassMember * curMember)
{
	return	FormatStr("%s += sizeof(%s) * %s;", m_CurLength, curMember->GetType(), curMember->GetArrayVar());
}

String	GetLengthGen::NormalDArrayGen(IClassMember * curMember)
{                                                
	return	FormatStr("%s += sizeof(%s) * %s.size();", m_CurLength, curMember->GetType(), curMember->GetName());
}

String	GetLengthGen::DArrayGen(IClassMember * curMember)
{
	return	FormatStr("for(int i=0; i<%s.Count(); i++) %s += %s[i]->GetLength();",
						curMember->GetName(), m_CurLength, curMember->GetName());
}

///////////////////////////////////////////////////////////////////////

WriteBufferGen::WriteBufferGen()
{
	m_GenType = "WriteBuffer";
	m_Data = "data";
}

WriteBufferGen::~WriteBufferGen()
{
}

String	WriteBufferGen::NeedToStringGen(IClassMember * curMember)
{
    int varValue = curMember->GetArrayVar().ToIntDef(0);
    if(varValue == 0)
    	return	FormatStr("WriteBuf(%s.c_str(),pos, %s.c_str(), %s.Length());",
					m_Data, curMember->GetName(), curMember->GetName());
    else
        return	FormatStr("WriteBuf(%s.c_str(),pos, %s.c_str(), %s.Length());pos+=%d-%s.Length();",
					m_Data, curMember->GetName(), curMember->GetName(), varValue, curMember->GetName());
}

String	WriteBufferGen::NormalTypeGen(IClassMember * curMember)
{
	String type = curMember->GetType();
	if(type == "char" || type == "BYTE")
	{
		return	FormatStr("WriteBYTE(%s.c_str(), pos, %s);", m_Data, curMember->GetName()); 
	}
	else if(type == "short" || type == "WORD")
	{
		return	FormatStr("WriteWORD(%s.c_str(), pos, %s);", m_Data, curMember->GetName());
	}
	else if(type == "int" || type == "DWORD")
	{
		return	FormatStr("WriteDWORD(%s.c_str(), pos, %s);", m_Data, curMember->GetName());
	}
	else if(type == "float")
	{                      
		return	FormatStr("WriteFloat(%s.c_str(), pos, %s);", m_Data, curMember->GetName());
	}
	else if(type == "double")
	{                            
		return	FormatStr("WriteDouble(%s.c_str(), pos, %s);", m_Data, curMember->GetName());
	}
	return "?";
}

String	WriteBufferGen::ExTypeGen(IClassMember * curMember)
{

    return	FormatStr("WriteBuf(%s.c_str(),pos, %s.GetBuffer(Key).c_str(), %s.GetLength());",
					m_Data, curMember->GetName(), curMember->GetName());
}

String	WriteBufferGen::ExTypeArrayGen(IClassMember * curMember)
{
	return	FormatStr("for(int i=0; i<%s; i++) WriteBuf(%s.c_str(),pos, %s[i].GetBuffer(Key).c_str(), %s[i].GetLength());",
					curMember->GetArrayVar(), m_Data,
					curMember->GetName(), curMember->GetName());
}

String	WriteBufferGen::NormalArrayGen(IClassMember * curMember)
{
	return	FormatStr("WriteBuf(%s.c_str(),pos, &%s[0], sizeof(%s) * %s);",
					m_Data, curMember->GetName(), curMember->GetType(), curMember->GetArrayVar()); 
}

String	WriteBufferGen::NormalDArrayGen(IClassMember * curMember)
{
	return	FormatStr("WriteBuf(%s.c_str(),pos, &%s[0], sizeof(%s) * %s.size());",
					m_Data, curMember->GetName(), curMember->GetType(), curMember->GetName());
}

String	WriteBufferGen::DArrayGen(IClassMember * curMember)
{
	return	FormatStr("for(int i=0; i<%s.Count(); i++) WriteBuf(%s.c_str(),pos, %s[i]->GetBuffer().c_str(), %s[i]->GetLength());",
					curMember->GetName(), m_Data,
					curMember->GetName(), curMember->GetName());
}

///////////////////////////////////////////////////////////////////////
MemberGetFuncGen::MemberGetFuncGen()
{
	m_GenType = "GetFunc";
}

MemberGetFuncGen::~MemberGetFuncGen()
{
}
                        
String	MemberGetFuncGen::NeedToStringGen(IClassMember * curMember)
{
	return	FormatStr("String\t\tGet%s()", curMember->GetName());	
}

String	MemberGetFuncGen::NormalTypeGen(IClassMember * curMember)
{
	return	FormatStr("%s\t\tGet%s()", curMember->GetType(), curMember->GetName());
}

String	MemberGetFuncGen::ExTypeGen(IClassMember * curMember)
{
	return	FormatStr("%s*\t\tGet%s()", curMember->GetType(), curMember->GetName());
}

String	MemberGetFuncGen::ExTypeArrayGen(IClassMember * curMember)
{
	return	FormatStr("%s*\t\tGet%s(int index)", curMember->GetType(), curMember->GetName());
}

String	MemberGetFuncGen::NormalArrayGen(IClassMember * curMember)
{
	return	FormatStr("%s\t\tGet%s(int index)", curMember->GetType(), curMember->GetName());
}

String	MemberGetFuncGen::NormalDArrayGen(IClassMember * curMember)
{
	return	FormatStr("%s\t\tGet%s(int index)", curMember->GetType(), curMember->GetName());
}

String	MemberGetFuncGen::DArrayGen(IClassMember * curMember)
{
	return	FormatStr("%s*\t\tGet%s(int index)", curMember->GetType(), curMember->GetName());
}

///////////////////////////////////////////////////////////////////////

MemberReturnGetFunc::MemberReturnGetFunc()
{
	m_GenType = "GetReturnFunc";
}

MemberReturnGetFunc::~MemberReturnGetFunc()
{
}

String	MemberReturnGetFunc::NeedToStringGen(IClassMember * curMember)
{
	return	FormatStr("return		m_Detail->%s;", curMember->GetName());
}

String	MemberReturnGetFunc::NormalTypeGen(IClassMember * curMember)
{
	return	FormatStr("return		m_Detail->%s;", curMember->GetName());
}

String	MemberReturnGetFunc::ExTypeGen(IClassMember * curMember)
{
	return	FormatStr("return		&m_Detail->%s;", curMember->GetName());
}

String	MemberReturnGetFunc::ExTypeArrayGen(IClassMember * curMember)
{
	return	FormatStr("if(index>=0 && index<%s)return &m_Detail->%s[index];else return NULL;",
						curMember->GetArrayVar(), curMember->GetName());
}

String	MemberReturnGetFunc::NormalArrayGen(IClassMember * curMember)
{
	return	FormatStr("if(index>=0 && index<%s)return m_Detail->%s[index];else return 0;",
						curMember->GetArrayVar(), curMember->GetName());
}

String	MemberReturnGetFunc::NormalDArrayGen(IClassMember * curMember)
{
	return	FormatStr("if(index>=0 && index<(int)%s.size())return m_Detail->%s[index];else return 0;",
						curMember->GetName(), curMember->GetName());
}

String	MemberReturnGetFunc::DArrayGen(IClassMember * curMember)
{
	return	FormatStr("if(index>=0 && index<%s.Count())return &m_Detail->%s[index];else return NULL;",
						curMember->GetName(), curMember->GetName());
}

//--------------------------------------------------------------


ADOStoreCreateGen::ADOStoreCreateGen()
{
	m_GenType = "ADOStoreCreate";
}

ADOStoreCreateGen::~ADOStoreCreateGen()
{
}

String	ADOStoreCreateGen::NeedToStringGen(IClassMember * curMember)
{
	String	head = FormatStr("StoredProc->Parameters->CreateParameter(\"@%s\"", curMember->GetName());
	if(IsADOStoreInputName(curMember->GetName()))
	{
		//输入
		return	FormatStr("%s, ftString, pdInput, %d, %s);", head,
					curMember->GetArrayVar().ToIntDef(0),
					curMember->GetName());
	}
	else
	{
		//输出
		return	FormatStr("if(bNeedOutput)%s, ftString, pdOutput, %d, \"\");else{%s, ftString, pdInput, %d, %s);}", head,
					curMember->GetArrayVar().ToIntDef(0),head,
					curMember->GetArrayVar().ToIntDef(0),
					curMember->GetName()
					);
	}
}

String	ADOStoreCreateGen::NormalTypeGen(IClassMember * curMember)
{
	String	head = FormatStr("StoredProc->Parameters->CreateParameter(\"@%s\"", curMember->GetName());

	String	type = "ftInteger";
    String  changeType = "int";

	if(curMember->GetType() == "double")
	{
		type = "ftDateTime";
        changeType = "double";
	}

	if(IsADOStoreInputName(curMember->GetName()))
	{
		//输入
		return	FormatStr("%s, %s, pdInput, sizeof(int), (%s)%s);",
                    head, type, changeType, curMember->GetName());
	}
	else
	{
		//输出
		return	FormatStr("if(bNeedOutput)%s, %s, pdOutput, sizeof(int), %d);else{%s, %s, pdInput, sizeof(int), (%s)%s);}",
                        head, type, -1,
                        head, type, changeType, curMember->GetName());
	}
}

String	ADOStoreCreateGen::ExTypeGen(IClassMember * curMember)
{
	return	FormatStr("%s.ADOStoreCreate(StoredProc);", curMember->GetName());
}

String	ADOStoreCreateGen::ExTypeArrayGen(IClassMember * curMember)
{
	return	"";
}

String	ADOStoreCreateGen::NormalArrayGen(IClassMember * curMember)
{
	return	"";
}

String	ADOStoreCreateGen::NormalDArrayGen(IClassMember * curMember)
{
	return	"";
}

String	ADOStoreCreateGen::DArrayGen(IClassMember * curMember)
{
	return	"";
}

//--------------------------------------------------------------
ADOStoreReadGen::ADOStoreReadGen()
{
	m_GenType = "ADOStoreRead";
}

ADOStoreReadGen::~ADOStoreReadGen()
{
}

String	ADOStoreReadGen::NeedToStringGen(IClassMember * curMember)
{
	if(IsADOStoreInputName(curMember->GetName()))
	{
		//输入
		return	"";
	}
	else
	{
		//输出
        int arrayLength = curMember->GetArrayVar().ToIntDef(-1);
        if(arrayLength == -1)
        {
            return	FormatStr("%s = StoredProc->Parameters->ParamByName(\"@%s\")->Value;",
                        curMember->GetName(), curMember->GetName());
        }
        else
            return	FormatStr("buffer = StoredProc->Parameters->ParamByName(\"@%s\")->Value;buffer=buffer.Trim();memcpy(%s, buffer.c_str(), buffer.Length());",
                        curMember->GetName(), curMember->GetName());
	}
}

String	ADOStoreReadGen::NormalTypeGen(IClassMember * curMember)
{
	if(IsADOStoreInputName(curMember->GetName()))
	{
		//输入
		return	"";
	}
	else
	{
		//输出
		return	FormatStr("%s = (%s)StoredProc->Parameters->ParamByName(\"@%s\")->Value;",
					curMember->GetName(),
					curMember->GetType(), curMember->GetName());
	}
}

String	ADOStoreReadGen::ExTypeGen(IClassMember * curMember)
{
		//输出
	return	FormatStr("%s.ADOStoreRead(StoredProc);",	curMember->GetName());
}

String	ADOStoreReadGen::ExTypeArrayGen(IClassMember * curMember)
{
	return	"";
}

String	ADOStoreReadGen::NormalArrayGen(IClassMember * curMember)
{
	return	"";
}

String	ADOStoreReadGen::NormalDArrayGen(IClassMember * curMember)
{
	return	"";
}

String	ADOStoreReadGen::DArrayGen(IClassMember * curMember)
{
	return	"";
}

////////////////////////////////////////////////////////////////////

DataSetCreateGen::DataSetCreateGen()
{
    m_GenType = "DataSetCreate";
}

DataSetCreateGen::~DataSetCreateGen()
{
}

String	DataSetCreateGen::NeedToStringGen(IClassMember * curMember)
{
    return  FormatStr("[%s] [char] (%s) COLLATE Chinese_PRC_CI_AS NOT NULL ,",
                        curMember->GetName(),
                        curMember->GetArrayVar());
}

String	DataSetCreateGen::NormalTypeGen(IClassMember * curMember)
{
    String  type = GetADOType(curMember->GetType());

    return  FormatStr("[%s] [%s] NOT NULL ,",
                        curMember->GetName(),
                        type);
}

String	DataSetCreateGen::ExTypeGen(IClassMember * curMember)
{
    return  "";
}

String	DataSetCreateGen::ExTypeArrayGen(IClassMember * curMember)
{
    return  "";
}

String	DataSetCreateGen::NormalArrayGen(IClassMember * curMember)
{
    return  "";
}

String	DataSetCreateGen::NormalDArrayGen(IClassMember * curMember)
{
    return  "";
}

String	DataSetCreateGen::DArrayGen(IClassMember * curMember)
{
    return  "";
}

/////////////////////////////////////////////////////////////////
MemberADOProcNameGen::MemberADOProcNameGen()
{
    m_GenType = "MemberADOProcName";
}

MemberADOProcNameGen::~MemberADOProcNameGen()
{
}

String	MemberADOProcNameGen::NeedToStringGen(IClassMember * curMember)
{
    if(IsADOStoreInputName(curMember->GetName()))
    {
        return      FormatStr("@%s char(%s), ",
                            curMember->GetName(),
                            curMember->GetArrayVar());
    }
    else
    {
        return      FormatStr("@%s char(%s) OUTPUT, ",
                            curMember->GetName(),
                            curMember->GetArrayVar());
    }
}

String	MemberADOProcNameGen::NormalTypeGen(IClassMember * curMember)
{
    String  type = GetADOType(curMember->GetType());
    if(IsADOStoreInputName(curMember->GetName()))
    {
        return  FormatStr("@%s %s, ",
                        curMember->GetName(),
                        type);
    }
    else
    {
        return  FormatStr("@%s %s OUTPUT, ",
                        curMember->GetName(),
                        type);
    }
}

String	MemberADOProcNameGen::ExTypeGen(IClassMember * curMember)
{
    return  "";
}

String	MemberADOProcNameGen::ExTypeArrayGen(IClassMember * curMember)
{
    return  "";
}

String	MemberADOProcNameGen::NormalArrayGen(IClassMember * curMember)
{
    return  "";
}

String	MemberADOProcNameGen::NormalDArrayGen(IClassMember * curMember)
{
    return  "";
}

String	MemberADOProcNameGen::DArrayGen(IClassMember * curMember)
{
    return  "";
}

/////////////////////////////////////////////////////////////////
MemberADOProcNoOutputGen::MemberADOProcNoOutputGen()
{
    m_GenType = "MemberADOProcNoOutput";
}

MemberADOProcNoOutputGen::~MemberADOProcNoOutputGen()
{
}

String	MemberADOProcNoOutputGen::NeedToStringGen(IClassMember * curMember)
{
    if(IsADOStoreInputName(curMember->GetName()))
    {
        return      FormatStr("@%s char(%s), ",
                            curMember->GetName(),
                            curMember->GetArrayVar());
    }
    else
    {
        return      FormatStr("@%s char(%s), ",
                            curMember->GetName(),
                            curMember->GetArrayVar());
    }
}

String	MemberADOProcNoOutputGen::NormalTypeGen(IClassMember * curMember)
{
    String  type = GetADOType(curMember->GetType());
    if(IsADOStoreInputName(curMember->GetName()))
    {
        return  FormatStr("@%s %s, ",
                        curMember->GetName(),
                        type);
    }
    else
    {
        return  FormatStr("@%s %s, ",
                        curMember->GetName(),
                        type);
    }
}

String	MemberADOProcNoOutputGen::ExTypeGen(IClassMember * curMember)
{
    return  "";
}

String	MemberADOProcNoOutputGen::ExTypeArrayGen(IClassMember * curMember)
{
    return  "";
}

String	MemberADOProcNoOutputGen::NormalArrayGen(IClassMember * curMember)
{
    return  "";
}

String	MemberADOProcNoOutputGen::NormalDArrayGen(IClassMember * curMember)
{
    return  "";
}

String	MemberADOProcNoOutputGen::DArrayGen(IClassMember * curMember)
{
    return  "";
}

//////////////////////////////////////
ADOQueryReadFunc::ADOQueryReadFunc()
{
    m_GenType = "ADOQueryReadFunc";
}

ADOQueryReadFunc::~ADOQueryReadFunc()
{
}

String	ADOQueryReadFunc::NeedToStringGen(IClassMember * curMember)
{
    int arrayLength = curMember->GetArrayVar().ToIntDef(-1);
    if(arrayLength == -1)
    {
        return	FormatStr("%s = ADOQuery->FieldByName(\"%s\")->AsString.Trim();",
                    curMember->GetName(), curMember->GetName());
    }
    else
        return	FormatStr("buffer = ADOQuery->FieldByName(\"%s\")->AsString.Trim();memcpy(%s, buffer.c_str(), buffer.Length());",
                    curMember->GetName(), curMember->GetName());
}

String	ADOQueryReadFunc::NormalTypeGen(IClassMember * curMember)
{
    return	FormatStr("%s = ADOQuery->FieldByName(\"%s\")->AsInteger;",
					curMember->GetName(), curMember->GetName());
}

String	ADOQueryReadFunc::ExTypeGen(IClassMember * curMember)
{
    return  "";
}

String	ADOQueryReadFunc::ExTypeArrayGen(IClassMember * curMember)
{
    return  "";
}

String	ADOQueryReadFunc::NormalArrayGen(IClassMember * curMember)
{
    return  "";
}

String	ADOQueryReadFunc::NormalDArrayGen(IClassMember * curMember)
{
    return  "";
}

String	ADOQueryReadFunc::DArrayGen(IClassMember * curMember)
{
    return  "";
}
