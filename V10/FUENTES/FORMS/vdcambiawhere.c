/*******************************************************************************
* Módulo : vdcambiawhere.c                                                     *
* Función: Modifica la where por defecto y permite almacenarlas                *
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
#define MAXOPCIONESWHERE    100

#define CSELALMA  "SELECT DISTINCT TITULOWHERE "\
                   " FROM VDWHERE "\
                   " WHERE DECODE(CODOPE,'VDUSER',VDUSER.GETUSER,CODOPE)=VDUSER.GETUSER  AND PANTALLA=:PANTALLA "\
                     " ORDER BY TITULOWHERE "
static v10cursors *vdselalma;                   
                              
#define CDELWHERE "DELETE VDWHERE "\
                    " WHERE CODOPE=VDUSER.GETUSER AND PANTALLA=:PANTALLA AND TITULOWHERE=:TITULOWHERE "
static v10cursors *vddelwhere;

#define CSELWHERE "SELECT PANTALLA,TITULOWHERE,TEXTOWHERE,TEXTOORDER,TEXTOHAVING "\
                    " FROM VDWHERE "\
                    " WHERE DECODE(CODOPE,'VDUSER',VDUSER.GETUSER,CODOPE)=VDUSER.GETUSER AND PANTALLA=:PANTALLA AND TITULOWHERE=:TITULOWHERE "\
                    " ORDER BY DECODE(CODOPE,'VDUSER',1,0) "
static v10cursors *vdselwhere;
#define CINSWHERE "INSERT INTO VDWHERE (CODOPE,PANTALLA,TITULOWHERE,TEXTOWHERE,TEXTOORDER,TEXTOHAVING,CODOPEMODIF) "\
                      " VALUES (VDUSER.GETUSER,:PANTALLA,:TITULOWHERE,:TEXTOWHERE,:TEXTOORDER,:TEXTOHAVING,VDUSER.GETUSER) "
static v10cursors *vdinswhere;
#define CUPDAWHERE "UPDATE VDWHERE SET TEXTOWHERE=:TEXTOWHERE, "\
                                      " TEXTOORDER=:TEXTOORDER, "\
                                      " TEXTOHAVING=:TEXTOHAVING "\
                      " WHERE CODOPE=VDUSER.GETUSER AND PANTALLA=:PANTALLA AND TITULOWHERE=:TITULOWHERE "
static v10cursors *vdupdawhere;

static char pwhere[][80]={"                                                                               ",
                              " Where:  _1024M______________________________________________________________  ",
                              " Order:  _1024M______________________________________________________________  ",
                              " Having: _1024M______________________________________________________________  ",
                              " Titulo: _60M__________________________________________                        "};
static v10dialogs viwhere;
typedef struct {
         char textowhere[LTEXTOWHERE],
              textoorder[LTEXTOORDER],
              textohaving[LTEXTOHAVING],
              titulowhere[LTITULOWHERE],
              pantalla[LPANTALLA];
       } vdwheres;
static vdwheres wh;
static char titulowhere[LTITULOWHERE];

static void finvdcambiawhere(void)
{
  liberadialog(&viwhere);
  liberacursor(vdselwhere);
  liberacursor(vdselalma);
}

static void initvdcambiawhere(void)
{
  initdian(&viwhere,pwhere,"Modificar parametros de consulta",2,1,"PIDEWHERE");
  asignadialog(&viwhere,wh.textowhere,wh.textoorder,wh.textohaving,wh.titulowhere,NULL);
  vdselwhere=abrecursor(CSELWHERE);
  definetodo(vdselwhere,wh.pantalla,sizeof(wh.pantalla),V10CADENA,
                         wh.titulowhere,sizeof(wh.titulowhere),V10CADENA,
                         wh.textowhere,sizeof(wh.textowhere),V10CADENA,
                         wh.textoorder,sizeof(wh.textoorder),V10CADENA,
                         wh.textohaving,sizeof(wh.textohaving),V10CADENA,
                         NULL);
  bindtodo(vdselwhere,"PANTALLA",wh.pantalla,sizeof(wh.pantalla),V10CADENA,
                      "TITULOWHERE",wh.titulowhere,sizeof(wh.titulowhere),V10CADENA,
                      NULL);
  vdselalma=abrecursor(CSELALMA);
  definetodo(vdselalma,titulowhere,sizeof(titulowhere),V10CADENA,
                        NULL);
  bindtodo(vdselalma,"PANTALLA",wh.pantalla,sizeof(wh.pantalla),V10CADENA,
                     NULL);
  atexit(finvdcambiawhere);
}

static int fpideconsulta(bloques *b,ftrigers *ft)
{
  int ret;
  if (vdselwhere==NULL) initvdcambiawhere();
  if (!es_blanco(wh.titulowhere)) {
	  if (strcmp(wh.pantalla,b->fichero)!=0 || strcmp(wh.textowhere,b->where?b->where:"") || strcmp(wh.textoorder,b->orderby?b->orderby:"") || strcmp(wh.textohaving,b->having?b->having:"")) {
        strcpy(wh.titulowhere,"");
	 }
  }
  if (b->where) {
     strcpy(wh.textowhere,b->where);
   } else *wh.textowhere=0;
  if (b->orderby) {
     strcpy(wh.textoorder,b->orderby);
   } else *wh.textoorder=0;
  if (b->having) {
     strcpy(wh.textohaving,b->having);
   } else *wh.textohaving=0;
  
  if (!editwhere) ret=dialoginputpres(&viwhere);
  else ret=editwhere(wh.textowhere,wh.textoorder,wh.textohaving,wh.titulowhere);

  if (ret!=esc) {
     if (b->where)   free(b->where);
     if (b->orderby)   free(b->orderby);
     if (b->having)   free(b->having);
     if (!es_blanco(wh.textowhere)) b->where=strdup(wh.textowhere);
        else         b->where=NULL;
     if (!es_blanco(wh.textoorder)) b->orderby=strdup(wh.textoorder);
        else         b->orderby=NULL;
     if (!es_blanco(wh.textohaving)) b->having=strdup(wh.textohaving);
        else         b->having=NULL;
   }
  if (ret==F(4) && !es_blanco(wh.titulowhere)) {
     relogin();
     vdinswhere=abrecursor(CINSWHERE);
     bindtodo(vdinswhere,"PANTALLA",wh.pantalla,sizeof(wh.pantalla),V10CADENA,
                         "TITULOWHERE",wh.titulowhere,sizeof(wh.titulowhere),V10CADENA,
                         "TEXTOWHERE",wh.textowhere,sizeof(wh.textowhere),V10CADENA,
                         "TEXTOORDER",wh.textoorder,sizeof(wh.textoorder),V10CADENA,
                         "TEXTOHAVING",wh.textohaving,sizeof(wh.textohaving),V10CADENA,
                         NULL);
     vdupdawhere=abrecursor(CUPDAWHERE);
     bindtodo(vdupdawhere,"PANTALLA",wh.pantalla,sizeof(wh.pantalla),V10CADENA,
                          "TITULOWHERE",wh.titulowhere,sizeof(wh.titulowhere),V10CADENA,
                          "TEXTOWHERE",wh.textowhere,sizeof(wh.textowhere),V10CADENA,
                          "TEXTOORDER",wh.textoorder,sizeof(wh.textoorder),V10CADENA,
                          "TEXTOHAVING",wh.textohaving,sizeof(wh.textohaving),V10CADENA,
                         NULL);
     strcpy(wh.pantalla,b->fichero);
     ejecutacursor(vdupdawhere);
     if (procesadascursor(vdupdawhere)==0) ejecutacursor(vdinswhere);
     liberacursor(vdinswhere);
     liberacursor(vdupdawhere);
     commit();
     logout();
   }
  return(0);
}

static int fmuestramenu(bloques *b,ftrigers *ft)
{
  int numop=1,i,ret;
  char **opciones;
  opciones=calloc(MAXOPCIONESWHERE,sizeof(char *));
  if (vdselwhere==NULL) initvdcambiawhere();
  strcpy(wh.pantalla,b->fichero);
  do {
     opciones[0]=strdup("CONSULTAS ALMACENADAS");
     ejecutacursor(vdselalma);
     while (fetchcursor(vdselalma)==0) {
           opciones[numop]=strdup(titulowhere);
           numop++;
      }
     opciones[numop]=NULL;
	 ret=selwhere(opciones,0,5,5);
     /*ret=menu(opciones,0,5,5);*/
     if (ult_pul==dele) {
        relogin();
        vddelwhere=abrecursor(CDELWHERE);
        bindtodo(vddelwhere,"PANTALLA",wh.pantalla,sizeof(wh.pantalla),V10CADENA,
                            "TITULOWHERE",wh.titulowhere,sizeof(wh.titulowhere),V10CADENA,
                            NULL);
        strcpy(wh.titulowhere,opciones[ret+1]);
        ejecutacursor(vddelwhere);
        commit();
        liberacursor(vddelwhere);
        logout();
      }
     if (ult_pul==cr) {
        strcpy(wh.titulowhere,opciones[ret+1]);
        ret=ejefetchcursor(vdselwhere);
        if (ret==0) {
           if (b->where && *wh.textowhere!='+')   free(b->where);
           if (b->orderby && *wh.textoorder!='+')   free(b->orderby);
           if (b->having && *wh.textohaving!='+')   free(b->having);
           if (!es_blanco(wh.textowhere)) {
               if (*wh.textowhere=='+') {
                   *wh.textowhere=' ';
                   if (b->where) {
                       strins(wh.textowhere," AND ");
                       strins(wh.textowhere,b->where);
                       free(b->where);
                   }
               }
               b->where=strdup(wh.textowhere);
           } else         b->where=NULL;
           if (!es_blanco(wh.textoorder)) {
               if (*wh.textoorder=='+') {
                   *wh.textoorder=' ';
                   if (b->orderby) {
                       strins(wh.textoorder,",");
                       strins(wh.textoorder,b->orderby);
                       free(b->orderby);
                   }
               }
               b->orderby=strdup(wh.textoorder);
           } else {
               if (*wh.textohaving=='+') {
                   *wh.textohaving=' ';
                   if (b->having) {
                       strins(wh.textohaving,",");
                       strins(wh.textohaving,b->having);
                       free(b->having);
                   }
               }
               b->orderby=NULL;
           }
           if (!es_blanco(wh.textohaving)) {
               b->having=strdup(wh.textohaving);
           } else {
               b->having=NULL;
           }
         }
      }
     for (i=0;i<numop;i++) {
         free(opciones[i]);
      }
     numop=1;
   } while (ult_pul==dele);
  free(opciones);
  return(0);
}

void initvdwhere(void)
{
	declaratriger("FPIDEWHERE",fpideconsulta,NULL);
	declaratriger("FMENUWHERE",fmuestramenu,NULL);
	defineteclaformdef(C_F(4),"FPIDEWHERE");
	defineteclaformdef(C_F(5),"FMENUWHERE");
}
