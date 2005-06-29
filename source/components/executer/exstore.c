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
 | FILENAME: amlexec.c - ACPI AML (p-code) execution
 |__________________________________________________________________________
 |
 | $Revision: 1.2 $
 | $Date: 2005/06/29 17:50:30 $
 | $Log: exstore.c,v $
 | Revision 1.2  2005/06/29 17:50:30  aystarik
 | Detabified.
 |
 | 
 | date	99.01.12.00.17.00;	author grsmith1;	state Exp;
 |
 * 
 * 2     1/11/99 4:17p Grsmith1
 * Detabified.
 * 
 * 1     1/11/99 2:11p Rmoore1
 * AML Interpreter
// 
//    Rev 1.32   11 Sep 1998 18:03:16   phutchis
// Change inc_error() etc. to dKinc_error() etc. (error key logging).
// 
//    Rev 1.31   09 Jun 1998 14:26:32   calingle
// fixed the way the opcode was being evaluated in iSetupFld.  Now iGetRvalue is called to get the pr
// oper data on the stack.
//
//    Rev 1.30   01 Jun 1998 17:52:52   phutchis
// Include failing AML offset in error messages concerning operands.
//
// Correct implementation of LNotOp.
//
//    Rev 1.29   30 Apr 1998 07:22:52   calingle
// Added in code to complete support for BankFields.  Also added support for
// checking the LockRule prior to modification and if it is set to Lock then
// a call is made to take ownership of the global lock.
//
//    Rev 1.28   13 Mar 1998 13:34:14   calingle
// added in calls for the synchronization code.  The functions are in
// amlopsys.c for now.  The functions are OS specific and currently only
// DOS is supported.
//
//    Rev 1.27   13 Mar 1998 11:16:20   phutchis
// Leave operand descriptors on apObjStack[] during operator execution
//   to fix GC problems.
// Fix GC problem in iExecStore() when the destination is a direct name pointer.
// Add support for Buffer sequence numbering.
// Correct iPrepStack call for ConcatOp in iExecDyadic2R()
//
//    Rev 1.26   06 Mar 1998 14:19:16   phutchis
// Fixed garbage collection problem:  Must not allow any further allocation
// call (malloc_bu or calloc_bu) to occur after a block has been allocated
// and before the pointer to it has been stored in a globally-findable
// location (e.g. in a name table entry or on a stack).  This is because
// allocation can cause garbage collection which will silently delete the
// apparently-unreferenced block.
//
// Also improved messages for some "internal error" conditions.
//
//    Rev 1.25   03 Mar 1998 16:31:16   phutchis
// Added tracing of Field operations in Buffers under control of TraceBufFld.
// In iGetRvalue():
//   Fixed glitch in debug identification of Local being fetched;
//   Included the value of the Local in the debug report if its type is Number;
//   Added similar debug reporting for Args as for Locals.
// Fixed major bug in iExecCreateField():
//   Field creation is supposed to cause the destination Name to refer to
//   the defined FieldUnit -- it should not store the constructed FieldUnit
//   object (or its current value) in some location that the Name may already
//   be pointing to.
//
//    Rev 1.24   19 Feb 1998 11:48:34   phutchis
// Added more details and spec reference to comments re semantics of NotifyOp,
// and fixed associated messages to print completely.
//
//    Rev 1.23   05 Feb 1998 11:56:44   phutchis
// Added iGetMethodDepth() and made several minor changes
//   to support calling a Method from within another Method.
// Added debug surrounding call of iGetMethodValue() in iGetRvalue().
// Improved diagnosis of unexpected Lvalues in iPrepStack().
// Added vMarkMethodValues() and iIsMethodValue() to support improved
//   storage management; delete descriptors when overlaid on stack.
//
//    Rev 1.22   08 Jan 1998 15:58:02   phutchis
// Fix uninitialized pointer introduced in rev 1.16.
//
//    Rev 1.21   24 Dec 1997 14:26:34   phutchis
// Clear package and object stacks before starting method execution.
//
//    Rev 1.20   10 Dec 1997 10:59:30   kdbranno
// Added casting to shut up iC386 remarks.
//
//    Rev 1.19   10 Dec 1997 08:45:48   phutchis
// Fix iPrepStack() stack underflow bug.
// Add vAmlAppendOperandDiag(), and call it when iPrepStack() returns
//   S_ERROR, to identify calling location and opcode being processed.
//
//    Rev 1.18   02 Dec 1997 13:34:24   nburke
// Added a conditional vFunctionHello call to every function in the file.
//
//    Rev 1.17   26 Nov 1997 16:19:32   phutchis
// Code inspection rework:
//   Added #include "acpirio.h" for ACPI_READ and ACPI_WRITE definitions.
//   Added #include <limits.h> for UCHAR_MAX definition.
//   Added PRINT_XXX macro so logfile notes of XXX stuff are selectable
//     at compile time.
//   Added comments and parameter validation throughout.
//   Improved error detection and reporting.
//   Changed most allocation failures to call vKFatalError(())
//   Fixed some storage leaks.
//   Replaced hard-coded constants with #defines where appropriate.
//   Combine the nearly identical logic of iGetNamedFieldValue() and
//     iSetNamedFieldValue() into a single function iAccessNamedFieldValue().
//   Renamed parameters of iExecStore() and rearranged logic for clarity.
//
//    Rev 1.16   21 Nov 1997 16:49:06   phutchis
// Fixed iGetRvalue() to work properly when the input is an OBJECT_DESCRIPTOR
// of type FieldUnit.  (It was already handling the case where the input was
// an NsHandle and the name's value was of type FieldUnit.)
//
//    Rev 1.15   17 Nov 1997 15:16:42   phutchis
// In iExecStore() when the result is a field and the value to be stored is not
//   a Number, call iGetRvalue() to try to convert the value to a Number.  Fixes
//   problem of incorrectly logging an error when both source and destination
//   are fields.
// Rework identified in amlscan code inspection:
//   Replaced MAXLEVEL with new AML_METHOD_MAX_NEST in sizing apMethodStack[].
//   Revised iPrepBankFieldValue() to possibly work.
//
//    Rev 1.14   06 Nov 1997 11:56:26   calingle
// added return S_SUCCESS at end of case Device in iGetRvalue.
//
//    Rev 1.13   05 Nov 1997 08:50:10   calingle
// removed #include <bu_plumr.h>
//
//    Rev 1.12   04 Nov 1997 16:55:10   phutchis
// Handle Device case in iGetRvalue().
// This just returns an NsHandle, which seems to be adequate for current use
// in acpiirt, but may need to be revisited in the future.
//
//    Rev 1.11   31 Oct 1997 16:10:28   phutchis
// Revise PCI configuration space access function calls to match new acfglib.
// Rework identified in acpinmsp code inspection:
//   Changed return-value symbols SUCCESS, FAILURE, ERROR, and RETURN to
//     S_SUCCESS, S_FAILURE, S_ERROR, and S_RETURN, to forestall collisions
//     with other subsystems.
//   Changed empty formal parameter lists to "(void)".
//
//    Rev 1.10   24 Sep 1997 15:12:04   phutchis
// Add #include of bu_plumr.h to audit allocation and find leaks.
// Add allocation comments to function headers.
// Add comments to iSetMethodValue() to clarify flow.
// Fix storage leaks in iExecMonadic1() and iExecMonadic2().
//
//    Rev 1.9   29 Jul 1997 14:36:40   phutchis
// Handle passing of parameters to methods:
//   Add ppsParams parameter to iAmlExec()
//   Undefine locals and unused parameters when entering a method
// Fix problem with converting a Buffer from in-line AML to an object
// Fix stack overlay problem during first access to a Region
// Properly handle alignment of accesses to the Region when a Field is unaligned
//
//    Rev 1.8   11 Jul 1997 16:03:42   phutchis
// Fix problem with converting a package from in-line AML to an object.
//
//    Rev 1.7   08 Jul 1997 17:05:58   phutchis
// Fix handling of nested #include of amlpriv.h
//
//    Rev 1.6   20 Jun 1997 11:52:54   phutchis
// Clean up handling of uninitialized values
//
//    Rev 1.5   19 Jun 1997 16:37:56   phutchis
// Added test for SystemMemory access above 1MB when running in real mode
//
//    Rev 1.4   19 Jun 1997 15:31:46   phutchis
// Implement reads and writes to OperationRegion's defined in SystemMemory,
// SystemIO, and PCIConfig spaces; and tracing of such operations.
// EmbeddedControl and SMBus spaces are not implemented.
//
//    Rev 1.3   11 Jun 1997 15:53:34   phutchis
// Add runtime support for DefField and IndexField.
// Generate messages in XXX areas so that logfile records work needed.
// Improve checktrash facility.
// Add some debug capability.
//
//    Rev 1.2   14 May 1997 16:56:54   phutchis
// Generate debug/trace output only if debug level > 0
//
//    Rev 1.1   14 May 1997 15:16:26   phutchis
// Fixed ic386 complaints, mostly casting enum's
//
//    Rev 1.0   13 May 1997 17:34:48   phutchis
// Initial revision.
 |__________________________________________________________________________

*/

#define __AMLEXEC_C__

#include "acpiosd.h"
#include "acpitype.h"
#include "acpipriv.h"
#include "acpirio.h"
#include "aml.h"
#include "acpinmsp.h"
#include "amldsio.h"
#include "amlscan.h"
#include "amlexec.h"
#include "amlpriv.h"
#include "amlopsys.h"
#include <bu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

extern char *apcNsTypeNames[];
extern char *RV[];

/* Change this to #if 1 to enable logfile notes of some XXX stuff */
#if 0
    #define PRINT_XXX   fprintf_bu
#else
    #define PRINT_XXX(a,b,c)
#endif

/* Method Stack, containing locals and args */
/* per level, 0-7 are Local# and 8-14 are Arg# */
#define LCLBASE 0
#define NUMLCL      8
#define ARGBASE (LCLBASE+NUMLCL)
#define NUMARG      7
#define AML_METHOD_MAX_NEST 10  /* Max depth of nested method calls */
static OBJECT_DESCRIPTOR *apMethodStack[AML_METHOD_MAX_NEST][ARGBASE+NUMARG];
static int  iMethodStackTop = -1;

#include <pciutils.h>

/*****************************************************************************
 * FUNCTION:        int iGetMethodDepth(void)
 *
 * RETURN:          The current value of iMethodStackTop
 *
 ****************************************************************************/
int
iGetMethodDepth(void)
{
    return iMethodStackTop;
}

/*****************************************************************************
 * FUNCTION:        NsType iGetMethodValTyp(int iIndex)
 *
 * PARAMETERS:      int iIndex      index in apMethodStack[iMethodStackTop]
 *
 * RETURN:          Data type of selected Arg or Local
 *                      Used only in iExecMonadic2()/TypeOp.
 *
 ****************************************************************************/
static NsType
iGetMethodValTyp(int iIndex)
{
#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "iGetMethodValTyp");
#endif

    if (OUTRANGE(iMethodStackTop, apMethodStack)
     || OUTRANGE(iIndex, apMethodStack[iMethodStackTop]))
    {
        fprintf_bu(iLstFileHandle, LOGFILE,
                      "iGetMethodValTyp: internal error: index %d, %d out of range",
                      iMethodStackTop, iIndex);
        _dKinc_error("0001", PACRLF, __LINE__, __FILE__, iLstFileHandle, LOGFILE);
        return (NsType)-1;
    }

    if ((OBJECT_DESCRIPTOR *)0 == apMethodStack[iMethodStackTop][iIndex])
        return Any; /* Any == 0 => "uninitialized" -- see spec 15.2.3.5.2.28 */

    return apMethodStack[iMethodStackTop][iIndex]->bValTyp;
}

/*****************************************************************************
 * FUNCTION:        int iGetMethodValue(int iIndex, OBJECT_DESCRIPTOR *pOD)
 *
 * PARAMETERS:      int iIndex          index in apMethodStack[iMethodStackTop]
 *                      OBJECT_DESCRIPTOR *pOD  Descriptor into which selected Arg
 *                                                      or Local value should be copied
 *
 * RETURN:          S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Retrieve value of selected Arg or Local
 *                      Used only in iGetRvalue().
 *
 ****************************************************************************/
static int
iGetMethodValue(int iIndex, OBJECT_DESCRIPTOR *pOD)
{
#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "iGetMethodValue");
#endif

    if (OUTRANGE(iMethodStackTop, apMethodStack)
     || OUTRANGE(iIndex, apMethodStack[iMethodStackTop]))
    {
        sprintf(acWhyBuf, "iGetMethodValue: Bad method stack index [%d][%d]",
                iMethodStackTop, iIndex);
    }
    else if ((OBJECT_DESCRIPTOR *)0 == apMethodStack[iMethodStackTop][iIndex])
    {
        if (ARGBASE <= iIndex && iIndex < (ARGBASE+NUMARG))
            sprintf(acWhyBuf, "iGetMethodValue: Uninitialized Arg%d",
                    iIndex - ARGBASE);
        else if (LCLBASE <= iIndex && iIndex < (LCLBASE+NUMLCL))
            sprintf(acWhyBuf, "iGetMethodValue: Uninitialized Local%d",
                    iIndex - LCLBASE);
        else
            sprintf(acWhyBuf, "iGetMethodValue: Uninitialized method value %d",
                    iIndex);
#ifdef HACK
        fprintf_bu(iLstFileHandle, LOGFILE,
                " ** iGetMethodValue: ret uninit as 4 **");
        pOD->sNumber.bValTyp = (BYTE)Number;
        pOD->sNumber.dNumber = 0x4;
        return S_SUCCESS;
#endif /* HACK */
    }
    else
    {
        memcpy((void *)pOD,
                 (void *)apMethodStack[iMethodStackTop][iIndex],
                 sizeof(*pOD));
        if (Buffer == pOD->bValTyp)
            /* Assign a new sequence number */
            pOD->sBuffer.dSequence = dAmlBufSeq();
        return S_SUCCESS;
    }
    pcWhy = acWhyBuf;
    return S_ERROR;
}

/*****************************************************************************
A* FUNCTION:        int iSetMethodValue(int iIndex, OBJECT_DESCRIPTOR *pOD, ...)
 *
 * PARAMETERS:      int iIndex          index in apMethodStack[iMethodStackTop]
 *                      OBJECT_DESCRIPTOR *pOD  Value to be stored
 *                                                      May be NULL -- see Description.
 *                      OBJECT_DESCRIPTOR *pSCR Spare descriptor into which *pOD
 *                                                      can be copied, or NULL if one must
 *                                                      be allocated for the purpose.  If
 *                                                      provided, this descriptor will be
 *                                                      consumed (either used for the new
 *                                                      value or deleted).
 *
 * RETURN:          S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Store a value in an Arg or Local.
 *                      To undefine an entry, pass pOD as NULL; the old descriptor
 *                      will be deleted.
 *
 *  ALLOCATION:
A*  Reference       Size                        Pool    Owner           Description
A*  apMethodStack   s(OBJECT_DESCRIPTOR)    bu      amlexec     Object
 *
 ****************************************************************************/
static int
iSetMethodValue(int iIndex, OBJECT_DESCRIPTOR *pOD, OBJECT_DESCRIPTOR *pSCR)
{
#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "iSetMethodValue");
#endif

    if (OUTRANGE(iMethodStackTop, apMethodStack)
     || OUTRANGE(iIndex, apMethodStack[iMethodStackTop]))
    {
        sprintf(acWhyBuf, "iSetMethodValue: Bad method stack index [%d][%d]",
                iMethodStackTop, iIndex);
        pcWhy = acWhyBuf;
        return S_ERROR;
    }
    if ((OBJECT_DESCRIPTOR *)0 == apMethodStack[iMethodStackTop][iIndex])
    {
        /* Local or Arg is currently undefined */
        if ((OBJECT_DESCRIPTOR *)0 == pSCR && (OBJECT_DESCRIPTOR *)0 != pOD)
        {
            /* No descriptor was provided in pSCR, and the currently-undefined
             * Local or Arg is to be defined.  Allocate a descriptor.
             */
            apMethodStack[iMethodStackTop][iIndex] = NEW(OBJECT_DESCRIPTOR);
            if ((OBJECT_DESCRIPTOR *)0 == apMethodStack[iMethodStackTop][iIndex])
            {
                vKFatalError("0002", ("iSetMethodValue: Descriptor Allocation Failure"));
                return S_ERROR;
            }
        }
        else
            /* A descriptor was provided in pSCR; use it for the Arg/Local
             * new value (or delete it later if the new value is NULL).
             * We also come here if no descriptor was supplied and the
             * undefined Local or Arg is to remain undefined; in that case
             * the assignment is a no-op.
             */
            apMethodStack[iMethodStackTop][iIndex] = pSCR;
    }
    else
        /* Arg or Local is currently defined, so that descriptor will be
         * reused for the new value.  Delete the spare descriptor if supplied.
         */
        if ((OBJECT_DESCRIPTOR *)0 != pSCR)
            /* XXX - see XXX comment below re possible storage leak */
            DELETE(pSCR);

    if ((OBJECT_DESCRIPTOR *)0 == pOD)
    {
        /* Undefine the Arg or Local by setting its descriptor pointer to NULL.
         * If it is currently defined, delete the old descriptor first.
         */
        if ((OBJECT_DESCRIPTOR *)0 != apMethodStack[iMethodStackTop][iIndex])
        {
            if (Buffer == apMethodStack[iMethodStackTop][iIndex]->bValTyp)
                /* Ensure the about-to-be-deleted Buffer's sequence number
                 * will no longer match any FieldUnits defined within it,
                 * by inverting its most-significant bit.
                 */
                apMethodStack[iMethodStackTop][iIndex]->sBuffer.dSequence
                ^= 0x80000000UL;
            DELETE(apMethodStack[iMethodStackTop][iIndex]);
            /* XXX - Should also delete any unshared storage pointed to by this
             * XXX - descriptor, but lacking a convenient way to determine
             * XXX - whether the storage is shared or not we'll let GC handle it.
             */
        }
        apMethodStack[iMethodStackTop][iIndex] = pOD;
    }
    else
    {
        /* Copy the apObjStack descriptor (*pOD) into the descriptor for the
         * Arg or Local.
         */
        /* XXX - possible storage leak: if the old descriptor happens to be
         * XXX - for an aggregate (Buffer, String, Package, etc.), it points
         * XXX - to other storage which may or may not be shared; if unshared
         * XXX - it should be freed here.  (Good Luck figuring out whether it
         * XXX - is shared or not.)
         */
        memcpy((void *)apMethodStack[iMethodStackTop][iIndex],
                 (void *)pOD, sizeof(*pOD));
        if (Buffer == pOD->bValTyp)
            /* Assign a new sequence number */
            apMethodStack[iMethodStackTop][iIndex]->sBuffer.dSequence
            = dAmlBufSeq();
    }

    return S_SUCCESS;
}

/*****************************************************************************
A* FUNCTION:        int iPrepDefFieldValue(NsHandle hRegion, ... )
 *
 * PARAMETERS:      NsHandle    hRegion Region in which field is being defined
 *                      BYTE        bFldFlg Access, LockRule, UpdateRule
 *                                              The format of a FieldFlag is described
 *                                              in the ACPI specification and in <aml.h>
 *                      long        lFldPos field position
 *                      long        lFldLen field length
 *
 * RETURN:          S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Construct an OBJECT_DESCRIPTOR of type DefField and connect
 *                      it to the nte whose handle is at apObjStack[iObjStackTop]
 *
 *  ALLOCATION:
A*  Reference       Size                        Pool    Owner           Description
A*  nte.pVal            s(OBJECT_DESCRIPTOR)    bu      amlexec     Field descriptor
 *
 ****************************************************************************/
int
iPrepDefFieldValue(NsHandle hRegion, BYTE bFldFlg, long lFldPos, long lFldLen)
{
    OBJECT_DESCRIPTOR *pOD = NEW(OBJECT_DESCRIPTOR);

#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "iPrepDefFieldValue");
#endif

    if ((OBJECT_DESCRIPTOR *)0 == pOD)
    {
        vKFatalError("0003", ("iPrepDefFieldValue: Descriptor Allocation Failure"));
        return S_ERROR;
    }
    if ((NsHandle)0 == hRegion)
    {
        pcWhy = "iPrepDefFieldValue: null Region";
        DELETE(pOD);
        return S_ERROR;
    }
    if (Region != iNsValType(hRegion))
    {
        sprintf(acWhyBuf, "iPrepDefFieldValue: Needed Region, found %d",
                    iNsValType(hRegion));
        pcWhy = acWhyBuf;
        DELETE(pOD);
        return S_ERROR;
    }

    if (debug_level() > 0)
        vDumpStack(Exec, "iPrepDefFieldValue", 2, "case DefField");

    pOD->bValTyp = (BYTE)DefField;
    if (DefField != pOD->sField.bValTyp)
    {
        /* The C implementation has done something which is technically legal
         * but unexpected:  the bValTyp field which was defined as a BYTE did
         * not map to the same structure offset as the one which was defined
         * as a WORD_BIT -- see comments in the definition of the sFieldUnit
         * variant of OBJECT_DESCRIPTOR in amlpriv.h.
         *
         * Log some evidence to facilitate porting the code.
         */
        pOD->sField.bValTyp = 0x005a;
        sprintf(acWhyBuf,
                "iPrepDefFieldValue: internal failure %p %02x %02x %02x %02x",
                pOD, ((BYTE *)pOD)[0], ((BYTE *)pOD)[1], ((BYTE *)pOD)[2],
                ((BYTE *)pOD)[3]);
        pcWhy = acWhyBuf;
        DELETE(pOD);
        return S_ERROR;
    }

    pOD->sField.wAccess = (bFldFlg & ACCESS_TYPE_MASK) >> ACCESS_TYPE_SHIFT;
    pOD->sField.wLockRule = (bFldFlg & LOCK_RULE_MASK) >> LOCK_RULE_SHIFT;
    pOD->sField.wUpdateRule = (bFldFlg & UPDATE_RULE_MASK) >> UPDATE_RULE_SHIFT;
    pOD->sField.wDatLen = (WORD)lFldLen;
    /* XXX - should use width of data register, not hardcoded 8 */
    PRINT_XXX(iLstFileHandle, LOGFILE, " ** iPrepDefFieldValue: hard 8 **");
    pOD->sField.wBitOffset = (WORD)lFldPos % 8;
    pOD->sField.dOffset = (DWORD)lFldPos / 8;
    pOD->sField.pContainer = pvNsValPtr(hRegion);

    if (debug_level() > 0)
    {
        fprintf_bu(iLstFileHandle, LOGFILE,
                "\niPrepDefFieldValue: set nte %p (%4.4s) val = %p",
                apObjStack[iObjStackTop], apObjStack[iObjStackTop], pOD);
        iDumpStackEntry(pOD);
        vNsDumpEntry(hRegion, LOGFILE);
        fprintf_bu(iLstFileHandle, LOGFILE, "\t%p ", pOD->sField.pContainer);
        if (pOD->sField.pContainer)
            iDumpStackEntry(pOD->sField.pContainer);
        fprintf_bu(iLstFileHandle, LOGFILE,
            "\n============================================================");
    }

    /* Store the constructed descriptor (pOD) into the nte whose
     * handle is on TOS, preserving the current type of that nte.
     */
    vNsSetValue((NsHandle)apObjStack[iObjStackTop], pOD,
            (BYTE)iNsValType((NsHandle)apObjStack[iObjStackTop]));

    return S_SUCCESS;
}

/*****************************************************************************
A* FUNCTION:        int iPrepBankFieldValue(NsHandle hIndexReg, ... )
 *
 * PARAMETERS:      NsHandle    hRegion     Region in which field is being defined
 *                      NsHandle hBankReg       Bank selection register
 *                      DWORD       dBankVal        Value to store in selection register
 *                      BYTE        bFldFlg     Access, LockRule, UpdateRule
 *                      long        lFldPos     field position
 *                      long        lFldLen     field length
 *
 * RETURN:          S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Construct an OBJECT_DESCRIPTOR of type BankField and connect
 *                      it to the nte whose handle is at apObjStack[iObjStackTop]
 *
 *  ALLOCATION:
A*  Reference       Size                        Pool    Owner           Description
A*  nte.pVal            s(OBJECT_DESCRIPTOR)    bu      amlexec     Field descriptor
 *
 ****************************************************************************/
int
iPrepBankFieldValue(NsHandle hRegion, NsHandle hBankReg, DWORD dBankVal,
        BYTE bFldFlg, long lFldPos, long lFldLen)
{
    OBJECT_DESCRIPTOR *pOD = NEW(OBJECT_DESCRIPTOR);

#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "iPrepBankFieldValue");
#endif

    if ((OBJECT_DESCRIPTOR *)0 == pOD)
    {
        vKFatalError("0004", ("iPrepBankFieldValue: Descriptor Allocation Failure"));
        return S_ERROR;
    }
    if ((NsHandle)0 == hRegion)
    {
        pcWhy = "iPrepBankFieldValue: null Region";
        DELETE(pOD);
        return S_ERROR;
    }
    if (Region != iNsValType(hRegion))
    {
        sprintf(acWhyBuf, "iPrepBankFieldValue: Needed Region, found %d",
                    iNsValType(hRegion));
        pcWhy = acWhyBuf;
        DELETE(pOD);
        return S_ERROR;
    }

    if (debug_level() > 0)
        vDumpStack(Exec, "iPrepBankFieldValue", 2, "case BankField");

    pOD->bValTyp = (BYTE)BankField;
    if (BankField != pOD->sBankField.bValTyp)
    {
        /* See comments in iPrepDefFieldValue() re unexpected C behavior */
        pOD->sBankField.bValTyp = 0x005a;
        sprintf(acWhyBuf,
                "iPrepBankFieldValue: internal failure %p %02x %02x %02x %02x",
                pOD, ((BYTE *)pOD)[0], ((BYTE *)pOD)[1], ((BYTE *)pOD)[2],
                ((BYTE *)pOD)[3]);
        pcWhy = acWhyBuf;
        DELETE(pOD);
        return S_ERROR;
    }

    pOD->sBankField.wAccess = (bFldFlg & ACCESS_TYPE_MASK) >> ACCESS_TYPE_SHIFT;
    pOD->sBankField.wLockRule = (bFldFlg & LOCK_RULE_MASK) >> LOCK_RULE_SHIFT;
    pOD->sBankField.wUpdateRule
                                    = (bFldFlg & UPDATE_RULE_MASK) >> UPDATE_RULE_SHIFT;
    pOD->sBankField.wDatLen = (WORD)lFldLen;
    /* XXX - should use width of data register, not hardcoded 8 */
    PRINT_XXX(iLstFileHandle, LOGFILE, " ** iPrepBankFieldValue: hard 8 **");
    pOD->sBankField.wBitOffset = (WORD)lFldPos % 8;
    pOD->sBankField.dOffset = (DWORD)lFldPos / 8;
    pOD->sBankField.dBankVal = dBankVal;
    pOD->sBankField.pContainer = pvNsValPtr(hRegion);
    pOD->sBankField.hBankSelect = pvNsValPtr(hBankReg);

    if (debug_level() > 0)
    {
        fprintf_bu(iLstFileHandle, LOGFILE,
                "\niPrepBankFieldValue: set nte %p (%4.4s) val = %p",
                apObjStack[iObjStackTop], apObjStack[iObjStackTop], pOD);
        iDumpStackEntry(pOD);
        vNsDumpEntry(hRegion, LOGFILE);
        vNsDumpEntry(hBankReg, LOGFILE);
        fprintf_bu(iLstFileHandle, LOGFILE,
            "\n============================================================");
    }

    /* Store the constructed descriptor (pOD) into the nte whose
     * handle is on TOS, preserving the current type of that nte.
     */
    vNsSetValue((NsHandle)apObjStack[iObjStackTop], pOD,
            (BYTE)iNsValType((NsHandle)apObjStack[iObjStackTop]));

    return S_SUCCESS;
}

/*****************************************************************************
A* FUNCTION:        int iPrepIndexFieldValue(hIndexReg, ... )
 *
 * PARAMETERS:      NsHandle    hIndexReg   Index register
 *                      NsHandle hDataReg       Data register
 *                      BYTE        bFldFlg     Access, LockRule, UpdateRule
 *                      long        lFldPos     field position
 *                      long        lFldLen     field length
 *
 * RETURN:          S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Construct an OBJECT_DESCRIPTOR of type IndexField and connect
 *                      it to the nte whose handle is at apObjStack[iObjStackTop]
 *
 *  ALLOCATION:
A*  Reference       Size                        Pool    Owner           Description
A*  nte.pVal            s(OBJECT_DESCRIPTOR)    bu      amlexec     Field descriptor
 *
 ****************************************************************************/
int
iPrepIndexFieldValue(NsHandle hIndexReg, NsHandle hDataReg,
        BYTE bFldFlg, long lFldPos, long lFldLen)
{
    OBJECT_DESCRIPTOR *pOD = NEW(OBJECT_DESCRIPTOR);

#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "iPrepIndexFieldValue");
#endif

    if ((OBJECT_DESCRIPTOR *)0 == pOD)
    {
        vKFatalError("0005", ("iPrepIndexFieldValue: Descriptor Allocation Failure"));
        return S_ERROR;
    }
    if ((NsHandle)0 == hIndexReg || (NsHandle)0 == hDataReg)
    {
        pcWhy = "iPrepIndexFieldValue: null handle";
        DELETE(pOD);
        return S_ERROR;
    }

    pOD->bValTyp = (BYTE)IndexField;
    if (IndexField != pOD->sIndexField.bValTyp)
    {
        /* See comments in iPrepDefFieldValue() re unexpected C behavior */
        pOD->sIndexField.bValTyp = 0x005a;
        sprintf(acWhyBuf,
                "iPrepIndexFieldValue: internal failure %p %02x %02x %02x %02x",
                pOD, ((BYTE *)pOD)[0], ((BYTE *)pOD)[1], ((BYTE *)pOD)[2],
                ((BYTE *)pOD)[3]);
        pcWhy = acWhyBuf;
        DELETE(pOD);
        return S_ERROR;
    }

    pOD->sIndexField.wAccess = (bFldFlg & ACCESS_TYPE_MASK) >> ACCESS_TYPE_SHIFT;
    pOD->sIndexField.wLockRule = (bFldFlg & LOCK_RULE_MASK) >> LOCK_RULE_SHIFT;
    pOD->sIndexField.wUpdateRule
                                    = (bFldFlg & UPDATE_RULE_MASK) >> UPDATE_RULE_SHIFT;
    pOD->sIndexField.wDatLen = (WORD)lFldLen;
    /* XXX - should use width of data register, not hardcoded 8 */
    PRINT_XXX(iLstFileHandle, LOGFILE, " ** iPrepIndexFieldValue: hard 8 **");
    pOD->sIndexField.wBitOffset = (WORD)lFldPos % 8;
    pOD->sIndexField.dIndexVal = (DWORD)lFldPos / 8;
    pOD->sIndexField.hIndex = hIndexReg;
    pOD->sIndexField.hData = hDataReg;

    if (debug_level() > 0)
    {
        fprintf_bu(iLstFileHandle, LOGFILE,
                "\niPrepIndexFieldValue: set nte %p (%4.4s) val = %p",
                apObjStack[iObjStackTop], apObjStack[iObjStackTop], pOD);
        iDumpStackEntry(pOD);
        vNsDumpEntry(hIndexReg, LOGFILE);
        vNsDumpEntry(hDataReg, LOGFILE);
        fprintf_bu(iLstFileHandle, LOGFILE,
            "\n============================================================");
    }

    /* Store the constructed descriptor (pOD) into the nte whose
     * handle is on TOS, preserving the current type of that nte.
     */
    vNsSetValue((NsHandle)apObjStack[iObjStackTop], pOD,
            (BYTE)iNsValType((NsHandle)apObjStack[iObjStackTop]));

    return S_SUCCESS;
}

/*****************************************************************************
 * FUNCTION:        iSetupFld(OBJECT_DESCRIPTOR *pOD, OBJECT_DESCRIPTOR *pRgn)
 *
 * PARAMETERS:      OBJECT_DESCRIPTOR *pOD      Field to be read or written
 *                      OBJECT_DESCRIPTOR *pRgn     Region containing field
 *                      int                  iFldW  Field Width in bits (8, 16, or 32)
 *
 * RETURN:          S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Common processing for iReadFld and iWriteFld
 *
 ****************************************************************************/
static int
iSetupFld(OBJECT_DESCRIPTOR *pOD, OBJECT_DESCRIPTOR *pRgn, int iFldW)
{
    int iRv;
    int iFldByteW = iFldW / 8;                  /* possible values are 1, 2, 4 */

#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "iSetupFld");
#endif

    if ((OBJECT_DESCRIPTOR *)0 == pOD || (OBJECT_DESCRIPTOR *)0 == pRgn)
    {
        pcWhy = "iSetupFld:internal error: null handle";
        return S_ERROR;
    }
    if (Region != pRgn->bValTyp)
    {
        sprintf(acWhyBuf, "iSetupFld: Needed Region, found %d", pRgn->bValTyp);
        pcWhy = acWhyBuf;
        return S_ERROR;
    }
    if (iFldW != 8 && iFldW != 16 && iFldW != 32)
    {
        sprintf(acWhyBuf, "iSetupFld:internal error: bad width %d", iFldW);
        pcWhy = acWhyBuf;
        return S_ERROR;
    }

    if (debug_level() > 2)
    {
        /* flow trace */
        fprintf_bu(iLstFileHandle, LOGFILE, "\niSetupFld: ");
    }

    /* If the address and length have not been previously evaluated,
     * evaluate them and save the results.
     */
    if (0 == pRgn->sRegion.wAdrLenValid)
    {
        /* preserve current stack */
        if ((iRv = PushExecLen(0L)) != S_SUCCESS)
        {
            if (debug_level() > 2)
            {
                /* flow trace */
                fprintf_bu(iLstFileHandle, LOGFILE,
                        "PushExecLen returned %s", RV[iRv]);
            }
            return iRv;
        }

        /* Point to Address opcode in AML stream */
        vSetCurrentLoc(&pRgn->sRegion.sAdrLoc);

        /* Evaluate the Address opcode */
        if ((iRv = DoOpCode(Exec)) == S_SUCCESS
         && (iRv = iGetRvalue((OBJECT_DESCRIPTOR **)&apObjStack[iObjStackTop]))
             == S_SUCCESS)
        {
            /* Capture the address */
            OBJECT_DESCRIPTOR *pODval = apObjStack[iObjStackTop];
            if ((OBJECT_DESCRIPTOR *)0 == pODval
             || pODval->bValTyp != (BYTE)Number)
            {
                pcWhy = "iSetupFld: Malformed Region/Address";
                if (debug_level() > 2)
                {
                    /* flow trace */
                    fprintf_bu(iLstFileHandle, LOGFILE, " Malformed Region/Address "
                        "\npODval = %p, pODval->bValTyp = %02Xh, Number = %02Xh\n",
                        pODval, pODval->bValTyp, (BYTE)Number);

                }
                return S_ERROR;
            }
            pRgn->sRegion.dAddress = pODval->sNumber.dNumber;

            /* Evaluate the Length opcode */
            if ((iRv = DoOpCode(Exec)) == S_SUCCESS
             && (iRv = iGetRvalue((OBJECT_DESCRIPTOR **)&apObjStack[iObjStackTop]))
                 == S_SUCCESS)
            {
                /* Capture the length */
                pODval = apObjStack[iObjStackTop];
                if ((OBJECT_DESCRIPTOR *)0 == pODval
                 || pODval->bValTyp != (BYTE)Number)
                {
                    pcWhy = "iSetupFld: Malformed Region/Length";
                    if (debug_level() > 2)
                    {
                        /* flow trace */
                        fprintf_bu(iLstFileHandle, LOGFILE,
                                " Malformed Region/Length ");
                    }
                    return S_ERROR;
                }
                pRgn->sRegion.dLength = pODval->sNumber.dNumber;

                /* Remember that both Address and Length
                 * have been successfully evaluated and saved.
                 */
                pRgn->sRegion.wAdrLenValid = 1;
            }
        }   /* if ((iRv = DoOpCode(Exec)) == S_SUCCESS) */

        if (S_SUCCESS != iRv)
        {
            if (debug_level() > 1)
            {
                fprintf_bu(iLstFileHandle, LOGFILE,
                        " DoOpCode at [%04x:%04lx] returned %s ",
                        pRgn->sRegion.sAdrLoc.iOffset,
                        pRgn->sRegion.sAdrLoc.lLength,
                        RV[iRv]);
            }
            return iRv;
        }
        if ((iRv = PopExec()) != S_SUCCESS)
        {
            if (debug_level() > 1)
            {
                fprintf_bu(iLstFileHandle, LOGFILE,
                        " PopExec returned %s ", RV[iRv]);
            }
            return iRv;
        }
    }   /* if (0 == pRgn->sRegion.wAdrLenValid) */

    /* If (offset rounded up to next multiple of field width)
     * exceeds region length, indicate an error.
     */
    if (pRgn->sRegion.dLength
      < (pOD->sField.dOffset & ~((DWORD)iFldByteW - 1)) + iFldByteW)
    {
        sprintf(acWhyBuf,
        "iSetupFld: Operation at %08lx width %d bits exceeds region bound %08lx",
                pOD->sField.dOffset, iFldW, pRgn->sRegion.dLength);
        pcWhy = acWhyBuf;
        if (debug_level() > 2)
        {
            /* flow trace */
            fprintf_bu(iLstFileHandle, LOGFILE, "out of bounds");
        }
        if (debug_level() > 0)
        {
            iDumpStackEntry(pRgn);
            iDumpStackEntry(pOD);
        }
        return S_ERROR;
    }
    if (debug_level() > 2)
    {
        /* flow trace */
        fprintf_bu(iLstFileHandle, LOGFILE, "S_SUCCESS");
    }
    return S_SUCCESS;
}

/*****************************************************************************
 * FUNCTION:        iReadFld(OBJECT_DESCRIPTOR *pOD, DWORD *pdVal)
 *
 * PARAMETERS:      OBJECT_DESCRIPTOR *pOD      Field to be read
 *                      DWORD                   *pdVal  Where to store value
 *                      int                  iFldW  Field Width in bits (8, 16, or 32)
 *
 * RETURN:          S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Retrieve the value of the given field
 *
 ****************************************************************************/
static int
iReadFld(OBJECT_DESCRIPTOR *pOD, DWORD *pdVal, int iFldW)
{
    /* pOD is validated by callers */
    OBJECT_DESCRIPTOR *pRgn = pOD->sField.pContainer;
    DWORD dAdr;
    int iFldByteW = iFldW / 8;
    int iRv = iSetupFld(pOD, pRgn, iFldW);

#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "iReadFld");
#endif

    if (S_SUCCESS != iRv)
        return iRv;

    /* Round offset down to next multiple of
     * field width, and add region base address.
     */
    dAdr = pRgn->sRegion.dAddress
          + (pOD->sField.dOffset & ~((DWORD)iFldByteW - 1));

    if (Trace & TraceOpRgn)
        if (OUTRANGE(pRgn->sRegion.bSpaceId, apcRegionTypes))
            fprintf_bu(iLstFileHandle, LOGFILE,
                "\n** iReadFld: Read from unknown region SpaceID %d at %08lx width %d ** ",
                    pRgn->sRegion.bSpaceId, dAdr, iFldW);
        else
        {
            fprintf_bu(iLstFileHandle, LOGFILE,
                    "\n** Read from %s at %08lx width %d",
                    apcRegionTypes[pRgn->sRegion.bSpaceId], dAdr, iFldW);
            fflush_bu(iLstFileHandle);
        }
    switch(pRgn->sRegion.bSpaceId)
    {
        void *pvPhysPtr;
        BYTE bPciBus, bDevFunc, bPciReg, bRv;

        case SystemMemory:
#ifdef RMX
            pvPhysPtr = pvBuildPtr(sFlatSeg, (size_t)dAdr);
#else
            if (dAdr & 0xFFF00000UL)
            {
                sprintf(acWhyBuf,
                        "iReadFld:implementation limitation: SystemMemory address %08lx over 1MB", dAdr);
                pcWhy = acWhyBuf;
                return S_ERROR;
            }
            pvPhysPtr = PHYStoFP(dAdr);
#endif
            switch (iFldW)
            {
                case 8:
                    *pdVal = (DWORD)*(BYTE *)pvPhysPtr;
                    break;

                case 16:
                    *pdVal = (DWORD)*(WORD *)pvPhysPtr;
                    break;

                case 32:
                    *pdVal = *(DWORD *)pvPhysPtr;
                    break;

                default:
                    sprintf(acWhyBuf,
                            "iReadFld: invalid SystemMemory width %d", iFldW);
                    pcWhy = acWhyBuf;
                    return S_ERROR;
            }
            break;

        case SystemIO:
            switch (iFldW)
            {
                case 8:
                    *pdVal = (DWORD)bIn8((WORD)dAdr);
                    break;

                case 16:
                    *pdVal = (DWORD)wIn16((WORD)dAdr);
                    break;

                case 32:
                    *pdVal = dIn32((WORD)dAdr);
                    break;

                default:
                    sprintf(acWhyBuf,
                            "iReadFld: invalid SystemIO width %d", iFldW);
                    pcWhy = acWhyBuf;
                    return S_ERROR;
            }
            break;

        case PCIConfig:
            bPciBus = (BYTE)(dAdr >> 16);
            bDevFunc = (BYTE)(dAdr >> 8);
            bPciReg = (BYTE)((dAdr >> 2) & 0x3f);
            switch (iFldW)
            {
                case 8:
                    bRv
                    = bReadPciCfgByte(bPciBus, bDevFunc, bPciReg, (BYTE *)pdVal);
                    break;

                case 16:
                    bRv
                    = bReadPciCfgWord(bPciBus, bDevFunc, bPciReg, (WORD *)pdVal);
                    break;

                case 32:
                    bRv = bReadPciCfgDword(bPciBus, bDevFunc, bPciReg, pdVal);
                    break;

                default:
                    sprintf(acWhyBuf,
                            "iReadFld: invalid PCIConfig width %d", iFldW);
                    pcWhy = acWhyBuf;
                    return S_ERROR;
            }
            if (bRv)
                return S_ERROR;
            break;

        case EmbeddedControl:
        case SMBus:
            /* XXX - Actual read should happen here */
            sprintf(acWhyBuf, "iReadFld: Region type %s not implemented",
                    apcRegionTypes[pRgn->sRegion.bSpaceId]);
            pcWhy = acWhyBuf;
            return S_ERROR;

        default:
            sprintf(acWhyBuf, "iReadFld: Unknown region SpaceID %d",
                    pRgn->sRegion.bSpaceId);
            pcWhy = acWhyBuf;
            return S_ERROR;
    }
    if (Trace & TraceOpRgn)
        fprintf_bu(iLstFileHandle, LOGFILE, " val %08lx ", *pdVal);
    return S_SUCCESS;
}

/*****************************************************************************
 * FUNCTION:        iWriteFld(OBJECT_DESCRIPTOR *pOD, DWORD dVal)
 *
 * PARAMETERS:      OBJECT_DESCRIPTOR *pOD  Field to be set
 *                      DWORD                   dVal  Value to store
 *                      int                 iFldW   Field Width in bits (8, 16, or 32)
 *
 * RETURN:          S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Store the value into the given field
 *
 ****************************************************************************/
static int
iWriteFld(OBJECT_DESCRIPTOR *pOD, DWORD dVal, int iFldW)
{
    /* pOD is validated by callers */
    OBJECT_DESCRIPTOR *pRgn = pOD->sField.pContainer;
    DWORD dAdr;
    int iFldByteW = iFldW / 8;
    int iRv = iSetupFld(pOD, pRgn, iFldW);

#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "iWriteFld");
#endif

    if (S_SUCCESS != iRv)
        return iRv;

    dAdr = pRgn->sRegion.dAddress
          + (pOD->sField.dOffset & ~((DWORD)iFldByteW - 1));
    if (Trace & TraceOpRgn)
        if (OUTRANGE(pRgn->sRegion.bSpaceId, apcRegionTypes))
            fprintf_bu(iLstFileHandle, LOGFILE,
                "\n** iWriteFld: Store %lx in unknown region SpaceID %d at %08lx width %d ** ",
                    dVal, pRgn->sRegion.bSpaceId, dAdr, iFldW);
        else
        {
            fprintf_bu(iLstFileHandle, LOGFILE,
                    "\n** Store %lx in %s at %08lx width %d",
                    dVal, apcRegionTypes[pRgn->sRegion.bSpaceId], dAdr, iFldW);
            fflush_bu(iLstFileHandle);
        }
    switch(pRgn->sRegion.bSpaceId)
    {
        void *pvPhysPtr;
        BYTE bPciBus, bDevFunc, bPciReg, bRv;

        case SystemMemory:
#ifdef RMX
            pvPhysPtr = pvBuildPtr(sFlatSeg, (size_t)dAdr);
#else
            if (dAdr & 0xFFF00000UL)
            {
                sprintf(acWhyBuf,
                        "iWriteFld:implementation limitation: SystemMemory address %08lx over 1MB", dAdr);
                pcWhy = acWhyBuf;
                return S_ERROR;
            }
            pvPhysPtr = PHYStoFP(dAdr);
#endif
            switch (iFldW)
            {
                case 8:
                    *(BYTE *)pvPhysPtr = (BYTE)dVal;
                    break;

                case 16:
                    *(WORD *)pvPhysPtr = (WORD)dVal;
                    break;

                case 32:
                    *(DWORD *)pvPhysPtr = dVal;
                    break;

                default:
                    sprintf(acWhyBuf,
                            "iWriteFld: invalid SystemMemory width %d", iFldW);
                    pcWhy = acWhyBuf;
                    return S_ERROR;
            }
            break;

        case SystemIO:
            switch (iFldW)
            {
                case 8:
                    vOut8((WORD)dAdr, (BYTE)dVal);
                    break;

                case 16:
                    vOut16((WORD)dAdr, (WORD)dVal);
                    break;

                case 32:
                    vOut32((WORD)dAdr, dVal);
                    break;

                default:
                    sprintf(acWhyBuf,
                            "iWriteFld: invalid SystemIO width %d", iFldW);
                    pcWhy = acWhyBuf;
                    return S_ERROR;
            }
            break;

        case PCIConfig:
            bPciBus = (BYTE)(dAdr >> 16);
            bDevFunc = (BYTE)(dAdr >> 8);
            bPciReg = (BYTE)((dAdr >> 2) & 0x3f);
            switch (iFldW)
            {
                case 8:
                    bRv
                    = bWritePciCfgByte(bPciBus, bDevFunc, bPciReg, *(BYTE *)&dVal);
                    break;

                case 16:
                    bRv
                    = bWritePciCfgWord(bPciBus, bDevFunc, bPciReg, *(WORD *)&dVal);
                    break;

                case 32:
                    bRv = bWritePciCfgDword(bPciBus, bDevFunc, bPciReg, dVal);
                    break;

                default:
                    sprintf(acWhyBuf,
                            "iWriteFld: invalid PCIConfig width %d", iFldW);
                    pcWhy = acWhyBuf;
                    return S_ERROR;
            }
            if (bRv)
                return S_ERROR;
            break;

        case EmbeddedControl:
        case SMBus:
            /* XXX - Actual write should happen here */
            sprintf(acWhyBuf, "iWriteFld: Region type %s not implemented",
                    apcRegionTypes[pRgn->sRegion.bSpaceId]);
            pcWhy = acWhyBuf;
            return S_ERROR;

        default:
            sprintf(acWhyBuf, "iWriteFld: Unknown region SpaceID %d",
                    pRgn->sRegion.bSpaceId);
            pcWhy = acWhyBuf;
            return S_ERROR;
    }
    return S_SUCCESS;
}

/*****************************************************************************
 * FUNCTION:        static void vAmlAppendBlockOwner(void *pvB)
 *
 * PARAMETERS:      void *pvB
 *
 * DESCRIPTION: Append block-owner data from bu_plumr to acWhyBuf.
 *
 ****************************************************************************/
static void
vAmlAppendBlockOwner(void *pvB)
{
#ifdef PLUMBER
    if (pcWhy != acWhyBuf)
    {
        /* Copy message to acWhyBuf */
        strcpy(acWhyBuf, pcWhy);
        pcWhy = acWhyBuf;
    }
#if 1
    vPlumber("internal type mismatch", 3);
#endif
    sprintf(&acWhyBuf[strlen(acWhyBuf)], " %s", pcIdentifyOwner(pvB));
#endif  /* PLUMBER */
}

/*****************************************************************************
 * FUNCTION:        static int iAccessNamedField(int iMode, NsHandle hNamedField,
 *
 * PARAMETERS:      int     iMode               ACPI_READ or ACPI_WRITE
 * PARAMETERS:      NsHandle    hNamedField     Handle for field to be accessed
 *                      DWORD       *pdVal          Value to be read or written
 *
 * RETURN:          S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Read or write a named field
 *
 ****************************************************************************/
static int
iAccessNamedField(int iMode, NsHandle hNamedField, DWORD *pdVal)
{
    OBJECT_DESCRIPTOR *pOD = pvNsValPtr(hNamedField);
    char *pcType;
    int iGran, iRv, iMaxW;

#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "iAccessNamedField");
#endif

    if ((OBJECT_DESCRIPTOR *)0 == pOD)
    {
        pcWhy = "iAccessNamedField:internal error: null value pointer";
        return S_ERROR;
    }
    if (DefField != iNsValType(hNamedField))
    {
        sprintf(acWhyBuf,
                  "iAccessNamedField: Name %4.4s type %d is not a defined field",
                  hNamedField, iNsValType(hNamedField));
        pcWhy = acWhyBuf;
        return S_ERROR;
    }
    if (debug_level() > 2)
    {
        fprintf_bu(iLstFileHandle, LOGFILE,
                    "\nin iAccessNamedField: DefField type and ValPtr OK in nte ");
        vNsDumpEntry(hNamedField, LOGFILE);
        fprintf_bu(iLstFileHandle, LOGFILE, "pOD = %p, pOD->bValTyp = %d",
                pOD, pOD->bValTyp);
        fprintf_bu(iLstFileHandle, LOGFILE, " wDatLen = %d, wBitOffset = %d\n",
                pOD->sFieldUnit.wDatLen, pOD->sFieldUnit.wBitOffset);
    }
    if (DefField != pOD->bValTyp)
    {
        sprintf(acWhyBuf,
            "iAccessNamedField:internal error: Name %4.4s type %d does not match value-type %d at %p",
            hNamedField, iNsValType(hNamedField), pOD->bValTyp, pOD);
        pcWhy = acWhyBuf;
        vAmlAppendBlockOwner(pOD);
        return S_ERROR;
    }

    switch (pOD->sField.wAccess)
    {
        case AnyAcc:
            iGran = 8;
            iMaxW = 32;
            pcType = "DWORD";
            break;

        case ByteAcc:
            iGran = iMaxW = 8;
            pcType = "BYTE";
            break;

        case WordAcc:
            iGran = iMaxW = 16;
            pcType = "WORD";
            break;

        case DWordAcc:
            iGran = iMaxW = 32;
            pcType = "DWORD";
            break;

        default:
            sprintf(acWhyBuf,
                "iAccessNamedField: unknown access type %d",
                pOD->sField.wAccess);
            pcWhy = acWhyBuf;
            return S_ERROR;
    }
    if (pOD->sFieldUnit.wDatLen + pOD->sFieldUnit.wBitOffset > (WORD)iMaxW)
    {
        sprintf(acWhyBuf, "iAccessNamedField: Field exceeds %s", pcType);
        pcWhy = acWhyBuf;
        return S_ERROR;
    }

    /* As long as iMaxW/2 is wide enough for the data and iMaxW > iGran,
     * divide iMaxW by 2.
     */
    while (iGran < iMaxW
         && pOD->sFieldUnit.wDatLen + pOD->sFieldUnit.wBitOffset
            <= (WORD)iMaxW / 2)
        iMaxW /= 2;

    if (ACPI_WRITE == iMode)
    {
        /* Construct dMask with 1 bits where the field is, 0 bits elsewhere */
        DWORD dMask = (((DWORD)1 << pOD->sFieldUnit.wDatLen) - (DWORD)1)
                            << pOD->sField.wBitOffset;
        /* Shift and mask the value into the field position */
        DWORD dValue = (*pdVal << pOD->sField.wBitOffset) & dMask;
        int iLocked = FALSE;


        if (pOD->sFieldUnit.wDatLen % iGran || pOD->sFieldUnit.wBitOffset)
            /* Write does not fill an integral number of naturally aligned units */
            switch (pOD->sField.wUpdateRule)
            {
                DWORD dOldVal;

                case Preserve:
                    /* Read the current contents of the byte/word/dword containing
                     * the field, and merge with the new field value.
                     */
                    iRv = iReadFld(pOD, &dOldVal, iMaxW);
                    if (S_SUCCESS != iRv)
                        return iRv;
                    dValue |= dOldVal & ~dMask;
                    break;

                case WriteAsOnes:
                    /* Set positions outside the field to 1's */
                    dValue |= ~dMask;
                    break;

                case WriteAsZeros:
                    /* Positions outside the field are already 0
                     * due to "& dMask" above
                     */
                    break;

                default:
                    sprintf(acWhyBuf,
                                "iAccessNamedField: Unknown UpdateRule setting %d",
                                pOD->sField.wUpdateRule);
                    pcWhy = acWhyBuf;
                    return S_ERROR;
            }

        if (debug_level() > 2)
        {
            fprintf_bu(iLstFileHandle, LOGFILE, " invoking iWriteFld");
        }
        /* Check lock rule prior to modifing the field */
        if (pOD->sFieldUnit.wLockRule == (WORD)Lock)
        {
            if (iGetGlobalLock() == S_ERROR)
            {
                /* the ownship failed - Bad Bad Bad, this is a single threaded */
                /* implementation so there is no way some other process should */
                /* own this.  This means something grabbed it and did not */
                /* release the Global Lock! (pcWhy will already be set) */
                return (S_ERROR);
            }
            else
                iLocked = TRUE;
        }
        /* perform the update */
        iRv = iWriteFld(pOD, dValue, iMaxW);
        /* if the Global Lock is owned the release it */
        if (iLocked)
        {
            vReleaseGlobalLock();
            iLocked = FALSE;
        }
    }/* (ACPI_WRITE == iMode) */
    else
    {
        /* ACPI_READ */
        iRv = iReadFld(pOD, pdVal, iMaxW);
        if (S_SUCCESS == iRv)
        {
            *pdVal >>= pOD->sField.wBitOffset;
            *pdVal &= (((DWORD)1 << pOD->sFieldUnit.wDatLen) - (DWORD)1);
        }
    }
    return iRv;
}

/*****************************************************************************
 * FUNCTION:        int iSetNamedFieldValue(NsHandle hNamedField, DWORD dValue)
 *
 * PARAMETERS:      NsHandle    hNamedField     Handle for field to be set
 *                  DWORD       dValue          Value to be stored in field
 *
 * RETURN:          S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Store the given value into the field
 *
 ****************************************************************************/
int
iSetNamedFieldValue(NsHandle hNamedField, DWORD dValue)
{
#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "iSetNamedFieldValue");
#endif

    if ((NsHandle)0 == hNamedField)
    {
        pcWhy = "iSetNamedFieldValue:internal error:null handle";
        return S_ERROR;
    }
    return iAccessNamedField(ACPI_WRITE, hNamedField, &dValue);
}

/*****************************************************************************
 * FUNCTION:        int iGetNamedFieldValue(NsHandle hNamedField, DWORD *pdVal)
 *
 * PARAMETERS:      NsHandle    hNamedField     Handle for field to be read
 *                      DWORD       *pdVal          Where to store value read froom field
 *
 * RETURN:          S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Retrieve the value of the given field
 *
 ****************************************************************************/
int
iGetNamedFieldValue(NsHandle hNamedField, DWORD *pdVal)
{
#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "iGetNamedFieldValue");
#endif

    if ((NsHandle)0 == hNamedField)
    {
        pcWhy = "iGetNamedFieldValue:internal error:null handle";
        return S_ERROR;
    }
    return iAccessNamedField(ACPI_READ, hNamedField, pdVal);
}

/*****************************************************************************
A* FUNCTION:        iExecStore(OBJECT_DESCRIPTOR *pVal, OBJECT_DESCRIPTOR *pDest)
 *
 * PARAMETERS:      OBJECT_DESCRIPTOR *pVal     value to be stored
 *                      OBJECT_DESCRIPTOR *pDest    where to store it -- must be
 *                                                          either an (NsHandle) or an
 *                                                          OBJECT_DESCRIPTOR of type Lvalue;
 *                                                          if the latter the descriptor will
 *                                                          be either reused or deleted.
 *
 * RETURN:          S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Store the value described by pVal into the location
 *                      described by pDest.  Called by various interpreter
 *                      functions to store the result of an operation into
 *                      the destination operand.
 *
 *  ALLOCATION:
A*  Reference       Size                        Pool    Owner           Description
A*  nte.pVal            s(OBJECT_DESCRIPTOR)    bu      amlexec     Name(Lvalue)
 *
 ****************************************************************************/
int
iExecStore(OBJECT_DESCRIPTOR *pVal, OBJECT_DESCRIPTOR *pDest)
{
    NsHandle nTemp;
    int iRv;
    int iStacked = FALSE;
    int iLocked = FALSE;

#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "iExecStore");
#endif

    if ((OBJECT_DESCRIPTOR *)0 == pVal || (OBJECT_DESCRIPTOR *)0 == pDest)
    {
        pcWhy = "iExecStore:internal error: null pointer";
        return S_ERROR;
    }

    if (debug_level() > 2)
    {
        fprintf_bu(iLstFileHandle, LOGFILE, "\nin iExecStore");
    }

    if (iIsNsHandle(pDest))
    {
        nTemp = (NsHandle)pDest;
        pDest = NEW(OBJECT_DESCRIPTOR);
        if (pDest)
        {
            pDest->bValTyp = (BYTE)Lvalue;
            pDest->sLvalue.bOpCode = NameOp;
            pDest->sLvalue.pvRef = nTemp;
            /* Push the descriptor on TOS temporarily
             * to protect it from garbage collection
             */
            iRv = iPushIfExec(Exec);
            if (S_SUCCESS != iRv)
            {
                DELETE(pDest);
                return iRv;
            }
            apObjStack[iObjStackTop] = pDest;
            iStacked = TRUE;
        }
        else
        {
            vKFatalError("0006", ("iExecStore: Descriptor Allocation Failure"));
            return S_ERROR;
        }
    }
    if (pDest->bValTyp != Lvalue)
    {
        sprintf(acWhyBuf, "iExecStore: Store target is not an Lvalue [%s]",
                apcNsTypeNames[pDest->bValTyp]);
        pcWhy = acWhyBuf;
        if (debug_level() > 0)
        {
            iDumpStackEntry(pVal);
            iDumpStackEntry(pDest);
            vDumpStack(Exec, "iExecStore", 2, "target not Lvalue");
        }
        return S_ERROR;
    }

    switch(pDest->sLvalue.bOpCode)
    {
    case NameOp:
        /* Storing into a Name */
        nTemp = pDest->sLvalue.pvRef;
        switch (iNsValType(nTemp))              /* Type of Name's existing value */
        {
            case Alias:
#if 1
                sprintf(acWhyBuf,
                          "iExecStore/NameOp: Store into %s not implemented",
                          apcNsTypeNames[iNsValType(nTemp)]);
                pcWhy = acWhyBuf;
                iRv = S_ERROR;
#else
                fprintf_bu(iLstFileHandle, LOGFILE,
                        "\niExecStore/NameOp: Store into %s not implemented\n",
                          apcNsTypeNames[iNsValType(nTemp)]);
                iRv = S_SUCCESS;
#endif
                DELETE(pDest);
                break;

            case BankField:
                /* Storing into a BankField.
                 * If value is not a Number, try to resolve it to one.
                 */
                if (pVal->bValTyp != Number
                 && (iRv = iGetRvalue(&pVal)) != S_SUCCESS)
                {
                    DELETE(pDest);
                    break;
                }

                if (pVal->bValTyp != Number)
                {
                    sprintf(acWhyBuf,
                "iExecStore: Value assigned to BankField must be Number, not %d",
                              pVal->bValTyp);
                    pcWhy = acWhyBuf;
                    DELETE(pDest);
                    iRv = S_ERROR;
                    break;
                }
                /* Delete descriptor that points to name,
                 * and point to descriptor for name's value instead.
                 */
                DELETE(pDest);
                pDest = pvNsValPtr(nTemp);
                if ((OBJECT_DESCRIPTOR *)0 == pDest)
                {
                    pcWhy = "iExecStore/BankField:internal error: null old-value pointer";
                    iRv = S_ERROR;
                    break;
                }
                if (BankField != pDest->bValTyp)
                {
                    sprintf(acWhyBuf,
        "iExecStore/BankField:internal error: Name %4.4s type %d does not match value-type %d at %p",
                              nTemp, iNsValType(nTemp), pDest->bValTyp, pDest);
                    pcWhy = acWhyBuf;
                    vAmlAppendBlockOwner(pDest);
                    iRv = S_ERROR;
                    break;
                }

                /* Set Bank value to select proper Bank */
                /* Check lock rule prior to modifing the field */
                if (pDest->sBankField.wLockRule == (WORD)Lock)
                {/* Lock Rule is Lock */
                    if (iGetGlobalLock() == S_ERROR)
                    {
                        /* the ownship failed - Bad Bad Bad, this is a single threaded */
                        /* implementation so there is no way some other process should */
                        /* own this.  This means something grabbed it and did not */
                        /* release the Global Lock! (pcWhy will already be set) */
                        return (S_ERROR);
                    }
                    else
                    {
                        /* perform the update */
                        iRv = iSetNamedFieldValue(pDest->sBankField.hBankSelect,
                                                            pDest->sBankField.dBankVal);
                    }
                    /* Release the Global Lock */
                    vReleaseGlobalLock();
                }
                else
                {/* Lock Rule is NoLock */
                    /* perform the update */
                    iRv = iSetNamedFieldValue(pDest->sBankField.hBankSelect,
                                                        pDest->sBankField.dBankVal);
                }
                if (debug_level() > 2)
                    fprintf_bu(iLstFileHandle, LOGFILE,
                            "\nset bank select returned %s", RV[iRv]);

                if (S_SUCCESS == iRv)
                {
                    if (debug_level() > 2)
                        fprintf_bu(iLstFileHandle, LOGFILE, " about to set data");
                    /* Set Data value */
                    iRv = iSetNamedFieldValue(pDest->sBankField.hBankSelect,
                                                      pVal->sBankField.dBankVal);
                    if (debug_level() > 2)
                        fprintf_bu(iLstFileHandle, LOGFILE,
                                "\nset bank select returned %s", RV[iRv]);
                }
                break;


            case DefField:
                /* Storing into a Field defined in a Region.
                 * If value is not a Number, try to resolve it to one.
                 */
                if (pVal->bValTyp != Number
                 && (iRv = iGetRvalue(&pVal)) != S_SUCCESS)
                {
                    DELETE(pDest);
                    break;
                }

                if (pVal->bValTyp != Number)
                {
                    sprintf(acWhyBuf,
            "iExecStore/DefField: Value assigned to Field must be Number, not %d",
                              pVal->bValTyp);
                    pcWhy = acWhyBuf;
                    DELETE(pDest);
                    iRv = S_ERROR;
                    break;
                }
                /* Delete descriptor that points to name,
                 * and point to descriptor for name's value instead.
                 */
                DELETE(pDest);
                pDest = pvNsValPtr(nTemp);
                if ((OBJECT_DESCRIPTOR *)0 == pDest)
                {
                    pcWhy = "iExecStore/DefField:internal error: null old-value pointer";
                    iRv = S_ERROR;
                    break;
                }
                if (DefField != pDest->bValTyp)
                {
                    sprintf(acWhyBuf,
            "iExecStore/DefField:internal error: Name %4.4s type %d does not match value-type %d at %p",
                        nTemp, iNsValType(nTemp), pDest->bValTyp, pDest);
                    pcWhy = acWhyBuf;
                    vAmlAppendBlockOwner(pDest);
                    iRv = S_ERROR;
                    break;
                }
                /* Check lock rule prior to modifing the field */
                if (pVal->sField.wLockRule == (WORD)Lock)
                {/* Lock Rule is Lock */
                    if (iGetGlobalLock() == S_ERROR)
                    {
                        /* the ownship failed - Bad Bad Bad, this is a single threaded */
                        /* implementation so there is no way some other process should */
                        /* own this.  This means something grabbed it and did not */
                        /* release the Global Lock! (pcWhy will already be set) */
                        return (S_ERROR);
                    }
                    else
                    {
                        /* perform the update */
                        iRv = iSetNamedFieldValue(nTemp, pVal->sNumber.dNumber);
                    }
                    /* Release the Global Lock */
                    vReleaseGlobalLock();
                }
                else
                {/* Lock Rule is NoLock */
                    /* perform the update */
                    iRv = iSetNamedFieldValue(nTemp, pVal->sNumber.dNumber);
                }
                break;

            case IndexField:
                /* Storing into an IndexField.
                 * If value is not a Number, try to resolve it to one.
                 */
                if (pVal->bValTyp != Number
                 && (iRv = iGetRvalue(&pVal)) != S_SUCCESS)
                {
                    DELETE(pDest);
                    break;
                }

                if (pVal->bValTyp != Number)
                {
                    sprintf(acWhyBuf,
                "iExecStore: Value assigned to IndexField must be Number, not %d",
                              pVal->bValTyp);
                    pcWhy = acWhyBuf;
                    DELETE(pDest);
                    iRv = S_ERROR;
                    break;
                }
                /* Delete descriptor that points to name,
                 * and point to descriptor for name's value instead.
                 */
                DELETE(pDest);
                pDest = pvNsValPtr(nTemp);
                if ((OBJECT_DESCRIPTOR *)0 == pDest)
                {
                    pcWhy = "iExecStore/IndexField:internal error: null old-value pointer";
                    iRv = S_ERROR;
                    break;
                }
                if (IndexField != pDest->bValTyp)
                {
                    sprintf(acWhyBuf,
        "iExecStore/IndexField:internal error: Name %4.4s type %d does not match value-type %d at %p",
                              nTemp, iNsValType(nTemp), pDest->bValTyp, pDest);
                    pcWhy = acWhyBuf;
                    vAmlAppendBlockOwner(pDest);
                    iRv = S_ERROR;
                    break;
                }

                /* Set Index value to select proper Data register */
                /* Check lock rule prior to modifing the field */
                if (pDest->sIndexField.wLockRule == (WORD)Lock)
                {/* Lock Rule is Lock */
                    if (iGetGlobalLock() == S_ERROR)
                    {
                        /* the ownship failed - Bad Bad Bad, this is a single threaded */
                        /* implementation so there is no way some other process should */
                        /* own this.  This means something grabbed it and did not */
                        /* release the Global Lock! (pcWhy will already be set) */
                        return (S_ERROR);
                    }
                    else
                    {
                        /* perform the update */
                        iRv = iSetNamedFieldValue(pDest->sIndexField.hIndex,
                                                          pDest->sIndexField.dIndexVal);
                    }
                    /* Release the Global Lock */
                    vReleaseGlobalLock();
                }
                else
                {/* Lock Rule is NoLock */
                    /* perform the update */
                    iRv = iSetNamedFieldValue(pDest->sIndexField.hIndex,
                                                      pDest->sIndexField.dIndexVal);
                }
                iRv = iSetNamedFieldValue(pDest->sIndexField.hIndex,
                                                  pDest->sIndexField.dIndexVal);
                if (debug_level() > 2)
                    fprintf_bu(iLstFileHandle, LOGFILE,
                            "\nset index returned %s", RV[iRv]);

                if (S_SUCCESS == iRv)
                {
                    if (debug_level() > 2)
                        fprintf_bu(iLstFileHandle, LOGFILE, " about to set data");
                    /* Set Data value */
                    iRv = iSetNamedFieldValue(pDest->sIndexField.hData,
                                                      pVal->sNumber.dNumber);
                    if (debug_level() > 2)
                        fprintf_bu(iLstFileHandle, LOGFILE,
                                "\nset data returned %s", RV[iRv]);
                }
                break;

            case FieldUnit:
                /* Storing into a FieldUnit (defined in a Buffer).
                 * If value is not a Number, try to resolve it to one.
                 */
                if (pVal->bValTyp != Number
                 && (iRv = iGetRvalue(&pVal)) != S_SUCCESS)
                {
                    DELETE(pDest);
                    break;
                }

                if (pVal->bValTyp != Number)
                {
                    sprintf(acWhyBuf,
            "iExecStore/FieldUnit: Value assigned to Field must be Number, not %d",
                              pVal->bValTyp);
                    pcWhy = acWhyBuf;
                    DELETE(pDest);
                    iRv = S_ERROR;
                    break;
                }
                /* Delete descriptor that points to name,
                 * and point to descriptor for name's value instead.
                 */
                DELETE(pDest);
                pDest = pvNsValPtr(nTemp);
                if ((OBJECT_DESCRIPTOR *)0 == pDest)
                {
                    pcWhy = "iExecStore/FieldUnit:internal error: null old-value pointer";
                    iRv = S_ERROR;
                    break;
                }
                if (pDest->bValTyp != (BYTE)iNsValType(nTemp))
                {
                    sprintf(acWhyBuf,
        "iExecStore/FieldUnit:internal error: Name %4.4s type %d does not match value-type %d at %p",
                              nTemp, iNsValType(nTemp), pDest->bValTyp, pDest);
                    pcWhy = acWhyBuf;
                    vAmlAppendBlockOwner(pDest);
                    iRv = S_ERROR;
                    break;
                }

                if (!pDest->sFieldUnit.pContainer
                 || Buffer != pDest->sFieldUnit.pContainer->bValTyp
                 || pDest->sFieldUnit.dConSeq
                     != pDest->sFieldUnit.pContainer->sBuffer.dSequence)
                {
                    char *pcFQN = pcNsFullyQualifiedName(nTemp);

                    if (debug_level() > 0)
                    {
                        printf_bu("\niExecStore/FieldUnit: bad container in %s (%p)\n",
                                     pcFQN, nTemp);
                        vNsDumpEntry(nTemp, SCREEN|LOGFILE);
                    }
                    sprintf(acWhyBuf,
                                "iExecStore/FieldUnit: bad container %p in %s",
                                pDest->sFieldUnit.pContainer, pcFQN);
                    pcWhy = acWhyBuf;
                    iRv = S_ERROR;
                    break;
                }

                /* Check lock rule prior to modifing the field */
                if (pDest->sFieldUnit.wLockRule == (WORD)Lock)
                {/* Lock Rule is Lock */
                    if (iGetGlobalLock() == S_ERROR)
                    {
                        /* the ownship failed - Bad Bad Bad, this is a single threaded */
                        /* implementation so there is no way some other process should */
                        /* own this.  This means something grabbed it and did not */
                        /* release the Global Lock! (pcWhy will already be set) */
                        return (S_ERROR);
                    }
                    else
                    {
                        /* Set the Locked Flag */
                        iLocked = TRUE;
                    }
                }
                if (pDest->sFieldUnit.wDatLen + pDest->sFieldUnit.wBitOffset > 32)
                {
                    if (iLocked)
                    {
                        /* Release the Global Lock */
                        vReleaseGlobalLock();
                        iLocked = FALSE;
                    }
                    pcWhy = "iExecStore/FieldUnit:implementation limitation: Field exceeds DWORD";
                    iRv = S_ERROR;
                }
                else
                {
                    /* Field location is (base of buffer) + (byte offset) */
                    BYTE *pbLoc = pDest->sFieldUnit.pContainer->sBuffer.pbBuffer
                                    + pDest->sFieldUnit.dOffset;
                    /* Construct dMask with 1 bits where the field is,
                     * 0 bits elsewhere
                     */
                    DWORD dMask = ((DWORD)1 << pDest->sFieldUnit.wDatLen) - (DWORD)1
                                      << pDest->sFieldUnit.wBitOffset;

                    if (Trace & TraceBufFld)
                        fprintf_bu(iLstFileHandle, LOGFILE,
                            "\n** Store %lx in buffer %p byte %ld bit %d width %d addr %p mask %08lx",
                            pVal->sNumber.dNumber,
                            pDest->sFieldUnit.pContainer->sBuffer.pbBuffer,
                            pDest->sFieldUnit.dOffset,
                            pDest->sFieldUnit.wBitOffset,
                            pDest->sFieldUnit.wDatLen,
                            pbLoc, dMask);

                    /* zero out the field in the buffer */
                    *(DWORD *)pbLoc &= ~dMask;

                    /* Shift and mask the new value into position,
                     * and or it into the buffer.
                     */
                    *(DWORD *)pbLoc
                    |= (pVal->sNumber.dNumber << pDest->sFieldUnit.wBitOffset) & dMask;
                    if (Trace & TraceBufFld)
                        fprintf_bu(iLstFileHandle, LOGFILE,
                            " val %08lx", *(DWORD *)pbLoc);

                    iRv = S_SUCCESS;
                }
                if (iLocked)
                {
                    /* Release the Global Lock */
                    vReleaseGlobalLock();
                    iLocked = FALSE;
                }
                break;

            default:
                /* All other types than Alias and the various Fields come here.
                 * Store a copy of pVal as the new value of the Name, and set
                 * the Name's type to that of the value being stored in it.
                 */
                memcpy((void *)pDest, (void *)pVal, sizeof(*pVal));
                if (Buffer == pDest->bValTyp)
                    /* Assign a new sequence number */
                    pDest->sBuffer.dSequence = dAmlBufSeq();
                vNsSetValue(nTemp, pDest, pDest->bValTyp);

                if (iStacked && debug_level() > 0)
                {
                    printf_bu("\niExecStore: set %s (%p)\n",
                                 pcNsFullyQualifiedName(nTemp), nTemp);
                    vNsDumpEntry(nTemp, SCREEN|LOGFILE);
                    iDumpStackEntry(pDest);
                }
                iRv = S_SUCCESS;
                break;
        }
        break;

    case ZeroOp: case OneOp: case OnesOp:
        /* Storing to a constant is a no-op -- see spec sec 15.2.3.3.1.
         * Delete the result descriptor.
         */
        DELETE(pDest);
        iRv = S_SUCCESS;
        break;

    case Local0: case Local1: case Local2: case Local3:
    case Local4: case Local5: case Local6: case Local7:
        iRv = iSetMethodValue(LCLBASE + pDest->sLvalue.bOpCode - Local0, pVal, pDest);
        break;

    case Arg0: case Arg1: case Arg2: case Arg3:
    case Arg4: case Arg5: case Arg6:
        iRv = iSetMethodValue(ARGBASE + pDest->sLvalue.bOpCode - Arg0, pVal, pDest);
        break;

    case Debug1:
        /* Storing to the Debug object causes the value stored to be
         * displayed and otherwise has no effect -- see sec. 15.2.3.3.3.
         */
        fprintf_bu(iLstFileHandle, LOGFILE, "\nDebugOp: ");
        iDumpStackEntry(pVal);
        DELETE(pDest);
        iRv = S_SUCCESS;
        break;

#if 0
    case IndexOp:
        break;
#endif

    default:
        sprintf(acWhyBuf,
                    "iExecStore:internal error: Unknown Lvalue subtype %02x",
                    pDest->sLvalue.bOpCode);
        pcWhy = acWhyBuf;
        fprintf_bu(iLstFileHandle, LOGFILE,
                    "\niExecStore:internal error: Unknown Lvalue subtype %02x",
                    pDest->sLvalue.bOpCode);
        _dump_buf(pDest, sizeof(OBJECT_DESCRIPTOR), ASCII | HEX,
                         iLstFileHandle, LOGFILE);
        DELETE(pDest);
        iRv = S_ERROR;
    }   /* switch(pDest->sLvalue.bOpCode) */

    if (iStacked)
        --iObjStackTop;

    return iRv;
}

/*****************************************************************************
 * FUNCTION:        static int iGetFieldUnitValue(OBJECT_DESCRIPTOR *pField ...)
 *
 * PARAMETERS:      OBJECT_DESCRIPTOR *pField   points to a FIeldUnit
 *
 *                      OBJECT_DESCRIPTOR *pResult  points to an empty descriptor
 *                                                          which will become a Number
 *                                                          containing the field's value.
 *
 * RETURN:          S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Retrieve the value from a FieldUnit
 *
 *  ALLOCATION:     none
 *
 ****************************************************************************/
static int
iGetFieldUnitValue(OBJECT_DESCRIPTOR *pField, OBJECT_DESCRIPTOR *pResult)
{
    BYTE *pbLoc;
    DWORD dMask;
    int iLocked = FALSE;

#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "iGetFieldUnitValue");
#endif

    if (!pField)
    {
        pcWhy = "iGetFieldUnitValue: internal error: null field pointer";
        return S_ERROR;
    }
    if (!pField->sFieldUnit.pContainer)
    {
        pcWhy = "iGetFieldUnitValue: internal error: null container pointer";
        return S_ERROR;
    }
    if (Buffer != pField->sFieldUnit.pContainer->bValTyp)
    {
        pcWhy = "iGetFieldUnitValue: internal error: container is not a Buffer";
        return S_ERROR;
    }
    if (pField->sFieldUnit.dConSeq
         != pField->sFieldUnit.pContainer->sBuffer.dSequence)
    {
        sprintf(acWhyBuf,
                "iGetFieldUnitValue: internal error: stale Buffer [%lx != %lx]",
                pField->sFieldUnit.dConSeq,
                pField->sFieldUnit.pContainer->sBuffer.dSequence);
        pcWhy = acWhyBuf;
        return S_ERROR;
    }
    if (!pResult)
    {
        pcWhy = "iGetFieldUnitValue: internal error: null result pointer";
        return S_ERROR;
    }

                /* Check lock rule prior to modifing the field */
                if (pField->sFieldUnit.wLockRule == (WORD)Lock)
                {/* Lock Rule is Lock */
                    if (iGetGlobalLock() == S_ERROR)
                    {
                        /* the ownship failed - Bad Bad Bad, this is a single threaded */
                        /* implementation so there is no way some other process should */
                        /* own this.  This means something grabbed it and did not */
                        /* release the Global Lock! (pcWhy will already be set) */
                        return (S_ERROR);
                    }
                    else
                    {
                        /* set the Locked Flag */
                        iLocked = TRUE;
                    }
                }
    if (pField->sFieldUnit.wDatLen + pField->sFieldUnit.wBitOffset > 32)
    {
        if (iLocked)
        {
            /* Release the Global Lock */
            vReleaseGlobalLock();
            iLocked = FALSE;
        }
        pcWhy
        = "iGetFieldUnitValue: implementation limitation: Field exceeds DWORD";
        return S_ERROR;
    }

    /* Field location is (base of buffer) + (byte offset) */
    pbLoc = pField->sFieldUnit.pContainer->sBuffer.pbBuffer
            + pField->sFieldUnit.dOffset;

    /* Construct dMask with as many 1 bits as the field width */
    dMask = ((DWORD)1 << pField->sFieldUnit.wDatLen) - (DWORD)1;

    pResult->sNumber.bValTyp = (BYTE)Number;

    /* Shift the word containing the field, and mask the value */
    pResult->sNumber.dNumber
        = *(DWORD *)pbLoc >> pField->sFieldUnit.wBitOffset & dMask;

    if (Trace & TraceBufFld)
        fprintf_bu(iLstFileHandle, LOGFILE,
            "\n** Read from buffer %p byte %ld bit %d width %d addr %p mask %08lx val %08lx",
            pField->sFieldUnit.pContainer->sBuffer.pbBuffer,
            pField->sFieldUnit.dOffset,
            pField->sFieldUnit.wBitOffset,
            pField->sFieldUnit.wDatLen,
            pbLoc, dMask, pResult->sNumber.dNumber);
    if (iLocked)
    {
        /* Release the Global Lock */
        vReleaseGlobalLock();
        iLocked = FALSE;
    }

    return S_SUCCESS;
}

/*****************************************************************************
A* FUNCTION:        int iGetRvalue(OBJECT_DESCRIPTOR **ppStackPtr)
 *
 * PARAMETERS:      OBJECT_DESCRIPTOR **ppStackPtr  points to entry on ObjStack,
 *                                                              which can be either an
 *                                                              (OBJECT_DESCRIPTOR *)
 *                                                                  or an NsHandle.
 *
 * RETURN:          S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Convert Lvalue entries on apObjStack to rvalues
 *
 *  ALLOCATION:
A*  Reference       Size                        Pool    Owner           Description
A*  *ppStackPtr     s(OBJECT_DESCRIPTOR)    bu      amlexec     Value
 *
 ****************************************************************************/
int
iGetRvalue(OBJECT_DESCRIPTOR **ppStackPtr)
{
    NsHandle nTemp;
    OBJECT_DESCRIPTOR *pOD;
    int iRv;

#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "iGetRvalue");
#endif

    if ((OBJECT_DESCRIPTOR **)0 == ppStackPtr
     || (OBJECT_DESCRIPTOR *)0 == *ppStackPtr)
    {
        pcWhy = "iGetRvalue:internal error: null pointer";
        return S_ERROR;
    }

    switch ((*ppStackPtr)->bValTyp)
    {
        case Lvalue:
            switch ((*ppStackPtr)->sLvalue.bOpCode)
            {
                BYTE bMvIndex;

                case NameOp:
                    /* Convert indirect name ptr to direct name ptr */
                    nTemp = (*ppStackPtr)->sLvalue.pvRef;
                    DELETE(*ppStackPtr);
                    (*ppStackPtr) = nTemp;
                    iRv = S_SUCCESS;
                    break;

                case Local0: case Local1: case Local2: case Local3:
                case Local4: case Local5: case Local6: case Local7:
                    if (debug_level() > 0)
                        fprintf_bu(iLstFileHandle, LOGFILE,
                            "\niGetRvalue:Lcl%d: before iGetMethodValue %p %p %08lx ",
                            bMvIndex = (*ppStackPtr)->sLvalue.bOpCode - Local0,
                            ppStackPtr, *ppStackPtr, *(DWORD *)*ppStackPtr);
                    iRv = iGetMethodValue(
                                    LCLBASE + (*ppStackPtr)->sLvalue.bOpCode - Local0,
                                    *ppStackPtr);
                    if (debug_level() > 0)
                    {
                        fprintf_bu(iLstFileHandle, LOGFILE,
                                    "\niGetRvalue:Lcl%d: iGMV iRv=%s %p %p %08lx ",
                                    bMvIndex, RV[iRv], ppStackPtr, *ppStackPtr,
                                    *(DWORD *)*ppStackPtr);
                        if (Number == (*ppStackPtr)->bValTyp)
                            /* Value is a Number */
                            fprintf_bu(iLstFileHandle, LOGFILE,
                                    "[%ld] ", (*ppStackPtr)->sNumber.dNumber);
                    }
                    break;

                case Arg0: case Arg1: case Arg2: case Arg3:
                case Arg4: case Arg5: case Arg6:
                    if (debug_level() > 0)
                        fprintf_bu(iLstFileHandle, LOGFILE,
                            "\niGetRvalue:Arg%d: before iGetMethodValue %p %p %08lx ",
                            bMvIndex = (*ppStackPtr)->sLvalue.bOpCode - Arg0,
                            ppStackPtr, *ppStackPtr, *(DWORD *)*ppStackPtr);
                    iRv = iGetMethodValue(
                                    ARGBASE + (*ppStackPtr)->sLvalue.bOpCode - Arg0,
                                    *ppStackPtr);
                    if (debug_level() > 0)
                    {
                        fprintf_bu(iLstFileHandle, LOGFILE,
                                    "\niGetRvalue:Arg%d: iGMV returned %s %p %p %08lx ",
                                    bMvIndex, RV[iRv], ppStackPtr, *ppStackPtr,
                                    *(DWORD *)*ppStackPtr);
                        if (Number == (*ppStackPtr)->bValTyp)
                            /* Value is a Number */
                            fprintf_bu(iLstFileHandle, LOGFILE,
                                    "[%ld] ", (*ppStackPtr)->sNumber.dNumber);
                    }
                    break;

                case ZeroOp:
                    (*ppStackPtr)->bValTyp = (BYTE)Number;
                    (*ppStackPtr)->sNumber.dNumber = 0;
                    iRv = S_SUCCESS;
                    break;

                case OneOp:
                    (*ppStackPtr)->bValTyp = (BYTE)Number;
                    (*ppStackPtr)->sNumber.dNumber = 1;
                    iRv = S_SUCCESS;
                    break;

                case OnesOp:
                    (*ppStackPtr)->bValTyp = (BYTE)Number;
                    (*ppStackPtr)->sNumber.dNumber = 0xFFFFFFFF;
                    iRv = S_SUCCESS;
                    break;

                default:
                    sprintf(acWhyBuf, "iGetRvalue: Unknown Lvalue subtype %02x",
                            (*ppStackPtr)->sLvalue.bOpCode);
                    pcWhy = acWhyBuf;
                    iRv = S_ERROR;
            }   /* switch ((*ppStackPtr)->sLvalue.bOpCode) */

            if (S_SUCCESS != iRv)
                return iRv;
            break;

        case FieldUnit:
            pOD = NEW(OBJECT_DESCRIPTOR);
            if ((OBJECT_DESCRIPTOR *)0 == pOD)
            {
                vKFatalError("0007", ("iGetRvalue: Descriptor Allocation Failure"));
                return S_ERROR;
            }

            if ((iRv = iGetFieldUnitValue(*ppStackPtr, pOD)) != S_SUCCESS)
                DELETE(pOD);
            *ppStackPtr = (void *)pOD;
            return iRv;

        case BankField:
            pOD = NEW(OBJECT_DESCRIPTOR);
            if ((OBJECT_DESCRIPTOR *)0 == pOD)
            {
                vKFatalError("0008", ("iGetRvalue: Descriptor Allocation Failure"));
                return S_ERROR;
            }

            if ((iRv = iGetFieldUnitValue(*ppStackPtr, pOD)) != S_SUCCESS)
                DELETE(pOD);
            *ppStackPtr = (void *)pOD;
            return iRv;
            break;
        /* XXX - may need to handle sIndexField, and DefField someday */
        default:
            break;
    }   /* switch ((*ppStackPtr)->bValTyp) */

    if (iIsNsHandle(*ppStackPtr))       /* direct name ptr */
    {
        OBJECT_DESCRIPTOR *pVal
            = (OBJECT_DESCRIPTOR *)pvNsValPtr((NsHandle)*ppStackPtr);

        if (Trace & TraceExec)
            fprintf_bu(iLstFileHandle, LOGFILE,
                          "iGetRvalue: found direct name ptr ");

        switch (iNsValType((NsHandle)*ppStackPtr))
        {
            DWORD dTemp;

            case Package:
                /* pVal should point to either an OBJECT_DESCRIPTOR of
                 * type Package, or an initialization in the AML stream.
                 */
                if ((OBJECT_DESCRIPTOR *)0 == pVal)
                {
                    pcWhy = "iGetRvalue/Package:internal error: null ValPtr";
                    return S_ERROR;
                }
                if (PackageOp == *(BYTE *)pVal)
                {
                    /* The value pointer in the name table entry
                     * points to a package definition in the AML stream.
                     * Convert it to an object.
                     */
                    if (S_SUCCESS != (iRv = iPushIfExec(Exec)))         /* ObjStack */
                        return iRv;
                    if (S_SUCCESS == (iRv = PushExec((BYTE *)pVal + 1, 0L)) /*PkgStack*/
                     && S_SUCCESS == (iRv = DoPkg(Package, Exec))
                     && S_SUCCESS == (iRv = PopExec()))                     /* PkgStack */
                    {
                        vNsSetValue((NsHandle)*ppStackPtr,
                                        apObjStack[iObjStackTop],
                                        (BYTE)Package);
                        /* Refresh local value pointer to reflect newly set value */
                        pVal = (OBJECT_DESCRIPTOR *)pvNsValPtr((NsHandle)*ppStackPtr);
                        --iObjStackTop;
                    }
                    else
                    {
                        --iObjStackTop;
                        return iRv;
                    }
                }
                if (Package != pVal->bValTyp)
                {
                    pcWhy = "iGetRvalue:internal error: Bad package value";
                    return S_ERROR;
                }

                pOD = NEW(OBJECT_DESCRIPTOR);
                if ((OBJECT_DESCRIPTOR *)0 == pOD)
                    vKFatalError("0009", ("iGetRvalue: Descriptor Allocation Failure"));
                memcpy((void *)pOD, (void *)pVal, sizeof(*pOD));
                break;

            case String:
/* XXX - Is there a problem here if the nte points to an AML definition? */
                if (String != pVal->bValTyp)
                {
                    pcWhy = "iGetRvalue:internal error: Bad string value";
                    return S_ERROR;
                }

                pOD = NEW(OBJECT_DESCRIPTOR);
                if ((OBJECT_DESCRIPTOR *)0 == pOD)
                    vKFatalError("0010", ("iGetRvalue: Descriptor Allocation Failure"));
                memcpy((void *)pOD, (void *)pVal, sizeof(*pOD));
                break;

            case Buffer:
                if (BufferOp == *(BYTE *)pVal)
                {
                    /* The value pointer in the name table entry
                     * points to a buffer definition in the AML stream.
                     * Convert it to an object.
                     */
                    if (S_SUCCESS != (iRv = iPushIfExec(Exec)))         /* ObjStack */
                        return iRv;

                    if (S_SUCCESS == (iRv = PushExec((BYTE *)pVal + 1, 0L)) /*PkgStack*/
                     && S_SUCCESS == (iRv = DoPkg(Buffer, Exec))
                     && S_SUCCESS == (iRv = PopExec()))                     /* PkgStack */
                    {
                        vNsSetValue((NsHandle)*ppStackPtr,
                                        apObjStack[iObjStackTop],
                                        (BYTE)Buffer);
                        /* Refresh local value pointer to reflect newly set value */
                        pVal = (OBJECT_DESCRIPTOR *)pvNsValPtr((NsHandle)*ppStackPtr);
                        --iObjStackTop;
                    }
                    else
                    {
                        --iObjStackTop;
                        return iRv;
                    }
                }
                if (Buffer != pVal->bValTyp)
                {
                    pcWhy = "iGetRvalue: Bad buffer value";
                    return S_ERROR;
                }

                pOD = NEW(OBJECT_DESCRIPTOR);
                if ((OBJECT_DESCRIPTOR *)0 == pOD)
                    vKFatalError("0011", ("iGetRvalue: Descriptor Allocation Failure"));
                memcpy((void *)pOD, (void *)pVal, sizeof(*pOD));
                /* Assign a new sequence number */
                pOD->sBuffer.dSequence = dAmlBufSeq();
                if ((Trace & TraceBufFld) && debug_level() > 0)
                {
                    fprintf_bu(iLstFileHandle, LOGFILE,
                            "iGetRvalue: new Buffer descriptor seq %ld @ %p ",
                            pOD->sBuffer.dSequence, pOD);
                }
                break;

            case Number:
                if (Trace & TraceExec)
                    fprintf_bu(iLstFileHandle, LOGFILE, "case Number ");

                if (Number == pVal->bValTyp)
                {
                    pOD = NEW(OBJECT_DESCRIPTOR);
                    if ((OBJECT_DESCRIPTOR *)0 == pOD)
                        vKFatalError("0012", ("iGetRvalue: Descriptor Allocation Failure"));
                    memcpy((void *)pOD, (void *)pVal, sizeof(*pOD));
                }
                else
                {
                    /* nte type is Number, but it does not point to a Number,
                     * so it had better point to a Literal in the AML stream.
                     */
                    if (!iIsInPCodeBlock((BYTE *)pVal))
                    {
                        pcWhy = "iGetRvalue/Number:internal error: not a Number";
                        return S_ERROR;
                    }

                    pOD = NEW(OBJECT_DESCRIPTOR);
                    if ((OBJECT_DESCRIPTOR *)0 == pOD)
                        vKFatalError("0013", ("iGetRvalue: Descriptor Allocation Failure"));
                    switch (*(BYTE *)pVal)
                    {
                        case ZeroOp:
                            pOD->sNumber.dNumber = 0;
                            break;

                        case OneOp:
                            pOD->sNumber.dNumber = 1;
                            break;

                        case OnesOp:
                            pOD->sNumber.dNumber = 0xFFFFFFFF;
                            break;

                        case ByteOp:
                            pOD->sNumber.dNumber = (DWORD)((BYTE *)pVal)[1];
                            break;

                        /* XXX - This case and DWordOp will not work properly
                         * XXX - if the processor's endianness does not match
                         * XXX - that of the AML.
                         */
                        case WordOp:
                            pOD->sNumber.dNumber = (DWORD)*(WORD *)&((BYTE *)pVal)[1];
                            break;

                        case DWordOp:
                            pOD->sNumber.dNumber = *(DWORD *)&((BYTE *)pVal)[1];
                            break;

                        default:
                            DELETE(pOD);
                            sprintf(acWhyBuf,
                                    "iGetRvalue/Number:internal error: Expected AML number, found %02x",
                                    *(BYTE *)pVal);
                            pcWhy = acWhyBuf;
                            return S_ERROR;
                    }
                    pOD->sNumber.bValTyp = (BYTE)Number;
                }
                break;

            case DefField:
                /* XXX - Implementation limitation: Fields are implemented as type
                 * XXX - Number, but they really are supposed to be type Buffer.
                 * XXX - The two are interchangeable only for lengths <= 32 bits.
                 */
                iRv = iGetNamedFieldValue((NsHandle)*ppStackPtr, &dTemp);
                if (S_SUCCESS != iRv)
                    return S_ERROR;

                pOD = NEW(OBJECT_DESCRIPTOR);
                if ((OBJECT_DESCRIPTOR *)0 == pOD)
                    vKFatalError("0014", ("iGetRvalue: Descriptor Allocation Failure"));
                pOD->sNumber.bValTyp = (BYTE)Number;
                pOD->sNumber.dNumber = dTemp;
                break;

            case BankField:
                if (BankField != pVal->bValTyp)
                {
                    sprintf(acWhyBuf,
        "iGetRvalue/BankField:internal error: Name %4.4s type %d does not match value-type %d at %p",
                              *ppStackPtr, BankField, pVal->bValTyp, pVal);
                    pcWhy = acWhyBuf;
                    vAmlAppendBlockOwner(pVal);
                    return S_ERROR;
                }

                /* Set Index value to select proper Data register */
                /* Check lock rule prior to modifing the field */
                if (pOD->sFieldUnit.wLockRule == (WORD)Lock)
                {/* Lock Rule is Lock */
                    if (iGetGlobalLock() == S_ERROR)
                    {
                        /* the ownship failed - Bad Bad Bad, this is a single threaded */
                        /* implementation so there is no way some other process should */
                        /* own this.  This means something grabbed it and did not */
                        /* release the Global Lock! (pcWhy will already be set) */
                        return (S_ERROR);
                    }
                    else
                    {
                        /* perform the update */
                        iRv = iSetNamedFieldValue(pVal->sBankField.hBankSelect,
                                                          pVal->sBankField.dBankVal);
                    }
                    /* Release the Global Lock */
                    vReleaseGlobalLock();
                }
                else
                {/* Lock Rule is NoLock */
                    /* perform the update */
                    iRv = iSetNamedFieldValue(pVal->sBankField.hBankSelect,
                                                      pVal->sBankField.dBankVal);
                }
                if (S_SUCCESS != iRv)
                    return S_ERROR;

                /* Read Data value */
                iRv = iGetNamedFieldValue((NsHandle)pVal->sBankField.pContainer, &dTemp);
                if (S_SUCCESS != iRv)
                    return S_ERROR;

                pOD = NEW(OBJECT_DESCRIPTOR);
                if ((OBJECT_DESCRIPTOR *)0 == pOD)
                    vKFatalError("0015", ("iGetRvalue: Descriptor Allocation Failure"));
                pOD->sNumber.bValTyp = (BYTE)Number;
                pOD->sNumber.dNumber = dTemp;
                break;


            case IndexField:
                if (IndexField != pVal->bValTyp)
                {
                    sprintf(acWhyBuf,
        "iGetRvalue/IndexField:internal error: Name %4.4s type %d does not match value-type %d at %p",
                              *ppStackPtr, IndexField, pVal->bValTyp, pVal);
                    pcWhy = acWhyBuf;
                    vAmlAppendBlockOwner(pVal);
                    return S_ERROR;
                }

                /* Set Index value to select proper Data register */
                /* Check lock rule prior to modifing the field */
                if (pOD->sFieldUnit.wLockRule == (WORD)Lock)
                {/* Lock Rule is Lock */
                    if (iGetGlobalLock() == S_ERROR)
                    {
                        /* the ownship failed - Bad Bad Bad, this is a single threaded */
                        /* implementation so there is no way some other process should */
                        /* own this.  This means something grabbed it and did not */
                        /* release the Global Lock! (pcWhy will already be set) */
                        return (S_ERROR);
                    }
                    else
                    {
                        /* perform the update */
                        iRv = iSetNamedFieldValue(pVal->sIndexField.hIndex,
                                                          pVal->sIndexField.dIndexVal);
                    }
                    /* Release the Global Lock */
                    vReleaseGlobalLock();
                }
                else
                {/* Lock Rule is NoLock */
                    /* perform the update */
                    iRv = iSetNamedFieldValue(pVal->sIndexField.hIndex,
                                                      pVal->sIndexField.dIndexVal);
                }
                if (S_SUCCESS != iRv)
                    return S_ERROR;

                /* Read Data value */
                iRv = iGetNamedFieldValue(pVal->sIndexField.hData, &dTemp);
                if (S_SUCCESS != iRv)
                    return S_ERROR;

                pOD = NEW(OBJECT_DESCRIPTOR);
                if ((OBJECT_DESCRIPTOR *)0 == pOD)
                    vKFatalError("0016", ("iGetRvalue: Descriptor Allocation Failure"));
                pOD->sNumber.bValTyp = (BYTE)Number;
                pOD->sNumber.dNumber = dTemp;
                break;

            case FieldUnit:
                if (pVal->bValTyp != (BYTE)iNsValType((NsHandle)*ppStackPtr))
                {
                    sprintf(acWhyBuf,
      "iGetRvalue/FieldUnit:internal error: Name %4.4s type %d does not match value-type %d at %p",
                              *ppStackPtr, iNsValType((NsHandle)*ppStackPtr),
                              pVal->bValTyp, pVal);
                    pcWhy = acWhyBuf;
                    vAmlAppendBlockOwner(pVal);
                    return S_ERROR;
                    break;
                }
                pOD = NEW(OBJECT_DESCRIPTOR);
                if ((OBJECT_DESCRIPTOR *)0 == pOD)
                    vKFatalError("0017", ("iGetRvalue: Descriptor Allocation Failure"));
                if ((iRv = iGetFieldUnitValue(pVal, pOD)) != S_SUCCESS)
                {
                    DELETE(pOD);
                    return iRv;
                }
                break;

            /* cases which just return the name as the rvalue */
            case Device:
                return S_SUCCESS;
                break;



            case Method:        /* XXX - unimplemented, handled elsewhere */
            case Power:         /* XXX - unimplemented, may not be needed */
            case Processor: /* XXX - unimplemented, may not be needed */
            case Thermal:       /* XXX - unimplemented, may not be needed */
            case Event:         /* XXX - unimplemented, may not be needed */
            case Mutex:         /* XXX - unimplemented, may not be needed */
            case Region:        /* XXX - unimplemented, may not be needed */

            case Any:
                if (Trace & TraceExec)
                    fprintf_bu(iLstFileHandle, LOGFILE, "case %s ",
                            apcNsTypeNames[iNsValType((NsHandle)*ppStackPtr)]);
#ifdef HACK
                fprintf_bu(iLstFileHandle, LOGFILE,
                  "\n** iGetRvalue: Fetch from %s not implemented, using value 0\n",
                  apcNsTypeNames[iNsValType((NsHandle)*ppStackPtr)]);
                pOD = NEW(OBJECT_DESCRIPTOR);
                if ((OBJECT_DESCRIPTOR *)0 == pOD)
                    vKFatalError("0018", ("iGetRvalue: Descriptor Allocation Failure"));
                pOD->sNumber.bValTyp = (BYTE)Number;
                pOD->sNumber.dNumber = 0x0;
                break;
#else
                sprintf(acWhyBuf,
                        "iGetRvalue: Fetch from %s not implemented",
                        apcNsTypeNames[iNsValType((NsHandle)*ppStackPtr)]);
                pcWhy = acWhyBuf;
                return S_ERROR;
#endif /* HACK */

            default:

                if (Trace & TraceExec)
                    fprintf_bu(iLstFileHandle, LOGFILE, "default??? ");

                sprintf(acWhyBuf, "iGetRvalue: Unknown NsType %d",
                        iNsValType((NsHandle)*ppStackPtr));
                pcWhy = acWhyBuf;
                return S_ERROR;
        }
        *ppStackPtr = (void *)pOD;
    }
    return S_SUCCESS;
}

/*****************************************************************************
 * FUNCTION:        int iPrepStack(char *pcTypes)
 *
 * PARAMETERS:      char *pcTypes       String showing operand types needed
 *
 * RETURN:          S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Convert stack entries to required types
 *
 *                      Each character in pcTypes represents one required operand
 *                      and indicates the required bValTyp:
 *                       l => Lvalue, also accepts an entry which is an NsHandle
 *                              instead of an (OBJECT_DESCRIPTOR *))
 *                       n => Number
 *                       s => String or Buffer
 *                       b => Buffer
 *                       i => If
 *                       p => Package
 *                      The corresponding stack entry will be converted to the
 *                      required type if possible, else return S_ERROR.
 *
 ****************************************************************************/
int
iPrepStack(char *pcTypes)
{
    OBJECT_DESCRIPTOR **ppStackPtr
        = (OBJECT_DESCRIPTOR **)&apObjStack[iObjStackTop];
    int iRv;

#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "iPrepStack");
#endif

    /* Ensure room on stack for iGetRvalue() to operate
     * without clobbering top existing entry.
     */
    iRv = iPushIfExec(Exec);
    if (S_SUCCESS != iRv)
        return iRv;

    /* Normal exit is with *pcTypes == '\0' at end of string.
     * Function will return S_ERROR from within the loop upon
     * finding an entry which is not, and cannot be converted
     * to, the required type; if stack underflows; or upon
     * finding a NULL stack entry (which "should never happen").
     */
    while (*pcTypes)
    {
        BYTE bTypeFound;
        char acTypeFound[30], *pcTypeFound;

        if ((OBJECT_DESCRIPTOR *)0 == *ppStackPtr)
        {
            pcWhy = "iPrepStack:internal error: null stack entry";
            --iObjStackTop;
            return S_ERROR;
        }

        bTypeFound = (*ppStackPtr)->bValTyp;
        if (bTypeFound > (BYTE)Lvalue
         || acBadType == apcNsTypeNames[bTypeFound])
        {
            sprintf(acTypeFound, "type encoding %d", bTypeFound);
            pcTypeFound = acTypeFound;
        }
        else if ((BYTE)Lvalue == bTypeFound)
        {
            strcpy(acTypeFound, "Lvalue ");
            switch ((*ppStackPtr)->sLvalue.bOpCode)
            {
                case ZeroOp:
                    strcat(acTypeFound, "Zero");
                    break;
                case OneOp:
                    strcat(acTypeFound, "One");
                    break;
                case OnesOp:
                    strcat(acTypeFound, "Ones");
                    break;
                case Debug1:
                    strcat(acTypeFound, "Debug");
                    break;
                case NameOp:
                    sprintf(&acTypeFound[7], "Name");
                    break;
                case IndexOp:
                    sprintf(&acTypeFound[7], "Index %p",
                                (*ppStackPtr)->sLvalue.pvRef);
                    break;
                case Arg0: case Arg1: case Arg2: case Arg3:
                case Arg4: case Arg5: case Arg6:
                    sprintf(&acTypeFound[7], "Arg%d",
                                (*ppStackPtr)->sLvalue.bOpCode - Arg0);
                    break;
                case Local0: case Local1: case Local2: case Local3:
                case Local4: case Local5: case Local6: case Local7:
                    sprintf(&acTypeFound[7], "Local%d",
                                (*ppStackPtr)->sLvalue.bOpCode - Local0);
                    break;
                default:
                    sprintf(&acTypeFound[7], "??? %02x",
                                (*ppStackPtr)->sLvalue.bOpCode);
                    break;
            }
        }
        else
            pcTypeFound = apcNsTypeNames[bTypeFound];

        switch (*pcTypes++)
        {
            case 'l':                                                       /* need Lvalue */
                if (iIsNsHandle(*ppStackPtr))           /* direct name ptr OK as-is */
                    break;
                if (Lvalue != (*ppStackPtr)->bValTyp)
                {
                    sprintf(acWhyBuf, "iPrepStack: Needed Lvalue, found %s",
                                pcTypeFound);
                    pcWhy = acWhyBuf;
                    --iObjStackTop;
                    return S_ERROR;
                }
                if (NameOp == (*ppStackPtr)->sLvalue.bOpCode)
                {
                    /* Convert indirect name ptr to direct name ptr */
                    NsHandle nTemp = (*ppStackPtr)->sLvalue.pvRef;
                    DELETE(*ppStackPtr);
                    (*ppStackPtr) = nTemp;
                }
                break;

            case 'n':                                                       /* need Number */
                if ((iRv = iGetRvalue(ppStackPtr)) != S_SUCCESS)
                {
                    if (debug_level() > 0)
                        fprintf_bu(iLstFileHandle, LOGFILE,
                                      "iPrepStack:n: iGetRvalue returned %s\n", RV[iRv]);
                    --iObjStackTop;
                    return iRv;
                }

                if (Trace & TraceExec)
                    fprintf_bu(iLstFileHandle, LOGFILE,
                                  "iGetRvalue returned S_SUCCESS\n");

                if (Number != (*ppStackPtr)->bValTyp)
                {
                    sprintf(acWhyBuf, "iPrepStack: Needed Number, found %s",
                                pcTypeFound);
                    pcWhy = acWhyBuf;
                    --iObjStackTop;
                    return S_ERROR;
                }
                break;

            case 's':                                       /* need String (or Buffer) */
                if ((iRv = iGetRvalue(ppStackPtr)) != S_SUCCESS)
                {
                    --iObjStackTop;
                    return iRv;
                }

                if (Trace & TraceExec)
                    fprintf_bu(iLstFileHandle, LOGFILE,
                                  "iGetRvalue returned S_SUCCESS\n");

                if (String != (*ppStackPtr)->bValTyp
                 && Buffer != (*ppStackPtr)->bValTyp)
                {
                    sprintf(acWhyBuf,
                            "iPrepStack: Needed String or Buffer, found %s",
                                pcTypeFound);
                    pcWhy = acWhyBuf;
                    --iObjStackTop;
                    return S_ERROR;
                }
                break;

            case 'b':                                                       /* need Buffer */
                if ((iRv = iGetRvalue(ppStackPtr)) != S_SUCCESS)
                {
                    --iObjStackTop;
                    return iRv;
                }

                if (Trace & TraceExec)
                    fprintf_bu(iLstFileHandle, LOGFILE,
                                  "iGetRvalue returned S_SUCCESS\n");

                if (Buffer != (*ppStackPtr)->bValTyp)
                {
                    sprintf(acWhyBuf, "iPrepStack: Needed Buffer, found %s",
                                pcTypeFound);
                    pcWhy = acWhyBuf;
                    --iObjStackTop;
                    return S_ERROR;
                }
                break;

            case 'i':                                                           /* need If */
                if (If != (*ppStackPtr)->bValTyp)
                {
                    sprintf(acWhyBuf, "iPrepStack: Needed If, found %s",
                                pcTypeFound);
                    pcWhy = acWhyBuf;
                    --iObjStackTop;
                    return S_ERROR;
                }
                break;

            case 'p':                                                       /* need Package */
                if ((iRv = iGetRvalue(ppStackPtr)) != S_SUCCESS)
                {
                    --iObjStackTop;
                    return iRv;
                }

                if (Trace & TraceExec)
                    fprintf_bu(iLstFileHandle, LOGFILE,
                                  "iGetRvalue returned S_SUCCESS\n");

                if (Package != (*ppStackPtr)->bValTyp)
                {
                    sprintf(acWhyBuf, "iPrepStack: Needed Package, found %s",
                                pcTypeFound);
                    pcWhy = acWhyBuf;
                    --iObjStackTop;
                    return S_ERROR;
                }
                break;

            default:
                sprintf(acWhyBuf,
                            "iPrepStack:internal error Unknown type flag %02x",
                            *--pcTypes);
                pcWhy = acWhyBuf;
                --iObjStackTop;
                return S_ERROR;
        }   /* switch (*pcTypes++) */

        /* If more operands needed, decrement ppStackPtr to point
         * to next operand on stack (after checking for underflow).
         */
        if (*pcTypes)
        {
            /* Don't try to decrement below bottom of stack */
            if ((OBJECT_DESCRIPTOR **)&apObjStack[0] == ppStackPtr)
            {
                pcWhy = "iPrepStack: not enough operands";
                --iObjStackTop;
                return S_ERROR;
            }
            --ppStackPtr;
        }

    }   /* while (*pcTypes) */

    --iObjStackTop;
    return S_SUCCESS;
}

/*****************************************************************************
 * FUNCTION:        void vAmlAppendOperandDiag(char *pcFN, int iLine ...)
 *
 * PARAMETERS:      char *pcFN      Name of source file
 *                      int iLine       Line Number in file
 *                      WORD wOpCode    OpCode being executed
 *                      int iNOperands  Number of operands iPrepStack tried to check
 *
 * DESCRIPTION: Append diagnostic information about operands to acWhyBuf
 *                      This function is intended to be called after iPrepStack
 *                      has returned S_ERROR.
 *
 ****************************************************************************/
void
vAmlAppendOperandDiag(char *pcFN, int iLine, WORD wOpCode, int iNOperands)
{
    meth sM;

    if (pcWhy != acWhyBuf)
    {
        /* Copy message to acWhyBuf */
        strcpy(acWhyBuf, pcWhy);
        pcWhy = acWhyBuf;
    }

    vGetCurrentLoc(&sM);
    sprintf(&acWhyBuf[strlen(acWhyBuf)], " [%s:%d, op = %s AML offset %04x]",
            pcFN, iLine,
            (wOpCode > UCHAR_MAX)
                ? apcLongOps[wOpCode & 0x00ff]
                : apcShortOps[wOpCode],
            sM.iOffset);

    if (debug_level() > 0)
    {
        int iTraceWas = Trace;

        /* Turn on TraceExec to enable output from vDumpStack() */
        Trace |= TraceExec;
        vDumpStack(Exec,
                      (wOpCode > UCHAR_MAX)
                      ? apcLongOps[wOpCode & 0x00ff]
                      : apcShortOps[wOpCode],
                      iNOperands,
                      "after iPrepStack failed");
        Trace = iTraceWas;
    }
}

/*****************************************************************************
A* FUNCTION:        int iExecMonadic1(WORD op)
 *
 * PARAMETERS:      WORD op  The opcode to be executed
 *
 * RETURN:          S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Execute Type 1 monadic operator
 *                      with numeric operand on object stack
 *
A*  ALLOCATION:     Deletes the operand
 *
 ****************************************************************************/
int
iExecMonadic1(WORD op)
{
    OBJECT_DESCRIPTOR *op1;
    int iRv;

#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "iExecMonadic1");
#endif

    if (SleepOp == op || StallOp == op)
        iRv = iPrepStack("n");                      /* operand should be a Number */
    else
        iRv = iPrepStack("l");                      /* operand should be an Lvalue */

    if (iRv != S_SUCCESS)
    {
        vAmlAppendOperandDiag(__FILE__, __LINE__, op, 1);
        return iRv;
    }

    vDumpStack(Exec, apcLongOps[op & 0x00ff], 1, "after iPrepStack");

    op1 = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop];

    switch (op)
    {
        case ReleaseOp:
            if (Mutex != op1->bValTyp)
            {
                sprintf(acWhyBuf,
                        "iExecMonadic1/ReleaseOp: Needed Mutex, found %d",
                        op1->bValTyp);
                pcWhy = acWhyBuf;
                return S_ERROR;
            }
            return (iReleaseOpRqst(op1));


        case ResetOp:
            if (Event != op1->bValTyp)
            {
                sprintf(acWhyBuf,
                    "iExecMonadic1/ResetOp: Needed Event, found %d", op1->bValTyp);
                pcWhy = acWhyBuf;
                return S_ERROR;
            }
            return (iResetOpRqst(op1));


        case SignalOp:
            if (Event != op1->bValTyp)
            {
                sprintf(acWhyBuf,
                    "iExecMonadic1/SignalOp: Needed Event, found %d", op1->bValTyp);
                pcWhy = acWhyBuf;
                return S_ERROR;
            }
            return (iSignalOpRqst(op1));


        case SleepOp:
#ifndef RMX
            vDoSuspend(op1->sNumber.dNumber);
            break;
#else
            pcWhy = "iExecMonadic1: SleepOp not implemented on RMX";
            return S_ERROR;
#endif

        case StallOp:
#ifndef RMX
            bsleep_microseconds(op1->sNumber.dNumber);
            break;
#else
            /* XXX - this is supposed to NOT yield the processor, so should
             * XXX - busy-wait.  RMX has no corresponding service.
             */
            pcWhy = "iExecMonadic1: StallOp not implemented on RMX";
            return S_ERROR;
#endif

        default:
            sprintf(acWhyBuf, "iExecMonadic1: Unknown monadic opcode %02x", op);
            pcWhy = acWhyBuf;
            return S_ERROR;
    }
    DELETE(op1);
    return S_SUCCESS;
}

/*****************************************************************************
 * FUNCTION:        int iExecMonadic2R(WORD op)
 *
 * PARAMETERS:      WORD op  The opcode to be executed
 *
 * RETURN:          S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Execute Type 2 monadic operator with numeric operand and
 *                      result operand on operand stack
 *
 ****************************************************************************/
int
iExecMonadic2R(WORD op)
{
    OBJECT_DESCRIPTOR *op1, *res;
    DWORD dResVal;
    int rv;

#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "iExecMonadic2R");
#endif

    rv = iPrepStack("ln");

    if (rv != S_SUCCESS)
    {
        /* This was added since it is allowable to return a buffer so */
        /* ln is a local and a number and that will fail.  lb is a local */
        /* and a buffer which will pass.  */
        rv = iPrepStack("lb");

        if (rv != S_SUCCESS)
        {
            vAmlAppendOperandDiag(__FILE__, __LINE__, op, 2);
            return rv;
        }
    }

    vDumpStack(Exec, apcShortOps[op], 2, "after iPrepStack");

    res = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop];
    op1 = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop - 1];

    switch (op)
    {
        int d0, d1, d2, d3;

        case BitNotOp:
            op1->sNumber.dNumber = ~op1->sNumber.dNumber;
            break;

        case FindSetLeftBitOp:
            for (dResVal = 0 ; op1->sNumber.dNumber && dResVal < 33 ; ++dResVal)
                op1->sNumber.dNumber >>= 1;
            op1->sNumber.dNumber = dResVal;
            break;

        case FindSetRightBitOp:
            for (dResVal = 0 ; op1->sNumber.dNumber && dResVal < 33 ; ++dResVal)
                op1->sNumber.dNumber <<= 1;
            op1->sNumber.dNumber = dResVal == 0 ? 0 : 33 - dResVal;
            break;

        case FromBCDOp:
            d0 = (int)(op1->sNumber.dNumber & 15);
            d1 = (int)(op1->sNumber.dNumber >> 4 & 15);
            d2 = (int)(op1->sNumber.dNumber >> 8 & 15);
            d3 = (int)(op1->sNumber.dNumber >> 12 & 15);
            if (d0 > 9 || d1 > 9 || d2 > 9 || d3 > 9)
            {
                sprintf(acWhyBuf,
                        "iExecMonadic2R/FromBCDOp: improper BCD digit %d %d %d %d",
                        d3, d2, d1, d0);
                pcWhy = acWhyBuf;
                return S_ERROR;
            }
            op1->sNumber.dNumber = d0 + d1 * 10 + d2 * 100 + d3 * 1000;
            break;

        case ToBCDOp:
            if (op1->sNumber.dNumber > 9999)
            {
                pcWhy = "iExecMonadic2R/ToBCDOp: BCD overflow";
                return S_ERROR;
            }
            op1->sNumber.dNumber
                = op1->sNumber.dNumber % 10
                + (op1->sNumber.dNumber / 10 % 10 << 4)
                + (op1->sNumber.dNumber / 100 % 10 << 8)
                + (op1->sNumber.dNumber / 1000 % 10 << 12);
            break;

        case ShiftLeftBitOp:
        case ShiftRightBitOp:
        case CondRefOfOp:
            sprintf(acWhyBuf, "iExecMonadic2R: %s unimplemented",
                    (op > UCHAR_MAX) ? apcLongOps[op & 0x00ff] : apcShortOps[op]);
            pcWhy = acWhyBuf;
            return S_ERROR;

        case StoreOp:
            break;

        default:
            sprintf(acWhyBuf, "iExecMonadic2R:internal error: Unknown monadic opcode %02x", op);
            pcWhy = acWhyBuf;
            return S_ERROR;
    }
    rv = iExecStore(op1, res);
    --iObjStackTop;
    return rv;
}

/*****************************************************************************
A* FUNCTION:        int iExecMonadic2(WORD op)
 *
 * PARAMETERS:      WORD op  The opcode to be executed
 *
 * RETURN:          S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Execute Type 2 monadic operator with numeric operand:
 *                      DerefOfOp, RefOfOp, SizeOfOp, TypeOp, IncrementOp,
 *                      DecrementOp, LNotOp,
 *
 *  ALLOCATION:
A*  Reference       Size                        Pool    Owner           Description
A*  apObjStack      s(OBJECT_DESCRIPTOR)    bu      amlexec     Number
 *
 ****************************************************************************/
int
iExecMonadic2(WORD op)
{
    OBJECT_DESCRIPTOR *op1, *res;
    int iRv;

#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "iExecMonadic2");
#endif

    if (LNotOp == op)
        iRv = iPrepStack("n");
    else
        iRv = iPrepStack("l");

    if (iRv != S_SUCCESS)
    {
        vAmlAppendOperandDiag(__FILE__, __LINE__, op, 1);
        return iRv;
    }

    vDumpStack(Exec, apcShortOps[op], 1, "after iPrepStack");

    op1 = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop];

    switch (op)
    {
        case LNotOp:
            op1->sNumber.dNumber = (!op1->sNumber.dNumber) - (DWORD)1;
            break;

        case DecrementOp:
        case IncrementOp:

            if ((iRv = iPushIfExec(Exec)) != S_SUCCESS)
                vKFatalError("0019", ("iExecMonadic2/IncDec: stack overflow"));

            /* duplicate the Lvalue on TOS */
            res = NEW(OBJECT_DESCRIPTOR);
            if (res)
            {
                memcpy((void *)res, (void *)op1, sizeof(*op1));
                /* push went into unused space, so no need to vDeleteObject() */
                apObjStack[iObjStackTop] = (void *)res;
            }
            else
            {
                vKFatalError("0020", ("iExecMonadic2/IncDec: Descriptor Allocation Failure"));
                return S_ERROR;
            }

            /* Convert the top copy to a Number */
            iRv = iPrepStack("n");
            if (iRv != S_SUCCESS)
            {
                vAmlAppendOperandDiag(__FILE__, __LINE__, op, 1);
                return iRv;
            }

            /* get the Number in op1 and the Lvalue in res */
            op1 = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop];
            res = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop - 1];

            /* do the ++ or -- */
            if (IncrementOp == op)
                ++op1->sNumber.dNumber;
            else
                --op1->sNumber.dNumber;

            /* store result */
            vDeleteObject((OBJECT_DESCRIPTOR **)&apObjStack[iObjStackTop - 1]);
            apObjStack[iObjStackTop - 1] = (void *)op1;
            iRv = iExecStore(op1, res);
            --iObjStackTop;
            return iRv;

        case TypeOp:
            /* This case uses iRv to hold the type encoding */
            if (Lvalue == op1->bValTyp)
            {
                /* Not a Name -- an indirect name pointer would have
                 * been converted to a direct name pointer in iPrepStack
                 */
                switch(op1->sLvalue.bOpCode)
                {
                case ZeroOp: case OneOp: case OnesOp:
                    /* Constants are of type Number */
                    iRv = (int)Number;
                    break;

                case Debug1:
                    /* Per spec, Debug object is of type Region */
                    iRv = (int)Region;
                    break;

                case IndexOp:
                    pcWhy = "iExecMonadic2/TypeOp: determining type of Index result is not implemented";
                    return S_ERROR;

                case Local0: case Local1: case Local2: case Local3:
                case Local4: case Local5: case Local6: case Local7:
                    iRv = (int)iGetMethodValTyp(LCLBASE
                                                         + op1->sLvalue.bOpCode - Local0);
                    break;

                case Arg0: case Arg1: case Arg2: case Arg3:
                case Arg4: case Arg5: case Arg6:
                    iRv = (int)iGetMethodValTyp(ARGBASE
                                                         + op1->sLvalue.bOpCode - Arg0);
                    break;

                default:
                    sprintf(acWhyBuf,
                        "iExecMonadic2/TypeOp:internal error: Unknown Lvalue subtype %02x",
                        op1->sLvalue.bOpCode);
                    return S_ERROR;
                }
            }
            else
            {
                /* Since we passed iPrepStack("l") and it's not an Lvalue,
                 * it must be a direct name pointer.  Allocate a descriptor
                 * to hold the type.
                 */
                iRv = (int)iNsValType((NsHandle)op1);
                op1 = NEW(OBJECT_DESCRIPTOR);
                if ((OBJECT_DESCRIPTOR *)0 == op1)
                {
                    vKFatalError("0021", ("iExecMonadic2/TypeOp: Descriptor Allocation Failure"));
                    return S_ERROR;
                }
                /* Replace (NsHandle) on TOS with descriptor containing result.
                 * No need to vDeleteObject() first since TOS is an NsHandle.
                 */
                apObjStack[iObjStackTop] = (void *)op1;
            }
            op1->bValTyp = (BYTE)Number;
            op1->sNumber.dNumber = (DWORD)(long)iRv;
            break;

        case SizeOfOp:
            switch (op1->bValTyp)
            {
                case Buffer:
                    op1->sNumber.dNumber = op1->sBuffer.wBufLen;
                    op1->bValTyp = (BYTE)Number;
                    break;

                case String:
                    op1->sNumber.dNumber = op1->sString.wStrLen;
                    op1->bValTyp = (BYTE)Number;
                    break;

                case Package:
                    op1->sNumber.dNumber = op1->sPackage.wPkgCount;
                    op1->bValTyp = (BYTE)Number;
                    break;

                default:
                    sprintf(acWhyBuf,
                            "iExecMonadic2: Needed aggregate, found %d", op1->bValTyp);
                    pcWhy = acWhyBuf;
                    return S_ERROR;
            }
            break;

        case RefOfOp:
        case DerefOfOp:
            sprintf(acWhyBuf, "iExecMonadic2: %s unimplemented",
                    (op > UCHAR_MAX) ? apcLongOps[op & 0x00ff] : apcShortOps[op]);
            pcWhy = acWhyBuf;
            ++iObjStackTop;
            return S_ERROR;

        default:
            sprintf(acWhyBuf,
                        "iExecMonadic2:internal error: Unknown monadic opcode %02x",
                        op);
            pcWhy = acWhyBuf;
            return S_ERROR;
    }
    return S_SUCCESS;
}

/*****************************************************************************
A* FUNCTION:        int iExecDyadic1(WORD op)
 *
 * PARAMETERS:      WORD op  The opcode to be executed
 *
 * RETURN:          S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Execute Type 1 dyadic operator with numeric operands:
 *                      NotifyOp
 *
A*  ALLOCATION:     Deletes both operands
 *
 ****************************************************************************/
int
iExecDyadic1(WORD op)
{
    OBJECT_DESCRIPTOR *obj, *val;
    int iRv;

#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "iExecDyadic1");
#endif

    iRv = iPrepStack("nl");

    if (iRv != S_SUCCESS)
    {
        vAmlAppendOperandDiag(__FILE__, __LINE__, op, 2);
        return iRv;
    }

    vDumpStack(Exec, apcShortOps[op], 2, "after iPrepStack");

    val = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop];
    obj = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop - 1];

    switch (op)
    {
        case NotifyOp:
            /* XXX - What should actually happen here [NotifyOp] ?
             * XXX - See ACPI 1.0 spec sec 5.6.3 p. 5-102.
             * XXX - We may need to simulate what an OS would
             * XXX - do in response to the Notify operation.
             * XXX - For value 1 (Ejection Request),
             * XXX -        some device method may need to be run.
             * XXX - For value 2 (Device Wake) if _PRW exists,
             * XXX -        the _PS0 method may need to be run.
             * XXX - For value 0x80 (Status Change) on the power button or
             * XXX -        sleep button, initiate soft-off or sleep operation?
             */
            switch (obj->bValTyp)
            {
                case Device:
                case Thermal:
                    /* XXX - Requires that sDevice and sThermalZone
                     * XXX - be compatible mappings
                     */
                    iDoNotifyOp (val, obj);
                    break;

                default:
                    sprintf(acWhyBuf,
                            "iExecDyadic1/NotifyOp: unexpected object type %d",
                            obj->bValTyp);
                    pcWhy = acWhyBuf;
                    return S_ERROR;
            }
            break;

        default:
            sprintf(acWhyBuf, "iExecDyadic1: Unknown dyadic opcode %02x", op);
            pcWhy = acWhyBuf;
            return S_ERROR;
    }
    DELETE(val);
    DELETE(obj);
    apObjStack[--iObjStackTop] = (void *)0;
    return S_SUCCESS;
}

/*****************************************************************************
A* FUNCTION:        int iExecDyadic2R(WORD op)
 *
 * PARAMETERS:      WORD op  The opcode to be executed
 *
 * RETURN:          S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Execute Type 2 dyadic operator with numeric operands and
 *                      one or two result operands
 *
A*  ALLOCATION:     Deletes one operand descriptor -- other remains on stack
 *
A*  Reference       Size                        Pool    Owner           Description
A*  sString.pbString varies             bu    amlexec     result of Concat
A*  sBuffer.pbBuffer varies             bu    amlexec     result of Concat
 *
 ****************************************************************************/
int
iExecDyadic2R(WORD op)
{
    OBJECT_DESCRIPTOR *op1, *op2, *res, *res2;
    DWORD remain;
    int iRv, iNOperands;

#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "iExecDyadic2R");
#endif

    switch (op)
    {
        case ConcatOp:
            iRv = iPrepStack("lss");
            iNOperands = 3;
            break;

        case DivideOp:
            iRv = iPrepStack("llnn");
            iNOperands = 4;
            break;

        default:
            iRv = iPrepStack("lnn");
            iNOperands = 3;
            break;

    }

    if (iRv != S_SUCCESS)
    {
        vAmlAppendOperandDiag(__FILE__, __LINE__, op, iNOperands);
        return iRv;
    }

    vDumpStack(Exec, apcShortOps[op], iNOperands, "after iPrepStack");

    if (DivideOp == op)
        res2 = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop--];
    res = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop--];
    op2 = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop--];
    op1 = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop];
    iObjStackTop += iNOperands - 1;

    switch (op)
    {
        case AddOp:
            op1->sNumber.dNumber += op2->sNumber.dNumber;
            break;
        case BitAndOp:
            op1->sNumber.dNumber &= op2->sNumber.dNumber;
            break;
        case BitNandOp:
            op1->sNumber.dNumber = ~(op1->sNumber.dNumber & op2->sNumber.dNumber);
            break;
        case BitOrOp:
            op1->sNumber.dNumber |= op2->sNumber.dNumber;
            break;
        case BitNorOp:
            op1->sNumber.dNumber = ~(op1->sNumber.dNumber | op2->sNumber.dNumber);
            break;
        case BitXorOp:
            op1->sNumber.dNumber ^= op2->sNumber.dNumber;
            break;
        case DivideOp:
            if ((DWORD)0 == op2->sNumber.dNumber)
            {
                pcWhy = "iExecDyadic2R/DivideOp: divide by zero";
                return S_ERROR;
            }
            remain = op1->sNumber.dNumber % op2->sNumber.dNumber;
            op1->sNumber.dNumber /= op2->sNumber.dNumber;
            op2->sNumber.dNumber = remain;
            break;
        case MultiplyOp:
            op1->sNumber.dNumber *= op2->sNumber.dNumber;
            break;
        case ShiftLeftOp:
            op1->sNumber.dNumber <<= op2->sNumber.dNumber;
            break;
        case ShiftRightOp:
            op1->sNumber.dNumber >>= op2->sNumber.dNumber;
            break;
        case SubtractOp:
            op1->sNumber.dNumber -= op2->sNumber.dNumber;
            break;

        case ConcatOp:
            if (op2->bValTyp != op1->bValTyp)
            {
                sprintf(acWhyBuf,
                        "iExecDyadic2R/ConcatOp: operand type mismatch %d %d",
                        op1->bValTyp, op2->bValTyp);
                pcWhy = acWhyBuf;
                return S_ERROR;
            }

            /* Both bValTyp are now known to be the same */
            if (String == op1->bValTyp)
            {
                char *pcNew = OsdAllocate ((size_t)(op1->sString.wStrLen
                                                            + op2->sString.wStrLen + 1));
                if ((char *)0 == pcNew)
                {
                    vKFatalError("0022", (
                        "iExecDyadic2R/ConcatOp: String allocation failure %d",
                        op1->sString.wStrLen + op2->sString.wStrLen + 1));
                    pcWhy = acWhyBuf;
                    return S_ERROR;
                }
                strcpy(pcNew, (char *)op1->sString.pbString);
                strcpy(pcNew + op1->sString.wStrLen,
                         (char *)op2->sString.pbString);
                /* Don't free old op1->sString.pbString; the operand still exists */
                op1->sString.pbString = (BYTE *)pcNew;
                op1->sString.wStrLen += op2->sString.wStrLen;
            }
            else
            {
                char *pcNew = OsdAllocate ((size_t)(op1->sBuffer.wBufLen
                                                            + op2->sBuffer.wBufLen));
                if ((char *)0 == pcNew)
                {
                    /* Only bail out if the buffer is small */
                    if (op1->sBuffer.wBufLen + op2->sBuffer.wBufLen < 1024)
                        vKFatalError("0023", (
                            "iExecDyadic2R/ConcatOp: Buffer allocation failure %d",
                            op1->sBuffer.wBufLen + op2->sBuffer.wBufLen));
                    sprintf(acWhyBuf,
                            "iExecDyadic2R/ConcatOp: Buffer allocation failure %d",
                            op1->sBuffer.wBufLen + op2->sBuffer.wBufLen);
                    pcWhy = acWhyBuf;
                    return S_ERROR;
                }
                memcpy(pcNew, op1->sBuffer.pbBuffer, (size_t)op1->sBuffer.wBufLen);
                memcpy(pcNew + op1->sBuffer.wBufLen, op2->sBuffer.pbBuffer,
                        (size_t)op2->sBuffer.wBufLen);
                /* Don't free old op1->sBuffer.pbBuffer; the operand still exists */
                op1->sBuffer.pbBuffer = (BYTE *)pcNew;
                op1->sBuffer.wBufLen += op2->sBuffer.wBufLen;
            }
            break;

        default:
            sprintf(acWhyBuf, "iExecDyadic2R: Unknown dyadic opcode %02x", op);
            pcWhy = acWhyBuf;
            return S_ERROR;
    }
    if ((iRv = iExecStore(op1, res)) != S_SUCCESS)
    {
        iObjStackTop -= iNOperands - 1;
        return iRv;
    }
    if (DivideOp == op)
        iRv = iExecStore(op2, res2);
    /* Don't delete op1 because it remains on the stack */
    DELETE(op2);
    iObjStackTop -= iNOperands - 1;
    return iRv;
}

/*****************************************************************************
A* FUNCTION:        int iExecDyadic2S(WORD op)
 *
 * PARAMETERS:      WORD op  The opcode to be executed
 *
 * RETURN:          S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Execute Type 2 dyadic synchronization operator
 *
A*  ALLOCATION:     Deletes one operand descriptor -- other remains on stack
 *
 ****************************************************************************/
int
iExecDyadic2S(WORD op)
{
    OBJECT_DESCRIPTOR *obj, *timeo, *res;
    int iRv;

#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "iExecDyadic2S");
#endif

    iRv = iPrepStack("nl");

    if (iRv != S_SUCCESS)
    {
        vAmlAppendOperandDiag(__FILE__, __LINE__, op, 2);
        return iRv;
    }

    vDumpStack(Exec, apcLongOps[op & 0x00ff], 2, "after iPrepStack");

    timeo = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop];
    obj = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop - 1];

    switch (op)
    {
        case AcquireOp:
            if (Mutex != obj->bValTyp)
            {
                sprintf(acWhyBuf,
                        "iExecDyadic2S/AcquireOp: Needed Mutex, found %d",
                        res->bValTyp);
                pcWhy = acWhyBuf;
                return S_ERROR;
            }
            return (iAcquireOpRqst(timeo, obj));


        case WaitOp:
            if (Event != obj->bValTyp)
            {
                sprintf(acWhyBuf,
                        "iExecDyadic2S/WaitOp: Needed Event, found %d",
                        res->bValTyp);
                pcWhy = acWhyBuf;
                return S_ERROR;
            }
            return (iWaitOpRqst(timeo, obj));


        default:
            sprintf(acWhyBuf,
                    "iExecDyadic2S: Unknown dyadic synchronization opcode %02x",
                    op);
            pcWhy = acWhyBuf;
            return S_ERROR;
    }

    /* This will become reachable when Acquire or Wait is implemented */
    DELETE(timeo);
    --iObjStackTop;
    return iRv;
}

/*****************************************************************************
A* FUNCTION:        int iExecDyadic2(WORD op)
 *
 * PARAMETERS:      WORD op  The opcode to be executed
 *
 * RETURN:          S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Execute Type 2 dyadic operator with numeric operands and
 *                      no result operands
 *
A*  ALLOCATION:     Deletes one operand descriptor -- other remains on stack
A*                      containing result value
 *
 ****************************************************************************/
int
iExecDyadic2(WORD op)
{
    OBJECT_DESCRIPTOR *op1, *op2;
    int rv;

#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "iExecDyadic2");
#endif

    rv = iPrepStack("nn");

    if (rv != S_SUCCESS)
    {
        vAmlAppendOperandDiag(__FILE__, __LINE__, op, 2);
        return rv;
    }

    vDumpStack(Exec, apcShortOps[op], 2, "after iPrepStack");

    op2 = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop];
    op1 = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop - 1];

    switch (op)
    {
        case LAndOp:
            if (op1->sNumber.dNumber && op2->sNumber.dNumber)
                rv = 1;
            else
                rv = 0;
            break;
        case LEqualOp:
            if (op1->sNumber.dNumber == op2->sNumber.dNumber)
                rv = 1;
            else
                rv = 0;
            break;
        case LGreaterOp:
            if (op1->sNumber.dNumber > op2->sNumber.dNumber)
                rv = 1;
            else
                rv = 0;
            break;
        case LLessOp:
            if (op1->sNumber.dNumber < op2->sNumber.dNumber)
                rv = 1;
            else
                rv = 0;
            break;
        case LOrOp:
            if (op1->sNumber.dNumber || op2->sNumber.dNumber)
                rv = 1;
            else
                rv = 0;
            break;
        default:
            sprintf(acWhyBuf, "iExecDyadic2: Unknown dyadic opcode %02x", op);
            pcWhy = acWhyBuf;
            return S_ERROR;
    }

    /* op1->bValTyp == Number was assured by iPrepStack("nn") call */
    if (rv)
        op1->sNumber.dNumber = 0xffffffff;
    else
        op1->sNumber.dNumber = 0;

    DELETE(op2);
    --iObjStackTop;
    return S_SUCCESS;
}

/*****************************************************************************
A* FUNCTION:        int iExecCreateField(WORD op)
 *
 * PARAMETERS:      WORD op  The opcode to be executed
 *
 * RETURN:          S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Execute CreateField operators: CreateBitFieldOp,
 *                      CreateByteFieldOp, CreateWordFieldOp, CreateDWordFieldOp,
 *                      CreateFieldOp (which define fields in buffers)
 *
A*  ALLOCATION:     Deletes CreateFieldOp's count operand descriptor
 *
 ****************************************************************************/
int
iExecCreateField(WORD op)
{
    OBJECT_DESCRIPTOR *res, *count, *off, *src;
    char *pcOpName;
    DWORD dBitOffset;
    int iRv, iNOperands;
    WORD wBitCount;

#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "iExecCreateField");
#endif

    if (CreateFieldOp == op)
    {
        iRv = iPrepStack("lnnb");
        iNOperands = 4;
        pcOpName = apcLongOps[op & 0x00ff];
    }
    else
    {
        iRv = iPrepStack("lnb");
        iNOperands = 3;
        pcOpName = apcShortOps[op];
    }

    if (iRv != S_SUCCESS)
    {
        vAmlAppendOperandDiag(__FILE__, __LINE__, op, iNOperands);
        return iRv;
    }

    vDumpStack(Exec, pcOpName, iNOperands, "after iPrepStack");

    res = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop--];      /* result */
    if (CreateFieldOp == op)
        count = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop--];    /* count */
    off = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop--];      /* offset */
    src = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop];            /* source */
    iObjStackTop += iNOperands - 1;

    /* If res is a Name, it will be a direct name pointer after iPrepStack() */
    if (!iIsNsHandle(res))
    {
        sprintf(acWhyBuf, "%s: destination must be a Name", pcOpName);
        pcWhy = acWhyBuf;
        return S_ERROR;
    }

    switch (op)
    {
        case BitFieldOp:
            dBitOffset = off->sNumber.dNumber;              /* offset is in bits */
            wBitCount = 1;                                          /* field is a bit */
            break;

        case ByteFieldOp:
            dBitOffset = 8 * off->sNumber.dNumber;          /* offset is in bytes */
            wBitCount = 8;                                          /* field is a Byte */
            break;

        case WordFieldOp:
            dBitOffset = 8 * off->sNumber.dNumber;          /* offset is in bytes */
            wBitCount = 16;                                     /* field is a Word */
            break;

        case DWordFieldOp:
            dBitOffset = 8 * off->sNumber.dNumber;          /* offset is in bytes */
            wBitCount = 32;                                     /* field is a DWord */
            break;

        case CreateFieldOp:
            dBitOffset = off->sNumber.dNumber;              /* offset is in bits */
            wBitCount = (WORD)count->sNumber.dNumber;       /* as is count */
            break;

        default:
            sprintf(acWhyBuf,
                "iExecCreateField:internal error: Unknown field creation opcode %02x",
                op);
            pcWhy = acWhyBuf;
            return S_ERROR;
    }

    switch (src->bValTyp)
    {
        BYTE bTypeFound;
        char acTypeFound[20], *pcTypeFound;

    case Buffer:
        if (dBitOffset + (DWORD)wBitCount > 8 * (DWORD)src->sBuffer.wBufLen)
        {
            sprintf(acWhyBuf, "iExecCreateField: Field exceeds Buffer %d > %d",
                    dBitOffset + (DWORD)wBitCount,
                    8 * (DWORD)src->sBuffer.wBufLen);
            pcWhy = acWhyBuf;
            return S_ERROR;
        }

        /* Reuse "off" descriptor to build result */
        off->bValTyp = (BYTE)FieldUnit;
        off->sFieldUnit.wAccess = (WORD)AnyAcc;
        off->sFieldUnit.wLockRule = (WORD)NoLock;
        off->sFieldUnit.wUpdateRule = (WORD)Preserve;
        off->sFieldUnit.wDatLen = wBitCount;
        off->sFieldUnit.wBitOffset = (WORD)dBitOffset % 8;
        off->sFieldUnit.dOffset = dBitOffset / 8;
        off->sFieldUnit.pContainer = src;
        off->sFieldUnit.dConSeq = src->sBuffer.dSequence;
        break;

    default:
        bTypeFound = src->bValTyp;
        if (bTypeFound > (BYTE)Lvalue
         || acBadType == apcNsTypeNames[bTypeFound])
        {
            sprintf(acTypeFound, "encoding %d", bTypeFound);
            pcTypeFound = acTypeFound;
        }
        else
            pcTypeFound = apcNsTypeNames[bTypeFound];

        sprintf(acWhyBuf,
            "iExecCreateField: Tried to create field in improper object type %s",
            pcTypeFound);
        pcWhy = acWhyBuf;
        return S_ERROR;
    }

    if (CreateFieldOp == op)
        DELETE(count);

    /* This operation is supposed to cause the destination Name to refer
     * to the defined FieldUnit -- it must not store the constructed
     * FieldUnit object (or its current value) in some location that the
     * Name may already be pointing to.  So, if the Name currently contains
     * a reference which would cause iExecStore() to perform an indirect
     * store rather than setting the value of the Name itself, clobber that
     * reference before calling iExecStore().
     */
    switch (iNsValType(res))                /* Type of Name's existing value */
    {
        case Alias:
        case BankField:
        case DefField:
        case FieldUnit:
        case IndexField:
            if ((Trace & TraceBufFld) && debug_level() > 0)
            {
                printf_bu("\niExecCreateField: clobber %s (%p) ",
                             pcNsFullyQualifiedName(res), res);
                vNsDumpEntry(res, SCREEN|LOGFILE);
                iDumpStackEntry(pvNsValPtr(res));
            }
            vNsSetValue(res, NULL, Any);
            break;

        default:
            break;
    }

    /* Store constructed field descriptor in result location */
    iRv = iExecStore(off, res);
    iObjStackTop -= iNOperands - 1;
    return iRv;
}

/*****************************************************************************
 * FUNCTION:        int iExecFatal()
 *
 * PARAMETERS:      none
 *
 * RETURN:          S_ERROR
 *
 * DESCRIPTION: Execute Fatal operator
 *
 ****************************************************************************/
int
iExecFatal(void)
{
    OBJECT_DESCRIPTOR *poType, *poCode, *poArg;
    int iRv;

#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "iExecFatal");
#endif

    iRv = iPrepStack("nnn");

    if (iRv != S_SUCCESS)
    {
        vAmlAppendOperandDiag(__FILE__, __LINE__, (WORD)FatalOp, 3);
        return iRv;
    }

    vDumpStack(Exec, apcLongOps[FatalOp & 0x00ff], 3, "after iPrepStack");

    poArg = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop];
    poCode = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop - 1];
    poType = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop - 2];

    fprintf_bu(iLstFileHandle, LOGFILE,
            "\nFatalOp: Type %x Code %x Arg %x <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n",
            poType->sNumber.dNumber, poCode->sNumber.dNumber,
            poArg->sNumber.dNumber);

    pcWhy = "iExecFatal: FatalOp executed";
    return S_ERROR;
}

/*****************************************************************************
A* FUNCTION:        int iExecIndex()
 *
 * PARAMETERS:      none
 *
 * RETURN:          S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Execute Index operator
 *
A*  ALLOCATION:     Deletes one operand descriptor -- other remains on stack
 *
 ****************************************************************************/
int
iExecIndex(void)
{
    OBJECT_DESCRIPTOR *poPkg, *poIdx, *poResult;
    int iRv;

#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "iExecIndex");
#endif

    iRv = iPrepStack("lnp");

    if (iRv != S_SUCCESS)
    {
        vAmlAppendOperandDiag(__FILE__, __LINE__, (WORD)IndexOp, 3);
        return iRv;
    }

    vDumpStack(Exec, apcShortOps[IndexOp], 3, "after iPrepStack");

    poResult = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop];
    poIdx = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop - 1];
    poPkg = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop - 2];

    if (poIdx->sNumber.dNumber < 0
     || poIdx->sNumber.dNumber >= (DWORD)poPkg->sPackage.wPkgCount)
    {
        pcWhy = "iExecIndex: Index value out of range";
        return S_ERROR;
    }

    /* XXX - possible dangling reference: if the package vector changes
     * XXX - before this pointer is used, the results may be surprising.
     */
    poPkg->sLvalue.pvRef
        = (void *)&poPkg->sPackage.ppPackage[poIdx->sNumber.dNumber];
    poPkg->bValTyp = (BYTE)Lvalue;
    poPkg->sLvalue.bOpCode = IndexOp;

    if ((iRv = iExecStore(poPkg, poResult)) != S_SUCCESS)
    {
        iObjStackTop -= 2;
        return iRv;
    }
    DELETE(poIdx);
    iObjStackTop -= 2;
    return iRv;
}

/*****************************************************************************
A* FUNCTION:        int iExecMatch()
 *
 * PARAMETERS:      none
 *
 * RETURN:          S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Execute Match operator
 *
A*  ALLOCATION:     Deletes 5 operands
 *
 ****************************************************************************/
int
iExecMatch(void)
{
    OBJECT_DESCRIPTOR *poPkg, *poOp1, *poV1, *poOp2, *poV2, *poStart;
    DWORD dLook;
    DWORD dMatchVal = (DWORD)-1;
    int iRv;

#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "iExecMatch");
#endif

    iRv = iPrepStack("nnnnnp");

    if (iRv != S_SUCCESS)
    {
        vAmlAppendOperandDiag(__FILE__, __LINE__, (WORD)MatchOp, 6);
        return iRv;
    }

    vDumpStack(Exec, apcShortOps[MatchOp], 6, "after iPrepStack");

    poStart = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop];
    poV2 = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop - 1];
    poOp2 = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop - 2];
    poV1 = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop - 3];
    poOp1 = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop - 4];
    poPkg = (OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop - 5];

    /* Validate match comparison sub-opcodes */
    if (poOp1->sNumber.dNumber < 0 || poOp1->sNumber.dNumber > 5
     || poOp2->sNumber.dNumber < 0 || poOp2->sNumber.dNumber > 5)
    {
        pcWhy = "iExecMatch: operation encoding out of range";
        return S_ERROR;
    }

    dLook = poStart->sNumber.dNumber;
    if (dLook < 0 || dLook >= (DWORD)poPkg->sPackage.wPkgCount)
    {
        pcWhy = "iExecMatch: start position value out of range";
        return S_ERROR;
    }

    /* Examine each element until a match is found.  Within the loop,
     * "continue" signifies that the current element does not match
     * and the next should be examined.
     * Upon finding a match, the loop will terminate via "break" at
     * the bottom.  If it terminates "normally", dMatchVal will be -1
     * (its initial value) indicating that no match was found.  When
     * returned as a Number, this will produce the Ones value as specified.
     */
    for ( ; dLook < (DWORD)poPkg->sPackage.wPkgCount ; ++dLook)
    {
        /* Treat any NULL or non-numeric elements as non-matching.
         * XXX - if an element is a Name, should we examine its value?
         */
        if ((OBJECT_DESCRIPTOR *)0 == poPkg->sPackage.ppPackage[dLook]
         || Number != poPkg->sPackage.ppPackage[dLook]->bValTyp)
            continue;

        /* Within these switch statements:
         *      "break" (exit from the switch) signifies a match;
         *      "continue" (proceed to next iteration of enclosing
         *          "for" loop) signifies a non-match.
         */
        switch(poOp1->sNumber.dNumber)
        {
            case MTR:
                break;

            case MEQ:
                if (poPkg->sPackage.ppPackage[dLook]->sNumber.dNumber
                     != poV1->sNumber.dNumber)
                    continue;
                break;

            case MLE:
                if (poPkg->sPackage.ppPackage[dLook]->sNumber.dNumber
                     > poV1->sNumber.dNumber)
                    continue;
                break;

            case MLT:
                if (poPkg->sPackage.ppPackage[dLook]->sNumber.dNumber
                     >= poV1->sNumber.dNumber)
                    continue;
                break;

            case MGE:
                if (poPkg->sPackage.ppPackage[dLook]->sNumber.dNumber
                     < poV1->sNumber.dNumber)
                    continue;
                break;

            case MGT:
                if (poPkg->sPackage.ppPackage[dLook]->sNumber.dNumber
                     <= poV1->sNumber.dNumber)
                    continue;
                break;

            default:
                continue;
        }
        switch(poOp2->sNumber.dNumber)
        {
            case MTR:
                break;

            case MEQ:
                if (poPkg->sPackage.ppPackage[dLook]->sNumber.dNumber
                     != poV2->sNumber.dNumber)
                    continue;
                break;

            case MLE:
                if (poPkg->sPackage.ppPackage[dLook]->sNumber.dNumber
                     > poV2->sNumber.dNumber)
                    continue;
                break;

            case MLT:
                if (poPkg->sPackage.ppPackage[dLook]->sNumber.dNumber
                     >= poV2->sNumber.dNumber)
                    continue;
                break;

            case MGE:
                if (poPkg->sPackage.ppPackage[dLook]->sNumber.dNumber
                     < poV2->sNumber.dNumber)
                    continue;
                break;

            case MGT:
                if (poPkg->sPackage.ppPackage[dLook]->sNumber.dNumber
                     <= poV2->sNumber.dNumber)
                    continue;
                break;

            default:
                continue;
        }

        /* Match found: exit from loop */
        dMatchVal = dLook;
        break;
    }

    poPkg->bValTyp = (BYTE)Number;
    poPkg->sNumber.dNumber = dMatchVal;

    DELETE(poStart);
    DELETE(poV2);
    DELETE(poOp2);
    DELETE(poV1);
    DELETE(poOp1);
    iObjStackTop -= 5;          /* Remove operands */
    return S_SUCCESS;
}

/******************************************************************************
 * FUNCTION:        int iAmlExec(int iOffset, long lLen, ...)
 *
 * PARAMETERS:      int  iOffset    Offset to method in code block
 *                      long lLen       Length of method
 *                      OBJECT_DESCRIPTOR **ppsParams   list of parameters to pass to
 *                                                              method, terminated by NULL.
 *                                                              ppsParams itself may be NULL if
 *                                                              no parameters are being passed.
 *
 * RETURN:          S_SUCCESS, S_RETURN, or S_ERROR
 *
 * DESCRIPTION: Execute the method
 *
 *****************************************************************************/
int
iAmlExec(int iOffset, long lLen, OBJECT_DESCRIPTOR **ppsParams)
{
    int iRv;
    int i1, i2;

#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "iAmlExec");
#endif

    if (iAmlPrepExec(iOffset, lLen) != S_SUCCESS)               /* package stack */
    {
        pcWhy = "iAmlExec: Exec Stack Overflow";
        return S_ERROR;
    }

    /* Push new frame on Method stack */
    if (++iMethodStackTop >= AML_METHOD_MAX_NEST)
    {
        --iMethodStackTop;
        pcWhy = "iAmlExec: Method Stack Overflow";
        return S_ERROR;
    }

    /* Undefine all local variables */
    for ( i1 = 0 ; i1 < NUMLCL ; ++i1 )
    {
        iRv = iSetMethodValue(i1 + LCLBASE, NULL, NULL);
        if (S_SUCCESS != iRv)
        {
            --iMethodStackTop;
            return iRv;
        }
    }

    /* Copy passed parameters into method stack frame */
    for ( i2 = i1 = 0 ; i1 < NUMARG ; ++i1 )
    {
        if (ppsParams && ppsParams[i2])
            iRv = iSetMethodValue(i1 + ARGBASE, ppsParams[i2++], NULL);
        else
            iRv = iSetMethodValue(i1 + ARGBASE, NULL, NULL);
        if (S_SUCCESS != iRv)
        {
            --iMethodStackTop;
            return iRv;
        }
    }

    LineSet(0, Exec);

    /* Normal exit is with iRv == S_RETURN when a ReturnOp has been executed,
     * or with iRv == S_FAILURE at end of AML block (end of Method code)
     */
    while ((iRv = DoCode(Exec)) == S_SUCCESS)
        ;

    if (S_FAILURE == iRv)
        iRv = PopExec();            /* package stack -- inverse of iAmlPrepExec() */
    else
    {
        if (S_RETURN == iRv && debug_level() > 0)
        {
            fprintf_bu(iLstFileHandle, LOGFILE, "\nMethod returned: ");
            iDumpStackEntry((OBJECT_DESCRIPTOR *)apObjStack[iObjStackTop]);
            fprintf_bu(iLstFileHandle, LOGFILE,
                    " at stack level %d\n", iObjStackTop);
        }
        (void)PopExec();            /* package stack -- inverse of iAmlPrepExec() */
    }

    --iMethodStackTop;          /* pop our frame off method stack */

    return iRv;
}

#ifdef PLUMBER

/*****************************************************************************
 * FUNCTION:        void    vMarkMethodValues(int *piCount)
 *
 * PARAMETERS:      int *piCount        Count of blocks marked
 *
 * DESCRIPTION: Mark blocks occupied by currently-active args and locals
 *
 ****************************************************************************/
void
vMarkMethodValues(int *piCount)
{
    int iMethodNestLevel, iIndex;

#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "vMarkMethodValues");
#endif

    /* For each active Method */
    for ( iMethodNestLevel = iMethodStackTop ;
            iMethodNestLevel >= 0 ;
            --iMethodNestLevel )
    {
        /* For each possible Arg and Local */
        for ( iIndex = 0 ; iIndex < (ARGBASE+NUMARG) ; ++iIndex )
        {
            /* Mark value's storage */
            if ((OBJECT_DESCRIPTOR *)0 != apMethodStack[iMethodNestLevel][iIndex])
            {
                ++*piCount;
                vAmlMarkObject(apMethodStack[iMethodStackTop][iIndex]);
            }
        }
    }
}

#endif /* PLUMBER */

/*****************************************************************************
 * FUNCTION:        int iIsMethodValue(OBJECT_DESCRIPTOR *pOD)
 *
 * PARAMETERS:      OBJECT_DESCRIPTOR *pOD
 *
 * RETURN:          TRUE if the passed descriptor is the value of an Arg or
 *                      Local in a currently-active Method, else FALSE
 *
 ****************************************************************************/
int
iIsMethodValue(OBJECT_DESCRIPTOR *pOD)
{
    int iMethodNestLevel, iIndex;

#ifdef FUNCTION_HELLO
   vFunctionHello ("amlexec.c", "iIsMethodValue");
#endif

    /* For each active Method */
    for ( iMethodNestLevel = iMethodStackTop ;
            iMethodNestLevel >= 0 ;
            --iMethodNestLevel )
        /* For each possible Arg and Local */
        for ( iIndex = 0 ; iIndex < (ARGBASE+NUMARG) ; ++iIndex )
            if (pOD == apMethodStack[iMethodNestLevel][iIndex])
                return TRUE;

    return FALSE;
}
