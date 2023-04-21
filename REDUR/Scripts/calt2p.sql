-- Damos permiso de "connect" al proxy 
BEGIN
 DBMS_NETWORK_ACL_ADMIN.append_host_ace (
   host       => 'proxy.safa.net', 
   lower_port => 12321,
   upper_port => 12321,
   ace        => xs$ace_type(privilege_list => xs$name_list('connect'),--> Puede ser connect y resolve
                             principal_name => 'APPS',
                             principal_type => xs_acl.ptype_db)); 
END;
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
