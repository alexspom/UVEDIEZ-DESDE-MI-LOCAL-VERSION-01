#include "info4.h"


#define 	A0   		0xfffe
#define 	A1   		0xfffe
#define 	A2   		0xfffd
#define 	A3   		0xf7ff
#define 	A4   		0xfdff
#define 	A5   		0xfdff
#define 	A6   		0xff7f
#define 	A7   		0xffbf
#define 	A8   		0xfff7
#define 	A9   		0xffdf
#define 	AA   		0xffef
#define 	AB   		0xfffb
#define 	AC   		0xfeff
#define 	AD   		0xefff
#define 	AE   		0xdfff
#define 	AF   		0xbfff
#define 	AP   		0xfbff
      
int  tablaascii[256]={
/*Segmentos uno a uno que son 17 ints*/
		0X0000,A1,A2,A3,A4,A5,A6,A7,A8,A9,AA,AB,AC,AD,AE,AF,AP,
/*Zona Libre que son 31 ints*/
		0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
		0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
		0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
/*.*/   AP,0xffff,
/*Numeros, letras y otros símbolos, que son 78 ints*/
/*0*/	A0&A1&A2&A3&A4&A5&A6&A7&AB&AF,
/*1*/	A2&A3&AB,
/*2*/	A0&A1&A2&A4&A5&A6&A8&AC,
/*3*/	A0&A1&A2&A3&A4&A5&AC,
/*4*/	A2&A3&A7&A8&AC,
/*5*/	A0&A1&A3&A4&A5&A7&A8&AC,
/*6*/	A0&A1&A3&A4&A5&A6&A7&A8&AC,
/*7*/	A0&A1&A2&A3,
/*8*/	A0&A1&A2&A3&A4&A5&A6&A7&A8&AC,
/*9*/	A0&A1&A2&A3&A4&A5&A7&A8&AC,
/*:*/	AA&AE,
/*;*/	AD,
/*<*/	AB&AD,
/*=*/	A4&A5&A8&AC,
/*>*/	A9&AF,
/*?*/	0xffff,
/*@*/	0xffff,
/*A*/   A0&A1&A2&A3&A6&A7&A8&AC,
/*B*/	A0&A1&A2&A3&A4&A5&AA&AE&AC,
/*C*/	A0&A1&A4&A5&A6&A7,
/*D*/	A0&A1&A2&A3&A4&A5&AA&AE,
/*E*/	A0&A1&A4&A5&A6&A7&A8,
/*F*/	A0&A1&A6&A7&A8,
/*G*/	A0&A1&A3&A4&A5&A6&A7&AC,
/*H*/	A2&A3&A6&A7&A8&AC,
/*I*/	A0&A1&A4&A5&AA&AE,
/*J*/	A2&A3&A4&A5&A6,
/*K*/	A6&A7&A8&AB&AD,
/*L*/	A4&A5&A6&A7,
/*M*/	A2&A3&A6&A7&A9&AB,
/*N*/	A2&A3&A6&A7&A9&AD,
/*O*/	A0&A1&A2&A3&A4&A5&A6&A7,
/*P*/	A0&A1&A2&A6&A7&A8&AC,
/*Q*/	A0&A1&A2&A3&A4&A5&A6&A7&AD,
/*R*/	A0&A1&A2&A6&A7&A8&AC&AD,
/*S*/	A0&A1&A3&A4&A5&A7&A8&AC,
/*T*/	A0&A1&AA&AE,
/*U*/	A2&A3&A4&A5&A6&A7,
/*V*/	A6&A7&AB&AF,
/*W*/	A2&A3&A6&A7&AD&AF,
/*X*/	A9&AB&AD&AF,
/*Y*/	A9&AB&AE,
/*Z*/	A0&A1&A4&A5&A8&AB&AC&AF,
/*[*/	A0&A1&A4&A5&A6&A7,
/*\*/	A9&AD,
/*]*/	A0&A1&A2&A3&A4&A5,
/*^*/	AD&AF,
/*-*/	A4&A5,
/*`*/	A9,
/*a*/	A4&A5&A6&A8&AE,
/*b*/	A5&A6&A7&A8&AE,
/*c*/	A5&A6&A8,
/*d*/	A5&A6&A8&AA&AE,
/*e*/	A4&A5&A6&A8&AF,
/*f*/	A1&AA&AC&AE,
/*g*/	A0&A5&A7&A8&AA&AE,
/*h*/	A6&A7&A8&AE,
/*i*/	A6,
/*j*/	A2&A3&A4&AE,
/*k*/	A6&A7&A8&AA&AE,
/*l*/	A5&A6&A7,
/*m*/	A3&A6&A8&AC&AE,
/*n*/	A6&A8&AE,
/*o*/	A3&A4&A5&A6&A8&AC,
/*p*/	A0&A6&A7&A8&AA,
/*q*/	A0&A7&A8&AA&AE,
/*r*/	A6&A8,
/*s*/	A4&AC&AD,
/*t*/	A5&A6&A7&A8,
/*u*/	A5&A6&AE,
/*v*/	A6&AF,
/*w*/	A3&A6&AD&AF,
/*x*/	A9&AB&AD&AF,
/*y*/	A3&A4&AD,
/*z*/	A5&A8&AF,
/*{*/	A2&A3&AC,
/*&*/	AA&AE,
/*}*/	A6&A7&A8,
/*Zona Libre de 38 ints*/
		0xffff,0xffff,
/*0.*/	A0&A1&A2&A3&A4&A5&A6&A7&AB&AF&AP,
/*1.*/	A2&A3&AB&AP,
/*2.*/	A0&A1&A2&A4&A5&A6&A8&AC&AP,
/*3.*/	A0&A1&A2&A3&A4&A5&AC&AP,
/*4.*/	A2&A3&A7&A8&AC&AP,
/*5.*/	A0&A1&A3&A4&A5&A7&A8&AC&AP,
/*6.*/	A0&A1&A3&A4&A5&A6&A7&A8&AC&AP,
/*7.*/	A0&A1&A2&A3&AP,
/*8.*/	A0&A1&A2&A3&A4&A5&A6&A7&A8&AC&AP,
/*9.*/	A0&A1&A2&A3&A4&A5&A7&A8&AC&AP,
		0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
		0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
		0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
/*Las españolas ñ y Ñ, y que viva España. Son 2 ints*/
/*ñ*/	A0&A1&A3&A6&A8&AC,
/*Ñ*/	A0&A1&A2&A3&A6&A7&A9&AD,
/*Zona libre de 90 ints*/
	    0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
		0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
		0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
		0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
		0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
		0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
		0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
		0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
		0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff};
long consuascii[256];
long cerosascii[256];
long cicloluces[4]={0,100,50,30};
long consumoluces[MAXLUCESDISPLAY]={653,1325,1325,59650,61650,37150,1325};
long consumoinfrarojo=44;
int  init=0;

static int cuentaunos(int valor)
{
  int i,ret=0;
  for (i=0;i<16;i++) {
      ret+=(valor&1);
      valor>>=1;
   }
 return(ret);
}

static void initconsumo(void)
{
  int i;
  if (init) return;
  init=1;
  for (i=0;i<256;i++) {
      cerosascii[i]=(8-cuentaunos(i))*consumoinfrarojo;
      consuascii[i]=16-cuentaunos(tablaascii[i]);
   }
}


static long consumolucesdisplay(infodisps *di)
{
  int i;
  long consumo=0;
  if (di->tipodisp==NULL) return(di->consumo=0);
  for (i=0;i<di->tipodisp->digitos;i++) {
      consumo+=consuascii[di->valor[i]];
   }
  consumo=((consumo*cicloluces[di->luces[0]])*consumoluces[0]);
  for (i=1;i<di->tipodisp->luces;i++) {
      consumo+=(cicloluces[di->luces[i]]*consumoluces[i]);
   }
  consumo/=100;
  return(di->consumo=consumo);
}

long consumolinea(infolineas *linea)
{
  int i,cambiado=linea->ciclotrabajo[0];
  long consumoluces=0,consumodisp=0,consumo232=0;
  initconsumo();
  for (i=0;i<linea->numdisp;i++) {
      infodisps *di=linea->disp+i;
      if (di->tipodisp==NULL) continue;
      consumoluces+=consumolucesdisplay(di);
      consumodisp+=di->tipodisp->consumo;
   }
  if (consumoluces==0) consumoluces=1;
  for (i=0;i<linea->lonida;i++) {
      consumo232+=cerosascii[linea->tramaida[i]];
   }
  linea->consumo=consumoluces+consumodisp;
  linea->consumo232=consumo232;
  if (linea->consumo>linea->limitacionlinea) {
     long resto=linea->limitacionlinea-consumodisp;
     int i;
     if (resto<0) resto=0;
     resto=(resto*7/consumoluces);
     for (i=0;i<MAXLUCESDISPLAY;i++) linea->ciclotrabajo[i]=resto;
     if (linea->ciclotrabajo[6]<6) linea->ciclotrabajo[6]=6;
   } else {
     int i;
     for (i=0;i<MAXLUCESDISPLAY;i++) linea->ciclotrabajo[i]=7;
   }
  return(cambiado!=linea->ciclotrabajo[0]);
}
