#CERRAR PRECINTOS
CERRAR PRECINTOS


 Precinto  Tipo                 Ubicación    Creado por
 _________ _25_________________ _20_________ _15____________ ¿D-MM-Y.YY ________
                      
|

SOLOQUERY
NOINSERT
NOUPDATE
NODELETE


INCLUDEFICHEROCSS="vertis.css"
INCLUDECSS=".v10tabla td{height:34px;}"
INCLUDEFICHEROHTML="botoneratactil.html"
INCLUDEHTML="<SCRIPT> var eventoforzado=1; window.document.getElementById('tactil').style.top=550+'px'; window.document.getElementById('tactil').style.left=970+'px'; </SCRIPT>"


SELECT=SELECT CODPRECINTO,CODUBI,TIPOPRECINTO,FECINS,HORAINS,CODOPEINS
          FROM VDPRECINTO PR
          WHERE PR.STATUS=VDVST.FPRCABIERTO;
        
#PREUPDATE=FEJECUTA("@CHAYNUEVO","",
#                   "-CNOUSADO","Precinto ya ha sido usado",
#                   "CCIERRAVIEJO","No puedo cerrar el precinto antiguo",
#                   "CINSERTANUEVO","No puedo insertar nuevo precinto")
        
CAMPO=CODPRECINTO,NOUPDATE,TITULO("Precinto")
CAMPO=TIPOPRECINTO,NOUPDATE,TITULO("Tipo"),WLONX=80
CAMPO=CODUBI,TITULO("Ubicación")
CAMPO=CODOPEINS,NOUPDATE,TITULO("Ult. Modificación")
CAMPO=FECINS,NOUPDATE
CAMPO=HORAINS,NOUPDATE

#CURSOR=CHAYNUEVO SELECT :CODPRECINTONUEVO FROM DUAL WHERE :CODPRECINTONUEVO IS NOT NULL;
#
#CURSOR=CNOUSADO SELECT :CODPRECINTONUEVO FROM VDPRECINTO WHERE CODPRECINTO=:CODPRECINTONUEVO;
#
#CURSOR=CCIERRAVIEJO UPDATE VDPRECINTO SET  STATUS=VDST.FPRCCERRADO,
#                                           CODOPECIERRA=VDUSER.GETUSER,
#                                           FECCIERRA=VD.FECHASYS,
#                                           HORACIERRA=VD.HORASYS,
#                                           CODOPEMODIF=VDUSER.GETUSER,
#                                           FECMODIF=VD.FECHASYS,
#                                           HORAMODIF=VD.HORASYS
#                            WHERE CODPRECINTO=:CODPRECINTO;
#             
#CURSOR=CDAMEUNPRECINTO SELECT VDSEQPRECINTO.NEXTVAL CODPRECINTONUEVO FROM DUAL;			 
#
#CURSOR=CINSERTANUEVO  INSERT INTO VDPRECINTO(CODPRECINTO,TIPOPRECINTO,STATUS,CODOPEMODIF,FECMODIF,HORAMODIF,
#                                              CODOPEINS,FECINS,HORAINS,CODOPECIERRA,FECCIERRA,HORACIERRA,CODOPEDESTRUYE,FECDESTRUYE,HORADESTRUYE,CODCOMEN)
#                            VALUES (:CODPRECINTONUEVO,:TIPOPRECINTO,VDST.FPRCABIERTO,VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS,
#                                    VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS,'',0,'','',0,'',0);                            
#
#        

TECLA=F4,FPULSATECLAS("F6","F4")
#TECLA=10000,FPULSATECLAS("F4","ESC")
#TECLA=10001,FEJECUTA("+CDAMEUNPRECINTO","")
#
BOTON=SALIR,1050,120,120,120,"Salir",vertis\vertissalir.png,27,"Salir de la pantalla" ,INCLUDECSS="border-style:outset;background-color:transparent"
BOTON=VALIDAR,1050,260,120,120,"Cerrar Precinto",vertis\vertiscerrar.png,F4,"Cerrar el precinto" ,INCLUDECSS="border-style:outset;background-color:transparent"
ONLINE={F4} Confirmar {Esc} Salir;