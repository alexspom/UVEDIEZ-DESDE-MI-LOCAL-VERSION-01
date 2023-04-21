# Módulo   : VDZONAS.PAN
# Función  : Mantenimiento de zonas
#
# Creación : 21-05-2008
# Autor    : Maite González
###########################################
MANTENIMIENTO DEL HARDWARE DE DISPLAYS
Id. Numdisp  Mirror      Ge. Texto                                         Luces            Teclas Est   Estado                  Vdextra Ultima modificación
@L@ @L@@@@@@ @L@ @L@@@@@ @L@ _256_________________________________________ _256____________ _256__ @L@@@ @L@@ _40_______________ _256___ _32________ ¿D-MM-Y.YY ________ _40_____________
|

TABLA=VDINFOHARDDISP
ORDERBY=IDINFOPICK,NUMDISP;

REGPAG=40
PREREGISTRO=FEJECUTA("+CREPRESENTA","")
#TIMEOUT=FPULSATECLAS("1005"),200
WLONX=1050


PROTECT("IMPLANTADOR")

PREINSERT=FEJECUTA("CSELMODIF","No puedo poner fecha/hora modificacion")
PREUPDATE=FEJECUTA("CSELMODIF","No puedo poner fecha/hora modificacion")

CAMPO=IDINFOPICK,NOUPDATE,TOOLTIP("Número de infopick hardware al que se refiere el display"),TITULO("Infopick"),WLONX=35
CAMPO=NUMDISP,NOUPDATE,TOOLTIP("Número de display en la red InfoPick.\nEste Código y el anterior forman la clave primaria."),TITULO("Display")
CAMPO=IDINFOPICKM,TOOLTIP("Número de infopick hardware al que se refiere el display"),TITULO("Inf. Espejo"),WLONX=50
CAMPO=NUMDISPM,TOOLTIP("Número de display en la red InfoPick.\nEste Código y el anterior forman la clave primaria."),TITULO("Espejo")
CAMPO=IDINFOGEST,TOOLTIP("Identificador del programa que gestiona la zona"),TITULO("Ges"),WLONX=20
CAMPO=TEXTO,TOOLTIP("Texto que se muestra en el display"),TITULO("Texto")
CAMPO=LUCES,TOOLTIP("Luces encendidas en el display"),TITULO("Luces")
CAMPO=TECLAS,TOOLTIP("Cola de teclas pulsadas en el display"),TITULO("Teclas")
CAMPO=ESTADOBOT,TOOLTIP("Estado de los botones"),TITULO("Botones"),WLONX=25
CAMPO=STATUS,POSTCHANGE=FDESIGNACION("CSELSTATUS","No existe estado"),TOOLTIP("Status del display"),TITULO("Estado")
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Descripcion del status del display")
CAMPO=VDEXTRA,TOOLTIP("Información adicional del display"),TITULO("Extra")
CAMPO=CODOPEMODIF,NOENTER, TOOLTIP("Usuario que ha realizado la ultima modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER, TOOLTIP("Fecha  en que se efectuó alguna modificación a los datos del registro")
CAMPO=HORAMODIF,NOENTER, TOOLTIP("Es la hora  en que se efectuó alguna modificación a los datos del registro")
CAMPO=CODCOMEN,OCULTO,"@L@@@@@@@@"
CAMPO=V10OBJETO,AUXILIAR,NOUPDATE,TITULO("Objeto")
CAMPO=V10HTML,AUXILIAR,NOUPDATE,OCULTO,"_50000"
CAMPO=V10HTML1,AUXILIAR,NOUPDATE,OCULTO,"_50000"

CURSOR=CSLEEP BEGIN
               WHILE 1=1 LOOP BEGIN
                 SELECT TECLAS INTO :TECLAS FROM VDINFOHARDDISP WHERE IDINFOGEST=:IDINFOGEST AND TECLAS IS NOT NULL AND ROWNUM=1;
                 DBMS_LOCK.SLEEP(0.05);
                 EXCEPTION WHEN NO_DATA_FOUND THEN 
                   DBMS_LOCK.SLEEP(0.05);
                   EXIT;
                END;
               END LOOP;
              END;@
              
CURSOR=CREPRESENTA BEGIN
                     :V10HTML:=VDECOPKG.VARIOS2HTML(:IDINFOPICK,:NUMDISP,25 ,60,10,650,5);
                     EXCEPTION WHEN NO_DATA_FOUND THEN :V10HTML:=NULL;
                   END;@
                          

#POSTCOMMIT=+FEJECUTA(FCOMMIT,"","CSLEEP","",+FEJECUTATODOS(+FRELOADREG,""),"")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CSELSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='IHD';

CURSOR=CESZONA SELECT :IDINFOPICK FROM VDZONAS WHERE IDINFOPICK=:IDINFOPICK AND NUMDISP=:NUMDISP;

CURSOR=CPONVALIDA BEGIN
                 UPDATE VDINFOHARDDISP SET TECLAS='0' WHERE NUMDISP=VD.PIECE(:V10OBJETO,';',2) AND IDINFOPICK=VD.PIECE(:V10OBJETO,';',1);
                 COMMIT;
                END;@
CURSOR=CPONMAS  BEGIN
                 UPDATE VDINFOHARDDISP SET TECLAS='1' WHERE NUMDISP=VD.PIECE(:V10OBJETO,';',2) AND IDINFOPICK=VD.PIECE(:V10OBJETO,';',1);
                 COMMIT;
                END;@
CURSOR=CPONMENOS  BEGIN
                 UPDATE VDINFOHARDDISP SET TECLAS='2' WHERE NUMDISP=VD.PIECE(:V10OBJETO,';',2) AND IDINFOPICK=VD.PIECE(:V10OBJETO,';',1);
                 COMMIT;
                END;@
CURSOR=CPONFUNC BEGIN
                 UPDATE VDINFOHARDDISP SET TECLAS='3' WHERE NUMDISP=VD.PIECE(:V10OBJETO,';',2) AND IDINFOPICK=VD.PIECE(:V10OBJETO,';',1);
                 COMMIT;
                END;@

TECLA=1000,FEJECUTA("CPONVALIDA","EN PONVALIDA","CSLEEP","EN SLEEP",+FEJECUTATODOS(+FRELOADREG,""),"","CREPRESENTA","EN REPRESENTA")
TECLA=1001,FEJECUTA("CPONMAS","EN PONFMAS","CSLEEP","EN SLEEP",+FEJECUTATODOS(+FRELOADREG,""),"","CREPRESENTA","")
TECLA=1002,FEJECUTA("CPONMENOS","EN PONMENOS","CSLEEP","EN SLEEP",+FEJECUTATODOS(+FRELOADREG,""),"","CREPRESENTA","")
TECLA=1003,FEJECUTA("CPONFUNC","EN PONFUNC","CSLEEP","EN SLEEP",+FEJECUTATODOS(+FRELOADREG,""),"","CREPRESENTA","")
#TECLA=1005,FEJECUTA(+FEJECUTATODOS(+FRELOADREG,""),"","CREPRESENTA","")

