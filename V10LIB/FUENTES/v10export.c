
#include "v10form.h"

static v10cursors *vdexport;

static FILE *salida;
int COMPRESS=TRIM;
int HEADERS=HIMPORT;
int VERBOSE=2;
char EXSEPARADOR='�';
unsigned TAMBUFFER=3000000U;
unsigned ANALISIS=0;
char NOMBRETABLA[MAXNOMBREV10];

typedef struct {
	 char *nombre;
	 int  off,lon;
       } bcampos;
typedef struct {
	    bcampos *c;
	    int     nbind,
               tam;
	    char    *buffer;
      } bexports;
unsigned maxlon[MAXCAMPOS];

#define EXSEPARADORES "=  ,"


static bexports *analiza_paramexp(char *param)
{
  bexports *ret;
  char *ptr,*aux;
  int lon=0;
  if (param==NULL) return(NULL);
  aux=strdup(param);
  ret=calloc(1,sizeof(bexports));
  ret->buffer=calloc(1,strlen(param));
  ret->c=calloc(MAXBCAMPOS,sizeof(bcampos));
  ptr=strtok(aux,EXSEPARADORES);
  while (ptr) {
        ret->c[ret->nbind].nombre=strdup(ptr);
	ptr=strtok(NULL,EXSEPARADORES);
        if (ptr==NULL) {
           final(("Error analizando %s**\n",param));
         }
        ret->c[ret->nbind].off=lon;
        strcpy(ret->buffer+lon,ptr);
        lon+=strlen(ptr)+1;
        ret->nbind++;
	ptr=strtok(NULL,EXSEPARADORES);
     }
  ret->c=realloc(ret->c,ret->nbind*sizeof(bcampos));
  free(aux);
  return(ret);
}

static void liberabexport(bexports *b)
{
  int nc;
  if (b==NULL) return;
  for (nc=0;nc<b->nbind;nc++) free(b->c[nc].nombre);
  if (b->c) free(b->c);
  if (b->buffer) free(b->buffer);
  free(b);
}
                        

long export(char *select,char *fich,char *tabla,char *param,unsigned tambuffer)
{
  int nc;
  unsigned lon=0,off;
  int ret;
  unsigned nelem;
  long nreg=0,nbytes=0;
  bexports *bind;
  char *buffer;
  char linea[MAXCADENA*10],*ptr;
  if (VERBOSE) {
     v10log(LOGNORMAL,"Haciendo export tabla %s a fichero %s\n",tabla,fich?fich:"DEFECTO.VDB");
     if (VERBOSE>1) {
        if (param) v10log(LOGNORMAL,"   parametros %s\n",param);
	if (VERBOSE>2) {
           v10log(LOGNORMAL,"   select %s\n",select);
         }
      }
   }
  vdexport=abrecursor(select);
  if ((salida=fopen(fich?fich:"DEFECTO.VDB","wb"))==NULL) {
     final(("No puedo abir fichero de backup"));
   }
  if (HEADERS) fprintf(salida,"%s,%010ld,%010ld,%05d,%03d\r\n",tabla,nreg,nbytes,vdexport->ndef,EXSEPARADOR);
  bind=analiza_paramexp(param);
  if (bind) {
     for (nc=0;nc<bind->nbind;nc++) {
         if (campobind(vdexport,bind->c[nc].nombre)) {
            bindcursor(vdexport,bind->c[nc].nombre,bind->buffer+bind->c[nc].off,MAXLCAMPO,V10CADENA);
          }
       }
   }
  for (nc=0;nc<vdexport->ndef;nc++) {
      int tam;
      tam=vdexport->def[nc].oralen;
      if (vdexport->def[nc].oratipo==OCINUMBER) tam=LNUMERO;
      lon+=tam+1;
      if (HEADERS) fprintf(salida,"%s,%02d,%05d,%05d\r\n",vdexport->def[nc].nombre,vdexport->def[nc].oratipo,tam,tam);
    }
  buffer=calloc(1,lon);
  off=0;
  for (nc=0;nc<vdexport->ndef;nc++) {
      unsigned tam;
      tam=vdexport->def[nc].oralen+1;
      if (vdexport->def[nc].oratipo==OCINUMBER) tam=LNUMERO;
      definecursor(vdexport,nc+1,buffer+off,tam,V10CADENA);
      maxlon[nc]=1;
      off+=tam;
    }
  nelem=tambuffer/(lon+2*sizeof(short));
  if (VERBOSE>1) {
     v10log(LOGNORMAL,"   Buffer %u Registro %u Elementos %u\n",tambuffer,lon,nelem);
   }
  if (nelem) preparaarrayfetch(vdexport,nelem);
  ret=ejecutacursor(vdexport);
  if (ret) cursordebug(vdexport);
  while ((ret=fetchcursor(vdexport))==0) {
        off=0;
        ptr=linea;
        for (nc=0;nc<vdexport->ndef;nc++) {
            unsigned lon;
            if (strchr(buffer+off,EXSEPARADOR)) {
                char *aux;
                v10log(LOGERROR,"En campo %s esta el caracter '%c' que se usa como separador\n",vdexport->def[nc].nombre,EXSEPARADOR);
                while ((aux=strchr(buffer+off,EXSEPARADOR))!=NULL) *aux=(char)((*aux)+1);
            }
            if (COMPRESS==NONE) {
                lon=vdexport->def[nc].oralen;
                if (vdexport->def[nc].oratipo==OCINUMBER) lon=LNUMERO-1;
                pad(buffer+off,lon);
            } else {
                trim(buffer+off);
            }
            lon=strlen(buffer+off);
            strcpy(ptr,buffer+off);
            ptr+=lon;*ptr++=EXSEPARADOR;
            if (lon>maxlon[nc]) maxlon[nc]=lon;
            if (vdexport->def[nc].oratipo==OCINUMBER) lon=LNUMERO;
            else                                lon=vdexport->def[nc].oralen+1;
            off+=lon;
        }
       *ptr++='\r';*ptr++='\n';*ptr=0;
       fwrite(linea,1,ptr-linea,salida);
       nreg++;
       if (((nreg%INFORMA)==0)&&VERBOSE) {
          v10log(LOGNORMAL,"  %ld registros salvados\r",nreg);
          hay_tecla();
        }
     }
  if (ret!=NOFOUND) {
     cursordebug(vdexport);
     v10log(LOGERROR,"Tabla %s no exportada completamente\n",tabla);
  }
  nbytes=ftell(salida);
  rewind(salida);
  if (HEADERS) fprintf(salida,"%s,%010ld,%010ld,%05d,%03d\r\n",tabla,nreg,nbytes,vdexport->ndef,EXSEPARADOR);
  for (nc=0;nc<vdexport->ndef;nc++) {
      int tam;
      tam=vdexport->def[nc].oralen;
      if (vdexport->def[nc].oratipo==OCINUMBER) tam=LNUMERO;
      if (HEADERS) fprintf(salida,"%s,%02d,%05d,%05d\r\n",vdexport->def[nc].nombre,vdexport->def[nc].oratipo,tam,maxlon[nc]);
    }
  fclose(salida);
  free(buffer);
  if (bind) liberabexport(bind);
  liberacursor(vdexport);
  if (VERBOSE) {
     v10log(LOGNORMAL,"  %ld registros salvados bytes %ld\n",nreg,nbytes);
     hay_tecla();
   }
  return(nreg);
}


long exporttabla(char *nombre,char *where,char *param,char *nfichero)
{
  char *buffer,*fichero;
  long ret;
  buffer=calloc(1,MAXSQL);
  fichero=calloc(1,MAXCADENA);
  sprintf(buffer,"SELECT * FROM %s",nombre);
  if (where) {
     sprintf(buffer+strlen(buffer)," %s",where);
   }
  if (nfichero==NULL) sprintf(fichero,"%s.VDB",nombre);
     else             strcpy(fichero,nfichero);
  ret=export(buffer,fichero,nombre,param,TAMBUFFER);
  free(buffer);
  free(fichero);
  return(ret);
}

#define SELTABLAS "SELECT TABLE_NAME FROM USER_TABLES ORDER BY TABLE_NAME"

void exportuser(char *where,char *param)
{
  v10cursors *vdc;
  char nombre[100]="";
  int ret;
  vdc=abrecursor(SELTABLAS);
  definetodo(vdc,nombre,sizeof(nombre),V10CADENA,NULL);
  ret=ejecutacursor(vdc);
  if (ret) cursordebug(vdc);
  while ((ret=fetchcursor(vdc))==0) exporttabla(nombre,where,param,NULL);
  if (ret!=NOFOUND) {
     cursordebug(vdc);
     v10log(LOGERROR,"%s","No se han exportado todas las tablas\n");
   }
  liberacursor(vdc);
}

void importuser(char **genconst)
{
  v10cursors *vdc;
  char nombre[100]="";
  int ret;
  char *constraint=NULL,*totconstraint=NULL;
  int lonconstraint=0;
  vdc=abrecursor(SELTABLAS);
  definetodo(vdc,nombre,sizeof(nombre),V10CADENA,NULL);
  ret=ejecutacursor(vdc);
  if (ret) cursordebug(vdc);
  while ((ret=fetchcursor(vdc))==0) {
        strcat(nombre,".VDB");
        if (access(nombre,0)==0) {
           recupera(nombre,TAMBUFFER,&constraint);
           if (constraint) {
              v10log(LOGDEBUG,"Constraints de la tabla %s\n",constraint);
              if (totconstraint==NULL) {
                 totconstraint=constraint;
                 lonconstraint=strlen(totconstraint);
               } else {    
                 lonconstraint+=strlen(constraint)+1;
                 totconstraint=realloc(totconstraint,lonconstraint);
                 strcat(totconstraint,"@");
                 strcat(totconstraint,constraint);
               }
            }
         }
     }
  if (ret!=NOFOUND) {
     cursordebug(vdc);
     v10log(LOGERROR,"%s","No se han importado todas las tablas\n");
   }
  liberacursor(vdc);
  *genconst=totconstraint;
}
