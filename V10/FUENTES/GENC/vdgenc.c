/****
* VDGENC.C - Generación automática del código c para acceder a una tabla.
* 
* Propósito: Funciones comunes para la lectura e interpretación del .DEF
*           
* Autor	   : MGM
* Fecha    : 20-10-2007
****
* Modificaciones:
***/

#include "vdgenc.h"

#define MAXPRECDOUBLE 15

#define SELTABCOLUMNS "    SELECT COLUMN_NAME,DATA_TYPE, "\
                      "           DATA_LENGTH,DATA_PRECISION,DATA_SCALE, "\
                      "           NULLABLE,COLUMN_ID,DEFAULT_LENGTH "\
                      "      FROM USER_TAB_COLUMNS "\
                      "     WHERE TABLE_NAME=:TABLE_NAME "\
                      "  ORDER BY TABLE_NAME,COLUMN_ID"
static v10cursors *vdseltabcolumns;

#define SELPKCOLUMNS "     SELECT B.COLUMN_NAME "\
                     "     FROM USER_CONSTRAINTS A, "\
                     "          USER_CONS_COLUMNS B, "\
					 "          USER_TAB_COLUMNS C "\
                     "     WHERE A.TABLE_NAME = :TABLE_NAME AND "\
					 "           A.CONSTRAINT_TYPE = 'P' AND "\
					 "           A.CONSTRAINT_NAME = B.CONSTRAINT_NAME AND "\
					 "           A.TABLE_NAME = C.TABLE_NAME AND "\
					 "           B.COLUMN_NAME = C.COLUMN_NAME "\
                     "     ORDER BY C.COLUMN_ID "
static v10cursors *vdselpkcolumns;

static columns column;
static tablas  stabla;

char include[_MAX_PATH];      
char buffertablas[LCADENA];


static void fin_vd_genc(void)
{
  if (vdseltabcolumns) liberacursor(vdseltabcolumns);
  if (vdselpkcolumns)  liberacursor(vdselpkcolumns);
}


static void init_vd_genc(void)
{
    vdseltabcolumns=abrecursor(SELTABCOLUMNS);
    definetodo(vdseltabcolumns,column.column_name,sizeof(column.column_name),V10CADENA,
                              column.data_type,sizeof(column.data_type),V10CADENA,
                              &column.data_length,sizeof(column.data_length),V10LONG,
                              &column.data_precision,sizeof(column.data_precision),V10LONG,
                              &column.data_scale,sizeof(column.data_scale),V10LONG,
                              column.nullable,sizeof(column.nullable),V10CADENA,
                              &column.column_id,sizeof(column.column_id),V10LONG,
                              &column.default_length,sizeof(column.default_length),V10LONG,NULL);
    bindtodo(vdseltabcolumns,"TABLE_NAME",stabla.table_name,sizeof(stabla.table_name),V10CADENA,NULL);

    vdselpkcolumns=abrecursor(SELPKCOLUMNS);
    definetodo(vdselpkcolumns,column.column_name,sizeof(column.column_name),V10CADENA,NULL);
    bindtodo(vdselpkcolumns,"TABLE_NAME",stabla.table_name,sizeof(stabla.table_name),V10CADENA,NULL);

    atexit(fin_vd_genc);
}


static char * palres_genc[]={
                  "TABLE", "CLAVE", "LOCK", "NOWAIT", "NOWHERE", "SELECT",
                  "WHERE", "ORDERBY", "GENCOUNT", "GENMAX", "GENMIN", "GENSUM","GROUPBY", 
                  "NORET", "RECORRE", "RECORREPROC", "UPDATE", "UPDATEDEF",
                  "SECUENCIA", "EXTRA", "AMPLIAPI", "INSERT", "DELETE", "PRIMARIA","ORADEBUG","ROWID",
                  "INTERFASE", NULL
                  };

#define GTABLE       0
#define GCLAVE       1
#define GLOCK        2
#define GNOWAIT      3
#define GNOWHERE     4
#define GSELECT      5
#define GWHERE       6
#define GORDER       7
#define GCOUNT       8    
#define GMAX         9
#define GMIN         10
#define GSUM         11
#define GGROUPBY     12
#define GNORET       13
#define GRECORRE     14
#define GRECORREPROC 15
#define GUPDATE      16
#define GUPDATEDEF   17
#define GSECUEN      18
#define GEXTRA       19
#define GAMPLIAPI    20
#define GINSERT      21
#define GDELETE      22
#define GPRIMARIA    23
#define GORADEBUG    24
#define GROWID       25
#define GINTERFASE   26


#define CAMPOSSTD "FECMODIF HORAMODIF CODOPEMODIF MODULOMODIF ACCIONMODIF"
#define SEPARADORES    " =,;(){}"
#define SEPARADORCAMPO '.'


// Función que añade las columnas definidas en ORACLE a la estructura de tabla
int anade_columns(tablas *tabla)
{
  int ret = 0;

  sprintf(tabla->aplicacion,"%-*.*s",LAPLICACION-1,LAPLICACION-1,tabla->table_name);
  sprintf(tabla->ntypedef,"%ss",tabla->table_name);
  strmin(tabla->ntypedef);
  sprintf(tabla->nstatic,"s%s",tabla->table_name);
  strmin(tabla->nstatic);
  strcpy(tabla->nombrec,tabla->table_name);
  strmin(tabla->nombrec);

  if (!vdseltabcolumns) init_vd_genc();
  v10log(LOGNORMAL," Buscando columnas de la tabla %s...\n",tabla->table_name);
  if (ejecutacursor(vdseltabcolumns)) {
     cursordebug(vdseltabcolumns);
     ret=-1;
   }else {
     memset(&column,0,sizeof(columns));
     tabla->numcol=0;
     tabla->col=calloc(MAXCOLUMNS,sizeof(columns));
     while (fetchcursor(vdseltabcolumns)==0) {
           strcpy(column.nombrec,column.column_name);
           strmin(column.nombrec);
		   column.tabla=1;
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
			   if (column.data_precision<=MAXPRECDOUBLE) {
				   column.tipo=TIPONUMBER;
                   column.longitud=column.data_precision+1;
			   } else {
                   column.tipo=TIPOVARCHAR2;
                   column.longitud=column.data_precision+2;
			   }
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
       switch (column.tipo) {
		         case TIPORAW:
                 case TIPOCHAR:
				 case TIPOTIME: 
                 case TIPOLONG:
                 case TIPOVARCHAR2:strcpy(column.tipoc,"char");
                                   strcpy(column.tipovd,"V10CADENA");
                                   break;
                 case TIPONUMBER: if (!column.data_scale && column.data_precision<=MAXDIGLON) {
                                     strcpy(column.tipoc,"long");
                                     strcpy(column.tipovd,"V10LONG");
                                   } else {
                                     strcpy(column.tipoc,"double");
                                     strcpy(column.tipovd,"V10DOUBLE");
                                   }
                                  break;
                  case TIPODATE:  strcpy(column.tipoc,"fechas");
                                  strcpy(column.tipovd,"V10FECHA");
                                  break;
                  default:        final(("Tipo %d no implementado.",column.tipo));
                                  break;
            }
           if (!column.longitud) warning(("Tipo %s no puedo calcular longitud",column.data_type));
           tabla->col[tabla->numcol]=column;
           tabla->numcol++;
           tabla->numcolorig++;
           if (tabla->numcol>MAXCOLUMNS) final(("MAXCOLUMNS pequeno"));
           v10log(LOGNORMAL,"   COLUMN: %s\n",column.column_name);
           memset(&column,0,sizeof(columns));
      }
  }
  return(ret);
}


// Función que lee una linea de un fichero, descartando las comentadas con #
static char *lee_linea(char *linea,int maxlon,FILE *fich)
{ char *aux,*ret;
  while ((ret=fgets(linea,maxlon,fich))!=NULL) {
        if (*linea=='#') continue;
        if ((aux=strchr(linea,'\n'))!=NULL) *aux=0;
        sustituyedefines(linea);
        ltrim(linea);
        if (linea[strlen(linea)-1]!=';') 
            strcat(linea," ");
        return(ret);
     }
  return(NULL);
}


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

static int busca_paltok(char *tok)
{
  int pal;
  pal=0;
  while (palres_genc[pal]) {
        if (stricmp(palres_genc[pal],tok)==0) {
           return(pal);
         }
        pal++;
   }
  return(-1);
}

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

columns *busca_columna(tablas *tabla,char *nombre)
{
    int nc;
    char *ptr;
    char minus[MAXLNOMBRE];
     //permitir joins con proyecciones prefijadas. 
    //Los wheres deben escribirse manualmente para no complicar el análisis
    if (ptr=strchr(nombre,SEPARADORCAMPO)) ptr++;
    else ptr=nombre;  
    
    strcpy(minus,ptr);
    strmin(minus);
    for (nc=0;nc<tabla->numcol;nc++) {
      if (strcmp(minus,tabla->col[nc].nombrec)==0) {
         return(tabla->col+nc);
      }
    }
    if (!strcmp(minus,"mirowid")) return NULL;
    final(("Columna %s no existe en tabla %s",nombre,tabla->table_name));
    return(NULL);
}

static char *lee_sql(FILE *pantalla,char *linea)
{
  char *ret,*ptro,*aux;
  char term=';';
  ptro=ret=calloc(1,MAXCADENA);
  strcpy(ptro,linea);
  if (strstr(linea,"BEGIN")||strstr(linea,"DECLARE")) term='@';
  while ((aux=strchr(ptro,term))==NULL) {
        if (lee_linea(linea,MAXCADENA-1,pantalla)==NULL) final(("Sql sin terminar %s",ret));
        ptro+=strlen(ptro);
        if ((ptro-ret)+strlen(linea)>=MAXCADENA) final(("Sql muy largo o no terminado en ;\n%s",ret));
        strcpy(ptro,linea);
        if (*ptro==' ') ptro++;
        ltrim(ptro);
     }
  *aux=0;
  if (aux[1]==',') {
     if (es_blanco(aux+2)) {
        lee_linea(aux+2,MAXCADENA,pantalla);
      }
    }
  strcpy(linea,aux+1);
  ret=realloc(ret,(int)(strlen(ret))+1);
  return(ret);
}

static void lee_nombre(char *linea,char *donde,FILE *entrada)
{
  char *aux;
  aux=lee_tok(linea);
  if (*aux==0) {
     strcpy(donde,linea);
     *linea=0;
   } else {
     if (*aux==',') {
        if (es_blanco(aux+1)) {
           lee_linea(aux+1,MAXCADENA,entrada);
         }
      }
     *aux=0;
     strcpy(donde,linea);
     strcpy(linea,aux+1);
   }
}

static void lee_tabla(char *tablas, char *tabla)
{
  char *aux;
  aux=lee_tok(tablas);
  if (*aux==0) {
     strcpy(tabla,tablas);
     *tablas=0;
   } else {
     *aux=0;
     strcpy(tabla,tablas);
     strcpy(tablas,aux+1);
   }
}

columns *busca_columnaextra(defselects *s,char *nombre)
{
  int nc;
  char minus[MAXLNOMBRE];
  strcpy(minus,nombre);
  strmin(minus);
  for (nc=0;nc<s->numcolselect;nc++) {
      if (strcmp(minus,s->colselect[nc]->nombrec)==0) return(s->colselect[nc]);
    }
  return(NULL);
}

static void proyectacamposextra(tablas *tabla,defselects *s,FILE *entrada)
{
    int pal;
    char nombre[MAXLNOMBRE];    
    char *dupselect=strdup(s->select);
    int n=0;
    
    s->colselect=calloc(MAXCOLUMNS,sizeof(columns *));
    while (*dupselect) {
        columns *c;
        lee_nombre(dupselect,nombre,entrada);
        pal=busca_paltok(nombre);
        if (pal==-1) {
           c=busca_columna(tabla,nombre);
           s->colselect[s->numcolselect]=c;
           s->numcolselect++;
         } 
    }
    free(dupselect);
}

void liberatabla(tablas *tabla)
{
  int ns;
  if (tabla->col)      free(tabla->col);
  if (tabla->primaria) free(tabla->primaria);
  for (ns=0;ns<tabla->numsel;ns++) {
      defselects *s=tabla->sel+ns;
      if (s->col) free(s->col);
    }
  for (ns=0;ns<tabla->numup;ns++) {
      defupdates *s=tabla->up+ns;
      if (s->col) free(s->col);
    }
  memset(tabla,0,sizeof(tablas));
}

void concat_lista_campos(char **dest,char *orig,char *separador){

  char nommaxmin[MAXLNOMBRE],*pnombre,*plistanomb;

  plistanomb = orig;
  pnombre=lee_tok(plistanomb);

  while(*plistanomb){
	  memcpy(nommaxmin,plistanomb,(pnombre-plistanomb));
	  nommaxmin[pnombre-plistanomb]=0;
	  if (!*dest || !strstr(*dest,nommaxmin)){ //Si ya existe en la lista, no lo añadimos.
		  if (*dest) {
              *dest = realloc(*dest, (int)(strlen(*dest) + strlen(nommaxmin)) + 2);
			strcat(*dest,separador);
          }
          else *dest = malloc((int)(strlen(nommaxmin) + 2));
		  strcat(*dest,nommaxmin);
	  }
	  plistanomb = pnombre;
	  if (*plistanomb) plistanomb++;
	  pnombre=lee_tok(plistanomb);
  }
}

void quitablancos(char *texto){
	char *ptexto=texto;
	while(*ptexto) {
		if (*ptexto==' ') strcpy(ptexto,ptexto+1);
		else ptexto++;
	}
	_strupr(texto);
}

static void campos_bind(tablas *tabla, char *buffer, FILE *entrada, columns **col, int *psolobind, int *numcol)
{
   char nombre[MAXLNOMBRE];
   int i,len;    
   int solobind=0;
   char *aux;

   while(*buffer){
        buffer=strchr(buffer,':');
        if (buffer!=NULL) buffer++;
        if (buffer==NULL) return;
        aux=lee_tok(buffer);
        len = (int)(strlen(buffer) - strlen(aux));
        strncpy(nombre,buffer,len);
        nombre[len]=0;


        for (i=0;i<*numcol;i++){
            if (!strcmp(col[i]->column_name,nombre)){
                solobind=1;
                break;
            }
        }
        if(!solobind){
            columns *c;
            c=busca_columna(tabla,nombre);
            //c->solobind=1;
            psolobind[*numcol]=1;
            col[*numcol]=c;
            *numcol=*numcol+1;
            solobind=0;
        }
   }
}




// Función que interpreta las caracteristicas de una query de tipo clave definidas en el .DEF
void caracclave(tablas *tabla,defselects *s,char *buffer,FILE *entrada)
{
  int pal,i=0;
  char nombre[2*MAXLNOMBRE];
  char nommaxmin[MAXLNOMBRE],*plistanomb;

  strcpy(s->nombrec,s->nombre);
  strmin(s->nombrec);
  while ((pal=busca_palabra(buffer))!=-1) {
        switch (pal) {
           case GLOCK:s->lock=1;
                      pal=-1;
                       break;
           case GNOWAIT:s->nowait=1;
                       pal=-1;
                       break;
         }
        if ((pal==GNOWHERE)) {
            pal=-1;
            break;
        }else if (pal!=-1) break;

    }
  s->col=calloc(MAXCOLUMNS,sizeof(columns *));
  while (*buffer) {
        columns *c;
        int palaux;
        if(pal==-1 || i!=0){
            lee_nombre(buffer,nombre,entrada);
	    	if (*nombre==0) continue;
		    palaux=busca_paltok(nombre);
            if (palaux==-1) {
               c=busca_columna(tabla,nombre);
               s->col[s->numcol]=c;
               s->numcol++;
            }
        }else palaux=pal;

        if(palaux!=-1) {
           switch (palaux) {
             case GTABLE:s->table=lee_sql(entrada,buffer);
                         break;
             case GSELECT:s->select=lee_sql(entrada,buffer);
                          proyectacamposextra(tabla,s,entrada); 
                          break;
             case GWHERE:s->where=lee_sql(entrada,buffer);
                         campos_bind(tabla,s->where,entrada,s->col,s->solobind,&s->numcol);
                         break;
             case GORDER:s->order=lee_sql(entrada,buffer);
                         break;
             case GCOUNT: s->gencount=lee_sql(entrada,buffer);
                          tabla->gencount=s->gencount;
                          tabla->numcount=1;
         				  break;
             case GMAX:s->genmax=lee_sql(entrada,buffer);
					   quitablancos(s->genmax);
					   concat_lista_campos(&tabla->genmax,s->genmax,",");
                       plistanomb=s->genmax;
                       while (damecampomaxmin(nommaxmin,&plistanomb)) tabla->numagrup++;
        			   break;
             case GMIN:s->genmin=lee_sql(entrada,buffer);
						  quitablancos(s->genmin);
						  concat_lista_campos(&tabla->genmin,s->genmin,",");
                          plistanomb=s->genmin;
                          while (damecampomaxmin(nommaxmin,&plistanomb)) tabla->numagrup++;
        			     break;
             case GSUM: s->gensum=lee_sql(entrada,buffer);
                        tabla->gensum=s->gensum;
                        tabla->numsum=1;
         				break;
             case GGROUPBY:s->groupby=lee_sql(entrada,buffer);
						   quitablancos(s->groupby);
                           break;
			 case GNORET:s->noretvd=1;
                         break;
            }
        }
        i++;
  }
}

// Función que obtiene y guarda en la estructura tabla las características de la clave primaria.
void caracupdatedef(tablas *tabla, defupdates *u)
{
	int i,j,upd=0;
    // Creamos el update de todos los campos salvo los de clave primaria
	strcpy(u->nombrec,tabla->table_name);
	strmin(u->nombrec);
    u->col=calloc(MAXCOLUMNS,sizeof(columns *));
    for (i=0;i<tabla->numcol;i++) {
		if(!tabla->col[i].tabla) continue;
		if (strstr(CAMPOSSTD, tabla->col[i].column_name)) continue;
		upd=0;
		for(j=0;j<tabla->numprimaria;j++){
			if (!strcmp(tabla->col[i].column_name,tabla->primaria[j]->column_name)) upd=1;
		}
		if (!upd){
			u->col[u->numcol]=tabla->col+i;
			u->numcol++;
		}
    }
}

// Función que interpreta las caracteristicas de una query de tipo update definidas en el .DEF
void caracupdate(tablas *tabla,defupdates *u,char *buffer,FILE *entrada)
{
  char nombre[MAXLNOMBRE];
  strcpy(u->nombrec,u->nombre);
  strmin(u->nombrec);
  u->col=calloc(MAXCOLUMNS,sizeof(columns *));
  if (!*buffer) caracupdatedef(tabla, u);
  while (*buffer) {
        columns *c;
        lee_nombre(buffer,nombre,entrada);
        c=busca_columna(tabla,nombre);
        u->col[u->numcol]=c;
        u->numcol++;
    }
}

// Función que interpreta las caracteristicas de una query de tipo secuencia definidas en el .DEF
void caracsecuen(tablas *tabla,defsecuens *s,char *buffer,FILE *entrada)
{
  char nombre[MAXLNOMBRE];
  strcpy(s->nombrec,s->nombre);
  strmin(s->nombrec);
  lee_nombre(buffer,nombre,entrada);
  s->col=busca_columna(tabla,nombre);
  if (strcmp(s->col->tipoc,"long")!=0) final(("Secuencia %s va a %s no long",s->nombre,s->col->nombrec));
}

// Función que da de alta los campos extra definidos en el .DEF
int caracextra(tablas *tabla,char *buffer,FILE *entrada)
{
	int ret = 0;
	char nombre[MAXLNOMBRE];
    // Leemos el nombre del campo extra
	lee_nombre(buffer,column.column_name,entrada);
	strcpy(column.nombrec,column.column_name);
	strmin(column.nombrec);
	column.tabla=0;
    // Leemos el tipo del campo extra
	lee_nombre(buffer,column.data_type,entrada);
    // Tipo puntero
    if (stricomp(column.data_type,"VOIDPTR")==0) {
        sprintf(column.nombrec,"(*%s)(void *)",column.column_name);
        strmin(column.nombrec);
		column.tipo=TIPOVOIDPTR;
		column.longitud=sizeof(void *);
	}
    // Tipo caracter
    if (stricomp(column.data_type,"V10CHAR")==0){
        column.tipo=TIPOCHAR;
        column.longitud=1;
        column.data_scale=0;
    }
    // Tipo cadena
	if (stricomp(column.data_type,"V10CADENA")==0) {
		column.tipo=TIPOVARCHAR2;
		lee_nombre(buffer,nombre,entrada);
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
	switch (column.tipo) {
	    case TIPOVARCHAR2:strcpy(column.tipoc,"char");
	                     strcpy(column.tipovd,"V10CADENA");
		                 break;
	    case TIPONUMBER: if (!column.data_scale) {
		                     strcpy(column.tipoc,"long");
		                     strcpy(column.tipovd,"V10LONG");
                         } else {
						     strcpy(column.tipoc,"double");
						     strcpy(column.tipovd,"V10DOUBLE");
                         }
					     break;
	    case TIPODATE:   strcpy(column.tipoc,"fechas");
		                 strcpy(column.tipovd,"V10FECHA");
		                 break;
        case TIPOVOIDPTR: strcpy(column.tipoc,"int");
                          strcpy(column.tipovd,"V10INT");
                          break;
	    default:         final(("Tipo %d no implementado.",column.tipo));
		             break;
	}
	if (!column.longitud) warning(("Tipo %s no puedo calcular longitud",column.data_type));
	tabla->col[tabla->numcol]=column;
	tabla->numcol++;
	if (tabla->numcol>MAXCOLUMNS) final(("MAXCOLUMNS pequeno"));
    v10log(LOGNORMAL,"  COLUMN: %s\n",column.column_name);
	memset(&column,0,sizeof(columns));
	return(ret);
}

// Función que interpreta las caracteristicas de una query por rowid
void caracrowid(tablas *tabla,defselects *s,char *buffer,FILE *entrada)
{
    s->col=calloc(MAXCOLUMNS,sizeof(columns *));
    memset(s->col,0,sizeof(s->col));
    strcpy(tabla->sel[tabla->numsel].nombre,"ROWID");
    strcpy(s->nombrec,tabla->sel[tabla->numsel].nombre);
    strmin(s->nombrec);
    strcpy(buffer,"MIROWID,V10CADENA,ROWIDLON");
    caracextra(tabla, buffer, entrada);
    s->where="ROWID=:MIROWID";
    campos_bind(tabla,s->where,entrada,s->col,s->solobind,&s->numcol);
}

// Función que guarda como clave primaria en la estructura los campos que se indican en el fichero.
void caracprimaria(tablas *tabla,char *buffer,FILE *entrada)
{
  char nombre[MAXLNOMBRE];
  
  tabla->primaria=calloc(MAXCOLUMNS,sizeof(columns *));
  while (*buffer) {
        columns *c;
        lee_nombre(buffer,nombre,entrada);
        c=busca_columna(tabla,nombre);
        tabla->primaria[tabla->numprimaria]=c;
        tabla->numprimaria++;
    }
}

// Función que obtiene y guarda en la estructura tabla las características de la clave primaria.
void caracprimariadef(tablas *tabla)
{
	defselects *s=tabla->sel+tabla->numsel;
    int i, nprimaria = 0;

    if (!tabla->numprimaria)
        tabla->primaria=calloc(MAXCOLUMNS,sizeof(columns *));

    if (!vdselpkcolumns) init_vd_genc();
    v10log(LOGNORMAL," Buscando columnas de la clave primaria de la tabla %s...\n",tabla->table_name);

	// Creamos la query de clave primaria 
	tabla->sel[tabla->numsel].recorre=0;
    tabla->sel[tabla->numsel].recorreproc=0;
	strcpy(s->nombre,tabla->table_name);
	strcpy(s->nombrec,s->nombre);
    strmin(s->nombrec);
    s->col=calloc(MAXCOLUMNS,sizeof(columns *));
    
	if (ejecutacursor(vdselpkcolumns)){
		cursordebug(vdselpkcolumns);
	} else {
		memset(&column,0,sizeof(columns));
        while (fetchcursor(vdselpkcolumns)==0){
			columns *c;
            int existe=0;
			c=busca_columna(tabla,column.column_name);

            for (i=0;i<tabla->numprimaria;i++){
                if (!strcmp(tabla->primaria[i]->column_name,column.column_name)) existe=1;
            }
            if (!existe){
			    // Incluimos la clave primaria
			    tabla->primaria[tabla->numprimaria]=c;
			    tabla->numprimaria++;
            }
    	    // Generamos la query por clave primaria
	    	s->col[s->numcol]=c;
            s->solobind[s->numcol]=0;
			s->numcol++;  
            nprimaria++;
        } 
        if (!nprimaria){
            for (i=0;i<tabla->numprimaria;i++){
   //             columns *c;
                s->col[s->numcol]=tabla->primaria[i];
                s->solobind[s->numcol]=0;
		     	s->numcol++;
                //c=busca_columna(tabla,tabla->primaria[i]->column_name);
            }
        }
		tabla->numsel++;
	}
}




// Función que lee el fichero .DEF y determina las cara
int leefichero(tablas *tabla,char *table_name)
{
  FILE *entrada;
  char buffer[MAXCADENA];
  char nombre[MAXPATH];

  //Obtenemos el nombre del fichero .DEF que vamos a leer.
  while (strchr(table_name,'\\')) strcpy(table_name,strchr(table_name,'\\')+1);
  if (strstr(table_name,".DEF")) *strstr(table_name,".DEF")=0;
  v10log(LOGNORMAL,"Analizando fichero %s.DEF\n",table_name);
  strcpy(tabla->table_name,table_name);
  strcpy(nombre,table_name);
  strcat(nombre,".DEF");

  // Añadimos los campos de columna a la tabla
  anade_columns(tabla);

  // Leemos el fichero .DEF e incluye sus características en la estructura TABLA.
  entrada=fopenpath(nombre,"r");
  if (entrada==NULL) {
      mensajefcm(10,"No existe fichero %s",nombre);
      return(-1);
  }
  while (lee_linea(buffer,sizeof(buffer),entrada)) {
        int pal;
        if (*buffer=='#') continue;
        if (es_blanco(buffer)) continue;
        pal=busca_palabra(buffer);
        switch (pal){
               case GPRIMARIA:caracprimaria(tabla,buffer,entrada);
                              break;
	           case GTABLE:lee_nombre(buffer,tabla->abreviado,entrada);
				           tabla->numdic=1;
				           strcpy(tabla->ntypedeforig,tabla->ntypedef);
						   strcpy(tabla->nstaticorig,tabla->nstatic);
						   strcpy(tabla->nombrecorig,tabla->nombrec);
						   strcpy(tabla->abreviadoorig,tabla->abreviado);
                           strcpy(tabla->abreviadoc,tabla->abreviado);
                           strcpy(tabla->abreviadocorig,tabla->abreviadoc);
                           strmin(tabla->abreviadoc);
                           strmin(tabla->abreviadocorig);
			        break;
               case GCLAVE: lee_nombre(buffer,tabla->sel[tabla->numsel].nombre,entrada);
                            tabla->sel[tabla->numsel].recorre=0;
                            tabla->sel[tabla->numsel].recorreproc=0;
                            caracclave(tabla,tabla->sel+tabla->numsel,buffer,entrada);
                            tabla->numsel++;
                            break;
               case GROWID: tabla->rowid=1;
                            caracrowid(tabla,tabla->sel+tabla->numsel,buffer,entrada);
                            tabla->sel[tabla->numsel].recorre=0;
                            tabla->sel[tabla->numsel].recorreproc=0;
                            tabla->numsel++;
                            break;
               case GRECORRE: lee_nombre(buffer,tabla->sel[tabla->numsel].nombre,entrada);
                            tabla->sel[tabla->numsel].recorre=1;
                            tabla->sel[tabla->numsel].recorreproc=0;
                            caracclave(tabla,tabla->sel+tabla->numsel,buffer,entrada);
                            tabla->numsel++;
                            break;
               case GRECORREPROC: lee_nombre(buffer,tabla->sel[tabla->numsel].nombre,entrada);
                            tabla->sel[tabla->numsel].recorre=0;
                            tabla->sel[tabla->numsel].recorreproc=1;
                            caracclave(tabla,tabla->sel+tabla->numsel,buffer,entrada);
                            tabla->numsel++;
                            break;
               case GUPDATE: lee_nombre(buffer,tabla->up[tabla->numup].nombre,entrada);
                            caracupdate(tabla,tabla->up+tabla->numup,buffer,entrada);
                            tabla->numup++;
                            break;
               case GUPDATEDEF: lee_nombre(buffer, tabla->up[tabla->numup].nombre,entrada);
                                caracupdatedef(tabla,tabla->up+tabla->numup);
                                tabla->numup++;
                                break;
               case GSECUEN: lee_nombre(buffer,tabla->sec[tabla->numsecuen].nombre,entrada);
                            caracsecuen(tabla,tabla->sec+tabla->numsecuen,buffer,entrada);
                            tabla->numsecuen++;
                            break;
               case GEXTRA: caracextra(tabla,buffer,entrada);
				            break;						   
               case GORADEBUG:  {char mioradebug[MAXNOMBREV10];
                                 lee_nombre(buffer,mioradebug,entrada);
                                 tabla->oradebug=atoi(mioradebug);
                                 break;						   
                                }
               case GLOCK:  tabla->lock=1;
                            break;
               case GINSERT:tabla->insert=1;
                            break;
               case GDELETE:tabla->delete=1;
                            break;
               case GINTERFASE:tabla->interfase=1;
                               break;
               case GAMPLIAPI:lee_nombre(buffer,tabla->ampliaapi,entrada);
					       tabla->numdic=2;
				           strcpy(tabla->ntypedeforig,tabla->ntypedef);

						   strcpy(tabla->nstaticorig,tabla->nstatic);
                           strmin(tabla->nstaticorig);

						   strcpy(tabla->nombrecorig,tabla->nombrec);
                           strmin(tabla->nombrecorig);

						   strcpy(tabla->abreviadoorig,tabla->abreviado);

                           strcpy(tabla->abreviadocorig,tabla->abreviadoc);
                           strmin(tabla->abreviadocorig);

						   strcpy(buffer,tabla->ampliaapi);
						   strcat(buffer,tabla->ntypedef);
						   strcpy(tabla->ntypedef,buffer);
						   strmin(tabla->ntypedef);

						   strcpy(buffer,tabla->ampliaapi);
						   strcat(buffer,tabla->nstatic);
						   strcpy(tabla->nstatic,buffer);
						   strmin(tabla->nstatic);

						   strcpy(buffer,tabla->ampliaapi);
						   strcat(buffer,tabla->nombrec);
						   strcpy(tabla->nombrec,buffer);
						   strmin(tabla->nombrec);

						   strcpy(buffer,tabla->ampliaapi);
						   strcat(buffer,tabla->abreviado);
						   strcpy(tabla->abreviado,buffer);

                           strcpy(buffer,tabla->ampliaapi);
                           strcat(buffer,tabla->abreviadoc);
                           strcpy(tabla->abreviadoc,buffer);
                           strmin(tabla->abreviadoc);
                           
						   break;
			   default: break;
        }
  }
  fclose(entrada);
  return(0);
}

// Añade las funciones comunes a todas las tablas: PRIMARIA, INSERT, DELETE, LOCK.
void anadeprimaria(tablas *tabla,char *table_name)
{
  //if (tabla->ampliaapi[0]==0 && !tabla->primaria){
  if (tabla->ampliaapi[0]==0){
    caracprimariadef(tabla);
  }
}


// Trata los parámetros propios del genc
static int trataparamgenc(char *cadena)
{
    switch (toupper(*cadena)) {
          case 'H' :strcpy(include,cadena+1);   
                    break;
          case 'F' :if (!es_blanco(buffertablas)) strcat(buffertablas,",");
                    strcat(buffertablas+strlen(buffertablas),cadena+1);
                   break;
    }

    return(0);
}


int main(int argc,char *argv[])
{
  char tabla[LCADENA];

  trataparamstd(argc,argv,trataparamgenc,NULL);

  while (buffertablas[0]!=0) {
      lee_tabla(buffertablas,tabla);
      memset(&stabla,0,sizeof(stabla));
      stabla.oradebug=DEPURADEFECTO+DEPURAVDNOLOG;
      if (leefichero(&stabla,strmay(tabla))==0) {
          anadeprimaria(&stabla,strmay(tabla));
          generah(&stabla);
          generac(&stabla);
      }
      liberatabla(&stabla);
   }

  return(0);
}

int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hprev,
           LPSTR cmd, int cmdshow)
{
  int ret;
  initv10lib(hinst,hprev);	
  trataparamstd(__argc,__argv,trataparammain,trataparamoracle,NULL);
  ret=main(__argc,__argv);
  return(ret);
}
