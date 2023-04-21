###################################################################
#Módulo: VDASIGNAGE.PAN
#Funcionalidad : Mantenimiento de asignacion de agencias
#Autor: FPD      
#Fecha: 08-04-2008
###################################################################
# Histórico de cambios:
MANTENIMIENTO DE ASIGNACION DE AGENCIAS
 
  Id: @L@@@@@@@    Agencia  _10_______ _30____________________________
  
  Entorno _30________________________________ Prioridad de asignación @L@         
 
  Información: _255______________________________________________________
 
 ÏÄÄ Artículo ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË
 ³                                                                                                         ³ 
 ³  Código de artículo    _1024_______________________________ _255_____________________________________   ³ 
 ³                                                                                                         ³ 
 ³  Clase                 _1024_______________________________ _255_____________________________________   ³ 
 ³                                                                                                         ³ 
 ³  División del artículo _1024_______________________________ _255_____________________________________   ³ 
 ³                                                                                                         ³ 
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
 
 ÏÄÄ Pedido ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË    
 ³                                                                                                         ³ 
 ³  Cliente         _1024_______________________________________________________________________________   ³
 ³                                                                                                         ³
 ³  Tipo de pedido  _1024_______________________________________________________________________________   ³
 ³                                                                                                         ³
 ³  Div. del pedido _1024__________________________________ _255________________________________________   ³
 ³                                                                                                         ³
 ³  Rango DP        _1024_______________________________________________________________________________   ³
 ³                                                                                                         ³
 ³  Zona geografica _255___________________________________ _255________________________________________   ³
 ³                                                                                                         ³
 ³  Países          _1024__________________________________ _255________________________________________   ³
 ³                                                                                                         ³
 ³  Rango Bultos    ____________________________________________________________________________________   ³
 ³                                                                                                         ³
 ³  Rango Peso      _1024_____________________________________________________________________________ Gr. ³
 ³                                                                                                         ³
 ³  Rango Volumen   _1024__________________________________________________________________________ Litros ³
 ³                                                                                                         ³
 ³  Rango Agencia:  _1024__________________________________ _255________________________________________   ³
 ³                                                                                                         ³
 ³  Urgencia @L          Prioridad @L                                                                      ³
 ³                                                                                                         ³
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ   

   Ultima modificación _32_______ ¿D-MM-YY.Y ________  
| 


PROTECT("SUPERVISOR")

TABLA=VDASIGNAGE
ORDERBY=CODAGE;


PREINSERT=FEJECUTA("CMODIF","No puedo asignar fecha de modificación.","CNEXTAGASI","No puedo calcular siguiente secuencial")
PREUPDATE=FEJECUTA("CMODIF","No puedo asignar fecha de modificación.")

CAMPO=SECASIGNAGE,NOENTER,TOOLTIP("Código que identifica la regla de asignación de agencia")
CAMPO=CODAGE,UPPER,POSTCHANGE=FDESIGNACION("CSELDESAGE","No existe agencia"),TOOLTIP("Código de agencia")
CAMPO=DESAGE,AUXILIAR,NOENTER,TOOLTIP("Descripción completa de la agencia")
CAMPO=ENTORNO,TOOLTIP("Entorno de asignacion REAL es el productivo")
CAMPO=PRIORIDADREGLA,TOOLTIP("Es la prioridad para asignar la prioridad,siendo 1 la mas alta y 999 O 0 la mas baja")
CAMPO=VDEXTRA,TOOLTIP("Información extra útil para el cliente")
CAMPO=RANGOCODART,POSTCHANGE=FDESIGNACION("CSELDESART","No existe artículo"),TOOLTIP("Código de artículo (Admite seleccion multiple separada por ,)")
CAMPO=DESART,AUXILIAR,NOENTER,TOOLTIP("Descripción completa del artículo")
CAMPO=RANGOCODCLASE,POSTCHANGE=FDESIGNACION("CSELCLASE","No existe clase de articulos"),TOOLTIP("Código de clase de artículo (Admite seleccion multiple separada por ,)")
CAMPO=DESCLASE,AUXILIAR,NOENTER,TOOLTIP("Descripción de la clase de articulo")
CAMPO=RANGOCODDIVART,POSTCHANGE=FDESIGNACION("CSELDESDIVART","No existe division del artículo"),TOOLTIP("Código de división del artículo (Admite seleccion multiple separada por ,)")
CAMPO=DESDIVART,AUXILIAR,NOENTER,TOOLTIP("Descripción completa de la división del artículo")
CAMPO=RANGOCLIENTE,TOOLTIP("Código de cliente (Admite seleccion multiple separada por ,)")
CAMPO=RANGOTIPOPEDIDO,TOOLTIP("Rango de tipos de pedido (Admite seleccion multiple separada por ,)")
CAMPO=RANGOCODDIVPED,POSTCHANGE=FDESIGNACION("CSELDESDIVCP","No existe division del pedido"),TOOLTIP("Código de división del pedido (Admite seleccion multiple separada por ,)")
CAMPO=DESDIVCP,AUXILIAR,NOENTER,TOOLTIP("Descripción completa de la división del pedido")
CAMPO=RANGODP,TOOLTIP("Rango de distritos postales (Admite seleccion multiple separada por ,)")
CAMPO=RANGOZONAGEO,POSTCHANGE=FDESIGNACION("CSELZONAGEO","No existe zona geografica"),TOOLTIP("Rango de zonas geográficas (Admite seleccion multiple separada por ,)")
CAMPO=DESZONAGEO,AUXILIAR,NOENTER
CAMPO=RANGOCODPAIS,POSTCHANGE=FDESIGNACION("CSELPAISES","No existe el Código del país"),TOOLTIP("Rango de Códigos de países (Admite seleccion multiple separada por ,)")
CAMPO=DESPAIS,AUXILIAR,NOENTER
CAMPO=RANGOBULTOS,POSTCHANGE=FDESIGNACION("CVERBULTOSNUM","Los rangos de bultos han de ser numericos\n:MSGERROR"),TOOLTIP("Rango de número de bultos (Admite seleccion multiple separada por ,)")
CAMPO=RANGOPESO,POSTCHANGE=FDESIGNACION("CVERPESONUM","Los rangos de pesos han de ser numericos\n:MSGERROR"),TOOLTIP("Rango de pesos en gramos (Admite seleccion multiple separada por ,)")
CAMPO=RANGOVOLUMEN,POSTCHANGE=FDESIGNACION("CVERVOLUMENNUM","Los rangos de volumen han de ser numericos\n:MSGERROR"),TOOLTIP("Rango de volumen en litros (Admite seleccion multiple separada por ,)")
CAMPO=RANGOCODAGE,POSTCHANGE=FDESIGNACION("CSELAGEN","No existe Código de Agencia Original (Admite seleccion multiple separada por ,)"),TOOLTIP("Rango de Códigos de Agencia Original (Admite seleccion multimple separada por ,)")
CAMPO=DESAGEOR, AUXILIAR,NOENTER,TOOLTIP("Descripcion del Código de Agencia")
CAMPO=URGENCIA,TOOLTIP("Urgencia del pedido (0-99)")
CAMPO=PRIORIDAD,TOOLTIP("Prioridad del pedido (0-99)")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Código de Operario que realizó la última modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en la que se realizó la Ultima modificación")
CAMPO=HORAMODIF,UPPER,NOENTER,TOOLTIP("Hora en la que se realizó la Ultima modificación")
CAMPO=MSGERROR,AUXILIAR,OCULTO,"_1024"

CURSOR=CNEXTAGASI SELECT VDSECASIGNAGE.NEXTVAL SECASIGNAGE FROM DUAL;

CURSOR=CMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF
                FROM DUAL;

CURSOR=CVERPESONUM SELECT VDAGE.VALIDORANGONUM(:RANGOPESO) MSGERROR FROM DUAL WHERE VDAGE.VALIDORANGONUM(:RANGOPESO) IS NULL;

CURSOR=CVERVOLUMENNUM SELECT VDAGE.VALIDORANGONUM(:RANGOVOLUMEN) MSGERROR FROM DUAL WHERE VDAGE.VALIDORANGONUM(:RANGOVOLUMEN) IS NULL;

CURSOR=CVERBULTOSNUM SELECT VDAGE.VALIDORANGONUM(:RANGOBULTOS) MSGERROR FROM DUAL WHERE VDAGE.VALIDORANGONUM(:RANGOBULTOS) IS NULL;

CURSOR=CSELDESAGE SELECT DESAGE FROM VDAGENCIA WHERE CODAGE=:CODAGE;

CURSOR=CSELZONAGEO SELECT DESZONAGEO FROM VDZONAGEOCAB WHERE CODZONAGEO=:RANGOZONAGEO
                    UNION
                   SELECT '' DESZONAGEO FROM DUAL WHERE :RANGOZONAGEO IS NULL
                    UNION
                   SELECT NVL(VDAGE.VALIDORANGO('VDZONAGEOCAB','CODZONAGEO',:RANGOZONAGEO),'SELECCION MULTIPLE') FROM DUAL WHERE (INSTR(:RANGOZONAGEO,',')>0 OR INSTR(:RANGOZONAGEO,'-')>0);

CURSOR=CSELPAISES SELECT DESPAIS FROM VDPAIS WHERE CODPAIS=:RANGOCODPAIS
                    UNION
                   SELECT '' DESPAIS FROM DUAL WHERE :RANGOCODPAIS IS NULL
                    UNION
                   SELECT NVL(VDAGE.VALIDORANGO('VDPAIS','CODPAIS',:RANGOCODPAIS),'SELECCION MULTIPLE') FROM DUAL WHERE (INSTR(:RANGOCODPAIS,',')>0 OR INSTR(:RANGOCODPAIS,'-')>0);


CURSOR=CSELCLASE SELECT DESCLASE FROM VDCLASES WHERE CODCLASIF=NVL(VD.GETPROP('CLASIFASIGNAGE'),'ASIGNAGE') AND CODCLASE=:RANGOCODCLASE
                  UNION
                 SELECT '' DESCLASE FROM DUAL WHERE :RANGOCODCLASE IS NULL
                  UNION
                 SELECT NVL(VDAGE.VALIDORANGO('VDCLASES','CODCLASE',:RANGOCODCLASE),'SELECCION MULTIPLE') FROM DUAL WHERE (INSTR(:RANGOCODCLASE,',')>0 OR INSTR(:RANGOCODCLASE,'-')>0);

CURSOR=CSELDESART SELECT DESART FROM VDARTIC WHERE CODART=:RANGOCODART
                   UNION
                  SELECT '' DESART FROM DUAL WHERE :RANGOCODART IS NULL
                   UNION
                  SELECT NVL(VDAGE.VALIDORANGO('VDARTIC','CODART',:RANGOCODART),'SELECCION MULTIPLE') FROM DUAL WHERE (INSTR(:RANGOCODART,',')>0 OR INSTR(:RANGOCODART,'-')>0);

CURSOR=CSELDESDIVART SELECT DESDIV DESDIVART FROM VDDIVIS WHERE CODDIV=:RANGOCODDIVART
                      UNION
                     SELECT '' DESDIVART FROM DUAL WHERE :RANGOCODDIVART IS NULL
                      UNION
                     SELECT NVL(VDAGE.VALIDORANGO('VDDIVIS','CODDIV',:RANGOCODDIVART),'SELECCION MULTIPLE') FROM DUAL WHERE (INSTR(:RANGOCODDIVART,',')>0 OR INSTR(:RANGOCODDIVART,'-')>0);

CURSOR=CSELDESDIVCP SELECT CODDIV DESDIVCP FROM VDDIVIS WHERE CODDIV=:RANGOCODDIVPED
                     UNION
                    SELECT '' DESDIVCP FROM DUAL WHERE :RANGOCODDIVPED IS NULL
                     UNION
                    SELECT NVL(VDAGE.VALIDORANGO('VDDIVIS','CODDIV',:RANGOCODDIVPED),'SELECCION MULTIPLE') FROM DUAL WHERE (INSTR(:RANGOCODDIVPED,',')>0 OR INSTR(:RANGOCODDIVPED,'-')>0);

CURSOR=CSELAGEN SELECT DESAGE DESAGEOR FROM VDAGENCIA WHERE CODAGE=:RANGOCODAGE
                   UNION
                  SELECT '' DESAGEOR FROM DUAL WHERE :RANGOCODAGE IS NULL
                   UNION
                  SELECT NVL(VDAGE.VALIDORANGO('VDAGENCIA','CODAGE',:RANGOCODAGE),'SELECCION MULTIPLE') FROM DUAL WHERE (INSTR(:RANGOCODAGE,',')>0 OR INSTR(:RANGOCODAGE,'-')>0);

