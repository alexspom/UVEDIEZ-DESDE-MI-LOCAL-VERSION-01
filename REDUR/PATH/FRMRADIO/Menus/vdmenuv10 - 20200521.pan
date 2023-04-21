# Módulo   : VDMENUV10.PAN
# Función: Menú del administrador de V10
#            
MENU DEL IMPLANTADOR DE V10
 _10_______ _10_______
 MENU DE SUPERVISOR
 0.- BUSCAR TRABAJO
 1.- RECEPCIONAR
 2.- UBICAR
 3.- PICKING
 4.- MONOPEDIDO
 5.- CAMBIA UBICACION
 6.- TRANSFERENCIA
 7.- CONSULTA MATRICULA
 8.- CONSULTA UBICACION
 9.- SALIR
 OPCION @L
|

POSTQUERY=FEJECUTA(FLIMPIABLOQUE("0"),"","CPONCERO","") 

CAMPO=CODRECURSO,VIRTUAL,NOENTER
CAMPO=CODOPE,VIRTUAL,NOENTER

 
                                
CAMPO=OPCION,POSTCHANGE=FEJECUTA(FENRANGO("0-9"),"DEBE INTRODUCIR\n OPCION ENTRE\n 0 Y 9",
                                 FSWITCHCADENA(":OPCION",
                                 "0", FEJECUTA("CUPDRECURSO","ERROR \nACTUALIZANDO \nRECURSO",
                                                FCOMMIT,"ERROR \nEN COMMIT",
                                                FCARGATERMINAL("CODOPE"),"ERROR \nCARGANDO \nRECURSO"),
                                 "1", FCARGAFORM("VDRECEPCION.FRM"),
                                 "2", FCARGAFORM("VDUBICAENTRADAS.FRM"),
                                 "3", FCARGAFORM("VDPICKUNIVD.FRM"),
                                 "4", FCARGAFORM("VDPICKUNIPP"),
                                 "5", FCARGAFORM("VDREUBICACNT.FRM"),
                                 "6", FCARGAFORM("VDMEZCLA.FRM"),
                                 "7", FCARGAFORM("VDCONSCNT.FRM"),
                                 "8", FCARGAFORM("VDCONSUBI.FRM"),
                                 "9", FPULSATECLAS("ESC"),
                                 "",  FPOSICIONABLOQUE("-1")),"IMPOSIBLE EJECUTAR")

CURSOR=CPONCERO SELECT 0 OPCION FROM DUAL;

CURSOR=CUPDRECURSO UPDATE VDRECURSO 
                      SET NPANTALLA=NULL,
                          STATUS=VDST.FRECBUSCANDO,
                          CODOPEMODIF=:CODOPE, 
                          FECMODIF=VD.FECHASYS, 
                          HORAMODIF=VD.HORASYS
                    WHERE CODRECURSO=:CODRECURSO;
