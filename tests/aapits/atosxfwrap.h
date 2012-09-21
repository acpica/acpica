/******************************************************************************
 *
 * Module Name: atosxfwrap - include for AcpiOs* interfaces wrapping
 *                           derived from acpixf.h
 *
 *****************************************************************************/

#ifndef _AT_OSXF_WRAP
#define _AT_OSXF_WRAP

/*
 * OSL Initialization and shutdown primitives
 */
ACPI_STATUS
AcpiOsActualInitialize (
    void);

ACPI_STATUS
AcpiOsActualTerminate (
    void);


/*
 * ACPI Table interfaces
 */
/*
ACPI_STATUS
AcpiOsActualGetRootPointer (
    UINT32                  Flags,
    ACPI_POINTER            *Address);
*/
ACPI_PHYSICAL_ADDRESS
AcpiOsActualGetRootPointer (
    void);

ACPI_STATUS
AcpiOsActualPredefinedOverride (
    const ACPI_PREDEFINED_NAMES *InitVal,
    ACPI_STRING                 *NewVal);

ACPI_STATUS
AcpiOsActualTableOverride (
    ACPI_TABLE_HEADER       *ExistingTable,
    ACPI_TABLE_HEADER       **NewTable);


/*
 * Synchronization primitives
 */
ACPI_STATUS
AcpiOsActualCreateSemaphore (
    UINT32                  MaxUnits,
    UINT32                  InitialUnits,
    ACPI_HANDLE             *OutHandle);

ACPI_STATUS
AcpiOsActualDeleteSemaphore (
    ACPI_HANDLE             Handle);

ACPI_STATUS
AcpiOsActualWaitSemaphore (
    ACPI_HANDLE             Handle,
    UINT32                  Units,
    UINT16                  Timeout);

ACPI_STATUS
AcpiOsActualSignalSemaphore (
    ACPI_HANDLE             Handle,
    UINT32                  Units);

ACPI_STATUS
AcpiOsActualCreateLock (
    ACPI_HANDLE             *OutHandle);

void
AcpiOsActualDeleteLock (
    ACPI_HANDLE             Handle);

ACPI_CPU_FLAGS
AcpiOsActualAcquireLock (
    ACPI_HANDLE             Handle);

void
AcpiOsActualReleaseLock (
    ACPI_HANDLE             Handle,
    ACPI_CPU_FLAGS          Flags);


/*
 * Memory allocation and mapping
 */
void *
AcpiOsActualAllocate (
    ACPI_SIZE               Size);

void
AcpiOsActualFree (
    void *                  Memory);

/*
ACPI_STATUS
AcpiOsActualMapMemory (
    ACPI_PHYSICAL_ADDRESS   PhysicalAddress,
    ACPI_SIZE               Size,
    void                    **LogicalAddress);
*/
void *
AcpiOsActualMapMemory (
    ACPI_PHYSICAL_ADDRESS   Where,
    ACPI_SIZE               Length);

void
AcpiOsActualUnmapMemory (
    void                    *LogicalAddress,
    ACPI_SIZE               Size);

ACPI_STATUS
AcpiOsActualGetPhysicalAddress (
    void                    *LogicalAddress,
    ACPI_PHYSICAL_ADDRESS   *PhysicalAddress);


/*
 * Memory/Object Cache
 */
ACPI_STATUS
AcpiOsActualCreateCache (
    char                    *CacheName,
    UINT16                  ObjectSize,
    UINT16                  MaxDepth,
    ACPI_CACHE_T            **ReturnCache);

ACPI_STATUS
AcpiOsActualDeleteCache (
    ACPI_CACHE_T            *Cache);

ACPI_STATUS
AcpiOsActualPurgeCache (
    ACPI_CACHE_T            *Cache);

void *
AcpiOsActualAcquireObject (
    ACPI_CACHE_T            *Cache);

ACPI_STATUS
AcpiOsActualReleaseObject (
    ACPI_CACHE_T            *Cache,
    void                    *Object);


/*
 * Interrupt handlers
 */
ACPI_STATUS
AcpiOsActualInstallInterruptHandler (
    UINT32                  InterruptNumber,
    ACPI_OSD_HANDLER        ServiceRoutine,
    void                    *Context);

ACPI_STATUS
AcpiOsActualRemoveInterruptHandler (
    UINT32                  InterruptNumber,
    ACPI_OSD_HANDLER        ServiceRoutine);


/*
 * Threads and Scheduling
 */
ACPI_THREAD_ID
AcpiOsActualGetThreadId (
    void);

ACPI_STATUS
AcpiOsActualExecute (
    ACPI_EXECUTE_TYPE       Type,
    ACPI_OSD_EXEC_CALLBACK  Function,
    void                    *Context);

void
AcpiOsActualWaitEventsComplete (
    void                    *Context);

void
AcpiOsActualSleep (
    ACPI_INTEGER            Milliseconds);

void
AcpiOsActualStall (
    UINT32                  Microseconds);

ACPI_STATUS
AcpiOsActualValidateInterface (
    char                    *Interface);

ACPI_STATUS
AcpiOsActualValidateAddress (
    UINT8                   SpaceId,
    ACPI_PHYSICAL_ADDRESS   Address,
    ACPI_SIZE               Length);

/*
 * Platform and hardware-independent I/O interfaces
 */
ACPI_STATUS
AcpiOsActualReadPort (
    ACPI_IO_ADDRESS         Address,
    UINT32                  *Value,
    UINT32                  Width);

ACPI_STATUS
AcpiOsActualWritePort (
    ACPI_IO_ADDRESS         Address,
    UINT32                  Value,
    UINT32                  Width);


/*
 * Platform and hardware-independent physical memory interfaces
 */
ACPI_STATUS
AcpiOsActualReadMemory (
    ACPI_PHYSICAL_ADDRESS   Address,
    UINT64                  *Value,
    UINT32                  Width);

ACPI_STATUS
AcpiOsActualWriteMemory (
    ACPI_PHYSICAL_ADDRESS   Address,
    UINT64                  Value,
    UINT32                  Width);


/*
 * Platform and hardware-independent PCI configuration space access
 * Note: Can't use "Register" as a parameter, changed to "Reg" --
 * certain compilers complain.
 */
ACPI_STATUS
AcpiOsActualReadPciConfiguration (
    ACPI_PCI_ID             *PciId,
    UINT32                  Reg,
    void                    *Value,
    UINT32                  Width);

ACPI_STATUS
AcpiOsActualWritePciConfiguration (
    ACPI_PCI_ID             *PciId,
    UINT32                  Reg,
    ACPI_INTEGER            Value,
    UINT32                  Width);

/*
 * Interim function needed for PCI IRQ routing
 */
void
AcpiOsActualDerivePciId(
    ACPI_HANDLE             Rhandle,
    ACPI_HANDLE             Chandle,
    ACPI_PCI_ID             **PciId);

/*
 * Miscellaneous
 */
BOOLEAN
AcpiOsActualReadable (
    void                    *Pointer,
    ACPI_SIZE               Length);

BOOLEAN
AcpiOsActualWritable (
    void                    *Pointer,
    ACPI_SIZE               Length);

UINT64
AcpiOsActualGetTimer (
    void);

ACPI_STATUS
AcpiOsActualSignal (
    UINT32                  Function,
    void                    *Info);

/*
 * Debug print routines
 */
void ACPI_INTERNAL_VAR_XFACE
AcpiOsActualPrintf (
    const char              *Format,
    ...);

void
AcpiOsActualVprintf (
    const char              *Format,
    va_list                 Args);

void
AcpiOsActualRedirectOutput (
    void                    *Destination);


/*
 * Debug input
 */
UINT32
AcpiOsActualGetLine (
    char                    *Buffer);


/*
 * Directory manipulation
 */
void *
AcpiOsActualOpenDirectory (
    char                    *Pathname,
    char                    *WildcardSpec,
    char                    RequestedFileType);

/* RequesteFileType values */

#define REQUEST_FILE_ONLY                   0
#define REQUEST_DIR_ONLY                    1


char *
AcpiOsActualGetNextFilename (
    void                    *DirHandle);

void
AcpiOsActualCloseDirectory (
    void                    *DirHandle);

/*
 * Debug
 */
void
AcpiOsActualDbgAssert(
    void                    *FailedAssertion,
    void                    *FileName,
    UINT32                  LineNumber,
    char                    *Message);

#endif /* _AT_OSXF_WRAP */
