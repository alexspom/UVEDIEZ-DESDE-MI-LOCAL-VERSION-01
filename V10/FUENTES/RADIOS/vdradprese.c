#include "vdradio.h"

static int prescon,consel;
static windows wradio,wterm;
static int ACTMODIF;


void pintaradio(virtsels *s,int resaltado)
{
    int pos=VIRTPOS(s);
    char pmensaje[20],umensaje[20];
    conexiones *c=con[pos];
    char cadena[MAXCADENA];
    if (resaltado) poncolorv(&s->v,CINPUTACT);
       else        poncolorv(&s->v,CNORMAL);
    v10printf(&s->v,"%-*.*s %-*.*s %-*.*s %4d %s %s",10,10,c->rec.codrecurso,
           10,10,c->rec.codope,
           30,30,c->rec.npantalla,c->rec.status,cent2a(c->pmensaje,8,':',pmensaje),cent2a(c->umensaje,8,':',umensaje));
    poncolorv(&s->v,CNORMAL);
    clv(&wterm);
    if (c->rec.status!=STRECCONFORM) {
        if (c->contenidomensaje) v10printf(&wterm,c->contenidomensaje);
    } else {
        dr.damecadenaform(c,cadena);
        v10printf(&wterm,"%s",cadena);
    }
}

#define TTIMERAD 50
int teclaradio(virtsels *s)
{
    int ret;
    int pos=VIRTPOS(s);
    conexiones *c;
    forms *f;
	static v10horas ultpres;
    while (!hay_tecla_contimeout()) {
          if (prescon!=ncon) {
              if (ncon==0) {
                  clv(&s->v);
              }
              prescon=ncon;
              return(esc);
          }
          if (MODIFRADIO!=ACTMODIF && damecent()-ultpres>TTIMERAD) {
              representapagina(s);
              poncursorsel(s);
              ACTMODIF=MODIFRADIO;
			  ultpres = damecent();
          }
          esperamensaje(10);
     }
    ret=tecla();
    c=con[pos];
    f=c->f;
    switch (ret) {
        case C_F(10) : if (c->f) {
                          char nombre[MAXPATH];
                          bloques *b=f->b[f->act];
                          damenombrecompleto(b->fichero,nombre);
                          invocaeditor(nombre,NULL);
                       }
                       ret=0;
                       break;
        case C_F(11) : if (c->f) {
                          char nombre[MAXPATH],nombref[MAXPATH];
                          int ret;
                          sprintf(nombref,"%s.FRM",f->nombre);
                          ret=damenombrecompleto(nombref,nombre);
                          if (ret==0) invocaeditor(nombre,NULL);
                       }
                       ret=0;
                       break;
        case C_F(12):{char *fichero[MAXBLOQUES+1],destino[MAXPATH],nombref[MAXPATH];
			unsigned  nb = 0,i;
			int ret;
                      if (strchr(f->nombre, '.') == NULL) sprintf(nombref, "%s.FRM", f->nombre);
                        else strcpy(nombref, f->nombre);
                      ret = damenombrecompleto(nombref, destino);
                      if (ret == 0) {
                          fichero[nb] = strdup(destino);
                          nb++;
                      }
                      for (i=0;i<f->nbloques;i++,nb++) {
                           damenombrecompleto(f->b[i]->fichero,destino);
                           fichero[nb]=strdup(destino);
                       }
                      invocaeditormultiple(fichero,nb);
                      for (i = 0; i < nb;i++) free(fichero[i]);
                      ret=0;
                      break;
                     }
        default: if (ret<255 || ret==F(1)) encolateclaconexion(c, ret);
    }
    return(ret);
}

static void initpresentacion(void)
{
    int antansi=v10usaansi;
    char titulo[MAXCADENA];
    pontrigervivo(dr.tick);
    if (atoi(dr.serviciotcp)>0) {
        sprintf(titulo,"PROGRAMA DE RADIOS  Puertos: %s-%d  B.D. %s%s%s",dr.serviciotcp,atoi(dr.serviciotcp)+dr.numports-1,ORAUSR,*ORADB?"@":"",ORADB);
    } else {
    sprintf(titulo,"PROGRAMA DE RADIOS  Puerto: %s  B.D. %s%s%s",dr.serviciotcp,ORAUSR,*ORADB?"@":"",ORADB);
    }
    pintapantallav10(titulo);
    initvn(&wradio,1,2,85,30,"RADIO");
    enmarca(&wradio,0,"Terminales");
    v10printf(&wradio,"Recurso    Operario   Pantalla                       St.  Primer men.  Ult. mensaje\n");
    v10usaansi=0;
    v10printf(&wradio,"様様様様様 様様様様様 様様様様様様様様様様様様様様様 様様 様様様様様様 様様様様様様\n");
    v10usaansi=antansi;
    initvn(&wterm,88,2,COLUMNASPANTALLA-2,30,"RADIO");
    enmarca(&wterm,0,"Terminal");
    pintaonline("{AF10} Salir {CF10} Edita Bloque {CF11} Edita form {CF12} Edita todo");
}

int presentapantalla(void)
{
    static int init=0;
    if (init==0) {
        initpresentacion();
        init=1;
    }
    if (ncon) {
        consel=selecciona(0,2,0,0,1,&wradio,ncon,1,1,WANCHO(&wradio),"Terminales",pintaradio,teclaradio,consel,NULL);
    } else if (hay_tecla()) tecla();
    return(ult_pul);
}