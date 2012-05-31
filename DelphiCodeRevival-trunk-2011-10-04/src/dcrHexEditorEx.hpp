// CodeGear C++Builder
// Copyright (c) 1995, 2009 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Dcrhexeditorex.pas' rev: 21.00

#ifndef DcrhexeditorexHPP
#define DcrhexeditorexHPP

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
#include <Controls.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Dcrhexeditor.hpp>	// Pascal unit
#include <Activex.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Printers.hpp>	// Pascal unit
#include <Stdactns.hpp>	// Pascal unit
#include <Clipbrd.hpp>	// Pascal unit
#include <Shlobj.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <Grids.hpp>	// Pascal unit
#include <Stdctrls.hpp>	// Pascal unit
#include <Types.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------
DECLARE_DINTERFACE_TYPE(IDropTarget)
DECLARE_DINTERFACE_TYPE(IDropSource)
DECLARE_DINTERFACE_TYPE(IEnumFORMATETC)

namespace Dcrhexeditorex
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TMPHOLEOperation { oleDrop, oleClipboard };
#pragma option pop

typedef DynamicArray<System::Word> TClipFormats;

#pragma option push -b-
enum TMPHPrintFlag { pfSelectionOnly, pfSelectionBold, pfMonochrome, pfUseBackgroundColor, pfCurrentViewOnly, pfIncludeRuler };
#pragma option pop

typedef Set<TMPHPrintFlag, pfSelectionOnly, pfIncludeRuler>  TMPHPrintFlags;

typedef StaticArray<System::UnicodeString, 2> TMPHPrintHeaders;

typedef void __fastcall (__closure *TMPHQueryPublicPropertyEvent)(System::TObject* Sender, const System::UnicodeString PropertyName, bool &IsPublic);

class DELPHICLASS TMPHexEditorEx;
class DELPHICLASS TMPHDropTarget;
class DELPHICLASS TMPHPrintOptions;
class PASCALIMPLEMENTATION TMPHexEditorEx : public Dcrhexeditor::TCustomMPHexEditor
{
	typedef Dcrhexeditor::TCustomMPHexEditor inherited;
	
private:
	bool FCreateBackups;
	System::UnicodeString FBackupFileExt;
	bool FOleDragDrop;
	TMPHDropTarget* FDropTarget;
	StaticArray<System::Word, 2> FOleFormat;
	bool FOleDragging;
	bool FOleStartDrag;
	int FOleDragX;
	int FOleDragY;
	bool FOleWasTarget;
	TMPHPrintOptions* FPrintOptions;
	int FPrintPages;
	Graphics::TFont* FPrintFont;
	bool FUseEditorFontForPrinting;
	bool FClipboardAsHexText;
	_di_IDataObject FClipData;
	bool FFlushClipboardAtShutDown;
	bool FSupportsOtherClipFormats;
	Menus::TPopupMenu* FOffsetPopupMenu;
	bool FZoomOnWheel;
	int FPaintUpdateCounter;
	TMPHQueryPublicPropertyEvent FOnQueryPublicProperty;
	bool FHasDoubleClicked;
	bool FBookmarksNoChange;
	bool FCreateUndoOnUndoUpdate;
	bool FModifiedNoUndo;
	void __fastcall SetOleDragDrop(const bool Value);
	bool __fastcall OLEHasSupportedFormat(const _di_IDataObject dataObj, System::Word const *Formats, const int Formats_Size, System::Word &Format);
	TClipFormats __fastcall GetMyOLEFormats(void);
	HIDESBASE MESSAGE void __fastcall WMDestroy(Messages::TWMNoParams &message);
	void __fastcall SetPrintOptions(const TMPHPrintOptions* Value);
	int __fastcall PrintToCanvas(Graphics::TCanvas* ACanvas, const int APage, const Types::TRect &AMargins);
	Types::TRect __fastcall PrinterMarginRect(void);
	void __fastcall SetPrintFont(const Graphics::TFont* Value);
	void __fastcall SetOffsetPopupMenu(const Menus::TPopupMenu* Value);
	Menus::TPopupMenu* __fastcall GetOffsetPopupMenu(void);
	System::UnicodeString __fastcall GetBookmarksAsString(void);
	void __fastcall SetBookMarksAsString(System::UnicodeString Value);
	
protected:
	virtual bool __fastcall CanCreateUndo(const Dcrhexeditor::TMPHUndoFlag aKind, const __int64 aCount, const __int64 aReplCount);
	virtual System::UnicodeString __fastcall GetPropertiesAsString(void);
	virtual void __fastcall SetPropertiesAsString(const System::UnicodeString Value);
	virtual bool __fastcall IsPropPublic(System::UnicodeString PropName);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	DYNAMIC void __fastcall DoContextPopup(const Types::TPoint &MousePos, bool &Handled);
	DYNAMIC void __fastcall KeyDown(System::Word &Key, Classes::TShiftState Shift);
	DYNAMIC bool __fastcall DoMouseWheelDown(Classes::TShiftState Shift, const Types::TPoint &MousePos);
	DYNAMIC bool __fastcall DoMouseWheelUp(Classes::TShiftState Shift, const Types::TPoint &MousePos);
	virtual void __fastcall PrepareOverwriteDiskFile(void);
	DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall CreateWnd(void);
	HRESULT __fastcall SupportsOLEData(const _di_IDataObject dataObj, const int grfKeyState, const Types::TPoint &pt, int &dwEffect, const TMPHOLEOperation Operation);
	HRESULT __fastcall InsertOLEData(const _di_IDataObject dataObj, const int grfKeyState, const Types::TPoint &pt, int &dwEffect, const TMPHOLEOperation Operation);
	HRESULT __fastcall ModifyOLEDropEffect(const int grfKeyState, const Types::TPoint &pt, int &dwEffect);
	virtual void __fastcall Paint(void);
	DYNAMIC void __fastcall DblClick(void);
	virtual void __fastcall BookmarkChanged(void);
	
public:
	__fastcall virtual TMPHexEditorEx(Classes::TComponent* AOwner);
	__fastcall virtual ~TMPHexEditorEx(void);
	virtual void __fastcall WriteBuffer(const void *ABuffer, const __int64 AIndex, const __int64 ACount);
	DYNAMIC bool __fastcall ExecuteAction(Classes::TBasicAction* Action);
	virtual bool __fastcall UpdateAction(Classes::TBasicAction* Action);
	__property bool CreateUndoOnUndoUpdate = {read=FCreateUndoOnUndoUpdate, write=FCreateUndoOnUndoUpdate, nodefault};
	int __fastcall BeginUpdate(void);
	int __fastcall EndUpdate(void);
	HIDESBASE int __fastcall UndoBeginUpdate(const System::UnicodeString StrUndoDesc = L"");
	virtual int __fastcall UndoEndUpdate(void);
	void __fastcall CreateRangeUndo(const int aStart, const int aCount, System::UnicodeString sDesc);
	bool __fastcall CanPaste(void);
	bool __fastcall CanCopy(void);
	bool __fastcall CanCut(void);
	bool __fastcall CBCopy(void);
	bool __fastcall CBCut(void);
	bool __fastcall CBPaste(void);
	bool __fastcall OwnsClipBoard(void);
	void __fastcall ReleaseClipboard(const bool Flush);
	void __fastcall Save(void);
	bool __fastcall DumpUndoStorage(const System::UnicodeString FileName);
	Graphics::TMetafile* __fastcall PrintPreview(const int Page);
	void __fastcall Print(const int Page);
	int __fastcall PrintNumPages(void);
	void __fastcall PasteData(void * P, const int aCount, const System::UnicodeString UndoDesc = L"");
	__property System::UnicodeString BookMarksAsString = {read=GetBookmarksAsString, write=SetBookMarksAsString};
	__property System::UnicodeString PropertiesAsString = {read=GetPropertiesAsString, write=SetPropertiesAsString};
	
__published:
	__property bool CreateBackup = {read=FCreateBackups, write=FCreateBackups, default=1};
	__property System::UnicodeString BackupExtension = {read=FBackupFileExt, write=FBackupFileExt};
	__property bool OleDragDrop = {read=FOleDragDrop, write=SetOleDragDrop, default=0};
	__property bool ClipboardAsHexText = {read=FClipboardAsHexText, write=FClipboardAsHexText, default=0};
	__property bool FlushClipboardAtShutDown = {read=FFlushClipboardAtShutDown, write=FFlushClipboardAtShutDown, default=0};
	__property bool SupportsOtherClipFormats = {read=FSupportsOtherClipFormats, write=FSupportsOtherClipFormats, default=1};
	__property TMPHPrintOptions* PrintOptions = {read=FPrintOptions, write=SetPrintOptions};
	__property Graphics::TFont* PrintFont = {read=FPrintFont, write=SetPrintFont};
	__property bool UseEditorFontForPrinting = {read=FUseEditorFontForPrinting, write=FUseEditorFontForPrinting, default=1};
	__property Menus::TPopupMenu* OffsetPopupMenu = {read=GetOffsetPopupMenu, write=SetOffsetPopupMenu};
	__property bool ZoomOnWheel = {read=FZoomOnWheel, write=FZoomOnWheel, default=1};
	__property TMPHQueryPublicPropertyEvent OnQueryPublicProperty = {read=FOnQueryPublicProperty, write=FOnQueryPublicProperty};
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
	__property AutoBytesPerRow = {default=0};
	__property BytesPerRow;
	__property BytesPerColumn = {default=2};
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
	/* TWinControl.CreateParented */ inline __fastcall TMPHexEditorEx(HWND ParentWindow) : Dcrhexeditor::TCustomMPHexEditor(ParentWindow) { }
	
};


class PASCALIMPLEMENTATION TMPHDropTarget : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	TMPHexEditorEx* FEditor;
	unsigned FEditorHandle;
	bool FActive;
	void __fastcall SetActive(const bool Value);
	
public:
	__fastcall TMPHDropTarget(TMPHexEditorEx* Editor);
	virtual void __fastcall BeforeDestruction(void);
	HRESULT __stdcall DragEnter(const _di_IDataObject dataObj, int grfKeyState, const Types::TPoint pt, int &dwEffect);
	HRESULT __stdcall DragOver(int grfKeyState, const Types::TPoint pt, int &dwEffect);
	HRESULT __stdcall DragLeave(void);
	HRESULT __stdcall Drop(const _di_IDataObject dataObj, int grfKeyState, const Types::TPoint pt, int &dwEffect);
	__property bool Active = {read=FActive, write=SetActive, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMPHDropTarget(void) { }
	
private:
	void *__IDropTarget;	/* IDropTarget */
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	operator _di_IDropTarget()
	{
		_di_IDropTarget intf;
		GetInterface(intf);
		return intf;
	}
	#else
	operator IDropTarget*(void) { return (IDropTarget*)&__IDropTarget; }
	#endif
	
};


class PASCALIMPLEMENTATION TMPHPrintOptions : public Classes::TPersistent
{
	typedef Classes::TPersistent inherited;
	
private:
	Types::TRect FMargins;
	TMPHPrintHeaders FHeaders;
	TMPHPrintFlags FFlags;
	System::UnicodeString __fastcall GetHeader(const int index);
	int __fastcall GetMargin(const int index);
	void __fastcall SetHeader(const int index, const System::UnicodeString Value);
	void __fastcall SetMargin(const int index, const int Value);
	
public:
	__fastcall TMPHPrintOptions(void);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	
__published:
	__property int MarginLeft = {read=GetMargin, write=SetMargin, index=1, nodefault};
	__property int MarginTop = {read=GetMargin, write=SetMargin, index=2, nodefault};
	__property int MarginRight = {read=GetMargin, write=SetMargin, index=3, nodefault};
	__property int MarginBottom = {read=GetMargin, write=SetMargin, index=4, nodefault};
	__property System::UnicodeString PageHeader = {read=GetHeader, write=SetHeader, index=0};
	__property System::UnicodeString PageFooter = {read=GetHeader, write=SetHeader, index=1};
	__property TMPHPrintFlags Flags = {read=FFlags, write=FFlags, nodefault};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TMPHPrintOptions(void) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE Types::TRect MPH_DEF_PRINT_MARGINS;
extern PACKAGE void __fastcall MPHSetHexClipboardData(void * Data, int DataSize, System::ShortString &ScrapFileName, bool TextAsHex, bool SwapNibbles);

}	/* namespace Dcrhexeditorex */
using namespace Dcrhexeditorex;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DcrhexeditorexHPP
