
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

#include <acpi.h>
#include <namespace.h>
#include <devices.h>
#include <events.h>


#define _THIS_MODULE        "evsci.c"
#define _COMPONENT          EVENT_HANDLING

/* 
 * Elements correspond to counts for
 * TMR, NOT_USED, GBL, PWR_BTN, SLP_BTN, RTC,
 * and GENERAL respectively.  These counts
 * are modified by the ACPI interrupt handler...
 * Note that GENERAL should probably be split out
 * into one element for each bit in the GPE
 * registers 
 */
#ifdef _DEBUG
volatile UINT32         	EventCount[NUM_EVENTS];   
#endif

/******************************************************************************
 *
 * FUNCTION:    FixedEventHandler
 *
 * PARAMETERS:  Event				Event type, defined in events.h
 *
 * RETURN:      INTERRUPT_HANDLED or INTERRUPT_NOT_HANDLED
 *
 * DESCRIPTION: Clears the status bit for the requested event, calls the
 *              handler that previously registered for the event.
 *
 ******************************************************************************/

/* TBD - is this needed?
#pragma check_stack (off)   stack probes MUST be off for any function call in a BU ISR */

static INT32
FixedEventHandler (
	INT32 Event)
{
	/* Clear the status bit, increment the event counter. */
	WRITE_ACPI_REGISTER (TMR_STS + Event, 1);
	
#ifdef _DEBUG
	EventCount[Event]++;
#endif

	/* If there's no handler installed for the event, disable it.
	   Note: this will never happen, but why not check... */
	if (NULL == FixedEventHandlers[Event])
	{
		DEBUG_PRINT (TRACE_INTERRUPTS,
			("Disabling unhandled fixed event %08x.\n", Event));

        /* AcpiDisableFixedEvent (Event);*/
		return INTERRUPT_NOT_HANDLED;
	}
	
	return (FixedEventHandlers[Event]) ();
}
	

/******************************************************************************
 *
 * FUNCTION:    GpeEventHandler
 *
 * PARAMETERS:
 *
 * RETURN:      INTERRUPT_HANDLED or INTERRUPT_NOT_HANDLED
 *
 * DESCRIPTION: Clears the status bit for the requested event
 *
 * The Gpe handler differs from the fixed events in that it clears the enable
 * bit rather than the status bit to clear the interrupt.  This allows
 * software outside of interrupt context to determine what caused the SCI and
 * dispatch the correct AML. 
 *
 ******************************************************************************/

static INT32
GpeEventHandler (UINT16 Index, UINT32 GpeBase, UINT16 GpeLength)
{
    UINT8               GpeStatus;
    UINT8               GpeEnable;
    UINT8               Bit;

    /* Read the entire status byte because we don't know which bit may be set */

    GpeStatus = OsdIn8 ((UINT16) (GpeBase + Index));

    if (!GpeStatus)
    {
    	return INTERRUPT_NOT_HANDLED;
    }
    
    /*  GPE status bit set  */
    /* Read the entire byte because we don't know which bit may be set */

    GpeEnable = OsdIn8 ((UINT16) (GpeBase + Index + GpeLength));

    /* verify the set status bit has a matching enable bit set */

    Bit = GpeEnable & GpeStatus;
    
    if (!Bit)
    {
    	return INTERRUPT_NOT_HANDLED;
    }
    
    /*  matching status and enable bit(s) set   */

    OsdOut8 ((UINT16) (GpeBase + GpeLength + Index), (UINT8) (GpeEnable & ~Bit));
#ifdef _DEBUG
    EventCount[GENERAL_EVENT]++;
#endif

    return INTERRUPT_HANDLED;
}   


/******************************************************************************
 *
 * FUNCTION:    SciHandler
 *
 * PARAMETERS:  none
 *
 * RETURN:      Status code indicates whether interrupt was handled.
 *
 * DESCRIPTION: Interrupt handler that will figure out what function or
 *              control method to call to deal with a SCI.  Installed
 *              using BU interrupt support.
 *
 ******************************************************************************/

UINT32 
SciHandler (void)
{
	/* CHANGE: if multiple SCI's happen concurrently and only one of them
		is handled, what should be returned?
	*/
	
    INT32 		InterruptHandled = INTERRUPT_NOT_HANDLED;
	UINT32      StatusRegister = 0;
    UINT32      EnableRegister = 0;
	UINT16 		Index;
	UINT16		GpeLength;
        
    DEBUG_PRINT (TRACE_INTERRUPTS, ("Entered SCI handler\n"));

	if (! READ_ACPI_REGISTER (SCI_EN))
    {
    	DEBUG_PRINT (TRACE_INTERRUPTS, ("Not an SCI\n"));
    	return INTERRUPT_NOT_HANDLED;
    }	
    
    /* Determine if the SCI was a fixed event ot a GPE. */
    DEBUG_PRINT (TRACE_INTERRUPTS, ("Got an SCI\n"));

    /* 
     * Read the fixed feature status and enable registers, as all the cases
     * depend on their values.  
     */

    StatusRegister = (UINT32) OsdIn16 ((UINT16) FACP->Pm1aEvtBlk);
    if (FACP->Pm1bEvtBlk)
    {
    	StatusRegister |= (UINT32) OsdIn16 ((UINT16) FACP->Pm1bEvtBlk);
    }
        
    EnableRegister = (UINT32)
    	OsdIn16 ((UINT16) (FACP->Pm1aEvtBlk + FACP->Pm1EvtLen / 2));
    
    if (FACP->Pm1bEvtBlk)
    {
        EnableRegister |= (UINT32)
        	OsdIn16 ((UINT16) (FACP->Pm1bEvtBlk + FACP->Pm1EvtLen / 2));
    }
        
    DEBUG_PRINT (TRACE_INTERRUPTS,
    	("Enable: %08x\tStatus: %08x\n", EnableRegister, StatusRegister));

	/* If the SCI was a fixed event, invoke the handler with the event type. */
    
    if ((EnableRegister & 1) && (StatusRegister & 1))
    {
        /* power management timer roll over */
        InterruptHandled = FixedEventHandler (PMTIMER_EVENT);
    }

    if ((EnableRegister & 32) && (StatusRegister & 32))
    {
        /* global event */
        InterruptHandled = FixedEventHandler (GLOBAL_EVENT);
    }

    if ((EnableRegister & 256) && (StatusRegister & 256))
    {
        /* power button event */
        InterruptHandled = FixedEventHandler (POWER_BUTTON_EVENT);
        // InterruptHandled = PwrbtnEventHandler ();
    }

    if ((EnableRegister & 512) && (StatusRegister & 512))
    {
        /* sleep button event */
        InterruptHandled = FixedEventHandler (SLEEP_BUTTON_EVENT);
        // InterruptHandled = SlpbtnEventHandler ();
    }
   
    /* Check for a general purpose event handler */
    
    /* CHANGE: This checks every single GPE every single time.... */
            
    GpeLength = FACP->Gpe0BlkLen / 2;

    for (Index = 0; Index < GpeLength && InterruptHandled == FALSE; Index++)
    {
    	InterruptHandled = GpeEventHandler (Index, FACP->Gpe0Blk, GpeLength);
    }

    /* 
     * GPE1 checking will not be done if InterruptHandled == TRUE or 
     * FACP->bGpe1BlkLen == 0 which is the case if GPE1 does not exist 
     */

    GpeLength = FACP->Gpe1BlkLen / 2;

    for (Index = 0; Index < GpeLength && InterruptHandled == FALSE; Index++)
    {
	    InterruptHandled = GpeEventHandler (Index, FACP->Gpe1Blk, GpeLength);
    }
    
    return INTERRUPT_HANDLED;
    // return InterruptHandled;
}

/* Change: is this needed? #pragma check_stack () */

/******************************************************************************
 *
 * FUNCTION:    InstallSciHandler
 *
 * PARAMETERS:  none
 *
 * RETURN:      Handle to BU ISR
 *
 * DESCRIPTION: Installs SCI handler.
 *
 ******************************************************************************/

UINT32 
InstallSciHandler (void)
{
	UINT32 Except = AE_OK;
	 
    FUNCTION_TRACE ("InstallSciHandler");
   
    if (!SciHandle)
    {
        Except = OsdInstallInterruptHandler (
                            (UINT32) FACP->SciInt,
                            SciHandler,
                            &SciHandle);
    }

    return Except;
}


/******************************************************************************
 *
 * FUNCTION:    UninstallSciHandler
 *
 * PARAMETERS:  none
 *
 * RETURN:      E_OK if handler uninstalled OK, E_ERROR if handler was not
 *              installed to begin with
 *
 * DESCRIPTION: Restores original status of all fixed event enable bits and
 *              removes SCI handler.
 *
 ******************************************************************************/

ACPI_STATUS
UninstallSciHandler (void)
{
    FUNCTION_TRACE ("UninstallSciHandler");
    
    if (SciHandle)
    {
#if 0
        /* Disable all events first ???  TBD:  Figure this out!! */

        if (OriginalFixedEnableBitStatus ^ 1 << EventIndex (TMR_FIXED_EVENT))
        {
            AcpiEventDisableEvent (TMR_FIXED_EVENT);
        }
            
        if (OriginalFixedEnableBitStatus ^ 1 << EventIndex (GBL_FIXED_EVENT))
        {
            AcpiEventDisableEvent (GBL_FIXED_EVENT);
        }
            
        if (OriginalFixedEnableBitStatus ^ 1 << EventIndex (PWR_BTN_FIXED_EVENT))
        {
            AcpiEventDisableEvent (PWR_BTN_FIXED_EVENT);
        }
            
        if (OriginalFixedEnableBitStatus ^ 1 << EventIndex (SLP_BTN_FIXED_EVENT))
        {
            AcpiEventDisableEvent (SLP_BTN_FIXED_EVENT);
        }
            
        if (OriginalFixedEnableBitStatus ^ 1 << EventIndex (RTC_FIXED_EVENT))
        {
            AcpiEventDisableEvent (RTC_FIXED_EVENT);
        }
        
        OriginalFixedEnableBitStatus = 0;
#endif      
            
        OsdRemoveInterruptHandler (SciHandle);
        SciHandle = 0;
    }

    return AE_OK;
}


/******************************************************************************
 *
 * FUNCTION:    SciCount
 *
 * PARAMETERS:  char * EventName        name (fully qualified name from namespace 
 *                                      or one of the fixed event names defined above)
 *                                      of the event to check if it's generated an SCI.
 *
 * RETURN:      Number of SCI's for requested event since last time iSciOccured()
 *              was called for this event.
 *
 * DESCRIPTION: Checks to see if SCI has been generated from requested source
 *              since the last time this function was called.
 *
 ******************************************************************************/

#ifdef _DEBUG

INT32 
SciCount (UINT32 Event)
{
      /* 
       * Elements correspond to counts for TMR, NOT_USED, GBL, 
       * PWR_BTN, SLP_BTN, RTC, and GENERAL respectively. 
       */
    FUNCTION_TRACE ("SciCount");
    
    if (Event >= NUM_EVENTS)
    {
    	return -1;	
    }
    
    return EventCount[Event];
}

#endif

/**************************************************************************
 *
 * FUNCTION:    AcpiEnable
 *
 * PARAMETERS:  Flags           flag bitmask (logical OR) to specify:
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
AcpiEnable ()
{
    FUNCTION_TRACE ("AcpiEnable");

    if (AcpiLibInitStatus == AE_NO_ACPI_TABLES)
    {
        /*	ACPI tables are not available	*/
        DEBUG_PRINT (ACPI_WARN, ("No ACPI tables present!\n"));
		return AE_NO_ACPI_TABLES;
    }

    /*  ACPI tables are available or not required   */

    if (LEGACY_MODE == AcpiModeCapabilities ())
    {   
    	/*  no ACPI mode support provided by BIOS   */
        /*  The only way to get through sign_on() without ACPI support is
         *  if we are running from an input file.
         */

		/* TBD:	verify input file specified	*/

        DEBUG_PRINT (ACPI_WARN, ("Only legacy mode supported!\n"));
		return AE_ERROR;
	}

    OriginalMode = AcpiModeStatus ();

    if (InstallSciHandler () != AE_OK)
    {   
    	/* Unable to install SCI handler	*/
        DEBUG_PRINT (ACPI_FATAL, ("Unable to install System Control Interrupt Handler"));
		return AE_ERROR;
	}

    /*  SCI Interrupt Handler installed properly    */

	if (ACPI_MODE != OriginalMode)
	{	
        /*	legacy mode	*/
				
        if (AE_OK != AcpiSetMode (ACPI_MODE))
		{	
			/*	Unable to transition to ACPI Mode	*/
			DEBUG_PRINT (ACPI_FATAL, ("Could not transition to ACPI mode.\n"));
			return AE_ERROR;	
		}
		else
    	{
			DEBUG_PRINT (ACPI_OK, ("Transition to ACPI mode successful\n"));
        }
    }

    return AE_OK;

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
    FUNCTION_TRACE ("AcpiDisable");

    /* Restore original mode   */

    if (AE_OK != AcpiSetMode (OriginalMode))
    {
        DEBUG_PRINT (ACPI_ERROR, ("Unable to transition to original mode"));
        return AE_ERROR;    
    }

    /* Unload the SCI interrupt handler  */

	UninstallSciHandler ();
    RestoreAcpiState ();
    AcpiLocalCleanup ();

    return AE_OK;
}
