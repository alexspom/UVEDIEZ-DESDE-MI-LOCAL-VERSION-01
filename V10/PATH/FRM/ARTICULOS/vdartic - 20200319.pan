# MOdulo   : VDARTIC.PAN
# Función  : Mantenimiento de artículos
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# HistOrico de cambios:
MANTENIMIENTO DE ARTICULOS
 Código: _40____________ _100_______________________________________________________________________
 Descripción Alternativa:_70________________________________________________________________________
 Division: _20____  Cod.Nac.:____________      EAN: ______________        Codartdiv: _20____________
 Unidades: _10____  Uni.Host:_10_________ Decimales:@L    Stock:_    Orden salida:_    Traza bulto:_   
 ÏÄÄÄÄÄÄÄÄÄÄÄÄ DIMENSIONES ARTÍCULO ÄÄÄÄË  ÏÄÄÄÄÄÄÄÄÄÄÄÄÄ DATOS LOGISTICOS ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË
 ³ Largo:#L##.#mm. Peso:  #L,###.## gr. ³  ³Uni/Caj:@L@@@@@    Caj/Cap:@L@@@       Caj/Pal:@L@@@    ³
 ³ Ancho:#L##.#mm. Coef.Llenado:@L@     ³  ³Paq/Caj:@L@@@      Uni/Pal:@L@@@@@     Cap/Pal:@L@@@    ³
 ³ Alto: #L##.#mm.                      ³  ³Tipo Vol:_10______ Caj/Cub:@L@@@ Cub/Caj:@L@@ Tumbable _³
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
 ÏÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ DIMENSIONES PAQUETE ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË
 ³Uni/paq.:#L## Largo:#L##.#mm. Ancho:#L##.#mm. Alto:#L##.#mm. Peso:#L,###.###gr  Coef.llenado: @L@ ³
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
 ÏÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ ENCAJADO ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË ÏÄÄÄÄÄÄÄPEDIDOS ÄÄÄÄÄÄÄÄÄË
 ³ Largo:#L###mm. Ancho:#L###mm. Alto:#L###mm.      \Tipo caja:___________³ ³Max.unis:   @L@@@      ³
 ³ Pesar:_            Peso caja llena:#L,###gr.  \Caja defecto:___________³ ³Min.pal %:  #L### @L@@@³
 ³                    Peso caja vacia:#L,###gr. \Palet defecto:___________³ ³Serv.Multip.@L         ³
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
 ÏÄÄÄÄÄÄÄÄÄÄÄÄ    DATOS LOTE     ÄÄÄÄÄÄÄÄÄÄÄÄÄË ÏÄÄÄÄ CLASIFICACION V10 ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË
 ³ Analisis _ Lote _ Muestroteca: _10________  ³ ³ _  Activo      _ Interno   Tipo Ubicacion:_20_____³
 ³ Caduci:@L@  Uni Caduci: _     Fto. Lote:_   ³ ³ _  Etiqueta    _ FMD                              ³  
 ³ Retest:@L@  Uni Retest: _     Muestras: @@L ³ ³ _  Tipo verificación            Porc.Verif:@L@ %  ³
 ³ Aviso: @L@  Uni aviso:  _       Anular: _   ³ ³ Min.Pte: @L                     _1_ Pick Inv      ³
 ³ _ Agrup.Lineas                  Ajuste: _   ³ ³ _ Número de serie   _ Inv.Cont  _1_ Comp.Fin Caja ³
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
 ÏÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ GESTIÓN DE PRECIOS ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË
 ³   PVP Nuevo:  #L,#####               PVD Vigente:#L,#####              PVP con IVA: #L,#####     ³
 ³   PVP Antiguo:#L,#####               PVD Nuevo:  #L,#####              IVA Nuevo:   #L,#####     ³
 ³   Entra Vigor:¿D-MM-Y.YY             PVD Antiguo:#L,#####              IVA Antiguo: #L,#####     ³
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
 ÏÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ RESUMEN STOCK ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË
 ³ Total:@L@,@@@    Libre:@L@,@@@  Devolucion:@L@,@@@ Defectuoso:@L@,@@@  Bloqueado:@L@,@@@         ³
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
   Informacion adicional: _255_________________________________________________
   Comentario @L@@@@@@@    Ultima modificación _32________ ¿D-MM-Y.YY  ________   
|

TABLA=VDARTIC
WLONX=745
PROTECT("ARTICULOS")

#SELECT=EMBCONT/DECODE(EMBPISO,0,1,EMBPISO) CAMASPALET,EMBCONT*UNIEMB UNIPALET,MINPAL,ROUND((MINPAL/DECODE(EMBCONT,0,1,EMBCONT))*100) PORPAL;   
SELECT= EMBCONT*UNIEMB UNIPALET, MINPAL, ROUND((MINPAL/DECODE(EMBCONT,0,1,EMBCONT))*100) PORPAL;   

POSTQUERY=FEJECUTA("CPONPESOCAJC","","+CCALCSTOCK","","+CSELTIPOUBI","")

PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")

PREUPDATE=FEJECUTA("CDAMEPESOCAJC","",
                   "CSELMODIF","ERROR EN FECHA DE MODIFICACION",
                   "CACTUALIZACOMENTARIOS","No puedo actualizar comentarios",
                   "CUPDAMINPAL","No puedo actualizar minpal")
#                   "+CALCAJASCAMA","El valor de ejemplares/pallet es mayor de 5 digitos"

CURSOR=CCALCSTOCK SELECT SUM(CANTIDAD) STKTOTAL,
                         SUM(DECODE(BLOQUEOS,'0000000000',CANTIDAD,0)) STKLIBRE,
                         SUM(DECODE(BLOQUEOS,'0000010000',CANTIDAD,0)) STKDEV,
                         SUM(DECODE(BLOQUEOS,'0000020000',CANTIDAD,0)) STKDEF,
                         SUM(DECODE(BLOQUEOS,'0000000000',0,CANTIDAD)) STKBLOQ
                   FROM VDSTOCK WHERE CODART=:CODART;
                   
#CURSOR=CALCAJASCAMA SELECT DECODE(:EMBPISO,0,1,:EMBPISO)*:CAMASPALET EMBCONT,:UNIEMB*DECODE(:EMBPISO,0,1,:EMBPISO)*:CAMASPALET UNIPALET 
#                        FROM DUAL
#						WHERE :UNIEMB*DECODE(:EMBPISO,0,1,:EMBPISO)*:CAMASPALET<100000;
CURSOR=CSELUNIPAL SELECT :EMBCONT*:UNIEMB UNIPALET FROM DUAL;						

                   
CURSOR=CACTUALIZACOMENTARIOS BEGIN
                              UPDATE VDCLASEARTIC SET CODCLASE=:UBIGENERAL WHERE CODART=:CODART AND CODCLASIF='GENERAL';
                             END;@    

CAMPO=IMAGEN,OCULTO,AUXILIAR,"_255_____",NOUPDATE
CAMPO=IMAGEN2,OCULTO,AUXILIAR,"_255_____",NOUPDATE
CAMPO=CODART,NOUPDATE,TOOLTIP("Código del artículo")
CAMPO=DESART,MIXED,TOOLTIP("Designación del artículo")
CAMPO=DESARTALT,MIXED,TOOLTIP("Designación del artículo para el proveedor")
CAMPO=CODDIV,POSTCHANGE=FEJECUTA("CDIVNULL","La división no puede estar en blanco"),
               COMBOX("CLISTADIVIS")
CAMPO=CODNAC,TOOLTIP("Código nacional")
CAMPO=CODEAN
CAMPO=CODARTDIV,TOOLTIP("Código del artículo para la división")
CAMPO=UNIDADES,TOOLTIP("Unidades en las que se mide el artículo en V10"),
               CONTEXTUAL=FEJECUTAFORM("VDUNIDADES","N","","","UNIDADES=:UNIDAD","Selección de unidades","S"),
               COMBOX("CLISTAUNIDADES"),POSTCHANGE=FDESIGNACION("CSELUNIDADES","No existen las unidades V10")
CAMPO=UNIDADESHOST,TOOLTIP("Unidades en las que mide el artículo el Host"),
               CONTEXTUAL=FEJECUTAFORM("VDUNIDADES","N","","","UNIDADESHOST=:UNIDAD","Selección de unidades","S"),
               COMBOX("CLISTAUNIDADESHOST"),POSTCHANGE=FDESIGNACION("CSELUNIDADESHOST","No existen las unidades Host")
CAMPO=DECIMALES,TOOLTIP("Numero de decimales en la representación de cantidades")
CAMPO=SWTSTOCK,TOOLTIP("Indica si el producto controla stock"),POSTCHANGE=FVERIFICA("SN ","Debe introducir S(i) o N(o)"),CHECKBOX("N","S")
CAMPO=ORDENSAL,TOOLTIP("Orden de salida del articulo C(aducidad) F(ifo) R(etest) L(ote)"),POSTCHANGE=FVERIFICA("CFRL","Debe introducir C(aducidad) F(ifo) R(etest) L(ote)"),COMBOX("C Caducidad","F Fifo","R Retest","L Lote")
CAMPO=TRAZABULTO,TOOLTIP("Indica si el artículo precisa trazabilidad de bulto"),POSTCHANGE=FVERIFICA("SN ","Debe introducir S(i) o N(o)"),CHECKBOX("N","S")
CAMPO=LARGOUNI,TOOLTIP("Largo de la unidad en mm.")
CAMPO=PESOUNI,TOOLTIP("Peso de la unidad en gramos")
CAMPO=UNIEMB,TOOLTIP("Unidades por caja")
CAMPO=EMBPISO,TOOLTIP("Cajas por piso de paletización"),POSTCHANGE=FEJECUTA("CVERCAMAS","",FENRANGO("0-:EMBCONT","Debe introducir un número en el rango 0-:EMBCONT"),"")
#,POSTCHANGE=FDESIGNACION("+CALCAJASCAMA","El valor de ejemplares/pallet es mayor de 5 digitos")
CAMPO=EMBCONT,TOOLTIP("Embalajes por contenedor"),POSTCHANGE=FEJECUTA("CSELUNIPAL","ERROR al calcular unidades por palet","+CVERCAMAS","")
CAMPO=ANCHOUNI,TOOLTIP("Ancho de la unidad en mm.")
CAMPO=COEFUNI,TOOLTIP("Coeficiente de volumetría"),POSTCHANGE=FENRANGO("0-100","Debe introducir un numero entre 0 y 100")
CAMPO=PAQCAJA,AUXILIAR,TOOLTIP("Paquetes por caja o Paquetes por embalajes"),NOENTER
CAMPO=UNIPALET,AUXILIAR,NOUPDATE,NOENTER
CAMPO=CAMASPALET,AUXILIAR,NOENTER
#,POSTCHANGE=FDESIGNACION("+CALCAJASCAMA","El valor de ejemplares/pallet es mayor de 5 digitos"),NOENTER
CAMPO=ALTOUNI,TOOLTIP("Alto de la unidad en mm.")
CAMPO=TIPOVOL,TOOLTIP("Código de la volumetría asociada al articulo"),POSTCHANGE=FDESIGNACION("CSELTIPOVOL"," No existe volumetría "),
               CONTEXTUAL=FEJECUTAFORM("VDVOLUMETRIA","N","","","TIPOVOL=:TIPOVOL","Selección de volumetría","S"),
               COMBOX("CLISTATIPOVOL")
CAMPO=CAJACUBETA
CAMPO=CUBETACAJA
CAMPO=SWTTUMBABLE,TOOLTIP("Indica si el producto se considera tumbable en la volumetria"),POSTCHANGE=FVERIFICA("SN ","Debe introducir S(i) o N(o)"),CHECKBOX("N","S")
CAMPO=UNIPAQ,TOOLTIP("Unidades por paquete"),POSTCHANGE=FEJECUTA("+CSELPAQCAJ","")
CAMPO=LARGOPAQ,TOOLTIP("Largo del paquete en mm.")
CAMPO=ANCHOPAQ,TOOLTIP("Ancho del paquete en mm.")
CAMPO=ALTOPAQ,TOOLTIP("Alto del paquete en mm.")
CAMPO=PESOPAQ,TOOLTIP("Peso del paquete en gramos")
CAMPO=COEFPAQ,TOOLTIP("Coeficiente de ajuste de volumetría del paquete"),POSTCHANGE=FENRANGO("0-100","Debe introducir un numero entre 0 y 100")
CAMPO=LARGOCAJC,TOOLTIP("Longitud de la caja completa en mm.")
CAMPO=ANCHOCAJC,TOOLTIP("Ancho de la caja completa en mm.")
CAMPO=ALTOCAJC,TOOLTIP("Alto de la caja completa en mm.")
CAMPO=TIPOCAJC,TOOLTIP("Tipo de caja completa"),POSTCHANGE=FDESIGNACION("+CSELTIPOCAJC","No existe volumetría"),
               CONTEXTUAL=FEJECUTAFORM("VDLISTACOMPLETAS","S","","TIPOVOL='COMPLETA'","TIPOCAJC=:TIPOCAJA","Selección de caja","S"),
               COMBOX("CLISTATIPOCAJC")
CAMPO=MAXUNI,TOOLTIP("Maximo a servir por unidades")
CAMPO=SWTPESACAJA,TOOLTIP("Indica si se han de pesar cajas completas en las instalación"),POSTCHANGE=FVERIFICA("SN ","Debe introducir S(i) o N(o)"),CHECKBOX("N","S")
CAMPO=PESOCAJCLLENA,NOENTER,AUXILIAR,TOOLTIP("Peso de la caja completa llena en gr."),POSTCHANGE=FDESIGNACION("+CPESOCAJC","")
CAMPO=TIPOEMBADEF,TOOLTIP("Tipo de embalaje por defecto"),POSTCHANGE=FDESIGNACION("CSELEMBADEF","No existe embalaje por defecto"),
               CONTEXTUAL=FEJECUTAFORM("VDTIPOEMBA","N","","","TIPOEMBADEF=:TIPOEMBA","Selección de tipo de embalaje","S"),
               COMBOX("CLISTAEMBA")
CAMPO=PORPAL,AUXILIAR,TOOLTIP("Porcentaje del palet que debe ser consideradas como un palet completo"),POSTCHANGE=FEJECUTA("CCALCMINPAL","No puedo calcular el minpalet")
CAMPO=MINPAL,AUXILIAR,TOOLTIP("Mínimo numero de cajas que deben ser consideradas como un palet completo"),NOENTER
CAMPO=PESOCAJCAUX,AUXILIAR,TOOLTIP("Peso de la caja completa vacia en gr."),POSTCHANGE=FDESIGNACION("CPESOCAJCLLENA","ERROR CALCULANDO PESO DE CAJA LLENA")
CAMPO=PESOCAJC,OCULTO,"#L,######.###"
CAMPO=TIPOCONTEDEF,TOOLTIP("Tipo de contenedor por defecto"),POSTCHANGE=FDESIGNACION("CSELCONTEDEF","No existe contenedor por defecto"),
               CONTEXTUAL=FEJECUTAFORM("VDTIPOCONTE","N","","","TIPOCONTEDEF=:TIPOCONTE","Selección de tipo de contenedor","S"),
               COMBOX("CLISTACONTE")
CAMPO=PEDMULTIPLO,TOOLTIP("El producto ha de ser pedido en multiplos de esta cantidad")
CAMPO=SWTANALISIS,TOOLTIP("Indica si el producto esta sujeto a analisis en entradas"),POSTCHANGE=FVERIFICA("SN ","Debe introducir S(i) o N(o)"),CHECKBOX("N","S")
CAMPO=SWTLOTE,TOOLTIP("Indica si el producto controla lote"),POSTCHANGE=FVERIFICA("SN ","Debe introducir S(i) o N(o)"),CHECKBOX("N","S")
CAMPO=MUESTROTECA,TOOLTIP("Area donde se llevarán las muestras")
CAMPO=SWTACTIVO,TOOLTIP("Indica si el producto esta activo"),POSTCHANGE=FVERIFICA("SN ","Debe introducir S(i) o N(o)"),CHECKBOX("N","S"),NOUPDATE("ARTICULOS")
CAMPO=SWTGENERICO,TOOLTIP("Indica si el producto debe tomar designacion de comentarios en albaranes"),POSTCHANGE=FVERIFICA("SN ","Debe introducir S(i) o N(o)"),CHECKBOX("N","S"),NOUPDATE("V10")
CAMPO=UBIGENERAL,NOENTER,AUXILIAR,WHERE=CODART IN (SELECT CODART FROM VDCLASEARTIC WHERE CODCLASIF='GENERAL' AND CODCLASE=:UBIGENERAL);
CAMPO=TCADUC,TOOLTIP("Fecha de caducidad a partir de la actual al crear un nuevo lote automatico")
CAMPO=UNICADUC,TOOLTIP("Unidades en las que se mide el tiempo de caducidad puede ser D(ias) o M(eses)"),
               POSTCHANGE=FENRANGO("D,M","Debe introducir D(ias) o M(eses)"),COMBOX("M Meses","D Días")
CAMPO=FORMATOLOTE,TOOLTIP("Formato de lote generado automaticamente puede ser U(nico) E(ntrada) A(ño) M(es) D(ía)"),COMBOX("U Único (Asignado en TipoRecep)","E Entrada (Cod.Recep)","A Año (yyyy)","M Mes (yyyymm)", "D Día (yyyymmdd)"),POSTCHANGE=FVERIFICA("UEAMD ","Debe introducir U(nico) E(ntrada) A(ño) o M(es)")
CAMPO=SWTETIQ,TOOLTIP("Indica si se puede leer la etiqueta del producto"),POSTCHANGE=FVERIFICA("SN ","Debe introducir S(i) o N(o)"),CHECKBOX("N","S"),NOUPDATE("ARTICULOS")
CAMPO=SWTFMD,TOOLTIP("Artículo sujeto a FMD"),CHECKBOX("N","S")
CAMPO=TRETEST,TOOLTIP("Fecha de retest al crear un nuevo lote automatico")
CAMPO=UNIRETEST,TOOLTIP("Unidades en las que se mide el tiempo de retest puede ser D(ias) o M(eses)"),
               POSTCHANGE=FENRANGO("D,M","Debe introducir D(ias) o M(eses)"),COMBOX("M Meses","D Días")
CAMPO=NUMMUESTRAS,TOOLTIP("Unidades a muestrear")
CAMPO=TIPOVERIFCIEGA,TOOLTIP("Tipo de verificación ciega que se hará con este artículo:\n(C)iega: la pantalla no muestra nada referente a este artículo\n(S)emiciega: la pantalla muestra el artículo pero no la cantidad\n(N)ula: la pantalla lo muestra todo"),
      COMBOX("CTIPOVERIFCIEGA"),POSTCHANGE=FVERIFICA("CSN ","Debe introducir C(iega) S(emiciega) o N(ula)")
CAMPO=TPCVERIF,TOOLTIP("Porcentaje de bultos con el producto que han de pasar por verificación"),POSTCHANGE=FENRANGO("0-100","Debe introducir un numero entre 0 y 100")
CAMPO=TAVISA,TOOLTIP("Fecha de aviso antes de que un producto entre en retest")
CAMPO=UNIAVISA,TOOLTIP("Unidades en las que se mide el tiempo de aviso puede ser D(ias) o M(eses)"),POSTCHANGE=FENRANGO("D,M","Debe introducir D(ias) o M(eses)"),COMBOX("M Meses","D Días")
CAMPO=SWTANULADO,TOOLTIP("Indica si el producto tiene preanulado el precio"),POSTCHANGE=FVERIFICA("SNI ","Debe introducir S(i) o N(o)o I(ndiferente)"),COMBOX("S Sí","N No","I Indiferente")
CAMPO=MINPENDIENTE,TOOLTIP("Mínimo a partir del cual no se genera nuevo pedido si queda pendiente")
CAMPO=PICKINV,TOOLTIP("Si se sirve por picking inverso (S O P), o (N)o\n (S)i: picking inverso y genera restos\n (P)repicking: picking inverso sin generar restos"),COMBOX("N - No","S - Sí","P - Prepicking"),POSTCHANGE=FVERIFICA("SNP ","Debe introducir S(i), N(o) P(repicking)")
CAMPO=AGRUPALIN,TOOLTIP("Indica si la ubicación ha de agrupar las lineas con las mismas caracteristicas"),POSTCHANGE=FVERIFICA("SN ","Debe introducir S(i) o N(o)"),CHECKBOX("N","S")
CAMPO=TIPOAJUSTE,TOOLTIP("Indica como se han de ajustar los pedidos que no vengan en multiplos\nD(efecto) E(xceso) R(edondeo) N(o ajustar)"),COMBOX("D Defecto","E Exceso","R Redondeo","N No ajustar")
CAMPO=SWTNUMEROSERIE,TOOLTIP("Indicador de si el artículo tiene número de serie o no. Posibles valores S o N"),CHECKBOX("N","S"),POSTCHANGE=FVERIFICA("SN ","Debe introducir S(i) o N(o)")
CAMPO=INVCONT,TOOLTIP("Indica si el articulo ha de ser sometido a inventario continuo"),CHECKBOX("N","S"),POSTCHANGE=FVERIFICA("SN ","Debe introducir S(i) o N(o)")
CAMPO=PETINICAJA,TOOLTIP("Al finalizar una caja o palet que se ha de comprobar: A(rticulo) L(ote) o C(etiqueta caja)"),COMBOX("A Articulo","L Lote","C Etiq.Caja"),POSTCHANGE=FVERIFICA("ALC ","Debe introducir S(i) o N(o)")
CAMPO=CONFPICKING,TOOLTIP("La confirmación de fin de caja se ha de realizar por B(oton), L(ector) o N(inguno, por no ser necesaria la confirmación)"),COMBOX("B Botón","L Lector","N Ninguno"),WPOSX=-16,OCULTO,"_"
########MODULOS DE PRECIOS
CAMPO=PVPNUEVO,TOOLTIP("Precio nuevo")
CAMPO=PVDVIGENTE,TOOLTIP("Precio de venta al distribuidor vigente")
CAMPO=PVPIVAVIGENTE,TOOLTIP("Precio con IVA vigente")
CAMPO=PVPANTIGUO,TOOLTIP("Precio antiguo")
CAMPO=PVDNUEVO,TOOLTIP("Precio de venta al distribuidor nuevo")
CAMPO=PVPIVANUEVO,TOOLTIP("Precio con IVA nuevo")
CAMPO=FECVIGNP,TOOLTIP("Fecha de entrada en vigor del nuevo precio")
CAMPO=PVDANTIGUO,TOOLTIP("Precio de venta al distribuidor antiguo")
CAMPO=PVPIVAANTIGUO,TOOLTIP("Precio con IVA antiguo")

###MODULO DE STOCK####
CAMPO=STKTOTAL,AUXILIAR,NOUPDATE
CAMPO=STKLIBRE,AUXILIAR,NOUPDATE
CAMPO=STKDEV,AUXILIAR,NOUPDATE
CAMPO=STKDEF,AUXILIAR,NOUPDATE
CAMPO=STKBLOQ,AUXILIAR,NOUPDATE
CAMPO=VDEXTRA
CAMPO=CODCOMEN,TOOLTIP("Código de comentario asociado al producto"),NOUPDATE
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizO la última modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro"),COMBOX("CALENDARIO")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CDIVNULL SELECT :CODDIV FROM DUAL WHERE :CODDIV IS NOT NULL;

CURSOR=CCALCMINPAL SELECT ROUND(:EMBCONT*:PORPAL/100) MINPAL FROM DUAL;

CURSOR=CSELSTSAP SELECT DESIGNACIONSAP DESESTADO FROM XVDDESIGNA WHERE CODIGOSAP=:TIPOART AND CAMPOSAP='STMAT';

CURSOR=CSELPROPIETARIO SELECT DESIGNACIONSAP DESPROPIETARIO FROM XVDDESIGNA WHERE CODIGOSAP=:PROPIETARIO AND CAMPOSAP='PROPIETARIO';

CURSOR=CLISTATIPOVOL SELECT TIPOVOL,DESVOL FROM VDVOLUMETRIA ORDER BY TIPOVOL;
CURSOR=CLISTATIPOCAJC SELECT TIPOCAJA, DESCAJA, TIPOEMBA FROM VDCAJAS WHERE  TIPOVOL='COMPLETA' ORDER BY TIPOVOL, TIPOCAJA;

CURSOR=CTIPOVERIFCIEGA SELECT * FROM
                            ( SELECT 'C' T,'Ciega' FROM DUAL UNION
                              SELECT 'S' T,'Semiciega' FROM DUAL UNION
                              SELECT 'N' T,'En la pantalla se muestra todo' FROM DUAL)
                       ORDER BY DECODE(T,'N',0,'S',1,'C',2);



CURSOR=CLISTACONTE SELECT TIPOCONTE, DESTIPOCONTE FROM VDTIPOCONTE ORDER BY TIPOCONTE;

CURSOR=CLISTAEMBA SELECT TIPOEMBA, DESTIPOEMBA FROM VDTIPOEMBA ORDER BY TIPOEMBA;

CURSOR=CLISTADIV SELECT CODDIV FROM VDDIVIS ORDER BY CODDIV;

CURSOR=CLISTAUNIDADESHOST SELECT DISTINCT UNIDADORIGEN UNIDADESHOST FROM VDCONVERSIONES;

CURSOR=CLISTAUNIDADES SELECT DISTINCT UNIDADDESTINO UNIDADES FROM VDCONVERSIONES;

CURSOR=CVERIFMINPAL SELECT :MINPAL FROM DUAL WHERE :MINPAL < :EMBCONT;

CURSOR=CPONPESOCAJC SELECT :PESOCAJC PESOCAJCAUX FROM DUAL;

CURSOR=CDAMEPESOCAJC SELECT :PESOCAJCAUX PESOCAJC FROM DUAL;

CURSOR=CPESOCAJCLLENA SELECT :PESOCAJCAUX + (:UNIEMB * :PESOUNI) PESOCAJCLLENA FROM DUAL;

CURSOR=CPESOCAJC SELECT :PESOCAJCLLENA - (:UNIEMB * :PESOUNI) PESOCAJCAUX FROM DUAL WHERE :PESOCAJCLLENA>0;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CSELDIVIS SELECT DESDIV FROM VDDIVIS WHERE CODDIV=:CODDIV;

CURSOR=CSELUNIDADES SELECT UNIDAD UNIDADES FROM VDUNIDADES WHERE UNIDAD=:UNIDADES;
CURSOR=CSELUNIDADESHOST SELECT UNIDAD UNIDADESHOST FROM VDUNIDADES WHERE UNIDAD=:UNIDADESHOST;

CURSOR=CSELEMBADEF SELECT :TIPOEMBADEF FROM DUAL WHERE :TIPOEMBADEF IS NULL OR :TIPOEMBADEF IN (SELECT TIPOEMBA FROM VDTIPOEMBA);
CURSOR=CSELCONTEDEF SELECT :TIPOCONTEDEF FROM DUAL WHERE :TIPOCONTEDEF IS NULL OR :TIPOCONTEDEF IN (SELECT TIPOCONTE FROM VDTIPOCONTE);

CURSOR=CSELTIPOVOL SELECT :TIPOVOL FROM VDVOLUMETRIA WHERE TIPOVOL=:TIPOVOL;

CURSOR=CSELTIPOCAJC SELECT :TIPOCAJC FROM VDCAJAS WHERE TIPOVOL='COMPLETA' AND TIPOCAJA=:TIPOCAJC
                     UNION
                    SELECT :TIPOCAJC FROM DUAL WHERE :TIPOCAJC IS NULL;


CURSOR=CSELTIPOUBI SELECT CODCLASE UBIGENERAL FROM VDCLASEARTIC WHERE CODCLASIF='GENERAL' AND CODART=:CODART;

CURSOR=CUPDAMINPAL UPDATE VDARTIC SET MINPAL=:MINPAL WHERE CODART=:CODART;

                    
TECLA=SF10,FLEEMENU("VDARTIC.ZOO")
TECLA=3000,FPULSATECLAS("F2")

CURSOR=CSELLECTURA DECLARE 
                   MITEXTO VARCHAR2(1024); 
                   MIROWIDSCAN VARCHAR2(1024);  
                    BEGIN
                     :V10EVAJAX:=0;
                     :DUMMY:=NVL(:DUMMY,0)+1;
                     SELECT NVL(LTRIM(TEXTO,'0'),'0'),ROWID INTO MITEXTO,MIROWIDSCAN FROM VDSCANLECT 
                     WHERE MIROWIDSCAN IS NULL AND (REDSCAN, SCANNER) IN
                           (SELECT ORD.IDINFOLECTURA, ORD.SCANNER
                               FROM VDORDENADORES ORD
                                 WHERE ORD.ORDENADOR =VDUSER.GETHOSTNAME)
                        AND ROWNUM=1;
                     DELETE VDSCANLECT WHERE ROWID=MIROWIDSCAN; 
                     IF :MIROWID IS NULL THEN  
                        :V10EVAJAX:=3000;
                        :CODART:=MITEXTO;
                      ELSE 
                      :V10EVAJAX:=-1;
                      END IF; 
                     COMMIT;
                     EXCEPTION WHEN NO_DATA_FOUND THEN 
                     IF MOD(:DUMMY,10)=0 THEN :V10EVAJAX:=0;
                        ELSE          :V10EVAJAX:=-1;
                      END IF;
                    END;@ 
                    
CURSOR=CCUENTA BEGIN
                     :DUMMY1:=NVL(:DUMMY1,0)+1;
                     IF MOD(:DUMMY1,20)=0 THEN :V10EVAJAX:=0;
                        ELSE          :V10EVAJAX:=-1;
                      END IF;
                    END;@ 
CURSOR=CSELPAQCAJ SELECT DECODE(NVL(:UNIPAQ,1),1,:UNIEMB,0,0,:UNIEMB/:UNIPAQ) PAQCAJA FROM DUAL;
CURSOR=CVERCAMAS SELECT :EMBCONT/DECODE(:EMBPISO,0,1,:EMBPISO) CAMASPALET FROM DUAL;

CURSOR=CLISTADIVIS SELECT CODDIV,DESDIV FROM VDDIVIS ORDER BY CODDIV;


#AJAX(SCANNER,"","C","","CSELLECTURA","CODART,DUMMY",10)
#AJAX(PRUEBA,"","C","","CCUENTA","DUMMY1",0.1)