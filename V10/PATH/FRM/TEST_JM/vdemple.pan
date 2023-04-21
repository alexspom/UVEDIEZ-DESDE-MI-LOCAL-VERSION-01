# M�dulo   : VDEMPLE.PAN
# Funci�n  : Formacion con ejemplo de empleados
#
# Creaci�n : 30-06-2022
# Autor    : JMGB
###########################################
#
- MAESTRO DE EMPLEADOS -
 C�digo Empleado: @L@@@ Correo v10: _50__________________   Tel�fono: _20______
 ������������� DATOS EMPLEADO ����� ����������� DATOS LABORALES ��������������� 
 � Nombre :     _30___________    � � Contrataci�n : �D-MM-Y.YY               �
 � Apellido 1 : _30___________    � � Salario :      @L@@@@@@@@               �
 � Apellido 2 : _30___________    � � Departamento : @L@@@                    �
 ���������������������������������� �������������������������������������������
                           Ultima Modificacion:_32_______ �D-MM-Y.YYY _8______
|
 
TABLA=VDTEMPLE 
ORDERBY=CODEMP ASC;
WLONX=600
#WLONY=400

PREINSERT=FEJECUTA("CSELMODIF","ERROR INSERTANDO ULTIMA MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR ACTUALIZANDO ULTIMA MODIFICACION")


#CAMPO=CODEMP,PREFIELD=FEJECUTA("CSECEMPLE"),POSTCHANGE=FVALNOCERO("Debe introducir un codigo de empleado nuevo(secuencial)"),TOOLTIP("C�digo del Empleado")
CAMPO=CODEMP,POSTCHANGE=FVALNOCERO("Debe introducir un codigo de empleado nuevo(secuencial)"),TOOLTIP("C�digo del Empleado")
CAMPO=EMAIL,TOOLTIP("Correo Corporativo")
CAMPO=NUM_TELEFONO,TOOLTIP("Telefono Corporativo")
CAMPO=NOMBRE,POSTCHANGE=FVALNOCERO("Debe introducir Nombre Empleado"),TOOLTIP("Nombre del Empleado")
CAMPO=FEC_CONTRATACION,TOOLTIP("Fecha de Contrataci�n")
CAMPO=APELLIDO1,POSTCHANGE=FVALNOCERO("Debe introducir al menos el primer apellido"),TOOLTIP("Primer Apellido")
CAMPO=SALARIO,TOOLTIP("Salario del Empleado")
CAMPO=APELLIDO2,TOOLTIP("Segundo Apellido")
CAMPO=CODDEPT,TOOLTIP("Codigo del Departamento"),COMBOX("CLISTADEPT")

CAMPO=CODOPEMODIF,TOOLTIP("Usuario que ha realizado la Ultima modificaci�n.Es utilizado para depuraci�n y control de los registros en las tablas"),TITULO("Ultima modificaci�n")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Es la fecha  en que se efectuO alguna modificaci�n. Es utilizado para depuraci�n y control de los registros en las tablas")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Es la hora  en que se efectuO alguna modificaci�n. Es utilizado para depuraci�n y control de los registros en las tablas")


CURSOR=CSECEMPLE SELECT MAX(CODEMP)+1 CODEMP
                   FROM VDTEMPLE;


CURSOR=CLISTADEPT SELECT CODDEPT,NOMBRE||' '||CIUDAD DESCRIPCION 
                    FROM VDTDEPT ORDER BY CODDEPT;


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, 
						VD.FECHASYS FECMODIF,
						VD.HORASYS HORAMODIF 
				   FROM DUAL;


ONLINE= {F2} Consulta   {F4} Guardar cambios   {Esc} Cerrar Pantalla    {F5} Borrar Pantalla    ;

TECLA=SF10,FLEEMENU("VDEMPLE.ZOO")

BOTON=B1,620,65,35,35,"P",xls.png,F11,"Exportar a Excel",INCLUDECSS="background-color: transparent;border-width:0px"
BOTON=B2,680,65,35,35,"P",refresh.png,F5,"Refrescar pantalla",INCLUDECSS="background-color: transparent;border-width:0px"
BOTON=B3,740,65,35,35,"P",apply.png,F4,"Guardar datos",INCLUDECSS="background-color: transparent;border-width:0px"
BOTON=B4,800,65,35,35,"P",borrar.png,F9,"Guardar datos",INCLUDECSS="background-color: transparent;border-width:0px"