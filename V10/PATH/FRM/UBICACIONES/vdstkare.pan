# M�dulo   : VDSTKARE.PAN
# Funci�n  : Consulta de stock de �reas
#
# Creaci�n : 01-10-2007
# Autor    : EAA
###########################################
# Hist�rico de cambios:
STOCK POR AREA
Area                         Libre    Bloq.   Reserv. Cont. 
_20_____ _40________________ #L,##### #L,#### #L,#### @L@@@ 
                                                           |

SOLOQUERY

SELECT=SELECT ARE.CODAREA,ARE.DESAREA,VDART.VD2HOST(SUM(DECODE(STK.BLOQUEOS,'0000000000',CANTIDAD,0)),STK.CODART) LIBRE,
              VDART.VD2HOST(SUM(DECODE(STK.BLOQUEOS,'0000000000',0,CANTIDAD)),STK.CODART) BLOQUEADO,
              COUNT(DISTINCT STK.CODMAT) CONTENEDORES,
              ART.DECIMALES LIBRE__DECIMALES,ART.DECIMALES BLOQUEADO__DECIMALES,ART.DECIMALES RESERVADO__DECIMALES,
              VDART.VD2HOST(VDUBI.AREARESERVADO(ARE.CODAREA,'U',:CODART,:CODLOT),STK.CODART) RESERVADO    
        FROM VDAREA ARE,VDUBICA UBI,VDCONTE CNT,VDSTOCK STK,VDARTIC ART
        WHERE ARE.CODAREA=UBI.CODAREA AND UBI.CODUBI=CNT.CODUBI AND STK.CODMAT=CNT.CODMAT AND
              STK.CODART=ART.CODART AND (STK.CODART=ART.CODART OR UBI.CODART=ART.CODART);
GROUPBY=ARE.CODAREA,ARE.DESAREA,STK.CODART,ART.DECIMALES;
ORDERBY=DECODE(ARE.CODAREA,'PU',1,'PUGETAFE',1,'RP',2,'CACHEUNID',3,'HR',4,'HRGETAFE',4,'MUESTRAS',5,6);

WLONX=500

CAMPO=CODART,VIRTUAL,OCULTO,PREFIJO=ART
CAMPO=CODALM,VIRTUAL,OCULTO,PREFIJO=ARE
CAMPO=CODAREA,TOOLTIP("C�digo del �rea"),TITULO("Cod.Area")
CAMPO=DESAREA,TOOLTIP("Designaci�n del �rea"),TITULO("Area")
CAMPO=LIBRE,TOOLTIP("Stock libre"),TITULO("Libre")
CAMPO=BLOQUEADO,TOOLTIP("Stock bloqueado"),TITULO("Bloqueado"), WLONX=30
CAMPO=RESERVADO,TOOLTIP("Reservado del Art�culo en el Area"),TITULO("Reservado"), WLONX=30
CAMPO=CONTENEDORES,TOOLTIP("N�mero de contenedores"),TITULO("Cont."),WLONX=30



