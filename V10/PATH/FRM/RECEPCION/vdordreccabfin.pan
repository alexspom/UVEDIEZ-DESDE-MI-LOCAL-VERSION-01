#*****************************************************************
#Módulo: VDORDRECCABFIN.PAN
#Función : Finalización manual de las Ordenes de recepción y de sus líneas.
#          Muestra las Ordenes que no están finalizadas o anuladas, y que no tienen una recepción pendientes de validación.
#          En caso de querer finalizar una orden de recepción que no han finalizado todas sus líneas, muestra un mensaje de aviso.
#
#Autor: ICC      
#Fecha: 14-02-2008
#*****************************************************************
#* Histórico de cambios
#* ====================
FINALIZACION O ANULACION DE ORDENES DE RECEPCION
Orden de recepción   División Tipo orden  Proveedor                              F. orden   F. creación         F/A Estado                        Clave ext.       Ultima modificación             
_20_________________   _20__   _10_______  _20______________ _60________________ ¿D-MM-Y.YYY ¿D-MM-Y.YYY _8______ _  ##### _30____________________ _50_____________ _32_______ ¿D-MM-Y.YYY _8______
|

TABLA=VDORDRECCAB
WHERE=STATUS NOT IN (VDST.FRCCFINALIZADA,VDST.FRCCANULADA)
  AND (CODORDREC, CODDIV) NOT IN (SELECT CODORDREC, CODDIV
                                    FROM VDRECEPCAB
                                   WHERE STATUS    = VDST.FRCCACTIVA);



PREUPDATE=FEJECUTA(FIF("CFANUL", FEJECUTA("!-CVALFANUL","HAY LINEAS QUE NO SE HAN RECEPCIONADO POR COMPLETO\n¿DESEA CONTINUAR?", 
                                          "CUPDORDENLIN","ERROR AL MODIFICAR LAS LINEAS DE LA ORDEN :CODORDREC",
                                          "CUPDORDENCAB","ERROR AL MODIFICAR LA CABECERA DE LA ORDEN :CODORDREC",
                                          FCOMMIT,"")),"")

CAMPO=CODORDREC,NOUPDATE, TOOLTIP("Código de la orden de recepción"),TITULO("Orden de Recepción")
CAMPO=CODDIV,NOUPDATE,TOOLTIP("Código de la división/compañía.División ':DESDIV'"),TITULO("División"),WLONX=27
CAMPO=TIPORDREC,NOUPDATE,TOOLTIP("Es el tipo de orden de recepción. Existirá en la tabla VDTIPORDREC"),TITULO("Tipo Orden"),WLONX=24
CAMPO=CODPROVE,NOUPDATE,TOOLTIP("Es el Código del proveedor "),TITULO("Proveedor")
CAMPO=DESPROVE,NOUPDATE,TOOLTIP("Es la denominación del proveedor ")
CAMPO=FECORDREC,NOUPDATE,TOOLTIP("Fecha original de la orden de recepción. Vendrá en la interfase"),TITULO("F. Orden")
CAMPO=FECCREADO,NOUPDATE,TOOLTIP("Es la fecha de creación de la orden en el sistema "),TITULO("F. creación")
CAMPO=HORACREADO,NOUPDATE,TOOLTIP("Es la hora de creación de la orden en el sistema ")
CAMPO=FANUL,AUXILIAR,UPPER,TOOLTIP("Indicador de si se quiere finalizar o anular una orden de recepción, F(in), A(nular) o blanco, no se hace nada"),
            POSTCHANGE=FVERIFICA("FA ","EL CAMPO DEBE SER  F(in), A(nular) O Blanco"),TITULO("F/A"),WLONX=12
CAMPO=STATUS,NOUPDATE,TOOLTIP("Es el estado en el que se encuentra la orden de recepción"),
             POSTCHANGE=FEJECUTA("CDESSTATUS","ERROR, NO EXISTE EL ESTADO :STATUS"),TITULO("Estado")
CAMPO=DESSTATUS,NOENTER,AUXILIAR
CAMPO=CLAVEEXT,NOUPDATE,TOOLTIP("Clave externa que permite relacionar con otros sistemas no definidos"),TITULO("Clave Externa")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Usuario que ha realizado la Ultima modificación.Es utilizado para depuración y control de los registros en las tablas"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Es la fecha  en que se efectuó alguna modificación. Es utilizado para depuración y control de los registros en las tablas")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Es la hora  en que se efectuó alguna modificación. Es utilizado para depuración y control de los registros en las tablas")
CAMPO=VDEXTRA,OCULTO,"_255_",TOOLTIP("Datos adicionales externos a V10 y útiles para el cliente")
CAMPO=CODCOMEN,OCULTO,"#########",TOOLTIP("")
CAMPO=DUMMY,AUXILIAR,OCULTO,"#"

CURSOR=CDESSTATUS SELECT DESSTATUS
                    FROM VDSTATUS
                   WHERE STATUS     = :STATUS
                     AND TIPOSTATUS = 'ORC';

CURSOR=CFANUL SELECT 1 DUMMY
                FROM DUAL
               WHERE :FANUL IN ('F','A');

CURSOR=CVALFANUL SELECT 1 DUMMY
                   FROM VDORDRECLIN
                  WHERE CODORDREC = :CODORDREC
                    AND CODDIV    = :CODDIV
                    AND STATUS    = VDST.FORLACTIVA
                    AND :FANUL    = 'F'
                    AND CANTIDAD-VDRECEP.CANTPDTE(:CODORDREC, CODART, :CODDIV, CODLOT, SECLINORD, 'N') > 0;

CURSOR=CUPDORDENLIN UPDATE VDORDRECLIN
                       SET STATUS = DECODE(:FANUL, 'A', VDST.FORLANULADA, 'F',VDST.FORLFINALIZADA),
                           CODOPEMODIF =VDUSER.GETUSER, FECMODIF = VD.FECHASYS, HORAMODIF = VD.HORASYS
                     WHERE CODORDREC = :CODORDREC
                       AND CODDIV    = :CODDIV
                       AND STATUS NOT IN (VDST.FORLANULADA, VDST.FORLFINALIZADA);

CURSOR=CUPDORDENCAB UPDATE VDORDRECCAB
                       SET STATUS = DECODE(:FANUL, 'A', VDST.FORCANULADA, 'F',VDST.FORCFINALIZADA),
                           CODOPEMODIF =VDUSER.GETUSER, FECMODIF = VD.FECHASYS, HORAMODIF = VD.HORASYS
                     WHERE CODORDREC = :CODORDREC
                       AND CODDIV    = :CODDIV;


