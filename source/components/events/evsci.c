/*__________________________________________________________________________
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
 | ModuleName: evsci - System Control Interrupt configuration and
 |                      legacy to ACPI mode state transition functions
 |__________________________________________________________________________
*/

#define __EVSCI_C__

#include <acpi.h>
#include <namespace.h>
#include <devices.h>
#include <events.h>


#define _THIS_MODULE        "evsci.c"
#define _COMPONENT          EVENT_HANDLING

extern INT32                __AcpiLibInitStatus;


INT32                       EdgeLevelSave   = SAVE_NOT_VALID;
INT32                       IrqEnableSave   = SAVE_NOT_VALID;
INT32                       OriginalMode    = SAVE_NOT_VALID;   /*  original ACPI/legacy mode   */


static ST_KEY_DESC_TABLE KDT[] = {
   {"0000", '1', "", ""},	/*	obsolete	*/
   {"0001", 'W', "", ""},	/*	obsolete: SCI edge sensitivity in legacy mode	*/
   {"0002", '1', "ACPI tables are required but not available", "ACPI tables are required but not available"},
   {"0003", '1', "", ""},	/*	obsolete	*/
   {"0004", '1', "", ""},	/*	obsolete	*/
   {"0005", '1', "Unable to transition to ACPI Mode", "Unable to transition to ACPI Mode"},
   {"0006", '1', "Unable to install System Control Interrupt Handler", "Unable to install System Control Interrupt Handler"},
   {"0007", 'W', "Unable to restore interrupt to edge sensitivity", "Unable to restore interrupt to edge sensitivity"},
   {"0008", 'W', "Unable to restore interrupt to disable", "Unable to restore interrupt to disable"},
   {"0009", 'W', "Unable to transition to Original Mode", "Unable to transition to Original Mode"},
   {"0010", '1', "ACPI namespace failed to load correctly", "ACPI namespace failed to load correctly"},
   {"0011", '1', "Unable to enable SCI interrupt", "Unable to enable SCI interrupt"},
   {NULL, 'I', NULL, NULL}
};

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
        /*	ACPI tables are not available	*/

        REPORT_ERROR (&KDT[2]);

        ErrorMask = NO_ACPI_TABLES_MASK;
    }

    return ErrorMask;
}


/**************************************************************************
 *
 * FUNCTION:    AcpiEnable
 *
 * PARAMETERS:  TestName        pointer to test name string for log messages
 *              Flags           flag bitmask (logical OR) to specify:
 *                              ACPI_TABLES_REQUIRED, HW_OVERRIDE_SUPPORTED,
 *                              PROGRAM_SCI_LEVEL_SENSITIVITY, DISABLE_KNOWN_EVENTS
 *
 * RETURN:      0 if successful; non-zero if failure encountered
 *
 * DESCRIPTION: Ensures that the system
 *              control interrupt (SCI) is properly configured, disables
 *              SCI event sources, installs the SCI handler, and
 *              transfers the system into ACPI mode.
 *              If successful, return 0. Otherwise, return non-zero.
 *
 *************************************************************************/

INT32        
AcpiEnable (char *TestName, INT32 Flags)
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

            /*	TBD:	verify input file specified	*/

            DEBUG_PRINT (ACPI_WARN, ("Only legacy mode supported\n"));
        }


        OriginalMode = AcpiModeStatus ();

        if (Flags & DISABLE_KNOWN_EVENTS)
        {   
            /*  disable any ACPI interrupt sources that may be enabled  */

            DISABLE_EVENT (TMR_FIXED_EVENT);
            DISABLE_EVENT (GBL_FIXED_EVENT);
            DISABLE_EVENT (PWR_BTN_FIXED_EVENT);
            DISABLE_EVENT (SLP_BTN_FIXED_EVENT);
            DISABLE_EVENT (RTC_FIXED_EVENT);
        }

        else
        {
            /* Enable everything */

            ENABLE_EVENT (TMR_FIXED_EVENT);
            ENABLE_EVENT (GBL_FIXED_EVENT);
            ENABLE_EVENT (PWR_BTN_FIXED_EVENT);
            ENABLE_EVENT (SLP_BTN_FIXED_EVENT);
            ENABLE_EVENT (RTC_FIXED_EVENT);
        }

        if (InstallSciHandler () == 0)
        {   
            /*	Unable to install SCI handler	*/

            REPORT_ERROR (&KDT[6]);
			ErrorMask |= NO_SCI_HANDLER_MASK;
		}

        else
        {
            /*  SCI Interrupt Handler installed properly    */

			if (ACPI_MODE != OriginalMode)
			{	
                /*	legacy mode	*/
				
                if (E_OK == AcpiSetMode (ACPI_MODE))
                {
					DEBUG_PRINT (ACPI_SUCCESS, ("Transition to ACPI mode successful\n"));
                }

				else
				{	
                    /*	Unable to transition to ACPI Mode	*/
					
                    REPORT_ERROR (&KDT[5]);
					ErrorMask |= NO_ACPI_TRANSITION_MASK;
				}
			}

			if (ACPI_MODE == AcpiModeStatus ())
			{	
                /*	verify SCI sensitivity while in ACPI mode	*/

/* TOO LOW LEVEL?? !!! TBD                 
                if (GlobalProgramSCI ||	
					 (Flags & PROGRAM_SCI_LEVEL_SENSITIVITY))
					ErrorMask |= iInitializeSCI (TRUE);
				else
					ErrorMask |= iInitializeSCI (FALSE);
*/
			}
        }

		if (LOAD_ACPI_NAMESPACE & Flags)
		{	
            /*	load ACPI namespace	*/

            DEBUG_PRINT (ACPI_INFO, ("Loading ACPI namespace\n"));
			if (AcpiLoadNameSpace (FALSE))
			{
                REPORT_ERROR (&KDT[10]);
				ErrorMask |= UNABLE_TO_LOAD_NAMESPACE;
			}
			else
            {
				DEBUG_PRINT (ACPI_INFO, ("ACPI namespace loaded\n"));
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
        REPORT_WARNING (&KDT[9]);
        
        /*  ErrorMask |= NO_LEGACY_TRANSITION_MASK;    */
    }

    /*  unload SCI handler  */

    UninstallSciHandler ();


    AcpiCleanup ();

    return ErrorMask;
}
