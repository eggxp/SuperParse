//---------------------------------------------------------------------------


#pragma hdrstop

#include "PluginManager.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


PluginParseVar::PluginParseVar()
{
}

PluginParseVar::~PluginParseVar()
{
}

void		PluginParseVar::Init(getTypeInfo	getTypeInfoFunc)
{
	if(getTypeInfoFunc)
	{
		getTypeInfoFunc(&m_TypeInfo);
		m_Type = m_TypeInfo.GetVarName();
	}
	
}

String		PluginParseVar::OnParse(char *lpData, int Len, int &pos, int key)
{
	char	buffer[MAX_RESULT_LEN];
	memset(buffer, '\0', MAX_RESULT_LEN);
	if(m_TypeInfo.OnParse(lpData, Len, pos, buffer, key))
	{
		return	GetLangText(buffer, MAX_RESULT_LEN);       
	}
	return	"Ω‚Œˆ ß∞‹";
}

DWORD			PluginParseVar::GetSize(char * lpData, int Len, int pos)
{
	return	m_TypeInfo.GetSize(lpData, Len, pos);
}

int			PluginParseVar::GetVersion()
{
	return	m_TypeInfo.version;
}

String		PluginParseVar::GetDescription()
{
	return	m_TypeInfo.description;
}

//==============================================================================

PluginManager::PluginManager()
{
}

PluginManager::~PluginManager()
{
	for(int i=0; i<m_ParseVar.Count(); i++)
	{
		FreeLibrary(m_ParseVar[i]->Name.c_str());
	}
}

void		PluginManager::LoadDLL(String path, ParseEngine * curEngine)
{
	m_ParseEngine = curEngine;
	String dllPath = path + DLL_PATH;

	auto_ptr<TStringList>	filesList(new TStringList);
	GetFileList(dllPath, "*.dll", filesList.get(), false);

	for(int i=0; i<filesList->Count; i++)
	{
	 	LoadDllByName(filesList->Strings[i]);
	}

}

void						PluginManager::LoadDllByName(String dllName)
{
	HANDLE hDll = LoadLibrary(dllName.c_str());
	getTypeInfo pfnGet = (getTypeInfo)GetProcAddress(hDll, "exeGetTypeInfo");
	if (pfnGet == NULL)
	{
		ErrorOutput("≤Âº˛%s∂¡»° ß∞‹", dllName);
		return;
	}

	tagPluginInfo	* curPlugin = new tagPluginInfo;
	curPlugin->Name = dllName;
	curPlugin->ParseVar.Init(pfnGet);

	m_ParseVar.Add(curPlugin);
	m_ParseEngine->RegisterVar(&curPlugin->ParseVar);
}
