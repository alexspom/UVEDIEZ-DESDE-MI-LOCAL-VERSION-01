/*
* Módulo : V10USERMAIN.C
* Objeto:  Módulo principal del programa V10USER
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 01-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10user.h"

users user;
cfgs cfg;  
static int generah=1,extension=0,generasql=1; 

void userinit(int argc,char *argv[])
{
  char nficsal[8+1];
  char ntablasal[8+1]="";
  int i = 0;

  user.nombre=strdup(ORAUSR);
  strmay(user.nombre);
  strcopia(nficsal,user.nombre,LAPLICACION-1);
  for (i=1;i<argc;i++) {
      if (*argv[i]=='-') {
          switch (toupper(argv[i][1])) {
          case 'F':strcopia(nficsal,argv[i]+2,LAPLICACION-1);
              break;
          case 'S':generah=0;  
              break;
          case 'Q':generasql=0;  
              break;
          case 'T':strcopia(ntablasal,argv[i]+2,LAPLICACION-1); 
                   extension=1;
              break;
          }
      }
  }
  strmay(nficsal);
  strcpy(user.aplicacion,nficsal);
  if (strlen(nficsal)>5) final(("Nombre de usuario mayor de seis."));
  strcopia(user.hficsal,nficsal,8);
  strcat(user.hficsal,"DEF.H");
  strcopia(user.sthficsal,nficsal,8);
  strcat(user.sthficsal,"ST.H");
  strcopia(user.sqlficsal,nficsal,8);
  strcat(user.sqlficsal,"ST.SQL");

  strcopia(user.dficsal,nficsal,8);
  strcat(user.dficsal,".DOC");
  strcopia(user.sficsal,nficsal,8);
  strcat(user.sficsal,".STR");
  strcopia(user.tficsal,nficsal,8);  
  strcat(user.tficsal,".TRI");
  sprintf(user.status,"%sSTATUS",extension==0 ? nficsal : ntablasal);
}


int main(int argc,char *argv[])
{  
  strcpy(TITULOVENTANA,"GENERACION DE FICHEROS");
  initv10lib(v10hinst,v10hprev);
  trataparamstd(argc,argv,trataparammain,trataparamoracle,NULL);
  initform();
  ttimeout=10;
  charblanco='²';
  cls(0,0,COLUMNASPANTALLA-1,LINEASPANTALLA-1,23);
  charblanco=' ';
  imprimep(0,0,0x00ff0000,0x00ffffff,"  GENERACION DE FICHEROS DE USUARIO ORACLE                                           ",0,80);
  userinit(argc,argv);
  initv10log("V10USER.LOG");
  anadetables(0);
  anadecolumns();
  if (chequeadatos()) tecla();
  imprimesth(generah,extension);  
  imprimeh(generah,extension);     
  imprimestr();
  imprimesql(generasql,extension); 
  return(0);
}

#ifndef __LINUX__

int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hprev,
           LPSTR cmd, int cmdshow)
{
  int ret;
  strcpy(TITULOVENTANA,"GENERACION DE FICHEROS");
  initv10lib(hinst,hprev);
  trataparamstd(__argc,__argv,trataparammain,trataparamoracle,NULL);
  ret=main(__argc,__argv);
  return(ret);
}
#endif
