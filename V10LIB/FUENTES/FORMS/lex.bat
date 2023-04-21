SET M4=c:\GnuWin32\bin\M4.EXE
call flex -ov10forlex.c -n v10forlex.l
call c:\GnuWin32\bin\bison.exe -obison.c -l -v --defines=v10parse.h bison.y