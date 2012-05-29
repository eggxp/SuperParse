//---------------------------------------------------------------------------

#include <vcl.h>
#include <FileCtrl.hpp>
#pragma hdrstop

#include "FrmSourceGenDesign.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSourceGenDesignFrm *SourceGenDesignFrm;
//---------------------------------------------------------------------------
__fastcall TSourceGenDesignFrm::TSourceGenDesignFrm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSourceGenDesignFrm::btOkClick(TObject *Sender)
{

    if(edtHeadPackCount->Text.ToIntDef(0) == 0)
    {
        ShowMessage("���ͷ������Ŀ����Ϊ��");
        return;
    }

    if(edtSubHeadCount->Text.ToIntDef(0) == 0)
    {
        ShowMessage("�����������Ŀ����Ϊ��");
        return;
    }


    this->ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TSourceGenDesignFrm::btCancelClick(TObject *Sender)
{
    this->ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

bool        TSourceGenDesignFrm::StartDesign()
{
    if(ShowModal() == mrOk)
    {
        return  true;
    }
    return false;
}
