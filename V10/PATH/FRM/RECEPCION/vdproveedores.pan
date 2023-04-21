#####
# VDPROVEEDORES.PAN
#                                                    
# Propósito: Mantenimiento de la tabla de proveedores                          
#                                                                              
#####
MANTENIMIENTO DE PROVEEDORES
 
 Proveedor: _20_____________ _60______________________________    
 Tipo: _20_______________    NIF:  _30___________   Activo: __
 
 ÏÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ ENVIO ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË
 ³                                                                                         ³
 ³ Dirección: _40___________________________  _40___________________________               ³
 ³                                                                                         ³
 ³            _40___________________________  _40___________________________               ³
 ³                                                                                         ³
 ³ País: _____ _30_________________  Provincia: _____ _40__________________                ³
 ³                                                                                         ³
 ³ Población: _40_________________ DP: _10____  Contacto: _40_____________________________ ³
 ³                                                                                         ³
 ³ Teléfono: _12_______            Fax: _12______     Email: _40__________________________ ³
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
 
 Cajas a verificar:@@@   Margen de peso:@@@@    Verificación FMD:_
 
 Observaciones: _256________________________________________________________________________ 
 
 Ultima modificación: _32________________ ¿D-MM-YY.Y ________

|

TABLA=VDPROVEEDOR


#TRIGGERS
PREINSERT=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")

PREUPDATE=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")

#CAMPOS				   
CAMPO=CODPROVE,TOOLTIP("Es el código de proveedor al que se realiza el pedido de compra")
CAMPO=DESPROVE,TOOLTIP("Designación completa del proveedor")
CAMPO=TIPOPROVE,TOOLTIP("Tipo de proveedor")
CAMPO=NIF,TOOLTIP("Nif del proveedor")
CAMPO=ACTIVO,TOOLTIP("Indica si el proveedor está activo o no")
CAMPO=DIRECCION,TOOLTIP("Es la dirección del proveedor. Está descompuesta en cuatro campos de 40 caracteres")
CAMPO=DIRECCION1,TOOLTIP("Línea 2 de la dirección de proveedor")
CAMPO=DIRECCION2,TOOLTIP("Línea 3 de la dirección de proveedor")
CAMPO=DIRECCION3,TOOLTIP("Línea 4 de la dirección de proveedor")
CAMPO=CODPAIS,TOOLTIP("País de proveedor"),POSTCHANGE=FDESIGNACION("+CSELPAISDEST",""),COMBOX("CLISTAPAIS")
CAMPO=DESPAISDEST,AUXILIAR,NOENTER
CAMPO=CODPROV,TOOLTIP("Código de la provincia de proveedor"),POSTCHANGE=FDESIGNACION("+CSELDESPROVDEST",""),COMBOX("CLISTAPROV")
CAMPO=DESPROVDEST,AUXILIAR,NOENTER
CAMPO=POBLACION,TOOLTIP("Población del proveedor")
CAMPO=DP,TOOLTIP("Distrito postal de la dirección de proveedor"),POSTCHANGE=FDESIGNACION("+CSELPOB",""),COMBOX("CLISTADP")
CAMPO=CONTACTO,TOOLTIP("Indica el posible contacto con el proveedor")
CAMPO=TELEFONO,TOOLTIP("Teléfono correspondiente a dirección de proveedor")
CAMPO=FAX,TOOLTIP("Número de fax del proveedor")
CAMPO=EMAIL,TOOLTIP("Direccion email correspondiente a dirección de proveedor")
CAMPO=CAJASAVERIF,TOOLTIP("Número de cajas a verificar asociado al proveedor")
CAMPO=MARGENPESO,TOOLTIP("Margen de peso asociado al proveedor")
CAMPO=SWTFMD,TOOLTIP("Requiere verificación FMD, (N)unca, (S)iempre, (O)casionalmente")
CAMPO=OBSERVACIONES,TOOLTIP("observaciones al cliente")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realiza la modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la última modificación. Es utilizado para depuración y control de los registros en las tablas")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora de la última modificación. Es utilizado para depuración y control de los registros en las tablas")


#CURSORES
CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CSELDESPROVDEST SELECT DESPROV DESPROVDEST
                         FROM VDPROVI 
                        WHERE CODPROV = :CODPROV AND CODPAIS = :CODPAIS;

CURSOR=CSELPAISDEST SELECT DESPAIS DESPAISDEST
                      FROM VDPAIS
                     WHERE CODPAIS = :CODPAIS;
                     
CURSOR=CLISTAPAIS SELECT CODPAIS,DESPAIS DESPAISDEST FROM VDPAIS ORDER BY DESPAIS;

CURSOR=CLISTAPROV SELECT CODPROV,DESPROV DESPROVDEST FROM VDPROVI;

CURSOR=CLISTADP SELECT DP,LOCALIDAD POBLACION FROM VDLOCALIDAD WHERE NVL(:CODPAIS,CODPAIS)=CODPAIS AND NVL(:CODPROV,CODPROV)=CODPROV AND NVL(:POBLACION,LOCALIDAD)=LOCALIDAD
                ORDER BY DP,LOCALIDAD;

CURSOR=CSELPOB SELECT :POBLACION POBLACION FROM DUAL;



AYUDA=MANTENIMIENTO DE PROVEEDORES
ONLINE=     {F1} Ayuda {F2} Consulta {F4} Confirmar cambios {F5} Borrar pantalla
              {F9} Borrar registro {Ctrl-F7} Copia {Esc} Salir;

