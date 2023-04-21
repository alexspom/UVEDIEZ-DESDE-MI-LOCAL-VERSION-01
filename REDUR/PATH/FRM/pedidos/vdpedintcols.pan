# Módulo   : VDPEDINTCOLS.PAN
# Función  : Listado de exportaciones
#
# Creación : 20-04-2020
# Autor    : infanahe
###########################################
# Histórico de cambios:

PEDIDOS EXPORTACION BELLOTA
FECHA      CODPED          CODALB        DESSTATUS  DESAGE     PEDIDOCLIENTE  CODCLIENTE  DESCLIENTE              DIRECCION               DIRECCION1              DIRECCION2              CODPOSTAL   CODPAIS  DESPAIS      CONTACTO        BULTOS   PESOPEDIDO  VOLUMENPEDIDO          
¿D-MM-Y.YY _20____________ _20__________ _30______  _40_______ _60__________  _20________ _30____________________ _40____________________ _40____________________ _40____________________ _10_______  _3__     _20_________ _30____________ @L@@@@@  @L@@@@@     @L@@@@@  
|

SOLOQUERY
TABLA=PEDINT
SELECT=select FECHA, CODPED, CODALB, PEDIDOCLIENTE, CODCLIENTE, DESCLIENTE, DIRECCION,
              DIRECCION1, DIRECCION2, COD_POSTAL, CODPAIS, DESPAIS, CONTACTO, BULTOS,
              PESOPEDIDO, VOLUMENPEDIDO, DESSTATUS, DESAGE
         from (select FECTERMIN FECHA, A.CODPED,
                      CODALB, PEDIDOCLIENTE, CODCLIENTE, DESCLIENTE, DIRECCION,
                      DIRECCION1, DIRECCION2, DP COD_POSTAL, A.CODPAIS, P.DESPAIS,
                      CONTACTO, C.DESSTATUS,
                      sum(case
                             when B.CODPED is not null then
                              1
                             else
                              0
                           end) BULTOS, A.PESOPEDIDO, A.VOLUMENPEDIDO, AG.DESAGE
                 from VDPEDIDOCAB A, VDSTATUS C, VDPAIS P, VDBULTOCAB B, VDAGENCIA AG
                where A.CODPAIS not in ('724', '620')
                  and A.CODPED = B.CODPED(+)
                  and C.TIPOSTATUS = 'PEC'
                  and A.STATUS = C.STATUS
                  and P.CODPAIS = A.CODPAIS
                  and DESSTATUS in ('EXPEDIDO', 'FINALIZADO')
                  and AG.CODAGE = A.CODAGE
                  and A.CODDIV = 'BEL'
                  and A.FECTERMIN between :DESDE and :HASTA
                group by FECTERMIN, A.CODPED, CODALB, PEDIDOCLIENTE, CODCLIENTE,
                         DESCLIENTE, DIRECCION, DIRECCION1, DIRECCION2, POBLACION, DP,
                         A.CODPAIS, P.DESPAIS, A.STATUS, C.DESSTATUS, CONTACTO,
                         A.PESOPEDIDO, A.VOLUMENPEDIDO, AG.DESAGE) PEDINT
  WHERE 1=1;
WHERE = 1=1;
REGPAG=40   
WLONX=1300   
   
CAMPO=DESDE,AUXILIAR,VIRTUAL,OCULTO
CAMPO=HASTA,AUXILIAR,VIRTUAL,OCULTO
CAMPO=FECHA,TITULO("Fecha")
CAMPO=CODPED,TITULO("Pedido")
CAMPO=CODALB,TITULO("Albaran")
CAMPO=DESSTATUS,TITULO("Estado"),WLONX=30 
CAMPO=DESAGE,TITULO("Agencia"),WLONX=40
CAMPO=PEDIDOCLIENTE,TITULO("Pedido Cliente")
CAMPO=CODCLIENTE,TITULO("Cod.Cliente")
CAMPO=DESCLIENTE,TITULO("Nombre Cliente")
CAMPO=DIRECCION,TITULO("Direccion"),WLONX=40
CAMPO=DIRECCION1,TITULO("Direccion1"),WLONX=40
CAMPO=DIRECCION2,TITULO("Direccion2"),WLONX=40
CAMPO=COD_POSTAL,TITULO("C.Postal"),WLONX=10
CAMPO=CODPAIS,TITULO("Cod.Pais"),WLONX=3 
CAMPO=DESPAIS,TITULO("Pais"),WLONX=30 
CAMPO=CONTACTO,TITULO("Contacto"),WLONX=40 
CAMPO=BULTOS,TITULO("Bultos"),WLONX=15 
CAMPO=PESOPEDIDO,TITULO("Peso"),WLONX=15 
CAMPO=VOLUMENPEDIDO,TITULO("Volumen"),WLONX=15 
