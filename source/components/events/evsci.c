/*
  __________________________________________________________________________
 |
 |
 |           Copyright (C) Intel Corporation 1994-1998
 |
 | All rights reserved. No part of this program or publication may be
 | reproduced, transmitted, transcribed, stored in a retrieval system, or
 | translated into any language or computer language, in any form or by any
 | means, electronic, mechanical, magnetic, optical, chemical, manual, or
 | otherwise, without the prior written permission of Intel Corporation.
 |__________________________________________________________________________
 |
 | System Control Interrupt configuration and
 | legacy to ACPI mode state transition functions
 |__________________________________________________________________________
 |
 | $Revision: 1.8 $
 | $Date: 2005/06/29 16:43:46 $
 | $Log: evsci.c,v $
 | Revision 1.8  2005/06/29 16:43:46  aystarik
 | 16/32/64-bit common data types
 |
 | 
 | date	99.03.10.00.05.00;	author rmoore1;	state Exp;
 |
 * 
 * 8     3/09/99 4:05p Rmoore1
 * 16/32/64-bit common data types
 * 
 * 7     2/16/99 9:56a Rmosgrov
 * 
 * 6     2/11/99 5:27p Grsmith1
 * Took out Hungarian Notation
 * 
 * 5     2/03/99 4:08p Rmoore1
 * 
 * 4     1/20/99 9:39a Rmoore1
 * Major cleanup
 * 
 * 3     1/13/99 2:49p Grsmith1
 * First BeOS build.
 * 
 * 2     1/11/99 4:08p Grsmith1
 * Detabified.
 * 
 * 1     1/11/99 2:08p Rmoore1
 * Event Handling
// 
//    Rev 1.4   11 Sep 1998 18:03:28   phutchis
// Change inc_error() etc. to Kinc_error() etc. (error key logging).
// 
//    Rev 1.3   14 Aug 1998 17:46:14   jkreinem
// Added VerifyAcpiTablesPresent() function and NO_ACPI_TABLES_MASK
// error code.
// 
//    Rev 1.2   13 Aug 1998 17:28:54   jkreinem
// Added SAVE_NOT_VALID definition for interrupt configuration.
// Enhanced failure messages and debug output.
// 
//    Rev 1.1   12 Aug 1998 16:31:04   jkreinem
// Improved SCI configuration and legacy to ACPI transition log messages.
// 
//    Rev 1.0   12 Aug 1998 15:54:34   jkreinem
// Initial revision.
 |__________________________________________________________________________

*/

#define __EVSCI_C__
#define _THIS_MODULE        "evsci.c"

#include <bu.h>
#include "acpi.h"
#include "acpievnt.h"
#include "acpilgcy.h"
#include "hwoverrd.h"
#include "evsci.h"
#include "acpitbls.h"

extern INT32         __AcpiLibInitStatus;


/**************************************************************************
 *
 * FUNCTION:    InitializeSCI
 *
 * PARAMETERS:  ProgramSCI     TRUE if SCI can be reprogrammed to level sensitivity
 *                              FALSE if current SCI sensitivity must be preserved
 *
 * RETURN:      0 if successful; non-zero if failure encountered
 *
 * DESCRIPTION: InitializeSCI() ensures that the system control
 *              interrupt (SCI) is properly configured.
 *              If successful, return 0. Otherwise, return non-zero.
 *
 *************************************************************************/

/* TOO LOW LEVEL FOR OS=INDEPENDENT CODE !!! */


/*
INT32        InitializeSCI (INT32        ProgramSCI)
{
    INT32            ErrorMask=0, StatusOfIrq;


    //  Set up the System Control Interrupt (SCI) as required.
    //  If it is installed, verify it is level not edge triggered.
    //  If it is edge triggered, bail.
    //

    IrqEnabledAtPic (FACP->SciInt, &StatusOfIrq);
    if (SAVE_NOT_VALID == IrqEnableSave)
    {
        IrqEnableSave = StatusOfIrq;
        trace_bu (debug_level() >= 4, __FILE__, __LINE__,
            "InitializeSCI: IrqEnableSave=%d (%sabled)", IrqEnableSave,
            IrqEnableSave ? "dis" : "en");
    }

    if (IRQ_DISABLE != StatusOfIrq)
    {   
        //  SCI interrupt already enabled

        IrqAttributesAtPic (FACP->SciInt, &StatusOfIrq);
        if (SAVE_NOT_VALID == EdgeLevelSave)
        {
            EdgeLevelSave = StatusOfIrq;
            trace_bu (debug_level() >= 4, __FILE__, __LINE__,
                "InitializeSCI: EdgeLevelSave=%d (%s)", EdgeLevelSave,
                EdgeLevelSave ? "level" : "edge");
        }

        if (IRQ_EDGE == StatusOfIrq)
        {   
            //   SCI interrupt is edge sensitive

            printf_bu ("\nInterrupt %02Xh is Enabled/Edge sensitive and the"
                "\nSCI handler requires it to be Level sensitive.", FACP->SciInt);

            if (ProgramSCI)
            {   
                //  set SCI to Level Triggered

                SetIrqToLevel (FACP->SciInt);
                IrqAttributesAtPic (FACP->SciInt, &StatusOfIrq);

                if (IRQ_EDGE == StatusOfIrq)
                    printf_bu ("\n  Unable to reprogram SCI interrupt %d to level sensitivity",
                        FACP->SciInt);
                else
                    printf_bu ("\n  Interrupt %02Xh reprogrammed to level sensitive\n",
                        FACP->SciInt);
            }

            if (IRQ_EDGE == StatusOfIrq)
            {   
                    //  SCI interrupt is still edge sensitive

                if (ACPI_MODE == AcpiModeStatus())
                {   
                        //  edge level sensitivity in ACPI mode

                    Kinc_error ("0000", PRINT | APPEND_CRLF);
                    ErrorMask |= SCI_LEVEL_INT_MASK;
                    printf_bu ("    Failure Explanation:");
                    printf_bu ("\n      ACPI Specification 1.0(a) sections 4.7.2.5, 5.2.5, and 5.6.1");
                    printf_bu ("\n      specify that the system control interrupt must be sharable, level");
                    printf_bu ("\n      sensitive, active low, and mapped to a declared interrupt vector.\n");
                }

                else
                {
                    //  edge level sensitivity in legacy (non-ACPI) mode
                    //  To prevent legacy mode interrupt handling problems where
                    //  interrupt handlers expect the interrupt to be configured
                    //  edge sensitive, just issue warning since we may be allowed
                    //  to reprogram the interrupt to level sensitivity after
                    //  transitioning into ACPI mode.
                    //
                    dKinc_warning ("0001", PRINT | APPEND_CRLF);

            }
        }
    }
    else
    {   
            //  SCI interrupt disabled
            //  Enable the SCI Interrupt

        EnableIrqAtPic (FACP->SciInt);

            //  Set it to Level Triggered

        SetIrqToLevel (FACP->SciInt);
    }


    return ErrorMask;
}


/**************************************************************************
 *
 * FUNCTION:    VerifyAcpiTablesPresent
 *
 * PARAMETERS:  TestName      pointer to test name string for log messages
 *
 * RETURN:      0               if tables are present
 *              non-zero        if ACPI tables can NOT be located
 *
 * DESCRIPTION: VerifyAcpiTablesPresent() ensures that the current
 *              environment contains ACPI (namespace) tables from
 *              either the BIOS or from an input file.
 *              Return 0 if tables are present; non-zero otherwise.
 *
 *************************************************************************/

INT32        
VerifyAcpiTablesPresent (char *TestName)
{
    INT32            ErrorMask = 0;

    FUNCTION_TRACE ("VerifyAcpiTablesPresent");


    if (__AcpiLibInitStatus == E_NO_ACPI_TBLS)
    {
        printf_bu ("\nACPI tables are required for %s but not available",
                    TestName);
        Kinc_error ("0002", PRINT | APPEND_CRLF);

        ErrorMask = NO_ACPI_TABLES_MASK;
        printf_bu ("\nACPI tables can be loaded from an input file."
                    "\nCommand line help is available with the '/?' switch.\n");
    }

    return ErrorMask;
}


/**************************************************************************
 *
 * FUNCTION:    AcpiEnable
 *
 * PARAMETERS:  TestName      pointer to test name string for log messages
 *              Flags          flag bitmask (logical OR) to specify:
 *                              ACPI_TABLES_REQUIRED, HW_OVERRIDE_SUPPORTED,
 *                              PROGRAM_SCI_LEVEL_SENSITIVITY, DISABLE_KNOWN_EVENTS
 *
 * RETURN:      0 if successful; non-zero if failure encountered
 *
 * DESCRIPTION: iInstallSCIHandlerXferToACPI() ensures that the system
 *              control interrupt (SCI) is properly configured, disables
 *              SCI event sources, installs the SCI handler, and
 *              transfers the system into ACPI mode.
 *              If successful, return 0. Otherwise, return non-zero.
 *
 *************************************************************************/

INT32        
AcpiEnable (char *TestName, INT32        Flags)
{
    INT32            ErrorMask = 0;

    FUNCTION_TRACE ("AcpiEnable");


    if (NULL == TestName)
    {
        TestName = "";    /*  create valid pointer    */
    }

    if (Flags & ACPI_TABLES_REQUIRED)
    {
        ErrorMask |= VerifyAcpiTablesPresent (TestName);
    }

    if (E_OK == ErrorMask)
    {   
        /*  ACPI tables are available or not required   */

        if (LEGACY_MODE == AcpiModeCapabilities ())
        {   
            /*  no ACPI mode support provided by BIOS   */
            /*  The only way to get through sign_on() without ACPI support is
             *  if we are running from an input file.
             */

            if (Flags & HW_OVERRIDE_SUPPORTED)
            {   
                /*  hardware override supported    */

                if (!HardwareOverrideStatus ())
                {   
                    /*  hardware override not specified    */
                    
                    printf_bu ("\n%s execution from input table requires HwOverride\n",
                                TestName);
                    Kinc_error ("0003", PRINT | APPEND_CRLF);
                }
            }

            else
            {   
                /*  hardware override not supported    */
                
                printf_bu ("\n%s does NOT support execution from input table with HwOverride\n",
                            TestName);
                Kinc_error ("0004", PRINT | APPEND_CRLF);
            }
        }

        OriginalMode = AcpiModeStatus ();

        /*  do not change the SCI sensitivity while in legacy mode  */

/* !!! TOO LOW LEVEL FOR OS-independent code!!

      ErrorMask |= InitializeSCI (FALSE);
*/
        if (0 == ErrorMask)
        {   
            /*  SCI configured correctly    */

            if (Flags & DISABLE_KNOWN_EVENTS)
            {   
                /*  disable any ACPI interrupt sources that may be enabled  */

                AcpiEventDisableEvent (TMR_FIXED_EVENT);
                AcpiEventDisableEvent (GBL_FIXED_EVENT);
                AcpiEventDisableEvent (PWR_BTN_FIXED_EVENT);
                AcpiEventDisableEvent (SLP_BTN_FIXED_EVENT);
                AcpiEventDisableEvent (RTC_FIXED_EVENT);
            }

            if (InstallSciHandler ())
            {   
                /*  SCI Interrupt Handler installed properly    */

                if (E_OK == AcpiSetMode (ACPI_MODE))
                {   
                    /*  in ACPI mode    */

                    printf_bu ("\nTransition to ACPI mode successful\n");

                    /*  verify SCI sensitivity while in ACPI mode   */
/* !!! Nope, DON'T DO IT
                    ErrorMask |= InitializeSCI (Flags & PROGRAM_SCI_LEVEL_SENSITIVITY);
*/
                }

                else
                {
                    printf_bu ("\nUnable to transition to ACPI Mode");
                    Kinc_error ("0005", PRINT | APPEND_CRLF);
                    SetNotSupported ();
                    ErrorMask |= NO_ACPI_TRANSITION_MASK;
                }
            }

            else
            {
                printf_bu ("\nUnable to install the System Control Interrupt Handler");
                Kinc_error ("0006", PRINT | APPEND_CRLF);
                ErrorMask |= NO_SCI_HANDLER_MASK;
            }
        }
    }

    return ErrorMask;

}
    

/**************************************************************************
 *
 * FUNCTION:    AcpiDisable
 *
 * PARAMETERS:  none
 *
 * RETURN:      0 if successful; non-zero if failure encountered
 *
 * DESCRIPTION: iUninstallSCIHandlerXferToLegacy() returns the system
 *              to original ACPI/legacy mode, unloads the SCI handler,
 *              and restores the SCI to its original configuration.
 *              If successful, return 0. Otherwise, return non-zero.
 *
 *************************************************************************/

INT32        
AcpiDisable ()
{
    INT32            ErrorMask = 0;

    FUNCTION_TRACE ("AcpiDisable");


    /*  restore IRQ before returning to legacy mode */

/* Don't fuss with PIC here !!!

    if (IRQ_EDGE == EdgeLevelSave)
    {
        trace_bu (debug_level() >= 4, __FILE__, __LINE__,
                    "iUninstallSCIHandlerXferToLegacy: Restore IRQ %d to edge sensitivity",
                    FACP->SciInt);


        if (iSetIrqToEdge (FACP->SciInt))
        {
            printf_bu ("\nUnable to restore interrupt %d to edge sensitivity",
                FACP->SciInt);
            dKinc_warning ("0007", PRINT | APPEND_CRLF);
            //  ErrorMask |= SCI_LEVEL_INT_MASK;
        }
        else
            printf_bu ("\nInterrupt %d restored to edge sensitivity\n",
                FACP->SciInt);

    }
*/

/* Don't fuss with PIC here !!!

    if (IRQ_DISABLE == IrqEnableSave)
    {
        trace_bu (debug_level() >= 4, __FILE__, __LINE__,
            "iUninstallSCIHandlerXferToLegacy: Restore interrupt %d to disable",
            FACP->SciInt);

        if (iDisableIrqAtPic (FACP->SciInt))
        {
            printf_bu ("\nUnable to restore interrupt %d to disable",
                FACP->SciInt);
            dKinc_warning ("0008", PRINT | APPEND_CRLF);
        }

        else
            printf_bu ("\nInterrupt %d restored to disable\n", FACP->SciInt);
    }
*/

    /*  restore original mode   */

    if (E_OK != AcpiSetMode (OriginalMode))
    {
        printf_bu ("\nUnable to transition to the Original Mode");
        Kinc_warning ("0009", PRINT | APPEND_CRLF);
        
        /*  ErrorMask |= NO_LEGACY_TRANSITION_MASK;    */
    }

    /*  unload SCI handler  */

    UninstallSciHandler ();


    AcpiCleanup ();

    return ErrorMask;
}
