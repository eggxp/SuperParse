@echo off
if not exist doc\nul mkdir ..\Help
del doc\*.chm
del doc\*.hhc
del doc\*.hhk
del doc\*.hhp
del doc\*.htm*
del doc\*.gif
del doc\*.log
DIPasDoc_Console.exe -OHtml -Edoc -Isrc src\*.pas
