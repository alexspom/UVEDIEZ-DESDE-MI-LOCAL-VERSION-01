

exec DBMS_NETWORK_ACL_ADMIN.DROP_ACL ('v10t2p.xml');


begin
 DBMS_NETWORK_ACL_ADMIN.create_acl (
    acl          => 'v10t2p.xml', --Aqu� definimos un fichero xml donde se va a almacenar la informaci�n de los permisos de red a un usuario.
    description  => 'Informaci�n de los permisos al usuario para los procesos de V10',
    principal    => 'APPS', --Aqu� va el usuario del esquema en el que queremos activarlo
    is_grant     => TRUE, 
    privilege    => 'connect');
end;
/

    
begin
  DBMS_NETWORK_ACL_ADMIN.ADD_PRIVILEGE(
    acl         => 'v10t2p.xml', 
    principal   => 'APPS',
    is_grant    => TRUE, 
    position    => NULL, 
    privilege   => 'use-client-certificates');    
END;
/ 

begin
  DBMS_NETWORK_ACL_ADMIN.ADD_PRIVILEGE(
    acl         => 'v10t2p.xml', 
    principal   => 'APPS',
    is_grant    => TRUE,
    privilege   => 'use-passwords');    
END;
/    


begin
  DBMS_NETWORK_ACL_ADMIN.assign_acl (
    acl         => 'v10t2p.xml',
    host        => 'proxy.safa.net', --Aqu� va el servidor de correo electr�nico saliente, si solo se quiere dar acceso a un servicio como por ejemplo env�o de emails.
    lower_port  => 12321, --Aqu� definimos el puerto inicial o si lo ponemos a null todos los puertos son validos.
    upper_port  => 12321); --Aqu� si va a NULL se toma como limite el puerto lower.
end;
/

begin
  DBMS_NETWORK_ACL_ADMIN.assign_acl (
    acl         => 'v10t2p.xml',
    host        => '10.0.0.77', --Aqu� va el servidor de correo electr�nico saliente, si solo se quiere dar acceso a un servicio como por ejemplo env�o de emails.
    lower_port  => 12321, --Aqu� definimos el puerto inicial o si lo ponemos a null todos los puertos son validos.
    upper_port  => 12321); --Aqu� si va a NULL se toma como limite el puerto lower.
end;
/

begin
  DBMS_NETWORK_ACL_ADMIN.assign_acl (
    acl         => 'v10t2p.xml',
    host        => '*.nmvs.eu', --Aqu� va el servidor de correo electr�nico saliente, si solo se quiere dar acceso a un servicio como por ejemplo env�o de emails.
    lower_port  => null, --Aqu� definimos el puerto inicial o si lo ponemos a null todos los puertos son validos.
    upper_port  => null); --Aqu� si va a NULL se toma como limite el puerto lower.
end;
/

begin
  DBMS_NETWORK_ACL_ADMIN.assign_acl (
    acl         => 'v10t2p.xml',
    host        => 'ws-single-transactions-int-bp.nmvs.eu', --Aqu� va el servidor de correo electr�nico saliente, si solo se quiere dar acceso a un servicio como por ejemplo env�o de emails.
    lower_port  => null, --Aqu� definimos el puerto inicial o si lo ponemos a null todos los puertos son validos.
    upper_port  => null); --Aqu� si va a NULL se toma como limite el puerto lower.
end;
/


begin
  DBMS_NETWORK_ACL_ADMIN.ASSIGN_WALLET_ACL(
    acl         => 'v10t2p.xml', 
    wallet_path => 'file:E:\Oradata\wallet');
end;
/



BEGIN
DBMS_NETWORK_ACL_ADMIN.add_privilege ( 
    acl         => 'v10t2p.xml', 
    principal   => 'APPS', --Aqu� va el usuario del esquema en el que queremos activarlo
    is_grant    => TRUE, 
    privilege   => 'resolve', 
    position    => NULL, 
    start_date  => NULL,
    end_date    => NULL);
end;
/    

BEGIN
DBMS_NETWORK_ACL_ADMIN.DELETE_PRIVILEGE ( 
    acl         => 'v10t2p.xml', 
    principal   => 'APPS', --Aqu� va el usuario del esquema en el que queremos activarlo
    is_grant    => TRUE, 
    privilege   => 'resolve');
end;
/      


--
-- Damos permiso "http" al dominio de NMVS para APPS
BEGIN
 DBMS_NETWORK_ACL_ADMIN.append_host_ace (
   host       => '*.nmvs.eu', 
   lower_port => null,
   upper_port => null,
   ace        => xs$ace_type(privilege_list => xs$name_list('http'),
                             principal_name => 'APPS',
                             principal_type => xs_acl.ptype_db)); 
END;
/

  -- Dar permisos ACL para acceder al Wallet
BEGIN
 dbms_network_acl_admin.append_wallet_ace(
  wallet_path => 'file:E:\Oradata\wallet',
  ace         =>  xs$ace_type(privilege_list => xs$name_list('use_client_certificates', 'use_passwords'),
                                    principal_name => 'APPS',
                                    principal_type => xs_acl.ptype_db));
END;
/
