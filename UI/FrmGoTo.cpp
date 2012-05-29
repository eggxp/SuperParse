//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FrmGoTo.h"
#include "SPCommon.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGoToFrm *GoToFrm;
//---------------------------------------------------------------------------
__fastcall TGoToFrm::TGoToFrm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

int			TGoToFrm::Goto(int	curPosition)
{
	edtCurOffset->Text = GetHexAndIntString(curPosition);
	
	if(this->ShowModal() == mrOk)
	{
		int jmpPos = edtJumpOffset->Text.ToIntDef(0);

		if(rbFrmCurPosition->Checked)
			return	jmpPos + curPosition;
		else
			return	jmpPos;
	}
	return -1;
}

