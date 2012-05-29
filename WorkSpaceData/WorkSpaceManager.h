//---------------------------------------------------------------------------

#ifndef WorkSpaceManagerH
#define WorkSpaceManagerH
//---------------------------------------------------------------------------

#include "SPCommon.h"
#include "ParseFileData.h"
#include "SourceData.h"
#include "AMap.h"
#include <ComCtrls.hpp>

class	ClassManager;
class	FileManager;


//Êý¾ÝÀà
class	WorkSpace
{
private:
	String 			m_FilePath;
	String			m_FileName;
	String			m_Comment;
	FileManager		m_FileManager;
	ClassManager	m_ClassManager;

	void			CreateNew();
    
public:
	WorkSpace();
	~WorkSpace();
	String			GetFileName(){return	m_FileName;}
	void			SetFileName(String fileName){m_FileName = fileName;}
	String			GetComment(){return	m_Comment;}
	String			GetFullName();
	String			GetPath(){return	m_FilePath;}
	void			SetComment(String comment){m_Comment = comment;}
    String          GetStructName();

	bool			Open();
	bool			OpenClassOnly();
	void			Close();
	FileManager	*	GetFileManager(){return	&m_FileManager;}
	ClassManager	*GetClassManager(){return	&m_ClassManager;}

	bool			IsNewFile();
	bool			SaveToFile(String fileName = "");
    void            DeleteWorkSpaceFile();

    String          GetHead();
    String          GetSubHead();

    void			InitWorkSpace(String filePath, String	fileName, String comment);
	void			SetFilePath(String path){m_FilePath = path;}

};

//==============================================================================
struct   WorkPackHead
{
    AList<WorkSpace>        m_Files;
    String                  m_Head;
    String                  m_Describe;
    WorkPackHead();
};

//=============================================================================
struct      tagWorkPackHeadDescribe
{
    String      HeadName;
    String      HeadDescribe;
};

class   WorkPacks
{
private:
	AList<WorkPackHead>        	m_WorkPacks;
  	
public:
    WorkPacks();
    ~WorkPacks();
    void                        LoadWorkSpaces(AList<WorkSpace> * workSpaces);
	AList<WorkPackHead> *  		GetWorkPacks(){return   &m_WorkPacks;}
	WorkPackHead		*		FindWorkPack(String head);
    void                        Clear();
};


//=============================================================================

class	WorkSpaceManager
{
private:
    WorkPacks               m_WorkPacks;
	AList<WorkSpace>		m_WorkSpace;
	String					m_FileName;
	TListView		*		m_ListItemView;
    TTreeView       *       m_TreeView;
    String                  m_FilePath;
    bool                    m_bIsUpdating;

	void __fastcall 		lvWorkSpaceData(TObject *Sender, TListItem *Item);
    void                    LoadFromFileNew(String  fileName);
    void                    AddWorkSpace(String path, String fileName, String comment);
    TTreeNode       *       GetTreeNodeByWorkSpace(WorkSpace * workSpace);
public:
	WorkSpaceManager();
	~WorkSpaceManager();
    WorkPacks   *   GetWorkSpacePacks(){return   &m_WorkPacks;}
	void			RefreshGUI(bool reloadMap = true);
	void			LoadFromFile(String fileName);
	WorkSpace	*	CreateNewWorkSpace(bool  needRefresh = true);
	bool			IsNewFile();
    bool			SaveToFile(String fileName = "");
	void			Clear();
	void			BindGUI(TListView	*	lvList);
	void			BindGUI(TTreeView	*	lvTree);    
	int				TextSelect(String	text);
	WorkSpace	*	GetWorkSpace(int index){return	m_WorkSpace[index];}
	void			SetWorkSpaceSelect(WorkSpace	*	curWorkSpace);
	int				GetWorkSpaceCount(){return	m_WorkSpace.Count();}

	void			SetWorkSpaceComment(int index, String Comment);
	void			DeleteWorkSpace(int index);
    void			DeleteWorkSpace(WorkSpace	*	curWorkSpace);
	void			AddToWorkSpace(String fileName);
    String          GetFilePath(){return    m_FilePath;}
    void            ReloadWorkSpacePack();
    void            BeginUpdate();
    void            EndUpdate();
};


WorkSpaceManager    *   GetWorkSpaceManager();

#endif
