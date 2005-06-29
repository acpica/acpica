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
 | FILENAME: devices.h -- hardware specific interfaces
 |__________________________________________________________________________
*/

#ifndef __DEVICES_H__
#define __DEVICES_H__



/* flags for use in DisplayBitFlags parameters */

#define ACPI_MODE       1
#define LEGACY_MODE     2

/* Sleep states */

#define S0              "_S0_"
#define S1              "_S1_"
#define S2              "_S2_"
#define S3              "_S3_"
#define S4              "_S4_"
#define S4BIOS          "_S4B"
#define S5              "_S5_"

/* 
 * The #define's and enum below establish an abstract way of identifying what
 * register block and register is to be accessed.  Do not change any of the
 * values as they are used in switch statements and offset calculations. 
 */
    
#define REGISTER_BLOCK_MASK     0xFF00
#define BIT_IN_REGISTER_MASK    0x00FF
#define PM1_EVT                 0x100
#define PM1_CONTROL             0x200
#define PM2_CONTROL             0x300
#define PM_TIMER                0x400
#define PROCESSOR_BLOCK         0x500
#define GPE0_STS_BLOCK          0x600
#define GPE0_EN_BLOCK           0x700
#define GPE1_STS_BLOCK          0x800
#define GPE1_EN_BLOCK           0x900


enum
{
    /* PM1 status register ids */
    
    TMR_STS = (PM1_EVT | 0x01),
    BM_STS,
    GBL_STS,
    PWRBTN_STS,
    SLPBTN_STS,
    RTC_STS,
    WAK_STS,

    /* PM1 enable register ids */
    
    TMR_EN,
    /* need to skip 1 enable number since there's no bus master enable register */  
    GBL_EN = (PM1_EVT | 0x0A),
    PWRBTN_EN,
    SLPBTN_EN,
    RTC_EN,

    /* PM1 control register ids */

    SCI_EN = (PM1_CONTROL | 0x01),
    BM_RLD,
    GBL_RLS,
    SLP_TYPa,
    SLP_TYPb,
    SLP_EN,

    /* PM2 control register ids */

    ARB_DIS = (PM2_CONTROL | 0x01),

    /* PM Timer register ids */

    TMR_VAL = (PM_TIMER | 0x01),

    GPE0_STS = (GPE0_STS_BLOCK | 0x01),
    GPE0_EN = (GPE0_EN_BLOCK | 0x01),

    GPE1_STS = (GPE1_STS_BLOCK | 0x01),
    GPE1_EN = (GPE0_EN_BLOCK | 0x01),

    /* Last register value is one less than LAST_REG */

    LAST_REG
};


#define TMR_STS_MASK        0x0001
#define BM_STS_MASK         0x0010
#define GBL_STS_MASK        0x0020
#define PWRBTN_STS_MASK     0x0100
#define SLPBTN_STS_MASK     0x0200
#define RTC_STS_MASK        0x0400
#define WAK_STS_MASK        0x8000
#define ALL_FIXED_STS_BITS  \
                            (TMR_STS_MASK      |   \
                            BM_STS_MASK        |   \
                            GBL_STS_MASK       |   \
                            PWRBTN_STS_MASK    |   \
                            SLPBTN_STS_MASK    |   \
                            RTC_STS_MASK       |   \
                            WAK_STS_MASK)

#define TMR_EN_MASK         0x0001
#define GBL_EN_MASK         0x0020
#define PWRBTN_EN_MASK      0x0100
#define SLPBTN_EN_MASK      0x0200
#define RTC_EN_MASK         0x0400

#define SCI_EN_MASK         0x0001
#define BM_RLD_MASK         0x0002
#define GBL_RLS_MASK        0x0004
#define SLP_TYPx_MASK       0x1C00
#define SLP_EN_MASK         0x2000

#define ARB_DIS_MASK        0x0001

#define GPE0_STS_MASK
#define GPE0_EN_MASK

#define GPE1_STS_MASK
#define GPE1_EN_MASK


#define ACPI_READ           1
#define ACPI_WRITE          2

#define LOW_BYTE            0x00FF
#define ONE_BYTE            0x08

#ifndef SET 
    #define SET             1
#endif
#ifndef CLEAR
    #define CLEAR           0
#endif

/* Macros */

#define AcpiReadRegister(RegisterId) \
    AcpiRegisterIO (ACPI_READ, (INT32) (RegisterId))

#define AcpiWriteRegister(RegisterId, Value) \
    AcpiRegisterIO (ACPI_WRITE, (INT32) (RegisterId), Value)



/* Register I/O Prototypes */

UINT32
AcpiRegisterIO (
    INT32                   ReadWrite, 
    INT32                   RegisterId, ... /* DWORD Value */);

void 
ClearAllAcpiChipsetStatusBits (
   void);


/* Sleep Prototypes */

INT32
AcpiObtainSleepTypeRegisterData (
    char                    *SleepStateReq,
    UINT8                   *Slp_TypA,
    UINT8                   *Slp_TypB);

BOOLEAN 
AcpiSleepStateSupported (
    char                    *SleepState);

INT32
AcpiGoToSleep (
    char                    *SleepState);


/* ACPI mode Prototypes */

INT32
AcpiSetMode (
    INT32                   Mode);

INT32
AcpiModeStatus (
    void);

INT32
AcpiModeCapabilities (
    void);


/* ACPI Timer prototypes */

UINT32
AcpiPmtTicks (
    void);

INT32
AcpiPmtResolution (
    void);



#endif /* __DEVICES_H__ */
