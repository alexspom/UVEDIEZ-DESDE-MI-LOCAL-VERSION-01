# Módulo   : VDDEMANDALINDET.PAN
# Función  : Detalle de Líneas de Demanda
#
# Creación : 25-03-2008
# Autor    : FGS
###########################################
# Histórico de cambios:
DETALLE DE LINEAS DE DEMANDA

 ÏÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ Filtros ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË     
 ³ Codmat: __________________        Lote: _40_______________   Bloqueos: __________          ³
 ³ Uniemb: #L15##########       Marca Stk: _60_______________  Tipo Emba: __________          ³
 ³ Precio: #L15##########      Cod.Recep.: _20_______________                                 ³  
 ³ Bulto:  _20_______________  Num. Serie: _60_______________                                 ³  
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
 
 BackOrder: _    Uniagrupa: _   Redondeo: _  Orden Reserva: _  Orden Reserva en Uic.: _ Comentario: #L#######
 Marca Stk Origen: _60________________________________ Claveext: _50________________________________________
 
 Inicio:   ¿D-MM-Y.YY  ________      Insercción: _32________ ¿D-MM-Y.YY  ________ 
 Finaliz:  ¿D-MM-Y.YY  ________      Ult. Modif: _32________ ¿D-MM-Y.YY  ________
|


TABLA=VDDEMANDALIN

PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")


CAMPO=CODDEMANDA,VIRTUAL,OCULTO
CAMPO=TIPODEMANDA,VIRTUAL,OCULTO
CAMPO=LINDEMANDA,VIRTUAL,OCULTO
CAMPO=CODART,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODUBIORI,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODUBIDEST,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODAREAORI,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODAREADEST,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODMAT,TOOLTIP("Si se informa, matrícula donde se debe encontrar la mercancía a trasladar.")
CAMPO=CODLOT,TOOLTIP("Si se informa, Lote a trasladar")
CAMPO=BLOQUEOS,TOOLTIP("Si se informa, patrón de estado a satisfacer por la mercancia a trasladar")
CAMPO=UNIEMB,TOOLTIP("Si se informa, Unidades por embalaje de la mercancia a trasladar")
CAMPO=MARCASTK,TOOLTIP("Si se informa, la mercancia a trasladar debe estar marcado con su valor")
CAMPO=TIPOEMBA,TOOLTIP("Si se informa, Tipo de embalaje de la mercancia a trasladar")
CAMPO=PRECIOUNI,TOOLTIP("Si se informa, precio unitario de la mercancia a trasladar")
CAMPO=CODRECEP,TOOLTIP("Si se informa, Código de Recepción de la mercancía a trasladar")
CAMPO=BULTO,TOOLTIP("Si se informa, Código de bulto de la mercancía a trasladar")
CAMPO=NUMEROSERIE,TOOLTIP("Si se informa, valor del campo NUMEROSERIE a cumplir por la mercancia a trasladar")
CAMPO=BACKORDER,NOUPDATE,TOOLTIP("Backorder de la línea de Demanda, (P)arcial (cantidad reservada superior o inferior) o (E)xacta")
CAMPO=UNIAGRUPA,NOUPDATE,TOOLTIP("Determina en que se expresa la cantidad pedida. (U)nidades,(E)mbalajes o (C)ontenedores")
CAMPO=TIPOREDONDEO,TOOLTIP("Tipo de Redondeo de la línea en caso de BACKORDER a (E)xacto. Puede ser\n(N) sin redondeo\n(B) redondea a bulto si hay trazabilidad de bulto\n(E) redondea a embalajes completos según stock, por exceso (CEIL)\n(D) redondea a embalajes completos según stock, por defecto (FLOOR)\n(C) redondea a contenedor completo")
CAMPO=ORDENRESERVA,TOOLTIP("(A) dentro de la misma prioridad de área, ORDSALAUT(FEFO) y PRIORIDAD EMBALAJE, se reserva por cantidad ascendente del contenedor. Por defecto.\n(D) dentro de la misma prioridad de áreas,ORDSALAUT(FEFO) y PRIORIDAD EMBALAJE, se reserva por cantidad descendente del contenedor")
CAMPO=ORDENRESERVAUBI,TOOLTIP("En reserva de stock, después de ordenar por ORDENRESERVA, para una ubicación, se reserva por\n(A) POCONTE y ORDENSTK ascendente. Por defecto.\n(D) POSCONTE y ORDENSTK descendente")
CAMPO=CODCOMEN,NOENTER,TOOLTIP("Identificador de los comentarios asociados a la línea de la Demanda")
CAMPO=MARCASTKORIGEN,NOUPDATE,TOOLTIP("Si se informa, no se genera movto en la mercancia encontrada, se limita a marcarla con su valor")
CAMPO=CLAVEEXT,NOENTER,TOOLTIP("Clave externa que permite relacionar con otros sistemas")
CAMPO=FECINI,NOUPDATE,TOOLTIP("Fecha en la que se reserva la linea o la primera parte de esta")
CAMPO=HORAINI,NOUPDATE,TOOLTIP("Hora en la que se reserva la linea o la primera parte de esta")
CAMPO=CODOPEINSERT,NOENTER,TOOLTIP("Operario que inserto la línea de demanda")
CAMPO=FECINSERT,NOENTER,TOOLTIP("Fecha de insercción de la línea")
CAMPO=HORAINSERT,NOENTER,TOOLTIP("Hora de inserción de la línea")
CAMPO=FECFIN,NOUPDATE,TOOLTIP("Fecha de cierra la línea de demanda, al ejecutarse sus movtos")
CAMPO=HORAFIN,NOUPDATE,TOOLTIP("Hora de cierre de la línea, al ejecutarse sus movtos")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la Ultima modificación")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora de la Ultima modificación")


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;




