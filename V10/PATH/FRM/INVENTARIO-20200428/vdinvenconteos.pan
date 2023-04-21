#*****************************************************************
#Módulo: VDINVENCONTEOS.PAN
#Funcionalidad : Muestra todos los conteos de los inventarios.
#Autor: ICC      
#Fecha: 03-02-2010
#*****************************************************************
#* Histórico de cambios
#* ====================
#
INVENTARIOS REALIZADOS
       Matricula: _18_______________ Estado ###### _40_____________________   Ultima modif.: _32_____ ¿D-MM-Y.YYY _8______ 
          Artículo                             Lote      Cantidad Rotas Operario Fecha inicio         Fecha fin           
 Teórico: _40_________ _100___________________ _40______ ######## 
 Real   : _40_________ _100___________________ _40______ ######## ##### _32_____ ¿D-MM-Y.YYY _8______ ¿D-MM-Y.YYY _8______

|

TABLA=VDINVENCONTEO
WHERE=NVL(:CODMATINVL, CODMAT)=CODMAT;
ORDERBY=CODMAT,FECINI DESC, HORAINI DESC;

NODELETE
NOINSERT

CAMPO=CODMAT,NOUPDATE
CAMPO=STATUS,NOENTER,POSTCHANGE=FDESIGNACION("+CSELDESSTATUS","No existe status")
CAMPO=DESSTATUS,AUXILIAR,NOENTER
CAMPO=CODOPEMODIF,TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,TOOLTIP("Fecha  en que se efectuó alguna modificación a los datos del registro")
CAMPO=HORAMODIF,TOOLTIP("Hora  en que se efectuó alguna modificación a los datos del registro")

CAMPO=CODINVEN,TOOLTIP("Código de inventario"),VIRTUAL, OCULTO
CAMPO=CODUBI,TOOLTIP("Código de ubicación a inventariar"),VIRTUAL, OCULTO
CAMPO=CODMATINVL,TOOLTIP("Código de matrícula a inventariar"),VIRTUAL,AUXILIAR, OCULTO
#CAMPO=SEQINVEN,OCULTO,"##"
CAMPO=CODARTTEORICO,NOENTER,TOOLTIP("Código de artículo antes de inventariar"), POSTCHANGE=FDESIGNACION("+CSELDESARTT","")
CAMPO=DESARTT,AUXILIAR,NOENTER
CAMPO=CODLOTTEORICO,NOENTER,TOOLTIP("Código de lote antes de inventaria")
CAMPO=CANTTEORICO,NOENTER,TOOLTIP("Cantidad antes de inventaria")
CAMPO=CODARTREAL,NOENTER,TOOLTIP("Código de artículo después de inventariar"),POSTCHANGE=FDESIGNACION("+CSELDESARTR","")
CAMPO=DESARTR,NOENTER,AUXILIAR,NOENTER
CAMPO=CODLOTREAL,NOENTER,TOOLTIP("Código de lote después de inventaria")
CAMPO=CANTREAL,NOENTER,TOOLTIP("Cantidad total después de inventariar, incluidas las rotas")
CAMPO=CANTROTAS,NOENTER,TOOLTIP("Cantidad de unidades rotas")
CAMPO=CODOPE,NOENTER,TOOLTIP("Código de operario que realiza el inventario")
CAMPO=FECINI,NOENTER,TOOLTIP("Fecha en juliano en que se inicia el inventario, es decir, cuando al operario comienza a inventariar la matrícula")
CAMPO=HORAINI,NOENTER,TOOLTIP("Hora en que se inicia el inventario, es decir, cuando al operario comienza a inventariar la matrícula")
CAMPO=FECFIN,NOENTER,TOOLTIP("Fecha en juliano en que se se finaliza el recuento de la matrícula")
CAMPO=HORAFIN,NOENTER,TOOLTIP("Hora en que se se finaliza el recuento de la matrícula")

CURSOR=CSELDESARTT SELECT DESART DESARTT
                     FROM VDARTIC
                    WHERE CODART = :CODARTTEORICO;

CURSOR=CSELDESARTR SELECT DESART DESARTR
                     FROM VDARTIC
                    WHERE CODART = :CODARTREAL;

CURSOR=CSELDESSTATUS SELECT DESSTATUS 
                       FROM VDSTATUS
                      WHERE TIPOSTATUS = 'INO'
                        AND STATUS = :STATUS;


ONLINE= {F1} Ayuda    {F2} Consulta    {F4} Confirmar cambios    {Esc} Cerrar Pantalla    
        {May-F7} Documentación {May+F8} Imprimir  {F9} Borrar un registro    {F5} Borrar Pantalla    ;


