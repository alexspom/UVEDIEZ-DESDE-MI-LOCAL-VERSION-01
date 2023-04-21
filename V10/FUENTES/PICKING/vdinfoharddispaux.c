/****
* vdinfoharddispaux.c - Funciones para el tratamiento a bajo de nivel de los displays
* 
* Propósito: Funciones para el tratamiento a bajo de nivel de los displays
*           
* Autor	   : MGM
* Fecha    : 24-03-2008                                   
****/

#include "vdinfopicking.h"

static char *nombreteclas[]={"VALIDA","MAS","MENOS","FUNC"};
static char *nombrevirtuales[]={"INIT","TICK"};
static int cont=0; 

char *damenombretecla(int ntecla)
{
	char **minombretecla=nombreteclas;
	if (ntecla>=1000) {
		ntecla-=1000;
		minombretecla=nombrevirtuales;
	}
	if (ntecla<0) return ("DESCONOCIDA");
	return(minombretecla[ntecla]);
}


VDEXPORT int vdinfodametecla(int idinfogest,vdinfomensajes *ite)
{
	int ret;
	vdinfoharddisps ihd;
	char mitecla[LTECLAS],*aux;
	ret=IHDbuscateclas(idinfogest,&ihd);
	if (ret!=0) return(ret);
	if (*ihd.teclas=='#') strcpy(ihd.teclas,ihd.teclas+1);
	piece(ihd.teclas,mitecla,"#",1);
	memset(ite,0,sizeof(*ite));
	ite->tipomensaje=INFOMENTECLA;
	ite->numdisp=ihd.numdisp;
	ite->idinfopick=ihd.idinfopick;
	ite->nmensaje=atoi(mitecla);
	if ((aux=strchr(ihd.teclas,'#'))!=NULL) {
		strcpy(ihd.teclas,aux+1);
	} else {
		strcpy(ihd.teclas,"");
	}
	IHDactualizateclas(&ihd,0);
	return(0);
}

#define MAXLUCESDISPLAYS 8

static void vdponlucespadre(vdinfoharddisps *ihd) {
	char valorluz[3];
	int i=0,ret=0;
	int lucesfinal[MAXLUCESDISPLAYS];
	vdinfodisps idiluz, idi; 
	vdinfoharddisps ihdluz, ihdluzpadre;
	vdplsqlcomens com;
	int liparpadeo=1; 

	memset(valorluz,0,sizeof(valorluz));
	piece(ihd->luces, valorluz,",",1);
	if (valorluz[0]=='*') return;

	lucesfinal[0]=atoi(valorluz);
	memset(valorluz,0,sizeof(valorluz));
	piece(ihd->luces, valorluz,",",2);
	lucesfinal[1]=atoi(valorluz); 
	memset(valorluz,0,sizeof(valorluz));
	piece(ihd->luces, valorluz,",",3);
	lucesfinal[2]=atoi(valorluz); 
	memset(valorluz,0,sizeof(valorluz));
	piece(ihd->luces, valorluz,",",4);
	lucesfinal[3]=atoi(valorluz); 
	memset(valorluz,0,sizeof(valorluz));
	piece(ihd->luces, valorluz,",",5);
	lucesfinal[4]=atoi(valorluz);
	memset(valorluz,0,sizeof(valorluz));
	piece(ihd->luces, valorluz,",",6);
	lucesfinal[5] = atoi(valorluz);
	piece(ihd->luces, valorluz, ",", 7);
	lucesfinal[6] = atoi(valorluz);
	piece(ihd->luces, valorluz, ",", 8);
	lucesfinal[7] = atoi(valorluz);

	// Buscamos si el display tiene un padre de luces
	ret=IDIselvdinfodisp(ihd->idinfopick,ihd->numdisp,&idiluz);
	if(!ret) // Buscamos el texto del display padre 
		ret=IHDselvdinfoharddisp(idiluz.idinfopickluz,idiluz.numluz,&ihdluzpadre);
    // Buscamos si es el único display con luces
	ret=IDIbuscaluzpadre(idiluz.idinfopickluz,idiluz.numluz,&idi);
	do{ 
		if (!(idi.idinfopick == idiluz.idinfopickluz && idi.numdisp == idiluz.numluz && !strcmp(ihdluzpadre.texto,""))){
			// Buscamos la luz del display
			ret=IHDselvdinfoharddisp(idi.idinfopick,idi.numdisp,&ihdluz);
			// Buscamos si la luz debe encenderse parpadeando
			PLSQLCOMENbuscadamecomen(ihd->codcomen,"PARPADEO",1,&com);
			if(!strcmp(com.comentario,"S")) liparpadeo=2;
			for (i=0;i<MAXLUCESDISPLAYS;i++) {
				memset(valorluz,0,sizeof(valorluz));
				piece(ihdluz.luces, valorluz,",",i+1);
				// No ha indicado valor para esa luz
				if (*valorluz==0) {			
					piece(ihd->luces, valorluz,",",i+1);
					if (*valorluz==0) valorluz[0]='0';
				}
				if (lucesfinal[i] < atoi(valorluz)) lucesfinal[i]=atoi(valorluz); 
			}
		}
	}while (!IDInextluzpadre(&idi));

	sprintf(ihdluzpadre.luces,"%d,%d,%d,%d,%d,%d,%d,%d",
			lucesfinal[0]==1?liparpadeo:lucesfinal[0],
			lucesfinal[1]==1?liparpadeo:lucesfinal[1],
			lucesfinal[2]==1?liparpadeo:lucesfinal[2],
			lucesfinal[3]==1?liparpadeo:lucesfinal[3],
			lucesfinal[4] == 1 ? liparpadeo : lucesfinal[4],
			lucesfinal[5] == 1 ? liparpadeo : lucesfinal[5],
			lucesfinal[6] == 1 ? liparpadeo : lucesfinal[6],
			lucesfinal[7] == 1 ? liparpadeo : lucesfinal[7]);
     
	ihdluzpadre.status=STIHDPENDIENTE;
    ret=IHDactualizastytexto(&ihdluzpadre,NOVERIFICA);
	if (ret) v10log(LOGERROR,"vdinfoprintf: Error actualizando VDINFOHARDDISP del display %d-%d a estado %d\n",
	    	ihdluzpadre.idinfopick,ihdluzpadre.numdisp,ihdluzpadre.status);
}


static void vdponluces(vdinfoharddisps *ihd,char *luces) {
	
	char valorluz[3];
	int i=0,ret=0;
	int lucesfinal[MAXLUCESDISPLAYS];
	vdplsqlcomens com;
	int liparpadeo=1; 

	memset(valorluz,0,sizeof(valorluz));
	piece(luces, valorluz,",",1);
	if (valorluz[0]=='*') return;

	for (i=0;i<MAXLUCESDISPLAYS;i++) {
		memset(valorluz,0,sizeof(valorluz));
		piece(luces, valorluz,",",i+1);
		// no ha indicado valor para esa luz
		if (*valorluz==0) {			
			piece(ihd->luces, valorluz,",",i+1);
			if (*valorluz==0) valorluz[0]='0';
		} 
		lucesfinal[i]=atoi(valorluz);
	}
	memset(&com,0,sizeof(com));
	PLSQLCOMENbuscadamecomen(ihd->codcomen,"PARPADEO",1,&com);
	if(!strcmp(com.comentario,"S")) liparpadeo=2;

	sprintf(ihd->luces, "%d,%d,%d,%d,%d,%d\0",
		lucesfinal[0] == 1 ? liparpadeo : lucesfinal[0],
		lucesfinal[1] == 1 ? liparpadeo : lucesfinal[1],
		lucesfinal[2] == 1 ? liparpadeo : lucesfinal[2],
		lucesfinal[3] == 1 ? liparpadeo : lucesfinal[3],
		lucesfinal[4] == 1 ? liparpadeo : lucesfinal[4],
		lucesfinal[5] == 1 ? liparpadeo : lucesfinal[5],
		lucesfinal[6] == 1 ? liparpadeo : lucesfinal[6],
		lucesfinal[7] == 1 ? liparpadeo : lucesfinal[7]);
}

VDEXPORT int vdinfoprintf(int idinfopick,int numdisp,char *format,...)
{
	va_list arg;
	char destino[MAXCADENA],*luces;
	vdinfoharddisps ihd;
	vdpickings picking;
	int ret;
	
    va_start(arg,format);
	vsprintf(destino,format,arg);
	va_end(arg);
	ret=IHDselvdinfoharddisp(idinfopick,numdisp,&ihd);
	if (ret!=0) {
		v10log(LOGNORMAL,"Intentando escribir en display %d-%d inexistente\n",idinfopick,numdisp);
		return(-1);
	}
	luces=strchr(destino,'$');
	if (luces) *luces++=0;
	strcpy(ihd.texto,destino);
//	ret=IHDactualizastytexto(&ihd,0); 
	if (luces) vdponluces(&ihd,luces); 
	else  strcpy(ihd.luces,"0,0,0,0,0,0");
	ihd.status=STIHDPENDIENTE;
    ret=IHDactualizastytexto(&ihd,0);
	if (ret) v10log(LOGERROR,"vdinfoprintf: Error actualizando VDINFOHARDDISP del display %d-%d a estado %d\n",
	    	idinfopick,numdisp,ihd.status);
	ret=PICKINGbuscahijosluz(ihd.idinfopick,ihd.numdisp,&picking);
	if(!ret) vdponlucespadre(&ihd); 
	return(strlen(ihd.texto));
}

VDEXPORT int vdinfoencolatecla(int idinfopick,int numdisp,int nboton,int causa)
{
	vdinfoharddisps ihd;
    v10log(LOGNORMAL,"Encolando tecla Idinfopick %d Numdisp %d tecla %d causa %d\n",idinfopick,numdisp,nboton,causa);
    IHDselvdinfoharddisp(idinfopick,numdisp,&ihd);
    if (strlen(ihd.teclas)==0) {
	   sprintf(ihd.teclas, "#%d$%d", nboton, causa);
	   IHDactualizateclas(&ihd,0);
	   return(0);
    }
	return(-1);
}

