{$IFDEF VER80} // Delphi 1
	ERROR Delphi 1 not supported!
{$ENDIF}
{$IFDEF VER90} // Delphi 2
        {$DEFINE DELPHI}
	{$DEFINE DELPHI2}
        {$DEFINE DELPHI2UP}
{$ENDIF}
{$IFDEF VER93}
        {$DEFINE BCB}
	{$DEFINE BCB1}
        {$DEFINE DELPHI2UP}
{$ENDIF}
{$IFDEF VER100} // Delphi 3
        {$DEFINE DELPHI}
	{$DEFINE DELPHI3}
        {$DEFINE DELPHI2UP}
        {$DEFINE DELPHI3UP}
{$ENDIF}
{$IFDEF VER110}
        {$DEFINE BCB}
	{$DEFINE BCB3}
        {$DEFINE DELPHI2UP}
        {$DEFINE DELPHI3UP}
{$ENDIF}
{$IFDEF VER120} // Delphi4
        {$DEFINE DELPHI}
	{$DEFINE DELPHI4}
        {$DEFINE DELPHI2UP}
        {$DEFINE DELPHI3UP}
        {$DEFINE DELPHI4UP}
{$ENDIF}
{$IFDEF VER125}
        {$DEFINE BCB}
	{$DEFINE BCB4}
        {$DEFINE DELPHI2UP}
        {$DEFINE DELPHI3UP}
        {$DEFINE DELPHI4UP}
{$ENDIF}
{$IFDEF VER130} // Delphi 5
        {$IFNDEF BCB}
                 {$DEFINE DELPHI}
	         {$DEFINE DELPHI5}
                 {$DEFINE DELPHI2UP}
                 {$DEFINE DELPHI3UP}
                 {$DEFINE DELPHI4UP}
                 {$DEFINE DELPHI5UP}
        {$ELSE}
               {$DEFINE BCB}
	       {$DEFINE BCB5}
               {$DEFINE DELPHI2UP}
               {$DEFINE DELPHI3UP}
               {$DEFINE DELPHI4UP}
               {$DEFINE DELPHI5UP}
        {$ENDIF}
{$ENDIF}
{$IFDEF VER140} // Delphi 6
        {$IFNDEF BCB}
                 {$DEFINE DELPHI}
	         {$DEFINE DELPHI6}
                 {$DEFINE DELPHI2UP}
                 {$DEFINE DELPHI3UP}
                 {$DEFINE DELPHI4UP}
                 {$DEFINE DELPHI5UP}
                 {$DEFINE DELPHI6UP}
        {$ELSE}
               {$DEFINE BCB}
	       {$DEFINE BCB6}
               {$DEFINE DELPHI2UP}
               {$DEFINE DELPHI3UP}
               {$DEFINE DELPHI4UP}
               {$DEFINE DELPHI5UP}
               {$DEFINE DELPHI6UP}
        {$ENDIF}
{$ENDIF}
{$IFDEF VER150} // Delphi 7
        {$IFNDEF BCB}
             {$DEFINE DELPHI}
             {$DEFINE DELPHI7}
             {$DEFINE DELPHI2UP}
             {$DEFINE DELPHI3UP}
             {$DEFINE DELPHI4UP}
             {$DEFINE DELPHI5UP}
             {$DEFINE DELPHI6UP}
             {$DEFINE DELPHI7UP}
        {$ELSE}
             {$DEFINE BCB}
             {$DEFINE BCB7}
             {$DEFINE DELPHI2UP}
             {$DEFINE DELPHI3UP}
             {$DEFINE DELPHI4UP}
             {$DEFINE DELPHI5UP}
             {$DEFINE DELPHI6UP}
             {$DEFINE DELPHI7UP}
        {$ENDIF}
{$ENDIF}
{$IFDEF VER160} // Delphi 8
        {$DEFINE DELPHI}
        {$DEFINE DELPHI8}
        {$DEFINE DELPHI2UP}
        {$DEFINE DELPHI3UP}
        {$DEFINE DELPHI4UP}
        {$DEFINE DELPHI5UP}
        {$DEFINE DELPHI6UP}
        {$DEFINE DELPHI7UP}
        {$DEFINE DELPHI8UP}
{$ENDIF}
{$IFDEF VER170} // Delphi 2005
        {$DEFINE DELPHI}
        {$DEFINE DELPHI2005}
        {$DEFINE DELPHI2UP}
        {$DEFINE DELPHI3UP}
        {$DEFINE DELPHI4UP}
        {$DEFINE DELPHI5UP}
        {$DEFINE DELPHI6UP}
        {$DEFINE DELPHI7UP}
        {$DEFINE DELPHI8UP}
        {$DEFINE DELPHI2005UP}
{$ENDIF}
{$IFDEF VER180} // Delphi 2006
        {$DEFINE DELPHI}
        {$DEFINE DELPHI2006}
        {$DEFINE DELPHI2UP}
        {$DEFINE DELPHI3UP}
        {$DEFINE DELPHI4UP}
        {$DEFINE DELPHI5UP}
        {$DEFINE DELPHI6UP}
        {$DEFINE DELPHI7UP}
        {$DEFINE DELPHI8UP}
        {$DEFINE DELPHI2005UP}
        {$DEFINE DELPHI2006UP}
{$ENDIF}
{$IFDEF VER185} // Delphi 2006
        {$DEFINE DELPHI}
        {$DEFINE DELPHI2006}
        {$DEFINE DELPHI2UP}
        {$DEFINE DELPHI3UP}
        {$DEFINE DELPHI4UP}
        {$DEFINE DELPHI5UP}
        {$DEFINE DELPHI6UP}
        {$DEFINE DELPHI7UP}
        {$DEFINE DELPHI8UP}
        {$DEFINE DELPHI2005UP}
        {$DEFINE DELPHI2006UP}
{$ENDIF}
{$IFDEF VER190}
        {$DEFINE DELPHI}
        {$DEFINE DELPHI2007}
        {$DEFINE DELPHI2UP}
        {$DEFINE DELPHI3UP}
        {$DEFINE DELPHI4UP}
        {$DEFINE DELPHI5UP}
        {$DEFINE DELPHI6UP}
        {$DEFINE DELPHI7UP}
        {$DEFINE DELPHI8UP}
        {$DEFINE DELPHI2005UP}
        {$DEFINE DELPHI2006UP}
        {$DEFINE DELPHI2007UP}
{$ENDIF}
{$IFDEF VER200} // Delphi 2009
        {$DEFINE DELPHI}
        {$DEFINE DELPHI2007}
        {$DEFINE DELPHI2UP}
        {$DEFINE DELPHI3UP}
        {$DEFINE DELPHI4UP}
        {$DEFINE DELPHI5UP}
        {$DEFINE DELPHI6UP}
        {$DEFINE DELPHI7UP}
        {$DEFINE DELPHI8UP}
        {$DEFINE DELPHI2005UP}
        {$DEFINE DELPHI2006UP}
        {$DEFINE DELPHI2007UP}
{$ENDIF}
{$IFDEF VER210} // Delphi 2010
        {$DEFINE DELPHI}
        {$DEFINE DELPHI2007}
        {$DEFINE DELPHI2UP}
        {$DEFINE DELPHI3UP}
        {$DEFINE DELPHI4UP}
        {$DEFINE DELPHI5UP}
        {$DEFINE DELPHI6UP}
        {$DEFINE DELPHI7UP}
        {$DEFINE DELPHI8UP}
        {$DEFINE DELPHI2005UP}
        {$DEFINE DELPHI2006UP}
        {$DEFINE DELPHI2007UP}
{$ENDIF}
{$IFDEF VER220} // Delphi 2011/XE
        {$DEFINE DELPHI}
        {$DEFINE DELPHI2007}
        {$DEFINE DELPHI2UP}
        {$DEFINE DELPHI3UP}
        {$DEFINE DELPHI4UP}
        {$DEFINE DELPHI5UP}
        {$DEFINE DELPHI6UP}
        {$DEFINE DELPHI7UP}
        {$DEFINE DELPHI8UP}
        {$DEFINE DELPHI2005UP}
        {$DEFINE DELPHI2006UP}
        {$DEFINE DELPHI2007UP}
{$ENDIF}
{$IFDEF DELPHI4UP}
        {$DEFINE DYNARRAY}
{$ENDIF}

