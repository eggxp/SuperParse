//---------------------------------------------------------------------------


#pragma hdrstop

#include "TxtToListLoader.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TxtToListLoader::TxtToListLoader()
{
	m_OutputStream = new 	TMemoryStream;
	m_ModeClass = NULL;
}

TxtToListLoader::~TxtToListLoader()
{
	delete	m_OutputStream;
}

bool		TxtToListLoader::IsUnicode(TStringList * inputList)
{
	
	if(inputList->Strings[0].Length() > 2)
	{
		int pos = 0;
		String read_content = inputList->Strings[0];
		WORD	result = ReadWORD(AnsiString(read_content).c_str(), pos);
		if(result == 0xFFFE)
			return	true;

		if(result == 0xFEFF)
			return true;
	}
	return false;
}

void		TxtToListLoader::LoadTxtFile(String	fileName, String splitTable, IClassData* classData)
{
	m_ModeClass = classData;

	if(m_ModeClass == NULL)
	{
		int result = Application->MessageBox(L"模板类为空, 读取可能不正确, 是否继续读取?",L"读取询问",MB_OKCANCEL);
		if(result == IDCANCEL)
		{
			return;
		}
	}

	m_SplitTable = splitTable;
	auto_ptr<TStringList>	loadStr(new TStringList);

	loadStr->LoadFromFile(fileName);

	if(IsUnicode(loadStr.get()))
	{
		auto_ptr<TWideStringList>	loadWideStr(new TWideStringList);
		loadWideStr->LoadFromFile(fileName);

		loadStr->Clear();
		for(int i=0; i<loadWideStr->Count; i++)
		{
			loadStr->Add(WideCharToString(loadWideStr->Strings[i].c_bstr()));
		}
	}

	m_OutputStream->Clear();

	//第一行是头, 不读
	for(int i=2; i<loadStr->Count; i++)
	{
		LoadLine(loadStr->Strings[i]);		
	}
}

void		TxtToListLoader::LoadLine(String	line)
{              
	auto_ptr<TStringList>	splitList(new	TStringList);
	SplitStr(line, m_SplitTable, splitList.get());

	IClassMember	*	curClassMember;
	for(int i=0; i<splitList->Count; i++)
	{
		if(i >= m_ModeClass->GetMemberDataCount())
		{
			int result = splitList->Strings[i].ToIntDef(0);
			m_OutputStream->Write(&result, sizeof(int));
		}
		else
		{
			curClassMember = m_ModeClass->GetMemberData(i);
			if(curClassMember->GetType() == "char")
			{
				//字符串
				int arraySize = curClassMember->GetArrayVar().ToIntDef(0);
				String	arrayResult;
				arrayResult.SetLength(arraySize);
				memset(arrayResult.c_str(), '\0', arrayResult.Length());
				memcpy(arrayResult.c_str(), splitList->Strings[i].c_str(), min(splitList->Strings[i].Length(), arraySize));

				m_OutputStream->Write(arrayResult.c_str(), arrayResult.Length());
			}
			else
			{
				DWORD size = (DWORD)GetParseEngine()->GetSize(curClassMember->GetType(), NULL, 0, 0);
				if(size == sizeof(DWORD))
				{
					DWORD	DResult = (DWORD)splitList->Strings[i].ToIntDef(0);
					m_OutputStream->Write(&DResult, size);
				}
				else	if(size == sizeof(WORD))
				{
					WORD	WResult = (WORD)splitList->Strings[i].ToIntDef(0);
					m_OutputStream->Write(&WResult, size);
				}
				else	if(size == sizeof(BYTE))
				{
					BYTE	BResult = (BYTE)splitList->Strings[i].ToIntDef(0);
					m_OutputStream->Write(&BResult, size);
				}
				else
				{
					ShowMessage(FormatStr("Error %s", curClassMember->GetType()));
				}
			}
		}
	}
}
