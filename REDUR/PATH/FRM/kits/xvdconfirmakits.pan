###################################################################
#M?dulo: XVDCONFIRMAKITS.PAN
#Funcionalidad : SELECCION DE ORDEN PARA CONFIRMAR SUS BULTOS
#Autor: DGB      
#Fecha: 02-04-2019
###################################################################
# Hist?rico de cambios:
#
#
#
CONFIRMACION DE BULTOS DE KITS


 Orden            Arti�culo        LOTE        Cajas fabricadas  Cajas a confirmar C?digo de lote de proveedor Finalizar S/N 
 _15____________  _40__________   _15____________   @L@@@                 @L@@@            _40___________________           _    
 
                                                                                                                                 |
																																						   
PQUERY

SOLOQUERY

PREBLOQUE=FPREGUNTAR("0")

SELECT=SELECT OKC.CODORDKIT, OKC.CODART, OKC.CODLOT, COUNT(*) NUMBULTOS, COUNT(*) CANTIDADSEL,'N' SWTFIN, OKC.CODPROVE, '' CODLOTPROV, MIN(PEC.SEQPED) UNIEMB, PEC.CODDIV
                  FROM (SELECT DISTINCT CODORDKIT, CODART, CODLOT, CODPROVE FROM VDORDKITCAB) OKC,
               VDBULTOCAB BUC,
             VDPEDIDOCAB PEC,
             (SELECT CODBULTO,COUNT(*) CONTADOR1 FROM VDBULTOLIN GROUP BY CODBULTO) LINBUL,
             (SELECT CODBULTO,COUNT(*) CONTADOR2 FROM VDMOVIM MOV2,VDBULTOLIN BUL2 WHERE BUL2.CODMOV=MOV2.CODMOV AND MOV2.STATUS=VDST.FMOVPDTERECOGE GROUP BY CODBULTO) CONTMOV
          WHERE BUC.CODPED=PEC.CODPED
          AND OKC.CODORDKIT = PEC.PEDIDOHOST
          AND PEC.PEDIDOCLIENTE='KIT'
          AND PEC.CODAGE='KIT'
          AND PEC.CODPED LIKE 'PRO%'
          AND PEC.TIPOPEDIDO='05'
          AND PEC.TIPODEMANDA='PEDIDOKIT'
          AND BUC.STATUS=VDST.FBUCRESERVADO
          AND PEC.STATUS=VDST.FPECPREPARANDO
          AND LINBUL.CODBULTO=BUC.CODBULTO
          AND CONTMOV.CODBULTO=BUC.CODBULTO
          AND LINBUL.CONTADOR1=CONTMOV.CONTADOR2
          GROUP BY OKC.CODORDKIT, OKC.CODART, OKC.CODLOT, OKC.CODPROVE, PEC.CODDIV;
				  
WLONX=1000
WLONY=528

PREUPDATE=FEJECUTA("+CCOMPRUEBALOTEPROVE","Debe introducir el codigo de lote de proveedor",
                   "CSWTFIN","DEBE MARCAR EL CAMPO LANZAR AL VALOR S.",
                   "CSELCODMAT","ERROR OBTENIENDO\nLA MATRICULA",
                   "CSELDESTINO","ERROR OBTENIENDO DESTINOS",
				   "CSELFECFAB","ERROR OBTENIENDO FECHA DE FABRIACION",
                   "CUPDSTATUSBULTO","ERROR ACTUALIZANDO UN TOTAL DE :CANTIDADIMP BULTOS\nASOCIADOS A KIT DE ARTICULO :CODART Y LOTE :CODLOT.\nCODIGO DE ORDEN :CODORDKIT.",
				   "CINSLOTE","ERROR INSERTANDO LOTE",
				   "CFINMOV","ERROR FINALIZANDO MOVIMIENTOS",
				   "CINITCODMOV","ERROR INICIALIZANDO\nNEWCODMOV",
				   "CSELEMBCONT","ERROR OBTENIENDO EMBALAJES POR CONTENEDOR",
				   "CCREAMOV","ERROR AL\nCREAR\nMOVIMIENTO",
				   FCOMMIT,"",
				   FEJECUTAMOVSYNC("ACTSTKORIGEN","ACTSTKDESTINO",":NEWCODMOV","PRUEBASOFI"),"ERROR EJECUTANDO MOVIMIENTO :NEWCODMOV",
                   FIF("CSELRET",FEJECUTA(FCOMMIT,""),
				                FEJECUTA(FROLLBACK,"",
								         %FFAILURE,"ERROR EJECUTANDO MOVIMIENTO\nDE CREACION\nDE KIT :CODORDKIT")))
				   
POSTCOMMIT=FEJECUTA(%FFAILURE,"Confirmacion relizada correctamente",
                   FPULSATECLAS("F3","F2"),"")

CAMPO=CODORDKIT,AUXILIAR,NOENTER,TOOLTIP("C?digo de la orden de fabricaci?n"),TITULO("Orden")
CAMPO=CODART,AUXILIAR,NOENTER,TOOLTIP("C?digo del artículo"),TITULO("Art�culo")
CAMPO=CODLOT,AUXILIAR,TOOLTIP("C?digo de lote. Si el lote es SL se generar? autom?ticamente como corresponda al artículo"),TITULO("CODLOT")
CAMPO=NUMBULTOS,AUXILIAR,NOENTER,TOOLTIP("Número de cajas de kits fabricadas"),TITULO("Kits fabricados"),WLONX=60
CAMPO=CANTIDADSEL,AUXILIAR,TOOLTIP("Total de cajas completas de kits a confirmar"),TITULO("Confirmar")
CAMPO=CODLOTPROV,AUXILIAR,TOOLTIP("Codigo de lote de proveedor"),TITULO("Lote proveedor")
CAMPO=SWTFIN,AUXILIAR,TOOLTIP("Switch de lanzamiento"),TITULO("Finalizar S/N"),POSTCHANGE=FVERIFICA("SN","Debe introducir S(i) o N(o)"),WLONX=80
CAMPO=CODMAT,AUXILIAR,OCULTO,"_18_"
CAMPO=CODMATDEST,AUXILIAR,OCULTO,"_18_"
CAMPO=CODUBIDEST,AUXILIAR,OCULTO,"_18_"
CAMPO=NEWCODMOV,AUXILIAR,OCULTO,"@L@@@@@@@"
CAMPO=RET,AUXILIAR,OCULTO,"@L@@"
CAMPO=MSGERROR,AUXILIAR,OCULTO,"_100_"
CAMPO=EMBCONT,AUXILIAR,OCULTO,"@L@@@@@@@@@@@@@"
CAMPO=FORMATOLOTE,AUXILIAR,OCULTO,"_"
CAMPO=FECFABRICA,AUXILIAR,OCULTO,"_8_"
CAMPO=CODPROVE,AUXILIAR,OCULTO,"_20_"
CAMPO=UNIEMB,AUXILIAR,OCULTO,"@L@@@@@@@@@@@@@"
CAMPO=CODDIV,AUXILIAR,OCULTO,"_8_"

CURSOR=CSWTFIN SELECT :SWTFIN FROM DUAL WHERE :SWTFIN='S';

CURSOR=CSELCODMAT SELECT CODMAT 
					FROM VDCONTE CNT, VDUBICA UBI
					WHERE CNT.CODUBI = UBI.CODUBI
					AND UBI.CODAREA = RDRPKG.DAMEAREA(:CODDIV,'KITTING')
					AND UBI.CODUBI LIKE 'FUENTEKITS%';

CURSOR=CSELDESTINO SELECT CNT.CODMAT CODMATDEST, UBI.CODUBI CODUBIDEST
					FROM VDCONTE CNT, VDUBICA UBI
					WHERE CNT.CODUBI = UBI.CODUBI
					AND UBI.CODAREA = RDRPKG.DAMEAREA(:CODDIV,'KITTING')
					AND UBI.CODUBI LIKE 'NUEVOSKITS%';
				   
CURSOR=CCOMPMOV SELECT :CODORDKIT FROM DUAL
                WHERE NOT EXISTS (SELECT MOV.STATUS FROM VDMOVIM MOV,VDBULTOLIN BUL,VDBULTOCAB BUC,VDPEDIDOCAB PEC
                          WHERE MOV.CODMOV=BUL.CODMOV
                          AND PEC.CODPED=BUC.CODPED
                          AND BUC.CODBULTO=BUL.CODBULTO
                          AND PEC.PEDIDOHOST=:CODORDKIT
						  AND PEC.CODDIV=:CODDIV
                          AND MOV.STATUS<VDST.FMOVPDTERECOGE);
				   
CURSOR=CFINMOV UPDATE VDMOVIM SET STATUS=VDST.FMOVRECODEPO
               WHERE CODMOV IN (SELECT BUL.CODMOV FROM VDBULTOLIN BUL,VDBULTOCAB BUC, VDPEDIDOCAB PEC 
			                    WHERE BUL.CODBULTO=BUC.CODBULTO 
								AND BUC.CODPED=PEC.CODPED
				                AND PEC.PEDIDOCLIENTE='KIT'
				                AND PEC.CODAGE='KIT'
				                AND PEC.CODPED LIKE 'PRO%'
				                AND PEC.TIPOPEDIDO='05'
				                AND BUC.STATUS=VDST.FBUCPDTESERVIR
				                AND PEC.STATUS=VDST.FPECPREPARANDO
				                AND PEC.PEDIDOHOST=:CODORDKIT
								AND PEC.CODDIV=:CODDIV) 
			   AND STATUS=VDST.FMOVPDTERECOGE;
			   
CURSOR=CCOMPLOTE SELECT :CODART 
                 FROM VDLOTES
                 WHERE CODART=:CODART
                 AND CODLOT=:CODLOT;

#Para Bolton:
#Si el kit esta compuesto por pegamentos (codclase in 'ZA00','ZA01','ZB00') se toma como fecha de fabricaci?n la m?s antigua de entre los pegamentos que tengan menor tiempo de duraci?n.
#Si el kit no esta compuesto por pegamentos (codclase distinto de Y) se toma como fecha de fabricaci?n la m?s antigua de entre los productos que tengan menor tiempo de duracion.
CURSOR=CSELFECFAB SELECT FECFABRICA FROM (

       SELECT MIN(FECFABRICA) FECFABRICA
       FROM VDLOTES LOT
       INNER JOIN VDSTOCK STK ON STK.CODART = LOT.CODART AND STK.CODLOT = LOT.CODLOT
       INNER JOIN VDCONTE CNT ON CNT.CODMAT = STK.CODMAT AND CNT.CODUBI = 'PREPKITS'
       INNER JOIN VDORDKITLIN OKL ON OKL.CODART = STK.CODART
       INNER JOIN VDCLASEARTIC CLA ON CLA.CODART = STK.CODART
       INNER JOIN VDARTIC ART ON ART.CODART = OKL.CODART AND ART.CODDIV = 'BOL' 
       WHERE  CLA.CODCLASE IN ('ZA00','ZA01','ZB00') AND CLA.CODCLASIF = 'BOLTON' AND OKL.CODORDKIT = :CODORDKIT
       AND ART.TCADUC = (SELECT MIN(ART.TCADUC) FROM VDARTIC ART, VDORDKITLIN OKL, VDCLASEARTIC CLA WHERE CLA.CODART = ART.CODART AND ART.CODART = OKL.CODART AND CLA.CODCLASE IN ('ZA00','ZA01','ZB00') AND CLA.CODCLASIF = 'BOLTON' AND OKL.CODORDKIT = :CODORDKIT)
       UNION ALL
       SELECT MIN(FECFABRICA) FECFABRICA
       FROM VDLOTES LOT
       INNER JOIN VDSTOCK STK ON STK.CODART = LOT.CODART AND STK.CODLOT = LOT.CODLOT
       INNER JOIN VDCONTE CNT ON CNT.CODMAT = STK.CODMAT AND CNT.CODUBI = 'PREPKITS'
       INNER JOIN VDORDKITLIN OKL ON OKL.CODART = STK.CODART
       INNER JOIN VDCLASEARTIC CLA ON CLA.CODART = STK.CODART
       INNER JOIN VDARTIC ART ON ART.CODART = OKL.CODART AND ART.CODDIV = 'BOL' 
       WHERE CLA.CODCLASE <> 'Y' AND CLA.CODCLASIF = 'FLAGPROMO' AND OKL.CODORDKIT = :CODORDKIT
       AND ART.TCADUC = (SELECT MIN(ART.TCADUC) FROM VDARTIC ART, VDORDKITLIN OKL, VDCLASEARTIC CLA WHERE CLA.CODART = ART.CODART AND ART.CODART = OKL.CODART AND CLA.CODCLASE <> 'Y' AND CLA.CODCLASIF = 'FLAGPROMO' AND OKL.CODORDKIT = :CODORDKIT)
       
     ) WHERE ((FECFABRICA IS NOT NULL AND :CODDIV = 'BOL') OR :CODDIV <> 'BOL') AND ROWNUM=1;

CURSOR=CINSLOTE DECLARE 
                   MICADUCI VDLOTES.CADUCI%TYPE;
				BEGIN 
				 IF :CODDIV = 'BOL' THEN
				 
					 IF :CODLOT = 'SL' THEN
						:CODLOT := NULL;
					 END IF;
					 VDRECEP.CREA_LOTE_BOLTON(:CODART,:CODLOT,MICADUCI,'', :FECFABRICA, :CODLOTPROV, '','');
					 UPDATE VDLOTES SET CODPROVE = :CODPROVE WHERE CODLOT = :CODLOT AND CODART = :CODART;
					 
					 UPDATE VDPEDIDOCAB SET VDEXTRA = :CODLOT WHERE CODPED IN (SELECT CODPED FROM
											   (SELECT PEC.CODPED
											   FROM VDPEDIDOCAB PEC,VDBULTOCAB BUC 
											   WHERE PEC.CODPED=BUC.CODPED
											   AND   PEC.SEQPED=BUC.SEQPED
											   AND   PEC.ANOPED=BUC.ANOPED
											   AND   PEC.CODDIV=BUC.CODDIV
											   AND   PEC.STATUS=VDST.FPECPREPARANDO
											   AND   BUC.STATUS=VDST.FBUCPDTESERVIR
											   AND   PEC.PEDIDOHOST=:CODORDKIT
											   ORDER BY CODBULTO));
				 END IF;
                END;@
				
CURSOR=CINITCODMOV SELECT 0 NEWCODMOV FROM DUAL;

CURSOR=CSELEMBCONT SELECT EMBCONT FROM VDARTIC WHERE CODART=:CODART;

CURSOR=CCOMPRUEBALOTEPROVE SELECT :CODLOTPROV FROM DUAL WHERE :CODLOTPROV IS NOT NULL;

CURSOR=CCREAMOV BEGIN
				VDMOV.CREAMOV(:NEWCODMOV,'REUBICAR','KIT',VDST.FMOVRECOGIDO,:CODMAT,:CODUBIDEST,:CODMATDEST,
							  :CODART,:CODLOT,:UNIEMB,NULL,:CANTIDADSEL*:UNIEMB,0,50,VDUSER.GETUSER,NULL,NULL,NULL,0,0);
				IF :NEWCODMOV=0 THEN 
                    :RET:=1;
                    :MSGERROR:='ERROR CREANDO MOVIMIENTO';
                ELSE
                    VDMOV.VDACTMOVIM (:NEWCODMOV, 0, '0000000000', '0000000000', :EMBCONT, 'CAJA', NULL, NULL);
                END IF;
				END;@
				
CURSOR=CSELRET SELECT :RET FROM DUAL WHERE :RET=0;

CURSOR=CUPDSTATUSBULTO UPDATE VDBULTOCAB SET STATUS=VDST.FBUCPDTESERVIR, CODOPEIMPRIME = VDUSER.GETUSER,FECIMPRIME = VD.FECHASYS, HORAIMPRIME = VD.HORASYS
                        WHERE CODBULTO IN (SELECT CODBULTO FROM
						                   (SELECT BUC.CODBULTO 
						                   FROM VDPEDIDOCAB PEC,VDBULTOCAB BUC 
	                                       WHERE PEC.CODPED=BUC.CODPED
	                                       AND   PEC.SEQPED=BUC.SEQPED
	                                       AND   PEC.ANOPED=BUC.ANOPED
	                                       AND   PEC.CODDIV=BUC.CODDIV
	                                       AND   PEC.STATUS=VDST.FPECPREPARANDO
	                                       AND   BUC.STATUS=VDST.FBUCRESERVADO
										   AND   PEC.PEDIDOHOST=:CODORDKIT
										   ORDER BY CODBULTO)
	                                       WHERE ROWNUM<=:CANTIDADSEL); 

CONTEXTUAL=FLEEMENU("XVDCONFIRMAKITS.ZOO")

ONLINE={F4} Finalizar   {Esc} Salir;