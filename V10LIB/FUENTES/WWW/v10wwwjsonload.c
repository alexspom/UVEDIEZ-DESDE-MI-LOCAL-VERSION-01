#include "v10wwwform.h"
extern double timeoutact;

static int hayhijodesplegado(forms *f,bloques *b,int inibloque) {
	int i,ret;
	bloques *bh;
	for (i=inibloque;i<f->nbloques;i++) {
		bh=f->b[i];
		if (bh->padre==b && bh->wtemplegado==0) return(1);
		ret=hayhijodesplegado(f,bh,i+1);
		if (ret) return(ret);
	}
	return(0);
}

static int haybloquehijos(bloques *b) 
{
	if (b->fpreregistro) {
		// es distinto a PRESEHIJO, por lo que si tiene que actualizarse
		if (strcmp(b->fpreregistro->nombre,"PRESEHIJO")) return (1);
		else { // tiene como preregistro el presentar bloques hijos
			   // busca si tiene algún bloque hijo desplegado
			if (hayhijodesplegado(b->form,b,b->form->act+1)) return(1);
		}
	}
	if (b->fpostregistro) {
		// es distinto a PRESEHIJO, por lo que si tiene que actualizarse
		if (strcmp(b->fpostregistro->nombre,"PRESEHIJO")) return (1);
		else { // tiene como preregistro el presentar bloques hijos
			   // busca si tiene algún bloque hijo desplegado
			if (hayhijodesplegado(b->form,b,b->form->act+1)) return(1);
		}
	}
	return(0);
}


void damefilasycolumnas(bloques *b) 
{
	int i=0,ncol=1;
	if (b->regpag==1)  {
		maxfilas=1;
		filaactiva=1;		
	} else  {
		maxfilas=(b->s->ulin - b->s->plin)+1;
		if (maxfilas<1) maxfilas=1;	
		filaactiva=(b->s->clin-b->s->plin)+1;
	}	
	for (i=0;i<b->ncamp;i++) {
		if (!b->c[i].v) continue; // oculto
		if (b->vi.act==b->c[i].v) colactiva=ncol;
		ncol++;
	}	
	maxcolumnas=ncol-1;
	if (b->regpag==1) sprintf(idanterior,"bl%df%dc%d",b->form->act,1,colactiva);
	else {
		if (entrablebloque(b) && !b->noinput)  sprintf(idanterior,"bl%df%dc%d",b->form->act,filaactiva,colactiva);
		else sprintf(idanterior,"tdbl%df%dc%d",b->form->act,filaactiva,colactiva);		
	}
}


void v10jsonload(forms *f,int timeout) 
{
	bloques *b=v10damebloqueactual();
    *v10datoshtml = 0;
	damefilasycolumnas(v10damebloqueactual());
	sprintf(v10datoshtml+strlen(v10datoshtml),"v10lib.ponfoco(%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%lf);\n",
	    	f->act,filaactiva,colactiva,b->regpag==1?1:0,(entrablebloque(b) && !b->noinput)?1:0,
		    maxfilas,maxcolumnas,/*(b->fpreregistro)?1:0,*/haybloquehijos(b),ventanamodal,(haymensajespost()>0)?1:0,
		    (b->ftimeout && timeout)?b->timeout:0,timeoutact);
	if (oradebug) strcat(v10datoshtml,"document.getElementById('imgdebug').style.visibility='visible';");
	wwwtratamensajespost(v10datoshtml);
	v10reemplazapatron(v10html,PATRONJAVASCRIPTONLOAD,v10datoshtml,1);
    if (b->nbajax) {
        sprintf(v10datoshtml, "ajaxsock.abort();");
        v10reemplazapatron(v10html, PATRONJAVASCRIPTONUNLOAD, v10datoshtml, 1);
    }
}