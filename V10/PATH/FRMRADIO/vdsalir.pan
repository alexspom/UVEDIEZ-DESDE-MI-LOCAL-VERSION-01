# Módulo   : VDSALIR.PAN
# Función  : Finzalizar la sesión
#
# Creación : 14-02-2008
# Autor    : ICC
###########################################
# Histórico de cambios:
# 
FINALIZAR LA SESION
 _10_______ _10__________ 


  SALIR  _ (0/1)
|

POSTQUERY=FEJECUTA(FSWITCHCADENA(":SALIR",
                                 "0", FCARGATERMINAL("CODOPE"),
                                 "1", FEJECUTA("+CCHECKBULTOS","",
                                               "CUPDMOV","ERROR ACTUALIZANDO MOVIMIENTO",
                                               "CUPDRECURSO","ERROR ACTUALIZANDO RECURSO",
                                               FCOMMIT,"",
                                               FDESCONECTAUSUARIO,"ERROR DESCONECTANDO",
                                               FIF("CSELIDENTOPE",
                                                                  +FCARGAFORM("VDRUSER"),
                                                                  +FCARGAFORM("VDNOIDENTOPE")),"ERROR EN FIF"),
                                 "",FCARGAFORM("")),"")

CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=SALIR,UPPER, POSTCHANGE=FVERIFICA("01 ","EL CAMPO DEBE SER 0(NO) 1(Si) O Blanco")
CAMPO=DUMMY,OCULTO,"#"
#CAMPO=IDENTOPE,OCULTO,"_"

CURSOR=CUPDMOV UPDATE VDMOVIM MOV
                  SET CODRECURSO= NULL,
                      STATUS = VDST.FMOVPDTERECOGE,
                      PRIOMOV=PRIOMOV+1,
                      CODOPEMODIF=:CODOPE, FECMODIF=VD.FECHASYS, HORAMODIF=VD.HORASYS
                WHERE CODRECURSO||'' = :CODRECURSO
                  AND STATUS >= VDST.FMOVASIGNADO AND STATUS < VDST.FMOVRECOGIDO;

CURSOR=CUPDRECURSO UPDATE VDRECURSO 
                      SET CONECTADO  = 'N' ,
                        STATUS=VDST.FRECINACTIVO,NPANTALLA='',
                        CODOPEMODIF=:CODOPE, FECMODIF=VD.FECHASYS, HORAMODIF=VD.HORASYS
                     WHERE CODRECURSO = :CODRECURSO;

CURSOR=CSELIDENTOPE SELECT 1 DUMMY
                      FROM DUAL
                     WHERE VD.GETPROP('IDENTOPE')='S';

CURSOR=CCHECKBULTOS SELECT :CODRECURSO FROM VDMOVIM WHERE CODRECURSO = :CODRECURSO AND STATUS = VDST.FMOVASIGNADO;

CURSOR=CUPDBULTOS UPDATE VDBUCAB CB SET CB.STATUS = 2000 , CODOPEMODIF = :CODOPE,
                                        FECMODIF = VD.FECHASYS, HORAMODIF = VD.HORASYS
                   WHERE CB.CODBULTO IN (SELECT LB.CODBULTO FROM VDBULIN LB, VDMOVIM MOV
                                          WHERE LB.CODMOV = MOV.CODMOV AND 
                                                MOV.CODRECURSO = :CODRECURSO AND
                                                MOV.STATUS =  VDST.FMOVASIGNADO);
