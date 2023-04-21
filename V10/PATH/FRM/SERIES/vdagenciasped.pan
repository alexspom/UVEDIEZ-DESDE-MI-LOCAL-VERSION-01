###################################################################
#Módulo: VDAGENCIASPED.PAN
#Funcionalidad : Presenta las agencias que tienen los pedidos
#                incluidos en la serie
#Autor: FPD      
#Fecha: 18-04-2008
###################################################################
# Histórico de cambios:
AGENCIAS ASOCIADAS A LA SERIE
                                                             BULTOS  
Agencia                                    Pedidos   Palets  Cajas   Unidades  Restos  L?neas  Unidades
__________ ______________________________  @L@@@@@   @L@@@@  @L@@@@@ @L@@@@@   @L@@@@@ @L@@@@@ @@@@@@@
|
SOLOQUERY
SELECT=SELECT AGE.CODAGE,AGE.DESAGE,COUNT(*) NUMPED
       FROM VDPEDIDOCAB PEC, VDAGENCIA AGE
       WHERE PEC.CODSERIEPREP=:CODSERIEPREP AND
             PEC.CODAGE=AGE.CODAGE;
GROUPBY=AGE.CODAGE,AGE.DESAGE;

POSTQUERY=FDESIGNACION("@CSELVOL","","+CSELDATOS")
WFRAME(353,-2,188,0,"Bultos","")

CAMPO=CODSERIEPREP,VIRTUAL,OCULTO
CAMPO=CODAGE,TOOLTIP("C?igo de la agencia"),TITULO("Agencia")
CAMPO=DESAGE,TOOLTIP("Nombre completo de la agencia")
CAMPO=NUMPED,AUXILIAR,NOENTER,TOOLTIP("N?ero de pedidos de la serie que pertenecen a la agencia"),TITULO("Pedidos"),WLONX=20
CAMPO=PALETS,AUXILIAR,NOENTER,TOOLTIP("N?ero de palets aproximados de los pedidos que pertenecen a la agencia"),TITULO("Palets")
CAMPO=CAJAS,AUXILIAR,NOENTER,TOOLTIP("N?ero de cajas aproximadas de los pedidos que pertenecen a la agencia"),TITULO("Cajas")
CAMPO=BULTOSUNI,AUXILIAR,NOENTER,TOOLTIP("N?ero de bultos de unidades de los pedidos que pertenecen a la agencia"),TITULO("Unidades")
CAMPO=PICOS,AUXILIAR,NOENTER,TOOLTIP("N?ero de restos de los pedidos que pertenecen a la agencia"),TITULO("Restos")
CAMPO=LINEAS,AUXILIAR,NOENTER,TOOLTIP("N?ero de l?eas de los pedidos que pertenecen a la agencia"),TITULO("L?eas")
CAMPO=MAXVOLCAJA,AUXILIAR,OCULTO,"#L##############"
CAMPO=UNIDADES,AUXILIAR,NOENTER

CURSOR=CSELVOL SELECT MAX(LARGOCAJA*ANCHOCAJA*ALTOCAJA) MAXVOLCAJA 
                 FROM VDCAJAS
               GROUP BY TIPOVOL 
               HAVING MAX(LARGOCAJA*ANCHOCAJA*ALTOCAJA) IN (SELECT MAX(LARGOCAJA*ANCHOCAJA*ALTOCAJA) 
                                                              FROM VDCAJAS 
                                                             WHERE NVL(VOLDINAMICA,'N')='N' AND 
                                                                   TIPOVOL IN (SELECT DISTINCT TIPOVOL 
                                                                                 FROM VDARTIC ART,VDPEDIDOLIN PEL,VDPEDIDOCAB PEC  
									                                                              WHERE PEL.CODDIV=PEC.CODDIV AND PEL.ANOPED=PEC.ANOPED AND 
                                                                                      PEL.CODPED=PEC.CODPED AND PEL.SEQPED=PEC.SEQPED AND
                                                                                      PEC.CODAGE||''=:CODAGE AND PEC.CODSERIEPREP=:CODSERIEPREP AND
                                                                                      PEL.STATUS+0=VDST.FPELASERVIR AND 
                                                                                      PEL.CODART||''=ART.CODART));

CURSOR=CSELDATOS SELECT COUNT(*) LINEAS,
                        SUM(DECODE(ART.EMBCONT,0,0,FLOOR(FLOOR(VDART.CONVIERTE(CANTPEDIDA,ART.UNIDADES,ART.UNIDADESHOST)/DECODE(NVL(ART.UNIEMB,1),0,1,VDART.CONVIERTE(ART.UNIEMB,ART.UNIDADES,ART.UNIDADESHOST)))/ART.EMBCONT))) PALETS,
                        ABS(SUM(DECODE(ART.EMBCONT, 0,0,DECODE(NVL(ART.UNIEMB,1),0,1,VDART.CONVIERTE(ART.UNIEMB,ART.UNIDADES,ART.UNIDADESHOST))*FLOOR(FLOOR(VDART.CONVIERTE(CANTPEDIDA,ART.UNIDADES,ART.UNIDADESHOST)/DECODE(NVL(ART.UNIEMB,1),0,1,VDART.CONVIERTE(ART.UNIEMB,ART.UNIDADES,ART.UNIDADESHOST)))/ART.EMBCONT))) - 
                            SUM(FLOOR(VDART.CONVIERTE(CANTPEDIDA,ART.UNIDADES,ART.UNIDADESHOST)/DECODE(NVL(ART.UNIEMB,1),0,1,VDART.CONVIERTE(ART.UNIEMB,ART.UNIDADES,ART.UNIDADESHOST))))) CAJAS,
                        CEIL(SUM(MOD(VDART.CONVIERTE(CANTPEDIDA,ART.UNIDADES,ART.UNIDADESHOST),DECODE(NVL(ART.UNIEMB,1),0,1,VDART.CONVIERTE(ART.UNIEMB,ART.UNIDADES,ART.UNIDADESHOST))) * LARGOUNI*ANCHOUNI*ALTOUNI) / :MAXVOLCAJA) BULTOSUNI,
                        SUM(MOD(VDART.CONVIERTE(CANTPEDIDA,ART.UNIDADES,ART.UNIDADESHOST),DECODE(NVL(ART.UNIEMB,1),0,1,VDART.CONVIERTE(ART.UNIEMB,ART.UNIDADES,ART.UNIDADESHOST)))) PICOS
                        ,SUM(PEL.CANTASERVIR) UNIDADES
                   FROM VDPEDIDOLIN PEL,VDPEDIDOCAB PEC,VDARTIC ART
                  WHERE PEL.CODDIV=PEC.CODDIV AND PEL.ANOPED=PEC.ANOPED AND 
                        PEL.CODPED=PEC.CODPED AND PEL.SEQPED=PEC.SEQPED AND
                        PEC.CODAGE||''=:CODAGE AND PEC.CODSERIEPREP=:CODSERIEPREP AND
                        PEL.STATUS+0=VDST.FPELASERVIR AND 
                        PEL.CODART||''=ART.CODART;
