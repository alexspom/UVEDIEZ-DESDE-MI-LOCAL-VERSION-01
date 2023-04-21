#include "info4.h"

static tipodisps tipo[]={{0,"PL0D",0,0,0,1,23000},
                         {4,"PL4D",4,4,6,1,23000},
                         {6,"PL6D",6,4,6,1,23000},
                         {16,"PL16D",16,4,7,1,23000},
                         {-1,"DESCONOCIDO",0,0,0,1,23000}};

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

