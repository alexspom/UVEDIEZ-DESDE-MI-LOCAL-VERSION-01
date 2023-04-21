#include "v10etiqueta.h"

#define PREFORMAT   '^'
#define PRECONTROL  '~'
#define PREFIJO     "^XA"
#define SUFIJO      "^XZ"
#define CODESC  27
static double multfontx=3;
static double multfonty=3;
static double PPMHX     =8.3;
static double PPMHY     =8;
static double PPMVX     =8;
static double PPMVY     =8.2;

static tcpipetiq *tcpipzpl;
static void posicionazplii(idrivers *id,char **ptrsal)
{
    int x,y,tx,ty;
    if (id->numcad) {        // Vertical (Z4MPlus)
        x=(int)((id->px)*PPMVX)/10;
        ty=(int)(id->tx*PPMVY)/10;
        tx=(int)(id->ty*PPMVX)/10;
    } else {                 // Horizontal (Z6MPlus)
        x=(int)(id->px*PPMHX)/10;
        tx=(int)(id->tx*PPMHX)/10;
        ty=(int)(id->ty*PPMHY)/10;
    }
    if (id->numcad) y=(int)((id->py)*PPMVY+5)/10;
    else y=(int)((id->py)*PPMHY+5)/10;
    if (y<0) y=0;
    if (x<0) x=0;
    if (id->numcad==0) if (x>tx) x=tx;
    if (id->numcad) {
        sprintf(*ptrsal,"%cFT%04d,%04d",
            PREFORMAT,x,y);
    } else {
        sprintf(*ptrsal,"%cFT%04d,%04d",
            PREFORMAT,ty-y,x);
    }
    *ptrsal+=strlen(*ptrsal);
}

static char damerrotacion(idrivers *id,int angulo)
{
    char orientacion;
    if (id->numcad) {
        angulo-=90;
        if (angulo<0) angulo+=360;
    }
    if (angulo<90) {
        orientacion='R';
    } else {
        if (angulo<180) {
            orientacion='I';
        } else {
            if (angulo<270) {
                orientacion='B';
            } else {
                orientacion='N';
            }
        }
    }
    return(orientacion);
}

static void pasararas(char *cadena,char *fin)
{
    char *ptr;
    for (ptr=cadena;ptr<=fin;ptr++) {
        if (*ptr=='Ñ') *ptr=0x5c;
        if (*ptr=='ñ') *ptr=0x7c;
    }
}

static void imprimecadenazplii(idrivers *id,char *cadena,char *fin,char *ptrsal)
{
    char orientacion;
    char fuente='0';
    if (id->font==1) fuente='B';
    orientacion=damerrotacion(id,id->angulo);
    posicionazplii(id,&ptrsal);
    pasararas(cadena,fin);
    sprintf(ptrsal,"%cA%c%c,%d,%d%cFD%-*.*s%cFS",
        PREFORMAT,fuente,orientacion,(int)(id->fx*multfontx),(int)(id->fy*multfonty),
        PREFORMAT,fin-cadena,fin-cadena,cadena,
        PREFORMAT);
    
    ptrsal+=strlen(ptrsal);
}

static void imprimecadenazplinvii(idrivers *id, char *cadena, char *fin, char *ptrsal)
{
	char orientacion;
	char fuente = '0';
	if (id->font == 1) fuente = 'B';
	orientacion = damerrotacion(id, id->angulo);
	posicionazplii(id, &ptrsal);
	pasararas(cadena, fin);
	sprintf(ptrsal, "%cA%c%c,%d,%d%cFR%cFD%-*.*s%cFS",
		PREFORMAT, fuente, orientacion, (int)(id->fx*multfontx), (int)(id->fy*multfonty),
		PREFORMAT, PREFORMAT, fin - cadena, fin - cadena, cadena,
		PREFORMAT);

	ptrsal += strlen(ptrsal);
}

static void comprime128(char *origen,char *hasta,char *destino)
{
	char *ptr=origen,*prin=ptr;
	int numdig=0,encodec=0;
	while (ptr<hasta) {
		if (isdigit(*ptr)) {
			if (numdig==0) {
				prin=ptr;
			}
			numdig++;
		} else {
			if (numdig) {
				if (numdig>3 || (numdig>1 && encodec==1)) {
					if (numdig%2) {
						ptr--;
						numdig--;
					}
					if (encodec==0) {
						if (prin==origen) {
							*destino++='>';
							*destino++=';';
						} else {
							*destino++='>';
							*destino++='5';
						}
					}
					encodec=1;
					while (prin<ptr) {
						*destino++=*prin++;
						numdig--;
					}
				} else {
					ptr=prin;
					numdig=0;
				}
			}
			if (*ptr=='¿') {
				if (prin==origen) {
					*destino++='>';
					*destino++=';';
					encodec=1;
				}
				*destino++='>';
				*destino++='8';
				prin=++ptr;
				continue;
			}
			if (encodec) {
				*destino++='>';
				*destino++='6';
			}
			encodec=0;
			*destino++=*ptr;
			numdig=0;
			prin=ptr;
		}
		ptr++;
	}
	if (numdig>0) {
		if (numdig>1) {
			if (numdig%2) {
				if (encodec) {
					while (numdig>1) {
						*destino++=*prin++;
						numdig--;
					}
					*destino++='>';
					*destino++='6';
				} else {
					*destino++=*prin++;
					*destino++='>';
					*destino++='5';
				}
			} else {
				if (prin==origen) {
					*destino++='>';
					*destino++=';';
				} else {
					if (encodec==0) {
						*destino++='>';
						*destino++='5';
					}
				}
			}
		}
	} else prin=hasta;
	while (prin<hasta) {
		if (*prin=='¿') {
			*destino++='>';
			*destino++='8';
		} else {
			*destino++=*prin;
		}
		prin++;
	}
	*destino=0;
}

static void imprimebarraszplii(idrivers *id,char *cadena,char *fin,char **ptrsal)
{
    int  ancho,alto;
    char destino[MAXCADENA];
    char orientacion;
    orientacion=damerrotacion(id,id->angulo);
    id->numcb++;
    posicionazplii(id,ptrsal);
    if (id->numcad) {
        ancho=(int)(id->ancb*PPMVY)/100;
        alto=(int)(id->alcb*(PPMVX-0.1))/10;
    } else {
        ancho=(int)(id->ancb*PPMHX)/100;
        alto=(int)(id->alcb*PPMHY)/10;
    }
	switch (id->tipocb) {
	case INTER25:
        strcopia(destino,cadena,fin-cadena);
        sprintf(*ptrsal,"%cBY%d%cB2%c,%3d,N,N,N%cFD%-*.*s%cFS",
            PREFORMAT,ancho,
            PREFORMAT,orientacion,alto,
            PREFORMAT,strlen(destino),strlen(destino),destino,
            PREFORMAT);
        break;
    case EAN13:
        strcopia(destino, cadena, fin - cadena);
        sprintf(*ptrsal, "%cBY%d%cBE%c,%3d,Y,N%cFD%-*.*s%cFS",
                PREFORMAT, ancho,
                PREFORMAT, orientacion, alto,
                PREFORMAT, strlen(destino), strlen(destino), destino,
                PREFORMAT);
        break;
    case DATAMATRIX:
        strcopia(destino, cadena, fin - cadena);
        sprintf(*ptrsal, "%cBXN,%d,200%cFD%-*.*s%cFS",
                PREFORMAT, ancho,
                PREFORMAT, strlen(destino), strlen(destino), destino,
                PREFORMAT);
        break;
    case PDF417:
        strcopia(destino, cadena, fin - cadena);
        sprintf(*ptrsal, "%cBY%d,%d%cB7%c,5,5,,%d,N%cFD%-*.*s%cFS",
                PREFORMAT, ancho,alto,
                PREFORMAT, orientacion,id->ratiocb,
                PREFORMAT, strlen(destino), strlen(destino), destino,
                PREFORMAT);
        break;
	default:
            comprime128(cadena, fin, destino);
            sprintf(*ptrsal, "%cBY%d%cBC%c,%3d,N,N,N,N%cFD%-*.*s%cFS",
                PREFORMAT, ancho,
                PREFORMAT, orientacion, alto,
                PREFORMAT, strlen(destino), strlen(destino), destino,
                PREFORMAT);
    }
    *ptrsal+=strlen(*ptrsal);
}

static void imprimelineazplii(idrivers *id,char **ptrsal,int lx,int ly,int ancho,int tipo)
{
    int an;
    int px,py;
    if (id->numcad) {
        an=(int)(ancho*PPMVX)/100;
        py=(int)(lx*PPMVX)/10;
        px=(int)(ly*PPMVY)/10;
        id->px-=lx;
    } else {
        an=(int)(ancho*PPMHX)/100;
        px=(int)(lx*PPMHX)/10;
        py=(int)(ly*PPMHY)/10;
    }
    posicionazplii(id,ptrsal);
	if (tipo == 2) {//rectángulo con relleno
		if (py > px) //se pone el ancho de línea a la menor de sus dimensiones
			an = px;
		else
			an = py;
	}

	sprintf(*ptrsal, "%cGB%d,%d,%d%cFS",
		PREFORMAT, py, px, an,
		PREFORMAT);
	
    *ptrsal+=strlen(*ptrsal);
}

static void imprimelogozplii(idrivers *id,char **ptrsal,int lx, int ly, int tx, int ty, char *nombre)
{
    int px,py;
    if (id->numcad) {
        py=(int)(lx*PPMVX)/10;
        px=(int)((id->ty-ly-tx)*PPMVY)/10;
    } else {
        px=(int)(lx*PPMHX)/10;
        py=(int)(ly*PPMHY)/10;
    }
    sprintf(*ptrsal,"%cFO%d,%d%cXGE:%s,1,1%cFS",
        PREFORMAT,py,px,PREFORMAT, nombre,
        PREFORMAT);
    *ptrsal+=strlen(*ptrsal);
}

static void tiraetiqzplii(idrivers *id,char **ptrsal)
{
    sprintf(*ptrsal,"%s",SUFIJO);
    *ptrsal+=strlen(*ptrsal);
}

static void initetiqzplii(idrivers *id,char **ptrsal)
{
    sprintf(*ptrsal,"%s%cCI10",PREFIJO,PREFORMAT);
    *ptrsal+=strlen(*ptrsal);
}
static void initetiqzplii300(idrivers *id,char **ptrsal)
{
    sprintf(*ptrsal,"%s%cMUd,200,300%cCI10",PREFIJO,PREFORMAT,PREFORMAT);
    *ptrsal+=strlen(*ptrsal);
}

#define MAXSTATUS 100
#define STIMPIDDLE  0
#define STIMPENVEQ  1
static char buffer[MAXSTATUS],*ptr=buffer;
static int st=STIMPIDDLE;
static v10horas hstatus;
static int numstlin;

#define TIMEREINT    120
#define TIMEOUTIMPRE 100


void finalizazpl(idrivers *id)
{
    if (tcpipzpl==NULL) return;
    if (tcpipzpl->pipeenv==NULL) return;
    v10socklibera(tcpipzpl->pipeenv);
    tcpipzpl->pipeenv=NULL;
}

#define REINTENTOS 10
static int statuszplii(idrivers *id,int PUERTO,tcpipetiq *tcpip)
{
    static v10horas ultint;
    static int reintentos;
    if (PUERTO==-1 && tcpip) {
        if (tcpip->pipeenv==NULL) {
            ultint=damecent();
        }
        
        if (tcpip->pipeenv==NULL)            
            tcpip->pipeenv=v10socknuevocliente(tcpip->ip,tcpip->puertotcpenv,0,4096,NULL,NULL,NULL,NULL,NULL);
        if (tcpip->pipeenv) {
            struct linger ling;
            ling.l_onoff=1;
            ling.l_linger=35000;
            v10sockopt(tcpip->pipeenv,SO_LINGER,SOL_SOCKET,(char *)&ling,sizeof(ling));
            ultint=damecent();
            tcpipzpl=tcpip;
            reintentos=0;
            return (STTERMICAOK);
        } else {
            if (reintentos++>REINTENTOS) {
                mensajefcm(10,"No se puede establecer comunicacion con etiquetadora %s ",tcpip->ip);
                reintentos=0;
            }
            return(STTERMICAAPAGADA);
        }
    } else if (PUERTO==-1) return(STTERMICAOK);
    switch (st) {
    case STIMPIDDLE:while (damecar232(PUERTO)!=-1);
        printf232(PUERTO,"%cHS",PRECONTROL);
        ptr=buffer;
        hstatus=damecent();
        st=STIMPENVEQ;
        numstlin=0;
        break;
    case STIMPENVEQ:
		while (haycar232(PUERTO)) {
			int ch;
			ch=damecar232(PUERTO);
			if (ptr-buffer>=MAXSTATUS) {
				ptr=buffer;
				st=STIMPIDDLE;
				return(STTERMICAAPAGADA);
			}
			*ptr++=(char)ch;
			if (ch==lf) numstlin++;
			if (numstlin==3) {
				int papel,pausa,buflleno,ram,tempbaja,tempalta,cabezal,ribon,impresa;
				papel=buffer[5]-'0';
				pausa=buffer[7]-'0';
				buflleno=buffer[18]-'0';
				ram=buffer[28]-'0';
				tempalta=buffer[30]-'0';
				tempbaja=buffer[32]-'0';
				cabezal=buffer[43]-'0';
				ribon=buffer[45]-'0';
				impresa=atoi(buffer+14);
				st=STIMPIDDLE;
				if (papel) return(STTERMICASINPAPEL);
				if (ribon) return(STTERMICASINCINTA);
				if (impresa) return(STTERMICACARGADA);
				if (pausa) return(STTERMICAPAUSA);
				if (buflleno) return(STTERMICABUFFER);
				if (ram||tempalta||tempbaja) return(STTERMICAHARD);
				if (cabezal) return(STTERMICAABIERTA);
				return(STTERMICAOK);
			}
		}			
		if (damecent()-hstatus>TIMEOUTIMPRE) {
			st=STIMPIDDLE;
			return(STTERMICAAPAGADA);
		}
		break;
    }
    return(STTERMICAENCURSO);
}

static void cancelatrabajozplii(idrivers *id,int PUERTO,tcpipetiq *tcpip)
{
	if (tcpip) v10sockprintf(tcpip->pipeenv,"%cJA",PRECONTROL);
    else printf232(PUERTO,"%cJA",PRECONTROL);
}

void pondriverzplii(idrivers *id)
{
    id->imprimecadena=imprimecadenazplii;
	id->imprimecadenainv=imprimecadenazplinvii;
    id->imprimebarras=imprimebarraszplii;
    id->imprimelinea=imprimelineazplii;
    id->imprimelogo=imprimelogozplii;
    id->cancelatrabajo=cancelatrabajozplii;
    id->tiraetiq=tiraetiqzplii;
    id->cambiamaxetiq=NULL;
    id->initetiq=initetiqzplii;
    id->statusimpre=statuszplii;
    id->repiteetiq=0;
    id->finaliza=finalizazpl;
    id->numcad=0;
    PPMHX     =8.3;
    PPMHY     =8;
    PPMVX     =8;
    PPMVY     =8.3;
    multfontx=3;
    multfonty=3;
}

void pondriverzpliiv(idrivers *id)
{
    id->imprimecadena=imprimecadenazplii;
	id->imprimecadenainv=imprimecadenazplinvii;
    id->imprimebarras=imprimebarraszplii;
    id->imprimelogo=imprimelogozplii;
    id->imprimelinea=imprimelineazplii;
    id->cancelatrabajo=cancelatrabajozplii;
    id->tiraetiq=tiraetiqzplii;
    id->cambiamaxetiq=NULL;
    id->initetiq=initetiqzplii;
    id->statusimpre=statuszplii;
    id->repiteetiq=0;
    id->finaliza=finalizazpl; 
    id->numcad=1;
    PPMHX     =8.3;
    PPMHY     =8;
    PPMVX     =8;
    PPMVY     =8.3;
    multfontx=3;
    multfonty=3;
}

void pondriverzplii300(idrivers *id)
{
    id->imprimecadena=imprimecadenazplii;
	id->imprimecadenainv=imprimecadenazplinvii;
    id->imprimebarras=imprimebarraszplii;
    id->imprimelogo=imprimelogozplii;
    id->imprimelinea=imprimelineazplii;
    id->cancelatrabajo=cancelatrabajozplii;
    id->tiraetiq=tiraetiqzplii;
    id->cambiamaxetiq=NULL;
    id->initetiq=initetiqzplii300;
    id->statusimpre=statuszplii;
    id->repiteetiq=0;
    id->finaliza=finalizazpl;
    id->numcad=0;
    PPMHX     =12.08;
    PPMHY     =11.76;
    PPMVX     =11.76;
    PPMVY     =12.08;
    multfontx=4.4;
    multfonty=4.4;
}