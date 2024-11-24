@echo off
setlocal enabledelayedexpansion

set delay=28

set list[0]=Amelia
set list[1]=Botan
set list[2]=Calli
set list[3]=Coco
set list[4]=Gura
set list[5]=Ina
set list[6]=Marine
set list[7]=Pekora
set list[8]=Polka
set list[9]=Suisei
set list[10]=Towa
set list[11]=Watame
set list[12]=Miko
set list[13]=Fubuki
set list[14]=Mio
set list[15]=Kanata
set list[16]=Hololive

:loopbegin
(for /l %%a in (0, 1, 16) do (
    echo !List[%%a]!
    call ChangeHolo.bat !list[%%a]! %delay%
    sleep %delay% > NUL 2>&1
))
goto loopbegin