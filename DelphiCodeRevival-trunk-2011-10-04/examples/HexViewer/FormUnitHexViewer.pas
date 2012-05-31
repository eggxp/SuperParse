// *****************************************************************************
// Copyright: © Markus Stephany. All rights reserved.
// License:   LGPL 2.1 - http://www.gnu.org/licenses/lgpl-2.1.html
// File:      FormUnitHexViewer.pas
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

unit FormUnitHexViewer;

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
   FileCtrl,
   StdCtrls,
   ExtCtrls,
   Grids,
   dcrHexEditor,
   dcrHexEditorEx;

type
   TfmHexViewer = class(TForm)
      Panel1: TPanel;
      DriveComboBox1: TDriveComboBox;
      DirectoryListBox1: TDirectoryListBox;
      FileListBox1: TFileListBox;
      MPHexEditor1: TMPHexEditorEx;
      Panel2: TPanel;
      btnPrint: TButton;
      btnFind: TButton;
      procedure FileListBox1Change(Sender: TObject);
      procedure MPHexEditor1InvalidKey(Sender: TObject);
      procedure FormCreate(Sender: TObject);
      procedure btnPrintClick(Sender: TObject);
      procedure btnFindClick(Sender: TObject);
   private
      { Private declarations }
   public
      { Public declarations }
   end;

var
   fmHexViewer: TfmHexViewer;

implementation

uses
   dcrUIDlgPrintHex,
   FormUnitFindDialog;

{$R *.DFM}

procedure TfmHexViewer.FileListBox1Change(Sender: TObject);
begin
   // load the selected file into the hex editor
   with MPHexEditor1 do
      if FileName <> FileListBox1.FileName then begin
         if not FileExists(FileListBox1.FileName) then begin
            CreateEmptyFile('Unnamed');
            btnPrint.Enabled := False;
            btnFind.Enabled := False;
         end else begin
            LoadFromFile(FileListBox1.FileName);
            btnPrint.Enabled := DataSize > 0;
            btnFind.Enabled := DataSize > 0;
         end;
      end;
end;

procedure TfmHexViewer.MPHexEditor1InvalidKey(Sender: TObject);
begin
   // invalid Key, Beep
   MessageBeep(MB_ICONASTERISK)
end;

procedure TfmHexViewer.FormCreate(Sender: TObject);
begin
   // make sure that MYGRID is not defined in mphexeditor.pas
   Assert(MPHexEditor1 is TCustomGrid);
end;

procedure TfmHexViewer.btnPrintClick(Sender: TObject);
begin
   HexPrintPreview(MPHexEditor1);
end;

procedure TfmHexViewer.btnFindClick(Sender: TObject);
var
   sData, sTemp: AnsiString;
   ct: integer;
begin
   with TDlgFind.Create(Application) do
      try
         if ShowModal = mrOK then begin
            sData := AnsiString(edSearch.Text);
            if cbHex.Checked then begin
               // text is in hex digit format '0a 0c...', convert to binary
               sTemp := sData;
               SetLength(sData, Length(sTemp) div 2);
               ConvertHexToBin(PAnsiChar(sTemp), PAnsiChar(sData), Length(sTemp), False, ct);
               // in ct the amount of converted data bytes is stored, now set real
               // length of the converted data
               SetLength(sData, ct);
            end;
            if sData <> '' then begin
               // get first position to find (end of selection)
               with MPHexEditor1 do begin
                  ct := Min(SelStart, SelEnd) + SelCount;
                  // prepare find data
                  PrepareFindReplaceData(sData, cbIgnoreCase.Checked, not cbHex.Checked);
                  // find data
                  ct := Find(PAnsiChar(sData), Length(sData), ct, DataSize - 1, cbIgnoreCase.Checked);
                  if ct = -1 then ShowMessage('Not found.')
                  else begin
                     // select
                     SelStart := ct;
                     SelEnd := SelStart + Length(sData) - 1;
                  end;
               end;
            end;
         end;
      finally
         Free;
      end;
end;

end.
