KPI DE PREPARACIONES
Fecha      Pedidos  Lineas Unidades BPalet Bcajas Bpicking Upalet  Ucajas  Upicking
�D-MM-Y.YY @L@@@    @L,@@@ @L,@@@@  @L,@@  @L,@@@ @L,@@@@  @L,@@@@ @L,@@@@ @L,@@@@
|
SOLOQUERY

SELECT=SELECT COUNT(DISTINCT PEC.CODPED) NUMPED,COUNT(*) NUMLIN
        FROM VDPEDIDOCAB PEC
        WHERE PEC.CODPED=PEL.CODPED AND PEC.CODDIV=PEL.CODDIV AND PEC.ANOPED=PEL.ANOPED AND PEC.SEQPED=PEL.SEQPED AND
              PEC.FECTERMIN BETWEEN :DESDE AND :HASTA;

CAMPO=DESDE,AUXILIAR,VIRTUAL,OCULTO
CAMPO=HASTA,AUXILIAR,VIRTUAL,OCULTO
CAMPO=FECTERMIN
CAMPO=NUMPED
CAMPO=NUMLIN
CAMPO=NUMUNI
CAMPO=BPALET
CAMPO=BCAJAS
CAMPO=BPICKING
CAMPO=UPALET
CAMPO=UCAJAS
CAMPO=UPICKING