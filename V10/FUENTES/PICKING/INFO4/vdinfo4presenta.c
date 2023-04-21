#include "info4\infopc.h"

static windows wcom;
static int initwcom;

static void initpresenta(void)
{

  if (initwcom==0) {
     //initvn(&wcom,1,27,NUMERO_COLUMNAS-3,42,"DEFECTO");
     initvn(&wcom,1,2,COLUMNASPANTALLA-2,15,"DEFECTO");
	 enmarca(&wcom,0,"Comunicacion");
	 wcom.t.t[CINPUTINAC].papel=0xFF00;wcom.t.t[CINPUTINAC].tinta=0x00FF00;
	 wcom.t.t[CINPUTACT].papel=0xFFFF;wcom.t.t[CINPUTACT].tinta=0xFFFF;
	 wcom.t.t[CMARCA].papel=0x7F;wcom.t.t[CMARCA].tinta=0xffffff;
	 wcom.t.t[CMARCON].papel=0xfF;wcom.t.t[CMARCON].tinta=0xffffff;
     initwcom=1;
  }
}	 


#define ANCHOLIN 30
#define LMIDIRIP4  17
void refrescalineas(void)
{
   int i,j;
   if (initwcom==0) initpresenta();
   for (i=0;i<numetherbox;i++) {
       etherboxs *peth=eth+i;
       wcom.cursory=i*6;
       wcom.cursorx=0;
       v10printf(&wcom,"%s",peth->dirip);
       for (j=0;j<MAXLINEAS-1;j++) {
           ethlineas *lin=peth->lin+j+1;
           wcom.cursory=i*6+j/4;
           wcom.cursorx=(j%4)*ANCHOLIN+LMIDIRIP4;
           if (lin->vds) {
            switch (lin->vds->status) {
                case STSOCKABIERTO:  poncolorv(&wcom,CINPUTINAC);
                                     break;
                default:poncolorv(&wcom,CMARCON);
                       break;
            }
           } else poncolorv(&wcom,CMARCON);
           v10printf(&wcom," ");
           poncolorv(&wcom,CNORMAL);
           if (lin->vds) v10printf(&wcom,"%5d %3d %6ld %6ld %2x",ntohs(lin->vds->port),lin->numdisp,lin->tramasvuelta,lin->errtrama,lin->stglob);
       }
   }
}