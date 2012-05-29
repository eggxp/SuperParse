// Borland C++ Builder
// Copyright (c) 1995, 2005 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Fs_xml.pas' rev: 10.00

#ifndef Fs_xmlHPP
#define Fs_xmlHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Sysutils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Fs_xml
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TfsXMLItem;
class PASCALIMPLEMENTATION TfsXMLItem : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	TfsXMLItem* operator[](int Index) { return Items[Index]; }
	
private:
	void *FData;
	Classes::TList* FItems;
	AnsiString FName;
	TfsXMLItem* FParent;
	AnsiString FText;
	int __fastcall GetCount(void);
	TfsXMLItem* __fastcall GetItems(int Index);
	AnsiString __fastcall GetProp(AnsiString Index);
	void __fastcall SetProp(AnsiString Index, const AnsiString Value);
	void __fastcall SetParent(const TfsXMLItem* Value);
	
public:
	__fastcall virtual ~TfsXMLItem(void);
	void __fastcall AddItem(TfsXMLItem* Item);
	void __fastcall Assign(TfsXMLItem* Item);
	void __fastcall Clear(void);
	void __fastcall InsertItem(int Index, TfsXMLItem* Item);
	TfsXMLItem* __fastcall Add(void);
	int __fastcall Find(const AnsiString Name);
	TfsXMLItem* __fastcall FindItem(const AnsiString Name);
	int __fastcall IndexOf(TfsXMLItem* Item);
	TfsXMLItem* __fastcall Root(void);
	__property int Count = {read=GetCount, nodefault};
	__property void * Data = {read=FData, write=FData};
	__property TfsXMLItem* Items[int Index] = {read=GetItems/*, default*/};
	__property AnsiString Name = {read=FName, write=FName};
	__property TfsXMLItem* Parent = {read=FParent, write=SetParent};
	__property AnsiString Prop[AnsiString Index] = {read=GetProp, write=SetProp};
	__property AnsiString Text = {read=FText, write=FText};
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TfsXMLItem(void) : System::TObject() { }
	#pragma option pop
	
};


class DELPHICLASS TfsXMLDocument;
class PASCALIMPLEMENTATION TfsXMLDocument : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	bool FAutoIndent;
	TfsXMLItem* FRoot;
	
public:
	__fastcall TfsXMLDocument(void);
	__fastcall virtual ~TfsXMLDocument(void);
	void __fastcall Clear(void);
	void __fastcall SaveToStream(Classes::TStream* Stream);
	void __fastcall LoadFromStream(Classes::TStream* Stream);
	void __fastcall SaveToFile(const AnsiString FileName);
	void __fastcall LoadFromFile(const AnsiString FileName);
	__property bool AutoIndent = {read=FAutoIndent, write=FAutoIndent, nodefault};
	__property TfsXMLItem* Root = {read=FRoot};
};


class DELPHICLASS TfsXMLReader;
class PASCALIMPLEMENTATION TfsXMLReader : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	char *FBuffer;
	int FBufPos;
	int FBufEnd;
	__int64 FPosition;
	__int64 FSize;
	Classes::TStream* FStream;
	void __fastcall SetPosition(const __int64 Value);
	void __fastcall ReadBuffer(void);
	void __fastcall ReadItem(AnsiString &Name, AnsiString &Text);
	
public:
	__fastcall TfsXMLReader(Classes::TStream* Stream);
	__fastcall virtual ~TfsXMLReader(void);
	void __fastcall RaiseException(void);
	void __fastcall ReadHeader(void);
	void __fastcall ReadRootItem(TfsXMLItem* Item);
	__property __int64 Position = {read=FPosition, write=SetPosition};
	__property __int64 Size = {read=FSize};
};


class DELPHICLASS TfsXMLWriter;
class PASCALIMPLEMENTATION TfsXMLWriter : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	bool FAutoIndent;
	AnsiString FBuffer;
	Classes::TStream* FStream;
	Classes::TStream* FTempStream;
	void __fastcall FlushBuffer(void);
	void __fastcall WriteLn(const AnsiString s);
	void __fastcall WriteItem(TfsXMLItem* Item, int Level = 0x0);
	
public:
	__fastcall TfsXMLWriter(Classes::TStream* Stream);
	void __fastcall WriteHeader(void);
	void __fastcall WriteRootItem(TfsXMLItem* RootItem);
	__property Classes::TStream* TempStream = {read=FTempStream, write=FTempStream};
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TfsXMLWriter(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE AnsiString __fastcall StrToXML(const AnsiString s);
extern PACKAGE AnsiString __fastcall XMLToStr(const AnsiString s);
extern PACKAGE AnsiString __fastcall ValueToXML(const Variant &Value);

}	/* namespace Fs_xml */
using namespace Fs_xml;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fs_xml
