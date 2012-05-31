(*
  @author((C) markus stephany, <a href="http://launchpad.net/dcr">Delphi Code Revival</a>, all rights reserved.)
  @abstract(Print progress dialog for TMPHexEditor and TMPHexEditorEx)
  @lastmod(07-10-2010)

// *****************************************************************************
// Copyright: © Markus Stephany. All rights reserved.
// License:   LGPL 2.1 - http://www.gnu.org/licenses/lgpl-2.1.html
// File:      dcrUIDlgPrintHexProgress.pas
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

unit dcrUIDlgPrintHexProgress;

interface

uses
   SysUtils,
   Windows,
   Messages,
   Classes,
   Graphics,
   Controls,
   StdCtrls,
   ExtCtrls,
   Forms,
   ComCtrls,
   dcrHexEditorEx;

type
   TDialogPrintProgress = class(TForm)
      Button2: TButton;
      lbPrinting: TLabel;
      ProgressBar1: TProgressBar;
      procedure FormCreate(Sender: TObject);
      procedure Button2Click(Sender: TObject);
      procedure FormShow(Sender: TObject);
   private
      FFrom, FTo: Integer;
      FCancel: Boolean;
      FEditor: TMPHexEditorEx;
      procedure WMUser1(var Msg: TMsg); message WM_USER + 1;
   end;

var
   DialogPrintProgress: TDialogPrintProgress;

   // do printing
function DoPrint(Editor: TMPHexEditorEx; const PageFrom, PageTo: Integer): Boolean;

implementation

uses
   Printers;

{$R *.DFM}

const
   STR_PRINTING   = 'Printing page %d of %d';
   STR_PRINTTITLE = 'TMPHexEditorEx Print Job';

   // do printing
function DoPrint(Editor: TMPHexEditorEx; const PageFrom, PageTo: Integer): Boolean;
begin
   with TDialogPrintProgress.Create(Application) do
      try
         FEditor := Editor;
         FFrom := PageFrom;
         FTo := PageTo;
         Result := (ShowModal = mrOK) and (not FCancel);
      finally
         Free;
      end;
end;

procedure TDialogPrintProgress.FormCreate(Sender: TObject);
begin
   FCancel := False;
end;

procedure TDialogPrintProgress.Button2Click(Sender: TObject);
begin
   FCancel := True;
   ModalResult := mrCancel;
end;

procedure TDialogPrintProgress.FormShow(Sender: TObject);
begin
   PostMessage(Handle, WM_USER + 1, 0, 0);
end;

procedure TDialogPrintProgress.WMUser1(var Msg: TMsg);
var
   LIntLoop: Integer;
begin
   Printer.Title := STR_PRINTTITLE;
   Printer.BeginDoc;
   try
      ProgressBar1.Min := FFrom;
      ProgressBar1.Max := FTo;
      for LIntLoop := FFrom to FTo do begin
         ProgressBar1.Position := LIntLoop;
         lbPrinting.Caption := Format(STR_PRINTING, [LIntLoop, FTo]);
         Application.ProcessMessages;
         if FCancel then Break;
         try
            FEditor.Print(LIntLoop);
         except
            ModalResult := mrCancel;
            Break;
         end;
         if LIntLoop < FTo then Printer.NewPage;
      end;
   finally
      if FCancel then begin
         Printer.Abort;
         ModalResult := mrCancel
      end else begin
         Printer.EndDoc;
         ModalResult := mrOK;
      end;
   end;
end;

end.
