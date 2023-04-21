######
# VDPARAMETROS.PAN - Sistema de ventanas de configuración de algoritmos.
#
# Propósito: Ventana para dar crear/modificar/borrar parámetros de los procesos.
#
#
# Autor	   : José Carlos Santos
# Fecha    : 12-12-2007
####
# Modificaciones:
####
PARAMETROS DE LA FUNCION
Parámetro        Valor                  Descripción
_20_____________ _255__________________ _256______________________________
                                                                          |

SOLOQUERY


SELECT= SELECT PAR.NOMBREPARAM,VD.PIECE(PRO.PARAM,'#',PAR.POSICION) VALOR,PAR.POSICION POSICION,PAR.INFORMAR,PAR.DESCRIPCION
        FROM  VDPARAMALGPROC PAR, VDPROCESOS PRO
        WHERE PRO.PROCESO = :PROCESO AND
	            PAR.FUNCION = PRO.FUNCIONPROC AND
	            PAR.TIPOPROC='F';
ORDERBY=PAR.POSICION;

PREUPDATE=FEJECUTA("CUPDPARPROC","ERROR ACTUALIZANDO PARAMETRO DE LA FUNCION",
		               FCOMMIT,"ERROR EN EL COMMIT",
                   FPULSATECLAS("CF2","F2"),"")


CAMPO=PROCESO,VIRTUAL,AUXILIAR,OCULTO
CAMPO=FUNCIONPROC,VIRTUAL,AUXILIAR,OCULTO
CAMPO=NOMBREPARAM,UPPER,TOOLTIP("Es el nombre del parámetro"),TITULO("Parámetro")
CAMPO=VALOR,UPPER,AUXILIAR,POSTCHANGE=FEJECUTA("@CSELINFORMAR","","CSELVALORNULO","Obligatorio informar el parametro :NOMBREPARAM"),  TOOLTIP("Es el valor del parámetro"),TITULO("Valor")
CAMPO=DESCRIPCION,NOUPDATE,TOOLTIP("Descripción del valor"),TITULO("Descripción")
CAMPO=POSICION,OCULTO,"@@@"
CAMPO=INFORMAR,OCULTO,"_"


CURSOR=CSELINFORMAR SELECT :INFORMAR
                      FROM DUAL
                     WHERE :INFORMAR='S';

CURSOR=CSELVALORNULO SELECT :VALOR
                       FROM DUAL
                      WHERE :VALOR IS NOT NULL;

CURSOR=CUPDPARPROC UPDATE VDPROCESOS SET PARAM = VD.SUSTPIECE(PARAM,:POSICION,:VALOR),
                                         CODOPEMODIF = VDUSER.GETUSER, FECMODIF=VD.FECHASYS, HORAMODIF=VD.HORASYS
		                WHERE PROCESO = :PROCESO ;



