#historico de cambios
#fecha: 26-02-2010
#
Monitor de series
Serie   Pedidos   Bul.  Lineas  Unid.     %       Bul.   Unid.    Pal. Unid
@L,@@@@ @L,@@@@   @L,@@ @L,@@@@ @L,@@@  #L#.#   @L,@@@ @L,@@@   @L,@ @L,@@@
|
SOLOQUERY

SELECT=SELECT CODSERIEPREP,COUNT(DISTINCT CODPED) PEDIDOS,SUM(DECODE(TIPOBULTO,'U',1,0)) BULUNI,
              SUM(DECODE(TIPOBULTO,'U',LINEAS,0)) LINUNI,SUM(DECODE(TIPOBULTO,'U',UNIDADES,0)) UNIUNI,
              SUM(DECODE(TIPOBULTO,'E',1,0)) BULCOMP,SUM(DECODE(TIPOBULTO,'E',UNIDADES,0)) UNICOMP,
              SUM(DECODE(TIPOBULTO,'C',1,0)) BULPAL,SUM(DECODE(TIPOBULTO,'C',UNIDADES,0)) UNIPAL,
              SUM(DECODE(TIPOBULTO,'U',DECODE(FECPREPARA,0,0,LINEAS),0))/SUM(DECODE(TIPOBULTO,'U',LINEAS,1))*100 PORUNI
 FROM
  (SELECT SEP.CODSERIEPREP,PEC.CODPED,BUC.TIPOBULTO,BUC.CODBULTO,BUL.STATUS,COUNT(*) LINEAS,SUM(CANTPEDIDA) UNIDADES,BUL.FECPREPARA
   FROM VDPEDIDOCAB PEC,VDSERIEPREP SEP,VDBULTOCAB BUC,VDBULTOLIN BUL
   WHERE PEC.CODSERIEPREP=SEP.CODSERIEPREP AND 
         PEC.CODPED=BUC.CODPED AND PEC.CODDIV=BUC.CODDIV AND PEC.ANOPED=BUC.ANOPED AND PEC.SEQPED=BUC.SEQPED AND
         BUC.CODBULTO=BUL.CODBULTO AND SEP.FECLANZA>=VD.FECHASYS-7 AND SEP.STATUS=VDST.FSPRLANZADA
   GROUP BY SEP.CODSERIEPREP,PEC.CODPED,BUC.TIPOBULTO,BUC.CODBULTO,BUL.STATUS,BUL.FECPREPARA);
GROUPBY=CODSERIEPREP;
ORDERBY=CODSERIEPREP DESC;

CAMPO=CODSERIEPREP,AUXILIAR,TITULO("Serie")
CAMPO=PEDIDOS,AUXILIAR,TITULO("Pedidos")
CAMPO=BULUNI,AUXILIAR,TITULO("Bul.Pick.")
CAMPO=LINUNI,AUXILIAR,TITULO("L�neas Pick.")
CAMPO=UNIUNI,AUXILIAR,TITULO("Uni. Pick.")
CAMPO=PORUNI,AUXILIAR,TOOLTIP("Porcentaje de l�neas de unidades preparadas"),TITULO("%")
CAMPO=BULCOMP,AUXILIAR,TITULO("Cajas")
CAMPO=UNICOMP,AUXILIAR,TITULO("Uni. Cajas")
CAMPO=BULPAL,AUXILIAR,TITULO("Palets")
CAMPO=UNIPAL,AUXILIAR,TITULO("Uni. Palets")
