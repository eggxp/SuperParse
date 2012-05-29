// Borland C++ Builder
// Copyright (c) 1995, 2005 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Fs_idisp.pas' rev: 10.00

#ifndef Fs_idispHPP
#define Fs_idispHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Sysutils.hpp>	// Pascal unit
#include <Activex.hpp>	// Pascal unit
#include <Comobj.hpp>	// Pascal unit
#include <Fs_iinterpreter.hpp>	// Pascal unit
#include <Variants.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Fs_idisp
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TfsOLEHelper;
class PASCALIMPLEMENTATION TfsOLEHelper : public Fs_iinterpreter::TfsCustomHelper 
{
	typedef Fs_iinterpreter::TfsCustomHelper inherited;
	
private:
	Variant __fastcall DispatchInvoke(const Variant &ParamArray, int ParamCount, Word Flags);
	
protected:
	virtual void __fastcall SetValue(const Variant &Value);
	virtual Variant __fastcall GetValue();
	
public:
	__fastcall TfsOLEHelper(const AnsiString AName);
public:
	#pragma option push -w-inl
	/* TfsItemList.Destroy */ inline __fastcall virtual ~TfsOLEHelper(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Fs_idisp */
using namespace Fs_idisp;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fs_idisp
