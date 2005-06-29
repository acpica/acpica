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

#include "acpiobj.h"


/*
 * Debug levels and component IDs.  These are used to control the
 * granularity of the output of the DEBUG_PRINT macro -- on a per-
 * component basis and a per-exception-type basis.
 */

/* Component IDs -- used in the global "DebugLayer" */

#define GLOBAL                      0x00000001
#define INTERPRETER                 0x00000002
#define NAMESPACE                   0x00000004
#define DEVICE_MANAGER              0x00000008
#define RESOURCE_MANAGER            0x00000010
#define EVENT_HANDLING              0x00000020
#define MISCELLANEOUS               0x00000040
#define OS_DEPENDENT                0x00000080

#define ALL_COMPONENTS              0x000000FF


/* Exception level or Trace level -- used in the global "DebugLevel" */

#define ACPI_SUCCESS                0x00000001
#define ACPI_INFO                   0x00000002
#define ACPI_WARN                   0x00000004
#define ACPI_ERROR                  0x00000008
#define ACPI_FATAL                  0x00000010
#define ACPI_ALL                    0x0000001F

#define TRACE_LOAD                  0x00000100
#define TRACE_OPCODE                0x00000200
#define TRACE_STACK                 0x00000400
#define TRACE_EXEC                  0x00000800
#define TRACE_NAMES                 0x00001000
#define TRACE_OPREGION              0x00002000
#define TRACE_BFIELD                0x00004000
#define TRACE_TRASH                 0x00008000
#define TRACE_TABLES                0x00010000
#define TRACE_FUNCTIONS             0x00020000
#define TRACE_VALUES                0x00040000
#define TRACE_OBJECTS               0x00080000
#define TRACE_IO                    0x00100000
#define TRACE_INTERRUPTS            0x00800000
#define TRACE_ALL                   0x001FFF00

/* Exceptionally verbose output -- used in the global "DebugLevel"  */

#define VERBOSE_INFO                0x01000000
#define VERBOSE_TABLES              0x02000000

/* Defaults for DebugLevel, debug and normal */

#define DEBUG_DEFAULT               0x0011001D  /* Tables, I/O, errors, success */
#define NORMAL_DEFAULT              0x0000001D  /* errors, warnings, success */

/* Misc defines */

#define HEX                         0x01
#define ASCII                       0x02
#define FULL_ADDRESS                0x04
#define CHARS_PER_LINE              16      /* used in DumpBuf function */



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


/* Prototypes */

INT32
GetDebugLevel (void);

void
SetDebugLevel (
    INT32               level);

void
FunctionTrace (
    char                *ModuleName, 
    INT32               LineNumber, 
    INT32               ComponentId, 
    char                *FunctionName);

void
DebugPrintPrefix (
    char                *ModuleName, 
    INT32               LineNumber, 
    INT32               ComponentId);

void
DebugPrint (
    char                *ModuleName, 
    INT32               LineNumber, 
    INT32               ComponentId, 
    INT32               PrintLevel, 
    char                *Format, ...);

void
DebugPrintRaw (
    char                *Format, ...);

void
_ReportInfo (
    char                *ModuleName, 
    INT32               LineNumber, 
    INT32               ComponentId, 
    ST_KEY_DESC_TABLE   *KdtEntry);

void
_ReportError (
    char                *ModuleName, 
    INT32               LineNumber, 
    INT32               ComponentId, 
    ST_KEY_DESC_TABLE   *KdtEntry);

void
_ReportWarning (
    char                *ModuleName, 
    INT32               LineNumber, 
    INT32               ComponentId, 
    ST_KEY_DESC_TABLE   *KdtEntry);

void
_ReportSuccess (
    char                *ModuleName, 
    INT32               LineNumber, 
    INT32               ComponentId, 
    ST_KEY_DESC_TABLE   *KdtEntry);

void 
DumpBuffer (
    char               *Buffer, 
    UINT32              Count, 
    INT32               Flags, 
    INT32               componentId);

void
DumpObjectDescriptor (
	OBJECT_DESCRIPTOR *Obj);

void 
_Kinc_error (char *, INT32, INT32, char *, INT32, INT32); 
void 
_Kinc_info (char *, INT32, INT32, char *, INT32, INT32); 
void 
_Kinc_warning (char *, INT32, INT32, char *, INT32, INT32);


/*
 * Memory allocation functions.
 * Macros that expand to include filename and line number
 *
 * TBD:  Move to a more appropriate header!!
 *
 */

void *
_AllocateObjectDesc (
    char                *ModuleName, 
    INT32               LineNumber, 
    INT32               ComponentId, 
    ST_KEY_DESC_TABLE   *KdtEntry);

void *
_LocalAllocate (
    char                *ModuleName, 
    INT32               LineNumber, 
    INT32               ComponentId, 
    INT32               AllocSize);

void *
_LocalCallocate (
    char                *ModuleName, 
    INT32               LineNumber, 
    INT32               ComponentId, 
    INT32               AllocSize);

#define LocalAllocate(a)                _LocalAllocate(_THIS_MODULE,__LINE__,_COMPONENT,a)
#define LocalCallocate(a)               _LocalCallocate(_THIS_MODULE,__LINE__,_COMPONENT,a)
#define AllocateObjectDesc(a)           _AllocateObjectDesc(_THIS_MODULE,__LINE__,_COMPONENT,a)



/*
 * Reporting macros that are never compiled out
 */

/* Error reporting.  These versions add callers module/line# */

#define REPORT_INFO(a)                  _ReportInfo(_THIS_MODULE,__LINE__,_COMPONENT,a)
#define REPORT_ERROR(a)                 _ReportError(_THIS_MODULE,__LINE__,_COMPONENT,a)
#define REPORT_WARNING(a)               _ReportWarning(_THIS_MODULE,__LINE__,_COMPONENT,a)
#define REPORT_SUCCESS(a)               _ReportSuccess(_THIS_MODULE,__LINE__,_COMPONENT,a)

/* Error reporting.  These versions pass thru the module/line# */

#define _REPORT_INFO(a,b,c,d)           _ReportInfo(a,b,c,d)
#define _REPORT_ERROR(a,b,c,d)          _ReportError(a,b,c,d)
#define _REPORT_WARNING(a,b,c,d)        _ReportWarning(a,b,c,d)


/* Buffer dump macros */

#define DUMP_BUFFER(a,b,c)              DumpBuffer((char *)a,b,c,_COMPONENT)


/*
 * Debug macros that are conditionally compiled
 */

#ifdef _DEBUG

/* Function entry tracing */

#define FUNCTION_TRACE(a)               FunctionTrace(_THIS_MODULE,__LINE__,_COMPONENT,a)

/* Stack and buffer dumping */

#define DUMP_STACK_ENTRY(a)             DumpStackEntry(a)
#define DUMP_STACK(a,b,c,d)             DumpStack(a,b,c,d)
#define DUMP_ENTRY(a)                   NsDumpEntry (a)
#define DUMP_TABLES(a,b)                NsDumpTables(a,b)

/* 
 * Master debug print macros 
 * Print iff:
 *    1) Debug print for the current component is enabled
 *    2) Debug error level or trace level for the print statement is enabled
 *
 */

#define	PARAM_LIST(PL) PL
#define TEST_DEBUG_SWITCH(lvl)          if ((lvl & DebugLevel) && (_COMPONENT & DebugLayer))

#define DEBUG_PRINT(lvl,fp)             TEST_DEBUG_SWITCH(lvl) {\
                                            DebugPrintPrefix (_THIS_MODULE,__LINE__,_COMPONENT);\
                                            DebugPrintRaw PARAM_LIST(fp);}

#define DEBUG_PRINT_RAW(lvl,fp)         TEST_DEBUG_SWITCH(lvl) {\
                                            DebugPrintRaw PARAM_LIST(fp);}

#define DEBUG_EXEC(a)                   a;

#else

/* Non-debug case -- make everything go away */

#define FUNCTION_TRACE(a)
#define DUMP_STACK_ENTRY(a)
#define DUMP_STACK(a,b,c,d)
#define DUMP_ENTRY(a)
#define DUMP_TABLES(a,b)

#define DEBUG_PRINT(l,f)
#define DEBUG_PRINT_RAW(l,f) 
#define DEBUG_EXEC(a)                       

#endif



/********************************************************************************************
 *
 * Obsolete??
 */

#ifdef _SCREEN_IO
#define LINE_SET(a,b)                   LineSet(a,b)
#else
#define LINE_SET(a,b)
#endif

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

/* 
 * fflush_bu and fflushall_bu have been changed to be identical and are implemented
 *  as macros.  They both always return E_OK and flush all open logfiles 
 */

/* OLD:  these called file primitives 
 *
 * #define flushall_bu() (CloseOFT(),RestoreOFT(),OsdFlushall())
 * #define fflush_bu(x) flushall_bu()
 *
 * NEW: do nothing
 */

#define flushall_bu()
#define fflush_bu(x)

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


INT32
AcpiInit (char          *FileName);



#endif /* _OUTPUT_H */
