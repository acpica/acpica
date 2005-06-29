
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

#include <acpi.h>
#include <interpreter.h>
#include <amlcode.h>
#include <namespace.h>

#define _THIS_MODULE        "isutils.c"
#define _COMPONENT          INTERPRETER



/*****************************************************************************
 * 
 * FUNCTION:    AmlAppendOperandDiag
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
AmlAppendOperandDiag(
    char                    *FileName, 
    INT32                   LineNum, 
    UINT16                  OpCode, 
    INT32                   NumOperands)
{
    METHOD_INFO             Method;


    AmlGetCurrentLocation (&Method);

    DEBUG_PRINT (ACPI_ERROR, (" [%s:%d, opcode = %s AML offset %04x]\n",
                    FileName, LineNum,
                    (OpCode > ACPI_UCHAR_MAX)
                        ? LongOps[OpCode & 0x00ff]
                        : ShortOps[OpCode],
                    Method.Offset));

    if (GetDebugLevel () > 0)
    {
        DUMP_STACK (MODE_Exec,
                      (OpCode > ACPI_UCHAR_MAX)
                      ? LongOps[OpCode & 0x00ff]
                      : ShortOps[OpCode],
                      NumOperands,
                      "after PrepStack failed");
    }
}



/*****************************************************************************
 *
 * FUNCTION:    AmlBufSeq
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
AmlBufSeq (void)
{
    
    return ++BufSeq;
}



/*****************************************************************************
 *
 * FUNCTION:    AmlAcquireGlobalLock
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
AmlAcquireGlobalLock (
    UINT16                  Rule)
{
    BOOLEAN                 Locked = FALSE;


    FUNCTION_TRACE ("AmlAcquireGlobalLock");


    /*  Only attempt lock if the Rule says so */
    
    if (Rule == (UINT16) GLOCK_AlwaysLock)
    {   
        /*  OK to get the lock   */
        
        if (OsGetGlobalLock () != AE_OK)
        {
            /*  
             * lock ownership failed
             */
            DEBUG_PRINT (ACPI_ERROR, ("Get Global Lock Failed!!\n"));
        }

        else
        {
            GlobalLockSet = TRUE;
            Locked = TRUE;
        }
    }

    FUNCTION_EXIT;
    return Locked;
}


/*****************************************************************************
 *
 * FUNCTION:    AmlReleaseGlobalLock
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
AmlReleaseGlobalLock (
    BOOLEAN                 LockedByMe)
{

    FUNCTION_TRACE ("AmlReleaseGlobalLock");


    /* Only attempt unlock if the caller locked it */

    if (LockedByMe)
    {
        /* Double check against the global flag */

        if (GlobalLockSet)
        {
            /* OK, now release the lock */

            OsReleaseGlobalLock ();
            GlobalLockSet = FALSE;
        }

        else
        {
            /* Sorry, the lock wasn't set, according to our records */

            DEBUG_PRINT (ACPI_ERROR, ("Global lock was not set\n"));
        }
    }


    FUNCTION_EXIT;
    return AE_OK;
}

/******************************************************************************
 * 
 * FUNCTION:    AmlDigitsNeeded
 *
 * PARAMETERS:  val             - Value to be represented
 *              base            - Base of representation
 *
 * RETURN:      the number of digits needed to represent val in base
 *
 *****************************************************************************/

INT32
AmlDigitsNeeded (
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

    FUNCTION_EXIT;
    return NumDigits;
}


