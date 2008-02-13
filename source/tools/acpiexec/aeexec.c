/******************************************************************************
 *
 * Module Name: aeexec - Support routines for AcpiExec utility
 *              $Revision: 1.129 $
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2008, Intel Corp.
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

#include "aecommon.h"

#define _COMPONENT          ACPI_TOOLS
        ACPI_MODULE_NAME    ("aeexec")


ACPI_PARSE_OBJECT           *root;
UINT8                       *AmlStart;
UINT32                      AmlLength;
UINT8                       *DsdtPtr;
UINT32                      AcpiDsdtLength;

DEBUG_REGIONS               AeRegions;
ACPI_TABLE_RSDP             LocalRsdp;

/*
 * Misc ACPI tables to be installed
 */
unsigned char Ssdt1Code[] =
{
    0x53,0x53,0x44,0x54,0x30,0x00,0x00,0x00,  /* 00000000    "SSDT0..." */
    0x01,0xB8,0x49,0x6E,0x74,0x65,0x6C,0x00,  /* 00000008    "..Intel." */
    0x4D,0x61,0x6E,0x79,0x00,0x00,0x00,0x00,  /* 00000010    "Many...." */
    0x01,0x00,0x00,0x00,0x49,0x4E,0x54,0x4C,  /* 00000018    "....INTL" */
    0x24,0x04,0x03,0x20,0x14,0x0B,0x5F,0x54,  /* 00000020    "$.. .._T" */
    0x39,0x38,0x00,0x70,0x0A,0x04,0x60,0xA4,  /* 00000028    "98.p..`." */
};

unsigned char Ssdt2Code[] =
{
    0x53,0x53,0x44,0x54,0x30,0x00,0x00,0x00,  /* 00000000    "SSDT0..." */
    0x01,0xB7,0x49,0x6E,0x74,0x65,0x6C,0x00,  /* 00000008    "..Intel." */
    0x4D,0x61,0x6E,0x79,0x00,0x00,0x00,0x00,  /* 00000010    "Many...." */
    0x01,0x00,0x00,0x00,0x49,0x4E,0x54,0x4C,  /* 00000018    "....INTL" */
    0x24,0x04,0x03,0x20,0x14,0x0B,0x5F,0x54,  /* 00000020    "$.. .._T" */
    0x39,0x39,0x00,0x70,0x0A,0x04,0x60,0xA4,  /* 00000028    "99.p..`." */
};

unsigned char Oem1Code[] =
{
    0x4F,0x45,0x4D,0x31,0x38,0x00,0x00,0x00,  /* 00000000    "OEM18..." */
    0x01,0x4B,0x49,0x6E,0x74,0x65,0x6C,0x00,  /* 00000008    ".KIntel." */
    0x4D,0x61,0x6E,0x79,0x00,0x00,0x00,0x00,  /* 00000010    "Many...." */
    0x01,0x00,0x00,0x00,0x49,0x4E,0x54,0x4C,  /* 00000018    "....INTL" */
    0x18,0x09,0x03,0x20,0x08,0x5F,0x58,0x54,  /* 00000020    "... ._XT" */
    0x32,0x0A,0x04,0x14,0x0C,0x5F,0x58,0x54,  /* 00000028    "2...._XT" */
    0x31,0x00,0x70,0x01,0x5F,0x58,0x54,0x32,  /* 00000030    "1.p._XT2" */
};

/*
 * We need a local FADT so that the hardware subcomponent will function,
 * even though the underlying OSD HW access functions don't do
 * anything.
 */
ACPI_TABLE_RSDP             LocalRSDP;
ACPI_TABLE_FADT             LocalFADT;
ACPI_TABLE_FACS             LocalFACS;
ACPI_TABLE_HEADER           LocalDSDT;
ACPI_TABLE_HEADER           LocalTEST;
ACPI_TABLE_HEADER           LocalBADTABLE;

ACPI_TABLE_RSDT             *LocalRSDT;

#define RSDT_TABLES         7
#define RSDT_SIZE           (sizeof (ACPI_TABLE_RSDT) + ((RSDT_TABLES -1) * sizeof (UINT32)))

#define ACPI_MAX_INIT_TABLES (16)
static ACPI_TABLE_DESC      Tables[ACPI_MAX_INIT_TABLES];

UINT32                      SigintCount = 0;

/******************************************************************************
 *
 * FUNCTION:    AeCtrlCHandler
 *
 * PARAMETERS:  Sig
 *
 * RETURN:      none
 *
 * DESCRIPTION: Control-C handler.  Abort running control method if any.
 *
 *****************************************************************************/

void __cdecl
AeCtrlCHandler (
    int                     Sig)
{

    signal (SIGINT, SIG_IGN);
    SigintCount++;

    AcpiOsPrintf ("Caught a ctrl-c (#%d)\n\n", SigintCount);

    if (AcpiGbl_MethodExecuting)
    {
        AcpiGbl_AbortMethod = TRUE;
        signal (SIGINT, AeCtrlCHandler);

        if (SigintCount < 10)
        {
            return;
        }
    }

    exit (0);
}


/******************************************************************************
 *
 * FUNCTION:    AeBuildLocalTables
 *
 * PARAMETERS:
 *
 * RETURN:      Status
 *
 * DESCRIPTION:
 *
 *****************************************************************************/

ACPI_STATUS
AeBuildLocalTables (
    ACPI_TABLE_HEADER       *UserTable)
{
    ACPI_PHYSICAL_ADDRESS   DsdtAddress;


    /* Build an RSDT */

    LocalRSDT = AcpiOsAllocate (RSDT_SIZE);
    if (!LocalRSDT)
    {
        return AE_NO_MEMORY;
    }

    ACPI_MEMSET (LocalRSDT, 0, RSDT_SIZE);
    ACPI_STRNCPY (LocalRSDT->Header.Signature, ACPI_SIG_RSDT, 4);
    LocalRSDT->Header.Length = RSDT_SIZE;

    LocalRSDT->TableOffsetEntry[0] = ACPI_PTR_TO_PHYSADDR (&LocalTEST);
    LocalRSDT->TableOffsetEntry[1] = ACPI_PTR_TO_PHYSADDR (&LocalBADTABLE);
    LocalRSDT->TableOffsetEntry[2] = ACPI_PTR_TO_PHYSADDR (&LocalFADT);
    LocalRSDT->TableOffsetEntry[3] = ACPI_PTR_TO_PHYSADDR (&LocalTEST);  /* Just a placeholder for a user SSDT */

    /* Install two SSDTs to test multiple table support */

    LocalRSDT->TableOffsetEntry[4] = ACPI_PTR_TO_PHYSADDR (&Ssdt1Code);
    LocalRSDT->TableOffsetEntry[5] = ACPI_PTR_TO_PHYSADDR (&Ssdt2Code);

    /* Install the OEM1 table to test LoadTable */

    LocalRSDT->TableOffsetEntry[6] = ACPI_PTR_TO_PHYSADDR (&Oem1Code);

    /* Build an RSDP */

    ACPI_MEMSET (&LocalRSDP, 0, sizeof (ACPI_TABLE_RSDP));
    ACPI_MEMCPY (LocalRSDP.Signature, ACPI_SIG_RSDP, 8);
    LocalRSDP.Revision = 1;
    LocalRSDP.RsdtPhysicalAddress = ACPI_PTR_TO_PHYSADDR (LocalRSDT);
    LocalRSDP.Length = sizeof (ACPI_TABLE_RSDT);
    ACPI_MEMCPY (LocalRSDP.OemId, "I_TEST", 6);

    /*
     * Examine the incoming user table.  At this point, it has been verified
     * to be either a DSDT, SSDT, or a PSDT, but they must be handled differently
     */
    if (ACPI_COMPARE_NAME (UserTable->Signature, ACPI_SIG_DSDT))
    {
        /* The incoming user table is a DSDT */

        DsdtAddress = ACPI_PTR_TO_PHYSADDR (UserTable);
    }
    else
    {
        /* Build a local DSDT because incoming table is an SSDT or PSDT */

        ACPI_MEMSET (&LocalDSDT, 0, sizeof (ACPI_TABLE_HEADER));
        ACPI_STRNCPY (LocalDSDT.Signature, ACPI_SIG_DSDT, 4);
        LocalDSDT.Revision = 1;
        LocalDSDT.Length = sizeof (ACPI_TABLE_HEADER);
        LocalDSDT.Checksum = (UINT8) -AcpiTbChecksum ((void *) &LocalDSDT, LocalDSDT.Length);

        /* Install incoming table (SSDT or PSDT) directly into the RSDT */

        LocalRSDT->TableOffsetEntry[3] = ACPI_PTR_TO_PHYSADDR (UserTable);
        DsdtAddress = ACPI_PTR_TO_PHYSADDR (&LocalDSDT);
    }

    /* Set checksums for both RSDT and RSDP */

    LocalRSDT->Header.Checksum = (UINT8) -AcpiTbChecksum ((void *) LocalRSDT, LocalRSDT->Header.Length);
    LocalRSDP.Checksum = (UINT8) -AcpiTbChecksum ((void *) &LocalRSDP, ACPI_RSDP_CHECKSUM_LENGTH);

    /*
     * Build a FADT so we can test the hardware/event init
     */
    ACPI_MEMSET (&LocalFADT, 0, sizeof (ACPI_TABLE_FADT));
    ACPI_STRNCPY (LocalFADT.Header.Signature, ACPI_SIG_FADT, 4);

    /* Setup FADT header and DSDT/FACS addresses */

    if (ACPI_MACHINE_WIDTH == 32)
    {
        /* Short (V1) FADT used for 32-bit case */

        LocalFADT.Dsdt = DsdtAddress;
        LocalFADT.Facs = ACPI_PTR_TO_PHYSADDR (&LocalFACS);

        LocalFADT.Header.Revision = 1;
        LocalFADT.Header.Length = ACPI_FADT_OFFSET (Flags);
    }
    else
    {
        /* Long (V2) FADT used for 64-bit case */

        LocalFADT.XDsdt = DsdtAddress;
        LocalFADT.XFacs = ACPI_PTR_TO_PHYSADDR (&LocalFACS);

        LocalFADT.Header.Revision = 2;
        LocalFADT.Header.Length = sizeof (ACPI_TABLE_FADT);
    }

    /* Miscellaneous FADT fields */

    LocalFADT.Gpe0BlockLength = 16;
    LocalFADT.Gpe1BlockLength = 6;
    LocalFADT.Gpe1Base = 96;

    LocalFADT.Pm1EventLength = 4;
    LocalFADT.Pm1ControlLength = 4;
    LocalFADT.PmTimerLength  = 8;

    LocalFADT.Gpe0Block = 0x12340000;
    LocalFADT.Gpe1Block = 0x56780000;

    LocalFADT.Pm1aEventBlock = 0x1aaa0000;
    LocalFADT.Pm1bEventBlock = 0;
    LocalFADT.PmTimerBlock = 0xA0;
    LocalFADT.Pm1aControlBlock = 0xB0;

    /* Complete the FADT with the checksum */

    LocalFADT.Header.Checksum = 0;
    LocalFADT.Header.Checksum = (UINT8) -AcpiTbChecksum ((void *) &LocalFADT, LocalFADT.Header.Length);

    /* Build a FACS */

    ACPI_MEMSET (&LocalFACS, 0, sizeof (ACPI_TABLE_FACS));
    ACPI_STRNCPY (LocalFACS.Signature, ACPI_SIG_FACS, 4);
    LocalFACS.Length = sizeof (ACPI_TABLE_FACS);
    LocalFACS.GlobalLock = 0x11AA0011;

    /* Build a fake table [TEST] so that we make sure that the CA core ignores it */

    ACPI_MEMSET (&LocalTEST, 0, sizeof (ACPI_TABLE_HEADER));
    ACPI_STRNCPY (LocalTEST.Signature, "TEST", 4);

    LocalTEST.Revision = 1;
    LocalTEST.Length = sizeof (ACPI_TABLE_HEADER);
    LocalTEST.Checksum = (UINT8) -AcpiTbChecksum ((void *) &LocalTEST, LocalTEST.Length);

    /* Build a fake table with a bad signature [BAD!] so that we make sure that the CA core ignores it */

    ACPI_MEMSET (&LocalBADTABLE, 0, sizeof (ACPI_TABLE_HEADER));
    ACPI_STRNCPY (LocalBADTABLE.Signature, "BAD!", 4);

    LocalBADTABLE.Revision = 1;
    LocalBADTABLE.Length = sizeof (ACPI_TABLE_HEADER);
    LocalBADTABLE.Checksum = (UINT8) -AcpiTbChecksum ((void *) &LocalBADTABLE, LocalBADTABLE.Length);

    return (AE_OK);
}


/******************************************************************************
 *
 * FUNCTION:    AeInstallTables
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install the various ACPI tables
 *
 *****************************************************************************/

ACPI_STATUS
AeInstallTables (
    void)
{
    ACPI_STATUS             Status;

    Status = AcpiInitializeTables (Tables, ACPI_MAX_INIT_TABLES, TRUE);
    Status = AcpiReallocateRootTable ();
    Status = AcpiLoadTables ();
    return (Status);
}


/******************************************************************************
 *
 * FUNCTION:    AeLocalGetRootPointer
 *
 * PARAMETERS:  Flags       - not used
 *              Address     - Where the root pointer is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Return a local RSDP, used to dynamically load tables via the
 *              standard ACPI mechanism.
 *
 *****************************************************************************/

ACPI_PHYSICAL_ADDRESS
AeLocalGetRootPointer (
    void)
{

    return ((ACPI_PHYSICAL_ADDRESS) &LocalRSDP);
}


/******************************************************************************
 *
 * FUNCTION:    AeRegionHandler
 *
 * PARAMETERS:  Standard region handler parameters
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Test handler - Handles some dummy regions via memory that can
 *              be manipulated in Ring 3.
 *
 *****************************************************************************/

ACPI_STATUS
AeRegionHandler (
    UINT32                  Function,
    ACPI_PHYSICAL_ADDRESS   Address,
    UINT32                  BitWidth,
    ACPI_INTEGER            *Value,
    void                    *HandlerContext,
    void                    *RegionContext)
{

    ACPI_OPERAND_OBJECT     *RegionObject = (ACPI_OPERAND_OBJECT*) RegionContext;
    ACPI_PHYSICAL_ADDRESS   BaseAddress;
    ACPI_SIZE               Length;
    BOOLEAN                 BufferExists;
    REGION                  *RegionElement;
    void                    *BufferValue;
    UINT32                  ByteWidth;
    UINT32                  i;
    UINT8                   SpaceId;


    ACPI_FUNCTION_NAME (AeRegionHandler);

    /*
     * If the object is not a region, simply return
     */
    if (RegionObject->Region.Type != ACPI_TYPE_REGION)
    {
        return AE_OK;
    }

    /*
     * Find the region's address space and length before searching
     * the linked list.
     */
    BaseAddress = RegionObject->Region.Address;
    Length = (ACPI_SIZE) RegionObject->Region.Length;
    SpaceId = RegionObject->Region.SpaceId;

    ACPI_DEBUG_PRINT ((ACPI_DB_OPREGION, "Operation Region request on %s at 0x%X\n",
            AcpiUtGetRegionName (RegionObject->Region.SpaceId),
            (UINT32) Address));

    if (SpaceId == ACPI_ADR_SPACE_SMBUS)
    {
        Length = 0;

        switch (Function & ACPI_IO_MASK)
        {
        case ACPI_READ:
            switch (Function >> 16)
            {
            case AML_FIELD_ATTRIB_SMB_QUICK:
            case AML_FIELD_ATTRIB_SMB_SEND_RCV:
            case AML_FIELD_ATTRIB_SMB_BYTE:
                Length = 1;
                break;

            case AML_FIELD_ATTRIB_SMB_WORD:
            case AML_FIELD_ATTRIB_SMB_WORD_CALL:
                Length = 2;
                break;

            case AML_FIELD_ATTRIB_SMB_BLOCK:
            case AML_FIELD_ATTRIB_SMB_BLOCK_CALL:
                Length = 32;
                break;

            default:
                break;
            }
            break;

        case ACPI_WRITE:
            switch (Function >> 16)
            {
            case AML_FIELD_ATTRIB_SMB_QUICK:
            case AML_FIELD_ATTRIB_SMB_SEND_RCV:
            case AML_FIELD_ATTRIB_SMB_BYTE:
            case AML_FIELD_ATTRIB_SMB_WORD:
            case AML_FIELD_ATTRIB_SMB_BLOCK:
                Length = 0;
                break;

            case AML_FIELD_ATTRIB_SMB_WORD_CALL:
                Length = 2;
                break;

            case AML_FIELD_ATTRIB_SMB_BLOCK_CALL:
                Length = 32;
                break;

            default:
                break;
            }
            break;

        default:
            break;
        }

        for (i = 0; i < Length; i++)
        {
            ((UINT8 *) Value)[i+2] = (UINT8) (0xA0 + i);
        }

        ((UINT8 *) Value)[0] = 0x7A;
        ((UINT8 *) Value)[1] = (UINT8) Length;

        return AE_OK;
    }

    /*
     * Search through the linked list for this region's buffer
     */
    BufferExists = FALSE;
    RegionElement = AeRegions.RegionList;

    if (AeRegions.NumberOfRegions)
    {
        while (!BufferExists && RegionElement)
        {
            if (RegionElement->Address == BaseAddress &&
                RegionElement->Length == Length &&
                RegionElement->SpaceId == SpaceId)
            {
                BufferExists = TRUE;
            }
            else
            {
                RegionElement = RegionElement->NextRegion;
            }
        }
    }

    /*
     * If the Region buffer does not exist, create it now
     */
    if (!BufferExists)
    {
        /*
         * Do the memory allocations first
         */
        RegionElement = AcpiOsAllocate (sizeof (REGION));
        if (!RegionElement)
        {
            return AE_NO_MEMORY;
        }

        RegionElement->Buffer = AcpiOsAllocate (Length);
        if (!RegionElement->Buffer)
        {
            AcpiOsFree (RegionElement);
            return AE_NO_MEMORY;
        }

        ACPI_MEMSET (RegionElement->Buffer, 0, Length);
        RegionElement->Address      = BaseAddress;
        RegionElement->Length       = Length;
        RegionElement->SpaceId      = SpaceId;
        RegionElement->NextRegion   = NULL;

        /*
         * Increment the number of regions and put this one
         *  at the head of the list as it will probably get accessed
         *  more often anyway.
         */
        AeRegions.NumberOfRegions += 1;

        if (AeRegions.RegionList)
        {
            RegionElement->NextRegion = AeRegions.RegionList;
        }

        AeRegions.RegionList = RegionElement;
    }

    /*
     * Calculate the size of the memory copy
     */
    ByteWidth = (BitWidth / 8);

    if (BitWidth % 8)
    {
        ByteWidth += 1;
    }

    /*
     * The buffer exists and is pointed to by RegionElement.
     * We now need to verify the request is valid and perform the operation.
     *
     * NOTE: RegionElement->Length is in bytes, therefore it we compare against
     * ByteWidth (see above)
     */
    if (((ACPI_INTEGER) Address + ByteWidth) >
        ((ACPI_INTEGER)(RegionElement->Address) + RegionElement->Length))
    {
        ACPI_WARNING ((AE_INFO,
            "Request on [%4.4s] is beyond region limit Req-%X+%X, Base=%X, Len-%X",
            (RegionObject->Region.Node)->Name.Ascii, (UINT32) Address,
            ByteWidth, (UINT32)(RegionElement->Address),
            RegionElement->Length));

        return AE_AML_REGION_LIMIT;
    }

    /*
     * Get BufferValue to point to the "address" in the buffer
     */
    BufferValue = ((UINT8 *) RegionElement->Buffer +
                    ((ACPI_INTEGER) Address - (ACPI_INTEGER) RegionElement->Address));

    /*
     * Perform a read or write to the buffer space
     */
    switch (Function)
    {
    case ACPI_READ:
        /*
         * Set the pointer Value to whatever is in the buffer
         */
        ACPI_MEMCPY (Value, BufferValue, ByteWidth);
        break;

    case ACPI_WRITE:
        /*
         * Write the contents of Value to the buffer
         */
        ACPI_MEMCPY (BufferValue, Value, ByteWidth);
        break;

    default:
        return AE_BAD_PARAMETER;
    }
    return AE_OK;
}


/******************************************************************************
 *
 * FUNCTION:    AeRegionInit
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Opregion init function.
 *
 *****************************************************************************/

ACPI_STATUS
AeRegionInit (
    ACPI_HANDLE                 RegionHandle,
    UINT32                      Function,
    void                        *HandlerContext,
    void                        **RegionContext)
{
    /*
     * Real simple, set the RegionContext to the RegionHandle
     */
    *RegionContext = RegionHandle;

    return AE_OK;
}


/******************************************************************************
 *
 * FUNCTION:    AeNotifyHandler
 *
 * PARAMETERS:  Standard notify handler parameters
 *
 * RETURN:      Status
 *
 * DESCRIPTION: System notify handler for AcpiExec utility.  Used by the ASL
 *              test suite(s) to communicate errors and other information to
 *              this utility via the Notify() operator.
 *
 *****************************************************************************/

void
AeNotifyHandler (
    ACPI_HANDLE                 Device,
    UINT32                      Value,
    void                        *Context)
{

    switch (Value)
    {
#if 0
    case 0:
        printf ("**** Method Error 0x%X: Results not equal\n", Value);
        if (AcpiGbl_DebugFile)
        {
            AcpiOsPrintf ("**** Method Error: Results not equal\n");
        }
        break;


    case 1:
        printf ("**** Method Error: Incorrect numeric result\n");
        if (AcpiGbl_DebugFile)
        {
            AcpiOsPrintf ("**** Method Error: Incorrect numeric result\n");
        }
        break;


    case 2:
        printf ("**** Method Error: An operand was overwritten\n");
        if (AcpiGbl_DebugFile)
        {
            AcpiOsPrintf ("**** Method Error: An operand was overwritten\n");
        }
        break;

#endif

    default:
        printf ("**** Received a Notify on Device [%4.4s] %p value 0x%X\n",
            AcpiUtGetNodeName (Device), Device, Value);
        if (AcpiGbl_DebugFile)
        {
            AcpiOsPrintf ("**** Received a notify, value 0x%X\n", Value);
        }

        (void) AcpiEvaluateObject (Device, "_NOT", NULL, NULL);
        break;
    }

}


/******************************************************************************
 *
 * FUNCTION:    AeExceptionHandler
 *
 * PARAMETERS:  Standard exception handler parameters
 *
 * RETURN:      Status
 *
 * DESCRIPTION: System exception handler for AcpiExec utility.
 *
 *****************************************************************************/

ACPI_STATUS
AeExceptionHandler (
    ACPI_STATUS             AmlStatus,
    ACPI_NAME               Name,
    UINT16                  Opcode,
    UINT32                  AmlOffset,
    void                    *Context)
{
    ACPI_STATUS             NewAmlStatus = AmlStatus;
    ACPI_STATUS             Status;
    ACPI_BUFFER             ReturnObj;
    ACPI_OBJECT_LIST        ArgList;
    ACPI_OBJECT             Arg[3];
    const char              *Exception;


    Exception = AcpiFormatException (AmlStatus);
    AcpiOsPrintf ("**** AcpiExec: Exception %s during execution ", Exception);
    if (Name)
    {
        AcpiOsPrintf ("of method [%4.4s]", (char *) &Name);
    }
    else
    {
        AcpiOsPrintf ("at module level (table load)");
    }
    AcpiOsPrintf (" Opcode [%s] @%X\n", AcpiPsGetOpcodeName (Opcode), AmlOffset);

    /*
     * Invoke the _ERR method if present
     *
     * Setup parameter object
     */
    ArgList.Count = 3;
    ArgList.Pointer = Arg;

    Arg[0].Type = ACPI_TYPE_INTEGER;
    Arg[0].Integer.Value = AmlStatus;

    Arg[1].Type = ACPI_TYPE_STRING;
    Arg[1].String.Pointer = (char *) Exception;
    Arg[1].String.Length = ACPI_STRLEN (Exception);

    Arg[2].Type = ACPI_TYPE_INTEGER;
    Arg[2].Integer.Value = AcpiOsGetThreadId();

    /* Setup return buffer */

    ReturnObj.Pointer = NULL;
    ReturnObj.Length = ACPI_ALLOCATE_BUFFER;

    Status = AcpiEvaluateObject (NULL, "\\_ERR", &ArgList, &ReturnObj);
    if (ACPI_SUCCESS (Status))
    {
        if (ReturnObj.Pointer)
        {
            /* Override original status */

            NewAmlStatus = (ACPI_STATUS)
                ((ACPI_OBJECT *) ReturnObj.Pointer)->Integer.Value;

            AcpiOsFree (ReturnObj.Pointer);
        }
    }
    else if (Status != AE_NOT_FOUND)
    {
        AcpiOsPrintf ("**** AcpiExec: Could not execute _ERR method, %s\n",
            AcpiFormatException (Status));
    }

    /* Global override */

    if (AcpiGbl_IgnoreErrors)
    {
        NewAmlStatus = AE_OK;
    }

    if (NewAmlStatus != AmlStatus)
    {
        AcpiOsPrintf ("**** AcpiExec: Exception override, new status %s\n",
            AcpiFormatException (NewAmlStatus));
    }

    return (NewAmlStatus);
}


/******************************************************************************
 *
 * FUNCTION:    AeTableHandler
 *
 * PARAMETERS:  Table handler
 *
 * RETURN:      Status
 *
 * DESCRIPTION: System table handler for AcpiExec utility.
 *
 *****************************************************************************/

char                *TableEvents[] =
{
    "LOAD",
    "UNLOAD",
    "UNKNOWN"
};

ACPI_STATUS
AeTableHandler (
    UINT32                  Event,
    void                    *Table,
    void                    *Context)
{

    if (Event > ACPI_NUM_TABLE_EVENTS)
    {
        Event = ACPI_NUM_TABLE_EVENTS;
    }

    /* TBD: could dump entire table header, need a header dump routine */

    printf ("**** AcpiExec: Table Event %s, [%4.4s] %p\n",
        TableEvents[Event], ((ACPI_TABLE_HEADER *) Table)->Signature, Table);
    return (AE_OK);
}


/******************************************************************************
 *
 * FUNCTION:    AeInstallHandlers
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install handlers for the AcpiExec utility.
 *              NOTE: Currently only a system notify handler is installed.
 *
 *****************************************************************************/

ACPI_ADR_SPACE_TYPE         SpaceId[] = {0, 1, 2, 3, 4, 5, 6, 0x80};
#define AEXEC_NUM_REGIONS   8

ACPI_STATUS
AeInstallHandlers (void)
{
    ACPI_STATUS             Status;
    UINT32                  i;
    ACPI_HANDLE             Handle;


    ACPI_FUNCTION_ENTRY ();


    Status = AcpiInstallTableHandler (AeTableHandler, NULL);
    if (ACPI_FAILURE (Status))
    {
        printf ("Could not install table handler, %s\n",
            AcpiFormatException (Status));
    }

    Status = AcpiInstallExceptionHandler (AeExceptionHandler);
    if (ACPI_FAILURE (Status))
    {
        printf ("Could not install exception handler, %s\n",
            AcpiFormatException (Status));
    }

    Status = AcpiInstallNotifyHandler (ACPI_ROOT_OBJECT, ACPI_SYSTEM_NOTIFY,
                                        AeNotifyHandler, NULL);
    if (ACPI_FAILURE (Status))
    {
        printf ("Could not install a global notify handler, %s\n",
            AcpiFormatException (Status));
    }

    Status = AcpiGetHandle (NULL, "\\_SB", &Handle);
    if (ACPI_SUCCESS (Status))
    {
        Status = AcpiInstallNotifyHandler (Handle, ACPI_SYSTEM_NOTIFY,
                                            AeNotifyHandler, NULL);
        if (ACPI_FAILURE (Status))
        {
            printf ("Could not install a notify handler, %s\n",
                AcpiFormatException (Status));
        }

        Status = AcpiRemoveNotifyHandler (Handle, ACPI_SYSTEM_NOTIFY,
                                            AeNotifyHandler);
        if (ACPI_FAILURE (Status))
        {
            printf ("Could not remove a notify handler, %s\n",
                AcpiFormatException (Status));
        }

        Status = AcpiInstallNotifyHandler (Handle, ACPI_ALL_NOTIFY,
                                            AeNotifyHandler, NULL);
        Status = AcpiRemoveNotifyHandler (Handle, ACPI_ALL_NOTIFY,
                                            AeNotifyHandler);
        Status = AcpiInstallNotifyHandler (Handle, ACPI_ALL_NOTIFY,
                                            AeNotifyHandler, NULL);
        if (ACPI_FAILURE (Status))
        {
            printf ("Could not install a notify handler, %s\n",
                AcpiFormatException (Status));
        }
    }
    else
    {
        printf ("No _SB_ found, %s\n", AcpiFormatException (Status));
    }

    /* Set a handler for all supported operation regions */

    for (i = 0; i < AEXEC_NUM_REGIONS; i++)
    {
        Status = AcpiRemoveAddressSpaceHandler (AcpiGbl_RootNode,
                        SpaceId[i], AeRegionHandler);

        /* Install handler at the root object.
         * TBD: all default handlers should be installed here!
         */
        Status = AcpiInstallAddressSpaceHandler (AcpiGbl_RootNode,
                        SpaceId[i], AeRegionHandler, AeRegionInit, NULL);
        if (ACPI_FAILURE (Status))
        {
            ACPI_EXCEPTION ((AE_INFO, Status,
                "Could not install an OpRegion handler for %s space(%d)",
                AcpiUtGetRegionName((UINT8) SpaceId[i]), SpaceId[i]));
            return (Status);
        }
    }

    /*
     * Initialize the global Region Handler space
     * MCW 3/23/00
     */
    AeRegions.NumberOfRegions = 0;
    AeRegions.RegionList = NULL;

    return Status;
}


/******************************************************************************
 *
 * FUNCTION:    AeGpeHandler
 *
 * DESCRIPTION: GPE handler for acpiexec
 *
 *****************************************************************************/

UINT32
AeGpeHandler (
    void                        *Context)
{


    AcpiOsPrintf ("Received a GPE at handler\n");
    return (0);
}


/******************************************************************************
 *
 * FUNCTION:    AfInstallGpeBlock
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Various GPE initialization
 *
 *****************************************************************************/

void
AfInstallGpeBlock (
    void)
{
    ACPI_STATUS                 Status;
    ACPI_HANDLE                 Handle;
    ACPI_HANDLE                 Handle2 = NULL;
    ACPI_HANDLE                 Handle3 = NULL;
    ACPI_GENERIC_ADDRESS        BlockAddress;


    Status = AcpiGetHandle (NULL, "\\_GPE", &Handle);
    if (ACPI_FAILURE (Status))
    {
        return;
    }

    BlockAddress.SpaceId = 0;
    BlockAddress.Address = 0x76540000;

//    Status = AcpiInstallGpeBlock (Handle, &BlockAddress, 4, 8);

    /* Above should fail, ignore */

    Status = AcpiGetHandle (NULL, "\\GPE2", &Handle2);
    if (ACPI_SUCCESS (Status))
    {
        Status = AcpiInstallGpeBlock (Handle2, &BlockAddress, 8, 8);

        AcpiInstallGpeHandler (Handle2, 8, ACPI_GPE_LEVEL_TRIGGERED, AeGpeHandler, NULL);
        AcpiSetGpeType (Handle2, 8, ACPI_GPE_TYPE_WAKE);
        AcpiEnableGpe (Handle2, 8, 0);
    }

    Status = AcpiGetHandle (NULL, "\\GPE3", &Handle3);
    if (ACPI_SUCCESS (Status))
    {
        Status = AcpiInstallGpeBlock (Handle3, &BlockAddress, 8, 11);
    }

//    Status = AcpiRemoveGpeBlock (Handle);
//    Status = AcpiRemoveGpeBlock (Handle2);
//    Status = AcpiRemoveGpeBlock (Handle3);

}


/* Test using a Buffer object as a method argument */

void
AeTestBufferArgument (void)
{
    ACPI_STATUS             Status;
    ACPI_OBJECT_LIST        Params;
    ACPI_OBJECT             BufArg;
    UINT8                   Buffer[] = {
        0,0,0,0,
        4,0,0,0,
        1,2,3,4};


    BufArg.Type = ACPI_TYPE_BUFFER;
    BufArg.Buffer.Length = 12;
    BufArg.Buffer.Pointer = Buffer;

    Params.Count = 1;
    Params.Pointer = &BufArg;


    Status = AcpiEvaluateObject (NULL, "\\BUF", &Params, NULL);
}


ACPI_OBJECT                 PkgArg;
ACPI_OBJECT                 PkgElements[5];
ACPI_OBJECT                 Pkg2Elements[5];
ACPI_OBJECT_LIST            Params;


/*
 * Test using a Package object as an method argument
 */
void
AeTestPackageArgument (
    void)
{
    ACPI_STATUS             Status;


    /* Main package */

    PkgArg.Type = ACPI_TYPE_PACKAGE;
    PkgArg.Package.Count = 4;
    PkgArg.Package.Elements = PkgElements;

    /* Main package elements */

    PkgElements[0].Type = ACPI_TYPE_INTEGER;
    PkgElements[0].Integer.Value = 0x22228888;

    PkgElements[1].Type = ACPI_TYPE_STRING;
    PkgElements[1].String.Length = sizeof ("Top-level package");
    PkgElements[1].String.Pointer = "Top-level package";

    PkgElements[2].Type = ACPI_TYPE_BUFFER;
    PkgElements[2].Buffer.Length = sizeof ("XXXX");
    PkgElements[2].Buffer.Pointer = (UINT8 *) "XXXX";

    PkgElements[3].Type = ACPI_TYPE_PACKAGE;
    PkgElements[3].Package.Count = 2;
    PkgElements[3].Package.Elements = Pkg2Elements;

    /* Sub-package elements */

    Pkg2Elements[0].Type = ACPI_TYPE_INTEGER;
    Pkg2Elements[0].Integer.Value = (ACPI_INTEGER) 0x5555AAAABBBBCCCC;

    Pkg2Elements[1].Type = ACPI_TYPE_STRING;
    Pkg2Elements[1].String.Length = sizeof ("Nested Package");
    Pkg2Elements[1].String.Pointer = "Nested Package";

    /* Parameter object */

    Params.Count = 1;
    Params.Pointer = &PkgArg;

    Status = AcpiEvaluateObject (NULL, "\\_PKG", &Params, NULL);
}


ACPI_STATUS
AeGetDevices (
    ACPI_HANDLE                     ObjHandle,
    UINT32                          NestingLevel,
    void                            *Context,
    void                            **ReturnValue)
{

    return (AE_OK);
}


void
AeMiscellaneousTests (
    void)
{
    ACPI_HANDLE             Handle;
    ACPI_BUFFER             ReturnBuf;
    char                    Buffer[32];
    ACPI_VENDOR_UUID        Uuid = {0, {ACPI_INIT_UUID (0,0,0,0,0,0,0,0,0,0,0)}};
    ACPI_STATUS             Status;
    UINT32                  LockHandle1;
    UINT32                  LockHandle2;
    ACPI_STATISTICS         Stats;


    AeTestBufferArgument();
    AeTestPackageArgument ();


    ReturnBuf.Length = 32;
    ReturnBuf.Pointer = Buffer;

    AcpiGetName (AcpiGbl_RootNode, ACPI_FULL_PATHNAME, &ReturnBuf);
    AcpiEnableEvent (ACPI_EVENT_GLOBAL, 0);

    AcpiInstallGpeHandler (NULL, 0, ACPI_GPE_LEVEL_TRIGGERED, AeGpeHandler, NULL);
    AcpiSetGpeType (NULL, 0, ACPI_GPE_TYPE_WAKE_RUN);
    AcpiEnableGpe (NULL, 0, ACPI_NOT_ISR);
    AcpiRemoveGpeHandler (NULL, 0, AeGpeHandler);

    AcpiInstallGpeHandler (NULL, 0, ACPI_GPE_LEVEL_TRIGGERED, AeGpeHandler, NULL);
    AcpiSetGpeType (NULL, 0, ACPI_GPE_TYPE_WAKE_RUN);
    AcpiEnableGpe (NULL, 0, ACPI_NOT_ISR);

    AcpiInstallGpeHandler (NULL, 1, ACPI_GPE_EDGE_TRIGGERED, AeGpeHandler, NULL);
    AcpiSetGpeType (NULL, 1, ACPI_GPE_TYPE_RUNTIME);
    AcpiEnableGpe (NULL, 1, ACPI_NOT_ISR);

    AcpiInstallGpeHandler (NULL, 2, ACPI_GPE_LEVEL_TRIGGERED, AeGpeHandler, NULL);
    AcpiSetGpeType (NULL, 2, ACPI_GPE_TYPE_WAKE);
    AcpiEnableGpe (NULL, 2, ACPI_NOT_ISR);

    AcpiInstallGpeHandler (NULL, 3, ACPI_GPE_EDGE_TRIGGERED, AeGpeHandler, NULL);
    AcpiSetGpeType (NULL, 3, ACPI_GPE_TYPE_WAKE_RUN);

    AcpiInstallGpeHandler (NULL, 4, ACPI_GPE_LEVEL_TRIGGERED, AeGpeHandler, NULL);
    AcpiSetGpeType (NULL, 4, ACPI_GPE_TYPE_RUNTIME);

    AcpiInstallGpeHandler (NULL, 5, ACPI_GPE_EDGE_TRIGGERED, AeGpeHandler, NULL);
    AcpiSetGpeType (NULL, 5, ACPI_GPE_TYPE_WAKE);

    AcpiInstallGpeHandler (NULL, 0x19, ACPI_GPE_LEVEL_TRIGGERED, AeGpeHandler, NULL);
    AcpiSetGpeType (NULL, 0x19, ACPI_GPE_TYPE_WAKE_RUN);
    AcpiEnableGpe (NULL, 0x19, ACPI_NOT_ISR);

    AfInstallGpeBlock ();


    Status = AcpiGetHandle (NULL, "RSRC", &Handle);
    if (ACPI_SUCCESS (Status))
    {
        ReturnBuf.Length = ACPI_ALLOCATE_BUFFER;

        Status = AcpiGetVendorResource (Handle, "_CRS", &Uuid, &ReturnBuf);
        if (ACPI_SUCCESS (Status))
        {
            AcpiOsFree (ReturnBuf.Pointer);
        }
    }

    /* Test global lock */

    Status = AcpiAcquireGlobalLock (0xFFFF, &LockHandle1);
    if (ACPI_FAILURE (Status))
    {
        AcpiOsPrintf ("Could not get GlobalLock, %X\n", Status);
    }

    Status = AcpiAcquireGlobalLock (0x5, &LockHandle2);
    if (ACPI_FAILURE (Status))
    {
        AcpiOsPrintf ("Could not get GlobalLock, %X\n", Status);
    }

    Status = AcpiReleaseGlobalLock (LockHandle1);
    if (ACPI_FAILURE (Status))
    {
        AcpiOsPrintf ("Could not release GlobalLock, %X\n", Status);
    }

    Status = AcpiReleaseGlobalLock (LockHandle2);
    if (ACPI_FAILURE (Status))
    {
        AcpiOsPrintf ("Could not release GlobalLock, %X\n", Status);
    }

    /* Get Devices */

    Status = AcpiGetDevices (NULL, AeGetDevices, NULL, NULL);
    if (ACPI_FAILURE (Status))
    {
        AcpiOsPrintf ("Could not AcpiGetDevices, %X\n", Status);
    }

    Status = AcpiGetStatistics (&Stats);
    if (ACPI_FAILURE (Status))
    {
        AcpiOsPrintf ("Could not AcpiGetStatistics, %X\n", Status);
    }
}

