
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
 | Publics for ACPI tables and prototypes for
 | library initialization and some types of table access
 |__________________________________________________________________________
 |
 | $Revision: 1.2 $
 | $Date: 2005/06/29 19:14:58 $
 | $Log: utinit.c,v $
 | Revision 1.2  2005/06/29 19:14:58  aystarik
 | 16/32/64-bit common data types
 |
 | 
 | date	99.03.10.00.06.00;	author rmoore1;	state Exp;
 |
 * 
 * 2     3/09/99 4:06p Rmoore1
 * 16/32/64-bit common data types
 * 
 * 1     2/16/99 2:15p Rmosgrov
 * Module contains the AcpiInit fucntion only
 |__________________________________________________________________________

*/

#define __NSTABLES_C__
#define _THIS_MODULE        "AcpiInit.c"

#include <bu.h>
#include "acpiasm.h"
#include "acpiosd.h"
#include "acpilgcy.h"
#include "acpipriv.h"
#include "acpitype.h"
#include "acpitbls.h"
#include "acpinmsp.h"
#include "display.h"
#include "debuglvl.h"
#include "acpilgcy.h"
#include "amlscan.h"
#include "acpirio.h"
#include "amlpriv.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


static INT32        RestoreAcpiChipset = TRUE;
static UINT16       Pm1EnableRegisterSave = 0;
static UINT8 *      Gpe0EnableRegisterSave = NULL;
static UINT8 *      Gpe1EnableRegisterSave = NULL;

INT32               OriginalMode;
INT32               HardwareOverride = FALSE;


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
    INT32                   ErrorCheck;
    INT32                   NumberOfTables; 
    INT32                   Index;
    ACPI_TABLE_HEADER       *TableHeader;
    OSD_FILE                *FilePtr;
    UINT32                   RsdpOriginalLocation;


    FUNCTION_TRACE ("AcpiInit");


    /* first initialize ACPILIB globals... */

    InitAcpiLibGlobals ();

    /* next initialize locals */

    ErrorCheck = E_OK;
    FilePtr = NULL;

    atexit_bu (AcpiCleanup);
    fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA, "Initializing ACPILIB...");
    IncIndent ();

    InputFile = FileName;
    if (InputFile != NULL)
    {
        RestoreAcpiChipset = FALSE;

        fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                    "Loading all ACPI table data and addresses from %s.", InputFile);
        
        FilePtr = OsdOpen (InputFile, "rb");
        if (FilePtr == NULL)
        {
            fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                        "Unable to open file \"%s\"", InputFile);
            _Kinc_error ("0000", PRINT, __LINE__, __FILE__, GetMasterLogHandle (), OUTPUT_DATA);
            ErrorCheck = E_FILE_NOT_EXIST;
        }
        
        else
        {
            char        Buffer[80];

            OsdRead (Buffer, strlen (ACPILIB_DATA_FILE_VERSION), (size_t) 1, FilePtr);
            
            if (strncmp (ACPILIB_DATA_FILE_VERSION, Buffer, strlen (ACPILIB_DATA_FILE_VERSION)))
            {
                fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                            "Data file version mismatch");
                _Kinc_error ("0001", PRINT, __LINE__, __FILE__, GetMasterLogHandle (), OUTPUT_DATA);
                
                fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                            "ACPILIB version %s expects a data file version string of"
                            "\n \"%s\"", ACPI_LIB_VER, ACPILIB_DATA_FILE_VERSION);
                fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                            "%s's version string is \"%s\"", InputFile, Buffer);
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
        if (HardwareOverride)
        {
            fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                        "HwOverride specified on command line, but no input file was provided"
                        "\n  HwOverride ignored");
            /* dKinc_info ("0003", PRINT);*/
            HardwareOverride = FALSE;
        }
    }

    if (ErrorCheck == E_OK)
    {
        ErrorCheck |= FindRootSystemDescriptorPointer (& RSDP, FilePtr);

        if (ErrorCheck)
        {
            fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                        "RSDP structure not found");
            _Kinc_warning ("0004", PRINT, __LINE__, __FILE__, GetMasterLogHandle (), OUTPUT_DATA);
            ErrorCheck = E_NO_ACPI_TBLS;
        }
        
        else
        {
            if (FilePtr == NULL)
            {
                fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA, "RSDP located at %lXh", RSDP);
            }
            
            else
            {
                fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                            "RSDP located at %lXh", RsdpOriginalLocation);
                
                /* 
                 * Since we're working from an input file, assume we're running on
                 * legacy hardware.  This is intended to prevent any accesses to the
                 * hardware since the ACPI tables are probably not valid for the
                 * current hardware 
                 */
                
                Capabilities = LEGACY_MODE;
            }


            /* Since we found the RSDP, enumerate all tables... */
            /* first is the RSDT */
            
            RSDT = GetTable (RSDP->RsdtPhysicalAddress, FilePtr);

            if (strncmp (RSDT->header.Signature, RSDT_SIG, 4))
            {
                fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                            "RSDP indicates RSDT should be located at %lXh, however the table"
                            "\n  signature at %lXh is incorrect."
                            "\n  Expected signature: 'RSDT'  Actual signature: '%4.4s'",
                            RSDP->RsdtPhysicalAddress, RSDP->RsdtPhysicalAddress,
                            RSDT->header.Signature);

                _Kinc_error ("0005", PRINT, __LINE__, __FILE__, GetMasterLogHandle (), OUTPUT_DATA);
                ErrorCheck |= E_ERROR;
            }
            
            else
            {
                fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                            "RSDT located at %lXh", RSDP->RsdtPhysicalAddress);
            }
            
            ErrorCheck |= VerifyTableChecksum (RSDT, OUTPUT_DATA | OUTPUT_ERRORS);

            /* next enumerate all table pointers found in the RSDT */

            NumberOfTables = (INT32) (RSDT->header.Length - sizeof (ACPI_TABLE_HEADER)) / 4;

            for (Index = 0; Index < NumberOfTables; Index++)
            {
                TableHeader = GetTable (RSDT->TableOffsetEntry[Index], FilePtr);

                if (!strncmp (TableHeader->Signature, FACP_SIG, 4))
                {
                    FACP = (FIXED_ACPI_DESCRIPTION_TABLE *) TableHeader;
                    fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                                "FACP located at %lXh", RSDT->TableOffsetEntry[Index]);

                    ErrorCheck |= VerifyTableChecksum (FACP, OUTPUT_DATA | OUTPUT_ERRORS);

                    FACS = GetFACS (FilePtr);
                    fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                                "FACS located at %lXh", FACP->FirmwareCtrl);

                    if (HardwareOverride)
                    {
                        fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                                    "DSDT not loaded from file when hardware override is enabled.  AML access"
                                    "\n  prohibited.");
                    }
                    
                    else
                    {
                        if (DsdtFile)
                        {
                            FILE        *DsdtFilePtr = OsdOpen (DsdtFile, "rb");

                            if (DsdtFilePtr)
                            {
                                DSDT = GetTable (FACP->Dsdt, DsdtFilePtr);
                                OsdClose (DsdtFilePtr);
                            }
                            
                            else
                            {
                                fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                                            "Unable to open file \"%s\"", DsdtFile);
                                _Kinc_error ("0006", PRINT, __LINE__, __FILE__,
                                                GetMasterLogHandle (), OUTPUT_DATA);
                                ErrorCheck = E_FILE_NOT_EXIST;
                            }
                        }
                        
                        else
                        {
BREAKPOINT3;
                            DSDT = GetTable (FACP->Dsdt, FilePtr);
                        }

                        if (DSDT)
                        {
                            fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                                        "DSDT located at %lXh", FACP->Dsdt);
                            ErrorCheck |= VerifyTableChecksum (DSDT,
                                                    OUTPUT_DATA | OUTPUT_ERRORS);

#ifdef _DEBUG
                            if (debug_level () >= HEX_DUMP_DEBUG_LEVEL)
                            {
                                fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                                            "Hex dump of DSDT (not including header), size %d (0x%x)\n",
                                            (size_t)DSDT->Length, (size_t)DSDT->Length);
                                DumpBuffer ((UINT8 *) (DSDT + 1),
                                                (size_t)DSDT->Length, HEX | ASCII);
                            }
#endif
                        }
                    }
                }
                
                else if (!strncmp (TableHeader->Signature, APIC_SIG, 4))
                {
                    MAPIC = (APIC_TABLE *) TableHeader;
                    fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                                "APIC Table located at %lXh", RSDT->TableOffsetEntry[Index]);
                    ErrorCheck |= VerifyTableChecksum (MAPIC, OUTPUT_DATA | OUTPUT_ERRORS);
                }
                
                else if (!strncmp (TableHeader->Signature, PSDT_SIG, 4))
                {
                    PSDT = TableHeader;
                    fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                                "PSDT located at %lXh", RSDT->TableOffsetEntry[Index]);
                    ErrorCheck |= VerifyTableChecksum (PSDT, OUTPUT_DATA | OUTPUT_ERRORS);
                }
                else if (!strncmp (TableHeader->Signature, SSDT_SIG, 4))
                {
                    /* TBD - need to be able to deal with multiple SSDTs */
                    
                    SSDT = TableHeader;
                    fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                                "SSDT located at %lXh", RSDT->TableOffsetEntry[Index]);
                    ErrorCheck |= VerifyTableChecksum (SSDT, OUTPUT_DATA | OUTPUT_ERRORS);
                }
                else if (!strncmp (TableHeader->Signature, SBDT_SIG, 4))
                {
                    SBDT = TableHeader;
                    fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                                "SBDT located at %lXh", RSDT->TableOffsetEntry[Index]);
                    ErrorCheck |= VerifyTableChecksum (SBDT, OUTPUT_DATA | OUTPUT_ERRORS);
                }
                else
                {
                    fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                                "Unknown table listed in RSDT with signature '%4.4' located at %lXh",
                                TableHeader->Signature, RSDT->TableOffsetEntry[Index]);
                    ErrorCheck |= VerifyTableChecksum (TableHeader, OUTPUT_DATA | OUTPUT_ERRORS);
                    
                    /* 
                     * !! TBD - need to be able to handle multiple unknown tables.  Error should be
                     *  displayed when tables is displayed,  Displaying it here for now 
                     */
                    
                    DisplayTable (&RSDT->header, OUTPUT_DATA | OUTPUT_ERRORS);
                }
            }
            
            if (FilePtr != NULL)
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
    }
    
    if (OutputFile != NULL && InputFile == NULL && ErrorCheck != E_NO_ACPI_TBLS)
    {
        FilePtr = OsdOpen (OutputFile, "wb");
        if (FilePtr != NULL)
        {
            OsdWrite (ACPILIB_DATA_FILE_VERSION, strlen (ACPILIB_DATA_FILE_VERSION),
                        (size_t) 1, FilePtr);
            
            RsdpOriginalLocation = (UINT32) PtrOffset (RSDP);

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
            fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                        "Error creating output file \"%s\"", OutputFile);
            _Kinc_error ("0007", PRINT, __LINE__, __FILE__, GetMasterLogHandle (), OUTPUT_DATA);
        }
    }

    DecIndent ();

    if (ErrorCheck == E_OK && !(Capabilities & ~(ACPI_MODE | LEGACY_MODE)))
    {
        switch (Capabilities)
        {
            case (ACPI_MODE):
                OriginalMode = ACPI_MODE;
                fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                            "System supports ACPI mode only.\n");
                break;

            case (LEGACY_MODE):
                if (HardwareOverride)
                {
                    fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                                "ACPI table data loaded from file, but hardware override was enabled so ACPI"
                                "\n  hardware is assumed.\n");
                    Capabilities = ACPI_MODE | LEGACY_MODE;
                }
                
                else
                {
                    OriginalMode = LEGACY_MODE;
                    fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                                "Tables loaded from file, hardware assumed to support LEGACY mode only.\n");
                    break;
                }

            case (ACPI_MODE | LEGACY_MODE):
                (AcpiModeStatus () == ACPI_MODE) ? (OriginalMode = ACPI_MODE) : (OriginalMode = LEGACY_MODE);

                fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                            "System supports both ACPI and LEGACY modes.");

                fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                            "  System is currently in %s mode.",
                            (OriginalMode == ACPI_MODE) ? "ACPI" : "LEGACY");
                break;
        }


BREAKPOINT3;

        if (Capabilities != LEGACY_MODE)
        {
            INT32         Index;

            /* This block of code is only executed if the tables were loaded from
                memory or HardwareOverride is set.  It is skipped if the tables
                are loaded from a file and HardwareOverride is not set. */

            /* the purpose of this block of code is to save the initial state of
                the ACPI event enable registers.  An exit function will be
                registered which will restore this state when the application
                exits.  The exit function will also clear all of the ACPI event
                status bits prior to restoring the original mode */

            /* The location of the PM1aEvtBlk enable registers is defined as the
                base of PM1aEvtBlk + PM1aEvtBlkLength / 2.  Since the spec further
                fully defines the PM1aEvtBlk to be a total of 4 bytes, the offset
                for the enable registers is always 2 from the base.  It is hard
                coded here.  If this changes in the spec, this code will need to
                be modified.  The PM1bEvtBlk behaves as expected. */

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

                Gpe0EnableRegisterSave = OsdAllocate ((size_t) (FACP->Gpe0BlkLen / 2));
                OsdAssert (Gpe0EnableRegisterSave);
                RegisterStaticBlockPtr ((void **) &Gpe0EnableRegisterSave);

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
                Gpe1EnableRegisterSave = OsdAllocate ((size_t) (FACP->Gpe1BlkLen / 2));
                OsdAssert (Gpe1EnableRegisterSave);
                RegisterStaticBlockPtr ((void **) &Gpe1EnableRegisterSave);

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
        }

        fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                    "ACPILIB successfully initialized.");

        AcpiHook = 2;              /* indicate to the outside world we're up and OK ... */
    }
    
    else
    {
        if (!ErrorCheck && (!Capabilities || (Capabilities & ~(ACPI_MODE | LEGACY_MODE))))
        {
            fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                        "Internal ACPILIB error.  Capabilities not initialized correctly by AcpiInit()\n");
            ErrorCheck |= E_ERROR;
        }

        fprintf_bu (GetMasterLogHandle (), OUTPUT_DATA,
                    "ACPILIB NOT successfully initialized.");
    }

    return (ErrorCheck);
}
