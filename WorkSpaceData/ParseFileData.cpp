//---------------------------------------------------------------------------


#pragma hdrstop

#include "ParseFileData.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

FileStruct::FileStruct()
{
	m_DataStream = new TMemoryStream;
}

FileStruct::~FileStruct()
{
	delete	m_DataStream;
}

String			FileStruct::GetFullName()
{
	return	FormatStr("%s(%s)", m_FileStructData.describe, m_FileStructData.date);
}

void			FileStruct::CopyStr(char *data, int len, String copyData)
{
	memset(data, '\0', len);
	int minLen = min(len, copyData.Length());
	memcpy(data, copyData.c_str(), minLen);
}

int				FileStruct::ReadData(char *lpData)
{
	m_DataStream->Clear();
	int pos =	m_FileStructData.ReadData(lpData);
	m_DataStream->SetSize(m_FileStructData.dataLen);
	m_DataStream->Write(lpData + pos, m_FileStructData.dataLen);
	pos += m_FileStructData.dataLen;
	return	pos;
}

void			FileStruct::WriteData(TMemoryStream	*	data)
{
	m_FileStructData.dataLen = m_DataStream->Size;
	data->Write(&m_FileStructData, sizeof(m_FileStructData));
	data->Write(m_DataStream->Memory, m_DataStream->Size);
}

void			FileStruct::SetDescribe(String describe)
{
	CopyStr(m_FileStructData.describe, FileDescribeLen, describe);
}

void			FileStruct::SetDateTime(String dateTime)
{
	CopyStr(m_FileStructData.date, FileDateLen, dateTime);
}

void			FileStruct::SetRemark(String remark)
{
	CopyStr(m_FileStructData.remark, FileRemarkLen, remark);
}

void			FileStruct::SetKey(DWORD	key)
{
	m_FileStructData.Key = key;
}

//=============================================================================

FileManager::FileManager()
{
	m_FileListView = NULL;
}

FileManager::~FileManager()
{
	
}

void			FileManager::BindView(TListView * curItems)
{
	m_FileListView = curItems;
	m_FileListView->OwnerData = true;
	m_FileListView->OnData = lvWorkSpaceData;
}

void __fastcall FileManager::lvWorkSpaceData(TObject *Sender, TListItem *Item)
{
	Item->Caption = m_FileStruct[Item->Index]->GetFullName();
}

void			FileManager::Clear()
{
	m_FileStruct.Clear();
	m_FileListView = NULL;
}

void			FileManager::SaveToFile(String fileName)
{
	auto_ptr<TMemoryStream>	saveStream(new TMemoryStream);
	TMemoryStream * curStream;
	DWORD	fileCount = m_FileStruct.Count();
	saveStream->Write(&fileCount, 4);

	for(int i=0; i<m_FileStruct.Count(); i++)
	{
		m_FileStruct[i]->WriteData(saveStream.get());
	}
	saveStream->SaveToFile(fileName);
}

bool			FileManager::LoadFromFile(String fileName)
{
	FileExistCheck(fileName);
	if(OpenFileCheck(fileName) == 0)
		return false;

	auto_ptr<TMemoryStream>	fileStream(new TMemoryStream);
	fileStream->LoadFromFile(fileName);

	char	*	lpData = (char *)fileStream->Memory;
	int pos = 0;
	if(lpData == NULL)
	{
		//无任何数据
		CreateNew();
		return true;
	}
	int	fileCount = ReadDWORD(lpData, pos);

	FileStruct	*	curFile;
	for(int i=0; i<fileCount; i++)
	{
		if(pos >= fileStream->Size)
			break;
		curFile = new FileStruct;
		pos += curFile->ReadData(lpData+pos);
		m_FileStruct.Add(curFile);
	}

	RefreshView();
	return true;
}

void			FileManager::CreateNew()
{
	FileStruct	*	curFile = new FileStruct;
	curFile->SetDateTime(SPGetCurrentTime());
	m_FileStruct.Add(curFile);
	RefreshView();
}

void			FileManager::DeleteVersion(int index)
{
	m_FileStruct.Delete(index);
	RefreshView();
}

void			FileManager::RefreshView()
{
	if(m_FileListView == NULL)
		return;

	ListView_SetItemCountEx(m_FileListView->Handle, m_FileStruct.Count(), LVSICF_NOINVALIDATEALL | LVSICF_NOSCROLL);
	m_FileListView->Refresh();
}

void			FileManager::OutPutClassSource(TStrings	*	outputStr)
{
	outputStr->Clear();
}
