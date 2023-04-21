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
 MENU DE SUPERVISOR
 0.- BUSCAR TRABAJO
 1.- RECEPCIONAR
 2.- UBICAR
 3.- UBICAR CON CARRO
 4.- CONSULTA MATRICULA
 5.- CONSULTA UBICACION
 6.- PICKING
 7.- MONOPEDIDO
 8.- IMPRESION BULTOS MONOP.
 9.- CAMBIA UBICACION
 10.- REPOSICIONES N14
 11.- REPOSICIONES N15
 12.- TRANSFERENCIA
 13.- PEDIDOS
 14.- SALIR
 OPCION @L
|

POSTQUERY=FEJECUTA(FLIMPIABLOQUE("0"),"","CPONCERO","") 

CAMPO=CODRECURSO,VIRTUAL,NOENTER
CAMPO=CODOPE,VIRTUAL,NOENTER

 
                                
CAMPO=OPCION,POSTCHANGE=FEJECUTA(FENRANGO("00-14"),"DEBE INTRODUCIR\n OPCION ENTRE\n 0 Y 14",
                                 FSWITCHCADENA(":OPCION",
                                 "0", FEJECUTA("CUPDRECURSO","ERROR \nACTUALIZANDO \nRECURSO",
                                                FCOMMIT,"ERROR \nEN COMMIT",
                                                FCARGATERMINAL("CODOPE"),"ERROR \nCARGANDO \nRECURSO"),
                                 "1", FCARGAFORM("VDRECEPCION.FRM"),
                                 "2", FCARGAFORM("VDUBICAENTRADAS.FRM"),
								 "3", FCARGAFORM("VDUBICAENTRADASCARRO.FRM"),
                                 "4", FCARGAFORM("VDCONSCNT.FRM"),
                                 "5", FCARGAFORM("VDCONSUBI.FRM"),
                                 "6", FCARGAFORM("VDPICKUNIVD.FRM"),
                                 "7", FCARGAFORM("VDPICKUNIPP"),
								 "8", FCARGAFORM("VDIMPBUL.FRM"),
                                 "9", FCARGAFORM("VDREUBICACNT.FRM"),
                                 "10",FCARGAPERFIL("REPON14"), 
                                 "11",FCARGAPERFIL("REPON15"), 
                                 "12", FCARGAFORM("VDMEZCLA.FRM"),
                                 "13",FEJECUTA("CACTIVAPEDIDOS","",FCOMMIT,"",FCARGAPERFIL("MENUPED","")),
                                 "14",FPULSATECLAS("ESC"),
                                 "", FPOSICIONABLOQUE("-1")),"IMPOSIBLE EJECUTAR")

CURSOR=CPONCERO SELECT 0 OPCION FROM DUAL;

CURSOR=CACTIVAPEDIDOS UPDATE VDRECTAREA SET ACTIVA='S' WHERE CODPERFIL='MENUPED' AND CODRECURSO=:CODRECURSO;

CURSOR=CUPDRECURSO UPDATE VDRECURSO 
                      SET NPANTALLA=NULL,
                          STATUS=VDST.FRECBUSCANDO,
                          CODOPEMODIF=:CODOPE, 
                          FECMODIF=VD.FECHASYS, 
                          HORAMODIF=VD.HORASYS
                    WHERE CODRECURSO=:CODRECURSO;
