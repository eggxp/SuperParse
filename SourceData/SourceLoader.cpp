//---------------------------------------------------------------------------


#pragma hdrstop

#include "SourceLoader.h"
#include "SPCommon.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

SourceLoader::SourceLoader()
{
	m_ClassManager = NULL;
	m_CurParseClass = NULL;
    m_SourceData = new TStringList;
}

SourceLoader::~SourceLoader()
{
	delete	m_SourceData;
}

void				   	SourceLoader::LoadFromFile(String fileName, ClassManager	*  classManager)
{
	FileExistCheck(fileName);
	m_SourceData->Clear();
	m_ClassManager = classManager;
	m_SourceData->LoadFromFile(fileName);
	m_FileName = fileName;
	StartParse();
}

void					SourceLoader::LoadFromStringList(TStrings * strs, ClassManager	*  classManager)
{
	m_SourceData->Clear();
	m_ClassManager = classManager;
	m_SourceData->AddStrings(strs);
	StartParse();
}

void					SourceLoader::StartParse()
{
	m_ClassManager->Clear();
	m_CurParseClass = NULL;
	tagReadStruct	result;
	int readLineCount = 0;
	int curReadResult = 0;
	while(readLineCount < m_SourceData->Count)
	{
		result.Clear();
		curReadResult = ReadLine(readLineCount, result);
		if(curReadResult <= 0)
		{
//			ErrorOutput("伪代码文件读取错误(%s)", m_FileName);
			return;
		}

		readLineCount += curReadResult;
		if(result.Name != "")
			ParseResult(&result);
	}
}

int					SourceLoader::ReadLine(int lineIndex, tagReadStruct &result)
{
	if(lineIndex >= m_SourceData->Count)
		return -1;
	String line  = m_SourceData->Strings[lineIndex];

	//分割值和注释
	int	commentStart = line.Pos("//");
	String	values = line;
	String	comment;
	if(commentStart != 0)
	{
		values = line.SubString(1, commentStart-1);
		comment = line.SubString(commentStart, line.Length() - commentStart+1);
	}
	while(comment.Length() && comment.c_str()[0] == '/')
	{
		comment = comment.Delete(1,1);
	}

	if(values.Pos("{") || values.Pos("}") ||
				(comment == "" && values == ""))
	{
		//语法符号
		return 1;
	}

	//1. 删除空格
	values = Strutils::ReplaceStr(values, '\t', ' ');
	while(values.Length() && values.c_str()[0] == ' ')
	{
		values = values.Delete(1, 1);
	}

	while(values.Length())
	{
		int result = 0;
		for(int i=1; i<values.Length()-1; i++)
		{
			if(values.c_str()[i] == ' ' && values.c_str()[i+1] == ' ')
			{
				values = values.Delete(i+1, 1);
				result = 1;
			}
		}
		if(result == 0)
			break;
	}
	//2. 分割
	auto_ptr<TStringList>	parseStr(new TStringList);
	SplitStr(values, ' ', parseStr.get());

	//3. 赋值
	//注释:去掉前面2竖线
	result.Comment = comment;

	if(parseStr->Count>0 && parseStr->Strings[0] != "")
	{
		result.Type = parseStr->Strings[0];
	}
	else
	{
		int readResult = 1;
		readResult += ReadLine(lineIndex+readResult, result);
		return	readResult;
	}

	if(parseStr->Count>1)
	{
		String resultName = Strutils::ReplaceStr(parseStr->Strings[1], ";", "");
		if(resultName.Pos("[") == 0)
			result.Name = resultName;
		else
		{
			//分开名称和数组
			result.Name = LeftString(resultName, "[");
			result.ArrayVar = RightString(resultName, "[");
			result.ArrayVar = LeftString(result.ArrayVar, "]");
		}
	}
	return	1;		
}

void					SourceLoader::ParseResult(tagReadStruct * result)
{
	if(result->Type == "class" || result->Type == "struct")
	{
		m_CurParseClass = m_ClassManager->AddClass();
		m_CurParseClass->Init(result->Name, result->Comment);
	}
	else
	{
		if(m_CurParseClass == NULL)
			return;
		ClassMember * curMember = m_CurParseClass->AddMember();
		curMember->Init(result->Type, result->Name, result->Comment, result->ArrayVar);
	} 
}
