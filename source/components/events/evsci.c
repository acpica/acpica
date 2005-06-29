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
 | FILENAME: scilast.c -  System Control Interrupt configuration and
 |                                  legacy to ACPI mode state transition functions
 |__________________________________________________________________________
 |
 | $Revision: 1.2 $
 | $Date: 2005/06/29 16:43:40 $
 | $Log: evsci.c,v $
 | Revision 1.2  2005/06/29 16:43:40  aystarik
 | Detabified.
 |
 | 
 | date	99.01.12.00.08.00;	author grsmith1;	state Exp;
 |
 * 
 * 2     1/11/99 4:08p Grsmith1
 * Detabified.
 * 
 * 1     1/11/99 2:08p Rmoore1
 * Event Handling
// 
//    Rev 1.4   11 Sep 1998 18:03:28   phutchis
// Change inc_error() etc. to dKinc_error() etc. (error key logging).
// 
//    Rev 1.3   14 Aug 1998 17:46:14   jkreinem
// Added iVerifyAcpiTablesPresent() function and NO_ACPI_TABLES_MASK
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

#define __SCILAST_C__

#include <bu.h>
#include "acpi.h"
#include "acpievnt.h"
#include "acpilgcy.h"
#include "hwoverrd.h"
#include "evsci.h"

extern int  __iAcpiLibInitStatus;


/**************************************************************************
 *  FUNCTION:       int iInitializeSCI
 *
 *  PARAMETERS:
 *      iProgramSCI --  TRUE if SCI can be reprogrammed to level sensitivity
 *                          FALSE if current SCI sensitivity must be preserved
 *
 *  RETURN:         0 if successful; non-zero if failure encountered
 *
 *  DESCRIPTION:    iInitializeSCI() ensures that the system control
 *                      interrupt (SCI) is properly configured.
 *                      If successful, return 0. Otherwise, return non-zero.
 *************************************************************************/
/*
int iInitializeSCI (int iProgramSCI)
{
    int iErrorMask=0, iStatusOfIrq;

//  enter_function (GetMasterLogHandle(), LOGFILE, "iInitializeSCI",
//      "iProgramSCI=%d", iProgramSCI);

    //  Set up the System Control Interrupt (SCI) as required.
    //  If it is installed, verify it is level not edge triggered.
    //  If it is edge triggered, bail.
    //

    iIrqEnabledAtPic (pFACP->wSciInt, &iStatusOfIrq);
    if (SAVE_NOT_VALID == iIrqEnableSave)
    {
        iIrqEnableSave = iStatusOfIrq;
        trace_bu (debug_level() >= 4, __FILE__, __LINE__,
            "iInitializeSCI: iIrqEnableSave=%d (%sabled)", iIrqEnableSave,
            iIrqEnableSave ? "dis" : "en");
    }

    if (IRQ_DISABLE != iStatusOfIrq)
    {   
        //  SCI interrupt already enabled

        iIrqAttributesAtPic (pFACP->wSciInt, &iStatusOfIrq);
        if (SAVE_NOT_VALID == iEdgeLevelSave)
        {
            iEdgeLevelSave = iStatusOfIrq;
            trace_bu (debug_level() >= 4, __FILE__, __LINE__,
                "iInitializeSCI: iEdgeLevelSave=%d (%s)", iEdgeLevelSave,
                iEdgeLevelSave ? "level" : "edge");
        }

        if (IRQ_EDGE == iStatusOfIrq)
        {   
            //   SCI interrupt is edge sensitive

            printf_bu ("\nInterrupt %02Xh is Enabled/Edge sensitive and the"
                "\nSCI handler requires it to be Level sensitive.", pFACP->wSciInt);

            if (iProgramSCI)
            {   
                //  set SCI to Level Triggered

                iSetIrqToLevel (pFACP->wSciInt);
                iIrqAttributesAtPic (pFACP->wSciInt, &iStatusOfIrq);

                if (IRQ_EDGE == iStatusOfIrq)
                    printf_bu ("\n  Unable to reprogram SCI interrupt %d to level sensitivity",
                        pFACP->wSciInt);
                else
                    printf_bu ("\n  Interrupt %02Xh reprogrammed to level sensitive\n",
                        pFACP->wSciInt);
            }

            if (IRQ_EDGE == iStatusOfIrq)
            {   
                    //  SCI interrupt is still edge sensitive

                if (ACPI_MODE == AcpiModeStatus())
                {   
                        //  edge level sensitivity in ACPI mode

                    dKinc_error ("0000", PRINT | APPEND_CRLF);
                    iErrorMask |= SCI_LEVEL_INT_MASK;
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

        iEnableIrqAtPic (pFACP->wSciInt);

            //  Set it to Level Triggered

        iSetIrqToLevel (pFACP->wSciInt);
    }

//  exit_function (GetMasterLogHandle(), LOGFILE,
//      "iInitializeSCI", "iErrorMask=%d", iErrorMask);

    return iErrorMask;

}


/**************************************************************************
 *  FUNCTION:       int iVerifyAcpiTablesPresent
 *
 *  PARAMETERS:
 *      pcTestName  --  pointer to test name string for log messages
 *
 *  RETURN:
 *      0               if tables are present
 *      non-zero        if ACPI tables can NOT be located
 *
 *  DESCRIPTION:    iVerifyAcpiTablesPresent() ensures that the current
 *                      environment contains ACPI (namespace) tables from
 *                      either the BIOS or from an input file.
 *                      Return 0 if tables are present; non-zero otherwise.
 *************************************************************************/

int iVerifyAcpiTablesPresent (char *pcTestName)
{
    int iErrorMask=0;

//  enter_function (GetMasterLogHandle(), LOGFILE, "iVerifyAcpiTablesPresent",
//      NULL);

    if (__iAcpiLibInitStatus == E_NO_ACPI_TBLS)
    {
        printf_bu ("\nACPI tables are required for %s but not available",
            pcTestName);
        dKinc_error ("0002", PRINT | APPEND_CRLF);

        iErrorMask = NO_ACPI_TABLES_MASK;
        printf_bu ("\nACPI tables can be loaded from an input file."
            "\nCommand line help is available with the '/?' switch.\n");
    }

//  exit_function (GetMasterLogHandle(), LOGFILE,
//      "iVerifyAcpiTablesPresent", "iErrorMask=%d", iErrorMask);

    return iErrorMask;

}   /*  iVerifyAcpiTablesPresent    */


/**************************************************************************
 *  FUNCTION:       int iInstallSCIHandlerXferToACPI
 *
 *  PARAMETERS:
 *      pcTestName  --  pointer to test name string for log messages
 *      iFlags      --  flag bitmask (logical OR) to specify:
 *                          ACPI_TABLES_REQUIRED, HW_OVERRIDE_SUPPORTED,
 *                          PROGRAM_SCI_LEVEL_SENSITIVITY, DISABLE_KNOWN_EVENTS
 *
 *  RETURN:         0 if successful; non-zero if failure encountered
 *
 *  DESCRIPTION:    iInstallSCIHandlerXferToACPI() ensures that the system
 *                      control interrupt (SCI) is properly configured, disables
 *                      SCI event sources, installs the SCI handler, and
 *                      transfers the system into ACPI mode.
 *                      If successful, return 0. Otherwise, return non-zero.
 *************************************************************************/

int AcpiEnable (char *pcTestName, int iFlags)
{
    int iErrorMask=0;

//  enter_function (GetMasterLogHandle(), LOGFILE,
//      "iInstallSCIHandlerXferToACPI", "pcTestName=%p, iFlags=%d",
//      pcTestName, iFlags);

    if (NULL == pcTestName)
        pcTestName = "";    /*  create valid pointer    */

    if (iFlags & ACPI_TABLES_REQUIRED)
        iErrorMask |= iVerifyAcpiTablesPresent (pcTestName);

    if (E_OK == iErrorMask)
    {   /*  ACPI tables are available or not required   */

        if (LEGACY_MODE == AcpiModeCapabilities ())
        {   /*  no ACPI mode support provided by BIOS   */
            /*  The only way to get through sign_on() without ACPI support is
             *  if we are running from an input file.
             */

            if (iFlags & HW_OVERRIDE_SUPPORTED)
            {   /*  hardware over-ride supported    */

                if (!iHardwareOverrideStatus())
                {   /*  hardware over-ride not specified    */
                    printf_bu ("\n%s execution from input table requires HwOverride\n",
                        pcTestName);
                    dKinc_error ("0003", PRINT | APPEND_CRLF);
                }
            }   /*  hardware over-ride supported    */

            else
            {   /*  hardware over-ride not supported    */
                printf_bu ("\n%s does NOT support execution from input table with HwOverride\n",
                    pcTestName);
                dKinc_error ("0004", PRINT | APPEND_CRLF);
            }
        }   /*  no ACPI mode support provided by BIOS   */

        iOriginalMode = AcpiModeStatus();

        /*  do not change the SCI sensitivity while in legacy mode  */

// TOO LOW LEVEL FOR OS-independent code!!
//
//      iErrorMask |= iInitializeSCI (FALSE);

        if (0 == iErrorMask)
        {   /*  SCI configured correctly    */

            if (iFlags & DISABLE_KNOWN_EVENTS)
            {   /*  disable any ACPI interrupt sources that may be enabled  */

                iAcpiEventDisableEvent (TMR_FIXED_EVENT);
                iAcpiEventDisableEvent (GBL_FIXED_EVENT);
                iAcpiEventDisableEvent (PWR_BTN_FIXED_EVENT);
                iAcpiEventDisableEvent (SLP_BTN_FIXED_EVENT);
                iAcpiEventDisableEvent (RTC_FIXED_EVENT);
            }   /*  disable any ACPI interrupt sources that may be enabled  */

            if (wInstallSciHandler())
            {   /*  SCI Interrupt Handler installed properly    */

                if (E_OK == AcpiSetMode (ACPI_MODE))
                {   /*  in ACPI mode    */

                    printf_bu ("\nTransition to ACPI mode successful\n");

                    /*  verify SCI sensitivity while in ACPI mode   */
// Nope, DON'T DO IT
//                  iErrorMask |= iInitializeSCI (iFlags & PROGRAM_SCI_LEVEL_SENSITIVITY);
                }

                else
                {
                    printf_bu ("\nUnable to transition to ACPI Mode");
                    dKinc_error ("0005", PRINT | APPEND_CRLF);
                    vSetNotSupported ();
                    iErrorMask |= NO_ACPI_TRANSITION_MASK;
                }
            }   /*  SCI Interrupt Handler installed properly    */

            else
            {
                printf_bu ("\nUnable to install the System Control Interrupt Handler");
                dKinc_error ("0006", PRINT | APPEND_CRLF);
                iErrorMask |= NO_SCI_HANDLER_MASK;
            }
        }   /*  SCI configured correctly    */
    }   /*  ACPI tables are available or not required   */

//  exit_function (GetMasterLogHandle(), LOGFILE,
//      "iInstallSCIHandlerXferToACPI", "iErrorMask=%d", iErrorMask);

    return iErrorMask;

}   /*  iInstallSCIHandlerXferToACPI    */

    
/**************************************************************************
 *  FUNCTION:       int iUninstallSCIHandlerXferToLegacy
 *
 *  PARAMETERS:     none
 *
 *  RETURN:         0 if successful; non-zero if failure encountered
 *
 *  DESCRIPTION:    iUninstallSCIHandlerXferToLegacy() returns the system
 *                      to original ACPI/legacy mode, unloads the SCI handler,
 *                      and restores the SCI to its original configuration.
 *                      If successful, return 0. Otherwise, return non-zero.
 *************************************************************************/

int AcpiDisable ()
{
    int iErrorMask=0;

//  enter_function (GetMasterLogHandle(), LOGFILE,
//      "vUninstallSCIHandlerXferToLegacy", NULL);

    /*  restore IRQ before returning to legacy mode */

    if (IRQ_EDGE == iEdgeLevelSave)
    {
        trace_bu (debug_level() >= 4, __FILE__, __LINE__,
            "iUninstallSCIHandlerXferToLegacy: Restore IRQ %d to edge sensitivity",
            pFACP->wSciInt);

/* Don't fuss with PIC here !!!

        if (iSetIrqToEdge (pFACP->wSciInt))
        {
            printf_bu ("\nUnable to restore interrupt %d to edge sensitivity",
                pFACP->wSciInt);
            dKinc_warning ("0007", PRINT | APPEND_CRLF);
            //  iErrorMask |= SCI_LEVEL_INT_MASK;
        }
        else
            printf_bu ("\nInterrupt %d restored to edge sensitivity\n",
                pFACP->wSciInt);
*/

    }

/* Don't fuss with PIC here !!!

    if (IRQ_DISABLE == iIrqEnableSave)
    {
        trace_bu (debug_level() >= 4, __FILE__, __LINE__,
            "iUninstallSCIHandlerXferToLegacy: Restore interrupt %d to disable",
            pFACP->wSciInt);

        if (iDisableIrqAtPic (pFACP->wSciInt))
        {
            printf_bu ("\nUnable to restore interrupt %d to disable",
                pFACP->wSciInt);
            dKinc_warning ("0008", PRINT | APPEND_CRLF);
        }

        else
            printf_bu ("\nInterrupt %d restored to disable\n", pFACP->wSciInt);
    }
*/

    /*  restore original mode   */

    if (E_OK != AcpiSetMode (iOriginalMode))
    {
        printf_bu ("\nUnable to transition to the Original Mode");
        dKinc_warning ("0009", PRINT | APPEND_CRLF);
        /*  iErrorMask |= NO_LEGACY_TRANSITION_MASK;    */
    }

    /*  unload SCI handler  */

    vUninstallSciHandler();

//  exit_function (GetMasterLogHandle(), LOGFILE,
//      "vUninstallSCIHandlerXferToLegacy", "iErrorMask=%d", iErrorMask);

    return iErrorMask;

}   /*  iUninstallSCIHandlerXferToLegacy    */
