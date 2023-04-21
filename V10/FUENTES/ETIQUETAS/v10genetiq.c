#include "v10etiqueta.h"

static char traduceimp(char ch)
{
  	char c1[2],c2[2];
	switch (ch) {
        	case 'á':ch='a';break;
        	case 'Á':ch='A';break;
        	case 'é':ch='e';break;
        	case 'É':ch='E';break;
        	case 'í':ch='i';break;
        	case 'Í':ch='I';break;
        	case 'ó':ch='o';break;
        	case 'Ó':ch='O';break;
        	case 'ú':ch='u';break;
        	case 'Ú':ch='u';break;
        	case 'ü':ch='u';break;
        	case 'Ü':ch='u';break;
			case '°':ch='.'; break;
			case 'º':ch = '.'; break;
    		case 'ñ':
        	case 'Ñ':
        	case 'ç':
            case 'Ç':
       			c1[1]=c2[1]=0;
      			*c1=ch;
            	v10ansitooem(c1,c2);
            	ch=*c2;
				break;
			default:
        		break;
		}
    return(ch);
}

static void transformabuffer(char *buffer)
{
  char *ptr=buffer;
  while (*ptr) {
      if (*ptr=='\\') {
         char car=ptr[1];
         switch (car) {
           case '\\':*ptr='\\';
                    strcpy(ptr+1,ptr+2);
                    break;
           case 'r':*ptr='\r';
                    strcpy(ptr+1,ptr+2);
                    break;
           case 'n':*ptr='\n';
                    strcpy(ptr+1,ptr+2);
                    break;
           case '0':
           case '1':
           case '2':
           case '3':*ptr=(char)((car-'0')*64+(ptr[2]-'0')*8+ptr[3]-'0');
                    strcpy(ptr+1,ptr+4);
                    break;
         }
      }
     ptr++;
   }
}

static void buscacampo(idatos *idato,char **ptr,int *campo,int linea)
{
  char ncampo[MAXNOMBREV10],*aux=ncampo;
  int i;
  while (**ptr!='-' && **ptr!='%') {
        if (**ptr==0) final(("Formato erroneo en linea %d",linea));
        *aux++=**ptr;
        (*ptr)++;
     }
  if (**ptr=='-') (*ptr)++;
  *aux=0;
  for (i=0;;i++) {
      if (es_blanco(idato[i].nombre)) break;
      if (strcmp(idato[i].nombre,ncampo)==0) {
         *campo=i;
         break;
       }
    }
}

static void preparasalida(idatos *idato,int linea,char *buffer,char *cadorden,char *bsalid)
{
  char *ptr=buffer,*ptrsal=bsalid;
  int  campo;
  while (*ptr) {
      if (*ptr=='%') {
         int desde=0,hasta=0;
         int inte=0;
         int ascii=0;
         int haztrim=1;
         campo=-1;
         ptr++;
         if (*ptr=='%') {
            *ptrsal++=*ptr;
            ptr++;
            continue;
          }
         if (toupper(*ptr)=='I') {
            if (*ptr=='I') inte=1;
               else        inte=2;
            ptr++;
          }
         if (toupper(*ptr)=='C') {
            ascii=1;
            ptr++;
          }
         if (toupper(*ptr)=='T') {
            haztrim=1;
            ptr++;
          }
         if (*ptr=='_') {
            ptr++;
            buscacampo(idato,&ptr,&campo,linea);
          }
         while (*ptr!='-' && *ptr!='%') {
               if (!isdigit(*ptr)) {
                  final(("Formato erroneo en linea %d",linea));
                }
               desde=desde*10+(*ptr-'0');
               ptr++;
             }
         if (desde) desde--;
         if (*ptr=='-') ptr++;
         while (*ptr!='%') {
               if (!isdigit(*ptr)) {
                  final(("Formato erroneo en linea %d",linea));
                }
               hasta=hasta*10+(*ptr-'0');
               ptr++;
            }
         if (campo!=-1) {
            desde+=idato[campo].inicio-1;
            if (hasta==0) hasta=idato[campo].lon;
          }
         strcopia(ptrsal,cadorden+desde,hasta);
         if (inte) {
            char *aux=ptrsal;
            while ((*aux=='0' ||*aux==' ') && *aux) aux++;
            if ((*aux==0 || *aux==' ' || *aux=='.' || *aux==',') && aux>ptrsal) *--aux='0';
            strcpy(ptrsal,aux);
            if (inte==1) {
               lpad(ptrsal,hasta);
             }
          }
         if (ascii==1) {
            long valor;
            valor=atol(ptrsal);
            sprintf(ptrsal,"%c",valor);
          }
         if (haztrim==1) {
            trim(ptrsal);
          }
         ptrsal+=strlen(ptrsal);
       } else {
         *ptrsal++=*ptr;
       }
     ptr++;
   }
  *ptrsal=0;
}

void analizadh(int linea,char *prin,char *fin,int *desde,int *hasta)
{
  char *ch;
  ch=strchr(prin,'-');
  if (ch==NULL || ch>fin) final(("Cadena $ incorrecta en linea %d\n",linea));
  *desde=atoi(prin);
  *hasta=atoi(ch+1);
}

void analiza4(int linea,char **prin,char *fin,int *p1,int *p2,int *p3,int *p4)
{
  char *ch;
  ch=strchr(*prin,'-');
  if (ch==NULL || ch>fin) final(("Cadena $ incorrecta en linea %d\n",linea));
  *p1=atoi(*prin);
  *prin=ch+1;
  ch=strchr(*prin,'-');
  if (ch==NULL || ch>fin) final(("Cadena $ incorrecta en linea %d\n",linea));
  *p2=atoi(*prin);
  *prin=ch+1;
  ch=strchr(*prin,'-');
  if (ch==NULL || ch>fin) final(("Cadena $ incorrecta en linea %d\n",linea));
  *p3=atoi(*prin);
  *prin=ch+1;
  *p4=atoi(*prin);
  ch=strchr(*prin,'-');
  if (ch==NULL) ch=*prin+strlen(*prin)-1;
  *prin=ch+1;
}

void analiza4y1(int linea,char **prin,char *fin,int *p1,int *p2,int *p3,int *p4,char *p5)
{
  char *ch;
  ch=strchr(*prin,'-');
  if (ch==NULL || ch>fin) final(("Cadena $ incorrecta en linea %d\n",linea));
  *p1=atoi(*prin);
  *prin=ch+1;
  ch=strchr(*prin,'-');
  if (ch==NULL || ch>fin) final(("Cadena $ incorrecta en linea %d\n",linea));
  *p2=atoi(*prin);
  *prin=ch+1;
  ch=strchr(*prin,'-');
  if (ch==NULL || ch>fin) final(("Cadena $ incorrecta en linea %d\n",linea));
  *p3=atoi(*prin);
  *prin=ch+1;
  ch=strchr(*prin,'-');
  if (ch==NULL || ch>fin) final(("Cadena $ incorrecta en linea %d\n",linea));
  *p4=atoi(*prin);
  *prin=ch+1;
  for (ch=*prin;ch<=fin;ch++) {
      if (*ch=='$') *ch=0;
  }
  strcpy(p5,*prin);
}

static char *preparadriver(idrivers *id,int linea,char *buffer,char *bsalid)
{
  char *ptr=buffer,*ptrsal=bsalid,*fin,*prin;
  while (*ptr) {
      *ptr=traduceimp(*ptr);
      if (*ptr=='$') {
         ptr++;
         if (*ptr=='$') {
            *ptrsal++=*ptr;
            ptr++;
            continue;
          }
         prin=ptr;
         while (*ptr!='$' || ptr[1]=='$') {
			   if (*ptr=='$') strcpy(ptr,ptr+1);
               if (*ptr==0) final(("Secuencia $ sin terminar en linea %d",linea));
               *ptr=traduceimp(*ptr);
               ptr++;
            }
         fin=ptr;
         switch (toupper(*prin)) {
           case 'X':analizadh(linea,prin+1,fin,&id->tx,&id->ty);
			        if (id->asignatametiq) id->asignatametiq(id,&ptrsal);
                    break;
           case 'E':analizadh(linea,prin+1,fin,&id->ex,&id->ey);
                    if (id->cambiamaxetiq) id->cambiamaxetiq(id,&ptrsal,id->ex,id->ey);
                    break;
           case 'P':analizadh(linea,prin+1,fin,&id->px,&id->py);
                    break;
           case 'T':analizadh(linea,prin+1,fin,&id->fx,&id->fy);
                    break;
           case 'F':id->font=atoi(prin+1);
                    break;
           case 'J':id->color=*(prin+1);
			        break;
           case 'D':id->angulo=atoi(prin+1);
                    break;
           case 'B':prin++;
                    analiza4(linea,&prin,fin,&id->tipocb,&id->ancb,&id->alcb,&id->ratiocb);
                    if (id->imprimebarras) id->imprimebarras(id,prin,fin,&ptrsal);
                    break;
           case 'G':{int px, py, tx, ty;
                    char nombre[MAXPATH];
                    prin++;
                    analiza4y1(linea, &prin, fin, &px, &py, &tx, &ty, (void *)&nombre);
                    if (id->imprimelogo) id->imprimelogo(id,&ptrsal, px, py, tx, ty, (void *)&nombre);
                    break;
                    }
           case 'L':{int lx,ly,ancho,tipo;
                    prin++;
                    analiza4(linea,&prin,fin,&lx,&ly,&ancho,&tipo);
                    if (id->imprimelinea) id->imprimelinea(id,&ptrsal,lx,ly,ancho,tipo);
                    break;
                    }
		   case 'I':if (prin + 1 >= fin) break;
			        if (id->imprimecadena) id->imprimecadena(id, prin + 1, fin, ptrsal);
                    ptrsal+=strlen(ptrsal);
                    break;
		   case 'K':if (prin + 1 >= fin) break;
					if (id->imprimecadenainv) id->imprimecadenainv(id, prin + 1, fin, ptrsal);
					ptrsal += strlen(ptrsal);
					break;
           case 'A':if (id->tiraetiq) id->tiraetiq(id,&ptrsal);
                    break;
           case 'C':if (id->initetiq) id->initetiq(id,&ptrsal);
                    break;
          }
       } else {
         *ptrsal++=*ptr;
       }
     ptr++;
   }
  *ptrsal=0;
  return(ptrsal);
}

static char *llrealizaimpresionetiq(idatos *idato,idrivers *id,char *datosetiq,char *nfile,char *salida)
{
  FILE *entrada;
  char *buffer,*bsalid,*fin,*ptrsalida=salida;
  int linea=0;
  entrada=fopenseguro(nfile,"r");
  buffer=calloc(1,20*MAXCADENA);
  bsalid=calloc(1,20*MAXCADENA);
  while (fgetss(buffer,MAXCADENA-1,entrada)) {
        linea++;
		eliminasp(buffer);
        if (*buffer=='#') continue;
        if (*buffer=='@') {
          ptrsalida=llrealizaimpresionetiq(idato,id,datosetiq,buffer+1,ptrsalida);
          continue;
        }
        transformabuffer(buffer);
        preparasalida(idato,linea,buffer,datosetiq,bsalid);
        fin=preparadriver(id,linea,bsalid,buffer);
        memcpy(ptrsalida,buffer,fin-buffer);
        ptrsalida+=fin-buffer;
   }
  free(buffer);
  free(bsalid);
  fclose(entrada);
  return(ptrsalida);
}

char *realizaimpresionetiq(idatos *idato,idrivers *id,char *datosetiq,char *nfile,int *lon)
{
    char *ret=calloc(1,20*MAXCADENA),*fin;
    fin=llrealizaimpresionetiq(idato,id,datosetiq,nfile,ret);
    if (lon) *lon=(int)(fin-ret);
    return(ret);
}

