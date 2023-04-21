# Módulo   : VDMOVPARCIALASIG.PAN
# Función  : Formulario de movimiento de stock parcial asignado a recurso
#            Pantalla de obtencion de movimientos.
#
# Creación : 20-05-2008
# Autor    : JMM
###########################################
# Histórico de cambios:
#
MOVIMIENTO DE STOCK PARCIAL
_10_______ _10_______

NO HAY MOVIMIENTOS
PENDIENTES

PULSE ENTER _

|

PREQUERY=FEJECUTA(FIF("CSELMOVPDTE",FPOSICIONABLOQUE("VDMOVSTKPARCIALORI.PAN")), "ERROR EN CSELMOVPDTE") 

POSTQUERY=FEJECUTA(FCARGAFORM(""),"ERROR\n AL VOLVER AL MENU") 


# DEFINICION DE CAMPOS
CAMPO=CODRECURSO,VIRTUAL,NOENTER
CAMPO=CODOPE,VIRTUAL,NOENTER
CAMPO=SALIR

CAMPO=CODMOV,OCULTO,"@L@@@@@@@@"


CURSOR=CSELMOVPDTE SELECT MOV.CODMOV
                     FROM VDMOVIM MOV
                    WHERE MOV.CODRECURSO=:CODRECURSO
                          AND MOV.STATUS IN (VDST.FMOVASIGNADO,VDST.FMOVENUBIINTER,VDST.FMOVPRESENTADO)
                          AND MOV.CODMATORI != MOV.CODMATDEST
                    ORDER BY DECODE(MOV.STATUS,VDST.FMOVENUBIINTER,0,1),
                          DECODE(NVL(NUMEROSERIE,'-'),'-',1,0),
                          DECODE(NVL(BULTO,'-'),'-',1,0),
                          DECODE(PRECIOUNI,0,1,0),
                          DECODE(NVL(TIPOEMBA,'-'),'-',1,0),
                          DECODE(NVL(CODRECEP,'-'),'-',1,0),
                          DECODE(NVL(MARCASTK,'-'),'-',1,0),
                          DECODE(NVL(BLOQUEOSORI,'-'),'-',1,0),
                          DECODE(NVL(CODLOT,'-'),'-',1,0);

