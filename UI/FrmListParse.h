//---------------------------------------------------------------------------

#ifndef FrmListParseH
#define FrmListParseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <DBClient.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
#include "cspin.h"
#include "cgauges.h"
#include "IParseEngine.h"
#include "ISourceData.h"
#include "TreeToClientData.h"
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------

class	ParseTree;
class	ParseTreeNode;

class TListParseFrm : public TForm
{
__published:	// IDE-managed Components
	TDBGrid *DBGrid1;
	TClientDataSet *cdsData;
	TDataSource *DataSource1;
	TPanel *Panel1;
	TSplitter *Splitter1;
	TLabel *Label1;
	TCSpinEdit *edtParseCount;
	TButton *btStart;
	TButton *btOutputFile;
	TCGauge *cgProcess;
	TListView *lvParseData;
	TSplitter *Splitter2;
	TSaveDialog *SaveDialog1;
	TButton *btOutput;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btOutputFileClick(TObject *Sender);
	void __fastcall btStartClick(TObject *Sender);
	void __fastcall lvParseDataData(TObject *Sender, TListItem *Item);
	void __fastcall btOutputClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
	ParseTree		*	m_ParseTree;
	int					m_FileSize;
	int					m_ParsePos;
	String				m_SavePath;

	TreeToClientData	m_TreeToClientData;
	void				RefreshList();
public:		// User declarations
	__fastcall TListParseFrm(TComponent* Owner);

	void			ShowFrm(IParseEngine	*	engine, IClassManager * classManager, IClassData * curClass, 
							char * lpData, int dataSize, int parsePos, String savePath);
};
//---------------------------------------------------------------------------
extern PACKAGE TListParseFrm *ListParseFrm;
//---------------------------------------------------------------------------
#endif
