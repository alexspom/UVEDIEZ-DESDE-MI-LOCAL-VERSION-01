grant connect to ALC identified by ALC;

grant select on v_$session to ALC;

grant execute on dbms_lock to ALC;

grant create any table to ALC;

grant create any index to ALC;

grant create any trigger to ALC;

grant select any table to ALC;

grant update any table to ALC;

grant insert any table to ALC;

GRANT CREATE ANY SYNONYM TO ALC;

GRANT CREATE ANY SEQUENCE TO ALC;

grant execute on utl_file to ALC;

grant execute on utl_tcp to ALC;

GRANT CREATE ANY PROCEDURE TO ALC;

GRANT CREATE ANY TYPE TO ALC;

GRANT CREATE  USER TO ALC;


GRANT DBA TO ALC;

create or replace synonym alc.telnetproveedor for sys.telnetproveedor;

create or replace  synonym alc.telnetarticulo for sys.telnetarticulo;

create or replace  synonym alc.telnetcliente for sys.telnetcliente;

GRANT SELECT ON TELNETCLIENTE TO ALC;

GRANT SELECT ON TELNETARTICULO TO ALC;

GRANT SELECT ON TELNETPROVEEDOR TO ALC;

CREATE OR REPLACE SYNONYM VDARTIC$AUD FOR ALC$AUD.VDARTIC$AUD;