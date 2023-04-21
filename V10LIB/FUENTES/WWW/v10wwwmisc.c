/*
* M�dulo :  V10wwwMisc.C
* Objeto:   Funciones varias de posicionamiento y traducci�n caracteres especiales
* 
* 
* Autor	 : Francisco Jos� Guerrero S�nchez
* Fecha  : 25-09-2007

* MODIFICACIONES
* ---------------------------
*/

#include "v10wwwform.h"
int v10maxpxX=1800,v10maxpxY=900;
int margenx=0,margeny=30;
#define MAXUTF8 15

typedef struct {
	char c_ansi; // car�cter ansi
	char htmlcode[7]; // c�digo html del car�cter en utf8
} tansitohtml;

typedef struct {
	char cutf8[7]; // 2 byte utf8 
	char cansi[2]; // car�cter ascii 
} tutf8;

tutf8 arrutf8[MAXUTF8]= {
	{"%C2%A0"," "},{"%C3%A1","�"},{"%C3%A9","�"},{"%C3%AD","�"},{"%C3%B3","�"},{"%C3%BA","�"},{"%C3%BC","�"},{"%C3%B1","�"},
	{"%C3%81","�"},{"%C3%89","�"},{"%C3%8D","�"},{"%C3%93","�"},{"%C3%9A","�"},{"%C3%9C","�"},{"%C3%91","�"}};


tansitohtml arransitohtml[95] = {
	{'�',"&#161;"},{'�',"&#162;"},{'�',"&#163;"},{'�',"&#164;"},{'�',"&#165;"}, 
	{'�',"&#166;"},{'�',"&#167;"},{'�',"&#168;"},{'�',"&#169;"},{'�',"&#170;"}, 
	{'�',"&#171;"},{'�',"&#172;"},{'�',"&#173;"},{'�',"&#174;"},{'�',"&#175;"}, 
	{'�',"&#176;"},{'�',"&#177;"},{'�',"&#178;"},{'�',"&#179;"},{'�',"&#180;"}, 
	{'�',"&#181;"},{'�',"&#182;"},{'�',"&#183;"},{'�',"&#184;"},{'�',"&#185;"}, 
	{'�',"&#186;"},{'�',"&#187;"},{'�',"&#188;"},{'�',"&#189;"},{'�',"&#190;"}, 
	{'�',"&#191;"},{'�',"&#192;"},{'�',"&#193;"},{'�',"&#194;"},{'�',"&#195;"}, 
	{'�',"&#196;"},{'�',"&#197;"},{'�',"&#198;"},{'�',"&#199;"},{'�',"&#200;"}, 
	{'�',"&#201;"},{'�',"&#202;"},{'�',"&#203;"},{'�',"&#204;"},{'�',"&#205;"}, 
	{'�',"&#206;"},{'�',"&#207;"},{'�',"&#208;"},{'�',"&#209;"},{'�',"&#210;"}, 
	{'�',"&#211;"},{'�',"&#212;"},{'�',"&#213;"},{'�',"&#214;"},{'�',"&#215;"}, 
	{'�',"&#216;"},{'�',"&#217;"},{'�',"&#218;"},{'�',"&#219;"},{'�',"&#220;"}, 
	{'�',"&#221;"},{'�',"&#222;"},{'�',"&#223;"},{'�',"&#224;"},{'�',"&#225;"}, 
	{'�',"&#226;"},{'�',"&#227;"},{'�',"&#228;"},{'�',"&#229;"},{'�',"&#230;"}, 
	{'�',"&#231;"},{'�',"&#232;"},{'�',"&#233;"},{'�',"&#234;"},{'�',"&#235;"}, 
	{'�',"&#236;"},{'�',"&#237;"},{'�',"&#238;"},{'�',"&#239;"},{'�',"&#240;"}, 
	{'�',"&#241;"},{'�',"&#242;"},{'�',"&#243;"},{'�',"&#244;"},{'�',"&#245;"}, 
	{'�',"&#246;"},{'�',"&#247;"},{'�',"&#248;"},{'�',"&#249;"},{'�',"&#250;"}, 
	{'�',"&#251;"},{'�',"&#252;"},{'�',"&#253;"},{'�',"&#254;"},{'�',"&#255;"}};


/*int v10px2x(int px,double widthpx)
{
	return(int)(px/widthpx);
}*/
	
char *traduceutf8(char *cadena) {
	int i;
	for (i=0;i<MAXUTF8;i++) {
		while (strstr(cadena,arrutf8[i].cutf8))	v10cadespeciales(cadena,arrutf8[i].cutf8,arrutf8[i].cansi);
	}
	return(cadena);
}

int v10x2pxsm(int px,double widthpx)
{
	return((int)(px*widthpx));
}

int v10y2pxsm(int py,int heightpx)
{
	return(py*heightpx);
}

int v10x2px(int px,double widthpx)
{
	return(v10x2pxsm(px,widthpx)+margenx);
}

int v10y2px(int py,int heightpx)
{
	return(v10y2pxsm(py,heightpx)+margeny);
}

void v10ponresolucion(int x,int y)
{
	v10maxpxX=x;
	v10maxpxY=y;
}

int v10px2font(int px,int widthpx,double ptofont) 
{
	return ((int)(px*(double)((widthpx*widthpx)/ptofont)));
}

void v10ansitohtml(char *cadena) 
{
	int i;
	for (i=0;cadena[i];i++) {
		if (cadena[i] < 161) continue;
		if (cadena[i]=='�' || cadena[i]=='�'  || cadena[i]=='�' || 
			cadena[i]=='�' || cadena[i]=='�'  || cadena[i]=='�') v10carespeciales(cadena+i,cadena[i],"&#160;");
		else  {			
			switch (cadena[i]) {
				case '-': v10carespeciales(cadena+i,cadena[i],"&#45;");break;
				case '(': v10carespeciales(cadena+i,cadena[i],"&#40;");break;
				case ')': v10carespeciales(cadena+i,cadena[i],"&#41;");break;
				case '"': v10carespeciales(cadena+i,cadena[i],"&quot;");break;
				case '<': v10carespeciales(cadena+i,cadena[i],"&lt;");break;
				case '>': v10carespeciales(cadena+i,cadena[i],"&gt;");break;
				default: v10carespeciales(cadena+i,cadena[i],arransitohtml[cadena[i]-161].htmlcode);
			}
		}
	}
}

char *v10wwwoem2ansi(char *cad)
{
	char *source=strdup(cad);
	v10oemtoansi(source,cad);
	free(source);
	return(cad);
}

static void v10hextoansi(char *cadena, int off)
{
	char *ptr;
	char hex[3]="";	
	char ant[MAXCADENA]="",post[MAXCADENA]=""; 	
	ptr=strchr(cadena+off,'%');
	strcopia(ant,cadena,(int)(ptr-cadena));
	strcopia(post,ptr+3,(strlen(cadena)+cadena)-(ptr+3));	
	hex[0]=*(ptr+1);
	hex[1]=*(ptr+2);
	hex[2]=0;
	sprintf(cadena,"%s%c%s",ant,(char)strtol(hex,NULL,16),post);	
}


char *v10evtoansi(char *chtml)
{
	int off=0,i;
	char *ptr;
	// s�mbolos de + correspondientes a espacios en blanco eliminados
	for (i=0;i<strlen(chtml);i++) if (chtml[i]==43) chtml[i]=32;
	while ((ptr=strchr(chtml+off,'%'))) {
		v10hextoansi(chtml,off);
		off = (int)(ptr - chtml) + 1;
	}
	v10cadespeciales(chtml,"&amp;","&");	
	v10cadespeciales(chtml,"&gt;",">");	
	v10cadespeciales(chtml,"&lt;","<");	
	return(chtml);
}

void delrecuadrooem(char *cadena) 
{
	int i;
	for (i=0;i<strlen(cadena);i++) {
		if (cadena[i]==0xB3/*�*/ || cadena[i]==0xC0/*�*/  || cadena[i]==0xC4/*�*/ || 
			cadena[i]== 0xBF/*�*/ || cadena[i]== 0xDA/*�*/  || cadena[i]== 0xD9/*�*/) 				
		   cadena[i]=' ';
	}
}


char *v10cadespeciales(char *chtml,char *cad,char *newcad)
{
	char *ptr=chtml,*ptrcad;
	char chtml_bak[MAXCADENAHTML]="";
	while ((ptrcad=(char *)strstr(ptr,cad))!=NULL) {
		strcopia(chtml_bak+strlen(chtml_bak),ptr,(int)(ptrcad-ptr));
		strcat(chtml_bak,newcad);
		ptr=ptrcad+strlen(cad);
	}
	strcpy(chtml_bak+strlen(chtml_bak),ptr);
	strcpy(chtml,chtml_bak);	
	return(chtml);
}

char *v10carespeciales(char *chtml,char c,char *newc)
{    
    char *ptrch=chtml;
    while ((ptrch=strchr(ptrch,c))!=NULL) {
          //strcpy(ptrch,ptrch+1);
          *ptrch=*newc;
          strins(ptrch+1,newc+1);
          ptrch+=strlen(newc);
     }
    return(chtml);
}




