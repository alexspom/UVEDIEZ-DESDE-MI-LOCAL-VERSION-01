#*****************************************************************
#Módulo: VDVISBULTCAB.PAN
#Funcionalidad : Visualizacion de Bultos en curso.
#Autor: VEGA Y JOTA      
#Fecha: 06-07-2022
#*****************************************************************
#* Histórico de cambios
#* ====================
CABECERA DE BULTO
 Fecha       Hora     Pedido   Bulto      Número  					
 ¿D-MM-Y.YY  ________ _20_____ _18_______  @5@@@   
 
 Tipo        Caja       Peso     Volumen   
 _10_______  _10_______ @15@@@@@ @15@@@@@  
 
 Status  Descripcion	
 @5@@@ _30______________  
|
TABLA=VDBULTOCAB
WHERE=NBULTO=9001;

CAMPO=FECMODIF,NOENTER,TOOLTIP("Es la fecha  en que se efectuÃ³ alguna modificación. Es utilizado para depuración y control de los registros en las tablas"),TITULO("Fecha")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Es la hora  en que se efectuÃ³ alguna modificación. Es utilizado para depuración y control de los registros en las tablas"),TITULO("Hora")
CAMPO=CODPED,NOENTER,TOOLTIP(""),TITULO("Cod. Pedido")
CAMPO=CODBULTO,NOENTER,TOOLTIP(""),TITULO("Cod. Bulto")
CAMPO=NBULTO,NOENTER,TOOLTIP(""),TITULO("Numero Bulto")
CAMPO=TIPOVOL,NOENTER,TOOLTIP(""),TITULO("Tipo Volumetria")
CAMPO=TIPOCAJA,NOENTER,TOOLTIP(""),TITULO("Tipo Caja")
CAMPO=PESOTEORICO,NOENTER,TOOLTIP(""),TITULO("Peso")
CAMPO=VOLUMEN,NOENTER,TOOLTIP(""),TITULO("Volumen")
CAMPO=STATUS,NOENTER,TOOLTIP(""),TITULO("Estado Bulto")
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Descripcion Estado"),POSTCHANGE=FDESIGNACION("CDESSTATUS","ERROR, NO EXISTE EL STATUS"),TITULO("Descripcion")


CURSOR=CDESSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE TIPOSTATUS='BUC' AND STATUS=:STATUS;