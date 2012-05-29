//---------------------------------------------------------------------------


#pragma hdrstop

#include "SourceGen.h"
#include "IParseEngine.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

String          GetStoreProcByClassName(String name)
{
    return  "proc_" + name;
};



const	String		gClassRep = "#ClassRep#";
const	String		gClassRepEnd = "#ClassRepEnd#";
const	String		gMemberRep = "#MemberRep#";
const	String		gMemberRepEnd = "#MemberRepEnd#";
const	String		gClassComment = "<%ClassComment%>";
const	String		gClassName = "<%ClassName%>";
const	String		gMemberType = "<%MemberType%>";
const	String		gMemberName = "<%MemberName%>";
const	String		gMemberRealName = "<%MemberRealName%>";
const	String		gMemberComment = "<%MemberComment%>";
const	String		gFileComment = "<%FileComment%>";
const	String		gSetHeadStr = "<%SetHeadStr%>";
const	String		gCommentTag = "//";

const	String		gMemberReadDataType = "<%MemberReadDataType%>";
const	String		gMemberReadDataName = "<%MemberReadDataName%>";
const	String		gMemberReadDataFunc = "<%MemberReadDataFunc%>";
const	String		gMemberClearFunc = "<%MemberClearFunc%>";
const	String		gMemberDataSetCreateName = "<%MemberDataSetCreateName%>";
const	String		gMemberKeyName = "<%MemberKeyName%>";

const	String		gADOStoreCreateFunc = "<%ADOStoreCreateFunc%>";
const	String		gADOStoreReadFunc = "<%ADOStoreReadFunc%>";

const	String		gDynamicClass = "#DynamicClass#";
const	String		gDynamicClassElse = "#DynamicClassElse#";
const	String		gDynamicClassEnd = "#DynamicClassEnd#";

const	String		gMemberGetLengthFunc = "<%MemberGetLengthFunc%>";
const	String		gMemberWriteBufferFunc = "<%MemberWriteBufferFunc%>";

const	String		gMemberGetFunc = "<%MemberGetFunc%>";
const	String		gMemberReturnGetFunc = "<%MemberReturnGetFunc%>";
const	String		gSmallClassName = "<%SmallClassName%>";

const	String		gMemberADOProcName = "<%MemberADOProcName%>";
const	String		gStoreProcName = "<%StoreProcName%>";
                             
const	String		gADOStoreSqlSelectName = "<%ADOStoreSqlSelectName%>";
const	String		gADOStoreSqlWhereName = "<%ADOStoreSqlWhereName%>";
const	String		gDot = "<%,%>";
const	String		gMemberADOProcNoOutput = "<%MemberADOProcNoOutput%>";

const   String      gADOQueryReadFunc = "<%ADOQueryReadFunc%>";



const  	int		LINE_RESULT_ERROR		=	0;
const  	int		LINE_RESULT_NORMAL		=	1;
const  	int		LINE_RESULT_CLASSEND	=	-1;
const  	int		LINE_RESULT_MEMBEREND	=	-2;
const	int		LINE_RESULT_IFEND		=	-3;



SourceGen::SourceGen()
{
	m_SrcFileStr = new TStringList;

	//生成类型
	ReadDataGen * 	curReadDataGen = new ReadDataGen;
	m_SourceGenType.Add(curReadDataGen);
	ClearGen * 		curClearGen = new ClearGen;
	m_SourceGenType.Add(curClearGen);
	GetLengthGen * 	curGetLengthGen = new GetLengthGen;
	m_SourceGenType.Add(curGetLengthGen);
	WriteBufferGen *curWriteBufferGen = new WriteBufferGen;
	m_SourceGenType.Add(curWriteBufferGen);
	MemberGetFuncGen * curMemberGetFuncGen = new MemberGetFuncGen;
	m_SourceGenType.Add(curMemberGetFuncGen);
	MemberReturnGetFunc * curMemberReturnGetFunc = new MemberReturnGetFunc;
	m_SourceGenType.Add(curMemberReturnGetFunc);

	ADOStoreCreateGen *  curMemberADOStoreCreateFunc = new ADOStoreCreateGen;
	m_SourceGenType.Add(curMemberADOStoreCreateFunc);

	ADOStoreReadGen * curMemberADOStoreReadFunc = new ADOStoreReadGen;
	m_SourceGenType.Add(curMemberADOStoreReadFunc);

    DataSetCreateGen * curDataSetCreateGen = new DataSetCreateGen;
    m_SourceGenType.Add(curDataSetCreateGen);

    MemberADOProcNameGen * memberADOProcNameGen = new MemberADOProcNameGen;
    m_SourceGenType.Add(memberADOProcNameGen);

    MemberADOProcNoOutputGen * memberADOProcNoOutputGen = new MemberADOProcNoOutputGen;
    m_SourceGenType.Add(memberADOProcNoOutputGen);

    ADOQueryReadFunc        *   aDOQueryReadFunc = new ADOQueryReadFunc;
    m_SourceGenType.Add(aDOQueryReadFunc);

	Clear();
}

ISourceGenType	*	SourceGen::GetSourceGenType(String type)
{
	for(int i=0; i<m_SourceGenType.Count(); i++)
	{
		if(m_SourceGenType[i]->GetGenType() == type)
			return	m_SourceGenType[i];
	}
	return NULL;
}

void		SourceGen::Clear()
{
	m_ClassManager = NULL;
	m_OutputStr = NULL;
	m_CurParseClass = NULL;
	m_CurClassMember = NULL;
    m_CurWorkSpace = NULL;
	m_bEnterIfDynamicClass = 0;
}

int				SourceGen::IsClassDynamic(IClassData * curClass)
{
	String arrayVar;
	for(int i=0; i<curClass->GetMemberDataCount(); i++)
	{
		if(IsMemberDynamic(curClass->GetMemberData(i)))
			return	1;

		//新增, BString 算动态的长度
        if(GetParseEngine()->GetSize(curClass->GetMemberData(i)->GetType(), NULL) == 0)
			return 1;
	}
	return 0;
}

SourceGen::~SourceGen()
{
	delete	m_SrcFileStr;
}

void			SourceGen::GenSource(WorkSpace	*workSpace, String srcFileName, IClassManager	*	curClass, TStrings	*	outputStr)
{
	Clear();
    m_CurWorkSpace = workSpace;
	outputStr->Clear();
	if(curClass == NULL || curClass->GetClassCount() == 0)
		return;
	outputStr->BeginUpdate();

	m_ClassManager = curClass;
	m_OutputStr = outputStr;
	m_SrcFileName = srcFileName;

	m_SrcFileStr->LoadFromFile(srcFileName);
	m_OutputStr->Clear();

	int curReadModalNum = 0;
	int	result = 0;
	int readLength;
	while(curReadModalNum < m_SrcFileStr->Count)
	{
		readLength = 0;
		result = ReadModal(curReadModalNum, readLength);
		curReadModalNum += readLength;
		if(result == LINE_RESULT_ERROR)
			break;
	}
	outputStr->EndUpdate();
}

String				SourceGen::GetCommentStr(String comment)
{
	if(comment == "")
		return "";
	else
		return gCommentTag + comment;
}

String				SourceGen::GetCommentStr(IClassMember * classMember)
{
	String comment = classMember->GetComment();
	if(IsMemberDynamic(classMember))
	{
		comment = FormatStr("size = %s", classMember->GetArrayVar());
	}

	return	GetCommentStr(comment);
}


int					SourceGen::ReadModal(int lineNum, int & readLength)
{
	String line = m_SrcFileStr->Strings[lineNum];
	readLength = 1;
	if(ContainStr(line, gClassRep))
	{
		//类的开始
		if(m_CurParseClass != NULL)
		{
			ErrorOutput("%s文件%d行:%s类循环定义错误!", m_SrcFileName, lineNum, m_CurParseClass->GetName());
			return LINE_RESULT_ERROR;
		}

		int readResult;
		for(int i=0; i<m_ClassManager->GetClassCount(); i++)
		{                                     
			m_CurParseClass = m_ClassManager->GetClassByIndex(i);
			readLength = 0;
			readResult = ReadClass(lineNum+1, readLength);
			if(readResult == LINE_RESULT_ERROR)
				return LINE_RESULT_ERROR;
		}

		return	LINE_RESULT_NORMAL;
	}
	else	if(ContainStr(line, gClassRepEnd))
	{
		//类的结束
		m_CurParseClass = NULL;
		return	LINE_RESULT_CLASSEND;
	}
	else	if(ContainStr(line, gMemberRep))
	{
		//变量的开始
		if(m_CurParseClass == NULL)
			m_CurParseClass = m_ClassManager->GetClassByIndex(0);

		if(m_CurParseClass == NULL)
		{
			return LINE_RESULT_ERROR;
		}
		if(m_CurClassMember)
		{
			ErrorOutput("%s文件%d行:%s变量循环定义错误", m_SrcFileName, lineNum, m_CurClassMember->GetName());
			return LINE_RESULT_ERROR;
		}

		int readResult;
		for(int i=0; i<m_CurParseClass->GetMemberDataCount(); i++)
		{
			if(m_SrcFileName == gDataInterfaceSrc)
			{
				if(m_CurParseClass->GetMemberData(i)->GetName().LowerCase().AnsiPos("unknown"))
				{
					//特殊处理, 输出数据接口的时候, 有Unknown的不输出
					continue;
				}
			}
			m_CurClassMember = m_CurParseClass->GetMemberData(i);
			readLength = 0;
			readResult = ReadMember(lineNum+1, readLength);
			if(readResult == LINE_RESULT_ERROR)
				return LINE_RESULT_ERROR;
		}

		return	LINE_RESULT_NORMAL;
	}
	else	if(ContainStr(line, gMemberRepEnd))
	{
		//变量的结束
		m_CurClassMember = NULL;
		return	LINE_RESULT_MEMBEREND;
	}
	else	if(ContainStr(line, gDynamicClass))
	{
		m_bEnterIfDynamicClass = 1;
		return	LINE_RESULT_NORMAL;
	}
	else	if(ContainStr(line, gDynamicClassElse))
	{
		m_bEnterIfDynamicClass = 2;
		return	LINE_RESULT_NORMAL;
	}
	else	if(ContainStr(line, gDynamicClassEnd))
	{
		m_bEnterIfDynamicClass = 0;
		return	LINE_RESULT_IFEND;
	}
	else
	{
        if(ContainStr(line, gFileComment))
        {
            line = ReplaceStr(line, gFileComment, GetCommentStr(m_CurWorkSpace->GetComment()));
        }
        
		if(m_CurParseClass == NULL)
		{
			m_OutputStr->Add(line);
			return LINE_RESULT_NORMAL;
		}
		int doNotReadLine = 0;
		int isDynamicNode = IsClassDynamic(m_CurParseClass);
		if(m_bEnterIfDynamicClass == 1 && isDynamicNode == 0)
		{
			//动态字段
			doNotReadLine = 1;
		}
		else	if(m_bEnterIfDynamicClass == 2 && isDynamicNode == 1)
		{
			//非动态字段
			doNotReadLine = 1;
		}
		if(doNotReadLine)
			return	LINE_RESULT_NORMAL;

        

		if(m_CurParseClass)
		{
			if(ContainStr(line, gClassComment))
			{
				line = ReplaceStr(line, gClassComment, GetCommentStr(m_CurParseClass->GetComment()));
			}

			if(ContainStr(line, gClassName))
			{
				line = ReplaceStr(line, gClassName, m_CurParseClass->GetName());
			}

			if(ContainStr(line, gSmallClassName))
			{
				line = ReplaceStr(line, gSmallClassName, GetSmallClassName(m_CurParseClass->GetName()));
			}

            if(ContainStr(line, gSetHeadStr))
            {
                line = ReplaceStr(line, gSetHeadStr, GetSetHeadFunc());
            }

            if(ContainStr(line, gMemberKeyName))
            {
                String keyName;
                for(int i=0; i<m_CurParseClass->GetMemberDataCount(); i++)
                {
                    if(IsDataSetKeyName(m_CurParseClass->GetMemberData(i)->GetName()))
                    {
                        keyName = m_CurParseClass->GetMemberData(i)->GetName();
                        break;
                    }
                }
                line = ReplaceStr(line, gMemberKeyName, keyName);
            }

            if(ContainStr(line, gStoreProcName))
            {
                line = ReplaceStr(line, gStoreProcName, GetStoreProcByClassName(m_CurParseClass->GetName()));
            }
            if(ContainStr(line, gADOStoreSqlSelectName))
            {
                line = ReplaceStr(line, gADOStoreSqlSelectName, GetADOStoreSqlSelectName());
            }
            if(ContainStr(line, gADOStoreSqlWhereName))
            {
                line = ReplaceStr(line, gADOStoreSqlWhereName, GetADOStoreSqlWhereName());
            }
		}

		if(m_CurClassMember)
		{
			if(ContainStr(line, gMemberType))
			{
				line = ReplaceStr(line, gMemberType, m_CurClassMember->GetType());
			}

			if(ContainStr(line, gMemberName))
			{
				line = ReplaceStr(line, gMemberName, m_CurClassMember->GetFullName());
			}
            
            if(ContainStr(line, gMemberRealName))
			{
				line = ReplaceStr(line, gMemberRealName, m_CurClassMember->GetName());
			}

			if(ContainStr(line, gMemberComment))
			{
				line = ReplaceStr(line, gMemberComment, GetCommentStr(m_CurClassMember));
			}

			if(ContainStr(line, gMemberReadDataType))
			{
				tagNodeType type;
				GetReadDataType(m_CurClassMember, type);
				line = ReplaceStr(line, gMemberReadDataType, type.Type);
				line = ReplaceStr(line, gMemberReadDataName, type.Name);
			}

			if(ContainStr(line, gMemberReadDataFunc))
			{
				line = ReplaceStr(line, gMemberReadDataFunc, GetGenFunc(m_CurClassMember, "ReadData"));
			}

			if(ContainStr(line, gMemberClearFunc))
			{
				line = ReplaceStr(line, gMemberClearFunc, GetGenFunc(m_CurClassMember, "Clear"));
			}

			if(ContainStr(line, gMemberGetLengthFunc))
			{
				line = ReplaceStr(line, gMemberGetLengthFunc, GetGenFunc(m_CurClassMember, "GetLength"));
			}

			if(ContainStr(line, gMemberWriteBufferFunc))
			{
				line = ReplaceStr(line, gMemberWriteBufferFunc, GetGenFunc(m_CurClassMember, "WriteBuffer"));
			}

			if(ContainStr(line, gMemberGetFunc))
			{
				line = ReplaceStr(line, gMemberGetFunc, GetGenFunc(m_CurClassMember, "GetFunc"));
			}

			if(ContainStr(line, gMemberReturnGetFunc))
			{
				line = ReplaceStr(line, gMemberReturnGetFunc, GetGenFunc(m_CurClassMember, "GetReturnFunc"));
			}

			if(ContainStr(line, gADOStoreCreateFunc))
			{
				line = ReplaceStr(line, gADOStoreCreateFunc, GetGenFunc(m_CurClassMember, "ADOStoreCreate"));
			}

			if(ContainStr(line, gADOStoreReadFunc))
			{
				line = ReplaceStr(line, gADOStoreReadFunc, GetGenFunc(m_CurClassMember, "ADOStoreRead"));
			}

            if(ContainStr(line, gMemberDataSetCreateName))
			{
				line = ReplaceStr(line, gMemberDataSetCreateName, GetGenFunc(m_CurClassMember, "DataSetCreate"));
			}

            if(ContainStr(line, gMemberADOProcName))
			{
				line = ReplaceStr(line, gMemberADOProcName, GetGenFunc(m_CurClassMember, "MemberADOProcName"));
			}

            if(ContainStr(line, gDot))
			{
				line = ReplaceStr(line, gDot, GetDot());
			}

            if(ContainStr(line, gMemberADOProcNoOutput))
			{
				line = ReplaceStr(line, gMemberADOProcNoOutput, GetGenFunc(m_CurClassMember, "MemberADOProcNoOutput"));
			}

            if(ContainStr(line, gADOQueryReadFunc))
			{
				line = ReplaceStr(line, gADOQueryReadFunc, GetGenFunc(m_CurClassMember, "ADOQueryReadFunc"));
			}
		}


		line = line.TrimRight();
		m_OutputStr->Add(line);
		return	LINE_RESULT_NORMAL;
	}
}

int				SourceGen::IsMemberDynamic(IClassMember *curClassMember)
{
	String	arrayVar = curClassMember->GetArrayVar();
	if(arrayVar != "" && arrayVar.ToIntDef(-1) == -1)
		return	1;
	if(arrayVar.ToIntDef(-1) == -1 && curClassMember->GetType() == "char")
		return	1;

	return	0;
}

bool			SourceGen::GetReadDataType(IClassMember *curClassMember, tagNodeType& nodeType)
{
	//特殊处理
	if(IsNeedToString(curClassMember))
	{
        if(curClassMember->GetType() == "char" && curClassMember->GetArrayVar().ToIntDef(-1) == -1)
        {
    		nodeType.Type = "String";
            nodeType.Name = curClassMember->GetName();
        }
        else
        {
            nodeType.Type = "char";
            nodeType.Name = curClassMember->GetFullName();
        }

		return	1;
	}

	//普通处理
	if(IsMemberDynamic(curClassMember))
	{
		if(IsNormalType(curClassMember->GetType()))
		{
			nodeType.Type = FormatStr("vector<%s>", curClassMember->GetType());
			nodeType.Name = curClassMember->GetName();
		}
		else
		{
			nodeType.Type = FormatStr("AList<%s>", curClassMember->GetType());
			nodeType.Name = curClassMember->GetName();
		}
	}
	else
	{
		nodeType.Type = curClassMember->GetType();
		nodeType.Name = curClassMember->GetFullName();
	}
	return 1;
}

int				SourceGen::ReadSec(int lineNum, int & readLength, int endResultType)
{
	int	result = 0;
	readLength = 0;

	while(lineNum < m_SrcFileStr->Count)
	{
		int classReadLength = 0;
		result = ReadModal(lineNum, classReadLength);
		lineNum += classReadLength;
		readLength += classReadLength;

		if(result == LINE_RESULT_ERROR)
			return	LINE_RESULT_ERROR;
		if(result == endResultType)
		{
			break;
		}
	}
	return	LINE_RESULT_NORMAL;
}

int					SourceGen::ReadClass(int lineNum, int & readLength)
{
	//读取一个类
	return	ReadSec(lineNum, readLength, LINE_RESULT_CLASSEND);
}

int					SourceGen::ReadMember(int lineNum, int & readLength)
{
	//读取一个变量
	return	ReadSec(lineNum, readLength, LINE_RESULT_MEMBEREND);
}

bool			SourceGen::IsNeedToString(IClassMember * curMember)
{
//	if(IsMemberDynamic(curMember)&& curMember->GetType() == "char")
//		return	true;
	if(curMember->GetArrayVar() != "" && curMember->GetType() == "char")
		return	true;
	return false;
}

String				SourceGen::GetGenFunc(IClassMember * curMember, String genType)
{
	ISourceGenType	*	curGen = GetSourceGenType(genType);
	if(curGen == NULL)
	{
		return FormatStr("%s解析类型未知", genType);
	}
	//特殊处理
	if(IsNeedToString(curMember))
	{
		return	curGen->NeedToStringGen(curMember);	
	}
	//普通处理
	String result, readCount;
	if(IsMemberDynamic(curMember))
	{
		if(IsNormalType(curMember->GetType()))
		{
			//动态, 普通类型
			return	curGen->NormalDArrayGen(curMember);
		}
		//动态, 下面读取
	}
	else
	{
		String type = curMember->GetType();
		if(curMember->GetArrayVar() == "")
		{
			if(IsNormalType(curMember->GetType()))
			{
				return curGen->NormalTypeGen(curMember);
			}
			else
			{
				//不是普通的变量
				return curGen->ExTypeGen(curMember);
			}
		}
		else
		{
			//数组
			if(IsNormalType(curMember->GetType()))
			{
				return curGen->NormalArrayGen(curMember);
			}
			else
			{
				//普通数组, 非普通变量
				return curGen->ExTypeArrayGen(curMember);
			}
		}
	}
	return	curGen->DArrayGen(curMember);
}

String			SourceGen::GetSmallClassName(String className)
{
	if(className.AnsiPos("tag") == 1)
	{
		className = className.Delete(1, 3);
	}
	return className;
}

String          SourceGen::GetSetHeadFunc()
{
    IClassMember    *   curMember = m_CurParseClass->GetMemberData(0);
    String  fileCommand = m_CurWorkSpace->GetComment();
    String  Head = fileCommand.SubString(1, 2); //02 01
    String  SubHead = fileCommand.SubString(4, 2);

    Head = "0x" + Head;
    SubHead = "0x" + SubHead;
    
    if(curMember->GetType() != "tagHead")
        return "";

    return  FormatStr("%s.Cmd = %s; %s.SubCmd = %s;",
                        curMember->GetName(), Head,
                        curMember->GetName(), SubHead);
}

String          SourceGen::GetADOStoreSqlSelectName()
{
    String  selectName, whereName;
    IClassMember * curClassMember;

    for(int i=0; i<m_CurParseClass->GetMemberDataCount(); i++)
    {
        curClassMember = m_CurParseClass->GetMemberData(i);
        if(IsADOStoreInputName(curClassMember->GetName()) == false)
        {
            selectName += FormatStr("@%s=%s,",
                                    curClassMember->GetName(),
                                    curClassMember->GetName());
        }
    }

    whereName  = GetADOStoreSqlWhereName();

    return  FormatStr("SELECT %s@ADOResult = 1 FROM %s WHERE %s",
                        selectName,
                        m_CurParseClass->GetName(),
                        whereName);
}


String          SourceGen::GetADOStoreSqlWhereName()
{
    if(m_CurParseClass == NULL)
        return "";
    String  whereName;
    IClassMember * curClassMember; 

    for(int i=0; i<m_CurParseClass->GetMemberDataCount(); i++)
    {
        curClassMember = m_CurParseClass->GetMemberData(i);
        if(IsADOStoreInputName(curClassMember->GetName()))
        {
            whereName += FormatStr("%s=@%s AND ",
                                    curClassMember->GetName(),
                                    curClassMember->GetName());
        }
    }

    whereName  = whereName.Delete(whereName.Length()-4, 5);
    return  whereName;
}

String          SourceGen::GetDot()
{
    if( m_CurParseClass->GetMemberData(m_CurParseClass->GetMemberDataCount()-1) == m_CurClassMember)
        return "";
    else
        return ",";
}
