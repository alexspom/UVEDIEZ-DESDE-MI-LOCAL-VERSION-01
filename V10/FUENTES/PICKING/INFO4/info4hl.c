#include "infopc.h"

int numetherbox;

int MODIFICADOINFO;

/*void miescribelog(int nivel,char *format,...)
{
  va_list arg;
  va_start(arg,format);
#ifdef WIN32
  vescribe_log(nivel,format,arg);
#else
	printf ("%s/%s:", ordenador, puerto);
    vprintf(format,arg);
#endif
}*/

static void inithleth(int i,char *tarj,int tciclo,int tenvtrama,int timeouttrama,int timeoutwho,int limitacionlinea,char *rangolineas)
{
  strcpy(eth[i].dirip,tarj);
  initeth(eth+i,tciclo,tenvtrama,timeouttrama,timeoutwho,limitacionlinea,rangolineas);
}

int initinfopick(int tciclo,int tenvtrama,int timeouttrama,int timeoutwho,int limitacionlinea,char *rangolineas,char *tarj1,...)
{
  va_list arg;
  int i;
  i=0;
  inithleth(i,tarj1,tciclo,tenvtrama,timeouttrama,timeoutwho,limitacionlinea,rangolineas);
  va_start(arg,tarj1);
  while ((tarj1=va_arg(arg,char *))!=NULL) {
        if (es_blanco(tarj1)) break;
        i++;
        inithleth(i, tarj1, tciclo, tenvtrama, timeouttrama, timeoutwho, limitacionlinea, rangolineas);
    }
  numetherbox=i+1;
  MODIFICADOINFO++;
  return(i);
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
  refrescalineas();
}


int vdisplayprintf(long iddisplay,char *format,va_list arg)
{
  return(vdisplayprintfid(iddisplay,format,arg));
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
   lucesdisplayid(iddisplay,numluz,valor);
}

/*void togglelucesdisplay(long iddisplay,int numluz)
{
   togglelucesdisplayid(iddisplay,numluz);
}

int statusdisplay(long iddisplay)
{
   return(statusdisplayid(iddisplay));
}

void encolatecladisp(long iddisplay,int boton,int causa)
{
   encolatecladispid(iddisplay,boton,causa);
}*/


