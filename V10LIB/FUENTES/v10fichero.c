/*
* Módulo : V10FICHERO.C
* Objeto:  Manejo estandarizado de ficheros
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
//Version minima de windows sobre la que funciona

#define _WIN32_WINNT 0X0400
#include "v10.h"

static int expandido=0;
int precalculaficheros=1;
#define MAXFICHEROS 20000
static char pathv10[MAXCADENA*10];
static char *listadir[MAXFICHEROS];
static int numficheros;

void stradd(char *cadena,char ch)
{
    int lon;
    lon=strlen(cadena);
    cadena[lon]=ch;
    cadena[lon+1]=0;
}

static void anadefichero(char *directorio,char *fichero)
{
    listadir[numficheros]=calloc(1,strlen(directorio)+strlen(fichero)+1);
    sprintf(listadir[numficheros],"%s%s",directorio,fichero);
    strmin(listadir[numficheros]);
    numficheros++;
}

static int yaanalizado(char *path,char *destino)
{
    char *aux;
    while ((aux=strstr(destino,path))!=NULL) {
        if (aux==destino||aux[-1]==SEMICOLON) {
            if (strlen(destino)>=strlen(path)) {
                if (destino[strlen(path)]==0||destino[strlen(path)]==SEMICOLON) return 1;
            }
        }
        if (aux=strchr(destino,SEMICOLON)) destino=aux+1;
        else break;
    }
    return(0);
}

static void listadedirectorios(char *path,char *destino)
{
	HANDLE handle; 
	char directorio[MAXPATH],nombre[MAXPATH]; 
	WIN32_FIND_DATA finddata;
    v10log(LOGDEBUG,"Lista de directorios %s %s\n",path,destino);
	strcpy(directorio,path);
    if (directorio[strlen(directorio) - 1] != BACKSLASH) stradd(directorio, BACKSLASH);
	sprintf(nombre,"%s*.*",directorio);
	handle=FindFirstFile(nombre,&finddata);
    if (yaanalizado(path,destino)) {
        v10log(LOGNORMAL,"Directorio %s ya analizado\n",path);
        return;
    }
    sprintf(destino+strlen(destino),"%s%c",path,SEMICOLON);
	while (handle) {
		if (*finddata.cFileName!='.') {
            strmin(finddata.cFileName);
		   if (finddata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			   char nuevodir[MAXPATH*10];	
               sprintf(nuevodir, "%s%s%c", directorio, finddata.cFileName, BACKSLASH);
               //strmay(nuevodir);
		       listadedirectorios(nuevodir,destino);
		   } else {
               anadefichero(directorio,finddata.cFileName);
               v10log(LOGDEBUG,"Procesado fichero %d %s completo %s%s\n",numficheros,finddata.cFileName,directorio,finddata.cFileName);
		   }
		}
		if (FindNextFile(handle,&finddata)==0) break;
	}
	if (handle) FindClose(handle);
	return;
}


static void precalculapath(void)
{
    char *path,*semicolon;
    v10horas init=damecent();
    if (expandido) return;
    v10log(LOGNORMAL,"%s","Precalculando el path\n");
    expandido=1;
    strcpy(pathv10,"");
    path=getenv("PATHV10");
    if (path==NULL) {
        return;
    }
    path=strdup(path);
    strmin(path);
    semicolon=path;
    while (semicolon!=NULL) {
        char *aux;
        aux=strchr(semicolon,SEMICOLON);
        if (aux) {
            *aux=0;
            aux++;
        }
        if (!es_blanco(semicolon)) {
           listadedirectorios(semicolon,pathv10);
        }
        semicolon=aux;
    }
    free(path);
    while (pathv10[strlen(pathv10)-1]==SEMICOLON) pathv10[strlen(pathv10)-1]=0;
    v10log(LOGNORMAL,"Precalculado el path %5.2lf sg. ficheros %d\n",(damecent()-init)/100,numficheros);
}

int dameprecalculado(char *nombre,char *completo)
{
	int i;
	char destino[MAXPATH];
    if (*nombre == BACKSLASH) strcpy(destino, nombre);
    else sprintf(destino, "%c%s", BACKSLASH,nombre);
    v10log(LOGDEBUG,"Busco %s en %d ficheros\n",nombre,numficheros);
	for (i=0;i<numficheros;i++) {
		if (strlen(listadir[i])>=strlen(destino)) {
			if (stricmp(destino,listadir[i]+strlen(listadir[i])-strlen(destino))==0) {
				strcpy(completo,listadir[i]);
                v10log(LOGDEBUG,"Fichero %s resuelto en %s precalculado\n",nombre,completo);
				return(0);
			}
		}
	}
	strcpy(completo,nombre);
	return(-1);
}
    
void pasaaos(char *nombre)
{
    char *aux;
    strmin(nombre);
    if (BACKSLASH!='/') while ((aux = strchr(nombre, '/'))) *aux = BACKSLASH;
}
    
int damenombrecompleto(char *nombre,char *completo)
{
  char *path,*copiapath,*semicolon,destino[MAXPATH];
  int ret;

  pasaaos(nombre);
  ret=access(nombre,0);
  if (ret==0) {
     strcpy(completo,nombre);
     return(0);
   }
  path=getenv("PATHV10");
  if (path==NULL) {
	  path=getenv("PATH");
  } else {
      precalculapath();
      path=pathv10;
	  if (precalculaficheros) {
		  ret=dameprecalculado(nombre,completo);
          if (ret==0) {
              v10log(LOGDEBUG,"%s","Existe precalculado\n");
              return ret;
          } 
	  }
  }
  if (path) {
     copiapath=strdup(path);
     semicolon=copiapath;
   } else {
     semicolon=NULL;
     copiapath=NULL;
   }
  strcpy(completo,nombre);
  while (semicolon!=NULL) {
     char *aux;
     aux=strchr(semicolon,SEMICOLON);
     if (aux) {
        *aux=0;
        aux++;
      }
     if (!es_blanco(semicolon)) {
        strcpy(destino,semicolon);
        if (destino[strlen(destino)-1]!='/') stradd(destino,'/');
        strcat(destino,nombre);
        ret=access(destino,0);
        if (ret==0) {
            strcpy(completo,destino);
            break;
        }
     }
     semicolon=aux;
   }
  if (copiapath) free(copiapath);
  return(ret);
}

FILE *fopenpath(char *nombre,char *modo)
{
  FILE *ret;
  char nuevo[MAXPATH];	
  ret=fopen(nombre,modo);
  if (ret) return(ret);
  if (damenombrecompleto(nombre,nuevo)==0) {
      v10log(LOGDEBUG,"Intentando abrir %s\n",nuevo);
     ret=fopen(nuevo,modo);
  } else {
	  ret=NULL;
  }
  return(ret);
}

FILE *fopenlog(char *nombre,char *modo)
{
  FILE *ret;
  ret=fopenpath(nombre,modo);
  if (ret==NULL) v10log(LOGNORMAL,"Error al abrir fichero %s\n",nombre);

  return(ret);
}

FILE *fopenseguro(char *nombre,char *modo)
{
  FILE *ret;
  ret=fopenpath(nombre,modo);
  if (ret==NULL) final(("Error al abrir fichero %s",nombre));
  return(ret);
}


char *fgetss(char *linea,int n,FILE *entrada)
{
  char *ret,*aux;
  if ((ret=fgets(linea,n,entrada))!=NULL) {
     aux=strchr(ret,'\n');
     if (aux) *aux=0;
     aux=strchr(ret,'\r');
     if (aux) *aux=0;

   }
  return(ret);
}

int copiafich( char *fdesde, char *fhasta ) {
	FILE *entrada, *salida;
	int ch;

	entrada = fopen( fdesde, "rb" );
	if ( entrada == NULL ) return(-1);
	salida = fopen( fhasta, "wb" );
	if ( salida == NULL) {
		fclose( entrada );
		v10log(LOGERROR, "No he podido copiar %s a %s\n", fdesde, fhasta );
		return(-1);
	}

	while ( (ch=fgetc(entrada)) != EOF ) fputc(ch,salida);
	fclose( entrada );
	fclose( salida );
	return(0);
}

int muevefich( char *fdesde, char *fhasta ) {
	int ret;
	ret=copiafich(fdesde,fhasta);
	if (ret) return(ret);
	unlink(fdesde);
	return(0);
}

