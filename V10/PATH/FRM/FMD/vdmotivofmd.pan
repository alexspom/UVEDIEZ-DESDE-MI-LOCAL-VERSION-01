# M�dulo   : VDMOTIVOFMD.PAN
# Funci�n  : 
#
# Creaci�n : 17-07-2019
# Autor    : DFL
# Fichero generado por el Asistente de Generaci�n de Pantallas V10 
###########################################
# Hist�rico de cambios:
MOTIVOS DE FMD
MOTIVOFMD          DESCMOTIVOFMD         ACCIONDECOM ACCIONUNDODECOM CODOPEMODIF FECMODIF   HORAMODIF
_20______________  _40_________________  _40________ _40____________ _32________ �D-MM-Y.YY _10_______
|

TABLA=VDMOTIVOFMD
AQUERY
REGPAG=20
PREINSERT=FEJECUTA("CSELMODIF","ERROR EN CSELMODIF")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN CSELMODIF")

CAMPO=MOTIVOFMD,TITULO("Motivo")  
CAMPO=DESCMOTIVOFMD,TITULO("Descripci�n Motivo") 
CAMPO=ACCIONDECOM ,TITULO("Acci�n Decom.")
CAMPO=ACCIONUNDODECOM,TITULO("Acci�n UndoDedcom")
CAMPO=CODOPEMODIF,NOENTER ,TITULO("Mofificado por...")
CAMPO=FECMODIF,NOENTER 
CAMPO=HORAMODIF,NOENTER

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

# LISTA DE CAMPOS DE LA PANTALLA

# PARTE PERSONALIZADA DE LA PANTALLA 