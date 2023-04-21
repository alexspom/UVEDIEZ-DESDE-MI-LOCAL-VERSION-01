MANTENIMIENTO DE TRADUCCIONES
Texto                                          Tipo  M Trad                             Entorno                               MODULO
_1000_________________________________________ _20__ _ _1000___________________________ _1000_________________________________ _200___________________________________________ _40______
|

TABLA=VDTRADUCE

REGPAG=40

CAMPO=TEXTOORIG,MIXED,TITULO("Original")
CAMPO=TIPO,TITULO("Tipo")
CAMPO=MARCATEXTO,TITULO("M")
CAMPO=TRADUCCION,MIXED,TITULO("Traducción")
CAMPO=ENTORNOTRAD,MIXED,TITULO("Entorno traduccion")
CAMPO=MODULO,MIXED,TITULO("Modulo")
CAMPO=IDIOMA
CAMPO=CODOPEMODIF,OCULTO,"_32"
CAMPO=FECMODIF,OCULTO,"¿D-MM-Y.YY"
CAMPO=HORAMODIF,OCULTO,"_8"

CURSOR=CCOPIATRAD SELECT :TEXTOORIG TRADUCCION FROM DUAL;

TECLA=F8,FDESIGNACION("CCOPIATRAD","")