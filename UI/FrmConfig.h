//---------------------------------------------------------------------------

#ifndef FrmConfigH
#define FrmConfigH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "cspin.h"
//---------------------------------------------------------------------------
class TConfigFrm : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *edtCharset;
	TButton *btOk;
	TButton *btCancel;
	TCSpinEdit *edtCharsetSize;
	TCheckBox *cbUseDefSetup;
    void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TConfigFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TConfigFrm *ConfigFrm;
//---------------------------------------------------------------------------
#endif
