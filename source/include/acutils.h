
/******************************************************************************
 *
 * Name: accommon.h -- prototypes for the common (subsystem-wide) procedures
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

#ifndef _ACCOMMON_H
#define _ACCOMMON_H


#define REF_INCREMENT       (UINT16) 0
#define REF_DECREMENT       (UINT16) 1
#define REF_FORCE_DELETE    (UINT16) 2

/* AcpiCmDumpBuffer */

#define DB_BYTE_DISPLAY     1
#define DB_WORD_DISPLAY     2
#define DB_DWORD_DISPLAY    4
#define DB_QWORD_DISPLAY    8


/* Global initialization interfaces */

void
AcpiCmInitGlobals (
    ACPI_INIT_DATA *InitData);

void
AcpiCmTerminate (
    void);


/*
 * AcpiCmInit - miscellaneous initialization and shutdown
 */

ACPI_STATUS
AcpiCmHardwareInitialize (
    void);

ACPI_STATUS
AcpiCmSubsystemShutdown (
    void);

/*
 * AcpiCmGlobal - Global data structures and procedures
 */

INT8 *
AcpiCmGetMutexName (
    UINT32                  MutexId);

INT8 *
AcpiCmGetTypeName (
    UINT32                  Type);

BOOLEAN
AcpiCmValidObjectType (
    UINT32                  Type);

ACPI_OWNER_ID
AcpiCmAllocateOwnerId (
    UINT32                  IdType);


/*
 * AcpiCmClib - Local implementations of C library functions
 */

NATIVE_UINT
AcpiCmStrlen (
    const INT8              *String);

INT8 *
AcpiCmStrcpy (
    INT8                    *DstString,
    const INT8              *SrcString);

INT8 *
AcpiCmStrncpy (
    INT8                    *DstString,
    const INT8              *SrcString,
    NATIVE_UINT             Count);

UINT32
AcpiCmStrncmp (
    const INT8              *String1,
    const INT8              *String2,
    NATIVE_UINT             Count);

UINT32
AcpiCmStrcmp (
    const INT8              *String1,
    const INT8              *String2);

INT8 *
AcpiCmStrcat (
    INT8                    *DstString,
    const INT8              *SrcString);

INT8 *
AcpiCmStrncat (
    INT8                    *DstString,
    const INT8              *SrcString,
    NATIVE_UINT             Count);

UINT32
AcpiCmStrtoul (
    const INT8              *String,
    INT8                    **Terminator,
    INT32                   Base);

INT8 *
AcpiCmStrstr (
    INT8                    *String1,
    INT8                    *String2);

INT8 *
AcpiCmStrupr (
    INT8                    *SrcString);

void *
AcpiCmMemcpy (
    void                    *Dest,
    const void              *Src,
    NATIVE_UINT             Count);

void *
AcpiCmMemset (
    void                    *Dest,
    INT32                   Value,
    NATIVE_UINT             Count);

INT32
AcpiCmToUpper (
    INT32                   c);

INT32
AcpiCmToLower (
    INT32                   c);


/*
 * AcpiCmCopy - Object construction and conversion interfaces
 */

ACPI_STATUS
AcpiCmBuildSimpleObject(
    ACPI_OBJECT_INTERNAL    *Obj,
    ACPI_OBJECT             *UserObj,
    INT8                    *DataSpace,
    UINT32                  *BufferSpaceUsed);

ACPI_STATUS
AcpiCmBuildPackageObject (
    ACPI_OBJECT_INTERNAL    *Obj,
    INT8                    *Buffer,
    UINT32                  *SpaceUsed);

ACPI_STATUS
AcpiCmBuildExternalObject (
    ACPI_OBJECT_INTERNAL    *Obj,
    ACPI_BUFFER             *RetBuffer);

ACPI_STATUS
AcpiCmBuildInternalSimpleObject(
    ACPI_OBJECT             *UserObj,
    ACPI_OBJECT_INTERNAL    *Obj);

ACPI_STATUS
AcpiCmBuildInternalObject (
    ACPI_OBJECT             *Obj,
    ACPI_OBJECT_INTERNAL    *InternalObj);

ACPI_STATUS
AcpiCmCopyInternalSimpleObject (
    ACPI_OBJECT_INTERNAL    *SourceObj,
    ACPI_OBJECT_INTERNAL    *DestObj);

ACPI_STATUS
AcpiCmBuildCopyInternalPackageObject (
    ACPI_OBJECT_INTERNAL    *SourceObj,
    ACPI_OBJECT_INTERNAL    *DestObj);


/*
 * AcpiCmCreate - Object creation
 */

ACPI_STATUS
AcpiCmUpdateObjectReference (
    ACPI_OBJECT_INTERNAL    *Object,
    UINT16                  Action);

ACPI_OBJECT_INTERNAL *
_CmCreateInternalObject (
    INT8                    *ModuleName,
    INT32                   LineNumber,
    INT32                   ComponentId,
    OBJECT_TYPE_INTERNAL    Type);


/*
 * AcpiCmDebug - Debug interfaces
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
    INT8                    *String);

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
    NATIVE_UINT             Value);

void
FunctionPtrExit (
    ACPI_STRING             ModuleName,
    INT32                   LineNumber,
    INT32                   ComponentId,
    ACPI_STRING             FunctionName,
    INT8                    *Ptr);

void
DebugPrintPrefix (
    ACPI_STRING             ModuleName,
    INT32                   LineNumber);

void
DebugPrint (
    ACPI_STRING             ModuleName,
    INT32                   LineNumber,
    INT32                   ComponentId,
    INT32                   PrintLevel,
    INT8                    *Format, ...);

void
DebugPrintRaw (
    INT8                    *Format, ...);

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
AcpiCmDumpBuffer (
    INT8                    *Buffer,
    UINT32                  Count,
    UINT32                  Display,
    INT32                   componentId);


/*
 * AcpiCmDelete - Object deletion
 */

void
AcpiCmDeleteInternalObj (
    ACPI_OBJECT_INTERNAL    *Object);

void
AcpiCmDeleteInternalPackageObject (
    ACPI_OBJECT_INTERNAL    *Object);

void
AcpiCmDeleteInternalSimpleObject (
    ACPI_OBJECT_INTERNAL    *Object);

ACPI_STATUS
AcpiCmDeleteInternalObjectList (
    ACPI_OBJECT_INTERNAL    **ObjList);


/*
 * AcpiCmEval - object evaluation
 */

/* Method name strings */

#define METHOD_NAME__HID        "_HID"
#define METHOD_NAME__UID        "_UID"
#define METHOD_NAME__ADR        "_ADR"
#define METHOD_NAME__STA        "_STA"
#define METHOD_NAME__REG        "_REG"
#define METHOD_NAME__SEG        "_SEG"
#define METHOD_NAME__BBN        "_BBN"


ACPI_STATUS
AcpiCmEvaluateNumericObject (
    INT8                    *MethodName,
    ACPI_NAMED_OBJECT       *AcpiDevice,
    UINT32                  *Address);

ACPI_STATUS
AcpiCmExecute_HID (
    ACPI_NAMED_OBJECT       *AcpiDevice,
    DEVICE_ID               *Hid);

ACPI_STATUS
AcpiCmExecute_STA (
    ACPI_NAMED_OBJECT       *AcpiDevice,
    UINT32                  *StatusFlags);

ACPI_STATUS
AcpiCmExecute_UID (
    ACPI_NAMED_OBJECT       *AcpiDevice,
    DEVICE_ID               *Uid);


/*
 * AcpiCmError - exception interfaces
 */

INT8 *
AcpiCmFormatException (
    ACPI_STATUS             Status);


/*
 * AcpiCmMutex - mutual exclusion interfaces
 */

ACPI_STATUS
AcpiCmMutexInitialize (
    void);

void
AcpiCmMutexTerminate (
    void);

ACPI_STATUS
AcpiCmCreateMutex (
    ACPI_MUTEX_HANDLE       MutexId);

ACPI_STATUS
AcpiCmDeleteMutex (
    ACPI_MUTEX_HANDLE       MutexId);

ACPI_STATUS
AcpiCmAcquireMutex (
    ACPI_MUTEX_HANDLE       MutexId);

ACPI_STATUS
AcpiCmReleaseMutex (
    ACPI_MUTEX_HANDLE       MutexId);


/*
 * AcpiCmObject - internal object create/delete/cache routines
 */

#define AcpiCmCreateInternalObject(t)   _CmCreateInternalObject(_THIS_MODULE,__LINE__,_COMPONENT,t)
#define AcpiCmAllocateObjectDesc()      _CmAllocateObjectDesc(_THIS_MODULE,__LINE__,_COMPONENT)

void *
_CmAllocateObjectDesc (
    INT8                    *ModuleName,
    INT32                   LineNumber,
    INT32                   ComponentId);

void
AcpiCmDeleteObjectDesc (
    ACPI_OBJECT_INTERNAL    *Object);

BOOLEAN
AcpiCmValidInternalObject (
    void                    *Object);


/*
 * AcpiCmRefCnt - Object reference count management
 */

void
AcpiCmAddReference (
    ACPI_OBJECT_INTERNAL    *Object);

void
AcpiCmRemoveReference (
    ACPI_OBJECT_INTERNAL    *Object);

/*
 * AcpiCmSize - Object size routines
 */

ACPI_STATUS
AcpiCmGetSimpleObjectSize (
    ACPI_OBJECT_INTERNAL    *Obj,
    UINT32                  *ObjLength);

ACPI_STATUS
AcpiCmGetPackageObjectSize (
    ACPI_OBJECT_INTERNAL    *Obj,
    UINT32                  *ObjLength);

ACPI_STATUS
AcpiCmGetObjectSize(
    ACPI_OBJECT_INTERNAL    *Obj,
    UINT32                  *ObjLength);


/*
 * AcpiCmState - Generic state creation/cache routines
 */

void
AcpiCmPushGenericState (
    ACPI_GENERIC_STATE      **ListHead,
    ACPI_GENERIC_STATE      *State);

ACPI_GENERIC_STATE *
AcpiCmPopGenericState (
    ACPI_GENERIC_STATE      **ListHead);


ACPI_GENERIC_STATE *
AcpiCmCreateGenericState (
    void);

ACPI_GENERIC_STATE *
AcpiCmCreateUpdateState (
    ACPI_OBJECT_INTERNAL    *Object,
    UINT16                  Action);

ACPI_STATUS
AcpiCmCreateUpdateStateAndPush (
    ACPI_OBJECT_INTERNAL    *Object,
    UINT16                  Action,
    ACPI_GENERIC_STATE      **StateList);

ACPI_GENERIC_STATE *
AcpiCmCreateControlState (
    void);

void
AcpiCmDeleteGenericState (
    ACPI_GENERIC_STATE      *State);

void
AcpiCmDeleteGenericStateCache (
    void);

void
AcpiCmDeleteObjectCache (
    void);

/*
 * AcpiCmutils
 */

BOOLEAN
AcpiCmValidAcpiName (
    UINT32                  Name);

BOOLEAN
AcpiCmValidAcpiCharacter (
    INT8                    Character);


/*
 * Memory allocation functions and related macros.
 * Macros that expand to include filename and line number
 */

void *
_CmAllocate (
    UINT32                  Size,
    UINT32                  Component,
    ACPI_STRING             Module,
    INT32                   Line);

void *
_CmCallocate (
    UINT32                  Size,
    UINT32                  Component,
    ACPI_STRING             Module,
    INT32                   Line);

void
_CmFree (
    void                    *Address,
    UINT32                  Component,
    ACPI_STRING             Module,
    INT32                   Line);

void
AcpiCmInitStaticObject (
    ACPI_OBJECT_INTERNAL    *ObjDesc);

#define AcpiCmAllocate(a)               _CmAllocate(a,_COMPONENT,_THIS_MODULE,__LINE__)
#define AcpiCmCallocate(a)              _CmCallocate(a, _COMPONENT,_THIS_MODULE,__LINE__)
#define AcpiCmFree(a)                   _CmFree(a,_COMPONENT,_THIS_MODULE,__LINE__)

#ifndef ACPI_DEBUG

#define AcpiCmAddElementToAllocList(a,b,c,d,e,f)
#define AcpiCmDeleteElementFromAllocList(a,b,c,d)
#define AcpiCmDumpCurrentAllocations(a,b)
#define AcpiCmDumpAllocationInfo()

#define DECREMENT_OBJECT_METRICS(a)
#define INCREMENT_OBJECT_METRICS(a)
#define INITIALIZE_ALLOCATION_METRICS()

#else

#define INITIALIZE_ALLOCATION_METRICS() \
    AcpiGbl_CurrentObjectCount = 0; \
    AcpiGbl_CurrentObjectSize = 0; \
    AcpiGbl_RunningObjectCount = 0; \
    AcpiGbl_RunningObjectSize = 0; \
    AcpiGbl_MaxConcurrentObjectCount = 0; \
    AcpiGbl_MaxConcurrentObjectSize = 0; \
    AcpiGbl_CurrentAllocSize = 0; \
    AcpiGbl_CurrentAllocCount = 0; \
    AcpiGbl_RunningAllocSize = 0; \
    AcpiGbl_RunningAllocCount = 0; \
    AcpiGbl_MaxConcurrentAllocSize = 0; \
    AcpiGbl_MaxConcurrentAllocCount = 0

#define DECREMENT_OBJECT_METRICS(a) \
    AcpiGbl_CurrentObjectCount--; \
    AcpiGbl_CurrentObjectSize -= a

#define INCREMENT_OBJECT_METRICS(a) \
    AcpiGbl_CurrentObjectCount++; \
    AcpiGbl_RunningObjectCount++; \
    if (AcpiGbl_MaxConcurrentObjectCount < AcpiGbl_CurrentObjectCount) \
    { \
        AcpiGbl_MaxConcurrentObjectCount = AcpiGbl_CurrentObjectCount; \
    } \
    AcpiGbl_RunningObjectSize += a; \
    AcpiGbl_CurrentObjectSize += a; \
    if (AcpiGbl_MaxConcurrentObjectSize < AcpiGbl_CurrentObjectSize) \
    { \
        AcpiGbl_MaxConcurrentObjectSize = AcpiGbl_CurrentObjectSize; \
    }


void
AcpiCmDumpAllocationInfo (
    void);

void
AcpiCmDumpCurrentAllocations (
    UINT32                  Component,
    ACPI_STRING             Module);

#endif


#endif /* _ACCOMMON_H */
