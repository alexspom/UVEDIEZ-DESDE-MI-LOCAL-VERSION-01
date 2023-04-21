#*****************************************************************
#Módulo: VDTIPORDRECLIN.PAN
#Función: Mantenimiento de las líneas de los tipos de recepción
#Autor: ICC      
#Fecha: 12-02-2008
#*****************************************************************
#* Histórico de cambios
#* ====================
#
MANTENIMIENTO DE LAS LINEAS DE LOS TIPOS DE RECEPCION

Clasificación   Clase          RO RU MUESTREAR AM  C. Lote Est. lote  Est. stock D. Ant D. Ret M. lote Lote por defecto  Mult.   Ultima modificación
_15____________ _15____________ _  _     _      _     _    _10_______ _10_______  ###    ###     _     _40______________ _1____  _32_______ ¿D-MM-Y.YYY _8______
|
TABLA=VDTIPORDRECLIN
WLONY=220


PREINSERT=FEJECUTA("CVALCODCLASIF", "ERROR, EL Código DE CLASIFICACION :CODCLASIF NO EXISTE",
                   "CVALCODCLASE", "ERROR, EL Código DE CLASE :CODCLASE\n NO EXISTE PARA LA CLASIFICACION :CODCLASIF",
                   "-CVALNUMERICO", ":MSGERROR",
                   "CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CVALCODCLASIF", "ERROR, EL Código DE CLASIFICACION :CODCLASIF NO EXISTE",
                   "CVALCODCLASE", "ERROR, EL Código DE CLASE :CODCLASE\n NO EXISTE PARA LA CLASIFICACION :CODCLASIF",
                   "-CVALNUMERICO", ":MSGERROR",
                   "CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")

CAMPO=TIPORDREC,VIRTUAL,TOOLTIP("Tipo de orden de recepción"),OCULTO
CAMPO=CODCLASIF,TOOLTIP("Es el Código alfanumérico único asociado a cada clasificación."),
                CONTEXTUAL=FDESIGNACION(FEJECUTAFORM("VDMNTOCLASIF.FRM","N","","","CODCLASIF=:CODCLASIF","","S")),
                TITULO("Clasificación")
CAMPO=CODCLASE,TOOLTIP("Es el Código alfanumérico asociado a cada clase dentro de la clasificación."),UPPER,
               CONTEXTUAL=FDESIGNACION(FEJECUTAFORM("VDCLASES.FRM","N","","CODCLASIF=:CODCLASIF","CODCLASE=:CODCLASE","","S")),
               TITULO("Clase")
CAMPO=REQUIERE_ORDEN,TOOLTIP("Indicador de si se requiere la existencia de orden de recepción para poder hacer una recepción"),UPPER,
                     POSTCHANGE=FVERIFICA("SN","EL CAMPO DEBE SER S(SI) O N(NO)"),
                     TITULO("RO"),WLONX=15
CAMPO=RECEPCION_UNICA,TOOLTIP("Indica si toda la recepción debe hacerse en una única entrada. Para chequeo de tolerancias"),UPPER,
                      POSTCHANGE=FVERIFICA("SN","EL CAMPO DEBE SER S(SI) O N(NO)"),
                      TITULO("RU"),WLONX=15
CAMPO=MUESTREAR,TOOLTIP("Indicador de si requiere toma de muestras para control de calidad.\n 'N' no se muestrea, 'P' se muestrea por palet,\n 'L' se muestrea por Lote,'R' se muestrea por recepción"),UPPER,
                POSTCHANGE=FVERIFICA("NLPR","EL CAMPO DEBE SER N(NO) O L(LOTE) O P(PALET) O R(RECEPCION)"),
                TITULO("MUESTREAR"),WLONX=70
CAMPO=ALTAS_MANUALES,TOOLTIP("N=Entrada repasada. Debe existir la recepción. S=Se permite dar de alta la línea de recepción"),UPPER,
                     POSTCHANGE=FVERIFICA("SN","EL CAMPO DEBE SER S(SI) O N(NO)"),
                     TITULO("AM"),WLONX=15
CAMPO=CREA_LOTE,TOOLTIP("N=No se permite crear lote.S=Se crea el lote desde la pantalla de recepción"),UPPER,
                POSTCHANGE=FVERIFICA("SN","EL CAMPO DEBE SER S(SI) O N(NO)"),
                TITULO("C.Lote"),WLONX=30
CAMPO=ESTADOS_LOTE,TOOLTIP("Estados con los que se creará el lote cuando CREA_LOTE es distinto de N"),
                   TITULO("Est. Lote"),WLONX=28
CAMPO=ESTADOS_STOCK,TOOLTIP("Cada byte puede tomar un valor que se transmitirá al stock o _ en cuyo caso dicho byte se toma del maestro de lotes"),
                   TITULO("Est. stock"),WLONX=-6
CAMPO=DIASANTFECPREV,TOOLTIP("Días de antelación permitidos sobre la fecha prevista de recepción de una línea de orden de recepción."),
                     TITULO("D.Ant"),WLONX=20
CAMPO=DIASRETFECPREV,TOOLTIP("Días de retraso permitidos sobre la fecha prevista de recepción de una línea de orden de recepción."),
                     TITULO("D.Ret"),WLONX=20
CAMPO=INDLOTE,TOOLTIP("Indicador de si debe mostrarse el lote en pantalla o no, valores: S/N \nSi queremos que se cree el Lote automático tiene que estar a N"),UPPER,
              POSTCHANGE=FVERIFICA("SN","EL CAMPO DEBE SER S(SI) O N(NO)"),
              TITULO("M.Lote"),WLONX=35
CAMPO=LOTEDEF,TOOLTIP("En caso de que INDLOTE=N, deberá informarse el Código de lote por defecto que se creará"),TITULO("Lote por defecto")
CAMPO=MULTIARTICULO,TOOLTIP("Mostrará en la pantalla la posibilidad de recepcionar un palet multiartículo, valores: S/N"),UPPER,
                    POSTCHANGE=FVERIFICA("SN","EL CAMPO DEBE SER S(SI) O N(NO)"),TITULO("Mult."),WLONX=-12
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Es la fecha  en que se efectuó alguna modificación a los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Es la hora en que se efectuó alguna modificación a los datos del registro")
CAMPO=MSGERROR,AUXILIAR,OCULTO,"_100_____________________________________________________________"
CAMPO=DUMMY,AUXILIAR,OCULTO,"#"


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CVALCODCLASIF SELECT 1 DUMMY
                       FROM VDCLASIFICACIONES
                      WHERE CODCLASIF = :CODCLASIF;
                      
CURSOR=CVALCODCLASE SELECT 1 DUMMY
                      FROM VDCLASES
                     WHERE CODCLASIF = :CODCLASIF
                       AND CODCLASE  = :CODCLASE;

CURSOR=CVALNUMERICO SELECT CASE WHEN VD.ISVALOR(:ESTADOS_LOTE, '_0123456789') != 0 THEN
                                     'ERROR, LOS ESTADOS DEL LOTE SOLO PUEDEN SER NUMERICO O "_"'
                                ELSE 'ERROR, LOS ESTADOS DEL STOCK SOLO PUEDEN SER NUMERICO O "_"'
                           END MSGERROR
                      FROM DUAL
                     WHERE VD.ISVALOR(:ESTADOS_LOTE, '_0123456789') != 0
                        OR VD.ISVALOR(:ESTADOS_STOCK, '_0123456789') != 0;

