#*****************************************************************
#Módulo: VDREUBICAR.PAN
#Funcionalidad : Reubica un palet a una ubicación compatible
#Autor: ICC      
#Fecha: 08-05-2008
#*****************************************************************
#* Histórico de cambios
#* ====================
#*****************************************************************
REUBICAR STOCK

Artículo                      Lote      Cantidad           Bloqueos   Matrícula   Tipo    Ubicación  Area    Cant Reubi      R
_40________ _100_____________ _40______ ############ _10_ _10_______ _18_________ _10____ _20_______ _10____ ########## _10_ _
                                                                                                                               |

SOLOQUERY
SELECT=SELECT CODMAT, CODART, CODLOT, BLOQUEOS, UNIEMB, SUM(CANTIDAD) CANTIDAD
         FROM VDSTOCK;
GROUPBY= CODMAT, CODART, CODLOT, BLOQUEOS,UNIEMB;


PREUPDATE=FEJECUTA(FIF("CUPDREUBI", FEJECUTA(FIF("CCANTREUBI", FEJECUTA(FREUBICONTE(":CODMAT",":TAREA","CODMOV","","",""),":V10ERROR"),
                                                              FEJECUTA(FREUBISTK(":CODMAT",":TAREA",":CODART",":CODLOT",":UNIEMB","",":CANTREUBI","CODMOV","","",""),":V10ERROR")),"",
                                            %FFAILURE,"GENERADO MOVIMIENTO :CODMOV",
                                            FCOMMIT,"",
                                            FPULSATECLAS("CF2","F2"),"")),"")

POSTQUERY=FEJECUTA("+CSELCONTE","")
                  
CAMPO=CODART,POSTCHANGE=FDESIGNACION("CSELVDARTICDESART","ERROR No existe artículo :CODART"),TOOLTIP("Código del artículo"),TITULO("Artículo")
CAMPO=DESART,NOENTER,AUXILIAR,TOOLTIP("Designacion del artículo")
CAMPO=CODLOT,TOOLTIP("Lote"),TITULO("Lote")
CAMPO=CANTIDAD,TOOLTIP("Cantidad de la línea de stock"),CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),TITULO("Cantidad")
CAMPO=UNIDADES,NOENTER
CAMPO=BLOQUEOS,TOOLTIP("Situación de bloqueos del stock. todo 0 indica disponible cada caracter tiene significado individual"),TITULO("Bloqueos")
CAMPO=CODMAT,TOOLTIP("Matricula del contenedor en el que se halla el stock"),TITULO("Matrícula")
CAMPO=TIPOCONTE,NOENTER,TOOLTIP("Tipo de contenedor"),TITULO("Tipo")
CAMPO=CODUBI,NOENTER,TOOLTIP("Código de la ubicación donde se encuentra el contenedor"),TITULO("Ubicación")
CAMPO=CODAREA,NOENTER,TOOLTIP("Código del área donde se encuentra el contenedor"),TITULO("Area")
CAMPO=CANTREUBI,UPDATE,TOOLTIP("Cantidad a reubicar"),AUXILIAR,
                POSTCHANGE=FEJECUTA("CVALCANT", "ERROR, la cantidad a reubicar, no puede ser mayor que la existente"),
                TITULO("Cant. Reubi")
CAMPO=UNIDADES2,NOENTER
CAMPO=REUBI,UPDATE,AUXILIAR,UPPER,POSTCHANGE=FVERIFICA("SN ","Valores: S=Enviar a ubicación libre, N o blanco=No reubicar"),TITULO("R")
CAMPO=UNIEMB,OCULTO,"###########"
CAMPO=CODMOV,OCULTO,"@L@@@@@@@"
CAMPO=TAREA,OCULTO,AUXILIAR,"_32_"
CAMPO=DUMMY,OCULTO,AUXILIAR,"#"


CURSOR=CSELVDARTICDESART SELECT DESART, UNIDADES, UNIDADES UNIDADES2, DECIMALES CANTIDAD__DECIMALES
                           FROM VDARTIC WHERE CODART=:CODART;

CURSOR=CSELCONTE SELECT CNT.TIPOCONTE, CNT.CODUBI, UBI.CODAREA, VD.GETPROP('TREUBICAAUTO') TAREA
                   FROM VDCONTE CNT, VDUBICA UBI
                  WHERE CNT.CODUBI = UBI.CODUBI
                    AND CNT.CODMAT = :CODMAT;
                    
CURSOR=CVALCANT SELECT 1 DUMMY
                  FROM DUAL
                 WHERE :CANTREUBI <= :CANTIDAD;                    
                    
CURSOR=CUPDREUBI SELECT DECODE(:CANTREUBI,0,:CANTIDAD,:CANTREUBI) CANTREUBI FROM DUAL WHERE :REUBI = 'S';

CURSOR=CCANTREUBI SELECT 1 DUMMY
                    FROM DUAL
                   WHERE (:CANTREUBI= 0
                      OR :CANTREUBI = :CANTIDAD)
                     AND :TIPOCONTE !='VIRTUAL';
                      

