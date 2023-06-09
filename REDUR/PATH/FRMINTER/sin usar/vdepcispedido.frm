CAMPO=HFICHERO,AUXILIAR,OCULTO,"@L@@@@@@@@@@"
CAMPO=CODDIV,AUXILIAR,OCULTO,"_256"

BEGINBLOQUEFRM=EPCIS
   TABLA=EPCIS_PEDIDO ns2:EPCISDocument
   SOLOQUERY

   SELECT=SELECT  IHO.ROWID IHOROWID,BUC.CODBULTO,'1.0' VERSION,'urn:epcglobal:epcis:xsd:1' "XMLNS:NS2",TO_CHAR(SYSDATE,'YYYY-MM-DD"T"HH24:MI:SS')||'+02' creationDate
            FROM VDBULTOCAB BUC,VDINTERPENDHOST IHO
           WHERE BUC.CODCOMEN=IHO.CODCOMEN AND IHO.TIPOCOMEN='SERVIDO' AND IHO.STATUS=2000;

   POSTQUERY=FEJECUTA("CSELDIR","No existe carpeta",FABREFICHEROSTD(":DIRINTER","HFICHERO","XML","","1","0","1"),"No puedo abrir fichero cabecera")
   PREUPDATE=FEJECUTA(FESCRIBEFICHEROINTER(":HFICHERO","EPCIS_PEDIDO","ns2:EPCISDocument","1","1"),"","@CSELENVIAR","")

   POSTUPDATE=FEJECUTA("CUPDAIHO","",FCIERRAXML(":HFICHERO","ns2:EPCISDocument"),"")
   POSTDELETE=FEJECUTA(FCIERRAFICHERO(":HFICHERO"),"")

   CURSOR=CSELDIR SELECT DISTINCT BUZONOUT DIRINTER
                    FROM VDDIVIS
                   WHERE CODDIV LIKE :CODDIV;

   CURSOR=CSELENVIAR SELECT 'S' ENVIAR
                       FROM VDBULTOLIN BUL,VDPEDIDOCAB PEC
                      WHERE BUL.CODBULTO=:CODBULTO AND BUL.CANTSERVIDA>0 AND
                            (PEC.CODPED,PEC.CODDIV,PEC.ANOPED,PEC.SEQPED) IN (SELECT CODPED,CODDIV,ANOPED,SEQPED FROM VDBULTOCAB WHERE CODBULTO=:CODBULTO);

   CURSOR=CUPDAIHO BEGIN
                    UPDATE VDINTERPENDHOST SET STATUS=3000,
                                           CODOPEINTER=VDUSER.GETUSER,FECINTER=VD.FECHASYS,HORAINTER=VD.HORASYS,
                                           CODOPEMODIF=VDUSER.GETUSER,FECMODIF=VD.FECHASYS,HORAMODIF=VD.HORASYS
                     WHERE ROWID=:IHOROWID;
                    COMMIT;
                  END;@
				  							
   CAMPO=HFICHERO,AUXILIAR,VIRTUAL,OCULTO
   CAMPO=CODDIV,AUXILIAR,VIRTUAL,OCULTO
   CAMPO=DIRINTER,AUXILIAR,OCULTO,"_256"
   CAMPO=ENVIAR,AUXILIAR,OCULTO,"_"
   CAMPO=CODBULTO,AUXILIAR,OCULTO,"_20"
   CAMPO=IHOROWID,AUXILIAR,OCULTO,"_40"

ENDBLOQUE

BEGINBLOQUEFRM=EPCIS_HEADER
   TABLA=EPCIS_PEDIDO EPCISHeader
   PADRE=EPCIS
   SOLOQUERY

   SELECT=SELECT :HFICHERO FROM DUAL;
   
   POSTQUERY=FESCRIBEFICHEROINTER(":HFICHERO","EPCIS_PEDIDO","EPCISHeader","0","1")
   POSTUPDATE=FEJECUTA(FCIERRAXML(":HFICHERO","EPCISHeader"))
   
   CAMPO=HFICHERO,AUXILIAR,VIRTUAL,OCULTO
   CAMPO=CODBULTO,AUXILIAR,VIRTUAL,OCULTO
   
ENDBLOQUE
   
BEGINBLOQUEFRM=EPCIS_VERSION
   TABLA=EPCIS_PEDIDO DOCHeader
   PADRE=EPCIS_HEADER
   SOLOQUERY

   SELECT=SELECT '1.0' VERSION FROM DUAL;
   
   POSTQUERY=FESCRIBEFICHEROINTER(":HFICHERO","EPCIS_PEDIDO","DOCHeader","0","1")
   POSTUPDATE=FCIERRAXML(":HFICHERO","DOCHeader")

   CAMPO=HFICHERO,AUXILIAR,VIRTUAL,OCULTO
   CAMPO=CODBULTO,AUXILIAR,VIRTUAL,OCULTO

ENDBLOQUE

BEGINBLOQUEFRM=EPCIS_DOC
   PADRE=EPCIS_VERSION
   TABLA=EPCIS_PEDIDO DocumentId
   SOLOQUERY

    POSTQUERY=FESCRIBEFICHEROINTER(":HFICHERO","EPCIS_PEDIDO","DocumentId","0","1")

    SELECT=SELECT 'EPCglobal' ESTANDAR,'1.0' TIPOVERSION,'000001' INSTID,'Events' TIPO,SYSTIMESTAMP(0) CREACION
            FROM VDBULTOCAB BUC,VDINFODISP IDI,VDPEDIDOCAB PEC
           WHERE BUC.CODBULTO=:CODBULTO AND BUC.IDINFOPICK=IDI.IDINFOPICK AND BUC.NUMDISP=IDI.NUMDISP AND
		         PEC.CODPED=BUC.CODPED AND PEC.CODDIV=BUC.CODDIV AND PEC.ANOPED=BUC.ANOPED AND PEC.SEQPED=BUC.SEQPED;


   CAMPO=HFICHERO,AUXILIAR,VIRTUAL,OCULTO
   CAMPO=CODBULTO,AUXILIAR,VIRTUAL,OCULTO

ENDBLOQUE

BEGINBLOQUEFRM=EPCIS_BODY
   TABLA=EPCIS_PEDIDO EPCISBody
   PADRE=EPCIS
   SOLOQUERY

   SELECT=SELECT :HFICHERO FROM DUAL;
   
   POSTQUERY=FESCRIBEFICHEROINTER(":HFICHERO","EPCIS_PEDIDO","EPCISBody","0","1")
   POSTUPDATE=FCIERRAXML(":HFICHERO","EPCISBody")
   
   CAMPO=HFICHERO,AUXILIAR,VIRTUAL,OCULTO
   CAMPO=CODBULTO,AUXILIAR,VIRTUAL,OCULTO
ENDBLOQUE
   
BEGINBLOQUEFRM=EPCIS_EVENTLIST
   TABLA=EPCIS_PEDIDO EventList
   PADRE=EPCIS_BODY
   SOLOQUERY

   SELECT=SELECT :HFICHERO FROM DUAL;
   
   POSTQUERY=FESCRIBEFICHEROINTER(":HFICHERO","EPCIS_PEDIDO","EventList","0","1")
   POSTUPDATE=FCIERRAXML(":HFICHERO","EventList")
   
   CAMPO=HFICHERO,AUXILIAR,VIRTUAL,OCULTO
   CAMPO=CODBULTO,AUXILIAR,VIRTUAL,OCULTO
ENDBLOQUE
   
BEGINBLOQUEFRM=EPCIS_OBJECTEVENT
   TABLA=EPCIS_PEDIDO ObjectEvent
   PADRE=EPCIS_EVENTLIST
   SOLOQUERY

   SELECT=SELECT SYSTIMESTAMP(0) EVENTTIME,SYSTIMESTAMP(0) RECORDTIME,TO_CHAR(SYSTIMESTAMP,'TZR') ZONEOFFSET,'DELETE' ACTION FROM DUAL;
   
   POSTQUERY=FESCRIBEFICHEROINTER(":HFICHERO","EPCIS_PEDIDO","ObjectEvent","0","1")
   POSTUPDATE=FCIERRAXML(":HFICHERO","ObjectEvent")
   
   CAMPO=HFICHERO,AUXILIAR,VIRTUAL,OCULTO
   CAMPO=CODBULTO,AUXILIAR,VIRTUAL,OCULTO
ENDBLOQUE

BEGINBLOQUEFRM=EPCIS_EPCLIST	
   TABLA=EPCIS_PEDIDO EpcList
   PADRE=EPCIS_OBJECTEVENT
   SOLOQUERY

   SELECT=SELECT :CODBULTO FROM DUAL;
   
   POSTQUERY=FESCRIBEFICHEROINTER(":HFICHERO","EPCIS_PEDIDO","EpcList","0","1")
   POSTUPDATE=FCIERRAXML(":HFICHERO","EpcList")
   
   CAMPO=HFICHERO,AUXILIAR,VIRTUAL,OCULTO
   CAMPO=CODBULTO,AUXILIAR,VIRTUAL,OCULTO
ENDBLOQUE

BEGINBLOQUEFRM=EPCIS_EPC
   TABLA=EPCIS_PEDIDO Epc
   PADRE=EPCIS_EPCLIST
   SOLOQUERY

   SELECT=SELECT CODART EPC FROM VDBULTOLIN WHERE CODBULTO=:CODBULTO;
   
   POSTQUERY=FESCRIBEFICHEROINTER(":HFICHERO","EPCIS_PEDIDO","Epc","0","0")
   
   CAMPO=HFICHERO,AUXILIAR,VIRTUAL,OCULTO
   CAMPO=CODBULTO,AUXILIAR,VIRTUAL,OCULTO
ENDBLOQUE
