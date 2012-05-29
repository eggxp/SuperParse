//---------------------------------------------------------------------------

#ifndef FrmDesignH
#define FrmDesignH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <ExtCtrls.hpp>
#include "WorkSpaceManager.h"
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TDesignFrm : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *GroupBox1;
    TValueListEditor *vleHeadDef;
    TPanel *Panel1;
    TButton *btAddHeadDef;
    TButton *btDefHeadDef;
    TButton *btClearHeadDef;
    TGroupBox *gbSubPack;
    TValueListEditor *vleSubHeadDef;
    TPanel *Panel2;
    TButton *btAddSubHead;
    TSplitter *Splitter1;
    TButton *btSaveRefresh;
    TButton *btDeleteSubHead;
    TButton *btStartNew;
    TButton *btOutputSource;
    TSaveDialog *SaveDialog1;
    TMemo *Memo1;
    void __fastcall btAddSubHeadClick(TObject *Sender);
    void __fastcall btAddHeadDefClick(TObject *Sender);
    void __fastcall btDefHeadDefClick(TObject *Sender);
    void __fastcall btClearHeadDefClick(TObject *Sender);
    void __fastcall btSaveRefreshClick(TObject *Sender);
    void __fastcall vleHeadDefMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall btDeleteSubHeadClick(TObject *Sender);
    void __fastcall btStartNewClick(TObject *Sender);
    void __fastcall vleSubHeadDefKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall btOutputSourceClick(TObject *Sender);
private:	// User declarations
    WorkSpaceManager        *       m_WorkSpaceManager;
    WorkPackHead            *       m_LastMovePackHead;

    bool        m_UpDating;
    bool        m_bModified;
    void        WorkspaceToGUI();
    void        DoSave();
    void        SaveLastSubHead();

    void        RefreshCurClickHead();
    void        SaveAndRefreshClickHead();

    void        SetBeginUpdate();
    void        SetEndUpDate();
public:		// User declarations
    __fastcall TDesignFrm(TComponent* Owner);
    void        EditWorkSpace(WorkSpaceManager  *   workSpaceManager);
};
//---------------------------------------------------------------------------
extern PACKAGE TDesignFrm *DesignFrm;
//---------------------------------------------------------------------------
#endif
