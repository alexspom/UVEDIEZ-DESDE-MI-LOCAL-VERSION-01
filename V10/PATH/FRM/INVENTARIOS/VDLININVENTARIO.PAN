#*****************************************************************
#MOdulo: VDINVENCONTEOS.PAN
#Funcionalidad : Muestra todos los conteos de los inventarios.
#Autor: ICC      
#Fecha: 03-02-2010
#*****************************************************************
#* HistOrico de cambios
#* ====================
#
LINEAS DE INVENTARIO
Inven.   Lin  Ubic.       Matricula Artículo                              Teorico  Real    Term.     Operario Fecha inicio         Fecha fin            Estado                         Anr.  Re Tipo        Mov.    
@L,@@@@@ @L@@ _20________ _20______ _20______ _40________________________ #L###### #L##### _20______ _32_____ ¿D-MM-Y.YYY _8______ ¿D-MM-Y.YYY _8______ ###### _40____________________ @L@@@ @L ___________ @L@@@@@@@
|

TABLA=VDINVENCONTEO
ORDERBY=STATUS DESC,CODUBI,FECINI DESC, HORAINI DESC;
INCLUDECSS="inventario.css"
WLONX=1200

#NODELETE
NOINSERT,PROTECT("V10")
REGPAG=40


CAMPO=CODINVEN,TOOLTIP("Código de inventario"),TITULO("Inven.")
CAMPO=SEQINVEN,NOUPDATE,TITULO("Lin.")
CAMPO=CODUBI,TOOLTIP("Código de ubicación a inventariar"),TITULO("Ubicacion"),WLONX=20
CAMPO=CODMAT,TITULO("Matricula")
CAMPO=CODARTREAL,NOUPDATE("V10"),TOOLTIP("Código de artículo después de inventariar"),POSTCHANGE=FDESIGNACION("+CSELDESARTR",""),TITULO("Artículo")
CAMPO=DESARTR,NOENTER,AUXILIAR,NOENTER,TITULO("Descripción")
CAMPO=CANTTEORICO,NOENTER,TITULO("Teórico"),WLONX=15
CAMPO=CANTREAL,NOENTER,TOOLTIP("Cantidad total después de inventariar, incluidas las rotas"),TITULO("Real"),WLONX=15
CAMPO=CODRECURSO,NOUPDATE("V10"),TITULO("Term.")
CAMPO=CODOPE,NOENTER,TOOLTIP("Código de operario que realiza el inventario"),TITULO("Operario"),WLONX=20
CAMPO=FECINI,NOENTER,TOOLTIP("Fecha en juliano en que se inicia el inventario, es decir, cuando al operario comienza a inventariar la matrícula"),TITULO("Fecha inicio")
CAMPO=HORAINI,NOENTER,TOOLTIP("Hora en que se inicia el inventario, es decir, cuando al operario comienza a inventariar la matrícula")
CAMPO=FECFIN,NOENTER,TOOLTIP("Fecha en juliano en que se se finaliza el recuento de la matrícula"),TITULO("Fecha fin")
CAMPO=HORAFIN,NOENTER,TOOLTIP("Hora en que se se finaliza el recuento de la matrícula")
CAMPO=STATUS,NOUPDATE("SUPERVISOR"),POSTCHANGE=FDESIGNACION("+CSELDESSTATUS","No existe status"),TITULO(""),WLONX=5
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TITULO("Estado"),WLONX=60
CAMPO=ANTSEQINVEN
CAMPO=RECONTEO
CAMPO=TIPOINVEN
CAMPO=CODMOV,NOUPDATE("V10")


CURSOR=CSELDESARTR SELECT DESART DESARTR
                     FROM VDARTIC
                    WHERE CODART = :CODARTREAL;

CURSOR=CSELDESSTATUS SELECT DESSTATUS 
                       FROM VDSTATUS
                      WHERE TIPOSTATUS = 'INO'
                        AND STATUS = :STATUS;
                        
CONTEXTUAL=FEJECUTAFORM("VDUBICA","S","CODUBI=:CODUBI")


ONLINE= {F1} Ayuda    {F2} Consulta    {Esc} Cerrar Pantalla    {F5} Borrar Pantalla    ;


CONTEXTUAL=FLEEMENU("VDINVENCONTEO.ZOO")