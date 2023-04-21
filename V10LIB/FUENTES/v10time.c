/*
* M�dulo : V10TIME.C
* Objeto:  Manejo estandarizado de fecha y hora
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"

#define FEPOCH   2415385L /* Es el 1 de Enero de 1901 en juliano. */
#define ANOEPOCH    1901L

#define CENTHORA 360000L /* Cent�simas de segundo en una hora. */
#define CENTMINUTO 6000L /* Cent�simas de segundo en un minuto. */
#define CENTSEGUNDO 100L /* Cent�simas de segundo en un segundo. */


char *nombredemes[13]={"          ","ENERO     ","FEBRERO   ","MARZO     ",
                     "ABRIL     ","MAYO      ","JUNIO     ","JULIO     ",
		             "AGOSTO    ","SEPTIEMBRE","OCTUBRE   ","NOVIEMBRE ",
		             "DICIEMBRE "};

int diasdemes[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};

static int anohoy;
static int meshoy;
static int diahoy;
static v10dates fechahoy;

static int diasanonormal[12]={0,31,59,90,120,151,181,212,243,273,304,334};
static int diasanobisiesto[12]={0,31,60,91,121,152,182,213,244,274,305,335};



static char *format(int ano,int mes,int dia,char *formato,char *donde)
{
  char *salida = donde;
  char letra;

  while (*formato) {
    *salida=*formato;
    letra=*formato++;
    switch (toupper(letra)) {
      case 'D':
                  if (toupper(*formato)=='D') {
                  if (*formato=='D') {
                    *salida++=(char)((dia/10)+'0');
                    *salida=(char)((dia%10)+'0');
                    formato++;
                  }
                  if (*formato=='d') {
                    if (dia>9) *salida++=(char)((dia/10)+'0');
                    else *salida++=' ';
                    *salida=(char)((dia%10)+'0');
		    formato++;
                  }
                }
		else *++salida=*formato++;
                break;

      case 'M':
                if (toupper(*formato)=='M' || toupper(*formato)=='L') {
                  if (*formato=='M') {
                    *salida++=(char)((mes/10)+'0');
                    *salida=(char)((mes%10)+'0');
                    formato++;
                  }
                  if (*formato=='m') {
                    if (mes>9) *salida++=(char)((mes/10)+'0');
                    else *salida++=' ';
                    *salida=(char)((mes%10)+'0');
                    formato++;
                  }
                  if (toupper(*formato)=='L') {
		    int cuantos;
                    char letra = *formato;

		    formato++;
                    if (isdigit(*formato)) {
                      cuantos=*formato-'0';
                      if (cuantos==0) cuantos=10;
                      formato++;
                    }
                    else cuantos=3;
                    strncpy(salida,v10translate(nombredemes[mes]),cuantos);
                    salida[cuantos]='\0';
                    if ((letra=='l') && (mes!=0)) {
                      eliminasp(salida);
                    }
                    cuantos=strlen(salida);
                    salida+=cuantos-1;
                  }
                }
                else *++salida=*formato++;
		break;

      case 'Y':
		if (toupper(*formato)=='Y' || *formato=='.') {
                  if (toupper(*formato)=='Y') {
                    sprintf(salida,"%02d",ano%100);
                    salida++;
                    formato++;
                  }
                  if (*formato=='.') {
                    sprintf(salida,"%4d",ano);
                    salida+=3;
                    formato++;
                    if (toupper(*formato)=='Y') formato++;
                    if (toupper(*formato)=='Y') formato++;
                  }
                }
                else *++salida=*formato++;
                break;
    }
    salida++;
  }
  *salida='\0';
  if ((dia||mes||ano)==0) strfill(donde,' ',strlen(donde));
  return(donde);
}

v10dates jultof(v10dates fechajul,int *dia,int *mes,int *ano)
{
  v10dates auxiliar;
  int *tipo_ano;

  if (fechajul<=FEPOCH) fechajul=FEPOCH+1;
  auxiliar=(fechajul-FEPOCH);
  *ano=ANOEPOCH+(int)((auxiliar-1)/1461)*4;
  auxiliar=auxiliar-(((auxiliar-1)/1461)*1461);

  tipo_ano=diasanonormal;
  if (auxiliar>1095) {
    auxiliar -= 1095;
    (*ano)+=3;
    tipo_ano=diasanobisiesto;
  } else {
    if (auxiliar>730) {
      auxiliar -= 730;
      (*ano)+=2;
    }
    else {
      if (auxiliar>365) {
        auxiliar -= 365;
        (*ano)+=1;
      }
    }
  }

  *mes=1;
  while ((auxiliar>(v10dates)tipo_ano[*mes]) && ((*mes)<12))
    (*mes)++;

  *dia=(int)auxiliar-tipo_ano[(*mes)-1];
  return(fechajul);
}

char *jul2a(v10dates fechajul,char *formato,char *donde)
{
  int dia;
  int mes;
  int ano;

  if (fechajul==0) return(format(0,0,0,formato,donde));
  jultof(fechajul,&dia,&mes,&ano);

  return(format(ano,mes,dia,formato,donde));
}


v10dates f2jul(int dia,int mes,int ano)
{
  v10dates resto,total;
  int *tipo_ano;

  if (ano==-1) ano=anohoy;
  if (ano<100) ano+=(anohoy)/100*100;
  if (mes==0) mes=meshoy;
  if (mes<0 || mes>12) {
    return(-1);
  }
  if (dia==0) dia=diahoy;
  if (dia<0 || dia>diasdemes[mes]) {
    return(-1);
  }
  if (ano<ANOEPOCH) ano=ANOEPOCH;
  total=(((v10dates)ano-ANOEPOCH)/4)*1461;
  resto=((v10dates)ano-ANOEPOCH)%4;
  if (resto<3) tipo_ano=diasanonormal;
  else tipo_ano=diasanobisiesto;
  total+=resto*365+tipo_ano[mes-1]+dia;
  total+=FEPOCH;
  return(total);
}

v10dates damedate(void)
{
#ifndef __LINUX__
  SYSTEMTIME time;
  GetLocalTime(&time);
  anohoy=time.wYear;
  meshoy=time.wMonth;
  diahoy=time.wDay;
#else
  struct tm *t;
  time_t ahora;
  char buff[20];
  ahora=time(0);
  t=localtime(&ahora);
  strftime(buff,10,"%Y",t);
  anohoy=atoi(buff);
  strftime(buff,10,"%m",t);
  meshoy=atoi(buff);
  strftime(buff,10,"%d",t);
  diahoy=atoi(buff);
#endif
  fechahoy=f2jul(diahoy,meshoy,anohoy);
  return(fechahoy);
}


static int dato(char *cadena,int *donde,int cuantos)
    /* Convierte a entero y sit�a en donde como m�ximo los
       cuantos primeros caract�res num�ricos de la cadena
       cadena. Devuelve el n�mero de caract�res avanzados. */
{
  int total = 0;
  char dato[5] = {0,0,0,0,0};
  int i = 0;

  while (*cadena && (!isdigit(*cadena))) {
    cadena++;
    total++;
  }
  while (i<cuantos && *cadena && isdigit(*cadena)) {
    dato[i++]=*cadena++;
    total++;
  }
  if (es_blanco(dato)) *donde=-1;
     else              *donde=atoi(dato);
  return(total);
}


v10dates a2jul(int tipo,char *lafecha)
{
  int ano=0,mes=0,dia=0;

  switch (tipo) {
    case 1: lafecha+=dato(lafecha,&dia,2);
	    lafecha+=dato(lafecha,&mes,2);
	    dato(lafecha,&ano,4);
	    break;

    case 2: lafecha+=dato(lafecha,&mes,2);
	    lafecha+=dato(lafecha,&dia,2);
	    dato(lafecha,&ano,4);
	    break;

    case 3: lafecha+=dato(lafecha,&ano,2);
	    lafecha+=dato(lafecha,&mes,2);
	    dato(lafecha,&dia,2);
	    break;

    case 7: lafecha+=dato(lafecha,&ano,4);
	    lafecha+=dato(lafecha,&mes,2);
	    dato(lafecha,&dia,2);
	    break;

    case 4: lafecha+=dato(lafecha,&dia,2);
	    dato(lafecha,&mes,2);
	    ano = 0;
	    break;

    case 5: dia = 1;
	    lafecha+=dato(lafecha,&mes,2);
	    dato(lafecha,&ano,4);
	    break;

    case 6: dia = 1;
	    lafecha+=dato(lafecha,&ano,4);
	    dato(lafecha,&mes,2);
	    break;
  }
  if (dia==-1 && mes==-1 && ano==-1) return(0);
  if (dia==-1) dia=1;
  if (mes==-1) mes=0;
  damedate();
  return(f2jul(dia,mes,ano));
}


char *cent2a(v10horas centhora,int formato,char separador,char *donde)
{
  int hora,minutos,segundos;
  v10horas aux;
  char *salida = donde;
  char pmoam;

  if (formato>8 || formato<0) formato=0;

  hora=(int)(centhora/CENTHORA);
  if (hora>11) pmoam='p';
  else pmoam='a';
  aux=centhora-hora*CENTHORA;
  minutos=(int)(aux/CENTMINUTO);
  aux=aux-minutos*CENTMINUTO;
  segundos=(int)(aux/CENTSEGUNDO);
  aux=aux-segundos*CENTSEGUNDO;
  if ((formato!=0) && (formato!=3) && (formato!=6)&& (formato!=8)) hora%=12;
  sprintf(salida,"%02d%c%02d",hora,separador,minutos);
  if ((formato < 3) || (formato > 5)) {
      sprintf(salida+strlen(salida),"%c%02d",separador,segundos);
  }
  if ((formato==2) || (formato==5)) {
      sprintf(salida+strlen(salida)," %cm",pmoam);
  }
  if (formato==8) {
        sprintf(salida+strlen(salida),"%c%03d",separador,(int)(aux*10));
  } else {
    if (formato > 5) {
        sprintf(salida+strlen(salida),"%c%02d",separador,(int)aux);
	}
  }
  return(donde);
}


v10horas a2cent(char *lahora)
{
  int hora,minutos,segundos,cent;

  lahora+=dato(lahora,&hora,2);
  lahora+=dato(lahora,&minutos,2);
  lahora+=dato(lahora,&segundos,2);
  lahora+=dato(lahora,&cent,2);
  return((v10horas)hora*CENTHORA+(v10horas)minutos*CENTMINUTO+segundos*CENTSEGUNDO+cent);
}

v10horas gettime(void)
{
#ifndef __LINUX__
  SYSTEMTIME time;
  GetLocalTime(&time);
  return((v10horas)time.wHour*CENTHORA+(v10horas)time.wMinute*CENTMINUTO+time.wSecond*CENTSEGUNDO+time.wMilliseconds/10.0);
#else
  struct timeval tp;
  tzset();
  gettimeofday(&tp,NULL);
  return(((tp.tv_sec-timezone)%(3600*24))*100+tp.tv_usec/10000);
#endif
}

static v10dates fecini;
static v10horas  horaini;
#ifndef __LINUX__
static v10horas lrdamecent(void)
{
  v10dates fecahora;
  v10horas  horaahora;
  fecahora=damedate();
  horaahora=gettime();
  if (fecini==0) {
     fecini=fecahora;
   }
  horaahora-=horaini;
  horaahora+=(fecahora-fecini)*CENTHORA*24;
  return(horaahora);
}
#endif



v10horas damecent(void)
{  
#ifndef __LINUX__
    static LARGE_INTEGER tickssegundo={0},tickprin;
    LARGE_INTEGER tick;  
    if (tickssegundo.QuadPart==0) {
       if (!QueryPerformanceFrequency(&tickssegundo)) return(lrdamecent());
       tickssegundo.QuadPart/=100;
       QueryPerformanceCounter(&tickprin);
       tickprin.QuadPart=(LONGLONG)(gettime()*tickssegundo.QuadPart)-tickprin.QuadPart;
    }
    QueryPerformanceCounter(&tick);
    return((double)(tick.QuadPart+tickprin.QuadPart)/(double)tickssegundo.QuadPart);
#else
  v10dates fecahora;
  v10horas  horaahora;
  fecahora=damedate();
  horaahora=gettime();
  if (fecini==0) {
      fecini=fecahora;
  }
  horaahora+=(fecahora-fecini)*CENTHORA*24;
  return horaahora;
#endif
}
