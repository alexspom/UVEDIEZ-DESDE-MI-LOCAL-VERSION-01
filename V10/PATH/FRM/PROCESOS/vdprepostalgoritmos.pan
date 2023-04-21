######
# VDPREPOSTALGORITMOS.PAN - Sistema de ventanas de configuración de algoritmos.
# 
# Propósito: Ventana para dar crear/modificar/borrar algoritmos
#               
#           
# Autor	   : José Carlos Santos
# Fecha    : 18-12-2007
####
# Modificaciones:
####
LISTA DE PREALGORITMOS Y POSTALGORITMOS
 Tipo              P.  Función         Librería        Act Descripción                          Fec. Modif Hora modif. Usuario 
 _ _______________ @L@ _32____________ _256___________ _1_ _256_______________________________ ¿D-MM-Y.YY _32________ ________ 
                                                                            |

TABLA=VDPREPOSTALGORITMOS

ORDERBY=DECODE(TIPOALG,'A',0,'D',1),PRIORIDAD;

PREINSERT=FEJECUTA("CSELMODIF","No se puede insertar fecha de modificación.")
                   
PREUPDATE=FEJECUTA("CSELMODIF","No se puede actualizar fecha de modificación.")

POSTQUERY=FEJECUTA("CDAMEDESCTIPO","")

CAMPO=TIPOALG,TOOLTIP("Tipo de ejecución (A)ntes del algoritmo o (D)espués del algoritmo"),TITULO("Tipo")
CAMPO=DESCTIPO,AUXILIAR,NOENTER,TOOLTIP("Descripción del tipo")
CAMPO=PROCESO,VIRTUAL, OCULTO
CAMPO=NOMBREALG,VIRTUAL,OCULTO
CAMPO=PRIORIDAD,TOOLTIP("Prioridad de ejecución"),TITULO("P.")
CAMPO=FUNCIONALG,TOOLTIP("Nombre de la función"),TITULO("Función")
CAMPO=LIBALGORITMO, UPPER,TOOLTIP("Nombre de la librería, si está vacío, está en el ejecutable"),TITULO("Librería")
CAMPO=ACTIVO, UPPER,TOOLTIP("Indica si está o no activo"),TITULO("Act")
CAMPO=DESALG,TOOLTIP("Designación del pre/postalgoritmo"),TITULO("Descripción")
CAMPO=FECMODIF, NOENTER,TITULO("Ultima modificación")
CAMPO=HORAMODIF, NOENTER
CAMPO=CODOPEMODIF, NOENTER

CAMPO=PARAMALG,OCULTO,"_256__________________"

CURSOR=CDAMEDESCTIPO SELECT DECODE(:TIPOALG,'A','PREALGORITMO','D','POSTALGORITMO') DESCTIPO FROM DUAL;

TECLA=SF4,FEJECUTA(FMODIFICA,"",FPULSATECLAS("F4"))

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;   


