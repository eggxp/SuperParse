// CodeGear C++Builder
// Copyright (c) 1995, 2009 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Dcrhexeditor.pas' rev: 21.00

#ifndef DcrhexeditorHPP
#define DcrhexeditorHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Sysutils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Inifiles.hpp>	// Pascal unit
#include <Grids.hpp>	// Pascal unit
#include <Types.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <Stdctrls.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Dcrhexeditor
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TMPHHightlightFieldType { hftUnknown, hftCountBytesIncl, hftCountCharsIncl, hftCountBytesExcl, hftCountCharsExcl, hftAnsiText, hftWideText };
#pragma option pop

typedef Grids::TGridCoord TGridCoord;

#pragma option push -b-
enum TMPHCharConvType { cctFromAnsi, cctToAnsi };
#pragma option pop

typedef StaticArray<char, 256> TMPHCharConvTable;

typedef StaticArray<StaticArray<char, 256>, 2> TMPHCharConv;

typedef StaticArray<System::UnicodeString, 7> Dcrhexeditor__1;

class DELPHICLASS EMPHexEditor;
class PASCALIMPLEMENTATION EMPHexEditor : public Sysutils::Exception
{
	typedef Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EMPHexEditor(const System::UnicodeString Msg) : Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EMPHexEditor(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	/* Exception.CreateRes */ inline __fastcall EMPHexEditor(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	/* Exception.CreateResFmt */ inline __fastcall EMPHexEditor(int Ident, System::TVarRec const *Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	/* Exception.CreateHelp */ inline __fastcall EMPHexEditor(const System::UnicodeString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EMPHexEditor(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EMPHexEditor(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EMPHexEditor(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EMPHexEditor(void) { }
	
};


struct TMPHBookmark
{
	
public:
	__int64 mPosition;
	bool mInCharField;
};


typedef StaticArray<TMPHBookmark, 10> TMPHBookmarks;

#pragma option push -b-
enum TMPHCaretKind { ckFull, ckLeft, ckBottom, ckAuto };
#pragma option pop

#pragma option push -b-
enum TMPHTranslationKind { tkAsIs, tkDos8, tkASCII, tkMac, tkBCD, tkCustom };
#pragma option pop

#pragma option push -b-
enum TMPHProgressKind { pkLoad, pkSave, pkFind };
#pragma option pop

typedef void __fastcall (__closure *TMPHProgressEvent)(System::TObject* Sender, const TMPHProgressKind ProgressType, const Sysutils::TFileName aName, const System::Byte Percent, bool &Cancel);

typedef void __fastcall (__closure *TMPHGetData)(System::TObject* Sender, const __int64 Offset, System::Byte &Data);

typedef void __fastcall (__closure *TMPHGetOffsetTextEvent)(System::TObject* Sender, const __int64 Number, System::AnsiString &OffsetText);

typedef void __fastcall (__closure *TMPHFindEvent)(System::TObject* Sender, const char * Pattern, const __int64 PatLength, const __int64 SearchFrom, const __int64 SearchUntil, const bool IgnoreCase, const char Wildcard, __int64 &FoundPos);

typedef StaticArray<char, 63734> TMPHFindTable;

typedef TMPHFindTable *PMPHFindTable;

#pragma option push -b-
enum TMPHUndoFlag { ufKindBytesChanged, ufKindByteRemoved, ufKindInsertBuffer, ufKindReplace, ufKindAppendBuffer, ufKindNibbleInsert, ufKindNibbleDelete, ufKindConvert, ufKindSelection, ufKindCombined, ufKindAllData, ufFlagByte1Changed, ufFlagByte2Changed, ufFlagModified, ufFlag2ndByteCol, ufFlagInCharField, ufFlagHasSelection, ufFlagInsertMode, ufFlagIsUnicode, ufFlagIsUnicodeBigEndian, ufFlagHasDescription };
#pragma option pop

typedef Set<TMPHUndoFlag, ufKindBytesChanged, ufFlagHasDescription>  TMPHUndoFlags;

class DELPHICLASS TMPHColors;
class PASCALIMPLEMENTATION TMPHColors : public Classes::TPersistent
{
	typedef Classes::TPersistent inherited;
	
private:
	Controls::TControl* FParent;
	Graphics::TColor FOffset;
	Graphics::TColor FOddColumn;
	Graphics::TColor FEvenColumn;
	Graphics::TColor FCursorFrame;
	Graphics::TColor FNonFocusCursorFrame;
	Graphics::TColor FBackground;
	Graphics::TColor FChangedText;
	Graphics::TColor FChangedBackground;
	Graphics::TColor FCurrentOffsetBackground;
	Graphics::TColor FOffsetBackground;
	Graphics::TColor FActiveFieldBackground;
	Graphics::TColor FCurrentOffset;
	Graphics::TColor FGrid;
	void __fastcall SetOffsetBackground(const Graphics::TColor Value);
	void __fastcall SetCurrentOffset(const Graphics::TColor Value);
	void __fastcall SetParent(const Controls::TControl* Value);
	void __fastcall SetGrid(const Graphics::TColor Value);
	void __fastcall SetBackground(const Graphics::TColor Value);
	void __fastcall SetChangedBackground(const Graphics::TColor Value);
	void __fastcall SetChangedText(const Graphics::TColor Value);
	void __fastcall SetCursorFrame(const Graphics::TColor Value);
	void __fastcall SetEvenColumn(const Graphics::TColor Value);
	void __fastcall SetOddColumn(const Graphics::TColor Value);
	void __fastcall SetOffset(const Graphics::TColor Value);
	void __fastcall SetActiveFieldBackground(const Graphics::TColor Value);
	void __fastcall SetCurrentOffsetBackground(const Graphics::TColor Value);
	void __fastcall SetNonFocusCursorFrame(const Graphics::TColor Value);
	
public:
	__fastcall TMPHColors(Controls::TControl* Parent);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	__property Controls::TControl* Parent = {read=FParent, write=SetParent};
	
__published:
	__property Graphics::TColor Background = {read=FBackground, write=SetBackground, nodefault};
	__property Graphics::TColor ChangedBackground = {read=FChangedBackground, write=SetChangedBackground, nodefault};
	__property Graphics::TColor ChangedText = {read=FChangedText, write=SetChangedText, nodefault};
	__property Graphics::TColor CursorFrame = {read=FCursorFrame, write=SetCursorFrame, nodefault};
	__property Graphics::TColor Offset = {read=FOffset, write=SetOffset, nodefault};
	__property Graphics::TColor OddColumn = {read=FOddColumn, write=SetOddColumn, nodefault};
	__property Graphics::TColor EvenColumn = {read=FEvenColumn, write=SetEvenColumn, nodefault};
	__property Graphics::TColor CurrentOffsetBackground = {read=FCurrentOffsetBackground, write=SetCurrentOffsetBackground, nodefault};
	__property Graphics::TColor OffsetBackground = {read=FOffsetBackground, write=SetOffsetBackground, nodefault};
	__property Graphics::TColor CurrentOffset = {read=FCurrentOffset, write=SetCurrentOffset, nodefault};
	__property Graphics::TColor Grid = {read=FGrid, write=SetGrid, nodefault};
	__property Graphics::TColor NonFocusCursorFrame = {read=FNonFocusCursorFrame, write=SetNonFocusCursorFrame, nodefault};
	__property Graphics::TColor ActiveFieldBackground = {read=FActiveFieldBackground, write=SetActiveFieldBackground, nodefault};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TMPHColors(void) { }
	
};


class DELPHICLASS TMPHMemoryStream;
class PASCALIMPLEMENTATION TMPHMemoryStream : public Classes::TMemoryStream
{
	typedef Classes::TMemoryStream inherited;
	
private:
	void * __fastcall PointerAt(const __int64 APosition, const __int64 ACount);
	
public:
	System::PByte __fastcall GetAddress(const __int64 AIndex, const __int64 ACount);
	void __fastcall ReadBufferAt(void *Buffer, const __int64 APosition, const __int64 ACount);
	void __fastcall WriteBufferAt(const void *Buffer, const __int64 APosition, const __int64 ACount);
	void __fastcall Move(const __int64 AFromPos, const __int64 AToPos, const __int64 ACount);
	void __fastcall TranslateToAnsi(const TMPHTranslationKind AFromTranslation, const __int64 APosition, const __int64 ACount);
	void __fastcall TranslateFromAnsi(const TMPHTranslationKind AToTranslation, const __int64 APosition, const __int64 ACount);
	System::AnsiString __fastcall GetAsHex(const __int64 APosition, const __int64 ACount, const bool SwapNibbles);
public:
	/* TMemoryStream.Destroy */ inline __fastcall virtual ~TMPHMemoryStream(void) { }
	
public:
	/* TObject.Create */ inline __fastcall TMPHMemoryStream(void) : Classes::TMemoryStream() { }
	
};


#pragma option push -b-
enum TMPHOffsetFormatFlag { offCalcWidth, offCalcRow, offCalcColumn, offBytesPerUnit };
#pragma option pop

typedef Set<TMPHOffsetFormatFlag, offCalcWidth, offBytesPerUnit>  TMPHOffsetFormatFlags;

struct TMPHOffsetFormat
{
	
public:
	System::UnicodeString Format;
	System::AnsiString Prefix;
	System::AnsiString Suffix;
	int MinWidth;
	TMPHOffsetFormatFlags Flags;
	System::Byte Radix;
	System::Byte _BytesPerUnit;
};


typedef void __fastcall (__closure *TMPHDrawCellEvent)(System::TObject* Sender, Graphics::TCanvas* ACanvas, int ACol, int ARow, System::WideString &AWideText, const Types::TRect &ARect, bool &ADefaultDraw);

struct TColorHighlightArea
{
	
public:
	unsigned StartOffset;
	unsigned EndOffset;
	bool UseForegroundColor;
	bool UseBackgroundColor;
	Graphics::TColor ForegroundColor;
	Graphics::TColor BackgroundColor;
	System::UnicodeString FieldName;
	TMPHHightlightFieldType FieldType;
};


class DELPHICLASS TCustomMPHexEditor;
class DELPHICLASS TMPHUndoStorage;
class PASCALIMPLEMENTATION TCustomMPHexEditor : public Grids::TCustomGrid
{
	typedef Grids::TCustomGrid inherited;
	
private:
	typedef DynamicArray<TColorHighlightArea> _TCustomMPHexEditor__1;
	
	typedef DynamicArray<int> _TCustomMPHexEditor__2;
	
	
private:
	_TCustomMPHexEditor__1 FColorHighlightAreas;
	bool FIsViewSyncing;
	__int64 FIntLastHexCol;
	TMPHFindTable FFindTable;
	TMPHFindTable FFindTableI;
	bool FIsMaxOffset;
	bool FFindProgress;
	__int64 FBlockSize;
	bool FSepCharBlocks;
	TMPHGetOffsetTextEvent FOnGetOffsetText;
	TMPHGetData FOnData;
	bool FFixedFileSize;
	int FCharWidth;
	int FCharHeight;
	Controls::TImageList* FBookmarkImageList;
	bool FInsertModeOn;
	Graphics::TBitmap* FCaretBitmap;
	TMPHColors* FColors;
	int FBytesPerRow;
	int FOffSetDisplayWidth;
	int FBytesPerRowDup;
	TMPHMemoryStream* FDataStorage;
	int FSwapNibbles;
	bool FFocusFrame;
	bool FIsFileReadonly;
	int FBytesPerCol;
	bool FPosInCharField;
	bool FLastPosInCharField;
	System::UnicodeString FFileName;
	Classes::TBits* FModifiedBytes;
	TMPHBookmarks FBookmarks;
	__int64 FSelStart;
	__int64 FSelPosition;
	__int64 FSelEnd;
	__int64 FSelBeginPosition;
	TMPHTranslationKind FTranslation;
	TMPHCaretKind FCaretKind;
	char FReplaceUnprintableCharsBy;
	bool FAllowInsertMode;
	bool FWantTabs;
	bool FReadOnlyView;
	bool FHideSelection;
	bool FGraySelOnLostFocus;
	TMPHProgressEvent FOnProgress;
	int FMouseDownCol;
	int FMouseDownRow;
	bool FShowDrag;
	int FDropCol;
	int FDropRow;
	Classes::TNotifyEvent FOnInvalidKey;
	Classes::TNotifyEvent FOnTopLeftChanged;
	bool FAutoBytesPerRow;
	bool FSetAutoBytesPerRow;
	bool FDrawGridLines;
	bool FDrawGutter3D;
	int FGutterWidth;
	TMPHOffsetFormat FOffsetFormat;
	bool FSelectionPossible;
	Graphics::TBitmap* FBookmarkBitmap;
	_TCustomMPHexEditor__2 FCursorList;
	bool FHasCustomBMP;
	System::UnicodeString FStreamFileName;
	bool FHasFile;
	int FMaxUndo;
	StaticArray<char, 16> FHexChars;
	bool FHexLowerCase;
	Classes::TNotifyEvent FOnChange;
	bool FShowRuler;
	int FBytesPerUnit;
	int FRulerBytesPerUnit;
	Classes::TNotifyEvent FOnSelectionChanged;
	int FSelectionChangedCount;
	bool FShowPositionIfNotFocused;
	bool FOffsetHandler;
	int FUsedRulerBytesPerUnit;
	bool FIsSelecting;
	bool FMouseUpCanResetSel;
	TMPHUndoStorage* FUndoStorage;
	bool FUnicodeCharacters;
	bool FUnicodeBigEndian;
	Sysutils::TSysCharSet FMaskedChars;
	__int64 FDrawDataPosition;
	bool FDrawDataPositionIsHex;
	TMPHDrawCellEvent FOnDrawCell;
	Classes::TNotifyEvent FOnBookmarkChanged;
	bool FIsDrawDataSelected;
	TMPHFindEvent FOnWildcardFind;
	TMPHFindEvent FOnFind;
	System::Byte FSetDataSizeFillByte;
	System::Byte FRulerNumberBase;
	unsigned FDisplayOffset;
	bool FDrawGutterGradient;
	bool FOwnerData;
	void __fastcall SetDrawGutterGradient(const bool Value);
	void __fastcall SetOwnerData(const bool Value);
	TColorHighlightArea __fastcall GetColorHighlightArea(int AAreaIndex);
	__property Color = {default=-16777211};
	bool __fastcall IsInsertModePossible(void);
	void __fastcall RecalcBytesPerRow(void);
	bool __fastcall IsFileSizeFixed(void);
	void __fastcall InternalErase(const bool AKeyWasBackspace, const System::UnicodeString AUndoDesc = L"");
	void __fastcall SetReadOnlyView(const bool Value);
	void __fastcall SetCaretKind(const TMPHCaretKind Value);
	void __fastcall SetFocusFrame(const bool Value);
	void __fastcall SetBytesPerColumn(const int Value);
	void __fastcall SetSwapNibbles(const bool Value);
	bool __fastcall GetSwapNibbles(void);
	int __fastcall GetBytesPerColumn(void);
	void __fastcall SetOffsetDisplayWidth(void);
	void __fastcall SetColors(const TMPHColors* Value);
	void __fastcall SetReadOnlyFile(const bool Value);
	void __fastcall SetTranslation(const TMPHTranslationKind Value);
	void __fastcall SetModified(const bool Value);
	void __fastcall SetChanged(__int64 ADataPos, const bool Value);
	void __fastcall SetFixedFileSize(const bool Value);
	void __fastcall SetAllowInsertMode(const bool Value);
	bool __fastcall GetInsertMode(void);
	void __fastcall SetWantTabs(const bool Value);
	void __fastcall SetHideSelection(const bool Value);
	void __fastcall SetGraySelectionIfNotFocused(const bool Value);
	__int64 __fastcall CalcColCount(void);
	__int64 __fastcall GetLastCharCol(void);
	__int64 __fastcall GetPropColCount(void);
	__int64 __fastcall GetPropRowCount(void);
	bool __fastcall GetMouseOverSelection(void);
	bool __fastcall CursorOverSelection(const __int64 AX, const __int64 AY);
	bool __fastcall MouseOverFixed(const __int64 AX, const __int64 AY);
	void __fastcall AdjustBookmarks(const __int64 AFrom, const __int64 AOffset);
	void __fastcall IntSetCaretPos(const __int64 AX, const __int64 AY, const __int64 ACol);
	void __fastcall TruncMaxPosition(__int64 &ADataPos);
	HIDESBASE void __fastcall SetSelection(__int64 ADataPos, __int64 AStartPos, __int64 AEndPos);
	int __fastcall GetCurrentValue(void);
	void __fastcall SetInsertMode(const bool Value);
	bool __fastcall GetModified(void);
	void __fastcall SetBytesPerRow(const int Value);
	void __fastcall SetMaskChar(const char Value);
	void __fastcall SetAsText(const System::AnsiString Value);
	void __fastcall SetAsHex(const System::AnsiString Value);
	System::AnsiString __fastcall GetAsText(void);
	System::AnsiString __fastcall GetAsHex(void);
	HIDESBASE MESSAGE void __fastcall WMTimer(Messages::TWMTimer &Msg);
	void __fastcall CheckSetCaret(void);
	__int64 __fastcall GetRow(const __int64 ADataPos);
	void __fastcall WrongKey(void);
	void __fastcall CreateCaretGlyph(void);
	__int64 __fastcall GetSelStart(void);
	__int64 __fastcall GetSelEnd(void);
	__int64 __fastcall GetSelCount(void);
	void __fastcall SetSelStart(__int64 AValue);
	void __fastcall SetSelEnd(__int64 AValue);
	void __fastcall SetSelCount(__int64 AValue);
	void __fastcall SetInCharField(const bool Value);
	bool __fastcall GetInCharField(void);
	void __fastcall InternalInsertBuffer(char * ABuffer, const __int64 ASize, const __int64 APosition);
	void __fastcall InternalAppendBuffer(char * ABuffer, const __int64 ASize);
	void __fastcall InternalGetCurSel(__int64 &AStartPos, __int64 &AEndPos, __int64 &ACol, __int64 &ARow);
	void __fastcall InternalDelete(__int64 AStartPos, __int64 AEndPos, __int64 ACol, __int64 ARow);
	bool __fastcall InternalDeleteNibble(const __int64 APos, const bool AHighNibble);
	bool __fastcall InternalInsertNibble(const __int64 APos, const bool AHighNibble);
	Classes::TFileStream* __fastcall CreateShift4BitStream(const __int64 AStartPos, Sysutils::TFileName &AFilename);
	void __fastcall InternalConvertRange(const __int64 AFrom, const __int64 ATo, const TMPHTranslationKind ATransFrom, const TMPHTranslationKind ATransTo);
	void __fastcall MoveFileMem(const __int64 AFrom, const __int64 ATo, const __int64 ACount);
	TMPHBookmark __fastcall GetBookmark(System::Byte AIndex);
	void __fastcall SetBookmark(System::Byte AIndex, const TMPHBookmark &Value);
	void __fastcall SetBookmarkVals(const System::Byte AIndex, const __int64 APosition, const bool AInCharField);
	void __fastcall SetDrawGridLines(const bool Value);
	void __fastcall SetGutterWidth(const int Value);
	void __fastcall BookmarkBitmapChanged(System::TObject* Sender);
	void __fastcall SetBookmarkBitmap(const Graphics::TBitmap* Value);
	System::UnicodeString __fastcall GetVersion(void);
	void __fastcall SetVersion(const System::UnicodeString Value);
	void __fastcall FreeStorage(bool AFreeUndo = false);
	bool __fastcall GetCanUndo(void);
	bool __fastcall GetCanRedo(void);
	System::UnicodeString __fastcall GetUndoDescription(void);
	System::UnicodeString __fastcall GetOffsetFormat(void);
	void __fastcall SetOffsetFormat(const System::UnicodeString Value);
	void __fastcall GenerateOffsetFormat(System::UnicodeString Value);
	void __fastcall SetHexLowerCase(const bool Value);
	void __fastcall SetDrawGutter3D(const bool Value);
	void __fastcall SetShowRuler(const bool Value);
	void __fastcall SetBytesPerUnit(const int Value);
	void __fastcall SetRulerString(void);
	void __fastcall CheckSelectUnit(__int64 &AStart, __int64 &AEnd);
	void __fastcall SetRulerBytesPerUnit(const int Value);
	void __fastcall SetShowPositionIfNotFocused(const bool Value);
	System::Byte __fastcall GetDataAt(__int64 AIndex);
	void __fastcall SetDataAt(__int64 AIndex, const System::Byte Value);
	void __fastcall SetUnicodeCharacters(const bool Value);
	void __fastcall SetUnicodeBigEndian(const bool Value);
	void __fastcall SetAutoBytesPerRow(const bool Value);
	int __fastcall GetPositionAtCursor(const int ACol, const int ARow);
	bool __fastcall GetIsCharFieldCol(const int ACol);
	void __fastcall SetDataSize(const __int64 Value);
	void __fastcall SetBlockSize(const __int64 Value);
	void __fastcall SetSepCharBlocks(const bool Value);
	void __fastcall SetFindProgress(const bool Value);
	void __fastcall SetRulerNumberBase(const System::Byte Value);
	void __fastcall SetMaskedChars(const Sysutils::TSysCharSet &Value);
	
protected:
	__int64 FOwnerDataSize;
	System::UnicodeString FRulerString;
	System::UnicodeString FRulerCharString;
	bool FFixedFileSizeOverride;
	bool FModified;
	virtual void __fastcall DoGetData(__int64 Offset, System::Byte &Data);
	virtual void __fastcall DrawCell(int ACol, int ARow, const Types::TRect &ARect, Grids::TGridDrawState AState);
	DYNAMIC bool __fastcall DoMouseWheelDown(Classes::TShiftState Shift, const Types::TPoint &MousePos);
	DYNAMIC bool __fastcall DoMouseWheelUp(Classes::TShiftState Shift, const Types::TPoint &MousePos);
	__property int UsedRulerBytesPerUnit = {read=FUsedRulerBytesPerUnit, nodefault};
	__property bool IsSelecting = {read=FIsSelecting, nodefault};
	__property bool MouseUpCanResetSel = {read=FMouseUpCanResetSel, write=FMouseUpCanResetSel, nodefault};
	__property TMPHUndoStorage* UndoStorage = {read=FUndoStorage};
	__property TMPHMemoryStream* DataStorage = {read=FDataStorage};
	virtual void __fastcall SelectionChanged(void);
	void __fastcall NewSelection(__int64 ASelFrom, __int64 ASelTo);
	Grids::TGridCoord __fastcall CheckMouseCoord(int &X, int &Y);
	void __fastcall CheckUnit(__int64 &AValue);
	HIDESBASE virtual void __fastcall Changed(void);
	__int64 __fastcall DropPosition(void);
	void __fastcall Stream2Stream(Classes::TStream* AStreamFrom, Classes::TStream* AStreamTo, const TMPHProgressKind AOperation, const __int64 ACount = 0xffffffffffffffff);
	virtual void __fastcall PrepareOverwriteDiskFile(void);
	void __fastcall WaitCursor(void);
	void __fastcall OldCursor(void);
	virtual void __fastcall Paint(void);
	DYNAMIC void __fastcall TopLeftChanged(void);
	void __fastcall AdjustMetrics(void);
	__int64 __fastcall GetDataSize(void);
	void __fastcall CalcSizes(void);
	virtual bool __fastcall SelectCell(int ACol, int ARow);
	__int64 __fastcall GetPosAtCursor(const __int64 ACol, const __int64 ARow);
	Grids::TGridCoord __fastcall GetCursorAtPos(const __int64 APos, const bool aChars);
	__int64 __fastcall GetOtherFieldCol(const __int64 ACol);
	__int64 __fastcall GetOtherFieldColCheck(const __int64 ACol);
	bool __fastcall CheckSelectCell(__int64 ACol, __int64 ARow);
	HIDESBASE MESSAGE void __fastcall WMChar(Messages::TWMKey &Msg);
	MESSAGE void __fastcall WMImeChar(Messages::TWMKey &Msg);
	MESSAGE void __fastcall CMINTUPDATECARET(Messages::TMessage &Msg);
	MESSAGE void __fastcall CMSelectionChanged(Messages::TMessage &Msg);
	HIDESBASE MESSAGE void __fastcall WMGetDlgCode(Messages::TWMNoParams &Msg);
	HIDESBASE MESSAGE void __fastcall CMFontChanged(Messages::TMessage &message);
	void __fastcall IntChangeByte(const System::Byte aOldByte, const System::Byte aNewByte, __int64 APos, __int64 ACol, __int64 ARow, const System::UnicodeString UndoDesc = L"");
	void __fastcall IntChangeWideChar(const System::WideChar aOldChar, const System::WideChar aNewChar, __int64 APos, __int64 ACol, __int64 ARow, const System::UnicodeString UndoDesc = L"");
	DYNAMIC void __fastcall KeyDown(System::Word &Key, Classes::TShiftState Shift);
	bool __fastcall HasChanged(__int64 APosition);
	void __fastcall Select(const __int64 ACurCol, const __int64 ACurRow, const __int64 ANewCol, const __int64 ANewRow);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	virtual bool __fastcall CanCreateUndo(const TMPHUndoFlag aKind, const __int64 ACount, const __int64 aReplCount);
	void __fastcall CreateUndo(const TMPHUndoFlag aKind, const __int64 APos, const __int64 ACount, const __int64 aReplCount, const System::UnicodeString sDesc = L"");
	virtual void __fastcall Loaded(void);
	virtual void __fastcall CreateWnd(void);
	HIDESBASE MESSAGE void __fastcall WMSetFocus(Messages::TWMSetFocus &Msg);
	HIDESBASE MESSAGE void __fastcall WMKillFocus(Messages::TWMKillFocus &Msg);
	HIDESBASE MESSAGE void __fastcall WMVScroll(Messages::TWMScroll &Msg);
	HIDESBASE MESSAGE void __fastcall WMHScroll(Messages::TWMScroll &Msg);
	DYNAMIC void __fastcall Resize(void);
	bool __fastcall HasCustomBookmarkBitmap(void);
	__property bool AutoBytesPerRow = {read=FAutoBytesPerRow, write=SetAutoBytesPerRow, default=0};
	__property int BytesPerRow = {read=FBytesPerRow, write=SetBytesPerRow, nodefault};
	__property bool FindProgress = {read=FFindProgress, write=SetFindProgress, default=0};
	__property int BytesPerColumn = {read=GetBytesPerColumn, write=SetBytesPerColumn, default=2};
	__property TMPHTranslationKind Translation = {read=FTranslation, write=SetTranslation, nodefault};
	__property System::UnicodeString OffsetFormat = {read=GetOffsetFormat, write=SetOffsetFormat};
	__property TMPHGetOffsetTextEvent OnGetOffsetText = {read=FOnGetOffsetText, write=FOnGetOffsetText};
	__property TMPHGetData OnData = {read=FOnData, write=FOnData};
	__property __int64 BytesPerBlock = {read=FBlockSize, write=SetBlockSize, default=-1};
	__property bool SeparateBlocksInCharField = {read=FSepCharBlocks, write=SetSepCharBlocks, default=1};
	__property TMPHCaretKind CaretKind = {read=FCaretKind, write=SetCaretKind, default=3};
	__property TMPHColors* Colors = {read=FColors, write=SetColors};
	__property bool FocusFrame = {read=FFocusFrame, write=SetFocusFrame, nodefault};
	__property bool SwapNibbles = {read=GetSwapNibbles, write=SetSwapNibbles, default=0};
	__property char MaskChar = {read=FReplaceUnprintableCharsBy, write=SetMaskChar, stored=false, nodefault};
	__property bool NoSizeChange = {read=FFixedFileSize, write=SetFixedFileSize, default=0};
	__property bool AllowInsertMode = {read=FAllowInsertMode, write=SetAllowInsertMode, default=1};
	__property bool WantTabs = {read=FWantTabs, write=SetWantTabs, default=1};
	__property bool ReadOnlyView = {read=FReadOnlyView, write=SetReadOnlyView, default=0};
	__property bool HideSelection = {read=FHideSelection, write=SetHideSelection, default=0};
	__property bool GraySelectionIfNotFocused = {read=FGraySelOnLostFocus, write=SetGraySelectionIfNotFocused, default=0};
	__property TMPHProgressEvent OnProgress = {read=FOnProgress, write=FOnProgress};
	__property Classes::TNotifyEvent OnInvalidKey = {read=FOnInvalidKey, write=FOnInvalidKey};
	__property Classes::TNotifyEvent OnTopLeftChanged = {read=FOnTopLeftChanged, write=FOnTopLeftChanged};
	System::AnsiString __fastcall GetSelectionAsHex(void);
	void __fastcall SetSelectionAsHex(const System::AnsiString AText);
	System::AnsiString __fastcall GetSelectionAsText(void);
	void __fastcall SetSelectionAsText(const System::AnsiString s);
	__property bool DrawGridLines = {read=FDrawGridLines, write=SetDrawGridLines, nodefault};
	__property int GutterWidth = {read=FGutterWidth, write=SetGutterWidth, default=-1};
	__property Graphics::TBitmap* BookmarkBitmap = {read=FBookmarkBitmap, write=SetBookmarkBitmap, stored=HasCustomBookmarkBitmap};
	__property System::UnicodeString Version = {read=GetVersion, write=SetVersion, stored=true};
	__property int MaxUndo = {read=FMaxUndo, write=FMaxUndo, default=1048576};
	__property bool InsertMode = {read=GetInsertMode, write=SetInsertMode, default=0};
	__property bool HexLowerCase = {read=FHexLowerCase, write=SetHexLowerCase, default=0};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property bool DrawGutter3D = {read=FDrawGutter3D, write=SetDrawGutter3D, default=1};
	__property bool DrawGutterGradient = {read=FDrawGutterGradient, write=SetDrawGutterGradient, default=1};
	__property bool OwnerData = {read=FOwnerData, write=SetOwnerData, default=0};
	__property bool ShowRuler = {read=FShowRuler, write=SetShowRuler, default=0};
	__property System::Byte RulerNumberBase = {read=FRulerNumberBase, write=SetRulerNumberBase, default=16};
	__property int BytesPerUnit = {read=FBytesPerUnit, write=SetBytesPerUnit, default=1};
	__property int RulerBytesPerUnit = {read=FRulerBytesPerUnit, write=SetRulerBytesPerUnit, default=-1};
	__property bool ShowPositionIfNotFocused = {read=FShowPositionIfNotFocused, write=SetShowPositionIfNotFocused, default=0};
	__property bool UnicodeChars = {read=FUnicodeCharacters, write=SetUnicodeCharacters, default=0};
	__property bool UnicodeBigEndian = {read=FUnicodeBigEndian, write=SetUnicodeBigEndian, default=0};
	__property Classes::TNotifyEvent OnSelectionChanged = {read=FOnSelectionChanged, write=FOnSelectionChanged};
	__property TMPHDrawCellEvent OnDrawCell = {read=FOnDrawCell, write=FOnDrawCell};
	virtual void __fastcall BookmarkChanged(void);
	void __fastcall DoSetCellWidth(const int AIndex, int AValue);
	virtual void __fastcall DefineProperties(Classes::TFiler* Filer);
	void __fastcall ReadMaskChar(Classes::TReader* Reader);
	void __fastcall ReadMaskChar_I(Classes::TReader* Reader);
	void __fastcall WriteMaskChar_I(Classes::TWriter* Writer);
	
public:
	__int64 __fastcall ColorHighlightAreaSize(void);
	void __fastcall ClearColorHighlightAreas(void);
	void __fastcall AddColorHighlightArea(unsigned StartOffset, unsigned EndOffset, bool UseForegroundColor, bool UseBackgroundColor, Graphics::TColor ForegroundColor, Graphics::TColor BackgroundColor, System::UnicodeString FieldName = L"", TMPHHightlightFieldType FieldType = (TMPHHightlightFieldType)(0x0));
	void __fastcall SaveColorHighlightAreas(System::UnicodeString Filename)/* overload */;
	void __fastcall SaveColorHighlightAreas(Inifiles::TCustomIniFile* IniFile)/* overload */;
	void __fastcall LoadColorHighlightAreas(System::UnicodeString Filename)/* overload */;
	void __fastcall LoadColorHighlightAreas(Inifiles::TCustomIniFile* IniFile)/* overload */;
	__property TColorHighlightArea ColorHighlightArea[int AreaIndex] = {read=GetColorHighlightArea};
	System::PByte __fastcall GetFastPointer(const int index, const int Count);
	__fastcall virtual TCustomMPHexEditor(Classes::TComponent* aOwner);
	__fastcall virtual ~TCustomMPHexEditor(void);
	__property Sysutils::TSysCharSet MaskedChars = {read=FMaskedChars, write=SetMaskedChars};
	__property __int64 DrawDataPosition = {read=FDrawDataPosition};
	__property bool IsDrawDataSelected = {read=FIsDrawDataSelected, nodefault};
	System::WideChar __fastcall GetMemory(const int index);
	DYNAMIC bool __fastcall CanFocus(void);
	void __fastcall SetMemory(const int index, const System::WideChar Value);
	__property bool IsMaxOffset = {read=FIsMaxOffset, nodefault};
	void __fastcall SeekToEOF(void);
	void __fastcall SyncView(TCustomMPHexEditor* Source, int SyncOffset = 0x0);
	int __fastcall DisplayStart(void);
	int __fastcall DisplayEnd(void);
	bool __fastcall IsSelected(const __int64 APosition);
	__property int PositionAtCursor[const int ACol][const int ARow] = {read=GetPositionAtCursor};
	__property bool IsCharFieldCol[const int ACol] = {read=GetIsCharFieldCol};
	__property System::Byte SetDataSizeFillByte = {read=FSetDataSizeFillByte, write=FSetDataSizeFillByte, nodefault};
	__property bool HasFile = {read=FHasFile, write=FHasFile, nodefault};
	virtual int __fastcall UndoBeginUpdate(void);
	virtual int __fastcall UndoEndUpdate(void);
	void __fastcall ResetSelection(const bool aDraw);
	__property System::AnsiString SelectionAsHex = {read=GetSelectionAsHex, write=SetSelectionAsHex};
	__property System::AnsiString SelectionAsText = {read=GetSelectionAsText, write=SetSelectionAsText};
	__property TMPHFindEvent OnFind = {read=FOnFind, write=FOnFind};
	__property TMPHFindEvent OnWildcardFind = {read=FOnWildcardFind, write=FOnWildcardFind};
	virtual System::AnsiString __fastcall GetOffsetString(const __int64 APosition);
	virtual System::AnsiString __fastcall GetAnyOffsetString(const __int64 APosition);
	int __fastcall RowHeight(void);
	void __fastcall ResetUndo(void);
	__int64 __fastcall Seek(const __int64 AOffset, const __int64 AOrigin);
	__int64 __fastcall Find(char * ABuffer, __int64 ACount, const __int64 AStart, const __int64 AEnd, const bool IgnoreCase);
	__int64 __fastcall FindWithWildcard(char * ABuffer, int ACount, const int AStart, const int AEnd, const bool IgnoreCase, const char Wildcard);
	void __fastcall AddSelectionUndo(const __int64 AStart, const __int64 ACount);
	System::AnsiString __fastcall PrepareFindReplaceData(System::AnsiString StrData, const bool IgnoreCase, const bool IsText);
	void __fastcall ReadBuffer(void *ABuffer, const __int64 AIndex, const __int64 ACount);
	virtual void __fastcall WriteBuffer(const void *ABuffer, const __int64 AIndex, const __int64 ACount);
	void __fastcall DeleteSelection(const System::UnicodeString UndoDesc = L"");
	void __fastcall LoadFromStream(Classes::TStream* Strm);
	void __fastcall LoadFromFile(const System::UnicodeString Filename);
	void __fastcall SaveToStream(Classes::TStream* Strm);
	void __fastcall SaveToFile(const System::UnicodeString Filename, const bool aUnModify = true);
	void __fastcall SaveRangeToStream(Classes::TStream* Strm, const int APosition, const int ACount);
	bool __fastcall Undo(void);
	bool __fastcall Redo(void);
	void __fastcall CreateEmptyFile(const System::UnicodeString TempName);
	char * __fastcall BufferFromFile(const __int64 APos, __int64 &ACount);
	void __fastcall InsertBuffer(char * ABuffer, const __int64 ASize, const __int64 APos, const System::UnicodeString UndoDesc = L"", const bool MoveCursor = true);
	void __fastcall AppendBuffer(char * ABuffer, const __int64 ASize, const System::UnicodeString UndoDesc = L"", const bool MoveCursor = true);
	void __fastcall ReplaceSelection(char * ABuffer, __int64 ASize, const System::UnicodeString UndoDesc = L"", const bool MoveCursor = true);
	int __fastcall Replace(char * ABuffer, __int64 APosition, __int64 aOldCount, __int64 aNewCount, const System::UnicodeString UndoDesc = L"", const bool MoveCursor = false);
	__int64 __fastcall GetCursorPos(void);
	bool __fastcall DeleteNibble(const __int64 APos, const bool HighNibble, const System::UnicodeString UndoDesc = L"");
	bool __fastcall InsertNibble(const __int64 APos, const bool HighNibble, const System::UnicodeString UndoDesc = L"");
	void __fastcall ConvertRange(const __int64 AFrom, const __int64 ATo, const TMPHTranslationKind ATransFrom, const TMPHTranslationKind ATransTo, const System::UnicodeString UndoDesc = L"");
	int __fastcall GetTopLeftPosition(bool &oInCharField);
	void __fastcall SetTopLeftPosition(const __int64 APosition, const bool AInCharField);
	int __fastcall ShowDragCell(const int X, const int Y);
	void __fastcall HideDragCell(void);
	void __fastcall CombineUndo(const int ACount, const System::UnicodeString sDesc = L"");
	char __fastcall TranslateToAnsiChar(const System::Byte aByte);
	char __fastcall TranslateFromAnsiChar(const System::Byte aByte);
	__property __int64 SelStart = {read=GetSelStart, write=SetSelStart};
	__property __int64 SelEnd = {read=GetSelEnd, write=SetSelEnd};
	__property __int64 SelCount = {read=GetSelCount, write=SetSelCount};
	__property bool CanUndo = {read=GetCanUndo, nodefault};
	__property bool CanRedo = {read=GetCanRedo, nodefault};
	__property bool InCharField = {read=GetInCharField, write=SetInCharField, nodefault};
	__property System::UnicodeString UndoDescription = {read=GetUndoDescription};
	__property bool ReadOnlyFile = {read=FIsFileReadonly, write=SetReadOnlyFile, nodefault};
	__property bool Modified = {read=GetModified, write=SetModified, nodefault};
	__property __int64 DataSize = {read=GetDataSize, write=SetDataSize};
	__property System::Byte Data[__int64 AIndex] = {read=GetDataAt, write=SetDataAt};
	__property System::AnsiString AsText = {read=GetAsText, write=SetAsText};
	__property System::AnsiString AsHex = {read=GetAsHex, write=SetAsHex};
	__property System::UnicodeString Filename = {read=FFileName, write=FFileName};
	__property TMPHBookmark Bookmark[System::Byte AIndex] = {read=GetBookmark, write=SetBookmark};
	__property bool ByteChanged[__int64 AIndex] = {read=HasChanged, write=SetChanged};
	__property __int64 ColCountRO = {read=GetPropColCount};
	__property __int64 RowCountRO = {read=GetPropRowCount};
	__property bool MouseOverSelection = {read=GetMouseOverSelection, nodefault};
	__property int CurrentValue = {read=GetCurrentValue, nodefault};
	void __fastcall SelectAll(void);
	__property VisibleColCount;
	__property VisibleRowCount;
	__property Canvas;
	__property Col;
	__property LeftCol;
	__property Row;
	__property TopRow;
	__property unsigned DisplayOffset = {read=FDisplayOffset, write=FDisplayOffset, nodefault};
	__property Classes::TNotifyEvent OnBookmarkChanged = {read=FOnBookmarkChanged, write=FOnBookmarkChanged};
	bool __fastcall GotoBookmark(const int index);
	void __fastcall UpdateGetOffsetText(void);
	void __fastcall CenterCursorPosition(void);
public:
	/* TWinControl.CreateParented */ inline __fastcall TCustomMPHexEditor(HWND ParentWindow) : Grids::TCustomGrid(ParentWindow) { }
	
};


class DELPHICLASS TMPHexEditor;
class PASCALIMPLEMENTATION TMPHexEditor : public TCustomMPHexEditor
{
	typedef TCustomMPHexEditor inherited;
	
__published:
	__property Align = {default=0};
	__property Anchors = {default=3};
	__property BiDiMode;
	__property BorderStyle = {default=1};
	__property Constraints;
	__property Ctl3D;
	__property DragCursor = {default=-12};
	__property DragKind = {default=0};
	__property DragMode = {default=0};
	__property Enabled = {default=1};
	__property Font;
	__property ImeMode = {default=3};
	__property ImeName;
	__property OnClick;
	__property OnDblClick;
	__property OnDragDrop;
	__property OnDragOver;
	__property OnEndDock;
	__property OnEndDrag;
	__property OnEnter;
	__property OnExit;
	__property OnKeyDown;
	__property OnKeyPress;
	__property OnKeyUp;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheel;
	__property OnMouseWheelDown;
	__property OnMouseWheelUp;
	__property OnStartDock;
	__property OnStartDrag;
	__property ParentBiDiMode = {default=1};
	__property ParentCtl3D = {default=1};
	__property ParentFont = {default=1};
	__property ParentShowHint = {default=1};
	__property PopupMenu;
	__property ScrollBars = {default=3};
	__property ShowHint;
	__property TabOrder = {default=-1};
	__property TabStop = {default=1};
	__property Visible = {default=1};
	__property BytesPerRow;
	__property BytesPerColumn = {default=2};
	__property AutoBytesPerRow = {default=0};
	__property Translation;
	__property OffsetFormat;
	__property CaretKind = {default=3};
	__property Colors;
	__property FocusFrame;
	__property SwapNibbles = {default=0};
	__property MaskChar;
	__property NoSizeChange = {default=0};
	__property AllowInsertMode = {default=1};
	__property DrawGridLines;
	__property WantTabs = {default=1};
	__property ReadOnlyView = {default=0};
	__property HideSelection = {default=0};
	__property GraySelectionIfNotFocused = {default=0};
	__property GutterWidth = {default=-1};
	__property BookmarkBitmap;
	__property Version;
	__property MaxUndo = {default=1048576};
	__property InsertMode = {default=0};
	__property HexLowerCase = {default=0};
	__property OnProgress;
	__property OnInvalidKey;
	__property OnTopLeftChanged;
	__property OnChange;
	__property DrawGutter3D = {default=1};
	__property DrawGutterGradient = {default=1};
	__property OwnerData = {default=0};
	__property ShowRuler = {default=0};
	__property BytesPerUnit = {default=1};
	__property RulerBytesPerUnit = {default=-1};
	__property ShowPositionIfNotFocused = {default=0};
	__property OnSelectionChanged;
	__property UnicodeChars = {default=0};
	__property UnicodeBigEndian = {default=0};
	__property OnDrawCell;
	__property OnBookmarkChanged;
	__property OnGetOffsetText;
	__property OnData;
	__property BytesPerBlock = {default=-1};
	__property SeparateBlocksInCharField = {default=1};
	__property FindProgress = {default=0};
	__property RulerNumberBase = {default=16};
public:
	/* TCustomMPHexEditor.Create */ inline __fastcall virtual TMPHexEditor(Classes::TComponent* aOwner) : TCustomMPHexEditor(aOwner) { }
	/* TCustomMPHexEditor.Destroy */ inline __fastcall virtual ~TMPHexEditor(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TMPHexEditor(HWND ParentWindow) : TCustomMPHexEditor(ParentWindow) { }
	
};


struct TMPHUndoRec;
typedef TMPHUndoRec *PMPHUndoRec;

#pragma pack(push,1)
struct TMPHUndoRec
{
	
public:
	int DataLen;
	TMPHUndoFlags Flags;
	int CurPos;
	unsigned Pos;
	unsigned Count;
	unsigned ReplCount;
	TMPHTranslationKind CurTranslation;
	int CurBPU;
	System::Byte Buffer;
};
#pragma pack(pop)


class PASCALIMPLEMENTATION TMPHUndoStorage : public Classes::TMemoryStream
{
	typedef Classes::TMemoryStream inherited;
	
private:
	int FCount;
	int FUpdateCount;
	TCustomMPHexEditor* FEditor;
	System::UnicodeString FDescription;
	TMPHUndoRec *FRedoPointer;
	TMPHUndoRec *FLastUndo;
	int FLastUndoSize;
	System::UnicodeString FLastUndoDesc;
	void __fastcall SetCount(const int Value);
	void __fastcall ResetRedo(void);
	void __fastcall CreateRedo(const TMPHUndoRec &Rec);
	TMPHUndoFlag __fastcall GetUndoKind(const TMPHUndoFlags Flags);
	void __fastcall AddSelection(const int APos, const int ACount);
	TMPHUndoFlag __fastcall ReadUndoRecord(TMPHUndoRec &aUR, System::UnicodeString &SDescription);
	TMPHUndoFlag __fastcall GetLastUndoKind(void);
	
public:
	__fastcall TMPHUndoStorage(TCustomMPHexEditor* AEditor);
	__fastcall virtual ~TMPHUndoStorage(void);
	virtual void __fastcall SetSize(int NewSize)/* overload */;
	void __fastcall CreateUndo(TMPHUndoFlag aKind, int APosition, int ACount, int AReplaceCount, const System::AnsiString SDescription = "");
	bool __fastcall CanUndo(void);
	bool __fastcall CanRedo(void);
	bool __fastcall Redo(void);
	bool __fastcall Undo(void);
	int __fastcall BeginUpdate(void);
	int __fastcall EndUpdate(void);
	void __fastcall Reset(bool AResetRedo = true);
	void __fastcall RemoveLastUndo(void);
	__property int Count = {read=FCount, write=SetCount, nodefault};
	__property int UpdateCount = {read=FUpdateCount, nodefault};
	__property System::UnicodeString Description = {read=FDescription};
	__property TMPHUndoFlag UndoKind = {read=GetLastUndoKind, nodefault};
	
/* Hoisted overloads: */
	
protected:
	inline void __fastcall  SetSize(const __int64 NewSize){ Classes::TStream::SetSize(NewSize); }
	
};


typedef StaticArray<System::UnicodeString, 6> Dcrhexeditor__8;

typedef StaticArray<System::UnicodeString, 6> Dcrhexeditor__9;

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE Dcrhexeditor__1 ColorHighlightAreaFieldType;
static const Word MPH_FILEIO_BLOCKSIZE = 0xf000;
static const Word CM_INTUPDATECARET = 0xb100;
static const Word CM_SELECTIONCHANGED = 0xb101;
extern PACKAGE TMPHCharConv MPH_CCONV_MAC;
extern PACKAGE TMPHCharConv MPH_CCONV_BCD38;
extern PACKAGE System::ResourceString _MPH_TK_ASIS;
#define Dcrhexeditor_MPH_TK_ASIS System::LoadResourceString(&Dcrhexeditor::_MPH_TK_ASIS)
extern PACKAGE System::ResourceString _MPH_TK_DOS8;
#define Dcrhexeditor_MPH_TK_DOS8 System::LoadResourceString(&Dcrhexeditor::_MPH_TK_DOS8)
extern PACKAGE System::ResourceString _MPH_TK_ASCII7;
#define Dcrhexeditor_MPH_TK_ASCII7 System::LoadResourceString(&Dcrhexeditor::_MPH_TK_ASCII7)
extern PACKAGE System::ResourceString _MPH_TK_MAC;
#define Dcrhexeditor_MPH_TK_MAC System::LoadResourceString(&Dcrhexeditor::_MPH_TK_MAC)
extern PACKAGE System::ResourceString _MPH_TK_BCD38;
#define Dcrhexeditor_MPH_TK_BCD38 System::LoadResourceString(&Dcrhexeditor::_MPH_TK_BCD38)
extern PACKAGE System::ResourceString _MPH_UC;
#define Dcrhexeditor_MPH_UC System::LoadResourceString(&Dcrhexeditor::_MPH_UC)
extern PACKAGE System::ResourceString _MPH_UC_BE;
#define Dcrhexeditor_MPH_UC_BE System::LoadResourceString(&Dcrhexeditor::_MPH_UC_BE)
extern PACKAGE System::ResourceString _MPH_TK_ASIS_S;
#define Dcrhexeditor_MPH_TK_ASIS_S System::LoadResourceString(&Dcrhexeditor::_MPH_TK_ASIS_S)
extern PACKAGE System::ResourceString _MPH_TK_DOS8_S;
#define Dcrhexeditor_MPH_TK_DOS8_S System::LoadResourceString(&Dcrhexeditor::_MPH_TK_DOS8_S)
extern PACKAGE System::ResourceString _MPH_TK_ASCII7_S;
#define Dcrhexeditor_MPH_TK_ASCII7_S System::LoadResourceString(&Dcrhexeditor::_MPH_TK_ASCII7_S)
extern PACKAGE System::ResourceString _MPH_TK_MAC_S;
#define Dcrhexeditor_MPH_TK_MAC_S System::LoadResourceString(&Dcrhexeditor::_MPH_TK_MAC_S)
extern PACKAGE System::ResourceString _MPH_TK_BCD38_S;
#define Dcrhexeditor_MPH_TK_BCD38_S System::LoadResourceString(&Dcrhexeditor::_MPH_TK_BCD38_S)
extern PACKAGE System::ResourceString _MPH_TK_CUSTOM_S;
#define Dcrhexeditor_MPH_TK_CUSTOM_S System::LoadResourceString(&Dcrhexeditor::_MPH_TK_CUSTOM_S)
extern PACKAGE System::ResourceString _MPH_TK_CUSTOM;
#define Dcrhexeditor_MPH_TK_CUSTOM System::LoadResourceString(&Dcrhexeditor::_MPH_TK_CUSTOM)
extern PACKAGE System::ResourceString _MPH_UC_S;
#define Dcrhexeditor_MPH_UC_S System::LoadResourceString(&Dcrhexeditor::_MPH_UC_S)
extern PACKAGE System::ResourceString _MPH_UC_BE_S;
#define Dcrhexeditor_MPH_UC_BE_S System::LoadResourceString(&Dcrhexeditor::_MPH_UC_BE_S)
extern PACKAGE Dcrhexeditor__8 MPHTranslationDesc;
extern PACKAGE Dcrhexeditor__9 MPHTranslationDescShort;
extern PACKAGE TMPHCharConv MPHCustomCharConv;
#define MPHOffsetHex L"-!10:0x|"
#define MPHOffsetDec L"a:|"
#define MPHOffsetOct L"0!8:o|"
extern PACKAGE void __fastcall TranslateBufferFromAnsi(const TMPHTranslationKind TType, System::WideChar * ABuffer, char * bBuffer, const int ACount);
extern PACKAGE void __fastcall TranslateBufferToAnsi(const TMPHTranslationKind TType, char * ABuffer, System::WideChar * bBuffer, const int ACount);
extern PACKAGE System::UnicodeString __fastcall GetTempName(void);
extern PACKAGE bool __fastcall IsKeyDown(int aKey);
extern PACKAGE int __fastcall Min(int a1, int a2);
extern PACKAGE int __fastcall Max(int a1, int a2);
extern PACKAGE Grids::TGridCoord __fastcall GridCoord(int AX, int AY);
extern PACKAGE char * __fastcall ConvertHexToBin(char * APositionFrom, char * APositionTo, const __int64 ACount, const bool ASwapNibbles, __int64 &ABytesTranslated);
extern PACKAGE char * __fastcall ConvertBinToHex(char * AFrom, char * ATo, const int ACount, const bool SwapNibbles);
extern PACKAGE System::AnsiString __fastcall IntToRadix(int Value, System::Byte Radix);
extern PACKAGE System::AnsiString __fastcall IntToRadix64(__int64 Value, System::Byte Radix);
extern PACKAGE System::AnsiString __fastcall IntToRadixLen(int Value, System::Byte Radix, System::Byte Len);
extern PACKAGE __int64 __fastcall DivideU64(const __int64 Dividend, const __int64 Divisor);
extern PACKAGE bool __fastcall TryDivideU64(const __int64 Dividend, const __int64 Divisor, __int64 &Val);
extern PACKAGE __int64 __fastcall ModuloU64(const __int64 Dividend, const __int64 Divisor);
extern PACKAGE bool __fastcall TryModuloU64(const __int64 Dividend, const __int64 Divisor, __int64 &Val);
extern PACKAGE bool __fastcall TryMultiplyU64(const __int64 Multiplier, const __int64 Multiplicator, __int64 &Val);
extern PACKAGE __int64 __fastcall MultiplyU64(const __int64 Multiplier, const __int64 Multiplicator);
extern PACKAGE bool __fastcall TryAddU64(const __int64 Addend1, const __int64 Addend2, __int64 &Val);
extern PACKAGE __int64 __fastcall AddU64(const __int64 Addend1, const __int64 Addend2);
extern PACKAGE bool __fastcall TrySubtractU64(const __int64 Minuend, const __int64 Subtrahend, __int64 &Val);
extern PACKAGE __int64 __fastcall SubtractU64(const __int64 Minuend, const __int64 Subtrahend);
extern PACKAGE System::AnsiString __fastcall IntToRadixLen64(__int64 Value, System::Byte Radix, System::Byte Len);
extern PACKAGE System::AnsiString __fastcall IntToOctal(const int Value);
extern PACKAGE int __fastcall RadixToInt(System::UnicodeString Value, System::Byte Radix);
extern PACKAGE __int64 __fastcall RadixToInt64(System::UnicodeString Value, System::Byte Radix);
extern PACKAGE int __fastcall CheckRadixToInt(System::UnicodeString Value);
extern PACKAGE __int64 __fastcall CheckRadixToInt64(System::UnicodeString Value);
extern PACKAGE int __fastcall OctalToInt(const System::UnicodeString Value);
extern PACKAGE void __fastcall SwapWideChar(System::WideChar &WChar);
extern PACKAGE Graphics::TColor __fastcall FadeToGray(Graphics::TColor aColor);

}	/* namespace Dcrhexeditor */
using namespace Dcrhexeditor;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DcrhexeditorHPP
