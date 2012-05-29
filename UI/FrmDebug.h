//---------------------------------------------------------------------------

#ifndef FrmDebugH
#define FrmDebugH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TDebugFrm : public TForm
{
__published:	// IDE-managed Components
    TMemo *MemoDebug;
    TButton *Button1;
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
private:	// User declarations

public:		// User declarations
    __fastcall TDebugFrm(TComponent* Owner);

    void        OnError(String err);    
};
//---------------------------------------------------------------------------
extern PACKAGE TDebugFrm *DebugFrm;
//---------------------------------------------------------------------------
#endif
