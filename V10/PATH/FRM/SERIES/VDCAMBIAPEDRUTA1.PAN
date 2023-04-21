#*****************************************************************
#Módulo: VDCAMBIAPEDRUTA1.PAN
#Funcionalidad : Cambiar una expedición de ruta.
#Autor: RFD      
#Fecha: 27-10-2008
#*****************************************************************
#* Histórico de cambios
#
SERIE ORIGEN

          ÏÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË 
          ³                         ³  
          ³   Serie Origen: @L@@@@  ³ 
          ³                         ³ 
          ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ 
       
      Estado 
      @L@@@ ______________________________ 
      Agencia 
      _10__ ______________________________

                                               |

TABLA=VDSERIEEXP

NOINSERT
NOUPDATE
NODELETE

SELECT=CODSERIEEXP CODSERIEANTERIOR,CODSERIEEXP CODSERIEANTERIOR1, CODAGE CODAGEANTERIOR;
WHERE=STATUS IN (VDST.FSEXLANZADA,VDST.FSEXFINALIZADA) AND CODSERIEEXP<>:CODSERIENUEVA;
ORDERBY=CODSERIEEXP DESC,STATUS; 



CAMPO=CODSERIEEXP,POSTCHANGE=FDESIGNACION("CSELDATANTERIOR","Error en CSELDATANTERIOR",
                                       "+CVALIDARUTAANTERIOR","RUTA ORIGEN INCORRECTA\n \n Las expediciones de la ruta :CODSERIEEXP  no pueden ser cambiados de ruta .")
CAMPO=STATUS,NOUPDATE,POSTCHANGE=FDESIGNACION("CDESSTATUS","Estado inexistente.")
CAMPO=DESSTATUS,UPPER,AUXILIAR,NOENTER
CAMPO=CODAGE,NOUPDATE,POSTCHANGE=FDESIGNACION("CSELDESAGE","No existe agencia")
CAMPO=DESAGE,AUXILIAR,NOUPDATE

CAMPO=CODSERIENUEVA,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODSERIEANTERIOR,AUXILIAR,OCULTO,"@@@@@@"
###VIRTUAL,
CAMPO=CODAGEANTERIOR,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODSERIEANTERIOR1,AUXILIAR,OCULTO,VIRTUAL
CAMPO=FLAGCREARUTA,AUXILIAR,OCULTO,VIRTUAL
CAMPO=DUMMY,AUXILIAR,OCULTO,"@"


CURSOR=CDESSTATUS SELECT DESSTATUS
                    FROM VDSTATUS
                   WHERE TIPOSTATUS='SEX' AND STATUS=:STATUS;

CURSOR=CSELDATANTERIOR SELECT :CODSERIEEXP CODSERIEANTERIOR,:CODAGE CODAGEANTERIOR FROM DUAL;

CURSOR=CVALIDARUTAANTERIOR SELECT 1 DUMMY FROM DUAL WHERE EXISTS (SELECT CODSERIEEXP FROM VDSERIEEXP SEX, VDAGENCIA AGE 
                                                                                 WHERE SEX.CODAGE=AGE.CODAGE
                                                                                   AND SEX.CODSERIEEXP=:CODSERIEANTERIOR 
                                                                                   AND SEX.STATUS IN (VDST.FSEXLANZADA,VDST.FSEXFINALIZADA)); 

CURSOR=CSELDESAGE SELECT AGE.CODAGE CODAGE ,AGE.DESAGE DESAGE
                    FROM VDAGENCIA AGE, VDSERIEEXP SEX
                   WHERE SEX.CODSERIEEXP=:CODSERIEEXP
                     AND AGE.CODAGE=SEX.CODAGE;

                  
CONTEXTUAL=FLEEMENU("VDCAMBDERUTAORI.ZOO")             

