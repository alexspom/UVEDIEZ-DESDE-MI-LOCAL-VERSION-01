@echo off
REM Script para realizar un Export diario de la BBDD.
REM Siempre que se inicia el proceso, se mueve el ultimo export a la carpeta DIA_ANTERIOR.
REM Por ultimo se comienza el Export y se guarda el fichero con el nombre SMCL%YYYYMMDD%.dmp.
REM Donde %YYYYMMDD% es la fecha en la que es realizado el export.
REM (c) UveDiez Soluciones, S.L. - Eduardo L. Arana

Set DIACTUAL=%TEMP%\DIACTUAL.TMP
DATE /T > %DIACTUAL%
Set PARSEARG="eol=; tokens=1,2,3,4* delims=-/, "
For /F %PARSEARG% %%i in (%DIACTUAL%) Do SET YYYYMMDD=%%l%%k%%j%%i%

cls
echo Moviendo export del dia anterior a la carpeta E:\backup\export\dia-anterior
echo.
@del E:\backup\export\dia-anterior\*.dmp /Q
@move /Y E:\backup\export\dia-actual\SMCL*.dmp E:\backup\export\dia-anterior
echo.
echo Realizando export diario para almacenarlo en E:\backup\export\dia-actual
@exp smcl/smcl@smcl owner=smcl file=E:\backup\export\dia-actual\SMCL%YYYYMMDD%.dmp
exit
  