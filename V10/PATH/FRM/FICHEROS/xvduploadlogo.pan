# Módulo   : XVDUPLOAD.PAN
# Función  : 
## Creación : 13-03-2014
# Autor    : RIK
# Fichero generado por el Asistente de Generación de Pantallas V10 
###########################################
# Histórico de cambios:
ADJUNTAR LOGO DIVIS                                                                         
Id   #L#########
|

TABLA=DUAL
WLONY=100
WLONX=720
UPPER
CAMPO=CODCOMEN,VIRTUAL,NOUPDATE,AUXILIAR,POSTCHANGE=FDESIGNACION("CSELCAMPOHTL","")
CAMPO=CODTABLA,VIRTUAL,NOUPDATE,OCULTO,AUXILIAR 
CAMPO=CODDIV,VIRTUAL,AUXILIAR,OCULTO
CAMPO=FICHERO,AUXILIAR,NOUPDATE,OCULTO,"_1020_"

CAMPO=V10HTML,AUXILIAR,OCULTO,"_2048_"


CURSOR=CSELCAMPOHTL BEGIN
                         SELECT '<table id="tablaSubida"  width="400" style="position:absolute;top:92px;left:0px;z-index:9000" cellpadding="0" cellspacing="5">
                         <tr height="10">
                         <th>
                           <form name="form1" method="post" enctype="multipart/form-data">
                                <input name="campo" id="campo" type="hidden" tabindex="0" value="FICHERO"/>
                                <input name="accion" id="accion" type="hidden" tabindex="0" value="3000"/>
                                <input hidefocus="hidefocus" unselectable="on"   
                                 style=" width:600px;height=22px;margin-left:21px;background-color:white;font-color:Black;font-size:12px" 
                                 type="file" name="DESDIV" id="miid" />                                
                                <input type="button" name="Submit" value="Subir Fichero" style="position:absolute;top:40px;left:540px;height:22px;width:98px;"
                                id="miid" onclick="window.document.body.onclick='''';
                                         v10lib.fuerzocierre=true;
                                         document.form1.submit();
                                         window.document.body.onclick=''v10lib.fonclick()'';"/>
                           </form>
                        </th>
                        </tr>
                           </table>' INTO :V10HTML FROM DUAL;
                    END;@


CURSOR=CUPDFICHE  DECLARE 
                     MILINCOMEN NUMBER; 
                   BEGIN
                      SELECT NVL(MAX(LINCOMEN),0)+1 INTO MILINCOMEN FROM VDCOMEN WHERE CODCOMEN=:CODCOMEN AND TIPOCOMEN='FICHEROS';  
                      VDCOM.CREACOMEN(:CODTABLA,:CODCOMEN,'FICHEROS',MILINCOMEN,:FICHERO);
                  END;@    
CURSOR=CSELIMG SELECT :FICHERO FROM DUAL WHERE SUBSTR(:FICHERO,LENGTH(:FICHERO)-2) IN ('JPG','jpg','PNG','png','BMP','bmp');
 
CURSOR=CARGALOGO BEGIN
                    XVDROD.CARGAIMG(:CODDIV,:FICHERO);
                 END;@
                  
TECLA=3000,FDESIGNACION("CSELIMG","TIPO DE IMAGEN NO VALIDO",
                         "CARGALOGO","ERROR CARGANDO LOGO",
                         "CUPDFICHE","ERROR ACTUALIZANDO FICHERO",
                         FCOMMIT,"",
                        "CSELCAMPOHTL","",
                        %FFAILURE,"FICHERO SUBIDO :FICHERO",
                        FPULSATECLAS("ESC"),"")

TECLA=9999,FDESIGNACION(%FFAILURE,"ERROR AL SUBIR FICHERO ... :FICHERO")


ONLINE={F4} Grabar cambios {May+F10} Consultas {Esc} Salir;