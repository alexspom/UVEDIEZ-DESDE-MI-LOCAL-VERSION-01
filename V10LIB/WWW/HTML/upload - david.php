<?php
  //Script de subida de ficheros personalizado para RODAIR. Soluciona el bug de los ficheros corruptos.
  //(c) 2014 - Eduardo L. Arana.
  //Última modificación: 09/06/2015 para Decopharma
	
  // definimos la ruta de destino, donde copiaremos el fichero.
  //$destination_path = "E://ALLOGA//V10DATOS//INCIDENCIAS".DIRECTORY_SEPARATOR;
  //CAMBIAMOS LA VARIABLE DESTINO POR UN PARAMETRO DEL "FORM"
  
  ini_set('display_errors', 1);
  ini_set('display_startup_errors', 1);
  error_reporting(E_ALL);
  
  $destination_path =$_POST['pathfichero'];   
  $result = 0;   
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
      print ("<h2>Fichero adjuntado de forma correcta</h2> <br> <h3> Puede cerrar esta ventana</h3>");		 
      
	  }
      else 
      {	 
	    oci_rollback($conn); //*** En caso de error naranjas de la china (rollback) ***//
	    $m = oci_error($objParse); 	  	  
		print ("<h1>Error</h1> <h2> al adjuntar el fichero</h2> <br> <h3> Pongase en contacto con sistemas si el archivo no se ha copiado a la carpeta correspondiente</h3>");		 
      }
   }
  //*** Cerramos la conexión tras la subida ***//
  oci_close($conn);
   
  sleep(1);  
?>


