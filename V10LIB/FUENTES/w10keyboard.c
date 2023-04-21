/*
* Módulo : V10KEYBOARD.C
* Objeto:  Gestion del teclado
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"

#define MAXTECLAS 1024  /* Tama¤o del buffer de teclado */
#define MAX_ESPECIAL 10  /* M ximo n£mero de teclas a las que se puede
			    asignar una funci¢n especial. */
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
static int tope_tecla;  /* Indice del al £ltimo car cter del buffer */

static unsigned timeout = 0;
static void (*triger_timeout)(void) = NULL;
	 /* Si transcurre un tiempo "timeout" en centesimas de
	    segundo y no se pulsa ninguna tecla se ejecuta la
	    funci¢n "triger_timeout()". */

static void (*triger_iddle)(void) = NULL;
	 /* Funci¢n que se ejecuta siempre que se invoca una petici¢n
	    de tecla. */

static int numtriger; /* N£mero de teclas a las que se les ha asignado
			 un tratamiento especial. Se pueden definir
			 hasta MAX_ESPECIAL, de 0 al MAX_ESPECIAL-1. */

static mis_trigers triger[MAX_ESPECIAL];
	 /* Array con: el c¢digo de tecla asignado a cada funci¢n de
	    tratamiento especial, una bandera indicando si se est 
	    ejecutando la funci¢n especial asignada al c¢digo de tecla
	    (esto evita una posible recursi¢n) y un puntero a la funci¢n
	    que realiza la tarea especial. Esta funci¢n recibe como
	    par metro la tecla que la invoca y puede ser aprovechado o
	    no. */

static v10horas horatimeout;




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

void tratarestoteclas(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
  MSG msg;
  msg.hwnd=hwnd;
  msg.message=message;
  msg.wParam=wParam;
  msg.lParam=lParam;
  DispatchMessage(&msg);
}


static long tratawm_char(HWND hwnd,UINT key,int crepeat)
{
  int sh,ctr,alt;
  sh=GetAsyncKeyState(VK_SHIFT)&0x8000;
  ctr=GetAsyncKeyState(VK_CONTROL)&0x8000;
  alt=GetAsyncKeyState(VK_MENU)&0x8000;
  {char cad[2];
   *cad=(char)key;
   cad[1]=0;
   if (v10usaansi==0) v10ansitooem(cad,cad);
   key=*cad;
  }
  if (key==esc && (sh||ctr||alt)) {
     FORWARD_WM_CHAR(hwnd,key,crepeat,tratarestoteclas);
     return(0);
    }
  if (key==tab) {
     if (sh) key=stab;
     if (alt) {
        FORWARD_WM_CHAR(hwnd,key,crepeat,tratarestoteclas);
        return(0);
      }
  }
  if (key<256) {
      if (isalpha(key)) {
          if (ctr) key=toupper(key)-'A'+1;
          else  if (alt) key=alter[toupper(key)-'A'];
      } else {
          if (isdigit(key)) {
              if (alt) {
                  if (key=='0') key+=10;
                  key=ALTN(key-'0');
              }
          }
      }
  }
  STDencolatecla(key);
  return(1);
}

static long tratawm_keydown(HWND hwnd,UINT key,BOOL fdown,int crepeat,UINT flags)
{
   int func;
   int sh,ctr,alt;
   int encolar=0;
   sh=GetAsyncKeyState(VK_SHIFT)&0x8000;
   ctr=GetAsyncKeyState(VK_CONTROL)&0x8000;
   alt=GetAsyncKeyState(VK_MENU)&0x8000;
   if (key==esc && (sh||ctr||alt)) {
       FORWARD_WM_KEYDOWN(hwnd,key,crepeat,flags,tratarestoteclas);
       return(0);
     }
   if (key==tab) {
      if (key==tab && (ctr||alt)) {
          FORWARD_WM_SYSKEYDOWN(hwnd,key,crepeat,flags,tratarestoteclas);
          return(0);
        }
     }
   func=(unsigned)(flags&0x0100L);
   if (key>=VK_F1 && key<=VK_F12) {
       key=key-VK_F1+F(1);
       if (sh) {
           if (ctr) key=key-F(1)+CS_F(1);
           else     key=key-F(1)+S_F(1);
       } else {
           if (ctr) key=key-F(1)+C_F(1);
           else  if (alt) key=key-F(1)+A_F(1);
       }
      encolar=1;
    }
   if (func && key!=VK_DIVIDE && key!=VK_CONTROL && key!=VK_MENU && key!=VK_DELETE &&
       key!=VK_INSERT && key!=VK_LEFT && key!=VK_RIGHT && key!=VK_PRIOR && key!=VK_NEXT && key!=VK_HOME &&
       key!=VK_END && key!=VK_UP && key!=VK_DOWN && key!=VK_APPS) {
      key=(unsigned)(flags)&0xff;
      if (key!=28) {
         key+=256;
         encolar=1;
       }
    }
   switch (key) {
          case VK_PRIOR: if (sh) key=spgup;
                            else if (ctr) key=cpgup;
                                    else  key=pgup;
                         encolar=1;
                         break;
          case VK_NEXT:  if (sh) key=spgdn;
                            else if (ctr) key=cpgdn;
                                    else  key=pgdn;
                         encolar=1;
                         break;
          case VK_INSERT:if (sh) key=sinse;
                            else if (ctr) key=cinse;
                                    else  key=inse;
                         encolar=1;
                         break;
          case VK_DELETE:if (sh) key=sdele;
                            else if (ctr) key=cdele;
                                    else  key=dele;
                         encolar=1;
                         break;
          case VK_APPS:if (ctr) key=CS_F(10);
                       else     key=S_F(10);
                          encolar=1;
                          break;
          case VK_END:   if (sh) key=shend;
                            else if (ctr) key=cend;
                                    else  key=end;
                         encolar=1;
                         break;
          case VK_HOME:  if (sh) key=shome;
                            else if (ctr) key=chome;
                                    else  key=home;
                         encolar=1;
                         break;
          case VK_LEFT:if (sh) key=scui;
                            else if (ctr) key=ccui;
                                    else  key=cui; 
                         encolar=1;
                       break;
          case VK_UP:  if (sh) key=scuu;
                            else if (ctr) key=ccuu;
                                    else  key=cuu;
                       encolar=1;
                       break;
          case VK_RIGHT:if (sh) key=scud;
                            else if (ctr) key=ccud;
                                    else  key=cud;
                         encolar=1;
                         break;
          case VK_DOWN:if (sh) key=scua;
                            else if (ctr) key=ccua;
                                    else  key=cua;
                         encolar=1;
                         break;
      }
   if (encolar) STDencolatecla(key);
   return(1);
}

static long traduceteclado(HWND hwnd,UINT message,WPARAM wParam,
							LPARAM lParam)
{
  switch (message) {
      HANDLE_MSG(hwnd,WM_CHAR,tratawm_char);
      HANDLE_MSG(hwnd,WM_SYSCHAR,tratawm_char);
      HANDLE_MSG(hwnd,WM_SYSKEYDOWN,tratawm_keydown);
      HANDLE_MSG(hwnd,WM_KEYDOWN,tratawm_keydown);
    }
  return(1);
}

static int tratamensajes(HWND hwnd,int first,int last)
{
  MSG msg;
  while (PeekMessage(&msg,hwnd,first,last,PM_REMOVE)!=0) {
        if (msg.message==WM_QUIT) {
           exit((int)msg.wParam);
         }
        TranslateMessage(&msg);
        if (traduceteclado(msg.hwnd,msg.message,msg.wParam,msg.lParam)!=0) DispatchMessage(&msg);
           else 			v10limpiatooltip(hwnddefecto);

    }
  return(0);
}

int esperamensaje(int espera)
{
  MSG msg;
  UINT_PTR mitimer;

  mitimer=SetTimer(NULL,1,espera,NULL);
  if (mitimer) {
     GetMessage(&msg,NULL,0,0);
     KillTimer(NULL,mitimer);
   } else {
     return(0);
   }
  if (msg.message==WM_QUIT) {
     exit((int)msg.wParam);
   }
  TranslateMessage(&msg);
  if (traduceteclado(msg.hwnd,msg.message,msg.wParam,msg.lParam)!=0) DispatchMessage(&msg);
  return(0);
}


static int mibioskey(void)
{
  tratamensajes(NULL,0,0);
  if (tope_tecla) return(pila_teclas[tope_tecla-1]);
  return(0);
}

static int bioskey(int a)
{
  while (mibioskey()==0);
  return(pila_teclas[--tope_tecla]);
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

  ch=mibioskey();
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
          else bioskey(0);
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
  unsigned ch;
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
            if (ch!=CTRL_BREAK) {
               ch=bioskey(0);
             } else bioskey(0);
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
  if (strcmp(nombre,"TECLATIMEOUT")==0) return(TECLATIMEOUT);
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
