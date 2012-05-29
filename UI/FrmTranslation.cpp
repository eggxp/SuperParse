//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FrmTranslation.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTranslationFrm *TranslationFrm;
//---------------------------------------------------------------------------
__fastcall TTranslationFrm::TTranslationFrm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

int			TTranslationFrm::ShowTranslation(int curTan)
{
	cbTanslation->ItemIndex = curTan;
	this->ShowModal();
	return	cbTanslation->ItemIndex;
}
