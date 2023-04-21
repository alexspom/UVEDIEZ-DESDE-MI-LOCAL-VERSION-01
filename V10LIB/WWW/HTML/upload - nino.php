<?php
	//Script de subida de ficheros personalizado para RODAIR. Soluciona el bug de los ficheros corruptos.
	//(c) 2014 - Eduardo L. Arana.
	//Última modificación: 09/06/2015 para Decopharma
	
	// definimos la ruta de destino, donde copiaremos el fichero.
	
	
   $destination_path = "E://V10//productos//V10v20190613//V10//FICHEROS".DIRECTORY_SEPARATOR;

   $result = 0;
   
   $target_path = $destination_path . basename(str_replace(' ', '_', $_FILES['DESDIV']['name']));
   
   if(@move_uploaded_file(str_replace(' ', '_', $_FILES['DESDIV']['tmp_name']), $target_path)) {
	  $result = 1;
   }
   
   	//*** nos conectamos a la bbdd ***//
$conn = oci_connect("ALLOGA", "ALLOGA", "LOCAL");

//*** definimos los comandos de insert ***//
$strSQL = "INSERT INTO VDCOMEN ";
$strSQL .="(TIPOCOMEN,CODCOMEN, LINCOMEN,COMENTARIO,NOTIFICAR,CODOPEMODIF) ";
$strSQL .="VALUES ";
$strSQL .="('FICHEROS', ".$_POST['insertcomentario'].",VDSECSUBIDA.NEXTVAL,'".str_replace(' ', '_', $_FILES['DESDIV']['name'])."','N','PHP') ";


$objParse = oci_parse($conn, $strSQL);
$objExecute = oci_execute($objParse, OCI_DEFAULT);
if($objExecute)
{
	oci_commit($conn); //*** Hacemos Commit ***//
}
else
{
	oci_rollback($conn); //*** En caso de error naranjas de la china (rollback) ***//
	$m = oci_error($objParse); 
}

//*** Cerramos la conexión tras la subida ***//
oci_close($conn);
   
   sleep(1);
?>

<script language="javascript" type="text/javascript">window.top.window.stopUpload(<?php echo $result; ?>);</script>   
