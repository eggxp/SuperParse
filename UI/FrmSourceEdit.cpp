//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FrmSourceEdit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSourceEditFrm *SourceEditFrm;
//---------------------------------------------------------------------------
__fastcall TSourceEditFrm::TSourceEditFrm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

int			TSourceEditFrm::EditSource(WorkSpace	*workSpace, IClassManager	*	curClass, String modeName, bool viewMode)
{
	m_IClassManager = curClass;
    m_WorkSpace = workSpace;
	m_SourceGen.GenSource(workSpace, modeName, curClass, memSrcFile->Lines);
	pcSourceMod->TabIndex = 0;
    btOk->Visible = true;
	if(viewMode)
	{
		panControl->Visible = false;
	}
	else
	{
		panControl->Visible = true;
	}
	if(this->ShowModal() == mrOk)
	{
		return	1;
	}
	return 0;
}
void __fastcall TSourceEditFrm::pcSourceModChange(TObject *Sender)
{
    if(pcSourceMod->TabIndex != 0)
    {
        btOk->Visible = false;
    }
    else
        btOk->Visible = true;
	String modName;
	switch(pcSourceMod->TabIndex)
	{
		case	0:
			modName = gBasicSrc;
			break;
		case	1:
			modName = gReadDataSrc;
			break;
		case	2:
			modName = gWriteBufferSrc;
			break;
		case	3:
			modName = gDataInterfaceSrc;
			break;
		case	4:
			modName = gAllReadWriteSrc;
			break;
		case	5:
			modName = gADOStoreSrc;
			break;
        case    6:
            modName = gADOCreate;
            break;
        case    7:
            modName = gADOStoreLoad;
            break;
        case    8:
            modName = gADOStoreSave; 
            break;
        case    9:
            modName = gADOStoreInsert;
            break;
        case    10:
            modName = gADOStoreQueryAll;
            break;
	}

	if(modName != "")
	{
		m_SourceGen.GenSource(m_WorkSpace, modName, m_IClassManager, memSrcFile->Lines);
	}
}
//---------------------------------------------------------------------------


void __fastcall TSourceEditFrm::memSrcFileKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if ((Key == 'A' || Key == 'a') && (Shift.Contains(ssCtrl)))
    {
        memSrcFile->SelectAll();
        Key = 0;
    }
    else if(Key == 0xD && Shift.Contains(ssCtrl))
    {
        if(btOk->Visible)
        {
            Key = 0;
            this->ModalResult = mrOk;
        }
    }
}
//---------------------------------------------------------------------------

