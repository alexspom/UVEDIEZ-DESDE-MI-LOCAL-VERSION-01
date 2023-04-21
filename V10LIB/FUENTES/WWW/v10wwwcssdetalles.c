#include "v10wwwform.h"


char *cssalign(fcampos *c) {
	switch (c->tipo) {
	case V10INT:
	case V10SHORT:
	case V10LONG:
	case V10UINT:
	case V10USHORT:
	case V10ULONG:
	case V10FLOAT:
	case V10DOUBLE:
		//if (strlen(valor)==0) strcat(valor,"0");
		return("right");
	case V10FECHA:
	case V10HORA:				
	case V10CHAR:
	case V10BYTE:
	case V10CADENA:
		return("left");
	}
	return("left");
}

/*
void wwwsincero(fcampos *c,char *valor) {
	switch (c->tipo) {
	case V10INT:
	case V10SHORT:
	case V10LONG:
	case V10UINT:
	case V10USHORT:
	case V10ULONG:
	case V10FLOAT:
	case V10DOUBLE:
		if (strlen(valor)==0 && c->b->vi.act!=c->v) strcat(valor,"0");
		return;
	}
}
*/
