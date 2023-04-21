#*****************************************************************
#Módulo: VDCAMBIAPEDNEWRUTA.PAN
#Funcionalidad : Cambiar una expedición de ruta.
#Autor: RFD     
#Fecha: 27-10-2008
#*****************************************************************
#* Histórico de cambios
#
SERIE DESTINO

           ÏÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË 
           ³                         ³  
           ³  Serie Destino: @L@@@@  ³ 
           ³                         ³ 
           ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ 
       
       Estado 
       @L@@@ ______________________________ 
       Agencia 
       _10__ ______________________________

                                                |

TABLA=VDSERIEEXP
SELECT='N' FLAGCREARUTA;
NOINSERT
NOUPDATE
NODELETE
WHERE=STATUS IN (VDST.FSEXLANZADA,VDST.FSEXFINALIZADA) AND CODSERIEEXP<>:CODSERIEANTERIOR1;
ORDERBY=CODSERIEEXP DESC,STATUS; 


CAMPO=CODSERIEEXP,POSTCHANGE=FEJECUTA("CSELASIGCODSERIENUEVA","Error en CSELASIGCODSERIENUEVA",
                                       +FIF("CSELFLAGCREARUTA",
                                            FEJECUTA("CSELCODAGEANTERIOR","Se debe seleccionar primero la serie origen",
                                                     "CSELDESAGE2","No existe agencia"),
                                            FEJECUTA("CSELDESAGE","No existe agencia",
                                                     "CVALIDARUTANUEVA","SERIE DESTINO INCORRECTA \n\n No se pueden mover expediciones a la serie :CODSERIENUEVA.  ")),""
                                     )

CAMPO=STATUS,NOENTER,POSTCHANGE=FDESIGNACION(FIF("-CSELFLAGCREARUTA",
                                                 FEJECUTA("CDESSTATUS","Estado inexistente.")),"")
CAMPO=DESSTATUS,UPPER,AUXILIAR,NOENTER                                       
CAMPO=CODAGE,POSTCHANGE=FDESIGNACION("CSELDESAGE2","No existe agencia")
CAMPO=DESAGE,AUXILIAR,NOUPDATE

CAMPO=CODSERIENUEVA,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODSERIEANTERIOR1,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODAGEANTERIOR,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODAGENUEVA,AUXILIAR,VIRTUAL,OCULTO
CAMPO=FLAGCREARUTA,AUXILIAR,VIRTUAL,OCULTO
CAMPO=DUMMY,AUXILIAR,OCULTO,"@"

CURSOR=CDESSTATUS SELECT DESSTATUS
                    FROM VDSTATUS
                   WHERE TIPOSTATUS='SEX' AND STATUS=:STATUS;

CURSOR=CSELFLAGCREARUTA SELECT 'S' FLAGCREARUTA FROM DUAL WHERE :FLAGCREARUTA='S';

CURSOR=CSELCODAGEANTERIOR SELECT :CODAGEANTERIOR CODAGE FROM DUAL;

CURSOR=CSELDESAGE2 SELECT CODAGE CODAGENUEVA,DESAGE FROM VDAGENCIA WHERE CODAGE=:CODAGE;

CURSOR=CSELASIGCODSERIENUEVA SELECT :CODSERIEEXP CODSERIENUEVA FROM DUAL;

CURSOR=CVALIDARUTANUEVA SELECT 1 DUMMY FROM DUAL WHERE EXISTS (SELECT CODSERIEEXP FROM VDSERIEEXP SEX, VDAGENCIA AGE 
                                                                                 WHERE SEX.CODAGE=AGE.CODAGE
                                                                                   AND SEX.CODSERIEEXP=:CODSERIENUEVA 
                                                                                   AND SEX.STATUS IN (VDST.FSEXLANZADA,VDST.FSEXFINALIZADA)); 
                                                                                   
CURSOR=CSELNUEVARUTA SELECT VDSECSERIEEXP.NEXTVAL CODSERIEEXP,'S' FLAGCREARUTA FROM DUAL;

CURSOR=CSELDESAGE SELECT AGE.CODAGE CODAGE ,AGE.DESAGE DESAGE
                   FROM VDAGENCIA AGE, VDSERIEEXP SEX
                   WHERE SEX.CODSERIEEXP=:CODSERIEEXP
                     AND AGE.CODAGE=SEX.CODAGE;

                  
                 
                   
CONTEXTUAL=FLEEMENU("VDCAMBDERUTADEST.ZOO")
