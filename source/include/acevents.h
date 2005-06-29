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
 | FILENAME: events.h - System Control Interrupt configuration and
 |                      legacy to ACPI mode state transition functions
 |__________________________________________________________________________
 |
 | $Revision: 1.6 $
 | $Date: 2005/06/29 19:31:12 $
 | $Log: acevents.h,v $
 | Revision 1.6  2005/06/29 19:31:12  aystarik
 |
 |
 | 
 | date	99.04.06.20.41.00;	author rmoore1;	state Exp;
 |
 * 
 * 6     4/06/99 1:41p Rmoore1
 * 
 * 5     3/31/99 2:30p Rmoore1
 * Integrated with 03/99 OPSD code
 * 
 * 4     3/09/99 4:04p Rmoore1
 * 16/32/64-bit common data types
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

#ifndef __EVENTS_H__
#define __EVENTS_H__

/* Interrupt handler return values */

#define INTERRUPT_HANDLED               0x01
#define INTERRUPT_NOT_HANDLED           0x02
#define INTERRUPT_ERROR                 0x03

/*  InstallSCIHandlerXferToACPI() Flags bitmask options   */

#define ACPI_TABLES_REQUIRED            0x01
#define HW_OVERRIDE_SUPPORTED           0x02
#define PROGRAM_SCI_LEVEL_SENSITIVITY   0x04
#define DISABLE_KNOWN_EVENTS            0x08
#define	LOAD_ACPI_NAMESPACE             0x10


/*  iErrorMask mask bits    */

#define NO_ACPI_TABLES_MASK             0x01
#define NO_ACPI_TRANSITION_MASK         0x02
#define SCI_LEVEL_INT_MASK              0x04
#define NO_SCI_HANDLER_MASK             0x08
#define NO_LEGACY_TRANSITION_MASK       0x10
#define	UNABLE_TO_LOAD_NAMESPACE        0x20
#define	SCI_DISABLED                    0x40

#define SAVE_NOT_VALID                  -1

#ifdef __EVSCI_C__
INT32 EdgeLevelSave   = SAVE_NOT_VALID;
INT32 IrqEnableSave   = SAVE_NOT_VALID;
INT32 OriginalMode    = SAVE_NOT_VALID;   /*  original ACPI/legacy mode   */

#else
extern  INT32 EdgeLevelSave;
extern  INT32 IrqEnableSave; /*  original SCI config */
extern  INT32 OriginalMode;  /*  stores the original ACPI/legacy mode    */
#endif

/* Prototypes */

INT32 
InitializeSCI (
    INT32           ProgramSCI);

INT32 
VerifyAcpiTablesPresent (
    char *          TestName);

INT32 
InstallSCIHandlerXferToACPI (
    char *          TestName, 
    INT32           Flags);

INT32 
UninstallSCIHandlerXferToLegacy (void);

UINT32
InstallInterruptHandler (
    UINT32          InterruptNumber,
    INT32           (* Isr)(void),
    UINT32          *ExceptPtr);

INT32
RemoveInterruptHandler (UINT32 Handle);



#endif  /*  __EVENTS_H__   */
