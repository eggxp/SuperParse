//---------------------------------------------------------------------------

#ifndef FrmSourceEditH
#define FrmSourceEditH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "ISourceData.h"
#include "SourceGen.h"
#include <ComCtrls.hpp>
#include "WorkSpaceManager.h"
//---------------------------------------------------------------------------
class TSourceEditFrm : public TForm
{
__published:	// IDE-managed Components
	TPanel *panControl;
	TMemo *memSrcFile;
	TButton *btOk;
	TButton *btCancel;
	TTabControl *pcSourceMod;
	TMemo *Memo1;
	void __fastcall pcSourceModChange(TObject *Sender);
    void __fastcall memSrcFileKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
	SourceGen		m_SourceGen;
	IClassManager	*m_IClassManager;
    WorkSpace	*    m_WorkSpace;
public:		// User declarations
	__fastcall TSourceEditFrm(TComponent* Owner);

	int			EditSource(WorkSpace	*workSpace, IClassManager	*	curClass, String modeName, bool viewMode);
};
//---------------------------------------------------------------------------
extern PACKAGE TSourceEditFrm *SourceEditFrm;
//---------------------------------------------------------------------------
#endif
