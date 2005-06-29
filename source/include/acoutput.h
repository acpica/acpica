
/******************************************************************************
 * 
 * Name: output.h -- debug macros and procedures
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999, Intel Corp.  All rights 
 * reserved.
 *
 * 2. License
 * 
 * 2.1. Intel grants, free of charge, to any person ("Licensee") obtaining a 
 * copy of the source code appearing in this file ("Covered Code") a license 
 * under Intel's copyrights in the base code distributed originally by Intel 
 * ("Original Intel Code") to copy, make derivatives, distribute, use and 
 * display any portion of the Covered Code in any form; and
 *
 * 2.2. Intel grants Licensee a non-exclusive and non-transferable patent 
 * license (without the right to sublicense), under only those claims of Intel
 * patents that are infringed by the Original Intel Code, to make, use, sell, 
 * offer to sell, and import the Covered Code and derivative works thereof 
 * solely to the minimum extent necessary to exercise the above copyright 
 * license, and in no event shall the patent license extend to any additions to
 * or modifications of the Original Intel Code.  No other license or right is 
 * granted directly or by implication, estoppel or otherwise;
 *
 * the above copyright and patent license is granted only if the following 
 * conditions are met:
 *
 * 3. Conditions 
 *
 * 3.1. Redistribution of source code of any substantial portion of the Covered 
 * Code or modification must include the above Copyright Notice, the above 
 * License, this list of Conditions, and the following Disclaimer and Export 
 * Compliance provision.  In addition, Licensee must cause all Covered Code to 
 * which Licensee contributes to contain a file documenting the changes 
 * Licensee made to create that Covered Code and the date of any change.  
 * Licensee must include in that file the documentation of any changes made by
 * any predecessor Licensee.  Licensee must include a prominent statement that
 * the modification is derived, directly or indirectly, from Original Intel 
 * Code.
 *
 * 3.2. Redistribution in binary form of any substantial portion of the Covered 
 * Code or modification must reproduce the above Copyright Notice, and the 
 * following Disclaimer and Export Compliance provision in the documentation 
 * and/or other materials provided with the distribution.
 *
 * 3.3. Intel retains all right, title, and interest in and to the Original 
 * Intel Code.
 *
 * 3.4. Neither the name Intel nor any other trademark owned or controlled by 
 * Intel shall be used in advertising or otherwise to promote the sale, use or 
 * other dealings in products derived from or relating to the Covered Code 
 * without prior written authorization from Intel.
 *
 * 4. Disclaimer and Export Compliance
 *
 * 4.1. INTEL MAKES NO WARRANTY OF ANY KIND REGARDING ANY SOFTWARE PROVIDED 
 * HERE.  ANY SOFTWARE ORIGINATING FROM INTEL OR DERIVED FROM INTEL SOFTWARE 
 * IS PROVIDED "AS IS," AND INTEL WILL NOT PROVIDE ANY SUPPORT,  ASSISTANCE, 
 * INSTALLATION, TRAINING OR OTHER SERVICES.  INTEL WILL NOT PROVIDE ANY 
 * UPDATES, ENHANCEMENTS OR EXTENSIONS.  INTEL SPECIFICALLY DISCLAIMS ANY 
 * IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGEMENT AND FITNESS FOR A 
 * PARTICULAR PURPOSE. 
 *
 * 4.2. IN NO EVENT SHALL INTEL HAVE ANY LIABILITY TO LICENSEE, ITS LICENSEES 
 * OR ANY OTHER THIRD PARTY, FOR ANY LOST PROFITS, LOST DATA, LOSS OF USE OR 
 * COSTS OF PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, OR FOR ANY INDIRECT, 
 * SPECIAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THIS AGREEMENT, UNDER ANY 
 * CAUSE OF ACTION OR THEORY OF LIABILITY, AND IRRESPECTIVE OF WHETHER INTEL 
 * HAS ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES.  THESE LIMITATIONS 
 * SHALL APPLY NOTWITHSTANDING THE FAILURE OF THE ESSENTIAL PURPOSE OF ANY 
 * LIMITED REMEDY.
 *
 * 4.3. Licensee shall not export, either directly or indirectly, any of this 
 * software or system incorporating such software without first obtaining any 
 * required license or other approval from the U. S. Department of Commerce or 
 * any other agency or department of the United States Government.  In the 
 * event Licensee exports any such software from the United States or re-
 * exports any such software from a foreign destination, Licensee shall ensure
 * that the distribution and export/re-export of the software is in compliance 
 * with all laws, regulations, orders, or other restrictions of the U.S. Export 
 * Administration Regulations. Licensee agrees that neither it nor any of its 
 * subsidiaries will export/re-export any technical data, process, software, or 
 * service, directly or indirectly, to any country for which the United States 
 * government or any agency thereof requires an export license, other 
 * governmental approval, or letter of assurance, without first obtaining such
 * license, approval or letter.
 *
 *****************************************************************************/


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

#define ACPI_OK                     0x00000001
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
#define TRACE_ALLOCATIONS           0x00200000
#define TRACE_INTERRUPTS            0x00800000
#define TRACE_ALL                   0x002FFF00

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
 * Reporting macros that are never compiled out
 */

/* Error reporting.  These versions add callers module and line# */

#define REPORT_INFO(a)                  _ReportInfo(_THIS_MODULE,__LINE__,_COMPONENT,a)
#define REPORT_ERROR(a)                 _ReportError(_THIS_MODULE,__LINE__,_COMPONENT,a)
#define REPORT_WARNING(a)               _ReportWarning(_THIS_MODULE,__LINE__,_COMPONENT,a)
#define REPORT_SUCCESS(a)               _ReportSuccess(_THIS_MODULE,__LINE__,_COMPONENT,a)

/* Error reporting.  These versions pass thru the module and line# */

#define _REPORT_INFO(a,b,c,d)           _ReportInfo(a,b,c,d)
#define _REPORT_ERROR(a,b,c,d)          _ReportError(a,b,c,d)
#define _REPORT_WARNING(a,b,c,d)        _ReportWarning(a,b,c,d)


/* Buffer dump macros */

#define DUMP_BUFFER(a,b,c)              DumpBuffer((char *)a,b,c,_COMPONENT)


/*
 * Debug macros that are conditionally compiled
 */

#ifdef _DEBUG

/* Conditional execution */

#define DEBUG_EXEC(a)                   a;

/* Function entry tracing */

#define FUNCTION_TRACE(a)               char * ThisProc = a;\
                                        FunctionTrace(_THIS_MODULE,__LINE__,_COMPONENT,a);
#define FUNCTION_EXIT                   FunctionExit(_THIS_MODULE,__LINE__,_COMPONENT,ThisProc);

/* Stack and buffer dumping */

#define DUMP_STACK_ENTRY(a)             AmlDumpStackEntry(a)
#define DUMP_STACK(a,b,c,d)             AmlDumpStack(a,b,c,d)
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
#define TEST_DEBUG_SWITCH(lvl)          if (((lvl) & DebugLevel) && (_COMPONENT & DebugLayer))

#define DEBUG_PRINT(lvl,fp)             TEST_DEBUG_SWITCH(lvl) {\
                                            DebugPrintPrefix (_THIS_MODULE,__LINE__,_COMPONENT);\
                                            DebugPrintRaw PARAM_LIST(fp);}

#define DEBUG_PRINT_RAW(lvl,fp)         TEST_DEBUG_SWITCH(lvl) {\
                                            DebugPrintRaw PARAM_LIST(fp);}




#else
/* 
 * This is the non-debug case -- make everything go away,
 * leaving no executable debug code!
 */

#define DEBUG_EXEC(a)                       
#define FUNCTION_TRACE(a)
#define FUNCTION_EXIT
#define DUMP_STACK_ENTRY(a)
#define DUMP_STACK(a,b,c,d)
#define DUMP_ENTRY(a)
#define DUMP_TABLES(a,b)

#define DEBUG_PRINT(l,f)
#define DEBUG_PRINT_RAW(l,f) 

#endif




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
FunctionExit (
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



/* TBD: simplify or remove entirely */

void 
_Kinc_error (char *, INT32, INT32, char *, INT32, INT32); 
void 
_Kinc_info (char *, INT32, INT32, char *, INT32, INT32); 
void 
_Kinc_warning (char *, INT32, INT32, char *, INT32, INT32);


/*
 * Memory allocation functions and related macros.
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






/********************************************************************************************
 *
 * Obsolete??
 */

/*  Bitflags for all display functions  */

#define DISPLAY_DATA        SCREEN          /*  SCREEN defined in BU.H (1)  */
#define LOG_DATA            LOGFILE         /*  LOGFILE defined in BU.H (2) */
#define OUTPUT_DATA         (DISPLAY_DATA | LOG_DATA)

/*  
 * start using bits from the other end to minimize the possibility
 * of additional flag bits from BU being defined that will conflict
 */
#define OUTPUT_ERRORS       0x80

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



#endif /* _OUTPUT_H */
