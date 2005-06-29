
/******************************************************************************
 *
 * Module Name: isutils - interpreter/scanner utilities
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
 * 2.1. This is your license from Intel Corp. under its intellectual property
 * rights.  You may have additional license terms from the party that provided
 * you this software, covering your right to use that party's intellectual
 * property rights.
 *
 * 2.2. Intel grants, free of charge, to any person ("Licensee") obtaining a
 * copy of the source code appearing in this file ("Covered Code") an
 * irrevocable, perpetual, worldwide license under Intel's copyrights in the
 * base code distributed originally by Intel ("Original Intel Code") to copy,
 * make derivatives, distribute, use and display any portion of the Covered
 * Code in any form, with the right to sublicense such rights; and
 *
 * 2.3. Intel grants Licensee a non-exclusive and non-transferable patent
 * license (with the right to sublicense), under only those claims of Intel
 * patents that are infringed by the Original Intel Code, to make, use, sell,
 * offer to sell, and import the Covered Code and derivative works thereof
 * solely to the minimum extent necessary to exercise the above copyright
 * license, and in no event shall the patent license extend to any additions
 * to or modifications of the Original Intel Code.  No other license or right
 * is granted directly or by implication, estoppel or otherwise;
 *
 * The above copyright and patent license is granted only if the following
 * conditions are met:
 *
 * 3. Conditions
 *
 * 3.1. Redistribution of Source with Rights to Further Distribute Source.
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification with rights to further distribute source must include
 * the above Copyright Notice, the above License, this list of Conditions,
 * and the following Disclaimer and Export Compliance provision.  In addition,
 * Licensee must cause all Covered Code to which Licensee contributes to
 * contain a file documenting the changes Licensee made to create that Covered
 * Code and the date of any change.  Licensee must include in that file the
 * documentation of any changes made by any predecessor Licensee.  Licensee
 * must include a prominent statement that the modification is derived,
 * directly or indirectly, from Original Intel Code.
 *
 * 3.2. Redistribution of Source with no Rights to Further Distribute Source.
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification without rights to further distribute source must
 * include the following Disclaimer and Export Compliance provision in the
 * documentation and/or other materials provided with distribution.  In
 * addition, Licensee may not authorize further sublicense of source of any
 * portion of the Covered Code, and must include terms to the effect that the
 * license from Licensee to its licensee is limited to the intellectual
 * property embodied in the software Licensee provides to its licensee, and
 * not to intellectual property embodied in modifications its licensee may
 * make.
 *
 * 3.3. Redistribution of Executable. Redistribution in executable form of any
 * substantial portion of the Covered Code or modification must reproduce the
 * above Copyright Notice, and the following Disclaimer and Export Compliance
 * provision in the documentation and/or other materials provided with the
 * distribution.
 *
 * 3.4. Intel retains all right, title, and interest in and to the Original
 * Intel Code.
 *
 * 3.5. Neither the name Intel nor any other trademark owned or controlled by
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
 * event Licensee exports any such software from the United States or
 * re-exports any such software from a foreign destination, Licensee shall
 * ensure that the distribution and export/re-export of the software is in
 * compliance with all laws, regulations, orders, or other restrictions of the
 * U.S. Export Administration Regulations. Licensee agrees that neither it nor
 * any of its subsidiaries will export/re-export any technical data, process,
 * software, or service, directly or indirectly, to any country for which the
 * United States government or any agency thereof requires an export license,
 * other governmental approval, or letter of assurance, without first obtaining
 * such license, approval or letter.
 *
 *****************************************************************************/

#define __ISUTILS_C__

#include "acpi.h"
#include "parser.h"
#include "interp.h"
#include "amlcode.h"
#include "namesp.h"
#include "events.h"

#define _COMPONENT          INTERPRETER
        MODULE_NAME         ("isutils");

static char                 hex[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};



/*****************************************************************************
 *
 * FUNCTION:    AcpiAmlEnterInterpreter
 *
 * PARAMETERS:  None
 *
 * DESCRIPTION: Enter the interpreter execution region
 *
 ****************************************************************************/

void
AcpiAmlEnterInterpreter (void)
{
    FUNCTION_TRACE ("AmlEnterInterpreter");


    AcpiCmAcquireMutex (MTX_EXECUTE);

    return_VOID;
}


/*****************************************************************************
 *
 * FUNCTION:    AcpiAmlExitInterpreter
 *
 * PARAMETERS:  None
 *
 * DESCRIPTION: Exit the interpreter execution region
 *
 * Cases where the interpreter is unlocked:
 *      1) Completion of the execution of a control method
 *      2) Method blocked on a Sleep() AML opcode
 *      3) Method blocked on an Acquire() AML opcode
 *      4) Method blocked on a Wait() AML opcode
 *      5) Method blocked to acquire the global lock
 *      6) Method blocked to execute a serialized control method that is
 *          already executing
 *      7) About to invoke a user-installed opregion handler
 *
 ****************************************************************************/

void
AcpiAmlExitInterpreter (void)
{
    FUNCTION_TRACE ("AmlExitInterpreter");


    AcpiCmReleaseMutex (MTX_EXECUTE);

    return_VOID;
}


/*****************************************************************************
 *
 * FUNCTION:    AcpiAmlValidateObjectType
 *
 * PARAMETERS:  Type            Object type to validate
 *
 * DESCRIPTION: Determine if a type is a valid ACPI object type
 *
 ****************************************************************************/

BOOLEAN
AcpiAmlValidateObjectType (
    ACPI_OBJECT_TYPE        Type)
{

    if ((Type > ACPI_TYPE_MAX && Type < INTERNAL_TYPE_BEGIN) ||
        (Type > INTERNAL_TYPE_MAX))
    {
        return FALSE;
    }

    return TRUE;
}


/*****************************************************************************
 *
 * FUNCTION:    AcpiAmlAppendOperandDiag
 *
 * PARAMETERS:  *FileName       - Name of source file
 *              LineNum         - Line Number in file
 *              OpCode          - OpCode being executed
 *              NumOperands     - Number of operands PrepStack tried to check
 *
 * DESCRIPTION: Print diagnostic information about operands.
 *              This function is intended to be called after PrepStack
 *              has returned S_ERROR.
 *
 ****************************************************************************/

void
AcpiAmlAppendOperandDiag (
    char                    *FileName,
    INT32                   LineNum,
    UINT16                  OpCode,
    ACPI_OBJECT_INTERNAL    **Operands,
    INT32                   NumOperands)
{

    DEBUG_PRINT (ACPI_ERROR, (" [%s:%d, opcode = %s AML offset %04x]\n",
                    FileName, LineNum, AcpiPsGetOpcodeName (OpCode), NULL));

    if (GetDebugLevel () > 0)
    {
        DUMP_OPERANDS (Operands, IMODE_EXECUTE, AcpiPsGetOpcodeName (OpCode),
                        NumOperands, "after PrepStack failed");
    }
}



/*****************************************************************************
 *
 * FUNCTION:    AcpiAmlBufSeq
 *
 * RETURN:      The next buffer descriptor sequence number
 *
 * DESCRIPTION: Provide a unique sequence number for each Buffer descriptor
 *              allocated during the interpreter's existence.  These numbers
 *              are used to relate FieldUnit descriptors to the Buffers
 *              within which the fields are defined.
 *
 *              Just increment the global counter and return it.
 *
 ****************************************************************************/

UINT32
AcpiAmlBufSeq (void)
{

    return ++AcpiGbl_BufSeq;
}



/*****************************************************************************
 *
 * FUNCTION:    AcpiAmlAcquireGlobalLock
 *
 * PARAMETERS:  Rule            - Lock rule: AlwaysLock, NeverLock
 *
 * RETURN:      TRUE/FALSE indicating whether the lock was actually acquired
 *
 * DESCRIPTION: Obtain the global lock and keep track of this fact via two
 *              methods.  A global variable keeps the state of the lock, and
 *              the state is returned to the caller.
 *
 ****************************************************************************/

BOOLEAN
AcpiAmlAcquireGlobalLock (
    UINT32                  Rule)
{
    BOOLEAN                 Locked = FALSE;


    FUNCTION_TRACE ("AmlAcquireGlobalLock");


    /*  Only attempt lock if the Rule says so */

    if (Rule == (UINT32) GLOCK_ALWAYS_LOCK)
    {
        /*  OK to get the lock   */

        if (AcpiEvAcquireGlobalLock () != AE_OK)
        {
            /*
             * lock ownership failed
             */
            DEBUG_PRINT (ACPI_ERROR, ("Get Global Lock Failed!!\n"));
        }

        else
        {
            AcpiGbl_GlobalLockSet = TRUE;
            Locked = TRUE;
        }
    }

    return_VALUE (Locked);
}


/*****************************************************************************
 *
 * FUNCTION:    AcpiAmlReleaseGlobalLock
 *
 * PARAMETERS:  LockedByMe      - Return value from corresponding call to
 *                                AcquireGlobalLock.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Release the global lock if it is locked.
 *
 ****************************************************************************/

ACPI_STATUS
AcpiAmlReleaseGlobalLock (
    BOOLEAN                 LockedByMe)
{

    FUNCTION_TRACE ("AmlReleaseGlobalLock");


    /* Only attempt unlock if the caller locked it */

    if (LockedByMe)
    {
        /* Double check against the global flag */

        if (AcpiGbl_GlobalLockSet)
        {
            /* OK, now release the lock */

            AcpiEvReleaseGlobalLock ();
            AcpiGbl_GlobalLockSet = FALSE;
        }

        else
        {
            /* Sorry, the lock wasn't set, according to our records */

            DEBUG_PRINT (ACPI_ERROR, ("Global lock was not set\n"));
        }
    }


    return_ACPI_STATUS (AE_OK);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiAmlDigitsNeeded
 *
 * PARAMETERS:  val             - Value to be represented
 *              base            - Base of representation
 *
 * RETURN:      the number of digits needed to represent val in base
 *
 *****************************************************************************/

INT32
AcpiAmlDigitsNeeded (
    INT32                   val,
    INT32                   base)
{
    INT32                   NumDigits = 0;


    FUNCTION_TRACE ("AmlDigitsNeeded");


    if (base < 1)
    {
        /*  impossible base */

        REPORT_ERROR ("AmlDigitsNeeded: Impossible base");
    }

    else
    {
        for (NumDigits = 1 + (val < 0) ; val /= base ; ++NumDigits)
        { ; }
    }

    return_VALUE (NumDigits);
}


/******************************************************************************
 *
 * FUNCTION:    ntohl
 *
 * PARAMETERS:  Value           - Value to be converted
 *
 * RETURN:      Convert a 32-bit value to big-endian (swap the bytes)
 *
 *****************************************************************************/

UINT32
_ntohl (
    UINT32                  Value)
{
    union
    {
        UINT32              Value;
        char                Bytes[4];
    } Out;

    union
    {
        UINT32              Value;
        char                Bytes[4];
    } In;


    In.Value = Value;

    Out.Bytes[0] = In.Bytes[3];
    Out.Bytes[1] = In.Bytes[2];
    Out.Bytes[2] = In.Bytes[1];
    Out.Bytes[3] = In.Bytes[0];

    return Out.Value;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiAmlEisaIdToString
 *
 * PARAMETERS:  NumericId       - EISA ID to be converted
 *              OutString       - Where to put the converted string (8 bytes)
 *
 * RETURN:      Convert a numeric EISA ID to string representation
 *
 *****************************************************************************/

ACPI_STATUS
AcpiAmlEisaIdToString (
    UINT32                  NumericId,
    char                    *OutString)
{
    UINT32                  id;


    id = _ntohl (NumericId);                    /* swap to big-endian to get contiguous bits */

    OutString[0] = (char) ('@' + ((id >> 26) & 0x1f));
    OutString[1] = (char) ('@' + ((id >> 21) & 0x1f));
    OutString[2] = (char) ('@' + ((id >> 16) & 0x1f));
    OutString[3] = hex[(id >> 12) & 0xf];
    OutString[4] = hex[(id >> 8) & 0xf];
    OutString[5] = hex[(id >> 4) & 0xf];
    OutString[6] = hex[id & 0xf];
    OutString[7] = 0;

    return AE_OK;
}

