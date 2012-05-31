//---------------------------------------------------------------------------


#pragma hdrstop

#include "SPCommon.h"
#include "KOEItlbm.h"
#include "wylocal.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

static		String		gAppPath;
static		String		gSrcModPath;
static		LangModule	gLangModule;
static		TStatusBar	*gStatusBar = NULL;
static		TMemo	*gMemo = NULL;
static		IParseEngine	*	gParseEngine = NULL;
static		int		   	gKey = 0;
static		int			gUseGlobalKey = 0;
static		int			gParseAsHex = 0;
static      TConfig     m_Config;

TConfig         *       GetConfig()
{
    return  &m_Config;
}

void		SetAppPath(String appPath)
{
	gAppPath = appPath;
	gSrcModPath = gAppPath + "SourceMod\\";
}

String		GetAppPath()
{
	return		gAppPath;
}

String		GetSrcModPath()
{
	return		gSrcModPath;
}


void		SetErrorOutPut(TStatusBar * statusBar, TMemo * memo)
{
	gMemo = memo;
	gStatusBar = statusBar;
}


void		LogError(String info)
{
	if(gStatusBar && gMemo)
	{
		gStatusBar->Panels->Items[0]->Text = info;
		gMemo->Lines->Add(info);
	}
	else
	{
		ShowMessage(info);
	}
}

void		ErrorOutput(String	error, ...)
{
	String  StrInfo;
	va_list vaArgs;
	va_start(vaArgs, error);
	if (error.c_str())
	{
		StrInfo.vprintf(error.c_str(), vaArgs);

		LogError(StrInfo);
	}
	va_end(vaArgs);

}


int			OpenFileCheck(String fileName)
{
	int size = GetFileSize(fileName);
	if(size/1024/1024 > 100)
	{
		int result = Application->MessageBox(L"文件大于100M,是否一定要打开?",L"打开文件",MB_OKCANCEL);
		if(result == IDCANCEL)
		{
			return 0;
		}
	}
	return	1;
}

void		FileExistCheck(String fileName)
{
	if(FileExists(fileName) == false)
	{
		int handle = FileCreate(fileName);
		FileClose(handle);
	}
}

String		GetHexAndIntString(int	iValue)
{
	String hex = IntToHex(iValue, 0);
	return	FormatStr("0x%s(%d)", hex, iValue);
}

void		SetLangModule(LangModule  langModule)
{
	gLangModule = langModule;
}

String		GetLangText(char *lpData, int len)
{
	if(gLangModule == lmGB)
		return String(lpData, len);
	else if(gLangModule == lmBIG5)
	{
		return	Big2GBK(String(lpData, len));
	}
	else if(gLangModule == lmUTF8)
	{
		return	tlbm_UTF8ToAnsi(lpData, len);
	}
	else if(gLangModule == lmUnicode)
	{
		String	desBuffer;
		desBuffer.SetLength(len);                
		int size = UnicodeToUtf8(AnsiString(desBuffer).c_str(), (wchar_t *)lpData, len);
		return	tlbm_UTF8ToAnsi(AnsiString(desBuffer).c_str(), size);
	}

	return String(lpData, len);
}

LangModule	GetLangModule()
{
	return	gLangModule;
}

String		SPGetCurrentTime()
{
	return	FormatStr("%s %s", DateToStr(Date()), TimeToStr(Now())); 
}

void				SetParseEngine(IParseEngine	*	parseEngine)
{
	gParseEngine = parseEngine;
}

IParseEngine	*	GetParseEngine()
{
	return	gParseEngine;
}

void				SetKey(int Key)
{
	gKey = Key;
}

int					GetKey()
{
	return	gKey;
}

void				SetUseGlobalKey(int use)
{
	gUseGlobalKey = use;
}

int					GetUseGlobalKey()
{
	return	gUseGlobalKey;
}

void				SetParseAsHex(int isOK)
{
	gParseAsHex = isOK;
}

int					GetParseAsHex()
{
	return	gParseAsHex;
}
