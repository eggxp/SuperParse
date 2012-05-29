//---------------------------------------------------------------------------

#ifndef FrmSetupH
#define FrmSetupH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TSetupFrm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TComboBox *cbLanguage;
	void __fastcall cbLanguageChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TSetupFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSetupFrm *SetupFrm;
//---------------------------------------------------------------------------
#endif
