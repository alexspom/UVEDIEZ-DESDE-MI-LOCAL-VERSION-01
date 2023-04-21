/*******************************************************************************
* Módulo : v10SATO.c                                                           *
* Función: Driver SATO no estándar para V10 de las etiquetadoras de ASENGA     *
*                                                                              *
* Autor  : ICC                                                                 *
* Revisado por:                                                                *
* Fecha  : 13-04-2010                                                          *
********************************************************************************
* Histórico de cambios
* ====================
*******************************************************************************/
#include "v10etiqueta.h"


#define CODESC  27
#define PPM      7.99212598
#define ITF       2   //Código de barras Interleaved 2 of 5
#define RATIO13   3   //Ratio 1:3
#define RATIO12   2   //Ratio 1:2
#define RATIO25   5   //Ratio 2:5
#define Code39    3   //Código de barras Code 39

#define TIMEOUTIMPRE 100
#define MAXSTATUS 30
#define STIMPIDDLE  0
#define STIMPENVEQ  1
static char buffer[MAXSTATUS],*ptr=buffer;
static int st=STIMPIDDLE;
static v10horas hstatus;


static void posicionasato(idrivers *id,char **ptrsal)
{
  int x,y,tx;
  int angulo;
  if (id->angulo<90) angulo=1;
     else if (id->angulo<180) angulo=0;
             else if (id->angulo<270) angulo=3;
                     else         angulo=2;
  x=(int) ((id->px*PPM+5)/10);
  y=(int) (((id->py+100)*PPM+5)/10);
  tx=(int) ((id->tx*PPM+5)/10);
  if (y<0) y=0;
  if (x<0) x=0;
  if (x>tx) x=tx;
  sprintf(*ptrsal,"%c%%%d%cH%04d%cV%04d",
                 CODESC,angulo,CODESC,y,CODESC,tx-x);
  *ptrsal+=strlen(*ptrsal);
}

static void imprimecadenasato(idrivers *id,char *cadena,char *fin,char *ptrsal)
{
  int px,py;
  if (id->angulo<90) {
     px=0;
     py=-1;
   } else {
     if (id->angulo<180) {
        px=-1;
        py=0;
      } else {
        if (id->angulo<270) {
           px=0;
           py=1;
         } else {
           px=1;
           py=0;
         }
      }
   }
  id->numcad++;
  id->px+=(px*(id->fy*70))/30;
  id->py+=(py*(id->fy*70))/30;
  posicionasato(id,&ptrsal);
  sprintf(ptrsal,"%c$B,%03d,%03d,0%c$=%-*.*s",
                 CODESC,id->fx*3,id->fy*3,CODESC,fin-cadena,fin-cadena,cadena);
  ptrsal+=strlen(ptrsal);
}
 
static void comprime128(char *origen,char *hasta,char *destino)
{
  char *ptr=origen,*prin=origen,*resultado=destino;
  int numdig=0;
  while (ptr<hasta) {
        if (isdigit(*ptr)) {
           if (numdig==0) {
              prin=ptr;
            }
           numdig++;
         } else {
           if (numdig) {
              if (numdig>3) {
                 if (numdig%2) {
                    ptr--;
                  }
                 if (prin==origen) {
                    *destino++='>';
                    *destino++='I';
                  } else {
                    *destino++='>';
                    *destino++='C';
                  }
               }
              while (prin<ptr) {
                    *destino++=*prin++;
               }
            }
           if (numdig>3) {
              *destino++='>';
              *destino++='E';
            }
           if (*ptr=='¿') {
              *destino++='>';
              *destino++='F';
            } else {
              *destino++=*ptr;
            }
           numdig=0;
           prin=ptr;
         }
        ptr++;
   }
  if (numdig>0) {
     if (numdig>3) {
        if (numdig%2) {
           *destino++=*prin++;
           *destino++='>';
           *destino++='C';
         } else {
           if (prin==origen) {
              *destino++='>';
              *destino++='I';
            } else {
             *destino++='>';
             *destino++='C';
            }
          }
      }
   } else prin=hasta;
  while (prin<hasta) {
           if (*prin=='¿') {
              *destino++='>';
              *destino++='F';
            } else {
              *destino++=*prin;
            }
        prin++;
   }
  *destino=0;
  if (strncmp(resultado,">F>C",4)==0) {
     resultado[1]='I';
     resultado[3]='F';
   }
}

static void imprimebarrassato(idrivers *id,char *cadena,char *fin,char **ptrsal)
{
  int ancho,alto;
  char destino[MAXCADENA];
  char comando[MAXCADENA];
  char *ptr;
  id->numcb++;
  posicionasato(id,ptrsal);

  ancho=(int) ((id->ancb*PPM)/100);
  alto=(int) ((id->alcb*PPM)/10);

//(1) Inicio
  switch (id->tipocb)
  {
     case ITF:
     {
        switch (id->ratiocb)
        {
           case RATIO13:
              strcpy(comando,"B2");
           break;

           case RATIO12:
              strcpy(comando,"D2");
           break;

           case RATIO25:
              strcpy(comando,"BD2");
           break;
        }

        ptr=cadena;
        while (ptr<fin)
        {
           ptr++;
        }
        *ptr='\0';

        sprintf(*ptrsal,"%c%-*.*s%02d%03d%-*.*s",
                        CODESC,strlen(comando),strlen(comando),comando,ancho,alto,strlen(cadena),strlen(cadena),cadena);
     }
     break;
//(1) Fin
//(2) Inicio
     case Code39:
     {
        switch (id->ratiocb)
        {
           case RATIO13:
              strcpy(comando,"B1");
           break;

           case RATIO12:
              strcpy(comando,"D1");
           break;

           case RATIO25:
              strcpy(comando,"BD1");
           break;
        }

        ptr=cadena;
        while (ptr<fin)
        {
           ptr++;
        }
        *ptr='\0';

        sprintf(*ptrsal,"%c%-*.*s%02d%03d%-*.*s",
                        CODESC,strlen(comando),strlen(comando),comando,ancho,alto,strlen(cadena),strlen(cadena),cadena);
     }
     break;
//(2) Fin
//(1) Inicio
     default:
     {
//(1) Fin
        comprime128(cadena,fin,destino);
        sprintf(*ptrsal,"%cBG%02d%03d%-*.*s",
                        CODESC,ancho,alto,strlen(destino),strlen(destino),destino);
//(1) Inicio
     }
  }
//(1) Fin

  *ptrsal+=strlen(*ptrsal);
}

//#pragma warn -par  ??????????
static void imprimelineasato(idrivers *id,char **ptrsal,int lx,int ly,int ancho,int tipo)
{
  int an,px,py;

  posicionasato(id,ptrsal);
  an=(int) ((ancho*PPM+5)/100);
  px=(int) ((lx*PPM+5)/10);
  py=(int) ((ly*PPM+5)/10);
  sprintf(*ptrsal,"%cFW%02d%02dV%03dH%03d",
                  CODESC,an,an,py,px);
  *ptrsal+=strlen(*ptrsal);
}

static void tiraetiqsato(idrivers *id,char **ptrsal)
{
  sprintf(*ptrsal,"\033Z\003");
  *ptrsal+=strlen(*ptrsal);
}

static void initetiqsato(idrivers *id,char **ptrsal)
{
  sprintf(*ptrsal,"\002\033A\033AX");
  *ptrsal+=strlen(*ptrsal);
}

// int  (*statusimpre)(struct IDRIVER *id,int PUERTO,tcpipetiq *tcpip); en V10
static int statussato(idrivers *id,int PUERTO,tcpipetiq *tcpip)
{
  switch (st) {
    case STIMPIDDLE:while (damecar232(PUERTO)!=-1);
                    STDencolach232(PUERTO,5);
                    ptr=buffer;
                    hstatus=damecent();
                    st=STIMPENVEQ;
                    break;
    case STIMPENVEQ:if (haycar232(PUERTO)) {
                      int ch;
                      ch=damecar232(PUERTO);
                      if (ptr-buffer>=MAXSTATUS) {
                         ptr=buffer;
                         st=STIMPIDDLE;
                         return(STTERMICAAPAGADA);
                       }
                      *ptr++=(char)ch;
                      if (ch==3) {
                         int status;
                         status=buffer[3];
                         st=STIMPIDDLE;
                         ptr=buffer;
                         switch (status) {                 
                             case 'a':return(STTERMICAABIERTA);
                             case 'b':return(STTERMICASINPAPEL);
                             case 'c':return(STTERMICASINCINTA);
                             case 'd':return(STTERMICAATASCO);
                             default:if (status!='A' && status!='G' && status!='M') return(1);
                                     break;
                          }
                         return(STTERMICAOK);
                       }
                    } else {
                      if (damecent()-hstatus>TIMEOUTIMPRE) {
                         st=STIMPIDDLE;
                         return(STTERMICAAPAGADA);
                       }
                    }
                   break;
	}
  return(STTERMICAENCURSO);
}
//void (*cancelatrabajo)(struct IDRIVER *id,int PUERTO,tcpipetiq *tcpip);
static void cancelatrabajosato(idrivers *id,int PUERTO,tcpipetiq *tcpip)
{
  printf232(PUERTO,"%c",0x18 );
}
//#pragma warn +par?????

void pondriversato(idrivers *id)
{
  id->imprimecadena=imprimecadenasato;
  id->imprimebarras=imprimebarrassato;
  id->imprimelinea=imprimelineasato;
  id->cancelatrabajo=cancelatrabajosato;
  id->tiraetiq=tiraetiqsato;
  id->cambiamaxetiq=NULL;
  id->initetiq=initetiqsato;
  id->statusimpre=statussato;
  id->repiteetiq=0;
}
