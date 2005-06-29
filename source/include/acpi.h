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
 | FILENAME: acpi.h - Publics and external data for ACPI.LIB
 |__________________________________________________________________________
 |
 | $Revision: 1.6 $
 | $Date: 2005/06/29 19:58:22 $
 | $Log: acpi.h,v $
 | Revision 1.6  2005/06/29 19:58:22  aystarik
 | Moved major table-size constants to here
 |
 | 
 | date	99.03.12.00.17.00;	author rmoore1;	state Exp;
 |
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
 * Subsystem headers
// 
//    Rev 1.12   12 Aug 1998 15:55:12   jkreinem
// added inclusion of scilast.h
// 
//    Rev 1.11   02 Feb 1998 10:07:16   kdbranno
// Moved ACPI_EXTERN declarations for the global table pointers
// (pRSDP, pRSDT, pFACS, ...) from acpipriv.h to acpi.h.  These
// pointers are to be available to applications so they must be
// declared publicly.
// 
//    Rev 1.10   16 Oct 1997 09:34:00   kdbranno
// Removed ability for an acpi library module to get any meaningful inclusion of
// acpi.h.  This header is intended for application use only.  Library modules
// should include the specific acpilib headers they need.
// 
//    Rev 1.9   03 Sep 1997 14:45:56   kdbranno
// Added #include for debuglvl.h and device.h
// 
//    Rev 1.8   17 Jul 1997 12:09:08   kdbranno
// Removed references to dossuprt.h. This support has been moved to BU.
// 
//    Rev 1.7   19 Jun 1997 16:10:56   kdbranno
// Fixed problem with #include after ACPIPATH was removed from acpilib
// generation makefile
// 
//    Rev 1.6   12 Jun 1997 15:50:50   kdbranno
// Modified so it correctly includes headers depending on library generation...
//
//    Rev 1.5   10 Jun 1997 10:57:52   kdbranno
// Added check for library generation for #include's
//
//    Rev 1.4   09 Jun 1997 13:15:38   kdbranno
// Added #include <acpirio.h> to acpi.h
//
//    Rev 1.3   Mar 24 1997 17:47:28   KBRANNOC
// Added #include <amlscan.h> and conditional #include <dossuprt.h>
//
//    Rev 1.2   Mar 20 1997 17:59:08   KBRANNOC
// Added #include for display.h
//
//    Rev 1.1   Mar 05 1997 16:43:48   KBRANNOC
// Removed #include of BU.H, moved #include of ACPITYPE.H to top.
//
//    Rev 1.0   Feb 28 1997 08:59:22   KBRANNOC
// Initial revision.
 |__________________________________________________________________________

*/

#ifndef __ACPI_H__
#define __ACPI_H__

/* 
 * All scary-looking constants should go here!!! 
 * 
 * Some of these should be fixed or at least made run-time configurable.
 *
 */

/*
 * AML Interpreter
 */

#define MAX_ACPI_TABLE_SIZE         49152   /* For phys to logical mapping */
#define AML_PKG_MAX_NEST            100     /* Max depth of package nesting */
#define AML_METHOD_MAX_NEST         10      /* Max depth of nested method calls */
#define INITIAL_NAME_BUF_SIZE       32

/* 
 * NameSpace Table sizes
 * 
 * If USE_HASHING is #defined, these must be prime numbers and
 * should be large enough that the tables never get terribly full.
 *
 * The root NT was made bigger than others in the possibly erroneous
 * expectation that there might be quite a few entries in the root.
 */

#ifdef USE_HASHING
#define ROOTSIZE                    101     /* # of slots in root table */
#define TABLSIZE                    53      /* # of slots per table below the root */

#else
#define ROOTSIZE                    40      /* initial # of slots in root table */
#define TABLSIZE                    20      /* initial # of slots per table below the root */
#endif

#define MAXNEST                     15      /* Max nesting of name scopes, used for sizing stacks */



#include "acpitype.h"

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
 * Common macros
 */



#endif /* __ACPI_H__ */
