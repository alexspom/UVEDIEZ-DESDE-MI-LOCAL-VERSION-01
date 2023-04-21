# M�dulo    : XVDNUMEROSERIEART.PAN
# Funci�n   : Mantenimiento de n�meros de serie le�dos
# Fecha     : 19-01-2023
# Autor     : LLMP
#
# 
###########################################
# Hist�rico de cambios:
MANTENIMIENTO DE NUMEROS DE SERIE LEIDOS
Divisi�n  C�d.Bulto    C�d.Art�culo C�d.Lote     Num.Serie    Fec.Creaci�n           �ltima modificaci�n 
_20___ _18____________ _40_________ _20______  _50_________ �D-MM-Y.YY ________   _32_____ �D-MM-Y.YY  ________   
	 							   
|

TABLA=XVDNUMEROSERIEARTFU 
ORDERBY=CODBULTO ASC, FECINSER DESC, HORINSER DESC;
WLONX=1000
REGPAG=30

PREINSERT=FEJECUTA("CSELMODIF","ERROR INSERTANDO ULTIMA MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR ACTUALIZANDO ULTIMA MODIFICACION")



PREINSERT=FEJECUTA( "CSELMODIF","ERROR INSERTANDO ULTIMA MODIFICACION",
                    "CCODDIVNULL","El C�digo de divisi�n no puede estar vac�o",
                    "CCODBULTONULL","El C�digo del bulto no puede estar vac�o",
                    "CCODARTNULL","El C�digo del art�culo no puede estar vac�o",
                    "CCODLOTNULL","El C�digo del lote no puede estar vac�o",
					"CCODMOVNULL","El C�digo del movimiento no puede estar vac�o",
					"CCODSERIEARTNULL","El C�digo del n�mero de serie no puede estar vac�o",
					"-CEXISTECODSERIE","Ya existe el n�mero de serie del art�culo"
)
PREUPDATE=FEJECUTA( "CSELMODIF","ERROR ACTUALIZANDO ULTIMA MODIFICACION",                    
					"CCODSERIEARTNULL","El C�digo del n�mero de serie no puede estar vac�o",
					"-CEXISTECODSERIE","Ya existe el n�mero de serie del art�culo"
)
               
CAMPO=CODDIV,NOUPDATE,TOOLTIP("C�digo divisi�n"),TITULO("Divisi�n")
CAMPO=CODBULTO,NOUPDATE,TOOLTIP("C�digo del bulto"),TITULO("C�d. Bulto")
CAMPO=CODART,NOUPDATE,TOOLTIP("C�digo del art�culo"),TITULO("C�d. Art�culo")
CAMPO=CODLOT,NOUPDATE,TOOLTIP("C�digo del lote"),TITULO("C�d. Lote")
CAMPO=CODSERIEART,AUTOENTER,TOOLTIP("N�mero de serie del art�culo"),TITULO("Num. Serie")
CAMPO=FECINSER,NOENTER,TOOLTIP("Fecha de creaci�n del registro"),TITULO("Fec. Creaci�n")
CAMPO=HORINSER,NOENTER,TOOLTIP("Hora de creaci�n del registro")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realiz� la �ltima modificaci�n"),TITULO("�ltima modificaci�n")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")



CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, 
                        VD.FECHASYS FECMODIF,
                        VD.HORASYS HORAMODIF,
                        VD.FECHASYS FECINSER,
                        VD.HORASYS HORINSER 						
                   FROM DUAL;

CURSOR=CCODDIVNULL SELECT :CODDIV FROM DUAL WHERE :CODDIV IS NOT NULL;
CURSOR=CCODBULTONULL SELECT :CODBULTO FROM DUAL WHERE :CODBULTO IS NOT NULL;
CURSOR=CCODARTNULL SELECT :CODART FROM DUAL WHERE :CODART IS NOT NULL;
CURSOR=CCODLOTNULL SELECT :CODLOT FROM DUAL WHERE :CODLOT IS NOT NULL;
CURSOR=CCODMOVNULL SELECT :CODMOV FROM DUAL WHERE :CODMOV IS NOT NULL;
CURSOR=CCODSERIEARTNULL SELECT :CODSERIEART FROM DUAL WHERE :CODSERIEART IS NOT NULL;
CURSOR=CEXISTECODSERIE SELECT CODSERIEART FROM XVDNUMEROSERIEART WHERE CODSERIEART = :CODSERIEART AND CODART = :CODART;


                   

ONLINE= {F1} Ayuda    {F2} Consulta     {F4} Grabar departamento   
        {Esc} Cerrar Pantalla  {F9} Borrar departamento  {M�y+F10} Men� Contextual ;