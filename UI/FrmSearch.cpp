//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FrmSearch.h"
#include "SPCommon.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSearchFrm *SearchFrm;
//---------------------------------------------------------------------------
__fastcall TSearchFrm::TSearchFrm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

String      TSearchFrm::GetSearchResult()
{
    String result;
    if(this->ShowModal() == mrOk)
    {
        if(cbSearchMode->ItemIndex == 0)
        {
            result = edtSearchContent->Text;
        }
        else
        {
            result = BinToStr(edtSearchContent->Text.c_str(), edtSearchContent->Text.Length());
        }
        return  result;
    }
    return "";
}
