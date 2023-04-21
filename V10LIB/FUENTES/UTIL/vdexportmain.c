
#include "forms/v10form.h"

                                                                    
static char *constraint=NULL,*totconstraint=NULL;
static int lonconstraint=0;
static int comando;
void analiza_comando(char **where,char **param,char **nfichero,char *cadena);

/* Uso:
    export user/pwd comando opciones
    comando E export
            I import
    opciones U         exporta/importa usuario
             Ttabla    exporta/importa tabla
             Snumero   define separador como codigo ascii
             Cnumero   define nivel de compresion
                       0 Tabulado con blancos
                       1 sin blancos y campos separados por SEPARADOR
             Vnumero   Cantidad de informacion que da
             Hnumero   Tipo de cabecera.
             Bnumero   Tama¤o buffer array fetch
*/

void anadeconstraint(void)
{ 
   if (constraint) {
     if (totconstraint==NULL) {
        totconstraint=constraint;
        lonconstraint=strlen(totconstraint);
      } else {
        totconstraint=realloc(totconstraint,lonconstraint+strlen(constraint));
        strcat(totconstraint,constraint);
      }
   }
}

void uso(void)
{
  windows w;
  initvn(&w,1,1,COLUMNASPANTALLA-2,LINEASPANTALLA-2,"DEFECTO");
  enmarca(&w,0,"Uso del export");
  v10printf(&w,"Uso:\n  export user/pwd comando opciones\n"
             "   comando E export\n"
             "           I import\n"
             "   opciones U          exporta/importa usuario\n"
             "            Anumero    1 Solo analisis del fichero a importar no realizar el import 0 normal\n"
             "            Ttabla     exporta/importa tabla\n"
             "            Snumero    define separador como codigo ascii\n"
             "            Cnumero    define nivel de compresion\n"
             "                       0 Tabulado con blancos\n"
             "                       1 sin blancos y campos separados por SEPARADOR\n"
             "            Vnumero    Cantidad de informacion que da\n"
             "            Hnumero    Tipo de cabecera.\n"
             "                       0 Sin cabecera\n"
             "                       1 Con cabecera\n"
             "            Bnumero    Tamaño buffer array fetch por defecto 500000 bytes\n"
             "            Ffichero   Nombre fichero destino \n"
             "            Pcadena    Parametros que se pasan a la select\n"
             "                       De la forma Variable=Valor ... Variable=valor\n"
             "            Wcadena    Where que se pasa al export tabla\n"
             "            XSelect    hace export de la select\n"
             "            Nnumero    Indica si borrar indices antes de inport\n"
             "                       0 No borrar indices al importar\n"
             "                       1 Borrar indices y crearlos al final\n"
             "            R          Indica que el export ha de ser consistente entre todas las tablas\n"
             "            Ynombre    Da el nombre de tabla sobre todo util para export de una select\n"
             "            Lnumero    Indica si se ha de poner en modo NOLOGGING para hacer el import\n"
             "            Osentencia Ejecuta la sentencia SQL\n"
             "            D          Pone en modo Debug\n"
             "            @fichero   Procesa el fichero como parametros (ojo los comandos deben empezar linea y estar precedidos de /)");
    tecla();
    exit(1);
}

char *lee_linea(char *cadena,unsigned len,FILE *entrada)
{
  char *aux;
  if (fgets(cadena,len,entrada)==NULL) return(NULL);
  if ((aux=strchr(cadena,'\n'))!=NULL) *aux=0;
  return(cadena);
}

void lee_fichero(char *nombre,char **where,char **param,char **nfichero)
{
    FILE *entrada;
    char *linea,*ptr;
    if ((entrada=fopenpath(nombre,"r"))==NULL) {
        final(("No puedo abrir %s\n",nombre));
    }
    ptr=linea=calloc(1,MAXCADENA);
    while (lee_linea(ptr,MAXCADENA-strlen(linea),entrada)) {
        if (*ptr=='/') {
            if (ptr>linea) {
                *ptr=0;
                analiza_comando(where,param,nfichero,linea+1);
                *ptr='/';
                strcpy(linea,ptr);
                ptr=linea;
            }
        }
        ptr+=strlen(ptr);
    }
    if (ptr>linea) analiza_comando(where,param,nfichero,linea+1);
    free(linea);
}

void analiza_comando(char **where,char **param,char **nfichero,char *cadena)
{
    switch (*cadena) {
       case '@':lee_fichero(cadena+1,where,param,nfichero);
           break;
       case 'E':comando=EXPORT;
           break;
       case 'I':comando=IMPORT;
           break;
       case 'A': ANALISIS=atoi(cadena+1);
           break;
       case 'U':if (comando==EXPORT) {
                   exportuser(*where,*param);
                 } else {
                   importuser(&constraint);
                   anadeconstraint();
                 }
                break;
       case 'W':if (*where) free(*where);
           if (es_blanco(cadena+1)) *where=NULL;
           else *where=strdup(cadena+1);
           break;
       case 'F':if (*nfichero) free(*nfichero);
           if (es_blanco(cadena+1)) *nfichero=NULL;
           else *nfichero=strdup(cadena+1);
           *nfichero=strdup(cadena+1);
           break;
       case 'P':if (*param) free(*param);
           if (es_blanco(cadena+1)) *param=NULL;
           else *param=strdup(cadena+1);
           *param=strdup(cadena+1);
           break;
       case 'T':if (comando==EXPORT) {
                   exporttabla(cadena+1,*where,*param,*nfichero);
                 } else {
                   recupera(cadena+1,TAMBUFFER,&constraint);
                   anadeconstraint();
                 }
                break;
       case 'S':EXSEPARADOR=(char)atoi(cadena+1);
           break;
       case 'X':export(cadena+1,*nfichero,NOMBRETABLA,*param,TAMBUFFER);
           break;
       case 'C':COMPRESS=atoi(cadena+1);
           break;
       case 'V':VERBOSE=atoi(cadena+1);
           break;
       case 'H':HEADERS=atoi(cadena+1);
           break;
       case 'B':TAMBUFFER=(unsigned)atol(cadena+1);
           break;
       case 'N':NOINDICES=(unsigned)atol(cadena+1);
           break;
       case 'R':ejecutaimmediato("SET TRANSACTION READ ONLY");
           v10log(LOGNORMAL,"Export consistente\n");
           break;
       case 'O':ejecutaimmediato(cadena+1);
           v10log(LOGNORMAL,"Ejecutada la sentencia ORACLE %s\n",cadena+1);
           break;
       case 'D':oradebug=1;
           v10log(LOGNORMAL,"Puesto ORACLE en modo debug\n");
           break;
       case 'L':LOGGING=atoi(cadena+1);
                break;
       case 'Y':strcpy(NOMBRETABLA,cadena+1);
                break;
    }
}
static void creaconstraints(char *indice)
{
  char *ptr=indice;
  v10cursors *l;
  int ret;
  if (indice==NULL) return;
  while (*ptr) {
        char *aux;
        aux=strchr(ptr,'@');
        if (aux) *aux=0;
        if (VERBOSE) {
           v10log(LOGNORMAL,"Ejecutando %s\n",ptr);
         }
        if (strlen(ptr)) {
           l=parsecursornombre(ptr,"CREAINDEX");
           if (l) {
              ret=ejecutacursor(l);
              if (ret) cursordebug(l);
              liberacursor(l);
            }
         }
        ptr+=strlen(ptr);
        if (aux) ptr++;
        hay_tecla();
     }
}

int main(int argc,char *argv[])
{
  int ncomando;

  char *where=NULL,*param=NULL,*nfichero=NULL;
	strcpy(TITULOVENTANA,"IMPORTACION DE FICHEROS EXCEL 1.0");
	LINEASPANTALLA=50;
	COLUMNASPANTALLA=140;
//    v10translate=traduce;
	initv10lib(v10hinst,v10hprev);
  trataparamstd(argc,argv,trataparammain,trataparamoracle,NULL);
  v10usaansi=1;
  if (argc<4) uso();
  ORATECLA=0;
  ejecutaimmediato("ALTER SESSION SET NLS_NUMERIC_CHARACTERS=',.'");
  asignatecla(ALT('D'),toggleoradebug);
  initv10log("VDEXPORT.LOG");
  for (ncomando=1;ncomando<argc;ncomando++) {
     analiza_comando(&where,&param,&nfichero,argv[ncomando]);
   }
  if (where) free(where);
  if (param) free(param);
  if (nfichero) free(nfichero);
  if (totconstraint) {
     creaconstraints(totconstraint);
   }
  return(0);
}
#ifndef __LINUX__

int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hprev,
           LPSTR cmd, int cmdshow)
{
  int ret;
  strcpy(TITULOVENTANA,"VDEXPORT 1.0");
  initv10lib(hinst,hprev);
  trataparamstd(__argc,__argv,trataparammain,trataparamoracle,NULL);
  ret=main(__argc,__argv);
  return(ret);
}
#endif
