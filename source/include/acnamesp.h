
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


/* 
 * If USE_HASHING is not set, there will be an (nte *) prefix to each name
 * table, containing either a NULL pointer or the address of the next array
 * of nte's in the scope.
 */

#ifndef USE_HASHING
#define NEXTSEG(NameTbl) ((nte **)NameTbl)[-1]
#endif



/* 
 * An NsHandle (which is actually an nte *) can appear in some contexts,
 * such as on apObjStack, where a pointer to an OBJECT_DESCRIPTOR can also
 * appear.  This macro is used to distinguish them.
 *
 * The first byte of an nte is a character of the name segment, which will
 * be accepted by NcOK().  The first byte of an OBJECT_DESCRIPTOR is the
 * ValTyp field, whose (UINT8) value comes from the NsType enumeration.
 * Valid NsType values must not include any character acceptable in a name.
 */

#define IsNsHandle(h)           (NcOK ((INT32) * (char *) (h)))


/* To search the entire name space, pass this as SearchBase */

#define  NS_ALL                 ((NsHandle)0)


#define NUM_NS_TYPES            37


/* 
 * Elements of NsProperties are bit significant
 * and should be one-to-one with values of NsType in acpinmsp.h
 */
#define NEWSCOPE    1               /* a definition of this type opens a name scope */
#define LOCAL       2               /* suppress search of enclosing scopes */



/* 
 * Names built-in to the interpreter
 *
 * Initial values are currently supported only for types String and Number.
 * To avoid type punning, both are specified as strings in this table.
 */

static struct InitVal {
    char        *Name;
    NsType      Type;
    char        *Val;
} PreDefinedNames[] = {
    {"_GPE",    DefAny},
    {"_PR_",    DefAny},
    {"_SB_",    DefAny},
    {"_SI_",    DefAny},
    {"_TZ_",    DefAny},
    {"_REV",    Number, "2"},
    {"_OS_",    String, "Intel AML interpreter"},
    {"_GL_",    Mutex},

    /* Table terminator */

    {(char *)0, Any}
};


/* Namespace globals */

extern SCOPE_STACK              ScopeStack[];
extern SCOPE_STACK              *CurrentScope;
extern char                     BadType[];
extern char                     *NsTypeNames[NUM_NS_TYPES];
extern INT32                    NsProperties[NUM_NS_TYPES];




/* Prototypes */

INT32
PriUnloadNameSpace (
    void);

void
NsPushMethodScope (
    NsHandle            nNewScope);

INT32
AcpiExecuteMethod (
    char                *MethodName, 
    OBJECT_DESCRIPTOR   **ReturnValue,
    OBJECT_DESCRIPTOR   **Params);

int 
AcpiInit (
    char *);

INT32
AcpiLoadNameSpace  (
    INT32               DisplayAmlDuringLoad);

INT32
AcpiUnloadNameSpace (
    void);

void
AcpiLocalCleanup (
    void);

NsType
NsValType (
    NsHandle            h);

void *
NsValPtr (
    NsHandle            h);

void
NsSetup (
    void);

INT32
NsPopCurrent (
    NsType              Type);

NsHandle
NsEnter (
    char                *Name, 
    NsType              Type, 
    OpMode              iLE);

NsHandle 
GetParentHandle (
    NsHandle            Look);

char *
NsNameOfCurrentScope (
    void);

char *
NsFullyQualifiedName (
    NsHandle            Look);

void
NsSetMethod (
    NsHandle            h, 
    ptrdiff_t           Offset, 
    INT32               Length);
        
void
NsSetValue (
    NsHandle h, 
    ACPI_OBJECT_HANDLE  v, 
    UINT8               ValTyp);

void
NsDumpTables (
    NsHandle            SearchBase, 
    INT32               MaxDepth);

void
NsDumpEntry (
    NsHandle            h);

NsHandle *
NsFindNames (
    char                *SearchFor, 
    NsHandle            SearchBase, 
    INT32               MaxDepth);

NsHandle
NsGetHandle (
    char                *Name, 
    NsHandle            Scope);

INT32
IsNsValue (
    OBJECT_DESCRIPTOR   *pOD);

INT32
NsMarkNS(
    void);


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

/******************************************************************************
 *
 * The following are the publically defined APIs published and exposed to the OSD
 *
 ******************************************************************************/

INT32
AcpiLoadNameSpace (
    INT32               DisplayAmlDuringLoad);

NsHandle 
AcpiLoadTable (
    NsHandle            OpRegion);

INT32 
AcpiUnLoadTable (
    NsHandle            TableHandle);

NsHandle 
AcpiLoadTableFromFile (
    char                *FileName);

INT32 
AcpiEnumerateDevice (
    NsHandle            DeviceHandle, 
    DEVICE_ID           *HidPtr, 
    BOOLEAN             *EnumPtr);

NsHandle 
AcpiGetNextSubDevice(
    NsHandle            DeviceHandle, 
    UINT32              Count);

NsHandle 
AcpiNameToHandle (
    char                *NsName, 
    NsHandle            Scope);

char * 
AcpiHandleToName (
    NsHandle            InHandle);

NsHandle 
AcpiGetParentHandle (
    NsHandle            ChildHandle);

NsType 
AcpiValueType (
    NsHandle            Handle);

char * 
AcpiCurrentScopeName (
    void);

BOOLEAN 
AcpiIsNameSpaceHandle (
    NsHandle            QueryHandle);

BOOLEAN 
AcpiIsNameSpaceValue (
    NsType              Value);

INT32
AcpiSetFirmwareWakingVector (
    UINT32              PhysicalAddress);

INT32
AcpiGetFirmwareWakingVector (
    UINT32              *PhysicalAddress);

ACPI_TABLE_HEADER * 
AcpiGetTableHeader (
    NsHandle            Handle);

ACPI_TABLE_HEADER * 
AcpiGetTable (
    NsHandle            Handle);




#define ACPILIB_DATA_FILE_VERSION "ADF-001"

/* ACPI Table Prototypes */

/* functions visable outside of the library itself */

void 
InitAcpiLibGlobals (
    void);

INT32
LoadNameSpace (
    INT32               DisplayAmlDuringLoad);

INT32
AcpiSetFirmwareWakingVector (
    UINT32              PhysicalAddress);

INT32
AcpiGetFirmwareWakingVector (
    UINT32              *PhysicalAddress);

/* functions private to the library */

INT32
FindRootSystemDescriptorPointer (
    ROOT_SYSTEM_DESCRIPTOR_POINTER  ** RSDP,
    OSD_FILE                        *InputFile);

UINT8
checksum (
    void                *Buffer,
    UINT32              Length);


INT32
VerifyTableChecksum (
    void                *TableHeader, 
    INT32               DisplayBitFlags);

void * 
GetTable (
    UINT32              PhysicalAddress, 
    OSD_FILE            *InputFile);

void * 
GetFACS (
    OSD_FILE            *InputFile);




/* nsaccess functions */


INT32
ExistDownstreamSibling (
    nte                 *ThisEntry, 
    INT32               Size, 
    nte                 *Appendage);


char *
InternalizeName (
    char                *DottedName);

void
NsPushCurrentScope (
    nte                 *NewScope, 
    NsType              Type);

nte *
AllocateNteDesc (
    INT32               Size);

nte *
SearchTable (
    char                *NamSeg, 
    nte                 *NameTbl, 
    INT32               TableSize, 
    OpMode              LoadMode, 
    NsType              Type);

INT32
NsOpensScope (
    NsType              Type);

NsHandle
NsFindpVal (
    OBJECT_DESCRIPTOR   *ObjDesc, 
    NsHandle            SearchBase, 
    INT32               MaxDepth);

char *
FindParentName (
    nte                 *EntryToSearch, 
    INT32               Trace);



#endif /* __NAMESPACE_H__ */
