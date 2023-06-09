# M�dulo   : VDLOTES.PAN
# Funci�n  : Mantenimiento de lotes
#
# Creaci�n : 01-10-2007
# Autor    : EAA
###########################################
# Hist�rico de cambios:
MANTENIMIENTO DE LOTES
Art�culo            Designaci�n           Lote               Lote proveedor     Caduci   Retest   Bloqueos   Potencia      Muestreado Extra               Coment.   Ultima modificaci�n
_40________________ _100_________________ _40_______________ _40_______________ ________ ________ __________ #L#######.###  _         _255_______________ @L@@@@@@@ _32________ �D-MM-Y.YY  ________
|
TABLA=VDLOTES
REGPAG=30

PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION","+CSELBLOQUEO","",
                   "CCHECKFORMATOCADUCI","EL FORMATO DE LA FECHA DE CADUCIDAD\n DEBE SER DIA,MES,A�O (DDMMAAAA)",
                   "CSELRETEST","ERROR AL CALCULAR FECHA RETEST",
                   "+CSELPOTENCIA","")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION",
                   "CCHECKFORMATOCADUCI","EL FORMATO DE LA FECHA DE CADUCIDAD\n DEBE SER DIA,MES,A�O (DDMMAAAA)",
                   "CCHECKFORMATORETEST","EL FORMATO DE LA FECHA DE RETEST\n DEBE SER DIA,MES,A�O (DDMMAAAA)")




CAMPO=CODART,TOOLTIP("C�digo del art�culo"),NOUPDATE,POSTCHANGE=FDESIGNACION("CSELDESART","No existe art�culo"),TITULO("Art�culo")
CAMPO=DESART,AUXILIAR,NOENTER,TOOLTIP("Designaci�n del art�culo")
CAMPO=CODLOT,POSTCHANGE=FVALNOCERO("Debe informar un lote"),NOUPDATE,TOOLTIP("Lote"),TITULO("Lote")
CAMPO=CODLOTPROV,TOOLTIP("Lote del proveedor"),TITULO("Lote Proveedor")
CAMPO=CADUCI,TOOLTIP("Caducidad en formato DDMMAAAA"),TITULO("Caduci")
CAMPO=FORMATOOK,AUXILIAR,OCULTO,"_8_"
CAMPO=RETEST,TOOLTIP("Fecha de retest del lote en formato DDMMAAAA"),TITULO("Retest")
CAMPO=BLOQLOTE,NOENTER,TOOLTIP("Bloqueos del lote"),POSTCHANGE=FDESIGNACION("-CVERBLOQUEO",":V10ERROR"),TITULO("Bloqueos")
CAMPO=POTENCIA,TOOLTIP("Potencia del lote"),TITULO("Potencia")
CAMPO=MUESTREADO,TOOLTIP("Indica si se ha muestreado ese lote"),TITULO("Muestreado"),WLONX=10
CAMPO=VDEXTRA,TOOLTIP("Campo extra para el implantador"),TITULO("Extra")
CAMPO=CODCOMEN,NOENTER,TOOLTIP("C�digo de comentario del lote"),TITULO("Comen")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realiz� la �ltima modificaci�n"),TITULO("Ultima modificaci�n")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CSELDESART SELECT DESART FROM VDARTIC WHERE CODART=:CODART;

CURSOR=CVERBLOQUEO SELECT VDART.VALIDABLOQUEO(:BLOQLOTE) V10ERROR FROM DUAL WHERE VDART.VALIDABLOQUEO(:BLOQLOTE) IS NOT NULL AND :BLOQLOTE IS NOT NULL;

CURSOR=CSELBLOQUEO SELECT '0' || DECODE(ART.SWTANALISIS,'S','1','0') || '00000000' BLOQLOTE
                     FROM VDARTIC ART
                    WHERE ART.CODART = :CODART;

CURSOR=CCHECKFORMATOCADUCI SELECT TO_CHAR(TO_DATE(:CADUCI,'YYYYMMDD'),'YYYYMMDD') FORMATOOK FROM DUAL WHERE :CADUCI IS NOT NULL AND TO_NUMBER(SUBSTR(:CADUCI,1,4))> 2000;

CURSOR=CCHECKFORMATORETEST SELECT TO_CHAR(TO_DATE(:RETEST,'YYYYMMDD'),'YYYYMMDD') FORMATOOK FROM DUAL WHERE :RETEST IS NOT NULL AND TO_NUMBER(SUBSTR(:RETEST,1,4))> 2000;

CURSOR=CSELRETEST SELECT DECODE(UNIRETEST,'A',TO_CHAR(ADD_MONTHS(TO_DATE(:CADUCI,'YYYYMMDD'),-12*TRETEST),'YYYYMMDD'),
                                          'M',TO_CHAR(ADD_MONTHS(TO_DATE(:CADUCI,'YYYYMMDD'),-TRETEST),'YYYYMMDD'),
                                          'D',TO_CHAR(TO_DATE(:CADUCI,'YYYYMMDD')-TRETEST,'YYYYMMDD')) RETEST
                    FROM VDARTIC 
                   WHERE CODART = :CODART AND UNIRETEST IN ('A','M','D');

CURSOR=CSELPOTENCIA SELECT DECODE(:POTENCIA,0,1,:POTENCIA) POTENCIA FROM DUAL;




