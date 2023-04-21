/*
* Módulo : V10MENULISTAS.C
* Objeto:  Menus temporales generados a partir de listas de cadenas
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"


menulistas *crea_menulista(char *nombre,unsigned maximo)
{
  menulistas *menulista;
  menulista=(menulistas *)calloc(1,sizeof(menulistas));
  menulista->p=calloc(maximo,sizeof(char *));
  menulista->nombre=strdup(nombre);
  menulista->maximo=maximo;
  return(menulista);
}


void libera_menulista(menulistas *menulista)
{
  if (menulista->num) {
    int i;
    for (i=0 ; i<menulista->num ; i++) free(menulista->p[i]);
  }
  free(menulista->nombre);
  free(menulista->p);
  free(menulista);
}


static void promociona(menulistas *menulista,int elemento)
{
  char *tmp;
  int i;
  tmp=menulista->p[elemento];
  for (i=elemento ; i<menulista->num-1 ; i++)
    menulista->p[i]=menulista->p[i+1];
  menulista->p[menulista->num-1]=tmp;
}


int esta_en_menulista(menulistas *menulista,char *cadena)
{
  int i;

  for (i=0 ; i<menulista->num ; i++) {
    if (strcmp(menulista->p[i],cadena)==0) return(i);
  }
  return(-1);
}


int mete_en_menulista(menulistas *menulista,char *cadena)
{
  int ret;

  if (es_blanco(cadena)) ret=0;
  else if ((ret=esta_en_menulista(menulista,cadena))>=0) {
         promociona(menulista,ret);
         ret=-1;
       }
       else {
         if (menulista->num >= menulista->maximo) {
           promociona(menulista,0);
           menulista->num--;
           free(menulista->p[menulista->num]);
         }
         menulista->p[menulista->num]=strdup(cadena);
         menulista->num++;
         if (menulista->num < menulista->maximo) menulista->p[menulista->num]=NULL;
         ret=1;
       }
  return(ret);
}


int salva_menulista(menulistas *menulista)
{
  FILE *salida;

  if ((salida=fopen(menulista->nombre,"w"))!=NULL) {
    int i;

    for (i=0;i<menulista->num;i++) {
      fprintf(salida,"%s\n",menulista->p[i]);
    }
    fclose(salida);
    return(1);
  }
  warning(("No puedo abrir %s",menulista->nombre));
  return(0);
}


int carga_menulista(menulistas *menulista)
{
  FILE *salida;

  if ((salida=fopenpath(menulista->nombre,"r"))!=NULL) {
    char *linea;

    linea=(char *)calloc(1,MAXCADENA);
    while (fgetss(linea,MAXCADENA-1,salida)) {
      mete_en_menulista(menulista,linea);
    }
    free(linea);
    fclose(salida);
    return(menulista->num);
  }
  return(0);
}

char *valor_menulista(menulistas *menulista,int elemento)
{
  if (elemento >= menulista->num) return(NULL);
  return(menulista->p[elemento]);
}

static int saca_menupos(menulistas *menulista,int x,int y,int pos)
{
  int ret;
  int salir = 0;
  char **opciones;

  if (menulista->num>0) {
    opciones=calloc(menulista->maximo+2,sizeof(char *));
    opciones[0]=menulista->nombre;
    memmove(opciones+1,menulista->p,menulista->maximo*sizeof(char *));
    opciones[menulista->num+1]=NULL;
    ret=pos;
    if (ret<0) ret=0;
    while (!salir) {
      ret=menu(opciones,ret,x,y);
      switch (ult_pul) {

        case cr: promociona(menulista,ret);
                 ret=menulista->num-1;
                 salir=1;
                 break;

        case dele: promociona(menulista,ret);
                   free(menulista->p[menulista->num-1]);
                   menulista->p[menulista->num-1]=NULL;
                   menulista->num--;
                   if (ret>0) ret--;
                   if (menulista->num>0) {
                     memmove(opciones+1,menulista->p,menulista->maximo*sizeof(char *));
                   }
                   else {
                     ret=-1;
                     salir=1;
                   }
                   break;

        case esc: ret=-1;
                 salir=1;
                 break;
        default:promociona(menulista,ret);
                 ret=-1;
                 salir=1;
                 break;
      }
    }
    free(opciones);
    return(ret);
  }
  return(-1);
}

int saca_menu(menulistas *menulista,int x,int y)
{
  int ret=-1;
  if (menulista->num>0) {
    ret=saca_menupos(menulista,x,y,menulista->num-1);
   }
  return(ret);
}
