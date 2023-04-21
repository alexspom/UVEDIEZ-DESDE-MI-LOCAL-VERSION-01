#include "v10wwwform.h"

typedef struct {
	char teclas[MAXPATH];
	char texto[MAXPATH];
	int ctrl;
	int tecla;
} mionlinemsjs;

mionlinemsjs ionline[10]={
{"{Ctrl-F4}","Muestra campos ",1,115},
{"{Ctrl-F5}","Copiar path form",1,116},
{"{Ctrl-F6}","Copiar form",1,117},
{"{Ctrl-F7}","Copiar path bloque",1,118},
{"{Ctrl-F8}","Copiar bloque",1,119},
{"{Ctrl-F10}","Editar bloque",1,121},
{"{Ctrl-F11}","Editar form",1,122},
{"{Ctrl-F12}","Edita todo",1,123},
{"{F4}","Propiedades por defecto",0,115},
{"{ESC}","Salir",0,27}};

void v10wwwmuestracampos(bloques *b)
{ 
	char mimensaje[MAXCADENAHTML]="",titulo[MAXPATH]="";
	char destino[MAXCADENA];
    int i,modificado=0,antansi=v10usaansi;
	fcampos *c;
    sprintf(titulo,"Campos del bloque %s",b->nombre);    
	sprintf(mimensaje,"Bloque %s Modificado %d Antiguo %d<table onclick=\"fonclickmsj()\" id=\"tbcampos\" rules=\"all\"  border=\"0\" cellpadding=\"2\" CELLSPACING=\"0\" class=\"v10tablacampos\">",b->nombre,CABECERA(b)->modif,CABECERA(b)->antiguo);
	
	sprintf(mimensaje+strlen(mimensaje),"<thead><tr>"\
	"<th style=\"width:%dpx\">Campo</th>"\
	"<th style=\"width:%dpx\">Tipo</th>"\
	"<th style=\"width:%dpx\">Lon</th>"\
	"<th style=\"width:%dpx\">Err.</th>"\
	"<th style=\"width:%dpx\">V.</th>"\
	"<th style=\"width:%dpx\">T.</th>"\
	"<th style=\"width:%dpx\">M.</th>"\
	"<th >Valor</th></tr></thead>\n", 
		v10x2pxsm(21,damepxcol(b)),
		v10x2pxsm(11,damepxcol(b)),
		v10x2pxsm(5,damepxcol(b)),
		v10x2pxsm(5,damepxcol(b)),
		v10x2pxsm(3,damepxcol(b)),
		v10x2pxsm(3,damepxcol(b)),
		v10x2pxsm(3,damepxcol(b)));		
	for (i=0;i<b->ncamp;i++) {
		c=b->c+i;
		bcampo2a(b,c->nombre,destino,0);
        if (!c->noupdate) if (comparacampo(b,c,direcantcampo(b,i))!=0) modificado=1;
		sprintf(mimensaje+strlen(mimensaje),"<tr fila=%d class=\"%s\">"\
			"<td style=\"text-align:left\">%s</td>"\
			"<td style=\"text-align:left\">%s</td>"\
			"<td style=\"text-align:right\">%d</td>"\
			"<td style=\"text-align:right\">%d</td>"\
			"<td style=\"style=\"text-align:right\">%d</td>"\
			"<td style=\"style=\"text-align:right\">%d</td>"\
			"<td style=\"style=\"text-align:right\">%d</td>"\
			"<td style=\"style=\"text-align:left\">%s</td></tr>\n ",
				i+1,i%2==0?"dpar":"dimpar",
				c->nombre,
				dameoratipo(c->tipo),
				c->lon,
				*FERROR(b,c),
				c->virtual,
				c->tabla,
				modificado,
				destino);
	}
	strcat(mimensaje,"</table>");
	v10usaansi=0;
    v10usaansi=antansi;
	v10wwwmensajecampos(titulo,mimensaje);
}

void v10wwwformerror(forms *f,char *msg)
{
  char mimensaje[MAXCADENA]="";
  int antpul=ult_pul;
  sprintf(mimensaje,"Causa: %s", v10translate(msg));
  v10wwwmensajegen("ERROR FORM",mimensaje);
  ult_pul=antpul;
}              

static void adaptaruta(char *cad) {
	char *ptr;
	ptr=cad;
	do {
		ptr=strstr(ptr,"\\");
		if (!ptr) break;
		v10reemplazapatron(ptr,"\\","\\\\",1);		
		ptr+=2;
	} while (ptr);
}

void v10wwwforminfo(forms *f)
{
  char mimensaje[MAXCADENA]="";
  char *err_oracle;
  char *nform,*nbloque, *ncampo;
  int antpul=ult_pul;
  bloques *b;
  int nc,i;
  char pathf[MAXPATH], pathb[MAXPATH], form[MAXPATH],mionline[MAXCADENA]=""; 
  int ret,ch,salir=0;

  nform=nbloque=ncampo="";
  err_oracle=calloc(1,MAXCADENA);
  if (f) {
     nform=f->nombre;
     b=f->b[f->act];
     nbloque=b->fichero;
     for (nc=0;nc<b->ncamp;nc++) {
         if (b->vi.act==b->c[nc].v) ncampo=b->c[nc].nombre;
       }
   }
  strcpy(form, nform);
  if (strstr(form,"FRM")==NULL) strcat(form, ".FRM");
  ret=damenombrecompleto(form, pathf);
  if (ret==0) {
  	sprintf(mimensaje+strlen(mimensaje)," Form  : %-40.40s<br/>", form);
    sprintf(mimensaje+strlen(mimensaje)," Path  : %-60.60s<br/>", pathf);
  } else {
  	strcpy(form,"");
  	sprintf(mimensaje+strlen(mimensaje)," Form  :<br/>");
  	strcpy(pathf,"");
    sprintf(mimensaje+strlen(mimensaje)," Path  :<br/> ");
  }
  sprintf(mimensaje+strlen(mimensaje)," Bloque: %-40.40s<br/>", nbloque);
  damenombrecompleto(nbloque, pathb);
  sprintf(mimensaje+strlen(mimensaje)," Path  : %-60.60s<br/><br/>", pathb);
  sprintf(mimensaje+strlen(mimensaje)," Campo : %-40.40s<br/>",ncampo);
  if (f->tipotriger>=0) {
     sprintf(mimensaje+strlen(mimensaje)," Tipo Triger %d<br/>",f->tipotriger);
   }
  if (f->terror) {
     sprintf(mimensaje+strlen(mimensaje)," Nombre %s<br/><br/>",f->terror->nombre);
     if (f->terror->msg) {
        sprintf(mimensaje+strlen(mimensaje),"   Mensaje %s<br/>",f->terror->msg);
      }
   }
  
  sprintf(mimensaje+strlen(mimensaje),"Ultimo error forms %d<br/>",f->formerr);
  getlastdberror(err_oracle);
  trim(err_oracle);
  sprintf(mimensaje+strlen(mimensaje)," Ultimo error ORACLE %s",err_oracle);
  adaptaruta(pathb);
  adaptaruta(pathf);
  sprintf(mimensaje+strlen(mimensaje),"<script>var nbloque='%s';var pathb='%s';var form='%s';var pathf='%s';</script>",
	  nbloque,pathb,form,pathf);
  
  *mionline=0;
  for (i=0;i<10;i++) {	
	  if (i%2==0) strcat(mionline,"<tr style=\"height:25px\">");	
	  sprintf(mionline+strlen(mionline),"<td><input type=\"button\" class=\"v10button\" style=\"width:60px;height:23px\" onclick=\"{%s;fonkeyupmsj(window.event,%d);}\"value=\"%s\"/><span class=\"v10spanforminfo\">%s</span></td>",ionline[i].ctrl?"v10lib.ctrl=1":"v10lib.ctrl=0",ionline[i].tecla,ionline[i].teclas,ionline[i].texto);
	  if (i%2==1) strcat(mionline,"</tr>");	
  }  
  while (!salir) {
     ch=v10wwwmensajeforminfo("INFORMACION FORM",mimensaje, mionline);
	 if (protegidoform==9) {
         switch (ch) {
			case F(4):	{	char *ptr,miwhere[MAXCADENA]="",nomfichero[MAXPATH]="",mititulo[MAXCADENA]="";
							strcpy(nomfichero,f->b[f->act]->fichero);
							ptr=strchr(nomfichero,'.');
							if (ptr) *ptr=0;
                            sprintf(miwhere, "NBLOQUE=UPPER(\'%s\')", nomfichero);
							sprintf(mititulo,"PROPIEDADES DEL BLOQUE %s",f->b[f->act]->fichero);
							fcejecutaform(f->b[f->act],"VDDEFBLOQUEINFO","S",miwhere,"","","",mititulo,"S");
							break;
						}
            case C_F(4): v10wwwmuestracampos(b);
                          break;           
            case C_F(10):invocaeditor(pathb,NULL);
                         break;
            case C_F(11):invocaeditor(pathf,NULL);
                         break;
            case C_F(12):{char *fichero[MAXBLOQUES+1],destino[MAXPATH];
                          int nb;
                          for (nb=0;nb<f->nbloques;nb++) {
                              damenombrecompleto(f->b[nb]->fichero,destino);
                              fichero[nb]=strdup(destino);
                          }
                          fichero[nb]=strdup(pathf);
                          invocaeditormultiple(fichero,f->nbloques+1);
                          for (nb=0;nb<f->nbloques;nb++) free(fichero[nb]);
                          free(fichero[nb]);
                         }
                         break;
            default:     salir=1;
                         break;
         }
	 } else break;
  }
 
  free(err_oracle);
  ult_pul=antpul;
}


