    /*
* Módulo :  v10httpconfig.c
* Objeto:   Carga valores para parámetros HTTP
* 
* 
* Autor	 : Francisco José Guerrero Sánchez
* Fecha  : 25-09-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10wwwform.h"


typedef struct {
	char *nombre;
	void *ptr;
	int tipo;
} defvars;


static defvars dvar[]={
	{"RELEECONF",&v10httpconf.releeconfig,V10INT},  
	{"ACCESO",&v10httpconf.acceso,V10CHAR},
	{"NIVELLOG",&v10httpconf.nivellog,V10INT},
	{"PROTEGIDO",&v10httpconf.protegido,V10INT},
	{"DEBUGHTTP",&v10httpconf.debughttp,V10INT},
	{"VISIBLEEXE",&v10httpconf.visibleexe,V10INT},
	{"FICHEROEXE",&v10httpconf.ficheroexe,V10CHAR},
    { "CONEXIONBD", &v10httpconf.conexionBD, V10CHAR },
    { "SERVIDOR", &v10httpconf.v10servidor, V10CHAR },
    { "PREFIJOSERVICIO", &v10httpconf.prefijoservicio, V10CHAR },
	{"SERVERPORT",&v10httpconf.v10puertoservidor,V10CHAR},
	{"SERVERPORTFILES",&v10httpconf.v10puertomisc,V10CHAR},
	{"PUERTOINICIAL",&v10httpconf.v10puertoinicial,V10CHAR},
	{"SERVERHTML",&v10httpconf.v10serverhtml,V10CHAR},
	{"SERVERIMG",&v10httpconf.v10serverimg,V10CHAR},
	{"SERVERXLS",&v10httpconf.v10serverxls,V10CHAR},
	{"SERVERPDF",&v10httpconf.v10serverpdf,V10CHAR},
	{"FILEEXPIRED",&v10httpconf.fileexpired,V10INT},
	{"TIEMPOESPERA",&v10httpconf.tiempoespera,V10INT},
	{"RUTAINICIAL",&v10httpconf.rutainicial,V10CHAR},
	{"LIBRERIAV10",&v10httpconf.libreriaV10,V10CHAR},
	{"LIBRERIAMENUV10",&v10httpconf.libreriamenuV10,V10CHAR},
	{"MENU",&v10httpconf.menu,V10CHAR},
	{"USUARIO",&v10httpconf.usuario,V10CHAR},
	{"PASSWORD",&v10httpconf.password,V10CHAR},	
    { "SSL", &v10httpconf.ssl, V10INT },
    { "SSLKEYFILE", &v10httpconf.sslkeyfile, V10CHAR },
    { "SSLCERTFILE", &v10httpconf.sslcertfile, V10CHAR },
	{"SSLPASSWORD",&v10httpconf.sslpassword,V10CHAR},
	{"SSLDHFILE",&v10httpconf.dhfile,V10CHAR},
	{"SSLCA_LIST",&v10httpconf.ca_list,V10CHAR},
	{"RUTAZIP",&v10httpconf.rutazip,V10CHAR},
	{"RUTAHELP",&v10httpconf.rutahelp,V10CHAR},
	{"RUTAPLANTILLAS",&v10httpconf.rutaplantillas,V10CHAR},
	{"RUTAXLS",&v10httpconf.rutaxls,V10CHAR},
	{"RUTAPDF",&v10httpconf.rutapdf,V10CHAR},
	{"COMPRIMIR",&v10httpconf.comprimir,V10INT},
	{"EXTRA",&v10httpconf.extra,V10CHAR},
	{"TECLADOVIRTUAL",&v10httpconf.tecladovirtual,V10INT},
	{"PREFIJOPLANTILLA",&v10httpconf.prefijoplantilla,V10CHAR},
	{"SERVERAJAX",&v10httpconf.v10serverAJAX,V10CHAR},	
	{"PUERTOAJAX",&v10httpconf.v10puertoAJAX,V10CHAR},	
	{"AJAXSIDEBARFRM",&v10httpconf.AJAXsidebarFRM,V10CHAR},
	{"AJAXSIDEBARMENU",&v10httpconf.AJAXsidebarMENU,V10CHAR},
	{"AJAXSIDEBARFRMVISIBLE",&v10httpconf.AJAXsidebarFRMvisible,V10INT},
	{"AJAXSIDEBARMENUVISIBLE",&v10httpconf.AJAXsidebarMENUvisible,V10INT}};


v10httpconfigs v10httpconf;

static void v10confhttp_pordefecto(void) 
{
	memset(&v10httpconf,0,sizeof(v10httpconf));
	v10httpconf.releeconfig=6000;
	strcpy(v10httpconf.acceso,"v10httpcliente");
	v10httpconf.nivellog=1;
	v10httpconf.protegido=4;
	v10httpconf.visibleexe=2;
	v10httpconf.debughttp=0;
	strcpy(v10httpconf.ficheroexe,"vdform.exe");
	strcpy(v10httpconf.conexionBD,"VD/VD@ORCL");
	strcpy(v10httpconf.v10servidor,"http://v10server");
	strcpy(v10httpconf.v10puertoservidor,"1234");
	strcpy(v10httpconf.v10puertomisc,"80");
	strcpy(v10httpconf.v10puertoinicial,"20000");
	strcpy(v10httpconf.v10serverhtml,"http://v10server:80/html");
	strcpy(v10httpconf.v10serverimg, "http://v10server:80/img");
	strcpy(v10httpconf.v10serverxls, "http://v10server:80/xls");
	strcpy(v10httpconf.v10serverpdf, "http://v10server:80/pdf");
	strcpy(v10httpconf.hostname,"");
	v10httpconf.fileexpired=5;
	v10httpconf.autorefresh=5;
	v10httpconf.tiempoespera=0;
	strcpy(v10httpconf.rutainicial,"v10.html");
	strcpy(v10httpconf.libreriaV10,"v10libreriajs.html");
	/*strcpy(v10httpconf.libreriamenuV10,"v10menujs.html");
	strcpy(v10httpconf.ficheromenujs,"html/scriptmenu.js");*/
	v10httpconf.versiondistribuida=0;
    v10httpconf.ssl = 0;
    strcpy(v10httpconf.sslkeyfile, "i:\\fuentes\\ssl\\server.pem");
    strcpy(v10httpconf.sslcertfile, "i:\\fuentes\\ssl\\server.pem");
	strcpy(v10httpconf.sslpassword,"meliton");
	strcpy(v10httpconf.dhfile, "i:\\fuentes\\ssl\\dh1024.pem");
	strcpy(v10httpconf.ca_list,"i:\\fuentes\\ssl\\root.pem");
	strcpy(v10httpconf.rutazip,"i:\\zip");
	strcpy(v10httpconf.rutaxls,"i:\\xls");
	strcpy(v10httpconf.rutahelp,"i:\\help\\html");
	strcpy(v10httpconf.rutaplantillas,"i:\\v10lib\\v10web\\html");
	v10httpconf.comprimir=0;
	*v10httpconf.extra=0;
	v10httpconf.tecladovirtual=0;
	*v10httpconf.prefijoplantilla=0;	
	strcpy(v10httpconf.v10serverAJAX,"http://v10server");	
	strcpy(v10httpconf.v10puertoAJAX,"4321");	
	strcpy(v10httpconf.AJAXsidebarFRM,"SIDEBAR;window.document.getElementById('sideBarContentsInner').innerHTML;F;VDJAX.DLL;includefichero;calendario.ajax;-1");
	strcpy(v10httpconf.AJAXsidebarMENU,"SIDEBAR;window.document.getElementById('sideBarContentsInner').innerHTML;F;VDAJAX.DLL;includefichero;calendario.ajax;-1");	
	v10httpconf.AJAXsidebarFRMvisible=2;	
	v10httpconf.AJAXsidebarMENUvisible=2;
}

static int asignavariable(char *cadena) 
{
	char *aux;
	int i;
	aux=strchr(cadena,'=');
	if (aux==NULL) {
		v10log(LOGNORMAL,"Variable %s no existe\n",cadena);
		return(-1);
	}
	*aux++=0;
	trim(cadena);
	trim(aux);
	for (i=0;i<sizeof(dvar)/sizeof(defvars);i++) {
		if (strcmp(cadena,dvar[i].nombre)==0) {
			switch (dvar[i].tipo) {
				case V10INT:
				if (!atoi(aux)) break;
				if (*(int *)dvar[i].ptr!=atoi(aux)) {
					v10log(LOGNORMAL,"Asignando %s a %s\n",aux,cadena);
					*(int *)dvar[i].ptr=atoi(aux);
				}
				break;

			case V10CHAR:				
				if (!(*(char *)dvar[i].ptr) || strcmp(((char *)dvar[i].ptr),aux)!=0) {
					v10log(LOGNORMAL,"Asignando %s a %s\n",aux,cadena);
					strcpy((char *)dvar[i].ptr,aux);
				}
				break;
			}
			break;
		}
	}
	return(0);
}

static void leeconf(char *file) 
{	
	FILE *f;
	char buffer[MAXCADENA],bak[MAXCADENA],*ptr;
	f=fopenpath(file,"r");
	if (!f) {
		mensajefcm(10,"No puedo abrir fichero de configuración %s",file);
		exit(0);
	}
	while (fgetss(buffer,sizeof(buffer)-1,f)) {
		strcpy(bak,buffer);
		ptr=strstr(buffer,"/*");
		if (ptr) { 
			trim(buffer);			
			*ptr=0;
			if (strlen(buffer)==0) {
				v10log(LOGNORMAL,"Comentario: %s\n",bak);
				continue;	
			}
		}
		asignavariable(buffer);
	}
	fclose(f);
	v10log(1,"Cargado fichero %s\n",file);
}
#define CSELCONF "SELECT VD.GETPROPEX(:PROPIEDAD,:INSTANCIA,1,' ') FROM DUAL"
static v10cursors *v10selconf;
#define LPROPIEDAD 65
#define LVALOR 256
typedef struct {
    char instancia[LPROPIEDAD];
    char propiedad[LPROPIEDAD];
    char valor[LVALOR];
} props;
static props prop;
static void initconf(void)
{
    v10selconf = abrecursor(CSELCONF);
    bindtodo(v10selconf, "PROPIEDAD", prop.propiedad, sizeof(prop.propiedad), V10CADENA,
              "INSTANCIA", prop.instancia, sizeof(prop.instancia), V10CADENA,
              NULL);
    definetodo(v10selconf, prop.valor, sizeof(prop.valor), V10CADENA, NULL);
}
static void leebd(char *instancia)
{
    int i,ret;
    if (v10selconf == NULL) initconf();
    strcpy(prop.instancia, instancia);
    for (i = 0; i < sizeof(dvar) / sizeof(defvars); i++) {
        defvars *d = dvar + i;
        strcpy(prop.propiedad, d->nombre);
        ret=ejefetchcursor(v10selconf);
		v10log(LOGDEBUG, "VARIABLE %s VALOR %s RET %d\n", d->nombre, prop.valor, ret);
        if (ret == 0) {
            if (strcmp(prop.valor, " ") == 0) continue;
            switch (d->tipo) {
                case V10INT:
                    if (*(int *)d->ptr != atoi(prop.valor)) {
                        v10log(LOGNORMAL, "Asignando %s a %s\n", prop.propiedad, prop.valor);
                        *(int *)d->ptr = atoi(prop.valor);
                    }
                    break;

                case V10CHAR:
                    if (strcmp(((char *)d->ptr), prop.valor) != 0) {
                        v10log(LOGNORMAL, "Asignando %s a %s\n", prop.propiedad, prop.valor);
                        strcpy((char *)d->ptr, prop.valor);
                    }
                    break;
            }

        }
    }
}

V10WWWIMPORT void v10configurahttp(char *fichero) 
{
	static int primeralectura=0;
	if (primeralectura==0) v10confhttp_pordefecto();
	primeralectura=1;
	leebd(fichero);
	if (*v10httpconf.v10serverhtml==0) strcpy(v10httpconf.v10serverhtml,v10httpconf.v10servidor);
	if (*v10httpconf.v10serverimg==0) strcpy(v10httpconf.v10serverimg,v10httpconf.v10servidor);
	if (*v10httpconf.v10serverxls==0) strcpy(v10httpconf.v10serverxls,v10httpconf.v10servidor);
	if (*v10httpconf.v10serverpdf==0) strcpy(v10httpconf.v10serverpdf,v10httpconf.v10servidor);  	
}


