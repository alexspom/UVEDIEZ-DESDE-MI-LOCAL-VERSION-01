#CAMBIAR PRECINTO
CAMBIAR PRECINTO









  Precinto Antiguo _________ _25__________________ 
                             _20_________
   
  
  
  
  
  
          
  Precinto Nuevo   _________ 
                       
|

INCLUDEFICHEROCSS="vertis.css"
INCLUDECSS=".v10tabla td{height:34px;} .v10fieldset label{font-family:Tahoma;font-size:28pt;padding:0px 0px 0px 0px;color:#2E2E2E;position:absolute;overflow:visible;}"
INCLUDEFICHEROHTML="botoneratactil.html"
INCLUDEHTML="<SCRIPT> window.document.getElementById('tactil').style.top=550+'px'; window.document.getElementById('tactil').style.left=970+'px'; </SCRIPT>"

TABLA=DUAL
NOLOCK
NOORAINS
NOINSERT
NOUPDATE
NODELETE
NOCOMMIT
POSY=3
POSX=3
WPOSY=50
WLONX=1250
WLONY=860




CAMPO=CODPRECINTOANT,AUXILIAR,POSTCHANGE=FDESIGNACION("CSELPRECINTO","No existe precinto"),WPOSX=180,WLONX=130,INCLUDECSS="HEIGHT:46px;font-family:Tahoma;font-size:28pt;",
                             CONTEXTUAL=FEJECUTAFORM("VDPRECINTO","N","STATUS <= VDVST.FPRCDESTRUIDO","","CODPRECINTOANT=:CODPRECINTO","","S")
                             
CAMPO=TIPOPRECINTO,AUXILIAR,NOENTER,WPOSX=305,WLONX=260,INCLUDECSS="HEIGHT:46px;font-family:Tahoma;font-size:28pt;"
CAMPO=CODUBI,AUXILIAR,NOENTER,INCLUDECSS="HEIGHT:46px;font-family:Tahoma;font-size:28pt;",WLONX=180,WPOSX=305,WPOSY=36
CAMPO=CODPRECINTONUEVO,AUXILIAR,WPOSX=180,WLONX=130,INCLUDECSS="HEIGHT:46px;font-family:Tahoma;font-size:28pt;"
#,POSTCHANGE=FDESIGNACION("-CSELPRECNUEVO","Precinto ya existe o es NULO"

CURSOR=CSELPRECINTO SELECT TIPOPRECINTO,CODUBI FROM VDPRECINTO WHERE CODPRECINTO=:CODPRECINTOANT;

CURSOR=CCREAPRECINTONUEVO INSERT INTO VDPRECINTO (SELECT  :CODPRECINTONUEVO,STATUS,CODUBI,CODOPEINS,FECINS,HORAINS,
                                                          CODOPECIERRA,FECCIERRA,HORACIERRA,CODOPEDESTRUYE,FECDESTRUYE,HORADESTRUYE,
                                                          CODOPEINVEN,FECINVEN,HORAINVEN,VDSECCOMEN.NEXTVAL,VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS,
                                                          :TIPOPRECINTO FROM
                                                    VDPRECINTO WHERE CODPRECINTO = :CODPRECINTOANT); 
                                                          
CURSOR=CBORRAPRECINTOANT DELETE VDPRECINTO WHERE CODPRECINTO=:CODPRECINTOANT;                        
                           
CURSOR=CSELPRECNUEVO SELECT :CODPRECINTONUEVO FROM VDPRECINTO WHERE CODPRECINTO=:CODPRECINTONUEVO;

CURSOR=CCAMBIAPREC UPDATE VDDEVOLLIN SET CODPRECINTO=:CODPRECINTONUEVO WHERE CODPRECINTO=:CODPRECINTOANT;
                  
CURSOR=CSELPRECINTONULO SELECT :CODPRECINTONUEVO FROM DUAL WHERE :CODPRECINTONUEVO IS NULL;


TECLA=F4,FEJECUTA("-CSELPRECNUEVO","Precinto ya existe",
                  "-CSELPRECINTONULO","Precinto es NULO",
                  "CCREAPRECINTONUEVO","ERROR EN CCREAPRECINTONUEVO",
                  "CCAMBIAPREC","No puedo cambiar el precinto",
                  "CBORRAPRECINTOANT","ERROR EN CBORRAPRECINTOANT",                  
                  FIMPRIME("ETIQ","VDPRECINTO.GEN;VDPRECINTO.VSQ;CSELPRECINTO","CODPRECINTO=:CODPRECINTONUEVO",""),":V10ERROR",
                  FCOMMIT,"",%FFAILURE,"Cambio Realizado",FPULSATECLAS("F5"))


BOTON=SALIR,1050,120,120,120,"Salir",vertis\vertissalir.png,27,"Salir de la pantalla" ,INCLUDECSS="border-style:outset;background-color:transparent"
BOTON=VALIDAR,1050,280,120,120,"Confirmar",vertis\vertisok.png,F4,"Confirmar cambios"  ,INCLUDECSS="border-style:outset;background-color:transparent"
ONLINE={F4} Confirmar {Esc} Salir;
