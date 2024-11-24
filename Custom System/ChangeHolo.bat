@echo off

set "scriptPath=.\"
set cursorScript="%scriptPath%Cursors\ChangeCursors.bat"
set wallpaperScript="%scriptPath%Wallpapers\ChangeWallpaper.bat"
set colorScript="%scriptPath%Colors\ChangeColors.bat"
set rgbScript="%scriptPath%RGB\G910_RGB.exe"

set /a delay=%2%+2 

start "RGB" /min %rgbScript% RGB\%1 %delay%
start /min cmd /c %wallpaperScript% %1%
start /min cmd /c %cursorScript% %1%
start /min cmd /c %colorScript% %1%
