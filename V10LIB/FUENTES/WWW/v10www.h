#ifndef __LINUX__
#ifdef _V10WWWDLL
  #define V10WWWIMPORT __declspec(dllexport)
#else
  #define V10WWWIMPORT __declspec( dllimport)
#endif
#endif

#define V10MAXTECLAS	100
#define V10WWWCONTROL	"ctrl"
#define V10WWWSHIFT		"shift"
#define V10WWWALT		"alt"

// patrones de la plantilla a sustituir
#define PATRONDATOS			"<!--V10FRMDATA-->"	
#define PATRONBOTONES		"<!--V10BOTONES-->"
#define PATRONBOTONERADEF   "<!--V10BOTONERADEF-->"
#define PATRONTEXTOMENSAJE	"<!--V10TEXTOMENSAJE-->"
#define PATRONIDSESION      "<!--IDSESION-->"
#define PATRONTITULO		"<!--V10MENUTITULO-->"
#define PATRONOPCIONES		"<!--V10MENUDATA-->"
#define INCLUDEDATA			"<!--V10INCLUDEDATA-->"
#define ENDINCLUDEDATA		"<!--V10ENDINCLUDEDATA-->"
#define INCLUDEBOTONES		"<!--V10INCLUDEBOTONES-->"
#define ENDINCLUDEBOTONES	"<!--V10ENDINCLUDEBOTONES-->"
#define INCLUDEBOTONES		"<!--V10INCLUDEBOTONES-->"
#define ENDINCLUDEBOTONES	"<!--V10ENDINCLUDEBOTONES-->"
#define PATRONMENSAJE		"<!--V10MENSAJE-->"
#define PATRONCOMBOX		"<!--V10COMBOX-->"
#define PATRONJAVASCRIPTONLOAD      "<!--ONLOAD-->"	
#define PATRONJAVASCRIPTONUNLOAD      "<!--ONUNLOAD-->"	
#define PATRONJAVASCRIPTONSCRIPTS   "<!--SCRIPTS-->"
#define PATRONJAVASCRIPTONLINE      "<!--ONLINE-->"
#define PATRONAJAX                  "<!--AJAX-->"
#define PATRONINCLUDEHTML	"<!--V10INCLUDEHTML-->"
#define PATRONINCLUDECSS	"<!--V10INCLUDECSS-->"
#define PATRONCALENDARIO    "<!--V10CALENDARIO-->"
#define PATRONHELP			"<!--V10HELP-->"
#define PATRONTECLADOVIRTUAL "<!--V10TECLADOVIRTUAL-->"
#define PATRONIMGTECLADOVIRTUAL "<!--V10IMGTECLADOVIRTUAL-->"
#define PATRONSIDEBAR           "<!--V10SIDEBAR-->"
#define PATRONUSER           "<!--V10USER-->"
#define PATRONINFOUSERTITULO     "<!--NOMBREREAL-->"

// plantilla de frm y menus por defecto
#define PLANTILLAFRM	  "plantilla.frm.html"
#define PLANTILLABLOQUE	  "plantilla.pan.html"
#define PLANTILLAMENU	   "plantilla.menu.html"

#define MAXCADENAHTML	MAXCADENA*10

// determina que tipo de plantilla HTML se est� generando
#define SINPLANTILLA		0
#define ENPLANTILLAFRM		1
#define ENPLANTILLAPAN		2
#define SUSTITUYEPLANTILLA	3

#include "v10sockssl.h"
#include "v10wwwmisc.h"
#include "v10wwwzip.h"
#include "v10http.h"
#include "v10html.h"

extern char ficheroconf[MAXPATH];
void v10contenidoayuda(int comando,v10sockssls *v10server,char *fichero);
void capturatopicayuda(char *fichero);
void v10indiceayuda(int comando,v10sockssls *v10server,char *fichero);

void v10finconexiones(void);
void v10trataservidores(char *param);
void v10atiendeconexiones(char *param);

void sidebarForm(void);
void sidebarMenu(void);


void httpenviarespuesta(int comando,char *fichero,int tipofichero,v10sockssls *v10server,char *datos,int lon,int comprimir,int conexabierta,char *accesoAJAX);



