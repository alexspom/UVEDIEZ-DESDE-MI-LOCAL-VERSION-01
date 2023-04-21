#include "v10.h"
#ifndef WIN32
#include <sys/timeb.h>
#endif
typedef struct timeval timeval;
typedef struct sockaddr sockaddr;

int pthread_create(DWORD *thread, const void *attr,void *(*start_routine)(void*), void *arg);
int nanosleep(const struct timeval *reqt,struct timeval *remt); 
int usleep(int useconds);
