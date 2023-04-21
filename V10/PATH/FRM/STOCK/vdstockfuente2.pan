###################################################################
#Módulo: VDSTOCKFUENTE2.PAN
#Funcionalidad :  Pantalla para consulta detalada de los registros de la tabla vdstockfuente
#Autor: FGS      
#Fecha: 17-07-2008
###################################################################
# Histórico de cambios:
DETALLE DE REGISTROS PARA CREACION DE STOCK
 
 Estado:      @L@@@ _30___________________________
 
 Ubicación:   _20___________ _20_________    Contenedor: __________________ __________ 
 
 Artículo:    _40_________________ _100____________________________________  Lote: _40_________________  
 
 Cantidad Host: #########.#### _10_   Uniemb Host: #########.####  EmbCont: @L@@@   Tipo Embalaje: __________ 
 
 Peso Unit:   ############  Precio Unit: #######.#### Bulto: __________________ Bloqueos:  __________  Cod. Recep: _20_________
 
 Marca Stock: _60_____________________________________ Núm. Serie:  _60_____________________________________
 ÏÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ Datos del Lote ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË  Codcomen:    @L@@@@@@@@     
 ³ Lote Proveedor: _40__________________________________________ ³
 ³ Caducidad:      ________    Retest:   ________                ³  Info Extra:  _255_______________________________________ 
 ³ Bloqueos Lote:  __________  Potencia: ######.###              ³
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ  Ult. Modif.: _32_____________ ¿D-MM-Y.YYY ________
|
TABLA=VDSTOCKFUENTE


CAMPO=SEQFUENTE,VIRTUAL,OCULTO
CAMPO=STATUS,TOOLTIP("Estado del registro"),POSTCHANGE=FDESIGNACION("+CSELDESSTATUS","ERROR AL EJECUTAR CURSOR CSELDESSTATUS")
CAMPO=DESSTATUS,AUXILIAR,NOENTER
CAMPO=CODUBI,TOOLTIP("Ubicación en la que se creará el stock"),POSTCHANGE=FDESIGNACION("+CSELAREA","ERROR AL EJECUTAR CURSOR CSELAREA")
CAMPO=CODAREA,AUXILIAR,NOENTER,TOOLTIP("Area de la Ubicación")
CAMPO=CODMAT,TOOLTIP("Si se informa, matrícula en la que se crea el stock")
CAMPO=TIPOCONTE,TOOLTIP("Tipo de contenedor a crear, si no se informa matrícula")
CAMPO=CODART,POSTCHANGE=FDESIGNACION("+CSELVDARTICDESART","ERROR AL EJECUTAR CURSOR CSELVDARTICDESART"),TOOLTIP("Artículo del que se crea stock")
CAMPO=DESART,AUXILIAR,NOENTER,TOOLTIP("Designacion")
CAMPO=CODLOT,TOOLTIP("Lote del que se crea stock")
CAMPO=CANTIDADHOST,TOOLTIP("Cantidad a crear en stock en unidades HOST")
CAMPO=UNIDADESHOST,TOOLTIP("Unidades HOST de la cantidad de stock a crear")
CAMPO=UNIEMBHOST,TOOLTIP("Unidades por Embalaje (HOST) del stock a crear")
CAMPO=EMBCONT,TOOLTIP("Embalajes por contenedor del stock a crear")
CAMPO=TIPOEMBA,TOOLTIP("Tipo de Embalaje del stock a crear")
CAMPO=PESOUNI,TOOLTIP("Peso Unitario del stock a crear")
CAMPO=PRECIOUNI,TOOLTIP("Precio Unitario del stock a crear")
CAMPO=BULTO,TOOLTIP("Código de bulto en el stock a crear")
CAMPO=BLOQUEOS,TOOLTIP("Bloqueos del stock a crear, si es  NULO, coge el del lote")
CAMPO=CODRECEP,TOOLTIP("Código de Recepción del stock a crear")
CAMPO=MARCASTK,TOOLTIP("Marca de stock en el stock a crear")
CAMPO=NUMEROSERIE,TOOLTIP("Número de serie en el stock a crear")
CAMPO=CODCOMEN,TOOLTIP("Código de comentario del registro")
CAMPO=CODLOTPROV,TOOLTIP("Lote del proveedor, por si se crea lote al crear el stock")
CAMPO=CADUCI,TOOLTIP("Fecha de caducidad del Lote, por si se crea lote al crear el stock")
CAMPO=RETEST,TOOLTIP("Fecha de Retest del Lote, por si se crea lote al crear el stock")
CAMPO=VDEXTRA,TOOLTIP("Datos adicionales externos a V10 y útiles para el cliente")
CAMPO=BLOQLOTE,TOOLTIP("Bloqueo del Lote, por si se crea lote al crear el stock")
CAMPO=POTENCIA,TOOLTIP("Potencia del Lote, por si se crea lote al crear el stock")
CAMPO=CODOPEMODIF,TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,TOOLTIP("Es la fecha  en que se efectuó alguna modificación a los datos del registro")
CAMPO=HORAMODIF,TOOLTIP("Es la hora  en que se efectuó alguna modificación a los datos del registro")

CURSOR=CSELDESSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='FTE';

CURSOR=CSELAREA SELECT CODAREA FROM VDUBICA WHERE CODUBI=:CODUBI;

CURSOR=CSELVDARTICDESART SELECT DESART FROM VDARTIC WHERE CODART=:CODART;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;
