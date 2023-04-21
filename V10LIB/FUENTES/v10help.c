/*
* Módulo : V10HELP.C
* Objeto:  Llamadas estandar a la help de windows
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"

#define MAXHELP  200

char file_help[MAXPATH];

typedef struct {
          char *file;
          char *texto;
        } v10helps;
static v10helps sv10help[MAXHELP];
static int nhelps;

#define LINEASONLINE 2

static int v10ponayudafile(char *file,char *texto)
{
  if (nhelps>=MAXHELP-1) {
     v10log(LOGERROR,v10translate("Superado el numero maximo de ayuda %d"),MAXHELP);
     return(-1);
   }
  sv10help[nhelps].file=strdup(file);
  sv10help[nhelps++].texto=strdup(texto);
  return(0);
}

void v10help(void)
{
  if (nhelps) {
     v10helps *ayu=sv10help+nhelps-1;
     WinHelp(hwnddefecto,ayu->file,HELP_KEY,(DWORD)ayu->texto);
   }
}

void v10quitaayuda(void)
{
  if (nhelps) {
     nhelps--;
     free(sv10help[nhelps].file);
     free(sv10help[nhelps].texto);
   }
}

int v10ponayuda(char *texto)
{
  return(v10ponayudafile(file_help,texto));
}

#define MAXONLINE 100
static tpixels *wonline[MAXONLINE];
static int numonline;

static int damelononline(char *p)
{
	int ret=0;
	while (*p) {
		if (*p==cr || *p==lf) break;
		if (*p!='{' && *p!='}') ret++;
		p++;
	}
	return(ret);
}

static void centraonline(char *p)
{
	unsigned lon;
	while (*p) {
		while (*p==' ') strcpy(p,p+1);
	    lon=damelononline(p);
		if (lon<COLUMNASPANTALLA-1) {
			char blancos[MAXCADENA];
			strfill(blancos,' ',(COLUMNASPANTALLA-lon)/2);
			strins(p,blancos);
		}
		p=strchr(p,lf);
		if (p==NULL) break;
		p++;
	}
}


void pintaonline(char *cadena)
{
  int nl=LINEASONLINE;
  windows w;
  char *p,dest[MAXCADENA];
  strcpy(dest,v10translate(cadena));
  initvn(&w,0,LINEASPANTALLA-nl,COLUMNASPANTALLA-1,LINEASPANTALLA-1,"ONLINE");
  free(wonline[numonline]);
  wonline[numonline++]=salvavdm(&w,0);
  clv(&w);
  p=dest;
  centraonline(p);
  while (*p) {
        switch (*p) {
          case '{':poncolorv(&w,CINPUTINAC);
                   break;
          case '}':poncolorv(&w,CNORMAL);
                   break;
          default: v10printf(&w,"%c",*p);
                  break;
        }
        p++;
     }
}

void borraonline(void)
{
  int nl=LINEASONLINE;
  windows w;
  if (numonline<=0) return;
  numonline--;
  if (wonline[numonline]==NULL) return;
  initvn(&w,0,LINEASPANTALLA-nl,COLUMNASPANTALLA-1,LINEASPANTALLA-1,"ONLINE");
  recuperavdm(&w,wonline[numonline],0);
  wonline[numonline]=NULL;
}