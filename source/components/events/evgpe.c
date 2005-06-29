/******************************************************************************
 *
 * Module Name: evgpe - General Purpose Event handling and dispatch
 *              $Revision: 1.10 $
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2003, Intel Corp.
 * All rights reserved.
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

#include "acpi.h"
#include "acevents.h"
#include "acnamesp.h"

#define _COMPONENT          ACPI_EVENTS
        ACPI_MODULE_NAME    ("evgpe")



/*******************************************************************************
 *
 * FUNCTION:    AcpiEvGetGpeEventInfo
 *
 * PARAMETERS:  GpeNumber       - Raw GPE number
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Returns the EventInfo struct
 *              associated with this GPE.
 *
 * TBD: this function will go away when full support of GPE block devices
 *      is implemented!
 *
 ******************************************************************************/

ACPI_GPE_EVENT_INFO *
AcpiEvGetGpeEventInfo (
    UINT32                  GpeNumber)
{
    ACPI_GPE_BLOCK_INFO     *GpeBlock;


    /* Examine GPE Block 0 */

    GpeBlock = AcpiGbl_GpeBlockListHead;
    if (!GpeBlock)
    {
        return (NULL);
    }

    if ((GpeNumber >= GpeBlock->BlockBaseNumber) &&
        (GpeNumber < GpeBlock->BlockBaseNumber + (GpeBlock->RegisterCount * 8)))
    {
        return (&GpeBlock->EventInfo[GpeNumber - GpeBlock->BlockBaseNumber]);
    }

    /* Examine GPE Block 1 */

    GpeBlock = GpeBlock->Next;
    if (!GpeBlock)
    {
        return (NULL);
    }

    if ((GpeNumber >= GpeBlock->BlockBaseNumber) &&
        (GpeNumber < GpeBlock->BlockBaseNumber + (GpeBlock->RegisterCount * 8)))
    {
        return (&GpeBlock->EventInfo[GpeNumber - GpeBlock->BlockBaseNumber]);
    }

    return (NULL);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiEvSaveMethodInfo
 *
 * PARAMETERS:  Callback from WalkNamespace
 *
 * RETURN:      None
 *
 * DESCRIPTION: Called from AcpiWalkNamespace.  Expects each object to be a
 *              control method under the _GPE portion of the namespace.
 *              Extract the name and GPE type from the object, saving this
 *              information for quick lookup during GPE dispatch
 *
 *              The name of each GPE control method is of the form:
 *                  "_Lnn" or "_Enn"
 *              Where:
 *                  L      - means that the GPE is level triggered
 *                  E      - means that the GPE is edge triggered
 *                  nn     - is the GPE number [in HEX]
 *
 ******************************************************************************/

static ACPI_STATUS
AcpiEvSaveMethodInfo (
    ACPI_HANDLE             ObjHandle,
    UINT32                  Level,
    void                    *ObjDesc,
    void                    **ReturnValue)
{
    ACPI_GPE_BLOCK_INFO     *GpeBlock = (void *) ObjDesc;
    ACPI_GPE_EVENT_INFO     *GpeEventInfo;
    UINT32                  GpeNumber;
    char                    Name[ACPI_NAME_SIZE + 1];
    UINT8                   Type;
    ACPI_STATUS             Status;


    ACPI_FUNCTION_NAME ("EvSaveMethodInfo");


    /* Extract the name from the object and convert to a string */

    ACPI_MOVE_UNALIGNED32_TO_32 (Name,
                &((ACPI_NAMESPACE_NODE *) ObjHandle)->Name.Integer);
    Name[ACPI_NAME_SIZE] = 0;

    /*
     * Edge/Level determination is based on the 2nd character of the method name
     */
    switch (Name[1])
    {
    case 'L':
        Type = ACPI_EVENT_LEVEL_TRIGGERED;
        break;

    case 'E':
        Type = ACPI_EVENT_EDGE_TRIGGERED;
        break;

    default:
        /* Unknown method type, just ignore it! */

        ACPI_DEBUG_PRINT ((ACPI_DB_ERROR,
            "Unknown GPE method type: %s (name not of form _Lnn or _Enn)\n",
            Name));
        return (AE_OK);
    }

    /* Convert the last two characters of the name to the GPE Number */

    GpeNumber = ACPI_STRTOUL (&Name[2], NULL, 16);
    if (GpeNumber == ACPI_UINT32_MAX)
    {
        /* Conversion failed; invalid method, just ignore it */

        ACPI_DEBUG_PRINT ((ACPI_DB_ERROR,
            "Could not extract GPE number from name: %s (name is not of form _Lnn or _Enn)\n",
            Name));
        return (AE_OK);
    }

    /* Ensure that we have a valid GPE number for this GPE block */

    if ((GpeNumber < GpeBlock->BlockBaseNumber) ||
        (GpeNumber >= (GpeBlock->RegisterCount * 8)))
    {
        /* Not valid, all we can do here is ignore it */

        ACPI_DEBUG_PRINT ((ACPI_DB_ERROR,
            "GPE number associated with method %s is not valid\n", Name));
        return (AE_OK);
    }

    /*
     * Now we can add this information to the GpeEventInfo block
     * for use during dispatch of this GPE.
     */
    GpeEventInfo = &GpeBlock->EventInfo[GpeNumber - GpeBlock->BlockBaseNumber];

    GpeEventInfo->Type       = Type;
    GpeEventInfo->MethodNode = (ACPI_NAMESPACE_NODE *) ObjHandle;

    /*
     * Enable the GPE (SCIs should be disabled at this point)
     */
    Status = AcpiHwEnableGpe (GpeEventInfo);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    ACPI_DEBUG_PRINT ((ACPI_DB_INFO, "Registered GPE method %s as GPE number %2.2X\n",
        Name, GpeNumber));
    return (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiEvInstallGpeBlock
 *
 * PARAMETERS:  
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install a block of GPE registers
 *
 ******************************************************************************/

ACPI_STATUS
AcpiEvInstallGpeBlock (
    char                    *Pathname,
    ACPI_GENERIC_ADDRESS    *GpeBlockAddress,
    UINT32                  RegisterCount,
    UINT8                   GpeBlockBaseNumber,
    UINT32                  InterruptLevel)
{
    ACPI_GPE_BLOCK_INFO     *NextGpeBlock;
    ACPI_GPE_BLOCK_INFO     *GpeBlock;
    ACPI_GPE_REGISTER_INFO  *GpeRegisterInfo;
    ACPI_GPE_EVENT_INFO     *GpeEventInfo;
    ACPI_GPE_EVENT_INFO     *ThisEvent;
    ACPI_STATUS             Status;
    ACPI_GPE_REGISTER_INFO  *ThisRegister;
    ACPI_NATIVE_UINT        i;
    ACPI_NATIVE_UINT        j;
    ACPI_HANDLE             ObjHandle;



    ACPI_FUNCTION_TRACE ("AcpiEvInstallGpeBlock");


    if (!RegisterCount)
    {
        return_ACPI_STATUS (AE_OK)
    }

    /* Allocate a new GPE block */

    GpeBlock = ACPI_MEM_CALLOCATE (sizeof (ACPI_GPE_BLOCK_INFO));
    if (!GpeBlock)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /* Allocate the GPE register information block */

    GpeRegisterInfo = ACPI_MEM_CALLOCATE (
                                (ACPI_SIZE) RegisterCount *
                                sizeof (ACPI_GPE_REGISTER_INFO));
    if (!GpeRegisterInfo)
    {
        ACPI_DEBUG_PRINT ((ACPI_DB_ERROR,
            "Could not allocate the GpeRegisterInfo table\n"));
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /*
     * Allocate the GPE dispatch handler block.  There are eight distinct GPEs
     * per register.  Initialization to zeros is sufficient.
     */
    GpeEventInfo = ACPI_MEM_CALLOCATE (
                        ((ACPI_SIZE) RegisterCount * ACPI_GPE_REGISTER_WIDTH) *
                        sizeof (ACPI_GPE_EVENT_INFO));
    if (!GpeEventInfo)
    {
        ACPI_DEBUG_PRINT ((ACPI_DB_ERROR, "Could not allocate the GpeEventInfo table\n"));
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /*
     * Initialize the GPE Register and Event structures.  A goal of these
     * tables is to hide the fact that there are two separate GPE register sets
     * in a given gpe hardware block, the status registers occupy the first half,
     * and the enable registers occupy the second half.  Another goal is to hide
     * the fact that there may be multiple GPE hardware blocks.
     */
    ThisRegister = GpeRegisterInfo;
    ThisEvent    = GpeEventInfo;

    for (i = 0; i < RegisterCount; i++)
    {
        /* Init the RegisterInfo for this GPE register (8 GPEs) */

        ThisRegister->BaseGpeNumber = (UINT8) (GpeBlockBaseNumber + 
                                                 (i * ACPI_GPE_REGISTER_WIDTH));

        ACPI_STORE_ADDRESS (ThisRegister->StatusAddress.Address,
                                (ACPI_GET_ADDRESS (GpeBlockAddress->Address)
                                + i));

        ACPI_STORE_ADDRESS (ThisRegister->EnableAddress.Address,
                                (ACPI_GET_ADDRESS (GpeBlockAddress->Address)
                                + i
                                + RegisterCount));

        ThisRegister->StatusAddress.AddressSpaceId    = GpeBlockAddress->AddressSpaceId;
        ThisRegister->EnableAddress.AddressSpaceId    = GpeBlockAddress->AddressSpaceId;
        ThisRegister->StatusAddress.RegisterBitWidth  = ACPI_GPE_REGISTER_WIDTH;
        ThisRegister->EnableAddress.RegisterBitWidth  = ACPI_GPE_REGISTER_WIDTH;
        ThisRegister->StatusAddress.RegisterBitOffset = ACPI_GPE_REGISTER_WIDTH;
        ThisRegister->EnableAddress.RegisterBitOffset = ACPI_GPE_REGISTER_WIDTH;

        /* Init the EventInfo for each GPE within this register */

        for (j = 0; j < ACPI_GPE_REGISTER_WIDTH; j++)
        {
            ThisEvent->BitMask = AcpiGbl_DecodeTo8bit[j];
            ThisEvent->RegisterInfo = ThisRegister;
            ThisEvent++;
        }

        /*
         * Clear the status/enable registers.  Note that status registers
         * are cleared by writing a '1', while enable registers are cleared
         * by writing a '0'.
         */
        Status = AcpiHwLowLevelWrite (ACPI_GPE_REGISTER_WIDTH, 0x00, 
                    &ThisRegister->EnableAddress, 0);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }

        Status = AcpiHwLowLevelWrite (ACPI_GPE_REGISTER_WIDTH, 0xFF, 
                    &ThisRegister->StatusAddress, 0);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }
        
        ThisRegister++;
    }

    /* Initialize the new GPE block */

    GpeBlock->RegisterInfo    = GpeRegisterInfo;
    GpeBlock->EventInfo       = GpeEventInfo;
    GpeBlock->RegisterCount   = RegisterCount;
    GpeBlock->BlockBaseNumber = GpeBlockBaseNumber;

    ACPI_MEMCPY (&GpeBlock->BlockAddress, GpeBlockAddress, sizeof (ACPI_GENERIC_ADDRESS));

    /* Dump info about this GPE block */

    ACPI_DEBUG_PRINT ((ACPI_DB_INIT, "GPE Block: %X registers at %8.8X%8.8X\n",
        GpeBlock->RegisterCount,
        ACPI_HIDWORD (ACPI_GET_ADDRESS (GpeBlock->BlockAddress.Address)),
        ACPI_LODWORD (ACPI_GET_ADDRESS (GpeBlock->BlockAddress.Address))));

    ACPI_DEBUG_PRINT ((ACPI_DB_INIT, "GPE Block defined as GPE%d to GPE%d\n",
        GpeBlock->BlockBaseNumber,
        (UINT32) (GpeBlock->BlockBaseNumber +
                ((GpeBlock->RegisterCount * ACPI_GPE_REGISTER_WIDTH) -1))));

    /* Install the new block at the end of the global list */

    if (AcpiGbl_GpeBlockListHead)
    {
        NextGpeBlock = AcpiGbl_GpeBlockListHead;
        while (NextGpeBlock->Next)
        {
            NextGpeBlock = NextGpeBlock->Next;
        }

        NextGpeBlock->Next = GpeBlock;
        GpeBlock->Previous = NextGpeBlock;
    }
    else
    {
        AcpiGbl_GpeBlockListHead = GpeBlock;
    }

    /* Get a handle to the parent object for this GPE block */

    Status = AcpiGetHandle (NULL, Pathname, &ObjHandle);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Find all GPE methods (_Lxx, _Exx) for this block */

    Status = AcpiWalkNamespace (ACPI_TYPE_METHOD, ObjHandle,
                                ACPI_UINT32_MAX, AcpiEvSaveMethodInfo,
                                GpeBlock, NULL);

    /* TBD: Install block in the interrupt handler list */

    return_ACPI_STATUS (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiEvGpeInitialize
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Initialize the GPE data structures
 *
 ******************************************************************************/

ACPI_STATUS
AcpiEvGpeInitialize (void)
{
    UINT32                  RegisterCount0 = 0;
    UINT32                  RegisterCount1 = 0;
    UINT32                  GpeNumberMax = 0;


    ACPI_FUNCTION_TRACE ("EvGpeInitialize");


    /*
     * Initialize the GPE Blocks defined in the FADT
     *
     * Why the GPE register block lengths are divided by 2:  From the ACPI Spec,
     * section "General-Purpose Event Registers", we have:
     *
     * "Each register block contains two registers of equal length
     *  GPEx_STS and GPEx_EN (where x is 0 or 1). The length of the
     *  GPE0_STS and GPE0_EN registers is equal to half the GPE0_LEN
     *  The length of the GPE1_STS and GPE1_EN registers is equal to
     *  half the GPE1_LEN. If a generic register block is not supported
     *  then its respective block pointer and block length values in the
     *  FADT table contain zeros. The GPE0_LEN and GPE1_LEN do not need
     *  to be the same size."
     */

    /*
     * Determine the maximum GPE number for this machine.
     *
     * Note: both GPE0 and GPE1 are optional, and either can exist without
     * the other.
     * If EITHER the register length OR the block address are zero, then that
     * particular block is not supported.
     */
    if (AcpiGbl_FADT->Gpe0BlkLen && 
        ACPI_GET_ADDRESS (AcpiGbl_FADT->XGpe0Blk.Address))
    {
        /* GPE block 0 exists (has both length and address > 0) */

        RegisterCount0 = (UINT16) (AcpiGbl_FADT->Gpe0BlkLen / 2);

        GpeNumberMax = (RegisterCount0 * ACPI_GPE_REGISTER_WIDTH) - 1;

        AcpiEvInstallGpeBlock ("\\_GPE", &AcpiGbl_FADT->XGpe0Blk, 
            RegisterCount0, 0, AcpiGbl_FADT->SciInt);
    }

    if (AcpiGbl_FADT->Gpe1BlkLen && 
        ACPI_GET_ADDRESS (AcpiGbl_FADT->XGpe1Blk.Address))
    {
        /* GPE block 1 exists (has both length and address > 0) */

        RegisterCount1 = (UINT16) (AcpiGbl_FADT->Gpe1BlkLen / 2);

        /* Check for GPE0/GPE1 overlap (if both banks exist) */

        if ((RegisterCount0) &&
            (GpeNumberMax >= AcpiGbl_FADT->Gpe1Base))
        {
            ACPI_REPORT_ERROR ((
                "GPE0 block (GPE 0 to %d) overlaps the GPE1 block (GPE %d to %d) - Ignoring GPE1\n",
                GpeNumberMax, AcpiGbl_FADT->Gpe1Base,
                AcpiGbl_FADT->Gpe1Base + 
                ((RegisterCount1 * ACPI_GPE_REGISTER_WIDTH) - 1)));

            /* Ignore GPE1 block by setting the register count to zero */

            RegisterCount1 = 0;
        }
        else
        {
            AcpiEvInstallGpeBlock ("\\_GPE", &AcpiGbl_FADT->XGpe1Blk, 
                RegisterCount1, AcpiGbl_FADT->Gpe1Base, AcpiGbl_FADT->SciInt);

            /*
             * GPE0 and GPE1 do not have to be contiguous in the GPE number space,
             * But, GPE0 always starts at zero.
             */
            GpeNumberMax = AcpiGbl_FADT->Gpe1Base +
                                ((RegisterCount1 * ACPI_GPE_REGISTER_WIDTH) - 1);
        }
    }

    /* Exit if there are no GPE registers */

    if ((RegisterCount0 + RegisterCount1) == 0)
    {
        /* GPEs are not required by ACPI, this is OK */

        ACPI_REPORT_INFO (("There are no GPE blocks defined in the FADT\n"));
        return_ACPI_STATUS (AE_OK);
    }

    /* Check for Max GPE number out-of-range */

    if (GpeNumberMax > ACPI_GPE_MAX)
    {
        ACPI_REPORT_ERROR (("Maximum GPE number from FADT is too large: 0x%X\n",
            GpeNumberMax));
        return_ACPI_STATUS (AE_BAD_VALUE);
    }

    return_ACPI_STATUS (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiEvGpeDetect
 *
 * PARAMETERS:  None
 *
 * RETURN:      INTERRUPT_HANDLED or INTERRUPT_NOT_HANDLED
 *
 * DESCRIPTION: Detect if any GP events have occurred.  This function is
 *              executed at interrupt level.
 *
 ******************************************************************************/

UINT32
AcpiEvGpeDetect (void)
{
    UINT32                  IntStatus = ACPI_INTERRUPT_NOT_HANDLED;
    UINT32                  i;
    UINT32                  j;
    UINT8                   EnabledStatusByte;
    UINT8                   BitMask;
    ACPI_GPE_REGISTER_INFO  *GpeRegisterInfo;
    UINT32                  InValue;
    ACPI_STATUS             Status;
    ACPI_GPE_BLOCK_INFO     *GpeBlock;


    ACPI_FUNCTION_NAME ("EvGpeDetect");


    /* Examine all GPE blocks attached to this interrupt level */

    GpeBlock = AcpiGbl_GpeBlockListHead;
    while (GpeBlock)
    {
        /*
         * Read all of the 8-bit GPE status and enable registers
         * in this GPE block, saving all of them.
         * Find all currently active GP events.
         */
        for (i = 0; i < GpeBlock->RegisterCount; i++)
        {
            /* Get the next status/enable pair */

            GpeRegisterInfo = &GpeBlock->RegisterInfo[i];

            Status = AcpiHwLowLevelRead (ACPI_GPE_REGISTER_WIDTH, &InValue, 
                        &GpeRegisterInfo->StatusAddress, 0);
            GpeRegisterInfo->Status = (UINT8) InValue;
            if (ACPI_FAILURE (Status))
            {
                return (ACPI_INTERRUPT_NOT_HANDLED);
            }

            Status = AcpiHwLowLevelRead (ACPI_GPE_REGISTER_WIDTH, &InValue, 
                        &GpeRegisterInfo->EnableAddress, 0);
            GpeRegisterInfo->Enable = (UINT8) InValue;
            if (ACPI_FAILURE (Status))
            {
                return (ACPI_INTERRUPT_NOT_HANDLED);
            }

            ACPI_DEBUG_PRINT ((ACPI_DB_INTERRUPTS,
                "GPE block at %8.8X%8.8X - Values: Enable %02X Status %02X\n",
                ACPI_HIDWORD (ACPI_GET_ADDRESS (GpeRegisterInfo->EnableAddress.Address)),
                ACPI_LODWORD (ACPI_GET_ADDRESS (GpeRegisterInfo->EnableAddress.Address)),
                GpeRegisterInfo->Enable,
                GpeRegisterInfo->Status));

            /* First check if there is anything active at all in this register */

            EnabledStatusByte = (UINT8) (GpeRegisterInfo->Status &
                                         GpeRegisterInfo->Enable);
            if (!EnabledStatusByte)
            {
                /* No active GPEs in this register, move on */

                continue;
            }

            /* Now look at the individual GPEs in this byte register */

            for (j = 0, BitMask = 1; j < ACPI_GPE_REGISTER_WIDTH; j++, BitMask <<= 1)
            {
                /* Examine one GPE bit */

                if (EnabledStatusByte & BitMask)
                {
                    /*
                     * Found an active GPE. Dispatch the event to a handler
                     * or method.
                     */
                    IntStatus |= AcpiEvGpeDispatch (
                                    &GpeBlock->EventInfo[(i * ACPI_GPE_REGISTER_WIDTH) +j]);
                }
            }
        }

        GpeBlock = GpeBlock->Next;
    }

    return (IntStatus);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiEvAsynchExecuteGpeMethod
 *
 * PARAMETERS:  GpeEventInfo - Info for this GPE
 *
 * RETURN:      None
 *
 * DESCRIPTION: Perform the actual execution of a GPE control method.  This
 *              function is called from an invocation of AcpiOsQueueForExecution
 *              (and therefore does NOT execute at interrupt level) so that
 *              the control method itself is not executed in the context of
 *              the SCI interrupt handler.
 *
 ******************************************************************************/

static void ACPI_SYSTEM_XFACE
AcpiEvAsynchExecuteGpeMethod (
    void                    *Context)
{
    ACPI_GPE_EVENT_INFO     *GpeEventInfo = (void *) Context;
    UINT32                  GpeNumber = 0;
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE ("EvAsynchExecuteGpeMethod");


    /*
     * Take a snapshot of the GPE info for this level - we copy the
     * info to prevent a race condition with RemoveHandler.
     */
    Status = AcpiUtAcquireMutex (ACPI_MTX_EVENTS);
    if (ACPI_FAILURE (Status))
    {
        return_VOID;
    }

    Status = AcpiUtReleaseMutex (ACPI_MTX_EVENTS);
    if (ACPI_FAILURE (Status))
    {
        return_VOID;
    }

    if (GpeEventInfo->MethodNode)
    {
        /*
         * Invoke the GPE Method (_Lxx, _Exx):
         * (Evaluate the _Lxx/_Exx control method that corresponds to this GPE.)
         */
        Status = AcpiNsEvaluateByHandle (GpeEventInfo->MethodNode, NULL, NULL);
        if (ACPI_FAILURE (Status))
        {
            ACPI_REPORT_ERROR (("%s while evaluating method [%4.4s] for GPE[%2.2X]\n",
                AcpiFormatException (Status),
                GpeEventInfo->MethodNode->Name.Ascii, GpeNumber));
        }
    }

    if (GpeEventInfo->Type & ACPI_EVENT_LEVEL_TRIGGERED)
    {
        /*
         * GPE is level-triggered, we clear the GPE status bit after handling
         * the event.
         */
        Status = AcpiHwClearGpe (GpeEventInfo);
        if (ACPI_FAILURE (Status))
        {
            return_VOID;
        }
    }

    /* Enable this GPE */

    (void) AcpiHwEnableGpe (GpeEventInfo);
    return_VOID;
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiEvGpeDispatch
 *
 * PARAMETERS:  GpeEventInfo   - info for this GPE
 *
 * RETURN:      INTERRUPT_HANDLED or INTERRUPT_NOT_HANDLED
 *
 * DESCRIPTION: Dispatch a General Purpose Event to either a function (e.g. EC)
 *              or method (e.g. _Lxx/_Exx) handler.  This function executes
 *              at interrupt level.
 *
 ******************************************************************************/

UINT32
AcpiEvGpeDispatch (
    ACPI_GPE_EVENT_INFO     *GpeEventInfo)
{
    UINT32                  GpeNumber = 0; /* TBD: remove */
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE ("EvGpeDispatch");


    /*
     * If edge-triggered, clear the GPE status bit now.  Note that
     * level-triggered events are cleared after the GPE is serviced.
     */
    if (GpeEventInfo->Type & ACPI_EVENT_EDGE_TRIGGERED)
    {
        Status = AcpiHwClearGpe (GpeEventInfo);
        if (ACPI_FAILURE (Status))
        {
            ACPI_REPORT_ERROR (("AcpiEvGpeDispatch: Unable to clear GPE[%2.2X]\n", 
                GpeNumber));
            return_VALUE (ACPI_INTERRUPT_NOT_HANDLED);
        }
    }

    /*
     * Dispatch the GPE to either an installed handler, or the control
     * method associated with this GPE (_Lxx or _Exx).
     * If a handler exists, we invoke it and do not attempt to run the method.
     * If there is neither a handler nor a method, we disable the level to
     * prevent further events from coming in here.
     */
    if (GpeEventInfo->Handler)
    {
        /* Invoke the installed handler (at interrupt level) */

        GpeEventInfo->Handler (GpeEventInfo->Context);
    }
    else if (GpeEventInfo->MethodNode)
    {
        /*
         * Disable GPE, so it doesn't keep firing before the method has a
         * chance to run.
         */
        Status = AcpiHwDisableGpe (GpeEventInfo);
        if (ACPI_FAILURE (Status))
        {
            ACPI_REPORT_ERROR (("AcpiEvGpeDispatch: Unable to disable GPE[%2.2X]\n", 
                GpeNumber));
            return_VALUE (ACPI_INTERRUPT_NOT_HANDLED);
        }

        /*
         * Execute the method associated with the GPE.
         */
        if (ACPI_FAILURE (AcpiOsQueueForExecution (OSD_PRIORITY_GPE,
                                AcpiEvAsynchExecuteGpeMethod,
                                GpeEventInfo)))
        {
            ACPI_REPORT_ERROR ((
                "AcpiEvGpeDispatch: Unable to queue handler for GPE[%2.2X], event is disabled\n", 
                GpeNumber));
        }
    }
    else
    {
        /* No handler or method to run! */

        ACPI_REPORT_ERROR ((
            "AcpiEvGpeDispatch: No handler or method for GPE[%2.2X], disabling event\n", 
            GpeNumber));

        /*
         * Disable the GPE.  The GPE will remain disabled until the ACPI
         * Core Subsystem is restarted, or the handler is reinstalled.
         */
        Status = AcpiHwDisableGpe (GpeEventInfo);
        if (ACPI_FAILURE (Status))
        {
            ACPI_REPORT_ERROR (("AcpiEvGpeDispatch: Unable to disable GPE[%2.2X]\n", 
                GpeNumber));
            return_VALUE (ACPI_INTERRUPT_NOT_HANDLED);
        }
    }

    /*
     * It is now safe to clear level-triggered evnets.
     */
    if (GpeEventInfo->Type & ACPI_EVENT_LEVEL_TRIGGERED)
    {
        Status = AcpiHwClearGpe (GpeEventInfo);
        if (ACPI_FAILURE (Status))
        {
            ACPI_REPORT_ERROR (("AcpiEvGpeDispatch: Unable to clear GPE[%2.2X]\n", 
                GpeNumber));
            return_VALUE (ACPI_INTERRUPT_NOT_HANDLED);
        }
    }

    return_VALUE (ACPI_INTERRUPT_HANDLED);
}

