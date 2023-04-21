# M�dulo   : VDLEERFMD.PAN
# Funci�n  : LEER TODOS LOS NUMEROS DE SERIE SEG�N LA CANTIDAD DE ARTICULOS QUE SE RECIBEN
#            
# Creaci�n : 12/07/2018
# Autor    : DFL
###########################################
# Hist�rico de cambios:
#
# Autor    : MJGG
# Fecha    : 17-08-2018
# Cambio   : M001 - INCLUIR CAMINO TRAS LECTURA DE FMD. YA NO VA A VDFMDMATRICULA.PAN.
#
# Autor    : MJGG
# Fecha    : 11-09-2018
# Cambio   : M002 - INCLUIR COMPROBACI�N DEL NUMERO DE SERIE: CURSOR "CVERIFNUMSERIE".
# 
NUMEROS DE SERIES
 _10_______ _10_______
LEER NUMEROS DE SERIE DEL ART.
_200__________________________

 LEIDOS #### DE #### 

 NUM. SERIES
 _240______________________________________________________________________________________

|

PREQUERY=FEJECUTA("+CINICAMPOS","","+CCUANTOS","")

POSTQUERY=FEJECUTA(FIF("CSELNOTNULL",FCARGAFORM(""),FSUCCESS),"",
                    "-CVERSIEXISTE","ERROR\nNUM.SERIE YA LEIDO",
					"CVERIFNUMSERIE","ERROR\nEL NUMERO DE SERIE\nNO SE CORRESPONDE CON\nEL ARTICULO Y LOTE",
				    "CCONSULTAFMD","ERROR\nVERIFICANDO/INSERTANDO\nNUM. SERIE",
                    "+CACTLEIDOS","",
                    FIF("CVERSALIR",FEJECUTA("CSELCODARTEAN","\nERROR,\nEL EAN LEIDO NO EXISTE",
                                             "CCHECKLOTEYART","\nERROR,\nEL ARTICULO Y LOTE\nNO COINCIDE",         
                                             FIF(FEJECUTAMOVSTSYNC("ACTSTKORIGEN2","ACTSTKDESTINO",":CODMOV",":CODRECURSO","2300","3100"),
                                                 FSUCCESS,
                                                 FEJECUTA("CDIVIDEERROR","ERROR\nDIVIDIENDO ERROR MOV",FFAILURE,":MSGERROR")),"",                                                
                                             FCOMMIT,"ERROR\n HACIENDO COMMIT",
                                             FPOSICIONABLOQUE("VDPICKUNIOK.PAN"),"ERROR\n CARGANDO BLOQUE\nVDPICKUNIOK.PAN"),
								    FEJECUTA("+CINICAMPOS","","+CCUANTOS","")
                        ),""
			       )



CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=DESART1,NOENTER,VIRTUAL
CAMPO=CANTIDADLEIDA,NOENTER
CAMPO=CANTIDAD,VIRTUAL,NOENTER
CAMPO=CODBARRAS,SCAN,AUTOENTER

CAMPO=RET,AUXILIAR,OCULTO,"#L#####"
CAMPO=CODART,VIRTUAL,OCULTO
CAMPO=CODLOT,VIRTUAL,OCULTO
CAMPO=MSGERROR,OCULTO, "_20"
CAMPO=LONGERROR,OCULTO,"@@@"

#M001 INICIO
CAMPO=CODBULTO,VIRTUAL,OCULTO
CAMPO=CODMOV,VIRTUAL,OCULTO
#M001 FIN
CAMPO=CODEAN,AUXILIAR,OCULTO,"_14_"
CAMPO=NVMSID,AUXILIAR,OCULTO,"_240_"     
CAMPO=NVMSSTATUS,AUXILIAR,OCULTO,"_240_" 
CAMPO=NVMSREASON,AUXILIAR,OCULTO,"_240_" 
CAMPO=NVMSRET,AUXILIAR,OCULTO,"_240_"    
CAMPO=NVMSRETDESC,AUXILIAR,OCULTO,"_240_"  


CURSOR=CSELNOTNULL SELECT :CODBARRAS FROM DUAL  WHERE :CODBARRAS IS NULL;

CURSOR=CSELNULL SELECT :CODBARRAS FROM DUAL WHERE :CODBARRAS IS NULL;

CURSOR=CINICAMPOS SELECT CODEAN,NULL CODBARRAS FROM VDARTIC WHERE CODART=:CODART;

CURSOR=CCUANTOS SELECT COUNT(*) CANTIDADLEIDA FROM VDNUMSERIESFMD WHERE CODART=:CODART AND CODLOT =:CODLOT AND CODMOV = :CODMOV;

CURSOR=CCONSULTAFMD DECLARE
                      VSTATUS NUMBER := 100;
                    BEGIN      
					   IF VDFMD.INSERTANUMSERIEVERIF(VDEAN.VALOR(:CODBARRAS,'21'),:CODART, :CODLOT,:CODMOV,VSTATUS,:CODBULTO) <> 0 THEN RAISE NO_DATA_FOUND; END IF;					                    
                       COMMIT;
                    END;@

CURSOR=CACTLEIDOS SELECT :CANTIDADLEIDA + 1 CANTIDADLEIDA, NULL CODBARRAS FROM DUAL;

CURSOR=CVERSALIR SELECT :CODART FROM DUAL WHERE :CANTIDADLEIDA = :CANTIDAD; 

CURSOR=CSELLONGERROR SELECT VD.GETPROP('LONGITUDERROR') LONGERROR FROM DUAL;

CURSOR=CDIVIDEERROR BEGIN :MSGERROR:=VD.DIVERRORRADIO(:V10ERROR,:LONGERROR);
                    END;@

CURSOR=CSELCODARTEAN SELECT CODART CODART
                       FROM VDARTIC
                      WHERE CODEAN=:CODEAN OR CODART=:CODEAN;
					  
CURSOR=CCHECKLOTEYART SELECT :CODART 
                        FROM DUAL 
                       WHERE :CODART = :CODART AND
                             NVL(:CODLOT,'0') = DECODE(:CODLOT,NULL,NVL(:CODLOT,'0'),:CODLOT); 					  
					  
CURSOR=CVERSIEXISTE SELECT :CODART FROM VDNUMSERIESFMD WHERE CODART=:CODART AND CODLOT =:CODLOT AND NUMEROSERIE=VDEAN.VALOR(:CODBARRAS,'21') AND CODMOV = :CODMOV AND CODBULTO=:CODBULTO AND ROWNUM=1; 

#M002 INICIO
CURSOR=CVERIFNUMSERIE SELECT :CODBARRAS FROM DUAL WHERE VDEAN.VALOR(:CODBARRAS,'01')=:CODEAN AND VDEAN.VALOR(:CODBARRAS,'10')=:CODLOT;
#M002 FIN