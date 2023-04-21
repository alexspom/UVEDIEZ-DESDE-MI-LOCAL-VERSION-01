# Módulo   : VDMONIMOVIM.PAN
# Función  : Monitor de movimientos. Listado de movimientos
#
# Creación : 04-08-2008
# Autor    : JMM
###########################################
# Histórico de cambios:
#
MOVIMIENTOS EN EL ESTADO SELECCIONADO
                                                                   ÏÄÄÄÄÄÄÄÄÄÄÄ ORIGEN ÄÄÄÄÄÄÄÄÄÄÄË ÏÄÄÄÄÄÄÄÄÄÄÄ DESTINO ÄÄÄÄÄÄÄÄÄÄË 
Código    Articulo                      Tarea     Concepto Recurso Matricula  Ubicacion    Area     Matricula  Ubicacion  Area       Cantidad  
@L@@@@@@@ _40______ _100_______________ _32______ _10_____ _10____ _18_______ _20_________ _20_____ _18_______ _20_______ _20_______ @L,@@@@@  
|
#WFRAME(260,-2,318,0,"Origen","font-style:bold;font-family:Times New Roman")
#WFRAME(580,-2,305,0,"Destino","font-style:italic;font-family:Times New Roman")

SOLOQUERY
TABLA=MOV
SELECT=SELECT MOV.CODMOV,MOV.CODART,ART.DESART, MOV.TAREA, MOV.CODCONCE, MOV.CODRECURSO, MOV.CODMATORI, MOV.CODUBIORI, MOV.CODMATDEST, MOV.CODUBIDEST,MOV.CANTIDAD
         FROM VDMOVIM MOV,VDARTIC ART
        WHERE MOV.STATUS = :STATUS AND MOV.CODART=ART.CODART;
ORDERBY=MOV.PRIOMOV,MOV.CODMATORI,MOV.TAREA,MOV.CODCONCE,MOV.CODMOV;

CAMPO=STATUS,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODMOV,NOUPDATE,TOOLTIP("Código del movimiento"),TITULO("Código")
CAMPO=CODART,NOUPDATE,TITULO("Articulo")
CAMPO=DESART,NOUPDATE,TITULO("Desc.Articulo")
CAMPO=TAREA,NOUPDATE,TOOLTIP("Tarea del movimiento"),TITULO("Tarea")
CAMPO=CODCONCE,NOUPDATE,TOOLTIP("Concepto del movimiento"),TITULO("Concepto"),WLONX=25
CAMPO=CODRECURSO,NOUPDATE,TOOLTIP("Recurso que ejecuta el movimiento"),TITULO("Term."),WLONX=25
CAMPO=CODMATORI,TOOLTIP("Matricula del contenedor origen del movimiento"),TITULO("Mat.Orig.")
CAMPO=CODUBIORI,NOUPDATE,TOOLTIP("Ubicacion origen del movimiento"),POSTCHANGE=FDESIGNACION("+CSELAREAORI",""),TITULO("Ubi.Orig.")
CAMPO=CODAREAORI,AUXILIAR,NOENTER,TOOLTIP("Area origen del movimiento"),TITULO("Area Orig."),WHERE=(CODUBIORI IN (SELECT CODUBI FROM VDUBICA WHERE CODAREA=:CODAREAORI));
CAMPO=CODMATDEST,TOOLTIP("Matricula del contenedor destino del movimiento"),TITULO("Mat.Dest.")
CAMPO=CODUBIDEST,NOUPDATE,TOOLTIP("Ubicacion destino del movimiento"),POSTCHANGE=FDESIGNACION("+CSELAREADEST",""),TITULO("Ubi.Dest.")
CAMPO=CODAREADEST,AUXILIAR,NOENTER,TOOLTIP("Area origen del movimiento"),TITULO("Area Dest."),WHERE=(CODUBIDEST IN (SELECT CODUBI FROM VDUBICA WHERE CODAREA=:CODAREADEST));
CAMPO=CANTIDAD,TITULO("Cantidad")

CURSOR=CSELAREAORI SELECT CODAREA CODAREAORI FROM VDUBICA WHERE CODUBI = :CODUBIORI;

CURSOR=CSELAREADEST SELECT CODAREA CODAREADEST FROM VDUBICA WHERE CODUBI = :CODUBIDEST;



