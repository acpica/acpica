
/******************************************************************************
 * 
 * Module Name: iesystem - Interface to OS services
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


#define __IESYSTEM_C__

#include <acpi.h>
#include <interpreter.h>
#include <namespace.h>


#define _THIS_MODULE        "iesystem.c"
#define _COMPONENT          INTERPRETER


static ST_KEY_DESC_TABLE KDT[] = {
    {"0000", 'W', "NOT IMPLEMENTED", "NOT IMPLEMENTED"},
    {NULL, 'I', NULL, NULL}
};


/******************************************************************************
 * 
 * FUNCTION:    OsThreadId
 *
 * PARAMETERS:  void
 *
 * RETURN:      Current Thread ID (for this implementation a 1 is returned)
 *
 * DESCRIPTION: An invocation is identified by its Thread ID.  In a single
 *              threaded OS the Thread ID is undefined so a 1 will be
 *              returned.
 *
 ******************************************************************************/

UINT16 
OsThreadId (void)
{
    return (1);
}



/******************************************************************************
 * 
 * FUNCTION:    OsDoNotifyOp 
 *
 * PARAMETERS:  OBJECT_DESCRIPTOR *ValDesc -    The value of the opcode to be
 *                                          executed.
 *
 * RETURN:      S_SUCCESS or S_ERROR (S_SUCCESS for now only)
 *
 * DESCRIPTION: prints a message that these operations are not implemented
 *
 ******************************************************************************/

INT32
OsDoNotifyOp (OBJECT_DESCRIPTOR *ValDesc, OBJECT_DESCRIPTOR *ObjDesc)
{

    if (ValDesc)
    {
        if (ObjDesc)
        {
            DEBUG_PRINT (ACPI_INFO, 
                        ("NotifyOp: %s\n", NsTypeNames[ObjDesc->ValType]));
            NsDumpPathname (ObjDesc->Device.Device, "NotifyOp: ", ACPI_INFO, _COMPONENT);
        }
    
        switch (ValDesc->Number.Number)
        {
        case 0:
            DEBUG_PRINT (ACPI_INFO, ("Re-enumerate Devices \n"));
            break;

        case 1:
            DEBUG_PRINT (ACPI_INFO, ("Ejection Request \n"));
            break;

        case 2:
            DEBUG_PRINT (ACPI_INFO, ("Device Wake \n"));
            break;

        case 0x80:
            DEBUG_PRINT (ACPI_INFO, ("Status Change \n"));
            break;

        default:
            DEBUG_PRINT (ACPI_INFO, ("%lx \n",
                    ValDesc->Number.Number));
            break;
        }

        REPORT_WARNING (&KDT[0]);
    }
    
    return S_SUCCESS;
}


/******************************************************************************
 * 
 * FUNCTION:    OsDoSuspend
 *
 * PARAMETERS:  UINT32 HowLong - The amount of time to suspend
 *
 * RETURN:      void
 *
 * DESCRIPTION: Suspend processing for specified amount of time.  This
 *              function should be suspending the current thread but is using
 *              busy wait instead since this implementation is single threaded
 *
 ******************************************************************************/

void
OsDoSuspend (UINT32 HowLong)
{
    OsdSleep ((UINT16) (HowLong / (UINT32) 1000), (UINT16) (HowLong % (UINT32) 1000));
}


/******************************************************************************
 * 
 * FUNCTION:    OsAcquireOpRqst
 *
 * PARAMETERS:  OBJECT_DESCRIPTOR *TimeDesc  - The 'time to delay' object descriptor
 *              OBJECT_DESCRIPTOR *ObjDesc   - The object descriptor for this op
 *
 * RETURN:      S_SUCCESS/S_ERROR
 *
 * DESCRIPTION: Provides an access point to perform synchronization operations
 *              within the AML.  Current implementation is for single thread
 *              OS only.  This function will cause a lock to be generated
 *              for the Mutex pointed to by ObjDesc.
 *              Timeout is being ignored for now since this is single threaded.
 *
 ******************************************************************************/

INT32
OsAcquireOpRqst (OBJECT_DESCRIPTOR *TimeDesc, OBJECT_DESCRIPTOR *ObjDesc)
{
    UINT16      CurrentId;
    INT32       Excep = S_SUCCESS;


    if (ObjDesc)
    {
        if (ObjDesc->Mutex.LockCount == 0)
        {
            ObjDesc->Mutex.ThreadId = OsThreadId ();
        }
    
        else if (ObjDesc->Mutex.ThreadId != (CurrentId = OsThreadId ()))
        {
            DEBUG_PRINT (ACPI_ERROR, ("Thread %02Xh attemted to Aquire a resource owned "
                    "by thread %02Xh\n", CurrentId, ObjDesc->Mutex.ThreadId));
            Excep = S_ERROR;
        }

        if (S_SUCCESS == Excep)
        {
            ObjDesc->Mutex.LockCount++;
        }
    }

    return (Excep);
}


/******************************************************************************
 * 
 * FUNCTION:    OsReleaseOpRqst
 *
 * PARAMETERS:  OBJECT_DESCRIPTOR *ObjDesc  - The object descriptor for this op
 *
 * RETURN:      S_SUCCESS/S_ERROR
 *
 * DESCRIPTION: Provides an access point to perform synchronization operations
 *              within the AML.  Current implementation is for single thread
 *              OS only.  This operation is a request to release a previously
 *              acquired Mutex.  If the Mutex variable is set then it will be
 *              decremented.  Otherwise S_ERROR will be returned.
 *
 ******************************************************************************/

INT32
OsReleaseOpRqst (OBJECT_DESCRIPTOR *ObjDesc)
{
    UINT16      CurrentId;
    INT32       Excep = S_SUCCESS;


    if (ObjDesc)
    {
        if (ObjDesc->Mutex.LockCount == 0)
        {
            DEBUG_PRINT (ACPI_ERROR, ("Attempting to Release a Mutex that is not locked\n"));
            Excep == S_ERROR;
        }
    
        else if (ObjDesc->Mutex.ThreadId != (CurrentId = OsThreadId ()))
        {
            DEBUG_PRINT (ACPI_ERROR, ("Thread %02Xh attemted to Release a Mutex owned "
                        "by thread %02Xh\n", CurrentId, ObjDesc->Mutex.ThreadId));
            Excep = S_ERROR;
        }
    
        if (S_SUCCESS == Excep)
        {
            ObjDesc->Mutex.LockCount--;
        }
    }

    return (Excep);
}


/******************************************************************************
 * 
 * FUNCTION:    OsSignalOpRqst
 *
 * PARAMETERS:  OBJECT_DESCRIPTOR *ObjDesc  - The object descriptor for this op
 *
 * RETURN:      S_SUCCESS
 *
 * DESCRIPTION: Provides an access point to perform synchronization operations
 *              within the AML.  Current implementation is for single thread
 *              OS only.  This will signal when an event has been posted.
 *              if this occures prior to a wait then the wait will succeed.
 *              if a wait occures without a signal then the wait will fail
 *              because the signal will never occur.
 *
 ******************************************************************************/

INT32
OsSignalOpRqst (OBJECT_DESCRIPTOR *ObjDesc)
{

    if (ObjDesc)
    {
        ObjDesc->Event.SignalCount++;
    }

    return (S_SUCCESS);
}


/******************************************************************************
 * 
 * FUNCTION:    OsWaitOpRqst
 *
 * PARAMETERS:  OBJECT_DESCRIPTOR *TimeDesc - The 'time to delay' object descriptor
 *              OBJECT_DESCRIPTOR *ObjDesc   - The object descriptor for this op
 *
 * RETURN:      S_SUCCESS/S_ERROR
 *
 * DESCRIPTION: Provides an access point to perform synchronization operations
 *              within the AML.  Current implementation is for single thread
 *              OS only.  This operation is a request to wait for an event.
 *              In a single thread OS,  if the signal for this event has
 *              already occured then dec the signal count and return success.
 *              If the signal has not already occured then it never will
 *              because the wait would have to give the processor over to a
 *              new process and that can't happen in a single threaded OS.
 *              Timeout is being ignored for the current implementation.
 *
 ******************************************************************************/

INT32
OsWaitOpRqst (OBJECT_DESCRIPTOR *TimeDesc, OBJECT_DESCRIPTOR *ObjDesc)
{
    INT32       Excep = S_SUCCESS;


    if (ObjDesc)
    {
        if (0 == ObjDesc->Event.SignalCount)
        {
            /* Error for single threaded OS */
        
            DEBUG_PRINT (ACPI_ERROR, ("Waiting for a signal that has not occured.  In a single threaded"
                    "\nOperating System the signal would never be received.\n"));
            Excep = S_ERROR;
        }
    
        else
        {
            ObjDesc->Event.SignalCount--;
        }
    }
  
    return (Excep);
}


/******************************************************************************
 * 
 * FUNCTION:    OsResetOpRqst
 *
 * PARAMETERS:  OBJECT_DESCRIPTOR *ObjDesc  - The object descriptor for this op
 *
 * RETURN:      S_SUCCESS/S_ERROR
 *
 * DESCRIPTION: Provides an access point to perform synchronization operations
 *              within the AML.  Current implementation is for single thread
 *              OS only.  This will reset the total signal count for this
 *              event to 0.
 *
 ******************************************************************************/

INT32
OsResetOpRqst (OBJECT_DESCRIPTOR *ObjDesc)
{
    INT32       Excep = S_SUCCESS;


    if (ObjDesc)
    {
        ObjDesc->Event.SignalCount = 0;
    }

    return (Excep);
}


/***************************************************************************
 * 
 * FUNCTION:    OsGetGlobalLock
 *
 * RETURN:      S_SUCCESS/S_ERROR
 *
 * DESCRIPTION: attemts to gain ownership of the Global Lock.  Since this
 *              is a single threaded implementation if the Global Lock
 *              ownership is not successful then the test will fail.
 *
 **************************************************************************/

INT32
OsGetGlobalLock(void)
{
    UINT32          GlobalLockReg;
    INT32           Excep = S_ERROR;


    if (FACS)
    {
        /* Only if the FACS is valid */

        GlobalLockReg = FACS->GlobalLock;

        if (GlobalLockReg & GL_OWNED)
        {
            DEBUG_PRINT (ACPI_ERROR, ("The Global Lock is owned by another process\n"\
                    "This is a single threaded implementation. There is no way some\n"\
                    "other process can own the Global Lock!\n"));
            Excep = S_ERROR;
        }
    
        else
        {
            /* Its not owned so take ownership and return S_SUCCESS */
        
            FACS->GlobalLock |= GL_OWNED;
            Excep = S_SUCCESS;
        }
    }

    return (Excep);
}


/***************************************************************************
 * 
 * FUNCTION:    OsReleaseGlobalLock
 *
 * DESCRIPTION: Releases the ownership of the Global Lock.
 *
 **************************************************************************/

void
OsReleaseGlobalLock (void)
{
    
    if (FACS)
    {
        FACS->GlobalLock &= 0xFFFFFFFF ^ GL_OWNED;
    }
}
