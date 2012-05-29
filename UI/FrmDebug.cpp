//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FrmDebug.h"
#include "ScriptLoader.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDebugFrm *DebugFrm;
//---------------------------------------------------------------------------
__fastcall TDebugFrm::TDebugFrm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void        TDebugFrm::OnError(String err)
{
    MemoDebug->Lines->Add(err);
}
void __fastcall TDebugFrm::Button1Click(TObject *Sender)
{
    GetScriptLoader()->GetPythonScript()->RunFunc(GetSrcModPath() + "ServerPacket.py",
                                                "GenSrc");

	MemoDebug->Lines->BeginUpdate();
	MemoDebug->Lines->Add("==================================================");
	MemoDebug->Lines->AddStrings(GetWriteStr());
	MemoDebug->Lines->EndUpdate();
}
//---------------------------------------------------------------------------

void __fastcall TDebugFrm::FormCreate(TObject *Sender)
{
    GetScriptLoader()->GetPythonScript()->fpPythonError = OnError;
    //³õÊ¼»¯½Å±¾
    GetScriptLoader()->GetPythonScript()->LoadFromFile(GetSrcModPath() + "ServerPacket.py");
}
//---------------------------------------------------------------------------

