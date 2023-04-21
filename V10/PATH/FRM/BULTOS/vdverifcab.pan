###################################################################
#M�dulo: VDVERIFCAB.PAN
#Funcionalidad : Verificaci�n de bultos
#Autor: RFD      
#Fecha: 13-10-2010
###################################################################
# Hist�rico de cambios:
VERIFICACION DE BULTOS
 C�digo : _18_______________    Tipo bulto: _    N� bulto: @L@@@ / @L@@@ 
 
 Estado:  @L@@@@ _30________________________  Tracking: _20_________________
 
 Pedido:  _20_______________ Div.:_20_ _40_____________________ A�o:@@@@   Versi�n:@@@    
 
 ����������� Empaquetado ������������ ���� Preparaci�n �������� ������������ Preparaci�n �������������
 � Volumetr�a:   _10_________       � � ID.Pick:       @@@    � � CNTSSCC:   _18_______________      �
 � Caja:         _10_________       � � N�m.Display:   @@@@@@@� � Matr�cula: _18_______________      �
 � Peso Te�rico: #L############# g. � � Anular prec.:  _      � � Recogida:  _20__________________   �
 � Peso Real:    #L############# g. � � Lleva albar�n: _      � � Scanner:   @@@@ ________________   �
 � Vol�men:      #L############# cc.� � Verif.Forzada: _      � �                 �D-MM-YY.Y ________�
 �                                  � �                       � � Recir.Prepar: @@@@ Verif: @@@@     �
 ������������������������������������ ������������������������� ��������������������������������������
 ���������������������������� Seguimiento ��������������������������
 � Fecha de creaci�n:      �D-MM-YY.Y ________                     �          
 � Impreso:                �D-MM-YY.Y ________ _32________________ �       
 � Verificado:             �D-MM-YY.Y ________ _32________________ �       
 � Fecha de finalizaci�n:  �D-MM-YY.Y ________                     �
 � Ultima modificaci�n:    �D-MM-YY.Y ________ _32________________ �   Comentario:@L@@@@@@@
 �������������������������������������������������������������������    
 Informaci�n: _255________________________________________________________________________
                                                       DESEA VALIDAR ESTE BULTO (S/N) ? _
|

TABLA=VDBULTOCAB
SELECT=STATUS CBSTATUS,NVL(:TVALIDAR,'S') VALIDAR;
WHERE=STATUS=VDST.FBUCPREPARADO;
ORDERBY=STATUS,CODPED,NBULTO;

NOINSERT
NODELETE
NOUPDATE

POSTQUERY=FEJECUTA("+CSELMENHOST","",
                   "CSELPREPARADO","Bulto :CODBULTO \nno ha sido preparado correctamente",
                   @FIF("-CSELTERMIN",FEJECUTA(%FFAILURE,"Bulto :CODBULTO \nya esta validado",FPULSATECLAS("F5"),"",FFAILURE,"")),"",
                   FIF("CSELVALIDA",FMODIFICA,FSUCCESS),"ERROR DETERMINANDO MODIFICACION",
                   "-CSELLINPEND","Bulto :CODBULTO \ntiene l�neas pendientes",
                                    "+CCALCPESOCOR","",
                   "+CCALCDIFERENCIA","",
                   FIF("-CVERIFPESO",
                           FEJECUTA("CSELHTML","",
                                    "CSELERRART","ERROR AL MOSTRAR PESOS",
                                    %FFAILURE,"<span style='color:black' </span> PESO ERRONEO\n PESA :PESOREAL Y DEBE ESTAR ENTRE :PESOD Y :PESOH\n DIFERENCIA :DIFERENCIAPESO \n\n\n :ARTICULOS</span><BGSOUND id='BGSOUND_ID' LOOP=1 SRC='file://C:\WINDOWS\Media\flourish.mid'>",
                                    "CSELSTDHTML",""),
                           FSUCCESS),"",
                   FIF("CVERIFANU",FSUCCESS,
                       FEJECUTA("%-CSELAANULAR","ANULAR PRECINTOS DE LA SEGURIDAD SOCIAL\n :ARTICULOS")),"",
                   "+CVERIART","ARTICULO :ARTVERIF :CODCLASE",
                   FWHILE(FERRORCURSOR("CVERIART"),
                          FEJECUTA("CSELARTAVERIF","",%FFAILURE,"VERIFICACION FORZOSA DE ARTICULOS :CODCLASE\n :ARTICULOS ",
                                   +FFETCHCURSOR("CVERIART"),"")),"Error en While",
                   "%CVERPEQUENA","PASAR A CAJA PEQUE�A",
                   "%CVERIFMENHOST","OBSERVACIONES  :MENHOST")

PREUPDATE=FEJECUTA("CVERNOMODIF","ESTADO MODIFICADO POR OTRO PROCESO",
                   "CDAMELLEVAALBARAN","ERROR OBTENIENDO INFORMACION LLEVA ALBARAN",
                  FIF("CLLEVAALBARAN",FEJECUTA(FACTLINEASPEDIDO(":CODDIV",":ANOPED",":CODPED",":SEQPED"),"ERROR ACTUALIZANDO PEDIDO -\n :V10ERROR",
                                               FCOMMIT,"",
                                               +FIMPRIMEPEDIDO("INFORME",":CODDIV",":ANOPED",":CODPED",":SEQPED","$(VDALBARAN)","CODDIV=:CODDIV;ANOPED=:ANOPED;CODPED=:CODPED;SEQPED=:SEQPED",""),":V10ERROR",
                                               %FFAILURE,"INSERTAR EL ALBAR�N EN EL\nBULTO :CODBULTO")),"ERROR EN FIF CLLEVAALBARAN",
                    FIF("CSELBULCNT",FEJECUTA("CSELULTIMO","ERROR OBTENIENDO ULTIMO BULTO","CUPDBULCNT","ERROR ACTUALIZANDO BULTO"),
                                     "CUPDBULTO"),"NO SE PUEDE ACTUALIZAR CABECERA DE BULTO")

#,FPOSICIONACAMPO(FSUCCESS,"VALIDAR"),""
                   
                   
POSTCOMMIT=FEJECUTA(FPULSATECLAS("F5"),"ERROR EN PULSA TECLAS")

PREBLOQUE=FEJECUTA(FDAMEORDENADOR("ORDENADOR"),"",
                     "CDELALLSCAN","",
                     FCOMMIT,"")
                                         
  
                    
CAMPO=MIROWIDSCAN,AUXILIAR,NOUPDATE,OCULTO,"_40"
CAMPO=ORDENADOR,AUXILIAR,NOUPDATE,OCULTO,"_40"
CAMPO=TVALIDAR,AUXILIAR,NOUPDATE,OCULTO,"_"
CAMPO=CODBULTO,TOOLTIP("C�digo del bulto. N�mero �nico que lo identifica")
CAMPO=TIPOBULTO,PROTECT("SUPALMACEN"),TOOLTIP("Tipo del bulto 'U' unidades, 'E' Embalajes, 'C' Contenedor")
CAMPO=NBULTO,NOUPDATE,TOOLTIP("N�mero de bulto dentro del pedido")
CAMPO=TOTALBULTOS,AUXILIAR,NOENTER,TOOLTIP("Total de bultos dentro del pedido")
CAMPO=STATUS,PROTECT("SUPALMACEN"),TOOLTIP("Estado del bulto seg�n tabla de estados tipo BUC"),POSTCHANGE=FDESIGNACION("CSELSTATUS","Estado no existe"),COMBOX("CSELMISTATUS")
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Descripci�n del estado del bulto seg�n tabla de estados tipo BUC")
CAMPO=TRACKINGAGE,NOUPDATE,TOOLTIP("C�digo identificativo del bulto para la agencia de transporte")
CAMPO=CODPED,NOUPDATE,POSTCHANGE=FDESIGNACION("CCOUNT","ERROR CONTANDO BULTOS DEL PEDIDOS"),TOOLTIP("C�digo del pedido")
CAMPO=CODDIV,NOUPDATE,POSTCHANGE=FDESIGNACION("CDESDIV","C�digo de divisi�n no existe."),TOOLTIP("Divisi�n o compa�ia del pedido")
CAMPO=DESDIV,AUXILIAR,NOENTER,TOOLTIP("Descripci�n de la divisi�n o compa��a del pedido")
CAMPO=ANOPED,NOUPDATE,TOOLTIP("A�o del pedido")
CAMPO=SEQPED,NOUPDATE,TOOLTIP("Versi�n del pedido")
CAMPO=TIPOVOL,PROTECT("SUPALMACEN"),CONTEXTUAL=FEJECUTAFORM("VDVOLUMETRIA","N","TIPOVOL=:TIPOVOL","","","","S"),TOOLTIP("Tipo de volumetr�a si el bulto es de unidades")
CAMPO=IDINFOPICK,NOUPDATE,TOOLTIP("Indica a que infopick hardware se refiere el numero de display al que est� asociado el bulto")
CAMPO=CNTSSCC,NOUPDATE,TOOLTIP("Matr�cula del palet de expediciones en caso de paletizaci�n para la expedici�n")
CAMPO=TIPOCAJA,PROTECT("SUPALMACEN"),TOOLTIP("Inicial de la caja que aparece en la etiqueta")
CAMPO=NUMDISP,NOUPDATE,TOOLTIP("N�mero de display en la red infopick hardware al que est� asociado el bulto")
CAMPO=MATCAJA,PROTECT("SUPALMACEN"),TOOLTIP("Matr�cula de la caja para identificarla unicamente.")
CAMPO=PESOTEORICO,PROTECT("SUPALMACEN"),TOOLTIP("Peso te�rico del bulto en gramos")
CAMPO=SWTANULAR,PROTECT("SUPALMACEN"),TOOLTIP("Indicador con valores: 'S' anular precintos, 'N' no se deben anular precintos")
CAMPO=SERIERECOGIDA,PROTECT("SUPALMACEN"),TOOLTIP("N�mero de serie de recogida en recogidas de cajas por etiquetado de cajas manual")
CAMPO=PESOREAL,PROTECT("SUPALMACEN"),TOOLTIP("Peso medido por la b�scula en gramos")
CAMPO=SWTLLEVAALB,PROTECT("SUPALMACEN"),TOOLTIP("Indicador con valores: 'S' si el bulto lleva el albar�n del pedido, VAC�O si no lleva el albar�n")
CAMPO=ULTSCAN,NOENTER,TOOLTIP("Ultimo scanner por el que ha pasado el bulto"),POSTCHANGE=FDESIGNACION("+CSELDESSCAN","")
CAMPO=DESSCAN,AUXILIAR,NOENTER
CAMPO=VOLUMEN,TOOLTIP("Vol�men del bulto en cent�metros c�bicos"),PROTECT("SUPALMACEN"),TOOLTIP("Volumen del bulto en centimetros c�bicos")
CAMPO=SWTVERIFFORZADA,PROTECT("SUPALMACEN"),TOOLTIP("Indicador con valores: 'S' si el bulto se ha forzado, por alguien o por un programa a que se verifique, 'N' no se fuerza a que entre en verificaci�n.")
CAMPO=FECULTSCAN,NOENTER,TOOLTIP("Fecha en que actualiz� el campo de �ltimo scanner por el que ha pasado el bulto")
CAMPO=HORAULTSCAN,NOENTER,TOOLTIP("Hora en que actualiz� el campo de �ltimo scanner por el que ha pasado el bulto")
CAMPO=NUMRECIRCULAPREP,NOENTER,TOOLTIP("N�mero de recirculaciones del bulto en la zona de preparaci�n")
CAMPO=NUMRECIRCULAVERIF,NOENTER,TOOLTIP("N�mero de recirculaciones del bulto en la zona de verificaci�n")
CAMPO=FECCREADO,NOENTER,TOOLTIP("Fecha en que cre� el bulto")
CAMPO=HORACREADO,NOENTER,TOOLTIP("Hora en que creo el bulto")
CAMPO=FECIMPRIME,NOENTER,TOOLTIP("Fecha en que realiz� la impresi�n de la etiqueta  del bulto")
CAMPO=HORAIMPRIME,NOENTER,TOOLTIP("Hora en que realiz� la impresi�n de la etiqueta  del bulto")
CAMPO=CODOPEIMPRIME,NOENTER,TOOLTIP("Usuario que realiza la impresi�n de la etiqueta del bulto")
CAMPO=FECVERIFICA,NOENTER,TOOLTIP("Fecha en que realiz� la verificaci�n del bulto")
CAMPO=HORAVERIFICA,NOENTER,TOOLTIP("Hora en que realiz� la verificaci�n del bulto")
CAMPO=CODOPEVERIFICA,NOENTER,TOOLTIP("Usuario que realiza la verificaci�n del bulto")
CAMPO=FECFINALIZA,NOENTER,TOOLTIP("Fecha en que se finaliz� el bulto")
CAMPO=HORAFINALIZA,NOENTER,TOOLTIP("Hora en que se finaliz� el bulto")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la �ltima modificaci�n")
CAMPO=HORAMODIF,UPPER,NOENTER,TOOLTIP("Hora de la �ltima modificaci�n")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Usuario que realiza la �ltima modificaci�n")
CAMPO=CODCOMEN,NOUPDATE,TOOLTIP("C�digo de los comentarios a la cabecera del bulto")
CAMPO=VDEXTRA,UPDATE,TOOLTIP("Datos adicionales externos a V10")
CAMPO=VALIDAR,AUXILIAR,UPPER,POSTCHANGE=FVERIFICA("SNT- ","Los posibles valores son S(i), N(o) y (T)erminar.")
CAMPO=PESOD,AUXILIAR,NOUPDATE,OCULTO,"#L#############"
CAMPO=PESOH,AUXILIAR,NOUPDATE,OCULTO,"#L#############"
CAMPO=MENHOST,AUXILIAR,NOUPDATE,OCULTO,"_255_"

CAMPO=ULTIMO,AUXILIAR,NOUPDATE,OCULTO,"_"
CAMPO=LLEVAALBARAN,AUXILIAR,NOUPDATE,OCULTO,"@L"
CAMPO=DIFERENCIAPESO,AUXILIAR,NOUPDATE,OCULTO,"@@@@@@@@"
CAMPO=CBSTATUS,AUXILIAR,OCULTO,"@L@@@"
CAMPO=MARGEN,AUXILIAR,OCULTO,"@@@@@@"
CAMPO=ARTICULOS,AUXILIAR,OCULTO,"_2000"
CAMPO=ARTVERIF,AUXILIAR,OCULTO,"_60___________________"
CAMPO=CODCLASE,AUXILIAR,OCULTO,"_40_"

CAMPO=V10HTML,NOUPDATE,AUXILIAR,OCULTO,"_16000_"


  CURSOR=CSELSCAN SELECT LTRIM(TEXTO,'0') CODBULTO,ROWID MIROWIDSCAN FROM VDSCANLECT 
                     WHERE :MIROWIDSCAN IS NULL AND (REDSCAN, SCANNER) IN
                (SELECT ORD.IDINFOLECTURA, ORD.SCANNER
                   FROM VDORDENADORES ORD, SYS.V_$SESSION S
                  WHERE AUDSID = USERENV ('SESSIONID')
                        AND ORD.ORDENADOR =:ORDENADOR);
                        
  CURSOR=CDELSCAN DELETE VDSCANLECT WHERE ROWID=:MIROWIDSCAN;                      
  
  CURSOR=CDELALLSCAN DELETE VDSCANLECT 
                      WHERE (REDSCAN, SCANNER) IN
                            (SELECT ORD.IDINFOLECTURA, ORD.SCANNER
                               FROM VDORDENADORES ORD, SYS.V_$SESSION S
                              WHERE AUDSID = USERENV ('SESSIONID') AND ORD.ORDENADOR =:ORDENADOR);

CURSOR=CVERPEQUENA SELECT :CODBULTO
                    FROM VDBULTOLIN BUL,VDARTIC ART
                    WHERE ART.CODART=BUL.CODART AND BUL.CODBULTO=:CODBULTO
                    HAVING SUM(ART.LARGOUNI*ART.ALTOUNI*ART.ANCHOUNI*BUL.CANTPEDIDA/1000)>VD.GETPROP('CAJAPEQUENA') OR :TIPOBULTO!='U';

CURSOR=CSELHTML BEGIN
                 SELECT '<STYLE TYPE="text/css" MEDIA=screen>'||
                        '.v10ventmedioizq{background-image:url(../img/ventmen/4A.png);background-repeat:repeat;width:18px;height:22px;}'||
                        '.v10ventmedioder{background-image:url(../img/ventmen/5A.png);background-repeat:repeat;width:19px;height:22px;}'||
                        '.v10ventmediomed{background-image:url(../img/ventmen/6A.png);background-repeat:repeat;width:25px;height:22px;}'||
                        '.v10ventabajoizq{background-image:url(../img/ventmen/7A.png);background-repeat:norepeat;width:18px;height:22px;}'||
                        '.v10ventabajomed{background-image:url(../img/ventmen/8A.png);background-repeat:repeat;height:22px;}'||
                        '.v10ventabajoder{background-image:url(../img/ventmen/9A.png);background-repeat:norepeat;width:25px;height:22px;}'||
                        '</STYLE>' INTO :V10HTML
                  FROM DUAL;
                END;@

CURSOR=CSELSTDHTML BEGIN
                 SELECT '<STYLE TYPE="text/css" MEDIA=screen>'||
                        '.v10ventmedioizq{background-image:url(../img/ventmen/4.png);background-repeat:repeat;width:18px;height:22px;}'||
                        '.v10ventmedioder{background-image:url(../img/ventmen/5.png);background-repeat:repeat;width:19px;height:22px;}'||
                        '.v10ventmediomed{background-image:url(../img/ventmen/6.png);background-repeat:repeat;width:25px;height:22px;}'||
                        '.v10ventabajoizq{background-image:url(../img/ventmen/7.png);background-repeat:norepeat;width:18px;height:22px;}'||
                        '.v10ventabajomed{background-image:url(../img/ventmen/8.png);background-repeat:repeat;height:22px;}'||
                        '.v10ventabajoder{background-image:url(../img/ventmen/9.png);background-repeat:norepeat;width:25px;height:22px;}'||
                        '</STYLE>' INTO :V10HTML
                  FROM DUAL;
                END;@


CURSOR=CSELERRART DECLARE 
                CURSOR C1 IS SELECT DISTINCT AR.CODART,AR.DESART,AR.PESOUNI
                              FROM VDBULTOLIN LB,VDARTIC AR
                              WHERE LB.CODBULTO=:CODBULTO AND
                                    LB.CODART=AR.CODART AND ROWNUM<20;
               BEGIN
                :ARTICULOS:='';
                FOR I IN C1 LOOP
                    IF :ARTICULOS IS NOT NULL THEN :ARTICULOS:=:ARTICULOS||' ';
                     END IF;
                    :ARTICULOS:=:ARTICULOS||I.CODART||' '||RPAD(I.DESART,32)||I.PESOUNI||'\n';
                END LOOP;
               END;@
  
CURSOR=CVERIART SELECT DISTINCT CODCLASE
                  FROM VDARTIC AR,VDBULTOLIN LB, VDCLASEARTIC CLAAR
                  WHERE LB.CODBULTO=:CODBULTO AND LB.CODART=AR.CODART AND AR.TPCVERIF=100
                  AND AR.CODART=CLAAR.CODART 
                  AND CLAAR.CODCLASIF='TIPOART';

CURSOR=CSELARTAVERIF DECLARE
                       CURSOR C1 IS SELECT DISTINCT AR.CODART||' '||AR.DESART TEXTO
                             FROM VDARTIC AR,VDBULTOLIN LB, VDCLASEARTIC CLAAR
                             WHERE LB.CODBULTO=:CODBULTO AND LB.CODART=AR.CODART AND AR.TPCVERIF=100
                                   AND AR.CODART=CLAAR.CODART 
                                   AND CLAAR.CODCLASIF='TIPOART' AND CODCLASE=:CODCLASE;
                      BEGIN
                        :ARTICULOS:='';
                         FOR I IN C1 LOOP 
                            IF :ARTICULOS IS NOT NULL THEN :ARTICULOS:=:ARTICULOS||' ';
                              END IF;
                            :ARTICULOS:=:ARTICULOS||I.TEXTO||'\n';
                          END LOOP;
                       END;@

CURSOR=CSELAANULAR DECLARE
                       CURSOR C1 IS SELECT AR.CODART||' '||AR.DESART||' '||SUM(CANTSERVIDA) TEXTO
                             FROM VDARTIC AR,VDBULTOLIN LB
                             WHERE LB.CODBULTO=:CODBULTO AND LB.CODART=AR.CODART AND AR.SWTANULADO='N'
                             GROUP BY AR.CODART,AR.DESART;
                      BEGIN
                        :ARTICULOS:='';
                         FOR I IN C1 LOOP 
                            IF :ARTICULOS IS NOT NULL THEN :ARTICULOS:=:ARTICULOS||' ';
                              END IF;
                            :ARTICULOS:=:ARTICULOS||I.TEXTO||'\n';
                          END LOOP;
                       END;@

CURSOR=CSELDESSCAN SELECT DECODE(:ULTSCAN,1,'',2,'',3,'',4,'','SIN SCANNER') DESSCAN FROM DUAL;

CURSOR=CCOUNT SELECT COUNT(*) TOTALBULTOS FROM VDBULTOCAB
              WHERE CODPED=:CODPED AND SEQPED=:SEQPED AND CODDIV=:CODDIV AND ANOPED=:ANOPED ; 

CURSOR=CDESDIV SELECT DESDIV
                 FROM VDDIVIS
                WHERE CODDIV=:CODDIV;

CURSOR=CSELSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:CBSTATUS AND TIPOSTATUS='BUC';
 

CURSOR=CSELMENHOST SELECT MENHOST
                     FROM VDPEDIDOCAB
                    WHERE CODDIV=:CODDIV AND ANOPED=:ANOPED AND
                          CODPED=:CODPED AND SEQPED=:SEQPED;

CURSOR=CSELPREPARADO SELECT :CBSTATUS 
                       FROM VDBULTOCAB
                                WHERE CODBULTO=:CODBULTO AND STATUS>=VDST.FBUCPREPARADO AND STATUS=:CBSTATUS;
                                
CURSOR=CSELTERMIN SELECT NVL(:TVALIDAR,'S') VALIDAR
                       FROM VDBULTOCAB
                                WHERE CODBULTO=:CODBULTO AND STATUS<VDST.FBUCENEXPED AND STATUS=:CBSTATUS;

CURSOR=CSELLINPEND SELECT CODBULTO 
                     FROM VDBULTOLIN
                    WHERE CODBULTO=:CODBULTO AND STATUS<VDST.FBULSERVIDA;


CURSOR=CCALCPESOCOR SELECT :PESOTEORICO-MIN(AR.PESOUNI)*VD.GETPROP('PORMINPESO')/100 PESOD,
                           :PESOTEORICO+MIN(AR.PESOUNI)*VD.GETPROP('PORMINPESO')/100  PESOH,
                           MIN(AR.PESOUNI)*VD.GETPROP('PORMINPESO')/100 MARGEN
                     FROM VDBULTOLIN LB,VDARTIC AR
                     WHERE LB.CODBULTO=:CODBULTO 
                       AND LB.CODART=AR.CODART;

CURSOR=CCALCDIFERENCIA SELECT A+B DIFERENCIAPESO
                         FROM    (SELECT -:PESOTEORICO + :PESOREAL A 
                                 FROM DUAL 
                                WHERE :PESOREAL < :PESOTEORICO
                                         UNION  
                                         SELECT 0 FROM DUAL ) A,
                                        (SELECT -:PESOTEORICO + :PESOREAL B 
                                           FROM DUAL 
                                          WHERE :PESOREAL > :PESOTEORICO
                                         UNION
                                         SELECT 0 FROM DUAL) B
                              WHERE A+B <> 0 AND ROWNUM < 2;

CURSOR=CVERIFPESO SELECT :PESOH PESOH 
                    FROM DUAL 
                   WHERE (:PESOREAL BETWEEN :PESOD AND :PESOH OR :TIPOBULTO!='U');


CURSOR=CVERIFANU SELECT :SWTANULAR SWTANULAR  FROM DUAL
                  WHERE :SWTANULAR='N' OR 
                        NOT EXISTS (SELECT ART.CODART
                                     FROM VDARTIC ART,VDBULTOLIN BUL
                                     WHERE BUL.CODBULTO=:CODBULTO AND BUL.CODART=ART.CODART AND ART.SWTANULADO='N');

CURSOR=CVERIFMENHOST SELECT :MENHOST MENHOST FROM DUAL
                     WHERE :MENHOST IS NULL;


                          

CURSOR=CVERNOMODIF SELECT :CBSTATUS CBSTATUS 
                     FROM VDBULTOCAB
                    WHERE CODBULTO=:CODBULTO AND STATUS=:CBSTATUS
                     AND STATUS>=VDST.FBUCPREPARADO;

CURSOR=CUPDBULTO UPDATE VDBULTOCAB 
                    SET FECMODIF=VD.FECHASYS,
                        HORAMODIF=VD.HORASYS,
                        CODOPEVERIFICA=VDUSER.GETUSER,
                        FECVERIFICA=VD.FECHASYS,
                        HORAVERIFICA=VD.HORASYS,
                        STATUS=DECODE(:VALIDAR,'S',VDST.FBUCAEXPED,
                                               'T',VDST.FBUCENEXPED,
                                                :CBSTATUS)
                  WHERE CODBULTO=:CODBULTO;


CURSOR=CSELBULCNT SELECT :TIPOBULTO FROM VDBULTOCAB WHERE TIPOBULTO='C' AND CODBULTO=:CODBULTO;

CURSOR=CSELULTIMO SELECT  VDBULTO.DAMEULTBULTO(:CODBULTO) ULTIMO FROM DUAL;

CURSOR=CUPDBULCNT UPDATE VDBULTOCAB 
                    SET FECMODIF=VD.FECHASYS,
                        HORAMODIF=VD.HORASYS,
                        CODOPEVERIFICA=VDUSER.GETUSER,
                        FECVERIFICA=VD.FECHASYS,
                        HORAVERIFICA=VD.HORASYS,
                        STATUS=DECODE(:VALIDAR,'N',STATUS,'-',STATUS,VDST.FBUCENEXPED)
                   WHERE CODBULTO=:CODBULTO;


CURSOR=CDAMELLEVAALBARAN SELECT VDVERIF.LLEVAALBARAN(:CODBULTO) LLEVAALBARAN FROM VDBULTOCAB WHERE CODBULTO=:CODBULTO;

CURSOR=CLLEVAALBARAN SELECT :LLEVAALBARAN FROM DUAL WHERE :LLEVAALBARAN=1;

CURSOR=CSELVALIDA SELECT :VALIDAR FROM DUAL WHERE :VALIDAR='S'; 
                   

TECLA=3000,FEJECUTA(FDAMEORDENADOR("ORDENADOR"),"",
                    "@CSELSCAN","",
                    "CDELSCAN","",FCOMMIT,"",
                    FPULSATECLAS("F2"),"")
TECLA=SF10,FLEEMENU("VDBULCAB.ZOO")    

BOTON=B1,650,260,80,80,"P",miok.png,F4,"Verificar",INCLUDECSS="background-color: transparent;border-width:0px"


AYUDA=VERIFICACION DE BULTOS
ONLINE={F1} Ayuda {F2} Consulta {F4} Confirmar cambios   {Esc} Salir;

