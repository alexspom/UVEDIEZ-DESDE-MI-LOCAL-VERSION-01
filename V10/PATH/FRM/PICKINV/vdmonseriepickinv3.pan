###################################################################
#Módulo: VMONSERIEPICKINV3.PAN
#Funcionalidad : Monitor de series de picking inverso, zonas
#Autor: FGS   
#Fecha: 24-09-2008
###################################################################
MONITOR DE ZONAS DE LAS SERIE(S) DE PICKING INVERSO
                  ÏÄ Totales ÄË   ÏÄÄÄÄÄÄ Pendiente ÄÄÄÄÄÄÄË   Visitas
  Zona   Peso     Unid.  Lineas   Bul.Exp.  Lineas  Cantidad  Pendientes 
  @L@  ########   @L@@@@ @L@@@@    @L@@@@   @L@@@@   @L@@@@    @L@@@@
|

SOLOQUERY
SELECT=SELECT CODZONA,TOTALUNIDADES,TOTALLINEAS,VDEQUILIBRA.PONDERAZONA(CODZONA,VD.GETPROP('FACTORUNI'),VD.GETPROP('FACTORLIN'),VD.GETPROP('FACTORBUL')) PESOZONA
        FROM VDZONAS,
         (SELECT SUM(BUL.CANTPEDIDA) TOTALUNIDADES,SUM(1) TOTALLINEAS
          FROM VDPEDIDOCAB PEC, VDBULTOCAB BUC, VDBULTOLIN BUL, VDARTIC ART, VDSERIEPREP SPR 
           WHERE
              PEC.CODSERIEPREP = SPR.CODSERIEPREP AND                            
              BUC.CODPED=PEC.CODPED AND
              BUC.CODDIV=PEC.CODDIV AND
              BUC.ANOPED=PEC.ANOPED AND
              BUC.SEQPED=PEC.SEQPED AND
              BUL.CODBULTO=BUC.CODBULTO AND
              BUL.CODART=ART.CODART AND
              ART.PICKINV IN ('S','P') AND     
              VD.CONTIENECAD(:RANSERIE,SPR.CODSERIEPREP) = 1 AND                  
              SPR.SWTPICKINGINV='S' AND
              BUC.TIPOBULTO='U' AND
              BUL.STATUS = VDST.FBULASERVIR)   TOTALES    
        WHERE TIPOZONA='I' ORDER BY CODZONA; 

POSTQUERY=FEJECUTA("+CSELPDTES","",
                   "+CVISITASPDTES","")
#WFRAME(116,-2,108,0,"Totales","")
#WFRAME(221,-2,193,0,"Pendiente","")
#WFRAME(446,-2,60,0,"Visitas","")
                   
NOUPDATE                   

CAMPO=CODZONA,TITULO("Zona"),WLONX=18
CAMPO=PESOZONA,TITULO("Peso")
CAMPO=TOTALUNIDADES,TITULO("Unid.")
CAMPO=TOTALLINEAS,TITULO("Lineas"),WLONX=20
CAMPO=BULTOSPDTES,AUXILIAR,TOOLTIP("Número de bulto de expediciones por acabar en la zona"),TITULO("Bul.Exp."),WLONX=25
CAMPO=LINEASPDTES,AUXILIAR,TOOLTIP("Número de Líneas de bultos de expedidiciones por picar en la zona"),TITULO("Lineas"),WLONX=20
CAMPO=CANTIDADPDTE,AUXILIAR,TOOLTIP("Cantidad en unidades pendiente de picar en la zona"),TITULO("Cantidad"),WLONX=20
CAMPO=VISITASPDTES,AUXILIAR,NOENTER,TOOLTIP("Número de bultos de picking inverso que faltan por visitar la zona"),TITULO("Visitas Pdtes"),WLONX=60
CAMPO=RANSERIE,AUXILIAR,VIRTUAL,OCULTO


CURSOR=CSELPDTES SELECT COUNT(DISTINCT BUC.CODBULTO) BULTOSPDTES,
                        SUM(1) LINEASPDTES,
                        SUM(CANTPEDIDA) CANTIDADPDTE
                   FROM  VDBULTOLIN BUL,  VDINFODISP DSP, VDBULTOCAB BUC, VDPEDIDOCAB PEC  
                   WHERE BUC.CODBULTO    =   BUL.CODBULTO AND 
                         BUC.IDINFOPICK  =   DSP.IDINFOPICK AND
                         BUC.NUMDISP     =   DSP.NUMDISP AND
                         BUC.TIPOBULTO   =   'U' AND     
                         BUC.STATUS      <   VDST.FBUCPREPARADO AND
                         DSP.CODZONA  = :CODZONA AND
                         BUL.STATUS+0 =    VDST.FBULASERVIR AND
                         PEC.CODDIV =  BUC.CODDIV AND
                         PEC.ANOPED =  BUC.ANOPED AND
                         PEC.CODPED =  BUC.CODPED AND
                         PEC.SEQPED =  BUC.SEQPED AND
                         VD.CONTIENECAD(:RANSERIE,PEC.CODSERIEPREP)=1;    

CURSOR=CVISITASPDTES SELECT COUNT (DISTINCT BPC.CODBULTO)  VISITASPDTES
                       FROM VDBULTOCABPINV BPC, VDMOVIM MOV, VDBULTOCAB BUC, VDBULTOLIN BUL, VDINFODISP IDI 
                       WHERE 
                            BPC.STATUS < 3000 AND
                            MOV.CODMATORI = BPC.CODMAT AND
                            BUL.CODMOV = MOV.CODMOV AND
                            BUC.CODBULTO = BUL.CODBULTO AND
                            IDI.IDINFOPICK = BUC.IDINFOPICK AND
                            IDI.NUMDISP = BUC.NUMDISP AND
                            MOV.STATUS < VDST.FMOVACTUALIZA AND
                            IDI.CODZONA =:CODZONA;


