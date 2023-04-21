/*******************************************************************************
* M�dulo : vdpassword.c                                                        *
* Funci�n: Gestion de passwords codificados generacion de clave publica/privada*
*                                                                              *
*                                                                              *
* Autor	 : Eduardo Alsina                                                      *
* Revisado por:                                                                *
* Fecha  : 01-10-2007                                                          *
********************************************************************************
* Hist�rico de cambios
* ====================
*******************************************************************************/
#include "vdform.h"



static char *errores[]={"SIN ERROR",
                       "Password demasiado corto",
					   "Password demasiado simple",
					   "Password incorrecto",
					   "Usuario bloqueado",
					   "Password caducado",
					   "Password a punto de caducar",
					   "Error en parametros",
					   "Password repetido demasiado pronto"};



#define CSELPASSCAD "SELECT HPASSWORD FROM VDUSUARIO$HIST WHERE CODOPE=:CODOPE AND HISTDATEDESDE>SYSDATE-:MINREP AND HPASSWORD=:HPASSWORD"
static v10cursors *vdselpass;

#define CDAMEDATOSUSU "BEGIN VDUSER.DAMEDATOSPASS(:CODOPE,:MINDIG,:MINMAY,:MINMIN,:MINLON,:MINREP,:AVISAR,:CADUCA); END;"
static v10cursors *vddamedatosusu;

#define CSELUSU "SELECT HPASSWORD,BLOQUEOPE,FECCADUC "\
	             " FROM VDUSUARIO "\
				 " WHERE CODOPE=:CODOPE"
static v10cursors *vdselusu;

typedef struct {
	      char codope[LCODOPE];
		  char hpassword[LHPASSWORD];
		  char bloqueope[LBLOQUEOPE];
		  v10dates feccaduc;
	      long mindig,
			   minmay,
			   minmin,
			   minlon,
			   minrep,
			   avisar,
			   caduca;
} datousus;
static datousus usu;

static void finpassword(void)
{
	liberacursor(vdselpass);
	liberacursor(vddamedatosusu);
	liberacursor(vdselusu);
}

static void initpassword(void)
{
	vdselpass=abrecursor(CSELPASSCAD);
	definetodo(vdselpass,usu.hpassword,sizeof(usu.hpassword),V10CADENA,
		                     NULL);
	bindtodo(vdselpass,"CODOPE",usu.codope,sizeof(usu.codope),V10CADENA,
		                   "HPASSWORD",usu.hpassword,sizeof(usu.hpassword),V10CADENA,
						   "MINREP",&usu.minrep,sizeof(usu.minrep),V10LONG,
						   NULL);
	vddamedatosusu=abrecursor(CDAMEDATOSUSU);
	bindtodo(vddamedatosusu,"CODOPE",usu.codope,sizeof(usu.codope),V10CADENA,
		                    "MINDIG",&usu.mindig,sizeof(usu.mindig),V10LONG,
		                    "MINMAY",&usu.minmay,sizeof(usu.minmay),V10LONG,
		                    "MINMIN",&usu.minmin,sizeof(usu.minmin),V10LONG,
		                    "MINLON",&usu.minlon,sizeof(usu.minlon),V10LONG,
		                    "MINREP",&usu.minrep,sizeof(usu.minrep),V10LONG,
		                    "AVISAR",&usu.avisar,sizeof(usu.avisar),V10LONG,
		                    "CADUCA",&usu.caduca,sizeof(usu.caduca),V10LONG,
							NULL);
	vdselusu=abrecursor(CSELUSU);
	definetodo(vdselusu,usu.hpassword,sizeof(usu.hpassword),V10CADENA,
		                usu.bloqueope,sizeof(usu.bloqueope),V10CADENA,
                        &usu.feccaduc,sizeof(usu.feccaduc),V10FECHA,
						NULL);
	bindtodo(vdselusu,"CODOPE",usu.codope,sizeof(usu.codope),V10CADENA,
		              NULL);
		                     
	atexit(finpassword);
}

int damehashope(char *codope,char *pass,char *hpass)
{
	char destino[MAXCADENA];
	strcpy(destino,codope);
	strcat(destino,pass);
	return(damehash(destino,hpass));
}

static int llverificanuevopass(char *codope,char *pass,int numdig,int nummay,int nummin,int lontotal,int minfecrep)
{
   int ndig=0,nmay=0,nmin=0,i,ret;
   char hpass[MAXHASH];
   if (vdselpass==NULL) initpassword();
   if (strlen(pass)<(unsigned)lontotal) {
      v10log(LOGERROR,"Password del usuario %s demasiado corto\n",codope);
	  return(ERRPASSCORTO);
   }
   for (i=0;i<(int)strlen(pass);i++) {
	   if (isdigit(pass[i])) ndig++;
	   if (pass[i]>='A' && pass[i]<='Z') nmay++;
	   if (pass[i]>='a' && pass[i]<='z') nmin++;
   }
   if (ndig<numdig || nmay<nummay || nmin<nummin) {
	   v10log(LOGERROR,"Password del usuario %s demasiado simple\n",codope);
	   return(ERRPASSSIMPLE);
   }
   ret=damehashope(codope,pass,hpass);
   if (ret) return(ret);
   strcpy(usu.codope,codope);
   strcpy(usu.hpassword,hpass);
   usu.minrep=minfecrep;
   ret=ejefetchcursor(vdselpass);
   if (ret==0) return(ERRPASSREPETIDO);
   return(0);	  
}


int verificanuevopass(char *codope,char *pass,char **error)
{
	int ret;
	strcpy(usu.codope,codope);
	ejecutacursor(vddamedatosusu);
	ret=llverificanuevopass(codope,pass,usu.mindig,usu.minmay,usu.minmin,usu.minlon,usu.minrep);
	if (ret && error) {
		*error=errores[ret];
	}
	return(ret);
}


int verificapass(char *codope,char *pass,char **error)
{
	char hpass[MAXHASH];
	int ret=0;
	if (vdselusu==NULL) initpassword();
	ret=damehashope(codope,pass,hpass);
	if (ret) return(ret);
	strcpy(usu.codope,codope);
	ret=ejefetchcursor(vdselusu);
    if (ret) {
        *error="USUARIO NO EXISTE";
        return(ret);
    }
	if (usu.feccaduc-usu.avisar<=damedate()) ret=ERRPASSAVISO;
	if (usu.feccaduc<=damedate()) ret=ERRPASSCADUCADO;
	if (*usu.bloqueope=='S') ret=ERRPASSBLOQUEAD;
	if (strcmp(hpass,usu.hpassword)) ret=ERRPASSINCORREC;
	if (ret && error) {
		*error=errores[ret];
	}
	return(ret);	
}

int creafirma(char *codope,char *password,char *priv,char *pub,char **error)
{
   int ret;
   HCRYPTKEY sesion;
   ret=verificapass(codope,password,error);
   if (ret) return(ret);
   sesion=dameclave(password);
   ret=genfirma(sesion,priv,pub);
   if (ret && error) *error=errores[ret];
   return(ret);
}

