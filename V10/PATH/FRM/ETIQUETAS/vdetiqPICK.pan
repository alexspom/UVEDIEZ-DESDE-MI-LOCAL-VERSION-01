# Módulo   : VDETIQCNT.PAN
# Función  : Impresión de etiquetas de contenedor. Elección del número de etiquetas de contenedor NUEVO.
#
# Creación : 13-08-2008
# Autor    : JCSR
###########################################
# Histórico de cambios:
NUMERO DE ETIQUETAS PICKING A IMPRIMIR.

  Seleccione el número de matrículas @L@

  Seleccione el número de etiquetas por matrícula @L 
|

TABLA=DUAL


CURSOR=CIMPRIME BEGIN
                  VDIMPRIME.IMPRIME('ETIQ', 'VDCODMAT.ZPL;VDETIQUETAS.VSQ;MATRICULA', 'CODMAT='||:CODMAT||'',1,'', '', :V10ERROR); 
                  COMMIT;				  
                 END;@

TECLA=F4,FEJECUTA("CSELETIQ","El número de etiquetas a imprimir debe ser mayor que 0",
                   FWHILE(FERRORCURSOR("CSELETIQ"),
                   FEJECUTA("CSELCODMAT", "No puedo sacar el Código de matrícula", 
                            "CIMPRIME", "No puedo insertar los datos de las matrículas.",
                            FCOMMIT,"",
                            +FFETCHCURSOR("CSELETIQ"),"ERROR EN FETCH")), "ERROR EN WHILE",
                   FCOMMIT, "")


CAMPO=NUMCNT, AUXILIAR
CAMPO=NUMETIQ, AUXILIAR
CAMPO=CODMAT, AUXILIAR, OCULTO, "_18_"

CURSOR=CSELETIQ SELECT :NUMETIQ NUMETIQ FROM ALL_TABLES  WHERE ROWNUM<=:NUMCNT;                                

CURSOR=CSELCODMAT SELECT VDSECPICK.NEXTVAL CODMAT FROM DUAL;

# POSCONTE A 1
# STATUS A 0
# FECHA ENTRADA, HORAENTRADA => EN VDCONTE FECCREADO Y HORACREADO
# TIPOCONTE A DUMMY


                                                 
