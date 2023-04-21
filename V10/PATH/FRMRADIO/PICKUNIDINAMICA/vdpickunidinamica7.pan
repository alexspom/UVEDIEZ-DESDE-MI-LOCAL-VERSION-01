# Módulo   : VDPICKUNIDINAMICA7.PAN
# Función  : Formulario de recogida de bultos de unidades.
#            Pantalla de información de zonas pendientes
#            del bulto.
#
# Creación : 27-05-2008
# Autor    : FPD
###########################################
# Histórico de cambios:
#
PICKING DINAMICA
_10_______ _10_______  

BULTO 
__________________

ZONAS PENDIENTES
_255________________

PULSAR ENTER _
|

#POSTQUERY=FEJECUTA("CUPDBULTO","ERROR\n DESASIGNANDO BULTO",
#                   FCOMMIT,"",
#                   FCARGAFORM(""))
POSTQUERY=FEJECUTA(FCARGAFORM(""))


#DEFINICION DE CAMPOS
CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=CODBULTO,VIRTUAL,NOENTER
CAMPO=ZONASPEND,VIRTUAL,NOENTER
CAMPO=HAYTECLA,UPPER,AUXILIAR

#DEFINICION DE CURSORES
#CURSOR=CUPDBULTO UPDATE VDBULTOCAB
#                    SET STATUS=VDST.FBUCPDTESERVIR
#                  WHERE CODBULTO=:CODBULTO AND STATUS=VDST.FBUCASITERM;
