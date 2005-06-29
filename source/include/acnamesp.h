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
 | $Revision: 1.10 $
 | $Date: 2005/06/29 19:49:36 $
 | $Log: acnamesp.h,v $
 | Revision 1.10  2005/06/29 19:49:36  aystarik
 | 16/32/64-bit common data types
 |
 | 
 | date	99.03.10.00.04.00;	author rmoore1;	state Exp;
 |
 * 
 * 10    3/09/99 4:04p Rmoore1
 * 16/32/64-bit common data types
 * 
 * 9     2/16/99 3:36p Rmosgrov
 * 
 * 8     2/16/99 3:04p Rmosgrov
 * 
 * 7     2/16/99 10:15a Rmosgrov
 * 
 * 6     2/12/99 4:22p Rmosgrov
 * 
 * 5     2/12/99 10:26a Rmosgrov
 * Anti-Polish clean up
 * 
 * 4     2/03/99 4:12p Rmoore1
 * Moved definition of NsType to acpiobj.h
 * 
 * 3     1/13/99 10:50a Grsmith1
 * First BeOS compatible check-in.
 * 
 * 2     1/11/99 4:15p Grsmith1
 * 
 * 1     1/11/99 2:10p Rmoore1
 * Subsystem headers
// 
//    Rev 1.23   05 Feb 1998 11:56:34   phutchis
// Added NsPushMethodScope(), IsNsValue(), RegisterStaticBlockPtr(), and
//   MarkStaticBlocks().
// 
//    Rev 1.22   26 Nov 1997 16:19:44   phutchis
// Code inspection rework:
//   Made acBadType[] public so other modules can check for it in apcNsTypeNames[].
// 
//    Rev 1.21   31 Oct 1997 15:57:30   phutchis
// Rework from code inspection:
//   Added/revised comments throughout.
//   Added #include <stddef.h> to get typedef for ptrdiff_t.
//   Changed vNsPopCurrent() to NsPopCurrent(), returning the number of frames
//     popped (or an error indication).
//   Changed empty formal parameter lists to "(void)".
//   Changed meth.Offset, and other values which are offsets, from (INT32) to
//     (ptrdiff_t).
//   Replaced "INT32 iLoading" parameter of NsEnter() with "OpMode iLE".
// Removed vReporter() parameter from several functions.
//   Removed iExistDownstreamSibling() which is now static.
// 
//    Rev 1.20   08 Oct 1997 16:32:28   kdbranno
// Removed define/undefine of OBJECT_DESCRIPTOR.  Added #include of amlpub.h
// when ACPILIB_GEN is not defined.
// 
//    Rev 1.19   24 Sep 1997 15:11:36   phutchis
// Add function declaration for NsMarkNS().
// 
//    Rev 1.18   16 Sep 1997 10:43:00   phutchis
// Added function NsGetHandle()
// 
//    Rev 1.17   04 Aug 1997 16:14:12   kdbranno
// Added function GetParentHandle.
// 
//    Rev 1.16   29 Jul 1997 14:34:28   phutchis
// Add Params parameter to AcpiExecuteMethod() and iAmlExec()
// 
//    Rev 1.15   11 Jul 1997 16:13:58   phutchis
// Fix problem with ordering of recursive includes
// 
//    Rev 1.14   11 Jul 1997 16:07:38   phutchis
// Add IsNsHandle() macro.
// 
//    Rev 1.13   08 Jul 1997 17:03:22   phutchis
// Add ReturnValue parameter to AcpiExecuteMethod().
// This requires #include of amlexec.h and amlpriv.h
// 
//    Rev 1.12   18 Jun 1997 09:34:42   phutchis
// Add SearchBase and MaxDepth parameters to NsDumpTables()
// and NsFindNames()
// 
//    Rev 1.11   12 Jun 1997 11:43:52   phutchis
// Conform function headers to .c file.
// 
//    Rev 1.10   12 Jun 1997 09:59:54   phutchis
// Add parameter to NsFindNames() to enable searching a subtree.
// 
//    Rev 1.9   11 Jun 1997 15:51:12   phutchis
// Add entry point NsFindNames.
// Add some debug capability.
// 
//    Rev 1.8   14 May 1997 16:05:10   kdbranno
// Removed calloc_bu
//
//    Rev 1.7   13 May 1997 18:00:54   phutchis
// Add guards for uninitialized namespace and hooks for interpreter
//
//    Rev 1.6   16 Apr 1997 15:06:52   kdbranno
// Changed include brackets to quotes for .h files from ACPILIB
// Removed declarations for "meth" and "nte" and returned them to ACPINMSP.C
// Changed prototype for iExistDownstreamSibling
//
//    Rev 1.5   Apr 14 1997 16:18:50   kdbranno
// Moved typedef for nte and meth to acpinmsp.h
//
//    Rev 1.4   Apr 14 1997 15:51:34   kdbranno
// Added prototype for iExistDownstreamSibling
//
//    Rev 1.3   Apr 14 1997 15:43:00   kdbranno
// Added DisplayBitFlags parameter to NsDumpTables()
//
//    Rev 1.2   14 Mar 1997 17:46:26   phutchis
// Renamed vNsEnter to NsEnter to correspond to its return value
// type (handle), and added iLoading parameter.
//
//    Rev 1.1   05 Mar 1997 13:29:14   phutchis
// Added typedefs and function prototypes
//
//    Rev 1.0   Feb 28 1997 13:26:18   KBRANNOC
// Initial revision.
 |__________________________________________________________________________

*/

#ifndef __ACPINMSP_H__
#define __ACPINMSP_H__

#include "acpiobj.h"


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
   #include <acpType.h>
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

#endif /* __ACPINMSP_H__ */
