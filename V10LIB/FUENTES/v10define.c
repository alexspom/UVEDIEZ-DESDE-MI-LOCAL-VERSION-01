/*
* M�dulo : V10DEFINE.C                                             
* Objeto:  Lectura de fichero h con defines estandar C
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"


#define MAXLINEA    300
#define MAXTOKEN     50
#define MAXDEFINE   2000
typedef struct {
         char *nombre;
         char *definicion;
       } defines;
static defines arrdef[MAXDEFINE];
static int numdef;


static defines *buscadef(char *nombre)
{
  int ndef;
  for (ndef=0;ndef<numdef;ndef++) {
      defines *def=arrdef+ndef;
      if (strcmp(nombre,def->nombre)==0) return(def);
      if (strcmp(nombre,def->nombre)<0) {
         memmove(def+1,def,(numdef-ndef)*sizeof(defines));
         memset(def,0,sizeof(defines));
         def->nombre=strdup(nombre);
         numdef++;
         return(def);
       }
   }
  if (numdef>=MAXDEFINE-1) final(("Demasiados defines"));
  arrdef[numdef].nombre=strdup(nombre);
  numdef++;
  return(arrdef+numdef-1);
}

static void eliminacomentarios(char *linea)
{
  char *aux,*aux1;
  aux=strstr(linea,"/*");
  if (aux==NULL) return;
  aux1=strstr(aux,"*/");
  if (aux1==NULL) final(("Linea %s sin fin comentario",linea));
  strcpy(aux,aux1+2);
}

static void findefine(void)
{
  int n;
  for (n=0;n<numdef;n++) {
      defines *def=arrdef+n;
      if (def->nombre)     free(def->nombre);
      if (def->definicion) free(def->definicion);
    }
  numdef=0;
}

void leedefines(char *minombre)
{
  FILE *entrada;
  char linea[MAXLINEA],nombre[MAXPATH];
  static int init=0;
  if (init==0) {
     atexit(findefine);
     init=1;
   }
  strcpy(nombre, minombre);
  entrada=fopen(nombre,"r");
  if (entrada==NULL) {
      v10log(LOGERROR,"Error al abrir fichero %s\n",minombre);
      return;
  }
  while (fgetss(linea,sizeof(linea)-1,entrada)) {
        eliminacomentarios(linea);
        eliminasp(linea);
        if (strncmp(linea,"#define",7)==0) {
           char nombre[MAXLINEA],definicion[MAXLINEA];
           char *aux;
           defines *def;
           strcpy(nombre,linea+7);
           eliminasp(nombre);
           aux=strchr(nombre,' ');
           if (aux==NULL) final(("Define sin definicion %s",linea));
           strcpy(definicion,aux);
           eliminasp(definicion);
           *aux=0;
           def=buscadef(nombre);
           def->definicion=strdup(definicion);
        }
      }
  fclose(entrada);
}


void sustituyedefines(char *linea)
{
  char *aux=linea;
  while ((aux=strchr(aux,'#'))!=NULL) {
        char token[MAXTOKEN],*nombre=token,*desde=aux;
        defines *def;
        aux++;
        while (isalnum(*aux) || *aux=='_') {
              *nombre++=*aux++;
           }
        if (nombre==token||(*token=='L' && nombre==token+1)) {
           linea=aux;
           continue;
         }
        *nombre=0;
        def=buscadef(token);
        if (def->definicion==NULL) {
            continue;
           mensajefcm(10,"Define %s no existe",token);
           return;
         }
        strerase(desde,0,strlen(token)+1);
        strins(desde,def->definicion);
        aux+=strlen(def->definicion)-strlen(token);
    }
}

