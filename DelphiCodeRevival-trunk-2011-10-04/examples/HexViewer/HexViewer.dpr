// *****************************************************************************
// Copyright: © Markus Stephany. All rights reserved.
// License:   LGPL 2.1 - http://www.gnu.org/licenses/lgpl-2.1.html
// File:      HexViewer.dpr
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

program HexViewer;

uses
   Forms,
   FormUnitHexViewer in 'FormUnitHexViewer.pas' {fmHexViewer} ,
   FormUnitFindDialog in 'FormUnitFindDialog.pas' {dlgFind};

{$R *.RES}

begin
   Application.Initialize;
   Application.CreateForm(TfmHexViewer, fmHexViewer);
   Application.Run;

end.
