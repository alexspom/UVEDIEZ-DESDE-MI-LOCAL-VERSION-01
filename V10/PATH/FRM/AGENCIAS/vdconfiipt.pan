#*****************************************************************
#Módulo: VDCONFIIPT.PAN
#Funcionalidad : Incrementos porcentuales de los campos asociandos a las tarifas de las agencias para la autofacturacion
#Autor: Sergio Rojo      
#Fecha: 16-02-2009
#* Copyright @2009 V10, S.A.                                 *
#*****************************************************************
#* Histórico de cambios
#* ====================
#
#*****************************************************************
#
#
#*****************************************************************
INCREMENTOS PORCENTUALES DE LOS CAMPOS ASOCIADOS A LAS TARIFAS

  Campos de la autofacturación    (IPT, Incremento Porcentual de la Tarifa)                                         Valor      Ultima modificación
  _255____________________________________________________________________________________________________________  #L#.###   _32________ ¿D-MM-Y.YY  ________


                                                                                                                                             |


TABLA=VDCONFI
WHERE=GRUPOPROP='AUTOFACTURACION' AND PROPIEDAD LIKE 'IPT%';
REGPAG=20

PQUERY

NODELETE
NOINSERT
PREINSERT=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")

CAMPO=COMENTARIO,TOOLTIP("Descripción de la propiedad"),NOENTER,TITULO("Campos de la autofacturación    (IPT, Incremento Porcentual de la Tarifa)")
CAMPO=VALOR,NOUPDATE("FACTURACION"),TITULO("Valor")
CAMPO=CODOPEMODIF,NOENTER,TITULO("Ult. Modificación")
CAMPO=FECMODIF,NOENTER
CAMPO=HORAMODIF,NOENTER

CURSOR=CSELMODIF SELECT VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

ONLINE= {F1} Ayuda    {F2} Consulta    {F4} Confirmar cambios    {Esc} Cerrar Pantalla    
                 {F5} Borrar Pantalla    ;
