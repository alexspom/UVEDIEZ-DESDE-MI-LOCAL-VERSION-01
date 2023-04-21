/*
** File:    CRPE.h
**
** Authors: Crystal Decisions, Inc.
** Date:    13 Nov 91
**
** Purpose: This file presents the API to the Crystal Reports
**          Print Engine DLL.
**
** Copyright (c) 1991-2002  Crystal Decisions, Inc.
*/

#if !defined (CRPE_H)
#define CRPE_H

#if !defined (___PETYPES_H_)
    #include "petypes.h"
#endif

// Set 1-byte structure alignment
#if defined (__BORLANDC__)      // Borland C/C++
  #pragma option -a-
#elif defined (_MSC_VER)        // Microsoft Visual C++
  #if _MSC_VER >= 900           // MSVC 2.x and later
    #pragma pack (push)
    #pragma comment (lib, "crpe32m.lib") // Point to Microsoft Lib File
  #endif
  #pragma pack (1)
#endif

#if defined (__cplusplus)
extern "C"
{
#endif

/*********************************************/
// CRPE error code
/*********************************************/
#define PE_ERR_NOERROR                      0

#define PE_ERR_NOTENOUGHMEMORY              500
#define PE_ERR_INVALIDJOBNO                 501
#define PE_ERR_INVALIDHANDLE                502
#define PE_ERR_STRINGTOOLONG                503
#define PE_ERR_NOSUCHREPORT                 504
#define PE_ERR_NODESTINATION                505
#define PE_ERR_BADFILENUMBER                506
#define PE_ERR_BADFILENAME                  507
#define PE_ERR_BADFIELDNUMBER               508
#define PE_ERR_BADFIELDNAME                 509
#define PE_ERR_BADFORMULANAME               510
#define PE_ERR_BADSORTDIRECTION             511
#define PE_ERR_ENGINENOTOPEN                512
#define PE_ERR_INVALIDPRINTER               513
#define PE_ERR_PRINTFILEEXISTS              514
#define PE_ERR_BADFORMULATEXT               515
#define PE_ERR_BADGROUPSECTION              516
#define PE_ERR_ENGINEBUSY                   517
#define PE_ERR_BADSECTION                   518
#define PE_ERR_NOPRINTWINDOW                519
#define PE_ERR_JOBALREADYSTARTED            520
#define PE_ERR_BADSUMMARYFIELD              521
#define PE_ERR_NOTENOUGHSYSRES              522
#define PE_ERR_BADGROUPCONDITION            523
#define PE_ERR_JOBBUSY                      524
#define PE_ERR_BADREPORTFILE                525
#define PE_ERR_NODEFAULTPRINTER             526
#define PE_ERR_SQLSERVERERROR               527
#define PE_ERR_BADLINENUMBER                528
#define PE_ERR_DISKFULL                     529
#define PE_ERR_FILEERROR                    530
#define PE_ERR_INCORRECTPASSWORD            531
#define PE_ERR_BADDATABASEDLL               532
#define PE_ERR_BADDATABASEFILE              533
#define PE_ERR_ERRORINDATABASEDLL           534
#define PE_ERR_DATABASESESSION              535
#define PE_ERR_DATABASELOGON                536
#define PE_ERR_DATABASELOCATION             537
#define PE_ERR_BADSTRUCTSIZE                538
#define PE_ERR_BADDATE                      539
#define PE_ERR_BADEXPORTDLL                 540
#define PE_ERR_ERRORINEXPORTDLL             541
#define PE_ERR_PREVATFIRSTPAGE              542
#define PE_ERR_NEXTATLASTPAGE               543
#define PE_ERR_CANNOTACCESSREPORT           544
#define PE_ERR_USERCANCELLED                545
#define PE_ERR_OLE2NOTLOADED                546
#define PE_ERR_BADCROSSTABGROUP             547
#define PE_ERR_NOCTSUMMARIZEDFIELD          548
#define PE_ERR_DESTINATIONNOTEXPORT         549
#define PE_ERR_INVALIDPAGENUMBER            550
#define PE_ERR_NOTSTOREDPROCEDURE           552
#define PE_ERR_INVALIDPARAMETER             553
#define PE_ERR_GRAPHNOTFOUND                554
#define PE_ERR_INVALIDGRAPHTYPE             555
#define PE_ERR_INVALIDGRAPHDATA             556
#define PE_ERR_CANNOTMOVEGRAPH              557
#define PE_ERR_INVALIDGRAPHTEXT             558
#define PE_ERR_INVALIDGRAPHOPT              559
#define PE_ERR_BADSECTIONHEIGHT             560
#define PE_ERR_BADVALUETYPE                 561
#define PE_ERR_INVALIDSUBREPORTNAME         562
#define PE_ERR_NOPARENTWINDOW               564 // dialog parent window
#define PE_ERR_INVALIDZOOMFACTOR            565 // zoom factor
#define PE_ERR_PAGESIZEOVERFLOW             567
#define PE_ERR_LOWSYSTEMRESOURCES           568
#define PE_ERR_BADGROUPNUMBER               570
#define PE_ERR_INVALIDOBJECTFORMATNAME      571
#define PE_ERR_INVALIDNEGATIVEVALUE         572
#define PE_ERR_INVALIDMEMORYPOINTER         573
#define PE_ERR_INVALIDOBJECTTYPE            574
#define PE_ERR_INVALIDGRAPHDATATYPE         577
#define PE_ERR_INVALIDSUBREPORTLINKNUMBER   582
#define PE_ERR_SUBREPORTLINKEXIST           583
#define PE_ERR_BADROWCOLVALUE               584
#define PE_ERR_INVALIDSUMMARYNUMBER         585
#define PE_ERR_INVALIDGRAPHDATAFIELDNUMBER  586
#define PE_ERR_INVALIDSUBREPORTNUMBER       587
#define PE_ERR_INVALIDFIELDSCOPE            588
#define PE_ERR_FIELDINUSE                   590
#define PE_ERR_INVALIDPARAMETERNUMBER       594
#define PE_ERR_INVALIDPAGEMARGINS           595
#define PE_ERR_REPORTONSECUREQUERY          596
#define PE_ERR_CANNOTOPENSECUREQUERY        597
#define PE_ERR_INVALIDSECTIONNUMBER         598
#define PE_ERR_SQLSERVERNOTOPENED           599
#define PE_ERR_TABLENAMEEXIST               606
#define PE_ERR_INVALIDCURSOR                607
#define PE_ERR_FIRSTPASSNOTFINISHED         608
#define PE_ERR_CREATEDATASOURCE             609
#define PE_ERR_CREATEDRILLDOWNPARAMETERS    610
#define PE_ERR_CHECKFORDATASOURCECHANGES    613
#define PE_ERR_STARTBACKGROUNDPROCESSING    614
#define PE_ERR_SQLSERVERINUSE               619
#define PE_ERR_GROUPSORTFIELDNOTSET         620
#define PE_ERR_CANNOTSETSAVESUMMARIES       621
#define PE_ERR_LOADOLAPDATABASEMANAGER      622
#define PE_ERR_OPENOLAPCUBE                 623
#define PE_ERR_READOLAPCUBEDATA             624
#define PE_ERR_CANNOTSAVEQUERY              626
#define PE_ERR_CANNOTREADQUERYDATA          627
#define PE_ERR_MAINREPORTFIELDLINKED        629
#define PE_ERR_INVALIDMAPPINGTYPEVALUE      630
#define PE_ERR_HITTESTFAILED                636
#define PE_ERR_BADSQLEXPRESSIONNAME         637 // no SQL expression by the specified *name* exists in this report.
#define PE_ERR_BADSQLEXPRESSIONNUMBER       638 // no SQL expression by the specified *number* exists in this report.
#define PE_ERR_BADSQLEXPRESSIONTEXT         639 // not a valid SQL expression
#define PE_ERR_INVALIDDEFAULTVALUEINDEX     641 // invalid index for default value of a parameter.
#define PE_ERR_NOMINMAXVALUE                642 // the specified PE_PF_* type does not have min/max values.
#define PE_ERR_INCONSISTANTTYPES            643 // if both min and max values are specified in PESetParameterMinMaxValue,
                                                // the value types for the min and max must be the same.

#define PE_ERR_CANNOTLINKTABLES             645
#define PE_ERR_CREATEROUTER                 646

#define PE_ERR_INVALIDFIELDINDEX            647
#define PE_ERR_INVALIDGRAPHTITLETYPE        648
#define PE_ERR_INVALIDGRAPHTITLEFONTTYPE    649

#define PE_ERR_PARAMTYPEDIFFERENT           650 // the type used in a add/set value API for a
                                                // parameter differs with it's existing type.
#define PE_ERR_INCONSISTANTRANGETYPES       651 // the value type for both start & end range
                                                // values must be the same.
#define PE_ERR_RANGEORDISCRETE              652 // an operation was attempted on a discrete parameter that is
                                                // only legal for range parameters or vice versa.

#define PE_ERR_NOTMAINREPORT                654 // an operation was attempted that is disallowed for subreports.
#define PE_ERR_INVALIDCURRENTVALUEINDEX     655 // invalid index for current value of a parameter.
#define PE_ERR_LINKEDPARAMVALUE             656 // operation illegal on linked parameter.

#define PE_ERR_INVALIDPARAMETERRANGEINFO    672 // Invalid PE_RI_* combination.
#define PE_ERR_INVALIDSORTMETHODINDEX       674 // Invalid sort method index.

#define PE_ERR_INVALIDGRAPHSUBTYPE          675 // Invalid PE_GST_* or 
                                                // PE_GST_* does not match PE_GT_* or 
                                                // PE_GST_* current graph type.
#define PE_ERR_BADGRAPHOPTIONINFO           676 // one of the members of PEGraphOptionInfo is out of range.
#define PE_ERR_BADGRAPHAXISINFO             677 // one of the members of PEGraphAxisInfo is out of range.

#define PE_ERR_NOTEXTERNALSUBREPORT         680 // the subreport is not imported.
#define PE_ERR_INVALIDPARAMETERVALUE        687
#define PE_ERR_INVALIDFORMULASYNTAXTYPE     688 // specified formula syntax not in PE_FST_*
#define PE_ERR_INVALIDCROPVALUE             689
#define PE_ERR_INVALIDCOLLATIONVALUE        690
#define PE_ERR_STARTPAGEGREATERSTOPPAGE     691
#define PE_ERR_INVALIDEXPORTFORMAT          692

#define PE_ERR_READONLYPARAMETEROPTION      700 // This parameter option is read only and cannot be changed.
#define PE_ERR_MINGREATERTHANMAX            702 // The minimum cannot be greater than the maximum
#define PE_ERR_INVALIDSTARTPAGE             703 // Specified start page is greater than the last page on the report.
#define PE_ERR_MBCS2UNICODE                 994 // error converting from MBCS to UNICODE
#define PE_ERR_UNICODE2MBCS                 995 // error converting from UNICODE to MBCS
#define PE_ERR_INVALID_PEENUM               996 // some PE_xx_yyyy is not in the specified allowable range.
#define PE_ERR_OTHERERROR                   997
#define PE_ERR_INTERNALERROR                998 // programming error
#define PE_ERR_NOTIMPLEMENTED               999

/*************************************/
// unchanged constant
/*************************************/
#define PE_UNCHANGED       -1
#define PE_UNCHANGED_COLOR (PECOLORREF) -2
#define PE_NO_COLOR  (unsigned long) 0xffffffffL

#if !defined (CRPE_UNIX)
#   if defined (_WINDLL)
#       define CRPE_API /* __declspec(dllexport) */ WINAPI
#   else
#      define CRPE_API __stdcall
#   endif
#else
#   define CRPE_API
#endif


/**********************************/
// Open and close print engine
/***********************************/
PEBOOL CRPE_API PEOpenEngine (void);
void CRPE_API PECloseEngine (void);
PEBOOL CRPE_API PECanCloseEngine (void);

/*************************************/
// Get version info
/*************************************/
#define PE_GV_DLL     100
#define PE_GV_ENGINE  200

short CRPE_API PEGetVersion (short versionRequested);

/*********************************************/
// the version number of the .rpt file format
/*********************************************/

typedef struct PEVersionInfo
{
#if defined (__cplusplus)
    PEVersionInfo ()
    {
        StructSize = sizeof (PEVersionInfo);
        major = 0;
        minor = 0;
        letter = 0;
    };
#endif

    PEWORD StructSize;  // initialize to PE_SIZEOF_VERSION_INFO
    PEWORD major;
    PEWORD minor;
    char letter;
} PEVersionInfo;
#define PE_SIZEOF_VERSION_INFO (sizeof(PEVersionInfo))

PEBOOL CRPE_API PEGetReportVersion( short printJob, 
                                  PEVersionInfo FAR* pVersionInfo );

/*************************************************************************/
// Open, print and close report (used when no changes needed to report)
/*************************************************************************/
short CRPE_API PEPrintReport (const char FAR *reportFilePath,
                              PEBOOL toDefaultPrinter,
                              PEBOOL toWindow,
                              const char FAR *title,
                              int left,
                              int top,
                              int width,
                              int height,
                              PEDWORD style,
                              PEHWND parentWindow);


#define PE_RPTOPT_CVTDATETIMETOSTR  0
#define PE_RPTOPT_CVTDATETIMETODATE 1
#define PE_RPTOPT_KEEPDATETIMETYPE  2

//Following are the valid values for promptMode
#define PE_RPTOPT_PROMPT_NONE 0
#define PE_RPTOPT_PROMPT_NORMAL 1
#define PE_RPTOPT_PROMPT_ALWAYS 2

/*******************************************/
// report options
/********************************************/
typedef struct PEReportOptions
{
#if defined (__cplusplus)
    PEReportOptions ()
    {
        StructSize = sizeof (PEReportOptions);
        saveDataWithReport = PE_UNCHANGED;
        saveSummariesWithReport = PE_UNCHANGED;
        useIndexForSpeed = PE_UNCHANGED;
        translateDOSStrings = PE_UNCHANGED;
        translateDOSMemos = PE_UNCHANGED;
        convertDateTimeType = PE_UNCHANGED;
        convertNullFieldToDefault = PE_UNCHANGED;
        morePrintEngineErrorMessages = PE_UNCHANGED;
        caseInsensitiveSQLData = PE_UNCHANGED;
        verifyOnEveryPrint = PE_UNCHANGED;
        zoomMode = PE_UNCHANGED;
        hasGroupTree = PE_UNCHANGED;
        dontGenerateDataForHiddenObjects = PE_UNCHANGED;
        performGroupingOnServer = PE_UNCHANGED;
        doAsyncQuery = PE_UNCHANGED;
        promptMode = PE_UNCHANGED;
        selectDistinctRecords = PE_UNCHANGED;
        alwaysSortLocally = PE_UNCHANGED;
        isReadOnly = PE_UNCHANGED;
        canSelectDistinctRecords = PE_UNCHANGED;
        useDummyData = PE_UNCHANGED;
        convertAllNullsToDefault = PE_UNCHANGED;
    };
#endif

    PEWORD StructSize;  // initialize to PE_SIZEOF_REPORT_OPTIONS
    short saveDataWithReport;  // PEBOOL value, except use PE_UNCHANGED for no change
    short saveSummariesWithReport;  // PEBOOL value, except use PE_UNCHANGED for no change
    short useIndexForSpeed;    // PEBOOL value, except use PE_UNCHANGED for no change
    short translateDOSStrings; // PEBOOL value, except use PE_UNCHANGED for no change
    short translateDOSMemos;   // PEBOOL value, except use PE_UNCHANGED for no change
    short convertDateTimeType; // a PE_RPTOPT_ value, except use PE_UNCHANGED for no change
    short convertNullFieldToDefault; // PEBOOL value, except use PE_UNCHANGED for no change
                                     // This corresponds to 'Convert NULL Values from Database to Default'
    short morePrintEngineErrorMessages;// PEBOOL value, except use PE_UNCHANGED for no change
    short caseInsensitiveSQLData; // PEBOOL value, except use PE_UNCHANGED for no change
    short verifyOnEveryPrint;     // PEBOOL value, except use PE_UNCHAGED for no change
    short zoomMode;                //  a PE_ZOOM_ constant, except use PE_UNCHANGED for no change
    short hasGroupTree;           // PEBOOL value, except use PE_UNCHANGED for no change
    short dontGenerateDataForHiddenObjects; // PEBOOL value, except use PE_UNCHANGED for no change
    short performGroupingOnServer;           // PEBOOL value, except use PE_UNCHANGED for no change
    short doAsyncQuery; // PEBOOL value, except use PE_UNCHANGED for no change
    short promptMode; // PE_RPTOPT_PROMPT_NONE, PE_RPTOPT_PROMPT_NORMAL, PE_RPTOPT_PROMPT_ALWAYS, use PE_UNCHANGED for no change
    short selectDistinctRecords; // PEBOOL value, except use PE_UNCHANGED for no change
    short alwaysSortLocally; // PEBOOL value, except use PE_UNCHANGED for no change
    short isReadOnly; // PEBOOL value,  a read-only attribute.  PESetReportOptions simply ignores it.
    short canSelectDistinctRecords; // PEBOOL value,  a read-only attribute.  PESetReportOptions simply ignore it
    short useDummyData; // PEBOOL value, except use PE_UNCHANGED for no change
    short convertAllNullsToDefault; //  PEBOOL value, except use PE_UNCHANGED for no change
}PEReportOptions;
#define PE_SIZEOF_REPORT_OPTIONS (sizeof(PEReportOptions))

PEBOOL CRPE_API PEGetReportOptions (short printJob,
                                  PEReportOptions FAR * reportOptions);
PEBOOL CRPE_API PESetReportOptions (short printJob,
                                  PEReportOptions FAR * reportOptions);

/***************************************************/
// print job
/***************************************************/
short CRPE_API PEOpenPrintJob (const char FAR *reportFilePath);
PEBOOL CRPE_API PEClosePrintJob (short printJob);

PEBOOL CRPE_API PEStartPrintJob (short printJob,
                               PEBOOL waitUntilDone);
void CRPE_API PECancelPrintJob (short printJob);

// open and close subreport
short CRPE_API PEOpenSubreport (short parentJob,
                                const char FAR *subreportName);
PEBOOL CRPE_API PECloseSubreport (short printJob);

// Print job status
// ----------------

PEBOOL CRPE_API PEIsPrintJobFinished (short printJob);

#define PE_JOBNOTSTARTED 1
#define PE_JOBINPROGRESS 2
#define PE_JOBCOMPLETED  3
#define PE_JOBFAILED     4  // an error occurred
#define PE_JOBCANCELLED  5  // by user
#define PE_JOBHALTED     6  // too many records or too much time

typedef struct PEJobInfo
{
#if defined (__cplusplus)
    PEJobInfo ()
    {
        StructSize = sizeof (PEJobInfo);
        NumRecordsRead = 0;
        NumRecordsSelected = 0;
        NumRecordsPrinted = 0;
        DisplayPageN = 0;
        LatestPageN = 0;
        StartPageN = 0;
        printEnded = PEFALSE;
    };
#endif

    PEWORD StructSize;    // initialize to PE_SIZEOF_JOB_INFO

    PEDWORD NumRecordsRead,
          NumRecordsSelected,
          NumRecordsPrinted;
    PEWORD  DisplayPageN, // the page being displayed in window
          LatestPageN,  // the page being generated
          StartPageN;   // user opted, default to 1
    PEBOOL  printEnded;   // full report print completed?
}PEJobInfo;
#define PE_SIZEOF_JOB_INFO (sizeof (PEJobInfo))

short CRPE_API PEGetJobStatus (short printJob,
                               PEJobInfo FAR *jobInfo);

/***************************************/
// Controlling dialogs
/***************************************/
PEBOOL CRPE_API PESetDialogParentWindow (short printJob,
                                       PEHWND parentWindow);

PEBOOL CRPE_API PEEnableProgressDialog (short printJob,
                                      PEBOOL enable);
/***********************************************/
// Controlling Parameter Field Prompting Dialog
/***********************************************/

// Set boolean to indicate whether CRPE is allowed to prompt for parameter values
// during printing.

PEBOOL CRPE_API PEGetAllowPromptDialog(short printJob);
PEBOOL CRPE_API PESetAllowPromptDialog(short printJob, PEBOOL showPromptDialog);

/*******************************************/
// Print job error codes and messages
/******************************************/

short CRPE_API PEGetErrorCode (short printJob);
PEBOOL  CRPE_API PEGetErrorText (short printJob,
                               PEHANDLE FAR *textHandle,
                               short  FAR *textLength);

PEBOOL  CRPE_API PEGetHandleString (PEHANDLE textHandle,
                                  char FAR *buffer,
                                  short bufferLength);

/*************************************/
// Getting and setting the print date
/*************************************/
PEBOOL CRPE_API PEGetPrintDate (short printJob,
                              short FAR *year,
                              short FAR *month,
                              short FAR *day);

PEBOOL CRPE_API PESetPrintDate (short printJob,
                              short year,
                              short month,
                              short day);

/********************************************/
// Area, section and group operations
/********************************************/
#define PE_ALLSECTIONS           0

// A macro to create section codes:
// (This representation allows up to 25 groups and 40 sections of a given
// type, although Crystal Reports itself has no such limitations.)
#define PE_SECTION_CODE(sectionType,groupN,sectionN) \
    (((sectionType) * 1000) + ((groupN) % 25) + (((sectionN) % 40) * 25))

// A macro to create area codes:
#define PE_AREA_CODE(sectionType,groupN) \
    PE_SECTION_CODE (sectionType, groupN, 0)

// Section types:
#define PE_SECT_PAGE_HEADER      2
#define PE_SECT_PAGE_FOOTER      7
#define PE_SECT_REPORT_HEADER    1
#define PE_SECT_REPORT_FOOTER    8
#define PE_SECT_GROUP_HEADER     3
#define PE_SECT_GROUP_FOOTER     5
#define PE_SECT_DETAIL           4

// Macros to decode section and area codes:
#define PE_SECTION_TYPE(sectionCode) ((sectionCode) / 1000)
#define PE_GROUP_N(sectionCode)      ((sectionCode) % 25)
#define PE_SECTION_N(sectionCode)    (((sectionCode) / 25) % 40)

// The old section constants redefined in terms of the new:
// (Note that PE_GRANDTOTALSECTION and PE_SUMMARYSECTION both map
// to PE_SECT_REPORT_FOOTER.)
#define PE_HEADERSECTION      PE_SECTION_CODE (PE_SECT_PAGE_HEADER,   0, 0)
#define PE_FOOTERSECTION      PE_SECTION_CODE (PE_SECT_PAGE_FOOTER,   0, 0)
#define PE_TITLESECTION       PE_SECTION_CODE (PE_SECT_REPORT_HEADER, 0, 0)
#define PE_SUMMARYSECTION     PE_SECTION_CODE (PE_SECT_REPORT_FOOTER, 0, 0)
#define PE_GROUPHEADER        PE_SECTION_CODE (PE_SECT_GROUP_HEADER,  0, 0)
#define PE_GROUPFOOTER        PE_SECTION_CODE (PE_SECT_GROUP_FOOTER,  0, 0)
#define PE_DETAILSECTION      PE_SECTION_CODE (PE_SECT_DETAIL,        0, 0)
#define PE_GRANDTOTALSECTION  PE_SUMMARYSECTION

// Controlling group conditions (i.e. group breaks)
#define PE_SF_MAX_NAME_LENGTH 50

#define PE_SF_DESCENDING 0
#define PE_SF_ASCENDING  1
#define PE_SF_ORIGINAL   2 // only for group condition
#define PE_SF_SPECIFIED  3 // only for group condition


// use PE_ANYCHANGE for all field types except Date
#define PE_GC_ANYCHANGE    0

// use these constants for Date and DateTime fields
#define PE_GC_DAILY        0
#define PE_GC_WEEKLY       1
#define PE_GC_BIWEEKLY     2
#define PE_GC_SEMIMONTHLY  3
#define PE_GC_MONTHLY      4
#define PE_GC_QUARTERLY    5
#define PE_GC_SEMIANNUALLY 6
#define PE_GC_ANNUALLY     7

// use these constants for Time  and DateTime fields
#define PE_GC_BYSECOND     8
#define PE_GC_BYMINUTE     9
#define PE_GC_BYHOUR       10
#define PE_GC_BYAMPM       11

// use these constants for Boolean fields
#define PE_GC_TOYES        1
#define PE_GC_TONO         2
#define PE_GC_EVERYYES     3
#define PE_GC_EVERYNO      4
#define PE_GC_NEXTISYES    5
#define PE_GC_NEXTISNO     6

PEBOOL CRPE_API PESetGroupCondition (short printJob,
                                   short sectionCode,
                                   const char FAR *conditionField, // formula form
                                   short condition,       // a PE_GC_ constant
                                   short sortDirection);  // a PE_SF_ constant

short CRPE_API PEGetNGroups (short printJob);  // return -1 if failed.


// for PEGetGroupCondition, condition encodes both
// the condition and the type of the condition field
#define PE_GC_CONDITIONMASK   0x00FF
#define PE_GC_TYPEMASK        0x0F00

#define PE_GC_TYPEOTHER       0x0000
#define PE_GC_TYPEDATE        0x0200
#define PE_GC_TYPEBOOLEAN     0x0400
#define PE_GC_TYPETIME        0x0800

PEBOOL CRPE_API PEGetGroupCondition (short printJob,
                                   short sectionCode,
                                   PEHANDLE FAR *conditionFieldHandle,
                                   short  FAR *conditionFieldLength,
                                   short  FAR *condition,
                                   short  FAR *sortDirection);

#define PE_FIELD_NAME_LEN 512

#define PE_GO_TBN_ALL_GROUPS_UNSORTED   0
#define PE_GO_TBN_ALL_GROUPS_SORTED     1
#define PE_GO_TBN_TOP_N_GROUPS          2
#define PE_GO_TBN_BOTTOM_N_GROUPS       3

typedef struct PEGroupOptions
{
#if defined (__cplusplus)
    PEGroupOptions ()
    {
        StructSize = sizeof (PEGroupOptions);
        condition = PE_UNCHANGED;
        fieldName [0] = '\0';
        sortDirection = PE_UNCHANGED;
        repeatGroupHeader = PE_UNCHANGED;
        keepGroupTogether = PE_UNCHANGED;
        topOrBottomNGroups = PE_UNCHANGED;
        topOrBottomNSortFieldName [0] = '\0';
        nTopOrBottomGroups = PE_UNCHANGED;
        discardOtherGroups = PE_UNCHANGED;
        hierarchicalSorting = PE_UNCHANGED;
        instanceIDField [0] = '\0';
        parentIDField [0] = '\0';
        groupIndent = PE_UNCHANGED;
        customizeGroupName = PE_UNCHANGED;
        notInTopOrBottomNName [0] = '\0';
    };
#endif

    PEWORD    StructSize;
     // when setting, pass a PE_GC_ constant, or PE_UNCHANGED for no change.
    // when getting, use PE_GC_TYPEMASK and PE_GC_CONDITIONMASK to
    // decode the condition.
    short   condition;
    char    fieldName [PE_FIELD_NAME_LEN]; // formula form, or empty for no change.
    short   sortDirection;                // a PE_SF_ const, or PE_UNCHANGED for no change.
    short   repeatGroupHeader;            // PEBOOL value, or PE_UNCHANGED for no change.
    short   keepGroupTogether;            // PEBOOL value, or PE_UNCHANGED for no change.
    short   topOrBottomNGroups;           // a PE_GO_TBN_ constant, or PE_UNCHANGED for no change.
    char    topOrBottomNSortFieldName [PE_FIELD_NAME_LEN]; // formula form, or empty for no change.
    short   nTopOrBottomGroups;           // the number of groups to keep, 0 for all, or PE_UNCHANGED for no change.
    short   discardOtherGroups;           // PEBOOL value, or PE_UNCHANGED for no change.
    short   ignored;                                // for 4 byte alignment. ignored.
    short   hierarchicalSorting;                    // Boolean or PE_UNCHANGED
    char    instanceIDField [PE_FIELD_NAME_LEN];    // for hierarchical grouping
    char    parentIDField [PE_FIELD_NAME_LEN];      // for hierarchical grouping
    long    groupIndent;                            // twips
    short   customizeGroupName;               //PEBOOL or PE_UNCHANGED
    char    notInTopOrBottomNName [PE_FIELD_NAME_LEN]; // empty for no change.
}
    PEGroupOptions;
#define PE_SIZEOF_GROUP_OPTIONS (sizeof (PEGroupOptions))

PEBOOL CRPE_API PEGetGroupOptions(short printJob,
                                short groupN,
                                PEGroupOptions FAR * groupOptions);
PEBOOL CRPE_API PESetGroupOptions(short printJob,
                                short groupN,
                                PEGroupOptions FAR * groupOptions);

//Get number of sections
short CRPE_API PEGetNSections (short printJob); // return -1 if failed
short CRPE_API PEGetNSectionsInArea(short printJob, short areaCode); // return -1 if failed

short CRPE_API PEGetSectionCode (short printJob,  // return 0 if failed
                                 short sectionN); // range within the number from PEGetNSections

// Setting section/area height
// This is the replacement API Call for PEGetMinimumSectionHeight which is obsolete.
// The obsolete API will still work for older applications, but use this for all new development
PEBOOL CRPE_API PEGetSectionHeight(short printJob,
                                 short sectionCode,
                                 short FAR * height); // Twips

// This is the replacement API Call for PESetMinimumSectionHeight which is obsolete.
// The obsolete API will still work for older applications, but use this for all new development
PEBOOL CRPE_API PESetSectionHeight (short printJob,
                                  short sectionCode,
                                  short height); // twips

// area or section format.
typedef struct PESectionOptions // For area options, too.
{
#if defined (__cplusplus)
    PESectionOptions ()
    {
        StructSize = sizeof (PESectionOptions);
        visible = PE_UNCHANGED;
        newPageBefore = PE_UNCHANGED;
        newPageAfter = PE_UNCHANGED;
        keepTogether = PE_UNCHANGED;
        suppressBlankSection = PE_UNCHANGED;
        resetPageNAfter = PE_UNCHANGED;
        printAtBottomOfPage = PE_UNCHANGED;
        backgroundColor = PE_UNCHANGED_COLOR;
        underlaySection = PE_UNCHANGED;
        showArea = PE_UNCHANGED;
        freeFormPlacement = PE_UNCHANGED;
        reserveMinimumPageFooter = PE_UNCHANGED;
        hCssClass = 0;
        cssClassLen = PE_UNCHANGED;
    };
#endif

    PEWORD StructSize;            // initialize to PE_SIZEOF_SECTION_OPTIONS

    short visible,              // PEBOOL values, except use PE_UNCHANGED
          newPageBefore,        // to preserve the existing settings
          newPageAfter,
          keepTogether,
          suppressBlankSection,
          resetPageNAfter,
          printAtBottomOfPage;
    PECOLORREF backgroundColor;   // Use PE_UNCHANGED_COLOR to preserve the
                                // existing color. only for section format
    short underlaySection;      // PEBOOL values, except use PE_UNCHANGED
    short showArea;             // to preserve the existing settings
    short freeFormPlacement;
    short reserveMinimumPageFooter;   // choose the maximum visible page footer section 
                                      // as reserve.
    PEHANDLE  hCssClass;            // handle to styleclass contents (string).
    short   cssClassLen;          // length in bytes of hStyleClass,
}PESectionOptions;
#define PE_SIZEOF_SECTION_OPTIONS (sizeof (PESectionOptions))

PEBOOL CRPE_API PESetSectionFormat (short printJob,
                                  short sectionCode,
                                  PESectionOptions FAR *options);

PEBOOL CRPE_API PEGetSectionFormat (short printJob,
                                  short sectionCode,
                                  PESectionOptions FAR *options);

PEBOOL CRPE_API PESetAreaFormat (short printJob,
                               short areaCode,
                               PESectionOptions FAR *options);

PEBOOL CRPE_API PEGetAreaFormat (short printJob,
                               short areaCode,
                               PESectionOptions FAR *options);

// Setting font and color info
#define PE_FIELDS    0x0001
#define PE_TEXT      0x0002

PEBOOL CRPE_API PESetFont (short printJob,
                         short sectionCode,
                         short scopeCode,     // PE_FIELDS or PE_TEXT
                         const char FAR *faceName,  // 0 for no change
                         short fontFamily,    // PE_FF_DONTCARE for no change
                         short fontPitch,     // PE_DEFAULT_PITCH for no change
                         short charSet,       // PE_DEFAULT_CHARSET for no change
                         short pointSize,     // 0 for no change
                         short isItalic,      // PE_UNCHANGED for no change
                         short isUnderlined,  // ditto
                         short isStruckOut,   // ditto
                         short weight);       // 0 for no change

// Subreport object
short CRPE_API PEGetNSubreportsInSection (short printJob,
                                          short sectionCode);

PEDWORD CRPE_API PEGetNthSubreportInSection (short printJob,
                                           short sectionCode,
                                           short subreportN);

#define PE_SUBREPORT_NAME_LEN 128
// PE_SRI_ONOPENJOB: Reimport the subreport when opening the main report.
// PE_SRI_ONFUNCTIONCALL: Reimport the subreport when the api is called.
#define PE_SRI_UNDEFINED     -1
#define PE_SRI_ONOPENJOB      0
#define PE_SRI_ONFUNCTIONCALL 1

typedef struct PESubreportInfo
{
#if defined (__cplusplus)
    PESubreportInfo ()
    {
        StructSize = sizeof (PESubreportInfo);
        name [0] = '\0';
        NLinks = 0;
        isOnDemand = PE_UNCHANGED;
        external = PE_UNCHANGED;
        reimportOption = PE_UNCHANGED;
    };
#endif

    PEWORD StructSize;            // Initialize to PE_SIZEOF_SUBREPORT_INFO.
    // Strings are null-terminated.
    char name [PE_SUBREPORT_NAME_LEN];

    // number of links
    short NLinks;
    // subreport placement.
    short isOnDemand;    // PETRUE if the subreport is on demand subreport.
    
    short external;         // 1: the subreport is imported; 0: otherwise.
    short reimportOption;   // PE_SRI_ONOPENJOB or PE_SRI_ONFUNCTIONCALL
                            // This value is ignored if the subreport is
                            // not imported (value of external is 0).
} PESubreportInfo;
#define PE_SIZEOF_SUBREPORT_INFO (sizeof (PESubreportInfo))

PEBOOL CRPE_API PEGetSubreportInfo (short printJob,
                                  PEDWORD subreportHandle,
                                  PESubreportInfo FAR *subreportInfo);

PEBOOL CRPE_API PEReimportSubreport(short printJob,
                                  PEDWORD subreportHandle,
                                  PEBOOL FAR * linkChanged,
                                  PEBOOL FAR * reimported);

/* *************************************** */
/*        GRAPHING                         */
/* *************************************** */
//graph type

#define PE_GT_BARCHART              0
#define PE_GT_LINECHART             1
#define PE_GT_AREACHART             2
#define PE_GT_PIECHART              3
#define PE_GT_DOUGHNUTCHART         4
#define PE_GT_THREEDRISERCHART      5
#define PE_GT_THREEDSURFACECHART    6
#define PE_GT_SCATTERCHART          7
#define PE_GT_RADARCHART            8
#define PE_GT_BUBBLECHART           9
#define PE_GT_STOCKCHART            10
#define PE_GT_USERDEFINEDCHART      50      // <----|__ for PEGetGraphTypeInfo only - 
#define PE_GT_UNKNOWNTYPECHART      100     // <----|   do not use in PESetGraphTypeInfo.


// graph subtype
// bar charts
#define PE_GST_SIDEBYSIDEBARCHART                   0
#define PE_GST_STACKEDBARCHART                      1
#define PE_GST_PERCENTBARCHART                      2
#define PE_GST_FAKED3DSIDEBYSIDEBARCHART            3
#define PE_GST_FAKED3DSTACKEDBARCHART               4
#define PE_GST_FAKED3DPERCENTBARCHART               5
                                                    
// line charts                                      
#define PE_GST_REGULARLINECHART                     10
#define PE_GST_STACKEDLINECHART                     11
#define PE_GST_PERCENTAGELINECHART                  12
#define PE_GST_LINECHARTWITHMARKERS                 13
#define PE_GST_STACKEDLINECHARTWITHMARKERS          14
#define PE_GST_PERCENTAGELINECHARTWITHMARKERS       15
                                                    
//area charts                                       
#define PE_GST_ABSOLUTEAREACHART                    20
#define PE_GST_STACKEDAREACHART                     21
#define PE_GST_PERCENTAREACHART                     22
#define PE_GST_FAKED3DABSOLUTEAREACHART             23
#define PE_GST_FAKED3DSTACKEDAREACHART              24
#define PE_GST_FAKED3DPERCENTAREACHART              25
                                                    
// pie charts                                       
#define PE_GST_REGULARPIECHART                      30
#define PE_GST_FAKED3DREGULARPIECHART               31
#define PE_GST_MULTIPLEPIECHART                     32
#define PE_GST_MULTIPLEPROPORTIONALPIECHART         33
                                                    
// doughnut charts                                  
#define PE_GST_REGULARDOUGHNUTCHART                 40
#define PE_GST_MULTIPLEDOUGHNUTCHART                41
#define PE_GST_MULTIPLEPROPORTIONALDOUGHNUTCHART    42

// 3D riser charts
#define PE_GST_THREEDREGULARCHART                   50
#define PE_GST_THREEDPYRAMIDCHART                   51
#define PE_GST_THREEDOCTAGONCHART                   52
#define PE_GST_THREEDCUTCORNERSCHART                53
                                                    
// 3D surface charts                                
#define PE_GST_THREEDSURFACEREGULARCHART            60
#define PE_GST_THREEDSURFACEWITHSIDESCHART          61
#define PE_GST_THREEDSURFACEHONEYCOMBCHART          62
                                                    
// scatter charts                                   
#define PE_GST_XYSCATTERCHART                       70
#define PE_GST_XYSCATTERDUALAXISCHART               71
#define PE_GST_XYSCATTERWITHLABELSCHART             72
#define PE_GST_XYSCATTERDUALAXISWITHLABELSCHART     73
                                                    
// radar charts                                     
#define PE_GST_REGULARRADARCHART                    80
#define PE_GST_STACKEDRADARCHART                    81
#define PE_GST_RADARDUALAXISCHART                   82
                                                    
// bubble charts                                    
#define PE_GST_REGULARBUBBLECHART                   90
#define PE_GST_DUALAXISBUBBLECHART                  91
                                                    
// stocked charts                                   
#define PE_GST_HIGHLOWCHART                         100
#define PE_GST_HIGHLOWOPENCLOSECHART                101
                                                    
#define PE_GST_UNKNOWNSUBTYPECHART                  1000

typedef struct PEGraphTypeInfo
{
#if defined (__cplusplus)
    PEGraphTypeInfo ()
    {
        StructSize = sizeof (PEGraphTypeInfo);
        graphType = PE_UNCHANGED;
        graphSubtype = PE_UNCHANGED;
    };
#endif

    PEWORD StructSize;
    short graphType;      // PE_GT_*, PE_UNCHANGED for no change
    short graphSubtype;   // PE_GST_*, PE_UNCHANGED for no change

} PEGraphTypeInfo;

#define PE_SIZEOF_GRAPH_TYPE_INFO (sizeof (PEGraphTypeInfo))

PEBOOL CRPE_API PEGetGraphTypeInfo(short printJob, 
                                 short sectionN, 
                                 short graphN, 
                                 PEGraphTypeInfo FAR * graphTypeInfo);

PEBOOL CRPE_API PESetGraphTypeInfo(short printJob, 
                                 short sectionN, 
                                 short graphN, 
                                 PEGraphTypeInfo FAR * graphTypeInfo);


// graph text
#define PE_GTT_TITLE            0
#define PE_GTT_SUBTITLE         1
#define PE_GTT_FOOTNOTE         2
#define PE_GTT_SERIESTITLE      3
#define PE_GTT_GROUPSTITLE      4
#define PE_GTT_XAXISTITLE       5
#define PE_GTT_YAXISTITLE       6
#define PE_GTT_ZAXISTITLE       7

// graph text fonts
#define PE_GTF_TITLEFONT        0
#define PE_GTF_SUBTITLEFONT     1
#define PE_GTF_FOOTNOTEFONT     2
#define PE_GTF_GROUPSTITLEFONT  3
#define PE_GTF_DATATITLEFONT    4
#define PE_GTF_LEGENDFONT       5
#define PE_GTF_GROUPLABELSFONT  6
#define PE_GTF_DATALABELSFONT   7

#define PE_FACE_NAME_LEN 64
typedef struct PEFontColorInfo
{
#if defined (__cplusplus)
    PEFontColorInfo ()
    {
        StructSize = sizeof (PEFontColorInfo);
        faceName[0] = '\0';
        fontFamily = PE_FF_DONTCARE;
        fontPitch = PE_DEFAULT_PITCH;
        charSet = PE_DEFAULT_CHARSET;
        pointSize = 0;
        isItalic = PE_UNCHANGED;
        isUnderlined = PE_UNCHANGED;
        isStruckOut = PE_UNCHANGED;
        weight = 0;
        color = PE_UNCHANGED_COLOR;
        twipSize = 0;
    };
#endif

    PEWORD StructSize;
    char faceName[PE_FACE_NAME_LEN]; // empty string for no change
    short fontFamily; // PE_FF_DONTCARE for no change
    short fontPitch;  // PE_DEFAULT_PITCH for no change
    short charSet;   // PE_DEFAULT_CHARSET for no change
    short pointSize;  // 0 for no change
    short isItalic;   // PEBOOL value, except use PE_UNCHANGED for no change.
    short isUnderlined; // PEBOOL value, except use PE_UNCHANGED for no change.
    short isStruckOut;  // PEBOOL value, except use PE_UNCHANGED for no change.
    short weight;       // 0 for no change
    PECOLORREF color;     // PE_UNCHANGED_COLOR for no change.
    short twipSize;     // Font size in twips, 0 for no change.
                        // Use one of pointSize or twipSize. If both pointSize and twipSize
                        // are non-zero, twipSize will be used and pointSize will be ignored.
}PEFontColorInfo;
#define PE_SIZEOF_FONT_COLOR_INFO (sizeof(PEFontColorInfo))

PEBOOL CRPE_API PEGetGraphTextInfo(short printJob, 
                                 short sectionN, 
                                 short graphN, 
                                 PEWORD titleType,     //PE_GTT_*
                                 PEHANDLE FAR * title, 
                                 short FAR * titleLength);

PEBOOL CRPE_API PESetGraphTextInfo(short printJob, 
                                 short sectionN, 
                                 short graphN, 
                                 PEWORD titleType, 
                                 const char FAR * title);

//enable/disable graph default titles
PEBOOL CRPE_API PESetGraphTextDefaultOption (short printJob,
                                    short sectionN, 
                                    short graphN, 
                                    PEWORD titleType,     //PE_GTT_*
                                    PEBOOL useDefault);

PEBOOL CRPE_API PEGetGraphTextDefaultOption (short printJob,
                                    short sectionN, 
                                    short graphN, 
                                    PEWORD titleType,     //PE_GTT_*
                                    PEBOOL FAR * useDefault);


//graph font
PEBOOL CRPE_API PEGetGraphFontInfo(short printJob, 
                                 short sectionN, 
                                 short graphN, 
                                 PEWORD titleFontType,  //PE_GTF_
                                 PEFontColorInfo FAR * fontColourInfo);

PEBOOL CRPE_API PESetGraphFontInfo(short printJob, 
                                 short sectionN, 
                                 short graphN, 
                                 PEWORD titleFontType,  //PE_GTF_
                                 PEFontColorInfo FAR * fontColourInfo);

// graph options
#define PE_GLP_PLACEUPPERRIGHT      0
#define PE_GLP_PLACEBOTTOMCENTER    1
#define PE_GLP_PLACETOPCENTER       2
#define PE_GLP_PLACERIGHT           3
#define PE_GLP_PLACELEFT            4
#define PE_GLP_PLACECUSTOM          5   // for PEGetGraphOptionInfo, do not use
                                        // in PESetGraphOptionInfo.

//legend layout
#define PE_GLL_PERCENTAGE           0
#define PE_GLL_AMOUNT               1
#define PE_GLL_CUSTOM               2   // for PEGetGraphOptionInfo, do not use
                                        // in PESetGraphOptionInfo.

// bar sizes
#define PE_GBS_MINIMUMBARSIZE       0
#define PE_GBS_SMALLBARSIZE         1
#define PE_GBS_AVERAGEBARSIZE       2
#define PE_GBS_LARGEBARSIZE         3
#define PE_GBS_MAXIMUMBARSIZE       4

// pie sizes
#define PE_GPS_MINIMUMPIESIZE       64
#define PE_GPS_SMALLPIESIZE         48
#define PE_GPS_AVERAGEPIESIZE       32
#define PE_GPS_LARGEPIESIZE         16
#define PE_GPS_MAXIMUMPIESIZE       0

// detached pie slice
#define PE_GDPS_NODETACHMENT        0
#define PE_GDPS_SMALLESTSLICE       1
#define PE_GDPS_LARGESTSLICE        2

// marker sizes
#define PE_GMS_SMALLMARKERS         0
#define PE_GMS_MEDIUMSMALLMARKERS   1
#define PE_GMS_MEDIUMMARKERS        2
#define PE_GMS_MEDIUMLARGEMARKERS   3
#define PE_GMS_LARGEMARKERS         4

// marker shapes
#define PE_GMSP_RECTANGLESHAPE      1
#define PE_GMSP_CIRCLESHAPE         4
#define PE_GMSP_DIAMONDSHAPE        5
#define PE_GMSP_TRIANGLESHAPE       8

// chart color
#define PE_GCR_COLORCHART           0
#define PE_GCR_BLACKANDWHITECHART   1

// chart data points
#define PE_GDP_NONE                 0
#define PE_GDP_SHOWLABEL            1
#define PE_GDP_SHOWVALUE            2

// number formats
#define PE_GNF_NODECIMAL            0
#define PE_GNF_ONEDECIMAL           1
#define PE_GNF_TWODECIMAL           2
#define PE_GNF_CURRENCYNODECIMAL    3
#define PE_GNF_CURRENCYTWODECIMAL   4
#define PE_GNF_PERCENTNODECIMAL     5
#define PE_GNF_PERCENTONEDECIMAL    6
#define PE_GNF_PERCENTTWODECIMAL    7

// viewing angles
#define PE_GVA_STANDARDVIEW         1
#define PE_GVA_TALLVIEW             2
#define PE_GVA_TOPVIEW              3
#define PE_GVA_DISTORTEDVIEW        4
#define PE_GVA_SHORTVIEW            5
#define PE_GVA_GROUPEYEVIEW         6
#define PE_GVA_GROUPEMPHASISVIEW    7
#define PE_GVA_FEWSERIESVIEW        8
#define PE_GVA_FEWGROUPSVIEW        9
#define PE_GVA_DISTORTEDSTDVIEW     10
#define PE_GVA_THICKGROUPSVIEW      11
#define PE_GVA_SHORTERVIEW          12
#define PE_GVA_THICKSERIESVIEW      13
#define PE_GVA_THICKSTDVIEW         14
#define PE_GVA_BIRDSEYEVIEW         15
#define PE_GVA_MAXVIEW              16

typedef struct PEGraphOptionInfo
{
#if defined (__cplusplus)
    PEGraphOptionInfo ()
    {
        StructSize = sizeof (PEGraphOptionInfo);
        graphColour = PE_UNCHANGED;
        showLegend = PE_UNCHANGED;
        legendPosition = PE_UNCHANGED;
        pieSize = PE_UNCHANGED;
        detachedPieSlice = PE_UNCHANGED;
        barSize = PE_UNCHANGED;
        verticalBars = PE_UNCHANGED;
        markerSize = PE_UNCHANGED;
        markerShape = PE_UNCHANGED;
        dataPoints = PE_UNCHANGED;
        dataValueNumberFormat = PE_UNCHANGED;
        viewingAngle = PE_UNCHANGED;
        legendLayout = PE_UNCHANGED;
    };
#endif

    PEWORD StructSize;

    short graphColour; // PE_GCR_*, PE_UNCHANGED for no change

    short showLegend; //PEBOOL, PE_UNCHANGED for no change
    short legendPosition; //PE_GLP_*, if showLegend == 0, means no legend 

// pie charts and doughut charts
    short pieSize; // PE_GPS_*, PE_UNCHANGED for no change
    short detachedPieSlice; // PE_GDPS_*, PE_UNCHANGED for no change

// bar chart
    short barSize; // PE_GBS_*, PE_UNCHANGED for no change
    short verticalBars; //PEBOOL, PE_UNCHANGED for no change

// markers (used for line and bar charts)
    short markerSize; // PE_GMS_*, PE_UNCHANGED for no change
    short markerShape; // PE_GMSP_*, PE_UNCHANGED for no change

//data points
    short dataPoints; // PE_GDP_*, PE_UNCHANGED for no change    
    short dataValueNumberFormat; //PE_GNF_*, PE_UNCHANGED for no change

// 3d
    short viewingAngle; //PE_GVA_*, PE_UNCHANGED for no change

    short legendLayout;     //PE_GLL_*

} PEGraphOptionInfo;

#define PE_SIZEOF_GRAPH_OPTION_INFO (sizeof (PEGraphOptionInfo))


PEBOOL CRPE_API PEGetGraphOptionInfo(short printJob, 
                                   short sectionN, 
                                   short graphN, 
                                   PEGraphOptionInfo FAR * graphOptionInfo);

PEBOOL CRPE_API PESetGraphOptionInfo(short printJob, 
                                   short sectionN, 
                                   short graphN,
                                   PEGraphOptionInfo FAR * graphOptionInfo);

//graph axes
#define PE_GGT_NOGRIDLINES              0
#define PE_GGT_MINORGRIDLINES           1
#define PE_GGT_MAJORGRIDLINES           2
#define PE_GGT_MAJORANDMINORGRIDLINES   3

//axis division method
#define PE_ADM_AUTOMATIC                0
#define PE_ADM_MANUAL                   1

typedef struct PEGraphAxisInfo
{
#if defined (__cplusplus)
    PEGraphAxisInfo ()
    {
        StructSize = sizeof (PEGraphAxisInfo);
        groupAxisGridLine = PE_UNCHANGED;
        dataAxisYGridLine = PE_UNCHANGED;
        dataAxisY2GridLine = PE_UNCHANGED;
        seriesAxisGridline = PE_UNCHANGED;
        dataAxisYMinValue = 0;
        dataAxisYMaxValue = 0;
        dataAxisY2MinValue = 0;
        dataAxisY2MaxValue = 0;
        seriesAxisMinValue = 0;
        seriesAxisMaxValue = 0;
        dataAxisYNumberFormat = PE_UNCHANGED;
        dataAxisY2NumberFormat = PE_UNCHANGED;
        seriesAxisNumberFormat = PE_UNCHANGED;
        dataAxisYAutoRange = PE_UNCHANGED;
        dataAxisY2AutoRange = PE_UNCHANGED;
        seriesAxisAutoRange = PE_UNCHANGED;
        dataAxisYAutomaticDivision = PE_UNCHANGED;
        dataAxisY2AutomaticDivision = PE_UNCHANGED;
        seriesAxisAutomaticDivision = PE_UNCHANGED;
        dataAxisYManualDivision = PE_UNCHANGED;
        dataAxisY2ManualDivision = PE_UNCHANGED;
        seriesAxisManualDivision = PE_UNCHANGED;
        dataAxisYAutoScale = PE_UNCHANGED;
        dataAxisY2AutoScale = PE_UNCHANGED;
        seriesAxisAutoScale = PE_UNCHANGED;
    };
#endif

    PEWORD StructSize;

    short groupAxisGridLine; // PE_GGT_*, PE_UNCHANGED for no change
    short dataAxisYGridLine; // PE_GGT_*, PE_UNCHANGED for no change
    short dataAxisY2GridLine; // PE_GGT_*, PE_UNCHANGED for no change
    short seriesAxisGridline; // PE_GGT_*, PE_UNCHANGED for no change

    double dataAxisYMinValue;
    double dataAxisYMaxValue;
    double dataAxisY2MinValue;
    double dataAxisY2MaxValue;
    double seriesAxisMinValue;
    double seriesAxisMaxValue;

    short dataAxisYNumberFormat; //PE_GNF_*, PE_UNCHANGED for no change
    short dataAxisY2NumberFormat; //PE_GNF_*, PE_UNCHANGED for no change
    short seriesAxisNumberFormat; //PE_GNF_*, PE_UNCHANGED for no change

    short dataAxisYAutoRange; // PEBOOL, PE_UNCHANGED for no change
    short dataAxisY2AutoRange; //PEBOOL, PE_UNCHANGED for no change
    short seriesAxisAutoRange; //PEBOOL, PE_UNCHANGED for no change

    short dataAxisYAutomaticDivision; // PE_ADM_* or PE_UNCHANGED for no change
    short dataAxisY2AutomaticDivision; // PE_ADM_* or PE_UNCHANED for no change
    short seriesAxisAutomaticDivision; // PE_ADM_* or PE_UNCHANED for no change

    long dataAxisYManualDivision;  //if dataAxisYAutomaticDivision is PE_ADM_AUTOMATIC, this field is ignored
    long dataAxisY2ManualDivision; //if dataAxisY2AutomaticDivision is PE_ADM_AUTOMATIC, this field is ignored
    long seriesAxisManualDivision; //if seriesAxisAutomaticDivision is PE_ADM_AUTOMATIC, this field is ignored

    short dataAxisYAutoScale;       //PEBOOL, PE_UNCHANGED for no change
    short dataAxisY2AutoScale;      //PEBOOL, PE_UNCHANGED for no change
    short seriesAxisAutoScale;      //PEBOOL, PE_UNCHANGED for no change

}  PEGraphAxisInfo;

#define PE_SIZEOF_GRAPH_AXIS_INFO (sizeof (PEGraphAxisInfo))

PEBOOL CRPE_API PEGetGraphAxisInfo(short printJob, 
                                 short sectionN, 
                                 short graphN, 
                                 PEGraphAxisInfo FAR * graphAxisInfo);

PEBOOL CRPE_API PESetGraphAxisInfo(short printJob, 
                                 short sectionN, 
                                 short graphN, 
                                 PEGraphAxisInfo FAR * graphAxisInfo);

/*******************************************/
// formula operations
/********************************************/
short CRPE_API PEGetNFormulas (short printJob);

PEBOOL CRPE_API PEGetNthFormula (short printJob,
                               short formulaN,
                               PEHANDLE FAR *nameHandle,
                               short FAR *nameLength,
                               PEHANDLE FAR *textHandle,
                               short FAR *textLength);

PEBOOL CRPE_API PEGetFormula (short printJob,
                            const char FAR *formulaName,
                            PEHANDLE FAR *textHandle,
                            short FAR *textLength);

PEBOOL CRPE_API PESetFormula (short printJob,
                            const char FAR *formulaName,
                            const char FAR *formulaString);

// Format formula name
// Old naming convention
#define SECTION_VISIBILITY               58
#define NEW_PAGE_BEFORE                  60
#define NEW_PAGE_AFTER                   61
#define KEEP_SECTION_TOGETHER            62
#define SUPPRESS_BLANK_SECTION           63
#define RESET_PAGE_N_AFTER               64
#define PRINT_AT_BOTTOM_OF_PAGE          65
#define UNDERLAY_SECTION                 66
#define SECTION_BACK_COLOUR              67

// New naming convention
#define PE_FFN_AREASECTION_VISIBILITY           58  // area & section format
#define PE_FFN_SECTION_VISIBILITY               58  // section format
#define PE_FFN_SHOW_AREA                        59  // area format
#define PE_FFN_NEW_PAGE_BEFORE                  60  // area & section format
#define PE_FFN_NEW_PAGE_AFTER                   61  // area & section format
#define PE_FFN_KEEP_TOGETHER                    62  // area & section format
#define PE_FFN_SUPPRESS_BLANK_SECTION           63  // section format
#define PE_FFN_RESET_PAGE_N_AFTER               64  // area & section format
#define PE_FFN_PRINT_AT_BOTTOM_OF_PAGE          65  // area & section format
#define PE_FFN_UNDERLAY_SECTION                 66  // section format
#define PE_FFN_SECTION_BACK_COLOUR              67  // section format
#define PE_FFN_SECTION_BACK_COLOR               67  // section format

PEBOOL CRPE_API PEGetAreaFormatFormula (short printJob,
                                      short areaCode,
                                      short formulaName, // an area PE_FFN_ constant
                                      PEHANDLE FAR *textHandle,
                                      short FAR *textLength);

PEBOOL CRPE_API PESetAreaFormatFormula (short printJob,
                                      short areaCode,
                                      short formulaName, // an area PE_FFN_ constant
                                      const char FAR *formulaString);

PEBOOL CRPE_API PEGetSectionFormatFormula (short printJob,
                                         short sectionCode,
                                         short formulaName, // a section PE_FFN_ constant
                                         PEHANDLE FAR *textHandle,
                                         short FAR *textLength);

PEBOOL CRPE_API PESetSectionFormatFormula (short printJob,
                                         short sectionCode,
                                         short formulaName, // a section PE_FFN_ constant
                                         const char FAR *formulaString);

PEBOOL CRPE_API PECheckFormula (short printJob,
                              const char FAR *formulaName);

PEBOOL CRPE_API PEGetSelectionFormula (short printJob,
                                     PEHANDLE FAR *textHandle,
                                     short FAR *textLength);

PEBOOL CRPE_API PESetSelectionFormula (short printJob,
                                     const char FAR *formulaString);

PEBOOL CRPE_API PECheckSelectionFormula (short printJob);

PEBOOL CRPE_API PEGetGroupSelectionFormula (short printJob,
                                          PEHANDLE FAR *textHandle,
                                          short FAR *textLength);

PEBOOL CRPE_API PESetGroupSelectionFormula (short printJob,
                                          const char FAR *formulaString);

PEBOOL CRPE_API PECheckGroupSelectionFormula (short printJob);

/* ************************************ */
/*          SQL Expressions             */
/* ************************************ */
short CRPE_API PEGetNSQLExpressions (short printJob);

PEBOOL CRPE_API PEGetNthSQLExpression (short printJob,
                                    short expressionN,
                                    PEHANDLE FAR *nameHandle,
                                    short FAR *nameLength,
                                    PEHANDLE FAR *textHandle,
                                    short FAR *textLength);

PEBOOL CRPE_API PEGetSQLExpression (short printJob,
                                    const char FAR *expressionName,
                                    PEHANDLE FAR *textHandle,
                                    short FAR *textLength);

PEBOOL CRPE_API PESetSQLExpression (short printJob,
                                    const char FAR *expressionName,
                                    const char FAR *expressionString);

PEBOOL CRPE_API PECheckSQLExpression (short printJob,
                                    const char FAR *expressionName);

/********************************************************************************/
// NOTE : Stored Procedures
//
// The previous Stored Procedure API Calls PEGetNParams, PEGetNthParam,
// PEGetNthParamInfo and PESetNthParam have been made obsolete.  Older 
// applications that used these API Calls will still work as before, but for new 
// development please use the new Parameter API calls below, 
//
// The Stored Procedure Parameters have now been unified with the Parameter 
// Fields.
//
// The replacements for these calls are as follows : 
//		PEGetNParams		= PEGetNParameterFields
//		PEGetNthParam		= PEGetNthParameterField
//		PEGetNthParamInfo	= PEGetParameterValueInfo
//		PESetNthParam		= PESetNthParameterField
//
// NOTE : To tell if a Parameter Field is a Stored Procedure, use the 
//		  PEGetNthParameterType or PEGetNthParameterField API Calls
//
// If you wish to SET a parameter to NULL then set the CurrentValue to CRWNULL.
// The CRWNULL is of Type String and is independant of the datatype of the 
// parameter.
//
/********************************************************************************/

/****************************************/
// Parameter field operation
/****************************************/
#define PE_WORD_LEN           2
#define PE_PF_REPORT_NAME_LEN 128
#define PE_PF_NAME_LEN        256
#define PE_PF_PROMPT_LEN      256
#define PE_PF_VALUE_LEN       256
#define PE_PF_EDITMASK_LEN    256

#define PE_PF_NUMBER          0
#define PE_PF_CURRENCY        1
#define PE_PF_BOOLEAN         2
#define PE_PF_DATE            3
#define PE_PF_STRING          4
#define PE_PF_DATETIME        5
#define PE_PF_TIME            6

typedef struct PEParameterFieldInfo
{
#if defined (__cplusplus)
    PEParameterFieldInfo ()
    {
        StructSize = sizeof (PEParameterFieldInfo);
        ValueType = PE_UNCHANGED;
        DefaultValueSet = 0;    // PEWORD is unsigned, so set it to 0 instead of PE_UNCHANGED
        CurrentValueSet = 0;    // PEWORD is unsigned, so set it to 0 instead of PE_UNCHANGED
        Name [0] = '\0';
        Prompt [0] = '\0';
        DefaultValue [0] = '\0';
        CurrentValue [0] = '\0';
        ReportName [0] = '\0';
        needsCurrentValue = 0;  // PEWORD is unsigned, so set it to 0 instead of PE_UNCHANGED
        isLimited = 0;          // PEWORD is unsigned, so set it to 0 instead of PE_UNCHANGED
        MinSize = 0.0;
        MaxSize = 0.0;
        EditMask [0] = '\0';
        isHidden = PE_UNCHANGED; // obsolete
        isLinked = '\0';
    };
#endif

    // Initialize to PE_SIZEOF_PARAMETER_FIELD_INFO.
    PEWORD StructSize;

    // PE_PF_ constant
    PEWORD ValueType;

    // Indicate the default value is set in PEParameterFieldInfo.
    PEWORD DefaultValueSet;

    // Indicate the current value is set in PEParameterFieldInfo.
    PEWORD CurrentValueSet;

    // All strings are null-terminated.
    char Name [PE_PF_NAME_LEN];
    char Prompt [PE_PF_PROMPT_LEN];

    // Could be Number, Currency, Boolean, Date, DateTime, Time, or String
    char DefaultValue [PE_PF_VALUE_LEN];
    char CurrentValue [PE_PF_VALUE_LEN];

    // name of report where the field belongs, only used in
    // PEGetNthParameterField and PENewParameterField
    char ReportName [PE_PF_REPORT_NAME_LEN];

    // returns false if parameter is linked, not in use, or has current value set
    PEWORD needsCurrentValue;

    //for String values this will be PETRUE if the string is limited on length, for 
    //other types it will be PETRUE if the parameter is limited by a range
    PEWORD isLimited;

    //For string fields, these are the minimum/maximum length of the string.
    //For numeric fields, they are the minimum/maximum numeric value.
    //For other fields, use PEGetParameterMinMaxValue
    double MinSize;
    double MaxSize;

    //An edit mask that restricts what may be entered for string parameters.
    char EditMask [PE_PF_EDITMASK_LEN];

    PEWORD isHidden; // obsolete

    // Indicate if this parameter is linked to a subreport. Readonly. Set will ignore it.
    PEWORD isLinked;
}PEParameterFieldInfo;

#define PE_SIZEOF_PARAMETER_FIELD_INFO (sizeof (PEParameterFieldInfo))

short CRPE_API PEGetNParameterFields (short printJob);

PEBOOL CRPE_API PEGetNthParameterField (short printJob,
                                      short parameterN,
                                      PEParameterFieldInfo FAR *parameterInfo);

PEBOOL CRPE_API PESetNthParameterField (short printJob,
                                      short parameterN,
                                      PEParameterFieldInfo FAR *parameterInfo);

// define value type
#define PE_VI_NUMBER       0
#define PE_VI_CURRENCY     1
#define PE_VI_BOOLEAN      2
#define PE_VI_DATE         3
#define PE_VI_STRING       4
#define PE_VI_DATETIME     5
#define PE_VI_TIME         6
#define PE_VI_INTEGER      7
#define PE_VI_COLOR        8
#define PE_VI_CHAR         9
#define PE_VI_LONG         10
#define PE_VI_STRINGHANDLE 11 // use viLong as handle and then call PEGetHandleString
#define PE_VI_HANDLE       12 // use viLong as generic handle.
#define PE_VI_NOVALUE      100

#define PE_VI_STRING_LEN 256

typedef struct PEValueInfo
{
#if defined (__cplusplus)
    PEValueInfo ()
    {
        StructSize = sizeof (PEValueInfo);
        valueType = PE_VI_NOVALUE; // a PE_VI_ constant
        viNumber = 0.0;
        viCurrency = 0.0;
        viBoolean = PE_UNCHANGED;
        viString[0] = 0;
        for (int i=0; i<3; i++)
        {
            viDate[i] = PE_UNCHANGED;
            viDateTime[i] = PE_UNCHANGED;
            viDateTime[i+3] = PE_UNCHANGED;
            viTime[i] = PE_UNCHANGED;
        }
        viColor = PE_UNCHANGED_COLOR;
        viInteger = 0;
        viC = '\0';
        viLong = PE_UNCHANGED;
    };
#endif

    PEWORD StructSize;
    PEWORD valueType; // a PE_VI_ constant
    double viNumber;
    double viCurrency;
    PEBOOL viBoolean;
    char viString[PE_VI_STRING_LEN];
    short viDate[3]; // year, month, day
    short viDateTime[6]; // year, month, day, hour, minute, second
    short viTime[3];  // hour, minute, second
    PECOLORREF viColor;
    short viInteger;
    char viC; //PEBYTE
    char ignored; // for 4 byte alignment. ignored.
    long viLong;
} PEValueInfo;

#define PE_SIZEOF_VALUE_INFO (sizeof (PEValueInfo))

// Converting parameterInfo default value or current value into value info
// pass default vaule or current value in PEParameterFieldInfo into these two functions.
PEBOOL CRPE_API PEConvertPFInfoToVInfo(void FAR * value, short valueType, PEValueInfo FAR * valueInfo);
PEBOOL CRPE_API PEConvertVInfoToPFInfo(PEValueInfo FAR * valueInfo, PEWORD FAR * valueType, void FAR * value);

// Default values for Parameter fields.
// ////////////////////////////////////

// If return value is -1 then an error has occurred.
short CRPE_API PEGetNParameterDefaultValues (short printJob,
                                             const char FAR * parameterFieldName,
                                             const char FAR * reportName);

PEBOOL  CRPE_API PEGetNthParameterDefaultValue (short printJob,
                                                const char FAR * parameterFieldName,
                                                const char FAR * reportName, short index,
                                                PEValueInfo FAR * valueInfo);

PEBOOL  CRPE_API PESetNthParameterDefaultValue (short printJob,
                                                const char FAR * parameterFieldName,
                                                const char FAR * reportName,
                                                short index,
                                                PEValueInfo FAR * valueInfo);

PEBOOL  CRPE_API PEAddParameterDefaultValue (short printJob,
                                             const char FAR * parameterFieldName,
                                             const char FAR * reportName,
                                             PEValueInfo FAR * valueInfo);

PEBOOL  CRPE_API PEDeleteNthParameterDefaultValue (short printJob,
                                                   const char FAR * parameterFieldName,
                                                   const char FAR * reportName,
                                                   short index);

// Min/Max values for Parameter fields.
// ////////////////////////////////////
PEBOOL  CRPE_API PEGetParameterMinMaxValue (short printJob, const char FAR * parameterFieldName,
                                          const char FAR * reportName,
                                          PEValueInfo FAR * valueMin, // Set to PENULL to retrieve MAX only; must be non-PENULL if valueMax is PENULL.
                                          PEValueInfo FAR * valueMax  // Set to PENULL to retrieve MIN only; must be non-PENULL if valueMin is PENULL.
                                          );
PEBOOL  CRPE_API PESetParameterMinMaxValue (short printJob, const char FAR * parameterFieldName,
                                          const char FAR * reportName,
                                          PEValueInfo FAR * valueMin, // Set to PENULL to set MAX only; must be non-PENULL if valueMax is PENULL.
                                          PEValueInfo FAR * valueMax  // Set to PENULL to set MIN only; must be non-PENULL if valueMin is PENULL.
                                                                        // If both valueInfo and valueMax are non-PENULL then
                                                                        // valueMin->valueType MUST BE THE SAME AS valueMax->valueType.
                                                                        // If different, PE_ERR_INCONSISTANTTYPES is returned.
                                          );

// Pick list options in Parameter fields.
// //////////////////////////////////////
PEBOOL CRPE_API PEGetNthParameterValueDescription (short printJob, const char FAR * parameterFieldName,
                                                 const char FAR * reportName, short index, PEHANDLE FAR * valueDesc,
                                                 short FAR *valueDescLength);
PEBOOL CRPE_API PESetNthParameterValueDescription (short printJob, const char FAR * parameterFieldName,
                                                 const char FAR * reportName, short index, char FAR * valueDesc);

// constants for sortMethod in PEParameterPickListOption struct
#define PE_OR_NO_SORT                   0
#define PE_OR_ALPHANUMERIC_ASCENDING    1
#define PE_OR_ALPHANUMERIC_DESCENDING   2
#define PE_OR_NUMERIC_ASCENDING         3
#define PE_OR_NUMERIC_DESCENDING        4

typedef struct PEParameterPickListOption
{
#if defined (__cplusplus)
    PEParameterPickListOption ()
    {
        StructSize = sizeof (PEParameterPickListOption);
        showDescOnly = PE_UNCHANGED;
        sortMethod = PE_UNCHANGED;
        sortBasedOnDesc = PE_UNCHANGED;
    };
#endif

    PEWORD  StructSize;       // initialize to PE_SIZEOF_PICK_LIST_OPTION
    short showDescOnly;     // boolean value or PE_UNCHANGED
    short sortMethod;       // enum type const, PE_UNCHANGED for no change
    short sortBasedOnDesc;  // boolean value or PE_UNCHANGED
} PEParameterPickListOption;
#define PE_SIZEOF_PICK_LIST_OPTION (sizeof (PEParameterPickListOption))

PEBOOL CRPE_API PEGetParameterPickListOption (short printJob, const char FAR * parameterFieldName,
                                            const char FAR * reportName, PEParameterPickListOption FAR * pickListOption);
PEBOOL CRPE_API PESetParameterPickListOption (short printJob, const char FAR * parameterFieldName,
                                            const char FAR * reportName, PEParameterPickListOption FAR * pickListOption);
// Parameter current values
///////////////////////////
// parameter field origin
#define PE_PO_REPORT         0
#define PE_PO_STOREDPROC     1
#define PE_PO_QUERY          2

// range info
#define PE_RI_INCLUDEUPPERBOUND 1
#define PE_RI_INCLUDELOWERBOUND 2
#define PE_RI_NOUPPERBOUND      4
#define PE_RI_NOLOWERBOUND      8

#define PE_DR_HASRANGE              0
#define PE_DR_HASDISCRETE           1
#define PE_DR_HASDISCRETEANDRANGE   2

typedef struct PEParameterValueInfo
{
#if defined (__cplusplus)
    PEParameterValueInfo ()
    {
        StructSize = sizeof (PEParameterValueInfo);
        isNullable = PE_UNCHANGED;
        disallowEditing = PE_UNCHANGED;
        allowMultipleValues = PE_UNCHANGED;
        hasDiscreteValues = PE_UNCHANGED;
        partOfGroup = PE_UNCHANGED;
        groupNum = PE_UNCHANGED;
        mutuallyExclusiveGroup = PE_UNCHANGED;
    };
#endif

    PEWORD StructSize;
    short isNullable;               // Boolean value or PE_UNCHANGED for no change.
    short disallowEditing;          // Boolean value or PE_UNCHANGED for no change.
    short allowMultipleValues;      // Boolean value or PE_UNCHANGED for no change.
    short hasDiscreteValues;        // int value or PE_UNCHANGED for no change.
                                    // 0 means has ranges, 1 means has discrete values
                                    // 2 means has discrete and ranged values
    short partOfGroup;              // Boolean value or PE_UNCHANGED for no change.
    short groupNum;                 // a group number or PE_UNCHANGED for no change.
    short mutuallyExclusiveGroup;   // Boolean value or PE_UNCHANGED for no change.
} PEParameterValueInfo;
#define PE_SIZEOF_PARAMETER_VALUE_INFO (sizeof (PEParameterValueInfo))

PEBOOL CRPE_API PEGetParameterValueInfo (short printJob,
                                         const char FAR * parameterFieldName,
                                         const char FAR * reportName,
                                         PEParameterValueInfo FAR * valueInfo);

PEBOOL CRPE_API PESetParameterValueInfo (short printJob,
                                         const char FAR * parameterFieldName,
                                         const char FAR * reportName,
                                         PEParameterValueInfo FAR * valueInfo);

// If return value is -1 then an error has occurred.
short CRPE_API PEGetNParameterCurrentValues (short printJob,
                                                      const char FAR * parameterFieldName,
                                                      const char FAR * reportName);

PEBOOL CRPE_API PEGetNthParameterCurrentValue (short printJob,
                                               const char FAR * parameterFieldName,
                                               const char FAR * reportName,
                                               short index,
                                               PEValueInfo FAR * currentValue);

PEBOOL CRPE_API PEAddParameterCurrentValue (short printJob,
                                            const char FAR * parameterFieldName,
                                            const char FAR * reportName,
                                            PEValueInfo FAR * currentValue);

// If return value is -1 then an error has occurred.
short CRPE_API PEGetNParameterCurrentRanges (short printJob,
                                                      const char FAR * parameterFieldName,
                                                      const char FAR * reportName);

PEBOOL CRPE_API PEGetNthParameterCurrentRange (short printJob,
                                               const char FAR * parameterFieldName, // if parameterFieldName does not contain ranges then
                                               const char FAR * reportName,
                                               short index,                         // last error is set to PE_ERR_RANGEORDISCRETE.
                                               PEValueInfo FAR * rangeStart,
                                               PEValueInfo FAR * rangeEnd,
                                               short FAR *rangeInfo    // one or more PE_RI_* constants.
                                              );

PEBOOL CRPE_API PEAddParameterCurrentRange (short printJob,
                                            const char FAR * parameterFieldName,  // if parameterFieldName does not contain ranges then
                                            const char FAR * reportName,                                    // last error is set to PE_ERR_RANGEORDISCRETE.
                                            PEValueInfo FAR * rangeStart, PEValueInfo FAR * rangeEnd,
                                            short rangeInfo     // one or more PE_RI_* constants.
                                           );

short CRPE_API PEGetNthParameterType (short printJob, short index); // returns PE_PO_* or -1 if index is invalid.
PEBOOL  CRPE_API PEClearParameterCurrentValuesAndRanges (short printJob,
                                                         const char FAR * parameterFieldName,
                                                         const char FAR * reportName);

/**********************************************/
// Adding, controlling sort order and group sort order
/**********************************************/
short CRPE_API PEGetNSortFields (short printJob);

PEBOOL CRPE_API PEGetNthSortField (short printJob,
                                 short sortFieldN,
                                 PEHANDLE FAR *nameHandle,
                                 short  FAR *nameLength,
                                 short  FAR *direction);

PEBOOL CRPE_API PESetNthSortField (short printJob,
                                 short sortFieldN,
                                 const char FAR *name, // formula form
                                 short direction);  // a PE_SF_ constant

PEBOOL CRPE_API PEDeleteNthSortField (short printJob,
                                    short sortFieldN);

short CRPE_API PEGetNGroupSortFields (short printJob);

PEBOOL CRPE_API PEGetNthGroupSortField (short printJob,
                                      short sortFieldN,
                                      PEHANDLE FAR *nameHandle,
                                      short  FAR *nameLength,
                                      short  FAR *direction); // a PE_SF_ constant

PEBOOL CRPE_API PESetNthGroupSortField (short printJob,
                                      short sortFieldN,
                                      const char FAR *name,
                                      short direction);

PEBOOL CRPE_API PEDeleteNthGroupSortField (short printJob,
                                         short sortFieldN);

/********************************************/
// Controlling databases
/********************************************/

// The following functions allow retrieving and updating database info
// in an opened report, so that a report can be printed using different
// session, server, database, user and/or table location settings.  Any
// changes made to the report via these functions are not permanent, and
// only last as long as the report is open.
//
// The following database functions (except for PELogOnServer and
// PELogOffServer) must be called after PEOpenPrintJob and before
// PEStartPrintJob.

// The function PEGetNTables is called to fetch the number of tables in
// the report.  This includes all PC databases (e.g. Paradox, xBase)
// as well as SQL databases (e.g. SQL Server, Oracle, Netware).

short CRPE_API PEGetNTables (short printJob);


// The function PEGetNthTableType allows the application to determine the
// type of each table.  The application can test DBType (equal to
// PE_DT_STANDARD or PE_DT_SQL), or test the database DLL name used to
// create the report.  DLL names have the following naming convention:
//     - PDB*.DLL for standard (non-SQL) databases,
//     - PDS*.DLL for SQL databases.
//
// In the case of ODBC (PDSODBC.DLL) the DescriptiveName includes the
// ODBC data source name.

#define PE_WORD_LEN          2
#define PE_DLL_NAME_LEN      64
#define PE_FULL_NAME_LEN     256

#define PE_DT_STANDARD               1
#define PE_DT_SQL                    2
#define PE_DT_SQL_STORED_PROCEDURE   3

typedef struct PETableType
{
#if defined (__cplusplus)
    PETableType ()
    {
        StructSize = sizeof (PETableType);
        DLLName [0] = '\0';
        DescriptiveName [0] = '\0';
        DBType = PE_UNCHANGED;
    };
#endif

    // Initialize to PE_SIZEOF_TABLE_TYPE.
    PEWORD StructSize;

    // All strings are null-terminated.
    char DLLName [PE_DLL_NAME_LEN];
    char DescriptiveName [PE_FULL_NAME_LEN];

    PEWORD DBType;

}PETableType;
#define PE_SIZEOF_TABLE_TYPE (sizeof (PETableType))

PEBOOL  CRPE_API PEGetNthTableType (short printJob,
                                  short tableN,
                                  PETableType FAR *tableType);

// The functions PEGetNthTableSessionInfo and PESetNthTableSessionInfo
// are only used when connecting to MS Access databases (which require a
// session to be opened first)

#define PE_LONGPTR_LEN       4
#define PE_SESS_USERID_LEN   128
#define PE_SESS_PASSWORD_LEN 128

typedef struct PESessionInfo
{
#if defined (__cplusplus)
    PESessionInfo ()
    {
        StructSize = sizeof (PESessionInfo);
        UserID [0] = '\0';
        Password [0] = '\0';
        SessionHandle = 0;
    };
#endif

    // Initialize to PE_SIZEOF_SESSION_INFO.
    PEWORD StructSize;

    // All strings are null-terminated.
    char UserID [PE_SESS_PASSWORD_LEN];

    // Password is undefined when getting information from report.
    char Password [PE_SESS_PASSWORD_LEN];

    // SessionHandle is undefined when getting information from report.
    // When setting information, if it is = 0 the UserID and Password
    // settings are used, otherwise the SessionHandle is used.
    PEDWORD SessionHandle;
}
    PESessionInfo;
#define PE_SIZEOF_SESSION_INFO (sizeof (PESessionInfo))


PEBOOL  CRPE_API PEGetNthTableSessionInfo (short printJob,
                                         short tableN,
                                         PESessionInfo FAR *sessionInfo);
PEBOOL  CRPE_API PESetNthTableSessionInfo (short printJob,
                                         short tableN,
                                         PESessionInfo FAR *sessionInfo,
                                         PEBOOL propagateAcrossTables);


// Logging on is performed when printing the report, but the correct
// log on information must first be set using PESetNthTableLogOnInfo.
// Only the password is required, but the server, database, and
// user names may optionally be overriden as well.
//
// If the parameter propagateAcrossTables is PETRUE, the new log on info
// is also applied to any other tables in this report that had the
// same original server and database names as this table.  If PEFALSE
// only this table is updated.
//
// Logging off is performed automatically when the print job is closed

#define PE_SERVERNAME_LEN    128
#define PE_DATABASENAME_LEN  128
#define PE_USERID_LEN        128
#define PE_PASSWORD_LEN      128

typedef struct PELogOnInfo
{
#if defined (__cplusplus)
    PELogOnInfo ()
    {
        StructSize = sizeof (PELogOnInfo);
        ServerName [0] = '\0';
        DatabaseName [0] = '\0';
        UserID [0] = '\0';
        Password [0] = '\0';
    };
#endif

    // Initialize to PE_SIZEOF_LOGON_INFO.
    PEWORD StructSize;

    // For any of the following values an empty string ("") means to use
    // the value already set in the report.  To override a value in the
    // report use a non-empty string (e.g. "Server A").  All strings are
    // null-terminated.
    //
    // For Netware SQL, pass the dictionary path name in ServerName and
    // data path name in DatabaseName.
    char ServerName [PE_SERVERNAME_LEN];
    char DatabaseName [PE_DATABASENAME_LEN];
    char UserID [PE_USERID_LEN];

    // Password is undefined when getting information from report.
    char Password [PE_PASSWORD_LEN];
}PELogOnInfo;
#define PE_SIZEOF_LOGON_INFO (sizeof (PELogOnInfo))

PEBOOL  CRPE_API PEGetNthTableLogOnInfo (short printJob,
                                       short tableN,
                                       PELogOnInfo FAR *logOnInfo);

PEBOOL  CRPE_API PESetNthTableLogOnInfo (short printJob,
                                       short tableN,
                                       PELogOnInfo FAR *logOnInfo,
                                       PEBOOL propagateAcrossTables);

// A table's location is fetched and set using PEGetNthTableLocation and
// PESetNthTableLocation.  This name is database-dependent, and must be
// formatted correctly for the expected database.  For example:
//     - Paradox: "c:\crw\ORDERS.DB"
//     - SQL Server: "publications.dbo.authors"

#define PE_TABLE_LOCATION_LEN      256
#define PE_CONNECTION_BUFFER_LEN   512

typedef struct PETableLocation
{
#if defined (__cplusplus)
    PETableLocation ()
    {
        StructSize = sizeof (PETableLocation);
        Location [0] = '\0';
        SubLocation[0] = '\0';
        ConnectBuffer[0] = '\0';
    };
#endif

    // Initialize to PE_SIZEOF_TABLE_LOCATION.
    PEWORD StructSize;

    // String is null-terminated.
    char Location [PE_TABLE_LOCATION_LEN];
    char SubLocation[PE_TABLE_LOCATION_LEN];
    char ConnectBuffer[PE_CONNECTION_BUFFER_LEN];    //Connection Info for attached tables
}PETableLocation;
#define PE_SIZEOF_TABLE_LOCATION (sizeof (PETableLocation))

PEBOOL  CRPE_API PEGetNthTableLocation (short printJob,
                                      short tableN,
                                      PETableLocation FAR *location);

PEBOOL  CRPE_API PESetNthTableLocation (short printJob,
                                      short tableN,
                                      PETableLocation FAR *location);

// Table Private Info

typedef struct PETablePrivateInfo
{
#if defined (__cplusplus)
    PETablePrivateInfo ()
    {
        StructSize = sizeof (PETablePrivateInfo);
        nBytes = 0;
        tag = 0;
        dataPtr = 0;
    };
#endif

    PEWORD StructSize;  // initialize to PE_SIZEOF_TABLE_PRIVATE_INFO
    PEWORD nBytes;
    PEDWORD tag;
    PEBYTE FAR * dataPtr;
} PETablePrivateInfo;
#define PE_SIZEOF_TABLE_PRIVATE_INFO (sizeof(PETablePrivateInfo))

PEBOOL CRPE_API PEGetNthTablePrivateInfo (short printJob,
                                        short tableN,
                                        PETablePrivateInfo FAR *privateInfo);

PEBOOL CRPE_API PESetNthTablePrivateInfo (short printJob,
                                        short tableN,
                                        PETablePrivateInfo FAR *privateInfo);

// The function PETestNthTableConnectivity tests whether a database
// table's settings are valid and ready to be reported on.  It returns
// true if the database session, log on, and location info is all
// correct.
//
// This is useful, for example, in prompting the user and testing a
// server password before printing begins.
//
// This function may require a significant amount of time to complete,
// since it will first open a user session (if required), then log onto
// the database server (if required), and then open the appropriate
// database table (to test that it exists).  It does not read any data,
// and closes the table immediately once successful.  Logging off is
// performed when the print job is closed.
//
// If it fails in any of these steps, the error code set indicates
// which database info needs to be updated using functions above:
//    - If it is unable to begin a session, PE_ERR_DATABASESESSION is set,
//      and the application should update with PESetNthTableSessionInfo.
//    - If it is unable to log onto a server, PE_ERR_DATABASELOGON is set,
//      and the application should update with PESetNthTableLogOnInfo.
//    - If it is unable open the table, PE_ERR_DATABASELOCATION is set,
//      and the application should update with PESetNthTableLocation.

PEBOOL  CRPE_API PETestNthTableConnectivity (short printJob,
                                           short tableN);

// PELogOnServer and PELogOffServer can be called at any time to log on
// and off of a database server.  These functions are not required if
// function PESetNthTableLogOnInfo above was already used to set the
// password for a table.
//
// These functions require a database DLL name, which can be retrieved
// using PEGetNthTableType above.
//
// This function can also be used for non-SQL tables, such as password-
// protected Paradox tables.  Call this function to set the password
// for the Paradox DLL before beginning printing.
//
// Note: When printing using PEStartPrintJob the ServerName passed in
// PELogOnServer must agree exactly with the server name stored in the
// report.  If this is not true use PESetNthTableLogOnInfo to perform
// logging on instead.

PEBOOL CRPE_API PELogOnServer (const char FAR *dllName,
                             PELogOnInfo FAR *logOnInfo);
PEBOOL CRPE_API PELogOffServer (const char FAR *dllName,
                              PELogOnInfo FAR *logOnInfo);

PEBOOL CRPE_API PELogOnSQLServerWithPrivateInfo (const char FAR *dllName,
                                               void FAR *privateInfo);

/***************************************/
// Overriding SQL query in report
/***************************************/
//
// PEGetSQLQuery () returns the same query as appears in the Show SQL Query
// dialog in CRW, in syntax specific to the database driver you are using.
//
// PESetSQLQuery () is mostly useful for reports with SQL queries that
// were explicitly edited in the Show SQL Query dialog in CRW, i.e. those
// reports that needed database-specific selection criteria or joins.
// (Otherwise it is usually best to continue using function calls such as
// PESetSelectionFormula () and let CRW build the SQL query automatically.)
//
// PESetSQLQuery () has the same restrictions as editing in the Show SQL
// Query dialog; in particular that changes are accepted in the FROM and
// WHERE clauses but ignored in the SELECT list of fields.

PEBOOL CRPE_API PEGetSQLQuery (short printJob,
                             PEHANDLE FAR *textHandle,
                             short  FAR *textLength);

PEBOOL CRPE_API PESetSQLQuery (short printJob,
                             const char FAR *queryString);

PEBOOL CRPE_API PEVerifyDatabase(short printJob);

// constants returned from PECheckNthTableDifferences, can be any
// combination of the following:
#define PE_TCD_OKAY                          0x00000000
#define PE_TCD_DATABASENOTFOUND              0x00000001
#define PE_TCD_SERVERNOTFOUND                0x00000002
#define PE_TCD_SERVERNOTOPENED               0x00000004
#define PE_TCD_ALIASCHANGED                  0x00000008
#define PE_TCD_INDEXESCHANGED                0x00000010
#define PE_TCD_DRIVERCHANGED                 0x00000020
#define PE_TCD_DICTIONARYCHANGED             0x00000040
#define PE_TCD_FILETYPECHANGED               0x00000080
#define PE_TCD_RECORDSIZECHANGED             0x00000100
#define PE_TCD_ACCESSCHANGED                 0x00000200
#define PE_TCD_PARAMETERSCHANGED             0x00000400
#define PE_TCD_LOCATIONCHANGED               0x00000800
#define PE_TCD_DATABASEOTHER                 0x00001000
#define PE_TCD_NUMFIELDSCHANGED              0x00010000
#define PE_TCD_FIELDOTHER                    0x00020000
#define PE_TCD_FIELDNAMECHANGED              0x00040000
#define PE_TCD_FIELDDESCCHANGED              0x00080000
#define PE_TCD_FIELDTYPECHANGED              0x00100000
#define PE_TCD_FIELDSIZECHANGED              0x00200000
#define PE_TCD_NATIVEFIELDTYPECHANGED        0x00400000
#define PE_TCD_NATIVEFIELDOFFSETCHANGED      0x00800000
#define PE_TCD_NATIVEFIELDSIZECHANGED        0x01000000
#define PE_TCD_FIELDDECPLACESCHANGED         0x02000000

typedef struct PETableDifferenceInfo
{
#if defined (__cplusplus)
    PETableDifferenceInfo ()
    {
        StructSize = sizeof (PETableDifferenceInfo);
        tableDifferences = 0;
    };
#endif

    PEWORD StructSize;
    PEDWORD tableDifferences;                 // any combination of PE_TCD_*
    PEDWORD reserved1;                        // reserved - do not use
    PEDWORD reserved2;                        // reserved - do not use
} PETableDifferenceInfo;

#define PE_SIZEOF_TABLE_DIFFERENCE_INFO (sizeof (PETableDifferenceInfo))

// Not implemented for reports based on dictionary returns PE_ERR_NOTIMPLEMENTED
PEBOOL CRPE_API PECheckNthTableDifferences (short printJob, short tableN, PETableDifferenceInfo FAR *tabledifferenceinfo);

/*******************************/
// Saved data
/*******************************/
//
// Use PEHasSavedData() to find out if a report currently has saved data
// associated with it.  This may or may not be PETRUE when a print job is
// first opened from a report file.  Since data is saved during a print,
// this will always be PETRUE immediately after a report is printed.
//
// Use PEDiscardSavedData() to release the saved data associated with a
// report.  The next time the report is printed, it will get current data
// from the database.
//
// The default behavior is for a report to use its saved data, rather than
// refresh its data from the database when printing a report.

PEBOOL CRPE_API PEHasSavedData (short printJob,
                              PEBOOL FAR *hasSavedData);
PEBOOL CRPE_API PEDiscardSavedData (short printJob);

/*************************/
// Report title
/*************************/

PEBOOL CRPE_API PEGetReportTitle (short printJob,
                                PEHANDLE FAR *titleHandle,
                                short  FAR *titleLength);
PEBOOL CRPE_API PESetReportTitle (short printJob,
                                const char FAR *title);


/*************************************/
// Controlling print to window
/*************************************/

PEBOOL CRPE_API PEOutputToWindow (short printJob,
                                const char FAR *title,
                                int left,
                                int top,
                                int width,
                                int height,
                                PEDWORD style,
                                PEHWND parentWindow);

typedef struct PEWindowOptions
{
#if defined (__cplusplus)
    PEWindowOptions ()
    {
        StructSize = sizeof (PEWindowOptions);
        hasGroupTree = PE_UNCHANGED;
        canDrillDown = PE_UNCHANGED;
        hasNavigationControls = PE_UNCHANGED;
        hasCancelButton = PE_UNCHANGED;
        hasPrintButton = PE_UNCHANGED;
        hasExportButton = PE_UNCHANGED;
        hasZoomControl = PE_UNCHANGED;
        hasCloseButton = PE_UNCHANGED;
        hasProgressControls = PE_UNCHANGED;
        hasSearchButton = PE_UNCHANGED;
        hasPrintSetupButton = PE_UNCHANGED;
        hasRefreshButton = PE_UNCHANGED;
        showToolbarTips = PE_UNCHANGED;
        showDocumentTips = PE_UNCHANGED;
        hasLaunchButton = PE_UNCHANGED;
    };
#endif

    PEWORD StructSize;                // initialize to PE_SIZEOF_WINDOW_OPTIONS

    short hasGroupTree;             // PEBOOL value, except use PE_UNCHANGED for no change
    short canDrillDown;             // PEBOOL value, except use PE_UNCHANGED for no change
    short hasNavigationControls;    // PEBOOL value, except use PE_UNCHANGED for no change
    short hasCancelButton;          // PEBOOL value, except use PE_UNCHANGED for no change
    short hasPrintButton;           // PEBOOL value, except use PE_UNCHANGED for no change
    short hasExportButton;          // PEBOOL value, except use PE_UNCHANGED for no change
    short hasZoomControl;           // PEBOOL value, except use PE_UNCHANGED for no change
    short hasCloseButton;           // PEBOOL value, except use PE_UNCHANGED for no change
    short hasProgressControls;      // PEBOOL value, except use PE_UNCHANGED for no change
    short hasSearchButton;          // PEBOOL value, except use PE_UNCHANGED for no change
    short hasPrintSetupButton;      // PEBOOL value, except use PE_UNCHANGED for no change
    short hasRefreshButton;         // PEBOOL value, except use PE_UNCHANGED for no change
    short showToolbarTips;          // PEBOOL value, except use PE_UNCHANGED for no change
                                    //      default is PETRUE (*Show* tooltips on toolbar)
    short showDocumentTips;         // PEBOOL value, except use PE_UNCHANGED for no change
                                    //      default is PEFALSE (*Hide* tooltips on document)
    short hasLaunchButton;          // Launch Seagate Analysis button on toolbar.
                                    // PEBOOL value, except use PE_UNCHANGED for no change
                                    //      default is PEFALSE
} PEWindowOptions;

#define PE_SIZEOF_WINDOW_OPTIONS (sizeof (PEWindowOptions))

PEBOOL CRPE_API PESetWindowOptions (short printJob,
                                  PEWindowOptions FAR *options);

PEBOOL CRPE_API PEGetWindowOptions (short printJob,
                                  PEWindowOptions FAR *options);

PEHWND CRPE_API PEGetWindowHandle (short printJob);

void CRPE_API PECloseWindow (short printJob);


/***********************************/
// Controlling printed pages
/*************************************/

PEBOOL CRPE_API PEShowNextPage (short printJob);
PEBOOL CRPE_API PEShowFirstPage (short printJob);
PEBOOL CRPE_API PEShowPreviousPage (short printJob);
PEBOOL CRPE_API PEShowLastPage (short printJob);
short CRPE_API PEGetNPages (short printJob);
PEBOOL CRPE_API PEShowNthPage (short printJob,
                             short pageN); // start from 1

#define PE_ZOOM_FULL_SIZE           0
#define PE_ZOOM_SIZE_FIT_ONE_SIDE   1
#define PE_ZOOM_SIZE_FIT_BOTH_SIDES 2

PEBOOL CRPE_API PEZoomPreviewWindow (short printJob,
                                   short level); // a percent from 25 to 400
                                                 // or a PE_ZOOM_ constant

/*************************************************************/
// Controlling print window when print control buttons hidden
/*************************************************************/

PEBOOL CRPE_API PEShowPrintControls (short printJob,
                                   PEBOOL showPrintControls);
PEBOOL CRPE_API PEPrintControlsShowing (short printJob,
                                      PEBOOL FAR *controlsShowing);

PEBOOL CRPE_API PEPrintWindow (short printJob,
                             PEBOOL waitUntilDone);

PEBOOL CRPE_API PEExportPrintWindow (short printJob,
                                   PEBOOL toMail,
                                   PEBOOL waitUntilDone);

PEBOOL CRPE_API PENextPrintWindowMagnification (short printJob);


/********************************/
// Changing printer selection
/********************************/

// Should not pass uninitialize pointer to DEVMODE structure, 
// you must new a pointer pointing to structure or initialize it 0
PEBOOL CRPE_API PESelectPrinter (short printJob,
                               const char FAR *driverName,
                               const char FAR *printerName,
                               const char FAR *portName,
                               PEDEVMODEA FAR *mode
                               );

PEBOOL CRPE_API PEGetSelectedPrinter (short printJob,
                                    PEHANDLE  FAR *driverHandle,
                                    short   FAR *driverLength,
                                    PEHANDLE  FAR *printerHandle,
                                    short   FAR *printerLength,
                                    PEHANDLE  FAR *portHandle,
                                    short   FAR *portLength,
                                    PEDEVMODEA FAR * FAR *mode
                                    );


PEBOOL CRPE_API PEFreeDevMode (short printJob,
                             PEDEVMODEA FAR * mode
                             );


/*********************************/
// Controlling print to printer
/*********************************/

PEBOOL CRPE_API PEOutputToPrinter (short printJob,
                                 short nCopies);

PEBOOL CRPE_API PESetNDetailCopies (short printJob,
                                  short nDetailCopies);

PEBOOL CRPE_API PEGetNDetailCopies (short printJob,
                                  short FAR *nDetailCopies);

// Extension to PESetPrintOptions function: If the 2nd parameter
// (pointer to PEPrintOptions) is set to 0 (null) the function prompts
// the user for these options.
//
// With this change, you can get the behaviour of the print-to-printer
// button in the print window by calling PESetPrintOptions with a
// null pointer and then calling PEPrintWindow.

#define PE_MAXPAGEN  65535

#define PE_FILE_PATH_LEN     512

#define PE_UNCOLLATED       0
#define PE_COLLATED         1
#define PE_DEFAULTCOLLATION 2

typedef struct PEPrintOptions
{
#if defined (__cplusplus)
    PEPrintOptions ()
    {
        StructSize = sizeof (PEPrintOptions);
        startPageN = 0,
        stopPageN = 0;
        nReportCopies = 0;
        collation = 0;
        outputFileName[0] = '\0';
    };
#endif

    PEWORD StructSize;            // initialize to PE_SIZEOF_PRINT_OPTIONS

    // page and copy numbers are 1-origin
    // use 0 to preserve the existing settings
    unsigned short startPageN,
                   stopPageN;

    unsigned short nReportCopies;
    unsigned short collation;
    char outputFileName[PE_FILE_PATH_LEN];
}
    PEPrintOptions;
#define PE_SIZEOF_PRINT_OPTIONS (sizeof (PEPrintOptions))

PEBOOL CRPE_API PESetPrintOptions (short printJob,
                                 PEPrintOptions FAR *options);

PEBOOL CRPE_API PEGetPrintOptions (short printJob,
                                 PEPrintOptions FAR *options);

/***************************************/
// Controlling print to file and export
/**************************************/

typedef struct PEExportOptions
{
#if defined (__cplusplus)
    PEExportOptions ()
    {
        StructSize = sizeof (PEExportOptions);
        formatDLLName [0] = '\0';
        formatType = PE_UNCHANGED;
        formatOptions = 0;
        destinationDLLName [0] = '\0';
        destinationType = PE_UNCHANGED;
        destinationOptions = 0;
        nFormatOptionsBytes = 0;
        nDestinationOptionsBytes = 0;
        unicodeFormatOptions = PEFALSE;
        unicodeDestinationOptions = PEFALSE;
    };
#endif

    PEWORD StructSize;               // initialize to PE_SIZEOF_EXPORT_OPTIONS

    char formatDLLName [PE_DLL_NAME_LEN];
    PEDWORD formatType;
    void FAR *formatOptions;
    char destinationDLLName [PE_DLL_NAME_LEN];
    PEDWORD destinationType;
    void FAR *destinationOptions;
    PEWORD nFormatOptionsBytes;      // Set by 'PEGetExportOptions', not set
                                   // by 'PEDecodeExportOptions', and
                                   // ignored by 'PEExportTo'.
    PEWORD nDestinationOptionsBytes; // Set by 'PEGetExportOptions', not set
                                   // by 'PEDecodeExportOptions', and
                                   // ignored by 'PEExportTo'.
    PEBOOL unicodeFormatOptions;
    PEBOOL unicodeDestinationOptions;
}
    PEExportOptions;
#define PE_SIZEOF_EXPORT_OPTIONS (sizeof (PEExportOptions))

PEBOOL CRPE_API PEGetExportOptions (short printJob,
                                    PEExportOptions FAR *options);

PEBOOL CRPE_API PEExportTo (short printJob,
                          PEExportOptions FAR *options);

/************************/
// Setting page margins
/************************/

#define PE_SM_DEFAULT  (short)0x8000

PEBOOL CRPE_API PESetMargins (short printJob,
                            short left,
                            short right,
                            short top,
                            short bottom);

PEBOOL CRPE_API PEGetMargins (short printJob,
                            short FAR *left,
                            short FAR *right,
                            short FAR *top,
                            short FAR *bottom);

#define PE_SI_APPLICATION_NAME_LEN  128
#define PE_SI_TITLE_LEN 128
#define PE_SI_SUBJECT_LEN 128
#define PE_SI_AUTHOR_LEN 128
#define PE_SI_KEYWORDS_LEN 128
#define PE_SI_COMMENTS_LEN 512
#define PE_SI_REPORT_TEMPLATE_LEN 128

typedef struct PEReportSummaryInfo
{
#if defined (__cplusplus)
    PEReportSummaryInfo ()
    {
        StructSize = sizeof (PEReportSummaryInfo);
        applicationName[0] = '\0';
        title[0] = '\0';
        subject[0] = '\0';
        author[0] = '\0';
        keywords[0] = '\0';
        comments[0] = '\0';
        reportTemplate[0] = '\0';
        savePreviewPicture = PE_UNCHANGED;
    };
#endif

    PEWORD StructSize;
    char applicationName[PE_SI_APPLICATION_NAME_LEN]; // read only.
    char title[PE_SI_TITLE_LEN];
    char subject[PE_SI_SUBJECT_LEN];
    char author[PE_SI_AUTHOR_LEN];
    char keywords[PE_SI_KEYWORDS_LEN];
    char comments[PE_SI_COMMENTS_LEN];
    char reportTemplate[PE_SI_REPORT_TEMPLATE_LEN];
    short savePreviewPicture; // PEBOOL PE_UNCHANGED for no change
} PEReportSummaryInfo;

#define PE_SIZEOF_REPORT_SUMMARY_INFO (sizeof(PEReportSummaryInfo))
PEBOOL CRPE_API PEGetReportSummaryInfo(short printJob, PEReportSummaryInfo FAR * summaryInfo);
PEBOOL CRPE_API PESetReportSummaryInfo(short printJob, PEReportSummaryInfo FAR * summaryInfo);

/************************************************/
// Event support
/***************************************************/
// event ID
#define PE_CLOSE_PRINT_WINDOW_EVENT           1
#define PE_ACTIVATE_PRINT_WINDOW_EVENT        2
#define PE_DEACTIVATE_PRINT_WINDOW_EVENT      3
#define PE_PRINT_BUTTON_CLICKED_EVENT         4
#define PE_EXPORT_BUTTON_CLICKED_EVENT        5
#define PE_ZOOM_LEVEL_CHANGING_EVENT          6
#define PE_FIRST_PAGE_BUTTON_CLICKED_EVENT    7
#define PE_PREVIOUS_PAGE_BUTTON_CLICKED_EVENT 8
#define PE_NEXT_PAGE_BUTTON_CLICKED_EVENT     9
#define PE_LAST_PAGE_BUTTON_CLICKED_EVENT     10
#define PE_CANCEL_BUTTON_CLICKED_EVENT        11
#define PE_CLOSE_BUTTON_CLICKED_EVENT         12
#define PE_SEARCH_BUTTON_CLICKED_EVENT        13
#define PE_GROUP_TREE_BUTTON_CLICKED_EVENT    14
#define PE_PRINT_SETUP_BUTTON_CLICKED_EVENT   15
#define PE_REFRESH_BUTTON_CLICKED_EVENT       16
#define PE_SHOW_GROUP_EVENT                   17
#define PE_DRILL_ON_GROUP_EVENT               18 // include drill on graph
#define PE_DRILL_ON_DETAIL_EVENT              19
#define PE_READING_RECORDS_EVENT              20
#define PE_START_EVENT                        21
#define PE_STOP_EVENT                         22
#define PE_MAPPING_FIELD_EVENT                23
#define PE_RIGHT_CLICK_EVENT                  24 // right mouse click
#define PE_LEFT_CLICK_EVENT                   25 // left mouse click
#define PE_MIDDLE_CLICK_EVENT                 26 // middle mouse click
#define PE_DRILL_ON_HYPERLINK_EVENT           27
#define PE_LAUNCH_SEAGATE_ANALYSIS_EVENT      28


// job destination
#define PE_TO_NOWHERE                   0
#define PE_TO_WINDOW                    1
#define PE_TO_PRINTER                   2
#define PE_TO_EXPORT                    3
#define PE_FROM_QUERY                   4

// mouse click action
#define PE_MOUSE_NOTSUPPORTED   0
#define PE_MOUSE_DOWN           1
#define PE_MOUSE_UP             2
#define PE_MOUSE_DOUBLE_CLICK   3

// mouse click flags (virtual key state-masks)
#define PE_CF_NONE       0x0000
#define PE_CF_LBUTTON    0x0001
#define PE_CF_RBUTTON    0x0002
#define PE_CF_SHIFTKEY   0x0004
#define PE_CF_CONTROLKEY 0x0008
#define PE_CF_MBUTTON    0x0010

// for PE_*_CLICK_EVENT
typedef struct PEMouseClickEventInfo
{
#if defined (__cplusplus)
    PEMouseClickEventInfo ()
    {
        StructSize = sizeof (PEMouseClickEventInfo);
        windowHandle = PE_UNCHANGED;
        clickAction = PE_UNCHANGED;
        clickFlags = PE_UNCHANGED;
        xOffset = 0;
        yOffset = 0;
        //PEValueInfo fieldValue; TODO check if this constructor gets called
        objectHandle = 0;
        sectionCode = PE_UNCHANGED;
    };
#endif

        PEWORD StructSize;
        long windowHandle;
        PEUINT clickAction;           // one of PE_MOUSE_*
        PEUINT clickFlags;            // any combination of PE_CF_*
        int xOffset;                // x-coordinate of mouse click in pixels
        int yOffset;                // y-coordinate of mouse click in pixels
        PEValueInfo fieldValue;     // value of object at click point if it is a field
                                    // object, excluding MEMO and BLOB fields,
                                    // else valueType element = PE_VI_NOVALUE.
        PEDWORD objectHandle;         // the design view object
        short sectionCode;          // section in which click occurred.
} PEMouseClickEventInfo;
#define PE_SIZEOF_MOUSE_CLICK_EVENT_INFO (sizeof(PEMouseClickEventInfo))

// for PE_START_EVENT
typedef struct PEStartEventInfo
{
#if defined (__cplusplus)
    PEStartEventInfo ()
    {
        StructSize = sizeof (PEStartEventInfo);
        destination = PE_UNCHANGED;
    };
#endif

        PEWORD StructSize;
        PEWORD destination;
} PEStartEventInfo;
#define PE_SIZEOF_START_EVENT_INFO (sizeof(PEStartEventInfo))

// for PE_STOP_EVENT
typedef struct PEStopEventInfo
{
#if defined (__cplusplus)
    PEStopEventInfo ()
    {
        StructSize = sizeof (PEStopEventInfo);
        destination = PE_UNCHANGED;
        jobStatus = PE_UNCHANGED;
    };
#endif

        PEWORD StructSize;
        PEWORD destination;
        PEWORD jobStatus; // a PE_JOB constant
} PEStopEventInfo;
#define PE_SIZEOF_STOP_EVENT_INFO (sizeof(PEStopEventInfo))

// for PE_READING_RECORDS_EVENT
typedef struct PEReadingRecordsEventInfo
{
#if defined (__cplusplus)
    PEReadingRecordsEventInfo ()
    {
        StructSize = sizeof (PEReadingRecordsEventInfo);
        cancelled = PE_UNCHANGED;
        recordsRead = PE_UNCHANGED;
        recordsSelected = PE_UNCHANGED;
        done = PE_UNCHANGED;
    };
#endif

        PEWORD StructSize;
        short cancelled; // PEBOOL value.
        long recordsRead;
        long recordsSelected;
        short done;             // PEBOOL value.
} PEReadingRecordsEventInfo;

#define PE_SIZEOF_READING_RECORDS_EVENT_INFO (sizeof(PEReadingRecordsEventInfo))

// use this structure for
// PE_CLOSE_PRINT_WINDOW_EVENT
// PE_PRINT_BUTTON_CLICKED_EVENT
// PE_EXPORT_BUTTON_CLICKED_EVENT
// PE_FIRST_PAGE_BUTTON_CLICKED_EVENT
// PE_PREVIOUS_PAGE_BUTTON_CLICKED_EVENT
// PE_NEXT_PAGE_BUTTON_CLICKED_EVENT
// PE_LAST_PAGE_BUTTON_CLICKED_EVENT
// PE_CANCEL_BUTTON_CLICKED_EVENT
// PE_PRINT_SETUP_BUTTON_CLICKED_EVENT
// PE_REFRESH_BUTTON_CLICKED_EVENT
// PE_ACTIVATE_PRINT_WINDOW_EVENT
// PE_DEACTIVATE_PRINT_WINDOW_EVENT
typedef struct PEGeneralPrintWindowEventInfo
{
#if defined (__cplusplus)
    PEGeneralPrintWindowEventInfo ()
    {
        StructSize = sizeof (PEGeneralPrintWindowEventInfo);
        windowHandle = 0;
    };
#endif

        PEWORD StructSize;
        PEWORD ignored; // for 4 byte alignment. ignore.
        long windowHandle; // PEHWND
} PEGeneralPrintWindowEventInfo;

#define PE_SIZEOF_GENERAL_PRINT_WINDOW_EVENT_INFO (sizeof(PEGeneralPrintWindowEventInfo))

// for PE_ZOOM_CONTROL_SELECTED_EVENT
typedef struct PEZoomLevelChangingEventInfo
{
#if defined (__cplusplus)
    PEZoomLevelChangingEventInfo ()
    {
        StructSize = sizeof (PEZoomLevelChangingEventInfo);
        zoomLevel = PE_UNCHANGED;
        windowHandle = 0;
    };
#endif

        PEWORD StructSize;
        PEWORD zoomLevel;
        long windowHandle;
} PEZoomLevelChaningEventInfo;

#define PE_SIZEOF_ZOOM_LEVEL_CHANGING_EVENT_INFO (sizeof (PEZoomLevelChangingEventInfo))

// for PE_CLOSE_BUTTON_CLICKED_EVENT
typedef struct PECloseButtonClickedEventInfo
{
#if defined (__cplusplus)
    PECloseButtonClickedEventInfo ()
    {
        StructSize = sizeof (PECloseButtonClickedEventInfo);
        viewIndex = PE_UNCHANGED;
        windowHandle = 0;
    };
#endif

        PEWORD StructSize;
        PEWORD viewIndex; // which view is going to be closed. start from zero.
        long windowHandle; // frame window handle the button is on.
} PECloseButtonClickedEventInfo;
#define PE_SIZEOF_CLOSE_BUTTON_CLICKED_EVENT_INFO (sizeof(PECloseButtonClickedEventInfo))

//for PE_SEARCH_BUTTON_CLICKED_EVENT
#define PE_SEARCH_STRING_LEN   128
typedef struct PESearchButtonClickedEventInfo
{
#if defined (__cplusplus)
    PESearchButtonClickedEventInfo ()
    {
        StructSize = sizeof (PESearchButtonClickedEventInfo);
        windowHandle = 0;
        searchString[0] = '\0';
    };
#endif

        long windowHandle;
        char searchString[PE_SEARCH_STRING_LEN];
        PEWORD StructSize;
} PESearchButtonClickedEventInfo;
#define PE_SIZEOF_SEARCH_BUTTON_CLICKED_EVENT_INFO (sizeof(PESearchButtonClickedEventInfo))

//for PE_GROUPTREE_BUTTON_CLICKED_EVENT
typedef struct PEGroupTreeButtonClickedEventInfo
{
#if defined (__cplusplus)
    PEGroupTreeButtonClickedEventInfo ()
    {
        StructSize = sizeof (PEGroupTreeButtonClickedEventInfo);
        visible = PE_UNCHANGED;
        windowHandle = 0;
    };
#endif

        PEWORD StructSize;
        short visible; // PEBOOL value. current state of the group tree button
        long windowHandle;
}PEGroupTreeButtonClickedEventInfo;

#define PE_SIZEOF_GROUP_TREE_BUTTON_CLICKED_EVENT_INFO (sizeof(PEGroupTreeButtonClickedEventInfo))

//for PE_SHOW_GROUP_EVENT
typedef struct PEShowGroupEventInfo
{
#if defined (__cplusplus)
    PEShowGroupEventInfo ()
    {
        StructSize = sizeof (PEShowGroupEventInfo);
        groupLevel = PE_UNCHANGED;
        windowHandle = 0;
        groupList = 0;
    };
#endif

        PEWORD StructSize;
        PEWORD groupLevel;
        long windowHandle;
        // points to an array of group name. memory pointed by group list is freed after calling the call
        // back function.
        char **groupList;
} PEShowGroupEventInfo;
#define PE_SIZEOF_SHOW_GROUP_EVENT_INFO (sizeof(PEShowGroupEventInfo))

//For PE_DRILL_ON_GROUP_EVENT
#define PE_DE_ON_GROUP       0
#define PE_DE_ON_GROUPTREE   1
#define PE_DE_ON_GRAPH       2
#define PE_DE_ON_MAP         3
#define PE_DE_ON_SUBREPORT   4

typedef struct PEDrillOnGroupEventInfo
{
#if defined (__cplusplus)
    PEDrillOnGroupEventInfo ()
    {
        StructSize = sizeof (PEDrillOnGroupEventInfo);
        drillType = PE_UNCHANGED;
        windowHandle = 0;
        groupList = 0;
        groupLevel = 0;
    };
#endif

        PEWORD StructSize;
        PEWORD drillType; // a PE_DE_ constant
        long windowHandle;
        // points to an array of group name. memory pointed by group list is freed after calling the call
        // back function.
        char **groupList;   // points to an array of group name for drillOnGroup, drillOnGroupTree, drillOnGraph, drillOnMap
                            // points to an array with one element, the subreport name, for drillOnSubreport.
        PEWORD groupLevel;
}PEDrillOnGroupEventInfo;
#define PE_SIZEOF_DRILL_ON_GROUP_EVENT_INFO (sizeof(PEDrillOnGroupEventInfo))

// for PE_DRILL_ON_DETAIL_EVENT
typedef struct PEFieldValueInfo
{
#if defined (__cplusplus)
    PEFieldValueInfo ()
    {
        StructSize = sizeof (PEFieldValueInfo);
        fieldName [0] = '\0';
        //PEValueInfo fieldValue; TODO check if this constructor gets called.
    };
#endif

        PEWORD StructSize;
        PEWORD ignored; // for 4 byte alignment. ignore.
        char fieldName[PE_FIELD_NAME_LEN];
        PEValueInfo fieldValue;
} PEFieldValueInfo;
#define PE_SIZEOF_FIELD_VALUE_INFO (sizeof(PEFieldValueInfo))

typedef struct PEDrillOnDetailEventInfo
{
#if defined (__cplusplus)
    PEDrillOnDetailEventInfo ()
    {
        StructSize = sizeof (PEDrillOnDetailEventInfo);
        selectedFieldIndex = PE_UNCHANGED; // -1 if no field selected
        windowHandle = 0;
        fieldValueList = 0;
        nFieldValue = 0; // number of field value in fieldValueList
    };
#endif

    PEWORD StructSize;
    short selectedFieldIndex; // -1 if no field selected
    long windowHandle;
    // points to an array of PEFieldValueInfo. memory pointed by fieldValueList is freed after calling the call
    // back function.
    struct PEFieldValueInfo ** fieldValueList;
    short nFieldValue; // number of field value in fieldValueList
} PEDrillOnDetailEventInfo;
#define PE_SIZEOF_DRILL_ON_DETAIL_EVENT_INFO (sizeof(PEDrillOnDetailEventInfo))

/* -------------------------------------------------------------------------*/

#define PE_TABLE_NAME_LEN 128
#define PE_DATABASE_FIELD_NAME_LEN  128

// Field value type
#define PE_FVT_INT8SFIELD            1
#define PE_FVT_INT8UFIELD            2
#define PE_FVT_INT16SFIELD           3
#define PE_FVT_INT16UFIELD           4
#define PE_FVT_INT32SFIELD           5
#define PE_FVT_INT32UFIELD           6
#define PE_FVT_NUMBERFIELD           7
#define PE_FVT_CURRENCYFIELD         8
#define PE_FVT_BOOLEANFIELD          9
#define PE_FVT_DATEFIELD             10
#define PE_FVT_TIMEFIELD             11
#define PE_FVT_STRINGFIELD           12
#define PE_FVT_TRANSIENTMEMOFIELD    13
#define PE_FVT_PERSISTENTMEMOFIELD   14
#define PE_FVT_BLOBFIELD             15
#define PE_FVT_DATETIMEFIELD         16
#define PE_FVT_BITMAPFIELD           17
#define PE_FVT_ICONFIELD             18
#define PE_FVT_PICTUREFIELD          19
#define PE_FVT_OLEFIELD              20
#define PE_FVT_GRAPHFIELD            21
#define PE_FVT_UNKNOWNFIELD          22

// Field mapping types
#define PE_FM_AUTO_FLD_MAP          0   //Auto field name mapping
                                        //unmapped report fields will be removed
#define PE_FM_CRPE_PROMPT_FLD_MAP   1   //CRPE provided dialog box to map field manually
#define PE_FM_EVENT_DEFINED_FLD_MAP 2   //CPPE provided list of field in report and new database
                                        //User need to activate the PE_MAPPING_FIELD_EVENT
                                        //and define a callback function

PEBOOL CRPE_API PESetFieldMappingType(short printJob,
                                    PEWORD mappingType);

PEBOOL CRPE_API PEGetFieldMappingType(short printJob,
                                    PEWORD FAR * mappingType);

typedef struct PEReportFieldMappingInfo
{
#if defined (__cplusplus)
    PEReportFieldMappingInfo ()
    {
        StructSize = sizeof (PEReportFieldMappingInfo);
        valueType = PE_UNCHANGED;
        tableAliasName[0] = '\0';
        databaseFieldName[0] = '\0';
        mappingTo = PE_UNCHANGED;
    };
#endif

    PEWORD StructSize;
    PEWORD valueType; // a PE_FVT_constant
    char tableAliasName[PE_TABLE_NAME_LEN];
    char databaseFieldName[PE_DATABASE_FIELD_NAME_LEN];
    int mappingTo;   //mapped fields are assigned to the index of a field
                      //in array PEFieldMappingEventInfo->databaseFields
                      //unmapped fields are assigned to -1
} PEReportFieldMappingInfo;
#define PE_SIZEOF_REPORT_FIELDMAPPING_INFO (sizeof(PEReportFieldMappingInfo))

typedef struct PEFieldMappingEventInfo
{
#if defined (__cplusplus)
    PEFieldMappingEventInfo ()
    {
        StructSize = sizeof (PEFieldMappingEventInfo);
        reportFields = 0;
        nReportFields = 0;
        databaseFields = 0;
        nDatabaseFields = 0;
    };
#endif

    PEWORD StructSize;

   PEReportFieldMappingInfo ** reportFields; //An array of fields in the report.
                                            //User need to modify the 'mappingTo' of
                                            //each new mapped field by assigning the value
                                            //of the index of a field in the array
                                            //databaseFields.
   PEWORD nReportFields;                      //Size of array reportFields

   PEReportFieldMappingInfo ** databaseFields; //An array of fields in the new database file
   PEWORD nDatabaseFields;                    //Size of array databaseField
} PEFieldMappingEventInfo;
#define PE_SIZEOF_FIELDMAPPING_EVENT_INFO (sizeof(PEFieldMappingEventInfo))
/* -------------------------------------------------------------------------*/

typedef struct PEHyperlinkEventInfo
{
#if defined (__cplusplus)
    PEHyperlinkEventInfo ()
    {
        StructSize = sizeof (PEHyperlinkEventInfo);
        windowHandle = 0;
        hyperlinkText = 0;
    };
#endif

    PEWORD StructSize;
    PEWORD ignored;               // for 4 byte alignment. ignore.
    long windowHandle;          // PEHWND
    char FAR *hyperlinkText;    // points to the hyperlink text associated with the object.
                                // memory pointed by hyperlinkText is freed after calling the callback function.
} PEHyperlinkEventInfo;

#define PE_SIZEOF_HYPERLINKEVENTINFO (sizeof (PEHyperlinkEventInfo))

typedef struct PELaunchSeagateAnalysisEventInfo
{
#if defined (__cplusplus)
    PELaunchSeagateAnalysisEventInfo ()
    {
        StructSize = sizeof (PELaunchSeagateAnalysisEventInfo);
        windowHandle = 0;
        pathFile = 0;
    };
#endif

    PEWORD StructSize;
    PEWORD ignored;               // for 4 byte alignment. ignore.
    long windowHandle;          // PEHWND
    char FAR *pathFile;         // points to the path and filename of the temporary report.
                                // memory pointed by pathFile is freed after calling the callback function.
} PELaunchSeagateAnalysisEventInfo;

#define PE_SIZEOF_LAUNCH_SEAGATE_ANALYSIS_EVENT_INFO (sizeof (PELaunchSeagateAnalysisEventInfo))

// All events are disabled by default
// use PEEnableEvent to enable events.
typedef struct PEEnableEventInfo
{
#if defined (__cplusplus)
    PEEnableEventInfo ()
    {
        StructSize = sizeof (PEEnableEventInfo);
        startStopEvent = PE_UNCHANGED;
        readingRecordEvent = PE_UNCHANGED;
        printWindowButtonEvent = PE_UNCHANGED;
        drillEvent = PE_UNCHANGED;
        closePrintWindowEvent = PE_UNCHANGED;
        activatePrintWindowEvent = PE_UNCHANGED;
        fieldMappingEvent = PE_UNCHANGED;
        mouseClickEvent = PE_UNCHANGED;
        hyperlinkEvent = PE_UNCHANGED;
        launchSeagateAnalysisEvent = PE_UNCHANGED;
        formattingEvent = PE_UNCHANGED;
    };
#endif

    PEWORD StructSize;
    short startStopEvent; // PEBOOL value, PE_UNCHANGED for no change
    short readingRecordEvent; // PEBOOL value, PE_UNCHANGED for no change
    short printWindowButtonEvent; // PEBOOL value, PE_UNCHANGED for no change
    short drillEvent; // PEBOOL value, PE_UNCHANGED for no change
    short closePrintWindowEvent; // PEBOOL value, PE_UNCHANGED for no change
    short activatePrintWindowEvent; // PEBOOL value, PE_UNCHANGED for no change
    short fieldMappingEvent; // PEBOOL value, PE_UNCHANGED for no change.
    short mouseClickEvent; // PEBOOL value, PE_UNCHANGED for no change.
    short hyperlinkEvent;   // PEBOOL value, PE_UNCHANGED for no change.
    short launchSeagateAnalysisEvent;   // PEBOOL value, PE_UNCHANGED for no change.
    short formattingEvent; // PEBOOL value, PE_UNCHANGED for no change.
} PEEnableEventInfo;

#define PE_SIZEOF_ENABLE_EVENT_INFO (sizeof(PEEnableEventInfo))

PEBOOL CRPE_API PEEnableEvent(short printJob, PEEnableEventInfo FAR * enableEventInfo);
PEBOOL CRPE_API PEGetEnableEventInfo(short printJob, PEEnableEventInfo FAR * enableEventInfo);

// Set callback function
PEBOOL CRPE_API PESetEventCallback(short printJob, PEBOOL (PECALLBACK * callbackProc)(short eventID, void *param, void *userData), void *userData);
/* -------------------------------------------------------------------------*/

// all are window standard cursors except PE_TC_MAGNIFY_CURSOR.
// PE_TC_SIZEALL_CURSOR, PE_TC_NO_CURSOR, PE_TC_APPSTARTING_CURSOR
// and PE_TC_HELP_CURSOR are not supported in 16bit. 
// PE_TC_SIZE_CURSOR and PE_TC_ICON_CURSOR are obsolete for 32bit
// use PE_TC_SIZEALL_CURSOR and PE_TC_ARROW_CURSOR instead.

#define PE_TC_DEFAULT_CURSOR     0 // CRPE set default cursor to be PE_TC_ARRAOW_CURSOR
#define PE_TC_ARROW_CURSOR       1
#define PE_TC_CROSS_CURSOR       2
#define PE_TC_IBEAM_CURSOR       3
#define PE_TC_UPARROW_CURSOR     4
#define PE_TC_SIZEALL_CURSOR     5
#define PE_TC_SIZENWSE_CURSOR    6
#define PE_TC_SIZENESW_CURSOR    7
#define PE_TC_SIZEWE_CURSOR      8
#define PE_TC_SIZENS_CURSOR      9
#define PE_TC_NO_CURSOR          10
#define PE_TC_WAIT_CURSOR        11
#define PE_TC_APPSTARTING_CURSOR 12
#define PE_TC_HELP_CURSOR        13
#define PE_TC_SIZE_CURSOR        14 // for 16bit
#define PE_TC_ICON_CURSOR        15 // for 16bit

 // CRPE specific cusors
#define PE_TC_BACKGROUND_PROCESS_CURSOR 94
#define PE_TC_GRAB_HAND_CURSOR          95
#define PE_TC_ZOOM_IN_CURSOR            96
#define PE_TC_REPORT_SECTION_CURSOR     97
#define PE_TC_HAND_CURSOR               98
#define PE_TC_MAGNIFY_CURSOR            99  // CRPE specific cusor

typedef struct PETrackCursorInfo
{
#if defined (__cplusplus)
    PETrackCursorInfo ()
    {
        StructSize = sizeof (PETrackCursorInfo);
        groupAreaCursor = PE_UNCHANGED;
        groupAreaFieldCursor = PE_UNCHANGED;
        detailAreaCursor = PE_UNCHANGED;
        detailAreaFieldCursor = PE_UNCHANGED;
        graphCursor = PE_UNCHANGED;
        groupAreaCursorHandle = PE_UNCHANGED;
        groupAreaFieldCursorHandle = PE_UNCHANGED;
        detailAreaCursorHandle = PE_UNCHANGED;
        detailAreaFieldCursorHandle = PE_UNCHANGED;
        graphCursorHandle = PE_UNCHANGED;
        ondemandSubreportCursor = PE_UNCHANGED;
        hyperlinkCursor = PE_UNCHANGED;
    };
#endif

        PEWORD StructSize;
        short groupAreaCursor; // a PE_TC constant. PE_UNCHANGED for no change.
        short groupAreaFieldCursor; // a PE_TC constant. PE_UNCHAGNED for no change.
        short detailAreaCursor;  // a PE_TC constant. PE_UNCHANGED for no change
        short detailAreaFieldCursor; // a PE_TC constant. PE_UNCHANGED for no change
        short graphCursor;                      // a PE_TC constant. PE_UNCHANGED for no change.
        long groupAreaCursorHandle; // reserved
        long groupAreaFieldCursorHandle; // reserved
        long detailAreaCursorHandle; // reserved
        long detailAreaFieldCursorHandle; // reserved
        long graphCursorHandle; // reserved
        short ondemandSubreportCursor;  // Cursor to show over on-demand subreports when
                                        // drilldown for the window is enabled;
                                        // default is PE_TC_MAGNIFY_CURSOR.
        short hyperlinkCursor;          // Cursor to show over report object that has hyperlink text;
                                        // default is PE_TC_HAND_CURSOR.
} PETrackCursorInfo;
#define PE_SIZEOF_TRACK_CURSOR_INFO  (sizeof(PETrackCursorInfo))

// set tracking cursor
PEBOOL CRPE_API PESetTrackCursorInfo(short printJob,
                                   PETrackCursorInfo FAR * cursorInfo);
PEBOOL CRPE_API PEGetTrackCursorInfo(short printJob,
                                   PETrackCursorInfo FAR * cursorInfo);

/* ******************************* */
/* Report Alerting                 */
/* ******************************* */

typedef struct PEReportAlertInfo
{
#if defined (__cplusplus)
    PEReportAlertInfo ()
    {
        StructSize = sizeof (PEReportAlertInfo);
        nameLength = PE_UNCHANGED;
        name = 0;
        isEnabled = PE_UNCHANGED;
        alertConditionLength = PE_UNCHANGED;
        alertConditionFormula = 0;
        nTriggeredInstances = 0;
        alertMessageLength = 0;
        defaultAlertMessageLength = 0;
        alertMessageFormula = 0;
        defaultAlertMessage = 0;
    };
#endif

    PEWORD StructSize;    // initialized to be PE_SIZEOF_REPORT_ALERT_INFO
    short nameLength;
    PEHANDLE name;        // NOTE: must release HANDLEs even not using them
    short isEnabled;    // PETRUE if alert is enabled, else PEFALSE
    short alertConditionLength;
    PEHANDLE alertConditionFormula;
    PEDWORD nTriggeredInstances;  // the number of times the alert was triggered
    short alertMessageLength;
    short defaultAlertMessageLength;
    PEHANDLE alertMessageFormula;
    PEHANDLE defaultAlertMessage;
} PEReportAlertInfo;
#define PE_SIZEOF_REPORT_ALERT_INFO (sizeof (PEReportAlertInfo))

typedef struct PEAlertInstanceInfo
{
#if defined (__cplusplus)
    PEAlertInstanceInfo ()
    {
        StructSize = sizeof (PEAlertInstanceInfo);
        alertMessageLength = PE_UNCHANGED;
        alertMessage = 0;
    };
#endif

    PEWORD StructSize;    // initialized to be PE_SIZEOF_ALERT_INSTANCE_INFO
    short alertMessageLength;
    PEHANDLE alertMessage;
} PEAlertInstanceInfo;

#define PE_SIZEOF_ALERT_INSTANCE_INFO (sizeof (PEAlertInstanceInfo))

short CRPE_API PEGetNReportAlerts (short printJob);  // return -1 if failed.

PEBOOL CRPE_API PEGetNthReportAlert (short printJob,
                                   short alertN,
                                   PEReportAlertInfo FAR * reportAlertInfo);

PEBOOL CRPE_API PEGetNthAlertInstanceInfo (short printJob,
                                         short alertN,
                                         PEDWORD instanceN,
                                         PEAlertInstanceInfo FAR * alertInstanceInfo);

PEBOOL CRPE_API PESetNthAlertConditionFormula (short printJob,
                                             short alertN,
                                             const char FAR *formula);

PEBOOL CRPE_API PESetNthAlertMessageFormula (short printJob,
                                           short alertN,
                                           const char FAR *formula);

PEBOOL CRPE_API PESetNthAlertDefaultMessage (short printJob,
                                           short alertN,
                                           const char FAR *text);

PEBOOL CRPE_API PEEnableNthAlert (short printJob,
                                short alertN,
                                PEBOOL enabled);

/* ******************************* */
/* Formula Syntax                  */
/* ******************************* */

#define PE_FS_SIZE      2

#define PE_FST_CRYSTAL   0
#define PE_FST_BASIC     1

typedef struct PEFormulaSyntax
{
#if defined (__cplusplus)
    PEFormulaSyntax ()
    {
        StructSize = sizeof (PEFormulaSyntax);
        memset (formulaSyntax, 0, PE_FS_SIZE * sizeof (short));
    };
#endif

    PEWORD StructSize;
    short formulaSyntax [PE_FS_SIZE];           // PE_FST_* or PE_UNCHANGED.
} PEFormulaSyntax;

#define PE_SIZEOF_FORMULA_SYNTAX (sizeof (PEFormulaSyntax))

// PESetFormulaSyntax
// Use this API to set the syntax to use in the next (and all successive)
// formula API call(s).
// Set one of PE_FST_* into formulaSyntax[0];
// formulaSyntax[1] is reserved for internal use.
// ***Default Behaviour: If any Formula API is called before calling
//                       PESetFormulaSyntax then PE_FST_CRYSTAL is assumed.
/////////////////////////////////////////////////////////////////////////
PEBOOL CRPE_API PESetFormulaSyntax (short printJob, PEFormulaSyntax FAR *formulaSyntax);

// PEGetFormulaSyntax
// Indicates the syntax used by the formula addressed in the last formula API call.
// The syntax type is returned in formulaSyntax[0];
// formulaSyntax[1] is reserved for internal use.
// ***Default Behaviour: If this API is called before any Formula API is called
//                       then the values returned will be PE_UNCHANGED.
///////////////////////////////////////////////////////////////////////////////////
PEBOOL CRPE_API PEGetFormulaSyntax (short printJob, PEFormulaSyntax FAR *formulaSyntax);

// for 4.x version
#define PE_ALLLINES  -1

#if defined (__cplusplus)
}
#endif

// Reset structure alignment
#if defined (__BORLANDC__)
  #pragma option -a.
#elif defined (_MSC_VER)
  #if _MSC_VER >= 900
    #pragma pack (pop)
  #else
    #pragma pack ()
  #endif
#endif

#endif // CRPE_H
