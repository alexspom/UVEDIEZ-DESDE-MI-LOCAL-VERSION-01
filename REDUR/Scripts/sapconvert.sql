SELECT t0."ItemCode" as "Número de artículo", t0."ItemName" as "Descripción", t0."ItmsGrpCod" as "Codigo Grupo de artículos", 
t1."ItmsGrpNam" as "Grupo de artículos", 
CASE t0."InvntItem"
WHEN 'Y' THEN 'SI'
WHEN 'N' THEN 'NO'
ELSE ''
END as "Art.inventario",
CASE t0."SellItem"
WHEN 'Y' THEN 'SI'
WHEN 'N' THEN 'NO'
ELSE ''
END as "Artículo de venta",
CASE t0."PrchseItem"
WHEN 'Y' THEN 'SI'
WHEN 'N' THEN 'NO'
ELSE ''
END as "Artículo de compra",
CASE t0."WTLiable"
WHEN 'Y' THEN 'SI'
WHEN 'N' THEN 'NO'
ELSE ''
END as "Sujeto a retención", 
nvl(t0."ShipType",'') as "Codigo Clase de expedición", nvl(t2."TrnspName",'') as "Clase de expedición",
CASE
WHEN t0."ManBtchNum" = 'Y' THEN 'Lotes'
WHEN t0."ManSerNum" = 'Y' THEN 'Números de serie'
ELSE 'Ning.'
END as "Gestionar artículo por",
CASE t0."MngMethod"
WHEN 'A' THEN 'En cada operación'
WHEn 'R' THEN 'Sólo en salida'
ELSE ''
END as "Método de gestión",
CASE t0."IssuePriBy"
WHEN 0 THEN 'Números de serie y de lote'
WHEN 1 THEN 'Ubicaciones'
ELSE ''
END as "Emisión principalmente por",
CASE
WHEN t0."frozenFor" = 'Y' THEN 'NO'
WHEN t0."frozenFor" = 'N' THEN 'SI'
END as "Activo",
nvl(t0."BuyUnitMsr",'') as "medida de compras", t0."NumInBuy" as "Artículos por un.compras", 
nvl(t0."PurPackMsr",'') as "medida de embalaje compras", t0."PurPackUn" as "Cantidad por embalaje compras",
t0."VatGroupPu" as "Grupo impositivo compras", 
nvl(t0."BLength1",0) as "Longitud compras", nvl(t3."UnitDisply",'') as "Longitud compras medida",
nvl(t0."BWidth1",0) as "Ancho compras", nvl(t4."UnitDisply",'') as "Ancho compras medida",
nvl(t0."BHeight1",0) as "Altura compras", nvl(t5."UnitDisply",'') as "Altura compras medida",
nvl(t0."BVolume",0) as "Volumen compras", nvl(t6."VolDisply",'') as "Volumen compras medida",
nvl(t0."BWeight1",0) as "Peso compras", nvl(t17."UnitDisply",'') as "Peso compras medida",
t0."VatGourpSa" as "Grupo impositivo ventas", 
nvl(t0."SalUnitMsr",'') as "medida de ventas", t0."NumInSale" as "Artículos por un.ventas", 
nvl(t0."SalPackMsr",'') as "medida de embalaje ventas", t0."SalPackUn" as "Cantidad por embalaje ventas",
nvl(t0."SLength1",0) as "Longitud ventas", nvl(t7."UnitDisply",'') as "Longitud ventas medida",
nvl(t0."SWidth1",0) as "Ancho ventas", nvl(t8."UnitDisply",'') as "Ancho ventas medida",
nvl(t0."SHeight1",0) as "Altura ventas", nvl(t9."UnitDisply",'') as "Altura ventas medida",
nvl(t0."SVolume",0) as "Volumen ventas", nvl(t10."VolDisply",'') as "Volumen ventas medida",
nvl(t0."SWeight1",0) as "Peso ventas", nvl(t18."UnitDisply",'') as "Peso ventas medida",
t0."GLMethod" as "Fijar cuentas de mayor por",
nvl(t0."InvntryUom",'') as "Nombre de unidad de medida", 
t0."ByWh" as "Gestión de stocks por almacén",
nvl(t0."U_SEILab",'') as "Laboratorio UDF", nvl(t0."U_SEIean14",'') as "Código EAN-14 EDI UDF", nvl(t11."Name",'') as "Tipo Artículo UDF",
nvl(t12."Name",'') as "SubTipo Artículo UDF", 
t0."U_SEICaja" as "Es Caja? UDF",
nvl(t13."Name",'') as "Condición de Transporte UDF",
t0."U_SEIDimCa" as "Dimensión Caja UDF",
t0."U_SEITerm" as "Es Termógrafo UDF",
t0."U_SEIEti" as "Es Etiqueta UDF",
t0."U_SEIFaRan" as "Facturar como Randomizado? UDF",
CASE t0."U_SEIImpGA"
WHEN 'Y' THEN 'SI'
WHEN 'N' THEN 'NO'
ELSE ''
END as "Imprimir Grupo Artículo? UDF",
NVL(t14."Name",'') as "Impresión UDF", nvl(t15."Name",'') as "Tipo Termógrafo UDF", 
NVL(t16."Name",'') as "Activity Line Alcura UDF"
from OITM@SAP t0
left join OITB@SAP t1 on t0."ItmsGrpCod" = t1."ItmsGrpCod"
left join OSHP@SAP t2 on t0."ShipType" = t2."TrnspCode"
left join OLGT@SAP t3 on t0."BLen1Unit" = t3."UnitCode"
left join OLGT@SAP t4 on t0."BWdth1Unit" = t4."UnitCode"
left join OLGT@SAP t5 on t0."BHght1Unit" = t5."UnitCode"
left join OLGT@SAP t6 on t0."BVolUnit" = t6."UnitCode"
left join OLGT@SAP t7 on t0."SLen1Unit" = t7."UnitCode"
left join OLGT@SAP t8 on t0."SWdth1Unit" = t8."UnitCode"
left join OLGT@SAP t9 on t0."SHght1Unit" = t9."UnitCode"
left join OLGT@SAP t10 on t0."SVolUnit" = t10."UnitCode"
left join "@SEIARTICULO1"@SAP t11 on t0."U_SEIClas1" = t11."Code"
left join "@SEIARTICULO2"@SAP t12 on t0."U_SEIClas2" = t12."Code"
left join "@SEICONDTRANS"@SAP t13 on t0."U_SEIConTr" = t13."Code"
left join "@SEIAGRIMPRESION"@SAP t14 on t0."U_SEIAgrIm" = t14."Code"
left join "@SEITIPOTERMOGRAFO"@SAP t15 on t0."U_SEITiTer" = t15."Code"
left join "@SEIACTLINALCURA"@SAP t16 on t0."U_SEIAcLiA" = t16."Code"
left join OWGT@SAP t17 on t0."BWght1Unit" = t17."UnitCode"
left join OWGT@SAP t18 on t0."SWght1Unit" = t18."UnitCode";