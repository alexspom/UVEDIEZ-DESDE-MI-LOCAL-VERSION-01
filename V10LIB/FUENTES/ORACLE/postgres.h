#include "v10.h"
#include "v10db.h"
#include "libpq-fe.h"

#ifndef __LINUX__
__declspec(dllexport) dbdrivers *damedriverpostgre(void);
#else
extern  dbdrivers *damedriverpostgre(void);
#endif