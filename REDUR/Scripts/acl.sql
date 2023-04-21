--ojo ejecutar como sys

exec DBMS_NETWORK_ACL_ADMIN.DROP_ACL ( 'v10acl1.xml');


begin
 DBMS_NETWORK_ACL_ADMIN.create_acl (
    acl          => 'v10acl1.xml', --Aquí definimos un fichero xml donde se va a almacenar la información de los permisos de red a un usuario.
    description  => 'Información de los permisos al usuario para los procesos de V10',
    principal    => 'ALC', --Aquí va el usuario del esquema en el que queremos activarlo
    is_grant     => TRUE, 
    privilege    => 'connect',
    start_date   => SYSTIMESTAMP,
    end_date     => NULL);
end;

BEGIN
DBMS_NETWORK_ACL_ADMIN.add_privilege ( 
    acl         => 'v10acl1.xml', 
    principal   => 'ALC', --Aquí va el usuario del esquema en el que queremos activarlo
    is_grant    => TRUE, 
    privilege   => 'resolve', 
    position    => NULL, 
    start_date  => NULL,
    end_date    => NULL);
end;    

begin
  DBMS_NETWORK_ACL_ADMIN.assign_acl (
    acl         => 'v10acl1.xml',
    host        => 'mail.191.biz', --Aquí va el servidor de correo electrónico saliente, si solo se quiere dar acceso a un servicio como por ejemplo envío de emails.
    lower_port  => null, --Aquí definimos el puerto inicial o si lo ponemos a null todos los puertos son validos.
    upper_port  => null); --Aquí si va a NULL se toma como limite el puerto lower.
end;

begin
  DBMS_NETWORK_ACL_ADMIN.assign_acl (
    acl         => 'v10acl1.xml',
    host        => 'gprs.nacex.com', --Aquí va el servidor de correo electrónico saliente, si solo se quiere dar acceso a un servicio como por ejemplo envío de emails.
    lower_port  => null, --Aquí definimos el puerto inicial o si lo ponemos a null todos los puertos son validos.
    upper_port  => null); --Aquí si va a NULL se toma como limite el puerto lower.
end;

begin
  DBMS_NETWORK_ACL_ADMIN.assign_acl (
    acl         => 'v10acl1.xml',
    host        => 'gprs.nacex.com', 
    lower_port  => 80, 
    upper_port  => NULL); 
end;



 
 
