set wallPath="E:\Pascal5333\Custom System\Wallpapers\%1.bmp"

REG add "HKEY_CURRENT_USER\Control Panel\Desktop" /v Wallpaper /t REG_SZ /d %wallPath% /f
REG add "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Explorer\Wallpapers" /v BackgroundHistoryPath0 /t REG_SZ /d %wallPath% /f
sleep 1
start "" /b RUNDLL32.EXE user32.dll,UpdatePerUserSystemParameters ,1 ,True
start "" /b RUNDLL32.EXE user32.dll,UpdatePerUserSystemParameters ,1 ,True
start "" /b RUNDLL32.EXE user32.dll,UpdatePerUserSystemParameters ,1 ,True
start "" /b RUNDLL32.EXE user32.dll,UpdatePerUserSystemParameters ,1 ,True
sleep 1
start "" /b RUNDLL32.EXE user32.dll,UpdatePerUserSystemParameters ,1 ,True
exit