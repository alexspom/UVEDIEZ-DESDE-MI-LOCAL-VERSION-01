/****
* VDCOMENFORMTRIG.C
*                                                    
* Propósito: Triggers para el manejo de comentarios desde pantalla                   
*                                                                              
* Autor  : FGS e ICC                                                           
* Fecha  : 13-11-2007                                                          
******
*  Modificaciones:
****/

#include "vd.h"

// función interna que crea un comentario para los triggers que la llaman
static int llcreacomen(char *nombretrigger,int relogin, bloques *b, ftrigers *ft) {
  int ret,numcampo;
  char campocomen[MAXNOMBREV10]="",tabla[MAXNOMBREV10]="";
  long *ptr=NULL;
  vdcomens com;
  char msjerror[MAXCADENA]="";

  if (ft->nparam<5) {
    mensajefcm(10,"Pocos parametros en %s nos pasan %d y necesitamos\n "
                  "TABLA,CODCOMEN,TIPOCOMEN,LINCOMEN,COMENTARIO",
        nombretrigger,ft->nparam);
		return(-1);
  } 
    
  // captura el valor del campo CODCOMEN
  dameparametro(b,ft,0, V10CADENA, campocomen);
  numcampo=damecampo(b, campocomen);
  if (numcampo<0) {
	  mensajefcm(10,"No existe campo %s en %s",campocomen,nombretrigger);
		return(-1);
  } 

  dameparametro(b,ft,1, V10CADENA, tabla);
  
  ptr=(long *)direcncampo(b,campocomen);

  dameparametro(b,ft,2, V10CADENA, com.tipocomen);
  dameparametro(b,ft,3, V10LONG,   &com.lincomen);
  dameparametro(b,ft,4, V10CADENA, com.comentario);

  if (relogin==0) ret=v10comen(tabla,*ptr,com.tipocomen,com.lincomen,com.comentario,msjerror);
  else ret=v10comenrelogin(tabla,*ptr,com.tipocomen,com.lincomen,com.comentario,msjerror);
  ponerrorbloque(b,msjerror);
  return(ret);
}

// FCREACOMEN("CODCOMEN","TABLA","TIPOCOMEN",":LINCOMEN","COMENTARIO")
// si lincomen es 0, el numero de linea a crear es la ultima existente del tipo +1 
// se crea en la transacción actual
VDEXPORT int fcreacomen(bloques *b,ftrigers *ft)
{ 
  return(llcreacomen("fcreacomen",0,b,ft));
}


// FCREACOMENRELOGIN("CODCOMEN","TABLA","TIPOCOMEN",":LINCOMEN","COMENTARIO)
// si lincomen es 0, el numero de linea a crear es la ultima existente del tipo +1 
// se crea en una transacción independiente
VDEXPORT int fcreacomenrelogin(bloques *b,ftrigers *ft)
{ 
  return(llcreacomen("fcreacomenrelogin",1,b,ft));
}


// FDAMECOMEN("CODCOMEN","TIPOCOMEN",":LINCOMEN","COMENTARIO")
// si lincomen es 0,devuelve el primero
VDEXPORT int fdamecomen(bloques *b,ftrigers *ft)
{ 
  int ret,numcampo;
  char msjerror[LCADENABIG]="",campocomen[MAXNOMBREV10]="";
  char *comentario;
  vdcomens com;

  if (ft->nparam<4) {
    mensajefcm(10,"Pocos parametros en FDAMECOMEN nos pasan %d y necesitamos 4\n "
                  "CODCOMEN,TIPOCOMEN,LICOMEN,COMENTARIO",
        ft->nparam);
		return(-1);    
  } 
 
  memset(&com,0,sizeof(com));

  // coge el campo para meter comentarios
  numcampo=damecampo(b, ft->param[3]);
	if (numcampo<0) {
		mensajefcm(10,"No existe campo %s en fdamecomen",ft->param[3]);
		return(-1);
	}
  comentario=direcncampo(b,ft->param[3]);

  dameparametro(b,ft,0, V10CADENA, campocomen);
  numcampo=damecampo(b, campocomen);
  if (numcampo<0) {
	  mensajefcm(10,"No existe campo %s en fdamecomen",campocomen);
		return(-1);
  } 
  com.codcomen=*((long *)direcncampo(b,campocomen));
  dameparametro(b,ft,1, V10CADENA, com.tipocomen);
  dameparametro(b,ft,2, V10LONG, &com.lincomen);
  ret=v10damecomen(com.codcomen,com.tipocomen,com.lincomen,msjerror,&com);

  if (ret==0) strcpy(comentario,com.comentario);
  ponerrorbloque(b,msjerror);
  return(ret);
}


// FBORRACOMENPORTIPO("CODCOMEN","TIPOCOMEN")
VDEXPORT int fborracomenportipo(bloques *b,ftrigers *ft)
{ 
  int ret,numcampo;
  long codcomen;
  char campocomen[MAXNOMBREV10]="",tipocomen[LTIPOCOMEN]="";
  char msjerror[MAXCADENA]="";
  
  if (ft->nparam<2) {
    mensajefcm(10,"Pocos parametros en FBORRACOMENPORTIPO nos pasan %d y necesitamos 2\n "
                  "CODCOMEN,TIPOCOMEN",
        ft->nparam);
		return(-1);    
  }  

  dameparametro(b,ft,0, V10CADENA, campocomen);
  numcampo=damecampo(b, campocomen);
  if (numcampo<0) {
	  mensajefcm(10,"No existe campo %s en fdamecomen",campocomen);
		return(-1);
  } 
  codcomen=*((long *)direcncampo(b,campocomen));
  dameparametro(b,ft,1, V10CADENA, tipocomen);
  ret=v10deletecomenportipo(codcomen, tipocomen,msjerror);
  ponerrorbloque(b,msjerror);
  return(ret);
}


// FCOMENPROPCADENA(CODCOMEN,TIPOCOMEN,PROPIEDAD)
VDEXPORT int fcomenpropcadena(bloques *b,ftrigers *ft)
{ 
  int ret,numcampo;
  char campocomen[MAXNOMBREV10]="";
  char *comentario;
  vdcomens com;

  if (ft->nparam<3) {
    mensajefcm(10,"Pocos parametros en FCOMENPROCADENA nos pasan %d y necesitamos 3\n "
                  "CODCOMEN,TIPOCOMEN,CAMPO DONDE ALMACENA LA PROPIEDAD",
        ft->nparam);
		return(-1);    
  } 
 
  memset(&com,0,sizeof(com));

  // coge el campo para meter comentarios
  numcampo=damecampo(b, ft->param[2]);
	if (numcampo<0) {
		mensajefcm(10,"No existe campo %s en fdamecomen",ft->param[2]);
		return(-1);
	}
  comentario=direcncampo(b,ft->param[2]);

 
  dameparametro(b,ft,0, V10CADENA, campocomen);
  numcampo=damecampo(b, campocomen);
  if (numcampo<0) {
	  mensajefcm(10,"No existe campo %s en fdamecomen",campocomen);
		return(-1);
  } 
  com.codcomen=*((long *)direcncampo(b,campocomen));
  dameparametro(b,ft,1, V10CADENA, com.tipocomen);
  ret=v10comenpropcadena(com.codcomen,com.tipocomen,comentario);
  return(ret);
}

// FCOMENPROPENTERO(CODCOMEN,TIPOCOMEN,PROPIEDAD)
VDEXPORT int fcomenpropentero(bloques *b,ftrigers *ft)
{ 
  int ret,numcampo;
  char campocomen[MAXNOMBREV10]="";
  long *valor;
  vdcomens com;

  if (ft->nparam<3) {
    mensajefcm(10,"Pocos parametros en FCOMENPROPENTERO nos pasan %d y necesitamos 3\n "
                  "CODCOMEN,TIPOCOMEN,CAMPO DONDE ALMACENA LA PROPIEDAD",
        ft->nparam);
		return(-1);    
  } 
 
  memset(&com,0,sizeof(com));

  // coge el campo para meter comentarios
  numcampo=damecampo(b, ft->param[2]);
	if (numcampo<0) {
		mensajefcm(10,"No existe campo %s en fdamecomen",ft->param[2]);
		return(-1);
	}
  valor=(long *)direcncampo(b,ft->param[2]);

 
  dameparametro(b,ft,0, V10CADENA, campocomen);
  numcampo=damecampo(b, campocomen);
  if (numcampo<0) {
	  mensajefcm(10,"No existe campo %s en fdamecomen",campocomen);
		return(-1);
  } 
  com.codcomen=*((long *)direcncampo(b,campocomen));
  dameparametro(b,ft,1, V10CADENA, com.tipocomen);
  ret=v10comenpropentero(com.codcomen,com.tipocomen,valor);
  return(ret);
}


void initvdcomenformtrig(void) {
	declaratriger("FCREACOMEN",fcreacomen,NULL);
	declaratriger("FCREACOMENRELOGIN",fcreacomenrelogin,NULL);
	declaratriger("FDAMECOMEN",fdamecomen,NULL);
    declaratriger("FBORRACOMENPORTIPO",fborracomenportipo,NULL);
    declaratriger("FCOMENPROPCADENA",fcomenpropcadena,NULL);
    declaratriger("FCOMENPROPENTERO",fcomenpropentero,NULL);
}
