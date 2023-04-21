MENU DE PANTALLAS
MENU
__________ __________

1. PRUEBA
2. Código DE BARRAS
3. SALIR

OPCION _
|

UPPER

CAMPO=CODRECURSO,NOENTER
CAMPO=CODOPE,NOENTER
CAMPO=OPCION,POSTCHANGE=FEJECUTA(FENRANGO("1,3"),"DEBE INTRODUCIR 1 O 2",
                                 FSWITCHCADENA(":OPCION","1",FCARGAFORM("PRUEBA"),
                                                         "2",FCARGAFORM("CB"),
                                                         "3",FDESCONECTAUSUARIO),
                                                         "IMPOSIBLE EJECUTAR")

