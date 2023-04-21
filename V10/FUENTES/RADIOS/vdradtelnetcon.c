/*******************************************************************************
* Módulo : vdradtelnetcon.c                                                    *
* Función: Gestion de conexiones terminales telnet                             *
*                                                                              *
*                                                                              *
* Autor  : Eduardo Alsina                                                      *
* Revisado por:                                                                *
* Fecha  : 01-10-2007                                                          *
********************************************************************************
* Histórico de cambios
* ====================
*******************************************************************************/

#include "vdradio.h"

#define OFFSET_ADDR_TCP     2
#define LEN_ADDR_TCP        4


conexiones *con[MAXRECURSOS];
static servidorsocks *server[MAXPORTRADIO];
int ncon;

#define CLOGOUT "BEGIN VDRADIO.LOGOUT(:CODRECURSO);END;"
static v10cursors *vdlogout;
#define CLOGIN "DECLARE RET NUMBER; BEGIN RET:=VDRADIO.LOGIN(:CODRECURSO,:CODOPE,:NPANTALLA);END;"
static v10cursors *vdlogin;
#define CDAMESID "BEGIN VD.DAMESID(:SID,:SERIALNUM,:TERMINAL); END;"
static v10cursors *vddamesid;

typedef struct {
           long sid;
           long serialnum;
           char terminal[LTERMINAL];
} vdsids;
static vdsids vdsid;

static void fvddamesid(long *sid,long *serial,char *terminal)
{
    ejecutacursor(vddamesid);
    *sid=vdsid.sid;
    *serial=vdsid.serialnum;
    strcpy(terminal,vdsid.terminal);
}

int loginterminal(conexiones *c)
{
    int ret;
    bindtodo(vdlogin,"CODRECURSO",c->rec.codrecurso,sizeof(c->rec.codrecurso),V10CADENA,
		             "CODOPE",c->rec.codope,sizeof(c->rec.codope),V10CADENA,
		             "NPANTALLA",c->f->nombre,sizeof(c->f->nombre),V10CADENA,NULL);
    ret=ejecutacursor(vdlogin);
    return(ret);
}

int logoutterminal(conexiones *c)
{
    int ret;
    bindtodo(vdlogout,"CODRECURSO",c->rec.codrecurso,sizeof(c->rec.codrecurso),V10CADENA,NULL);
    ret=ejecutacursor(vdlogout);
    strcpy(c->rec.codope,"");
    memset(&c->op,0,sizeof(c->op));
    RECactualizacodope(&c->rec,NOVERIFICA);
    return(ret);
}

void liberaconexion(conexiones *c)
{
    int i;
    conexiones **dest,**orig;
    strcpy(c->rec.conectado,"N");
    c->rec.sid=0;
    c->rec.serialnum=0;
    strcpy(c->rec.terminal,"");
    RECactualizaconectado(&c->rec,NOVERIFICA);
    logoutterminal(c);
    commit();
    v10socklibera(c->v10sock);
    if (c->f) liberaform(c->f); 
    c->f=NULL;
    for (i=0;i<ncon;i++) {
        if (con[i]==c) {
           free(c);
           for (dest=con+i,orig=con+i+1;orig<con+ncon;orig++,dest++) {
               *dest = *orig;
           }
           ncon--;
           break;
        }
    }
}

conexiones *numcon(char *codrecurso)
{
    int nc;
    for (nc=0;nc<ncon;nc++) {
        if (strcmp(con[nc]->rec.codrecurso,codrecurso)==0) return(con[nc]);
    }
    return(NULL);
}


static vdrecursos *buscaterminal(SOCKADDR *origen,SOCKADDR *destino)
{
    int ret; 
    unsigned short puerto=ntohs(*(short *)destino->sa_data);
    unsigned char buffer[LDIRRECURSO];    
    static vdrecursos rec,posible;
    int numterm=0;
    if (!es_blanco(codrecursodef)) {
        ret=RECselcodrecurso(codrecursodef,&rec);
        if (ret==0) {
            conexiones *c=numcon(rec.codrecurso);
            if (c!=NULL) {
                v10log(LOGNORMAL,"%s","conexion anulada por reconexion\n");
                liberaconexion(c);
            }
            return(&rec);
        }
    }
    v10sockpintadir(origen,buffer);
    ret=RECbuscadirrecurso(buffer,&rec);
    memset(&posible,0,sizeof(posible));
    while (ret==0) {
        numterm++;
        if (atoi(rec.driver)!=0 && atoi(rec.driver)!=puerto) {
            ret=RECnextdirrecurso(&rec);
            continue;
        }
        if (numcon(rec.codrecurso)!=NULL) {
            posible=rec;
            ret=RECnextdirrecurso(&rec);
            continue;
        }   
        return(&rec);
    }
    if (*posible.codrecurso) {
        conexiones *c=numcon(posible.codrecurso);
        if (c!=NULL) {
            v10log(LOGNORMAL,"%s","conexion anulada por reconexion\n");
            liberaconexion(c);
        }
        return(&posible);
    }
    v10log(LOGNORMAL,"Conexion de direccion %s no asignada a %d terminal(es)\n",buffer,numterm);
    return(NULL);
}

void tratanuevatcp(void)
{
    v10socks *nueva;
    vdrecursos *rec;
    conexiones *c;
    int np=0;
    char buffer[LDIRRECURSO];
    for (np=0;np<dr.numports;np++) {
        while ((nueva=v10sockdameconexion(server[np]))!=NULL) {
        if (nueva==NULL) return;
            v10log(LOGNORMAL,"Recibida conexion de direccion %s puerto %d\n",v10sockpintaorigen(nueva,buffer),ntohs(*(short *)nueva->destino.sa_data));
            rec=buscaterminal(&nueva->origen,&nueva->destino);
        if (rec==NULL) {
            v10socklibera(nueva);
            continue;
        }
		ponprefijolog(rec->codrecurso);
        v10log(LOGNORMAL,"asociado a conexion %d\n",ncon);
        strcpy(rec->conectado,"S");
	    ponprefijolog(rec->codrecurso);
        fvddamesid(&rec->sid,&rec->serialnum,rec->terminal);
        RECactualizaconectado(rec,NOVERIFICA);
        commit();
        c=con[ncon]=calloc(1,sizeof(conexiones));
        c->rec=*rec;
        c->v10sock=nueva;
		//v10socknuggle(c->v10sock,1);
        c->ptr=con[ncon]->buffer;
        c->pmensaje=con[ncon]->umensaje=damecent();
        dr.initterm(con[ncon]);
        c->pideusr=OPPENDIENTE;
        c->mostrar=1;
        ncon++;
    }
}
}

static void finradiotcp(void)
{
    int np=0;
    for (np=0;np<dr.numports;np++) {
        v10sockcierraservidor(server[np]);
    }
    while (ncon) {
          liberaconexion(con[0]);
    }
    liberacursor(vdlogout);
    liberacursor(vdlogin);
    liberacursor(vddamesid);
}

int initradiotcp(void)
{
    int np=0;
    char destino[MAXPATH];
    for (np=0;np<dr.numports;np++) {
        sprintf(destino,"%d",atoi(dr.serviciotcp)+np);
        server[np]=v10socknuevoservidor(destino,0,NULL,NULL,NULL,NULL,NULL);
        if (server[np]==NULL) final(("No puedo abrir servidor %d",atoi(dr.serviciotcp)+np));
    }
    vdlogout=abrecursor(CLOGOUT);
    vdlogin=abrecursor(CLOGIN);
    vddamesid=abrecursor(CDAMESID);
    bindtodo(vddamesid,"SID",&vdsid.sid,sizeof(vdsid.sid),V10LONG,
                       "SERIALNUM",&vdsid.serialnum,sizeof(vdsid.serialnum),V10LONG,
                       "TERMINAL",vdsid.terminal,sizeof(vdsid.terminal),V10CADENA,
                       NULL);
    {vdrecursos rec; //Solo arregla error al hacer exit en ordenes raros
    RECselcodrecurso("",&rec);
    }
    atexit(finradiotcp);
    return(0);
}

int hayteclaconexion(conexiones *c)
{
    return(c->nbuftec);
}

int sigcarconexion(conexiones *c)
{
    int ret;
    if (c->nbuftec) {
        ret=c->buftec[0];
        memcpy(c->buftec,c->buftec+1,(c->nbuftec-1)*sizeof(c->buftec[0]));
        c->nbuftec--;
        return(ret);
    }
    return(-1);
}

void encolateclaconexion(conexiones *c,int tec)
{
    if (c->nbuftec>=MAXBUFTEC-1) return;
    c->buftec[c->nbuftec++]=tec;
}

