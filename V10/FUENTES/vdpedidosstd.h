#include "execproc/vdexec.h"
#include "impresion/vdimpresion.h"

#define MAXAGE             101 // Máximo número de agencias diferentes para un pedido
#define LSWITCH              2 // Longitud de los distintos indicadores SWT
#define BULCNT          25000L // Primer número de bulto de contenedores en la creación de bultos
#define BULEMBA         50000L // Primer número de bulto de embalajes en la creación de bultos
#define BULUNI          75000L // Primer número de bulto de unidades en la creación de bultos
#define MAXLINBU          5000 // Máximo número de líneas de bulto
#define MAXCAJAS            20 // Máximo número de cajas por volumetría 
#define TERMINFASE1         60 //
#define TERMINFASE2         50 //
#define TERMINFASE3         40 //
#define TERMINFASE4         30 //
#define TERMINFASE5         20 //
#define TERMINFASE6         10 //

typedef struct versionpedidoage {
  char agencia[LCODAGE];
  int  versionpedido;
} VERSIONPEDIDOAGE;

typedef struct LINARTS {
  char codart[LCODART];
  char codlot[LCODLOT];
  char unidadeshost[LUNIDADESHOST];
  char unidades[LUNIDADES];
  long seqlinea;
  long codmov;
  long ordenmovim;
  long codinfozona;
  double pedida;
  double pedidav10;
  long largouni;
  long anchouni;
  long altouni;
  double volumenuni; 
  double pesouni;
  double coefuni;
  long unipaq;
  long largopaq;
  long anchopaq;
  long altopaq;
  double volumenpaq;
  long altura;
  double pesopaq;
  double coefpaq;
  long nbultos;     // Número de bultos de unibulto 
  double unibulto;  // Unidades por bulto, en sueltas o paquetes 
  double paqbulto;  // Paquetes por bulto 
  double npaquetes; // Paquetes del pico
  double nsueltas;  // Unidades del pico 
  double volpico;   // Volumen total del pico 
  double volbulto;  // Volumen total del bulto completo
  double pesopico;  // Peso total del pico
  double numuni;    // Total de unidades del bulto 
  long maxlargo;
  long maxancho;
  long maxalto;
  char swttumbable[LSWTTUMBABLE];
  int homogeneo;    // Indicador de pico homogeneo 
  int genera;
  struct LINARTS *sig;
  int npicos;
  int terminada;
  int bulto;
} linarts;


VDEXPORT int validapedidorig(void *ptr,char *param);
VDEXPORT int grabapedidosorig(void *ptr,char *param);

VDEXPORT int vdimprimebulto(vdbultocabs *cb,char *tipoimpre,char *documento,char *params,char *codimpre,int copias,char *msjerror);
VDEXPORT int vdimprimepedido(vdpedidocabs *pec,char *tipoimpre,char *documento,char *params,char *codimpre,int copias,char *msjerror);
VDEXPORT int vdexportapedido(vdpedidocabs *pec,char *tipoimpre,char *documento,char *params,char *fichero,int copias,int modospool,char *msjerror);
	
// trata los pedidos de series de picking inverso, al final del cálculo de volumetría del mismo
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