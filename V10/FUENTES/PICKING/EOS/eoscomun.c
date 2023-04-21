/*
* Módulo : EOSCOMUN.C
* Objeto: Funciones comunes para ethernet-box y PC en displays de la gama EOS
*
*
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-12-2007

* MODIFICACIONES
* --
*/
#include "eos.h"

#define NUMTIPODISP 20
#define CONSUMODEFECTO 23000

//Tipo, nombre, digitos, botones, luces, status, consumo

static tipodisps tipo[NUMTIPODISP]={{0,"EOS0",0,1,6,1,21000}, 
				   {4,"EOS4",4,4,6,1,32000},
				   {6,"EOS6",6,4,6,1,32000},
				   {16,"EOS16",16,4,7,1,37000},
				   {17,"EOS16XL",16,0,1,1,CONSUMODEFECTO},
				   {18,"EOS16XLM",16,0,1,1,CONSUMODEFECTO},
				   {23,"EOSDA",0,2,2,1,CONSUMODEFECTO},
				   {24,"EOSACT5",0,1,5,1,CONSUMODEFECTO},
				   {25,"EOSRS232",0,0,0,16,CONSUMODEFECTO},
				   {26,"EOSBAT",0,3,0,1,CONSUMODEFECTO},
                                   {-1,"DESCONOCIDO",20,4,7,1,CONSUMODEFECTO}};

tipodisps *dametipo(int  mitipo)
{
    int i=0;
    while (tipo[i].tipo!=mitipo && tipo[i].tipo!=-1) i++;
    return(tipo+i);
}

char *recogelong(char *cadena,unsigned long *p)
{
    *p=*cadena++;
    *p=*p+(*cadena++<<8);
    *p=*p+(+*cadena++<<16);
    *p=*p+(*cadena++<<24);
    return(cadena);
}

char *mandalong(char *cadena,unsigned long p)
{
    *cadena++=(char)(p&0xff);
    *cadena++=(char)((p>>8)&0xff);
    *cadena++=(char)((p>>16)&0xff);
    *cadena++=(char)((p>>24)&0xff);
    return(cadena);
}


char *recogeshort(char *cadena,unsigned short *p)
{
    *p=*cadena++;
    *p=(unsigned short)(*p+(*cadena++<<8));
    return(cadena);
}

char *mandashort(char *cadena,unsigned short p)
{
    *cadena++=(char)(p&0xff);
    *cadena++=(char)((p>>8)&0xff);
    return(cadena);
}

char *llinfodameversion(unsigned long version,int adisp)
{
    static char cversion[sizeof(long)+2];
    if (adisp) {
        cversion[4]=0;
        cversion[3]=(char)(version&0xff);
        cversion[2]=(char)((version>>8)&0xff);
        cversion[1]=(char)(((version>>16)&0xff)+128-'0');
    } else {
        cversion[5]=0;
        cversion[4]=(char)(version&0xff);
        cversion[3]=(char)((version>>8)&0xff);
        cversion[2]='.';
        cversion[1]=(char)((version>>16)&0xff);
    }
    cversion[0]=(char)((version>>24)&0xff);
    return(cversion);
}

char *infodameversion(unsigned long version)
{
    return(llinfodameversion(version,0));
}

