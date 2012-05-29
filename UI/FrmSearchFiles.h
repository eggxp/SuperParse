//---------------------------------------------------------------------------

#ifndef FrmSearchFilesH
#define FrmSearchFilesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include "cgauges.h"
#include "FileSearch.h"
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
typedef		void	(__closure	*TLoadFile)(String	fileName);

class TSearchFilesFrm : public TForm
{
__published:	// IDE-managed Components
	TListView *lvResult;
	TCGauge *cgProcess;
	TPanel *Panel1;
	TLabel *Label1;
	TEdit *edtSearchContent;
	TComboBox *cbSearchMode;
	TLabel *Label2;
	TEdit *edtSearchPath;
	TButton *btSelectSearchPath;
	TCheckBox *cbInclude;
	TLabel *Label3;
	TButton *btBeginSearch;
	TEdit *edtFileExt;
	TButton *btResearch;
	TPopupMenu *PopupMenu1;
	TMenuItem *nLoadFile;
	void __fastcall btSelectSearchPathClick(TObject *Sender);
	void __fastcall lvResultData(TObject *Sender, TListItem *Item);
	void __fastcall btBeginSearchClick(TObject *Sender);
	void __fastcall btResearchClick(TObject *Sender);
	void __fastcall nLoadFileClick(TObject *Sender);
private:	// User declarations
	AllFileSearch			 	m_FileSearch;

	String						GetSearchData();
	void						RefreshResult();
public:		// User declarations
	__fastcall TSearchFilesFrm(TComponent* Owner);
	TLoadFile					LoadFile;
};
//---------------------------------------------------------------------------
extern PACKAGE TSearchFilesFrm *SearchFilesFrm;
//---------------------------------------------------------------------------
#endif
