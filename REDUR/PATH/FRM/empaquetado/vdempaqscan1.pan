EMPAQUETADO DE BULTOS
C�digo : _18_______________    Matricula: _18________ 
Pedido:  _20_______________ Div.:____ _40_____________________ A�o: @@@@   Versi�n: @@@@  
Tara:         #L############# g.   Parcial: #L,###### #L,###### #L###
Peso Real:    #L############# g.   Peso Te�rico: #L############# g.


OK            _______________



|
TABLA=VDBULTOCAB
WHERE= (CODPED,CODDIV,ANOPED,SEQPED) IN (SELECT CODPED,CODDIV,ANOPED,SEQPED FROM VDBULTOCAB WHERE CODBULTO=:CODBULTOAUX) AND STATUS=4100;
NOINSERT
NOUPDATE
NODELETE
AQUERY
POSTQUERY=FEJECUTA("CSELTARA","NO PUEDO OBTENER LA TARA DEL BULTO","CRECALC","","+CSELAMA","",FPULSATECLAS("F6"),"")

CAMPO=CODMESA,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODBULTOAUX,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODBULTO,NOENTER
CAMPO=MATCAJA,NOENTER
CAMPO=CODPED,NOENTER
CAMPO=CODDIV,NOENTER
CAMPO=DESDIV,AUXILIAR,NOENTER
CAMPO=ANOPED,NOENTER
CAMPO=SEQPED,NOENTER
CAMPO=TARA,NOENTER
CAMPO=TARAPARCIAL,AUXILIAR,NOUPDATE
CAMPO=ULTIMOPESO,AUXILIAR,NOUPDATE
CAMPO=MARGENPESO,NOUPDATE,AUXILIAR
CAMPO=ULTIMACANTIDAD,NOUPDATE,AUXILIAR,OCULTO,"@L@@@@"
CAMPO=ULTIMOART,NOUPDATE,AUXILIAR,OCULTO,"_20"
CAMPO=PESOREAL,NOUPDATE,NOENTER,WLONX=50,INCLUDECSS="font-size:37px;color:yellow;font-familiy:Times New Roman;height:48px;background-color:black;"
CAMPO=PESOTEORICO,AUXILIAR,NOUPDATE,NOENTER,INCLUDECSS="font-size:37px;color:yellow;font-familiy:Times New Roman;height:48px;background-color:black;color:green"
CAMPO=OK,AUXILIAR,NOUPDATE,WLONX=90,INCLUDECSS="font-size:45px;color:yellow;font-familiy:Times New Roman;height:60px;background-color:black;"
CAMPO=DATOSEXTRA,OCULTO,NOUPDATE,AUXILIAR,"_100________________________________________________________________"
CAMPO=DATOSEXTRA2,OCULTO,NOUPDATE,AUXILIAR,"_100________________________________________________________________"

                           
				
CURSOR=CSELTARA SELECT TARA TARA FROM VDBULTOCAB WHERE CODBULTO=:CODBULTO;

CURSOR=CSELAMA SELECT 'AMAZON' OK FROM VDPEDIDOCAB WHERE CODPED=:CODPED AND CODDIV=:CODDIV AND ANOPED=:ANOPED AND SEQPED=:SEQPED AND SUFIJODOC LIKE 'AMA%';
                           

CURSOR=CRECALC SELECT DECODE(:TARAPARCIAL,0,NVL(SUM(ART.PESOUNI*BUL.CANTSERVIDA),0)+:TARA,:TARAPARCIAL+:ULTIMOPESO) PESOTEORICO
                FROM VDBULTOLIN BUL,VDARTIC ART
                WHERE BUL.CODBULTO=:CODBULTO AND ART.CODART=BUL.CODART;                             
