/*
* Módulo : EOSHL.C
* Objeto: Rutinas de alto nivel de la ethernetbox sistema EOS
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-12-2007

* MODIFICACIONES
* --
*/
#include "eospc.h"

int tipoidentdisp=TIPOIDNUMDISP;
int numetherbox;
//int maxnivellog=LOGPROGRESO;

int MODIFICADOINFO;

void miescribelog(int nivel,char *format,...)
{
  va_list arg;    
  if (maxnivellog<nivel) return;
  va_start(arg,format);
#ifdef __WIN32__
  vv10log(nivel,format,arg);
#else
	printf ("%s/%s:", ordenador, puerto);
  vprintf(format,arg);
#endif
}

static void inithleth(int i,char *tarj,int tciclo,int tenvtrama,int timeouttrama,int timeoutwho,int limitacionlinea)
{
  strcpy(eth[i].dirip,tarj);
  initeth(eth+i,tciclo,tenvtrama,timeouttrama,timeoutwho,limitacionlinea);
}

int vinitinfopickex(int tciclo,int tenvtrama,int timeouttrama,int timeoutwho,int limitacionlinea,char *tarj1,va_list arg)
{
  int i;
  i=0;
  inithleth(i,tarj1,tciclo,tenvtrama,timeouttrama,timeoutwho,limitacionlinea);
  while ((tarj1=va_arg(arg,char *))!=NULL) {
        if (es_blanco(tarj1)) break;
        i++;
        inithleth(i,tarj1,tciclo,tenvtrama,timeouttrama,timeoutwho,limitacionlinea);
    }
  numetherbox=i+1;
  MODIFICADOINFO++;
  return(i);
}

int initinfopickex(int tciclo,int tenvtrama,int timeouttrama,int timeoutwho,int limitacionlinea,char *tarj1,...)
{
  va_list arg;
  va_start(arg,tarj1);
  return(vinitinfopickex(tciclo,tenvtrama,timeouttrama,timeoutwho,limitacionlinea,tarj1,arg));
}

int initinfopick(char *tarj1,...)
{
  va_list arg; 
  va_start(arg,tarj1);
  return(vinitinfopickex(TCICLO,TENVTRAMA,TIMEOUTTRAMA,TIMEOUTWHO,LIMITACIONLINEA,tarj1,arg));
}  

int numdispeth(etherboxs *peth)
{
  int j,ret=0;
  for (j=0;j<MAXLINEAS;j++) ret+=peth->lin[j].numdisp;
  return(ret);
}

int numdisp(void)
{
  int i,ret=0;
  for (i=0;i<numetherbox;i++) {
      ret+=numdispeth(eth+i);
   }
  return(ret);
}

void tickhleth(void)
{
  int i;
  for (i=0;i<numetherbox;i++) ticketh(eth+i);
}


int vdisplayprintf(long iddisplay,char *format,va_list arg)
{
  return(vdisplayprintfid(tipoidentdisp,iddisplay,format,arg));
}

int displayprintf(long iddisplay,char *format,...)
{
  int ret;
  va_list arg;
  va_start(arg,format);
  ret=vdisplayprintf(iddisplay,format,arg);
  va_end(arg);
  return(ret);
}

void lucesdisplay(long iddisplay,int numluz,int valor)
{
   lucesdisplayid(tipoidentdisp,iddisplay,numluz,valor);
}

void togglelucesdisplay(long iddisplay,int numluz)
{
   togglelucesdisplayid(tipoidentdisp,iddisplay,numluz);
}

int statusdisplay(long iddisplay)
{
   return(statusdisplayid(tipoidentdisp,iddisplay));
}

void encolatecladisp(long iddisplay,int boton,int causa)
{
   encolatecladispid(tipoidentdisp,iddisplay,boton,causa);
}


