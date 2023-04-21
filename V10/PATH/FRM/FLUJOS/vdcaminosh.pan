#M�dulo: VDCAMINOS.PAN
#Funci�n: Mantenimiento de caminos
#
# Creaci�n : 13-11-2007
# Autor    : ICC
###########################################
# Hist�rico de cambios:
MANTENIMIENTO DE CAMINOS

 C�digo    Descripci�n                                 Area origen        Area Dest.         Operario   Ultima modificaci�n
 @L@@@@@@@ _60________________________________________ _20______________  _20______________  _32_________ �D-MM-Y.YY ________ 
|

TABLA=VDCAMINOS
ORDERBY=CODCAMINO;
NOINSERT

PREINSERT=FEJECUTA("CSELMODIF","ERROR AL INSERTAR COD. OPERARIO Y FECHA",
                   "CSELSECCAM","ERROR AL SELECCIONAR EL SECUENCIAL DEL CAMINO")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL ACTUALIZAR COD. OPERARIO Y FECHA")

CAMPO=CODCAMINO,VIRTUAL,NOUPDATE,TOOLTIP("C�digo del camino."),TITULO("C�digo")
CAMPO=DESCAMINO, TOOLTIP("Descripci�n del camino."),POSTCHANGE=FVALNOCERO("DEBES INDICAR DESCRIPCION DEL CAMINO"),TITULO("Descripci�n")
CAMPO=CODAREAORI, TOOLTIP("C�digo alfanum�rico del �rea origen del este camino"),
                  POSTCHANGE=FDESIGNACION("CCODAREAO","EL C�digo DE AREA DE ORIGEN NO EXISTE"),
                  CONTEXTUAL=FEJECUTAFORM("VDSELAREA","N","","","CODAREAORI=:CODAREA","Selecci�n de �rea","S"),TITULO("Area Orig."),
                  COMBOX("CSELAREA")
CAMPO=CODAREADEST, TOOLTIP("C�digo alfanum�rico del �rea destino del este camino"),
                   POSTCHANGE=FDESIGNACION("CCODAREAD","EL C�digo DE AREA DE DESTINO NO EXISTE"),
                   CONTEXTUAL=FEJECUTAFORM("VDSELAREA","N","","","CODAREADEST=:CODAREA","Selecci�n de �rea","S"),TITULO("Area Dest."),
                   COMBOX("CSELAREA")
CAMPO=CODOPEMODIF, NOENTER, TOOLTIP("Operario que realiz� la �ltima modificaci�n"),TITULO("Ultima modificaci�n")
CAMPO=FECMODIF, NOENTER, TOOLTIP("Es la fecha  en que se efectu� alguna modificaci�n.")
CAMPO=HORAMODIF, NOENTER, TOOLTIP("Es la hora  en que se efectu� alguna modificaci�n.")


#CURSORES
CURSOR=CSELAREA SELECT CODAREA CODAREAORI, CODAREA CODAREADEST FROM VDAREA ORDER BY CODAREA;

CURSOR=CSELMODIF SELECT VD.HORASYS HORAMODIF, VD.FECHASYS FECMODIF, VDUSER.GETUSER CODOPEMODIF FROM DUAL; 
CURSOR=CCODAREAO SELECT CODAREA CODAREAORI FROM VDAREA WHERE CODAREA=:CODAREAORI;
CURSOR=CCODAREAD SELECT CODAREA CODAREADEST FROM VDAREA WHERE CODAREA=:CODAREADEST;
CURSOR=CSELSECCAM SELECT VDSECCAMINO.NEXTVAL CODCAMINO FROM DUAL;
CURSOR=CSELAREAO SELECT CODAREA CODAREAORI FROM VDAREA;
CURSOR=CSELAREAD SELECT CODAREA CODAREADEST FROM VDAREA;




