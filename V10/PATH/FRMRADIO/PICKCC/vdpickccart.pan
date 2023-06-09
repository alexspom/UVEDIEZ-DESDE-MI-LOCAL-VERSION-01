# M�dulo   : VDPICKCCART.PAN
# Funci�n  : Formulario de recogida de bultos de caja completa.
#            Pantalla de lectura del articulo
#
# Creaci�n : 13-05-2008
# Autor    : JMM
###########################################
# Hist�rico de cambios:
# M001 - DFL - A�ADIR FMD
# 
CAJAS COMPLETAS
_10_______ _10_______
CAJAS COMPLETAS
U.ORIGEN :_12_________
CONTENEDOR: _18______________
  
ARTICULO _40_________________
  _20_________________
  _20_________________
LOTE:  _40_________________  
LECTURA DE ARTICULO 
_255______________________________________________________________________________________________________________________
_255______________________________________________________________________________________________________________________
  
CAJAS A COGER #L####
DE (U/E): #15L######
|

# agrupar� movtos de una misma matr�cula , art�culo y lote, uneimb
# 
PREQUERY=FEJECUTA("CSELLIMPIA","ERROR LIMPIANDO PANTALLA",
                  "CSELLONGERROR","ERROR\n OBTENIENDO PROPIEDAD\n LONGERROR",
                  FIF("-CMOVTOPDTES",FPOSICIONABLOQUE("VDPICKCCNOMOV.PAN"),FSUCCESS),"\n\nNO HAY \nMOVIMIENTOS\nPENDIENTES",
                  "CCONGELAMOVS","ERROR\n CONGELANDO MOVTOS DE\n UBICACION :CODUBI",
                  FCOMMIT,"",
                  FIF("-CMOVCONGELADOS", FPOSICIONABLOQUE("VDPICKCCERRCONGELA.PAN"),FSUCCESS),"\n\nNO HAY \nMOVIMIENTOS\nCONGELADOS",
                  "+CSELDECIMALES","",
				  "+CTIENEFMD","")

POSTQUERY=FEJECUTA(FIF("CSELNOTNULL",FCARGAFORM(""),FSUCCESS),"ERROR\n AL VOLVER AL MENU",
                   "CSELCODARTEAN","\nERROR,\nEL EAN LEIDO NO EXISTE",
                   "CCHECKLOTEYART","\nERROR,\nEL ARTICULO Y LOTE\nNO COINCIDE.",
				   "CSELIMPRE","\nASEGURESE DE QUE TIENE\n IMPRESORA ASOCIADA",
                   "CSELMOVSAJECUTAR","ERROR,\n AL RECUPERAR LOS\n MOVIMIENTOS A EJECUTAR.",
                   FWHILE(FERRORCURSOR("CSELMOVSAJECUTAR"),
                                FEJECUTA(FIF(FIMPREBULTOSDEMOV(":CODMOV",":CODIMPRE"),
                                             FSUCCESS,
                                             FEJECUTA("CDIVIDEERROR","ERROR\nDIVIDIENDO ERROR IMPRESION",FFAILURE,":MSGERROR")),"ERROR AL IMPRIMIR ETIQUETA",								
    								     FIF(FEJECUTAMOVSYNC("ACTSTKORIGEN","ACTSTKDESTINO",":CODMOV",":CODRECURSO"),
                                             FSUCCESS,
                                             FEJECUTA("CDIVIDEERROR","ERROR\nDIVIDIENDO ERROR MOV",FFAILURE,":MSGERROR")),"",									     
										 FIF("CFMDSI","CUPBUCPTEFMD",FSUCCESS),"",
                                         +FFETCHCURSOR("CSELMOVSAJECUTAR"),"")
                         ),"",
                   FCOMMIT,"ERROR\n HACIENDO COMMIT",
                   FPOSICIONABLOQUE("VDPICKCCCONF.PAN"),"ERROR\n CARGANDO BLOQUE\n VDPICKCCCONF.PAN")

#                   "CVERIFDAT","ERROR\n DATOS LEIDOS\n INCORRECTOS",

# DEFINICION DE CAMPOS
CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=CODUBI,NOENTER
CAMPO=CODUBIDEST,OCULTO,"_12____"
CAMPO=CODMAT,NOENTER
CAMPO=CODART,NOENTER
CAMPO=DESART1,NOENTER
CAMPO=DESART2,NOENTER
CAMPO=CODLOT,NOENTER
CAMPO=CADUCI,OCULTO,"_8_"
#CAMPO=CODBARRAS,SCAN,AUTOENTER,POSTCHANGE=FEJECUTA(FLEEARTICULO("CODBARRAS","CODARTLEIDO",":CODART","CODLOTLEIDO"),"ERROR\n OBTENIENDO ARTICULO Y LOTE") 
#CAMPO=CODBARRAS1,SCAN,POSTCHANGE=FDESIGNACION(FIF("CSELNOTNULL",FCARGAFORM(""),FSUCCESS),"",
#                                              +FLEEARTICULO("CODBARRAS1", "CODARTLEIDO",""),"ERROR :V10ERROR",
#                                              +FANALIZAEANRAD("CODBARRAS1", "37","UNIEMB","17", "CADUCI","10","CODLOTLEIDO"),"\nERROR,\nEN LECTURA DEL\nC�digo DE BARRAS")
CAMPO=CODBARRAS1,SCAN,POSTCHANGE=FDESIGNACION(FIF("CSELNOTNULL",FCARGAFORM(""),FSUCCESS),"",
                                              +FANALIZAEANRAD("CODBARRAS1","02","CODEANLEIDO","37","UNIEMB","17","CADUCI","10","CODLOTLEIDO"),"\nERROR,\nEN LECTURA DEL\nC�digo DE BARRAS")
                                               
CAMPO=CODBARRAS2,SCAN,POSTCHANGE=FDESIGNACION(+FANALIZAEANRAD("CODBARRAS2","02","CODEANLEIDO","37","UNIEMB","17","CADUCI","10","CODLOTLEIDO"),"\nERROR,\nEN LECTURA DEL\nC�digo DE BARRAS") 

CAMPO=CAJAS,NOENTER
CAMPO=UNIEMB,NOENTER,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")

CAMPO=UNIEMBSCAN,OCULTO,"#L#############",CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=CODARTLEIDO,OCULTO,"_40_"
#,POSTCHANGE=FEJECUTA(FFUERZASCAN("ART"),"\nERROR\n DEBE SCANNEAR\n EL ARTICULO")
CAMPO=CODLOTLEIDO,OCULTO,"_40_"
CAMPO=MSGERROR,OCULTO,"_2048_"
CAMPO=LONGERROR,OCULTO,"@@@"
CAMPO=CODMOV,OCULTO,"@L@@@@@@@"
CAMPO=CODEANLEIDO,OCULTO,"_14_"
CAMPO=SWTFMD,OCULTO,"_1_"
CAMPO=CODIMPRE,OCULTO,"_15_"

# DEFINICION DE CURSORES
CURSOR=CSELARTNOTNULL SELECT :CODART FROM DUAL WHERE :CODART IS NOT NULL;

CURSOR=CSELLIMPIA SELECT NULL CODBARRAS1, NULL CODBARRAS2,NULL CODARTLEIDO,NULL CODLOTLEIDO FROM DUAL;

CURSOR=CSELLONGERROR SELECT VD.GETPROP('LONGITUDERROR') LONGERROR FROM DUAL;


CURSOR=CSELCODARTEAN SELECT CODART CODARTLEIDO
                       FROM VDARTIC
                      WHERE CODEAN=:CODEANLEIDO;

CURSOR=CCHECKLOTEYART SELECT :CODARTLEIDO 
                        FROM DUAL 
                       WHERE :CODARTLEIDO = :CODART AND
                             NVL(:CODLOTLEIDO,'0') = DECODE(:CODLOT,NULL,NVL(:CODLOTLEIDO,'0'),:CODLOT); 

CURSOR=CMOVTOPDTES SELECT MOV.CODUBIORI CODUBI,MOV.CODMATORI CODMAT,MOV.CODUBIDEST CODUBIDEST,MOV.CODART,MOV.UNIEMB,
                          VD.DIVIDEXBUSQUEDA(1,ART.DESART,' ',20,0) DESART1,VD.DIVIDEXBUSQUEDA(2,ART.DESART,' ',20,0) DESART2                       
                       FROM VDMOVIM MOV,VDARTIC ART, VDUBICA UBI
                       WHERE MOV.STATUS IN (VDST.FMOVASIGNADO,VDST.FMOVPRESENTADO) 
                         AND MOV.CODRECURSO = :CODRECURSO 
                         AND MOV.TAREA = 'PEDEMBA'
                         AND ART.CODART = MOV.CODART
                         AND MOV.CODUBIORI = UBI.CODUBI
                       ORDER BY DECODE(MOV.STATUS,VDST.FMOVPRESENTADO,0,1),UBI.ORDENMOVIM;
											            
 
CURSOR=CSELNOTNULL SELECT :CODBARRAS1 FROM DUAL WHERE :CODBARRAS1 IS NULL AND :CODBARRAS2 IS NULL;
                        
CURSOR=CCONGELAMOVS DECLARE
											CURSOR C1 IS SELECT MOV.* 
											         FROM VDMOVIM MOV
											         WHERE 											            
											            MOV.TAREA = 'PEDEMBA' 
											            AND MOV.STATUS = VDST.FMOVASIGNADO
											            AND MOV.CODRECURSO = :CODRECURSO 											            
											            AND MOV.CODUBIORI  = :CODUBI 
											            AND MOV.CODUBIDEST = :CODUBIDEST 
											            AND MOV.CODMATORI  = :CODMAT 
											            AND MOV.CODART     = :CODART 
											            AND MOV.UNIEMB     = :UNIEMB 
                            ORDER BY DECODE(NVL(NUMEROSERIE,'-'),'-',1,0),
                                  DECODE(NVL(BULTO,'-'),'-',1,0),
                                  DECODE(PRECIOUNI,0,1,0),
                                  DECODE(NVL(TIPOEMBA,'-'),'-',1,0),
                                  DECODE(NVL(CODRECEP,'-'),'-',1,0),
                                  DECODE(NVL(MARCASTK,'-'),'-',1,0),
                                  DECODE(NVL(BLOQUEOSORI,'-'),'-',1,0),
                                  DECODE(NVL(CODLOT,'-'),'-',1,0);
                     CONGELADOS NUMBER;                                   
                   BEGIN
									    UPDATE VDMOVIM SET STATUS=VDST.FMOVASIGNADO,CODOPEMODIF=:CODOPE,FECMODIF=VD.FECHASYS,HORAMODIF=VD.HORASYS 
									       WHERE STATUS=VDST.FMOVPRESENTADO AND CODRECURSO=:CODRECURSO;									          
									    CONGELADOS:=0;
									    FOR I IN C1 LOOP									    
									      IF (VDMOV.CONGELA(I.CODMOV)=0) THEN
									        CONGELADOS:=CONGELADOS+1;
									        VDLOG.PONMENSAJE('VDPICKCCART','CCONGELAMOVS: CONGELADO MOVTO ' || I.CODMOV);
									        UPDATE VDMOVIM SET STATUS=VDST.FMOVPRESENTADO,CODOPEMODIF=:CODOPE,FECMODIF=VD.FECHASYS,HORAMODIF=VD.HORASYS WHERE CODMOV=I.CODMOV;
									      ELSE
                                            VDLOG.PONERROR('VDPICKCCART','CCONGELAMOVS: NO SE PUEDE CONGELAR MOVTO ' || I.CODMOV);
									      END IF;
									    END LOOP;                      
                      
                      IF (CONGELADOS=0) THEN									    
 							          UPDATE VDMOVIM MOV 
                                         SET STATUS=VDST.FMOVPDTESTOCK,CODOPEMODIF=:CODOPE,FECMODIF=VD.FECHASYS,HORAMODIF=VD.HORASYS 
 							            WHERE MOV.TAREA = 'PEDEMBA' 
											      AND MOV.STATUS = VDST.FMOVASIGNADO
											      AND MOV.CODRECURSO = :CODRECURSO 											            
											      AND MOV.CODUBIORI  = :CODUBI 
											      AND MOV.CODUBIDEST = :CODUBIDEST 
											      AND MOV.CODMATORI  = :CODMAT 
											      AND MOV.CODART     = :CODART 
											      AND MOV.UNIEMB     = :UNIEMB;
									    END IF; 
									    
                   END;@       
                   
CURSOR=CSELMOVSAJECUTAR SELECT MOV.CODMOV
                          FROM VDMOVIM MOV
                         WHERE MOV.STATUS = VDST.FMOVPRESENTADO 
                           AND MOV.TAREA = 'PEDEMBA'
                           AND MOV.CODUBIORI = :CODUBI
                           AND MOV.CODRECURSO = :CODRECURSO
                           AND MOV.CODUBIDEST = :CODUBIDEST 
						   AND MOV.CODMATORI  = :CODMAT 											                           
                           AND MOV.CODART = :CODART
                           AND MOV.UNIEMB = :UNIEMB;                                   
                         
CURSOR=CMOVCONGELADOS SELECT SUM(CANTIDAD/UNIEMB) CAJAS,CODLOT,UNIEMB FROM VDMOVIM MOV
                              WHERE MOV.TAREA = 'PEDEMBA' 
											          AND MOV.STATUS = VDST.FMOVPRESENTADO
											          AND MOV.CODRECURSO = :CODRECURSO 											            
											          AND MOV.CODUBIORI  = :CODUBI 
											          AND MOV.CODUBIDEST = :CODUBIDEST 
											          AND MOV.CODMATORI  = :CODMAT 
											          AND MOV.CODART     = :CODART 
											          AND MOV.UNIEMB     = :UNIEMB
                                                      AND MOV.CODLOT IS NOT NULL
											GROUP BY CODLOT,UNIEMB; 
                                

CURSOR=CSELDECIMALES SELECT ART.DECIMALES UNIEMB__DECIMALES FROM VDARTIC ART WHERE CODART = :CODART;

CURSOR=CSELNULL SELECT :CODBARRAS
                     FROM DUAL 
                    WHERE :CODBARRAS IS NULL;              

CURSOR=CVERIFDAT SELECT :CODBARRAS1
                   FROM DUAL
                  WHERE :CODARTLEIDO = :CODART  
                    AND :CODLOTLEIDO = :CODLOT
                    AND DECODE(:UNIEMBSCAN,0,:UNIEMBSCAN,:UNIEMB) = :UNIEMBSCAN;

CURSOR=CDIVIDEERROR BEGIN :MSGERROR:=VD.DIVERRORRADIO(:V10ERROR,:LONGERROR);
                    END;@
					
CURSOR=CSELIMPRE SELECT CODIMPRE 
                   FROM VDRECURSO 
                  WHERE CODRECURSO=:CODRECURSO AND CODIMPRE IS NOT NULL;					
#M001 INICIO
CURSOR=CTIENEFMD SELECT CASE
						 WHEN VDFMD.TIENEFMD(:CODART,'','', :CODLOT,:CODMOV) = 'S' THEN 'FMD: S'
						 ELSE ''
					     END SWTFMD
    			   FROM DUAL;
				   
CURSOR=CFMDSI SELECT :SWTFMD FROM DUAL WHERE :SWTFMD='FMD: S';

CURSOR=CUPBUCPTEFMD UPDATE VDBULTOCAB 
                   SET STATUS=VDST.FBUCPTEFMD,
				       CODOPEMODIF=:CODOPE,
                       FECMODIF=VD.FECHASYS,
					   HORAMODIF=VD.HORASYS
                    WHERE CODBULTO=:CODBULTO;
#M001 FIN	
					