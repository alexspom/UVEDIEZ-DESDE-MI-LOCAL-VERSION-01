#include "v10.h"

int leecarespera(v10socks *p)
{
    int ret;
    while ((ret=v10socksigcar(p))==-1) if (p->status!=STSOCKREADY) return(-1);
    return(ret);
}

int leeshortespera(v10socks *p)
{
    int c1,c2;
    c1=leecarespera(p);
    if (c1==-1) return(-1);
    c2=leecarespera(p);
    if (c1==-1) return(-1);
    return (c2<<8)+c1;
}


DWORD threadid;

void creaventanarem(v10socks *p,int op,int lon,char *buffer,char *nombre)
{
    int altof=fontmensaje.alto,anchof=fontmensaje.ancho;
    char font[LF_FACESIZE];
    strcpy(font,fontmensaje.font);
    fontmensaje.alto=12;fontmensaje.ancho=8;strcpy(fontmensaje.font,"Terminal");
    p->extradata=calloc(1,sizeof(windows));
    creaventana(nombre,p->extradata,1,1,COLUMNASPANTALLA,LINEASPANTALLA,"DEFECTO");
    AttachThreadInput(GetCurrentThreadId(),threadid,TRUE);
    fontmensaje.alto=altof;fontmensaje.alto=anchof;strcpy(fontmensaje.font,(char *)font);
}

void liberaventanarem(v10socks *p,int op,int lon,char *buffer)
{
    if (p->extradata) free(p->extradata);
    p->extradata=NULL;
}

void tratacliente(v10socks *p)
{
    int columnas,filas,i;
    char *ptr;
    v10horas inicio;
    windows *w=p->extradata;
    extrawins *t=dameextrawin(w->hwnd);
    columnas=leecarespera(p);
    if (columnas==-1) return;
    filas=leecarespera(p);
    if (filas==-1) return;
    inicio=gettime();
    for (i=0;i<filas;i++) {
        int ret,leer;
        ptr=((char *)t->texto)+t->columnas*i*sizeof(tpixels);
        leer=columnas*sizeof(tpixels);
        while (leer>0) {
            ret=v10sockread(p,ptr,leer);
            ptr+=ret;
            leer-=ret;
            if (gettime()-inicio>200) break;
        }
    }
    InvalidateRect(w->hwnd,NULL,0);
}

static void mandacar(v10socks *p,int op,int lon,char *buffer)
{
  int tec=0;
  v10sockescribe(p,&tec,sizeof(short));
}

static void ponbreak(v10socks *p,int op,int lon,char *buffer)
{
  v10log(LOGNORMAL,"Perdida conexion\n");
}

void testclientepantalla(char *maquina,char *puerto)
{
    int tec;
    int reint;
    v10socks *p;
    char titulo[MAXPATH];
    sprintf(titulo,"VISUALIZA %s puerto %s",maquina,puerto);
    SetWindowText(hwnddefecto,titulo);
    initv10log("CLIENTES.LOG");
    threadid=GetCurrentThreadId();
    p=v10socknuevocliente(maquina,puerto,1,TAMRECSERVER*2,NULL,mandacar,NULL,ponbreak,liberaventanarem);
    if (p==NULL) {
        final(("No existe puerto %s en maquina %s\n",puerto,maquina));
        return;
    }
    creaventanarem(p,SOCKOPEN,0,NULL,titulo);
    v10log(LOGDEBUGAPI,"Entro a mostrar pantalla\n");
    while (1) {
        tec=0;
        reint=0;
        while (!hay_tecla() && reint<30) {
            Sleep(10); 
            reint++;
        }
        if (hay_tecla()) tec=tecla();
        if (tec=='T' || tec=='t') break;
        v10log(LOGDEBUGAPI,"Encolo tecla %d\n",tec);
        if (tec!=A_F(10) && tec!=ALT('T')) {
                if (v10sockhaycar(p)) {
                    tratacliente(p);
                }
                if (p->status==STSOCKREADY) {
                    v10sockescribe(p,&tec,sizeof(short));
                }
        }
    }
}

void logread(v10socks *p,int op,int lon,char *buffer)
{
    maxnivellog=0;
    v10log(LOGNORMAL,"%-*.*s",lon,lon,buffer);
}

void testclientelog(int clientes,char *maquina,char *puerto)
{
    int i;
    v10socks *p[1000];
    initv10log("CLIENTES.LOG");
    SetWindowText(hwnddefecto,puerto);
	ShowWindow(hwnddefecto,SW_SHOWMAXIMIZED);
    for (i=0;i<clientes;i++) {
        p[i]=v10socknuevocliente(maquina,puerto,1,4096,NULL,NULL,logread,ponbreak,NULL);
    }
    while (1) {
        if (hay_tecla()) if (tecla()==esc) break;
        Sleep(10);
    }
}


int main(int argc,char *argv[])
{
    char *port;
    char *maquina;
    char portpantalla[MAXPATH],portlog[MAXPATH];
    if (argc<3) final(("Uso visualiza MAQUINA PORT [TIPO(P/L)]"));
    port=argv[2];
    if (*argv[1]==0) maquina=".";
       else          maquina=argv[1];
    
	if (atoi(port)==0) {
		sprintf(portpantalla,"%sPANT",port);
		sprintf(portlog,"%sLOG",port);
	} else {
		strcpy(portpantalla, port);
		strcpy(portlog, port);
	}

    if (argc==3) 
		testclientepantalla(maquina,portpantalla); //Por defecto visualiza pantalla
    else {
		switch(*argv[3]) {
			case 'L': testclientelog(1,maquina,portlog);
			          break;
			case 'P': testclientepantalla(maquina,portpantalla);
					  break;
			default: final(("La variable TIPO sólo puede ser P(antalla) o L(og)"))
		}
	}
    return(0);
}

int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hprev,
           LPSTR cmd, int cmdshow)
{
  int ret;
  strcpy(TITULOVENTANA,"VISUALIZA");
  COLUMNASPANTALLA = 129;
  LINEASPANTALLA = 59;
  initv10lib(hinst,hprev);
  ret=main(__argc,__argv);
  return(ret);
}
