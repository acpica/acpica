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
 | $Revision: 1.4 $
 | $Date: 2005/06/29 19:58:20 $
 | $Log: acpi.h,v $
 | Revision 1.4  2005/06/29 19:58:20  aystarik
 | Cleanup.  Support for tables up to 48K.
 |
 | 
 | date	99.02.03.00.01.00;	author rmoore1;	state Exp;
 |
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
 * This is used to generate the physical to logical mappings.
 * TBD: Probably not a good idea.
 */

#define MAX_ACPI_TABLE_SIZE         49152



#ifndef ACPILIB_GEN
    #include <amlpub.h>
    #include <amlscan.h>
    #include <acpitype.h>
    #include <acpievnt.h>
    #include <acpilgcy.h>
    #include <acpinmsp.h>
    #include <acpipmt.h>
    #include <acpislwa.h>
    #include <acpitbls.h>
    #include <acpirio.h>
    #include <debuglvl.h>
    #include <device.h>
    #include <display.h>
    #include <exmethod.h>
    #include <scilast.h>
#else
    #include "acpitype.h"
#endif  


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

ACPI_EXTERN ROOT_SYSTEM_DESCRIPTOR_POINTER      * pRSDP;
ACPI_EXTERN ROOT_SYSTEM_DESCRIPTION_TABLE       * pRSDT;
ACPI_EXTERN FIRMWARE_ACPI_CONTROL_STRUCTURE     * pFACS;
ACPI_EXTERN FIXED_ACPI_DESCRIPTION_TABLE        * pFACP;
ACPI_EXTERN APIC_TABLE                          * pMAPIC;
ACPI_EXTERN ACPI_TABLE_HEADER                   * pDSDT;
ACPI_EXTERN ACPI_TABLE_HEADER                   * pPSDT;


/* 
 * TBD - There may be multiple SSDTs so a single pointer is not sufficient 
 * to tag them all.  An array or linked list of SSDT pointers will be
 * necessary. 
 */

ACPI_EXTERN ACPI_TABLE_HEADER                   * pSSDT;
ACPI_EXTERN ACPI_TABLE_HEADER                   * pSBDT;


#endif /* __ACPI_H__ */
