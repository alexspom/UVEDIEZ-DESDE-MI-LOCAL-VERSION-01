# M�dulo   : VDSTKUBI.PAN
# Funci�n  : Consulta de stock de �reas
#
# Creaci�n : 01-10-2007
# Autor    : EAA
###########################################
# Hist�rico de cambios:
STOCK POR UBICACION
Ubicaci�n    Libre         Bloqueado   Reservado  Cont.
_20_________ #L,#####.### #L,####.### #L,####.### @L@@@
                                                             |

SOLOQUERY

SELECT=SELECT UBI.CODUBI,VDART.VD2HOST(SUM(DECODE(STK.BLOQUEOS,'0000000000',CANTIDAD,0)),STK.CODART) LIBRE,
              VDART.VD2HOST(SUM(DECODE(STK.BLOQUEOS,'0000000000',0,CANTIDAD)),STK.CODART) BLOQUEADO,
              COUNT(DISTINCT STK.CODMAT) CONTENEDORES,
              ART.DECIMALES LIBRE__DECIMALES,ART.DECIMALES BLOQUEADO__DECIMALES,ART.DECIMALES RESERVADO__DECIMALES,
              VDART.VD2HOST(VDUBI.UBIRESERVADO(UBI.CODUBI,'U',:CODART,:CODLOT),STK.CODART) RESERVADO    
        FROM VDAREA ARE,VDUBICA UBI,VDCONTE CNT,VDSTOCK STK,VDARTIC ART
        WHERE ARE.CODAREA=UBI.CODAREA AND UBI.CODUBI=CNT.CODUBI AND STK.CODMAT=CNT.CODMAT AND
              STK.CODART=ART.CODART;
GROUPBY=UBI.CODUBI,STK.CODART,ART.DECIMALES;

CAMPO=CODART,VIRTUAL,OCULTO,PREFIJO=STK
CAMPO=CODALM,VIRTUAL,OCULTO,PREFIJO=ARE
CAMPO=CODAREA,VIRTUAL,OCULTO,PREFIJO=UBI
CAMPO=CODUBI,TOOLTIP("Ubicaci�n"),TITULO("Ubicaci�n")
CAMPO=LIBRE,TOOLTIP("Stock libre"),TITULO("Libre")
CAMPO=BLOQUEADO,TOOLTIP("Stock bloqueado"),TITULO("Bloqueado")
CAMPO=RESERVADO,TOOLTIP("Stock reservado de la ubicaci�n del art�culo"),TITULO("Reservado")
CAMPO=CONTENEDORES,TOOLTIP("N�mero de contenedores"),TITULO("Cont.")




