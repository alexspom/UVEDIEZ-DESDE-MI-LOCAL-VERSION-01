# M�dulo: VDRUSER.PAN
# Funci�n: Petici�n de usuario de radios
#
#
# Creado el 17-10-2007 por Eduardo Alsina
#
# Hist�rico de cambios
#
# 
PETICION DE USUARIO
_____________

  /*IDENTIFIQUESE*/ 

      IDENTIFICACION

    USUARIO:  __________
    PASSWORD: _P________



|

POSTUPDATE=FEJECUTA("+CPASAMAY","No puedo pasar el password a mayusculas",
                    "CSELUSU","\n\n\nUSUARIO NO EXISTE",
#                    FVERIFICAPASS(":CODOPE",":PASSWORD","V10ERROR"),":V10ERROR",
                    "CVERPRIVILEGIO","\n\n\nNO TIENE PRIVILEGIO PARA\nCONECTARSE A ESTE TERMINAL",
                    "CLOGINRADIO","\n\n\n:MENSAJE",
                    "CVERERROR","\n\n\n:MENSAJE",
                    FCARGATERMINAL("CODOPE"),"",
                    FCOMMIT,"")

CAMPO=CODRECURSO,NOENTER
CAMPO=CODOPE,SCAN,AUTOENTER
#,POSTCHANGE=FEJECUTA(FFUERZASCAN("USU"),"\n DEBE LEER USUARIO")
CAMPO=PASSWORD,SCAN,AUTOENTER
CAMPO=MENSAJE,OCULTO,"_200_"

CURSOR=CLOGINRADIO BEGIN
                    :MENSAJE:=VDRADIO.LOGIN(:CODRECURSO,:CODOPE);
                   END;@
                   
CURSOR=CVERERROR SELECT :MENSAJE FROM DUAL WHERE :MENSAJE IS NULL;                   

CURSOR=CVERPRIVILEGIO SELECT :CODRECURSO 
                       FROM VDRECURSO 
                       WHERE CODRECURSO=:CODRECURSO AND VDUSER.TIENEPRIVILEGIO(:CODOPE,PRIVILEGIOSLOGIN)=1;

CURSOR=CPASAMAY SELECT UPPER(:CODOPE) CODOPE FROM DUAL WHERE VD.GETPROP('PAADMITEMINUS')='N';

CURSOR=CSELUSU SELECT TRIM(:CODOPE) CODOPE FROM VDUSUARIO WHERE CODOPE=TRIM(:CODOPE);

ONLINE=LOGIN EN APLICACION DE RADIOS;











