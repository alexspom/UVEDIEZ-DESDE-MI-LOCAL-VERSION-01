#*****************************************************************
#Módulo: VDRECCABMANUAL.PAN
#Funcionalidad : Mantenimiento de la cabecera de recepción para recepciones manuales
#Autor: ICC      
#Fecha: 25-03-2008
#*****************************************************************
#* Histórico de cambios
#* ====================
CABECERA DE RECEPCION MANUAL

Cod. recepción Tipo   Pulmón     Cod. Orden     División            Albarán transportista                Albarán proveedor Clave ext Fecha recepción     Estado Observaciones                Ultima modificación             
_20___________ _10___ _15_______ _20____________ _20_ _40__________ _20__________ _40___________________ _20_____________  _50_____ ¿D-MM-Y.YYY _8______ #####  _60__________ _60__________ _32_________ ¿D-MM-Y.YY ________
|
TABLA=VDRECEPCAB
WHERE=STATUS = VDST.FRCCACTIVA
  AND SWTRECEP ='M';
ORDERBY=TO_NUMBER(CODRECEP) DESC, CODDIV;


PROTECT("RECEPCIONES")

POSTQUERY=FEJECUTA("CSELPULMON","ERROR SELECCIONANDO EL PULMON")

PREUPDATE=FEJECUTA("CVALTIPO", "ERROR TIPO DE ORDEN NO PERMITIDO PARA ALTAS MANUALES",
                   "CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION",
                   FCOMMIT,"")

PREINSERT=FEJECUTA("CVALTIPO", "ERROR TIPO DE ORDEN NO PERMITIDO PARA ALTAS MANUALES",
                   "CSELDEFECTO", "ERROR SELECCIONANDO LOS VALORES POR DEFECTO",
                   "CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION",
                   FCOMMIT,"")

CAMPO=CODRECEP,TOOLTIP("Número único y clave de recepción.Utiliza la secuencia VDSECRECEP"),NOENTER,TITULO("Cod. Recepción")
CAMPO=TIPORDREC,NOUPDATE,TOOLTIP("Tipo de orden de recepción que debe existir en la tabla VDTIPORDREC "),
                CONTEXTUAL=FDESIGNACION(FEJECUTAFORM("VDTIPORDREC.FRM","N","TIPORDREC IN (SELECT TIPORDREC FROM VDTIPORDRECLIN A WHERE A.TIPORDREC = TIPORDREC AND ALTAS_MANUALES='S')","","TIPORDREC=:TIPORDREC","","S")),
                TITULO("Tipo")
CAMPO=PULMON,AUXILIAR,TOOLTIP("Ubicación pulmón donde se va a recepcionar"), 
             POSTCHANGE=FEJECUTA("CVERIFPULMON","\nERROR,\nNO EXISTE\n EL PULMON :PULMON",
                                 "CSELFUENTE","\nERROR,\nNO EXISTE NINGUNA FUENTE\nEN EL AREA DE :PULMON"),
             TITULO("Pulmón")
CAMPO=CODUBI,AUXILIAR,OCULTO,"_20_______"
CAMPO=CODAREA,AUXILIAR,OCULTO,"_20_______"
CAMPO=CODORDREC,TOOLTIP("Código de la orden de recepción. Si esta informado debe existir en VDCABORDREC"),
                CONTEXTUAL=FDESIGNACION(FEJECUTAFORM("VDORDENESRECEP.FRM","N","","","CODORDREC=:CODORDREC CODDIV=:CODDIV TIPORDREC=:TIPORDREC","","S")),
                TITULO("Cod. Orden")
CAMPO=CODDIV,NOUPDATE,TOOLTIP("Código de la división/compañía.Para permitir duplicidad de Ordenes en distintas divisiones = interfases"),
             POSTCHANGE=FDESIGNACION("CSELDESDIV", "ERROR, DIVISION NO EXISTE"), TITULO("División")
CAMPO=DESDIV,AUXILIAR,NOENTER
CAMPO=CODALBTRAN,TOOLTIP("Código del albarán del transportista"),TITULO("Albarán Transportista")
CAMPO=DESTRAN,TOOLTIP("Designación del transportista")
CAMPO=CODALBPROVE,TOOLTIP("Código de albarán de proveedor"),TITULO("Albarán Proveedor"),WLONX=30
CAMPO=CLAVEEXT,TOOLTIP("Clave externa que permite relacionar con otros sistemas no definidos"),TITULO("Clave Ext."),WLONX=20
CAMPO=FECRECEP,NOENTER,TOOLTIP("Fecha de la recepción"),TITULO("Fecha Recepción")
CAMPO=HORARECEP,NOENTER,TOOLTIP("Hora de la recepción")
CAMPO=STATUS,NOENTER,TOOLTIP("Es el estado en el que se encuentra la recepción"),TITULO("Estado")
CAMPO=OBSERVACION1,TOOLTIP("Observaciones a la cabecera de recepción"),TITULO("Observaciones")
CAMPO=OBSERVACION2,TOOLTIP("Más observaciones a la cabecera de recepción")
CAMPO=VDEXTRA,OCULTO,"_255_",TOOLTIP("Datos adicionales externos a V10 y útiles para el cliente")
CAMPO=CODCOMEN,OCULTO,"#########",TOOLTIP("Código de comentario")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Usuario que ha realizado la Ultima modificación.Es utilizado para depuración y control de los registros en las tablas"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Es la fecha  en que se efectuó alguna modificación. Es utilizado para depuración y control de los registros en las tablas")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Es la hora  en que se efectuó alguna modificación. Es utilizado para depuración y control de los registros en las tablas")
CAMPO=SWTRECEP,OCULTO,"_"
CAMPO=DUMMY,AUXILIAR,OCULTO,"#"

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CSELDESDIV SELECT DESDIV
                    FROM VDDIVIS
                   WHERE CODDIV = :CODDIV;

CURSOR=CSELPULMON SELECT CODUBIDEST PULMON
                    FROM VDMOVIM
                   WHERE CODRECEP = :CODRECEP
                     AND CODCONCE IN (SELECT CODCONCE 
                                        FROM VDTIPORDRECCAB
                                       WHERE TIPORDREC = :TIPORDREC);

#La ubicación debe existir y ser de stock y no bloqueado para entrada y salida:
CURSOR=CVERIFPULMON SELECT CODAREA
                      FROM VDUBICA
                     WHERE CODUBI    = :PULMON
                       AND STOCK     = 'S'
                       AND BLOQUEOSE = 'N'
                       AND BLOQUEOSS = 'N';

#Buscar la fuente de esa área, es decir, una ubicación que no sea de stock y no esté bloqueada para salida.
CURSOR=CSELFUENTE SELECT CODUBI
                    FROM VDUBICA
                   WHERE CODAREA = :CODAREA
                     AND STOCK     = 'N'
                     AND BLOQUEOSS = 'N';

CURSOR=CVALTIPO SELECT 1 DUMMY
                  FROM VDTIPORDRECLIN LTO
                 WHERE LTO.TIPORDREC = :TIPORDREC
                   AND LTO.ALTAS_MANUALES='S';

CURSOR=CSELDEFECTO SELECT VDSECRECEP.NEXTVAL CODRECEP, VDST.FRCCACTIVA STATUS, 'M' SWTRECEP, VD.FECHASYS FECRECEP, VD.HORASYS HORARECEP
                     FROM DUAL;

#CONTEXTUAL=FDESIGNACION(FEJECUTAFORM("VDORDENESRECEP.FRM","S","CODORDREC=:CODORDREC CODDIV=:CODDIV","","","","S"))                           

