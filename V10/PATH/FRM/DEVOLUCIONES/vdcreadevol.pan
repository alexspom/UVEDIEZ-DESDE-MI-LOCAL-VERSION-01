CREACION DE CABECERAS DE DEVOLUCION

 Protocolo   @L@@@@@@@                          
 
 Div:     _20___ _40__________________________________________________
      
 Cliente  _20____________ 
          _60______________________________________________________

 оддддддддддддддддддддддддд Devoluci?  дддддддддддддддддддддддд? 
 ?ev. Cliente: _20_____________    Recepci?: ?-MM-Y.YY        ?
 ?                                                              ?
 ?xpedici?: _20_____________                                   ?
 ??Entrega Roche : ____________________                        ?
 ?ransporte: _20_____________ Albar? ST: ____________________  ?
 ?eritaje: _                  Solucionado cliente: _            ?
 ?MS: ____________________    RECALL: _________                 ?
 ?                                                              ?
 ?mporte: #L,####.## Unidades: @L@@ Bultos: @L,@@@ Kilos @L,@@@ ?
 ?                                                              ?
 ?bservaciones _255____________________________________________ ?
 ?                                                              ?
 ?                                                              ?
 ?                                                              ?
 ?                                                              ?
 ?дддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддд▓ 

 оддддддддддддддддддддддддд?Direcci?  дддддддддддддддддддддддд? 
 ?Contacto   _40_____________________________________           ?                          
 ?Direcci?  _40_____________________________________           ?
 ?           _40_____________________________________           ?
 ?           _40_____________________________________           ?
 ?           _40_____________________________________           ?
 ?                                                              ?
 ?Poblacion  _40_____________________________________           ? 
 ?Pais       _____ _40_________________                         ?
 ?Provincia  _____ _40_______________________________           ?
 ?Tel?ono   ____________                                       ?
 ?                                                              ?
 ?дддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддд▓       
 
 оддддддддддддддддддддддддд?Seguimiento  дддддддддддддддддддддд?
 ?                                                              ?
 ?Inserci?        _32______________ ?-MM-Y.YY ________        ?
 ?Validaci?       _32______________ ?-MM-Y.YY ________        ?
 ?Conf. Protocolo. _32______________ ?-MM-Y.YY ________        ?
 ?Finalizaci?     _32______________ ?-MM-Y.YY ________        ?
 ?                                                              ?
 ?Estado     @L@@@ _40__________________________________________?
 ?Ult.Modificaci? _32______________ ?-MM-Y.YY ________        ?
 ?                                                              ?
 ?дддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддд▓  
|
INCLUDEFICHEROCSS="vertis.css"
TABLA=VDDEVOLCAB
NOQUERY
POSX=36
WPOSY=120

PREREGISTRO=FPOSICIONACAMPO(FSUCCESS,"CODCLIENTE")

PREUPDATE=FDESIGNACION("CSELDESPROV","NO EXISTE LA PROVINCIA DEL PAIS INDICADO") 

PREINSERT=FDESIGNACION("+CPONDIVIS","",
                       "-CDIVNULL","Debe elegir la divisi? de la devoluci?",
                       "CSELDESCLI","Debe introducir un C?igo de cliente v?ido",
                       "CSELDESPROV","NO EXISTE LA PROVINCIA DEL PAIS INDICADO", 
                       "+CSELOPEINS","",
                       "CSELST","DEBE INFORMARSE INDICADOR DE PERITAJE \nPARA SINIESTRO DE TRANSPORTE",
                       FPULSATECLAS("SF2"),"")
                       
#POSTINSERT=FEJECUTA(%FFAILURE,"DEVOLUCION :SEQDEVOL CREADA")                       



CAMPO=SEQDEVOL,NOUPDATE,NOENTER,TOOLTIP("C?igo de la devoluci?")
#CAMPO=ULTMAPEO,AUXILIAR,NOUPDATE,NOENTER
CAMPO=CODDIV,COMBOX("CLISTADIVIS"),POSTCHANGE=FEJECUTA("+CSELDIVIS",""),COMBOXREGPAG=10
CAMPO=DESDIV,AUXILIAR,NOENTER
CAMPO=CODCLIENTE,UPPER,POSTCHANGE=FEJECUTA("+CSELDATOSCLI",""),WPOSY=-2,INCLUDECSS="font-style:bold;border-style:ridge;background-color:#F7BE81;"

CAMPO=DESCLIENTE,UPPER,NOUPDATE,POSTCHANGE=FVALNOCERO("Debe introducir designaci? de cliente")
CAMPO=CODDEVCLI,INCLUDECSS="height:26px;COLOR:DARKBLUE;font-style:bold;font-size:14pt;border-style:ridge;background-color:#F7BE81;",WPOSY=-2,WLONX=6
CAMPO=FECRECEP,COMBOX("CALENDARIO")
CAMPO=EXPEDICION
CAMPO=CODPED,WPOSX=-8
CAMPO=TRANSPORTE,POSTCHANGE=FVALNOCERO("Debe introducir Transporte")
CAMPO=CODALBAST,TOOLTIP("N?ero de albar? de siniestro de transporte")
CAMPO=SWTPERITAJE,POSTCHANGE=FEJECUTA(FVERIFICA("SN ","Debe introducir S(i) o N(o)"),""),TOOLTIP("Indica si se requiere peritaje")
CAMPO=SWTSOLCLIENTE,POSTCHANGE=FEJECUTA(FVERIFICA("SN ","Debe introducir S(i) o N(o)"),""),TOOLTIP("Campo informativo que indica si se ha solucionado la devoluci? por parte del cliente")
CAMPO=CODCMS,TOOLTIP("N?ero de CMS (C?igo interno)")
CAMPO=NUMRECALL,TOOLTIP("N?ero de RECALL interno")
CAMPO=PRECIODEV,INCLUDECSS="height:26px;COLOR:DARKBLUE;font-style:bold;font-size:14pt;border-style:ridge;background-color:#F7BE81;",WPOSY=-2,WLONX=8
#,POSTCHANGE=FVALNOCERO("Debe introducir importe")
CAMPO=NUMUNI,INCLUDECSS="height:26px;COLOR:DARKBLUE;font-style:bold;font-size:14pt;border-style:ridge;background-color:#F7BE81;",WPOSY=-2,WLONX=6
#,POSTCHANGE=FVALNOCERO("Debe introducir n?ero de unidades")
CAMPO=NUMBULTOS,POSTCHANGE=FVALNOCERO("Debe introducir Numero de bultos"),INCLUDECSS="height:26px;COLOR:DARKBLUE;font-style:bold;font-size:14pt;border-style:ridge;background-color:#F7BE81;",WPOSY=-2,WLONX=6
CAMPO=KILOS,INCLUDECSS="height:26px;COLOR:DARKBLUE;font-style:bold;font-size:14pt;border-style:ridge;background-color:#F7BE81;",WPOSY=-2,WLONX=6
#,POSTCHANGE=FVALNOCERO("Debe introducir los kilos")
CAMPO=OBSERV,REGPAG=5,INCLUDECSS="border-style:inset;border-width:2px;background-color:#FBE9C0"

CAMPO=CONTACTO
CAMPO=DIRECCION
CAMPO=DIRECCION1
CAMPO=DIRECCION2
CAMPO=DIRECCION3
CAMPO=POBLACION
CAMPO=CODPAIS,POSTCHANGE=FDESIGNACION("+CSELPAIS","No existe pa?"),COMBOX("CSELCOMBPAIS")
CAMPO=DESPAIS,AUXILIAR,NOENTER
CAMPO=CODPROV,POSTCHANGE=FDESIGNACION("+CSELDESPROV","No existe provincia"),COMBOX("CSELCOMBPROV"),COMBOXREGPAG=20
CAMPO=DESPROV,AUXILIAR,NOENTER
CAMPO=TELEFONO
CAMPO=CODOPEINS,NOENTER
CAMPO=FECINS,NOENTER
CAMPO=HORAINS,NOENTER
CAMPO=CODOPEVALIDA,NOENTER
CAMPO=FECVALIDA,NOENTER
CAMPO=HORAVALIDA,NOENTER
CAMPO=CODOPEPROTO,NOENTER
CAMPO=FECPROTO,NOENTER
CAMPO=HORAPROTO,NOENTER
CAMPO=CODOPEFIN,NOENTER
CAMPO=FECFIN,NOENTER
CAMPO=HORAFIN,NOENTER
CAMPO=STATUS,NOENTER,POSTCHANGE=FDESIGNACION("CSELSTATUS","No existe estado"),COMBOX("CSELCOMBSTATUS")
CAMPO=DESSTATUS,AUXILIAR,NOENTER
CAMPO=CODCOMEN,OCULTO,"@L@@@@@@@"
CAMPO=CODOPEMODIF,NOENTER
CAMPO=FECMODIF,NOENTER
CAMPO=HORAMODIF,NOENTER
CAMPO=NBULTO,AUXILIAR,NOUPDATE,OCULTO,"@L@"

CURSOR=CPONDIVIS SELECT '1' CODDIV FROM DUAL;                

CURSOR=CDIVNULL SELECT :CODDIV FROM DUAL WHERE :CODDIV IS NULL;

CURSOR=CLISTADIVIS SELECT CODDIV, DESDIV FROM VDDEVOLDIVIS ORDER BY DECODE(CODDIV,NULL,1,0),CODDIV;

CURSOR=CSELDIVIS SELECT DESDIV FROM VDDEVOLDIVIS WHERE NVL(CODDIV,'-') = NVL(:CODDIV,'-');

CURSOR=CSELCOMBSTATUS SELECT STATUS,DESSTATUS FROM VDSTATUS WHERE TIPOSTATUS='DVC' ORDER BY STATUS;

CURSOR=CSELCOMBPAIS SELECT CODPAIS,DESPAIS FROM VDPAIS;

CURSOR=CSELCOMBPROV SELECT DISTINCT CODPROV,DESPROV,PROV.CODPAIS,DESPAIS FROM VDPROVI PROV, VDPAIS PA 
                             WHERE PROV.CODPAIS=PA.CODPAIS AND PA.CODPAIS=NVL(:CODPAIS,'%') ORDER BY DECODE(CODPAIS,:CODPAIS,0,1),CODPROV;

CURSOR=CSELPAIS SELECT DESPAIS FROM VDPAIS WHERE CODPAIS=:CODPAIS OR :CODPAIS IS NULL;

CURSOR=CSELDESPROV SELECT DESPROV FROM VDPROVI PROV, VDPAIS PA 
                             WHERE PROV.CODPAIS=PA.CODPAIS AND CODPROV=:CODPROV AND PROV.CODPAIS=:CODPAIS;


CURSOR=CSELDESCLI SELECT DESCLIENTE FROM VDPEDIDOCAB WHERE CODCLIENTE=:CODCLIENTE AND ROWNUM=1 
                  UNION
                  SELECT DESCLIENTE FROM VDCLIENTES WHERE CODCLIENTE=:CODCLIENTE AND ROWNUM=1;

CURSOR=CSELSTATUS SELECT TO_NUMBER(:STATUS) STATUS,DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='DVC'
                   UNION
                  SELECT 100 STATUS,DESSTATUS FROM VDSTATUS WHERE :STATUS=0 AND TIPOSTATUS='DEC' AND STATUS=100;


CURSOR=CSELOPEINS SELECT VDSEQDEVOL.NEXTVAL SEQDEVOL,VDUSER.GETUSER CODOPEINS,VD.FECHASYS FECINS,VD.HORASYS HORAINS,50 STATUS,
                         VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF
                    FROM DUAL;

CURSOR=CBORRABULTO SELECT 0 NBULTO FROM DUAL;

CURSOR=CSELNBULTO SELECT TO_NUMBER(:NBULTO)+1 NBULTO FROM DUAL
                    WHERE :NBULTO<:NUMBULTOS;
                    
#TECLA=SF2,FEJECUTA("CBORRABULTO","",
#                    FWHILE("CSELNBULTO",
#                           FIF("CIMPREDEVOL",
#                               FIMPRIME("ETIQ","VDDEVOL.GEN;VDDEVOL.VSQ;CSELDEVOL","SEQDEVOL=:SEQDEVOL;NBULTO=:NBULTO",""),
#                               FSUCCESS),":V10ERROR"),":V10ERROR")
TECLA=SF2,FEJECUTA("CBORRABULTO","",
                    FWHILE("CSELNBULTO",
                           FIMPRIME("ETIQ","VDDEVOL.GEN;VDDEVOL.VSQ;CSELDEVOL","SEQDEVOL=:SEQDEVOL;NBULTO=:NBULTO",""),":V10ERROR"),":V10ERROR")


CURSOR=CSELDATOSCLI SELECT DESCLIENTE,CONTACTO,DIRECCION,DIRECCION1,DIRECCION2,DIRECCION3,POBLACION,TELEFONO,
                           PAI.CODPAIS,PAI.DESPAIS,PRO.CODPROV,PRO.DESPROV
                      FROM VDPEDIDOCAB CLI,VDPAIS PAI,VDPROVI PRO
                     WHERE CODCLIENTE=:CODCLIENTE AND CLI.CODPAIS=PAI.CODPAIS AND CLI.CODPROV=PRO.CODPROV AND ROWNUM=1;

CURSOR=CIMPREDEVOL SELECT :NUMCAJA FROM DUAL
                    WHERE VD.GETPROP('IMPRIMEDEVOL')='S';

CURSOR=CSELST SELECT :SEQDEVOL FROM DUAL
               WHERE :CODALBAST IS NULL OR (:CODALBAST IS NOT NULL AND :SWTPERITAJE IS NOT NULL);

TECLA=SF5,FEJECUTAFORM("VDCABDEVOL","S","SEQDEVOL=:SEQDEVOL","","")
                
CONTEXTUAL=FEJECUTAFORM("VDSELCLI","N","DESCLIENTE LIKE :DESCLIENTE||'%' GROUP BY CODDIV,CODCLIENTE,DESCLIENTE, DP,POBLACION,CONTACTO,DIRECCION,DIRECCION1,DIRECCION2,DIRECCION3,TELEFONO,CODPROV,CODPAIS UNION SELECT '1',CODCLIENTE,DESCLIENTE,DP,POBLACION,CONTACTO,DIRECCION,DIRECCION1,DIRECCION2,DIRECCION3,TELEFONO,CODPROV,CODPAIS,VD.FECHASYS MAXFECRECEP FROM VDCLIENTES WHERE TIPOCLI='DEVOL' AND DESCLIENTE LIKE :DESCLIENTE||'%'","","CODCLIENTE=:CODCLIENTE DESCLIENTE=:DESCLIENTE CONTACTO=:CONTACTO DIRECCION=:DIRECCION DIRECCION1=:DIRECCION1 DIRECCION2=:DIRECCION2 DIRECCION3=:DIRECCION3 POBLACION=:POBLACION TELEFONO=:TELEFONO CODPAIS=:CODPAIS CODPROV=:CODPROV")
                    

BOTON=SALIR,745,200,120,120,"Salir",vertis\vertissalir.png,27,"Salir de la pantalla" ,INCLUDECSS="border-style:outset;background-color:transparent"
BOTON=VALIDAR,745,330,120,120,"Confirmar",vertis\vertisguardar.png,F4,"Confirmar cambios" ,INCLUDECSS="border-style:outset;background-color:transparent"
BOTON=LIMPIAR,745,460,120,120,"Limpiar",vertis\vertislimpiar.png,F5,"Limpiar pantalla"   ,INCLUDECSS="border-style:outset;background-color:transparent"
BOTON=ESCANEAR,745,590,120,120,"Escanear",vertis\C?igo_barras.png,SF5,"Escanear devoluci?",INCLUDECSS="border-style:outset;background-color:transparent"

ONLINE= {F4} Confirmar {Esc} Salir {SF10} Men?                