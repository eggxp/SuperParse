// *****************************************************************************
// Copyright: © Markus Stephany. All rights reserved.
// License:   LGPL 2.1 - http://www.gnu.org/licenses/lgpl-2.1.html
// File:      CustomTranslation.dpr
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

program CustomTranslation;

uses
   Forms,
   FormUnitCustomTranslation in 'FormUnitCustomTranslation.pas' {Form1};

{$R *.res}

begin
   Application.Initialize;
   Application.CreateForm(TForm1, Form1);
   Application.Run;

end.
