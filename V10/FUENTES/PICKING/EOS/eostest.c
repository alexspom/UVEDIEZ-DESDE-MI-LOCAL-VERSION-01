/*
* M๓dulo : EOSTEST.C
* Objeto: Programa de verificaci๓n de displays sistema EOS
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-12-2007

* MODIFICACIONES
* --
*/
#include "eospc.h"

static windows weth,wdisp,wlinea;
static int ACTETH,ACTLINEAS,ACTDISP;
#define NUMDIGDISPPANT  20



static void cambiavelocidad(int comando, int velocidad, ethlineas *lin)
{
  int ndglob;
  ndglob=pdisplin(lin);
  lin->velmodificado = 1;
  switch (comando){
	case MOVSIEMPRE: lin->velocidad &= 0x7E;
		break;
	case MOVCONDICIONAL : lin->velocidad |= 0x80;
		break;
	case STOP: lin->velocidad &= 0x80;
		break;
	case PAUSE: lin->velocidad = (lin->velocidad & 0x80) | 0x40;
		break;
	case PLAY: lin->velocidad |= ((velocidad & 0x3F)|0x40);
		break;
	case REVERSE: lin->velocidad = (((velocidad & 0x3F)|lin->velocidad)&0xBF);
		break;
  }
}

static int calcstgloblin(ethlineas *lin)
{
  int i,st;
  int ndglob;
  ndglob=pdisplin(lin);
  st=0;
  for (i=0;i<lin->numdisp;i++) {
      displays *disp=damedisplayid(TIPOIDNUMDISP,ndglob+i);
      if (disp==NULL) continue;
      st|=disp->status[0];
    }
  return(st);
}
static void pontodosdisplincadena(ethlineas *lin,char* cadena)
{
  int i;
  int ndglob;
  ndglob=pdisplin(lin);
  for (i=0;i<lin->numdisp;i++) {
      displays *disp=damedisplayid(TIPOIDNUMDISP,ndglob+i);
      if (disp==NULL) continue;
		displayprintfp(disp,cadena);
    }
}


static void pontodosdisplin(ethlineas *lin,int tipoid)
{
  int i;
  int ndglob;
  ndglob=pdisplin(lin);
  for (i=0;i<lin->numdisp;i++) {
      displays *disp=damedisplayid(TIPOIDNUMDISP,ndglob+i);
      if (disp==NULL) continue;
      if (tipoid==TIPOIDSERIE) displayprintfp(disp,"%X",disp->serie);
         else                  if (tipoid==TIPOIDNUMDISP) displayprintfp(disp,"%d",i+1);
                                  else                    displayprintfp(disp,"");
    }
}

static void pontodosdisplin8(ethlineas *lin)
{
  int i,j;
  int ndglob;
  ndglob=pdisplin(lin);
  for (i=0;i<lin->numdisp;i++) {
      displays *disp=damedisplayid(TIPOIDNUMDISP,ndglob+i);
      if (disp==NULL) continue;
      displayprintfp(disp,"%d",8888);
      for (j=0;j<MAXLUCESDISPLAY;j++) lucesdisplayp(disp,j,1);
    }
}

static void toggletodosdisplin(ethlineas *lin,int luz)
{
  int i;
  int ndglob;
  ndglob=pdisplin(lin);
  for (i=0;i<lin->numdisp;i++) {
      displays *disp=damedisplayid(TIPOIDNUMDISP,ndglob+i);
      if (disp==NULL) continue;
      togglelucesdisplayp(disp,luz);
    }
}

static int calcstglobeth(etherboxs *peth)
{
  int i,st;
  st=0;
  for (i=0;i<MAXLINEAS;i++) {
      st|=calcstgloblin(peth->lin+i);
   }
  return(st);
}

static void pontodosdispeth(etherboxs *peth,int tipoid)
{
  int i;
  for (i=0;i<MAXLINEAS;i++) {
      pontodosdisplin(peth->lin+i,tipoid);
   }
}

static void toggletodosdispeth(etherboxs *peth,int luz)
{
  int i;
  for (i=0;i<MAXLINEAS;i++) {
      toggletodosdisplin(peth->lin+i,luz);
   }
}

static int teclamenudisp(virtsels *s)
{
  int ret,nz=VIRTPOS(s);
  ethlineas *plin=s->dato;
  int ndglob,numdisp=plin->numdisp;
  displays *pdisp;
  ndglob=pdisplin(plin);
  pdisp=damedisplayid(TIPOIDNUMDISP,ndglob+nz);
  while (!hay_tecla_contimeout()) {
        if (numdisp!=plin->numdisp) {
           encolatecla(esc);
           encolatecla(cr);
         }
        if (ACTDISP<MODIFICADOINFO) {
           repintapagina(s);
           poncursorsel(s);
           ACTDISP=MODIFICADOINFO;
         }
        esperamensaje(10);
     }
  ret=tecla();
  switch (upper(ret)) {
     case cr: ret=0;
              break;
     case 'S': displayprintfp(pdisp,"%X",pdisp->serie);
               break;
     case 'N': displayprintfp(pdisp,"%d",nz+1);
               break;
     case ' ': displayprintfp(pdisp,"");
               break;
     case 'Q': displayprintfp(pdisp,"%c",127);
               break;
     case 'W': displayprintfp(pdisp," %c",127);
               break;
     case 'E': displayprintfp(pdisp,"  %c",127);
               break;
     case 'R': displayprintfp(pdisp,"   %c",127);
               break;
     case 'T':
                  (*pdisp->valor)++;
                  *pdisp->valor=1;
                  displayprintfp(pdisp,"%c%3d",*pdisp->valor,*pdisp->valor);
                  break;
     case 'A': displayprintfp(pdisp,"%c%c%c%c",33,34,35,36);
               break;
     case 'D': displayprintfp(pdisp,"%c%c%c%c",37,38,39,40);
               break;
     case 'F': displayprintfp(pdisp,"%c%c%c%c",41,42,43,44);
               break;                                     
     case 'G': displayprintfp(pdisp,"%c%c%c%c",45,46,47,48);
               break;                                    
     case 'K': displayprintfp(pdisp,"UVEDIEZ SUPPLY CHAIN S.L");//"EN UN LUGAR DE LA MANCHA ");
               break;
     default : if (ret>='0' && ret<='9') togglelucesdisplayp(pdisp,ret-'0');
               break;
   }
  pidestatusdisp(plin,nz);
  return(ret);
}

static void pintadisp(virtsels *s,int resal)
{
  int nz=VIRTPOS(s);
  ethlineas *plin=s->dato;
  int ndglob;
  displays *pdisp;
  tipodisps *tipo;
//  pidestatusdisp(plin,nz);
  ndglob=pdisplin(plin);
  pdisp=damedisplayid(TIPOIDNUMDISP,ndglob+nz);
  if (resal) {
     poncolorv(&s->v,CINPUTACT);
   }
  tipo=dametipo(pdisp->tipo);
  v10printf(&s->v,"%7d %3d  %8X %8d  %-7.7s %2d %-10.10s %02X %-*.*s %d%d%d%d%d%d%d %7ld %8ld %8ld",
       ndglob+nz,nz+1,pdisp->serie,pdisp->serie,infodameversion(pdisp->version),pdisp->tipo,tipo->nombre,pdisp->status[0],
       NUMDIGDISPPANT,NUMDIGDISPPANT,pdisp->valor,pdisp->luces[0],pdisp->luces[1],pdisp->luces[2],pdisp->luces[3],pdisp->luces[4],pdisp->luces[5],pdisp->luces[6],pdisp->errhard,pdisp->errtrama,pdisp->consumo);
  poncolorv(&s->v,CNORMAL);
}

static int menudisp(ethlineas *plin)
{
  short *copia;
  copia=salvavd(&wdisp);
  enmarca(&wdisp,0,"Displays");
  v10printf(&wdisp,"Dis.    Num Serie(0x) Serie(d)  Version T. Tipo       St Valor                Luces   Errhard Errtrama Consumo\n");
  v10printf(&wdisp,"อออออออ อออ อออออออออ ออออออออ  อออออออ ออ ออออออออออ ออ ออออออออออออออออออออ อออออออ อออออออ ออออออออ ออออออออ");
  selecciona(0,2,0,0,1,&wdisp,plin->numdisp,1,1,WANCHO(&wdisp),"Lineas",pintadisp,teclamenudisp,0,plin);
  recuperavd(&wdisp,copia);
  return(0);
}

static int teclalineas(virtsels *s)
{
  int nz=VIRTPOS(s);
  etherboxs *peth=s->dato;
  ethlineas *plin=peth->lin+nz;
  int ret;
  while (!hay_tecla_contimeout()) {
        if (ACTLINEAS<MODIFICADOINFO) {
           repintapagina(s);
           poncursorsel(s);
           ACTLINEAS=MODIFICADOINFO;
         }
        esperamensaje(10);
     }
  ret=tecla();
  switch (upper(ret)) {
     case cr: menudisp(plin);
              ret=0;
              break;
     case 'S':pontodosdisplin(plin,TIPOIDSERIE);
              break;
     case 'N':pontodosdisplin(plin,TIPOIDNUMDISP);
              break;
     case 'P':pontodosdisplin8(plin);
              break;
	 case 'K': pontodosdisplincadena(plin,"UVEDIEZ SUPPLY CHAIN S.L");//"EN UN LUGAR DE LA MANCHA ");
               break;
     case ' ':pontodosdisplin(plin,-1);
              break;
	 case '>':cambiavelocidad(PLAY, 0x1F, plin);//Play
		      break;
	 case '<':cambiavelocidad(REVERSE, 0x1F, plin);//Reverse
		      break;
	 case 'Q':cambiavelocidad(PAUSE, 0x1F, plin);//Quietooooooorrl
		      break;
	 case 'I':cambiavelocidad(STOP, 0x1F, plin);//Poner al Inicio
		      break;
     default : if (ret>='0' && ret<='9') toggletodosdisplin(plin,ret-'0');
               break;
   }
  return(ret);
}

static void pintalineas(virtsels *s,int resal)
{
  int nz=VIRTPOS(s),st;
  etherboxs *peth=s->dato;
  ethlineas *plin=peth->lin+nz;
  int ndglob,stglob;
  ndglob=pdisplin(plin);
  if (resal) {
     poncolorv(&s->v,CINPUTACT);
   }
  stglob=1;
  if (plin->v10s==NULL) stglob=0;
     else              if (plin->v10s->status!=STSOCKABIERTO) stglob=0;
  st=calcstgloblin(plin);
  v10printf(&s->v,"%2d %3d %3d %-7.7s %7d %8ld %8ld %8ld %8ld %10ld %10ld %8ld %4ld %4ld %8ld %8ld %2d %02X",
       nz+1,stglob,plin->numdisp,infodameversion(plin->version),ndglob,plin->bucles,plin->tramasida,plin->tramasvuelta,plin->errtrama,
       plin->bytesida,plin->bytesvuelta,plin->creatramas,plin->lonida,plin->reconexiones,plin->consumo,plin->consumo232,plin->ciclotrabajo[0],st);
  poncolorv(&s->v,CNORMAL);
}

static int menulinea(etherboxs *peth)
{
  short *copia;
  copia=salvavd(&wlinea);
  enmarca(&wlinea,0,"Lineas");
  v10printf(&wlinea,"L. Act N.  Version Prim    Bucles   Tramas I Tramas V Errores  Bytes I    Bytes V    T.Calc.  Lon  Rec. Consumo  Con232   C  St\n");
  v10printf(&wlinea,"ออ อออ อออ อออออออ อออออออ ออออออออ ออออออออ ออออออออ ออออออออ ออออออออออ ออออออออออ ออออออออ ออออ ออออ ออออออออ ออออออออ ออ ออ");
  selecciona(0,2,0,0,1,&wlinea,MAXLINEAS,1,1,WANCHO(&wlinea),"Lineas",pintalineas,teclalineas,0,peth);
  recuperavd(&wlinea,copia);
  return(0);
}

static void renumeradisplays(void)
{
   int i,j,k,ndglob;
   for (i=0;i<numetherbox;i++) {
       etherboxs *peth=eth+i;
       for (j=0;j<MAXLINEAS;j++) {
           ethlineas *plin=peth->lin+j;
           ndglob=pdisplin(plin);
           if (peth->autonumera) {
              for (k=0;k<plin->numdisp;k++) {
                  displays *pdisp;
                  pdisp=damedisplayid(TIPOIDNUMDISP,ndglob+k);
                  if (peth->autonumera== AUTONUMDISP) displayprintfid(TIPOIDNUMDISP,ndglob+k,"%d",k+1);
                     else                             displayprintfid(TIPOIDNUMDISP,ndglob+k,"%d",pdisp->serie);
              }
           }
        }
    }
}

static int teclaeth(virtsels *s)
{
  int ret;
  int nz=VIRTPOS(s);
  etherboxs *peth=eth+nz;
  while (!hay_tecla_contimeout()) {
        if (ACTETH<MODIFICADOINFO) {
           repintapagina(s);
           poncursorsel(s);
           ACTETH=MODIFICADOINFO;
         }
        esperamensaje(10);
     }
  ret=tecla();
  switch (upper(ret)) {
     case cr: menulinea(peth);
              ret=0;
              break;
     case 'A':peth->autonumera=peth->autonumera?0:AUTONUMDISP;
              renumeradisplays();
              break;
     case 'I':peth->autonumera=peth->autonumera?0:AUTONUMSERIE;
              renumeradisplays();
              break;
     case 'S':pontodosdispeth(peth,TIPOIDSERIE);
              break;
     case 'N':pontodosdispeth(peth,TIPOIDNUMDISP);
              break;
     case ' ':pontodosdispeth(peth,-1);
              break;
     case 'T':{int i,j;
               modotest=modotest?0:1;
               for (i=0;i<numetherbox;i++) {
                   etherboxs *peth=eth+i;
                   for (j=0;j<MAXLINEAS;j++) {
                       ethlineas *plin=peth->lin+j;
                       plin->initlinea=0;
                    }
               }
              }
              break;
     default : if (ret>='0' && ret<='9') toggletodosdispeth(peth,ret-'0');
               break;
   }
  return(ret);
}

static void pintaeth(virtsels *s,int resal)
{
  int nz=VIRTPOS(s),ndglob;
  etherboxs *peth=eth+nz;
  int i,numdisp=0,abiertos=0,cerrados=0,st;
  ndglob=pdisplin(peth->lin);
  for (i=0;i<MAXLINEAS;i++) {
      ethlineas *lin=peth->lin+i;
      numdisp+=lin->numdisp;
      if (lin->v10s) {
         if (lin->v10s->status==STSOCKABIERTO) abiertos++;
            else                             cerrados++;
       } else cerrados++;
   }
  if (resal) {
     poncolorv(&s->v,CINPUTACT);
   }
  st=calcstglobeth(peth);
  v10printf(&s->v,"%2d %-*.*s %-7.7s %2d %2d %4d %7d %02X %-4.4s",
       nz+1,LDIRIP-1,LDIRIP-1,peth->dirip,infodameversion(peth->version),abiertos,cerrados,numdisp,ndglob,st,peth->autonumera==0?"No":peth->autonumera==AUTONUMDISP?"Num":"Ser");
  poncolorv(&s->v,CNORMAL);
}


static int menueth(void)
{
  short *copia;
  copia=salvavd(&weth);
  enmarca(&weth,0,"Ethernetbox");
  v10printf(&weth,"E. Dirip           Version A. C. Disp Prim    St Auto\n");
  v10printf(&weth,"ออ อออออออออออออออ อออออออ ออ ออ ออออ อออออออ ออ ออออ");
  selecciona(0,2,0,0,1,&weth,numetherbox,1,1,WANCHO(&weth),"Ethernet box",pintaeth,teclaeth,0,eth);
  recuperavd(&weth,copia);
  return(0);
}

static void pruebadisplays(void)
{
   static int ndisp;
   if (ndisp!=numdisp()) {
      renumeradisplays();
      ndisp=numdisp();
    }
   tickhleth();
   if (haytecladisp()) {
      tecladisps tec;
      tecladisp(&tec);
      escribe_log(LOGNORMAL,"Recibida tecla %d de display %X\n",tec.boton,tec.serie);
      switch (tec.boton) {
          case TECLAFUNCION: displayprintfid(TIPOIDSERIE,tec.serie,"%s",llinfodameversion(tec.version,1));
                            togglelucesdisplayid(TIPOIDSERIE,tec.serie,TECLAACEPTA+2);
                            break;
          case TECLAACEPTA: {displays *pdisp=damedisplayid(TIPOIDSERIE,tec.serie);
                             if (es_blanco(pdisp->valor))  {
                                displayprintfid(TIPOIDSERIE,tec.serie,"8888");
                                lucesdisplayid(TIPOIDSERIE,tec.serie,3,1);
                                lucesdisplayid(TIPOIDSERIE,tec.serie,4,1);
                                lucesdisplayid(TIPOIDSERIE,tec.serie,5,1);
                              } else {
                                displayprintfid(TIPOIDSERIE,tec.serie,"");
                                lucesdisplayid(TIPOIDSERIE,tec.serie,1,0);
                                lucesdisplayid(TIPOIDSERIE,tec.serie,2,0);
                                lucesdisplayid(TIPOIDSERIE,tec.serie,3,0);
                                lucesdisplayid(TIPOIDSERIE,tec.serie,4,0);
                                lucesdisplayid(TIPOIDSERIE,tec.serie,5,0);
                              }
                            break;
                            }
          case TECLAMAS:    displayprintfid(TIPOIDSERIE,tec.serie,"%d",tec.numdisp);
                            togglelucesdisplayid(TIPOIDSERIE,tec.serie,TECLAMAS+2);
                            break;
          case TECLAMENOS:  displayprintfid(TIPOIDSERIE,tec.serie,"%X",tec.serie);
                            togglelucesdisplayid(TIPOIDSERIE,tec.serie,TECLAMENOS+2);
                            break;
       }
    }
}

void presentainfo(void)
{
  pontrigervivo(pruebadisplays);
  while (1) {
        menueth();
        if (ult_pul==A_F(10)) return;
        Sleep(10);
    }
}

int main(int argc,char *argv[])
{
//   maxnivellog=1000;
   ttimeout=0;
   modotest=1;
   initv10logparam("PRUEBA.LOG",1,30,COLUMNASPANTALLA-2,10);
   if (argc<2) initinfopickex(TCICLO,TENVTRAMA,TIMEOUTTRAMA,TIMEOUTWHO,LIMITACIONLINEA,"192.168.0.29","127.0.0.1",NULL);
      else     initinfopickex(TCICLO,TENVTRAMA,TIMEOUTTRAMA,TIMEOUTWHO,LIMITACIONLINEA,argv[1],argc>2?argv[2]:NULL,argc>3?argv[3]:NULL,argc>4?argv[4]:NULL,argc>5?argv[5]:NULL);
   initvn(&weth,1,2,53,13,"DEFECTO");
   initvn(&wlinea,10,2,139,19,"DEFECTO");
   initvn(&wdisp,20,2,133,19,"DEFECTO");
   presentainfo();
   return(0);
}

int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hprev,
           LPSTR cmd, int cmdshow)
{
  int ret;
  v10usaansi=0;
  initv10lib(hinst,hprev); 
  trataparamstd(_argc,_argv,trataparammain,NULL);
  ret=main(_argc,_argv);
  return(ret);
}