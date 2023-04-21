#Módulo: VDCLIDIVASIG.FRM
#Funcionalidad : Asignación rápida de clientes a divisiones
#Autor: JMM
#Fecha: 06-10-2008
#*****************************************************************
#* Histórico de cambios
#* ====================
#
DIVISION
 Div.  Descripcion                               Asignar  Cod. Laboratorio
 _20_  ________________________________________     _     _20_________________ 
|

SOLOQUERY
PQUERY

SELECT=SELECT CODDIV, DESDIV 
         FROM VDDIVIS 
        WHERE CODDIV NOT IN (SELECT CODDIV FROM VDCLIENTESDIVIS WHERE CODCLIENTE=:CODCLIENTE AND SEQCODCLI = :SEQCODCLI) 
        ORDER BY CODDIV ASC;

POSTQUERY=FEJECUTA("CINICIALIZA","No puedo seleccionar datos",
                   FPOSICIONACAMPO(FSUCCESS,"ASIGNAR"),"")
                   
PREUPDATE=FEJECUTA("@CSELASIGNAR","",
                   "CINSCLIENTESDIVIS","\n Error al asignar la division al cliente \n\n",
                   FPULSATECLAS("F3","F2"),""
                   )                   



CAMPO=CODCLIENTE,VIRTUAL,AUXILIAR,OCULTO
CAMPO=SEQCODCLI,VIRTUAL,AUXILIAR,OCULTO

CAMPO=CODDIV,NOENTER
CAMPO=DESDIV,NOENTER
CAMPO=ASIGNAR,AUXILIAR,UPPER,POSTCHANGE=FVERIFICA("SN","Debe introducir S o N")
CAMPO=CODCLILAB,AUXILIAR,UPPER
 
CURSOR=CINICIALIZA SELECT 'N' ASIGNAR FROM DUAL;


CURSOR=CSELASIGNAR SELECT :ASIGNAR FROM DUAL WHERE :ASIGNAR='S';

CURSOR=CINSCLIENTESDIVIS  INSERT INTO VDCLIENTESDIVIS (CODDIV, CODCLIENTE, SEQCODCLI,CODCLILAB, CODOPEMODIF, FECMODIF, HORAMODIF)
                           VALUES (:CODDIV, :CODCLIENTE, :SEQCODCLI, :CODCLILAB, VDUSER.GETUSER, VD.FECHASYS, VD.HORASYS);
    
AYUDA=MANTENIMIENTO DE CLIENTES
ONLINE=    {F1} Ayuda    {F2} Consulta    {F5} Borrar pantalla  {Esc} Salir
          {F4} Asigna Division al Cliente marcados con 'S' en el campo Asignar ;    
