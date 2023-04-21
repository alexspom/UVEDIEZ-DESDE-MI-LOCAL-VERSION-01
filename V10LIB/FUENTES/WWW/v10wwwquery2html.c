#include "v10wwwform.h"
static void sustituyebinds(v10cursors *c,char *query)
{
	char sql[MAXSQL];
	int nc;
	char *aux;
	char nombrebind[MAXPATH];
	char buffer[MAXCADENA];
	strcpy(sql,c->sql);
	for (nc=0;nc<c->nbind;nc++) {
		campooras *ca=c->bind+nc;
		sprintf(nombrebind,":%s",ca->nombre);
		while ((aux=strstr(sql,nombrebind))!=NULL) {
			  strerase(aux,0,strlen(nombrebind));
			  pasaoracampo2ascii(ca,buffer,1,1);
			  strins(aux,buffer);
		}
	}
    strcpy(query,sql);
}

int v10cad2query(bloques *b, char *cad, char *query) 
{
	fcursores *fcur;
	if (!b || (fcur=buscafcursor(b,cad))==NULL) {
        v10cursors *vdquery;
        vdquery=bindbloque(b,cad,"AJAX");
        if (vdquery) {
		   sustituyebinds(vdquery,query);
        } else strcpy(query,"");
        liberacursor(vdquery);
		return(0);
	}	
   strcpy(query,cad);
   return(0);
}


void v10query2html(char *sql, char *html) 
{
  v10cursors *vdquery;
  int vdret;
  char error[MAXERRORORACLE]="";  	
  vdquery=abrecursordebug(sql,256);
  if (!vdquery) {
	sprintf(html,"<b>Error Abriendo cursor Oracle:<h1>%s</h1></b>",sql);
	return;
  }
  vdret=definetodo(vdquery,html,MAXCADENA,V10CADENA,	NULL);
  if (vdret) {
	getlastdberror(error);
	sprintf(html,"<b>Error Oracle: %d. %s en cursor<h1>%s</h1></b>",vdret, error,sql);
    liberacursor(vdquery);
	return;
  }
  vdret=ejefetchcursor(vdquery);
  if (vdret) {
	getlastdberror(error);
	sprintf(html,"<b>Error Oracle: %d. %s en cursor<h1>%s</h1></b>",vdret, error,sql);
    liberacursor(vdquery);
	return;
  }	  
  liberacursor(vdquery);
}

int v10cursor2html(char *sql,char *campos,char *html) 
{
    bloques *b;
    int ret;
    int nc;
    long *valor;
    b = v10damebloqueactual(); 
    if (b==NULL) return(-1);
    if (buscafcursor(b,sql)==NULL) {
        v10log(LOGNORMAL,"No existe cursor %s en bloque %s\n",sql,b->fichero);
        strcpy(html,"");
        return(-1);
    }
    ret=ejecutafcursor(b,sql);
    if (ret) return(ret);
    nc = damecampo(b, "V10EVAJAX");
    valor = (long *)direccampo(b, nc); 
    if (*valor < 0) return (*valor);
    if (campos) {
        int i,j,ncol;
        char nombre[MAXNOMBREV10];
        for (i=0;i<numpieces(campos,",");i++) {
            int nbloque=v10damenumbloque(b);
            char valor[MAXCADENA]="";
            int nc,fila;
            piece(campos,nombre,",",i+1);
            nc=damecampo(b,nombre);
            if (nc<0) continue;
            ncol=0;
            if (b->regpag>0) fila=b->s->clin+1-b->s->plin;
            else fila=1;
            for (j=0;j<=nc;j++) {
		        fcampos *c=b->c+j;
		        if (!c->v || c->v->invisible) continue; 
		        ncol++;
	         }	
            v10ora2campo(1,nbloque,b,b->c+nc,1,nombre,1,valor);
            sprintf(html+strlen(html),"window.document.getElementById('bl%df%dc%d').value='%s';",nbloque,fila,ncol,valor);
            v10log(LOGNORMAL,"Mandando a WEB resultado de AJAX campo %s valor %s\n",nombre,valor);
        }
    }
    if (nc) {
        if (*valor>0) sprintf(html + strlen(html), "v10lib.valorobjactivo();v10lib.gestenvioeevento(v10lib.objactivo,'onkeyup',%d);", *valor);

    }
    return(*valor);
}