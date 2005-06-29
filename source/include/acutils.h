
/******************************************************************************
 * 
 * Name: common.h -- prototypes for the common (subsystem-wide) procedures
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

#ifndef _COMMON_H
#define _COMMON_H

#include "acpiobj.h"
#include "acpiosd.h"


#define REF_INCREMENT       1
#define REF_DECREMENT       -1
#define REF_FORCE_DELETE    0x80000000


/* Global initialization interfaces */

void 
CmInitGlobals (
    void);

void
CmTerminate (
    void);


/*
 * CmInit - miscellaneous initialization
 */

ACPI_STATUS
CmHardwareInitialize (
    void);


/* Object construction and conversion interfaces - cmobject */

ACPI_OBJECT_INTERNAL *
_CmCreateInternalObject (
    char                    *ModuleName, 
    INT32                   LineNumber, 
    INT32                   ComponentId,
    ACPI_OBJECT_TYPE        Type);

ACPI_STATUS
CmBuildSimpleObject(
    ACPI_OBJECT_INTERNAL    *Obj,
    ACPI_OBJECT             *UserObj,
    char                    *DataSpace,
    UINT32                  *BufferSpaceUsed);

ACPI_STATUS
CmBuildPackageObject (
    ACPI_OBJECT_INTERNAL    *Obj, 
    char                    *Buffer, 
    UINT32                  *SpaceUsed);

ACPI_STATUS
CmBuildExternalObject (
    ACPI_OBJECT_INTERNAL    *Obj, 
    ACPI_BUFFER             *RetBuffer);

ACPI_STATUS
CmBuildInternalSimpleObject(
    ACPI_OBJECT             *UserObj,
    ACPI_OBJECT_INTERNAL    *Obj);

ACPI_STATUS
CmBuildInternalObject (
    ACPI_OBJECT             *Obj, 
    ACPI_OBJECT_INTERNAL    *InternalObj);


/*
 * CmSize - Object size routines
 */

ACPI_STATUS
CmGetSimpleObjectSize (
    ACPI_OBJECT_INTERNAL    *Obj, 
    UINT32                  *ObjLength);

ACPI_STATUS
CmGetPackageObjectSize (
    ACPI_OBJECT_INTERNAL    *Obj, 
    UINT32                  *ObjLength);

ACPI_STATUS
CmGetObjectSize(
    ACPI_OBJECT_INTERNAL    *Obj, 
    UINT32                  *ObjLength);


/*
 * CmDelete - Object deletion and copy 
 */

ACPI_STATUS
CmUpdateObjectReference (
    ACPI_OBJECT_INTERNAL    *Object,
    INT32                   Action);

ACPI_STATUS
CmCopyInternalObject (
    ACPI_OBJECT_INTERNAL    *SrcDesc, 
    ACPI_OBJECT_INTERNAL    *DestDesc);


/* Object deletion - cmdelete */

void
CmDeleteInternalPackageObject (
    ACPI_OBJECT_INTERNAL    *Object);

void
CmDeleteInternalSimpleObject (
    ACPI_OBJECT_INTERNAL    *Object);

void
CmDeleteInternalObject (
    ACPI_OBJECT_INTERNAL    *Object);

ACPI_STATUS
CmDeleteInternalObjectList (
    ACPI_OBJECT_INTERNAL    **ObjList);

void
CmDeleteInternalObjDispatch (
    ACPI_OBJECT_INTERNAL    *Object);


/*
 * CmMutex - mutual exclusion interfaces
 */

ACPI_STATUS
CmMutexInitialize (
    void);

void
CmMutexTerminate (
    void);

ACPI_STATUS
CmCreateMutex (
    ACPI_MUTEX_HANDLE       MutexId);

ACPI_STATUS
CmDeleteMutex (
    ACPI_MUTEX_HANDLE       MutexId);

ACPI_STATUS
CmAcquireMutex (
    ACPI_MUTEX_HANDLE       MutexId);

ACPI_STATUS
CmReleaseMutex (
    ACPI_MUTEX_HANDLE       MutexId);



/* 
 * CmDebug - Debug interfaces 
 */

INT32
GetDebugLevel (
    void);

void
SetDebugLevel (
    INT32                   level);

void
FunctionTrace (
    ACPI_STRING             ModuleName, 
    INT32                   LineNumber, 
    INT32                   ComponentId, 
    ACPI_STRING             FunctionName);

void
FunctionTracePtr (
    ACPI_STRING             ModuleName, 
    INT32                   LineNumber, 
    INT32                   ComponentId, 
    ACPI_STRING             FunctionName,
    void                    *Pointer);

void
FunctionTraceU32 (
    ACPI_STRING             ModuleName, 
    INT32                   LineNumber, 
    INT32                   ComponentId, 
    ACPI_STRING             FunctionName,
    UINT32                  Integer);

void
FunctionTraceStr (
    ACPI_STRING             ModuleName, 
    INT32                   LineNumber, 
    INT32                   ComponentId, 
    ACPI_STRING             FunctionName,
    char                    *String);

void
FunctionExit (
    ACPI_STRING             ModuleName, 
    INT32                   LineNumber, 
    INT32                   ComponentId, 
    ACPI_STRING             FunctionName);

void
FunctionStatusExit (
    ACPI_STRING             ModuleName, 
    INT32                   LineNumber, 
    INT32                   ComponentId, 
    ACPI_STRING             FunctionName,
    ACPI_STATUS             Status);

void
FunctionValueExit (
    ACPI_STRING             ModuleName, 
    INT32                   LineNumber, 
    INT32                   ComponentId, 
    ACPI_STRING             FunctionName,
    UINT32                  Value);

void
DebugPrintPrefix (
    ACPI_STRING             ModuleName, 
    INT32                   LineNumber, 
    INT32                   ComponentId);


void
DebugPrint (
    ACPI_STRING             ModuleName, 
    INT32                   LineNumber, 
    INT32                   ComponentId, 
    INT32                   PrintLevel, 
    char                    *Format, ...);

void
DebugPrintRaw (
    char                    *Format, ...);

void
_ReportInfo (
    ACPI_STRING             ModuleName, 
    INT32                   LineNumber, 
    INT32                   ComponentId, 
    ACPI_STRING             Message);

void
_ReportError (
    ACPI_STRING             ModuleName, 
    INT32                   LineNumber, 
    INT32                   ComponentId, 
    ACPI_STRING             Message);

void
_ReportWarning (
    ACPI_STRING             ModuleName, 
    INT32                   LineNumber, 
    INT32                   ComponentId, 
    ACPI_STRING             Message);

void
_ReportSuccess (
    ACPI_STRING             ModuleName, 
    INT32                   LineNumber, 
    INT32                   ComponentId, 
    ACPI_STRING             Message);

void 
DumpBuffer (
    char                    *Buffer, 
    UINT32                  Count, 
    INT32                   Flags, 
    INT32                   componentId);



/*
 * Local implementations of C library functions
 */

ACPI_SIZE
_strlen (
    const char              *String);

char *
_strcpy (
    char                    *DstString, 
    const char              *SrcString);

char *
_strncpy (
    char                    *DstString, 
    const char              *SrcString, 
    ACPI_SIZE               Count);

UINT32
_strncmp (
    const char              *String1, 
    const char              *String2, 
    ACPI_SIZE               Count);

UINT32
_strcmp (
    const char              *String1, 
    const char              *String2);

char *
_strcat (
    char                    *DstString,
    const char              *SrcString);

char *
_strncat (
    char                    *DstString, 
    const char              *SrcString, 
    ACPI_SIZE               Count);

UINT32
_strtoul (
    const char              *String, 
    char                    **Terminator, 
    INT32                   Base);

void *
_memcpy (
    void                    *Dest, 
    const void              *Src, 
    ACPI_SIZE               Count);

void *
_memset (
    void                    *Dest,
    INT32                   Value,
    ACPI_SIZE               Count);




/*
 * Memory allocation functions and related macros.
 * Macros that expand to include filename and line number
 */

void *
_CmAllocate (
	UINT32					Size,
	UINT32                  Component,
	ACPI_STRING				Module,
	INT32                   Line);

void *
_CmCallocate (
	UINT32					Size,
	UINT32                  Component,
	ACPI_STRING             Module,
	INT32                   Line);

void
_CmFree (
	void					*Address,
	UINT32                  Component,
	ACPI_STRING             Module,
	INT32                   Line);

void
CmInitStaticObject (
    ACPI_OBJECT_INTERNAL    *ObjDesc);

#define CmAllocate(a)		        _CmAllocate(a,_COMPONENT,_THIS_MODULE,__LINE__)
#define CmCallocate(a)		        _CmCallocate(a, _COMPONENT,_THIS_MODULE,__LINE__)
#define CmFree(a)			        _CmFree(a,_COMPONENT,_THIS_MODULE,__LINE__)

#ifndef ACPI_DEBUG

#define CmAddElementToAllocList(a,b,c,d,e,f)
#define CmDeleteElementFromAllocList(a,b,c,d)
#define CmDumpCurrentAllocations(a,b)
#define CmDumpAllocationInfo()

#else

void
CmDumpAllocationInfo (
	void);
	
void
CmDumpCurrentAllocations (
	UINT32					Component,
	ACPI_STRING				Module);

#endif

#define CmCreateInternalObject(t)   _CmCreateInternalObject(_THIS_MODULE,__LINE__,_COMPONENT,t)
#define CmAllocateObjectDesc()      _CmAllocateObjectDesc(_THIS_MODULE,__LINE__,_COMPONENT)

void *
_CmAllocateObjectDesc (
    char                    *ModuleName, 
    INT32                   LineNumber, 
    INT32                   ComponentId); 


#endif /* _COMMON_H */
