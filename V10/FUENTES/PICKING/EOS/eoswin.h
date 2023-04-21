
#include "v10.h"
//#include "winsock.h"
//#include <winsock2.h>
//#include <ws2tcpip.h>
//#include <sys/timeb.h>

typedef void pthread_attr_t;
typedef struct timeval timeval;
typedef struct sockaddr sockaddr;
typedef DWORD pthread_t;
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,void *(*start_routine)(void*), void *arg);
int nanosleep(const struct timeval *reqt,struct timeval *remt); 
int usleep(int useconds);
