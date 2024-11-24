@echo off
setlocal EnableExtensions EnableDelayedExpansion
set "File2Read=E:\Pascal5333\Custom System\Colors\Colors_%1.txt"
set /a count=0
for /f "delims=" %%a in ('Type "%File2Read%"') do (
    set "Line[!count!]=%%a"
    set /a count+=1
)

call "E:\Pascal5333\Custom System\Colors\ChangeColors_Helper.bat"
exit