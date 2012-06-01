//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "test.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dcrHexEditor"
#pragma link "dcrHexEditorEx"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	AnsiString bb = "01 02 03";
	String cc = bb;
	String aa = "01 02 03 04 05";
	TCHAR *c = aa.c_str();
	int a=0;
}
//---------------------------------------------------------------------------

