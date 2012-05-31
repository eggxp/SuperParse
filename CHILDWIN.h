//----------------------------------------------------------------------------
#ifndef ChildWinH
#define ChildWinH
//----------------------------------------------------------------------------
#include <Controls.hpp>
#include <Forms.hpp>
#include <Graphics.hpp>
#include <Classes.hpp>
#include <Windows.hpp>
#include <System.hpp>
#include <StdCtrls.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ActnList.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
#include <Tabs.hpp>
#include <Dialogs.hpp>
#include "WorkSpaceManager.h"
#include "SourceGen.h"
#include "IParseEngine.h"
#include "SourceLoader.h"
#include "cspin.h"
#include "ColorAppend.h"
#include "SearchTool.h"
#include "dcrHexEditor.hpp"
#include <stack>
#include <vcl\Clipbrd.hpp>
using namespace std;

class	ParseTree;

struct	tagSelRect
{
	int	SelStart;
	int	SelLength;
};


struct  tagExePlugins
{
	String          Name;
	String          ClassName;
    String          ExeName;
    int             RecvType;
};

typedef		void (__closure	*TNeedSaveReq)();
typedef		void (__closure	*TRefreshWorkSpaceReq)();


//----------------------------------------------------------------------------
class TMDIChild : public TForm
{
__published:
	TPanel *Panel1;
	TListView *lvFastView;
	TPanel *Panel2;
	TPanel *Panel3;
	TToolBar *ToolBar1;
	TToolButton *ToolButton1;
	TToolButton *ToolButton2;
	TActionList *ActionList1;
	TImageList *ImageList1;
	TAction *actFastParse;
	TAction *actInsertMode;
	TAction *actGoTo;
	TPanel *Panel4;
	TStatusBar *sbState;
	TAction *actDoXor;
	TToolButton *ToolButton6;
	TPopupMenu *pmLanguage;
	TAction *actSetToBIG5;
	TAction *actSetToGB;
	TAction *actSetToUTF8;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *UTF81;
	TAction *actCopyAsHexStr;
	TAction *actCopyAsBin;
	TAction *actCopyAsList;
	TToolButton *ToolButton10;
	TAction *actParseAsList;
	TSplitter *Splitter1;
	TToolButton *ToolButton4;
	TToolButton *ToolButton5;
	TAction *actOpenFile;
	TAction *actSaveFile;
	TSplitter *Splitter2;
	TToolButton *ToolButton8;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTreeView *tvParseTree;
	TAction *actChoose;
	TPopupMenu *pmHex;
	TMenuItem *N5;
	TMenuItem *Bin4;
	TMenuItem *N162;
	TMenuItem *N7;
	TOpenDialog *OpenDialog1;
	TPanel *Panel5;
	TListView *lvWorkSpace;
	TMemo *memInfo;
	TSplitter *Splitter3;
	TSplitter *Splitter4;
	TMemo *memWatch;
	TAction *actSetViewMode;
	TListView *lvAllClasses;
	TSplitter *Splitter5;
	TPopupMenu *pmEditSource;
	TAction *actEditSource;
	TMenuItem *N4;
	TAction *actDelSelect;
	TMenuItem *N8;
	TMenuItem *N9;
	TToolButton *ToolButton9;
	TPopupMenu *pmEdit;
	TMenuItem *N10;
	TMenuItem *N11;
	TMenuItem *N12;
	TMenuItem *N13;
	TMenuItem *N14;
	TAction *actColorAppend;
	TPanel *Panel6;
	TButton *Button1;
	TButton *Button2;
	TLabel *Label1;
	TAction *actGoToNext;
	TAction *actGoToPrev;
	TCSpinEdit *edtCurParseCount;
	TAction *actGoToNum;
	TMenuItem *N1;
	TMenuItem *a1;
	TMenuItem *N15;
	TAction *actChangeFileDescribe;
	TPopupMenu *pmFileDescribe;
	TMenuItem *N16;
	TLabel *labFastParse;
	TPopupMenu *pmFastParse;
	TAction *actDelCurNode;
	TAction *actReNameCurNode;
	TPopupMenu *pmParseTree;
	TMenuItem *N17;
	TMenuItem *N18;
	TMenuItem *N19;
	TMenuItem *N20;
	TAction *actOutputSource;
	TAction *actSetToUnicode;
	TMenuItem *Unicode1;
	TAction *actNewVersion;
	TMenuItem *N6;
	TAction *actDelVersion;
	TMenuItem *N21;
	TAction *actFileSaveAs;
	TSaveDialog *SaveDialog1;
	TMenuItem *N22;
	TAction *actReNameStruct;
	TMenuItem *N26;
    TAction *actFind;
    TMenuItem *N27;
    TAction *actChangeComment;
    TMenuItem *N28;
    TToolButton *ToolButton3;
    TPopupMenu *pmExePlug;
    TAction *actOpenNet;
    TAction *actSendToNetTest;
    TMenuItem *N30;
    TMenuItem *miSendTo;
    TAction *actWrite;
    TMenuItem *N29;
    TMenuItem *N31;
	TPopupMenu *pmImport;
	TMenuItem *N32;
	TAction *actOpenListFromTxt;
	TMenuItem *txt1;
	TMPHexEditor *m_HexEditor;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall actOpenFileExecute(TObject *Sender);
	void __fastcall actInsertModeExecute(TObject *Sender);
	void __fastcall actGoToExecute(TObject *Sender);
	void __fastcall actChooseExecute(TObject *Sender);
	void __fastcall actSetViewModeExecute(TObject *Sender);
	void __fastcall actDoXorExecute(TObject *Sender);
	void __fastcall actSaveFileExecute(TObject *Sender);
	void __fastcall m_HexEditorChange(TObject *Sender);
	void __fastcall actSetToBIG5Execute(TObject *Sender);
	void __fastcall actSetToGBExecute(TObject *Sender);
	void __fastcall lvAllClassesData(TObject *Sender, TListItem *Item);
	void __fastcall lvAllClassesClick(TObject *Sender);
	void __fastcall m_HexEditorDrawCell(TObject *Sender, TCanvas *ACanvas,
          int ACol, int ARow, WideString &AWideText, TRect &ARect,
          bool &ADefaultDraw);
	void __fastcall tvParseTreeClick(TObject *Sender);
	void __fastcall lvFastViewData(TObject *Sender, TListItem *Item);
	void __fastcall pmLanguagePopup(TObject *Sender);
	void __fastcall actSetToUTF8Execute(TObject *Sender);
	void __fastcall tvParseTreeExpanding(TObject *Sender, TTreeNode *Node,
          bool &AllowExpansion);
	void __fastcall actEditSourceExecute(TObject *Sender);
	void __fastcall actDelSelectExecute(TObject *Sender);
	void __fastcall m_HexEditorMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
	void __fastcall m_HexEditorMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall m_HexEditorMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall actColorAppendExecute(TObject *Sender);
	void __fastcall actGoToNextExecute(TObject *Sender);
	void __fastcall actGoToPrevExecute(TObject *Sender);
	void __fastcall actGoToNumExecute(TObject *Sender);
	void __fastcall actChangeFileDescribeExecute(TObject *Sender);
	void __fastcall actFastParseExecute(TObject *Sender);
	void __fastcall pmFastParsePopup(TObject *Sender);
	void __fastcall actDelCurNodeExecute(TObject *Sender);
	void __fastcall actReNameCurNodeExecute(TObject *Sender);
	void __fastcall actOutputSourceExecute(TObject *Sender);
	void __fastcall actParseAsListExecute(TObject *Sender);
	void __fastcall actCopyAsBinExecute(TObject *Sender);
	void __fastcall actCopyAsHexStrExecute(TObject *Sender);
	void __fastcall actCopyAsListExecute(TObject *Sender);
	void __fastcall actSetToUnicodeExecute(TObject *Sender);
	void __fastcall actNewVersionExecute(TObject *Sender);
	void __fastcall actDelVersionExecute(TObject *Sender);
	void __fastcall lvWorkSpaceClick(TObject *Sender);
	void __fastcall pmFileDescribePopup(TObject *Sender);
	void __fastcall actFileSaveAsExecute(TObject *Sender);
	void __fastcall actCopyFastViewExecute(TObject *Sender);
	void __fastcall actReNameStructExecute(TObject *Sender);
    void __fastcall actFindExecute(TObject *Sender);
    void __fastcall actChangeCommentExecute(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall actWriteExecute(TObject *Sender);
	void __fastcall m_HexEditorClick(TObject *Sender);
	void __fastcall m_HexEditorKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall actOpenListFromTxtExecute(TObject *Sender);
    void __fastcall FormActivate(TObject *Sender);


private:
    int             m_LastPos;
	bool			m_LMouseDown;

	WorkSpace	*	m_WorkSpace;
	FileStruct	*	m_ActiveFileStruct;
	ParseTree	 *	m_ParseTree;
	IParseEngine	*m_ParseEngine;

	SourceLoader	m_SourceLoader;
	ColorAppender	m_ColorAppender;

	stack<int>		m_ParseListHistory;
	void			ClearListHistory();


	void			RefreshAllClassView();
	void			LoadCurWork();
	void			RefreshStateBar();
	void			CheckModify();
	void			SetModify();

	bool			IsCurPosInTreeSelection(int pos);
	bool			GetTreeSelRect(tagSelRect & selRect);

	void			RefreshFastView();
	void			ParseData(bool gotoPos = true);

	void			SetFileDescribe(FileStruct * curFile);

	void			SetSelectDetail();
	//快速翻译模式
	bool			m_bFastParseMode;
	int				m_FastParsePos;

	void			ExpandFirstNode();
	void 			AddFastParseMenu(String Caption, int tag = 0);
	void			MakeFastParseMenu();
	void __fastcall FastParseExecute(TObject *Sender);
	ClassData	*	GetCurParseClass();
	int				GetCurParseClassIndex();

	void			ChangeNodeName(ParseTreeNode * parseTreeNode, bool needRefresh = true, int changeType=0);   //0:改名 1:改注释
	void			DeleteCurClass();

	bool			m_bTreeModify;

	bool			m_bShowCharacter;
	int				m_CharacterShowState;
    CSearchEngine   m_SearchEngine;

    AList<tagExePlugins>    *   m_Plugins;
    void                        InitPlugins();
    void __fastcall actOpenPluginExecute(TObject *Sender);
	void __fastcall actSendToPluginTestExecute(TObject *Sender);
	void			GotoPosition(int pos);

public:
	virtual __fastcall TMDIChild(TComponent *Owner);
	TTabSet * MainTabSet;

	void		InitFrm(WorkSpace	*	workSpace, IParseEngine * engine);
	WorkSpace	*	GetWorkSpace(){return	m_WorkSpace;}

	TNeedSaveReq				NeedSaveReq;
	TRefreshWorkSpaceReq		RefreshWorkSpaceReq;

	int				GetIndexInMainTab();
	void			DoBringToFront();
	void			DoSetTabCaption();
	void			LoadFromFile(String fileName);
    void            SetPlugins(AList<tagExePlugins> *   plugins);
};
//----------------------------------------------------------------------------
#endif
