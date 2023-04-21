#################################################################################
#Módulo: VDBULRETROPED.PAN
#Funcionalidad : Bultos asociados al pedido que queremos retroceder
#Autor: JMM      
#Fecha: 30-07-2008
#################################################################################
# Histórico de cambios:
#
BULTOS ASOCIADOS AL PEDIDO
 Bulto                Tipo  Estado                               Líneas  Resoluble
 _20_________________  _    @L@@@@ _30__________________________ @L@@@@  _64_________________ 
|


TABLA=VDBULTOCAB


CAMPO=CODDIV,VIRTUAL,OCULTO
CAMPO=ANOPED,VIRTUAL,OCULTO
CAMPO=CODPED,VIRTUAL,OCULTO
CAMPO=SEQPED,VIRTUAL,OCULTO
CAMPO=CODBULTO,NOUPDATE,TOOLTIP("Bulto asociado al pedido"),POSTCHANGE=FDESIGNACION("+CSELSTATUS","Estado no existe","+CLINEAS","","+CRESOLUBLE",""),
                        TITULO("Bulto")
CAMPO=TIPOBULTO,NOUPDATE,TOOLTIP("Tipo de bulto "),TITULO("Tipo")
CAMPO=STATUS,NOUPDATE,TITULO("Estado")
CAMPO=DESSTATUS,AUXILIAR,NOENTER
CAMPO=LINEAS,AUXILIAR,NOENTER,TITULO("Líneas")
CAMPO=RESOLUBLE,AUXILIAR,NOENTER,TITULO("Resoluble")

CURSOR=CSELSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='BUC';

CURSOR=CLINEAS SELECT COUNT(*) LINEAS FROM VDBULTOLIN WHERE CODBULTO=:CODBULTO;

CURSOR=CRESOLUBLE SELECT 'SI' RESOLUBLE FROM DUAL 
                   WHERE NOT EXISTS (SELECT 1 FROM VDMOVIM MOV,VDBULTOLIN BUL 
                                      WHERE CODBULTO = :CODBULTO AND MOV.CODMOV = BUL.CODMOV AND 
                                           MOV.STATUS < VDST.FMOVPDTERECOGE)
                  UNION ALL
                  SELECT 'NO' || DECODE(NVL(MOV.CODMOVESP,0),0,'','- PENDIENTE DE MOV. ' || MOV.CODMOVESP) RESOLUBLE
                    FROM VDMOVIM MOV,VDBULTOLIN BUL
                   WHERE CODBULTO=:CODBULTO AND MOV.CODMOV = BUL.CODMOV AND MOV.STATUS < VDST.FMOVPDTERECOGE;




