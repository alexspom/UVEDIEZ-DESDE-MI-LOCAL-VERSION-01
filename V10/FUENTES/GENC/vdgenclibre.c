/****
* VDGENC.C - Generación automática del código c para ejecutar consultas oracle
* 
* Propósito: Funciones comunes para la lectura e interpretación del .DEF
*           
* Autor	   : MGM
* Fecha    : 06-11-2007
****
* Modificaciones:
***/

#include "vdgenclibre.h"

#define SELTABCOLUMNS "SELECT COLUMN_NAME,DATA_TYPE, "\
                            " DATA_LENGTH,DATA_PRECISION,DATA_SCALE, "\
                            " NULLABLE,COLUMN_ID,DEFAULT_LENGTH "\
                        " FROM USER_TAB_COLUMNS "\
                        " WHERE TABLE_NAME=:TABLE_NAME AND COLUMN_NAME=:COLUMN_NAME "\
                        " ORDER BY TABLE_NAME,COLUMN_ID"
static v10cursors *vdseltabcolumns;

char include[_MAX_PATH];  
char fichero[_MAX_PATH];
char bufferficheros[LCADENABIG];
static columns column;

int soradebug;

static void fin_vd_genc(void)
{
  if (vdseltabcolumns) liberacursor(vdseltabcolumns);
}

static void init_vd_genc(void)
{
        //vdselartcodart=abrecursordebug(SELARTCODART,256);
    vdseltabcolumns=abrecursordebug(SELTABCOLUMNS,256);
    definetodo(vdseltabcolumns,column.column_name,sizeof(column.column_name),V10CADENA,
                              column.data_type,sizeof(column.data_type),V10CADENA,
                              &column.data_length,sizeof(column.data_length),V10LONG,
                              &column.data_precision,sizeof(column.data_precision),V10LONG,
                              &column.data_scale,sizeof(column.data_scale),V10LONG,
                              column.nullable,sizeof(column.nullable),V10CADENA,
                              &column.column_id,sizeof(column.column_id),V10LONG,
                              &column.default_length,sizeof(column.default_length),V10LONG,NULL);
    bindtodo(vdseltabcolumns,"TABLE_NAME",column.table_name,sizeof(column.table_name),V10CADENA,
                             "COLUMN_NAME",column.column_name,sizeof(column.column_name),V10CADENA,NULL);

    atexit(fin_vd_genc);
}

#define SEPARADORES    " =,;(){}"
#define SEPARADORCAMPO '.'
#define SEPARADORBIND  ':'
#define MAXCURSORES     100
#define MAXLINC 1000

static columns *colextra;
static cursor *cursores;
static int numcur=0;
static int numextra=0;
static char *lineash[MAXLINC];
static char *lineasc[MAXLINC];
static nlinc,nlinh;


static char * palres_genc[]={
                  "EXTRA","CURSOR","NOMBRE","SELECT","PROCEDURE","ORADEBUG", NULL
                  };

// Función que lee una linea de un fichero, descartando las comentadas con #
static char *lee_linea(char *linea,int maxlon,FILE *fich,int enfuente)
{  
    char *aux,*ret;
    while ((ret=fgetss(linea,maxlon,fich))!=NULL) {
        if (enfuente) return (ret);
        if (*linea=='#') continue;
        if ((aux=strchr(linea,'\n'))!=NULL) *aux=0;
        if (es_blanco(linea)) continue;
        sustituyedefines(linea);
        ltrim(linea);
        strcat(linea," ");
        return(ret);
    }
    return(NULL);
}

// Función que lee una línea hasta que se encuentra alguno de los separadores
static char *lee_tok(char *linea)
{
  char *aux;
  aux=linea;
  while (*aux) {
        if (strchr(SEPARADORES,*aux)==NULL) break;
        aux++;
     }
  strcpy(linea,aux);
  while (*aux) {
        if (strchr(SEPARADORES,*aux)!=NULL) break;
        aux++;
     }
  return(aux);
}

// Función que devuelve un entero si la primera palabra de la linea es significativa
static int busca_palabra(char *linea)
{
  char *aux,achar;
  int pal;
  aux=lee_tok(linea);
  achar=*aux;
  *aux=0;
  pal=0;
  while (palres_genc[pal]) {
        if (stricmp(palres_genc[pal],linea)==0) {
           if (achar) strcpy(linea,aux+1);
              else    *linea=0;
           return(pal);
         }
        pal++;
   }
  *aux=achar;
  return(-1);
}

// Función que lee hasta el siguiente separador de la línea
static void lee_nombre(char *linea,char *donde)
{
  char *aux;
  aux=lee_tok(linea);
  if (*aux==0) {
     strcpy(donde,linea);
     *linea=0;
   } else {
     *aux=0;
     strcpy(donde,linea);
     strcpy(linea,aux+1);
   }
}

// Función que lee del fichero hasta que termina la instrucción sql
static char *lee_sql(FILE *pantalla,char *linea)
{
  char *ret,*ptro,*aux;
  char term=';';
  ptro=ret=calloc(1,MAXCADENA);
  strcpy(ptro,linea);
  if (strstr(linea,"BEGIN")||strstr(linea,"DECLARE")) term='@';
  while ((aux=strchr(ptro,term))==NULL) {
        if (lee_linea(linea,MAXCADENA-1,pantalla,0)==NULL) final(("Sql sin terminar %s",ret));
        ptro+=strlen(ptro);
        if ((ptro-ret)+strlen(linea)>=MAXCADENA) final(("Sql muy largo o no terminado en ;\n%s",ret));
        strcpy(ptro,linea);
        if (*ptro==' ') ptro++;
        ltrim(ptro);
     }
  *aux=0;
  if (aux[1]==',') {
     if (es_blanco(aux+2)) {
        lee_linea(aux+2,MAXCADENA,pantalla,0);
      }
    }
  strcpy(linea,aux+1);
  ret = realloc(ret, (int)(strlen(ret) + 1));
  return(ret);
}

// Función que dependiendo del tipo oracle de la columna obtiene su equivalente C y V10
static void coviertecampocolum(columns *column){ 

    switch (column->tipo) {
	    case TIPORAW:
        case TIPOCHAR:
		case TIPOTIME: 
        case TIPOLONG:
        case TIPOVARCHAR2:strcpy(column->tipoc,"char");
                          strcpy(column->tipovd,"V10CADENA");
                          break;
        case TIPONUMBER: if (!column->data_scale && column->data_precision<=MAXDIGLON) {
                            strcpy(column->tipoc,"long");
                            strcpy(column->tipovd,"V10LONG");
                          } else {
                            strcpy(column->tipoc,"double");
                            strcpy(column->tipovd,"V10DOUBLE");
                          }
                          break;
        case TIPODATE:  strcpy(column->tipoc,"fechas");
                        strcpy(column->tipovd,"V10FECHA");
                        break;
        default:        final(("Campo %s no implementado.",column->column_name));
                        break;
    }
    
    strcpy(column->nombrec,column->column_name);
    strmin(column->nombrec);
}


// Función que recorre los campos de los cursores dandoles el formato adecuado.
static void conviertecampos(cursor *cursores){
    int i,j;

    for(i=0;i<numextra;i++){
        coviertecampocolum(&colextra[i]);
    }

    for(i=0;i<numcur;i++){
        for(j=0;j<cursores[i].numdef;j++){
          coviertecampocolum(&cursores[i].coldef[j]);
        }   
        for(j=0;j<cursores[i].numbind;j++){
          coviertecampocolum(&cursores[i].colbind[j]);
        }
    }
}

// Función que busca un campo en su tabla y añade sus propiedades
static void anade_column(columns *col)
{
    int ret;
    
    column=*col;


  /*int vdret;
  if (vdselartcodart==NULL) init_vd_art();
  memset(&svdartic,0,sizeof(svdartic));
  strcpy(svdartic.codart,codart);
  vdret=ejefetchcursor(vdselartcodart);
  if (vdret) {
    v10log(LOGDEBUG,"Ejefetch %s vdselartcodart. vdret %d. \n",ARTlog(&svdartic),vdret);
    return(VD_EERRORACLE);
   }
  *art=svdartic;
  return(vdret);*/



    if (vdseltabcolumns==NULL) init_vd_genc();
    v10log(LOGNORMAL," Buscando campo %s.%s\n",column.table_name, column.column_name);
    /*if (ejecutacursor(vdseltabcolumns)) {
        cursordebug(vdseltabcolumns);
        ret=-1;
    }else{*/
    ret=ejefetchcursor(vdseltabcolumns);
    if (!ret){
        if (stricomp(column.data_type,"CHAR")==0) {
           column.tipo=TIPOCHAR;
           column.longitud=column.data_length+1;
           column.data_scale=0;
        }
        if (stricomp(column.data_type,"VARCHAR2")==0) {
           column.tipo=TIPOVARCHAR2;
           column.longitud=column.data_length+1;
           column.data_scale=0;
        }
        if (stricomp(column.data_type,"RAW")==0) {
           column.tipo=TIPORAW;
           column.longitud=(column.data_length*2)+1;
           column.data_scale=0;
        }
        if (stricomp(column.data_type,"NUMBER")==0) {
           column.tipo=TIPONUMBER;
           column.longitud=column.data_precision+1;
        }
        if (stricomp(column.data_type,"DATE")==0) {
           column.tipo=TIPODATE;
           column.longitud=column.data_length;
        }
        if (stricomp(column.data_type,"LONG")==0) {
           column.tipo=TIPOLONG;
           column.longitud=0;
        }
        if (stricomp(column.data_type,"TIMESTAMP")==0) {
           column.tipo=TIPOTIME;
           column.longitud=column.data_length;
        }  
    }
    *col=column;
}

// Función que recorre la estructura de campos buscando sus propiedades y unificándolas en el caso
// de haber más de un campo con el mismo nombre
static void mapea_campos(void)
{
    int i,j;
    
    for (i=0;i<numextra;i++){
        if (colextra[i].table_name[0]!=0) anade_column(&colextra[i]);
    }

    for (i=0;i<cursores[numcur].numdef;i++){
       for(j=0;j<numextra;j++){
           if (!strcmp(cursores[numcur].coldef[i].column_name,colextra[j].column_name))
               cursores[numcur].coldef[i]=colextra[j];
       }
    }

    for (i=0;i<cursores[numcur].numbind;i++){
        if (cursores[numcur].colbind[i].table_name[0]==0) {
            for(j=0;j<numextra;j++){
                if (!strcmp(cursores[numcur].colbind[i].column_name,colextra[j].column_name))
                    cursores[numcur].colbind[i]=colextra[j];
            }
        }
        else anade_column(&cursores[numcur].colbind[i]);
    }

}


// Función que reemplaza una subcadena por otra en una cadena
static char *replace(char *origen, char *fin, char *cadena)
{
  	char *aux;
    char buffer[MAXCADENA];

    memset(&buffer,0,MAXCADENA);

//    while(strstr(cadena,origen)){
    	aux=strstr(cadena,origen);
        strncpy(buffer+strlen(buffer),cadena,aux-cadena);
    	strcat(buffer,fin);
        aux+=strlen(origen);
        cadena=aux;
//    }
    return strcat(buffer,aux);
}


// Función que detecta los campos bind de un cursor y busca la tabla a la que pertenecen
static char *elimina_tabla_bind(char *sql)
{
   char nombre[MAXCADENA];
   char buffer[MAXCADENA],*aux;
   char *pnombre, nombreaux[MAXCADENA],*ptabla;
   int i=0,j,repetido;

   strcpy(buffer,sql);

   while (*sql) {
       if (*sql==SEPARADORBIND){
           if (isalpha(sql[1])==0) {
               sql++;
               continue;
           }
            repetido=0;
            lee_nombre(sql,nombre);
            pnombre=strchr(nombre,SEPARADORCAMPO);
            if (pnombre==NULL) {
                strncpy(cursores[numcur].colbind[i].column_name,&nombre[1],strlen(nombre));
                i++;
                continue;
            }
            pnombre++;

            sprintf(nombreaux,"%c%s",SEPARADORBIND,pnombre);
            aux=replace(nombre,nombreaux,buffer);
            strcpy(buffer,aux);
            
            for(j=0;j<i;j++){
                if (!strcmp(cursores[numcur].colbind[j].column_name,pnombre))
                    repetido=1;
                    continue;
            }
            if (!repetido){
                strcpy(cursores[numcur].colbind[i].column_name,pnombre);
                nombre[strlen(nombre)-(strlen(pnombre)+1)]=0;
                ptabla=replace(":","",nombre);
                strcpy(cursores[numcur].colbind[i].table_name,ptabla);
                i++;
            }
       }
       if (*sql!=SEPARADORBIND) sql++;
   }
   strcpy(sql,buffer);
   return sql;
}

// Función que ejecuta el cursor que se ha definido en el fichero DEF determinanod los campos
// def y bind del mismo
static void analiza_sql(char *sql, char *nombre)
{
    v10cursors *vdseldinamica;
    char *aux;
    int i;

    cursores[numcur].coldef=calloc(MAXCOLUMNS,sizeof(columns));
    cursores[numcur].colbind=calloc(MAXCOLUMNS,sizeof(columns));
    cursores[numcur].tablas=calloc(MAXTABLES,sizeof(tables));

    aux=elimina_tabla_bind(sql);
    strcpy(sql,aux);

    strcpy(cursores[numcur].nombre,nombre);
    strcpy(cursores[numcur].nombrec,nombre);
    strmin(cursores[numcur].nombrec);
    strcpy(cursores[numcur].sql,sql);
    cursores[numcur].numcursor=numcur;
   
    vdseldinamica=abrecursor(sql);
    if (!vdseldinamica)   final(("Error en la QUERY %s.\n",sql));
    for (i=0;i<vdseldinamica->ndef;i++){
        memset(&column,0,sizeof(columns));
        strcpy(column.column_name,vdseldinamica->def[i].nombre);
        column.tipo=vdseldinamica->def[i].oratipo;
        column.longitud=vdseldinamica->def[i].oralen+1;
        column.data_precision=vdseldinamica->def[i].prec;
        column.data_scale=vdseldinamica->def[i].scale;
        cursores[numcur].coldef[i]=column;
    }
    for (i=0;i<vdseldinamica->nbind;i++){
        memset(&column,0,sizeof(columns));
        if (!strcmp(cursores[numcur].colbind[i].column_name,vdseldinamica->bind[i].nombre)) continue;
        else 
            final(("No se ha definido el campo bind %s", vdseldinamica->bind[i].nombre));
    }
    cursores[numcur].numdef=vdseldinamica->ndef;
    cursores[numcur].numbind=vdseldinamica->nbind;

    mapea_campos();
    liberacursor(vdseldinamica);
}

// Función que da de alta los campos extra definidos en el .DEF
int caracextra(char *buffer,FILE *entrada)
{
    int ret = 0, ncampos=0;
    char *pnombre,*ptabla;
    char nombre[MAXCADENA];

    memset(&column,0,sizeof(columns));
    
    lee_nombre(buffer,nombre);
    if (pnombre=strchr(nombre,SEPARADORCAMPO)) {
       pnombre++;
       ptabla=nombre;
       nombre[strlen(nombre)-(strlen(pnombre)+1)]=0;
       strcpy(column.column_name,pnombre);
       strcpy(column.table_name,ptabla);
    }
    else {
       strcpy(column.column_name,nombre);
        
       // Leemos el tipo de la columna.
       lee_nombre(buffer,column.data_type);
       // Tipo caracter
       if (stricomp(column.data_type,"V10CHAR")==0){
            column.tipo=TIPOCHAR;
            column.longitud=1;
            column.data_scale=0;
        }
        // Tipo cadena
	    if (stricomp(column.data_type,"V10CADENA")==0) {
		    column.tipo=TIPOVARCHAR2;
		    lee_nombre(buffer,nombre);
		    column.data_length=atoi(nombre);
		    column.longitud=column.data_length+1;
		    column.data_scale=0;
	    }
        // Tipo long
	    if (stricomp(column.data_type,"V10LONG")==0  ||
            stricomp(column.data_type,"V10ULONG")==0 ||
            stricomp(column.data_type,"V10INT")==0   ||
            stricomp(column.data_type,"V10UINT")==0  ||
            stricomp(column.data_type,"V10SHORT")==0 ||
            stricomp(column.data_type,"V10USHORT")==0) {
		    column.tipo=TIPONUMBER;
		    column.longitud=9;
            column.data_scale=0;
	    }

        // Tipo double
	    if (stricomp(column.data_type,"V10DOUBLE")==0 ||
            stricomp(column.data_type,"V10FLOAT")==0 ) {
		    column.tipo=TIPONUMBER;
		    column.longitud=18;
		    column.data_scale=8;
	    }
        // Tipo fecha
	    if (stricomp(column.data_type,"V10FECHA")==0) {
		    column.tipo=TIPODATE;
		    column.longitud=column.data_length;
	    }
    }
    colextra[numextra] = column;
    numextra++;

    return ret;
}

// Función que lee e interpreta el fichero .DEF
static void leefichero(char *nombre)
{
    FILE *entrada;
    char nomfichero[MAXLNOMBRE];
    char buffer[MAXCADENA];
    char tok[LCADENA],*aux;
    int pal;
    int enh=0,enc=0;
    
    
    v10log(LOGNORMAL,"Analizando fichero %s.DEF\n",nombre);
    
    colextra=calloc(MAXCOLUMNS,sizeof(columns));
    cursores=calloc(MAXCURSORES,sizeof(cursor));
    
    
    // Leemos el fichero .DEF
    sprintf(nomfichero,"%s.DEF",nombre);
    entrada=fopenpath(nomfichero,"r");
    
    if (entrada==NULL) final(("No existe el fichero %s", nomfichero));
    
    while (lee_linea(buffer,sizeof(buffer),entrada,enc+enh)) {
        if (strncmp(buffer,"%%h",3)==0) {
            enc=0;
            enh=1;
            continue;
        }
        if (strncmp(buffer,"%%c",3)==0) {
            enc=1;
            enh=0;
            continue;
        }
        if (enc) {
            lineasc[nlinc++]=strdup(buffer);
            continue;
        }
        if (enh) {
            lineash[nlinh++]=strdup(buffer);
            continue;
        }
        pal=busca_palabra(buffer);
        switch (pal){
               case GNOMBRE: strcpy(nomabreviado,lee_sql(entrada,buffer));
                             strcpy(nomabreviadoc,nomabreviado);
                             strmin(nomabreviadoc);
                             break;
               case GEXTRA:caracextra(buffer,entrada);
                           break;
               case GSELECT: aux=lee_sql(entrada,buffer);
                             lee_nombre(aux,tok);
                             analiza_sql(aux,tok);
                             cursores[numcur].tipocur=GSELECT;
                             numcur++;
                             break;
	           case GCURSOR:aux=lee_sql(entrada,buffer);
                            lee_nombre(aux,tok);
                            analiza_sql(aux,tok);
                            cursores[numcur].tipocur=GCURSOR;
                            numcur++;
                            break;
               case GPROCEDURE:aux=lee_sql(entrada,buffer);
                               lee_nombre(aux,tok);
                               analiza_sql(aux,tok);
                               cursores[numcur].tipocur=GPROCEDURE;
                               numcur++;
                               break;					   
               case GORADEBUG:  {char mioradebug[MAXNOMBREV10];
                                 lee_nombre(buffer,mioradebug);
                                 soradebug=atoi(mioradebug);
                                 break;						   
                                }
        }
  }
  
  v10log(LOGNORMAL,"Leido el fichero %s.DEF con %d cursores\n",nombre, numcur);
  fclose(entrada);
}

// Trata los parámetros propios del genclibre
static int trataparamgenclibre(char *cadena)
{
    switch (toupper(*cadena)) {
          case 'H' :strcpy(include,cadena+1);   
                    break;
          case 'F' :strcpy(bufferficheros,cadena+1);
                   break;
    }

    return(0);
}

int main(int argc,char *argv[])
{
    int i;
    trataparamstd(argc,argv,trataparamgenclibre,NULL);
    
    while (bufferficheros[0]!=0){ 
        nlinc=0;
        nlinh=0;
        numextra=0;
        numcur=0;
		soradebug=DEPURADEFECTO;
        lee_nombre(bufferficheros,fichero);
        leefichero(strmay(fichero));
        conviertecampos(cursores);
        generah(cursores,numcur,colextra,numextra,lineash,nlinh);
        generac(cursores,numcur,colextra,numextra,lineasc,nlinc);
        for (i=0;i<nlinc;i++) free(lineasc[i]);
        for (i=0;i<nlinh;i++) free(lineash[i]);
    }
    return(0);
}


int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hprev,
           LPSTR cmd, int cmdshow)
{
  int ret;
  v10hinst=hinst;
  v10hprev=hprev;
  trataparamstd(__argc,__argv,trataparampremain,NULL);
  initapptxt(hinst,hprev,SW_SHOWMAXIMIZED,TITULOVENTANA,CW_USEDEFAULT,CW_USEDEFAULT,
                   0,0,COLUMNASPANTALLA,LINEASPANTALLA,ESTILOV10,0,NULL,0,0,NULL);
  trataparamstd(__argc,__argv,trataparammain,trataparamoracle,NULL);
  ret=main(__argc,__argv);
  return(ret);
}