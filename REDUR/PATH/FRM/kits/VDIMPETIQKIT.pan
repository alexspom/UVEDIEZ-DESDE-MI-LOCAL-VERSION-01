######################################################################
#MOdulo: VDORDKITCAB.PAN
#Funcionalidad : Consulta de cabeceras de ordenes de producción procedentes del sistema superior
#Autor: DGB      
#Fecha: 28-03-2019
######################################################################
# HistOrico de cambios:
#
#
#
REIMPRIMIR ETIQUETAS
  Etiqueta pequeña             Etiqueta grande             Etiqueta de kit
       @@@@@                       @@@@@                        @@@@@
|

NOQUERY

CAMPO=CODORDKIT,VIRTUAL,OCULTO
CAMPO=CODART,VIRTUAL,OCULTO
CAMPO=RESULTADO,AUXILIAR,OCULTO,"@"
CAMPO=ETIQPEQ,AUXILIAR,TITULO("ETIQUETA PEQUEÑA"),TOOLTIP("Numero de etiquetas pequeñas a imprimir")
CAMPO=ETIQGRANDE,AUXILIAR,TITULO("ETIQUETA GRANDE"),TOOLTIP("Numero de etiquetas grandes a imprimir")
CAMPO=ETIQKIT,AUXILIAR,TITULO("ETIQUETA DE KIT"),TOOLTIP("Numero de etiquetas de kit a imprimir")

CURSOR=CIMPRIMEETIQ BEGIN 				   
                   VDIMPRE.SPOOL(VDUSER.GETHOSTNAME,'ETIQ','','','VDKITGRANDE.GEN;VDKITS.VSQ;CSELKIT','CODART='''||:CODART||'''',:ETIQGRANDE,0,'',:RESULTADO);
				   VDIMPRE.SPOOL(VDUSER.GETHOSTNAME,'ETIQ','','','VDKITPEQUENA.GEN;VDKITS.VSQ;CSELKIT','CODART='''||:CODART||'''',:ETIQPEQ,0,'',:RESULTADO); 
				   VDIMPRE.SPOOL(VDUSER.GETHOSTNAME,'ETIQ','','','VDORDKITCONTE.GEN;VDKITS.VSQ;CSELORDKIT','CODORDKIT='''||:CODORDKIT||'''',:ETIQKIT,0,'',:RESULTADO);
				   END;@
				   
#Imprimir etiquetas
TECLA=SF7,FEJECUTA("CIMPRIMEETIQ","ERROR AL IMPRIMIR ETIQUETAS", FCOMMIT,"")
				   
BOTON=B20,1015,100,70,70,"P",miimprimir.png,SF7,"Impresión de etiquetas ",INCLUDECSS="background-color: transparent;border-width:0px"