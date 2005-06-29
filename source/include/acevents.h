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
 | $Revision: 1.1 $
 | $Date: 2005/06/29 19:31:07 $
 | $Log: acevents.h,v $
 | Revision 1.1  2005/06/29 19:31:07  aystarik
 |
 |
 | 
 | date	99.02.12.17.57.00;	author rmosgrov;	state Exp;
 |
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
// Added iVerifyAcpiTablesPresent() function and NO_ACPI_TABLES_MASK
// error code.
// 
//    Rev 1.1   13 Aug 1998 17:27:34   jkreinem
// Added SAVE_NOT_VALID definition for interrupt configuration.
// 
//    Rev 1.0   12 Aug 1998 15:54:32   jkreinem
// Initial revision.
 |__________________________________________________________________________

*/

#ifndef __SCILAST_H__
#define __SCILAST_H__


/*  iInstallSCIHandlerXferToACPI() iFlags bitmask options   */
#define ACPI_TABLES_REQUIRED                1
#define HW_OVERRIDE_SUPPORTED           2
#define PROGRAM_SCI_LEVEL_SENSITIVITY   4
#define DISABLE_KNOWN_EVENTS                8

/*  iErrorMask mask bits    */
#define NO_ACPI_TABLES_MASK         1
#define NO_ACPI_TRANSITION_MASK     2
#define SCI_LEVEL_INT_MASK          4
#define NO_SCI_HANDLER_MASK         8
#define NO_LEGACY_TRANSITION_MASK   0x10

#define SAVE_NOT_VALID      -1

#ifdef __SCILAST_C__
int iEdgeLevelSave=SAVE_NOT_VALID, iIrqEnableSave=SAVE_NOT_VALID;
int iOriginalMode=SAVE_NOT_VALID;           /*  original ACPI/legacy mode   */
#else
extern  int iEdgeLevelSave, iIrqEnableSave; /*  original SCI config */
extern  int iOriginalMode;  /*  stores the original ACPI/legacy mode    */
#endif


/**************************************************************************
 *  FUNCTION:       int iInitializeSCI
 *
 *  PARAMETERS:
 *      iProgramSCI --  TRUE if SCI can be reprogrammed to level sensitivity
 *                          FALSE if current SCI sensitivity must be preserved
 *
 *  RETURN:         0 if successful; non-zero if failure encountered
 *
 *  DESCRIPTION:    iInitializeSCI() ensures that the system control
 *                      interrupt (SCI) is properly configured.
 *                      If successful, return 0. Otherwise, return non-zero.
 *************************************************************************/
int iInitializeSCI (int iProgramSCI);


/**************************************************************************
 *  FUNCTION:       int iVerifyAcpiTablesPresent
 *
 *  PARAMETERS:
 *      pcTestName  --  pointer to test name string for log messages
 *
 *  RETURN:
 *      0               if tables are present
 *      non-zero        if ACPI tables can NOT be located
 *
 *  DESCRIPTION:    iVerifyAcpiTablesPresent() ensures that the current
 *                      environment contains ACPI (namespace) tables from
 *                      either the BIOS or from an input file.
 *                      Return 0 if tables are present; non-zero otherwise.
 *************************************************************************/
int iVerifyAcpiTablesPresent (char *pcTestName);


/**************************************************************************
 *  FUNCTION:       int iInstallSCIHandlerXferToACPI
 *
 *  PARAMETERS:
 *      pcTestName  --  pointer to test name string for log messages
 *      iFlags      --  flag bitmask (logical OR) to specify:
 *                          ACPI_TABLES_REQUIRED, HW_OVERRIDE_SUPPORTED,
 *                          PROGRAM_SCI_LEVEL_SENSITIVITY, DISABLE_KNOWN_EVENTS
 *
 *  RETURN:         0 if successful; non-zero if failure encountered
 *
 *  DESCRIPTION:    iInstallSCIHandlerXferToACPI() ensures that the system
 *                      control interrupt (SCI) is properly configured, disables
 *                      SCI event sources, installs the SCI handler, and
 *                      transfers the system into ACPI mode.
 *                      If successful, return 0. Otherwise, return non-zero.
 *************************************************************************/
int iInstallSCIHandlerXferToACPI (char *pcTestName, int iFlags);


/**************************************************************************
 *  FUNCTION:       int iUninstallSCIHandlerXferToLegacy
 *
 *  PARAMETERS:     none
 *
 *  RETURN:         0 if successful; non-zero if failure encountered
 *
 *  DESCRIPTION:    iUninstallSCIHandlerXferToLegacy() returns the system
 *                      to original ACPI/legacy mode, unloads the SCI handler,
 *                      and restores the SCI to its original configuration.
 *                      If successful, return 0. Otherwise, return non-zero.
 *************************************************************************/
int iUninstallSCIHandlerXferToLegacy ();

#endif  /*  __SCILAST_H__   */
