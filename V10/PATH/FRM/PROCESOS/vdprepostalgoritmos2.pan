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
LISTA DE PREALGORITMOS
 P.  Funcion        Librería        Act Descripción                          Fec. Modif Hora modif. Usuario 
 @L@ _32____________ _256___________  _  _256_______________________________ ¿D-MM-Y.YY _32________ ________ 
                                                                            |

TABLA=VDPREPOSTALGORITMOS

ORDERBY=PRIORIDAD;

PREINSERT=FEJECUTA("CSEAPOSTALG","Error en CSEAPOSTALG",
                   "CSELMODIF","No se puede insertar fecha de modificación.")
                   
PREUPDATE=FEJECUTA("CSELMODIF","No se puede actualizar fecha de modificación.")


CAMPO=PROCESO,VIRTUAL, OCULTO
CAMPO=NOMBREALG,VIRTUAL,OCULTO
CAMPO=PRIORIDAD
CAMPO=FUNCIONALG
CAMPO=LIBALGORITMO, UPPER
CAMPO=ACTIVO, UPPER
CAMPO=DESALG
CAMPO=FECMODIF, NOENTER
CAMPO=HORAMODIF, NOENTER
CAMPO=CODOPEMODIF, NOENTER
CAMPO=TIPOALG, OCULTO, "_"
CAMPO=PARAMALG,OCULTO,"_256__________________"

TECLA=SF4,FEJECUTA(FMODIFICA,"",FPULSATECLAS("F4"))

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;   
