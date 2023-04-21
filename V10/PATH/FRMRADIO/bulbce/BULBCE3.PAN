#
GESTION DE BULBCE CON ETIQUETA
_10_______ _10_______
CAJA COMPLETA

ORIGEN: ____________________

ARTICULO: _20___________
_20_________________
_30_________________________
_30_________________________

 BULTO SIN PREPARAR 
 (FALTAN: @L@@ )

  LEA ETIQUETA DE BULTO
  _______________________

|

PREQUERY=FEJECUTA("CNBFALTAN","",
                  "CLIMPIA","")

POSTQUERY=FEJECUTA(FIF("CBUSCABULPDTE",FSUCCESS,
                                       FEJECUTA("CBUSCABUL","\n BULTO :CODSERIADO \n INCORRECTO",
                                                "CINTERCAMBIABUL","\n ERROR INTERCAMBIANDO \n BULTO :CODSERIADO")),"\n ERROR ACTUALIZANDO BULTO",
                   "CUPDBULTO","\n ERROR ACTUALIZANDO BULTO",
                   FCOMMIT,"",   
                   FIF("CFALTANANULAR",
                       FPOSICIONABLOQUE("BULBCE3.PAN"),
                       FEJECUTA("CSELMOVSAJECUTAR","\n ERROR\n AL RECUPERAR LOS\n MOVIMIENTOS A EJECUTAR",
                                FWHILE(FERRORCURSOR("CSELMOVSAJECUTAR"),
                                       FEJECUTA(FIF(FEJECUTAMOVSYNC("ACTSTKORIGEN","ACTSTKDESTINO",":CODMOV",":CODRECURSO"),
                                                    FSUCCESS,
                                                    FEJECUTA("+CDIVIDEERROR","",FFAILURE," ERROR\n :MSGERROR")),"",
                                               "+CSELHAYALB","\n ERROR \n CALCULANDO ALBARANES",
                                               "CACABABULTOS","ERROR ACABANDO BULTOS",
                                               +FFETCHCURSOR("CSELMOVSAJECUTAR"),"")),"",
                                FCOMMIT," ERROR\n HACIENDO COMMIT",
                                FIF("CHAYALBARAN",
                                    FPOSICIONABLOQUE("BULBCE8.PAN"),
                                    FSUCCESS),"",
                                FIF("CSELMOV",
                                    FPOSICIONABLOQUE("BULBCE1.PAN"),     
                                    FPOSICIONABLOQUE("BULBCE5.PAN")),"")),"")  
                                 

# DEFINICION DE CAMPOS
CAMPO=CODRECURSO,VIRTUAL,NOENTER
CAMPO=CODOPE,VIRTUAL,NOENTER
CAMPO=PINTAUBI,VIRTUAL,NOENTER
CAMPO=CODUBIORIGT,VIRTUAL,OCULTO
CAMPO=CODARTT,VIRTUAL,NOENTER
CAMPO=CODARTANT,VIRTUAL,NOENTER
CAMPO=DESARTT,VIRTUAL,NOENTER
CAMPO=DESARTT1,VIRTUAL,NOENTER
CAMPO=NBFALTAN,NOENTER
CAMPO=CODSERIADOPAN,SCAN,AUTOENTER,POSTCHANGE=FEJECUTA(FFUERZASCAN("BUL"),"\n DEBE LEER CODIGO\n SERIADO DEL BULTO",
                                                       +FANALIZAEANRAD("CODSERIADOPAN","00","CODSERIADO"),"")
CAMPO=CODSERIADO,OCULTO,"_18_"
CAMPO=UNIEMB,VIRTUAL,OCULTO
CAMPO=CAJAS,VIRTUAL,OCULTO
CAMPO=CANTIDAD,VIRTUAL,OCULTO
CAMPO=CODMATT,VIRTUAL,OCULTO
CAMPO=SERVIDA,VIRTUAL,OCULTO
CAMPO=DEFECTUOSO,VIRTUAL,OCULTO
CAMPO=SKORIG,VIRTUAL,OCULTO
CAMPO=CODPED,VIRTUAL,OCULTO
CAMPO=CERO,VIRTUAL,OCULTO
CAMPO=CODUBIDEST,VIRTUAL,OCULTO
CAMPO=AJUSTEPOS,OCULTO,"_10_"
CAMPO=AJUSTENEG,OCULTO,"_10_"
CAMPO=AJUSTEDEF,OCULTO,"_10_"
CAMPO=CODUBI,OCULTO,"_12_"
CAMPO=CODPREPARACION,VIRTUAL,OCULTO
CAMPO=CODMOV,OCULTO,"@L@@@@@@@"
CAMPO=LONGERROR,OCULTO,"@@@"
CAMPO=CODBULTO,OCULTO,"_18_"
CAMPO=NUMALBA,VIRTUAL,OCULTO


CURSOR=CBUSCABULPDTE SELECT BUC.CODBULTO
                       FROM VDBULTOCAB BUC,VDBULTOLIN BUL 
                      WHERE BUC.STATUS+0=VDST.FBUCBULABANETI AND BUC.SWTANULAR='S' AND BUC.CODBULTO=:CODSERIADO AND
                            BUC.CODBULTO=BUL.CODBULTO AND
                            BUL.CODMOV IN (SELECT MOV.CODMOV 
                                             FROM VDMOVIM MOV
                                            WHERE MOV.TAREA = 'PEDEMBA' 
                                              AND MOV.STATUS IN (VDST.FMOVPDTESTOCK,VDST.FMOVPDTERECOGE)
                                              AND MOV.CODRECURSO = :CODRECURSO
                                              AND MOV.CODUBIDEST = :CODUBIDEST 
                                              AND MOV.CODART     = :CODARTT
                                              AND MOV.UNIEMB     = :UNIEMB
                                              AND MOV.CODPREPARACION = :CODPREPARACION);

CURSOR=CBUSCABUL SELECT BUC.CODBULTO,BUL.CODMOV
                   FROM VDBULTOCAB BUC,VDBULTOLIN BUL 
                  WHERE BUC.STATUS+0=VDST.FBUCBULABANETI AND BUC.CODBULTO=:CODSERIADO AND
                        BUC.CODBULTO=BUL.CODBULTO AND
                        BUL.CODMOV IN (SELECT MOV.CODMOV 
                                         FROM VDMOVIM MOV
                                        WHERE MOV.TAREA = 'PEDEMBA' 
                                          AND MOV.STATUS = VDST.FMOVPRESENTADO
                                          AND MOV.CODRECURSO = :CODRECURSO
                                          AND MOV.CODUBIDEST = :CODUBIDEST 
                                          AND MOV.CODART     = :CODARTT
                                          AND MOV.UNIEMB     = :UNIEMB
                                          AND MOV.CODPREPARACION = :CODPREPARACION);

CURSOR=CINTERCAMBIABUL DECLARE
                         MICODBULTO VDBULTOCAB.CODBULTO%TYPE;
                         MICODMOV VDMOVIM.CODMOV%TYPE;
                       BEGIN
                         SELECT BUC.CODBULTO,BUL.CODMOV INTO MICODBULTO,MICODMOV
                           FROM VDBULTOCAB BUC,VDBULTOLIN BUL 
                          WHERE BUC.STATUS+0=VDST.FBUCBULABANETI AND BUC.SWTANULAR='S' AND 
                                BUC.CODBULTO=BUL.CODBULTO AND
                                BUL.CODMOV IN (SELECT MOV.CODMOV 
                                                 FROM VDMOVIM MOV
                                                WHERE MOV.TAREA = 'PEDEMBA' 
                                                  AND MOV.STATUS IN (VDST.FMOVPDTESTOCK,VDST.FMOVSINSTOCK,VDST.FMOVPDTERECOGE)
                                                  AND MOV.CODRECURSO = :CODRECURSO
                                                  AND MOV.CODUBIDEST = :CODUBIDEST 
                                                  AND MOV.CODART     = :CODARTT
                                                  AND MOV.UNIEMB     = :UNIEMB
                                                  AND MOV.CODPREPARACION = :CODPREPARACION) AND
                                ROWNUM=1;
                         VDLOG.PONMENSAJE('BULBCE3','ACTUALIZANDO LINEA DE BULTO '||:CODBULTO||' CON MOVTO '||MICODMOV||' PARA DEJAR PENDIENTE');
                         UPDATE VDBULTOLIN SET CODMOV=MICODMOV WHERE CODBULTO=:CODBULTO;
                         VDLOG.PONMENSAJE('BULBCE3','ACTUALIZANDO LINEA DE BULTO '||MICODBULTO||' CON MOVTO '||:CODMOV||' PARA SERVIR');
                         UPDATE VDBULTOLIN SET CODMOV=:CODMOV WHERE CODBULTO=MICODBULTO;
                         UPDATE VDBULTOCAB SET SWTANULAR='N' WHERE CODBULTO=MICODBULTO;
                       END;@

CURSOR=CUPDBULTO UPDATE VDBULTOCAB SET STATUS=VDST.FBUCBULABAN,SWTLLEVAALB=' ',SWTANULAR='N',
                                       CODOPEMODIF=:CODRECURSO,
                                       FECMODIF=VD.FECHASYS,
                                       HORAMODIF=VD.HORASYS
                  WHERE CODBULTO=:CODBULTO;

CURSOR=CNBFALTAN SELECT COUNT(DISTINCT BUC.CODBULTO) NBFALTAN
                   FROM VDBULTOCAB BUC,VDBULTOLIN BUL
                  WHERE BUC.STATUS+0=VDST.FBUCBULABANETI AND BUC.SWTANULAR='S' AND BUC.CODBULTO=BUL.CODBULTO AND 
                        BUL.CODMOV IN (SELECT MOV.CODMOV 
                                         FROM VDMOVIM MOV
                                        WHERE MOV.TAREA = 'PEDEMBA' 
                                          AND MOV.STATUS IN (VDST.FMOVPDTESTOCK,VDST.FMOVPDTERECOGE)
                                          AND MOV.CODRECURSO = :CODRECURSO
                                          AND MOV.CODUBIDEST = :CODUBIDEST 
                                          AND MOV.CODART     = :CODARTT
                                          AND MOV.UNIEMB     = :UNIEMB
                                          AND MOV.CODPREPARACION = :CODPREPARACION);
                                                                 
CURSOR=CFALTANANULAR SELECT :CAJAS 
                       FROM VDBULTOCAB BUC,VDBULTOLIN BUL
                      WHERE BUC.STATUS+0=VDST.FBUCBULABANETI AND BUC.SWTANULAR='S' AND BUC.CODBULTO=BUL.CODBULTO AND 
                            BUL.CODMOV IN (SELECT MOV.CODMOV 
                                             FROM VDMOVIM MOV
                                            WHERE MOV.TAREA = 'PEDEMBA' 
                                              AND MOV.STATUS IN (VDST.FMOVPDTESTOCK,VDST.FMOVPDTERECOGE)
                                              AND MOV.CODRECURSO = :CODRECURSO
                                              AND MOV.CODUBIDEST = :CODUBIDEST 
                                              AND MOV.CODART     = :CODARTT
                                              AND MOV.UNIEMB     = :UNIEMB
                                              AND MOV.CODPREPARACION = :CODPREPARACION);  

                      
CURSOR=CLIMPIA SELECT NULL CODSERIADOPAN FROM DUAL WHERE 1=1; 

CURSOR=CSELHAYALB SELECT :NUMALBA+DECODE(BUC.SWTLLEVAALB,'S',1,0) NUMALBA
                    FROM VDBULTOCAB BUC,VDBULTOLIN BUL
                   WHERE BUC.CODBULTO=BUL.CODBULTO AND BUC.SWTLLEVAALB='S' AND 
                         BUL.CODMOV=:CODMOV;

CURSOR=CHAYALBARAN SELECT :NUMALBA FROM DUAL WHERE :NUMALBA>0;
                                   
CURSOR=CSELMOV SELECT 'N' CERO                       
                     FROM VDMOVIM MOV,VDARTIC ART, VDUBICA UBI
                    WHERE MOV.STATUS IN (VDST.FMOVASIGNADO,VDST.FMOVPRESENTADO) 
                          AND MOV.CODRECURSO = :CODRECURSO 
                          AND MOV.TAREA = 'PEDEMBA'
                          AND ART.CODART = MOV.CODART
                          AND MOV.CODUBIORI = UBI.CODUBI
                    ORDER BY UBI.ORDENSALIDA,MOV.CODPREPARACION,DECODE(MOV.STATUS,VDST.FMOVPRESENTADO,0,1);
             
CURSOR=CSELMOVSAJECUTAR SELECT MOV.CODMOV
                          FROM VDMOVIM MOV
                         WHERE MOV.STATUS = VDST.FMOVPRESENTADO 
                           AND MOV.TAREA = 'PEDEMBA'
                           AND MOV.CODUBIORI = :CODUBIORIGT
                           AND MOV.CODRECURSO = :CODRECURSO
                           AND MOV.CODUBIDEST = :CODUBIDEST 
                           AND MOV.CODMATORI  = :CODMATT
                           AND MOV.CODART = :CODARTT
                           AND MOV.UNIEMB = :UNIEMB
                           AND MOV.CODPREPARACION = :CODPREPARACION;                                   

CURSOR=CDIVIDEERROR BEGIN :MSGERROR:=VD.DIVERRORRADIO(:V10ERROR,:LONGERROR);
                    END;@

CURSOR=CACABABULTOS DECLARE
                      RET NUMBER;
                    BEGIN
                      RET:=VDBULTO.ACABABULTOS(:CODMOV,:CODRECURSO,VDST.FBUCPREPARADO,VDST.FBUCAVERIF,VDST.FBUCAMANIPULAR);
                    END;@
