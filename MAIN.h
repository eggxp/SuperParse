//----------------------------------------------------------------------------
#ifndef MainH
#define MainH
//----------------------------------------------------------------------------
#include "ChildWin.h"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Messages.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <StdCtrls.hpp>
#include <Menus.hpp>
#include <Controls.hpp>
#include <Forms.hpp>
#include <Graphics.hpp>
#include <Classes.hpp>
#include <SysUtils.hpp>
#include <Windows.hpp>
#include <System.hpp>
#include <ActnList.hpp>
#include <ImgList.hpp>
#include <StdActns.hpp>
#include <ToolWin.hpp>
#include <XPMan.hpp>
#include <Tabs.hpp>
#include "WorkSpaceManager.h"
#include "ParseEngine.h"
#include "PluginManager.h"
#include "AllSourceGen.h"
#include "SPCommon.h"
#include <iniFiles.hpp>
//----------------------------------------------------------------------------


class TMainForm : public TForm
{
__published:
	TMainMenu *MainMenu1;
	TMenuItem *File1;
	TMenuItem *FileNewItem;
	TMenuItem *FileOpenItem;
	TMenuItem *FileCloseItem;
	TMenuItem *Window1;
	TMenuItem *Help1;
	TMenuItem *N1;
	TMenuItem *FileExitItem;
	TMenuItem *WindowCascadeItem;
	TMenuItem *WindowTileItem;
	TMenuItem *WindowArrangeItem;
	TMenuItem *HelpAboutItem;
	TOpenDialog *OpenDialog;
	TMenuItem *FileSaveItem;
	TMenuItem *WindowMinimizeItem;
        TStatusBar *StatusBar;
        TActionList *ActionList1;
        TEditCut *EditCut1;
        TEditCopy *EditCopy1;
        TEditPaste *EditPaste1;
        TAction *FileNew1;
        TAction *FileSave1;
        TAction *FileExit1;
        TAction *FileOpen1;
        TWindowCascade *WindowCascade1;
        TWindowTileHorizontal *WindowTileHorizontal1;
        TWindowArrange *WindowArrangeAll1;
        TWindowMinimizeAll *WindowMinimizeAll1;
        TAction *HelpAbout1;
        TWindowClose *FileClose1;
        TWindowTileVertical *WindowTileVertical1;
        TMenuItem *WindowTileItem2;
	TXPManifest *XPManifest1;
	TTabSet *TabSet1;
	TPanel *Panel1;
	TEdit *edtFind;
	TMenuItem *N2;
	TAction *actWatchLog;
	TMenuItem *N3;
	TMenuItem *miReOpen;
	TAction *actWatchPlugin;
	TMenuItem *N4;
	TSaveDialog *SaveDialog1;
	TAction *actSetComment;
	TPopupMenu *pmWorkSpace;
	TMenuItem *N5;
	TAction *actDeleteWorkSpace;
	TMenuItem *N6;
	TAction *actNewWorkSpace;
	TMenuItem *N7;
	TMenuItem *N8;
	TMenuItem *N9;
	TMenuItem *N10;
	TAction *actSearchFiles;
	TMenuItem *N11;
	TAction *actAddWorkSpace;
	TMenuItem *N12;
	TAction *actOutputAllRecv;
	TAction *actOutputAllSend;
	TMenuItem *N13;
	TMenuItem *Recv1;
	TMenuItem *WriteBuffer1;
	TSplitter *Splitter1;
	TAction *actSetKey;
	TMenuItem *Key1;
	TMenuItem *N14;
	TAction *actUseGlobalKey;
	TMenuItem *Key2;
	TOpenDialog *OpenDialog1;
	TAction *actParseAsHex;
	TMenuItem *N15;
	TMenuItem *N161;
    TMenuItem *N16;
    TAction *actOpenDesign;
    TMenuItem *N17;
    TNotebook *nbShowPages;
    TPanel *Panel2;
    TPanel *Panel3;
    TListView *lvWorkSpace;
    TTreeView *tvWorkSpaceTree;
    TAction *actChangeView;
    TMenuItem *N18;
    TMenuItem *N19;
    TAction *actDebug;
    TMenuItem *N20;
    TMenuItem *N21;
    TAction *actOpenSetup;
    TMenuItem *N22;
	TAction *actSetup;
	TMenuItem *N23;
    TAction *actOutputReadWriteAll;
    TMenuItem *ReadWriteAll1;
        void __fastcall FileOpen1Execute(TObject *Sender);
        void __fastcall HelpAbout1Execute(TObject *Sender);
        void __fastcall FileExit1Execute(TObject *Sender);
	void __fastcall TabSet1Change(TObject *Sender, int NewTab, bool &AllowChange);
	void __fastcall TabSet1DrawTab(TObject *Sender, TCanvas *TabCanvas, TRect &R,
          int Index, bool Selected);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall edtFindChange(TObject *Sender);
	void __fastcall lvWorkSpaceKeyPress(TObject *Sender, char &Key);
	void __fastcall lvWorkSpaceDblClick(TObject *Sender);
	void __fastcall actWatchLogExecute(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall actWatchPluginExecute(TObject *Sender);
	void __fastcall FileNew1Execute(TObject *Sender);
	void __fastcall FileSave1Execute(TObject *Sender);
	void __fastcall FileClose1Execute(TObject *Sender);
	void __fastcall actSetCommentExecute(TObject *Sender);
	void __fastcall actDeleteWorkSpaceExecute(TObject *Sender);
	void __fastcall actNewWorkSpaceExecute(TObject *Sender);
	void __fastcall actSearchFilesExecute(TObject *Sender);
	void __fastcall actAddWorkSpaceExecute(TObject *Sender);
	void __fastcall actOutputAllRecvExecute(TObject *Sender);
	void __fastcall actOutputAllSendExecute(TObject *Sender);
	void __fastcall actSetKeyExecute(TObject *Sender);
	void __fastcall actUseGlobalKeyExecute(TObject *Sender);
	void __fastcall actParseAsHexExecute(TObject *Sender);
    void __fastcall actOpenDesignExecute(TObject *Sender);
    void __fastcall actChangeViewExecute(TObject *Sender);
    void __fastcall tvWorkSpaceTreeDblClick(TObject *Sender);
    void __fastcall actDebugExecute(TObject *Sender);
    void __fastcall actOpenSetupExecute(TObject *Sender);
	void __fastcall actSetupExecute(TObject *Sender);
    void __fastcall actOutputReadWriteAllExecute(TObject *Sender);
private:
	void __fastcall CreateMDIChild(WorkSpace	*	workSpace);
    AList<tagExePlugins>        m_ExePlugins;
    void                        LoadExePluginIni();

	TStringList				*	m_ReOpenList;		//重新打开的列表

	ParseEngine				*m_ParseEngine;
	void					LoadWorkSpace(String	fileName);

	void					InitReOpenList();
	void					RefreshReOpenList();
	void __fastcall 		miReOpenitemExecute(TObject *Sender);
	void					SaveReOpenList();

	PluginManager			m_PluginManager;         
	AllSourceGen			m_AllSourceGen;

	void					OutputSrc(String srcMode);

    void                    DoWorkSpaceListDbClick(WorkSpace	*selWorkSpace);


    void                    ApplyWndConfig(TMDIChild * curChild);
public:
	virtual __fastcall TMainForm(TComponent *Owner);

	void					ChildNeedSave();
	void					RefreshWorkSpace();

	void					LoadSearchFile(String fileName);

	TMDIChild		*		GetCurWndByWorkSpace(WorkSpace *selWorkSpace);
    void                    ApplyConfig();
};
//----------------------------------------------------------------------------
extern TMainForm *MainForm;
extern TMDIChild *__fastcall MDIChildCreate(void);
//----------------------------------------------------------------------------
#endif    
