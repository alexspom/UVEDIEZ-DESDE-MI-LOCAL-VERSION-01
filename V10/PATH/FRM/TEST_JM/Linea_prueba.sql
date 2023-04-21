select fecmodif,
       horamodif,
       codbulto,--oculto
       seqlinea,
       codart,
       cantpedida,
       codlot,
       status
  from vdbultolin
 where codbulto='384352800003799557'
 order by seqlinea;
 
select status,desstatus from vdstatus where tipostatus='BUL';
SELECT codart,desart FROM vdartic WHERE codart='P088XPRNC'

 
select fecmodif,
       horamodif,
       codbulto,
       codped,
       nbulto,
       tipovol,
       tipocaja,
       pesoteorico,
       pesoreal,
       volumen,
       status
  from vdbultocab
 where codbulto='384352800003799557'; 
 -- codped='298696094'
select status,desstatus from vdstatus where tipostatus='BUC' ;


select fecmodif,
       horamodif,
       codped,
       codcliente,
       codalb,
       tipopedido
  from vdpedidocab
 where codped='298696094';
 
select nbulto from vdbultocab 
 group by nbulto
 order by 1 