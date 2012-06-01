//---------------------------------------------------------------------------

#ifndef SPCommonH
#define SPCommonH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <ComCtrls.hpp>
#include <StrUtils.hpp>
#include <IniFiles.hpp>
#include "AList.h"
#include "CommFunc.h"
#include "IParseEngine.h"

#define     SETUP_INI_FILE      GetAppPath() + "LocalConfig.ini"


void		SetAppPath(String appPath);
String		GetAppPath();
String		GetSrcModPath();

void		SetErrorOutPut(TStatusBar * statusBar, TMemo * memo);

void		ErrorOutput(String	error, ...);

int			OpenFileCheck(String fileName);
void		FileExistCheck(String fileName);
String		GetHexAndIntString(int	iValue);

enum		LangModule		{lmGB, lmBIG5, lmUTF8, lmUnicode};
void		SetLangModule(LangModule  langModule);
LangModule	GetLangModule();
String		GetLangText(char *lpData, int len);

String		SPGetCurrentTime();

void				SetParseEngine(IParseEngine	*	parseEngine);
IParseEngine	*	GetParseEngine();

void				SetKey(int Key);
int					GetKey();
void				SetUseGlobalKey(int use);
int					GetUseGlobalKey();

void				SetParseAsHex(int isOK);
int					GetParseAsHex();


TMemIniFile     *       GetConfig();

#endif
