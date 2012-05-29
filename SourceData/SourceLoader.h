//---------------------------------------------------------------------------

#ifndef SourceLoaderH
#define SourceLoaderH
//---------------------------------------------------------------------------
#include "SourceData.h"

//源代码读取器

struct			tagReadStruct
{
	String	Type;
	String  Name;
	String	Comment;
	String	ArrayVar;
	void		Clear()
	{
		Type = "";
		Name = "";
		Comment = "";
		ArrayVar = "";
	}
};

//把伪代码解析成为结构体数据
class	SourceLoader
{
private:
	ClassManager	*		m_ClassManager;
	TStringList		*		m_SourceData;
	
	ClassData 		* 		m_CurParseClass;
	String					m_FileName;
	void					StartParse();
	int						ReadLine(int lineIndex, tagReadStruct &result);
	void					ParseResult(tagReadStruct * result);

public:
	SourceLoader();
	~SourceLoader();
	
	void				   	LoadFromFile(String fileName, ClassManager	*  classManager);
	void					LoadFromStringList(TStrings * strs, ClassManager	*  classManager);
};

#endif
