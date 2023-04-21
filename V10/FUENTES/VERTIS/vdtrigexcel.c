#include "vdform.h"

int fsql2excel(bloques *b,ftrigers *ft)
{
	char select[MAXSQL];
	char destino[MAXPATH];
	int salir;
	int sobreescribir;
	int ret;
	char plantilla[MAXCADENA];
	dameparametro(b,ft,0,V10CADENA,select);
	dameparametro(b,ft,1,V10CADENA,destino);
	dameparametro(b,ft,2,V10LONG,&salir);
	dameparametro(b,ft,3,V10LONG,&sobreescribir);
	dameparametro(b,ft,4,V10CADENA,plantilla);
	if (sobreescribir==1 && !es_blanco(destino)) unlink(destino);
	ret=bloqsql2excel(b,select,plantilla,destino,salir);
	return(ret);
}

static int formateanatural(char *donde,double numero)
{
    char *ptr;
    v10dformat(numero,30,60,v10formatdef,' ',donde);
    ltrim(donde);
    ptr=donde+strlen(donde)-1;
    while ((ptr>donde) && (*ptr!=',') && (*ptr=='0')) {
      ptr--;
    }
    if ((ptr==donde) || (*ptr==',')) *ptr='\0';
    else *(ptr+1)='\0';
    return((int)strlen(donde));
}

static char *pasa_campo_ascii(campooras *c,char *buffer,int comillas)
{
  switch (c->tipo) {
    case V10INT   :formateanatural(buffer,*(int *)c->dato);
                break;                     
    case V10UINT   :formateanatural(buffer,(double)*(unsigned int *)c->dato);
                break; 
    case V10SHORT:formateanatural(buffer,*(short *)c->dato);
                break; 
    case V10USHORT:formateanatural(buffer,(long)*(short *)c->dato);
                break;
    case V10LONG:formateanatural(buffer,*(long *)c->dato);
                break;                      
    case V10ULONG   :formateanatural(buffer,*(unsigned long *)c->dato);
                break;    
    case V10DOUBLE:formateanatural(buffer,*(double *)c->dato);
                break;
    case V10FLOAT :formateanatural(buffer,*(float *)c->dato);
                break;
    case V10BYTE   :formateanatural(buffer,(int)*(char *)c->dato);
                break;
    case V10CHAR  :if (comillas) sprintf(buffer,"'%c'",*(char *)c->dato);
		              else       sprintf(buffer,"%c",*(char *)c->dato);
                break;
    case V10CADENA: if (comillas) sprintf(buffer,"'%s'",(char *)c->dato);
		               else       strcopia(buffer,c->dato,100);
                break;
    case V10FECHA :jul2a(*(v10dates *)c->dato,"DD-MM-Y.",buffer);
		           if (comillas) {
                      strins(buffer,"TO_CHAR(TO_DATE('"); 
					  strcat(buffer,"','DD-MM-YYYY'),'J')");
				   }
                   break;
    case V10HORA  :
                cent2a(*(v10horas *)c->dato,0,':',buffer);
                break;
    case OCIROWID:strcpy(buffer,"");
                  break;
    default:    v10tipo2a(c->dato,c->tipo,0,0,0,buffer,1);
                break;
   }
  return(buffer);
}

static void sustituyebinds(v10cursors *c,char *destino)
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
			  strerase(aux,0,(int)strlen(nombrebind));
			  pasa_campo_ascii(ca,buffer,1);
			  strins(aux,buffer);
		}
	}
   strcpy(destino,sql);
}

int fpan2excel(bloques *b,ftrigers *ft)
{
	char sqlpan[MAXSQL];
	char select[MAXSQL],sql[MAXSQL];
	char destino[MAXPATH];
	int salir;
	int sobreescribir;
	int ret;
	char plantilla[MAXCADENA]="";
	dameparametro(b,ft,0,V10CADENA,select);
	dameparametro(b,ft,1,V10CADENA,destino);
	dameparametro(b,ft,2,V10LONG,&salir);
	dameparametro(b,ft,3,V10LONG,&sobreescribir);
	dameparametro(b,ft,4,V10CADENA,plantilla);
	sustituyebinds(b->select,sqlpan);
	sprintf(sql,"%s FROM (%s)",select,sqlpan);
	if (sobreescribir==1 && !es_blanco(destino)) unlink(destino);
	ret=bloqsql2excel(b,sql,plantilla,destino,salir);
	return(ret);
}

void inittrigexcel(void)
{
	declaratriger("FSQL2EXCEL",fsql2excel,NULL);
	declaratriger("FPAN2EXCEL",fpan2excel,NULL);
}