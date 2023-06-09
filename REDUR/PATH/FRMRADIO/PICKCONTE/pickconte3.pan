#
MOVIMIENTO DE CONTENEDOR
_10_______ _10_______  
ETIQUETADO DE PALLETS
SIN MATRICULA

UBICACION: _________
ARTICULO:  _20________________
_40____________________________
_40____________________________

UBICACION: _________

MATRICULA: ________

ARTICULO:  ________________________________________

|



POSTQUERY=FEJECUTA("CSELLONGERROR","\n ERROR\n OBTENIENDO PROPIEDAD",
                   "CVERUBIORI","\n UBICACION INCORRECTA\n LEIDO :CODUBIORILEIDOF\n ESPERADO :CODUBIORI",
                   "CINSCNT","\n ERROR INSERTANDO \n PALLET NUEVO",
                   "CUPDSTKCNT","\n ERROR ACTUALIZANDO \n STOCK",
                   "CUPDMOVCNT","\n ERROR ACTUALIZANDO \n MOVIMIENTO",
                   "CUPDUBICNT","\n ERROR ACTUALIZANDO \n UBICACION",
                   "CDELCNTSINETIQ","\n ERROR BORRANDO \n CONTENEDOR SIN ETIQUETA",
                   FIF(FRECOGESTKSYNC("ACTSTKORIGEN",":CODMOV",":CODRECURSO"),
                       FSUCCESS,
                       FEJECUTA("+CDIVIDEERROR","\n ERROR\nDIVIDIENDO MENSAJE",FFAILURE,":MSGERROR")),"",
                   FCOMMIT,"\n ERROR\n HACIENDO COMMIT.",
                   FPOSICIONABLOQUE("PICKCONTE2.PAN"),"\n ERROR \n AL CARGAR PICKCONTE2.PAN")


# DEFINICION DE CAMPOS
CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=TAREA,VIRTUAL,OCULTO
CAMPO=CODMOV,VIRTUAL,OCULTO
CAMPO=CODUBIORI,VIRTUAL,OCULTO
CAMPO=PINTAUBI,VIRTUAL,NOENTER
CAMPO=CODART,VIRTUAL,NOENTER
CAMPO=DESART1,VIRTUAL,NOENTER
CAMPO=DESART2,VIRTUAL,NOENTER
CAMPO=UNIEMB,VIRTUAL,OCULTO
CAMPO=NCAJAS,VIRTUAL,OCULTO
CAMPO=UNIDSUELTAS,VIRTUAL,OCULTO
CAMPO=CODMATORI,VIRTUAL,OCULTO
CAMPO=CODUBIORILEIDO,SCAN,POSTCHANGE=FDESIGNACION("-CSELUBINULL","\n UBICACION INCORRECTA",FFUERZASCAN("UBI"),"\n ERROR\n DEBE LEER\n LA UBICACION")
CAMPO=CODUBIORILEIDOF,OCULTO,"_12_"
CAMPO=PROFUNDIDAD,OCULTO,"_",POSTCHANGE=FDESIGNACION("CVERUBIORI","\n UBICACION INCORRECTA\n LEIDO :CODUBIORILEIDOF\n ESPERADO :CODUBIORI")
CAMPO=CODMATORILEIDO,SCAN,POSTCHANGE=FEJECUTA("-CSELMATNULL","\n MATRICULA INCORRECTA","-CSELUBICNT","\n MATRICULA OCUPADA \n EN UBICACION :CODUBICNT")
CAMPO=CODARTLEIDO,SCAN,AUTOENTER,POSTCHANGE=FEJECUTA(FFUERZASCAN("ART"),"\n DEBE LEER ARTICULO",
                                                     "+CBORRAART","",
                                                     FLEEARTICULO("CODARTLEIDO","CODARTT",":CODART")," ERROR \n NO ENCUENTRO \n ARTICULO",
                                                     "CESNULOEAN","\n DEBE LEER ARTICULO",
                                                     "CVERIFART","\n ARTICULO INCORRECTO")                                                     
CAMPO=CODARTT,OCULTO,"______________"
CAMPO=CODAREA,VIRTUAL,OCULTO
CAMPO=CODUBICNT,OCULTO,"_18_"
CAMPO=LONGERROR,OCULTO,"@@@"


# DEFINICION DE CURSORES

CURSOR=CVERUBIORI SELECT :CODUBIORILEIDOF FROM DUAL WHERE :CODUBIORILEIDOF=:CODUBIORI;
        

CURSOR=CSELUBINULL SELECT :CODUBIORILEIDO FROM DUAL WHERE :CODUBIORILEIDO IS NULL;


CURSOR=CBORRAART SELECT '' CODARTT FROM DUAL;

CURSOR=CESNULOEAN SELECT :CODARTLEIDO FROM DUAL WHERE :CODARTLEIDO IS NOT NULL;

CURSOR=CVERIFART SELECT :CODART CODART FROM DUAL WHERE NVL(:CODARTT,:CODARTLEIDO)=:CODART;

CURSOR=CSELUBICNT SELECT CODUBI CODUBICNT FROM VDCONTE WHERE CODMAT=:CODMATORILEIDO;

CURSOR=CINSCNT DECLARE
                 MITIPOCONTE VDARTIC.TIPOCONTEDEF%TYPE;
                 MIALTPALET VDCONTE.ALTURACONTE%TYPE;
               BEGIN
                 SELECT TIPOCONTEDEF INTO MITIPOCONTE
                   FROM VDARTIC
                  WHERE CODART=:CODART;
                  
                 SELECT VDCNT.ALTURASTK(:CODART,(:NCAJAS*:UNIEMB)+:UNIDSUELTAS,:UNIEMB,MITIPOCONTE) INTO MIALTPALET
                   FROM DUAL;
                 BEGIN
                   INSERT INTO VDCONTE (CODMAT, TIPOCONTE, CNTSSCC, CODUBI, POSCONTE, ALTURACONTE, 
                                        STATUS, FECENTRADA, HORAENTRADA, VDEXTRA, CODCOMEN, CODOPEMODIF, FECMODIF, HORAMODIF)
                               VALUES  (:CODMATORILEIDO, 'NORMAL', NULL, NULL, 1, MIALTPALET, 
                                        0, VD.FECHASYS, VD.HORASYS, NULL, 0, VDUSER.GETUSER, VD.FECHASYS, VD.HORASYS);
                   EXCEPTION WHEN OTHERS THEN NULL;
                 END;
               END;@

CURSOR=CUPDSTKCNT UPDATE VDSTOCK SET CODMAT=:CODMATORILEIDO WHERE CODMAT=:CODMATORI;

CURSOR=CUPDMOVCNT UPDATE VDMOVIM SET CODMATORI=:CODMATORILEIDO,CODMATDEST=:CODMATORILEIDO WHERE CODMATORI=:CODMATORI;

CURSOR=CUPDUBICNT UPDATE VDCONTE SET CODUBI=:CODUBIORI WHERE CODMAT=:CODMATORILEIDO;

CURSOR=CSELMATNULL SELECT :CODMATORILEIDO
                     FROM DUAL
                    WHERE :CODMATORILEIDO IS NULL;

CURSOR=CDELCNTSINETIQ DELETE VDCONTE WHERE CODMAT=:CODMATORI;                    

CURSOR=CDIVIDEERROR BEGIN :MSGERROR:=VD.DIVERRORRADIO(:V10ERROR,:LONGERROR);
                    END;@

CURSOR=CSELLONGERROR SELECT VD.GETPROP('LONGITUDERROR') LONGERROR FROM DUAL;

                    
