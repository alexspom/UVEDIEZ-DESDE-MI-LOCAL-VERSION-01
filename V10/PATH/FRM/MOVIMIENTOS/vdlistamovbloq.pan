# Módulo   : VDLISTAMOVBLOQ.PAN
# Función  : Lista de Movimientos con información sobre bloqueos
#
# Creación : 07-08-2008
# Autor    : FGS
###########################################
# Histórico de cambios:
LISTA DE MOVIMIENTOS
Contenedor Ubicación    Código   Concepto Articulo     Lote       Cantidad   Stat  Bloqueos              Inserción           
_18_______ _20_________ @L@@@@@@ _10_____ _40_________ _40_______ #15L##.### @L@@@ __________ __________ _32_________ ¿D-MM-Y.YY ________ 
|
TABLA=VDMOVIM


CAMPO=CODMATORI,TOOLTIP("Matrícula origen"),TITULO("Contenedor"),WLONX=16
CAMPO=CODUBIORI,TOOLTIP("Ubicación origen"),TITULO("Ubicación"),WLONX=16
CAMPO=CODMOV,TOOLTIP("Código del movimiento"),POSTCHANGE=FDESIGNACION("CSELART",""),TITULO("Código")
CAMPO=CODCONCE,TOOLTIP("Concepto del movimiento"),CONTEXTUAL=FEJECUTAFORM("VDCONCEPTO","N","","","CODCONCE=:CODCONCE","Selección de concepto","S"),TITULO("Concepto"),WLONX=16
CAMPO=CODART,NOENTER,TITULO("Artículo")
CAMPO=DESART,AUXILIAR,NOENTER,OCULTO,"_100"
CAMPO=CODLOT,NOENTER,TITULO("Lote")
CAMPO=CANTIDAD,TOOLTIP("Cantidad en unidades host"),CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),TITULO("Cantidad")
CAMPO=STATUS,TOOLTIP("Estado del movimiento"),
                CONTEXTUAL=FEJECUTAFORM("VDSTATUS","N","TIPOSTATUS='MOV'","","STATUS=:STATUS","Selección de status","S"),
                TITULO("Stat")
CAMPO=BLOQUEOSORI,NOENTER,TITULO("Bloqueos")
CAMPO=BLOQUEOSDEST,NOENTER
CAMPO=CODOPEINS,NOENTER,TITULO("Inserción")
CAMPO=FECINS,NOENTER,TITULO("")
CAMPO=HORAINS,NOENTER

CURSOR=CSELART SELECT DESART FROM VDARTIC WHERE CODART=:CODART;

                   

