/*******************************************************************************
* M�dulo : VDCARGADEFBLOQUE.C                                                  *
* Funci�n: Carga desde ficheros .PAN las propiedades por defecto de los        *
*          bloques en la pantalla VDDEFBLOQUE                                  *
*                                                                              *
* Autor	 : Paco Guerrero                                                       *
* Revisado por:                                                                *
* Fecha  : 23-12-2008                                                          *
********************************************************************************

*******************************************************************************/

#include "execproc/vdexec.h"

static vddefbloques deb;
static int pdteptocoma=0;
static void (*fpdteptocoma)(char *linea,char *militeral,char *destino,char *priv);
static char *destpdteptocoma;

#define MAXLITERALES 18

typedef struct  {
	char *militeral;
	int tipo;	
	void *dest;
	void *priv;
	void (*func)(char *linea,char *militeral,char *destino,char *priv);
} itemdefbloque;

void fmuestralog(char *linea,char *militeral,char *destino,char *priv);
void fmasdeunalinea(char *linea,char *militeral,char *destino,char *priv);
void fprimeraletra(char *linea,char *militeral,char *destino,char *priv);
void fprivilegios(char *linea,char *militeral,char *destino,char *priv);


itemdefbloque defb[MAXLITERALES]=
					   {{"REGPAG="		,V10LONG,	&deb.numregpag,		NULL,				NULL},
                        {"POSX="		,V10LONG,	&deb.numposx,		NULL,				NULL},
						{"POSY="		,V10LONG,	&deb.numposy,		NULL,				NULL},
						{"ONLINE="		,V10CADENA,	deb.ayudaonline,	NULL,				fmasdeunalinea},
						{"TITULO="		,V10CADENA,	deb.titulobloque,	NULL,				NULL},
						{"AQUERY"		,V10CADENA,	deb.modoquery,		NULL,				fprimeraletra},
						{"TQUERY"		,V10CADENA,	deb.modoquery,		NULL,				fprimeraletra},
						{"PQUERY"		,V10CADENA,	deb.modoquery,		NULL,				fprimeraletra},
						{"CONTEXTUAL="	,V10CADENA,	deb.fcontextual,	NULL,				NULL},
//						{"TECLA="		,V10CADENA,	deb.ftecla,			NULL,				fmuestralog},
						{"UPPER"		,V10CADENA,	deb.capitaliza,		NULL,				fprimeraletra},
						{"LOWER"		,V10CADENA,	deb.capitaliza,		NULL,				fprimeraletra},
						{"MIXED"		,V10CADENA,	deb.capitaliza,		NULL,				fprimeraletra},
//						{"WHERE="		,V10CADENA,	deb.twhere,			NULL,				fmasdeunalinea},
//						{"ORDERBY="		,V10CADENA,	deb.torderby,		NULL,				fmasdeunalinea},
						{"NOINSERT"		,V10CADENA,	deb.cnoinsert,		deb.privinsert,		fprivilegios},
						{"NODELETE"		,V10CADENA,	deb.cnodelete,		deb.privdelete,		fprivilegios},
						{"NOENTER"		,V10CADENA,	deb.cnoenter,		deb.privnoenter,	fprivilegios},
						{"NOUPDATE"		,V10CADENA,	deb.cnoupdate,		deb.privupdate,		fprivilegios},
						{"NOORAINS"		,V10CADENA,	deb.cnoorains,		deb.privorains,		fprivilegios},
						{"AYUDA="		,V10CADENA, deb.fayuda,			NULL,				NULL}};

void fmuestralog(char *linea,char *militeral,char *destino,char *priv) {
	char cadena[MAXCADENA]="",*ptr;
	strcpy(cadena,linea+strlen(militeral));
	ptr=strchr(cadena,',');
	*ptr=0;
	v10log(LOGNORMAL,"\tfmuestralog: Tecla %s definida en la pantalla\n",cadena);
}

void fmasdeunalinea(char *linea,char *militeral,char *destino,char *priv) {
	strcat(destino,linea+strlen(militeral));	
	if (!strchr(destino,';')) {
		strcat(destino,"\n");
		fpdteptocoma=fmasdeunalinea;	
		destpdteptocoma=destino;
		pdteptocoma=1;	
	} else {
		fpdteptocoma=NULL;
		destpdteptocoma=NULL;
		pdteptocoma=0;
	}
}

static void fprimeraletra(char *linea,char *militeral,char *destino,char *priv) {
	*destino=*militeral;
}

static void fprivilegios(char *linea,char *militeral,char *destino,char *priv) {
	char *ptri,*ptrf;
	
	*destino='S';
	ptri=strchr(linea,'(');
	if (!ptri) return;
	ptrf=strchr(linea,')');
	strcopia(priv,ptri+1,(ptrf-ptri)-1);
}

static int traralinea(char *buffer) {
	int i,escribir=1;
	char *ptr;

	if (pdteptocoma) {
		ptr=strstr(buffer,"\r\n");
		if (ptr)  *ptr=0;		
		fpdteptocoma(buffer,"",destpdteptocoma,NULL);
		return(0);
	}

	for (i=0;i<MAXLITERALES;i++) {
		ptr=strstr(buffer,defb[i].militeral);
		if (ptr && ptr==buffer) { // est� al principio de la linea
			escribir=0;
			ptr=strstr(buffer,"\r\n");
			if (ptr)  *ptr=0;				
			if (!defb[i].func) {
				switch (defb[i].tipo) {
					case V10CADENA:						
						strcpy(defb[i].dest,buffer+strlen(defb[i].militeral));
						return(escribir);
					case V10LONG:
						*((long *)defb[i].dest)=atol(buffer+strlen(defb[i].militeral));
						return(escribir);
				}

			} else  {
				defb[i].func(buffer,defb[i].militeral,defb[i].dest,defb[i].priv);
				return(escribir);
			}
		}
	}

	return(escribir);
}

static void guardarpropiedades(char *path,char *directorio,char *fichero,int updfichero,char *tipopantalla) {
	int ret,escribir;
	char nombrecompleto[MAXPATH]="",nombrecompletonew[MAXPATH]="",*ptr,buffer[1025]="",midirectorio[MAXPATH]="";
	FILE *fin,*foutput=NULL;

	sprintf(nombrecompleto,"%s\\%s",path,fichero);
		
	if (updfichero) {
		strcpy(nombrecompletonew,nombrecompleto);
		ptr=strstr(strmay(nombrecompletonew),".PAN");
		*ptr=0;
		strmay(nombrecompletonew);
		strcat(nombrecompletonew,".NEW");
		foutput=fopen(nombrecompletonew,"wb");
		if (!foutput) {
			mensajefcm(10,"No puedo abrir fichero %s",nombrecompletonew);
			return;
		}
	}

	rollback();
	memset(&deb,0,sizeof(deb));
	strcpy(deb.nbloque,fichero);
	ptr=strstr(strmay(deb.nbloque),".PAN");
	*ptr=0;
	strcopia(midirectorio,directorio,strlen(directorio)-1);
	ptr=strrchr(midirectorio,'\\');
	if (ptr) strcpy(deb.grupobloque,ptr+1);
	else strcpy(deb.grupobloque,midirectorio);
	strcpy(deb.tipopantalla,tipopantalla);

	if (access(nombrecompleto,0)==0) {
		v10log(LOGNORMAL,"Encontrado fichero %s\n",nombrecompleto);
		fin=fopen(nombrecompleto,"rb");
		while (fgets(buffer,1024,fin)!=NULL) {
			escribir=traralinea(buffer);
			if (escribir && foutput) fprintf(foutput,"%s",buffer);
		}
		fclose(fin);
	} 

	if (foutput) fclose(foutput);

	ret=DEBinsert(&deb,0);
	if (ret==0) {
		commit();
		if (updfichero) {
			unlink(nombrecompleto);
			muevefich(nombrecompletonew,strmay(nombrecompleto));
		}
	}
}

static void buscarficheros(char *path,int updfichero,char *tipopantalla,char *pantallas) {
    HANDLE handle; 
	char directorio[MAXPATH],nombre[MAXPATH],nuevonombre[MAXPATH]="",*ptr; 
	WIN32_FIND_DATA finddata;
	strcpy(directorio,path);
	if (directorio[strlen(directorio)-1]!='\\') strcat(directorio,"\\");
	sprintf(nombre,"%s*.*",directorio);
	handle=FindFirstFile(nombre,&finddata);
	while (handle) {
		if (*finddata.cFileName!='.') {
			if (finddata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)  {
				sprintf(nuevonombre,"%s%s",directorio,finddata.cFileName);		
				buscarficheros(nuevonombre,updfichero,tipopantalla,pantallas);
			}
			else {
				ptr=strstr(strmay(finddata.cFileName),".PAN");
				if (ptr && finddata.cFileName+strlen(finddata.cFileName)==ptr+4 &&
					(*pantallas==0 || contiene(pantallas,finddata.cFileName)>0)) 
						guardarpropiedades(path,directorio,finddata.cFileName,updfichero,tipopantalla);
			}
		}
		if (FindNextFile(handle,&finddata)==0) break;
	}
	FindClose(handle);
}


// carga en la tabla vddefbloque las propiedades por defectos de las pantallas .PAN que 
// cuelgan de la ruta pasada como par�metro
VDEXPORT void vdcargadefbloque(procesos *proceso)
{   int updficheros;  
    char rutaficheros[MAXPATH ]="",cupdficheros[2]="",tipopantalla[2]="",pantallas[MAXPATH]="";

	piece(proceso->proc.param,rutaficheros,"#",1);
	piece(proceso->proc.param,cupdficheros,"#",2);
	piece(proceso->proc.param,tipopantalla,"#",3);
	piece(proceso->proc.param,pantallas,"#",4);
	if (*tipopantalla==0) *tipopantalla='F';

	updficheros=atoi(cupdficheros);
	buscarficheros(rutaficheros,updficheros,tipopantalla, pantallas);
	exit(0);
}

