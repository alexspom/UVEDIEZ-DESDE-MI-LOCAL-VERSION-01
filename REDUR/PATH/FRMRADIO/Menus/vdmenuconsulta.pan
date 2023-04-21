# Módulo   : VDMENUVPED.PAN
# Función: Menú depedidos de V10
#            
#
###########################################
# Histórico de cambios:
# 
MENU DE PEDIDOS
 _10_______ _10_______
 MENU DE CONSULTAS
 
 1.- MATRICULA
 2.- UBICACION
 3.- ARTICULO
 4.- SALIR
 
OPCION @L
|

POSTQUERY=FEJECUTA(FLIMPIABLOQUE("0"),"","CPONCERO","") 

CAMPO=CODRECURSO,VIRTUAL,NOENTER
CAMPO=CODOPE,VIRTUAL,NOENTER

 
                                
CAMPO=OPCION,POSTCHANGE=FEJECUTA(FENRANGO("1-4"),"DEBE INTRODUCIR\n OPCION ENTRE\n 1 Y 4",
                                 FSWITCHCADENA(":OPCION",
                                 "1", FCARGAFORM("VDCONSCNT"),
                                 "2", FCARGAFORM("VDCONSUBI"),
								 "3", FCARGAFORM("VDCONSART"),
								 "4", FEJECUTA("CANULAPED","","CUPDINAC","",FCOMMIT,"",FPOSICIONABLOQUE("-1"),""),
                                 "", FPOSICIONABLOQUE("-1")),"IMPOSIBLE EJECUTAR")

CURSOR=CPONCERO SELECT 0 OPCION FROM DUAL;

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