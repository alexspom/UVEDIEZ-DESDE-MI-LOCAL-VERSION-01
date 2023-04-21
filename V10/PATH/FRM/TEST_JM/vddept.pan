# Módulo   : VDDEPT.PAN
# Función  : Formacion con ejemplo de departamentos para empleados
#
# Creación : 30-06-2022
# Autor    : JMGB
###########################################
#
- MAESTRO DEPARTAMENTOS - 
Codigo: @L@@@ Nombre: _30_________
Ciudad: _15______

|

TABLA=VDTDEPT
WLONY=113

#CAMPO=CODDEPT,VIRTUAL,OCULTO
CAMPO=CODDEPT,VIRTUAL,TOOLTIP("Código del Departamento")
#CAMPO=CODDEPT
CAMPO=NOMBRE,TOOLTIP("Nombre del Departamento")
CAMPO=CIUDAD,TOOLTIP("Ciudad del Departamento")

