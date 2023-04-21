/****
* VDTRACKINGAGENCIA.C
*                                                    
* Prop�sito: Procesos y algoritmos en C propios del tratamiento de asignaci�n de tracking de agencia 
*                                            
* Autor  : RFD
* Fecha  : 25-09-2008                                                        
******
*  Modificaciones:
****/

#include "vdpedidos.h"

static int liberamovspec(vdpedidocabs *pec,char *forzarpickinv, int statusini, int statusfin, int *haypickinv) {
	int pickinvret=0;
	vdpedidos pedido;
	int ret;

	// mira si es picking inverso, para hacer un tratamiento especial
	ret=pickinvfinvolumetria(pec,forzarpickinv,haypickinv,&pickinvret);
	if (ret) return(ret);
	if (*haypickinv) {
		pec->status=STPECSPRPICKINV;
		return(pickinvret);
	}

	ret=PEDIDOprocliberamovpedido(pec->coddemanda,statusini,statusfin,0,&pedido);
    if (pedido.ret) {
		v10logcomen(LOGERROR,pec->comenpec,"vdagenciasintracking - ERROR Liberando movimientos para pedido. %s \n",PEClog(pec));
        return(pedido.ret);
     }
	return(0);
}


// Avanza pedidos y libera movimientos para agencias que no apliquen tracking de agencia
// PARAM1: (ptr) puntero al pedido
// PARAM2: Estado en el que dejar el pedido si todo ha ido correctamente
VDEXPORT int vdagenciasintracking(void *ptr,char *param) {
	
	int ret,haypickinv=0,nparam;
	char fuerzasprpickinv[2]="N";
    vdstatuss staped,stamovini,stamovfin;
    vdpedidocabs *pec=ptr;

	nparam=numpieces(param,"#");
    if (nparam < 3) {
        v10log(LOGERROR,"vdagenciasintracking: N�mero de par�metros incorrecto, recibe %d necesita 3\n", nparam);
		return(0);
	}
    if (ret=damestabreviada("vdagenciasintracking",param, 1, "#", pec, "PEC", &staped, STPECPREPARANDO)) return(ret);
	if (ret=damestabreviada("vdagenciasintracking",param, 2, "#", "VDMOVIM", "MOV", &stamovini,STMOVPDTEPEDIDO)) return(ret);
	if (ret=damestabreviada("vdagenciasintracking",param, 3, "#", "VDMOVIM", "MOV", &stamovfin,STMOVPDTEFLUJO)) return(ret);
	if (nparam>3) {
		memset(	fuerzasprpickinv,0,2);
		piece(param,fuerzasprpickinv,"#",4);
	}	
	
	// mira si es picking inverso, para hacer un tratamiento especial
	ret=liberamovspec(pec, fuerzasprpickinv, stamovini.status, stamovfin.status, &haypickinv);
	if (haypickinv) return(ret);
	if (ret) return(ret);

	pec->status=staped.status;
    v10log(LOGNORMAL,"vdagenciasintracking: Liberados movimientos de pedido %s %d %s %d\n", pec->coddiv,pec->anoped,pec->codped,pec->seqped);
	return(ret);
}

