/*
  __________________________________________________________________________
 |
 |
 |           Copyright (C) Intel Corporation 1994-1997
 |
 | All rights reserved.  No part of this program or publication may be
 | reproduced, transmitted, transcribed, stored in a retrieval system, or
 | translated into any language or computer language, in any form or by any
 | means, electronic, mechanical, magnetic, optical, chemical, manual, or
 | otherwise, without the prior written permission of Intel Corporation.
 |__________________________________________________________________________
 |
 | FILENAME: acpinmsp.c - functions for accessing ACPI namespace
 |__________________________________________________________________________
 |
 | $Revision: 1.3 $
 | $Date: 2005/06/29 18:15:20 $
 | $Log: nsaccess.c,v $
 | Revision 1.3  2005/06/29 18:15:20  aystarik
 |
 |
 | 
 | date	99.01.13.22.24.00;	author grsmith1;	state Exp;
 |
 * 
 * 3     1/13/99 2:24p Grsmith1
 * 
 * 2     1/11/99 4:18p Grsmith1
 * Detabified.
 * 
 * 1     1/11/99 2:11p Rmoore1
 * Name Space Manipulation
// 
//    Rev 1.55   11 Sep 1998 18:02:52   phutchis
// Change inc_error() etc. to dKinc_error() etc. (error key logging).
// 
//    Rev 1.54   11 Sep 1998 16:26:08   phutchis
// Rename the iType member of the nte to iNtType to improve readability.
// 
// Add support for a Method's nte to have a null pVal field, indicating
// that the Method is undefined (yet we somehow know that the name is
// supposed to represent a Method).
// 
// Refine debug output fron iNsPopCurrent().
// 
// Add a comment re an unfixed bug in hGetParentHandle() when the parent
// directory has multiple extents.
// 
// Reformat overlength lines.
// 
//    Rev 1.53   07 Jul 1998 12:58:58   calingle
// When a name is accessed but not defined (only happens in pass2 or exec),
// the interpreter will issue an error instead of a warning.  The error is
// "Unknown Reference" rather than the "Illegal Forward Reference" warning
// of the past.
//
//    Rev 1.52   02 Jul 1998 08:57:50   calingle
// Debug output added for popping current stack scope.
//
//    Rev 1.51   02 Jun 1998 12:46:08   calingle
// output control during pass 1 of the loader
//
//    Rev 1.49   14 May 1998 16:04:26   phutchis
// Fixed bug in iExistDownstreamSibling() when checking the last entry of an
// extent.
//
//    Rev 1.48   13 Mar 1998 14:05:44   phutchis
// Corrected marking of name tables in vNsMarkNT().
//
//    Rev 1.47   13 Mar 1998 11:16:10   phutchis
// Corrected handling of types BankField, DefField, FieldUnit, IndexField,
//   and Region in vNsMarkNT().
// Call vMarkObjectStack() from iNsMarkNS().
//
//    Rev 1.46   06 Mar 1998 11:41:00   phutchis
// Added comments concerning garbage collection.
// No code changes.
//
//    Rev 1.45   03 Mar 1998 16:31:24   phutchis
// Enable vNsSetValue() to set the value to NULL.
//
//    Rev 1.44   02 Mar 1998 19:02:06   phutchis
// When marking a Name Table, also mark the block(s) occupied by its
// appendage(s).  (The values pointed to by appendages were already
// being marked, but the appendages themselves were not.)
//
//    Rev 1.43   19 Feb 1998 15:25:48   phutchis
// Don't look for an NT appendage if dumping a single entry (DUH!)
//
//    Rev 1.42   05 Feb 1998 17:46:48   phutchis
// Implemented dynamic sizing of name tables.  ROOTSIZE and TABLSIZE now
//   determine the initial allocation, but upon overflow an appendage of
//   TABLSIZE entries is added.
// Also changed "Illegal forward reference..." from an error to a warning.
//   While Memphis appears to tolerate forward references, the implicit
//   definition carries a risk of their being allocated in a different
//   scope than intended.
//
//    Rev 1.41   05 Feb 1998 11:56:30   phutchis
// Temporarily reduced name table sizes.
// Added support for calling a Method from within another Method:
//   Added vNsPushMethodScope()
//   Check for non-empty stacks only at outermost Method exit.
// Improved storage management
//   Added hNsFindpVal(), iIsNsValue(), vRegisterStaticBlockPtr(),
//     and vMarkStaticBlocks().
//   Delete descriptors when popped from stack or overlaid in name table.
//
//    Rev 1.40   18 Dec 1997 21:09:30   kdbranno
// Increased ROOTSIZE and TABLSIZE to 64.  ESG has some scopes that have up
// to 64 entries.  We really should make this into a linked list instead to
// make it entirely dynamic rather than having a static size.
//
//    Rev 1.39   11 Dec 1997 12:08:02   kdbranno
// Fixed bug in nsSearchTable where false failure occured if ROOTSIZE and TABLSIZE were the same.
// Also enabled logging of forward reference problems even when debug level is 0.
// Changed ROOTSIZE and TABLSIZE both to 25
//
//    Rev 1.38   10 Dec 1997 12:58:28   calingle
// increased the size of the ROOTSIZE from 29 to 53
//
//    Rev 1.37   10 Dec 1997 10:45:04   phutchis
// Corrected comments.
// Removed unneeded {}.
// Fixed OpMode parameter to nsSearchTable() call in hNsGetHandle().
//
//    Rev 1.36   10 Dec 1997 09:27:54   kdbranno
// Added vFatalError calls to some malloc_bu validations rather than passing NULL back to caller.
// Reduced ROOTSIZE and TABLESIZE to 29 to save memory
//
//    Rev 1.35   08 Dec 1997 17:09:18   kdbranno
// Added cast to quiet iC386
//
//    Rev 1.34   05 Dec 1997 09:36:12   kdbranno
// Fixed up so it compiles with clean with iRMX.
//
//    Rev 1.33   02 Dec 1997 13:14:02   nburke
// Changed HELLO calls to conditional vFunctionHello calls - temporary.
//
//    Rev 1.32   26 Nov 1997 16:37:00   nburke
// Added HELLO function call to every function in the file.
//
//    Rev 1.31   26 Nov 1997 16:19:40   phutchis
// Code inspection rework:
//   Made acBadType[] public so other modules can check for it in apcNsTypeNames[].
//
//    Rev 1.30   06 Nov 1997 10:10:06   phutchis
// Added some parameter checking and a few more comments.
//
//    Rev 1.29   05 Nov 1997 08:48:30   calingle
// removed #include <bu_plumr.h>
//
//    Rev 1.28   04 Nov 1997 14:18:36   phutchis
// Fix problems in rev 1.27:
//   Restore increment of pcDottedName in pcInternalizeName (lost when the
//     return buffer was changed from static to HWM allocation).
//   Change 4th parameter in recursive call of nsSearchTable to correspond
//     with the change of that parameter from (int) to (OpMode).
// Add debug output when vNsSetValue cannot determine the correct type and
//   sets bValTyp to DefAny.
// Improved comments.
//
//    Rev 1.27   31 Oct 1997 15:43:18   phutchis
// Rework from code inspection:
//   Added/revised comments throughout.
//   Added #include <stddef.h> to get typedef for ptrdiff_t.
//   Replaced empty strings in apcNsTypeNames[] with error message.
//   Renamed nte.ulNamSeg to nte.dNameSeg.
//   Renamed nte.nChildren to nte.nChildScope.
//   Renamed sCurrentScope[] to sScopeStack[].
//   Renamed vNsSetCurrent() to vNsPushCurrentScope().
//   Removed vReporter() parameter from several functions.
//   Added calls to vKFatalError(()) for numerous catastrophic failures.
//   Changed name buffer used by pcInternalizeName() from static to HWM alloc.
//   Changed printf control %ls to %p when printing pointers.
//   Changed return-value symbols SUCCESS, FAILURE, ERROR, and RETURN to
//     S_SUCCESS, S_FAILURE, S_ERROR, and S_RETURN to forestall collisions
//     with other subsystems.
//   Delete allocated return value if caller of iAcpiExecuteMethod() did not
//     provide a place to store the descriptor.
//   Added warnings to various functions for invalid parameters.
//   Replaced "int iAdd" parameter of nsSearchTable() with "OpMode iLE".
//   Fixed major bug in nsSearchTable when USE_HASHING was not #defined.
//   Initial values which are strings now get copied to allocated space
//     instead of being left in compiler-allocated static storage.
//   Changed vNsPopCurrent() to iNsPopCurrent, returning the number of frames
//     popped (or an error indication).
//   Replaced "int iLoading" parameter of hNsEnter() with "OpMode iLE".
//   Revised pcFindParentName() to call hGetParentHandle() instead of
//     duplicating its logic.
//   Changed empty formal parameter lists to "(void)".
//   Changed values which are offsets from (int) to (ptrdiff_t).
//   Improved parameter diagnostics in vNsSetMethod() and vNsSetValue().
//   Revised iExistDownstreamSibling() to eliminate unneeded local variables.
//   Ensure correct table size is passed to various functions depending on
//     whether the root, or some other scope, is being processed.
//   Improve NOTFOUND handling in hNsGetHandle().
//   Made iExistDownstreamSibling() static.
//
//    Rev 1.26   24 Sep 1997 15:10:26   phutchis
// Add #include of bu_plumr.h, and functions vNsMarkNT() and iNsMarkNS(),
//   to audit allocation and find leaks.
// Add allocation comments to function headers.
//
//    Rev 1.25   16 Sep 1997 10:37:18   phutchis
// Renamed nParent member of nte to nParentScope to better reflect its use
// Added scope-related tracing in iAcpiExecuteMethod() and nsSearchTable()
// Handle case where vReporter() parameter to hNsEnter() is NULL
// Corrected oversimplification in hGetParentHandle()
// Corrected handling of subtree search in phNsFindNames()
// Added function pcNsNameOfScope() [generalization of pcNsNameOfCurrentScope()]
// Added function hNsGetHandle()
//
//    Rev 1.24   04 Aug 1997 16:14:04   kdbranno
// Added function hGetParentHandle.
//
//    Rev 1.23   29 Jul 1997 14:35:16   phutchis
// Add ppsParams parameter to iAcpiExecuteMethod()
// Ensure correct setting of current scope when a method starts execution
// Improve reporting of "name table overflow" and "name not found" conditions
//
//    Rev 1.22   16 Jul 1997 14:26:40   phutchis
// Change types of predefined names from Any to DefAny to eliminate
// forward reference complaints.
// Revised error reporting for forward references and excessive ^ in names.
//
//    Rev 1.21   15 Jul 1997 11:56:54   phutchis
// Refined detection of forward references to eliminate flagging of non-
// erroneous cases.
//
//    Rev 1.20   11 Jul 1997 16:05:12   phutchis
// Add iIsNsHandle() macro, some comments re typedef nte, and a function
// header for pcInternalizeName
//
//    Rev 1.19   08 Jul 1997 17:02:30   phutchis
// Add ppsReturnValue parameter to iAcpiExecuteMethod().
//
//    Rev 1.18   03 Jul 1997 16:26:22   phutchis
// fixed typo !!??$$##%%!!!
//
//    Rev 1.17   03 Jul 1997 16:14:30   phutchis
// Adjust scope handling so that types which open a scope level do so only
// when being defined, not when referenced.  (Fix for "Scope stack overflow"
// and other problems in 6/12/97 Anchorage)
// Generate message for forward-referenced names.
// Increment BUlib error count for forward referenced names, scope stack
// overflow, too many ^
// Increment BUlib warning count for name table overflow or allocation fail.
//
//    Rev 1.16   18 Jun 1997 16:41:22   kdbranno
// removed closing comment (star-slash) from change history.
// Caused the file header to end prematurely...
//
//    Rev 1.15   18 Jun 1997 09:35:36   phutchis
// Add hSearchBase and iMaxDepth parameters to vNsDumpTables()
// and phFindNames()
// Replace (XXX) debugging hack with (Trace & TraceNames)
// Clean up some XXX commented areas
//
//    Rev 1.14   12 Jun 1997 10:00:20   phutchis
// Add parameter to phNsFindNames() to enable searching a subtree.
//
//    Rev 1.13   11 Jun 1997 15:47:38   phutchis
// Adjust scope rules to agree with Memphis OS.
// Add capability to preload namespace.
// When a non-method object is passed to iAcpiExecuteMethod,
//   return the object as the result.
// When a search specifying "Any" type finds an object of known type,
//   make subsequent scope-related decisions according to the type found.
// Add capability to get a list of handles whose names match a search pattern.
// Suppress listing while executing.
// Improve checktrash facility.
//
//    Rev 1.12   14 May 1997 16:56:32   phutchis
// Generate debug/trace output only if debug level > 0
//
//    Rev 1.11   14 May 1997 16:05:02   kdbranno
// Removed calloc_bu
//
//    Rev 1.10   13 May 1997 17:57:30   phutchis
// Add guards for uninitialized namespace and hooks for interpreter
//
//    Rev 1.9   16 Apr 1997 15:02:32   kdbranno
// returned declarations for "meth" and "nte" to apcinmsp.c from acpinmsp.h.
// Changed prototpye of iExistDownstreamSibling to take NsHandle rather than
// nte.
// Changed include brackets to quotes for .h files from ACPILIB
//
//    Rev 1.8   Apr 14 1997 16:18:28   kdbranno
// Moved typedef for nte and meth to acpinmsp.h
//
//    Rev 1.7   Apr 14 1997 15:49:08   kdbranno
// Added #include <display.h>.  Implemented function iExistDownstreamSibling().
// Used iExistDownstreamSibling() to make intellegent choice of line drawing
// characters when outputing nametree. Added iDisplayBitFlags parameter to
// vNsDumpTables().
//
//    Rev 1.6   18 Mar 1997 09:29:56   phutchis
// Work around ic386 breakage where enum != int
// Change #include of <malloc.h> to <stdlib.h>
// Cast params of calloc() and NcOK() to proper types
//
//    Rev 1.5   14 Mar 1997 17:44:20   phutchis
// Renamed vNsEnter to hNsEnter to correspond to its return value
// type (handle), and added iLoading parameter.
// iAcpiExecuteMethod() now finds the passed name in the name space,
// locates the method's p-code, and (temporarily) processes it through
// the dumper.  Actual interpretation of the p-code is not yet provided.
//
//    Rev 1.4   12 Mar 1997 17:46:28   phutchis
// Make listing output optional and via printf_bu
// Replace some spaces with tabs
// Add function headers
//
//    Rev 1.3   07 Mar 1997 10:38:04   phutchis
// Change LOGFILE to NSLOGFILE since something is defining LOGFILE
//
//    Rev 1.2   06 Mar 1997 17:21:00   phutchis
// Put debug logging under #ifdef LOGFILE
//
//    Rev 1.1   05 Mar 1997 13:32:56   phutchis
// Added several functions
//
//    Rev 1.0   Feb 28 1997 08:59:24   KBRANNOC
// Initial revision.
 |__________________________________________________________________________

*/

#define __ACPINMSP_C__

/* Defining FETCH_VALUES enables iAcpiExecuteMethod() to "execute"
 *  a name which is not a Method by fetching and returning its value.
 */
#define FETCH_VALUES

static int TRACE = 1;   /* set non-zero to enable some flow tracing
                                 * in vNsDumpTable() and vNsDumpEntry()
                                 */

/* Table sizes
 *  if USE_HASHING is #defined, these must be prime numbers and
 *  should be large enough that the tables never get terribly full.
 *
 *  The root NT was made bigger than others in the, possibly erroneous,
 *  expectation that there might be quite a few entries in the root.
 */
#ifdef USE_HASHING
#define ROOTSIZE 101 /* # of slots in root table */
#define TABLSIZE    53 /* # of slots per table below the root */
#else
#define ROOTSIZE    40 /* initial # of slots in root table */
#define TABLSIZE    20 /* initial # of slots per table below the root */
#endif

#define MAXNEST 15 /* Max nesting of name scopes, used for sizing stacks */

#include <bu.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "acpiasm.h"
#include "acpiosd.h"
#include "aml.h"
#include "acpinmsp.h"
#include "amlscan.h"
#include "amlexec.h"
#include "amldsio.h"
#include "amlpriv.h"
#include "display.h"
#include "debuglvl.h"




/* Names built-in to interpreter, per Memphis build 1500
 *
 *  Initial values are currently supported only for types String and Number.
 *  To avoid type punning, both are specified as strings in this table.
 */
static struct InitVal {
    char        *pcName;
    NsType      iType;
    char        *pcVal;
} asPreDefinedNames[] = {
    {"_GPE", DefAny},
    {"_PR_", DefAny},
    {"_SB_", DefAny},
    {"_SI_", DefAny},
    {"_TZ_", DefAny},
    {"_REV", Number, "2"},
    {"_OS_", String, "Intel AML interpreter"},
    {"_GL_", Mutex},
    {(char *)0, Any}
};




/* Elements of aiNsProperties are bit significant
 *  and should be one-to-one with values of NsType in acpinmsp.h
 */
#define NEWSCOPE    1   /* a definition of this type opens a name scope */
#define LOCAL       2   /* suppress search of enclosing scopes */

static int aiNsProperties[] = { /* properties of types */
    0,                      /* Any              */
    0,                      /* Number           */
    0,                      /* String           */
    0,                      /* Buffer           */
    LOCAL,              /* Package          */
    0,                      /* FieldUnit        */
    NEWSCOPE | LOCAL,   /* Device           */
    LOCAL,              /* Event                */
    NEWSCOPE | LOCAL,   /* Method           */
    LOCAL,              /* Mutex                */
    LOCAL,              /* Region           */
    NEWSCOPE | LOCAL,   /* Power                */
    NEWSCOPE | LOCAL,   /* Processor        */
    NEWSCOPE | LOCAL,   /* Thermal          */
    0,                      /* Alias                */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,                      /* DefField         */
    0,                      /* BankField        */
    0,                      /* IndexField       */
    0,                      /* DefFieldDefn */
    0,                      /* BankFieldDefn    */
    0,                      /* IndexFieldDefn   */
    0,                      /* If                   */
    0,                      /* Else             */
    0,                      /* While                */
    NEWSCOPE,           /* Scope                */
    LOCAL,              /* DefAny           */
    0                       /* Lvalue           */
};

char acBadType[] = "ERROR: unused type encoding found in table";

/* Elements of apcNsTypeNames should be
 *  one-to-one with values of NsType in acpinmsp.h
 */

/* The type Any is used as a "don't care" when searching; when stored in a
 *  table it really means that we have thus far seen no evidence to indicate
 *  what type is actually going to be stored for this entry.
 */
char *apcNsTypeNames[] = { /* printable names of types */
    "Unknown",
    "Number",
    "String",
    "Buffer",
    "Package",
    "FieldUnit",
    "Device",
    "Event",
    "Method",
    "Mutex",
    "Region",
    "Power",
    "Processor",
    "Thermal",
    "Alias",
    acBadType, acBadType, acBadType, acBadType, acBadType,
    acBadType, acBadType, acBadType, acBadType, acBadType,
    "DefField",
    "BankField",
    "IndexField",
    "DefFieldDefn",
    "BankFieldDefn",
    "IndexFieldDefn",
    "If",
    "Else",
    "While",
    "Scope",
    "ERROR: DefAny found in table", /* should never happen */
    "ERROR: Lvalue found in table"  /* should never happen */
};

/* typedef nte (name table entry) is private to acpinmsp.c to avoid global
 *  impact in the event of changes to it.  The externally-known type NsHandle
 *  is actually an (nte *).  If an external program needs to extract a field
 *  from the nte, it should use an access function defined in acpinmsp.c
 *
 *  If you need an access function not provided herein, add it to this module
 *  rather than exporting the nte typedef.
 *
 *  (nte *) are actually used in two different and not entirely compatible
 *  ways: as pointer to an individual nte and as pointer to an entire name
 *  table (which is an array of nte, sometimes referred to as a scope).  In
 *  the latter case, the specific nte pointed to may be unused; however its
 *  nParentScope member will be valid.
 */
typedef struct nte
{
    DWORD           dNameSeg;       /* name segment, always 4 chars per ACPI spec.
                                     * dNameSeg must be the first field in the nte
                                     * -- see the iIsNsHandle macro in acpinmsp.h
                                     */
    struct nte *nChildScope;        /* next level of names */
    struct nte *nParentScope;       /* previous level of names */
    NsType      iNtType;            /* type associated with name */
    void          *pVal;            /* pointer to value */
} nte;

#define NOTFOUND (nte *)0

#ifndef USE_HASHING
/* If USE_HASHING is not set, there will be an (nte *) prefix to each name
 * table, containing either a NULL pointer or the address of the next array
 * of nte's in the scope.
 */
#define NEXTSEG(nNT) ((nte **)nNT)[-1]
#endif

static nte *psRoot = (nte *)0;
static int iNsRootSize;             /* set from ROOTSIZE -- could potentially
                                     * support dynamic sizing of root NT
                                     */
static int iNsCurrentSize;          /* will be either ROOTSIZE or TABLSIZE
                                     * depending on whether the current scope
                                     * is the root
                                     */
/* local logfile for debugging */
#ifdef NSLOGFILE
static FILE *LogFile;
#endif

/* Stack of currently-open scopes, and pointer to top of that stack */
static struct
{
    nte *psScope;
    NsType iType;       /* Type of scope, typically the same as the type of
                             * its parent's entry (but not the same as the type
                             * of its parent's scope).
                             */
} sScopeStack[MAXNEST], *psCurrentScope;

#ifdef PLUMBER

#define MAX_STATIC_BLOCKS 10
static void **
appvStaticBlockList[MAX_STATIC_BLOCKS];
static int iNumStaticBlocks = 0;

/****************************************************************************
 *  FUNCTION:       void vRegisterStaticBlockPtr(void **ppvBP)
 *
 *  PARAMETERS:     void    **ppvBP Addr of static pointer to be registered
 *
 *  DESCRIPTION:    If compiled with bu_plumr.h, add the pointer whose address
 *                      is passed to the registry.  vMarkStaticBlocks() will then
 *                      "mark" each block pointed to by a registered pointer.
 *
 ***************************************************************************/

void
vRegisterStaticBlockPtr(void **ppvBP)
{
    if (iNumStaticBlocks < MAX_STATIC_BLOCKS)
        appvStaticBlockList[iNumStaticBlocks++] = (void **)ppvBP;

    else
    {
        fprintf_bu(iLstFileHandle, LOGFILE,
                        "vRegisterStaticBlockPtr: too many static blocks");
        _dKinc_warning("0001", PRINT, __LINE__, __FILE__, iLstFileHandle, LOGFILE);
    }
}

/****************************************************************************
 *  FUNCTION:       void vMarkStaticBlocks(int *piCount)
 *
 *  PARAMETERS:     int *piCount        Count of blocks marked
 *
 *  DESCRIPTION:    "Mark" all blocks pointed to by registered static pointers
 *
 ***************************************************************************/
void
vMarkStaticBlocks(int *piCount)
{
    int i;

    for ( i = 0 ; i < iNumStaticBlocks ; ++i )
    {
        ++*piCount;
        vMarkBlock(*appvStaticBlockList[i]);
    }
}

#endif /* PLUMBER */

/****************************************************************************
 *  FUNCTION:       static nte *nAllocNT(int iSize)
 *
 *  PARAMETERS:     int iSize       # of nte in table
 *
 *  DESCRIPTION:    Allocate an array of nte, including prepended link space
 *
 *  RETURN:         The address of the first nte in the array, or NULL
 *
 ***************************************************************************/
static nte *
nAllocNT(int iSize)
{
    nte *nNewNT;
    size_t stAllocSize = (size_t)iSize * sizeof(nte);

#ifndef USE_HASHING
    /* Allow room for link to appendage */
    stAllocSize += sizeof(nte *);
#endif

    nNewNT = (nte *) OsdCallocate (stAllocSize, 1);

#ifndef USE_HASHING
    if (nNewNT)
        /* Move past the appendage pointer */
        nNewNT = (nte *)(((BYTE *)nNewNT) + sizeof(nte *));
#endif

    return nNewNT;
}

/****************************************************************************
 *  FUNCTION:       static void vNsPushCurrentScope(nte *nNewScope, ...)
 *
 *  PARAMETERS:     nte *nNewScope,             name to be made current
 *                      NsType iType,                   type of frame being pushed
 *
 *  DESCRIPTION:    Push the current scope on the scope stack, and make the
 *                      passed nte current.
 *
 ***************************************************************************/
static void
vNsPushCurrentScope(
    nte *nNewScope,                         /* name to be made current */
    NsType iType)                               /* type of frame being pushed */
{
#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "vNsPushCurrentScope");
#endif

    if ((nte *)0 == nNewScope)
        vKFatalError("0002", ("vNsPushCurrentScope: null scope passed"));

    if (OUTRANGE(iType, apcNsTypeNames) || acBadType == apcNsTypeNames[iType])
    {
        fprintf_bu(iLstFileHandle, LOGFILE,
                        "vNsPushCurrentScope: type code %d out of range", iType);
        _dKinc_warning("0003", PRINT, __LINE__, __FILE__, iLstFileHandle, LOGFILE);
    }

    if (psCurrentScope < &sScopeStack[MAXNEST-1])   /* check for overflow */
    {
        ++psCurrentScope;
        psCurrentScope->psScope = nNewScope;
        psCurrentScope->iType = iType;
        if (psCurrentScope->psScope == psRoot)
            iNsCurrentSize = iNsRootSize;
        else
            iNsCurrentSize = TABLSIZE;
    }
    else
    {
        vKFatalError("0004", ("Scope stack overflow"));
    }
}

/****************************************************************************
 *  FUNCTION:       void vNsPushMethodScope(NsHandle nNewScope)
 *
 *  PARAMETERS:     NsHandle nNewScope,             name to be made current
 *
 *  DESCRIPTION:    Push the current scope on the scope stack, and make the
 *                      passed nte current.
 *
 ***************************************************************************/
void
vNsPushMethodScope(NsHandle nNewScope)
{
#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "vNsPushMethodScope");
#endif

    if ((nte *)0 == nNewScope || (nte *)0 == ((nte *)nNewScope)->nChildScope)
        vKFatalError("0005", ("vNsPushMethodScope: null scope passed"));

    if (psCurrentScope < &sScopeStack[MAXNEST-1])   /* check for overflow */
        vNsPushCurrentScope(((nte *)nNewScope)->nChildScope, Method);
    else
        vKFatalError("0006", ("Scope stack overflow"));
}

/*ARGSUSED*/
void
vNoMsg(char * pcMessage)
{
#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "vNoMsg");
#endif
}

/****************************************************************************
A* FUNCTION:        char * pcInternalizeName(char *pcDottedName)
 *
 *  PARAMETERS:     char *pcDottedName - external representation of name
 *
 *  RETURN:         Internal representation of name
 *
 *  DESCRIPTION:    Convert an external representation (e.g. "\_PR_.CPU0")
 *                      to internal form (e.g. 5c 2f 02 5f 50 52 5f 43 50 55 30)
 *
 *  ALLOCATION:
A* Reference   Size              Pool  Owner                Description
A* pcIN{sl}    iINsiz{sl:HWM}    bu    pcInternalizeName    Internal name
 *
 ****************************************************************************/
static char *
pcInternalizeName(char *pcDottedName)
{
    char *pcResult;
    size_t i;
    static char *pcIN = (char *)0;
    static size_t iINsiz = 0;

#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "pcInternalizeName");
#endif

    i = strlen(pcDottedName++) / 5;

    /* required length is 4 bytes per segment, plus 1 each for RootPrefix,
     * MultiNamePrefixOp, segment count, trailing null (which is not really
     * needed, but no there's harm in putting it there)
     */
    if (iINsiz < 4 * i + 4)
    {
        if (pcIN != (char *)0)
            OsdFree (pcIN);
        else
            vRegisterStaticBlockPtr(&pcIN);
        pcIN = OsdCallocate (1, 4 * i + 4);
        if ((char *)0 == pcIN)
            vKFatalError("0007", ("pcInternalizeName: allocation failure"));
        iINsiz = 4 * i + 4;
    }

    strcpy(pcIN, "\\/");
    for (pcIN[2] = i, pcResult = &pcIN[3] ; i ; --i )
    {
        strncpy(pcResult, pcDottedName, 4);
        pcResult += 4;
        pcDottedName += 5;
    }
    *pcResult = '\0';
/* fprintf(fLstFile, "pcInternalizeName: returning %p => %s\n", pcIN, pcIN); */
    return pcIN;
}

/****************************************************************************
A* FUNCTION:        int iAcpiExecuteMethod(pcMethodName, ppsReturnValue, ...)
 *
 *  PARAMETERS:     char *pcMethodName      name of method to execute
 *
 *                  OBJECT_DESCRIPTOR       where to put method's return
 *                      **ppsReturnValue    value (if any).
 *                                          ppsReturnValue must not be
 *                                          passed in as NULL because
 *                                          *ppsReturnValue will always
 *                                          be set (to NULL if there is
 *                                          no return value).
 *
 *                  OBJECT_DESCRIPTOR 
 *                      **ppsParams         list of parameters to pass to
 *                                          method, terminated by NULL.
 *                                          ppsParams itself may be NULL
 *                                          if no parameters are being
 *                                          passed.
 *
 *  RETURN:         E_OK or E_ERROR
 *
 *  DESCRIPTION:    Find and execute the requested method passing the given
 *                      parameters
 *
 *  ALLOCATION:
A* Reference       Size                 Pool Owner       Description
A* *ppsReturnValue s(OBJECT_DESCRIPTOR) bu   CALLER      returned value
 *
 ****************************************************************************/
int
AcpiExecuteMethod (char * pcMethodName, OBJECT_DESCRIPTOR **ppsReturnValue,
                    OBJECT_DESCRIPTOR **ppsParams)
{
    nte     *hMethod;
    int     iRv;

#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "iAcpiExecuteMethod");
#endif

BREAKPOINT3;

    if ((OBJECT_DESCRIPTOR **)0 != ppsReturnValue)
        *ppsReturnValue = (OBJECT_DESCRIPTOR *)0;

    if ((nte *)0 == psRoot)
    {
        /* If the name space has not been initialized, the Method has surely
         * not been defined and there is nothing to execute.
         */
        pcWhy = "Name space not initialized";
        return E_ERROR;
    }

    if (pcMethodName[0] != '\\' || pcMethodName[1] != '/')
        pcMethodName = pcInternalizeName(pcMethodName);

/* See comment near top of file re significance of FETCH_VALUES */
#ifdef FETCH_VALUES
    hMethod = (nte *)hNsEnter(pcMethodName, Any, Exec);
#else
    hMethod = (nte *)hNsEnter(pcMethodName, Method, Exec);
#endif

    if (NOTFOUND == hMethod)
    {
        pcWhy = "Method not found";
        return E_ERROR;
    }

#ifdef FETCH_VALUES
    if (iNsValType(hMethod) == Method)
    {
        /* Name found is in fact a Method */
        if (debug_level() > 0)
        {
            LineSet(55, Exec);
            fprintf_bu(iLstFileHandle, LOGFILE,
                    "[%s hMethod %p pVal %p ",
                    pcMethodName, hMethod, hMethod->pVal);

            if (hMethod->pVal)
                fprintf_bu(iLstFileHandle, LOGFILE,
                        "iOffset %x lLength %lx]",
                        ((meth *)hMethod->pVal)->iOffset + 1,
                        ((meth *)hMethod->pVal)->lLength - 1);
            else
                fprintf_bu(iLstFileHandle, LOGFILE, "*Undefined*]");
        }
#endif

        /* Here if not FETCH_VALUES (and hence only Method was looked for), or
         * FETCH_VALUES and the name found was in fact a Method.  In either
         * case, set the current scope to that of the Method, and execute it.
         */
        if (!hMethod->pVal)
        {
            pcWhy = "Method is undefined";
            return E_ERROR;
        }
        if (Trace & TraceNames)
            fprintf_bu(iLstFileHandle, LOGFILE, "Set scope %s ",
                          pcNsFullyQualifiedName(hMethod->nChildScope));
        psCurrentScope = &sScopeStack[0];
        vNsPushCurrentScope(hMethod->nChildScope, Method);
        if (Trace & TraceNames)
            fprintf_bu(iLstFileHandle, LOGFILE, "Exec Method %s ",
                          pcNsFullyQualifiedName(hMethod));
        vClearPkgStack();
        iObjStackTop = 0;                                           /* Clear object stack */
        iRv = iAmlExec(((meth *)hMethod->pVal)->iOffset + 1,
                            ((meth *)hMethod->pVal)->lLength - 1,
                            ppsParams);

        if (debug_level() > 0 && iPkgNested())
        {
            fprintf_bu(iLstFileHandle, LOGFILE,
                            "Package stack not empty at method exit");
            _dKinc_info("0008", PACRLF, __LINE__, __FILE__, iLstFileHandle, LOGFILE);
        }

        if (iGetMethodDepth() > -1)
        {
            fprintf_bu(iLstFileHandle, LOGFILE,
                            "Method stack not empty at method exit");
            _dKinc_error("0009", PACRLF, __LINE__, __FILE__, iLstFileHandle, LOGFILE);
        }

        if (debug_level() > 0 && iObjStackTop)
        {
            int iSaveTrace = Trace;

            fprintf_bu(iLstFileHandle, LOGFILE,
                            "Object stack not empty at method exit");
            _dKinc_info("0010", PACRLF, __LINE__, __FILE__, iLstFileHandle, LOGFILE);
            Trace |= TraceExec;         /* enable output from vDumpStack */
            vDumpStack(Exec, "Remaining Object Stack entries", -1, "");
            Trace = iSaveTrace;
        }

#ifdef FETCH_VALUES
    }
    else
    {
        /* Here if FETCH_VALUES and the name found was not a Method.
         * Return its value.
         */
        OBJECT_DESCRIPTOR *pOD;

        if (debug_level() > 0)
        {
            fprintf_bu(iLstFileHandle, LOGFILE, "Value: ");
            vNsDumpEntry(hMethod, LOGFILE);
        }
        pOD = NEW(OBJECT_DESCRIPTOR);
        if (pOD)
        {
            /* Construct a descriptor pointing to the name */
            pOD->sLvalue.bValTyp = (BYTE)Lvalue;
            pOD->sLvalue.bOpCode = (BYTE)NameOp;
            pOD->sLvalue.pvRef = (void *)hMethod;

            /* Put it on the stack, and use iGetRvalue() to get the value.
             * Note that iObjStackTop points to the top valid entry, not to
             * the first unused position.
             */
            vDeleteObject((OBJECT_DESCRIPTOR **)&apObjStack[iObjStackTop]);
            apObjStack[iObjStackTop] = (void *)pOD;
            iRv = iGetRvalue((OBJECT_DESCRIPTOR **)&apObjStack[iObjStackTop]);

            /* If iGetRvalue() succeeded, treat the top stack entry as
             * a return value.
             */
            if (S_SUCCESS == iRv)
                iRv = S_RETURN;
        }
        else
        {
            pcWhy = "iAcpiExecuteMethod: Descriptor Allocation Failure";
            iRv = S_ERROR;
        }
    }
#endif


BREAKPOINT3;

    if (S_ERROR == iRv)
        return E_ERROR;
    else
    {
        /* If the Method returned a value and the caller provided a place
         * to store a returned value, pass back the returned value.
         */
        if (S_RETURN == iRv)
            if ((OBJECT_DESCRIPTOR **)0 != ppsReturnValue)
                *ppsReturnValue = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop];
            else
                DELETE(apObjStack[iObjStackTop]);
        return E_OK;
    }
}   /* iAcpiExecuteMethod */

/****************************************************************************
 *  FUNCTION:       int iAcpiLoadNameSpace (void)
 *
 *  PARAMETERS:     none
 *
 *  RETURN:         E_OK or E_ERROR
 *
 *  DESCRIPTION:    Expands namespace, typically in response to a docking event
 *
 ****************************************************************************/
int
iAcpiLoadNameSpace (void)
{
#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "iAcpiLoadNameSpace");
#endif

    if ((nte *)0 == psRoot)
        return E_ERROR;
    return (E_OK);
}

/****************************************************************************
 *  FUNCTION:       int iAcpiUnloadNameSpace (void)
 *
 *  PARAMETERS:     none
 *
 *  RETURN:         E_OK or E_ERROR
 *
 *  DESCRIPTION:    Contracts namespace, typically in response to an undocking
 *                      event
 *
 ****************************************************************************/
int
iAcipUnloadNameSpace (void)
{
#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "iAcipUnloadNameSpace");
#endif

    if ((nte *)0 == psRoot)
        return E_ERROR;
    return (E_OK);
}

/****************************************************************************
 *  FUNCTION:       static int iNsOpensScope(NsType iType)
 *
 *  PARAMETERS:     NsType iType
 *
 *  RETURN:         NEWSCOPE if the passed type "opens a name scope" according
 *                      to the ACPI specification, else 0
 *
 ***************************************************************************/
static int
iNsOpensScope(NsType iType)
{
#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "iNsOpensScope");
#endif

    if (OUTRANGE(iType, aiNsProperties))
    {
        fprintf_bu(iLstFileHandle, LOGFILE,
                        "iNsOpensScope: type code %d out of range", iType);
        _dKinc_warning("0011", PRINT, __LINE__, __FILE__, iLstFileHandle, LOGFILE);
        return 0;
    }
    return aiNsProperties[iType] & NEWSCOPE;
}

/****************************************************************************
 *  FUNCTION:       static int iNsLocal(NsType iType)
 *
 *  PARAMETERS:     NsType iType
 *
 *  RETURN:         LOCAL if names must be found locally in objects of the
 *                              passed type
 *                      0       if enclosing scopes should be searched
 *
 ***************************************************************************/
static int
iNsLocal(NsType iType)
{
#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "iNsLocal");
#endif

    if (OUTRANGE(iType, aiNsProperties))
    {
        fprintf_bu(iLstFileHandle, LOGFILE,
                        "iNsLocal: type code %d out of range", iType);
        _dKinc_warning("0012", PRINT, __LINE__, __FILE__, iLstFileHandle, LOGFILE);
         return 0;
    }
    return aiNsProperties[iType] & LOCAL;
}

/****************************************************************************
 *  FUNCTION:       NsType iNsValType(NsHandle h)
 *
 *  PARAMETERS:     NsHandle h      Handle of nte to be examined
 *
 *  RETURN:         iType field from nte whose handle is passed
 *
 ***************************************************************************/
NsType
iNsValType(NsHandle h)
{
#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "iNsValType");
#endif

    if ((NsHandle)0 == h)
    {
        fprintf_bu(iLstFileHandle, LOGFILE, "iNsValType: Null handle");
        _dKinc_warning("0013", PRINT, __LINE__, __FILE__, iLstFileHandle, LOGFILE);
        return Any;
    }

    return ((nte *)h)->iNtType;
}

/****************************************************************************
 *  FUNCTION:       void * pvNsValPtr(NsHandle h)
 *
 *  PARAMETERS:     NsHandle h      Handle of nte to be examined
 *
 *  RETURN:         pVal field from nte whose handle is passed
 *
 ***************************************************************************/
void *
pvNsValPtr(NsHandle h)
{
#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "pvNsValPtr");
#endif

    if ((NsHandle)0 == h)
    {
        fprintf_bu(iLstFileHandle, LOGFILE, "pvNsValPtr: Null handle");
        _dKinc_warning("0014", PRINT, __LINE__, __FILE__, iLstFileHandle, LOGFILE);
        return (void *)0;
    }
    return ((nte *)h)->pVal;
}

/* XXX - Absent recursion, should not need prototype for
 *  XXX - a locally-defined function; try to reorder definitions
 */
static char * pcNsNameOfScope(nte *nLook);

/****************************************************************************
 *  FUNCTION:       static nte * nsSearchTable(char *pcNamSeg, nte *nNt, ...)
 *
 *  PARAMETERS:     char    *pcNamSeg   name segment to find or insert
 *                      nte *nNt            name table to search
 *                      int  iTableSize # of slots in table,
 *                                                  must be prime if USE_HASHING
 *                      OpMode iLE          Add names only in Load mode
 *                      NsType iType        Type associated with name
 *
 *  RETURN:         pointer to found or added nte, or NOTFOUND
 *
 *  DESCRIPTION:    Search for a name segment in a single name table,
 *                      optionally adding it if it is not found.  If the passed
 *                      iType is not Any and the type previously stored in the
 *                      entry was Any (i.e. unknown), update the stored type.
 *
 ***************************************************************************/
static nte *
nsSearchTable(
    char    *pcNamSeg,      /* name segment to find or insert */
    nte *nNt,               /* name table to search */
    int  iTableSize,    /* # of slots in table, must be prime if USE_HASHING */
    OpMode iLE,             /* Add names only if in Load mode */
    NsType iType)           /* Type associated with name */
{
    DWORD ulHash;   /* hashed value of name */
    WORD    uiPos;  /* position in table */
    int iTries; /* number of positions not yet searched */

#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "nsSearchTable");
#endif

    vCheckTrash("enter nsSearchTable");

    if ((nte *)0 == nNt)
        vKFatalError("0015", ("nsSearchTable: null scope passed"));

    if (Trace & TraceNames)
        fprintf_bu(iLstFileHandle, LOGFILE,
                "nsSearchTable: search %s [%p] for %4.4s ... ",
                pcNsNameOfScope(nNt), nNt, pcNamSeg);

    if (!NcOK((int)pcNamSeg[0]) || !NcOK((int)pcNamSeg[1])
     || !NcOK((int)pcNamSeg[2]) || !NcOK((int)pcNamSeg[3]))
    {
        sprintf(acWhyBuf, "*** bad name %08lx *** ", *(DWORD *)pcNamSeg);
        pcWhy = acWhyBuf;
        fprintf_bu(iLstFileHandle, LOGFILE, pcWhy)
        vCheckTrash("leave nsSearchTable BADNAME");
        return NOTFOUND;
    }

    if (nNt == psRoot && iTableSize != ROOTSIZE
     || nNt != psRoot && iTableSize != TABLSIZE)
    {
        fprintf_bu(iLstFileHandle, LOGFILE, " *** NAME TABLE SIZE ERROR *** ");
        pcWhy = "*** NAME TABLE SIZE ERROR ***";
        vCheckTrash("leave nsSearchTable BADSIZE");
        return NOTFOUND;
    }

    /* If USE_HASHING is turned on, name tables will be hashed; see Knuth's
     * _Sorting and Searching_ (TAOCP vol. 3) for a general presentation of
     * hashing schemes.  Hashing should achieve better performance than linear
     * searching but will cause table dumps to display no evident ordering.
     *
     * If USE_HASHING is not turned on:
     *      Name tables will built (and subsequently dumped) in the
     *          order in which the names are encountered during Load;
     *      All searching will be linear;
     *      If a table overflows an additional segment will be added .
     */
#ifdef USE_HASHING
    /* Since all name segments are exactly 4 characters,
     * just use those bits as the hash value.
     */
    ulHash = *(DWORD *)pcNamSeg;
    uiPos = (WORD)(ulHash % (DWORD)iTableSize);
#else
    /* start linear search at top of table */
    ulHash = (DWORD)0;
    uiPos = (WORD)ulHash;
#endif

#ifdef NSLOGFILE
    fprintf(LogFile, "search %p size %d\n", nNt, iTableSize);
#endif
    /* Search for name in table, starting at uiPos.  Stop searching upon
     * finding an unused entry or after examining all entries in the table.
     *
     * Moving to the "next" entry is done at the bottom of the loop instead
     * of in the iteration expression because the method used depends on
     * whether or not USE_HASHING is in effect.
     */
    for (iTries = iTableSize ; iTries && 0 != nNt[uiPos].dNameSeg; --iTries)
    {
        vCheckTrash("top of nsSearchTable loop");
        if (nNt[uiPos].dNameSeg == *(DWORD *)pcNamSeg)
        {
            /* Found matching entry.  Capture type if appropriate before
             * returning the entry.
             */

            /* The DefFieldDefn and BankFieldDefn cases are actually
             * looking up the Region in which the field will be defined
             */
            if (DefFieldDefn == iType || BankFieldDefn == iType)
                iType = Region;

            /* Scope, DefAny, and IndexFieldDefn are bogus "types" which do
             * not actually have anything to do with the type of the name
             * being looked up.  For any other value of iType, if the type
             * stored in the entry is Any (i.e. unknown), save the actual type.
             */
            if (iType != Scope && iType != DefAny
             && iType != IndexFieldDefn && nNt[uiPos].iNtType == Any)
                nNt[uiPos].iNtType = iType;

            if (Trace & TraceNames)
                fprintf_bu(iLstFileHandle, LOGFILE, "found at %p", &nNt[uiPos]);
            vCheckTrash("leave nsSearchTable FOUND");
            return &nNt[uiPos];
        }

#ifdef USE_HASHING
        /* Found position occupied by a different name, decide where to look
         * next.  The value added must be relatively prime to the table size,
         * which is most easily assured by requiring the table size to be a
         * prime number.
         *
         * Use the second character of the name as the rehash value since the
         * first character will often be '_'
         */
        uiPos = (uiPos + pcNamSeg[1]) % iTableSize;
#else
        if (1 == iTries && NEXTSEG(nNt) != (nte *)0)
        {
            /* Just examined last slot, but table has an appendage.
             * All appendages, even to the root NT, contain TABLSIZE entries.
             */
            nNt = NEXTSEG(nNt);
            uiPos = 0;
            iTries += TABLSIZE;
        }
        else
            ++uiPos;
#endif
    }

    /* Name not found.  Before adding it or giving up, ACPI scope rules
     * require searching enclosing scopes in cases identified by iNsLocal()
     */

    /* nNt[0] will be an unused entry if the table being searched is empty,
     * and will often be unused even in a non-empty table if USE_HASHING is
     * in effect; however its nParentScope member will have been filled in
     * when the table was allocated (unless it is the root name table).
     */
    if (!iNsLocal(iType) && nNt[0].nParentScope != (nte *)0)
    {
        int iSize = (nNt[0].nParentScope == psRoot) ? iNsRootSize : iTableSize;
        nte *rv;

        if (Trace & TraceNames)
        {
            fprintf_bu(iLstFileHandle, LOGFILE, "searching parent");
            iIncIndent();
        }
        vCheckTrash("before recursive nsSearchTable");
        rv = nsSearchTable(pcNamSeg, nNt[0].nParentScope, iSize, Exec, Any);
        vCheckTrash("after  recursive nsSearchTable");
        if ((Trace & TraceNames) && (Load1 != iLE))
        {
            iDecIndent();
            fprintf_bu(iLstFileHandle, LOGFILE, "\n");
        }
        if (rv != NOTFOUND)
        {
            vCheckTrash("leave nsSearchTable FOUND in parent");
            return rv;
        }
    }
    else
    {
        if (Trace & TraceNames)
            if ((nte *)0 == nNt[0].nParentScope)
                fprintf_bu(iLstFileHandle, LOGFILE, "no parent, ");
            else if (iNsLocal(iType))
                fprintf_bu(iLstFileHandle, LOGFILE,
                        "%s is local, ", apcNsTypeNames[iType]);
    }

    /* If in Load mode and table is not full, add the not-found name to the
     * table.
     */
#ifndef USE_HASHING
    if ((Load1 == iLE || Load == iLE) && 0 == iTries)
    {
        nte *nPS = nNt[0].nParentScope;

        /* Allocate and chain an appendage to the filled table */
        NEXTSEG(nNt) = nAllocNT(TABLSIZE);
        if (!NEXTSEG(nNt))
            vKFatalError("0016", ("Name Table appendage allocation failure"));
        nNt = NEXTSEG(nNt);
        nNt[0].nParentScope = nPS;
        uiPos = 0;
        iTries += TABLSIZE;
    }
#endif
    if ((Load1 == iLE || Load == iLE) && iTries > 0)
    {
        vCheckTrash("nsSearchTable about to add");
        nNt[uiPos].dNameSeg = *(DWORD *)pcNamSeg;
        nNt[uiPos].nParentScope = nNt[0].nParentScope;
        vCheckTrash("nsSearchTable added name");

        /* If adding a name with unknown type, or having to add the region in
         * order to define fields in it, we have an improper forward reference
         */
        if (Any == iType || DefFieldDefn == iType || BankFieldDefn == iType)
        {
            fprintf_bu(iLstFileHandle != NO_LOG_HANDLE ? iLstFileHandle : GetMasterLogHandle(),
                LOGFILE | SCREEN, "Unknown reference in name space \"%4.4s\"",
                    pcNamSeg);
            _dKinc_error("0017", PRINT, __LINE__, __FILE__,
                iLstFileHandle != NO_LOG_HANDLE ? iLstFileHandle : GetMasterLogHandle(),
                LOGFILE | SCREEN);
            LineSet(0, iLE);        /* start new line in listing */
        }

        /* The DefFieldDefn and BankFieldDefn cases are actually
         * looking up the Region in which the field will be defined
         */
        if (DefFieldDefn == iType || BankFieldDefn == iType)
            iType = Region;

        /* Scope, DefAny, and IndexFieldDefn are bogus "types" which do
         * not actually have anything to do with the type of the name
         * being looked up.  Save any other value of iType as the type of
         * the entry.
         */
        if (iType != Scope && iType != DefAny && iType != IndexFieldDefn)
        {
            nNt[uiPos].iNtType = iType;
            vCheckTrashA("nsSearchTable added type",
                        &nNt[uiPos].dNameSeg, nNt[uiPos].dNameSeg, ulHash,
                        &nNt[uiPos].iNtType, nNt[uiPos].iNtType, iType, (void *)nNt);
        }

        if (Trace & TraceNames)
            fprintf_bu(iLstFileHandle, LOGFILE,
                    "added to %p at %p", nNt, &nNt[uiPos]);
        vCheckTrash("leave nsSearchTable ADDED");
        return &nNt[uiPos];
    }   /* if ((Load1 == iLE || Load == iLE) && iTries > 0) */

    if (Trace & TraceNames)
        fprintf_bu(iLstFileHandle, LOGFILE, "not found in %p ", nNt);
    vCheckTrash("leave nsSearchTable NOTFOUND");
    return NOTFOUND;
}   /* nsSearchTable */

/****************************************************************************
A* FUNCTION:        void vNsSetup()
 *
 *  PARAMETERS:     none
 *
 *  DESCRIPTION:    Allocate and initialize the root name table
 *
 *  ALLOCATION:
A* Reference      Size                 Pool  Owner       Description
A* psRoot         iNsRootSize*s(nte)   bu    acpinmsp    Root Name Table
A* nte.pVal       s(OBJECT_DESCRIPTOR) bu    acpinmsp    initialized value
A* nte.pVal->pbString   varies         bu    acpinmsp    string value
 *
 ***************************************************************************/
void
vNsSetup(void)
{
    struct InitVal *psNT;

#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "vNsSetup");
#endif

    /* psRoot is initially NULL, so a non-NULL value indicates
     * that vNsSetup() has already been called; just return.
     */
    if (psRoot)
        return;

    iNsCurrentSize = iNsRootSize = ROOTSIZE;
    psRoot = nAllocNT(iNsRootSize);
    if ((nte *)0 == psRoot)
        vKFatalError("0018", ("root name table allocation failure"));

    /* Push the root name table on the scope stack */
    sScopeStack[0].psScope = psRoot;
    sScopeStack[0].iType = Any;
    psCurrentScope = &sScopeStack[0];
#ifdef NSLOGFILE
    LogFile = fopen("ns.log", "wtc");
    fprintf(LogFile, "root = %08x size %d\n", psRoot, iNsRootSize);
#endif

    /* Enter the pre-defined names in the name table */
    for (psNT = asPreDefinedNames ; psNT->pcName ; ++psNT)
    {
        NsHandle hN
            = hNsEnter(psNT->pcName, psNT->iType, Load);

        /* if name entered successfully
         *  && its entry in asPreDefinedNames[] specifies an initial value
         */
        if (hN && psNT->pcVal)
        {
            /* Entry requests an initial value, allocate a descriptor for it. */
            OBJECT_DESCRIPTOR *pOD = NEW(OBJECT_DESCRIPTOR);

            if ((OBJECT_DESCRIPTOR *)0 == pOD)
                vKFatalError("0019", ("Initial value descriptor allocation failure"));

            pOD->bValTyp = (BYTE)psNT->iType;

            /* Convert value string from table entry to internal representation.
             * Only types actually used for initial values are implemented here.
             */
            switch (psNT->iType)
            {
                case Number:
                    pOD->sNumber.dNumber = (DWORD)atol(psNT->pcVal);
                    break;

                case String:
                    pOD->sString.wStrLen = (WORD)strlen(psNT->pcVal);
                    /* XXX - if this malloc_bu() causes a garbage collection pass,
                     * XXX - pOD will get deleted since no NT points to it yet.
                     * XXX - This "should not happen" during initialization.
                     */
                    pOD->sString.pbString = OsdAllocate ((size_t)(pOD->sString.wStrLen + 1));
                    if ((BYTE *)0 == pOD->sString.pbString)
                        vKFatalError("0020", ("Initial value string allocation failure"));
                    strcpy((char *)pOD->sString.pbString, psNT->pcVal);
                    break;

                default:
                    DELETE(pOD);
                    continue;
            }
            /* Store pointer to value descriptor in nte */
            vNsSetValue(hN, pOD, pOD->bValTyp);
        }
    }
#ifdef PLUMBER
    vRegisterMarkingFunction(iNsMarkNS);
#endif
}

/****************************************************************************
 *  FUNCTION:       int iNsPopCurrent(NsType iType)
 *
 *  PARAMETERS:     NsType iType    The type of frame to be found
 *
 *  DESCRIPTION:    Pop the scope stack until a frame of the requested type
 *                      is found.
 *
 *  RETURN:         Count of frames popped.  If no frame of the requested type
 *                      was found, the count is returned as a negative number and
 *                      the scope stack is emptied (which sets the current scope
 *                      to the root).  If the scope stack was empty at entry, the
 *                      function is a no-op and returns 0.
 *
 ***************************************************************************/
int
iNsPopCurrent(NsType iType)
{
    int iCount = 0;

#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "iNsPopCurrent");
#endif

    if (OUTRANGE(iType, apcNsTypeNames) || acBadType == apcNsTypeNames[iType])
    {
        fprintf_bu(iLstFileHandle, LOGFILE,
                        "iNsPopCurrent: type code %d out of range", iType);
        _dKinc_warning("0021", PRINT, __LINE__, __FILE__, iLstFileHandle, LOGFILE);
    }

    printfd_bu(TRACE_LEVEL,"Popping Scope till type (%i) is found\n", iType);

    while (psCurrentScope > &sScopeStack[0])
    {
        --psCurrentScope;
        ++iCount;
        printfd_bu(TRACE_LEVEL,"Popped %i ", (psCurrentScope+1)->iType);
        if (Any == iType || iType == (psCurrentScope+1)->iType)
        {
            printfd_bu(TRACE_LEVEL,"Found %i\n", iType);
            return iCount;
        }
    }

    printfd_bu(TRACE_LEVEL,"%i Not Found\n", iType);
    return -iCount;
}

/****************************************************************************
A* FUNCTION:        NsHandle hNsEnter(char *pcName, NsType iType, ...)
 *
 *  PARAMETERS:     char    *pcName name to be entered, in internal format
 *                                          as represented in the AML stream
 *                      NsType iType    type associated with name
 *                      OpMode iLE      Load => add name if not found
 *
 *  RETURN:         Handle to the nte for the passed name
 *
 *  DESCRIPTION:    Find or enter the passed name in the name space.
 *                      Log an error if name not found in Exec mode.
 *
 *  ALLOCATION:
A* Reference         Size                 Pool  Owner       Description
A* nte.nChildScope   TABLSIZE*s(nte)      bu    acpinmsp    Name Table
 *
 ***************************************************************************/
NsHandle
hNsEnter(
    char    *pcName,
    NsType iType,
    OpMode iLE)
{
    nte *nLook, *nThis;
    int iSize, iNumSeg;
    NsType iTTCF;           /* Type To Check For */

#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "hNsEnter");
#endif

    if ((nte *)0 == psRoot)
        /* If the name space has not been initialized:
         * -  In Pass1 of Load mode, we need to initialize it
         *    before trying to define a name.
         * -  In Exec mode, there are no names to be found.
         */
        if (Load1 == iLE)
            vNsSetup();
        else
            return NOTFOUND;

    if (Trace & TraceNames)
        fprintf_bu(iLstFileHandle, LOGFILE,
            " hNsEnter: %02x %02x %02x %02x %02x %02x ",
            pcName[0], pcName[1], pcName[2], pcName[3], pcName[4], pcName[5]);

    vCheckTrash("enter hNsEnter");

    /* DefFieldDefn and BankFieldDefn define fields in a Region */
    if (DefFieldDefn == iType || BankFieldDefn == iType)
        iTTCF = Region;
    else
        iTTCF = iType;

    /* Check for prefixes.  As represented in the AML stream, a Name consists
     * of an optional scope prefix followed by a segment part.
     *
     * If present, the scope prefix is either a RootPrefix (in which case the
     * name is fully qualified), or one or more ParentPrefixes (in which case
     * the name's scope is relative to the current scope).
     *
     * The segment part consists of:
     *  + a single 4-byte name segment, or
     *  + a DualNamePrefix followed by two 4-byte name segments, or
     *  + a MultiNamePrefixOp, followed by a byte indicating the number of
     *    segments and the segments themselves.
     */
    if (*pcName == RootPrefix)
    {
        /* Name is fully qualified, look in root NT */
        if (Trace & TraceNames)
            fprintf_bu(iLstFileHandle, LOGFILE, "root ");
        nLook = psRoot;
        iSize = iNsRootSize;
        ++pcName;   /* point to segment part */
    }
    else
    {
        char *pcOrigName = pcName;

        /* Name is relative to current scope, start there */
        nLook = psCurrentScope->psScope;
        iSize = iNsCurrentSize;

        while (*pcName == ParentPrefix)
        {
            if (Trace & TraceNames)
                fprintf_bu(iLstFileHandle, LOGFILE, "parent ");
            ++pcName;   /* point to segment part or next ParentPrefix */
            nLook = nLook->nParentScope;
            if (nLook == (nte *)0)
            {
                /* Scope has no parent */
                LineSet((int)strlen(pcOrigName) + 18, iLE);
                fprintf_bu(iLstFileHandle, LOGFILE, "*Too many ^ in <%s>*",
                        pcOrigName);
                _dKinc_error ("0022", PRINT, __LINE__, __FILE__, iLstFileHandle, LOGFILE);
                LineSet(0, iLE);
                vCheckTrash("leave hNsEnter NOTFOUND 1");
                return (NsHandle)NOTFOUND;
            }
        }
        if (nLook->nParentScope == (nte *)0)
            /* backed up all the way to the root */
            iSize = iNsRootSize;
    }

    if (*pcName == DualNamePrefix)
    {
        if (Trace & TraceNames)
            fprintf_bu(iLstFileHandle, LOGFILE, "dual ");
        iNumSeg = 2;
        ++pcName;   /* point to first segment */
    }
    else if (*pcName == MultiNamePrefixOp)
    {
        if (Trace & TraceNames)
            fprintf_bu(iLstFileHandle, LOGFILE, "multi %d ", pcName[1]);
        iNumSeg = (int)*(BYTE *)++pcName;
        ++pcName;   /* point to first segment */
    }
    else
        /* No Dual or Multi prefix, hence there is only one
         * segment and pcName is already pointing to it.
         */
        iNumSeg = 1;

    if (Trace & TraceNames)
        fprintf_bu(iLstFileHandle, LOGFILE, "seg = %d ", iNumSeg);
    while (iNumSeg-- && nLook)
    {
#if 0
        int SaveTrace = Trace;
        if (*(DWORD *)"LDN_" == *(DWORD *)pcName)
            Trace |= TraceNames;
        if (*(DWORD *)"LNKC" == *(DWORD *)pcName && Exec == iLE)
            Trace |= TraceNames;
#endif
        vCheckTrash("before nsSearchTable");
        /* Search for the current segment in the table where it should be.
         * Type is significant only at the last level.
         */
        nThis = nsSearchTable(pcName, nLook, iSize, iLE,
                                        iNumSeg == 0 ? iType : Any);
        vCheckTrash("after  nsSearchTable");
#if 0
        if (*(DWORD *)"LDN_" == *(DWORD *)pcName)
            Trace = SaveTrace;
#endif
        if (nThis == NOTFOUND)
        {
            if (Load1 == iLE || Load == iLE)
                vKFatalError("0023", ("\nname table overflow adding %4.4s to %s",
                        pcName, pcNsFullyQualifiedName(nLook)));
            else
            {
                fprintf_bu(iLstFileHandle, LOGFILE,
                        "name %4.4s not found in %s",
                        pcName, pcNsFullyQualifiedName(nLook));
                _dKinc_error ("0024", PACRLF, __LINE__, __FILE__, iLstFileHandle, LOGFILE);
            }
            vCheckTrash("leave hNsEnter NOTFOUND 2");
            return (NsHandle)NOTFOUND;
        }

        if (0 == iNumSeg                    /* if last segment                      */
         && iTTCF != Any                    /* and looking for a specific type  */
         && iTTCF != DefAny             /* which is not a phoney type           */
         && iTTCF != Scope              /*   "   "   "  "   "     "         */
         && iTTCF != IndexFieldDefn /*   "   "   "  "   "     "         */
         && nThis->iNtType != Any       /* and type of entry is known           */
         && nThis->iNtType != iTTCF)    /* and entry does not match request */
        {                                       /* complain.                                */
            fprintf_bu(iLstFileHandle, LOGFILE,
                    "Type mismatch, wanted %s, found %s\n",
                    apcNsTypeNames[iTTCF], apcNsTypeNames[nThis->iNtType]);
            _dKinc_warning("0025", PACRLF, __LINE__, __FILE__, iLstFileHandle, LOGFILE);
        }

        /* if last segment and not looking for a specific type, but type of
         * found entry is known, use that type to see if it opens a scope.
         */
        if (0 == iNumSeg && Any == iType)
            iType = nThis->iNtType;

        /* If there are more segments or the type implies that there should
         * be an enclosed scope, and the next scope has not been allocated ...
         */
        if ((iNumSeg || iNsOpensScope(iType))
         && nThis->nChildScope == (nte *)0)
        {
            if (Load1 == iLE || Load == iLE)
            {
                /* Allocate the next scope */
                if (Trace & TraceNames)
                    fprintf_bu(iLstFileHandle, LOGFILE, "add level ");
                nThis->nChildScope = nAllocNT(TABLSIZE);
            }

            /* Now complain if there is no next scope */
            if (nThis->nChildScope == (nte *)0)
            {
                if (Load1 == iLE || Load == iLE)
                    vKFatalError("0026", ("Name Table allocation failure"));
                else
                    fprintf_bu(iLstFileHandle, LOGFILE, " Name not found");
                _dKinc_error ("0027", PACRLF, __LINE__, __FILE__, iLstFileHandle, LOGFILE);
                vCheckTrash("leave hNsEnter NOTFOUND 3");
                return (NsHandle)NOTFOUND;
            }
#ifdef NSLOGFILE
            fprintf(LogFile, "%s = %08x size %d\n",
                        pcName, nThis->nChildScope, TABLSIZE);
#endif
            if (Load1 == iLE || Load == iLE)
                /* Set newly-created child scope's parent scope */
                nThis->nChildScope->nParentScope = nLook;
        }
        iSize = TABLSIZE;
        nLook = nThis->nChildScope;
        pcName += 4;    /* point to next name segment */
    }   /* while (iNumSeg-- && nLook) */

    /* If entry is a type which opens a scope,
     * push the new scope on the scope stack.
     */
    if (iNsOpensScope(iTTCF))
    {
        vCheckTrash("before vNsPushCurrentScope");
        vNsPushCurrentScope(nThis->nChildScope, iType);
        vCheckTrash("after  vNsPushCurrentScope");
    }
    return (NsHandle)nThis;
}   /* hNsEnter */

/****************************************************************************
 *  FUNCTION:       NsHandle hGetParentHandle(NsHandle hLook)
 *
 *  PARAMETERS:     NsHandle hLook - Handle whose parent is to be returned
 *
 *  RETURN:         Parent of parameter. NOTFOUND if hLook is invalid
 *                      or hLook refers to the root.
 *
 ***************************************************************************/
NsHandle hGetParentHandle(NsHandle hLook)
{
    nte *nLook, *nThis, *nNextSeg;
    int iSize;

#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "hGetParentHandle");
#endif

    if (hLook == (NsHandle)0 || ((nte *)hLook)->nParentScope == (nte *)0)
        return NOTFOUND;

    /* Look for the handle passed as a parameter */
    nLook = (nte *)hLook;

    /* Look in its parent scope */
    nThis = nLook->nParentScope;

    /* Locate appendage, if any, before losing original scope pointer */
    nNextSeg = NEXTSEG(nThis);

    /* For every entry in the parent scope */
    for (iSize = (nThis == psRoot ? iNsRootSize : TABLSIZE) ; iSize ; --iSize)
    {
        /* If the entry's ChildScope segment matches our segment
         * and our offset is within the ChildScope's range
         * XXX - BUG - This only checks for us being in the prospective parent's
         * XXX - BUG - initial extent.  It won't work if we are in an appendage.
         */

/* REMOVED FOR FLAT MODEL.
      if (sPtrSelector(nThis->nChildScope) == sPtrSelector(nLook)
*/
            
        if (nThis->nChildScope <= nLook
         && nLook < nThis->nChildScope + TABLSIZE)
        {
            /* Return the matching entry */
            return (NsHandle)nThis;
        }
        if (1 == iSize && nNextSeg)
        {
            /* Just examined last entry, but table has an appendage.  */
            nThis = nNextSeg;
            iSize += TABLSIZE;
            nNextSeg = NEXTSEG(nThis);
        }
        else
            ++nThis; /* next entry in parent scope */
    }

    return NOTFOUND;
}   /* hGetParentHandle */

/****************************************************************************
 *  FUNCTION:       static char * pcFindParentName(nte *nLook)
 *
 *  PARAMETERS:     nte *nLook  nte whose name is to be found
 *
 *  RETURN:         pointer to the name
 *
 *  DESCRIPTION:    Search for the given nte in its parent scope and return the
 *                      name segment, or "????" if the parent name can't be found
 *                      (which "should not happen").
 *
 ***************************************************************************/
static char *
pcFindParentName(nte *nLook, int iTrace)
{
    NsHandle hParent = hGetParentHandle(nLook);

#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "pcFindParentName");
#endif

    if (NOTFOUND != hParent)
    {
        nte *nParent = (nte *)hParent;

        if (iTrace)
            fprintf_bu(iLstFileHandle, LOGFILE, "%p->", nParent);
        if (nParent->dNameSeg)
            return (char *)&nParent->dNameSeg;
    }
    return "????";
}

/****************************************************************************
A* FUNCTION:        static char * pcNsNameOfScope(nte *nLook)
 *
 *  PARAMETERS:     nte *nLook  Scope whose name is needed
 *
 *  RETURN:         Pointer to storage containing the fully qualified name of
 *                      the scope, in Label format (all segments strung together
 *                      with no separators)
 *
 *  DESCRIPTION:    Used via pcNsNameOfCurrentScope() and pcLastFQN()
 *                      for label generation in amlscan.c, and for debug
 *                      printing in NsSearchTable().
 *
 *  ALLOCATION:
A* Reference      Size                 Pool  Owner       Description
A* pcFQN{sl}      iFQNsiz{sl:HWM}      bu    acpinmsp    Name of Scope
 *
 ***************************************************************************/
static char *
pcNsNameOfScope(nte *nLook)
{
    nte *nTemp;
    static char *pcFQN = (char *)0;
    static size_t iFQNsiz = 0;
    size_t iSize;

#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "pcNsNameOfScope");
#endif

    if ((nte *)0 == psRoot || (nte *)0 == nLook)
        /* If the name space has not been initialized,
        * this function should not have been called.
        */
        return (char *)0;

    /* Calculate required buffer size based on depth below root NT */
    for (iSize = 1, nTemp = nLook ;
            nTemp->nParentScope ;
            nTemp = nTemp->nParentScope)
        iSize += 4;

    if (iFQNsiz < iSize + 1)
    {
        /* Current buffer is too small; release it and allocate a larger one */
        if (pcFQN != (char *)0)
            OsdFree (pcFQN);
        else
            vRegisterStaticBlockPtr(&pcFQN);
        pcFQN = OsdCallocate (1, iSize + 1);
        if ((char *)0 == pcFQN)
            vKFatalError("0028", ("pcNsNameOfScope: allocation failure"));
        iFQNsiz = iSize + 1;
    }

    /* Store terminator byte, then build name backwards */
    pcFQN[iSize] = '\0';
    while (iSize > 4 && nLook->nParentScope != (nte *)0)
    {
        iSize -= 4;
        *(DWORD *)(pcFQN + iSize) = *(DWORD *)pcFindParentName(nLook, 0);
        nLook = nLook->nParentScope;
    }
    pcFQN[--iSize] = RootPrefix;
    return &pcFQN[iSize];
}

/****************************************************************************
 *  FUNCTION:       char * pcNsNameOfCurrentScope()
 *
 *  PARAMETERS:     none
 *
 *  RETURN:         pointer to storage containing the name of the current scope
 *
 ***************************************************************************/
char *
pcNsNameOfCurrentScope(void)
{
#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "pcNsNameOfCurrentScope");
#endif

    if (psCurrentScope && psCurrentScope->psScope)
        return pcNsNameOfScope(psCurrentScope->psScope);
    vKFatalError("0029", ("Current scope pointer trashed"));
    return (char *)0;
}

/****************************************************************************
A* FUNCTION:        char * pcNsFullyQualifiedName(NsHandle hLook)
 *
 *  PARAMETERS:     NsHandle hLook      handle of nte whose name is to be found
 *
 *  RETURN:         pointer to storage containing the name, in external format
 *
 *  DESCRIPTION:
 *
 *  ALLOCATION:
A* Reference      Size                 Pool  Owner       Description
A* pcFQN{sl}      iFQNsiz{sl:HWM}      bu    acpinmsp    Name of handle
 *
 ***************************************************************************/
char *
pcNsFullyQualifiedName(NsHandle hLook)
{
    nte *nLook = (nte *)hLook;
    nte *nTemp;
    static char *pcFQN = (char *)0;
    static size_t iFQNsiz = 0;
    size_t iSize;
    int iTraceFQN = 0;

#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "pcNsFullyQualifiedName");
#endif

    if ((nte *)0 == psRoot || (nte *)0 == nLook)
        /* If the name space has not been initialized,
         * this function should not have been called.
         */
        return (char *)0;

    /* Compute length of FQN as 5 * number of segments */
    for (iSize = 5, nTemp = nLook ;
          nTemp->nParentScope ;
          nTemp = nTemp->nParentScope)
        iSize += 5;

    if (iFQNsiz < iSize + 1)
    {
        if (pcFQN != (char *)0)
            OsdFree (pcFQN);
        else
            vRegisterStaticBlockPtr(&pcFQN);
        pcFQN = OsdCallocate (1, iSize + 1);
        if ((char *)0 == pcFQN)
            vKFatalError("0030", ("pcNsFullyQualifiedName: allocation failure"));
        iFQNsiz = iSize + 1;
    }

#if 0
    /* Debug hack: if dealing with segment "_PSC" turn on tracing */
    if (0x4353505f == nLook->dNameSeg)
    {
        iTraceFQN = 1;
        fprintf_bu(iLstFileHandle, LOGFILE,
                "NsFQN: nte @ %p, name %08lx, parent @ %p, SizeOfFQN = %d ",
                nLook, nLook->dNameSeg, nLook->nParentScope, iSize);
    }
#endif

    /* Store null termination */
    pcFQN[iSize] = '\0';
    iSize -= 4;
    if (iTraceFQN)
        fprintf_bu(iLstFileHandle, LOGFILE,
                        "%d:%08lx ", iSize, nLook->dNameSeg);
    *(DWORD *)(pcFQN + iSize) = nLook->dNameSeg;
    pcFQN[--iSize] = '.';

    /* Build name backwards, putting "." between segments */
    while (iSize > 4 && nLook != (nte *)0)
    {
        iSize -= 4;
        *(DWORD *)(pcFQN + iSize) = *(DWORD *)pcFindParentName(nLook, iTraceFQN);
        if (iTraceFQN)
            fprintf_bu(iLstFileHandle, LOGFILE,
                            "%d:%08lx ", iSize, *(DWORD *)(pcFQN + iSize));
        pcFQN[--iSize] = '.';
        nLook = nLook->nParentScope;
    }
    /* Overlay the "." preceding the first segment with root name "\" */
    pcFQN[iSize] = '\\';
    return &pcFQN[iSize];
}

/****************************************************************************
A* FUNCTION:        void vNsSetMethod(NsHandle h, ptrdiff_t iOffset, long lLength)
 *
 *  PARAMETERS:     NsHandle        h           handle of nte to be set
 *                      ptrdiff_t   iOffset value to be set
 *                      long            lLength length associated with value
 *
 *  DESCRIPTION:    Record the given offset and p-code length of the method
 *                      whose handle is passed
 *
 *  ALLOCATION:
A* Reference      Size                 Pool  Owner       Description
A* nte.pVal       s(meth)              bu    acpinmsp    Method AML descrip
 *
 ***************************************************************************/
void
vNsSetMethod(
    NsHandle        h,
    ptrdiff_t   iOffset,
    long            lLength)
{
    meth *pM = NEW(meth);

#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "vNsSetMethod");
#endif

    if ((meth *)0 == pM)
        vKFatalError("0031", ("vNsSetMethod: allocation failure"));
    if ((nte *)0 == psRoot)
        vKFatalError("0032", ("vNsSetMethod: name space not initialized"));
    if ((NsHandle)0 == h)
        vKFatalError("0033", ("vNsSetMethod: null name handle"));

    pM->iOffset = iOffset;
    pM->lLength = lLength;
    ((nte *)h)->pVal = (void *)pM;
#if 0
    LineSet(55, Load);
    fprintf_bu(iLstFileHandle, LOGFILE,
                    "[hMethod %p pVal %p iOffset %x lLength %lx]",
                    h, pM, pM->iOffset, pM->lLength);
#endif
}

/****************************************************************************
 *  FUNCTION:       void vNsSetValue(NsHandle hN, ACPI_OBJECT_HANDLE hV, ...)
 *
 *  PARAMETERS:     NsHandle                    hN          handle of nte to be set
 *                      ACPI_OBJECT_HANDLE  hV          value to be set
 *                      BYTE                        bValTyp type of value,
 *                                                              or Any if not known
 *
 *  DESCRIPTION:    Record the given object as the value associated with the
 *                      name whose NsHandle is passed.  If hV is NULL and bValTyp
 *                      is Any, set the name as having no value.
 *
 * ALLOCATION:      This function must not call NEW() or [mc]alloc_bu because
 *                      some of its callers require that no garbage collection
 *                      happen during it.
 *
 ***************************************************************************/
void
vNsSetValue(NsHandle hN, ACPI_OBJECT_HANDLE hV, BYTE bValTyp)
{
    void *pvTemp;

#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "vNsSetValue");
#endif

    if ((nte *)0 == psRoot)
        vKFatalError("0034", ("vNsSetValue: name space not initialized"));
    if ((NsHandle)0 == hN)
        vKFatalError("0035", ("vNsSetValue: null name handle"));
    if ((ACPI_OBJECT_HANDLE)0 == hV && Any != bValTyp)
        vKFatalError("0036", ("vNsSetValue: null value handle"));
    if (!iIsNsHandle(hN))
        vKFatalError("0037", ("vNsSetValue: \"name handle\" param isn't a name handle"));

    /* Delete the old value.  Must set the pVal field to NULL first
     * so that vDeleteObject() doesn't find the descriptor reachable.
     */
    pvTemp = ((nte *)hN)->pVal;
    ((nte *)hN)->pVal = (void *)0;
    vDeleteObject((OBJECT_DESCRIPTOR **)&pvTemp);

    /* If the new value is NULL, done */
    if ((ACPI_OBJECT_HANDLE)0 == hV && Any == bValTyp)
    {
        ((nte *)hN)->iNtType = (NsType)bValTyp;
        return;
    }

    /* Set the new value */
    ((nte *)hN)->pVal = hV;

    /* Set the type if given, or if it can be discerned */
    if (Any != bValTyp)
        ((nte *)hN)->iNtType = (NsType)bValTyp;
    else if (iIsInPCodeBlock((BYTE *)hV))
        /* hV points into the AML stream.  Check for a recognized OpCode */
        switch(*(BYTE *)hV)
        {
            case OpPrefix:
                if (*(WORD *)hV != RevisionOp)
                    /* OpPrefix is unrecognized unless part of RevisionOp */
                    break;
                /* else fall through to set type as Number */
            case ZeroOp: case OnesOp: case OneOp:
            case ByteOp: case WordOp: case DWordOp:
                ((nte *)hN)->iNtType = Number;
                break;

            case StringOp:
                ((nte *)hN)->iNtType = String;
                break;

            case BufferOp:
                ((nte *)hN)->iNtType = Buffer;
                break;

            case PackageOp:
                ((nte *)hN)->iNtType = Package;
                break;

            default:
                break;
        }
    else if (iIsNsHandle(hV) && ((nte *)hV)->pVal != (void *)0)
        /* Value passed is a name handle and that name has a non-null value.
         * Use that name's value and type.
         */
            vNsSetValue(hN, ((nte *)hV)->pVal, (BYTE)((nte *)hV)->iNtType);
    else
    {
        /* Cannot figure out the type -- set to DefAny which will print as an
         * error in the name table dump
         */
        if (debug_level() > 0)
        {
            fprintf_bu(iLstFileHandle, LOGFILE,
                        "vNsSetValue:confused:setting bogus type for %s from ",
                        pcNsFullyQualifiedName(hN));
            if (iIsInPCodeBlock((BYTE *)hV))
                fprintf_bu(iLstFileHandle, LOGFILE,
                            "AML-stream code %02x\n", *(BYTE *)hV);
            else if (iIsNsHandle(hV))
                fprintf_bu(iLstFileHandle, LOGFILE,
                            "name %s\n", pcNsFullyQualifiedName(hV));
            else
            {
                fprintf_bu(iLstFileHandle, LOGFILE,
                            "object %p:", pcNsFullyQualifiedName(hV));
                iDumpStackEntry(hV);
            }
        }
        ((nte *)hN)->iNtType = DefAny;
    }
}

/****************************************************************************
 *  FUNCTION:       static int iExistDownstreamSibling(nte *nThis, int iSize, ...)
 *
 *  PARAMETERS:     nte *nThis      pointer to first nte to examine
 *                      int iSize       # of entries remaining in table
 *                      nte *nNextSeg   addr of NT's appendage, or NULL
 *
 *  RETURN:         TRUE if sibling is found, FALSE otherwise
 *
 *  DESCRIPTION:    Searches remainder of scope being processed to determine
 *                      whether there is a downstream sibling to the current
 *                      object.  This function is used to determine what type of
 *                      line drawing character to use when displaying namespace
 *                      trees.
 *
 ***************************************************************************/
static int
iExistDownstreamSibling (nte *nThis, int iSize, nte *nNextSeg)
{
#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "iExistDownstreamSibling");
#endif

    if ((nte *)0 == nThis)
        return FALSE;

    if (0 == iSize && nNextSeg)
    {
        /* Trying to examine (last entry + 1), but table has an appendage.  */
        nThis = nNextSeg;
        iSize += TABLSIZE;
        nNextSeg = NEXTSEG(nThis);
    }

    while (iSize--)
    {
        if (nThis->dNameSeg)
            return TRUE;
        if (0 == iSize && nNextSeg)
        {
            /* Just examined last entry, but table has an appendage.  */
            nThis = nNextSeg;
            iSize += TABLSIZE;
            nNextSeg = NEXTSEG(nThis);
        }
        else
            ++nThis;
    }
    return FALSE;
}

/****************************************************************************
 *  FUNCTION:       static void vNsDumpTable(nte *nThis, int iSize, int iLevel)
 *
 *  PARAMETERS:     nte *nThis                  table to be dumped
 *                      int iSize                   size of table
 *                      int iLevel                  Number of ancestor levels
 *                      int iDisplayBitFlags        See description in vNsDumpTables()
 *                      int iUseGraphicCharSet  See description in vNsDumpTables()
 *                      int iMaxDepth               See description in vNsDumpTables()
 *
 *  DESCRIPTION:    Dump a name table and its descendents
 *
 ***************************************************************************/
static void
vNsDumpTable(
    nte *nThis,
    int iSize,
    int iLevel,
    int iDisplayBitFlags,
    int iUseGraphicCharSet,
    int iMaxDepth)
{
    nte *nNextSeg;
    static DWORD dDownstreamSiblingMask = 0;

#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "vNsDumpTable");
#endif

    if (0 == iMaxDepth || (nte *)0 == nThis)
        /* reached requested depth, or nothing to dump */
        return;

    if (TRACE)
        fprintf_bu(iLstFileHandle, LOGFILE,
                "enter vNsDumpTable(%p, %d, %d, %d, %d)\n                   %p",
                nThis, iSize, iLevel, iDisplayBitFlags, iUseGraphicCharSet,
                nThis->dNameSeg);

    /* Locate appendage, if any, before losing original scope pointer */
    if (1 == iSize)
        nNextSeg = (nte *)0;
    else
        nNextSeg = NEXTSEG(nThis);

    /* for each entry in table */
    while (iSize--)
    {
        if (nThis->dNameSeg)
        {
            /* non-empty entry */
            int     iL              = iLevel;
            NsType  iType           = nThis->iNtType;
            DWORD       dWhichBit   = 1;

            /* print appropriate graphic characters to form tree structure */
            while (iL--)
            {
                if (iL)
                {
                    if (dDownstreamSiblingMask & dWhichBit)
                        fprintf_bu(iLstFileHandle, iDisplayBitFlags & OUTPUT_DATA,
                                iUseGraphicCharSet ? "³  " : "|  ");
                    else
                        fprintf_bu(iLstFileHandle, iDisplayBitFlags & OUTPUT_DATA,
                                "   ");
                    dWhichBit <<= 1;
                }
                else
                {
                    if (iExistDownstreamSibling (nThis + 1, iSize, nNextSeg))
                    {
                        dDownstreamSiblingMask |= (1 << (iLevel - 1));
                        fprintf_bu (iLstFileHandle, iDisplayBitFlags & OUTPUT_DATA,
                                iUseGraphicCharSet ? "ÃÄÄ" : "+--");
                    }
                    else
                    {
                        dDownstreamSiblingMask &= 0xffffffff ^ (1 << (iLevel - 1));
                        fprintf_bu (iLstFileHandle, iDisplayBitFlags & OUTPUT_DATA,
                                iUseGraphicCharSet ? "ÀÄÄ" : "+--");
                    }

                    if (nThis->nChildScope == NULL)
                        fprintf_bu(iLstFileHandle, iDisplayBitFlags & OUTPUT_DATA,
                                iUseGraphicCharSet ? "Ä " : "- ");
                    else if (iExistDownstreamSibling(nThis->nChildScope, TABLSIZE,
                                                                NEXTSEG(nThis->nChildScope)))
                        fprintf_bu(iLstFileHandle, iDisplayBitFlags & OUTPUT_DATA,
                                iUseGraphicCharSet ? "Â " : "+ ");
                    else
                        fprintf_bu(iLstFileHandle, iDisplayBitFlags & OUTPUT_DATA,
                                iUseGraphicCharSet ? "Ä " : "- ");
                }
            }
            if (OUTRANGE(iType, apcNsTypeNames))
                iType = DefAny;                                 /* prints as *ERROR* */
            if (!NcOK((int)*(char *)&nThis->dNameSeg))
            {
                fprintf_bu(iLstFileHandle, LOGFILE,
                        "*** bad name %08lx at %p *** ", nThis->dNameSeg, nThis);
                _dKinc_error ("0038", PACRLF, __LINE__, __FILE__, iLstFileHandle, LOGFILE);
            }
            if (Method == iType && nThis->pVal != (void *)0)
            {
                /* name is a Method and its AML offset/length are set */
                if (debug_level() > 0)
                    fprintf_bu(iLstFileHandle, LOGFILE, "%p: ", nThis);
                fprintf_bu(iLstFileHandle, LOGFILE, "%4.4s [%s %04x:%04lx]",
                        &nThis->dNameSeg, apcNsTypeNames[iType],
                        ((meth *)nThis->pVal)->iOffset,
                        ((meth *)nThis->pVal)->lLength);
                if (debug_level() > 0)
                    fprintf_bu(iLstFileHandle, LOGFILE, " C:%p P:%p",
                            nThis->nChildScope, nThis->nParentScope);
/*              fprintf_bu(iLstFileHandle, LOGFILE, "\n"); */
            }
            else
            {
                /* name is not a Method, or the AML offset/length are not set */
                BYTE *pbVal = nThis->pVal;

                if (debug_level() > 0)
                    fprintf_bu(iLstFileHandle, LOGFILE, "%p: ", nThis);
                fprintf_bu(iLstFileHandle, LOGFILE,
                        "%4.4s [%s]", &nThis->dNameSeg, apcNsTypeNames[iType]);
                if (debug_level() > 0)
                    fprintf_bu(iLstFileHandle, LOGFILE, " C:%p P:%p V:%p",
                            nThis->nChildScope, nThis->nParentScope, nThis->pVal);
/*              fprintf_bu(iLstFileHandle, LOGFILE, "\n");a*/
#if 0
                /* debug code used to show parents */
                if (IndexField == iType && 0 == iSize && 0 == iLevel
                 && nThis->nParentScope)
                {
                    fprintf_bu(iLstFileHandle, LOGFILE, "  in ");
                    ++TRACE;
                    fprintf_bu(iLstFileHandle, LOGFILE,
                            "call vNsDumpEntry %p\n", nThis->nParentScope);
                    vNsDumpEntry((NsHandle)nThis->nParentScope, iDisplayBitFlags);
                    fprintf_bu(iLstFileHandle, LOGFILE,
                            "ret from vNsDumpEntry %p\n", nThis->nParentScope);
                    --TRACE;
                }
#endif
                /* if debug turned on, display values */
                while (pbVal && debug_level() > 0)
                {
                    BYTE bT = ((OBJECT_DESCRIPTOR *)pbVal)->bValTyp;

                    fprintf_bu(iLstFileHandle, LOGFILE,
                        "                 %p  %02x %02x %02x %02x %02x %02x",
                        pbVal, pbVal[0], pbVal[1], pbVal[2], pbVal[3], pbVal[4],
                        pbVal[5]);
                    fprintf_bu(iLstFileHandle, LOGFILE,
                        " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n",
                        pbVal[6], pbVal[7], pbVal[8], pbVal[9], pbVal[10],
                        pbVal[11], pbVal[12], pbVal[13], pbVal[14], pbVal[15]);
                    if (bT == String || bT == Buffer || bT == Package
                     || bT == FieldUnit || bT == DefField || bT == BankField
                     || bT == IndexField || bT == Lvalue)
                        /* Get pointer to next level.  This assumes that all of
                         * the above-listed variants of OBJECT_DESCRIPTOR have
                         * compatible mappings.
                         */
                        pbVal = ((OBJECT_DESCRIPTOR *)pbVal)->sBuffer.pbBuffer;
                    else
                        break;
                }
            }
            if (nThis->nChildScope && iMaxDepth > 1)
                /* dump next scope level */
                vNsDumpTable(nThis->nChildScope, TABLSIZE, iLevel+1,
                        iDisplayBitFlags, iUseGraphicCharSet, iMaxDepth - 1);
        }
        if (0 == iSize && nNextSeg)
        {
            /* Just examined last entry, but table has an appendage.  */
            nThis = nNextSeg;
            iSize += TABLSIZE;
            nNextSeg = NEXTSEG(nThis);
        }
        else
            ++nThis;
    }
    if (TRACE)
        fprintf_bu(iLstFileHandle, LOGFILE, "leave vNsDumpTable %p", nThis);
}

/****************************************************************************
 *  FUNCTION:       void vNsDumpTables(int iDisplayBitFlags, ...)
 *
 *  PARAMETERS:     int iDisplayBitFlags        See definitions of OUTPUT_DATA
 *                                                      and related symbols in display.h
 *                      int iUseGraphicCharSet  1 => use graphic character set to
 *                                                            draw links in name space tree
 *                                                      0 => use +, -, and | to draw links
 *                      NsHandle hSearchBase        Root of subtree to be dumped, or
 *                                                      NS_ALL to dump the entire namespace
 *                      int     iMaxDepth       Maximum depth of dump.  Use INT_MAX
 *                                                      for an effectively unlimited depth.
 *
 *  DESCRIPTION:    Dump the name space, or a portion of it.
 *
 ***************************************************************************/
void
vNsDumpTables(int iDisplayBitFlags, int iUseGraphicCharSet,
        NsHandle hSearchBase, int iMaxDepth)
{
#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "vNsDumpTables");
#endif

    if ((nte *)0 == psRoot)
        /* If the name space has not been initialized,
         * there is nothing to dump.
         */
        return;

    if (NS_ALL == hSearchBase)
    {
        hSearchBase = psRoot;
        fprintf_bu(iLstFileHandle, LOGFILE, "\\");
    }

    vNsDumpTable(hSearchBase, hSearchBase == psRoot ? iNsRootSize : TABLSIZE,
            1, iDisplayBitFlags, iUseGraphicCharSet, iMaxDepth);
}

/****************************************************************************
 *  FUNCTION:       void vNsDumpEntry(NsHandle h)
 *
 *  PARAMETERS:     NsHandle h      Entry to be dumped
 *
 *  DESCRIPTION:    Dump a single nte
 *
 ***************************************************************************/
void
vNsDumpEntry(NsHandle h, int iDisplayBitFlags)
{
#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "vNsDumpEntry");
#endif

    if (TRACE)
        fprintf_bu(iLstFileHandle, LOGFILE, "enter vNsDumpEntry %p", h);
    vNsDumpTable((nte *)h, 1, 0, iDisplayBitFlags, 0, 1);
    if (TRACE)
        fprintf_bu(iLstFileHandle, LOGFILE, "leave vNsDumpEntry %p", h);
}

/****************************************************************************
 *  FUNCTION:       static void vNsFindNames(nte *nThis, int iSize, ...)
 *
 *  PARAMETERS:     nte     *nThis          table to be searched
 *                      int      iSize          size of table
 *                      char        *pcSearchFor    pattern to be found.
 *                                                      4 bytes, ? matches any character.
 *                      int     *piCount            output count of matches found.
 *                                                      Outermost caller should preset to 0
 *                      NsHandle     anList[]       output array of handles.  If
 *                                                      null, only the count is obtained.
 *                      int     iMaxDepth       Maximum depth of search.  Use
 *                                                      INT_MAX for an effectively
 *                                                      unlimited depth.
 *
 *  DESCRIPTION:    Traverse the name space finding names which match a search
 *                      pattern, and return an array of handles in anList[].
 *
 ***************************************************************************/
static void
vNsFindNames(nte *nThis, int iSize, char *pcSearchFor,
                 int *piCount, NsHandle anList[], int iMaxDepth)
{
    nte *nNextSeg;
#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "vNsFindNames");
#endif

    if (0 == iMaxDepth || (nte *)0 == nThis
     || (char *)0 == pcSearchFor || (int *)0 == piCount)
        /* reached requested depth, nothing to search,
         * nothing to search for, or count pointer bad */
        return;

    /* Locate appendage, if any, before losing original scope pointer */
    nNextSeg = NEXTSEG(nThis);

    /* Loop over entries in NT */
    while (iSize--)
    {
        if (nThis->dNameSeg)
        {
            /* non-empty entry */
            int i;

#define BYTES_PER_SEGMENT 4
            for ( i = 0 ; i < BYTES_PER_SEGMENT ; ++i )
                if (pcSearchFor[i] != '?'
                 && pcSearchFor[i] != ((char *)&nThis->dNameSeg)[i])
                    break;

            if (BYTES_PER_SEGMENT == i)
            {
                /* name matches pattern */
                if (anList)
                    anList[*piCount] = (NsHandle)nThis;
                ++*piCount;
            }

            if (nThis->nChildScope)
                vNsFindNames(nThis->nChildScope, TABLSIZE, pcSearchFor,
                                 piCount, anList, iMaxDepth - 1);
        }
        if (0 == iSize && nNextSeg)
        {
            /* Just examined last entry, but table has an appendage.  */
            nThis = nNextSeg;
            iSize += TABLSIZE;
            nNextSeg = NEXTSEG(nThis);
        }
        else
            ++nThis;
    }
    if (anList)
        /* null-terminate the output array */
        anList[*piCount] = (NsHandle)0;
}

/****************************************************************************
A* FUNCTION:        NsHandle *phNsFindNames(char *pcSearchFor, ... )
 *
 *  PARAMETERS:     char      *pcSearchFor pattern to be found.
 *                                                  4 bytes, ? matches any character.
 *                                                  If NULL, "????" will be used.
 *                      NsHandle hSearchBase Root of subtree to be searched, or
 *                                                  NS_ALL to search the entire namespace
 *                      int     iMaxDepth   Maximum depth of search.  Use INT_MAX
 *                                                  for an effectively unlimited depth.
 *
 *  DESCRIPTION:    Traverse the name space finding names which match a search
 *                      pattern, and return an array of handles.  The end of the
 *                      array is marked by the value (NsHandle)0.  A return value
 *                      of (NsHandle *)0 indicates that no matching names were
 *                      found or that space for the list could not be allocated.
 *                      if hSearchBase is NS_ALL (null) search from the root,
 *                      else it is a handle whose children are to be searched.
 *
 *  ALLOCATION:
A* Reference      Size                 Pool  Owner       Description
A* RETURNED       #*s(NsHandle)        bu    CALLER      Array of NsHandle
 *
 ***************************************************************************/
NsHandle *
phNsFindNames(char *pcSearchFor, NsHandle hSearchBase, int iMaxDepth)
{
    NsHandle *pnList;
    int iCount, iBaseSize;

#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "phNsFindNames");
#endif

    if ((nte *)0 == psRoot)
        /* If the name space has not been initialized,
         * there surely are no matching names.
         */
        return (NsHandle *)0;

    if (NS_ALL == hSearchBase)
        hSearchBase = psRoot;
    else if ((NsHandle)0 != ((nte *)hSearchBase)->nChildScope)
        hSearchBase = ((nte *)hSearchBase)->nChildScope;
    else
        /* If base is not the root and has no children,
         * there is nothing to search.
         */
        return (NsHandle *)0;

    if (hSearchBase == psRoot)
        iBaseSize = iNsRootSize;
    else
        iBaseSize = TABLSIZE;

    if ((char *)0 == pcSearchFor)
        pcSearchFor = "????";

    /* Pass 1.  Get required buffer size, don't try to build list */
    iCount = 0;
    vCheckTrash("phNsFindNames before count");
    vNsFindNames(hSearchBase, iBaseSize, pcSearchFor, &iCount, (NsHandle *)0,
            iMaxDepth);
    vCheckTrash("phNsFindNames after count");
    if (0 == iCount)
        return (NsHandle *)0;

    ++iCount;   /* Allow for trailing null */
    pnList = (NsHandle *) OsdCallocate ((size_t)iCount, sizeof(NsHandle));
    if ((NsHandle *)0 == pnList)
        vKFatalError("0039", ("phNsFindNames: allocation failure"));

    /* Pass 2.  Fill buffer */
    iCount = 0;
    vCheckTrash("phNsFindNames before list");
    vNsFindNames(hSearchBase, iBaseSize, pcSearchFor, &iCount, pnList,
            iMaxDepth);
    vCheckTrash("phNsFindNames after list");

    return pnList;
}

/****************************************************************************
 *  FUNCTION:       NsHandle hNsGetHandle(char *pcName, NsHandle hScope)
 *
 *  PARAMETERS:     char      *pcName   Name to be found, in external (ASL)
 *                                              format.  The \ and ^ prefixes, and the
 *                                              . to separate segments, are supported.
 *
 *                      NsHandle hScope Root of subtree to be searched, or
 *                                              NS_ALL for the root of the name space.
 *                                              If pcName is fully qualified (first char
 *                                              is '\'), the passed value of hScope will
 *                                              not be accessed.
 *
 *  DESCRIPTION:    Look up a name relative to a given scope and return the
 *                      corresponding handle, or (NsHandle)NOTFOUND.
 *
 ***************************************************************************/
NsHandle
hNsGetHandle(char *pcName, NsHandle hScope)
{
    int iSize;

#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "hNsGetHandle");
#endif

    if ((nte *)0 == psRoot || (char *)0 == pcName)
        /* If the name space has not been initialized,
         * the requested name surely does not exist.
         */
        return (NsHandle)NOTFOUND;

    if ('\\' == *pcName)
    {
        /* Name is fully qualified -- start at the root */
        ++pcName;
        hScope = psRoot;
    }
    else
        /* Name is relative to hScope -- handle any ^ prefixes */
        while ('^' == *pcName)
        {
            if (psRoot == hScope || (NsHandle)0 == hScope)
                return (NsHandle)NOTFOUND;
            hScope = (NsHandle)((nte *)hScope)->nParentScope;
            ++pcName;
        }

    /* Handle NS_ALL case */
    if (NS_ALL == hScope)
        hScope = psRoot;

    iSize = hScope == psRoot ? iNsRootSize : TABLSIZE;

    do
    {
        hScope
            = (NsHandle)nsSearchTable(pcName, (nte *)hScope, iSize, Exec, DefAny);
        pcName += 4;
        iSize = TABLSIZE;
    } while (hScope && '.' == *pcName++);

    if (*pcName)
        /* ran out of levels, or there is a char following last segment */
        return (NsHandle)NOTFOUND;

    return hScope;
}

/****************************************************************************
 * FUNCTION:        static NsHandle hNsFindpVal(OBJECT_DESCRIPTOR *pOD, ... )
 *
 *  PARAMETERS:     OBJECT_DESCRIPTOR     *pOD value to be found in pVal field.
 *                      NsHandle hSearchBase Root of subtree to be searched, or
 *                                                  NS_ALL to search the entire namespace
 *                      int     iMaxDepth   Maximum depth of search.  Use INT_MAX
 *                                                  for an effectively unlimited depth.
 *
 *  DESCRIPTION:    Traverse the name space until finding a name whose pVal
 *                      matches the pOD parameter, and return a handle to that
 *                      name, or (NsHandle)0 if none exists.
 *                      if hSearchBase is NS_ALL (null) search from the root,
 *                      else it is a handle whose children are to be searched.
 *
 ***************************************************************************/
static NsHandle
hNsFindpVal(OBJECT_DESCRIPTOR *pOD, NsHandle hSearchBase, int iMaxDepth)
{
    nte *nThis, *nNextSeg;
    int iSize;

#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "hNsFindpVal");
#endif

    if ((nte *)0 == psRoot)
        /* If the name space has not been initialized,
         * there surely are no matching values.
         */
        return (NsHandle *)0;

    if (NS_ALL == hSearchBase)
        hSearchBase = psRoot;
    else if ((NsHandle)0 != ((nte *)hSearchBase)->nChildScope)
        hSearchBase = ((nte *)hSearchBase)->nChildScope;
    else
        /* If base is not the root and has no children,
         * there is nothing to search.
         */
        return (NsHandle *)0;

    if (hSearchBase == psRoot)
        iSize = iNsRootSize;
    else
        iSize = TABLSIZE;

    if ((OBJECT_DESCRIPTOR *)0 == pOD)
        return (NsHandle *)0;

    if (0 == iMaxDepth)
        return (NsHandle *)0;

    /* Loop over entries in NT */
    nThis = (nte *)hSearchBase;

    /* Locate appendage, if any, before losing original scope pointer */
    nNextSeg = NEXTSEG(nThis);

    while (iSize--)
    {
        if (nThis->dNameSeg)
        {
            /* non-empty entry */
            if (nThis->pVal == pOD)
                return (NsHandle)nThis;

            if (nThis->nChildScope)
            {
                nte *nTemp = hNsFindpVal(pOD, nThis, iMaxDepth - 1);
                if (nTemp)
                    return (NsHandle)nTemp;
            }
        }
        if (0 == iSize && nNextSeg)
        {
            /* Just examined last entry, but table has an appendage.  */
            nThis = nNextSeg;
            iSize += TABLSIZE;
            nNextSeg = NEXTSEG(nThis);
        }
        else
            ++nThis;
    }
}

/*****************************************************************************
 * FUNCTION:        int iIsNsValue(OBJECT_DESCRIPTOR *pOD)
 *
 * PARAMETERS:      OBJECT_DESCRIPTOR *pOD
 *
 * RETURN:          TRUE if the passed descriptor is the value of a Name in
 *                      the name space, else FALSE
 *
 ****************************************************************************/
int
iIsNsValue(OBJECT_DESCRIPTOR *pOD)
{
#ifdef FUNCTION_HELLO
    vFunctionHello ("amlexec.c", "iIsNsValue");
#endif

    return ((NsHandle)0 != hNsFindpVal(pOD, NS_ALL, INT_MAX));
}

#ifdef PLUMBER

/****************************************************************************
 *  FUNCTION:       static void vNsMarkNT(nte *nThis, int iSize, ...)
 *
 *  PARAMETERS:     nte     *nThis          table to be marked
 *                      int      iSize          size of table
 *                      int     *piCount            output count of blocks marked
 *                                                      Outermost caller should preset to 0
 *
 *  DESCRIPTION:    "Mark" a name table and its reachable values,
 *                      including descendents.
 *
 ***************************************************************************/
static void
vNsMarkNT(nte *nThis, int iSize, int *piCount)
{
    nte *nNextSeg;

    if ((nte *)0 == nThis)
        return;

    ++*piCount;
    vMarkBlock((void *)&NEXTSEG(nThis));

#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "vNsMarkNT");
#endif

    /* Locate appendage, if any, before losing original scope pointer */
    nNextSeg = NEXTSEG(nThis);

    /* for all entries in this NT */
    while (iSize--)
    {
        if (nThis->dNameSeg)
        {
            /* non-empty entry -- mark anything it points to */

            switch (iNsValType(nThis))
            {
                OBJECT_DESCRIPTOR *pVal;
                meth *pM;

                case String:
                    pVal = (OBJECT_DESCRIPTOR *)pvNsValPtr(nThis);
                    /* Check for the value pointer in the name table entry
                     * pointing to a string definition in the AML stream,
                     * in which case no allocated storage is involved.
                     */
                    if (pVal && StringOp != *(BYTE *)pVal)
                    {
                        /* Avoid marking value if it is in the AML stream */
                        if (!iIsInPCodeBlock(pVal->sString.pbString))
                            vMarkBlock(pVal->sString.pbString);
                        vMarkBlock(pVal);
                    }
                    break;

                case Buffer:
                    pVal = (OBJECT_DESCRIPTOR *)pvNsValPtr(nThis);
                    /* Check for the value pointer in the name table entry
                     * pointing to a buffer definition in the AML stream,
                     * in which case no allocated storage is involved.
                     */
                    if (pVal && BufferOp != *(BYTE *)pVal)
                    {
                        vMarkBlock(pVal->sBuffer.pbBuffer);
                        vMarkBlock(pVal);
                    }
                    break;

                case Package:
                    pVal = (OBJECT_DESCRIPTOR *)pvNsValPtr(nThis);
                    /* Check for the value pointer in the name table entry
                     * pointing to a package definition in the AML stream,
                     * in which case no allocated storage is involved.
                     */
                    if (pVal && PackageOp != *(BYTE *)pVal)
                        vAmlMarkPackage(pVal);
                    break;

                case Method:
                    pM = (meth *)pvNsValPtr(nThis);
                    if (pM)
                        vMarkBlock(pM);

                case BankField:
                case DefField:
                case FieldUnit:
                case IndexField:
                case Region:
                    pVal = (OBJECT_DESCRIPTOR *)pvNsValPtr(nThis);
                    if (pVal)
                        vAmlMarkObject(pVal);

                default:
                    /* No other types should own storage beyond the nte itself */
                    break;
            }   /* switch */

            if (nThis->nChildScope)
                vNsMarkNT(nThis->nChildScope, TABLSIZE, piCount);
        }
        if (0 == iSize && nNextSeg)
        {
            /* Just examined last entry, but table has an appendage.  */
            nThis = nNextSeg;
            iSize += TABLSIZE;
            ++*piCount;
            vMarkBlock((void *)&NEXTSEG(nThis));
            nNextSeg = NEXTSEG(nThis);
        }
        else
            ++nThis;
    }   /* while (iSize--) */
}
#endif  /* PLUMBER */

/****************************************************************************
 *  FUNCTION:       int iNsMarkNS()
 *
 *  PARAMETERS:     none
 *
 *  DESCRIPTION:    If compiled with bu_plumr.h, traverse the name space
 *                      "marking" all name tables and reachable values.
 *
 *  RETURN:         The number of blocks marked
 *
 ***************************************************************************/
int
iNsMarkNS(void)
{
    int iCount = 0;

#ifdef FUNCTION_HELLO
    vFunctionHello ("acpinmsp.c", "iNsMarkNS");
#endif

#ifdef PLUMBER
    if ((nte *)0 == psRoot)
        /* If the name space has not been initialized,
         * there is nothing to mark.
         */
        return 0;

    vNsMarkNT(psRoot, iNsRootSize, &iCount);
    vMarkStaticBlocks(&iCount);
    vMarkMethodValues(&iCount);
    vMarkObjectStack(&iCount);
#endif  /* PLUMBER */

    return iCount;
}
