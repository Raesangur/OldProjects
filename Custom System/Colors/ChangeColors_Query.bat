set Reg[0]="HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Explorer\Accent"
set Reg[1]="HKEY_CURRENT_USER\Software\Microsoft\Windows\DWM"

set Key[0]=StartColorMenu
set Key[1]=AccentColor
set Key[2]=ColorizationColor

set StartColor=0
set AccentColor=0
set ColorizationColor=0

for /f "tokens=3" %%a in ('reg query %Reg[0]%  /V %Key[0]% ^|findstr /ri "REG_DWORD"') do set StartColor=%%a
for /f "tokens=3" %%a in ('reg query %Reg[1]%  /V %Key[1]% ^|findstr /ri "REG_DWORD"') do set AccentColor=%%a
for /f "tokens=3" %%a in ('reg query %Reg[1]%  /V %Key[2]% ^|findstr /ri "REG_DWORD"') do set ColorizationColor=%%a

echo %StartColor%
echo %AccentColor%
echo %ColorizationColor%

(
   echo %StartColor%
   echo %AccentColor%
   echo %ColorizationColor%
) > Colors_%1%.txt