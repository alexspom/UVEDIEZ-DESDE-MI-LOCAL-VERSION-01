/*******************************************************************************
* M�dulo : IPETIQMARKPOINT.C												   *
* Autor driver original: ECF	                                               *
* Funci�n: Adaptaci�n de driver SGL a IP6.                                     *
*          M�dulo con driver para impresora Markpoint.                         *
*		                                                                       
*                                                                              *
* Autor	 : Ricardo Fern�ndez                                             	   *
********************************************************************************
* Hist�rico de cambios
* ====================
*******************************************************************************/

#include "v10etiqueta.h"

#define CODESC  27
                              // offsets automatico que mete la etiquetadora en la area util
#define OFFSETDERECHA  60
#define OFFSETABAJO    60

double multfontx = 1;
double multfonty = 0.9;

//      |           |<----->|
//      |           |  60   |
//      |           |       |
//      |           |       |
//      |           |       |
//      |-----------|-------|
//      |      60   |       |
//      |           |       |
//      |-----------|-------|






#define PPM1       7.99212598  // 203 punts/pulsada x 1pulsada/25'4 mm = 7,9921259842519685039370078740157
//#define PPM2      11.81102362  // 300 punts/pulsada x 1pulsada/25'4 mm = 11,811023622047244094488188976378
#define PPM2      12  // 300 punts/pulsada x 1pulsada/25'4 mm = 11,811023622047244094488188976378

// Tipograf�a permitida en la Markpoint.
#define CGTIMES                 1
#define UNIVERS                 2
#define ARIAL                   3
#define TIMESNEWROMAN           4
#define UNIVERSCONDENSEDMEDIUM  5
#define CORONET                 6
#define TIMESNEW                7

typedef struct {          // estructura para las fuentes Markpoint.
          int  font;
          int  fx;
          int  bold;
          int ch;
        } mpfonts;

static mpfonts mt[]={     // definici�n de las fuentes de Markpoint.
                {CGTIMES,8,0,92500},{CGTIMES,9,0,92500},{CGTIMES,10,0,92500},{CGTIMES,11,0,92500},{CGTIMES,12,0,92500},{CGTIMES,13,0,92500},
                {CGTIMES,14,0,92500},{CGTIMES,15,0,92500},{CGTIMES,16,0,92500},{CGTIMES,17,0,92500},{CGTIMES,18,0,92500},{CGTIMES,19,0,92500},
                {CGTIMES,20,0,92500},{CGTIMES,21,0,92500},{CGTIMES,22,0,92500},{CGTIMES,23,0,92500},{CGTIMES,24,0,92500},{CGTIMES,25,0,92500},
                {CGTIMES,26,0,92500},{CGTIMES,27,0,92500},
                {CGTIMES,8,7,92504},{CGTIMES,9,7,92504},{CGTIMES,10,7,92504},{CGTIMES,11,7,92504},{CGTIMES,12,7,92504},{CGTIMES,13,7,92504},
                {CGTIMES,14,7,92504},{CGTIMES,15,7,92504},{CGTIMES,16,7,92504},{CGTIMES,17,7,92504},{CGTIMES,18,7,92504},{CGTIMES,19,7,92504},
                {CGTIMES,20,7,92504},{CGTIMES,21,7,92504},{CGTIMES,22,7,92504},{CGTIMES,23,7,92504},{CGTIMES,24,7,92504},{CGTIMES,25,7,92504},
                {CGTIMES,26,7,92504},{CGTIMES,27,7,92504},
                {UNIVERS,8,7,94023},{UNIVERS,9,7,94023},{UNIVERS,10,7,94023},{UNIVERS,11,7,94023},{UNIVERS,12,7,94023},{UNIVERS,13,7,94023},
                {UNIVERS,14,7,94023},{UNIVERS,15,7,94023},{UNIVERS,16,7,94023},{UNIVERS,17,7,94023},{UNIVERS,18,7,94023},{UNIVERS,19,7,94023},
                {UNIVERS,20,7,94023},{UNIVERS,21,7,94023},{UNIVERS,22,7,94023},{UNIVERS,23,7,94023},{UNIVERS,24,7,94023},{UNIVERS,25,7,94023},
                {UNIVERS,26,7,94023},{UNIVERS,27,7,94023},

                {ARIAL,8,0,24459},{ARIAL,9,0,24459},{ARIAL,10,0,24459},{ARIAL,11,0,24459},{ARIAL,12,0,24459},{ARIAL,13,0,24459},
                {ARIAL,14,0,24459},{ARIAL,15,0,24459},{ARIAL,16,0,24459},{ARIAL,17,0,24459},{ARIAL,18,0,24459},{ARIAL,19,0,24459},
                {ARIAL,20,0,24459},{ARIAL,21,0,24459},{ARIAL,22,0,24459},{ARIAL,23,0,24459},{ARIAL,24,0,24459},{ARIAL,25,0,24459},
                {ARIAL,26,0,24459},{ARIAL,27,0,24459},
                {ARIAL,8,7,24461},{ARIAL,9,7,24461},{ARIAL,10,7,24461},{ARIAL,11,7,24461},{ARIAL,12,7,24461},{ARIAL,13,7,24461},
                {ARIAL,14,7,24461},{ARIAL,15,7,24461},{ARIAL,16,7,24461},{ARIAL,17,7,24461},{ARIAL,18,7,24461},{ARIAL,19,7,24461},
                {ARIAL,20,7,24461},{ARIAL,21,7,24461},{ARIAL,22,7,24461},{ARIAL,23,7,24461},{ARIAL,24,7,24461},{ARIAL,25,7,24461},
                {ARIAL,26,7,24461},{ARIAL,27,7,24461},
                {TIMESNEW,8,0,24455},{TIMESNEW,9,0,24455},{TIMESNEW,10,0,24455},{TIMESNEW,11,0,24455},{TIMESNEW,12,0,24455},{TIMESNEW,13,0,24455},
                {TIMESNEW,14,0,24455},{TIMESNEW,15,0,24455},{TIMESNEW,16,0,24455},{TIMESNEW,17,0,24455},{TIMESNEW,18,0,24455},{TIMESNEW,19,0,24455},
                {TIMESNEW,20,0,24455},{TIMESNEW,21,0,24455},{TIMESNEW,22,0,24455},{TIMESNEW,23,0,24455},{TIMESNEW,24,0,24455},{TIMESNEW,25,0,24455},
                {TIMESNEW,26,0,24455},{TIMESNEW,27,0,24455},
                {TIMESNEW,8,7,24457},{TIMESNEW,9,7,24457},{TIMESNEW,10,7,24457},{TIMESNEW,11,7,24457},{TIMESNEW,12,7,24457},{TIMESNEW,13,7,24457},
                {TIMESNEW,14,7,24457},{TIMESNEW,15,7,24457},{TIMESNEW,16,7,24457},{TIMESNEW,17,7,24457},{TIMESNEW,18,7,24457},{TIMESNEW,19,7,24457},
                {TIMESNEW,20,7,24457},{TIMESNEW,21,7,24457},{TIMESNEW,22,7,24457},{TIMESNEW,23,7,24457},{TIMESNEW,24,7,24457},{TIMESNEW,25,7,24457},
                {TIMESNEW,26,7,24457},{TIMESNEW,27,7,24457}};

// Estados posibles del algoritmo de control de estado de la Markpoint.
#define TIMEOUTIMPRE 100
#define TOKENSTATUS1 1   // petici�n estado 1
#define TOKENSTATUS2 2   // petici�n estado 2
#define TOKENSTATUS3 3   // petici�n estado 3
#define TOKENSTATUS4 4   // petici�n estado 4

#define RESPSTATUS1 10  // respuesta de estado 1
#define RESPSTATUS2 20  // respuesta de estado 2
#define RESPSTATUS3 30  // respuesta de estado 3
#define RESPSTATUS4 40  // respuesta de estado 4

#define CR          13  /* Retorno de carro */
// c�digos de Error de las tramas de respuesta de la etiquetadora Markpoint.
#define STOUTOFPAPER  10      // out of paper
#define STLABELNOTRE  20      // label not removed
#define STPRINTREEST  30      // printer restarted
#define STNOPAPERSEN  40      // no paper in paper sensor
#define STHEAPERROR   50      // Heap Error.
#define STSTOPLABEL   60      // stopped on a label gap
#define STPRINTINCOM  70      // print incomplete
#define STLASTPAPERM  80      // last paper movement type
#define STPARAMERROR  90       // operating parameters error
#define STBUTTONACTI 100      // internal print button active
#define STLABELSTOCK 110      // label stock
#define STHEADLIFTED 120      // head Lifted.
//#define STTERMICAENCURSO 200  // OK.
#define MAXSTATUS 9  // N�mero m�ximo de caracteres de la trama devuelta por la etiquetadora.

static char buffer[MAXSTATUS],*ptr=buffer;
static int st=TOKENSTATUS1;
static v10horas hstatus;
static char *angulo;
//static anchoet = 1150;
static int anchoet = 1050;

#define TIMEOUTIMPRE 100
//#define MAXSTATUS 30
#define STIMPIDDLE  0
#define STIMPENVEQ  1
//static int st=STIMPIDDLE;
// Funci�n que nos busca la Fuente que se adapta mejor seg�n el fichero de definici�n
// SGLESPA.GEN...
static void buscamejorfontmarkpoint(idrivers *id,int *font,int *fx,int *fy)
{
  int i,posible=-1;
  int tam = (int)(*fx / 8.0) * 12;
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
  *fy=((id->fy*10)/mt[posible].fx)/5*5;
}

static void imprimecadenamarkpoint(idrivers *id, char *cadena, char *fin, char *ptrsal)
{
    int x = 0;
    int font, tx, ty;
    // ratio es el % de anchura que lo establecemos a trav�s de la anchura que le imputamos al texto.
    // este ratio se aplica para que salga el texto lo m�s aproximado al driver de la sato.
    char angulo[2];
    int baseline, position;
    if (id->angulo == 90) {
        strcpy(angulo, "S");    // humano sglgespa.gen
        //baseline = id->px;
        //position = id->py;
		baseline = id->py;
		position = id->px;
    } else {
        if (id->angulo == 180) {
            strcpy(angulo, "W");
            baseline = id->py;
            position = id->px;
        } else {
            if (id->angulo == 270) {
                strcpy(angulo, "N");
                //baseline = id->px;
                //position = id->py;
				baseline = id->py;
				position = id->px;
            } else {                   // todo de sglespa.gen
                strcpy(angulo, "E");
                baseline = id->py;
                position = id->px;
            }
        }
    }

    tx = id->tx;
    ty = anchoet;
    //position=position-OFFSETDERECHA;
    //baseline=baseline-OFFSETABAJO;
    if (position < 0) position = 0;
    if (baseline < 0) baseline = 0;
    if (x > tx) x = tx;
	if (id->fx>10) font = 24461; else font = 24459;
    if ((*angulo == 'E') || (*angulo == 'W')) {
        sprintf(ptrsal, "!F S %c %d %d L %d %d %d \"%-*.*s\"\n",
        *angulo, ty-baseline, position, (int)(id->fx*multfontx), (int)(id->fy*multfonty), font, fin - cadena, fin - cadena, cadena);
    } else {
        sprintf(ptrsal, "!F S %c %d %d L %d %d %d \"%-*.*s\"\n",
			*angulo, position, ty - baseline, (int)(id->fy*multfonty), (int)(id->fx*multfontx), font, fin - cadena, fin - cadena, cadena);
    }
    ptrsal += strlen(ptrsal);
}

//////////////////////////////////////////////////////////////////////////////////////////////
static void imprimelineamarkpoint(idrivers *id,char **ptrsal,int lx,int ly,int ancho,int tipo)
{
  int baseline,position;
  //int x;
  int tx, ty;
  //char angulo[2];

    /*if (id->angulo==90){
         strcpy(angulo,"S");
		 baseline=id->py;
		 position=id->px;
    } else {
       if (id->angulo==180){
           strcpy(angulo,"W");
           baseline=id->py;
           position=id->px;
       }else{
           if (id->angulo==270){
               strcpy(angulo,"N");
			   baseline = id->py;
			   position = id->px;
           } else{
               strcpy(angulo,"E");
               baseline=id->py;
               position=id->px;
           }
       }
  }*/
  baseline = id->py;
  position = id->px;

  tx=id->tx;
  ty=anchoet;

  if (tipo == 2) //con el ancho de l�nea a 0 se pinta un rect�ngulo s�lido
	  ancho = 0;

  //sprintf(*ptrsal, "!/ anchoet: %d id->px: %d id->py: %d\n", anchoet, id->px, id->py);
  //*ptrsal += strlen(*ptrsal);

  if (ty - baseline < 0) {
	  baseline = 0;
	  ty=0;
  }
  if (position<0) position=0;
  //if (x>tx) x=tx;

  sprintf(*ptrsal, "!F B N %d %d L %d %d %d\n", position, ty - baseline, lx, ly, ancho / 10);

	//sprintf(*ptrsal, "!F B %c %d %d L %d %d %d\n", *angulo, ty-baseline, (tx - position), ly, lx, ancho / 10);
	//if ((*angulo == 'E') || (*angulo == 'W'))
	  //sprintf(*ptrsal, "!F B %c %d %d L %d %d %d\n", *angulo, position, ty - baseline, lx, ly, ancho / 10);
	//else
	  //sprintf(*ptrsal, "!F B %c %d %d L %d %d %d\n", *angulo, position, ty - baseline, lx, ly, ancho / 10);


*ptrsal+=strlen(*ptrsal);

}
//////////////////////////////////////////////////////////////////////////////////////////

//static  char destino[MAXCADENA];

static int buscaean128(char *origen,char *hasta,char *destino) {

  int ean=0;
  if (*origen=='�'){ 
	  origen++;
	  ean=1;
  }
  while (origen<hasta) {
           if (*origen=='�') {
              *destino++='?';
			  *destino++='?';
			  *destino++='1';
            } else {
              *destino++=*origen;
            }
        origen++;
   }
  *destino = 0;
 return(ean);
}
 
static void imprimebarrasmarkpoint(idrivers *id,char *cadena,char *fin,char **ptrsal)
{
  char angulo[2];
  int baseline,position;
  int ancho,alto;
  int tipocb;
  char destino[MAXCADENA]="";	

  if (id->angulo==90){
         strcpy(angulo,"S");
   } else {
       if (id->angulo==180){
           strcpy(angulo,"W");
       }else{
           if (id->angulo==270){
               strcpy(angulo,"N");
           } else{
               strcpy(angulo,"E");
           }
       }
  }

  baseline=id->py;
  position=id->px;

  //0.73913043478260 = 170/230 factor de conversi� de notaci� SGL a driver Markpoint
  ancho=(int)((id->ancb)*PPM1/100);
  alto=(int)(id->alcb*PPM1/10+50);

   //� EAN 128
  memset(destino, 0, sizeof(destino));
  memcpy(destino, cadena, fin - cadena);
  switch (id->tipocb) {
	case CODE128:
	  if (buscaean128(cadena,fin,destino)==1)     tipocb=43;  // EAN 128
	  else tipocb=41;  // CODE128
	  break;
	case EAN13:
		tipocb = 32;
		break;
	case INTER25:
		tipocb = 1;
		break;
	case TCODABAR:
		tipocb = 21;
		break;	//(1) I
  }		//(1) F
  
  if (id->tipocb==2) id->tipocb=id->ratiocb;  // entrelazado 2 de 5 // (1)	I

 
  sprintf(*ptrsal,"!Y42 0\n");  // Resetea el c�digo Humano que implicitamente sale por defecto en el c�digo de barras.
  *ptrsal += strlen(*ptrsal);
  if ((*angulo == 'E') || (*angulo == 'W')) {
      sprintf(*ptrsal, "!F C %c %d %d L %ld %ld %d \"%-*.*s\"\n",
              *angulo, anchoet - baseline, position, alto, ancho, tipocb, strlen(destino), strlen(destino), destino);
  } else {
      sprintf(*ptrsal, "!F C %c %d %d L %ld %ld %d \"%-*.*s\"\n",
              *angulo, position,anchoet - baseline, alto, ancho, tipocb, strlen(destino), strlen(destino), destino);
  }
  *ptrsal+=strlen(*ptrsal);
 
}

//////////////////////////////////////////////////////////////////////////////////////////
static int statusmarkpoint(idrivers *id,int PUERTO)
{
  switch (st) {
      case TOKENSTATUS1:   while (damecar232(PUERTO) != -1);
                    encolaecad232(PUERTO,"!S1\n");
                    ptr=buffer;
                    hstatus=damecent();
                    st=RESPSTATUS1;
                    break;
    case RESPSTATUS1:if (haycar232(PUERTO)) {      // SI HAY CAR�CTER.
                         int ch;
                         ch=damecar232(PUERTO);
                         if (ptr-buffer>=MAXSTATUS) {
                             ptr=buffer;
                             st=TOKENSTATUS1;
                             return(STTERMICAAPAGADA);
                         }
                         *ptr++=(char)ch;
                         if (ch==10 || ch==48) {
                             if (buffer[0]=='1') return(STOUTOFPAPER);    // out of paper
                             if (buffer[1]=='1') return(STLABELNOTRE);    // label not removed
                             if (buffer[2]=='1') return(STPRINTREEST);    // printer restarted
                             if (buffer[3]=='1') return(STNOPAPERSEN);    // no paper in paper sensor
                             if (buffer[7]=='1') return(STHEAPERROR);    // Heap Error.
                             strcpy(buffer,"00000000");
                             st=TOKENSTATUS2;
                             break;
                         }
                     } else {                  // SI NO HAY CAR�CTER.
                         if (damecent()-hstatus>TIMEOUTIMPRE) {
                             st=TOKENSTATUS1;
                             return(STTERMICAAPAGADA);
                         }
                     }
                     break;
    case TOKENSTATUS2:   while (damecar232(PUERTO)!=-1);
                    encolaecad232(PUERTO,"!S2\n");
                    ptr=buffer;
                    hstatus=damecent();
                    st=RESPSTATUS2;
                    break;
    case RESPSTATUS2:if (haycar232(PUERTO)) {      // SI HAY CAR�CTER.
                         int ch;
                         ch=damecar232(PUERTO);
                         if (ptr-buffer>=MAXSTATUS) {
                             ptr=buffer;
                             st=TOKENSTATUS1;
                             return(STTERMICAAPAGADA);
                         }
                         *ptr++=(char)ch;
                         if (ch==10 || ch==48) {
                             //int status;
//                             if (buffer[0]=='1') return(STSTOPLABEL);    // stopped on a label gap
//                             if (buffer[1]=='1') return(STPRINTINCOM);    // print incomplete
//                             if (buffer[4]=='1') return(STLASTPAPERM);    // last paper movement type
                             st=TOKENSTATUS3;
                             strcpy(buffer,"00000000");
                             break;
                         }
                     } else {                  // SI NO HAY CAR�CTER.
                         if (damecent()-hstatus>TIMEOUTIMPRE) {
                             st=TOKENSTATUS1;
                             return(STTERMICAAPAGADA);
                         }
                     }
                     break;
   case TOKENSTATUS3:   while (damecar232(PUERTO)!=-1);
                    encolaecad232(PUERTO,"!S3\n");
                    ptr=buffer;
                    hstatus=damecent();
                    st=RESPSTATUS3;
                    break;
    case RESPSTATUS3:if (haycar232(PUERTO)) {      // SI HAY CAR�CTER.
                         int ch;
                         ch=damecar232(PUERTO);
                         if (ptr-buffer>=MAXSTATUS) {
                             ptr=buffer;
                             st=TOKENSTATUS1;
                             return(STTERMICAAPAGADA);
                         }
                         *ptr++=(char)ch;
                         if (ch==10 || ch==48) {        // si ya tenemos toda la trama.
                             if (buffer[2]=='1') return(STPARAMERROR);    // operating parameters error
                             if (buffer[4]=='1') return(STBUTTONACTI);    // internal print button active
                             // if (buffer[6]=='1') return(STLABELSTOCK);    // label stock SWITCH INTERNO DE LA ETIQUETADORA.
                             st=TOKENSTATUS4;
                             strcpy(buffer,"00000000");
                             break;
                         }
                     } else {                  // SI NO HAY CAR�CTER.
                         if (damecent()-hstatus>TIMEOUTIMPRE) {
                             st=TOKENSTATUS1;
                             return(STTERMICAAPAGADA);
                         }
                     }
                     break;
    case TOKENSTATUS4:   while (damecar232(PUERTO)!=-1);
                    encolaecad232(PUERTO,"!S4\n");
                    ptr=buffer;
                    hstatus=damecent();
                    st=RESPSTATUS4;
                    break;
    case RESPSTATUS4:if (haycar232(PUERTO)) {      // SI HAY CAR�CTER.
                         int ch;
                         ch=damecar232(PUERTO);
                         if (ptr-buffer>=MAXSTATUS) {
                             ptr=buffer;
                             st=TOKENSTATUS1;
                             return(STTERMICAAPAGADA);
                         }
                         *ptr++=(char)ch;
                         if (ch==10 || ch==48) {
                             if (buffer[0]=='1') return(STOUTOFPAPER);    // out of paper
                             if (buffer[1]=='1') return(STLABELNOTRE);    // label not removed
                             if (buffer[3]=='1') return(STHEADLIFTED);    // Head Lifted.
                             if (buffer[4]=='1') return(STBUTTONACTI);    // no paper in paper sensor
                             if (buffer[6]=='1') return(STPRINTREEST);    // Heap Error.
							 return(STTERMICAOK);      // Se han verificado todos los estados posibles de la etiquetadora.
                         }
                     } else {                  // SI NO HAY CAR�CTER.
                         if (damecent()-hstatus>TIMEOUTIMPRE) {
                             st=TOKENSTATUS1;
                             return(STTERMICAAPAGADA);
                         }
                     }
                     break;
	}
  return(STTERMICAENCURSO);
//return(STTERMICAOK); 
}
//////////////////////////////////////////////////////////////////////////////////////////
static void cancelatrabajomarkpoint(idrivers *id,int PUERTO)
{
  printf232(PUERTO,"!C\n");

}
//////////////////////////////////////////////////////////////////////////////////////////
static void tiraetiqmarkpoint(idrivers *id,char **ptrsal)
{
  sprintf(*ptrsal,"!P1\n");
  *ptrsal+=strlen(*ptrsal);
}
//////////////////////////////////////////////////////////////////////////////////////////
//#pragma warn +par
static void initetiq(idrivers *id,char **ptrsal)
{

  sprintf(*ptrsal,"!/ version 1\n");      // Establece el n�mero de versi�n de la etiqueta.
  *ptrsal+=strlen(*ptrsal);
  sprintf(*ptrsal,"!Y35 10\n");  // Establece .
  *ptrsal+=strlen(*ptrsal);
  sprintf(*ptrsal,"!C\n"); // Hace un clear de las variables.
  *ptrsal+=strlen(*ptrsal);
  sprintf(*ptrsal,"!/ label \"etiq\" \"\" \"\" \"\" \"\" 1 S %ld %ld 0 0\n",id->tx,anchoet);  // Configura las dimensiones i orientaci�n de la etiqueta.
  *ptrsal+=strlen(*ptrsal);

  sprintf(*ptrsal,"!C\n");      // Borra todas las variables de memo.
  *ptrsal+=strlen(*ptrsal);
  sprintf(*ptrsal,"!Y24 40\n");  // Establece Tear Off (area de impresi�n que queremos).
  *ptrsal+=strlen(*ptrsal);
  sprintf(*ptrsal,"!Y100 0\n"); // Establece alimentaci�n de papel reversa autom�tica antes de imprimir
  *ptrsal+=strlen(*ptrsal);
  /*
  sprintf(*ptrsal,"!Y6 12\n");  // Establece 12Puntos X milimetro(300dpi).8ppm(203dpi)
  *ptrsal+=strlen(*ptrsal);
  sprintf(*ptrsal,"!Y8 1280\n"); // Establece ancho en puntos por milimetro 1280=300dpi;832=203dpi;
  *ptrsal+=strlen(*ptrsal);
  */
  sprintf(*ptrsal,"!Y35 10\n");  // carga el caracter set = 1 , es a dir el CP 850, MS-DOS Latin1
                                // segons p�gina 38 del manual de programaci�n de la markpoint.
  *ptrsal+=strlen(*ptrsal);
}
//////////////////////////////////////////////////////////////////////////////////////////
void pondrivermarkpoint(idrivers *id)
{
    id->initetiq=NULL;
    id->cancelatrabajo=(void *)cancelatrabajomarkpoint;
    id->tiraetiq=(void *)tiraetiqmarkpoint;
    id->repiteetiq=1;
    id->imprimelinea=imprimelineamarkpoint;
    id->imprimecadena=imprimecadenamarkpoint;
	id->imprimecadenainv = imprimecadenamarkpoint;
    id->imprimebarras=imprimebarrasmarkpoint;
 //   id->cambiamaxetiq=initetiq;
	id->initetiq=initetiq;
    id->statusimpre=(void *)statusmarkpoint;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

