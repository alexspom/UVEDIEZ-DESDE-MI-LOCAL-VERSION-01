#include "infopc.h"
#include "vdinfopicking.h"

etherboxs eth[MAXETHER];

tecladisps tecdisp[MAXTECLAS];
int numteclasdisp;

displays *damedisplayid(long iddisplay)
{
  displays *pdisp;
  int neth, nlin, ndisp;
  dimedatosdisp(iddisplay, &neth, &nlin, &ndisp);
  return(eth[neth].lin[nlin].disp + ndisp - 1);
}


int vdisplayprintfp(displays *p,char *format,va_list arg)
{
  char cadena[MAXCADENA];
  int ret;
  ret=vsprintf(cadena,format,arg);
  if (strcmp(p->valor,cadena)) {
     strcopia(p->valor,cadena,sizeof(p->valor)-1);
     if (p->luces[1]==0) p->luces[1]=1;
     p->modificado=1;
     MODIFICADOINFO++;
   }
  return(ret);
}

int displayprintfp(displays *p,char *format,...)
{
  int ret;
  va_list arg;
  va_start(arg,format);
  ret=vdisplayprintfp(p,format,arg);
  va_end(arg);
  return(ret);
}

int vdisplayprintfid(long iddisplay,char *format,va_list arg)
{
  displays *pdisp;
  int ret;
  pdisp=damedisplayid(iddisplay);
  if (pdisp==NULL) {
     v10log(LOGERROR,"Intentando escribir en display 0\n");
     return(0);
   }
  ret=vdisplayprintfp(pdisp,format,arg);
  return(ret);
}

int displayprintfid(long iddisplay,char *format,...)
{
  int ret;
  va_list arg;
  va_start(arg,format);
  ret=vdisplayprintfid(iddisplay,format,arg);
  va_end(arg);
  return(ret);
}

void lucesdisplayp(displays *p,int numluz,int valor)
{
  if (p->luces[numluz]!=(unsigned short) valor) {
     p->luces[numluz]=(unsigned short)valor;
     p->modificado=1;
     MODIFICADOINFO++;
   }
}

void togglelucesdisplayp(displays *p,int numluz)
{
  p->luces[numluz]=(short)(p->luces[numluz]?0:3);
  p->modificado=1;
  MODIFICADOINFO++;
}

void lucesdisplayid(long iddisplay,int numluz,int valor)
{
   displays *pdisp;
   pdisp=damedisplayid(iddisplay);
   if (pdisp==NULL) {
      v10log(LOGERROR,"Intentando escribir en display 0\n");
      return;
    }
   lucesdisplayp(pdisp,numluz,valor);
}

void togglelucesdisplayid(long iddisplay,int numluz)
{
   displays *pdisp;
   pdisp=damedisplayid(iddisplay);
   if (pdisp==NULL) {
      v10log(LOGERROR,"Intentando escribir en display 0\n");
      return;
    }
   togglelucesdisplayp(pdisp,numluz);
}

/*int statusdisplayp(displays *p)
{
   return(p->status[0]);
}

int statusdisplayid(long iddisplay)
{
   displays *pdisp;
   pdisp=damedisplayid(iddisplay);
   if (pdisp==NULL) {
      escribe_err("Intentando escribir en display 0\n");
      return(0);
    }
   return(statusdisplayp(pdisp));
}
*/

void encolatecladispp(displays *p,int boton,int causa)
{
  if (numteclasdisp>=MAXTECLAS-1) return;
  tecdisp[numteclasdisp].numdisp=p->numdisp;
  tecdisp[numteclasdisp].serie=p->serie;
  tecdisp[numteclasdisp].boton=boton;
  tecdisp[numteclasdisp].causa=causa;
  tecdisp[numteclasdisp].version=p->version;
  numteclasdisp++;
}

/*
void encolatecladispid(long iddisplay,int boton,int causa)
{
   displays *pdisp;
   pdisp=damedisplayid(iddisplay);
   if (pdisp==NULL) {
      escribe_err("Intentando escribir en display 0\n");
      return;
    }
   encolatecladispp(pdisp,boton,causa);
}*/

int haytecladisp(void)
{
	int neth, nlin, ndisp;
	if (numteclasdisp) return(numteclasdisp);
	for (neth = 0; neth < numetherbox; neth++) {
		for (nlin = 0; nlin < MAXLINEAS; nlin++) {
			for (ndisp = 0; ndisp < MAXDISPLAYS; ndisp++) {
				displays *pdisp = eth[neth].lin[nlin].disp+ndisp;
				if (pdisp->modifstatus) return(1);
			}
		}
	}
	return(0);
}

int tecladisp(tecladisps *tec)
{
	if (numteclasdisp == 0) {
		int neth, nlin, ndisp;
		if (numteclasdisp) return(numteclasdisp);
		for (neth = 0; neth < numetherbox; neth++) {
			for (nlin = 0; nlin < MAXLINEAS; nlin++) {
				for (ndisp = 0; ndisp < MAXDISPLAYS; ndisp++) {
					displays *pdisp = eth[neth].lin[nlin].disp + ndisp;
					if (pdisp->modifstatus) {
						tec->boton = TESTADOBOT;
						tec->causa = pdisp->status[0];
						tec->numdisp = pdisp->numdisp;
						tec->serie = pdisp->serie;
						tec->version = pdisp->version;
						pdisp->modifstatus = 0;
						return(1);
					}
				}
			}
		}
		return(0);
	}
	*tec=tecdisp[0];
	memcpy(tecdisp,tecdisp+1,(numteclasdisp-1)*sizeof(tecladisps));
	numteclasdisp--;
	return(1);
}


