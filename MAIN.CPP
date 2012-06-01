//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "About.h"
#include "FrmLog.h"
#include "FrmPlugin.h"
#include "FrmSearchFiles.h"
#include "FrmDesign.h"
#include "FrmDebug.h"
#include "FrmConfig.h"
#include "FrmSourceEdit.h"
#include "FrmSetup.h"

//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TMainForm *MainForm;

#define			REOPEN_LIST_FILENAME		"ReOpenList.ini"
#define			MAX_REOPEN_COUNT			20
//---------------------------------------------------------------------------

__fastcall TMainForm::TMainForm(TComponent *Owner)
	: TForm(Owner)
{
	m_IsCreatingWnd = false;
	SetAppPath(ExtractFilePath(Application->ExeName));
	SetLangModule(lmUTF8);

	m_ReOpenList = new TStringList;

    
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CreateMDIChild(WorkSpace	*	workSpace)
{
	m_IsCreatingWnd = true;
	SetErrorOutPut(StatusBar, LogFrm->memLog);
	
	TMDIChild *Child = NULL;

	//--- create a new MDI child window ----
	Child = new TMDIChild(Application);
	Child->InitFrm(workSpace, m_ParseEngine);
	Child->Caption = workSpace->GetFullName();
	Child->NeedSaveReq = ChildNeedSave;
	Child->RefreshWorkSpaceReq = RefreshWorkSpace;
    Child->SetPlugins(&m_ExePlugins);
	TabSet1->Tabs->AddObject(Child->Caption,Child);
	Child->MainTabSet = TabSet1;
	TabSet1->Repaint();
	int tab_index = TabSet1->Tabs->Count-1;
	TabSet1->TabIndex = tab_index;
	SearchFilesFrm->LoadFile = LoadSearchFile;

	ApplyWndConfig(Child);
	m_IsCreatingWnd = false;
}

//---------------------------------------------------------------------------

void            TMainForm::LoadExePluginIni()
{
    auto_ptr<TMemIniFile>     plugsIni(new TMemIniFile(GetAppPath() + "ExPlugin.ini"));
    String      plugsName = plugsIni->ReadString("Plugins", "Secs", "");
    auto_ptr<TStringList>       plugsStr(new TStringList);
    SplitStr(plugsName, ",", plugsStr.get());

    String  curSecName;
    for(int i=0; i<plugsStr->Count; i++)
    {
        curSecName = plugsStr->Strings[i];
        tagExePlugins   *   curPlugin = new tagExePlugins;
        curPlugin->Name = plugsIni->ReadString(curSecName, "Name", "");
        curPlugin->ClassName = plugsIni->ReadString(curSecName, "ClassName", "");
        curPlugin->ExeName = plugsIni->ReadString(curSecName, "ExeName", "");
        curPlugin->RecvType = plugsIni->ReadInteger(curSecName, "RecvType", 0);
        m_ExePlugins.Add(curPlugin);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
 	TabSet1->Tabs->Clear();

	//初始化动作
	GetWorkSpaceManager()->BindGUI(lvWorkSpace);
    GetWorkSpaceManager()->BindGUI(tvWorkSpaceTree);
	m_ParseEngine = new ParseEngine();

	InitReOpenList();
	m_PluginManager.LoadDLL(GetAppPath(), m_ParseEngine);

	SetParseEngine(m_ParseEngine);
    LoadExePluginIni();
}

void					TMainForm::RefreshReOpenList()
{
	miReOpen->Clear();
	TMenuItem	*	miReOpenitem;
	for(int i=0; i<m_ReOpenList->Count; i++)
	{
		miReOpenitem = new TMenuItem(miReOpen);
		miReOpenitem->Tag = i;
		miReOpenitem->Caption = m_ReOpenList->Strings[i];
		miReOpenitem->OnClick = miReOpenitemExecute;
		miReOpen->Add(miReOpenitem);
	}
}

void __fastcall 		TMainForm::miReOpenitemExecute(TObject *Sender)
{
	TMenuItem	*	curItem = (TMenuItem *)Sender;
	LoadWorkSpace(m_ReOpenList->Strings[curItem->Tag]);
}

void					TMainForm::InitReOpenList()
{
	//初始化重新打开列表
	String reOpenlist = GetAppPath() + REOPEN_LIST_FILENAME;
	if(FileExists(reOpenlist) == 0)
	{
		FileCreate(reOpenlist);
	}

	m_ReOpenList->LoadFromFile(reOpenlist);
	RefreshReOpenList();
}

//---------------------------------------------------------------------------


void __fastcall TMainForm::FileOpen1Execute(TObject *Sender)
{
	OpenDialog->Filter = "工作区文件 (*.egg)|*.egg";
	if (OpenDialog->Execute())
	{
		LoadWorkSpace(OpenDialog->FileName);
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::HelpAbout1Execute(TObject *Sender)
{
	AboutBox->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FileExit1Execute(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TabSet1Change(TObject *Sender, int NewTab,
      bool &AllowChange)
{
	TMDIChild * ChildForm = (TMDIChild *)TabSet1->Tabs->Objects[NewTab];
	 if (ChildForm)
	 {
	   ChildForm->BringToFront();
	   if (!m_IsCreatingWnd)
	   {
		   GetWorkSpaceManager()->SetWorkSpaceSelect(ChildForm->GetWorkSpace());
	   }
	 }	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TabSet1DrawTab(TObject *Sender, TCanvas *TabCanvas,
      TRect &R, int Index, bool Selected)
{
	if (Selected)
	{
		TabCanvas->Font->Color = clBlack;
	}
	else
	{
       TabCanvas->Font->Color = clBlack;
	}
	TabCanvas->TextOut(R.left,R.top,TabSet1->Tabs->Strings[Index]);
}

//---------------------------------------------------------------------------

void		TMainForm::LoadWorkSpace(String	fileName)
{
	if(GetWorkSpaceManager()->GetWorkSpaceCount() != 0)
		FileClose1Execute(this);

	GetWorkSpaceManager()->LoadFromFile(fileName);

	//把该文件加到重新打开列表中
	int curIndex = m_ReOpenList->IndexOf(fileName);
	while(curIndex >= 0)
	{
		m_ReOpenList->Delete(curIndex);
		curIndex = m_ReOpenList->IndexOf(fileName);
	}
	m_ReOpenList->Insert(0, fileName);
	SaveReOpenList();

	this->Caption = FormatStr("SuperParse2007(%s)", fileName);
    Application->Title = FormatStr("SuperParse2007(%s)", fileName);
}

void					TMainForm::SaveReOpenList()
{
	while(m_ReOpenList->Count > MAX_REOPEN_COUNT)
		m_ReOpenList->Delete(MAX_REOPEN_COUNT);
	m_ReOpenList->SaveToFile(GetAppPath() + REOPEN_LIST_FILENAME);
	InitReOpenList();
}

void __fastcall TMainForm::edtFindChange(TObject *Sender)
{
	GetWorkSpaceManager()->TextSelect(edtFind->Text);	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::lvWorkSpaceKeyPress(TObject *Sender, char &Key)
{
	edtFind->Text = Key;
	edtFind->SetFocus();
	edtFind->SelStart = 1;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::lvWorkSpaceDblClick(TObject *Sender)
{
	//读取工作区
	WorkSpace	*  selWorkSpace = 	GetWorkSpaceManager()->GetWorkSpace(lvWorkSpace->ItemIndex);
    DoWorkSpaceListDbClick(selWorkSpace);
}
//---------------------------------------------------------------------------
void            TMainForm::DoWorkSpaceListDbClick(WorkSpace	*selWorkSpace)
{
    if(selWorkSpace == NULL)
		return;

	TMDIChild		*curChild = GetCurWndByWorkSpace(selWorkSpace);
	if(curChild)
	{
		curChild->BringToFront();
		curChild->DoBringToFront();
	}
	else
	{
		CreateMDIChild(selWorkSpace);
	}
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::tvWorkSpaceTreeDblClick(TObject *Sender)
{
    if(tvWorkSpaceTree->Selected == NULL)
        return;
    if(tvWorkSpaceTree->Selected->Parent == NULL)
        return;

    DoWorkSpaceListDbClick((WorkSpace	*)tvWorkSpaceTree->Selected->Data);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::actWatchLogExecute(TObject *Sender)
{
	LogFrm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	int result = Application->MessageBox(L"是否关闭程序?",L"关闭询问",MB_OKCANCEL);
	if(result == IDCANCEL)
	{
		CanClose = false;
	}
	else
		CanClose = true;

	if(CanClose == true)
	{
		FileClose1Execute(this);
	}

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	delete	m_ReOpenList;
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::actWatchPluginExecute(TObject *Sender)
{
	PluginFrm->ShowPlugins(&m_PluginManager);	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FileNew1Execute(TObject *Sender)
{
	//新建工作区
	if(GetWorkSpaceManager()->GetWorkSpaceCount() != 0)
		FileClose1Execute(this);

		
	GetWorkSpaceManager()->CreateNewWorkSpace();
	WorkSpace	*  selWorkSpace = 	GetWorkSpaceManager()->GetWorkSpace(0);
	CreateMDIChild(selWorkSpace);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::FileSave1Execute(TObject *Sender)
{
	if(GetWorkSpaceManager()->GetWorkSpaceCount() == 0)
		return;
	//保存工作区
	if(GetWorkSpaceManager()->IsNewFile())
	{
		SaveDialog1->Filter = "工作区文件 (*.egg)|*.egg";
		if(SaveDialog1->Execute())
		{
			GetWorkSpaceManager()->SaveToFile(SaveDialog1->FileName);
		}
	}
	else
		GetWorkSpaceManager()->SaveToFile();
}
//---------------------------------------------------------------------------

void					TMainForm::ChildNeedSave()
{
	FileSave1Execute(NULL);
}

void __fastcall TMainForm::FileClose1Execute(TObject *Sender)
{
	if(GetWorkSpaceManager()->GetWorkSpaceCount() == 0)
		return;
	int result = Application->MessageBox(L"是否保存所有?",L"是否保存所有?",MB_OKCANCEL);
	bool	needSave = true;
	if(result == IDCANCEL)
	{
		needSave = false;
	}

	TMDIChild	*	curChild;
	if(needSave)
	{
		for(int i=0; i<this->MDIChildCount; i++)
		{
			curChild = (TMDIChild	*)this->MDIChildren[i];
			curChild->actSaveFileExecute(this);
		}
        FileSave1Execute(Sender);
	}

	for(int i=this->MDIChildCount-1; i>=0; i--)
	{
		this->MDIChildren[i]->Close();
	}

	GetWorkSpaceManager()->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::actSetCommentExecute(TObject *Sender)
{
    if(nbShowPages->PageIndex == 0)
    {
        int index = lvWorkSpace->ItemIndex;
        if(index < 0)
            return;

        String comment = GetWorkSpaceManager()->GetWorkSpace(index)->GetComment();
        if(InputQuery(L"输入注释", L"输入注释", comment))
        {
            GetWorkSpaceManager()->SetWorkSpaceComment(index, comment);
        }
    }
    else
    {
        if(tvWorkSpaceTree->Selected == NULL)
        {
            return;
        }

        if(tvWorkSpaceTree->Selected->Parent == NULL)
        {
            WorkPackHead * curHead = (WorkPackHead *)tvWorkSpaceTree->Selected->Data;
            if(curHead == NULL)
                return;

            if(curHead->m_Head == "")
            {
                ShowMessage("此类没有头, 请先为此类的子文件添加注释, 再添加文件类的注释");
                return;
            }
            String describe = curHead->m_Describe;
            if(InputQuery("输入注释", "输入注释", describe))
            {
                curHead->m_Describe = describe;
                GetWorkSpaceManager()->RefreshGUI();
            }
        }
        else
        {
            WorkSpace * curWorkSpace = (WorkSpace *)tvWorkSpaceTree->Selected->Data;
            if(curWorkSpace == NULL)
                return;

            String comment = curWorkSpace->GetComment();
            if(InputQuery("输入注释", "输入注释", comment))
            {
                curWorkSpace->SetComment(comment);
                GetWorkSpaceManager()->RefreshGUI();
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::actDeleteWorkSpaceExecute(TObject *Sender)
{
    if(nbShowPages->PageIndex == 0)
    {
        int index = lvWorkSpace->ItemIndex;
        if(index < 0)
            return;

        int result = Application->MessageBox(L"真的要删除吗?",L"删除?",MB_OKCANCEL);
        if(result == IDCANCEL)
        {
            return;
        }

        TMDIChild		*curChild = GetCurWndByWorkSpace(GetWorkSpaceManager()->GetWorkSpace(index));

        if(curChild)
            curChild->Close();

        GetWorkSpaceManager()->DeleteWorkSpace(index);
    }
    else
    {
        if(tvWorkSpaceTree->Selected == NULL)
        {
            return;
        }
        if(tvWorkSpaceTree->Selected->Parent == NULL)
            return;
            
        WorkSpace * curWorkSpace = (WorkSpace *)tvWorkSpaceTree->Selected->Data;
        if(curWorkSpace == NULL)
            return;

        int result = Application->MessageBox(L"真的要删除吗?",L"删除?",MB_OKCANCEL);
        if(result == IDCANCEL)
        {
            return;
        }

        TMDIChild		*curChild = GetCurWndByWorkSpace(curWorkSpace);

        if(curChild)
            curChild->Close();

        GetWorkSpaceManager()->DeleteWorkSpace(curWorkSpace);
    }
}

//---------------------------------------------------------------------------
TMDIChild		*		TMainForm::GetCurWndByWorkSpace(WorkSpace *selWorkSpace)
{
	for(int i=0; i<MDIChildCount; i++)
	{
		TMDIChild * curChild = (TMDIChild *)MDIChildren[i];
		if(curChild->GetWorkSpace() == selWorkSpace)
		{
			//已经打开了工作区
			return	curChild;
		}
	}
	return	NULL;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::actNewWorkSpaceExecute(TObject *Sender)
{
	WorkSpace	*  selWorkSpace = GetWorkSpaceManager()->CreateNewWorkSpace();
	CreateMDIChild(selWorkSpace);
}
//---------------------------------------------------------------------------


void					TMainForm::RefreshWorkSpace()
{
	GetWorkSpaceManager()->RefreshGUI();
}
void __fastcall TMainForm::actSearchFilesExecute(TObject *Sender)
{
	SearchFilesFrm->Show();	
}
//---------------------------------------------------------------------------

void					TMainForm::LoadSearchFile(String fileName)
{
	if(ActiveMDIChild == NULL)
	{
		ShowMessage("没有任何激活窗口!");
		return;
	}
	TMDIChild *child = (TMDIChild *)ActiveMDIChild;
	child->LoadFromFile(fileName);
}
void __fastcall TMainForm::actAddWorkSpaceExecute(TObject *Sender)
{
	OpenDialog1->Filter = "工作文件 (*.eggxp)|*.eggxp";
	if(OpenDialog1->Execute())
	{
		for(int i=0; i<OpenDialog1->Files->Count; i++)
		{
			GetWorkSpaceManager()->AddToWorkSpace(OpenDialog1->Files->Strings[i]);
		}
		GetWorkSpaceManager()->SaveToFile();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::actOutputAllRecvExecute(TObject *Sender)
{
	OutputSrc(gReadDataSrc);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::actOutputAllSendExecute(TObject *Sender)
{
	OutputSrc(gWriteBufferSrc);
}
//---------------------------------------------------------------------------

void					TMainForm::OutputSrc(String srcMode)
{
	if(MDIChildCount > 0)
	{
		ShowMessage("请先关闭所有窗口之后再进行操作");
		return;
	}
	SaveDialog1->Filter = "头文件 (*.h)|*.h";
	auto_ptr<TStringList>	saveStr(new TStringList);
	if(SaveDialog1->Execute())
	{
		m_AllSourceGen.SaveSource(GetWorkSpaceManager(), &m_PluginManager,
						SaveDialog1->FileName, srcMode);
	}
}
void __fastcall TMainForm::actSetKeyExecute(TObject *Sender)
{
	String key = IntToStr(GetKey());
	if(InputQuery("设置Key", "设置Key", key))
	{
		SetKey(key.ToIntDef(0));
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::actUseGlobalKeyExecute(TObject *Sender)
{
	SetUseGlobalKey(actUseGlobalKey->Checked);	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::actParseAsHexExecute(TObject *Sender)
{
	SetParseAsHex(actParseAsHex->Checked);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::actOpenDesignExecute(TObject *Sender)
{
    //打开设计页
    if(GetWorkSpaceManager()->IsNewFile())
    {
        int result = Application->MessageBox(L"文件必须保存后才可以打开设计页, 是否保存?",L"保存询问",MB_OKCANCEL);
        if(result == IDCANCEL)
        {
            return;
        }
        FileSave1Execute(Sender);
    }

    if(GetWorkSpaceManager()->IsNewFile() == false)
    {
        GetWorkSpaceManager()->BeginUpdate();
        DesignFrm->EditWorkSpace(GetWorkSpaceManager());
        FileSave1Execute(Sender);
        GetWorkSpaceManager()->EndUpdate();
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::actChangeViewExecute(TObject *Sender)
{
    if(nbShowPages->PageIndex == 0)
    {
        nbShowPages->PageIndex = 1;
        actChangeView->Caption = "切换到经典视图";

        //控制刷新, 为0的时候不刷新, 为1的时候刷新
        lvWorkSpace->Tag = 0;
        tvWorkSpaceTree->Tag = 1;
    }
    else
    {
        nbShowPages->PageIndex = 0;
        actChangeView->Caption = "切换到树形视图";

        lvWorkSpace->Tag = 1;
        tvWorkSpaceTree->Tag = 0;
    }

    RefreshWorkSpace();  
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::actDebugExecute(TObject *Sender)
{
    DebugFrm->Show();    
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::actOpenSetupExecute(TObject *Sender)
{
    
//    GetConfig()->Value2GUI();
//    if(ConfigFrm->ShowModal())
//    {
//        GetConfig()->GUI2Value();
//        ApplyConfig();
//    }
}
//---------------------------------------------------------------------------


void                    TMainForm::ApplyConfig()
{                  
//    GetConfig()->SaveToFile(SETUP_INI_FILE);
//    if((bool)GetConfig()->GetValue("cbUseDefSetup") == false)
//        return;
//    TMDIChild	*	curChild;
//
//    for(int i=0; i<this->MDIChildCount; i++)
//    {
//        curChild = (TMDIChild	*)this->MDIChildren[i];
//        ApplyWndConfig(curChild);
//    }
//
//    SourceEditFrm->memSrcFile->Font->Name = GetConfig()->GetValue("edtCharset");
//    SourceEditFrm->memSrcFile->Font->Size = GetConfig()->GetValue("edtCharsetSize");
}

void                    TMainForm::ApplyWndConfig(TMDIChild * curChild)
{
//    if((bool)GetConfig()->GetValue("cbUseDefSetup") == false)
//        return;
//
//	curChild->m_HexEditor->Font->Name = GetConfig()->GetValue("edtCharset");
//	curChild->m_HexEditor->Font->Size = GetConfig()->GetValue("edtCharsetSize");
}

void __fastcall TMainForm::actSetupExecute(TObject *Sender)
{
	SetupFrm->Show();	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::actOutputReadWriteAllExecute(TObject *Sender)
{
    OutputSrc(gAllReadWriteSrc);    
}
//---------------------------------------------------------------------------



