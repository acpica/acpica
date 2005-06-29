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
 | $Revision: 1.7 $
 | $Date: 2005/06/29 19:58:23 $
 | $Log: acpi.h,v $
 | Revision 1.7  2005/06/29 19:58:23  aystarik
 | Integrated with 03/99 OPSD code
 |
 | 
 | date	99.03.31.22.34.00;	author rmoore1;	state Exp;
 |
 * 
 * 7     3/31/99 2:34p Rmoore1
 * Integrated with 03/99 OPSD code
 * 
 * 6     3/11/99 4:17p Rmoore1
 * Moved major table-size constants to here
 * 
 * 5     2/12/99 10:26a Rmosgrov
 * Anti-Polish clean up
 * 
 * 4     2/02/99 4:01p Rmoore1
 * Cleanup.  Support for tables up to 48K.
 * 
 * 3     1/13/99 10:50a Grsmith1
 * First BeOS compatible check-in.
 * 
 * 2     1/11/99 4:15p Grsmith1
 * 
 * 1     1/11/99 2:10p Rmoore1
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
#include <acpitype.h>       /* Common ACPI types */
#include <acpiosd.h>        /* Interfaces to OS-dependent part (OSD) */


#ifdef DEFINE_ACPI_GLOBALS
#define ACPI_EXTERN
#pragma message ("ACPI_EXTERN variables defined in this module.")

#else
#define ACPI_EXTERN extern
#endif


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
ACPI_EXTERN INT32                               OutOfMemory;

/* Runtime error message communication */

extern char WhyBuf[WHYBUF_SIZE];
extern char *Why;




#define	ACPI_CHAPTER						3
#define	ACPI_TABLE_NAMESPACE_SECTION	    23


#endif /* __ACPI_H__ */
