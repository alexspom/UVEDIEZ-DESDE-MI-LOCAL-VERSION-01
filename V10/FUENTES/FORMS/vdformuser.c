/*******************************************************************************
* Módulo : vdformuser.c                                                        *
* Función: Tratamiento del usuario de las pantallas de v10                     *
*                                                                              *
*                                                                              *
* Autor	 : Eduardo Alsina                                                      *
* Revisado por:                                                                *
* Fecha  : 01-10-2007                                                          *
********************************************************************************
* Histórico de cambios
* ====================
*******************************************************************************/
#include "vdform.h"


vdusuarios vduser;

#define CSELUSER "SELECT MENUASOCIADO,IDIOMA, NIVEL "\
                   " FROM VDUSUARIO "\
                   " WHERE CODOPE=:CODOPE AND HPASSWORD=:HPASSWORD"
static v10cursors *vdseluser;

#define CSETUSER "BEGIN VDUSER.SETUSER(:CODOPE);VDUSER.SETIDIOMA(:IDIOMA);END;"
static v10cursors *vdsetuser;


static void finvdformuser(void)
{
	liberacursor(vdseluser);
	liberacursor(vdsetuser);	
}

static void initvdformuser(void)
{
	vdseluser=abrecursor(CSELUSER);
	definetodo(vdseluser,vduser.menuasociado,sizeof(vduser.menuasociado),V10CADENA,
                         vduser.idioma,sizeof(vduser.idioma),V10CADENA,
                         &vduser.nivel,sizeof(vduser.nivel),V10LONG,        // (2)
					     NULL);
	bindtodo(vdseluser,"CODOPE",vduser.codope,sizeof(vduser.codope),V10CADENA,
		               "HPASSWORD",vduser.hpassword,sizeof(vduser.hpassword),V10CADENA,
					   NULL);
	atexit(finvdformuser);
}

void ponwindowtext(void)
{
  char nombre[MAXCADENA];
  char usuario[MAXCADENA];
  strcpy(usuario,ORAUSR);
  if (!es_blanco(ORADB)) {
     strcat(usuario,"@");
     strcat(usuario,ORADB);
  }
  sprintf(nombre,v10translate("%s      B.D.:%s        USUARIO: %s PID: %d"),TITULOVENTANA,usuario,vduser.codope,getpid());
  SetWindowText(hwnddefecto,nombre);
}

void ponuserdb(void)
{
	vdsetuser=abrecursordebug(CSETUSER,0);
	bindtodo(vdsetuser,"CODOPE",vduser.codope,sizeof(vduser.codope),V10CADENA,
		                "IDIOMA",vduser.idioma,sizeof(vduser.idioma),V10CADENA,
						NULL);
	ejecutacursor(vdsetuser);
    strcpy(idiomav10,vduser.idioma);
    protegidoform=vduser.nivel;
    liberacursor(vdsetuser);
    vdsetuser=NULL;
}

void formdameusuario(char *donde)
{
    strcpy(donde, vduser.codope);
}


int verificausr(char *usr,char *pwd)
{
	int ret;
	char antmenu[LMENUASOCIADO];
	char hpass[MAXHASH],mipass[LCODOPE+LMIPASSWORD];
	strcpy(vduser.codope,usr);
	sprintf(mipass,"%s%s",usr,pwd);
	ret=damehash(mipass,hpass);
	if (ret) return(ret);
	strcpy(vduser.hpassword,hpass);
	strcpy(antmenu,vduser.menuasociado);
	if (vdseluser==NULL) initvdformuser();
	ret=ejefetchcursor(vdseluser);
    if (ret==0) ponuserdb();
	if (!es_blanco(antmenu)) strcpy(vduser.menuasociado,antmenu);
	return(ret);
}

int pideusuario(void)
{
	protegidoform=-1;
	cargaform("VDUSER","");
    dameusuario = formdameusuario;
	ponuserdb();
	trigerconecta=ponuserdb;
	if (v10versionweb) {
		
		/*strcpy(def.codind,vduser.codope);
		func_default();*/
	}
	return(protegidoform);
}
int fverificanuevopass(bloques *b,ftrigers *ft)
{
	char codope[LCODOPE],pass[MAXHASH],*hpass,*error;
	int ret;
	dameparametro(b,ft,0,V10CADENA,codope);
	dameparametro(b,ft,1,V10CADENA,pass);
	ret=verificanuevopass(codope,pass,&error);
	if (ret==0) {;
	   hpass=direcncampo(b,ft->param[2]);
	   ret=damehashope(codope,pass,hpass);
	}
	if (ret) {
		if (damecampo(b,ft->param[3])!=-1) {
			strcpy(direcncampo(b,ft->param[3]),error);
		}
		ret=-1;
	}
	return(ret);
}

static int fverificapass(bloques *b,ftrigers *ft)
{
	char codope[LCODOPE],pass[MAXHASH],*error;
	int ret;
	dameparametro(b,ft,0,V10CADENA,codope);
	dameparametro(b,ft,1,V10CADENA,pass);
	ret=verificapass(codope,pass,&error);
	if (ft->nparam>3) if (atoi(ft->param[3])==1 && ret==ERRPASSCADUCADO) ret=0;
	if (ft->nparam>3) if (atoi(ft->param[3])==1 && ret==ERRPASSAVISO) ret=0;
	if (ret==ERRPASSAVISO) {
		mensajefcm(10,"Su password esta a punto de caducar");
		ret=0;
	}
	if (ret) {
		if (damecampo(b,ft->param[2])!=-1) {
			strcpy(direcncampo(b,ft->param[2]),error);
		}
	}
	return(ret);
}

static int frecodificafirma(bloques *b,ftrigers *ft)
{
	char oldpwd[LMIPASSWORD],newpwd[LMIPASSWORD];
	char *cpriv;
	int ret;
	if (ft->nparam!=3) {
		mensajefcm(10,"Formato incorrecto en FRECODIFICAFIRMA(OLDPWD,NEWPWD,CPRIV)");
		return(ERRPARAM);
	}
	dameparametro(b,ft,0,V10CADENA,oldpwd);
	dameparametro(b,ft,1,V10CADENA,newpwd);
	if (damecampo(b,ft->param[2])!=-1) {
		cpriv=direcncampo(b,ft->param[2]);
		if (es_blanco(cpriv)) return(0);
		ret=recodificafirma(oldpwd,newpwd,cpriv);
		return(ret);
	}
	return(ERRPARAM);
}

static int fcreafirma(bloques *b,ftrigers *ft)
{
	char codope[LCODOPE],pwd[LMIPASSWORD];
	char *priv,*pub,*error;
	int ret;
	if (ft->nparam!=5) {
		mensajefcm(10,"Formato incorrecto en FGENFIRMA(CODOPE,PWD,PRIV,PUB,MENSAJE)");
		return(ERRPARAM);
	}
	dameparametro(b,ft,0,V10CADENA,codope);
	dameparametro(b,ft,1,V10CADENA,pwd);
    if (damecampo(b,ft->param[2])==-1 || damecampo(b,ft->param[3])==-1) {
		return(ERRPARAM);
	}
	priv=direcncampo(b,ft->param[2]);
	pub=direcncampo(b,ft->param[3]);
	ret=creafirma(codope,pwd,priv,pub,&error);
	if (ret) {
		if (damecampo(b,ft->param[4])!=-1) {
			strcpy(direcncampo(b,ft->param[4]),error);
		}
	}
	return(ret);
}

static int fponnivel(bloques *b,ftrigers *f)
{
  strcpy(vduser.codope,direcncampo(b,"CODOPE"));
  strcpy(vduser.menuasociado,direcncampo(b,"MENUASOCIADO"));
  strcpy(vduser.idioma,direcncampo(b,"IDIOMA"));
  if (damecampo(b,"NIVEL")!=-1) vduser.nivel=*(long *)direcncampo(b,"NIVEL");
  //ponidiomamenu();
  ponuserdb();
  ponwindowtext();
  return(0);
}

int fexpulsausuario(bloques *b,ftrigers *ft)
{
	mensajefcm(10,"DEMASIADOS ERRORES EN LOGIN");
	exit(1);
	return(0);
}


void inittriguser(void)
{
	declaratriger("FEXPULSAUSUARIO",fexpulsausuario,NULL);
	declaratriger("FPONNIVEL",fponnivel,NULL);
	declaratriger("FVERIFICANUEVOPASS",fverificanuevopass,NULL);
	declaratriger("FVERIFICAPASS",fverificapass,NULL);
	declaratriger("FRECODIFICAFIRMA",frecodificafirma,NULL);
	declaratriger("FCREAFIRMA",fcreafirma,NULL);
    declaramenutriger("REINICIAFORM",reiniciaform,NULL);
}


