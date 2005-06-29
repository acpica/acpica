
/******************************************************************************
 * 
 * Name: hardware.h -- hardware specific interfaces
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
 * 2.1. This is your license from Intel Corp. under its intellectual property
 * rights.  You may have additional license terms from the party that provided
 * you this software, covering your right to use that party's intellectual
 * property rights.
 *
 * 2.2. Intel grants, free of charge, to any person ("Licensee") obtaining a
 * copy of the source code appearing in this file ("Covered Code") an
 * irrevocable, perpetual, worldwide license under Intel's copyrights in the
 * base code distributed originally by Intel ("Original Intel Code") to copy,
 * make derivatives, distribute, use and display any portion of the Covered
 * Code in any form, with the right to sublicense such rights; and
 *
 * 2.3. Intel grants Licensee a non-exclusive and non-transferable patent
 * license (without the right to sublicense), under only those claims of Intel
 * patents that are infringed by the Original Intel Code, to make, use, sell,
 * offer to sell, and import the Covered Code and derivative works thereof
 * solely to the minimum extent necessary to exercise the above copyright
 * license, and in no event shall the patent license extend to any additions
 * to or modifications of the Original Intel Code.  No other license or right
 * is granted directly or by implication, estoppel or otherwise;
 *
 * The above copyright and patent license is granted only if the following
 * conditions are met:
 *
 * 3. Conditions 
 *
 * 3.1. Redistribution of Source with Rights to Further Distribute Source.  
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification with rights to further distribute source must include
 * the above Copyright Notice, the above License, this list of Conditions,
 * and the following Disclaimer and Export Compliance provision.  In addition,
 * Licensee must cause all Covered Code to which Licensee contributes to
 * contain a file documenting the changes Licensee made to create that Covered
 * Code and the date of any change.  Licensee must include in that file the
 * documentation of any changes made by any predecessor Licensee.  Licensee 
 * must include a prominent statement that the modification is derived,
 * directly or indirectly, from Original Intel Code.
 *
 * 3.2. Redistribution of Source with no Rights to Further Distribute Source.  
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification without rights to further distribute source must
 * include the following Disclaimer and Export Compliance provision in the
 * documentation and/or other materials provided with distribution.  In
 * addition, Licensee may not authorize further sublicense of source of any
 * portion of the Covered Code, and must include terms to the effect that the
 * license from Licensee to its licensee is limited to the intellectual
 * property embodied in the software Licensee provides to its licensee, and
 * not to intellectual property embodied in modifications its licensee may
 * make.
 *
 * 3.3. Redistribution of Executable. Redistribution in executable form of any
 * substantial portion of the Covered Code or modification must reproduce the
 * above Copyright Notice, and the following Disclaimer and Export Compliance
 * provision in the documentation and/or other materials provided with the
 * distribution.
 *
 * 3.4. Intel retains all right, title, and interest in and to the Original
 * Intel Code.
 *
 * 3.5. Neither the name Intel nor any other trademark owned or controlled by
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
 * event Licensee exports any such software from the United States or
 * re-exports any such software from a foreign destination, Licensee shall
 * ensure that the distribution and export/re-export of the software is in
 * compliance with all laws, regulations, orders, or other restrictions of the
 * U.S. Export Administration Regulations. Licensee agrees that neither it nor
 * any of its subsidiaries will export/re-export any technical data, process,
 * software, or service, directly or indirectly, to any country for which the
 * United States government or any agency thereof requires an export license,
 * other governmental approval, or letter of assurance, without first obtaining
 * such license, approval or letter.
 *
 *****************************************************************************/

#ifndef __HARDWARE_H__
#define __HARDWARE_H__



/* flags for use in DisplayBitFlags parameters */

#define ACPI_MODE               1
#define LEGACY_MODE             2

/* Sleep states */

#define S0                      "_S0_"
#define S1                      "_S1_"
#define S2                      "_S2_"
#define S3                      "_S3_"
#define S4                      "_S4_"
#define S4BIOS                  "_S4B"
#define S5                      "_S5_"

/* 
 * The #define's and enum below establish an abstract way of identifying what
 * register block and register is to be accessed.  Do not change any of the
 * values as they are used in switch statements and offset calculations. 
 */
    
#define REGISTER_BLOCK_MASK     0xFF00
#define BIT_IN_REGISTER_MASK    0x00FF
#define PM1_EVT                 0x0100
#define PM1_CONTROL             0x0200
#define PM2_CONTROL             0x0300
#define PM_TIMER                0x0400
#define PROCESSOR_BLOCK         0x0500
#define GPE0_STS_BLOCK          0x0600
#define GPE0_EN_BLOCK           0x0700
#define GPE1_STS_BLOCK          0x0800
#define GPE1_EN_BLOCK           0x0900


enum
{
    /* PM1 status register ids */
    
    TMR_STS =   (PM1_EVT        | 0x01),
    BM_STS,
    GBL_STS,
    PWRBTN_STS,
    SLPBTN_STS,
    RTC_STS,
    WAK_STS,

    /* PM1 enable register ids */
    
    TMR_EN,
    /* need to skip 1 enable number since there's no bus master enable register */  
    GBL_EN =    (PM1_EVT        | 0x0A),
    PWRBTN_EN,
    SLPBTN_EN,
    RTC_EN,

    /* PM1 control register ids */

    SCI_EN =    (PM1_CONTROL    | 0x01),
    BM_RLD,
    GBL_RLS,
    SLP_TYPa,
    SLP_TYPb,
    SLP_EN,

    /* PM2 control register ids */

    ARB_DIS =   (PM2_CONTROL    | 0x01),

    /* PM Timer register ids */

    TMR_VAL =   (PM_TIMER       | 0x01),

    GPE0_STS =  (GPE0_STS_BLOCK | 0x01),
    GPE0_EN =   (GPE0_EN_BLOCK  | 0x01),

    GPE1_STS =  (GPE1_STS_BLOCK | 0x01),
    GPE1_EN =   (GPE0_EN_BLOCK  | 0x01),

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

/* Register read/write Macros */

#define READ_ACPI_REGISTER(RegId)       AcpiRegisterIO (ACPI_READ, (INT32)(RegId))
#define WRITE_ACPI_REGISTER(RegId,Val)  AcpiRegisterIO (ACPI_WRITE, (INT32) (RegId), Val)



/* Register I/O Prototypes */

UINT32
AcpiRegisterIO (
    INT32                   ReadWrite, 
    INT32                   RegisterId, ... /* DWORD Value */);

void 
HwClearAcpiStatus (
   void);


/* GPE support */

void
HwEnableGpe (
    UINT32                  GpeNumber);

void
HwDisableGpe (
    UINT32                  GpeNumber);

void
HwClearGpe (
    UINT32                  GpeNumber);


/* Sleep Prototypes */

ACPI_STATUS
AcpiObtainSleepTypeRegisterData (
    char                    *SleepStateReq,
    UINT8                   *Slp_TypA,
    UINT8                   *Slp_TypB);

BOOLEAN 
AcpiSleepStateSupported (
    char                    *SleepState);

ACPI_STATUS
AcpiGoToSleep (
    char                    *SleepState);


/* ACPI Timer prototypes */

UINT32
AcpiPmtTicks (
    void);

INT32
AcpiPmtResolution (
    void);

#endif /* __HARDWARE_H__ */
