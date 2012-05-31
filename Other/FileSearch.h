//---------------------------------------------------------------------------

#ifndef FileSearchH
#define FileSearchH
//---------------------------------------------------------------------------
#include "SPCommon.h"
#include "FileMapping.h"
#include "cgauges.h"
#include "SearchTool.h"

class	AllFileSearch
{
private:
	CFileMappingStream	*		m_CurFile;

	AnsiString				m_Data;

	bool				CheckFile();

	TStringList		*			m_Result;
	TCGauge * 					m_Process;
	CSearchEngine				m_SearchEngine;

	void						StartSearch(TStringList * searchDir);
public:
	AllFileSearch();
	~AllFileSearch();

	void		BeginSearch(String path, String fileExt, String	data, bool includeSub, TCGauge * process);
	void		ReSearch(String	data);

	TStringList		*		GetSearchResult(){return	m_Result;}
};

#endif
