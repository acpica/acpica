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
 | $Revision: 1.8 $
 | $Date: 2005/06/29 19:59:43 $
 | $Log: acpiosxf.h,v $
 | Revision 1.8  2005/06/29 19:59:43  aystarik
 | Added File header
 |
 | 
 | date	99.02.12.18.29.00;	author rmosgrov;	state Exp;
 |
 * 
 * 8     2/12/99 10:29a Rmosgrov
 * Added File header
 */

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

int 
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

int 
OsdPrintf (
    OSD_FILE *      stream, 
    const char *    format, 
    ...);

int 
OsdFlushall (
    void);


/* Memory allocation */

void *
OsdAllocate (
    unsigned long   size);

char *
OsdCallocate (
    unsigned long   num, 
    unsigned long   size);

void 
OsdFree (
    void *          mem);


/* Memory mapping */

char *
OsdMapMemory (
    unsigned long   where,
    unsigned long   length);

void 
OsdUnMapMemory (
    char *          where, 
    unsigned long   length);



/* Interrupt handlers */

void *OsdInstallInterruptHandler (
    unsigned long   InterruptNumber,
    int             (* Isr)(void),
    unsigned long * ExceptPtr);


/* Scheduling */

void
OsdSleep (
    unsigned long   seconds,
    unsigned long   milliseconds);

void
OsdSleepUsec (
    unsigned long   microseconds);



/* Misc */

int OsdAssert (
    void *);



