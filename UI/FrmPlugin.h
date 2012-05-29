//---------------------------------------------------------------------------

#ifndef FrmPluginH
#define FrmPluginH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>

class	PluginManager;

//---------------------------------------------------------------------------
class TPluginFrm : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TMemo *Memo1;
	TListView *lvPlugins;
	TEdit *edtPluginPath;
	TButton *btOk;
	TPopupMenu *PopupMenu1;
	TMenuItem *nWatchHead;
	TMemo *memInfo;
	TSplitter *Splitter1;
	void __fastcall btOkClick(TObject *Sender);
	void __fastcall lvPluginsData(TObject *Sender, TListItem *Item);
	void __fastcall lvPluginsClick(TObject *Sender);
private:	// User declarations
	PluginManager		*m_PluginManager;
public:		// User declarations
	__fastcall TPluginFrm(TComponent* Owner);

	void		ShowPlugins(PluginManager * pluginManager);
};
//---------------------------------------------------------------------------
extern PACKAGE TPluginFrm *PluginFrm;
//---------------------------------------------------------------------------
#endif
