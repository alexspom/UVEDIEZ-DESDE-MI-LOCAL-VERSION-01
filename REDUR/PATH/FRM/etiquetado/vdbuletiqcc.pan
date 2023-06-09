#
CAJAS COMPLETAS PENDIENTES DE ETIQUETAR
Art�culo   Descripci�n                EAN            CAJAS 
_20_______ _40_______________________ ______________ @L@@@  _50_________________________ 
|

AQUERY
SOLOQUERY
WLONX=850
SELECT=SELECT ART.CODART,ART.DESART,ART.CODEAN,COUNT(BUC.CODBULTO) CAJAS,'S' ETIQUETAR,
              DECODE(ART.SWTNUMEROSERIE,'L','LECTURA DE NUMEROS DE SERIE','') TXTNUMEROSERIE
         FROM VDBULTOCAB BUC,VDBULTOLIN BUL,VDARTIC ART
        WHERE BUC.CNTSSCC=:CNTSSCC AND BUC.TIPOBULTO='E' AND 
              BUC.STATUS+0=VDST.FBUCAETIQUETAR AND BUC.CODBULTO=BUL.CODBULTO AND
              BUL.CODART=ART.CODART;

GROUPBY=ART.CODART,ART.DESART,ART.CODEAN,ART.SWTNUMEROSERIE;


CAMPO=CNTSSCC,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODART,AUXILIAR,NOENTER,TITULO("Art�culo")
CAMPO=DESART,AUXILIAR,NOENTER,TITULO("Descripci�n")
CAMPO=CODEAN,AUXILIAR,NOENTER,TITULO("EAN")
CAMPO=CAJAS,AUXILIAR,NOENTER,TITULO("CAJAS"),WLONX=5
CAMPO=TXTNUMEROSERIE,AUXILIAR,NOENTER,WLONX=20
CAMPO=ETIQUETAR,AUXILIAR,OCULTO,"_"


CONTEXTUAL=FEJECUTAFORM("VDBULTOSMA","N","CODBULTO IN (SELECT BUC.CODBULTO FROM VDBULTOCAB BUC,VDBULTOLIN BUL WHERE BUC.CODBULTO=BUL.CODBULTO AND CNTSSCC=:CNTSSCC AND TIPOBULTO='E' AND BUC.STATUS+0=VDST.FBUCAETIQUETAR AND BUL.CODART=:CODART)")
