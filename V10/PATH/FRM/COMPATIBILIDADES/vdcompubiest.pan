# Módulo   : VDCOMPUBIEST.PAN
# Función  : Compatibilidades de ubicaciones con la clasificación estados.
#            CODCLASIF siempre debe ser estados, por defecto se graba estados.
#
# Creación : 15-11-2007
# Autor    : ICC
###########################################
# Histórico de cambios:
COMPATIBILIDAD CON ESTADOS DE MERCANCIA
 
Clasif         Clase           Patrón               Ult Modif:
______________ _______________ ____________________ ¿DD-MM-Y.YYY 

|
TABLA=VDUBIESTADO


PREINSERT=FEJECUTA("CSELMODIF","ERROR AL INSERTAR COD. OPERARIO Y FECHA")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL ACTUALIZAR COD. OPERARIO Y FECHA")

CAMPO=CODCLASIF,TITULO("Clasif.")
CAMPO=CODCLASE,WLONX=20,UPPER,TOOLTIP("Código de la clase de ubicación dentro de la clasificación ESTADOS"),
      POSTCHANGE=FEJECUTA("CCLASE","No existe la clase :CODCLASE en la clasificación ESTADOS"),TITULO("Clase 'ESTADOS'")
CAMPO=PATRONESTADO,TOOLTIP("Máscara patrón de estados con la que se exige compatibilidad"),
      POSTCHANGE=FVALNOCERO("EL PATRON DE LA UBICACION NO PUEDE SER NULO"),TITULO("Patrón")
CAMPO=CODOPEMODIF,OCULTO,"_32__________", NOENTER, TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF, NOENTER, TOOLTIP("Ult. Modificación: :CODOPEMODIF :FECMODIF :HORAMODIF"),TITULO("Ult. Modif.")
CAMPO=HORAMODIF, OCULTO,"_8________",NOENTER, TOOLTIP("Hora en que se realizó la Ultima modificación")



#CURSORES

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CCLASE SELECT CODCLASE FROM VDCLASES WHERE CODCLASIF=:CODCLASIF AND CODCLASE=:CODCLASE;
