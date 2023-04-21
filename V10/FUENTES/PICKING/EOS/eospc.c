#include "eos.h"

#define LENPONDISP   (MAXDIGDISPLAY+sizeof(char))
#define LMANDACONF   (sizeof(long)*5)

//REvisar esto.
static void mandaAPC(int comando, int display, eoslineas *linea)
{
   unsigned char *p, cadena[MAXCADENA];
   int i,numbytes;
   char stglob;
   eosdisps *disp;
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
         if (linea->v10s) {
            *p++=(char)linea->v10s->status;
          } else *p++=0;
         break;
	}
   numbytes=p-cadena;
   if (numbytes) sendv10socket(linea->v10s,cadena,numbytes);
}

static void tratapondisp(eoslineas *linea)
{
  int numdisp,ret,lcad,nl,i;
  char buffer[MAXDIGDISPLAY],luces[MAXLUCESDISPLAY*sizeof(short)],*ptr;
  numdisp=sigcarsocketw(linea->v10s);
  if (numdisp<0) {
        escribe_log(LOGERROR,"Error al recibir numdisp\n");
        return;
    }
  lcad=sigcarsocketw(linea->v10s);
  if (lcad<0) return;
  ret=leebufsocketw(linea->v10s,buffer,lcad);
  if (ret<lcad) return;
  buffer[ret]=0;
  escribe_log(LOGNORMAL,"Recibido pon disp para display %d %s lon %d\n",numdisp,buffer,strlen(buffer));
  nl=sigcarsocketw(linea->v10s);
  if (nl<0) return;
  ret=leebufsocketw(linea->v10s,luces,nl*sizeof(short));
  if (ret<nl*sizeof(short));
  ptr=luces;
  for (i=0;i<ret/sizeof(short);i++) {
      unsigned short luz;
      ptr=recogeshort(ptr,&luz);
      linponlucesdisplay(linea,numdisp,i,luz);
   }
//  escribe_log(LOGDEPURA,"Recibido de pc display %d valor %-*s\n",numdisp,MAXDIGDISPLAY,buffer);
  lindisplayprintf(linea,numdisp,"%s",buffer);
}


static void tratastlin(eoslineas *linea)
{
  mandaAPC(RESPSTLIN, 0, linea);
}

static void tratastdisp(eoslineas *linea)
{
  int numdisp;
  numdisp=sigcarsocketw(linea->v10s);
  if (numdisp<0) return;
  mandaAPC(RESPSTDISP,numdisp, linea);
}

static void tratamodotest(eoslineas *linea)
{
  int modotest;
  modotest=sigcarsocketw(linea->v10s);
  if (modotest<0) return;
  if (linea->modotest!=modotest) {
     linea->recwho=WHOPEND;
     linea->modotest=modotest;
   }
  escribe_log(LOGNORMAL,"Recibido PC modotest %d\n",linea->modotest);
}

static void trataparopuerto(eoslineas *linea)
{
  int ret;
  ret=sigcarsocketw(linea->v10s);
  if (ret<0) return;
  linea->paropuerto=ret;
  //linea->paropuerto=sigcarsocket(linea->v10s);
  if (linea->recwho>=WHOREC) linea->recwho=WHOPEND;
  escribe_log(LOGNORMAL,"Recibido PC paro puerto %d\n",linea->paropuerto);
}

static void tratamandaconf(eoslineas *linea)
{
  char buffer[LMANDACONF],*ptr=buffer;
  int ret;
  ret=leebufsocketw(linea->v10s,buffer,LMANDACONF);
  if (ret<0) return;
  ptr=recogelong(ptr,&linea->limitacionlinea);
  ptr=recogelong(ptr,&linea->tciclo);
  ptr=recogelong(ptr,&linea->tenvtrama);
  ptr=recogelong(ptr,&linea->timeouttrama);
  recogelong(ptr,&linea->timeoutwho);
  escribe_log(LOGNORMAL,"Recibido PC configuracion limitacion %ld tciclo %ld tenvtrama %ld timeouttrama %ld timeoutwho %ld\n",
                          linea->limitacionlinea,linea->tciclo,linea->tenvtrama,linea->timeouttrama,linea->timeoutwho);
}

static void tratadiryvel(eoslineas *linea)
{
  linea->velocidad = sigcarsocket(linea->v10s);
  escribe_log(LOGNORMAL,"Recibido PC configuracion de velocidad de línea %X\n", linea->velocidad);
  linea->modifvel = 1;
}

void automatapc(eoslineas *linea)
{
   int i;
   if (linea->v10s==NULL) return;
   tratasocket(linea);
   if (linea->modifestrucpc && linea->v10s->status==STSOCKABIERTO) {
      linea->modifestruc=1;
      linea->modifestrucpc=0;
      linea->reconexiones++;
      mandaAPC(RESPVERSION,0,linea);
    }
   if (v10slog) {
      if (v10slog->status==STSOCKCERRADO) {
         reabreservidor(v10slog);
       }
    }
   if (linea->modifestruc /*&& linea->recwho>=WHOREC*/) {
      escribe_log(LOGNORMAL,"Linea modificada numero de displays %d\n",linea->numdisp);
      linea->modifestruc=0;
      mandaAPC(RESPESTLIN, 0, linea);
      escribe_log(LOGNORMAL,"Mandado mensaje de estructura de linea\n");
    }
   if (linea->modifvuelta && linea->recwho>=WHOREC) {
      for (i=0;i<linea->numdisp;i++) {
          eosdisps *di=linea->disp+i;
          if (di->tipodisp==NULL) continue;
          if (di->modifvuelta)	{
	      escribe_log(LOGNORMAL,"Display %d modificado nuevo estatus %x\n",i,*di->status);
              mandaAPC(RESPSTDISP, i, linea);
	      di->modifvuelta=0;
	   }
        }
      linea->modifvuelta=0;
    }
  while (haycarsocket(linea->v10s)) {
      int ret;
      ret=sigcarsocket(linea->v10s);
	  escribe_log(LOGNORMAL,"Recibido %d\n",ret);
      switch (ret) {
         case STATUSLIN:  tratastlin(linea);
                          break;
         case STATUSDISP: tratastdisp(linea);
                          break;
         case PONDISP:    tratapondisp(linea);
                          break;
         case PONMODOTEST:tratamodotest(linea);
                          break;
         case PAROPUERTO: trataparopuerto(linea);
                          break;
         case MANDACONF:  tratamandaconf(linea);
                          break;
	 case DIRYVEL:    tratadiryvel(linea);
			  break;
      }
   }
}
