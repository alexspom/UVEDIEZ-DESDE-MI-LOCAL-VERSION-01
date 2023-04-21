# M�dulo   : VDSTKALM.PAN
# Funci�n  : Consulta de stock de almacenes
#
# Creaci�n : 01-10-2007
# Autor    : EAA
###########################################
# Hist�rico de cambios:
STOCK POR ALMACEN
Almacen               Libre    Bloqueado Reservado  Cont.
_4____ _40___________ #L,##### #L,####   #L,####    @L@@@
                                                             |

SOLOQUERY

SELECT=SELECT ALM.CODALM,ALM.DESALM,VDART.VD2HOST(SUM(DECODE(STK.BLOQUEOS,'0000000000',CANTIDAD,0)),STK.CODART) LIBRE,
              VDART.VD2HOST(SUM(DECODE(STK.BLOQUEOS,'0000000000',0,CANTIDAD)),STK.CODART) BLOQUEADO,
              COUNT(DISTINCT STK.CODMAT) CONTENEDORES,
              ART.DECIMALES LIBRE__DECIMALES,ART.DECIMALES BLOQUEADO__DECIMALES,ART.DECIMALES RESERVADO__DECIMALES,
              VDART.VD2HOST(VDUBI.ALMARESERVADO(ALM.CODALM,'U',:CODART,:CODLOT),STK.CODART) RESERVADO    
        FROM VDALMA ALM,VDAREA ARE,VDUBICA UBI,VDCONTE CNT,VDSTOCK STK,VDARTIC ART
        WHERE ALM.CODALM=ARE.CODALM AND ARE.CODAREA=UBI.CODAREA AND UBI.CODUBI=CNT.CODUBI AND STK.CODMAT=CNT.CODMAT AND
              STK.CODART=ART.CODART AND STK.CODLOT=NVL(:CODLOT,STK.CODLOT);
GROUPBY=ALM.CODALM,ALM.DESALM,STK.CODART,ART.DECIMALES;


CAMPO=CODART,VIRTUAL,OCULTO,PREFIJO=STK
CAMPO=CODALM,TOOLTIP("C�digo del almac�n"),TITULO("Cod.Alm")
CAMPO=DESALM,TOOLTIP("Designaci�n del almac�n"),TITULO("Almac�n")
CAMPO=LIBRE,TOOLTIP("Stock libre"),TITULO("Libre")
CAMPO=BLOQUEADO,TOOLTIP("Stock bloqueado"),TITULO("Bloqueado")
CAMPO=RESERVADO,TOOLTIP("Cantidad Reservada del Art�culo en el Almac�n"),TITULO("Reservado")
CAMPO=CONTENEDORES,TOOLTIP("N�mero de contenedores"),TITULO("Cont."), WLONX=18

TECLA=SF9,FEJECUTAFORM("VDSTKCALIFLOT.FRM","N","LOT.CODART=:CODART","","","DESGLOSE DE STOCK POR CALIFICACION DE ARTICULO :CODART","S")                        


