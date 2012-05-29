//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FrmSetup.h"
#include "SPCommon.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSetupFrm *SetupFrm;
//---------------------------------------------------------------------------
__fastcall TSetupFrm::TSetupFrm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSetupFrm::cbLanguageChange(TObject *Sender)
{
	switch(cbLanguage->ItemIndex)
	{
		case	0:
			SetLangModule(lmBIG5);
			break;
		case	1:
			SetLangModule(lmGB);
			break;
		case	2:
			SetLangModule(lmUTF8);
			break;
		case	3:
			SetLangModule(lmUnicode);
			break;
	}
}
//---------------------------------------------------------------------------
