/*
* M�dulo : V10KEYBOARD.C
* Objeto:  Gestion del teclado
*
*
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"

#define MAXTECLAS 1024  /* Tama�o del buffer de teclado */
#define MAX_ESPECIAL 10  /* M�ximo n�mero de teclas a las que se puede
			    asignar una funci�n especial. */
typedef struct {
	  int key;
	  int activo;
	  void (*funcion)(int mikey);
	} mis_trigers;
unsigned long ttimeout=10;
mouseposs mousepos;
int alter[50]={286,304,302,288,274,289,290,291,279,292,293,294,306,305,280,281,272,275,287,276,278,303,273,301,277,300};
int ins = 0;
int ult_pul = 0;
int (*triger_tecla_antes)(void) = NULL;
int (*triger_tecla_despues)(int) = NULL;

static int pila_teclas[MAXTECLAS];  /* Buffer interno de teclas pulsadas */
static int tope_tecla;  /* Indice del al �ltimo car�cter del buffer */

static unsigned timeout = 0;
static void (*triger_timeout)(void) = NULL;
	 /* Si transcurre un tiempo "timeout" en centesimas de
	    segundo y no se pulsa ninguna tecla se ejecuta la
	    funci�n "triger_timeout()". */

static void (*triger_iddle)(void) = NULL;
	 /* Funci�n que se ejecuta siempre que se invoca una petici�n
	    de tecla. */

static int numtriger; /* N�mero de teclas a las que se les ha asignado
			 un tratamiento especial. Se pueden definir
			 hasta MAX_ESPECIAL, de 0 al MAX_ESPECIAL-1. */

static mis_trigers triger[MAX_ESPECIAL];
	 /* Array con: el c�digo de tecla asignado a cada funci�n de
	    tratamiento especial, una bandera indicando si se est�
	    ejecutando la funci�n especial asignada al c�digo de tecla
	    (esto evita una posible recursi�n) y un puntero a la funci�n
	    que realiza la tarea especial. Esta funci�n recibe como
	    par�metro la tecla que la invoca y puede ser aprovechado o
	    no. */

static v10horas horatimeout;

static void traducelinux(XKeyEvent *event)
{
    char buffer[100];
    KeySym key;
    int sh,alt,ctr;
    sh=event->state&1;
    alt=event->state&8;
    ctr=event->state&4;
    XLookupString(event, buffer, 20,&key,NULL);
    if (IsModifierKey(key)) return;
    switch (key) {
          case XK_Page_Up : if (sh) key=spgup;
                            else if (ctr) key=cpgup;
                                    else  key=pgup;
                         break;
          case XK_Page_Down:  if (sh) key=spgdn;
                            else if (ctr) key=cpgdn;
                                    else  key=pgdn;
                         break;
          case XK_Insert:if (sh) key=sinse;
                            else if (ctr) key=cinse;
                                    else  key=inse;
                         break;
          case XK_Return:key=cr;
                         break;
          case XK_Tab:   key=tab;
                         break;
          case XK_Escape: key=esc;
                          break;
          case XK_Delete:if (sh) key=sdele;
                            else if (ctr) key=cdele;
                                    else  key=dele;
                         break;
          case XK_BackSpace: key=back;
                             break;
          case XK_End:   if (sh) key=shend;
                            else if (ctr) key=cend;
                                    else  key=end;
                         break;
          case XK_Home:  if (sh) key=shome;
                            else if (ctr) key=chome;
                                    else  key=home;
                         break;
          case XK_Left:if (sh) key=scui;
                            else if (ctr) key=ccui;
                                    else  key=cui;
                       break;
          case XK_Up:  if (sh) key=scuu;
                            else if (ctr) key=ccuu;
                                    else  key=cuu;
                       break;
          case XK_Right:if (sh) key=scud;
                            else if (ctr) key=ccud;
                                    else  key=cud;
                         break;
          case XK_Down:if (sh) key=scua;
                            else if (ctr) key=ccua;
                                    else  key=cua;
                         break;
          default: if (key>=XK_F1 && key<=XK_F12) {
                      if (sh) {if (ctr) key=key-XK_F1+C_F(1); else key=key-XK_F1+S_F(1);}
                        else  if (ctr) key=key-XK_F1+C_F(1);
                                else if (alt) key=key-XK_F1+A_F(1);
                                      else key=key-XK_F1+F(1);
          } else {
                  if ((key>='A' && key <='Z')|| (key>='a' && key<='z')) {
                      if (ctr) key=CTRL(upper(key));
                        else if (alt) key=ALT(upper(key));
                  }
                  if (key>='0' && key<='9' && alt) key=ALTN(key-'0');
          }
    }
    STDencolatecla(key);
 //   v10log(LOGNORMAL,"Tecla pulsada %x estado %d\n",key,event->state);
}

static XButtonEvent antboton;
#define TIMEDBCLICK 300
static int trataraton(XButtonEvent *xb)
{
  extrawins *t=dameextrawin(dameventana(xb->window));
  STDencolatecla(MOUSEPOS);
  mousepos.posx=xb->x/t->anchofont;
  mousepos.posy=xb->y/t->altofont+t->origeny;
  mousepos.hwnd=dameventana(xb->window);
  if (xb->button==1) mousepos.boton=BOTONI;
   else if (xb->button==2) mousepos.boton=BOTONM;
        else if (xb->button==3) mousepos.boton=BOTOND;
             else mousepos.boton=xb->button;
  if (xb->time-antboton.time<TIMEDBCLICK && xb->button==antboton.button) mousepos.action=DOBLECLICK;
     else mousepos.action=CLICK;
 // printf("Boton %d estado %d ACCION %d\n",xb->button,xb->state,mousepos.action);
  antboton=*xb;
  return(0);
}

int tratamensajes(void)
{
    XEvent report;
    int tratado=0;
    HWND invalida;
	while ((invalida = ventanainvalida())) {
		xinvalido = 0;
		invalida->invalido = 0;
		if (invalida->sinx == 1) continue;
		report.type = Expose;
		report.xany.window = invalida->win;
		trataotroevento(&report);
	}
	if (hwnddefecto->sinx == 1) return (0);
    while (XCheckMaskEvent(xwindisplay, INPUTMASK,&report)) {
        if (dameventana(report.xany.window)==NULL) continue;
//        XNextEvent(xwindisplay, &report);
//        printf("Recibido evento %d dato %p\n",report.type,wdata);
        tratado++;
        switch (report.type) {
        case ButtonPress:trataraton(&report.xbutton);
                         break;
            /* Trickle down into KeyPress (no break) */
        case KeyPress:traducelinux(&report.xkey);
                      break;
        default:trataotroevento(&report);
            /* All events selected by StructureNotifyMask
            * except ConfigureNotify are thrown away here,
            * since nothing is done with them */
            break;
        } /* End switch */
    } /* End while */
   return(tratado);
}

int esperamensaje(int espera)
{
    v10horas inicio=damecent();
    while (tratamensajes()==0) {
        Sleep(1);
        if (damecent()-inicio>espera) break;
    }
    return(0);
}

static int winkeynoesp(void)
{
  tratamensajes();
  if (tope_tecla) return(pila_teclas[tope_tecla-1]);
  return(0);
}

static int winkey(void)
{
  while (winkeynoesp()==0);
  return(pila_teclas[--tope_tecla]);
}

int STDpushtecla(int cual)
{
  if (tope_tecla<MAXTECLAS-1) {
     v10limpiatooltip(hwnddefecto);
     pila_teclas[tope_tecla++]=cual;
     return(0);
   } else return(1);
}

int STDencolatecla(int cual)
{
  if (tope_tecla<MAXTECLAS-1) {
     memmove(pila_teclas+1,pila_teclas,sizeof(*pila_teclas)*tope_tecla);
     pila_teclas[0]=cual;
     tope_tecla++;
     v10limpiatooltip(hwnddefecto);
     return(0);
   }
  return(1);
}

int hay_cualquier_tecla(void)
{
  unsigned ch;
  static int llamado_iddle=0;

  if (triger_iddle && llamado_iddle==0) {
     llamado_iddle=1;
     (*triger_iddle)();
     llamado_iddle=0;
   }
  disparatimers(TIMERTECLA);
  disparatimers(TIMERTIMEOUT);

  ch=winkeynoesp();
  if (tope_tecla) return(pila_teclas[tope_tecla-1]);
  if (ch==0) return(0);
  if (ch==CTRL_BREAK) return(ch);
  if (ch&255) return(ch&255);
  return((ch>>8)+256);
}


int hay_tecla_normal(void)
{
  int j,ch;

  ch=hay_cualquier_tecla();
  if (ch) {
    for (j=0;j<MAX_ESPECIAL;j++) {
      if ((ch==triger[j].key)) {
        if (!triger[j].activo) {
          triger[j].activo=-1;
          if (tope_tecla) tope_tecla--;
          else winkey();
          if (triger[j].funcion) (triger[j].funcion)(triger[j].key);
          triger[j].activo=0;
          return(hay_tecla_normal());
        }
      }
    }
  }
  return(ch);
}


int hay_tecla_contimeout(void)
{
  int ch;
  static int puesto = 0;

  ch=hay_cualquier_tecla();
  if (ch) {
    puesto=0;
    resettimers(TIMERTIMEOUT);
  } else {
    if (timeout) {
      if (!puesto) {
        horatimeout=gettime()+timeout;
        puesto=1;
      }
      if (gettime()>horatimeout) {
        if (triger_timeout) (*triger_timeout)();
        puesto=0;
      }
    }
  }
  return(ch);
}


int hay_tecla_normalcontimeout(void)
{
  int ch;
  static int puesto = 0;

  ch=hay_tecla_normal();
  if (ch) {
    puesto=0;
  } else {
    if (timeout) {
      if (!puesto) {
        horatimeout=gettime()+timeout;
        puesto=1;
      }
      if (gettime()>horatimeout) {
        if (triger_timeout) (*triger_timeout)();
        puesto=0;
      }
    }
  }
  return(ch);
}

int hay_tecla(void)
{
  return(hay_tecla_normalcontimeout());
}


int STDtecla(void)
{
  v10horas conta = gettime();
  int j;
  int ch;
  int salir = 1;
  int ejecuta_tecla = 0;

  if (triger_tecla_antes) ejecuta_tecla=triger_tecla_antes();
  if (ejecuta_tecla==0) {
     if (timeout || ttimeout) {
        if (timeout==0) timeout=ttimeout;
        while (salir) {
              while ((gettime()-conta < timeout) && ((hay_cualquier_tecla()==0))) {
                    if (ttimeout) esperamensaje(ttimeout);
                  }
              if (!hay_cualquier_tecla()) {
                 if (triger_timeout) (*triger_timeout)();
               } else  salir=0;
              conta=gettime();
          }
      }
     if (tope_tecla) ch=pila_teclas[--tope_tecla];
        else {
            while ((ch=hay_cualquier_tecla())!=0);
             ch=winkey();
         }
     resettimers(TIMERTIMEOUT);
     ult_pul=ch;
     for (j=0;j<MAX_ESPECIAL;j++) {
         if ((ch==triger[j].key)) {
            if (!triger[j].activo) {
               triger[j].activo=-1;
               if (triger[j].funcion) (triger[j].funcion)(triger[j].key);
               triger[j].activo=0;
               return(tecla());
             }
          }
      }
     if (triger_tecla_despues) {
        ch=triger_tecla_despues(ch);
        ult_pul=ch;
      }
     return(ch);
   } else {
     ult_pul=ejecuta_tecla;
     return(ejecuta_tecla);
   }
}


void vaciateclado(void)
{
  while (hay_tecla_normal()) tecla();
}


void pontrigervivo(void *triger)
{
  triger_iddle=(void (*)(void))triger;
}

void *dametrigervivo(void)
{
  return((void *)triger_iddle);
}


void timeoutteclado(unsigned time,void *triger)
{
  timeout=time;
  triger_timeout=(void (*)(void))triger;
}


void dametimeoutteclado(unsigned *time,void **triger)
{
  *time=timeout;
  *triger=(void *)triger_timeout;
}


int asignatecla(int key,void (*funcion)(int mikey))
{
  if (numtriger>MAX_ESPECIAL-1) final(("Asignando demasiadas teclas"));
  triger[numtriger].key=key;
  triger[numtriger].funcion=funcion;
  numtriger++;
  return(numtriger);
}


int alttecla(int a)
{
  int i;

  for (i=0;i<='Z'-'A';i++)
    if (a==alter[i])
      return(i+'A');
  return(0);
}

int traducetecla(char *nombre)
{
  int ret;
  if (strcmp(nombre,"CR")==0) return(cr);
  if (strcmp(nombre,"LF")==0) return(lf);
  if (strcmp(nombre,"ESC")==0) return(esc);
  if (strcmp(nombre,"TAB")==0) return(tab);
  if (strcmp(nombre,"STAB")==0) return(stab);
  if (strcmp(nombre,"CUA")==0) return(cua);
  if (strcmp(nombre,"CUU")==0) return(cuu);
  if (strcmp(nombre,"PGUP")==0) return(pgup);
  if (strcmp(nombre,"PGDN")==0) return(pgdn);
  switch (*nombre) {
      case 'F':if (isdigit(nombre[2])) {
                  ret=F(0)+(nombre[1]-'0')*10+nombre[2]-'0';
                } else {
                  ret=F(0)+nombre[1]-'0';
                }
               break;
      case 'S':if (nombre[1]!='F') {
                  mensajefcm(10,"Tecla desconocida %s",nombre);
                  return(-1);
                }
               if (isdigit(nombre[3])) {
                  ret=S_F(0)+(nombre[2]-'0')*10+nombre[3]-'0';
                } else {
                  ret=S_F(0)+nombre[2]-'0';
                }
               break;
      case 'C':if (nombre[1]=='F') {
                  if (isdigit(nombre[3])) {
                     ret=C_F(0)+(nombre[2]-'0')*10+nombre[3]-'0';
                   } else {
                     ret=C_F(0)+nombre[2]-'0';
                   }
                } else {
                  ret=CTRL(nombre[2]);
                }
               break;
      case 'A':if (nombre[1]=='F') {
                  if (isdigit(nombre[3])) {
                     ret=A_F(0)+(nombre[2]-'0')*10+nombre[3]-'0';
                   } else {
                     ret=A_F(0)+nombre[2]-'0';
                   }
                } else {
                  ret=ALT(nombre[2]);
                }
               break;
      default: ret=atoi(nombre);
               break;
   }
  return(ret);
}
