// Borland C++ Builder
// Copyright (c) 1995, 2005 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Fs_iparser.pas' rev: 10.00

#ifndef Fs_iparserHPP
#define Fs_iparserHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Sysutils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Fs_iparser
{
//-- type declarations -------------------------------------------------------
typedef Set<char, 0, 255>  TfsIdentifierCharset;

class DELPHICLASS TfsParser;
class PASCALIMPLEMENTATION TfsParser : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	AnsiString FCommentBlock1;
	AnsiString FCommentBlock11;
	AnsiString FCommentBlock12;
	AnsiString FCommentBlock2;
	AnsiString FCommentBlock21;
	AnsiString FCommentBlock22;
	AnsiString FCommentLine1;
	AnsiString FCommentLine2;
	AnsiString FHexSequence;
	TfsIdentifierCharset FIdentifierCharset;
	Classes::TStrings* FKeywords;
	int FLastPosition;
	int FPosition;
	int FSize;
	AnsiString FSkipChar;
	bool FSkipEOL;
	bool FSkipSpace;
	AnsiString FStringQuotes;
	AnsiString FText;
	bool __fastcall DoDigitSequence(void);
	bool __fastcall DoHexDigitSequence(void);
	bool __fastcall DoScaleFactor(void);
	bool __fastcall DoUnsignedInteger(void);
	bool __fastcall DoUnsignedReal(void);
	void __fastcall SetPosition(const int Value);
	void __fastcall SetText(const AnsiString Value);
	AnsiString __fastcall Ident();
	void __fastcall SetCommentBlock1(const AnsiString Value);
	void __fastcall SetCommentBlock2(const AnsiString Value);
	
public:
	__fastcall TfsParser(void);
	__fastcall virtual ~TfsParser(void);
	void __fastcall ConstructCharset(const AnsiString s);
	void __fastcall SkipSpaces(void);
	bool __fastcall GetEOL(void);
	AnsiString __fastcall GetIdent();
	AnsiString __fastcall GetChar();
	AnsiString __fastcall GetWord();
	AnsiString __fastcall GetNumber();
	AnsiString __fastcall GetString();
	AnsiString __fastcall GetFRString();
	AnsiString __fastcall GetXYPosition();
	bool __fastcall IsKeyWord(const AnsiString s);
	__property AnsiString CommentBlock1 = {read=FCommentBlock1, write=SetCommentBlock1};
	__property AnsiString CommentBlock2 = {read=FCommentBlock2, write=SetCommentBlock2};
	__property AnsiString CommentLine1 = {read=FCommentLine1, write=FCommentLine1};
	__property AnsiString CommentLine2 = {read=FCommentLine2, write=FCommentLine2};
	__property AnsiString HexSequence = {read=FHexSequence, write=FHexSequence};
	__property TfsIdentifierCharset IdentifierCharset = {read=FIdentifierCharset, write=FIdentifierCharset};
	__property Classes::TStrings* Keywords = {read=FKeywords};
	__property AnsiString SkipChar = {read=FSkipChar, write=FSkipChar};
	__property bool SkipEOL = {read=FSkipEOL, write=FSkipEOL, nodefault};
	__property bool SkipSpace = {read=FSkipSpace, write=FSkipSpace, nodefault};
	__property AnsiString StringQuotes = {read=FStringQuotes, write=FStringQuotes};
	__property int Position = {read=FPosition, write=SetPosition, nodefault};
	__property AnsiString Text = {read=FText, write=SetText};
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Fs_iparser */
using namespace Fs_iparser;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fs_iparser
