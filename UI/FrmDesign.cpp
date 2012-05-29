//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FrmDesign.h"
#include "FrmSourceGenDesign.h"
#include "ScriptLoader.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDesignFrm *DesignFrm;
//---------------------------------------------------------------------------
__fastcall TDesignFrm::TDesignFrm(TComponent* Owner)
    : TForm(Owner)
{
    m_bModified = false;
    m_UpDating = false;
}
//---------------------------------------------------------------------------

void        TDesignFrm::EditWorkSpace(WorkSpaceManager  *   workSpaceManager)
{
    m_LastMovePackHead = NULL;
    m_WorkSpaceManager = workSpaceManager;
    WorkspaceToGUI();
    this->ShowModal();
    DoSave();
}

void        TDesignFrm::WorkspaceToGUI()
{
    if(m_UpDating)
        return;

	m_WorkSpaceManager->ReloadWorkSpacePack();
    String  curKey = vleHeadDef->Keys[vleHeadDef->Row];
    vleHeadDef->Strings->Clear();
    String  describe;
    for(int i=0; i<m_WorkSpaceManager->GetWorkSpacePacks()->GetWorkPacks()->Count(); i++)
    {
        describe = m_WorkSpaceManager->GetWorkSpacePacks()->GetWorkPacks()->At(i)->m_Describe;
        if(describe == "")
            describe = " ";

        vleHeadDef->InsertRow(m_WorkSpaceManager->GetWorkSpacePacks()->GetWorkPacks()->At(i)->m_Head,
                    describe, true);
	}

	int curSelCell = 0;
	for(int i=0; i<m_WorkSpaceManager->GetWorkSpacePacks()->GetWorkPacks()->Count(); i++)
	{
		if(m_WorkSpaceManager->GetWorkSpacePacks()->GetWorkPacks()->At(i)->m_Head == curKey)
		{
			curSelCell = i;
		}
	}

    vleHeadDef->Row = curSelCell+1;
    RefreshCurClickHead();
	m_WorkSpaceManager->RefreshGUI();
}

void        TDesignFrm::SaveLastSubHead()
{
    if(m_LastMovePackHead)
    {
        //保存
        String key = m_LastMovePackHead->m_Head;

        key = key + " ";
        for(int i=0; i<m_LastMovePackHead->m_Files.Count(); i++)
        {
            m_LastMovePackHead->m_Files[i]->SetComment(
                        key + vleSubHeadDef->Values[m_LastMovePackHead->m_Files[i]->GetFileName()]);
        }
        m_WorkSpaceManager->ReloadWorkSpacePack();
        WorkspaceToGUI();
    }
}


void __fastcall TDesignFrm::btAddHeadDefClick(TObject *Sender)
{
    String  key;
    if(InputQuery("输入标识头(2个字节以内)", "输入标识头(2个字节以内)", key))
    {
        if(key == "")
            return;
        key = key.SubString(1, 2);

        for(int i=0; i<m_WorkSpaceManager->GetWorkSpacePacks()->GetWorkPacks()->Count(); i++)
        {
            if(key == m_WorkSpaceManager->GetWorkSpacePacks()->GetWorkPacks()->At(i)->m_Head)
            {
                ShowMessage(FormatStr("已经有头定义 : %s", key));
                return;
            }
        }

        vleHeadDef->InsertRow(key, "", true);
        vleHeadDef->Row = vleHeadDef->RowCount-1;
        btAddSubHeadClick(Sender);
        SaveAndRefreshClickHead();
    }
}
//---------------------------------------------------------------------------

void __fastcall TDesignFrm::btDefHeadDefClick(TObject *Sender)
{
    SetBeginUpdate();
    int result = Application->MessageBox("这个操作会删除所有的子文件, 是否继续?","删除询问",MB_OKCANCEL);
    if(result == IDCANCEL)
    {
        return;
    }

    String  key = vleHeadDef->Keys[vleHeadDef->Row];
    WorkPackHead * curWorkPackHead = m_WorkSpaceManager->GetWorkSpacePacks()->FindWorkPack(key);

    if(curWorkPackHead == NULL)
        return;

    m_WorkSpaceManager->BeginUpdate();
    for(int i=curWorkPackHead->m_Files.Count()-1; i>=0; i--)
    {
        m_WorkSpaceManager->DeleteWorkSpace(curWorkPackHead->m_Files[i]);
    }
    m_WorkSpaceManager->EndUpdate();

    SetEndUpDate();  
}
//---------------------------------------------------------------------------

void __fastcall TDesignFrm::btClearHeadDefClick(TObject *Sender)
{
    int result = Application->MessageBox("这个清空动作会清空所有文件!  是否继续?","删除询问",MB_OKCANCEL);
    if(result == IDCANCEL)
    {
        return;
    }

    m_WorkSpaceManager->BeginUpdate();
    for(int i=m_WorkSpaceManager->GetWorkSpaceCount()-1; i>=0; i--)
    {
        m_WorkSpaceManager->DeleteWorkSpace(i);
    }


    //添加一条新数据
    String  head = IntToHex(0, 2);
    String  subHead = IntToHex(0, 2);
    String  fileName = FormatStr("Pack_%s_%s.eggxp", head, subHead);
    WorkSpace	*  selWorkSpace = m_WorkSpaceManager->CreateNewWorkSpace();
    selWorkSpace->InitWorkSpace(m_WorkSpaceManager->GetFilePath(),
				fileName, head);

	selWorkSpace->GetFileManager()->CreateNew();
	selWorkSpace->SaveToFile();

	m_WorkSpaceManager->ReloadWorkSpacePack();

	WorkspaceToGUI();
	m_WorkSpaceManager->EndUpdate();
}
//---------------------------------------------------------------------------

void __fastcall TDesignFrm::btAddSubHeadClick(TObject *Sender)
{
    String  key = vleHeadDef->Keys[vleHeadDef->Row];
    if(key == "")
    {
        ShowMessage("请先选择封包头!");
        return;
    }

    String  fileName;
    if(InputQuery("输入文件名(不加后缀)", "输入文件名(不加后缀)", fileName))
    {
        if(fileName == "")
            return;

        if(fileName.AnsiPos("."))
            fileName = LeftString(fileName, ".");
        fileName += ".eggxp";

        WorkSpace	*  selWorkSpace = m_WorkSpaceManager->CreateNewWorkSpace();
        selWorkSpace->InitWorkSpace(m_WorkSpaceManager->GetFilePath(),
                    fileName, key);
        selWorkSpace->SaveToFile();
        m_WorkSpaceManager->ReloadWorkSpacePack();
        WorkspaceToGUI();
    }
}

//---------------------------------------------------------------------------


void __fastcall TDesignFrm::btSaveRefreshClick(TObject *Sender)
{
    SetBeginUpdate();
    DoSave();
    SetEndUpDate();
}
//---------------------------------------------------------------------------

void        TDesignFrm::SetBeginUpdate()
{
    m_UpDating = true;
}

void        TDesignFrm::SetEndUpDate()
{
    if(m_UpDating)
    {
        m_UpDating = false;
        WorkspaceToGUI();
    }
}

void        TDesignFrm::DoSave()
{
    for(int i=0; i<m_WorkSpaceManager->GetWorkSpacePacks()->GetWorkPacks()->Count(); i++)
    {
        m_WorkSpaceManager->GetWorkSpacePacks()->GetWorkPacks()->At(i)->m_Describe =
                                        vleHeadDef->Values[m_WorkSpaceManager->GetWorkSpacePacks()->GetWorkPacks()->At(i)->m_Head];
    }
    SaveLastSubHead();
}

void        TDesignFrm::RefreshCurClickHead()
{
    vleSubHeadDef->Strings->BeginUpdate();
    vleSubHeadDef->Strings->Clear();
    int ARow = vleHeadDef->Row;
    gbSubPack->Caption = FormatStr("封包子定义    <%s>", vleHeadDef->Keys[ARow]);
    WorkPackHead * curWorkPackHead = m_WorkSpaceManager->GetWorkSpacePacks()->FindWorkPack(vleHeadDef->Keys[ARow]);
    m_LastMovePackHead = curWorkPackHead;

    if(curWorkPackHead == NULL)
        return;
    String comment;
    for(int i=0; i<curWorkPackHead->m_Files.Count(); i++)
    {
        comment = curWorkPackHead->m_Files[i]->GetComment();
        comment.Delete(1, 2);
        comment = comment.TrimLeft();
        vleSubHeadDef->InsertRow(curWorkPackHead->m_Files[i]->GetFileName(),
                    comment, true);
    }
    vleSubHeadDef->Strings->EndUpdate();
}
//---------------------------------------------------------------------------


void __fastcall TDesignFrm::vleHeadDefMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    SaveAndRefreshClickHead();
}
//---------------------------------------------------------------------------

void        TDesignFrm::SaveAndRefreshClickHead()
{
    if(m_bModified)
    {
        SaveLastSubHead();
        m_bModified = false;
    }
    RefreshCurClickHead();
}

void __fastcall TDesignFrm::btDeleteSubHeadClick(TObject *Sender)
{
    String fileName = vleSubHeadDef->Keys[vleSubHeadDef->Row];

    int result = Application->MessageBox(FormatStr("当真要删除文件 : %s(此操作不可恢复)", fileName).c_str(),"删除询问",MB_OKCANCEL);
    if(result == IDCANCEL)
    {
        return;
    }

    WorkPackHead * curWorkPackHead = m_WorkSpaceManager->GetWorkSpacePacks()->FindWorkPack(vleHeadDef->Keys[vleHeadDef->Row]);

    if(curWorkPackHead == NULL)
        return;

    WorkSpace	*  selWorkSpace;
    for(int i=0; i<curWorkPackHead->m_Files.Count(); i++)
    {
        if(curWorkPackHead->m_Files[i]->GetFileName() == fileName)
        {
            selWorkSpace = curWorkPackHead->m_Files[i];
            break;
        }
    }
    m_WorkSpaceManager->DeleteWorkSpace(selWorkSpace);
    m_WorkSpaceManager->ReloadWorkSpacePack();
    WorkspaceToGUI();
}
//---------------------------------------------------------------------------


void __fastcall TDesignFrm::btStartNewClick(TObject *Sender)
{
    if(SourceGenDesignFrm->StartDesign() == false)
        return;

    String  fileName, head, subHead;
    m_WorkSpaceManager->BeginUpdate();
    for(int i=0; i<SourceGenDesignFrm->GetHeadCount(); i++)
    {
        for(int j=0; j<SourceGenDesignFrm->GetSubHeadCount(); j++)
        {
            head = IntToHex(i+1, 2);
            subHead = IntToHex(j+1, 2);
            fileName = FormatStr("Pack_%s_%s.eggxp", head, subHead);
            WorkSpace	*  selWorkSpace = m_WorkSpaceManager->CreateNewWorkSpace();
            selWorkSpace->InitWorkSpace(m_WorkSpaceManager->GetFilePath(),
						fileName, head + " " + subHead);

			selWorkSpace->GetFileManager()->CreateNew();
            selWorkSpace->SaveToFile();            
        }
    }

    m_WorkSpaceManager->ReloadWorkSpacePack();
    WorkspaceToGUI();
    m_WorkSpaceManager->EndUpdate();
}
//---------------------------------------------------------------------------

void __fastcall TDesignFrm::vleSubHeadDefKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    m_bModified = true;    
}
//---------------------------------------------------------------------------

void __fastcall TDesignFrm::btOutputSourceClick(TObject *Sender)
{
    if(SaveDialog1->Execute())
    {
        GetWriteStr()->Clear();
        GetScriptLoader()->GetPythonScript()->RunFunc(GetSrcModPath() + "ServerPacket.py",
                                                "GenSrc");
        GetWriteStr()->SaveToFile(SaveDialog1->FileName);
    }
}
//---------------------------------------------------------------------------

