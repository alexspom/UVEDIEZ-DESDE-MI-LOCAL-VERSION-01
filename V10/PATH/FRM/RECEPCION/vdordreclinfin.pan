#*****************************************************************
#Módulo: VDORDRECLINFIN.PAN
#Funcionalidad : Finalización manual de las líneas de las Ordenes de recepción y de sus cabeceras, si estás finalizadas o anuladas todas las líneas.
#                Muestra las líneas de la Orden que no están finalizadas o anuladas, y que no tienen una recepción pendientes de validación del 
#                mismo artículo.
#Autor: ICC      
#Fecha: 14-02-2008
#*****************************************************************
#* Histórico de cambios
#
FINALIZACION O ANULACION DE LAS LINEAS DE LA ORDEN DE RECEPCION

Línea  Artículo                           Lote               Cantidad       Cant. recep     Exc Def F.Pr.recep  F/A Estado                     Clave ext Ultima modificación             
###### _40_________________ _100________  _40______________ ############### ############### ### ### ¿D-MM-Y.YYY  _  ##### _30_________________ _50______ _32_______ ¿D-MM-Y.YYY _8______     
|
TABLA=VDORDRECLIN
WHERE=STATUS NOT IN (VDST.FORLFINALIZADA, VDST.FORLANULADA)
  AND (CODORDREC, CODDIV, CODART) NOT IN (SELECT REL.CODORDREC, REL.CODDIV, REL.CODART
                                            FROM VDRECEPCAB RCC, VDRECEPLIN REL
                                           WHERE RCC.STATUS    = VDST.FRCCACTIVA
                                             AND RCC.CODRECEP = REL.CODRECEP);



POSTQUERY=FEJECUTA("CCANTRECEP","ERROR CALCULANDO LA CANTIDAD RECEPCIONADA")

PREUPDATE=FEJECUTA(FIF("CFANUL", FEJECUTA("CUPDORDENLIN","ERROR AL MODIFICAR LA LINEA DE LA ORDEN :CODORDREC",
                                          FCOMMIT,"")),"")

POSTCOMMIT=FEJECUTA("CUPDORDENCAB","ERROR ACTUALIZANDO LA CABERA DE LA ORDEN DE RECEPCION :CODORDREC")

CAMPO=CODORDREC,VIRTUAL,OCULTO,TOOLTIP("Código de la orden de recepción")
CAMPO=CODDIV,VIRTUAL,OCULTO,TOOLTIP("Código de la división/compañía.Para permitir duplicidad de Ordenes en distintas divisiones = interfases")
CAMPO=SECLINORD,NOENTER,TOOLTIP("Secuencia de registro. Pueden no ser consecutivos"),TITULO("Línea")
CAMPO=CODART,NOUPDATE,POSTCHANGE=FDESIGNACION("CDESART","ERROR, NO EXISTE EL ARTICULO :CODART"),TOOLTIP("Código de artículo"),TITULO("Artículo")
CAMPO=DESART,NOENTER,AUXILIAR,TOOLTIP("Designación")
CAMPO=CODLOT,NOUPDATE,TOOLTIP("Lote previsto. Si esta informado la mercancía en recepción debe ser de dicho lote"),TITULO("Lote")
CAMPO=CANTIDAD,NOUPDATE,TOOLTIP("Cantidad prevista a recibir"),TITULO("Cantidad")
CAMPO=CANTRECEP,AUXILIAR,NOENTER,TOOLTIP("Cantidad recepcionada hasta el momento"),TITULO("Cant. Recep.")
CAMPO=TOLEREXC,NOUPDATE,TOOLTIP("Porcentaje de variación por exceso en la cantidad permitida en entradas.Valor null o negativo no aplica tolerancia"),TITULO("Exc"),WLONX=7
CAMPO=TOLERDEF,NOUPDATE,TOOLTIP("Porcentaje de variación por defecto en la cantidad permitida en entradas.En Ordenes que admiten multiples entradas no es aplicable.Valor null o negativo no aplica tolerancia"),TITULO("Def"),WLONX=7
CAMPO=FECRECPRE,NOUPDATE,TOOLTIP("Fecha de recepción prevista de la línea"),TITULO("F.Pr.Recep")
CAMPO=FANUL,AUXILIAR,UPPER,TOOLTIP("Indicador de si se quiere finalizar o anular una línea de una orden de recepción, F(in), A(nular) o blanco, no se hace nada"),WLONX=12,
            POSTCHANGE=FVERIFICA("FA ","EL CAMPO DEBE SER  F(in), A(nular) O Blanco"),TITULO("F/A")
CAMPO=STATUS,NOUPDATE,TOOLTIP("Estado de la línea"),TITULO("Estado"),
             POSTCHANGE=FEJECUTA("CDESSTATUS","ERROR, NO EXISTE EL ESTADO :STATUS")
CAMPO=DESSTATUS,NOENTER,AUXILIAR
CAMPO=CODCOMEN,OCULTO,"#########",TOOLTIP("Código de comentario")
CAMPO=CLAVEEXT,NOUPDATE,TOOLTIP("Clave externa que permite relacionar con otros sistemas no definidos"),TITULO("Clave Ext")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Usuario que ha realizado la Ultima modificación.Es utilizado para depuración y control de los registros en las tablas"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Es la fecha  en que se efectuó alguna modificación. Es utilizado para depuración y control de los registros en las tablas")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Es la hora  en que se efectuó alguna modificación. Es utilizado para depuración y control de los registros en las tablas")
CAMPO=VDEXTRA,OCULTO,"_255_",TOOLTIP("Información adicional suministrada por el cliente")
CAMPO=MSGERROR,AUXILIAR,OCULTO,"_100______"
CAMPO=DUMMY,AUXILIAR,OCULTO,"#"

CURSOR=CDESSTATUS SELECT DESSTATUS
                    FROM VDSTATUS
                   WHERE STATUS     = :STATUS
                     AND TIPOSTATUS = 'ORL';
                     
CURSOR=CDESART SELECT DESART FROM VDARTIC WHERE CODART=:CODART;

CURSOR=CCANTRECEP SELECT (:CANTIDAD - VDRECEP.CANTPDTE(:CODORDREC, :CODART, :CODDIV, :CODLOT, :SECLINORD, 'N') ) CANTRECEP
                    FROM DUAL;

CURSOR=CFANUL SELECT 1 DUMMY
                FROM DUAL
               WHERE :FANUL IN ('F','A');

CURSOR=CUPDORDENLIN UPDATE VDORDRECLIN
                       SET STATUS = DECODE(:FANUL, 'F', VDST.FORLFINALIZADA, 'A',VDST.FORLANULADA),
                           CODOPEMODIF =VDUSER.GETUSER, FECMODIF = VD.FECHASYS, HORAMODIF = VD.HORASYS
                     WHERE CODORDREC = :CODORDREC
                       AND CODDIV    = :CODDIV
                       AND SECLINORD = :SECLINORD;

CURSOR=CUPDORDENCAB UPDATE VDORDRECCAB
                       SET STATUS = DECODE(:FANUL, 'F', VDST.FORCFINALIZADA, 'A',VDST.FORCANULADA),
                           CODOPEMODIF =VDUSER.GETUSER, FECMODIF = VD.FECHASYS, HORAMODIF = VD.HORASYS
                     WHERE CODORDREC = :CODORDREC
                       AND CODDIV    = :CODDIV
                       AND (CODORDREC, CODDIV) NOT IN (SELECT CODORDREC, CODDIV
                                                         FROM VDORDRECLIN
                                                        WHERE STATUS < VDST.FORLFINALIZADA);

