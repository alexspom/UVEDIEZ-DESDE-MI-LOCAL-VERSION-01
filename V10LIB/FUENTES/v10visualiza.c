/*
* Módulo : V10VISUALIZA.C
* Objeto:  Permite mandar pantallas texto o logs por un socket
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"

static servidorsocks *serlog,*serpantalla;

void mandalog(char *str)
{
    listasocks *p;
    if (serlog==NULL) return;
    EnterCriticalSection(&serlog->critopen);
    p=serlog->listaopen;
    while (p) {
        v10sockencolac(p->valor,str);
        if (p->next==serlog->listaopen) break;
        p=p->next;
    }
    LeaveCriticalSection(&serlog->critopen);
}

static void finserverlog(void)
{
  if (serlog) v10sockcierraservidor(serlog);
  serlog=NULL;
}

servidorsocks *arrancaserverlog(char *puerto)
{
    serlog=v10socknuevoservidor(puerto,1,NULL,NULL,NULL,NULL,NULL);
    if (serlog==NULL) {
       v10log(LOGDEBUG,"No puedo abrir socket %s\n",puerto);
       return NULL;
     }
    ponfnlog(mandalog);
    atexit(finserverlog);
    return(serlog);
}

static void mandapantalla(v10socks *p,int op,int lon,char *buffer)
{
    int ch;
    extrawins *t=dameextrawin(hwnddefecto);
    ch=buffer[0];
    if (lon>1) ch=ch+(buffer[1]<<8);
    if (ch!=0) STDencolatecla(ch);
    v10sockencola(p,t->columnas);
    v10sockencola(p,t->lineas);
    v10sockescribe(p,(char *)t->texto,t->lineas*t->columnas*sizeof(tpixels));
}                

static void finserverpantalla(void)
{
  if (serpantalla) v10sockcierraservidor(serpantalla);
  serpantalla=NULL;
}


servidorsocks *arrancaserverpantalla(char *puerto)
{
    serpantalla=v10socknuevoservidor(puerto,1,NULL,NULL,mandapantalla,NULL,NULL);
    if (serpantalla==NULL) {
       v10log(LOGDEBUG,"No puedo abrir socket %s\n",puerto);
       return NULL;
     }
    atexit(finserverpantalla);
    return(serpantalla);
}

