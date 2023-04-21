#*****************************************************************
#Módulo: VDRECSTOCK.PAN
#Funcionalidad : 
#Autor: ICC      
#Fecha: 12-02-2008
#*****************************************************************
#* Histórico de cambios
#* ====================
#
STOCK ASOCIADOS A LA RECEPCION POR MATRICULA

 Artículo           Lote             Caducidad Cantidad recep. Bloqueos   T. Embalaje Unidad/embalaje Capacidad PVP unidad
 _40_______________ _40_____________ _8______  ############### _10_______ _10_______  ############### #####     #########.####
|
SOLOQUERY
SELECT=SELECT STK.CODART, STK.CODLOT, STK.BLOQUEOS, STK.TIPOEMBA, STK.UNIEMB, STK.EMBCONT, 
              NVL(ART.DECIMALES,VD.GETPROP('DECIMALES')) PRECIOUNI__DECIMALES, STK.PRECIOUNI,
              SUM(STK.CANTIDAD) CANTIDAD
         FROM VDSTOCK STK, VDARTIC ART
        WHERE STK.CODRECEP = :CODRECEP
          AND STK.CODMAT   = :CODMAT
          AND STK.CODART   = ART.CODART;
GROUPBY=STK.CODART, STK.CODLOT, STK.BLOQUEOS, STK.TIPOEMBA, STK.UNIEMB, STK.EMBCONT, ART.DECIMALES, STK.PRECIOUNI;
ORDERBY=CODART, CODLOT, BLOQUEOS;



POSTQUERY=FEJECUTA("CVALORESORI","")

CAMPO=CODDIV,VIRTUAL,AUXILIAR,OCULTO
CAMPO=CODMAT,VIRTUAL,AUXILIAR,OCULTO,TOOLTIP("Código de la matrícula en origen")
CAMPO=CODRECEP,VIRTUAL,AUXILIAR,OCULTO,TOOLTIP("Movimiento por el que se hizo recepción del producto en el almacén")
CAMPO=CODORDREC,VIRTUAL,AUXILIAR,OCULTO
CAMPO=TIPORDREC,VIRTUAL,AUXILIAR,OCULTO
CAMPO=CODART,AUXILIAR,TOOLTIP("Código del artículo"),NOUPDATE
CAMPO=CODLOT,NOUPDATE,AUXILIAR,TOOLTIP("Lote"), POSTCHANGE=FEJECUTA("+CCADUCI",""),TITULO("Lote")
CAMPO=CADUCI,NOUPDATE,AUXILIAR,TOOLTIP("Caducidad del Lote"),TITULO("Caducidad"),WLONX=30
CAMPO=CANTIDAD,AUXILIAR,TOOLTIP("Cantidad de la línea de movimiento"),TITULO("Cantidad recep.")
CAMPO=BLOQUEOS,NOUPDATE,AUXILIAR,TOOLTIP("Calificación de stock de la mercancia"),TITULO("Bloqueos")
CAMPO=TIPOEMBA,NOUPDATE,AUXILIAR,TOOLTIP("Tipo de embalaje"),WLONX=30,
               POSTCHANGE=FEJECUTA("CVALTIPOEMBA","ERROR, TIPO DE EMBALAJE :TIPOEMBA NO EXISTE"),
               TITULO("T.Embalaje")
CAMPO=UNIEMB,NOUPDATE,AUXILIAR,TOOLTIP("Unidades por embalaje"),TITULO("Uni/Emb")
CAMPO=EMBCONT,NOUPDATE,AUXILIAR,TOOLTIP("Embalajes por contenedor, número de embalajes que cogerían en un contenedor completo"),TITULO("Capacidad"),WLONX=37
CAMPO=PRECIOUNI,NOUPDATE,AUXILIAR,TOOLTIP("Precio de cada unidad"),TITULO("PVP Unidad")
CAMPO=CODUBI,AUXILIAR,OCULTO,"_20_________"
CAMPO=MSGERROR,AUXILIAR,OCULTO,"_100___"
CAMPO=CANTIDADORI,AUXILIAR,OCULTO,"###############"
CAMPO=BLOQUEOSORI,AUXILIAR,OCULTO,"_10_______"
CAMPO=PRECIOUNIORI,AUXILIAR,OCULTO,"############"
CAMPO=CODMOV,AUXILIAR,OCULTO,"@L@@@@@@@"
CAMPO=DUMMY,OCULTO,"#"
CAMPO=ORDENSTK,   OCULTO,AUXILIAR,"@L@@@@@@@"
CAMPO=NUMEROSERIE,OCULTO,AUXILIAR,"_60_" 
CAMPO=BULTO,      OCULTO,AUXILIAR,"_18_"
CAMPO=MARCASTK,   OCULTO,AUXILIAR,"_60_"
CAMPO=PESOUNI,    OCULTO,AUXILIAR,"@L@@@@@@@@@@"
CAMPO=OBS,OCULTO,AUXILIAR,"_100_" 
CAMPO=CODLOTORI   ,OCULTO,AUXILIAR,"_20_" 
CAMPO=UNIEMBORI   ,OCULTO,AUXILIAR,"###############" 
CAMPO=EMBCONTORI  ,OCULTO,AUXILIAR,"###############" 
CAMPO=TIPOEMBAORI ,OCULTO,AUXILIAR,"_10_" 


CURSOR=CVALORESORI SELECT :CANTIDAD CANTIDADORI, :BLOQUEOS BLOQUEOSORI, :PRECIOUNI PRECIOUNIORI,
                          :CODLOT CODLOTORI, :UNIEMB UNIEMBORI, :TIPOEMBA TIPOEMBAORI, :EMBCONT EMBCONTORI
                     FROM DUAL;

CURSOR=CCADUCI SELECT CADUCI
                 FROM VDLOTES
                WHERE CODLOT = :CODLOT
                  AND CODART = :CODART;

CURSOR=CVALPVP SELECT VDRECEP.BLOQPVP (:BLOQUEOSORI, :CODART, :PRECIOUNI) BLOQUEOS
                 FROM DUAL
                WHERE :PRECIOUNI != :PRECIOUNIORI;

CURSOR=CVALTIPOEMBA SELECT 1 DUMMY
                      FROM VDTIPOEMBA
                     WHERE TIPOEMBA = :TIPOEMBA;

CURSOR=CVALCANTIDAD1 SELECT 1 DUMMY
                      FROM DUAL
                     WHERE :CANTIDAD > :CANTIDADORI
                       AND :CODORDREC IS NOT NULL;

CURSOR=CVALCANTIDAD2 SELECT 1 DUMMY
                       FROM DUAL
                      WHERE VDRECEP.CANTPDTE(:CODORDREC, :CODART, :CODDIV, :CODLOT,0,'S') > (:CANTIDADORI - :CANTIDAD);

#Valida el lote y la caducidad, y lo crea si no existe y es permitido por el tipo de recepción.
CURSOR=CVALLOTE BEGIN VDRECEP.VALIDALOTE (:CODART, :CODLOT, :CADUCI, :TIPORDREC, 'S', 'N', :MSGERROR);
                END;@

CURSOR=CVALBLOQUEOS SELECT VDUSER.BLOQUEOSPRIV (:BLOQUEOSORI, :BLOQUEOS) DUMMY
                      FROM DUAL
                     WHERE VDUSER.BLOQUEOSPRIV (:BLOQUEOSORI, :BLOQUEOS) !=0;

CURSOR=CGUARDABLOQ SELECT :MSGERROR BLOQUEOS
                     FROM DUAL
                    WHERE VD.ISNUMBER(SUBSTR(:MSGERROR,1,1)) = 0;
                    
CURSOR=CCODUBI SELECT CODUBI
                 FROM VDCONTE
                WHERE CODMAT = :CODMAT;
  
CURSOR=CSELTCAMBIO SELECT 1 DUMMY
                     FROM DUAL
                    WHERE :CANTIDADORI != :CANTIDAD;

CURSOR=CSELTCAMBIO2 SELECT 1 DUMMY
                      FROM DUAL
                     WHERE :CODLOT    = :CODLOTORI
                        OR :UNIEMB    = :UNIEMBORI
                        OR :EMBCONT   = :EMBCONTORI
                        OR :TIPOEMBA  = :TIPOEMBAORI
                        OR :PRECIOUNI = :PRECIOUNIORI;


CURSOR=CVERERROR SELECT 1 DUMMY
                   FROM DUAL
                  WHERE :MSGERROR IS NOT NULL;

CURSOR=CVERERROR2 SELECT 1 DUMMY
                    FROM DUAL
                   WHERE :CODMOV != 0;

CURSOR=CSELSTK SELECT ORDENSTK, NUMEROSERIE, BULTO, MARCASTK, PESOUNI
                 FROM VDSTOCK
                WHERE CODMAT = :CODMAT;
                
CURSOR=CACTCANTIDAD DECLARE
                      RET NUMBER;
                    BEGIN
                      RET:=VDRECEP.CORRIGEMATRICULAART(:CODMAT,:ORDENSTK,:CANTIDAD-:CANTIDADORI);
                      IF RET!=0 THEN RAISE NO_DATA_FOUND;
                       END IF;
                    END;@

TECLA=F12,FEJECUTA(FIF("CVALCANTIDAD1",FEJECUTA("CVALCANTIDAD2","CANTIDAD SUPERA LA CANTIDAD\nPENDIENTE DE RECEPCIONAR PARA LA ORDEN :CODORDREC")),"",
                   "CVALLOTE","ERROR EN PL DE VALIDACION DEL LOTE",
                  "-CVERERROR","ERROR, :MSGERROR",
                   "-CVALBLOQUEOS","ERROR EL OPERARIO :CODOPE\nNO TIENE SUFICIENTES PRIVILEGIOS\n PARA ACTUALIZAR LA POSICION :DUMMY",
                   "+CVALPVP","",
                   "CCODUBI", "NO EXISTE EL PALET :CODMAT",
                   FIF("CSELTCAMBIO",FEJECUTA("CSELSTK","NO HAY STOCK PARA EL PALET CON MATRICULA :CODMAT",
                                              "CACTCANTIDAD","ERROR ACTUALIZANDO CANTIDAD EN STOCK")),"",
                   FIF("-CSELTCAMBIO2",FEJECUTA("CSELSTK","NO HAY STOCK PARA EL PALET CON MATRICULA :CODMAT",
                                               FWHILE(FERRORCURSOR("CSELSTK"),
                                                      FEJECUTA(FTRANSFORMASTK(":CODMAT",":ORDENSTK","1",":CODART","1",":CODLOT","1",":NUMEROSERIE","1",
                                                                              ":BULTO","1",":MARCASTK","1",":CODRECEP","1",":UNIEMB","1",":EMBCONT","1",
                                                                              ":TIPOEMBA","1",":PRECIOUNI","1",":PESOUNI","1","OBS"), "\n ERROR\n\n :OBS\n:V10ERROR",
                                                               +FFETCHCURSOR("CSELSTK"),"ERROR EN FETCH")),"ERROR EN FWHILE")),"",
                   FCOMMIT,"",
                   FFAILURE,"MODIFICADO",
                   FPULSATECLAS("F3","F2"))                
