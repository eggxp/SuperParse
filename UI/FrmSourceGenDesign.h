//---------------------------------------------------------------------------

#ifndef FrmSourceGenDesignH
#define FrmSourceGenDesignH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TSourceGenDesignFrm : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TLabel *Label2;
    TEdit *edtHeadPackCount;
    TEdit *edtSubHeadCount;
    TButton *btOk;
    TButton *btCancel;
    TLabel *Label3;
    void __fastcall btOkClick(TObject *Sender);
    void __fastcall btCancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TSourceGenDesignFrm(TComponent* Owner);

    bool        StartDesign();

    int         GetHeadCount(){return   edtHeadPackCount->Text.ToIntDef(0);}
    int         GetSubHeadCount(){return   edtSubHeadCount->Text.ToIntDef(0);}
};
//---------------------------------------------------------------------------
extern PACKAGE TSourceGenDesignFrm *SourceGenDesignFrm;
//---------------------------------------------------------------------------
#endif
