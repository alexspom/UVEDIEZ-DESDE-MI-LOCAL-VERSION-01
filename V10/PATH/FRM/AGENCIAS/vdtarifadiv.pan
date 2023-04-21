# Módulo   : VDTARIFADIV.PAN
# Función  : Asignación de tarifas a divisiones
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
ASIGNACION DE DIVISIONES
 División                  Clase Validez    Hasta      Ultima modificación
 _20_ _40_________________   _   ¿D-MM-Y.YY ¿D-MM-Y.YY _32________ ¿D-MM-Y.YY  ________
|

TABLA=VDTARIFADIV
ORDERBY=CODDIV;


PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION",
                   "CSELCLASE","ERROR, No todas las divisiones tienen la misma clase de tarifa.")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION",
                   "CSELCLASE","ERROR, No todas las divisiones tienen la misma clase de tarifa..")
POSTQUERY=FEJECUTA("CSELCLASE","ERROR, No todas las divisiones tienen la misma clase de tarifa...")


CAMPO=SEQTARIFA,VIRTUAL,OCULTO
CAMPO=CODAGE,VIRTUAL,OCULTO
CAMPO=CODDIV,POSTCHANGE=FDESIGNACION("CSELDESDIV","No existe división"),TOOLTIP("Código de la división"),TECLA=SF10,FEJECUTAFORM("VDDIVIS","N","","","CODDIV=:CODDIV","","S"),
             TITULO("División")
CAMPO=DESDIV,AUXILIAR,NOENTER,TOOLTIP("Designación de la división")
CAMPO=CLASETARIFA,UPPER,POSTCHANGE=FVERIFICA("CV","Debe introducir C(oste) o V(enta)"),TOOLTIP("Clase de la tarifa debe ser C(oste) o V(enta)"),
             TITULO("Clase"),WLONX=30
CAMPO=FECDESDE,TOOLTIP("Fecha inicio de validez de la tarifa"),TITULO("Validez"),COMBOX("CALENDARIO"),WLONX=30
CAMPO=FECHASTA,TOOLTIP("Fecha de final de validez de la tarifa"),TITULO("Hasta"),COMBOX("CALENDARIO"),WLONX=30
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ult. Modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")
CAMPO=DUMMY,AUXILIAR,OCULTO,"@"
CAMPO=CODCOMEN,OCULTO,"@@@@@"


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CSELDESDIV SELECT DESDIV FROM VDDIVIS WHERE CODDIV=:CODDIV;

CURSOR=CSELCLASE SELECT 1 DUMMY
                   FROM (SELECT CLASETARIFA FROM VDTARIFADIV 
                          WHERE SEQTARIFA=:SEQTARIFA AND CODAGE=:CODAGE 
                          GROUP BY CLASETARIFA) 
                 HAVING COUNT(*) < 2;

AYUDA=ASIGNACION DE TARIFAS A DIVISIONES

#TECLA=SF10,FLEEMENU("VDTARIFADIV.ZOO")

ONLINE=   {F4} Confirmar Cambios   {F6} Cambio de pantalla   {F9} Borrar Registro   {May-F10} Menú contextual;
