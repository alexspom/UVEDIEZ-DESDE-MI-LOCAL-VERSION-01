# M�dulo   : VDREPULMON.PAN
# Funci�n  : Mensaje de desconexi�n cuando no existe identificaci�n de operario
#
# Creaci�n : 30-01-2008
# Autor    : ICC
###########################################
# Hist�rico de cambios:
# 
PETICION DE USUARIO
_____________

   

 NO ESTA CONFIGURADA
 LA IDENTIFICACION 
 DE USUARIO

 PULSE ENTER PARA 
 CONECTAR _

|


POSTQUERY=FEJECUTA("CUPDRECURSO","Error actualizando recurso",
                   FCOMMIT,"",
                   +FCARGAFORM(""),"")

CAMPO=CODRECURSO,NOENTER
CAMPO=OPCION,UPPER

CURSOR=CUPDRECURSO UPDATE VDRECURSO 
                      SET CONECTADO  = 'S' ,
                          CODOPEMODIF=VDUSER.GETUSER, FECMODIF=VD.FECHASYS, HORAMODIF=VD.HORASYS
                    WHERE CODRECURSO = :CODRECURSO;
