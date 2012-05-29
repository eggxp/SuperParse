//---------------------------------------------------------------------------

#ifndef TxtToListLoaderH
#define TxtToListLoaderH
//---------------------------------------------------------------------------

#include "SPCommon.h"
#include "ISourceData.h"

//��txt��ȡ���б����

class	TxtToListLoader
{
private:
	TMemoryStream		*		m_OutputStream;
	IClassData			*		m_ModeClass;

	String						m_SplitTable;
	void						LoadLine(String	line);

	bool						IsUnicode(TStringList * inputList);                    	
		
public:
	TxtToListLoader();
	~TxtToListLoader();
	void						LoadTxtFile(String	fileName, String splitTable, IClassData * classData);
	TMemoryStream		*		GetOutPutStream(){return	m_OutputStream;}	
};

#endif
