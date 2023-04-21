# Módulo   : VDREPULMON.PAN
# Función  : RECEPCIÓN DE MERCANCÍA: Selección del pulmón donde se va a recepcionar
#            Validaciones:
#              - La ubicación debe existir, ser de stock y no bloqueado para entrada.
#              - Buscar la fuente de esa área, es decir, una ubicación que no sea de stock y no esté bloqueada para salida.
#              - El terminal debe poder realizar esta tarea. 
#
# Creación : 30-01-2008
# Autor    : ICC
###########################################
# Histórico de cambios:
# 
SELECCION DEL PULMON
 _10_______ _10_______

/* LEER PULMON DE ENTRADAS */
 PULMON  _12___________
 
|


PREQUERY=FEJECUTA("CLIMPIAR","\nERROR,\nAL LIMPIAR LOS CAMPOS",
                  FPOSICIONACAMPO(FSUCCESS,"PULMON"),"\nERROR,\nAL POSICIONARSE EN EL CAMPO")

POSTQUERY=FEJECUTA(FIF("CSELNOTNULL",FCARGAFORM(""),FSUCCESS),"",
	               "CVERIFPULMON","\nERROR,\nNO EXISTE\n EL PULMON :PULMON",
                   "CSELFUENTE","\nERROR,\nNO EXISTE NINGUNA FUENTE\nEN EL AREA DE :PULMON",
#                   "CPERMISORECURSO", "\nERROR,\nEL TERMINAL NO TIENE\nPERMISOS PARA REALIZAR\nESTA TAREA",
                   FPOSICIONABLOQUE("VDRECORDEN.PAN"),"\nNO SE PUEDE POSICIONAR\nEN EL SIG. BLOQUE")

CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=BLOQUEOS,OCULTO,VIRTUAL
CAMPO=BLOQUEOSORIG,OCULTO,VIRTUAL
CAMPO=PULMON,SCAN,AUTOENTER,POSTCHANGE=FEJECUTA(FIF("CSELNOTNULL",FCARGAFORM("")))
CAMPO=FUENTE,OCULTO,"_12___________"
CAMPO=CODAREA,OCULTO,"_10_______"
CAMPO=CODUBI,OCULTO,"_12___________"
CAMPO=DUMMY,OCULTO,"#"

CURSOR=CLIMPIAR SELECT '' PULMON   FROM DUAL;

CURSOR=CSELNOTNULL SELECT :PULMON FROM DUAL WHERE :PULMON IS NULL;

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

#El terminal debe poder realizar esta tarea.
CURSOR=CPERMISORECURSO SELECT 1 DUMMY
                         FROM VDRECTAREA REC, VDPERFILTAREA PTA,
                              (SELECT PRIVILEGIO
                                 FROM VDPRIVGRU PRG, VDGRUPOOPE GRO
                                WHERE GRO.CODOPE = :CODOPE
                                  AND GRO.CODGRUPO = PRG.CODGRUPO
                               UNION
                               SELECT PRIVILEGIO
                                 FROM VDPRIVOPE
                                 WHERE CODOPE = :CODOPE) B
                        WHERE REC.CODRECURSO= :CODRECURSO
                          AND REC.CODPERFIL = PTA.CODPERFIL
                          AND (TRIM(PTA.PRIVILEGIOSTAREA) IS NULL
                          OR VD.CONTIENECAD(PTA.PRIVILEGIOSTAREA,B.PRIVILEGIO,',','-',1) = 1)
                          AND VD.CONTIENECAD(PTA.RANTAREA, VD.GETPROP('TAREARECEP'),',','-',1) = 1;
