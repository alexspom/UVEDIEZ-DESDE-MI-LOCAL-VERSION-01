# Módulo   : VDCOMPUBICONT.PAN
# Función  : Compatibilidades de clases de ubicaciones con contenedores
#
# Creación : 15-11-2007
# Autor    : ICC
###########################################
# Histórico de cambios:
COMPATIBILIDAD CON TIPOS DE CONTENEDORES 

                                   Tipo de                           Altura      Peso
Clasif.Ubicación Clase Ubicación   contenedor                        Máx.(cc)   Máx.(gr)    Prio.   Ult. Modif.
 _______________ _______________   __________ _20___________________ #L####### #L#,###,###  @L@     _32__________ ¿DD-MM-Y.YYY  

|
TABLA=VDUBICONTE
ORDERBY=CODCLASIF,CODCLASE,TIPOCONTE,PRIOUBI;

PREINSERT=FEJECUTA("CSELMODIF","ERROR AL INSERTAR COD. OPERARIO Y FECHA")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL ACTUALIZAR COD. OPERARIO Y FECHA")

CAMPO=CODCLASIF,TOOLTIP("Código de la clasificación de ubicaciones que se asigna a un tipo de contenedor"),TITULO("Clasif.Ubicación")
CAMPO=CODCLASE,TOOLTIP("Código de la clase de ubicaciones dentro de la clasificación que se parametriza"),
               POSTCHANGE=FEJECUTA("CCLASEU","No existe la clase :CODCLASE en la clasificación :CODCLASIF"),TITULO("Clase Ubicación")
CAMPO=TIPOCONTE,TOOLTIP("Código del contenedor a asignar a una ubicación"),
                POSTCHANGE=FEJECUTA("CTIPOCONTE","TIPO DE CONTENEDOR NO EXISTE O NO ES MOVIBLE","+CTIPOCONTE2",""),TITULO("Tipo Conte")
CAMPO=DESTIPOCONTE,AUXILIAR,NOENTER,TITULO("")
CAMPO=ALTURAMAX,TOOLTIP("Altura maxima de los contenedores a ubicar en esta clase de ubicación, en centímetros"),TITULO("Alt.Max (cc)"),WLONX=45
CAMPO=PESOMAX,TOOLTIP("Peso máximo de los contenedores a ubicar en esta clase de ubicación, en gramos"),TITULO("Peso.Max (gr)"), WLONX=45
CAMPO=PRIOUBI, TOOLTIP("Prioridad con la que asignaremos una clase de ubicación a un tipo de contenedor"),TITULO("Prio"), WLONX=18
CAMPO=CODOPEMODIF, NOENTER, TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF, NOENTER, TOOLTIP("Ult. Modificación: :CODOPEMODIF :FECMODIF :HORAMODIF")
CAMPO=HORAMODIF,OCULTO,"_8________", NOENTER, TOOLTIP("Hora en que se realizó la Ultima modificación")


#CURSORES

CURSOR=CPONCLASIF SELECT 'UBICACIONES' OBJCLASIF,'CONTENEDORES' CODCLASIF FROM DUAL;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CCLASEU SELECT CODCLASE FROM VDCLASES WHERE CODCLASIF=:CODCLASIF AND CODCLASE=:CODCLASE ;

CURSOR=CTIPOCONTE SELECT :TIPOCONTE FROM VDTIPOCONTE WHERE TIPOCONTE=:TIPOCONTE AND MOVIBLE='S';

CURSOR=CTIPOCONTE2 SELECT DESTIPOCONTE FROM VDTIPOCONTE WHERE TIPOCONTE=:TIPOCONTE;


