###################################################################
#M�dulo: VDPICKINVRESSTK.PAN
#Funcionalidad : Stock del bulto de picking inverso
#Autor: FGS
#Fecha: 10-03-2009
#MIRAR  COMPATIBILIDAD CON UBICACION DESTINO, EN ESTE CASO EXPEDICIONES
###################################################################
STOCK DEL BULTO DE PICKING INVERSO
    
    Matr�cula:  __________________
    
    Lote:       _40_______________
    
    Ubicaci�n:  _20___________
   
   
                En Stock     L�neas de Bulto 
 Cantidad:     @L@@@@@@@                    
 Reservado:    @L@@@@@@@       @L@@@@@@@
 Resto:        @L@@@@@@@       @L@@@@@@@    

|


SOLOQUERY
NOUPDATE

SELECT = SELECT MAX(CODLOT) CODLOT, SUM(CANTIDAD) CANTIDADSTK,   SUM(VDSTK.STKRESERVADO(STK.CODMAT,STK.ORDENSTK))  RESERVADOSTK FROM VDSTOCK STK WHERE CODMAT=:CODMAT;

CURSOR=CRESTOSSTK SELECT :CANTIDADSTK - :RESERVADOSTK RESTOSTK FROM DUAL;

CURSOR=CDATOSBPL SELECT SUM(DECODE(STATUS,VDST.FBPLASERVIR,CANTPEDIDA,0)) RESERVADOBPL,
                        SUM(DECODE(STATUS,VDST.FBPLRESTOS,CANTPEDIDA,0)) RESTOSBPL
                     FROM VDBULTOLINPINV 
                     WHERE  CODBULTO=:CODBULTO;

CURSOR=CDAMEUBI SELECT CODUBI FROM VDCONTE WHERE CODMAT=:CODMAT;                     

POSTQUERY=FEJECUTA("CRESTOSSTK","ERROR EN CRESTOSSTK", 
                   "+CDATOSBPL","ERROR EN CDATOSBPL",
                   "CDAMEUBI","")   
           

CAMPO=CODBULTO,VIRTUAL,AUXILIAR,OCULTO
CAMPO=CODMAT,VIRTUAL,AUXILIAR,NOUPDATE
CAMPO=CODLOT,NOUPDATE
CAMPO=CODUBI,AUXILIAR,NOUPDATE
CAMPO=CANTIDADSTK
CAMPO=RESERVADOSTK
CAMPO=RESERVADOBPL,AUXILIAR,NOUPDATE
CAMPO=RESTOSTK,AUXILIAR,NOUPDATE
CAMPO=RESTOSBPL,AUXILIAR,NOUPDATE

CONTEXTUAL=FEJECUTAFORM("VDCONTE","S","CODMAT=:CODMAT","","","","S")
  