
#include "v10form.h"

#define MAXBUFFER 2000000
#define MAXLOGGING 4
typedef struct {
          char *nombre;
          int  oratipo,
               oralen,
               off;
          int noimport;
        } bcampos;

typedef struct {
         char *nombre;
         long nreg,
              lon,
              nbytes,
              ncamp;
         int  separador;
         bcampos *c;
         char    *buffer;
         v10cursors *vdc;
         int    nelem;
      } exports;

FILE *entrada;

unsigned COMMITPOINT=100;
unsigned LOGGING=0;
unsigned NOINDICES=0;
unsigned INFORMA=1000;

void genselexport(exports *export)
{
  char *cadena=calloc(1,MAXSQL);
  char *ptr=cadena;
  int nc;
  int alguno=0;
  sprintf(ptr,"INSERT INTO %s (",export->nombre);
  ptr+=strlen(ptr);
  for (nc=0;nc<export->ncamp;nc++) {
      if (export->c[nc].noimport) continue;
      if (alguno) {
         sprintf(ptr,",");
         ptr+=strlen(ptr);
       }
      alguno=1;
      sprintf(ptr,"%s",export->c[nc].nombre);
      ptr+=strlen(ptr);
   }
  sprintf(ptr,") VALUES (");
  ptr+=strlen(ptr);
  alguno=0;
  for (nc=0;nc<export->ncamp;nc++) {
      if (export->c[nc].noimport) continue;
      if (alguno) {
         sprintf(ptr,",");
         ptr+=strlen(ptr);
       }
      alguno=1;
      if (export->c[nc].oratipo==OCINUMBER) sprintf(ptr,":%s",export->c[nc].nombre);
         else                            sprintf(ptr,":%s",export->c[nc].nombre);
      ptr+=strlen(ptr);
   }
  sprintf(ptr,")");
  export->vdc=parsecursornombre(cadena,"EXPORT");
  if (export->vdc!=NULL) {
     for (nc=0;nc<export->ncamp;nc++) {
         if (export->c[nc].noimport) continue;
         bindcursor(export->vdc,export->c[nc].nombre,export->buffer+export->c[nc].off*export->nelem,export->c[nc].oralen+1,V10CADENA);
      }
   }
  free(cadena);
}

char *dupcad(char **linea)
{
  char *aux,*ret;
  aux=strchr(*linea,',');
  if (aux!=NULL) *aux=0;
  ret=strdup(*linea);
  (*linea)+=strlen(*linea);
  if (aux!=NULL) {
     *aux=',';
     (*linea)++;
   }
  return(ret);
}

long leenumero(char **linea)
{
  char *aux;
  long ret;
  aux=strchr(*linea,',');
  if (aux!=NULL) *aux=0;
  ret=atol(*linea);
  (*linea)+=strlen(*linea);
  if (aux!=NULL) {
     *aux=',';
     (*linea)++;
   }
  return(ret);
}

exports *leecabexport(char *linea)
{
  exports *ret;
  ret=calloc(1,sizeof(exports));
  ret->nombre=dupcad(&linea);
  ret->nreg=leenumero(&linea);
  ret->nbytes=leenumero(&linea);
  ret->ncamp=leenumero(&linea);
  ret->separador=(unsigned)leenumero(&linea);
  ret->c=calloc((unsigned)ret->ncamp,sizeof(bcampos));
  return(ret);
}

void liberaexport(exports *export)
{
  int nc;
  for (nc=0;nc<export->ncamp;nc++) free(export->c[nc].nombre);
  if (export->c) free(export->c);
  if (export->vdc) liberacursor(export->vdc);
  if (export->buffer) free(export->buffer);
  free(export);
}

#define SELINDEXL "SELECT INDEX_NAME,UNIQUENESS,TABLESPACE_NAME, "\
                       " INI_TRANS,MAX_TRANS,INITIAL_EXTENT, "\
                       " NEXT_EXTENT,MIN_EXTENTS,MAX_EXTENTS, "\
                       " PCT_INCREASE,PCT_FREE,LOGGING  FROM  "\
                   " USER_INDEXES WHERE TABLE_NAME=:TNAME "
                 
#define SELINDEX "SELECT INDEX_NAME,UNIQUENESS,TABLESPACE_NAME, "\
                       " INI_TRANS,MAX_TRANS,INITIAL_EXTENT, "\
                       " NEXT_EXTENT,MIN_EXTENTS,MAX_EXTENTS, "\
                       " PCT_INCREASE,PCT_FREE FROM  "\
                   " USER_INDEXES WHERE TABLE_NAME=:TNAME "

#define SELCAMP "SELECT COLUMN_NAME "\
                  " FROM USER_IND_COLUMNS WHERE INDEX_NAME=:INDEX_NAME "\
                  " ORDER BY COLUMN_POSITION "

char *calcula_indices(char *tabla)
{
  char iname[MAXNOMBREV10],colname[MAXNOMBREV10],indextype[MAXNOMBREV10],
       tablespace_name[MAXNOMBREV10],logging[MAXLOGGING]="NO";
  long ini_trans,max_trans,initial_extent,next_extent,min_extents,
       max_extents,pct_increase,pct_free;
  v10cursors *li,*lc;
  char *indice,*ptr;
  int ret;
  lc=abrecursor(SELCAMP);
  definetodo(lc,colname,sizeof(colname),V10CADENA,NULL);
  bindtodo(lc,"INDEX_NAME",iname,sizeof(iname),V10CADENA,NULL);
  if (LOGGING) {
     li=abrecursor(SELINDEXL);
     definetodo(li,iname,sizeof(iname),V10CADENA,
                    indextype,sizeof(indextype),V10CADENA,
                    tablespace_name,sizeof(tablespace_name),V10CADENA,
                    &ini_trans,sizeof(ini_trans),V10LONG,
                    &max_trans,sizeof(max_trans),V10LONG,
                    &initial_extent,sizeof(initial_extent),V10LONG,
                    &next_extent,sizeof(next_extent),V10LONG,
                    &min_extents,sizeof(min_extents),V10LONG,
                    &max_extents,sizeof(max_extents),V10LONG,
                    &pct_increase,sizeof(pct_increase),V10LONG,
                    &pct_free,sizeof(pct_free),V10LONG,
                    logging,sizeof(logging),V10CADENA,NULL);
   } else {
     li=abrecursor(SELINDEX);
     definetodo(li,iname,sizeof(iname),V10CADENA,
                    indextype,sizeof(indextype),V10CADENA,
                    tablespace_name,sizeof(tablespace_name),V10CADENA,
                    &ini_trans,sizeof(ini_trans),V10LONG,
                    &max_trans,sizeof(max_trans),V10LONG,
                    &initial_extent,sizeof(initial_extent),V10LONG,
                    &next_extent,sizeof(next_extent),V10LONG,
                    &min_extents,sizeof(min_extents),V10LONG,
                    &max_extents,sizeof(max_extents),V10LONG,
                    &pct_increase,sizeof(pct_increase),V10LONG,
                    &pct_free,sizeof(pct_free),V10LONG,NULL);
   }
  bindtodo(li,"TNAME",tabla,strlen(tabla)+1,V10CADENA,NULL);
  ret=ejecutacursor(li);
  if (ret) cursordebug(li);
  indice=ptr=calloc(1,MAXSQL);
  while ((ret=fetchcursor(li))==0) {
        int primera=1;
        sprintf(ptr,"CREATE %s INDEX %s ON %s (",strcmp(indextype,"UNIQUE")==0?"UNIQUE":"",iname,tabla);
        ptr+=strlen(ptr);
        ret=ejecutacursor(lc);
        if (ret) cursordebug(lc);
        while ((ret=fetchcursor(lc))==0) {
              if (primera) primera=0;
                 else         *ptr++=',';
              sprintf(ptr,"%s",colname);
              ptr+=strlen(ptr);
            }
        sprintf(ptr,") INITRANS %ld MAXTRANS %ld TABLESPACE %s "
                    "STORAGE (INITIAL %ld NEXT %ld MINEXTENTS %ld "
                    "MAXEXTENTS %ld PCTINCREASE %ld) PCTFREE %ld %s",
                    ini_trans,max_trans,tablespace_name,initial_extent,
                    next_extent,min_extents,max_extents,pct_increase,
                    pct_free,LOGGING?"NOLOGGING":"");
        ptr+=strlen(ptr)+1;
        if (strcmp(logging,"YES")==0) {
           sprintf(ptr,"ALTER INDEX %s LOGGING",iname);
           ptr+=strlen(ptr)+1;
         }
        if (VERBOSE) {
           v10log(LOGNORMAL,"Borrando indice %s\n",iname);
         }
        ejecutaimmediatoparam("DROP INDEX %s",iname);
    }
  *ptr=0;
  liberacursor(li);
  liberacursor(lc);
  return(indice);
}

#define CSELREF "SELECT CONSTRAINT_NAME FROM USER_CONSTRAINTS WHERE TABLE_NAME=:TABLE_NAME AND CONSTRAINT_TYPE='R' AND STATUS='ENABLED'"

char *calcula_referencias(char *tabla)
{
  char constname[MAXNOMBREV10];
  v10cursors *lc;
  char *indice,*ptr;
  int ret;
  lc=abrecursor(CSELREF);
  definetodo(lc,constname,sizeof(constname),V10CADENA,NULL);
  bindtodo(lc,"TABLE_NAME",tabla,strlen(tabla)+1,V10CADENA,NULL);
  ret=ejecutacursor(lc);
  if (ret) cursordebug(lc);
  indice=ptr=calloc(1,MAXSQL);
  while ((ret=fetchcursor(lc))==0) {
        ejecutaimmediatoparam("ALTER TABLE %s DISABLE CONSTRAINT %s",tabla,constname);
        sprintf(ptr,"ALTER TABLE %s ENABLE CONSTRAINT %s",tabla,constname);
        ptr+=strlen(ptr)+1;
    }
  liberacursor(lc);
  if (ptr==indice) {
     free(indice);
     return(NULL);
   }
  *ptr++='@';
  *ptr=0;
  return(indice);
}

void recupera_indices(char *indice)
{
  char *ptr=indice;
  v10cursors *l;
  int ret;
  if (indice==NULL) return;
  while (*ptr) {
        if (VERBOSE) {
           v10log(LOGNORMAL,"Ejecutando %s\n",ptr);
         }
        l=parsecursornombre(ptr,"INDICES");
        if (l) {
           ret=ejecutacursor(l);
           if (ret) cursordebug(l);
           liberacursor(l);
         }
        ptr+=strlen(ptr)+1;
        hay_tecla();
     }
}

static char bufentrada[MAXBUFFER+10];
static int nbytes;
static int voypor;
static void resetbuffer(FILE *entrada)
{
  nbytes=voypor=0;
}

static int sigchar(FILE *entrada)
{
  if (voypor>=nbytes) {
     nbytes=fread(bufentrada,1,MAXBUFFER,entrada);
     if (nbytes==0)
        return(-1);
     voypor=0;
   }
  if (bufentrada[voypor]=='\r') {
     if (voypor>=nbytes-1) fread(bufentrada+voypor+1,1,1,entrada);
     if (bufentrada[voypor+1]=='\n') {
        voypor+=2;
        return('\n');
      }
   }
  return(bufentrada[voypor++]);
}

#define CSELTABLE "SELECT LOGGING FROM USER_TABLES WHERE TABLE_NAME=:TABLA"


long recupera(char *nombre,unsigned tambuffer,char **genconst)
{
  v10cursors *vdseltable;
  char logging[MAXLOGGING]="NO";
  exports *export;
  int nc,ret;
  long nreg;
  long nlin=1;
  long usados;
  long micommitpoint;
  char linea[255];
  char *indice=NULL,*constrainst;
  int auxnoindices;
  if ((entrada=fopenpath(nombre,"rb"))==NULL) {
     final(("No puedo abrir fichero %s\n",nombre));
   }
  fgets(linea,sizeof(linea)-1,entrada);
  export=leecabexport(linea);
  if (LOGGING) {
     vdseltable=abrecursor(CSELTABLE);
     definetodo(vdseltable,logging,sizeof(logging),V10CADENA,
                            NULL);
     bindtodo(vdseltable,"TABLA",export->nombre,strlen(export->nombre)+1,V10CADENA,
                          NULL);
     ejefetchcursor(vdseltable);
     liberacursor(vdseltable);
   }
  if (strcmp(logging,"YES")==0) {
     ejecutaimmediatoparam("ALTER TABLE %s NOLOGGING",export->nombre);
  }
  for (nc=0;nc<export->ncamp;nc++) {
      char *ptr;
      int maxlon;
      if (fgetss(linea,sizeof(linea)-1,entrada)==NULL)
         final(("Fichero %s truncado",nombre));
      nlin++;
      ptr=linea;
      export->c[nc].nombre=dupcad(&ptr);
      export->c[nc].oratipo=(unsigned)leenumero(&ptr);
      export->c[nc].oralen=(unsigned)leenumero(&ptr);
      maxlon=(unsigned)leenumero(&ptr);
      if (maxlon)  export->c[nc].oralen=maxlon;
      export->c[nc].off=(unsigned)export->lon;
      export->lon+=export->c[nc].oralen+1;
      if (stricmp(ptr,"NOIMPORT")==0) export->c[nc].noimport=1;
         else                     export->c[nc].noimport=0;
    }
  export->nelem=(unsigned)(tambuffer/export->lon);
  micommitpoint=COMMITPOINT;
  if (micommitpoint<export->nelem) micommitpoint=export->nelem;
  if (export->nelem==0) {
     final(("Registro demasiado grande %u para buffer %u\n",export->lon,tambuffer));
   }
  if (VERBOSE) {
     v10log(LOGNORMAL,"Recuperando fichero %s buffer %u reg. %ld\n",nombre,tambuffer,export->lon);
     if (VERBOSE>1) v10log(LOGNORMAL,"  Tabla %s campos %ld registros %ld elementos %u\n",export->nombre,export->ncamp,export->nreg,export->nelem);
   }
  auxnoindices=NOINDICES;
  if (export->nreg<50000) {
     NOINDICES=0;
   }
  if (NOINDICES) indice=calcula_indices(export->nombre);
  NOINDICES=auxnoindices;
  constrainst=calcula_referencias(export->nombre);
  export->buffer=calloc((unsigned)export->nelem,(unsigned)export->lon);
  genselexport(export);
  resetbuffer(entrada);
  if (export->vdc) {
     usados=0;
     ret=0;
     for (nreg=0;nreg<export->nreg;nreg++) {
         for (nc=0;nc<export->ncamp;nc++) {
             char *pcampo=export->buffer+(unsigned)(export->c[nc].off*export->nelem+usados*(export->c[nc].oralen+1));
             char *ptr;
             for (ptr=pcampo;1;ptr++) {
                 int ch;
                 if ((ch=sigchar(entrada))==EOF) {
                    final(("Fichero %s truncado en registro %ld linea %d",nombre,nreg,nlin));
                  }
                 if ((*ptr=(char)ch)==export->separador) break;
              }
             *ptr=0;
           }
         nlin++;
         if (sigchar(entrada)!='\n') {
            int c;
            v10log(LOGERROR,"Linea erronea registro %d linea %d\n",nreg,nlin);
            do {
                c=sigchar(entrada);
             } while (c!='\n' && c!=EOF);
          }
         if (ANALISIS==0) {
            if (export->nelem<=1) ret=ejecutacursor(export->vdc);
               else {
                  usados++;
                  if (usados>=export->nelem) {
                     ret=ejecutacursorarray(export->vdc,export->nelem);
                     usados=0;
                     hay_tecla();
                  }
               }
            if (ret || ((procesadascursor(export->vdc)==0) && (usados==0))) {
               cursordebug(export->vdc);
               v10log(LOGERROR,"Import de tabla %s parcialmente realizado\n",nombre);
             }
           } else usados=0;
         if (((nreg+1)%micommitpoint)==0&&VERBOSE) {
               v10log(LOGNORMAL,"Recuperados %ld registros\r",nreg);
               if (ANALISIS==0) commit();
               hay_tecla();
            }
       }
     if (usados) ret=ejecutacursorarray(export->vdc,(unsigned)usados);
     if (ret) {
        cursordebug(export->vdc);
        v10log(LOGERROR,"Import de tabla %s parcialmente realizado\n",nombre);
      }
     if (VERBOSE) v10log(LOGNORMAL,"Recuperados %ld registros\n",nreg);
     commit();
   } else {
     v10log(LOGERROR,"Import de tabla %s no realizado\n",nombre);
   }
  if (strcmp(logging,"YES")==0) {
     ejecutaimmediatoparam("ALTER TABLE %s LOGGING",export->nombre);
  }
  liberaexport(export);
  *genconst=constrainst;
  if (indice) {
     recupera_indices(indice);
     free(indice);
   }
  fclose(entrada);
  return(nreg);
}

