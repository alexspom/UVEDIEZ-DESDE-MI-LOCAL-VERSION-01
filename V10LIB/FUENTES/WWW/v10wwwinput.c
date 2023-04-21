#include "v10wwwform.h"

void v10tooltip2html(bloques *b,fcampos *c,char *tooltiphtml) 
{	
	char destino[MAXCADENA]="";
	*tooltiphtml=0;
	if (!c->tooltip || strlen(c->tooltip)==0) return;
	if (c->funtooltip) {
		FORM(b)->cinput=c;
        c->funtooltip->fun(b,c->funtooltip);
		if (c->funtooltip->msg) strcpy(destino,c->funtooltip->msg);
	} else {
	  strcpy(destino,c->tooltip);
	}
	sustituyevariablessc(b,destino,tooltiphtml);
	v10ansitohtml(v10wwwoem2ansi(tooltiphtml));
}

static void v10modificadoresinput(char *ptrout,int nbloque,int fila,int col,bloques *b,fcampos *c, int noenter) 
{
	if (c->v->formato&FORMATOUPPER) strcat(ptrout,"text-transform:uppercase;");
	else if (c->v->formato&FORMATOLOWER) strcat(ptrout,"text-transform:lowercase;");	
	if (b==v10damebloqueactual() && b->vi.act==c->v) strcat(ptrout,"background-color:yellow;");
	if (*c->includecss) strcpy(ptrout+strlen(ptrout),c->includecss);
	sprintf(ptrout+strlen(ptrout),"\" maxlength=%d ",c->v->lvar);
	if (c->v->autoenter) strcat(ptrout,"autoenter=1 "); 
	if (c->v->lpan==1) strcat(ptrout,"modoinsert=1 ");   
	if (noenter) strcat(ptrout,"nent=1 " );
	// si no es el campo actual o modo modal 
	if (noenter || (c->combox.activo && c->combox.readonly)) strcat(ptrout," READONLY ");
	//else if (ventanamodal)  strcat(ptrout," DISABLED ");
	sprintf(ptrout+strlen(ptrout),"onblur=\"fonblur(\'bl%df%dc%d\')\"",nbloque,fila,col);
	// si es un campo de COMBOX poner myselect=\"%s\"",idcombox
}

void dametipohtmlcampo(fcampos *c,char *tipo)
{
	switch (c->tipo) {
		case V10CADENA:strcpy(tipo,"alfa");
			           break;
		case V10BYTE:
        case V10INT:
        case V10UINT:
        case V10LONG:
        case V10ULONG:
        case V10DOUBLE:strcpy(tipo,"num");
			           break;
		case V10FECHA:strcpy(tipo,"date");
			           break;
		default:strcpy(tipo,"alfa");
	}
}

static void v10llinput2html(char *ptrout,int nbloque,int fila,int col,bloques *b,fcampos *c,int noenter,int incluyevalores) 
{
	long ancho,top,left,multilin;
	char valor[MAXCADENA]="",tooltiphtml[MAXCADENA]="",miclase[MAXPATH]="",sepvalue,miestilocss[MAXPATH]="";
	int campocolor=0;
	char tipo[30]="alfa";
    int x,y;
    formtabs *ftab;
	dametipohtmlcampo(c,tipo);
	v10tooltip2html(b,c,tooltiphtml);
	ancho=v10x2pxsm(c->v->lpan==1?2:c->v->lpan,damepxcol(b));
    damepostab(b,c->v->posx,c->v->posy,&x,&y,&ftab);
	if (c->v->lpan==1 && c->combox.activo) ancho=v10x2pxsm(3,damepxcol(b));
	//top=v10y2pxsm(y,damepxfila(b));
	top=v10y2pxsm(c->v->posy,damepxfila(b));
	left=v10x2pxsm(c->v->posx,damepxcol(b))-2;
	if (c->vipx.posx) left+=c->vipx.posx;
	if (c->vipx.posy) top+=c->vipx.posy;
	if (c->vipx.lonx) ancho+=c->vipx.lonx;
	*miestilocss=0;	
	if (*c->estilocss) strcpy(miestilocss,c->estilocss);		
	if (noenter==0) {
		if (c->combox.activo) {
			int leftimg;
			strcat(miclase,"ipt");
			leftimg=(left+ancho)-10;
			if (!strcmp(cssalign(c),"right")) leftimg+=10;			
			if (!strcmp(c->combox.opc[0],"COLOR")) {
				char sucolor[MAXCADENA]="";
                int decimales;
				campocolor=1;
                decimales = dameindcampo(b, c, "DECIMALES");
				v10tipo2a(c->v->dato,c->tipo,c->lvar,c->format,decimales,sucolor,1);
				leftimg=(left+ancho)-15;
				sprintf(ptrout+strlen(ptrout),"<input id=\"colorbl%df%dc%d\" value=\"\" type=\"button\" tipo=\"%s\" icolor=\"bl%df%dc%d\" style=\"z-index:9999;background-color:%s;position:absolute;top:%dpx;left:%dpx;height:%dpx;width:%dpx\"/>\n",
					nbloque, fila, col, tipo, nbloque, fila, col, trim(sucolor), top, leftimg, damepxfila(b), 14);
			} else {
				sprintf(ptrout+strlen(ptrout),"<img iselect=\"bl%df%dc%d__\"class=\"%s\"style=\"position:absolute;top:%dpx;left:%dpx;\"src=\"../img/desplegable.png\"",nbloque,fila,col,
					(*miestilocss)?miestilocss:((b->regpag>1)?"v10comboximgmul":"v10comboximg"),top+1,leftimg);
				if (c->combox.activo && b->vi.act==c->v && b==v10damebloqueactual() && muestracombox) strcat(ptrout,"comboxshowed=1");
				strcat(ptrout,"/>\n");
			}
		}
		else strcat(miclase,"ipt");		
	} else strcat(miclase,"iptnet");	
	if (strchr(v10ora2campo(incluyevalores,nbloque,b,c,fila,c->nombre,1,valor),'\"')) sepvalue='\'';
	else sepvalue='\"';
	multilin=(c->regpag<=1)?0:1;
	if (multilin==0) sprintf(ptrout+strlen(ptrout),"<input id=\"bl%df%dc%d\"value=%c%s%c tipo=\"%s\"",nbloque,fila,col,sepvalue,valor,sepvalue,tipo);
	else // campo multilínea 	
        sprintf(ptrout + strlen(ptrout), "<TEXTAREA id=\"bl%df%dc%d\" tipo=\"%s\"", nbloque, fila, col, tipo);
    if (c->feventos.ondbclick) sprintf(ptrout + strlen(ptrout), " ondblclick=\"fclick('ondblclick')\"");
    if (c->feventos.onrightclick) sprintf(ptrout + strlen(ptrout), " oncontextmenu=\"fclick('oncontextmenu')\"");
    if (c->feventos.onmouseover) sprintf(ptrout + strlen(ptrout), " onmouseenter=\"fclick('onmouseenter')\"");
    if (c->feventos.onmouseout) sprintf(ptrout + strlen(ptrout), " onmouseout=\"fclick('onmouseout')\"");
	if (campocolor) sprintf(ptrout+strlen(ptrout)," miicolor=\"colorbl%df%dc%d\" ",nbloque,fila,col);
	if (multilin==0) {
		// hoja de estilo		
		strcat(ptrout,"class=\"");
		if (noenter)	strcat(ptrout,"iptnet");
			else strcat(ptrout,"ipt");	
		if (*miestilocss) sprintf(ptrout+strlen(ptrout), " %s",miestilocss);	
		if (c->v->color>0) sprintf(ptrout+strlen(ptrout)," color%d",c->v->color);
		strcat(ptrout,"\"");	
		sprintf(ptrout+strlen(ptrout),"type=\"%s\"title=\"%s\"style=\"top:%dpx;left:%dpx;width:%dpx;",
			c->v->password?"password":"text",tooltiphtml,top,left,ancho);
		if(!strcmp(cssalign(c),"right")) strcat(ptrout,"text-align:right;");
		v10modificadoresinput(ptrout+strlen(ptrout),nbloque,fila,col,b,c,noenter);
		if (c->combox.activo) strcat(ptrout,"iselect=\"1\" "); // tiene asociada una select
		strcat(ptrout,"/>\n");  
		if (noenter==0 && b==v10damebloqueactual() && c->combox.activo && b->vi.act==c->v) v10combox2html(ptrout+strlen(ptrout),nbloque,0,fila,col,top,left,b,c,incluyevalores);		
	} else {
		// hoja de estilo		
		strcat(ptrout,"class=\"");
		if (noenter)	strcat(ptrout,"txarnet");
			else strcat(ptrout,"txar");	
		if (*miestilocss) sprintf(ptrout+strlen(ptrout), " %s",miestilocss);	
		if (c->v->color>0) sprintf(ptrout+strlen(ptrout)," color%d",c->v->color);
		strcat(ptrout,"\"");	
		sprintf(ptrout+strlen(ptrout),"rows=%d cols=%d title=\"%s\"style=\"height:%dpx;top:%dpx;left:%dpx;width:%dpx;",
			c->regpag,(int)((ancho-v10htmlconf.pixelescol)/v10htmlconf.pixelescol),tooltiphtml,
			(c->regpag*v10htmlconf.pixelesfila),top,left,ancho);
		if(!strcmp(cssalign(c),"right")) strcat(ptrout,"text-align:right;");
		v10modificadoresinput(ptrout+strlen(ptrout),nbloque,fila,col,b,c,noenter);
		sprintf(ptrout+strlen(ptrout),">%s</TEXTAREA>",valor);
	}
}


void v10inputnoenter2html(char *ptrout,int nbloque,int fila,int col, bloques *b,fcampos *c,int incluyevalores) 
{
	v10llinput2html(ptrout,nbloque,fila,col,b,c,1,incluyevalores);
}


void v10input2html(char *ptrout,int nbloque,int fila,int col,bloques *b,fcampos *c,int incluyevalores) 
{
	v10llinput2html(ptrout,nbloque,fila,col,b,c,b->noenter?1:0,incluyevalores);	
}


void v10inputcelda2html(char *ptrout,int nbloque,int ancho,int fila,int col,bloques *b,fcampos *c,int readonly,int incluyevalores) 
{	
	char valor[MAXCADENA]="",tooltiphtml[MAXCADENA]="",sepvalue,miestilocss[MAXPATH]="",tipo[MAXPATH];
	v10tooltip2html(b,c,tooltiphtml);
	if (strchr(v10ora2campo(incluyevalores,nbloque,b,c,fila,c->nombre,1,valor),'\"')) sepvalue='\'';
	else sepvalue='\"';
	*miestilocss=0;	
	dametipohtmlcampo(c,tipo);
	strcat(miestilocss,"cipt");
	if (*c->estilocss) {
		strcat(miestilocss," ");	
		strcpy(miestilocss+strlen(miestilocss),c->estilocss);
	}
	if (c->v->color>0) sprintf(miestilocss+strlen(miestilocss)," color%d",c->v->color);
	/* &bl%d_%02d_%s& */
	sprintf(ptrout+strlen(ptrout),
		"<input id=\"bl%df%dc%d\"value=%c%s%cclass=\"%s\"type=\"%s\"title=\"%s\"tipo=\"%s\""
		"style=\"width:%dpx;",
		nbloque,fila,col,sepvalue,valor,sepvalue,
        miestilocss, c->v->password ? "password" : "text", tooltiphtml, tipo, (c->combox.activo) ? (ancho - 16) : (ancho - 4)); // ,c->nombre c->nombre,
	if (!strcmp(cssalign(c),"right")) strcat(ptrout,"text-align:right;");
	v10modificadoresinput(ptrout+strlen(ptrout),nbloque,fila,col,b,c,0);
	sprintf(ptrout+strlen(ptrout)," classorig=\"%s\"",miestilocss);
	if (c->combox.activo) {
		if (!strcmp(c->combox.opc[0],"COLOR")) sprintf(ptrout+strlen(ptrout)," miicolor=\"colorbl%df%dc%d\" ",nbloque,fila,col);	
		else strcat(ptrout,"iselect=\"1\" "); // tiene asociada una select
	}
	strcat(ptrout,"/>");		
}