#include  "v10wwwform.h"

void v10calendario2html(char *ptrout,int nbloque,int multireg,int fila, int ncol,int sutop,int suleft, bloques *b,fcampos *c) 
{
	char textocal[MAXCADENA]="";
	int top,left,leftb,topb,anchob,largob;
	v10damedimensionesbloque(b, &leftb, &topb, &anchob, &largob);	
	if (multireg) {
		top=topb+sutop+24+(fila*14);
		left=leftb+suleft+v10x2pxsm(c->v->posx,damepxcol(b));  	
	} else {
		left=suleft+leftb;
		top=sutop+topb+36;
	}	
	sprintf(textocal+strlen(textocal),"<script>window.document.getElementById('calenderTable').style.top='%dpx'; "\
		                                      "window.document.getElementById('calenderTable').style.left='%dpx'; "\
	                                          "parent.frames[0].showCalender('bl%df%dc%d'); "\
											  "function fonkeyupmsj(mievento,tecla) {if (tecla!=27) v10lib.desonkeyefectos(mievento);} </script>",top,left,nbloque,fila,ncol);
	v10wwwmensajecalendario(textocal);
}