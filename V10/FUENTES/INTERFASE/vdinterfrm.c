#include "vdinterfase.h"


static int tratabloqueinter(bloques *b);

static void asignaerrorinter(bloques *b,int error)
{
    char destino[MAXCADENA];
    sprintf(destino,ERRORINTER"='%ld'",error);
    asignavariables(b,destino);
}

static int ejecutatrigerinter(bloques *b,ftrigers *ft)
{
    int ret=0;
    if (ft) {
        ret=ft->fun(b,ft);
        if (ret) {
            if (ft->msg) v10log(LOGERROR,"Error ejecutando triger en bloque %s mensaje %s\n",b->fichero,ft->msg);
            asignaerrorinter(b,ret);
        }
    }
    return(ret);
}

static int ejecutatrigersinter(bloques *b,...)
{
	va_list arg;
	int ret=0;
	ftrigers *ft;
	va_start(arg,b);
	while ((ft=va_arg(arg,ftrigers *))!=NOPAR) {
		if (ft) {
			ret=ejecutatrigerinter(b,ft);
			if (ret) break;
		}
	}
	va_end(arg);
	return(ret);
}


static int trataregistrointer(bloques *b)
{
    int ret;
    unsigned nb;
	forms *f = FORM(b);
    ret=ejecutatrigersinter(b,b->fpostquery,b->fpreupdate,b->fpredelete,b->fpreinsert,b->fpreregistro,NOPAR);
    if (ret) return(ret);
    for (nb=0;nb<f->nbloques;nb++) {
        bloques *bh=f->b[nb];
		if (bh->padre == b) {
			ret = tratabloqueinter(bh);
            asignaerrorinter(b,ret);
            if (ret) return(ret);
        }
    }
    ret=ejecutatrigersinter(b,b->fpostupdate,b->fpostdelete,b->fpostinsert,b->fpostregistro,NOPAR);
    if (ret) return(ret);
    return(0);
}

static int lltratabloqueinter(bloques *b)
{
    int ret;
    ret=ejecutatrigerinter(b,b->fprequery);
    if (ret) return(ret);
    memset(b->buffer,0,b->tamano*2);
    if ((ret=genselect(b))!=0) {
        b->aquery=0;
        return(ret);
    }
    ret=ejefetchcursor(b->select);
    conviertefromdb(b,b->select);
    while (ret==0) {
        ret=trataregistrointer(b);
        if (ret) return(ret);
        memset(b->buffer,0,b->tamano*2);
        ret=fetchcursor(b->select);
        conviertefromdb(b,b->select);
	}
	if (ret!=NOFOUND) {
		v10log(LOGERROR,"En cursor %s error %d\n",b->select->nombre,ret);
		return(ret);
	}
    return(0);
}

static int tratabloqueinter(bloques *b)
{
    int ret;
    ret=ejecutatrigerinter(b,b->fprebloque);
	if (ret) return(ret);
    ret=lltratabloqueinter(b);
    if (ret) {
        ejecutatrigerinter(b,b->fprerollback);
        asignaerrorinter(b,ret);
    } else {
        ejecutatrigerinter(b,b->fprecommit);
    }
    ret=ejecutatrigerinter(b,b->fpostbloque);
    if (ret) return(ret);
    return(0);
}

int trataforminter(forms *f)
{    
    int ret;
    unsigned nb;
    v10log(LOGNORMAL,"Ejecutando interfase %s\n",f->nombre);
    if (f->preform) {
        ret=f->preform->fun(f->b[0],f->preform);
        if (ret) return(ret);
    }
    for (nb=0;nb<f->nbloques;nb++) {
        bloques *b=f->b[nb];
        if (b->padre==NULL) {
            tratabloqueinter(b);
        }
    }
    if (f->postform) {
        ret=f->postform->fun(f->b[0],f->postform);
        if (ret) return(ret);
    }
    return(0);
}