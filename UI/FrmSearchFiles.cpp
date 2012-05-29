//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FrmSearchFiles.h"
#include <FileCtrl.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cgauges"
#pragma link "cgauges"
#pragma link "cgauges"
#pragma resource "*.dfm"
TSearchFilesFrm *SearchFilesFrm;
//---------------------------------------------------------------------------
__fastcall TSearchFilesFrm::TSearchFilesFrm(TComponent* Owner)
	: TForm(Owner)
{
	LoadFile = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TSearchFilesFrm::btSelectSearchPathClick(TObject *Sender)
{
	String path;
	if (SelectDirectory(path, TSelectDirOpts(), NULL))
	{
		path += "\\";
		edtSearchPath->Text = path;
	}
}
//---------------------------------------------------------------------------

void  			TSearchFilesFrm::RefreshResult()
{
	ListView_SetItemCountEx(lvResult->Handle, m_FileSearch.GetSearchResult()->Count, LVSICF_NOINVALIDATEALL | LVSICF_NOSCROLL);
	lvResult->Refresh();
}

void __fastcall TSearchFilesFrm::lvResultData(TObject *Sender, TListItem *Item)
{
 	Item->Caption = m_FileSearch.GetSearchResult()->Strings[Item->Index];
}
//---------------------------------------------------------------------------

void __fastcall TSearchFilesFrm::btBeginSearchClick(TObject *Sender)
{

	m_FileSearch.BeginSearch(edtSearchPath->Text, edtFileExt->Text, GetSearchData(), cbInclude->Checked, cgProcess);

	RefreshResult();
}
//---------------------------------------------------------------------------

String			TSearchFilesFrm::GetSearchData()
{
	String data;

	if(cbSearchMode->ItemIndex == 0)
	{
		data = edtSearchContent->Text;
	}
	else if(cbSearchMode->ItemIndex == 1)
	{
		data = BinToStr(edtSearchContent->Text.c_str(), edtSearchContent->Text.Length());
	}
	else if(cbSearchMode->ItemIndex == 2)
	{
		DWORD num = edtSearchContent->Text.ToInt();
		data.SetLength(4);
		int pos = 0;
		WriteDWORD(data.c_str(), pos, num);
		data = BinToStr(data.c_str(), data.Length());
	}
	else if(cbSearchMode->ItemIndex == 3)
	{
		WORD num = edtSearchContent->Text.ToInt();
		data.SetLength(2);
		int pos = 0;
		WriteWORD(data.c_str(), pos, num);
		data = BinToStr(data.c_str(), data.Length());
	}
	else if(cbSearchMode->ItemIndex == 4)
	{
		BYTE num = edtSearchContent->Text.ToInt();
		data.SetLength(1);
		int pos = 0;
		WriteBYTE(data.c_str(), pos, num);
		data = BinToStr(data.c_str(), data.Length());
	}
	return	data;
}

//---------------------------------------------------------------------------
void __fastcall TSearchFilesFrm::btResearchClick(TObject *Sender)
{
	m_FileSearch.ReSearch(GetSearchData());
	RefreshResult();
}
//---------------------------------------------------------------------------

void __fastcall TSearchFilesFrm::nLoadFileClick(TObject *Sender)
{
	if(lvResult->ItemIndex < 0)
		return;
	if(LoadFile)
	{
		LoadFile(m_FileSearch.GetSearchResult()->Strings[lvResult->ItemIndex]);
	}	
}
//---------------------------------------------------------------------------

