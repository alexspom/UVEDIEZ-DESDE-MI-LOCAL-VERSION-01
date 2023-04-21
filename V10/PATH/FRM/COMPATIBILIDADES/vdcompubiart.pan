# Módulo   : VDCOMPUBIART.PAN
# Función  : Compatibilidades de clases de ubicaciones con clases de artículos
#
# Creación : 15-11-2007
# Autor    : ICC
###########################################
# Histórico de cambios:
COMPATIBILIDAD CON CLASES DE ARTICULO
  
  Clasif.Ubicación Clase Ubicación    Clasif.Artículo Clase Artículo   Prohibido     Prio    Ult.Modif:
   _______________ _______________    _______________ _______________      _         @L@     _32__________ ¿D-MM-Y.YYY    

|
TABLA=VDUBIARTIC
ORDERBY=CODCLASEA,PRIOUBI,CODCLASEU;
PREINSERT=FEJECUTA("CSELMODIF","ERROR AL INSERTAR COD. OPERARIO Y FECHA")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL ACTUALIZAR COD. OPERARIO Y FECHA")

CAMPO=CODCLASIFU,TOOLTIP("Código de la clasificación de ubicaciones que se asigna a una clase de artículos"),
      POSTCHANGE=FEJECUTA("CCLASIFU","No existe  :CODCLASIFU en  clasificaciones de ubicacion"),TITULO("Clasif.Ubicación")
CAMPO=CODCLASEU,TOOLTIP("Código de la clase de ubicaciones dentro de la clasificación que se parametriza"),
      POSTCHANGE=FEJECUTA("CCLASEU","No existe la clase :CODCLASEU en la clasificación :CODCLASIFU"),TITULO("Clase Ubicación")
CAMPO=CODCLASIFA,TOOLTIP("Código de la clasificación de artículos que se parametriza"),
      POSTCHANGE=FEJECUTA("CCLASIFA","No existe  :CODCLASIFA en  clasificaciones"),TITULO("Clasif.Artículo")
CAMPO=CODCLASEA,TOOLTIP("Código de la clase de artículos dentro de la clasificación que se parametriza"),
      POSTCHANGE=FEJECUTA("CCLASEA","No existe la clase :CODCLASEA en la clasificación :CODCLASIFA"),TITULO("Clase Artículo")
CAMPO=PROHIBIDO      
CAMPO=PRIOUBI, TOOLTIP("Prioridad con la que asignaremos una clase de ubicación a una clase de artículo"),
      POSTCHANGE=FVALNOCERO("EL CAMPO PRIORIDAD NO PUEDE SER NULO"),TITULO("Prio")
CAMPO=CODOPEMODIF,NOENTER, TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF, NOENTER, TOOLTIP("Ult. Modif: :CODOPEMODIF :FECMODIF :HORAMODIF")
CAMPO=HORAMODIF, OCULTO,"_8________", NOENTER, TOOLTIP("Hora en que se realizó la Ultima modificación")

#CURSORES

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CCLASEA SELECT :CODCLASIFA FROM VDCLASES WHERE CODCLASIF=:CODCLASIFA AND CODCLASE=:CODCLASEA;

CURSOR=CCLASEU SELECT :CODCLASIFU FROM VDCLASES WHERE CODCLASIF=:CODCLASIFU AND CODCLASE=:CODCLASEU;

CURSOR=CCLASIFA SELECT :CODCLASIFA FROM VDCLASIFICACIONES WHERE TABLACLASIF='VDARTIC' AND CODCLASIF=:CODCLASIFA;

CURSOR=CCLASIFU SELECT :CODCLASIFU FROM VDCLASIFICACIONES WHERE TABLACLASIF='VDUBICA' AND CODCLASIF=:CODCLASIFU;



