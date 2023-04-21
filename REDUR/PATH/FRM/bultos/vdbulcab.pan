###################################################################
#Módulo: VDBULCAB.PAN
#Funcionalidad : Mantenimiento de cabecera de bultos
#Autor: RFD      
#Fecha: 08-04-2008
###################################################################
# Histórico de cambios:
MANTENIMIENTO DE CABECERAS DE BULTO
 Código : _18_______________    Tipo bulto: _    Nº bulto: @L@@@ / @L@@@ 
 
 Estado:  @L@@@@ _30________________________  Tracking: _20_________________
 
 Pedido:  _20_______________ Div.:_20_ _40_____________________ Año: @@@@   Versión: @@@@    
 
 ÏÄÄÄÄÄÄÄÄÄÄ Empaquetado ÄÄÄÄÄÄÄÄÄÄÄË ÏÄÄÄ Preparación ÄÄÄÄÄÄÄË ÏÄÄÄÄÄÄÄÄÄÄÄ Preparación ÄÄÄÄÄÄÄÄÄÄÄÄË
 ³ Volumetría:   _10_________       ³ ³ ID.Pick:       @@@    ³ ³ CNTSSCC:   _18_______________      ³
 ³ Caja:         _10_________       ³ ³ Núm.Display:   @@@@@@@³ ³ Matrícula: _18_______________      ³
 ³ Peso Teórico: #L############# g. ³ ³ Anular prec.:  _      ³ ³ Recogida:  _20__________________   ³
 ³ Peso Real:    #L############# g. ³ ³ Lleva albarán: _      ³ ³ PDA: _20_______________________    ³
 ³ Volúmen:      #L############# cc.³ ³ Verif.Forzada: _      ³ ³ Scanner:   @@@@ ¿D-MM-YY.Y ________³
 ³                                  ³ ³                       ³ ³ Recir.Prepar: @@@@ Verif: @@@@     ³
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
 ÏÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ Seguimiento ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË
 ³ Fecha de creación:      ¿D-MM-YY.Y ________                      ³
 ³ Impreso:                ¿D-MM-YY.Y ________ _32________________  ³ 
 ³ Verificado:             ¿D-MM-YY.Y ________ _32________________  ³ 
 ³ Fecha de finalización:  ¿D-MM-YY.Y ________                      ³
 ³ Ultima modificación:    ¿D-MM-YY.Y ________ _32________________  ³ Comentario:@L@@@@@@@
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ    
 Información: _255________________________________________________________________________
|

TABLA=VDBULTOCABFU

#TIMEOUT=QUERYAUTOM,100
#TECLA=F3,FEJECUTA(FIF(FLECTURAS("CODBULTO"),FEJECUTA(FCOMMIT,"",FPULSATECLAS("F2"),"")),"DASDASDASD")

CURSOR=CSELLECT BEGIN
                  SELECT TEXTO INTO :CODBULTO FROM VDSCANLECT WHERE REDSCAN=1 AND SCANNER=10 AND ROWNUM=1;
                  DELETE VDSCANLECT WHERE REDSCAN=1 AND SCANNER=10;
                  COMMIT;
                END;@
                   
POSTQUERY=FEJECUTA("+CSELPDA","")
PREINSERT=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")

CAMPO=CODBULTO,NOUPDATE,TOOLTIP("Código del bulto. Número único que lo identifica")
CAMPO=TIPOBULTO,PROTECT("SUPALMACEN"),TOOLTIP("Tipo del bulto 'U' unidades, 'E' Embalajes, 'C' Contenedor")
CAMPO=NBULTO,NOUPDATE("SUPALMACEN"),TOOLTIP("Número de bulto dentro del pedido")
CAMPO=TOTALBULTOS,AUXILIAR,NOENTER,TOOLTIP("Total de bultos dentro del pedido")
CAMPO=STATUS,UPDATE("STATUS"),TOOLTIP("Estado del bulto según tabla de estados tipo BUC"),POSTCHANGE=FDESIGNACION("CSELSTATUS","Estado no existe"),COMBOX("CSELMISTATUS")
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Descripción del estado del bulto según tabla de estados tipo BUC")
CAMPO=TRACKINGAGE,NOUPDATE,TOOLTIP("Código identificativo del bulto para la agencia de transporte")
CAMPO=CODPED,NOUPDATE,POSTCHANGE=FDESIGNACION("CCOUNT","ERROR CONTANDO BULTOS DEL PEDIDOS"),TOOLTIP("Código del pedido")
CAMPO=CODDIV,NOUPDATE,POSTCHANGE=FDESIGNACION("CDESDIV","Código de división no existe."),TOOLTIP("División o compañia del pedido")
CAMPO=DESDIV,AUXILIAR,NOENTER,TOOLTIP("Descripción de la división o compañía del pedido")
CAMPO=ANOPED,NOUPDATE,TOOLTIP("Año del pedido")
CAMPO=SEQPED,NOUPDATE,TOOLTIP("Versión del pedido")
CAMPO=TIPOVOL,PROTECT("SUPALMACEN"),CONTEXTUAL=FEJECUTAFORM("VDVOLUMETRIA","N","TIPOVOL=:TIPOVOL","","","","S"),TOOLTIP("Tipo de volumetría si el bulto es de unidades")
CAMPO=IDINFOPICK,NOUPDATE,TOOLTIP("Indica a que infopick hardware se refiere el numero de display al que está asociado el bulto")
CAMPO=CNTSSCC,NOUPDATE("V10"),TOOLTIP("Matrícula del palet de expediciones en caso de paletización para la expedición")
CAMPO=TIPOCAJA,PROTECT("SUPALMACEN"),TOOLTIP("Inicial de la caja que aparece en la etiqueta")
CAMPO=NUMDISP,NOUPDATE,TOOLTIP("Número de display en la red infopick hardware al que está asociado el bulto")
CAMPO=MATCAJA,PROTECT("SUPALMACEN"),TOOLTIP("Matrícula de la caja para identificarla unicamente.")
CAMPO=PESOTEORICO,PROTECT("SUPALMACEN"),TOOLTIP("Peso teórico del bulto en gramos")
CAMPO=SWTANULAR,PROTECT("SUPALMACEN"),TOOLTIP("Indicador con valores: 'S' anular precintos, 'N' no se deben anular precintos")
CAMPO=SERIERECOGIDA,PROTECT("SUPALMACEN"),TOOLTIP("Número de serie de recogida en recogidas de cajas por etiquetado de cajas manual")
CAMPO=PESOREAL,PROTECT("SUPALMACEN"),TOOLTIP("Peso medido por la báscula en gramos")
CAMPO=SWTLLEVAALB,PROTECT("SUPALMACEN"),TOOLTIP("Indicador con valores: 'S' si el bulto lleva el albarán del pedido, VACIO si no lleva el albarán")
CAMPO=CODRECURSO,AUXILIAR,NOUPDATE,WHERE=:CODRECURSO IN (SELECT CODRECURSO FROM VDMOVIM MOV,VDBULTOLIN BUL WHERE BUL.CODBULTO=VDBULTOCAB.CODBULTO AND BUL.CODMOV=MOV.CODMOV);
CAMPO=VOLUMEN,TOOLTIP("Volúmen del bulto en centímetros cúbicos"),PROTECT("SUPALMACEN"),TOOLTIP("Volumen del bulto en centimetros cúbicos")
CAMPO=SWTVERIFFORZADA,PROTECT("SUPALMACEN"),TOOLTIP("Indicador con valores: 'S' si el bulto se ha forzado, por alguien o por un programa a que se verifique, 'N' no se fuerza a que entre en verificación.")
CAMPO=ULTSCAN,NOENTER,TOOLTIP("Ultimo scanner por el que ha pasado el bulto")
CAMPO=FECULTSCAN,NOENTER,TOOLTIP("Fecha en que actualizó el campo de último scanner por el que ha pasado el bulto")
CAMPO=HORAULTSCAN,NOENTER,TOOLTIP("Hora en que actualizó el campo de último scanner por el que ha pasado el bulto")
CAMPO=NUMRECIRCULAPREP,NOENTER,TOOLTIP("Número de recirculaciones del bulto en la zona de preparación")
CAMPO=NUMRECIRCULAVERIF,NOENTER,TOOLTIP("Número de recirculaciones del bulto en la zona de verificación")
CAMPO=FECCREADO,NOENTER,TOOLTIP("Fecha en que creó el bulto")
CAMPO=HORACREADO,NOENTER,TOOLTIP("Hora en que creo el bulto")
CAMPO=FECIMPRIME,NOENTER,TOOLTIP("Fecha en que realizó la impresión de la etiqueta  del bulto")
CAMPO=HORAIMPRIME,NOENTER,TOOLTIP("Hora en que realizó la impresión de la etiqueta  del bulto")
CAMPO=CODOPEIMPRIME,NOENTER,TOOLTIP("Usuario que realiza la impresión de la etiqueta del bulto")
CAMPO=FECVERIFICA,NOENTER,TOOLTIP("Fecha en que realizó la verificación del bulto")
CAMPO=HORAVERIFICA,NOENTER,TOOLTIP("Hora en que realizó la verificación del bulto")
CAMPO=CODOPEVERIFICA,NOENTER,TOOLTIP("Usuario que realiza la verificación del bulto")
CAMPO=FECFINALIZA,NOENTER,TOOLTIP("Fecha en que se finalizó el bulto")
CAMPO=HORAFINALIZA,NOENTER,TOOLTIP("Hora en que se finalizó el bulto")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la Ultima modificación")
CAMPO=HORAMODIF,UPPER,NOENTER,TOOLTIP("Hora de la Ultima modificación")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Usuario que realiza la Ultima modificación")
CAMPO=CODCOMEN,NOUPDATE,TOOLTIP("Código de los comentarios a la cabecera del bulto")
CAMPO=VDEXTRA,PROTECT("SUPALMACEN"),TOOLTIP("Datos adicionales externos a V10")

CURSOR=CSELPDA SELECT CODRECURSO FROM (SELECT CODRECURSO FROM VDMOVIM WHERE CODMOV IN (SELECT CODMOV FROM VDBULTOLIN WHERE CODBULTO=:CODBULTO)ORDER BY CASE WHEN STATUS BETWEEN 2000 AND 2100 THEN 0 ELSE 1 END) WHERE ROWNUM=1;


CURSOR=CSELMISTATUS SELECT STATUS,DABSTATUS,DESSTATUS,TIPOSTATUS FROM VDSTATUS WHERE TIPOSTATUS='BUC' ORDER BY STATUS;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;
CURSOR=CCOUNT SELECT COUNT(*) TOTALBULTOS FROM VDBULTOCAB
              WHERE CODPED=:CODPED AND SEQPED=:SEQPED AND CODDIV=:CODDIV AND ANOPED=:ANOPED ; 

CURSOR=CDESDIV SELECT DESDIV
                 FROM VDDIVIS
                WHERE CODDIV=:CODDIV;

CURSOR=CSELSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='BUC';
 
                      
CURSOR=CIMPREBULTO BEGIN
                     VDIMPRIME.IMPRIME('ETIQ','VDETIQBU.GEN;VDETIQUETAS.VSQ;CSELBULTO','CODBULTO='||:CODBULTO,1,'','',:V10ERROR,VDST.FISPPENDFICH);
					 RDRPKG.IMPRIMEAMZNCCBULTO(:CODBULTO);
                     COMMIT;
                   END;@ 
				   
CURSOR=CIMPREPACKLISTETIQ BEGIN
                            RDRPKG.IMPRIMIRPACKINGLISTETIQ(:CODBULTO);
                            COMMIT;
                          END;@ 

TECLA=CF1,FEJECUTA("CIMPREBULTO","ERROR AL IMPRIMIR")
					