/*
* Módulo : V10FORMENU.C
* Objeto:  Gestion del menu principal de la aplicacion
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10form.h"

#define MAXOPCIONES 90
#define MAXMENUTRIGERS 50
#define MAXFICHMENU 50


int nmenutriger,noptriger;
defopciones defop[MAXMENUTRIGERS];
static char *fichmenu[MAXFICHMENU];
static int numfichmenu;

static void initformenu(void);

#define MAXPROF     10
#define INDENTADOH 1
#define INDENTADOV 1
#define POSH 2
#define POSV 1
#define POSPY 4


static menus *vmenu;
static int nivel;
static int elegidas[MAXPROF];
char *buffer;
int init_formenu;
menutrigers mt[MAXMENUTRIGERS];

static void liberafichmenu(void)
{
    while (--numfichmenu>=0) free(fichmenu[numfichmenu]);
}

static void anadefichmenu(char *fichero)
{
	char destino[MAXPATH];
    if (numfichmenu<=MAXFICHMENU-1) {
		damenombrecompleto(fichero,destino);
        fichmenu[numfichmenu++]=strdup(destino);
    }
}

static void ejecuta_menutriger(char *nombre,void *dato)
{
	int nt;
	for (nt=0;nt<nmenutriger;nt++) {
		char *param;
		if ((param=strchr(nombre,' '))!=NULL) {
			*param++=0;
		}
		if (strcmp(nombre,mt[nt].nombre)==0) {
			mt[nt].fun(param,mt[nt].dato);
         return;
		}
		if (param) param[-1]=' ';
	}
	mensajefcm(10,"Triger %s no existe",nombre);
}

static void ejecutaexterno(char *comando,int pwd)
{
  char cadena[MAXCADENA];
  int ret;
  if (comando) {
    if (pwd) {
        char *aux,achar;
        aux=comando;
        while (*aux && *aux!=' ') {
              aux++;
              if (*aux=='"') {
                 aux++;
                 while (*aux && *aux=='"') aux++;
               }
         }
        achar=*aux;
        *aux=0;
        if (achar) sprintf(cadena,"%s -OU%s/%s@%s %s",comando,ORAUSR,ORAPWD,ORADB,aux+1);
           else sprintf(cadena,"%s -OU%s/%s@%s",comando,ORAUSR,ORAPWD,ORADB);
        *aux=achar;
     } else sprintf(cadena,"%s",comando);
     ret=WinExec(cadena,1);
     if (ret<32) {
       switch (ret) {
          case 8:
          case 0: mensajefcm(10,"Falta memoria para ejecutar el programa");
                  break;
          case 2:
          case 3: mensajefcm(10,"Programa no existe");
                  break;
          case 5: mensajefcm(10,"Error de red");
                  break;
          case 20:
          case 6: mensajefcm(10,"Error de DLL");
                  break;
          case 15:
          case 14:
          case 11:
          case 10:mensajefcm(10,"Version de Windows incorrecta");
                  break;
          case 13:mensajefcm(10,"Aplicacion es DOS");
                  break;
          case 16:mensajefcm(10,"Aplicacion ya abierta");
                  break;
          case 19:mensajefcm(10,"Fichero comprimido");
                  break;
          case 21:mensajefcm(10,"Debe instalar WIN32S");
                  break;
         }
       }

   }
}

static void ejecutaoracle(char *param,void *dato)
{
	ejecutaexterno(param,1);
}

static void ejecutaexe(char *param,void *dato)
{
	ejecutaexterno(param,0);
}

static void ejecutamenu(char *param,void *dato)
{
	presentamenu((menus *)param);
}

static void ejecuta_form(char *nombre,void *dato)
{
  windows w; 
  char *copia;
  char *op=strchr(nombre,' ');
  if (!v10versionweb) {
	initvn(&w,1,1,COLUMNASPANTALLA-2,LINEASPANTALLA-2,"defecto");
	copia=salvavd(&w);
  }
  if (op) {
     *op=0;
     op++;
  }
  cargaform(nombre,op);
  if (op) {
     *--op=' ';
  }
  if (!v10versionweb) recuperavd(&w,copia);
}


void declaramenutriger(char *nombre,int (*fun)(char *param,void *dato),void *dato)
{
	if (nmenutriger==MAXMENUTRIGERS-1) final(("Demasiados trigers %s",nombre));
	strcpy(mt[nmenutriger].nombre,nombre);
	mt[nmenutriger].fun=fun;
	mt[nmenutriger].dato=dato;
	nmenutriger++;
}

void declaraopciontriger(char opcion,void (*fun)(char *param,void *dato),void *dato)
{
	int nop;
	if (!init_formenu) initformenu();
	for (nop=0;nop<noptriger;nop++) {
		if (defop[nop].opcion==opcion) {
			defop[nop].fun=fun;
			defop[nop].dato=dato;
			return;
		}
	}
	if (noptriger==MAXMENUTRIGERS-1) final(("Demasiadas opciones al menu %c",opcion));
	defop[noptriger].opcion=opcion;
	defop[noptriger].fun=fun;
	defop[noptriger].dato=dato;
	noptriger++;
}

void libera_menu(menus *ret)
{
  int nop;

  if (ret->titulo) free(ret->titulo);
  if (ret->fichero) free(ret->fichero);
  for (nop=0;nop<ret->numop;nop++) {
    if (ret->op[nop].nombreop) free(ret->op[nop].nombreop);
    if (ret->op[nop].tipo=='M') libera_menu((menus *)ret->op[nop].param);
    else if (ret->op[nop].param) free(ret->op[nop].param);
  }
  if (ret->op) free(ret->op);
  free(ret);
}

/*static*/ int eligeop(opmenus *op)
{
  int nop;
  for (nop=0;nop<noptriger;nop++) {
	  if (op->tipo==defop[nop].opcion) {
		  defop[nop].fun(op->param,defop[nop].dato);
		  return(0);
	  }
  }
  mensajefcm(10,"Tipo de menu no implementado %c",op->tipo);
  return(0);
}

/*static*/ int elige(virtsels *s)
{
  int indice=VIRTPOS(s);
  opmenus *op=vmenu->op+indice;
  int nop;
  if (indice>=vmenu->numop) final(("Ha seleccionado una opcion muy alta"));
  elegidas[nivel-1]=indice;
  for (nop=0;nop<noptriger;nop++) {
	  if (op->tipo==defop[nop].opcion) {
		  defop[nop].fun(op->param,defop[nop].dato);
		  return(0);
	  }
  }
  mensajefcm(10,"Tipo de menu no implementado %c",vmenu->op[indice].tipo);
  return(0);
}

void editamenus(void) {
	invocaeditormultiple(fichmenu,numfichmenu);
}

static int teclamenuform(virtsels *s)
{
    int ret,salir=0;
    menustructs *d = (menustructs *)s->dato;
    int (*funcion)(virtsels *s)=d->dato;
    while (!salir) {
        ret = tecla();
        if (ret == C_F(12)) {
            invocaeditormultiple(fichmenu, numfichmenu);
        }  else if (ret == C_F(10)) {
                   char completo[MAXPATH];
                   damenombrecompleto(s->titulo, completo);
                   invocaeditor(completo,NULL);
                }  else if (ret == cr) funcion(s);
                         else        salir=1;
    }
    return(ret);
}



void STDpresentamenu(menus *m)
{
    char **opciones;
    menus *antmenu=vmenu;
    int nop;

    vmenu=m;
    opciones=calloc(MAXOPCIONES,sizeof(char *));
    opciones[0]=m->titulo;
    for (nop=1;nop<=m->numop;nop++) opciones[nop]=m->op[nop-1].nombreop;
    opciones[nop]=NULL;
    nivel++;
    nop=0;
    do {
        char *miayuda=strdup(m->titulo);
        v10ponayuda(v10oemtoansi(miayuda,miayuda));
        free(miayuda);
        nop=menutotal(opciones,nop,(nivel-1)*INDENTADOV+POSV+1,(nivel-1)*INDENTADOH+POSH+1,-1,-1,1,NULL,(int (*)(virtsels *s))v10busca,NULL,teclamenuform,elige);
        v10quitaayuda();
    } while (((ult_pul!=esc && nivel>1) || (ult_pul!=A_F(10) && nivel==1)) && (nivel==1 || ult_pul!=MOUSEPOS));
    nivel--;
    free(opciones);
    vmenu=antmenu;
}

static char *leeansi(char *buffer,int n,FILE *entrada)
{
    char *ret;
    ret=fgetss(buffer,n,entrada);
    return(ret);
}   


static menus *lee_submenu(FILE *entrada,int subnivel,char *titulo)
{
    menus *ret;
    ret=calloc(1,sizeof(menus));
    ret->titulo=strdup(titulo);
    ret->fichero = strdup(titulo);
    ret->op=calloc(MAXOPCIONES,sizeof(opmenus));
    ret->numop=0;
    if (*buffer==0) leeansi(buffer,MAXCADENA,entrada);
    trim(buffer);
    while (*buffer!='\0') {
        char *aux;
        int bl = 0;
        while(bl<subnivel && buffer[bl]==' ') bl++;
        if (bl<subnivel) break;
        while(buffer[bl]==' ') bl++;
        if (bl>subnivel) {
            menus *subsubmenu;
            subsubmenu=lee_submenu(entrada,bl,ret->op[ret->numop-1].param);
            if (ret->op[ret->numop-1].param) free(ret->op[ret->numop-1].param);
            ret->op[ret->numop-1].param=(char *)subsubmenu;
        } else {
            char *mitrad,tok[MAXPATH];
            if ((aux=strchr(buffer+subnivel,';'))==NULL) final(("Linea de menu sin ; %s",buffer));
            *aux=0;
            aux=buffer+subnivel;
            mitrad=aux;
            while (*mitrad && (*mitrad==' ' || (*mitrad>='0' && *mitrad<='9') || *mitrad=='.')) mitrad++;
            strcopia(tok,aux,(int)(mitrad-aux));
            strcpy(tok+strlen(tok),v10translate(mitrad));
            ret->op[ret->numop].nombreop=strdup(tok);
            aux+=strlen(aux);
            *aux=';';
            ret->op[ret->numop].tipo=pasacarmay(aux[1]);
            if (aux[1] && aux[2]==';') ret->op[ret->numop].param=strdup(aux+3);
            else final(("En %s.",buffer));
            if (ret->op[ret->numop].tipo=='S') {
                FILE *auxiliar;
                menus *subsubmenu;
                auxiliar=fopenseguro(ret->op[ret->numop].param,"r");
                anadefichmenu(ret->op[ret->numop].param);
                *buffer=0;
                subsubmenu=lee_submenu(auxiliar,0,ret->op[ret->numop].param);
                if (ret->op[ret->numop].param) free(ret->op[ret->numop].param);
                ret->op[ret->numop].param=(char *)subsubmenu;
                fclose(auxiliar);
                ret->op[ret->numop].tipo='M';
            }
            ret->numop++;
            if (ret->numop>=MAXOPCIONES-1) final(("Demasiadas opciones en menu %d/%d",ret->numop,MAXOPCIONES));
            if (leeansi(buffer,MAXCADENA,entrada)==NULL) *buffer=0;
            trim(buffer);
        }
    }
    if (ret->numop==0) {
        free(ret->op);
        ret->op=NULL;
    } else ret->op=realloc(ret->op,ret->numop*sizeof(opmenus));
    return(ret);
}

static void carga_ayuda(void)
{
  char *aux;

  if ((aux=strchr(buffer+1,';'))!=NULL) *aux='\0';
  else final(("En %s.",buffer+1));
  if (aux+1) strcpy(file_help,aux+1);
  else final(("Sin fichero de help"));
}

static menus *lee_menugen(FILE *fichero)
{
  menus *ret;

  *buffer='\0';
  leeansi(buffer+1,MAXCADENA-1,fichero);
  trim(buffer);
  carga_ayuda();
  ret=lee_submenu(fichero,0,buffer+1);
  return(ret);
}

static void posiciona_menu(char *opciones)
{
  int teclas[40];
  int i,num,nteclas=0;

  while (*opciones) {
    num=*opciones++-'0';
    if (*opciones) num=num*10+*opciones++-'0';
    for (i=0;i<num;i++) teclas[nteclas++]=cua;
    if (*opciones) teclas[nteclas++]=13;
  }
  while (nteclas) pushtecla(teclas[--nteclas]);
}

static void pide_menu(FILE *fichero,char *opciones)
{
  menus *ret;

  if (opciones) posiciona_menu(opciones);
  ret=lee_menugen(fichero);
  fclose(fichero);
  free(buffer);
  presentamenu(ret);
  libera_menu(ret);
}


static void borrapantallaforms(char *cadena)
{
  charblanco='²';
  cls(0,0,COLUMNASPANTALLA-1,LINEASPANTALLA-1,0);
  charblanco=' ';
  pintapantallav10(cadena);
}

void presentamenuform(char *nombre,char *cadena,char *opciones)
{
    FILE *fichero;
    if (!init_formenu) initformenu();
    fichero=fopenseguro(nombre,"r");
    anadefichmenu(nombre);
    buffer=calloc(1,MAXCADENA);
    cadena=v10translate(cadena);
    borrapantallaforms(cadena);
    fseek(fichero,SEEK_SET,0);
    pide_menu(fichero,opciones);
    fclose(fichero);
    liberafichmenu();
}

static void initformenu(void)
{
	init_formenu=1;
	declaraopciontriger('C',ejecuta_menutriger,NULL);
	declaraopciontriger('F',ejecuta_form,NULL);
	declaraopciontriger('E',ejecutaexe,NULL);
	declaraopciontriger('O',ejecutaoracle,NULL);
	declaraopciontriger('M',ejecutamenu,NULL);
}