//---------------------------------------------------------------------
#include <vcl.h>
#include <Dialogs.hpp>
#pragma hdrstop

#include "ChildWin.h"
#include "FrmGoTo.h"
#include "FrmSelect.h"
#include "FrmTranslation.h"
#include "ParseTree.h"
#include "CountTime.h"
#include "FrmSourceEdit.h"
#include "FrmEditFileDescribe.h"
#include "FrmListParse.h"
#include "FrmSearch.h"
#include "TxtToListLoader.h"
//---------------------------------------------------------------------
#pragma link "cspin"
#pragma link "dcrHexEditor"
#pragma link "dcrHexEditorEx"
#pragma resource "*.dfm"

#define	GRID_FIXED	2

#define EX_PLUGIN_DIR   "ExPlugin\\"

//--------------------------------------------------------------------- 
__fastcall TMDIChild::TMDIChild(TComponent *Owner)
	: TForm(Owner)
{
	MainTabSet = NULL;
	m_WorkSpace = NULL;
	m_ActiveFileStruct = NULL;
	NeedSaveReq = NULL;
	RefreshWorkSpaceReq = NULL;
    m_Plugins = NULL;
}
//---------------------------------------------------------------------

void		TMDIChild::InitFrm(WorkSpace	*	workSpace, IParseEngine * engine)
{
	m_ParseEngine = engine;
	m_WorkSpace = workSpace;
	m_WorkSpace->GetFileManager()->BindView(lvWorkSpace);
	m_bTreeModify = false;
	m_WorkSpace->Open();

	SetModify();
	

	//初始化
	m_ParseTree = new ParseTree(m_ParseEngine, m_WorkSpace->GetClassManager());

	if(lvWorkSpace->Items->Count == 0)
	{
		actNewVersionExecute(NULL);
	}
	else
	{
		lvWorkSpace->ItemIndex = 0;
		LoadCurWork();
	}


	//绑定树控件
	m_ParseTree->BindView(tvParseTree->Items);

	m_bFastParseMode = false;
	m_FastParsePos = 0;

    String      structName = workSpace->GetStructName();
    if(structName != "")
    {
        bool  needAddStruct = true;
        for(int i=0; i<workSpace->GetClassManager()->GetClassCount(); i++)
        {
            if(workSpace->GetClassManager()->GetClassDataByIndex(i)->GetName() == structName)
            {
                needAddStruct = false;
                break;
            }
        }

        if(needAddStruct)
        {
            ClassData *curClass = m_WorkSpace->GetClassManager()->AddClass();
            curClass->Init(structName, workSpace->GetComment());
            int index = m_WorkSpace->GetClassManager()->GetClassIndexByClassData(curClass);
            RefreshAllClassView();
            lvAllClasses->ItemIndex = index;
            lvAllClassesClick(NULL);
        }
    }
}

//---------------------------------------------------------------------
void			TMDIChild::SetFileDescribe(FileStruct * curFile)
{
	memInfo->Lines->Clear();
	memInfo->Lines->Add(FormatStr("描述 : %s", curFile->GetDescribe()));
	String key_str = IntToStr(int(curFile->GetKey()));
	memInfo->Lines->Add(FormatStr("Key : %s", key_str));
	memInfo->Lines->Add(FormatStr("时间 : %s", curFile->GetDateTime()));
	memInfo->Lines->Add(FormatStr("详情 : %s", curFile->GetRemark()));
}
//---------------------------------------------------------------------
void			TMDIChild::LoadCurWork()
{
	if(m_ActiveFileStruct)
	{
		m_ActiveFileStruct->GetMemory()->Clear();
		m_HexEditor->SaveToStream(m_ActiveFileStruct->GetMemory());
	}

	m_ActiveFileStruct = m_WorkSpace->GetFileManager()->GetFileData(lvWorkSpace->ItemIndex);
	if(m_ActiveFileStruct == NULL)
		return;

   	SetFileDescribe(m_ActiveFileStruct);

	m_HexEditor->LoadFromStream(m_ActiveFileStruct->GetMemory());
	
	m_HexEditor->Modified = false;
	RefreshStateBar();
	CheckModify();
	RefreshAllClassView();

	char	*pointer = m_HexEditor->GetFastPointer(0, m_HexEditor->DataSize);
	m_ParseTree->SetParseData(pointer, m_HexEditor->DataSize);
}

//---------------------------------------------------------------------------

void __fastcall TMDIChild::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
	m_WorkSpace->Close();
	if(MainTabSet==NULL)
		return;
	int index = GetIndexInMainTab();
	if(index >= 0)
	{
		MainTabSet->Tabs->Delete(index);
        if(index < MainTabSet->Tabs->Count)
        {
            MainTabSet->TabIndex = index;
        }
        else
            MainTabSet->TabIndex = MainTabSet->Tabs->Count-1;
	}

}
//---------------------------------------------------------------------


void __fastcall TMDIChild::actOpenFileExecute(TObject *Sender)
{
	if(OpenDialog1->Execute())
	{
		if(OpenFileCheck(OpenDialog1->FileName))
			LoadFromFile(OpenDialog1->FileName);
	}
}

//---------------------------------------------------------------------------
void			TMDIChild::LoadFromFile(String fileName)
{
	m_HexEditor->LoadFromFile(fileName);
    SetModify();
}
//---------------------------------------------------------------------------

void			TMDIChild::RefreshStateBar()
{
	String	modeName;
	if(m_HexEditor->InsertMode)
		modeName = "插入";
	else
		modeName = "覆盖";
	sbState->Panels->Items[0]->Text = FormatStr("模式:%s", modeName);

	int iValue = m_HexEditor->SelStart;
	String hexValue = GetHexAndIntString(iValue);
	sbState->Panels->Items[1]->Text = FormatStr("偏移:%s", hexValue, iValue);


	iValue = m_HexEditor->SelCount;
	hexValue = GetHexAndIntString(iValue);
	sbState->Panels->Items[2]->Text = FormatStr("选定大小:%s", hexValue, iValue);

	hexValue = GetHexAndIntString(m_HexEditor->DataSize);
	sbState->Panels->Items[3]->Text = FormatStr("文件大小:%s", hexValue);

	iValue = 0;
	tagSelRect selRect;
	if(GetTreeSelRect(selRect))
	{
		iValue = selRect.SelLength;
	}
	hexValue = GetHexAndIntString(iValue);
	sbState->Panels->Items[4]->Text = FormatStr("选定类型长度:%s", hexValue, iValue);
}

//---------------------------------------------------------------------------

void __fastcall TMDIChild::actInsertModeExecute(TObject *Sender)
{
	if(m_HexEditor->InsertMode)
	{
		m_HexEditor->InsertMode = false;
		actInsertMode->Caption = "插入";
	}
	else
	{
		m_HexEditor->InsertMode = true;
		actInsertMode->Caption = "覆盖";
	}

	RefreshStateBar();
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::actGoToExecute(TObject *Sender)
{
	int pos = GoToFrm->Goto(m_HexEditor->SelStart);
	if(pos < 0)
		return;

	m_HexEditor->SelStart = pos;
	RefreshStateBar();
}
//---------------------------------------------------------------------------


void __fastcall TMDIChild::actChooseExecute(TObject *Sender)
{
	int pos = m_HexEditor->SelStart; 
	int area = SelectFrm->Select(pos);
	
	m_HexEditor->SelStart = pos;
	m_HexEditor->SelCount = area;
	RefreshStateBar();
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::actSetViewModeExecute(TObject *Sender)
{
	m_HexEditor->Translation = (TMPHTranslationKind)TranslationFrm->ShowTranslation(m_HexEditor->Translation);
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::actDoXorExecute(TObject *Sender)
{
	//异或
	String key;
	if(InputQuery("输入Key", "输入Key", key) == false)
		return;

	int keyInt = key.ToIntDef(0);
	
	for(int i=0; i<m_HexEditor->DataSize; i++)
	{
		m_HexEditor->Data[i] = m_HexEditor->Data[i] ^ keyInt;
	}

	CheckModify();
	ParseData();
}
//---------------------------------------------------------------------------

void			TMDIChild::CheckModify()
{
	if(m_HexEditor->Modified || m_bTreeModify)
	{
		actSaveFile->Enabled = true;
	}
	else
		actSaveFile->Enabled = false;
}

void			TMDIChild::SetModify()
{
	m_bTreeModify = true;
	CheckModify();
}

//---------------------------------------------------------------------------

void __fastcall TMDIChild::m_HexEditorChange(TObject *Sender)
{
	m_HexEditor->Modified = true;
	CheckModify();

}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::actSetToBIG5Execute(TObject *Sender)
{
	SetLangModule(lmBIG5);
	ParseData();
}
//---------------------------------------------------------------------------



void __fastcall TMDIChild::actSetToGBExecute(TObject *Sender)
{
	SetLangModule(lmGB);
	ParseData();
}
//---------------------------------------------------------------------------
void			TMDIChild::GotoPosition(int pos)
{
	m_HexEditor->SelStart = pos;
}

void			TMDIChild::ParseData(bool gotoPos)
{
	if(m_ParseTree->GetClassData() == NULL)
		return;
		
	char	*pointer = m_HexEditor->GetFastPointer(0, m_HexEditor->DataSize);
	m_ParseTree->SetParseData(pointer, m_HexEditor->DataSize);
	
	if(m_bFastParseMode)
		m_ParseTree->UnPackData(m_FastParsePos, 1);
	else
		m_ParseTree->UnPackData(m_HexEditor->SelStart, 1);
		
	m_ParseTree->ParseData();
	m_HexEditor->Repaint();

    if(gotoPos)
	{
		if(m_bFastParseMode)
		{
			GotoPosition(m_FastParsePos);
		}
		else
		{
			if(m_HexEditor->SelStart - 1 >= 0)
				GotoPosition(m_HexEditor->SelStart - 1);
		}
    }
}

void __fastcall TMDIChild::lvAllClassesData(TObject *Sender, TListItem *Item)
{
    if(m_WorkSpace->GetClassManager()->GetClassByIndex(Item->Index))
    	Item->Caption = m_WorkSpace->GetClassManager()->GetClassByIndex(Item->Index)->GetName();
    else
    {
        if(Item->Index == 0)
        {
            actNewVersionExecute(Sender);
        }
    }
}
//---------------------------------------------------------------------------

void			TMDIChild::RefreshAllClassView()
{
	lvAllClasses->Items->Count = m_WorkSpace->GetClassManager()->GetClassCount();
	lvAllClasses->Refresh();
}

//---------------------------------------------------------------------------

void __fastcall TMDIChild::lvAllClassesClick(TObject *Sender)
{
	//选中结构体
	if(lvAllClasses->ItemIndex >= 0)
	{
		m_ParseTree->BindClass(m_WorkSpace->GetClassManager()->GetClassByIndex(lvAllClasses->ItemIndex));
		ExpandFirstNode();
		ParseData();
	}
}

//---------------------------------------------------------------------------
void			TMDIChild::ExpandFirstNode()
{
	if(tvParseTree->Items->Count >= 1)
	{
		tvParseTree->Items->Item[0]->Expand(false);
		tvParseTree->Items->Item[0]->Selected = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::m_HexEditorDrawCell(TObject *Sender,
	  TCanvas *ACanvas, int ACol, int ARow, WideString &AWideText, TRect &ARect,
	  bool &ADefaultDraw)
{
	//画图动作
	if(ACol == 0)
	{
		//地址栏
		ADefaultDraw = true;
		return;
	}
	else	if(ACol < GRID_FIXED || ARow < GRID_FIXED)
	{
		//标尺
		return;
	}
	else
	{
		int curCol;
		int Watch_Start_Pos = m_HexEditor->ColCountRO - m_HexEditor->BytesPerRow;
		if(ACol >=  Watch_Start_Pos)
		{
			//右边的观察栏
			curCol = ACol - Watch_Start_Pos;
		}
		else
		{
			curCol = (ACol - GRID_FIXED)/2;
		}
		int drawPos = curCol + (ARow - GRID_FIXED) * m_HexEditor->BytesPerRow;

		TColor color;
		bool	needDraw = false;
		//检查是不是颜色扩展
		if(m_ColorAppender.GetEnableAppend())
		{
			int colorAppendType = m_ColorAppender.GetCurAppendColorODD(drawPos);
			if(colorAppendType == 0)
			{
				needDraw = true;
				color = clMedGray;
			}
			else	if(colorAppendType == 1)
			{
				needDraw = true;
				color = clSilver;
			}
		}
		
		//高亮显示当前解析元素
		if(IsCurPosInTreeSelection(drawPos))
		{
			needDraw = true;
			color = clMoneyGreen;
		}

		if(needDraw)
		{
			ADefaultDraw = false;
			ACanvas->Brush->Color = color;
			ACanvas->FillRect(ARect);
			ACanvas->TextOut(ARect.left, ARect.top, AWideText);
			return;
		}
	}
}
//---------------------------------------------------------------------------

bool			TMDIChild::IsCurPosInTreeSelection(int pos)
{
	tagSelRect	selRect;
	if(GetTreeSelRect(selRect) == false)
		return 0;
		
	if(pos >= selRect.SelStart && pos < selRect.SelStart+selRect.SelLength)
	{
			return 1;
	}
	return	0;
}

bool			TMDIChild::GetTreeSelRect(tagSelRect & selRect)
{
	if(tvParseTree->Selected == NULL)
		return false;
		
	ParseTreeNode	*	curParseTree = (ParseTreeNode	*)tvParseTree->Selected->Data;
	if(curParseTree == NULL)
	{
		//选择的是结构体
		selRect.SelStart = m_ParseTree->GetCurPos();
		selRect.SelLength = m_ParseTree->GetSize();
		return true;
	}
	else
	{
		//选择的是变量
		selRect.SelStart = curParseTree->GetCurPos();
		selRect.SelLength = curParseTree->GetParseLen();
		return true;
	}
	
}

void			TMDIChild::SetSelectDetail()
{
	//详细信息显示在右边
	memWatch->Lines->Clear();
	
	tagSelRect	selRect;
	if(GetTreeSelRect(selRect) == false)
		return;

	String info = FormatStr("偏移 : %d", selRect.SelStart);
	memWatch->Lines->Add(info);

	info = FormatStr("长度 : %d", selRect.SelLength);
	memWatch->Lines->Add(info);

	info = "";

	ParseTreeNode * curNode = (ParseTreeNode * )tvParseTree->Selected->Data;
	if(curNode)
	{
		if(curNode->GetClassMember()->GetType() == "char" && curNode->GetClassMember()->GetArrayVar() != "")
		{
			info = curNode->GetParseResult();
		}
	}

	info = FormatStr("信息 : %s", info);
	memWatch->Lines->Add(info);
}

void __fastcall TMDIChild::tvParseTreeClick(TObject *Sender)
{
	m_HexEditor->Repaint();


	//设置卷轴滚动
	tagSelRect	selRect;
	if(GetTreeSelRect(selRect) == false)
		return;

	if(selRect.SelStart < m_HexEditor->DataSize)
	{
		GotoPosition(selRect.SelStart);
	}

	
 	SetSelectDetail();
	RefreshStateBar();

    //设置提示
    String hint;
    ParseTreeNode	*	curParseTree = (ParseTreeNode	*)tvParseTree->Selected->Data;
	if(curParseTree == NULL)
	{
		//选择的是结构体
        hint = m_ParseTree->GetClassData()->GetComment();
	}
	else
	{
		//选择的是变量
        hint = curParseTree->GetClassMember()->GetComment();
	}
    tvParseTree->Hint = hint;   
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::lvFastViewData(TObject *Sender, TListItem *Item)
{
	char	*pointer = m_HexEditor->GetFastPointer(0, m_HexEditor->DataSize);
	IParseVar * curVar = m_ParseEngine->GetVarByIndex(Item->Index);
	Item->Caption = curVar->GetVarName();
	int selStart = m_HexEditor->SelStart;
	Item->SubItems->Add(curVar->Parse(pointer, m_HexEditor->DataSize, selStart));
}
//---------------------------------------------------------------------------

void			TMDIChild::RefreshFastView()
{
	lvFastView->Items->Count = m_ParseEngine->GetVarCount();
	lvFastView->Refresh();
}



void __fastcall TMDIChild::pmLanguagePopup(TObject *Sender)
{
	actSetToGB->Checked = false;
	actSetToBIG5->Checked = false;
	actSetToUTF8->Checked = false;
	actSetToUnicode->Checked = false;
	
	if(GetLangModule() == lmGB)
	{
		actSetToGB->Checked = true;
	}
	else	if(GetLangModule() == lmBIG5)
	{
		actSetToBIG5->Checked = true;
	}
	else	if(GetLangModule() == lmUTF8)
	{
		actSetToUTF8->Checked = true;
	}
	else	if(GetLangModule() == lmUnicode)
	{
		actSetToUnicode->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::actSetToUTF8Execute(TObject *Sender)
{
	SetLangModule(lmUTF8);
	ParseData();		
}
//---------------------------------------------------------------------------


void __fastcall TMDIChild::tvParseTreeExpanding(TObject *Sender,
	  TTreeNode *Node, bool &AllowExpansion)
{
	if(Node->Parent == NULL)
	{
		//默认展开结构体节点
		return;
	}
	m_ParseTree->ViewCurNode((ParseTreeNode *)Node->Data, Node);
 	AllowExpansion = true;
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::actEditSourceExecute(TObject *Sender)
{
	if(SourceEditFrm->EditSource(GetWorkSpace(), m_WorkSpace->GetClassManager(), gBasicSrc, false))
	{
		m_SourceLoader.LoadFromStringList(SourceEditFrm->memSrcFile->Lines, m_WorkSpace->GetClassManager());
		m_ParseTree->BindClass(NULL);
		RefreshAllClassView();
		SetModify();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::actDelSelectExecute(TObject *Sender)
{
	m_ParseTree->BindClass(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::m_HexEditorMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
	if(m_LMouseDown)
	{
		char	*pointer = m_HexEditor->GetFastPointer(0, m_HexEditor->DataSize);
		int pos = m_HexEditor->SelStart;
		int selSize = m_HexEditor->SelCount;
		memWatch->Text = GetLangText(pointer+pos, selSize);
		RefreshStateBar();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::m_HexEditorMouseDown(TObject *Sender,
	  TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if(Button == mbLeft)
	{
		m_LMouseDown = true;

		//鼠标点击, 刷新状态栏
		RefreshStateBar();
		RefreshFastView();
		if(m_bFastParseMode == false)
			ParseData();
		ClearListHistory();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::m_HexEditorMouseUp(TObject *Sender,
	  TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if(Button == mbLeft)
		m_LMouseDown = false;
}

//---------------------------------------------------------------------------

void __fastcall TMDIChild::actGoToNextExecute(TObject *Sender)
{
	int gotoPos = m_ParseTree->GetCurPos() + m_ParseTree->GetSize();
	if(gotoPos < m_HexEditor->DataSize)
	{
		m_ParseListHistory.push(m_HexEditor->SelStart);
		m_HexEditor->SelStart = m_ParseTree->GetCurPos() + m_ParseTree->GetSize();
		ParseData(false);

        tagSelRect	selRect;
        if(GetTreeSelRect(selRect) == false)
            return;
        GotoPosition(selRect.SelStart);

		edtCurParseCount->Value = m_ParseListHistory.size();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::actGoToPrevExecute(TObject *Sender)
{
	if(m_ParseListHistory.size() == 0)
		return;
	m_HexEditor->SelStart = m_ParseListHistory.top();
	ParseData();
	
	m_ParseListHistory.pop();
	edtCurParseCount->Value = m_ParseListHistory.size();	
}
//---------------------------------------------------------------------------
void			TMDIChild::ClearListHistory()
{
	//清空栈
	while(m_ParseListHistory.size())
		m_ParseListHistory.pop();
	edtCurParseCount->Value = 0;
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::actGoToNumExecute(TObject *Sender)
{
	String num;
	int value = 0;
	if(InputQuery("输入要转到的记录(10进制, 从0开始)", "转到记录位置", num))
	{
		value = num.ToIntDef(0);
		if(value == 0)
			return;

		int pos = m_HexEditor->SelStart;
		int curNum = 0;

      	ClearListHistory();
		
		while(pos < m_HexEditor->DataSize)
		{
			if(curNum >= num)
				break;
			m_ParseListHistory.push(pos);
			m_ParseTree->UnPackData(pos);
			pos += m_ParseTree->GetSize();
			curNum++;
		}
		edtCurParseCount->Value = curNum;
		m_HexEditor->SelStart = pos;
		ParseData();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::actColorAppendExecute(TObject *Sender)
{
	if(m_ColorAppender.GetEnableAppend())
	{
		actColorAppend->Checked = false;
		m_ColorAppender.SetEnableAppend(false);
		m_HexEditor->Repaint();
		return;
	}

	String num;
	num = "5";
	int value = 0;
	if(InputQuery("颜色扩展", "输入扩展结构体数目(10进制, 0表示所有)", num))
	{
		value = num.ToIntDef(-1);
		if(value == -1)
			return;

		char	*pointer = m_HexEditor->GetFastPointer(0, m_HexEditor->DataSize);
		m_ColorAppender.AppendColor(pointer, m_HexEditor->DataSize,
						m_HexEditor->SelStart, m_ParseTree, value);

		actColorAppend->Checked = true;
		m_ColorAppender.SetEnableAppend(true);
		m_HexEditor->Repaint();
	}
}
//---------------------------------------------------------------------------
void __fastcall TMDIChild::actChangeFileDescribeExecute(TObject *Sender)
{
	FileStruct * curFileStruct = m_WorkSpace->GetFileManager()->GetFileData(lvWorkSpace->ItemIndex);
	if(curFileStruct)
	{
		EditFileDescribeFrm->EditFileStructDescribe(curFileStruct);
		SetFileDescribe(curFileStruct);
		m_WorkSpace->GetFileManager()->RefreshView();

        SetModify();
	}
}
//---------------------------------------------------------------------------



void __fastcall TMDIChild::actFastParseExecute(TObject *Sender)
{
	if(m_bFastParseMode == false)
	{
		//启动快速翻译模式
		m_bFastParseMode = true;
		labFastParse->Visible = true;
		actFastParse->Checked = true;

		m_FastParsePos = m_HexEditor->SelStart;
		labFastParse->Caption = FormatStr("当前解析位置 : %d", m_FastParsePos);
		m_HexEditor->PopupMenu = pmFastParse;
	}
	else
	{
		//关闭快速翻译模式
		m_bFastParseMode = false;
		labFastParse->Visible = false;
		actFastParse->Checked = false;

		m_HexEditor->PopupMenu = pmHex;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::pmFastParsePopup(TObject *Sender)
{
	MakeFastParseMenu();
}
//---------------------------------------------------------------------------

void 				TMDIChild::AddFastParseMenu(String Caption, int tag)
{
	TMenuItem * item = new TMenuItem(this);
    item->OnClick = FastParseExecute;
    item->Caption = Caption;
    item->Tag = tag;
    pmFastParse->Items->Add(item);
}

//---------------------------------------------------------------------------

void 				TMDIChild::MakeFastParseMenu()
{
	pmFastParse->Items->Clear();

	if(m_HexEditor->SelCount == 0)
		return;


	//单个元素
	for(int i=0; i<m_ParseEngine->GetVarCount(); i++)
	{
		IParseVar * curVar = m_ParseEngine->GetVarByIndex(i);
		if((int)curVar->GetSize() == (int)m_HexEditor->SelCount)
		{
			AddFastParseMenu(curVar->GetVarName());
		}
	}

	//数组
	AddFastParseMenu("-");
	String arrayName;
	for(int i=0; i<m_ParseEngine->GetVarCount(); i++)
	{
		IParseVar * curVar = m_ParseEngine->GetVarByIndex(i);
		if(curVar->GetSize() != 0 && (int)curVar->GetSize() < (int)m_HexEditor->SelCount)
		{
			if(m_HexEditor->SelCount % curVar->GetSize() == 0)
			{
				int count = m_HexEditor->SelCount / curVar->GetSize();
				arrayName = FormatStr("%s[%d]", curVar->GetVarName(), count);
				AddFastParseMenu(arrayName, count);
			}
		}
	}

	//特殊变量
	AddFastParseMenu("-");
	for(int i=0; i<m_ParseEngine->GetVarCount(); i++)
	{
		IParseVar * curVar = m_ParseEngine->GetVarByIndex(i);
		if(curVar->GetSize() == 0)
		{
			AddFastParseMenu(curVar->GetVarName());
		}
	}
}

void __fastcall 	TMDIChild::FastParseExecute(TObject *Sender)
{
	TMenuItem * selMenu = (TMenuItem * )Sender;
	String typeName = selMenu->Caption;

	//修正typeName
	if(selMenu->Caption == "-")
		return;

	if(typeName.Pos("["))
		typeName = LeftString(typeName, "[");

	ClassData * curClass = GetCurParseClass();

//	bool	haveResult = false;
	String 	defaultName;
	if(curClass == NULL)
	{
		//当前无结构体, 新建结构体
		int classCount = m_WorkSpace->GetClassManager()->GetClassCount();
		defaultName = FormatStr("tagUnNamedStruct%d", classCount);

		curClass = m_WorkSpace->GetClassManager()->AddClass();
		curClass->Init(defaultName, "");
		RefreshAllClassView();
	}

	String arrayVar;
	if(selMenu->Tag == 0)
		arrayVar = "";
	else
		arrayVar = IntToStr(selMenu->Tag);
		
	ClassMember * curMember = curClass->AddMember();
	defaultName = FormatStr("UnKnown%d", m_ParseTree->GetSize() + m_FastParsePos);

	curMember->Init(typeName, defaultName, "", arrayVar);

	m_ParseTree->BindClass(curClass);
	ExpandFirstNode();
	ParseData(false);

    tagSelRect	selRect;
    if(GetTreeSelRect(selRect) == false)
		return;
	GotoPosition(selRect.SelStart + selRect.SelLength);
}

ClassData	*		TMDIChild::GetCurParseClass()
{
	int index = GetCurParseClassIndex();
	if(index < 0)
		return NULL;

	return	m_WorkSpace->GetClassManager()->GetClassDataByIndex(index);
}

int				TMDIChild::GetCurParseClassIndex()
{
	IClassData * curData;
	for(int i=0; i<m_WorkSpace->GetClassManager()->GetClassCount(); i++)
	{
		curData = m_WorkSpace->GetClassManager()->GetClassDataByIndex(i);
		if(curData == m_ParseTree->GetClassData())
			return	i;
	}
	return	-1;
}

void __fastcall TMDIChild::actDelCurNodeExecute(TObject *Sender)
{
	if(tvParseTree->Selected == NULL)
		return;

	ParseTreeNode	*	curParseTree = (ParseTreeNode	*)tvParseTree->Selected->Data;
	ClassData	*	curClass = GetCurParseClass();
	if(curClass == NULL)
		return;
	if(curParseTree == NULL)
	{
		//选择的是结构体
		DeleteCurClass();
		curClass = NULL;
		DeleteCurClass();
	}
	else
	{
		//选择的是变量
		if(curParseTree->GetParent() == NULL)
		{
			//只能够删除成员变量
			curClass->DeleteMember(curParseTree->GetClassMember());
			if(curClass->GetMemberDataCount() == 0)
			{
				DeleteCurClass();
			}
			else
			{
				m_ParseTree->BindClass(curClass);
				ExpandFirstNode();
				ParseData();
			}
		}
	}
	SetModify();
}

void			TMDIChild::DeleteCurClass()
{
	int index = GetCurParseClassIndex();
	m_WorkSpace->GetClassManager()->DeleteClass(index);
	RefreshAllClassView();
	m_ParseTree->BindClass(NULL);
	SetModify();
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::actReNameCurNodeExecute(TObject *Sender)
{
	if(tvParseTree->Selected == NULL)
		return;

	ParseTreeNode	*	curParseTree = (ParseTreeNode	*)tvParseTree->Selected->Data;
	ChangeNodeName(curParseTree);
	SetModify();
	RefreshAllClassView();
}
//---------------------------------------------------------------------------

void			TMDIChild::ChangeNodeName(ParseTreeNode * curParseTree, bool needRefresh, int changeType)
{
	ClassData	*	curClass = GetCurParseClass();
	if(curClass == NULL)
		return;

    String showName;
    if(changeType == 0)
    {
        showName = "输入新名称";
    }
    else
    {
        showName = "输入新注释";
    }

	String name;
	int haveResult = 0;
	if(curParseTree == NULL)
	{
		//选择的是结构体
        if(changeType==0)
        {
    		name = curClass->GetName();
        }
        else
        {
            name = curClass->GetComment(); 
        }
		if(InputQuery(showName, showName, name))
		{
			haveResult = 1;
            if(changeType==0)
            {
    			curClass->SetName(name);
            }
            else
            {
                curClass->SetComment(name);
            }
		}
	}
	else
	{
		//选择的是变量
		String curName;
        if(changeType==0)
        {
            curName = curParseTree->GetClassMember()->GetName();
        }
        else
        {
            curName = curParseTree->GetClassMember()->GetComment();
        }
                         
		if(curName.Pos("["))
		{
			//是数组中的一个
			ParseTreeNode * parent = curParseTree->GetParent();
			ChangeNodeName(parent, false);
			parent->SetExNodeName();
			haveResult = 1;
		}
		else
		{
			ClassMember * curModifyMember = NULL;
			for(int i=0; i<curClass->GetMemberDataCount(); i++)
			{
				if((IClassMember *)curClass->GetMemberData(i) == curParseTree->GetClassMember())
				{                     
					curModifyMember = curClass->GetMemberByIndex(i);
				}
			}
			if(curModifyMember)
			{
                if(changeType==0)
                {
    				name = curModifyMember->GetName();
                }
                else
                {
                    name = curModifyMember->GetComment();
                }
				if(InputQuery(showName, showName, name))
				{
					haveResult = 1;
                    if(changeType==0)
                    {
    					curModifyMember->SetName(name);
                    }
                    else
                    {
                        curModifyMember->SetComment(name);
                    }
					curParseTree->SetExNodeName();
				}
			}
		}
	}

	if(haveResult && needRefresh)
	{
		RefreshAllClassView();
		m_ParseTree->RefreshViewText();
	}
}

void __fastcall TMDIChild::actOutputSourceExecute(TObject *Sender)
{
	SourceEditFrm->EditSource(GetWorkSpace(), m_WorkSpace->GetClassManager(), gBasicSrc, false);
}
//---------------------------------------------------------------------------


void __fastcall TMDIChild::actParseAsListExecute(TObject *Sender)
{
	char	*pointer = m_HexEditor->GetFastPointer(0, m_HexEditor->DataSize);
	ListParseFrm->ShowFrm(m_ParseEngine, m_WorkSpace->GetClassManager(),
						m_ParseTree->GetClassData(), pointer, m_HexEditor->DataSize,
						m_HexEditor->SelStart, m_WorkSpace->GetPath());	
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::actSaveFileExecute(TObject *Sender)
{
	if(m_ActiveFileStruct == NULL)
		return;

	m_ActiveFileStruct->GetMemory()->Clear();
	m_HexEditor->SaveToStream(m_ActiveFileStruct->GetMemory());

	String fileName = m_WorkSpace->GetFileName();

	if(fileName == "")
	{
		if(InputQuery("输入文件名(不要加后缀)", "输入保存的文件名(不要加后缀)", fileName))
		{
			if(fileName.Pos("."))
				fileName = LeftString(fileName, ".");
			fileName += ".eggxp";
			m_WorkSpace->SetFileName(fileName);
		}
		else
			return;
	}

	//保存工作区
//	if(m_WorkSpace->GetPath() == "")
//	{
	if(NeedSaveReq)
		NeedSaveReq();
//	}

	if(m_WorkSpace->GetComment() == "" && m_HexEditor->DataSize >= 2)
	{
		//自动生成注释
		if(m_WorkSpace->GetComment() == "")
		{
			char	*pointer = m_HexEditor->GetFastPointer(0, m_HexEditor->DataSize);
			String comment = BinToStr(pointer, 2);
			m_WorkSpace->SetComment(comment);
			if(RefreshWorkSpaceReq)
				RefreshWorkSpaceReq();
		}
	}

	if(m_WorkSpace->IsNewFile())
	{
		if(m_WorkSpace->GetPath() == "")
			return;
		m_WorkSpace->SaveToFile(fileName);
	}
	else
	{
		m_WorkSpace->SaveToFile();
	}

	DoSetTabCaption();
	m_HexEditor->Modified = false;
	m_bTreeModify = false;
	CheckModify();
}

void			TMDIChild::DoSetTabCaption()
{
	int index = GetIndexInMainTab();
	if(index >= 0)
	{
		MainTabSet->Tabs->Strings[index] = m_WorkSpace->GetFullName();
	}
}

int				TMDIChild::GetIndexInMainTab()
{
	if(MainTabSet==NULL)
		return -1;

	for (int i = 0; i < MainTabSet->Tabs->Count; i++)
	{
		if (MainTabSet->Tabs && MainTabSet->Tabs->Objects[i] == this)
		{
			return	i;
		}
	}
	return	-1;
}

void			TMDIChild::DoBringToFront()
{
	int index = GetIndexInMainTab();

	if(index >= 0)
	{
		MainTabSet->TabIndex = index;
	}
}




void __fastcall TMDIChild::actCopyAsBinExecute(TObject *Sender)
{
	Clipboard()->AsText = m_HexEditor->SelectionAsText;
}
//---------------------------------------------------------------------------


void __fastcall TMDIChild::actCopyAsHexStrExecute(TObject *Sender)
{
	String hexStr = m_HexEditor->SelectionAsHex;
	
	for(int i=2; i<hexStr.Length(); i+=2)
	{
		hexStr.Insert(" ", i+1);
		i++;
	}
	Clipboard()->AsText = hexStr;
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::actCopyAsListExecute(TObject *Sender)
{
	char	*pointer = m_HexEditor->GetFastPointer(0, m_HexEditor->DataSize);
	int selStart = m_HexEditor->SelStart;
	int selLength = m_HexEditor->SelCount;

	String	arrayStr;
	for(int i=0; i<selLength; i++)
	{
		if(i != selLength - 1)
			arrayStr += FormatStr("0x%s, ", BinToStr(pointer + selStart + i, 1));
		else
			arrayStr += FormatStr("0x%s", BinToStr(pointer + selStart + i, 1));
	}
	String result = FormatStr("char arrayData[%d] = {\r\n\t%s};", selLength, arrayStr);
	Clipboard()->AsText = result;
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::actSetToUnicodeExecute(TObject *Sender)
{
	SetLangModule(lmUnicode);
	ParseData();		
}
//---------------------------------------------------------------------------


void __fastcall TMDIChild::actNewVersionExecute(TObject *Sender)
{
	m_WorkSpace->GetFileManager()->CreateNew();
	lvWorkSpace->ItemIndex = lvWorkSpace->Items->Count - 1;
	LoadCurWork();
	SetModify();
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::actDelVersionExecute(TObject *Sender)
{
	if(lvWorkSpace->ItemIndex < 0)
		return;
	if(lvWorkSpace->Items->Count == 1)
	{
		m_ActiveFileStruct->SetDateTime(SPGetCurrentTime());
		m_ActiveFileStruct->GetMemory()->Clear();
		m_HexEditor->LoadFromStream(m_ActiveFileStruct->GetMemory());
		m_WorkSpace->GetFileManager()->RefreshView();
        SetModify();
		return;
	}

	int curIndex = lvWorkSpace->ItemIndex - 1;
	m_WorkSpace->GetFileManager()->DeleteVersion(lvWorkSpace->ItemIndex);

	if(curIndex < 0)
		curIndex = 0;
	lvWorkSpace->ItemIndex = curIndex;
	m_ActiveFileStruct = NULL;
	LoadCurWork();
	SetModify();
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::lvWorkSpaceClick(TObject *Sender)
{
 	int selStart = m_HexEditor->SelStart;
	LoadCurWork();
	if(selStart < m_HexEditor->DataSize)
	{
		m_HexEditor->SelStart = selStart;
		ParseData();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::pmFileDescribePopup(TObject *Sender)
{
	lvWorkSpaceClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::actFileSaveAsExecute(TObject *Sender)
{
	if(SaveDialog1->Execute())
	{
		m_HexEditor->SaveToFile(SaveDialog1->FileName);
	}
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::actCopyFastViewExecute(TObject *Sender)
{
	int index = lvFastView->ItemIndex;
	if(index < 0)
		return;

	Clipboard()->AsText = lvFastView->Selected->SubItems->Strings[0];
}
//---------------------------------------------------------------------------


void __fastcall TMDIChild::actReNameStructExecute(TObject *Sender)
{
	ChangeNodeName(NULL, true);	
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::actFindExecute(TObject *Sender)
{
    String result = SearchFrm->GetSearchResult();
    if(result == "")
        return;

    char	*startPointer = m_HexEditor->GetFastPointer(0, m_HexEditor->DataSize) + m_HexEditor->SelStart;
    int     searchSize = m_HexEditor->DataSize - m_HexEditor->SelStart;

    LPVOID  curData = m_SearchEngine.NormalSearch(startPointer, searchSize+1, AnsiString(result).c_str());
    if(curData == NULL)
    {
        ShowMessage("没有结果");
        return;
    }

    String  buffer;
    buffer.SetLength(result.Length());
    int len = HexStrToBin(AnsiString(buffer).c_str(), result);

    m_HexEditor->SelStart += (char *)curData - startPointer;
    m_HexEditor->SelCount = len;
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::actChangeCommentExecute(TObject *Sender)
{
    if(tvParseTree->Selected == NULL)
		return;

	ParseTreeNode	*	curParseTree = (ParseTreeNode	*)tvParseTree->Selected->Data;
	ChangeNodeName(curParseTree, true, 1);
	SetModify();
	RefreshAllClassView();
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(Key == 0x1B)
    {
        Key=0;
        actDelSelectExecute(Sender);
    }
}

//---------------------------------------------------------------------------

void            TMDIChild::SetPlugins(AList<tagExePlugins> *   plugins)
{
    m_Plugins = plugins;
    InitPlugins();  
}

void             TMDIChild::InitPlugins()
{
    if(m_Plugins == NULL)
        return;

    tagExePlugins   *   exePlug;
    TMenuItem   *       curItem;
    for(int i=0; i<m_Plugins->Count(); i++)
    {
        exePlug = m_Plugins->At(i);
        curItem = new TMenuItem(pmExePlug->Items);
        pmExePlug->Items->Add(curItem);

        curItem->Caption = exePlug->Name;
        curItem->Tag = i;
        curItem->OnClick = actOpenPluginExecute;

        //发送到菜单
        curItem = new TMenuItem(miSendTo);
        miSendTo->Add(curItem);
        curItem->Caption = exePlug->Name;
        curItem->Tag = i;
        curItem->OnClick = actSendToPluginTestExecute;
    }
}

//---------------------------------------------------------------------------

void __fastcall TMDIChild::actOpenPluginExecute(TObject *Sender)
{
    TMenuItem   *   curItem = (TMenuItem *)Sender;
    tagExePlugins   *   exePlug = m_Plugins->At(curItem->Tag);

    if(exePlug == NULL)
    {
        ShowMessage("actOpenPluginExecute index Error");
        return;
    }

    String openFileName = GetAppPath() + EX_PLUGIN_DIR + exePlug->ExeName;
    ShellExecute(NULL, L"open", openFileName.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

//---------------------------------------------------------------------------

void __fastcall TMDIChild::actSendToPluginTestExecute(TObject *Sender)
{
    TMenuItem   *   curItem = (TMenuItem *)Sender;
    tagExePlugins   *   exePlug = m_Plugins->At(curItem->Tag);

    if(exePlug == NULL)
    {
        ShowMessage("actOpenPluginExecute index Error");
        return;
    }

    void * handle = FindWindow(exePlug->ClassName.c_str(), NULL);
	if(handle == NULL)
	{
        ShowMessage(FormatStr("没有开启%s!", exePlug->Name));
		return;
	}


    if(exePlug->RecvType == 0 || exePlug->RecvType == 2)
    {
        String hexStr;
        if(m_HexEditor->SelCount != 0)
        {
            hexStr = m_HexEditor->SelectionAsHex;

            for(int i=2; i<hexStr.Length(); i+=2)
            {
                hexStr.Insert(" ", i+1);
                i++;
            }
        }
        else
        {
            tagSelRect	selRect;
            if(GetTreeSelRect(selRect) == false)
                return;
            char	*pointer = m_HexEditor->GetFastPointer(0, m_HexEditor->DataSize);
            int pos = selRect.SelStart;
            int selSize = selRect.SelLength;
            hexStr = BinToStr(pointer+pos, selSize);
        }
        ///////////////////

        COPYDATASTRUCT	cds;
        cds.dwData = 0;
        cds.cbData = hexStr.Length();
        cds.lpData = (void *)hexStr.c_str();
        SendMessage(handle, WM_COPYDATA, 0, (long)&cds);
    }

    if(exePlug->RecvType == 1 || exePlug->RecvType == 2)
    {
        String info;
        if(m_ActiveFileStruct)
        {
            info = m_ActiveFileStruct->GetRemark();
        }
        else
        {
            info = "没有描述! 干!!";
        }
        COPYDATASTRUCT	cds;
        cds.dwData = 1;
        cds.cbData = info.Length();
        cds.lpData = (void *)info.c_str();
        SendMessage(handle, WM_COPYDATA, 0, (long)&cds);
    }
}

void __fastcall TMDIChild::actWriteExecute(TObject *Sender)
{
    if(tvParseTree->Selected == NULL)
		return;

	ParseTreeNode	*	curParseTree = (ParseTreeNode	*)tvParseTree->Selected->Data;

    if(curParseTree == NULL)
	{
        return;
    }

	ClassData	*	curClass = GetCurParseClass();
	if(curClass == NULL)
		return;

    tagSelRect	selRect;
    if(GetTreeSelRect(selRect) == false)
        return;

    String  type = curParseTree->GetClassMember()->GetType();
    if(IsNormalType(type) == false)
    {
        ShowMessage("只能改变普通变量的值");
        return;
    }

    String  value = curParseTree->GetParseResult();
    if(InputQuery("输入值", "输入值", value) == false)
        return;

//    m_HexEditor->BeginUpdate();
    char	*pointer = m_HexEditor->GetFastPointer(0, m_HexEditor->DataSize);
    int dataSize = m_HexEditor->DataSize;
    int pos = selRect.SelStart;
    int nodeSize = m_ParseEngine->GetSize(type, pointer, dataSize, pos);
    int childCount = curParseTree->GetClassMember()->GetArrayVar().ToIntDef(0);

    int curSize = 0;
    for(int i=0; i<m_ParseTree->GetParseTreeNodeCount(); i++)
    {
        ParseTreeNode	* curTreeNode = m_ParseTree->GetParseTreeNode(i);
        if(curTreeNode == curParseTree)
            break;

        int curChildCount = curTreeNode->GetClassMember()->GetArrayVar().ToIntDef(0);
        if(curChildCount == 0)
            curChildCount = 1;
        curSize += curChildCount * m_ParseEngine->GetSize(
                            curTreeNode->GetClassMember()->GetType(), pointer, dataSize, pos);
	}

    pos = m_LastPos + curSize;
    if(childCount == 0)
        childCount = 1;
	nodeSize *= childCount;

	
	//插入数据
    if(pos + nodeSize > dataSize)
    {
        String  buffer;
        buffer.SetLength(pos + nodeSize - dataSize);
        memset(buffer.c_str(), '\0', buffer.Length());
		m_HexEditor->InsertBuffer(AnsiString(buffer).c_str(), buffer.Length(), selRect.SelStart, "insert", false);
    }

	
	pointer = m_HexEditor->GetFastPointer(0, m_HexEditor->DataSize);
//	String  setEmpty;
//	setEmpty.SetLength(nodeSize);
//    int oldPos = pos;
//	WriteBuf(pointer, oldPos, setEmpty.c_str(), setEmpty.Length());

    if(type == "char")
    {
        WriteBuf(pointer, pos, value.c_str(), value.Length());
    }
    else
    {
        int iResult = value.ToIntDef(0);
        WriteBuf(pointer, pos, &iResult, sizeof(iResult));
    }
    m_HexEditor->SelStart = m_LastPos;
    ParseData(false);
//    m_HexEditor->EndUpdate();
}
//---------------------------------------------------------------------------


void __fastcall TMDIChild::m_HexEditorClick(TObject *Sender)
{
    m_LastPos = m_HexEditor->SelStart;
}
//---------------------------------------------------------------------------



void __fastcall TMDIChild::m_HexEditorKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    m_LastPos = m_HexEditor->SelStart;
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::actOpenListFromTxtExecute(TObject *Sender)
{
	//从txt格式导入列表
	if(OpenDialog1->Execute())
	{
		if(OpenFileCheck(OpenDialog1->FileName))
		{
			TxtToListLoader	txtToListLoader;
			txtToListLoader.LoadTxtFile(OpenDialog1->FileName, "\t", GetCurParseClass());
			m_HexEditor->LoadFromStream(txtToListLoader.GetOutPutStream());
		}
		SetModify();
	}
}
//---------------------------------------------------------------------------
void __fastcall TMDIChild::FormActivate(TObject *Sender)
{
    if(MainTabSet==NULL)
	  return;
	for (int i = 0; i <= MainTabSet->Tabs->Count; i++)
	{
		if (MainTabSet->Tabs->Objects[i] == this)
		{
			MainTabSet->TabIndex = i;
			return;
		}
	}    
}
//---------------------------------------------------------------------------



void __fastcall TMDIChild::FormCreate(TObject *Sender)
{
	DragAcceptFiles(this->Handle, TRUE);
}
//---------------------------------------------------------------------------


void __fastcall TMDIChild::WmDropFiles(TWMDropFiles& Message)
{
	TCHAR buff[MAX_PATH];
	HDROP hDrop = (HDROP)Message.Drop;
	int numFiles = DragQueryFile(hDrop, -1, NULL, NULL);
	if (numFiles > 1)
	{
		// 只接受一个
		numFiles = 1;
	}
	for (int i=0;i < numFiles;i++) {
		DragQueryFile(hDrop, i, buff, sizeof(buff));
		// process the file in 'buff'
		m_HexEditor->LoadFromFile(buff);
	}
	DragFinish(hDrop);
}
