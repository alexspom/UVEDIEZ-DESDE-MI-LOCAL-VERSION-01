# M�dulo   : VDCOMPUBIART.PAN
# Funci�n  : Compatibilidades de clases de ubicaciones con clases de art�culos
#
# Creaci�n : 15-11-2007
# Autor    : ICC
###########################################
# Hist�rico de cambios:
COMPATIBILIDAD CON CLASES DE ARTICULO
  
  Clasif.Ubicaci�n Clase Ubicaci�n    Clasif.Art�culo Clase Art�culo   Prohibido     Prio    Ult.Modif:
   _______________ _______________    _______________ _______________      _         @L@     _32__________ �D-MM-Y.YYY    

|
TABLA=VDUBIARTIC
ORDERBY=CODCLASEA,PRIOUBI,CODCLASEU;
PREINSERT=FEJECUTA("CSELMODIF","ERROR AL INSERTAR COD. OPERARIO Y FECHA")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL ACTUALIZAR COD. OPERARIO Y FECHA")

CAMPO=CODCLASIFU,TOOLTIP("C�digo de la clasificaci�n de ubicaciones que se asigna a una clase de art�culos"),
      POSTCHANGE=FEJECUTA("CCLASIFU","No existe  :CODCLASIFU en  clasificaciones de ubicacion"),TITULO("Clasif.Ubicaci�n")
CAMPO=CODCLASEU,TOOLTIP("C�digo de la clase de ubicaciones dentro de la clasificaci�n que se parametriza"),
      POSTCHANGE=FEJECUTA("CCLASEU","No existe la clase :CODCLASEU en la clasificaci�n :CODCLASIFU"),TITULO("Clase Ubicaci�n")
CAMPO=CODCLASIFA,TOOLTIP("C�digo de la clasificaci�n de art�culos que se parametriza"),
      POSTCHANGE=FEJECUTA("CCLASIFA","No existe  :CODCLASIFA en  clasificaciones"),TITULO("Clasif.Art�culo")
CAMPO=CODCLASEA,TOOLTIP("C�digo de la clase de art�culos dentro de la clasificaci�n que se parametriza"),
      POSTCHANGE=FEJECUTA("CCLASEA","No existe la clase :CODCLASEA en la clasificaci�n :CODCLASIFA"),TITULO("Clase Art�culo")
CAMPO=PROHIBIDO      
CAMPO=PRIOUBI, TOOLTIP("Prioridad con la que asignaremos una clase de ubicaci�n a una clase de art�culo"),
      POSTCHANGE=FVALNOCERO("EL CAMPO PRIORIDAD NO PUEDE SER NULO"),TITULO("Prio")
CAMPO=CODOPEMODIF,NOENTER, TOOLTIP("Operario que realiz� la �ltima modificaci�n"),TITULO("Ultima modificaci�n")
CAMPO=FECMODIF, NOENTER, TOOLTIP("Ult. Modif: :CODOPEMODIF :FECMODIF :HORAMODIF")
CAMPO=HORAMODIF, OCULTO,"_8________", NOENTER, TOOLTIP("Hora en que se realiz� la Ultima modificaci�n")

#CURSORES

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CCLASEA SELECT :CODCLASIFA FROM VDCLASES WHERE CODCLASIF=:CODCLASIFA AND CODCLASE=:CODCLASEA;

CURSOR=CCLASEU SELECT :CODCLASIFU FROM VDCLASES WHERE CODCLASIF=:CODCLASIFU AND CODCLASE=:CODCLASEU;

CURSOR=CCLASIFA SELECT :CODCLASIFA FROM VDCLASIFICACIONES WHERE TABLACLASIF='VDARTIC' AND CODCLASIF=:CODCLASIFA;

CURSOR=CCLASIFU SELECT :CODCLASIFU FROM VDCLASIFICACIONES WHERE TABLACLASIF='VDUBICA' AND CODCLASIF=:CODCLASIFU;



