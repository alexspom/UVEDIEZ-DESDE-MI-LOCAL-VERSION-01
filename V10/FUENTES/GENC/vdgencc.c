/****
* VDGENCC.C - Generación automática del código c para acceder a una tabla.
* 
* Propósito: Funciones comunes para la generación del fichero TABLA.C
*           
* Autor	   : MGM
* Fecha    : 20-10-2007
****
* Modificaciones:
*	18-01-2010 (MGM): Inicializar el cursor solo cuando se va a utilizar.
***/

#include "vdgenc.h"


static void traduceerror(char *prefijo,char *sufijo,char *nombrec,FILE *salida) {
	char nombrecursor[MAXCADENA]="";
	sprintf(nombrecursor,"%s%s%s",prefijo,sufijo,nombrec);
	fprintf(salida,"     getcurerrornombre(%s->nombre,mensajeerror);\n",nombrecursor);
	fprintf(salida,"     v10log(LOGERROR,\"%s\\n\",mensajeerror);\n","%s");
}

// Comprueba la exstencia de un campo en la tabla
static int existecampotabla(tablas *tabla,char *nombre)
{ 
	int nc;
	for (nc=0;nc<tabla->numcol;nc++) {
		if (strcmp(tabla->col[nc].column_name,nombre)==0) return(1);
	}
	return(0);
}


// Escribe en el fichero de salida los campos agrupados
void imprimecampoagrup(FILE *salida,char *tabla,char *listacampos,char *pref,char *suf,char alias,char *prefalias,char *sep,int *cont)
{
  char campoagrup[MAXLNOMBRE],*plistcampagr; 

  plistcampagr = listacampos;
  while (damecampomaxmin(campoagrup,&plistcampagr)) {
	  if (((*cont%3)==0) && *cont>2){
		  fprintf(salida,", \"\\\n                         \" ");
		  *sep = '\0';
	  }
	  _strupr(campoagrup);
	  if (alias) fprintf(salida,"%sNVL(%s%s.%s%s,0) %s%s",sep,pref,tabla,campoagrup,suf,prefalias,campoagrup);
	  else fprintf(salida,"%s%s%s.%s%s",sep,pref,tabla,campoagrup,suf);
	  *sep = ',';
	  (*cont)++;
  }
}


// GENERAMOS LOS COMANDOS SQL QUE SE VAN A EJECUTAR
static void generalsq(tablas *tabla,FILE *salida)
{
  int nc,ns;
  int rowid=0;
  int flagwhere; 
  char hayagrup;
  char sepagr[2]=""; 
  char *dblink;


  // Inicio del cursor para pintar las sentencias SELECT
  for (ns=0;ns<tabla->numsel;ns++) {
      defselects *s=tabla->sel+ns;

      // Comprobamos si hay algún tipo de agrupación
	  hayagrup = (s->gencount||s->genmax||s->genmin||s->groupby||s->gensum);
	  if (s->recorreproc && s->lock) rowid=1;
	  if (hayagrup){
          // Obtenemos los datos agrupados si hay agrupacion
		  fprintf(salida,"#define SEL%s%s \"SELECT ",tabla->abreviado,s->nombre);
		  nc = 0;
		  strcpy(sepagr,"");
		  if (s->groupby) imprimecampoagrup(salida,tabla->table_name,s->groupby,"","",FALSE,"",sepagr,&nc);
		  if (s->genmax) imprimecampoagrup(salida,tabla->table_name,s->genmax,"MAX(",")",TRUE,"MAX",sepagr,&nc);
		  if (s->genmin) imprimecampoagrup(salida,tabla->table_name,s->genmin,"MIN(",")",TRUE,"MIN",sepagr,&nc);
          if (s->gencount) {
              if(!strcmp(s->gencount,"*")) fprintf(salida,"%sCOUNT(%s) GENCOUNT",sepagr,s->gencount);
              else  fprintf(salida,"%sCOUNT(DISTINCT %s) GENCOUNT",sepagr,s->gencount);
          }
          if (s->gensum) fprintf(salida,"%sSUM(%s) GENSUM",sepagr,s->gensum);
	  }else{
          // Si no hay agrupación pintamos los datos de salida
		  fprintf(salida,"#define SEL%s%s \"SELECT %s.ROWID",tabla->abreviado,s->nombre,tabla->table_name);
		  for (nc=0;nc<tabla->numcol;nc++) {
			  columns *c=tabla->col+nc;
			  if (c->tabla==0) continue;
			  fprintf(salida,",");
			  if ((nc%3)==2) fprintf(salida," \"\\\n                    \" ");

              // Convertimos el tipo de dato desde Oracle.
			  if (c->tipo==TIPORAW) {
			     fprintf(salida,"RAWTOHEX(%s.%s) %s",tabla->table_name,c->column_name,c->column_name);
			  } else {
				  if (c->tipo==TIPODATE) {
			         fprintf(salida,"VD.DATE2CHAR(%s.%s) %s",tabla->table_name,c->column_name,c->column_name);
				  } 
				  else {
					  if (c->tipo==TIPOTIME) {
					  fprintf(salida,"VD.TIME2CHAR(%s.%s) %s",tabla->table_name,c->column_name,c->column_name);
					  }
					  else {
			              fprintf(salida,"%s.%s",tabla->table_name,c->column_name);
					  }
				  }
			  }
		   }
	  }
      // Campos SELECT.
      if (s->select) {
    	  fprintf(salida,",%s",s->select);
	  }

      // Obtenemos la tabla de donde van a obtenerse los datos  
	  fprintf(salida," \"\\\n        \" FROM %s",tabla->table_name); 
      // Si hay un dblink lo pintamos
	  if (s->table) {
		  dblink =strchr(s->table,'@');
		  if ((dblink!=NULL) && (dblink==s->table))
			  fprintf(salida,"%s",s->table);
		  else
			   fprintf(salida," ,%s",s->table);
	   }
	  fprintf(salida,"\""); 
      
      // Pintamos el campo where de la select 
	  flagwhere=0;
	  for (nc=0;nc<s->numcol;nc++) { 
			columns *c=s->col[nc];
			if (c->tabla==0) continue; 
            if (s->solobind[nc]) continue;
            // Pintamos los datos que se han incluido en el where implicito formateandolos si es necesario.
			if (!flagwhere){ 
				flagwhere=1;
				fprintf(salida,"\\\n        \" WHERE \"\\\n");

				if (c->tipo==TIPORAW) {
				    fprintf(salida,"               \" %s.%s=HEXTORAW(:%s) \"",tabla->table_name,c->column_name,c->column_name);
				} else {
				   if (c->tipo==TIPODATE) {
				       fprintf(salida,"               \" %s.%s=VD.CHAR2DATE(:%s) \"",tabla->table_name,c->column_name,c->column_name);
				   }
				   else {
					  if (c->tipo==TIPOTIME) {
						fprintf(salida,"               \" %s.%s=VD.CHAR2TIME(:%s) \"",tabla->table_name,c->column_name,c->column_name);
					  }
					  else {
		                 fprintf(salida,"               \" %s.%s=:%s \"",tabla->table_name,c->column_name,c->column_name);
					  }
				  } 
				}
			}else fprintf(salida,"\\\n               \" AND %s.%s=:%s \"",tabla->table_name,c->column_name,c->column_name);
	   }
       
       // Si hay un where explicito tambien lo pintamos.
	   if (s->where) {
		  if (!flagwhere) fprintf(salida,"\\\n        \" WHERE \""); 
		  fprintf(salida,"\\\n              \" %s%s \"",flagwhere ? " AND " : "", s->where);
		  flagwhere=1;
	   }
       
       // Pintamos el group by si se ha declarado
  	   if (s->groupby){
		  fprintf(salida,"\\\n        \" GROUP BY ");
		  nc = 0;
		  strcpy(sepagr,"");
		  imprimecampoagrup(salida,tabla->table_name,s->groupby,"","",FALSE,"",sepagr,&nc);
		  fprintf(salida,"\"");
	   }

       // Pintamos el order by si se ha declarado
	   if (s->order) {
		  fprintf(salida,"\\\n        \" ORDER BY %s \"",s->order);
	   }
	  
       // Pintamos el for update y el nowait si se han declarado.
	   if (s->lock && s->recorreproc==0) {
		 fprintf(salida," \\\n        \" FOR UPDATE");
		 if (s->nowait) fprintf(salida," NOWAIT");
		 fprintf(salida," \"");
	   }
	   fprintf(salida,"\n");
	   fprintf(salida,"static v10cursors *vdsel%s%s;\n\n",tabla->abreviadoc,s->nombrec);	  
  }

  // Filtramos por ROWID si se hubiese especificado
  if (rowid || tabla->lock) {
      fprintf(salida,"#define SEL%sROWIDLOCK \"SELECT ROWID",tabla->abreviado);
      for (nc=0;nc<tabla->numcol;nc++) {
          columns *c=tabla->col+nc;
		  if (c->tabla==0) continue;
		  fprintf(salida,",");
          if ((nc%7)==6) fprintf(salida," \"\\\n                    \" ");
		  if (c->tipo==TIPORAW) {
             fprintf(salida,"RAWTOHEX(%s) %s",c->column_name,c->column_name);
		  } else {
			  if (c->tipo==TIPODATE) {
                 fprintf(salida,"VD.DATE2CHAR(%s) %s",c->column_name,c->column_name);
			  } else {
				  if (c->tipo==TIPOTIME) {
						fprintf(salida,"VD.TIME2CHAR(%s) %s",c->column_name,c->column_name);
				  }
				  else {
					 fprintf(salida,"%s",c->column_name);
				  }
              } 
		  }
       }

      fprintf(salida," \"\\\n        \" FROM %s \"\\\n",tabla->table_name);
      fprintf(salida,"        \" WHERE ROWID=:MIROWID \"\\\n");
      fprintf(salida,"     \" FOR UPDATE NOWAIT \"\n");
	
	// Cursor de select por rowid
    if (rowid || tabla->lock ) 
	    fprintf(salida,"static v10cursors *vdsel%srowidlock;\n\n",tabla->abreviadoc); 
  } // Fin del cursor para pintar las sentencias SELECT

  // Inicio del cursor para pintar las sentencias UPDATE
  for (ns=0;ns<tabla->numup;ns++) {
      defupdates *s=tabla->up+ns;  
	  int concoma=0;
      fprintf(salida,"#define UPDA%s%s \"UPDATE %s SET ",
                     tabla->abreviado,s->nombre,tabla->table_name);
      // Si existen los campos de control de modificación de la tabla también les realizamos un update.
	  if (existecampotabla(tabla,"FECMODIF")) {
		 fprintf(salida," FECMODIF=VD.FECHASYS(), ");
	  }
	  if (existecampotabla(tabla,"HORAMODIF()")) {
		 fprintf(salida," HORAMODIF=VD.HORASYS, ");
	  }
	  if (existecampotabla(tabla,"CODOPEMODIF")) {
		 fprintf(salida," CODOPEMODIF=VDUSER.GETUSER(), ");
	  }
	  if (existecampotabla(tabla,"MODULOMODIF")) {
		 fprintf(salida," MODULOMODIF=VDUSER.GETMODULO(), ");
	  }
	  if (existecampotabla(tabla,"ACCIONMODIF")) {
		 fprintf(salida," ACCIONMODIF=VDUSER.GETACCION(), ");
	  }
      for (nc=0;nc<s->numcol;nc++) {
          columns *c=s->col[nc];
		  if (concoma) fprintf(salida,",");
		  concoma=1;
		  if (c->tipo==TIPORAW) {
		      fprintf(salida," \"\\\n               \" %s=HEXTORAW(:%s) ",c->column_name,c->column_name);
		  } else {
		    if (c->tipo==TIPODATE) {
		        fprintf(salida," \"\\\n               \" %s=VD.CHAR2DATE(:%s) ",c->column_name,c->column_name);
			} else {
			    fprintf(salida," \"\\\n               \" %s=:%s ",c->column_name,c->column_name);
			}
		  }
       }
      fprintf(salida," \"\\\n                     \" WHERE ROWID=:MIROWID \"\n");
      fprintf(salida,"static v10cursors *vdupda%s%s;\n\n",tabla->abreviadoc,s->nombrec);

  }  // Fin del cursor para pintar las sentencias UPDATE

  // Inicio del cursor para pintar las SECUENCIAS
  for (ns=0;ns<tabla->numsecuen;ns++) {
      defsecuens *s=tabla->sec+ns;
      fprintf(salida,"#define SEL%s \"SELECT %s.NEXTVAL FROM DUAL\"\n",s->nombre,s->nombre);
      fprintf(salida,"static v10cursors *vdsel%s;\n\n",s->nombrec);
  } // Fin del cursor para pintar las SECUENCIAS

  // Pintamos la sentencia INSERT
  if (tabla->insert) {
      fprintf(salida,"#define INS%s \"INSERT INTO %s (",tabla->abreviado,tabla->table_name);
      for (nc=0;nc<tabla->numcol;nc++) {
          columns *c=tabla->col+nc;
		  if (c->tabla==0) continue;
		  if (nc>0) fprintf(salida,",");
          if ((nc%7)==6) fprintf(salida," \"\\\n                    \" ");
          fprintf(salida,"%s",c->column_name);
       }
      fprintf(salida," \"\\\n       \" ) VALUES ( \"\\\n                    \" ");
      for (nc=0;nc<tabla->numcol;nc++) {
          columns *c=tabla->col+nc;
		  if (c->tabla==0) continue;
		  if (nc>0) fprintf(salida,",");
          if ((nc%7)==6) fprintf(salida," \"\\\n                    \" ");
          // Los campos de control de modificación de la tabla se rellenan con los valores correspondientes.
          if (strcmp(c->nombrec,"codopeins")==0 || strcmp(c->nombrec,"codopemodif")==0  ) {
             fprintf(salida,"VDUSER.GETUSER()");
             continue;
           }

          if (strcmp(c->nombrec,"moduloins")==0 || strcmp(c->nombrec,"modulomodif")==0 ) {
             fprintf(salida,"VDUSER.GETMODULO()");
             continue;
           }

          if (strcmp(c->nombrec,"accionins")==0 || strcmp(c->nombrec,"accionmodif")==0 ) {
             fprintf(salida,"VDUSER.GETACCION()");
             continue;
           }

          if (strcmp(c->nombrec,"fecmodif")==0 || strcmp(c->nombrec,"fecins")==0) {
             fprintf(salida,"VD.FECHASYS()");
             continue;
           }
          if (strcmp(c->nombrec,"horamodif")==0 || strcmp(c->nombrec,"horains")==0) {
             fprintf(salida,"VD.HORASYS()");
             continue;
           }
          // Se convierten los tipos de campo que así lo necesitan.
		  if (c->tipo==TIPORAW) {
              fprintf(salida,"HEXTORAW(:%s)",c->column_name);
		  } else {
			  if (c->tipo==TIPODATE) {
                  fprintf(salida,"VD.CHAR2DATE(:%s)",c->column_name);
			  } else {
	             if (c->tipo==TIPOTIME) {
					        fprintf(salida,"VD.CHAR2TIME(:%s)",c->column_name);
				 }
				 else {
					fprintf(salida,":%s",c->column_name);			  }
			    }
		  }
       }     
	  fprintf(salida,") \"\n"); 
      fprintf(salida,"static v10cursors *vdins%s;\n\n",tabla->abreviadoc); 
  }

  // Pintamos la sentencia DELETE
  if (tabla->delete) {
      fprintf(salida,"#define DEL%s \"DELETE %s WHERE ROWID=:MIROWID \"\n",tabla->abreviado,tabla->table_name);
      fprintf(salida,"static v10cursors *vddel%s;\n\n",tabla->abreviadoc);
  }
}


// GENERA LAS VARIABLES DE TIPO STATIC
static void genstatics(tablas *tabla,FILE *salida)
{
    int ns,nc,rowid=0,ni=0;
    char *ptrbuf;
    char nommaxmin[MAXLNOMBRE],*plistanomb;
	
	// Declaramos las variables del tipo estructura de tabla
	if (tabla->ampliaapi[0]!=0)
		fprintf(salida,"static %s %s;\n", tabla->ntypedeforig,tabla->nstaticorig);
    fprintf(salida,"static %s %s;\n\n",tabla->ntypedef,tabla->nstatic);

	// Declaramos las variables del tipo columna de diccionario
	if (tabla->ampliaapi[0]!=0)
		fprintf(salida,"static diccols col%s[%sNUMCOL];\n", tabla->nombrecorig, tabla->abreviadoorig); 
        fprintf(salida,"static diccols col%s[]={",tabla->nombrec);

    // Damos de alta el campo ROWID del diccionario
    if (tabla->ampliaapi[0]==0)
        fprintf(salida,"\n\t{\"ROWID\",V10CADENA,(size_t)&%s.rowid,sizeof(%s.rowid)},",
            tabla->nstatic, tabla->nstatic);
    
    for (nc=0;nc<tabla->numcol;nc++) {
	    columns *c=tabla->col+nc;
	    if (nc>0 && ns>0 && tabla->ampliaapi[0]!=0) fprintf(salida,",");
        if (nc>0 && tabla->ampliaapi[0]==0) fprintf(salida,",");
        if (!strcmp(c->column_name,"MIROWID")) continue;
		ns=nc;
        if (c->tipo==TIPOVOIDPTR){
            ptrbuf=strmin(strdup(c->column_name));
	        fprintf(salida,"\n\t{\"%s\",%s,(size_t)&%s.%s,sizeof(%s.%s)}",
		        c->column_name,c->tipovd,tabla->nstatic,ptrbuf,tabla->nstatic,ptrbuf);
            free(ptrbuf); 
            ni++;
        } else
            if (tabla->ampliaapi[0]==0 || !c->tabla){
				fprintf(salida,"\n\t{\"%s\",%s,(size_t)&%s.%s,sizeof(%s.%s)}",
					c->column_name,c->tipovd,tabla->nstatic,c->nombrec,tabla->nstatic,c->nombrec);
                ni++;
            }
			else{
				ns=0;
				continue;
			}
    }
    if (tabla->genmax) {
      columns *colmaxmin;
	  plistanomb = tabla->genmax;
	  while (damecampomaxmin(nommaxmin,&plistanomb)) {
		  colmaxmin=busca_columna(tabla,nommaxmin);
	      fprintf(salida,",");
          fprintf(salida,"\n\t{\"GENMAX%s\",%s,(size_t)&%s.genmax%s,sizeof(%s.genmax%s)}",
					colmaxmin->column_name,colmaxmin->tipovd,tabla->nstatic,colmaxmin->nombrec,tabla->nstatic,colmaxmin->nombrec);
          ni++;
	  }
    }
    if (tabla->genmin) {
      columns *colmaxmin;
	  plistanomb = tabla->genmin;
	  while (damecampomaxmin(nommaxmin,&plistanomb)) {
		  colmaxmin=busca_columna(tabla,nommaxmin);
	      fprintf(salida,",");
          fprintf(salida,"\n\t{\"GENMIN%s\",%s,(size_t)&%s.genmin%s,sizeof(%s.genmin%s)}",
					colmaxmin->column_name,colmaxmin->tipovd,tabla->nstatic,colmaxmin->nombrec,tabla->nstatic,colmaxmin->nombrec);
          ni++;
	  }
    }
    if (tabla->gencount) {
	  fprintf(salida,",");
      fprintf(salida,"\n\t{\"GENCOUNT\",V10DOUBLE,(size_t)&%s.gencount,sizeof(%s.gencount)}",
					tabla->nstatic,tabla->nstatic);
      ni++;
    }
    if (tabla->gensum) {
	  fprintf(salida,",");
      fprintf(salida,"\n\t{\"GENSUM\",V10DOUBLE,(size_t)&%s.gensum,sizeof(%s.gensum)}",
					tabla->nstatic,tabla->nstatic);
      ni++;
    }    
    // Si no hay ningún campo en el diccionario insertamos un NULL.
    if (tabla->ampliaapi[0]!=0 && ni==0)
        fprintf(salida,"\n    NULL");
    fprintf(salida,"\n\t};\n");

	// Declaramos las variables de tipo diccionarios
	fprintf(salida,"static diccionarios d%s[]={\n", tabla->nombrec);
    if (tabla->ampliaapi[0]==0) {
        if (tabla->rowid)
            fprintf(salida,"    {col%s,%d}\n", tabla->nombrec, tabla->numcol+tabla->numagrup+tabla->numsum+tabla->numcount);
        else
            fprintf(salida,"    {col%s,%d}\n", tabla->nombrec, tabla->numcol+tabla->numagrup+tabla->numsum+tabla->numcount+1);
    }
	else{
		fprintf(salida,"    {col%s,%sNUMCOL},\n", tabla->nombrecorig,tabla->abreviadoorig);
		fprintf(salida,"    {col%s,%d}\n", tabla->nombrec,tabla->numcol+tabla->numagrup-tabla->numcolorig);
	}
	fprintf(salida,"};\n");

	// Declaramos la variable de tipo diccionario
	fprintf(salida,"diccionario d%s={d%s,%d};\n\n", tabla->abreviadoc,tabla->nombrec,tabla->numdic);
    
    // Declaramos la variable de log
    if (tabla->ampliaapi[0]==0) fprintf(salida,"static char msglog%s[LCADENA];\n",tabla->abreviado);
    fprintf(salida,"static char msgdebug%s[LCADENABIG];\n", tabla->abreviado);
	fprintf(salida,"static int init=0;\n\n"); 

    fprintf(salida,"\n");
}


// Inicializa los campos agrupados
void geninitagrup(FILE *salida,tablas *tabla,char *listacampos,char *pref)
{
  char campoagrup[MAXLNOMBRE],nombrecampo[2*MAXLNOMBRE],*plistcampagr; 
  columns *c;
           
  plistcampagr = listacampos;
  while (damecampomaxmin(campoagrup,&plistcampagr)) {
	  c=busca_columna(tabla,campoagrup);
	  strcpy(nombrecampo,pref);
	  strcat(nombrecampo,c->nombrec);
      if (tabla->ampliaapi[0]!=0 && (!c->tabla || pref[0]!=0))
   	    fprintf(salida,"%s%s.%s,sizeof(%s.%s),%s,\n                          ",
		    					strcmp(c->tipoc,"char")==0?"":"&",
			    				tabla->nstatic,nombrecampo,tabla->nstatic,nombrecampo,c->tipovd);
      else  
	    fprintf(salida,"%s%s.%s,sizeof(%s.%s),%s,\n                          ",
		    					strcmp(c->tipoc,"char")==0?"":"&",
			    				tabla->nstaticorig,nombrecampo,tabla->nstaticorig,nombrecampo,c->tipovd);
  }
}


static void geninitdiccionario(tablas *tabla,FILE *salida)
{
        fprintf(salida,"static void init_diccionario_%s(void)\n{\n",tabla->abreviadoc);
        fprintf(salida,"     diccionario *dic;\n");
        fprintf(salida,"     dic=%sdamediccionario();\n", tabla->abreviadoorig);
        fprintf(salida,"     d%s[0]=dic->d[0];\n", tabla->nombrec);
        fprintf(salida,"}\n\n");
}

// Funcion que genera la función que inicializa los cursores de acceso a base de datos.
static void geninit(tablas *tabla,FILE *salida)
{
  int ns,nc;
  int rowid=0;
  char hayagrup;  

  if (tabla->ampliaapi[0]!=0) geninitdiccionario(tabla, salida);

  // Inicializamos los cursores para las selects
  for (ns=0;ns<tabla->numsel;ns++) {
      defselects *s=tabla->sel+ns;
	  // Definimos el nombre de la función
      fprintf(salida,"static void init_sel%s%s(void)\n{\n",tabla->abreviadoc,s->nombrec);
      // Declaramos las variables de la función
      fprintf(salida,"    int nc;\n\n");
      // Inicializamos el diccionario original si estamos ante un ampliapi
      if (tabla->ampliaapi[0]!=0)
          fprintf(salida,"    init_diccionario_%s();\n", tabla->abreviadoc);
      // Inicializamos el diccionario 
      fprintf(salida,"    if (init == 0) for (nc=0;nc<d%s[%d].numcol;nc++) d%s[%d].c[nc].offset-=(size_t)&%s;\n",
	       tabla->nombrec, tabla->numdic-1,tabla->nombrec, tabla->numdic-1, tabla->nstaticorig);
	  
      if (s->recorreproc && s->lock) rowid=1;
      fprintf(salida,"    vdsel%s%s=abrecursordebug(SEL%s%s,%d);\n",tabla->abreviadoc,s->nombrec,tabla->abreviado,s->nombre,tabla->oradebug);
      fprintf(salida,"    definetodo(vdsel%s%s,",tabla->abreviadoc,s->nombrec);

      hayagrup = (s->gencount||s->genmax||s->genmin||s->groupby||s->gensum);
	  if (hayagrup){
		  if (s->groupby) geninitagrup(salida,tabla,s->groupby,"");
		  if (s->genmax)  geninitagrup(salida,tabla,s->genmax,"genmax");
		  if (s->genmin)  geninitagrup(salida,tabla,s->genmin,"genmin");
		  if (s->gencount) fprintf(salida,"&%s.gencount,sizeof(%s.gencount),V10DOUBLE,\n                          ",
							       tabla->nstatic,tabla->nstatic);
		  if (s->gensum) fprintf(salida,"&%s.gensum,sizeof(%s.gensum),V10DOUBLE,\n                          ",
							       tabla->nstatic,tabla->nstatic);
	  } else{
		  if (tabla->ampliaapi[0]==0)
			fprintf(salida,"%s.rowid,sizeof(%s.rowid),V10CADENA,\n                          ",
								tabla->nstatic,tabla->nstatic);
		  else
 			fprintf(salida,"%s.rowid,sizeof(%s.rowid),V10CADENA,\n                          ",
								tabla->nstaticorig,tabla->nstaticorig);

		  for (nc=0;nc<tabla->numcol;nc++) {
			 columns *c=tabla->col+nc;
			 if (c->tabla==0 && !busca_columnaextra(s,c->nombrec)) continue;
			 
			 if (tabla->ampliaapi[0]==0 || !c->tabla)
				 fprintf(salida,"%s%s.%s,sizeof(%s.%s),%s,\n                          ",
								strcmp(c->tipoc,"char")==0?"":"&",
								tabla->nstatic,c->nombrec,tabla->nstatic,c->nombrec,c->tipovd);
		     else 
				 fprintf(salida,"%s%s.%s,sizeof(%s.%s),%s,\n                          ",
								strcmp(c->tipoc,"char")==0?"":"&",
								tabla->nstaticorig,c->nombrec,tabla->nstaticorig,c->nombrec,c->tipovd);
		   }
	  }
      fprintf(salida,"NULL);\n");
      fprintf(salida,"    bindtodo(vdsel%s%s,",tabla->abreviadoc,s->nombrec);
      for (nc=0;nc<s->numcol;nc++) {
         columns *c=s->col[nc];
		 
         if (tabla->ampliaapi[0]==0 || !c->tabla){
            if (!strcmp(c->column_name,"MIROWID"))
                fprintf(salida,"\"%s\",%s%s.rowid,sizeof(%s.rowid),%s,\n                          ",
				            c->column_name,strcmp(c->tipoc,"char")==0?"":"&",
					        tabla->nstatic,tabla->nstatic,c->tipovd);
            else
                fprintf(salida,"\"%s\",%s%s.%s,sizeof(%s.%s),%s,\n                          ",
				            c->column_name,strcmp(c->tipoc,"char")==0?"":"&",
					        tabla->nstatic,c->nombrec,tabla->nstatic,c->nombrec,c->tipovd);
         }
         else
            fprintf(salida,"\"%s\",%s%s.%s,sizeof(%s.%s),%s,\n                          ",
				            c->column_name,strcmp(c->tipoc,"char")==0?"":"&",
					        tabla->nstaticorig,c->nombrec,tabla->nstaticorig,c->nombrec,c->tipovd);
         
      }
     fprintf(salida,"NULL);\n");

	 // Finalizamos la función
	 fprintf(salida,"    if (init == 0) {\n");
     fprintf(salida,"        atexit(fin_vd_%s);\n",tabla->abreviadoc);
	 fprintf(salida,"        init = 1;\n");
	 fprintf(salida,"    }\n");
     fprintf(salida,"}\n\n");
    }

   // Inicializammos los cursores para las querys de rowid y los lock
   if (rowid || tabla->lock) {
	  // Definimos el nombre de la función
      fprintf(salida,"static void init_sel%srowidlock(void)\n{\n",tabla->abreviadoc);
      // Declaramos las variables de la función
      fprintf(salida,"    int nc;\n\n");
      // Inicializamos el diccionario original si estamos ante un ampliapi
      if (tabla->ampliaapi[0]!=0)
          fprintf(salida,"    init_diccionario_%s();\n", tabla->abreviadoc);
      // Inicializamos el diccionario 
      fprintf(salida,"    if (init == 0) for (nc=0;nc<d%s[%d].numcol;nc++) d%s[%d].c[nc].offset-=(size_t)&%s;\n",
	       tabla->nombrec, tabla->numdic-1,tabla->nombrec, tabla->numdic-1, tabla->nstaticorig);

      fprintf(salida,"    vdsel%srowidlock=abrecursordebug(SEL%sROWIDLOCK,%d);\n",tabla->abreviadoc,tabla->abreviado,tabla->oradebug);
      fprintf(salida,"    definetodo(vdsel%srowidlock,",tabla->abreviadoc);
      fprintf(salida,"%s.rowid,sizeof(%s.rowid),V10CADENA,\n                          ",
                        tabla->nstaticorig,tabla->nstaticorig);
      for (nc=0;nc<tabla->numcol;nc++) {
         columns *c=tabla->col+nc;
		 if (c->tabla==0 ) continue;
         fprintf(salida,"%s%s.%s,sizeof(%s.%s),%s,\n                          ",
                        strcmp(c->tipoc,"char")==0?"":"&",
                        tabla->nstaticorig,c->nombrec,tabla->nstaticorig,c->nombrec,c->tipovd);
      }
     fprintf(salida,"NULL);\n");
     fprintf(salida,"    bindtodo(vdsel%srowidlock,\"MIROWID\",%s.rowid,sizeof(%s.rowid),V10CADENA,NULL);\n",tabla->abreviadoc,tabla->nstaticorig,tabla->nstaticorig);

	 // Finalizamos la función
	 fprintf(salida,"    if (init == 0) {\n");
     fprintf(salida,"        atexit(fin_vd_%s);\n",tabla->abreviadoc);
	 fprintf(salida,"        init = 1;\n");
	 fprintf(salida,"    }\n");
     fprintf(salida,"}\n\n");
    }
  
  // Inicializamos los cursores para los updates
  for (ns=0;ns<tabla->numup;ns++) {
	  defupdates *s=tabla->up+ns;
	  // Definimos el nombre de la función
      fprintf(salida,"static void init_upda%s%s(void)\n{\n",tabla->abreviadoc,s->nombrec);
      // Declaramos las variables de la función
      fprintf(salida,"    int nc;\n\n");
      // Inicializamos el diccionario original si estamos ante un ampliapi
      if (tabla->ampliaapi[0]!=0)
          fprintf(salida,"    init_diccionario_%s();\n", tabla->abreviadoc);
      // Inicializamos el diccionario 
      fprintf(salida,"    if (init == 0) for (nc=0;nc<d%s[%d].numcol;nc++) d%s[%d].c[nc].offset-=(size_t)&%s;\n",
	       tabla->nombrec, tabla->numdic-1,tabla->nombrec, tabla->numdic-1, tabla->nstaticorig);

	  fprintf(salida,"    vdupda%s%s=abrecursordebug(UPDA%s%s,%d);\n",tabla->abreviadoc,s->nombrec,tabla->abreviado,s->nombre,tabla->oradebug);
      fprintf(salida,"    bindtodo(vdupda%s%s,",tabla->abreviadoc,s->nombrec);
      for (nc=0;nc<s->numcol;nc++) {
         columns *c=s->col[nc];
	     if (tabla->ampliaapi[0]==0 || !c->tabla)
            fprintf(salida,"\"%s\",%s%s.%s,sizeof(%s.%s),%s,\n                          ",
                            c->column_name,strcmp(c->tipoc,"char")==0?"":"&",
                            tabla->nstatic,c->nombrec,tabla->nstatic,c->nombrec,c->tipovd);
         else
            fprintf(salida,"\"%s\",%s%s.%s,sizeof(%s.%s),%s,\n                          ",
                            c->column_name,strcmp(c->tipoc,"char")==0?"":"&",
                            tabla->nstaticorig,c->nombrec,tabla->nstaticorig,c->nombrec,c->tipovd);
      }
     fprintf(salida,"\"MIROWID\",%s.rowid,sizeof(%s.rowid),V10CADENA,\n                          ",
                     tabla->nstaticorig,tabla->nstaticorig);
     fprintf(salida,"NULL);\n");
	 
	 // Finalizamos la función
	 fprintf(salida,"    if (init == 0) {\n");
     fprintf(salida,"        atexit(fin_vd_%s);\n",tabla->abreviadoc);
	 fprintf(salida,"        init = 1;\n");
	 fprintf(salida,"    }\n");
     fprintf(salida,"}\n\n");
    }

  // Inicializamos los cursores para las secuencias
  for (ns=0;ns<tabla->numsecuen;ns++) {
      defsecuens *s=tabla->sec+ns;
	  // Definimos el nombre de la función
      fprintf(salida,"static void init_sel%s(void)\n{\n",s->nombrec);
      // Declaramos las variables de la función
      fprintf(salida,"    int nc;\n\n");
      // Inicializamos el diccionario original si estamos ante un ampliapi
      if (tabla->ampliaapi[0]!=0)
          fprintf(salida,"    init_diccionario_%s();\n", tabla->abreviadoc);
      // Inicializamos el diccionario
	  fprintf(salida,"    if (init == 0) for (nc=0;nc<d%s[%d].numcol;nc++) d%s[%d].c[nc].offset-=(size_t)&%s;\n",
	       tabla->nombrec, tabla->numdic-1,tabla->nombrec, tabla->numdic-1, tabla->nstaticorig);

	  fprintf(salida,"    vdsel%s=abrecursordebug(SEL%s,%d);\n",s->nombrec,s->nombre,tabla->oradebug);
      fprintf(salida,"    definetodo(vdsel%s,",s->nombrec);
	  if (tabla->ampliaapi[0]==0 || !s->col->tabla)      
        fprintf(salida,"&%s.%s,sizeof(%s.%s),V10LONG,NULL);\n",tabla->nstatic,s->col->nombrec,tabla->nstatic,s->col->nombrec);
      else
        fprintf(salida,"&%s.%s,sizeof(%s.%s),V10LONG,NULL);\n",tabla->nstaticorig,s->col->nombrec,tabla->nstaticorig,s->col->nombrec);

	 // Finalizamos la función
	 fprintf(salida,"    if (init == 0) {\n");
     fprintf(salida,"        atexit(fin_vd_%s);\n",tabla->abreviadoc);
	 fprintf(salida,"        init = 1;\n");
	 fprintf(salida,"    }\n");
     fprintf(salida,"}\n\n");
  }

  // Inicializamos el cursor de insert
  if (tabla->insert) {
      // Definimos el nombre de la función
      fprintf(salida,"static void init_ins%s(void)\n{\n",tabla->abreviadoc);
      // Declaramos las variables de la función
      fprintf(salida,"    int nc;\n\n");
      // Inicializamos el diccionario original si estamos ante un ampliapi
      if (tabla->ampliaapi[0]!=0)
          fprintf(salida,"    init_diccionario_%s();\n", tabla->abreviadoc);
      // Inicializamos el diccionario
      fprintf(salida,"    if (init == 0) for (nc=0;nc<d%s[%d].numcol;nc++) d%s[%d].c[nc].offset-=(size_t)&%s;\n",
	       tabla->nombrec, tabla->numdic-1,tabla->nombrec, tabla->numdic-1, tabla->nstaticorig);

     fprintf(salida,"    vdins%s=abrecursordebug(INS%s,%d);\n",tabla->abreviadoc,tabla->abreviado,tabla->oradebug);
     fprintf(salida,"    bindtodo(vdins%s,",tabla->abreviadoc);
     for (nc=0;nc<tabla->numcol;nc++) {
         columns *c=tabla->col+nc;
		 if (c->tabla==0) continue;
         if (strcmp(c->column_name,"FECMODIF")==0    || 
			 strcmp(c->column_name,"HORAMODIF")==0   ||
			 strcmp(c->column_name,"CODOPEMODIF")==0 ||
             strcmp(c->column_name,"MODULOMODIF")==0 ||           
             strcmp(c->column_name,"ACCIONMODIF")==0) continue;   
         if (strcmp(c->column_name,"FECINS")==0      || 
			 strcmp(c->column_name,"HORAINS")==0     ||
			 strcmp(c->column_name,"CODOPEINS")==0   ||            
             strcmp(c->column_name,"MODULOINS")==0   ||            
             strcmp(c->column_name,"ACCIONINS")==0 ) continue;
         fprintf(salida,"\"%s\",%s%s.%s,sizeof(%s.%s),%s,\n                          ",
                        c->column_name,strcmp(c->tipoc,"char")==0?"":"&",
                        tabla->nstaticorig,c->nombrec,tabla->nstaticorig,c->nombrec,c->tipovd);
      }
     fprintf(salida,"NULL);\n");
	 
	 // Finalizamos la función
	 fprintf(salida,"    if (init == 0) {\n");
     fprintf(salida,"        atexit(fin_vd_%s);\n",tabla->abreviadoc);
	 fprintf(salida,"        init = 1;\n");
	 fprintf(salida,"    }\n");
     fprintf(salida,"}\n\n");
   }

  // Inicializamos el cursor de delete
  if (tabla->delete) {
      // Definimos el nombre de la función
      fprintf(salida,"static void init_del%s(void)\n{\n",tabla->abreviadoc);
      // Declaramos las variables de la función
      fprintf(salida,"    int nc;\n\n");
      // Inicializamos el diccionario original si estamos ante un ampliapi
      if (tabla->ampliaapi[0]!=0)
          fprintf(salida,"    init_diccionario_%s();\n", tabla->abreviadoc);
      // Inicializamos el diccionario
      fprintf(salida,"    if (init == 0) for (nc=0;nc<d%s[%d].numcol;nc++) d%s[%d].c[nc].offset-=(size_t)&%s;\n",
	       tabla->nombrec, tabla->numdic-1,tabla->nombrec, tabla->numdic-1, tabla->nstaticorig);

     fprintf(salida,"    vddel%s=abrecursordebug(DEL%s,%d);\n",tabla->abreviadoc,tabla->abreviado,tabla->oradebug);
     fprintf(salida,"    bindtodo(vddel%s,",tabla->abreviadoc);
     fprintf(salida,"\"MIROWID\",%s.rowid,sizeof(%s.rowid),V10CADENA,\n                          ",
                        tabla->nstaticorig,tabla->nstaticorig);
     fprintf(salida,"NULL);\n");

	 // Finalizamos la función
	 fprintf(salida,"    if (init == 0) {\n");
     fprintf(salida,"        atexit(fin_vd_%s);\n",tabla->abreviadoc);
	 fprintf(salida,"        init = 1;\n");
	 fprintf(salida,"    }\n");
     fprintf(salida,"}\n\n");
   }
}  


// Funcion que genera la función que libera los cursores que acceden a las tablas
static void genfin(tablas *tabla,FILE *salida)
{
  int ns;
  int rowid=0;

  // Definimos el nombre de la función
  fprintf(salida,"static void fin_vd_%s(void)\n{\n",tabla->abreviadoc);

  // Liberamos los cursores de seleccion
  for (ns=0;ns<tabla->numsel;ns++) {
      defselects *s=tabla->sel+ns;
      if (s->recorreproc && s->lock) rowid=1;
	  fprintf(salida,"if (vdsel%s%s) {\n", tabla->abreviadoc,s->nombrec);   
      fprintf(salida,"    liberacursor(vdsel%s%s);\n", tabla->abreviadoc,s->nombrec);
	  fprintf(salida,"    vdsel%s%s = NULL;\n}\n", tabla->abreviadoc,s->nombrec); 
  }

  // Liberamos el cursor de seleccion por rowid
  if (rowid || tabla->lock) {
	  fprintf(salida,"if (vdsel%srowidlock) {\n", tabla->abreviadoc);
	  fprintf(salida,"    liberacursor(vdsel%srowidlock);\n", tabla->abreviadoc);
	  fprintf(salida,"    vdsel%srowidlock = NULL;\n}\n", tabla->abreviadoc);
  }

  // Liberamos los cursores de update.
  for (ns=0;ns<tabla->numup;ns++) {
      defupdates *s=tabla->up+ns;
	  fprintf(salida,"if (vdupda%s%s) {\n", tabla->abreviadoc, s->nombrec);
	  fprintf(salida,"    liberacursor(vdupda%s%s);\n", tabla->abreviadoc, s->nombrec);
	  fprintf(salida,"    vdupda%s%s = NULL;\n}\n", tabla->abreviadoc, s->nombrec);
  }

  // Liberamos los cursores de secuencia
  for (ns=0;ns<tabla->numsecuen;ns++) {
      defsecuens *s=tabla->sec+ns;
	  fprintf(salida,"if (vdsel%s != NULL) {\n", s->nombrec); 
	  fprintf(salida,"    liberacursor(vdsel%s);\n", s->nombrec);
	  fprintf(salida,"    vdsel%s = NULL;\n}\n", s->nombrec); 
  }

  // Liberamos los cursores de insert
  if (tabla->insert) {
     fprintf(salida,"if (vdins%s != NULL) {\n", tabla->abreviadoc);
	 fprintf(salida,"    liberacursor(vdins%s);\n", tabla->abreviadoc);
	 fprintf(salida,"    vdins%s = NULL;\n}\n", tabla->abreviadoc);

  }

  // Liberamos los cursores de delete
  if (tabla->delete) {
     fprintf(salida,"if (vddel%s != NULL) {\n", tabla->abreviadoc);
	 fprintf(salida,"    liberacursor(vddel%s);\n", tabla->abreviadoc);
	 fprintf(salida,"    vddel%s = NULL;\n}\n", tabla->abreviadoc);
  }

  fprintf(salida,"}\n");
}


// Funcion que genera la función que nos devuelve el diccionario de campos.
static void genaccesodiccionario(tablas *tabla,FILE *salida)
{
 fprintf(salida,"diccionario *%sdamediccionario(void)\n{\n",tabla->abreviado);
  if (tabla->ampliaapi[0]!=0)
    fprintf(salida,"     init_diccionario_%s();\n", tabla->abreviadoc);
  fprintf(salida,"     return(&d%s);\n",tabla->abreviadoc);
  fprintf(salida,"}\n\n");
}


// Funcion que genera la cabecera de la funcion select
static void genprototiposel(tablas *tabla,defselects *s,FILE *salida)
{
  int nc;
  char hayagrup;

  hayagrup = (s->gencount||s->genmax||s->genmin||s->gensum);

  if (s->recorre==0) {
     if (s->recorreproc==0) {
        fprintf(salida,"int %ssel%s(",tabla->abreviado,s->nombrec);
      } else {
        fprintf(salida,"void %sprocesa%s(",tabla->abreviado,s->nombrec);
      }
    } else {
      fprintf(salida,"int %sbusca%s(",tabla->abreviado,s->nombrec);
    }
   for (nc=0;nc<s->numcol;nc++) {
       columns *c=s->col[nc];
       fprintf(salida,"%s %s%s,",c->tipoc,strcmp(c->tipoc,"char")==0?"*":"",c->nombrec);
    }
    if (s->recorreproc==0) {
        if (hayagrup) fprintf(salida,"%s *%s)",tabla->ntypedef,tabla->abreviadoc);
        else fprintf(salida,"%s *%s)",tabla->ntypedeforig,tabla->abreviadocorig);
    } else {
        fprintf(salida,"int (*func)(%s *%s,void *ptr),void *ptr,long cuantos)",tabla->ntypedef,tabla->abreviadoc);
    }
}


// Función que escribe en el fichero las características de la clave primaria para escribir en el log.
void genformatclave(tablas *tabla,FILE *salida)
{
  int nc;
  for (nc=0;nc<tabla->numprimaria;nc++) {
      columns *c=tabla->primaria[nc];
      fprintf(salida,"%s ",c->nombrec);
      if (strcmp(c->tipoc,"char")==0) {
         fprintf(salida,"%%s ");
       }
      if (strcmp(c->tipoc,"long")==0) {
         fprintf(salida,"%%ld ");
       }
      if (strcmp(c->tipoc,"double")==0) {
         fprintf(salida,"%%lf ");
       }
      if (strcmp(c->tipoc,"fechas")==0) {
         fprintf(salida,"%%ld ");
       }
   }
}

// Función que escribe en el fichero las características de la clave primaria para escribir en el log.
void genvariablesclave(tablas *tabla,FILE *salida)
{
  int nc;
  for (nc=0;nc<tabla->numprimaria;nc++) {
      columns *c=tabla->primaria[nc];
      fprintf(salida,",%s->%s",tabla->abreviadoc,c->nombrec);
   }
}

// Función que escribe en el fichero las características de las columnas de una query para escribir en el log.
void genformatselect(tablas *tabla,defselects *s,FILE *salida)
{
  int nc;
  for (nc=0;nc<s->numcol;nc++) {
      columns *c=s->col[nc];
      fprintf(salida,"%s ",c->nombrec);
      if (strcmp(c->tipoc,"char")==0) {
         fprintf(salida,"%%s ");
       }
      if (strcmp(c->tipoc,"long")==0) {
         fprintf(salida,"%%ld ");
       }
      if (strcmp(c->tipoc,"double")==0) {
         fprintf(salida,"%%lf ");
       }
      if (strcmp(c->tipoc,"fechas")==0) {
         fprintf(salida,"%%ld ");
       }
   }
}

// Función que escribe en el fichero las características de las columnas de una query para escribir en el log.
void genvariablesselect(tablas *tabla,defselects *s,FILE *salida,int prefijo)
{
  int nc;
  for (nc=0;nc<s->numcol;nc++) {
      columns *c=s->col[nc];
      if (prefijo) {
         fprintf(salida,"%s->%s%s",tabla->abreviadoc,c->nombrec,nc<s->numcol-1?",":"");
      } else {                                                                         
         fprintf(salida,"%s%s",c->nombrec,nc<s->numcol-1?",":"");
      }
   }
}

// Función que genera un log con las características de la query.
static void generalog(char *cadena, tablas *tabla, char *sql, FILE *salida, char *hayagrup, char *ret)
{
  fprintf(salida,"    v10log(LOGDEBUGAPI,\"%s %%s %s. ", cadena,sql);
  if (ret[0]!=0) fprintf(salida,"vdret %%d. \\n\",");
     else fprintf(salida," \\n\",");
  if (tabla->ampliaapi[0]!=0 && hayagrup[0]!=0)  fprintf(salida,"%slog(&%s->%s)", tabla->abreviadoorig, tabla->abreviadoc, tabla->abreviadocorig);
     else fprintf(salida,"%slog(&%s)", tabla->abreviadoorig, tabla->nstaticorig);
  if (ret[0]!=0) fprintf(salida,",%s);\n",ret);
     else fprintf(salida,");\n");
}

// Función que genera las funciones que ejecutan las sentencias que devuelven secuencias
void generasecuencias(tablas *tabla,FILE *salida)
{
  int ns;
  for (ns=0;ns<tabla->numsecuen;ns++) {
      defsecuens *s=tabla->sec+ns;
      fprintf(salida,"int %ssel%s(long *donde)\n{\n",tabla->abreviado,s->nombrec);
      fprintf(salida,"  int vdret;\n");
      fprintf(salida,"  if (!vdsel%s) init_sel%s();\n",s->nombrec,s->nombrec);
      fprintf(salida,"  vdret=ejefetchcursor(vdsel%s);\n",s->nombrec);
      fprintf(salida,"  if (!vdret) {\n");
      if (tabla->ampliaapi[0]==0||!s->col->tabla) fprintf(salida,"     *donde=%s.%s;\n",tabla->nstatic,s->col->nombrec);
      else fprintf(salida,"     *donde=%s.%s;\n",tabla->nstaticorig,s->col->nombrec);
      fprintf(salida,"     return(vdret);\n");
      fprintf(salida,"   }\n");
      fprintf(salida,"  *donde=0;\n");
      fprintf(salida,"  return(VD_EERRORACLE);\n");
      fprintf(salida,"}\n\n");
   }
}

// Función que inicializa las variables en que se le van a pasar a una query.
void asignavariablesselect(tablas *tabla,defselects *s,FILE *salida)
{
  int nc;
  fprintf(salida,"  memset(&%s,0,sizeof(%s));\n",tabla->nstaticorig, tabla->nstaticorig);
  for (nc=0;nc<s->numcol;nc++) {
      columns *c=s->col[nc];
      if (strcmp(c->tipoc,"char")==0) {
            if(tabla->ampliaapi[0]!=0 && !c->tabla) 
               fprintf(salida,"  strcpy(%s.%s,%s);\n",tabla->nstatic,c->nombrec,c->nombrec);       
            else {
                if (!strcmp(c->column_name,"MIROWID")) fprintf(salida,"  strcpy(%s.rowid,%s);\n",tabla->nstaticorig,c->nombrec);
                else fprintf(salida,"  strcpy(%s.%s,%s);\n",tabla->nstaticorig,c->nombrec,c->nombrec);
            }
       } else {
         if(tabla->ampliaapi[0]!=0 && !c->tabla) fprintf(salida,"  %s.%s=%s;\n",tabla->nstatic,c->nombrec,c->nombrec);
         else fprintf(salida,"  %s.%s=%s;\n",tabla->nstaticorig,c->nombrec,c->nombrec);
       }
    }
}

// Genera el cuerpo de la función que ejecuta una query normal
void generaselectnormal(tablas *tabla,defselects *s,FILE *salida)
{
  char hayagrup;
  char nombreselect[LCADENA];

  sprintf(nombreselect,"vdsel%s%s",tabla->abreviadoc,s->nombrec);

  hayagrup = (s->gencount||s->genmax||s->genmin||s->gensum);

  fprintf(salida,"\n{\n");
  fprintf(salida,"  int vdret;\n");
  fprintf(salida,"  if (%s==NULL) init_sel%s%s();\n",nombreselect,tabla->abreviadoc,s->nombrec);
  asignavariablesselect(tabla,s,salida);
  fprintf(salida,"  vdret=ejefetchcursor(%s);\n",nombreselect);
  fprintf(salida,"  if (vdret) {\n");
  generalog("Ejefetch",tabla,nombreselect,salida,&hayagrup,"vdret");
  if (s->noretvd)
	  fprintf(salida,"    return(vdret);\n");
  else
	  fprintf(salida,"    return(VD_EERRORACLE);\n");
  
  fprintf(salida,"   }\n");
  if (hayagrup) fprintf(salida,"  *%s=%s;\n",tabla->abreviadoc,tabla->nstatic);
  else fprintf(salida,"  *%s=%s;\n",tabla->abreviadocorig,tabla->nstaticorig);
  fprintf(salida,"  return(vdret);\n");
  fprintf(salida,"}\n\n");
}


// Genera la funcion de busca para la opción RECORRE
void generabusca(tablas *tabla,defselects *s,FILE *salida)
{
  char hayagrup;
  char nombreselect[LCADENA];

  sprintf(nombreselect,"vdsel%s%s",tabla->abreviadoc,s->nombrec);

  hayagrup = (s->gencount||s->genmax||s->genmin||s->gensum);

  fprintf(salida,"\n{\n");
  fprintf(salida,"  int vdret;\n");
  asignavariablesselect(tabla,s,salida);
  fprintf(salida,"  if (%s==NULL) init_sel%s%s();\n",nombreselect,tabla->abreviadoc,s->nombrec);
  fprintf(salida,"  vdret=ejefetchcursor(%s);\n",nombreselect);
  fprintf(salida,"  if (vdret==0) {\n");
  if (hayagrup) fprintf(salida,"     *%s=%s;\n",tabla->abreviadoc,tabla->nstatic);
  else fprintf(salida,"     *%s=%s;\n",tabla->abreviadocorig,tabla->nstaticorig);
  generalog("Encontrado primero",tabla,nombreselect,salida,&hayagrup,"vdret");
  fprintf(salida,"     return(0);\n");
  fprintf(salida,"   }\n");
  if (s->noretvd)
	  fprintf(salida,"  return(vdret);\n");
  else 
	  fprintf(salida,"  return(VD_EERRORACLE);\n");  
  fprintf(salida,"}\n\n");
}

// Genera la función next para la opción RECORRE
void generanext(tablas *tabla,defselects *s,FILE *salida)
{
  char hayagrup;
  char nombreselect[LCADENA];

  sprintf(nombreselect,"vdsel%s%s",tabla->abreviadoc,s->nombrec);

  hayagrup = (s->gencount||s->genmax||s->genmin||s->gensum);
  if (hayagrup) fprintf(salida,"int %snext%s(%s *%s)\n{\n",tabla->abreviado,s->nombrec,tabla->ntypedef,tabla->abreviadoc);
  else fprintf(salida,"int %snext%s(%s *%s)\n{\n",tabla->abreviado,s->nombrec,tabla->ntypedeforig,tabla->abreviadocorig);
  fprintf(salida,"  int vdret;\n");
  fprintf(salida,"  vdret=fetchcursor(%s);\n",nombreselect);
  fprintf(salida,"  if (vdret==0) {\n");
  if (hayagrup) fprintf(salida,"     *%s=%s;\n",tabla->abreviadoc,tabla->nstatic);
  else fprintf(salida,"     *%s=%s;\n",tabla->abreviadocorig,tabla->nstaticorig);
  generalog("Siguiente", tabla,nombreselect, salida,&hayagrup,"vdret");
  fprintf(salida,"     return(0);\n");
  fprintf(salida,"   }\n");
  if (s->noretvd)
	  fprintf(salida,"  return(vdret);\n");
  else {
	  fprintf(salida,"  if (vdret!=NOFOUND) cursordebug(vdsel%s%s);\n",tabla->abreviadoc,s->nombrec);
	  fprintf(salida,"  return(VD_EERRORACLE);\n");
  }
  fprintf(salida,"}\n\n");
}

// Función que genera las funciones que ejecutan las sentencias LOCK
void genbloqueo(tablas *tabla,FILE *salida)
{
	if (tabla->lock==0) return;

    // Generamos la cabecera de la función
	fprintf(salida,"int %slock(%s *%s,int wait,int verificar,...)\n{\n",tabla->abreviado,tabla->ntypedeforig,tabla->abreviadocorig);
    // Declaramos las variables
    fprintf(salida,"    int vdret;\n");
	fprintf(salida,"    va_list arg;\n");
    fprintf(salida,"    %s=*%s;\n",tabla->nstaticorig,tabla->abreviadocorig);
    // Inicializamos los cursores en caso de ser necesario
	fprintf(salida,"    if (vdsel%srowidlock==NULL) init_sel%srowidlock();\n",tabla->abreviadoc,tabla->abreviadoc); //(3)
	fprintf(salida,"    savepoint(\"lock%s\");\n",tabla->nombrec);
	fprintf(salida,"    while (1) {\n");
	fprintf(salida,"        vdret=ejefetchcursor(vdsel%srowidlock);\n",tabla->abreviadoc);
    fprintf(salida,"        if (vdret==0) break;\n");
	fprintf(salida,"        if (vdret==BLOQUEADO && wait) {\n");
    fprintf(salida,"           Sleep(1000);\n");
    fprintf(salida,"           if (hay_tecla()) if (tecla()==esc) return(VD_EERRBLOQUEO);\n");
    fprintf(salida,"           continue;\n");
    fprintf(salida,"         } else {\n");
    fprintf(salida,"           if (wait==0) return(VD_EERRBLOQUEO);\n");
    fprintf(salida,"         }\n");
	fprintf(salida,"    }\n");
    fprintf(salida,"    if (vdret) return(VD_EERRORACLE);\n");
	fprintf(salida,"    if (verificar==0) return(vdret);\n");
	fprintf(salida,"    va_start(arg,verificar);\n");
	fprintf(salida,"    vdret=vverificacampos(%s,&%s,&d%s[0],arg);\n",tabla->abreviadocorig,tabla->nstaticorig,tabla->nombrec);
	fprintf(salida,"    va_end(arg);\n");
	fprintf(salida,"    if (vdret!=0) rollbacksavepoint(\"lock%s\");\n",tabla->nombrec);
	fprintf(salida,"    return(vdret);\n}\n\n");		 
}

// Funcion que escribe en el fichero el código para verificar los cambios de las variables 
void verificavariables(tablas *tabla,defselects *s,FILE *salida)
{
  int nc;
  for (nc=0;nc<s->numcol;nc++) {
      columns *c=s->col[nc];
      if (strcmp(c->tipoc,"char")==0) {
         fprintf(salida,"        if (strcmp(%s.%s,%s)) {\n",tabla->nstatic,c->nombrec,c->nombrec);
         generalog("",tabla,"",salida,"","vdret");
         fprintf(salida,"           v10log(LOGDEBUGAPI,\" %s modificado, de %%s a %%s.\\n\"",c->nombrec);
         fprintf(salida,",%s,%s.%s);\n",c->nombrec,tabla->nstatic,c->nombrec);

         fprintf(salida,"          vdret=VD_EREGMODIF;\n"); 
         fprintf(salida,"        }\n");
      } else {
         fprintf(salida,"        if (%s.%s!=%s) {\n",tabla->nstatic,c->nombrec,c->nombrec);
         generalog("",tabla,"",salida,"","vdret");
         if (strcmp(c->tipoc,"long")==0 || strcmp(c->tipoc,"fechas")) {
            fprintf(salida,"           v10log(LOGDEBUGAPI,\" %s modificado, de %%ld a %%ld.\\n\"",c->nombrec);
          }
         if (strcmp(c->tipoc,"double")==0) {
            fprintf(salida,"           v10log(LOGDEBUGAPI,\" %s modificado, de %%lf a %%lf.\\n\"",c->nombrec);
          }
         fprintf(salida,",%s,%s.%s);\n",c->nombrec,tabla->nstatic,c->nombrec);
         fprintf(salida,"          vdret=VD_EREGMODIF;\n"); 
         fprintf(salida,"        }\n");
      }
   }
}

// Función que escribe los parámetros que se le van a pasar a una función que ejecuta una query.
static void genparametrosselect(tablas *tabla,defselects *s,FILE *salida)
{
  int nc;
   for (nc=0;nc<s->numcol;nc++) {
       columns *c=s->col[nc];
       fprintf(salida,"%s %s%s%s",c->tipoc,strcmp(c->tipoc,"char")==0?"*":"",c->nombrec,
              nc<s->numcol-1?",":"");
    }
}


void genpasaparametrosselect(tablas *tabla,defselects *s,FILE *salida)
{
  int nc;
   for (nc=0;nc<s->numcol;nc++) {
       columns *c=s->col[nc];
       fprintf(salida,"%s%s",c->nombrec,
              nc<s->numcol-1?",":"");
    }
}

void genauxrecorre(tablas *tabla,defselects *s,FILE *salida)
{
  char nombreselect[LCADENA];

  sprintf(nombreselect,"vdsel%s%s",tabla->abreviadoc,s->nombrec);
  // Declaramos la cabecera de la función
  fprintf(salida,"static int %ssel%s(",tabla->abreviado,s->nombrec);
  genparametrosselect(tabla,s,salida);
  fprintf(salida,")\n{\n");

  // Declaramos la variable de error
  fprintf(salida,"  int vdret;\n");

  // Abrimos el cursor
  fprintf(salida,"  if (vdsel%s%s==NULL) init_sel%s%s();\n",tabla->abreviadoc,s->nombrec,tabla->abreviadoc,s->nombrec);

  // Asignamos memoria a la variable y asignamos las variables.
  fprintf(salida,"  memset(&%s,0,sizeof(%s));\n",tabla->nstatic,tabla->nstatic);
  asignavariablesselect(tabla,s,salida);

  // Ejecutamos el cursor
  fprintf(salida,"  vdret=ejecutacursor(vdsel%s%s);\n",tabla->abreviadoc,s->nombrec);
  fprintf(salida,"  return(vdret);\n");
  fprintf(salida,"}\n\n");

  // Declaramos la cabecera de la función next
  fprintf(salida,"static int %snext%s(",tabla->abreviado,s->nombrec);
  genparametrosselect(tabla,s,salida);
  fprintf(salida,")\n{\n");
  if (s->nowait) fprintf(salida,"  int err;\n");
  fprintf(salida,"  int vdret;\n");
  fprintf(salida,"  %s *%s=&%s;\n",tabla->ntypedef,tabla->abreviadoc,tabla->nstatic);
  if (s->lock) {
     fprintf(salida,"  if ((vdret=fetchcursor(%s))==0) {\n",nombreselect);
     if (s->nowait==0) {
        fprintf(salida,"    while (1) {\n");
        fprintf(salida,"       err=ejefetchcursor(vdsel%srowid);\n",tabla->abreviadoc);
        fprintf(salida,"       if (err==BLOQUEADO) {\n");

        generalog("Registro bloqueado:",tabla,"",salida,"","err");
        fprintf(salida,"          if (hay_tecla()) if (tecla()==esc) return(VD_EERRBLOQUEO)\n");
        fprintf(salida,"          Sleep(1000);\n");
        fprintf(salida,"        } else {\n");
        fprintf(salida,"          break;\n");
        fprintf(salida,"        }\n");
        fprintf(salida,"     }\n");
      } else {
        fprintf(salida,"    err=ejefetchcursor(vdsel%srowid);\n",tabla->abreviadoc);
      }
     fprintf(salida,"    if (err) {\n");
     fprintf(salida,"      if (err==BLOQUEADO) {\n");
     generalog("Registro bloqueado:",tabla,"",salida,"","err");
     fprintf(salida,"        return(VD_EERRBLOQUEO);\n");
     fprintf(salida,"      }\n");
     fprintf(salida,"      v10log(LOGERROR,\"Ejecutando vdsel%srowid %s.C, err %%d.\\n\",err);\n",tabla->abreviadoc,tabla->table_name);
     fprintf(salida,"      return(VD_EERRORACLE);\n");
     fprintf(salida,"    }\n");
     verificavariables(tabla,s,salida);
     fprintf(salida,"  } else {\n");
     fprintf(salida,"    if (vdret!=NOFOUND) cursordebug(vdsel%s%s);\n",tabla->abreviadoc,s->nombrec);
     fprintf(salida,"    return(VD_EERRORACLE);\n"); //(6)
     fprintf(salida,"  }\n");
   } else {
     fprintf(salida,"  vdret=fetchcursor(%s);\n",nombreselect);
     fprintf(salida,"  if (vdret) {\n");
     fprintf(salida,"     if (vdret!=NOFOUND) cursordebug(%s);\n",nombreselect);
     fprintf(salida,"     return(VD_EERRORACLE);\n");
     fprintf(salida,"   }\n");
   }
  fprintf(salida,"  return(vdret);\n");
  fprintf(salida,"}\n\n");
}

// Función que genera la función de proceso 
void generarecorreproc(tablas *tabla,defselects *s,FILE *salida)
{
  fprintf(salida,"\n{\n");
  fprintf(salida,"  int salir = 0;\n");
  fprintf(salida,"  int vdret,err;\n");
  fprintf(salida,"  int procesados = 0;\n");
  fprintf(salida,"  int bloqueados = 0;\n");
  fprintf(salida,"  int modificados = 0;\n");
  fprintf(salida,"  long concont,cont;\n");
  fprintf(salida,"  %s l%s;\n",tabla->ntypedef,tabla->nombrec);
  fprintf(salida,"  %s *%s=&l%s;\n",tabla->ntypedef,tabla->abreviadoc,tabla->nombrec);
  fprintf(salida,"  if (%ssel%s(",tabla->abreviado,s->nombrec);
  genpasaparametrosselect(tabla,s,salida);
  fprintf(salida,")==0) {\n");
  fprintf(salida,"    concont=cont=cuantos;\n");
  fprintf(salida,"    do {\n");
  fprintf(salida,"      if ((concont?cont:1) && !hay_tecla()) {\n");
  fprintf(salida,"        err=%snext%s(",tabla->abreviado,s->nombrec);
  genpasaparametrosselect(tabla,s,salida);
  fprintf(salida,");\n");
  fprintf(salida,"        if (err==0) {\n");
  fprintf(salida,"          l%s=%s;\n",tabla->nombrec,tabla->nstatic);
  generalog("Procesando",tabla,s->nombrec,salida,"","err");
  fprintf(salida,"          vdret=(*func)(&l%s,ptr);\n",tabla->nombrec);
  fprintf(salida,"          commit();\n");
  fprintf(salida,"          if (!vdret) {\n");
  generalog("Procesando",tabla,s->nombrec,salida,"","err");
  fprintf(salida,"             if (concont) cont--;\n");
  fprintf(salida,"             procesados++;\n");
  fprintf(salida,"          }\n");
  fprintf(salida,"        } else {\n");
  fprintf(salida,"          switch (err) {\n");
  fprintf(salida,"              case VD_EERRBLOQUEO:bloqueados++;\n");
  fprintf(salida,"                                  break;\n");
  fprintf(salida,"              case VD_EREGMODIF:modificados++;\n");
  fprintf(salida,"                                  break;\n");
  fprintf(salida,"              default:salir=1;\n");
  fprintf(salida,"            }\n");
  fprintf(salida,"        }\n");
  fprintf(salida,"        rollback();\n");
  fprintf(salida,"      } else {\n");
  fprintf(salida,"        salir=1;\n");
  fprintf(salida,"      }\n");
  fprintf(salida,"    } while(!salir);\n");
  fprintf(salida,"  }\n");
  fprintf(salida,"  if (procesados || bloqueados || modificados) {\n");
  fprintf(salida,"    v10log(LOGDEBUGAPI,\"Procesados %%d, bloqueados %%d, modificados %%d.\\n\",procesados,bloqueados,modificados);\n");
  fprintf(salida,"  }\n");
  fprintf(salida,"}\n\n");
}

// Función que genera la función de log.
static void genlog(tablas *tabla, FILE *salida)
{
    if (tabla->ampliaapi[0]==0 && tabla->primaria){
        fprintf(salida,"char * %slog(%s *%s)\n{\n",tabla->abreviado,tabla->ntypedef,tabla->abreviadoc);
        fprintf(salida,"    sprintf(msglog%s, \"%s: ", tabla->abreviado, tabla->table_name);
        genformatclave(tabla,salida);
        fprintf(salida,"\"");
        genvariablesclave(tabla,salida);
        fprintf(salida,");\n");
        fprintf(salida,"    return(msglog%s);\n}\n\n", tabla->abreviado);
    }
}


// Función que genera la función de debug.
static void gendebug(tablas *tabla, FILE *salida)
{
    fprintf(salida,"char * %sdebug(%s *%s)\n{\n",tabla->abreviado,tabla->ntypedef,tabla->abreviadoc);
    fprintf(salida,"    debugestruct(&d%s,%s,msgdebug%s);\n",tabla->abreviadoc, tabla->abreviadoc, tabla->abreviado);
    fprintf(salida,"    return(msgdebug%s);\n}\n\n", tabla->abreviado);
}

    
// Función que genera las funciones que ejecutan las sentencias DELETE.
static void genquerydelete(tablas *tabla,FILE *salida)
{
  if (tabla->delete) {
     fprintf(salida,"int %sdel(%s *%s,int error)\n{\n  int vdret;\n",tabla->abreviado,tabla->ntypedeforig,tabla->abreviadocorig);
     fprintf(salida,"  %s=*%s;\n",tabla->nstaticorig,tabla->abreviadocorig);
     fprintf(salida,"  if (vddel%s==NULL) init_del%s();\n",tabla->abreviadoc,tabla->abreviadoc);  
     generalog("Borrando",tabla,"",salida,"","");
     fprintf(salida,"  vdret=ejecutacursor(vddel%s);\n",tabla->abreviadoc);
     fprintf(salida,"  if (vdret) {\n     char mensajeerror[MAXCADENA]=\"\";\n");
     fprintf(salida,"     if (error==1) cursordebug(vddel%s);\n",tabla->abreviadoc);
	 traduceerror("vddel",tabla->abreviadoc,"",salida);
     fprintf(salida,"     return(VD_EERRORACLE);\n");
     fprintf(salida,"  }\n");
     fprintf(salida,"  return(0);\n");
     fprintf(salida,"}\n\n");
   }
}


// Función que genera las funciones que ejecutan las sentencias INSERT.
static void genqueryinsert(tablas *tabla,FILE *salida)
{
    int ns;

    if (tabla->insert) {
     fprintf(salida,"int %sinsert(%s *%s,int error)\n",tabla->abreviado,tabla->ntypedeforig,tabla->abreviadocorig);
     fprintf(salida,"{\n  int vdret;\n");
     fprintf(salida,"  if (!vdins%s) init_ins%s();\n",tabla->abreviadoc,tabla->abreviadoc);
     for (ns=0;ns<tabla->numsecuen;ns++) {
         defsecuens *s=tabla->sec+ns;
         fprintf(salida,"  if (!%s->%s) {\n",tabla->abreviadoc,s->col->nombrec);
         fprintf(salida,"     if ((vdret=%ssel%s(&(%s->%s)))!=0) return(vdret);\n",tabla->abreviado,s->nombrec,tabla->abreviadoc,s->col->nombrec);
         fprintf(salida,"   }\n");
       }
     generalog("Insertando",tabla,"",salida,"","");
     fprintf(salida,"  %s=*%s;\n",tabla->nstaticorig,tabla->abreviadocorig);
     fprintf(salida,"  vdret=ejecutacursor(vdins%s);\n",tabla->abreviadoc); 
     fprintf(salida,"  if (vdret) {\n     char mensajeerror[MAXCADENA]=\"\";\n");
     fprintf(salida,"     if (error==1) cursordebug(vdins%s);\n",tabla->abreviadoc);
	 traduceerror("vdins",tabla->abreviadoc,"",salida);   
     fprintf(salida,"     return(VD_EERRORACLE);\n");
     fprintf(salida,"  }\n");
     fprintf(salida,"  return(0);\n");
     fprintf(salida,"}\n\n");
   }

}

// Función que genera las funciones que ejecutan las sentencias UPDATE.
static void genqueryupdate(tablas *tabla,FILE *salida)
{
    int ns;
    char cadena[LCADENA];
    
    for (ns=0;ns<tabla->numup;ns++) {
      defupdates *s=tabla->up+ns;
      fprintf(salida,"int %sactualiza%s(%s *%s,int error)\n",tabla->abreviado,s->nombrec,tabla->ntypedeforig,tabla->abreviadocorig);
      fprintf(salida,"{\n");
      fprintf(salida,"  int vdret = 0;\n");
      sprintf(cadena,"Actualizando %sactualiza%s: ", tabla->abreviado, s->nombrec);
      generalog(cadena,tabla,"",salida,"","");
      fprintf(salida,"  if (vdupda%s%s==NULL) init_upda%s%s();\n",tabla->abreviadoc,s->nombrec,tabla->abreviadoc,s->nombrec);
      fprintf(salida,"  %s=*%s;\n",tabla->nstaticorig,tabla->abreviadocorig);
      fprintf(salida,"  vdret=ejecutacursor(vdupda%s%s);\n",tabla->abreviadoc,s->nombrec);
      fprintf(salida,"  if (vdret) {\n     char mensajeerror[MAXCADENA]=\"\";\n");
      fprintf(salida,"     if (error==1) cursordebug(vdupda%s%s);\n",tabla->abreviadoc,s->nombrec);
      traduceerror("vdupda",tabla->abreviadoc,s->nombrec,salida);       
	  fprintf(salida,"     return(VD_EERRORACLE);\n");
      fprintf(salida,"  }\n");
      fprintf(salida,"  if (procesadascursor(vdupda%s%s)!=1) return(VD_EERRORACLE);\n",tabla->abreviadoc,s->nombrec);
      fprintf(salida,"  return(0);\n");
      fprintf(salida,"}\n\n");
    }
}

// Función que genera las funcion de acceso a interfases
static void genqueryinter(tablas *tabla,FILE *salida)
{
   int i;
   char nombreselect[LCADENA];

   fprintf(salida,"int %sinter(%s *%s)\n",tabla->abreviado,tabla->ntypedeforig,tabla->abreviadocorig);
   fprintf(salida,"{\n");
   fprintf(salida,"  int vdret = 0;\n");
   fprintf(salida,"  if (vdsel%s%s==NULL) init_sel%s%s();\n",tabla->abreviadoc,tabla->nombrec,tabla->abreviadoc,tabla->nombrec);
   fprintf(salida,"  memset(&%s,0,sizeof(%s));\n",tabla->nstaticorig, tabla->nstaticorig);
   for (i=0;i<tabla->numprimaria;i++){
       if (strcmp(tabla->primaria[i]->tipoc,"char"))
           fprintf(salida,"  %s.%s = %s->%s;\n", tabla->nstatic, tabla->primaria[i]->nombrec, tabla->abreviadocorig, tabla->primaria[i]->nombrec);
       else
           fprintf(salida,"  strcpy(%s.%s,%s->%s);\n", tabla->nstatic, tabla->primaria[i]->nombrec, tabla->abreviadocorig, tabla->primaria[i]->nombrec);
   }
   fprintf(salida,"  vdret=ejefetchcursor(vdsel%s%s);\n",tabla->abreviadoc, tabla->nombrec);
   fprintf(salida,"  if (vdret) {\n");
   sprintf(nombreselect,"vdsel%s%s",tabla->abreviadoc, tabla->nombrec);
   generalog("Ejefetch",tabla, nombreselect,salida,"N","vdret");
   fprintf(salida,"    return(VD_EERRORACLE);\n");
   fprintf(salida,"  }\n\n");
   fprintf(salida,"  *%s=%s;\n", tabla->abreviadoc, tabla->nstatic);
   fprintf(salida,"  return(vdret);\n");
   fprintf(salida,"}\n\n");
}

// Función que genera las funciones que ejecutan las sentencias SELECT.
static void genqueryselect(tablas *tabla,FILE *salida)
{
    int ns;
    
    for (ns=0;ns<tabla->numsel;ns++) {
      defselects *s=tabla->sel+ns;
      if (s->recorreproc) {
         genauxrecorre(tabla,s,salida);
       }
      genprototiposel(tabla,s,salida);
      if (s->recorre==0 && s->recorreproc==0) {
         generaselectnormal(tabla,s,salida);
       }
      if (s->recorre) {
         generabusca(tabla,s,salida);
         generanext(tabla,s,salida);
       }
      if (s->recorreproc) {
         generarecorreproc(tabla,s,salida);
       }
    }
}


// Funcion que copia la cabecera de comentarios del fichero
void copiaeldef(tablas *tabla,FILE *salida)
{
    char nombre[MAXPATH];
    FILE *entrada;
    char buffer[MAXCADENA];
    sprintf(nombre,"%s.DEF",tabla->table_name);
    fprintf(salida,"// Modulo generado automaticamente a partir de %s.DEF\n",tabla->table_name);
    entrada=fopenpath(nombre,"r");
    while (fgetss(buffer,sizeof(buffer),entrada)) {
        fprintf(salida,"//%s\n",buffer);
    }
    fprintf(salida,"\n");
}

void generac(tablas *tabla)
{
  FILE *salida;
  char incluye[MAXLNOMBRE];
  extern char include[MAXPATH];

  // Guardamos en el log
  sprintf(incluye,"%s%s.c",tabla->ampliaapi, tabla->table_name);
  v10log(LOGNORMAL," Generando fichero %s\n",incluye);

  // Generamos el fichero cabecera
  if (NULL==(salida=fopenpath(incluye,"w"))){
      final(("No puedo abrir %s.\nCompruebe que %s no sea de SOLO LECTURA\n y que tenga privilegios de escritura",incluye,incluye));
  }

  // Comentarios del fichero cabecera
  copiaeldef(tabla,salida);

  // Incluimos el fichero cabecera genérico que se ha indicado por parámetro.
  fprintf(salida,"#include \"%s\"\n",include);
 
  // Generamos las querys que se han de implementar.
  generalsq(tabla,salida);

  // Declaramos los campos estáticos.
  genstatics(tabla,salida);
  
  // Generamos la función que finaliza los cursosres
  genfin(tabla,salida); 

  // Generamos la función que incializa los cursores
  geninit(tabla,salida);

  // Generamos la función que devuelve el diccionario
  genaccesodiccionario(tabla,salida);

  // Generamos las funciones que ejecutan las sentencias SELECT.
  genqueryselect(tabla,salida);
  
  // Generamos la funcion lock.
  genbloqueo(tabla,salida);

  // Generamos los updates
  genqueryupdate(tabla,salida);

  // Generamos las secuencias
  generasecuencias(tabla,salida);
  
  // Generamos los inserts
  genqueryinsert(tabla,salida);

  // Generamos los deletes
  genquerydelete(tabla,salida);

  // Generamso la función para las interfases
  if (tabla->ampliaapi[0]==0 && tabla->interfase)  genqueryinter(tabla,salida);

  // Generamos la funcion de log
  genlog(tabla,salida);

  // Generamos la función de debug
  gendebug(tabla,salida);

  fclose(salida);
}