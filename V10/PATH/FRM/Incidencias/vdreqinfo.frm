# M�dulo   : VDREQINFO.FRM
# Funci�n  : PANTALLA PARA MANDAR CORREO A CLIENTE PIDIENDO INFORMACI�N ADICIONAL REFERENTE A UNA INCIDENCIA
#
# Creaci�n : 26-09-2009
# Autor    : JCSR
###########################################
# Hist�rico de cambios:
CAMPO = CODINCI, OCULTO , "@L@@@@@@@"
BEGINBLOQUE = VDREQINFO.PAN
	PREREGISTRO = PRESEHIJO
	BOTON = ENVIAR,600,15,70,70,"ENVIAR CORREO",Enveloppe.png,F4,"Enviar correo con la pregunta",INCLUDECSS="background-color: transparent;border-width:0px"
ENDBLOQUE
