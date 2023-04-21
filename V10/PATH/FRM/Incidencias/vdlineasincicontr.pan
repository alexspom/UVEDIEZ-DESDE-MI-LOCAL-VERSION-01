# Módulo   : VDLINEASINCICONTR.PAN
# Función  : LISTA DE INCIDENCIAS DE UN CONTRATO DE MANTENIMIENTO
#
# Creación : 14/12/2011 19:40:05
# Autor    : JCSR
###########################################
# Histórico de cambios:
Datos de las incidencias
Incidencia  Minutos Fec. Creado Descripción                                                                Causa                                                                              Solución
@L@@@@@@@ @L@@@@@@  ¿D-MM-Y.YY  _4000______________________________________________________________________ _500_____________________________________________________________________________  _500__________________________________________________________________________
|

SOLOQUERY

SELECT = SELECT INC.CODINCI, DESCRIPCION, CAUSA, SOLUCION, SUM(TIEMPO) MINUTOS, INC.FECCREADO
           FROM VDINCICAB INC, VDINCILIN INL, VDEMPLEADO EMP, VDINCILINOPE ILO, VDMANTENIMIENTO MAN
          WHERE     MAN.CODMANTENIMIENTO = INC.CODMANTENIMIENTO
                AND INC.FECCREADO BETWEEN MAN.FECINICIO AND MAN.FECFIN
                AND INC.CODINCI = INL.CODINCI
                AND INL.CODINCI = ILO.CODINCI
                AND INL.SEQLINEA = ILO.SEQLINEA
                AND ILO.CODOPE = EMP.CODOPE
                AND INC.STATUS = 500;
GROUPBY= INC.CODINCI, DESCRIPCION, CAUSA, SOLUCION, FECCREADO;

CAMPO = CODMANTENIMIENTO, VIRTUAL, OCULTO, PREFIJO=MAN
CAMPO = CODINCI, AUXILIAR, TITULO ("Incidencia"), WLONX=30
CAMPO = MINUTOS, AUXILIAR, TITULO ("Minutos")
CAMPO = FECCREADO, AUXILIAR, TITULO("Fec. creado"), WLONX= 15
CAMPO = DESCRIPCION, AUXILIAR, TITULO ("Descripción")
CAMPO = CAUSA, AUXILIAR, TITULO ("Causa")
CAMPO = SOLUCION, AUXILIAR, TITULO ("Solución")

TECLA = SF10, FEJECUTAFORM ("VDINCIDENCIAS", "S","CODINCI=:CODINCI","","DATOS DE LA INCIDENCIA :CODINCI")