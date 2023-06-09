/*
* M�dulo : V10FORTRIGER.C
* Objeto:  Trigers genericos de formularios
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10form.h"


/*Si el nombre de cursor en los parametros del triger comienza por un simbolo
  especial se moficia su comportamiento estos simbolos son:

    -  Inviente el sentido del cursor (Si falla devuelve SUCCESS EN caso contrario FAILURE
    $  Devuelve ignore esto es aborta con error pero no saca mensaje.
    @  Si falla el cursor no ejecuta ninguno mas y devuelve SUCCESS.
    +  Devuelve siempre SUCCESS.
    &  No se trata de un cursor sino de una funci�n
    %  Saca mensaje pero no devuelve error.
    !  Saca pregunta.
*/

#define CINVERSO    1
#define CIGNORE     2
#define CSOLOMEN    4
#define CTERMINA    8
#define CSUCCESS   16
#define CPREGUNTA  32
#define CFUNCION   64

int dameparametro(bloques *b,ftrigers *ft,int npar,int tipopar,void *var)
{
    char destino[MAXCADENA]="";	
	if (ft->nparam <= npar) return(-1);
    sustituyevariablessc(b,ft->param[npar],destino);
    switch(tipopar){
        case V10LONG:
        case V10INT:
            *(long *)var = atol(destino);
            break;
        case V10FLOAT:
            *(float *)var = (float)v10dval(destino,v10formatdef);
            break;
        case V10DOUBLE:
            *(double *)var = v10dval(destino,v10formatdef);
            break;
        case V10CADENA:
            strcpy((char *)var,destino);
            break;
        default:
            return(-1);
    }
    return(0);
}

static long calculaopciones(char **cursor)
{
  int opcion;
  long ret=0;
  int salir=0;
  while (!salir) {
        opcion=**cursor;
        switch (opcion) {
           case '-':ret|=CINVERSO;
                    break;
           case '$':ret|=CIGNORE;
                    break;
           case '%':ret|=CSOLOMEN;
                    break;
           case '@':ret|=CTERMINA;
                    break;
           case '+':ret|=CSUCCESS;
                    break;
           case '!':ret|=CPREGUNTA;
                    break;
           case '&':ret|=CFUNCION;
                    break;
           case '<':ret|=CDEBUG;
                    break;
           default: salir=1;
                    (*cursor)--;
                    break;
         }
         (*cursor)++;
    }
  return(ret);
}


int fejecutaparam(bloques *b,ftrigers *f,int numpar,long *opcion)
{
  int ret;
  long opciones;
  char *cursor;
  if (f->nparam<=numpar) {
     v10log(LOGERROR,"Intentando ejecutar parametro %ld en bloque %s triger %s cuando tiene solo %ld\n",numpar+1,b->fichero,f->nombre,f->nparam);
     return(-1);
   }
  if (f->tipoparam[numpar]==PARAMTRIGER) {
     ftrigers *ft=(ftrigers *)f->param[numpar];
     opciones=ft->opciones;
     ft->opciones=0;
     ret=ejecutaftriger(b,0,ft,FORM(b)->cinput);
     ft->opciones=opciones;
     if (opcion) {
        *opcion=ft->opciones;
      }
   } else {
     cursor=f->param[numpar];
     opciones=calculaopciones(&cursor);
     if (opciones & CFUNCION) {
        ftrigers *ft;
        ft=dametriger(cursor);
        if (ft==NULL) {
           mensajefcm(10,"no existe triger %s",cursor);
           ret=-1;
         } else {
           ret=ejecutaftriger(b,0,ft,NULL);
         }
      } else { 
         ret=ejecutafcursor(b,cursor);
         if (opciones&CDEBUG) {
             cursordebug(buscafcursor(b,cursor)->cur);
         }
      }
    }
  ret=resultadotriger(b,ret,opciones,f->param[numpar+1]);
  if (opcion) *opcion=opciones;
  return(ret);
}


static int fejecuta(bloques *b,ftrigers *f)
{
  int ret=SUCCESS;
  int nc;
  long opcion;
  if (f==NULL) return(ret);
  for (nc=0;nc<f->nparam;nc+=2) {
      ret=fejecutaparam(b,f,nc,&opcion);
      if ((opcion & CTERMINA) && ret) {
         ret=0;
         break;
       }
      if (ret) {
         f->msg=f->param[nc+1];
         break;
       }
   }
  return(ret);
}

static int fdesignacion(bloques *b,ftrigers *f)
{
  int ret;
  ret=fejecuta(b,f);
  if (!fdesignacionaux)
	  actualizabloque(b);	  
  return(ret);
}

static int ffailure(bloques *b, ftrigers *ft)
{
  return(FAILURE);
}

static int fsuccess(bloques *b, ftrigers *ft)
{
  return(SUCCESS);
}

static int queryautom(bloques *b, ftrigers *ft)
{
  pushtecla(F(3));  
  return(0);    
}                

static int queryhijo(bloques *b,ftrigers *f)
{
  int ret;
  if (b->padre==NULL) return(SUCCESS);
  if (esnuloregistro(b->padre)) {
      borrabloque(b,f);
	  return(IGNORAR);
  }
  ret=fejecuta(b,f);
  return(ret);
}




static int presehijo(bloques *b,ftrigers *ft)
{
  forms *f;
  int nb;
  int ret;
  ret=fejecuta(b,ft);
  if (ret) return(ret);
  f=FORM(b);
  for (nb=0;nb<f->nbloques;nb++) {
      if (f->b[nb]->padre==b) {
         bloques *bh=f->b[nb];
         if (bh->modif) if (commitsino(FORM(b))) return(IGNORAR);
         muestradialog(&bh->vi,0);
         borraregistro(bh,ft);
         selectpagina(bh,ft);
         presehijo(bh,NULL);
       }
    }
  return(SUCCESS);
}

static int presebloque(bloques *b,ftrigers *ft)
{
  forms *f;
  bloques *bh;
//  int ret;
  //ret=fejecuta(b,ft);
  //if (ret) return(ret);
  f=FORM(b);
  bh=damebloque(f,ft->param[0]);
  if (!bh) {
	  mensajefcm(10,"PRESEBLOQUE: Bloque %s no existe",ft->param[0]);
	  return(0);
  }
  if (bh->modif) if (commitsino(FORM(b))) return(IGNORAR);
  muestradialog(&bh->vi,0);
  borraregistro(bh,ft);
  selectpagina(bh,ft);
  presehijo(bh,NULL);
  return(SUCCESS);
}

static int ftransaccion(bloques *b,ftrigers *f)
{
	int ret;
	ret=fejecuta(b,f);
	if (ret) rollback();
	   else  commit();
	return(ret);
}

static int ftransaccionparc(bloques *b,ftrigers *f)
{
	static int nivel;
	int ret;
	nivel++;
	ejecutaimmediatoparam("SAVEPOINT TRANSACCIONPAR%d",nivel);
	ret=fejecuta(b,f);
	if (ret) {
		ejecutaimmediatoparam("ROLLBACK TO TRANSACCIONPAR%d",nivel);
	}
	nivel--;
	return(ret);
}

static int fif(bloques *b,ftrigers *f)
{
  int ret;

  if (f->msg) f->msg=NULL; 
  if (f->nparam<2) {
     mensajefcm(10,"Triger FIF debe tener al menos 2 parametros");
     return(FAILURE);
   }
  ret=fejecutaparam(b,f,0,NULL);
  if (ret==0) {
     ret=fejecutaparam(b,f,1,NULL);
   } else {
     if (f->nparam>2) {
        ret=fejecutaparam(b,f,2,NULL);
      } else ret=0;
   }
  return(ret);
}

static int fwhile(bloques *b,ftrigers *f)
{
  int ret=0;
  if (f->nparam<2) {
     mensajefcm(10,"Triger FWHILE debe tener al menos 2 parametros");
     return(FAILURE);
   }
  while (fejecutaparam(b,f,0,NULL)==0 && !ret) {
     ret = fejecutaparam(b,f,1,NULL);
   }
  return(ret);
}

static int ferrorcursor(bloques *b,ftrigers *f)
{
  fcursores *fcur;
  int ret;
  if ((fcur=buscafcursor(b,f->param[0]))==NULL) {
     mensajefcm(10,"No encuentro cursor %s",f->param[0]);
     return(-1);
   }
  if (fcur->cur==NULL) {
     final(("Intentando buscar error en un cursor de form no abierto"));
    }
  ret=errorcursor(fcur->cur);
  f->msg=NULL;
  return(ret);
}

static int ffetchcursor(bloques *b,ftrigers *f)
{
  int ret;
  ret=fetchfcursor(b,f->param[0]);
  f->msg=NULL;
  return(ret);
}

static int fverifica(bloques *b,ftrigers *f)
{
  char *cadena;
  char destino[MAXCADENA];
  forms *fo=FORM(b);
  if (fo->cinput->tipo!=V10CADENA) {
     mensajefcm(10,"Triger verifica en campo no cadena %s",fo->cinput->nombre);
     return(-1);
   }
  cadena=direccampoptr(b,fo->cinput);
  if (f->nparam>1) f->msg=f->param[1];
  sustituyevariablessc(b,cadena,destino);
  if (*destino==0) {
     if (strchr(f->param[0],' ')!=NULL)  return(0);
     return(-1);
   }
  if (strchr(f->param[0],*destino)==NULL) {
     return(-1);
   }
  return(0);
}

static int fenrango(bloques *b,ftrigers *f)
{
  forms *fo=FORM(b);
  char destino[MAXCADENA];
  if (f->nparam>1) f->msg=f->param[1];
  sustituyevariablessc(b,f->param[0],destino);
  switch (fo->cinput->tipo) {
      case V10CADENA: return(!contiene(destino,direccampoptr(b,fo->cinput)));
                      break;
      case V10INT:    return(!contienenum(destino,*(int *)direccampoptr(b,fo->cinput)));
                      break;
      case V10UINT:    return(!contienenum(destino,*(unsigned int *)direccampoptr(b,fo->cinput)));
                      break;
      case V10LONG:    return(!contienenum(destino,*(long *)direccampoptr(b,fo->cinput)));
                      break;
      case V10ULONG:    return(!contienenum(destino,*(unsigned long *)direccampoptr(b,fo->cinput)));
                      break;
      case V10SHORT:    return(!contienenum(destino,*(short *)direccampoptr(b,fo->cinput)));
                      break;
      case V10USHORT:    return(!contienenum(destino,*(unsigned short *)direccampoptr(b,fo->cinput)));
                      break;
      case V10DOUBLE:    return(!contienenum(destino,*(double *)direccampoptr(b,fo->cinput)));
                      break;
      case V10FLOAT:    return(!contienenum(destino,*(float *)direccampoptr(b,fo->cinput)));
                      break;
  }

  return(0);
}

static int fposicionacampo(bloques *b,ftrigers *f)
{                
  int ret;
  if (f->nparam<2) {
     mensajefcm(10,"Debe dar nombre de campo para posicionarse");
     return(-1);
   }
  ret=fejecutaparam(b,f,0,NULL);
  if (ret==0) posicionadialog(&b->vi,direcncampo(b,f->param[1]));
  return(0);
}

static int fentercampo(bloques *b,ftrigers *f)
{
  int ret;
  int i;
  if (f->nparam<3) {
     mensajefcm(10,"Debe dar nombre de campo para hacerlo entrable");
     return(-1);
   }
  ret=fejecutaparam(b,f,0,NULL);
  for (i=1;i<f->nparam;i+=2) {
      int nc;
      entrabledialog(&b->vi,direcncampo(b,f->param[i]),ret==0?atoi(f->param[i+1]):1-atoi(f->param[i+1]));
      nc=damecampo(b,f->param[i]);
      if (nc!=-1) b->c[nc].enter=ret==0?atoi(f->param[i+1]):1-atoi(f->param[i+1]);
    }
  return(0);
}

static int fvalnocero(bloques *b,ftrigers *ft)
{
  forms *f=FORM(b);
  void *donde;
  donde=direccampoptr(b,f->cinput);
  if (ft->nparam) ft->msg=ft->param[0];
  if (esnulo(donde,f->cinput->tipo)) return(-1);
  return(0);
}

static int fejecutacampo(bloques *b,ftrigers *ft)
{
  int ret;
  v10cursors *cursor;
  char *sql;
  sql=direcncampo(b,ft->param[0]);
  cursor=abrecursornombre(ft->param[0],sql);
  if (cursor==NULL) return(-1);
  ret=ejecutacursor(cursor);
  liberacursor(cursor);
  return(ret);
}

static int ffetchcampo(bloques *b,ftrigers *ft)
{	
  int ret;
  v10cursors *cursor;
  char *sql;
  sql=direcncampo(b,ft->param[0]);
  cursor=bindbloque(b,sql,ft->param[0]);
  if (cursor==NULL) return(-1);
  describebloque(b,cursor);
  ret=ejefetchcursor(cursor);
  liberacursor(cursor);
  return(ret);
}

static int frecalcpadre(bloques *b,ftrigers *f)
{
  int ret;
  bloques *padre;
  ret=fejecuta(b,f);
  if (ret) return(ret);
  padre=b->padre;
  if (padre==NULL) return(0);
  if (padre->fpostquery) {
      ejecutaftriger(padre,PPOSTQUERY,padre->fpostquery,NULL);
      ejecutapostchange(padre);
    }
  if (!frecalcpadreaux)
	  actualizabloque(padre);
  else
	  frecalcpadreaux(b,padre);
  grabareg(padre,VIRTPOS(padre->s));
  return(0);
}

static int fborraform(forms *f)
{
  int ret;
  ret=commit();
  if (ret) return(ret);
  limpiaform(f,NULL);
  f->act=0;
  return(IGNORAR);
}

static int fmodifica(bloques *b, ftrigers *ft)
{
  CABECERA(b)->modif=1;
  b->modif=1;
  b->form->modif=1;
  return(0);
}

static int fmodificawhere(bloques *b,ftrigers *f)
{
  if (f->nparam==0) {
     mensajefcm(10,"Debe indicar WHERE NUEVA");
     return(-1);
   }
  if (*f->param[0]!='.') {
     if (b->where) free(b->where);
     b->where=NULL;
     if (!es_blanco(f->param[0])) b->where=strdup(f->param[0]);
  }
  if (f->nparam>1) { 
     char *destino;
     destino=calloc(1,MAXCADENA);
     sustituyevariables(b,f->param[1],destino);
     free(b->vi.titulo);
     b->vi.titulo=strdup(destino);
     free(destino);
   }
  if (f->nparam>2) {
	  char *destino;
	  destino = calloc(1, MAXCADENA);
	  sustituyevariablessc(b, f->param[2], destino);
     if (b->orderby) free(b->orderby);
     b->orderby=NULL;
	 if (!es_blanco(destino)) b->orderby = strdup(destino);
	 free(destino);
   }
  encolatecla(F(2));
  return(0);
}

static int fpulsateclas(bloques *b,ftrigers *f)
{
  int nt;
  for (nt=0;nt<f->nparam;nt++) {
      int valor;
      valor=traducetecla(f->param[nt]);
      if (valor==0) valor=*f->param[nt];
      encolatecla(valor);
   }
  return(0);
}

static int fwinexec(bloques *b, ftrigers *f)
{
	char destino[MAXPATH];
	int show = SW_SHOW;
	if (f->nparam<1) {
		mensajefcm(10, "Debe dar nombre de programa");
		return(-1);
	}
	if (f->nparam>1) {
		show = atoi(f->param[1]);
	}
	sustituyevariablessc(b, f->param[0], destino);
	WinExec(destino, show);
	return(0);
}

static int freloadreg(bloques *b,ftrigers *f)
{
  int ret;
  if (b->soloquery) return(-1);
  if (CABECERA(b)->antiguo==0) return(0);
  if (b->reload==NULL) genreload(b);
  convierte2db(b,b->reload);
  ret=ejefetchcursor(b->reload);
  if (ret) return(ret);
  conviertefromdb(b,b->reload);
  memcpy(b->ant,b->buffer,(unsigned)b->tamano);
  memcpy(b->buffer+b->tamano,b->buffer,(unsigned)b->tamano);
  grabareg(b,VIRTPOS(b->s));
  CABECERA(b)->modif=0;
  b->modif=0;
  if (!v10versionweb) actualizabloque(b);
  return(0);
}

static int fesnuevo(bloques *b,ftrigers *f)
{
  int ret;
  ret=CABECERA(b)->antiguo;
  if (ret==0) return(-1);
  return(0);
}

static int fcommit(bloques *b,ftrigers *f)
{
  int ret;
  ret=commit();
  return(ret);
}

static int frollback(bloques *b,ftrigers *f)
{
  int ret;
  ret=rollback();
  return(ret);
}

static int fponsonido(bloques *b,ftrigers *f)
{
  formsuena=atoi(f->param[0]);
  return(0);
}

static int fplaywav(bloques *b,ftrigers *f)
{
  char nombre[MAXPATH],completo[MAXPATH];
  if (formsuena==0) return(0);
  if (f->nparam>0) {
	 sustituyevariablessc(b,f->param[0],nombre);
   } else {
     strcpy(nombre,"DEFECTO");
   }
  if (damenombrecompleto(nombre,completo)!=0) strcpy(completo,nombre);
  sndPlaySound(completo,SND_ASYNC);
  return(0);
}

static int flimpiaform(bloques *b,ftrigers *ft)
{
  int ret;
  ret=limpiaform(b->form,ft);
  return(ret);
}

static int borraform(bloques *b, ftrigers *ft)
{
  int ret;
  ret=fborraform(b->form);
  return(ret);
}

static int fponcaraccampo(bloques *b,ftrigers *ft)
{
	int ncamp,npar;
	char destino[MAXCADENA];
	fcampos *c;
	if (ft->nparam<3) {
		mensajefcm(10,"Pocos parametros en FPONCARACCAMPO %d",ft->nparam);
		return(-1);
	}
	if (((ft->nparam-1)%2)!=0) {
		mensajefcm(10,"Numero incorrecto de parametros en FPONCARACCAMPO %d",ft->nparam);
		return(-1);
	}
	sustituyevariablessc(b,ft->param[0],destino);
	ncamp=damecampo(b,destino);
	if (ncamp<0) {
		mensajefcm(10,"No existe campo %d en FPONCARACCAMPO",destino);
		return(-1);
	}
	c=b->c+ncamp;
    for (npar=1;npar<ft->nparam;npar+=2) {
		int indicador;
        sustituyevariablessc(b,ft->param[npar],destino);
		indicador=numeroindicadorcampo(destino);
		if (indicador<0) {
			mensajefcm(10,"Indicador %s no implementado en FPONCARACCAMPO",destino);
			continue;
		}
        sustituyevariablessc(b,ft->param[npar+1],destino);
		*indicadorcampo(b,c,indicador)=atoi(destino);
	}
	return(0);
}

static int fponcolorbloque(bloques *b,ftrigers *ft)
{
	char destino[MAXCADENA];
	sustituyevariablessc(b,ft->param[0],destino);
	strcpy(direcncampo(b,"V10_COLOR"),destino);
	return(0);
}

static int fsubstselect(bloques *b,ftrigers *ft)
{
	if (ft->nparam!=1) return(-1);
	if (damecampo(b,ft->param[0])==-1) return(-1);
	if (b->extraselect) free(b->extraselect);
	b->extraselect=strdup(direcncampo(b,ft->param[0]));
	return(0);
}

static int fdameordenador(bloques *b,ftrigers *ft)
{
    char *ordenador;
    char salida[MAXNOMBREV10];
	if (ft->nparam <1) return(-1);
    dameparametro(b,ft,0,V10CADENA,salida);
    ordenador=existecampo(b,salida);
    if (!ordenador) return(-1);
	strcpy(ordenador,damehostname());	
	return(0);
}

static int fswitchcadena(bloques *b,ftrigers *ft)
{
	int n;
	char resultado[MAXCADENA];
	char variable[MAXCADENA];
	if (ft->nparam < 3 || ft->nparam % 2 ==0) {
		v10log(LOGERROR,"%s","fswitchcadena - Numero minimo de parametros debe ser impar y mayor que 1\n");	
		wmensajeform(b,"fswitchcadena - Numero minimo de\n parametros debe ser \n impar y mayor que 1\n");
		return(-1);
	}
	dameparametro(b,ft,0,V10CADENA,resultado);
	for(n=1; n < ft->nparam ; n+=2){
		dameparametro(b,ft,n,V10CADENA,variable);
		if (!strcmp(variable,resultado) || *variable==0) return(fejecutaparam(b,ft,n+1,NULL));
	}
	return(-1);
}
int STDabrelink(char *link) 
{
	char sentencia[MAXCADENA]="";
	sprintf(sentencia,"iexplorer.exe %s",link);
	system(sentencia);
	return(0);
}

static int fabrelink(bloques *b,ftrigers *ft) 
{
    char destino[MAXCADENA]="";  
    sustituyevariablessc(b,ft->param[0],destino);
	return(pabrelink(destino));
}

static int fimagenboton(bloques *b,ftrigers *ft) 
{
	int i;
	char destino[MAXPATH]="",aux[MAXPATH]="";
	char nombre[MAXPATH]="",imagen[MAXPATH]="",estilo1[MAXPATH]="",estilo2[MAXPATH]="";
	fbotones *bot;	
	strcpy(nombre,ft->param[0]);
	if (ft->param[1]) {
		strcpy(aux,ft->param[1]);
		sustituyevariables(b,aux,destino);	
		strcopia(imagen,destino+1,strlen(destino+1)-1);	
	}
	if (ft->param[2]) strcpy(estilo1,ft->param[2]);
	if (ft->param[3]) strcpy(estilo2,ft->param[3]);

	for (i=0;i<b->numbotones;i++) {
		bot=b->fb+i;
		if (strcmp(bot->nombre,nombre)==0) {
			free(bot->image);
			if (*imagen==0) {
				bot->image=strdup("NO");
				sprintf(bot->includecss,"\"%s\"",estilo2);
			} else {
				bot->image=strdup(imagen);
				sprintf(bot->includecss,"\"%s\"",estilo1);	
			}			
			break;
		}
			
	}
	return(0);
}


static int fdebug(bloques *b,ftrigers *ft)
{
    if (ft->nparam>0) {
        oradebug=atoi(ft->param[0]);
    } else oradebug=DEPURAPRELOG|DEPURALOG|DEPURAPARSE|DEPURAEXEC|DEPURAFETCH;
	return(0);
}

static int fejecutatime(v10timers *lt, ftrigers *ft)
{
	bloques *b;
	ftrigers *f;
	f = lt->dato;
	if (f==NULL) return(0);
    b = f->b;
	if (v10versionweb) return(0);
	return(fejecuta(b,f));
}

static int fmuestraboton(bloques *b,ftrigers *ft) {
	fbotones *bot;
	if (ft->nparam==0) return(-1);
	bot=damebotonbloque(b,ft->param[0]);	
	if (!bot) return(-1);
	bot->oculto=0;
	return(0);
}

static int focultaboton(bloques *b,ftrigers *ft) {
	fbotones *bot;
	if (ft->nparam==0) return(-1);
	bot=damebotonbloque(b,ft->param[0]);
	if (!bot) return(-1);
	bot->oculto=1;
	return(0);
}

static int factivaboton(bloques *b,ftrigers *ft) {
	fbotones *bot;
	if (ft->nparam==0) return(-1);
	bot=damebotonbloque(b,ft->param[0]);
	if (!bot) return(-1);
	bot->disabled=0;
	return(0);
}


static int fdesactivaboton(bloques *b,ftrigers *ft) {
	fbotones *bot;
	if (ft->nparam==0) return(-1);
	bot=damebotonbloque(b,ft->param[0]);
	if (!bot) return(-1);
	bot->disabled=1;
	return(0);
}

static int fhtmlalert(bloques *b,ftrigers *ft) {
	if (ft->nparam==0) *b->htmlalert=0;
	else if (ft->nparam==1) strcpy(b->htmlalert,ft->param[0]);
	return(0);
}

static int fhtmlconfirm(bloques *b,ftrigers *ft) {
	if (ft->nparam==0) *b->htmlconfirm=0;
	else if (ft->nparam==1) strcpy(b->htmlconfirm,ft->param[0]);
	return(0);
}

static void sustituyebinds(v10cursors *c,char *sql)
{
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
			  pasaoracampo2ascii(ca,buffer,1,0);
			  strins(aux,buffer);
		}
	}
}
static int fcreaexcelc(bloques *b,ftrigers *ft)
{
    fcursores *cur;
    char nombrecur[MAXNOMBREV10]; 
	char sql[MAXSQL];   
    char plantilla[MAXPATH],destino[MAXPATH];
    int salir;
    dameparametro(b,ft,0,V10CADENA,nombrecur);
    dameparametro(b,ft,1,V10CADENA,plantilla);
    dameparametro(b,ft,2,V10CADENA,destino);
    dameparametro(b,ft,2,V10LONG,&salir);
    cur=buscafcursor(b,nombrecur);
    if (cur==NULL) return(-1);
    if (cur->cur==NULL) cur->cur=bindbloque(b,cur->sql,cur->nombre);
    if (cur->cur==NULL) return(-1);
    sustituyebinds(cur->cur,sql);
    sql2excel(sql,plantilla,destino,salir);
    return(0);
}

int reiniciaform(char *param,void *dato)
{
  int ret;
  char cadena[MAXCADENA];
  int i;

  sprintf(cadena,"%s",__argv[0]);
  for (i=1;i<__argc;i++) {
      sprintf(cadena+strlen(cadena)," \"%s\"",__argv[i]);
    }
  if (!v10versionweb) {
	  ret=WinExec(cadena,1);
	  exit(0);
  }  
  else {
	  Sleep(500);
	  ret=reinicia(cadena,1);
      Sleep(500);
      exit(0);
  }
 return(ret);
}

static int fposultimo(bloques *b, ftrigers *ft)
{
    int i = b->s->numero - 1;
    reposiciona(b->s, i);
    b->s->clin = i;
    leeregistroi(b, i);
    pintapaginabloque(b->s, 1);
    if (b->fpreregistro) {
        ejecutaftriger(b, PPREREGISTRO, b->fpreregistro, NULL);
    }
    return(0);
}

static int fcampobloque(bloques *b, ftrigers *f)
{
    if (FORM(b)->cinput) {
        fcampos *c;
        c = existecampo(b, FORM(b)->cinput->nombre);
        if (c) {
            a2bcampo(b, f->param[0], FORM(b)->cinput->nombre);
        }
        return(0);
    }
    else return -1;
}


void inittriger()
{
  declaratriger("LIMPIAFORM",flimpiaform,NULL);
  declaratriger("COMMIT",(void *)commitform,NULL);
  declaratriger("QUERY",selectpagina,NULL);
  declaratriger("INSERT",(void *)insertregistro,NULL);
  declaratriger("DELETE",deleteregistro,NULL);
  declaratriger("CLEAR",borraregistro,NULL);
  declaratriger("CLEARBLOCK",borrabloque,NULL);
  declaratriger("COPIAREG",copiaregistro,NULL);
  declaratriger("FFAILURE",ffailure,NULL);
  declaratriger("FSUCCESS",fsuccess,NULL);
  declaratriger("FEJECUTA",fejecuta,NULL);
  declaratriger("FDESIGNACION",fdesignacion,NULL);
  declaratriger("FVERIFICA",fverifica,NULL);
  declaratriger("FENRANGO",fenrango,NULL);
  declaratriger("QUERYAUTOM",queryautom,NULL);
  declaratriger("QUERYHIJO",queryhijo,NULL);
  declaratriger("PRESEHIJO",presehijo,NULL);
  declaratriger("PRESEBLOQUE",presebloque,NULL);
  declaratriger("FVALNOCERO",fvalnocero," Este campo no puede ser cero.");
  declaratriger("FRECALCPADRE",frecalcpadre,NULL);
  declaratriger("FBORRAFORM",borraform,NULL);
  declaratriger("FMODIFICA",fmodifica,NULL);
  declaratriger("FEJECUTAFORM",fejecutaform,NULL);
  declaratriger("FMODIFICAWHERE",fmodificawhere,NULL);
  declaratriger("FLEEMENU",fleemenucontextual,NULL);            
  declaratriger("FPOSICIONACAMPO",fposicionacampo,NULL);
  declaratriger("FENTERCAMPO",fentercampo,NULL);
  declaratriger("FIF",fif,NULL);
  declaratriger("FWHILE",fwhile,NULL);
  declaratriger("FERRORCURSOR",ferrorcursor,NULL);
  declaratriger("FFETCHCURSOR",ffetchcursor,NULL);
  declaratriger("FEJECUTACAMPO",fejecutacampo,NULL);
  declaratriger("FFETCHCAMPO",ffetchcampo,NULL);      
  declaratriger("FPULSATECLAS",fpulsateclas,NULL);
  declaratriger("FWINEXEC",fwinexec,NULL);    
  declaratriger("FRELOADREG",freloadreg,NULL);
  declaratriger("FPONSONIDO",fponsonido,NULL);
  declaratriger("FPLAYWAV",fplaywav,NULL);
  declaratriger("FESNUEVO",fesnuevo,NULL);
  declaratriger("FCOMMIT",fcommit,NULL);
  declaratriger("FROLLBACK",frollback,NULL);
  declaratriger("FTRANSACCION",ftransaccion,NULL);
  declaratriger("FTRANSACCIONPARC",ftransaccionparc,NULL);
  declaratriger("FPONCARACCAMPO",fponcaraccampo,NULL);
  declaratriger("FPONCOLORBLOQUE",fponcolorbloque,NULL);
  declaratriger("FSUBSTSELECT",fsubstselect,NULL);
  declaratriger("FDAMEORDENADOR",fdameordenador,NULL);
  declaratriger("FSWITCHCADENA",fswitchcadena,NULL);
  declaratriger("FDEBUG",fdebug,NULL);
  declaratriger("FEJECUTATIME",(void *)fejecutatime,NULL);
  declaratriger("FABRELINK",fabrelink,NULL);
  declaratriger("FIMAGENBOTON",fimagenboton,NULL);
// TRIGGERS DE LA WEB  
  declaratriger("FMUESTRABOTON",fmuestraboton,NULL);
  declaratriger("FOCULTABOTON",focultaboton,NULL);
  declaratriger("FACTIVABOTON",factivaboton,NULL);
  declaratriger("FDESACTIVABOTON",fdesactivaboton,NULL);
  declaratriger("FHTMLALERT",fhtmlalert,NULL);
  declaratriger("FHTMLCONFIRM", fhtmlconfirm, NULL);
  declaratriger("FPOSULTIMO", fposultimo, NULL);
  declaratriger("FCAMPOBLOQUE", fcampobloque, NULL);
  declaratriger("FCREAEXCELC", fcreaexcelc, NULL);
  declaratriger("FVALIDOBLOQUE", validobloque, NULL);
  declaramenutriger("REINICIAFORM",reiniciaform,NULL);
#ifndef __LINUX__
  initolefrm();
#endif
  initasfrm();
  initcsvfrm();
  initformseltabla();
}

