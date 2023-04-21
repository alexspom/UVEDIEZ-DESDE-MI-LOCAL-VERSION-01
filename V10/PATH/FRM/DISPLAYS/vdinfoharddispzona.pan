# Módulo   : VDZONAS.PAN
# Función  : Mantenimiento de zonas
#
# Creación : 21-05-2008
# Autor    : Maite González
###########################################
MANTENIMIENTO DEL HARDWARE DE DISPLAYS
Id. Numdisp Ge. Texto                 Luces           Teclas           Est   Estado            Vdextra       Ultima modificación
@L@ @L@@@@@ @L@ _256_________________ _256___________ _256____________ @L@@@ @L@@ _40_________ _256_________ _32________ ¿D-MM-Y.YY ________
|

TABLA=VDINFOHARDDISP
ORDERBY=IDINFOPICK,NUMDISP;


PROTECT("IMPLANTADOR")
WLONX=1050

PREINSERT=FEJECUTA("CSELMODIF","No puedo poner fecha/hora modificacion")
PREUPDATE=FEJECUTA("CSELMODIF","No puedo poner fecha/hora modificacion")

CAMPO=IDINFOPICK,NOUPDATE,TOOLTIP("Número de infopick hardware al que se refiere el display"),TITULO("Display")
CAMPO=NUMDISP,NOUPDATE,TOOLTIP("Número de display en la red InfoPick.\nEste Código y el anterior forman la clave primaria.")
CAMPO=IDINFOGEST,TOOLTIP("Identificador del programa que gestiona la zona"),TITULO("Ge.")
CAMPO=TEXTO,TOOLTIP("Texto que se muestra en el display"),TITULO("Texto")
CAMPO=LUCES,TOOLTIP("Luces encendidas en el display"),TITULO("Luces")
CAMPO=TECLAS,TOOLTIP("Cola de teclas pulsadas en el display"),TITULO("Teclas")
CAMPO=ESTADOBOT,TOOLTIP("Estado de los botones"),TITULO("Botones")
CAMPO=STATUS,POSTCHANGE=FDESIGNACION("CSELSTATUS","No existe estado"),TOOLTIP("Status del display"),TITULO("Estado")
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Descripcion del status del display")
CAMPO=VDEXTRA,TOOLTIP("Información adicional del display"),TITULO("Vdextra")
CAMPO=CODOPEMODIF,NOENTER, TOOLTIP("Usuario que ha realizado la ultima modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER, TOOLTIP("Fecha  en que se efectuó alguna modificación a los datos del registro")
CAMPO=HORAMODIF,NOENTER, TOOLTIP("Es la hora  en que se efectuó alguna modificación a los datos del registro")
CAMPO=CODCOMEN,OCULTO,"@L@@@@@@@@"

CURSOR=CSLEEP DECLARE
                TECLAS VARCHAR2(100);
              BEGIN
               WHILE 1=1 LOOP BEGIN
                 SELECT TECLAS INTO TECLAS FROM VDINFOHARDDISP WHERE (IDINFOPICK,NUMDISP) IN (SELECT IDINFOPICK,NUMDISP FROM VDINFODISP WHERE CODZONA=:CODZONA) AND TECLAS IS NOT NULL AND ROWNUM=1;
                 DBMS_LOCK.SLEEP(0.1);
                 EXCEPTION WHEN NO_DATA_FOUND THEN 
                   DBMS_LOCK.SLEEP(0.2);
                   EXIT;
                END;
               END LOOP;
              END;@
                          

POSTCOMMIT=+FEJECUTA(FCOMMIT,"","CSLEEP","",+FEJECUTATODOS(+FRELOADREG,""),"")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CSELSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='IHD';

CURSOR=CESZONA SELECT :IDINFOPICK FROM VDZONAS WHERE IDINFOPICK=:IDINFOPICK AND NUMDISP=:NUMDISP;

CURSOR=CPONVALIDA SELECT '0' TECLAS FROM DUAL;
CURSOR=CPONMAS SELECT '1' TECLAS FROM DUAL;
CURSOR=CPONMENOS SELECT '2' TECLAS FROM DUAL;
CURSOR=CPONFUNC SELECT '3' TECLAS FROM DUAL;

TECLA=SF1,FEJECUTA("CPONVALIDA","",FPULSATECLAS("F4"),"")
TECLA=SF2,FEJECUTA("CPONMAS","",FPULSATECLAS("F4"),"")
TECLA=SF3,FEJECUTA("CPONMENOS","",FPULSATECLAS("F4"),"")
TECLA=SF4,FEJECUTA("CPONFUNC","",FPULSATECLAS("F4"),"")


BOTON=B1,985,106,50,50,"P",restart.png,SF1,"Validar",INCLUDECSS="background-color: transparent;border-width:0px"
BOTON=B2,950,98,40,40,"P",symbol_add.png,SF2,"Mas",INCLUDECSS="background-color: transparent;border-width:0px"
BOTON=B3,950,160,40,40,"P",symbol_remove.png,SF3,"Menos",INCLUDECSS="background-color: transparent;border-width:0px"
BOTON=B4,985,160,40,40,"P",build.png,SF4,"Funcion",INCLUDECSS="background-color: transparent;border-width:0px"

TECLA=F3,FEJECUTA(FEJECUTATODOS(FRELOADREG,"ERROR EN RELOAD"),"OTRO")

TIMEOUT=QUERYAUTOM,100

ONLINE={S-F1} Validar {S-F2} Mas {S-F3} Menos {S-F4} Funcion;

