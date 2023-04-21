#include "vd.h"

#define CDAMESID "SELECT VDUSER.GETSID() SID,DBMS_DEBUG_JDWP.CURRENT_SESSION_SERIAL SERIAL FROM DUAL"
static v10cursors *vddamesid=NULL;
#define MAXESPERA 200
void funcactualizasid(void) 
{
	long misid=0,miserial=0,pid;
	int ret;
	vdservicioss ser;
	v10horas init;

	init=damecent();
	vddamesid=abrecursor(CDAMESID);
	definetodo(vddamesid,&misid ,sizeof(misid),V10LONG,
                         &miserial, sizeof(miserial), V10LONG, NULL);
	ret=ejefetchcursor(vddamesid);
	liberacursor(vddamesid);
	vddamesid=NULL;

	pid=GetCurrentProcessId();
	do {
		ret=SERselpid(pid, &ser);
		if (ret==0) {
			ser.sid = misid;
            ser.serial = miserial;
			ret=SERactualizasid(&ser,0);
			commit();
			v10log(LOGNORMAL,"Actualizado SID %d SERIAL %d del proceso con PID %d\n",misid,miserial,pid);
			break;
		}
		Sleep(10);
	} while (damecent()-init < MAXESPERA);
}
