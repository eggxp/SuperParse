//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FrmPlugin.h"
#include "PluginManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPluginFrm *PluginFrm;
//---------------------------------------------------------------------------
__fastcall TPluginFrm::TPluginFrm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPluginFrm::btOkClick(TObject *Sender)
{
	this->Close();	
}
//---------------------------------------------------------------------------
void __fastcall TPluginFrm::lvPluginsData(TObject *Sender, TListItem *Item)
{
	tagPluginInfo * curInfo = m_PluginManager->GetPlugin(Item->Index);
	Item->Caption = curInfo->Name;
	Item->SubItems->Add(curInfo->ParseVar.GetVersion());
	Item->SubItems->Add(curInfo->ParseVar.GetDescription());
}
//---------------------------------------------------------------------------

void		TPluginFrm::ShowPlugins(PluginManager * pluginManager)
{
	m_PluginManager = pluginManager;
	edtPluginPath->Text = GetAppPath() + DLL_PATH;
	lvPlugins->Items->Count = m_PluginManager->GetPluginCount();
	lvPlugins->Refresh();
	this->Show();
}

void __fastcall TPluginFrm::lvPluginsClick(TObject *Sender)
{
 	if(lvPlugins->ItemIndex < 0)
		return;
	memInfo->Lines->LoadFromFile(m_PluginManager->GetPlugin(lvPlugins->ItemIndex)->Name+".h");
}
//---------------------------------------------------------------------------

