/*
  __________________________________________________________________________
 |
 |
 |           Copyright (C) Intel Corporation 1994-1996
 |
 | All rights reserved.  No part of this program or publication may be
 | reproduced, transmitted, transcribed, stored in a retrieval system, or
 | translated into any language or computer language, in any form or by any
 | means, electronic, mechanical, magnetic, optical, chemical, manual, or
 | otherwise, without the prior written permission of Intel Corporation.
 |__________________________________________________________________________
 |
 | FILENAME: acpiosd.h - All interfaces to the OS-dependent layer
 |__________________________________________________________________________
 |
 |
 | These interfaces must be implemented by the OS-dependent front-end
 | to the ACPI subsystem.
 |
 */

/*
 */
#include <datatypes.h>
#include <acpiasm.h>
#include <stdarg.h>



/* File I/O */

//#define LogHandle void*

OSD_FILE *
OsdOpen (
    const char      *filename, 
    const char      *mode);

INT32 
OsdClose (
    OSD_FILE        *stream);

UINT32 
OsdRead (
    void            *buffer, 
    UINT32          size, 
    UINT32          count, 
    OSD_FILE        *stream);

UINT32 
OsdWrite (
    const void      *buffer, 
    UINT32          size, 
    UINT32          count, 
    OSD_FILE        *stream); 

INT32 
OsdPrintf (
    OSD_FILE        *stream, 
    const char      *format, 
    ...);

INT32
OsdVprintf (
    OSD_FILE        *stream, 
    const char      *format, 
    va_list         args);

INT32 
OsdFlushall (
    void);


/* Memory allocation */

void *
OsdAllocate (
    UINT32          size);

void *
OsdCallocate (
    UINT32          size);

void 
OsdFree (
    void *          mem);


/* Memory mapping */

char *
OsdMapMemory (
    UINT32          where,
    UINT32          length);

void 
OsdUnMapMemory (
    char *          where, 
    UINT32          length);



/* Interrupt handlers */

UINT32
OsdInstallInterruptHandler (
    UINT32          InterruptNumber,
    INT32           (* Isr)(void),
    UINT32          *ExceptPtr);

void
OsdRemoveInterruptHandler (
    UINT32          Handle);


/* Scheduling */

void
OsdSleep (
    UINT32          seconds,
    UINT32          milliseconds);

void
OsdSleepUsec (
    UINT32          microseconds);



/*
 * Platform/Hardware independent I/O interfaces
 */

UINT8
OsdIn8 (
    UINT16          InPort);

UINT16
OsdIn16 (
    UINT16          InPort);

UINT32
OsdIn32 (
    UINT16          InPort);

void
OsdOut8 (
    UINT16          OutPort, 
    UINT8           Value);

void
OsdOut16 (
    UINT16          OutPort, 
    UINT16          Value);

void
OsdOut32 (
    UINT16          OutPort, 
    UINT32          Value);


/*
 * Standard access to PCI configuration space
 */

UINT8 
OsdReadPciCfgByte (
    INT32           Bus, 
    INT32           DeviceFunction, 
    INT32           Register, 
    UINT8           *Value);

UINT8 
OsdReadPciCfgWord (
    INT32           Bus, 
    INT32           DeviceFunction, 
    INT32           Register, 
    UINT16          *Value);

UINT8 
OsdReadPciCfgDword (
    INT32           Bus, 
    INT32           DeviceFunction, 
    INT32           Register, 
    UINT32          *Value);

UINT8 
OsdWritePciCfgByte (
    INT32           Bus, 
    INT32           DeviceFunction, 
    INT32           Register, 
    UINT8           Value);

UINT8 
OsdWritePciCfgWord (
    INT32           Bus, 
    INT32           DeviceFunction, 
    INT32           Register, 
    UINT16          Value);

UINT8 
OsdWritePciCfgDword (
    INT32           Bus, 
    INT32           DeviceFunction, 
    INT32           Register, 
    UINT32          Value);




