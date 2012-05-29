//---------------------------------------------------------------------------

#ifndef ParseFileDataH
#define ParseFileDataH
//---------------------------------------------------------------------------

#include "SPCommon.h"

const	int	FileDescribeLen = 50;
const	int	FileDateLen = 20;
const	int	FileRemarkLen = 498;

#pragma pack(push, 1)
struct tagFileStruct
{
	char                            describe[FileDescribeLen];
	char                            date[FileDateLen];
	char                            remark[FileRemarkLen];
	DWORD							Key;
	int                             dataLen;
	int                             ReadData(char *Data, int Len = 0)
	{
		int Pos = 0;
		memcpy(this, Data, sizeof(*this));
		Pos += sizeof(*this);
		return Pos;
	}
	void                             Clear()
	{
		memset(this, 0, sizeof(*this));
	}

};
#pragma pack(pop)

class	FileManager;
class	FileStruct
{
friend	FileManager;
private:
	tagFileStruct		m_FileStructData;
	TMemoryStream	*	m_DataStream;

	void			CopyStr(char *data, int len, String copyData);
protected:
	int				ReadData(char *lpData);
	void			WriteData(TMemoryStream	*	data);
public:
	FileStruct();
	~FileStruct();

	String			GetDescribe(){return	m_FileStructData.describe;}
	String			GetDateTime(){return	m_FileStructData.date;}
	String			GetRemark(){return	m_FileStructData.remark;}
	String			GetFullName();
	DWORD			GetKey(){return	m_FileStructData.Key;}
	char	*		GetData(){return	(char *)m_DataStream->Memory;}
	int				GetDataLen(){return	m_FileStructData.dataLen;}
	TMemoryStream	*GetMemory(){return	m_DataStream;}

	void			SetDescribe(String describe);
	void			SetDateTime(String dateTime);
	void			SetRemark(String remark);
	void			SetKey(DWORD	key);
};


class	FileManager
{
private:
	AList<FileStruct>			m_FileStruct;
	TListView					*m_FileListView;

	void __fastcall lvWorkSpaceData(TObject *Sender, TListItem *Item);
public:
	FileManager();
	~FileManager();
	void						Clear();
	void						RefreshView();
	void						BindView(TListView * curItems);
	bool						LoadFromFile(String fileName);
	void						CreateNew();
	void						DeleteVersion(int index);
	void						SaveToFile(String fileName);
	FileStruct		*			GetFileData(int index){return m_FileStruct[index];}
	void						OutPutClassSource(TStrings	*	outputStr);
};


#endif
