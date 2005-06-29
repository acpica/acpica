/*
  __________________________________________________________________________
 |
 |
 |           Copyright (C) Intel Corporation 1994-1996
 |
 | All rights reserved.  No part of this program or publication may be
 | reproduced, transmitted, transcribed, stored in a retrieval system, or
 | translated into any language or computer language, in any form or by any
 | means, electronic, mechanical, magnetic, optical, chemical, manual, or
 | otherwise, without the prior written permission of Intel Corporation.
 |__________________________________________________________________________
 |
 | FILENAME: output.h -- debug macros and procedures
 |__________________________________________________________________________
*/

#ifndef _OUTPUT_H
#define _OUTPUT_H

/*
 * Debug/Error reporting table definition
 */

typedef struct
{
    char            *Key;
    char            Level;
    char            *Description;
    char            *Description2;

} ST_KEY_DESC_TABLE;



#define HEX                 0x01
#define ASCII               0x02
#define FULL_ADDRESS        0x04
#define CHARS_PER_LINE      16      /* used in DumpBuf function */


/* Prototypes */

INT32
GetDebugLevel (void);
void
SetDebugLevel (INT32 level);
void
FunctionTrace (char *ModuleName, INT32 LineNumber, char * FunctionName);
void
DebugPrintPrefix (char *ModuleName, INT32 LineNumber);
void
DebugPrint (char *ModuleName, INT32 LineNumber, INT32 PrintLevel, char *Format, ...);
void
DebugPrintRaw (char *Format, ...);
void
_ReportInfo (char *ModuleName, INT32 LineNumber, ST_KEY_DESC_TABLE *KdtEntry);
void
_ReportError (char *ModuleName, INT32 LineNumber, ST_KEY_DESC_TABLE *KdtEntry);
void
_ReportWarning (char *ModuleName, INT32 LineNumber, ST_KEY_DESC_TABLE *KdtEntry);
void
_ReportSuccess (char *ModuleName, INT32 LineNumber, ST_KEY_DESC_TABLE *KdtEntry);
void 
_Kinc_error (char *, INT32, INT32, char *, INT32, INT32); 
void 
_Kinc_info (char *, INT32, INT32, char *, INT32, INT32); 
void 
_Kinc_warning (char *, INT32, INT32, char *, INT32, INT32);

void
_dump_buf (
    void        *buf,
    UINT32      len,
    INT32       flags,
    LogHandle   Logfile,
    INT32       LogFlags);

void DumpBuf (UINT8*Buffer, UINT32 Count, INT32 Flags, LogHandle LogFile,
                INT32 iLogFlags);

#define dump_buf(Buf,len,flags)             _dump_buf(Buf,len,flags,0,SCREEN | LOGFILE)
#define DumpBuffer(Buffer, Count, Flags)    DumpBuf(Buffer, Count, Flags, 0, SCREEN | LOGFILE)


/*
 * TBD:  Move to a more appropriate header!!
 *
 * Memory allocation functions.
 * Macros that expand to include filename and line number
 */

void *
_AllocateObjectDesc (char *ModuleName, INT32 LineNumber, ST_KEY_DESC_TABLE *KdtEntry);
void *
_LocalAllocate (char *ModuleName, INT32 LineNumber, INT32 AllocSize);
void *
_LocalCallocate (char *ModuleName, INT32 LineNumber, INT32 AllocSize);

#define LocalAllocate(a)                _LocalAllocate(_THIS_MODULE,__LINE__,a)
#define LocalCallocate(a)               _LocalCallocate(_THIS_MODULE,__LINE__,a)
#define AllocateObjectDesc(a)           _AllocateObjectDesc(_THIS_MODULE,__LINE__,a)

/* 
 * Trace macro.
 * Used to trace procedure entries
 */

#ifdef _TRACE
#define FUNCTION_TRACE(a)               FunctionTrace (_THIS_MODULE,__LINE__,a)
#else
#define FUNCTION_TRACE(a)
#endif

#ifdef _SCREEN_IO
#define LINE_SET(a,b)                   LineSet(a,b)
#else
#define LINE_SET(a,b)
#endif

/*
 * Reporting macros that are never compiled out
 */

/* Error reporting.  These versions add callers module/line# */

#define REPORT_INFO(a)                  _ReportInfo(_THIS_MODULE,__LINE__,a)
#define REPORT_ERROR(a)                 _ReportError(_THIS_MODULE,__LINE__,a)
#define REPORT_WARNING(a)               _ReportWarning(_THIS_MODULE,__LINE__,a)
#define REPORT_SUCCESS(a)               _ReportSuccess(_THIS_MODULE,__LINE__,a)

/* Error reporting.  These versions pass thru the module/line# */

#define _REPORT_INFO(a,b,c)             _ReportInfo(a,b,c)
#define _REPORT_ERROR(a,b,c)            _ReportError(a,b,c)
#define _REPORT_WARNING(a,b,c)          _ReportWarning(a,b,c)


/*
 * Debug macros that are conditionally compiled
 */


#ifdef _DEBUG

/* Stack and buffer dumping */

#define DUMP_STACK_ENTRY(a)             DumpStackEntry(a)
#define DUMP_STACK(a,b,c,d)             DumpStack(a,b,c,d)
#define DUMP_ENTRY(a)                   NsDumpEntry (a, LOGFILE)
#define DUMP_BUFFER(a,b,c)              DumpBuffer(a,b,c)
#define DUMP_CODE(a)                    DumpCode(a)

/* Master debug print macros */

#define	PARAM_LIST(PL) PL

#define DEBUG_PRINT(lvl,fp)            if (lvl & DebugLevel) {\
                                            DebugPrintPrefix (_THIS_MODULE,__LINE__);\
                                            DebugPrintRaw PARAM_LIST(fp);}

#define DEBUG_PRINT_RAW(lvl,fp)        if (lvl & DebugLevel) {\
                                            DebugPrintRaw PARAM_LIST(fp);}


#else

#define DUMP_STACK_ENTRY(a)
#define DUMP_STACK(a,b,c,d)
#define DUMP_ENTRY(a)
#define DUMP_BUFFER(a,b,c)
#define DUMP_CODE(a)

#define DEBUG_PRINT(l,f)
#define DEBUG_PRINT_RAW(l,f)                        

#endif


/* Various debug print levels, controlled by global DebugLevel */


#define GLOBAL_SUCCESS              0x00000001
#define GLOBAL_ERROR                0x00000002
#define GLOBAL_WARN                 0x00000004
#define GLOBAL_INFO                 0x00000008
#define GLOBAL_ALL                  0x0000000F

#define AML_ERROR                   0x00000010
#define AML_WARN                    0x00000020
#define AML_INFO                    0x00000040

#define NS_ERROR                    0x00000080
#define NS_WARN                     0x00000100
#define NS_INFO                     0x00000200

#define DV_ERROR                    0x00000400
#define DV_WARN                     0x00000800
#define DV_INFO                     0x00001000

#define EV_ERROR                    0x00002000
#define EV_WARN                     0x00004000
#define EV_INFO                     0x00008000

#define TRACE_LOAD                  0x00100000
#define TRACE_OPCODE                0x00200000
#define TRACE_STACK                 0x00400000
#define TRACE_EXEC                  0x00800000
#define TRACE_NAMES                 0x01000000
#define TRACE_OPREGION              0x02000000
#define TRACE_BFIELD                0x04000000
#define TRACE_TRASH                 0x08000000
#define TRACE_OPCODE_EXEC           0x00A00000
#define TRACE_TABLES                0x10000000
#define TRACE_FUNCTIONS             0x20000000



/********************************************************************************************
 *
 * Obsolete??
 */

/* flags for print_message, inc_warning, inc_error, and inc_info. */

#define NO_PRINT        0                  /* quietly increment the count */
#define PRINT           1                  /* print the word "ERROR " (or
                                            * "WARNING " or "INFO ") */
#define PREPEND_CRLF    2                  /* prepend CRLF before printing
                                            * "ERROR " (or "WARNING " or
                                            * "INFO ") */
#define APPEND_CRLF 4                      /* append CRLF after printing
                                            * "ERROR " (or "WARNING " or
                                            * "INFO ") */
#define PACRLF          (PRINT | APPEND_CRLF)
#define FILE_LINE       8                  /* print file and line message was
                                            * generated from. */
#define NO_INC          16                 /* not increase a global count */

#define SCREEN          1
#define LOGFILE         2


/* 
 * The following functions deal with the indent level.  The concept is that
 *  if the library is allowed to maintain the indent level rather than doing
 *  it explicitly in the printf_bu format string, an output function can print
 *  correctly no matter where it's called from.
 */


#define SetIndentAfterNewLine(NewValue) _SetIndentAfterNewLine ((BOOLEAN) NewValue)

BOOLEAN
_SetIndentAfterNewLine (BOOLEAN NewValue);
BOOLEAN
GetIndentAfterNewLine (void);
INT32
IncIndent (void);
INT32
DecIndent (void);
INT32
SetIndent (INT32 i);
INT32
GetIndent (void);
char *
pIndent (void);
void
CloseOFT (void);
void
RestoreOFT (void);

/*
LogHandle
GetMasterLogHandle (void);
*/


/* 
 * fflush_bu and fflushall_bu have been changed to be identical and are implemented
 *  as macros.  They both always return E_OK and flush all open logfiles 
 */
#define flushall_bu() (CloseOFT(),RestoreOFT(),OsdFlushall())
#define fflush_bu(x) flushall_bu()

/* Log file open mode... */

#define OVERWRITE       0
#define APPEND          1
#define FORCE_WRITES    2

LogHandle
open_log (
    char        *filename,                      /* name of logfile to open. */
    INT32       mode);                          /* OVERWRITE, APPEND, FORCE_WRITES */

INT32
close_log (LogHandle handle);                             /* LogHandle to close */



/* Orphaned prototypes TBD:  move to appropriate header !!!*/

UINT8
checksum (
    void                *Buf,
    UINT32              BufSize);


UINT32
InstallInterruptHandler (
    UINT8               InterruptNumber,
    INT32               (* Isr)(void),
    UINT8               InterruptTaskFlag,
    UINT32 *            ExceptPtr);

INT32
RemoveInterruptHandler (UINT32 Key);

INT32
AcpiInit (char          *FileName);



#endif /* _OUTPUT_H */
