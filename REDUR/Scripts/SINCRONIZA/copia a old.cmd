XCOPY E:DATABASE "E:\Copy of Database" /Y /E
XCOPY F:DATABASE "F:\Copy of Database" /Y /E
XCOPY G:DATABASE "G:\Copy of Database" /Y /E
XCOPY H:DATABASE "H:\Copy of Database" /Y /E
rem forfiles /D -1 /P I:\ORACLE\ARCHIVE /M *.DBF /C "CMD /C DEL @PATH"
exit