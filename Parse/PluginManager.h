//---------------------------------------------------------------------------

#ifndef PluginManagerH
#define PluginManagerH
//---------------------------------------------------------------------------

#include "ParseEngine.h"
#include "PlugInterface.h"

#define		DLL_PATH		"Plugin"
///////////////////////////////////////////////////////////////////////

class	PluginParseVar : public	IParseVar
{
private:
	tagTypeInfo	m_TypeInfo;
	String		OnParse(char *lpData, int Len, int &pos, int key=0);
public:
	PluginParseVar();
	~PluginParseVar();
	void		Init(getTypeInfo	getTypeInfoFunc);
	DWORD			GetSize(char * lpData, int Len, int pos);

	int			GetVersion();
	String		GetDescription();
};

///////////////////////////////////////////////////////////////////////

struct		tagPluginInfo
{
	String				Name;
	PluginParseVar		ParseVar;
};

class	PluginManager
{
private:
	AList<tagPluginInfo>		m_ParseVar;
	ParseEngine 			*	m_ParseEngine;

	void						LoadDllByName(AnsiString dllName);
public:
	PluginManager();
	~PluginManager();
	void		LoadDLL(String path, ParseEngine * curEngine);

	int			GetPluginCount(){return	m_ParseVar.Count();}
	tagPluginInfo	*   GetPlugin(int index){return	m_ParseVar[index];}
};

#endif
