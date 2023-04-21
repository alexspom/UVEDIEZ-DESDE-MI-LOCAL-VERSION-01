select  
CASE 
WHEN t13.ManagedBy = '10000044' and t15.U_SEIEstad = '05' THEN 'Destrucción'
WHEN t13.ManagedBy = '10000045' and t17.U_SEIEstad = '05' THEN 'Destrucción'
ELSE 'Salida'
END as "Salida/Destrucción", 
t0.DocEntry as "DocEntry", t0.DocNum as "Documento", t0.CardCode as "Cliente", t0.CardName as "Nombre", 
nvl(t2.Name,'') as "Persona de contacto", nvl(t0.NumAtCard,'') as "Número ref. cliente", t0.DocCur as "Moneda",
t3.SeriesName as "Serie", 
CASE t0.DocStatus
WHEN 'O' THEN 'Abierto'
WHEN 'C' THEN 'Cerrado'
END as "Status",
t0.DocDate as "Fecha contable", t0.DocDueDate as "Fecha de vencimiento", t0.TaxDate as "Fecha de documento", t0.U_SEIFeEnA as "Fecha Entrada Almacén",
t4.SlpName as "Empl.dpto.Ventas", t5.firstName+' '+t5.LastName as "Titular", nvl(t0.Comments,'') as "Comentarios", 
nvl(t0.ShipToCode,'') as "Codigo Enviar a", t0.Address2 as "Enviar a", t0.PayToCode as "Codigo Destinatario de factura", t0.Address as "Destinatario de factura",
nvl(t6.TrnspName,'') as "Clase de expedición", nvl(t7.AgentName,'') as "Responsable", t8.Name as "Idioma", nvl(t0.BPChCode,'') as "Nombre canal IC",
t9.PymntGroup as "Condición de pago", nvl(t10.Descript,'') as "Vía de pago",
nvl(t0.U_SEILab,'') as "Laboratorio UDF", nvl(t0.U_SEI_EDI3,'') as "PO Quien emite EDI UDF", nvl(t0.U_SEI_EDIP,'') as "PO Quien emite EDI UDF", 
nvl(t0.U_SEI_EDIE,'') as "PO A quien se entrega EDI UDF", nvl(t0.U_SEI_EDIF,'') as "PO Quien Factura EDI UDF", 
nvl(t0.U_SEI_DPTO,'') as "Departamento EDI UDF", nvl(t0.U_SEIdptov,'') as "Venta según ECI UDF", 
nvl(t0.U_SEIsucur,'') as "Sucursal según ECI EDI UDF",  nvl(t0.U_SEI_EDIR,'') as "Ref. Ped. EDI Cliente UDF", 
CASE t0.U_SEIagrup
WHEN 'N' THEN 'NO'
WHEN 'S' THEN 'SI'
End AS "Pedido Agrupado EDI UDF",
nvl(t0.U_SEIfiedi,'') as "Fichero Mensaje EDI UDF",
CASE t0.U_SEIcancelol
WHEN 'N' THEN 'NO'
WHEN 'S' THEN 'SI'
End AS "INSDES Opera.Logist. UDF",
nvl(t0.U_SEItipoo,'') as "Tipo de Observación EDI UDF", nvl(t0.U_SEItexto1,'') as "Observaciones EDI UDF", 
nvl(t0.U_SEI_EDI,'') as "Nº factura EDI asociado UDF", nvl(t0.U_SEI_EDIL,'') as "DESADV EDI asociado UDF", 
nvl(t0.U_SEI_EDIABO,'') as "Nº abono EDI asociado UDF", nvl(t0.U_SEIfiedf,'') "Fichero INVOIC EDI UDF",
nvl(t11.DocNum,0) as "Órden Acondicionamiento UDF",
CASE t0.U_SEIFact
WHEN 'Y' THEN 'SI'
WHEN 'N' THEN 'NO'
ELSE ''
END as "Computable Facturación? UDF",
CASE t0.U_SEIIVRS
WHEN 'Y' THEN 'SI'
WHEN 'N' THEN 'NO'
ELSE ''
END as "IVRS UDF",
CASE t0.U_SEITrGes
WHEN 'Y' THEN 'SI'
WHEN 'N' THEN 'NO'
ELSE ''
END as "Gestionado por Alcura? UDF", 
nvl(t0.U_SEIProyN,'') as "Nombre Proyecto UDF", nvl(t0.U_SEIOrAcN,0) as "Órden Acondicionamiento UDF",
nvl(t0.U_SEIBultos,0) as "Bultos UDF",
CASE t0.U_SEIExpe
WHEN 'Y' THEN 'SI'
WHEN 'N' THEN 'NO'
ELSE ''
END as "Expedido UDF",
nvl(t0.U_SEISol,'') as "Solicitante UDF", nvl(t0.U_SEIInv,'') as "Investigador UDF", 
CASE t0.U_SEIPrEnv
WHEN 'Y' THEN 'SI'
WHEN 'N' THEN 'NO'
ELSE ''
END as "Primer Envío UDF",
CASE t0.U_SEIMuIni
WHEN 'Y' THEN 'SI'
WHEN 'N' THEN 'NO'
ELSE ''
END as "Muestra Inicial UDF",
nvl(t12.DocNum,'') as "Cambio Estado UDF", nvl(t0.U_SEICaEsN,0) as "Número Cambio Estado UDF", t0.U_SEIFeSol as "Fecha Solicitud Cliente UDF",
t0.U_SEIFeEnA as "Fecha Entrada Almacén UDF",
CASE t0.U_SEIUrge
WHEN 'Y' THEN 'SI'
WHEN 'N' THEN 'NO'
ELSE ''
END as "Servicio Urgente? UDF",
nvl(t0.U_SEIBaseImp,0) as "Base Imponible UDF", nvl(t0.U_SEIPrTra,0) as "Transporte (por Caja) UDF", 
t0.U_SEIDeFeF as "Desde Fecha Facturación UDF", t0.U_SEIHaFeF as "Hasta Fecha Facturación UDF", nvl(t0.U_SEIAgr,'') as "Agrupación de Proyectos UDF",
t0.U_SEIFRFECHA as "Factura Rect.Fecha UDF", nvl(t0.U_SEIFRNUMERO,0) as "Factura Rect.Nº UDF", t0.U_SEIFRFECHAULT as "Rect.Agrup.Ult.Fecha UDF",
CASE t0.U_SEIFRTIPO
WHEN 'R0' THEN ''
WHEN 'R1' THEN 'Abonos diferencias precio'
WHEN 'R2' THEN 'Clientes concuros'
WHEN 'R3' THEN 'Clientes dudoso cobro'
WHEN 'R4' THEN 'Devoluciones Albaranes'
ELSE ''
END as "Factura Rect.Tipo UDF",
t0.U_SEIFeInE as "Fecha Inicio Excel UDF", nvl(t0.U_SEIHoInE,0) as "Hora Inicio Excel UDF", 
t0.U_SEIFeFiE as "Fecha Fin Excel UDF", nvl(t0.U_SEIHoFiE,0) as "Hora Fin Excel UDF",
t1.ItemCode as "Número de artículo", t1.Dscription as "Descripción de artículo", 
CASE t13.ManagedBy
WHEN '10000044' THEN t14.Quantity
WHEN '10000045' THEN t14.Quantity
ELSE t1.Quantity 
END as "Cantidad",
t1.Price as "Precio por unidad",
t1.LineTotal as "Total (ML)",
t1.WhsCode as "Almacén",
t1.VatGroup as "Indicador de impuestos", 
CASE t13.ManagedBy
WHEN '10000044' THEN t15.LotNumber
WHEN '10000045' THEn T17.LotNumber
ELSE ''
END as "Lote",
CASE t13.ManagedBy
WHEN '10000044' THEN ''
WHEN '10000045' THEN t17.DistNumber
ELSE ''
END as "Num. Serie",
CASE t13.ManagedBy
WHEN '10000044' THEN nvl(t15.MnfSerial,'')
WHEN '10000045' THEN nvl(t17.MnfSerial,'')
ELSE ''
END as "PCN",
CASE t13.ManagedBy
WHEN '10000044' THEN t15.ExpDate
WHEN '10000045' THEN t17.ExpDate
END as "Caducidad",
CASE t13.ManagedBy
WHEN '10000044' THEN nvl(t16.BinCode,'')
WHEN '10000045' THEN nvl(t16.BinCode,'')
ELSE nvl(t20.BinCode,'')
END AS "Ubicacion",
CASE t13.ManagedBy
WHEN '10000044' THEN 'Lote' 
WHEN '10000045' THEN 'Serie'
ELSE 'Ninguno'
END as "Gestión articulo",
nvl(t1.Project,'') as "Proyecto", nvl(t1.U_SEIProyN,'') as "Nombre Proyecto", 
CASE t21.U_SEIEsta 
WHEN 'A' THEN 'Activo'
WHEN 'C' THEN 'Cerrado'
END as "Estado Proyecto",
nvl(t1.FreeTxt,'') as "Texto libre", nvl(t1.U_SEIArt,'') as "Código Artículo Cálculo", nvl(t1.U_SEIArtN,'') as "Nombre Artículo Cálculo",
nvl(t1.U_SEIUbi,'') as "Ubicación Almacenamiento", 
nvl((select t101.Descr from CUFD t100 
        inner join UFD1 t101 on t100.TableID = t101.TableID and t100.FieldID = t101.FieldID 
        where t100.TableID = 'DLN1' and t100.AliasID = 'SEICuota' and t101.FldValue = t1.U_SEICuota),'') as "Cuota",
nvl(t1.U_SEIPrCuo,0) as "Precio Cuota",
nvl((select t100.ItmsGrpNam from OITB t100 where t100.ItmsGrpCod = t1.U_SEIGrArt),'') as "Grupo Artículo",
nvl(t1.U_SEIPrGA,0) as "Precio Grupo Artículo",
nvl((select t101.Descr from CUFD t100 
        inner join UFD1 t101 on t100.TableID = t101.TableID and t100.FieldID = t101.FieldID 
        where t100.TableID = 'DLN1' and t100.AliasID = 'SEIEmb' and t101.FldValue = t1.U_SEIEmb),'') as "Embalaje",
nvl(t1.U_SEIPrEmb,0) as "Precio Embalaje",
nvl((select t100.Name from "@SEIARTICULO1" t100 where t100.Code = t1.U_SEIClas1),'') as "Tipo Artículo",
nvl(t1.U_SEIPrCl1,0) as "Precio Tipo Artículo",
nvl((select t100.Name from "@SEIARTICULO2" t100 where t100.Code = t1.U_SEIClas2),'') as "SubTipo Artículo",
nvl(t1.U_SEIPrCl2,0) as "Precio SubTipo Artículo",
nvl((select t101.Descr from CUFD t100 
        inner join UFD1 t101 on t100.TableID = t101.TableID and t100.FieldID = t101.FieldID 
        where t100.TableID = 'DLN1' and t100.AliasID = 'SEIAcon' and t101.FldValue = t1.U_SEIAcon),'') as "Acondicionamiento",
nvl(t1.U_SEIIDAco,0) as "ID Acondicionamiento", nvl(t1.U_SEINuAco,0) as "Número Acondicionamiento",
nvl(t1.U_SEIPrAc1,0) as "Precio Acondicio. Primario",
nvl((select t101.Descr from CUFD t100 
        inner join UFD1 t101 on t100.TableID = t101.TableID and t100.FieldID = t101.FieldID 
        where t100.TableID = 'DLN1' and t100.AliasID = 'SEITiAc2' and t101.FldValue = t1.U_SEITiAc2),'') as "Tipo Acondicio. Secundario",
nvl(t1.U_SEIPrTA2,0) as "Precio Tipo Acon. Secun.",
nvl((select t101.Descr from CUFD t100 
        inner join UFD1 t101 on t100.TableID = t101.TableID and t100.FieldID = t101.FieldID 
        where t100.TableID = 'DLN1' and t100.AliasID = 'SEIRand' and t101.FldValue = t1.U_SEIRand),'') as "Randomizado",
nvl(t1.U_SEIPrRan,0) as "Precio Randomizado",
nvl((select t100.Name from "@SEIAGRINTERVALOS" t100 where t100.Code = t1.U_SEIQtt),'') as "Cantidad UDF",
nvl(t1.U_SEIPrQtt,0) as "Precio Cantidad UDF",
nvl((select t101.Descr from CUFD t100 
        inner join UFD1 t101 on t100.TableID = t101.TableID and t100.FieldID = t101.FieldID 
        where t100.TableID = 'DLN1' and t100.AliasID = 'SEIImpAl' and t101.FldValue = t1.U_SEIImpAl),'') as "Impresión en Alcura",
nvl(t1.U_SEIPrImp,0) as "Precio Impresión en Alcura",
nvl((select t101.Descr from CUFD t100 
        inner join UFD1 t101 on t100.TableID = t101.TableID and t100.FieldID = t101.FieldID 
        where t100.TableID = 'DLN1' and t100.AliasID = 'SEIDiEti' and t101.FldValue = t1.U_SEIDiEti),'') as "Diseño Etiquetas",
nvl(t1.U_SEIPrDiE,0) as "Precio Diseño Etiquetas",
nvl((select t101.Descr from CUFD t100 
        inner join UFD1 t101 on t100.TableID = t101.TableID and t100.FieldID = t101.FieldID 
        where t100.TableID = 'DLN1' and t100.AliasID = 'SEIUrge' and t101.FldValue = t1.U_SEIUrge),'') as "Servicio Urgente",
nvl(t1.U_SEIPrUrg,0) as "Precio Servicio Urgente",
nvl((select t101.Descr from CUFD t100 
        inner join UFD1 t101 on t100.TableID = t101.TableID and t100.FieldID = t101.FieldID 
        where t100.TableID = 'DLN1' and t100.AliasID = 'SEIIVRS' and t101.FldValue = t1.U_SEIIVRS),'') as "IVRS",
nvl(t1.U_SEIPrIVR,0) as "Precio IVRS",
nvl((select t101.Descr from CUFD t100 
        inner join UFD1 t101 on t100.TableID = t101.TableID and t100.FieldID = t101.FieldID 
        where t100.TableID = 'DLN1' and t100.AliasID = 'SEIDoc' and t101.FldValue = t1.U_SEIDoc),'') as "Tipo Documento",
nvl(t1.U_SEIIDDoc,0) as "ID Documento", nvl(t1.U_SEINuDoc,0) as "Número Documento",
nvl((select t101.Descr from CUFD t100 
        inner join UFD1 t101 on t100.TableID = t101.TableID and t100.FieldID = t101.FieldID 
        where t100.TableID = 'DLN1' and t100.AliasID = 'SEIDimCa' and t101.FldValue = t1.U_SEIDimCa),'') as "Dimensión Caja",
nvl(t1.U_SEIPrDC,0) as "Precio Dimensión Caja", 
nvl((select t101.Descr from CUFD t100 
        inner join UFD1 t101 on t100.TableID = t101.TableID and t100.FieldID = t101.FieldID 
        where t100.TableID = 'DLN1' and t100.AliasID = 'SEITerm' and t101.FldValue = t1.U_SEITerm),'') as "Termógrafo",
nvl(t1.U_SEIPrTer,0) as "Precio Termógrafo",
nvl((select t101.Descr from CUFD t100 
        inner join UFD1 t101 on t100.TableID = t101.TableID and t100.FieldID = t101.FieldID 
        where t100.TableID = 'DLN1' and t100.AliasID = 'SEITrGes' and t101.FldValue = t1.U_SEITrGes),'') as "Trans. Gestionado por Alcura?",
nvl(t1.U_SEIPrTGA,0) as "Precio Trans. Ges. Alcura",
nvl((select t100.Name from "@SEIZONA" t100 where t100.Code = t1.U_SEIZona),'') as "Zona",
nvl(t1.U_SEIPrZon,0) as "Precio Zona",
nvl((select t101.Descr from CUFD t100 
        inner join UFD1 t101 on t100.TableID = t101.TableID and t100.FieldID = t101.FieldID 
        where t100.TableID = 'DLN1' and t100.AliasID = 'SEIClExp' and t101.FldValue = t1.U_SEIClExp),'') as "Clase Expedición",
nvl(t1.U_SEIPrCE,0) as "Precio Clase Expedición", nvl(t1.U_SEIDesMa,'') as "Descripción Detalle Manual", 
nvl(t1.U_SEIPrMan,0) as "Precio Manual",
nvl((select t100.Name from "@SEITIPOTERMOGRAFO" t100 where t100.Code = t1.U_SEITiTer),'') as "Tipo Termógrafo"

from ODLN@SAP t0
inner join DLN1@SAP t1 on t0.DocEntry = t1.DocEntry
left join OCPR@SAP t2 on t0.CntctCode = t2.CntctCode
left join NNM1@SAP t3 on t0.Series = t3.Series
left join OSLP@SAP t4 on t0.SlpCode = t4.SlpCode
left join OHEM@SAP t5 on t0.OwnerCode = t5.empID
left join OSHP@SAP t6 on t0.TrnspCode = t6.TrnspCode 
left join OAGP@SAP t7 on t0.AgentCode = t7.AgentCode
left join OLNG@SAP t8 on t0.LangCode = t8.Code
left join OCTG@SAP t9 on t0.GroupNum = t9.GroupNum
left join OPYM@SAP t10 on t0.PeyMethod = t10.PayMethCod
left join "@SEIORDENACON"@SAP t11 on t0.U_SEIOrAco = t11.DocEntry
left join "@SEICAMBIOESTADO"@SAP t12 on t0.U_SEICaEs = t12.DocEntry
left join OITL@SAP t13 on t0.DocEntry = t13.DocEntry and t1.ItemCode = t13.ItemCode and t1.LineNum = t13.DocLine and t13.DocType = 15 and ((t13.ManagedBy = 10000044) or (t13.ManagedBy = 10000045))
left join OBTL@SAP t14 ON (t13.LogEntry = t14.ITLEntry)
left join OBTN@SAP t15 ON (t14.SnBMDAbs = t15.AbsEntry)
left join OBIN@SAP t16 ON (t14.BinAbs = t16.AbsEntry)
left join OSRN@SAP t17 ON (t14.SnBMDAbs = t17.AbsEntry)
left join "B1_OinmWithBinTransfer"@SAP t18 on t1.DocEntry = t18.CreatedBy and t1.ItemCode = t18.ItemCode and t1.LineNum = t18.DocLineNum and t18.SnBType = 4 and t18.TransType = 15
left join OBTL@SAP t19 on t18.InvPLMessageID = t19.MessageID
left join OBIN@SAP t20 on t19.BinAbs = t20.AbsEntry
left join OPRJ@SAP t21 on t1.Project = t21.PrjCode
where (t3.ObjectCode@SAP = '15') 
order by "Docentry";


