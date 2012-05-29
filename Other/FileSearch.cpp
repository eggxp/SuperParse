//---------------------------------------------------------------------------


#pragma hdrstop

#include "FileSearch.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

AllFileSearch::AllFileSearch()
{
	m_CurFile = new CFileMappingStream();
	m_Result = new TStringList;
	m_Process = NULL;
}

AllFileSearch::~AllFileSearch()
{
	delete	m_CurFile;
	delete	m_Result;
}

void		AllFileSearch::BeginSearch(String path, String fileExt, String	data, bool includeSub, TCGauge * process)
{
	m_Process = process;
	auto_ptr<TStringList>	filesList(new TStringList);
	GetFileList(path, fileExt, filesList.get(), includeSub);
	m_Data = data;

	StartSearch(filesList.get());
}

void				AllFileSearch::StartSearch(TStringList * searchDir)
{
	m_Result->Clear();
	m_Process->MaxValue = searchDir->Count;
	for(int i=0; i<searchDir->Count; i++)
	{
		m_Process->Progress = i;
        Application->ProcessMessages();
		try
		{
			m_CurFile->Open(searchDir->Strings[i], fmOpenRead);
			if(CheckFile())
			{
				m_Result->Add(searchDir->Strings[i]);
			}
			m_CurFile->Close();
		}
		catch(...)
		{
			continue;
		}
	}
	m_Process->Progress = searchDir->Count;
}

bool				AllFileSearch::CheckFile()
{
	LPVOID  result = m_SearchEngine.NormalSearch(m_CurFile->Memory, m_CurFile->Size, m_Data.c_str());
	if(result == NULL)
		return false;
	return	true;
}

void		AllFileSearch::ReSearch(String	data)
{
	if(m_Result->Count == 0)
		return;

	m_Data = data;
	auto_ptr<TStringList>	filesList(new TStringList);
	filesList->AddStrings(m_Result);

	StartSearch(filesList.get());
}
