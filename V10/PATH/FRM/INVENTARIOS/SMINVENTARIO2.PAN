#*****************************************************************
#MOdulo: VDINVENCONTEOS.PAN
#Funcionalidad : Muestra todos los conteos de los inventarios.
#Autor: ICC      
#Fecha: 03-02-2010
#*****************************************************************
#* HistOrico de cambios
#* ====================
#
STOCK INVENTARIADO
Lin  OK   Ubic.      Matricula  Art�culo                              Teorico  Real    Term.   Operario Fecha inicio         Fecha fin            Estado                  Rec. Tipoinven   Orig Mov
@L@@ ___  _20_______ _20_______ _20_______ _40_______________________ #L###### #L##### _20____ _32_____ �D-MM-Y.YYY _8______ �D-MM-Y.YYY _8______ ###### _40_____________ @L@@ _10________ @L@@ @L@@@@@@
|

TABLA=VDINVENCONTEO
SELECT=SMINVEN.ESCORRECTA(CODINVEN,SEQINVEN) CORRECTA;
ORDERBY=SEQPADRE,CODUBI,SEQINVEN;
INCLUDECSS="inventario.css"
WLONX=1390

#NODELETE
NOINSERT,PROTECT("V10")


CAMPO=CODINVEN,TOOLTIP("C�digo de inventario"),VIRTUAL, OCULTO
CAMPO=SEQINVEN,NOUPDATE,TITULO("Lin.")
CAMPO=CORRECTA,AUXILIAR,NOUPDATE,TITULO("OK")
CAMPO=CODUBI,NOUPDATE("SUPERVISOR"),TOOLTIP("C�digo de ubicaci�n a inventariar"),TITULO("Ubicacion"),WLONX=20
CAMPO=CODMAT,NOUPDATE("SUPERVISOR"),TITULO("Matricula")
CAMPO=CODARTREAL,NOUPDATE,TOOLTIP("C�digo de art�culo despu�s de inventariar"),POSTCHANGE=FDESIGNACION("+CSELDESARTR",""),TITULO("Art�culo")
CAMPO=DESARTR,NOENTER,AUXILIAR,NOENTER,TITULO("Descripci�n")
CAMPO=CANTTEORICO,NOENTER,TITULO("Te�rico"),WLONX=15
CAMPO=CANTREAL,NOENTER,TOOLTIP("Cantidad total despu�s de inventariar, incluidas las rotas"),TITULO("Real"),WLONX=15
CAMPO=CODRECURSO,NOUPDATE("V10"),TITULO("Term.")
CAMPO=CODOPE,TOOLTIP("C�digo de operario que realiza el inventario"),TITULO("Operario"),WLONX=20
CAMPO=FECINI,NOUPDATE("SUPERVISOR"),TOOLTIP("Fecha en juliano en que se inicia el inventario, es decir, cuando al operario comienza a inventariar la matr�cula"),TITULO("Fecha inicio")
CAMPO=HORAINI,NOUPDATE("SUPERVISOR"),TOOLTIP("Hora en que se inicia el inventario, es decir, cuando al operario comienza a inventariar la matr�cula")
CAMPO=FECFIN,NOUPDATE("SUPERVISOR"),TOOLTIP("Fecha en juliano en que se se finaliza el recuento de la matr�cula"),TITULO("Fecha fin")
CAMPO=HORAFIN,NOUPDATE("SUPERVISOR"),TOOLTIP("Hora en que se se finaliza el recuento de la matr�cula")
CAMPO=STATUS,NOUPDATE("SUPERVISOR"),POSTCHANGE=FDESIGNACION("+CSELDESSTATUS","No existe status"),TITULO("Estado")
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TITULO("Desc.")
CAMPO=RECONTEO,NOUPDATE,TITULO("Conteos"),WLONX=18
CAMPO=TIPOINVEN,NOUPDATE,TITULO("Tipo")
CAMPO=ANTSEQINVEN,OCULTO,"@L@@@@@"
CAMPO=SEQPADRE,TITULO("Origen"),WLONX=15
CAMPO=CODMOV,NOUPDATE,TITULO("Mov.")

CURSOR=CSELDESARTR SELECT DESART DESARTR
                     FROM VDARTIC
                    WHERE CODART = :CODARTREAL;

CURSOR=CSELDESSTATUS SELECT DESSTATUS 
                       FROM VDSTATUS
                      WHERE TIPOSTATUS = 'INO'
                        AND STATUS = :STATUS;
                        
CURSOR=CHAYMOV SELECT :CODMOV FROM DUAL WHERE :CODMOV!=0;                        
                        
CONTEXTUAL=FIF("CHAYMOV",FLEEMENU("VDINVENCONTEO.ZOO"),
                        FEJECUTAFORM("VDUBICA","S","CODUBI=:CODUBI"))


ONLINE= {F1} Ayuda    {F2} Consulta    {Esc} Cerrar Pantalla    {F5} Borrar Pantalla    ;


