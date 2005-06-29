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
 | $Revision: 1.11 $
 | $Date: 2005/06/29 17:50:54 $
 | $Log: exstore.c,v $
 | Revision 1.11  2005/06/29 17:50:54  aystarik
 | Moved table-size constants to acpi.h
 |
 | 
 | date	99.03.12.00.20.00;	author rmoore1;	state Exp;
 |
 * 
 * 11    3/11/99 4:20p Rmoore1
 * Moved table-size constants to acpi.h
 * 
 * 10    3/10/99 1:19p Rmoore1
 * New xface to KFatalError
 * 
 * 9     3/09/99 4:08p Rmoore1
 * New names for I/O and PCI OSD interfaces
 * 
 * 8     2/19/99 4:33p Rmoore1
 * Changed to generic 64-bit friendly data types
 * 
 * 7     2/16/99 1:22p Rmoore1
 * Removed hungarian notation
 * 
 * 6     2/11/99 3:27p Grsmith1
 * 
 * 5     1/20/99 9:40a Rmoore1
 * Major cleanup
 * 
 * 4     1/14/99 3:53p Rmoore1
 * Cleanup
 * 
 * 3     1/13/99 10:50a Grsmith1
 * First BeOS compatible check-in.
 * 
 * 2     1/11/99 4:17p Grsmith1
 * Detabified.
 * 
 * 1     1/11/99 2:11p Rmoore1
 * AML Interpreter
// 
//    Rev 1.32   11 Sep 1998 18:03:16   phutchis
// Change inc_error() etc. to Kinc_error() etc. (error key logging).
// 
//    Rev 1.31   09 Jun 1998 14:26:32   calingle
// fixed the way the opcode was being evaluated in SetupField.  Now GetRvalue is called to get the pr
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
// Leave operand descriptors on ObjStack[] during operator execution
//   to fix GC problems.
// Fix GC problem in ExecStore() when the destination is a direct name pointer.
// Add support for Buffer sequence numbering.
// Correct PrepStack call for ConcatOp in ExecDyadic2R()
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
// In GetRvalue():
//   Fixed glitch in debug identification of Local being fetched;
//   Included the value of the Local in the debug report if its type is Number;
//   Added similar debug reporting for Args as for Locals.
// Fixed major bug in ExecCreateField():
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
// Added GetMethodDepth() and made several minor changes
//   to support calling a Method from within another Method.
// Added debug surrounding call of GetMethodValue() in GetRvalue().
// Improved diagnosis of unexpected Lvalues in PrepStack().
// Added MarkMethodValues() and IsMethodValue() to support improved
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
// Fix PrepStack() stack underflow bug.
// Add AmlAppendOperandDiag(), and call it when PrepStack() returns
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
//   Changed most allocation failures to call KFatalError(())
//   Fixed some storage leaks.
//   Replaced hard-coded constants with #defines where appropriate.
//   Combine the nearly identical logic of GetNamedFieldValue() and
//     SetNamedFieldValue() into a single function AccessNamedFieldValue().
//   Renamed parameters of ExecStore() and rearranged logic for clarity.
//
//    Rev 1.16   21 Nov 1997 16:49:06   phutchis
// Fixed GetRvalue() to work properly when the input is an OBJECT_DESCRIPTOR
// of type FieldUnit.  (It was already handling the case where the input was
// an NsHandle and the name's value was of type FieldUnit.)
//
//    Rev 1.15   17 Nov 1997 15:16:42   phutchis
// In ExecStore() when the result is a field and the value to be stored is not
//   a Number, call GetRvalue() to try to convert the value to a Number.  Fixes
//   problem of incorrectly logging an error when both source and destination
//   are fields.
// Rework identified in amlscan code inspection:
//   Replaced MAXLEVEL with new AML_METHOD_MAX_NEST in sizing MethodStack[].
//   Revised PrepBankFieldValue() to possibly work.
//
//    Rev 1.14   06 Nov 1997 11:56:26   calingle
// added return S_SUCCESS at end of case Device in GetRvalue.
//
//    Rev 1.13   05 Nov 1997 08:50:10   calingle
// removed #include <bu_plumr.h>
//
//    Rev 1.12   04 Nov 1997 16:55:10   phutchis
// Handle Device case in GetRvalue().
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
// Add comments to SetMethodValue() to clarify flow.
// Fix storage leaks in ExecMonadic1() and ExecMonadic2().
//
//    Rev 1.9   29 Jul 1997 14:36:40   phutchis
// Handle passing of parameters to methods:
//   Add Params parameter to AmlExec()
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
#define _THIS_MODULE    "amlexec.c"

#include <bu.h>
#include <acpi.h>
#include <acpiosd.h>
#include <acpitype.h>
#include <acpipriv.h>
#include <acpirio.h>
#include <aml.h>
#include <acpinmsp.h>
#include <amldsio.h>
#include <amlscan.h>
#include <amlexec.h>
#include <amlpriv.h>
#include <amlopsys.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

extern char *NsTypeNames[];
extern char *RV[];

/* Change this to #if 1 to enable logfile notes of some XXX stuff */

#if 0
    #define PRINT_XXX   fprintf_bu
#else
    #define PRINT_XXX(a,b,c)
#endif

/* 
 * Method Stack, containing locals and args
 * per level, 0-7 are Local# and 8-14 are Arg#
 */

#define LCLBASE             0
#define NUMLCL              8
#define ARGBASE             (LCLBASE+NUMLCL)
#define NUMARG              7

static OBJECT_DESCRIPTOR *  MethodStack[AML_METHOD_MAX_NEST][ARGBASE+NUMARG];
static INT32                MethodStackTop = -1;


/*****************************************************************************
 * 
 * FUNCTION:    GetMethodDepth
 *
 * RETURN:      The current value of MethodStackTop
 *
 ****************************************************************************/

INT32
GetMethodDepth (void)
{

    return MethodStackTop;
}


/*****************************************************************************
 * 
 * FUNCTION:    GetMethodValTyp
 *
 * PARAMETERS:  INT32 Index      index in MethodStack[MethodStackTop]
 *
 * RETURN:      Data type of selected Arg or Local
 *              Used only in ExecMonadic2()/TypeOp.
 *
 ****************************************************************************/

static NsType
GetMethodValTyp (INT32 Index)
{
    FUNCTION_TRACE ("GetMethodValTyp");


    if (OUTRANGE (MethodStackTop, MethodStack)
        || OUTRANGE (Index, MethodStack[MethodStackTop]))
    {
        fprintf_bu (LstFileHandle, LOGFILE,
                      "GetMethodValTyp: internal error: index %d, %d out of range",
                      MethodStackTop, Index);
        _Kinc_error ("0001", PACRLF, __LINE__, __FILE__, LstFileHandle, LOGFILE);

        return (NsType)-1;
    }

    if ((OBJECT_DESCRIPTOR *) 0 == MethodStack[MethodStackTop][Index])
    {
        return Any; /* Any == 0 => "uninitialized" -- see spec 15.2.3.5.2.28 */
    }

    return MethodStack[MethodStackTop][Index]->ValType;
}


/*****************************************************************************
 * 
 * FUNCTION:    GetMethodValue
 *
 * PARAMETERS:  INT32               Index       index in MethodStack[MethodStackTop]
 *              OBJECT_DESCRIPTOR   *ObjDesc    Descriptor into which selected Arg
 *                                              or Local value should be copied
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Retrieve value of selected Arg or Local
 *              Used only in GetRvalue().
 *
 ****************************************************************************/

static INT32
GetMethodValue (INT32 Index, OBJECT_DESCRIPTOR *ObjDesc)
{
    FUNCTION_TRACE ("GetMethodValue");


    if (OUTRANGE (MethodStackTop, MethodStack)
        || OUTRANGE (Index, MethodStack[MethodStackTop]))
    {
        sprintf (WhyBuf, "GetMethodValue: Bad method stack index [%d][%d]",
                MethodStackTop, Index);
    }

    else if ((OBJECT_DESCRIPTOR *) 0 == MethodStack[MethodStackTop][Index])
    {
        if (ARGBASE <= Index && Index < (ARGBASE+NUMARG))
        {
            sprintf (WhyBuf, "GetMethodValue: Uninitialized Arg%d",
                    Index - ARGBASE);
        }
        else if (LCLBASE <= Index && Index < (LCLBASE + NUMLCL))
        {
            sprintf (WhyBuf, "GetMethodValue: Uninitialized Local%d",
                    Index - LCLBASE);
        }
        else
        {
            sprintf (WhyBuf, "GetMethodValue: Uninitialized method value %d",
                    Index);
        }

#ifdef HACK
        fprintf_bu (LstFileHandle, LOGFILE,
                    " ** GetMethodValue: ret uninit as 4 **");
        ObjDesc->Number.ValType = (UINT8) Number;
        ObjDesc->Number.Number = 0x4;
        return S_SUCCESS;
#endif /* HACK */

    }

    else
    {
        memcpy ((void *) ObjDesc,
                 (void *) MethodStack[MethodStackTop][Index],
                 sizeof (*ObjDesc));

        if (Buffer == ObjDesc->ValType)
        {
            /* Assign a new sequence number */
            
            ObjDesc->Buffer.Sequence = AmlBufSeq ();
        }

        return S_SUCCESS;
    }

    Why = WhyBuf;
    return S_ERROR;
}


/*****************************************************************************
 * 
 * FUNCTION:    SetMethodValue
 *
 * PARAMETERS:  INT32               Index       index in MethodStack[MethodStackTop]
 *              OBJECT_DESCRIPTOR * ObjDesc     Value to be stored
 *                                              May be NULL -- see Description.
 *              OBJECT_DESCRIPTOR * ObjDesc2    Spare descriptor into which *ObjDesc
 *                                              can be copied, or NULL if one must
 *                                              be allocated for the purpose.  If
 *                                              provided, this descriptor will be
 *                                              consumed (either used for the new
 *                                              value or deleted).
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Store a value in an Arg or Local.
 *              To undefine an entry, pass ObjDesc as NULL; the old descriptor
 *              will be deleted.
 *
 * ALLOCATION:
 *  Reference     Size                    Pool    Owner       Description
 *  MethodStack   s(OBJECT_DESCRIPTOR)    bu      amlexec     Object
 *
 ****************************************************************************/

static INT32
SetMethodValue (INT32 Index, OBJECT_DESCRIPTOR *ObjDesc, OBJECT_DESCRIPTOR *ObjDesc2)
{
    FUNCTION_TRACE ("SetMethodValue");


    if (OUTRANGE (MethodStackTop, MethodStack)
        || OUTRANGE (Index, MethodStack[MethodStackTop]))
    {
        sprintf (WhyBuf, "SetMethodValue: Bad method stack index [%d][%d]",
                MethodStackTop, Index);
        Why = WhyBuf;
        return S_ERROR;
    }

    if ((OBJECT_DESCRIPTOR *) 0 == MethodStack[MethodStackTop][Index])
    {
        /* Local or Arg is currently undefined */

        if ((OBJECT_DESCRIPTOR *) 0 == ObjDesc2 && (OBJECT_DESCRIPTOR *) 0 != ObjDesc)
        {
            /* 
             * No descriptor was provided in ObjDesc2, and the currently-undefined
             * Local or Arg is to be defined.  Allocate a descriptor.
             */
            MethodStack[MethodStackTop][Index] = NEW(OBJECT_DESCRIPTOR);
            if ((OBJECT_DESCRIPTOR *) 0 == MethodStack[MethodStackTop][Index])
            {
                KFatalError ("0002", ("SetMethodValue: Descriptor Allocation Failure"));
                return S_ERROR;
            }
        }

        else
        {
            /* 
             * A descriptor was provided in ObjDesc2; use it for the Arg/Local
             * new value (or delete it later if the new value is NULL).
             * We also come here if no descriptor was supplied and the
             * undefined Local or Arg is to remain undefined; in that case
             * the assignment is a no-op.
             */
            MethodStack[MethodStackTop][Index] = ObjDesc2;
        }
    }
 
    else
    {
        /* 
         * Arg or Local is currently defined, so that descriptor will be
         * reused for the new value.  Delete the spare descriptor if supplied.
         */
        if ((OBJECT_DESCRIPTOR *) 0 != ObjDesc2)
        {
            /* XXX - see XXX comment below re possible storage leak */

            DELETE (ObjDesc2);
        }
    }

    if ((OBJECT_DESCRIPTOR *) 0 == ObjDesc)
    {
        /* 
         * Undefine the Arg or Local by setting its descriptor pointer to NULL.
         * If it is currently defined, delete the old descriptor first.
         */
        if ((OBJECT_DESCRIPTOR *) 0 != MethodStack[MethodStackTop][Index])
        {
            if (Buffer == MethodStack[MethodStackTop][Index]->ValType)
            {
                /* 
                 * Ensure the about-to-be-deleted Buffer's sequence number
                 * will no longer match any FieldUnits defined within it,
                 * by inverting its most-significant bit.
                 */
                MethodStack[MethodStackTop][Index]->Buffer.Sequence
                                                                ^= 0x80000000UL;
            }

            DELETE (MethodStack[MethodStackTop][Index]);

            /* 
             * XXX - Should also delete any unshared storage pointed to by this
             * XXX - descriptor, but lacking a convenient way to determine
             * XXX - whether the storage is shared or not we'll let GC handle it.
             */
        }
        MethodStack[MethodStackTop][Index] = ObjDesc;
    }

    else
    {
        /* 
         * Copy the ObjStack descriptor (*ObjDesc) into the descriptor for the
         * Arg or Local.
         */
        /* 
         * XXX - possible storage leak: if the old descriptor happens to be
         * XXX - for an aggregate (Buffer, String, Package, etc.), it points
         * XXX - to other storage which may or may not be shared; if unshared
         * XXX - it should be freed here.  (Good Luck figuring out whether it
         * XXX - is shared or not.)
         */
        memcpy ((void *) MethodStack[MethodStackTop][Index],
                 (void *) ObjDesc, sizeof (*ObjDesc));

        if (Buffer == ObjDesc->ValType)
        {
            /* Assign a new sequence number */

            MethodStack[MethodStackTop][Index]->Buffer.Sequence
                    = AmlBufSeq();
        }
    }

    return S_SUCCESS;
}


/*****************************************************************************
 * 
 * FUNCTION:    PrepDefFieldValue
 *
 * PARAMETERS:  NsHandle    Region     Region in which field is being defined
 *              UINT8       FldFlg     Access, LockRule, UpdateRule
 *                                     The format of a FieldFlag is described
 *                                     in the ACPI specification and in <aml.h>
 *              INT32       FldPos     field position
 *              INT32       FldLen     field length
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Construct an OBJECT_DESCRIPTOR of type DefField and connect
 *              it to the nte whose handle is at ObjStack[ObjStackTop]
 *
 * ALLOCATION:
 *  Reference   Size                    Pool    Owner       Description
 *  nte.ValDesc s(OBJECT_DESCRIPTOR)    bu      amlexec     Field descriptor
 *
 ****************************************************************************/

INT32
PrepDefFieldValue (NsHandle Region, UINT8 FldFlg, INT32 FldPos, INT32 FldLen)
{
    OBJECT_DESCRIPTOR *ObjDesc = NEW (OBJECT_DESCRIPTOR);


    FUNCTION_TRACE ("PrepDefFieldValue");


    if ((OBJECT_DESCRIPTOR *) 0 == ObjDesc)
    {
        KFatalError ("0003", ("PrepDefFieldValue: Descriptor Allocation Failure"));
        return S_ERROR;
    }

    if ((NsHandle) 0 == Region)
    {
        Why = "PrepDefFieldValue: null Region";
        DELETE (ObjDesc);
        return S_ERROR;
    }

    if (Region != (NsHandle) NsValType (Region))
    {
        sprintf (WhyBuf, "PrepDefFieldValue: Needed Region, found %d",
                    NsValType (Region));
        Why = WhyBuf;
        DELETE (ObjDesc);
        return S_ERROR;
    }

    if (debug_level () > 0)
    {
        DumpStack (Exec, "PrepDefFieldValue", 2, "case DefField");
    }

    ObjDesc->ValType = (UINT8) DefField;
    if (DefField != ObjDesc->Field.ValType)
    {
        /* 
         * The C implementation has done something which is technically legal
         * but unexpected:  the ValType field which was defined as a UINT8 did
         * not map to the same structure offset as the one which was defined
         * as a WORD_BIT -- see comments in the definition of the FieldUnit
         * variant of OBJECT_DESCRIPTOR in amlpriv.h.
         *
         * Log some evidence to facilitate porting the code.
         */
        ObjDesc->Field.ValType = 0x005a;
        sprintf (WhyBuf,
                "PrepDefFieldValue: internal failure %p %02x %02x %02x %02x",
                ObjDesc, ((UINT8 *) ObjDesc)[0], ((UINT8 *) ObjDesc)[1], ((UINT8 *) ObjDesc)[2],
                ((UINT8 *) ObjDesc)[3]);
        Why = WhyBuf;
        DELETE (ObjDesc);
        return S_ERROR;
    }

    ObjDesc->Field.Access     = (FldFlg & ACCESS_TYPE_MASK) >> ACCESS_TYPE_SHIFT;
    ObjDesc->Field.LockRule   = (FldFlg & LOCK_RULE_MASK) >> LOCK_RULE_SHIFT;
    ObjDesc->Field.UpdateRule = (FldFlg & UPDATE_RULE_MASK) >> UPDATE_RULE_SHIFT;
    ObjDesc->Field.DatLen     = (UINT16) FldLen;

    /* XXX - should use width of data register, not hardcoded 8 */

    PRINT_XXX (LstFileHandle, LOGFILE, " ** PrepDefFieldValue: hard 8 **");

    ObjDesc->Field.BitOffset  = (UINT16) FldPos % 8;
    ObjDesc->Field.Offset     = (UINT32) FldPos / 8;
    ObjDesc->Field.Container  = NsValPtr (Region);

    if (debug_level () > 0)
    {
        fprintf_bu (LstFileHandle, LOGFILE,
                "PrepDefFieldValue: set nte %p (%4.4s) val = %p",
                ObjStack[ObjStackTop], ObjStack[ObjStackTop], ObjDesc);

        DumpStackEntry (ObjDesc);
        NsDumpEntry (Region, LOGFILE);
        fprintf_bu (LstFileHandle, LOGFILE, "\t%p ", ObjDesc->Field.Container);

        if (ObjDesc->Field.Container)
        {
            DumpStackEntry (ObjDesc->Field.Container);
        }

        fprintf_bu (LstFileHandle, LOGFILE,
                    "============================================================");
    }

    /* 
     * Store the constructed descriptor (ObjDesc) into the nte whose
     * handle is on TOS, preserving the current type of that nte.
     */
    NsSetValue ((NsHandle) ObjStack[ObjStackTop], ObjDesc,
                (UINT8) NsValType ((NsHandle) ObjStack[ObjStackTop]));

    return S_SUCCESS;
}


/*****************************************************************************
 * 
 * FUNCTION:    PrepBankFieldValue
 *
 * PARAMETERS:  NsHandle    Region     Region in which field is being defined
 *              NsHandle    BankReg    Bank selection register
 *              UINT32      BankVal    Value to store in selection register
 *              UINT8       FldFlg     Access, LockRule, UpdateRule
 *              INT32       FldPos     field position
 *              INT32       FldLen     field length
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Construct an OBJECT_DESCRIPTOR of type BankField and connect
 *              it to the nte whose handle is at ObjStack[ObjStackTop]
 *
 * ALLOCATION:
 *  Reference   Size                    Pool    Owner       Description
 *  nte.ValDesc s(OBJECT_DESCRIPTOR)    bu      amlexec     Field descriptor
 *
 ****************************************************************************/

INT32
PrepBankFieldValue (NsHandle Region, NsHandle BankReg, UINT32 BankVal,
                        UINT8 FldFlg, INT32 FldPos, INT32 FldLen)
{
    OBJECT_DESCRIPTOR *ObjDesc = NEW (OBJECT_DESCRIPTOR);


    FUNCTION_TRACE ("PrepBankFieldValue");


    if ((OBJECT_DESCRIPTOR *) 0 == ObjDesc)
    {
        KFatalError ("0004", ("PrepBankFieldValue: Descriptor Allocation Failure"));
        return S_ERROR;
    }

    if ((NsHandle) 0 == Region)
    {
        Why = "PrepBankFieldValue: null Region";
        DELETE (ObjDesc);
        return S_ERROR;
    }

    if (Region != (NsHandle) NsValType (Region))
    {
        sprintf (WhyBuf, "PrepBankFieldValue: Needed Region, found %d",
                    NsValType (Region));
        Why = WhyBuf;
        DELETE (ObjDesc);
        return S_ERROR;
    }

    if (debug_level () > 0)
    {
        DumpStack (Exec, "PrepBankFieldValue", 2, "case BankField");
    }

    ObjDesc->ValType = (UINT8) BankField;
    if (BankField != ObjDesc->BankField.ValType)
    {
        /* See comments in PrepDefFieldValue() re unexpected C behavior */

        ObjDesc->BankField.ValType = 0x005a;
        sprintf (WhyBuf,
                "PrepBankFieldValue: internal failure %p %02x %02x %02x %02x",
                ObjDesc, ((UINT8 *) ObjDesc)[0], ((UINT8 *) ObjDesc)[1], ((UINT8 *) ObjDesc)[2],
                ((UINT8 *) ObjDesc)[3]);
        Why = WhyBuf;
        DELETE (ObjDesc);
        return S_ERROR;
    }

    ObjDesc->BankField.Access     = (FldFlg & ACCESS_TYPE_MASK) >> ACCESS_TYPE_SHIFT;
    ObjDesc->BankField.LockRule   = (FldFlg & LOCK_RULE_MASK) >> LOCK_RULE_SHIFT;
    ObjDesc->BankField.UpdateRule = (FldFlg & UPDATE_RULE_MASK) >> UPDATE_RULE_SHIFT;
    ObjDesc->BankField.DatLen     = (UINT16) FldLen;

    /* XXX - should use width of data register, not hardcoded 8 */

    PRINT_XXX (LstFileHandle, LOGFILE, " ** PrepBankFieldValue: hard 8 **");

    ObjDesc->BankField.BitOffset  = (UINT16) FldPos % 8;
    ObjDesc->BankField.Offset     = (UINT32) FldPos / 8;
    ObjDesc->BankField.BankVal    = BankVal;
    ObjDesc->BankField.Container  = NsValPtr (Region);
    ObjDesc->BankField.BankSelect = NsValPtr (BankReg);

    if (debug_level () > 0)
    {
        fprintf_bu (LstFileHandle, LOGFILE,
                    "PrepBankFieldValue: set nte %p (%4.4s) val = %p",
                    ObjStack[ObjStackTop], ObjStack[ObjStackTop], ObjDesc);
        DumpStackEntry (ObjDesc);
        NsDumpEntry (Region, LOGFILE);
        NsDumpEntry (BankReg, LOGFILE);

        fprintf_bu (LstFileHandle, LOGFILE,
            "============================================================");
    }

    /* 
     * Store the constructed descriptor (ObjDesc) into the nte whose
     * handle is on TOS, preserving the current type of that nte.
     */
    NsSetValue ((NsHandle) ObjStack[ObjStackTop], ObjDesc,
                (UINT8) NsValType ((NsHandle) ObjStack[ObjStackTop]));

    return S_SUCCESS;
}


/*****************************************************************************
 * 
 * FUNCTION:    PrepIndexFieldValue
 *
 * PARAMETERS:  NsHandle    IndexReg   Index register
 *              NsHandle    DataReg    Data register
 *              UINT8       FldFlg     Access, LockRule, UpdateRule
 *              INT32       FldPos     field position
 *              INT32       FldLen     field length
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Construct an OBJECT_DESCRIPTOR of type IndexField and connect
 *              it to the nte whose handle is at ObjStack[ObjStackTop]
 *
 * ALLOCATION:
 *  Reference   Size                    Pool    Owner       Description
 *  nte.ValDesc s(OBJECT_DESCRIPTOR)    bu      amlexec     Field descriptor
 *
 ****************************************************************************/

INT32
PrepIndexFieldValue (NsHandle IndexReg, NsHandle DataReg,
                        UINT8 FldFlg, INT32 FldPos, INT32 FldLen)
{
    OBJECT_DESCRIPTOR *ObjDesc = NEW (OBJECT_DESCRIPTOR);


    FUNCTION_TRACE ("PrepIndexFieldValue");


    if ((OBJECT_DESCRIPTOR *) 0 == ObjDesc)
    {
        KFatalError ("0005", ("PrepIndexFieldValue: Descriptor Allocation Failure"));
        return S_ERROR;
    }

    if ((NsHandle) 0 == IndexReg || (NsHandle) 0 == DataReg)
    {
        Why = "PrepIndexFieldValue: null handle";
        DELETE (ObjDesc);
        return S_ERROR;
    }

    ObjDesc->ValType = (UINT8) IndexField;
    if (IndexField != ObjDesc->IndexField.ValType)
    {
        /* See comments in PrepDefFieldValue() re unexpected C behavior */
        
        ObjDesc->IndexField.ValType = 0x005a;
        sprintf (WhyBuf,
                "PrepIndexFieldValue: internal failure %p %02x %02x %02x %02x",
                ObjDesc, ((UINT8 *) ObjDesc)[0], ((UINT8 *) ObjDesc)[1], ((UINT8 *) ObjDesc)[2],
                ((UINT8 *) ObjDesc)[3]);
        Why = WhyBuf;
        DELETE (ObjDesc);
        return S_ERROR;
    }

    ObjDesc->IndexField.Access        = (FldFlg & ACCESS_TYPE_MASK) >> ACCESS_TYPE_SHIFT;
    ObjDesc->IndexField.LockRule      = (FldFlg & LOCK_RULE_MASK) >> LOCK_RULE_SHIFT;
    ObjDesc->IndexField.UpdateRule    = (FldFlg & UPDATE_RULE_MASK) >> UPDATE_RULE_SHIFT;
    ObjDesc->IndexField.DatLen        = (UINT16) FldLen;

    /* XXX - should use width of data register, not hardcoded 8 */

    PRINT_XXX (LstFileHandle, LOGFILE, " ** PrepIndexFieldValue: hard 8 **");

    ObjDesc->IndexField.BitOffset = (UINT16) FldPos % 8;
    ObjDesc->IndexField.IndexVal  = (UINT32) FldPos / 8;
    ObjDesc->IndexField.Index     = IndexReg;
    ObjDesc->IndexField.Data      = DataReg;

    if (debug_level () > 0)
    {
        fprintf_bu (LstFileHandle, LOGFILE,
                    "PrepIndexFieldValue: set nte %p (%4.4s) val = %p",
                    ObjStack[ObjStackTop], ObjStack[ObjStackTop], ObjDesc);

        DumpStackEntry (ObjDesc);
        NsDumpEntry (IndexReg, LOGFILE);
        NsDumpEntry (DataReg, LOGFILE);

        fprintf_bu (LstFileHandle, LOGFILE,
            "============================================================");
    }

    /* 
     * Store the constructed descriptor (ObjDesc) into the nte whose
     * handle is on TOS, preserving the current type of that nte.
     */
    NsSetValue ((NsHandle) ObjStack[ObjStackTop], ObjDesc,
                (UINT8) NsValType ((NsHandle) ObjStack[ObjStackTop]));

    return S_SUCCESS;
}


/*****************************************************************************
 * 
 * FUNCTION:    SetupField
 *
 * PARAMETERS:  OBJECT_DESCRIPTOR * ObjDesc         Field to be read or written
 *              OBJECT_DESCRIPTOR * RgnDesc         Region containing field
 *              INT32               FieldBitWidth   Field Width in bits (8, 16, or 32)
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Common processing for ReadField and WriteField
 *
 ****************************************************************************/

static INT32
SetupField (OBJECT_DESCRIPTOR *ObjDesc, OBJECT_DESCRIPTOR *RgnDesc, INT32 FieldBitWidth)
{
    INT32 Excep;
    INT32 FieldByteWidth = FieldBitWidth / 8;                  /* possible values are 1, 2, 4 */


    FUNCTION_TRACE ("SetupField");


    if ((OBJECT_DESCRIPTOR *) 0 == ObjDesc || (OBJECT_DESCRIPTOR *) 0 == RgnDesc)
    {
        Why = "SetupField:internal error: null handle";
        return S_ERROR;
    }

    if (Region != RgnDesc->ValType)
    {
        sprintf (WhyBuf, "SetupField: Needed Region, found %d", RgnDesc->ValType);
        Why = WhyBuf;
        return S_ERROR;
    }

    if (FieldBitWidth != 8 && FieldBitWidth != 16 && FieldBitWidth != 32)
    {
        sprintf (WhyBuf, "SetupField:internal error: bad width %d", FieldBitWidth);
        Why = WhyBuf;
        return S_ERROR;
    }

    if (debug_level () > 2)
    {
        /* flow trace */
        fprintf_bu (LstFileHandle, LOGFILE, "SetupField: ");
    }

    /* 
     * If the address and length have not been previously evaluated,
     * evaluate them and save the results.
     */
    if (0 == RgnDesc->Region.AdrLenValid)
    {
        /* preserve current stack */

        if ((Excep = PushExecLen (0L)) != S_SUCCESS)
        {
            if (debug_level() > 2)
            {
                /* flow trace */
                fprintf_bu (LstFileHandle, LOGFILE,
                            "PushExecLen returned %s", RV[Excep]);
            }
            return Excep;
        }

        /* Point to Address opcode in AML stream */

        SetCurrentLoc (&RgnDesc->Region.AdrLoc);

        /* Evaluate the Address opcode */

        if ((Excep = DoOpCode (Exec)) == S_SUCCESS
            && (Excep = GetRvalue ((OBJECT_DESCRIPTOR **) &ObjStack[ObjStackTop]))
             == S_SUCCESS)
        {
            /* Capture the address */

            OBJECT_DESCRIPTOR       *ObjValDesc = ObjStack[ObjStackTop];


            if ((OBJECT_DESCRIPTOR *) 0 == ObjValDesc
                || ObjValDesc->ValType != (UINT8) Number)
            {
                Why = "SetupField: Malformed Region/Address";

                if (debug_level () > 2)
                {
                    /* flow trace */
                    fprintf_bu (LstFileHandle, LOGFILE, " Malformed Region/Address "
                                "ObjValDesc = %p, ObjValDesc->ValType = %02Xh, Number = %02Xh",
                                ObjValDesc, ObjValDesc->ValType, (UINT8) Number);

                }
                return S_ERROR;
            }

            RgnDesc->Region.Address = ObjValDesc->Number.Number;

            /* Evaluate the Length opcode */

            if ((Excep = DoOpCode (Exec)) == S_SUCCESS
                && (Excep = GetRvalue ((OBJECT_DESCRIPTOR **) &ObjStack[ObjStackTop]))
                 == S_SUCCESS)
            {
                /* Capture the length */

                ObjValDesc = ObjStack[ObjStackTop];

                if ((OBJECT_DESCRIPTOR *)0 == ObjValDesc
                    || ObjValDesc->ValType != (UINT8) Number)
                {
                    Why = "SetupField: Malformed Region/Length";
                    if (debug_level () > 2)
                    {
                        /* flow trace */
                        fprintf_bu (LstFileHandle, LOGFILE,
                                    " Malformed Region/Length ");
                    }
                    return S_ERROR;
                }

                RgnDesc->Region.Length = ObjValDesc->Number.Number;

                /* 
                 * Remember that both Address and Length
                 * have been successfully evaluated and saved.
                 */
                RgnDesc->Region.AdrLenValid = 1;
            }
        }

        if (S_SUCCESS != Excep)
        {
            if (debug_level () > 1)
            {
                fprintf_bu (LstFileHandle, LOGFILE,
                            " DoOpCode at [%04x:%04lx] returned %s ",
                            RgnDesc->Region.AdrLoc.Offset,
                            RgnDesc->Region.AdrLoc.Length,
                            RV[Excep]);
            }
            return Excep;
        }

        if ((Excep = PopExec ()) != S_SUCCESS)
        {
            if (debug_level() > 1)
            {
                fprintf_bu (LstFileHandle, LOGFILE,
                            " PopExec returned %s ", RV[Excep]);
            }
            return Excep;
        }
    }

    /* 
     * If (offset rounded up to next multiple of field width)
     * exceeds region length, indicate an error.
     */
    if (RgnDesc->Region.Length
        < (ObjDesc->Field.Offset & ~((UINT32) FieldByteWidth - 1)) + FieldByteWidth)
    {
        sprintf (WhyBuf,
                "SetupField: Operation at %08lx width %d bits exceeds region bound %08lx",
                ObjDesc->Field.Offset, FieldBitWidth, RgnDesc->Region.Length);
        Why = WhyBuf;

        if (debug_level () > 2)
        {
            /* flow trace */
            fprintf_bu (LstFileHandle, LOGFILE, "out of bounds");
        }

        if (debug_level () > 0)
        {
            DumpStackEntry (RgnDesc);
            DumpStackEntry (ObjDesc);
        }
        return S_ERROR;
    }

    if (debug_level () > 2)
    {
        /* flow trace */
        fprintf_bu (LstFileHandle, LOGFILE, "S_SUCCESS");
    }

    return S_SUCCESS;
}


/*****************************************************************************
 * 
 * FUNCTION:    ReadField
 *
 * PARAMETERS:  OBJECT_DESCRIPTOR * ObjDesc         Field to be read
 *              UINT32*             Value           Where to store value
 *              INT32               FieldBitWidth   Field Width in bits (8, 16, or 32)
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Retrieve the value of the given field
 *
 ****************************************************************************/

static INT32
ReadField (OBJECT_DESCRIPTOR *ObjDesc, UINT32*Value, INT32 FieldBitWidth)
{
    /* ObjDesc is validated by callers */

    OBJECT_DESCRIPTOR   *RgnDesc = ObjDesc->Field.Container;
    UINT32              Address;
    INT32               FieldByteWidth = FieldBitWidth / 8;
    INT32               Excep = SetupField (ObjDesc, RgnDesc, FieldBitWidth);


    FUNCTION_TRACE ("ReadField");


    if (S_SUCCESS != Excep)
    {
        return Excep;
    }

    /* 
     * Round offset down to next multiple of
     * field width, and add region base address.
     */
    Address = RgnDesc->Region.Address
            + (ObjDesc->Field.Offset & ~((UINT32) FieldByteWidth - 1));

    if (Trace & TraceOpRgn)
    {
        if (OUTRANGE (RgnDesc->Region.SpaceId, RegionTypes))
        {
            fprintf_bu (LstFileHandle, LOGFILE,
                "** ReadField: Read from unknown region SpaceID %d at %08lx width %d ** ",
                    RgnDesc->Region.SpaceId, Address, FieldBitWidth);
        }

        else
        {
            fprintf_bu (LstFileHandle, LOGFILE,
                        "** Read from %s at %08lx width %d",
                        RegionTypes[RgnDesc->Region.SpaceId], Address, FieldBitWidth);
            fflush_bu (LstFileHandle);
        }
    }


    switch(RgnDesc->Region.SpaceId)
    {
        void *      PhysicalAddrPtr;
        UINT8       PciBus;
        UINT8       DevFunc;
        UINT8       PciReg;
        UINT8       PciExcep;

        case SystemMemory:

            /* System memory defined to be in first Mbyte  */
            /* XXX:  Is this true on all OS/platform combinations??  */

            if (Address & 0xFFF00000UL)
            {
                sprintf(WhyBuf,
                        "ReadField:implementation limitation: SystemMemory address %08lx over 1MB", Address);
                Why = WhyBuf;
                return S_ERROR;
            }

            /* XXX: was PhysicalAddrPtr = PHYStoFP(Address); */

            /* 
             * XXX: This may be too high an overhead to do every time.
             * Probably should have a mapping cached.
             */

            PhysicalAddrPtr = OsdMapMemory (Address, 4);

            switch (FieldBitWidth)
            {
                case 8:
                    *Value = (UINT32)* (UINT8 *) PhysicalAddrPtr;
                    break;

                case 16:
                    *Value = (UINT32)* (UINT16 *) PhysicalAddrPtr;
                    break;

                case 32:
                    *Value = * (UINT32 *) PhysicalAddrPtr;
                    break;

                default:
                    sprintf (WhyBuf,
                            "ReadField: invalid SystemMemory width %d", FieldBitWidth);
                    Why = WhyBuf;
                    OsdUnMapMemory (PhysicalAddrPtr, 4);
                    return S_ERROR;
            }

            OsdUnMapMemory (PhysicalAddrPtr, 4);
            break;

        case SystemIO:
            switch (FieldBitWidth)
            {
                case 8:
                    *Value = (UINT32) OsdIn8 ((UINT16) Address);
                    break;

                case 16:
                    *Value = (UINT32) OsdIn16 ((UINT16) Address);
                    break;

                case 32:
                    *Value = OsdIn32 ((UINT16) Address);
                    break;

                default:
                    sprintf(WhyBuf,
                            "ReadField: invalid SystemIO width %d", FieldBitWidth);
                    Why = WhyBuf;
                    return S_ERROR;
            }
            break;

        case PCIConfig:
            PciBus = (UINT8) (Address >> 16);
            DevFunc = (UINT8) (Address >> 8);
            PciReg = (UINT8) ((Address >> 2) & 0x3f);

            switch (FieldBitWidth)
            {
                case 8:
                    PciExcep = OsdReadPciCfgByte (PciBus, DevFunc, PciReg, (UINT8 *) Value);
                    break;

                case 16:
                    PciExcep = OsdReadPciCfgWord (PciBus, DevFunc, PciReg, (UINT16 *) Value);
                    break;

                case 32:
                    PciExcep = OsdReadPciCfgDword (PciBus, DevFunc, PciReg, Value);
                    break;

                default:
                    sprintf (WhyBuf,
                            "ReadField: invalid PCIConfig width %d", FieldBitWidth);
                    Why = WhyBuf;
                    return S_ERROR;
            }
            if (PciExcep)
            {
                return S_ERROR;
            }
            break;

        case EmbeddedControl:
        case SMBus:

            /* XXX - Actual read should happen here */

            sprintf (WhyBuf, "ReadField: Region type %s not implemented",
                    RegionTypes[RgnDesc->Region.SpaceId]);
            Why = WhyBuf;
            return S_ERROR;

        default:
            sprintf (WhyBuf, "ReadField: Unknown region SpaceID %d",
                    RgnDesc->Region.SpaceId);
            Why = WhyBuf;
            return S_ERROR;
    }

    if (Trace & TraceOpRgn)
    {
        fprintf_bu (LstFileHandle, LOGFILE, " val %08lx ", *Value);
    }

    return S_SUCCESS;
}


/*****************************************************************************
 * 
 * FUNCTION:    WriteField
 *
 * PARAMETERS:  OBJECT_DESCRIPTOR * ObjDesc         Field to be set
 *              UINT32              Value           Value to store
 *              INT32               FieldBitWidth   Field Width in bits (8, 16, or 32)
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Store the value into the given field
 *
 ****************************************************************************/

static INT32
WriteField (OBJECT_DESCRIPTOR *ObjDesc, UINT32 Value, INT32 FieldBitWidth)
{
    /* ObjDesc is validated by callers */

    OBJECT_DESCRIPTOR *     RgnDesc = ObjDesc->Field.Container;
    UINT32                  Address;
    INT32                   FieldByteWidth = FieldBitWidth / 8;
    INT32                   Excep = SetupField (ObjDesc, RgnDesc, FieldBitWidth);


    FUNCTION_TRACE ("WriteField");


    if (S_SUCCESS != Excep)
    {
        return Excep;
    }

    Address = RgnDesc->Region.Address
                + (ObjDesc->Field.Offset & ~((UINT32) FieldByteWidth - 1));

    if (Trace & TraceOpRgn)
    {
        if (OUTRANGE (RgnDesc->Region.SpaceId, RegionTypes))
        {
            fprintf_bu (LstFileHandle, LOGFILE,
                "** WriteField: Store %lx in unknown region SpaceID %d at %08lx width %d ** ",
                    Value, RgnDesc->Region.SpaceId, Address, FieldBitWidth);
        }
        else
        {
            fprintf_bu (LstFileHandle, LOGFILE,
                    "** Store %lx in %s at %08lx width %d",
                    Value, RegionTypes[RgnDesc->Region.SpaceId], Address, FieldBitWidth);
            fflush_bu (LstFileHandle);
        }
    }

    switch(RgnDesc->Region.SpaceId)
    {
        void        *PhysicalAddrPtr;
        UINT8       PciBus;
        UINT8       DevFunc;
        UINT8       PciReg;
        UINT8       PciExcep;


        case SystemMemory:

            if (Address & 0xFFF00000UL)
            {
                sprintf (WhyBuf,
                        "WriteField:implementation limitation: SystemMemory address %08lx over 1MB", Address);
                Why = WhyBuf;
                return S_ERROR;
            }


            /* XXX: was PhysicalAddrPtr = PHYStoFP(Address); */

            /* XXX: This may be too high an overhead to do every time.
             * Probably should have a mapping cached.
             */

            PhysicalAddrPtr = OsdMapMemory (Address, 4);
                    
            switch (FieldBitWidth)
            {
                case 8:
                    *(UINT8 *) PhysicalAddrPtr = (UINT8) Value;
                    break;

                case 16:
                    *(UINT16 *) PhysicalAddrPtr = (UINT16) Value;
                    break;

                case 32:
                    *(UINT32 *) PhysicalAddrPtr = Value;
                    break;

                default:
                    sprintf (WhyBuf,
                            "WriteField: invalid SystemMemory width %d", FieldBitWidth);
                    Why = WhyBuf;
                    OsdUnMapMemory (PhysicalAddrPtr, 4);
                    return S_ERROR;
            }

            OsdUnMapMemory (PhysicalAddrPtr, 4);
            break;

        case SystemIO:
            switch (FieldBitWidth)
            {
                case 8:
                    OsdOut8 ((UINT16) Address, (UINT8) Value);
                    break;

                case 16:
                    OsdOut16 ((UINT16) Address, (UINT16) Value);
                    break;

                case 32:
                    OsdOut32 ((UINT16) Address, Value);
                    break;

                default:
                    sprintf (WhyBuf,
                            "WriteField: invalid SystemIO width %d", FieldBitWidth);
                    Why = WhyBuf;
                    return S_ERROR;
            }
            break;

        case PCIConfig:
            PciBus = (UINT8) (Address >> 16);
            DevFunc = (UINT8) (Address >> 8);
            PciReg = (UINT8) ((Address >> 2) & 0x3f);

            switch (FieldBitWidth)
            {
                case 8:
                    PciExcep = OsdWritePciCfgByte (PciBus, DevFunc, PciReg, *(UINT8 *)&Value);
                    break;

                case 16:
                    PciExcep = OsdWritePciCfgWord (PciBus, DevFunc, PciReg, *(UINT16 *)&Value);
                    break;

                case 32:
                    PciExcep = OsdWritePciCfgDword (PciBus, DevFunc, PciReg, Value);
                    break;

                default:
                    sprintf (WhyBuf,
                            "WriteField: invalid PCIConfig width %d", FieldBitWidth);
                    Why = WhyBuf;
                    return S_ERROR;
            }
            if (PciExcep)
            {
                return S_ERROR;
            }
            break;

        case EmbeddedControl:
        case SMBus:

            /* XXX - Actual write should happen here */
 
            sprintf (WhyBuf, "WriteField: Region type %s not implemented",
                    RegionTypes[RgnDesc->Region.SpaceId]);
            Why = WhyBuf;
            return S_ERROR;

        default:
            sprintf (WhyBuf, "WriteField: Unknown region SpaceID %d",
                    RgnDesc->Region.SpaceId);
            Why = WhyBuf;
            return S_ERROR;
    }

    return S_SUCCESS;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlAppendBlockOwner
 *
 * PARAMETERS:  void *Owner
 *
 * DESCRIPTION: Append block-owner data from bu_plumr to WhyBuf.
 *
 ****************************************************************************/

static void
AmlAppendBlockOwner (void *Owner)
{

#ifdef PLUMBER
    if (Why != WhyBuf)
    {
        /* Copy message to WhyBuf */
        
        strcpy(WhyBuf, Why);
        Why = WhyBuf;
    }

#if 1
    vPlumber ("internal type mismatch", 3);
#endif

    sprintf (&WhyBuf[strlen (WhyBuf)], " %s", pcIdentifyOwner(Owner));

#endif  /* PLUMBER */
}


/*****************************************************************************
 * 
 * FUNCTION:    AccessNamedField
 *
 * PARAMETERS:  INT32       Mode           ACPI_READ or ACPI_WRITE
 *              NsHandle    NamedField     Handle for field to be accessed
 *              UINT32      *Value          Value to be read or written
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Read or write a named field
 *
 ****************************************************************************/

static INT32
AccessNamedField (INT32 Mode, NsHandle NamedField, UINT32 *Value)
{
    OBJECT_DESCRIPTOR *     ObjDesc = NsValPtr (NamedField);
    char *                  Type;
    INT32                   Granularity;
    INT32                   Excep;
    INT32                   MaxW;


    FUNCTION_TRACE ("AccessNamedField");


    if ((OBJECT_DESCRIPTOR *) 0 == ObjDesc)
    {
        Why = "AccessNamedField:internal error: null value pointer";
        return S_ERROR;
    }

    if (DefField != NsValType (NamedField))
    {
        sprintf (WhyBuf,
                  "AccessNamedField: Name %4.4s type %d is not a defined field",
                  NamedField, NsValType (NamedField));
        Why = WhyBuf;
        return S_ERROR;
    }

    if (debug_level () > 2)
    {
        fprintf_bu (LstFileHandle, LOGFILE,
                    "in AccessNamedField: DefField type and ValPtr OK in nte ");
        NsDumpEntry (NamedField, LOGFILE);

        fprintf_bu (LstFileHandle, LOGFILE, "ObjDesc = %p, ObjDesc->ValType = %d",
                    ObjDesc, ObjDesc->ValType);
        fprintf_bu (LstFileHandle, LOGFILE, " DatLen = %d, BitOffset = %d",
                    ObjDesc->FieldUnit.DatLen, ObjDesc->FieldUnit.BitOffset);
    }

    if (DefField != ObjDesc->ValType)
    {
        sprintf (WhyBuf,
                "AccessNamedField:internal error: Name %4.4s type %d does not match value-type %d at %p",
                NamedField, NsValType (NamedField), ObjDesc->ValType, ObjDesc);
        Why = WhyBuf;
        AmlAppendBlockOwner (ObjDesc);
        return S_ERROR;
    }

    switch (ObjDesc->Field.Access)
    {
        case AnyAcc:
            Granularity = 8;
            MaxW = 32;
            Type = "UINT32";
            break;

        case ByteAcc:
            Granularity = MaxW = 8;
            Type = "UINT8";
            break;

        case WordAcc:
            Granularity = MaxW = 16;
            Type = "UINT16";
            break;

        case DWordAcc:
            Granularity = MaxW = 32;
            Type = "UINT32";
            break;

        default:
            sprintf (WhyBuf,
                    "AccessNamedField: unknown access type %d",
                    ObjDesc->Field.Access);
            Why = WhyBuf;
            return S_ERROR;
    }

    if (ObjDesc->FieldUnit.DatLen + ObjDesc->FieldUnit.BitOffset > (UINT16) MaxW)
    {
        sprintf (WhyBuf, "AccessNamedField: Field exceeds %s", Type);
        Why = WhyBuf;
        return S_ERROR;
    }

    /* 
     * As long as MaxW/2 is wide enough for the data and MaxW > Granularity,
     * divide MaxW by 2.
     */
    while (Granularity < MaxW
            && ObjDesc->FieldUnit.DatLen + ObjDesc->FieldUnit.BitOffset
                <= (UINT16) MaxW / 2)
    {
        MaxW /= 2;
    }

    if (ACPI_WRITE == Mode)
    {
        /* Construct Mask with 1 bits where the field is, 0 bits elsewhere */

        UINT32      Mask = (((UINT32) 1 << ObjDesc->FieldUnit.DatLen) - (UINT32) 1)
                            << ObjDesc->Field.BitOffset;
        /* Shift and mask the value into the field position */

        UINT32      dValue = (*Value << ObjDesc->Field.BitOffset) & Mask;
        INT32       Locked = FALSE;


        if (ObjDesc->FieldUnit.DatLen % Granularity || ObjDesc->FieldUnit.BitOffset)
        {
            /* Write does not fill an integral number of naturally aligned units */

            switch (ObjDesc->Field.UpdateRule)
            {
                UINT32 OldVal;

                case Preserve:

                    /* 
                     * Read the current contents of the byte/word/dword containing
                     * the field, and merge with the new field value.
                     */
                    Excep = ReadField (ObjDesc, &OldVal, MaxW);
                    if (S_SUCCESS != Excep)
                    {
                        return Excep;
                    }

                    dValue |= OldVal & ~Mask;
                    break;

                case WriteAsOnes:

                    /* Set positions outside the field to 1's */

                    dValue |= ~Mask;
                    break;

                case WriteAsZeros:

                    /* 
                     * Positions outside the field are already 0
                     * due to "& Mask" above
                     */
                    break;

                default:
                    sprintf (WhyBuf,
                                "AccessNamedField: Unknown UpdateRule setting %d",
                                ObjDesc->Field.UpdateRule);
                    Why = WhyBuf;
                    return S_ERROR;
            }
        }

        if (debug_level () > 2)
        {
            fprintf_bu (LstFileHandle, LOGFILE, " invoking WriteField");
        }

        /* Check lock rule prior to modifing the field */

        if (ObjDesc->FieldUnit.LockRule == (UINT16) Lock)
        {
            if (GetGlobalLock () == S_ERROR)
            {
                /* the ownship failed - Bad Bad Bad, this is a single threaded */
                /* implementation so there is no way some other process should */
                /* own this.  This means something grabbed it and did not */
                /* release the Global Lock! (Why will already be set) */

                return (S_ERROR);
            }
            else
            {
                Locked = TRUE;
            }
        }

        /* perform the update */

        Excep = WriteField (ObjDesc, dValue, MaxW);

        /* if the Global Lock is owned the release it */

        if (Locked)
        {
            ReleaseGlobalLock ();
            Locked = FALSE;
        }
    }

    else
    {
        /* ACPI_READ */

        Excep = ReadField (ObjDesc, Value, MaxW);

        if (S_SUCCESS == Excep)
        {
            *Value >>= ObjDesc->Field.BitOffset;
            *Value &= (((UINT32) 1 << ObjDesc->FieldUnit.DatLen) - (UINT32) 1);
        }
    }

    return Excep;
}


/*****************************************************************************
 * 
 * FUNCTION:    SetNamedFieldValue
 *
 * PARAMETERS:  NsHandle    NamedField     Handle for field to be set
 *              UINT32      Value          Value to be stored in field
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Store the given value into the field
 *
 ****************************************************************************/

INT32
SetNamedFieldValue (NsHandle NamedField, UINT32 Value)
{
    FUNCTION_TRACE ("SetNamedFieldValue");


    if ((NsHandle) 0 == NamedField)
    {
        Why = "SetNamedFieldValue:internal error:null handle";
        return S_ERROR;
    }

    return AccessNamedField (ACPI_WRITE, NamedField, &Value);
}


/*****************************************************************************
 * 
 * FUNCTION:    GetNamedFieldValue
 *
 * PARAMETERS:  NsHandle    NamedField      Handle for field to be read
 *              UINT32      *Value          Where to store value read froom field
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Retrieve the value of the given field
 *
 ****************************************************************************/

INT32
GetNamedFieldValue (NsHandle NamedField, UINT32 *Value)
{
    FUNCTION_TRACE ("GetNamedFieldValue");


    if ((NsHandle) 0 == NamedField)
    {
        Why = "GetNamedFieldValue:internal error:null handle";
        return S_ERROR;
    }

    return AccessNamedField (ACPI_READ, NamedField, Value);
}


/*****************************************************************************
 * 
 * FUNCTION:    ExecStore
 *
 * PARAMETERS:  OBJECT_DESCRIPTOR *ValDesc  value to be stored
 *              OBJECT_DESCRIPTOR *DestDesc where to store it -- must be
 *                                          either an (NsHandle) or an
 *                                          OBJECT_DESCRIPTOR of type Lvalue;
 *                                          if the latter the descriptor will
 *                                          be either reused or deleted.
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Store the value described by ValDesc into the location
 *              described by DestDesc.  Called by various interpreter
 *              functions to store the result of an operation into
 *              the destination operand.
 *
 * ALLOCATION:
 *  Reference      Size                    Pool    Owner       Description
 *  nte.ValDesc    s(OBJECT_DESCRIPTOR)    bu      amlexec     Name(Lvalue)
 *
 ****************************************************************************/

INT32
ExecStore(OBJECT_DESCRIPTOR *ValDesc, OBJECT_DESCRIPTOR *DestDesc)
{
    NsHandle        TempHandle;
    INT32           Excep;
    INT32           Stacked = FALSE;
    INT32           Locked = FALSE;


    FUNCTION_TRACE ("ExecStore");


    if ((OBJECT_DESCRIPTOR *) 0 == ValDesc || (OBJECT_DESCRIPTOR *) 0 == DestDesc)
    {
        Why = "ExecStore:internal error: null pointer";
        return S_ERROR;
    }

    if (debug_level () > 2)
    {
        fprintf_bu (LstFileHandle, LOGFILE, "in ExecStore");
    }

    if (IsNsHandle (DestDesc))
    {
        TempHandle = (NsHandle) DestDesc;
        DestDesc = NEW (OBJECT_DESCRIPTOR);

        if (DestDesc)
        {
            DestDesc->ValType       = (UINT8) Lvalue;
            DestDesc->Lvalue.OpCode = NameOp;
            DestDesc->Lvalue.Ref    = TempHandle;

            /* Push the descriptor on TOS temporarily
             * to protect it from garbage collection
             */
            Excep = PushIfExec (Exec);
            if (S_SUCCESS != Excep)
            {
                DELETE (DestDesc);
                return Excep;
            }

            ObjStack[ObjStackTop] = DestDesc;
            Stacked = TRUE;
        }

        else
        {
            KFatalError ("0006", ("ExecStore: Descriptor Allocation Failure"));
            return S_ERROR;
        }
    }

    if (DestDesc->ValType != Lvalue)
    {
        sprintf (WhyBuf, "ExecStore: Store target is not an Lvalue [%s]",
                NsTypeNames[DestDesc->ValType]);
        Why = WhyBuf;

        if (debug_level () > 0)
        {
            DumpStackEntry (ValDesc);
            DumpStackEntry (DestDesc);
            DumpStack (Exec, "ExecStore", 2, "target not Lvalue");
        }

        return S_ERROR;
    }

    switch (DestDesc->Lvalue.OpCode)
    {
    case NameOp:

        /* Storing into a Name */

        TempHandle = DestDesc->Lvalue.Ref;
        switch (NsValType (TempHandle))              /* Type of Name's existing value */
        {
            case Alias:
#if 1
                sprintf (WhyBuf,
                          "ExecStore/NameOp: Store into %s not implemented",
                          NsTypeNames[NsValType (TempHandle)]);
                Why = WhyBuf;
                Excep = S_ERROR;
#else
                fprintf_bu (LstFileHandle, LOGFILE,
                        "ExecStore/NameOp: Store into %s not implemented",
                          NsTypeNames[NsValType(TempHandle)]);
                Excep = S_SUCCESS;
#endif
                DELETE (DestDesc);
                break;

            case BankField:

                /* 
                 * Storing into a BankField.
                 * If value is not a Number, try to resolve it to one.
                 */
                if (ValDesc->ValType != Number
                    && (Excep = GetRvalue (&ValDesc)) != S_SUCCESS)
                {
                    DELETE (DestDesc);
                    break;
                }

                if (ValDesc->ValType != Number)
                {
                    sprintf(WhyBuf,
                            "ExecStore: Value assigned to BankField must be Number, not %d",
                            ValDesc->ValType);
                    Why = WhyBuf;
                    DELETE (DestDesc);
                    Excep = S_ERROR;
                    break;
                }

                /* 
                 * Delete descriptor that points to name,
                 * and point to descriptor for name's value instead.
                 */

                DELETE (DestDesc);
                DestDesc = NsValPtr (TempHandle);

                if ((OBJECT_DESCRIPTOR *) 0 == DestDesc)
                {
                    Why = "ExecStore/BankField:internal error: null old-value pointer";
                    Excep = S_ERROR;
                    break;
                }

                if (BankField != DestDesc->ValType)
                {
                    sprintf(WhyBuf,
                            "ExecStore/BankField:internal error: Name %4.4s type %d does not match value-type %d at %p",
                              TempHandle, NsValType(TempHandle), DestDesc->ValType, DestDesc);
                    Why = WhyBuf;
                    AmlAppendBlockOwner (DestDesc);
                    Excep = S_ERROR;
                    break;
                }

                /* Set Bank value to select proper Bank */
                /* Check lock rule prior to modifing the field */

                if (DestDesc->BankField.LockRule == (UINT16) Lock)
                {
                    /* Lock Rule is Lock */

                    if (GetGlobalLock () == S_ERROR)
                    {
                        /* the ownship failed - Bad Bad Bad, this is a single threaded */
                        /* implementation so there is no way some other process should */
                        /* own this.  This means something grabbed it and did not */
                        /* release the Global Lock! (Why will already be set) */

                        return (S_ERROR);
                    }

                    else
                    {
                        /* perform the update */

                        Excep = SetNamedFieldValue (DestDesc->BankField.BankSelect,
                                                            DestDesc->BankField.BankVal);
                    }
                    
                    /* Release the Global Lock */
                    
                    ReleaseGlobalLock ();
                }
                
                else
                {
                    /* Lock Rule is NoLock */
                    /* perform the update */
                    
                    Excep = SetNamedFieldValue (DestDesc->BankField.BankSelect,
                                                        DestDesc->BankField.BankVal);
                }
                
                if (debug_level () > 2)
                {
                    fprintf_bu (LstFileHandle, LOGFILE,
                                "set bank select returned %s", RV[Excep]);
                }

                if (S_SUCCESS == Excep)
                {
                    if (debug_level () > 2)
                    {
                        fprintf_bu (LstFileHandle, LOGFILE, " about to set data");
                    }

                    /* Set Data value */
                    
                    Excep = SetNamedFieldValue (DestDesc->BankField.BankSelect,
                                                      ValDesc->BankField.BankVal);
                    if (debug_level() > 2)
                    {
                        fprintf_bu (LstFileHandle, LOGFILE,
                                "set bank select returned %s", RV[Excep]);
                    }
                }
                break;


            case DefField:

                /* 
                 * Storing into a Field defined in a Region.
                 * If value is not a Number, try to resolve it to one.
                 */

                if (ValDesc->ValType != Number
                    && (Excep = GetRvalue (&ValDesc)) != S_SUCCESS)
                {
                    DELETE (DestDesc);
                    break;
                }

                if (ValDesc->ValType != Number)
                {
                    sprintf (WhyBuf,
                            "ExecStore/DefField: Value assigned to Field must be Number, not %d",
                              ValDesc->ValType);
                    Why = WhyBuf;
                    DELETE (DestDesc);
                    Excep = S_ERROR;
                    break;
                }

                /* 
                 * Delete descriptor that points to name,
                 * and point to descriptor for name's value instead.
                 */

                DELETE (DestDesc);
                DestDesc = NsValPtr (TempHandle);
                
                if ((OBJECT_DESCRIPTOR *) 0 == DestDesc)
                {
                    Why = "ExecStore/DefField:internal error: null old-value pointer";
                    Excep = S_ERROR;
                    break;
                }

                if (DefField != DestDesc->ValType)
                {
                    sprintf (WhyBuf,
                                "ExecStore/DefField:internal error: Name %4.4s type %d does not match value-type %d at %p",
                                TempHandle, NsValType (TempHandle), DestDesc->ValType, DestDesc);
                    Why = WhyBuf;
                    AmlAppendBlockOwner (DestDesc);
                    Excep = S_ERROR;
                    break;
                }

                /* Check lock rule prior to modifing the field */
                
                if (ValDesc->Field.LockRule == (UINT16) Lock)
                {
                    /* Lock Rule is Lock */
                    
                    if (GetGlobalLock () == S_ERROR)
                    {
                        /* the ownship failed - Bad Bad Bad, this is a single threaded */
                        /* implementation so there is no way some other process should */
                        /* own this.  This means something grabbed it and did not */
                        /* release the Global Lock! (Why will already be set) */
                        
                        return (S_ERROR);
                    }
                    
                    else
                    {
                        /* perform the update */
                        
                        Excep = SetNamedFieldValue (TempHandle, ValDesc->Number.Number);
                    }
                    
                    /* Release the Global Lock */
                    
                    ReleaseGlobalLock();
                }
                
                else
                {
                    /* Lock Rule is NoLock */
                    /* perform the update */
                    
                    Excep = SetNamedFieldValue (TempHandle, ValDesc->Number.Number);
                }
                
                break;

            case IndexField:
                
                /* 
                 * Storing into an IndexField.
                 * If value is not a Number, try to resolve it to one.
                 */
                
                if (ValDesc->ValType != Number
                    && (Excep = GetRvalue (&ValDesc)) != S_SUCCESS)
                {
                    DELETE (DestDesc);
                    break;
                }

                if (ValDesc->ValType != Number)
                {
                    sprintf (WhyBuf,
                            "ExecStore: Value assigned to IndexField must be Number, not %d",
                              ValDesc->ValType);
                    Why = WhyBuf;
                    DELETE (DestDesc);
                    Excep = S_ERROR;
                    break;
                }

                /* 
                 * Delete descriptor that points to name,
                 * and point to descriptor for name's value instead.
                 */

                DELETE (DestDesc);
                DestDesc = NsValPtr (TempHandle);
                
                if ((OBJECT_DESCRIPTOR *) 0 == DestDesc)
                {
                    Why = "ExecStore/IndexField:internal error: null old-value pointer";
                    Excep = S_ERROR;
                    break;
                }
                
                if (IndexField != DestDesc->ValType)
                {
                    sprintf (WhyBuf,
                            "ExecStore/IndexField:internal error: Name %4.4s type %d does not match value-type %d at %p",
                              TempHandle, NsValType (TempHandle), DestDesc->ValType, DestDesc);
                    Why = WhyBuf;
                    AmlAppendBlockOwner (DestDesc);
                    Excep = S_ERROR;
                    break;
                }

                /* Set Index value to select proper Data register */
                /* Check lock rule prior to modifing the field */
                
                if (DestDesc->IndexField.LockRule == (UINT16) Lock)
                {
                    /* Lock Rule is Lock */
                   
                    if (GetGlobalLock () == S_ERROR)
                    {
                        /* the ownship failed - Bad Bad Bad, this is a single threaded */
                        /* implementation so there is no way some other process should */
                        /* own this.  This means something grabbed it and did not */
                        /* release the Global Lock! (Why will already be set) */
                        
                        return (S_ERROR);
                    }
                    
                    else
                    {
                        /* perform the update */
                        Excep = SetNamedFieldValue (DestDesc->IndexField.Index,
                                                          DestDesc->IndexField.IndexVal);
                    }

                    /* Release the Global Lock */
                    
                    ReleaseGlobalLock();
                }
                
                else
                {
                    /* Lock Rule is NoLock */
                    /* perform the update */
                    
                    Excep = SetNamedFieldValue (DestDesc->IndexField.Index,
                                                      DestDesc->IndexField.IndexVal);
                }
                
                Excep = SetNamedFieldValue (DestDesc->IndexField.Index,
                                                  DestDesc->IndexField.IndexVal);
                if (debug_level () > 2)
                {
                    fprintf_bu (LstFileHandle, LOGFILE,
                            "set index returned %s", RV[Excep]);
                }

                if (S_SUCCESS == Excep)
                {
                    if (debug_level () > 2)
                    {
                        fprintf_bu (LstFileHandle, LOGFILE, " about to set data");
                    }

                    /* Set Data value */
                    
                    Excep = SetNamedFieldValue (DestDesc->IndexField.Data,
                                                      ValDesc->Number.Number);
                    if (debug_level () > 2)
                    {
                        fprintf_bu(LstFileHandle, LOGFILE,
                                "set data returned %s", RV[Excep]);
                    }
                }
                break;

            case FieldUnit:
                
                /* 
                 * Storing into a FieldUnit (defined in a Buffer).
                 * If value is not a Number, try to resolve it to one.
                 */
                if (ValDesc->ValType != Number
                    && (Excep = GetRvalue (&ValDesc)) != S_SUCCESS)
                {
                    DELETE (DestDesc);
                    break;
                }

                if (ValDesc->ValType != Number)
                {
                    sprintf (WhyBuf,
                            "ExecStore/FieldUnit: Value assigned to Field must be Number, not %d",
                              ValDesc->ValType);
                    Why = WhyBuf;
                    DELETE (DestDesc);
                    Excep = S_ERROR;
                    break;
                }

                /* 
                 * Delete descriptor that points to name,
                 * and point to descriptor for name's value instead.
                 */
                DELETE (DestDesc);
                DestDesc = NsValPtr (TempHandle);
                
                if ((OBJECT_DESCRIPTOR *) 0 == DestDesc)
                {
                    Why = "ExecStore/FieldUnit:internal error: null old-value pointer";
                    Excep = S_ERROR;
                    break;
                }
                
                if (DestDesc->ValType != (UINT8) NsValType (TempHandle))
                {
                    sprintf (WhyBuf,
                            "ExecStore/FieldUnit:internal error: Name %4.4s type %d does not match value-type %d at %p",
                              TempHandle, NsValType(TempHandle), DestDesc->ValType, DestDesc);
                    Why = WhyBuf;
                    AmlAppendBlockOwner (DestDesc);
                    Excep = S_ERROR;
                    break;
                }

                if (!DestDesc->FieldUnit.Container
                    || Buffer != DestDesc->FieldUnit.Container->ValType
                    || DestDesc->FieldUnit.ConSeq
                     != DestDesc->FieldUnit.Container->Buffer.Sequence)
                {
                    char *FullyQN = NsFullyQualifiedName (TempHandle);

                    if (debug_level() > 0)
                    {
                        printf_bu ("ExecStore/FieldUnit: bad container in %s (%p)\n",
                                     FullyQN, TempHandle);
                        NsDumpEntry (TempHandle, SCREEN | LOGFILE);
                    }

                    sprintf (WhyBuf,
                                "ExecStore/FieldUnit: bad container %p in %s",
                                DestDesc->FieldUnit.Container, FullyQN);
                    Why = WhyBuf;
                    Excep = S_ERROR;
                    break;
                }

                /* Check lock rule prior to modifing the field */
                
                if (DestDesc->FieldUnit.LockRule == (UINT16) Lock)
                {
                    /* Lock Rule is Lock */
                    
                    if (GetGlobalLock () == S_ERROR)
                    {
                        /* the ownship failed - Bad Bad Bad, this is a single threaded */
                        /* implementation so there is no way some other process should */
                        /* own this.  This means something grabbed it and did not */
                        /* release the Global Lock! (Why will already be set) */
                        
                        return (S_ERROR);
                    }
                    
                    else
                    {
                        /* Set the Locked Flag */
                        
                        Locked = TRUE;
                    }
                }
                
                if (DestDesc->FieldUnit.DatLen + DestDesc->FieldUnit.BitOffset > 32)
                {
                    if (Locked)
                    {
                        /* Release the Global Lock */
                        
                        ReleaseGlobalLock ();
                        Locked = FALSE;
                    }
                    
                    Why = "ExecStore/FieldUnit:implementation limitation: Field exceeds UINT32";
                    Excep = S_ERROR;
                }
                
                else
                {
                    /* Field location is (base of buffer) + (byte offset) */
                    
                    UINT8 *      Location = DestDesc->FieldUnit.Container->Buffer.Buffer
                                            + DestDesc->FieldUnit.Offset;
                    
                    /* 
                     * Construct Mask with 1 bits where the field is,
                     * 0 bits elsewhere
                     */
                    UINT32      Mask = ((UINT32) 1 << DestDesc->FieldUnit.DatLen) - (UINT32)1
                                         << DestDesc->FieldUnit.BitOffset;

                    if (Trace & TraceBufFld)
                    {
                        fprintf_bu(LstFileHandle, LOGFILE,
                            "** Store %lx in buffer %p byte %ld bit %d width %d addr %p mask %08lx",
                            ValDesc->Number.Number,
                            DestDesc->FieldUnit.Container->Buffer.Buffer,
                            DestDesc->FieldUnit.Offset,
                            DestDesc->FieldUnit.BitOffset,
                            DestDesc->FieldUnit.DatLen,
                            Location, Mask);
                    }

                    /* zero out the field in the buffer */
                    
                    *(UINT32 *) Location &= ~Mask;

                    /* 
                     * Shift and mask the new value into position,
                     * and or it into the buffer.
                     */
                    *(UINT32 *) Location
                        |= (ValDesc->Number.Number << DestDesc->FieldUnit.BitOffset) & Mask;
                    
                    if (Trace & TraceBufFld)
                    {
                        fprintf_bu(LstFileHandle, LOGFILE,
                            " val %08lx", *(UINT32 *) Location);
                    }

                    Excep = S_SUCCESS;
                }
                
                if (Locked)
                {
                    /* Release the Global Lock */
                    
                    ReleaseGlobalLock ();
                    Locked = FALSE;
                }
                break;

            default:
                
                /* 
                 * All other types than Alias and the various Fields come here.
                 * Store a copy of ValDesc as the new value of the Name, and set
                 * the Name's type to that of the value being stored in it.
                 */
                memcpy ((void *) DestDesc, (void *) ValDesc, sizeof (*ValDesc));
                
                if (Buffer == DestDesc->ValType)
                {
                    /* Assign a new sequence number */

                    DestDesc->Buffer.Sequence = AmlBufSeq ();
                }

                NsSetValue (TempHandle, DestDesc, DestDesc->ValType);

                if (Stacked && debug_level () > 0)
                {
                    printf_bu ("ExecStore: set %s (%p)\n",
                                 NsFullyQualifiedName (TempHandle), TempHandle);
                    NsDumpEntry (TempHandle, SCREEN | LOGFILE);
                    DumpStackEntry (DestDesc);
                }

                Excep = S_SUCCESS;
                break;
        }
        break;


    case ZeroOp: case OneOp: case OnesOp:

        /* 
         * Storing to a constant is a no-op -- see spec sec 15.2.3.3.1.
         * Delete the result descriptor.
         */
        DELETE (DestDesc);
        Excep = S_SUCCESS;
        break;


    case Local0: case Local1: case Local2: case Local3:
    case Local4: case Local5: case Local6: case Local7:

        Excep = SetMethodValue (LCLBASE + DestDesc->Lvalue.OpCode - Local0, ValDesc, DestDesc);
        break;


    case Arg0: case Arg1: case Arg2: case Arg3:
    case Arg4: case Arg5: case Arg6:

        Excep = SetMethodValue (ARGBASE + DestDesc->Lvalue.OpCode - Arg0, ValDesc, DestDesc);
        break;


    case Debug1:

        /* 
         * Storing to the Debug object causes the value stored to be
         * displayed and otherwise has no effect -- see sec. 15.2.3.3.3.
         */
        fprintf_bu (LstFileHandle, LOGFILE, "DebugOp: ");
        DumpStackEntry (ValDesc);
        DELETE (DestDesc);
        Excep = S_SUCCESS;
        break;

#if 0
    case IndexOp:
        break;
#endif

    default:
        sprintf (WhyBuf,
                    "ExecStore:internal error: Unknown Lvalue subtype %02x",
                    DestDesc->Lvalue.OpCode);
        Why = WhyBuf;
        
        fprintf_bu (LstFileHandle, LOGFILE,
                    "ExecStore:internal error: Unknown Lvalue subtype %02x",
                    DestDesc->Lvalue.OpCode);
        
        _dump_buf (DestDesc, sizeof (OBJECT_DESCRIPTOR), ASCII | HEX,
                         LstFileHandle, LOGFILE);
        DELETE (DestDesc);
        Excep = S_ERROR;
    
    }   /* switch(DestDesc->Lvalue.OpCode) */


    if (Stacked)
    {
        --ObjStackTop;
    }

    return Excep;
}


/*****************************************************************************
 * 
 * FUNCTION:    GetFieldUnitValue
 *
 * PARAMETERS:  OBJECT_DESCRIPTOR * FieldDesc   points to a FIeldUnit
 *              OBJECT_DESCRIPTOR * ResultDesc  points to an empty descriptor
 *                                              which will become a Number
 *                                              containing the field's value.
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Retrieve the value from a FieldUnit
 *
 * ALLOCATION:  none
 *
 ****************************************************************************/

static INT32
GetFieldUnitValue (OBJECT_DESCRIPTOR *FieldDesc, OBJECT_DESCRIPTOR *ResultDesc)
{
    UINT8 *          Location;
    UINT32          Mask;
    INT32           Locked = FALSE;


    FUNCTION_TRACE ("GetFieldUnitValue");


    if (!FieldDesc)
    {
        Why = "GetFieldUnitValue: internal error: null field pointer";
        return S_ERROR;
    }

    if (!FieldDesc->FieldUnit.Container)
    {
        Why = "GetFieldUnitValue: internal error: null container pointer";
        return S_ERROR;
    }

    if (Buffer != FieldDesc->FieldUnit.Container->ValType)
    {
        Why = "GetFieldUnitValue: internal error: container is not a Buffer";
        return S_ERROR;
    }

    if (FieldDesc->FieldUnit.ConSeq
         != FieldDesc->FieldUnit.Container->Buffer.Sequence)
    {
        sprintf (WhyBuf,
                "GetFieldUnitValue: internal error: stale Buffer [%lx != %lx]",
                FieldDesc->FieldUnit.ConSeq,
                FieldDesc->FieldUnit.Container->Buffer.Sequence);
        Why = WhyBuf;
        return S_ERROR;
    }

    if (!ResultDesc)
    {
        Why = "GetFieldUnitValue: internal error: null result pointer";
        return S_ERROR;
    }

    /* Check lock rule prior to modifing the field */

    if (FieldDesc->FieldUnit.LockRule == (UINT16) Lock)
    {
        /* Lock Rule is Lock */
        
        if (GetGlobalLock () == S_ERROR)
        {
            /* the ownship failed - Bad Bad Bad, this is a single threaded */
            /* implementation so there is no way some other process should */
            /* own this.  This means something grabbed it and did not */
            /* release the Global Lock! (Why will already be set) */
            
            return (S_ERROR);
        }

        else
        {
            /* set the Locked Flag */

            Locked = TRUE;
        }
    }
    
    if (FieldDesc->FieldUnit.DatLen + FieldDesc->FieldUnit.BitOffset > 32)
    {
        if (Locked)
        {
            /* Release the Global Lock */
            
            ReleaseGlobalLock ();
            Locked = FALSE;
        }
        
        Why = "GetFieldUnitValue: implementation limitation: Field exceeds UINT32";
        return S_ERROR;
    }

    /* Field location is (base of buffer) + (byte offset) */
    
    Location = FieldDesc->FieldUnit.Container->Buffer.Buffer
                + FieldDesc->FieldUnit.Offset;

    /* Construct Mask with as many 1 bits as the field width */
    
    Mask = ((UINT32) 1 << FieldDesc->FieldUnit.DatLen) - (UINT32) 1;

    ResultDesc->Number.ValType = (UINT8) Number;

    /* Shift the word containing the field, and mask the value */
    
    ResultDesc->Number.Number
        = *(UINT32 *) Location >> FieldDesc->FieldUnit.BitOffset & Mask;

    if (Trace & TraceBufFld)
    {
        fprintf_bu (LstFileHandle, LOGFILE,
            "** Read from buffer %p byte %ld bit %d width %d addr %p mask %08lx val %08lx",
            FieldDesc->FieldUnit.Container->Buffer.Buffer,
            FieldDesc->FieldUnit.Offset,
            FieldDesc->FieldUnit.BitOffset,
            FieldDesc->FieldUnit.DatLen,
            Location, Mask, ResultDesc->Number.Number);
    }

    if (Locked)
    {
        /* Release the Global Lock */
        
        ReleaseGlobalLock ();
        Locked = FALSE;
    }

    return S_SUCCESS;
}


/*****************************************************************************
 * 
 * FUNCTION:    GetRvalue
 *
 * PARAMETERS:  OBJECT_DESCRIPTOR **StackPtr    points to entry on ObjStack,
 *                                              which can be either an
 *                                              (OBJECT_DESCRIPTOR *)
 *                                              or an NsHandle.
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Convert Lvalue entries on ObjStack to rvalues
 *
 * ALLOCATION:
 *  Reference   Size                    Pool    Owner       Description
 *  *StackPtr   s(OBJECT_DESCRIPTOR)    bu      amlexec     Value
 *
 ****************************************************************************/

INT32
GetRvalue (OBJECT_DESCRIPTOR **StackPtr)
{
    NsHandle            TempHandle;
    OBJECT_DESCRIPTOR * ObjDesc;
    INT32               Excep;


    FUNCTION_TRACE ("GetRvalue");


    if ((OBJECT_DESCRIPTOR **) 0 == StackPtr
        || (OBJECT_DESCRIPTOR *) 0 == *StackPtr)
    {
        Why = "GetRvalue:internal error: null pointer";
        return S_ERROR;
    }

    switch ((*StackPtr)->ValType)
    {
        case Lvalue:
            switch ((*StackPtr)->Lvalue.OpCode)
            {
                UINT8       MvIndex;

                case NameOp:
                    
                    /* Convert indirect name ptr to direct name ptr */
                    
                    TempHandle = (*StackPtr)->Lvalue.Ref;
                    DELETE (*StackPtr);
                    (*StackPtr) = TempHandle;
                    Excep = S_SUCCESS;
                    break;

                case Local0: case Local1: case Local2: case Local3:
                case Local4: case Local5: case Local6: case Local7:

                    if (debug_level () > 0)
                    {
                        fprintf_bu (LstFileHandle, LOGFILE,
                            "GetRvalue:Lcl%d: before GetMethodValue %p %p %08lx ",
                            MvIndex = (*StackPtr)->Lvalue.OpCode - Local0,
                            StackPtr, *StackPtr, *(UINT32 *)* StackPtr);
                    }

                    Excep = GetMethodValue (LCLBASE + (*StackPtr)->Lvalue.OpCode - Local0,
                                            *StackPtr);

                    if (debug_level () > 0)
                    {
                        fprintf_bu (LstFileHandle, LOGFILE,
                                    "GetRvalue:Lcl%d: iGMV Excep=%s %p %p %08lx ",
                                    MvIndex, RV[Excep], StackPtr, *StackPtr,
                                    *(UINT32 *)* StackPtr);
                        
                        if (Number == (*StackPtr)->ValType)
                        {
                            /* Value is a Number */
                            
                            fprintf_bu (LstFileHandle, LOGFILE,
                                        "[%ld] ", (*StackPtr)->Number.Number);
                        }
                    }
                    break;

                case Arg0: case Arg1: case Arg2: case Arg3:
                case Arg4: case Arg5: case Arg6:

                    if (debug_level() > 0)
                    {
                        fprintf_bu (LstFileHandle, LOGFILE,
                                    "GetRvalue:Arg%d: before GetMethodValue %p %p %08lx ",
                                    MvIndex = (*StackPtr)->Lvalue.OpCode - Arg0,
                                    StackPtr, *StackPtr, *(UINT32 *)* StackPtr);
                    }

                    Excep = GetMethodValue (ARGBASE + (*StackPtr)->Lvalue.OpCode - Arg0,
                                            *StackPtr);
                    
                    if (debug_level () > 0)
                    {
                        fprintf_bu (LstFileHandle, LOGFILE,
                                    "GetRvalue:Arg%d: iGMV returned %s %p %p %08lx ",
                                    MvIndex, RV[Excep], StackPtr, *StackPtr,
                                    *(UINT32 *)* StackPtr);

                        if (Number == (*StackPtr)->ValType)
                        {
                            /* Value is a Number */
                            
                            fprintf_bu (LstFileHandle, LOGFILE,
                                        "[%ld] ", (*StackPtr)->Number.Number);
                        }
                    }
                    break;

                case ZeroOp:
                    (*StackPtr)->ValType = (UINT8) Number;
                    (*StackPtr)->Number.Number = 0;
                    Excep = S_SUCCESS;
                    break;

                case OneOp:
                    (*StackPtr)->ValType = (UINT8) Number;
                    (*StackPtr)->Number.Number = 1;
                    Excep = S_SUCCESS;
                    break;

                case OnesOp:
                    (*StackPtr)->ValType = (UINT8) Number;
                    (*StackPtr)->Number.Number = 0xFFFFFFFF;
                    Excep = S_SUCCESS;
                    break;

                default:
                    sprintf (WhyBuf, "GetRvalue: Unknown Lvalue subtype %02x",
                            (*StackPtr)->Lvalue.OpCode);
                    Why = WhyBuf;
                    Excep = S_ERROR;

            }   /* switch ((*StackPtr)->Lvalue.OpCode) */

            if (S_SUCCESS != Excep)
            {
                return Excep;
            }

            break;

        case FieldUnit:
            ObjDesc = NEW (OBJECT_DESCRIPTOR);
            if ((OBJECT_DESCRIPTOR *) 0 == ObjDesc)
            {
                KFatalError ("0007", ("GetRvalue: Descriptor Allocation Failure"));
                return S_ERROR;
            }

            if ((Excep = GetFieldUnitValue (*StackPtr, ObjDesc)) != S_SUCCESS)
            {
                DELETE (ObjDesc);
            }
            
            *StackPtr = (void *) ObjDesc;
            return Excep;

        case BankField:
            ObjDesc = NEW (OBJECT_DESCRIPTOR);
            if ((OBJECT_DESCRIPTOR *) 0 == ObjDesc)
            {
                KFatalError ("0008", ("GetRvalue: Descriptor Allocation Failure"));
                return S_ERROR;
            }

            if ((Excep = GetFieldUnitValue (*StackPtr, ObjDesc)) != S_SUCCESS)
            {
                DELETE(ObjDesc);
            }

            *StackPtr = (void *) ObjDesc;
            return Excep;
            break;

        /* XXX - may need to handle IndexField, and DefField someday */

        default:
            break;

    }   /* switch ((*StackPtr)->ValType) */


    if (IsNsHandle (*StackPtr))       /* direct name ptr */
    {
        OBJECT_DESCRIPTOR *ValDesc
                = (OBJECT_DESCRIPTOR *) NsValPtr ((NsHandle)* StackPtr);

        if (Trace & TraceExec)
        {
            fprintf_bu (LstFileHandle, LOGFILE,
                          "GetRvalue: found direct name ptr ");
        }

        switch (NsValType ((NsHandle)* StackPtr))
        {
            UINT32          TempVal;

            case Package:

                /* 
                 * ValDesc should point to either an OBJECT_DESCRIPTOR of
                 * type Package, or an initialization in the AML stream.
                 */
                if ((OBJECT_DESCRIPTOR *) 0 == ValDesc)
                {
                    Why = "GetRvalue/Package:internal error: null ValPtr";
                    return S_ERROR;
                }

                if (PackageOp == *(UINT8 *) ValDesc)
                {
                    /* 
                     * The value pointer in the name table entry
                     * points to a package definition in the AML stream.
                     * Convert it to an object.
                     */

                    if (S_SUCCESS != (Excep = PushIfExec(Exec)))             /* ObjStack */
                    {
                        return Excep;
                    }

                    if (S_SUCCESS == (Excep = PushExec ((UINT8 *) ValDesc + 1, 0L))/*PkgStack*/
                        && S_SUCCESS == (Excep = DoPkg (Package, Exec))
                        && S_SUCCESS == (Excep = PopExec ()))                 /* PkgStack */
                    {
                        NsSetValue ((NsHandle)* StackPtr,
                                        ObjStack[ObjStackTop],
                                        (UINT8) Package);

                        /* Refresh local value pointer to reflect newly set value */
                        
                        ValDesc = (OBJECT_DESCRIPTOR *) NsValPtr ((NsHandle)* StackPtr);
                        --ObjStackTop;
                    }
                    
                    else
                    {
                        --ObjStackTop;
                        return Excep;
                    }
                }
                
                if (Package != ValDesc->ValType)
                {
                    Why = "GetRvalue:internal error: Bad package value";
                    return S_ERROR;
                }

                ObjDesc = NEW (OBJECT_DESCRIPTOR);
                if ((OBJECT_DESCRIPTOR *) 0 == ObjDesc)
                {
                    KFatalError ("0009", ("GetRvalue: Descriptor Allocation Failure"));
                }

                memcpy ((void *) ObjDesc, (void *) ValDesc, sizeof (*ObjDesc));
                break;

            case String:

                /* XXX - Is there a problem here if the nte points to an AML definition? */
                
                if (String != ValDesc->ValType)
                {
                    Why = "GetRvalue:internal error: Bad string value";
                    return S_ERROR;
                }

                ObjDesc = NEW (OBJECT_DESCRIPTOR);
                if ((OBJECT_DESCRIPTOR *) 0 == ObjDesc)
                {
                    KFatalError ("0010", ("GetRvalue: Descriptor Allocation Failure"));
                }

                memcpy ((void *) ObjDesc, (void *) ValDesc, sizeof (*ObjDesc));
                break;

            case Buffer:
                if (BufferOp == *(UINT8 *) ValDesc)
                {
                    /* 
                     * The value pointer in the name table entry
                     * points to a buffer definition in the AML stream.
                     * Convert it to an object.
                     */
                    if (S_SUCCESS != (Excep = PushIfExec (Exec)))                /* ObjStack */
                    {
                        return Excep;
                    }

                    if (S_SUCCESS == (Excep = PushExec ((UINT8 *) ValDesc + 1, 0L))   /*PkgStack*/
                        && S_SUCCESS == (Excep = DoPkg (Buffer, Exec))
                        && S_SUCCESS == (Excep = PopExec ()))                     /* PkgStack */
                    {
                        NsSetValue ((NsHandle) *StackPtr,
                                        ObjStack[ObjStackTop],
                                        (UINT8) Buffer);
                        
                        /* Refresh local value pointer to reflect newly set value */
                        
                        ValDesc = (OBJECT_DESCRIPTOR *) NsValPtr ((NsHandle)* StackPtr);
                        --ObjStackTop;
                    }
                    
                    else
                    {
                        --ObjStackTop;
                        return Excep;
                    }
                }
                
                if (Buffer != ValDesc->ValType)
                {
                    Why = "GetRvalue: Bad buffer value";
                    return S_ERROR;
                }

                ObjDesc = NEW (OBJECT_DESCRIPTOR);
                if ((OBJECT_DESCRIPTOR *) 0 == ObjDesc)
                {
                    KFatalError ("0011", ("GetRvalue: Descriptor Allocation Failure"));
                }

                memcpy ((void *) ObjDesc, (void *) ValDesc, sizeof (*ObjDesc));

                /* Assign a new sequence number */
                
                ObjDesc->Buffer.Sequence = AmlBufSeq();
                
                if ((Trace & TraceBufFld) && debug_level () > 0)
                {
                    fprintf_bu (LstFileHandle, LOGFILE,
                                "GetRvalue: new Buffer descriptor seq %ld @ %p ",
                                ObjDesc->Buffer.Sequence, ObjDesc);
                }

                break;

            case Number:
                if (Trace & TraceExec)
                {
                    fprintf_bu (LstFileHandle, LOGFILE, "case Number ");
                }

                if (Number == ValDesc->ValType)
                {
                    ObjDesc = NEW(OBJECT_DESCRIPTOR);
                    if ((OBJECT_DESCRIPTOR *) 0 == ObjDesc)
                    {
                        KFatalError ("0012", ("GetRvalue: Descriptor Allocation Failure"));
                    }
                    
                    memcpy ((void *) ObjDesc, (void *) ValDesc, sizeof (*ObjDesc));
                }
                
                else
                {
                    /* 
                     * nte type is Number, but it does not point to a Number,
                     * so it had better point to a Literal in the AML stream.
                     */
                    if (!IsInPCodeBlock ((UINT8 *) ValDesc))
                    {
                        Why = "GetRvalue/Number:internal error: not a Number";
                        return S_ERROR;
                    }

                    ObjDesc = NEW(OBJECT_DESCRIPTOR);
                    if ((OBJECT_DESCRIPTOR *) 0 == ObjDesc)
                    {
                        KFatalError ("0013", ("GetRvalue: Descriptor Allocation Failure"));
                    }
                    
                    switch (*(UINT8 *) ValDesc)
                    {
                        case ZeroOp:
                            ObjDesc->Number.Number = 0;
                            break;

                        case OneOp:
                            ObjDesc->Number.Number = 1;
                            break;

                        case OnesOp:
                            ObjDesc->Number.Number = 0xFFFFFFFF;
                            break;

                        case ByteOp:
                            ObjDesc->Number.Number = (UINT32)((UINT8 *) ValDesc)[1];
                            break;

                        /* 
                         * XXX - This case and DWordOp will not work properly
                         * XXX - if the processor's endianness does not match
                         * XXX - that of the AML.
                         */
                        case WordOp:
                            ObjDesc->Number.Number = (UINT32)*(UINT16 *)&((UINT8 *) ValDesc)[1];
                            break;

                        case DWordOp:
                            ObjDesc->Number.Number = *(UINT32 *)&((UINT8 *) ValDesc)[1];
                            break;

                        default:
                            DELETE (ObjDesc);
                            sprintf (WhyBuf,
                                    "GetRvalue/Number:internal error: Expected AML number, found %02x",
                                    *(UINT8 *) ValDesc);
                            Why = WhyBuf;
                            return S_ERROR;
                    }
                    ObjDesc->Number.ValType = (UINT8) Number;
                }
                break;

            case DefField:

                /* 
                 * XXX - Implementation limitation: Fields are implemented as type
                 * XXX - Number, but they really are supposed to be type Buffer.
                 * XXX - The two are interchangeable only for lengths <= 32 bits.
                 */
                Excep = GetNamedFieldValue ((NsHandle)* StackPtr, &TempVal);
                if (S_SUCCESS != Excep)
                {
                    return S_ERROR;
                }

                ObjDesc = NEW (OBJECT_DESCRIPTOR);
                if ((OBJECT_DESCRIPTOR *) 0 == ObjDesc)
                {
                    KFatalError ("0014", ("GetRvalue: Descriptor Allocation Failure"));
                }

                ObjDesc->Number.ValType = (UINT8) Number;
                ObjDesc->Number.Number = TempVal;
                break;

            case BankField:
                if (BankField != ValDesc->ValType)
                {
                    sprintf (WhyBuf,
                                "GetRvalue/BankField:internal error: Name %4.4s type %d does not match value-type %d at %p",
                                *StackPtr, BankField, ValDesc->ValType, ValDesc);
                    
                    Why = WhyBuf;
                    AmlAppendBlockOwner (ValDesc);
                    return S_ERROR;
                }

                /* Set Index value to select proper Data register */
                /* Check lock rule prior to modifing the field */
                
                if (ObjDesc->FieldUnit.LockRule == (UINT16) Lock)
                {
                    /* Lock Rule is Lock */
                    
                    if (GetGlobalLock () == S_ERROR)
                    {
                        /* the ownship failed - Bad Bad Bad, this is a single threaded */
                        /* implementation so there is no way some other process should */
                        /* own this.  This means something grabbed it and did not */
                        /* release the Global Lock! (Why will already be set) */
                        
                        return (S_ERROR);
                    }
                    
                    else
                    {
                        /* perform the update */
                        
                        Excep = SetNamedFieldValue (ValDesc->BankField.BankSelect,
                                                          ValDesc->BankField.BankVal);
                    }
                    
                    /* Release the Global Lock */
                    
                    ReleaseGlobalLock ();
                }
                
                else
                {
                    /* Lock Rule is NoLock */
                    /* perform the update */
                    
                    Excep = SetNamedFieldValue (ValDesc->BankField.BankSelect,
                                                      ValDesc->BankField.BankVal);
                }
                
                if (S_SUCCESS != Excep)
                {
                    return S_ERROR;
                }

                /* Read Data value */
                
                Excep = GetNamedFieldValue ((NsHandle) ValDesc->BankField.Container, &TempVal);
                if (S_SUCCESS != Excep)
                {
                    return S_ERROR;
                }

                ObjDesc = NEW (OBJECT_DESCRIPTOR);
                if ((OBJECT_DESCRIPTOR *) 0 == ObjDesc)
                {
                    KFatalError ("0015", ("GetRvalue: Descriptor Allocation Failure"));
                }

                ObjDesc->Number.ValType = (UINT8) Number;
                ObjDesc->Number.Number = TempVal;
                break;


            case IndexField:
                if (IndexField != ValDesc->ValType)
                {
                    sprintf (WhyBuf,
                            "GetRvalue/IndexField:internal error: Name %4.4s type %d does not match value-type %d at %p",
                            *StackPtr, IndexField, ValDesc->ValType, ValDesc);
                    
                    Why = WhyBuf;
                    AmlAppendBlockOwner (ValDesc);
                    return S_ERROR;
                }

                /* Set Index value to select proper Data register */
                /* Check lock rule prior to modifing the field */
                
                if (ObjDesc->FieldUnit.LockRule == (UINT16) Lock)
                {
                    /* Lock Rule is Lock */
                    
                    if (GetGlobalLock () == S_ERROR)
                    {
                        /* the ownship failed - Bad Bad Bad, this is a single threaded */
                        /* implementation so there is no way some other process should */
                        /* own this.  This means something grabbed it and did not */
                        /* release the Global Lock! (Why will already be set) */
                        
                        return (S_ERROR);
                    }
                    
                    else
                    {
                        /* perform the update */
                        
                        Excep = SetNamedFieldValue (ValDesc->IndexField.Index,
                                                          ValDesc->IndexField.IndexVal);
                    }
                    
                    /* Release the Global Lock */
                    
                    ReleaseGlobalLock ();
                }
                
                else
                {
                    /* Lock Rule is NoLock */
                    /* perform the update */
                    
                    Excep = SetNamedFieldValue (ValDesc->IndexField.Index,
                                                      ValDesc->IndexField.IndexVal);
                }

                if (S_SUCCESS != Excep)
                {
                    return S_ERROR;
                }

                /* Read Data value */
                
                Excep = GetNamedFieldValue (ValDesc->IndexField.Data, &TempVal);
                if (S_SUCCESS != Excep)
                {
                    return S_ERROR;
                }

                ObjDesc = NEW (OBJECT_DESCRIPTOR);
                if ((OBJECT_DESCRIPTOR *) 0 == ObjDesc)
                {
                    KFatalError("0016", ("GetRvalue: Descriptor Allocation Failure"));
                }

                ObjDesc->Number.ValType = (UINT8) Number;
                ObjDesc->Number.Number = TempVal;
                break;

            case FieldUnit:
                if (ValDesc->ValType != (UINT8) NsValType ((NsHandle)* StackPtr))
                {
                    sprintf (WhyBuf,
                            "GetRvalue/FieldUnit:internal error: Name %4.4s type %d does not match value-type %d at %p",
                              *StackPtr, NsValType ((NsHandle)* StackPtr),
                              ValDesc->ValType, ValDesc);
                    
                    Why = WhyBuf;
                    AmlAppendBlockOwner (ValDesc);
                    return S_ERROR;
                    break;
                }

                ObjDesc = NEW (OBJECT_DESCRIPTOR);
                if ((OBJECT_DESCRIPTOR *) 0 == ObjDesc)
                {
                    KFatalError ("0017", ("GetRvalue: Descriptor Allocation Failure"));
                }

                if ((Excep = GetFieldUnitValue (ValDesc, ObjDesc)) != S_SUCCESS)
                {
                    DELETE (ObjDesc);
                    return Excep;
                }

                break;

            /* cases which just return the name as the rvalue */
            
            case Device:
                return S_SUCCESS;
                break;



            case Method:        /* XXX - unimplemented, handled elsewhere */
            case Power:         /* XXX - unimplemented, may not be needed */
            case Processor:     /* XXX - unimplemented, may not be needed */
            case Thermal:       /* XXX - unimplemented, may not be needed */
            case Event:         /* XXX - unimplemented, may not be needed */
            case Mutex:         /* XXX - unimplemented, may not be needed */
            case Region:        /* XXX - unimplemented, may not be needed */

            case Any:
                if (Trace & TraceExec)
                {
                    fprintf_bu (LstFileHandle, LOGFILE, "case %s ",
                                NsTypeNames[NsValType ((NsHandle)* StackPtr)]);
                }
#ifdef HACK
                fprintf_bu (LstFileHandle, LOGFILE,
                            "** GetRvalue: Fetch from %s not implemented, using value 0",
                            NsTypeNames[NsValType ((NsHandle)* StackPtr)]);
                
                ObjDesc = NEW (OBJECT_DESCRIPTOR);
                if ((OBJECT_DESCRIPTOR *) 0 == ObjDesc)
                {
                    KFatalError ("0018", ("GetRvalue: Descriptor Allocation Failure"));
                }

                ObjDesc->Number.ValType = (UINT8) Number;
                ObjDesc->Number.Number = 0x0;
                break;
#else
                sprintf (WhyBuf,
                        "GetRvalue: Fetch from %s not implemented",
                        NsTypeNames[NsValType ((NsHandle)* StackPtr)]);
                
                Why = WhyBuf;
                return S_ERROR;
#endif /* HACK */

            default:

                if (Trace & TraceExec)
                {
                    fprintf_bu(LstFileHandle, LOGFILE, "default??? ");
                }

                sprintf (WhyBuf, "GetRvalue: Unknown NsType %d",
                        NsValType ((NsHandle)* StackPtr));
                Why = WhyBuf;
                return S_ERROR;
        }

        *StackPtr = (void *) ObjDesc;
    }

    return S_SUCCESS;
}


/*****************************************************************************
 * 
 * FUNCTION:    PrepStack
 *
 * PARAMETERS:  char *Types       String showing operand types needed
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Convert stack entries to required types
 *
 *      Each character in Types represents one required operand
 *      and indicates the required ValType:
 *          l => Lvalue, also accepts an entry which is an NsHandle
 *                  instead of an (OBJECT_DESCRIPTOR *))
 *          n => Number
 *          s => String or Buffer
 *          b => Buffer
 *          i => If
 *          p => Package
 *      The corresponding stack entry will be converted to the
 *      required type if possible, else return S_ERROR.
 *
 ****************************************************************************/

INT32
PrepStack (char *Types)
{
    OBJECT_DESCRIPTOR **    StackPtr = (OBJECT_DESCRIPTOR **) &ObjStack[ObjStackTop];
    INT32                   Excep;


    FUNCTION_TRACE ("PrepStack");


    /* 
     * Ensure room on stack for GetRvalue() to operate
     * without clobbering top existing entry.
     */

    Excep = PushIfExec (Exec);
    if (S_SUCCESS != Excep)
    {
        return Excep;
    }

    /* 
     * Normal exit is with *Types == '\0' at end of string.
     * Function will return S_ERROR from within the loop upon
     * finding an entry which is not, and cannot be converted
     * to, the required type; if stack underflows; or upon
     * finding a NULL stack entry (which "should never happen").
     */

    while (*Types)
    {
        UINT8       bTypeFound;
        char        TypeFound[30];
        char        *TypeFoundPtr;


        if ((OBJECT_DESCRIPTOR *) 0 == *StackPtr)
        {
            Why = "PrepStack:internal error: null stack entry";
            --ObjStackTop;
            return S_ERROR;
        }

        bTypeFound = (*StackPtr)->ValType;
        if (bTypeFound > (UINT8) Lvalue
            || BadType == NsTypeNames[bTypeFound])
        {
            sprintf (TypeFound, "type encoding %d", bTypeFound);
            TypeFoundPtr = TypeFound;
        }
        
        else if ((UINT8) Lvalue == bTypeFound)
        {
            strcpy (TypeFound, "Lvalue ");
            switch ((*StackPtr)->Lvalue.OpCode)
            {
                case ZeroOp:
                    strcat (TypeFound, "Zero");
                    break;
                
                case OneOp:
                    strcat (TypeFound, "One");
                    break;
                
                case OnesOp:
                    strcat (TypeFound, "Ones");
                    break;
                
                case Debug1:
                    strcat (TypeFound, "Debug");
                    break;
                case NameOp:
                
                    sprintf (&TypeFound[7], "Name");
                    break;
               
                case IndexOp:
                    sprintf (&TypeFound[7], "Index %p",
                                (*StackPtr)->Lvalue.Ref);
                    break;
                
                case Arg0: case Arg1: case Arg2: case Arg3:
                case Arg4: case Arg5: case Arg6:
                    sprintf (&TypeFound[7], "Arg%d",
                                (*StackPtr)->Lvalue.OpCode - Arg0);
                    break;
                
                case Local0: case Local1: case Local2: case Local3:
                case Local4: case Local5: case Local6: case Local7:
                    sprintf (&TypeFound[7], "Local%d",
                                (*StackPtr)->Lvalue.OpCode - Local0);
                    break;
                
                default:
                    sprintf (&TypeFound[7], "??? %02x",
                                (*StackPtr)->Lvalue.OpCode);
                    break;
            }
        }
        
        else
        {
            TypeFoundPtr = NsTypeNames[bTypeFound];
        }


        switch (*Types++)
        {
            case 'l':                                   /* need Lvalue */
                if (IsNsHandle (*StackPtr))             /* direct name ptr OK as-is */
                {
                    break;
                }

                if (Lvalue != (*StackPtr)->ValType)
                {
                    sprintf (WhyBuf, "PrepStack: Needed Lvalue, found %s",
                                TypeFoundPtr);
                    Why = WhyBuf;
                    --ObjStackTop;
                    return S_ERROR;
                }

                if (NameOp == (*StackPtr)->Lvalue.OpCode)
                {
                    /* Convert indirect name ptr to direct name ptr */
                    
                    NsHandle TempHandle = (*StackPtr)->Lvalue.Ref;
                    DELETE (*StackPtr);
                    (*StackPtr) = TempHandle;
                }
                break;

            case 'n':                                   /* need Number */
                if ((Excep = GetRvalue (StackPtr)) != S_SUCCESS)
                {
                    if (debug_level () > 0)
                    {
                        fprintf_bu (LstFileHandle, LOGFILE,
                                      "PrepStack:n: GetRvalue returned %s", RV[Excep]);
                    }

                    --ObjStackTop;
                    return Excep;
                }

                if (Trace & TraceExec)
                {
                    fprintf_bu (LstFileHandle, LOGFILE,
                                  "GetRvalue returned S_SUCCESS");
                }

                if (Number != (*StackPtr)->ValType)
                {
                    sprintf (WhyBuf, "PrepStack: Needed Number, found %s",
                                TypeFoundPtr);
                    Why = WhyBuf;
                    --ObjStackTop;
                    return S_ERROR;
                }
                break;

            case 's':                                   /* need String (or Buffer) */
                if ((Excep = GetRvalue (StackPtr)) != S_SUCCESS)
                {
                    --ObjStackTop;
                    return Excep;
                }

                if (Trace & TraceExec)
                {
                    fprintf_bu (LstFileHandle, LOGFILE,
                                  "GetRvalue returned S_SUCCESS");
                }

                if (String != (*StackPtr)->ValType
                    && Buffer != (*StackPtr)->ValType)
                {
                    sprintf (WhyBuf,
                            "PrepStack: Needed String or Buffer, found %s",
                                TypeFoundPtr);
                    Why = WhyBuf;
                    --ObjStackTop;
                    return S_ERROR;
                }
                break;

            case 'b':                                   /* need Buffer */
                if ((Excep = GetRvalue(StackPtr)) != S_SUCCESS)
                {
                    --ObjStackTop;
                    return Excep;
                }

                if (Trace & TraceExec)
                {
                    fprintf_bu(LstFileHandle, LOGFILE,
                                  "GetRvalue returned S_SUCCESS");
                }

                if (Buffer != (*StackPtr)->ValType)
                {
                    sprintf(WhyBuf, "PrepStack: Needed Buffer, found %s",
                                TypeFoundPtr);
                    Why = WhyBuf;
                    --ObjStackTop;
                    return S_ERROR;
                }
                break;

            case 'i':                                   /* need If */
                if (If != (*StackPtr)->ValType)
                {
                    sprintf (WhyBuf, "PrepStack: Needed If, found %s",
                                TypeFoundPtr);
                    Why = WhyBuf;
                    --ObjStackTop;
                    return S_ERROR;
                }
                break;

            case 'p':                                   /* need Package */
                if ((Excep = GetRvalue (StackPtr)) != S_SUCCESS)
                {
                    --ObjStackTop;
                    return Excep;
                }

                if (Trace & TraceExec)
                {
                    fprintf_bu (LstFileHandle, LOGFILE,
                                  "GetRvalue returned S_SUCCESS");
                }

                if (Package != (*StackPtr)->ValType)
                {
                    sprintf (WhyBuf, "PrepStack: Needed Package, found %s",
                                TypeFoundPtr);
                    Why = WhyBuf;
                    --ObjStackTop;
                    return S_ERROR;
                }
                break;

            default:
                sprintf (WhyBuf,
                            "PrepStack:internal error Unknown type flag %02x",
                            *--Types);
                Why = WhyBuf;
                --ObjStackTop;
                return S_ERROR;

        }   /* switch (*Types++) */


        /* 
         * If more operands needed, decrement StackPtr to point
         * to next operand on stack (after checking for underflow).
         */
        if (*Types)
        {
            /* Don't try to decrement below bottom of stack */
            
            if ((OBJECT_DESCRIPTOR **) &ObjStack[0] == StackPtr)
            {
                Why = "PrepStack: not enough operands";
                --ObjStackTop;
                return S_ERROR;
            }

            --StackPtr;
        }

    }   /* while (*Types) */

    --ObjStackTop;
    return S_SUCCESS;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlAppendOperandDiag
 *
 * PARAMETERS:  char *  FileName    Name of source file
 *              INT32   LineNum     Line Number in file
 *              UINT16  OpCode      OpCode being executed
 *              INT32   NumOperands Number of operands PrepStack tried to check
 *
 * DESCRIPTION: Append diagnostic information about operands to WhyBuf
 *              This function is intended to be called after PrepStack
 *              has returned S_ERROR.
 *
 ****************************************************************************/

void
AmlAppendOperandDiag(char *FileName, INT32 LineNum, UINT16 OpCode, INT32 NumOperands)
{
    meth            sM;


    if (Why != WhyBuf)
    {
        /* Copy message to WhyBuf */
        
        strcpy (WhyBuf, Why);
        Why = WhyBuf;
    }

    GetCurrentLoc (&sM);

    sprintf (&WhyBuf[strlen (WhyBuf)], " [%s:%d, opcode = %s AML offset %04x]",
            FileName, LineNum,
            (OpCode > UCHAR_MAX)
                ? LongOps[OpCode & 0x00ff]
                : ShortOps[OpCode],
            sM.Offset);

    if (debug_level () > 0)
    {
        INT32       iTraceWas = Trace;

        /* Turn on TraceExec to enable output from DumpStack() */
        
        Trace |= TraceExec;

        DumpStack (Exec,
                      (OpCode > UCHAR_MAX)
                      ? LongOps[OpCode & 0x00ff]
                      : ShortOps[OpCode],
                      NumOperands,
                      "after PrepStack failed");
        Trace = iTraceWas;
    }
}


/*****************************************************************************
 * 
 * FUNCTION:    ExecMonadic1
 *
 * PARAMETERS:  UINT16  opcode      The opcode to be executed
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Execute Type 1 monadic operator
 *              with numeric operand on object stack
 *
 * ALLOCATION:  Deletes the operand
 *
 ****************************************************************************/

INT32
ExecMonadic1 (UINT16 opcode)
{
    OBJECT_DESCRIPTOR *     ObjDesc;
    INT32                   Excep;


    FUNCTION_TRACE ("ExecMonadic1");


    if (SleepOp == opcode || StallOp == opcode)
    {
        Excep = PrepStack ("n");                 /* operand should be a Number */
    }
    else
    {
        Excep = PrepStack ("l");                 /* operand should be an Lvalue */
    }

    if (Excep != S_SUCCESS)
    {
        AmlAppendOperandDiag (__FILE__, __LINE__, opcode, 1);
        return Excep;
    }


    DumpStack (Exec, LongOps[opcode & 0x00ff], 1, "after PrepStack");

    ObjDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];

    switch (opcode)
    {
        case ReleaseOp:
            if (Mutex != ObjDesc->ValType)
            {
                sprintf (WhyBuf,
                        "ExecMonadic1/ReleaseOp: Needed Mutex, found %d",
                        ObjDesc->ValType);
                Why = WhyBuf;
                return S_ERROR;
            }

            return (ReleaseOpRqst (ObjDesc));

        case ResetOp:
            if (Event != ObjDesc->ValType)
            {
                sprintf (WhyBuf,
                        "ExecMonadic1/ResetOp: Needed Event, found %d", ObjDesc->ValType);
                Why = WhyBuf;
                return S_ERROR;
            }

            return (ResetOpRqst (ObjDesc));

        case SignalOp:
            if (Event != ObjDesc->ValType)
            {
                sprintf (WhyBuf,
                        "ExecMonadic1/SignalOp: Needed Event, found %d", ObjDesc->ValType);
                Why = WhyBuf;
                return S_ERROR;
            }
            return (SignalOpRqst (ObjDesc));

        case SleepOp:
#ifndef RMX
            DoSuspend (ObjDesc->Number.Number);
            break;
#else
            Why = "ExecMonadic1: SleepOp not implemented on RMX";
            return S_ERROR;
#endif

        case StallOp:
#ifndef RMX
            OsdSleepUsec (ObjDesc->Number.Number);
            break;
#else
            /* 
             * XXX - this is supposed to NOT yield the processor, so should
             * XXX - busy-wait.  RMX has no corresponding service.
             */
            Why = "ExecMonadic1: StallOp not implemented on RMX";
            return S_ERROR;
#endif

        default:
            sprintf (WhyBuf, "ExecMonadic1: Unknown monadic opcode %02x", opcode);
            Why = WhyBuf;
            return S_ERROR;
    }

    DELETE (ObjDesc);
    return S_SUCCESS;
}


/*****************************************************************************
 * 
 * FUNCTION:    ExecMonadic2R
 *
 * PARAMETERS:  UINT16  opcode      The opcode to be executed
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Execute Type 2 monadic operator with numeric operand and
 *              result operand on operand stack
 *
 ****************************************************************************/

INT32
ExecMonadic2R (UINT16 opcode)
{
    OBJECT_DESCRIPTOR       *ObjDesc;
    OBJECT_DESCRIPTOR       *ResDesc;
    UINT32                  ResVal;
    INT32                   Excep;


    FUNCTION_TRACE ("ExecMonadic2R");


    Excep = PrepStack ("ln");

    if (Excep != S_SUCCESS)
    {
        /* This was added since it is allowable to return a buffer so */
        /* ln is a local and a number and that will fail.  lb is a local */
        /* and a buffer which will pass.  */
        
        Excep = PrepStack ("lb");

        if (Excep != S_SUCCESS)
        {
            AmlAppendOperandDiag (__FILE__, __LINE__, opcode, 2);
            return Excep;
        }
    }

    DumpStack (Exec, ShortOps[opcode], 2, "after PrepStack");

    ResDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];
    ObjDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 1];

    switch (opcode)
    {
        INT32           d0, d1, d2, d3;


        case BitNotOp:
            ObjDesc->Number.Number = ~ObjDesc->Number.Number;
            break;

        case FindSetLeftBitOp:
            for (ResVal = 0; ObjDesc->Number.Number && ResVal < 33; ++ResVal)
            {
                ObjDesc->Number.Number >>= 1;
            }

            ObjDesc->Number.Number = ResVal;
            break;

        case FindSetRightBitOp:
            for (ResVal = 0; ObjDesc->Number.Number && ResVal < 33; ++ResVal)
            {
                ObjDesc->Number.Number <<= 1;
            }

            ObjDesc->Number.Number = ResVal == 0 ? 0 : 33 - ResVal;
            break;

        case FromBCDOp:
            d0 = (INT32) (ObjDesc->Number.Number & 15);
            d1 = (INT32) (ObjDesc->Number.Number >> 4 & 15);
            d2 = (INT32) (ObjDesc->Number.Number >> 8 & 15);
            d3 = (INT32) (ObjDesc->Number.Number >> 12 & 15);
            
            if (d0 > 9 || d1 > 9 || d2 > 9 || d3 > 9)
            {
                sprintf (WhyBuf,
                        "ExecMonadic2R/FromBCDOp: improper BCD digit %d %d %d %d",
                        d3, d2, d1, d0);
                Why = WhyBuf;
                return S_ERROR;
            }
            
            ObjDesc->Number.Number = d0 + d1 * 10 + d2 * 100 + d3 * 1000;
            break;

        case ToBCDOp:
            if (ObjDesc->Number.Number > 9999)
            {
                Why = "ExecMonadic2R/ToBCDOp: BCD overflow";
                return S_ERROR;
            }
            
            ObjDesc->Number.Number
                = ObjDesc->Number.Number % 10
                + (ObjDesc->Number.Number / 10 % 10 << 4)
                + (ObjDesc->Number.Number / 100 % 10 << 8)
                + (ObjDesc->Number.Number / 1000 % 10 << 12);
            
            break;

        case ShiftLeftBitOp:
        case ShiftRightBitOp:
        case CondRefOfOp:
            
            sprintf (WhyBuf, "ExecMonadic2R: %s unimplemented",
                    (opcode > UCHAR_MAX) ? LongOps[opcode & 0x00ff] : ShortOps[opcode]);
            Why = WhyBuf;
            return S_ERROR;

        case StoreOp:
            break;

        default:
            sprintf (WhyBuf, "ExecMonadic2R:internal error: Unknown monadic opcode %02x", opcode);
            Why = WhyBuf;
            return S_ERROR;
    }
    
    Excep = ExecStore (ObjDesc, ResDesc);
    --ObjStackTop;
    
    return Excep;
}


/*****************************************************************************
 * 
 * FUNCTION:    ExecMonadic2
 *
 * PARAMETERS:  UINT16  opcode      The opcode to be executed
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Execute Type 2 monadic operator with numeric operand:
 *              DerefOfOp, RefOfOp, SizeOfOp, TypeOp, IncrementOp,
 *              DecrementOp, LNotOp,
 *
 * ALLOCATION:
 *  Reference   Size                    Pool    Owner       Description
 *  ObjStack    s(OBJECT_DESCRIPTOR)    bu      amlexec     Number
 *
 ****************************************************************************/

INT32
ExecMonadic2 (UINT16 opcode)
{
    OBJECT_DESCRIPTOR       *ObjDesc;
    OBJECT_DESCRIPTOR       *ResDesc;
    INT32                   Excep;


    FUNCTION_TRACE ("ExecMonadic2");


    if (LNotOp == opcode)
    {
        Excep = PrepStack ("n");
    }
    else
    {
        Excep = PrepStack ("l");
    }

    if (Excep != S_SUCCESS)
    {
        AmlAppendOperandDiag (__FILE__, __LINE__, opcode, 1);
        return Excep;
    }

    DumpStack (Exec, ShortOps[opcode], 1, "after PrepStack");

    ObjDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];


    switch (opcode)
    {
        case LNotOp:
            ObjDesc->Number.Number = (!ObjDesc->Number.Number) - (UINT32) 1;
            break;

        case DecrementOp:
        case IncrementOp:

            if ((Excep = PushIfExec (Exec)) != S_SUCCESS)
            {
                KFatalError("0019", ("ExecMonadic2/IncDec: stack overflow"));
            }

            /* duplicate the Lvalue on TOS */
            
            ResDesc = NEW (OBJECT_DESCRIPTOR);
            if (ResDesc)
            {
                memcpy ((void *) ResDesc, (void *) ObjDesc, sizeof (*ObjDesc));
                
                /* push went into unused space, so no need to DeleteObject() */
                
                ObjStack[ObjStackTop] = (void *) ResDesc;
            }
            
            else
            {
                KFatalError ("0020", ("ExecMonadic2/IncDec: Descriptor Allocation Failure"));
                return S_ERROR;
            }

            /* Convert the top copy to a Number */
            
            Excep = PrepStack ("n");
            if (Excep != S_SUCCESS)
            {
                AmlAppendOperandDiag (__FILE__, __LINE__, opcode, 1);
                return Excep;
            }

            /* get the Number in ObjDesc and the Lvalue in ResDesc */
            
            ObjDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];
            ResDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 1];

            /* do the ++ or -- */
            
            if (IncrementOp == opcode)
            {
                ++ObjDesc->Number.Number;
            }
            else
            {
                --ObjDesc->Number.Number;
            }

            /* store result */
            
            DeleteObject ((OBJECT_DESCRIPTOR **) &ObjStack[ObjStackTop - 1]);
            ObjStack[ObjStackTop - 1] = (void *) ObjDesc;
            
            Excep = ExecStore (ObjDesc, ResDesc);
            --ObjStackTop;
            return Excep;

        case TypeOp:
            
            /* This case uses Excep to hold the type encoding */
            
            if (Lvalue == ObjDesc->ValType)
            {
                /* 
                 * Not a Name -- an indirect name pointer would have
                 * been converted to a direct name pointer in PrepStack
                 */
                switch (ObjDesc->Lvalue.OpCode)
                {
                case ZeroOp: case OneOp: case OnesOp:
                    
                    /* Constants are of type Number */
                    
                    Excep = (INT32) Number;
                    break;

                case Debug1:
                    
                    /* Per spec, Debug object is of type Region */
                    
                    Excep = (INT32) Region;
                    break;

                case IndexOp:
                    
                    Why = "ExecMonadic2/TypeOp: determining type of Index result is not implemented";
                    return S_ERROR;

                case Local0: case Local1: case Local2: case Local3:
                case Local4: case Local5: case Local6: case Local7:
                    
                    Excep = (INT32) GetMethodValTyp (LCLBASE + ObjDesc->Lvalue.OpCode - Local0);
                    break;

                case Arg0: case Arg1: case Arg2: case Arg3:
                case Arg4: case Arg5: case Arg6:
                    
                    Excep = (INT32) GetMethodValTyp (ARGBASE + ObjDesc->Lvalue.OpCode - Arg0);
                    break;

                default:
                    
                    sprintf (WhyBuf,
                            "ExecMonadic2/TypeOp:internal error: Unknown Lvalue subtype %02x",
                            ObjDesc->Lvalue.OpCode);
                    return S_ERROR;
                }
            }
            
            else
            {
                /* 
                 * Since we passed PrepStack("l") and it's not an Lvalue,
                 * it must be a direct name pointer.  Allocate a descriptor
                 * to hold the type.
                 */
                Excep = (INT32) NsValType ((NsHandle) ObjDesc);
                ObjDesc = NEW (OBJECT_DESCRIPTOR);
                if ((OBJECT_DESCRIPTOR *) 0 == ObjDesc)
                {
                    KFatalError ("0021", ("ExecMonadic2/TypeOp: Descriptor Allocation Failure"));
                    return S_ERROR;
                }

                /* 
                 * Replace (NsHandle) on TOS with descriptor containing result.
                 * No need to DeleteObject() first since TOS is an NsHandle.
                 */

                ObjStack[ObjStackTop] = (void *) ObjDesc;
            }
            
            ObjDesc->ValType = (UINT8) Number;
            ObjDesc->Number.Number = (UINT32)(INT32) Excep;
            break;

        case SizeOfOp:
            switch (ObjDesc->ValType)
            {
                case Buffer:
                    ObjDesc->Number.Number = ObjDesc->Buffer.BufLen;
                    ObjDesc->ValType = (UINT8) Number;
                    break;

                case String:
                    ObjDesc->Number.Number = ObjDesc->String.StrLen;
                    ObjDesc->ValType = (UINT8) Number;
                    break;

                case Package:
                    ObjDesc->Number.Number = ObjDesc->Package.PkgCount;
                    ObjDesc->ValType = (UINT8) Number;
                    break;

                default:
                    sprintf (WhyBuf,
                            "ExecMonadic2: Needed aggregate, found %d", ObjDesc->ValType);
                    Why = WhyBuf;
                    return S_ERROR;
            }
            break;

        case RefOfOp:
        case DerefOfOp:
            sprintf (WhyBuf, "ExecMonadic2: %s unimplemented",
                    (opcode > UCHAR_MAX) ? LongOps[opcode & 0x00ff] : ShortOps[opcode]);
            Why = WhyBuf;
            ++ObjStackTop;
            return S_ERROR;

        default:
            sprintf (WhyBuf,
                        "ExecMonadic2:internal error: Unknown monadic opcode %02x",
                        opcode);
            Why = WhyBuf;
            return S_ERROR;
    }

    return S_SUCCESS;
}


/*****************************************************************************
 * 
 * FUNCTION:    ExecDyadic1
 *
 * PARAMETERS:  UINT16 opcode  The opcode to be executed
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Execute Type 1 dyadic operator with numeric operands:
 *              NotifyOp
 *
 * ALLOCATION:  Deletes both operands
 *
 ****************************************************************************/

INT32
ExecDyadic1 (UINT16 opcode)
{
    OBJECT_DESCRIPTOR       *ObjDesc;
    OBJECT_DESCRIPTOR       *ValDesc;
    INT32                   Excep;


    FUNCTION_TRACE ("ExecDyadic1");


    Excep = PrepStack ("nl");

    if (Excep != S_SUCCESS)
    {
        AmlAppendOperandDiag (__FILE__, __LINE__, opcode, 2);
        return Excep;
    }

    DumpStack (Exec, ShortOps[opcode], 2, "after PrepStack");

    ValDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];
    ObjDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 1];

    switch (opcode)
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

            switch (ObjDesc->ValType)
            {
                case Device:
                case Thermal:
                    
                    /* XXX - Requires that sDevice and sThermalZone
                     * XXX - be compatible mappings
                     */

                    DoNotifyOp (ValDesc, ObjDesc);
                    break;

                default:
                    sprintf (WhyBuf,
                            "ExecDyadic1/NotifyOp: unexpected object type %d",
                            ObjDesc->ValType);
                    Why = WhyBuf;
                    return S_ERROR;
            }
            break;

        default:
            sprintf (WhyBuf, "ExecDyadic1: Unknown dyadic opcode %02x", opcode);
            Why = WhyBuf;
            return S_ERROR;
    }

    DELETE (ValDesc);
    DELETE (ObjDesc);
    ObjStack[--ObjStackTop] = (void *) 0;

    return S_SUCCESS;
}


/*****************************************************************************
 * 
 * FUNCTION:    ExecDyadic2R
 *
 * PARAMETERS:  UINT16  opcode      The opcode to be executed
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Execute Type 2 dyadic operator with numeric operands and
 *              one or two result operands
 *
 * ALLOCATION:  Deletes one operand descriptor -- other remains on stack
 *  Reference       Size        Pool    Owner   Description
 *  String.String varies     bu    amlexec   result of Concat
 *  Buffer.Buffer varies     bu    amlexec   result of Concat
 *
 ****************************************************************************/

INT32
ExecDyadic2R (UINT16 opcode)
{
    OBJECT_DESCRIPTOR       *ObjDesc;
    OBJECT_DESCRIPTOR       *ObjDesc2;
    OBJECT_DESCRIPTOR       *ResDesc;
    OBJECT_DESCRIPTOR       *ResDesc2;
    UINT32                  remain;
    INT32                   Excep;
    INT32                   NumOperands;


    FUNCTION_TRACE ("ExecDyadic2R");


    switch (opcode)
    {
        case ConcatOp:
            Excep = PrepStack ("lss");
            NumOperands = 3;
            break;

        case DivideOp:
            Excep = PrepStack ("llnn");
            NumOperands = 4;
            break;

        default:
            Excep = PrepStack ("lnn");
            NumOperands = 3;
            break;
    }

    if (Excep != S_SUCCESS)
    {
        AmlAppendOperandDiag (__FILE__, __LINE__, opcode, NumOperands);
        return Excep;
    }

    DumpStack (Exec, ShortOps[opcode], NumOperands, "after PrepStack");

    if (DivideOp == opcode)
    {
        ResDesc2 = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop--];
    }

    ResDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop--];
    ObjDesc2 = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop--];
    ObjDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];
    ObjStackTop += NumOperands - 1;

    switch (opcode)
    {
        case AddOp:
            ObjDesc->Number.Number += ObjDesc2->Number.Number;
            break;
        
        case BitAndOp:
            ObjDesc->Number.Number &= ObjDesc2->Number.Number;
            break;
        
        case BitNandOp:
            ObjDesc->Number.Number = ~(ObjDesc->Number.Number & ObjDesc2->Number.Number);
            break;
        
        case BitOrOp:
            ObjDesc->Number.Number |= ObjDesc2->Number.Number;
            break;
        
        case BitNorOp:
            ObjDesc->Number.Number = ~(ObjDesc->Number.Number | ObjDesc2->Number.Number);
            break;
        
        case BitXorOp:
            ObjDesc->Number.Number ^= ObjDesc2->Number.Number;
            break;
        
        case DivideOp:
            if ((UINT32) 0 == ObjDesc2->Number.Number)
            {
                Why = "ExecDyadic2R/DivideOp: divide by zero";
                return S_ERROR;
            }

            remain = ObjDesc->Number.Number % ObjDesc2->Number.Number;
            ObjDesc->Number.Number /= ObjDesc2->Number.Number;
            ObjDesc2->Number.Number = remain;
            break;
        
        case MultiplyOp:
            ObjDesc->Number.Number *= ObjDesc2->Number.Number;
            break;
        
        case ShiftLeftOp:
            ObjDesc->Number.Number <<= ObjDesc2->Number.Number;
            break;
        
        case ShiftRightOp:
            ObjDesc->Number.Number >>= ObjDesc2->Number.Number;
            break;
        
        case SubtractOp:
            ObjDesc->Number.Number -= ObjDesc2->Number.Number;
            break;

        case ConcatOp:
            if (ObjDesc2->ValType != ObjDesc->ValType)
            {
                sprintf (WhyBuf,
                        "ExecDyadic2R/ConcatOp: operand type mismatch %d %d",
                        ObjDesc->ValType, ObjDesc2->ValType);
                Why = WhyBuf;
                return S_ERROR;
            }

            /* Both ValType are now known to be the same */
            
            if (String == ObjDesc->ValType)
            {
                char *NewBuf = OsdAllocate ((size_t) (ObjDesc->String.StrLen
                                                    + ObjDesc2->String.StrLen + 1));
                if ((char *) 0 == NewBuf)
                {
                    KFatalError ("0022", 
                        "ExecDyadic2R/ConcatOp: String allocation failure %d",
                        ObjDesc->String.StrLen + ObjDesc2->String.StrLen + 1);
                    
                    Why = WhyBuf;
                    return S_ERROR;
                }
                
                strcpy (NewBuf, (char *) ObjDesc->String.String);
                strcpy (NewBuf + ObjDesc->String.StrLen,
                         (char *) ObjDesc2->String.String);
                
                /* Don't free old ObjDesc->String.String; the operand still exists */
                
                ObjDesc->String.String = (UINT8 *) NewBuf;
                ObjDesc->String.StrLen += ObjDesc2->String.StrLen;
            }
            
            else
            {
                char *NewBuf = OsdAllocate ((size_t) (ObjDesc->Buffer.BufLen
                                                    + ObjDesc2->Buffer.BufLen));
                if ((char *) 0 == NewBuf)
                {
                    /* Only bail out if the buffer is small */
                    
                    if (ObjDesc->Buffer.BufLen + ObjDesc2->Buffer.BufLen < 1024)
                    {
                        KFatalError ("0023", 
                                "ExecDyadic2R/ConcatOp: Buffer allocation failure %d",
                                ObjDesc->Buffer.BufLen + ObjDesc2->Buffer.BufLen);
                    }

                    sprintf (WhyBuf,
                                "ExecDyadic2R/ConcatOp: Buffer allocation failure %d",
                                ObjDesc->Buffer.BufLen + ObjDesc2->Buffer.BufLen);
                    Why = WhyBuf;
                    return S_ERROR;
                }

                memcpy (NewBuf, ObjDesc->Buffer.Buffer, (size_t) ObjDesc->Buffer.BufLen);
                memcpy (NewBuf + ObjDesc->Buffer.BufLen, ObjDesc2->Buffer.Buffer,
                        (size_t) ObjDesc2->Buffer.BufLen);
                
                /* Don't free old ObjDesc->Buffer.Buffer; the operand still exists */
                
                ObjDesc->Buffer.Buffer = (UINT8 *) NewBuf;
                ObjDesc->Buffer.BufLen += ObjDesc2->Buffer.BufLen;
            }
            break;

        default:
            sprintf (WhyBuf, "ExecDyadic2R: Unknown dyadic opcode %02x", opcode);
            Why = WhyBuf;
            return S_ERROR;
    }
    
    if ((Excep = ExecStore (ObjDesc, ResDesc)) != S_SUCCESS)
    {
        ObjStackTop -= NumOperands - 1;
        return Excep;
    }
    
    if (DivideOp == opcode)
    {
        Excep = ExecStore(ObjDesc2, ResDesc2);
    }

    /* Don't delete ObjDesc because it remains on the stack */
    
    DELETE (ObjDesc2);
    ObjStackTop -= NumOperands - 1;
    
    return Excep;
}


/*****************************************************************************
 * 
 * FUNCTION:    ExecDyadic2S
 *
 * PARAMETERS:  UINT16  opcode      The opcode to be executed
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Execute Type 2 dyadic synchronization operator
 *
 * ALLOCATION:  Deletes one operand descriptor -- other remains on stack
 *
 ****************************************************************************/

INT32
ExecDyadic2S (UINT16 opcode)
{
    OBJECT_DESCRIPTOR       *ObjDesc;
    OBJECT_DESCRIPTOR       *TimeDesc;
    OBJECT_DESCRIPTOR       *ResDesc;
    INT32                   Excep;


    FUNCTION_TRACE ("ExecDyadic2S");


    Excep = PrepStack ("nl");

    if (Excep != S_SUCCESS)
    {
        AmlAppendOperandDiag (__FILE__, __LINE__, opcode, 2);
        return Excep;
    }

    DumpStack (Exec, LongOps[opcode & 0x00ff], 2, "after PrepStack");

    TimeDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];
    ObjDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 1];

    switch (opcode)
    {
        case AcquireOp:
            if (Mutex != ObjDesc->ValType)
            {
                sprintf (WhyBuf,
                        "ExecDyadic2S/AcquireOp: Needed Mutex, found %d",
                        ResDesc->ValType);
                Why = WhyBuf;
                return S_ERROR;
            }
            return (AcquireOpRqst (TimeDesc, ObjDesc));


        case WaitOp:
            if (Event != ObjDesc->ValType)
            {
                sprintf (WhyBuf,
                        "ExecDyadic2S/WaitOp: Needed Event, found %d",
                        ResDesc->ValType);
                Why = WhyBuf;
                return S_ERROR;
            }
            return (WaitOpRqst (TimeDesc, ObjDesc));


        default:
            sprintf (WhyBuf,
                    "ExecDyadic2S: Unknown dyadic synchronization opcode %02x",
                    opcode);
            Why = WhyBuf;
            return S_ERROR;
    }

    /* This will become reachable when Acquire or Wait is implemented */
    
    DELETE (TimeDesc);
    --ObjStackTop;
    
    return Excep;
}


/*****************************************************************************
 * 
 * FUNCTION:    ExecDyadic2
 *
 * PARAMETERS:  UINT16  opcode      The opcode to be executed
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Execute Type 2 dyadic operator with numeric operands and
 *              no result operands
 *
 * ALLOCATION:  Deletes one operand descriptor -- other remains on stack
 *              containing result value
 *
 ****************************************************************************/

INT32
ExecDyadic2 (UINT16 opcode)
{
    OBJECT_DESCRIPTOR       *ObjDesc;
    OBJECT_DESCRIPTOR       *ObjDesc2;
    INT32                   Excep;


    FUNCTION_TRACE ("ExecDyadic2");


    Excep = PrepStack ("nn");

    if (Excep != S_SUCCESS)
    {
        AmlAppendOperandDiag (__FILE__, __LINE__, opcode, 2);
        return Excep;
    }

    DumpStack (Exec, ShortOps[opcode], 2, "after PrepStack");

    ObjDesc2 = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];
    ObjDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 1];

    switch (opcode)
    {
        case LAndOp:
            if (ObjDesc->Number.Number && ObjDesc2->Number.Number)
                Excep = 1;
            else
                Excep = 0;
            break;

        case LEqualOp:
            if (ObjDesc->Number.Number == ObjDesc2->Number.Number)
                Excep = 1;
            else
                Excep = 0;
            break;

        case LGreaterOp:
            if (ObjDesc->Number.Number > ObjDesc2->Number.Number)
                Excep = 1;
            else
                Excep = 0;
            break;

        case LLessOp:
            if (ObjDesc->Number.Number < ObjDesc2->Number.Number)
                Excep = 1;
            else
                Excep = 0;
            break;

        case LOrOp:
            if (ObjDesc->Number.Number || ObjDesc2->Number.Number)
                Excep = 1;
            else
                Excep = 0;
            break;
        
        default:
            sprintf (WhyBuf, "ExecDyadic2: Unknown dyadic opcode %02x", opcode);
            Why = WhyBuf;
            return S_ERROR;
    }

    /* ObjDesc->ValType == Number was assured by PrepStack("nn") call */
    
    if (Excep)
    {
        ObjDesc->Number.Number = 0xffffffff;
    }
    else
    {
        ObjDesc->Number.Number = 0;
    }

    DELETE (ObjDesc2);
    --ObjStackTop;
    
    return S_SUCCESS;
}


/*****************************************************************************
 * 
 * FUNCTION:    ExecCreateField
 *
 * PARAMETERS:  UINT16  opcode      The opcode to be executed
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Execute CreateField operators: CreateBitFieldOp,
 *              CreateByteFieldOp, CreateWordFieldOp, CreateDWordFieldOp,
 *              CreateFieldOp (which define fields in buffers)
 *
 * ALLOCATION:  Deletes CreateFieldOp's count operand descriptor
 *
 ****************************************************************************/

INT32
ExecCreateField (UINT16 opcode)
{
    OBJECT_DESCRIPTOR       *ResDesc;
    OBJECT_DESCRIPTOR       *CntDesc;
    OBJECT_DESCRIPTOR       *OffDesc;
    OBJECT_DESCRIPTOR       *SrcDesc;
    char                    *OpName;
    INT32                   NumOperands;
    UINT16                  BitCount;
    UINT32                  BitOffset;
    INT32                   Excep;


    FUNCTION_TRACE ("ExecCreateField");


    if (CreateFieldOp == opcode)
    {
        Excep = PrepStack ("lnnb");
        NumOperands = 4;
        OpName = LongOps[opcode & 0x00ff];
    }
    
    else
    {
        Excep = PrepStack ("lnb");
        NumOperands = 3;
        OpName = ShortOps[opcode];
    }

    if (Excep != S_SUCCESS)
    {
        AmlAppendOperandDiag (__FILE__, __LINE__, opcode, NumOperands);
        return Excep;
    }

    DumpStack (Exec, OpName, NumOperands, "after PrepStack");

    ResDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop--];        /* result */
    
    if (CreateFieldOp == opcode)
    {
        CntDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop--];        /* count */
    }

    OffDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop--];        /* offset */
    SrcDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];          /* source */
    ObjStackTop += NumOperands - 1;

    /* If ResDesc is a Name, it will be a direct name pointer after PrepStack() */
    
    if (!IsNsHandle (ResDesc))
    {
        sprintf (WhyBuf, "%s: destination must be a Name", OpName);
        Why = WhyBuf;
        return S_ERROR;
    }

    switch (opcode)
    {
        case BitFieldOp:
            BitOffset = OffDesc->Number.Number;             /* offset is in bits */
            BitCount = 1;                                   /* field is a bit */
            break;

        case ByteFieldOp:
            BitOffset = 8 * OffDesc->Number.Number;         /* offset is in bytes */
            BitCount = 8;                                   /* field is a Byte */
            break;

        case WordFieldOp:
            BitOffset = 8 * OffDesc->Number.Number;         /* offset is in bytes */
            BitCount = 16;                                  /* field is a Word */
            break;

        case DWordFieldOp:
            BitOffset = 8 * OffDesc->Number.Number;         /* offset is in bytes */
            BitCount = 32;                                  /* field is a DWord */
            break;

        case CreateFieldOp:
            BitOffset = OffDesc->Number.Number;             /* offset is in bits */
            BitCount = (UINT16) CntDesc->Number.Number;       /* as is count */
            break;

        default:
            sprintf (WhyBuf,
                    "ExecCreateField:internal error: Unknown field creation opcode %02x",
                    opcode);
            Why = WhyBuf;
            return S_ERROR;
    }

    switch (SrcDesc->ValType)
    {
        UINT8       bTypeFound;
        char        TypeFound[20];
        char        *TypeFoundPtr;

    case Buffer:
        if (BitOffset + (UINT32) BitCount > 8 * (UINT32) SrcDesc->Buffer.BufLen)
        {
            sprintf (WhyBuf, "ExecCreateField: Field exceeds Buffer %d > %d",
                    BitOffset + (UINT32)BitCount,
                    8 * (UINT32)SrcDesc->Buffer.BufLen);
            Why = WhyBuf;
            return S_ERROR;
        }

        /* Reuse "OffDesc" descriptor to build result */
        
        OffDesc->ValType                = (UINT8) FieldUnit;
        OffDesc->FieldUnit.Access       = (UINT16) AnyAcc;
        OffDesc->FieldUnit.LockRule     = (UINT16) NoLock;
        OffDesc->FieldUnit.UpdateRule   = (UINT16) Preserve;
        OffDesc->FieldUnit.DatLen       = BitCount;
        OffDesc->FieldUnit.BitOffset    = (UINT16) BitOffset % 8;
        OffDesc->FieldUnit.Offset       = BitOffset / 8;
        OffDesc->FieldUnit.Container    = SrcDesc;
        OffDesc->FieldUnit.ConSeq       = SrcDesc->Buffer.Sequence;
        break;

    default:
        bTypeFound = SrcDesc->ValType;

        if (bTypeFound > (UINT8) Lvalue
            || BadType == NsTypeNames[bTypeFound])
        {
            sprintf (TypeFound, "encoding %d", bTypeFound);
            TypeFoundPtr = TypeFound;
        }
        else
        {
            TypeFoundPtr = NsTypeNames[bTypeFound];
        }

        sprintf (WhyBuf,
                "ExecCreateField: Tried to create field in improper object type %s",
                TypeFoundPtr);
        Why = WhyBuf;
        return S_ERROR;
    }

    if (CreateFieldOp == opcode)
    {
        DELETE (CntDesc);
    }

    /* 
     * This operation is supposed to cause the destination Name to refer
     * to the defined FieldUnit -- it must not store the constructed
     * FieldUnit object (or its current value) in some location that the
     * Name may already be pointing to.  So, if the Name currently contains
     * a reference which would cause ExecStore() to perform an indirect
     * store rather than setting the value of the Name itself, clobber that
     * reference before calling ExecStore().
     */

    switch (NsValType (ResDesc))                /* Type of Name's existing value */
    {
        case Alias:
        case BankField:
        case DefField:
        case FieldUnit:
        case IndexField:

            if ((Trace & TraceBufFld) && debug_level () > 0)
            {
                printf_bu ("ExecCreateField: clobber %s (%p) ",
                             NsFullyQualifiedName (ResDesc), ResDesc);

                NsDumpEntry (ResDesc, SCREEN|LOGFILE);
                DumpStackEntry (NsValPtr (ResDesc));
            }
            
            NsSetValue (ResDesc, NULL, Any);
            break;

        default:
            break;
    }

    /* Store constructed field descriptor in result location */
    
    Excep = ExecStore (OffDesc, ResDesc);
    ObjStackTop -= NumOperands - 1;
    
    return Excep;
}


/*****************************************************************************
 * 
 * FUNCTION:    ExecFatal
 *
 * PARAMETERS:  none
 *
 * RETURN:      S_ERROR
 *
 * DESCRIPTION: Execute Fatal operator
 *
 ****************************************************************************/

INT32
ExecFatal (void)
{
    OBJECT_DESCRIPTOR       *TypeDesc;
    OBJECT_DESCRIPTOR       *CodeDesc;
    OBJECT_DESCRIPTOR       *ArgDesc;
    INT32                   Excep;


    FUNCTION_TRACE ("ExecFatal");


    Excep = PrepStack ("nnn");

    if (Excep != S_SUCCESS)
    {
        AmlAppendOperandDiag (__FILE__, __LINE__, (UINT16) FatalOp, 3);
        return Excep;
    }

    DumpStack (Exec, LongOps[FatalOp & 0x00ff], 3, "after PrepStack");

    ArgDesc  = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];
    CodeDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 1];
    TypeDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 2];

    fprintf_bu (LstFileHandle, LOGFILE,
                "FatalOp: Type %x Code %x Arg %x <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<",
                TypeDesc->Number.Number, CodeDesc->Number.Number,
                ArgDesc->Number.Number);

    Why = "ExecFatal: FatalOp executed";
    return S_ERROR;
}


/*****************************************************************************
 * 
 * FUNCTION:    ExecIndex
 *
 * PARAMETERS:  none
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Execute Index operator
 *
 * ALLOCATION:  Deletes one operand descriptor -- other remains on stack
 *
 ****************************************************************************/

INT32
ExecIndex (void)
{
    OBJECT_DESCRIPTOR       *PkgDesc;
    OBJECT_DESCRIPTOR       *IdxDesc;
    OBJECT_DESCRIPTOR       *ResDesc;
    INT32                   Excep;


    FUNCTION_TRACE ("ExecIndex");


    Excep = PrepStack ("lnp");

    if (Excep != S_SUCCESS)
    {
        AmlAppendOperandDiag (__FILE__, __LINE__, (UINT16)IndexOp, 3);
        return Excep;
    }

    DumpStack (Exec, ShortOps[IndexOp], 3, "after PrepStack");

    ResDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];
    IdxDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 1];
    PkgDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 2];

    if (IdxDesc->Number.Number < 0
        || IdxDesc->Number.Number >= (UINT32) PkgDesc->Package.PkgCount)
    {
        Why = "ExecIndex: Index value out of range";
        return S_ERROR;
    }

    /* 
     * XXX - possible dangling reference: if the package vector changes
     * XXX - before this pointer is used, the results may be surprising.
     */
    PkgDesc->Lvalue.Ref     = (void *) &PkgDesc->Package.PackageElems[IdxDesc->Number.Number];
    PkgDesc->ValType        = (UINT8) Lvalue;
    PkgDesc->Lvalue.OpCode  = IndexOp;

    if ((Excep = ExecStore (PkgDesc, ResDesc)) != S_SUCCESS)
    {
        ObjStackTop -= 2;
        return Excep;
    }
    
    DELETE (IdxDesc);
    ObjStackTop -= 2;
    
    return Excep;
}


/*****************************************************************************
 * 
 * FUNCTION:    ExecMatch
 *
 * PARAMETERS:  none
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Execute Match operator
 *
 * ALLOCATION:  Deletes 5 operands
 *
 ****************************************************************************/

INT32
ExecMatch (void)
{
    OBJECT_DESCRIPTOR       *PkgDesc;
    OBJECT_DESCRIPTOR       *Op1Desc;
    OBJECT_DESCRIPTOR       *V1Desc;
    OBJECT_DESCRIPTOR       *Op2Desc;
    OBJECT_DESCRIPTOR       *V2Desc;
    OBJECT_DESCRIPTOR       *StartDesc;
    UINT32                  Look;
    UINT32                  MatchValue = (UINT32)-1;
    INT32                   Excep;


    FUNCTION_TRACE ("ExecMatch");


    Excep = PrepStack ("nnnnnp");

    if (Excep != S_SUCCESS)
    {
        AmlAppendOperandDiag (__FILE__, __LINE__, (UINT16)MatchOp, 6);
        return Excep;
    }

    DumpStack (Exec, ShortOps[MatchOp], 6, "after PrepStack");

    StartDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];
    V2Desc    = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 1];
    Op2Desc   = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 2];
    V1Desc    = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 3];
    Op1Desc   = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 4];
    PkgDesc   = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 5];

    /* Validate match comparison sub-opcodes */
    
    if (Op1Desc->Number.Number < 0 || Op1Desc->Number.Number > 5
        || Op2Desc->Number.Number < 0 || Op2Desc->Number.Number > 5)
    {
        Why = "ExecMatch: operation encoding out of range";
        return S_ERROR;
    }

    Look = StartDesc->Number.Number;
    if (Look < 0 || Look >= (UINT32) PkgDesc->Package.PkgCount)
    {
        Why = "ExecMatch: start position value out of range";
        return S_ERROR;
    }

    /* 
     * Examine each element until a match is found.  Within the loop,
     * "continue" signifies that the current element does not match
     * and the next should be examined.
     * Upon finding a match, the loop will terminate via "break" at
     * the bottom.  If it terminates "normally", MatchValue will be -1
     * (its initial value) indicating that no match was found.  When
     * returned as a Number, this will produce the Ones value as specified.
     */

    for ( ; Look < (UINT32) PkgDesc->Package.PkgCount ; ++Look)
    {
        /* 
         * Treat any NULL or non-numeric elements as non-matching.
         * XXX - if an element is a Name, should we examine its value?
         */
        if ((OBJECT_DESCRIPTOR *) 0 == PkgDesc->Package.PackageElems[Look]
          || Number != PkgDesc->Package.PackageElems[Look]->ValType)
        {
            continue;
        }

        /* 
         * Within these switch statements:
         *      "break" (exit from the switch) signifies a match;
         *      "continue" (proceed to next iteration of enclosing
         *          "for" loop) signifies a non-match.
         */
        switch (Op1Desc->Number.Number)
        {
            case MTR:
                break;

            case MEQ:
                if (PkgDesc->Package.PackageElems[Look]->Number.Number
                     != V1Desc->Number.Number)
                    continue;
                break;

            case MLE:
                if (PkgDesc->Package.PackageElems[Look]->Number.Number
                     > V1Desc->Number.Number)
                    continue;
                break;

            case MLT:
                if (PkgDesc->Package.PackageElems[Look]->Number.Number
                     >= V1Desc->Number.Number)
                    continue;
                break;

            case MGE:
                if (PkgDesc->Package.PackageElems[Look]->Number.Number
                     < V1Desc->Number.Number)
                    continue;
                break;

            case MGT:
                if (PkgDesc->Package.PackageElems[Look]->Number.Number
                     <= V1Desc->Number.Number)
                    continue;
                break;

            default:
                continue;
        }
        
        switch(Op2Desc->Number.Number)
        {
            case MTR:
                break;

            case MEQ:
                if (PkgDesc->Package.PackageElems[Look]->Number.Number
                     != V2Desc->Number.Number)
                    continue;
                break;

            case MLE:
                if (PkgDesc->Package.PackageElems[Look]->Number.Number
                     > V2Desc->Number.Number)
                    continue;
                break;

            case MLT:
                if (PkgDesc->Package.PackageElems[Look]->Number.Number
                     >= V2Desc->Number.Number)
                    continue;
                break;

            case MGE:
                if (PkgDesc->Package.PackageElems[Look]->Number.Number
                     < V2Desc->Number.Number)
                    continue;
                break;

            case MGT:
                if (PkgDesc->Package.PackageElems[Look]->Number.Number
                     <= V2Desc->Number.Number)
                    continue;
                break;

            default:
                continue;
        }

        /* Match found: exit from loop */
        
        MatchValue = Look;
        break;
    }

    PkgDesc->ValType = (UINT8) Number;
    PkgDesc->Number.Number = MatchValue;

    DELETE (StartDesc);
    DELETE (V2Desc);
    DELETE (Op2Desc);
    DELETE (V1Desc);
    DELETE (Op1Desc);
    
    ObjStackTop -= 5;          /* Remove operands */
    return S_SUCCESS;
}


/******************************************************************************
 * 
 * FUNCTION:    AmlExec
 *
 * PARAMETERS:  INT32               Offset      Offset to method in code block
 *              INT32               Length      Length of method
 *              OBJECT_DESCRIPTOR   **Params    list of parameters to pass to
 *                                              method, terminated by NULL.
 *                                              Params itself may be NULL if
 *                                              no parameters are being passed.
 *
 * RETURN:      S_SUCCESS, S_RETURN, or S_ERROR
 *
 * DESCRIPTION: Execute the method
 *
 *****************************************************************************/

INT32
AmlExec (INT32 Offset, INT32 Length, OBJECT_DESCRIPTOR **Params)
{
    INT32           Excep;
    INT32           i1;
    INT32           i2;


    FUNCTION_TRACE ("AmlExec");


    if (AmlPrepExec (Offset, Length) != S_SUCCESS)               /* package stack */
    {
        Why = "AmlExec: Exec Stack Overflow";
        return S_ERROR;
    }

    /* Push new frame on Method stack */
    
    if (++MethodStackTop >= AML_METHOD_MAX_NEST)
    {
        --MethodStackTop;
        Why = "AmlExec: Method Stack Overflow";
        return S_ERROR;
    }

    /* Undefine all local variables */
    
    for (i1 = 0; i1 < NUMLCL; ++i1)
    {
        Excep = SetMethodValue (i1 + LCLBASE, NULL, NULL);
        if (S_SUCCESS != Excep)
        {
            --MethodStackTop;
            return Excep;
        }
    }

    /* Copy passed parameters into method stack frame */
    
    for (i2 = i1 = 0; i1 < NUMARG; ++i1)
    {
        if (Params && Params[i2])
        {
            Excep = SetMethodValue (i1 + ARGBASE, Params[i2++], NULL);
        }
        
        else
        {
            Excep = SetMethodValue (i1 + ARGBASE, NULL, NULL);
        }

        if (S_SUCCESS != Excep)
        {
            --MethodStackTop;
            return Excep;
        }
    }

    LineSet (0, Exec);


    /* 
     * Normal exit is with Excep == S_RETURN when a ReturnOp has been executed,
     * or with Excep == S_FAILURE at end of AML block (end of Method code)
     */

    while ((Excep = DoCode (Exec)) == S_SUCCESS)
    {;}

    if (S_FAILURE == Excep)
    {
        Excep = PopExec ();            /* package stack -- inverse of AmlPrepExec() */
    }

    else
    {
        if (S_RETURN == Excep && debug_level () > 0)
        {
            fprintf_bu (LstFileHandle, LOGFILE, "Method returned: ");
            
            DumpStackEntry ((OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop]);

            fprintf_bu (LstFileHandle, LOGFILE,
                        " at stack level %d", ObjStackTop);
        }

        (void) PopExec ();            /* package stack -- inverse of AmlPrepExec() */
    }

    --MethodStackTop;          /* pop our frame off method stack */

    return Excep;
}


#ifdef PLUMBER

/*****************************************************************************
 * 
 * FUNCTION:    MarkMethodValues
 *
 * PARAMETERS:  INT32 *   Count        Count of blocks marked
 *
 * DESCRIPTION: Mark blocks occupied by currently-active args and locals
 *
 ****************************************************************************/

void
MarkMethodValues (INT32 *Count)
{
    INT32           MethodNestLevel;
    INT32           Index;


    FUNCTION_TRACE ("MarkMethodValues");


    /* For each active Method */
    
    for (MethodNestLevel = MethodStackTop; MethodNestLevel >= 0; --MethodNestLevel)
    {
        /* For each possible Arg and Local */
        
        for (Index = 0; Index < (ARGBASE + NUMARG); ++Index)
        {
            /* Mark value's storage */
            
            if ((OBJECT_DESCRIPTOR *) 0 != MethodStack[MethodNestLevel][Index])
            {
                ++*Count;
                AmlMarkObject (MethodStack[MethodStackTop][Index]);
            }
        }
    }
}

#endif /* PLUMBER */


/*****************************************************************************
 * 
 * FUNCTION:    IsMethodValue
 *
 * PARAMETERS:  OBJECT_DESCRIPTOR *ObjDesc
 *
 * RETURN:      TRUE if the passed descriptor is the value of an Arg or
 *              Local in a currently-active Method, else FALSE
 *
 ****************************************************************************/

INT32
IsMethodValue (OBJECT_DESCRIPTOR *ObjDesc)
{
    INT32           MethodNestLevel;
    INT32           Index;


    FUNCTION_TRACE ("IsMethodValue");


    /* For each active Method */
    
    for (MethodNestLevel = MethodStackTop; MethodNestLevel >= 0; --MethodNestLevel)
    {
        /* For each possible Arg and Local */
        
        for (Index = 0; Index < (ARGBASE + NUMARG); ++Index)
        {
            if (ObjDesc == MethodStack[MethodNestLevel][Index])
            {
                return TRUE;
            }
        }
    }

    return FALSE;
}
