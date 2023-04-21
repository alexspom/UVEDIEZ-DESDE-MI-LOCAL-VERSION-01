/*******************************************************************************
* Módulo : VDRADSCAN.C                                                         *
* Función: Trigers para tratar lectura obligatoria de scanner                  *
*                                                                              *
* Autor  : Eduardo Alsina                                                      *
* Revisado por:                                                                *
* Fecha  : 01-10-2007                                                          *
********************************************************************************
* Histórico de cambios
* ====================
*******************************************************************************/

#include "vdradio.h"

int ffuerzascan(bloques *b,ftrigers *ft)
{    
    conexiones *c=numcon(b->form->extraform);
    int ret;
    forms *f=FORM(b);
    fcampos *cinput=f->cinput;
    if (*FSCAN(b,cinput)) return(0);
    RECselcodrecurso(c->rec.codrecurso,&c->rec);
    if (*c->rec.tecleo=='S') return(0);
    ret=dameproteccionvd("TECLEARADIO");
    if (ret==0) return(0);
    if (ft->nparam>0) {
        if (strcmp(ft->param[0],"UBI")==0) {
            vdubicas vdubica;
            ret=UBIselvdubica(direccampoptr(b,cinput),&vdubica);
            if (ret==0 && *vdubica.swtetiq!='S') return(0);
        }
        if (strcmp(ft->param[0],"ART")==0) {
            vdartics vdartic;
            ret=ARTselcodart(direccampoptr(b,cinput),&vdartic);
            if (ret==0 && *vdartic.swtetiq!='S') return(0);
        }
    }
    return(-1);
}
