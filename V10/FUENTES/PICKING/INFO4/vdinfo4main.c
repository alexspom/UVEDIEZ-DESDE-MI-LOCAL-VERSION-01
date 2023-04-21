#include "vdinfopicking.h"
//#include "infopc.h"
//#include "vd.h"

static int sidinfopick;

VDEXPORT void vdinfoinit(int idinfopick)
{
    vdinfohards iha;
    sidinfopick=idinfopick;
    IHAselidinfopick(idinfopick,&iha);
    initinfopick(iha.tciclo,iha.tenvtrama,iha.timeouttrama,iha.timeoutwho,iha.limitelinea,iha.dirip1,iha.dirip2,iha.dirip3,iha.dirip4,iha.dirip5,NULL);
    tipoidentdisp=TIPOIDNUMDISP;
}

