Monitor de zonas
Z. Operario Bultos Lineas Unid.
@L ________ @L,@@@ @L,@@@ @L,@@@
|
SOLOQUERY

SELECT=SELECT CODZONA,SUM(DECODE(TIPOBULTO,'U',1,0)) BULUNI,SUM(DECODE(TIPOBULTO,'U',LINEAS,0)) LINUNI,SUM(DECODE(TIPOBULTO,'U',UNIDADES,0)) UNIUNI,
              DECODE(MAX(CODOPEPREPARA),MIN(CODOPEPREPARA),MAX(CODOPEPREPARA),'VARIOS') CODOPE
 FROM
  (SELECT BUC.TIPOBULTO,BUC.CODBULTO,BUL.CODOPEPREPARA,BUL.STATUS,IDI.CODZONA,
          COUNT(*) LINEAS,SUM(CANTPEDIDA) UNIDADES
   FROM VDPEDIDOCAB PEC,VDSERIEPREP SEP,VDBULTOCAB BUC,VDBULTOLIN BUL,VDINFODISP IDI
   WHERE PEC.CODSERIEPREP=SEP.CODSERIEPREP AND BUC.IDINFOPICK=IDI.IDINFOPICK AND BUC.NUMDISP=IDI.NUMDISP AND 
         PEC.CODPED=BUC.CODPED AND PEC.CODDIV=BUC.CODDIV AND PEC.ANOPED=BUC.ANOPED AND PEC.SEQPED=BUC.SEQPED AND
         BUC.CODBULTO=BUL.CODBULTO AND SEP.CODSERIEPREP=:CODSERIEPREP AND
         SUBSTR(TO_CHAR(VDF.JUL2DATE(BUL.FECPREPARA,BUL.HORAPREPARA),'DD-MM-YY HH24'),1,11)=SUBSTR(:FECHA,1,11)
   GROUP BY BUC.TIPOBULTO,BUC.CODBULTO,BUL.CODOPEPREPARA,BUL.STATUS,IDI.CODZONA)
   GROUP BY CODZONA;
   
CAMPO=CODSERIEPREP,AUXILIAR,VIRTUAL,OCULTO
CAMPO=FECHA,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODZONA
CAMPO=CODOPE
CAMPO=BULUNI
CAMPO=LINUNI
CAMPO=UNIUNI