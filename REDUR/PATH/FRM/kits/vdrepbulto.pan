###################################################################
#MOdulo: VDREPBULTO.PAN
#Funcionalidad : Pantalla que permite la repetici�n de un kit identificado por un c�digo de bulto
#Autor: DGB      
#Fecha: 27-05-2019
###################################################################
# HistOrico de cambios:
BULTOS DE KITS
 C�digo : _18_______________    Tipo bulto: _     
 
 Estado:  @L@@@@ _30________________________
 
 Pedido:  _20_______________ Orden de preparaci�n:  _60_____________
 
 ��������������������������������������� KIT �������������������������������������������������
 � Art�culo Kit:  _255__________________________  LOTE: _255__________________________       �
 �                                                                                           �
 ���������������������������������������������������������������������������������������������
 ���������������������������� Seguimiento ���������������������������
 � Fecha de creaci�n:      �D-MM-YY.Y ________                      �
 � Impreso:                �D-MM-YY.Y ________ _32________________  � 
 � Verificado:             �D-MM-YY.Y ________ _32________________  � 
 � Fecha de finalizaci�n:  �D-MM-YY.Y ________                      �
 � Ultima modificaci�n:    �D-MM-YY.Y ________ _32________________  � 
 ��������������������������������������������������������������������    

|

TABLA=VDBULTOCAB

#WHERE=CODPED LIKE 'PRO%' AND STATUS=VDST.FBUCPDTESERVIR;

POSTQUERY=FEJECUTA("CSELBULTO","EL BULTO NO EXISTE.",
                   "CSELORPRO","EL BULTO NO PERTENECE A UNA ORDEN DE PRODUCCION",
                   "CSELSTATUSBUL","EL BULTO NO EST� EN EL ESTADO CORRECTO.\nIMPOSIBLE REIMPRIMIR.")

CAMPO=CODBULTO,NOUPDATE,TOOLTIP("C�digo del bulto. N�mero �nico que lo identifica")
CAMPO=TIPOBULTO,PROTECT("SUPALMACEN"),TOOLTIP("Tipo del bulto 'U' unidades, 'E' Embalajes, 'C' Contenedor")
CAMPO=STATUS,UPDATE("STATUS"),TOOLTIP("Estado del bulto seg�n tabla de estados tipo BUC"),POSTCHANGE=FDESIGNACION("CSELSTATUS","Estado no existe"),COMBOX("CSELMISTATUS")
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Descripci�n del estado del bulto seg�n tabla de estados tipo BUC")
CAMPO=CODPED,NOUPDATE,TOOLTIP("C�digo del pedido V10"),POSTCHANGE=FDESIGNACION("CSELDATOSKIT","Error obteniendo datos asociados al kit.")
CAMPO=CODORDKIT,AUXILIAR,NOENTER,TOOLTIP("C�digo de orden de preparaci�n suministrado por el sistema superior.")
CAMPO=CODARTKIT,AUXILIAR,NOENTER,TOOLTIP("C�digo de art�culo a fabricar en el kit.")
CAMPO=CODLOTKIT,AUXILIAR,NOENTER,TOOLTIP("C�digo de lote asociado al kit.")
CAMPO=FECCREADO,NOENTER,TOOLTIP("Fecha en que creO el bulto")
CAMPO=HORACREADO,NOENTER,TOOLTIP("Hora en que creo el bulto")
CAMPO=FECIMPRIME,NOENTER,TOOLTIP("Fecha en que realizO la impresiOn de la etiqueta  del bulto")
CAMPO=HORAIMPRIME,NOENTER,TOOLTIP("Hora en que realizO la impresiOn de la etiqueta  del bulto")
CAMPO=CODOPEIMPRIME,NOENTER,TOOLTIP("Usuario que realiza la impresiOn de la etiqueta del bulto")
CAMPO=FECVERIFICA,NOENTER,TOOLTIP("Fecha en que realizO la verificaci�n del bulto")
CAMPO=HORAVERIFICA,NOENTER,TOOLTIP("Hora en que realizO la verificaci�n del bulto")
CAMPO=CODOPEVERIFICA,NOENTER,TOOLTIP("Usuario que realiza la verificaci�n del bulto")
CAMPO=FECFINALIZA,NOENTER,TOOLTIP("Fecha en que se finalizO el bulto")
CAMPO=HORAFINALIZA,NOENTER,TOOLTIP("Hora en que se finalizO el bulto")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la Ultima modificaci�n")
CAMPO=HORAMODIF,UPPER,NOENTER,TOOLTIP("Hora de la Ultima modificaci�n")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Usuario que realiza la Ultima modificaci�n")
CAMPO=CODIMPREETIQ,AUXILIAR,OCULTO,"_15____________"

CURSOR=CIMPREETIQAMA BEGIN
					 RDRPKG.IMPRIMEAMZNCCBULTO(:CODBULTO);
                     COMMIT;
                   END;@ 

CURSOR=CSELBULTO SELECT :CODBULTO FROM VDBULTOCAB WHERE CODBULTO=:CODBULTO;

CURSOR=CSELORPRO SELECT :CODBULTO FROM DUAL WHERE :CODPED LIKE 'PRO%';

CURSOR=CSELSTATUSBUL SELECT :CODBULTO FROM DUAL WHERE :STATUS=VDST.FBUCPDTESERVIR;

CURSOR=CSELSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='BUC';

CURSOR=CSELDATOSKIT SELECT PEDIDOHOST CODORDKIT,MENHOST CODARTKIT,VDEXTRA CODLOTKIT FROM VDPEDIDOCAB WHERE CODPED=:CODPED;

CURSOR=CSELVALMAN SELECT VD.GETPROP('IMPETIQMANDEF') CODIMPREETIQ FROM DUAL;

TECLA=SF8,FEJECUTA("CSELBULTO","EL BULTO NO EXISTE.",
                   "CSELORPRO","EL BULTO NO PERTENECE A UNA ORDEN DE PRODUCCION",
                   "CSELSTATUSBUL","EL BULTO NO EST� EN EL ESTADO CORRECTO.\nIMPOSIBLE REIMPRIMIR.",
                   "CSELVALMAN","ERROR OBTENIENDO ETIQUETADORA POR DEFECTO.",
                   FIMPRIMEBULTO("ETIQ",":CODBULTO","VDETIQBUKIT.GEN;VDETIQUETAS.VSQ;CSELBULKIT","CODBULTO=:CODBULTO;ESCOPIA=S;NUMETIQ=1;TOTALETIQKIT=1",":CODIMPREETIQ","1"),"ERROR AL IMPRIMIR ETIQUETA\n :V10ERROR",
				   "CIMPREETIQAMA","NO PUEDO IMPRIMIR ETIQUETA AMAZON",
                   FCOMMIT,"")

ONLINE=     {F1} Ayuda {F2} Consulta {F5} Borrar pantalla {May+F8} Repetir etiqueta {Esc} Salir; 





