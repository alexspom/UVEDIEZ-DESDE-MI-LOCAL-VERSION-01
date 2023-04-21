/*
* Módulo : V10CADENAS.C
* Objeto:  Manejo estandarizado de cadenas de caracteres
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"

#define NUMCAR 256
static char mayusculas[NUMCAR] =    {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
                         10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
                         20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
                         30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
                         40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
                         50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
                         60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
                         70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
                         80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
                         90, 91, 92, 93, 94, 95, 96,'A','B','C',
                         'D','E','F','G','H','I','J','K','L','M',
                         'N','O','P','Q','R','S','T','U','V','W',
                         'X','Y','Z',123,124,125,126,127,128,'',
                         '','A','','A',134,'','E','E','E','I',
                         'I','I',142,143,144,145,146,'O','','O',
                         'U','U',152,153,154,155,156,157,158,159,
                         'A','I','O','U','Ñ',165,166,167,168,169,
                         170,171,172,173,174,175,176,177,178,179,
                         180,181,182,183,184,185,186,187,188,189,
                         190,191,192,193,194,195,196,197,198,199,
                         200,201,202,203,204,205,206,207,208,209,
                         210,211,212,213,214,215,216,217,218,219,
                         220,221,222,223,224,225,226,227,228,229,
                         230,231,232,233,234,235,236,237,238,239,
                         240,209,242,243,244,245,246,247,248,249,
                         250,251,252,253,254,255};

static char minusculas[NUMCAR] =    {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
                                10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
                                20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
                                30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
                                40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
                                50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
                                60, 61, 62, 63, 64,'a','b','c','d','e',
                                'f','g','h','i','j','k','l','m','n','o',
                                'p','q','r','s','t','u','v','w','x','y',
                                'z', 91, 92, 93, 94, 95, 96, 97, 98, 99,
                                100,101,102,103,104,105,106,107,108,109,
                                110,111,112,113,114,115,116,117,118,119,
                                120,121,122,123,124,125,126,127,'',129,
                                130,131,132,133,134,135,136,137,138,139,
                                140,141,'',143,'',145,146,147,148,149,
                                150,151,152,'','',155,156,157,158,159,
                                160,161,162,163,164,'ñ',166,167,168,169,
                                170,171,172,173,174,175,176,177,178,179,
                                180,181,182,183,184,185,186,187,188,189,
                                190,191,192,193,194,195,196,197,198,199,
                                200,201,202,203,204,205,206,207,208,241,
                                210,211,212,213,214,215,216,217,218,219,
                                220,221,222,223,224,225,226,227,228,229,
                                230,231,232,233,234,235,236,237,238,239,
                                240,241,242,243,244,245,246,247,248,249,
                                250,251,252,253,254,255};


char pasacarmay(int ch)
{
    return(mayusculas[ch]);
}

char pasacarmin(int ch)
{
    return(minusculas[ch]);
}

char *strfill(char *cadena,char ch,unsigned leng)
{
  memset(cadena,(int)ch,leng);
  cadena[leng]=0;
  return(cadena);
}

char *trunca(char *cadena,unsigned leng)
{
  if (strlen(cadena)>leng) cadena[leng]='\0';
  return(cadena);
}


char *padcar(char *cadena,unsigned leng,char ch)
{
  if (leng<strlen(cadena)) trunca(cadena,leng);
  else {
    memset(cadena+strlen(cadena),ch,leng-strlen(cadena));
    cadena[leng]='\0';
  }
  return(cadena);
}

char *pad(char *cadena,unsigned leng)
{
	return(padcar(cadena,leng,' '));
}


char *lpadcar(char *cadena,unsigned leng,char ch)
{
  unsigned i;

  if (leng<strlen(cadena)) trunca(cadena,leng);
  else {
    int longitud = strlen(cadena);

    memmove(cadena+leng-longitud,cadena,longitud+1);
    for(i=0 ; i < (leng-longitud) ; i++) cadena[i]=ch;
  }
  return(cadena);
}

char *lpad(char *cadena,unsigned len)
{
	return(lpadcar(cadena,len,' '));
}


char *centra(char *cadena,unsigned leng)
{
   lpad(cadena,(leng+strlen(cadena))/2);
   pad(cadena,leng);
   return(cadena);
}


char *trim(char *cadena)
{
	int i;
	for (i=strlen(cadena)-1;i>=0;i--) {
        if (cadena[i]!=' ' && cadena[i]!='\t') return(cadena);
		cadena[i]=0;
	}
    return(cadena);
}


char *ltrim(char *cadena)
{
  char *ret = cadena;

  while(*cadena==' ' || *cadena=='\t')
    cadena++;
  strcpy(ret,cadena);
  return(ret);
}


char *eliminasp(char *cadena)
{
  return(ltrim(trim(cadena)));
}



char *strinserta(char *cadena,unsigned desde,unsigned leng)
{
  if (desde<strlen(cadena)) {
     memmove(cadena+desde+leng,cadena+desde,strlen(cadena)-desde-leng);
     memset(cadena+desde,' ',leng);
   }
  return(cadena);
}


char *strins(char *destino,char *fuente)
{
  if (*fuente) {
     memmove(destino+strlen(fuente),destino,strlen(destino)+1);
     memmove(destino,fuente,strlen(fuente));
  }
  return(destino);
}


char *strdel(char *cadena,unsigned desde,unsigned leng)
{
  char *inicio=cadena+desde;
  char *final=cadena+desde+leng;

  while (*final) *inicio++=*final++;
  while (inicio<final) *inicio++=' ';
  return(cadena);
}


char *strerase(char *cadena,unsigned desde,unsigned leng)
{
    unsigned lon=strlen(cadena);
    if (desde<lon) {
        if ((desde+leng)>lon)
      trunca(cadena,desde);
    else
      strcpy(cadena+desde,cadena+desde+leng);
    }
  return(cadena);
}


char *strcopia(char *destino,char *fuente,size_t leng)
{
  if (leng>0) strncpy(destino,fuente,leng);
  destino[leng]='\0';
  return(destino);
}


char *irfin(char *cadena)
{
  char *aux = cadena;

  while (*cadena) {
    if (*cadena!=' ' && *cadena!='\t') aux=cadena+1;
    cadena++;
  }
  return(aux);
}


char *sigpal(char *posact)
{
  while ((*posact != ' ') && (*posact))
    posact++;
  while (*posact==' ')
    posact++;
  return(posact);
}


char *antpal(char *inicio,char *posact)
{
  if ((posact>inicio) && (posact<=inicio+strlen(inicio))) {
    posact--;
    while (posact>inicio && (*posact==' ' || *posact=='\t'))
      posact--;
    while (posact>inicio && *posact!=' ' && *posact!='\t')
      posact--;
    if (*posact==' ' || *posact=='\t')
      posact++;
    return(posact);
  }
  else return(inicio);
}


char *strmay(char *cadena)
{
  char *retorno = cadena;

  while (*cadena) {
    *cadena=mayusculas[*cadena];
    cadena++;
  }
  return(retorno);
}


char *strmin(char *cadena)
{
  char *retorno = cadena;

  while (*cadena) {
    *cadena=minusculas[*cadena];
    cadena++;
  }
  return(retorno);
}


int stricomp(char *destino,char *fuente)
{
  while (*destino && mayusculas[*destino]==mayusculas[*fuente]) {
    destino++;
    fuente++;
  }
  if (mayusculas[*destino] == mayusculas[*fuente]) return(0);
  if (mayusculas[*destino] <  mayusculas[*fuente]) return(-1);
  return(1);
}


int strnicomp(char *destino,char *fuente,unsigned leng)
{
  int i=0;

  while (*destino && mayusculas[*destino]==mayusculas[*fuente] && i!=leng) {
    destino++;
    fuente++;
    i++;
  }
  if ((i==leng) || (mayusculas[*destino] == mayusculas[*fuente])) return(0);
  if (mayusculas[*destino] <  mayusculas[*fuente]) return(-1);
  return(1);
}

int es_blanco(char *cadena)
{
  if (cadena==NULL) return(1);
  while (*cadena)
    if (*cadena++!=' ')
      return(0);
  return(1);
}

int piece(char *buffer,char *donde,char *sep,int parte)
{
	char *pbuff , *presult;
    unsigned int n  , len ;
    if (parte < 1 || !buffer || !donde || !sep) return (-1);
	*donde=0 ;
    n=0;
    len=strlen(sep) ;
    presult=(char *) buffer - len ;
    do {
      pbuff = presult + len   ;
      presult = strstr(pbuff,sep) ;
    } while (( ++n < parte)  && presult) ;
    if ( n != parte ) return (-1);
    len =  (presult) ? (presult- pbuff) : strlen(pbuff) ;
    memcpy(donde,pbuff,len) ;
    donde[len] = 0 ;
	return (len) ;
}

int numpieces(char *buffer,char *sep )
{
    char *buf=buffer , *res ;
    unsigned int n ,len=strlen(sep)  ;
    if ( !sep || !buffer ) return (0);
	for (n=1;(res=strstr(buf,sep))!=NULL;buf=res+len,n++);
    return (n) ;
}

int damenumeropieza(char *cadena,char *pieza,char *separador)
{
    char buff[MAXCADENA];
    int n,ret;
    if (strstr(cadena,pieza)==NULL) return(-1);
    for (n=1,ret=piece(cadena,buff,separador,n);ret>-1;n++,ret=piece(cadena,buff,separador,n)){
        if (!strcmp(buff,pieza)) return(n);
    }
    return(-1);    
}

int contieneex(char *cadenain,char *comparar,char *separador,char *seprango,int admitenulo)
{
    char *aux,*sig,*orig,*hasta;
    int ret=0;
    if (es_blanco(cadenain) && admitenulo) return(1);
    orig=aux=strdup(cadenain);
    while (1) {
          sig=strstr(aux,separador);
          if (sig) *sig=0;
          if (strcmp(aux,comparar)==0) {
              ret=1;
              break;
          }
          hasta=strstr(aux,seprango);
          if (hasta) {
              *hasta=0;
              if (strcmp(aux,comparar)<=0 && strcmp(hasta+strlen(seprango),comparar)>=0) {
                  ret=1;
                  break;
              }
          }
          if (sig) aux=sig+strlen(separador);
             else  break;
    }
    free(orig);
    return(ret);
}

int contiene(char *cadenain,char *comparar)
{
    return(contieneex(cadenain,comparar,",","-",1));
}

static int esnumerico(char *cadena)
{
    while (*cadena) {
        if (isdigit(*cadena) || *cadena=='.') cadena++;
           else return(0);
    }
    return(1);
}

int contienenumex(char *cadenain,double comparar,char *separador,char *seprango,int admitenulo)
{
    char *aux,*sig,*orig,*hasta;
    int ret=0;
    if (es_blanco(cadenain) && admitenulo) return(1);
    orig=aux=strdup(cadenain);
    while (1) {
          sig=strstr(aux,separador);
          if (sig) *sig=0;
          if (esnumerico(aux)) {
             if (atof(aux)==comparar) {
                 ret=1;
                 break;
             }
          }
          hasta=strstr(aux,seprango);
          if (hasta) {
              *hasta=0;
              if (esnumerico(aux) && esnumerico(hasta+strlen(seprango))) {
                 if (atof(aux)<=comparar && atof(hasta+strlen(seprango))>=comparar) {
                    ret=1;
                    break;
                 }
              }
          }
          if (sig) aux=sig+strlen(separador);
             else  break;
    }
    free(orig);
    return(ret);
}

int contienenum(char *cadenain,double comparar)
{
    return(contienenumex(cadenain,comparar,",","-",1));
}

