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
 | FILENAME: acpinmsp.h - prototypes for accessing namespace
 |__________________________________________________________________________
 |
 | $Revision: 1.12 $
 | $Date: 2005/06/29 19:49:38 $
 | $Log: acnamesp.h,v $
 | Revision 1.12  2005/06/29 19:49:38  aystarik
 | Added the currently defined Public APIs and removed a lot of the old
 | source control history
 |
 | 
 | date	99.04.02.18.14.00;	author rmosgrov;	state Exp;
 |
 * 
 * 12    4/02/99 10:14a Rmosgrov
 * Added the currently defined Public APIs and removed a lot of the old
 * source control history
 |__________________________________________________________________________

*/

#ifndef __ACPINMSP_H__
#define __ACPINMSP_H__

#include "acpiobj.h"
#include "pnp.h"

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

#define IsNsHandle(h) (NcOK((INT32)*(char *)(h)))


/* To search the entire name space, pass this as SearchBase */

#define  NS_ALL   ((NsHandle)0)


/* 
 * Definitions in amlpriv.h, including OBJECT_DESCRIPTOR, are internal to the
 * AML scanner/interpreter; however descriptor pointers are used externally
 * as object handles.  If not building the interpreter itself, we need to
 * include amlpub.h, which defines OBJECT_DESCRIPTOR as void so that functions
 * which actually expect (OBJECT_DESCRIPTOR *) are declared as receiving
 * (void *).
 */

#ifdef ACPILIB_GEN
   #include "acpitype.h"
   #include "amlexec.h"
   #include "amlscan.h"
   #include "amlpriv.h"
#else
   #include <acpitype.h>
   #include <amlexec.h>
   #include <amlscan.h>
   #include <amlpub.h>
#endif

extern char BadType[];
extern char *NsTypeNames[];


/* Prototypes */

INT32
PriUnloadNameSpace (void);

void
NsPushMethodScope (NsHandle nNewScope);

INT32
AcpiExecuteMethod (char * MethodName, OBJECT_DESCRIPTOR **ReturnValue,
        OBJECT_DESCRIPTOR **Params);

int 
AcpiInit (char *);

INT32
AcpiLoadNameSpace  (INT32 DisplayAmlDuringLoad);

INT32
AcpiUnloadNameSpace (void);

void
AcpiCleanup (void);

NsType
NsValType (NsHandle h);

void *
NsValPtr (NsHandle h);

void
NsSetup (void);

INT32
NsPopCurrent (NsType Type);

NsHandle
NsEnter (char *Name, NsType Type, OpMode iLE);

NsHandle 
GetParentHandle (NsHandle Look);

char *
NsNameOfCurrentScope (void);

char *
NsFullyQualifiedName (NsHandle Look);

void
NsSetMethod (NsHandle h, ptrdiff_t Offset, INT32 Length);

void
NsSetValue (NsHandle h, ACPI_OBJECT_HANDLE v, UINT8 ValTyp);

void
NsDumpTables (INT32 DisplayBitFlags, INT32 UseGraphicCharSet,
                NsHandle SearchBase, INT32 MaxDepth);

void
NsDumpEntry (NsHandle h, INT32 DisplayBitFlags);

NsHandle *
NsFindNames (char *SearchFor, NsHandle SearchBase, INT32 MaxDepth);

NsHandle
NsGetHandle (char *Name, NsHandle Scope);

INT32
IsNsValue (OBJECT_DESCRIPTOR *pOD);

INT32
NsMarkNS(void);


#ifndef PLUMBER

/* dummy macros to make calls go away */

#define MarkStaticBlocks(Count)
#define RegisterStaticBlockPtr(BP)

#else

void
RegisterStaticBlockPtr (void **BP);

void
MarkStaticBlocks (INT32 *Count);

#endif /* PLUMBER */

/******************************************************************************
 *
 * The following are the publically defined APIs published and exposed to the OSD
 *
 ******************************************************************************/

INT32
AcpiLoadNameSpace (INT32 DisplayAmlDuringLoad);
NsHandle 
AcpiLoadTable (NsHandle OpRegion);

INT32 
AcpiUnLoadTable (NsHandle TableHandle);

NsHandle 
AcpiLoadTableFromFile (char *FileName);

INT32 
AcpiEnumerateDevice (NsHandle DeviceHandle, DEVICE_ID *HidPtr, BOOLEAN *EnumPtr);

NsHandle 
AcpiGetNextSubDevice(NsHandle DeviceHandle, UINT32 Count);

NsHandle 
AcpiNameToHandle (char *NsName, NsHandle Scope);

char * 
AcpiHandleToName (NsHandle InHandle);

NsHandle 
AcpiGetParentHandle (NsHandle ChildHandle);

NsType 
AcpiValueType (NsHandle Handle);

char * 
AcpiCurrentScopeName (void);

BOOLEAN 
AcpiIsNameSpaceHandle (NsHandle QueryHandle);

BOOLEAN 
AcpiIsNameSpaceValue (NsType Value);

INT32
AcpiSetFirmwareWakingVector (UINT32 PhysicalAddress);

INT32
AcpiGetFirmwareWakingVector (UINT32 * PhysicalAddress);

ACPI_TABLE_HEADER * 
AcpiGetTableHeader (NsHandle Handle);

ACPI_TABLE_HEADER * 
AcpiGetTable (NsHandle Handle);

#endif /* __ACPINMSP_H__ */
