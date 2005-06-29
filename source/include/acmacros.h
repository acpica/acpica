
/******************************************************************************
 * 
 * Name: macros.h - C macros for the entire subsystem.
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
 * 2.1. This is your license from Intel Corp. under its intellectual property
 * rights.  You may have additional license terms from the party that provided
 * you this software, covering your right to use that party's intellectual
 * property rights.
 *
 * 2.2. Intel grants, free of charge, to any person ("Licensee") obtaining a
 * copy of the source code appearing in this file ("Covered Code") an
 * irrevocable, perpetual, worldwide license under Intel's copyrights in the
 * base code distributed originally by Intel ("Original Intel Code") to copy,
 * make derivatives, distribute, use and display any portion of the Covered
 * Code in any form, with the right to sublicense such rights; and
 *
 * 2.3. Intel grants Licensee a non-exclusive and non-transferable patent
 * license (with the right to sublicense), under only those claims of Intel
 * patents that are infringed by the Original Intel Code, to make, use, sell,
 * offer to sell, and import the Covered Code and derivative works thereof
 * solely to the minimum extent necessary to exercise the above copyright
 * license, and in no event shall the patent license extend to any additions
 * to or modifications of the Original Intel Code.  No other license or right
 * is granted directly or by implication, estoppel or otherwise;
 *
 * The above copyright and patent license is granted only if the following
 * conditions are met:
 *
 * 3. Conditions 
 *
 * 3.1. Redistribution of Source with Rights to Further Distribute Source.  
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification with rights to further distribute source must include
 * the above Copyright Notice, the above License, this list of Conditions,
 * and the following Disclaimer and Export Compliance provision.  In addition,
 * Licensee must cause all Covered Code to which Licensee contributes to
 * contain a file documenting the changes Licensee made to create that Covered
 * Code and the date of any change.  Licensee must include in that file the
 * documentation of any changes made by any predecessor Licensee.  Licensee 
 * must include a prominent statement that the modification is derived,
 * directly or indirectly, from Original Intel Code.
 *
 * 3.2. Redistribution of Source with no Rights to Further Distribute Source.  
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification without rights to further distribute source must
 * include the following Disclaimer and Export Compliance provision in the
 * documentation and/or other materials provided with distribution.  In
 * addition, Licensee may not authorize further sublicense of source of any
 * portion of the Covered Code, and must include terms to the effect that the
 * license from Licensee to its licensee is limited to the intellectual
 * property embodied in the software Licensee provides to its licensee, and
 * not to intellectual property embodied in modifications its licensee may
 * make.
 *
 * 3.3. Redistribution of Executable. Redistribution in executable form of any
 * substantial portion of the Covered Code or modification must reproduce the
 * above Copyright Notice, and the following Disclaimer and Export Compliance
 * provision in the documentation and/or other materials provided with the
 * distribution.
 *
 * 3.4. Intel retains all right, title, and interest in and to the Original
 * Intel Code.
 *
 * 3.5. Neither the name Intel nor any other trademark owned or controlled by
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
 * event Licensee exports any such software from the United States or
 * re-exports any such software from a foreign destination, Licensee shall
 * ensure that the distribution and export/re-export of the software is in
 * compliance with all laws, regulations, orders, or other restrictions of the
 * U.S. Export Administration Regulations. Licensee agrees that neither it nor
 * any of its subsidiaries will export/re-export any technical data, process,
 * software, or service, directly or indirectly, to any country for which the
 * United States government or any agency thereof requires an export license,
 * other governmental approval, or letter of assurance, without first obtaining
 * such license, approval or letter.
 *
 *****************************************************************************/

#ifndef __MACROS_H__
#define __MACROS_H__

/* 
 * Data manipulation macros 
 */

#ifndef LOWORD
#define LOWORD(l)                       ((UINT16)(NATIVE_UINT)(l))
#endif

#ifndef HIWORD
#define HIWORD(l)                       ((UINT16)((((NATIVE_UINT)(l)) >> 16) & 0xFFFF))
#endif  

#ifndef LOBYTE
#define LOBYTE(l)                       ((UINT8)(UINT16)(l))
#endif

#ifndef HIBYTE
#define HIBYTE(l)                       ((UINT8)((((UINT16)(l)) >> 8) & 0xFF))
#endif

#define BIT0(x)                         ((((x) & 0x01) > 0) ? 1 : 0)
#define BIT1(x)                         ((((x) & 0x02) > 0) ? 1 : 0)
#define BIT2(x)                         ((((x) & 0x04) > 0) ? 1 : 0)

#define BIT3(x)                         ((((x) & 0x08) > 0) ? 1 : 0)
#define BIT4(x)                         ((((x) & 0x10) > 0) ? 1 : 0)
#define BIT5(x)                         ((((x) & 0x20) > 0) ? 1 : 0)
#define BIT6(x)                         ((((x) & 0x40) > 0) ? 1 : 0)
#define BIT7(x)                         ((((x) & 0x80) > 0) ? 1 : 0)

#define LOW_BASE(w)                     ((UINT16) ((w) & 0x0000FFFF))
#define MID_BASE(b)                     ((UINT8) (((b) & 0x00FF0000) >> 16))
#define HI_BASE(b)                      ((UINT8) (((b) & 0xFF000000) >> 24))
#define LOW_LIMIT(w)                    ((UINT16) ((w) & 0x0000FFFF))
#define HI_LIMIT(b)                     ((UINT8) (((b) & 0x00FF0000) >> 16))


/*
 * Fast power-of-two math macros for non-optimized compilers
 */

#define DIV_2(a)                        ((a)>>1)
#define MUL_2(a)                        ((a)<<1)
#define MOD_2(a)                        ((a)&0x01)

#define DIV_4(a)                        ((a)>>2)
#define MUL_4(a)                        ((a)<<2)
#define MOD_4(a)                        ((a)&0x03)

#define DIV_8(a)                        ((a)>>3)
#define MUL_8(a)                        ((a)<<3)
#define MOD_8(a)                        ((a)&0x07)

#define DIV_16(a)                       ((a)>>4)
#define MUL_16(a)                       ((a)<<4)
#define MOD_16(a)                       ((a)&0x0F)



#ifdef IA64
#define ALIGN64(bc)                     char Align[bc];
#else
#define ALIGN64(bc)
#endif

/* Assert macros */

#ifdef DEBUG_ASSERT
#undef DEBUG_ASSERT
#endif

#define ACPI_ASSERT(exp)                if(!(exp)) \
                                            OsdDbgAssert(#exp, __FILE__, __LINE__, "Failed Assertion")

#define DEBUG_ASSERT(msg, exp)          if(!(exp)) \
                                            OsdDbgAssert(#exp, __FILE__, __LINE__, msg)


/* Register read/write Macros */

#define READ_ACPI_REGISTER(RegId)       HwRegisterIO (ACPI_READ, (INT32)(RegId))
#define WRITE_ACPI_REGISTER(RegId,Val)  HwRegisterIO (ACPI_WRITE, (INT32) (RegId), Val)



/* 
 * An ACPI_HANDLE (which is actually an NAME_TABLE_ENTRY *) can appear in some contexts,
 * such as on apObjStack, where a pointer to an ACPI_OBJECT_INTERNAL can also
 * appear.  This macro is used to distinguish them.
 *
 * The DataType field is the first field in both structures.
 */

#define VALID_DESCRIPTOR_TYPE(d,t)      (((NAME_TABLE_ENTRY *)d)->DataType == t)


/* Macro to test the object type */

#define VALID_OBJECT_TYPE(d,t)          (((ACPI_OBJECT_INTERNAL *)d)->Common.Type == (UINT8)t)



/* 
 * There is an (nte *) prefix to each name table, containing either a NULL 
 * pointer or the address of the next array of nte's in the scope.
 *
 * This macro extracts a pointer to the NEXT table in the chain.
 */
#define NEXTSEG(NameTbl)                ((NAME_TABLE_ENTRY **)NameTbl)[-1]



/* 
 * Macro to check if a pointer is within an ACPI table.
 * Parameter (a) is the pointer to check.  Parameter (b) must be defined 
 * as a pointer to an ACPI_TABLE_HEADER.  (b+1) then points past the header,
 * and ((UINT8 *)b+b->Length) points one byte past the end of the table.
 */

#define IS_IN_ACPI_TABLE(a,b)           (((UINT8 *)(a) >= (UINT8 *)(b + 1)) &&\
                                        ((UINT8 *)(a) < ((UINT8 *)b + b->Length)))


/*
 * Reporting macros that are never compiled out
 */

/*
 * Error reporting.  These versions add callers module and line#.  Since
 * _THIS_MODULE gets compiled out when ACPI_DEBUG isn't defined, only
 * use it in debug mode.
 */

#ifdef ACPI_DEBUG

#define REPORT_INFO(a)                  _ReportInfo(_THIS_MODULE,__LINE__,_COMPONENT,a)
#define REPORT_ERROR(a)                 _ReportError(_THIS_MODULE,__LINE__,_COMPONENT,a)
#define REPORT_WARNING(a)               _ReportWarning(_THIS_MODULE,__LINE__,_COMPONENT,a)
#define REPORT_SUCCESS(a)               _ReportSuccess(_THIS_MODULE,__LINE__,_COMPONENT,a)

#else

#define REPORT_INFO(a)                  _ReportInfo("",__LINE__,_COMPONENT,a)
#define REPORT_ERROR(a)                 _ReportError("",__LINE__,_COMPONENT,a)
#define REPORT_WARNING(a)               _ReportWarning("",__LINE__,_COMPONENT,a)
#define REPORT_SUCCESS(a)               _ReportSuccess("",__LINE__,_COMPONENT,a)

#endif

/* Error reporting.  These versions pass thru the module and line# */

#define _REPORT_INFO(a,b,c,d)           _ReportInfo(a,b,c,d)
#define _REPORT_ERROR(a,b,c,d)          _ReportError(a,b,c,d)
#define _REPORT_WARNING(a,b,c,d)        _ReportWarning(a,b,c,d)

/* Buffer dump macros */

#define DUMP_BUFFER(a,b,c)              DumpBuffer((char *)a,b,c,_COMPONENT)

/*
 * Debug macros that are conditionally compiled
 */

#ifdef ACPI_DEBUG

#define MODULE_NAME(name)               static char *_THIS_MODULE = name

/* 
 * Function entry tracing. 
 * The first parameter should be the procedure name as a quoted string.  This is declared
 * as a local string ("_ProcName) so that it can be also used by the function exit macros below.
 */

#define FUNCTION_TRACE(a)               char * _ProcName = a;\
                                        FunctionTrace(_THIS_MODULE,__LINE__,_COMPONENT,a)
#define FUNCTION_TRACE_PTR(a,b)         char * _ProcName = a;\
                                        FunctionTracePtr(_THIS_MODULE,__LINE__,_COMPONENT,a,(void *)b)
#define FUNCTION_TRACE_U32(a,b)         char * _ProcName = a;\
                                        FunctionTraceU32(_THIS_MODULE,__LINE__,_COMPONENT,a,(UINT32)b)
#define FUNCTION_TRACE_STR(a,b)         char * _ProcName = a;\
                                        FunctionTraceStr(_THIS_MODULE,__LINE__,_COMPONENT,a,(char *)b)
/* 
 * Function exit tracing. 
 * WARNING: These macros include a return statement.  This is usually considered 
 * bad form, but having a separate exit macro is very ugly and difficult to maintain.
 * One of the FUNCTION_TRACE macros above must be used in conjunction with these macros
 * so that "_ProcName" is defined.
 */
#define return_VOID                     {FunctionExit(_THIS_MODULE,__LINE__,_COMPONENT,_ProcName);return;}
#define return_ACPI_STATUS(s)           {FunctionStatusExit(_THIS_MODULE,__LINE__,_COMPONENT,_ProcName,s);return(s);}
#define return_VALUE(s)                 {FunctionValueExit(_THIS_MODULE,__LINE__,_COMPONENT,_ProcName,(UINT32)s);return(s);}


/* Conditional execution */

#define DEBUG_EXEC(a)                   a;
#define DEBUG_DEFINE(a)                 a;


/* Stack and buffer dumping */

#define DUMP_STACK_ENTRY(a)             AmlDumpObjStackEntry(a)
#define DUMP_STACK(a,b,c,d)             AmlDumpObjStack(a,b,c,d)
#define DUMP_ENTRY(a,b)                 NsDumpEntry (a,b)
#define DUMP_TABLES(a,b)                NsDumpTables(a,b)

//MsgAcpiErrorBreak
#define ERROR_BREAK
#ifdef  ERROR_BREAK
#define BREAK_ON_ERROR(lvl)             if ((lvl)&ACPI_ERROR) {\
                                            DebugPrintRaw (MsgAcpiErrorBreak);\
                                            BREAKPOINT3;}
#else
#define BREAK_ON_ERROR(lvl) 
#endif

/* 
 * Master debug print macros 
 * Print iff:
 *    1) Debug print for the current component is enabled
 *    2) Debug error level or trace level for the print statement is enabled
 *
 */

#define PARAM_LIST(pl)                  pl

#define TEST_DEBUG_SWITCH(lvl)          if (((lvl) & DebugLevel) && (_COMPONENT & DebugLayer))

#define DEBUG_PRINT(lvl,fp)             TEST_DEBUG_SWITCH(lvl) {\
                                            DebugPrintPrefix (_THIS_MODULE,__LINE__,_COMPONENT);\
                                            DebugPrintRaw PARAM_LIST(fp);\
                                            BREAK_ON_ERROR(lvl);}

#define DEBUG_PRINT_RAW(lvl,fp)         TEST_DEBUG_SWITCH(lvl) {\
                                            DebugPrintRaw PARAM_LIST(fp);}



#else
/* 
 * This is the non-debug case -- make everything go away,
 * leaving no executable debug code!
 */

#define MODULE_NAME(name)
#define _THIS_MODULE ""

#define DEBUG_EXEC(a)  
#define DEBUG_DEFINE(a)                     
#define FUNCTION_TRACE(a)
#define FUNCTION_TRACE_PTR(a,b)
#define FUNCTION_TRACE_U32(a,b)
#define FUNCTION_TRACE_STR(a,b)
#define FUNCTION_EXIT
#define FUNCTION_STATUS_EXIT(s)
#define FUNCTION_VALUE_EXIT(s)
#define DUMP_STACK_ENTRY(a)
#define DUMP_STACK(a,b,c,d)
#define DUMP_ENTRY(a,b)
#define DUMP_TABLES(a,b)
#define DEBUG_PRINT(l,f)
#define DEBUG_PRINT_RAW(l,f) 

#define return_VOID                     return
#define return_ACPI_STATUS(s)           return(s)
#define return_VALUE(s)                 return(s)


#endif




#ifndef ACPI_DEBUG

#define ADD_OBJECT_NAME(a,b)

#else


/*
 * 1) Set name to blanks
 * 2) Copy the object name
 */

#define ADD_OBJECT_NAME(a,b)            MEMSET (a->Common.Name, ' ', sizeof (a->Common.Name));\
	                                    STRNCPY (a->Common.Name, Gbl_NsTypeNames[b], sizeof (a->Common.Name))
	
#endif



#endif /* MACROS_H */
