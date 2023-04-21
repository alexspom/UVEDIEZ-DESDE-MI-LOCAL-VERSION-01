# Módulo   : VDCONCEPTOINTER.PAN
# Función  : Mantenimiento de conceptos de interfase
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
MANTENIMIENTO DE CONCEPTOS DE INTERFASE
Concepto         Designación                       Or. Positivo              A.or.  A.Dest Negativo                Variante A.Or.  A.Dest C Ultima modificación
_20_____________ _40______________________________ @L@ _10______ _10________ _10___ _10___ __________ _10_________ _10_____ _10___ _10___ _ _32________ ¿D-MM-Y.YY  ________
|
TABLA=VDCONCEPTOINTER

PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")



CAMPO=CONCEPTOINTER,NOUPDATE,TOOLTIP("Código interno del concepto"),TITULO("Concepto")
CAMPO=DESCONCEPTOINTER,TOOLTIP("Designación del concepto"),TITULO("Designación")
CAMPO=ORDENCONCEPTO,TOOLTIP("Orden del concepto para transmitir al host"),TITULO("Or.")
CAMPO=CONPOSITIVO,TOOLTIP("Concepto a transmitir si es positivo"),TITULO("Positivo")
CAMPO=CONPOSITIVO2,TOOLTIP("Concepto a transmitir si es positivo"),TITULO("Positivo")
CAMPO=ALMACENOP,TOOLTIP("Almacen origen si el concepto es positivo")
CAMPO=ALMACENDP,TOOLTIP("Almacen destino si el concepto es positivo")
CAMPO=CONNEGATIVO,TOOLTIP("Concepto a transmitir si es negativo"),TITULO("Negativo")
CAMPO=CONNEGATIVO2,TOOLTIP("Concepto a transmitir si es negativo"),TITULO("Negativo")
CAMPO=VARIANTESAP,TOOLTIP("Variante de sap"),TITULO("Variante")
CAMPO=ALMACENON,TOOLTIP("Almacen origen si el concepto es negativo")
CAMPO=ALMACENDN,TOOLTIP("Almacen destino si el concepto es negativo")
CAMPO=CIERRAIDOC,TOOLTIP("Indica si el concepto se ha de mandar en un IDOC independiente")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;




