//---------------------------------------------------------------------------

#ifndef FrmEditFileDescribeH
#define FrmEditFileDescribeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "ParseFileData.h"
#include "FrmEditFileDescribe.h"
//---------------------------------------------------------------------------
class TEditFileDescribeFrm : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TButton *Button2;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *edtFileDescribe;
	TEdit *edtCreateDate;
	TLabel *Label3;
	TMemo *memRemark;
	TButton *btResetTime;
	TLabel *Label4;
	TEdit *edtKey;
	void __fastcall btResetTimeClick(TObject *Sender);
private:	// User declarations
	FileStruct	*	m_FileStruct;
public:		// User declarations
	__fastcall TEditFileDescribeFrm(TComponent* Owner);
	void		EditFileStructDescribe(FileStruct	*	curFileStruct);
};
//---------------------------------------------------------------------------
extern PACKAGE TEditFileDescribeFrm *EditFileDescribeFrm;
//---------------------------------------------------------------------------
#endif
