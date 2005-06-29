
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
 * license (without the right to sublicense), under only those claims of Intel
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

#include <acpi.h>
#include <hardware.h>
#include <namespace.h>


#define _THIS_MODULE        "cminit.c"
#define _COMPONENT          MISCELLANEOUS


/******************************************************************************
 *
 * FUNCTION:    CmGetTableRsdt
 *
 * PARAMETERS:  NumberOfTables      - Where the table count is placed
 *              FilePtr             - Input file pointer, if file is in use
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Load and validate the RSDP (ptr) and RSDT (table)
 *
 ******************************************************************************/

ACPI_STATUS
CmGetTableRsdt (
    UINT32                  *NumberOfTables, 
    char                    **TablePtr)
{
    ACPI_STATUS             Status = AE_OK;
    UINT32                  VersionLength;


    FUNCTION_TRACE ("CmGetTableRsdt");

    if (*TablePtr)
    {
        VersionLength = strlen (ACPILIB_DATA_FILE_VERSION);

        if (strncmp (ACPILIB_DATA_FILE_VERSION, *TablePtr, VersionLength))
        {
            /* data file version mismatch  */

            REPORT_ERROR ("Data file version mismatch");

            DEBUG_PRINT (ACPI_INFO,
                        ("ACPICA version %s expects a data file version string of"
                        "\n \"%s\"", ACPI_LIB_VER, ACPILIB_DATA_FILE_VERSION));
            DEBUG_PRINT (ACPI_INFO,
                        ("version string is \"%s\"\n", *TablePtr));

            FUNCTION_STATUS_EXIT (AE_VERSION_MISMATCH);
            return AE_VERSION_MISMATCH;
        }
        
        else
        {
            *TablePtr += VersionLength;
            memcpy (&RsdpOriginalLocation, *TablePtr, (ACPI_SIZE) 4);
            *TablePtr += 4;
        }
    }
    

    /* Get the RSDP */

    Status = NsFindRsdp (&RSDP, TablePtr);
    if (ACPI_FAILURE (Status))
    {
        REPORT_WARNING ("RSDP structure not found");
        FUNCTION_STATUS_EXIT (AE_NO_ACPI_TABLES);
        return AE_NO_ACPI_TABLES;
    }

    /* RSDP structure found */

    if (!*TablePtr)
    {
        DEBUG_PRINT (ACPI_INFO, ("RSDP located at %lXh\n", RSDP));
    }
    
    else
    {
        DEBUG_PRINT (ACPI_INFO,
                    ("RSDP located at %lXh\n", RsdpOriginalLocation));
        
        /* 
         * Since we're working from an input buffer, assume we're running on
         * legacy hardware.  This is intended to prevent any accesses to the
         * hardware since the ACPI tables are probably not valid for the
         * current hardware 
         */
        
        SystemFlags &= ~SYS_MODE_ACPI;
        SystemFlags |= SYS_MODE_LEGACY;
    }



    /* Get the RSDT */

    Status = NsGetTable ((void *) RSDP->RsdtPhysicalAddress, TablePtr, (void *) &RSDT);
    if (Status != AE_OK)
    {
        FUNCTION_STATUS_EXIT (Status);
        return Status;
    }


    /* Valid RSDT pointer */

    if (strncmp (RSDT->header.Signature, RSDT_SIG, 4))
    {
        /* Invalid RSDT signature */

        REPORT_ERROR ("Invalid signature where RSDP indicates RSDT should be located");

        DEBUG_PRINT (ACPI_INFO,
                    ("RSDP indicates RSDT should be located at %lXh, however the table\n"
                    "  signature at %lXh is incorrect.\n"
                    "  Expected signature: 'RSDT'  Actual signature: '%4.4s'\n",
                    RSDP->RsdtPhysicalAddress, RSDP->RsdtPhysicalAddress,
                    RSDT->header.Signature));

        FUNCTION_STATUS_EXIT (AE_BAD_SIGNATURE);
        return AE_BAD_SIGNATURE;
    }


    /* Valid RSDT signature, verify the checksum */

    DEBUG_PRINT (ACPI_INFO,
                ("RSDT located at %lXh\n", RSDP->RsdtPhysicalAddress));

    Status = NsVerifyTableChecksum (RSDT);
    
    /* Determine the number of tables pointed to by the RSDT */

    *NumberOfTables = (INT32) (RSDT->header.Length - sizeof (ACPI_TABLE_HEADER)) / 4;


    FUNCTION_STATUS_EXIT (Status);
    return Status;
}


/******************************************************************************
 *
 * FUNCTION:    CmGetAllTables
 *
 * PARAMETERS:  NumberOfTables      - Number of tables to get
 *              FilePtr             - Input file pointer, if file is in use
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Load and validate all tables other than the RSDT.  The RSDT must
 *              already be loaded and validated.
 *
 ******************************************************************************/

ACPI_STATUS
CmGetAllTables (
    UINT32                  NumberOfTables, 
    char                    **TablePtr)
{
    ACPI_STATUS             Status = AE_OK;
    UINT32                  Index;
    ACPI_TABLE_HEADER       *TableHeader = NULL;

    
    FUNCTION_TRACE ("CmGetAllTables");

    /* loop through all table pointers found in RSDT   */

    DEBUG_PRINT (ACPI_INFO, ("Number of tables: %d\n", NumberOfTables));

    for (Index = 0; Index < NumberOfTables; Index++)
    {
        Status = NsGetTable ((void *) RSDT->TableOffsetEntry[Index], 
                                TablePtr, (void *) &TableHeader);
        if (ACPI_FAILURE (Status))
        {
            FUNCTION_STATUS_EXIT (Status);
            return Status;
        }

        if (!TableHeader)
        {   
            continue;
        }


        /* TableHeader valid   */

        if (!strncmp (TableHeader->Signature, FACP_SIG, 4))
        {
            FACP = (FIXED_ACPI_DESCRIPTION_TABLE *) TableHeader;
            DEBUG_PRINT (ACPI_INFO,
                        ("FACP located at %lXh\n", RSDT->TableOffsetEntry[Index]));

            NsVerifyTableChecksum (FACP);

            Status = NsGetTableFacs (TablePtr, (void *) &FACS);
            if (ACPI_FAILURE (Status))
            {
                FUNCTION_STATUS_EXIT (Status);
                return Status;
            }

            DEBUG_PRINT (ACPI_INFO,
                        ("FACS located at %lXh\n", FACP->FirmwareCtrl));

            /* TBD: original code used separate file for the DSDT */
            /* Get the DSDT */

            Status = NsGetTable ((void *) FACP->Dsdt, TablePtr, (void *) &DSDT);
            if (ACPI_FAILURE (Status))
            {
                FUNCTION_STATUS_EXIT (Status);
                return Status;
            }

            if (DSDT)
            {
                /* Found the DSDT - Verify the table checksum */

                DEBUG_PRINT (ACPI_INFO, ("DSDT located at %lXh\n", FACP->Dsdt));
                NsVerifyTableChecksum (DSDT);
                
                /* Dump the DSDT Header */

                DEBUG_PRINT (TRACE_TABLES, ("Hex dump of DSDT Header:\n"));
                DUMP_BUFFER ((UINT8 *) DSDT,
                                (ACPI_SIZE) sizeof (ACPI_TABLE_HEADER), HEX | ASCII);
                
                /* Dump the entire DSDT */

                DEBUG_PRINT (TRACE_TABLES,
                            ("Hex dump of DSDT (After header), size %d (0x%x)\n",
                            (ACPI_SIZE)DSDT->Length, (ACPI_SIZE)DSDT->Length));
                DUMP_BUFFER ((UINT8 *) (DSDT + 1),
                                (ACPI_SIZE)DSDT->Length, HEX | ASCII);
            }
        }
        
        else if (!strncmp (TableHeader->Signature, APIC_SIG, 4))
        {
            /* pointer to APIC table   */

            MAPIC = (APIC_TABLE *) TableHeader;
            DEBUG_PRINT (ACPI_INFO,
                        ("APIC Table located at %lXh\n", RSDT->TableOffsetEntry[Index]));
            NsVerifyTableChecksum (MAPIC);
        }
    
        else if (!strncmp (TableHeader->Signature, PSDT_SIG, 4))
        {
            /* pointer to PSDT table   */

            PSDT = TableHeader;
            DEBUG_PRINT (ACPI_INFO,
                        ("PSDT located at %lXh\n", RSDT->TableOffsetEntry[Index]));
            NsVerifyTableChecksum (PSDT);
        }

        else if (!strncmp (TableHeader->Signature, SSDT_SIG, 4))
        {
            /* pointer to SSDT table   */
            /* TBD - need to be able to deal with multiple SSDTs */
        
            SSDT = TableHeader;
            DEBUG_PRINT (ACPI_INFO,
                        ("SSDT located at %lXh\n", RSDT->TableOffsetEntry[Index]));
            NsVerifyTableChecksum (SSDT);
        }

        else if (!strncmp (TableHeader->Signature, SBDT_SIG, 4))
        {
            /* pointer to SBDT table   */

            SBDT = TableHeader;
            DEBUG_PRINT (ACPI_INFO,
                        ("SBDT located at %lXh\n", RSDT->TableOffsetEntry[Index]));
            NsVerifyTableChecksum (SBDT);
        }

        else
        {
            /* pointer to unknown table    */

            DEBUG_PRINT (ACPI_INFO,
                        ("Unknown table %x in RSDT with signature '%4.4s' located at %lXh\n",
                        TableHeader, TableHeader->Signature, RSDT->TableOffsetEntry[Index]));
            NsVerifyTableChecksum (TableHeader);
        
            /* 
             * !! TBD - need to be able to handle multiple unknown tables.  Error should be
             *  displayed when table is displayed,  Displaying it here for now 
             */
        
            DUMP_BUFFER (&RSDT->header, 32, 0);
        }
    }
      
    
    /* 
     * Initialize the capabilities flags.
     * Assumes that platform supports ACPI_MODE since we have tables!
     */
        
    SystemFlags |= HwGetModeCapabilities ();

    FUNCTION_STATUS_EXIT (Status);
    return Status;
}
  

/*******************************************************************************
 *
 * FUNCTION:    ReportFacpRegisterError
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
ReportFacpRegisterError (
    char                    *RegisterName, 
    UINT32                  Value,
    INT32                   AcpiTestSpecSection, 
    INT32                   AcpiAssertion)
{
    
    REPORT_ERROR ("Invalid FACP register value");
    
    DEBUG_PRINT (ACPI_ERROR, ("  Assertion %d.%d.%d Failed  %s=%08lXh\n",
                ACPI_CHAPTER, AcpiTestSpecSection, AcpiAssertion, RegisterName, Value));
}


/******************************************************************************
 *
 * FUNCTION:    CmHardwareInitialize
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Initialize and validate various ACPI registers
 *
 ******************************************************************************/

ACPI_STATUS
CmHardwareInitialize (void)
{
    ACPI_STATUS             Status = AE_OK;
    INT32                   Index;


    
    FUNCTION_TRACE ("CmHardwareInitialize");


    /* We must have an the ACPI tables by the time we get here */

    if (!FACP)
    {
        RestoreAcpiChipset = FALSE;

        DEBUG_PRINT (ACPI_ERROR, ("CmHardwareInitialize: No FACP!\n"));
        FUNCTION_STATUS_EXIT (AE_NO_ACPI_TABLES);
        return AE_NO_ACPI_TABLES;
    }

    /* Must support *some* mode! */
/*
    if (!(SystemFlags & SYS_MODES_MASK))
    {
        RestoreAcpiChipset = FALSE;

        DEBUG_PRINT (ACPI_ERROR, ("CmHardwareInitialize: Supported modes unitialized!\n"));
        FUNCTION_STATUS_EXIT (AE_ERROR);
        return AE_ERROR;
    }

*/


    switch (SystemFlags & SYS_MODES_MASK)
    {
        /* Identify current ACPI/legacy mode   */

    case (SYS_MODE_ACPI):

        OriginalMode = SYS_MODE_ACPI;
        DEBUG_PRINT (ACPI_INFO, ("System supports ACPI mode only.\n"));
        break;


    case (SYS_MODE_LEGACY):

        OriginalMode = SYS_MODE_LEGACY;
        DEBUG_PRINT (ACPI_INFO,
                    ("Tables loaded from buffer, hardware assumed to support LEGACY mode only.\n"));
        break;


    case (SYS_MODE_ACPI | SYS_MODE_LEGACY):

        if (AcpiGetMode () == SYS_MODE_ACPI)
        {
            OriginalMode = SYS_MODE_ACPI;
        }
        else
        {
            OriginalMode = SYS_MODE_LEGACY;
        }

        DEBUG_PRINT (ACPI_INFO, ("System supports both ACPI and LEGACY modes.\n"));

        DEBUG_PRINT (ACPI_INFO, ("System is currently in %s mode.\n",
                                (OriginalMode == SYS_MODE_ACPI) ? "ACPI" : "LEGACY"));
        break;
    }


    if (SystemFlags & SYS_MODE_ACPI)
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

        Pm1EnableRegisterSave = OsdIn16 ((UINT16) (FACP->Pm1aEvtBlk + 2));
        if (FACP->Pm1bEvtBlk)
        {
            Pm1EnableRegisterSave |= OsdIn16 ((UINT16) (FACP->Pm1bEvtBlk + 2));
        }


        /* 
         * The GPEs behave similarly, except that the length of the register
         * block is not fixed, so the buffer must be allocated with malloc 
         */

        if (FACP->Gpe0Blk && FACP->Gpe0BlkLen)
        {
            /* GPE0 specified in FACP  */

            Gpe0EnableRegisterSave = LocalAllocate ((ACPI_SIZE) (FACP->Gpe0BlkLen / 2));
            if (!Gpe0EnableRegisterSave)
            {
                FUNCTION_STATUS_EXIT (Status);
                return AE_NO_MEMORY;
            }

            /* save state of GPE0 enable bits */

            for (Index = 0; Index < FACP->Gpe0BlkLen / 2; Index++)
            {
                Gpe0EnableRegisterSave[Index] =
                    OsdIn8 ((UINT16) (FACP->Gpe0Blk + FACP->Gpe0BlkLen / 2));
            }
        }
        
        else
        {
            Gpe0EnableRegisterSave = NULL;
        }

        if (FACP->Gpe1Blk && FACP->Gpe1BlkLen)
        {
            /* GPE1 defined    */

            Gpe1EnableRegisterSave = LocalAllocate ((ACPI_SIZE) (FACP->Gpe1BlkLen / 2));
            if (!Gpe1EnableRegisterSave)
            {
                FUNCTION_STATUS_EXIT (Status);
                return AE_NO_MEMORY;
            }

            /* save state of GPE1 enable bits */
    
            for (Index = 0; Index < FACP->Gpe1BlkLen / 2; Index++)
            {
                Gpe1EnableRegisterSave[Index] =
                    OsdIn8 ((UINT16) (FACP->Gpe1Blk + FACP->Gpe1BlkLen / 2));
            }
        }
        
        else
        {
            Gpe1EnableRegisterSave = NULL;
        }
    
    
        /* 
         * Verify Fixed ACPI Description Table fields per ACPI 1.0 sections
         * 4.7.1.2 and 5.2.5 (assertions #410, 415, 435-440)
         */

        if (FACP->Pm1EvtLen < 4)
            ReportFacpRegisterError ("PM1_EVT_LEN", (UINT32) FACP->Pm1EvtLen,
                ACPI_TABLE_NAMESPACE_SECTION, 410); /* #410 == #435    */

        if (!FACP->Pm1CntLen)
            ReportFacpRegisterError ("PM1_CNT_LEN", (UINT32) FACP->Pm1CntLen,
                ACPI_TABLE_NAMESPACE_SECTION, 415); /* #415 == #436    */

        if (!FACP->Pm1aEvtBlk)
            ReportFacpRegisterError ("PM1a_EVT_BLK", FACP->Pm1aEvtBlk,
                ACPI_TABLE_NAMESPACE_SECTION, 432);

        if (!FACP->Pm1aCntBlk)
            ReportFacpRegisterError ("PM1a_CNT_BLK", FACP->Pm1aCntBlk,
                ACPI_TABLE_NAMESPACE_SECTION, 433);

        if (!FACP->PmTmrBlk)
            ReportFacpRegisterError ("PM_TMR_BLK", FACP->PmTmrBlk,
                ACPI_TABLE_NAMESPACE_SECTION, 434);

        if (FACP->Pm2CntBlk && !FACP->Pm2CntLen)
            ReportFacpRegisterError ("PM2_CNT_LEN", (UINT32) FACP->Pm2CntLen,
                ACPI_TABLE_NAMESPACE_SECTION, 437);

        if (FACP->PmTmLen < 4)
            ReportFacpRegisterError ("PM_TM_LEN", (UINT32) FACP->PmTmLen,
                ACPI_TABLE_NAMESPACE_SECTION, 438);

        if (FACP->Gpe0Blk && (FACP->Gpe0BlkLen & 1))    /* length not multiple of 2    */
            ReportFacpRegisterError ("GPE0_BLK_LEN", (UINT32) FACP->Gpe0BlkLen,
                ACPI_TABLE_NAMESPACE_SECTION, 439);

        if (FACP->Gpe1Blk && (FACP->Gpe1BlkLen & 1))    /* length not multiple of 2    */
            ReportFacpRegisterError ("GPE1_BLK_LEN", (UINT32) FACP->Gpe1BlkLen,
                ACPI_TABLE_NAMESPACE_SECTION, 440);
    }


    FUNCTION_STATUS_EXIT (Status);
BREAKPOINT3;
    return (Status);
}




