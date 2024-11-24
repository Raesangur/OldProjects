set Reg[0]="HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Explorer\Accent"
set Reg[1]="HKEY_CURRENT_USER\Software\Microsoft\Windows\DWM"

set a=%Line[0]%
set b=%Line[1]%
set c=%Line[2]%

REG add %Reg[0]% /v StartColorMenu /t REG_DWORD /d %a% /f
REG add %Reg[0]% /v AccentColorMenu /t REG_DWORD /d %b% /f
REG add %Reg[1]% /v AccentColor /t REG_DWORD /d %b% /f
REG add %Reg[1]% /v AccentColorInactive /t REG_DWORD /d %b% /f
REG add %Reg[1]% /v ColorizationColor /t REG_DWORD /d %c% /f
REG add %Reg[1]% /v ColorizationAfterglow /t REG_DWORD /d %c% /f