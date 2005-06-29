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
 | FILENAME: namespace.h - prototypes for accessing namespace
 |__________________________________________________________________________

*/

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

extern char                     BadType[];
extern char                     *NsTypeNames[NUM_NS_TYPES];
extern INT32                    NsProperties[NUM_NS_TYPES];


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


/* 
 * Typedef nte (name table entry) is private to acpinmsp.c to avoid global
 * impact in the event of changes to it.  The externally-known type NsHandle
 * is actually an (nte *).  If an external program needs to extract a field
 * from the nte, it should use an access function defined in acpinmsp.c
 *
 * If you need an access function not provided herein, add it to this module
 * rather than exporting the nte typedef.
 *
 * (nte *) are actually used in two different and not entirely compatible
 * ways: as pointer to an individual nte and as pointer to an entire name
 * table (which is an array of nte, sometimes referred to as a scope).  In
 * the latter case, the specific nte pointed to may be unused; however its
 * ParentScope member will be valid.
 */

typedef struct nte
{
    UINT32          NameSeg;        /* name segment, always 4 chars per ACPI spec.
                                     * NameSeg must be the first field in the nte
                                     * -- see the IsNsHandle macro in acpinmsp.h
                                     */
    struct nte      *ChildScope;    /* next level of names */
    struct nte      *ParentScope;   /* previous level of names */
    NsType          NtType;         /* type associated with name */
    void            *ptrVal;        /* pointer to value */
} nte;

#define NOTFOUND    (nte *)0


/* Stack of currently-open scopes, and pointer to top of that stack */

typedef struct
{
    nte         *Scope;
    /* 
     * Type of scope, typically the same as the type of its parent's entry 
     * (but not the same as the type of its parent's scope).
     */
    NsType      Type;   
} SCOPE_STACK;    



/* Namespace globals */

extern nte          *Root;
extern INT32        NsRootSize;        
extern INT32        NsCurrentSize;      
extern SCOPE_STACK  ScopeStack[];
extern SCOPE_STACK  *CurrentScope;




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
AcpiCleanup (
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
    INT32               DisplayBitFlags, 
    INT32               UseGraphicCharSet,
    NsHandle            SearchBase, 
    INT32               MaxDepth);

void
NsDumpEntry (
    NsHandle            h, 
    INT32               DisplayBitFlags);

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

void
AcpiCleanup (
    void);

/* functions private to the library */

INT32
FindRootSystemDescriptorPointer (
    ROOT_SYSTEM_DESCRIPTOR_POINTER  ** RSDP,
    OSD_FILE                        *InputFile);

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
