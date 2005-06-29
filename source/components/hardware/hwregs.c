
/******************************************************************************
 * 
 * Module Name: hwregs - Read/write access functions for the various ACPI
 *                       control and status registers.
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999, Intel Corp.  All rights 
 * reserved.
 *
 * 2. License
 * 
 * 2.1. Intel grants, free of charge, to any person ("Licensee") obtaining a 
 * copy of the source code appearing in this file ("Covered Code") a license 
 * under Intel's copyrights in the base code distributed originally by Intel 
 * ("Original Intel Code") to copy, make derivatives, distribute, use and 
 * display any portion of the Covered Code in any form; and
 *
 * 2.2. Intel grants Licensee a non-exclusive and non-transferable patent 
 * license (without the right to sublicense), under only those claims of Intel
 * patents that are infringed by the Original Intel Code, to make, use, sell, 
 * offer to sell, and import the Covered Code and derivative works thereof 
 * solely to the minimum extent necessary to exercise the above copyright 
 * license, and in no event shall the patent license extend to any additions to
 * or modifications of the Original Intel Code.  No other license or right is 
 * granted directly or by implication, estoppel or otherwise;
 *
 * the above copyright and patent license is granted only if the following 
 * conditions are met:
 *
 * 3. Conditions 
 *
 * 3.1. Redistribution of source code of any substantial portion of the Covered 
 * Code or modification must include the above Copyright Notice, the above 
 * License, this list of Conditions, and the following Disclaimer and Export 
 * Compliance provision.  In addition, Licensee must cause all Covered Code to 
 * which Licensee contributes to contain a file documenting the changes 
 * Licensee made to create that Covered Code and the date of any change.  
 * Licensee must include in that file the documentation of any changes made by
 * any predecessor Licensee.  Licensee must include a prominent statement that
 * the modification is derived, directly or indirectly, from Original Intel 
 * Code.
 *
 * 3.2. Redistribution in binary form of any substantial portion of the Covered 
 * Code or modification must reproduce the above Copyright Notice, and the 
 * following Disclaimer and Export Compliance provision in the documentation 
 * and/or other materials provided with the distribution.
 *
 * 3.3. Intel retains all right, title, and interest in and to the Original 
 * Intel Code.
 *
 * 3.4. Neither the name Intel nor any other trademark owned or controlled by 
 * Intel shall be used in advertising or otherwise to promote the sale, use or 
 * other dealings in products derived from or relating to the Covered Code 
 * without prior written authorization from Intel.
 *
 * 4. Disclaimer and Export Compliance
 *
 * 4.1. INTEL MAKES NO WARRANTY OF ANY KIND REGARDING ANY SOFTWARE PROVIDED 
 * HERE.  ANY SOFTWARE ORIGINATING FROM INTEL OR DERIVED FROM INTEL SOFTWARE 
 * IS PROVIDED "AS IS," AND INTEL WILL NOT PROVIDE ANY SUPPORT,  ASSISTANCE, 
 * INSTALLATION, TRAINING OR OTHER SERVICES.  INTEL WILL NOT PROVIDE ANY 
 * UPDATES, ENHANCEMENTS OR EXTENSIONS.  INTEL SPECIFICALLY DISCLAIMS ANY 
 * IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGEMENT AND FITNESS FOR A 
 * PARTICULAR PURPOSE. 
 *
 * 4.2. IN NO EVENT SHALL INTEL HAVE ANY LIABILITY TO LICENSEE, ITS LICENSEES 
 * OR ANY OTHER THIRD PARTY, FOR ANY LOST PROFITS, LOST DATA, LOSS OF USE OR 
 * COSTS OF PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, OR FOR ANY INDIRECT, 
 * SPECIAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THIS AGREEMENT, UNDER ANY 
 * CAUSE OF ACTION OR THEORY OF LIABILITY, AND IRRESPECTIVE OF WHETHER INTEL 
 * HAS ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES.  THESE LIMITATIONS 
 * SHALL APPLY NOTWITHSTANDING THE FAILURE OF THE ESSENTIAL PURPOSE OF ANY 
 * LIMITED REMEDY.
 *
 * 4.3. Licensee shall not export, either directly or indirectly, any of this 
 * software or system incorporating such software without first obtaining any 
 * required license or other approval from the U. S. Department of Commerce or 
 * any other agency or department of the United States Government.  In the 
 * event Licensee exports any such software from the United States or re-
 * exports any such software from a foreign destination, Licensee shall ensure
 * that the distribution and export/re-export of the software is in compliance 
 * with all laws, regulations, orders, or other restrictions of the U.S. Export 
 * Administration Regulations. Licensee agrees that neither it nor any of its 
 * subsidiaries will export/re-export any technical data, process, software, or 
 * service, directly or indirectly, to any country for which the United States 
 * government or any agency thereof requires an export license, other 
 * governmental approval, or letter of assurance, without first obtaining such
 * license, approval or letter.
 *
 *****************************************************************************/


#define __HWREGS_C__

#include <acpi.h>
#include <hardware.h>


#define _THIS_MODULE        "hwregs.c"
#define _COMPONENT          DEVICE_MANAGER


/* TBD: Is this needed? #pragma check_stack (off) */


/******************************************************************************
 *
 * FUNCTION:    GetBitShift
 *
 * PARAMETERS:  Mask            - Input mask to determine bit shift from.  Must
 *                                have at least 1 bit set.
 *
 * RETURN:      Bit location of the lsb of the mask
 *
 * DESCRIPTION: Returns the bit number for the low order bit that's set.
 *
 ******************************************************************************/

INT32
GetBitShift (
    UINT32                  Mask)
{
    INT32                   Shift;


    FUNCTION_TRACE ("GetBitShift");


    for (Shift = 0; ((Mask >> Shift) & 1) == 0; Shift++)
    { ; }

	FUNCTION_EXIT;
    return (Shift);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiRegisterIO
 *
 * PARAMETERS:  ReadWrite       - Either ACPI_READ or ACPI_WRITE.
 *              RegisterId      - index of ACPI register to access
 *              Value           - (only used on write) value to write to the
 *                                 register.  Shifted all the way right.
 *
 * RETURN:      Value written to or read from specified register.  This value
 *              is shifted all the way right.
 *
 * DESCRIPTION: Generic ACPI register read/write function.
 *
 ******************************************************************************/

UINT32
AcpiRegisterIO (
    INT32                   ReadWrite, 
    INT32                   RegisterId, 
    ...)
{
    UINT32                  RegisterValue = 0;
    UINT32                  Mask = 0;
    UINT32                  Value = 0;
    UINT32                  GpeReg = 0;


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
            DEBUG_PRINT (TRACE_IO, ("PM1a status: Read 0x%X from 0x%X\n", RegisterValue, FACP->Pm1aEvtBlk));
            
            if (FACP->Pm1bEvtBlk)
            {
                RegisterValue |= (UINT32) OsdIn16 ((UINT16) FACP->Pm1bEvtBlk);
                DEBUG_PRINT (TRACE_IO, ("PM1b status: Read 0x%X from 0x%X\n", RegisterValue, FACP->Pm1bEvtBlk));
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
                 * Status registers are different from the rest.  Clear by writing 1, writing 0
                 * has no effect.  So, the only relevent information is the single bit we're
                 * interested in, all others should be written as 0 so they will be left
                 * unchanged 
                 */
                
                Value <<= GetBitShift (Mask);
                Value &= Mask;
                
                if (Value)
                {
                    DEBUG_PRINT (TRACE_IO, ("About to write %04X to %04X\n", (UINT16) Value, 
                                (UINT16) FACP->Pm1aEvtBlk));
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
            DEBUG_PRINT (TRACE_IO, ("PM1a enable: Read 0x%X from 0x%X\n", RegisterValue, (FACP->Pm1aEvtBlk + FACP->Pm1EvtLen / 2)));
            
            if (FACP->Pm1bEvtBlk)
            {
                RegisterValue |= (UINT32) OsdIn16 ((UINT16) (FACP->Pm1bEvtBlk + FACP->Pm1EvtLen / 2));
                DEBUG_PRINT (TRACE_IO, ("PM1b enable: Read 0x%X from 0x%X\n", RegisterValue, (FACP->Pm1bEvtBlk + FACP->Pm1EvtLen / 2)));
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

                DEBUG_PRINT (TRACE_IO, ("About to write %04X to %04X\n", (UINT16) RegisterValue, 
                            (UINT16) (FACP->Pm1aEvtBlk + FACP->Pm1EvtLen / 2)));

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
            DEBUG_PRINT (TRACE_IO, ("PM1a control: Read 0x%X from 0x%X\n", RegisterValue, FACP->Pm1aCntBlk));
        }

        if (FACP->Pm1bEvtBlk && RegisterId != (INT32) SLP_TYPa)
        {
            RegisterValue |= (UINT32) OsdIn16 ((UINT16) FACP->Pm1bCntBlk);
            DEBUG_PRINT (TRACE_IO, ("PM1b control: Read 0x%X from 0x%X\n", RegisterValue, FACP->Pm1bCntBlk));
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
                     * Enable interrupts, the SCI handler is likely going to be invoked as
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
        DEBUG_PRINT (TRACE_IO, ("PM2 control: Read 0x%X from 0x%X\n", RegisterValue, FACP->Pm2CntBlk));
        
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

            DEBUG_PRINT (TRACE_IO, ("About to write %04X to %04X\n", (UINT16) RegisterValue, 
                        (UINT16) FACP->Pm2CntBlk));

            OsdOut16 ((UINT16) FACP->Pm2CntBlk, (UINT16) RegisterValue);
        }
        break;
    
    case PM_TIMER:
        RegisterValue = OsdIn32 ((UINT16) FACP->PmTmrBlk);
        DEBUG_PRINT (TRACE_IO, ("PM_TIMER: Read 0x%X from 0x%X\n", RegisterValue, FACP->PmTmrBlk));

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
        DEBUG_PRINT (TRACE_IO, ("GPE Enable bits: Read 0x%X from 0x%X\n", RegisterValue, GpeReg));
        
        if (ReadWrite == ACPI_WRITE)
        {               
            RegisterValue  &= ~Mask;
            Value          <<= GetBitShift (Mask);
            Value          &= Mask;
            RegisterValue  |= Value;
           
            /* This write will put the iAction state into the General Purpose */
            /* Enable Register indexed by the value in Mask */

            DEBUG_PRINT (TRACE_IO, ("About to write %04X to %04X\n", (UINT16) RegisterValue, 
                        (UINT16) GpeReg));

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

    DEBUG_PRINT (TRACE_IO, ("Register I/O: returning 0x%X\n", RegisterValue));
    FUNCTION_EXIT;
    return (RegisterValue);
}

/* Is this needed? #pragma check_stack () */


/******************************************************************************
 *
 * FUNCTION:    HwClearAcpiStatus
 *
 * PARAMETERS:  none
 *
 * RETURN:      none
 *
 * DESCRIPTION: Clears all fixed and general purpose status bits
 *
 ******************************************************************************/

void 
HwClearAcpiStatus (void)
{
    UINT16                  GpeLength;
    UINT16                  Index;


    FUNCTION_TRACE ("HwClearAcpiStatus");


    DEBUG_PRINT (TRACE_IO, ("About to write %04X to %04X\n", 
                    ALL_FIXED_STS_BITS, (UINT16) FACP->Pm1aEvtBlk));

    OsdOut16 ((UINT16) FACP->Pm1aEvtBlk, (UINT16) ALL_FIXED_STS_BITS);
    
    if (FACP->Pm1bEvtBlk)
    {
        OsdOut16 ((UINT16) FACP->Pm1bEvtBlk, (UINT16) ALL_FIXED_STS_BITS);
    }

    /* now clear the GPE Bits */
    
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

    FUNCTION_EXIT;
}   
