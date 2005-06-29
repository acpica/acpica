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
 | FILENAME: acpiosd.h - OS Dependant 
 |__________________________________________________________________________
 |
 |
 | acpiosd - OS dependent interfaces
 |
 | These interfaces must be implemented by the OS-dependent front-end
 | to the ACPI subsystem.
 |
 | $Revision: 1.9 $
 | $Date: 2005/06/29 19:59:45 $
 | $Log: acpiosxf.h,v $
 | Revision 1.9  2005/06/29 19:59:45  aystarik
 | 16/32/64-bit common data types
 |
 | 
 | date	99.03.10.00.04.00;	author rmoore1;	state Exp;
 |
 * 
 * 9     3/09/99 4:04p Rmoore1
 * 16/32/64-bit common data types
 * 
 * 8     2/12/99 10:29a Rmosgrov
 * Added File header
 */

#include "datatypes.h"
#include "acpiasm.h"

#define OSD_FILE    void

/* FIX THIS !! */
#ifndef _SIZE_T_DEFINED
typedef unsigned int size_t;
#define _SIZE_T_DEFINED
#endif


/* File I/O */


OSD_FILE *
OsdOpen (
    const char *    filename, 
    const char *    mode);

INT32 
OsdClose (
    OSD_FILE *      stream);

size_t 
OsdRead (
    void *          buffer, 
    size_t          size, 
    size_t          count, 
    OSD_FILE *      stream);

size_t 
OsdWrite (
    const void *    buffer, 
    size_t          size, 
    size_t          count, 
    OSD_FILE *      stream); 

INT32 
OsdPrintf (
    OSD_FILE *      stream, 
    const char *    format, 
    ...);

INT32 
OsdFlushall (
    void);


/* Memory allocation */

void *
OsdAllocate (
    UINT32          size);

char *
OsdCallocate (
    UINT32          num, 
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
    UINT32          * ExceptPtr);


/* Scheduling */

void
OsdSleep (
    UINT32          seconds,
    UINT32          milliseconds);

void
OsdSleepUsec (
    UINT32          microseconds);



/* Misc */

INT32 
OsdAssert (
    void *);


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
OsdReadPciCfgByte (INT32, INT32, INT32, UINT8 *);

UINT8 
OsdReadPciCfgWord (INT32, INT32, INT32, UINT16 *);

UINT8 
OsdReadPciCfgDword (INT32, INT32, INT32, UINT32 *);

UINT8 
OsdWritePciCfgByte (INT32, INT32, INT32, UINT8);

UINT8 
OsdWritePciCfgWord (INT32, INT32, INT32, UINT16);

UINT8 
OsdWritePciCfgDword (INT32, INT32, INT32, UINT32);




