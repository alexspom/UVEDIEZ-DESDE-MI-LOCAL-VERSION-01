KPI ALMACENAJE
FECHA      PALETS
�D-MM-Y.YY @L,@@@@
|
SOLOQUERY
SELECT=SELECT FECSTOCK,COUNT(DISTINCT CODMAT) PALETS
 FROM VDSTOCKDIA
 WHERE FECSTOCK BETWEEN :DESDE AND :HASTA
 GROUP BY FECSTOCK;  

REGPAG=40 
 

CAMPO=DESDE,AUXILIAR,VIRTUAL,OCULTO
CAMPO=HASTA,AUXILIAR,VIRTUAL,OCULTO
CAMPO=FECSTOCK,TITULO("Fecha")
CAMPO=PALETS,TITULO("Palets") 