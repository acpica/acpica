
/******************************************************************************
 * 
 * Module Name: acpiinit - Main ACPI subsystem initialization
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
 * 2.1. Intel grants, free of charge, to any person ("Licensee") obtaining a 
 * copy of the source code appearing in this file ("Covered Code") a license 
 * under Intel's copyrights in the base code distributed originally by Intel 
 * ("Original Intel Code") to copy, make derivatives, distribute, use and 
 * display any portion of the Covered Code in any form; and
 *
 * 2.2. Intel grants Licensee a non-exclusive and non-transferable patent 
 * license (without the right to sublicense), under only those claims of Intel
 * patents that are infringed by the Original Intel Code, to make, use, sell, 
 * offer to sell, and import the Covered Code and derivative works thereof 
 * solely to the minimum extent necessary to exercise the above copyright 
 * license, and in no event shall the patent license extend to any additions to
 * or modifications of the Original Intel Code.  No other license or right is 
 * granted directly or by implication, estoppel or otherwise;
 *
 * the above copyright and patent license is granted only if the following 
 * conditions are met:
 *
 * 3. Conditions 
 *
 * 3.1. Redistribution of source code of any substantial portion of the Covered 
 * Code or modification must include the above Copyright Notice, the above 
 * License, this list of Conditions, and the following Disclaimer and Export 
 * Compliance provision.  In addition, Licensee must cause all Covered Code to 
 * which Licensee contributes to contain a file documenting the changes 
 * Licensee made to create that Covered Code and the date of any change.  
 * Licensee must include in that file the documentation of any changes made by
 * any predecessor Licensee.  Licensee must include a prominent statement that
 * the modification is derived, directly or indirectly, from Original Intel 
 * Code.
 *
 * 3.2. Redistribution in binary form of any substantial portion of the Covered 
 * Code or modification must reproduce the above Copyright Notice, and the 
 * following Disclaimer and Export Compliance provision in the documentation 
 * and/or other materials provided with the distribution.
 *
 * 3.3. Intel retains all right, title, and interest in and to the Original 
 * Intel Code.
 *
 * 3.4. Neither the name Intel nor any other trademark owned or controlled by 
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
 * event Licensee exports any such software from the United States or re-
 * exports any such software from a foreign destination, Licensee shall ensure
 * that the distribution and export/re-export of the software is in compliance 
 * with all laws, regulations, orders, or other restrictions of the U.S. Export 
 * Administration Regulations. Licensee agrees that neither it nor any of its 
 * subsidiaries will export/re-export any technical data, process, software, or 
 * service, directly or indirectly, to any country for which the United States 
 * government or any agency thereof requires an export license, other 
 * governmental approval, or letter of assurance, without first obtaining such
 * license, approval or letter.
 *
 *****************************************************************************/


#define __ACPIINIT_C__

#include <acpi.h>
#include <devices.h>
#include <namespace.h>
#include <events.h>
#include <string.h>


#define _THIS_MODULE        "acpiinit.c"
#define _COMPONENT          MISCELLANEOUS


static ST_KEY_DESC_TABLE KDT[] = {
   {"0000", '1', "Unable to open input file", "Unable to open input file"},
   {"0001", '1', "Data file version mismatch", "Data file version mismatch"},
   {"0002", '1', "", ""},   /*  obsolete    */
   {"0003", 'I', "", ""},   /*  obsolete    */
   {"0004", 'W', "RSDP structure not found", "RSDP structure not found"},
   {"0005", '1', "Invalid signature where RSDP indicates RSDT should be located", "Invalid signature where RSDP indicates RSDT should be located"},
   {"0006", '1', "Unable to open DSDT file", "Unable to open DSDT file"},
   {"0007", '1', "Error creating output file", "Error creating output file"},
   {"0008", '1', "", ""},   /*  obsolete    */
   {"0009", '1', "", ""},   /*  obsolete    */
   {"0010", '1', "", ""},   /*  obsolete    */
   {"0011", '1', "Invalid value", "Invalid value"},
   {NULL, 'I', NULL, NULL}
};


/****************************************************************************
 * FUNCTION:    IncFACPRegisterError
 *
 * PARAMETERS:  char    *RegisterName           pointer to string identifying register
 *              UINT32  Value                   actual register contents value
 *              INT32   AcpiTestSpecSection     TDS section containing assertion
 *              INT32   AcpiAssertion           assertion number being tested
 *
 * RETURN:      none
 *
 * DESCRIPTION: display failure message and link failure to TDS assertion
 *
 ****************************************************************************/

void
IncFACPRegisterError (char *RegisterName, UINT32 Value,
                        INT32 AcpiTestSpecSection, INT32 AcpiAssertion)
{
    
    REPORT_ERROR (&KDT[11]);
    
    DEBUG_PRINT (ACPI_ERROR, ("  Assertion %d.%d.%d Failed  %s=%08lXh\n",
                ACPI_CHAPTER, AcpiTestSpecSection, AcpiAssertion, RegisterName, Value));
}


/******************************************************************************
 *
 * FUNCTION:    AcpiInit
 *
 * PARAMETERS:  none
 *
 * RETURN:      none
 *
 * DESCRIPTION: Enumerate all tables and initializes all ACPILIB global
 *              variables.  Strong link in ACPITBLS.C, weak link in
 *
 *              NOTE: The prototype for this function lives in BU.H
 *
 ******************************************************************************/

INT32
AcpiInit (char *FileName)
{
    INT32                   ErrorCheck = E_OK;
    INT32                   NumberOfTables = 0; 
    INT32                   Index = 0;
    ACPI_TABLE_HEADER       *TableHeader = NULL;
    OSD_FILE                *FilePtr = NULL;
    OSD_FILE                *DsdtFilePtr = NULL;
    UINT32                  RsdpOriginalLocation = 0;
    char                    Buffer[80];



    FUNCTION_TRACE ("AcpiInit");


    /* first initialize ACPILIB globals... */

    InitAcpiLibGlobals ();


    DEBUG_PRINT (ACPI_INFO, ("Initializing ACPILIB...\n"));
    IncIndent ();

    InputFile = FileName;
    if (InputFile != NULL)
    {
        RestoreAcpiChipset = FALSE;

        DEBUG_PRINT (ACPI_INFO,
                    ("Loading all ACPI table data and addresses from %s.\n", InputFile));
        
        FilePtr = OsdOpen (InputFile, "rb");
        if (!FilePtr)
        {
            /*  unable to open ACPI table input file    */

            REPORT_ERROR (&KDT[0]);
            ErrorCheck = E_FILE_NOT_EXIST;
        }
        
        else
        {
            OsdRead (Buffer, strlen (ACPILIB_DATA_FILE_VERSION), (size_t) 1, FilePtr);
            
            if (strncmp (ACPILIB_DATA_FILE_VERSION, Buffer, strlen (ACPILIB_DATA_FILE_VERSION)))
            {
                /*  data file version mismatch  */

                REPORT_ERROR (&KDT[1]);

                DEBUG_PRINT (ACPI_INFO,
                            ("ACPILIB version %s expects a data file version string of"
                            "\n \"%s\"", ACPI_LIB_VER, ACPILIB_DATA_FILE_VERSION));
                DEBUG_PRINT (ACPI_INFO,
                            ("%s's version string is \"%s\"\n", InputFile, Buffer));
                ErrorCheck = E_FILE_NOT_EXIST;
            }
            
            else
            {
                OsdRead (&RsdpOriginalLocation, (size_t) 4, (size_t) 1, FilePtr);
            }
        }
    }
    
    else
    {
        /* use BIOS ACPI tables */

        /* Anything to do here??? TBD */
    }

    if (ErrorCheck == E_OK)
    {
        ErrorCheck |= FindRootSystemDescriptorPointer (&RSDP, FilePtr);

        if (ErrorCheck)
        {
            REPORT_WARNING (&KDT[4]);
            ErrorCheck = E_NO_ACPI_TBLS;
        }
    }    

    if (ErrorCheck == E_OK)
    {
        /*  RSDP structure found */

        if (!FilePtr)
        {
            DEBUG_PRINT (ACPI_INFO, ("RSDP located at %lXh\n", RSDP));
        }
        
        else
        {
            DEBUG_PRINT (ACPI_INFO,
                        ("RSDP located at %lXh\n", RsdpOriginalLocation));
            
            /* 
             * Since we're working from an input file, assume we're running on
             * legacy hardware.  This is intended to prevent any accesses to the
             * hardware since the ACPI tables are probably not valid for the
             * current hardware 
             */
            
            Capabilities = LEGACY_MODE;
        }


        /* Since we found the RSDP, now enumerate all tables... */
        /* first is the RSDT */
        
        RSDT = GetTable (RSDP->RsdtPhysicalAddress, FilePtr);

        if (RSDT)
        {
            /* Valid RSDT pointer */

            if (strncmp (RSDT->header.Signature, RSDT_SIG, 4))
            {
                /* Invalid RSDT signature */

                REPORT_ERROR (&KDT[5]);

                DEBUG_PRINT (ACPI_INFO,
                            ("RSDP indicates RSDT should be located at %lXh, however the table\n"
                            "  signature at %lXh is incorrect.\n"
                            "  Expected signature: 'RSDT'  Actual signature: '%4.4s'\n",
                            RSDP->RsdtPhysicalAddress, RSDP->RsdtPhysicalAddress,
                            RSDT->header.Signature));

                ErrorCheck |= E_ERROR;
            }
        
            else
            {
                /* Valid RSDT signature */

                DEBUG_PRINT (ACPI_INFO,
                            ("RSDT located at %lXh\n", RSDP->RsdtPhysicalAddress));
            }
        
            ErrorCheck |= VerifyTableChecksum (RSDT, OUTPUT_DATA | OUTPUT_ERRORS);
            
            /* next, enumerate all table pointers found in the RSDT */

            NumberOfTables = (INT32) (RSDT->header.Length - sizeof (ACPI_TABLE_HEADER)) / 4;
        }


        /*  loop through all table pointers found in RSDT   */

        for (Index = 0; Index < NumberOfTables; Index++)
        {
            TableHeader = GetTable (RSDT->TableOffsetEntry[Index], FilePtr);
            if (TableHeader)
            {   
                /*  TableHeader valid   */

                if (!strncmp (TableHeader->Signature, FACP_SIG, 4))
                {
                    FACP = (FIXED_ACPI_DESCRIPTION_TABLE *) TableHeader;
                    DEBUG_PRINT (ACPI_INFO,
                                ("FACP located at %lXh\n", RSDT->TableOffsetEntry[Index]));

                    ErrorCheck |= VerifyTableChecksum (FACP, OUTPUT_DATA | OUTPUT_ERRORS);

                    FACS = GetFACS (FilePtr);
                    if (FACS)
                    {
                        DEBUG_PRINT (ACPI_INFO,
                                    ("FACS located at %lXh\n", FACP->FirmwareCtrl));
                    }

                    if (DsdtFile)
                    {
                        DsdtFilePtr = OsdOpen (DsdtFile, "rb");

                        if (DsdtFilePtr)
                        {
                            /* Opened DSDT file, get the table */

                            DSDT = GetTable (FACP->Dsdt, DsdtFilePtr);
                            OsdClose (DsdtFilePtr);
                        }
                    
                        else
                        {
                            REPORT_ERROR (&KDT[6]);
                            ErrorCheck = E_FILE_NOT_EXIST;
                        }
                    }
                
                    else
                    {
                        /* Normal -- get DSDT from BIOS table */

                        DSDT = GetTable (FACP->Dsdt, FilePtr);
                    }

                    if (DSDT)
                    {
                        /* Found the DSDT */

                        DEBUG_PRINT (ACPI_INFO,
                                    ("DSDT located at %lXh\n", FACP->Dsdt));
                        ErrorCheck |= VerifyTableChecksum (DSDT,
                                                OUTPUT_DATA | OUTPUT_ERRORS);

                        DEBUG_PRINT (TRACE_TABLES,
                                    ("Hex dump of DSDT (no header), size %d (0x%x)\n",
                                    (size_t)DSDT->Length, (size_t)DSDT->Length));
                        DUMP_BUFFER ((UINT8 *) (DSDT + 1),
                                        (size_t)DSDT->Length, HEX | ASCII);
                    }
                }
                
                else if (!strncmp (TableHeader->Signature, APIC_SIG, 4))
                {
                    /*  pointer to APIC table   */

                    MAPIC = (APIC_TABLE *) TableHeader;
                    DEBUG_PRINT (ACPI_INFO,
                                ("APIC Table located at %lXh\n", RSDT->TableOffsetEntry[Index]));
                    ErrorCheck |= VerifyTableChecksum (MAPIC, OUTPUT_DATA | OUTPUT_ERRORS);
                }
            
                else if (!strncmp (TableHeader->Signature, PSDT_SIG, 4))
                {
                    /*  pointer to PSDT table   */

                    PSDT = TableHeader;
                    DEBUG_PRINT (ACPI_INFO,
                                ("PSDT located at %lXh\n", RSDT->TableOffsetEntry[Index]));
                    ErrorCheck |= VerifyTableChecksum (PSDT, OUTPUT_DATA | OUTPUT_ERRORS);
                }

                else if (!strncmp (TableHeader->Signature, SSDT_SIG, 4))
                {
                    /*  pointer to SSDT table   */
                    /* TBD - need to be able to deal with multiple SSDTs */
                
                    SSDT = TableHeader;
                    DEBUG_PRINT (ACPI_INFO,
                                ("SSDT located at %lXh\n", RSDT->TableOffsetEntry[Index]));
                    ErrorCheck |= VerifyTableChecksum (SSDT, OUTPUT_DATA | OUTPUT_ERRORS);
                }

                else if (!strncmp (TableHeader->Signature, SBDT_SIG, 4))
                {
                    /*  pointer to SBDT table   */

                    SBDT = TableHeader;
                    DEBUG_PRINT (ACPI_INFO,
                                ("SBDT located at %lXh\n", RSDT->TableOffsetEntry[Index]));
                    ErrorCheck |= VerifyTableChecksum (SBDT, OUTPUT_DATA | OUTPUT_ERRORS);
                }

                else
                {
                    /*  pointer to unknown table    */

                    DEBUG_PRINT (ACPI_INFO,
                                ("Unknown table listed in RSDT with signature '%4.4' located at %lXh\n",
                                TableHeader->Signature, RSDT->TableOffsetEntry[Index]));
                    ErrorCheck |= VerifyTableChecksum (TableHeader, OUTPUT_DATA | OUTPUT_ERRORS);
                
                    /* 
                     * !! TBD - need to be able to handle multiple unknown tables.  Error should be
                     *  displayed when tables is displayed,  Displaying it here for now 
                     */
                
                    DUMP_BUFFER (&RSDT->header, 32, 0);
                }
            }
        }
            
        if (FilePtr)
        {   
            /* close the input file */
            
            OsdClose (FilePtr);
        }
        
        else
        {   
            /* since we're operating on ACPI hardware, initialize Capabilities */
                
            Capabilities = AcpiModeCapabilities ();
        }
    }
    
    if (OutputFile && 
        !InputFile && 
        ErrorCheck != E_NO_ACPI_TBLS)
    {
        /*  write BIOS ACPI tables to .dat file */

        /* TBD:  Needed for this ACPI driver ??? !!! */

        FilePtr = OsdOpen (OutputFile, "wb");
        if (FilePtr)
        {
            OsdWrite (ACPILIB_DATA_FILE_VERSION, strlen (ACPILIB_DATA_FILE_VERSION),
                        (size_t) 1, FilePtr);
            
            /* POINTER STUFF COMMENTED OUT !!!! */

/*
 *           RsdpOriginalLocation = (UINT32) PtrOffset (RSDP);
 */

            OsdWrite (&RsdpOriginalLocation, sizeof (UINT32), (size_t) 1, FilePtr);
            OsdWrite (RSDP, sizeof (ROOT_SYSTEM_DESCRIPTOR_POINTER), (size_t) 1, FilePtr);
            
            if (RSDT)
                OsdWrite (RSDT, (size_t) RSDT->header.Length, (size_t) 1, FilePtr);
            if (FACP)
                OsdWrite (FACP, (size_t) FACP->header.Length, (size_t) 1, FilePtr);
            if (FACS)
                OsdWrite (FACS, (size_t) FACS->Length, (size_t) 1, FilePtr);
            if (DSDT)
                OsdWrite (DSDT, (size_t) DSDT->Length, (size_t) 1, FilePtr);
            if (MAPIC)
                OsdWrite (MAPIC, (size_t) MAPIC->header.Length, (size_t) 1, FilePtr);
            if (PSDT)
                OsdWrite (PSDT, (size_t) PSDT->Length, (size_t) 1, FilePtr);
            if (SSDT)
                OsdWrite (SSDT, (size_t) SSDT->Length, (size_t) 1, FilePtr);
            if (SBDT)
                OsdWrite (SBDT, (size_t) SBDT->Length, (size_t) 1, FilePtr);
            
            OsdClose (FilePtr);
        }
        
        else
        {
            REPORT_ERROR (&KDT[7]);
        }
    }

    DecIndent ();

    /* How are things going now? */

    if (FACP &&
        ErrorCheck == E_OK && 
        !(Capabilities & ~(ACPI_MODE | LEGACY_MODE)))
    {
        /*  ACPILIB initialization OK so far    */

        switch (Capabilities)
        {
            /*  identify current ACPI/legacy mode   */

        case (ACPI_MODE):
            OriginalMode = ACPI_MODE;
            DEBUG_PRINT (ACPI_INFO,
                        ("System supports ACPI mode only.\n"));
            break;

        case (LEGACY_MODE):
            OriginalMode = LEGACY_MODE;
            DEBUG_PRINT (ACPI_INFO,
                        ("Tables loaded from file, hardware assumed to support LEGACY mode only.\n"));
            break;

        case (ACPI_MODE | LEGACY_MODE):
            (AcpiModeStatus () == ACPI_MODE) ? (OriginalMode = ACPI_MODE) : (OriginalMode = LEGACY_MODE);

            DEBUG_PRINT (ACPI_INFO,
                        ("System supports both ACPI and LEGACY modes.\n"));

            DEBUG_PRINT (ACPI_INFO,
                        ("System is currently in %s mode.\n",
                        (OriginalMode == ACPI_MODE) ? "ACPI" : "LEGACY"));
            break;
        }


        if (Capabilities != LEGACY_MODE)
        {
            INT32         Index;

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
                /*  GPE0 specified in FACP  */

                Gpe0EnableRegisterSave = LocalAllocate ((size_t) (FACP->Gpe0BlkLen / 2));
                if (Gpe0EnableRegisterSave)
                {
                    RegisterStaticBlockPtr ((void **) &Gpe0EnableRegisterSave);

                    /* save state of GPE0 enable bits */

                    for (Index = 0; Index < FACP->Gpe0BlkLen / 2; Index++)
                    {
                        Gpe0EnableRegisterSave[Index] =
                            OsdIn8 ((UINT16) (FACP->Gpe0Blk + FACP->Gpe0BlkLen / 2));
                    }
                }
            }
            
            else
            {
                Gpe0EnableRegisterSave = NULL;
            }

            if (FACP->Gpe1Blk && FACP->Gpe1BlkLen)
            {
                /*  GPE1 defined    */

                Gpe1EnableRegisterSave = LocalAllocate ((size_t) (FACP->Gpe1BlkLen / 2));
                if (Gpe1EnableRegisterSave)
                {
                    RegisterStaticBlockPtr ((void **) &Gpe1EnableRegisterSave);

                    /* save state of GPE1 enable bits */
            
                    for (Index = 0; Index < FACP->Gpe1BlkLen / 2; Index++)
                    {
                        Gpe1EnableRegisterSave[Index] =
                            OsdIn8 ((UINT16) (FACP->Gpe1Blk + FACP->Gpe1BlkLen / 2));
                    }
                }
            }
            
            else
            {
                Gpe1EnableRegisterSave = NULL;
            }
        
        
            /*  verify Fixed ACPI Description Table fields per ACPI 1.0 sections
             *  4.7.1.2 and 5.2.5 (assertions #410, 415, 435-440)
             */
            if (FACP->Pm1EvtLen < 4)
                IncFACPRegisterError ("PM1_EVT_LEN", (UINT32) FACP->Pm1EvtLen,
                    ACPI_TABLE_NAMESPACE_SECTION, 410); /*  #410 == #435    */

            if (!FACP->Pm1CntLen)
                IncFACPRegisterError ("PM1_CNT_LEN", (UINT32) FACP->Pm1CntLen,
                    ACPI_TABLE_NAMESPACE_SECTION, 415); /*  #415 == #436    */

            if (!FACP->Pm1aEvtBlk)
                IncFACPRegisterError ("PM1a_EVT_BLK", FACP->Pm1aEvtBlk,
                    ACPI_TABLE_NAMESPACE_SECTION, 432);

            if (!FACP->Pm1aCntBlk)
                IncFACPRegisterError ("PM1a_CNT_BLK", FACP->Pm1aCntBlk,
                    ACPI_TABLE_NAMESPACE_SECTION, 433);

            if (!FACP->PmTmrBlk)
                IncFACPRegisterError ("PM_TMR_BLK", FACP->PmTmrBlk,
                    ACPI_TABLE_NAMESPACE_SECTION, 434);

            if (FACP->Pm2CntBlk && !FACP->Pm2CntLen)
                IncFACPRegisterError ("PM2_CNT_LEN", (UINT32) FACP->Pm2CntLen,
                    ACPI_TABLE_NAMESPACE_SECTION, 437);

            if (FACP->PmTmLen < 4)
                IncFACPRegisterError ("PM_TM_LEN", (UINT32) FACP->PmTmLen,
                    ACPI_TABLE_NAMESPACE_SECTION, 438);

            if (FACP->Gpe0Blk && (FACP->Gpe0BlkLen & 1))    /*  length not multiple of 2    */
                IncFACPRegisterError ("GPE0_BLK_LEN", (UINT32) FACP->Gpe0BlkLen,
                    ACPI_TABLE_NAMESPACE_SECTION, 439);

            if (FACP->Gpe1Blk && (FACP->Gpe1BlkLen & 1))    /*  length not multiple of 2    */
                IncFACPRegisterError ("GPE1_BLK_LEN", (UINT32) FACP->Gpe1BlkLen,
                    ACPI_TABLE_NAMESPACE_SECTION, 440);
       
        
        
        }

        DEBUG_PRINT (ACPI_SUCCESS,
                    ("ACPILIB successfully initialized.\n"));

        AcpiHook = 2;              /* indicate to the outside world we're up and OK ... */
    }
    
    else
    {
        /*  ACPILIB initialization failure  */

        if (!ErrorCheck && (!Capabilities || (Capabilities & ~(ACPI_MODE | LEGACY_MODE))))
        {
            DEBUG_PRINT (ACPI_ERROR,
                        ("Internal ACPILIB error. Capabilities not initialized correctly by AcpiInit()\n"));
            ErrorCheck |= E_ERROR;
        }

        DEBUG_PRINT (ACPI_ERROR,
                    ("ACPILIB NOT successfully initialized.\n"));
        RestoreAcpiChipset = FALSE;
    }


BREAKPOINT3;

    return (ErrorCheck);
}




