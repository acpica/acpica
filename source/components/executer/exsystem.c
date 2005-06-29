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
 | $Revision: 1.3 $
 | $Date: 2005/06/29 17:56:34 $
 | $Log: exsystem.c,v $
 | Revision 1.3  2005/06/29 17:56:34  aystarik
 | First BeOS compatible check-in.
 |
 | 
 | date	99.01.13.18.50.00;	author grsmith1;	state Exp;
 |
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
// Remove "return S_SUCCESS;" from void function vReleaseGlobalLock().
// 
//    Rev 1.2   30 Apr 1998 07:23:48   calingle
// Added two functions one to get ownership of the Global Lock and another to Release
// ownership of the Global Lock.
//
//    Rev 1.1   13 Mar 1998 07:39:04   calingle
// Added *obj to the iDoNotifyOp function.
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
#include <bu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

/* Global Variables */
ACPI_EXTERN FIRMWARE_ACPI_CONTROL_STRUCTURE * pFACS;
extern char * pcWhy;


/******************************************************************************
 * FUNCTION:        WORD wThreadId(void)
 *
 * PARAMETERS:      void
 *
 * RETURN:          Current Thread ID (for this implementation a 1 is returned)
 *
 * DESCRIPTION: An invocation is identified by its Thread ID.  In a single
 *                      threaded OS the Thread ID is undefined so a 1 will be
 *                      returned.
 *
 ******************************************************************************/
WORD wThreadId(void)
{
    return (1);
}



/******************************************************************************
 * FUNCTION:    int iDoNotifyOp (OBJECT_DESCRIPTOR *val)
 *
 * PARAMETERS:      OBJECT_DESCRIPTOR *val - The value of the opcode to be
 *                                                          executed.
 *
 * RETURN:          S_SUCCESS or S_ERROR (S_SUCCESS for now only)
 *
 * DESCRIPTION: prints a message that these operations are not implemented
 *
 ******************************************************************************/
int
iDoNotifyOp (OBJECT_DESCRIPTOR *val, OBJECT_DESCRIPTOR *obj)
{
    fprintf_bu(iLstFileHandle, LOGFILE,
            "\nNotifyOp: %s %s ", apcNsTypeNames[obj->bValTyp],
            pcNsFullyQualifiedName(obj->sDevice.nDevice));
    switch(val->sNumber.dNumber)
    {
        case 0:
            fprintf_bu(iLstFileHandle, LOGFILE,
                            "Re-enumerate Devices ");
            break;

        case 1:
            fprintf_bu(iLstFileHandle, LOGFILE, "Ejection Request ");
            break;

        case 2:
            fprintf_bu(iLstFileHandle, LOGFILE, "Device Wake ");
            break;

        case 0x80:
            fprintf_bu(iLstFileHandle, LOGFILE, "Status Change ");
            break;

        default:
            fprintf_bu(iLstFileHandle, LOGFILE, "%lx ",
                    val->sNumber.dNumber);
            break;
    }
    fprintf_bu(iLstFileHandle, LOGFILE, "[not implemented]");
    _dKinc_warning("0000", PACRLF, __LINE__, __FILE__,
                        iLstFileHandle, LOGFILE);

    return S_SUCCESS;
}


/******************************************************************************
 * FUNCTION:        vDoSuspend (DWORD dTime)
 *
 * PARAMETERS:      DWORD dTime - The amount of time to suspend
 *
 * RETURN:          void
 *
 * DESCRIPTION: Suspend processing for specified amount of time.  This
 *                      function should be suspending the current thread but is using
 *                      busy wait instead since this implementation is single threaded
 *
 ******************************************************************************/
void
vDoSuspend(DWORD dTime)
{
    bsleep((WORD)(dTime / (DWORD)1000), (WORD)(dTime % (DWORD)1000));
}

/******************************************************************************
 * FUNCTION:        iAcquireOpRqst(OBJECT_DESCRIPTOR *sTime,OBJECT_DESCRIPTOR *sOb)
 *
 * PARAMETERS:      OBJECT_DESCRIPTOR *sTime- The 'time to delay' object descriptor
 *                      OBJECT_DESCRIPTOR *sOb  - The object descriptor for this op
 *
 * RETURN:          S_SUCCESS/S_ERROR
 *
 * DESCRIPTION: Provides an access point to perform synchronization operations
 *                      within the AML.  Current implementation is for single thread
 *                      OS only.  This function will cause a lock to be generated
 *                      for the Mutex pointed to by sOb.
 *                      Timeout is being ignored for now since this is single threaded.
 *
 ******************************************************************************/
int
iAcquireOpRqst(OBJECT_DESCRIPTOR *sTime, OBJECT_DESCRIPTOR *sOb)
{
    WORD wCurrentId;
    int iRetVal = S_SUCCESS;

    if (sOb->sMutex.wLockCount == 0)
    {
        sOb->sMutex.wThreadId = wThreadId();
    }
    else if (sOb->sMutex.wThreadId != (wCurrentId = wThreadId()))
    {
        sprintf(acWhyBuf, "Thread %02Xh attemted to Aquire a resource owned "
            "by thread %02Xh", wCurrentId, sOb->sMutex.wThreadId);
        pcWhy = acWhyBuf;
        iRetVal = S_ERROR;
    }
    if (S_SUCCESS == iRetVal)
        sOb->sMutex.wLockCount++;
    return (iRetVal);
}

/******************************************************************************
 * FUNCTION:        iReleaseOpRqst(OBJECT_DESCRIPTOR *sOb)
 *
 * PARAMETERS:      OBJECT_DESCRIPTOR *sOb  - The object descriptor for this op
 *
 * RETURN:          S_SUCCESS/S_ERROR
 *
 * DESCRIPTION: Provides an access point to perform synchronization operations
 *                      within the AML.  Current implementation is for single thread
 *                      OS only.  This operation is a request to release a previously
 *                      acquired Mutex.  If the Mutex variable is set then it will be
 *                      decremented.  Otherwise S_ERROR will be returned with pcWhy
 *                      set to explain.
 *
 ******************************************************************************/
int
iReleaseOpRqst(OBJECT_DESCRIPTOR *sOb)
{
    WORD wCurrentId;
    int iRetVal = S_SUCCESS;

    if (sOb->sMutex.wLockCount == 0)
    {
        pcWhy = "Attempting to Release a Mutex that is not locked";
        iRetVal == S_ERROR;
    }
    else if (sOb->sMutex.wThreadId != (wCurrentId = wThreadId()))
    {
        sprintf(acWhyBuf, "Thread %02Xh attemted to Release a Mutex owned "
            "by thread %02Xh", wCurrentId, sOb->sMutex.wThreadId);
        pcWhy = acWhyBuf;
        iRetVal = S_ERROR;
    }
    if (S_SUCCESS == iRetVal)
        sOb->sMutex.wLockCount--;
    return (iRetVal);
}

/******************************************************************************
 * FUNCTION:        iSignalOpRqst(OBJECT_DESCRIPTOR *sOb)
 *
 * PARAMETERS:      OBJECT_DESCRIPTOR *sOb  - The object descriptor for this op
 *
 * RETURN:          S_SUCCESS
 *
 * DESCRIPTION: Provides an access point to perform synchronization operations
 *                      within the AML.  Current implementation is for single thread
 *                      OS only.  This will signal when an event has been posted.
 *                      if this occures prior to a wait then the wait will succeed.
 *                      if a wait occures without a signal then the wait will fail
 *                      because the signal will never occur.
 *
 ******************************************************************************/
int
iSignalOpRqst(OBJECT_DESCRIPTOR *sOb)
{
    sOb->sEvent.wSignalCount++;
    return (S_SUCCESS);
}

/******************************************************************************
 * FUNCTION:        iWaitOpRqst(OBJECT_DESCRIPTOR *sTime, OBJECT_DESCRIPTOR *sOb)
 *
 * PARAMETERS:      OBJECT_DESCRIPTOR *sTime- The 'time to delay' object descriptor
 *                      OBJECT_DESCRIPTOR *sOb  - The object descriptor for this op
 *
 * RETURN:          S_SUCCESS/S_ERROR
 *
 * DESCRIPTION: Provides an access point to perform synchronization operations
 *                      within the AML.  Current implementation is for single thread
 *                      OS only.  This operation is a request to wait for an event.
 *                      In a single thread OS,  if the signal for this event has
 *                      already occured then dec the signal count and return success.
 *                     If the signal has not already occured then it never will
 *                      because the wait would have to give the processor over to a
 *                      new process and that can't happen in a single threaded OS.
 *                      Timeout is being ignored for the current implementation.
 *
 ******************************************************************************/
int
iWaitOpRqst(OBJECT_DESCRIPTOR *sTime, OBJECT_DESCRIPTOR *sOb)
{
    int iRetVal = S_SUCCESS;

    if (0 == sOb->sEvent.wSignalCount)
    {/* Error for single threaded OS */
        pcWhy = "Waiting for a signal that has not occured.  In a single threaded"
            "\nOperating System the signal would never be received.";
        iRetVal = S_ERROR;
    }
    else
        sOb->sEvent.wSignalCount--;

    return (iRetVal);
}

/******************************************************************************
 * FUNCTION:        iResetOpRqst(OBJECT_DESCRIPTOR *sOb)
 *
 * PARAMETERS:      OBJECT_DESCRIPTOR *sOb  - The object descriptor for this op
 *
 * RETURN:          S_SUCCESS/S_ERROR
 *
 * DESCRIPTION: Provides an access point to perform synchronization operations
 *                      within the AML.  Current implementation is for single thread
 *                      OS only.  This will reset the total signal count for this
 *                      event to 0.
 *
 ******************************************************************************/
int
iResetOpRqst(OBJECT_DESCRIPTOR *sOb)
{
    int iRetVal = S_SUCCESS;

        sOb->sEvent.wSignalCount = 0;

    return (iRetVal);
}

/***************************************************************************
 * FUNCTION:        int iGetGlobalLock(void)
 *
 * RETURN:          S_SUCCESS/S_ERROR
 *
 * DESCRIPTION: attemts to gain ownership of the Global Lock.  Since this
 *                      is a single threaded implementation if the Global Lock
 *                      ownership is not successful then the test will fail.
 *
 **************************************************************************/
int
iGetGlobalLock(void)
{
    DWORD   dGlobalLockReg = pFACS->dGlobalLock;
    int iRetVal;

    if (dGlobalLockReg & GL_OWNED)
    {
        pcWhy = "The Global Lock is owned by another process\n"\
            "This is a single threaded implementation. There is no way some\n"\
            "other process can own the Global Lock!";
        iRetVal = S_ERROR;
    }
    else
    {
        /* Its not owned so take ownership and return S_SUCCESS */
        pFACS->dGlobalLock |= GL_OWNED;
        iRetVal = S_SUCCESS;
    }
    return (iRetVal);
}

/***************************************************************************
 * FUNCTION:        void vReleaseGlobalLock(void)
 *
 * DESCRIPTION: Releases the ownership of the Global Lock.
 *
 **************************************************************************/
void
vReleaseGlobalLock(void)
{
    pFACS->dGlobalLock &= 0xFFFFFFFF ^ GL_OWNED;
}
