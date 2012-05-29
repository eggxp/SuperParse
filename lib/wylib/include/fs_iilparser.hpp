// Borland C++ Builder
// Copyright (c) 1995, 2005 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Fs_iilparser.pas' rev: 10.00

#ifndef Fs_iilparserHPP
#define Fs_iilparserHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Sysutils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Fs_iinterpreter.hpp>	// Pascal unit
#include <Fs_iparser.hpp>	// Pascal unit
#include <Fs_iexpression.hpp>	// Pascal unit
#include <Fs_xml.hpp>	// Pascal unit
#include <Variants.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Fs_iilparser
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TfsEmitOp { emNone, emCreate, emFree };
#pragma option pop

class DELPHICLASS TfsILParser;
class PASCALIMPLEMENTATION TfsILParser : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	AnsiString FErrorPos;
	Fs_xml::TfsXMLDocument* FGrammar;
	Fs_xml::TfsXMLDocument* FILScript;
	AnsiString FLangName;
	bool FNeedDeclareVars;
	Fs_iparser::TfsParser* FParser;
	Fs_iinterpreter::TfsScript* FProgram;
	Fs_xml::TfsXMLItem* FProgRoot;
	Fs_xml::TfsXMLItem* FRoot;
	AnsiString FUnitName;
	Classes::TStringList* FWithList;
	AnsiString __fastcall PropPos(Fs_xml::TfsXMLItem* xi);
	void __fastcall ErrorPos(Fs_xml::TfsXMLItem* xi);
	void __fastcall CheckIdent(Fs_iinterpreter::TfsScript* Prog, const AnsiString Name);
	Fs_iinterpreter::TfsClassVariable* __fastcall FindClass(const AnsiString TypeName);
	void __fastcall CheckTypeCompatibility(Fs_iinterpreter::TfsCustomVariable* Var1, Fs_iinterpreter::TfsCustomVariable* Var2);
	Fs_iinterpreter::TfsCustomVariable* __fastcall FindVar(Fs_iinterpreter::TfsScript* Prog, const AnsiString Name);
	Fs_iinterpreter::TfsVarType __fastcall FindType(AnsiString s);
	Fs_iinterpreter::TfsCustomVariable* __fastcall CreateVar(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog, const AnsiString Name, Fs_iinterpreter::TfsStatement* Statement = (Fs_iinterpreter::TfsStatement*)(0x0), bool CreateParam = false, bool IsVarParam = false);
	Fs_iinterpreter::TfsSetExpression* __fastcall DoSet(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog);
	Fs_iexpression::TfsExpression* __fastcall DoExpression(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog);
	void __fastcall DoUses(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog);
	void __fastcall DoVar(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog, Fs_iinterpreter::TfsStatement* Statement);
	void __fastcall DoConst(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog);
	void __fastcall DoParameters(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsProcVariable* v);
	void __fastcall DoProc1(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog);
	void __fastcall DoProc2(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog);
	void __fastcall DoFunc1(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog);
	void __fastcall DoFunc2(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog);
	void __fastcall DoAssign(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog, Fs_iinterpreter::TfsStatement* Statement);
	void __fastcall DoCall(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog, Fs_iinterpreter::TfsStatement* Statement);
	void __fastcall DoIf(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog, Fs_iinterpreter::TfsStatement* Statement);
	void __fastcall DoFor(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog, Fs_iinterpreter::TfsStatement* Statement);
	void __fastcall DoVbFor(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog, Fs_iinterpreter::TfsStatement* Statement);
	void __fastcall DoCppFor(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog, Fs_iinterpreter::TfsStatement* Statement);
	void __fastcall DoWhile(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog, Fs_iinterpreter::TfsStatement* Statement);
	void __fastcall DoRepeat(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog, Fs_iinterpreter::TfsStatement* Statement);
	void __fastcall DoCase(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog, Fs_iinterpreter::TfsStatement* Statement);
	void __fastcall DoTry(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog, Fs_iinterpreter::TfsStatement* Statement);
	void __fastcall DoBreak(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog, Fs_iinterpreter::TfsStatement* Statement);
	void __fastcall DoContinue(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog, Fs_iinterpreter::TfsStatement* Statement);
	void __fastcall DoExit(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog, Fs_iinterpreter::TfsStatement* Statement);
	void __fastcall DoReturn(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog, Fs_iinterpreter::TfsStatement* Statement);
	void __fastcall DoWith(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog, Fs_iinterpreter::TfsStatement* Statement);
	void __fastcall DoDelete(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog, Fs_iinterpreter::TfsStatement* Statement);
	void __fastcall DoCompoundStmt(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog, Fs_iinterpreter::TfsStatement* Statement);
	void __fastcall DoStmt(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog, Fs_iinterpreter::TfsStatement* Statement);
	void __fastcall DoProgram(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog);
	
public:
	__fastcall TfsILParser(Fs_iinterpreter::TfsScript* AProgram);
	__fastcall virtual ~TfsILParser(void);
	void __fastcall SelectLanguage(const AnsiString LangName);
	bool __fastcall MakeILScript(const AnsiString Text);
	void __fastcall ParseILScript(void);
	Fs_iinterpreter::TfsDesignator* __fastcall DoDesignator(Fs_xml::TfsXMLItem* xi, Fs_iinterpreter::TfsScript* Prog, TfsEmitOp EmitOp = (TfsEmitOp)(0x0));
	__property Fs_xml::TfsXMLDocument* ILScript = {read=FILScript};
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Fs_iilparser */
using namespace Fs_iilparser;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fs_iilparser
