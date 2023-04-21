/*
* M๓dulo : V10FORMSG.C
* Objeto:  Tratamiento de mensajes al usuario en un formulario
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10form.h"

static char *indexacampo(bloques *b,int nc)
{
    static char buffer[MAXCADENA];
    if (nc>=b->ncamp) return(NULL);
    if (nc==-1) {
        sprintf(buffer,"Campos del bloque %s",b->nombre);
    } else {
        char destino[MAXCADENA];
        int modificado=0;
        fcampos *c=b->c+nc;
        bcampo2a(b,c->nombre,destino,0);
        if (!c->noupdate) {
           if (comparacampo(b,c,direcantcampo(b,nc))!=0) modificado=1;
        }
        sprintf(buffer,"%-20.20s %-10.10s %4d %4d %2d %2d %2d %s",c->nombre,dameoratipo(c->tipo),c->lon,*FERROR(b,c),c->virtual,c->tabla,modificado,destino);
    }
    return(buffer);
}

void STDmuestracampos(bloques *b)
{ 
    int antansi=v10usaansi;
    char titulo[MAXCADENA];
    sprintf(titulo,"Bloque %s\n Modificado %d Antiguo %d\n Campo                Tipo       Lon  Err. V. T. M. Valor\n ออออออออออออออออออออ ออออออออออ ออออ ออออ ออ ออ ออ ออออออออออออออออออออออ",b->nombre,CABECERA(b)->modif,CABECERA(b)->antiguo);
    v10usaansi=0;
    menucabecera(b,0,0,4,titulo,1,1,COLUMNASPANTALLA-3,LINEASPANTALLA-4,1,(char *(*)(void *,int))indexacampo,(int (*)(virtsels *s))v10busca,NULL,NULL,NULL);   
    v10usaansi=antansi;
}

void STDformerror(forms *f,char *msg)
{
  windows w;
  int antpul=ult_pul;
  tpixels *copia;
  initvn(&w,1,LINEASPANTALLA-3,COLUMNASPANTALLA-2,LINEASPANTALLA-2,"FORMERR");
  copia=salvavd(&w);
  enmarca(&w,0,"ERROR FORM");
  msg=strdup(v10translate(msg));
  v10printf(&w,v10translate("Causa: %s"),msg);
  free(msg);
  mensajev(&w,v10translate("Pulse una tecla para continuar"));
  tecla();
  recuperavd(&w,copia);
  ult_pul=antpul;
}              

void STDforminfo(forms *f)
{
  windows w;
  tpixels *copia;
  char *err_oracle;
  char *nform,*nbloque, *ncampo;
  int antpul=ult_pul;
  bloques *b;
  int nc;
  char pathf[MAXPATH], pathb[MAXPATH], form[MAXPATH], dir[MAXPATH], comando[MAXPATH];
  int ret,ch,salir=0;

  initvn(&w,10,10,90,25,"FORMERR");          
  copia=salvavd(&w);
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
  enmarca(&w,0,"INFORMACION FORM");
  strcpy(form, nform);
  if (strstr(form,"FRM")==NULL) strcat(form, ".FRM");
  ret=damenombrecompleto(form, pathf);
  if (ret==0) {
  	v10printf(&w,"\n Form  : %-40.40s", form);
    v10printf(&w,"\n Path  : %-60.60s", pathf);
  } else {
  	strcpy(form,"");
  	v10printf(&w,"\n Form  :");
  	strcpy(pathf,"");
    v10printf(&w,"\n Path  : ");
  }
  v10printf(&w,"\n Bloque: %-40.40s", nbloque);
  damenombrecompleto(nbloque, pathb);
  v10printf(&w,"\n Path  : %-60.60s\n", pathb);
  v10printf(&w,"\n Campo : %-40.40s",ncampo);
  if (f->tipotriger>=0) {
     v10printf(&w,"\n Tipo Triger %d",f->tipotriger);
   }
  if (f->terror) {
     v10printf(&w,"\n Nombre %s\n",f->terror->nombre);
     if (f->terror->msg) {
        v10printf(&w,"   Mensaje %s\n",f->terror->msg);
      }
   }
  v10printf(&w,"\n Ultimo error forms %d\n",f->formerr);
  getlastdberror(err_oracle);
  trim(err_oracle);
  v10printf(&w," Ultimo error ORACLE %s",err_oracle);
  pintaonline("\n  {Ctrl-F4} Muestra campos {Ctrl-F5} Copiar path form {Ctrl-F6} Copiar form {Ctrl-F7} Copiar path bloque {Ctrl-F8} Copiar bloque {Ctrl-F9} Abrir carpeta bloque\n   {Ctrl-F10} Editar bloque   {Ctrl-F11} Editar form {Ctrl-F12} Edita todo {F4} Propiedades por defecto");
  while (!salir) {
     ch=STDtecla();
	 if (protegidoform==9) {
         switch (ch) {

			case F(4):	{	char *ptr,miwhere[MAXCADENA]="",nomfichero[MAXPATH]="",mititulo[MAXCADENA]="";
							strcpy(nomfichero,f->b[f->act]->fichero);
							ptr=strchr(nomfichero,'.');
							if (ptr) *ptr=0;
							sprintf(miwhere,"NBLOQUE=UPPER(\'%s\')",nomfichero);
							sprintf(mititulo,"PROPIEDADES DEL BLOQUE %s",f->b[f->act]->fichero);
							fcejecutaform(f->b[f->act],"VDDEFBLOQUEINFO","S",miwhere,"","","",mititulo,"S");
							break;
						}
            case C_F(4): STDmuestracampos(b);
                          break;
            case C_F(8): mete_en_clipboard(nbloque);
                         break;
            case C_F(7): mete_en_clipboard(pathb);
                         break;
            case C_F(6): mete_en_clipboard(form);
                         break;
            case C_F(5): mete_en_clipboard(pathf);
				break;
			case C_F(9):strcpy(dir, pathb);
			{ int i;
			for (i = strlen(dir); i > 0; i--) {
				if (dir[i] == '\\') {
					dir[i] = 0;
					break;
				}
			}
				sprintf(comando, "explorer %s", dir);
			ejecutacomando(comando, SW_SHOW, NULL);
			break;
			}
			case C_F(10):invocaeditor(pathb, NULL);
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
  recuperavd(&w,copia);
  borraonline();
  free(err_oracle);
  ult_pul=antpul;
}

void STDmensajeform(forms *f,char *mensaje,...)
{
  va_list arg;
  va_start(arg,mensaje);
  if (f->sucio==0) {
     if (f->copiamensaje==NULL) f->copiamensaje=salvavdm(&f->wmensaje,0);
   }
  clv(&f->wmensaje);
  mensaje=v10translate(mensaje);
  vv10printf(&f->wmensaje,mensaje,arg);
  f->sucio=1;
  va_end(arg);
}

void STDlimpiamensaje(forms *f)
{
	if (f == NULL) return;
  if (f->copiamensaje) {
     recuperavdm(&f->wmensaje,f->copiamensaje,0);
     f->copiamensaje=NULL;
   }
  f->sucio=0;
}

