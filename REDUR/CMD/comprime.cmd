CALL PONPATH
SET YYYYMMDD=%DATE:~6,4%%DATE:~3,2%%DATE:~0,2%

exp ALLOGA/ALLOGA@DEVEL owner=ALLOGA file=E:\PROYECTOS\ALLOGA\V10DATOS\BACKUP\ALLOGA.dmp > E:\PROYECTOS\ALLOGA\V10DATOS\LOG\export.log
"c:\Program Files\7-zip\7z" a -r  E:\PROYECTOS\ALLOGA\V10DATOS\BACKUP\alcura E:\PROYECTOS\ALLOGA\*.* -xr!*.exp -xr!*.pdb -xr!*.sdf -xr!*.bak -xr!*.idb -xr!*.tlog -xr!*.xlsx -xr!*.rar -xr!*.zip -xr!*.7z -xr!*.dmp -xr!*.log -xr!*.obj -xr!*.bsc -xr!*.pch
"c:\Program Files\7-zip\7z" a -r -sdel E:\PROYECTOS\ALLOGA\V10DATOS\BACKUP\ALLOGADMP E:\PROYECTOS\ALLOGA\V10DATOS\BACKUP\ALLOGA.dmp