#define __USE_LARGEFILE64
#ifndef _LARGEFILE_SOURCE
#define _LARGEFILE_SOURCE
#endif
#define _LARGEFILE64_SOURCE

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>
#include <signal.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <dlfcn.h>
#include <errno.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
//#include <sys/wait.h> 
#include <ctype.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/wait.h>
#include <asm/ioctls.h>
#include <termios.h>
//#include <sys/ipc.h>
#include <sys/shm.h>
#include <openssl/sha.h>

#define __argc _argc
#define __argv _argv
#define WCHAR char
#define SEMICOLON ':'
#define BACKSLASH '/'
#define V10WINIMPORT extern
#define V10IMPORT extern
#define V10ORAIMPORT extern
#define V10ORACLEIMPORT extern

#define V10SSLIMPORT extern
#define V10WWWIMPORT extern
#define VDEXPORT     extern
#define NOPARITY     0
#define ONESTOPBIT   1

extern int reusaexcel;

#define VDEXPORT extern
#define FALSE 0
#define TRUE  1

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define MAX_COMPUTERNAME_LENGTH 60
#define stricmp stricomp
#define strnicmp strnicomp
#define chsize ftruncate
#define strcpy strcpyoverlap
#define BYTE unsigned char
#define CopyMemory memcpy

char *strcpyoverlap(char *destino,char *origen);

#define INPUTMASK (ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask)

#define ESTILOV10   0
#define CW_USEDEFAULT 0
#define CW_USEDEFAULT 0
#define WS_OVERLAPPED 0
#define WS_CAPTION 0
#define WS_THICKFRAME 0

#define INVALID_HANDLE_VALUE NULL

#define virtual cvirtual
#define delete  cdelete

typedef void * HINSTANCE;
V10IMPORT HINSTANCE v10hinst, v10hprev;
typedef struct hwnd {
              Window win;
              int    usado;
              void   *t;
              int    invalido;
	          int    sinx;
              } *HWND;
//#define HWND      Window
#define HDC       GC
#define HANDLE    void *
#define HMENU     long
#define POINT     void *
#define LF_FACESIZE MAXPATH
#define HFONT     long
typedef unsigned long COLORREF;
typedef XFontStruct *LOGFONT;
typedef struct tagRECT
{
    long    left;
    long    top;
    long    right;
    long    bottom;
} RECT;
#define HBITMAP   long
#define CALLBACK  long
#define UINT      long
#define WPARAM    long
#define LPARAM    long
#define DWORD     long
#define WORD      long
#define SOCKET    int

#define PASCAL

typedef struct {
    HWND        hwnd;
    UINT        message;
    WPARAM      wParam;
    LPARAM      lParam;
    DWORD       time;
    POINT       pt;
} MSG;
typedef pthread_mutex_t CRITICAL_SECTION;

typedef struct sockaddr  SOCKADDR ;



#define INVALID_SOCKET -1
#define SOCKET_ERROR            (-1)

#define SW_SHOWMAXIMIZED 1
#define SW_SHOWMINIMIZED 2
#define SW_MINIMIZE      2
#define SW_HIDE      3
#define SW_SHOW 3

extern int _argc;
extern char **_argv;
extern int xinvalido;

extern Display *xwindisplay;
extern int bitspixel;

HWND dameventana(Window win);
HWND ventanainvalida(void);
void trataotroevento(XEvent *report);

#define closesocket close
#define ioctlsocket ioctl
void SetWindowText(HWND hwnd,char *titulo);
void Sleep(int mili);


typedef struct _WIN32_FIND_DATA {
  mode_t   dwFileAttributes;
  time_t   ftCreationTime;
  time_t   ftLastAccessTime;
  time_t   ftLastWriteTime;
  off_t    size;
  char     cFileName[MAXPATH];
} WIN32_FIND_DATA, *PWIN32_FIND_DATA, *LPWIN32_FIND_DATA;


#define FILE_ATTRIBUTE_DIRECTORY S_IFDIR
#define FORMAT_MESSAGE_FROM_SYSTEM 0
#define STILL_ACTIVE -1

typedef struct {
         char *path;
         DIR  *dir;
} midir;

typedef long STARTUPINFO;
typedef struct _PROCESS_INFORMATION {
	HANDLE hProcess;
	HANDLE hThread;
	DWORD dwProcessId;
	DWORD dwThreadId;
} PROCESS_INFORMATION, *PPROCESS_INFORMATION, *LPPROCESS_INFORMATION;
typedef long SECURITY_ATTRIBUTES;

typedef void *HMODULE;

HANDLE _beginthread (void *start,int pila,void *param);
HMODULE LoadLibrary(char *nombre);
void *GetProcAddress(HMODULE library,char *nombre);
int FreeLibrary(HMODULE library);
void FindClose(midir *dir);
midir *FindFirstFile(char *path,WIN32_FIND_DATA *data);
int FindNextFile(midir *dir,WIN32_FIND_DATA *data);

char* ltoa(long value, char* result, int base);
char* ultoa(unsigned long value, char* result, int base);

#define HIGH_PRIORITY_CLASS 0
void SetPriorityClass(int pid,int prio);
int FormatMessage(int Flags,char *source,int err,int language,char *donde,int len,void *arg);

int WSAGetLastError(void);

void EnterCriticalSection( CRITICAL_SECTION *lpCriticalSection);
void InitializeCriticalSection(CRITICAL_SECTION *lpCriticalSection);
void LeaveCriticalSection(CRITICAL_SECTION *crit);
void DeleteCriticalSection(CRITICAL_SECTION *crit);
long GetCurrentProcessId(void);
HANDLE CreateThread(void *security,int pila,void *rutina,void *param,int creacion,int *pid);
void TerminateThread(HANDLE thread,int dummy);
void SuspendThread(HANDLE thread);
void ResumeThread(HANDLE thread);
void DestroyWindow(HWND hwnd);
int CreateProcess(char *app, char *cmd, SECURITY_ATTRIBUTES *procatr, SECURITY_ATTRIBUTES *threatr, int hereda, int flags, void *entorno, char *directorio, STARTUPINFO *sti, PROCESS_INFORMATION *pi);
int GetExitCodeProcess(HANDLE pid, DWORD *err);
int TerminateProcess(HANDLE pid, int *status);
int pidetermina(HANDLE pid, int *status);
V10IMPORT int _chsize(int fd,int lon);
void tratasigtermina(void);



extern int oermsg(int err,char *msg);

int WinExec(char *cadena,int flags);


#define SND_ASYNC 0
int sndPlaySound(char *nombre,int flags);

void  InvalidateRect(HWND hwnd,RECT *r,int nose);
void GetWindowRect(HWND hwnddefecto,RECT *rect);

typedef void *HCRYPTKEY;
int damehash(char *origen,char *destino);
HCRYPTKEY dameclave(char *pass);
int genfirma(HCRYPTKEY keysesion,char *priv,char *pub);
int recodificafirma(char *oldpwd,char *newpwd,char *cpriv);

int _putenv(char *variable);