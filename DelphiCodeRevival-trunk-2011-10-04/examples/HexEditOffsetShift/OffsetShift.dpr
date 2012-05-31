// *****************************************************************************
// Copyright: © Markus Stephany. All rights reserved.
// License:   LGPL 2.1 - http://www.gnu.org/licenses/lgpl-2.1.html
// File:      OffsetShift.dpr
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

program OffsetShift;

uses
   Forms,
   FormUnitOffsetShift in 'FormUnitOffsetShift.pas' {FormOffsetShift};

{$R *.res}

begin
   Application.Initialize;
   Application.CreateForm(TFormOffsetShift, FormOffsetShift);
   Application.Run;

end.
