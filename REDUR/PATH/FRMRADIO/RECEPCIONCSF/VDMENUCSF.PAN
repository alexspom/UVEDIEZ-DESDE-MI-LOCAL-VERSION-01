# Módulo   : VDMENUV10.PAN
# Función: Menú del administrador de V10
#            
# Creación : 07-02-2008
# Autor    : ICC
###########################################
# Histórico de cambios:
# 
MENU DE OPERARIO 
 _10_______ _10_______
 MENU DE OPERARIO 
 1.- RECEPCIONAR
 2.- UBICAR
 3.- CONSULTAS
 4.- SALIR
 OPCION @L
|

POSTQUERY=FEJECUTA(FLIMPIABLOQUE("0"),"") 

CAMPO=CODRECURSO,VIRTUAL,NOENTER
CAMPO=CODOPE,VIRTUAL,NOENTER
CAMPO=OPCION,POSTCHANGE=FEJECUTA(FENRANGO("1-4"),"DEBE INTRODUCIR\n OPCION ENTRE\n 1 Y 4",
                                 FSWITCHCADENA(":OPCION",
                                 "1", FCARGAFORM("VDRECEPCIONCSF.FRM"),
                                 "2", FCARGAFORM("VDUBICAENTRADASCSF.FRM"), 
                                 "3", FCARGAFORM("VDMENUCONSULTAS.FRM"),
                                 "4", FCARGAFORM("VDSALIR.FRM"),
                                 "", FPOSICIONABLOQUE("-1")),"NO EXISTE LA OPCION")

CURSOR=CUPDRECURSO UPDATE VDRECURSO 
                      SET NPANTALLA=NULL,
                          STATUS=#STRECBUSCANDO,
                          CODOPEMODIF=:CODOPE, 
                          FECMODIF=VD.FECHASYS, 
                          HORAMODIF=VD.HORASYS
                    WHERE CODRECURSO=:CODRECURSO;
