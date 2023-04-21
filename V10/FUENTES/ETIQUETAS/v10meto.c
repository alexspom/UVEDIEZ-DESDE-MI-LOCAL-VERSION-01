/*******************************************************************************
* Módulo : v10METO.c                                                           *
* Función: Driver METO para V10 de las etiquetadoras de ROCHE                  *
*                                                                              *
* Autor  : Varios (JCSR)                                                                 *
* Revisado por:                                                                *
* Fecha  : 13-09-2011                                                          *
********************************************************************************
* Histórico de cambios
* ====================
*******************************************************************************/

#include "v10etiqueta.h"

//(1)
#define ITF 2 //Código de barras Interleaved 2 of 5
//(1)
//(2)
#define Code39Std  3
#define Code39Full 4
//(2)

typedef struct {
          int  font;
          int  fx;
          int  bold;
          char ch;
        } metofonts;
static metofonts mt[]={{0,12,0,'A'},
                {1,15,0,'B'},
                {2,15,7,'C'},
                {3,18,7,'D'},
                {4,21,7,'E'},
                {5, 9,0,'G'},
                {6,15,0,'H'},
                {7,18,0,'I'},
                {8,18,7,'J'},
                {9,21,0,'K'},
                {10,27,7,'M'},
                {11,14,0,'N'},
                {12,10,0,'O'},
                {13,15,7,'P'},
                {14,15,0,'Q'},
                {15,18,7,'R'}};

static void buscamejorfont(idrivers *id,int *font,int *fx,int *fy)
{
  int i,posible=-1;
  for (i=0;i<sizeof(mt)/sizeof(mt[0]);i++) {
      if (mt[i].font==id->font) {
         if (posible==-1) {
            posible=i;
          } else {
            if (mt[i].fx<id->fx && mt[i].fx<id->fy) posible=i;
          }
       }
   }
  if (posible==-1) posible=0;
  *font=mt[posible].ch;
  *fx=((id->fx*10)/mt[posible].fx)/5*5;
  if (*fx==0) *fx=5;
  *fy=((id->fy*10)/mt[posible].fx)/5*5;
  if (*fy==0) *fy=5;
}

static void imprimecadenameto(idrivers *id,char *cadena,char *fin,char *ptrsal)
{
  int  angulo;
  int font,fx,fy;
  char *ptr;

  if (id->angulo<90) angulo=0;
     else if (id->angulo<180) angulo=11;
//(5i)      else if (angulo<270) angulo=22;
            else if (id->angulo<270) angulo=22;
//(5f)
                     else         angulo=33;
  id->numcad++;
  buscamejorfont(id,&font,&fx,&fy);
  sprintf(ptrsal,"<[Ff \"%04d:%04d\" \"%03d\" \"%02d\" \"%c:B\" \"%02d:%02d\"]>\n",
                 id->px,id->py,id->numcad,angulo,font,fx,fy);
  ptrsal+=strlen(ptrsal);

  ptr=strchr(cadena,'"');
  while (ptr!=NULL) {
        *ptr='\'';
        ptr=strchr(ptr+1,'"');
   }
  ptr=strchr(cadena,'$');
  while (ptr!=NULL && ptr<fin) {
        *ptr='/';
        ptr=strchr(ptr+1,'$');
   }
  sprintf(ptrsal,"<[Df \"%03d\" \"%-*.*s\"]>\n",
                 id->numcad,fin-cadena,fin-cadena,cadena);
}

static void imprimebarrasmeto(idrivers *id,char *cadena,char *fin,char **ptrsal)
{
  int  angulo;
  int  ancho;
//(1) Inicio
  int anchogrande;
//(1) Fin
  char destino[MAXCADENA];
  char *ptr=cadena,*ptr1=destino;
  if (id->angulo<90) angulo=0;
     else if (id->angulo<180) angulo=1;
             else if (id->angulo<270) angulo=2;
                     else         angulo=3;
  while (ptr<fin) {
        if (*ptr=='¿') {
           *ptr1++='>';
           *ptr1++='8';
           ptr++;
         } else *ptr1++=*ptr++;
    }
  id->numcb++;
  ancho=(id->ancb*10)/110;
  anchogrande=ancho*id->ratiocb; //(1)

//(1) Inicio
  switch (id->tipocb)
  {
     case ITF:
     {
        sprintf(*ptrsal,"<[Fb \"%04d:%04d\" \"%02d\" \"%d\" \"%d:1\" \"%04d\" \"%02d:%02d:%02d:%02d:00\"]>\n",
                        id->px,id->py,id->numcb,angulo,id->tipocb,id->alcb,ancho,ancho,anchogrande,anchogrande);
     }
     break;
//(1) Fin
//(2) Inicio
     case Code39Std:
     {
        sprintf(*ptrsal,"<[Fb \"%04d:%04d\" \"%02d\" \"%d\" \"3:1\" \"%04d\" \"%02d:%02d:%02d:%02d:02\"]>\n",
                        id->px,id->py,id->numcb,angulo,id->alcb,ancho,ancho,anchogrande,anchogrande);
     }
     break;

     case Code39Full:
     {
        sprintf(*ptrsal,"<[Fb \"%04d:%04d\" \"%02d\" \"%d\" \"B:1\" \"%04d\" \"%02d:%02d:%02d:%02d:02\"]>\n",
                        id->px,id->py,id->numcb,angulo,id->alcb,ancho,ancho,anchogrande,anchogrande);
     }
     break;
//(2) Fin
//(1) Inicio
     default:
     {
//(1) Fin
        sprintf(*ptrsal,"<[Fb \"%04d:%04d\" \"%02d\" \"%d\" \"%d:1:0\" \"%04d\" \"%02d\"]>\n",
                        id->px,id->py,id->numcb,angulo,9,id->alcb,ancho);
//(1) Inicio
     }
  }
//(1) Fin

  *ptrsal+=strlen(*ptrsal);
  sprintf(*ptrsal,"<[Db \"%02d\" \"%-*.*s\"]>\n",
                 id->numcb,ptr1-destino,ptr1-destino,destino);
  *ptrsal+=strlen(*ptrsal);
}

static void imprimelineameto(idrivers *id,char **ptrsal,int lx,int ly,int ancho,int tipo)
{
  sprintf(*ptrsal,"<[Fl \"%04d:%04d\" \"%04d:%04d\" \"%d:%d\"]>\n",
                  id->px,id->py,id->px+lx,id->py+ly,tipo,ancho);
  *ptrsal+=strlen(*ptrsal);
}


//#pragma warn -par
static void tiraetiqmeto(idrivers *id,char **ptrsal)
{
//(3)  sprintf(*ptrsal,"<[Pi \"0001\" \"000\" \"2:C:A:1:0\" \"0\"]>");
/*(3) I*/       // PARA LABELING AUMENTO VELOCIDAD. CUIDADO AL RECOMPILAR CONTROL, PONER A 6

  sprintf(*ptrsal,"<[Pf \"2:0:C:A:1\"]>");
  sprintf(*ptrsal,"<[Pi \"0001\" \"000\" \"2:C:A:1:0\" \"0\"]>");
/*(3) F*/
  *ptrsal+=strlen(*ptrsal);
}

static void initetiqmeto(idrivers *id,char **ptrsal)
{
  sprintf(*ptrsal,"<[Cc]>");
  *ptrsal+=strlen(*ptrsal);
}
//#pragma warn +par

//(4i)

#define MAXSTMETO 8
#define TMAXST 	100
static char buffer[MAXSTMETO]="",*ptr;
static v10horas hstatus=0;
static int st=0;
#define STIMPIDDLE 	0
#define STIMPINICIO 	1
#define STIMPDATA 	2

static int statusmeto(idrivers *id,int PUERTO,tcpipetiq *tcpip) {
  int aux;
  // return(STTERMICAOK);
  switch (st) {

    case STIMPIDDLE:while (damecar232(PUERTO)!=-1);
                    printf232(PUERTO,"<[Ws]>");
                    ptr=buffer;
                    hstatus=damecent();
                    st=STIMPINICIO;
                    break;

    case STIMPINICIO:if (haycar232(PUERTO)) {
                      int ch;
                      ch=damecar232(PUERTO);
                      aux=ch; 
                      if (ch!='{') {
                         ptr=buffer;
                         st=STIMPIDDLE;
                      } else {
                       hstatus=damecent();
                       ptr=buffer;
                       st=STIMPDATA;
                      }
                    } else {    
                       if (damecent()-hstatus>TMAXST) {
                         ptr=buffer;
                         st=STIMPIDDLE;
                         return(STTERMICAAPAGADA);
                       }
                    }
                    break;

    case STIMPDATA: if (haycar232(PUERTO)) {
                      int ch;
                      ch=damecar232(PUERTO);
                      if (ch!='}') {
                        if (ptr-buffer>=MAXSTMETO) {
                          ptr=buffer;
                          st=STIMPIDDLE;
                        } else {
                         *ptr=(char)ch;
                         ptr++;
                        }
                      } else {
                        if (buffer[2]=='0') {
                          st=STIMPIDDLE;
                          break;
                        }
                        if (buffer[0]=='0' && buffer[1]=='1') return(STTERMICAABIERTA);
                        if (buffer[0]=='0' && buffer[1]=='2') return(STTERMICACARGADA);
                        if (buffer[0]=='0' && buffer[1]=='4') return(STTERMICAPAUSA);
                        if (buffer[0]=='0' && buffer[1]=='5') return(STTERMICACARGADA);
                        if (buffer[0]=='0' && buffer[1]=='6') return(STTERMICAHARD);
                        if (buffer[0]=='0' && buffer[1]=='7') return(STTERMICAHARD);
                        if (buffer[0]=='1' && buffer[1]=='1') return(STTERMICAATASCO);
                        if (buffer[0]=='1' && buffer[1]=='2') return(STTERMICAHARD);
                        if (buffer[0]=='1' && buffer[1]=='3') return(STTERMICASINPAPEL);
                        if (buffer[0]=='1' && buffer[1]=='4') return(STTERMICASINCINTA);
                        if (buffer[0]=='1' && buffer[1]=='5') return(STTERMICAABIERTA);
                        if (buffer[0]=='1' && buffer[1]=='8') return(STTERMICAHARD);
                        if (buffer[0]=='2' && buffer[1]=='1') return(STTERMICASINCINTA);
                        if (buffer[0]=='0' && buffer[1]=='0') return(STTERMICAOK);
                      }
                    } else {
                        if (damecent()-hstatus>TMAXST) {
                         ptr=buffer;
                         st=STIMPIDDLE;
                         return(STTERMICAAPAGADA);
                        }
                    }
                   break;
	}
  return(STTERMICAENCURSO);
}


void pondrivermeto(idrivers *id)
{
  id->imprimecadena=imprimecadenameto;
  id->imprimebarras=imprimebarrasmeto;
  id->imprimelinea=imprimelineameto;
  id->cambiamaxetiq=NULL;
  id->tiraetiq=tiraetiqmeto;
  id->initetiq=initetiqmeto;
  id->statusimpre=statusmeto;
  id->repiteetiq=0;
}
