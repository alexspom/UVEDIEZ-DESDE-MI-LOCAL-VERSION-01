# Módulo   : VDCOMPUBIEST.PAN
# Función  : Compatibilidades de ubicaciones con la clasificación EMBALAJES.
#            CODCLASIF siempre debe ser EMBALAJES, por defecto se graba EMBALAJES.
#
# Creación : 15-11-2007
# Autor    : ICC
###########################################
# Histórico de cambios:
COMPATIBILIDAD CON EMBALAJES CON CLASES DE UBICACION
 
 Tipo Embalaje   Clase Ubicación        Prio     Ult. Modif.
  __________     _______________         @L@     ¿DD-MM-Y.YYY 

|
TABLA=VDUBIEMBA
ORDERBY=TIPOEMBA,PRIOEMBA,CODCLASE;


PREINSERT=FEJECUTA("CSELMODIF","ERROR AL INSERTAR COD. OPERARIO Y FECHA")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL ACTUALIZAR COD. OPERARIO Y FECHA")

CAMPO=TIPOEMBA,UPPER,TOOLTIP("Código del embalaje a asignar a una ubicación"),
              POSTCHANGE=FEJECUTA("CEMBALAJE","NO EXISTE TIPO DE EMBALAJE"),TITULO("Tipo Embalaje"), WLONX=45
CAMPO=CODCLASE,UPPER,TOOLTIP("Código de la clase de ubicaciones dentro de la clasificación EMBALAJES"),
      POSTCHANGE=FEJECUTA("CCLASEU","No existe la clase :CODCLASE en la clasificación EMBALAJES"),TITULO("Clase Ubicación"), WLONX=55
CAMPO=PRIOEMBA, TOOLTIP("Prioridad con la que asignaremos una clase de ubicación a un tipo de embalaje"),TITULO("Prioridad"), WLONX=40
CAMPO=CODOPEMODIF,OCULTO," _32__________", NOENTER, TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF, NOENTER, TOOLTIP("Ult. Modificación: :CODOPEMODIF :FECMODIF :HORAMODIF"),TITULO("Ult. Modif."),WLONX=55
CAMPO=HORAMODIF, OCULTO,"_8________", NOENTER, TOOLTIP("Hora en que se realizó la Ultima modificación")


#CURSORES

CURSOR=CEMBALAJE SELECT :TIPOEMBA FROM VDTIPOEMBA WHERE TIPOEMBA=:TIPOEMBA;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CCLASEU SELECT CODCLASE FROM VDCLASES WHERE CODCLASIF='EMBALAJES' AND CODCLASE=:CODCLASE;





