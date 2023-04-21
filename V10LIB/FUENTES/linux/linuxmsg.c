/*
* M�dulo : WINMSG.C
* Objeto:  Tratamiento de mensajes windows
*
*
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/

#include "v10.h"
//#include <commdlg.h>

#define CM_FONT            1000
#define CM_PRINTSCREENVER  1001
#define CM_PRINTSCREENHOR  1002
#define DESPPAN 2

#define MAXVENTANAS 20
int singrafico = 0;

static struct hwnd arrvent[MAXVENTANAS];

HWND nuevaventana(void)
{
    int i;
    for (i=0;i<MAXVENTANAS;i++) {
        if (arrvent[i].usado==0) {
            arrvent[i].usado=1;
	        arrvent[i].sinx = singrafico;
            return arrvent+i;
        }
    }
    return NULL;
}

HWND dameventana(Window win)
{
    int i;
    for (i=0;i<MAXVENTANAS;i++) {
        if (arrvent[i].win==win && arrvent[i].usado) return arrvent+i;
    }
    return(NULL); 
}

HWND ventanainvalida(void)
{
    int i;
    for (i=0;i<MAXVENTANAS;i++) {
        if (arrvent[i].invalido) return arrvent+i;
    }
    return(NULL);
}

int _argc;
char **_argv;
unsigned int COLUMNASPANTALLA=140;
unsigned int LINEASPANTALLA=60;
int MODOSHOW=SW_SHOWMAXIMIZED;
HINSTANCE v10hinst,v10hprev;
char TITULOVENTANA[MAXPATH]="V10 SOLUCIONES, S.L.";
typedef struct {
        int   numcol;
        int   numlin;
        int   altofont;
        int   anchofont;
        char  *font;
      } textparams;

HWND hwnddefecto;
COLORREF TINTANOBMP=0x007f0000L;
COLORREF PAPELNOBMP=0x007f7f7fL;
colventanas COLORTRANSP={0,0};
char charblanco = ' ';
int centrar_titulo=1;
int menucerrar=1;
char *V10BMP="DEFECTO.BMP";

/*

static long fwm_mousemove(HWND hwnd,int x,int y,UINT flags)
{
	extrawins *t=dameextrawin(hwnd);
	if ((flags&MK_LBUTTON)==0) {
        mueveratontooltip(hwnd,x,y);
		return(0);
	}
	STDencolatecla(MUEVERATON);
	mousepos.boton=BOTONI;
	mousepos.action=CLICK;
	mousepos.posx=x/t->anchofont+t->origenx;
	mousepos.posy=y/t->altofont+t->origeny;
	mousepos.hwnd=hwnd;
	return(0);
}

void presentacursor(HWND hwnd)
{
    extrawins *t=dameextrawin(hwnd);
   if (hwnd==GetFocus()) {
      switch (t->modocursor) {
        case SINCURSOR:SetCaretPos((t->cursorx-t->origenx)*t->anchofont,(t->cursory-t->origeny+1)*t->altofont);
                      break;
        case CURSORNORMAL:SetCaretPos((t->cursorx-t->origenx)*t->anchofont,(t->cursory-t->origeny+1)*t->altofont-3);
                      break;
        case CURSORSOLIDO:SetCaretPos((t->cursorx-t->origenx)*t->anchofont,(t->cursory-t->origeny)*t->altofont);
                      break;
       }
     }
}

*/


Display *xwindisplay;
static int screen_num;
Colormap cmap;
static int initx=0;
int bitspixel = 24;

int damecolorlinux(unsigned long rgb)
{
    XColor color;
	color.blue = (rgb >> 16) & 0xff;
    color.red=rgb&0xff;
    color.green=(rgb>>8)&0xff;
    color.flags=DoRed|DoGreen|DoBlue;
	if (bitspixel == 24) color.pixel = (color.blue ) + ((color.green) << 8) + ((color.red) << 16); else color.pixel = (color.blue >> 3) + ((color.green >> 2) << 5) + ((color.red >> 3) << 11);
    //ret=XAllocColor(xwindisplay,cmap,&color);
    return(color.pixel);
}


static int trataxerror(Display *d,XErrorEvent *err)
{
    printf("Detectado error %d\n",err->error_code);
    return(0);
}

static int pintatexto(Display *xwindisplay,Drawable d,GC gc,int x,int y,char *string, int length)
{
    XDrawImageString(xwindisplay,d,gc,x,y,string,length);
    return(0);
}

#define TCURSOR 50
static int cursorpuesto=0;
static v10horas desdecursor=0;
void llpresentacursor(HWND hwnd,int fuerza)
{
    extrawins *t=dameextrawin(hwnd);
    colventanas antcol;
    int x,y;
	if (hwnd->sinx == 1) return;
    x=t->cursorx;y=t->cursory;
    if (damecent()-desdecursor>TCURSOR) {
        cursorpuesto=1-cursorpuesto;
        desdecursor=damecent();
    } else if (fuerza==0) return;
    antcol=t->texto[x+y*t->columnas].c;
      switch (t->modocursor) {
        case SINCURSOR:return;
        case CURSORNORMAL:if (cursorpuesto) {
                              XSetState(xwindisplay,t->hdc, damecolorlinux(antcol.papel), damecolorlinux(antcol.papel), GXinvert,0xffffffff);
                              XFillRectangle(xwindisplay,hwnd->win, t->hdc, (x-t->origenx)*t->anchofont,(y+1-t->origeny)*t->altofont-2, t->anchofont, 2);
                              XSetState(xwindisplay,t->hdc, damecolorlinux(antcol.papel), damecolorlinux(antcol.papel), GXcopy,0xffffffff);
                            } else {
                              XSetForeground(xwindisplay,t->hdc,damecolorlinux(antcol.tinta));
                              XSetBackground(xwindisplay,t->hdc,damecolorlinux(antcol.papel));
                              pintatexto(xwindisplay,hwnd->win,t->hdc, (x-t->origenx)*t->anchofont,(y+1-t->origeny)*t->altofont,&t->texto[x+y*t->columnas].ch,1);
                            }
                      break;
        case CURSORSOLIDO: if (cursorpuesto) {
                              XSetForeground(xwindisplay,t->hdc,damecolorlinux(antcol.papel));
                              XSetBackground(xwindisplay,t->hdc,damecolorlinux(antcol.tinta));
                            } else {
                              XSetForeground(xwindisplay,t->hdc,damecolorlinux(antcol.tinta));
                              XSetBackground(xwindisplay,t->hdc,damecolorlinux(antcol.papel));
                            }
                           pintatexto(xwindisplay,hwnd->win,t->hdc, (x-t->origenx)*t->anchofont,(y+1-t->origeny)*t->altofont,&t->texto[x+y*t->columnas].ch,1);
                      break;
       }
    //printf("pintado cursor en %d %d\n",x,y);
}

void presentacursor(HWND hwnd)
{
    llpresentacursor(hwnd,0);
}

static long trataexpose(HWND hwnd,XExposeEvent *ev)
{
  int fil,col,pcol;
  char buffer[MAXCADENA],*ptrbuff;
  colventanas antcol;
  extrawins *t=dameextrawin(hwnd);
  if (hwnd->sinx == 1) return (0);
  XSetErrorHandler(trataxerror);
//  printf("Repintando desde fila %d a %d columna %d a %d\n",t->origeny,t->lineas,t->origenx,t->columnas);
  for (fil=t->origeny;fil<t->lineas;fil++) {
      pcol=t->origenx;
      antcol=t->texto[pcol+fil*t->columnas].c;
      ptrbuff=buffer;
      for (col=t->origenx;col<t->columnas;col++) {
          if (antcol.tinta!=t->texto[col+fil*t->columnas].c.tinta ||antcol.papel!=t->texto[col+fil*t->columnas].c.papel ) {
             *ptrbuff=0;
             XSetForeground(xwindisplay,t->hdc,damecolorlinux(antcol.tinta));
             XSetBackground(xwindisplay,t->hdc,damecolorlinux(antcol.papel));
             if (memcmp(&antcol,&COLORTRANSP,sizeof(colventanas))==0) {
                if (t->hbitmap) {
                    XCopyArea(xwindisplay,t->hbitmap,hwnd->win,t->hdc,(pcol-t->origenx)*t->anchofont,(fil+1-t->origeny)*t->altofont,t->anchofont,t->altofont,(pcol-t->origenx)*t->anchofont,(fil-t->origeny)*t->altofont);
                } else {
                   XSetForeground(xwindisplay,t->hdc,damecolorlinux(TINTANOBMP));
                   XSetBackground(xwindisplay,t->hdc,damecolorlinux(PAPELNOBMP));
                   memset(buffer,' ',(unsigned)(ptrbuff-buffer));
                   pintatexto(xwindisplay,hwnd->win,t->hdc, (pcol-t->origenx)*t->anchofont,(fil+1-t->origeny)*t->altofont,buffer,(unsigned)(ptrbuff-buffer));
                 }
              } else {
                pintatexto(xwindisplay,hwnd->win,t->hdc, (pcol-t->origenx)*t->anchofont,(fil+1-t->origeny)*t->altofont,buffer,(unsigned)(ptrbuff-buffer));
              }
             antcol=t->texto[col+fil*t->columnas].c;
             pcol=col;
             ptrbuff=buffer;
           }
          *ptrbuff++=t->texto[col+fil*t->columnas].ch;
       }
      XSetForeground(xwindisplay,t->hdc,damecolorlinux(antcol.tinta));
      XSetBackground(xwindisplay,t->hdc,damecolorlinux(antcol.papel));
      if (memcmp(&antcol,&COLORTRANSP,sizeof(colventanas))==0) {
         if (t->hbitmap) {
            XCopyArea(xwindisplay,t->hbitmap,hwnd->win,t->hdc,(pcol-t->origenx)*t->anchofont,(fil+1-t->origeny)*t->altofont,t->anchofont,t->altofont,(pcol-t->origenx)*t->anchofont,(fil-t->origeny)*t->altofont);
          } else {
            XSetForeground(xwindisplay,t->hdc,damecolorlinux(TINTANOBMP));
            XSetBackground(xwindisplay,t->hdc,damecolorlinux(PAPELNOBMP));
            memset(buffer,' ',(unsigned)(ptrbuff-buffer));
            pintatexto(xwindisplay,hwnd->win,t->hdc, (pcol-t->origenx)*t->anchofont,(fil+1-t->origeny)*t->altofont,buffer,(unsigned)(ptrbuff-buffer));
          }
       } else {
         pintatexto(xwindisplay,hwnd->win,t->hdc, (pcol-t->origenx)*t->anchofont,(fil+1-t->origeny)*t->altofont,buffer,(unsigned)(ptrbuff-buffer));
       }
   }
//  printf("Terminado de repintar\n");
  llpresentacursor(hwnd,1);
  return(0);
}

void trataotroevento(XEvent *report)
{
//        XNextEvent(xwindisplay, &report);
    if (dameventana(report->xany.window)==NULL) return;
//    printf("Recibido evento %d dato %p\n",report->type,wdata);
    switch (report->type) {
        case Expose: //printf("Recibido Expose\n");
                     trataexpose(dameventana(report->xany.window),&report->xexpose);
            break;
        case ConfigureNotify:
            break;
        default:
            /* All events selected by StructureNotifyMask
            * except ConfigureNotify are thrown away here,
            * since nothing is done with them */
            break;
        } /* End switch */

}


extrawins *dameextrawin(HWND hwnd)
{
    extrawins *ret;
    ret=hwnd->t;
    return(ret);
}

static void finitx(void)
{
    char *display_name = NULL;
    XInitThreads();
    if ( (xwindisplay=XOpenDisplay(display_name)) == NULL )
    {
        (void) fprintf( stderr, "cannot connect to X server %s\n",
                         XDisplayName(display_name));
        exit(0);
    }
    /* Get screen size from xwindisplay structure macro */
    screen_num = DefaultScreen(xwindisplay);
/*	if (!XMatchVisualInfo(xwindisplay, screen_num, 32, TrueColor, &vinfo)) {
		printf("no 24 bit visual en init\n");
		exit(1);
	}*/
    cmap= XDefaultColormap(xwindisplay,screen_num);
    XSetErrorHandler(trataxerror);

    initx=1;
}

static void initapp(HINSTANCE hinst)
{
 /* WNDCLASSEX	wc;
  wc.cbSize=sizeof(WNDCLASSEX);
  wc.style           = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
  wc.lpfnWndProc     = (WNDPROC)textproc;
  wc.cbClsExtra      = 0;
  wc.cbWndExtra      = sizeof(void *);
  wc.hInstance       = hinst;
  wc.hIcon           = LoadIcon(hinst,MAKEINTRESOURCE(101));
  wc.hIconSm         = LoadIcon(hinst,MAKEINTRESOURCE(101));
  wc.hCursor         = LoadCursor(NULL,IDC_ARROW);
  wc.hbrBackground   = GetStockObject(WHITE_BRUSH);
  wc.lpszMenuName    =NULL;
  wc.lpszClassName   ="V10TEXTO";
  RegisterClassEx(&wc);*/
}

static extrawins *creaextrawin(HWND hwnd,textparams *param)
{
  extrawins *t;
  int i,j;
  XGCValues valuegc;
  Atom texto;
  char *fontname = "fixed";
  t=calloc(1,sizeof(extrawins));
  t->lineas = param->numlin;
  t->columnas = param->numcol;
  t->texto = calloc(sizeof(tpixels), t->columnas*t->lineas);
  t->colordefecto = 0x11;
  hwnd->t=t;
  for (i = 0; i < t->columnas; i++) for (j = 0; j < t->lineas; j++) t->texto[j*t->columnas + i].ch = ' ';
  t->altofont = 7;t->anchofont = 7;
  if (hwnd->sinx == 1) return (t);
  texto=XInternAtom(xwindisplay,"TEXTOV10",0);
  XChangeProperty(xwindisplay, hwnd->win, texto, texto, 32, PropModeReplace, (unsigned char *)&t, 2);
  //printf("Valor de la ventana %p atomo %d\n",t,(int)texto);
  t->hdc=XCreateGC(xwindisplay, hwnd->win, 0, &valuegc);
  t->lfo= XLoadQueryFont(xwindisplay,fontname);
  XSetFont(xwindisplay,t->hdc, t->lfo->fid);
  t->altofont = t->lfo->max_bounds.ascent + t->lfo->max_bounds.descent;
  t->anchofont=t->lfo->max_bounds.width;
  return(t);
}

HWND initprgex(HINSTANCE hinst,int cmdshow,char *titulo,int posx,int posy,
             int tamx,int tamy,
             int numcol,int numlin,DWORD estilo,DWORD estiloex,HWND padre,
             int anchofont,int altofont,char *font)
{
  HWND hmain;
  textparams t;
  t.numcol=numcol;
  t.numlin=numlin;
  t.altofont=altofont;
  t.anchofont=anchofont;
  t.font=font;
  hmain=nuevaventana();
  if (singrafico == 0) if (initx == 0) finitx();
	if (hmain->sinx == 0) {
		hmain->win = XCreateWindow(xwindisplay,
		                           RootWindow(xwindisplay, screen_num),
		                           posx,
		                           posy,
		                           numcol*7,
		                           numlin*12,
		                           1,
		                           CopyFromParent,
		                           CopyFromParent,
		                           CopyFromParent,
		                           0,
		                           NULL);
	}
	creaextrawin(hmain, &t);
	if (hmain->sinx == 1) return (hmain);
  XSelectInput(xwindisplay, hmain->win, INPUTMASK);
  SetWindowText(hmain,titulo);
  XMapWindow(xwindisplay,hmain->win);
  XSetErrorHandler(trataxerror);
  return(hmain);
}

HWND initprg(HINSTANCE hinst,int cmdshow,char *titulo,int posx,int posy,
             int tamx,int tamy,
             int numcol,int numlin,DWORD estilo,HWND padre,
             int anchofont,int altofont,char *font)
{
  return(initprgex(hinst,cmdshow,titulo,posx,posy,tamx,tamy,numcol,numlin,
                   estilo,0,padre,anchofont,altofont,font));
}

static void finapptxt(void)
{
    XDestroyWindowEvent evento={DestroyNotify,0,1,xwindisplay,hwnddefecto->win,hwnddefecto->win};
    if (hwnddefecto) {
       if (hwnddefecto->sinx ==0) XSendEvent(xwindisplay,hwnddefecto->win,0,0,(XEvent *)&evento);
     }
}

void initapptxt(HINSTANCE hinst, HINSTANCE hprev,int cmdshow,char *titulo,
                int posx,int posy,int tamx,int tamy,int numcol,int numlin,
                DWORD estilo,DWORD estiloex,HWND padre,int anchofont,int altofont,
                char *nombrefont)
{
  if (hprev==NULL) {
      initapp(hinst);
    }
  hwnddefecto=initprgex(hinst,cmdshow,titulo,posx,posy,tamx,tamy,numcol,numlin,
                     estilo,estiloex,padre,anchofont,altofont,nombrefont);
	tratasigtermina();
  atexit(finapptxt);
}

void initv10lib(HINSTANCE hinst,HINSTANCE hprev)
{
    v10hinst=hinst;
    v10hprev=hprev;
#undef atexit
    atexit((void *)ejecutaexit);
    initapptxt(hinst,hprev,MODOSHOW,TITULOVENTANA,CW_USEDEFAULT,CW_USEDEFAULT,
        0,0,COLUMNASPANTALLA,LINEASPANTALLA,ESTILOV10,0,0,0,0,NULL);
}


