#Módulo: VDDEMARTIC.PAN
#Función:
#         
#
#Autor: RFD
#Fecha creación: 13-10-2009
#
#Histórico de cambios
##########################################################
SELECCION DE ARTICULOS 
 
 Art:_40_________ _100_______________________________________    
 Lote:_40___________________

 Nº contenedores: @@@@@@@@
 Undidades Disp. : ########## unidades
|

TABLA=VDARTIC

NOUPDATE
NODELETE
NOINSERT

POSTQUERY=FEJECUTA("CSELDATOS","")
CAMPO=CODART,TOOLTIP("Artículo a trasladar"),
             POSTCHANGE=FDESIGNACION("CSELDESART","Error recuperando descripción del artículo",
                                     "+CSELDIV","ERROR, ARTICULO NO PERTENECE A DIVISION :CODDIV"	,
                                     "+CSELNUMCNT","Error contando contenedores" )
CAMPO=DESART,NOENTER
CAMPO=CODLOT,AUXILIAR

CAMPO=NUMCONTES,AUXILIAR,NOENTER
CAMPO=CANTTOTAL,AUXILIAR,NOENTER
CAMPO=CODDIV,OCULTO,"_20_"
CAMPO=CODDEMANDA,AUXILIAR,OCULTO,VIRTUAL
CAMPO=TIPODEMANDA,AUXILIAR,OCULTO,VIRTUAL

CURSOR=CSELDESART SELECT DESART FROM VDARTIC WHERE  CODART=:CODART;

CURSOR=CSELNUMCNT SELECT NVL(COUNT(DISTINCT(CODMAT)),0) NUMCONTES,NVL(SUM(CANTIDAD),0) CANTTOTAL FROM VDSTOCK WHERE CODART=:CODART
                AND CODMAT IN (SELECT CNT.CODMAT FROM VDCONTE CNT,VDTIPOCONTE TIPO,VDUBICA UBI  
                                    WHERE CNT.TIPOCONTE=TIPO.TIPOCONTE
                                    AND TIPO.MOVIBLE='S' AND TIPO.TIPOCONTE!='TMP'
                                    AND NOT EXISTS (SELECT 1 FROM VDMOVIM MOV WHERE MOV.CODMATORI=CNT.CODMAT
                                    AND MOV.STATUS < 4000
                                    AND CNT.CODUBI=UBI.CODUBI
                                    AND UBI.CODAREA IN ('HR'))
                                    AND BLOQUEOS='0000000000')
                                    GROUP BY CODART;

CURSOR=CSELCANT SELECT SUM(CANTIDAD) CANTTOTAL 
                     FROM VDSTOCK WHERE CODART=:CODART
                     AND 
                     GROUP BY CODART;
CURSOR=CSELDIV SELECT CODDIV FROM VDARTIC WHERE CODDIV=:CODDIV AND CODART=:CODART;

CURSOR=CSELDATOS SELECT :CODDEMANDA,:TIPODEMANDA FROM DUAL;

AYUDA=TABLA DE TRASLADOS
ONLINE=  {F1} Ayuda  {F2} Consulta  {F4} Confirmar Cambios  {F5} Borrar Pantalla  {F6} Cambio de pantalla;

