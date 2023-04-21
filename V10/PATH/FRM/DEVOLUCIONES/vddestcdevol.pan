DESTRUCCION DE DEVOLUCIONES VALIDADAS
  
  ÏÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ?Devoluci? ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ‘
  ?C?igo             @L@@@@@@@                               ?
  ?                                                           ? 
  ?Div.  _20__ _40_____________________________________        ?
  ?                                                           ? 
  ?Cliente            _20____________ _60_____________________?
  ?                                                           ?
  ?Devolucion cliente ____________________                    ?
  ?ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ?  
  ÏÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ?Seguimiento  ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ‘  
  ?Estado     @L@@@ _40________________________________       ? Observaciones 
  ?                                                           ?    _255______________________________________________ 
  ?Inserci?  _______________ ?-MM-Y.YY ________             ?  
  ?Validaci? _______________ ?-MM-Y.YY ________             ?
  ?Conf. Prot._______________ ?-MM-Y.YY ________             ?
  ?Fin        _______________ ?-MM-Y.YY ________             ?
  ?Ult.Modif  _______________ ?-MM-Y.YY ________             ?
  ?ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ?
  
|

TABLA=VDDEVOLCAB
WHERE= STATUS >= VDVST.FDVCESCANEADA AND EXISTS (SELECT 1 FROM VDDEVOLLIN DVL WHERE DVL.SEQDEVOL=VDDEVOLCAB.SEQDEVOL AND DVL.STATUS = VDVST.FDVLDEVCLIENTE AND DVL.FECDESTRUYE=0);
NOINSERT
NODELETE

PREINSERT=FDESIGNACION("CSELOPEINS")

CAMPO=SEQDEVOL,NOUPDATE,TOOLTIP("C?igo de la devoluci?"),TECLA=CR,FPULSATECLAS("F2"),INCLUDECSS="height:16px;COLOR:DARKBLUE;font-style:bold;border-style:ridge;background-color:#F7BE81;",WLONX=6
CAMPO=CODDIV,COMBOX("CLISTADIVIS"),NOUPDATE,POSTCHANGE=FEJECUTA("+CSELDIVIS","")
CAMPO=DESDIV,AUXILIAR,NOENTER
CAMPO=CODCLIENTE,UPPER,POSTCHANGE=FVALNOCERO("Debe introducir C?igo de cliente"),INCLUDECSS="height:16px;COLOR:DARKBLUE;font-style:bold;border-style:ridge;background-color:#F7BE81;",WLONX=6
CAMPO=DESCLIENTE,UPPER,POSTCHANGE=FVALNOCERO("Debe introducir designaci? de cliente")
CAMPO=CODDEVCLI
CAMPO=STATUS,POSTCHANGE=FDESIGNACION("CSELSTATUS","No existe estado"),NOENTER
CAMPO=DESSTATUS,AUXILIAR,NOENTER  
CAMPO=OBSERV,REGPAG=5,INCLUDECSS="border-style:inset;border-width:2px;background-color:#FBE9C0"
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
CAMPO=CODOPEMODIF,NOENTER
CAMPO=FECMODIF,NOENTER
CAMPO=HORAMODIF,NOENTER
CAMPO=MENSAJE,AUXILIAR,OCULTO,"_200"

CURSOR=CSELDIVIS SELECT DESDIV FROM VDDEVOLDIVIS WHERE NVL(CODDIV,'-') = NVL(:CODDIV,'-');


CURSOR=CSELSTATUS SELECT TO_NUMBER(:STATUS) STATUS,DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='DVC';


CURSOR=CSELOPEINS SELECT VDSEQDEVOL.NEXTVAL SEQDEVOL,VDUSER.GETUSER CODOPEINS,VD.FECHASYS FECINS,VD.HORASYS HORAINS,100 STATUS
                    FROM DUAL;
                    
CURSOR=CDUMMY SELECT TO_NUMBER(:SEQDEVOL) SEQDEVOL FROM DUAL WHERE 1=1;
                  
CURSOR=CDESTDEVOL  UPDATE VDDEVOLLIN SET CODOPEDESTRUYE=VDUSER.GETUSER,FECDESTRUYE=VD.FECHASYS,HORADESTRUYE=VD.HORASYS 
                                      WHERE STATUS=VDVST.FDVLDEVCLIENTE AND FECDESTRUYE=0 AND SEQDEVOL=:SEQDEVOL; 

CURSOR=CCHECKDEVOL SELECT TO_NUMBER(:SEQDEVOL) FROM DUAL WHERE NVL(:SEQDEVOL,0) > 0;
                                            
TECLA=SF5,FEJECUTA("CCHECKDEVOL","DEBE SELECCIONAR UNA DEVOLUCION",
                   "!CDUMMY","?Est?seguro de destruir la mercanc? no abonable de la devoluci? ?",
                   "CDESTDEVOL","No puedo destruir la devolucion",                   
                   FCOMMIT,"Error en commit",
                   %FFAILURE,"FINALIZADA DESTRUCCION DE LA DEVOLUCION",
                   +FBORRAFORM,"Error en limpia")  
                   
                    

BOTON=SALIR,980,150,100,50,"Salir",NO,27,"Salir de la pantalla" 
BOTON=VALIDAR,980,210,100,50,"Confirmar",NO,F4,"Confirmar cambios" 
BOTON=CONSULTAR,980,270,100,50,"Consultar",NO,F2,"Consultar"   
BOTON=LIMPIAR,980,330,100,50,"Limpiar",NO,F5,"Limpiar"         
BOTON=DESTRUIR,650,155,100,80,"Destruir >>",NO,SF5,"Destruir lineas no abonables de la devoluci?"      
      

