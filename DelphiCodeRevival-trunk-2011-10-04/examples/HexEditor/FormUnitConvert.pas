// *****************************************************************************
// Copyright: © Markus Stephany. All rights reserved.
// License:   LGPL 2.1 - http://www.gnu.org/licenses/lgpl-2.1.html
// File:      FormUnitConvert.pas
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

unit FormUnitConvert;

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
   dcrHexEditor;

type
   TDialogConvert = class(TForm)
      Button1: TButton;
      Button2: TButton;
      Label1: TLabel;
      cbFrom: TComboBox;
      Label2: TLabel;
      cbTo: TComboBox;
      procedure cbFromChange(Sender: TObject);
   end;

var
   DialogConvert: TDialogConvert;

   // select a from-to translation
function SelectConvertTranslation(var AFrom, ATo: TMPHTranslationKind): Boolean;

implementation

{$R *.DFM}

// select a from-to translation
function SelectConvertTranslation(var AFrom, ATo: TMPHTranslationKind): Boolean;

   procedure FillCombo(CBox: TComboBox; const Translation: TMPHTranslationKind);
   var
      LEnumTrans: TMPHTranslationKind;
   begin
      with CBox.Items do begin
         Clear;
         for LEnumTrans := low(TMPHTranslationKind) to high(TMPHTranslationKind) do AddObject(MPHTranslationDesc[LEnumTrans], Pointer(LEnumTrans));
         CBox.ItemIndex := IndexOfObject(Pointer(Translation));
      end;
   end;

begin
   with TDialogConvert.Create(Application) do
      try
         FillCombo(cbFrom, AFrom);
         FillCombo(cbTo, ATo);
         Result := ShowModal = mrOK;
         if Result then begin
            AFrom := TMPHTranslationKind(cbFrom.Items.Objects[cbFrom.ItemIndex]);
            ATo := TMPHTranslationKind(cbTo.Items.Objects[cbTo.ItemIndex]);
         end;
      finally
         Free;
      end;
end;

procedure TDialogConvert.cbFromChange(Sender: TObject);
begin
   // check item indices
   Button1.Enabled := cbTo.ItemIndex <> cbFrom.ItemIndex
end;

end.
