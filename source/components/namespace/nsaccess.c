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
 | Functions for accessing ACPI namespace
 |__________________________________________________________________________
 |
 | $Revision: 1.10 $
 | $Date: 2005/06/29 18:15:33 $
 | $Log: nsaccess.c,v $
 | Revision 1.10  2005/06/29 18:15:33  aystarik
 | Moved table-size constants to acpi.h
 |
 | 
 | date	99.03.12.00.20.00;	author rmoore1;	state Exp;
 |
 * 
 * 10    3/11/99 4:20p Rmoore1
 * Moved table-size constants to acpi.h
 * 
 * 9     3/09/99 4:06p Rmoore1
 * 16/32/64-bit common data types
 * 
 * 8     2/16/99 3:36p Rmosgrov
 * 
 * 7     2/16/99 9:05a Rmosgrov
 * Polish Conversion Complete - Compiles 
 * 
 * 6     2/12/99 3:20p Rmosgrov
 * Anti-Polish clean up
 * 
 * 5     2/09/99 11:50a Rmosgrov
 * NsFindpVal was returning with no value at end of the rountine.  May
 * have never reached the exit, but just because the compiler warned, I
 * fixed it.
 * 
 * 4     1/20/99 9:40a Rmoore1
 * Major cleanup
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
// Rename the Type member of the nte to NtType to improve readability.
// 
// Add support for a Method's nte to have a null ptrVal field, indicating
// that the Method is undefined (yet we somehow know that the name is
// supposed to represent a Method).
// 
// Refine debug output fron NsPopCurrent().
// 
// Add a comment re an unfixed bug in GetParentHandle() when the parent
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
// Fixed bug in ExistDownstreamSibling() when checking the last entry of an
// extent.
//
//    Rev 1.48   13 Mar 1998 14:05:44   phutchis
// Corrected marking of name tables in NsMarkNT().
//
//    Rev 1.47   13 Mar 1998 11:16:10   phutchis
// Corrected handling of types BankField, DefField, FieldUnit, IndexField,
//   and Region in NsMarkNT().
// Call vMarkObjectStack() from NsMarkNS().
//
//    Rev 1.46   06 Mar 1998 11:41:00   phutchis
// Added comments concerning garbage collection.
// No code changes.
//
//    Rev 1.45   03 Mar 1998 16:31:24   phutchis
// Enable NsSetValue() to set the value to NULL.
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
//   Added NsPushMethodScope()
//   Check for non-empty stacks only at outermost Method exit.
// Improved storage management
//   Added NsFindpVal(), IsNsValue(), RegisterStaticBlockPtr(),
//     and MarkStaticBlocks().
//   Delete descriptors when popped from stack or overlaid in name table.
//
//    Rev 1.40   18 Dec 1997 21:09:30   kdbranno
// Increased ROOTSIZE and TABLSIZE to 64.  ESG has some scopes that have up
// to 64 entries.  We really should make this into a linked list instead to
// make it entirely dynamic rather than having a static size.
//
//    Rev 1.39   11 Dec 1997 12:08:02   kdbranno
// Fixed bug in SearchTable where false failure occured if ROOTSIZE and TABLSIZE were the same.
// Also enabled logging of forward reference problems even when debug level is 0.
// Changed ROOTSIZE and TABLSIZE both to 25
//
//    Rev 1.38   10 Dec 1997 12:58:28   calingle
// increased the size of the ROOTSIZE from 29 to 53
//
//    Rev 1.37   10 Dec 1997 10:45:04   phutchis
// Corrected comments.
// Removed unneeded {}.
// Fixed OpMode parameter to SearchTable() call in NsGetHandle().
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
//   Made BadType[] public so other modules can check for it in NsTypeNames[].
//
//    Rev 1.30   06 Nov 1997 10:10:06   phutchis
// Added some parameter checking and a few more comments.
//
//    Rev 1.29   05 Nov 1997 08:48:30   calingle
// removed #include <bu_plumr.h>
//
//    Rev 1.28   04 Nov 1997 14:18:36   phutchis
// Fix problems in rev 1.27:
//   Restore increment of DottedName in InternalizeName (lost when the
//     return buffer was changed from static to HWM allocation).
//   Change 4th parameter in recursive call of SearchTable to correspond
//     with the change of that parameter from (INT32) to (OpMode).
// Add debug output when NsSetValue cannot determine the correct type and
//   sets ValType to DefAny.
// Improved comments.
//
//    Rev 1.27   31 Oct 1997 15:43:18   phutchis
// Rework from code inspection:
//   Added/revised comments throughout.
//   Added #include <stddef.h> to get typedef for ptrdiff_t.
//   Replaced empty strings in NsTypeNames[] with error message.
//   Renamed nte.ulNamSeg to nte.NameSeg.
//   Renamed nte.nChildren to nte.ChildScope.
//   Renamed sCurrentScope[] to ScopeStack[].
//   Renamed vNsSetCurrent() to NsPushCurrentScope().
//   Removed vReporter() parameter from several functions.
//   Added calls to KFatalError(()) for numerous catastrophic failures.
//   Changed name buffer used by InternalizeName() from static to HWM alloc.
//   Changed printf control %ls to %p when printing pointers.
//   Changed return-value symbols SUCCESS, FAILURE, ERROR, and RETURN to
//     S_SUCCESS, S_FAILURE, S_ERROR, and S_RETURN to forestall collisions
//     with other subsystems.
//   Delete allocated return value if caller of AcpiExecuteMethod() did not
//     provide a place to store the descriptor.
//   Added warnings to various functions for invalid parameters.
//   Replaced "INT32 iAdd" parameter of SearchTable() with "OpMode LoadMode".
//   Fixed major bug in SearchTable when USE_HASHING was not #defined.
//   Initial values which are strings now get copied to allocated space
//     instead of being left in compiler-allocated static storage.
//   Changed vNsPopCurrent() to NsPopCurrent, returning the number of frames
//     popped (or an error indication).
//   Replaced "INT32 iLoading" parameter of NsEnter() with "OpMode LoadMode".
//   Revised FindParentName() to call GetParentHandle() instead of
//     duplicating its logic.
//   Changed empty formal parameter lists to "(void)".
//   Changed values which are offsets from (INT32) to (ptrdiff_t).
//   Improved parameter diagnostics in NsSetMethod() and NsSetValue().
//   Revised ExistDownstreamSibling() to eliminate unneeded local variables.
//   Ensure correct table size is passed to various functions depending on
//     whether the root, or some other scope, is being processed.
//   Improve NOTFOUND handling in NsGetHandle().
//   Made ExistDownstreamSibling() static.
//
//    Rev 1.26   24 Sep 1997 15:10:26   phutchis
// Add #include of bu_plumr.h, and functions NsMarkNT() and NsMarkNS(),
//   to audit allocation and find leaks.
// Add allocation comments to function headers.
//
//    Rev 1.25   16 Sep 1997 10:37:18   phutchis
// Renamed nParent member of nte to ParentScope to better reflect its use
// Added scope-related tracing in AcpiExecuteMethod() and SearchTable()
// Handle case where vReporter() parameter to NsEnter() is NULL
// Corrected oversimplification in GetParentHandle()
// Corrected handling of subtree search in NsFindNames()
// Added function NsNameOfScope() [generalization of NsNameOfCurrentScope()]
// Added function NsGetHandle()
//
//    Rev 1.24   04 Aug 1997 16:14:04   kdbranno
// Added function GetParentHandle.
//
//    Rev 1.23   29 Jul 1997 14:35:16   phutchis
// Add Params parameter to AcpiExecuteMethod()
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
// Add IsNsHandle() macro, some comments re typedef nte, and a function
// header for InternalizeName
//
//    Rev 1.19   08 Jul 1997 17:02:30   phutchis
// Add ReturnValue parameter to AcpiExecuteMethod().
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
// Add SearchBase and MaxDepth parameters to NsDumpTables()
// and phFindNames()
// Replace (XXX) debugging hack with (Trace & TraceNames)
// Clean up some XXX commented areas
//
//    Rev 1.14   12 Jun 1997 10:00:20   phutchis
// Add parameter to NsFindNames() to enable searching a subtree.
//
//    Rev 1.13   11 Jun 1997 15:47:38   phutchis
// Adjust scope rules to agree with Memphis OS.
// Add capability to preload namespace.
// When a non-method object is passed to AcpiExecuteMethod,
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
// Changed prototpye of ExistDownstreamSibling to take NsHandle rather than
// nte.
// Changed include brackets to quotes for .h files from ACPILIB
//
//    Rev 1.8   Apr 14 1997 16:18:28   kdbranno
// Moved typedef for nte and meth to acpinmsp.h
//
//    Rev 1.7   Apr 14 1997 15:49:08   kdbranno
// Added #include <display.h>.  Implemented function ExistDownstreamSibling().
// Used ExistDownstreamSibling() to make intellegent choice of line drawing
// characters when outputing nametree. Added DisplayBitFlags parameter to
// NsDumpTables().
//
//    Rev 1.6   18 Mar 1997 09:29:56   phutchis
// Work around ic386 breakage where enum != INT32
// Change #include of <malloc.h> to <stdlib.h>
// Cast params of calloc() and NcOK() to proper types
//
//    Rev 1.5   14 Mar 1997 17:44:20   phutchis
// Renamed vNsEnter to NsEnter to correspond to its return value
// type (handle), and added iLoading parameter.
// AcpiExecuteMethod() now finds the passed name in the name space,
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

#define __NSACCESS_C__
#define _THIS_MODULE        "nsaccess.c"


/* 
 * Defining FETCH_VALUES enables AcpiExecuteMethod() to "execute"
 * a name which is not a Method by fetching and returning its value.
 */
#define FETCH_VALUES



#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "acpi.h"
#include "bu.h"
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


/* 
 * set non-zero to enable some flow tracing
 * in NsDumpTable() and NsDumpEntry()
 */
static INT32 TRACE = 1;



/* 
 * Names built-in to interpreter
 *
 * Initial values are currently supported only for types String and Number.
 * To avoid type punning, both are specified as strings in this table.
 */

static struct InitVal {
    char        *Name;
    NsType      Type;
    char        *Val;
} PreDefinedNames[] = {
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


/* 
 * Elements of NsProperties are bit significant
 * and should be one-to-one with values of NsType in acpinmsp.h
 */
#define NEWSCOPE    1               /* a definition of this type opens a name scope */
#define LOCAL       2               /* suppress search of enclosing scopes */

static INT32 NsProperties[] = {     /* properties of types */
    0,                      /* Any              */
    0,                      /* Number           */
    0,                      /* String           */
    0,                      /* Buffer           */
    LOCAL,                  /* Package          */
    0,                      /* FieldUnit        */
    NEWSCOPE | LOCAL,       /* Device           */
    LOCAL,                  /* Event            */
    NEWSCOPE | LOCAL,       /* Method           */
    LOCAL,                  /* Mutex            */
    LOCAL,                  /* Region           */
    NEWSCOPE | LOCAL,       /* Power            */
    NEWSCOPE | LOCAL,       /* Processor        */
    NEWSCOPE | LOCAL,       /* Thermal          */
    0,                      /* Alias            */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,                      /* DefField         */
    0,                      /* BankField        */
    0,                      /* IndexField       */
    0,                      /* DefFieldDefn     */
    0,                      /* BankFieldDefn    */
    0,                      /* IndexFieldDefn   */
    0,                      /* If               */
    0,                      /* Else             */
    0,                      /* While            */
    NEWSCOPE,               /* Scope            */
    LOCAL,                  /* DefAny           */
    0                       /* Lvalue           */
};

char BadType[] = "ERROR: unused type encoding found in table";


/* 
 * Elements of NsTypeNames should be
 * one-to-one with values of NsType in acpinmsp.h
 */

/* 
 * The type Any is used as a "don't care" when searching; when stored in a
 * table it really means that we have thus far seen no evidence to indicate
 * what type is actually going to be stored for this entry.
 */

char *NsTypeNames[] = { /* printable names of types */
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
    BadType, BadType, BadType, BadType, BadType,
    BadType, BadType, BadType, BadType, BadType,
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
    UINT32          NameSeg;       /* name segment, always 4 chars per ACPI spec.
                                     * NameSeg must be the first field in the nte
                                     * -- see the IsNsHandle macro in acpinmsp.h
                                     */
    struct nte      *ChildScope;   /* next level of names */
    struct nte      *ParentScope;  /* previous level of names */
    NsType          NtType;        /* type associated with name */
    void            *ptrVal;          /* pointer to value */
} nte;

#define NOTFOUND (nte *)0


/* 
 * If USE_HASHING is not set, there will be an (nte *) prefix to each name
 * table, containing either a NULL pointer or the address of the next array
 * of nte's in the scope.
 */

#ifndef USE_HASHING
#define NEXTSEG(NameTbl) ((nte **)NameTbl)[-1]
#endif

static nte      *Root = (nte *)0;

/* set from ROOTSIZE -- could potentially support dynamic sizing of root NT */

static INT32    NsRootSize;        

/* will be either ROOTSIZE or TABLSIZE depending on whether the current scope is the root */

static INT32    NsCurrentSize;      

/* local logfile for debugging */

#ifdef NSLOGFILE
static FILE     *LogFile;
#endif


/* Stack of currently-open scopes, and pointer to top of that stack */

static struct
{
    nte         *Scope;

    /* 
     * Type of scope, typically the same as the type of its parent's entry 
     * (but not the same as the type of its parent's scope).
     */

    NsType      Type;   
    
} ScopeStack[MAXNEST], *CurrentScope;



#ifdef PLUMBER

#define MAX_STATIC_BLOCKS 10

static void     **StaticBlockList[MAX_STATIC_BLOCKS];
static INT32    NumStaticBlocks = 0;



/****************************************************************************
 *
 * FUNCTION:    RegisterStaticBlockPtr
 *
 * PARAMETERS:  void    **BlkPtr         Addr of static pointer to be registered
 *
 * DESCRIPTION: If compiled with bu_plumr.h, add the pointer whose address
 *              is passed to the registry.  MarkStaticBlocks() will then
 *              "mark" each block pointed to by a registered pointer.
 *
 ***************************************************************************/

void
RegisterStaticBlockPtr (void **BlkPtr)
{


    if (NumStaticBlocks < MAX_STATIC_BLOCKS)
    {
        StaticBlockList[NumStaticBlocks++] = (void **) BlkPtr;
    }

    else
    {
        fprintf_bu (LstFileHandle, LOGFILE,
                        "RegisterStaticBlockPtr: too many static blocks");
        _Kinc_warning ("0001", PRINT, __LINE__, __FILE__, LstFileHandle, LOGFILE);
    }
}


/****************************************************************************
 *
 * FUNCTION:    MarkStaticBlocks
 *
 * PARAMETERS:  INT32 *Count        Count of blocks marked
 *
 * DESCRIPTION: "Mark" all blocks pointed to by registered static pointers
 *
 ***************************************************************************/

void
MarkStaticBlocks (INT32 *Count)
{
    INT32           i;


    for (i = 0; i < NumStaticBlocks; ++i)
    {
        ++*Count;
        MarkBlock (*StaticBlockList[i]);
    }
}

#endif /* PLUMBER */


/****************************************************************************
 *
 * FUNCTION:    AllocNT
 *
 * PARAMETERS:  INT32 Size       # of nte in table
 *
 * DESCRIPTION: Allocate an array of nte, including prepended link space
 *
 * RETURN:      The address of the first nte in the array, or NULL
 *
 ***************************************************************************/

static nte *
AllocNT (INT32 Size)
{
    nte             *NewNT;
    size_t          AllocSize = (size_t) Size * sizeof (nte);


#ifndef USE_HASHING
    
    /* Allow room for link to appendage */
    
    AllocSize += sizeof (nte *);
#endif

    
    NewNT = (nte *) OsdCallocate (AllocSize, 1);

#ifndef USE_HASHING
    if (NewNT)
    {
        /* Move past the appendage pointer */
        
        NewNT = (nte *) (((UINT8 *) NewNT) + sizeof (nte *));
    }
#endif

    return NewNT;
}


/****************************************************************************
 *
 * FUNCTION:    NsPushCurrentScope
 *
 * PARAMETERS:  nte     *NewScope,             name to be made current
 *              NsType  Type,                  type of frame being pushed
 *
 * DESCRIPTION: Push the current scope on the scope stack, and make the
 *              passed nte current.
 *
 ***************************************************************************/

static void
NsPushCurrentScope (nte *NewScope, NsType Type)
{

    FUNCTION_TRACE ("NsPushCurrentScope");


    if ((nte *) 0 == NewScope)
    {
        KFatalError ("0002", ("NsPushCurrentScope: null scope passed"));
    }

    if (OUTRANGE (Type, NsTypeNames) || BadType == NsTypeNames[Type])
    {
        fprintf_bu (LstFileHandle, LOGFILE,
                        "NsPushCurrentScope: type code %d out of range", Type);
        _Kinc_warning ("0003", PRINT, __LINE__, __FILE__, LstFileHandle, LOGFILE);
    }

    if (CurrentScope < &ScopeStack[MAXNEST-1])   /* check for overflow */
    {
        ++CurrentScope;
        CurrentScope->Scope = NewScope;
        CurrentScope->Type = Type;

        if (CurrentScope->Scope == Root)
        {
            NsCurrentSize = NsRootSize;
        }
        
        else
        {
            NsCurrentSize = TABLSIZE;
        }
    }
    
    else
    {
        KFatalError ("0004", ("Scope stack overflow"));
    }
}


/****************************************************************************
 *
 * FUNCTION:    NsPushMethodScope
 *
 * PARAMETERS:  NsHandle NewScope,             name to be made current
 *
 * DESCRIPTION: Push the current scope on the scope stack, and make the
 *              passed nte current.
 *
 ***************************************************************************/

void
NsPushMethodScope (NsHandle NewScope)
{

    FUNCTION_TRACE ("NsPushMethodScope");


    if ((nte *) 0 == NewScope || (nte *) 0 == ((nte *) NewScope)->ChildScope)
    {
        KFatalError ("0005", ("NsPushMethodScope: null scope passed"));
    }

    if (CurrentScope < &ScopeStack[MAXNEST-1])   /* check for overflow */
    {
        NsPushCurrentScope (((nte *) NewScope)->ChildScope, Method);
    }
    
    else
    {
        KFatalError ("0006", ("Scope stack overflow"));
    }
}


/*ARGSUSED*/

/* REMOVE THIS !!! */

void
NoMsg (char * pcMessage)
{

    FUNCTION_TRACE ("vNoMsg");

}


/****************************************************************************
 *
 * FUNCTION:    InternalizeName
 *
 * PARAMETERS:  char *DottedName -        external representation of name
 *
 * RETURN:      Internal representation of name
 *
 * DESCRIPTION: Convert an external representation (e.g. "\_PR_.CPU0")
 *              to internal form (e.g. 5c 2f 02 5f 50 52 5f 43 50 55 30)
 *
 * ALLOCATION:
 * Reference   Size              Pool  Owner                Description
 * pcIN{sl}    INsiz{sl:HWM}     bu    InternalizeName      Internal name
 *
 ****************************************************************************/

static char *
InternalizeName (char *DottedName)
{
    char            *pcResult;
    size_t          i;
    static char     *pcIN = (char *) 0;
    static          size_t INsiz = 0;


    FUNCTION_TRACE ("InternalizeName");


    i = strlen (DottedName++) / 5;

    /* 
     * Required length is 4 bytes per segment, plus 1 each for RootPrefix,
     * MultiNamePrefixOp, segment count, trailing null (which is not really
     * needed, but no there's harm in putting it there)
     */

    if (INsiz < 4 * i + 4)
    {
        if (pcIN != (char *) 0)
        {
            OsdFree (pcIN);
        }
        
        else
        {
            RegisterStaticBlockPtr(&pcIN);
        }

        pcIN = OsdCallocate (1, 4 * i + 4);
        if ((char *) 0 == pcIN)
        {
            KFatalError("0007", ("InternalizeName: allocation failure"));
        }
        
        INsiz = 4 * i + 4;
    }

    strcpy (pcIN, "\\/");
    for (pcIN[2] = i, pcResult = &pcIN[3]; i; --i)
    {
        strncpy (pcResult, DottedName, 4);
        pcResult += 4;
        DottedName += 5;
    }

    *pcResult = '\0';

    /* fprintf(fLstFile, "InternalizeName: returning %p => %s\n", pcIN, pcIN); */
    
    return pcIN;
}

/****************************************************************************
 *
 *  FUNCTION:       PriUnloadNameSpace (void)
 *
 *  PARAMETERS:     none
 *
 *  RETURN:         E_OK or E_ERROR
 *
 *  DESCRIPTION:    Contracts namespace, typically in response to an undocking
 *                      event
 *
 ****************************************************************************/

INT32
PriUnloadNameSpace (void)
{
    FUNCTION_TRACE ("PriUnloadNameSpace");


    if ((nte *)0 == Root)
    {
        return E_ERROR;
    }
    
    return (E_OK);
}

/****************************************************************************
 *
 * FUNCTION:    AcpiExecuteMethod
 *
 * PARAMETERS:  char *MethodName        name of method to execute
 *              OBJECT_DESCRIPTOR       where to put method's return
 *              **ReturnValue           value (if any).
 *                                      ReturnValue must not be
 *                                      passed in as NULL because
 *                                      *ReturnValue will always
 *                                      be set (to NULL if there is
 *                                      no return value).
 *              OBJECT_DESCRIPTOR 
 *              **Params                list of parameters to pass to
 *                                      method, terminated by NULL.
 *                                      Params itself may be NULL
 *                                      if no parameters are being
 *                                      passed.
 *
 * RETURN:      E_OK or E_ERROR
 *
 * DESCRIPTION: Find and execute the requested method passing the given
 *              parameters
 *
 * ALLOCATION:
 * Reference       Size                 Pool Owner       Description
 * *ReturnValue    s(OBJECT_DESCRIPTOR) bu   CALLER      returned value
 *
 ****************************************************************************/

INT32
AcpiExecuteMethod (char * MethodName, OBJECT_DESCRIPTOR **ReturnValue,
                    OBJECT_DESCRIPTOR **Params)
{
    nte             *MethodPtr;
    INT32           RetVal;


    FUNCTION_TRACE ("AcpiExecuteMethod");


BREAKPOINT3;

    if ((OBJECT_DESCRIPTOR **) 0 != ReturnValue)
    {
        *ReturnValue = (OBJECT_DESCRIPTOR *) 0;
    }

    if ((nte *) 0 == Root)
    {
        /* 
         * If the name space has not been initialized, the Method has surely
         * not been defined and there is nothing to execute.
         */

        Why = "Name space not initialized";
        return E_ERROR;
    }

    if (MethodName[0] != '\\' || MethodName[1] != '/')
    {
        MethodName = InternalizeName (MethodName);
    }


    /* See comment near top of file re significance of FETCH_VALUES */

#ifdef FETCH_VALUES
    MethodPtr = (nte *) NsEnter (MethodName, Any, Exec);
#else 
    MethodPtr = (nte *) NsEnter (MethodName, Method, Exec);
#endif

    if (NOTFOUND == MethodPtr)
    {
        Why = "Method not found";
        return E_ERROR;
    }

#ifdef FETCH_VALUES
    if (NsValType (MethodPtr) == Method)
    {
        /* Name found is in fact a Method */
        
        if (debug_level () > 0)
        {
            LineSet (55, Exec);
            fprintf_bu (LstFileHandle, LOGFILE,
                        "[%s Method %p ptrVal %p ",
                        MethodName, MethodPtr, MethodPtr->ptrVal);

            if (MethodPtr->ptrVal)
            {
                fprintf_bu (LstFileHandle, LOGFILE,
                            "Offset %x Length %lx]",
                            ((meth *) MethodPtr->ptrVal)->Offset + 1,
                            ((meth *) MethodPtr->ptrVal)->Length - 1);
            }
            
            else
            {
                fprintf_bu(LstFileHandle, LOGFILE, "*Undefined*]");
            }
        }
#endif

        /* 
         * Here if not FETCH_VALUES (and hence only Method was looked for), or
         * FETCH_VALUES and the name found was in fact a Method.  In either
         * case, set the current scope to that of the Method, and execute it.
         */

        if (!MethodPtr->ptrVal)
        {
            Why = "Method is undefined";
            return E_ERROR;
        }

        if (Trace & TraceNames)
        {
            fprintf_bu (LstFileHandle, LOGFILE, "Set scope %s ",
                          NsFullyQualifiedName(MethodPtr->ChildScope));
        }
        
        CurrentScope = &ScopeStack[0];
        NsPushCurrentScope (MethodPtr->ChildScope, Method);
        
        if (Trace & TraceNames)
        {
            fprintf_bu (LstFileHandle, LOGFILE, "Exec Method %s ",
                          NsFullyQualifiedName (MethodPtr));
        }
        
        ClearPkgStack ();
        ObjStackTop = 0;                                           /* Clear object stack */
        RetVal = AmlExec (((meth *) MethodPtr->ptrVal)->Offset + 1,
                            ((meth *) MethodPtr->ptrVal)->Length - 1,
                            Params);

        if (debug_level () > 0 && PkgNested ())
        {
            fprintf_bu (LstFileHandle, LOGFILE,
                            "Package stack not empty at method exit");
            _Kinc_info ("0008", PACRLF, __LINE__, __FILE__, LstFileHandle, LOGFILE);
        }

        if (GetMethodDepth () > -1)
        {
            fprintf_bu (LstFileHandle, LOGFILE,
                            "Method stack not empty at method exit");
            _Kinc_error("0009", PACRLF, __LINE__, __FILE__, LstFileHandle, LOGFILE);
        }

        if (debug_level () > 0 && ObjStackTop)
        {
            INT32           SaveTrace = Trace;

            fprintf_bu (LstFileHandle, LOGFILE,
                            "Object stack not empty at method exit");
            _Kinc_info ("0010", PACRLF, __LINE__, __FILE__, LstFileHandle, LOGFILE);
            
            Trace |= TraceExec;         /* enable output from DumpStack */
            DumpStack (Exec, "Remaining Object Stack entries", -1, "");
            Trace = SaveTrace;
        }

#ifdef FETCH_VALUES
    }
    
    else
    {
        /* 
         * Here if FETCH_VALUES and the name found was not a Method.
         * Return its value.
         */
        OBJECT_DESCRIPTOR           *pOD;

        if (debug_level () > 0)
        {
            fprintf_bu (LstFileHandle, LOGFILE, "Value: ");
            NsDumpEntry (MethodPtr, LOGFILE);
        }

        pOD = NEW (OBJECT_DESCRIPTOR);
        if (pOD)
        {
            /* Construct a descriptor pointing to the name */
            
            pOD->Lvalue.ValType = (UINT8) Lvalue;
            pOD->Lvalue.OpCode = (UINT8) NameOp;
            pOD->Lvalue.Ref = (void *) MethodPtr;

            /* 
             * Put it on the stack, and use GetRvalue() to get the value.
             * Note that ObjStackTop points to the top valid entry, not to
             * the first unused position.
             */

            DeleteObject ((OBJECT_DESCRIPTOR **) &ObjStack[ObjStackTop]);
            ObjStack[ObjStackTop] = (void *) pOD;
            RetVal = GetRvalue ((OBJECT_DESCRIPTOR **) &ObjStack[ObjStackTop]);

            /* 
             * If GetRvalue() succeeded, treat the top stack entry as
             * a return value.
             */

            if (S_SUCCESS == RetVal)
            {
                RetVal = S_RETURN;
            }
        }
        
        else
        {
            Why = "AcpiExecuteMethod: Descriptor Allocation Failure";
            RetVal = S_ERROR;
        }
    }
#endif


BREAKPOINT3;

    if (S_ERROR == RetVal)
    {
        return E_ERROR;
    }
    
    else
    {
        /* 
         * If the Method returned a value and the caller provided a place
         * to store a returned value, pass back the returned value.
         */

        if (S_RETURN == RetVal)
        {
            if ((OBJECT_DESCRIPTOR **) 0 != ReturnValue)
            {
                *ReturnValue = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];
            }
            
            else
            {
                DELETE (ObjStack[ObjStackTop]);
            }
        }

        return E_OK;
    }
}


/****************************************************************************
 *
 * FUNCTION:    AcpiLoadTableInNameSpace
 *
 * PARAMETERS:  none
 *
 * RETURN:      E_OK or E_ERROR
 *
 * DESCRIPTION: Expands namespace, typically in response to a docking event
 *
 ****************************************************************************/

INT32
AcpiLoadTableInNameSpace (void)
{
    FUNCTION_TRACE ("AcpiLoadTableInNameSpace");


    if ((nte *) 0 == Root)
    {
        return E_ERROR;
    }
    
    return (E_OK);
}


/****************************************************************************
 *
 * FUNCTION:    NsOpensScope
 *
 * PARAMETERS:  NsType Type
 *
 * RETURN:      NEWSCOPE if the passed type "opens a name scope" according
 *              to the ACPI specification, else 0
 *
 ***************************************************************************/

static INT32
NsOpensScope (NsType Type)
{
    FUNCTION_TRACE ("NsOpensScope");


    if (OUTRANGE (Type, NsProperties))
    {
        fprintf_bu (LstFileHandle, LOGFILE,
                        "NsOpensScope: type code %d out of range", Type);
        _Kinc_warning ("0011", PRINT, __LINE__, __FILE__, LstFileHandle, LOGFILE);
        return 0;
    }

    return NsProperties[Type] & NEWSCOPE;
}


/****************************************************************************
 *
 *  FUNCTION:   NsLocal
 *
 *  PARAMETERS: NsType Type
 *
 *  RETURN: LOCAL if names must be found locally in objects of the
 *              passed type
 *          0 if enclosing scopes should be searched
 *
 ***************************************************************************/

static INT32
NsLocal (NsType Type)
{
    FUNCTION_TRACE ("NsLocal");


    if (OUTRANGE (Type, NsProperties))
    {
        fprintf_bu (LstFileHandle, LOGFILE,
                        "NsLocal: type code %d out of range", Type);
        _Kinc_warning ("0012", PRINT, __LINE__, __FILE__, LstFileHandle, LOGFILE);
         return 0;
    }

    return NsProperties[Type] & LOCAL;
}


/****************************************************************************
 *
 * FUNCTION:    NsValType
 *
 * PARAMETERS:  NsHandle h          Handle of nte to be examined
 *
 * RETURN:      Type field from nte whose handle is passed
 *
 ***************************************************************************/

NsType
NsValType (NsHandle h)
{
    FUNCTION_TRACE ("NsValType");


    if ((NsHandle) 0 == h)
    {
        fprintf_bu (LstFileHandle, LOGFILE, "NsValType: Null handle");
        _Kinc_warning ("0013", PRINT, __LINE__, __FILE__, LstFileHandle, LOGFILE);
        return Any;
    }

    return ((nte *) h)->NtType;
}


/****************************************************************************
 *
 * FUNCTION:    NsValPtr
 *
 * PARAMETERS:  NsHandle h              Handle of nte to be examined
 *
 * RETURN:      ptrVal field from nte whose handle is passed
 *
 ***************************************************************************/

void *
NsValPtr (NsHandle h)
{
    FUNCTION_TRACE ("NsValPtr");


    if ((NsHandle) 0 == h)
    {
        fprintf_bu (LstFileHandle, LOGFILE, "NsValPtr: Null handle");
        _Kinc_warning ("0014", PRINT, __LINE__, __FILE__, LstFileHandle, LOGFILE);
        return (void *) 0;
    }

    return ((nte *) h)->ptrVal;
}


/* 
 * XXX - Absent recursion, should not need prototype for
 * XXX - a locally-defined function; try to reorder definitions
 */
static char * NsNameOfScope (nte *Look);


/****************************************************************************
 *
 * FUNCTION:    SearchTable
 *
 * PARAMETERS:  char    *NamSeg         name segment to find or insert
 *              nte     *NameTbl        name table to search
 *              INT32   TableSiz e      # of slots in table,
 *                                      must be prime if USE_HASHING
 *              OpMode  LoadMode        Add names only in Load mode
 *              NsType  Type            Type associated with name
 *
 * RETURN:      pointer to found or added nte, or NOTFOUND
 *
 * DESCRIPTION: Search for a name segment in a single name table,
 *              optionally adding it if it is not found.  If the passed
 *              Type is not Any and the type previously stored in the
 *              entry was Any (i.e. unknown), update the stored type.
 *
 ***************************************************************************/

static nte *
SearchTable (char *NamSeg, nte *NameTbl, INT32 TableSize, 
                OpMode LoadMode, NsType Type)
{
    UINT32              Hash;     /* hashed value of name */
    UINT16              Position;      /* position in table */
    INT32               Tries;     /* number of positions not yet searched */


    FUNCTION_TRACE ("SearchTable");


    CheckTrash ("enter SearchTable");

    if ((nte *) 0 == NameTbl)
    {
        KFatalError ("0015", ("SearchTable: null scope passed"));
    }

    if (Trace & TraceNames)
    {
        fprintf_bu (LstFileHandle, LOGFILE,
                    "SearchTable: search %s [%p] for %4.4s ... ",
                    NsNameOfScope (NameTbl), NameTbl, NamSeg);
    }

    if (!NcOK ((INT32) NamSeg[0]) || !NcOK ((INT32) NamSeg[1])
     || !NcOK ((INT32) NamSeg[2]) || !NcOK ((INT32) NamSeg[3]))
    {
        sprintf (WhyBuf, "*** bad name %08lx *** ", *(UINT32 *) NamSeg);
        Why = WhyBuf;
        fprintf_bu (LstFileHandle, LOGFILE, Why)
        CheckTrash ("leave SearchTable BADNAME");
        return NOTFOUND;
    }

    if (NameTbl == Root && TableSize != ROOTSIZE
     || NameTbl != Root && TableSize != TABLSIZE)
    {
        fprintf_bu (LstFileHandle, LOGFILE, " *** NAME TABLE SIZE ERROR *** ");
        Why = "*** NAME TABLE SIZE ERROR ***";
        CheckTrash ("leave SearchTable BADSIZE");
        return NOTFOUND;
    }

    /* 
     * If USE_HASHING is turned on, name tables will be hashed; see Knuth's
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

    /* 
     * Since all name segments are exactly 4 characters,
     * just use those bits as the hash value.
     */

    Hash = *(UINT32 *) NamSeg;
    Position = (UINT16) (Hash % (UINT32) TableSize);
#else

    /* start linear search at top of table */
    
    Hash = (UINT32) 0;
    Position = (UINT16) Hash;
#endif

#ifdef NSLOGFILE
    fprintf (LogFile, "search %p size %d\n", NameTbl, TableSize);
#endif

    /* 
     * Search for name in table, starting at Position.  Stop searching upon
     * finding an unused entry or after examining all entries in the table.
     *
     * Moving to the "next" entry is done at the bottom of the loop instead
     * of in the iteration expression because the method used depends on
     * whether or not USE_HASHING is in effect.
     */

    for (Tries = TableSize; Tries && 0 != NameTbl[Position].NameSeg; --Tries)
    {
        CheckTrash ("top of SearchTable loop");
        
        if (NameTbl[Position].NameSeg == *(UINT32 *) NamSeg)
        {
            /* 
             * Found matching entry.  Capture type if appropriate before
             * returning the entry.
             */

            /* 
             * The DefFieldDefn and BankFieldDefn cases are actually
             * looking up the Region in which the field will be defined
             */

            if (DefFieldDefn == Type || BankFieldDefn == Type)
            {
                Type = Region;
            }

            /* 
             * Scope, DefAny, and IndexFieldDefn are bogus "types" which do
             * not actually have anything to do with the type of the name
             * being looked up.  For any other value of Type, if the type
             * stored in the entry is Any (i.e. unknown), save the actual type.
             */

            if (Type != Scope && Type != DefAny
             && Type != IndexFieldDefn && NameTbl[Position].NtType == Any)
            {
                NameTbl[Position].NtType = Type;
            }

            if (Trace & TraceNames)
            {
                fprintf_bu (LstFileHandle, LOGFILE, "found at %p", &NameTbl[Position]);
            }
            
            CheckTrash ("leave SearchTable FOUND");
            return &NameTbl[Position];
        }

#ifdef USE_HASHING

        /* 
         * Found position occupied by a different name, decide where to look
         * next.  The value added must be relatively prime to the table size,
         * which is most easily assured by requiring the table size to be a
         * prime number.
         *
         * Use the second character of the name as the rehash value since the
         * first character will often be '_'
         */

        Position = (Position + NamSeg[1]) % TableSize;
#else

        if (1 == Tries && NEXTSEG (NameTbl) != (nte *)0)
        {
            /* 
             * Just examined last slot, but table has an appendage.
             * All appendages, even to the root NT, contain TABLSIZE entries.
             */

            NameTbl = NEXTSEG (NameTbl);
            Position = 0;
            Tries += TABLSIZE;
        }
        
        else
        {
            ++Position;
        }
#endif
    }

    /* 
     * Name not found.  Before adding it or giving up, ACPI scope rules
     * require searching enclosing scopes in cases identified by NsLocal()
     */

    /* 
     * NameTbl[0] will be an unused entry if the table being searched is empty,
     * and will often be unused even in a non-empty table if USE_HASHING is
     * in effect; however its ParentScope member will have been filled in
     * when the table was allocated (unless it is the root name table).
     */

    if (!NsLocal (Type) && NameTbl[0].ParentScope != (nte *) 0)
    {
        INT32       Size = (NameTbl[0].ParentScope == Root) ? NsRootSize : TableSize;
        nte         *rv;


        if (Trace & TraceNames)
        {
            fprintf_bu (LstFileHandle, LOGFILE, "searching parent");
            IncIndent ();
        }

        CheckTrash ("before recursive SearchTable");
        rv = SearchTable (NamSeg, NameTbl[0].ParentScope, Size, Exec, Any);
        CheckTrash ("after  recursive SearchTable");
        
        if ((Trace & TraceNames) && (Load1 != LoadMode))
        {
            DecIndent ();
            fprintf_bu (LstFileHandle, LOGFILE, "\n");
        }
        
        if (rv != NOTFOUND)
        {
            CheckTrash ("leave SearchTable FOUND in parent");
            return rv;
        }
    }
    
    else
    {
        if (Trace & TraceNames)
        {
            if ((nte *) 0 == NameTbl[0].ParentScope)
            {
                fprintf_bu (LstFileHandle, LOGFILE, "no parent, ");
            }
            else if (NsLocal (Type))
            {
                fprintf_bu (LstFileHandle, LOGFILE,
                            "%s is local, ", NsTypeNames[Type]);
            }
        }
    }


    /* 
     * If in Load mode and table is not full, add the not-found name to the
     * table.
     */
#ifndef USE_HASHING

    if ((Load1 == LoadMode || Load == LoadMode) && 0 == Tries)
    {
        nte         *nPS = NameTbl[0].ParentScope;


        /* Allocate and chain an appendage to the filled table */
        
        NEXTSEG (NameTbl) = AllocNT (TABLSIZE);
        
        if (!NEXTSEG (NameTbl))
        {
            KFatalError ("0016", ("Name Table appendage allocation failure"));
        }

        NameTbl = NEXTSEG (NameTbl);
        NameTbl[0].ParentScope = nPS;
        Position = 0;
        Tries += TABLSIZE;
    }

#endif

    if ((Load1 == LoadMode || Load == LoadMode) && Tries > 0)
    {
        CheckTrash ("SearchTable about to add");
        NameTbl[Position].NameSeg = *(UINT32 *) NamSeg;
        NameTbl[Position].ParentScope = NameTbl[0].ParentScope;
        CheckTrash ("SearchTable added name");

        /* 
         * If adding a name with unknown type, or having to add the region in
         * order to define fields in it, we have an improper forward reference
         */

        if (Any == Type || DefFieldDefn == Type || BankFieldDefn == Type)
        {
            fprintf_bu (LstFileHandle != NO_LOG_HANDLE ? LstFileHandle : GetMasterLogHandle (),
                        LOGFILE | SCREEN, "Unknown reference in name space \"%4.4s\"",
                            NamSeg);
            _Kinc_error ("0017", PRINT, __LINE__, __FILE__,
                        LstFileHandle != NO_LOG_HANDLE ? LstFileHandle : GetMasterLogHandle(),
                        LOGFILE | SCREEN);
            LineSet (0, LoadMode);        /* start new line in listing */
        }

        /* 
         * The DefFieldDefn and BankFieldDefn cases are actually
         * looking up the Region in which the field will be defined
         */

        if (DefFieldDefn == Type || BankFieldDefn == Type)
        {
            Type = Region;
        }

        /* 
         * Scope, DefAny, and IndexFieldDefn are bogus "types" which do
         * not actually have anything to do with the type of the name
         * being looked up.  Save any other value of Type as the type of
         * the entry.
         */

        if (Type != Scope && Type != DefAny && Type != IndexFieldDefn)
        {
            NameTbl[Position].NtType = Type;
            CheckTrashA ("SearchTable added type",
                            &NameTbl[Position].NameSeg, NameTbl[Position].NameSeg, Hash,
                            &NameTbl[Position].NtType, NameTbl[Position].NtType, Type, (void *) NameTbl);
        }

        if (Trace & TraceNames)
        {
            fprintf_bu (LstFileHandle, LOGFILE,
                        "added to %p at %p", NameTbl, &NameTbl[Position]);
        }
        
        CheckTrash ("leave SearchTable ADDED");
        return &NameTbl[Position];
    }

    if (Trace & TraceNames)
    {
        fprintf_bu (LstFileHandle, LOGFILE, "not found in %p ", NameTbl);
    }
    
    CheckTrash ("leave SearchTable NOTFOUND");
    return NOTFOUND;
}


/****************************************************************************
 * 
 * FUNCTION:    NsSetup()
 *
 * PARAMETERS:  none
 *
 * DESCRIPTION: Allocate and initialize the root name table
 *
 * ALLOCATION:
 * Reference        Size                 Pool  Owner       Description
 * Root             NsRootSize*s(nte)    bu    acpinmsp    Root Name Table
 * nte.ptrVal       s(OBJECT_DESCRIPTOR) bu    acpinmsp    initialized value
 * ptrVal->String   varies               bu    acpinmsp    string value
 *
 ***************************************************************************/

void
NsSetup (void)
{
    struct InitVal          *InitVal;


    FUNCTION_TRACE ("NsSetup");


    /* 
     * Root is initially NULL, so a non-NULL value indicates
     * that NsSetup() has already been called; just return.
     */

    if (Root)
    {
        return;
    }

    NsCurrentSize = NsRootSize = ROOTSIZE;
    Root = AllocNT (NsRootSize);
    if ((nte *) 0 == Root)
    {
        KFatalError ("0018", ("root name table allocation failure"));
    }

    /* Push the root name table on the scope stack */
    
    ScopeStack[0].Scope = Root;
    ScopeStack[0].Type = Any;
    CurrentScope = &ScopeStack[0];

#ifdef NSLOGFILE
    LogFile = fopen ("ns.log", "wtc");
    fprintf (LogFile, "root = %08x size %d\n", Root, NsRootSize);
#endif

    /* Enter the pre-defined names in the name table */
    
    for (InitVal = PreDefinedNames ; InitVal->Name ; ++InitVal)
    {
        NsHandle hN = NsEnter (InitVal->Name, InitVal->Type, Load);

        /* 
         * if name entered successfully
         *  && its entry in PreDefinedNames[] specifies an initial value
         */
        
        if (hN && InitVal->Val)
        {
            /* Entry requests an initial value, allocate a descriptor for it. */
            
            OBJECT_DESCRIPTOR       *pOD = NEW (OBJECT_DESCRIPTOR);


            if ((OBJECT_DESCRIPTOR *) 0 == pOD)
            {
                KFatalError("0019", ("Initial value descriptor allocation failure"));
            }

            pOD->ValType = (UINT8) InitVal->Type;

            /* 
             * Convert value string from table entry to internal representation.
             * Only types actually used for initial values are implemented here.
             */

            switch (InitVal->Type)
            {
                case Number:
                    pOD->Number.Number = (UINT32) atol (InitVal->Val);
                    break;

                case String:
                    pOD->String.StrLen = (UINT16) strlen (InitVal->Val);

                    /* 
                     * XXX - if this malloc_bu() causes a garbage collection pass,
                     * XXX - pOD will get deleted since no NT points to it yet.
                     * XXX - This "should not happen" during initialization.
                     */

                    pOD->String.String = OsdAllocate ((size_t) (pOD->String.StrLen + 1));
                    if ((UINT8 *) 0 == pOD->String.String)
                    {
                        KFatalError ("0020", ("Initial value string allocation failure"));
                    }
                    
                    strcpy ((char *) pOD->String.String, InitVal->Val);
                    break;

                default:
                    DELETE (pOD);
                    continue;
            }

            /* Store pointer to value descriptor in nte */
            
            NsSetValue(hN, pOD, pOD->ValType);
        }
    }

#ifdef PLUMBER
    RegisterMarkingFunction (NsMarkNS);
#endif
}


/****************************************************************************
 *
 * FUNCTION:    NsPopCurrent
 *
 * PARAMETERS:  NsType Type    The type of frame to be found
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

INT32
NsPopCurrent (NsType Type)
{
    INT32           Count = 0;


    FUNCTION_TRACE ("NsPopCurrent");


    if (OUTRANGE (Type, NsTypeNames) || BadType == NsTypeNames[Type])
    {
        fprintf_bu (LstFileHandle, LOGFILE,
                        "NsPopCurrent: type code %d out of range", Type);
        _Kinc_warning ("0021", PRINT, __LINE__, __FILE__, LstFileHandle, LOGFILE);
    }

    printfd_bu (TRACE_LEVEL, "Popping Scope till type (%i) is found\n", Type);

    while (CurrentScope > &ScopeStack[0])
    {
        --CurrentScope;
        ++Count;
        printfd_bu (TRACE_LEVEL,"Popped %i ", (CurrentScope+1)->Type);

        if (Any == Type || Type == (CurrentScope + 1)->Type)
        {
            printfd_bu (TRACE_LEVEL,"Found %i\n", Type);
            return Count;
        }
    }

    printfd_bu (TRACE_LEVEL,"%i Not Found\n", Type);
    return -Count;
}


/****************************************************************************
 *
 * FUNCTION:    NsEnter
 *
 * PARAMETERS:  char    *Name       name to be entered, in internal format
 *                                  as represented in the AML stream
 *              NsType  Type        type associated with name
 *              OpMode  LoadMode    Load => add name if not found
 *
 * RETURN:      Handle to the nte for the passed name
 *
 * DESCRIPTION: Find or enter the passed name in the name space.
 *              Log an error if name not found in Exec mode.
 *
 * ALLOCATION:
 * Reference        Size                 Pool  Owner       Description
 * nte.ChildScope   TABLSIZE*s(nte)      bu    acpinmsp    Name Table
 *
 ***************************************************************************/

NsHandle
NsEnter (char *Name, NsType Type, OpMode LoadMode)
{
    nte             *Look;
    nte             *This;
    INT32           Size;
    INT32           NumSeg;
    NsType          TTCF;              /* Type To Check For */


    FUNCTION_TRACE ("NsEnter");


    if ((nte *) 0 == Root)
    {
        /* 
         * If the name space has not been initialized:
         * -  In Pass1 of Load mode, we need to initialize it
         *    before trying to define a name.
         * -  In Exec mode, there are no names to be found.
         */

        if (Load1 == LoadMode)
        {
            NsSetup ();
        }
        else
        {
            return NOTFOUND;
        }
    }

    if (Trace & TraceNames)
    {
        fprintf_bu (LstFileHandle, LOGFILE,
                    " NsEnter: %02x %02x %02x %02x %02x %02x ",
                    Name[0], Name[1], Name[2], Name[3], Name[4], Name[5]);
    }

    CheckTrash ("enter NsEnter");

    /* DefFieldDefn and BankFieldDefn define fields in a Region */
    
    if (DefFieldDefn == Type || BankFieldDefn == Type)
    {
        TTCF = Region;
    }
    else
    {
        TTCF = Type;
    }

    /* 
     * Check for prefixes.  As represented in the AML stream, a Name consists
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

    if (*Name == RootPrefix)
    {
        /* Name is fully qualified, look in root NT */
        
        if (Trace & TraceNames)
        {
            fprintf_bu (LstFileHandle, LOGFILE, "root ");
        }
        
        Look = Root;
        Size = NsRootSize;
        ++Name;   /* point to segment part */
    }
    
    else
    {
        char        *OrigName = Name;


        /* Name is relative to current scope, start there */
        
        Look = CurrentScope->Scope;
        Size = NsCurrentSize;

        while (*Name == ParentPrefix)
        {
            if (Trace & TraceNames)
            {
                fprintf_bu (LstFileHandle, LOGFILE, "parent ");
            }
            
            ++Name;                   /* point to segment part or next ParentPrefix */
            Look = Look->ParentScope;
            
            if (Look == (nte *) 0)
            {
                /* Scope has no parent */
                
                LineSet ((INT32) strlen (OrigName) + 18, LoadMode);
                fprintf_bu (LstFileHandle, LOGFILE, "*Too many ^ in <%s>*",
                            OrigName);
                _Kinc_error ("0022", PRINT, __LINE__, __FILE__, LstFileHandle, LOGFILE);
                LineSet (0, LoadMode);
                CheckTrash ("leave NsEnter NOTFOUND 1");

                return (NsHandle) NOTFOUND;
            }
        }

        if (Look->ParentScope == (nte *) 0)
        {
            /* backed up all the way to the root */
            
            Size = NsRootSize;
        }
    }

    if (*Name == DualNamePrefix)
    {
        if (Trace & TraceNames)
        {
            fprintf_bu (LstFileHandle, LOGFILE, "dual ");
        }

        NumSeg = 2;
        ++Name;   /* point to first segment */
    }
    
    else if (*Name == MultiNamePrefixOp)
    {
        if (Trace & TraceNames)
        {
            fprintf_bu (LstFileHandle, LOGFILE, "multi %d ", Name[1]);
        }
        
        NumSeg = (INT32)* (UINT8 *) ++Name;
        ++Name;                           /* point to first segment */
    }
    else
    {
        /* 
         * No Dual or Multi prefix, hence there is only one
         * segment and Name is already pointing to it.
         */
        NumSeg = 1;
    }

    if (Trace & TraceNames)
    {
        fprintf_bu (LstFileHandle, LOGFILE, "seg = %d ", NumSeg);
    }

    while (NumSeg-- && Look)
    {
#if 0
        INT32       SaveTrace = Trace;

        if (*(UINT32 *) "LDN_" == *(UINT32 *) Name)
        {
            Trace |= TraceNames;
        }
        if (*(UINT32 *) "LNKC" == *(UINT32 *) Name && Exec == LoadMode)
        {
            Trace |= TraceNames;
        }
#endif
        
        CheckTrash ("before SearchTable");
        
        /* 
         * Search for the current segment in the table where it should be.
         * Type is significant only at the last level.
         */

        This = SearchTable (Name, Look, Size, LoadMode,
                                NumSeg == 0 ? Type : Any);
        CheckTrash ("after  SearchTable");

#if 0
        if (*(UINT32 *) "LDN_" == *(UINT32 *) Name)
        {
            Trace = SaveTrace;
        }
#endif
        if (This == NOTFOUND)
        {
            if (Load1 == LoadMode || Load == LoadMode)
            {
                KFatalError ("0023", ("\nname table overflow adding %4.4s to %s",
                                Name, NsFullyQualifiedName(Look)));
            }

            else
            {
                fprintf_bu (LstFileHandle, LOGFILE,
                            "name %4.4s not found in %s",
                            Name, NsFullyQualifiedName(Look));
                _Kinc_error ("0024", PACRLF, __LINE__, __FILE__, LstFileHandle, LOGFILE);
            }

            CheckTrash ("leave NsEnter NOTFOUND 2");
            return (NsHandle) NOTFOUND;
        }

        if (0 == NumSeg                    /* if last segment                  */
         && TTCF != Any                    /* and looking for a specific type  */
         && TTCF != DefAny                 /* which is not a phoney type       */
         && TTCF != Scope                  /*   "   "   "  "   "     "         */
         && TTCF != IndexFieldDefn         /*   "   "   "  "   "     "         */
         && This->NtType != Any           /* and type of entry is known       */
         && This->NtType != TTCF)        /* and entry does not match request */
        {                                   /* complain.                        */
            
            fprintf_bu (LstFileHandle, LOGFILE,
                        "Type mismatch, wanted %s, found %s\n",
                        NsTypeNames[TTCF], NsTypeNames[This->NtType]);
            _Kinc_warning ("0025", PACRLF, __LINE__, __FILE__, LstFileHandle, LOGFILE);
        }

        /*
         * If last segment and not looking for a specific type, but type of
         * found entry is known, use that type to see if it opens a scope.
         */

        if (0 == NumSeg && Any == Type)
        {
            Type = This->NtType;
        }

        /* 
         * If there are more segments or the type implies that there should
         * be an enclosed scope, and the next scope has not been allocated ...
         */

        if ((NumSeg || NsOpensScope (Type))
         && This->ChildScope == (nte *) 0)
        {
            if (Load1 == LoadMode || Load == LoadMode)
            {
                /* Allocate the next scope */
                
                if (Trace & TraceNames)
                {
                    fprintf_bu (LstFileHandle, LOGFILE, "add level ");
                }

                This->ChildScope = AllocNT(TABLSIZE);
            }

            /* Now complain if there is no next scope */
            
            if (This->ChildScope == (nte *) 0)
            {
                if (Load1 == LoadMode || Load == LoadMode)
                {
                    KFatalError ("0026", ("Name Table allocation failure"));
                }
                else
                {
                    fprintf_bu (LstFileHandle, LOGFILE, " Name not found");
                }
                
                _Kinc_error ("0027", PACRLF, __LINE__, __FILE__, LstFileHandle, LOGFILE);
                CheckTrash ("leave NsEnter NOTFOUND 3");
                
                return (NsHandle) NOTFOUND;
            }

#ifdef NSLOGFILE
            fprintf (LogFile, "%s = %08x size %d\n",
                        Name, This->ChildScope, TABLSIZE);
#endif
            if (Load1 == LoadMode || Load == LoadMode)
            {
                /* Set newly-created child scope's parent scope */
                
                This->ChildScope->ParentScope = Look;
            }
        }

        Size = TABLSIZE;
        Look = This->ChildScope;
        Name += 4;                        /* point to next name segment */
    }

    /* 
     * If entry is a type which opens a scope,
     * push the new scope on the scope stack.
     */

    if (NsOpensScope (TTCF))
    {
        CheckTrash ("before NsPushCurrentScope");
        NsPushCurrentScope (This->ChildScope, Type);
        CheckTrash ("after  NsPushCurrentScope");
    }

    return (NsHandle) This;
}


/****************************************************************************
 *
 * FUNCTION:    GetParentHandle(NsHandle Look)
 *
 * PARAMETERS:  NsHandle Look -    Handle whose parent is to be returned
 *
 * RETURN:      Parent of parameter. NOTFOUND if Look is invalid
 *              or Look refers to the root.
 *
 ***************************************************************************/

 NsHandle GetParentHandle(NsHandle LookHdl)
{
    nte             *Look;
    nte             *This;
    nte             *NextSeg;
    INT32           Size;


    FUNCTION_TRACE ("GetParentHandle");


    if (LookHdl == (NsHandle)0 || ((nte *) LookHdl)->ParentScope == (nte *) 0)
    {
        return NOTFOUND;
    }

    /* Look for the handle passed as a parameter */
    
    Look = (nte *) LookHdl;

    /* Look in its parent scope */
    
    This = Look->ParentScope;

    /* Locate appendage, if any, before losing original scope pointer */
    
    NextSeg = NEXTSEG (This);

    /* For every entry in the parent scope */
    
    for (Size = (This == Root ? NsRootSize : TABLSIZE) ; Size ; --Size)
    {
        /* 
         * If the entry's ChildScope segment matches our segment
         * and our offset is within the ChildScope's range
         * XXX - BUG - This only checks for us being in the prospective parent's
         * XXX - BUG - initial extent.  It won't work if we are in an appendage.
         */

/* !!!! REMOVED FOR FLAT MODEL.
      if (sPtrSelector(This->ChildScope) == sPtrSelector(Look)
*/
            
        if (This->ChildScope <= Look
         && Look < This->ChildScope + TABLSIZE)
        {
            /* Return the matching entry */
            
            return (NsHandle) This;
        }

        if (1 == Size && NextSeg)
        {
            /* Just examined last entry, but table has an appendage.  */
            
            This = NextSeg;
            Size += TABLSIZE;
            NextSeg = NEXTSEG(This);
        }
        
        else
        {
            ++This;    /* next entry in parent scope */
        }
    }

    return NOTFOUND;
}


/****************************************************************************
 *
 * FUNCTION:    FindParentName
 *
 * PARAMETERS:  nte *Look          nte whose name is to be found
 *
 * RETURN:      pointer to the name
 *
 * DESCRIPTION: Search for the given nte in its parent scope and return the
 *              name segment, or "????" if the parent name can't be found
 *              (which "should not happen").
 *
 ***************************************************************************/

static char *
FindParentName (nte *Look, INT32 Trace)
{
    NsHandle            hParent = GetParentHandle (Look);


    FUNCTION_TRACE ("FindParentName");


    if (NOTFOUND != hParent)
    {
        nte         *nParent = (nte *) hParent;

        if (Trace)
        {
            fprintf_bu (LstFileHandle, LOGFILE, "%p->", nParent);
        }

        if (nParent->NameSeg)
        {
            return (char *) &nParent->NameSeg;
        }
    }

    return "????";
}


/****************************************************************************
 *
 * FUNCTION:    NsNameOfScope
 *
 * PARAMETERS:  nte *Look          Scope whose name is needed
 *
 * RETURN:      Pointer to storage containing the fully qualified name of
 *              the scope, in Label format (all segments strung together
 *              with no separators)
 *
 * DESCRIPTION: Used via NsNameOfCurrentScope() and pcLastFQN()
 *              for label generation in amlscan.c, and for debug
 *              printing in SearchTable().
 *
 * ALLOCATION:
 * Reference      Size                 Pool  Owner       Description
 * pcFQN{sl}      iFQNsiz{sl:HWM}      bu    acpinmsp    Name of Scope
 *
 ***************************************************************************/

static char *
NsNameOfScope (nte *Look)
{
    nte                 *Temp;
    static char         *pcFQN = (char *) 0;
    static size_t       iFQNsiz = 0;
    size_t              Size;


    FUNCTION_TRACE ("NsNameOfScope");


    if ((nte *) 0 == Root || (nte *)0 == Look)
    {
        /* 
         * If the name space has not been initialized,
         * this function should not have been called.
         */
        return (char *) 0;
    }

    /* Calculate required buffer size based on depth below root NT */
    
    for (Size = 1, Temp = Look;
            Temp->ParentScope;
            Temp = Temp->ParentScope)
    {
        Size += 4;
    }

    if (iFQNsiz < Size + 1)
    {
        /* Current buffer is too small; release it and allocate a larger one */
        
        if (pcFQN != (char *) 0)
        {
            OsdFree (pcFQN);
        }
        else
        {
            RegisterStaticBlockPtr (&pcFQN);
        }

        pcFQN = OsdCallocate (1, Size + 1);
        if ((char *) 0 == pcFQN)
        {
            KFatalError("0028", ("NsNameOfScope: allocation failure"));
        }
        
        iFQNsiz = Size + 1;
    }

    /* Store terminator byte, then build name backwards */
    
    pcFQN[Size] = '\0';
    while (Size > 4 && Look->ParentScope != (nte *) 0)
    {
        Size -= 4;
        *(UINT32 *) (pcFQN + Size) = *(UINT32 *) FindParentName (Look, 0);
        Look = Look->ParentScope;
    }

    pcFQN[--Size] = RootPrefix;
    return &pcFQN[Size];
}


/****************************************************************************
 *
 * FUNCTION:    NsNameOfCurrentScope()
 *
 * PARAMETERS:  none
 *
 * RETURN:      pointer to storage containing the name of the current scope
 *
 ***************************************************************************/

char *
NsNameOfCurrentScope (void)
{
    FUNCTION_TRACE ("NsNameOfCurrentScope");


    if (CurrentScope && CurrentScope->Scope)
    {
        return NsNameOfScope (CurrentScope->Scope);
    }
    
    KFatalError ("0029", ("Current scope pointer trashed"));
    return (char *) 0;
}


/****************************************************************************
 *
 * FUNCTION:    NsFullyQualifiedName
 *
 * PARAMETERS:  NsHandle Look          handle of nte whose name is to be found
 *
 * RETURN:      pointer to storage containing the name, in external format
 *
 * DESCRIPTION:
 *
 * ALLOCATION:
 * Reference      Size                 Pool  Owner       Description
 * pcFQN{sl}      iFQNsiz{sl:HWM}      bu    acpinmsp    Name of handle
 *
 ***************************************************************************/

char *
NsFullyQualifiedName (NsHandle LookHdl)
{
    nte                 *Look = (nte *) LookHdl;
    nte                 *Temp;
    static char         *pcFQN = (char *) 0;
    static size_t       iFQNsiz = 0;
    size_t              Size;
    INT32               TraceFQN = 0;


    FUNCTION_TRACE ("NsFullyQualifiedName");


    if ((nte *) 0 == Root || (nte *) 0 == Look)
    {
        /* 
         * If the name space has not been initialized,
         * this function should not have been called.
         */

        return (char *) 0;
    }

    /* Compute length of FQN as 5 * number of segments */
    
    for (Size = 5, Temp = Look;
          Temp->ParentScope;
          Temp = Temp->ParentScope)
    {
        Size += 5;
    }
    
    if (iFQNsiz < Size + 1)
    {
        if (pcFQN != (char *) 0)
        {
            OsdFree (pcFQN);
        }
        
        else
        {
            RegisterStaticBlockPtr (&pcFQN);
        }
        
        pcFQN = OsdCallocate (1, Size + 1);
        if ((char *) 0 == pcFQN)
        {
            KFatalError ("0030", ("NsFullyQualifiedName: allocation failure"));
        }
        iFQNsiz = Size + 1;
    }

#if 0
    
    /* Debug hack: if dealing with segment "_PSC" turn on tracing */
    
    if (0x4353505f == Look->NameSeg)
    {
        TraceFQN = 1;
        fprintf_bu (LstFileHandle, LOGFILE,
                    "NsFQN: nte @ %p, name %08lx, parent @ %p, SizeOfFQN = %d ",
                    Look, Look->NameSeg, Look->ParentScope, Size);
    }
#endif

    /* Store null termination */
    
    pcFQN[Size] = '\0';
    Size -= 4;
    
    if (TraceFQN)
    {
        fprintf_bu (LstFileHandle, LOGFILE,
                        "%d:%08lx ", Size, Look->NameSeg);
    }
    
    *(UINT32 *) (pcFQN + Size) = Look->NameSeg;
    pcFQN[--Size] = '.';

    /* Build name backwards, putting "." between segments */
    
    while (Size > 4 && Look != (nte *) 0)
    {
        Size -= 4;
        *(UINT32 *) (pcFQN + Size) = *(UINT32 *) FindParentName (Look, TraceFQN);
        
        if (TraceFQN)
        {
            fprintf_bu (LstFileHandle, LOGFILE,
                            "%d:%08lx ", Size, *(UINT32 *)(pcFQN + Size));
        }
        pcFQN[--Size] = '.';
        Look = Look->ParentScope;
    }

    /* Overlay the "." preceding the first segment with root name "\" */
    
    pcFQN[Size] = '\\';
    return &pcFQN[Size];
}


/****************************************************************************
 *
 * FUNCTION:    NsSetMethod
 *
 * PARAMETERS:  NsHandle    h           handle of nte to be set
 *              ptrdiff_t   Offset      value to be set
 *              long        Length      length associated with value
 *
 * DESCRIPTION: Record the given offset and p-code length of the method
 *              whose handle is passed
 *
 * ALLOCATION:
 * Reference      Size                 Pool  Owner       Description
 * nte.ptrVal     s(meth)              bu    acpinmsp    Method AML descrip
 *
 ***************************************************************************/

void
NsSetMethod (NsHandle h, ptrdiff_t Offset, INT32 Length)
{
    meth            *pM = NEW (meth);


    FUNCTION_TRACE ("NsSetMethod");


    if ((meth *) 0 == pM)
    {
        KFatalError ("0031", ("NsSetMethod: allocation failure"));
    }
    
    if ((nte *) 0 == Root)
    {
        KFatalError ("0032", ("NsSetMethod: name space not initialized"));
    }
    
    if ((NsHandle) 0 == h)
    {
        KFatalError ("0033", ("NsSetMethod: null name handle"));
    }

    pM->Offset = Offset;
    pM->Length = Length;
    
    ((nte *) h)->ptrVal = (void *) pM;

#if 0
    LineSet (55, Load);
    fprintf_bu (LstFileHandle, LOGFILE,
                    "[Method %p ptrVal %p Offset %x Length %lx]",
                    h, pM, pM->Offset, pM->Length);
#endif
}


/****************************************************************************
 *
 * FUNCTION:    NsSetValue
 *
 * PARAMETERS:  NsHandle            hN          handle of nte to be set
 *              ACPI_OBJECT_HANDLE  hV          value to be set
 *              UINT8               ValType     type of value,
 *                                              or Any if not known
 *
 * DESCRIPTION: Record the given object as the value associated with the
 *              name whose NsHandle is passed.  If hV is NULL and ValType
 *              is Any, set the name as having no value.
 *
 * ALLOCATION:  This function must not call NEW() or [mc]alloc_bu because
 *              some of its callers require that no garbage collection
 *              happen during it.
 *
 ***************************************************************************/

void
NsSetValue (NsHandle hN, ACPI_OBJECT_HANDLE hV, UINT8 ValType)
{
    void                *Temp;


    FUNCTION_TRACE ("NsSetValue");


    if ((nte *) 0 == Root)
    {
        KFatalError ("0034", ("NsSetValue: name space not initialized"));
    }
    
    if ((NsHandle) 0 == hN)
    {
        KFatalError ("0035", ("NsSetValue: null name handle"));
    }
    
    if ((ACPI_OBJECT_HANDLE) 0 == hV && Any != ValType)
    {
        KFatalError ("0036", ("NsSetValue: null value handle"));
    }
    
    if (!IsNsHandle (hN))
    {
        KFatalError ("0037", ("NsSetValue: \"name handle\" param isn't a name handle"));
    }

    /* 
     * Delete the old value.  Must set the ptrVal field to NULL first
     * so that DeleteObject() doesn't find the descriptor reachable.
     */
    
    Temp = ((nte *) hN)->ptrVal;
    ((nte *) hN)->ptrVal = (void *) 0;
    DeleteObject ((OBJECT_DESCRIPTOR **) &Temp);

    /* If the new value is NULL, done */
    
    if ((ACPI_OBJECT_HANDLE) 0 == hV && Any == ValType)
    {
        ((nte *) hN)->NtType = (NsType) ValType;
        return;
    }

    /* Set the new value */
    
    ((nte *) hN)->ptrVal = hV;

    /* Set the type if given, or if it can be discerned */
    
    if (Any != ValType)
    {
        ((nte *) hN)->NtType = (NsType) ValType;
    }
    
    else if (IsInPCodeBlock ((UINT8 *) hV))
    {
        /* hV points into the AML stream.  Check for a recognized OpCode */
        
        switch (*(UINT8 *) hV)
        {
            case OpPrefix:
                if (*(UINT16 *) hV != RevisionOp)
                {
                    /* OpPrefix is unrecognized unless part of RevisionOp */
                    
                    break;
                }

            /* else fall through to set type as Number */
            
            case ZeroOp: case OnesOp: case OneOp:
            case ByteOp: case WordOp: case DWordOp:
                ((nte *) hN)->NtType = Number;
                break;

            case StringOp:
                ((nte *) hN)->NtType = String;
                break;

            case BufferOp:
                ((nte *) hN)->NtType = Buffer;
                break;

            case PackageOp:
                ((nte *) hN)->NtType = Package;
                break;

            default:
                break;
        }
    }

    else if (IsNsHandle (hV) && ((nte *) hV)->ptrVal != (void *) 0)
    {
        /* 
         * Value passed is a name handle and that name has a non-null value.
         * Use that name's value and type.
         */

        NsSetValue(hN, ((nte *) hV)->ptrVal, (UINT8) ((nte *) hV)->NtType);
    }
    
    else
    {
        /* 
         * Cannot figure out the type -- set to DefAny which will print as an
         * error in the name table dump
         */

        if (debug_level () > 0)
        {
            fprintf_bu (LstFileHandle, LOGFILE,
                        "NsSetValue:confused:setting bogus type for %s from ",
                        NsFullyQualifiedName (hN));

            if (IsInPCodeBlock((UINT8 *)hV))
            {
                fprintf_bu (LstFileHandle, LOGFILE,
                            "AML-stream code %02x\n", *(UINT8 *) hV);
            }
            
            else if (IsNsHandle (hV))
            {
                fprintf_bu (LstFileHandle, LOGFILE,
                            "name %s\n", NsFullyQualifiedName (hV));
            }
            
            else
            {
                fprintf_bu (LstFileHandle, LOGFILE,
                            "object %p:", NsFullyQualifiedName (hV));
                DumpStackEntry (hV);
            }
        }

        ((nte *) hN)->NtType = DefAny;
    }
}


/****************************************************************************
 * 
 * FUNCTION:    ExistDownstreamSibling
 *
 * PARAMETERS:  nte     *This           pointer to first nte to examine
 *              INT32   Size            # of entries remaining in table
 *              nte     *NextSeg        addr of NT's appendage, or NULL
 *
 * RETURN:      TRUE if sibling is found, FALSE otherwise
 *
 * DESCRIPTION: Searches remainder of scope being processed to determine
 *              whether there is a downstream sibling to the current
 *              object.  This function is used to determine what type of
 *              line drawing character to use when displaying namespace
 *              trees.
 *
 ***************************************************************************/

static INT32
ExistDownstreamSibling (nte *This, INT32 Size, nte *NextSeg)
{

    FUNCTION_TRACE ("ExistDownstreamSibling");


    if ((nte *) 0 == This)
    {
        return FALSE;
    }

    if (0 == Size && NextSeg)
    {
        /* Trying to examine (last entry + 1), but table has an appendage.  */
        
        This = NextSeg;
        Size += TABLSIZE;
        NextSeg = NEXTSEG (This);
    }

    while (Size--)
    {
        if (This->NameSeg)
        {
            return TRUE;
        }
        
        if (0 == Size && NextSeg)
        {
            /* Just examined last entry, but table has an appendage.  */
            
            This = NextSeg;
            Size += TABLSIZE;
            NextSeg = NEXTSEG (This);
        }
        
        else
        {
            ++This;
        }
    }

    return FALSE;
}


/****************************************************************************
 * 
 * FUNCTION:    NsDumpTable
 *
 * PARAMETERS:  nte *This                   table to be dumped
 *              INT32 Size                  size of table
 *              INT32 Level                 Number of ancestor levels
 *              INT32 DisplayBitFlags       See description in NsDumpTables()
 *              INT32 UseGraphicCharSet     See description in NsDumpTables()
 *              INT32 MaxDepth              See description in NsDumpTables()
 *
 * DESCRIPTION: Dump a name table and its descendents
 *
 ***************************************************************************/

static void
NsDumpTable (nte *This, INT32 Size, INT32 Level, INT32 DisplayBitFlags,
                INT32 UseGraphicCharSet, INT32 MaxDepth)
{
    nte                 *NextSeg;
    static UINT32       DownstreamSiblingMask = 0;


    FUNCTION_TRACE ("NsDumpTable");


    if (0 == MaxDepth || (nte *)0 == This)
    {
        /* reached requested depth, or nothing to dump */
        
        return;
    }

    if (TRACE)
    {
        fprintf_bu (LstFileHandle, LOGFILE,
                    "enter NsDumpTable (%p, %d, %d, %d, %d)\n                   %p",
                    This, Size, Level, DisplayBitFlags, UseGraphicCharSet,
                    This->NameSeg);
    }


    /* Locate appendage, if any, before losing original scope pointer */
    
    if (1 == Size)
    {
        NextSeg = (nte *) 0;
    }
    else
    {
        NextSeg = NEXTSEG (This);
    }


    /* for each entry in table */
    
    while (Size--)
    {
        if (This->NameSeg)
        {
            /* non-empty entry */
            
            INT32           LevelTmp              = Level;
            NsType          Type           = This->NtType;
            UINT32          WhichBit   = 1;

            /* print appropriate graphic characters to form tree structure */
            
            while (LevelTmp--)
            {
                if (LevelTmp)
                {
                    if (DownstreamSiblingMask & WhichBit)
                    {    
                        fprintf_bu (LstFileHandle, DisplayBitFlags & OUTPUT_DATA,
                                    UseGraphicCharSet ? "³  " : "|  ");
                    }
                    
                    else
                    {
                        fprintf_bu (LstFileHandle, DisplayBitFlags & OUTPUT_DATA,
                                    "   ");
                    }
                    
                    WhichBit <<= 1;
                }
                
                else
                {
                    if (ExistDownstreamSibling (This + 1, Size, NextSeg))
                    {
                        DownstreamSiblingMask |= (1 << (Level - 1));
                        fprintf_bu (LstFileHandle, DisplayBitFlags & OUTPUT_DATA,
                                    UseGraphicCharSet ? "ÃÄÄ" : "+--");
                    }
                    
                    else
                    {
                        DownstreamSiblingMask &= 0xffffffff ^ (1 << (Level - 1));
                        fprintf_bu (LstFileHandle, DisplayBitFlags & OUTPUT_DATA,
                                    UseGraphicCharSet ? "ÀÄÄ" : "+--");
                    }

                    if (This->ChildScope == NULL)
                    {
                        fprintf_bu (LstFileHandle, DisplayBitFlags & OUTPUT_DATA,
                                    UseGraphicCharSet ? "Ä " : "- ");
                    }
                    
                    else if (ExistDownstreamSibling (This->ChildScope, TABLSIZE,
                                                        NEXTSEG (This->ChildScope)))
                    {
                        fprintf_bu (LstFileHandle, DisplayBitFlags & OUTPUT_DATA,
                                    UseGraphicCharSet ? "Â " : "+ ");
                    }
                    
                    else
                    {
                        fprintf_bu (LstFileHandle, DisplayBitFlags & OUTPUT_DATA,
                                    UseGraphicCharSet ? "Ä " : "- ");
                    }
                }
            }

            if (OUTRANGE (Type, NsTypeNames))
            {
                Type = DefAny;                                 /* prints as *ERROR* */
            }
            
            if (!NcOK ((INT32)* (char *) &This->NameSeg))
            {
                fprintf_bu (LstFileHandle, LOGFILE,
                            "*** bad name %08lx at %p *** ", This->NameSeg, This);
                _Kinc_error ("0038", PACRLF, __LINE__, __FILE__, LstFileHandle, LOGFILE);
            }

            if (Method == Type && This->ptrVal != (void *)0)
            {
                /* name is a Method and its AML offset/length are set */
                
                if (debug_level () > 0)
                {
                    fprintf_bu (LstFileHandle, LOGFILE, "%p: ", This);
                }
                
                fprintf_bu (LstFileHandle, LOGFILE, "%4.4s [%s %04x:%04lx]",
                            &This->NameSeg, NsTypeNames[Type],
                            ((meth *) This->ptrVal)->Offset,
                            ((meth *) This->ptrVal)->Length);
                
                if (debug_level() > 0)
                {
                    fprintf_bu(LstFileHandle, LOGFILE, " C:%p P:%p",
                            This->ChildScope, This->ParentScope);
                }

                /* fprintf_bu(LstFileHandle, LOGFILE, "\n"); */
            }
            
            else
            {
                /* name is not a Method, or the AML offset/length are not set */
                
                UINT8           *Value = This->ptrVal;


                if (debug_level () > 0)
                {
                    fprintf_bu (LstFileHandle, LOGFILE, "%p: ", This);
                }
                
                fprintf_bu (LstFileHandle, LOGFILE,
                            "%4.4s [%s]", &This->NameSeg, NsTypeNames[Type]);
                
                if (debug_level() > 0)
                {
                    fprintf_bu(LstFileHandle, LOGFILE, " C:%p P:%p V:%p",
                            This->ChildScope, This->ParentScope, This->ptrVal);
                }

                /* fprintf_bu(LstFileHandle, LOGFILE, "\n");a*/
#if 0
                /* debug code used to show parents */
                
                if (IndexField == Type && 0 == Size && 0 == Level
                 && This->ParentScope)
                {
                    fprintf_bu (LstFileHandle, LOGFILE, "  in ");
                    ++TRACE;
                    fprintf_bu (LstFileHandle, LOGFILE,
                                "call NsDumpEntry %p\n", This->ParentScope);
                    
                    NsDumpEntry ((NsHandle) This->ParentScope, DisplayBitFlags);
                    fprintf_bu (LstFileHandle, LOGFILE,
                                "ret from NsDumpEntry %p\n", This->ParentScope);
                    --TRACE;
                }
#endif
                /* if debug turned on, display values */
                
                while (Value && debug_level () > 0)
                {
                    UINT8               bT = ((OBJECT_DESCRIPTOR *) Value)->ValType;


                    fprintf_bu (LstFileHandle, LOGFILE,
                                "                 %p  %02x %02x %02x %02x %02x %02x",
                                Value, Value[0], Value[1], Value[2], Value[3], Value[4],
                                Value[5]);
                    fprintf_bu  (LstFileHandle, LOGFILE,
                                " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n",
                                Value[6], Value[7], Value[8], Value[9], Value[10],
                                Value[11], Value[12], Value[13], Value[14], Value[15]);
                    
                    if (bT == String || bT == Buffer || bT == Package
                     || bT == FieldUnit || bT == DefField || bT == BankField
                     || bT == IndexField || bT == Lvalue)
                    {
                        /* 
                         * Get pointer to next level.  This assumes that all of
                         * the above-listed variants of OBJECT_DESCRIPTOR have
                         * compatible mappings.
                         */
                        Value = ((OBJECT_DESCRIPTOR *)Value)->Buffer.Buffer;
                    }
                    else
                    {
                        break;
                    }
                }
            }

            if (This->ChildScope && MaxDepth > 1)
            {
                /* dump next scope level */
                
                NsDumpTable (This->ChildScope, TABLSIZE, Level+1,
                                DisplayBitFlags, UseGraphicCharSet, MaxDepth - 1);
            }
        }

        if (0 == Size && NextSeg)
        {
            /* Just examined last entry, but table has an appendage.  */
            
            This = NextSeg;
            Size += TABLSIZE;
            NextSeg = NEXTSEG (This);
        }
        else
        {
            ++This;
        }
    }

    if (TRACE)
    {
        fprintf_bu (LstFileHandle, LOGFILE, "leave NsDumpTable %p", This);
    }
}


/****************************************************************************
 * 
 * FUNCTION:    NsDumpTables
 *
 * PARAMETERS:  INT32 DisplayBitFlags       See definitions of OUTPUT_DATA
 *                                          and related symbols in display.h
 *              INT32 UseGraphicCharSet     1 => use graphic character set to
 *                                          draw links in name space tree
 *                                          0 => use +, -, and | to draw links
 *              NsHandle SearchBase         Root of subtree to be dumped, or
 *                                          NS_ALL to dump the entire namespace
 *              INT32   MaxDepth            Maximum depth of dump.  Use INT_MAX
 *                                          for an effectively unlimited depth.
 *
 * DESCRIPTION: Dump the name space, or a portion of it.
 *
 ***************************************************************************/

void
NsDumpTables (INT32 DisplayBitFlags, INT32 UseGraphicCharSet,
                NsHandle SearchBase, INT32 MaxDepth)
{

    FUNCTION_TRACE ("NsDumpTables");


    if ((nte *) 0 == Root)
    {      
        /* 
         * If the name space has not been initialized,
         * there is nothing to dump.
         */
        return;
    }

    if (NS_ALL == SearchBase)
    {
        SearchBase = Root;
        fprintf_bu (LstFileHandle, LOGFILE, "\\");
    }

    NsDumpTable (SearchBase, SearchBase == Root ? NsRootSize : TABLSIZE,
                    1, DisplayBitFlags, UseGraphicCharSet, MaxDepth);
}


/****************************************************************************
 *
 * FUNCTION:    NsDumpEntry    
 *
 * PARAMETERS:  NsHandle h          Entry to be dumped
 *
 * DESCRIPTION: Dump a single nte
 *
 ***************************************************************************/

void
NsDumpEntry (NsHandle h, INT32 DisplayBitFlags)
{

    FUNCTION_TRACE ("NsDumpEntry");


    if (TRACE)
    {
        fprintf_bu (LstFileHandle, LOGFILE, "enter NsDumpEntry %p", h);
    }
    
    NsDumpTable ((nte *) h, 1, 0, DisplayBitFlags, 0, 1);
    
    if (TRACE)
    {
        fprintf_bu (LstFileHandle, LOGFILE, "leave NsDumpEntry %p", h);
    }
}


/****************************************************************************
 * 
 * FUNCTION:    InternalNsFindNames
 *
 * PARAMETERS:  nte         *This           table to be searched
 *              INT32        Size           size of table
 *              char        *SearchFor      pattern to be found.
 *                                          4 bytes, ? matches any character.
 *              INT32       *Count          output count of matches found.
 *                                          Outermost caller should preset to 0
 *              NsHandle     List[]         output array of handles.  If
 *                                          null, only the count is obtained.
 *              INT32        MaxDepth       Maximum depth of search.  Use
 *                                          INT_MAX for an effectively
 *                                          unlimited depth.
 *
 * DESCRIPTION: Traverse the name space finding names which match a search
 *              pattern, and return an array of handles in List[].
 *
 ***************************************************************************/

#define BYTES_PER_SEGMENT 4

static void
InternalNsFindNames (nte *This, INT32 Size, char *SearchFor,
                        INT32 *Count, NsHandle List[], INT32 MaxDepth)
{
    nte             *NextSeg;


    FUNCTION_TRACE ("NsFindNames");


    if (0 == MaxDepth || (nte *) 0 == This
     || (char *) 0 == SearchFor || (INT32 *) 0 == Count)
    {
        /* 
         * Reached requested depth, nothing to search,
         * nothing to search for, or count pointer bad 
         */
        
        return;
    }

    /* Locate appendage, if any, before losing original scope pointer */
    
    NextSeg = NEXTSEG (This);

    /* Loop over entries in NT */
    
    while (Size--)
    {
        if (This->NameSeg)
        {
            /* non-empty entry */
            
            INT32           i;

            for (i = 0; i < BYTES_PER_SEGMENT; ++i)
            {
                if (SearchFor[i] != '?'
                 && SearchFor[i] != ((char *) &This->NameSeg)[i])
                {
                    break;
                }
            }

            if (BYTES_PER_SEGMENT == i)
            {
                /* name matches pattern */
                
                if (List)
                {
                    List[*Count] = (NsHandle) This;
                }
                
                ++*Count;
            }

            if (This->ChildScope)
            {
                InternalNsFindNames (This->ChildScope, TABLSIZE, SearchFor,
                                 Count, List, MaxDepth - 1);
            }
        }

        if (0 == Size && NextSeg)
        {
            /* Just examined last entry, but table has an appendage.  */
            
            This = NextSeg;
            Size += TABLSIZE;
            NextSeg = NEXTSEG (This);
        }
        else
        {
            ++This;
        }
    }

    if (List)
    {
        /* null-terminate the output array */
        
        List[*Count] = (NsHandle) 0;
    }
}


/****************************************************************************
 *
 * FUNCTION:    NsFindNames
 *
 * PARAMETERS:  char        *SearchFor      pattern to be found.
 *                                          4 bytes, ? matches any character.
 *                                          If NULL, "????" will be used.
 *              NsHandle    SearchBase      Root of subtree to be searched, or
 *                                          NS_ALL to search the entire namespace
 *              INT32       MaxDepth        Maximum depth of search.  Use INT_MAX
 *                                          for an effectively unlimited depth.
 *
 * DESCRIPTION: Traverse the name space finding names which match a search
 *              pattern, and return an array of handles.  The end of the
 *              array is marked by the value (NsHandle)0.  A return value
 *              of (NsHandle *)0 indicates that no matching names were
 *              found or that space for the list could not be allocated.
 *              if SearchBase is NS_ALL (null) search from the root,
 *              else it is a handle whose children are to be searched.
 *
 * ALLOCATION:
 * Reference      Size                 Pool  Owner       Description
 * RETURNED       #*s(NsHandle)        bu    CALLER      Array of NsHandle
 *
 ***************************************************************************/

NsHandle *
NsFindNames (char *SearchFor, NsHandle SearchBase, INT32 MaxDepth)
{
    NsHandle            *List;
    INT32               Count;
    INT32               BaseSize;


    FUNCTION_TRACE ("NsFindNames");


    if ((nte *) 0 == Root)
    {
        /* 
         * If the name space has not been initialized,
         * there surely are no matching names.
         */

        return (NsHandle *) 0;
    }

    if (NS_ALL == SearchBase)
    {
        SearchBase = Root;
    }
    
    else if ((NsHandle) 0 != ((nte *) SearchBase)->ChildScope)
    {
        SearchBase = ((nte *) SearchBase)->ChildScope;
    }
    
    else
    {
        /* 
         * If base is not the root and has no children,
         * there is nothing to search.
         */

        return (NsHandle *) 0;
    }

    if (SearchBase == Root)
    {
        BaseSize = NsRootSize;
    }
    
    else
    {
        BaseSize = TABLSIZE;
    }

    if ((char *)0 == SearchFor)
    {
        SearchFor = "????";
    }

    
    /* Pass 1.  Get required buffer size, don't try to build list */
    
    Count = 0;
    CheckTrash ("NsFindNames before count");
    InternalNsFindNames (SearchBase, BaseSize, SearchFor, &Count, (NsHandle *)0,
                    MaxDepth);
    CheckTrash ("NsFindNames after count");
    
    if (0 == Count)
    {
        return (NsHandle *) 0;
    }

    ++Count;               /* Allow for trailing null */
    List = (NsHandle *) OsdCallocate ((size_t)Count, sizeof(NsHandle));
    if ((NsHandle *) 0 == List)
    {
        KFatalError("0039", ("NsFindNames: allocation failure"));
    }

    /* Pass 2.  Fill buffer */
    
    Count = 0;
    CheckTrash ("NsFindNames before list");
    InternalNsFindNames (SearchBase, BaseSize, SearchFor, &Count, List,
                    MaxDepth);
    CheckTrash ("NsFindNames after list");

    return List;
}


/****************************************************************************
 *
 * FUNCTION:    NsGetHandle
 *
 * PARAMETERS:  char        *Name       Name to be found, in external (ASL)
 *                                      format.  The \ and ^ prefixes, and the
 *                                      . to separate segments, are supported.
 *
 *              NsHandle    Scope       Root of subtree to be searched, or
 *                                      NS_ALL for the root of the name space.
 *                                      If Name is fully qualified (first char
 *                                      is '\'), the passed value of Scope will
 *                                      not be accessed.
 *
 * DESCRIPTION: Look up a name relative to a given scope and return the
 *              corresponding handle, or (NsHandle)NOTFOUND.
 *
 ***************************************************************************/

NsHandle
NsGetHandle (char *Name, NsHandle Scope)
{
    INT32               Size;


    FUNCTION_TRACE ("NsGetHandle");


    if ((nte *) 0 == Root || (char *) 0 == Name)
    {
        /* 
         * If the name space has not been initialized,
         * the requested name surely does not exist.
         */

        return (NsHandle) NOTFOUND;
    }

    if ('\\' == *Name)
    {
        /* Name is fully qualified -- start at the root */
        
        ++Name;
        Scope = Root;
    }

    else
    {
        /* Name is relative to Scope -- handle any ^ prefixes */
        
        while ('^' == *Name)
        {
            if (Root == Scope || (NsHandle) 0 == Scope)
            {
                return (NsHandle)NOTFOUND;
            }
            
            Scope = (NsHandle) ((nte *) Scope)->ParentScope;
            ++Name;
        }
    }

    /* Handle NS_ALL case */
    
    if (NS_ALL == Scope)
    {
        Scope = Root;
    }

    Size = Scope == Root ? NsRootSize : TABLSIZE;

    do
    {
        Scope = (NsHandle) SearchTable (Name, (nte *) Scope, Size, Exec, DefAny);
        Name += 4;
        Size = TABLSIZE;

    } while (Scope && '.' == *Name++);

    if (*Name)
    {
        /* ran out of levels, or there is a char following last segment */
        
        return (NsHandle) NOTFOUND;
    }

    return Scope;
}


/****************************************************************************
 *
 * FUNCTION:    NsFindpVal
 *
 * PARAMETERS:  OBJECT_DESCRIPTOR   *pOD        value to be found in ptrVal field.
 *              NsHandle            SearchBase  Root of subtree to be searched, or
 *                                              NS_ALL to search the entire namespace
 *              INT32               MaxDepth    Maximum depth of search.  Use INT_MAX
 *                                              for an effectively unlimited depth.
 *
 * DESCRIPTION: Traverse the name space until finding a name whose ptrVal
 *              matches the pOD parameter, and return a handle to that
 *              name, or (NsHandle)0 if none exists.
 *              if SearchBase is NS_ALL (null) search from the root,
 *              else it is a handle whose children are to be searched.
 *
 ***************************************************************************/

static NsHandle
NsFindpVal (OBJECT_DESCRIPTOR *pOD, NsHandle SearchBase, INT32 MaxDepth)
{
    nte             *This;
    nte             *NextSeg;
    INT32           Size;


    FUNCTION_TRACE ("NsFindpVal");


    if ((nte *) 0 == Root)
    {
        /* 
         * If the name space has not been initialized,
         * there surely are no matching values.
         */

        return (NsHandle *) 0;
    }

    if (NS_ALL == SearchBase)
    {
        SearchBase = Root;
    }
    
    else if ((NsHandle) 0 != ((nte *) SearchBase)->ChildScope)
    {
        SearchBase = ((nte *) SearchBase)->ChildScope;
    }
    
    else
    {
        /* 
         * If base is not the root and has no children,
         * there is nothing to search.
         */
        return (NsHandle *)0;
    }

    if (SearchBase == Root)
    {
        Size = NsRootSize;
    }
    else
    {
        Size = TABLSIZE;
    }

    if ((OBJECT_DESCRIPTOR *) 0 == pOD)
    {
        return (NsHandle *) 0;
    }

    if (0 == MaxDepth)
    {
        return (NsHandle *) 0;
    }

    /* Loop over entries in NT */
    
    This = (nte *) SearchBase;

    /* Locate appendage, if any, before losing original scope pointer */
    
    NextSeg = NEXTSEG (This);

    while (Size--)
    {
        if (This->NameSeg)
        {
            /* non-empty entry */
            
            if (This->ptrVal == pOD)
            {
                return (NsHandle) This;
            }

            if (This->ChildScope)
            {
                nte             *Temp = NsFindpVal (pOD, This, MaxDepth - 1);
                
                
                if (Temp)
                {
                    return (NsHandle) Temp;
                }
            }
        }

        if (0 == Size && NextSeg)
        {
            /* Just examined last entry, but table has an appendage.  */
            
            This = NextSeg;
            Size += TABLSIZE;
            NextSeg = NEXTSEG (This);
        }
        
        else
        {
            ++This;
        }
    }

    return (NsHandle *)0;
}


/*****************************************************************************
 *
 * FUNCTION:    IsNsValue
 *
 * PARAMETERS:  OBJECT_DESCRIPTOR *pOD
 *
 * RETURN:      TRUE if the passed descriptor is the value of a Name in
 *              the name space, else FALSE
 *
 ****************************************************************************/

INT32
IsNsValue (OBJECT_DESCRIPTOR *pOD)
{

    FUNCTION_TRACE ("IsNsValue");


    return ((NsHandle) 0 != NsFindpVal (pOD, NS_ALL, INT_MAX));
}

#ifdef PLUMBER


/****************************************************************************
 *
 * FUNCTION:    NsMarkNT
 *
 * PARAMETERS:  nte     *This       table to be marked
 *              INT32   Size        size of table
 *              INT32   *Count      output count of blocks marked
 *                                  Outermost caller should preset to 0
 *
 * DESCRIPTION: "Mark" a name table and its reachable values,
 *              including descendents.
 *
 ***************************************************************************/

static void
NsMarkNT (nte *This, INT32 Size, INT32 *Count)
{
    nte                 *NextSeg;


    FUNCTION_TRACE ("NsMarkNT");


    if ((nte *) 0 == This)
    {
        return;
    }

    ++*Count;
    MarkBlock ((void *) &NEXTSEG (This));


    /* Locate appendage, if any, before losing original scope pointer */
    
    NextSeg = NEXTSEG (This);

    /* for all entries in this NT */
    
    while (Size--)
    {
        if (This->NameSeg)
        {
            /* non-empty entry -- mark anything it points to */

            switch (NsValType (This))
            {
                OBJECT_DESCRIPTOR       *ptrVal;
                meth                    *pM;


                case String:
                    ptrVal = (OBJECT_DESCRIPTOR *) NsValPtr (This);
                    
                    /* 
                     * Check for the value pointer in the name table entry
                     * pointing to a string definition in the AML stream,
                     * in which case no allocated storage is involved.
                     */

                    if (ptrVal && StringOp != *(UINT8 *) ptrVal)
                    {
                        /* Avoid marking value if it is in the AML stream */
                        
                        if (!IsInPCodeBlock (ptrVal->String.String))
                        {
                            MarkBlock (ptrVal->String.String);
                        }
                        MarkBlock (ptrVal);
                    }
                    break;

                case Buffer:
                    ptrVal = (OBJECT_DESCRIPTOR *) NsValPtr (This);
                    
                    /* 
                     * Check for the value pointer in the name table entry
                     * pointing to a buffer definition in the AML stream,
                     * in which case no allocated storage is involved.
                     */
                    
                    if (ptrVal && BufferOp != *(UINT8 *) ptrVal)
                    { 
                        MarkBlock (ptrVal->sBuffer.pbBuffer);
                        MarkBlock (ptrVal);
                    }
                    break;

                case Package:
                    ptrVal = (OBJECT_DESCRIPTOR *) NsValPtr (This);
                    
                    /* 
                     * Check for the value pointer in the name table entry
                     * pointing to a package definition in the AML stream,
                     * in which case no allocated storage is involved.
                     */

                    if (ptrVal && PackageOp != *(UINT8 *) ptrVal)
                    {
                        AmlMarkPackage (ptrVal);
                    }
                    break;

                case Method:
                    pM = (meth *) NsValPtr (This);
                    if (pM)
                    {
                        MarkBlock(pM);
                    }

                case BankField:
                case DefField:
                case FieldUnit:
                case IndexField:
                case Region:
                    ptrVal = (OBJECT_DESCRIPTOR *) NsValPtr (This);
                    if (ptrVal)
                    {
                        AmlMarkObject (ptrVal);
                    }

                default:
                    
                    /* No other types should own storage beyond the nte itself */
                    
                    break;

            }   /* switch */

            if (This->ChildScope)
            {
                NsMarkNT (This->ChildScope, TABLSIZE, Count);
            }
        }

        if (0 == Size && NextSeg)
        {
            /* Just examined last entry, but table has an appendage.  */
            
            This = NextSeg;
            Size += TABLSIZE;
            ++*Count;
            MarkBlock ((void *) &NEXTSEG (This));
            NextSeg = NEXTSEG (This);
        }
        
        else
        {
            ++This;
        }
    }
}

#endif  /* PLUMBER */


/****************************************************************************
 *
 * FUNCTION:    NsMarkNS()
 *
 * PARAMETERS:  none
 *
 * DESCRIPTION: If compiled with bu_plumr.h, traverse the name space
 *              "marking" all name tables and reachable values.
 *
 * RETURN:      The number of blocks marked
 *
 ***************************************************************************/

INT32
NsMarkNS (void)
{
    INT32           Count = 0;


    FUNCTION_TRACE ("NsMarkNS");


#ifdef PLUMBER
    if ((nte *) 0 == Root)
    {
        /* 
         * If the name space has not been initialized,
         * there is nothing to mark.
         */
        return 0;
    }

    NsMarkNT (Root, NsRootSize, &Count);
    MarkStaticBlocks (&Count);
    MarkMethodValues (&Count);
    MarkObjectStack (&Count);

#endif  /* PLUMBER */

    return Count;
}
