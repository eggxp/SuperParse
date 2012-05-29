//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FrmConfig.h"
#include "SPCommon.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cspin"
#pragma resource "*.dfm"
TConfigFrm *ConfigFrm;
//---------------------------------------------------------------------------
__fastcall TConfigFrm::TConfigFrm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TConfigFrm::FormCreate(TObject *Sender)
{
    //³õÊ¼»¯ÅäÖÃ
    GetConfig()->SetRecordName("Charset");
    GetConfig()->AddOptionRecord(edtCharset);
    GetConfig()->AddOptionRecord(edtCharsetSize);
	GetConfig()->AddOptionRecord(cbUseDefSetup);

    GetConfig()->LoadFromFile(SETUP_INI_FILE, "Charset");

    GetConfig()->Value2GUI();

    MainForm->ApplyConfig();
}
//---------------------------------------------------------------------------


