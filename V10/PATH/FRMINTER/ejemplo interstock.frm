CAMPO=HFICHERO,AUXILIAR,OCULTO,"@L@@@@@@@@@@"
CAMPO=CODDIV,AUXILIAR,OCULTO,"____"
BEGINBLOQUEFRM=INTERSTOCKDIV
   TABLA=DUAL
   SOLOQUERY

   SELECT=SELECT DISTINCT BUZONOUT BUZONOUT
           FROM VDDIVIS
           WHERE CODDIV LIKE :CODDIV;

   CAMPO=CODDIV,AUXILIAR,VIRTUAL,OCULTO
   CAMPO=BUZONOUT,AUXILIAR,OCULTO,"_256"
   CAMPO=HFICHERO,AUXILIAR,VIRTUAL,OCULTO
ENDBLOQUE

BEGINBLOQUEFRM=INTERSTOCK
  PADRE=INTERSTOCKDIV
  TABLA=STOCKCAB STD
  SOLOQUERY

  PREBLOQUE=FABREFICHEROSTD(":BUZONOUT","HFICHERO")
  POSTBLOQUE=FCIERRAFICHERO(":HFICHERO")

  POSTQUERY=FESCRIBEFICHERO(":HFICHERO")

  SELECT=SELECT AR.CODART,AR.DESART,SUM(CANTIDAD) CANTIDAD
          FROM VDARTIC AR,VDSTOCK SK
          WHERE SK.CODART=AR.CODART AND AR.CODDIV IN (SELECT CODDIV FROM VDDIVIS WHERE BUZONOUT=:BUZONOUT);
  GROUPBY=AR.CODART,AR.DESART;        
  
  PREUPDATE=FEJECUTA(FIF("CESIMPAR",FCOMMITFICHERO(":HFICHERO"),FROLLBACKFICHERO(":HFICHERO")),"")
  
  CURSOR=CESIMPAR SELECT :CANTIDAD FROM DUAL WHERE MOD(:CANTIDAD,2)=0;

  CAMPO=CANTIDAD,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),AUXILIAR,OCULTO,"#L###########"
  CAMPO=HFICHERO,AUXILIAR,VIRTUAL,OCULTO
  CAMPO=BUZONOUT,AUXILIAR,VIRTUAL,OCULTO

ENDBLOQUE

BEGINBLOQUEFRM=INTERSTOCKLIN
  PADRE=INTERSTOCK
  TABLA=STOCKLIN STD
  SOLOQUERY

  POSTQUERY=FESCRIBEFICHERO(":HFICHERO")

  SELECT=SELECT SK.CODLOT,SUM(CANTIDAD) CANTIDAD
          FROM VDARTIC AR,VDSTOCK SK
          WHERE SK.CODART=AR.CODART;
  GROUPBY=AR.CODART,SK.CODLOT;        

  CAMPO=CODART,PREFIJO=AR,VIRTUAL,OCULTO
  CAMPO=CANTIDAD,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),AUXILIAR,OCULTO,"#L###########"
  CAMPO=HFICHERO,AUXILIAR,VIRTUAL,OCULTO
ENDBLOQUE