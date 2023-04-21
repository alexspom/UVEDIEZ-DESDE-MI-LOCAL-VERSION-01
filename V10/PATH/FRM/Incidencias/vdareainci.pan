# Módulo   : VDAREAINCI.PAN
# Función  : POSIBLES AREAS ASOCIADAS A LAS INCIDENCIAS
#
# Creación : 14-09-2009
# Autor    : JCSR
# Fichero generado por el Asistente de Generación de Pantallas V10 
###########################################
# Histórico de cambios:
AREAS ASOCIADAS A INCIDENCIAS
 COD. AREA            DESCRIPCIÓN AREA                                  CODOPEMODIF                             FECMODIF   HORAMODIF
 _20_________________ _50_______________________________________________ _32__ _93______________________________ ¿D-MM-Y.YY ________
                                                                                                                                     |

TABLA = VDINCIAREA
PREINSERT = FEJECUTA ( "CSELMODIF","ERROR EN CSELMODIF" )
PREUPDATE = FEJECUTA ( "CSELMODIF","ERROR EN CSELMODIF" )

PQUERY

REGPAG=30

CURSOR = CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

# LISTA DE CAMPOS DE LA PANTALLA
CAMPO = AREA, TITULO ("COD. AREA"),TOOLTIP("Identificador de área asociada a una posible incidencia.")
CAMPO = DESAREA , TITULO ("DESCRIPCIÓN AREA"),TOOLTIP("Descripción del área asociada a una posible incidencia ")
CAMPO = CODOPEMODIF, TITULO ( "MODIFICADO POR" ), NOENTER , POSTCHANGE = FDESIGNACION ("+CSELCODOPELARGO", " No se ha encontrado al operario. ")
CAMPO = CODOPELARGO, AUXILIAR , NOENTER
CAMPO = FECMODIF, NOENTER , TITULO ("EN FECHA Y HORA")
CAMPO = HORAMODIF, NOENTER

# PARTE PERSONALIZADA DE LA PANTALLA 
CURSOR = CSELCODOPELARGO SELECT RTRIM (NOMBRE)||' '||RTRIM (APELLIDO1)||' '|| RTRIM (APELLIDO2) CODOPELARGO 
                           FROM VDUSUARIO
						  WHERE CODOPE = :CODOPEMODIF;
						  
#BOTON = BUSCAR,980,80,70,70,"Buscar",buscar.png,F2,"Buscar",INCLUDECSS="background-color: transparent;border-width:0px"
#BOTON = ACEPTAR,1050,80,70,70,"ACEPTAR LOS CAMBIOS",miok.png,F4,"ACEPTAR LOS CAMBIOS",INCLUDECSS="background-color: transparent;border-width:0px"
  
  