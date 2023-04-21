###################################################################
#M�dulo: VDSBULSTKRES.PAN
#Funcionalidad : Selecci�n de stock para el cambio de reserva
#Autor: FGS
#Fecha: 10-03-2009
#MIRAR  COMPATIBILIDAD CON UBICACION DESTINO, EN ESTE CASO EXPEDICIONES
###################################################################
SELECCION DE STOCK PARA EL CAMBIO DE RESERVA
Area        Ubicaci�n    Matr�cula              Lote       Bloqueos   Uniemb     Stock   Reservado   Disp    Cantidad         Marcastk        Serie    
_20________ _20_________ __________________ @L@ _40_______ __________ @L@@@@   @L@@@@@@@ @L@@@@@@@ @L@@@@@@@ @L@@@@@@@ _10__ _60___________  _60___________
|


SOLOQUERY
SELECT = SELECT UBI.CODAREA,UBI.CODUBI,STK.CODMAT,STK.ORDENSTK,STK.CODLOT,STK.BLOQUEOS,STK.UNIEMB,STK.MARCASTK,STK.NUMEROSERIE,
                STK.CANTIDAD,VDSTK.STKRESERVADO(STK.CODMAT,STK.ORDENSTK) RESERVADO,STK.CANTIDAD-VDSTK.STKRESERVADO(STK.CODMAT,STK.ORDENSTK) DISPONIBLE,
                ART.UNIDADESHOST, 1 EJECMOV 
              FROM VDARTIC ART,VDUBICA UBI, VDCONTE CNT, VDSTOCK STK, VDDEMANDALIN DEML, VDPEDIDOCAB PEC, VDBULTOCAB BUC,VDLOTES LOT
              WHERE 
                  BUC.CODBULTO=:CODBULTO AND
                  PEC.CODDIV = BUC.CODDIV AND
                  PEC.ANOPED = BUC.ANOPED AND
                  PEC.CODPED = BUC.CODPED AND
                  PEC.SEQPED = BUC.SEQPED AND
                  DEML.CODDEMANDA = PEC.CODDEMANDA AND
                  DEML.TIPODEMANDA = PEC.TIPODEMANDA AND
                  DEML.CODART = :CODART AND
                  STK.CODART = :CODART AND 
                  STK.CODLOT = NVL(DEML.CODLOT,STK.CODLOT) AND
                  NVL(STK.MARCASTK,'-') = NVL(DEML.MARCASTK,'-') AND
                  NVL(STK.NUMEROSERIE,'-') = NVL(DEML.NUMEROSERIE,'-') AND
                  STK.CODRECEP = NVL(DEML.CODRECEP,STK.CODRECEP) AND
                  VDSTK.ESTADOCOMPATIBLE(STK.BLOQUEOS,NVL(DEML.BLOQUEOS,'__________'))=0 AND
                  CNT.CODMAT = STK.CODMAT AND
                  UBI.CODUBI = CNT.CODUBI AND
                  ART.CODART = :CODART AND
                  LOT.CODART = :CODART AND
                  LOT.CODLOT = STK.CODLOT AND                  
                  CODAREA NOT IN ('EXPEDICION','EXPEDPROMO'); 
ORDERBY= LOT.CADUCI,DECODE(UBI.CODAREA,'RESTOS',-1,'PI',0,'RP',1,'PP',2,'HR',3,4),UBI.CODUBI,STK.CODMAT,STK.ORDENSTK;                 


CAMPO=CODBULTO,VIRTUAL,AUXILIAR,OCULTO
CAMPO=SEQLINEA,VIRTUAL,AUXILIAR,OCULTO
CAMPO=CODART,VIRTUAL,AUXILIAR,OCULTO
CAMPO=STATUS,VIRTUAL,AUXILIAR,OCULTO
CAMPO=CANTPEDIDA,VIRTUAL,AUXILIAR,OCULTO
CAMPO=CODAREA,NOUPDATE,TITULO("Area")
CAMPO=CODUBI,NOUPDATE,TITULO("Ubicaci�n")
CAMPO=CODMAT,NOUPDATE,TITULO("Matr�cula")
CAMPO=ORDENSTK,NOUPDATE
CAMPO=CODLOT,NOUPDATE,TITULO("Lote")
CAMPO=BLOQUEOS,NOUPDATE,TITULO("Bloqueos")
CAMPO=UNIEMB,NOUPDATE,TITULO("UniEmb"),WLONX=-10
CAMPO=CANTIDAD,NOUPDATE,TITULO("Stock")
CAMPO=RESERVADO,NOUPDATE,TITULO("Reservado"),WLONX=10
CAMPO=DISPONIBLE,NOUPDATE,TITULO("Disponible"),WLONX=10
CAMPO=CANTIDADRES,AUXILIAR,TITULO("Cantidad")
CAMPO=UNIDADESHOST,NOUPDATE
CAMPO=MARCASTK,NOUPDATE,TITULO("Marca Stock")
CAMPO=NUMEROSERIE,NOUPDATE,TITULO("N� Serie")
CAMPO=CODMOVOUT,AUXILIAR,OCULTO,"@L@@@@@@@@@@"
# Si es 1, se ejecuta autom�ticamente el movto al crearse, si es 0, no se ejecuta y se enrutar�
CAMPO=EJECMOV,OCULTO,"@L@"

CURSOR=CDESART SELECT DESART FROM VDARTIC WHERE CODART=:CODART;
CURSOR=CSELSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='BUL';

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CDISPONIBLE SELECT :CANTIDADRES FROM DUAL WHERE :CANTIDADRES <= :DISPONIBLE;
                                                        
CURSOR=CPENDIENTE SELECT :CANTIDADRES FROM DUAL WHERE :CANTIDADRES <= :CANTPEDIDA;

CURSOR=CCHECKCERO SELECT :CANTIDADRES FROM DUAL WHERE :CANTIDADRES=0;

CURSOR=CMOVEJECUTADO SELECT :EJECMOV FROM DUAL WHERE :EJECMOV = 1;

PRECOMMIT=FEJECUTA("-CCHECKCERO","CANTIDAD A ROMPER NO PUEDE SER 0",
                   "CPENDIENTE","NO PUEDE CAMBIAR DE RESERVA MAS CANTIDAD DE LA PENDIENTE",
                   "CDISPONIBLE","CANTIDAD A CAMBIAR DE RESERVA SUPERA LA DISPONIBLE EN EL STOCK",
                   FCAMBIORESERVA(":CODBULTO",":SEQLINEA",":CANTIDADRES",":CODMAT",":ORDENSTK","REG-","REGULARIZA",":EJECMOV","CODMOVOUT"),":V10ERROR",
                   FCOMMIT,"",
                   %FFAILURE, "REALIZADO EL CAMBIO DE RESERVA DEL BULTO :CODBULTO",
# ahora en caso de CMOVEJECUTADO a SUCCESS se deber�a imprimir una orden de movto para que vaya a recogerlo
# el movto que le paso es el nuevo movto creado 
                   FIF("CMOVEJECUTADO",FEJECUTA(FIMPRIME("INFORME","VDCAMRESERVA.RPT","FORMCODMOV=:CODMOVOUT",""),":V10ERROR",
                                                %FFAILURE,"RECOJA DEL STOCK LA CANTIDAD :CANTIDADRES DE LA UBICACION :CODUBI, MATRICULA :CODMAT")),"",
                   FPULSATECLAS("CF6","F3","F2"),"")
                                



  