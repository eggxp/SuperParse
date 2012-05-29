//---------------------------------------------------------------------------

#ifndef FrmSearchH
#define FrmSearchH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TSearchFrm : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TEdit *edtSearchContent;
    TComboBox *cbSearchMode;
    TButton *btOk;
    TButton *Button2;
private:	// User declarations
public:		// User declarations
    __fastcall TSearchFrm(TComponent* Owner);
    String      GetSearchResult();
};
//---------------------------------------------------------------------------
extern PACKAGE TSearchFrm *SearchFrm;
//---------------------------------------------------------------------------
#endif
