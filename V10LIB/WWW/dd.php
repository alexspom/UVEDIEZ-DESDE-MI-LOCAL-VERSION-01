<?php

$c = oci_connect("ALLOGA", "ALLOGA", "DEVEL");

$s = oci_parse($c, 'select * from vdstatus');
oci_execute($s);
oci_fetch_all($s, $res);
echo "<pre>\n";
var_dump($res);
echo "</pre>\n";

?>