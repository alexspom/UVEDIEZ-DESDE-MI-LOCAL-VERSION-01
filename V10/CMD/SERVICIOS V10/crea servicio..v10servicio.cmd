CALL ..\PONPATH
START %DISCO%\V10\BIN\VDCREASERVICIO -LNVDCREASERVICIO  -SNV10SERVICIO -SE"%DISCO%\V10\BIN\vdservicio.exe -OU%BDATOS% -LNvdservicios -SS50000 -SP49999 -WS" -SA2 -SD"SERVICIO GESTOR DE PROCESOS V10" 
pause