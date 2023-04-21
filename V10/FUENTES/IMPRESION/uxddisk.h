
//<HEADER_BEGIN>
//================================================
//File name: Uxddisk.h
//Date : January, 15 2002  12:15
//Copyright (c) 2002 - Crystal Decisions Corp.
//================================================
//<HEADER_END>

#if !defined (UXDDISK_H)
#define UXDDISK_H

// Set 1-byte structure alignment
#if !defined(PLAT_UNIX) && !defined (MAINWIN)
#if defined (__BORLANDC__)      // Borland C/C++
  #pragma option -a-
#elif defined (_MSC_VER)        // Microsoft Visual C++
  #if _MSC_VER >= 900           // MSVC 2.x and later
    #pragma pack (push)
  #endif
  #pragma pack (1)
#endif
#endif

#if defined (__cplusplus)
extern "C"
{
#endif

#define UXDDiskType             0
#define UXDCurVersion           0x0100

typedef struct UXDDiskOptionsW
{
    WORD structSize;

    wchar_t FAR *fileName;
}
    UXDDiskOptionsW;

#define UXDDiskOptionsWSize      (sizeof (UXDDiskOptionsW))

typedef struct UXDDiskOptionsA
{
    WORD structSize;

    char FAR *fileName;
}
    UXDDiskOptionsA;

#define UXDDiskOptionsASize      (sizeof (UXDDiskOptionsA))

#ifdef UNICODE
typedef UXDDiskOptionsW UXDDiskOptions;
#else
typedef UXDDiskOptionsA UXDDiskOptions;
#endif  //UNICODE

#define UXDDiskOptionsSize      (sizeof (UXDDiskOptions))

#if defined (__cplusplus)
}
#endif

// Reset structure alignment
#if !defined(PLAT_UNIX) && !defined (MAINWIN)
#if defined (__BORLANDC__)
  #pragma option -a.
#elif defined (_MSC_VER)
  #if _MSC_VER >= 900
    #pragma pack (pop)
  #else
    #pragma pack ()
  #endif
#endif
#endif

#endif 

