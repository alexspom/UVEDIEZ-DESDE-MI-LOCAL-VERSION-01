<?php

  //Script de subida de ficheros personalizado para RODAIR. Soluciona el bug de los ficheros corruptos.
  //(c) 2014 - Eduardo L. Arana.
  
  //Admitir rutas personalizadas desde el post. Control de errores. David De la Fuente.
  //Integración Ajax para la respuesta real de la subida del fichero. E. Arana.
  
  ini_set('display_errors', 1);
  ini_set('display_startup_errors', 1);
  error_reporting(E_ALL);
  
  $destination_path =$_POST['pathfichero'];   
  $result = '';   
  $target_path = $destination_path . basename(str_replace(' ', '_', $_FILES['DESDIV']['name']));  
  //*** nos conectamos a la bbdd ***//  
  $conn = oci_connect("ALLOGA", "ALLOGA", "DEVEL");  
	   
  //*** definimos los comandos de insert ***//
  $strSQL = "INSERT INTO VDCOMEN ";
  $strSQL .="(TIPOCOMEN,CODCOMEN, LINCOMEN,COMENTARIO,NOTIFICAR,CODOPEMODIF) ";
  $strSQL .="VALUES ";
  $strSQL .="('FICHEROS', ".$_POST['insertcomentario'].",VDSECSUBIDA.NEXTVAL,'".str_replace(' ', '_', $_FILES['DESDIV']['name'])."','N','PHP') ";
  if($_FILES['DESDIV']['name'] <> '')
   {
    $objParse = oci_parse($conn, $strSQL);
    $objExecute = oci_execute($objParse, OCI_DEFAULT);
    if($objExecute)
     {    
	  oci_commit($conn); //*** Hacemos Commit ***//
	  if(@move_uploaded_file(str_replace(' ', '_', $_FILES['DESDIV']['tmp_name']), $target_path)) {
	     $result = 1;	  	   	  
         }
      $result=1;		 
	  }
      else 
      {	 
	    oci_rollback($conn); //*** En caso de error naranjas de la china (rollback) ***//
	    $m = oci_error($objParse); 	  	
		$result=0;
      }
   }
  //*** Cerramos la conexión tras la subida ***//
  oci_close($conn);
   
  sleep(1);  
  
?>

<script language="javascript" type="text/javascript">
  window.parent.window.stopUpload(<?php echo $result; ?>);
</script>   


