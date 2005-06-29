/******************************************************************************
 *
 * Module Name: oswinxf - Windows application interface
 *              $Revision: 1.6 $
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
 * 2.1. This is your license from Intel Corp. under its intellectual property
 * rights.  You may have additional license terms from the party that provided
 * you this software, covering your right to use that party's intellectual
 * property rights.
 *
 * 2.2. Intel grants, free of charge, to any person ("Licensee") obtaining a
 * copy of the source code appearing in this file ("Covered Code") an
 * irrevocable, perpetual, worldwide license under Intel's copyrights in the
 * base code distributed originally by Intel ("Original Intel Code") to copy,
 * make derivatives, distribute, use and display any portion of the Covered
 * Code in any form, with the right to sublicense such rights; and
 *
 * 2.3. Intel grants Licensee a non-exclusive and non-transferable patent
 * license (with the right to sublicense), under only those claims of Intel
 * patents that are infringed by the Original Intel Code, to make, use, sell,
 * offer to sell, and import the Covered Code and derivative works thereof
 * solely to the minimum extent necessary to exercise the above copyright
 * license, and in no event shall the patent license extend to any additions
 * to or modifications of the Original Intel Code.  No other license or right
 * is granted directly or by implication, estoppel or otherwise;
 *
 * The above copyright and patent license is granted only if the following
 * conditions are met:
 *
 * 3. Conditions
 *
 * 3.1. Redistribution of Source with Rights to Further Distribute Source.
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification with rights to further distribute source must include
 * the above Copyright Notice, the above License, this list of Conditions,
 * and the following Disclaimer and Export Compliance provision.  In addition,
 * Licensee must cause all Covered Code to which Licensee contributes to
 * contain a file documenting the changes Licensee made to create that Covered
 * Code and the date of any change.  Licensee must include in that file the
 * documentation of any changes made by any predecessor Licensee.  Licensee
 * must include a prominent statement that the modification is derived,
 * directly or indirectly, from Original Intel Code.
 *
 * 3.2. Redistribution of Source with no Rights to Further Distribute Source.
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification without rights to further distribute source must
 * include the following Disclaimer and Export Compliance provision in the
 * documentation and/or other materials provided with distribution.  In
 * addition, Licensee may not authorize further sublicense of source of any
 * portion of the Covered Code, and must include terms to the effect that the
 * license from Licensee to its licensee is limited to the intellectual
 * property embodied in the software Licensee provides to its licensee, and
 * not to intellectual property embodied in modifications its licensee may
 * make.
 *
 * 3.3. Redistribution of Executable. Redistribution in executable form of any
 * substantial portion of the Covered Code or modification must reproduce the
 * above Copyright Notice, and the following Disclaimer and Export Compliance
 * provision in the documentation and/or other materials provided with the
 * distribution.
 *
 * 3.4. Intel retains all right, title, and interest in and to the Original
 * Intel Code.
 *
 * 3.5. Neither the name Intel nor any other trademark owned or controlled by
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
 * event Licensee exports any such software from the United States or
 * re-exports any such software from a foreign destination, Licensee shall
 * ensure that the distribution and export/re-export of the software is in
 * compliance with all laws, regulations, orders, or other restrictions of the
 * U.S. Export Administration Regulations. Licensee agrees that neither it nor
 * any of its subsidiaries will export/re-export any technical data, process,
 * software, or service, directly or indirectly, to any country for which the
 * United States government or any agency thereof requires an export license,
 * other governmental approval, or letter of assurance, without first obtaining
 * such license, approval or letter.
 *
 *****************************************************************************/


/*
 * These interfaces are required in order to link to the ACPI subsystem
 * parser.  They are called during the execution of the parser, and all
 * map directly to Clibrary calls.
 */


#pragma warning(disable:4115)   /* warning C4115: named type definition in parentheses (caused by rpcasync.h> */

#include <windows.h>
#include <winbase.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <process.h>
#include <time.h>

#undef LOWORD
#undef HIWORD
#undef LOBYTE
#undef HIBYTE


#include "acpi.h"           /* TBD: this should be acpixf.h */
#include "acdebug.h"

#define _COMPONENT          ACPI_OS_SERVICES
        MODULE_NAME         ("oswinxf")


UINT32                      NextSemaphoreHandle = 0;
#define NUM_SEMAPHORES      128

typedef struct semaphore_entry
{
    UINT16                  MaxUnits;
    UINT16                  CurrentUnits;
    void                    *OsHandle;
} SEMAPHORE_ENTRY;


SEMAPHORE_ENTRY             SemaphoreTable[NUM_SEMAPHORES];



extern FILE                 *DebugFile;



/******************************************************************************
 *
 * FUNCTION:    AcpiOsInitialize, AcpiOsTerminate
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Init and terminate.  Nothing to do.
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsInitialize (void)
{
    UINT32                  i;



    for (i = 0; i < NUM_SEMAPHORES; i++)
    {
        SemaphoreTable[i].OsHandle = NULL;
    }

    return AE_OK;
}


ACPI_STATUS
AcpiOsTerminate (void)
{
    return AE_OK;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsGetTimer
 *
 * PARAMETERS:  None
 *
 * RETURN:      Current time in milliseconds
 *
 * DESCRIPTION: Get the current system time (in milliseconds).
 *
 *****************************************************************************/

UINT32
AcpiOsGetTimer (void)
{
    SYSTEMTIME              SysTime;


    GetSystemTime (&SysTime);

    return ((SysTime.wMinute * 60000) +
        (SysTime.wSecond * 1000) +
        SysTime.wMilliseconds);

}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsReadable
 *
 * PARAMETERS:  Pointer             - Area to be verified
 *              Length              - Size of area
 *
 * RETURN:      TRUE if readable for entire length
 *
 * DESCRIPTION: Verify that a pointer is valid for reading
 *
 *****************************************************************************/

BOOLEAN
AcpiOsReadable (
    void                    *Pointer,
    UINT32                  Length)
{

    return ((BOOLEAN) !IsBadReadPtr (Pointer, Length));
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsWritable
 *
 * PARAMETERS:  Pointer             - Area to be verified
 *              Length              - Size of area
 *
 * RETURN:      TRUE if writable for entire length
 *
 * DESCRIPTION: Verify that a pointer is valid for writing
 *
 *****************************************************************************/

BOOLEAN
AcpiOsWritable (
    void                    *Pointer,
    UINT32                  Length)
{

    return ((BOOLEAN) !IsBadWritePtr (Pointer, Length));
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsPrintf
 *
 * PARAMETERS:  fmt, ...            Standard printf format
 *
 * RETURN:      Actual bytes written
 *
 * DESCRIPTION: Formatted output
 *
 *****************************************************************************/

INT32
AcpiOsPrintf (
    const char              *Fmt,
    ...)
{
    INT32                   Count;
    va_list                 Args;


    va_start (Args, Fmt);

    Count = AcpiOsVprintf (Fmt, Args);

    va_end (Args);
    return Count;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsVprintf
 *
 * PARAMETERS:  fmt                 Standard printf format
 *              args                Argument list
 *
 * RETURN:      Actual bytes written
 *
 * DESCRIPTION: Formatted output with argument list pointer
 *
 *****************************************************************************/

INT32
AcpiOsVprintf (
    const char              *Fmt,
    va_list                 Args)
{
    INT32                   Count = 0;
    UINT8                   Flags;


    Flags = AcpiGbl_DbOutputFlags;
    if (Flags & DB_REDIRECTABLE_OUTPUT)
    {
        /* Output is directable to either a file (if open) or the console */

        if (DebugFile)
        {
            /* Output file is open, send the output there */

            Count = vfprintf (DebugFile, Fmt, Args);
        }
        else
        {
            /* No redirection, send output to console (once only!) */

            Flags |= DB_CONSOLE_OUTPUT;
        }
    }

    if (Flags & DB_CONSOLE_OUTPUT)
    {
        Count = vprintf (Fmt, Args);
    }

    return Count;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsGetLine
 *
 * PARAMETERS:  fmt                 Standard printf format
 *              args                Argument list
 *
 * RETURN:      Actual bytes read
 *
 * DESCRIPTION: Formatted input with argument list pointer
 *
 *****************************************************************************/

UINT32
AcpiOsGetLine (
    char                    *Buffer)
{
    UINT8                   Temp;
    UINT32                  i;


    for (i = 0; ; i++)
    {
        scanf ("%1c", &Temp);
        if (!Temp || Temp == '\n')
        {
            break;
        }

        Buffer [i] = Temp;
    }

    /* Null terminate the buffer */

    Buffer [i] = 0;

    /* Return the number of bytes in the string */

    return (i);
}

/******************************************************************************
 *
 * FUNCTION:    AcpiOsMapMemory
 *
 * PARAMETERS:  where               Physical address of memory to be mapped
 *              length              How much memory to map
 *              there               Logical address of mapped memory
 *
 * RETURN:      Pointer to mapped memory.  Null on error.
 *
 * DESCRIPTION: Map physical memory into caller's address space
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsMapMemory (
    UINT64                  where,
    UINT32                  length,
    void                    **there)
{
    *there = (void *) (UINT32) where;

    return AE_OK;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsUnmapMemory
 *
 * PARAMETERS:  where               Logical address of memory to be unmapped
 *              length              How much memory to unmap
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Delete a previously created mapping.  Where and Length must
 *              correspond to a previous mapping exactly.
 *
 *****************************************************************************/

void
AcpiOsUnmapMemory (
    void                    *where,
    UINT32                  length)
{

    return;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsAllocate
 *
 * PARAMETERS:  Size                Amount to allocate, in bytes
 *
 * RETURN:      Pointer to the new allocation.  Null on error.
 *
 * DESCRIPTION: Allocate memory.  Algorithm is dependent on the OS.
 *
 *****************************************************************************/

void *
AcpiOsAllocate (
    UINT32                  size)
{
    void                    *Mem;


    Mem = (void *) malloc ((size_t) size);

    return Mem;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsCallocate
 *
 * PARAMETERS:  Size                Amount to allocate, in bytes
 *
 * RETURN:      Pointer to the new allocation.  Null on error.
 *
 * DESCRIPTION: Allocate and zero memory.  Algorithm is dependent on the OS.
 *
 *****************************************************************************/

void *
AcpiOsCallocate (
    UINT32                  size)
{
    void                    *Mem;


    Mem = (void *) calloc (1, (size_t) size);

    return Mem;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsFree
 *
 * PARAMETERS:  mem                 Pointer to previously allocated memory
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Free memory allocated via AcpiOsAllocate or AcpiOsCallocate
 *
 *****************************************************************************/

void
AcpiOsFree (
    char                    *mem)
{


    free ((void *) mem);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsCreateSemaphore
 *
 * PARAMETERS:  MaxUnits            - Maximum units that can be sent
 *              InitialUnits        - Units to be assigned to the new semaphore
 *              OutHandle           - Where a handle will be returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create an OS semaphore
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsCreateSemaphore (
    UINT32              MaxUnits,
    UINT32              InitialUnits,
    ACPI_HANDLE         *OutHandle)
{
#ifdef _MULTI_THREADED
    void                *Mutex;
#endif


    if (MaxUnits == ACPI_UINT32_MAX)
    {
        MaxUnits = 255;
    }

    if (InitialUnits == ACPI_UINT32_MAX)
    {
        InitialUnits = MaxUnits;
    }

    if (InitialUnits > MaxUnits)
    {
        return AE_BAD_PARAMETER;
    }


#ifdef _MULTI_THREADED

    /* Create an OS semaphore */

    Mutex = CreateSemaphore (NULL, InitialUnits, MaxUnits, NULL);
    if (!Mutex)
    {
        DEBUG_PRINT (ACPI_ERROR, ("CreateSemaphore: could not create!\n"));

        return AE_NO_MEMORY;
    }


    SemaphoreTable[NextSemaphoreHandle].MaxUnits = (UINT16) MaxUnits;
    SemaphoreTable[NextSemaphoreHandle].CurrentUnits = (UINT16) InitialUnits;
    SemaphoreTable[NextSemaphoreHandle].OsHandle = Mutex;

    DEBUG_PRINT (ACPI_INFO, ("Created semaphore: Handle=%d, Max=%d, Current=%d, OsHandle=%p\n",
            NextSemaphoreHandle, MaxUnits, InitialUnits, Mutex));

    *OutHandle = (void *) NextSemaphoreHandle;
    NextSemaphoreHandle++;
#endif

    return AE_OK;
}

/******************************************************************************
 *
 * FUNCTION:    AcpiOsDeleteSemaphore
 *
 * PARAMETERS:  Handle              - Handle returned by AcpiOsCreateSemaphore
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Delete an OS semaphore
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsDeleteSemaphore (
    ACPI_HANDLE         Handle)
{
    UINT32              Index = (UINT32) Handle;


    if ((Index >= NUM_SEMAPHORES) ||
        !SemaphoreTable[Index].OsHandle)
    {
        return AE_BAD_PARAMETER;
    }


#ifdef _MULTI_THREADED

    CloseHandle (SemaphoreTable[Index].OsHandle);
    SemaphoreTable[Index].OsHandle = NULL;
#endif

    return AE_OK;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsWaitSemaphore
 *
 * PARAMETERS:  Handle              - Handle returned by AcpiOsCreateSemaphore
 *              Units               - How many units to wait for
 *              Timeout             - How long to wait
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Wait for units
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsWaitSemaphore (
    ACPI_HANDLE         Handle,
    UINT32              Units,
    UINT32              Timeout)
{
#ifdef _MULTI_THREADED
    UINT32              Index = (UINT32) Handle;
    UINT32              WaitStatus;


    if ((Index >= NUM_SEMAPHORES) ||
        !SemaphoreTable[Index].OsHandle)
    {
        return AE_BAD_PARAMETER;
    }

    if (Units > 1)
    {
        printf ("WaitSemaphore: Attempt to receive %d units\n", Units);
        return AE_NOT_IMPLEMENTED;
    }



/* Make this a command line option so that we can catch
 * synchronization deadlocks
 *
    if (Timeout == INFINITE)
        Timeout = 400000;
*/

    WaitStatus = WaitForSingleObject (SemaphoreTable[Index].OsHandle, Timeout);
    if (WaitStatus == WAIT_TIMEOUT)
    {
/* Make optional -- wait of 0 is used to detect if unit is available 
        DEBUG_PRINT (ACPI_ERROR, ("WaitSemaphore [%d]: *** Timeout on semaphore %d\n",
                    Handle));
*/
        return AE_TIME;
    }

    if (SemaphoreTable[Index].CurrentUnits == 0)
    {
        DEBUG_PRINT (ACPI_ERROR, ("WaitSemaphore [%d]: No units, Timeout %X, Status 0x%X\n",
                    Index, Timeout, WaitStatus));

        return AE_OK;
    }

    SemaphoreTable[Index].CurrentUnits--;
#endif


    return AE_OK;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsSignalSemaphore
 *
 * PARAMETERS:  Handle              - Handle returned by AcpiOsCreateSemaphore
 *              Units               - Number of units to send
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Send units
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsSignalSemaphore (
    ACPI_HANDLE         Handle,
    UINT32              Units)
{
#ifdef _MULTI_THREADED

    UINT32              Index = (UINT32) Handle;


    if ((Index >= NUM_SEMAPHORES) ||
        !SemaphoreTable[Index].OsHandle)
    {
        return AE_BAD_PARAMETER;
    }

    if (Units > 1)
    {
        printf ("SignalSemaphore: Attempt to signal %d units\n", Units);

        return AE_NOT_IMPLEMENTED;
    }


    if ((SemaphoreTable[Index].CurrentUnits + 1) > 
        SemaphoreTable[Index].MaxUnits)
    {
        DEBUG_PRINT (ACPI_ERROR, ("Signal: Oversignalled semaphore[%d]! Current %d Max %d\n", 
            Index, SemaphoreTable[Index].CurrentUnits, SemaphoreTable[Index].MaxUnits));

        return (AE_LIMIT);
    }

    ReleaseSemaphore (SemaphoreTable[Index].OsHandle, Units, NULL);

    SemaphoreTable[Index].CurrentUnits++;
#endif
    

    return (AE_OK);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsInstallInterruptHandler
 *
 * PARAMETERS:  InterruptNumber     Level handler should respond to.
 *              Isr                 Address of the ACPI interrupt handler
 *              ExceptPtr           Where status is returned
 *
 * RETURN:      Handle to the newly installed handler.
 *
 * DESCRIPTION: Install an interrupt handler.  Used to install the ACPI
 *              OS-independent handler.
 *
 *****************************************************************************/

UINT32
AcpiOsInstallInterruptHandler (
    UINT32                  InterruptNumber,
    OSD_HANDLER             ServiceRoutine,
    void                    *Context)
{


    return AE_OK;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsRemoveInterruptHandler
 *
 * PARAMETERS:  Handle              Returned when handler was installed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Uninstalls an interrupt handler.
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsRemoveInterruptHandler (
    UINT32                  InterruptNumber,
    OSD_HANDLER             ServiceRoutine)
{

    return AE_OK;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsGetThreadId
 *
 * PARAMETERS:  None
 *
 * RETURN:      Id of the running thread
 *
 * DESCRIPTION: Get the Id of the current (running) thread
 *
 *****************************************************************************/

UINT32
AcpiOsGetThreadId (
    void)
{


    return (GetCurrentThreadId ());

}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsQueueForExecution
 *
 * PARAMETERS:  Priority        - Requested execution priority
 *              Function        - Address of the function to execute
 *              Context         - Passed as a parameter to the function
 *
 * RETURN:      Status.
 *
 * DESCRIPTION: Sleep at microsecond granularity
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsQueueForExecution (
    UINT32                  Priority,
    OSD_EXECUTION_CALLBACK  Function,
    void                    *Context)
{

#ifdef _MULTI_THREADED
    _beginthread (Function, (unsigned) 0, Context);
#endif

    return 0;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsBreakpoint
 *
 * PARAMETERS:  Msg                 Message to print
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Print a message and break to the debugger.
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsBreakpoint (
    char                    *Msg)
{

    /* Print the message and do an INT 3 */

    if (Msg)
    {
        AcpiOsPrintf ("AcpiOsBreakpoint: %s ****\n", Msg);
    }
    else
    {
        AcpiOsPrintf ("At AcpiOsBreakpoint ****\n");
    }


    return AE_OK;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsSleepUsec
 *
 * PARAMETERS:  microseconds        To sleep
 *
 * RETURN:      Blocks until sleep is completed.
 *
 * DESCRIPTION: Sleep at microsecond granularity
 *
 *****************************************************************************/

void
AcpiOsSleepUsec (
    UINT32                  microseconds)
{

    Sleep ((microseconds / 1000) + 1);
    return;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsSleep
 *
 * PARAMETERS:  seconds             To sleep
 *              milliseconds        To sleep
 *
 * RETURN:      Blocks until sleep is completed.
 *
 * DESCRIPTION: Sleep at second/millisecond granularity
 *
 *****************************************************************************/

void
AcpiOsSleep (
    UINT32                  seconds,
    UINT32                  milliseconds)
{

    Sleep ((seconds * 1000) + milliseconds);
    return;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsReadPciCfgByte
 *
 * PARAMETERS:  Bus                 Bus ID
 *              Function            Device Function
 *              Register            Device Register
 *              Value               Buffer where value is placed
 *
 * RETURN:      Error status.  Zero is OK.
 *
 * DESCRIPTION: Read a byte (8 bits) from PCI configuration space
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsReadPciCfgByte (
    UINT32                  Bus,
    UINT32                  Function,
    UINT32                  Register,
    UINT8                   *Value)
{

    return 0;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsReadPciCfgWord
 *
 * PARAMETERS:  Bus                 Bus ID
 *              Function            Device Function
 *              Register            Device Register
 *              Value               Buffer where value is placed
 *
 * RETURN:      Error status.  Zero is OK.
 *
 * DESCRIPTION: Read a word (16 bits) from PCI configuration space
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsReadPciCfgWord (
    UINT32                  Bus,
    UINT32                  Function,
    UINT32                  Register,
    UINT16                  *Value)
{

    return 0;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsReadPciCfgDword
 *
 * PARAMETERS:  Bus                 Bus ID
 *              Function            Device Function
 *              Register            Device Register
 *              Value               Buffer where value is placed
 *
 * RETURN:      Error status.  Zero is OK.
 *
 * DESCRIPTION: Read a dword (32 bits) from PCI configuration space
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsReadPciCfgDword (
    UINT32                  Bus,
    UINT32                  Function,
    UINT32                  Register,
    UINT32                  *Value)
{

    *Value = (UINT32) 0xA7; // Just a random number
    return 0;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsWritePciCfgByte
 *
 * PARAMETERS:  Bus                 Bus ID
 *              Function            Device Function
 *              Register            Device Register
 *              Value               Value to be written
 *
 * RETURN:      Error status.  Zero is OK.
 *
 * DESCRIPTION: Write a byte (8 bits) to PCI configuration space
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsWritePciCfgByte (
    UINT32                  Bus,
    UINT32                  Function,
    UINT32                  Register,
    UINT8                   Value)
{

    return 0;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsWritePciCfgWord
 *
 * PARAMETERS:  Bus                 Bus ID
 *              Function            Device Function
 *              Register            Device Register
 *              Value               Value to be written
 *
 * RETURN:      Error status.  Zero is OK.
 *
 * DESCRIPTION: Write a word (16 bits) to PCI configuration space
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsWritePciCfgWord (
    UINT32                  Bus,
    UINT32                  Function,
    UINT32                  Register,
    UINT16                  Value)
{

    return 0;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsWritePciCfgDword
 *
 * PARAMETERS:  Bus                 Bus ID
 *              Function            Device Function
 *              Register            Device Register
 *              Value               Value to be written
 *
 * RETURN:      Error status.  Zero is OK.
 *
 * DESCRIPTION: Write a dword (32 bits) to PCI configuration space
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsWritePciCfgDword (
    UINT32                  Bus,
    UINT32                  Function,
    UINT32                  Register,
    UINT32                  Value)
{
    return 0;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsIn8
 *
 * PARAMETERS:  Port                Address of I/O port/register to read
 *
 * RETURN:      Value read from port
 *
 * DESCRIPTION: Read a byte (8 bits) from an I/O port or register
 *
 *****************************************************************************/

UINT8
AcpiOsIn8 (
    ACPI_IO_ADDRESS         Port)
{

    return ((UINT8) 0);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsIn16
 *
 * PARAMETERS:  Port                Address of I/O port/register to read
 *
 * RETURN:      Value read from port
 *
 * DESCRIPTION: Read a word (16 bits) from an I/O port or register
 *
 *****************************************************************************/

UINT16
AcpiOsIn16 (
    ACPI_IO_ADDRESS         Port)
{

    return ((UINT16) 0);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsIn32
 *
 * PARAMETERS:  Port                Address of I/O port/register to read
 *
 * RETURN:      Value read from port
 *
 * DESCRIPTION: Read a dword (32 bits) from an I/O port or register
 *
 *****************************************************************************/

UINT32
AcpiOsIn32 (
    ACPI_IO_ADDRESS         Port)
{

    return ((UINT32) 0);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsOut8
 *
 * PARAMETERS:  Port                Address of I/O port/register to write
 *              Value               Value to write
 *
 * RETURN:      None
 *
 * DESCRIPTION: Write a byte (8 bits) to an I/O port or register
 *
 *****************************************************************************/

void
AcpiOsOut8 (
    ACPI_IO_ADDRESS         Port,
    UINT8                   Value)
{

}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsOut16
 *
 * PARAMETERS:  Port                Address of I/O port/register to write
 *              Value               Value to write
 *
 * RETURN:      None
 *
 * DESCRIPTION: Write a word (16 bits) to an I/O port or register
 *
 *****************************************************************************/

void
AcpiOsOut16 (
    ACPI_IO_ADDRESS         Port,
    UINT16                  Value)
{

}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsOut32
 *
 * PARAMETERS:  Port                Address of I/O port/register to write
 *              Value               Value to write
 *
 * RETURN:      None
 *
 * DESCRIPTION: Write a dword (32 bits) to an I/O port or register
 *
 *****************************************************************************/

void
AcpiOsOut32 (
    ACPI_IO_ADDRESS         Port,
    UINT32                  Value)
{

}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsMemIn8
 *
 * PARAMETERS:  PhysAddr        Physical Memory Address to read
 *
 * RETURN:      Value read from physical memory address
 *
 * DESCRIPTION: Read a byte (8 bits) from a physical memory address
 *
 *****************************************************************************/

UINT8
AcpiOsMemIn8 (
    ACPI_PHYSICAL_ADDRESS   PhysAddr)
{

    return ((UINT8) 0);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsMemIn16
 *
 * PARAMETERS:  PhysAddr        Physical Memory Address to read
 *
 * RETURN:      Value read from physical memory address
 *
 * DESCRIPTION: Read a word (16 bits) from a physical memory address
 *
 *****************************************************************************/

UINT16
AcpiOsMemIn16 (
    ACPI_PHYSICAL_ADDRESS   PhysAddr)
{

    return ((UINT16) 0);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsMemIn32
 *
 * PARAMETERS:  PhysAddr        Physical Memory Address to read
 *
 * RETURN:      Value read from physical memory address
 *
 * DESCRIPTION: Read a dword (32 bits) from a physical memory address
 *
 *****************************************************************************/

UINT32
AcpiOsMemIn32 (
    ACPI_PHYSICAL_ADDRESS   PhysAddr)
{

    return ((UINT32) 0);
}

/******************************************************************************
 *
 * FUNCTION:    AcpiOsMemOut8
 *
 * PARAMETERS:  PhysAddr        Physical Memory Address to write
 *              Value           Value to write
 *
 * RETURN:      None
 *
 * DESCRIPTION: Write a byte (8 bits) to a physical memory address
 *
 *****************************************************************************/

void
AcpiOsMemOut8 (
    ACPI_PHYSICAL_ADDRESS   PhysAddr,
    UINT8                   Value)
{
    return;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsMemOut16
 *
 * PARAMETERS:  PhysAddr        Physical Memory Address to write
 *              Value           Value to write
 *
 * RETURN:      None
 *
 * DESCRIPTION: Write a word (16 bits) to a physical memory address
 *
 *****************************************************************************/

void
AcpiOsMemOut16 (
    ACPI_PHYSICAL_ADDRESS   PhysAddr,
    UINT16                  Value)
{
    return;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsMemOut32
 *
 * PARAMETERS:  PhysAddr        Physical Memory Address to write
 *              Value           Value to write
 *
 * RETURN:      None
 *
 * DESCRIPTION: Write a dword (32 bits) to a physical memory address
 *
 *****************************************************************************/

void
AcpiOsMemOut32 (
    ACPI_PHYSICAL_ADDRESS   PhysAddr,
    UINT32                  Value)
{
    return;
}

/******************************************************************************
 *
 * FUNCTION:    AcpiOsDbgTrap
 *
 * PARAMETERS:  pTrapCause      - pointer to char array that contains description
 *                                of cause of trap.
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Trap. Causes execution to halt after logging message.
 *
 *****************************************************************************/

void
AcpiOsDbgTrap (char *pTrapCause)
{
} // Debug_TRAP


/******************************************************************************
 *
 * FUNCTION:    AcpiOsDbgTrap
 *
 * PARAMETERS:  This should not be called directly. Use DEBUG_ASSERT macro.
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Assertion routine.
 *
 *****************************************************************************/

void
AcpiOsDbgAssert(void *FailedAssertion, void *FileName, UINT32 LineNumber,
             char *Message)
{

//    return 0;
} // Debug_Assert


