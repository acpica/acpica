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
FunctionTrace (INT32 LineNumber, char *ModuleName, char * FunctionName);
void
DebugPrint (INT32 LineNumber, char *ModuleName, INT32 DebugLevel, char *Format, ...);
void
DebugPrintRaw (INT32 DebugLevel, char *Format, ...);
void
_ReportInfo (ST_KEY_DESC_TABLE *KdtEntry, INT32 LineNumber, char *ModuleName);
void
_ReportError (ST_KEY_DESC_TABLE *KdtEntry, INT32 LineNumber, char *ModuleName);
void
_ReportWarning (ST_KEY_DESC_TABLE *KdtEntry, INT32 LineNumber, char *ModuleName);
void 
_Kinc_error (char *, INT32, INT32, char *, INT32, INT32); 
void 
_Kinc_info (char *, INT32, INT32, char *, INT32, INT32); 
void 
_Kinc_warning (char *, INT32, INT32, char *, INT32, INT32);



#define dump_buf(Buf, len, flags) _dump_buf (Buf, len, flags, 0, SCREEN | LOGFILE)

void
_dump_buf (
    void        *buf,
    UINT32      len,
    INT32       flags,
    LogHandle   Logfile,
    INT32       LogFlags);

void DumpBuf(UINT8*Buffer, UINT32 Count, INT32 Flags, LogHandle LogFile,
    INT32 iLogFlags);

#define DumpBuffer(Buffer, Count, Flags) \
    DumpBuf(Buffer, Count, Flags, 0, SCREEN | LOGFILE)


/*
 * TBD:  Move to a more appropriate header!!
 *
 * Memory allocation functions.
 * Macros that expand to include filename and line number
 */

void *
_AllocateObjectDesc (ST_KEY_DESC_TABLE *KdtEntry, INT32 LineNumber, char *ModuleName);
void *
_LocalAllocate (INT32 AllocSize, INT32 LineNumber, char *ModuleName);
void *
_LocalCallocate (INT32 AllocSize, INT32 LineNumber, char *ModuleName);

#define LocalAllocate(a)                _LocalAllocate(a,__LINE__,_THIS_MODULE)
#define LocalCallocate(a)               _LocalCallocate(a,__LINE__,_THIS_MODULE)
#define AllocateObjectDesc(a)           _AllocateObjectDesc(a,__LINE__,_THIS_MODULE)

/* 
 * Trace macro.
 * Used to trace procedure entries
 */

#ifdef _TRACE
#define FUNCTION_TRACE(a)     FunctionTrace (__LINE__,_THIS_MODULE,a)
#else
#define FUNCTION_TRACE(a)
#endif

#ifdef _SCREEN_IO
#define LINE_SET(a,b)                   LineSet(a,b)
#else
#define LINE_SET(a,b)
#endif

/*
 * Debug macros
 */

#ifdef _DEBUG

/* Error reporting.  These versions add callers module/line# */

#define REPORT_INFO(a)                  _ReportInfo(a,__LINE__,_THIS_MODULE)
#define REPORT_ERROR(a)                 _ReportError(a,__LINE__,_THIS_MODULE)
#define REPORT_WARNING(a)               _ReportWarning(a,__LINE__,_THIS_MODULE)

/* Error reporting.  These versions pass thru the module/line# */

#define _REPORT_INFO(a,b,c)             _ReportInfo(a,b,c)
#define _REPORT_ERROR(a,b,c)            _ReportError(a,b,c)
#define _REPORT_WARNING(a,b,c)          _ReportWarning(a,b,c)

/* Stack and buffer dumping */

#define DUMP_STACK_ENTRY(a)             DumpStackEntry(a)
#define DUMP_STACK(a,b,c,d)             DumpStack(a,b,c,d)
#define DUMP_ENTRY(a)                   NsDumpEntry (a, LOGFILE)
#define DUMP_BUFFER(a,b,c)              DumpBuffer(a,b,c)
#define DUMP_CODE(a)                    DumpCode(a)

/* Master debug print macros */

#define DEBUG_PRINT(l,f)                            DebugPrint(__LINE__,_THIS_MODULE,l,f)
#define DEBUG_PRINT1(l,f,a)                         DebugPrint(__LINE__,_THIS_MODULE,l,f,a)
#define DEBUG_PRINT2(l,f,a,b)                       DebugPrint(__LINE__,_THIS_MODULE,l,f,a,b)
#define DEBUG_PRINT3(l,f,a,b,c)                     DebugPrint(__LINE__,_THIS_MODULE,l,f,a,b,c)
#define DEBUG_PRINT4(l,f,a,b,c,d)                   DebugPrint(__LINE__,_THIS_MODULE,l,f,a,b,c,d)
#define DEBUG_PRINT5(l,f,a,b,c,d,e)                 DebugPrint(__LINE__,_THIS_MODULE,l,f,a,b,c,d,e)
#define DEBUG_PRINT6(l,f,a,b,c,d,e,g)               DebugPrint(__LINE__,_THIS_MODULE,l,f,a,b,c,d,e,g)
#define DEBUG_PRINT7(l,f,a,b,c,d,e,g,h)             DebugPrint(__LINE__,_THIS_MODULE,l,f,a,b,c,d,e,g,h)
#define DEBUG_PRINT10(l,f,a,b,c,d,e,g,h,i,j,k)      DebugPrint(__LINE__,_THIS_MODULE,l,f,a,b,c,d,e,g,h,i,j,k)

#define DEBUG_PRINT_RAW(l,f)                        DebugPrintRaw(l,f)
#define DEBUG_PRINT1_RAW(l,f,a)                     DebugPrintRaw(l,f,a)
#define DEBUG_PRINT2_RAW(l,f,a,b)                   DebugPrintRaw(l,f,a,b)
#define DEBUG_PRINT3_RAW(l,f,a,b,c)                 DebugPrintRaw(l,f,a,b,c)
#define DEBUG_PRINT4_RAW(l,f,a,b,c,d)               DebugPrintRaw(l,f,a,b,c,d)
#define DEBUG_PRINT5_RAW(l,f,a,b,c,d,e)             DebugPrintRaw(l,f,a,b,c,d,e)
#define DEBUG_PRINT6_RAW(l,f,a,b,c,d,e,g)           DebugPrintRaw(l,f,a,b,c,d,e,g)
#define DEBUG_PRINT7_RAW(l,f,a,b,c,d,e,g,h)         DebugPrintRaw(l,f,a,b,c,d,e,g,h)
#define DEBUG_PRINT10_RAW(l,f,a,b,c,d,e,g,h,i,j,k)  DebugPrintRaw(l,f,a,b,c,d,e,g,h,i,j,k)

#else

#define _REPORT_INFO(a,b,c)
#define _REPORT_ERROR(a,b,c)
#define _REPORT_WARNING(a,b,c)

#define REPORT_INFO(a) 
#define REPORT_ERROR(a) 
#define REPORT_WARNING(a)

#define DUMP_STACK_ENTRY(a)
#define DUMP_STACK(a,b,c,d)
#define DUMP_ENTRY(a)
#define DUMP_BUFFER(a,b,c)
#define DUMP_CODE(a)

#define DEBUG_PRINT(l,f)
#define DEBUG_PRINT1(l,f,a)
#define DEBUG_PRINT2(l,f,a,b)
#define DEBUG_PRINT3(l,f,a,b,c)
#define DEBUG_PRINT4(l,f,a,b,c,d)
#define DEBUG_PRINT5(l,f,a,b,c,d,e)
#define DEBUG_PRINT6(l,f,a,b,c,d,e,g)
#define DEBUG_PRINT7(l,f,a,b,c,d,e,g,h)
#define DEBUG_PRINT10(l,f,a,b,c,d,e,g,h,i,j,k)

#define DEBUG_PRINT_RAW(l,f)                        
#define DEBUG_PRINT1_RAW(l,f,a)                     
#define DEBUG_PRINT2_RAW(l,f,a,b)                   
#define DEBUG_PRINT3_RAW(l,f,a,b,c)                 
#define DEBUG_PRINT4_RAW(l,f,a,b,c,d)               
#define DEBUG_PRINT5_RAW(l,f,a,b,c,d,e)             
#define DEBUG_PRINT6_RAW(l,f,a,b,c,d,e,g)           
#define DEBUG_PRINT7_RAW(l,f,a,b,c,d,e,g,h)         
#define DEBUG_PRINT10_RAW(l,f,a,b,c,d,e,g,h,i,j,k)  


#endif



#define GLOBAL_INFO                 0x00000001
#define GLOBAL_WARN                 0x00000002
#define GLOBAL_ERROR                0x00000004
#define GLOBAL_FATAL                0x00000008
#define GLOBAL_ALL                  0x0000000F

#define AML_INFO                    0x00000010
#define AML_WARN                    0x00000020
#define AML_ERROR                   0x00000040

#define NS_INFO                     0x00000080
#define NS_WARN                     0x00000100
#define NS_ERROR                    0x00000200

#define DV_INFO                     0x00000400
#define DV_WARN                     0x00000800
#define DV_ERROR                    0x00001000

#define EV_INFO                     0x00002000
#define EV_WARN                     0x00004000
#define EV_ERROR                    0x00008000

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
