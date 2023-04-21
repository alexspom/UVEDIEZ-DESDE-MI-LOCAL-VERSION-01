# Módulo   : VDREQINFO.FRM
# Función  : PANTALLA PARA MANDAR CORREO A CLIENTE PIDIENDO INFORMACIÓN ADICIONAL REFERENTE A UNA INCIDENCIA
#
# Creación : 26-09-2009
# Autor    : JCSR
###########################################
# Histórico de cambios:
CAMPO = CODINCI, OCULTO , "@L@@@@@@@"
BEGINBLOQUE = VDREQINFO.PAN
	PREREGISTRO = PRESEHIJO
	BOTON = ENVIAR,600,15,70,70,"ENVIAR CORREO",Enveloppe.png,F4,"Enviar correo con la pregunta",INCLUDECSS="background-color: transparent;border-width:0px"
ENDBLOQUE
