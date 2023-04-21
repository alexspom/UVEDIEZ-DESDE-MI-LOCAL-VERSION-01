#include "vdexec.h"

typedef struct {
	          char proceso[LPROCESO];
	          char nombrealg[LNOMBREALG];
	          v10cursors *cur;
	        } cachealgs;
	        
#define MAXCACHEALGS 1000
static cachealgs ca[MAXCACHEALGS];
static int numcache;

static v10cursors *damecursorcache(vdalgoritmoss *alg,int *nuevo)
{
    int i;
    char sql[MAXSQL];
    for (i=0;i<numcache;i++) {
        if (strcmp(ca[i].proceso,alg->proceso)==0 && strcmp(ca[i].nombrealg,alg->nombrealg)==0) {
            piece(alg->paramalg,sql,"#",1); 
            if (ca[i].cur && strcmp(ca[i].cur->sql,sql)==0) {
                *nuevo=0;
                return(ca[i].cur);
            } else {
                if (ca[i].cur) liberacursor(ca[i].cur);
                ca[i].cur=parsecursornombre(sql,alg->nombrealg);
                *nuevo=1;
            }
            return(ca[i].cur);
        }
    }
    ca[numcache].cur=parsecursornombre(sql,alg->nombrealg);
    strcpy(ca[numcache].proceso,alg->proceso);
    strcpy(ca[numcache].nombrealg,alg->nombrealg);
    *nuevo=1;
    numcache++;
    return(ca[numcache-1].cur);
}
