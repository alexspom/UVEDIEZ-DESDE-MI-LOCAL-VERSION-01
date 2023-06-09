/*******************************************************************************
* M�dulo : VDLOG.C                                                             *
* Funci�n: Transforma log PLSQL en log C                                       *
*                                                                              *
* Autor  : Eduardo Alsina                                                      *
* Revisado por:                                                                *
* Fecha  : 01-10-2007                                                          *
********************************************************************************
* Hist�rico de cambios
* ====================
*******************************************************************************/
#include "vd.h"


#define CDAMELOG "BEGIN :MENSAJE:=VDLOG.DAMELOG;END;"
#define CGETLOG "SELECT COLUMN_VALUE FROM TABLE(VDLOG.TABLELOG())"
#define CINITLOG "BEGIN VDLOG.NIVEL(:NIVEL); END;"
#define CGETNIVELLOG "SELECT VDLOG.DAMENIVEL NIVEL FROM DUAL"


static v10cursors *vdgetlog;
static v10cursors *vdgetlogant;
static v10cursors *vdinitlog;
static v10cursors *vdgetnivellog;

static char mensaje[MAXCADENA];

static int sinlogoracle=0;

int quitalogoracle(int quita)
{
	int ret=sinlogoracle;
	sinlogoracle=quita;
	return(ret);
}
   
void vdlogoracle(void)
{
    void *antlog=logoracle;
	if (maxnivellog<0 || sinlogoracle) return;
    logoracle=NULL;
    if (vdgetlog==NULL) {
       vdgetlog=abrecursordebug(CDAMELOG,0);
       bindtodo(vdgetlog,"MENSAJE",mensaje,sizeof(mensaje),V10CADENA,NULL);
       preparaarrayfetch(vdgetlog, 100);
	}
    while (ejecutacursor(vdgetlog)==0) {
       if (es_blanco(mensaje)) break;       
       v10logchf(0,0,NULL,NULL,0,"%s\n",mensaje);
    }
    logoracle=antlog;
}

VDEXPORT int damenivel(void) 
{    
    int nivel=-1;   
    if (vdgetnivellog==NULL) vdgetnivellog=abrecursordebug(CGETNIVELLOG,0);    
    definetodo(vdgetnivellog,&nivel,sizeof(nivel),V10INT,NULL);    
    if (ejefetchcursor(vdgetnivellog)) v10log(LOGERROR,"%s","damenivel: Error en cursor vdgetnivellog\n");
    return(nivel);  
}

VDEXPORT int ponnivel(int nivel) 
{    
	int ret=0;
    if (vdinitlog==NULL) vdinitlog=abrecursordebug(CINITLOG,DEPURAVDNOLOG);
    bindtodo(vdinitlog,"NIVEL",&nivel,sizeof(int),V10INT,NULL);
    ret=ejecutacursor(vdinitlog);
    if (ret) v10log(LOGERROR,"initlogoracle: No se puede poner LOG ORACLE a valor %d\n",nivel);
	return(ret);
}

VDEXPORT void logoracle2cadena(char *cadena) 
{
    int ret,inicio=0;
    void *antlog=logoracle;
	if (maxnivellog<0 || sinlogoracle) return;
    logoracle=NULL;
	if (vdgetlogant==NULL) {
		vdgetlogant=abrecursordebug(CGETLOG,0);
		definetodo(vdgetlogant,mensaje,sizeof(mensaje),V10CADENA,NULL);    
	}
    
	*cadena=0;
    ret=ejefetchcursor(vdgetlogant);    
    while (ret==0) {       
       if (inicio==0) {
           strcat(cadena,"PLSQL:\n");
           inicio=1;
       }
       if (strlen(cadena) > MAXCADENA - 1000-strlen(mensaje)) {
           sprintf(cadena + strlen(cadena), "\nCadena demasiado larga\n");
           break;
       }
       sprintf(cadena+strlen(cadena),"%s\n",mensaje+22);
       ret=fetchcursor(vdgetlogant);
    }
    logoracle=antlog;
}

VDEXPORT void initlogoracle(void)
{
    int ret;

    logoracle=vdlogoracle;
    if (vdinitlog==NULL) vdinitlog=abrecursordebug(CINITLOG,DEPURAVDNOLOG);
    bindtodo(vdinitlog,"NIVEL",&maxnivellog,sizeof(int),V10INT,NULL);
    ret=ejecutacursor(vdinitlog);
    if (ret) v10log(LOGERROR,"initlogoracle: No se puede iniciar LOG ORACLE a nivel %d\n",maxnivellog);

}



