# Módulo   : VDENTSALXARTFEC.FRM              
# Función  : Trazabilidad por artículo - fecha 
#                                          
# Creación : 16-08-2008                    
# Autor    : MGM                           
###########################################

BEGINBLOQUE=VDARTICTRZ.PAN
  PREREGISTRO=PRESEHIJO
  NOINSERT
  NODELETE
  NOUPDATE
  NOCOMMIT
  WLONX=800
  POSY=1
 
  
ENDBLOQUE 

BEGINBLOQUE=VDMONFECHAS.PAN
  PADRE=VDARTICTRZ.PAN
  PREREGISTRO=PRESEHIJO
  PREQUERY=QUERYHIJO
  POSX=20
  POSY=15
  WPOSY=210  
  WLONX=400
  REGPAG=1
  NOINSERT
  NODELETE
  NOUPDATE
 CAMPO=CODART,AUXILIAR,VIRTUAL,OCULTO
 CAMPO=MIQUERY,AUXILIAR,OCULTO,"_4096_"
 CAMPO=DUMMY,AUXILIAR,OCULTO,"@"
 
  TECLA=SF8,FEJECUTA("CSELBINDNONULO","INFORME ARTICULO Y FECHAS",
                     FIMPRIME("INFORME","VDTRAZABILIDAD_STD.rpt","CODART=:CODART;CODLOT=NULL;CODCONCE=NULL;FECDESDE=:FECDESDE;FECHASTA=:FECHASTA",""),":V10ERROR")
  TECLA=SF9,FEJECUTA("CSELBINDNONULO","INFORME ARTICULO Y FECHAS",
                     FIMPRIME("INFORME","VDTRAZABILIDAD_STD.rpt","CODART=:CODART;CODLOT=NULL;CODCONCE='PEDEXPED';FECDESDE=:FECDESDE;FECHASTA=:FECHASTA",""),":V10ERROR")

  TECLA=SF11,FEJECUTA("CSELBINDNONULO","INFORME ARTICULO Y FECHAS",
                     "CDAMESELECT","",
                     FSQL2EXCEL(":MIQUERY","","0","1",""),"")    

  BOTON=B1,820,45,65,65,"EXPORTAEXCEL",EXCEL02.png,SF11,"Exportar a Excel",INCLUDECSS="background-color:transparent;border-width:0px"
  
  BOTON=B2,820,145,65,65,"EXPORTAPDF1",pdffiles01.png,SF8,"Informe Trazabilidad Completo",INCLUDECSS="background-color:transparent;border-width:0px"

#BOTON=B3,900,95,80,80,"EXPORTAPDF2",pdf-files02.png,SF9,"Informe Trazabilidad Pedidos",INCLUDECSS="background-color:transparent;border-width:0px"

  
 CURSOR=CSELBINDNONULO SELECT 1 DUMMY FROM DUAL WHERE :CODART IS NOT NULL AND :FECDESDE IS NOT NULL AND :FECHASTA IS NOT NULL; 
 
 CURSOR=CDAMESELECT SELECT 'SELECT ART.CODDIV DIVISION, '||'
                                         TO_CHAR (TO_DATE (MOV.FECFINMOV, ''J''), ''DD-MM-YYYY'')  FECHA, MOV.HORAFINMOV HORA, '||'
                                         MOV.CODART ARTICULO, ART.DESART DESCRIPCION, MOV.CODLOT LOTE, '||'
                                         CASE WHEN UBIO.STOCK = ''N'' THEN ''E'' '||'
                                              WHEN UBID.STOCK = ''N'' THEN ''S'' '||'
                                         ELSE ''I'' END TIPOOPE, SUM(MOV.CANTIDAD) CANTIDAD, '||'
                                         MOV.CODCONCE CONCEPTO, COC.DESCONCE DESCRIPCION, COC.SWTTRAZA TRAZA, '||'
                                         PEC.CODCLIENTE DESTINATARIO, '||'
                                         DECODE(MOV.CODCONCE,''PEDEXPED'',PEC.DESCLIENTE,NVL(MOV.CODOPEEJEMOV,CODOPEINS)) NOMBRE,   '||'
                                         ART.CODARTDIV ART_CODARTDIV, ART.CODEAN ART_CODEAN, ART.CODNAC ART_CODNAC, ART.UNIDADES ART_UNIDADES, ART.UNIEMB ART_UNIXEMB, ART.EMBCONT ART_EMBXCONT, ART.EMBPISO ART_EMBXPISO, ART.SWTACTIVO ART_SWTACTIVO,    '||'
                                         MOV.BLOQUEOSORI MOV_BLOQUEOSORI, MOV.BLOQUEOSDEST MOV_BLOQUEOS_DEST, MOV.CODRECEP MOV_RECEPCION,  '||'
                                         BUC.SEQPED BUC_SEQPED,  '||'
                                         PEC.CODPED PEC_CODPED, PEC.CODDIV PEC_CODDIV, PEC.ANOPED PEC_ANOPED, PEC.DP PEC_DP, PEC.POBLACION PEC_POBLACION, '||'
                                         TRIM (PEC.DIRECCION)|| '' ''|| TRIM (PEC.DIRECCION1)|| '' ''|| TRIM (PEC.DIRECCION2)|| '' ''|| TRIM (PEC.DIRECCION3) PEC_DIRECCION '||'
                                      FROM VDMOVIM MOV, VDBULTOLIN BUL, VDUBICA UBIO, VDUBICA UBID, VDARTIC ART,  '||'
                                           VDCONCEPTO COC, VDBULTOCAB BUC,  VDPEDIDOCAB PEC '||'
                                     WHERE MOV.CODMOV     = BUL.CODMOVEXP(+) '||'
                                       AND MOV.CODUBIORI  = UBIO.CODUBI '||'
                                       AND MOV.CODUBIDEST = UBID.CODUBI '||'
                                       AND MOV.CODART     = ART.CODART '||'
                                       AND MOV.CODCONCE   = COC.CODCONCE '||'
                                       AND MOV.CODCONCE = MOV.CODCONCE '||'
                                       AND MOV.CODART='''||:CODART||''' 
                                       AND MOV.CODLOT= MOV.CODLOT '||'
                                       AND BUL.CODBULTO   = BUC.CODBULTO(+) '||'
                                       AND BUC.CODDIV     = PEC.CODDIV(+) '||'
                                       AND BUC.ANOPED     = PEC.ANOPED(+) '||'
                                       AND BUC.CODPED     = PEC.CODPED(+) '||'
                                       AND BUC.SEQPED     = PEC.SEQPED(+) '||'
                                       AND MOV.CODUBIORI  = UBIO.CODUBI '||'
                                       AND MOV.CODUBIDEST = UBID.CODUBI '||'
                                       AND (UBIO.STOCK    = ''N'' '||'
                                         OR UBID.STOCK    = ''N'' '||'
                                         OR COC.SWTTRAZA   = ''S'') '||'
                                      AND MOV.FECMODIF BETWEEN '||:FECDESDE||' AND '||:FECHASTA||'
                                    GROUP BY MOV.CODART, ART.DESART, ART.CODDIV,   '||'
                                         ART.CODARTDIV, ART.CODEAN, ART.CODNAC, ART.UNIDADES, ART.UNIEMB, ART.EMBCONT,  '||'
                                         ART.EMBPISO, ART.SWTACTIVO, '||'
                                         MOV.HORAFINMOV, MOV.CODLOT, MOV.CODCONCE, MOV.BLOQUEOSORI,  '||'
                                         MOV.BLOQUEOSDEST, MOV.CODRECEP, COC.DESCONCE, '||'
                                         COC.SWTTRAZA, BUC.SEQPED, PEC.CODCLIENTE , '||'
                                         DECODE(MOV.CODCONCE,''PEDEXPED'',PEC.DESCLIENTE,NVL(MOV.CODOPEEJEMOV,CODOPEINS)), '||'
                                         PEC.CODPED, PEC.CODDIV, PEC.ANOPED, PEC.DP, PEC.POBLACION, '||'
                                         MOV.FECFINMOV, ART.FECMODIF, '||'
                                         TRIM (PEC.DIRECCION)|| '' ''|| TRIM (PEC.DIRECCION1)|| '' ''|| TRIM (PEC.DIRECCION2)|| '' ''|| TRIM (PEC.DIRECCION3) , '||'
                                         CASE WHEN UBIO.STOCK = ''N'' THEN ''E'' '||'
                                              WHEN UBID.STOCK = ''N'' THEN ''S'' '||'
                                         ELSE ''I'' END '||'
								ORDER BY MOV.CODLOT, MOV.FECFINMOV ' MIQUERY FROM DUAL;  
  
ENDBLOQUE

BEGINBLOQUE=VDENTSALARTXFEC.PAN
  PADRE=VDMONFECHAS.PAN
  PREREGISTRO=PRESEHIJO
  PREQUERY=QUERYHIJO
  POSY=21
  REGPAG=30
  NOINSERT
  NODELETE
  NOUPDATE
  NOCOMMIT

 
ENDBLOQUE
