// *****************************************************************************
// Copyright: © Markus Stephany. All rights reserved.
// License:   LGPL 2.1 - http://www.gnu.org/licenses/lgpl-2.1.html
// File:      FormUnitFindDialog.pas
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

unit FormUnitFindDialog;

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
   StdCtrls;

type
   TdlgFind = class(TForm)
      Label1: TLabel;
      edSearch: TEdit;
      cbHex: TCheckBox;
      Button1: TButton;
      Button2: TButton;
      cbIgnoreCase: TCheckBox;
      procedure edSearchChange(Sender: TObject);
   private
      { Private-Deklarationen }
   public
      { Public-Deklarationen }
   end;

var
   dlgFind: TdlgFind;

implementation

{$R *.dfm}

procedure TdlgFind.edSearchChange(Sender: TObject);
begin
   Button1.Enabled := edSearch.Text <> '';
end;

end.
