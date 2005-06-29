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
 | $Revision: 1.4 $
 | $Date: 2005/06/29 19:49:30 $
 | $Log: acnamesp.h,v $
 | Revision 1.4  2005/06/29 19:49:30  aystarik
 | Moved definition of NsType to acpiobj.h
 |
 | 
 | date	99.02.04.00.12.00;	author rmoore1;	state Exp;
 |
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
// Added vNsPushMethodScope(), iIsNsValue(), vRegisterStaticBlockPtr(), and
//   vMarkStaticBlocks().
// 
//    Rev 1.22   26 Nov 1997 16:19:44   phutchis
// Code inspection rework:
//   Made acBadType[] public so other modules can check for it in apcNsTypeNames[].
// 
//    Rev 1.21   31 Oct 1997 15:57:30   phutchis
// Rework from code inspection:
//   Added/revised comments throughout.
//   Added #include <stddef.h> to get typedef for ptrdiff_t.
//   Changed vNsPopCurrent() to iNsPopCurrent(), returning the number of frames
//     popped (or an error indication).
//   Changed empty formal parameter lists to "(void)".
//   Changed meth.iOffset, and other values which are offsets, from (int) to
//     (ptrdiff_t).
//   Replaced "int iLoading" parameter of hNsEnter() with "OpMode iLE".
// Removed vReporter() parameter from several functions.
//   Removed iExistDownstreamSibling() which is now static.
// 
//    Rev 1.20   08 Oct 1997 16:32:28   kdbranno
// Removed define/undefine of OBJECT_DESCRIPTOR.  Added #include of amlpub.h
// when ACPILIB_GEN is not defined.
// 
//    Rev 1.19   24 Sep 1997 15:11:36   phutchis
// Add function declaration for iNsMarkNS().
// 
//    Rev 1.18   16 Sep 1997 10:43:00   phutchis
// Added function hNsGetHandle()
// 
//    Rev 1.17   04 Aug 1997 16:14:12   kdbranno
// Added function hGetParentHandle.
// 
//    Rev 1.16   29 Jul 1997 14:34:28   phutchis
// Add ppsParams parameter to iAcpiExecuteMethod() and iAmlExec()
// 
//    Rev 1.15   11 Jul 1997 16:13:58   phutchis
// Fix problem with ordering of recursive includes
// 
//    Rev 1.14   11 Jul 1997 16:07:38   phutchis
// Add iIsNsHandle() macro.
// 
//    Rev 1.13   08 Jul 1997 17:03:22   phutchis
// Add ppsReturnValue parameter to iAcpiExecuteMethod().
// This requires #include of amlexec.h and amlpriv.h
// 
//    Rev 1.12   18 Jun 1997 09:34:42   phutchis
// Add hSearchBase and iMaxDepth parameters to vNsDumpTables()
// and phNsFindNames()
// 
//    Rev 1.11   12 Jun 1997 11:43:52   phutchis
// Conform function headers to .c file.
// 
//    Rev 1.10   12 Jun 1997 09:59:54   phutchis
// Add parameter to phNsFindNames() to enable searching a subtree.
// 
//    Rev 1.9   11 Jun 1997 15:51:12   phutchis
// Add entry point phNsFindNames.
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
// Added DisplayBitFlags parameter to vNsDumpTables()
//
//    Rev 1.2   14 Mar 1997 17:46:26   phutchis
// Renamed vNsEnter to hNsEnter to correspond to its return value
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
 * bValTyp field, whose (BYTE) value comes from the NsType enumeration.
 * Valid NsType values must not include any character acceptable in a name.
 */

#define iIsNsHandle(h) (NcOK((int)*(char *)(h)))


/* To search the entire name space, pass this as hSearchBase */

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

extern char acBadType[];
extern char *apcNsTypeNames[];


/****************************************************************************
 * FUNCTION:    vNsPushMethodScope
 *
 * PARAMETERS:  NsHandle nNewScope,             name to be made current
 *
 * DESCRIPTION: Push the current scope on the scope stack, and make the
 *              passed nte current.
 *
 ***************************************************************************/

void
vNsPushMethodScope(NsHandle nNewScope);


/****************************************************************************
 * FUNCTION:    iAcpiExecuteMethod
 *
 * PARAMETERS:  char *pcMethodName              name of method to execute
 *
 *              OBJECT_DESCRIPTOR **ppsReturnValue  where to put method's return
 *                                              value (if any).
 *                                              ppsReturnValue must not be
 *                                              passed in as NULL because
 *                                              *ppsReturnValue will always
 *                                              be set (to NULL if there is
 *                                              no return value).
 *
 *              OBJECT_DESCRIPTOR **ppsParams   list of parameters to pass to
 *                                              method, terminated by NULL.
 *                                              ppsParams itself may be NULL
 *                                              if no parameters are being
 *                                              passed.
 *
 * RETURN:      E_OK or E_ERROR
 *
 * DESCRIPTION: Find and execute the requested method passing the given
 *              parameters
 *
 ****************************************************************************/

int
iAcpiExecuteMethod (char * pcMethodName, OBJECT_DESCRIPTOR **ppsReturnValue,
        OBJECT_DESCRIPTOR **ppsParams);


/****************************************************************************
 * FUNCTION:    iAcpiLoadNameSpace
 *
 * PARAMETERS:  none
 *
 * RETURN:      E_OK or E_ERROR
 *
 * DESCRIPTION: Expands namespace, typically in response to a docking event
 *
 ****************************************************************************/

int
iAcpiLoadNameSpace (void);


/****************************************************************************
 * FUNCTION:    iAcpiUnloadNameSpace 
 *
 * PARAMETERS:  none
 *
 * RETURN:      E_OK or E_ERROR
 *
 * DESCRIPTION: Contracts namespace, typically in response to an undocking
 *              event
 *
 ****************************************************************************/

int
iAcipUnloadNameSpace (void);


/****************************************************************************
 * FUNCTION:    iNsValType
 *
 * PARAMETERS:  NsHandle h      Handle of nte to be examined
 *
 * RETURN:      iType field from nte whose handle is passed
 *
 ***************************************************************************/

NsType
iNsValType(NsHandle h);


/****************************************************************************
 * FUNCTION:    pvNsValPtr
 *
 * PARAMETERS:  NsHandle h      Handle of nte to be examined
 *
 * RETURN:      pVal field from nte whose handle is passed
 *
 ***************************************************************************/

void *
pvNsValPtr(NsHandle h);


/****************************************************************************
 * FUNCTION:    vNsSetup
 *
 * PARAMETERS:  none
 *
 * DESCRIPTION: Allocate and initialize the root name table
 *
 ***************************************************************************/

void
vNsSetup(void);


/****************************************************************************
 * FUNCTION:    iNsPopCurrent
 *
 * PARAMETERS:  NsType iType    The type of frame to be found
 *
 * DESCRIPTION: Pop the scope stack until a frame of the requested type
 *              is found.
 *
 * RETURN:      Count of frames popped.  If no frame of the requested type
 *              was found, the count is returned as a negative number and
 *              the scope stack is emptied (which sets the current scope
 *              to the root).  If the scope stack was empty at entry, the
 *              function is a no-op and returns 0.
 *
 ***************************************************************************/

int
iNsPopCurrent(NsType iType);


/****************************************************************************
* FUNCTION:     hNsEnter
 *
 * PARAMETERS:  char  *pcName   name to be entered, in internal format
 *                              as represented in the AML stream
 *              NsType iType    type associated with name
 *              OpMode iLE      Load => add name if not found
 *
 * RETURN:      Handle to the nte for the passed name
 *
 * DESCRIPTION: Find or enter the passed name in the name space.
 *
 ***************************************************************************/

NsHandle
hNsEnter(char *pcName, NsType iType, OpMode iLE);


/****************************************************************************
 * FUNCTION:    hGetParentHandle
 *
 * PARAMETERS:  NsHandle hLook - Handle whose parent is to be returned
 *
 * RETURN:      Parent of parameter.    NOTFOUND if hLook is invalid
 *              or hLook refers to the root.
 *
 ***************************************************************************/

NsHandle 
hGetParentHandle(NsHandle hLook);


/****************************************************************************
 * FUNCTION:    pcNsNameOfCurrentScope
 *
 * PARAMETERS:  none
 *
 * RETURN:      pointer to storage containing the name of the current scope
 *
 * DESCRIPTION:
 *
 ***************************************************************************/

char *
pcNsNameOfCurrentScope(void);


/****************************************************************************
 * FUNCTION:    pcNsFullyQualifiedName
 *
 * PARAMETERS:  NsHandle hLook      handle of nte whose name is to be found
 *
 * RETURN:      pointer to storage containing the name, in external format
 *
 * DESCRIPTION:
 *
 ***************************************************************************/

char *
pcNsFullyQualifiedName(NsHandle hLook);


/****************************************************************************
 * FUNCTION:    vNsSetMethod
 *
 * PARAMETERS:  NsHandle        h           handle of nte to be set
 *              ptrdiff_t       iOffset     value to be set
 *              long            lLength     length associated with value
 *
 * DESCRIPTION: Record the given offset and p-code length of the method
 *              whose handle is passed
 *
 ***************************************************************************/

void
vNsSetMethod(NsHandle h, ptrdiff_t iOffset, long lLength);


/****************************************************************************
 * FUNCTION:    vNsSetValue
 *
 * PARAMETERS:  NsHandle            hN          handle of nte to be set
 *              ACPI_OBJECT_HANDLE  hV          value to be set
 *              BYTE                bValTyp     type of value,
 *                                              or Any if not known
 *
 * DESCRIPTION: Record the given object as the value associated with the
 *              name whose NsHandle is passed
 *
 ***************************************************************************/

void
vNsSetValue(NsHandle hN, ACPI_OBJECT_HANDLE hV, BYTE bValTyp);


/****************************************************************************
 * FUNCTION:    vNsDumpTables
 *
 * PARAMETERS:  int iDisplayBitFlags        See definitions of OUTPUT_DATA
 *                                          and related symbols in display.h
 *              int iUseGraphicCharSet      1 => use graphic character set to
 *                                          draw links in name space tree
 *                                          0 => use +, -, and | to draw links
 *              NsHandle hSearchBase        Root of subtree to be dumped, or
 *                                          NS_ALL to dump the entire namespace
 *              int     iMaxDepth           Maximum depth of dump.  Use INT_MAX
 *                                          for an effectively unlimited depth.
 *
 * DESCRIPTION: Dump the name space, or a portion of it.
 *
 ***************************************************************************/

void
vNsDumpTables(int iDisplayBitFlags, int iUseGraphicCharSet,
                NsHandle hSearchBase, int iMaxDepth);


/****************************************************************************
 * FUNCTION:    NsDumpEntry
 *
 * PARAMETERS:  NsHandle h      Entry to be dumped
 *
 * DESCRIPTION: Dump a single nte
 *
 ***************************************************************************/

void
vNsDumpEntry(NsHandle h, int iDisplayBitFlags);


/****************************************************************************
 * FUNCTION:    phNsFindNames
 *
 * PARAMETERS:  char        *pcSearchFor    pattern to be found.
 *                                          4 bytes, ? matches any character.
 *                                          If NULL, "????" will be used.
 *              NsHandle    hSearchBase     Root of subtree to be searched, or
 *                                          NS_ALL to search the entire namespace
 *              int         iMaxDepth       Maximum depth of search.  Use INT_MAX
 *                                          for an effectively unlimited depth.
 *
 * DESCRIPTION: Traverse the name space finding names which match a search
 *              pattern, and return an array of handles.  The end of the
 *              array is marked by the value (NsHandle)0.  A return value
 *              of (NsHandle *)0 indicates that no matching names were
 *              found or that space for the list could not be allocated.
 *              if hSearchBase is NS_ALL (null) search from the root,
 *              else it is a handle whose children are to be searched.
 *
 ***************************************************************************/

NsHandle *
phNsFindNames(char *pcSearchFor, NsHandle hSearchBase, int iMaxDepth);


/****************************************************************************
 * FUNCTION:    hNsGetHandle
 *
 * PARAMETERS:  char        *pcName     Name to be found, in external (ASL)
 *                                      format.  The \ and ^ prefixes, and the
 *                                      . to separate segments, are supported.
 *
 *              NsHandle    hScope      Root of subtree to be searched, or
 *                                      NS_ALL for the root of the name space.
 *                                      If pcName is fully qualified (first char
 *                                      is '\'), the passed value of hScope will
 *                                      not be accessed.
 *
 * DESCRIPTION: Look up a name relative to a given scope and return the
 *              corresponding handle, or (NsHandle)NOTFOUND.
 *
 ***************************************************************************/

NsHandle
hNsGetHandle(char *pcName, NsHandle hScope);


/*****************************************************************************
 * FUNCTION:    iIsNsValue
 *
 * PARAMETERS:  OBJECT_DESCRIPTOR *pOD
 *
 * RETURN:      TRUE if the passed descriptor is the value of a Name in
 *              the name space, else FALSE
 *
 ****************************************************************************/

int
iIsNsValue(OBJECT_DESCRIPTOR *pOD);


/****************************************************************************
 * FUNCTION:    iNsMarkNS
 *
 * PARAMETERS:  none
 *
 * DESCRIPTION: If compiled with bu_plumr.h, traverse the name space
 *              "marking" all name tables and reachable values.
 *
 * RETURN:      The number of blocks marked
 *
 ***************************************************************************/

int
iNsMarkNS(void);


#ifndef PLUMBER

/* dummy macros to make calls go away */

#define vMarkStaticBlocks(piCount)
#define vRegisterStaticBlockPtr(ppvBP)

#else

/****************************************************************************
 * FUNCTION:    vRegisterStaticBlockPtr
 *
 * PARAMETERS:  void    **ppvBP         Addr of static pointer to be registered
 *
 * DESCRIPTION: If compiled with bu_plumr.h, add the pointer whose address
 *              is passed to the registry.  vMarkStaticBlocks() will then
 *              "mark" each block pointed to by a registered pointer.
 *
 ***************************************************************************/

void
vRegisterStaticBlockPtr(void **ppvBP);


/****************************************************************************
 * FUNCTION:    vMarkStaticBlocks
 *
 * PARAMETERS:  int *piCount        Count of blocks marked
 *
 * DESCRIPTION: "Mark" all blocks pointed to by registered static pointers
 *
 ***************************************************************************/
void
vMarkStaticBlocks(int *piCount)
;

#endif /* PLUMBER */

#endif /* __ACPINMSP_H__ */
