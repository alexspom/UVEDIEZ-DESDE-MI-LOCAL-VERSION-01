/****
* VDGENCC.H - Generación automática del código c para ejecutar consultas oracle.
* 
* Propósito: Funciones comunes para la generación del fichero FICHERO.H
*           
* Autor	   : MGM
* Fecha    : 06-11-2007
****
* Modificaciones:
***/

#include "vdgenclibre.h"


static columns *colaux;
static int numcol=0;


// Función que define las longitudes de los campos char
static void longitud_campo(columns *column, FILE *salida)
{
    int i=0,alta=0;
    
    for (i=0;i<numcol;i++){
        if (!strcmp(colaux[i].column_name,column->column_name)) {
            alta=1;
            break;
        }
    }
    if (!alta){
        colaux[numcol]=*column;
        numcol++;
        if (!strcmp(column->tipoc,"char"))
            fprintf(salida,"#ifndef L%s\n#define L%s %ld\n#endif\n\n", column->column_name, column->column_name, column->longitud);
    }
}   

// Función que determina los campos que tiene que tener la estructura
static void campo_estructura(columns *column, FILE *salida)
{
    int i=0,alta=0;
    
    for (i=0;i<numcol;i++){
        if (!strcmp(colaux[i].column_name,column->column_name)) {
            strcpy(column->tipoc,colaux[i].tipoc);
            alta=1;
            break;
        }
    }
    if (!alta){
        colaux[numcol]=*column;
        numcol++;
	    fprintf(salida,"        %-7.7s %s",column->tipoc,column->nombrec);
		if (!strcmp(column->tipoc,"char")) 
		    fprintf(salida,"[L%s]",column->column_name);
        fprintf(salida,";\n");
    }
}

// Funcion que genera el .h
void generah(cursor *cursores, int numcur, columns *col, int numcolextra,char **lineash,int nlinh)
{
  FILE *salida;
  extern char fichero[MAXPATH];
  char nomfichero[MAXPATH];
  extern char include[MAXPATH];
  int i,j;
  
  colaux=calloc(MAXCOLUMNS,sizeof(columns));

  sprintf(nomfichero,"%s.h", fichero);
  v10log(LOGNORMAL," Generando fichero %s\n",nomfichero);

  // Generamos el fichero cabecera
  if (NULL==(salida=fopenpath(nomfichero,"w"))){
      final(("No puedo abrir %s.\nCompruebe que %s no sea de SOLO LECTURA\n y que tenga privilegios de escritura",fichero,fichero));
  }

  // Comentarios del fichero cabecera
  fprintf(salida,"// Fichero generado automaticamente a partir de %s.DEF\n\n",fichero);

  // Incluimos el diccionario de campos
  fprintf(salida,"VDEXPORT diccionario d%s;\n", nomabreviadoc);

    //////////////////////////////////////////////////
  // DECLARAMOS LAS LONGITUDES DE LOS CAMPOS DE LA TABLA
  ////////////////////////////////////////////////////
  for(i=0;i<numcolextra;i++){
      longitud_campo(&col[i], salida);
  }

  for(i=0;i<numcur;i++){
      for(j=0;j<cursores[i].numdef;j++){
          longitud_campo(&cursores[i].coldef[j], salida);
      }
      for(j=0;j<cursores[i].numbind;j++){
          longitud_campo(&cursores[i].colbind[j], salida);
      }
  }  

  //////////////////////////////////////////////////
  // DECLARAMOS LA ESTRUCTURA DE DATOS DE LA TABLA
  //////////////////////////////////////////////////
  fprintf(salida,"typedef struct {\n");
  numcol=0;
  for(i=0;i<numcolextra;i++){
      campo_estructura(&col[i], salida);
  }

  for(i=0;i<numcur;i++){
      for(j=0;j<cursores[i].numdef;j++){
          campo_estructura(&cursores[i].coldef[j], salida);
      }
      for(j=0;j<cursores[i].numbind;j++){
          campo_estructura(&cursores[i].colbind[j], salida);
      }
  }

  fprintf(salida,"} vd%ss; \n\n", nomabreviadoc);

  //////////////////////////////////////////////////
  // DECLARAMOS LOS PROTOTIPOS DE LAS FUNCIONES
  //////////////////////////////////////////////////

  // Prototipo de la función diccionario.
  fprintf(salida,"\nVDEXPORT diccionario *%sdamediccionario(void);\n", nomabreviado);

  for(i=0;i<numcur;i++){
    switch (cursores[i].tipocur){
        case GCURSOR:fprintf(salida,"VDEXPORT int %sbusca%s(",nomabreviado,cursores[i].nombrec);
                      break;
        case GSELECT: fprintf(salida,"VDEXPORT int %ssel%s(",nomabreviado,cursores[i].nombrec);
                      break;
        case GPROCEDURE: fprintf(salida,"VDEXPORT int %sproc%s(",nomabreviado,cursores[i].nombrec);
                         break;
    }
    for(j=0;j<cursores[i].numbind;j++){
       if (j>0) fprintf(salida,",");
       if(!strcmp(cursores[i].colbind[j].tipoc,"char")) 
          fprintf(salida,"%s *%s", cursores[i].colbind[j].tipoc, cursores[i].colbind[j].nombrec);
       else
          fprintf(salida,"%s %s", cursores[i].colbind[j].tipoc, cursores[i].colbind[j].nombrec);
    }
    switch(cursores[i].tipocur){
        case GCURSOR:
        case GSELECT:
            if (j>0) fprintf(salida,",");
            fprintf(salida,"vd%ss *%s);\n", nomabreviadoc, nomabreviadoc);
            break;
        case GPROCEDURE:
            if (j>0) fprintf(salida,",");
            fprintf(salida,"vd%ss *%s);\n", nomabreviadoc, nomabreviadoc);
//            fprintf(salida,");\n");
            break;
    }

    if (cursores[i].tipocur==GCURSOR) fprintf(salida,"VDEXPORT int %snext%s(vd%ss *%s);\n",nomabreviado, cursores[i].nombrec, nomabreviadoc, nomabreviadoc);
  }

  fprintf(salida,"VDEXPORT char * %sdebug(vd%ss *%s);\n",nomabreviado,nomabreviadoc,nomabreviadoc);

  if (nlinh) fprintf(salida,"\n//Codigo incluido explicitamente en el DEF\n");
  for (i=0;i<nlinh;i++) {
      fprintf(salida,"%s\n",lineash[i]);
  }


  fclose(salida);
}
