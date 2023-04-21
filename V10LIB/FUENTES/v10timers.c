/*
* Módulo : V10TIMERS
* Objeto:  Timers estandar de v10
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"

#define MAXTIMER 50

static v10timers *v10timer;
static int ntimers;

static void liberatimer(int i)
{
  v10timers *lt;
  lt=v10timer+i;
  free(lt->nombre);
  if (i<ntimers-1) memcpy(v10timer+i,v10timer+i+1,sizeof(v10timers)*(ntimers-i-1));
  ntimers--;
}

static void fintimer(void)
{
  while (ntimers) {
      liberatimer(0);
    }
  free(v10timer);
}

static void inittimer(void)
{
  v10timer=calloc(MAXTIMER,sizeof(v10timers));
  atexit(fintimer);
}

static int buscatimer(char *nombre)
{
  int i;
  if (v10timer==NULL) inittimer();
  for (i=0;i<ntimers;i++) {
      v10timers *lt=v10timer+i;
      if (strcmp(nombre,lt->nombre)==0) return(i);
    }
  return(-1);
}

static void calculaproxtimer(v10timers *lt)
{
  v10horas hdia;
  hdia=a2cent("24:00:00");
  lt->proxfecha=lt->ultfecha;
  lt->proxhora=lt->ulthora+lt->intervalo;
  lt->proxfecha+=(int)(lt->proxhora/hdia);
  lt->proxhora=lt->proxhora-(int)(lt->proxhora/hdia);
}

static void disparatimer(v10timers *lt)
{
  lt->ultfecha=damedate();
  lt->ulthora=gettime();
  lt->triger(lt);
  calculaproxtimer(lt);
}

void declarav10timer(char *nombre,void (*triger)(v10timers *lt),double intervalo,int clase,void *dato)
{
  v10timers *lt;
  if (v10timer==NULL) inittimer();
  if (buscatimer(nombre)!=-1) final(("Timer %s ya declarado",nombre));
  if (ntimers>=MAXTIMER-1) final(("Demasiados timers"));
  lt=v10timer+ntimers;
  ntimers++;
  lt->nombre=strdup(nombre);
  lt->intervalo=intervalo;
  lt->triger=triger;
  lt->dato=dato;
  lt->clase=clase;
  disparatimer(lt);
}

void declarav10timernt(char *nombre,void (*triger)(v10timers *lt),double intervalo,int clase,void *dato)
{
  v10timers *lt;
  if (v10timer==NULL) inittimer();
  if (buscatimer(nombre)!=-1) final(("Timer %s ya declarado",nombre));
  if (ntimers>=MAXTIMER-1) final(("Demasiados timers"));
  lt=v10timer+ntimers;
  ntimers++;
  lt->nombre=strdup(nombre);
  lt->intervalo=intervalo;
  lt->triger=triger;
  lt->dato=dato;
  lt->clase=clase;
  lt->ulthora=gettime();
  lt->ultfecha=damedate();
  calculaproxtimer(lt);
}

void liberav10timer(char *nombre)
{
  int i;
  i=buscatimer(nombre);
  if (i==-1) final(("Timer no declarado %s ",nombre));
  liberatimer(i);
}

v10horas cambiaintervalotimer(char *nombre,v10horas intervalo)
{
  double antint;
  v10timers *lt;
  lt=v10timer+buscatimer(nombre);
  antint=lt->intervalo;
  lt->intervalo=intervalo;
  calculaproxtimer(lt);
  return(antint);
}

void resetuntimer(v10timers *lt)
{
  lt->ulthora=gettime();
  lt->ultfecha=damedate();
  calculaproxtimer(lt);
}

void resettimer(char *nombre)
{
  v10timers *lt;
  lt=v10timer+buscatimer(nombre);
  resetuntimer(lt);
}

void disparatimers(int clase)
{
  int i;
  v10dates hoy=damedate();
  v10horas  ahora=gettime();
  static int usado;
  if (usado) return;
  usado=1;
  if (v10timer==NULL) inittimer();
  for (i=0;i<ntimers;i++) {
      v10timers *lt=v10timer+i;
      if (clase!=lt->clase) continue;
      if (hoy>lt->proxfecha || (hoy==lt->proxfecha && ahora>=lt->proxhora)) {
         disparatimer(lt);
       }
    }
  usado=0;
}

void resettimers(int clase)
{
  int i;
  if (v10timer==NULL) inittimer();
  for (i=0;i<ntimers;i++) {
      v10timers *lt=v10timer+i;
      if (clase!=lt->clase) continue;
      resetuntimer(lt);
    }
}
