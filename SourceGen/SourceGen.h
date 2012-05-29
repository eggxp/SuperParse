//---------------------------------------------------------------------------

#ifndef SourceGenH
#define SourceGenH
//---------------------------------------------------------------------------
#include "ISourceData.h"
#include "ISourceGenType.h"
#include "WorkSpaceManager.h"

#define	gBasicSrc 			GetSrcModPath() + "Base.h"
#define	gReadDataSrc 		GetSrcModPath() + "ReadData.h"
#define	gWriteBufferSrc 	GetSrcModPath() + "WriteBuffer.h"
#define	gDataInterfaceSrc 	GetSrcModPath() + "DataInterface.h"
#define	gAllReadWriteSrc 	GetSrcModPath() + "AllReadWrite.h"
#define	gADOStoreSrc 		GetSrcModPath() + "ADOStore.h"
#define gADOCreate          GetSrcModPath() + "ADOCreate.h"
#define gADOStoreLoad       GetSrcModPath() + "ADOStoreLoad.h"
#define gADOStoreSave       GetSrcModPath() + "ADOStoreSave.h"
#define gADOStoreInsert     GetSrcModPath() + "ADOStoreInsert.h"
#define gADOStoreQueryAll   GetSrcModPath() + "ADOStoreQueryAll.h"

struct	tagNodeType
{
	String		Type;
	String		Name;
};

class	SourceGen
{
protected:
	IClassManager	*	m_ClassManager;
	TStrings		*	m_OutputStr;
	TStringList		*	m_SrcFileStr;
	String				m_SrcFileName;
	AList<ISourceGenType>	m_SourceGenType;
	ISourceGenType	*	GetSourceGenType(String type);

	IClassData * 		m_CurParseClass;
	IClassMember	*	m_CurClassMember;

    WorkSpace       *   m_CurWorkSpace;


	int					m_bEnterIfDynamicClass;    //0:未进入  1:动态  2:非动态

	void				Clear();
	String				GetCommentStr(IClassMember * classMember);
	String				GetCommentStr(String comment);

	int				ReadModal(int lineNum, int & readLength);
	int				ReadClass(int lineNum, int & readLength);
	int				ReadMember(int lineNum, int & readLength);

	int				ReadSec(int lineNum, int & readLength, int endResultType);

	int				IsClassDynamic(IClassData * curClass);
	int				IsMemberDynamic(IClassMember *curClassMember);

	bool			GetReadDataType(IClassMember *curClassMember, tagNodeType& nodeType);

	bool			IsNeedToString(IClassMember * curMember);

	String			GetGenFunc(IClassMember * curMember, String genType);

	String			GetSmallClassName(String className);


    String          GetSetHeadFunc();

    String          GetADOStoreSqlSelectName();
    String          GetADOStoreSqlWhereName();
    String          GetDot();       //逗号转义符, 如果是最后一个classMember, 就不加逗号, 否则, 加
public:
	SourceGen();
	~SourceGen();
	void			GenSource(WorkSpace	*workSpace, String srcFileName, IClassManager	*	curClass, TStrings	*	outputStr);
};

#endif
