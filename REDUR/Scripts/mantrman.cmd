REM ***********************************************************************************************************************
REM * Mantenimiento de las copias de seguridad - Borra las copias con una antiguedad mayor a 7 dias - Autor: E-A (el pibe)
REM ***********************************************************************************************************************
@echo off
cls
echo.
echo Borra las copias con una antiguedad mayor a 7 dias...
@rman catalog=rman/rman@ipcb target sys/sys@ipcb @E:\backup\Scripts\mantrman.rman
rem pause
exit