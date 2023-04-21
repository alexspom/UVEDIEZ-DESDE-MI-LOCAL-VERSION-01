MANTENIMIENTO DE CAUSAS DE DEVOLUCION
  
 Ord Código     Designación                                 Abo. Int. Ap Ultima modificación
 @L@ __________ _40________________________________________  _    _   _  _32________ ¿D-MM-Y.YY  ________  
|

PROTECT("VSUPERVISOR")

TABLA=VDDEVOLCAUSA
WHERE = NVL(CODDIV,'-') = NVL(:CODDIVAUX,'-');

REGPAG=18
PREINSERT=FEJECUTA("+CDAMESEQ","","CSELMODIF","ERROR EN FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")

CAMPO=CODDIV, OCULTO, "_20__"
CAMPO=ORDEN,TITULO("Ord"),TOOLTIP("Orden en el que se muestra en la pantalla")
CAMPO=CODDIVAUX,AUXILIAR, VIRTUAL("CODDIV"),OCULTO
CAMPO=CODCAUSA,TITULO("Causa"),WLONX=40
CAMPO=DESCAUSA,TITULO("Designación")
CAMPO=ABONAR,POSTCHANGE=FVERIFICA("SND","Debe introducir S(i) N(o) D(efecto)"),TITULO("Abonar"),TOOLTIP("S: Mercancia se abona siempre\nN: Mercancia se devuelve al cliente\n D: depende del lote y su caducidad"),WLONX=40
CAMPO=INTERNO,COMBOX("CSELINTERNO"),POSTCHANGE=FVERIFICA("SN","Debe introducir S(i) N(o)"),TITULO("Interno"),TOOLTIP("Causa solo permitida para destrucciones de mercancia no asociadas a clientes"),WLONX=40
CAMPO=APTO,COMBOX("CAPTO"),POSTCHANGE=FVERIFICA("SNDR","Debe introducir S(i) N(o) o D"),TITULO("Apto"),TOOLTIP("Si ABONAR es S o D, determina si se acepta como apto (S) o no (N), o depende de la caducidad del lote(D)"),WLONX=40
CAMPO=CODCOMEN,OCULTO,"@L@@@@@@@"
CAMPO=CODOPEMODIF,NOENTER,TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER
CAMPO=HORAMODIF,NOENTER,WLONX=20

CURSOR=CSELINTERNO  SELECT 'S','Causa de destrucción no asociada a una devolución de cliente' FROM DUAL UNION
                    SELECT 'N','Causa de destrucción asociada a una devolución de cliente' FROM DUAL;                    

CURSOR=CAPTO  SELECT 'S','Se acepta siempre como apto' FROM DUAL UNION
              SELECT 'N','Nunca se acepta como apto' FROM DUAL UNION      
              SELECT 'D','Depende de la caducidad del lote' FROM DUAL UNION
			  SELECT 'R','Entra en estado Reacondiccionar' FROM DUAL;             

CURSOR=CDAMESEQ SELECT :CODDIVAUX CODDIV, VDSECCOMEN.NEXTVAL CODCOMEN FROM DUAL;      

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;