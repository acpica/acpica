/*
  __________________________________________________________________________
 |
 |
 |           Copyright (C) Intel Corporation 1994-1998
 |
 | All rights reserved. No part of this program or publication may be
 | reproduced, transmitted, transcribed, stored in a retrieval system, or
 | translated into any language or computer language, in any form or by any
 | means, electronic, mechanical, magnetic, optical, chemical, manual, or
 | otherwise, without the prior written permission of Intel Corporation.
 |__________________________________________________________________________
 |
 | FILENAME: scilast.h -  System Control Interrupt configuration and
 |                                  legacy to ACPI mode state transition functions
 |__________________________________________________________________________
 |
 | $Revision: 1.3 $
 | $Date: 2005/06/29 19:31:09 $
 | $Log: acevents.h,v $
 | Revision 1.3  2005/06/29 19:31:09  aystarik
 | Made pretty
 |
 | 
 | date	99.02.16.22.36.00;	author rmoore1;	state Exp;
 |
 * 
 * 3     2/16/99 2:36p Rmoore1
 * Made pretty
 * 
 * 2     2/12/99 2:26p Rmosgrov
 * 
 * 1     2/12/99 9:57a Rmosgrov
 * 
 * 1     2/12/99 9:54a Rmosgrov
 * 
 * 3     1/13/99 2:49p Grsmith1
 * First BeOS build.
 * 
 * 2     1/11/99 4:08p Grsmith1
 * Detabified.
 * 
 * 1     1/11/99 2:08p Rmoore1
 * Event Handling
// 
//    Rev 1.2   14 Aug 1998 17:46:16   jkreinem
// Added VerifyAcpiTablesPresent() function and NO_ACPI_TABLES_MASK
// error code.
// 
//    Rev 1.1   13 Aug 1998 17:27:34   jkreinem
// Added SAVE_NOT_VALID definition for interrupt configuration.
// 
//    Rev 1.0   12 Aug 1998 15:54:32   jkreinem
// Initial revision.
 |__________________________________________________________________________

*/

#ifndef __EVSCI_H__
#define __EVSCI_H__


/*  InstallSCIHandlerXferToACPI() Flags bitmask options   */

#define ACPI_TABLES_REQUIRED            1
#define HW_OVERRIDE_SUPPORTED           2
#define PROGRAM_SCI_LEVEL_SENSITIVITY   4
#define DISABLE_KNOWN_EVENTS            8


/*  iErrorMask mask bits    */

#define NO_ACPI_TABLES_MASK             1
#define NO_ACPI_TRANSITION_MASK         2
#define SCI_LEVEL_INT_MASK              4
#define NO_SCI_HANDLER_MASK             8
#define NO_LEGACY_TRANSITION_MASK       0x10

#define SAVE_NOT_VALID                  -1

#ifdef __EVSCI_C__
int EdgeLevelSave   = SAVE_NOT_VALID;
int IrqEnableSave   = SAVE_NOT_VALID;
int OriginalMode    = SAVE_NOT_VALID;   /*  original ACPI/legacy mode   */

#else
extern  int EdgeLevelSave;
extern  int IrqEnableSave; /*  original SCI config */
extern  int OriginalMode;  /*  stores the original ACPI/legacy mode    */
#endif

/* Prototypes */

int 
InitializeSCI (int ProgramSCI);

int 
VerifyAcpiTablesPresent (char *TestName);

int 
InstallSCIHandlerXferToACPI (char *TestName, int Flags);

int 
UninstallSCIHandlerXferToLegacy (void);


#endif  /*  __EVSCI_H__   */
