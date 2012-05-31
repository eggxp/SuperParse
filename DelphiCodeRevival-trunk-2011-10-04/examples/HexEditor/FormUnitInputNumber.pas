// *****************************************************************************
// Copyright: © Markus Stephany. All rights reserved.
// License:   LGPL 2.1 - http://www.gnu.org/licenses/lgpl-2.1.html
// File:      FormUnitInputNumber.pas
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

unit FormUnitInputNumber;

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
   dcrHexEditor,
   ComCtrls;

type
   TDialogInputNumber = class(TForm)
      Button1: TButton;
      Button2: TButton;
      Label1: TLabel;
      Edit1: TEdit;
      UpDown1: TUpDown;
   end;

var
   DialogInputNumber: TDialogInputNumber;

   // select a number
function InputNumber(const AText: string; var Number: Integer; const Min, Max: Integer): Boolean;

implementation

{$R *.DFM}

// select a number
function InputNumber(const AText: string; var Number: Integer; const Min, Max: Integer): Boolean;
begin
   with TDialogInputNumber.Create(Application) do
      try
         UpDown1.Min := Min;
         UpDown1.Max := Max;
         UpDown1.Position := Number;
         Edit1.Text := IntToStr(Number);
         Caption := AText;
         Result := ShowModal = mrOK;
         if Result then Number := UpDown1.Position
      finally
         Free;
      end;
end;

end.
