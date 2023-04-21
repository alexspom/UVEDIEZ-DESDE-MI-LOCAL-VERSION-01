/*
* Módulo : EOSETH.C
* Objeto: Tratamiento de las ethernet box sistema EOS
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-12-2007

* MODIFICACIONES
* --
*/
#include "eospc.h"

#define TIPODISPPARTIDO   1
#define TIPODISPLINEAL    2

int TSTATLINEA=100;
#define LENSTDISP     (sizeof(char)+4*sizeof(long)+sizeof(long)+sizeof(char)+sizeof(char))
#define LENESTDISP    (sizeof(char)+sizeof(long)+sizeof(long)+sizeof(char))
#define LENSTLIN      (11*sizeof(long)+(2+MAXLUCESDISPLAY)*sizeof(char))
#define LENVERSION    (sizeof(long))
#define LENMANDACONF  (sizeof(char)+sizeof(long)*5)

int modotest=0;
int tipodispfisico=TIPODISPPARTIDO;

static void initethlinea(ethlineas *lin,int tciclo,int tenvtrama,int timeouttrama,int timeoutwho,int limitacionlinea)
{
   char servicio[MAXPATH];
   sprintf(servicio,"LINEA%d",lin-lin->eth->lin);
   lin->v10s=creacliente(lin->eth->dirip,servicio);
   lin->tciclo=tciclo;
   lin->limitacionlinea=limitacionlinea;
   lin->tenvtrama=tenvtrama;
   lin->timeouttrama=timeouttrama;
   lin->timeoutwho=timeoutwho;
}

void initeth(etherboxs *eth,int tciclo,int tenvtrama,int timeouttrama,int timeoutwho,int limitacionlinea)
{
  int i;
  for (i=0;i<MAXLINEAS;i++) {
      eth->lin[i].eth=eth;
      initethlinea(eth->lin+i,tciclo,tenvtrama,timeouttrama,timeoutwho,limitacionlinea);
   }
}

int pdisplin(ethlineas *lin)
{
  int i,j,ndglob;
  etherboxs *mieth=lin->eth;
  if (tipodispfisico==TIPODISPPARTIDO) {
     ndglob=((mieth-eth)*100+(lin-mieth->lin))*1000+1;
     return(ndglob);
   }
  ndglob=1;
  for (i=0;eth+i<mieth;i++) {
      for (j=0;j<MAXLINEAS;j++) ndglob+=eth[i].lin[j].numdisp;
   }
  for (j=0;mieth->lin+j<lin;j++)  ndglob+=mieth->lin[j].numdisp;
  return(ndglob);
}

static int dimelin(ethlineas *lin)
{
  int i,j,nlin;
  etherboxs *mieth=lin->eth;
  nlin=0;
  for (i=0;eth+i<mieth;i++) {
      for (j=0;j<MAXLINEAS;j++) nlin++;
   }
  for (j=0;mieth->lin+j<lin;j++)  nlin++;
  return(nlin);
}

int dimedatosdisp(int ndisp,int *neth,int *nlin,int *numdisp)
{
  int i,j;
  if (tipodispfisico==TIPODISPPARTIDO) {
     *neth=ndisp/100000;
     *nlin=(ndisp/1000)%100;
     *numdisp=ndisp%1000;
     return(0);
   }
  for (i=0;i<numetherbox;i++) {
      for (j=0;j<MAXLINEAS;j++) {
          if (ndisp<=eth[i].lin[j].numdisp) {
             *neth=i;
             *nlin=j;
             *numdisp=ndisp;
             return(0);
           }
          ndisp-=eth[i].lin[j].numdisp;
       }
   }
  return(-1);
}

static void mandacomandoethlin(ethlineas *lin,char *buffer,int lon)
{
  char buflog[MAXCADENA*10],*ptr;
  int i;
  if (lon==0) return;
  escribe_log(LOGDEPURATRAMA,"Mandando comando %X a linea %d longitud %d\n",buffer[0], dimelin(lin),lon);
  ptr=buflog;
  for (i=0;i<lon;i++) ptr+=sprintf(ptr,"%02x ",buffer[i]);
  sendv10socket(lin->v10s,buffer,lon);
  escribe_log(LOGDEPURATRAMA,"%s\n",buflog);
}


static void modificatodos(ethlineas *lin)
{
  int i,ndglob;
  ndglob=pdisplin(lin);
  for (i=0;i<lin->numdisp;i++) {
      displays *disp=damedisplayid(TIPOIDNUMDISP,ndglob+i);
      disp->modificado=1;
  }
}

static void tratacomandoest(ethlineas *lin)
{
  int numdisp,ret,i,ndglob;
  char buffer[MAXDISPLAYS*LENESTDISP],*ptr;
  ndglob=pdisplin(lin);
  numdisp=sigcarsocket(lin->v10s);
  if (numdisp<0) return;
  MODIFICADOINFO++;
  if (numdisp!=lin->numdisp && tipodispfisico!=TIPODISPPARTIDO) {
     cambianumdisp(ndglob,lin->numdisp,numdisp);
   }
  lin->numdisp=numdisp;
  escribe_log(LOGNORMAL,"Cambiada estructura de linea %d displays %d\n",dimelin(lin),numdisp);
  ret=leebufsocketw(lin->v10s,buffer,numdisp*LENESTDISP);
  if (ret<numdisp*LENESTDISP) return;
  ptr=buffer;
  for (i=0;i<numdisp;i++) {
      int tipod,st;
      unsigned long serie,version;
      displays *pdisp;
      tipod=*ptr++;
      ptr=recogelong(ptr,&serie);
      ptr=recogelong(ptr,&version);
      st=*ptr++;
      pdisp=revisadisp(serie,ndglob+i,tipod);
      pdisp->status[0]=(char)st;
      pdisp->version=version;
      escribe_log(LOGNORMAL,"  Display %d serie %ld tipo %d status %x\n",ndglob+i,serie,tipod,st);
  }
  modificatodos(lin);
//  lin->initlinea=0;
}

static void verificastatus(displays *pdisp,int st)
{
  if (st!=pdisp->status[0]) {
     int botones=st&0xff,antbot=pdisp->status[0]&0xff;
     if (botones!=antbot) {
        int i;
        for (i=0;i<MAXBOTONESDISPLAY;i++) {
            if ((botones&(1<<i))!=(antbot&(1<<i)) && (botones&(1<<i))) {
               encolatecladispp(pdisp,i,CAUSAOPER);
             }
         }
      }
  }
  pdisp->status[0]=(char)st;
  pdisp->modifstatus=1;
}

static void tratacomandost(ethlineas *lin)
{
  int numdisp,ret,ndglob;
  int tipod,st;
  unsigned long serie,version,errhard,errtrama,consumo;
  char buffer[LENSTDISP],*ptr;
  displays *pdisp;
  MODIFICADOINFO++;
  ndglob=pdisplin(lin);
  numdisp=sigcarsocket(lin->v10s);
  if (numdisp<0) return;
  ret=leebufsocketw(lin->v10s,buffer,LENSTDISP);
  if (ret<LENSTDISP) {
     escribe_log(LOGERROR,"Recibido de display trama corta %d\n",ret);
     return;
   }
  ptr=buffer;
  tipod=*ptr++;
  ptr=recogelong(ptr,&serie);
  ptr=recogelong(ptr,&version);
  ptr=recogelong(ptr,&errhard);
  ptr=recogelong(ptr,&errtrama);
  ptr=recogelong(ptr,&consumo);
  ptr++;
  st=*ptr;
  if (numdisp>=lin->numdisp) {
     escribe_log(LOGERROR,"Recibido de display %d serie %ld status %x cuando linea solo tiene %d displays\n",numdisp,serie,st,lin->numdisp);
     return;
   }
  pdisp=revisadisp(serie,ndglob+numdisp,tipod);
  pdisp->version=version;
  pdisp->errhard=errhard;
  pdisp->errtrama=errtrama;
  pdisp->consumo=consumo;
  verificastatus(pdisp,st);
  escribe_log(LOGDEPURATRAMA,"Recibido de display %d serie %ld tipo %d status %x\n",ndglob+numdisp,serie,tipod,st);
}

static void tratacomandostlin(ethlineas *lin)
{
  int numdisp;
  int ret,i;
  char buffer[LENSTLIN],*ptr;
  numdisp=sigcarsocket(lin->v10s);
  if (numdisp<0) return;
  ret=leebufsocketw(lin->v10s,buffer,LENSTLIN);
  if (ret<LENSTLIN) {
     escribe_log(LOGERROR,"Recibido de display trama corta %d\n",ret);
     return;
   }
  ptr=buffer;
  ptr=recogelong(ptr,&lin->tramasida);
  ptr=recogelong(ptr,&lin->tramasvuelta);
  ptr=recogelong(ptr,&lin->bytesida);
  ptr=recogelong(ptr,&lin->bytesvuelta);
  ptr=recogelong(ptr,&lin->bucles);
  ptr=recogelong(ptr,&lin->reconexiones);
  ptr=recogelong(ptr,&lin->creatramas);
  ptr=recogelong(ptr,&lin->lonida);
  ptr=recogelong(ptr,&lin->errtrama);
  ptr=recogelong(ptr,&lin->consumo);
  ptr=recogelong(ptr,&lin->consumo232);
  for (i=0;i<MAXLUCESDISPLAY;i++) lin->ciclotrabajo[i]=*ptr++;
  lin->stglob=*ptr++;
  lin->stcon=*ptr;
  escribe_log(LOGDEPURATRAMA,"Recibido de linea %d Displays %d status %x tramas %ld %ld bytes %ld %ld bucles %ld Creadas %ld Ida %ld reconexiones %ld Status %d %x\n",dimelin(lin),numdisp,lin->stglob,lin->tramasida,lin->tramasvuelta,lin->bytesida,lin->bytesvuelta,lin->bucles,lin->creatramas,lin->lonida,lin->reconexiones,lin->stcon,lin->stglob);
  MODIFICADOINFO++;
}

static void tratacomandoversion(ethlineas *lin)
{
  unsigned long version;
  char buffer[LENVERSION],*ptr;
  leebufsocketw(lin->v10s,buffer,LENVERSION);
  ptr=buffer;
  recogelong(ptr,&version);
  lin->version=lin->eth->version=version;
  escribe_log(LOGDEPURATRAMA,"Recibido de linea Version %s\n",infodameversion(lin->version));;
  MODIFICADOINFO++;
}

void pidestatusdisp(ethlineas *lin,int numdisp)
{
   char buffer[MAXCADENA],*ptr=buffer;
   *ptr++=STATUSDISP;
   *ptr++=(char)numdisp;
   mandacomandoethlin(lin,buffer,ptr-buffer);
}

static void mandaconf(ethlineas *lin)
{
   char buffer[LENMANDACONF],*ptr=buffer;
   *ptr++=MANDACONF;                       
   ptr=mandalong(ptr,lin->limitacionlinea);
   ptr=mandalong(ptr,lin->tciclo);
   ptr=mandalong(ptr,lin->tenvtrama);
   ptr=mandalong(ptr,lin->timeouttrama);
   ptr=mandalong(ptr,lin->timeoutwho);
   mandacomandoethlin(lin,buffer,ptr-buffer);
}

static void enviamodificaciones(ethlineas *lin)
{
  int i,ndglob,nl;
  char buffer[MAXCADENA],*ptr;
  if (lin->v10s->status!=STSOCKABIERTO) return;
  ndglob=pdisplin(lin);
  ptr=buffer;
  for (i=0;i<lin->numdisp;i++) {
      displays *disp=damedisplayid(TIPOIDNUMDISP,ndglob+i);
      if (disp->modificado) {
         disp->modificado=0;
         *ptr++=PONDISP;
         *ptr++=(char)i;
         *ptr++=(char)strlen(disp->valor);
         ptr+=sprintf(ptr,"%s",disp->valor);
         *ptr++=MAXLUCESDISPLAY;
         for (nl=0;nl<MAXLUCESDISPLAY;nl++)
             ptr=mandashort(ptr,disp->luces[nl]);
         escribe_log(LOGDEPURATRAMA,"Enviada modificacion a display %d serie %ld valor %s bytes %d\n",ndglob+i,disp->serie,disp->valor,ptr-buffer);
      }
  }
  mandacomandoethlin(lin,buffer,ptr-buffer);
  if (lin->velmodificado) {
	memset (buffer, 0, MAXCADENA);
	ptr=buffer;
	*ptr++=DIRYVEL;
	*ptr++=lin->velocidad;
	escribe_log(LOGNORMAL,"Enviada velocidad de linea %d serie %X\n",lin->port,lin->velocidad);
	mandacomandoethlin(lin,buffer,ptr-buffer);
	lin->velmodificado = 0;
  }
}

static void pidestatusethlinea(ethlineas *lin)
{
  char buffer=STATUSLIN;
  if (lin->v10s==NULL) return;
  if (lin->v10s->status!=STSOCKABIERTO) return;
  mandacomandoethlin(lin,&buffer,1);
}


static void tickethlinea(ethlineas *lin)
{
   int ret;
   if (lin->v10s==NULL) return;
   verificasocket(lin->v10s);
   if (lin->v10s->status==STSOCKCERRADO) {
      modificatodos(lin);
      reabrecliente(lin->v10s);
      lin->initlinea=0;
      return;
    }
   if (lin->v10s->status==STSOCKABIERTO && lin->initlinea==0) {
      char buffer[2]={PONMODOTEST};
      buffer[1]=(char)modotest;
      mandacomandoethlin(lin,buffer,2);
      lin->initlinea=1;
      mandaconf(lin);
    }
   if (damecent()-lin->hultstat>TSTATLINEA) {
      pidestatusethlinea(lin);
      lin->hultstat=damecent();
    }
   if (haycarsocket(lin->v10s)) {
      ret=sigcarsocket(lin->v10s);
      switch (ret) {
         case RESPVERSION:tratacomandoversion(lin);
                          break;
         case RESPESTLIN:tratacomandoest(lin);
                         break;
         case RESPSTDISP:tratacomandost(lin);
                         break;
         case RESPSTLIN:tratacomandostlin(lin);
                        break;
      }
   }
   enviamodificaciones(lin);
}

void ticketh(etherboxs *eth)
{
   int i;
   for (i=0;i<MAXLINEAS;i++) {
       tickethlinea(eth->lin+i);
    }
}

void pidestatuseth(etherboxs *eth)
{
   int i;
   for (i=0;i<MAXLINEAS;i++) {
       pidestatusethlinea(eth->lin+i);
    }
}

