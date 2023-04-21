/*******************************************************************************
* Módulo : VDRADTRATA.C                                                        *
* Función: Gestion de terminales de radio                                      *
*                                                                              *
* Autor  : Eduardo Alsina                                                      *
* Revisado por:                                                                *
* Fecha  : 01-10-2007                                                          *
********************************************************************************
* Histórico de cambios
* ====================
*******************************************************************************/
#include "vdradio.h"

#define TIEMPOREBUSCA  1500
#define TIEMPOBUSCANDO 20


void liberaterminal(conexiones *c)
{
    if (c->rec.status!=STRECBUSCANDO && c->rec.status!=STRECASIGNADO) {
        c->rec.status=STRECINACTIVO;
        RECactualizastatus(&c->rec,NOVERIFICA);
    }
}

int damestatusterm(conexiones *c)
{
    int ret;
    ret=RECselcodrecurso(c->rec.codrecurso,&c->rec);
    return(ret);
}

static int mensajeradio(conexiones *c,int suena,char *format,...)
{
    int ret;
    va_list arg;
    va_start(arg,format);
    ret=dr.mensaje(c,suena,format,arg);
    va_end(arg);
    return(ret);
}

void buscatrabajo(conexiones *c)
{
    vdrectareas tarea;
    vdperfiltareas perfil;
    int ret;
    c->ubusqueda=damecent();
    v10log(LOGNORMAL,"%s","Buscando trabajos\n");
    if (!es_blanco(c->rec.planificador)) {
        int (*planificador)(conexiones *c,char *param);
        planificador=damefundll(c->rec.libplanificador,c->rec.planificador);
        if (planificador) {
            ret=planificador(c,c->rec.paramplanif);
            if (ret==0) return;
        }
        mensajeradioc(c,0,"\n\n\nNO HAY TRABAJOS\nPENDIENTES");
    } else {
        ret=RETbuscacodrecurso(c->rec.codrecurso,&tarea);
        if (ret==0) {
            do {
                ret=PERselcodperfil(tarea.codperfil,&perfil);
                if (ret!=0) {
                    v10log(LOGERROR,"No existe perfil %s\n",tarea.codperfil);
                    continue;
                }
                if (*perfil.formplanif == 'S' && es_blanco(perfil.funplanif)) {
                    ret=cargaradfrm(perfil.npantalla,c,0,1);
                    if (ret==0) {
                        c->perfil=perfil;
                        strcpy(c->rec.codperfil,perfil.codperfil);
                        ret=RECactualizanpantalla(&c->rec,0);
                        commit();
                        return;
                    }
                }
            } while ((ret=RETnextcodrecurso(&tarea))==0);
        }
        c->rec.status=STRECBUSCANDO;
        ret=RECactualizastatus(&c->rec,0);
        commit();
        mensajeradioc(c,0,"\n\n\nBUSCANDO TRABAJO");
    }
}

static void asignaperfil(conexiones *c)
{
    vdperfiltareas perfil;
    int ret;
    ret=PERselcodperfil(c->rec.codperfil,&perfil);
    if (ret) {
        v10log(LOGERROR,"Terminal %s no existe perfil %s\n",c->rec.codrecurso,c->rec.codperfil);
		c->rec.status=STRECINACTIVO;
        liberaterminal(c);
        commit();
        return;
    }
    ret=cargaradfrm(perfil.npantalla,c,0,1);
    if (ret!=0) {
        liberaterminal(c);
        commit();
    }
}

void restauraterminal(conexiones *c)
{
  vduser=c->op;
  ponuserdb();
  ponrecurso(c->rec.codrecurso);
  switch (c->rec.status) {
    case STRECINACTIVO: gestionaterminal(1,c);
                    break;
    case STRECBUSCANDO:damestatusterm(c);
                       break;
    case STRECSINTRAB: 
	case STRECASIGNADO: 
					   liberaterminal(c);
                       commit();
                       mensajeradioc(c,0,"\n\n\nNO HAY TRABAJOS\nPENDIENTES");
                       break;
    case STRECCONFORM:
    case STRECMENSAJE:if (c->f) {
                         liberaform(c->f);
                         c->f=NULL;
                       }
                      if (*c->rec.npantalla) {
                         int ret;
                         ret=cargaradfrm(c->rec.npantalla,c,1,1);
                         if (ret) {
                             liberaterminal(c);
                             commit();
                         }
                      } else  gestionaterminal(1,c);
                      break;
    default: v10log(LOGNORMAL,"Status %d no conocido.\n",c->rec.status);
             liberaterminal(c);
             break;
  }
}

void gestionaterminal(int immediato,conexiones *c)
{
  static int gestionando=0;
  if (gestionando) return;
  if (!es_blanco(c->op.codope)) {
     vduser=c->op;
     ponuserdb();
     ponrecurso(c->rec.codrecurso);
  } else {
      strcpy(vduser.codope,"VDRADIO");
      ponuserdb();      
      ponrecurso(c->rec.codrecurso);
  }
  ponhostnameext(c->rec.codrecurso);
  switch (c->rec.status) {
	case STRECINACTIVO: if (c->pideusr!=OPVERIFICADO) {
	                      if (damecent()-c->ubusqueda<TIEMPOREBUSCA && immediato==0) break;
                          if (damestatusterm(c)==0) {
                             if (*(c->rec.activo)=='S') {
                                gestionando=1;
                                buscatrabajo(c);
                                gestionando=0;
                             } else {
                                mensajeradio(c,CSUENA,"%s %s\n\n\n\n       TERMINAL DESACTIVADO",c->rec.codrecurso,c->rec.codope);
                             }
                           }
		 				}
                   break;
    case STRECBUSCANDO:if (damecent()-c->ubusqueda<TIEMPOBUSCANDO && immediato==0) break;
                       damestatusterm(c);
                       break;
    case STRECSINTRAB: c->rec.status=STRECINACTIVO;
                       RECactualizastatus(&c->rec,0);
                       mensajeradioc(c,0,"\n\n\nNO HAY TRABAJOS\nPENDIENTES");
                       commit();
                       break;
    case STRECASIGNADO: asignaperfil(c);
                        break;
    case STRECCONFORM: vaciabuffertelnet(c); 
                       tratafrm(c);
                       break;
    case STRECMENSAJE :if (c->contenidomensaje) {
                          free(c->contenidomensaje);
                          c->contenidomensaje=NULL;
                       }
                       vaciabuffertelnet(c);
					   if (c->f) {
						   dr.pasaformaterm(c, CSUENA);
						   c->rec.status = STRECCONFORM;
					   }  else {
						   c->rec.status = STRECSINTRAB;
					   }
                       RECactualizastatus(&c->rec,NOVERIFICA);
                       commit();
                       break;
    default: v10log(LOGNORMAL,"Gestionando terminal %s: Status %d no conocido.\n",c->rec.codrecurso,c->rec.status);
             liberaterminal(c);
             break;
  }
  c->umensaje=damecent();
  ponhostname();
}
