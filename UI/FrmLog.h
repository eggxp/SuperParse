//---------------------------------------------------------------------------

#ifndef FrmLogH
#define FrmLogH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TLogFrm : public TForm
{
__published:	// IDE-managed Components
	TMemo *memLog;
private:	// User declarations
public:		// User declarations
	__fastcall TLogFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLogFrm *LogFrm;
//---------------------------------------------------------------------------
#endif
