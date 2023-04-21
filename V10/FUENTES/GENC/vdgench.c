/****
* VDGENCC.H - Generación automática del código c para acceder a una tabla.
* 
* Propósito: Funciones comunes para la generación del fichero TABLA.H
*           
* Autor	   : MGM
* Fecha    : 20-10-2007
****
* Modificaciones:
***/

#include "vdgenc.h"

char damecampomaxmin(char *dest,char **listacampos){
	char *pnombre;

	memset(dest,0,sizeof(dest));
	if (*listacampos){
		pnombre=strchr(*listacampos,',');
		if (!pnombre && (strlen(*listacampos)>0)) strcpy(dest,*listacampos);
		else {
			strncpy(dest,*listacampos,(pnombre-*listacampos));
			*(dest + (pnombre-*listacampos))='\0';
		}
		*listacampos=pnombre;
		if (pnombre) *listacampos=pnombre+1;
		else *listacampos=pnombre;
	}
	_strlwr(dest);
	return(*dest);
}


// Funcion que genera el .h
void generah(tablas *tabla)
{
  FILE *salida;
  int nc,ns;
  char incluye[MAXLNOMBRE];
  char nommaxmin[MAXLNOMBRE],*plistanomb;

  // Guardamos en el log
  sprintf(incluye,"%s%s.h",tabla->ampliaapi,tabla->table_name);
  v10log(LOGNORMAL," Generando fichero %s\n",incluye);

  // Generamos el fichero cabecera
  if (NULL==(salida=fopenpath(incluye,"w"))){
      final(("No puedo abrir %s.\nCompruebe que %s no sea de SOLO LECTURA\n y que tenga privilegios de escritura",incluye,incluye));
  }

  // Comentarios del fichero cabecera
  fprintf(salida,"// Modulo generado automaticamente a partir de %s.DEF\n\n",tabla->table_name);

  // Incluimos el diccionario de campos
  fprintf(salida,"VDEXPORT diccionario d%s;\n", tabla->abreviadoc);

  // Si es un apliapi incluimos el número de columnas de la estructura original
  if (tabla->ampliaapi[0]==0) {
      if (tabla->rowid)
          fprintf(salida,"#define %sNUMCOL\t%d\n", tabla->abreviado, tabla->numcol+tabla->numagrup);
      else
          fprintf(salida,"#define %sNUMCOL\t%d\n", tabla->abreviado, tabla->numcol+tabla->numagrup+1);
  }

  // Incluimos las longitudes de los campos extra
  for (nc=0;nc<tabla->numcol;nc++) {
      columns *c=tabla->col+nc;
	  if (c->tabla || strcmp(c->tipoc,"char")) continue;
      if (!strcmp(c->column_name,"ROWID")) continue;
      fprintf(salida,"#define L%s %d\n",c->column_name,c->longitud);
   }

  //////////////////////////////////////////////////
  // DECLARAMOS LA ESTRUCTURA DE DATOS DE LA TABLA
  //////////////////////////////////////////////////
  fprintf(salida,"typedef struct {\n");

  // Si es un apliapi el primer campo será la estructura de la tabla original. Si no el primer campo es el ROWID
  if (tabla->ampliaapi[0]==0)
	fprintf(salida,"        char    rowid[ROWIDLON];\n");
  else
	fprintf(salida,"        %s %s;\n", tabla->ntypedeforig, tabla->abreviadocorig);

  for (nc=0;nc<tabla->numcol;nc++) {
      columns *c=tabla->col+nc;
      if (!strcmp(c->column_name,"MIROWID")) continue;
      // Si es un apliapi solo guardamos los campos que no están en la estructura original
	  if (tabla->ampliaapi[0]==0 || !c->tabla){
	      fprintf(salida,"        %-7.7s %s",c->tipoc,c->nombrec);
		  if (strcmp(c->tipoc,"char")==0) {
			 fprintf(salida,"[L%s]",c->column_name);
		  }
		  fprintf(salida,";\n");
	  }
   }

  
  if (tabla->genmax) {
      columns *colmaxmin;
	  plistanomb = tabla->genmax;
	  while (damecampomaxmin(nommaxmin,&plistanomb)) {
		  colmaxmin=busca_columna(tabla,nommaxmin);
		  fprintf(salida,"        %-7.7s genmax%s",colmaxmin->tipoc,nommaxmin);
		  if (strcmp(colmaxmin->tipoc,"char")==0) {
			 fprintf(salida,"[L%s]",colmaxmin->column_name);
		   }
		  fprintf(salida,";\n");
	  }
  }
  if (tabla->genmin) {
      columns *colmaxmin;
	  plistanomb = tabla->genmin;
	  while (damecampomaxmin(nommaxmin,&plistanomb)) {
		  colmaxmin=busca_columna(tabla,nommaxmin);
		  fprintf(salida,"        %-7.7s genmin%s",colmaxmin->tipoc,nommaxmin);
		  if (strcmp(colmaxmin->tipoc,"char")==0) {
			 fprintf(salida,"[L%s]",colmaxmin->column_name);
		   }
		  fprintf(salida,";\n");
	  }
  }
  if (tabla->gencount) fprintf(salida,"        double  gencount;\n"); 
  if (tabla->gensum) fprintf(salida,"        double  gensum;\n"); 

  fprintf(salida,"    } %s;\n\n",tabla->ntypedef);

  ////////////////////////////////////////////////
  // INCLUIMOS LOS PROTOTIPOS DE LAS FUNCIONES
  ////////////////////////////////////////////////
  fprintf(salida,"// Prototipos de funciones definidas en %s%s.C\n",tabla->ampliaapi, tabla->table_name);

  // Guardamos las funciones correspondientes al diccionario 
  fprintf(salida,"VDEXPORT diccionario *%sdamediccionario(void);\n",tabla->abreviado);

  // Guardamos las funciones de querys.
  for (ns=0;ns<tabla->numsel;ns++) {
      defselects *s=tabla->sel+ns;
      char hayagrup=(s->gencount||s->genmax||s->genmin||s->gensum);

      if (s->recorre==0) {
         if (s->recorreproc==0) {
            fprintf(salida,"VDEXPORT int %ssel%s(",tabla->abreviado,s->nombrec);
          } else {
            fprintf(salida,"VDEXPORT void %sprocesa%s(",tabla->abreviado,s->nombrec);
          }
       } else {
         fprintf(salida,"VDEXPORT int %sbusca%s(",tabla->abreviado,s->nombrec);
       }
      for (nc=0;nc<s->numcol;nc++) {
          columns *c=s->col[nc];
          fprintf(salida,"%s %s%s,",c->tipoc,strcmp(c->tipoc,"char")==0?"*":"",c->nombrec);
       }
      if (s->recorreproc==0) {
         if (hayagrup) fprintf(salida,"%s *%s);\n",tabla->ntypedef,tabla->abreviadoc);
         else fprintf(salida,"%s *%s);\n",tabla->ntypedeforig,tabla->abreviadocorig);
       } else {
         fprintf(salida,"int (*func)(%s *%s,void *ptr),void *ptr,long cuantos);\n",tabla->ntypedef,tabla->abreviadoc);
       }
      if (s->recorre) {
         if (hayagrup) fprintf(salida,"VDEXPORT int %snext%s(%s *%s);\n",tabla->abreviado,s->nombrec,tabla->ntypedef,tabla->abreviadoc);
         else fprintf(salida,"VDEXPORT int %snext%s(%s *%s);\n",tabla->abreviado,s->nombrec,tabla->ntypedeforig,tabla->abreviadocorig);
       }
  }

  // Prototipo de la funcion lock
  if (tabla->lock) {
	  fprintf(salida,"VDEXPORT int %slock(%s *%s,int wait,int verificar,...);\n",tabla->abreviado,tabla->ntypedeforig,tabla->abreviadocorig);
  }

  // Prototipo de los updates
  for (ns=0;ns<tabla->numup;ns++) {
      defupdates *s=tabla->up+ns;
      fprintf(salida,"VDEXPORT int %sactualiza%s(%s *%s,int error);\n",tabla->abreviado,s->nombrec,tabla->ntypedeforig,tabla->abreviadocorig);
  }

  // Prototipo de las secuencias
  for (ns=0;ns<tabla->numsecuen;ns++) {
      defsecuens *s=tabla->sec+ns;
      fprintf(salida,"VDEXPORT int %ssel%s(long *donde);\n",tabla->abreviado,s->nombrec);
  }

  // Prototipo del insert
  if (tabla->insert) {
      fprintf(salida,"VDEXPORT int %sinsert(%s *%s,int error);\n",tabla->abreviado,tabla->ntypedeforig,tabla->abreviadocorig);
  } 

  // Prototipo del delete
  if (tabla->delete) {
      fprintf(salida,"VDEXPORT int %sdel(%s *%s,int error);\n",tabla->abreviado,tabla->ntypedeforig,tabla->abreviadocorig);
  }

  if (tabla->ampliaapi[0]==0 && tabla->primaria && tabla->interfase)
      fprintf(salida,"VDEXPORT int %sinter(%s *%s);\n", tabla->abreviado, tabla->ntypedeforig, tabla->abreviadocorig);

  if (tabla->ampliaapi[0]==0 && tabla->primaria)
    fprintf(salida,"VDEXPORT char *%slog(%s *%s);\n",tabla->abreviado,tabla->ntypedeforig, tabla->abreviadocorig);

  fprintf(salida,"char * %sdebug(%s *%s);\n",tabla->abreviado,tabla->ntypedef,tabla->abreviadoc);
  
  fclose(salida);
}
