# Módulo   : VDINFOMENUS.PAN
# Función  : Mantenimiento de menus de picking
#
# Creación : 21-05-2008
# Autor    : Maite González
###########################################
MENUS DE PICKING
Menú       Padre Menú Ord Texto            A Función                     Estado               T.Tick Presenta                  Cod.Ope.     Ultima modificación
_10_______ _10_______ @L@ _256____________ _ _255_______________________ @L@@@ _32___________ @L@@@@ _255_____________________ _32_________ ¿D-MM-Y.YY ________
|

TABLA=VDINFOMENUS
ORDERBY=PADREMENU,ORDENMENU;

PROTECT("SUPERVISOR")

PREINSERT=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")

CAMPO=IDMENU,TOOLTIP("Identificador del menu"),TITULO("Menú")
CAMPO=PADREMENU,TOOLTIP("Padre de la opcion de menu"),TITULO("Padre Menú")
CAMPO=ORDENMENU,TOOLTIP("Orden de la opcion dentro del padre"),TITULO("Ord")
CAMPO=TEXTO,TOOLTIP("Texto que aparece en el display"),TITULO("Texto")
CAMPO=TIPOACCION,TOOLTIP("Accion que ejecuta la opcion de menu M->submenu F->Función con parametros"),TITULO("A")
CAMPO=FUNCION,TOOLTIP("Funcion que se ejecuta cuando se confirma"),TITULO("Función")
CAMPO=STATUSORIGZONA,POSTCHANGE=FDESIGNACION(FIF("-CHAYSTATUS","CSELSTATUS"),"No existe estado"),TOOLTIP("Status original de la zona para entrar en el menu"),TITULO("Estado")
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Descripcion del estatus original de la zona")
CAMPO=TTICK, TOOLTIP("Tiempo en centésimas de segundo para ejecutar el tick"),TITULO("T.TICK")
CAMPO=FPRESENTA, TOOLTIP("Función que se ejecuta en cada tick"),TITULO("Función TICK")
CAMPO=CODOPEMODIF,NOENTER, TOOLTIP("Usuario que ha realizado la ultima modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER, TOOLTIP("Fecha  en que se efectuó alguna modificación a los datos del registro")
CAMPO=HORAMODIF,NOENTER, TOOLTIP("Es la hora  en que se efectuó alguna modificación a los datos del registro")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CSELSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUSORIGZONA AND TIPOSTATUS='ZON';
CURSOR=CHAYSTATUS SELECT 0 STATUSORIGZONA FROM DUAL WHERE :STATUSORIGZONA = 0;

