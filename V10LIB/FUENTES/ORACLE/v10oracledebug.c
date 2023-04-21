/*
* Módulo : V10ORADEBUG.C                                             
* Objeto:  Debugger de ORACLE
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10db.h"

int (*handleoraerr)(int coderr,v10cursors *c)=NULL;

static char error_oracle[MAXERRORORACLE];

static int despdef=25;
static int despbind=14;
static int despsel=0;
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



static char *ntipo[]={"INT","UINT","SHORT","USHORT","LONG","ULONG","FLOAT","DOUBLE","CHAR","BYTE","CADENA","FECHA","ENUM","HORA","DATE",
                      "RAW","","","","","","","","","OCIROW"};

char *dameoratipo(int tipo)
{
    return(ntipo[tipo]);
}

int oradebug=0;

void toggleoradebug(int dummy)
{
    if (oradebug) oradebug=0;
       else       oradebug=DEPURAPRELOG|DEPURALOG|DEPURAPARSE|DEPURAEXEC|DEPURAFETCH;
}

static char *buscafun(orafuns *f,int valor)
{
  while (f->fun!=-1&&f->fun!=valor) f++;
  return(f->nombre);
}

void  errlda(void)
{
   getlastdberror(error_oracle);
   trunca(error_oracle,50);
   final(("LDA error %s",error_oracle));
}

char *direc_define(v10cursors *c,int indice)
{
   static char buffer[MAXCADENA];
   int i;
   campooras *ca;
   if (indice==-1) return("Campos de select");
   if (indice>=c->ndef) return(NULL);
   ca=c->def+indice;
   sprintf(buffer,"%p %04d %04d %01d %4d %5d %4d %-6s %-10.10s ",ca->dato,ca->prec,
                  ca->scale,ca->nullok,ca->indicador,ca->error,
                  ca->lon,dameoratipo(ca->tipo),ca->nombre);
   if (ca->dato) pasaoracampo2ascii(ca,buffer+strlen(buffer),0,1);
   for (i=0;i<despdef;i++) if (buffer[i]==0) break;
   return(buffer+i);
}

char *direc_bind(v10cursors *c,int indice)
{
   static char buffer[MAXCADENA];
   int i;
   campooras *ca;
   if (indice==-1) return("Campos de bind");
   if (indice>=c->nbind) return(NULL);
   ca=c->bind+indice;
   sprintf(buffer,"%p %4d %-6s %-10.10s ",ca->dato,ca->lon,dameoratipo(ca->tipo),ca->nombre);
   if (ca->dato) pasaoracampo2ascii(ca,buffer+strlen(buffer),0,1);
   for (i=0;i<despbind;i++) if (buffer[i]==0) break;
   return(buffer+i);
}

static int tecla_debugdef(virtsels *s)
{
  int ret;
  ret=tecla();
  switch (ret) {
         case cui:if (despdef) despdef--;
                  ret=0;
                  break;
         case cud:despdef++;
                  ret=0;
                  break;
      }
  return(ret);
}                        
static int tecla_debugbind(virtsels *s)
{
  int ret;
  ret=tecla();
  switch (ret) {
         case cui:if (despbind) despbind--;
                  ret=0;
                  break;
         case cud:despbind++;
                  ret=0;
                  break;
      }
  return(ret);
}

void presentaselect(v10cursors *c,windows *w)
{
  char ant,antuletra;
  char *pletra,*perror=c->sql+strlen(c->sql),*uletra;
  pletra=c->sql+despsel*WANCHO(w);
  if (strlen(pletra)>WANCHO(w)*WALTO(w)) uletra=pletra+WANCHO(w)*WALTO(w);
     else                                uletra=pletra+strlen(pletra);
  antuletra=*uletra;
  *uletra=0;
  clv(w);
  if (c->parseerror) {
     perror=c->sql+c->parseerror;
     ant=*perror;
     *perror=0;
   }
  if (pletra<perror) v10printf(w,"%s",pletra);
  if (c->parseerror && ant) {
        poncolorv(w,CINPUTINAC);
        if (pletra<perror && perror<=uletra) v10printf(w,"%c",ant);
        *perror=ant;
        poncolorv(w,CNORMAL);
        if (pletra<perror) pletra=perror+1;
        if (pletra<=uletra) v10printf(w,"%s",pletra);
   }
  *uletra=antuletra;
}

int editaselect(v10cursors *c,windows *w)
{
  int ch;
  int salir=0;
  renmarca(w,0,"SELECT");
  while (!salir) {
        ch=tecla();
        switch (ch) {
              case cua:if ((despsel+1)*WANCHO(w)<strlen(c->sql)) despsel++;
                       presentaselect(c,w);
                       break;
              case cuu:if (despsel>0) despsel--;
                       presentaselect(c,w);
                       break;
              default:
				  salir=1;
                       break;
            }
    }
  renmarca(w,1,"SELECT");
  return(ch);
}

char pantdebug[][127]={"Cursor: _40______________________________                                                                                     ",
                       "Fichero _255________________________________________________            Linea @L@@                                            ", 
                       "Funcion ____________________         OCI @S@ _30_______________         OCI @S@@ _30_________________________                 ",                                                        
                       "Error @S@@@@ Filas procesadas @L,@@@@                                                                                         ",
                       "______________________________________________________________________________________________________________________________",
                       "______________________________________________________________________________________________________________________________",
                       "______________________________________________________________________________________________________________________________",
                       "______________________________________________________________________________________________________________________________",
                       "______________________________________________________________________________________________________________________________",
					   "Ejec. @L,@@@@@ #L,####.### sg.       Fetch @L,@@@@ #L,####.### sg.      Ejefetch @L,@@@@ #L,####.### sg.                      ",
					   "Total          #L,####.###                         #L,####.###                           #L,####.###                          "
};


static void csrdef_debug(v10cursors *cur)
{
  static v10dialogs dicsr;
  static int init;
  int funoci;
  char nombrefunoci[MAXPATH],nombrefunora[MAXPATH];
  char fichero[MAXPATH],funcion[MAXPATH];
  char error1[MAXPATH], error2[MAXPATH], error3[MAXPATH], error4[MAXPATH], error5[MAXPATH];
  if (init==0) {
     initdian(&dicsr,pantdebug,"DEBUG CURSOR",1,LINEASPANTALLA-14,"ORADEBUG");
	 init=1;
  }
  funoci=cur->funoci;
  strcpy(fichero,cur->file);
  strcpy(funcion,cur->funcion);
  asignadialog(&dicsr,cur->nombre,fichero,&cur->line,funcion,&cur->funsql,nombrefunora,&funoci,nombrefunoci,&cur->errcode,
      &cur->filasprocesadas, error1, error2, error3, error4, error5, &cur->ejecuciones, &cur->texec, &cur->numfetch, &cur->tfetch,
					  &cur->numejefetch,&cur->tejefetch,&cur->totexec,&cur->totfetch,&cur->totejefetch,NULL);
  if (cur->errcode) {
      getcurerror(cur,error_oracle);
   	  v10log(LOGERROR,"Cursor %s Error %s\n",cur->nombre,error_oracle);
  }
  else strcpy(error_oracle, "");
  piece(error_oracle, error1, "\n", 1);
  piece(error_oracle, error2, "\n", 2);
  piece(error_oracle, error3, "\n", 3);
  piece(error_oracle, error4, "\n", 4);
  piece(error_oracle, error5, "\n", 5);
  strcpy(nombrefunora,buscafun(orafun,cur->funsql));
  strcpy(nombrefunoci,buscafun(ocifun,cur->funoci));
  muestradialog(&dicsr,0);
  actualizadialog(&dicsr);
}

static void sustituyebinds(v10cursors *c)
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
		while ((aux=strstr(sql,nombrebind))!=NULL && !isalnum(aux[strlen(nombrebind)])) {
			  strerase(aux,0,strlen(nombrebind));
			  pasaoracampo2ascii(ca,buffer,1,1);
			  strins(aux,buffer);
		}
	}
	mete_en_clipboard(sql);

}

void STDcursordebug(v10cursors *c)
{
  windows wselect;
  int salir=0,ret;
  int vinput=2;
  short *copia;
  unsigned timeout;
  void *triger_timeout,*trigervivo;
  dametimeoutteclado(&timeout,&triger_timeout);
  trigervivo=dametrigervivo();
  pontrigervivo(NULL);
  timeoutteclado(0,NULL);
  copia=salvapantallad(0,0,COLUMNASPANTALLA-1,LINEASPANTALLA-1);
  pintaonline("{Tab} Cambia de ventana {Esc} Salir {CF10} Edita Fichero\n {CF11} Copia Select {CF12} Copia Select con binds {M} Menu cursores {AF10} Aborta");
  initvn(&wselect,1,22,COLUMNASPANTALLA-2,LINEASPANTALLA-17,"ORADEBUG");
  csrdef_debug(c);
  enmarca(&wselect,1,"SELECT");
  despsel=0;
  presentaselect(c,&wselect);
  encolatecla(cr);
  menugenerico(c,0,1,1,COLUMNASPANTALLA/2-3,19,0,(char *(*)(void *,int))direc_define,NULL,NULL);
  encolatecla(cr);
  menugenerico(c,0,COLUMNASPANTALLA/2,1,COLUMNASPANTALLA-2,19,0,(char *(*)(void *,int))direc_bind,NULL,NULL);
  while (!salir) {
        switch (vinput) {
               case 0:if (c->ndef) {
                         menugenerico(c,0,1,1,COLUMNASPANTALLA/2-3,19,1,(char *(*)(void *,int))direc_define,tecla_debugdef,NULL);
                         ret=ult_pul;
                       } else ret=tab;
                      break;
               case 1:if (c->nbind) {
                          menugenerico(c,0,COLUMNASPANTALLA/2,1,COLUMNASPANTALLA-2,19,1,(char *(*)(void *,int))direc_bind,tecla_debugbind,NULL);
                          ret=ult_pul;
                       } else ret=tab;
                      break;
               case 2:ret=editaselect(c,&wselect);
                      break;
            }
        switch (ret) {
		     case C_F(10):invocaeditor(c->file,NULL);
				          break;
		     case C_F(11):mete_en_clipboard(c->sql);
				          break;
		     case C_F(12):sustituyebinds(c);
				          break;
             case 'm':
             case 'M': menucursores();
                       break;
             case esc:salir=-1;
             case tab:vinput++;vinput%=3;
                      break;
             case A_F(10):final(("Programa abortado por usuario"));
          }
   }
  borraonline();
  recuperapantallad(0,0,COLUMNASPANTALLA-1,LINEASPANTALLA-1,copia);
  timeoutteclado(timeout,triger_timeout);
  pontrigervivo(trigervivo);
}

void STDldadebug(struct csrdef *c,int funcion)
{
  windows win;
  short *copia;
  initvn(&win,1,LINEASPANTALLA-10,COLUMNASPANTALLA-2,LINEASPANTALLA-3,"ORADEBUG");
  copia=salvavd(&win);
  enmarca(&win,0,"Debug ORACLE nivel LDA");
  poncolorv(&win,CNORMAL);
  v10printf(&win,"\nFuncion oracle ");
  poncolorv(&win,CINPUTINAC);
  v10printf(&win,"%3d %s",funcion,buscafun(orafun,funcion));
  poncolorv(&win,CNORMAL);
  v10printf(&win," Funcion OCI ");
  poncolorv(&win,CINPUTINAC);
  v10printf(&win,"%3d %s\n",funcion,buscafun(orafun,funcion));
  poncolorv(&win,CNORMAL);
  v10printf(&win,"\n");
  poncolorv(&win,CNORMAL);
  tecla();
  recuperavd(&win,copia);
}     

void detallaerrorcursor(int nivel,v10cursors *cur,int soloerror)
{
    int nc;
    char buffer[MAXCADENA]="";
    char valor[MAXCADENA];
    if (cur->errcode==0 && soloerror==1) return;
    if (cur->errcode) {
        getcurerror(cur,buffer);
    } else {
        *buffer=0;
    }
    v10log(nivel,"Cursor %s error %ld %s\n",cur->nombre,cur->errcode,buffer);
    v10log(nivel,"%s"," Defines\n");
    for (nc=0;nc<cur->ndef;nc++) {
        campooras *c=cur->def+nc;
		getcurerror(cur,buffer);
        if (c->dato) pasaoracampo2ascii(c,valor,0,1);
        else         *valor=0;
        if (c->error || soloerror==0) v10log(nivel,"   campo %s Valor %s error %ld %s\n",c->nombre,valor,c->error,buffer);
    }
    v10log(nivel,"%s"," Binds\n");
    for (nc=0;nc<cur->nbind;nc++) {
        campooras *c=cur->bind+nc;
		getcurerror(cur,buffer);
        if (c->dato) pasaoracampo2ascii(c,valor,0,1);
        else         *valor=0;
        if (c->error || soloerror==0) v10log(nivel,"   campo %s Valor %s error %ld %s\n",c->nombre,valor,c->error,buffer);
    }
}

