#include "v10wwwform.h"

static char error_oracle[MAXERRORORACLE];

char textodefines[MAXCADENAHTML]="";
char textobinds[MAXCADENAHTML]="";
char textoselect[MAXCADENAHTML]="";
char textocursor[MAXCADENAHTML]="";
char textoclipboard[MAXCADENAHTML]="";
static char textocursores[MAXCADENAHTML]="";
int poscursor=0;
typedef struct {
         int fun;
         char *nombre;
        } orafuns;


static orafuns orafun[]={{1,"CREATE TABLE"},
                  {3,"INSERT"},
                  {4,"SELECT"},
                  {5,"UPDATE"},
                  {7,"DROP VIEW"},
                  {8,"DROP TABLE"},
                  {9,"DELETE"},
                  {10,"CREATE VIEW"},
                  {18,"CREATE CLUSTER"},
                  {20,"CREATE INDEX"},
                  {21,"DROP INDEX"},
                  {22,"DROP CLUSTER"},
                  {26,"ALTER TABLE"},
                  {28,"GRANT"},
                  {29,"REVOKE"},
                  {30,"CREATE SYNONYM"},
                  {31,"DROP SYNONYM"},
                  {35,"LOCK TABLE"},
                  {37,"RENAME"},
                  {38,"COMMENT"},
                  {39,"AUDIT"},
                  {40,"NOAUDIT"},
                  {41,"ALTER INDEX"},
                  {43,"CREATE DB LINK"},
                  {44,"DROP DB LINK"},
                  {45,"ALTER DATABASE"},
                  {46,"CREATE RB SEG."},
                  {47,"ALTER RB SEG."},
                  {48,"DROP RB SEG"},
                  {49,"CREATE TABLESPACE"},
                  {50,"ALTER TABLESPACE"},
                  {51,"DROP TABLESPACE"},
                  {52,"ALTER SESION"},
                  {53,"ALTER USER"},
                  {54,"COMMIT"},
                  {55,"ROLLBACK"},
                  {56,"SAVEPOINT"},
                  {-1,"FUNCION INDEFINIDA"}};

static orafuns ocifun[]={{2,"OSQL"},
                  {4,"OEXEN(N)"},
                  {6,"OBIND"},
                  {8,"ODEFIN(N)"},
                  {10,"ODSRBN"},
                  {12,"OFETCH(N)"},
                  {14,"OOPEN"},
                  {16,"OCLOSE"},
                  {22,"ODSC"},
                  {24,"ONAME"},
                  {26,"OSQL3"},
                  {28,"OBNDRV"},
                  {30,"OBNDRN"},
                  {32,"OOPT"},
                  {50,"OBIND"},
                  {52,"OCAN"},
                  {54,"OPARSE"},
                  {56,"OEXFET"},
                  {58,"OFLNG"},
                  {60,"ODESCR"},
                  {62,"OBNDRA"},
                  {64,"ODEFINPS"},
                  {65,"OGETPI"},
                  {66,"OSETPI"},
                  {-1,"Indefinida"}};




static char *buscafun(orafuns *f,int valor)
{
  while (f->fun!=-1&&f->fun!=valor) f++;
  return(f->nombre);
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
    return(strlen(donde));
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

void listadefines(v10cursors *c)
{
   char *ptr;
   int i;
   campooras *ca;  

   ptr=textodefines;
   *ptr=0;   
   if (c->ndef==0) return;
   strcat(ptr,"<table class=\"tbdebugdefines\" border=\"0\" cellspacing=\"0\" cellpadding=\"2\">");

   	strcat(ptr,"<thead><tr>"\
		"<th style=\"width:80px\">DATO</th>"\
		 "<th style=\"width:30px\">PREC</th>"\
		 "<th style=\"width:30px\">ESCALA</th>"\
		 "<th style=\"width:10px\">NULL</th>"\
		 "<th style=\"width:30px\">IND</th>"\
		 "<th style=\"width:38px\">ERROR</th>"\
		 "<th style=\"width:30px\">LON</th>"\
		 "<th style=\"width:40px\">TIPO</th>"\
		 "<th style=\"width:100px\">NOMBRE</th>"\
		"<th style=\"width:100px\">VALOR</th></tr></thead>");
   for (i=0;i<c->ndef;i++) {
	 ca=c->def+i;
	 sprintf(ptr+strlen(ptr),"<tr class=\"%s\">",(i%2==0)?"dpar":"dimpar");
	 sprintf(ptr+strlen(ptr),
		 "<td style=\"width:80px\">%p</td>"\
		 "<td style=\"width:30px\">%4d</td>"\
		 "<td style=\"width:30px\">%4d</td>"\
		 "<td style=\"width:10px\">%1d</td>"\
		 "<td style=\"width:30px\">%4d</td>"\
		 "<td style=\"width:38px\">%5d</td>"\
		 "<td style=\"width:30px\">%4d</td>"\
		 "<td style=\"width:40px\">%-6s</td>"\
		 "<td style=\"width:100px\">%-10.10s</td>",
			ca->dato,ca->prec,
            ca->scale,ca->nullok,ca->indicador,ca->error,
            ca->lon,dameoratipo(ca->tipo),ca->nombre);
		if (ca->dato)  {
			strcat(ptr,"<td style=\"width:100px\">");
			pasa_campo_ascii(ca,ptr+strlen(ptr),0);
			strcat(ptr,"</td>");
		} 
	 strcat(ptr,"</tr>");
   }
    strcat(ptr,"</table>");

}

void listabinds(v10cursors *c)
{
   char *ptr;
   campooras *ca;
   int i;
   ptr=textobinds;
   *ptr=0; 
   if (c->nbind==0) return;
   strcat(ptr,"<table class=\"tbdebugdefines\" border=\"0\" cellspacing=\"0\" cellpadding=\"2\">"); 

   strcat(ptr,"<thead><tr>"\
		"<th style=\"width:80px\">DATO</th>"\
		"<th style=\"width:30px\">LON</th>"\
		"<th style=\"width:40px\">TIPO</th>"\
		"<th style=\"width:100px\">NOMBRE</th>"\
		"<th style=\"width:100px\">VALOR</th></tr></thead>");

   for (i=0;i<c->nbind;i++) {
		ca=c->bind+i;
		sprintf(ptr+strlen(ptr),"<tr class=\"%s\">",(i%2==0)?"dpar":"dimpar");
		sprintf(ptr+strlen(ptr),
		   "<td style=\"width:80px\">%p</td>"\
		   "<td style=\"width:30px\">%4d</td>"\
		   "<td style=\"width:40px\">%-6s</td>"\
		   "<td style=\"width:100px\">%-10.10s</td>",
		   ca->dato,ca->lon,dameoratipo(ca->tipo),ca->nombre);
		if (ca->dato)  {
			strcat(ptr,"<td style=\"width:100px\">");
			pasa_campo_ascii(ca,ptr+strlen(ptr),0);
			strcat(ptr,"</td>");
		}
		strcat(ptr,"</tr>");
   }
   strcat(ptr,"</table>");
}

static int comparacursor(const void *a1,const void *a2)
{
    const v10cursors **c1=(void *)a1,**c2=(void *)a2;
    return(strcmp((*c1)->nombre,(*c2)->nombre));
}

static void v10wwwmenucursores(void) {
    v10cursors **ac,*ptrc;
	v10cursors *vc;
	int salir=0,ret,numcursor=0;
	char presdebug[MAXNOMBREV10],*ptr;
    int i;
    ptrc=damercursor(&numcursor);
    ac=calloc(numcursor,sizeof(v10cursors *));
    for (i=0;i<numcursor;i++) {
        ac[i]=ptrc;
        ptrc=ptrc->next;
    }
    qsort(ac,numcursor,sizeof(v10cursors *),comparacursor);	
	ptr=textocursores;
	*ptr=0;
	strcat(ptr,"<table id=\"tbcursores\"  onclick=\"fonclickmsj()\" class=\"v10tbcursores\" border=\"0\" cellspacing=\"0\" cellpadding=\"2\">"); 
    strcat(ptr,"<thead><tr>"\
		"<th style=\"width:240px\">CURSOR</th>"\
		"<th style=\"width:100px\">PRESDEBUG</th></tr></thead>");	
	for (i=0;i<numcursor;i++) {
		vc=ac[i];
		v10lformat(vc->debug,10,0,'0',presdebug,2);		
		sprintf(ptr+strlen(ptr),"<tr fila=%d class=\"%s\">",i+1,(i%2==0)?"dpar":"dimpar");
		sprintf(ptr+strlen(ptr),
		   "<td>%s</td>"\
		   "<td>%s</td></tr>",vc->nombre,presdebug);
	}
    strcat(ptr,"</table>");
	ret=v10wwwmensajecursores(ptr);
	if (ret==-1) salir=1;
	while (!salir) {
		vc=ac[ret];       
        switch (ult_pul) {
                 case '0':
                 case '1':
                 case '2':
                 case '3':
                 case '4':
                 case '5':
                 case '6':
                 case '7':
                 case '8':
                 case '9':vc->debug=vc->debug^(1<<(ult_pul-'0'));
                     ult_pul=0;
                     salir=1;
                     break;
                 case 'd':
                 case 'D':cursordebug(vc);
                     break;
                 default: salir=1;
                     break;
        }
    }
	free(ac);
}


void infoselect(v10cursors *c)
{
  char *perror,*ptrdest,*ptrsql;
  int ancho=115,index=0,salir=0,len,off;
  
  ptrdest=textoselect;  
  *ptrdest=0;
  ptrsql=c->sql;
  do {
	  len=strlen(ptrsql);
	  if (len > ancho) off=ancho;
	  else { 
		  off=len; 
		  salir=1; 
	  }
	  if (c->parseerror && c->parseerror >= index && c->parseerror <= index + off) {
		perror=ptrsql+(c->parseerror-index);
		strcopia(ptrdest,ptrsql,(int)(perror-ptrsql));	
		sprintf(ptrdest+strlen(ptrdest),"<font\nclass=\"v10debugerror\">%c</font>",*perror);
		if (((index + off) - c->parseerror) - 1>0) strcopia(ptrdest + strlen(ptrdest), perror + 1, ((index + off) - c->parseerror) - 1);
		} else {
		  strcopia ( ptrdest, ptrsql, off);
		  strcat(ptrdest,"</br>");
	  }
	  if (salir) break;	 
	  ptrsql = ptrsql + off;
	  index += off;
	  ptrdest = ptrdest + strlen(ptrdest);
  }while (salir==0);
  v10carespeciales(ptrdest,32,"&nbsp");
}


void infocursor(v10cursors *cur)
{
  int funoci;
  char nombrefunoci[MAXPATH],nombrefunora[MAXPATH];
  char fichero[MAXPATH],funcion[MAXPATH],*ptr;
  
  ptr=textocursor;
  *ptr=0;

  funoci=cur->funoci;
  strcpy(fichero,cur->file);
  strcpy(funcion,cur->funcion);
  if (cur->errcode) getcurerror(cur,error_oracle);
  else strcpy(error_oracle,"");
  strcpy(nombrefunora,buscafun(orafun,cur->funsql));
  strcpy(nombrefunoci,buscafun(ocifun,cur->funoci));
  sprintf(ptr+strlen(ptr),
	        "</br>Cursor:  %s"\
			"</br>Fichero: %-30.30s   Linea: %d"\
			"</br>Funcion: %-30.30s   OCI: %3d %-30.30s  OCI: %4d %-30.30s"\
			"</br>Error:   %5d   Filas procesadas %d"\
			"</br>%s</br>"\
			"</br>Ejec. %05d %05lf sg. Fetch %05d %05lf sg. Ejefetch %05d %05lf sg."\
			"</br>Ultima ej  %05lf                %05lf                   %05lf",
	  cur->nombre,fichero,cur->line,funcion,cur->funsql,nombrefunora,funoci,nombrefunoci,cur->errcode,cur->filasprocesadas,
	  error_oracle,cur->ejecuciones,cur->texec,cur->numfetch,cur->tfetch,
      cur->numejefetch,cur->tejefetch,cur->totexec,cur->totfetch,cur->totejefetch);
  v10carespeciales(ptr,32,"&nbsp");
}


static void varsclipboard(v10cursors *c)
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
			  if (ca->dato==NULL) strcpy(buffer,"");
                  else            pasa_campo_ascii(ca,buffer,1);
			  strins(aux,buffer);
		}
	}
	sprintf(textoclipboard,"<script>miselect=\"%s\";\nmiselectbind=\"%s\";</script>",c->sql,sql);
}
// con tab o ret, va cambiando de ventana => señalar ventana activa de alguna manera !!
void v10wwwcursordebug(v10cursors *c)
{
	int salir=0,ret=0;
	char online[MAXCADENA]="";
	unsigned timeout;
	void *triger_timeout,*trigervivo;
	dametimeoutteclado(&timeout,&triger_timeout);
	trigervivo=dametrigervivo();
	pontrigervivo(NULL);
	timeoutteclado(0,NULL);  
	infocursor(c);
	infoselect(c);  
	listadefines(c);
	listabinds(c);
	varsclipboard(c);
	
	while (!salir) {       
		ret=v10wwwmensajedebug("",online);
		switch (ret) {
			case C_F(10):invocaeditor(c->file,NULL);
			break;
			case 'm':
			case 'M': v10wwwmenucursores();
					break;
			case esc:salir=-1;
				     break;
			 case A_F(10):final(("Programa abortado por usuario"));
		}
	}
	timeoutteclado(timeout,triger_timeout);
	pontrigervivo(trigervivo);
}

// solo muestra un recuadro, y espera que pulse una tecla;
// lo encola como mensaje normal
void v10wwwldadebug(void *param,int funcion)
{
	char mimensaje[MAXCADENA]="",titulo[MAXCADENA]="Debug ORACLE nivel LDA";  
	strcat(mimensaje,"</ BR> Funcion oracle %s");
	sprintf(mimensaje+strlen(mimensaje),"<p class=\"v10ldadebug\">%3d %s</p>",funcion,buscafun(orafun,funcion));
	strcat(mimensaje,"</ BR> Funcion OCI ");
	sprintf(mimensaje+strlen(mimensaje),"<p class=\"v10ldadebug\">%3d %s</p></ BR>",funcion,buscafun(orafun,funcion));
	v10wwwmensajegen(titulo,mimensaje);
}   