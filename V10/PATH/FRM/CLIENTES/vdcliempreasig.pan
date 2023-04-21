#Módulo: VDCLIEMPREASIG.FRM
#Funcionalidad : Asignación rápida de clientes a divisiones de una empresa
#Autor: FPD
#Fecha: 24-03-2014
#*************************************************************************
#* Histórico de cambios
#* ====================
#
EMPRESA
 Empresa  Descripcion                               Asignar  Cod. Cliente Divis.
 ____  ________________________________________     _     _20_________________ 
|

SOLOQUERY
PQUERY

SELECT=SELECT CODEMP, DESEMP 
  FROM VDEMPRE EMP 
 WHERE EXISTS (SELECT DIV.CODDIV FROM VDDIVIS DIV WHERE DIV.CODEMP=EMP.CODEMP AND DIV.SWTACTIVA='S' AND DIV.CODDIV NOT IN (SELECT CODDIV FROM VDCLIENTESDIVIS WHERE CODCLIENTE=:CODCLIENTE AND SEQCODCLI = :SEQCODCLI)) 
ORDER BY CODEMP ASC;
        

POSTQUERY=FEJECUTA("CINICIALIZA","No puedo seleccionar datos",
                   FPOSICIONACAMPO(FSUCCESS,"ASIGNAR"),"")
                   
PREUPDATE=FEJECUTA("@CSELASIGNAR","",
                   "CINSCLIENTESDIVIS","\n Error al asignar la empresa al cliente \n\n",
                   FPULSATECLAS("F3","F2"),""
                   )                   



CAMPO=CODCLIENTE,VIRTUAL,AUXILIAR,OCULTO
CAMPO=SEQCODCLI,VIRTUAL,AUXILIAR,OCULTO

CAMPO=CODEMP,NOENTER,TITULO("Empresa")
CAMPO=DESEMP,NOENTER
CAMPO=ASIGNAR,AUXILIAR,UPPER,POSTCHANGE=FVERIFICA("SN","Debe introducir S o N"),TITULO("Asignar")
CAMPO=CODCLIDIV,AUXILIAR,UPPER
 
CURSOR=CINICIALIZA SELECT 'N' ASIGNAR FROM DUAL;


CURSOR=CSELASIGNAR SELECT :ASIGNAR FROM DUAL WHERE :ASIGNAR='S';

CURSOR=CINSCLIENTESDIVIS  INSERT INTO VDCLIENTESDIVIS (CODDIV, CODCLIENTE, SEQCODCLI,CODCLIDIV, CODOPEMODIF, FECMODIF, HORAMODIF)
                           SELECT CODDIV, :CODCLIENTE, :SEQCODCLI, :CODCLIDIV, VDUSER.GETUSER, VD.FECHASYS, VD.HORASYS
                             FROM VDDIVIS
                            WHERE CODEMP=:CODEMP;
    
AYUDA=MANTENIMIENTO DE CLIENTES
ONLINE=    {F1} Ayuda    {F2} Consulta    {F5} Borrar pantalla  {Esc} Salir
          {F4} Asigna Empresas al Cliente marcando con 'S' en el campo Asignar;    
