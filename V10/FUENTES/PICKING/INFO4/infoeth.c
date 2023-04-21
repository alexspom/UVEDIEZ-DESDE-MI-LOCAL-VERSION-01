#include "infopc.h"

#define TIPODISPPARTIDO   1
//#define TIPODISPLINEAL    2

#define TSTATLINEA    100
#define LENSTDISP     (sizeof(char)+4*sizeof(long)+sizeof(long)+sizeof(char)+sizeof(char))
#define LENESTDISP    (sizeof(char)+sizeof(long)+sizeof(long)+sizeof(char))
#define LENSTLIN      (11*sizeof(long)+(2+MAXLUCESDISPLAY)*sizeof(char))
#define LENVERSION    (sizeof(long))
#define LENMANDACONF  (sizeof(char)+sizeof(long)*5)

int modotest=0;


int pdisplin(ethlineas *lin)
{
	int i, j, ndglob;
	etherboxs *mieth = lin->eth;
	ndglob = ((mieth - eth) * 100 + (lin - mieth->lin)) * 1000 + 1;
	return(ndglob);
}

static void initethlinea(ethlineas *lin,int tciclo,int tenvtrama,int timeouttrama,int timeoutwho,int limitacionlinea)
{
   char servicio[MAXPATH];
   int ndglob = pdisplin(lin);
   int nd;
   if (modotest) {
       sprintf(servicio, "TEST%d", lin - lin->eth->lin);
   } else {
   sprintf(servicio,"LINEA%d",lin-lin->eth->lin);
   }
   lin->vds=creacliente(lin->eth->dirip,servicio);
   lin->tciclo=tciclo;
   lin->limitacionlinea=limitacionlinea;
   lin->tenvtrama=tenvtrama;
   lin->timeouttrama=timeouttrama;
   lin->timeoutwho=timeoutwho;
   for (nd = 0; nd < MAXDISPLAYS; nd++) lin->disp[nd].numdisp = ndglob + nd;
}

void initeth(etherboxs *eth,int tciclo,int tenvtrama,int timeouttrama,int timeoutwho,int limitacionlinea,char *rangolineas)
{
	int i;
	for (i = 0; i<MAXLINEAS; i++) {
		eth->lin[i].eth = eth;
		if (contienenum(rangolineas, i)>0) {
			initethlinea(eth->lin + i, tciclo, tenvtrama, timeouttrama, timeoutwho, limitacionlinea);
		}
	}
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
	int i, j;
	*neth = ndisp / 100000;
	*nlin = (ndisp / 1000) % 100;
	*numdisp = ndisp % 1000;
	return(0);
}

static void mandacomandoethlin(ethlineas *lin,char *buffer,int lon)
{
  char buflog[MAXCADENA],*ptr;
  int i;
  if (lon==0) return;
  v10log(LOGDEBUG,"Mandando comando a linea %d longitud %d\n",dimelin(lin),lon);
  ptr=buflog;
  for (i=0;i<lon;i++) ptr+=sprintf(ptr,"%02x ",buffer[i]);
  sendvdsocket(lin->vds,buffer,lon);
  v10log(LOGDEBUG,"%s\n",buflog);
}


static void modificatodos(ethlineas *lin)
{
  int i,ndglob;
  ndglob=pdisplin(lin);
  for (i=0;i<lin->numdisp;i++) {
      displays *disp=damedisplayid(ndglob+i);
      disp->modificado=1;
  }
}


static void tratacomandoest(ethlineas *lin)
{
  int numdisp,ret,i,ndglob;
  char buffer[MAXDISPLAYS*LENESTDISP],*ptr;
  ndglob=pdisplin(lin);
  numdisp=sigcarsocket(lin->vds);
  if (numdisp<0) return;
  MODIFICADOINFO++;
  lin->numdisp=numdisp;
  v10log(LOGNORMAL,"Cambiada estructura de linea %d displays %d\n",dimelin(lin),numdisp);
  ret=leebufsocketw(lin->vds,buffer,numdisp*LENESTDISP);
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
	  pdisp = damedisplayid(ndglob + i);
      pdisp->status[0]=(char)st;
      pdisp->version=version;
	  pdisp->modifstatus=1;
	  pdisp->numdisp = ndglob + i;
      v10log(LOGNORMAL,"  Display %d serie %ld tipo %d status %x\n",ndglob+i,serie,tipod,st);
  }
  modificatodos(lin);
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
  numdisp=sigcarsocket(lin->vds);
  if (numdisp<0) return;
  ret=leebufsocketw(lin->vds,buffer,LENSTDISP);
  if (ret<LENSTDISP) {
     v10log(LOGERROR,"Recibido de display trama corta %d\n",ret);
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
     v10log(LOGERROR,"Recibido de display %d serie %ld status %x cuando linea solo tiene %d displays\n",numdisp,serie,st,lin->numdisp);
     closesocket(lin->vds->soc);
     v10log(LOGDEBUG,"socket cerrado por recibir display demasiado alto\n");
     lin->vds->status=STSOCKCERRADO;
     return;
   }
  pdisp = damedisplayid(ndglob + numdisp);
  pdisp->version=version;
  pdisp->errhard=errhard;
  pdisp->errtrama=errtrama;
  pdisp->consumo=consumo;
  verificastatus(pdisp,st);
  v10log(LOGDEBUG,"Recibido de display %d serie %ld tipo %d status %x\n",ndglob+numdisp,serie,tipod,st);
}

static void tratacomandostlin(ethlineas *lin)
{
  int numdisp;
  int ret,i;
  char buffer[LENSTLIN],*ptr;
  numdisp=sigcarsocket(lin->vds);
  if (numdisp<0) return;
  ret=leebufsocketw(lin->vds,buffer,LENSTLIN);
  if (ret<LENSTLIN) {
     v10log(LOGERROR,"Recibido de display trama corta %d\n",ret);
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
  v10log(LOGDEBUG,"Recibido de linea %d Displays %d status %x tramas %ld %ld bytes %ld %ld bucles %ld Creadas %ld Ida %ld reconexiones %ld Status %d %x\n",dimelin(lin),numdisp,lin->stglob,lin->tramasida,lin->tramasvuelta,lin->bytesida,lin->bytesvuelta,lin->bucles,lin->creatramas,lin->lonida,lin->reconexiones,lin->stcon,lin->stglob);
  if (lin->numdisp!= numdisp) {
      v10log(LOGERROR,"Recibido de linea %d trama con numero de displays %d diferente al esperado %d\n",dimelin(lin),numdisp,lin->numdisp);
      closesocket(lin->vds->soc);
      lin->vds->status=STSOCKCERRADO;
  }
  MODIFICADOINFO++;
}

static void tratacomandoversion(ethlineas *lin)
{
  unsigned long version;
  char buffer[LENVERSION],*ptr;
  leebufsocketw(lin->vds,buffer,LENVERSION);
  ptr=buffer;
  recogelong(ptr,&version);
  lin->version=lin->eth->version=version;
  v10log(LOGDEBUG,"Recibido de linea Version %s\n",infodameversion(lin->version));;
  MODIFICADOINFO++;
}

void pidestatusdisp(ethlineas *lin,int numdisp)
{
   char buffer[20],*ptr=buffer;
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

void traduceeco(char *origen, char *destino)
{
	int ncad, i;
	if (*origen != '@') {
		strcpy(destino, origen);
		return;
	}
	origen++;
	ncad = numpieces(origen, "@");
	for (i = 0; i < ncad; i++) {
		char parte[MAXPATH];
		int font = 1, posx = 1, posy = 1;
		char valor[MAXPATH];
		int nparam;
		piece(origen, parte, "@", i + 1);
		nparam = numpieces(parte, ",");
		if (nparam > 1) {
			piece(parte, valor, ",", 2);
			font = atoi(valor);
			if (nparam > 2) {
				piece(parte, valor, ",", 3);
				posx = atoi(valor);
				if (nparam > 3) {
					piece(parte, valor, ",", 4);
					posy = atoi(valor);
				}
			}
		}
		piece(parte, valor, ",", 1);
		sprintf(destino, "%c%c%c%s\005", font, posx, posy, valor);
		destino += strlen(destino);
	}
	strcpy(destino, "\006");
}

static void enviamodificaciones(ethlineas *lin)
{
  int i,ndglob,nl;
	char buffer[MAXCADENA], *ptr, destino[MAXDIGDISPLAY];
  if (lin->vds->status!=STSOCKABIERTO) return;
  ndglob=pdisplin(lin);
  ptr=buffer;
  for (i=0;i<lin->numdisp;i++) {
      displays *disp=damedisplayid(ndglob+i);
      if (disp->modificado) {
         disp->modificado=0;
         *ptr++=PONDISP;
         *ptr++=(char)i;
			traduceeco(disp->valor, destino);
			*ptr ++= (char)strlen(destino);
			ptr += sprintf(ptr, "%s", destino);
         *ptr++=MAXLUCESDISPLAY;
         for (nl=0;nl<MAXLUCESDISPLAY;nl++)
             ptr=mandashort(ptr,disp->luces[nl]);
         v10log(LOGDEBUG,"Enviada modificacion a display %d serie %ld valor %s bytes %d\n",ndglob+i,disp->serie,disp->valor,ptr-buffer);
      }
  }
  mandacomandoethlin(lin,buffer,ptr-buffer);
}

static void pidestatusethlinea(ethlineas *lin)
{
  char buffer=STATUSLIN;
  if (lin->vds==NULL) return;
  if (lin->vds->status!=STSOCKABIERTO) return;
  mandacomandoethlin(lin,&buffer,1);
}


static void tickethlinea(ethlineas *lin)
{
   int ret;
   if (lin->vds==NULL) return;
   verificasocket(lin->vds);
   if (lin->vds->status==STSOCKCERRADO) {
      modificatodos(lin);
      reabrecliente(lin->vds);
      lin->initlinea=0;
      return;
    }
   if (lin->vds->status==STSOCKABIERTO && lin->initlinea==0) {
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
   if (haycarsocket(lin->vds)) {
      ret=sigcarsocket(lin->vds);
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

/*void pidestatuseth(etherboxs *eth)
{
   int i;
   for (i=0;i<MAXLINEAS;i++) {
       pidestatusethlinea(eth->lin+i);
    }
}*/

