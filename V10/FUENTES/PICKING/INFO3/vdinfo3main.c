#include "vdinfopicking.h"
#include "info3.h"

static int sidinfopick;

VDEXPORT void vdinfoinit(int idinfopick)
{
    int ret;
    vdinfohards iha;
    sidinfopick=idinfopick;
    ret=IHAselvdinfohard(idinfopick,&iha);
    infotconfig.tipodir=TIPOIDNUMDISP;
	infotconfig.fichwho=1;
	infotconfig.delaycab=iha.tenvtrama;
	infotconfig.statsgap=iha.statgaps;
	infotconfig.watchdog=iha.statgaps+100;
	infotconfig.queue=10;
	infotconfig.queue_timeout=10;
	infotconfig.maxerror=iha.maxerror;
	infotconfig.ratioerr=iha.maxerror;
	infotconfig.tparpada=iha.tparpada;
	infotconfig.tparpade=iha.tparpade;
    infoinit3(idinfopick,iha.dirip1,iha.dirip2,iha.dirip3,iha.dirip4,iha.dirip5,NULL);
}


void traducecadena(int disp, char *cadena){
   infotdefdisps *t;
   char cadenaaux[14+1];
   char aux[2];
   
   t=infotipo(disp);
   if (t==NULL) return;
   if (t->bytes==9){
	   if (!strcmp(cadena,"NSTK")) strcpy(cadena,"NST");
	   if (!strcmp(cadena,"BLOQUEO")) strcpy(cadena,"BLOQ");
       if (!strcmp(cadena,"ERR-ART")) strcpy(cadena,"ER");
	   if (!strcmp(cadena,"ERR-LOT")) strcpy(cadena,"ER");
	   if (!strcmp(cadena,"ERR-UNIEMB")) strcpy(cadena,"ER");
	   if (!strcmp(cadena,"ERROR")) strcpy(cadena,"ER");

	   if (cadena[0]=='L'||cadena[0]=='A'||cadena[0]=='M') {
		   aux[0]=cadena[0];
		   strncpy(cadena+1,cadena+2,strlen(cadena));
		   cadena[strlen(cadena)]='\0';
		   if (strlen(cadena)>5) {
			   strncpy(cadena,cadena+(strlen(cadena)-5),strlen(cadena));
			   cadena[0]=aux[0];
			   cadena[5]='\0';
		   }else cadena[strlen(cadena)+1]='\0';
	   }
   }if (t->bytes==26){
	   if (strlen(cadena)>12){ 
		   strncpy(cadena,cadena+(strlen(cadena)-12),strlen(cadena)); 
	       cadena[12]='\0';
	   }
   }
}

void traduceluces(int disp, char *luces){
   infotdefdisps *t;
   char luzval[2],luzval1[2],luzval2[2],luzval3[2],luzmas[2],luzmenos[2];
   
   piece(luces,luzval1,",",3);
   piece(luces,luzval2,",",4);
   piece(luces,luzval3,",",5);

   if (atoi(luzval1)==2||atoi(luzval2)==2||atoi(luzval3)==2||atoi(luzval1)==3||atoi(luzval2)==3||atoi(luzval3)==3)	
	   strcpy(luzval,"2");
   else if (atoi(luzval1)==1||atoi(luzval2)==1||atoi(luzval3)==1)
	   strcpy(luzval,"1");
   else strcpy(luzval,"0");

   piece(luces,luzmas,",",1);
   piece(luces,luzmenos,",",1); 
   if (atoi(luzmas)==3) strcpy(luzmas,"2");
   if (atoi(luzmenos)==3) strcpy(luzmenos,"2");
   t=infotipo(disp);
   if (t==NULL) return;
   if (t->bytes==26) sprintf(luces,"%s,%s,%s,0,0,0",luzval,luzmas,luzmenos); 
   if (t->bytes==9) sprintf(luces,"%s,%s,0,0,0,0",luzval,luzmas!=0?luzmas:luzmenos); 
}


VDEXPORT int vdinfoprint(int iddisplay,char *cadena,char *luces)
{
    char numluz[20];
    int i=0;

	traducecadena(iddisplay, cadena);
 	traduceluces(iddisplay, luces);
    infoprintf(iddisplay,"%s",cadena);
	if (!es_blanco(luces)) {
       while (piece(luces,numluz,",",i+1)!=-1) {
           if (!es_blanco(numluz)) infoponluz(iddisplay,i,atoi(numluz));
           i++;
	   }
	}
	for (;i<MAXLUCESDISPLAY;i++) infoponluz(iddisplay,i,0);
    return(strlen(cadena));
}

void traduceboton(int disp, int *tecla){
   infotdefdisps *t;
   
   t=infotipo(disp);
   if (t->bytes==9){
	   if (*tecla==0) *tecla=2;
	   else if (*tecla==2) *tecla=0; 
   }
   else if (t->bytes==26){
       if (*tecla==1) *tecla=2;
	   else if (*tecla==2) *tecla=1;
   }
}


VDEXPORT int vddametecla(vdinfomensajes *men)
{
    infotteclas mitec;
    if (infohaytecla()) {
        infotecla(&mitec);
		traduceboton(mitec.disp, &mitec.boton);
		memset(men,0,sizeof(*men));
		men->tipomensaje=INFOMENTECLA;
        men->numdisp=mitec.disp;
        men->nmensaje=mitec.boton;
        men->causa=mitec.causa;
		men->param=NULL;
		men->funlibera=NULL;
        return(1);
    }
    return(0);
}

VDEXPORT void vdtickinfo(void)
{
}
    
