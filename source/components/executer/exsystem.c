/*
  __________________________________________________________________________
 |
 |
 |           Copyright (C) Intel Corporation 1994-1998
 |
 | All rights reserved.  No part of this program or publication may be
 | reproduced, transmitted, transcribed, stored in a retrieval system, or
 | translated into any language or computer language, in any form or by any
 | means, electronic, mechanical, magnetic, optical, chemical, manual, or
 | otherwise, without the prior written permission of Intel Corporation.
 |__________________________________________________________________________
 |
 | FILENAME: amlopsys.c
 |__________________________________________________________________________
 |
 | $Revision: 1.7 $
 | $Date: 2005/06/29 17:56:38 $
 | $Log: exsystem.c,v $
 | Revision 1.7  2005/06/29 17:56:38  aystarik
 | New names for I/O and PCI OSD interfaces
 |
 | 
 | date	99.03.10.00.08.00;	author rmoore1;	state Exp;
 |
 * 
 * 7     3/09/99 4:08p Rmoore1
 * New names for I/O and PCI OSD interfaces
 * 
 * 6     2/19/99 4:33p Rmoore1
 * Changed to generic 64-bit friendly data types
 * 
 * 5     2/16/99 1:22p Rmoore1
 * Removed hungarian notation
 * 
 * 4     1/20/99 9:40a Rmoore1
 * Major cleanup
 * 
 * 3     1/13/99 10:50a Grsmith1
 * First BeOS compatible check-in.
 * 
 * 2     1/11/99 4:17p Grsmith1
 * Detabified.
 * 
 * 1     1/11/99 2:11p Rmoore1
 * AML Interpreter
// 
//    Rev 1.4   11 Sep 1998 18:03:18   phutchis
// Change inc_error() etc. to dKinc_error() etc. (error key logging).
// 
//    Rev 1.3   14 May 1998 16:49:38   phutchis
// Remove "return S_SUCCESS;" from VOID function ReleaseGlobalLock().
// 
//    Rev 1.2   30 Apr 1998 07:23:48   calingle
// Added two functions one to get ownership of the Global Lock and another to Release
// ownership of the Global Lock.
//
//    Rev 1.1   13 Mar 1998 07:39:04   calingle
// Added *ObjDesc to the DoNotifyOp function.
//
//    Rev 1.0   13 Mar 1998 07:23:42   calingle
// Initial revision.
 |__________________________________________________________________________

*/

#define __AMLOPSYS_C__

#include "acpitype.h"
#include "acpipriv.h"
#include "acpirio.h"
#include "aml.h"
#include "acpinmsp.h"
#include "amldsio.h"
#include "amlscan.h"
#include "amlexec.h"
#include "amlpriv.h"
#include "amlopsys.h"
#include "acpiosd.h"
#include "bu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

/* Global Variables */

ACPI_EXTERN FIRMWARE_ACPI_CONTROL_STRUCTURE * FACS;

extern char     *Why;


/******************************************************************************
 * 
 * FUNCTION:    ThreadId
 *
 * PARAMETERS:  VOID
 *
 * RETURN:      Current Thread ID (for this implementation a 1 is returned)
 *
 * DESCRIPTION: An invocation is identified by its Thread ID.  In a single
 *              threaded OS the Thread ID is undefined so a 1 will be
 *              returned.
 *
 ******************************************************************************/

UINT16 
ThreadId (VOID)
{
    return (1);
}



/******************************************************************************
 * 
 * FUNCTION:    DoNotifyOp 
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
DoNotifyOp (OBJECT_DESCRIPTOR *ValDesc, OBJECT_DESCRIPTOR *ObjDesc)
{

    fprintf_bu (LstFileHandle, LOGFILE,
                "NotifyOp: %s %s ", NsTypeNames[ObjDesc->ValType],
                NsFullyQualifiedName (ObjDesc->Device.Device));
    
    switch (ValDesc->Number.Number)
    {
        case 0:
            fprintf_bu (LstFileHandle, LOGFILE,
                            "Re-enumerate Devices ");
            break;

        case 1:
            fprintf_bu (LstFileHandle, LOGFILE, "Ejection Request ");
            break;

        case 2:
            fprintf_bu (LstFileHandle, LOGFILE, "Device Wake ");
            break;

        case 0x80:
            fprintf_bu (LstFileHandle, LOGFILE, "Status Change ");
            break;

        default:
            fprintf_bu (LstFileHandle, LOGFILE, "%lx ",
                    ValDesc->Number.Number);
            break;
    }

    fprintf_bu (LstFileHandle, LOGFILE, "[not implemented]");
    _Kinc_warning ("0000", PACRLF, __LINE__, __FILE__,
                        LstFileHandle, LOGFILE);

    return S_SUCCESS;
}


/******************************************************************************
 * 
 * FUNCTION:    DoSuspend
 *
 * PARAMETERS:  UINT32 HowLong - The amount of time to suspend
 *
 * RETURN:      VOID
 *
 * DESCRIPTION: Suspend processing for specified amount of time.  This
 *              function should be suspending the current thread but is using
 *              busy wait instead since this implementation is single threaded
 *
 ******************************************************************************/

VOID
DoSuspend (UINT32 HowLong)
{
    OsdSleep ((UINT16) (HowLong / (UINT32) 1000), (UINT16) (HowLong % (UINT32) 1000));
}


/******************************************************************************
 * 
 * FUNCTION:    AcquireOpRqst
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
AcquireOpRqst (OBJECT_DESCRIPTOR *TimeDesc, OBJECT_DESCRIPTOR *ObjDesc)
{
    UINT16      CurrentId;
    INT32       RetVal = S_SUCCESS;


    if (ObjDesc->Mutex.LockCount == 0)
    {
        ObjDesc->Mutex.ThreadId = ThreadId ();
    }
    
    else if (ObjDesc->Mutex.ThreadId != (CurrentId = ThreadId ()))
    {
        sprintf (WhyBuf, "Thread %02Xh attemted to Aquire a resource owned "
                "by thread %02Xh", CurrentId, ObjDesc->Mutex.ThreadId);
        Why = WhyBuf;
        RetVal = S_ERROR;
    }

    if (S_SUCCESS == RetVal)
    {
        ObjDesc->Mutex.LockCount++;
    }

    return (RetVal);
}


/******************************************************************************
 * 
 * FUNCTION:    ReleaseOpRqst
 *
 * PARAMETERS:  OBJECT_DESCRIPTOR *ObjDesc  - The object descriptor for this op
 *
 * RETURN:      S_SUCCESS/S_ERROR
 *
 * DESCRIPTION: Provides an access point to perform synchronization operations
 *              within the AML.  Current implementation is for single thread
 *              OS only.  This operation is a request to release a previously
 *              acquired Mutex.  If the Mutex variable is set then it will be
 *              decremented.  Otherwise S_ERROR will be returned with Why
 *              set to explain.
 *
 ******************************************************************************/

INT32
ReleaseOpRqst (OBJECT_DESCRIPTOR *ObjDesc)
{
    UINT16      CurrentId;
    INT32       RetVal = S_SUCCESS;


    if (ObjDesc->Mutex.LockCount == 0)
    {
        Why = "Attempting to Release a Mutex that is not locked";
        RetVal == S_ERROR;
    }
    
    else if (ObjDesc->Mutex.ThreadId != (CurrentId = ThreadId ()))
    {
        sprintf (WhyBuf, "Thread %02Xh attemted to Release a Mutex owned "
                    "by thread %02Xh", CurrentId, ObjDesc->Mutex.ThreadId);
        Why = WhyBuf;
        RetVal = S_ERROR;
    }
    
    if (S_SUCCESS == RetVal)
    {
        ObjDesc->Mutex.LockCount--;
    }

    return (RetVal);
}


/******************************************************************************
 * 
 * FUNCTION:    SignalOpRqst
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
SignalOpRqst (OBJECT_DESCRIPTOR *ObjDesc)
{

    ObjDesc->Event.SignalCount++;
    return (S_SUCCESS);
}


/******************************************************************************
 * 
 * FUNCTION:    WaitOpRqst
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
WaitOpRqst (OBJECT_DESCRIPTOR *TimeDesc, OBJECT_DESCRIPTOR *ObjDesc)
{
    INT32       RetVal = S_SUCCESS;


    if (0 == ObjDesc->Event.SignalCount)
    {
        /* Error for single threaded OS */
        
        Why = "Waiting for a signal that has not occured.  In a single threaded"
                "\nOperating System the signal would never be received.";
        RetVal = S_ERROR;
    }
    
    else
    {
        ObjDesc->Event.SignalCount--;
    }

    return (RetVal);
}


/******************************************************************************
 * 
 * FUNCTION:    ResetOpRqst
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
ResetOpRqst (OBJECT_DESCRIPTOR *ObjDesc)
{
    INT32       RetVal = S_SUCCESS;


    ObjDesc->Event.SignalCount = 0;

    return (RetVal);
}


/***************************************************************************
 * 
 * FUNCTION:    GetGlobalLock
 *
 * RETURN:      S_SUCCESS/S_ERROR
 *
 * DESCRIPTION: attemts to gain ownership of the Global Lock.  Since this
 *              is a single threaded implementation if the Global Lock
 *              ownership is not successful then the test will fail.
 *
 **************************************************************************/

INT32
GetGlobalLock(VOID)
{
    UINT32          GlobalLockReg = FACS->GlobalLock;
    INT32           RetVal;


    if (GlobalLockReg & GL_OWNED)
    {
        Why = "The Global Lock is owned by another process\n"\
                "This is a single threaded implementation. There is no way some\n"\
                "other process can own the Global Lock!";
        RetVal = S_ERROR;
    }
    
    else
    {
        /* Its not owned so take ownership and return S_SUCCESS */
        
        FACS->GlobalLock |= GL_OWNED;
        RetVal = S_SUCCESS;
    }
    
    return (RetVal);
}


/***************************************************************************
 * 
 * FUNCTION:    ReleaseGlobalLock
 *
 * DESCRIPTION: Releases the ownership of the Global Lock.
 *
 **************************************************************************/

VOID
ReleaseGlobalLock (VOID)
{
    
    FACS->GlobalLock &= 0xFFFFFFFF ^ GL_OWNED;
}
