/*
* Módulo : WINSIMU.C
* Objeto:  Simula en windows las funciones bajo nivel DOS
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"


static void (*anttrigervivo)(void);

#ifndef __LINUX__
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
#endif
void set_cursor(int modo)
{
  wset_cursor(hwnddefecto,modo);
}

void curr_cursor(int *x,int *y)
{
   wcurr_cursor(hwnddefecto,x,y);
}

void STDfgotoxy(int x,int y)
{
  wfgotoxy(hwnddefecto,x,y);
}

void cls(int x1,int y1,int x2,int y2,int color)
{
  wcls(hwnddefecto,x1,y1,x2,y2,color);
}

void plot(int x,int y,int ch,int tinta,int papel)
{
  wplot(hwnddefecto,x,y,ch,tinta,papel);
}

int screen(int x ,int y)
{
  return(wscreen(hwnddefecto,x,y));
}

char *imprime(int x,int y,int tinta,int papel,char *cadena)
{
  return(wimprime(hwnddefecto,x,y,tinta,papel,cadena));
}

char *imprimep(int x,int y,int tinta,int papel,char *cadena,int desde,int numchars)
{
  return(wimprimep(hwnddefecto,x,y,tinta,papel,cadena,desde,numchars));
}

void horizontal(int x,int y,int l,int tinta,int papel,int tipo)
{
  whorizontal(hwnddefecto,x,y,l,tinta,papel,tipo);
}

void vertical(int x,int y,int l,int tinta,int papel,int tipo)
{
  wvertical(hwnddefecto,x,y,l,tinta,papel,tipo);
}

void scrollu(int numlin,int x1,int y1,int x2,int y2,int color)
{
  wscrollu(hwnddefecto,numlin,x1,y1,x2,y2,color);
}

void scrolld(int numlin,int x1,int y1,int x2,int y2,int color)
{
  wscrolld(hwnddefecto,numlin,x1,y1,x2,y2,color);
}

void scrollr(int numcol,int x1,int y1,int x2,int y2,int color)
{
  wscrollr(hwnddefecto,numcol,x1,y1,x2,y2,color);
}

void scrolll(int numcol,int x1,int y1,int x2,int y2,int color)
{
  wscrolll(hwnddefecto,numcol,x1,y1,x2,y2,color);
}

void marco(int x1,int y1,int base,int altura,int tipo,int tmarco,int pmarco,int ttitulo,int ptitulo,char *titulo)
{
  wmarco(hwnddefecto,x1,y1,base,altura,tipo,tmarco,pmarco,ttitulo,ptitulo,titulo);
}

void salvapantalla(void *p,int x1,int y1,int x2,int y2)
{
  wsalvapantalla(hwnddefecto,p,x1,y1,x2,y2);
}

void *salvapantallad(int x1,int y1,int x2,int y2)
{
  return(wsalvapantallad(hwnddefecto,x1,y1,x2,y2));
}

void recuperapantalla(void *p,int x1,int y1,int x2,int y2)
{
  wrecuperapantalla(hwnddefecto,p,x1,y1,x2,y2);
}

void recuperapantallaansi(void *p,int x1,int y1,int x2,int y2)
{
  wrecuperapantallaansi(hwnddefecto,p,x1,y1,x2,y2);
}

void recuperapantallad(int x1,int y1,int x2,int y2,void *donde)
{
  wrecuperapantallad(hwnddefecto,x1,y1,x2,y2,donde);
}

static void trigervivo(void)
{
  char hora[10];
  static v10horas anthora;
  if (gettime()!=anthora) {
     anthora=gettime();
     cent2a(gettime(),0,':',hora);
     strcat(hora," ");
     imprime(COLUMNASPANTALLA-9,0,0x0000ffff,0x0000007f,hora);
   }
  if (anttrigervivo) anttrigervivo();
}

void pintapantallav10(char *cadena)
{
  char micadena[MAXPATH];
  strcpy(micadena,cadena);
  pad(micadena,COLUMNASPANTALLA-1);
  imprimep(0,0,0x0000ffff,0x0000007f,micadena,0,COLUMNASPANTALLA);
  trigervivo();
  anttrigervivo=dametrigervivo();
  pontrigervivo(trigervivo);
  damedate();
}
