###################################################################
#M�dulo: VDLOTESCAMBIOCALIF.PAN
#Funcionalidad :  Cambios de calificaciones de Lotes desde pantalla
#Autor: FGS      
#Fecha: 01-07-2008
###################################################################
# Hist�rico de cambios:
CAMBIOS DE CALIFICACION DE LOTES DESDE PANTALLAS

 Art�culo:_40__________ _60_____________________________________
 Lote:    _40__________
  
 1  _40______________________________________ _ => __ _40_________________________________________
 2  _40______________________________________ _ => __ _40_________________________________________                                                                                
 3  _40______________________________________ _ => __ _40_________________________________________
 4  _40______________________________________ _ => __ _40_________________________________________
 5  _40______________________________________ _ => __ _40_________________________________________
 6  _40______________________________________ _ => __ _40_________________________________________
 7  _40______________________________________ _ => __ _40_________________________________________
 8  _40______________________________________ _ => __ _40_________________________________________
 9  _40______________________________________ _ => __ _40_________________________________________
 10 _40______________________________________ _ => __ _40_________________________________________
 
 
|

TABLA=VDLOTES


POSTQUERY=FEJECUTA("CDESGLOSABLOQ","ERROR DESGLOSANDO BLOQLOTE",
                   "CDESINDICADOR1","",
                   "CDESINDICADOR2","",
                   "CDESINDICADOR3","",
                   "CDESINDICADOR4","",
                   "CDESINDICADOR5","",
                   "CDESINDICADOR6","",
                   "CDESINDICADOR7","",
                   "CDESINDICADOR8","",
                   "CDESINDICADOR9","",
                   "CDESINDICADOR10","",
                   "CBLOQLOTEENTRABLES","ERROR EN CBLOQLOTEENTRABLES")

CAMPO=CODART,NOENTER,POSTCHANGE=FDESIGNACION("CSELDESART","ERROR OBTENIENDO DESCRIPCION DEL ARTICULO")
CAMPO=DESART,AUXILIAR,NOENTER
CAMPO=CODLOT,NOENTER
CAMPO=BLOQLOTE,OCULTO,"__________"
CAMPO=NUEVOBLOQLOTE,AUXILIAR,OCULTO,"__________"



# POSTCHANGE, CAMBIOS DE VALORES CORRECTOS POR PRIVILEGIOS ??
# AVISO DE SI HAY MERCANCIA RESERVADA, QUE PUEDE DEJAR MOVTOS HU�RFANOS

CAMPO=DESINDICADOR1,AUXILIAR,NOENTER
CAMPO=VALOR1,AUXILIAR,NOENTER
CAMPO=NUEVOVALOR1,AUXILIAR,POSTCHANGE=FDESIGNACION("CSELDESVALOR1","NO EXISTE VALOR  :NUEVOVALOR1 EN POSICION 1","CVERIFVALORES1","CAMBIO DE VALORES NO PERMITIDOS"),
                           CONTEXTUAL=FEJECUTAFORM("VDCALIFVALOR","N","","INDICADOR=1","NUEVOVALOR1=:VALORCALIF","SELECCION DE VALORES DE INDICADOR 1","S")                           
CAMPO=DESVALOR1,AUXILIAR,NOENTER


CAMPO=DESINDICADOR2,AUXILIAR,NOENTER
CAMPO=VALOR2,AUXILIAR,NOENTER
CAMPO=NUEVOVALOR2,AUXILIAR,POSTCHANGE=FDESIGNACION("CSELDESVALOR2","NO EXISTE VALOR  :NUEVOVALOR2 DE POSICION 2","CVERIFVALORES2","CAMBIO DE VALORES NO PERMITIDOS"),
                           CONTEXTUAL=FEJECUTAFORM("VDCALIFVALOR","N","","INDICADOR=2","NUEVOVALOR2=:VALORCALIF","SELECCION DE VALORES DE INDICADOR 2","S")                           
CAMPO=DESVALOR2,AUXILIAR,NOENTER

CAMPO=DESINDICADOR3,AUXILIAR,NOENTER
CAMPO=VALOR3,AUXILIAR,NOENTER
CAMPO=NUEVOVALOR3,AUXILIAR,POSTCHANGE=FDESIGNACION("CSELDESVALOR3","NO EXISTE VALOR  :NUEVOVALOR3 DE POSICION 3","CVERIFVALORES3","CAMBIO DE VALORES NO PERMITIDOS"),
                           CONTEXTUAL=FEJECUTAFORM("VDCALIFVALOR","N","","INDICADOR=3","NUEVOVALOR3=:VALORCALIF","SELECCION DE VALORES DE INDICADOR 3","S")                           
CAMPO=DESVALOR3,AUXILIAR,NOENTER

CAMPO=DESINDICADOR4,AUXILIAR,NOENTER
CAMPO=VALOR4,AUXILIAR,NOENTER
CAMPO=NUEVOVALOR4,AUXILIAR,POSTCHANGE=FDESIGNACION("CSELDESVALOR4","NO EXISTE VALOR  :NUEVOVALOR4 DE POSICION 4","CVERIFVALORES4","CAMBIO DE VALORES NO PERMITIDOS"),
                           CONTEXTUAL=FEJECUTAFORM("VDCALIFVALOR","N","","INDICADOR=4","NUEVOVALOR4=:VALORCALIF","SELECCION DE VALORES DE INDICADOR 4","S")                           
CAMPO=DESVALOR4,AUXILIAR,NOENTER

CAMPO=DESINDICADOR5,AUXILIAR,NOENTER
CAMPO=VALOR5,AUXILIAR,NOENTER
CAMPO=NUEVOVALOR5,AUXILIAR,POSTCHANGE=FDESIGNACION("CSELDESVALOR5","NO EXISTE VALOR  :NUEVOVALOR5 DE POSICION 5","CVERIFVALORES5","CAMBIO DE VALORES NO PERMITIDOS"),
                           CONTEXTUAL=FEJECUTAFORM("VDCALIFVALOR","N","","INDICADOR=5","NUEVOVALOR5=:VALORCALIF","SELECCION DE VALORES DE INDICADOR 5","S")                           
CAMPO=DESVALOR5,AUXILIAR,NOENTER

CAMPO=DESINDICADOR6,AUXILIAR,NOENTER
CAMPO=VALOR6,AUXILIAR,NOENTER
CAMPO=NUEVOVALOR6,AUXILIAR,POSTCHANGE=FDESIGNACION("CSELDESVALOR6","NO EXISTE VALOR  :NUEVOVALOR6 DE POSICION 6","CVERIFVALORES6","CAMBIO DE VALORES NO PERMITIDOS"),
                           CONTEXTUAL=FEJECUTAFORM("VDCALIFVALOR","N","","INDICADOR=6","NUEVOVALOR6=:VALORCALIF","SELECCION DE VALORES DE INDICADOR 6","S")                           
CAMPO=DESVALOR6,AUXILIAR,NOENTER

CAMPO=DESINDICADOR7,AUXILIAR,NOENTER
CAMPO=VALOR7,AUXILIAR,NOENTER
CAMPO=NUEVOVALOR7,AUXILIAR,POSTCHANGE=FDESIGNACION("CSELDESVALOR7","NO EXISTE VALOR  :NUEVOVALOR7 DE POSICION 7","CVERIFVALORES7","CAMBIO DE VALORES NO PERMITIDOS"),
                           CONTEXTUAL=FEJECUTAFORM("VDCALIFVALOR","N","","INDICADOR=7","NUEVOVALOR7=:VALORCALIF","SELECCION DE VALORES DE INDICADOR 7","S")                           
CAMPO=DESVALOR7,AUXILIAR,NOENTER

CAMPO=DESINDICADOR8,AUXILIAR,NOENTER
CAMPO=VALOR8,AUXILIAR,NOENTER
CAMPO=NUEVOVALOR8,AUXILIAR,POSTCHANGE=FDESIGNACION("CSELDESVALOR8","NO EXISTE VALOR  :NUEVOVALOR8 DE POSICION 8","CVERIFVALORES8","CAMBIO DE VALORES NO PERMITIDOS"),
                           CONTEXTUAL=FEJECUTAFORM("VDCALIFVALOR","N","","INDICADOR=8","NUEVOVALOR8=:VALORCALIF","SELECCION DE VALORES DE INDICADOR 8","S")                           
CAMPO=DESVALOR8,AUXILIAR,NOENTER

CAMPO=DESINDICADOR9,AUXILIAR,NOENTER
CAMPO=VALOR9,AUXILIAR,NOENTER
CAMPO=NUEVOVALOR9,AUXILIAR,POSTCHANGE=FDESIGNACION("CSELDESVALOR9","NO EXISTE VALOR  :NUEVOVALOR9 DE POSICION 9","CVERIFVALORES9","CAMBIO DE VALORES NO PERMITIDOS"),
                           CONTEXTUAL=FEJECUTAFORM("VDCALIFVALOR","N","","INDICADOR=9","NUEVOVALOR9=:VALORCALIF","SELECCION DE VALORES DE INDICADOR 9","S")                           
CAMPO=DESVALOR9,AUXILIAR,NOENTER

CAMPO=DESINDICADOR10,AUXILIAR,NOENTER
CAMPO=VALOR10,AUXILIAR,NOENTER
CAMPO=NUEVOVALOR10,AUXILIAR,POSTCHANGE=FDESIGNACION("CSELDESVALOR10","NO EXISTE VALOR :NUEVOVALOR10 DE POSICION 10","CVERIFVALORES10","CAMBIO DE VALORES NO PERMITIDOS"),
                           CONTEXTUAL=FEJECUTAFORM("VDCALIFVALOR","N","","INDICADOR=10","NUEVOVALOR10=:VALORCALIF","SELECCION DE VALORES DE INDICADOR 10","S")                           
CAMPO=DESVALOR10,AUXILIAR,NOENTER
CAMPO=SOLOSTOCK,AUXILIAR,VIRTUAL,OCULTO

CURSOR=CSELDESART SELECT DESART FROM VDARTIC WHERE CODART=:CODART;

CURSOR=CDESGLOSABLOQ SELECT SUBSTR(:BLOQLOTE,1,1) VALOR1,
                            SUBSTR(:BLOQLOTE,1,1) NUEVOVALOR1,
                            SUBSTR(:BLOQLOTE,2,1) VALOR2,
                            SUBSTR(:BLOQLOTE,2,1) NUEVOVALOR2,
                            SUBSTR(:BLOQLOTE,3,1) VALOR3,
                            SUBSTR(:BLOQLOTE,3,1) NUEVOVALOR3,
                            SUBSTR(:BLOQLOTE,4,1) VALOR4,
                            SUBSTR(:BLOQLOTE,4,1) NUEVOVALOR4,
                            SUBSTR(:BLOQLOTE,5,1) VALOR5,
                            SUBSTR(:BLOQLOTE,5,1) NUEVOVALOR5,
                            SUBSTR(:BLOQLOTE,6,1) VALOR6,
                            SUBSTR(:BLOQLOTE,6,1) NUEVOVALOR6,
                            SUBSTR(:BLOQLOTE,7,1) VALOR7,
                            SUBSTR(:BLOQLOTE,7,1) NUEVOVALOR7,
                            SUBSTR(:BLOQLOTE,8,1) VALOR8,
                            SUBSTR(:BLOQLOTE,8,1) NUEVOVALOR8,
                            SUBSTR(:BLOQLOTE,9,1) VALOR9,
                            SUBSTR(:BLOQLOTE,9,1) NUEVOVALOR9,
                            SUBSTR(:BLOQLOTE,10,1) VALOR10,
                            SUBSTR(:BLOQLOTE,10,1) NUEVOVALOR10 FROM DUAL;

                       
CURSOR=CDESINDICADOR1 SELECT DESINDICADOR DESINDICADOR1 FROM VDCALIF WHERE INDICADOR=1;
CURSOR=CDESINDICADOR2 SELECT DESINDICADOR DESINDICADOR2 FROM VDCALIF WHERE INDICADOR=2;
CURSOR=CDESINDICADOR3 SELECT DESINDICADOR DESINDICADOR3 FROM VDCALIF WHERE INDICADOR=3;
CURSOR=CDESINDICADOR4 SELECT DESINDICADOR DESINDICADOR4 FROM VDCALIF WHERE INDICADOR=4;
CURSOR=CDESINDICADOR5 SELECT DESINDICADOR DESINDICADOR5 FROM VDCALIF WHERE INDICADOR=5;
CURSOR=CDESINDICADOR6 SELECT DESINDICADOR DESINDICADOR6 FROM VDCALIF WHERE INDICADOR=6;
CURSOR=CDESINDICADOR7 SELECT DESINDICADOR DESINDICADOR7 FROM VDCALIF WHERE INDICADOR=7;
CURSOR=CDESINDICADOR8 SELECT DESINDICADOR DESINDICADOR8 FROM VDCALIF WHERE INDICADOR=8;
CURSOR=CDESINDICADOR9 SELECT DESINDICADOR DESINDICADOR9 FROM VDCALIF WHERE INDICADOR=9;
CURSOR=CDESINDICADOR10 SELECT DESINDICADOR DESINDICADOR10 FROM VDCALIF WHERE INDICADOR=10;

CURSOR=CSELDESVALOR1 SELECT DESVALOR DESVALOR1 FROM VDCALIFVALOR WHERE INDICADOR=1 AND VALORCALIF=:NUEVOVALOR1;
CURSOR=CSELDESVALOR2 SELECT DESVALOR DESVALOR2 FROM VDCALIFVALOR WHERE INDICADOR=2 AND VALORCALIF=:NUEVOVALOR2;
CURSOR=CSELDESVALOR3 SELECT DESVALOR DESVALOR3 FROM VDCALIFVALOR WHERE INDICADOR=3 AND VALORCALIF=:NUEVOVALOR3;
CURSOR=CSELDESVALOR4 SELECT DESVALOR DESVALOR4 FROM VDCALIFVALOR WHERE INDICADOR=4 AND VALORCALIF=:NUEVOVALOR4;
CURSOR=CSELDESVALOR5 SELECT DESVALOR DESVALOR5 FROM VDCALIFVALOR WHERE INDICADOR=5 AND VALORCALIF=:NUEVOVALOR5;
CURSOR=CSELDESVALOR6 SELECT DESVALOR DESVALOR6 FROM VDCALIFVALOR WHERE INDICADOR=6 AND VALORCALIF=:NUEVOVALOR6;
CURSOR=CSELDESVALOR7 SELECT DESVALOR DESVALOR7 FROM VDCALIFVALOR WHERE INDICADOR=7 AND VALORCALIF=:NUEVOVALOR7;
CURSOR=CSELDESVALOR8 SELECT DESVALOR DESVALOR8 FROM VDCALIFVALOR WHERE INDICADOR=8 AND VALORCALIF=:NUEVOVALOR8;
CURSOR=CSELDESVALOR9 SELECT DESVALOR DESVALOR9 FROM VDCALIFVALOR WHERE INDICADOR=9 AND VALORCALIF=:NUEVOVALOR9;
CURSOR=CSELDESVALOR10 SELECT DESVALOR DESVALOR10 FROM VDCALIFVALOR WHERE INDICADOR=10 AND VALORCALIF=:NUEVOVALOR10;

CURSOR=CBLOQLOTEENTRABLES SELECT VDUSER.TENGOPRIVINDICADOR(1) NUEVOVALOR1__ENTER,
                                 VDUSER.TENGOPRIVINDICADOR(2) NUEVOVALOR2__ENTER,
                                 VDUSER.TENGOPRIVINDICADOR(3) NUEVOVALOR3__ENTER,
                                 VDUSER.TENGOPRIVINDICADOR(4) NUEVOVALOR4__ENTER,
                                 VDUSER.TENGOPRIVINDICADOR(5) NUEVOVALOR5__ENTER,
                                 VDUSER.TENGOPRIVINDICADOR(6) NUEVOVALOR6__ENTER,
                                 VDUSER.TENGOPRIVINDICADOR(7) NUEVOVALOR7__ENTER,
                                 VDUSER.TENGOPRIVINDICADOR(8) NUEVOVALOR8__ENTER,
                                 VDUSER.TENGOPRIVINDICADOR(9) NUEVOVALOR9__ENTER,
                                 VDUSER.TENGOPRIVINDICADOR(10) NUEVOVALOR10__ENTER
                          FROM DUAL;
                          
CURSOR=CVERIFVALORES1 SELECT :NUEVOVALOR1 FROM DUAL WHERE VDUSER.BLOQUEOSPRIVPOS(1, :VALOR1, :NUEVOVALOR1)=0; 
CURSOR=CVERIFVALORES2 SELECT :NUEVOVALOR1 FROM DUAL WHERE VDUSER.BLOQUEOSPRIVPOS(2, :VALOR2, :NUEVOVALOR2)=0; 
CURSOR=CVERIFVALORES3 SELECT :NUEVOVALOR1 FROM DUAL WHERE VDUSER.BLOQUEOSPRIVPOS(3, :VALOR3, :NUEVOVALOR3)=0; 
CURSOR=CVERIFVALORES4 SELECT :NUEVOVALOR1 FROM DUAL WHERE VDUSER.BLOQUEOSPRIVPOS(4, :VALOR4, :NUEVOVALOR4)=0; 
CURSOR=CVERIFVALORES5 SELECT :NUEVOVALOR1 FROM DUAL WHERE VDUSER.BLOQUEOSPRIVPOS(5, :VALOR5, :NUEVOVALOR5)=0; 
CURSOR=CVERIFVALORES6 SELECT :NUEVOVALOR1 FROM DUAL WHERE VDUSER.BLOQUEOSPRIVPOS(6, :VALOR6, :NUEVOVALOR6)=0; 
CURSOR=CVERIFVALORES7 SELECT :NUEVOVALOR1 FROM DUAL WHERE VDUSER.BLOQUEOSPRIVPOS(7, :VALOR7, :NUEVOVALOR7)=0; 
CURSOR=CVERIFVALORES8 SELECT :NUEVOVALOR1 FROM DUAL WHERE VDUSER.BLOQUEOSPRIVPOS(8, :VALOR8, :NUEVOVALOR8)=0; 
CURSOR=CVERIFVALORES9 SELECT :NUEVOVALOR1 FROM DUAL WHERE VDUSER.BLOQUEOSPRIVPOS(9, :VALOR9, :NUEVOVALOR9)=0; 
CURSOR=CVERIFVALORES10 SELECT :NUEVOVALOR1 FROM DUAL WHERE VDUSER.BLOQUEOSPRIVPOS(10, :VALOR10, :NUEVOVALOR10)=0; 

CURSOR=CDAMEOBSERV SELECT TRIM(:OBSERV1) || ' ' || TRIM(:OBSERV2) || ' ' || TRIM(:OBSERV3) || ' ' || TRIM(:OBSERV4) OBSERV FROM DUAL;

CURSOR=CDAMENUEVOBLOQLOTE SELECT :NUEVOVALOR1||:NUEVOVALOR2||:NUEVOVALOR3||:NUEVOVALOR4||:NUEVOVALOR5||:NUEVOVALOR6||:NUEVOVALOR7||:NUEVOVALOR8||:NUEVOVALOR9||:NUEVOVALOR10 NUEVOBLOQLOTE FROM DUAL;

TECLA=F4,FEJECUTA("+CDAMENUEVOBLOQLOTE","",
                  FNUEVOBLOQLOTE(":CODART",":CODLOT",":NUEVOBLOQLOTE",":SOLOSTOCK"),":V10ERROR",
                  FCOMMIT,"",
                  %FFAILURE,"CAMBIO DE CALIFICACIONES DEL LOTE REALIZADO",
                  +FPULSATECLAS("F3","F2"),"")      

