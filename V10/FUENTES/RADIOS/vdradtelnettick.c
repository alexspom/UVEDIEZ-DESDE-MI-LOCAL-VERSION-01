/*******************************************************************************
* Módulo : VDRADTELNETTICK.C                                                   *
* Función: Tratamiento de teclas telnet                                        *
*                                                                              *
* Autor  : Eduardo Alsina                                                      *
* Revisado por:                                                                *
* Fecha  : 01-10-2007                                                          *
********************************************************************************
* Histórico de cambios
* ====================
*******************************************************************************/
#include "vdradio.h"
// Caracteres especiales TELNET
#define CIAC     255
#define CDONT    254
#define CDO      253
#define CWONT    252
#define CWILL    251
#define CECHO      1
#define CTILDE   126
#define CFIN      52
#define CINICIO   49
#define CINSERT   50

//Gestion de terminales telnet

#define STCONORMAL      0
#define STCORECIAC      1
#define STCORECWILL     2
#define STCORECWONT     3
#define STCORECDO       4
#define STCORECDONT     5
#define STCORECESC      6
#define STCORECCORCHETE 7
#define STCORECFUNC     8
#define STCORECFUNC1    9


char PRINSCAN='$';
char FINSCAN='%';
char PRIN232=1;
char FIN232=1;
int CSUENA=0;

static void tratawill(conexiones *c,int ret)
{
    c->status=STCONORMAL;
}

static void tratado(conexiones *c,int ret)
{
    if (ret==CECHO) {
        v10sockprintf(c->v10sock,"%c%c%c",CIAC,CWILL,CECHO);
    }
    c->status=STCONORMAL;
}

static int conviertefuncion(conexiones *c,int ret)
{
	switch (ret) {
	    case 'P':ret=F(1);
			     break;
	    case 'Q':ret=F(2);
			     break;
	    case 'R':ret=F(3);
			     break;
	    case 'S':ret=F(4);
			     break;
	    case '5':ret=F(5);
                 if (v10sockhaycar(c->v10sock)) v10socksigcar(c->v10sock);
			     break;
	    case '7':ret=F(6);
                 if (v10sockhaycar(c->v10sock)) v10socksigcar(c->v10sock);
			     break;
	    case '8':ret=F(7);
                 if (v10sockhaycar(c->v10sock)) v10socksigcar(c->v10sock);
			     break;
	    case '9':ret=F(8);
                 if (v10sockhaycar(c->v10sock)) v10socksigcar(c->v10sock);
			     break;
	    case 'A':ret=F(9);
                 if (v10sockhaycar(c->v10sock)) v10socksigcar(c->v10sock);
			     break;
	    case 'B':ret=F(10);
                 if (v10sockhaycar(c->v10sock)) v10socksigcar(c->v10sock);
			     break;
	    case 'D':ret=F(11);
                 if (v10sockhaycar(c->v10sock)) v10socksigcar(c->v10sock);
			     break;
	    case 'E':ret=F(12);
                 if (v10sockhaycar(c->v10sock)) v10socksigcar(c->v10sock);
			     break;
        default :ret=0;
                 break;
	}
    return(ret);
}

void vaciabuffertelnet(conexiones *c)
{
    while (v10sockhaycar(c->v10sock)) {
        int ret;
        ret = v10socksigcar(c->v10sock);
    }
}

void tratateclastelnet(conexiones *c)
{
    while (v10sockhaycar(c->v10sock)) {
        int ret;
        ret=v10socksigcar(c->v10sock);
        switch (c->status) {
            case STCORECCORCHETE:c->status=STCONORMAL; 
                                switch (ret) {
                                   case 'A':encolateclaconexion(c,cuu);
                                            break;
                                   case 'B':encolateclaconexion(c,cua);
                                            break;
                                   case 'D':encolateclaconexion(c,cui);
                                            break;
                                   case 'C':encolateclaconexion(c,cud);
                                            break;
                                   case CINICIO:
											 if (v10sockhaycar(c->v10sock)>1) {
												 c->status=STCORECFUNC;
												 break;
											 }
                                             encolateclaconexion(c,home);
                                             break;
                                   case CINSERT:
                                             if (v10sockhaycar(c->v10sock)>1) {
												    c->status=STCORECFUNC1;
												    break;
                                             }
                                             encolateclaconexion(c,inse);
                                             break;
                                   case CFIN:encolateclaconexion(c,end);
                                  }
                                 break;
			case STCORECFUNC1:ret=ret-'0'+'A';
            case STCORECFUNC: ret=conviertefuncion(c,ret);
                              c->status=STCONORMAL;
                              if (ret) encolateclaconexion(c,ret);
                              break;
            case STCORECWILL:
            case STCORECWONT:tratawill(c,ret);
                             break;
            case STCORECDO:
            case STCORECDONT:tratado(c,ret);
                             break;
            case STCORECIAC:switch (ret) {
                                case CWILL:c->status=STCORECWILL;
                                           break;
                                case CWONT:c->status=STCORECWONT;
                                           break;
                                case CDO:c->status=STCORECDO;
                                           break;
                                case CDONT:c->status=STCORECDONT;
                                           break;
                                default:   c->status=STCONORMAL;
                                           break;
                            }
                            break;
            case STCORECESC:if (ret=='[') {
                               c->status=STCORECCORCHETE;
                               break;
                             }
                            if (ret=='O') {
                               c->status=STCORECFUNC;
                               break;
                             }
                            c->status=STCONORMAL;
            case STCONORMAL:
                  switch (ret) {
                    case CTILDE:break;
                    case CIAC:c->status=STCORECIAC;
                              break;
                    case esc:if (v10sockhaycar(c->v10sock)) c->status=STCORECESC;
							 else                        {
								 v10log(LOGNORMAL,"%s","Recibido esc\n");
								 fdesconecta(c);
							 }
                             break;
                    case '\n':
                              break;
                    case 127:encolateclaconexion(c,dele);
                             break;
                    default: encolateclaconexion(c,ret);
                             break;
                  }
        }
    }
}

static int trata232(conexiones *c,int ret)
{
    bloques *b;
	if (c->f==NULL) return(0);
	b=c->f->b[c->f->act];
	if (ret==PRIN232) {
		c->en232=1;
		c->ptr232=c->buffer232;
		return(1);
	}
	if (c->en232==0) return(0);
	if (ret==FIN232) {
		c->en232=0;
		*c->ptr232=0;
		if (b->ffinquery) {
            ejecutaftriger(b,PFINQUERY,b->ffinquery,NULL);
		}
		return(1);

	}
	if (c->ptr232-c->buffer232>=sizeof(c->buffer232)) c->ptr232=c->buffer232;
	*c->ptr232++=(char)ret;
	return(1);
}

static void tratateclasnormales(conexiones *c)
{
	int primtecla = 1;
    while (hayteclaconexion(c)) {
        int ret;
        bloques *b=NULL;
        v10inputs *v=NULL;
        fcampos *campo;
        MODIFRADIO++;
        if (c->pideusr==OPCONFIRMADO && primtecla==1) {
            vduser=c->op;
            ponuserdb();
            ponrecurso(c->rec.codrecurso);
			primtecla = 0;
        }
        ret=sigcarconexion(c);
		v10log(LOGDEBUG, "Recibido car %d %c de conexion %s\n", ret,ret,c->rec.codrecurso);
        c->umensaje=damecent();
        if (c->f) {
            if (c->f->act>=0) {
                b=c->f->b[c->f->act];
                v=b->vi.act;  
                campo=v->trigerdatos;
            } else {
                ret=cr;
            }
        }
        if (c->f==NULL || c->rec.status==STRECMENSAJE) if (ret!='\r' && (ret<F(1) || ret>F(12))) continue;
        if (c->pmensaje==0) c->pmensaje=c->umensaje;
        if (trata232(c,ret)) continue;
        switch (ret) {
		case cuu:       c->scanning = 0;
			            if (c->f) anteriorcampo(c);
                        break;
             case tab:
			 case cua:  c->scanning = 0;
				        if (c->f) siguientecampo(c);
                        break;
             case cui:  if (c->ptr>c->buffer) {
                           c->ptr--;
                           v10sockencolac(c->v10sock,"\033[D");
                         }
                        break;
             case cud:  if (c->ptr<=c->buffer+v->lpan-1) {
                            c->ptr++;
                            v10sockencolac(c->v10sock,"\033[C");
                         }
                         break;
             case home:  while (c->ptr>c->buffer) {
                               c->ptr--;
                               v10sockencolac(c->v10sock,"\033[D");
                         }
                         break;
             case inse:  strinserta(c->ptr,0,1);
                         v10sockprintf(c->v10sock,"%s",v->password?"":c->ptr);
                         posicionaconexion(c);
                         break;
             case end:   while (!es_blanco(c->ptr) && c->ptr<=c->buffer+v->lpan-1) {
                                c->ptr++;
                                v10sockencolac(c->v10sock,"\033[C");
                          }
                         break;
             case back:  if (c->ptr>c->buffer) {
						    c->ptr--;
                            strdel(c->ptr,0,1);
                            v10sockprintf(c->v10sock,"\033[D\0337%s\0338",v->password?"":c->ptr);
                         }
                         break;
             case dele:  strdel(c->ptr,0,1);
                         v10sockprintf(c->v10sock,"\0337%s\0338",v->password?"":c->ptr);
                         break;
             case cr:    v10log(LOGNORMAL,"%s","Recibido ENTER del terminal\n");
			        	 c->scanning = 0;
				         gestionaterminal(1,c);
                         break;
             case lf:    break;
             default:    if (ret==PRINSCAN) {
                            c->scanning=1;
							c->ptr = c->buffer;
                            break;
                         }
                         if (ret==FINSCAN) {
                             *c->ptr=0;
                             c->scanning=0;
                             if (campo->scan==0) break;
                             campo->nscan++;
                             if (campo->nscan>=campo->scan) {                                 
                                 if (v->autoenter) {
                                     //ret=terminainputcampo(c,1);
                                     gestionaterminal(1,c);
								 } else {
									 ret=siguientecampo(c);
                                     if (ret) break;
								 }
                             }
                             break;
                         }
                         if ((ret>=F(1) && ret<=F(12)) ||ret==esc) {
                             if (tratafuncion(c,ret)) gestionaterminal(1,c);
                             if (c->f) {
                                 if (c->f->act<0) gestionaterminal(1,c);
                             }
                             break;
                         }
                         if (campo->scan==0 && c->scanning) break;
                         if (tratateclaconexion(c,ret)) {
                             if (b->vi.act->password) v10sockencola(c->v10sock,' ');
                             else                  if (c->scanning==0)v10sockencola(c->v10sock,ret);
                         }
                         break;
        }
        v10log(LOGDEBUG,"tecla pulsada %d %c PENDIENTES %d\n",ret,ret,c->nbuftec);
    }
}

#define CDAMEMENSAJE "DECLARE MIROWID VARCHAR2(100);"\
                     "BEGIN "\
                     " SELECT MSG.ROWID,'\nMENSAJE DE '||NVL(USU.NOMBRE,MSG.CODOPEMODIF)||'\n'||MSG.MENSAJE INTO MIROWID,:MENSAJE FROM VDMSGRAD MSG,VDUSUARIO USU WHERE MSG.CODOPEMODIF=USU.CODOPE(+) AND MSG.CODRECURSO=:CODRECURSO AND MSG.STATUS=100 AND ROWNUM=1;"\
                     " UPDATE VDMSGRAD SET STATUS=200 WHERE ROWID=MIROWID;"\
                     " COMMIT;"\
                     " EXCEPTION WHEN NO_DATA_FOUND THEN :MENSAJE:=NULL;"\
                     "END;"

void tratamensajesrad(conexiones *c)
{
    static v10cursors *vddamemensaje;
    static char mensaje[MAXPATH];
	static char codrecurso[LCODRECURSO];
    if (vddamemensaje == NULL) {
        vddamemensaje = abrecursordebug(CDAMEMENSAJE,0);
        bindtodo(vddamemensaje, "MENSAJE", mensaje, sizeof(mensaje), V10CADENA,
                 "CODRECURSO", codrecurso, sizeof(codrecurso),V10CADENA,
                 NULL);
    }
	strcpy(codrecurso, c->rec.codrecurso);
    ejecutacursor(vddamemensaje);
    if (es_blanco(mensaje)) return;
    c->rec.status = STRECMENSAJE;
    mensajeradioc(c, CSUENA, mensaje);
}

#define TMENSAJE 200
int telnettick(void)
{
    int nc;
    static v10horas hultmensaje;
    int tratamensaje = 0;
    if (gettime() - hultmensaje > TMENSAJE) {
        tratamensaje = 1;
        hultmensaje = gettime();
    }
    tratanuevatcp();
    for (nc=0;nc<ncon;nc++) {
        conexiones *c=con[nc];
		ponprefijolog(c->rec.codrecurso);
        if (v10socklisto(c->v10sock)==0) {
            v10log(LOGNORMAL,"Conexión %d anulada\n",nc);
            liberaconexion(c);
            continue;
        }
        if (c->pideusr==OPPENDIENTE) {
            if (c->f) liberaform(c->f);
            c->f=NULL;
            cargaradfrm("VDRUSER",c,0,0);
            c->pideusr=OPENCURSO;
        }
        if (c->pideusr==OPVERIFICADO) {
            if (c->f) liberaform(c->f);
            c->f=NULL;
            restauraterminal(c);
            c->pideusr=OPCONFIRMADO;
        }
        switch (c->rec.status) {
            case STRECINACTIVO:
            case STRECBUSCANDO:
            case STRECSINTRAB:
            case STRECASIGNADO: gestionaterminal(0,c);
                               break;
        }
        if (c->f && c->f->act>=0) {
            bloques *b = c->f->b[c->f->act];
            if (b->ftimeout && (damecent()-c->umensaje)>b->timeout) {
                ejecutaftriger(b, 0, b->ftimeout, NULL);
                c->umensaje = damecent();
                rollback();
                if (c->f->act<0) {
                    liberaform(c->f);
                    c->f = NULL;
                    strcpy(c->rec.npantalla, "");
                    liberaconexion(c);
                }
                continue;
            }
        }
        c->mostrar=1;
        if (c->modificado && c->rec.status==STRECCONFORM) dr.pasaformaterm(c,CSUENA);
        c->mostrar=0;
        tratateclastelnet(c);
        tratateclasnormales(c);
        if (tratamensaje) tratamensajesrad(c);
    }
    return(0);
}