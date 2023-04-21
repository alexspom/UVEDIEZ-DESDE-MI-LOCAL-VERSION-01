Mantenimiento de cabeceras de devolucion
    Código      #L####### Cliente _20____________ _40_________________________________________
    División:   _20__ _40__________________________________________________
    Dev.cliente ____________________  Importe #L,####.## Unidades @L,@@@ Bultos @L,@@ Cajas Cliente: @L@
    Estado      @L@@@ _40________________________________
    Inserción   _______________ ¿D-MM-Y.YY ________ Validación    _______________ ¿D-MM-Y.YY ________
    Conf. Prot. _______________ ¿D-MM-Y.YY ________ Finalización: _______________ ¿D-MM-Y.YY ________
    Observ. _255____________________________________________ Modifica:_______________ ¿D-MM-Y.YY ________
|

TABLA=VDDEVOLCAB
NOINSERT


CAMPO=SEQDEVOL,NOUPDATE,TOOLTIP("Código de la devolución"),TECLA=CR,FPULSATECLAS("F2","F6")
CAMPO=CODCLIENTE,UPPER,POSTCHANGE=FVALNOCERO("Debe introducir Código de cliente")
CAMPO=DESCLIENTE,UPPER,POSTCHANGE=FVALNOCERO("Debe introducir designación de cliente")
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
CAMPO=MENSAJE,AUXILIAR,OCULTO,"_100_"
CAMPO=CODOPEMODIF,NOENTER
CAMPO=FECMODIF,NOENTER
CAMPO=HORAMODIF,NOENTER
CURSOR=CSELDIVIS SELECT DESDIV FROM VDDEVOLDIVIS WHERE NVL(CODDIV,'-') = NVL(:CODDIV,'-');

CURSOR=CSELSTATUS SELECT TO_NUMBER(:STATUS) STATUS,DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='DVC';
   
CURSOR=CUPDDEVOLCAB UPDATE VDDEVOLCAB SET STATUS=VDVST.FDVCVALPROTO, 
                                          CODOPEPROTO=VDUSER.GETUSER, FECPROTO = VD.FECHASYS, HORAPROTO = VD.HORASYS,
                                          CODOPEMODIF = VDUSER.GETUSER, FECMODIF = VD.FECHASYS, HORAMODIF = VD.HORASYS 
                                       WHERE STATUS=VDVST.FDVCPDTEPROTO AND SEQDEVOL=:SEQDEVOL;


TECLA=SF4,FEJECUTA("CUPDDEVOLCAB", "",
                    FCOMMIT,"",
                    %FFAILURE,"DEVOLUCION :SEQDEVOL CONFIRMADA PROTOCOLO",
                    FPULSATECLAS("CF2","F2"))
                                       
BOTON=SALIR,960,70,120,120,"Salir",vertis\vertissalir.png,27,"Salir de la pantalla" ,INCLUDECSS="border-style:outset;background-color:transparent"
BOTON=SALIR,820,70,120,120,"Confirmar Protocolo",vertis\confproto.png,SF4,"Confirmar Protocolo de la Devolución",INCLUDECSS="border-style:outset;background-color:transparent"


