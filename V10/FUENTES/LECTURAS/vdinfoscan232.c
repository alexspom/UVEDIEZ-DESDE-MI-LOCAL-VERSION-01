#include "vd.h"

static vdinfolecturass ilt; 
static int sidinfolectura=0;

VDEXPORT int vdinithardlectura(int idinfolectura) {
	int ret;
	sidinfolectura=idinfolectura;
	ret=ILTselvdinfolecturas(idinfolectura,&ilt);
	return initpuerto232(ilt.puerto232,ilt.velocidad,NOPARITY,8,ONESTOPBIT);
}


VDEXPORT int vddamecaracter(void) {
	if (STDhaycar232(ilt.puerto232)) {
		return STDdamecar232(ilt.puerto232);
	} else return (0);
}

