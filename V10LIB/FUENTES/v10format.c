/*
* Módulo : V10FORMAT.C
* Objeto:  Formatea long y doubles
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/

#include "v10.h"

#define MAXLLONG 50
//char *fcvt(double number, int ndigits, int *decpt, int *sign);

unsigned v10formatdef = COMADECIMAL;


static char *v10formatlong(long numero,int longitud,int tipo,char relleno,char *donde,int base,int consigno)
{
  char *salida;
  int lon;
  int signo=0;
  char straux[2]={0,0};
  straux[0]=relleno;
  if (longitud>32) lon=32;
  else lon=longitud;
  if (base==0) base=10;
  salida=(char *)calloc(MAXLLONG+1,1);
  if (consigno) {
     if (numero<0) {
        signo=1;
        numero=-numero;
      } else signo=0;
   }
  if (consigno) ltoa(numero,salida,base);
     else     ultoa(numero,salida,base);
  strmay(salida);
  lon-=strlen(salida);
  if (signo==1) {
    if (lon>0) {
      if (tipo & SIGNODERECHA) strcat(salida,"-");
      else strins(salida,"-" );
    }
    lon--;
  } else {
	  if (lon>0) {
         if (tipo & FUERZASIGNO) {
            if (tipo & SIGNODERECHA) strcat(salida,"+");
             else strins(salida,"+" );
            lon--;
		 } else {
           if (tipo & SIGNODERECHA) {
              strcat(salida," ");
              lon--;
		   }
		 }
	  }
  }
  if ((tipo & MARCAMILES) && (lon>0)) {
    int i;
    i=strlen(salida)-3-(((tipo & FUERZASIGNO) || signo) && (tipo & SIGNODERECHA));
    while(i>0 && (lon>0)) {
      if (tipo & COMADECIMAL) strins(salida+i+(((tipo & FUERZASIGNO) || signo) && (tipo & SIGNODERECHA)),".");
      else strins(salida+i+(((tipo & FUERZASIGNO) || signo) && (tipo & SIGNODERECHA)),",");
      i-=3;
      lon--;
    }
  }
  if (lon<0) strfill(donde,'*',longitud);
  else {
    if (*salida=='-' && relleno!=' ') signo=1;
    else signo=0;
    while (lon-->0) strins(salida+signo,straux);
    strcpy(donde,salida);
  }
  free(salida);
  return(donde);
}

char *v10lformat(long numero,int longitud,int tipo,char relleno,char *donde,int base)
{
  return(v10formatlong(numero,longitud,tipo,relleno,donde,base,1));
}

char *v10uformat(unsigned long numero,int longitud,int tipo,char relleno,char *donde,int base)
{
  return(v10formatlong(numero,longitud,tipo,relleno,donde,base,0));
}

long v10lval(char *cadena,int tipo,int base)
{
  char *salida,*aux;
  char separador;
  long numero;
  if (base==0) base=10;
  salida=(char *)calloc(strlen(cadena)+1,1);
  if (tipo & COMADECIMAL) separador='.';
  else separador=',';
  aux=salida;
  while (*cadena) {
    if (*cadena==separador) cadena++;
    else *aux++=*cadena++;
  }
  *aux=0;
  numero=strtol(salida,&aux,base);
  free(salida);
  return(numero);
}

unsigned long v10uval(char *cadena,int tipo,int base)
{
  char *salida,*aux;
  char separador;
  unsigned long numero;
  salida=(char *)calloc(strlen(cadena)+1,1);
  if (tipo & COMADECIMAL) separador='.';
  else separador='.';
  aux=salida;
  while (*cadena) {
    if (*cadena==separador) cadena++;
    else *aux++=*cadena++;
  }
  *aux=0;
  numero=strtoul(salida,&aux,base);
  free(salida);
  return(numero);
}

char *v10dformat(double numero,int decimales,int longitud,int tipo,char relleno,char *donde)
{
  char *salida,*parte_entera,*parte_decimal,*ptr;
  int posdec,signo;
  int lon,i;
  char straux[2]={0,0};
  straux[0]=relleno;
  ptr=fcvt(numero,decimales,&posdec,&signo);
  parte_decimal=(char *)calloc(decimales+1,1);
  if (posdec>0) {
    parte_entera=(char *)calloc(posdec+1,1);
    strcopia(parte_entera,ptr,posdec);
    strcopia(parte_decimal,ptr+posdec,decimales);
  }
  else {
    parte_entera=(char *)calloc(1+1,1);
    strcpy(parte_entera,"0");
    if (decimales) {
       for (i=0;i<-posdec && decimales;decimales--,i++)
           parte_decimal[i]='0';
       if (decimales) strcopia(parte_decimal-posdec,ptr,decimales);
    }
  }
  if (strlen(parte_decimal)==0) {
    for (i=0;i<decimales;i++) {
      parte_decimal[i]='0';
    }
  }
  salida=(char *)calloc(longitud+1,1);
  lon=longitud-strlen(parte_entera)-strlen(parte_decimal);
  if (strlen(parte_decimal)) lon--;
  if (lon>=0) {
    strcpy(salida,parte_entera);
    ptr=salida+strlen(salida);
    if (strlen(parte_decimal)) {
       if (tipo & COMADECIMAL) strins(ptr,",");
          else strins(ptr,".");
       strins(salida+strlen(salida),parte_decimal);
     }
  }
  if (signo==1) {
    if (lon>0) {
      if (tipo & SIGNODERECHA) strcat(salida,"-");
      else {
	     strins(salida,"-" );
	     ptr++;
      }
      lon--;
    }
  }
  else {
	  if (lon) {
         if (tipo & SIGNODERECHA) {
            if (tipo & FUERZASIGNO) strcat(salida,"+");
			else strcat(salida," ");
            lon--;
		 } else {
			 if (tipo & FUERZASIGNO) {
				 strins(salida,"+");
				 lon--;
				 ptr++;
			 }
		 }
    }
  }
  if (((tipo & MARCAMILES)) && (lon>0)) {
    i=(strlen(parte_entera)-1)/3;
    while(i>0 && (lon>0)) {
      ptr-=3;
      if (tipo & COMADECIMAL) strins(ptr,".");
      else strins(ptr,",");
      lon--;
      i--;
    }
  }
  if (lon<0) strfill(donde,'*',longitud);
  else {
    if (*salida=='-' && relleno!=' ') signo=1;
    else signo=0;
    while (lon-->0) strins(salida+signo,straux);
    strcpy(donde,salida);
  }
  free(salida);
  free(parte_entera);
  free(parte_decimal);
  return(donde);
}


double v10dval(char *cadena,int tipo)
{
  char *salida,*aux;
  int signo = 1;
  double numero;
  salida=(char *)calloc(strlen(cadena)+1,1);
  aux=salida;
  while (*cadena) {
    if ((*cadena>='0') && (*cadena<='9')) *aux++=*cadena;
    if (*cadena=='-') signo=-1;
    if ((*cadena==',') && (tipo & COMADECIMAL)) *aux++='.';
    if ((*cadena=='.') && (tipo & COMADECIMAL)==0) *aux++='.';
    cadena++;
  }
  *aux=0;
  numero=atof(salida)*signo;
  free(salida);
  return(numero);
}
