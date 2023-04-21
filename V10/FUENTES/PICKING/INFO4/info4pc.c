#include "info4.h"

#define LMANDACONF   (sizeof(long)*5)


static void mandaAPC(int comando, int display, infolineas *linea)
{
	unsigned char *p, cadena[MAXCADENA];
	int i,numbytes;
    char stglob;
    infodisps *disp;
	p=cadena;
	switch (comando){
      case RESPVERSION:
           *p++=RESPVERSION;
           p=mandalong(p,version);
           break;
		case RESPSTDISP:
			*p++=RESPSTDISP; // Comando
				// 01 -> Respuesta de display
         disp=linea->disp+display;
         *p++=(char)display;
         *p++=(char)disp->tipo;
         p=mandalong(p,disp->serie);
         p=mandalong(p,disp->version);
         p=mandalong(p,disp->errhard);
         p=mandalong(p,disp->errtrama);
         p=mandalong(p,disp->consumo);
         *p++=1;
         *p++=disp->status[0];
			break;
      case RESPESTLIN:
         *p++=RESPESTLIN;
         *p++=(char)linea->numdisp;
         for (i=0;i<linea->numdisp;i++) {
             disp=linea->disp+i;
             *p++=(char)disp->tipo;
             p=mandalong(p,disp->serie);
             p=mandalong(p,disp->version);
             *p++=disp->status[0];
          }
         break;
      case RESPSTLIN:
         *p++=RESPSTLIN;
         *p++=(char)linea->numdisp;
         p=mandalong(p,linea->tramasida);
         p=mandalong(p,linea->tramasvuelta);
         p=mandalong(p,linea->bytesida);
         p=mandalong(p,linea->bytesvuelta);
         p=mandalong(p,linea->bucles);
         p=mandalong(p,linea->reconexiones);
         p=mandalong(p,linea->creatramas);
         p=mandalong(p,linea->lonida);
         p=mandalong(p,linea->errtrama);
         p=mandalong(p,linea->consumo);
         p=mandalong(p,linea->consumo232);
         for (i=0;i<MAXLUCESDISPLAY;i++) *p++=(char)linea->ciclotrabajo[i];
         stglob=0;
         for (i=0;i<linea->numdisp;i++) {
             disp=linea->disp+i;
             stglob|=disp->status[0];
          }
         *p++=stglob;
         if (linea->vds) {
            *p++=(char)linea->vds->status;
          } else *p++=0;
         break;
	}
   numbytes=p-cadena;
   if (numbytes) sendvdsocket(linea->vds,cadena,numbytes);
}

static void tratapondisp(infolineas *linea)
{
  int numdisp,ret,lcad,nl,i;
  char buffer[MAXDIGDISPLAY],luces[MAXLUCESDISPLAY*sizeof(short)],*ptr;
  numdisp=sigcarsocket(linea->vds);
  if (numdisp<0) return;
  lcad=sigcarsocket(linea->vds);
  if (lcad<0) return;
  ret=leebufsocket(linea->vds,buffer,lcad);
  buffer[ret]=0;
  nl=sigcarsocket(linea->vds);
  if (nl<0) return;
  ret=leebufsocket(linea->vds,luces,nl*sizeof(short));
  ptr=luces;
  for (i=0;i<ret/sizeof(short);i++) {
      unsigned short luz;
      ptr=recogeshort(ptr,&luz);
      linponlucesdisplay(linea,numdisp,i,luz);
   }
  lindisplayprintf(linea,numdisp,"%s",buffer);
}

static void tratastlin(infolineas *linea)
{
  mandaAPC(RESPSTLIN, 0, linea);
}

static void tratastdisp(infolineas *linea)
{
  int numdisp;
  numdisp=sigcarsocket(linea->vds);
  mandaAPC(RESPSTDISP,numdisp, linea);
}

static void tratamodotest(infolineas *linea)
{
  int modotest;
  modotest=sigcarsocket(linea->vds);
  if (linea->modotest!=modotest) {
     linea->recwho=WHOPEND;
     linea->modotest=modotest;
   }
  v10log(LOGNORMAL,"Recibido PC modotest %d\n",linea->modotest);
}

static void trataparopuerto(infolineas *linea)
{
  linea->paropuerto=sigcarsocket(linea->vds);
  if (linea->recwho>=WHOREC) linea->recwho=WHOPEND;
  v10log(LOGNORMAL,"Recibido PC paro puerto %d\n",linea->paropuerto);
}

static void tratamandaconf(infolineas *linea)
{
  char buffer[LMANDACONF],*ptr=buffer;
  int ret;
  ret=leebufsocket(linea->vds,buffer,LMANDACONF);
  ptr=recogelong(ptr,&linea->limitacionlinea);
  ptr=recogelong(ptr,&linea->tciclo);
  ptr=recogelong(ptr,&linea->tenvtrama);
  ptr=recogelong(ptr,&linea->timeouttrama);
  recogelong(ptr,&linea->timeoutwho);
  v10log(LOGNORMAL,"Recibido PC configuracion limitacion %ld tciclo %ld tenvtrama %ld timeouttrama %ld timeoutwho %ld\n",
                          linea->limitacionlinea,linea->tciclo,linea->tenvtrama,linea->timeouttrama,linea->timeoutwho);
}

void automatapc(infolineas *linea)
{
	int i;
   if (linea->vds==NULL) return;
   verificasocket(linea->vds);
   if (linea->modifestrucpc && linea->vds->status==STSOCKABIERTO) {
      linea->modifestruc=1;
      linea->modifestrucpc=0;
      linea->reconexiones++;
      mandaAPC(RESPVERSION,0,linea);
    }
   if (linea->vds->status==STSOCKCERRADO) {
      reabreservidor(linea->vds);
      linea->modifestrucpc=1;
    }
   if (vdslog) {
      if (vdslog->status==STSOCKCERRADO) {
         reabreservidor(vdslog);
       }
    }
	if (linea->modifestruc && linea->recwho>=WHOREC) {
		v10log(LOGNORMAL,"Linea modificada numero de displays %d\n",linea->numdisp);
		linea->modifestruc=0;
		mandaAPC(RESPESTLIN, 0, linea);
		v10log(LOGNORMAL,"Mandado mensaje de estructura de linea\n");
	}
	if (linea->modifvuelta && linea->recwho>=WHOREC) {
		for (i=0;i<linea->numdisp;i++) {
			infodisps *di=linea->disp+i;
         if (di->tipodisp==NULL) continue;
			if (di->modifvuelta)	{
				v10log(LOGNORMAL,"Display %d modificado nuevo estatus %x\n",i,*di->status);
				mandaAPC(RESPSTDISP, i, linea);
				di->modifvuelta=0;
			}
		}
   	linea->modifvuelta=0;
	}
  while (haycarsocket(linea->vds)) {
      int ret;
      ret=sigcarsocket(linea->vds);
      switch (ret) {
         case STATUSLIN:tratastlin(linea);
                         break;
         case STATUSDISP:tratastdisp(linea);
                         break;
         case PONDISP:tratapondisp(linea);
                         break;
         case PONMODOTEST:tratamodotest(linea);
                          break;
         case PAROPUERTO: trataparopuerto(linea);
                          break;
         case MANDACONF:  tratamandaconf(linea);
                          break;
      }
   }
}
