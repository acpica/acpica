
/*
 * acpiosd - OS dependent interfaces
 *
 * These interfaces must be implemented by the OS-dependent front-end
 * to the ACPI subsystem.
 */

#include "acpiasm.h"

#define OSD_FILE    void

// FIX THIS !!
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



