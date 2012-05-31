// *****************************************************************************
// Copyright: © Markus Stephany. All rights reserved.
// License:   LGPL 2.1 - http://www.gnu.org/licenses/lgpl-2.1.html
// File:      HexEditor.dpr
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

program HexEditor;

uses
   Forms,
   FormUnitHexEditorMain in 'FormUnitHexEditorMain.pas' {FormHexEditorMain} ,
   FormUnitReplace in 'FormUnitReplace.pas' {DialogReplace} ,
   FormUnitCustomTranslation in 'FormUnitCustomTranslation.pas' {DialogEditCustomTranslation} ,
   FormUnitFind in 'FormUnitFind.pas' {DialogFind} ,
   FormUnitInputNumber in 'FormUnitInputNumber.pas' {DialogInputNumber} ,
   FormUnitConvert in 'FormUnitConvert.pas' {DialogConvert} ,
   FormUnitOptions in 'FormUnitOptions.pas' {DialogOptions};

{$R *.res}

begin
   Application.Initialize;
   Application.Title := 'mirkes.de''s little hexer';
   Application.CreateForm(TFormHexEditorMain, FormHexEditorMain);
   Application.Run;

end.
