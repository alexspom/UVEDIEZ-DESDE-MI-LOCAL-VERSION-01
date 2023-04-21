# Módulo   : VDCUADRE.PAN
# Función  : Trazabilidad por artículo
#
# Creación : 17-08-2008
# Autor    : MGM
###########################################
CUADRE DE ENTRADAS Y SALIDAS DE STOCK                                                   
Artículo      Descripción                     Lote               Saldo E/S       Stock actual  Dif. Pr.movim.    Ult.movim.  
_40_________________ _40____________________________ _20____________ #L##,###,###.##  #L##,###,###.##  _   ¿D-MM-Y.YYY  ¿D-MM-Y.YYY 
|

SOLOQUERY
TABLA=ACUM

SELECT=SELECT CODART, DESART, CODLOT, SALDO, NVL(CANTSTK,0) STOCK, DECODE(SALDO,NVL(CANTSTK,0),'N','S') DESCUADRE, MINFECFINMOV, MAXFECFINMOV
       FROM (SELECT MOV.CODART, ART.DESART, MOV.CODLOT, SUM(DECODE(UBIO.STOCK,'N',MOV.CANTIDAD,-MOV.CANTIDAD)) SALDO, MIN(MOV.FECFINMOV) MINFECFINMOV, MAX(MOV.FECFINMOV) MAXFECFINMOV,
                    (SELECT SUM(STK.CANTIDAD)
                     FROM VDSTOCK STK WHERE STK.CODART = MOV.CODART AND STK.CODLOT = MOV.CODLOT 
                     GROUP BY STK.CODART, STK.CODLOT) CANTSTK
             FROM VDMOVIM MOV, VDUBICA UBIO, VDUBICA UBID, VDARTIC ART
             WHERE MOV.CODUBIORI = UBIO.CODUBI AND
                   MOV.CODUBIDEST = UBID.CODUBI AND
                   (UBIO.STOCK = 'N' OR UBID.STOCK = 'N') AND
                   MOV.STATUS >= VDST.FMOVACTUALIZA AND MOV.STATUS NOT IN (VDST.FMOVANULADO, VDST.FMOVTRATADAANU) AND
                   MOV.CODART = ART.CODART 
             GROUP BY MOV.CODART, ART.DESART, MOV.CODLOT)
       WHERE 1=1;
ORDERBY=DESCUADRE DESC, CODART, CODLOT;       



CAMPO=CODART,NOPREF,TOOLTIP("Código del articulo"),TITULO("Artículo")
CAMPO=DESART,NOPREF,TOOLTIP("Descripcion del articulo"),TITULO("Descripción")
CAMPO=CODLOT,NOPREF,TOOLTIP("Lote del artículo"),TITULO("Lote")
CAMPO=SALDO,NOPREF,TOOLTIP("Saldo de entradas/salidas"),TITULO("Saldo E/S")
CAMPO=STOCK,NOPREF,TOOLTIP("Stock del artículo"),TITULO("Stock actual")
CAMPO=DESCUADRE,NOPREF,TOOLTIP("S - Artículo descuadrado; N - Articulo cuadrado"),TITULO("Dif"),WLONX=15
CAMPO=MINFECFINMOV,NOPREF,TOOLTIP("Fecha del primer movimiento del artículo"),TITULO("Pr.movim.")
CAMPO=MAXFECFINMOV,NOPREF,TOOLTIP("Fecha del último movimiento del artículo"),TITULO("Últ.movim.")

TECLA=SF8,FEJECUTA(FIMPRIME("INFORME","VDTRAZABILIDAD.rpt","CODART=:CODART;CODLOT=:CODLOT;CODCONCE='';FECDESDE='01-01-01';FECHASTA='31-12-50'",""),":V10ERROR")
TECLA=SF9,FEJECUTA(FIMPRIME("INFORME","VDTRAZABILIDAD.rpt","CODART=:CODART;CODLOT=:CODLOT;CODCONCE='PEDEXPED';FECDESDE='01-01-01';FECHASTA='31-12-50'",""),":V10ERROR")



