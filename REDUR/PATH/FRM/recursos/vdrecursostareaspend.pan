# Módulo   : VDRECURSOSTAREASPEND.PAN
# Función  : Recursos con tareas asignadas
#
# Creación : 07-04-2020
# Autor    : CGG
###########################################
# Histórico de cambios:
MANTENIMIENTO DE RECURSOS
Código     Descripción                  Activo Dirección        Conectado Terminal         Usuario           Perfil
__________ _40_________________________ _      _30_____________ _         ________________ ________________  ____________________ _40___________________________
|

TABLA=VDRECURSO
WHERE=CODRECURSO IN (SELECT DISTINCT CODRECURSO
                       FROM VDMOVIM
                      WHERE CODRECURSO IS NOT NULL
                        AND STATUS < VDST.FMOVFINALIZADO);
ORDERBY=CODRECURSO;
NOINSERT
NOUPDATE
NODELETE
PQUERY


CAMPO=CODRECURSO,NOUPDATE,TOOLTIP("Código del recurso"),TITULO("Código")
CAMPO=DESRECURSO,TOOLTIP("Designación del recurso"),POSTCHANGE=FVALNOCERO("Debe introducir la designación del recurso"),TITULO("Descripción")
CAMPO=ACTIVO,TOOLTIP("Indica si el recurso es utilizable"),CHECKBOX("N","S"),TITULO("Act."),WLONX=15
CAMPO=DIRRECURSO,TOOLTIP("Direccion física del recurso (Normalmente dirección ip)"),TITULO("Dirección")
CAMPO=CONECTADO,TOOLTIP("Indica si el recurso est  conectado"),POSTCHANGE=FVERIFICA("SN","Debe introducir S(i) o N(o)"),CHECKBOX("N","S"),TITULO("Con."),WLONX=15
CAMPO=TERMINAL,TOOLTIP("Maquina a la que se ha conectado el recurso"),TITULO("Máquina")
CAMPO=CODOPE,TOOLTIP("Operario identificado en el terminal"),TITULO("Operario")
CAMPO=CODPERFIL,TOOLTIP("Perfil que esta ejecutando el recurso"),POSTCHANGE=FDESIGNACION("CSELDESPERFIL","No existe perfil"),TITULO("Perfil")
CAMPO=DESPERFIL,AUXILIAR,NOENTER,TOOLTIP("Designación del perfil que esta ejecutando el recurso")

CURSOR=CSELDESPERFIL SELECT DESPERFIL FROM VDPERFILTAREA WHERE CODPERFIL=:CODPERFIL
                   UNION
                  SELECT '' DESPERFIL FROM DUAL WHERE :CODPERFIL IS NULL;



CURSOR=CDESASIGNA DECLARE
                   RET NUMBER;
                  BEGIN
                   RET:=VDPLANMOV.DESASIGNAMOV(:CODRECURSO);
                   COMMIT;
                  END;@
                                
