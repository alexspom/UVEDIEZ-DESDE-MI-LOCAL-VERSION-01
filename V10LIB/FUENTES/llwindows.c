/*
* Módulo : LLWINDOWS.C                                              
* Objeto:  Funciones genericas texto en ventanas windows
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#pragma warning(disable: 4267)
#include "v10.h"


char v10marco[6][5]={"ÉÚÖÕ","»¿·¸","ÈÀÓÔ","¼Ù½¾","º³º³","ÍÄÄÍ"};


fontmensajes fontmensaje={20,10,"Terminal"};


void liberaventana(windows *w)
{
    if (w->hwnd!=hwnddefecto)  DestroyWindow(w->hwnd);
    else                       recuperavd(w,w->debajo);
}

void creaventana(char *titulo,windows *w,int x1,int y1,int x2,int y2,char *color)
{
  HWND hwnd;
  RECT rect;
  extrawins *t=dameextrawin(hwnddefecto);
  if (MODOSERVICIO) {
     winitvn(hwnddefecto,w,x1,y1,x2,y2,color);
     w->debajo=salvavd(w);
     enmarca(w,0,titulo);
  } else {
      GetWindowRect(hwnddefecto,&rect);
      if (rect.left<0) {
          rect.right-=rect.left;
          rect.left=0;
      }
      if (rect.top<0) {
          rect.bottom-=rect.top;
          rect.top=0;
      }
      x1+=rect.left/t->anchofont;
      x2+=rect.left/t->anchofont;
      y1+=rect.top/t->altofont;
      y2+=rect.top/t->altofont;
      titulo=v10translate(titulo);
      hwnd=initprgex(v10hinst,1,titulo,t->anchofont*x1,t->altofont*y1,(fontmensaje.ancho+3)*(x2-x1+1),
          (fontmensaje.alto+3)*(y2-y1+1),x2-x1+1,y2-y1+1,(WS_OVERLAPPED|WS_CAPTION|WS_THICKFRAME),
          0,
          hwnddefecto,-fontmensaje.ancho,-fontmensaje.alto,fontmensaje.font);
      winitvn(hwnd,w,0,0,x2-x1,y2-y1,color);
      clv(w);
  }
}

#ifndef __LINUX__
void wset_cursor(HWND hwnd,int modo)
{
  extrawins *t=dameextrawin(hwnd);
  t->modocursor=statuscursor=modo;
  if (hwnd==GetFocus()) {
      switch (t->modocursor) {
        case SINCURSOR:CreateCaret(hwnd,NULL,t->anchofont,0);
                      break;
        case CURSORNORMAL:CreateCaret(hwnd,NULL,t->anchofont,3);
                      break;
        case CURSORSOLIDO:CreateCaret(hwnd,NULL,t->anchofont,t->altofont);
                      break;
       }
      if (t->modocursor!=SINCURSOR) ShowCaret(hwnd);
      presentacursor(hwnd);
    }
}
#endif
void wcurr_cursor(HWND hwnd,int *x,int *y)
{
  extrawins *t=dameextrawin(hwnd);
  *x=t->cursorx;
  *y=t->cursory;
}

void wfgotoxy(HWND hwnd,int x,int y)
{
  extrawins *t=dameextrawin(hwnd);
  t->cursorx=x;
  t->cursory=y;
  presentacursor(hwnd);
}

void wcls(HWND hwnd,int x1,int y1,int x2,int y2,int color)
{
  int i,j;
  extrawins *t=dameextrawin(hwnd);
  RECT r;
  tpixels tp={charblanco,{0,color}};
  if (y1<0 || y2>=t->lineas || x1<0 || x2>=t->columnas) {
     final(("Error al limpiar la ventana %d %d %d %d",x1,y1,x2,y2));
   }
  for (i=y1 ; i<=y2 ; i++) {
    for (j=x1 ; j<=x2 ; j++)
        t->texto[i*t->columnas+j]=tp;
  }
  r.left=(x1-t->origenx)*t->anchofont;
  r.right=(x2-t->origenx+1)*t->anchofont;
  r.top=(y1-t->origeny)*t->altofont;
  r.bottom=(y2-t->origeny+1)*t->altofont;
  InvalidateRect(hwnd,&r,0);
}

int wplotext(HWND hwnd, int x, int y, int ch, int tinta, int papel, int invalida, extrawins *t)
{
  RECT r;
  tpixels val;
  if ((y>=0)&&(y<t->lineas)&&(x>=0)&&(x<t->columnas)) {
     val.ch=pasacharoem(ch);
     val.c.tinta=tinta;
     val.c.papel=papel;
     if (memcmp(t->texto+y*t->columnas+x,&val,sizeof(tpixels))) {
        t->texto[y*t->columnas+x]=val;
            if (invalida) {
        r.left=(x-t->origenx)*t->anchofont;
        r.right=(x-t->origenx+1)*t->anchofont;
        r.top=(y-t->origeny)*t->altofont;
        r.bottom=(y-t->origeny+1)*t->altofont;
        InvalidateRect(hwnd,&r,0);
      }
            return(1);
        }
	} else {
      if (MODODEBUG) warning(("Haciendo plot en posicion incorrecta %d %d",x,y));
   }
    return(0);
}
void wplot(HWND hwnd, int x, int y, int ch, int tinta, int papel)
{
  extrawins *t=dameextrawin(hwnd);
    wplotext(hwnd, x, y, ch, tinta, papel, 1,t);
}

int wscreen(HWND hwnd,int x ,int y)
{
  extrawins *t=dameextrawin(hwnd);
  if ((y>=0)&&(y<t->lineas)&&(x>=0)&&(x<t->columnas)) {
     return(t->texto[y*t->columnas+x].ch);
   } else {
     final(("Screen con coordenadas incorrectas %d %d",x,y));
   }
  return(0);
}

char *wimprime(HWND hwnd,int x,int y,int tinta,int papel,char *cadena)
{
  char *retu = cadena;
  int modificado = 0,inicio=x;
  RECT r;
  extrawins *t = dameextrawin(hwnd);
  while (*cadena!='\0') {
      if (wplotext(hwnd, x, y, *cadena, tinta, papel, 0,t)) modificado = 1;
    x++;
    cadena++;
  }
  if (modificado) {
      r.left = (inicio - t->origenx)*t->anchofont;
      r.right = (x - t->origenx + 1)*t->anchofont;
      r.top = (y - t->origeny)*t->altofont;
      r.bottom = (y - t->origeny + 1)*t->altofont;
      InvalidateRect(hwnd, &r, 0);
  }
  return(retu);
}

char *wimprimep(HWND hwnd,int x,int y,int tinta,int papel,char *cadena,int desde,int numchars)
{
  if ((desde >= 0) && (desde < strlen(cadena))) {
    if (strlen(cadena+desde)<=numchars)
      wimprime(hwnd,x,y,tinta,papel,cadena+desde);
    else {
      char *aux=strdup(cadena);
      aux[desde+numchars]=0;
      wimprime(hwnd,x,y,tinta,papel,aux+desde);
      free(aux);
    }
  }
  return(cadena);
}

void whorizontal(HWND hwnd,int x,int y,int l,int tinta,int papel,int tipo)
{
  int i;
  extrawins *t=dameextrawin(hwnd);
  if ((tipo >= 0) && (tipo < (strlen(v10marco[BARRAHOR])))) {
     if ((y>=0) && (y<t->lineas)) {
        if (x<0) {
           l=l+x;
           x=0;
         }
        if (x+l >= t->columnas) l=t->columnas-x;
        for (i=0;i<l;i++)
            wplot(hwnd,x+i,y,pasaoemchar(v10marco[BARRAHOR][tipo]),tinta,papel);
     }
  }
}

void wvertical(HWND hwnd,int x,int y,int l,int tinta,int papel,int tipo)
{
  int i;
  extrawins *t=dameextrawin(hwnd);
  if ((tipo >= 0) && (tipo < (strlen(v10marco[BARRAVER])))) {
    if ((x>=0) && (x<t->columnas)) {
       if (y<0) {
          l=l+y;
          y=0;
        }
       if (y+l >= t->lineas) l=t->lineas-y;
       for (i=0;i<l;i++)
           wplot(hwnd,x,y+i,pasaoemchar(v10marco[BARRAVER][tipo]),tinta,papel);
     }
  }
}

void wscrollu(HWND hwnd,int numlin,int x1,int y1,int x2,int y2,int papel)
{
  int i,j,lon;
  extrawins *t=dameextrawin(hwnd);
  RECT r;
  if (x1<0 || x2>=t->columnas || y1<0 || y2>=t->lineas) {
     final(("Error en scroll hacia arriba"));
   }
  if (numlin==0) numlin=y2-y1+1;
  if (numlin>y2-y1+1) numlin=y2-y1+1;
  lon=(x2-x1+1)*sizeof(tpixels);
  for (i=y1+numlin ; i<=y2 ; i++) {
      memmove(&t->texto[(i-numlin)*t->columnas+x1],&t->texto[i*t->columnas+x1],lon);
    }
  for (j=0 ; j<numlin ; j++)
      for (i=x1 ; i<=x2 ; i++) {
          t->texto[(y2-j)*t->columnas+i].c.papel=papel;
          t->texto[(y2-j)*t->columnas+i].ch=charblanco;
      }
  r.left=(x1-t->origenx)*t->anchofont;
  r.right=(x2-t->origenx+1)*t->anchofont;
  r.top=(y1-t->origeny)*t->altofont;
  r.bottom=(y2-t->origeny+1)*t->altofont;
  InvalidateRect(hwnd,&r,0);
}

void wscrolld(HWND hwnd,int numlin,int x1,int y1,int x2,int y2,int color)
{
  int i,j,lon;
  extrawins *t=dameextrawin(hwnd);
  RECT r;
  if (x1<0 || x2>=t->columnas || y1<0 || y2>=t->lineas) {
     final(("Error en scroll derecha"));
   }
  if (numlin==0) numlin=y2-y1+1;
  if (numlin>y2-y1+1) numlin=y2-y1+1;
  lon=(x2-x1+1)*sizeof(tpixels);
  for (i=y2-numlin ; i>=y1 ; i--) {
      memmove(&t->texto[(i+numlin)*t->columnas+x1],&t->texto[i*t->columnas+x1],lon);
    }
  for (j=0 ; j<numlin ; j++)
      for (i=x1 ; i<=x2 ; i++)
        wplot(hwnd,i,y1+j,charblanco,0,color);
  r.left=(x1-t->origenx)*t->anchofont;
  r.right=(x2-t->origenx+1)*t->anchofont;
  r.top=(y1-t->origeny)*t->altofont;
  r.bottom=(y2-t->origeny+1)*t->altofont;
  InvalidateRect(hwnd,&r,0);
}

void wscrollr(HWND hwnd,int numcol,int x1,int y1,int x2,int y2,int color)
{
  int fuente;
  int i,j,longitud;
  extrawins *t=dameextrawin(hwnd);
  if (x1<0 || x2>=t->columnas || y1<0 || y2>=t->lineas) {
     final(("Scroll incorrecto"));
   }
  if (numcol==0) numcol=x2-x1+1;
  if (numcol>x2-x1+1) numcol=x2-x1+1;
  fuente=x1+numcol;
  longitud=(x2-x1-numcol+1)*sizeof(tpixels);
  for (i=y1;i<=y2;i++) {
      memmove(&t->texto[i*t->columnas+x1],&t->texto[i*t->columnas+fuente],longitud);
      for(j=x2-numcol+1 ; j<=x2 ; j++)
        wplot(hwnd,j,i,charblanco,0,color);
    }
}

void wscrolll(HWND hwnd,int numcol,int x1,int y1,int x2,int y2,int color)
{
  int fuente;
  int i,j,longitud;
  extrawins *t=dameextrawin(hwnd);
  if (x1<0 || x2>=t->columnas || y1<0 || y2>=t->lineas) {
     final(("Error en scroll izquierda"));
   }
  if (numcol==0) numcol=x2-x1+1;
  if (numcol>x2-x1+1) numcol=x2-x1+1;
  fuente=x1+numcol;
  longitud=(x2-x1-numcol+1)*sizeof(tpixels);
  for (i=y1 ; i<=y2 ; i++) {
      memmove(&t->texto[i*t->columnas+fuente],&t->texto[i*t->columnas+x1],longitud);
      for(j=x1 ; j<=x1+numcol-1 ; j++)
        wplot(hwnd,j,i,charblanco,0,color);
    }
}

void wmarco(HWND hwnd,int x1,int y1,int base,int altura,int tipo,int tmarco,int pmarco,int ttitulo,int ptitulo,char *titulo)
{
  titulo=v10translate(titulo);
  if ((tipo >= 0) && (tipo < (strlen(v10marco[BARRAHOR]))) && (tipo < (strlen(v10marco[BARRAVER])))) {
    wplot(hwnd,x1,y1,pasaoemchar(v10marco[SUPIZQ][tipo]),tmarco,pmarco);
    wplot(hwnd,x1+base-1,y1,pasaoemchar(v10marco[SUPDER][tipo]),tmarco,pmarco);
    wplot(hwnd,x1,y1+altura-1,pasaoemchar(v10marco[INFIZQ][tipo]),tmarco,pmarco);
    wplot(hwnd,x1+base-1,y1+altura-1,pasaoemchar(v10marco[INFDER][tipo]),tmarco,pmarco);
    whorizontal(hwnd,x1+1,y1,base-2,tmarco,pmarco,tipo);
    whorizontal(hwnd,x1+1,y1+altura-1,base-2,tmarco,pmarco,tipo);
    wvertical(hwnd,x1,y1+1,altura-2,tmarco,pmarco,tipo);
    wvertical(hwnd,x1+base-1,y1+1,altura-2,tmarco,pmarco,tipo);
    if (*titulo) {
      int x2,y2;
      if (base>=strlen(titulo)) {
         y2=y1;
         x2=x1+(base-strlen(titulo))/2-1;
         if (centrar_titulo) {
            if (x2>=x1) wplot(hwnd,x2++,y2,' ',ttitulo,ptitulo);
	            else x2=x1;
            wimprime(hwnd,x2,y2,ttitulo,ptitulo,titulo);
            x2+=strlen(titulo);
            wplot(hwnd,x2,y2,' ',ttitulo,ptitulo);
          } else wimprime(hwnd,x1+1,y2,ttitulo,ptitulo,titulo);
       }
    }
  }
}

void wsalvapantalla(HWND hwnd,void *p,int x1,int y1,int x2,int y2)
{
  int i,lon;
  extrawins *t=dameextrawin(hwnd);
  if (x1<0 || x2>=t->columnas || y1<0 || y2>=t->lineas) {
     final(("Coordenadas incorrectas para salvapantalla %d %d %d %d",x1,x2,y1,y2));
   }
  lon=(x2-x1+1)*sizeof(tpixels);
  for (i=y1 ; i<=y2 ; i++) {
      memmove(p,&(t->texto[i*t->columnas+x1]),lon);
      p=(void *)((char *)p+lon);
   }
}

void *wsalvapantallad(HWND hwnd,int x1,int y1,int x2,int y2)
{
  void *donde;
  extrawins *t=dameextrawin(hwnd);
  if (x1<0) x1=0;
  if (y1<0) y1=0;
  if (x2>=t->columnas) x2=t->columnas-1;
  if (y2>=t->lineas) y2=t->lineas-1;
  donde=calloc(x2-x1+1,(y2-y1+1)*sizeof(tpixels));
  wsalvapantalla(hwnd,donde,x1,y1,x2,y2);
  return(donde);
}

void wrecuperapantalla(HWND hwnd,void *p,int x1,int y1,int x2,int y2)
{
  int i,lon;
  RECT r;
  extrawins *t=dameextrawin(hwnd);
  if (x1<0 || x2>=t->columnas || y1<0 || y2>=t->lineas) {
     final(("Coordenadas incorrectas en recuperapantalla %d %d %d %d",x1,x2,y1,y2));
   }
  lon=(x2-x1+1)*sizeof(tpixels);
  for (i=y1;i<=y2;i++) {
      memmove(t->texto+i*t->columnas+x1,p,lon);
      p=(void *)(((char *)p)+lon);
  }
  r.left=(x1-t->origenx)*t->anchofont;
  r.right=(x2-t->origenx+1)*t->anchofont;
  r.top=(y1-t->origeny)*t->altofont;
  r.bottom=(y2-t->origeny+1)*t->altofont;
  InvalidateRect(hwnd,&r,0);
} 

void wrecuperapantallaansi(HWND hwnd,void *p,int x1,int y1,int x2,int y2)
{
  int i,j,lon;
  RECT r;
  int modificado = 0;
  extrawins *t=dameextrawin(hwnd);
  if (x1<0 || x2>=t->columnas || y1<0 || y2>=t->lineas) {
     final(("Coordenadas incorrectas en recuperapantalla %d %d %d %d",x1,x2,y1,y2));
   }
  lon=(x2-x1+1)*sizeof(tpixels);
  for (i=y1;i<=y2;i++) {
      for (j=x1;j<=x2;j++) {
          tpixels *tw=((tpixels *)p)+(i-y1)*lon+j-x1;
          if (wplotext(hwnd, j, i, tw->ch, tw->c.tinta, tw->c.papel, 0,t)) modificado = 1;
      }
  }
  r.left=(x1-t->origenx)*t->anchofont;
  r.right=(x2-t->origenx+1)*t->anchofont;
  r.top=(y1-t->origeny)*t->altofont;
  r.bottom=(y2-t->origeny+1)*t->altofont;
  if (modificado) InvalidateRect(hwnd,&r,0);
} 

void wrecuperapantallad(HWND hwnd,int x1,int y1,int x2,int y2,void *donde)
{
  extrawins *t=dameextrawin(hwnd);
  if (x1<0) x1=0;
  if (y1<0) y1=0;
  if (x2>=t->columnas) x2=t->columnas-1;
  if (y2>=t->lineas) y2=t->lineas-1;
  wrecuperapantalla(hwnd,donde,x1,y1,x2,y2);
  free(donde);
}


teclamenus arrteclamenu[MAXTECLAMENU];
int nteclamenu;

static void finteclamenu(void)
{
    int i;
    for (i=0;i<nteclamenu;i++) if (arrteclamenu[i].nombre) free(arrteclamenu[i].nombre);
}

void declarateclamenu(char *nombre,int mitecla)
{
    int i;
    if (nteclamenu==0) atexit(finteclamenu);
    for (i=0;i<nteclamenu;i++) {
        if (arrteclamenu[i].tecla==mitecla) {
            free(arrteclamenu[i].nombre);
            arrteclamenu[i].nombre=strdup(nombre);
            return;
        }
    }
    arrteclamenu[i].nombre=strdup(nombre);
    arrteclamenu[i].tecla=mitecla;
    nteclamenu++;
}