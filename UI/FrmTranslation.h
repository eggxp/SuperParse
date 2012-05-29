//---------------------------------------------------------------------------

#ifndef FrmTranslationH
#define FrmTranslationH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TTranslationFrm : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TComboBox *cbTanslation;
private:	// User declarations
public:		// User declarations
	__fastcall TTranslationFrm(TComponent* Owner);
	int			ShowTranslation(int curTan);
};
//---------------------------------------------------------------------------
extern PACKAGE TTranslationFrm *TranslationFrm;
//---------------------------------------------------------------------------
#endif
