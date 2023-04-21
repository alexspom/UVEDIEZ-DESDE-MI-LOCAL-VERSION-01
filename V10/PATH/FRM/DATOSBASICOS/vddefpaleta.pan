# Módulo   : VDDEFTEMACOLOR.PAN
# Función  : Mantenimiento de definciones de colores por tema
#
# Creación : 05-11-2008
# Autor    : JMM
###########################################
# Histórico de cambios:
PALETAS DEFINIDAS EN EL TEMA
  Nombre:
  _40____________  _60________________________________________________________________
|

TABLA=VDDEFCOLOR


POSTQUERY=FEJECUTA("+CDESPALETA","")
ORDERBY=DECODE(NOMBRECOLOR,'DEFECTO',0,'MONOREG',1,'MENUS',2,'MENSAJES',3,'ERROR',4,'ONLINE',5,'TOOLTIP',6,7);

PREINSERT=FEJECUTA("CSELMODIF","ERROR INSERTANDO ULTIMA MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR ACTUALIZANDO ULTIMA MODIFICACION")

CAMPO=TEMA,VIRTUAL,OCULTO
CAMPO=NOMBRECOLOR,TOOLTIP("Nombre del conjunto de colores"),TITULO("Nombre")
CAMPO=DESPALETA,AUXILIAR,NOENTER,TITULO("Descripción")
CURSOR=CDESPALETA SELECT DECODE(:NOMBRECOLOR,'DEFECTO','BLOQUES MULTIREGISTRO', 
                                             'ERROR','MENSAJES DE ERROR',
                                             'MENSAJES','MENSAJES DEL FORM',
                                             'MENUS','MENUS DEL FORM',
                                             'ONLINE','AYUDA ONLINE',
                                             'TOOLTIP','TOOLTIP DE CAMPOS',
                                             'MONOREG','BLOQUES DE UN SOLO REGISTRO',
                                             'DEMO','PALETA PARA DEMOS DE TINTA Y PAPEL EN LA PANTALLA',
                                             'ORADEBUG','CONFIGURACION ESPECIFICA DE DEBUG ORACLE',
                                             '---') DESPALETA FROM DUAL;
                                        


