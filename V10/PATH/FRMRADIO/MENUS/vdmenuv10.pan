# Módulo   : VDMENUV10.PAN
# Función: Menú del administrador de V10
#            
# Creación : 07-02-2008
# Autor    : ICC
###########################################
# Histórico de cambios:
# 
MENU DEL IMPLANTADOR DE V10
 _10_______ _10_______
 MENU DEL IMPLANTADOR DE V10
 0.-  BUSCAR TRABAJO
 1.-  RECEPCIONAR
 2.-  UBICAR
 3.-  CONSULTA MATRICULA
 4.-  CONSULTA UBICACION
 5.-  UBICA DEVOLUCION
 6.-  RECOGE DESTRUCCIONES
 7.-  REUBICAR CONTENEDOR
 8.-  SIMULAR SCANNER
 9.-  VERIFICA FMD
 10.- PICKING
 11.- SALIR
 OPCION @L
|

POSTQUERY=FEJECUTA(FLIMPIABLOQUE("0"),"","CPONCERO","") 

CAMPO=CODRECURSO,VIRTUAL,NOENTER
CAMPO=CODOPE,VIRTUAL,NOENTER

 
                                
CAMPO=OPCION,POSTCHANGE=FEJECUTA(FENRANGO("0-11"),"DEBE INTRODUCIR\n OPCION ENTRE\n 0 Y 9",
                                 FSWITCHCADENA(":OPCION",
                                 "0", FEJECUTA("CUPDRECURSO","ERROR \nACTUALIZANDO \nRECURSO",
                                                FCOMMIT,"ERROR \nEN COMMIT",
                                                FCARGATERMINAL("CODOPE"),"ERROR \nCARGANDO \nRECURSO"),
                                 "1", FCARGAFORM("VDRECEPCION.FRM"),
                                 "2", FCARGAFORM("VDUBICAENTRADAS.FRM"),
                                 "3", FCARGAFORM("VDCONSCNT.FRM"),
                                 "4", FCARGAFORM("VDCONSUBI.FRM"),
                                 "5", FCARGAFORM("VDREUBICADEV.FRM"),
                                 "6", FCARGAPERFIL("DESTRUIR"),
                                 "7", FCARGAFORM("VDREUBICACNT.FRM"),
                                 "8", FCARGAFORM("SIMULASCANNER.FRM"),
                                 "9", FCARGAFORM("VDVERIFICAFMD.FRM"),
                                 "10", FCARGAPERFIL("PICKING"),
                                 "11",FCARGAFORM("VDSALIR.FRM"), 
                                 "", FPOSICIONABLOQUE("-1")),"IMPOSIBLE EJECUTAR")

CURSOR=CPONCERO SELECT 0 OPCION FROM DUAL;

CURSOR=CUPDRECURSO UPDATE VDRECURSO 
                      SET NPANTALLA=NULL,
                          STATUS=VDST.FRECBUSCANDO,
                          CODOPEMODIF=:CODOPE, 
                          FECMODIF=VD.FECHASYS, 
                          HORAMODIF=VD.HORASYS
                    WHERE CODRECURSO=:CODRECURSO;
