###################################################################
#Módulo: VDSERIEPREP.PAN
#Funcionalidad : Mantenimiento de series de preparación
#Autor: FPD      
#Fecha: 21-04-2008
###################################################################
# Histórico de cambios:
MANTENIMIENTO DE SERIES DE PREPARACION          
Código Prio. I  P Estado               Descripción 
@@@@@@  @@@  _  _ @@@@@ _30___________ _1000_______________________________________ 
|

TABLA=VDSERIEPREP
ORDERBY=STATUS, CODSERIEPREP DESC;

PREINSERT=FEJECUTA("CSELMODIF","ERROR EN CSELMODIF","CSELINSERT","No se ha podido recuperar un Código de pedido o la fecha/hora de creación.")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN CSELMODIF")
PREDELETE=FEJECUTA("CQUITASERIEPED","ERROR ELIMINANDO SERIE")

WFRAME(105,-2,91,0,"Picking","")
#WLONY=100

CAMPO=CODSERIEPREP,NOUPDATE,TOOLTIP("Código de la serie de preparación"),TITULO("Código"),WLONX=20
CAMPO=PRIORIDAD,TOOLTIP("Prioridad de la serie de preparación. La heredan todas las series de expedición generadas a partir de esta serie de preparación"),TITULO("Prio."),WLONX=20
CAMPO=SWTPICKINGINV,TOOLTIP("Indica si la serie es de picking inverso"),TITULO("I")
CAMPO=TIPOPUERTO,UPPER,TOOLTIP("Indica si el puerto de salida utilizado es el asignado por defecto o es uno alternativo"),
                 POSTCHANGE=FVERIFICA("DA ","Los posibles valores de puerto son D(efecto) o A(lternativo)."),TITULO("P")
CAMPO=STATUS,TOOLTIP("Estado en que se encuentra la serie de preparación\n :DESSTATUS"),
             POSTCHANGE=FDESIGNACION("+CDESSTATUS",""),TITULO("Estado")
CAMPO=DESSTATUS,AUXILIAR,TITULO("")
CAMPO=DESSERIE,TITULO("Descripción")
CAMPO=CODOPECREADA,OCULTO,"_32__________"
CAMPO=FECCREADA,OCULTO,"¿D-MM-Y.YY"
CAMPO=HORACREADA,OCULTO,"________"
CAMPO=CODOPELANZA,OCULTO,"_32__________"
CAMPO=FECLANZA,OCULTO,"¿D-MM-Y.YY"
CAMPO=HORALANZA,OCULTO,"________"
CAMPO=FECTERMIN,OCULTO,"¿D-MM-Y.YY"
CAMPO=HORATERMIN,OCULTO,"________"
CAMPO=CODOPEMODIF,OCULTO,"_32__________"
CAMPO=FECMODIF,OCULTO,"¿D-MM-Y.YY"
CAMPO=HORAMODIF,OCULTO,"________"
CAMPO=RANGOZONASPICKINV,OCULTO,"_1000____________________"

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CSELINSERT SELECT VDSECSERIEPREP.NEXTVAL CODSERIEPREP,
                         VD.FECHASYS FECCREADA,VD.HORASYS HORACREADA,
                         VDST.FSPRCREADA STATUS, VDUSER.GETUSER CODOPEMODIF,
                         VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF
			              FROM DUAL;

CURSOR=CQUITASERIEPED UPDATE VDPEDIDOCAB 
                         SET CODSERIEPREP=0,CODSERIEEXP=0 
                       WHERE CODSERIEPREP=:CODSERIEPREP;

CURSOR=CDESSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='SPR';

CONTEXTUAL=FLEEMENU("VDSERIEPREP.ZOO")

