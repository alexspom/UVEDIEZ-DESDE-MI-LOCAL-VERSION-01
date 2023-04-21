/*
* Módulo :  V10wwwMisc.C
* Objeto:   Funciones varias de posicionamiento y traducción caracteres especiales
* 
* 
* Autor	 : Francisco José Guerrero Sánchez
* Fecha  : 25-09-2007

* MODIFICACIONES
* ---------------------------
*/

#include "v10wwwform.h"
int v10maxpxX=1800,v10maxpxY=900;
int margenx=0,margeny=30;
#define MAXUTF8 15

typedef struct {
	char c_ansi; // carácter ansi
	char htmlcode[7]; // código html del carácter en utf8
} tansitohtml;

typedef struct {
	char cutf8[7]; // 2 byte utf8 
	char cansi[2]; // carácter ascii 
} tutf8;

tutf8 arrutf8[MAXUTF8]= {
	{"%C2%A0"," "},{"%C3%A1","á"},{"%C3%A9","é"},{"%C3%AD","í"},{"%C3%B3","ó"},{"%C3%BA","ú"},{"%C3%BC","ü"},{"%C3%B1","ñ"},
	{"%C3%81","Á"},{"%C3%89","É"},{"%C3%8D","Í"},{"%C3%93","Ó"},{"%C3%9A","Ú"},{"%C3%9C","Ü"},{"%C3%91","Ñ"}};


tansitohtml arransitohtml[95] = {
	{'¡',"&#161;"},{'¢',"&#162;"},{'£',"&#163;"},{'¤',"&#164;"},{'¥',"&#165;"}, 
	{'¦',"&#166;"},{'§',"&#167;"},{'¨',"&#168;"},{'©',"&#169;"},{'ª',"&#170;"}, 
	{'«',"&#171;"},{'¬',"&#172;"},{'­',"&#173;"},{'®',"&#174;"},{'¯',"&#175;"}, 
	{'°',"&#176;"},{'±',"&#177;"},{'²',"&#178;"},{'³',"&#179;"},{'´',"&#180;"}, 
	{'µ',"&#181;"},{'¶',"&#182;"},{'·',"&#183;"},{'¸',"&#184;"},{'¹',"&#185;"}, 
	{'º',"&#186;"},{'»',"&#187;"},{'¼',"&#188;"},{'½',"&#189;"},{'¾',"&#190;"}, 
	{'¿',"&#191;"},{'À',"&#192;"},{'Á',"&#193;"},{'Â',"&#194;"},{'Ã',"&#195;"}, 
	{'Ä',"&#196;"},{'Å',"&#197;"},{'Æ',"&#198;"},{'Ç',"&#199;"},{'È',"&#200;"}, 
	{'É',"&#201;"},{'Ê',"&#202;"},{'Ë',"&#203;"},{'Ì',"&#204;"},{'Í',"&#205;"}, 
	{'Î',"&#206;"},{'Ï',"&#207;"},{'Ð',"&#208;"},{'Ñ',"&#209;"},{'Ò',"&#210;"}, 
	{'Ó',"&#211;"},{'Ô',"&#212;"},{'Õ',"&#213;"},{'Ö',"&#214;"},{'×',"&#215;"}, 
	{'Ø',"&#216;"},{'Ù',"&#217;"},{'Ú',"&#218;"},{'Û',"&#219;"},{'Ü',"&#220;"}, 
	{'Ý',"&#221;"},{'Þ',"&#222;"},{'ß',"&#223;"},{'à',"&#224;"},{'á',"&#225;"}, 
	{'â',"&#226;"},{'ã',"&#227;"},{'ä',"&#228;"},{'å',"&#229;"},{'æ',"&#230;"}, 
	{'ç',"&#231;"},{'è',"&#232;"},{'é',"&#233;"},{'ê',"&#234;"},{'ë',"&#235;"}, 
	{'ì',"&#236;"},{'í',"&#237;"},{'î',"&#238;"},{'ï',"&#239;"},{'ð',"&#240;"}, 
	{'ñ',"&#241;"},{'ò',"&#242;"},{'ó',"&#243;"},{'ô',"&#244;"},{'õ',"&#245;"}, 
	{'ö',"&#246;"},{'÷',"&#247;"},{'ø',"&#248;"},{'ù',"&#249;"},{'ú',"&#250;"}, 
	{'û',"&#251;"},{'ü',"&#252;"},{'ý',"&#253;"},{'þ',"&#254;"},{'ÿ',"&#255;"}};


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
		if (cadena[i]=='Ï' || cadena[i]=='Ä'  || cadena[i]=='Ë' || 
			cadena[i]=='À' || cadena[i]=='Ù'  || cadena[i]=='³') v10carespeciales(cadena+i,cadena[i],"&#160;");
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
	// símbolos de + correspondientes a espacios en blanco eliminados
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
		if (cadena[i]==0xB3/*³*/ || cadena[i]==0xC0/*À*/  || cadena[i]==0xC4/*Ä*/ || 
			cadena[i]== 0xBF/*Ë*/ || cadena[i]== 0xDA/*Ï*/  || cadena[i]== 0xD9/*Ù*/) 				
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




