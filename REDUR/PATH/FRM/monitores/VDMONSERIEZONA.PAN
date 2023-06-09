Monitor de volumetrias
Volumetria   Operario Bultos Lineas Unid.
____________ ________ @L,@@@ @L,@@@ @L,@@@
|
SOLOQUERY

SELECT=SELECT TIPOVOL,SUM(DECODE(TIPOBULTO,'U',1,0)) BULUNI,SUM(DECODE(TIPOBULTO,'U',LINEAS,0)) LINUNI,SUM(DECODE(TIPOBULTO,'U',UNIDADES,0)) UNIUNI,
              DECODE(MAX(CODOPEPREPARA),MIN(CODOPEPREPARA),MAX(CODOPEPREPARA),'VARIOS') CODOPE
 FROM
  (SELECT BUC.TIPOBULTO,BUC.CODBULTO,BUL.CODOPEPREPARA,BUL.STATUS,BUC.TIPOVOL,
          COUNT(*) LINEAS,SUM(CANTPEDIDA) UNIDADES
   FROM VDPEDIDOCAB PEC,VDBULTOCAB BUC,VDBULTOLIN BUL,VDSERIEPREP SEP
   WHERE PEC.CODSERIEPREP=SEP.CODSERIEPREP AND BUC.TIPOBULTO='U' AND
         PEC.CODPED=BUC.CODPED AND PEC.CODDIV=BUC.CODDIV AND PEC.ANOPED=BUC.ANOPED AND PEC.SEQPED=BUC.SEQPED AND
         BUC.CODBULTO=BUL.CODBULTO AND SEP.CODSERIEPREP=:CODSERIEPREP
   GROUP BY BUC.TIPOBULTO,BUC.CODBULTO,BUL.CODOPEPREPARA,BUL.STATUS,BUC.TIPOVOL)
   GROUP BY TIPOVOL;
   
CAMPO=CODSERIEPREP,AUXILIAR,VIRTUAL,OCULTO
CAMPO=TIPOVOL,TITULO("Volumetria")
CAMPO=CODOPE,TITULO("Operario")
CAMPO=BULUNI,TITULO("Bultos")
CAMPO=LINUNI,TITULO("L�neas")
CAMPO=UNIUNI,TITULO("Unid.")