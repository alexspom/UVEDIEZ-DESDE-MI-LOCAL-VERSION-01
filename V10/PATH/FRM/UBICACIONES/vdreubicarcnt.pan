#*****************************************************************
#Módulo: VDREUBICARCNT.PAN
#Funcionalidad : Reubica un palet compelto a una ubicación compatible
#Autor: ICC      
#Fecha: 08-05-2008
#*****************************************************************
#* Histórico de cambios
#* ====================
#*****************************************************************
REUBICAR PALETS COMPLETOS
Ubicación    Area       B Matrícula          Tipo       Código seriado       Posición  Altura  Reubicar
_20_________ _10_______ _ _18_______________ _10_______ _20_________________ @L9@@@    @L9@@@     _
|

SOLOQUERY   
SELECT=SELECT CNT.CODMAT, CNT.TIPOCONTE, CNT.CODUBI, CNT.POSCONTE, CNT.ALTURACONTE, UBI.CODAREA,BLOQUEOSE
         FROM VDCONTE CNT, VDUBICA UBI
        WHERE CNT.CODUBI = UBI.CODUBI AND UBI.TIPOUBI='R'
          AND CNT.TIPOCONTE NOT IN ( 'VIRTUAL','TMP');

ORDERBY=CNT.CODMAT, UBI.CODAREA;

WLONX=1150
PREUPDATE=FEJECUTA(FIF("CUPDREUBI", FEJECUTA(FREUBICONTE(":CODMAT",":TAREA","CODMOV","","",""),":V10ERROR",
                                            %FFAILURE,"GENERADO MOVIMIENTO :CODMOV",
                                            FCOMMIT,"")),"")

CAMPO=CODUBI,TOOLTIP("Código de la ubicación donde se encuentra el contenedor"),TITULO("Ubicación"),PREFIJO=UBI
CAMPO=CODAREA,NOUPDATE,TOOLTIP("Código del área donde se encuentra el contenedor"),TITULO("Area")
CAMPO=BLOQUEOSE,TOOLTIP("Bloqueo de recargas"),TITULO("B")
CAMPO=CODMAT,TOOLTIP("Matricula del contenedor en el que se halla el stock"),TITULO("Matrícula")
CAMPO=TIPOCONTE,NOENTER,TOOLTIP("Tipo de contenedor"),TITULO("Tipo")
CAMPO=CNTSSCC,TOOLTIP("Código seriado del contenedor"),TITULO("Código Seriado")
CAMPO=POSCONTE,TOOLTIP("Posición del contenedor en la ubicación"),TITULO("Posición"),WLONX=22
CAMPO=ALTURACONTE,TOOLTIP("Altura del contenedor"),TITULO("Altura"),WLONX=20
CAMPO=REUBI,AUXILIAR,TITULO("Reubi"),POSTCHANGE=FVERIFICA("SN ","Valores: S=Enviar a ubicación libre, N o blanco=No reubicar"),WLONX=20
CAMPO=CODMOV,OCULTO,"@L9@@@"
CAMPO=TAREA,OCULTO,AUXILIAR,"_32_"

CURSOR=CUPDREUBI SELECT 'REUBICAR' TAREA FROM DUAL WHERE :REUBI = 'S';

                      
