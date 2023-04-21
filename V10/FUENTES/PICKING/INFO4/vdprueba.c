#include "vd.h"
#include "infopc.h"

static windows weth,wdisp,wlinea;
static int ACTETH,ACTLINEAS,ACTDISP;

static int calcstgloblin(ethlineas *lin)
{
  int i,st;
  int ndglob;
  ndglob=pdisplin(lin);
  st=0;
  for (i=0;i<lin->numdisp;i++) {
      displays *disp=damedisplayid(ndglob+i);
      if (disp==NULL) continue;
      st|=disp->status[0];
    }
  return(st);
}

static void pontodosdisplin(ethlineas *lin,int ret)
{
  int i;
  int ndglob;
  ndglob=pdisplin(lin);
  for (i=0;i<lin->numdisp;i++) {
      displays *disp=damedisplayid(ndglob+i);
      if (disp==NULL) continue;
	  switch (ret) {
	  case 'N':  displayprintfp(disp, "%d", i + 1);
	  case 'S':  displayprintfp(disp, "%d", disp->serie);
	  case ' ':  displayprintfp(disp, "");
	  }
    }
}

static void pontodosdisplin8(ethlineas *lin)
{
  int i,j;
  int ndglob;
  ndglob=pdisplin(lin);
  for (i=0;i<lin->numdisp;i++) {
      displays *disp=damedisplayid(ndglob+i);
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
      displays *disp=damedisplayid(ndglob+i);
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

static void pontodosdispeth(etherboxs *peth,int ret)
{
  int i;
  for (i=0;i<MAXLINEAS;i++) {
      pontodosdisplin(peth->lin+i,ret);
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
  pdisp=damedisplayid(ndglob+nz);
  while (!hay_tecla_contimeout()) {
        if (numdisp!=plin->numdisp) {
           encolatecla(esc);
           encolatecla(cr);
         }
        if (ACTDISP<MODIFICADOINFO) {
           representapagina(s);
           poncursorsel(s);
           ACTDISP=MODIFICADOINFO;
         }
        esperamensaje(10);
     }
  ret=tecla();
  switch (toupper(ret)) {
     case cr: ret=0;
              break;
     case 'S': displayprintfp(pdisp,"%d",pdisp->serie);
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
     case 'T': if (*pdisp->valor<17) {
                  (*pdisp->valor)++;
                  if (*pdisp->valor>17) *pdisp->valor=1;
                  displayprintfp(pdisp,"%c%c%c%c",*pdisp->valor,*pdisp->valor,*pdisp->valor,*pdisp->valor);
                }
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
  ndglob=pdisplin(plin);
  pdisp=damedisplayid(ndglob+nz);
  if (resal) {
     poncolorv(&s->v,CINPUTACT);
   }
  tipo=dametipo(pdisp->tipo);
  v10printf(&s->v,"%7d %3d %8d %-7.7s %2d %-10.10s %02X %-*.*s %d%d%d%d%d%d%d %7ld %8ld %8ld",
       ndglob+nz,nz+1,pdisp->serie,infodameversion(pdisp->version),pdisp->tipo,tipo->nombre,pdisp->status[0],MAXDIGDISPLAY-1,MAXDIGDISPLAY-1,pdisp->valor,pdisp->luces[0],pdisp->luces[1],pdisp->luces[2],pdisp->luces[3],pdisp->luces[4],pdisp->luces[5],pdisp->luces[6],pdisp->errhard,pdisp->errtrama,pdisp->consumo);
  poncolorv(&s->v,CNORMAL);
}

static int menudisp(ethlineas *plin)
{
  short *copia;
  copia=salvavd(&wdisp);
  enmarca(&wdisp,0,"Displays");
  v10printf(&wdisp,"Dis.    Num Serie    Version T. Tipo       St Valor               Luces   Errhard Errtrama Consumo\n");
//  v10printf(&wdisp,"อออออออ อออ ออออออออ อออออออ ออ ออออออออออ ออ อออออออออออออออออออ อออออออ อออออออ ออออออออ ออออออออ");
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
           representapagina(s);
           poncursorsel(s);
           ACTLINEAS=MODIFICADOINFO;
         }
         esperamensaje(10);
     }
  ret=tecla();
  switch (toupper(ret)) {
     case cr: menudisp(plin);
              ret=0;
              break;
     case 'N':pontodosdisplin(plin,ret);
              break;
     case 'P':pontodosdisplin8(plin);
              break;
     case ' ':pontodosdisplin(plin,ret);
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
  if (plin->vds==NULL) stglob=0;
     else              if (plin->vds->status!=STSOCKABIERTO) stglob=0;
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
  //v10printf(&wlinea,"ออ อออ อออ อออออออ อออออออ ออออออออ ออออออออ ออออออออ ออออออออ ออออออออออ ออออออออออ ออออออออ ออออ ออออ ออออออออ ออออออออ ออ ออ");
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
                  pdisp=damedisplayid(ndglob+k);
                  if (peth->autonumera== AUTONUMDISP) displayprintfid(ndglob+k,"%d",k+1);
                     else                             displayprintfid(ndglob+k,"%d",pdisp->serie);
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
           representapagina(s);
           poncursorsel(s);
           ACTETH=MODIFICADOINFO;
         }
        esperamensaje(10);
     }
  ret=tecla();
  switch (toupper(ret)) {
     case cr: menulinea(peth);
              ret=0;
              break;
     case 'A':peth->autonumera=peth->autonumera?0:AUTONUMDISP;
              renumeradisplays();
              break;
     case 'I':peth->autonumera=peth->autonumera?0:AUTONUMSERIE;
              renumeradisplays();
              break;
     case 'S':pontodosdispeth(peth,ret);
              break;
     case 'N':pontodosdispeth(peth,ret);
              break;
     case ' ':pontodosdispeth(peth,ret);
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
      if (lin->vds) {
         if (lin->vds->status==STSOCKABIERTO) abiertos++;
            else                             cerrados++;
       } else cerrados++;
   }
  if (resal) {
     poncolorv(&s->v,CINPUTACT);
   }
  st=calcstglobeth(peth);
  v10printf(&s->v,"%2d %-*.*s %-7.7s %2d %2d %4d %7d %02X %-4.4s",
       nz+1,LDIRIPINFO4-1,LDIRIPINFO4-1,peth->dirip,infodameversion(peth->version),abiertos,cerrados,numdisp,ndglob,st,peth->autonumera==0?"No":peth->autonumera==AUTONUMDISP?"Num":"Ser");
  poncolorv(&s->v,CNORMAL);
}


static int menueth(void)
{
  short *copia;
  copia=salvavd(&weth);
  enmarca(&weth,0,"Ethernetbox");
  v10printf(&weth,"E. Dirip           Version A. C. Disp Prim    St Auto\n");
//  v10printf(&weth,"ออ อออออออออออออออ อออออออ ออ ออ ออออ อออออออ ออ ออออ");
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
      v10log(LOGNORMAL,"Recibida tecla %d de display %d serie %d\n",tec.boton,tec.numdisp,tec.serie);
      switch (tec.boton) {
          case TECLAFUNCION: displayprintfid(tec.numdisp,"%s",llinfodameversion(tec.version,1));
			  togglelucesdisplayid( tec.numdisp, TECLAACEPTA + 2);
                            break;
		  case TECLAACEPTA: {displays *pdisp = damedisplayid( tec.numdisp);
                             if (es_blanco(pdisp->valor))  {
								 displayprintfid( tec.numdisp, "8888");
								 lucesdisplayid( tec.numdisp, 3, 1);
								 lucesdisplayid( tec.numdisp, 4, 1);
								 lucesdisplayid( tec.numdisp, 5, 1);
                              } else {
								 displayprintfid( tec.numdisp, "");
								 lucesdisplayid( tec.numdisp, 1, 0);
                                lucesdisplayid(tec.numdisp,2,0);
                                lucesdisplayid(tec.numdisp,3,0);
                                lucesdisplayid(tec.numdisp,4,0);
                                lucesdisplayid(tec.numdisp,5,0);
                              }
                            break;
                            }
          case TECLAMAS:    displayprintfid(tec.numdisp,"%d",tec.numdisp);
                            togglelucesdisplayid(tec.numdisp,TECLAMAS+2);
                            break;
          case TECLAMENOS:  displayprintfid(tec.numdisp,"%d",tec.numdisp);
                            togglelucesdisplayid(tec.numdisp,TECLAMENOS+2);
                            break;
       }
    }
}

static void presentainfo(void)
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
   ttimeout=0;
   modotest=1;
   initvn(&weth,5,15,60,22,"TAREAS");
   initvn(&wlinea,7,20,150,35,"TAREAS");
   initvn(&wdisp,9,22,133,45,"TAREAS");
   presentainfo();
   Sleep(10);
   return(0);
}

int trataparameos(char *cadena)
{
    if (*cadena == 'E') {
        if (cadena[1] == 'I') initinfopick(TCICLO, TENVTRAMA, TIMEOUTTRAMA, TIMEOUTWHO, LIMITACIONLINEA, cadena+2, NULL);
    }
	return(0);
}

int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hprev,
           LPSTR cmd, int cmdshow)
{
  int ret=0;
  v10hinst=hinst;
  v10hprev=hprev;
  COLUMNASPANTALLA=160;
  LINEASPANTALLA=55;
  trataparamstd(__argc,__argv,trataparampremain,NULL);
  initapptxt(hinst,hprev,SW_SHOWMAXIMIZED,TITULOVENTANA,CW_USEDEFAULT,CW_USEDEFAULT,
                   0,0,COLUMNASPANTALLA,LINEASPANTALLA,ESTILOV10,0,NULL,0,0,NULL);
  trataparamstd(__argc,__argv,trataparammain,trataparameos,NULL);
  ret=main(__argc,__argv);
  return(ret);
}
