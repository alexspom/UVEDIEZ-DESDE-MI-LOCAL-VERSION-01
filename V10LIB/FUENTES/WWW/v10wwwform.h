#ifndef __v10wwwform
#define __v10wwwform
#include "v10form.h"
#include "v10www.h"



#define EVBLOQUE 0
#define EVCAMPO	 1

#define MARCONORMAL		0
#define MARCOFRAME		1
#define MARCOPESTANA	2
#define MARCOBACIO		3

extern int debug;

typedef struct _evhandlers {  
	char *ev; 
	int (*fun)(v10dialogs *,v10httpeventos *);
    int esajax;
} evhandlers;

#define ONCLICK "onclick"
#define ONKEYUP "onkeyup"
#define ONKEYUPCOLA "onkeyupcola"


V10WWWIMPORT int recibidologin;
int muestracombox;
evhandlers *v10gethandler(char *ev);

// v10wwwforaux.c
void v10wwwfejecutaformaux(forms *formanterior,forms *formactual,int *ret);
int v10wwwcommitsino(forms *f);
void v10frecalcpadreaux(bloques *b,bloques *padre);
int v10llbloquearegistroaux(bloques *b);
int v10finputregistroaux(bloques *b); 
void v10wwwpintapaginabloque(virtsels *s,int resaltado);
void v10wwwactualizabloque(bloques *b);
int v10camposnoenter(v10dialogs *v);

// v10wwvirtsel.c
bloques *v10damebloqueactual(void);
int v10damenumbloque(bloques *b);
V10WWWIMPORT forms *v10dameformactual(void);
fcampos *v10campoactual(bloques *b); 
int v10nbcampoactivo(bloques *b);
V10WWWIMPORT int semueveelraton(bloques *b);
int v10wwwreposicionadialograton(v10dialogs *v);
int v10wwwreposicionaregraton(v10dialogs *v);
int v10wwwreposicionaraton(virtsels *s);
int v10wwwreposratonform(forms *f);
void v10guardatodosenter(bloques *b);
int v10evposterior(v10dialogs *v,int ret);
int v10wwwblinput(v10dialogs *vi);

// v10evqueue.c
void v10evencolaevento(v10httpeventos *ev);
void v10evencola(char *objeto,char *evento,char *valor,char *antid,char *antvalor);
void v10evclick();
int v10evtecla(int t);
int v10evpushtecla(int c);
int v10evrunencolados(v10dialogs *vi);
int v10evencolados(void);
int v10evencoladosnoajax(void);

// v10ev.c
extern v10httpeventos evactual;
fcampos *v10evdamecampo(bloques *b,v10httpeventos *ev);
bloques *v10evdamebloque(v10httpeventos *ev);
int v10evfilasidem(bloques *b,v10httpeventos *ev);
int v10evcamposidem(v10httpeventos *ev);
void trataevbloques(v10httpeventos *ev);
int v10htmlevento(v10dialogs *vi);
int v10htmleventodummy(v10dialogs *vi);
int v10evtipo(v10httpeventos *ev);
int v10evdamefila(v10httpeventos *ev);
int v10evdamecolumna(v10httpeventos *ev);
void v10evdamevalor(v10dialogs *vi, v10httpeventos *mievento);
int v10runhander(v10dialogs *vi,v10httpeventos *ev);
int v10evento(void);

// v10evdefhandlers.c
void v10addhandler(char *ev,int (*fun)(v10dialogs *v,v10httpeventos *),int esajax); 

// v10evrunhandlers.c
void v10ponhandlers(void);


// v10wwwform.c
void v10form2html(forms *f,int timeout);
V10WWWIMPORT void v10form2plantillahtml(forms *f,char *ruta);

// v10htmlmenu.c
void v10menu2html(menus *m);
int v10wwwelige(char *opcion);
V10WWWIMPORT menus *menuactual;

// v10htmlmenucontext.c
int v10wwwmenucontex(formenus *f);

// v10wwwcheckbox.c
void v10checkbox2html(char *ptrout,int nbloque,int multireg,int fila, int ncol, bloques *b,fcampos *f,int incluyevalores);

// v10wwwwindow.c
int v10openbrowserwindow();
int v10wwwabrelink(char *);

// v10wwwcssdetalles.c
char *cssalign(fcampos *c);

// v10wwwbloque.c
void v10bloques2html(forms *f, int tipodatos);
V10WWWIMPORT void v10bloque2plantillahtml(bloques *b,char *ruta);
void v10incluyebloques(forms *f);
int entrablecampo(fcampos *c);
void creavaruser(char *v10html);
V10WWWIMPORT void(*dameusuario)(char *donde);

// v10wwwteclas.c
void v10jsteclas(forms *f);
void v10jsonload(forms *f,int timeout);
void damefilasycolumnas(bloques *b);

// v10wwwbotones.c
void v10botones2html(int nbloque,bloques *b,int tipodatos);
void v10cargabotoneradef(void);

// v10wwwonline.c
void v10online2html(bloques *b,char *cad, int extonline);

// v10wwwtabla.c
void v10tabla2html(int nbloque,bloques *b,int incluyevalores,formtabs *ftab);

// v10wwwinput.c
void dametipohtmlcampo(fcampos *c,char *tipo);
void v10tooltip2html(bloques *b,fcampos *c,char *tooltiphtml);
void v10inputcelda2html(char *ptrout,int nbloque,int ancho,int fila,int col,bloques *b,fcampos *c,int readonly,int incluyevalores);
void v10inputnoenter2html(char *ptrout,int nbloque,int fila,int col, bloques *b,fcampos *c,int incluyevalores);
void v10input2html(char *ptrout,int nbloque,int fila,int col,bloques *b,fcampos *c,int incluyevalores);

// v10wwwframes.c
void v10frames2html(bloques *b,int bloque,int top,int left);

// v10wwwliterales.c
void v10labels2html(int nbloque,bloques *b,formtabs *ftab);

// v10httppost.c
int v10httpesperaevento(v10dialogs *v,v10httpeventos *_v10ev,int enajax);

// v10wwwcombox.c
void v10combox2html(char *ptrout,int nbloque,int multireg, int fila, int ncol, int top, int left, bloques *b,fcampos *f,int incluyevalores);

// v10wwwcalendario.c
void v10calendario2html(char *ptrout,int nbloque,int multireg,int fila, int ncol,int sutop,int suleft, bloques *b,fcampos *c);

// v10wwwreposiciona.c
void v10recolocaform(forms *f);
void v10damedimensionesbloque(bloques *b, int *left, int *top, int *ancho, int *largo);
double damepxcol(bloques *b);
int damepxfila(bloques *b);

// v10wwwwhere.c
int v10wwwselwhere(char **opciones,int primera,int x,int y);

// v10wwwmensajes.c
void v10wwwmensajegen(char *titulo,char *cadena);
void v10wwwvmensajefm(int x,int y,char *cadena,va_list arg);
int v10wwwconfirmasn(int x,int y,char *cadena);
void v10wwwmensajeform(forms *f,char *mensaje,...);
int v10wwwmensajezoom(forms *f,char *titulo,char *cadena);
void v10wwwmensajeonline(char *titulo,char *cadena);
int v10wwwmensajewhere(char *textowhere,char *textoorder,char *textohaving,char *titulowhere);
int v10wwwmensajeselwhere(char *titulo,char *cadena);
int v10wwwmensajeforminfo(char *titulo,char *cadena, char *online);
void v10wwwmensajecampos(char *titulo,char *cadena);
int v10wwwmensajedebug(char *cadena,char *online);
int v10wwwmensajecursores(char *cadena);
void v10wwwmensajecombox(char *texto,int multiple);
void v10wwwmensajecalendario(char *texto);
void v10wwwmensajeabrelink(char *link);
V10WWWIMPORT void v10wwwmensajexls(char *fichero);
V10WWWIMPORT void v10wwwmensajepdf(char *fichero);
void wwwtratamensajesprev(char *cadena);
void wwwtratamensajespost(char *cadena);
int haymensajesprev(void);
int haymensajespost(void);

// v10wwwora2html.c
char *v10ora2campo(int incluyevalores,int nbloque,bloques *b,fcampos *c,int fila,char *nombre, int esinput, char *valor);
void v10mascarav2html(int nbloque,int fila,bloques *b);
void initvbloque(bloques *b);
int limitvbloque(bloques *b,int i);
int damevbloquei(bloques *b,int i);
void finvbloque(bloques *b);

// v10wwwaborta.c
void v10wwwerror(char *formato,va_list lista_param_variable,short salir);

// v10wwwformsg.c
void v10wwwforminfo(forms *f);
void v10wwwformerror(forms *f,char *msg);

// v10wwwdebug.c
void v10wwwcursordebug(v10cursors *c);
void v10wwwldadebug(void *param,int funcion);

// v10wwwayuda.c
void ayudaform(forms *f, char *v10html);
void ayudamenu(menus *m, char *v10html);

//v10wwwstats.c
void v10statsform(forms *f);

//v10wwwtecladovirt.c
void v10cargatecladovirtual(void);

//v10wwwAJAX.C
void AJAXform2HTML(bloques *b);
void AJAXmenu2HTML();

//v10wwwquery2HTML.c 
int v10cad2query(bloques *b, char *cad, char *query);
void v10query2html(char *sql, char *html);
int v10cursor2html(char *sql,char *campos,char *html);

#endif