/*
* Módulo : V10INTDIALOG.C                                            
* Objeto:  Interpreta dialogos a partir de la pantalla pintada en texto
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"

#define MAXVENTANA 400

static char *lee_digito(char *cadena ,int *donde)
{
  int lon=0;
  while ((*cadena>='0')&&(*cadena<='9')) {
        lon=(lon*10)+(*cadena-'0');
        cadena++;
      }
  *donde=lon;
  return(cadena-1);
}

static void interpretapf(char *token,int *tipo,int *formato,int *dec,int *lon,int *lpan,int *password)
{
  char *p;
  *tipo=V10DOUBLE;
  if (strchr(token,'S'))  {
     *tipo=V10FLOAT;
   }
  if (strchr(token,'P'))  {
     if (password) *password=1;
   } else {
     if (password) *password=0;
    }
  if (strchr(token,','))  *formato=v10formatdef|MARCAMILES; else *formato=v10formatdef;
  p=strchr(token,'.');
  if (p) *dec=strlen(token)-(int)(p-token)-1; else *dec=0;
  *lon=*lpan=strlen(token);
  while (*token) {
      if (isdigit(*token)) {
          token=lee_digito(token,lon)+1;
      } else token++;
  }
}

static void interpretachar(char *token,int *tipo,int *formato,int *dec,int *lon,int *lpan,int *password)
{
  char *aux=token,carac;
  *tipo=V10CADENA;
  *formato=0;
  if (password) *password=0;
  *lpan=*lon=strlen(token);
  while (*aux) {
        carac=(char)toupper(*aux);
        switch (carac) {
          case 'M':if (*aux=='M') *formato|=FORMATOUPPER;
                    else          *formato|=FORMATOLOWER;
                   break;
          case 'R':*formato|=FORMATORAW;
                   break;
          case 'N':*formato|=FORMATONUM;
                   break;
          case 'D':*formato|=FORMATODATE;
                   break;
          case 'P':if (password) *password=1;
                   break;
          default:if (isdigit(carac)) {
                     aux=lee_digito(aux,lon);
                   }
         }
        aux++;
     }
}

char *analizatokendia(char *token,char **donde,int *tipo,int *formato,int *dec,int *lon,int *lpan,int *password)
{
  char *p=token;
  static char primeros[11]="@#&_$¿­/";
  static char *posibles[7]={"@ZLHSUP,1234567890",
                            "#ZLSP,.1234567890",
                            "&ZLP",
                            "_PDICMmRN1234567890",
                            "$",
                            "¿D-MY.",
                            "­"};
  *tipo=-1;
  while (*p) {
      char *ptok;
      if ((ptok=strchr(primeros,*p))!=NULL) {
          int tipotok=(int)(ptok-primeros);
          char *fintok,achar;
		  if (*p=='/') {
			  if (p[1]=='*') {
			     while ((*p!='*' || p[1]!='/') && *p) p++;
			     continue;
			  } else {
				  p++;
				  continue;
			  }
		  } 
          fintok=p+strspn(p,posibles[tipotok]);
          achar=*fintok;
          *fintok=0;
          *lon=*lpan=strlen(p);
          switch (tipotok) {
          case 2 :
          case 0 :if (strchr(p,'L'))  {
              *tipo=V10LONG;
              if (strchr(p,'U')) *tipo=V10ULONG;
                  } else {
                      if (tipotok==2) {
                          *tipo=V10BYTE;
                      } else {
                          if (strchr(p,'S')) {
                              *tipo=V10SHORT;
                              if (strchr(p,'U')) *tipo=V10USHORT;
                          } else {
                              *tipo=V10INT;
                              if (strchr(p,'U')) *tipo=V10UINT;
                          }
                      }
                  }
                  if (strchr(p,','))  *formato=v10formatdef|MARCAMILES; else *formato=v10formatdef;         
                  if (strchr(p,'H'))  *dec=16;    else *dec=10;
                  if (strchr(p,'P'))  {
                      if (password) *password=1;
                  } else {
                      if (password) *password=0;
                  }
                  {char *token=p;
                   while (*token) {
                         if (isdigit(*token)) {
                           token=lee_digito(token,lon)+1;
                         } else token++;
                   }
                  }
                  break;
          case 1 :interpretapf(p,tipo,formato,dec,lon,lpan,password);
              break;
          case 3 :interpretachar(p,tipo,formato,dec,lon,lpan,password);
              break;
          case 4 :*tipo=V10CHAR;
              break;
          case 5 :*tipo=V10FECHA;
              if (strchr(p,'.')) {
                  *formato=F4ANO;
                  if (strlen(p)<10) final(("Debe dejar sitio para formato con 4 digitios año"));
              }
              break;
          case 6 :*tipo=V10HORA;
              break;
          }
        if (donde) *donde=p;
        while (p<fintok) *p++=' ';
        *fintok=achar;
        p=fintok;
        break;
     }
     p++;
   }
  return(p);
}

static void interpretalinea(char *texto ,int numlin ,v10dialogs *vi)
{
  char *p;
  v10inputs *v=vi->act;
  p=texto;
  while (1) {
        char *donde;
        p=analizatokendia(p,&donde,&v->tipo,&v->formato,&v->dec,&v->lvar,&v->lpan,&v->password);
        if (v->lpan>=WANCHO(&vi->w)) v->lpan=WANCHO(&vi->w);
        if (v->tipo==-1) break;
        v->posx=(int)(donde-texto);
        v->posy=numlin;
        v->dato=0L;v->triger=NULL;v->enter=1;v->noinput=0;
        v->activa=v->seleccion=0;
        v->w=&vi->w;
        v++;
        if (v>=vi->prim+MAXVENTANA) final(("Demasiadas v10inputs en bloque"));
    }
  vi->act=v;
}

void interpretadialogo(v10dialogs *vi ,char *contenido)
{
  char *p2,*p3;
  tpixels *p1;
  int i;
  int tinta,papel;
  initbloque(vi);
  if ((vi->prim=vi->act=calloc(MAXVENTANA,sizeof(v10inputs)))==0L) final(("Sin memoria"));
  tinta=vi->w.t.t[0].tinta;
  papel=vi->w.t.t[0].papel;
  if ((p1=vi->contenido=(tpixels *)calloc((vi->largo)*(vi->alto),sizeof(tpixels)))==0L) final(("Sin memoria"));
  if (p1==0L) final(("Sin memoria"));
  p2=contenido;
  for (i=0;i<vi->alto;i++) {
      p3=p2;
      interpretalinea(p2,i,vi);
      while (*p3) {
          p1->ch=*p3++;
          p1->c.tinta=tinta;
          p1->c.papel=papel;
          p1++;
      }
      p2=p2+vi->largo+1;
   }
  if (vi->act>vi->prim) {
     int num=vi->act-vi->prim;
     vi->prim=realloc(vi->prim,num*sizeof(v10inputs));
     vi->ult=vi->prim+num-1;
     vi->numinput=num;
    } else {
     free(vi->prim);
     vi->prim=vi->ult=vi->act=vi->ultinp=NULL;
    }
  vi->act=vi->prim;vi->ultinp=vi->ult;
  vi->pantalla_debajo=NULL;
}
