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
 | Read/write access functions for the various ACPI
 | control and status registers.
 |__________________________________________________________________________
 |
 | $Revision: 1.8 $
 | $Date: 2005/06/29 16:54:08 $
 | $Log: hwregs.c,v $
 | Revision 1.8  2005/06/29 16:54:08  aystarik
 | 16/32/64-bit common data types
 |
 | 
 | date	99.03.10.00.05.00;	author rmoore1;	state Exp;
 |
 * 
 * 8     3/09/99 4:05p Rmoore1
 * 16/32/64-bit common data types
 * 
 * 7     2/16/99 9:35a Rmosgrov
 * Anti-Polish Complete - Compiles
 * 
 * 6     2/11/99 5:51p Rmosgrov
 * Anti-Polish
 * 
 * 5     1/20/99 9:38a Rmoore1
 * Major Cleanup
 * 
 * 4     1/13/99 2:53p Rmoore1
 * includes acpiasm.h
 * 
 * 3     1/13/99 2:39p Grsmith1
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
// added code to ClearAllAcpiChipsetStatusBits to clear bits
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
// Added function ClearAllAcpiChipsetStatusBits.
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
// Updated AcpiRegisterIO () to support General Purpose Events by
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
// casted enum to INT32 for brain dead iC386 tool.
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
// changed casting of first parameter to OsdOut16.  Now casts correctly.
//
//    Rev 1.3   15 May 1997 11:18:56   kdbranno
// Fixed bug in wAcpiRegisterIO ('=' became '==').  Changed inword/outword to
// OsdIn16/OsdOut16.
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

#define __DVREGS_C__
#define _THIS_MODULE    "dvregs.c"

#include <bu.h>
#include <stdarg.h>
#include "acpirio.h"
#include "acpitbls.h"
#include "acpipriv.h"
#include "acpiasm.h"
#include "acpiosd.h"

#ifndef RMX
#pragma check_stack (off)
#endif


/******************************************************************************
 *
 * FUNCTION:    GetBitShift
 *
 * PARAMETERS:  UINT32   Mask     - input mask to determine bit shift from.  Must
 *                                  have at least 1 bit set.
 *
 * RETURN:      bit location of the lsb of the mask
 *
 * DESCRIPTION: returns the bit number for the low order bit that's set.
 *
 ******************************************************************************/

INT32
GetBitShift (UINT32 Mask)
{
    INT32             Shift;


    FUNCTION_TRACE ("GetBitShift");


    for (Shift = 0; ((Mask >> Shift) & 1) == 0; Shift++)
    { ; }

    return (Shift);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiRegisterIO
 *
 * PARAMETERS:  INT32   ReadWrite      - Either ACPI_READ or ACPI_WRITE.
 *              INT32   RegisterId     - index of ACPI register to access
 *              UINT32  Value          - (only used on write) value to write to the
 *                                       register.  This value is shifted all the way right.
 *
 * RETURN:      value written to or read from specified register.  This value
 *              is shifted all the way right.
 *
 * DESCRIPTION: Generic ACPI register read/write function.
 *
 ******************************************************************************/

UINT32
AcpiRegisterIO (INT32 ReadWrite, INT32 RegisterId, ... /* UINT32 Value */)
{
    UINT32          RegisterValue;
    UINT32          Mask;
    UINT32          Value;
    UINT32          GpeReg = 0;


    FUNCTION_TRACE ("AcpiRegisterIO");

    
    if (ReadWrite == ACPI_WRITE)
    {
        va_list         marker;

        va_start (marker, RegisterId);
        Value = va_arg (marker, INT32);
        va_end (marker);
    }

    switch (RegisterId & REGISTER_BLOCK_MASK)
    {
        case PM1_EVT:
            if (RegisterId < (INT32) TMR_EN)
            {   
                /* status register */
                
                RegisterValue = (UINT32) OsdIn16 ((UINT16) FACP->Pm1aEvtBlk);
                
                if (FACP->Pm1bEvtBlk)
                {
                    RegisterValue |= (UINT32) OsdIn16 ((UINT16) FACP->Pm1bEvtBlk);
                }

                switch (RegisterId)
                {
                    case TMR_STS:
                        Mask = TMR_STS_MASK;
                        break;
                    
                    case BM_STS:
                        Mask = BM_STS_MASK;
                        break;
                    
                    case GBL_STS:
                        Mask = GBL_STS_MASK;
                        break;
                    
                    case PWRBTN_STS:
                        Mask = PWRBTN_STS_MASK;
                        break;
                    
                    case SLPBTN_STS:
                        Mask = SLPBTN_STS_MASK;
                        break;
                    
                    case RTC_STS:
                        Mask = RTC_STS_MASK;
                        break;
                    
                    case WAK_STS:
                        Mask = WAK_STS_MASK;
                        break;
                    
                    default:
                        Mask = 0;
                        break;
                }
                
                if (ReadWrite == ACPI_WRITE)
                {
                    /* 
                     * status registers are different from the rest.  Clear by writing 1, writing 0
                     * has no effect.  So, the only relevent information is the single bit we're
                     * interested in, all others should be written as 0 so they will be left
                     * unchanged 
                     */
                    
                    Value <<= GetBitShift (Mask);
                    Value &= Mask;
                    
                    if (Value)
                    {
#if 0
                        printf_bu ("\nAbout to write %04X to %04X", (UINT16) Value, 
                                    (UINT16) FACP->Pm1aEvtBlk);
#endif
                        OsdOut16 ((UINT16) FACP->Pm1aEvtBlk, (UINT16) Value);
                        
                        if (FACP->Pm1bEvtBlk)
                        {
                            OsdOut16 ((UINT16) FACP->Pm1bEvtBlk, (UINT16) Value);
                        }
                        
                        RegisterValue = 0;
                    }
                }
            }
            
            else
            {   
                /* enable register */
                
                RegisterValue = (UINT32) OsdIn16 ((UINT16) (FACP->Pm1aEvtBlk + FACP->Pm1EvtLen / 2));
                
                if (FACP->Pm1bEvtBlk)
                {
                    RegisterValue |= (UINT32) OsdIn16 ((UINT16) (FACP->Pm1bEvtBlk + FACP->Pm1EvtLen / 2));
                }

                switch (RegisterId)
                {
                    case TMR_EN:
                        Mask = TMR_EN_MASK;
                        break;
                    
                    case GBL_EN:
                        Mask = GBL_EN_MASK;
                        break;
                    
                    case PWRBTN_EN:
                        Mask = PWRBTN_EN_MASK;
                        break;
                    
                    case SLPBTN_EN:
                        Mask = SLPBTN_EN_MASK;
                        break;
                    
                    case RTC_EN:
                        Mask = RTC_EN_MASK;
                        break;
                    
                    default:
                        Mask = 0;
                        break;
                }
                
                if (ReadWrite == ACPI_WRITE)
                {
                    RegisterValue  &= ~Mask;
                    Value          <<= GetBitShift (Mask);
                    Value          &= Mask;
                    RegisterValue  |= Value;
#if 0
                    printf_bu ("\nAbout to write %04X to %04X", (UINT16) RegisterValue, 
                                (UINT16) (FACP->Pm1aEvtBlk + FACP->Pm1EvtLen / 2));
#endif
                    OsdOut16 ((UINT16) (FACP->Pm1aEvtBlk + FACP->Pm1EvtLen / 2), 
                            (UINT16) RegisterValue);
                    
                    if (FACP->Pm1bEvtBlk)
                    {
                        OsdOut16 ((UINT16)(FACP->Pm1bEvtBlk + FACP->Pm1EvtLen / 2), 
                                (UINT16) RegisterValue);
                    }
                }
            }
            break;
        
        case PM1_CONTROL:
            RegisterValue = 0;
            
            if (RegisterId != (INT32) SLP_TYPb)   
            {
                /* 
                 * SLP_TYPx registers are written differently
                 * than any other control registers with
                 * respect to A and B registers.  The value
                 * for A may be different than the value for B 
                 */

                RegisterValue = (UINT32) OsdIn16 ((UINT16)  FACP->Pm1aCntBlk);
            }

            if (FACP->Pm1bEvtBlk && RegisterId != (INT32)SLP_TYPa)
            {
                RegisterValue |= (UINT32) OsdIn16 ((UINT16) FACP->Pm1bCntBlk);
            }

            switch (RegisterId)
            {
                case SCI_EN:
                    Mask = SCI_EN_MASK;
                    break;
                
                case BM_RLD:
                    Mask = BM_RLD_MASK;
                    break;
                
                case GBL_RLS:
                    Mask = GBL_RLS_MASK;
                    break;
                
                case SLP_TYPa:
                case SLP_TYPb:
                    Mask = SLP_TYPx_MASK;
                    break;
                
                case SLP_EN:
                    Mask = SLP_EN_MASK;
                    break;
                default:
                
                    Mask = 0;
                    break;
            }
            
            if (ReadWrite == ACPI_WRITE)
            {
                RegisterValue  &= ~Mask;
                Value          <<= GetBitShift (Mask);
                Value          &= Mask;
                RegisterValue  |= Value;
                
                /* 
                 * SLP_TYPx registers are written differently
                 * than any other control registers with
                 * respect to A and B registers.  The value
                 * for A may be different than the value for B
                 */
                
                if (RegisterId != (INT32) SLP_TYPb)
                {
                    if (Mask == SLP_EN_MASK)
                    {
                        disable();  /* disable interrupts */
                    }

                    OsdOut16 ((UINT16) FACP->Pm1aCntBlk, (UINT16) RegisterValue);
                    
                    if (Mask == SLP_EN_MASK)
                    {
                        /* 
                         * enable interrupts, the SCI handler is likely going to be invoked as
                         * soon as interrupts are enabled, since gpe's and most fixed resume
                         * events also generate SCI's. 
                         */
                        enable();
                    }
                }
                    
                if (FACP->Pm1bEvtBlk && RegisterId != (INT32) SLP_TYPa)
                {
                    OsdOut16 ((UINT16) FACP->Pm1bCntBlk, (UINT16) RegisterValue);
                }
            }
            break;
        
        case PM2_CONTROL:
            RegisterValue = (UINT32) OsdIn16 ((UINT16) FACP->Pm2CntBlk);
            
            switch (RegisterId)
            {
                case ARB_DIS:
                    Mask = ARB_DIS_MASK;
                    break;
                
                default:
                    Mask = 0;
                    break;
            }
            
            if (ReadWrite == ACPI_WRITE)
            {
                RegisterValue  &= ~Mask;
                Value          <<= GetBitShift (Mask);
                Value          &= Mask;
                RegisterValue  |= Value;
#if 0
                printf_bu ("\nAbout to write %04X to %04X", (UINT16) RegisterValue, 
                            (UINT16) FACP->Pm2CntBlk);
#endif
                OsdOut16 ((UINT16) FACP->Pm2CntBlk, (UINT16) RegisterValue);
            }
            break;
        
        case PM_TIMER:
            RegisterValue = OsdIn32 ((UINT16) FACP->PmTmrBlk);
            Mask = 0xFFFFFFFF;
            break;
        
        case GPE1_EN_BLOCK:
            GpeReg = (FACP->Gpe1Blk + (UINT32) FACP->Gpe1Base) + (GpeReg + 
                        ((UINT32) ((FACP->Gpe1BlkLen) / 2)));
        
        case GPE1_STS_BLOCK:
            if (!GpeReg)
            {
                GpeReg = (FACP->Gpe1Blk + (UINT32) FACP->Gpe1Base);
            }

        case GPE0_EN_BLOCK:
            if (!GpeReg)
            {
                GpeReg = FACP->Gpe0Blk + ((UINT32) ((FACP->Gpe0BlkLen) / 2));
            }
        
        case GPE0_STS_BLOCK:
            if (!GpeReg)
            {
                GpeReg = FACP->Gpe0Blk;
            }

            /* Determine the bit to be accessed */
            
            Mask = (((UINT32) RegisterId) & BIT_IN_REGISTER_MASK);
            Mask = 1 << (Mask-1);
            
            /* The base address of the GPE 0 Register Block */
            /* Plus 1/2 the length of the GPE 0 Register Block */
            /* The enable register is the register following the Status Register */
            /* and each register is defined as 1/2 of the total Register Block */
            
            /* This sets the bit within wEnableBit that needs to be written to */
            /* the register indicated in Mask to a 1, all others are 0 */
            
            if (Mask > LOW_BYTE)
            {
                /* Shift the value 1 byte to the right and add 1 to the register */
                
                Mask >>= ONE_BYTE;
                GpeReg++;
            }
            
            /* Now get the current Enable Bits in the selected Reg */
            
            RegisterValue = (UINT32) OsdIn8 ((UINT16) GpeReg);
            
            if (ReadWrite == ACPI_WRITE)
            {               
                RegisterValue  &= ~Mask;
                Value          <<= GetBitShift (Mask);
                Value          &= Mask;
                RegisterValue  |= Value;
               
                /* This write will put the iAction state into the General Purpose */
                /* Enable Register indexed by the value in Mask */
#if 0
                printf_bu ("\nAbout to write %04X to %04X", (UINT16) RegisterValue, 
                            (UINT16) GpeReg);
#endif
                OsdOut8 ((UINT16) GpeReg, (UINT8) RegisterValue);
                RegisterValue = (UINT32) OsdIn8 ((UINT16) GpeReg);          
            }
            break;
        
        case PROCESSOR_BLOCK:
        default:
            Mask = 0;
            break;
    }

    RegisterValue &= Mask;
    RegisterValue >>= GetBitShift (Mask);

    return (RegisterValue);
}

#ifndef RMX
#pragma check_stack ()
#endif


/******************************************************************************
 *
 * FUNCTION:    ClearAllAcpiChipsetStatusBits
 *
 * PARAMETERS:  none
 *
 * RETURN:      none
 *
 * DESCRIPTION: Clears all fixed and general purpose status bits
 *
 ******************************************************************************/

void 
ClearAllAcpiChipsetStatusBits (void)
{
    UINT16      GpeLength;
    UINT16      Index;


    FUNCTION_TRACE ("ClearAllAcpiChipsetStatusBits");


#if 0
    printf_bu ("\nAbout to write %04X to %04X", ALL_STS_BITS, (UINT16) FACP->Pm1aEvtBlk);
#endif

    OsdOut16 ((UINT16) FACP->Pm1aEvtBlk, (UINT16) ALL_FIXED_STS_BITS);
    
    if (FACP->Pm1bEvtBlk)
    {
        OsdOut16 ((UINT16) FACP->Pm1bEvtBlk, (UINT16) ALL_FIXED_STS_BITS);
    }

    /* now clear GPE Bits */
    
    if (FACP->Gpe0BlkLen)
    {
        GpeLength = FACP->Gpe0BlkLen / 2;

        for (Index = 0; Index < GpeLength; Index++)
        {
            OsdOut8 ((UINT16) (FACP->Gpe0Blk + Index), (UINT8) 0xff);
        }
    }

    if (FACP->Gpe1BlkLen)
    {
        GpeLength = FACP->Gpe1BlkLen / 2;

        for (Index = 0; Index < GpeLength; Index++)
        {
            OsdOut8 ((UINT16) (FACP->Gpe1Blk + Index), (UINT8) 0xff);
        }
    }
}   
