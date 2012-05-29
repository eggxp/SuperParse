//---------------------------------------------------------------------------

#ifndef FrmSelectH
#define FrmSelectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "SPCommon.h"
//---------------------------------------------------------------------------
class TSelectFrm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TEdit *edtJumpOffset;
	TLabel *Label2;
	TEdit *edtCurOffset;
	TPanel *Panel1;
	TRadioButton *rbFrmCurPosition;
	TRadioButton *rbFromStart;
	TLabel *Label3;
	TButton *btOK;
	TButton *btCancel;
private:	// User declarations
public:		// User declarations
	__fastcall TSelectFrm(TComponent* Owner);
	int			Select(int	&curPosition);
};
//---------------------------------------------------------------------------
extern PACKAGE TSelectFrm *SelectFrm;
//---------------------------------------------------------------------------
#endif
