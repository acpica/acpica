
/******************************************************************************
 * 
 * Module Name: evsci - System Control Interrupt configuration and
 *                      legacy to ACPI mode state transition functions
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


/* What the hell is this?? #define __EVSCI_C__ */

#include <acpi.h>
#include <namespace.h>
#include <devices.h>
#include <events.h>


#define _THIS_MODULE        "evsci.c"
#define _COMPONENT          EVENT_HANDLING


static ST_KEY_DESC_TABLE KDT[] = {
   {"0000", '1', "ACPI tables are required but not available", "ACPI tables are required but not available"},
   {"0001", '1', "Unable to transition to ACPI Mode", "Unable to transition to ACPI Mode"},
   {"0002", '1', "Unable to install System Control Interrupt Handler", "Unable to install System Control Interrupt Handler"},
   {"0003", 'W', "Unable to restore interrupt to edge sensitivity", "Unable to restore interrupt to edge sensitivity"},
   {"0004", 'W', "Unable to restore interrupt to disable", "Unable to restore interrupt to disable"},
   {"0005", 'W', "Unable to transition to Original Mode", "Unable to transition to Original Mode"},
   {"0006", '1', "ACPI namespace failed to load correctly", "ACPI namespace failed to load correctly"},
   {"0007", '1', "Unable to enable SCI interrupt", "Unable to enable SCI interrupt"},
   {NULL, 'I', NULL, NULL}
};


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
    INT32 ErrorMask = 0;

    FUNCTION_TRACE ("VerifyAcpiTablesPresent");

    if (AcpiLibInitStatus == AE_NO_ACPI_TABLES)
    {
        /*	ACPI tables are not available	*/

        REPORT_ERROR (&KDT[0]);

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

ACPI_STATUS
AcpiEnable (char *TestName, INT32 Flags)
{
    INT32   ErrorMask = 0;

    FUNCTION_TRACE ("AcpiEnable");

    if (NULL == TestName)
    {
        TestName = "";    /*  create valid pointer    */
    }

    if (Flags & ACPI_TABLES_REQUIRED)
    {
        ErrorMask |= VerifyAcpiTablesPresent (TestName);
    }

    if (AE_OK == ErrorMask)
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

		/* CHANGE: right now you can enable all or disable all.  This needs
		   to be split out somehow. */
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

            REPORT_ERROR (&KDT[2]);
			ErrorMask |= NO_SCI_HANDLER_MASK;
		}

        else
        {
            /*  SCI Interrupt Handler installed properly    */

			if (ACPI_MODE != OriginalMode)
			{	
                /*	legacy mode	*/
				
                if (AE_OK == AcpiSetMode (ACPI_MODE))
                {
					DEBUG_PRINT (ACPI_OK, ("Transition to ACPI mode successful\n"));
                }

				else
				{	
                    /*	Unable to transition to ACPI Mode	*/
					
                    REPORT_ERROR (&KDT[1]);
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
                REPORT_ERROR (&KDT[6]);
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
    


/******************************************************************************
 *
 * FUNCTION:    RestoreAcpiState
 *
 * PARAMETERS:  none
 *
 * RETURN:      none
 *
 * DESCRIPTION: Exit function registered by AcpiInit().  This function will
 *              free memory allocated for table storage.
 *
 ******************************************************************************/

void
RestoreAcpiState (void)
{
    INT32 Index;

    FUNCTION_TRACE ("RestoreAcpiState");

    /* restore state of chipset enable bits. */
    
    if (RestoreAcpiChipset == TRUE)
    {
        /* restore the fixed events */
        
        if (OsdIn16 ((UINT16) (FACP->Pm1aEvtBlk + 2)) != Pm1EnableRegisterSave)
        {
            OsdOut16 ((UINT16) (FACP->Pm1aEvtBlk + 2), Pm1EnableRegisterSave);
        }
        
        if (FACP->Pm1bEvtBlk)
        {
            if (OsdIn16 ((UINT16) (FACP->Pm1bEvtBlk + 2)) != Pm1EnableRegisterSave)
            {
                OsdOut16 ((UINT16) (FACP->Pm1bEvtBlk + 2), Pm1EnableRegisterSave);
            }
        }

        /* insure all status bits are clear */
        
        ClearAllAcpiChipsetStatusBits ();

        /* restore the GPEs */
        
        for (Index = 0; Index < FACP->Gpe0BlkLen / 2; Index++)
        {
            if (OsdIn8 ((UINT16)(FACP->Gpe0Blk + FACP->Gpe0BlkLen / 2)) != Gpe0EnableRegisterSave[Index])
            {
                OsdOut8 ((UINT16)(FACP->Gpe0Blk + FACP->Gpe0BlkLen / 2), Gpe0EnableRegisterSave[Index]);
            }
        }

        if (FACP->Gpe1Blk && FACP->Gpe1BlkLen)
        {
            for (Index = 0; Index < FACP->Gpe1BlkLen / 2; Index++)
            {
                if (OsdIn8 ((UINT16)(FACP->Gpe1Blk + FACP->Gpe1BlkLen / 2)) != Gpe1EnableRegisterSave[Index])
                {
                    OsdOut8 ((UINT16)(FACP->Gpe1Blk + FACP->Gpe1BlkLen / 2), Gpe1EnableRegisterSave[Index]);
                }
            }
        }
        
        if (AcpiModeStatus() != OriginalMode)
        {
            AcpiSetMode (OriginalMode);
        }
    }
}


/**************************************************************************
 *
 * FUNCTION:    AcpiDisable
 *
 * PARAMETERS:  none
 *
 * RETURN:      0 if successful; non-zero if failure encountered
 *
 * DESCRIPTION: Returns the system to original ACPI/legacy mode, and 
 *              uninstalls the SCI interrupt handler.
 *              If successful, return 0. Otherwise, return non-zero.
 *
 *************************************************************************/

ACPI_STATUS     
AcpiDisable ()
{
    INT32       ErrorMask = 0;

    FUNCTION_TRACE ("AcpiDisable");

    /* Restore original ACPI mode   */

    if (AE_OK != AcpiSetMode (OriginalMode))
    {
        REPORT_WARNING (&KDT[5]);
        
        /*  ErrorMask |= NO_LEGACY_TRANSITION_MASK;    */
    }

    /* Unload the SCI interrupt handler  */

    UninstallSciHandler ();

    RestoreAcpiState ();
    AcpiLocalCleanup ();

    return ErrorMask;
}
