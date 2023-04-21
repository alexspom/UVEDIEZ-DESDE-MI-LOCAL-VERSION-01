CREATE OR REPLACE PACKAGE     VDFMDPKG IS
  PROCEDURE SOAP(MIURL VARCHAR2,MIWALLET VARCHAR2,MIWALLETPWD VARCHAR2,MIPROXY VARCHAR2,MICOMANDO VARCHAR2,MIACCION VARCHAR2,RET OUT NUMBER,RESULTADO OUT VARCHAR2);
  PROCEDURE TEST;
END;
/
CREATE OR REPLACE PACKAGE BODY VDFMDPKG IS
  PROCEDURE SOAP(MIURL VARCHAR2,MIWALLET VARCHAR2,MIWALLETPWD VARCHAR2,MIPROXY VARCHAR2,MICOMANDO VARCHAR2,MIACCION VARCHAR2,RET OUT NUMBER,RESULTADO OUT VARCHAR2) IS     
      REQUEST  UTL_HTTP.REQ;
      RESPONSE UTL_HTTP.RESP;
      RESPUESTA VARCHAR2(32000);
    BEGIN
      RESULTADO:='';
      IF MIWALLET IS NOT NULL THEN
        UTL_HTTP.SET_WALLET(MIWALLET, MIWALLETPWD);
       END IF;
      IF MIPROXY IS NOT NULL THEN
        UTL_HTTP.SET_PROXY(MIPROXY);
       END IF;
      REQUEST := UTL_HTTP.BEGIN_REQUEST(MIURL, 'POST', UTL_HTTP.HTTP_VERSION_1_1);
      UTL_HTTP.SET_HEADER(REQUEST, 'Content-Type', 'text/xml; charset="utf-8"');
      UTL_HTTP.SET_HEADER(REQUEST, 'Content-Length', LENGTH(MICOMANDO));
      UTL_HTTP.SET_HEADER(REQUEST, 'SOAPAction', MIACCION);
      UTL_HTTP.WRITE_TEXT(REQUEST, MICOMANDO);
      RESPONSE := UTL_HTTP.GET_RESPONSE(REQUEST);
      BEGIN
        LOOP
          UTL_HTTP.READ_TEXT(RESPONSE, RESPUESTA, 32000);
          RESULTADO:=RESULTADO||RESPUESTA;
        END LOOP;
      EXCEPTION
        WHEN UTL_HTTP.END_OF_BODY THEN
          UTL_HTTP.END_RESPONSE(RESPONSE);
      END;
      EXCEPTION WHEN OTHERS THEN
        VDLOG.PONERROR('SOAP','ERROR AL EJECUTAR SOAP');
    END;
    
    PROCEDURE LOGPARCIAL(CADENA VARCHAR2) IS
      I NUMBER:=1;
     BEGIN
      WHILE I<LENGTH(CADENA) LOOP
        VDLOG.PONMENSAJE('LOGPARCIAL',SUBSTR(CADENA,I,200));
        I:=I+200;
       END LOOP;
     END;
    
    PROCEDURE FMDSINGLE(MICODFMD VARCHAR2,MIACCION VARCHAR2,MITRX VARCHAR2,MICODART VARCHAR2,MICODLOT VARCHAR2,MICADUCI VARCHAR2,MISERIE VARCHAR2,
                        MIRETURNCODE OUT VARCHAR2,MISTATUS OUT VARCHAR2,MIREASON OUT VARCHAR2,MIDESCRIPCION OUT VARCHAR2,MINMVSTRXID OUT VARCHAR2) IS
      MIFMD VDFMD%ROWTYPE;
      MIRESULTADO VARCHAR2(32000);
      RET NUMBER;
      MITIPO VARCHAR2(100);
      MIRET VARCHAR2(100);
     BEGIN
       SELECT * INTO MIFMD FROM VDFMD WHERE CODFMD=MICODFMD;
       MIFMD.COMANDOSINGLE:=REPLACE(MIFMD.COMANDOSINGLE,'<!--ACCION-->',MIACCION);
       MIFMD.COMANDOSINGLE := REPLACE(MIFMD.COMANDOSINGLE, '<!--IDLOGIN-->', MIFMD.IDLOGIN);
       MIFMD.COMANDOSINGLE := REPLACE(MIFMD.COMANDOSINGLE, '<!--IDUSER-->', MIFMD.IDUSER);
       MIFMD.COMANDOSINGLE := REPLACE(MIFMD.COMANDOSINGLE, '<!--USERPWD-->', MIFMD.USERPWD);
       MIFMD.COMANDOSINGLE := REPLACE(MIFMD.COMANDOSINGLE, '<!--SOFTNOMBRE-->', MIFMD.SOFTNOMBRE);
       MIFMD.COMANDOSINGLE := REPLACE(MIFMD.COMANDOSINGLE, '<!--SOFTPROV-->', MIFMD.SOFTPROV);
       MIFMD.COMANDOSINGLE := REPLACE(MIFMD.COMANDOSINGLE, '<!--SOFTVER-->', MIFMD.SOFTVER);
       MIFMD.COMANDOSINGLE := REPLACE(MIFMD.COMANDOSINGLE, '<!--TRXID-->', MITRX);
       MIFMD.COMANDOSINGLE := REPLACE(MIFMD.COMANDOSINGLE, '<!--LENGUAJE-->', MIFMD.LENGUAJE);
       MIFMD.COMANDOSINGLE := REPLACE(MIFMD.COMANDOSINGLE, '<!--TIPOCODIGO-->', MIFMD.TIPOCODIGO);
       MIFMD.COMANDOSINGLE := REPLACE(MIFMD.COMANDOSINGLE, '<!--CODART-->', MICODART);
       MIFMD.COMANDOSINGLE := REPLACE(MIFMD.COMANDOSINGLE, '<!--CODLOT-->', MICODLOT);
       MIFMD.COMANDOSINGLE := REPLACE(MIFMD.COMANDOSINGLE, '<!--CADUCI-->', TO_CHAR(TO_DATE(MICADUCI,'YYYYMMDD'),'YYMMDD'));
       MIFMD.COMANDOSINGLE := REPLACE(MIFMD.COMANDOSINGLE, '<!--NUMEROSERIE-->',MISERIE);
       SOAP(MIFMD.URLSINGLE,MIFMD.WALLETPATH,MIFMD.WALLETPWD,MIFMD.PROXY,MIFMD.COMANDOSINGLE,MIACCION,RET,MIRESULTADO);
       MITIPO:='/soap:Envelope/soap:Body/ns2:'||MIACCION||'Response';
       SELECT  STATUS,REASON,RETURNCODE,DESCRIPCION,NMVSTRXID
          INTO MISTATUS,MIREASON,MIRETURNCODE,MIDESCRIPCION,MINMVSTRXID
         FROM XMLTABLE(XMLNAMESPACES('http://www.w3.org/2003/05/soap-envelope' AS "soap",
                                    'urn:types.nmvs.eu:v1.0' AS "ns1",
                              'urn:wsdltypes.nmvs.eu:v1.0' AS "ns2"),                             
                '/soap:Envelope/soap:Body/ns2:G110Response,/soap:Envelope/soap:Body/ns2:G120Response,/soap:Envelope/soap:Body/ns2:G121Response,/soap:Envelope/soap:Body/ns2:G130Response,/soap:Envelope/soap:Body/ns2:G131Response,/soap:Envelope/soap:Body/ns2:G140Response,/soap:Envelope/soap:Body/ns2:G141Response,/soap:Envelope/soap:Body/ns2:G150Response,/soap:Envelope/soap:Body/ns2:G151Response,/soap:Envelope/soap:Body/ns2:G160Response,/soap:Envelope/soap:Body/ns2:G161Response,/soap:Envelope/soap:Body/ns2:G170Response,/soap:Envelope/soap:Body/ns2:G171Response,/soap:Envelope/soap:Body/ns2:G180Response,/soap:Envelope/soap:Body/ns2:G181Response'
                passing XMLTYPE(MIRESULTADO),
                 MIACCION AS "MIACCION"
                columns 
                 NMVSTRXID   VARCHAR2(100) PATH 'ns1:Header/ns1:Transaction/ns1:NMVSTrxId',
                 STATUS      VARCHAR2(100) PATH 'ns1:Body/ns1:Pack/@ns1:state',
                 REASON      VARCHAR2(100) PATH 'ns1:Body/ns1:Pack/ns1:Reason',
                 RETURNCODE  VARCHAR2(100) PATH 'ns1:Body/ns1:ReturnCode/@ns1:code',
                 DESCRIPCION VARCHAR2(100) PATH 'ns1:Body/ns1:ReturnCode/@ns1:desc'
                 );
     END;
   
  PROCEDURE FMDSINGLELOG(MICODFMD VARCHAR2,MIACCION VARCHAR2,MITRX VARCHAR2,MICODART VARCHAR2,MICODLOT VARCHAR2,MICADUCI VARCHAR2,MISERIE VARCHAR2,
                         MIRETURNCODE OUT VARCHAR2,MISTATUS OUT VARCHAR2,MIREASON OUT VARCHAR2,MIDESCRIPCION OUT VARCHAR2,MINMVSTRXID OUT VARCHAR2) IS
       MISECFMD NUMBER;
     BEGIN
       FMDSINGLE(MICODFMD,MIACCION,MITRX,MICODART,MICODLOT,MICADUCI,MISERIE,MIRETURNCODE,MISTATUS,MIREASON,MIDESCRIPCION,MINMVSTRXID);
       MISECFMD:=VDSECFMDLOG.NEXTVAL;
       INSERT INTO VDFMDLOG (SECFMDLOG,CODFMD,ACCION,CODART,CODLOT,NUMEROSERIE,CADUCI,TRXIN,TRXOUT,STATUS,RET,REASON,DESCRIPCION, 
                             CODOPEINS, FECMODIF, HORAMODIF) 
                      VALUES (MISECFMD,MICODFMD,MIACCION,MICODART,MICODLOT,MISERIE,MICADUCI,MITRX,MINMVSTRXID,MISTATUS,MIRETURNCODE,MIREASON,MIDESCRIPCION,
                              VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS);
     END; 
     
     
     
 PROCEDURE TEST IS  
  ID VARCHAR2(100);
  REASON VARCHAR2(100);
  RET VARCHAR2(100);
  MIRETURNCODE VARCHAR2(100);
  MIDESCRIPCION VARCHAR2(100);
  STATUS VARCHAR2(100);
  BEGIN
    FMDSINGLELOG('ALCURA','G110','123','09365766820875','TEST7F51599CDB',TO_CHAR(TO_DATE('03/31/23','MM/DD/YY'),'YYYYMMDD'),'PK001D948A749CE6B40',
                 MIRETURNCODE, STATUS,REASON,MIDESCRIPCION,ID);
    VDLOG.PONMENSAJE('TEST','ID',ID,'STATUS',STATUS,'REASON',REASON);
  END;

END;

/
CREATE SEQUENCE VDSECFMDLOG
  START WITH 41
  MAXVALUE 9999999999999999999999999999
  MINVALUE 1
  NOCYCLE
  CACHE 20
  NOORDER
  NOKEEP
  GLOBAL;
CREATE TABLE VDFMD
(
  CODFMD         VARCHAR2(20 BYTE),
  DESFMD         VARCHAR2(60 BYTE),
  PROXY          VARCHAR2(100 BYTE),
  WALLETPATH     VARCHAR2(200 BYTE),
  WALLETPWD      VARCHAR2(40 BYTE),
  URLSINGLE      VARCHAR2(500 BYTE),
  COMANDOSINGLE  VARCHAR2(4000 BYTE),
  IDLOGIN        VARCHAR2(40 BYTE),
  IDUSER         VARCHAR2(40 BYTE),
  USERPWD        VARCHAR2(40 BYTE),
  SOFTNOMBRE     VARCHAR2(100 BYTE),
  SOFTPROV       VARCHAR2(100 BYTE),
  SOFTVER        VARCHAR2(40 BYTE),
  LENGUAJE       VARCHAR2(40 BYTE),
  TIPOCODIGO     VARCHAR2(10 BYTE),
  DOMINIO        VARCHAR2(200 BYTE),
  CODOPEINS      VARCHAR2(32 BYTE),
  FECINS         NUMBER(7),
  HORAINS        VARCHAR2(8 BYTE)
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE TABLE VDFMDLOG
(
  SECFMDLOG    NUMBER(9),
  CODFMD       VARCHAR2(20 BYTE),
  ACCION       VARCHAR2(20 BYTE),
  CODART       VARCHAR2(20 BYTE),
  CODLOT       VARCHAR2(20 BYTE),
  NUMEROSERIE  VARCHAR2(60 BYTE),
  CADUCI       VARCHAR2(8 BYTE),
  TRXIN        VARCHAR2(60 BYTE),
  TRXOUT       VARCHAR2(60 BYTE),
  STATUS       VARCHAR2(20 BYTE),
  RET          VARCHAR2(20 BYTE),
  REASON       VARCHAR2(100 BYTE),
  DESCRIPCION  VARCHAR2(100 BYTE),
  CODOPEINS    VARCHAR2(32 BYTE),
  FECMODIF     NUMBER(9),
  HORAMODIF    VARCHAR2(8 BYTE)
)
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;

ALTER TABLE VDFMD ADD (
  CONSTRAINT VDFMDPK
  PRIMARY KEY
  (CODFMD)
  ENABLE VALIDATE);

ALTER TABLE VDFMDLOG ADD (
  CONSTRAINT VDFMDLOGPK
  PRIMARY KEY
  (SECFMDLOG)
  ENABLE VALIDATE);
SET DEFINE OFF;
Insert into ALC.VDFMD
   (CODFMD, DESFMD, WALLETPATH, WALLETPWD, URLSINGLE, 
    COMANDOSINGLE, IDLOGIN, IDUSER, USERPWD, SOFTNOMBRE, 
    SOFTPROV, SOFTVER, LENGUAJE, TIPOCODIGO, DOMINIO, 
    CODOPEINS, FECINS, HORAINS)
 Values
   ('ALCURA', 'FMD ALCURA', 'file:C:\ORACLE\WALLET', 'AHrcl17-', 'https://ws-single-transactions-int-bp.nmvs.eu:8443/WS_SINGLE_TRANSACTIONS_V1/SinglePackServiceV10', 
    '<soap:Envelope xmlns:soap="http://www.w3.org/2003/05/soap-envelope" xmlns:urn="urn:wsdltypes.nmvs.eu:v1.0" xmlns:urn1="urn:types.nmvs.eu:v1.0">
  <soap:Header/>
   <soap:Body>
      <urn:<!--ACCION-->Request>
         <urn1:Header>
            <urn1:Auth>
               <urn1:ClientLoginId><!--IDLOGIN--></urn1:ClientLoginId>
               <urn1:UserId><!--IDUSER--></urn1:UserId>
               <urn1:Password><!--USERPWD--></urn1:Password>
            </urn1:Auth>
            <urn1:UserSoftware urn1:name="<!--SOFTNOMBRE-->" urn1:supplier="<!--SOFTPROV-->" urn1:version="<!--SOFTVER-->"/>
            <urn1:Transaction>
               <urn1:ClientTrxId><!--TRXID--></urn1:ClientTrxId>
               <urn1:Language><!--LENGUAJE--></urn1:Language>
            </urn1:Transaction>
         </urn1:Header>
         <urn1:Body>
            <urn1:Product>
               <urn1:ProductCode urn1:scheme="<!--TIPOCODIGO-->"><!--CODART--></urn1:ProductCode>
               <urn1:Batch>
                  <urn1:Id><!--CODLOT--></urn1:Id>
                  <urn1:ExpDate><!--CADUCI--></urn1:ExpDate>
               </urn1:Batch>
            </urn1:Product>
            <urn1:Pack urn1:sn="<!--NUMEROSERIE-->"/>
         </urn1:Body>
      </urn:<!--ACCION-->Request>
   </soap:Body>
</soap:Envelope>', 'SWS', 'ALCA1001', '?_5sJHR2USdb2', 'V10', 
    'V10', '3.0', 'eng', 'GTIN', 'nmvs.eu', 
    'X', 0, '00:00:00');
COMMIT;
