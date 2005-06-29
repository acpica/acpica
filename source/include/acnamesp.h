
/******************************************************************************
 * 
 * Name: namespace.h - Namespace subcomponent prototypes and defines
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

#ifndef __NAMESPACE_H__
#define __NAMESPACE_H__

#include <acpitypes.h>
#include <acpitables.h>
#include <acpiobj.h>
#include <pnp.h>


#define ACPILIB_DATA_FILE_VERSION "ADF-001"

/* 
 * There is an (nte *) prefix to each name table, containing either a NULL 
 * pointer or the address of the next array of nte's in the scope.
 *
 * This macro extracts a pointer to the NEXT table in the chain.
 */
#define NEXTSEG(NameTbl)        ((NAME_TABLE_ENTRY **)NameTbl)[-1]

/* 
 * An ACPI_HANDLE (which is actually an NAME_TABLE_ENTRY *) can appear in some contexts,
 * such as on apObjStack, where a pointer to an ACPI_OBJECT can also
 * appear.  These macros are used to distinguish them.
 *
 * The DataType field is the first field in both structures.
 */

#define IS_NS_HANDLE(h)         (((NAME_TABLE_ENTRY *)h)->DataType == DESC_TYPE_NTE) 
#define IS_ACPI_OBJECT(o)       (((NAME_TABLE_ENTRY *)o)->DataType == DESC_TYPE_ACPI_OBJ) 

/* To search the entire name space, pass this as SearchBase */

#define NS_ALL                  ((ACPI_HANDLE)0)

/* 
 * Elements of NsProperties are bit significant
 * and should be one-to-one with values of ACPI_OBJECT_TYPE
 */
#define NEWSCOPE                1   /* a definition of this type opens a name scope */
#define LOCAL                   2   /* suppress search of enclosing scopes */


/* UINT32 definitions of the predefined namespace names (Must be reversed!) */

#define NS_ROOT                 '/   '
#define NS_SYSTEM_BUS           '_BS_'

/* Char * definitions of common namespace names */

#define NS_ROOT_PATH            "/"


/* Used in NsMapAcpiTable for size parameter if table header is to be used */

#define SIZE_IN_HEADER          0


/* Flags for NsLookup, NsSearchAndEnter */

#define NS_SEARCH_PARENT        1
#define NS_NO_UPSEARCH          0


/*
 * Top-level namespace access - nsaccess
 */


ACPI_STATUS
NsSetup (
    void);

ACPI_STATUS
NsLookup (
    NAME_TABLE_ENTRY        *PrefixEntry,
    char                    *Name, 
    ACPI_OBJECT_TYPE        Type, 
    OPERATING_MODE          LoadMode,
    UINT32                  Flags,
    NAME_TABLE_ENTRY        **RetEntry);


/*
 * Table allocation/deallocation - nsalloc
 */

BOOLEAN
NsIsInSystemTable (
    void                    *Where);

NAME_TABLE_ENTRY *
NsAllocateNameTable (
    INT32                   NteEntries);

ACPI_STATUS
NsDeleteNamespace (
    void);

void
NsDetachObject (
    ACPI_HANDLE             Object);

void
NsDeleteScope (
    ACPI_HANDLE             Scope);

void
NsDeleteAcpiTables (
    void);

void
NsDeleteAcpiTable (
    ACPI_TABLE_TYPE         Type);

void
NsFreeAcpiTable (
    ACPI_TABLE_DESC         *TableInfo);

ACPI_STATUS
NsInstallAcpiTable (
    ACPI_TABLE_TYPE         TableType,
    ACPI_TABLE_DESC         *TableInfo);


/*
 * Namespace modification - nsmodify
 */

ACPI_STATUS
NsUnloadNamespace (
    ACPI_HANDLE             Handle);

ACPI_STATUS
NsDeleteSubtree (
    ACPI_HANDLE             StartHandle);


/* 
 * Namespace dump/print utilities - nsdump
 */

void
NsDumpTables (
    ACPI_HANDLE             SearchBase, 
    INT32                   MaxDepth);

void
NsDumpEntry (
    ACPI_HANDLE             Handle,
    UINT32                  DebugLevel);

ACPI_STATUS
NsDumpPathname (
    ACPI_HANDLE             Handle, 
    char                    *Msg, 
    UINT32                  Level, 
    UINT32                  Component);

void
NsDumpRootDevices (
    void);


/*
 * Namespace evaluation functions - nseval
 */

ACPI_STATUS
NsEvaluateByHandle (
    NAME_TABLE_ENTRY        *ObjectNte, 
    ACPI_OBJECT_INTERNAL    **Params,
    ACPI_OBJECT_INTERNAL    *ReturnObject);

ACPI_STATUS
NsEvaluateByName (
    char                    *Pathname, 
    ACPI_OBJECT_INTERNAL    **Params,
    ACPI_OBJECT_INTERNAL    *ReturnObject);

ACPI_STATUS
NsEvaluateRelative (
    NAME_TABLE_ENTRY        *ObjectNte, 
    char                    *Pathname, 
    ACPI_OBJECT_INTERNAL    **Params,
    ACPI_OBJECT_INTERNAL    *ReturnObject);


ACPI_STATUS
NsExecuteControlMethod (
    NAME_TABLE_ENTRY        *MethodNte, 
    ACPI_OBJECT_INTERNAL    **Params);

ACPI_STATUS
NsGetObjectValue (
    NAME_TABLE_ENTRY        *ObjectNte);


/*
 * Parent/Child/Peer utility functions - nsfamily
 */

ACPI_NAME
NsFindParentName (
    NAME_TABLE_ENTRY        *EntryToSearch);

INT32
NsExistDownstreamSibling (
    NAME_TABLE_ENTRY        *ThisEntry, 
    INT32                   Size, 
    NAME_TABLE_ENTRY        *Appendage);


/*
 * Scope manipulation - nsscope
 */

INT32
NsOpensScope (
    ACPI_OBJECT_TYPE        Type);

char *
NsNameOfScope (
    NAME_TABLE_ENTRY        *EntryToSearch);

char *
NsNameOfCurrentScope (
    void);

ACPI_STATUS
NsHandleToPathname (
    ACPI_HANDLE             ObjHandle,
    UINT32                  *BufSize,
    char                    *UserBuffer);

BOOLEAN
NsPatternMatch (
    NAME_TABLE_ENTRY        *ObjEntry, 
    char                    *SearchFor);
        
void *
NsNameCompare (
    ACPI_HANDLE             ObjHandle, 
    UINT32                  Level, 
    void                    *Context);

void
NsLowFindNames (
    NAME_TABLE_ENTRY        *ThisEntry, 
    char                    *SearchFor,
    INT32                   *Count, 
    ACPI_HANDLE             List[], 
    INT32                   MaxDepth);

ACPI_HANDLE *
NsFindNames (
    char                    *SearchFor, 
    ACPI_HANDLE             SearchBase, 
    INT32                   MaxDepth);

ACPI_STATUS
NsGetNte (
    char                    *Name, 
    ACPI_HANDLE             Scope,
    NAME_TABLE_ENTRY      **OutNte);

/*
 * Object management for NTEs - nsobject
 */

ACPI_STATUS
NsAttachMethod (
    ACPI_HANDLE             ObjHandle, 
    UINT8                   *PcodeAddr, 
    UINT32                  PcodeLength);

ACPI_STATUS
NsAttachObject (
    ACPI_HANDLE             ObjHandle, 
    ACPI_HANDLE             Value, 
    UINT8                   ValTyp);


void *
NsCompareValue (
    ACPI_HANDLE             ObjHandle, 
    UINT32                  Level, 
    void                    *ObjDesc);

ACPI_HANDLE
NsFindAttachedObject (
    ACPI_OBJECT_INTERNAL    *ObjDesc, 
    ACPI_HANDLE             SearchBase, 
    INT32                   MaxDepth);


/*
 * Namespace searching and entry - nssearch
 */

ACPI_STATUS
NsSearchAndEnter (
    UINT32                  EntryName, 
    NAME_TABLE_ENTRY        *NameTable,
    OPERATING_MODE          LoadMode, 
    ACPI_OBJECT_TYPE        Type, 
    UINT32                  Flags,
    NAME_TABLE_ENTRY        **RetEntry);

void
NsInitializeTable (
    NAME_TABLE_ENTRY        *NewTbl, 
    NAME_TABLE_ENTRY        *ParentScope, 
    NAME_TABLE_ENTRY        *ParentEntry);


/*
 * Scope Stack manipulation - nsstack
 */

void
NsPushCurrentScope (
    NAME_TABLE_ENTRY        *NewScope, 
    ACPI_OBJECT_TYPE        Type);

void
NsPushMethodScope (
    ACPI_HANDLE             NewScope);

INT32
NsPopCurrent (
    ACPI_OBJECT_TYPE        Type);


/*
 * ACPI Table functions - nstables
 */

ACPI_STATUS
NsGetTablePtr (
    ACPI_TABLE_TYPE         TableType, 
    UINT32                  Instance,
    ACPI_TABLE_HEADER       **TablePtrLoc);

ACPI_STATUS
NsFindRsdp (
    char                    *BufferPtr,
    ACPI_TABLE_DESC         *TableInfo);

ACPI_STATUS
NsVerifyTableChecksum (
    void                    *TableHeader); 

ACPI_STATUS
NsGetTable (
    void                    *PhysicalAddress, 
    char                    *BufferPtr,
    ACPI_TABLE_DESC         *TableInfo);

ACPI_STATUS
NsGetTableFacs (
    char                    *BufferPtr,
    ACPI_TABLE_DESC         *TableInfo);


/*
 * Utility functions - nsutils
 */

UINT8
NsChecksum (
    void                    *Buffer,
    UINT32                  Length);

ACPI_OBJECT_TYPE
NsGetType (
    ACPI_HANDLE             ObjHandle);

void *
NsGetAttachedObject (
    ACPI_HANDLE             ObjHandle);

INT32
NsLocal (
    ACPI_OBJECT_TYPE        Type);

ACPI_STATUS
NsInternalizeName (
    char                    *DottedName,
    char                    **ConvertedName);

INT32
IsNsObject (
    ACPI_OBJECT_INTERNAL    *pOD);

INT32
NsMarkNS(
    void);

NAME_TABLE_ENTRY *
NsConvertHandleToEntry (
    ACPI_HANDLE             Handle);

ACPI_HANDLE
NsConvertEntryToHandle(
    NAME_TABLE_ENTRY *Nte);

void
NsTerminate (
    void);



#endif /* __NAMESPACE_H__ */
