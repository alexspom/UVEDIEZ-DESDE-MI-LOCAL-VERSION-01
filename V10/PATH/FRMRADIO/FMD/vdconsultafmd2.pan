#  Función : Menú para consultar números de serie                            #
#  Autor : MJGG                                                              #
#  Fecha : 21-11-2018                                                        #
#  Revisador por  :                                                          #
#  Fecha revisión :                                                          #
##############################################################################
#  Histórico de cambios
#  --------------------
#  Se adapta para los terminales de radio 06022019 - EAG - PFD
##############################################################################
CONSULTA NUMEROS DE SERIE 
 
Numero Serie                             
_40________________  
              
Articulo          
_40_______________

Lote          
_40_______________

NMVS Status
_40_______________

NMVS Resultado
_40_______________

 PULSE '0' PARA VOLVER: _
 
|

#POSTQUERY=FEJECUTA(FCARGAFORM("VDCONSFMDRAD.FRM"),"ERROR\n AL VOLVER") 

POSTQUERY=FEJECUTA(FIF("CSELMAS",FPOSICIONABLOQUE("VDCONSULTAFMD1.PAN")),"")

#POSTQUERY=FEJECUTA(FPOSICIONABLOQUE("VDCONSULTAFMD1.PAN"),"ERROR\n AL CARGAR BLOQUE VDCONSULTAFMD2.PAN")

CAMPO=NUMEROSERIE,NOENTER,VIRTUAL
CAMPO=CODARTAUX,NOENTER,VIRTUAL
CAMPO=CODLOTAUX,NOENTER,VIRTUAL
CAMPO=NVMSSTATUS,NOENTER,VIRTUAL 
CAMPO=NVMSRET,NOENTER,VIRTUAL    
CAMPO=INTRO

# DEFINICION DE CURSORES
CURSOR=CSELMAS SELECT :INTRO FROM DUAL WHERE :INTRO='0';