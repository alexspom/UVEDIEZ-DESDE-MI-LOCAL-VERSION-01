# Módulo   : XVDUPLOAD.PAN
# Función  : 
#
# Creación : 09-09-2014
# Autor    : Eduardo L. Arana
# Pantalla personalizada que utiliza PHP y Apache para la subida de ficheros.
###########################################
# Explicación de funciones:
ADJUNTAR FICHEROS   

 Comentario #L#########
   
|

TABLA=DUAL
WLONY=150
WLONX=420
CAMPO=CODCOMEN,VIRTUAL,NOUPDATE,AUXILIAR,POSTCHANGE=FEJECUTA("CSELCAMPOHTL","")
CAMPO=CODTABLA,VIRTUAL,NOUPDATE,OCULTO,AUXILIAR 
CAMPO=PATHFICHERO,VIRTUAL,OCULTO,AUXILIAR
CAMPO=V10HTML,AUXILIAR,OCULTO,"_4000_"


CURSOR=CSELCAMPOHTL BEGIN
                         SELECT '
						 <script languaje="javascript">
							function startUpload(){
								document.getElementById(''muestramensaje'').style.visibility = ''hidden'';
								return true;
							}
							
							function stopUpload(success){
								var result = '''';
								if (success == 1){
									result = ''<p style="font-size:20px;"><b>Fichero adjuntado de forma correcta.</b><\/p><br/>'';
								}
								else {
									result = ''<p style="font-size:13px;color:red;">Error al adjuntar el fichero. Pongase en contacto con sistemas si el archivo no se ha copiado a la carpeta correspondiente<\/p>'';
								}
								document.getElementById(''muestramensaje'').innerHTML = result + ''<input style="background-color:white;font-color:Black;font-size:12px" type="file" name="DESDIV" id="fichero"><input type="submit" name="submitBtn" class="sbtn" value="Adjuntar" id="miid" style="background-color:white;font-color:Black;font-size:12px"/>'';
								document.getElementById(''muestramensaje'').style.visibility = ''visible'';      
								return true;   
							}
							</script>
						 <table id="tablaSubida" width="400" style="position:absolute;top:125px;left:10px;z-index:10;" cellpadding="0" cellspacing="5">
									<tr height="10">
									<th>
										<form name="form1" id="form1" action="../html/upload.php" method="post" enctype="multipart/form-data" target="upload_target" onsubmit="startUpload();">
											<label1>
											<p id="muestramensaje" style="z-index:999" align="center"><br/>
												<input type="hidden" value="'||:CODCOMEN||'" id="inputcomentario" name="insertcomentario">
												<input type="hidden" value="'||:PATHFICHERO||'" id="path" name="pathfichero">
											    <input style="height=22px;margin-left:21px;background-color:white;font-color:Black;font-size:12px" type="file" name="DESDIV" id="fichero" required>
											</label1>
											<label1>											   
											    <input type="submit" name="submitBtn" class="sbtn" value="Adjuntar" id="miid"
         										 	   style="background-color:white;font-color:Black;font-size:12px"/>
											</label1>  
											<div id="image_details"></div>				
										   <iframe id="upload_target" name="upload_target" src="#" style="width:0;height:0;border:0px solid #fff;"></iframe>
										</form>
										 
									</th>
									</tr>									
								</table>'
							 INTO :V10HTML FROM DUAL;
                    END;@	


