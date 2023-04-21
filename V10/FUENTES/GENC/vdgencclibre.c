/****
* VDGENCCLIBRE.C - Generaci�n autom�tica del c�digo c para ejecutar consultas.
* 
* Prop�sito: Funciones comunes para la generaci�n del fichero FICHERO.C
*           
* Autor	   : MGM
* Fecha    : 06-11-2007
****
* Modificaciones:
*	18-01-2010 (MGM): Inicializar el cursor solo cuando se va a utilizar.
***/

#include "vdgenclibre.h"


static columns *colaux;
static int numcol;

// Funci�n que genera la funci�n de debug.
static void gendebug(cursor *cursores, FILE *salida)
{
    fprintf(salida,"\nchar * %sdebug(vd%ss *%s)\n{\n",nomabreviado,nomabreviadoc, nomabreviadoc);
    fprintf(salida,"    debugestruct(&d%s,%s,msgdebug%s);\n",nomabreviadoc, nomabreviadoc, nomabreviadoc);
    fprintf(salida,"    return(msgdebug%s);\n}\n\n", nomabreviadoc);
}

// Funci�n que genera la funci�n next
static void genfuncnext(cursor *cursores, FILE *salida)
{
    fprintf(salida,"\nint %snext%s(vd%ss *%s)\n{\n",nomabreviado, cursores->nombrec, nomabreviadoc, nomabreviadoc);
    fprintf(salida,"    int vdret;\n");
    fprintf(salida,"    vdret=fetchcursor(vdsel%s);\n", cursores->nombrec);
    fprintf(salida,"    if (!vdret) {\n");
    fprintf(salida,"        *%s=svd%s;\n", nomabreviadoc, nomabreviadoc);
    fprintf(salida,"        v10log(LOGDEBUGAPI,\"Siguiente vdret %%d. \\n\", vdret);\n");
    fprintf(salida,"        return(vdret);\n    }\n");
    fprintf(salida,"    if(vdret!=NOFOUND) cursordebug(vdsel%s);\n", cursores->nombrec);
    fprintf(salida,"    return(VD_EERRORACLE);\n}\n");

}

// Funci�n que genera la cabecera de una funci�n
static void cabecerafuncion(cursor *cursores, FILE *salida)
{
    int i;

    switch(cursores->tipocur){
        case GCURSOR:
            fprintf(salida,"\nint %sbusca%s(",nomabreviado,cursores->nombrec);
            break;
        case GSELECT:
            fprintf(salida,"\nint %ssel%s(",nomabreviado,cursores->nombrec);
            break;
        case GPROCEDURE:
            fprintf(salida,"\nint %sproc%s(",nomabreviado,cursores->nombrec);
            break;
    }
    for(i=0;i<cursores->numbind;i++){
        if (i>0) fprintf(salida,",");
        if(!strcmp(cursores->colbind[i].tipoc,"char")) 
            fprintf(salida,"%s *%s", cursores->colbind[i].tipoc, cursores->colbind[i].nombrec);
        else
            fprintf(salida,"%s %s", cursores->colbind[i].tipoc, cursores->colbind[i].nombrec);
    }
    switch(cursores->tipocur){
        case GCURSOR:
        case GSELECT:
            if (i>0) fprintf(salida,",");
            fprintf(salida,"vd%ss *%s)\n{\n", nomabreviadoc, nomabreviadoc);
            break;
        case GPROCEDURE:
            if (i>0) fprintf(salida,",");   
            fprintf(salida,"vd%ss *%s)\n{\n", nomabreviadoc, nomabreviadoc);
//            fprintf(salida,")\n{\n");
            break;
    }
}

// Funci�n que genera el cuerpo de las funciones                      
static void genfuncselect(cursor *cursores, FILE *salida)
{
    int i;
    char nomfuncion[LCADENASMALL];

    cabecerafuncion(cursores, salida);
    fprintf(salida,"    int vdret;\n");
    fprintf(salida,"    if (vdsel%s==NULL) init_sel%s();\n",cursores->nombrec, cursores->nombrec);
    fprintf(salida,"    memset(&svd%s,0,sizeof(svd%s));\n",nomabreviadoc, nomabreviadoc);
    for(i=0;i<cursores->numbind;i++){
        if(!strcmp(cursores->colbind[i].tipoc,"char")) 
            fprintf(salida,"    strcpy(svd%s.%s,%s);\n", nomabreviadoc, cursores->colbind[i].nombrec, cursores->colbind[i].nombrec);
        else
            fprintf(salida,"    svd%s.%s=%s;\n", nomabreviadoc, cursores->colbind[i].nombrec, cursores->colbind[i].nombrec);
    }

    switch(cursores->tipocur){
        case GSELECT:
            sprintf(nomfuncion,"%ssel%s",nomabreviado,cursores->nombrec);
        case GCURSOR:
            sprintf(nomfuncion,"%sbusca%s",nomabreviado,cursores->nombrec);
            fprintf(salida,"    vdret=ejefetchcursor(vdsel%s);\n",cursores->nombrec);
            fprintf(salida,"    if(vdret) {\n");
            fprintf(salida,"        v10log(LOGDEBUGAPI,\"Ejefetch %s vdret %%d. \\n\", vdret);\n", nomfuncion);
            break;
        case GPROCEDURE:
            sprintf(nomfuncion,"%sproc%s",nomabreviado,cursores->nombrec);
            fprintf(salida,"    vdret=ejecutacursor(vdsel%s);\n",cursores->nombrec);
            fprintf(salida,"    if(vdret) {\n");
            fprintf(salida,"        v10log(LOGDEBUGAPI,\"Ejecuta %s vdret %%d. \\n\", vdret);\n", nomfuncion);
            break;
    }
    fprintf(salida,"        return(VD_EERRORACLE);\n    }\n");
    switch(cursores->tipocur){
        case GSELECT:
        case GCURSOR:
        case GPROCEDURE:
            fprintf(salida,"    *%s=svd%s;\n", nomabreviadoc, nomabreviadoc);
            break;
    }
    fprintf(salida,"    return(vdret);\n}\n");

}


// Funcion que genera las funciones necesarias para el fichero c
static void genfunciones(cursor *cursores, int numcur, FILE *salida)
{
    int i;

    for(i=0;i<numcur;i++){
        switch(cursores[i].tipocur){
            case GCURSOR:
                genfuncselect(&cursores[i],salida);
                genfuncnext(&cursores[i],salida);
                break;
            case GSELECT:
            case GPROCEDURE:
                genfuncselect(&cursores[i],salida);
                break;
        }
    }
}

// Funci�n que genere el acceso al diccionario
static void genaccesodiccionario(cursor *cursores, int numcur, FILE *salida)
{
    fprintf(salida,"\ndiccionario *%sdamediccionario(void)\n{\n", nomabreviado);
    fprintf(salida,"    return(&d%s);\n}\n", nomabreviadoc);
}

// Funci�n que genera la funci�n de inicializaci�n de los cursores
static void geninit(cursor *cursores, int numcur, FILE *salida)
{
    int i,j;
   
    for(i=0;i<numcur;i++){
		// Generamos la cabecera de la funci�n
		fprintf(salida,"\nstatic void init_sel%s(void)\n{\n", cursores[i].nombrec);
		fprintf(salida,"    int nc;\n\n");
		fprintf(salida,"    for(nc=0;nc<dvd%s[0].numcol;nc++) dvd%s[0].c[nc].offset-=(size_t)&svd%s;\n",
				nomabreviadoc, nomabreviadoc, nomabreviadoc);
 
        fprintf(salida,"\n    vdsel%s=abrecursordebug(SEL%s,%d);\n", cursores[i].nombrec, cursores[i].nombre,soradebug);
        fprintf(salida,"    definetodo(vdsel%s,",cursores[i].nombrec);
        for(j=0;j<cursores[i].numdef;j++){
            if (!strcmp(cursores[i].coldef[j].tipoc,"char"))
                fprintf(salida,"svd%s.%s,sizeof(svd%s.%s),%s,\n               ", 
                     nomabreviadoc, cursores[i].coldef[j].nombrec,
                     nomabreviadoc,cursores[i].coldef[j].nombrec,cursores[i].coldef[j].tipovd);
            else
                fprintf(salida,"&svd%s.%s,sizeof(svd%s.%s),%s,\n               ", 
                     nomabreviadoc, cursores[i].coldef[j].nombrec,
                     nomabreviadoc,cursores[i].coldef[j].nombrec,cursores[i].coldef[j].tipovd);
        }
        fprintf(salida,"NULL);\n");
        fprintf(salida,"    bindtodo(vdsel%s,",cursores[i].nombrec);
        for(j=0;j<cursores[i].numbind;j++){
            if (!strcmp(cursores[i].colbind[j].tipoc,"char"))
                fprintf(salida,"\"%s\",svd%s.%s,sizeof(svd%s.%s),%s,\n             ", 
                     cursores[i].colbind[j].column_name, nomabreviadoc, cursores[i].colbind[j].nombrec,
                     nomabreviadoc,cursores[i].colbind[j].nombrec,cursores[i].colbind[j].tipovd);
            else
                fprintf(salida,"\"%s\",&svd%s.%s,sizeof(svd%s.%s),%s,\n             ", 
                     cursores[i].colbind[j].column_name, nomabreviadoc, cursores[i].colbind[j].nombrec,
                     nomabreviadoc,cursores[i].colbind[j].nombrec,cursores[i].colbind[j].tipovd);
        }
        fprintf(salida,"NULL);\n\n");
		fprintf(salida,"    if (init == 0) {\n");
		fprintf(salida,"        atexit(fin_vd_%s);\n", nomabreviado);
		fprintf(salida,"        init = 1;\n");
		fprintf(salida,"    }\n}\n");
    }
}

// Funci�n que genera la funci�n que cierra los cursores
static void genfin(cursor *cursores, int numcur, FILE *salida)
{
    int i;

    fprintf(salida,"\nstatic void fin_vd_%s(void)\n{\n", nomabreviado);

    for(i=0;i<numcur;i++){
        fprintf(salida,"    if(vdsel%s){\n", cursores[i].nombrec);
        fprintf(salida,"        liberacursor(vdsel%s);\n", cursores[i].nombrec);
        fprintf(salida,"        vdsel%s=NULL;\n    }\n", cursores[i].nombrec);
    }

    fprintf(salida,"}\n\n");
}

// Funci�n que genera los campos del diccionario
static void campo_diccionario(columns *column, FILE *salida)
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
        if (numcol>1) fprintf(salida,",\n");
        fprintf(salida,"    {\"%s\",%s,(size_t)&svd%s.%s,sizeof(svd%s.%s)}",
                column->column_name, column->tipovd, nomabreviadoc, column->nombrec, nomabreviadoc, column->nombrec);
    }
}


// Funci�n que genera las variables est�ticas del .DEF
static void genstatics(cursor *cursores, int numcur, columns *col, int numcolextra, FILE *salida)
{
    int i,j;

    fprintf(salida,"\nstatic vd%ss svd%s;\n", nomabreviadoc, nomabreviadoc);
    fprintf(salida,"\nstatic diccols colvd%s[]={ \n", nomabreviadoc);

    for(i=0;i<numcolextra;i++){
      campo_diccionario(&col[i], salida);
    }

    for(i=0;i<numcur;i++){
      for(j=0;j<cursores[i].numdef;j++){
          campo_diccionario(&cursores[i].coldef[j], salida);
      }
      for(j=0;j<cursores[i].numbind;j++){
          campo_diccionario(&cursores[i].colbind[j], salida);
      }
    }  
    fprintf(salida,"\n    };\n");

    fprintf(salida,"\nstatic diccionarios dvd%s[]={\n", nomabreviadoc);
    fprintf(salida,"    {colvd%s,%ld}\n    };\n", nomabreviadoc, numcol);
    fprintf(salida,"\ndiccionario d%s={dvd%s,1};\n", nomabreviadoc, nomabreviadoc);

    fprintf(salida,"\nstatic char msgdebug%s[LCADENABIG];\n", nomabreviadoc);
	fprintf(salida,"\nstatic int init=0;\n\n");

}

// Funci�n que genera los defines de los cursores
static void generalsq(cursor *cursores, int numcur, FILE *salida)
{
    int i;

    for (i=0;i<numcur;i++){
        fprintf(salida,"#define SEL%s \"%s\"\n", cursores[i].nombre, cursores[i].sql);
        fprintf(salida,"static v10cursors *vdsel%s;\n", cursores[i].nombrec);
    }
}

// Funcion que copia la cabecera de comentarios del fichero
static void copiaeldef(cursor *cursores, FILE *salida, char *fichero)
{
    char nombre[MAXPATH];
    FILE *entrada;
    char buffer[MAXCADENA];
    sprintf(nombre,"%s.DEF",fichero);
    fprintf(salida,"// Modulo generado automaticamente a partir de %s.DEF\n",fichero);
    entrada=fopenpath(nombre,"r");
    while (fgetss(buffer,sizeof(buffer),entrada)) {
        fprintf(salida,"//%s\n",buffer);
    }
    fprintf(salida,"\n");
}

// Funci�n que genera el fichero .c a partir del fichero .DEF
void generac(cursor *cursores, int numcur, columns *col, int numcolextra,char **lineasc,int nlinc)
{
  FILE *salida;
  extern char fichero[MAXPATH];
  char nomfichero[MAXPATH];
  extern char include[MAXPATH];
  int i;

  colaux=calloc(MAXCOLUMNS,sizeof(columns));
  numcol=0;

  sprintf(nomfichero,"%s.c", fichero);
  v10log(LOGNORMAL," Generando fichero %s\n",nomfichero);

  // Generamos el fichero cabecera
  if (NULL==(salida=fopenpath(nomfichero,"w"))){
      final(("No puedo abrir %s.\nCompruebe que %s no sea de SOLO LECTURA\n y que tenga privilegios de escritura",fichero,fichero));
  }

  // Comentarios del fichero cabecera
  copiaeldef(cursores,salida,fichero);

  // Incluimos el fichero cabecera gen�rico que se ha indicado por par�metro.
  fprintf(salida,"#include \"%s\"\\\n\n",include);
 
  // Generamos las querys que se han de implementar.
  generalsq(cursores,numcur,salida);

  // Declaramos los campos est�ticos.
  genstatics(cursores,numcur,col,numcolextra,salida);
  
  // Generamos la funci�n que finaliza los cursosres
  genfin(cursores,numcur,salida); 

  // Generamos la funci�n que incializa los cursores
  geninit(cursores,numcur,salida); 

  // Generamos la funci�n que devuelve el diccionario
  genaccesodiccionario(cursores,numcur,salida);

  // Generamos las funciones que ejecutan las sentencias SELECT.
  genfunciones(cursores,numcur,salida);

  // Generamos la funci�n de debug
  gendebug(cursores,salida);
  if (nlinc) fprintf(salida,"\n//Codigo incluido explicitamente en el DEF\n");
  for (i=0;i<nlinc;i++) {
      fprintf(salida,"%s\n",lineasc[i]);
  }  
  fclose(salida);
}