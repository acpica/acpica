
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


#ifndef __NAMESPACE_H__
#define __NAMESPACE_H__

#include <datatypes.h>
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
#define NEXTSEG(NameTbl) ((NAME_TABLE_ENTRY **)NameTbl)[-1]

/* 
 * An NsHandle (which is actually an NAME_TABLE_ENTRY *) can appear in some contexts,
 * such as on apObjStack, where a pointer to an OBJECT_DESCRIPTOR can also
 * appear.  This macro is used to distinguish them.
 *
 * The first byte of an NAME_TABLE_ENTRY is a character of the name segment, which will
 * be accepted by NcOK().  The first byte of an OBJECT_DESCRIPTOR is the
 * ValTyp field, whose (UINT8) value comes from the NsType enumeration.
 * Valid NsType values must not include any character acceptable in a name.
 */

#define IS_NS_HANDLE(h)         (AmlGoodChar((INT32) * (char *) (h)))

/* To search the entire name space, pass this as SearchBase */

#define NS_ALL                  ((NsHandle)0)

/* 
 * Elements of NsProperties are bit significant
 * and should be one-to-one with values of NsType in acpinmsp.h
 */
#define NEWSCOPE                1   /* a definition of this type opens a name scope */
#define LOCAL                   2   /* suppress search of enclosing scopes */


/* UINT32 definitions of the predefined namespace names */

#define NS_ROOT                 '/   '
#define NS_SYSTEM_BUS           '_BS_'

/* Char * definitions of common namespace names */

#define NS_ROOT_PATH            "/"



/*
 * Top-level namespace access - nsaccess
 */


ACPI_STATUS
NsSetup (
    void);

ACPI_STATUS
NsEnter (
    char                *Name, 
    NsType              Type, 
    OpMode              iLE,
    NAME_TABLE_ENTRY    **RetEntry);

ACPI_STATUS
NsUnloadNamespace (
    NsHandle            Handle);

ACPI_STATUS
NsDeleteSubtree (
    NsHandle            StartHandle);


/* 
 * Namespace dump/print utilities - nsdump
 */

void
NsDumpTables (
    NsHandle            SearchBase, 
    INT32               MaxDepth);

void
NsDumpEntry (
    NsHandle            Handle);

ACPI_STATUS
NsDumpPathname (
    NsHandle            Handle, 
    char                *Msg, 
    UINT32              Level, 
    UINT32              Component);


/*
 * Namespace evaluation functions - nseval
 */

ACPI_STATUS
NsEvaluateByHandle (
    NAME_TABLE_ENTRY    *ObjectNte, 
    OBJECT_DESCRIPTOR   *ReturnObject,
    OBJECT_DESCRIPTOR   **Params);

ACPI_STATUS
NsEvaluateByName (
    char                *Pathname, 
    OBJECT_DESCRIPTOR   *ReturnObject,
    OBJECT_DESCRIPTOR   **Params);

ACPI_STATUS
NsEvaluateRelative (
    NAME_TABLE_ENTRY    *ObjectNte, 
    char                *Pathname, 
    OBJECT_DESCRIPTOR   *ReturnObject,
    OBJECT_DESCRIPTOR   **Params);


ACPI_STATUS
NsExecuteControlMethod (
    NAME_TABLE_ENTRY    *MethodNte, 
    OBJECT_DESCRIPTOR   **Params);

ACPI_STATUS
NsGetObjectValue (
    NAME_TABLE_ENTRY    *ObjectNte);


/*
 * Parent/Child/Peer utility functions - nsfamily
 */

char *
NsFindParentName (
    NAME_TABLE_ENTRY    *EntryToSearch, 
    INT32               Trace);

INT32
NsExistDownstreamSibling (
    NAME_TABLE_ENTRY    *ThisEntry, 
    INT32               Size, 
    NAME_TABLE_ENTRY    *Appendage);

NsHandle 
NsGetParentHandle (
    NsHandle            Look);


/*
 * Scope manipulation - nsscope
 */

INT32
NsOpensScope (
    NsType              Type);

char *
NsNameOfScope (
    NAME_TABLE_ENTRY    *EntryToSearch);

char *
NsNameOfCurrentScope (
    void);

ACPI_STATUS
NsHandleToPathname (
    NsHandle            ObjHandle,
    UINT32              BufSize,
    char                *UserBuffer);

ACPI_STATUS
NsSetMethod (
    NsHandle            ObjHandle, 
    ptrdiff_t           Offset, 
    INT32               Length);

void
NsSetValue (
    NsHandle            ObjHandle, 
    ACPI_OBJECT_HANDLE  v, 
    UINT8               ValTyp);

BOOLEAN
NsPatternMatch (
    NAME_TABLE_ENTRY    *ObjEntry, 
    char                *SearchFor);
        
void *
NsNameCompare (
    NsHandle            ObjHandle, 
    UINT32              Level, 
    void                *Context);

void
NsLowFindNames (
    NAME_TABLE_ENTRY    *ThisEntry, 
    char                *SearchFor,
    INT32               *Count, 
    NsHandle            List[], 
    INT32               MaxDepth);

NsHandle *
NsFindNames (
    char                *SearchFor, 
    NsHandle            SearchBase, 
    INT32               MaxDepth);

ACPI_STATUS
NsGetHandle (
    char                *Name, 
    NsHandle            Scope,
    NsHandle            *OutHandle);

void *
NsCompareValue (
    NsHandle            ObjHandle, 
    UINT32              Level, 
    void                *ObjDesc);

NsHandle
NsFindValue (
    OBJECT_DESCRIPTOR   *ObjDesc, 
    NsHandle            SearchBase, 
    INT32               MaxDepth);

/*
 * Namespace searching and entry - nssearch
 */


ACPI_STATUS
NsSearchAndEnter (
    char                *NamSeg, 
    NAME_TABLE_ENTRY    *NameTbl, 
    OpMode              LoadMode, 
    NsType              Type,
    NAME_TABLE_ENTRY    **RetNte);

void
NsInitializeTable (
    NAME_TABLE_ENTRY    *NewTbl, 
    NAME_TABLE_ENTRY    *ParentScope, 
    NAME_TABLE_ENTRY    *ParentEntry);

/*
 * Scope Stack manipulation - nsstack
 */

void
NsPushCurrentScope (
    NAME_TABLE_ENTRY    *NewScope, 
    NsType              Type);

void
NsPushMethodScope (
    NsHandle            nNewScope);

INT32
NsPopCurrent (
    NsType              Type);


/*
 * ACPI Table functions - nstables
 */

ACPI_STATUS
NsFindRootSystemDescriptorPointer (
    ROOT_SYSTEM_DESCRIPTOR_POINTER  ** RSDP,
    OSD_FILE                        *InputFile);

INT32
NsVerifyTableChecksum (
    void                *TableHeader, 
    INT32               DisplayBitFlags);

ACPI_STATUS
NsGetTable (
    UINT32              PhysicalAddress, 
    OSD_FILE            *InputFile,
    void *              *Table);

ACPI_STATUS
NsGetFACS (
    OSD_FILE            *InputFile,
    void *              *Table);


/*
 * Utility functions - nsutils
 */

NAME_TABLE_ENTRY *
NsAllocateNteDesc (
    INT32               Size);

UINT8
NsChecksum (
    void                *Buffer,
    UINT32              Length);

NsType
NsGetType (
    NsHandle            ObjHandle);

void *
NsGetValue (
    NsHandle            ObjHandle);

INT32
NsLocal (
    NsType              Type);

char *
NsInternalizeName (
    char                *DottedName);

INT32
IsNsValue (
    OBJECT_DESCRIPTOR   *pOD);

INT32
NsMarkNS(
    void);

NAME_TABLE_ENTRY *
NsConvertHandleToEntry (
    NsHandle            Handle);


/*
 * TBD: What is PLUMBER??
 */

#ifndef PLUMBER

/* dummy macros to make calls go away */

#define MarkStaticBlocks(Count)
#define RegisterStaticBlockPtr(BP)

#else

void
RegisterStaticBlockPtr (
    void                **BP);

void
MarkStaticBlocks (
    INT32               *Count);

#endif /* PLUMBER */




#endif /* __NAMESPACE_H__ */
