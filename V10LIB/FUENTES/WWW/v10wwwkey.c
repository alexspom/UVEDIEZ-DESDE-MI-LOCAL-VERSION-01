/*
* Módulo :  V10wwwKey.C
* Objeto:  Traducción teclas ANSI a HTML/Javascript
* 
* 
* Autor	 : Francisco José Guerrero Sánchez
* Fecha  : 25-09-2007

* MODIFICACIONES
* ---------------------------
*/

#include "v10wwwform.h"



typedef struct {
	int wwwcode;  // código tecla en Navegador
	int ansicode; // código tecla ANSI
} v10wwwkey;


static v10wwwkey wwwVansi[V10MAXTECLAS]={
	{112,3101}, {113,3102},  {114,3103}, {115,3104},{116,3105}, {117,3106}, {118,3107},	{119,3108},	{120,3109},	{121,3110},	{122,3111},	{123,3112},
	{40,336}, {38,328}, {39,333}, {37,331}, {33,329}, {34,337}, {45,338}, {46,339},  {36,327}, {35,335}, {46,339}, {93,1130},
	{37,371}, {39,372}, {35,373}, {34,374}, {36,375}, {8,127},  {33,388}, {45,1010}, {46,1011},{40,1012},{38,1013},	
	{45,1014},{46,1015},{37,1016},{39,1017},{38,1018},{40,1019},{36,1020},{35,1021}, {33,1022},{34,1023},{9,271}};



	int v10ansi2js(int k)
	{
		int i;
		//combinaciones de teclas de función
		if (k>3120 && k<3132) k-=20;	//Tecla Shift
		if (k>3140 && k<3152) k-=40;	//Tecla Control	  
		if (k>3160 && k<3172) k-=60; 	//Tecla Alt	  
		for (i=0;i<V10MAXTECLAS;i++) 
			if (wwwVansi[i].ansicode==k) 
				return(wwwVansi[i].wwwcode);
		if (k>=97 && k<=122) k-=32; 
		return(k);
	}


	char *v10comb(char *kespecial,int k)
	{
		memset(kespecial,0,100);
		if (k>3140 && k<3152)   strcpy(kespecial,V10WWWCONTROL);
		if (k>3160 && k<3172)   strcpy(kespecial,V10WWWALT);
		if (k==271 || (k>3120 && k<3132))	strcpy(kespecial,V10WWWSHIFT);
		if (k==127 || k==388 || (k>=1010 && k<=1013) || (k>=371 && k<=375)) strcpy(kespecial,V10WWWCONTROL);
		if (k>=1014 && k<=1023) strcpy(kespecial,V10WWWSHIFT);
		return(kespecial);
	}




	int v10charjs2ansi(int k,int ini,int fin)
	{
		int i;
		for (i=ini;i<ini+fin;i++)
			if (wwwVansi[i].wwwcode==k)  return wwwVansi[i].ansicode;
		return(k);
	}



	int v10js2ansi(char *ev,int k)
	{
		int ret;
		char *kespecial;

		kespecial=strstr(ev,"_");
		if (!kespecial) return v10charjs2ansi(k,0,24);
		kespecial++;
		k=v10charjs2ansi(k,0,12);

		if (!strcmp(kespecial,V10WWWSHIFT)) {
			if (k>3100) return (k+=20);
			ret= v10charjs2ansi(k,35,46);
			if (ret<=0) return(1);
			return(ret);	
		}

		if (!strcmp(kespecial,V10WWWCONTROL)) {
			if (k>3100) return (k+=40);		
			ret= CTRL(k); 
			if (ret<=0) return(1);
			return(ret);
		}

		if (!strcmp(kespecial,V10WWWALT)) {
			if (k>3100) return (k+=60);
			ret= ALT(k);		
			if (ret<=0) return(1);
			return(ret);
		}


		return(v10charjs2ansi(k,0,V10MAXTECLAS));
}