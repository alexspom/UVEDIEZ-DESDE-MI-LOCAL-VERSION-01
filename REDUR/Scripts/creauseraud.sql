
grant connect,dba to ALC identified by ALC;

GRANT CONNECT TO ALC$AUD IDENTIFIED BY ALC$AUD;

GRANT UNLIMITED TABLESPACE TO ALC;

GRANT UNLIMITED TABLESPACE TO ALC$AUD;

grant select on v_$session to ALC;

grant execute on dbms_lock to ALC;

grant create any table to ALC;

grant create any index to ALC;

grant create any trigger to ALC;

grant select any table to ALC;

grant update any table to ALC;

grant insert any table to ALC;

GRANT CREATE ANY SYNONYM TO ALC;           

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   