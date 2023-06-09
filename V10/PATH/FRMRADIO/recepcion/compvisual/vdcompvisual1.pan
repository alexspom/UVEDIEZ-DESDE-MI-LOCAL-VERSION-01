# M�dulo   : VDCOMVISUAL1.PAN
# Creaci�n : 17-09-2019
# Autor    : DFL
###########################################
# Hist�rico de cambios:
#   
SELECCION DE ORDEN
 _10_______ _10_______

  /* TIPO DE MERCANCIA */
 
 1. [_] PRODUCTO
 2. [_] PRODUCTO REFRIGERADO
 3. [_] MATERIAL PROMOCIONAL
 4. [_] MATERIAL DE
        ACONDICIONAMIENTO
 5. [_] OTROS
  
|

POSTQUERY=FEJECUTA(FIF("CSELNOTNULL",FPOSICIONABLOQUE("0"),FSUCCESS),"",
                   "CINSERTDATOS","ERROR AL INSERTAR DATOS",
				   FCOMMIT,"",
				   FPOSICIONABLOQUE("2"),"")
                   

CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=CODPROTO,OCULTO,VIRTUAL

CAMPO=SWT1,POSTCHANGE=FEJECUTA("+CCAMBIASWT1","")
CAMPO=SWT2,POSTCHANGE=FEJECUTA("+CCAMBIASWT2","")
CAMPO=SWT3,POSTCHANGE=FEJECUTA("+CCAMBIASWT3","")
CAMPO=SWT4,POSTCHANGE=FEJECUTA("+CCAMBIASWT4","")
CAMPO=SWT5,POSTCHANGE=FEJECUTA("+CCAMBIASWT5","")


CURSOR=CSELNOTNULL SELECT :SWT1 FROM DUAL WHERE :SWT1 IS  NULL AND :SWT2 IS NULL AND :SWT3 IS NULL AND :SWT4 IS NULL;
CURSOR=CCAMBIASWT1 SELECT 'X' SWT1 FROM DUAL WHERE :SWT1 IS NOT NULL;
CURSOR=CCAMBIASWT2 SELECT 'X' SWT2 FROM DUAL WHERE :SWT2 IS NOT NULL;
CURSOR=CCAMBIASWT3 SELECT 'X' SWT3 FROM DUAL WHERE :SWT3 IS NOT NULL;
CURSOR=CCAMBIASWT4 SELECT 'X' SWT4 FROM DUAL WHERE :SWT4 IS NOT NULL;
CURSOR=CCAMBIASWT5 SELECT 'X' SWT5 FROM DUAL WHERE :SWT5 IS NOT NULL;
CURSOR=CINSERTDATOS  DECLARE
                       VALORES VDRECEPCLI.NAMESARRAY;
                       MITIPO VARCHAR2(20) := 'TIPOMERCANCIA'; 
                     BEGIN
					    VALORES:= VDRECEPCLI.NAMESARRAY(:SWT1,'1 PRODUCTO', 
						                                :SWT2,'2 PRODUCTO REFRIGERADO',
														:SWT3,'3 MATERIAL PROMOCIONAL',
														:SWT4,'4 MATERIAL DE ACONDICIONAMIENTO',
														:SWT5,'5 OTROS');
                        VDRECEPCLI.COMPROBACIONVISUAL (:CODPROTO, MITIPO, VALORES);
                      END;@