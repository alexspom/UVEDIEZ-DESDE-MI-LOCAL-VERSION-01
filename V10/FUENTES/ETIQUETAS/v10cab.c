#include "v10etiqueta.h"

#define MEDIDA      "m m" //fuerza la unidad de medida a mil�metros
#define ORIENTACION "O R" //Con "O R" etiqueta normal, sin esta instucci�n aparecer� invertida
#define PREFIJO     'J'
#define SUFIJO      "A 1" //A indica el fin de la etiqueta, el n�mero que la acompa�a indica la cantidad de copias
#define ESC         "27"//Caracter de escape


static tcpipetiq *tcpipcab;

static int damerrotacion(int angulo) //para los elementos que solo admiten una rotaci�n de 0, 90, 180 o 270 se verifica que se corresponda
{
    int orientacion;

    if (angulo != 0 && angulo != 90 && angulo != 180 && angulo != 270)
		orientacion = 0;
	else
		orientacion = angulo;

    return(orientacion);
}

static void pasararas(char *cadena,char *fin)
{
    char *ptr;
    for (ptr=cadena;ptr<=fin;ptr++) {
        if (*ptr=='�') *ptr=0x5c;
        if (*ptr=='�') *ptr=0x7c;
    }
}

static void asignatametiqcab(idrivers *id,char **ptrsal)
{

	//S[ptype;]xo,yo,ho,dy,wd[,dx,col][;name] CR //xo: desplazamiento x repecto al punto origen ,yo:desplazamiento y repecto al punto origen ,ho: altura ,dy: altura m�s espacio entre entre etiquetas, wd: anchura
	
	sprintf(*ptrsal,"S 0,0,%d,%d,%d\n", id->tx/10, (id->tx/10)+3, id->ty/10);

    *ptrsal+=strlen(*ptrsal);
}

static void imprimecadenacab(idrivers *id,char *cadena,char *fin,char *ptrsal)
{
	//en la cadena simepre viene el �timo caracter de cierre de etiqueta
	char cadenatmp[300];
	char *tmp;
	int i = 0;
	int fuente, tam;
    
	for (tmp=cadena; tmp<fin; tmp++) {
        cadenatmp[i++] = *tmp;
    }
	cadenatmp[i] = '\0';
	
	//T[:name;]x,y,r,font,size[,effects];text

	//El tama�o de la letra es un valor recibido en puntos, tratado aqu� en mil�metros, usable para las fuentes escalables(Vector)
	//Se usa el valor id->fx

    tam = (int)id->fx/2;
	if (tam == 0)
		tam = 1;

    
	switch (id->font) {
           case 0: fuente = 3;  //Vector Swiss 721
			       break;
           case 1: fuente = 5;  //Vector Swiss 721 Bold
			       break;
           case 2: fuente = 596;//Vector Monospace 821
			       break;
		   case 3:
		   case 4: 
		   case 5:
		   case 6: 
		   case 7:
		   case 8:
		   case 9:fuente = 3;  //Vector Swiss 721
			   break;
				   
	}

    
    pasararas(cadena,fin);

    sprintf(ptrsal,"T %d,%d,%d,%d,%d;%s\n", (int)id->px/10, (int)id->py/10, damerrotacion(id->angulo), fuente, tam, cadenatmp);
    
    ptrsal+=strlen(ptrsal);
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
							/**destino++='>';
							*destino++=';';*/
						} else {
							/**destino++='>';
							*destino++='5';*/
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
			if (*ptr=='�') {
				if (prin==origen) {
					/**destino++='>';
					*destino++=';';*/
					encodec=1;
				}
				*destino++ = '[';
				*destino++ = 'U';
				*destino++ = ':';
				*destino++ = 'F';
				*destino++ = 'N';
				*destino++ = 'C';
				*destino++ = '1';
				*destino++ = ']';
				/**destino++='>';
				*destino++='8';*/
				prin=++ptr;
				continue;
			}
			if (encodec) {
				/**destino++='>';
				*destino++='6';*/
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
					/**destino++='>';
					*destino++='6';*/
				} else {
					*destino++=*prin++;
					/**destino++='>';
					*destino++='5';*/
				}
			} else {
				if (prin==origen) {
					/*
					*destino++='>';
					*destino++=';';
					*/
				} else {
					if (encodec==0) {
						/**destino++='>';
						*destino++='5';*/
					}
				}
			}
		}
	} else prin=hasta;
	while (prin<hasta) {
		if (*prin=='�') {
			/**destino++='>';
			*destino++='8';*/
		} else {
			*destino++=*prin;
		}
		prin++;
	}
	*destino=0;
}

static void imprimebarrascab(idrivers *id,char *cadena,char *fin,char **ptrsal)
{
    int alto;
	float ancho;
    char destino[MAXCADENA];
    id->numcb++;

    ancho=(float)(id->ancb)/100;
    alto=(int)(id->alcb)/10;
	//si se pasa el tipo de c�digo de barras en may�sculas, debajo imrime el c�digo en humano
    if (id->tipocb==2) { //Interleaved 2 of 5
		//B[:name;]x,y,r,2OF5INTERLEAVED[+options],height,ne,ratio;text
        strcopia(destino,cadena,fin-cadena);
        sprintf(*ptrsal,"B %d,%d,%d,2of5interleaved,%d,%.1f,%d;%s\n",id->px/10,id->py/10,damerrotacion(id->angulo),alto,ancho,id->ratiocb,destino);
    } else {
		if (id->tipocb==7) {//Ean13
			//B[:name;]x,y,r,EAN13[+options],height,ne;text
			strcopia(destino,cadena,fin-cadena);
			sprintf(*ptrsal,"B %d,%d,%d,ean13,%d,%.1f;%s\n",id->px/10,id->py/10,damerrotacion(id->angulo),alto,ancho,destino);
		} else {//code 128
	       //B[:name;]x,y,r,CODE128[+options],height,ne;[U:subcode]text
           comprime128(cadena,fin,destino);
		   sprintf(*ptrsal,"B %d,%d,%d,code128,%d,%.1f;%s\n",id->px/10,id->py/10,damerrotacion(id->angulo),alto,ancho,destino);
		}
    }
    *ptrsal+=strlen(*ptrsal);
}

static void imprimelineacab(idrivers *id,char **ptrsal,int lx,int ly,int ancho,int tipo)
{
    float px, py, an;

	px = (float)lx/10;
	py = (float)ly/10;
	an=(float)(ancho)/100;

	if (tipo == 0){//L�nea
		//G[:name;]x,y,r;L:length,width[,start[,end]][,options]	
		sprintf(*ptrsal,"G %d,%d,%d;L:%.1f,%.1f\n", id->px/10, id->py/10, id->angulo, px, an);

	} else if (tipo == 1){//Rect�ngulo
		//G[:name;]x,y,r;R:width,height[,ht [,vt]][,options]
		sprintf(*ptrsal,"G %d,%d,%d;R:%1.f,%.1f,%.1f\n", id->px/10, id->py/10, id->angulo, px, py, an);
	}

    *ptrsal+=strlen(*ptrsal);
}

static void imprimelogocab(idrivers *id, char **ptrsal, int px, int py, int tx, int ty, char *nombre){
	//I[:name;]x,y,r[,mx,my,GOODBADn][,a];name

	sprintf(*ptrsal,"I %d,%d,%d;%s\n", id->px/10, id->py/10, damerrotacion(id->angulo), nombre);
	*ptrsal+=strlen(*ptrsal);
}

static void tiraetiqcab(idrivers *id,char **ptrsal)
{
    sprintf(*ptrsal,"%s\n",SUFIJO);
    *ptrsal+=strlen(*ptrsal);
}

static void initetiqcab(idrivers *id,char **ptrsal)
{
	sprintf(*ptrsal,"%s\n%c\n%s\n",MEDIDA,PREFIJO,ORIENTACION);
    *ptrsal+=strlen(*ptrsal);
}


#define MAXSTATUS 100
#define STIMPIDDLE  0
#define STIMPENVEQ  1
static char buffer[MAXSTATUS];

#define TIMEREINT    120
#define TIMEOUTIMPRE 100


void finalizacab(idrivers *id)
{
    if (tcpipcab==NULL) return;
    if (tcpipcab->pipeenv==NULL) return;
    v10socklibera(tcpipcab->pipeenv);
    tcpipcab->pipeenv=NULL;
}

/*#define REINTENTOS 10
static int statuscab(idrivers *id,int PUERTO,tcpipetiq *tcpip)
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
            tcpipcab=tcpip;
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
        printf232(PUERTO,"%sa",ESC);
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
}*/

static void cancelatrabajocab(idrivers *id,int PUERTO,tcpipetiq *tcpip)
{
	if (tcpip) v10sockprintf(tcpip->pipeenv,"%sc",ESC);
    else printf232(PUERTO,"%sc",ESC);
}

void pondrivercab(idrivers *id)
{
	id->initetiq=initetiqcab;
	id->asignatametiq=asignatametiqcab;
    id->imprimebarras=imprimebarrascab;
    id->imprimelinea=imprimelineacab;
	id->imprimelogo=imprimelogocab;
	id->imprimecadena=imprimecadenacab;
    id->tiraetiq=tiraetiqcab;
    id->cambiamaxetiq=NULL;
	id->cancelatrabajo=cancelatrabajocab;
    id->finaliza=finalizacab;

	//id->statusimpre=statuscab;
	id->repiteetiq=0;
    id->numcad=0;
}