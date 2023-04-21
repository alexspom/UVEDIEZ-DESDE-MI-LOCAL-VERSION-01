#include "vdradio.h"

// Caracteres especiales TELNET
#define CIAC     255
#define CDONT    254
#define CDO      253
#define CWONT    252
#define CWILL    251
#define CECHO      1

//Definicion de cadenas especiales de TELNET
#define RESALTADO   "\033[7m"
#define NORESALTADO "\033[0m"
#define LIMPIAPAN   "\033[1;1H\033[2J\033[?25h"

void posicionaconexion(conexiones *c)
{
    bloques *b=c->f->b[c->f->act];
    v10sockprintf(c->v10sock,"\033[%d;%dH",b->vi.act->posy-b->vi.act->desp+1,b->vi.act->posx+(c->ptr-c->buffer)+1);
}

void presentacampotelnet(conexiones *c,int resaltado,int lon,int pass)
{
    posicionaconexion(c);
    v10sockprintf(c->v10sock,"%s%-*.*s",resaltado==1?RESALTADO:(resaltado==2?"":NORESALTADO),lon,lon,pass?"":c->buffer);
    posicionaconexion(c);
}

static void damecadenatelnet(conexiones *conex,char *cadena)
{
    bloques *b;
    char *ptr=cadena,*inicio;
    v10dialogs *vi;
    int i,j,off=0;
    v10inputs *v;
    fcampos *c;
    int nlinea,desp;
    strcpy(cadena,"");
    if (conex->f==NULL) return;
    if (conex->f->act<0) return;
    b=conex->f->b[conex->f->act];
    vi=&b->vi;
    if (conex->v10sock==NULL) return;
    for (i=0;i<vi->alto;i++) {
        for (j=0;j<vi->largo;j++) {
            *ptr++=(char)(vi->contenido[i*vi->largo+j].ch);
        }
        if (i<vi->alto-1) {
            *ptr++='\n';
        }
    }
    *ptr++='\n';
    *ptr=0;
    v=vi->prim;
    for (i=0;i<b->ncamp;i++) {
        char text[MAXCADENA];
        c=b->c+i;
        if (c->oculto) continue;
        bcampo2a(b,c->nombre,text,0);
        ltrim(text);
        pad(text,v->lpan);
        if (c->v->password || c->invisible) strfill(text,' ',(int)strlen(text));
        strcpy(cadena+v->posx+v->posy*(vi->largo+1)+off,cadena+v->posx+v->posy*(vi->largo+1)+v->lpan+off);
        strins(cadena+v->posx+v->posy*(vi->largo+1)+off,text);
        v++;
    }
    ptr=cadena;
    nlinea=0;
    desp=0;
    inicio=ptr;
    while ((ptr=strchr(ptr,'\n'))!=NULL) {
        char *fin;

        int haycampo=0;
        fin=ptr;
        while (*--ptr==' ' && ptr>=cadena);
        strcpy(ptr+1,fin);
        strins(ptr+1,"\r");
        ptr+=3;
        for (i=0;i<b->ncamp;i++) {
            c=b->c+i;
            if (c->oculto) continue;
            if (c->v->posy!=nlinea) continue;
            c->v->desp=desp;
            if (c->invisible) haycampo=1;
               else           haycampo=0;
        }
        if (haycampo) {
            strcpy(inicio,ptr);
            desp++;
        } else inicio=ptr;
        nlinea++;
    }
    trim(cadena);
    {char *ptr=cadena+strlen(cadena)-1;
    while (*ptr=='\n') ptr--;
    ptr[1]=0;
    }
    for (i=0;i<b->ncamp;i++) {
        c=b->c+i;
        if (c->oculto || c->enter==0 || c->noupdate==1 || c->invisible==1) {
            if (b->vi.act==c->v) b->vi.act++;
            continue;
        }
        if (b->vi.act==c->v) break;
    }
    if (b->vi.act<b->vi.prim || b->vi.act>b->vi.ult) b->vi.act=b->vi.prim;
} 

void pasapantalog(char *cadena)
{
	char *aux,*aux1,copia[MAXCADENA],*prin=copia;
	v10log(LOGNORMAL,"%s","Inicio de pantalla\n");
	strcpy(copia,cadena);
	while ((aux=strchr(prin,'\n'))!=NULL) {
		  *aux=0;
		  while ((aux1=strchr(prin,13))!=NULL) strcpy(aux1,aux1+1);
           v10log(LOGNORMAL,"%s\n",prin);
		   prin=aux+1;
	}
           v10log(LOGNORMAL,"%s\n",prin);
	v10log(LOGNORMAL,"%s","Fin de pantalla\n");

}


int form2telnet(conexiones *conex,int suena)
{
    bloques *b=conex->f->b[conex->f->act];
    char cadena[MAXCADENA];
    v10dialogs *vi=&b->vi;
    if (conex->mostrar==0) {
        conex->modificado=1;
        return(0);
	}
	if (conex->f == NULL) return(0);
	if (conex->f->act < 0) return 0;
	b = conex->f->b[conex->f->act];
    damecadenatelnet(conex,cadena);
    //v10log(LOGNORMAL,"mandada pantalla valor\n%s\n",cadena);
	pasapantalog(cadena);
    v10sockprintf(conex->v10sock,"%s%s",NORESALTADO,LIMPIAPAN);
    v10sockescribe(conex->v10sock,cadena,(int)strlen(cadena));
    v10sockprintf(conex->v10sock,"\033[%d;%dH",vi->act->posy-vi->act->desp+1,vi->act->posx+1);
    if (suena) v10sockprintf(conex->v10sock,"\007");
    if (haycampoenter(conex)) empiezainputcampo(conex);
    conex->mensaje=0;
    conex->modificado=0;
    return(0);
}

int mensajetelnet(conexiones *c,int suena,char *texto,va_list arg)
{
    char destino[MAXCADENA],destino2[MAXCADENA];
    char *ptr;
    ptr=destino;
    while (*texto) {
        if (*texto=='\\' && texto[1]=='n') {
            *ptr++='\n';
            *ptr++='\r';
            texto+=2;
            continue;
        }
        if (*texto=='\n') {
            *ptr++='\n';
            *ptr++='\r';
            texto+=1;
            continue;
        }
        *ptr++=*texto++;
    }
    *ptr=0;
    vsprintf(destino2,destino,arg);
    v10sockprintf(c->v10sock,"%s%s%s\033[1;1H",NORESALTADO,LIMPIAPAN,destino2);
    if (suena) v10sockprintf(c->v10sock,"\007");
    //v10log(LOGNORMAL,"Mandado mensaje %s\n",destino2);
	pasapantalog(destino2);
    if (c->contenidomensaje) free(c->contenidomensaje);
    c->contenidomensaje=strdup(destino2);
    c->mensaje=1;
    return(0);
}

static int telnet2form(conexiones *c)
{
    int ret;
    ret=terminainputcampo(c,1,0);
    c->mensaje=1;
    return(ret);
}

static int inittermtelnet(conexiones *c)
{
    v10sockprintf(c->v10sock,"%c%c%c",CIAC,CDONT,CECHO);
    v10sockprintf(c->v10sock,"CONEXION A TERMINAL %s\n",c->rec.codrecurso);
    return(0);
}

void cargadrivertelnet(raddrivers *dr)
{
    if (es_blanco(dr->serviciotcp)) strcpy(dr->serviciotcp,"telnet");
    strcpy(dr->nombre,"TELNET");
    dr->init=initradiotcp;
    dr->tick=telnettick;
    dr->initterm=inittermtelnet;
    dr->pasaformaterm=form2telnet;
    dr->pasatermaform=telnet2form;
    dr->presentacampo=presentacampotelnet;
    dr->mensaje=mensajetelnet;
    dr->encolatecla=encolateclaconexion;
    dr->damecadenaform=damecadenatelnet;
    if (dr->numports==0) dr->numports=1;
}