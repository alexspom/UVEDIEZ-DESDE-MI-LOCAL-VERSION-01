/*
* M�dulo : V10FORGENERA.C
* Objeto:  Generacion de los diversos sql de un forms
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10form.h"

void gensolowhere(bloques *b, char *ptro, int haywhere)
{
    int i;
    int hay = 0;
    char ntabla[MAXNOMBREV10];
    for (i = 1; i<b->ncamp; i++) {
        fcampos *c = b->c + i;
        if (b->soloquery && ((!es_blanco(b->nombre) && !c->nopref) || c->prefijo)) {
            if (c->prefijo) strcpy(ntabla, c->prefijo);
            else              strcpy(ntabla, b->nombre);
            strcat(ntabla, ".");
        } else  *ntabla = 0;
        if (c->tabla == 0 && c->where == NULL) continue;
        if (esnulo(direcuquerycampo(b, i), c->tipo) && !c->virtual) continue;
        if (hay == 0) {
            hay = 1;
            if (!haywhere) sprintf(ptro, " WHERE ");
            else        sprintf(ptro, " AND ");
            ptro += strlen(ptro);
        } else {
            sprintf(ptro, " AND ");
            ptro += strlen(ptro);
        }
        if (c->where) {
            sprintf(ptro, "(%s)", b->c[i].where);
        } else { //OJO UNICODE
            if (c->tipo == V10CADENA && (strchr((char *)direcuquerycampo(b, i), '%') || strchr((char *)direcuquerycampo(b, i), '_'))) {
                if (*(char *)direcuquerycampo(b, i) == '@')
                    if (c->capitaliza) sprintf(ptro, "%s%s NOT LIKE :%s", ntabla, c->nombre, c->nombre);
                    else sprintf(ptro, "UPPER(%s%s) NOT LIKE UPPER(:%s)", ntabla, c->nombre, c->nombre);
                else {
                    if (c->capitaliza == 0) sprintf(ptro, "UPPER(%s%s) LIKE UPPER(:%s)", ntabla, c->nombre, c->nombre);
                    else sprintf(ptro, "%s%s LIKE :%s", ntabla, c->nombre, c->nombre);
                }
            } else {
                if (c->tipo == V10CADENA && c->format == FORMATODATE) {
                    sprintf(ptro, "%s%s=VDFORM.CHAR2DATE(:%s)", ntabla, c->nombre, c->nombre);
                } else {
                    if (c->tipo == V10CADENA && c->format == FORMATORAW) {
                        sprintf(ptro, "%s%s=HEXTORAW(:%s)", ntabla, c->nombre, c->nombre);
                    } else {
                        if (c->tipo == V10CADENA && c->capitaliza == 0)	sprintf(ptro, "UPPER(%s%s)=UPPER(:%s)", ntabla, c->nombre, c->nombre);
                        else	sprintf(ptro, "%s%s=:%s", ntabla, c->nombre, c->nombre);
                    }
                }
            }
        }
        ptro += strlen(ptro);
    }
    if ((hay || haywhere) && b->where && strnicmp(b->where, "ORDER ", 6) && strnicmp(b->where, "GROUP ", 6)) {
        sprintf(ptro, " AND");
        ptro += strlen(ptro);
    }
    if (b->where) {
        if (!hay && !haywhere && strnicmp(b->where, "ORDER ", 6) && strnicmp(b->where, "GROUP ", 6)) {
            sprintf(ptro, " WHERE");
            ptro += strlen(ptro);
        }
        sprintf(ptro, " %s", b->where);
        ptro += strlen(ptro);
    }
}

void genwhere(bloques *b, char *ptro, int haywhere)
{
    gensolowhere(b, ptro, haywhere);
    ptro += strlen(ptro);
    if (b->groupby) {
        sprintf(ptro, " GROUP BY %s", b->groupby);
        ptro += strlen(ptro);
    }
    if (b->having) {
        sprintf(ptro, " HAVING %s", b->having);
        ptro += strlen(ptro);
    }
    if (b->orderby) {
        sprintf(ptro, " ORDER BY %s", b->orderby);
    }
}

int genselect(bloques *b)
{
    char *ret,*ptro;
    int i,err=0;
    int haywhere=0;
    ptro=ret=calloc(1,MAXSQL);
    if (!b->soloquery) {
        int ncamp=0; 
        if (b->norowid) sprintf(ptro,"SELECT ");
        else         sprintf(ptro,"SELECT ROWID MIROWID");
        ptro+=strlen(ptro);
        for (i=1;i<b->ncamp;i++) { //OJO UNICODE
            fcampos *c=b->c+i;
            if (c->tabla==0 || c->virtual==1) continue;
            if (b->norowid==0 || ncamp!=0) *ptro++=',';
            if (c->tipo==V10CADENA && (c->format & FORMATODATE)) {
                sprintf(ptro,"VDFORM.DATE2CHAR(%s) %s",c->nombre,c->nombre);
            } else {
                if (c->tipo==V10CADENA && (c->format & FORMATORAW)) {
                    sprintf(ptro,"RAWTOHEX(%s) %s",c->nombre,c->nombre);
                } else {
                    sprintf(ptro,c->nombre);
                }
            }
            ptro+=strlen(ptro);
            ncamp++;
        }
    }
    if (b->extraselect) {
        if (!b->soloquery) *ptro++=',';
        strcpy(ptro,b->extraselect);
        ptro+=strlen(ptro);
    }
    if (!b->soloquery) {
        sprintf(ptro," FROM %s",b->nombre);
        ptro+=strlen(ptro);
    }
    memcpy(b->bufuquery,b->buffer,(unsigned)b->tamano);
    if (strstr(ret," WHERE ")) haywhere=1;
    if (!b->noquery) genwhere(b,ptro,haywhere);

	//v10log(LOGNORMAL, "Entro en ABREFICHERO %s\n", b->nombre);
    abreficheroaux(b);
	//v10log(LOGNORMAL, "Salgo de ABREFICHERO %s\n", b->nombre);
    pidevwhere(ret);
    sustituyedefines(ret);
    if (b->select) {
        if (strcmp(ret,b->select->sql)) {
            liberacursor(b->select);
            b->select=NULL;
        }
    }
    if (b->select==NULL) {
        char nombre[MAXNOMBREV10];
        sprintf(nombre,"FORM%s",b->fichero);
        b->select=bindquery(b,ret,nombre);
        if (b->select!=NULL) {
            if (describebloque(b,b->select)) {
                mensajefcm(10,ultimoerrorbloque);
                liberacursor(b->select);
                b->select=NULL;
                err=-1;
            } else convierte2db(b,b->select);
        } else err=-1;
    } else convierte2db(b,b->select);
    free(ret);
    return(err);
}

int gencount(bloques *b)
{
    char *ret,*ptro;
    int err=0;
    if (b->select==NULL) genselect(b);
    if (b->select==NULL) return(-1);
    ptro=ret=calloc(1,MAXSQL);
    sprintf(ptro,"SELECT COUNT(*) FROM (%s) CUENTA",b->select->sql);
    if ((ptro=strstr(ret," ORDER BY"))!=NULL) {
        *ptro++=')';
        *ptro=0;
    }
    if (b->count) {
        if (strcmp(ret,b->count->sql)) {
            liberacursor(b->count);
            b->count=NULL;
        }
    }
    if (b->count==NULL) {
        b->count=bindquery(b,ret,"FORMCOUNT");
        if (b->count!=NULL) {
            definetodo(b->count,&b->total,sizeof(b->total),V10LONG,NULL);
            convierte2db(b,b->count);
        } else err=1;
    }
    free(ret);
    return(err);
}

void geninsert(bloques *b)
{
    char *ret,*ptro;
    int i,ct=0;
    ptro=ret=calloc(1,MAXSQL);
    sprintf(ptro,"INSERT INTO %s (",b->nombre);
    ptro+=strlen(ptro);
    for (i=1;i<b->ncamp;i++) {
        fcampos *c=b->c+i;
        if (c->tabla==0) continue;
        if (ct>0) *ptro++=',';
        ct++;
        sprintf(ptro,c->nombre);
        ptro+=strlen(ptro);
    }
    sprintf(ptro,") VALUES(");
    ptro+=strlen(ptro);
    ct=0;
    for (i=1;i<b->ncamp;i++) {
        fcampos *c=b->c+i;
        if (c->tabla==0) continue;
        if (ct>0) *ptro++=',';
        ct++;
        if (c->tipo==V10CADENA && (c->format & FORMATODATE)) {
            sprintf(ptro,"VDFORM.CHAR2DATE(:%s)",c->nombre);
        } else {
            if (c->tipo==V10CADENA && (c->format & FORMATORAW)) {
                sprintf(ptro,"HEXTORAW(:%s)",c->nombre);
            } else {
                sprintf(ptro,":%s",c->nombre);
            }
        }
        ptro+=strlen(ptro);
    }
    sprintf(ptro,") RETURNING ROWID");
	if (DRIVERDB->insertinto) {
		sprintf(ptro+strlen(ptro)," INTO :MIROWID");
	} else {
		sprintf(ptro+strlen(ptro)," MIROWID");		
	}
    b->insert=bindbloque(b,ret,"FORMINSERT");
	describebloque(b, b->insert);
    free(ret);
}

int genupdate(bloques *b)
{
    char *ret,*ptro;
    int i,ct=0;
    ptro=ret=calloc(1,MAXSQL);
    sprintf(ptro,"UPDATE %s SET ",b->nombre);
    ptro+=strlen(ptro);
    for (i=1;i<b->ncamp;i++) {
        fcampos *c=b->c+i;
        if (c->tabla==0) continue;
        if (c->noupdate) continue;
        if (comparacampo(b,c,direcantcampo(b,i))==0) continue;
        if (ct>0) *ptro++=',';
        ct++;
        if (c->tipo==V10CADENA && (c->format & FORMATODATE)) {
            sprintf(ptro,"%s=VDFORM.CHAR2DATE(:%s)",c->nombre,c->nombre);
        } else {
            if (c->tipo==V10CADENA && (c->format & FORMATORAW)) {
                sprintf(ptro,"%s=HEXTORAW(:%s)",c->nombre,c->nombre);
            } else {
                sprintf(ptro,"%s=:%s",c->nombre,c->nombre);
            }
        }
        ptro+=strlen(ptro);
    }
    if (ct==0) {
        b->update=NULL;
        return(0);
    }
    sprintf(ptro," WHERE ROWID=:MIROWID RETURNING ");
    ptro+=strlen(ptro);
    ct=0;
    for (i=1;i<b->ncamp;i++) {
        fcampos *c=b->c+i;
        if (c->tabla==0) continue;
        if (ct>0) *ptro++=',';
        ct++;
        sprintf(ptro,"%s",c->nombre);
        ptro+=strlen(ptro);
    }
    ct=0;
	if (DRIVERDB->insertinto) sprintf(ptro," INTO ");
    else sprintf(ptro, " ");
    ptro+=strlen(ptro);
    for (i=1;i<b->ncamp;i++) {
        fcampos *c=b->c+i;
        if (c->tabla==0) continue;
        if (ct>0) *ptro++=',';
        ct++;
        if (DRIVERDB->insertinto) {
        sprintf(ptro,":%s",c->nombre);
        } else {
            sprintf(ptro, "%s", c->nombre);
        }
        ptro+=strlen(ptro);
    }
    if (ct==0) return(ct);
    b->update=bindbloque(b,ret,"FORMUPDATE");
	describebloque(b, b->update);
    free(ret);
    return(ct);
}

void gendelete(bloques *b)
{
    char *ret;
    ret=calloc(1,MAXSQL);
    sprintf(ret,"DELETE FROM %s WHERE ROWID=:MIROWID",b->nombre);
    b->delete=bindbloque(b,ret,"FORMDELETE");
    free(ret);
}

void genlock(bloques *b)
{
    char *ret,*ptro;
    int i;
    ptro=ret=calloc(1,MAXSQL);
    sprintf(ptro,"SELECT ROWID MIROWID");
    ptro+=strlen(ptro);
    for (i=1;i<b->ncamp;i++) {
        fcampos *c=b->c+i;
        if (c->tabla==0 || c->virtual==1) continue;
        *ptro++=',';
        if (c->tipo==V10CADENA && (c->format & FORMATODATE)) {
            sprintf(ptro,"VDFORM.DATE2CHAR(%s) %s",c->nombre,c->nombre);
        } else {
            if (c->tipo==V10CADENA && (c->format & FORMATORAW)) {
                sprintf(ptro,"RAWTOHEX(%s) %s",c->nombre,c->nombre);
            } else {
                sprintf(ptro,c->nombre);
            }
        }
        ptro+=strlen(ptro);
    }
    sprintf(ptro," FROM %s WHERE ROWID=:MIROWID FOR UPDATE NOWAIT",b->nombre);
    b->lock=bindbloque(b,ret,"FORMLOCK");
    if (b->lock!=NULL) {
        if (describebloque(b,b->lock)) {
            liberacursor(b->lock);
            b->lock=NULL;
        }
    }
    free(ret);
}

void genreload(bloques *b)
{
    char *ret,*ptro;
    int i;
    ptro=ret=calloc(1,MAXSQL);
    sprintf(ptro,"SELECT ROWID MIROWID");
    ptro+=strlen(ptro);
    for (i=1;i<b->ncamp;i++) {
        fcampos *c=b->c+i;
        if (c->tabla==0 || c->virtual==1) continue;
        *ptro++=',';
        if (c->tipo==V10CADENA && (c->format & FORMATODATE)) {
            sprintf(ptro,"VDFORM.DATE2CHAR(%s) %s",c->nombre,c->nombre);
        } else {
            if (c->tipo==V10CADENA && (c->format & FORMATORAW)) {
                sprintf(ptro,"RAWTOHEX(%s) %s",c->nombre,c->nombre);
            } else {
                sprintf(ptro,c->nombre);
            }
        }
        ptro+=strlen(ptro);
    }
    sprintf(ptro," FROM %s WHERE ROWID=:MIROWID",b->nombre);
    b->reload=bindbloque(b,ret,"FORMRELOAD");
    if (describebloque(b,b->reload)) {
        liberacursor(b->reload);
        b->reload=NULL;
    }
    free(ret);
}
