# Módulo   : VDWHERE.PAN
# Función  : Mantenimiento de consultas pregrabadas
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
MANTENIMIENTO DE CONSULTAS PREGRABADAS
 Usuario    Pantalla
 __________ _255___________________________________________________________________________ 

 Título
 ______________________________________________________

 Where
 _2000_____________________________________________________________________________________

 Order
 _2000_____________________________________________________________________________________

 Having
 _2000_____________________________________________________________________________________

 Ultima modificación
 _32_________ ¿D-MM-Y.YY  ________
|

TABLA=VDWHERE
ORDERBY=PANTALLA,CODOPE;


PREINSERT=FEJECUTA("CSELMODIF","ERROR INSERTANDO ULTIMA MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR ACTUALIZANDO ULTIMA MODIFICACION")

POSTQUERY=FEJECUTA("CSELCAMPOHTL","")

CAMPO=CODOPE,TOOLTIP("Usuario que define la consulta")
CAMPO=PANTALLA,TOOLTIP("Pantalla en la que se define la consulta")
CAMPO=TITULOWHERE,TOOLTIP("Título de la consulta")
CAMPO=TEXTOWHERE,TOOLTIP("Texto de la where de la consulta"),REGPAG=2
CAMPO=TEXTOORDER,TOOLTIP("Texto del order de la consulta"),REGPAG=2
CAMPO=TEXTOHAVING,TOOLTIP("Texto del having de la consulta"),REGPAG=2
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")
CAMPO=FICHERO,AUXILIAR,OCULTO,"_100"
CAMPO=V10HTML,AUXILIAR,OCULTO,"_2048_"

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;


CURSOR=CSELCAMPOHTL BEGIN
                         SELECT '<table id="tablaSubida"  width="400" style="position:absolute;top:70px;left:550px;z-index:9000" cellpadding="0" cellspacing="5">
                         <tr height="50">
                         <th><script type="text/javascript">
                               function foco() {
                                   window.document.body.onclick='''';
                               }
                               function quitafoco() {
                                    window.document.body.onclick=''v10lib.fonclick()'';
                               }
                           </script>
                           <form name="form1" method="post" enctype="multipart/form-data">
                                <input name="campo" id="campo" type="hidden" tabindex="0" value="FICHERO"/>
                                <input name="accion" id="accion" type="hidden" tabindex="0" value="3000"/>
                                <input onclick="foco()" onblur="quitafoco()" style="margin-left:100px;margin-top:15px;background-color:WHITE;font-color:BLACK;" type="file" name="DESDIV" id="miid"/>
                                <input type="button" name="Submit" value="Subir Fichero"
                                onclick="window.document.body.onclick='''';
                                         v10lib.fuerzocierre=true;
                                         document.form1.submit();
                                         window.document.body.onclick=''v10lib.fonclick()'';"/>
                           </form>
                        </th>
                        </tr>
                           </table>' INTO :V10HTML FROM DUAL;
                           END;@


