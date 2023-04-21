/*****************************************************************
*																 *
* Módulo:  Infopick.c											 *
* Función: Manejo de displays a alto nivel						 *
*																 *	
*																 *
* Autor: Francisco J. Guerrero									 *
* Fecha: 29-1-2010												 *
*																 *	
******************************************************************/

#include "info3.h"
#include <process.h>

infopicks infopick;
char send_conf;

void infograbaconfig(void)
{
  int i;
  for (i=0;i<infopick.numcards;i++) {
      infotsios *t=infopick.t[i];
      infotgrabaconfig(t);
  }
  send_conf=0;
}

int datosdisp(int disp,int *tarjeta,int *linea,int *ndisp)
{
  int nt,nr;
  if (infotconfig.tipodir==0) {
	  for (nt=0;nt<infopick.numcards;nt++) {
		  infotsios *t=infopick.t[nt];
		  for (nr=0;nr<t->numred;nr++) {
			  infotreddisps *r=infopick.t[nt]->r+nr;
			  if (disp>=r->numdisp) {
				  disp-=r->numdisp;
				  continue;
			  }
			  *linea=nr;
			  *tarjeta=nt;
			  *ndisp=disp;
			  return(0);
		  }
	  }
  } else {
	  *tarjeta=disp/100000;
	  *linea=(disp%100000)/1000;
      *ndisp=disp%1000;
	  if (*tarjeta>=infopick.numcards) {
		  v10log(LOGERROR,"Numero de tarjeta muy alto %d\n",*tarjeta);
		  return(-1);
	  }
	  if (*linea>=infopick.t[*tarjeta]->numred) {
		  v10log(LOGERROR,"Numero de red muy alto tarjeta %d red %d\n",*tarjeta,*linea);
		  return(-1);
	  }
	  if (*ndisp>=infopick.t[*tarjeta]->r[*linea].numdisp) {
		  v10log(LOGERROR,"Numero de display muy alto tarjeta %d red %d display %d\n",*tarjeta,*linea,*ndisp);
		  return(-1);
	  }
	  return(0);
  }
  return(-1);
}

int damedirtipo(int numdisp)
{
	int nt,nr,nd;
	if (infotconfig.tipodir==0) return numdisp;
	nd=0;
	for (nt=0;nt<infopick.numcards;nt++) {
		infotsios *t=infopick.t[nt];
		for (nr=0;nr<t->numred;nr++) {
			infotreddisps *r=t->r+nr;
			if (numdisp<nd+r->numdisp) return(nt*100000+nr*1000+numdisp-nd);
			nd+=r->numdisp;
		}
	}
	return(0);
}

void infowho(void)
{
  int i;
  for (i=0;i<infopick.numcards;i++) {
      infotsios *t=infopick.t[i];
      infotstop(t);
	  infotwho(t);
	  infotstop(t);
	  infotresetstats(t);
      infotstart(t);
  }
}


void inforeset(void)
{
  int i;
  IPsv4 tarjetas[MAXTARJ];
  
  for (i=0;i<MAXTARJ;i++) {
	  tarjetas[i]=NULL;
  }

  for (i=0;i<infopick.numcards;i++) {
      infotstop(infopick.t[i]);
      tarjetas[i]=strdup(infopick.t[i]->dir_IP);
	  infotreset(infopick.t[i]); 	
  }
  
  Sleep(infotconfig.espreset);
  for (i=0;i<infopick.numcards;i++) 
	infotstart(infopick.t[i]);
}


int infostatus(void)
{
  int nt,nr,nd;
  int valor;
  if (infopick.numcards==0) return(ERRNOINFO);
  for (nt=0;nt<infopick.numcards;nt++) { 
	  infotsios *t=infopick.t[nt];
	  for (nr=0;nr<t->numred;nr++) 
		  for (nd=0;nd<t->r[nr].numdisp;nd++) {
			  valor=infotstdisplay(t,nr,nd);
			  if ((valor & 0x20)==0)	return ERRTARJ+nt;
			  if ((valor & 0x10)==0)	return ERRLUZ;						 
			  if (valor &0xf)			return ERRBOTON;
		  }
  }
  return(0);
}


void infoinicializa(void)
{
  int nt,nr,nd,ndisp;
  for (ndisp=0;ndisp<infopick.numdisp;ndisp++) {
	  int dir=damedirtipo(ndisp);
	if (datosdisp(dir,&nt,&nr,&nd)) return;
	infotinicializa(infopick.t[nt],nr,nd);
  }
}

void infoimprime(int ndisp,char *cadena)
{
  int nt,nr,nd;
  if (datosdisp(ndisp,&nt,&nr,&nd)) return;
  infotimprime(infopick.t[nt],nr,nd,cadena);
}

void infovprintf(int ndisp,char *format,va_list arg)
{
  int nt,nr,nd;
  if (datosdisp(ndisp,&nt,&nr,&nd)) return;
  infotvprintf(infopick.t[nt],nr,nd,format,arg);
}

void infoprintf(int ndisp,char *format,...)
{
  va_list arg;
  va_start(arg,format);
  infovprintf(ndisp,format,arg);
  va_end(arg);
}


void infoponluz(int disp,int numluz,int valor)
{
  int nt,nr,nd;
  if (datosdisp(disp,&nt,&nr,&nd)) return;
  infotponluz(infopick.t[nt],nr,nd,numluz,valor);
}


int infostluz(int disp,int numluz)
{
  int nt,nr,nd;
  if (datosdisp(disp,&nt,&nr,&nd)) return(-1);
  return(infotstluz(infopick.t[nt],nr,nd,numluz));
}


void infotoggleluz(int disp,int numluz,int valor)
{
  int nt,nr,nd;
  if (datosdisp(disp,&nt,&nr,&nd)) return;
  infottoggleluz(infopick.t[nt],nr,nd,numluz,valor,NULL,0);
}


int infostdisplay(int disp)
{
  int nt,nr,nd;
  if (datosdisp(disp,&nt,&nr,&nd)) return(-1);
  return(infotstdisplay(infopick.t[nt],nr,nd));
}


infotdisplays *infodisplay(int ndisp)
{
  int nt,nr,nd;
  infotdisplays *ret;
  if (datosdisp(ndisp,&nt,&nr,&nd)) return(NULL);
  ret=infopick.t[nt]->r[nr].d+nd;
  return(ret);
}


infotdefdisps *infotipo(int disp)
{
  infotreddisps *r;
  int nt,nr,nd;
  if (datosdisp(disp,&nt,&nr,&nd)) return(NULL);
  r=infopick.t[nt]->r+nr;
  return(r->d[nd].tipo);
}


char *infovalor(int disp)
{
  int nt,nr,nd;
  if (datosdisp(disp,&nt,&nr,&nd)) return(NULL);
  return(infotvalor(infopick.t[nt],nr,nd));
}

void infoencolatecla(int disp,int boton,int causa)
{
  int nt,nr,nd;
  if (datosdisp(disp,&nt,&nr,&nd)) return;
  infotencolatecla(infopick.t[nt],nr,nd,boton,causa);
}

int infohaytecla(void)
{
  int i,ret=0;
  for (i=0;i<infopick.numcards;i++) {
	  ret+=infothaytecla(infopick.t[i]);
  }
  return(ret);
}


int infotecla(infotteclas *tec)
{
  int i,j;
  int nd=0,nl=0;
  for (i=0;i<infopick.numcards;i++) {
	  infotsios *t=infopick.t[i];
      if (infottecla(t,tec)) {
		  if (infotconfig.tipodir==0) {
             tec->disp+=nd;
             for (j=0;j<tec->linea;j++) tec->disp+=t->r[j].numdisp;
             tec->linea+=nl;
             return(1);
		  } else {
			  tec->disp=i*100000+tec->linea*1000+tec->disp;
			  return(1);
		  }
      }
	  nl+=t->numred;
      for (j=0;j<infopick.t[i]->numred;j++)
		nd+=t->r[j].numdisp;
  }
  return(0);
}


void infotratateclas(void)
{
  int i;
  for (i=0;i<infopick.numcards;i++) {
      infottratateclas(infopick.t[i]);
  }
}

int infonumdisp(void)
{
  int nt,nr;
  int ret=0;
  for (nt=0;nt<infopick.numcards;nt++) {
	  infotsios *t=infopick.t[nt];
      for (nr=0;nr<t->numred;nr++) {
          infotreddisps *r=t->r+nr;
          ret+=r->numdisp;
      }
  }
  return(ret);
}


int infonextboton(void)
{
  int antdisp=infopick.ultdisp;
  int nb;
  infotdisplays *d;
  do {
     infopick.ultdisp++;
     if (infopick.ultdisp>=infopick.numdisp) infopick.ultdisp=0;
     d=infodisplay(infopick.ultdisp);
     for (nb=0;nb<d->tipo->botones;nb++) {
         infotbotones *b=d->bot+nb;
         if (b->estado==INFOTBPULSADO) return(infopick.ultdisp);
     }
  } while (antdisp!=infopick.ultdisp);
  return(-1);
}


static void infoparpadea(int valor)
{
	int nt,nr,nd,nl;
	char cadena[MAXCADENA];
	int parpadea;

	for (nt=0;nt<infopick.numcards;nt++) {
		infotsios *t=infopick.t[nt];
		for (nr=0;nr<t->numred;nr++) {
			infotreddisps *r=t->r+nr;

			strcpy(cadena,"");
			parpadea=0;

			for (nd=0;nd<r->numdisp;nd++) {
				infotdisplays *d=r->d+nd;
				infotdefdisps *df=d->tipo;
				int dispparpa=0;
				for (nl=0;nl<df->luces;nl++) {
					if (infotstluz(t,nr,nd,nl)&2) {
						if (valor==0) infottoggleluz(t,nr,nd,nl,0,cadena,parpadea);
						else       infottoggleluz(t,nr,nd,nl,1,cadena,parpadea);
						dispparpa=1;
					}
				}
				if (dispparpa) {
					infottoggleluz(t,nr,nd,0,10,cadena,parpadea);
					parpadea++;
					if (parpadea>400) {
						infohsend(PARPADEO,r,parpadea*4,0,cadena);
						strcpy(cadena,"");
						parpadea=0;
					}
				}
			}

		  if (parpadea) 
			  infohsend(PARPADEO,r,parpadea*4,0,cadena);

	  }
   }
}

int infonexterror(void)
{
  int antdisp=infopick.ultdisp;
  int nb;
  infotdisplays *d;
  do {
     infopick.ultdisp++;
     if (infopick.ultdisp>=infopick.numdisp) infopick.ultdisp=0;
     d=infodisplay(infopick.ultdisp);
     for (nb=0;nb<d->tipo->botones;nb++) {
         infotbotones *b=d->bot+nb;
         if (b->estado==INFOTBPULSADO) return(infopick.ultdisp);
     }
  } while (antdisp!=infopick.ultdisp);
  return(-1);
}
                 

static void infoTCPIP(void)
{
  int nt,nr;
  for (nt=0;nt<infopick.numcards;nt++) {
	  infotsios *t=infopick.t[nt];
	  for (nr=0;nr<t->numred;nr++) {
			if (t->r[nr].numdisp)				
				infotTCPIP(t,t->r+nr,nr);				
	  }
  }
}


static void infoaskforstats(void)
{
  int nt,nr;
  if ((infotconfig.statsgap!=0) && (infopick.hultstats!=0) && (damecent()-infopick.hultstats)>infotconfig.statsgap) {
	  for (nt=0;nt<infopick.numcards;nt++) {
		  infotsios *t=infopick.t[nt];
		  for (nr=0;nr<t->numred;nr++)
			  if (t->r[nr].numdisp) {
				  infohsend(STATS,infopick.t[nt]->r+nr,0,0,NULL);
				  v10log(LOGNORMAL,"Solicitadas estadisticas tarjeta %s red %d\n",infopick.t[nt]->dir_IP,nr);
				  t->r[nr].stats_pend=damecent();
			  }
	  }
	infopick.hultstats=damecent();
  }
}

static void infothread(void *param)
{
  static int valor=0;
  while (infopick.tid!=INVALID_HANDLE_VALUE) {
		Sleep(infotconfig.espera);	
		infoTCPIP();	
		infotratateclas();
		if (valor==0 && damecent()-infotconfig.uparpad>infotconfig.tparpada) {
           infoparpadea(valor);
           valor=!valor;
           infotconfig.uparpad=damecent();
        }
        if (valor && damecent()-infotconfig.uparpad>infotconfig.tparpade) {
           infoparpadea(valor);
           valor=!valor;
           infotconfig.uparpad=damecent();
        }
		infoaskforstats();		
  }
  infopick.tid=0;
}

static void fininfopick(void)
{
  int i;
  if (infopick.tid) {
     infopick.tid=INVALID_HANDLE_VALUE;
     if (infopick.tid==INVALID_HANDLE_VALUE) Sleep(10);
  }
  for (i=0;i<infopick.numcards;i++) {
      infotlibera(infopick.t[i]);
	  infopick.t[i]=NULL;
  }
  infopick.numcards=0;
}

static int llinfoinit(int ninfo,IPsv4 tarjetas[])
{
   v10socks *pipe[MAXREDESTARJ];
   int pdisp=0;
   int i;
   infopick.numcards=0;
   memset(pipe,0,sizeof(pipe));
   for (i=0;i<MAXTARJ;i++){
	   int redes;
	   redes=infotconfig.puertos[i];
	   if (redes==0) redes=MAXREDESTARJ;
	   if (infotconfig.tarj[i]) {
		   int j,k;
		   for (j=0;j<redes;j++) {
			   char servicio[MAXPATH];
			   sprintf(servicio,"infopick%d",j+1);
			   pipe[j]=abrecliente(infotconfig.tarj[i],servicio);
			   if (pipe[j]==NULL) {
				   for (k=0;k<j;k++) {
					   v10socklibera(pipe[k]);
					   pipe[k]=NULL;
				   }
				   break;
			   }
		   }
		   if ((infopick.t[i]=infotidentifica(ninfo,infotconfig.tarj[i],redes,pipe,&pdisp))==NULL) {
			   v10log(LOGNORMAL, "Tarjeta %s no ha podido ser identificada\n",infotconfig.tarj[i]);
			   i--;
			   continue;
		   }		
		   infopick.numcards++;
	   } else return(infopick.numcards);
   }
   return(infopick.numcards);
}


void infoinit(int ninfo)
{
  int ret;
  infopick.hultstats=0;
  ret=llinfoinit(ninfo,infotconfig.tarj);
  if (ret>0) {
	 infopick.hultstats=damecent();
	 infopick.ultdisp=0; 
     infopick.numdisp=infonumdisp();
	 infoinicializa();
     atexit(fininfopick);
     infopick.tid=(HANDLE)_beginthread(infothread,0,NULL);
  }
}

void infoinit3(int ninfo,...)
{
  int ret;
  int numpar=0;
  char *dirip;
  va_list arg;
  va_start(arg,ninfo);
  while (!es_blanco(dirip=va_arg(arg,char *))) infotconfig.tarj[numpar++]=strdup(dirip);
  va_end(arg);
  infopick.hultstats=0;
  ret=llinfoinit(ninfo,infotconfig.tarj);
  if (ret>0) {
	 infopick.hultstats=damecent();
	 infopick.ultdisp=0; 
     infopick.numdisp=infonumdisp();
	 infoinicializa();
     atexit(fininfopick);
     infopick.tid=(HANDLE)_beginthread(infothread,0,NULL);
  }
}

