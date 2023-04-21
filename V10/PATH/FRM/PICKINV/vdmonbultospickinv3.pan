###################################################################
#Módulo: VDMONBULTOSPICKINV3.PAN
#Funcionalidad : Monitor de bultos de picking inverso, de un estado y una seie(s)
#Autor: FGS   
#Fecha: 24-06-2008
###################################################################
# Histórico de cambios:
LISTA DE BULTOS DE PICKING INVERSO DEL ESTADO SELECCIONADO Y LA SERIE(S)
                                                                  ÏÄÄÄÄÄÄÄÄÄÄÄ Cantidades ÄÄÄÄÄÄÄÄÄÄÄ‘  ÏÄÄÄÄÄ Líneas ÄÄÄÄÄÄ‘
  Bulto             P Matrícula          Artículo        Capac. C Movida AServir Servida Proces Restos  AServ Serv Proc Resto 
 __________________ _ __________________ _40____________ @L@@@@ _ @L@@@@ @L@@@@  @L@@@@  @L@@@@ @L@@@@   @L@@  @L@@ @L@@ @L@@
|

SOLOQUERY
TABLA=BPL
SELECT= SELECT * FROM 
         (SELECT BPC.CODBULTO,CAJACOMPLETA,BPC.CODMAT,MOV.CODART
          FROM VDBULTOCABPINV BPC,
               VDMOVIM MOV,
               VDBULTOLIN BUL,
               VDBULTOCAB BUC,
               VDPEDIDOCAB PEC,
               VDSERIEPREP SPR
          WHERE
              VD.CONTIENECAD(:RANSERIE,SPR.CODSERIEPREP) = 1 AND
              PEC.CODSERIEPREP = SPR.CODSERIEPREP AND
              BUC.CODPED       =    PEC.CODPED AND
              BUC.CODDIV       =    PEC.CODDIV AND
              BUC.ANOPED       =    PEC.ANOPED AND
              BUC.SEQPED       =    PEC.SEQPED AND            
              SWTPICKINGINV='S' AND 
              BUL.CODBULTO = BUC.CODBULTO AND
              MOV.CODMOV   = BUL.CODMOV AND
              BPC.CODMAT = MOV.CODMATORI AND                 
              BPC.STATUS   = :STATUS) BPL
          WHERE 1 = 1;
              
GROUPBY=CODBULTO,CAJACOMPLETA,CODMAT, CODART;
WFRAME(456,-2,319,0,"Cantidades","")
WFRAME(772,-2,200,0,"Líneas","")
WLONX=1000

POSTQUERY=FEJECUTA("+CSELCODART","",
                   "CSELCANTIDADES","")
                   
CAMPO=CODBULTO,TITULO("Bulto")
CAMPO=PREPICKING,AUXILIAR,TOOLTIP("Si se trata de un bulto de picking inverso por prepicking"),TITULO("P")
CAMPO=CODMAT,TOOLTIP("Matrícula asociada al bulto de picking inverso"),TITULO("Matrícula")
CAMPO=CODART,TITULO("Artículo")
CAMPO=UNIEMB,AUXILIAR,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),TITULO("Capac."),WLONX=20
CAMPO=CAJACOMPLETA,TOOLTIP("Si la caja del bulto es una caja completa o parcial"),TITULO("C")
CAMPO=CANTIDADMOVIDA,AUXILIAR,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),TITULO("Movida"),WLONX=22
CAMPO=CANTPORSERVIR,AUXILIAR,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),TITULO("A servir"),WLONX=22
CAMPO=CANTSERVIDA,AUXILIAR,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),TITULO("Servida"),WLONX=22
CAMPO=CANTPROCESADA,AUXILIAR,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),TITULO("Proces"),WLONX=22
CAMPO=CANTRESTOS,AUXILIAR,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),TITULO("Restos"),WLONX=20
CAMPO=LINEASPORSERVIR,AUXILIAR,TITULO("A serv."),WLONX=22
CAMPO=LINEASSERVIDA,AUXILIAR,TITULO("Serv"),WLONX=22
CAMPO=LINEASPROCESADA,AUXILIAR,TITULO("Proc"),WLONX=22
CAMPO=LINEASRESTOS,AUXILIAR,TITULO("Resto"),WLONX=20 
CAMPO=RANSERIE,AUXILIAR,VIRTUAL,OCULTO
CAMPO=STATUS,AUXILIAR,VIRTUAL,OCULTO

CURSOR=CSELCODART SELECT ART.CODART, MOV.UNIEMB, DECODE(PICKINV,'P','S','N') PREPICKING
                    FROM VDBULTOLIN BUL, VDMOVIM MOV ,VDARTIC ART 
                  WHERE BUL.CODBULTO = :CODBULTO 
				    AND BUL.CODMOV   = MOV.CODMOV
					AND BUL.CODART   = ART.CODART
                  GROUP BY ART.CODART, ART.PICKINV,  MOV.UNIEMB;
                  
CURSOR=CSELCANTIDADES SELECT  SUM(CANTPEDIDA) CANTIDADMOVIDA,
                              SUM(DECODE(STATUS,VDST.FBPLASERVIR,CANTPEDIDA,0))   CANTPORSERVIR,
                              SUM(DECODE(STATUS,VDST.FBPLSERVIDA,CANTPEDIDA,0))   CANTSERVIDA,
                              SUM(DECODE(STATUS,VDST.FBPLPROCESADA,CANTPEDIDA,0)) CANTPROCESADA,
                              SUM(DECODE(STATUS,VDST.FBPLRESTOS,CANTPEDIDA,0)) 	  CANTRESTOS,
                              SUM(DECODE(STATUS,VDST.FBPLASERVIR,1,0)) 			  LINEASPORSERVIR,       
                              SUM(DECODE(STATUS,VDST.FBPLSERVIDA,1,0)) 			  LINEASSERVIDA,       
                              SUM(DECODE(STATUS,VDST.FBPLPROCESADA,1,0)) 		  LINEASPROCESADA,       
                              SUM(DECODE(STATUS,VDST.FBPLRESTOS,1,0)) 			  LINEASRESTOS       
                        FROM VDBULTOLIN BUL
                        WHERE CODBULTO=:CODBULTO;
                        

                        