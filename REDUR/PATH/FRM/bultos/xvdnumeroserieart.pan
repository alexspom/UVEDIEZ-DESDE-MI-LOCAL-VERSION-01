# Módulo    : XVDNUMEROSERIEART.PAN
# Función   : Mantenimiento de nÚmeros de serie leídos
# Fecha     : 19-01-2023
# Autor     : LLMP
#
# 
###########################################
# Histórico de cambios:
MANTENIMIENTO DE NUMEROS DE SERIE LEIDOS
División  Cód.Bulto    Cód.Artículo Cód.Lote     Num.Serie    Fec.Creación           Última modificación 
_20___ _18____________ _40_________ _20______  _50_________ ¿D-MM-Y.YY ________   _32_____ ¿D-MM-Y.YY  ________   
	 							   
|

TABLA=XVDNUMEROSERIEARTFU 
ORDERBY=CODBULTO ASC, FECINSER DESC, HORINSER DESC;
WLONX=1000
REGPAG=30

PREINSERT=FEJECUTA("CSELMODIF","ERROR INSERTANDO ULTIMA MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR ACTUALIZANDO ULTIMA MODIFICACION")



PREINSERT=FEJECUTA( "CSELMODIF","ERROR INSERTANDO ULTIMA MODIFICACION",
                    "CCODDIVNULL","El Código de división no puede estar vacío",
                    "CCODBULTONULL","El Código del bulto no puede estar vacío",
                    "CCODARTNULL","El Código del artículo no puede estar vacío",
                    "CCODLOTNULL","El Código del lote no puede estar vacío",
					"CCODMOVNULL","El Código del movimiento no puede estar vacío",
					"CCODSERIEARTNULL","El Código del número de serie no puede estar vacío",
					"-CEXISTECODSERIE","Ya existe el número de serie del artículo"
)
PREUPDATE=FEJECUTA( "CSELMODIF","ERROR ACTUALIZANDO ULTIMA MODIFICACION",                    
					"CCODSERIEARTNULL","El Código del número de serie no puede estar vacío",
					"-CEXISTECODSERIE","Ya existe el número de serie del artículo"
)
               
CAMPO=CODDIV,NOUPDATE,TOOLTIP("Código división"),TITULO("División")
CAMPO=CODBULTO,NOUPDATE,TOOLTIP("Código del bulto"),TITULO("Cód. Bulto")
CAMPO=CODART,NOUPDATE,TOOLTIP("Código del artículo"),TITULO("Cód. Artículo")
CAMPO=CODLOT,NOUPDATE,TOOLTIP("Código del lote"),TITULO("Cód. Lote")
CAMPO=CODSERIEART,AUTOENTER,TOOLTIP("Número de serie del artículo"),TITULO("Num. Serie")
CAMPO=FECINSER,NOENTER,TOOLTIP("Fecha de creación del registro"),TITULO("Fec. Creación")
CAMPO=HORINSER,NOENTER,TOOLTIP("Hora de creación del registro")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Última modificación")
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
        {Esc} Cerrar Pantalla  {F9} Borrar departamento  {Máy+F10} Menú Contextual ;