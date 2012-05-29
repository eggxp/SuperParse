//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FrmEditFileDescribe.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEditFileDescribeFrm *EditFileDescribeFrm;
//---------------------------------------------------------------------------
__fastcall TEditFileDescribeFrm::TEditFileDescribeFrm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void		TEditFileDescribeFrm::EditFileStructDescribe(FileStruct	*	curFileStruct)
{
	m_FileStruct = curFileStruct;

	edtFileDescribe->Text = m_FileStruct->GetDescribe();
	edtCreateDate->Text = m_FileStruct->GetDateTime();
	memRemark->Text = m_FileStruct->GetRemark();
	edtKey->Text = IntToStr(m_FileStruct->GetKey());

	if(this->ShowModal() == mrOk)
	{
		m_FileStruct->SetDescribe(edtFileDescribe->Text);
		m_FileStruct->SetDateTime(edtCreateDate->Text);
		m_FileStruct->SetRemark(memRemark->Text);
		m_FileStruct->SetKey(edtKey->Text.ToIntDef(0));
	}
}

void __fastcall TEditFileDescribeFrm::btResetTimeClick(TObject *Sender)
{
  	edtCreateDate->Text = SPGetCurrentTime();
}
//---------------------------------------------------------------------------


