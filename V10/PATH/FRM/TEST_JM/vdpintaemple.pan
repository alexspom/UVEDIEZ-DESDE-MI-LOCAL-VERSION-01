# M�dulo   : VDPINTAEMPLE.PAN
# Funci�n  : Formacion con lectura de empleados
#
# Creaci�n : 30-06-2022
# Autor    : JMGB
###########################################
#
DATOS EMPLEADOS 
 Nombre         Email               Tel�fono   Nombre        Apellido1      Apellido2      Contratacion   Salario    Departamento
 _30___________ _50________________ _20______ _30___________ _30___________ _30___________ �D-MM-Y.YY     @L@@@@@@@@ @L@@@
|

TABLA=VDTEMPLE 
ORDERBY=CODEMP ASC;

REGPAG=10

#CAMPO=CODEMP,VIRTUAL,NOENTER,TOOLTIP("C�digo del Empleado"),TITULO("Cod. Emp")
CAMPO=CODEMP,NOENTER,TOOLTIP("C�digo del Empleado"),TITULO("Cod. Emp")
CAMPO=EMAIL,NOENTER,TOOLTIP("Correo Corporativo"),TITULO("Correo v10")
CAMPO=NUM_TELEFONO,NOENTER,TOOLTIP("Telefono Corporativo"),TITULO("Tel�fono")
CAMPO=NOMBRE,NOENTER,TOOLTIP("Nombre del Empleado"),TITULO("Nombre")
CAMPO=APELLIDO1,NOENTER,TOOLTIP("Primer Apellido"),TITULO("Apellido1")
CAMPO=APELLIDO2,NOENTER,TOOLTIP("Segundo Apellido"),TITULO("Apellido2")
CAMPO=FEC_CONTRATACION,NOENTER,TOOLTIP("Fecha de Contrataci�n"),TITULO("Contratacion")
CAMPO=SALARIO,NOENTER,TOOLTIP("Salario del Empleado"),TITULO("Salario")
CAMPO=CODDEPT,NOENTER,TOOLTIP("Codigo del Departamento"),TITULO("Cod. Dept"),WLONX=15


