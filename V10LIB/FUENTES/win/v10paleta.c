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
#include "../v10.h"



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


