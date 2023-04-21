REM ************************************************************************************
REM * Script de copia de archivos en caliente con RMAN - Autor: E-A (el pibe)
REM ************************************************************************************
@echo off
cls
echo.
echo Lanzando RMAN para iniciar la copia de archivos en caliente...
@rman catalog=RMAN/RMAN@SMMX target=SYS/SYS@SMMX @D:\SMMX\Scripts\backuporacle.rman
REM pause
exit