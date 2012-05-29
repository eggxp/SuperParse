// Borland C++ Builder
// Copyright (c) 1995, 2005 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Fs_ievents.pas' rev: 10.00

#ifndef Fs_ieventsHPP
#define Fs_ieventsHPP

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
#include <Controls.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Fs_ievents
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TfsNotifyEvent;
class PASCALIMPLEMENTATION TfsNotifyEvent : public Fs_iinterpreter::TfsCustomEvent 
{
	typedef Fs_iinterpreter::TfsCustomEvent inherited;
	
public:
	void __fastcall DoEvent(System::TObject* Sender);
	virtual void * __fastcall GetMethod(void);
public:
	#pragma option push -w-inl
	/* TfsCustomEvent.Create */ inline __fastcall virtual TfsNotifyEvent(System::TObject* AObject, Fs_iinterpreter::TfsProcVariable* AHandler) : Fs_iinterpreter::TfsCustomEvent(AObject, AHandler) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TfsNotifyEvent(void) { }
	#pragma option pop
	
};


class DELPHICLASS TfsMouseEvent;
class PASCALIMPLEMENTATION TfsMouseEvent : public Fs_iinterpreter::TfsCustomEvent 
{
	typedef Fs_iinterpreter::TfsCustomEvent inherited;
	
public:
	void __fastcall DoEvent(System::TObject* Sender, Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	virtual void * __fastcall GetMethod(void);
public:
	#pragma option push -w-inl
	/* TfsCustomEvent.Create */ inline __fastcall virtual TfsMouseEvent(System::TObject* AObject, Fs_iinterpreter::TfsProcVariable* AHandler) : Fs_iinterpreter::TfsCustomEvent(AObject, AHandler) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TfsMouseEvent(void) { }
	#pragma option pop
	
};


class DELPHICLASS TfsMouseMoveEvent;
class PASCALIMPLEMENTATION TfsMouseMoveEvent : public Fs_iinterpreter::TfsCustomEvent 
{
	typedef Fs_iinterpreter::TfsCustomEvent inherited;
	
public:
	void __fastcall DoEvent(System::TObject* Sender, Classes::TShiftState Shift, int X, int Y);
	virtual void * __fastcall GetMethod(void);
public:
	#pragma option push -w-inl
	/* TfsCustomEvent.Create */ inline __fastcall virtual TfsMouseMoveEvent(System::TObject* AObject, Fs_iinterpreter::TfsProcVariable* AHandler) : Fs_iinterpreter::TfsCustomEvent(AObject, AHandler) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TfsMouseMoveEvent(void) { }
	#pragma option pop
	
};


class DELPHICLASS TfsKeyEvent;
class PASCALIMPLEMENTATION TfsKeyEvent : public Fs_iinterpreter::TfsCustomEvent 
{
	typedef Fs_iinterpreter::TfsCustomEvent inherited;
	
public:
	void __fastcall DoEvent(System::TObject* Sender, Word &Key, Classes::TShiftState Shift);
	virtual void * __fastcall GetMethod(void);
public:
	#pragma option push -w-inl
	/* TfsCustomEvent.Create */ inline __fastcall virtual TfsKeyEvent(System::TObject* AObject, Fs_iinterpreter::TfsProcVariable* AHandler) : Fs_iinterpreter::TfsCustomEvent(AObject, AHandler) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TfsKeyEvent(void) { }
	#pragma option pop
	
};


class DELPHICLASS TfsKeyPressEvent;
class PASCALIMPLEMENTATION TfsKeyPressEvent : public Fs_iinterpreter::TfsCustomEvent 
{
	typedef Fs_iinterpreter::TfsCustomEvent inherited;
	
public:
	void __fastcall DoEvent(System::TObject* Sender, char &Key);
	virtual void * __fastcall GetMethod(void);
public:
	#pragma option push -w-inl
	/* TfsCustomEvent.Create */ inline __fastcall virtual TfsKeyPressEvent(System::TObject* AObject, Fs_iinterpreter::TfsProcVariable* AHandler) : Fs_iinterpreter::TfsCustomEvent(AObject, AHandler) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TfsKeyPressEvent(void) { }
	#pragma option pop
	
};


class DELPHICLASS TfsCloseEvent;
class PASCALIMPLEMENTATION TfsCloseEvent : public Fs_iinterpreter::TfsCustomEvent 
{
	typedef Fs_iinterpreter::TfsCustomEvent inherited;
	
public:
	void __fastcall DoEvent(System::TObject* Sender, Forms::TCloseAction &Action);
	virtual void * __fastcall GetMethod(void);
public:
	#pragma option push -w-inl
	/* TfsCustomEvent.Create */ inline __fastcall virtual TfsCloseEvent(System::TObject* AObject, Fs_iinterpreter::TfsProcVariable* AHandler) : Fs_iinterpreter::TfsCustomEvent(AObject, AHandler) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TfsCloseEvent(void) { }
	#pragma option pop
	
};


class DELPHICLASS TfsCloseQueryEvent;
class PASCALIMPLEMENTATION TfsCloseQueryEvent : public Fs_iinterpreter::TfsCustomEvent 
{
	typedef Fs_iinterpreter::TfsCustomEvent inherited;
	
public:
	void __fastcall DoEvent(System::TObject* Sender, bool &CanClose);
	virtual void * __fastcall GetMethod(void);
public:
	#pragma option push -w-inl
	/* TfsCustomEvent.Create */ inline __fastcall virtual TfsCloseQueryEvent(System::TObject* AObject, Fs_iinterpreter::TfsProcVariable* AHandler) : Fs_iinterpreter::TfsCustomEvent(AObject, AHandler) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TfsCloseQueryEvent(void) { }
	#pragma option pop
	
};


class DELPHICLASS TfsCanResizeEvent;
class PASCALIMPLEMENTATION TfsCanResizeEvent : public Fs_iinterpreter::TfsCustomEvent 
{
	typedef Fs_iinterpreter::TfsCustomEvent inherited;
	
public:
	void __fastcall DoEvent(System::TObject* Sender, int &NewWidth, int &NewHeight, bool &Resize);
	virtual void * __fastcall GetMethod(void);
public:
	#pragma option push -w-inl
	/* TfsCustomEvent.Create */ inline __fastcall virtual TfsCanResizeEvent(System::TObject* AObject, Fs_iinterpreter::TfsProcVariable* AHandler) : Fs_iinterpreter::TfsCustomEvent(AObject, AHandler) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TfsCanResizeEvent(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Fs_ievents */
using namespace Fs_ievents;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fs_ievents
