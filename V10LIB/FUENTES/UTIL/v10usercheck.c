/*
* Módulo : V10USERCHECK.C
* Objeto:  Verificación de coherencia del usuario
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10user.h"

int chequeadatos(void)
{
	int i,j,k,l;
	int ret = 0;
	v10log(LOGNORMAL,"Chequeando los campos de igual nombre...\n");
	for (i=0;i<user.ntables;i++) {
		for (j=0;j<user.table[i]->ncolumns;j++) {
			columns *c1=user.table[i]->column[j];
			for (k=i+1;k<user.ntables;k++) {
				for (l=0;l<user.table[k]->ncolumns;l++) {
					columns *c2=user.table[k]->column[l];
					if (stricomp(c1->column_name,c2->column_name)!=0) continue;
					if (stricomp(c1->data_type,c2->data_type)!=0) {
						v10log(LOGERROR,"  %s.%s=%s.%s:\n",user.table[i]->table_name,user.table[i]->column[j]->column_name,user.table[k]->table_name,user.table[k]->column[l]->column_name);
						v10log(LOGERROR," Tipo diferente %s != %s\n",user.table[i]->column[j]->data_type,user.table[k]->column[l]->data_type);
						ret=-1;
						continue;
					}
					if (c1->data_length==c2->data_length) {
						if (c1->tipo!=TIPONUMBER) continue;
						if (c1->data_precision!=c2->data_precision) {
							v10log(LOGERROR,"  %s.%s=%s.%s:\n",user.table[i]->table_name,c1->column_name,user.table[k]->table_name,c2->column_name);
							v10log(LOGERROR," Precision diferente %ld != %ld\n",user.table[i]->column[j]->data_precision,user.table[k]->column[l]->data_precision);
							ret=-1;
						}
						if (c1->data_scale!=c2->data_scale) {
							v10log(LOGERROR,"  %s.%s=%s.%s:\n",user.table[i]->table_name,c1->column_name,user.table[k]->table_name,c2->column_name);
							v10log(LOGERROR," Scale diferente %ld != %ld\n",c1->data_scale,c2->data_scale);
							ret=-1;
						}
					} else {
						v10log(LOGERROR,"  %s.%s=%s.%s:\n",user.table[i]->table_name,c1->column_name,user.table[k]->table_name,c2->column_name);
						v10log(LOGERROR," Length diferente %ld != %ld\n",c1->data_length,c2->data_length);
						ret=-1;
					}
				}			  
			}
		}
	}
	return(ret);
}