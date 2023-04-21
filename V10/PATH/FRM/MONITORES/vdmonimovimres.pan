# Módulo   : VDMONIMOVIMRES.PAN
# Función  : Monitor de movimientos. Resumen del movimiento
#
# Creación : 04-08-2008
# Autor    : JMM
###########################################
# Histórico de cambios:
#
DETALLE DEL MOVIMIENTO
 Artículo _40_____________ _100______________________________     Cantidad #15L###########    
                                                                                                                       
 Uni/emb #L15########## Emb. conte. @L@@@ Tipo emba __________   Bloqueos:    Origen __________  Destino __________ 

 Concepto _20_____ 
 Creacion _32___________ ¿D-MM-Y.YY ________ Ejecución _32_________ ¿D-MM-Y.YY ________ Fin ¿D-MM-Y.YY _______
                                                                                                                       
|
TABLA=VDMOVIM

CAMPO=CODMOV,VIRTUAL,OCULTO
CAMPO=CODART,TOOLTIP("Código del artículo"),POSTCHANGE=FDESIGNACION("CSELDESART","No existe artículo"),
                CONTEXTUAL=FEJECUTAFORM("VDSELART","S","","","CODART=:CODART","Selección de articulo","N") 
CAMPO=DESART,AUXILIAR,NOENTER,TOOLTIP("Designación del artículo")
CAMPO=CANTIDAD,TOOLTIP("Cantidad en unidades host"),CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=UNIEMB,TOOLTIP("Unidades por embalaje en unidades host"),CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=EMBCONT,TOOLTIP("Embalajes por contenedor")
CAMPO=TIPOEMBA,TOOLTIP("Tipo de embalaje"),POSTCHANGE=FDESIGNACION("CSELTIPOEMBA","No existe el tipo de embalaje"),
                CONTEXTUAL=FEJECUTAFORM("VDTIPOEMBA","S","","","TIPOEMBA=:TIPOEMBA","Selección de tipo de embalaje","S") 
CAMPO=BLOQUEOSORI,TOOLTIP("Bloqueo de la mercancia"),POSTCHANGE=FDESIGNACION("-CVERBLOQUEOORI",":V10ERROR")
CAMPO=BLOQUEOSDEST,TOOLTIP("Bloqueo de la mercancia"),POSTCHANGE=FDESIGNACION("-CVERBLOQUEODEST",":V10ERROR")
CAMPO=CODCONCE
CAMPO=CODOPEINS
CAMPO=FECINS
CAMPO=HORAINS
CAMPO=CODOPEEJEMOV
CAMPO=FECINIMOV
CAMPO=HORAINIMOV
CAMPO=FECFINMOV
CAMPO=HORAFINMOV

CURSOR=CSELDESART SELECT DESART FROM VDARTIC WHERE CODART=:CODART;

CURSOR=CSELCODLOT SELECT :CODLOT FROM VDLOTES WHERE CODART=:CODART AND CODLOT=:CODLOT
                   UNION
                  SELECT '' CODLOT FROM DUAL WHERE :CODLOT IS NULL;

CURSOR=CSELTIPOEMBA SELECT :TIPOEMBA FROM VDTIPOEMBA WHERE TIPOEMBA=:TIPOEMBA
                   UNION
                  SELECT '' TIPOEMBA FROM DUAL WHERE :TIPOEMBA IS NULL;

CURSOR=CVERBLOQUEOORI SELECT VDART.VALIDABLOQUEO(:BLOQUEOSORI) V10ERROR FROM DUAL 
                       WHERE VDART.VALIDABLOQUEO(:BLOQUEOSORI) IS NOT NULL AND :BLOQUEOSORI IS NOT NULL;
                       
CURSOR=CVERBLOQUEODEST SELECT VDART.VALIDABLOQUEO(:BLOQUEOSDEST) V10ERROR FROM DUAL 
                        WHERE VDART.VALIDABLOQUEO(:BLOQUEOSDEST) IS NOT NULL AND :BLOQUEOSDEST IS NOT NULL;


