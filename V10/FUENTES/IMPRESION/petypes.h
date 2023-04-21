/*
** File:    petypes.h
**
** Authors: Crystal Decisions, Inc.
** Date:    14 February 2002
**
** Purpose: This file presents the API to the Crystal Reports
**          Print Engine DLL.
**
** Copyright (c) 1991-2002  Crystal Decisions, Inc.
*/

#if !defined (___PETYPES_H_)
#define ___PETYPES_H_

#if defined (CRPE_UNIX)

typedef char *                  PELPSTR;
typedef const char *            PELPCSTR;
typedef unsigned char           PEBYTE;

typedef unsigned short          PEWORD;
typedef long                    PEWCHAR_T;

typedef int                     PEBOOL;
typedef int                     PEHFILE;
typedef unsigned int            PEUINT;

typedef unsigned long           PELCID;
typedef unsigned long           PECOLORREF;
typedef unsigned long           PEULONG;
typedef unsigned long           PEDWORD;

typedef void                    PEDEVMODEA;
typedef void                    PEDEVMODEW;
typedef void *                  PEHANDLE;

  #define PECALLBACK
  #define PENULL                  0
const PEBOOL PEFALSE = 0, PETRUE = 1;

  #if !defined (FAR)
    #define                     FAR
  #endif

  #define DECLARE_PE_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name
DECLARE_PE_HANDLE           (PEHWND);

  #define PE_FF_DONTCARE      0
  #define PE_DEFAULT_PITCH    0
  #define PE_DEFAULT_CHARSET  1

extern void *memset (void *dest, int c, size_t count);

#else
//default to CRPE_WIN
typedef LPSTR                   PELPSTR;
typedef LPCSTR                  PELPCSTR;
typedef BYTE                    PEBYTE;

typedef WORD                    PEWORD;
typedef wchar_t                 PEWCHAR_T;

typedef BOOL                    PEBOOL;
typedef HFILE                   PEHFILE;
typedef UINT                    PEUINT;

typedef LCID                    PELCID;
typedef COLORREF                PECOLORREF;
typedef ULONG                   PEULONG;
typedef DWORD                   PEDWORD;

typedef DEVMODEA                PEDEVMODEA;
typedef DEVMODEW                PEDEVMODEW;
typedef HANDLE                  PEHANDLE;
typedef HWND                    PEHWND;

  #define PECALLBACK              CALLBACK
  #define PENULL                  NULL
  #define PEFALSE                 FALSE
  #define PETRUE                  TRUE

  #define PE_FF_DONTCARE          FF_DONTCARE
  #define PE_DEFAULT_PITCH        DEFAULT_PITCH
  #define PE_DEFAULT_CHARSET      DEFAULT_CHARSET

#endif //defined (CRPE_UNIX)



#endif //ndef ___PETYPES_H_

