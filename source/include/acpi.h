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
 | FILENAME: acpi.h - Master include file, Publics and external data for ACPI.LIB
 |__________________________________________________________________________
 |
//
//    Rev 1.0   Feb 28 1997 08:59:22   KBRANNOC
// Initial revision.
 |__________________________________________________________________________

*/

#ifndef __ACPI_H__
#define __ACPI_H__

/*
 * Standard C library headers.
 * We want to keep these to a minimum.
 */
#include <stdio.h>


/* 
 * Common includes for all ACPI driver files
 * We put them here because we don't want to duplicate them
 * in the rest of the source again and again.
 */
#include <datatypes.h>      /* Fundamental data types */
#include <excep.h>          /* Local exception codes */
#include <config.h>         /* Configuration constants */
#include <output.h>         /* Error output and Debug macros */
#include <acpiasm.h>        /* Assembly macros */
#include <acpitables.h>     /* ACPI table definitions */
#include <acpiosd.h>        /* Interfaces to OS-dependent part (OSD) */


#ifdef DEFINE_ACPI_GLOBALS
#define ACPI_EXTERN
#pragma message ("ACPI_EXTERN variables defined in this module.")

#else
#define ACPI_EXTERN extern
#endif


/* Version string */

#define ACPI_LIB_VER "032"
#define OS_ACPI_LIB_VER "F" ## ACPI_LIB_VER
#define ACPILIB_VERSION " ACPILIB-" ## OS_ACPI_LIB_VER



/* 
 * global data, DEFINE_ACPI_GLOBALS is defined in ACPIPRIV.C,
 * Initialization of all variables occurs in iAcpiInit 
 */

ACPI_EXTERN ROOT_SYSTEM_DESCRIPTOR_POINTER      * RSDP;
ACPI_EXTERN ROOT_SYSTEM_DESCRIPTION_TABLE       * RSDT;
ACPI_EXTERN FIRMWARE_ACPI_CONTROL_STRUCTURE     * FACS;
ACPI_EXTERN FIXED_ACPI_DESCRIPTION_TABLE        * FACP;
ACPI_EXTERN APIC_TABLE                          * MAPIC;
ACPI_EXTERN ACPI_TABLE_HEADER                   * DSDT;
ACPI_EXTERN ACPI_TABLE_HEADER                   * PSDT;


/* 
 * TBD - There may be multiple SSDTs so a single pointer is not sufficient 
 * to tag them all.  An array or linked list of SSDT pointers will be
 * necessary. 
 */

ACPI_EXTERN ACPI_TABLE_HEADER                   * SSDT;
ACPI_EXTERN ACPI_TABLE_HEADER                   * SBDT;



/*  
 * OutOfMemory is initialized to FALSE and is set to TRUE whenever
 * an ACPI.LIB allocation failure is encountered.
 */
ACPI_EXTERN INT32       OutOfMemory;



/* Misc Globals */

ACPI_EXTERN INT32       Capabilities;
ACPI_EXTERN OSD_FILE    *fAsmFile;      /* If not null, /A output gets written here */
ACPI_EXTERN LogHandle   LstFileHandle;  /* /L output gets written here */
ACPI_EXTERN INT32       NameStringSize;
ACPI_EXTERN char        *NameString;    /* Runtime AML error message communication */


/* These must not be ACPI_EXTERN since they need explicit initialization */

extern char             *AsmFile;           /* defined in acpipriv.c */
extern char             *DsdtFile;          /* defined in acpipriv.c */
extern char             *OutputFile;        /* defined in acpipriv.c */
extern char             *InputFile;         /* defined in acpipriv.c */
extern                  HardwareOverride;   /* defined in AcpiTbls.c */
extern INT32            AcpiHook;           /* strong link that lives in acpilibv.c */




/* Runtime error message communication */

extern char             WhyBuf[WHYBUF_SIZE];
extern char             *Why;


extern INT32            DebugLevel;
extern INT32            DebugLayer;



#define	ACPI_CHAPTER						3
#define	ACPI_TABLE_NAMESPACE_SECTION	    23


#endif /* __ACPI_H__ */
