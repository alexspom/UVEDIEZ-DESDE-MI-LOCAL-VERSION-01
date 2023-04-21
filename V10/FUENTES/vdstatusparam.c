/****
* VDSTATUSPARAM.C
*                                                    
* Propósito: Recupera de los parámetros el valor del estado pasado en una posición indicada                                                    
*                                                                              
*                                                                              
* Autor  : FGS e ICC                                                           
* Fecha  : 5-3-2008                                                         
******
*  Modificaciones:
****/

#include "vd.h"

#define CSELABREVIADA "SELECT STATUS,TIPOSTATUS,DABSTATUS FROM VDSTATUS "
static v10cursors *v10selabreviada;
#define MAXSTATUS 2000
typedef struct {
              int status;
              char tipostatus[LTIPOSTATUS];
              char dabstatus[LDABSTATUS];
} mistatus;

static mistatus mst[MAXSTATUS];
static int numstatus;

static void leestatus(void)
{
    mistatus mist;
    v10selabreviada=abrecursor(CSELABREVIADA);
    definetodo(v10selabreviada,&mist.status,sizeof(mist.status),V10LONG,
                               mist.tipostatus,sizeof(mist.tipostatus),V10CADENA,
                               mist.dabstatus,sizeof(mist.dabstatus),V10CADENA,                      
                               NULL);
    ejecutacursor(v10selabreviada);
    while (fetchcursor(v10selabreviada)==0) {
        mst[numstatus]=mist;
        numstatus++;
    }
}

int dameabreviada(char *tipostatus,char *dabstatus)
{
    int i;
    if (numstatus==0) leestatus();
    for (i=0;i<numstatus;i++) {
        if (strcmp(mst[i].tipostatus,tipostatus)==0 && strcmp(mst[i].dabstatus,dabstatus)==0) return mst[i].status;
    }
    return 0;
}


// asigna a 'st' el valor numérico del parámetro en la posición 'pos' de 'param' separado por 'sep'
// PARAM1: (algoritmo) informa del algoritmo desde donde se le llama
// PARAM2: (param) informa de la lista de parámetros del algoritmo
// PARAM3: (pos) informa de la posición del parámetro a tratar
// PARAM4: (sep) separador utilizado dentro de la cadena
// PARAM5: (objeto) informa del objeto tratándose en el algoritmo
// PARAM6: (tipost) informa del tipo de status
// PARAM7: (st) estructura vdstatuss donde recoger el valor numérico del status
// PARAM8: (valordefecto) informa el valor por defecto en caso de que el parámetro no esté informado

VDEXPORT int damestabreviada(char *algoritmo,char *param, int pos, char *sep, void *obj, char *tipost, vdstatuss *st, int valordefecto) { 
   // int ret;  
    if (0>=piece(param,st->dabstatus,sep,pos)) {
        if (valordefecto==0) {
            v10log(LOGERROR,"%s: Debe informar estado de tipo %s en parametro %d\n", algoritmo, tipost, pos); 
            return(VD_ESTNOEXISTE);
        }
        st->status = valordefecto; 
        return(0);
    } 
   /* if (ret=STAselabreviada(tipost,st->dabstatus,st)) {
        if (!strcmp(tipost,"MOV") && obj) v10log(LOGERROR,"%s: estado %s,%s no existe para movto %s\n", algoritmo, tipost, st->dabstatus, MOVlog((vdmovims *)obj));
        else v10log(LOGERROR,"%s: estado %s,%s no existe\n", algoritmo, tipost, st->dabstatus);  
        return(VD_ESTNOEXISTE);
    } */
    strcpy(st->tipostatus,tipost);
    st->status=dameabreviada(st->tipostatus,st->dabstatus);
    if (st->status==0) {
        if (!strcmp(tipost,"MOV") && obj) v10log(LOGERROR,"%s: estado %s,%s no existe para movto %s\n", algoritmo, tipost, st->dabstatus, MOVlog((vdmovims *)obj));
         else v10log(LOGERROR,"%s: estado %s,%s no existe\n", algoritmo, tipost, st->dabstatus); 
        return(VD_ESTNOEXISTE);
    }
    return(0);
}
