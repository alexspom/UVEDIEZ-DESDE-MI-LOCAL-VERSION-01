/*
* Módulo : V10FORCAMPOS.C
* Objeto:  Tratamiento de campos en formularios
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10form.h"

int esnulo(void *var,int tipo)
{
  return(esnulov10tipo(var,tipo));
}

int damecampo(bloques *b,char *nombre)
{
  int nc;
  for (nc=0;nc<b->ncamp;nc++) {
      if (stricmp(b->c[nc].nombre,nombre)==0) return(nc);
    }
  return(-1);
}

int damecamposeguro(bloques *b,char *nombre)
{
  int nc;
  nc=damecampo(b,nombre);
  if (nc!=-1) return(nc);
  final(("Campo %s no existe en bloque %s",nombre,b->fichero));
  return(-1);
}

void *direccampo(bloques *b,int camp)
{
  void *ret;
  fcampos *c=b->c+camp;
  if (camp>=b->ncamp) final(("Referencia a campo muy alta"));
  if (!c->virtual) return(b->buffer+c->off);
  if (b->padre==NULL) {
     if (c->off>b->form->ncamp) final(("Referencia a campo muy alta"));
     return(b->form->buffer+b->form->c[c->off].off);
   }
  ret=direccampo(b->padre,c->off);
  return(ret);
}

void *direclockcampo(bloques *b,int camp)
{
  void *ret;
  fcampos *c=b->c+camp;
  if (camp>=b->ncamp) final(("Referencia a campo muy alta"));
  if (!c->virtual)     return(b->buffer+b->tamano+c->off);
  if (b->padre==NULL) {
     if (c->off>b->form->ncamp) final(("Referencia a campo muy alta"));
     return(b->form->buffer+b->form->c[c->off].off);
   }
  ret=direclockcampo(b->padre,c->off);
  return(ret);
}

void *direcantcampo(bloques *b,int camp)
{
  void *ret;
  fcampos *c=b->c+camp;
  if (camp>=b->ncamp) final(("Referencia a campo muy alta"));
  if (!c->virtual)     return(b->ant+c->off);
  if (b->padre==NULL) {
     if (c->off>b->form->ncamp) final(("Referencia a campo muy alta"));
     return(b->form->buffer+b->form->c[c->off].off);
   }
  ret=direcantcampo(b->padre,c->off);
  return(ret);
}

void *direcuquerycampo(bloques *b,int camp)
{
  void *ret;
  fcampos *c=b->c+camp;
  if (camp>=b->ncamp) final(("Referencia a campo muy alta"));
  if (!c->virtual)     return(b->bufuquery+b->c[camp].off);
  if (b->padre==NULL) {
     if (c->off>b->form->ncamp) final(("Referencia a campo muy alta"));
     return(b->form->buffer+b->form->c[c->off].off);
   }
  ret=direccampo(b->padre,c->off);
  return(ret);
}


void *direccampoptr(bloques *b,fcampos *c)
{
  void *ret;
  if (!c->virtual)     return(b->buffer+c->off);
  if (b->padre==NULL) {
     if (c->off>b->form->ncamp) final(("Referencia a campo muy alta"));
     ret=b->form->buffer+b->form->c[c->off].off;
   } else {
     ret=direccampo(b->padre,c->off);
   }
  return(ret);
}

void *direcncampo(bloques *b,char *nombre)
{
  void *ret;
  ret=direccampo(b,damecamposeguro(b,nombre));
  return(ret);
}

void *existecampo(bloques *b,char *nombre)
{
  void *ret;
  int nc=damecampo(b,nombre);
  if (nc<0) return(NULL);
  ret=direccampo(b,nc);
  return(ret);
}

int esnuloregistro(bloques *b)
{
  int ncamp;
  for (ncamp=CAMPOSEXTRA;ncamp<b->ncamp;ncamp++) {
      if (b->c[ncamp].virtual==1) continue;
      if (!esnulo(direccampo(b,ncamp),b->c[ncamp].tipo)) return(0);
   }
  return(-1);
}

int entrablebloque(bloques *b)
{
  v10inputs *v;
  for (v=b->vi.prim;v<=b->vi.ult;v++) {
      if (v->enter || b->enterquery|| (CABECERA(b)->antiguo==0)) { 
         fcampos *c=v->trigerdatos;
         if ((((c->tabla && b->noupdate)||c->noupdate)&& CABECERA(b)->antiguo )||c->oculto!=0||c->enter==0) continue;
         if (b->enterquery && !c->tabla && c->where==0) continue;
         return(1);
       }
   }
  return(0);
}

int damecampoform(forms *f,char *nombre)
{
  int nc;
  for (nc=0;nc<f->ncamp;nc++) {
      if (stricmp(f->c[nc].nombre,nombre)==0) return(nc);
    }
  return(-1);
}

void recuperacampo(bloques *b,fcampos *c,void *donde)
{
  memcpy(direccampoptr(b,c),donde,c->lon);
}

void copiacampo(bloques *b,fcampos *c,void *donde)
{
  memcpy(donde,direccampoptr(b,c),c->lon);
}

void *salvacampo(bloques *b,fcampos *c)
{
  void *ret;
  ret=calloc(1,c->lon);
  copiacampo(b,c,ret);
  return(ret);
}

int *indicadorcampo(bloques *b,fcampos *c,int numind)
{
	char *donde;
	if (numind>=NUMINDCAMPO) return(NULL);
	donde=direccampoptr(b,c);
	donde+=c->lon;
	return(((int *)(donde))+numind);
}

int *FERROR(bloques *b,fcampos *c)
{
    return(indicadorcampo(b,c,CINDERROR));
}

int *FSCAN(bloques *b,fcampos *c) 
{
	return(indicadorcampo(b,c,CINDSCAN));
}

static int comparacadena(char *s1,char *s2)
{
  while (*s1==*s2 && *s1) {
        s1++;
        s2++;
    }
  if (*s1==0) {
     if (es_blanco(s2)) return(0);
     return(-1);
   } else {
     if (*s2==0) {
        if (es_blanco(s1)) return(0);
        return(1);
      }
     return(*s1-*s2);
  }
}

static int wes_blanco(WCHAR *s)
{
    while (*s!=0) {
        if (*s!=32) return 0;
    }
    return(1);
}

static int comparawcadena(WCHAR *s1,WCHAR *s2)
{
  while (*s1==*s2 && *s1) {
        s1++;
        s2++;
    }
  if (*s1==0) {
     if (wes_blanco(s2)) return(0);
     return(-1);
   } else {
     if (*s2==0) {
        if (wes_blanco(s1)) return(0);
        return(1);
      }
     return(*s1-*s2);
  }
}


int comparacampo(bloques *b,fcampos *c,void *donde)
{
  int ret;
  switch (c->tipo) {
         case V10INT:
         case V10UINT:
         case V10SHORT:
         case V10USHORT:
         case V10LONG:
         case V10ULONG:
         case V10BYTE:
         case V10FLOAT:
         case V10DOUBLE:
         case V10FECHA:
         case V10HORA:
         case V10CHAR:ret=memcmp(donde,direccampoptr(b,c),c->lon);
                      break;
         case V10CADENA:ret=comparacadena(donde,direccampoptr(b,c));
                     break;
         case V10WCADENA:ret=comparawcadena(donde,direccampoptr(b,c));
                     break;
         default:    final(("Tipo no definido %d",c->tipo));
   }
  return(ret);
}

/*En esta funcion se recibe 
     b->ant registro de bd 
	 b->buffer registro que se extrajo 
	 b->buffer+b->tamano registro que hay en pantalla
*/
int compararegistrolock(bloques *b)
{
  int nc,ret=0;
  for (nc=0;nc<b->ncamp;nc++) {
      if (!b->c[nc].noupdate) {
		  ret=comparacampo(b,b->c+nc,direclockcampo(b,nc));
          if (ret) {
			  ret=comparacampo(b,b->c+nc,direcantcampo(b,nc));
			  if (ret) return(nc+1);
		  }
	  }
   }
  if (CABECERA(b)->modif!=CABANT(b)->modif) return(1);
  if (CABECERA(b)->antiguo!=CABANT(b)->antiguo) return(1);
  if (CABECERA(b)->borrado!=CABANT(b)->borrado) return(1);
  return(0);
}

int compararegistro(bloques *b)
{
  int nc,ret=0;
  for (nc=0;nc<b->ncamp;nc++) {
      if (!b->c[nc].noupdate) ret=comparacampo(b,b->c+nc,direcantcampo(b,nc));
      if (ret) return(nc+1);
   }
  if (CABECERA(b)->modif!=CABANT(b)->modif) return(1);
  if (CABECERA(b)->antiguo!=CABANT(b)->antiguo) return(1);
  if (CABECERA(b)->borrado!=CABANT(b)->borrado) return(1);
  return(0);
}

int numeroindicadorcampo(char *nombre)
{
	if (strcmp(nombre,"ERROR")==0) return(CINDERROR);
	if (strcmp(nombre,"SCAN")==0) return(CINDSCAN);
	if (strcmp(nombre,"DECIMALES")==0) return(CINDDEC);
	if (strcmp(nombre,"FORMATO")==0) return(CINDFORMATO);
	if (strcmp(nombre,"LPAN")==0) return(CINDLPAN);
	if (strcmp(nombre,"ENTER")==0) return(CINDENTER);
	if (strcmp(nombre,"NOINPUT")==0) return(CINDNOINPUT);
	if (strcmp(nombre,"INVISIBLE")==0) return(CINDINVISIBLE);
	if (strcmp(nombre,"NOUPDATE")==0) return(CINDNOUPDATE);
    if (strcmp(nombre, "COLOR") == 0) return(CINDCOLOR);
    if (strcmp(nombre, "AUTOENTER") == 0) return(CINDAUTOENTER);
    if (strcmp(nombre, "OLD") == 0) return(CINDOLD);
	return(-1);
}


int damebase(char *nombre,char *base)
{
	char *aux;
	if ((aux=strstr(nombre,"__"))) {
		*aux=0;
		strcpy(base,nombre);
		*aux='_';
		return(numeroindicadorcampo(aux+2));
	} else {
		strcpy(base,nombre);
		return(-1);
	}
}

char *direccampoind(bloques *b,int ncamp,int indicador)
{
	char *donde=direccampo(b,ncamp);
	fcampos *c=b->c+ncamp;
	if (donde==NULL) return(NULL);
	if (indicador<0 || indicador>=NUMINDCAMPO) return(donde);
    if (indicador == CINDOLD) return direcantcampo(b, ncamp);
	return(donde+c->lon+indicador*sizeof(int));
}

int dameindcampo(bloques *b,fcampos *c,char *indicador)
{
    int *ptr;
    int ind,valorind;
    ind=numeroindicadorcampo(indicador);
    ptr=(int *)direccampoind(b,(int)(c-b->c),ind);
    valorind=*ptr;
    switch (ind) {
        case CINDSCAN: if (valorind==-1) return(c->scan);
                       else              return(valorind);
                       break;
        case CINDDEC:  if (valorind==-1) return(c->dec);
                       else              return(valorind);
                       break;
        case CINDFORMATO: if (valorind==-1) return(c->format);
                          else              return(valorind);
                          break;
        case CINDLPAN:    if (valorind==-1) return(c->lvar);
                          else              return(valorind);
                          break;
        case CINDENTER:   if (valorind==-1) return(c->enter);
                          else              return(valorind);
                          break;
        case CINDNOINPUT:   if (valorind==-1) return(c->noinput);
                          else              return(valorind);
                          break;
        case CINDINVISIBLE:   if (valorind==-1) return(c->invisible);
                          else              return(valorind);
                          break;
        case CINDNOUPDATE:   if (valorind==-1) return(c->noupdate);
                          else              return(valorind);
                          break;
        case CINDAUTOENTER:   if (valorind==-1) return(c->autoenter);
                          else              return(valorind);
                          break;
    }
	return(-1);
}

int validocampo(bloques *b,fcampos *c)
{
  if (c->change) {
     if (*FERROR(b,c)) {
        *FERROR(b,c)=ejecutaftriger(b,PPOSTCHANGE,c->change,c);
       }
   }
  return(*FERROR(b,c));
}


void liberacampo(fcampos *c)
{
  int i;
  for (i=0;i<c->nteclas;i++) {
      liberatriger(c->teclas[i].trig);
   }
  free(c->datoconv);
  free(c->teclas);
  free(c->prefijo);
  free(c->tooltip);
  free(c->where);
  if (c->titulo) free(c->titulo);
  c->prefijo=NULL;
  c->teclas=NULL;
  c->nteclas=0;
  c->tooltip=NULL;  
  c->where=NULL;
  liberatriger(c->feventos.onclick);
  liberatriger(c->feventos.onrightclick);
  liberatriger(c->feventos.oncenterclick);
  liberatriger(c->feventos.ondbclick);
  liberatriger(c->feventos.onmouseover);
  liberatriger(c->feventos.onmouseout);
  liberatriger(c->feventos.onmousemove);
  liberatriger(c->contextual);
  if (c->checkbox) {
	free(c->checkbox->valor_true);
	free(c->checkbox->valor_false);
	free(c->checkbox);
  }
  liberatriger(c->change);
  liberatriger(c->pref);
  liberatriger(c->postf);
  liberatriger(c->prepinta);
  liberatriger(c->postpinta);
  liberatriger(c->onpinta);
  liberatriger(c->convfrombd);
  liberatriger(c->conv2bd);
  if (c->combox.activo) {
    int i;
    for (i=0;i<c->combox.nopc;i++)
      free(c->combox.opc[i]);
  }
}
