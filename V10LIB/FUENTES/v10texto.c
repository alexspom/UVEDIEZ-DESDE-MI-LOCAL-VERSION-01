/*
* Módulo : V10TEXTO.C                                            
* Objeto:  Ventanas de texto
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"



// Definicion de colores puros

#define COLORNEGRO 0x00000000
#define COLORAZUL  0x007f0000
#define COLORVERDE 0x00007f00
#define COLORROJO  0x0000007f


defvents defvent[MAXVENT]={
    //                0               1                    2                      3                     4                        5
    //                         6                       7                    8                       9                      10
    {"DEFECTO",   {{{0,0},{0x0000ffff,COLORAZUL},{0x00ffff00,COLORVERDE},{0x0000ffff,COLORROJO},{0x0000afaf,0x00003f00},{0x00ffffff,COLORROJO},
                    {0x0000ffff,COLORAZUL},{0x00ffffff,COLORAZUL},{COLORAZUL,0x007f7f7f},{COLORAZUL,0x007f7f7f},{0x0000FFFF,COLORVERDE},
                    {0x0000FFFF,COLORVERDE+COLORAZUL},{0x0000FFFF,COLORVERDE},{0x0000FFFF,COLORVERDE},{0x0000FFFF,COLORVERDE+COLORAZUL},{0x0000FFFF,COLORVERDE+COLORAZUL}}}},
    {"COLORES",   {{0,0x1e,0x1B,0x4e,0x4f,0x1e,0x1f,0x71,0x71}}},
    {"AYUDA",     {{0,0x17,0x1a,0x21,0x1F,0x1F,0x70,0x71,0x71}}},
    {"ONLINE",    {{{0,0},{0x0000ffff,COLORAZUL},{0x00ffff00,COLORAZUL},{0x0000ffff,COLORROJO},{0x0000ffff,COLORROJO},{0x00ffffff,COLORROJO},
                    {0x0000ffff,COLORAZUL},{0x00ffffff,COLORAZUL},{COLORAZUL,0x007f7f7f},{COLORAZUL,0x007f7f7f}}}},
    {"MENUS",     {{{0,0},{COLORAZUL,0x007F7F7F},{COLORNEGRO,0X007F7F7F},{COLORNEGRO,0x007f7f00},{COLORNEGRO,0x007f7f00},{COLORROJO,0x007f7f7F },
                    {COLORNEGRO,0x007f7f7f},{COLORNEGRO,0X007F7F00},{COLORNEGRO,0X007F7F7F},{0X007F7F7F,COLORNEGRO},{0X007F7F7F,COLORNEGRO}}}},
    {"ERROR",     {{{0,0},{0x0000ffff,COLORROJO},{0x0000ffff,COLORAZUL},{0x0000ffff,COLORROJO},{0x0000ffff,COLORROJO},{0x00ffffff,COLORROJO},
                    {0x0000ffff,COLORROJO},{0x00ffff00,COLORAZUL},{0x00ffff00,COLORAZUL},{0x00ffff00,COLORAZUL}}}},
    {"MENSAJES",  {{{0,0},{0x0000ffff,COLORROJO},{0x0000ffff,COLORAZUL},{0x0000ffff,COLORAZUL},{0x0000ffff,COLORROJO},{0x00ffffff,COLORROJO},
                    {0x0000ffff,COLORROJO},{0x00ffff00,COLORAZUL},{0x00ffff00,COLORAZUL},{0x00ffff00,COLORAZUL}}}},
    {"TOOLTIP",   {{{0,0},{0x00000000,0x0000ffff},{0x00ffff00,COLORVERDE},{0x0000ffff,COLORROJO},{0x00007f7f,0x00003f00},{0x00ffffff,COLORROJO},
                    {0x0000ffff,COLORAZUL},{0x00ffffff,COLORAZUL},{COLORAZUL,0x007f7f7f},{COLORAZUL,0x007f7f7f},{0x0000FFFF,COLORVERDE},
                    {0x0000FFFF,COLORVERDE},{0x0000FFFF,COLORVERDE}}}}
  };

int damepaleta(char *nombre)
{
  int i=0,def=0;

  while (strcmp(nombre,defvent[i].nombre) && (i<MAXVENT)) {
		if (strcmp(defvent[i].nombre,"DEFECTO")==0) def=i;
	    i++;
  }
  if (i==MAXVENT) i=def;
  return(i);
}

void initvt(windows *v,int x1,int y1,int x2,int y2,paletas *t)
{
  v->x1=x1;
  v->x2=x2;
  v->y1=y1;
  v->y2=y2;
  v->t=*t;
  v->mododebug=WTTY;
  v->cursorx=0;
  v->cursory=0;
  poncolorv(v,CNORMAL);
  v->hwnd=hwnddefecto;
}


void initvf(windows *v,int x1,int y1,int x2,int y2,int numero)
{
  if (numero>MAXVENT) numero=0;
  initvt(v,x1,y1,x2,y2,&(defvent[numero].t));
}


void initvn(windows *v,int x1,int y1,int x2,int y2,char *nombre)
{
  int i=damepaleta(nombre);
  initvf(v,x1,y1,x2,y2,i);
}

void winitvt(HWND hwnd,windows *v,int x1,int y1,int x2,int y2,paletas *t)
{
  initvt(v,x1,y1,x2,y2,t);
  v->hwnd=hwnd;
}

void winitvn(HWND hwnd,windows *v,int x1,int y1,int x2,int y2,char *nombre)
{
  initvn(v,x1,y1,x2,y2,nombre);
  v->hwnd=hwnd;
}

void usa_colores(char *nom_fichero)
{
  FILE *fichero;
  char aux[MAXPATH];

  strcpy(aux,nom_fichero);
  strcat(aux,".col");
  fichero=fopenpath(aux,"rb");
  if (fichero==NULL) return;
  fread(defvent,MAXVENT,sizeof(defvents),fichero);
  fclose(fichero);
}


void salva_colores(char *nom_fichero)
{
  FILE *fichero;
  char aux[64];

  strcpy(aux,nom_fichero);
  strcat(aux,".col");
  if ((fichero=fopenpath(aux,"r+b"))==NULL)
    fichero=fopenseguro(aux,"wb");
  fwrite(defvent,MAXVENT,sizeof(defvents),fichero);
  fclose(fichero);
}


void clv(windows *v)
{
  wcls(v->hwnd,v->x1,v->y1,v->x2,v->y2,v->t.t[0].papel);
  v->cursorx=0;
  v->cursory=0;
}


static void codesp(windows *v,int ch)
{
  switch(v->mododebug) {
    case 1: escribe(v,'^');
            escribe(v,ch+64);
            break;
    case 2:
    case 3: switch(ch) {
              case back: if (v->cursorx) v->cursorx--;break;
              case  tab: do {
                           escribe(v,' ');
                         } while ((v->cursorx%8) && (v->cursorx<WANCHO(v)-1));
                         break;
              case lf: v->cursory++;
                       if (v->cursory+v->y1>v->y2) {
                          v->cursory--;
                          scrollv(v,1);
                        }
                       if (v->mododebug==3) v->cursorx=0;
                       break;
              case cr: v->cursorx=0;
                       break;
              default: escribe(v,'^');
                       escribe(v,ch+64);
                       break;
              }
	    break;
     case 4:switch(ch) {
              case lf: v->cursory++;
                       if (v->cursory+v->y1>v->y2) {
                          v->cursory--;
                          scrollv(v,1);
                         }
              case cr: v->cursorx=0;
                       break;
              default: {int antmododebug;
                        antmododebug=v->mododebug;
                        v->mododebug=0;
                        escribe(v,ch);
                        v->mododebug=antmododebug;
                        break;
                       }
              }
	    break;
  }
}


int escribeext(windows *v, int ch, int invalida,extrawins *t)
{
  int cursorx,cursory;
    int modificado;
  if (v->mododebug)
    if (ch<' ') {
      codesp(v,ch);
            return 0;
    }
  cursorx=v->cursorx+v->x1;
  cursory=v->cursory+v->y1;
  if (cursorx>v->x2)  {
    cursory++;
    cursorx=v->x1;
    if (cursory>v->y2) {
      cursory--;
      scrollv(v,1);
    }
  }
    modificado=wplotext(v->hwnd, cursorx, cursory, ch, v->t.t[0].tinta, v->t.t[0].papel,invalida,t);
  cursorx++;
  v->cursorx=cursorx-v->x1;
  v->cursory=cursory-v->y1;
    return modificado;
}

void escribe(windows *v, int ch)
{
    extrawins *t = dameextrawin(v->hwnd);
    escribeext(v, ch, 1, t);
}

void escribec(windows *v,char *cadena)
{
    extrawins *t = dameextrawin(v->hwnd);
    RECT r;
    int minx=COLUMNASPANTALLA, miny=LINEASPANTALLA,maxx=0,maxy=0, modificado = 0;
    minx = v->cursorx; miny = v->cursory;
  char destino[MAXCADENA],*pdestino=destino;
  if (v10usaansi) v10ansitooem(cadena,destino);
     else strcpy(destino,cadena);
     while (*pdestino) {
         if (maxx < v->cursorx) maxx = v->cursorx;
         if (minx > v->cursorx) minx = v->cursorx;
         if (maxy < v->cursory) maxy = v->cursory;
         if (miny > v->cursorx) miny = v->cursorx;
         if (escribeext(v, *pdestino++, 0, t)) modificado = 1;
     }
    if (modificado) {
        r.left = (minx+v->x1 - t->origenx)*t->anchofont;
        r.right = (maxx + v->x1 - t->origenx + 1)*t->anchofont;
        r.top = (miny + v->y1 - t->origeny)*t->altofont;
        r.bottom = (maxy + v->y1 - t->origeny + 1)*t->altofont;
        InvalidateRect(v->hwnd, &r, 0);
    }
} 

int vv10printf(windows *v,char *format,va_list arg)
{
  char aux[MAXCADENA];
  int ret;

  vsprintf(aux,format,arg);
  escribec(v,aux);
  ret=strlen(aux);
  return(ret);
}

int v10printf(windows *v,char *format,...)
{
  va_list arg;

  va_start(arg,format);
  return(vv10printf(v,format,arg));
}

char *imprimevp(windows *v,int x,int y,char *cadena,int desde,int numchars)
{
  int lon;
  colventanas tp=v->t.t[0];
  char destino[MAXCADENA];

  lon=v->x2-v->x1+1;
  if (v10usaansi) v10ansitooem(cadena,destino);
     else strcpy(destino,cadena);
  if (x+numchars>lon)
    return(wimprimep(v->hwnd,v->x1+x,v->y1+y,tp.tinta,tp.papel,destino,desde,lon-x));
  else
    return(wimprimep(v->hwnd,v->x1+x,v->y1+y,tp.tinta,tp.papel,destino,desde,numchars));
}

char *imprimev(windows *v,int x,int y,char *cadena)
{
  return(imprimevp(v,x,y,cadena,0,strlen(cadena)));
}


void renmarca(windows *v,int tipo,char *titulo)
{
  colventanas tmarco,ttitulo;
  if (tipo==0) {
      tmarco=v->t.t[CMARCOR];
      ttitulo=v->t.t[CMARCOR];
  } else {
      tmarco=v->t.t[CMARCON];
      ttitulo=v->t.t[CMARCON];
  }
  wmarco(v->hwnd,v->x1-1,v->y1-1,v->x2-v->x1+3,v->y2-v->y1+3,tipo,tmarco.tinta,tmarco.papel,ttitulo.tinta,ttitulo.papel,titulo);
}


void enmarca(windows *v,int tipo,char *titulo)
{
  renmarca(v,tipo,titulo);
  clv(v);
}


void scrollv(windows *v,int numlin)
{
  if (numlin>=0) wscrollu(v->hwnd,numlin,v->x1,v->y1,v->x2,v->y2,v->t.t[0].papel);
  else wscrolld(v->hwnd,-numlin,v->x1,v->y1,v->x2,v->y2,v->t.t[0].papel);
}


void scrollh(windows *v,int numcol)
{
  if (numcol>=0) wscrollr(v->hwnd,numcol,v->x1,v->y1,v->x2,v->y2,v->t.t[0].papel);
  else wscrolll(v->hwnd,-numcol,v->x1,v->y1,v->x2,v->y2,v->t.t[0].papel);
}


void salvav(windows *v,void *donde)
{
  int x1 = v->x1-1;
  int x2 = v->x2+1;
  int y1 = v->y1-1;
  int y2 = v->y2+1;
  extrawins *t=dameextrawin(v->hwnd);
  if (x1<0) x1=0;
  if (y1<0) y1=0;
  if (x2>=t->columnas) x2=t->columnas-1;
  if (y2>=t->lineas) y2=t->lineas-1;
  wsalvapantalla(v->hwnd,donde,x1,y1,x2,y2);
}


void *salvavdm(windows *v,int marco)
{
  tpixels *donde;
  int x1 = v->x1-marco;
  int x2 = v->x2+marco;
  int y1 = v->y1-marco;
  int y2 = v->y2+marco;
  extrawins *t=dameextrawin(v->hwnd);
  if (x1<0) x1=0;
  if (y1<0) y1=0;
  if (x2>=t->columnas) x2=t->columnas-1;
  if (y2>=t->lineas) y2=t->lineas-1;
  donde=calloc(x2-x1+1,(y2-y1+1)*sizeof(tpixels));
  wsalvapantalla(v->hwnd,donde,x1,y1,x2,y2);
  return(donde);
}

void *salvavd(windows *w)
{
    return(salvavdm(w,1));
}

void recuperavm(windows *v,void *donde,int marco)
{
  int x1 = v->x1-marco;
  int x2 = v->x2+marco;
  int y1 = v->y1-marco;
  int y2 = v->y2+marco;
  extrawins *t=dameextrawin(v->hwnd);
  if (x1<0) x1=0;
  if (y1<0) y1=0;
  if (x2>=t->columnas) x2=t->columnas-1;
  if (y2>=t->lineas) y2=t->lineas-1;
  wrecuperapantalla(v->hwnd,donde,x1,y1,x2,y2);
}

void recuperav(windows *v,void *donde)
{
    recuperavm(v,donde,1);
}

void recuperavdm(windows *v,void *donde,int marco)
{
  recuperavm(v,donde,marco);
  free(donde);
}



void recuperavd(windows *v,void *donde)
{
  recuperavdm(v,donde,1);
}


void pon_curf(windows *v)
{
  wfgotoxy(v->hwnd,v->cursorx + v->x1 , v->cursory + v->y1);
}


void pon_curv(windows *v,int cursorx,int cursory)
{
  v->cursorx=cursorx;
  v->cursory=cursory;
}


void pos_curv(windows *v,int *cursorx,int *cursory)
{
  *cursorx=v->cursorx;
  *cursory=v->cursory;
}


void poncolorv(windows *v,int color)
{
  v->t.t[0]=v->t.t[color];
}


void mensajev_color(windows *v,char *mensaje,int terminal)
{
  int y,x;

  y=v->y2+1;
  x=(v->x2+v->x1-strlen(mensaje))/2;
  if (*mensaje==0) {
    whorizontal(v->hwnd,v->x1,y,v->x2-v->x1,v->t.t[CMARCON].tinta,v->t.t[CMARCON].papel,0);
    return;
  }
  wplot(v->hwnd,x++,y,'Í',v->t.t[CMARCON].tinta,v->t.t[CMARCON].papel);
  while (*mensaje)
    wplot(v->hwnd,x++,y,*mensaje++,v->t.t[terminal].tinta,v->t.t[terminal].papel);
  wplot(v->hwnd,x++,y,'Í',v->t.t[CMARCON].tinta,v->t.t[CMARCON].papel);
}


void mensajev(windows *v,char *mensaje)
{
  mensajev_color(v,mensaje,CTITULON);
}


void flechas(windows *v,long ini_limite,long fin_limite,long ini,long fin,short tipo_marco,short color)
{
  if (ini>ini_limite) wplot(v->hwnd,v->x2+1,v->y1,'\x1E',v->t.t[color].tinta,v->t.t[color].papel);
  else wplot(v->hwnd,v->x2+1,v->y1,pasaoemchar(v10marco[BARRAVER][tipo_marco]),v->t.t[CMARCON].tinta,v->t.t[CMARCON].papel);

  if (fin<fin_limite) wplot(v->hwnd,v->x2+1,v->y2,'\x1F',v->t.t[color].tinta,v->t.t[color].papel);
  else wplot(v->hwnd,v->x2+1,v->y2,pasaoemchar(v10marco[BARRAVER][tipo_marco]),v->t.t[CMARCON].tinta,v->t.t[CMARCON].papel);
}



