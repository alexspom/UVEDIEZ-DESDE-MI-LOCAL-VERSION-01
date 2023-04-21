# Módulo   : VDMENUPEDMULTI.PAN
# Función: Menú de pedidos multicliente de V10
#            
#
###########################################
# Histórico de cambios:
# 
MENU PEDIDOS MULTICLIENTE
_10_______ _10_______
MENU PED. MULTICLIENTE
 0.- BUSCAR TRABAJO
 1.- CAJAS
 2.- PICKING MULTI N14
 3.- PICKING MULTI N15
 4.- PICKING MULTI MEZZANINE
 5.- PICKING MULTI DESBORDANTE
 6.- MONOPEDIDO
 7.- PALET
 8.- CONSULTAS
 9.- SIMULA SCANNER
 10.- SALIR
OPCION @L
|

POSTQUERY=FEJECUTA(FLIMPIABLOQUE("0"),"","CPONCERO","") 

CAMPO=CODRECURSO,VIRTUAL,NOENTER
CAMPO=CODOPE,VIRTUAL,NOENTER

 
                                
CAMPO=OPCION,POSTCHANGE=FEJECUTA(FENRANGO("0-10"),"DEBE INTRODUCIR\n OPCION ENTRE\n 0 Y 10",
                                 FSWITCHCADENA(":OPCION",
                                 "0", FEJECUTA("CUPDRECURSO","ERROR \nACTUALIZANDO \nRECURSO",
                                                FCOMMIT,"ERROR \nEN COMMIT",
                                                FCARGATERMINAL("CODOPE"),"ERROR \nCARGANDO \nRECURSO"),
                                 "1", FCARGAPERFIL("BULBCE",""),
                                 "2", FCARGAFORM("VDASOCIAPICKINGTERMN14"),
                                 "3", FCARGAFORM("VDASOCIAPICKINGTERMN15"),
                                 "4", FCARGAFORM("VDASOCIAPICKINGTERMMEZ"),
                                 "5", FCARGAFORM("VDASOCIAPICKINGTERMDES"),
                                 "6", FCARGAFORM("VDPICKUNIPP"),
                                 "7", FCARGAPERFIL("PALETCOMPLETO",""),
                                 "8", FEJECUTA("CACTIVACONSULTAS","",FCOMMIT,"",FCARGAPERFIL("MENUCONSULTA","")),
								 "9", FCARGAFORM("SIMULASCANNER.FRM"),
								 "10", FEJECUTA("CANULAPED","","CUPDINAC","",FCOMMIT,"",FPOSICIONABLOQUE("-1"),""),
                                 "", FPOSICIONABLOQUE("-1")),"IMPOSIBLE EJECUTAR")

CURSOR=CPONCERO SELECT 0 OPCION FROM DUAL;

CURSOR=CACTIVACONSULTAS UPDATE VDRECTAREA SET ACTIVA='S' WHERE CODPERFIL='MENUCONSULTA' AND CODRECURSO=:CODRECURSO;

CURSOR=CANULAPED UPDATE VDRECTAREA SET ACTIVA='N' WHERE (CODPERFIL,CODRECURSO)=(SELECT CODPERFIL,CODRECURSO FROM VDRECURSO WHERE CODRECURSO=:CODRECURSO);

CURSOR=CUPDRECURSO UPDATE VDRECURSO 
                      SET NPANTALLA=NULL,
                          STATUS=VDST.FRECBUSCANDO,
                          CODOPEMODIF=:CODOPE, 
                          FECMODIF=VD.FECHASYS, 
                          HORAMODIF=VD.HORASYS
                    WHERE CODRECURSO=:CODRECURSO;
                    
CURSOR=CUPDINAC UPDATE VDRECURSO 
                      SET NPANTALLA=NULL,
                          CODPERFIL=NULL,
                          STATUS=VDST.FRECINACTIVO,
                          CODOPEMODIF=:CODOPE, 
                          FECMODIF=VD.FECHASYS, 
                          HORAMODIF=VD.HORASYS
                    WHERE CODRECURSO=:CODRECURSO;