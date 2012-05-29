// Borland C++ Builder
// Copyright (c) 1995, 2005 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Fs_itools.pas' rev: 10.00

#ifndef Fs_itoolsHPP
#define Fs_itoolsHPP

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
#include <Fs_xml.hpp>	// Pascal unit
#include <Variants.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Fs_itools
{
//-- type declarations -------------------------------------------------------
typedef System::TVarRec TVarRecArray[32];

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall fsRegisterLanguage(const AnsiString Name, const AnsiString Grammar);
extern PACKAGE AnsiString __fastcall fsGetLanguage(const AnsiString Name);
extern PACKAGE void __fastcall fsGetLanguageList(Classes::TStrings* List);
extern PACKAGE Fs_iinterpreter::TfsVarType __fastcall StrToVarType(const AnsiString TypeName);
extern PACKAGE bool __fastcall TypesCompatible(const Fs_iinterpreter::TfsTypeRec &Typ1, const Fs_iinterpreter::TfsTypeRec &Typ2);
extern PACKAGE bool __fastcall AssignCompatible(Fs_iinterpreter::TfsCustomVariable* Var1, Fs_iinterpreter::TfsCustomVariable* Var2);
extern PACKAGE Variant __fastcall VarRecToVariant(const System::TVarRec &v);
extern PACKAGE void __fastcall VariantToVarRec(const Variant &v, System::TVarRec * ar);
extern PACKAGE void __fastcall ClearVarRec(System::TVarRec * ar);
extern PACKAGE Variant __fastcall ParserStringToVariant(const AnsiString s);
extern PACKAGE Fs_iinterpreter::TfsCustomVariable* __fastcall ParseMethodSyntax(const AnsiString Syntax);
extern PACKAGE Types::TPoint __fastcall fsPosToPoint(const AnsiString ErrorPos);
extern PACKAGE void __fastcall GenerateXMLContents(Fs_iinterpreter::TfsScript* Prog, Fs_xml::TfsXMLItem* Item);

}	/* namespace Fs_itools */
using namespace Fs_itools;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fs_itools
