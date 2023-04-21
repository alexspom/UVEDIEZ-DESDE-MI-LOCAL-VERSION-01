/****
* VDDISP.C
*                                                    
* Propósito: Procesos de Reserva 
*                                            
* Autor  : FGS
* Fecha  : 25-4-2008                                                        
******
*  Modificaciones:
****/

#include "vdpedidos.h"

VDEXPORT void vddisp(procesos *proceso) {
    int ret;
    vdtareass tar;
    vdpedidos pedidos;

    v10log(LOGNORMAL,"%s","Iniciando disponibilidad...\n");
    memset(&tar,0,sizeof(tar));

    piece(proceso->proc.param,tar.tarea,"#",1);

    ret=TARselvdtareas(tar.tarea,&tar);
    if (ret) {
        v10log(LOGERROR,"vddisp. Tarea %s no existe\n", tar.tarea);
        return;
    }
    
    ret=PEDIDOprocdisponibilidad(tar.tarea,&pedidos);
    if (ret) {
      v10log(LOGERROR,"%s","vddisp. Error ejecutando procedimiento VDDISP.CALCULADISP\n");
      rollback();  
      return;
    } else {
      commit();
    }
}