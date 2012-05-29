//---------------------------------------------------------------------------
#ifndef AllSourceGenH
#define AllSourceGenH
//---------------------------------------------------------------------------
#include "WorkSpaceManager.h"
#include "PluginManager.h"
#include "SourceGen.h"

class	AllSourceGen
{
private:
	WorkSpaceManager	*	m_WorkSpaceManager;
	PluginManager		*	m_PluginManager;
	SourceGen				m_SourceGen;
	TStringList			*	m_AllClassList;	
public:
	AllSourceGen();
	~AllSourceGen();
	void					SaveSource(WorkSpaceManager	*	workSpaceManager,
										PluginManager	*	pluginManager,
										String		fileName,
										String		sourceMod);
};

#endif
