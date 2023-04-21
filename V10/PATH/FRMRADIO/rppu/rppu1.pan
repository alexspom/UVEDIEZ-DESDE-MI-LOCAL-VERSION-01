# M�dulo   : RPPU1.PAN
# Funci�n  : Pantalla de obtencion de movimientos.
#
# Creaci�n : 24-09-2014
# Autor    : FPD
###########################################
# Hist�rico de cambios:
#
PICKING TOUR (ORIGEN)
_10_______ _10_______

NO HAY MOVIMIENTOS
PENDIENTES


|

PREQUERY=FEJECUTA(
                  FIF("CSELMOVPDTE",
                      FEJECUTA(
					           FIF("CSELCODMAT",
					               FPOSICIONABLOQUE("RPPU2.PAN"),
								   FPOSICIONABLOQUE("RPPU5.PAN")
								  )," ERROR \n BUSCANDO MOVIMIENTOS"
							  ),
                      FEJECUTA(
					           FIF("CSELMOVCURSO",
                                   FEJECUTA(
								            FIF("CSELCODMAT",
                                                FIF("CSEL2ETAPAS",
												    FPOSICIONABLOQUE("RPPU10.PAN"),
                                                    FPOSICIONABLOQUE("RPPU8.PAN")
												   ),
                                                FPOSICIONABLOQUE("RPPU5.PAN"))," ERROR \n BUSCANDO MOVIMIENTOS"),
                                   FSUCCESS)," ERROR \n BUSCANDO MOVIMIENTOS"
						      )
			         )," ERROR \n BUSCANDO MOVIMIENTOS"
				 )											   

#PREQUERY=FEJECUTA(FIF("CSELMOVPDTE",
#                      FIF("CSELCODMAT",FPOSICIONABLOQUE("RPPU2.PAN"),FPOSICIONABLOQUE("RPPU5.PAN")),FSUCCESS)," ERROR \n BUSCANDO MOVIMIENTOS",
#                  FIF("CSELMOVCURSO",
#                      FIF("CSELCODMAT",
#                          FIF("CSEL2ETAPAS",FPOSICIONABLOQUE("RPPU10.PAN"),
#                                            FPOSICIONABLOQUE("RPPU8.PAN")),
#                          FPOSICIONABLOQUE("RPPU5.PAN")
#                         ),FSUCCESS)," ERROR \n BUSCANDO MOVIMIENTOS") 
						 
POSTQUERY=FEJECUTA(FCARGAFORM("")," ERROR\n AL VOLVER AL MENU") 


# DEFINICION DE CAMPOS
CAMPO=CODRECURSO,VIRTUAL,NOENTER
CAMPO=CODOPE,VIRTUAL,NOENTER
CAMPO=CODMAT,OCULTO,"_20_"

CAMPO=CODMOV,OCULTO,"@L@@@@@@@@"
CAMPO=CODAREA,OCULTO,"_20_"
CAMPO=CODPERFIL,OCULTO,"_20_"


CURSOR=CSELMOVPDTE SELECT  MOV.CODMOV,REC.CODPERFIL
                     FROM VDMOVIM MOV,VDUBICA UBI,VDRECURSO REC
                    WHERE MOV.CODRECURSO=:CODRECURSO
                      AND MOV.CODRECURSO=REC.CODRECURSO
                      AND MOV.STATUS IN (VDST.FMOVASIGNADO,VDST.FMOVPRESENTADO)
                      AND MOV.CODMATORI != MOV.CODMATDEST
                      AND MOV.CODUBIORI=UBI.CODUBI
                    ORDER BY MOV.PRIOMOV,UBI.ORDENMOVIM;
                    
CURSOR=CSELMOVCURSO SELECT  MOV.CODMOV,REC.CODPERFIL,UBID.CODAREA
                     FROM VDMOVIM MOV,VDUBICA UBI,VDRECURSO REC,VDUBICA UBID
                    WHERE MOV.CODRECURSO=:CODRECURSO
                      AND MOV.CODRECURSO=REC.CODRECURSO
                      AND MOV.STATUS IN (VDST.FMOVENUBIINTER)
                      AND MOV.CODMATORI != MOV.CODMATDEST
                      AND MOV.CODUBIORI=UBI.CODUBI AND MOV.CODUBIDEST=UBID.CODUBI
                    ORDER BY UBI.ORDENMOVIM;
                    
CURSOR=CSELCODMAT SELECT CNT.CODMAT 
                   FROM VDRECURSO REC,VDCONTE CNT WHERE CODRECURSO=:CODRECURSO AND CNT.CODMAT=REC.CODMAT;                    

CURSOR=CSEL2ETAPAS SELECT :CODAREA FROM DUAL WHERE :CODAREA IN ('INTERRP');
