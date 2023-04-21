#include "v10wwwform.h"

void v10checkbox2html(char *ptrout,int nbloque,int multireg,int fila, int ncol, bloques *b,fcampos *c,int incluyevalores)
{
 char valor[MAXCADENA]="",tooltiphtml[MAXCADENA]="";
 int top,left;
 v10ora2campo(incluyevalores,nbloque,b,c,fila,c->nombre, 1,valor);
 top=v10y2pxsm(c->v->posy,damepxfila(b));
 left=v10x2pxsm(c->v->posx,damepxcol(b))-2;
 if (c->vipx.posx) left+=c->vipx.posx;
 if (c->vipx.posy) top+=c->vipx.posy;
 v10tooltip2html(b,c,tooltiphtml);
 sprintf(ptrout+strlen(ptrout),"<input type=\"text\" READONLY id=\"bl%df%dc%d\" class=\"%s\" iffalse=\"%s\" iftrue=\"%s\" chkbox=\"si\" value=\"%s\"  title=\"%s\" ",
	 nbloque,fila,ncol,"v10chk",c->checkbox->valor_false,c->checkbox->valor_true,	
	 !strcmp(valor,c->checkbox->valor_true)?"X":"",tooltiphtml);
 if (b->regpag==1) sprintf(ptrout+strlen(ptrout),"style=\"top:%dpx;left:%dpx;\"",top+2,left+1);
 //else strcat(ptrout, "style=\"position:relative;top:-3px;left:-1px\""); ?? para que se ha definido algo en negativo..
 else strcat(ptrout,"style=\"position:relative;\"");
 strcat(ptrout," onclick=\"v10lib.fchkboxclick()\"/>");
}