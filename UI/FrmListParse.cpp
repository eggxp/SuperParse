//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FrmListParse.h"
#include "ParseTree.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cspin"
#pragma link "cgauges"
#pragma resource "*.dfm"
TListParseFrm *ListParseFrm;
//---------------------------------------------------------------------------
__fastcall TListParseFrm::TListParseFrm(TComponent* Owner)
	: TForm(Owner)
{
	m_ParseTree = NULL;
}

//---------------------------------------------------------------------------

void			TListParseFrm::ShowFrm(IParseEngine	*	engine, IClassManager * classManager, IClassData * curClass,
							char * lpData, int dataSize, int parsePos, String savePath)
{
	m_ParseTree = new ParseTree(engine, classManager);
	m_ParseTree->SetParseData(lpData, dataSize);
	m_ParseTree->BindClass(curClass);
	m_FileSize = dataSize;
	m_ParsePos = parsePos;
	m_SavePath = savePath;

	edtParseCount->Value = 0;

	m_TreeToClientData.Init(m_ParseTree, m_FileSize, m_ParsePos);
	m_TreeToClientData.SetColumn();

	lvParseData->Columns->Clear();
	TListColumn * curColumn;

	curColumn = lvParseData->Columns->Add();
	curColumn->Width = 100; 
	curColumn->Caption = "Index";

		
	for(int i=0; i<m_TreeToClientData.GetParseData()->GetColumnCount(); i++)
	{
		curColumn = lvParseData->Columns->Add();
		curColumn->Width = 100; 
		curColumn->Caption = m_TreeToClientData.GetParseData()->GetColumnAt(i);
	}
	RefreshList();
	this->Show();
}

void __fastcall TListParseFrm::FormClose(TObject *Sender, TCloseAction &Action)
{
	delete	m_ParseTree;
	m_ParseTree = NULL;	
}
//---------------------------------------------------------------------------


void __fastcall TListParseFrm::btOutputFileClick(TObject *Sender)
{
	//清空
	cdsData->FieldDefs->Clear();

	if(cdsData->IsEmpty() == false)
	{
		cdsData->EmptyDataSet();
		cdsData->Close();
	}

	//生成列
	TFieldDef * fieldDef;
	fieldDef = cdsData->FieldDefs->AddFieldDef();
	fieldDef->DataType = ftInteger;
	fieldDef->Name = "Index";
	for(int i=0; i<m_TreeToClientData.GetParseData()->GetColumnCount(); i++)
	{
		fieldDef = cdsData->FieldDefs->AddFieldDef();
		fieldDef->DataType = ftString;
		fieldDef->Size = m_TreeToClientData.GetParseData()->GetColumnMaxLength(i);
		fieldDef->Name = m_TreeToClientData.GetParseData()->GetColumnAt(i);
	}

	//填充数据
	cdsData->CreateDataSet();
	cdsData->Open();

	cgProcess->MaxValue = m_TreeToClientData.GetParseData()->GetLineCount();
	for(int i=0; i<m_TreeToClientData.GetParseData()->GetLineCount(); i++)
	{
		cdsData->Append();
		cdsData->Fields->FieldByNumber(1)->AsInteger = i;
		for(int j=0; j<m_TreeToClientData.GetParseData()->GetColumnCount(); j++)
		{
			cdsData->Fields->FieldByNumber(j+2)->AsString = m_TreeToClientData.GetParseData()->At(i, j)->Result;
		}
		cdsData->Post();

		if(i % 10 == 0)
		{
			cgProcess->Progress = i+1;
			Application->ProcessMessages();
		}
	}
	cgProcess->Progress = cgProcess->MaxValue;
}
//---------------------------------------------------------------------------

void __fastcall TListParseFrm::btStartClick(TObject *Sender)
{
	m_TreeToClientData.StartParse(edtParseCount->Value, edtParseCount);
	RefreshList();

	int result = Application->MessageBox(L"是否继续生成XML文件?",L"生成文件",MB_OKCANCEL);
	if(result == IDCANCEL)
	{
		return;
	}
	btOutputFileClick(NULL);
}

//---------------------------------------------------------------------------
void				TListParseFrm::RefreshList()
{                
	lvParseData->Items->Count = m_TreeToClientData.GetParseData()->GetLineCount();
	lvParseData->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TListParseFrm::lvParseDataData(TObject *Sender, TListItem *Item)
{
  	Item->Caption = Item->Index;

	for(int i=0; i<m_TreeToClientData.GetParseData()->GetColumnCount(); i++)
	{
		Item->SubItems->Add(m_TreeToClientData.GetParseData()->At(Item->Index, i)->Result);
	}
}
//---------------------------------------------------------------------------
void __fastcall TListParseFrm::btOutputClick(TObject *Sender)
{
	SaveDialog1->DefaultExt = m_SavePath;
	if(SaveDialog1->Execute())
	{
		cdsData->SaveToFile(SaveDialog1->FileName,dfXML);
	}

	//执行选择的文件
    String execCmd = ExtractFilePath(Application->ExeName) + "xmlist.exe " + "\"" + SaveDialog1->FileName + "\"";
    WinExec(AnsiString(execCmd).c_str(), SW_MAXIMIZE);
}
//---------------------------------------------------------------------------

void __fastcall TListParseFrm::FormCreate(TObject *Sender)
{
	edtParseCount->Value = 0;	
}
//---------------------------------------------------------------------------

