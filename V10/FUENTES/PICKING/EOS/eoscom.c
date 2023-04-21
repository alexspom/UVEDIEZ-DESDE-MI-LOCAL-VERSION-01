/*
* Módulo : EOSCOM.C
* Objeto: Comunicación a bajo nivel con displays EOS
*
*
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-12-2007

* MODIFICACIONES
* --
*/
#include "eos.h"

#define SOLOLUZDIG   0X400

#define VERSION2 0x30323031
#define VERADMITEST1 0X30313036

#define VELOCIDADDISPLAY 0x14;


v10sockets *v10slog=NULL;

void miescribelog(int nivel,char *format,...)
{
    char bufferlog[MAXCADENA];
    va_list argc;
    int ch;
    if (v10slog!=NULL)
        if ((ch=sigcarsocket(v10slog))!=-1)
            maxnivellog=ch-'0';
    if (maxnivellog<nivel) return;
    va_start(argc,format);
#ifdef __WIN32__
    vv10log(nivel,format,argc);
#else
    vprintf(format,argc);
#endif
    if (v10slog==NULL) {
#ifndef __NETOS__
           va_end(argc);
#endif
           return;
     }
    vsprintf(bufferlog,format,argc);
    sendv10socket(v10slog,bufferlog,strlen(bufferlog));
    va_end(argc);
}

static void writeport232(eoslineas *linea,char *buff,int tam)
{
    HANDLE hp;
    DWORD escrito;
    if (linea->port>=MAXPORTREAL) {
        if (linea->vdsockvirt->status==STSOCKCERRADO) reabrecliente(linea->vdsockvirt);
        sendv10socket(linea->vdsockvirt,buff,tam);
    } else {
        hp=damepuerto232(linea->port);
#ifdef __WIN32__
    WriteFile(hp,buff,tam,&escrito,NULL);
#else
    escrito=write (hp,buff, tam);
#endif
        if (escrito!=tam) {
            v10log(LOGERROR,"Error intento escribir %d bytes y escribo %d\n",tam,escrito);
        }
    }
}

static int damecarr(eoslineas *linea)
{
    int ret;
    if (linea->port>=MAXPORTREAL) {
        if (linea->vdsockvirt->status==STSOCKCERRADO) reabrecliente(linea->vdsockvirt);
        ret=sigcarsocket(linea->vdsockvirt);
    } else {
        ret=dame232(linea->port);
    }
    return(ret);
}

static void inicializa232(eoslineas *linea)
{
    if (linea->port<MAXPORTREAL) {
        if (initpuerto232(linea->port,BAUDRATE,NOPARITY,8,ONESTOPBIT)!=0) 
            final(("No puedo abrir puerto %d\n",linea->port+1));
    } else {
        char servicio[40];
		char ordenador[40];
        sprintf(servicio,"LINEAVIRT");
		sprintf(ordenador,"EOSVIRT%d",linea->port);
        linea->vdsockvirt=creacliente(ordenador,servicio);
    }
}


void initlinea(eoslineas *linea)
{
    char servicio[MAXPATH];
    int i;
    linea->ptrvuelta=linea->tramavuelta;
    inicializa232(linea);
    sprintf(servicio,"LINEA%d",linea->port);
    linea->v10s=creaservidor(servicio);
    sprintf(servicio,"LOG%d",linea->port);
    v10slog=creaservidor(servicio);
    linea->modifestrucpc=1;
    linea->limitacionlinea=LIMITACIONLINEA;
    linea->tenvtrama=TENVTRAMA;
    linea->timeouttrama=TIMEOUTTRAMA;
    linea->timeoutwho=TIMEOUTWHO;
    linea->tramasnulas=TRAMASNULAS;
    linea->tciclo=TCICLO;
    linea->paropuerto=210;
    linea->hulttramavuelta=damecent();
    linea->velocidad = VELOCIDADDISPLAY;
    for (i=0;i<MAXLUCESDISPLAY;i++) linea->ciclotrabajo[i]=10;
}
static char bufferida[MAXCADENA]="";
static char tramaida[MAXCADENA],*ptrtrama;

void miencolae(int port,int ch)
{
    if (maxnivellog>=LOGDEPURATRAMA) sprintf(bufferida+strlen(bufferida),"%02x ",ch);
    *ptrtrama++=(char)ch;
}

static void mandacomando(eoslineas *linea,int comando,char *trama,int lon)
{
    char *ptr=trama;
    int port=linea->port;
    int check,i;
    char numcartrama;
    escribe_log(LOGDEBUG,"Intento mandar comando %d\n",comando);
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
    writeport232(linea,tramaida,ptrtrama-tramaida);
    linea->bytesida+=ptrtrama-tramaida+7;
    escribe_log(LOGDEBUG,"Mandado comando %02x\n",comando);
    escribe_log(LOGDEBUG,"Mando %s\n",bufferida);
    linea->hulttrama=damecent();
    linea->tramasida++;
}

static void mandatramalinea(eoslineas *linea)
{
    escribe_log(LOGDEBUG,"Mandatramalinea\n");
    mandacomando(linea,linea->tipotrama,linea->tramaida,linea->lonida);
}

static void mandawholinea(eoslineas *linea, int comando)
{
    char buffer[MAXCADENA],*ptr=buffer;
    char ndisp=(char)(linea->paropuerto==210?0:linea->paropuerto);
    escribe_log(LOGNORMAL,"linea %d modotest %d paroserie %d\n",linea->port,linea->modotest,linea->paropuerto);
    *ptr++=(char)linea->modotest;
    *ptr++=(char)(ndisp);
    *ptr++=(char)(linea->paropuerto+3);
    *ptr++=(char)(ndisp+0xc);
    *ptr++=(char)(ndisp+0x30);
    *ptr++=(char)(ndisp+0xf);
    mandacomando(linea,comando,buffer,ptr-buffer);
    //mandacomando(linea,WHO,buffer,ptr-buffer);
    if (comando == WHO) {
       linea->numwho++;
       linea->recwho=WHOENV;
       linea->hultwho=damecent();
     }
}

static void mandatramaciclo(eoslineas *linea)
{
    char buffer[MAXCADENA];
    int i;
    for (i=0;i<MAXLUCESDISPLAY;i++) buffer[i]=(char)linea->ciclotrabajo[i];
    buffer[MAXLUCESDISPLAY] = linea->velocidad;
    mandacomando(linea,CICLOTRABAJO,buffer,MAXLUCESDISPLAY+1);
    linea->modifvel = 0;
    escribe_log(LOGNORMAL,"Mandada tramaciclo velocidad %d MAXLUCES %d\n",linea->velocidad,MAXLUCESDISPLAY);
}

#define STIDDLE    0
#define STRECINI   1
#define STCONFINI  2
#define STRECFIN   3
#define STCONFFIN  4

static void logtramavuelta(eoslineas *linea)
{
    char buffer[MAXCADENA]="";
    int i;
    escribe_log(LOGERROR,"Recibida trama de vuelta comando %02X numdisp %d\n",*linea->tramavuelta,linea->tramavuelta[1]);
    for (i=0;i<linea->lonvuelta;i++) {
        sprintf(buffer+strlen(buffer),"%02X ",linea->tramavuelta[i]);
        if (((i-2) % 90)==0) sprintf(buffer+strlen(buffer),"\n");
    }
    escribe_log(LOGERROR,"  Trama %s\n",buffer);
}

static void tratavuelta(eoslineas *linea)
{
    unsigned char comando;
    char *ptr=linea->tramavuelta,*miptr;
    int ndisp=0,numdisp;
    int longnombre;
    static int antdisp;
    static int desconocido = 0;
    int predospuntocero = 0;
    comando=*ptr++;
    numdisp=*ptr++;
    escribe_log(LOGDEBUG,"Recibido comando %02x numdisp %d longitud %d\n",comando,numdisp,linea->lonvuelta);
    if (linea->recwho<WHOREC && comando!=RESPWHO) {
        escribe_log(LOGNORMAL,"Ignorado comando %02x numdisp %d longitud %d\n",comando,numdisp,linea->lonvuelta);
        return;
    }
    if (linea->numdisp!=numdisp && (antdisp==numdisp))  {
        linea->numdisp=numdisp;
        linea->modifestruc=1;
        linea->modifida=1;
        linea->recwho=WHOPEND;
        escribe_log(LOGNORMAL,"Recibido comando de diaplays %02x numdisp %d longitud %d\n",comando,numdisp,linea->lonvuelta);
    }
    antdisp=numdisp;
    switch (comando)  {
     case RESPST: miptr=ptr;
         for (ndisp=0;ndisp<linea->numdisp;ndisp++)   {
             int lstatus;
             if (*ptr & BITSTLEN) {
                 lstatus=*ptr&~BITSTLEN;
                 escribe_log(LOGERROR,"Recibido estatus de longitud %d\n",lstatus);
                 if (lstatus>=MAXSTATUSDISPLAY) break;
             } else {
                 lstatus=0;
             }
             ptr+=lstatus+1;
             if (ptr-linea->tramavuelta>linea->lonvuelta) {
                 escribe_log(LOGERROR,"Linea de vuelta con pocos status espero %d y recibo %d\n",linea->numdisp,ndisp);
                 return;
             }
         }
         if (ptr<linea->tramavuelta+linea->lonvuelta) {
             escribe_log(LOGERROR,"Linea de vuelta con muchos estatus\n");
             return;
         }
         ptr=miptr;
         for (ndisp=0;ndisp<linea->numdisp;ndisp++)   {
             eosdisps *di=linea->disp+ndisp;
             int lstatus;
             if (*ptr & BITSTLEN) {
                 lstatus=*ptr&~BITSTLEN;
                 escribe_log(LOGERROR,"Recibido estatus de longitud %d\n",lstatus);
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
                 escribe_log(LOGERROR,"Linea de vuelta con pocos status espero %d y recibo %d\n",linea->numdisp,ndisp);
                 break;
             }
         }
         break;
     case RETERROR:
     case RESPST1: {int ultdisp=-1,i;
         eosdisps *di;
         while (ptr<linea->tramavuelta+linea->lonvuelta) {
             int lstatus;
             ndisp=*ptr++;
             if (ndisp>linea->numdisp) {
                 escribe_log(LOGERROR,"Linea de vuelta con muchos estatus\n");
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
                 escribe_log(LOGERROR,"Recibido estatus de longitud %d\n",lstatus);
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
                 escribe_log(LOGERROR,"Linea de vuelta con pocos status espero %d y recibo %d\n",linea->numdisp,ndisp);
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
     case RESPWHO:
     	while (ptr<linea->tramavuelta+linea->lonvuelta && ndisp<=numdisp) {
                int i;
        	if (linea->disp[ndisp].tipo!=*ptr) linea->modifestruc=1;
         	linea->disp[ndisp].tipo=*ptr++;
         	linea->disp[ndisp].tipodisp=dametipo(linea->disp[ndisp].tipo);
		if (linea->disp[ndisp].tipodisp->tipo == -1) desconocido = 1;
         	ptr=recogelong(ptr,&linea->disp[ndisp].serie);
         	ptr=recogelong(ptr,&linea->disp[ndisp].version);
		if (atoi(infodameversion(linea->disp[ndisp].version))<2) predospuntocero = 1;
         	escribe_log(LOGNORMAL,"Display %d tipo %d %s serie %08lx version %s\n",ndisp+1,linea->disp[ndisp].tipo, linea->disp[ndisp].tipodisp->nombre,linea->disp[ndisp].serie,infodameversion(linea->disp[ndisp].version));
         	for (i=0;i<MAXLUCESDISPLAY;i++) linea->ciclotrabajo[i]=0;
         	ndisp++;
	}
        if (ptr<linea->tramavuelta+linea->lonvuelta) {
            linea->recwho=WHOPEND;
            escribe_log(LOGERROR,"Recibida una trama de who larga\n");
            break;
		}
        if (ndisp==numdisp) {
            linea->recwho=WHOREC;
            linea->numdisp=numdisp;
	    if (desconocido && ! predospuntocero) {
		mandawholinea(linea, WHOEXTENDIDO);
		escribe_log(LOGNORMAL,"Mando who extendido a linea\n");
	      }
         } else {
	    escribe_log(LOGERROR,"Recibida una trama de who con %d displays y se esperaban %d\n",ndisp,numdisp);
            linea->recwho=WHOPEND;
	 }
	break;
     case RESPWHOEXT:
     	 while (ptr<linea->tramavuelta+linea->lonvuelta && ndisp<=numdisp) {
                int i;
         	linea->disp[ndisp].tipodisp=dametipo(linea->disp[ndisp].tipo);
	        longnombre = *ptr++ - 4;
		if (linea->disp[ndisp].tipodisp->tipo == -1) { //Tengo que repasar el resto de displays con -1 que tengo después para diferenciar los que 
				// quedan bien definidos tras añadir este de los uqe no quedan bien definidos porque son distintos a este.
		    int i = ndisp;
		    memcpy(linea->disp[ndisp].tipodisp+1, linea->disp[ndisp].tipodisp, sizeof(tipodisps));
		    memset(linea->disp[ndisp].tipodisp,0,  sizeof(tipodisps));
		    linea->disp[ndisp].tipodisp->tipo=linea->disp[ndisp].tipo;
                    linea->disp[ndisp].tipodisp->digitos = *ptr++;
         	    linea->disp[ndisp].tipodisp->botones = *ptr++;
         	    linea->disp[ndisp].tipodisp->luces = *ptr++;
         	    linea->disp[ndisp].tipodisp->status = *ptr++;
         	    strncpy(linea->disp[ndisp].tipodisp->nombre, ptr, longnombre);
         	    ptr = ptr + longnombre;
		    escribe_log(LOGNORMAL,"Añadido el tipo del display nº %d (%d). %d digitos, %d botones, %d luces y longitud de status %d. Nombre: %s\n",ndisp+1,linea->disp[ndisp].tipodisp->tipo, linea->disp[ndisp].tipodisp->digitos, linea->disp[ndisp].tipodisp->botones, linea->disp[ndisp].tipodisp->luces, linea->disp[ndisp].tipodisp->status, linea->disp[ndisp].tipodisp->nombre);
		    while (++i < numdisp ){
			  if (linea->disp[i].tipodisp->tipo != linea->disp[i].tipo) linea->disp[i].tipodisp++;
		     }
		 } else ptr = ptr + (longnombre + 4);
         	ndisp++;
         	for (i=0;i<MAXLUCESDISPLAY;i++) linea->ciclotrabajo[i]=0;
	   }
          if (ptr<linea->tramavuelta+linea->lonvuelta) {
             linea->recwho=WHOPEND;
             escribe_log(LOGERROR,"Recibida una trama de who larga\n");
             break;
           }
          if (ndisp==numdisp) {
             linea->recwho=WHOREC;
             linea->numdisp=numdisp;
           } else {
	     escribe_log(LOGERROR,"Recibida una trama de who con %d displays y se esperaban %d\n",ndisp,numdisp);
             linea->recwho=WHOPEND;
	   }
	   break;

     case RESPLOG:{
            int numlin=*ptr++;
            while (ptr<linea->tramavuelta+linea->lonvuelta) {
                  unsigned long log;
                  ptr=recogelong(ptr,&log);
                  escribe_log(LOGNORMAL,"Display %d linea %d log %lx\n",ndisp+1,numlin,log);
                  ndisp++;
              }
            }
           break;
     default:    logtramavuelta(linea);
         return;
    }
    linea->hulttramavuelta=damecent();
    escribe_log(LOGDEBUG,"Terminado de tratar comando desde displays\n");
}

static void automatavuelta(eoslineas *linea)
{
    int ch;
    while ((ch=damecarr(linea))!=-1) {
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
                   escribe_log(LOGERROR,"Recibida trama vuelta demasiado larga\n");
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
               escribe_log(LOGERROR,"Trama de vuelta con checksum erroneo es %02X deberia ser %02X  check %02X  lon %02X\n",ch,linea->check^linea->numcartrama,linea->check,linea->numcartrama);
           }
           linea->status=STIDDLE;
           break;
        }
    }
}


static short valorluces(eosdisps *di)
{
    unsigned short ret=0;
    int i;
    for (i=0;i<di->tipodisp->luces;i++) {
        ret=(unsigned short)((ret<<2)+di->luces[i]);
    }
    return(ret);
}

static char *tododigitos(eosdisps *di)
{
    int i;
    static char valor[MAXDIGDISPLAY];
    char *ptr=valor;
    int lon=di->tipodisp->digitos;
    if (di->version>=VERSION2) lon=strlen(di->valor);
    else pad(di->valor,di->tipodisp->digitos);
    memset(valor,0,sizeof(valor));
    for (i=0;i<lon;i++) {
        if (di->valor[i]!=' ' && !isdigit(di->valor[i])) return(NULL);
        if ((i&1)==0) *ptr=(char)(di->valor[i]==' '?10:di->valor[i]-'0');
        else {
            *ptr=(char)(*ptr+((di->valor[i]==' '?10:di->valor[i]-'0')<<4));
            ptr++;
        }
    }
    if ((i&1)) *ptr=*ptr+(10<<4);
    return(valor);
}
#define APAGADO    0
#define BLANCOLUZ  1
#define NUMERICO   2
#define ALFA       3

static char *calculavalordisp(eosdisps *di,char *ptr)
{
    int i;
    if (di->tipodisp==NULL) di->tipodisp=dametipo(-1);
    if (es_blanco(di->valor)) {
        if ((valorluces(di)&(~SOLOLUZDIG))==0) {
            *ptr++=APAGADO;
        } else {
	    escribe_log(LOGNORMAL,"Es BLANCOLUZ\n");
            *ptr++=(char)(BLANCOLUZ+(2<<2));
            ptr=mandashort(ptr,valorluces(di));
        }
    } else {
        char *valor;
        int lon;
        if ((valor=tododigitos(di))!=NULL) {
            if (di->version>=VERSION2) {
                lon=(strlen(di->valor)+1)>>1;
                *ptr++=(char)(BLANCOLUZ+((lon+2)<<2));
            } else {
                lon=di->tipodisp->digitos>>1;
                *ptr++=(char)(NUMERICO+((lon+2)<<2));
            }
            for (i=0;i<lon;i++) *ptr++=valor[i];
            ptr=mandashort(ptr,valorluces(di));
        } else {
            if (di->version>=VERSION2) {
                *ptr++=(char)(APAGADO+((strlen(di->valor)+2)<<2));
                for (i=0;i<strlen(di->valor);i++) *ptr++=di->valor[i];
            } else {
                *ptr++=(char)(ALFA+((di->tipodisp->digitos+2)<<2));
                for (i=0;i<di->tipodisp->digitos;i++) *ptr++=di->valor[i];
            }
            ptr=mandashort(ptr,valorluces(di));

        }
    }
    return(ptr);
}

static void creatramaida(eoslineas *linea)
{
    char *ptr=linea->tramaida,*sig;
    int nd,napa=0;
    linea->minversion=0x77777777;
    linea->modifida=0;
    linea->creatramas++;
    escribe_log(LOGNORMAL,"Creando trama de ida\n");
    for (nd=0;nd<linea->numdisp;nd++) {
        eosdisps *di=linea->disp+nd;
        if (di->version<linea->minversion) linea->minversion=di->version;
        sig=calculavalordisp(di,ptr);
        if (*ptr==APAGADO) napa++;
        ptr=sig;
    }
    if (napa>linea->numdisp/2) {
        linea->tipotrama=ENCDISP1;
        ptr=linea->tramaida;
        for (nd=0;nd<linea->numdisp;nd++) {
            eosdisps *di=linea->disp+nd;
            sig=calculavalordisp(di,ptr+1);
            if (ptr[1]!=APAGADO) {
                *ptr=(char)nd;
                ptr=sig;
            }
        }
    } else linea->tipotrama=ENCDISP;
    linea->lonida=ptr-linea->tramaida;
    escribe_log(LOGNORMAL,"Creada trama de ida longitud %d\n",linea->lonida);
    if (consumolinea(linea)) mandatramaciclo(linea);
    escribe_log(LOGDEBUG,"Mandada trama de ciclo\n");
}


int automatalinea(eoslineas *linea)
{
    int i;
    for (i=0;i<10;i++) automatavuelta(linea);
    if (linea->status!=STIDDLE && damecent()-linea->hultbyte>TPERRO232) {
        escribe_log(LOGNORMAL,"Trama del vuelta cortada\n");
        linea->status=STIDDLE;
    }
    if (damecent()-linea->hulttramavuelta>linea->timeouttrama && linea->recwho>=WHOREC) {
        reset232(linea->port);
        escribe_log(LOGERROR,"Timeout en trama\n");
        linea->recwho=WHOPEND;
        linea->hulttramavuelta=damecent();
        linea->modifestruc=1;
        linea->numdisp=0;
    }
    if (linea->recwho==WHOPEND || (damecent()-linea->hultwho>linea->timeoutwho && linea->recwho<WHOREC)) {
        if (linea->recwho==WHOENV && damecent()-linea->hultwho>linea->timeoutwho) {
	    if (linea->numdisp!=0) {
	      linea->numdisp=0;
	      linea->modifestruc=1;
              escribe_log(LOGNORMAL,"Linea pasa a tener 0 displays timeout %d\n",linea->timeoutwho);
	    }
            escribe_log(LOGNORMAL,"Timeout en WHO displays %d\n",linea->numdisp);
        }
//#ifndef __WIN32__
#ifdef __LINUX__
        if (linea->numdisp==0  && linea->port<MAXPORTREAL) {
           if ((linea->dirserie=open(DISPOSITIVO, O_RDWR))>=0){
              write (linea->dirserie, &linea->port, sizeof(int));
              close (linea->dirserie);
           }
           reset232(linea->port);
	}
#endif
        escribe_log(LOGNORMAL,"Mando who a linea\n");
        mandawholinea(linea, WHO);
    }
    if (damecent()>linea->nexttrama && damecent()-linea->hulttrama>=linea->tenvtrama) {
        switch (linea->recwho) {
       case MANDADOCICLO:  if (linea->modifestruc || linea->modifida) {
                               creatramaida(linea);
                               linea->llevonulas=linea->tramasnulas;
                               escribe_log(LOGDEBUG,"Despues de crear\n");
                           }
                           if (linea->llevonulas++>=linea->tramasnulas) {
                              escribe_log(LOGDEBUG,"Antes de mandar\n");
                               mandatramalinea(linea);
                               linea->llevonulas=0;
#ifdef __WIN32__
                               linea->nexttrama=damecent()+(linea->lonida*1000/BAUDRATE)+linea->tenvtrama;
#endif
                           } else {
                               escribe_log(LOGDEBUG,"Antes de trama nula\n");
                               mandacomando(linea,TRAMANULA1,NULL,0);
                           }
                           if (linea->modifvel) mandatramaciclo(linea);
                           break;
       case WHOREC:       mandatramaciclo(linea);
                          linea->recwho=MANDADOCICLO;
                          break;
        }
    }
    return(0);
}
