# MOdulo   : FUTRECEPCIONES.PAN
# Función  : Menú de Recepciones de Future del V10
#            
# Creación : 21-11-2018
# Autor    : Xavi.
###########################################
# HistOrico de cambios:
# 
MENU DE RECEPCIONES DE V10
 _10_______ _10_______
 MENU DE RECEPCIONES
 1.- GESTION DE MUELLE
 2.- RECEPCIONAR
 3.- COMP. VISUAL
 9.- SALIR
 OPCION @L
|

POSTQUERY=FEJECUTA(FLIMPIABLOQUE("0"),"","CPONCERO","") 

CAMPO=CODRECURSO,VIRTUAL,NOENTER
CAMPO=CODOPE,VIRTUAL,NOENTER

 
                                
CAMPO=OPCION,POSTCHANGE=FEJECUTA(FENRANGO("1-9"),"DEBE INTRODUCIR\n OPCION ENTRE\n 0 Y 9",
                                 FSWITCHCADENA(":OPCION",
                                               "1", FCARGAFORM("VDGESMUELLE.FRM"),
                                               "2", FCARGAFORM("VDRECEPCION.FRM"),                                               
											   "3", FCARGAFORM("VDCOMPVISUAL.FRM"),
                                               "9", FCARGAFORM("VDSALIR.FRM"),
                                               "", FPOSICIONABLOQUE("-1")),"IMPOSIBLE EJECUTAR")

CURSOR=CPONCERO SELECT 0 OPCION FROM DUAL;

CURSOR=CUPDRECURSO UPDATE VDRECURSO 
                      SET NPANTALLA=NULL,
                          STATUS=VDST.FRECBUSCANDO,
                          CODOPEMODIF=:CODOPE, 
                          FECMODIF=VD.FECHASYS, 
                          HORAMODIF=VD.HORASYS
                    WHERE CODRECURSO=:CODRECURSO;
