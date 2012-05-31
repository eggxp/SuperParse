(*
  @author((C) markus stephany, <a href="http://launchpad.net/dcr">Delphi Code Revival</a>, all rights reserved.)
  @abstract(Print dialog for TMPHexEditor and TMPHexEditorEx)
  @lastmod(07-10-2010)

// *****************************************************************************
// Copyright: © Markus Stephany. All rights reserved.
// License:   LGPL 2.1 - http://www.gnu.org/licenses/lgpl-2.1.html
// File:      dcrUIDlgPrintHex.pas
// Compiler:  Delphi
// *****************************************************************************
// Dependencies:
// *****************************************************************************
// Changelog (new entries first):
// ---------------------------------------
// 2010-10-07  ##   --  Beautified code (using Code Beautifier Wizard)
// 2010-10-07  ##   --  Added this header (from Code Beautifier Wizard)
// *****************************************************************************
// CodeBeautifier exceptions:
// ---------------------------------------
// skip: TBeautifierHeaderComments
// *****************************************************************************
*)

unit dcrUIDlgPrintHex;

interface

uses
   Windows,
   Messages,
   SysUtils,
   Classes,
   Graphics,
   Controls,
   Forms,
   Dialogs,
   dcrHexEditorEx,
   ActnList,
   ExtCtrls,
   StdCtrls,
   Buttons,
   ComCtrls;

type
   TDialogHexEditorPrintPreview = class(TForm)
      panelTop: TPanel;
      panelLeft: TPanel;
      groupRange: TGroupBox;
      rbPrintAllPages: TRadioButton;
      rbPrintCurrentPage: TRadioButton;
      rbPrintSelection: TRadioButton;
      groupMargins: TGroupBox;
      edMarginTop: TEdit;
      edMarginLeft: TEdit;
      edMarginRight: TEdit;
      edMarginBottom: TEdit;
      bnPrinterSelect: TBitBtn;
      cbColors: TCheckBox;
      cbBack: TCheckBox;
      cbSelBold: TCheckBox;
      labelPage: TLabel;
      labelPageCount: TLabel;
      bnPrint: TButton;
      bnClose: TButton;
      FontDialog1: TFontDialog;
      sbPreview: TScrollBox;
      imgPreview: TImage;
      labelZoom: TLabel;
      edZoom: TEdit;
      udZoom: TUpDown;
      bnFont: TButton;
      labelPageHeader: TLabel;
      edPageHeader: TEdit;
      labelPageFooter: TLabel;
      edPageFooter: TEdit;
      rbPrintCurrentView: TRadioButton;
      dlgSetupPrinter: TPrinterSetupDialog;
      udPage: TUpDown;
      edPage: TEdit;
      procedure bnCloseClick(Sender: TObject);
      procedure FormShow(Sender: TObject);
      procedure FormCreate(Sender: TObject);
      procedure FormDestroy(Sender: TObject);
      procedure sbPreviewResize(Sender: TObject);
      procedure bnFontClick(Sender: TObject);
      procedure cbSelBoldClick(Sender: TObject);
      procedure cbBackClick(Sender: TObject);
      procedure cbColorsClick(Sender: TObject);
      procedure udPageClick(Sender: TObject; Button: TUDBtnType);
      procedure rbPrintSelectionClick(Sender: TObject);
      procedure udZoomClick(Sender: TObject; Button: TUDBtnType);
      procedure edPageHeaderChange(Sender: TObject);
      procedure edMarginTopChange(Sender: TObject);
      procedure bnPrintClick(Sender: TObject);
      procedure bnPrinterSelectClick(Sender: TObject);
   private
      { Private-Deklarationen }
      FEditor: TMPHexEditorEx;
      FMeta: TMetaFile;
      FSetting: Boolean;
      procedure SetControls;
      procedure SetImageBounds;
      procedure CreatePreview;
   public
      { Public-Deklarationen }
   end;

   // var fmPrinting: TfmPrinting;

procedure HexPrintPreview(Editor: TMPHexEditorEx);

implementation

uses
   dcrUIDlgPrintHexProgress;

{$R *.dfm}

const
   STR_NUMPG      = 'of %d';
   STR_INVMARGINS = 'Invalid page margins.';

   // printing
procedure HexPrintPreview(Editor: TMPHexEditorEx);
begin
   with TDialogHexEditorPrintPreview.Create(Application) do
      try
         FEditor := Editor;
         ShowModal;
      finally
         Free;
      end;
end;

{ TfmPrinting }

procedure TDialogHexEditorPrintPreview.bnCloseClick(Sender: TObject);
begin
   Close;
end;

procedure TDialogHexEditorPrintPreview.FormShow(Sender: TObject);
begin
   rbPrintSelection.Enabled := FEditor.SelCount > 0;
   rbPrintSelection.Checked := rbPrintSelection.Enabled and (pfSelectionOnly in FEditor.PrintOptions.Flags);
   rbPrintCurrentView.Checked := (pfCurrentViewOnly in FEditor.PrintOptions.Flags);
   SetControls;
   CreatePreview;
   SetImageBounds;
end;

procedure TDialogHexEditorPrintPreview.SetControls;
begin
   with FEditor.PrintOptions do begin
      FSetting := True;
      try
         cbColors.Checked := not(pfMonochrome in Flags);
         cbBack.Enabled := cbColors.Checked;
         cbBack.Checked := cbColors.Checked and (pfUseBackGroundColor in Flags);
         cbSelBold.Enabled := not rbPrintSelection.Checked;
         cbSelBold.Checked := cbSelBold.Enabled and (pfSelectionBold in Flags);
         Flags := Flags - [pfIncludeRuler];

         edMarginTop.Text := IntToStr(MarginTop);
         edMarginLeft.Text := IntToStr(MarginLeft);
         edMarginRight.Text := IntToStr(MarginRight);
         edMarginBottom.Text := IntToStr(MarginBottom);

         try
            udPage.Max := FEditor.PrintNumPages;
         except
            udPage.Max := 1;
         end;
         if udPage.Max < udPage.Position then udPage.Position := udPage.Max;
         edPage.Text := IntToStr(udPage.Position);
         labelPage.Enabled := udPage.Max > 1;
         edPage.Enabled := udPage.Max > 1;
         udPage.Enabled := udPage.Max > 1;
         labelPageCount.Enabled := udPage.Max > 1;
         labelPageCount.Caption := Format(STR_NUMPG, [udPage.Max]);

         edPageHeader.Text := PageHeader;
         edPageFooter.Text := PageFooter;
      finally
         FSetting := False;
      end;
   end;
end;

procedure TDialogHexEditorPrintPreview.FormCreate(Sender: TObject);
begin
   FMeta := nil;
   FSetting := False;
   sbPreview.DoubleBuffered := True;
end;

procedure TDialogHexEditorPrintPreview.FormDestroy(Sender: TObject);
begin
   if Assigned(FMeta) then FreeAndNil(FMeta);
end;

procedure TDialogHexEditorPrintPreview.SetImageBounds;
var
   LDblRatio: Single;
   LIntW, LIntH: Integer;
begin
   if Assigned(FMeta) then begin
      // get height/width ratio
      LDblRatio := FMeta.MMWidth / FMeta.MMHeight;
      // calc max bounds of image (depending on pnPreview.clientw/h)
      LIntW := sbPreview.Width - 16;
      LIntH := Round(LIntW / LDblRatio);
      if LIntH > (sbPreview.Height - 16) then begin
         LIntH := sbPreview.Height - 16;
         LIntW := Round(LIntH * LDblRatio);
      end;
      // calc zoom
      LIntW := LIntW * udZoom.Position div 100;
      LIntH := LIntH * udZoom.Position div 100;
      with imgPreview do begin
         Width := LIntW;
         Height := LIntH;
         Picture.Bitmap.Width := 0;
         Picture.Bitmap.Height := 0;
         Picture.Bitmap.Width := LIntW;
         Picture.Bitmap.Height := LIntH;
         Picture.Bitmap.Canvas.StretchDraw(Rect(0, 0, LIntW, LIntH), FMeta);
      end;
   end;
end;

procedure TDialogHexEditorPrintPreview.CreatePreview;
begin
   if Assigned(FMeta) then FreeAndNil(FMeta);
   try
      FMeta := FEditor.PrintPreview(udPage.Position);
   except
      FMeta := nil;
      raise;
   end;
end;

procedure TDialogHexEditorPrintPreview.sbPreviewResize(Sender: TObject);
begin
   SetImageBounds;
end;

procedure TDialogHexEditorPrintPreview.bnFontClick(Sender: TObject);
begin
   with FontDialog1 do begin
      if FEditor.UseEditorFontForPrinting then Font.Assign(FEditor.Font)
      else Font.Assign(FEditor.PrintFont);
      if Execute then begin
         FEditor.PrintFont := Font;
         SetControls;
         CreatePreview;
         SetImageBounds;
      end;
   end;
end;

procedure TDialogHexEditorPrintPreview.cbSelBoldClick(Sender: TObject);
begin
   if FSetting then Exit;
   with FEditor.PrintOptions do
      if cbSelBold.Checked then Flags := Flags + [pfSelectionBold]
      else Flags := Flags - [pfSelectionBold];
   SetControls;
   CreatePreview;
   SetImageBounds;
end;

procedure TDialogHexEditorPrintPreview.cbBackClick(Sender: TObject);
begin
   if FSetting then Exit;
   with FEditor.PrintOptions do
      if cbBack.Checked then Flags := Flags + [pfUseBackGroundColor]
      else Flags := Flags - [pfUseBackGroundColor];
   SetControls;
   CreatePreview;
   SetImageBounds;
end;

procedure TDialogHexEditorPrintPreview.cbColorsClick(Sender: TObject);
begin
   if FSetting then Exit;
   with FEditor.PrintOptions do
      if cbColors.Checked then Flags := Flags - [pfMonochrome]
      else Flags := Flags + [pfMonochrome];
   SetControls;
   CreatePreview;
   SetImageBounds;
end;

procedure TDialogHexEditorPrintPreview.udPageClick(Sender: TObject; Button: TUDBtnType);
begin
   if FSetting then Exit;
   try
      CreatePreview;
      SetImageBounds;
   except
   end;
end;

procedure TDialogHexEditorPrintPreview.rbPrintSelectionClick(Sender: TObject);
begin
   if FSetting then Exit;
   with FEditor.PrintOptions do begin
      if rbPrintSelection.Checked then Flags := Flags + [pfSelectionOnly]
      else Flags := Flags - [pfSelectionOnly];
      if rbPrintCurrentView.Checked then Flags := Flags + [pfCurrentViewOnly]
      else Flags := Flags - [pfCurrentViewOnly];
   end;
   SetControls;
   CreatePreview;
   SetImageBounds;
end;

procedure TDialogHexEditorPrintPreview.udZoomClick(Sender: TObject; Button: TUDBtnType);
begin
   SetImageBounds;
end;

procedure TDialogHexEditorPrintPreview.edPageHeaderChange(Sender: TObject);
begin
   if FSetting then Exit;
   with FEditor.PrintOptions do begin
      PageHeader := edPageHeader.Text;
      PageFooter := edPageFooter.Text;
   end;
   SetControls;
   CreatePreview;
   SetImageBounds;
end;

procedure TDialogHexEditorPrintPreview.edMarginTopChange(Sender: TObject);
var
   LIntLeft, LIntTop, LIntRight, LIntBottom: Integer;
begin
   if FSetting or (TEdit(Sender).Text = '') then Exit;
   with FEditor.PrintOptions do begin
      // save in case of invalid values (no line per page)
      LIntLeft := MarginLeft;
      LIntTop := MarginTop;
      LIntRight := MarginRight;
      LIntBottom := MarginBottom;

      try
         MarginLeft := StrToIntDef(edMarginLeft.Text, MarginLeft);
         MarginTop := StrToIntDef(edMarginTop.Text, MarginTop);
         MarginRight := StrToIntDef(edMarginRight.Text, MarginRight);
         MarginBottom := StrToIntDef(edMarginBottom.Text, MarginBottom);
         SetControls;
         CreatePreview;
         SetImageBounds;
      except
         MarginLeft := LIntLeft;
         MarginTop := LIntTop;
         MarginRight := LIntRight;
         MarginBottom := LIntBottom;
         try
            SetControls;
            CreatePreview;
            SetImageBounds;
         except
            MarginLeft := 0;
            MarginTop := 0;
            MarginRight := 0;
            MarginBottom := 0;
            SetControls;
            CreatePreview;
            SetImageBounds;
         end;
         raise Exception.Create(STR_INVMARGINS);
      end;
   end;
end;

procedure TDialogHexEditorPrintPreview.bnPrintClick(Sender: TObject);
var
   LIntFrom, LIntTo: Integer;
begin
   if rbPrintCurrentPage.Checked then begin
      LIntFrom := udPage.Position;
      LIntTo := LIntFrom;
   end else begin
      LIntFrom := 1;
      LIntTo := udPage.Max;
   end;
   DoPrint(FEditor, LIntFrom, LIntTo);
end;

procedure TDialogHexEditorPrintPreview.bnPrinterSelectClick(Sender: TObject);
begin
   if dlgSetupPrinter.Execute then begin
      SetControls;
      CreatePreview;
      SetImageBounds;
   end;
end;

end.
