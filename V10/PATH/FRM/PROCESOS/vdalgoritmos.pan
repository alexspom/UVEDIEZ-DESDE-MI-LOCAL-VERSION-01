######
# VDALGORITMOS.PAN - Sistema de ventanas de configuración de algoritmos.
# 
# Propósito: Ventana para dar crear/modificar/borrar algoritmos
#               
#           
# Autor	   : José Carlos Santos
# Fecha    : 18-12-2007
####
# Modificaciones:
####
MANTENIMIENTO DE ALGORITMOS
 Algoritmo        Función                    Librería       Act Descripción                                          Fec. Modif Hora modif. Usuario 
 _40_____________ _32_______________________ _256___________ _  _256________________________________________________ ¿D-MM-Y.YY _32________ ________ 
|           

TABLA=VDALGORITMOS

ORDERBY=NOMBREALG;

PREUPDATE=FEJECUTA("CFORMATEADISC","",
                   "CSELMODIF","No se puede actualizar fecha de modificación.")

PREINSERT=FEJECUTA("CFORMATEADISC","",
                   "CSELMODIF","No se puede insertar fecha de modificación.")

CAMPO=NOMBREALG,UPPER,TOOLTIP("Es el nombre del algoritmo"),TITULO("Algoritmo")
CAMPO=FUNCIONALG,MIXED,TOOLTIP("Función del algortimo"),TITULO("Función")
CAMPO=FUNCIONPROC,VIRTUAL,AUXILIAR,OCULTO
CAMPO=LIBALGORITMO,UPPER,TOOLTIP("Librería del algortimo"),TITULO("Librería")
CAMPO=ACTIVO,UPPER,TOOLTIP("Indica si el algoritmo está activo"),TITULO("Act"),WLONX=5,CHECKBOX("N","S")
CAMPO=DISCRIMINANTE,OCULTO,"_256___________________",PROTECT("IMPLANTADOR")
CAMPO=DESALG,TOOLTIP("Descripción del algoritmo"),TITULO("Descripción")
CAMPO=FECMODIF,NOENTER,TITULO("Ultima modificación")
CAMPO=HORAMODIF,NOENTER
CAMPO=CODOPEMODIF,UPPER,NOENTER
CAMPO=PROCESO,VIRTUAL, OCULTO
CAMPO=PARAMALG,OCULTO,"_256________"

TECLA=SF4,FEJECUTA(FMODIFICA,"",FPULSATECLAS("F4"))

CURSOR=CFORMATEADISC SELECT VDPROC.FORMATEADISCRIMINANTE(:FUNCIONPROC,:DISCRIMINANTE) DISCRIMINANTE FROM DUAL;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;  


