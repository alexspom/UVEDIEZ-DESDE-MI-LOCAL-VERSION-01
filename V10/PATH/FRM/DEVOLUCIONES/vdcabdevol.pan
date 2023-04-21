Mantenimiento de cabeceras de devolucion
    Código      #L####### Cliente _20____________ _40_________________________________________  Albarán ST: _20_____________
    División:   _20_ _40__________________________________________________                      
    Dev.cliente ____________________  Importe #L,####.## Unidades @L,@@@ Bultos @L,@@ Cajas Cliente: @L@
    Estado      @L@@@ _40________________________________
    Inserción       _______________ ¿D-MM-Y.YY ________ Validación    _______________ ¿D-MM-Y.YY ________
    Conf. Protocolo _______________ ¿D-MM-Y.YY ________ Finalización: _______________ ¿D-MM-Y.YY ________
    Observ. _255____________________________________________ Modifica:_______________ ¿D-MM-Y.YY ________
|

TABLA=VDDEVOLCAB
NOINSERT
WHERE=STATUS<=VDVST.FDVCESCANEADA;


CAMPO=SEQDEVOL,NOUPDATE,TOOLTIP("Código de la devolución"),TECLA=CR,FPULSATECLAS("F2","F6")
CAMPO=CODCLIENTE,UPPER,POSTCHANGE=FVALNOCERO("Debe introducir Código de cliente")
CAMPO=DESCLIENTE,UPPER,POSTCHANGE=FVALNOCERO("Debe introducir designación de cliente")
CAMPO=CODALBAST,NOENTER,TOOLTIP("Número de albarán de siniestro de transporte")
CAMPO=CODDIV,NOUPDATE,POSTCHANGE=FEJECUTA("+CSELDIVIS","")
CAMPO=DESDIV,AUXILIAR,NOENTER
CAMPO=CODDEVCLI
CAMPO=PRECIODEV
CAMPO=NUMUNI,NOUPDATE
CAMPO=NUMBULTOS
CAMPO=CAJASCLIENTE,NOUPDATE
CAMPO=STATUS,NOUPDATE,POSTCHANGE=FDESIGNACION("CSELSTATUS","No existe estado")
CAMPO=DESSTATUS,AUXILIAR,NOENTER
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
CAMPO=OBSERV,REGPAG=4,INCLUDECSS="border-style:inset;border-width:2px;background-color:#FBE9C0",WPOSY=4
CAMPO=CODOPEMODIF,NOENTER
CAMPO=FECMODIF,NOENTER
CAMPO=HORAMODIF,NOENTER
CAMPO=MENSAJE,AUXILIAR,OCULTO,"_100_"
#CAMPO=CODPRECINTOCITO,AUXILIAR,VIRTUAL,OCULTO
#CAMPO=CODPRECINTONORMAL,AUXILIAR,VIRTUAL,OCULTO
CAMPO=INFORMEPROTO,AUXILIAR,OCULTO,"_256_"
CAMPO=FICHEROPDF,AUXILIAR,OCULTO,"_256_"

CURSOR=CSELDIVIS SELECT DESDIV FROM VDDEVOLDIVIS WHERE NVL(CODDIV,'-') = NVL(:CODDIV,'-');

CURSOR=CSELSTATUS SELECT TO_NUMBER(:STATUS) STATUS,DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='DVC';
                    
CURSOR=CVALIDADEV  UPDATE VDDEVOLCAB SET STATUS = VDVST.FDVCESCANEADA, 
                                         CODOPEVALIDA  = VDUSER.GETUSER, FECVALIDA   = VD.FECHASYS, HORAVALIDA   = VD.HORASYS,
                                         CODOPEMODIF  = VDUSER.GETUSER, FECMODIF     = VD.FECHASYS, HORAMODIF    = VD.HORASYS
                      WHERE SEQDEVOL = :SEQDEVOL;

CURSOR=CCHECKDEVOL SELECT TO_NUMBER(:SEQDEVOL) SEQDEVOL FROM DUAL WHERE :SEQDEVOL > 0;

CURSOR=CHECKCANTIDAD SELECT TO_NUMBER(:NUMUNI) NUMUNI FROM DUAL WHERE :NUMUNI = (SELECT SUM(CANTIDAD) FROM VDDEVOLLIN WHERE SEQDEVOL=:SEQDEVOL); 
                   
CURSOR=CINCCAJASCLIENTE UPDATE VDDEVOLCAB SET    CAJASCLIENTE = NVL(CAJASCLIENTE,0) + 1,
                                                 CODOPEMODIF  = VDUSER.GETUSER,
                                                 FECMODIF     = VD.FECHASYS,
                                                 HORAMODIF    = VD.HORASYS
                                      WHERE SEQDEVOL = :SEQDEVOL;

CURSOR=CDAMEINFORMEPROTO SELECT INFORMEDIV INFORMEPROTO,'E:\V10\VERTIS\PATH\CORREOS\' || :CODDIV || '.' || :SEQDEVOL || '.PDF' FICHEROPDF FROM VDDEVOLDIVIS WHERE CODDIV=:CODDIV;

CURSOR=CINCCAJASCLIENTE2 SELECT TO_NUMBER(NVL(:CAJASCLIENTE,0)) + 1 CAJASCLIENTE FROM DUAL; 
                                     
CURSOR=CIMPREPROTOCOLO SELECT :INFORMEPROTO FROM DUAL
                        WHERE VD.GETPROP('IMPRIMEPROTOCOLO')='S';

CURSOR=CSELDVLAPTO SELECT :SEQDEVOL 
                     FROM VDDEVOLLIN
                    WHERE SEQDEVOL=:SEQDEVOL AND STATUS=VDVST.FDVLAPTO;
                                     

#TECLA=SF8,FEJECUTA("CCHECKDEVOL","DEBE SELECCIONAR UNA DEVOLUCION", 
#                   "CVALIDADEV","No puedo validar la devolucion",
#                   FCOMMIT,"Error en commit",                   
#                   "CDAMEINFORMEPROTO","ERROR AL OBTENER INFORME DE PROTOCOLO",
#                   FEXPORTA("INFORME",":INFORMEPROTO","FORMSEQDEVOL=:SEQDEVOL",":FICHEROPDF","1"),"ERROR",
# AQUI IRIA INSETAR EN LA TABLA DE CORREOS                   
#                   %FFAILURE,"LA DEVOLUCION HA FINALIZADO SU ESCANEO\n\n Y SE HA ENVIADO EL CORREO AL LABORATORIO",
#                   +FBORRAFORM,"Error al limpiar")    
                                                        
TECLA=SF5,FEJECUTA("CCHECKDEVOL","DEBE SELECCIONAR UNA DEVOLUCION", 
                   "CVALIDADEV","No puedo validar la devolucion",
                   FCOMMIT,"Error en commit",                   
                   FIF("CIMPREPROTOCOLO",
                       FEJECUTA(FIMPRIME("INFORME","DEVOLUCIONES.RPT","FORMSEQDEVOL=:SEQDEVOL","",""),"ERROR IMPRIMIENDO INFORME",
                                FIF("CSELDVLAPTO",FIMPRIME("INFORME","VDBOLETINBE.RPT","FORMSEQDEVOL=:SEQDEVOL","","")),""),
                       FSUCCESS),"ERROR IMPRIMIENDO PROTOCOLO",
                   +FBORRAFORM,"Error al limpiar")     
#%FFAILURE,"LA DEVOLUCION HA FINALIZADO SU ESCANEO",

TECLA=SF6,FEJECUTA("CCHECKDEVOL","DEBE SELECCIONAR UNA DEVOLUCION",                   
                   "CINCCAJASCLIENTE","ERROR INCREMENTANDO CAJAS CLIENTE",       
                   "+CINCCAJASCLIENTE2","",
                   FIMPRIME("ETIQ","VDDEVOLCLI.GEN;VDDEVOL.VSQ;CSELDEVOLCLI","SEQDEVOL=:SEQDEVOL",""),":V10ERROR",
                   FCOMMIT,"",
                   %FFAILURE,"Impresa Etiqueta de Caja Cliente") 
                                      
TECLA=SF3,FEJECUTA(FIMPRIME("ETIQ","VDDEVOLCLI.GEN;VDDEVOL.VSQ;CSELDEVOLCLI","SEQDEVOL=:SEQDEVOL",""),":V10ERROR")                                  
                    
BOTON=PROTO,940,70,80,80,"Confirmar Protocolo",vertis\vertislistado.png,SF5,"Valida devolución e imprime informe",INCLUDECSS="border-style:outset;background-color:transparent"
BOTON=SALIR,1040,70,80,80,"Salir",vertis\vertissalir.png,27,"Salir de la pantalla" ,INCLUDECSS="border-style:outset;background-color:transparent"
#BOTON=PROTO,840,70,80,80,"Confirmar Protocolo",vertis\vertislistado.png,SF5,"Finaliza devolución e imprime informe",INCLUDECSS="border-style:outset;background-color:transparent"
# BOTON=CORREO,940,70,80,80,"Confirmar Protocolo",vertis\vertismail.png,SF8,"Valida devolución y envío correo",INCLUDECSS="border-style:outset;background-color:transparent",BOTONDISABLED=1
#,BOTONDISABLED=1
