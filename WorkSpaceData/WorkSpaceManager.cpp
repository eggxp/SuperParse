//---------------------------------------------------------------------------


#pragma hdrstop

#include "WorkSpaceManager.h"
#include "SourceLoader.h"
#include "SourceGen.h"
#include "FrmSetup.h"
#include <IniFiles.hpp>
//---------------------------------------------------------------------------

#pragma package(smart_init)

//=================================================================
static       WorkSpaceManager       gWorkSpaceManager;

WorkSpaceManager    *   GetWorkSpaceManager()
{
    return  &gWorkSpaceManager;
}
//=================================================================

size_t	GetStrCRC32(const char * StrKey)
{
    int strLen = strlen(StrKey);
    if(strLen == 0)
        return 0;
    if(strLen == 1)
        return  StrKey[0];

    return  StrKey[0]*1000 + StrKey[1];

//	return	GetCrc32(0, (char *)StrKey, strlen(StrKey));
}


WorkSpace::WorkSpace()
{
}

WorkSpace::~WorkSpace()
{
}

void			WorkSpace::InitWorkSpace(String filePath, String	fileName, String comment)
{
	m_FilePath = filePath;
	m_FileName = fileName;
	m_Comment = comment;
}

String			WorkSpace::GetFullName()
{
	return	FormatStr("%s(%s)", m_Comment, m_FileName);
}

bool			WorkSpace::Open()
{
	String fileName = m_FilePath+m_FileName;
	if(m_FileName != "")
	{
		OpenClassOnly();
		m_FileManager.LoadFromFile(fileName);
		return	true;
	}
	else
	{
		CreateNew();
		return	false;
	}
}

bool			WorkSpace::OpenClassOnly()
{
	//读取类数据
	String fileName = m_FilePath+m_FileName;
	SourceLoader	sourceLoader;
	sourceLoader.LoadFromFile(fileName+".h", &m_ClassManager);
	return	true;
}

void			WorkSpace::Close()
{
	m_FileManager.Clear();
	m_ClassManager.Clear();
}

bool			WorkSpace::IsNewFile()
{
	if(m_FileName == "")
		return true;
	return false;
}

bool			WorkSpace::SaveToFile(String fileName)
{
	if(fileName == "")
		fileName = m_FilePath+m_FileName;

	if(fileName == "")
		return	false;

	if(m_FileName == "")
		m_FileName = ExtractFileName(fileName);
	auto_ptr<TStringList>	saveStr(new TStringList);
	SourceGen	sourceGen;
	sourceGen.GenSource(this, gBasicSrc, &m_ClassManager, saveStr.get());
	saveStr->SaveToFile(fileName+".h");
	m_FileManager.SaveToFile(fileName);
	return true;
}

void            WorkSpace::DeleteWorkSpaceFile()
{
    String  fileName;
    if(fileName == "")
		fileName = m_FilePath+m_FileName;

	if(fileName == "")
		return;

    if(FileExists(fileName))
        DeleteFile(fileName);
    if(FileExists(fileName + ".h"))
        DeleteFile(fileName + ".h");
}

void			WorkSpace::CreateNew()
{
	m_FileManager.CreateNew();
}

String          WorkSpace::GetHead()
{
    return  m_Comment.SubString(1, 2);
}

String          WorkSpace::GetSubHead()
{
    return  m_Comment.SubString(4, 2);
}

String          WorkSpace::GetStructName()
{
    String result =   RightString(m_Comment, "#");
    result = result.Trim();
    return  result;
}

//=============================================================================
WorkPackHead::WorkPackHead()    : m_Files(false)
{
}
//=============================================================================
WorkPacks::WorkPacks() : m_WorkPacks(false)
{
}

WorkPacks::~WorkPacks()
{
}

void        WorkPacks::Clear()
{
	m_WorkPacks.Clear();
}

WorkPackHead		*		WorkPacks::FindWorkPack(String head)
{
	for(int i=0; i<m_WorkPacks.Count(); i++)
	{
		if(m_WorkPacks[i]->m_Head == head)
			return	m_WorkPacks[i];
	}
	return NULL;
}

int 	ComparWorkPackName(WorkPackHead *Item1, WorkPackHead *Item2)
{
	String Dis1 =  Item1->m_Head;
	String Dis2 =  Item2->m_Head;

	return	Dis1.AnsiCompare(Dis2);
}

void        WorkPacks::LoadWorkSpaces(AList<WorkSpace> * workSpaces)
{
    for(int i=0; i<m_WorkPacks.Count(); i++)
    {
        m_WorkPacks.At(i)->m_Files.Clear();
    }

    String  curHead;
    WorkPackHead    *   curPackHead;
    tagWorkPackHeadDescribe *   curWorkPackHeadDescribe;
    for(int i=0; i<workSpaces->Count(); i++)
    {
        curHead = workSpaces->At(i)->GetHead();
        curPackHead = FindWorkPack(curHead);
        if(curPackHead == NULL)
        {
            curPackHead = new WorkPackHead;
            curPackHead->m_Head = curHead;
            m_WorkPacks.Add(curPackHead);
        }
        curPackHead->m_Files.Add(workSpaces->At(i));
    }

    for(int i=m_WorkPacks.Count()-1; i>=0; i--)
    {
        if(m_WorkPacks.At(i)->m_Files.Count() == 0)
        {
            m_WorkPacks.Delete(i);
        }
    }

    m_WorkPacks.Sort(ComparWorkPackName);
}

//=============================================================================

WorkSpaceManager::WorkSpaceManager()
{
	m_ListItemView = NULL;
}

WorkSpaceManager::~WorkSpaceManager()
{
}

void			WorkSpaceManager::Clear()
{
	m_WorkSpace.Clear();
    m_WorkPacks.Clear();
	RefreshGUI();
	m_FileName = "";
}

int 	ComparWorkSpaceName(WorkSpace *Item1, WorkSpace *Item2)
{
	String Dis1 =  Item1->GetFullName();
	String Dis2 =  Item2->GetFullName();

	return	Dis1.AnsiCompare(Dis2);
}

WorkSpace	*			WorkSpaceManager::CreateNewWorkSpace(bool  needRefresh)
{
	WorkSpace	*	workSpace = new WorkSpace;
	workSpace->SetFilePath(ExtractFilePath(m_FileName));
	m_WorkSpace.Add(workSpace);

    if(needRefresh)
    	RefreshGUI();
	return	workSpace;
}

bool			WorkSpaceManager::IsNewFile()
{
	if(m_FileName == "")
		return true;
	return false;
}

bool			WorkSpaceManager::SaveToFile(String fileName)
{
	if(fileName == "")
		fileName = m_FileName;
	if(fileName == "")
		return false;

	if(m_FileName == "")
	{
		//是新文件保存
		m_FileName = fileName;
		for(int i=0; i<m_WorkSpace.Count(); i++)
		{
			m_WorkSpace[i]->SetFilePath(ExtractFilePath(fileName));
		}
        m_FilePath = ExtractFilePath(fileName);
	}

//  	auto_ptr<TStringList>	saveStr(new TStringList);
//
//	for(int i=0; i<m_WorkSpace.Count(); i++)
//	{
//
//		saveStr->Add(m_WorkSpace[i]->GetFileName());
//		saveStr->Add(m_WorkSpace[i]->GetComment());
//	}
//
//	saveStr->Add("");
//	saveStr->Add("==LibStart==");
//	saveStr->SaveToFile(fileName);
    //ini方式保存
    auto_ptr<TMemIniFile>       writeIni(new  TMemIniFile(fileName));
    writeIni->Clear();
    writeIni->WriteInteger("Files", "FilesCount", m_WorkSpace.Count());
    
    String  curSecName;
    for(int i=0; i<m_WorkSpace.Count(); i++)
    {
        curSecName = FormatStr("Files_%d", i+1);

        if(m_WorkSpace[i]->GetComment() != "")
            writeIni->WriteString("Files", curSecName,
                    FormatStr("%s,%s", m_WorkSpace[i]->GetFileName(),
                                    m_WorkSpace[i]->GetComment() ));
        else
            writeIni->WriteString("Files", curSecName,
                    FormatStr("%s,", m_WorkSpace[i]->GetFileName()));
    }

    writeIni->WriteInteger("Head", "HeadsCount", m_WorkPacks.GetWorkPacks()->Count());
    WorkPackHead *  workPackHead;
    for(int i=0; i<m_WorkPacks.GetWorkPacks()->Count(); i++)
    {
        curSecName = FormatStr("Head_%d", i+1);
        workPackHead = m_WorkPacks.FindWorkPack(m_WorkPacks.GetWorkPacks()->At(i)->m_Head);
        if(workPackHead == NULL)
            continue;

        if(workPackHead->m_Describe != "")
        {
            writeIni->WriteString("Head", curSecName,
                        FormatStr("%s,%s", workPackHead->m_Head, workPackHead->m_Describe));
        }
        else
        {
            if(workPackHead->m_Head != "")
            {
                writeIni->WriteString("Head", curSecName, workPackHead->m_Head + ",");
            }
            else
                writeIni->WriteString("Head", curSecName, ",");
        }
	}

	writeIni->WriteInteger("Other", "Language", SetupFrm->cbLanguage->ItemIndex);
    writeIni->UpdateFile();

    
	RefreshGUI();
	return true;
}

void			WorkSpaceManager::LoadFromFile(String fileName)
{
	FileExistCheck(fileName);
	Clear();
	WorkSpace	*	workSpace;
	m_FileName = fileName;
	auto_ptr<TStringList>	loadStr(new TStringList);

    m_FilePath = ExtractFilePath(m_FileName);

    loadStr->LoadFromFile(fileName);
    if(!loadStr->Text.AnsiPos("==LibStart=="))
    {
        LoadFromFileNew(fileName);
        return;
    }
    else
    {
        for(int i=0; i<loadStr->Count; i+=2)
        {
            if(i+1 >= loadStr->Count)
                break;

            if(loadStr->Strings[i] == "" && loadStr->Strings[i+1] == "==LibStart==")
                break;

            AddWorkSpace(ExtractFilePath(fileName), loadStr->Strings[i], loadStr->Strings[i+1]);
        }
    }
	m_WorkSpace.Sort(ComparWorkSpaceName);
	RefreshGUI();
}

void            WorkSpaceManager::AddWorkSpace(String path, String fileName, String comment)
{
    WorkSpace * workSpace = CreateNewWorkSpace(false);
    workSpace->InitWorkSpace(path, fileName, comment);
}

void            WorkSpaceManager::LoadFromFileNew(String    fileName)
{
    //ini方式读取
    auto_ptr<TMemIniFile>       loadIni(new  TMemIniFile(fileName));
    auto_ptr<TStringList>       splitStr(new TStringList);
    
    int fileCount = loadIni->ReadInteger("Files", "FilesCount", 0);
    String  curSecName;
    String  curValue;
    for(int i=0; i<fileCount; i++)
    {
        curSecName = FormatStr("Files_%d", i+1);
        curValue = loadIni->ReadString("Files", curSecName, "");
        SplitStr(curValue, ",", splitStr.get());
        AddWorkSpace(ExtractFilePath(fileName), splitStr->Strings[0], splitStr->Strings[1]);
    }

    m_WorkSpace.Sort(ComparWorkSpaceName);
    m_WorkPacks.LoadWorkSpaces(&m_WorkSpace);

    int headCount = loadIni->ReadInteger("Head", "HeadsCount", 0);
    for(int i=0; i<headCount; i++)
    {
        curSecName = FormatStr("Head_%d", i+1);
        curValue = loadIni->ReadString("Head", curSecName, "");
        SplitStr(curValue, ",", splitStr.get());
        WorkPackHead    *   curHead = m_WorkPacks.FindWorkPack(splitStr->Strings[0]);
        if(curHead)
        {
            if(splitStr->Count > 1)
                curHead->m_Describe = splitStr->Strings[1];
        }
    }

	SetupFrm->cbLanguage->ItemIndex = loadIni->ReadInteger("Other", "Language", 0);
	SetupFrm->cbLanguageChange(NULL);
	RefreshGUI(false);
}

void			WorkSpaceManager::AddToWorkSpace(String fileName)
{
	String fileRealName = ExtractFileName(fileName);

	for(int i=0; i<m_WorkSpace.Count(); i++)
	{
		if(m_WorkSpace[i]->GetFileName() == fileRealName)
			return;
	}

	
	WorkSpace	*	workSpace = CreateNewWorkSpace(false);
	workSpace->InitWorkSpace(ExtractFilePath(fileName), fileRealName, "");
	m_WorkSpace.Sort(ComparWorkSpaceName);
	RefreshGUI();
}

void			WorkSpaceManager::BindGUI(TListView	*	lvList)
{
	m_ListItemView = lvList;
	m_ListItemView->OwnerData = true;
	m_ListItemView->OnData = lvWorkSpaceData;
   	RefreshGUI();
}

void			WorkSpaceManager::BindGUI(TTreeView	*	lvTree)
{
    m_TreeView = lvTree;
    m_TreeView->ReadOnly = true;
    m_TreeView->RowSelect = true;
    m_TreeView->ShowLines = false;
    m_TreeView->HideSelection = false;
   	RefreshGUI();
}

void                    WorkSpaceManager::ReloadWorkSpacePack()
{
    m_WorkPacks.LoadWorkSpaces(&m_WorkSpace);
}

void					WorkSpaceManager::RefreshGUI(bool reloadMap)
{
    if(m_bIsUpdating)
        return;
	if(m_ListItemView == NULL && m_TreeView == NULL)
		return;

    if(reloadMap)
        ReloadWorkSpacePack();
    if(m_ListItemView && m_ListItemView->Tag)
    {
        ListView_SetItemCountEx(m_ListItemView->Handle, m_WorkSpace.Count(), LVSICF_NOINVALIDATEALL | LVSICF_NOSCROLL);
        m_ListItemView->Refresh();
    }

    if(m_TreeView && m_TreeView->Tag)
    {
        m_TreeView->Items->BeginUpdate();
        WorkSpace *  selWorkSpaceNode = NULL;
        if(m_TreeView->Selected)
        {
            selWorkSpaceNode = (WorkSpace *)m_TreeView->Selected->Data;
        }
        m_TreeView->Items->Clear();
        TTreeNode * curNode;
        TTreeNodes * curNodes = m_TreeView->Items;
        WorkPackHead    *   curHead;
        String  curHeadName;
        for(int i=0; i<m_WorkPacks.GetWorkPacks()->Count(); i++)
        {
            curNode = curNodes->AddChild(NULL, "");
            curHeadName = m_WorkPacks.GetWorkPacks()->At(i)->m_Head;
            
            curHead = m_WorkPacks.FindWorkPack(curHeadName);
            if(curHead == NULL)
                continue;

            if(curHead->m_Describe == "")
            {
                curNode->Text = curHeadName;
            }
            else
            {
                curNode->Text = FormatStr("%s    <%s>", curHeadName, curHead->m_Describe);
            }
            curNode->Data = curHead;
            TTreeNode * curAddChild;
            for(int j=0; j<curHead->m_Files.Count(); j++)
            {
                curAddChild = curNodes->AddChild(curNode, "");
                curAddChild->Text = curHead->m_Files[j]->GetFullName();
                curAddChild->Data = curHead->m_Files[j];
            }

            curNode->Expand(false);
        }

        if(selWorkSpaceNode)
        {
            TTreeNode * curNode = GetTreeNodeByWorkSpace(selWorkSpaceNode);
            if(curNode)
                curNode->Selected = true;
        }
        m_TreeView->Items->EndUpdate();
    }
}

TTreeNode       *       WorkSpaceManager::GetTreeNodeByWorkSpace(WorkSpace * workSpace)
{
    for(int i=0; i<m_TreeView->Items->Count; i++)
    {
        if((WorkSpace   *)m_TreeView->Items->Item[i]->Data == workSpace)
        {
            return  m_TreeView->Items->Item[i];
        }
    }
    return  NULL;
}

int				WorkSpaceManager::TextSelect(String	text)
{
	int index = -1;
	String curName;
    WorkSpace   *   curWorkSpace;
	for(int i=0; i<m_WorkSpace.Count(); i++)
	{
		curName = m_WorkSpace[i]->GetFullName().LowerCase();
		if(curName.AnsiPos(text.LowerCase()) != 0)
		{
			index = i;
            curWorkSpace = m_WorkSpace[i];
			break;
		}
	}

	if(m_ListItemView && m_ListItemView->Tag)
	{
		m_ListItemView->ItemIndex = index;
		if(m_ListItemView->Selected)
			m_ListItemView->Selected->MakeVisible(true);
	}

    if(m_TreeView && m_TreeView->Tag)
    {
        TTreeNode       *   curNode = GetTreeNodeByWorkSpace(curWorkSpace);
        if(curNode)
        {
            curNode->MakeVisible();
            curNode->Selected = true;
        }
    }

	return	index;
}

void			WorkSpaceManager::SetWorkSpaceSelect(WorkSpace	*	curWorkSpace)
{
    if(m_ListItemView && m_ListItemView->Tag)
	{
        for(int i=0; i<m_WorkSpace.Count(); i++)
        {
            if(m_WorkSpace[i] == curWorkSpace)
            {
                m_ListItemView->ItemIndex = i;
                m_ListItemView->SetFocus();
                if(m_ListItemView->Selected)
                    m_ListItemView->Selected->MakeVisible(true);
                break;
            }
        }
    }

    if(m_TreeView && m_TreeView->Tag)
    {
        TTreeNode       *   curNode = GetTreeNodeByWorkSpace(curWorkSpace);
        curNode->MakeVisible();
        curNode->Selected = true;
        m_TreeView->SetFocus();
    }
}

void			WorkSpaceManager::SetWorkSpaceComment(int index, String Comment)
{
	if(m_WorkSpace[index])
	{
		m_WorkSpace[index]->SetComment(Comment);
		RefreshGUI();
	}
}

void            WorkSpaceManager::BeginUpdate()
{
    m_bIsUpdating = true;
}

void            WorkSpaceManager::EndUpdate()
{
    m_bIsUpdating = false;
    RefreshGUI();
}

void			WorkSpaceManager::DeleteWorkSpace(int index)
{
    m_WorkSpace[index]->DeleteWorkSpaceFile();
	m_WorkSpace.Delete(index);
	RefreshGUI();
}

void			WorkSpaceManager::DeleteWorkSpace(WorkSpace	*	curWorkSpace)
{
    for(int i=0; i<m_WorkSpace.Count(); i++)
    {
        if(m_WorkSpace[i] == curWorkSpace)
        {
            DeleteWorkSpace(i);
            break;
        }
    }
}

void __fastcall 		WorkSpaceManager::lvWorkSpaceData(TObject *Sender, TListItem *Item)
{
	Item->Caption = m_WorkSpace[Item->Index]->GetFullName();
}
