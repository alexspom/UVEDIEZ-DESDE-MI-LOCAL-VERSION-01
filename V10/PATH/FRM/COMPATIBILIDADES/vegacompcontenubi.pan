# Módulo   : VEGACOMPUBICONT.PAN
# Función  : Compatibilidades de tipos de contenedores con clases de ubicaciones
#
# Creación : 07-04-2022
# Autor    : VEGA
###########################################
# Histórico de cambios:
COMPATIBILIDAD DE TIPOS DE CONTENEDORES CON CLASE DE UBICACIONES VEGA

 Tipo de                                             Altura      Peso
 Contenedor    Clasif.Ubicación Clase Ubicación      Máx.(cm)   Máx.(gr)        Prio.   Ult. Modif.
 __________    _______________ _______________      #L####### #L#,###,###        @L@    _32__________ ¿DD-MM-Y.YYY  

|
TABLA=VEGAUBICONTE
ORDERBY=TIPOCONTE,PRIOUBI,CODCLASIF,CODCLASE;

PREINSERT=FEJECUTA("CSELMODIF","ERROR AL INSERTAR COD. OPERARIO Y FECHA")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL ACTUALIZAR COD. OPERARIO Y FECHA")

CAMPO=TIPOCONTE,TOOLTIP("Código del contenedor a asignar a una ubicación"),
                POSTCHANGE=FEJECUTA("CTIPOCONTE","TIPO DE CONTENEDOR NO EXISTE O NO ES MOVIBLE"),TITULO("Tipo Conte")
CAMPO=CODCLASIF,TOOLTIP("Código de la clasificación de ubicaciones que se asigna a un tipo de contenedor"),TITULO("Clasif. Ubicación")
CAMPO=CODCLASE,TOOLTIP("Código de la clase de ubicaciones dentro de la clasificación que se parametriza"),
               POSTCHANGE=FEJECUTA("CCLASEU","No existe la clase :CODCLASE en la clasificación :CODCLASIF"),TITULO("Clase Ubicación")
CAMPO=ALTURAMAX,TOOLTIP("Altura maxima de los contenedores a ubicar en esta clase de ubicación, en centímetros"),TITULO("Alt. Máx (cm)"),WLONX=30
CAMPO=PESOMAX,TOOLTIP("Peso máximo de los contenedores a ubicar en esta clase de ubicación, en gramos"),TITULO("Peso Máx (gr)"), WLONX=45

CAMPO=PRIOUBI, TOOLTIP("Prioridad con la que asignaremos una clase de ubicación a un tipo de contenedor"),TITULO("Prio"), WLONX=18
CAMPO=CODOPEMODIF, NOENTER, TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF, NOENTER, TOOLTIP("Ult. Modificación: :CODOPEMODIF :FECMODIF :HORAMODIF")
CAMPO=HORAMODIF,OCULTO,"_8________", NOENTER, TOOLTIP("Hora en que se realizó la Ultima modificación")


#CURSORES

CURSOR=CPONCLASIF SELECT 'UBICACIONES' OBJCLASIF,'CONTENEDORES' CODCLASIF FROM DUAL;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CCLASEU SELECT CODCLASE FROM VEGACLASES WHERE CODCLASIF=:CODCLASIF AND CODCLASE=:CODCLASE ;

CURSOR=CTIPOCONTE SELECT :TIPOCONTE FROM VEGATIPOCONTE WHERE TIPOCONTE=:TIPOCONTE AND MOVIBLE='S';



