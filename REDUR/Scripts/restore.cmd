REM **************************************************************************************
REM * Restauracion completa de la base de datos desde un hotbackup - Autor: E-A (el pibe)
REM **************************************************************************************
@echo off
cls
echo.
echo Restauracion de la copia de seguridad activa de Rman.
echo.
echo PRECAUCION: Este script borra y restaura los datos con un dia de antiguedad.
echo.
echo Para salir de este script, debes pulsar CTRL+C.
echo.
pause
rem rman target=sys/sys cmdfile=E:\backup\Scripts\restore.rman
