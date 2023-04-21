// Modulo generado automaticamente a partir de VDDEFBLOQUE.DEF

VDEXPORT diccionario ddeb;
#define DEBNUMCOL	31
typedef struct {
        char    rowid[ROWIDLON];
        char    nbloque[LNBLOQUE];
        char    grupobloque[LGRUPOBLOQUE];
        char    tipopantalla[LTIPOPANTALLA];
        long    numposx;
        long    numposy;
        long    numregpag;
        char    ayudaonline[LAYUDAONLINE];
        char    titulobloque[LTITULOBLOQUE];
        char    modoquery[LMODOQUERY];
        char    fcontextual[LFCONTEXTUAL];
        char    ftecla[LFTECLA];
        char    capitaliza[LCAPITALIZA];
        char    twhere[LTWHERE];
        char    torderby[LTORDERBY];
        char    cnoinsert[LCNOINSERT];
        char    privinsert[LPRIVINSERT];
        char    cnodelete[LCNODELETE];
        char    privdelete[LPRIVDELETE];
        char    cnoenter[LCNOENTER];
        char    privnoenter[LPRIVNOENTER];
        char    cnoupdate[LCNOUPDATE];
        char    privupdate[LPRIVUPDATE];
        char    cnoorains[LCNOORAINS];
        char    privorains[LPRIVORAINS];
        char    fayuda[LFAYUDA];
        char    fauxiliar[LFAUXILIAR];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
    } vddefbloques;

// Prototipos de funciones definidas en VDDEFBLOQUE.C
VDEXPORT diccionario *DEBdamediccionario(void);
VDEXPORT int DEBselvddefbloque(char *nbloque,char *tipopantalla,vddefbloques *deb);
VDEXPORT int DEBactualizavddefbloque(vddefbloques *deb,int error);
VDEXPORT int DEBinsert(vddefbloques *deb,int error);
VDEXPORT char *DEBlog(vddefbloques *deb);
char * DEBdebug(vddefbloques *deb);
