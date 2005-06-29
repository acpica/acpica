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


/* identifier strings for fixed events */

#define TMR_FIXED_EVENT         "TMR_FIXED_EVENT"
#define NOT_USED_EVENT          "UNHANDLED_SCI"
#define GBL_FIXED_EVENT         "GBL_FIXED_EVENT"
#define PWR_BTN_FIXED_EVENT     "PWR_BTN_FIXED_EVENT"
#define SLP_BTN_FIXED_EVENT     "SLP_BTN_FIXED_EVENT"
#define RTC_FIXED_EVENT         "RTC_FIXED_EVENT"

/* event index for types of events */

enum 
{
    TMR_EVENT,
    NOT_USED,
    /* 
     * There's no bus master event so index 1 is used for IRQ's that are not
     * handled by the SCI handler 
     */
    GBL_EVENT, 
    PWR_BTN_EVENT, 
    SLP_BTN_EVENT, 
    RTC_EVENT, 
    GENERAL_EVENT
};

#define DISABLE 0
#define STATUS  0
#define ENABLE  1

/* 
 * Use the four macros below + the function iAcpiEventClearStatusBit for
 * accessing and manipulating status/enable bits for various events.
 *  
 * IMPORTANT!! SCI handler must be installed or the enable bit will not be
 * modified. 
 */
#define AcpiEventEnableEvent(name)                      AcpiEventEnableDisableEvent(name, ENABLE)
#define AcpiEventDisableEvent(name)                     AcpiEventEnableDisableEvent(name, DISABLE)
#define AcpiGenEventEnableEvent(name, offset)           AcpiEventEnableDisableEvent(name, ENABLE, offset)
#define AcpiGenEventDisableEvent(name, offset)          AcpiEventEnableDisableEvent(name, DISABLE, offset)
#define AcpiEventReadEnableBit(name, buf)               AcpiEventReadStatusEnableBit(name, ENABLE, buf)
#define AcpiEventReadStatusBit(name, buf)               AcpiEventReadStatusEnableBit(name, STATUS, buf)
#define AcpiGenEventReadEnableBit(name, buf, offset)    AcpiEventReadStatusEnableBit(name, ENABLE, buf, offset)
#define AcpiGenEventReadStatusBit(name, buf, offset)    AcpiEventReadStatusEnableBit(name, STATUS, buf, offset)

/* 
 * elements correspond to counts for
 * TMR, GBL, PWR_BTN, SLP_BTN, and RTC
 * respectively.  These counts are modified
 * by the ACPI interrupt handler... 
 */

extern volatile UINT32 EventCount[];   


/* Prototypes */

INT32
AcpiEventClearStatusBit (
    char *          EventName, ...);

INT32
AcpiEventEnableDisableEvent (
    char *          EventName, 
    INT32           Action, ...);

INT32
AcpiEventReadStatusEnableBit (
    char *          EventName, 
    INT32           StatusOrEnable, 
    BOOLEAN *       OutBit, ...);

UINT32 
InstallSciHandler (
    void);

void 
UninstallSciHandler (
    void);

UINT32 
SciCount (
    char *          EventName);

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
UninstallSCIHandlerXferToLegacy (
    void);

UINT32
InstallInterruptHandler (
    UINT32          InterruptNumber,
    INT32           (* Isr)(void),
    UINT32          *ExceptPtr);

INT32
RemoveInterruptHandler (UINT32 Handle);



#endif  /*  __EVENTS_H__   */
