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
	String content_text = edtSearchContent->Text;
	if(this->ShowModal() == mrOk)
	{
		if(cbSearchMode->ItemIndex == 0)
		{
			result = content_text;
		}
		else
		{
			result = BinToStr(AnsiString(content_text).c_str(), content_text.Length());
        }
        return  result;
    }
    return "";
}
