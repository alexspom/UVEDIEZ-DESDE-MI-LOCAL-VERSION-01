/*
* Módulo : V10DINAMICA.C                                              
* Objeto:  Depuracion de memoria dinamica
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>


#ifndef __LINUX__
#include <windows.h>
#include <windowsx.h>



#ifdef _V10WINDLL
  #define V10IMPORT __declspec(dllimport)
#else
  #define V10IMPORT __declspec( dllexport )
#endif
#else
#define MAXPATH     512
#include "linux/v10linux.h"
#endif
#include "v10aborta.h"
V10IMPORT int v10atexit(void (*fun)(void));
V10IMPORT char *(*v10translate)(char *);

static CRITICAL_SECTION critdin;

#define MAXBUCKET (1<<1)




typedef struct LISTA {
          char *file;
          int line;
          struct LISTA *sig,*ant;
          unsigned tam;
          char *funcion;
          long orden;
        } listas;

#define CHECKBYTE  0xaa


int DINAMICA_SEGURA = 1; /* Controla las acciones a tomar ante
                            un free() erroneo. Si vale 0 el programa
			                contin£a, en caso contrario el programa
			                aborta. */


static listas *raiz[MAXBUCKET];
static FILE *log_sal;
static int init_dinamica = 0;



static long   maxalloc,
				  actalloc,
				  totalloc,
				  maxbloque,
				  actbloque,
				  totalbloque;


V10IMPORT void v10free(void *ptr,char *file,int line);
static void escribe_estadistica(FILE *std_sal)
{
  listas  *i,*posible;
  double  kk;
  int j,haymem=1,minorden;

  log_sal=NULL;

  fprintf(std_sal,v10translate("Estad¡sticas:\n\n"));
  fprintf(std_sal,v10translate("M xima memoria instantanea pedida: %ld\n"),maxalloc);
  fprintf(std_sal,v10translate("Memoria pedida actualmente: %ld\n"),actalloc);
  fprintf(std_sal,v10translate("Memoria total pedida: %ld\n"),totalloc);
  fprintf(std_sal,v10translate("M ximo n£mero de bloques pedidos en un instante: %ld\n"),maxbloque);
  fprintf(std_sal,v10translate("N£mero de bloques pedidos actualmente: %ld\n"),actbloque);
  fprintf(std_sal,v10translate("N£mero total de bloques pedidos: %ld\n"),totalbloque);
  kk=totalloc/totalbloque;
  fprintf(std_sal,v10translate("Media de memoria por bloque: %7.2lf\n\n"),kk);
  fprintf(std_sal,v10translate("N§     FUNCION  FICHERO                          LINEA PUNTERO    TAMA¥O\n"));
  fprintf(std_sal,v10translate("ÍÍÍÍÍÍ ÍÍÍÍÍÍÍÍ ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ ÍÍÍÍÍ ÍÍÍÍÍÍÍÍÍ  ÍÍÍÍÍÍÍÍ\n"));

  while (haymem) {
     posible=NULL;
     minorden=totalbloque+1;
     haymem=0;
     for (j=0;j<MAXBUCKET;j++) {
         if (raiz[j]==NULL) continue;
         i=raiz[j];
         haymem=1;
         while (i) {
               if (i->orden<minorden) {
                  posible=i;
                  minorden=i->orden;
               }
               i=i->sig;
          }
      }
      if (haymem) {
         fprintf(std_sal,"%6ld %-8.8s %-32.32s %5u %p  %9u\n",posible->orden,posible->funcion,posible->file,posible->line,posible+1,posible->tam);
         v10free(posible+1,__FILE__,__LINE__);
      }
   }
  log_sal=std_sal;
}


V10IMPORT void imprime_dinamica(char *fich_out)
    /* Imprime las estadisticas sobre el programa compilado, as¡ como
       los bloques de memoria no liberados, si los hubiese, en el fichero
       "fich_out". */
{
  FILE *std_sal;

  std_sal=fopen(fich_out,"w");
  if (std_sal==NULL) return;
  escribe_estadistica(std_sal);
  fclose(std_sal);
}


static void al_salir(void)
    /* Acciones a realizar al acabar el programa. */
{
  char *entorno=NULL;

  if (log_sal) {
    fprintf(log_sal,"\n\n");
    escribe_estadistica(log_sal);
    fclose(log_sal);
  }
  entorno=getenv("STD");
  if (entorno) imprime_dinamica(entorno);
}


V10IMPORT void initdinamica(char *entorno)
    /* Inicializaci¢n del fichero de "log" seg£n la variable fich_dinamica. */
{
  if (init_dinamica) return;
  InitializeCriticalSection(&critdin);
  init_dinamica=1;
  if (entorno==NULL) entorno=getenv("DINAMICA");
  if (entorno!=NULL) {
    log_sal=fopen(entorno,"w");
    if (log_sal==NULL) return;
    fprintf(log_sal,v10translate("N§     FUNCION  FICHERO                          LINEA PUNTERO    TAMA¥O \n"));
    fprintf(log_sal,v10translate("ÍÍÍÍÍÍ ÍÍÍÍÍÍÍÍ ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ ÍÍÍÍÍ ÍÍÍÍÍÍÍÍÍ  ÍÍÍÍÍÍÍÍ\n"));
	 fflush(log_sal);
  } else log_sal=NULL;
  v10atexit(al_salir);
}

static void poncheckbyte(listas *ret)
{
  char *din;
  din=(char *)(ret+1);
  din[ret->tam]=CHECKBYTE;
}

static int checkbyte(listas *ret)
{
  char *din;
  din=(char *)(ret+1);
  if (din[ret->tam]==CHECKBYTE) return(0);
  return(1);
}


static void engancha_suma(listas *ret,unsigned size,char *funcion,char *file,int line)
{
  int bucket;
  bucket=(((size_t)ret)>>5)&(MAXBUCKET-1);
  EnterCriticalSection(&critdin);
  ret->file=file;
  ret->line=line;
  ret->orden=totalbloque;
  ret->funcion=funcion;
  ret->tam=size;
  ret->sig=raiz[bucket];
  ret->ant=NULL;
  if (raiz[bucket]) raiz[bucket]->ant=ret;
  raiz[bucket]=ret;

  if (log_sal) {
    fprintf(log_sal,"%6ld %-8.8s %-32.32s %5u %p  %9u\n",ret->orden,ret->funcion,ret->file,ret->line,ret+1,ret->tam);
    fflush(log_sal);
  }

  totalloc+=size;
  if ((actalloc+=size) > maxalloc)
    maxalloc=actalloc;

  totalbloque++;
  if (++actbloque > maxbloque)
    maxbloque++;
  poncheckbyte(ret);
  LeaveCriticalSection(&critdin);
}



static listas *pide_bloque(unsigned size,char *funcion,char *file,int line)
{
  listas *ret;

  if (!init_dinamica) initdinamica(NULL);
  if (log_sal) {
    if (!size) warning(("Petici¢n de bloque de 0 bytes en %s %d",file,line));
  }
  ret=calloc(1,size+sizeof(listas)+1);
  if (ret==NULL) {
    if (DINAMICA_SEGURA) final(("Sin memoria en %s %d",file,line));
    return(NULL);
  }
  engancha_suma(ret,size,funcion,file,line);
  return(ret);
}


static listas *busca_libera(void *ptr,char *funcion,char *file, int line)
{
  listas  *i;
  listas *ptr1=((listas *)ptr)-1;
  int bucket;
  bucket=(((size_t)ptr1)>>5)&(MAXBUCKET-1);

  if (!init_dinamica) initdinamica(NULL);
  if (ptr==NULL) final(("Liberando puntero nulo en %s %d",file,line));
  EnterCriticalSection(&critdin);
  for(i=raiz[bucket];i!=NULL;i=i->sig)
    if (ptr1==i) break;
  if (i==NULL) {
    imprime_dinamica("std.txt");
    final(("Liberando bloque no allocado %Fp %s %d",ptr,file,line));
  }

  if (log_sal) {
    fprintf(log_sal,"%6ld %-8.8s %-32.32s %5u %p  %9u\n",totalbloque,funcion,file,line,i+1,i->tam);
    fflush(log_sal);
  }

  if (i->sig) i->sig->ant=i->ant;
  if (i->ant) i->ant->sig=i->sig;
  else raiz[bucket]=i->sig;
  actalloc-=i->tam;
  actbloque--;
  LeaveCriticalSection(&critdin);
  return(i);
}

V10IMPORT int verificadinamica(void)
{
  listas  *i;
  int j;

  if (!init_dinamica) initdinamica(NULL);
  for (j=0;j<MAXBUCKET;j++) {
      for (i=raiz[j];i!=NULL;i=i->sig) {
          if (checkbyte(i)!=0) {
             final(("En fichero %s %d bloque de memoria dinamica sobreescrito",i->file,i->line));
          }
       }
   }
  return(0);
}


V10IMPORT void *v10calloc(unsigned number,unsigned size,char *file,int line)
{
  listas *ret;

  ret=pide_bloque(size*number,"CALLOC",file, line);
  return(ret+1);
}


V10IMPORT void *v10malloc(unsigned size,char *file,int line)
{
  listas *ret;

  ret=pide_bloque(size,"MALLOC",file, line);
  return(ret+1);
}


V10IMPORT char *v10strdup(char *cadena,char *file,int line)
{
  listas   *ret;
  unsigned size;

  size=strlen(cadena)+1;
  ret=pide_bloque(size,"STRDUP",file, line);
  strcpy((char *)(ret+1),cadena);
  return((char *)(ret+1));
}


V10IMPORT void *v10realloc(void *ptr,unsigned size,char *file,int line)
{
  listas *ret=NULL;

  if (ptr) ret=busca_libera(ptr,"REFRE",file,line);
  if (size==0) {
     if (checkbyte(ret)!=0) {
        final(("En fichero %s %d bloque de memoria dinamica sobreescrito",ret->file,ret->line));
      }
     free(ret);
     return(NULL);
   }
  ret=realloc(ret,size+sizeof(listas)+1);

  if (ret==NULL) {
    if (DINAMICA_SEGURA) final(("Sin memoria en %s %d",file,line));
    return(NULL);
  }
  engancha_suma(ret,size,"REALLOC",file,line);
  return(ret+1);
}


V10IMPORT void v10free(void *ptr,char *file,int line)
{
  listas *freeptr;

  if (ptr==NULL) return;
  freeptr=busca_libera(ptr,"FREE",file,line);
  if (checkbyte(freeptr)!=0) {
     final(("En fichero %s %d bloque de memoria dinamica sobreescrito",freeptr->file,freeptr->line));
   }
  free(freeptr);
}


