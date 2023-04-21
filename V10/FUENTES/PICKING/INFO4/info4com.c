#include "info4.h"

#ifdef ColdFire
#define s2d(ret)   ((ret>>8)+((ret&0xff)<<8))
#else
#define s2d(ret) (ret)
#endif

#define SOLOLUZDIG   0X400

#define VERADMITEST1 0X30313036

#define STIDDLE    0
#define STRECINI   1
#define STCONFINI  2
#define STRECFIN   3
#define STCONFFIN  4

#define APAGADO    0
#define BLANCOLUZ  1
#define NUMERICO   2
#define ALFA       3

static char bufferida[MAXCADENA]="";
static char tramaida[MAXCADENA],*ptrtrama;

vdsockets *vdslog;

void initlinea(infolineas *linea)
{
  char servicio[MAXPATH];
  int i;
  linea->ptrvuelta=linea->tramavuelta;
  if (initpuerto232(linea->port,57600,NOPARITY,8,ONESTOPBIT)!=0) 
      final(("No puedo abrir puerto %d\n",linea->port+1));
  sprintf(servicio,"LINEA%d",linea->port);
  linea->vds=creaservidor(servicio);
  sprintf(servicio,"LOG%d",linea->port);
  vdslog=creaservidor(servicio);
  linea->modifestrucpc=1;
  linea->limitacionlinea=LIMITACIONLINEA;
  linea->tenvtrama=TENVTRAMA;
  linea->timeouttrama=TIMEOUTTRAMA;
  linea->timeoutwho=TIMEOUTWHO;
  linea->tramasnulas=TRAMASNULAS;
  linea->tciclo=TCICLO;
  linea->paropuerto=210;
  linea->hulttramavuelta=damecent();
  for (i=0;i<MAXLUCESDISPLAY;i++) linea->ciclotrabajo[i]=10;
}


static void writeport232(int port,char *buff,int tam)
{
  HANDLE hp=damepuerto232(port);
  DWORD escrito;
  WriteFile(hp,buff,tam,&escrito,NULL);
  if (escrito!=tam) {
     v10log(LOGERROR,"Error intento escribir %d bytes y escribo %d\n",tam,escrito);
   }
}


static void miencolae(int port,int ch)
{
  sprintf(bufferida+strlen(bufferida),"%02x ",ch);
  *ptrtrama++=(char)ch;
}

static void mandacomando(infolineas *linea,int comando,char *trama,int lon)
{
  char *ptr=trama;
  int port=linea->port;
  int check,i;
  char numcartrama;
  check=comando;
  strcpy(bufferida,"");
  ptrtrama=tramaida;
  miencolae(port,INITRAMA);
  miencolae(port,INITRAMA);
  miencolae(port,comando);
  miencolae(port,0x0);
  numcartrama=4;
  for (i=0;i<lon;i++) {
    check^=*ptr;
    numcartrama++;
    miencolae(port,*ptr++);
  }
  miencolae(port,INITRAMA);
  miencolae(port,FINTRAMA);
  check^=INITRAMA^FINTRAMA;
  numcartrama+=(char)3;
  check^=numcartrama;
  miencolae(port,check);
  writeport232(port,tramaida,ptrtrama-tramaida);
  linea->bytesida+=ptrtrama-tramaida;
  v10log(LOGDEBUG,"Mandado comando %02x\n",comando);
  v10log(LOGDEBUG,"Mando %s\n",bufferida);
}

static void mandatramalinea(infolineas *linea)
{
  linea->hulttrama=damecent();
  mandacomando(linea,linea->tipotrama,linea->tramaida,linea->lonida);
  linea->tramasida++;
}

static void mandatramalog(infolineas *linea,int numlin)
{
  char buffer[MAXCADENA];
  int i;
  linea->hulttrama=damecent();
  *buffer=(char)numlin;
  for (i=0;i<linea->numdisp;i++) {
    buffer[i+1]=0;
  }
  mandacomando(linea,GRABALOG,buffer,i+1);
  linea->tramasida++;
  linea->bytesida+=linea->lonida+11;
}

static void mandawholinea(infolineas *linea)
{
  char buffer[MAXCADENA],*ptr=buffer;
  char ndisp=(char)(linea->paropuerto==210?0:linea->paropuerto);

  linea->hulttrama=damecent();
  v10log(LOGNORMAL,"linea %d modotest %d paroserie %d\n",linea->port,linea->modotest,linea->paropuerto);
  *ptr++=(char)linea->modotest;
  *ptr++=(char)(ndisp);
  *ptr++=(char)(linea->paropuerto+3);
  *ptr++=(char)(ndisp+0xc);
  *ptr++=(char)(ndisp+0x30);
  *ptr++=(char)(ndisp+0xf);
  mandacomando(linea,WHO,buffer,ptr-buffer);
  linea->tramasida++;
  linea->bytesida+=7;
  linea->numwho++;
  linea->recwho=WHOENV;
  linea->hultwho=damecent();
}

static void mandatramaciclo(infolineas *linea)
{
  char buffer[MAXCADENA];
  int i;
  linea->hulttrama=damecent();
  for (i=0;i<MAXLUCESDISPLAY;i++) buffer[i]=(char)linea->ciclotrabajo[i];
  mandacomando(linea,CICLOTRABAJO,buffer,MAXLUCESDISPLAY);
  linea->tramasida++;
}

static void logtramavuelta(infolineas *linea)
{
   char buffer[MAXCADENA]="";
   int i;
   v10log(LOGERROR,"Recibida trama de vuelta comando %02X numdisp %d\n",*linea->tramavuelta,linea->tramavuelta[1]);
   for (i=0;i<linea->lonvuelta;i++) {
       sprintf(buffer+strlen(buffer),"%02X ",linea->tramavuelta[i]);
       if (((i-2) % 90)==0) sprintf(buffer+strlen(buffer),"\n");
    }
   v10log(LOGERROR,"  Trama %s\n",buffer);
}

static void tratavuelta(infolineas *linea)
{
  unsigned char comando;
  char *ptr=linea->tramavuelta,*miptr;
  int ndisp=0,numdisp;
  static int antdisp;
  comando=*ptr++;
  numdisp=*ptr++;
  v10log(LOGDEBUG,"Recibido comando %02x numdisp %d longitud %d\n",comando,numdisp,linea->lonvuelta);
  if (linea->numdisp!=numdisp && (comando!=0x84 || antdisp==numdisp))  {
    linea->numdisp=numdisp;
    linea->modifestruc=1;
    linea->modifida=1;
    linea->recwho=WHOPEND;
    v10log(LOGNORMAL,"Recibido comando %02x numdisp %d longitud %d\n",comando,numdisp,linea->lonvuelta);
  }
  antdisp=numdisp;
  switch (comando)  {
     case RESPST: miptr=ptr;
                  for (ndisp=0;ndisp<linea->numdisp;ndisp++)   {
                       int lstatus;
                       if (*ptr & BITSTLEN) {
                          lstatus=*ptr&~BITSTLEN;
                          v10log(LOGERROR,"Recibido estatus de longitud %d\n",lstatus);
                          if (lstatus>=MAXSTATUSDISPLAY) break;
                        } else {
                          lstatus=0;
                       }
                      ptr+=lstatus+1;
                      if (ptr-linea->tramavuelta>linea->lonvuelta) {
                         v10log(LOGERROR,"Linea de vuelta con pocos status espero %d y recibo %d\n",linea->numdisp,ndisp);
                         return;
                       }
                   }
                  if (ptr<linea->tramavuelta+linea->lonvuelta) {
                     v10log(LOGERROR,"Linea de vuelta con muchos estatus\n");
                     return;
                   }
                  ptr=miptr;
                  for (ndisp=0;ndisp<linea->numdisp;ndisp++)   {
                       infodisps *di=linea->disp+ndisp;
                       int lstatus;
                       if (*ptr & BITSTLEN) {
                          lstatus=*ptr&~BITSTLEN;
                          v10log(LOGERROR,"Recibido estatus de longitud %d\n",lstatus);
                          if (lstatus>=MAXSTATUSDISPLAY) break;
                          if (memcmp(ptr+1,di->status,lstatus)) {
                             di->modifvuelta=1;
                             memcpy(di->status,ptr+1,lstatus);
                          }
                        } else {
                          if (*ptr!=*di->status) {
                             di->modifvuelta=1;
                             linea->modifvuelta=1;
                             *di->status=*ptr;
                           }
                          if (*ptr&BITERRSOFT) {
                             di->errtrama++;
                             break;
                           }
                          if (*ptr&BITERRHARD) di->errhard++;
                          lstatus=0;
                       }
                      ptr+=lstatus+1;
                      if (ptr-linea->tramavuelta>linea->lonvuelta) {
                         v10log(LOGERROR,"Linea de vuelta con pocos status espero %d y recibo %d\n",linea->numdisp,ndisp);
                         break;
                       }
                   }
                  break;
     case RETERROR:
     case RESPST1: {int ultdisp=-1,i;
                          infodisps *di;
                    while (ptr<linea->tramavuelta+linea->lonvuelta) {
                          int lstatus;
                          ndisp=*ptr++;
                          if (ndisp>linea->numdisp) {
                             v10log(LOGERROR,"Linea de vuelta con muchos estatus\n");
                             return;
                           }
                          ndisp=linea->numdisp-ndisp-1;
                          for (i=ultdisp+1;i<ndisp;i++) {
                              di=linea->disp+i;
                              if (*di->status) {
                                 di->modifvuelta=1;
                                 linea->modifvuelta=1;
                                 *di->status=0;
                               }
                           }
                          ultdisp=ndisp;
                          di=linea->disp+ndisp;
                          if (*ptr & BITSTLEN) {
                             lstatus=*ptr&~BITSTLEN;
                             v10log(LOGERROR,"Recibido estatus de longitud %d\n",lstatus);
                             if (lstatus>=MAXSTATUSDISPLAY) break;
                             if (memcmp(ptr+1,di->status,lstatus)) {
                                di->modifvuelta=1;
                                memcpy(di->status,ptr+1,lstatus);
                             }
                           } else {
                             if (*ptr!=*di->status) {
                                di->modifvuelta=1;
                                linea->modifvuelta=1;
                                *di->status=*ptr;
                              }
                             if (*ptr&BITERRSOFT) {
                                di->errtrama++;
                                break;
                              }
                             if (*ptr&BITERRHARD) di->errhard++;
                             lstatus=0;
                           }
                         ptr+=lstatus+1;
                         if (ptr-linea->tramavuelta>linea->lonvuelta) {
                            v10log(LOGERROR,"Linea de vuelta con pocos status espero %d y recibo %d\n",linea->numdisp,ndisp);
                            break;
                          }
                   }
                          for (i=ultdisp+1;i<linea->numdisp;i++) {
                              di=linea->disp+i;
                              if (*di->status) {
                                 di->modifvuelta=1;
                                 linea->modifvuelta=1;
                                 *di->status=0;
                               }
                           }
                  break;
                 }
     case RESPWHO:while (ptr<linea->tramavuelta+linea->lonvuelta && ndisp<=numdisp) {
                        if (linea->disp[ndisp].tipo!=*ptr) linea->modifestruc=1;
                        linea->disp[ndisp].tipo=*ptr++;
                        linea->disp[ndisp].tipodisp=dametipo(linea->disp[ndisp].tipo);
                        ptr=recogelong(ptr,&linea->disp[ndisp].serie);
                        ptr=recogelong(ptr,&linea->disp[ndisp].version);
                        if (linea->disp[ndisp].version<0x30313034) {
                           linea->recwho=WHOPEND;
                           v10log(LOGERROR,"Recibida una trama de who version %X\n",linea->disp[ndisp].version);
                           break;
                         }
                        v10log(LOGNORMAL,"Display %d tipo %d %s serie %08lx version %s luz %d\n",ndisp+1,linea->disp[ndisp].tipo, linea->disp[ndisp].tipodisp->nombre,linea->disp[ndisp].serie,infodameversion(linea->disp[ndisp].version),linea->disp[ndisp].tipodisp->luzdig);
                        ndisp++;
                        linea->ciclotrabajo[0]=0;
                  }
                 if (ptr<linea->tramavuelta+linea->lonvuelta) {
                    linea->recwho=WHOPEND;
                    v10log(LOGERROR,"Recibida una trama de who larga\n");
                           break;
                  }
                 if (ndisp==numdisp) linea->recwho=WHOREC;
                    else {
                      v10log(LOGERROR,"Recibida una trama de who con %d displays y se esperaban %d\n",ndisp,numdisp);
                      linea->recwho=WHOPEND;
                    }
                 break;
     case RESPLOG:{
                   int numlin=*ptr++;
                   while (ptr<linea->tramavuelta+linea->lonvuelta) {
                         unsigned long log;
                         ptr=recogelong(ptr,&log);
                         v10log(LOGNORMAL,"Display %d linea %d log %lx\n",ndisp+1,numlin,log);
                         ndisp++;
                    }
                  }
                 break;
     default:    logtramavuelta(linea);
                 return;
  }
  linea->hulttramavuelta=damecent();
}

static int damecarr(int port)
{
  int ret;
  ret=STDdamecar232(port);
  return(ret);
}

static void automatavuelta(infolineas *linea)
{
  int ch;
  while ((ch=damecarr(linea->port))!=-1) {
    linea->bytesvuelta++;
    linea->hultbyte=damecent();
    linea->numcartrama++;
    switch (linea->status) {
       case STIDDLE:   if (ch==INITRAMA) linea->status=STRECINI;
                          else           if (ch!=0XAA) linea->perdidos++;
                       break;
       case STRECINI:  if (ch==INITRAMA) {
                          linea->status=STCONFINI;
                          linea->check=0;
                          linea->ptrvuelta=linea->tramavuelta;
                          linea->numcartrama=2;
                        } else {
                          linea->status=STIDDLE;
                        }
                       break;
       case STCONFINI: linea->check^=(char)ch;
                       if (ch==INITRAMA) {
                          linea->status=STRECFIN;
                        } else {
                          if (linea->ptrvuelta-linea->tramavuelta>=MAXTRAMAVUELTA) {
                             linea->errtrama++;
                             v10log(LOGERROR,"Recibida trama vuelta demasiado larga\n");
                             linea->status=STIDDLE;
                           }
                          *linea->ptrvuelta++=(char)ch;
                        }
                       break;
       case STRECFIN:  linea->check^=(char)ch;
                       if (ch==FINTRAMA) {
                          linea->status=STCONFFIN;
                        } else {
                          *linea->ptrvuelta++=INITRAMA;
                          *linea->ptrvuelta++=(char)ch;
                          linea->status=STCONFINI;
                        }
                       break;
       case STCONFFIN:  *linea->ptrvuelta++=INITRAMA;
                        *linea->ptrvuelta++=FINTRAMA;
                        *linea->ptrvuelta++=(char)ch;
                        linea->tramasvuelta++;
                        linea->lonvuelta=linea->ptrvuelta-linea->tramavuelta-3;
                        if ((linea->check^linea->numcartrama)==ch) {
                           tratavuelta(linea);
                         } else {
                           linea->errtrama++;
                           logtramavuelta(linea);
                           v10log(LOGERROR,"Trama de vuelta con checksum erroneo es %02X deberia ser %02X  check %02X  lon %02X\n",ch,linea->check^linea->numcartrama,linea->check,linea->numcartrama);
                         }
                        linea->status=STIDDLE;
                        break;
     }
  }
}


static short valorluces(infodisps *di)
{
  unsigned short ret=0;
  int i;
  for (i=0;i<di->tipodisp->luces;i++) {
    ret=(unsigned short)((ret<<2)+di->luces[i]);
  }
  return(s2d(ret));
}

static char *tododigitos(infodisps *di)
{
  int i;
  static char valor[MAXDIGDISPLAY];
  char *ptr=valor;
  memset(valor,0,sizeof(valor));
  for (i=0;i<di->tipodisp->digitos;i++) {
    if (di->valor[i]!=' ' && !isdigit(di->valor[i])) return(NULL);
    if ((i&1)==0) *ptr=(char)(di->valor[i]==' '?10:di->valor[i]-'0');
     else {
      *ptr=(char)(*ptr+((di->valor[i]==' '?10:di->valor[i]-'0')<<4));
      ptr++;
     }
  }
  return(valor);
}


static char *calculavalordisp(infodisps *di,char *ptr)
{
   int i;
   if (di->tipodisp==NULL) di->tipodisp=dametipo(-1);
   if (es_blanco(di->valor)) {
      if ((valorluces(di)&(~SOLOLUZDIG))==0) {
         *ptr++=APAGADO;
       } else {
         *ptr++=(char)(BLANCOLUZ+(2<<2));
          ptr=mandashort(ptr,valorluces(di));
       }
    } else {
      char *valor;
      if ((valor=tododigitos(di))!=NULL) {
         *ptr++=(char)(NUMERICO+(((di->tipodisp->digitos>>1)+2)<<2));
         for (i=0;i<(di->tipodisp->digitos>>1);i++) *ptr++=valor[i];
         ptr=mandashort(ptr,valorluces(di));
      } else {
        *ptr++=(char)(ALFA+((di->tipodisp->digitos+2)<<2));
        for (i=0;i<di->tipodisp->digitos;i++) *ptr++=di->valor[i];
        ptr=mandashort(ptr,valorluces(di));
      }
  }
 return(ptr);
}

static void creatramaida(infolineas *linea)
{
  char *ptr=linea->tramaida,*sig;
  int nd,napa=0;
  linea->minversion=0x33333333;
  linea->modifida=0;
  linea->creatramas++;
  for (nd=0;nd<linea->numdisp;nd++) {
       infodisps *di=linea->disp+nd;
       if (di->version<linea->minversion) linea->minversion=di->version;
       sig=calculavalordisp(di,ptr);
       if (*ptr==APAGADO) napa++;
       ptr=sig;
  }
  if (napa>linea->numdisp/2 && linea->minversion>=VERADMITEST1) {
     linea->tipotrama=ENCDISP1;
     ptr=linea->tramaida;
     for (nd=0;nd<linea->numdisp;nd++) {
         infodisps *di=linea->disp+nd;
         sig=calculavalordisp(di,ptr+1);
         if (ptr[1]!=APAGADO) {
            *ptr=(char)nd;
            ptr=sig;
          }
      }
  } else linea->tipotrama=ENCDISP;
  linea->lonida=ptr-linea->tramaida;
  if (consumolinea(linea)) mandatramaciclo(linea);
}


int automatalinea(infolineas *linea)
{
  {int i;for (i=0;i<10;i++) automatavuelta(linea);}
  if (linea->status!=STIDDLE && damecent()-linea->hultbyte>TPERRO232) {
     v10log(LOGDEBUG,"Trama del vuelta cortada\n");
     linea->status=STIDDLE;
   }
  if (damecent()-linea->hulttramavuelta>linea->timeouttrama && linea->recwho>=WHOREC) {
     v10log(LOGERROR,"Timeout en trama\n");
     linea->recwho=WHOPEND;
     linea->hulttramavuelta=damecent();
     linea->modifestruc=1;
     linea->numdisp=0;
   }
  if (linea->recwho==WHOPEND || (damecent()-linea->hultwho>linea->timeoutwho && linea->recwho<WHOREC)) {
     if (linea->recwho==WHOENV) {
        v10log(LOGDEBUG,"Timeout en WHO\n");
      }
     v10log(LOGDEBUG,"Mando who a linea\n");
     mandawholinea(linea);
  }

  if (hay_tecla()) {
    int ret=tecla();
    if (ret>='0' && ret<='9') {
      int i;
      for (i=0;i<MAXLUCESDISPLAY;i++) linea->ciclotrabajo[i]=ret-'0';
      mandatramaciclo(linea);
    }
    if (ret=='A') {
       int i;
       for (i=0;i<linea->numdisp;i++) lindisplayprintf(linea,i,"%d",i);
     }
    if (ret>='a' && ret<='z') {
      v10log(LOGNORMAL,"Envio\n");
      mandatramalog(linea,ret-'a');
    }
    if (ret==A_F(10)) return(-1);
  }
  if (damecent()-linea->hulttrama>=linea->tenvtrama) {
    switch (linea->recwho) {
       case MANDADOCICLO:  if (linea->modifestruc || linea->modifida) {
                             creatramaida(linea);
                             linea->llevonulas=linea->tramasnulas;
                           }
                          if (linea->llevonulas++>=linea->tramasnulas) {
                             mandatramalinea(linea);
                             linea->llevonulas=0;
                           } else {
                             linea->hulttrama=damecent();
                             if (linea->minversion>=VERADMITEST1) mandacomando(linea,TRAMANULA1,NULL,0);
                                else                              mandacomando(linea,TRAMANULA,NULL,0);
                             linea->tramasida++;
                           }
                          break;
       case WHOREC:       mandatramaciclo(linea);
                          linea->recwho=MANDADOCICLO;
                          break;
    }
  }
  return(0);
}
