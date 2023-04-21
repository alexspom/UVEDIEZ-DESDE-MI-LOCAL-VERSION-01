// Modulo generado automaticamente a partir de VDRESERVAAUX.DEF
//#***
//# VDSTOCK.DEF - Generación automática del código c SOLOQUERY sobre la tabla VDMOVIM                                                    
//# 
//# Propósito: idem.
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 07-04-2008                                               
//#********************************************************************************
//# Modificaciones
//#***
//NOMBRE=RES;
//EXTRA=TAREACONTE,V10CADENA,32
//EXTRA=TAREAEMBA,V10CADENA,32
//EXTRA=TAREAUNIINV,V10CADENA,32
//EXTRA=TAREAPREPICK,V10CADENA,32
//EXTRA=TAREAUNI,V10CADENA,32
//EXTRA=UNIAGRUPAEMBA,V10CADENA,1
//EXTRA=UNIAGRUPAUNI,V10CADENA,1
//EXTRA=MONOFORMATO,V10CADENA,1;
//EXTRA=EMBALAJESCOMPLETOS,V10CADENA,1;
//EXTRA=SOLOPARCIALES,V10CADENA,1;
//EXTRA=REVISARCOMPLETO,V10CADENA,1;
//EXTRA=RESERVADO,V10DOUBLE 
//EXTRA=CANTIDAD,V10DOUBLE
//EXTRA=DIFERCONTE,V10DOUBLE
//EXTRA=DIFEREMBA,V10DOUBLE
//EXTRA=DIFERUNI,V10DOUBLE
//
//
//CURSOR=RESERVADODEML,SELECT VDDEM.RESERVADODEML(:VDDEMANDALIN.CODDEMANDA,:VDDEMANDALIN.TIPODEMANDA,:VDDEMANDALIN.LINDEMANDA,:VDDEMANDALIN.UNIAGRUPA) CANTIDAD FROM DUAL;
//
//PROCEDURE= RESERVAPEDIDODIF, BEGIN
//                              VDDEM.RESERVAPEDIDODIF(:VDDEMANDALIN.CODDEMANDA, :VDDEMANDALIN.TIPODEMANDA, :VDDEMANDALIN.LINDEMANDA,
//                                                     :CANTIDAD,:VDMOVIM.CODUBIORI,:TAREAUNI,:TAREAEMBA,:TAREACONTE,:VDMOVIM.CODCONCE,:VDMOVIM.STATUS, :VDCOMEN.COMENTARIO, :RESERVADO);
//                             END;@
//                             
//PROCEDURE= RESERVAPEDIDOSTD, BEGIN
//                              VDDEM.RESERVAPEDIDOSTD(:VDDEMANDALIN.CODDEMANDA, :VDDEMANDALIN.TIPODEMANDA, :VDDEMANDALIN.LINDEMANDA,
//                                                     :CANTIDAD,  :TAREACONTE, :TAREAEMBA,:TAREAUNIINV,:TAREAPREPICK,:TAREAUNI,:UNIAGRUPAEMBA,:UNIAGRUPAUNI,
//                                                     :MONOFORMATO, :REVISARCOMPLETO, :VDCOMEN.COMENTARIO, :RESERVADO);
//                             END;@
//							 
//PROCEDURE= RESERVAPEDIDOEXT, BEGIN
//                              VDDEM.RESERVAPEDIDOSTD(:VDDEMANDALIN.CODDEMANDA, :VDDEMANDALIN.TIPODEMANDA, :VDDEMANDALIN.LINDEMANDA,
//                                                     :CANTIDAD,  :TAREACONTE, :TAREAEMBA,:TAREAUNIINV,:TAREAPREPICK,:TAREAUNI,:UNIAGRUPAEMBA,:UNIAGRUPAUNI,
//                                                     :MONOFORMATO, :REVISARCOMPLETO, :VDCOMEN.COMENTARIO, :RESERVADO,:DIFERCONTE,:DIFEREMBA,:DIFERUNI);
//                             END;@
//
//PROCEDURE= RESERVASTD, BEGIN          
//                             VDDEM.RESERVASTD(:VDDEMANDALIN.CODDEMANDA, :VDDEMANDALIN.TIPODEMANDA, :VDDEMANDALIN.LINDEMANDA,
//                                              :CANTIDAD, :VDFLUJOPARAM.TAREA, :EMBALAJESCOMPLETOS, 
//                                              :SOLOPARCIALES, :VDUBICA.UNIAGRUPAE, :MONOFORMATO, :REVISARCOMPLETO, :VDCOMEN.COMENTARIO, :RESERVADO);                                
//                       END;@                         

#include "vd.h"\

#define SELRESERVADODEML "SELECT VDDEM.RESERVADODEML(:CODDEMANDA,:TIPODEMANDA,:LINDEMANDA,:UNIAGRUPA) CANTIDAD FROM DUAL"
static v10cursors *vdselreservadodeml;
#define SELRESERVAPEDIDODIF " BEGIN VDDEM.RESERVAPEDIDODIF(:CODDEMANDA, :TIPODEMANDA, :LINDEMANDA, :CANTIDAD,:CODUBIORI,:TAREAUNI,:TAREAEMBA,:TAREACONTE,:CODCONCE,:STATUS, :COMENTARIO, :RESERVADO); END;"
static v10cursors *vdselreservapedidodif;
#define SELRESERVAPEDIDOSTD " BEGIN VDDEM.RESERVAPEDIDOSTD(:CODDEMANDA, :TIPODEMANDA, :LINDEMANDA, :CANTIDAD,  :TAREACONTE, :TAREAEMBA,:TAREAUNIINV,:TAREAPREPICK,:TAREAUNI,:UNIAGRUPAEMBA,:UNIAGRUPAUNI, :MONOFORMATO, :REVISARCOMPLETO, :COMENTARIO, :RESERVADO); END;"
static v10cursors *vdselreservapedidostd;
#define SELRESERVAPEDIDOEXT " BEGIN VDDEM.RESERVAPEDIDOSTD(:CODDEMANDA, :TIPODEMANDA, :LINDEMANDA, :CANTIDAD,  :TAREACONTE, :TAREAEMBA,:TAREAUNIINV,:TAREAPREPICK,:TAREAUNI,:UNIAGRUPAEMBA,:UNIAGRUPAUNI, :MONOFORMATO, :REVISARCOMPLETO, :COMENTARIO, :RESERVADO,:DIFERCONTE,:DIFEREMBA,:DIFERUNI); END;"
static v10cursors *vdselreservapedidoext;
#define SELRESERVASTD " BEGIN           VDDEM.RESERVASTD(:CODDEMANDA, :TIPODEMANDA, :LINDEMANDA, :CANTIDAD, :TAREA, :EMBALAJESCOMPLETOS,  :SOLOPARCIALES, :UNIAGRUPAE, :MONOFORMATO, :REVISARCOMPLETO, :COMENTARIO, :RESERVADO);                                 END;"
static v10cursors *vdselreservastd;

static vdress svdres;

static diccols colvdres[]={ 
    {"TAREACONTE",V10CADENA,(size_t)&svdres.tareaconte,sizeof(svdres.tareaconte)},
    {"TAREAEMBA",V10CADENA,(size_t)&svdres.tareaemba,sizeof(svdres.tareaemba)},
    {"TAREAUNIINV",V10CADENA,(size_t)&svdres.tareauniinv,sizeof(svdres.tareauniinv)},
    {"TAREAPREPICK",V10CADENA,(size_t)&svdres.tareaprepick,sizeof(svdres.tareaprepick)},
    {"TAREAUNI",V10CADENA,(size_t)&svdres.tareauni,sizeof(svdres.tareauni)},
    {"UNIAGRUPAEMBA",V10CADENA,(size_t)&svdres.uniagrupaemba,sizeof(svdres.uniagrupaemba)},
    {"UNIAGRUPAUNI",V10CADENA,(size_t)&svdres.uniagrupauni,sizeof(svdres.uniagrupauni)},
    {"MONOFORMATO",V10CADENA,(size_t)&svdres.monoformato,sizeof(svdres.monoformato)},
    {"EMBALAJESCOMPLETOS",V10CADENA,(size_t)&svdres.embalajescompletos,sizeof(svdres.embalajescompletos)},
    {"SOLOPARCIALES",V10CADENA,(size_t)&svdres.soloparciales,sizeof(svdres.soloparciales)},
    {"REVISARCOMPLETO",V10CADENA,(size_t)&svdres.revisarcompleto,sizeof(svdres.revisarcompleto)},
    {"RESERVADO",V10DOUBLE,(size_t)&svdres.reservado,sizeof(svdres.reservado)},
    {"CANTIDAD",V10DOUBLE,(size_t)&svdres.cantidad,sizeof(svdres.cantidad)},
    {"DIFERCONTE",V10DOUBLE,(size_t)&svdres.diferconte,sizeof(svdres.diferconte)},
    {"DIFEREMBA",V10DOUBLE,(size_t)&svdres.diferemba,sizeof(svdres.diferemba)},
    {"DIFERUNI",V10DOUBLE,(size_t)&svdres.diferuni,sizeof(svdres.diferuni)},
    {"CODDEMANDA",V10CADENA,(size_t)&svdres.coddemanda,sizeof(svdres.coddemanda)},
    {"TIPODEMANDA",V10CADENA,(size_t)&svdres.tipodemanda,sizeof(svdres.tipodemanda)},
    {"LINDEMANDA",V10LONG,(size_t)&svdres.lindemanda,sizeof(svdres.lindemanda)},
    {"UNIAGRUPA",V10CADENA,(size_t)&svdres.uniagrupa,sizeof(svdres.uniagrupa)},
    {"CODUBIORI",V10CADENA,(size_t)&svdres.codubiori,sizeof(svdres.codubiori)},
    {"CODCONCE",V10CADENA,(size_t)&svdres.codconce,sizeof(svdres.codconce)},
    {"STATUS",V10LONG,(size_t)&svdres.status,sizeof(svdres.status)},
    {"COMENTARIO",V10CADENA,(size_t)&svdres.comentario,sizeof(svdres.comentario)},
    {"TAREA",V10CADENA,(size_t)&svdres.tarea,sizeof(svdres.tarea)},
    {"UNIAGRUPAE",V10CADENA,(size_t)&svdres.uniagrupae,sizeof(svdres.uniagrupae)}
    };

static diccionarios dvdres[]={
    {colvdres,26}
    };

diccionario dres={dvdres,1};

static char msgdebugres[LCADENABIG];

static int init=0;


static void fin_vd_RES(void)
{
    if(vdselreservadodeml){
        liberacursor(vdselreservadodeml);
        vdselreservadodeml=NULL;
    }
    if(vdselreservapedidodif){
        liberacursor(vdselreservapedidodif);
        vdselreservapedidodif=NULL;
    }
    if(vdselreservapedidostd){
        liberacursor(vdselreservapedidostd);
        vdselreservapedidostd=NULL;
    }
    if(vdselreservapedidoext){
        liberacursor(vdselreservapedidoext);
        vdselreservapedidoext=NULL;
    }
    if(vdselreservastd){
        liberacursor(vdselreservastd);
        vdselreservastd=NULL;
    }
}


static void init_selreservadodeml(void)
{
    int nc;

    for(nc=0;nc<dvdres[0].numcol;nc++) dvdres[0].c[nc].offset-=(size_t)&svdres;

    vdselreservadodeml=abrecursordebug(SELRESERVADODEML,256);
    definetodo(vdselreservadodeml,&svdres.cantidad,sizeof(svdres.cantidad),V10DOUBLE,
               NULL);
    bindtodo(vdselreservadodeml,"CODDEMANDA",svdres.coddemanda,sizeof(svdres.coddemanda),V10CADENA,
             "TIPODEMANDA",svdres.tipodemanda,sizeof(svdres.tipodemanda),V10CADENA,
             "LINDEMANDA",&svdres.lindemanda,sizeof(svdres.lindemanda),V10LONG,
             "UNIAGRUPA",svdres.uniagrupa,sizeof(svdres.uniagrupa),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_RES);
        init = 1;
    }
}

static void init_selreservapedidodif(void)
{
    int nc;

    for(nc=0;nc<dvdres[0].numcol;nc++) dvdres[0].c[nc].offset-=(size_t)&svdres;

    vdselreservapedidodif=abrecursordebug(SELRESERVAPEDIDODIF,256);
    definetodo(vdselreservapedidodif,NULL);
    bindtodo(vdselreservapedidodif,"CODDEMANDA",svdres.coddemanda,sizeof(svdres.coddemanda),V10CADENA,
             "TIPODEMANDA",svdres.tipodemanda,sizeof(svdres.tipodemanda),V10CADENA,
             "LINDEMANDA",&svdres.lindemanda,sizeof(svdres.lindemanda),V10LONG,
             "CANTIDAD",&svdres.cantidad,sizeof(svdres.cantidad),V10DOUBLE,
             "CODUBIORI",svdres.codubiori,sizeof(svdres.codubiori),V10CADENA,
             "TAREAUNI",svdres.tareauni,sizeof(svdres.tareauni),V10CADENA,
             "TAREAEMBA",svdres.tareaemba,sizeof(svdres.tareaemba),V10CADENA,
             "TAREACONTE",svdres.tareaconte,sizeof(svdres.tareaconte),V10CADENA,
             "CODCONCE",svdres.codconce,sizeof(svdres.codconce),V10CADENA,
             "STATUS",&svdres.status,sizeof(svdres.status),V10LONG,
             "COMENTARIO",svdres.comentario,sizeof(svdres.comentario),V10CADENA,
             "RESERVADO",&svdres.reservado,sizeof(svdres.reservado),V10DOUBLE,
             NULL);

    if (init == 0) {
        atexit(fin_vd_RES);
        init = 1;
    }
}

static void init_selreservapedidostd(void)
{
    int nc;

    for(nc=0;nc<dvdres[0].numcol;nc++) dvdres[0].c[nc].offset-=(size_t)&svdres;

    vdselreservapedidostd=abrecursordebug(SELRESERVAPEDIDOSTD,256);
    definetodo(vdselreservapedidostd,NULL);
    bindtodo(vdselreservapedidostd,"CODDEMANDA",svdres.coddemanda,sizeof(svdres.coddemanda),V10CADENA,
             "TIPODEMANDA",svdres.tipodemanda,sizeof(svdres.tipodemanda),V10CADENA,
             "LINDEMANDA",&svdres.lindemanda,sizeof(svdres.lindemanda),V10LONG,
             "CANTIDAD",&svdres.cantidad,sizeof(svdres.cantidad),V10DOUBLE,
             "TAREACONTE",svdres.tareaconte,sizeof(svdres.tareaconte),V10CADENA,
             "TAREAEMBA",svdres.tareaemba,sizeof(svdres.tareaemba),V10CADENA,
             "TAREAUNIINV",svdres.tareauniinv,sizeof(svdres.tareauniinv),V10CADENA,
             "TAREAPREPICK",svdres.tareaprepick,sizeof(svdres.tareaprepick),V10CADENA,
             "TAREAUNI",svdres.tareauni,sizeof(svdres.tareauni),V10CADENA,
             "UNIAGRUPAEMBA",svdres.uniagrupaemba,sizeof(svdres.uniagrupaemba),V10CADENA,
             "UNIAGRUPAUNI",svdres.uniagrupauni,sizeof(svdres.uniagrupauni),V10CADENA,
             "MONOFORMATO",svdres.monoformato,sizeof(svdres.monoformato),V10CADENA,
             "REVISARCOMPLETO",svdres.revisarcompleto,sizeof(svdres.revisarcompleto),V10CADENA,
             "COMENTARIO",svdres.comentario,sizeof(svdres.comentario),V10CADENA,
             "RESERVADO",&svdres.reservado,sizeof(svdres.reservado),V10DOUBLE,
             NULL);

    if (init == 0) {
        atexit(fin_vd_RES);
        init = 1;
    }
}

static void init_selreservapedidoext(void)
{
    int nc;

    for(nc=0;nc<dvdres[0].numcol;nc++) dvdres[0].c[nc].offset-=(size_t)&svdres;

    vdselreservapedidoext=abrecursordebug(SELRESERVAPEDIDOEXT,256);
    definetodo(vdselreservapedidoext,NULL);
    bindtodo(vdselreservapedidoext,"CODDEMANDA",svdres.coddemanda,sizeof(svdres.coddemanda),V10CADENA,
             "TIPODEMANDA",svdres.tipodemanda,sizeof(svdres.tipodemanda),V10CADENA,
             "LINDEMANDA",&svdres.lindemanda,sizeof(svdres.lindemanda),V10LONG,
             "CANTIDAD",&svdres.cantidad,sizeof(svdres.cantidad),V10DOUBLE,
             "TAREACONTE",svdres.tareaconte,sizeof(svdres.tareaconte),V10CADENA,
             "TAREAEMBA",svdres.tareaemba,sizeof(svdres.tareaemba),V10CADENA,
             "TAREAUNIINV",svdres.tareauniinv,sizeof(svdres.tareauniinv),V10CADENA,
             "TAREAPREPICK",svdres.tareaprepick,sizeof(svdres.tareaprepick),V10CADENA,
             "TAREAUNI",svdres.tareauni,sizeof(svdres.tareauni),V10CADENA,
             "UNIAGRUPAEMBA",svdres.uniagrupaemba,sizeof(svdres.uniagrupaemba),V10CADENA,
             "UNIAGRUPAUNI",svdres.uniagrupauni,sizeof(svdres.uniagrupauni),V10CADENA,
             "MONOFORMATO",svdres.monoformato,sizeof(svdres.monoformato),V10CADENA,
             "REVISARCOMPLETO",svdres.revisarcompleto,sizeof(svdres.revisarcompleto),V10CADENA,
             "COMENTARIO",svdres.comentario,sizeof(svdres.comentario),V10CADENA,
             "RESERVADO",&svdres.reservado,sizeof(svdres.reservado),V10DOUBLE,
             "DIFERCONTE",&svdres.diferconte,sizeof(svdres.diferconte),V10DOUBLE,
             "DIFEREMBA",&svdres.diferemba,sizeof(svdres.diferemba),V10DOUBLE,
             "DIFERUNI",&svdres.diferuni,sizeof(svdres.diferuni),V10DOUBLE,
             NULL);

    if (init == 0) {
        atexit(fin_vd_RES);
        init = 1;
    }
}

static void init_selreservastd(void)
{
    int nc;

    for(nc=0;nc<dvdres[0].numcol;nc++) dvdres[0].c[nc].offset-=(size_t)&svdres;

    vdselreservastd=abrecursordebug(SELRESERVASTD,256);
    definetodo(vdselreservastd,NULL);
    bindtodo(vdselreservastd,"CODDEMANDA",svdres.coddemanda,sizeof(svdres.coddemanda),V10CADENA,
             "TIPODEMANDA",svdres.tipodemanda,sizeof(svdres.tipodemanda),V10CADENA,
             "LINDEMANDA",&svdres.lindemanda,sizeof(svdres.lindemanda),V10LONG,
             "CANTIDAD",&svdres.cantidad,sizeof(svdres.cantidad),V10DOUBLE,
             "TAREA",svdres.tarea,sizeof(svdres.tarea),V10CADENA,
             "EMBALAJESCOMPLETOS",svdres.embalajescompletos,sizeof(svdres.embalajescompletos),V10CADENA,
             "SOLOPARCIALES",svdres.soloparciales,sizeof(svdres.soloparciales),V10CADENA,
             "UNIAGRUPAE",svdres.uniagrupae,sizeof(svdres.uniagrupae),V10CADENA,
             "MONOFORMATO",svdres.monoformato,sizeof(svdres.monoformato),V10CADENA,
             "REVISARCOMPLETO",svdres.revisarcompleto,sizeof(svdres.revisarcompleto),V10CADENA,
             "COMENTARIO",svdres.comentario,sizeof(svdres.comentario),V10CADENA,
             "RESERVADO",&svdres.reservado,sizeof(svdres.reservado),V10DOUBLE,
             NULL);

    if (init == 0) {
        atexit(fin_vd_RES);
        init = 1;
    }
}

diccionario *RESdamediccionario(void)
{
    return(&dres);
}

int RESbuscareservadodeml(char *coddemanda,char *tipodemanda,long lindemanda,char *uniagrupa,vdress *res)
{
    int vdret;
    if (vdselreservadodeml==NULL) init_selreservadodeml();
    memset(&svdres,0,sizeof(svdres));
    strcpy(svdres.coddemanda,coddemanda);
    strcpy(svdres.tipodemanda,tipodemanda);
    svdres.lindemanda=lindemanda;
    strcpy(svdres.uniagrupa,uniagrupa);
    vdret=ejefetchcursor(vdselreservadodeml);
    if(vdret) {
        v10log(LOGDEBUGAPI,"Ejefetch RESbuscareservadodeml vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *res=svdres;
    return(vdret);
}

int RESnextreservadodeml(vdress *res)
{
    int vdret;
    vdret=fetchcursor(vdselreservadodeml);
    if (!vdret) {
        *res=svdres;
        v10log(LOGDEBUGAPI,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselreservadodeml);
    return(VD_EERRORACLE);
}

int RESprocreservapedidodif(char *coddemanda,char *tipodemanda,long lindemanda,double cantidad,char *codubiori,char *tareauni,char *tareaemba,char *tareaconte,char *codconce,long status,char *comentario,double reservado,vdress *res)
{
    int vdret;
    if (vdselreservapedidodif==NULL) init_selreservapedidodif();
    memset(&svdres,0,sizeof(svdres));
    strcpy(svdres.coddemanda,coddemanda);
    strcpy(svdres.tipodemanda,tipodemanda);
    svdres.lindemanda=lindemanda;
    svdres.cantidad=cantidad;
    strcpy(svdres.codubiori,codubiori);
    strcpy(svdres.tareauni,tareauni);
    strcpy(svdres.tareaemba,tareaemba);
    strcpy(svdres.tareaconte,tareaconte);
    strcpy(svdres.codconce,codconce);
    svdres.status=status;
    strcpy(svdres.comentario,comentario);
    svdres.reservado=reservado;
    vdret=ejecutacursor(vdselreservapedidodif);
    if(vdret) {
        v10log(LOGDEBUGAPI,"Ejecuta RESprocreservapedidodif vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *res=svdres;
    return(vdret);
}

int RESprocreservapedidostd(char *coddemanda,char *tipodemanda,long lindemanda,double cantidad,char *tareaconte,char *tareaemba,char *tareauniinv,char *tareaprepick,char *tareauni,char *uniagrupaemba,char *uniagrupauni,char *monoformato,char *revisarcompleto,char *comentario,double reservado,vdress *res)
{
    int vdret;
    if (vdselreservapedidostd==NULL) init_selreservapedidostd();
    memset(&svdres,0,sizeof(svdres));
    strcpy(svdres.coddemanda,coddemanda);
    strcpy(svdres.tipodemanda,tipodemanda);
    svdres.lindemanda=lindemanda;
    svdres.cantidad=cantidad;
    strcpy(svdres.tareaconte,tareaconte);
    strcpy(svdres.tareaemba,tareaemba);
    strcpy(svdres.tareauniinv,tareauniinv);
    strcpy(svdres.tareaprepick,tareaprepick);
    strcpy(svdres.tareauni,tareauni);
    strcpy(svdres.uniagrupaemba,uniagrupaemba);
    strcpy(svdres.uniagrupauni,uniagrupauni);
    strcpy(svdres.monoformato,monoformato);
    strcpy(svdres.revisarcompleto,revisarcompleto);
    strcpy(svdres.comentario,comentario);
    svdres.reservado=reservado;
    vdret=ejecutacursor(vdselreservapedidostd);
    if(vdret) {
        v10log(LOGDEBUGAPI,"Ejecuta RESprocreservapedidostd vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *res=svdres;
    return(vdret);
}

int RESprocreservapedidoext(char *coddemanda,char *tipodemanda,long lindemanda,double cantidad,char *tareaconte,char *tareaemba,char *tareauniinv,char *tareaprepick,char *tareauni,char *uniagrupaemba,char *uniagrupauni,char *monoformato,char *revisarcompleto,char *comentario,double reservado,double diferconte,double diferemba,double diferuni,vdress *res)
{
    int vdret;
    if (vdselreservapedidoext==NULL) init_selreservapedidoext();
    memset(&svdres,0,sizeof(svdres));
    strcpy(svdres.coddemanda,coddemanda);
    strcpy(svdres.tipodemanda,tipodemanda);
    svdres.lindemanda=lindemanda;
    svdres.cantidad=cantidad;
    strcpy(svdres.tareaconte,tareaconte);
    strcpy(svdres.tareaemba,tareaemba);
    strcpy(svdres.tareauniinv,tareauniinv);
    strcpy(svdres.tareaprepick,tareaprepick);
    strcpy(svdres.tareauni,tareauni);
    strcpy(svdres.uniagrupaemba,uniagrupaemba);
    strcpy(svdres.uniagrupauni,uniagrupauni);
    strcpy(svdres.monoformato,monoformato);
    strcpy(svdres.revisarcompleto,revisarcompleto);
    strcpy(svdres.comentario,comentario);
    svdres.reservado=reservado;
    svdres.diferconte=diferconte;
    svdres.diferemba=diferemba;
    svdres.diferuni=diferuni;
    vdret=ejecutacursor(vdselreservapedidoext);
    if(vdret) {
        v10log(LOGDEBUGAPI,"Ejecuta RESprocreservapedidoext vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *res=svdres;
    return(vdret);
}

int RESprocreservastd(char *coddemanda,char *tipodemanda,long lindemanda,double cantidad,char *tarea,char *embalajescompletos,char *soloparciales,char *uniagrupae,char *monoformato,char *revisarcompleto,char *comentario,double reservado,vdress *res)
{
    int vdret;
    if (vdselreservastd==NULL) init_selreservastd();
    memset(&svdres,0,sizeof(svdres));
    strcpy(svdres.coddemanda,coddemanda);
    strcpy(svdres.tipodemanda,tipodemanda);
    svdres.lindemanda=lindemanda;
    svdres.cantidad=cantidad;
    strcpy(svdres.tarea,tarea);
    strcpy(svdres.embalajescompletos,embalajescompletos);
    strcpy(svdres.soloparciales,soloparciales);
    strcpy(svdres.uniagrupae,uniagrupae);
    strcpy(svdres.monoformato,monoformato);
    strcpy(svdres.revisarcompleto,revisarcompleto);
    strcpy(svdres.comentario,comentario);
    svdres.reservado=reservado;
    vdret=ejecutacursor(vdselreservastd);
    if(vdret) {
        v10log(LOGDEBUGAPI,"Ejecuta RESprocreservastd vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *res=svdres;
    return(vdret);
}

char * RESdebug(vdress *res)
{
    debugestruct(&dres,res,msgdebugres);
    return(msgdebugres);
}

