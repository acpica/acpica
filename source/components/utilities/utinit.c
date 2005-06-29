
/******************************************************************************
 *
 * Module Name: cminit - Common ACPI subsystem initialization
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


#define __CMINIT_C__

#include "acpi.h"
#include "achware.h"
#include "acnamesp.h"
#include "acevents.h"
#include "acparser.h"
#include "acdispat.h"

#define _COMPONENT          MISCELLANEOUS
        MODULE_NAME         ("cminit");


/*******************************************************************************
 *
 * FUNCTION:    AcpiCmFacpRegisterError
 *
 * PARAMETERS:  *RegisterName           - Pointer to string identifying register
 *              Value                   - Actual register contents value
 *              AcpiTestSpecSection     - TDS section containing assertion
 *              AcpiAssertion           - Assertion number being tested
 *
 * RETURN:      none
 *
 * DESCRIPTION: Display failure message and link failure to TDS assertion
 *
 ******************************************************************************/

void
AcpiCmFacpRegisterError (
    NATIVE_CHAR             *RegisterName,
    UINT32                  Value)
{

    REPORT_ERROR ("Invalid FACP register value");

    DEBUG_PRINT (ACPI_ERROR,
        ("Invalid FACP register value, %s = 0x%X (FACP=0x%X)\n",
        RegisterName, Value, AcpiGbl_FACP));
}


/******************************************************************************
 *
 * FUNCTION:    AcpiCmHardwareInitialize
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Initialize and validate various ACPI registers
 *
 ******************************************************************************/

ACPI_STATUS
AcpiCmHardwareInitialize (void)
{
    ACPI_STATUS             Status = AE_OK;
    UINT32                  Index;


    FUNCTION_TRACE ("CmHardwareInitialize");


    /* Are we running on the actual hardware */

    if (!AcpiGbl_AcpiHardwarePresent)
    {
        /* No, just return */

        return_ACPI_STATUS (AE_OK);
    }

    /* We must have the ACPI tables by the time we get here */

    if (!AcpiGbl_FACP)
    {
        AcpiGbl_RestoreAcpiChipset = FALSE;

        DEBUG_PRINT (ACPI_ERROR, ("CmHardwareInitialize: No FACP!\n"));

        return_ACPI_STATUS (AE_NO_ACPI_TABLES);
    }

    /* Must support *some* mode! */
/*
    if (!(SystemFlags & SYS_MODES_MASK))
    {
        RestoreAcpiChipset = FALSE;

        DEBUG_PRINT (ACPI_ERROR,
            ("CmHardwareInitialize: Supported modes uninitialized!\n"));
        return_ACPI_STATUS (AE_ERROR);
    }

*/


    switch (AcpiGbl_SystemFlags & SYS_MODES_MASK)
    {
        /* Identify current ACPI/legacy mode   */

    case (SYS_MODE_ACPI):

        AcpiGbl_OriginalMode = SYS_MODE_ACPI;
        DEBUG_PRINT (ACPI_INFO, ("System supports ACPI mode only.\n"));
        break;


    case (SYS_MODE_LEGACY):

        AcpiGbl_OriginalMode = SYS_MODE_LEGACY;
        DEBUG_PRINT (ACPI_INFO,
            ("Tables loaded from buffer, hardware assumed to support LEGACY mode only.\n"));
        break;


    case (SYS_MODE_ACPI | SYS_MODE_LEGACY):

        if (AcpiHwGetMode () == SYS_MODE_ACPI)
        {
            AcpiGbl_OriginalMode = SYS_MODE_ACPI;
        }
        else
        {
            AcpiGbl_OriginalMode = SYS_MODE_LEGACY;
        }

        DEBUG_PRINT (ACPI_INFO,
            ("System supports both ACPI and LEGACY modes.\n"));

        DEBUG_PRINT (ACPI_INFO,
            ("System is currently in %s mode.\n",
            (AcpiGbl_OriginalMode == SYS_MODE_ACPI) ? "ACPI" : "LEGACY"));
        break;
    }


    if (AcpiGbl_SystemFlags & SYS_MODE_ACPI)
    {
        /* Target system supports ACPI mode */

        /*
         * The purpose of this block of code is to save the initial state
         * of the ACPI event enable registers. An exit function will be
         * registered which will restore this state when the application
         * exits. The exit function will also clear all of the ACPI event
         * status bits prior to restoring the original mode.
         *
         * The location of the PM1aEvtBlk enable registers is defined as the
         * base of PM1aEvtBlk + PM1aEvtBlkLength / 2. Since the spec further
         * fully defines the PM1aEvtBlk to be a total of 4 bytes, the offset
         * for the enable registers is always 2 from the base. It is hard
         * coded here. If this changes in the spec, this code will need to
         * be modified. The PM1bEvtBlk behaves as expected.
         */

        AcpiGbl_Pm1EnableRegisterSave =
            AcpiOsIn16 ((AcpiGbl_FACP->Pm1aEvtBlk + 2));
        if (AcpiGbl_FACP->Pm1bEvtBlk)
        {
            AcpiGbl_Pm1EnableRegisterSave |=
                AcpiOsIn16 ((AcpiGbl_FACP->Pm1bEvtBlk + 2));
        }


        /*
         * The GPEs behave similarly, except that the length of the register
         * block is not fixed, so the buffer must be allocated with malloc
         */

        if (AcpiGbl_FACP->Gpe0Blk && AcpiGbl_FACP->Gpe0BlkLen)
        {
            /* GPE0 specified in FACP  */

            AcpiGbl_Gpe0EnableRegisterSave =
                AcpiCmAllocate (DIV_2 (AcpiGbl_FACP->Gpe0BlkLen));
            if (!AcpiGbl_Gpe0EnableRegisterSave)
            {
                return_ACPI_STATUS (AE_NO_MEMORY);
            }

            /* Save state of GPE0 enable bits */

            for (Index = 0; Index < DIV_2 (AcpiGbl_FACP->Gpe0BlkLen); Index++)
            {
                AcpiGbl_Gpe0EnableRegisterSave[Index] =
                    AcpiOsIn8 (AcpiGbl_FACP->Gpe0Blk +
                    DIV_2 (AcpiGbl_FACP->Gpe0BlkLen));
            }
        }

        else
        {
            AcpiGbl_Gpe0EnableRegisterSave = NULL;
        }

        if (AcpiGbl_FACP->Gpe1Blk && AcpiGbl_FACP->Gpe1BlkLen)
        {
            /* GPE1 defined */

            AcpiGbl_Gpe1EnableRegisterSave =
                AcpiCmAllocate (DIV_2 (AcpiGbl_FACP->Gpe1BlkLen));
            if (!AcpiGbl_Gpe1EnableRegisterSave)
            {
                return_ACPI_STATUS (AE_NO_MEMORY);
            }

            /* save state of GPE1 enable bits */

            for (Index = 0; Index < DIV_2 (AcpiGbl_FACP->Gpe1BlkLen); Index++)
            {
                AcpiGbl_Gpe1EnableRegisterSave[Index] =
                    AcpiOsIn8 (AcpiGbl_FACP->Gpe1Blk +
                    DIV_2 (AcpiGbl_FACP->Gpe1BlkLen));
            }
        }

        else
        {
            AcpiGbl_Gpe1EnableRegisterSave = NULL;
        }


        /*
         * Verify Fixed ACPI Description Table fields,
         * but don't abort on any problems, just display error
         */

        if (AcpiGbl_FACP->Pm1EvtLen < 4)
        {
            AcpiCmFacpRegisterError ("PM1_EVT_LEN",
                                    (UINT32) AcpiGbl_FACP->Pm1EvtLen);
        }

        if (!AcpiGbl_FACP->Pm1CntLen)
        {
            AcpiCmFacpRegisterError ("PM1_CNT_LEN",
                                    (UINT32) AcpiGbl_FACP->Pm1CntLen);
        }

        if (!AcpiGbl_FACP->Pm1aEvtBlk)
        {
            AcpiCmFacpRegisterError ("PM1a_EVT_BLK", AcpiGbl_FACP->Pm1aEvtBlk);
        }

        if (!AcpiGbl_FACP->Pm1aCntBlk)
        {
            AcpiCmFacpRegisterError ("PM1a_CNT_BLK", AcpiGbl_FACP->Pm1aCntBlk);
        }

        if (!AcpiGbl_FACP->PmTmrBlk)
        {
            AcpiCmFacpRegisterError ("PM_TMR_BLK", AcpiGbl_FACP->PmTmrBlk);
        }

        if (AcpiGbl_FACP->Pm2CntBlk && !AcpiGbl_FACP->Pm2CntLen)
        {
            AcpiCmFacpRegisterError ("PM2_CNT_LEN",
                                    (UINT32) AcpiGbl_FACP->Pm2CntLen);
        }

        if (AcpiGbl_FACP->PmTmLen < 4)
        {
            AcpiCmFacpRegisterError ("PM_TM_LEN",
                                    (UINT32) AcpiGbl_FACP->PmTmLen);
        }

        /* length not multiple of 2    */
        if (AcpiGbl_FACP->Gpe0Blk && (AcpiGbl_FACP->Gpe0BlkLen & 1))
        {
            AcpiCmFacpRegisterError ("GPE0_BLK_LEN",
                                    (UINT32) AcpiGbl_FACP->Gpe0BlkLen);
        }

        /* length not multiple of 2    */
        if (AcpiGbl_FACP->Gpe1Blk && (AcpiGbl_FACP->Gpe1BlkLen & 1))
        {
            AcpiCmFacpRegisterError ("GPE1_BLK_LEN",
                                    (UINT32) AcpiGbl_FACP->Gpe1BlkLen);
        }
    }


    return_ACPI_STATUS (Status);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiCmTerminate
 *
 * PARAMETERS:  none
 *
 * RETURN:      none
 *
 * DESCRIPTION: free memory allocated for table storage.
 *
 ******************************************************************************/

void
AcpiCmTerminate (void)
{

    FUNCTION_TRACE ("CmTerminate");


    /* Free global tables, etc. */

    if (AcpiGbl_Gpe0EnableRegisterSave)
    {
        AcpiCmFree (AcpiGbl_Gpe0EnableRegisterSave);
    }

    if (AcpiGbl_Gpe1EnableRegisterSave)
    {
        AcpiCmFree (AcpiGbl_Gpe1EnableRegisterSave);
    }


    return_VOID;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiCmSubsystemShutdown
 *
 * PARAMETERS:  none
 *
 * RETURN:      none
 *
 * DESCRIPTION: Shutdown the various subsystems.  Don't delete the mutex
 *              objects here -- because the AML debugger may be still running.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiCmSubsystemShutdown (void)
{

    FUNCTION_TRACE ("CmSubsystemShutdown");

    /* Just exit if subsystem is already shutdown */

    if (AcpiGbl_Shutdown)
    {
        DEBUG_PRINT (ACPI_ERROR, ("ACPI Subsystem is already terminated\n"));
        return_ACPI_STATUS (AE_OK);
    }

    /* Subsystem appears active, go ahead and shut it down */

    AcpiGbl_Shutdown = TRUE;
    DEBUG_PRINT (ACPI_INFO, ("Shutting down ACPI Subsystem...\n"));


    /* Close the Namespace */

    AcpiNsTerminate ();

    /* Close the AcpiEvent Handling */

    AcpiEvTerminate ();

    /* Close the globals */

    AcpiCmTerminate ();

    /* Flush the local cache(s) */

    AcpiCmDeleteGenericStateCache ();
    AcpiCmDeleteObjectCache ();
    AcpiDsDeleteWalkStateCache ();

    /* Close the Parser */

    /* TBD: [Restructure] AcpiPsTerminate () */

    AcpiPsDeleteParseCache ();

    /* Debug only - display leftover memory allocation, if any */
#ifdef ENABLE_DEBUGGER
    AcpiCmDumpCurrentAllocations (ACPI_UINT32_MAX, NULL);
#endif

    BREAKPOINT3;

    return_ACPI_STATUS (AE_OK);
}


