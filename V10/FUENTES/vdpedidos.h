#include "execproc/vdexec.h"
#include "impresion/vdimpresion.h"

#define MAXAGE             101 // M�ximo n�mero de agencias diferentes para un pedido
#define LSWITCH              2 // Longitud de los distintos indicadores SWT
#define BULCNT          25000L // Primer n�mero de bulto de contenedores en la creaci�n de bultos
#define BULEMBA         50000L // Primer n�mero de bulto de embalajes en la creaci�n de bultos
#define BULUNI          75000L // Primer n�mero de bulto de unidades en la creaci�n de bultos
#define MAXLINBU          5000 // M�ximo n�mero de l�neas de bulto
#define MAXCAJAS            20 // M�ximo n�mero de cajas por volumetr�a 
VDEXPORT int validapedidorig(void *ptr,char *param);
VDEXPORT int grabapedidosorig(void *ptr,char *param);

VDEXPORT int vdimprimebulto(vdbultocabs *cb,char *tipoimpre,char *documento,char *params,char *fichero,char *codimpre,int copias,char *msjerror);
VDEXPORT int vdimprimepedido(vdpedidocabs *pec,char *tipoimpre,char *documento,char *params,char *codimpre,int copias,char *msjerror);
VDEXPORT int vdexportapedido(vdpedidocabs *pec,char *tipoimpre,char *documento,char *params,char *fichero,int copias,int modospool,char *msjerror);
	
// trata los pedidos de series de picking inverso, al final del c�lculo de volumetr�a del mismo
extern int pickinvfinvolumetria(vdpedidocabs *pec,char *forzarpickinv, int *espickinv, int *pickinvret);
VDEXPORT int vdcreabultospinvconte(char *codmat,char *codrecurso,char *tarea,long stmov,
								   char *codubirestos,char *mitarearestos,char *micodconcerestos, long maxbultos);
VDEXPORT int vdregularizabpc(char *codbulto,char *codmat,char *codart,char *codlot,long uniemb,
							 char *codubidest,char *codubireserva,long total,char *codconce,char *ubicodconce,
							 char *observ,char *msjerror); 
VDEXPORT int vdpartemovpinv(long codmov,char *ubipickinv,char *codmatbulto,double *codmovout,char *msjerror);
VDEXPORT int vdreenganchasprpinv(long codserieprep,long stpdteequili,long stpdtebulinv,long stpickinv,
								 char *diferido,char *tareadiferidauni, char *tareadiferidaemba,long stpedido, char *ejecmovemba);
VDEXPORT int vdregularizastkpinv(char *codmat,long ordenstk,char *codconce,char *codubicodconce,double cantidad,
								 char *observ,double *codmovout,char *codubidest,char *comentario,char *msjerror);
VDEXPORT int creabpc(char *codmat,int status,char *msjerror);
VDEXPORT int damenombredocumento(char *tipoimpre, char *coddiv, long anoped, char *codped, long seqped,
	char *tipobulto, char *documento, char *fichero, char *driver, char *msjerror);
VDEXPORT int damedriverimpresora(char *tipoimpre, char *documento, char *fichero, char *codimpre, char *driver, char *msjerror);