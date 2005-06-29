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
 | FILENAME: acpirio.c - Read/write access functions for the various ACPI
 |                                  control and status registers.
 |__________________________________________________________________________
 |
 | $Revision: 1.2 $
 | $Date: 2005/06/29 16:54:01 $
 | $Log: hwregs.c,v $
 | Revision 1.2  2005/06/29 16:54:01  aystarik
 | Detabified.
 |
 | 
 | date	99.01.12.00.07.00;	author grsmith1;	state Exp;
 |
 * 
 * 2     1/11/99 4:07p Grsmith1
 * Detabified.
 * 
 * 1     1/11/99 2:07p Rmoore1
 * Hardware Specific Modules
// 
//    Rev 1.18   15 Jan 1998 14:40:50   kdbranno
// Added function headers and comments
// 
//    Rev 1.17   24 Dec 1997 14:10:12   kdbranno
// Quieted chatter from iC386
// 
//    Rev 1.16   11 Dec 1997 09:09:34   calingle
// added code to vClearAllAcpiChipsetStatusBits to clear bits
// in GPE Block 0 and (if it exists) GPE Block 1.
// 
//    Rev 1.15   08 Dec 1997 17:08:20   kdbranno
// Added #include "acpipriv.h"
// 
//    Rev 1.14   05 Dec 1997 09:36:36   kdbranno
// Fixed up so it compiles with clean with iRMX.
// 
//    Rev 1.13   26 Nov 1997 14:47:18   nburke
// Added a conditional vFunctionHello call to every function in the file.
// 
//    Rev 1.12   26 Nov 1997 11:00:54   kdbranno
// Changed references to ACPI_REGISTER_READ and ACPI_REGISTER_WRITE to ACPI_READ and ACPI_WRITE.
// Added function vClearAllAcpiChipsetStatusBits.
// 
//    Rev 1.11   25 Sep 1997 11:14:44   calingle
// Added support for general purpose event register read and 
// write for GPE1.
// 
//    Rev 1.10   25 Sep 1997 08:56:28   calingle
// Fixed a possible precedence bug in GPE0_EN_BLOCK case
// statement.
// 
//    Rev 1.9   24 Sep 1997 09:15:52   calingle
// Updated dAcpiRegisterIO () to support General Purpose Events by
// adding cases to the switch statemene for GPE0 Enable and 
// GPE0 Status blocks.  This only allows for the GPE0 register since
// the ACPI spec is not clear on how to tell which Register a given
// General Purpose Device is attached.  Since the PIIX4 and PIIX6 are
// only supporting 1 register this is low risk for now.  Once it is
// determined how to tell where a device is attached it should be
// easy to add the needed code to support this update.
// 
//    Rev 1.8   03 Sep 1997 14:51:02   kdbranno
// Changed most register references from 16 bit to 32 bit since that's what the
// ACPI specification defines.
// 
//    Rev 1.7   16 Jul 1997 16:59:18   kdbranno
// casted enum to int for brain dead iC386 tool.
// 
//    Rev 1.6   15 Jul 1997 10:14:12   kdbranno
// Changed &= to |= at one point in iAcpiReadWriteRegister
// 
//    Rev 1.5   30 Jun 1997 12:43:08   kdbranno
// Turned off stack checking for DOS (there isn't any anyway for iRMX).  Fixed a
// problem where the status bits were being inadvertently cleared by writing 1's
// to preserve bits that already had 1's in them.  Writing a 1 clears a status
// bit.  The code was changed to write 0's to all bits except for the requested
// bit.
// 
//    Rev 1.4   09 Jun 1997 13:14:26   kdbranno
// changed casting of first parameter to vOut16.  Now casts correctly.
//
//    Rev 1.3   15 May 1997 11:18:56   kdbranno
// Fixed bug in wAcpiRegisterIO ('=' became '==').  Changed inword/outword to
// wIn16/vOut16.
//
//    Rev 1.2   16 Apr 1997 19:35:48   kdbranno
// Redesigned and completed implementation of ACPI register access functions
//
//    Rev 1.1   16 Apr 1997 15:08:28   kdbranno
// Changed include brackets to quotes for .h files from ACPILIB
//
//    Rev 1.0   Apr 14 1997 14:10:58   kdbranno
// Initial revision.
 |__________________________________________________________________________

*/

#define __ACPIRIO_C__
#include <bu.h>
#include <stdarg.h>
#include "acpirio.h"
#include "acpitbls.h"
#include "acpipriv.h"

#ifndef RMX
#pragma check_stack (off)
#endif

/******************************************************************************
 * FUNCTION:        int iGetBitShift
 *
 * PARAMETERS:      DWORD dMask - input mask to determine bit shift from.  Must
 *                          have at least 1 bit set.
 *
 * RETURN:          bit location of the lsb of the mask
 *
 * DESCRIPTION: returns the bit number for the low order bit that's set.
 *
 ******************************************************************************/
int
iGetBitShift (DWORD dMask)
{
    int iShift;

    #ifdef FUNCTION_HELLO
       vFunctionHello ("acpirio.c", "iGetBitShift");
    #endif

    for (iShift = 0; ((dMask >> iShift) & 1) == 0; iShift++);
    return (iShift);
}

/******************************************************************************
 * FUNCTION:        dAcpiRegisterIO (int iReadWrite, int iRegisterId, ...)
 *
 * PARAMETERS:      int iReadWrite - Either ACPI_READ or ACPI_WRITE.
 *                      int iRegisterId - index of ACPI register to access
 *                      DWORD dValue - (only used on write) value to write to the
 *                          register.  This value is shifted all the way right.
 *
 * RETURN:          value written to or read from specified register.  This value
 *                          is shifted all the way right.
 *
 * DESCRIPTION: Generic ACPI register read/write function.
 *
 ******************************************************************************/
DWORD
dAcpiRegisterIO (int iReadWrite, int iRegisterId, ... /* DWORD dValue */)
{
    DWORD dRegisterValue, dMask, dValue;
    DWORD   dGpeReg=0;

    #ifdef FUNCTION_HELLO
       vFunctionHello ("acpirio.c", "dAcpiRegisterIO");
    #endif
    
    if (iReadWrite == ACPI_WRITE)
    {
        va_list marker;

        va_start (marker, iRegisterId);
        dValue = va_arg (marker, int);
        va_end (marker);
    }

    switch (iRegisterId & REGISTER_BLOCK_MASK)
    {
        case PM1_EVT:
            if (iRegisterId < (int) TMR_EN)
            {   /* status register */
                dRegisterValue = (DWORD) wIn16 ((WORD)pFACP->dPm1aEvtBlk);
                if (pFACP->dPm1bEvtBlk)
                    dRegisterValue |= (DWORD) wIn16 ((WORD)pFACP->dPm1bEvtBlk);
                switch (iRegisterId)
                {
                    case TMR_STS:
                        dMask = TMR_STS_MASK;
                        break;
                    case BM_STS:
                        dMask = BM_STS_MASK;
                        break;
                    case GBL_STS:
                        dMask = GBL_STS_MASK;
                        break;
                    case PWRBTN_STS:
                        dMask = PWRBTN_STS_MASK;
                        break;
                    case SLPBTN_STS:
                        dMask = SLPBTN_STS_MASK;
                        break;
                    case RTC_STS:
                        dMask = RTC_STS_MASK;
                        break;
                    case WAK_STS:
                        dMask = WAK_STS_MASK;
                        break;
                    default:
                        dMask = 0;
                        break;
                }
                if (iReadWrite == ACPI_WRITE)
                {
                    /* status registers are different from the rest.  Clear by writing 1, writing 0
                        has no effect.  So, the only relevent information is the single bit we're
                        interested in, all others should be written as 0 so they will be left
                        unchanged */
                    dValue <<= iGetBitShift (dMask);
                    dValue &= dMask;
                    if (dValue)
                    {
#if 0
                        printf_bu ("\nAbout to write %04X to %04X", (WORD) dValue, (WORD)pFACP->dPm1aEvtBlk);
#endif
                        vOut16 ((WORD)pFACP->dPm1aEvtBlk, (WORD) dValue);
                        if (pFACP->dPm1bEvtBlk)
                            vOut16 ((WORD)pFACP->dPm1bEvtBlk, (WORD) dValue);
                        dRegisterValue = 0;
                    }
                }
            }
            else
            {   /* enable register */
                dRegisterValue = (DWORD) wIn16 ((WORD)(pFACP->dPm1aEvtBlk + pFACP->bPm1EvtLen / 2));
                if (pFACP->dPm1bEvtBlk)
                    dRegisterValue |= (DWORD) wIn16 ((WORD)(pFACP->dPm1bEvtBlk + pFACP->bPm1EvtLen / 2));
                switch (iRegisterId)
                {
                    case TMR_EN:
                        dMask = TMR_EN_MASK;
                        break;
                    case GBL_EN:
                        dMask = GBL_EN_MASK;
                        break;
                    case PWRBTN_EN:
                        dMask = PWRBTN_EN_MASK;
                        break;
                    case SLPBTN_EN:
                        dMask = SLPBTN_EN_MASK;
                        break;
                    case RTC_EN:
                        dMask = RTC_EN_MASK;
                        break;
                    default:
                        dMask = 0;
                        break;
                }
                if (iReadWrite == ACPI_WRITE)
                {
                    dRegisterValue &= ~dMask;
                    dValue <<= iGetBitShift (dMask);
                    dValue &= dMask;
                    dRegisterValue |= dValue;
#if 0
                    printf_bu ("\nAbout to write %04X to %04X", (WORD) dRegisterValue, (WORD)(pFACP->dPm1aEvtBlk + pFACP->bPm1EvtLen / 2));
#endif
                    vOut16 ((WORD)(pFACP->dPm1aEvtBlk + pFACP->bPm1EvtLen / 2), (WORD) dRegisterValue);
                    if (pFACP->dPm1bEvtBlk)
                        vOut16 ((WORD)(pFACP->dPm1bEvtBlk + pFACP->bPm1EvtLen / 2), (WORD) dRegisterValue);
                }
            }
            break;
        case PM1_CONTROL:
            dRegisterValue = 0;
            if (iRegisterId != (int)SLP_TYPb)   /* SLP_TYPx registers are written differently
                                                                than any other control registers with
                                                                respect to A and B registers.  The value
                                                                for A may be different than the value for
                                                                B */
                dRegisterValue = (DWORD) wIn16 ((WORD)pFACP->dPm1aCntBlk);
            if (pFACP->dPm1bEvtBlk && iRegisterId != (int)SLP_TYPa)
                dRegisterValue |= (DWORD) wIn16 ((WORD)pFACP->dPm1bCntBlk);
            switch (iRegisterId)
            {
                case SCI_EN:
                    dMask = SCI_EN_MASK;
                    break;
                case BM_RLD:
                    dMask = BM_RLD_MASK;
                    break;
                case GBL_RLS:
                    dMask = GBL_RLS_MASK;
                    break;
                case SLP_TYPa:
                case SLP_TYPb:
                    dMask = SLP_TYPx_MASK;
                    break;
                case SLP_EN:
                    dMask = SLP_EN_MASK;
                    break;
                default:
                    dMask = 0;
                    break;
            }
            if (iReadWrite == ACPI_WRITE)
            {
                dRegisterValue &= ~dMask;
                dValue <<= iGetBitShift (dMask);
                dValue &= dMask;
                dRegisterValue |= dValue;
                /* SLP_TYPx registers are written differently
                    than any other control registers with
                    respect to A and B registers.  The value
                    for A may be different than the value for   B
                */
                if (iRegisterId != (int)SLP_TYPb)
                {
                    if (dMask == SLP_EN_MASK)
                        disable();  /* disable interrupts */
                    vOut16 ((WORD)pFACP->dPm1aCntBlk, (WORD) dRegisterValue);
                    if (dMask == SLP_EN_MASK)
                    /* enable interrupts, the SCI handler is likely going to be invoked as
                        soon as interrupts are enabled, since gpe's and most fixed resume
                        events also generate SCI's. */
                        enable();
                }
                    
                if (pFACP->dPm1bEvtBlk && iRegisterId != (int)SLP_TYPa)
                    vOut16 ((WORD)pFACP->dPm1bCntBlk, (WORD) dRegisterValue);
            }
            break;
        case PM2_CONTROL:
            dRegisterValue = (DWORD) wIn16 ((WORD)pFACP->dPm2CntBlk);
            switch (iRegisterId)
            {
                case ARB_DIS:
                    dMask = ARB_DIS_MASK;
                    break;
                default:
                    dMask = 0;
                    break;
            }
            if (iReadWrite == ACPI_WRITE)
            {
                dRegisterValue &= ~dMask;
                dValue <<= iGetBitShift (dMask);
                dValue &= dMask;
                dRegisterValue |= dValue;
#if 0
                printf_bu ("\nAbout to write %04X to %04X", (WORD) dRegisterValue, (WORD)pFACP->dPm2CntBlk);
#endif
                vOut16 ((WORD)pFACP->dPm2CntBlk, (WORD) dRegisterValue);
            }
            break;
        case PM_TIMER:
            dRegisterValue = dIn32 ((WORD)pFACP->dPmTmrBlk);
            dMask = 0xFFFFFFFF;
            break;
        case GPE1_EN_BLOCK:
            dGpeReg = (pFACP->dGpe1Blk + (DWORD)pFACP->bGpe1Base) + (dGpeReg + 
                        ((DWORD)((pFACP->bGpe1BlkLen)/2)));
        case GPE1_STS_BLOCK:
            if (!dGpeReg)
                dGpeReg = (pFACP->dGpe1Blk + (DWORD)pFACP->bGpe1Base);
        case GPE0_EN_BLOCK:
            if (!dGpeReg)
                dGpeReg = pFACP->dGpe0Blk + ((DWORD)((pFACP->bGpe0BlkLen)/2));
        
        case GPE0_STS_BLOCK:
            if (!dGpeReg)
                dGpeReg = pFACP->dGpe0Blk;
            /* Determine the bit to be accessed */
            dMask = (((DWORD) iRegisterId) & BIT_IN_REGISTER_MASK);
            dMask = 1 << (dMask-1);
            /* The base address of the GPE 0 Register Block */
            /* Plus 1/2 the length of the GPE 0 Register Block */
            /* The enable register is the register following the Status Register */
            /* and each register is defined as 1/2 of the total Register Block */
            
            /* This sets the bit within wEnableBit that needs to be written to */
            /* the register indicated in dMask to a 1, all others are 0 */
            
            if (dMask > LOW_BYTE)
            {
                /* Shift the value 1 byte to the right and add 1 to the register */
                dMask >>= ONE_BYTE;
                dGpeReg++;
            }
            
            /* Now get the current Enable Bits in the selected Reg */
            dRegisterValue = (DWORD) bIn8 ((WORD)dGpeReg);
            
            if (iReadWrite == ACPI_WRITE)
            {               
                     dRegisterValue &= ~dMask;
                     dValue <<= iGetBitShift (dMask);
                     dValue &= dMask;
                     dRegisterValue |= dValue;
                
                /* This write will put the iAction state into the General Purpose */
                /* Enable Register indexed by the value in dMask */
#if 0
                printf_bu ("\nAbout to write %04X to %04X", (WORD) dRegisterValue, (WORD)dGpeReg);
#endif
                vOut8 ((WORD)dGpeReg, (BYTE) dRegisterValue);
                dRegisterValue = (DWORD) bIn8 ((WORD)dGpeReg);          
            }
            break;
        case PROCESSOR_BLOCK:
        default:
            dMask = 0;
            break;
    }

    dRegisterValue &= dMask;
    dRegisterValue >>= iGetBitShift (dMask);

    return (dRegisterValue);
}
#ifndef RMX
#pragma check_stack ()
#endif

/******************************************************************************
 * FUNCTION:        void vClearAllAcpiChipsetStatusBits (void)
 *
 * PARAMETERS:      none
 *
 * RETURN:          none
 *
 * DESCRIPTION: Clears all fixed and general purpose status bits
 *
 ******************************************************************************/
void vClearAllAcpiChipsetStatusBits (void)
{
    WORD    wGpeLength;
    WORD    wIndex;
    #ifdef FUNCTION_HELLO
       vFunctionHello ("acpirio.c", "vClearAllAcpiChipsetStatusBits");
    #endif

#if 0
    printf_bu ("\nAbout to write %04X to %04X", ALL_STS_BITS, (WORD)pFACP->dPm1aEvtBlk);
#endif
    vOut16 ((WORD)pFACP->dPm1aEvtBlk, (WORD)ALL_FIXED_STS_BITS);
    if (pFACP->dPm1bEvtBlk)
        vOut16 ((WORD)pFACP->dPm1bEvtBlk, (WORD)ALL_FIXED_STS_BITS);
    /* now clear GPE Bits */
    if (pFACP->bGpe0BlkLen)
    {
        wGpeLength = pFACP->bGpe0BlkLen / 2;
        for (wIndex = 0; wIndex < wGpeLength; wIndex++)
            vOut8 ((WORD)(pFACP->dGpe0Blk + wIndex), (BYTE)0xff);
    }
    if (pFACP->bGpe1BlkLen)
    {
        wGpeLength = pFACP->bGpe1BlkLen / 2;
        for (wIndex = 0; wIndex < wGpeLength; wIndex++)
            vOut8 ((WORD)(pFACP->dGpe1Blk + wIndex), (BYTE)0xff);
    }
}   
