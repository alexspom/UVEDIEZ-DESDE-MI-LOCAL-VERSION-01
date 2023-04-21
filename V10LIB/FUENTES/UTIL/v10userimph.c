#include "V10user.h"

#define MAXCOLAPP  5000

typedef struct {
	char tipostatus[3+1];
	long status;
	char dabstatus[10+1];
	char desstatus[50+1];
} statuss;
static statuss status;

static char  SELSTATUS[]="SELECT TIPOSTATUS,DABSTATUS,DESSTATUS,STATUS "\
                         " FROM %s "\
                         " ORDER BY TIPOSTATUS,STATUS ";
static char  SELSTATUSX[]="SELECT TIPOSTATUS,DABSTATUS,DESSTATUS,STATUS "\
                          " FROM %s "\
                          " WHERE TIPOAPP !='S' "\
                          "ORDER BY TIPOSTATUS,STATUS ";

static v10cursors *vdselstatus;


static void fincursoresstatus(void)
{
	liberacursor(vdselstatus);
}

static void initcursoresstatus(int extension)
{
	char selstatus[MAXCADENA];
	
    if (extension) sprintf(selstatus,SELSTATUSX,user.status);
	else sprintf(selstatus,SELSTATUS,user.status);

	vdselstatus=abrecursor(selstatus);
	definetodo(vdselstatus,status.tipostatus,sizeof(status.tipostatus),V10CADENA,
		status.dabstatus,sizeof(status.dabstatus),V10CADENA,
		status.desstatus,sizeof(status.desstatus),V10CADENA,
		&status.status,sizeof(status.status),V10LONG,NULL);
	
	atexit(fincursoresstatus);
}

void declaradefineguion(char *campo,FILE *ficsal)
{
	char aux[MAXCADENA];
	long lon=0;
	int i,j;
	for (i=0;i<user.ntables;i++) {
		for (j=0;j<user.table[i]->ncolumns;j++) {
			if (stricomp(user.table[i]->column[j]->column_name,campo)==0) lon=user.table[i]->column[j]->longitud;
		}
	}
	if (i>=user.ntables) return;
	strfill(aux,'-',lon-1);                            
	fprintf(ficsal,"#define C%sVACIO \"%s\"\n",campo,aux);
	fprintf(ficsal,"#define S%sVACIO \'%s\'\n",campo,aux);
}

void imprimesth(int generah,int extension)
{
	FILE *ficsal;
	if ((ficsal=fopen(user.sthficsal,"w"))==NULL) {
        final(("No puedo abrir fichero de salida: %s.",user.sthficsal));
	}
	v10log(1,"Imprimiendo el fichero %s...\n",user.sthficsal);
	fprintf(ficsal,"/* USUARIO: %s. */\n\n",user.username);
	fprintf(ficsal,"/* Defines de los status. */\n");
	if (generah) {
        if (!vdselstatus) initcursoresstatus(extension);
        if (ejecutacursor(vdselstatus)) {
			cursordebug(vdselstatus);
		} else {
			while (fetchcursor(vdselstatus)==0) {
                if (extension) fprintf(ficsal,"#ifndef ST%s%-10.10s\n#define  ST%s%-10.10s    %4ld  /* %s */\n#endif\n",status.tipostatus,status.dabstatus,status.tipostatus,status.dabstatus,status.status,status.desstatus);
				else fprintf(ficsal,"#define  ST%s%-10.10s    %4ld  /* %s */\n",status.tipostatus,status.dabstatus,status.status,status.desstatus);
            }
		}
	}                                    
	fclose(ficsal);
}

static int cmpcol(const void *elem1,const void *elem2)
{
	const columns **ptr1=elem1,**ptr2=elem2;
	return(strcmp((*ptr1)->column_name,(*ptr2)->column_name));
}

void imprimeh(int generah,int extension)
{
	int i,j,k,l;
	tables *ptr_table;
	columns *ptr_column;
	columns *arrcol[MAXCOLAPP];
	int ncol=0;
	FILE *ficsal;
	
	if ((ficsal=fopen(user.hficsal,"w"))==NULL) {
        final(("No puedo abrir fichero de salida: %s.",user.hficsal));
	}
	v10log(1,"Imprimiendo el fichero %s...\n",user.hficsal);
	fprintf(ficsal,"/* USUARIO: %s. */\n\n",user.username);
	fprintf(ficsal,"/* Includes: */\n");
	fprintf(ficsal,"#include \"%s\"\n\n",user.sthficsal);
	fprintf(ficsal,"/* Defines de las longitudes de los campos. */\n");
	for (i=0;i<user.ntables;i++) {
		ptr_table=user.table[i];
		for (j=0;j<ptr_table->ncolumns;j++) {
			ptr_column=ptr_table->column[j];
			for (k=0;k<i;k++) {
				for (l=0;l<user.table[k]->ncolumns;l++) {
					if (strcmp(user.table[k]->column[l]->column_name,ptr_column->column_name)==0) break;
				}
				if (l<user.table[k]->ncolumns) break;
			}
			if (k<i) continue;
			arrcol[ncol++]=ptr_column;		
		}
	}
	qsort(arrcol,ncol,sizeof(arrcol[0]),cmpcol);
	for (i=0;i<ncol;i++) {
		j=0;
		ptr_column=arrcol[i];
		if (ptr_column->longitud==0L) {
			warning(("No he podido calcular la longitud de %s tipo %s tabla %s",ptr_column->column_name,ptr_column->data_type,ptr_table->table_name));
		} else {
            if (extension) fprintf(ficsal,"#ifndef L%-30.30s\n#define L%-30.30s  %3ld /*",ptr_column->column_name,ptr_column->column_name,ptr_column->longitud);
			else fprintf(ficsal,"#define L%-30.30s  %3ld /*",ptr_column->column_name,ptr_column->longitud);
			for (k=0;k<user.ntables;k++) {
				for (l=0;l<user.table[k]->ncolumns;l++) {
					if (strcmp(user.table[k]->column[l]->column_name,ptr_column->column_name)==0) {
						if (j++!=0) fprintf(ficsal,",");
						fprintf(ficsal,"%s",user.table[k]->table_name);
					}
				}
			}
			if (extension) fprintf(ficsal,"*/\n#endif\n");
            else fprintf(ficsal,"*/\n");
            if (ptr_column->data_scale) {
                if (extension) fprintf(ficsal,"#ifndef LD%-30.30s\n#define LD%-30.30s %3ld /* Parte decimal */\n#endif\n",ptr_column->column_name,ptr_column->column_name,ptr_column->data_scale);
				else fprintf(ficsal,"#define LD%-30.30s %3ld /* Parte decimal */\n",ptr_column->column_name,ptr_column->data_scale);
		    }
        }
	}
    fprintf(ficsal,"\n");
    fprintf(ficsal,"/* Defines de los status. */\n");
    if (generah) {
		if (!vdselstatus) initcursoresstatus(extension);
		if (ejecutacursor(vdselstatus)) {
			cursordebug(vdselstatus);
        } else {
			while (fetchcursor(vdselstatus)==0) {
                if (extension) fprintf(ficsal,"#ifndef CST%s%-10.10s\n#define CST%s%-10.10s   \"%4ld\" /* %s */\n#endif\n",status.tipostatus,status.dabstatus,status.tipostatus,status.dabstatus,status.status,status.desstatus);
                else fprintf(ficsal,"#define CST%s%-10.10s   \"%4ld\" /* %s */\n",status.tipostatus,status.dabstatus,status.status,status.desstatus);
			}
        }
	}
    fclose(ficsal);
}

void imprimestr(void)
{
	int i;
	int j;
	int col;
	tables *ptr_table;
	columns *ptr_column;
	FILE *ficsal;
	char *min;
	char *may;
	long longitud;
	int ncampos;
	
    if ((ficsal=fopen(user.sficsal,"w"))==NULL) {
		final(("No puedo abrir fichero de salida: %s.",user.sficsal));
    }
    v10log(1,"Imprimiendo el fichero %s...\n",user.sficsal);
    fprintf(ficsal,"/* USUARIO: %s. */\n\n",user.username);
    fprintf(ficsal,"/* Estructuras de las tablas. */\n\n");
    for (i=0;i<user.ntables;i++) {
		longitud=0;
		ptr_table=user.table[i];
		fprintf(ficsal,"  /*  Tabla %s  */\n",ptr_table->table_name);
		fprintf(ficsal,"typedef struct {\n");
        ncampos=0;
        for (j=0;j<ptr_table->ncolumns;j++) {
            ncampos++;
            ptr_column=ptr_table->column[j];
            min=strdup(ptr_column->column_name);
            strmin(min);
            may=strdup(ptr_column->column_name);
            strmay(may);
            switch (ptr_column->tipo) {
                case TIPOCHAR:
                case TIPOVARCHAR2:
                    fprintf(ficsal,"                char %s[L%s];\n",min,may);
                    longitud+=ptr_column->longitud;
                    break;
                case TIPONUMBER: if (!ptr_column->data_scale) {
                    fprintf(ficsal,"                long %s;\n",min);
                    longitud+=4;
                    } else {
                                     fprintf(ficsal,"                double %s;\n",min);
                                     longitud+=8;
                        }
                    break;
                case TIPODATE: fprintf(ficsal,"                char %s[%d];\n",min,LTIPODATE);
                    longitud+=4;
                    break;
                case TIPOTIMESTAMP: fprintf(ficsal,"                char %s[%d];\n",min,LTIPOTIMESTAMP);
                    longitud+=4;
                    break;
                default: final(("Tipo %d no implementado.",ptr_column->tipo));
                    break;
                }
            free(min);
            free(may);
            }
		fprintf(ficsal,"               } %ss;\n",strmin(ptr_table->table_name));
		fprintf(ficsal,"    /* Son %d campos y ocupa %ld bytes. */\n\n",ncampos,longitud);
		fprintf(ficsal,"  /*  Defines y binds %s  */\n",ptr_table->table_name);
		fprintf(ficsal,"define_todo(TUCURSOR,");
		for (j=0;j<ptr_table->ncolumns;j++) {
			ptr_column=ptr_table->column[j];
			min=strdup(ptr_column->column_name);
			strmin(min);
			may=strdup(ptr_column->column_name);
			strmay(may);
			switch(ptr_column->tipo) {
			case TIPOCHAR:
			case TIPOVARCHAR2:
				fprintf(ficsal,"ESTRUC.%s,sizeof(ESTRUC.%s),V10CADENA,\n                     ",min,min);
				break;
			case TIPONUMBER: if (!ptr_column->data_scale) {
				fprintf(ficsal,"&ESTRUC.%s,sizeof(ESTRUC.%s),V10LONG,\n                     ",min,min);
							 } else {
								 fprintf(ficsal,"&ESTRUC.%s,sizeof(ESTRUC.%s),V10DOUBLE,\n                     ",min,min);
							 }
							 break;
			case TIPODATE: fprintf(ficsal,"ESTRUC.%s,sizeof(ESTRUC.%s),V10CADENA,\n                     ",min,min);
				break;
			case TIPOTIMESTAMP: fprintf(ficsal,"ESTRUC.%s,sizeof(ESTRUC.%s),V10CADENA,\n                     ",min,min);
				break;
			default: final(("Tipo %d no implementado.",ptr_column->tipo));
				break;
			}
			free(min);
			free(may);
		}
		fprintf(ficsal,"NULL);\n",strmin(ptr_table->table_name));
		fprintf(ficsal,"bind_todo(TUCURSOR,");
		for (j=0;j<ptr_table->ncolumns;j++) {
			
			ptr_column=ptr_table->column[j];
			min=strdup(ptr_column->column_name);
			strmin(min);
			may=strdup(ptr_column->column_name);
			strmay(may);
			switch(ptr_column->tipo) {
			case TIPOCHAR:
			case TIPOVARCHAR2:
				fprintf(ficsal,"\"%s\",ESTRUC.%s,sizeof(ESTRUC.%s),V10CADENA,\n                   ",may,min,min);
				break;
			case TIPONUMBER: if (!ptr_column->data_scale) {
				fprintf(ficsal,"\"%s\",&ESTRUC.%s,sizeof(ESTRUC.%s),V10LONG,\n                   ",may,min,min);
							 } else {
								 fprintf(ficsal,"\"%s\",&ESTRUC.%s,sizeof(ESTRUC.%s),V10DOUBLE,\n                   ",may,min,min);
							 }
							 break;
			case TIPODATE: fprintf(ficsal,"\"%s\",ESTRUC.%s,sizeof(ESTRUC.%s),V10CADENA,\n                   ",may,min,min);
				break;
			case TIPOTIMESTAMP: fprintf(ficsal,"\"%s\",ESTRUC.%s,sizeof(ESTRUC.%s),V10CADENA,\n                   ",may,min,min);
				break;
			default: final(("Tipo %d no implementado.",ptr_column->tipo));
				break;
			}
			free(min);
			free(may);
		}
		fprintf(ficsal,"NULL);\n",strmin(ptr_table->table_name));
		
		fprintf(ficsal,"\n");
		
		col=17;
		fprintf(ficsal,"INSERT INTO %s ( \n                ",strmay(ptr_table->table_name));
		for (j=0;j<ptr_table->ncolumns;j++) {
			
			ptr_column=ptr_table->column[j];
			min=strdup(ptr_column->column_name);
			strmin(min);
			may=strdup(ptr_column->column_name);
			strmay(may);
			col+=fprintf(ficsal,"%s",may);
			if (j<ptr_table->ncolumns-1) {
				fprintf(ficsal,",");
				col++;
			}
			if (col>65 && (j+1)<ptr_table->ncolumns) {
				fprintf(ficsal,"\n                ");
				col=17;
			}
			free(min);
			free(may);
		}
		col=17;
		fprintf(ficsal,"\n     ) VALUES (\n                ");
		for (j=0;j<ptr_table->ncolumns;j++) {
			
			ptr_column=ptr_table->column[j];
			min=strdup(ptr_column->column_name);
			strmin(min);
			may=strdup(ptr_column->column_name);
			strmay(may);
			col+=fprintf(ficsal,":%s",may);
			if (j<ptr_table->ncolumns-1) {
				fprintf(ficsal,",");
			}
			if (col>65 && (j+1)<ptr_table->ncolumns) {
				fprintf(ficsal,"\n                ");
				col=17;
			}
			free(min);
			free(may);
		}
		fprintf(ficsal,"\n     )\n",strmin(ptr_table->table_name));
		
		fprintf(ficsal,"\n");
		col=17;
		fprintf(ficsal,"SELECT ");
		for (j=0;j<ptr_table->ncolumns;j++) {
			
			ptr_column=ptr_table->column[j];
			min=strdup(ptr_column->column_name);
			strmin(min);
			may=strdup(ptr_column->column_name);
			strmay(may);
			col+=fprintf(ficsal,"%s",may);
			if (j<ptr_table->ncolumns-1) {
				fprintf(ficsal,",");
				col++;
			}
			if (col>65 && (j+1)<ptr_table->ncolumns) {
				fprintf(ficsal,"\n       ");
				col=17;
			}
			free(min);
			free(may);
		}
		fprintf(ficsal,"\n  FROM %s\n",strmay(ptr_table->table_name));
		fprintf(ficsal," WHERE\n");
		
		fprintf(ficsal,"\n");
		fprintf(ficsal,"UPDATE %s\n",strmay(ptr_table->table_name));
		for (j=0;j<ptr_table->ncolumns;j++) {
			
			ptr_column=ptr_table->column[j];
			min=strdup(ptr_column->column_name);
			strmin(min);
			may=strdup(ptr_column->column_name);
			strmay(may);
			if (!j) {
				fprintf(ficsal,"   SET %s=:%s",may,may);
			} else {
				fprintf(ficsal,"       %s=:%s",may,may);
			}
			if (j<ptr_table->ncolumns-1) {
				fprintf(ficsal,",\n");
			}
			free(min);
			free(may);
		}
		fprintf(ficsal,"\n WHERE\n\n");
    }
    fprintf(ficsal,"\n");
    fclose(ficsal);
}

void imprimesql(int generasql,int extension)
{
    FILE *ficsal;
    if ((ficsal=fopen(user.sqlficsal,"w"))==NULL) {
        final(("No puedo abrir fichero de salida: %s.",user.sqlficsal));
    }
    v10log(1,"Imprimiendo el fichero %s...\n",user.sqlficsal);
    fprintf(ficsal,"-- USUARIO: %s.\n\n",user.username);
    fprintf(ficsal,"-- Paquete Oracle con los estados. \n");
    if (generasql) {
        if (!vdselstatus) initcursoresstatus(extension);
        fprintf(ficsal,"CREATE OR REPLACE PACKAGE VDST IS\n\n");
        if (ejecutacursor(vdselstatus)) {
            cursordebug(vdselstatus);
        } else {
           /* while (fetchcursor(vdselstatus)==0) {
                fprintf(ficsal,"    %s%-10.10s CONSTANT NUMBER := %4ld;  --%s \n",status.tipostatus,status.dabstatus,status.status,status.desstatus);
            }*/
            
            fprintf(ficsal,"\n-- FUNCIONES PLSQL PARA OBTENER ESTADOS\n");      
            if (ejecutacursor(vdselstatus)==0) {
                while (fetchcursor(vdselstatus)==0) {
                    fprintf(ficsal,"    FUNCTION F%s%s RETURN NUMBER;\n",status.tipostatus,status.dabstatus);  
                   // fprintf(ficsal,"    PRAGMA RESTRICT_REFERENCES(F%s%s, WNDS, WNPS);\n",status.tipostatus,status.dabstatus);      
                }
            } 
            
            fprintf(ficsal,"\nEND;\n/\n");
            if (generasql) {
                if (!vdselstatus) initcursoresstatus(extension);
                fprintf(ficsal,"CREATE OR REPLACE PACKAGE BODY VDST AS\n\n");
                if (ejecutacursor(vdselstatus)) {
                    cursordebug(vdselstatus);
                } else {
                    while (fetchcursor(vdselstatus)==0) {
                        fprintf(ficsal," FUNCTION F%s%s RETURN NUMBER IS BEGIN RETURN(%ld); END;\n",status.tipostatus,status.dabstatus,status.status);
                    }
                }
            }
        }
    }
        
    fprintf(ficsal,"\nEND;\n/\n");
    fclose(ficsal);
 }

