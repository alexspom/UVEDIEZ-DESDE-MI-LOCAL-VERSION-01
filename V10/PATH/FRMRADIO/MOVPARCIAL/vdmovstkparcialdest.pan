# M�dulo   : VDMOVSTKPARCIALDEST.PAN
# Funci�n  : Formulario de movimiento de stock parcial asignado a recurso
#            Pantalla de lectura de ubicacion destino.
#
# Creaci�n : 20-05-2008
# Autor    : JMM
###########################################
# Hist�rico de cambios:
#
MOVIMIENTO DE STOCK PARCIAL
_10_______ _10_______ 
MOVIMIENTO PARCIAL
LECTURA DE UBICACION DESTINO

ARTICULO: _40_________________
______________________________
______________________________
LOTE _40_________________
CAJAS   U/E      + PICO 
##### * #L#######  #L#######
TOTAL UNIDADES A COGER
#L############# _10__ 

UB.DESTINO  ____________
            ____________
|

PREQUERY=FEJECUTA("CSELLIMPIACAMPOS","ERROR\n AL LIMPIAR\nLOS CAMPOS",                 
                  "CSELLONGERROR","ERROR\n OBTENIENDO PROPIEDAD\n LONGERROR")

POSTQUERY=FEJECUTA("CSELVERIFUBI","\nERROR,\nLA UBICACION LEIDA INCORRECTA\n LEIDO :CODUBIDESTLEIDO\n ESPERADO :CODUBIDEST",
                   "CUPMOV","ERROR ACTUALIZANDO DESTINO",
                   "CUPDRECURSO","ERROR \nACTUALIZANDO \nRECURSO",
                   FCOMMIT,"ERROR\n HACIENDO COMMIT",
                   FCARGATERMINAL("CODOPE"),"ERROR \nCARGANDO \nRECURSO")

# DEFINICION DE CAMPOS
CAMPO=CODRECURSO,VIRTUAL,NOENTER
CAMPO=CODOPE,VIRTUAL,NOENTER
CAMPO=CODMATORI,VIRTUAL,OCULTO
CAMPO=CODUBIORI,VIRTUAL,OCULTO
CAMPO=CODART,VIRTUAL,NOENTER
CAMPO=DESART1,VIRTUAL,NOENTER
CAMPO=DESART2,VIRTUAL,NOENTER
CAMPO=CODLOT,VIRTUAL,NOENTER
CAMPO=NCAJAS,VIRTUAL,NOENTER
CAMPO=UNIEMB,VIRTUAL,NOENTER
CAMPO=UNIDSUELTAS,VIRTUAL,NOENTER
CAMPO=TOTALUNID,VIRTUAL,NOENTER
CAMPO=UNIDADESHOST,VIRTUAL,NOENTER
CAMPO=CODUBIDEST,VIRTUAL,NOENTER
CAMPO=CODUBIDESTLEIDO,SCAN,AUTOENTER
#,POSTCHANGE=FEJECUTA(FFUERZASCAN("UBI"),"\nERROR\n DEBE SCANNEAR\n LA UBICACION")
CAMPO=MSGERROR,OCULTO,"_512_"
CAMPO=LONGERROR,OCULTO,"@@@"
CAMPO=BULTO,VIRTUAL,OCULTO

# DEFINICION DE CURSORES
CURSOR=CSELLIMPIACAMPOS SELECT NULL CODUBIDESTLEIDO FROM DUAL; 

CURSOR=CSELLONGERROR SELECT VD.GETPROP('LONGITUDERROR') LONGERROR FROM DUAL;

CURSOR=CSELVERIFUBI SELECT :CODUBIDEST 
                      FROM DUAL
                     WHERE :CODUBIDEST=:CODUBIDESTLEIDO;

CURSOR=CDIVIDEERROR BEGIN :MSGERROR:=VD.DIVERRORRADIO(:V10ERROR,:LONGERROR);
                    END;@

CURSOR=CUPDRECURSO UPDATE VDRECURSO 
                      SET NPANTALLA=NULL,
                          STATUS=VDST.FRECBUSCANDO,
                          CODOPEMODIF=:CODOPE, 
                          FECMODIF=VD.FECHASYS, 
                          HORAMODIF=VD.HORASYS
                    WHERE CODRECURSO=:CODRECURSO;

CURSOR=CUPMOV UPDATE VDMOVIM MOV
                 SET STATUS = VDST.FMOVDEPOSITADO,                     
                     CODOPEMODIF=:CODOPE,     
                     FECMODIF=VD.FECHASYS,    
                     HORAMODIF=VD.HORASYS     
               WHERE CODRECURSO=:CODRECURSO AND
                     MOV.STATUS = VDST.FMOVENUBIINTER AND
                     MOV.CODRECURSO = :CODRECURSO AND
                     MOV.CODMATORI = :CODMATORI AND
                     MOV.CODUBIORI = :CODUBIORI AND
                     MOV.CODUBIDEST = :CODUBIDEST AND
                     MOV.UNIEMB  = :UNIEMB AND
                     MOV.CODART  = :CODART AND
                     MOV.CODLOT  = :CODLOT AND
                     (MOV.BULTO   = :BULTO OR :BULTO IS NULL);