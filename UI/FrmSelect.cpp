//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FrmSelect.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSelectFrm *SelectFrm;
//---------------------------------------------------------------------------
__fastcall TSelectFrm::TSelectFrm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

int			TSelectFrm::Select(int	&curPosition)
{
	edtCurOffset->Text = GetHexAndIntString(curPosition);

	if(this->ShowModal() == mrOk)
	{
		int area = edtJumpOffset->Text.ToIntDef(0);

		if(rbFrmCurPosition->Checked == false)
			curPosition = 0;
		return	area;
	}
	return 0;
}
