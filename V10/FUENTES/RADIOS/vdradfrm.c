/*******************************************************************************
* Módulo : vdradfrm.c                                                          *
* Función: Gestion de forms para radios                                        *
*                                                                              *
*                                                                              *
* Autor  : Eduardo Alsina                                                      *
* Revisado por:                                                                *
* Fecha  : 01-10-2007                                                          *
********************************************************************************
* Histórico de cambios
* ====================
*******************************************************************************/

#include "vdradio.h"

static int muestramsg=1;
#define CUPDARECURSO "BEGIN VDUSER.SETRECURSO(:CODRECURSO); END;"
#define CSELRECURSO "SELECT VDUSER.GETRECURSO FROM DUAL"

static v10cursors *v10updarecurso;
static v10cursors *v10selrecurso;

char codrecurso[LCODRECURSO];

char *damerecurso(void)
{
    ejefetchcursor(v10selrecurso);
    return(codrecurso);
}

static void init_cursores(void)
{
    v10updarecurso=abrecursordebug(CUPDARECURSO,0);
    bindtodo(v10updarecurso,"CODRECURSO",codrecurso,sizeof(codrecurso),V10CADENA,NULL);
    v10selrecurso = abrecursordebug(CSELRECURSO, 0);
    definetodo(v10selrecurso, codrecurso, sizeof(codrecurso), V10CADENA, NULL);
    damehostname = damerecurso;
}

void ponrecurso(char *micodrecurso)
{
    strcpy(codrecurso,micodrecurso);
    if (v10updarecurso==NULL) init_cursores();
    ejecutacursor(v10updarecurso);
}

int haycampoenter(conexiones *c)
{
    bloques *b;
    v10inputs *aux;
    if (c->f==NULL) return(0);
    b=c->f->b[c->f->act];
    for (aux=b->vi.prim; aux<=b->vi.ult; aux++) if (aux->enter!=0 && aux->invisible==0) return(1);
    return(0);
}

#define LINEASTERM 14
static void formatearadio(char *cadena,char *destino)
{
    int linea=0,i;
    char *aux;
    if (*cadena=='\n') {
        strcpy(destino,cadena);
        return;
    }
    for (aux=cadena,linea=0;(aux=strchr(aux,'\n'));aux++,linea++);
    if (linea<LINEASTERM-8) {
        for (i=0;i<(LINEASTERM-linea)/2;i++) *destino++='\n';
    } else if (linea<LINEASTERM-1) *destino++='\n';
    strcpy(destino,cadena);
}

void vmensajeradioc(conexiones *c,int suena,char *texto,va_list arg)
{
    char plinea[MAXCADENA];
    if (dr.mensaje==NULL) return;
    sprintf(plinea,"%-*.*s %s\\n%s",LCODRECURSO-1,LCODRECURSO-1,c->rec.codrecurso,c->op.codope,texto);
    dr.mensaje(c,suena,plinea,arg);
    MODIFRADIO++;
}

void mensajeradioc(conexiones *c,int suena,char *texto,...)
{
    va_list arg;
    va_start(arg,texto);
    vmensajeradioc(c,suena,texto,arg);
    va_end(arg);
}

static void mensajeradio(forms *f,char *texto,...)
{
    conexiones *c=numcon(f->extraform);
    va_list arg;
    char destino[MAXCADENA];
    vdrecursos *rec=&c->rec;
    if (rec->status==STRECMENSAJE) return;
    if (muestramsg==0) return; 
    rec->status=STRECMENSAJE;
    va_start(arg,texto);
    formatearadio(texto,destino);
    vmensajeradioc(c,CSUENA,destino,arg);
    va_end(arg);
}

int ejecutatrigerradionombre(conexiones *c,bloques *b,ftrigers *ft,char *nombre,int tipo,fcampos *campo,int mostrar)
{
    int ret;
    forms *f=b->form;
    int antmuestramsg=muestramsg;
    if (f->nivel!=NIVEL_BLOQUE) return(0);
    if (ft) {
        muestramsg=mostrar;
        ret = ejecutaftriger(b, tipo, ft, campo);
        if (campo) {
            v10log(LOGNORMAL, "Ejecutando triger %s en bloque %s campo %s ret %d\n", nombre, b->fichero, campo->nombre,ret);
        } else {
            v10log(LOGNORMAL, "Ejecutando triger %s en bloque %s ret %d\n", nombre, b->fichero, ret);
        }
        muestramsg=antmuestramsg;
        if (ret) {
            if (mostrar) {
               rollback(); 
               c->rec.status=STRECMENSAJE;
               RECactualizastatus(&c->rec,NOVERIFICA);
               commit();
            }
            return(ret);
        }
    }
    return(0);
}


static void borraindicadores(bloques *b)
{
    int nc;
    for (nc=0;nc<b->ncamp;nc++) {
        fcampos *c=b->c+nc;
        *indicadorcampo(b,c,CINDDEC)=-1;
        *indicadorcampo(b,c,CINDFORMATO)=-1;
        *indicadorcampo(b,c,CINDLPAN)=-1;
        *indicadorcampo(b,c,CINDENTER)=-1;
        *indicadorcampo(b,c,CINDINVISIBLE)=-1;
        *indicadorcampo(b,c,CINDNOUPDATE)=-1;
        *indicadorcampo(b,c,CINDCOLOR)=-1;
        *indicadorcampo(b,c,CINDAUTOENTER)=-1;
		if (c->v) {
			if (c->v->autoenter==1) 
				c->v->autoenter=0;
		}
    }
}

#define PONVALORIND(b,c,var,ind) (var=(*indicadorcampo(b,c,ind)==-1?var:*indicadorcampo(b,c,ind)))
void ponindicadoresbloque(bloques *b)
{
    int nc;
    for (nc=0;nc<b->ncamp;nc++) {
        fcampos *c=b->c+nc;
        PONVALORIND(b,c,c->dec,CINDDEC);
        PONVALORIND(b,c,c->format,CINDFORMATO);
        PONVALORIND(b,c,c->lvar,CINDLPAN);
        PONVALORIND(b,c,c->enter,CINDENTER);
        PONVALORIND(b,c,c->noinput,CINDNOINPUT);
        PONVALORIND(b,c,c->invisible,CINDINVISIBLE);
        PONVALORIND(b,c,c->noupdate,CINDNOUPDATE);
        PONVALORIND(b,c,c->autoenter,CINDAUTOENTER);
        if (c->v) {
            c->v->enter=c->enter;
            if (c->invisible || c->noinput) c->v->enter=0;
			if (c->autoenter) 
				c->v->autoenter=c->autoenter;//rik
            c->v->dec=c->dec;
        }
    }
}

static int llmandabloqueradio(conexiones *c)
{
    forms *f=c->f;
    bloques *b=f->b[f->act];
    f->nivel=NIVEL_BLOQUE;  
    borraindicadores(b);           
    if (ejecutatrigerradio(c,b,b->fprequery,PPREQUERY,NULL,1)) return(-1);
    if (ejecutatrigerradio(c,b,b->fpreupdate,PPREUPDATE,NULL,1)) return(-1);
    if (ejecutatrigerradio(c,b,b->fpreinsert,PPREINSERT,NULL,1)) return(-1);
    if (ejecutatrigerradio(c,b,b->fpredelete,PPREDELETE,NULL,1)) return(-1);
    if (f->act==LOADFRM) {
       tratafrm(c);
       return(0);
    }
    if (f->nivel!=NIVEL_BLOQUE) return(-1);
    if (f->act<0) return(-1);
    ponindicadoresbloque(b);
    dr.pasaformaterm(c,CSUENA);
    MODIFRADIO++;
    return(0);
}

int mandabloqueradio(conexiones *c)
{
    int ret;
    forms *f=c->f;
    do {
        ret=llmandabloqueradio(c);
    } while (f->nivel!=NIVEL_BLOQUE && f->act>=0);
    return(ret);
}

static int llejecutaradfrm(conexiones *c,int restaura)
{
    forms *f=c->f;
    v10log(LOGNORMAL,"%s","llejecutaradfrm - Inicio ejecución trigers\n");
    if (restaura==0) {
        if (ejecutatrigerradio(c,f->b[0],f->preform,PPREFORM,NULL,1)) return(-1);
        if (ejecutatrigerradio(c,f->b[0],f->precommit,PPRECOMMIT,NULL,1)) return(-1);
        if (ejecutatrigerradio(c,f->b[0],f->prerollback,PPREROLLBACK,NULL,1)) return(-1);
    }
    f->nivel=NIVEL_BLOQUE;
    if (ejecutatrigerradio(c,f->b[0],f->postform,PPOSTFORM,NULL,1)) return(-1);
    if (ejecutatrigerradio(c,f->b[0],f->postcommit,PPOSTCOMMIT,NULL,1)) return(-1);
    if (ejecutatrigerradio(c,f->b[0],f->postrollback,PPOSTROLLBACK,NULL,1)) return(-1);
    rollback(); 
    c->rec.status=STRECCONFORM;
    RECactualizastatus(&c->rec,NOVERIFICA);
    commit();
	mandabloqueradio(c);
	if (f->act < 0) {
		if (c->f) liberaform(c->f);
		c->f = NULL;
		strcpy(c->rec.npantalla, "");
		strcpy(c->rec.codperfil, "");
		RECactualizanpantalla(&c->rec, NOVERIFICA);
		liberaterminal(c);
		commit();
		gestionaterminal(1, c);
	}
    v10log(LOGNORMAL,"%s","llejecutaradfrm - Fin ejecución trigers\n");
    return(0);
}

static int llcargaradfrm(conexiones *c,int restaura)
{
    forms *f;
    char cadena[MAXCADENA];
    int ret;
    if (*c->rec.npantalla==0) return(-1);
    v10log(LOGNORMAL,"llcargaradfrm - Cargando pantalla %s\n",c->rec.npantalla);
    f=leeformtelnet(c->rec.npantalla,"");
    if (f == NULL) return(-1);
    f->extraform=c->rec.codrecurso;
    c->f=f;
    f->mensaje=(void *)mensajeradio;
    sprintf(cadena,"NOMBREFORM='%s' CODRECURSO='%s' CODOPE=%s",
        c->rec.npantalla,c->rec.codrecurso,c->op.codope); //(3)
    asignavariablesext(f->b[0],cadena,0);
    f->nivel=NIVEL_BLOQUE;
	loginterminal(c);
	commit();
    ret=llejecutaradfrm(c,restaura);
    v10log(LOGNORMAL,"llcargaradfrm - Fin carga pantalla %s\n",c->rec.npantalla);
    if (ret) return(ret);
    return(0);
}

static int ejecutapostchangecampo(bloques *b,fcampos *c,int mostrar)
{
    int error;
    conexiones *con=numcon(b->form->extraform);
    if (c->change) {
        *FERROR(b,c)=ejecutatrigerradio(con,b,c->change,PPOSTCHANGE,c,mostrar);
        if (*FERROR(b,c)) {
            error=*FERROR(b,c);
            posicionadialog(&b->vi,direccampoptr(b,c));
            return(error);
        }
    }
    return(0);
}

static int ejecutapostchangerad(bloques *b)
{
    int nc,error=0;
    for (nc=0;nc<b->ncamp;nc++) {
        fcampos *c=b->c+nc;
        error=ejecutapostchangecampo(b,c,1);
        if (error) break;
    }
    return(error);
}

int cargaradfrm(char *nombre,conexiones *c,int restaura,int salva)
{
    int ret;
    strcpy(c->rec.npantalla,nombre);
    if (salva) {
        RECactualizanpantalla(&c->rec,NOVERIFICA);
        commit();
    }
    ret=llcargaradfrm(c,restaura);
    rollback();
    if (ret) {
        if (c->f) {
            liberaform(c->f);
            c->f=NULL;
            strcpy(c->rec.npantalla,"");
        }
        liberaterminal(c);
    }
    return(ret);
}

void empiezainputcampo(conexiones *c)
{
    forms *f=c->f;
    bloques *b;
    v10inputs *v;
    fcampos *camp;
    int lon;
	if (f == NULL) return;
	if (f->act < 0) return;
	b = f->b[f->act];
	v = b->vi.act;
	camp = v->trigerdatos;
    if (v->enter==0 || camp->noupdate==1 || camp->invisible) return;
    camp->nscan=0;
    input2a(b->vi.act,c->buffer,1);
    c->ptr=c->buffer;
    lon=v->lpan;
    f->cinput=camp;
    dr.presentacampo(c,1,lon,b->vi.act->password);
}

int terminainputcampo(conexiones *c,int mostrar,int post)
{
    int lon;
    void *copia;
    int ret=0;
    bloques *b=c->f->b[c->f->act];
    v10inputs *v=b->vi.act;
    fcampos *camp=v->trigerdatos;
    if (v->enter==0 || camp->noupdate==1 || camp->invisible) return(0);
    lon=v->lpan;
    c->buffer[camp->lvar]=0;
    c->ptr=c->buffer;
    trim(c->buffer);
    copia=salvacampo(b,camp);
    a2input(b->vi.act,c->buffer);
    input2a(b->vi.act,c->buffer,0);
    if (comparacampo(b,camp,copia)) {
        v10log(LOGNORMAL,"me devuelve campo %s valor %s scaneado %ld\n",camp->nombre,b->vi.act->password?"******":c->buffer,*(int *)FSCAN(b,camp));
    }
    free(copia);
    if (post) ret=ejecutapostchangecampo(b,camp,mostrar);
    if (FORM(b)->nivel==NIVEL_BLOQUE && FORM(b)->act>=0 && (ret==0 || mostrar==0)) {
       dr.presentacampo(c,0,lon,b->vi.act->password);
    }
    memset(c->buffer,0,sizeof(c->buffer));
    return(ret);
}

int siguientecampo(conexiones *c)
{
    forms *f=c->f;
    bloques *b;
    v10inputs *vprim;
    int ret;
    fcampos *camp;
    if (f->act<0) return(-1);
    b=c->f->b[c->f->act];
    vprim=b->vi.act;
    ret=terminainputcampo(c,1,1);
/*    if (FORM(b)->nivel!=NIVEL_BLOQUE || FORM(b)->act<0) {
        encolateclaconexion(c,cr);
        return(ret);
    }*/
    if (ret) return(ret);
    do {
        b->vi.act++;
        if (b->vi.act>b->vi.ult) b->vi.act=b->vi.prim;
        if (vprim==b->vi.act) break;
        camp=b->vi.act->trigerdatos;
    } while (b->vi.act->enter==0 || camp->noupdate==1 || camp->invisible);
    empiezainputcampo(c);
    return(0);
}

int anteriorcampo(conexiones *c)
{
    bloques *b=c->f->b[c->f->act];
    int ret;
    fcampos *camp;
    v10inputs *vprim=b->vi.act;
    ret=terminainputcampo(c,0,1);
    do {
        b->vi.act--;
        if (b->vi.act<b->vi.prim) b->vi.act=b->vi.ult;
        if (vprim==b->vi.act) break;
        camp=b->vi.act->trigerdatos;
    } while (b->vi.act->enter==0 || camp->noupdate==1 || camp->invisible);
    if (FORM(b)->nivel!=NIVEL_BLOQUE || FORM(b)->act<0) return(ret);
    empiezainputcampo(c);
    return(0);
}

static int teclacamporad(bloques *b,fcampos *c,int ret)
{
    int nt;
    for (nt=0;nt<c->nteclas;nt++) {
        if (c->teclas[nt].t==ret) {
            if (c->teclas[nt].trig->fun) c->teclas[nt].trig->fun(b,c->teclas[nt].trig);
            ret=0;
            return(ret);
        }
    }
    return(ret);
}

static int teclabloquerad(bloques *b,int ret)
{
    int nt;
    for (nt=0;nt<b->nteclas;nt++) {
        if (b->teclas[nt].t==ret) {
            if (b->teclas[nt].trig->fun) b->teclas[nt].trig->fun(b,b->teclas[nt].trig);
            ret=0;
            return(ret);
        }
    }
    return(ret);
}

static int tecladriver(conexiones *c,int ret)
{
    int nt;
    for (nt=0;nt<dr.nteclas;nt++) {
        if (dr.tec[nt].t==ret) {
			if (dr.tec[nt].funcion) {
				v10log(LOGNORMAL,"Tecla especial %d\n",ret);
				dr.tec[nt].funcion(c);
			}
            ret=0;
            return(ret);
        }
    }
    return(ret);
}

int tratafuncion(conexiones *c,int ret)
{
    bloques *b;
    v10inputs *v;
    fcampos *camp;
    v10log(LOGNORMAL,"recibida funcion %d\n",ret-F(1)+1);
    ret=tecladriver(c,ret);
    if (ret==0) return(0);
	terminainputcampo(c,1,0);
    if (c->f) {
        b=c->f->b[c->f->act];
        v=b->vi.act;
        camp=v->trigerdatos;
        ret=teclacamporad(b,camp,ret);
        if (ret) ret=teclabloquerad(b,ret);
    }
	empiezainputcampo(c);
    return(0);
}

int tratateclaconexion(conexiones *c,int ret)
{
    bloques *b=c->f->b[c->f->act];
    v10inputs *v=b->vi.act;
    fcampos *campo=b->vi.act->trigerdatos;
    int *donde;
    if (haycampoenter(c)==0) return(0);
    if (c->ptr-c->buffer>=b->vi.act->lpan) {
        siguientecampo(c);
        return(0);
    }
    if (esv10tiponum(campo->tipo)|| (campo->tipo==V10CADENA && (campo->format & FORMATONUM))) {
        if ((ret<'0' || ret>'9') && ret!=',' && ret!='.' && ret!=' ') return(0);
        if (c->ptr==c->buffer) {
            strfill(c->ptr,' ',v->lvar);
            dr.presentacampo(c,2,v->lpan,v->password);
        }
    } else if (campo->capitaliza & FORMATOUPPER) ret=pasacarmay(ret);
    donde=FSCAN(b,campo);
    *donde=c->scanning;
    *c->ptr++=(char)ret;
    return(1);
}

static int lltratafrm(conexiones *c)
{
    forms *f=c->f;
    bloques *b;
    if (f==NULL) return(-1);
    if (f->act>=0) {
        b=f->b[f->act];
        f->nivel=NIVEL_BLOQUE; 
        if (dr.pasatermaform(c)) return(-1);             
        if (ejecutapostchangerad(b)) return(-1);
        if (ejecutatrigerradio(c,b,b->fpostquery,PPOSTQUERY,NULL,1)) return(-1);
        if (ejecutatrigerradio(c,b,b->fpostupdate,PPOSTUPDATE,NULL,1)) return(-1);
        if (ejecutatrigerradio(c,b,b->fpostinsert,PPOSTINSERT,NULL,1)) return(-1);
        if (ejecutatrigerradio(c,b,b->fpostdelete,PPOSTDELETE,NULL,1)) return(-1);
    }
    rollback();
    if (f->act>=0) {
        mandabloqueradio(c);
    }
    if (f->act<0) {
        int ret=-1;
        if (f->act==REINITFRM) {
            f->act=0;
            f->nivel=NIVEL_BLOQUE;
            ret=llejecutaradfrm(c,0);
        } else if (f->act==LOADFRM){
            f->act=0;
            if (*c->rec.npantalla){
                liberaform(c->f);
                f=c->f=NULL;
				if (c->pideusr!=OPVERIFICADO) {
					ret=cargaradfrm(c->rec.npantalla,c,0,1);
                    if (!ret) f=c->f;
				} else ret=0;
            }
        }    
        if (ret) {
            if (c->f) liberaform(c->f);
            c->f=NULL;
            strcpy(c->rec.npantalla,"");
            strcpy(c->rec.codperfil,"");
            RECactualizanpantalla(&c->rec,NOVERIFICA);
            liberaterminal(c);
            commit();
            gestionaterminal(1,c);
        }
    }
    return(0);
}

int tratafrm(conexiones *c)
{
    int ret;
    ret=lltratafrm(c);
    return(ret);
}