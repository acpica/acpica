/******************************************************************************
 *
 * Module Name: dmtbinfo - Table info for non-AML tables
 *              $Revision: 1.3 $
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2006, Intel Corp.
 * All rights reserved.
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
 * license (with the right to sublicense), under only those claims of Intel
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

#include "acpi.h"
#include "acdisasm.h"

/* This module used for application-level code only */

#define _COMPONENT          ACPI_CA_DISASSEMBLER
        ACPI_MODULE_NAME    ("dmtbinfo")

/*
 * ACPI Table Information, used to dump formatted ACPI tables
 *
 * Each entry is of the form:  <Field Type, Field Offset, Field Name>
 */


/*******************************************************************************
 *
 * Common ACPI table header
 *
 ******************************************************************************/

ACPI_DMTABLE_INFO           AcpiDmTableInfoHeader[] =
{
    {ACPI_DMT_NAME4,    ACPI_HDR_OFFSET (Signature),                "Signature"},
    {ACPI_DMT_UINT32,   ACPI_HDR_OFFSET (Length),                   "Table Length"},
    {ACPI_DMT_UINT8,    ACPI_HDR_OFFSET (Revision),                 "Revision"},
    {ACPI_DMT_CHKSUM,   ACPI_HDR_OFFSET (Checksum),                 "Checksum"},
    {ACPI_DMT_NAME6,    ACPI_HDR_OFFSET (OemId),                    "Oem ID"},
    {ACPI_DMT_NAME8,    ACPI_HDR_OFFSET (OemTableId),               "Oem Table ID"},
    {ACPI_DMT_UINT32,   ACPI_HDR_OFFSET (OemRevision),              "Oem Revision"},
    {ACPI_DMT_NAME4,    ACPI_HDR_OFFSET (AslCompilerId),            "Asl Compiler ID"},
    {ACPI_DMT_UINT32,   ACPI_HDR_OFFSET (AslCompilerRevision),      "Asl Compiler Revision"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};


/*******************************************************************************
 *
 * GAS - Generic Address Structure
 *
 ******************************************************************************/

ACPI_DMTABLE_INFO           AcpiDmTableInfoGas[] =
{
    {ACPI_DMT_SPACEID,  ACPI_GAS_OFFSET (AddressSpaceId),           "Space ID"},
    {ACPI_DMT_UINT8,    ACPI_GAS_OFFSET (RegisterBitWidth),         "Bit Width"},
    {ACPI_DMT_UINT8,    ACPI_GAS_OFFSET (RegisterBitOffset),        "Bit Offset"},
    {ACPI_DMT_UINT8,    ACPI_GAS_OFFSET (AccessWidth),              "Access Width"},
    {ACPI_DMT_UINT64,   ACPI_GAS_OFFSET (Address),                  "Address"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};


/*******************************************************************************
 *
 * RSDP - Root System Description Pointer (Signature is "RSD PTR ")
 *
 ******************************************************************************/

ACPI_DMTABLE_INFO           AcpiDmTableInfoRsdp1[] =
{
    {ACPI_DMT_NAME8,    ACPI_RSDP_OFFSET (Signature),               "Signature"},
    {ACPI_DMT_UINT8,    ACPI_RSDP_OFFSET (Checksum),                "Checksum"},
    {ACPI_DMT_NAME6,    ACPI_RSDP_OFFSET (OemId),                   "Oem ID"},
    {ACPI_DMT_UINT8,    ACPI_RSDP_OFFSET (Revision),                "Revision"},
    {ACPI_DMT_UINT32,   ACPI_RSDP_OFFSET (RsdtPhysicalAddress),     "RSDT Address"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};

/* ACPI 2.0+ Extensions */

ACPI_DMTABLE_INFO           AcpiDmTableInfoRsdp2[] =
{
    {ACPI_DMT_UINT32,   ACPI_RSDP_OFFSET (Length),                  "Length"},
    {ACPI_DMT_UINT64,   ACPI_RSDP_OFFSET (XsdtPhysicalAddress),     "XSDT Address"},
    {ACPI_DMT_UINT8,    ACPI_RSDP_OFFSET (ExtendedChecksum),        "Extended Checksum"},
    {ACPI_DMT_UINT24,   ACPI_RSDP_OFFSET (Reserved),                "Reserved"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};


/*******************************************************************************
 *
 * FACS - Firmware ACPI Control Structure
 *
 ******************************************************************************/

ACPI_DMTABLE_INFO           AcpiDmTableInfoFacs[] =
{
    {ACPI_DMT_NAME4,    ACPI_FACS_OFFSET (Signature),               "Signature"},
    {ACPI_DMT_UINT32,   ACPI_FACS_OFFSET (Length),                  "Length"},
    {ACPI_DMT_UINT32,   ACPI_FACS_OFFSET (HardwareSignature),       "Hardware Signature"},
    {ACPI_DMT_UINT32,   ACPI_FACS_OFFSET (FirmwareWakingVector),    "Firmware Waking Vector(32)"},
    {ACPI_DMT_UINT32,   ACPI_FACS_OFFSET (GlobalLock),              "Global Lock"},
    {ACPI_DMT_UINT32,   ACPI_FACS_FLAG_OFFSET (GlobalLock,0),       "Flags (decoded below)"},
    {ACPI_DMT_FLAG0,    ACPI_FACS_FLAG_OFFSET (GlobalLock,0),       "S4BIOS Support Present"},
    {ACPI_DMT_UINT64,   ACPI_FACS_OFFSET (XFirmwareWakingVector),   "Firmware Waking Vector(64)"},
    {ACPI_DMT_UINT8,    ACPI_FACS_OFFSET (Version),                 "Version"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};


/*******************************************************************************
 *
 * FADT - Fixed ACPI Description Table (Signature is FACP)
 *
 ******************************************************************************/

ACPI_DMTABLE_INFO           AcpiDmTableInfoFadt1[] =
{
    {ACPI_DMT_UINT32,   ACPI_FADT_OFFSET (V1_FirmwareCtrl),         "FACS Address"},
    {ACPI_DMT_UINT32,   ACPI_FADT_OFFSET (V1_Dsdt),                 "DSDT Address"},
    {ACPI_DMT_UINT8,    ACPI_FADT_OFFSET (Reserved1),               "Reserved"},
    {ACPI_DMT_UINT8,    ACPI_FADT_OFFSET (Prefer_PM_Profile),       "PM Profile"},
    {ACPI_DMT_UINT16,   ACPI_FADT_OFFSET (SciInt),                  "SCI Interrupt"},
    {ACPI_DMT_UINT32,   ACPI_FADT_OFFSET (SmiCmd),                  "SMI Command Port"},
    {ACPI_DMT_UINT8,    ACPI_FADT_OFFSET (AcpiEnable),              "ACPI Enable Value"},
    {ACPI_DMT_UINT8,    ACPI_FADT_OFFSET (AcpiDisable),             "ACPI Disable Value"},
    {ACPI_DMT_UINT8,    ACPI_FADT_OFFSET (S4BiosReq),               "S4BIOS Command"},
    {ACPI_DMT_UINT8,    ACPI_FADT_OFFSET (PstateCnt),               "P-State Control"},
    {ACPI_DMT_UINT32,   ACPI_FADT_OFFSET (V1_Pm1aEvtBlk),           "PM1A Event Address"},
    {ACPI_DMT_UINT32,   ACPI_FADT_OFFSET (V1_Pm1bEvtBlk),           "PM1B Event Address"},
    {ACPI_DMT_UINT32,   ACPI_FADT_OFFSET (V1_Pm1aCntBlk),           "PM1A Control Address"},
    {ACPI_DMT_UINT32,   ACPI_FADT_OFFSET (V1_Pm1bCntBlk),           "PM1B Control Address"},
    {ACPI_DMT_UINT32,   ACPI_FADT_OFFSET (V1_Pm2CntBlk),            "PM2 Control Address"},
    {ACPI_DMT_UINT32,   ACPI_FADT_OFFSET (V1_PmTmrBlk),             "PM Timer Address"},
    {ACPI_DMT_UINT32,   ACPI_FADT_OFFSET (V1_Gpe0Blk),              "GPE0 Event Address"},
    {ACPI_DMT_UINT32,   ACPI_FADT_OFFSET (V1_Gpe1Blk),              "GPE1 Event Address"},
    {ACPI_DMT_UINT8,    ACPI_FADT_OFFSET (Pm1EvtLen),               "PM1 Event Length"},
    {ACPI_DMT_UINT8,    ACPI_FADT_OFFSET (Pm1CntLen),               "PM1 Control Length"},
    {ACPI_DMT_UINT8,    ACPI_FADT_OFFSET (Pm2CntLen),               "PM2 Control Length"},
    {ACPI_DMT_UINT8,    ACPI_FADT_OFFSET (PmTmLen),                 "PM Timer Length"},
    {ACPI_DMT_UINT8,    ACPI_FADT_OFFSET (Gpe0BlkLen),              "GPE0 Block Length"},
    {ACPI_DMT_UINT8,    ACPI_FADT_OFFSET (Gpe1BlkLen),              "GPE1 Block Length"},
    {ACPI_DMT_UINT8,    ACPI_FADT_OFFSET (Gpe1Base),                "GPE1 Base"},
    {ACPI_DMT_UINT8,    ACPI_FADT_OFFSET (CstCnt),                  "_CST Support"},
    {ACPI_DMT_UINT16,   ACPI_FADT_OFFSET (Plvl2Lat),                "C2 Latency"},
    {ACPI_DMT_UINT16,   ACPI_FADT_OFFSET (Plvl3Lat),                "C3 Latency"},
    {ACPI_DMT_UINT16,   ACPI_FADT_OFFSET (FlushSize),               "CPU Cache Size"},
    {ACPI_DMT_UINT16,   ACPI_FADT_OFFSET (FlushStride),             "Cache Flush Stride"},
    {ACPI_DMT_UINT8,    ACPI_FADT_OFFSET (DutyOffset),              "Duty Cycle Offset"},
    {ACPI_DMT_UINT8,    ACPI_FADT_OFFSET (DutyWidth),               "Duty Cycle Width"},
    {ACPI_DMT_UINT8,    ACPI_FADT_OFFSET (DayAlrm),                 "RTC Day Alarm Index"},
    {ACPI_DMT_UINT8,    ACPI_FADT_OFFSET (MonAlrm),                 "RTC Month Alarm Index"},
    {ACPI_DMT_UINT8,    ACPI_FADT_OFFSET (Century),                 "RTC Century Index"},
    {ACPI_DMT_UINT16,   ACPI_FADT_OFFSET (IapcBootArch),            "Boot Architecture Flags"},
    {ACPI_DMT_UINT8,    ACPI_FADT_OFFSET (Reserved2),               "Reserved"},
    {ACPI_DMT_UINT32,   ACPI_FADT_FLAG_OFFSET (Reserved2,0),        "Flags (decoded below)"},

    /* Flags byte 0 */

    {ACPI_DMT_FLAG0,    ACPI_FADT_FLAG_OFFSET (Reserved2,0),        "WBINVD is operational"},
    {ACPI_DMT_FLAG0,    ACPI_FADT_FLAG_OFFSET (Reserved2,0),        "WBINVD is operational"},
    {ACPI_DMT_FLAG1,    ACPI_FADT_FLAG_OFFSET (Reserved2,0),        "WBINVD does not invalidate"},
    {ACPI_DMT_FLAG2,    ACPI_FADT_FLAG_OFFSET (Reserved2,0),        "All CPUs support C1"},
    {ACPI_DMT_FLAG3,    ACPI_FADT_FLAG_OFFSET (Reserved2,0),        "C2 works on MP system"},
    {ACPI_DMT_FLAG4,    ACPI_FADT_FLAG_OFFSET (Reserved2,0),        "Power button is generic"},
    {ACPI_DMT_FLAG5,    ACPI_FADT_FLAG_OFFSET (Reserved2,0),        "Sleep button is generic"},
    {ACPI_DMT_FLAG6,    ACPI_FADT_FLAG_OFFSET (Reserved2,0),        "RTC wakeup not fixed"},
    {ACPI_DMT_FLAG7,    ACPI_FADT_FLAG_OFFSET (Reserved2,0),        "RTC wakeup/S4 not possible"},

    /* Flags byte 1 */

    {ACPI_DMT_FLAG0,    ACPI_FADT_FLAG_OFFSET (Reserved2,1),        "32-bit PM Timer"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};

/* ACPI 2.0+ Extensions */

ACPI_DMTABLE_INFO           AcpiDmTableInfoFadt2[] =
{
    {ACPI_DMT_FLAG1,    ACPI_FADT_FLAG_OFFSET (Reserved2,1),        "Docking Supported"},
    {ACPI_DMT_FLAG2,    ACPI_FADT_FLAG_OFFSET (Reserved2,1),        "Reset Register Supported"},
    {ACPI_DMT_FLAG3,    ACPI_FADT_FLAG_OFFSET (Reserved2,1),        "Sealed Case"},
    {ACPI_DMT_FLAG4,    ACPI_FADT_FLAG_OFFSET (Reserved2,1),        "Headless - No Video"},
    {ACPI_DMT_FLAG5,    ACPI_FADT_FLAG_OFFSET (Reserved2,1),        "Native instr after SLP_TYP"},
    {ACPI_DMT_FLAG6,    ACPI_FADT_FLAG_OFFSET (Reserved2,1),        "PCIEXP_WAK Supported"},
    {ACPI_DMT_FLAG7,    ACPI_FADT_FLAG_OFFSET (Reserved2,1),        "Use Platform Timer"},

    /* Flags byte 2 */

    {ACPI_DMT_FLAG0,    ACPI_FADT_FLAG_OFFSET (Reserved2,2),        "RTC_STS valid after S4"},
    {ACPI_DMT_FLAG1,    ACPI_FADT_FLAG_OFFSET (Reserved2,2),        "Remote Power-on capable"},
    {ACPI_DMT_FLAG2,    ACPI_FADT_FLAG_OFFSET (Reserved2,2),        "APIC Cluster Model"},
    {ACPI_DMT_FLAG3,    ACPI_FADT_FLAG_OFFSET (Reserved2,2),        "APIC Physical Dest Mode"},

    {ACPI_DMT_GAS,      ACPI_FADT_OFFSET (ResetRegister),           "Reset Register"},
    {ACPI_DMT_UINT8,    ACPI_FADT_OFFSET (ResetValue),              "Value to cause reset"},
    {ACPI_DMT_UINT24,   ACPI_FADT_OFFSET (Reserved4),               "Reserved"},
    {ACPI_DMT_UINT64,   ACPI_FADT_OFFSET (XFirmwareCtrl),           "FACS Address"},

    {ACPI_DMT_UINT64,   ACPI_FADT_OFFSET (XDsdt),                   "DSDT Address"},
    {ACPI_DMT_GAS,      ACPI_FADT_OFFSET (XPm1aEvtBlk),             "PM1A Event Register"},
    {ACPI_DMT_GAS,      ACPI_FADT_OFFSET (XPm1bEvtBlk),             "PM1B Event Register"},
    {ACPI_DMT_GAS,      ACPI_FADT_OFFSET (XPm1aCntBlk),             "PM1A Control Register"},
    {ACPI_DMT_GAS,      ACPI_FADT_OFFSET (XPm1bCntBlk),             "PM1B Control Register"},
    {ACPI_DMT_GAS,      ACPI_FADT_OFFSET (XPm2CntBlk),              "PM2 Control Register"},
    {ACPI_DMT_GAS,      ACPI_FADT_OFFSET (XPmTmrBlk),               "PM Timer Register"},
    {ACPI_DMT_GAS,      ACPI_FADT_OFFSET (XGpe0Blk),                "GPE0 Block Register"},
    {ACPI_DMT_GAS,      ACPI_FADT_OFFSET (XGpe1Blk),                "GPE1 Block Register"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};


/*
 * Remaining tables are not consumed directly by the ACPICA subsystem
 */

/*******************************************************************************
 *
 * ASF - Alert Standard Format table (Signature "ASF!")
 *
 ******************************************************************************/

/* Common sub-table header (one per sub-table) */

ACPI_DMTABLE_INFO           AcpiDmTableInfoAsfHdr[] =
{
    {ACPI_DMT_UINT8,    ACPI_ASF0_OFFSET (Type),                   "Sub-Table Type"},
    {ACPI_DMT_UINT8,    ACPI_ASF0_OFFSET (Length),                 "Length"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};

/* 0: ASF Information */

ACPI_DMTABLE_INFO           AcpiDmTableInfoAsf0[] =
{
    {ACPI_DMT_UINT8,    ACPI_ASF0_OFFSET (MinResetValue),           "Minimum Reset Value"},
    {ACPI_DMT_UINT8,    ACPI_ASF0_OFFSET (MinResetValue),           "Minimum Polling Interval"},
    {ACPI_DMT_UINT16,   ACPI_ASF0_OFFSET (SystemId),                "System ID"},
    {ACPI_DMT_UINT32,   ACPI_ASF0_OFFSET (SystemId),                "Manufacturer ID"},
    {ACPI_DMT_UINT8,    ACPI_ASF0_OFFSET (Flags),                   "Flags"},
    {ACPI_DMT_UINT24,   ACPI_ASF0_OFFSET (Reserved2),               "Reserved"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};

/* 1: ASF Alerts */

ACPI_DMTABLE_INFO           AcpiDmTableInfoAsf1[] =
{
    {ACPI_DMT_UINT8,    ACPI_ASF1_OFFSET (AssertMask),              "AssertMask"},
    {ACPI_DMT_UINT8,    ACPI_ASF1_OFFSET (DeassertMask),            "DeassertMask"},
    {ACPI_DMT_UINT8,    ACPI_ASF1_OFFSET (Alerts),                  "Alerts"},
    {ACPI_DMT_UINT8,    ACPI_ASF1_OFFSET (DataLength),              "Data Length"},
    /* TBD: Alert array */
    {ACPI_DMT_EXIT,     0,                                          NULL}
};

/* 2: ASF Remote Control */

ACPI_DMTABLE_INFO           AcpiDmTableInfoAsf2[] =
{
    {ACPI_DMT_UINT8,    ACPI_ASF2_OFFSET (Controls),                "Controls"},
    {ACPI_DMT_UINT8,    ACPI_ASF2_OFFSET (DataLength),              "Data Length"},
    {ACPI_DMT_UINT16,   ACPI_ASF2_OFFSET (Reserved2),               "Reserved"},
    /* TBD: Control array */
    {ACPI_DMT_EXIT,     0,                                          NULL}
};

/* 3: ASF RMCP Boot Options */

ACPI_DMTABLE_INFO           AcpiDmTableInfoAsf3[] =
{
    {ACPI_DMT_UINT56,   ACPI_ASF3_OFFSET (Capabilities),            "Capabilites"},
    {ACPI_DMT_UINT8,    ACPI_ASF3_OFFSET (CompletionCode),          "Completion Code"},
    {ACPI_DMT_UINT32,   ACPI_ASF3_OFFSET (EnterpriseId),            "Enterprise ID"},
    {ACPI_DMT_UINT8,    ACPI_ASF3_OFFSET (Command),                 "Command"},
    {ACPI_DMT_UINT16,   ACPI_ASF3_OFFSET (Parameter),               "Parameter"},
    {ACPI_DMT_UINT16,   ACPI_ASF3_OFFSET (BootOptions),             "Boot Options"},
    {ACPI_DMT_UINT16,   ACPI_ASF3_OFFSET (OemParameters),           "Oem Parameters"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};

/* 4: ASF Address */

ACPI_DMTABLE_INFO           AcpiDmTableInfoAsf4[] =
{
    {ACPI_DMT_UINT8,    ACPI_ASF4_OFFSET (EpromAddress),            "Eprom Address"},
    {ACPI_DMT_UINT8,    ACPI_ASF4_OFFSET (Devices),                 "Devices"},
    /* TBD: Address array */
    {ACPI_DMT_EXIT,     0,                                          NULL}
};


/*******************************************************************************
 *
 * BOOT - Simple Boot Flag Table
 *
 ******************************************************************************/

ACPI_DMTABLE_INFO           AcpiDmTableInfoBoot[] =
{
    {ACPI_DMT_UINT8,    ACPI_BOOT_OFFSET (CmosIndex),               "Boot Register Index"},
    {ACPI_DMT_UINT24,   ACPI_BOOT_OFFSET (Reserved),                "Reserved"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};


/*******************************************************************************
 *
 * CPEP - Corrected Platform Error Polling table
 *
 ******************************************************************************/

ACPI_DMTABLE_INFO           AcpiDmTableInfoCpep[] =
{
    {ACPI_DMT_UINT64,   ACPI_CPEP_OFFSET (Reserved),                "Reserved"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};

ACPI_DMTABLE_INFO           AcpiDmTableInfoCpep0[] =
{
    {ACPI_DMT_UINT8,    ACPI_CPEP0_OFFSET (Type),                   "Sub-Table Type"},
    {ACPI_DMT_UINT8,    ACPI_CPEP0_OFFSET (Length),                 "Length"},
    {ACPI_DMT_UINT8,    ACPI_CPEP0_OFFSET (ProcessorId),            "Processor ID"},
    {ACPI_DMT_UINT8,    ACPI_CPEP0_OFFSET (ProcessorEid),           "Processor EID"},
    {ACPI_DMT_UINT8,    ACPI_CPEP0_OFFSET (PollingInterval),        "Polling Interval"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};


/*******************************************************************************
 *
 * DBGP - Debug Port
 *
 ******************************************************************************/

ACPI_DMTABLE_INFO           AcpiDmTableInfoDbgp[] =
{
    {ACPI_DMT_UINT8,    ACPI_DBGP_OFFSET (InterfaceType),           "Interface Type"},
    {ACPI_DMT_UINT24,   ACPI_DBGP_OFFSET (Reserved),                "Reserved"},
    {ACPI_DMT_GAS,      ACPI_DBGP_OFFSET (DebugPort),               "Debug Port Register"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};


/*******************************************************************************
 *
 * ECDT - Embedded Controller Boot Resources Table
 *
 ******************************************************************************/

ACPI_DMTABLE_INFO           AcpiDmTableInfoEcdt[] =
{
    {ACPI_DMT_GAS,      ACPI_ECDT_OFFSET (EcControl),               "Command/Status Register"},
    {ACPI_DMT_GAS,      ACPI_ECDT_OFFSET (EcData),                  "Data Register"},
    {ACPI_DMT_UINT32,   ACPI_ECDT_OFFSET (Uid),                     "UID"},
    {ACPI_DMT_UINT8,    ACPI_ECDT_OFFSET (GpeBit),                  "GPE Number"},
    {ACPI_DMT_STRING,   ACPI_ECDT_OFFSET (EcId),                    "Namepath"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};


/*******************************************************************************
 *
 * HPET - High Precision Event Timer table
 *
 ******************************************************************************/

ACPI_DMTABLE_INFO           AcpiDmTableInfoHpet[] =
{
    {ACPI_DMT_UINT32,   ACPI_HPET_OFFSET (HardwareId),              "Hardware Block ID"},
    {ACPI_DMT_GAS,      ACPI_HPET_OFFSET (BaseAddress),             "Timer Block Register"},
    {ACPI_DMT_UINT8,    ACPI_HPET_OFFSET (HpetNumber),              "Sequence Number"},
    {ACPI_DMT_UINT16,   ACPI_HPET_OFFSET (ClockTick),               "Minimum Clock Ticks"},
    {ACPI_DMT_UINT8,    ACPI_HPET_FLAG_OFFSET (ClockTick,0),        "Flags (decoded below)"},
    {ACPI_DMT_FLAG0,    ACPI_HPET_FLAG_OFFSET (ClockTick,0),        "Page Protect"},
    {ACPI_DMT_FLAG1,    ACPI_HPET_FLAG_OFFSET (ClockTick,0),        "4K Page Protect"},
    {ACPI_DMT_FLAG2,    ACPI_HPET_FLAG_OFFSET (ClockTick,0),        "64K Page Protect"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};


/*******************************************************************************
 *
 * MADT - Multiple APIC Description Table and subtables
 *
 ******************************************************************************/

ACPI_DMTABLE_INFO           AcpiDmTableInfoMadt[] =
{
    {ACPI_DMT_UINT32,   ACPI_MADT_OFFSET (LocalApicAddress),        "Local Apic Address"},
    {ACPI_DMT_UINT32,   ACPI_MADT_FLAG_OFFSET (LocalApicAddress,0), "Flags (decoded below)"},
    {ACPI_DMT_FLAG0,    ACPI_MADT_FLAG_OFFSET (LocalApicAddress,0), "PC-AT Compatibility"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};

/* Common sub-table header (one per sub-table) */

ACPI_DMTABLE_INFO           AcpiDmTableInfoMadtHdr[] =
{
    {ACPI_DMT_MADT,     ACPI_MADTH_OFFSET (Type),                   "Sub-Table Type"},
    {ACPI_DMT_UINT8,    ACPI_MADTH_OFFSET (Length),                 "Length"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};

/* MADT sub-tables */

/* 0: processor APIC */

ACPI_DMTABLE_INFO           AcpiDmTableInfoMadt0[] =
{
    {ACPI_DMT_UINT8,    ACPI_MADT0_OFFSET (ProcessorId),            "Processor ID"},
    {ACPI_DMT_UINT8,    ACPI_MADT0_OFFSET (LocalApicId),            "Local Apic ID"},
    {ACPI_DMT_UINT32,   ACPI_MADT0_FLAG_OFFSET (LocalApicId,0),     "Flags (decoded below)"},
    {ACPI_DMT_FLAG0,    ACPI_MADT0_FLAG_OFFSET (LocalApicId,0),     "Processor Enabled"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};

/* 1: IO APIC */

ACPI_DMTABLE_INFO           AcpiDmTableInfoMadt1[] =
{
    {ACPI_DMT_UINT8,    ACPI_MADT1_OFFSET (IoApicId),               "I/O Apic ID"},
    {ACPI_DMT_UINT8,    ACPI_MADT1_OFFSET (Reserved),               "Reserved"},
    {ACPI_DMT_UINT32,   ACPI_MADT1_OFFSET (Address),                "Address"},
    {ACPI_DMT_UINT32,   ACPI_MADT1_OFFSET (Interrupt),              "Interrupt"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};

/* 2: Interrupt Override */

ACPI_DMTABLE_INFO           AcpiDmTableInfoMadt2[] =
{
    {ACPI_DMT_UINT8,    ACPI_MADT2_OFFSET (Bus),                    "Bus"},
    {ACPI_DMT_UINT8,    ACPI_MADT2_OFFSET (Source),                 "Source"},
    {ACPI_DMT_UINT32,   ACPI_MADT2_OFFSET (Interrupt),              "Interrupt"},
    {ACPI_DMT_UINT16,   ACPI_MADT2_FLAG_OFFSET (Interrupt,0),       "Flags (decoded below)"},
    {ACPI_DMT_FLAGS0,   ACPI_MADT2_FLAG_OFFSET (Interrupt,0),       "Polarity"},
    {ACPI_DMT_FLAGS2,   ACPI_MADT2_FLAG_OFFSET (Interrupt,0),       "Trigger Mode"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};

/* 3: NMI Sources */

ACPI_DMTABLE_INFO           AcpiDmTableInfoMadt3[] =
{
    {ACPI_DMT_UINT16,   ACPI_MADT3_FLAG_OFFSET (Length,0),          "Flags (decoded below)"},
    {ACPI_DMT_FLAGS0,   ACPI_MADT3_FLAG_OFFSET (Length,0),          "Polarity"},
    {ACPI_DMT_FLAGS2,   ACPI_MADT3_FLAG_OFFSET (Length,0),          "Trigger Mode"},
    {ACPI_DMT_UINT32,   ACPI_MADT3_OFFSET (Interrupt),              "Interrupt"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};

/* 4: Local APIC NMI */

ACPI_DMTABLE_INFO           AcpiDmTableInfoMadt4[] =
{
    {ACPI_DMT_UINT8,    ACPI_MADT4_OFFSET (ProcessorId),            "Processor ID"},
    {ACPI_DMT_UINT16,   ACPI_MADT4_FLAG_OFFSET (ProcessorId,0),     "Flags (decoded below)"},
    {ACPI_DMT_FLAGS0,   ACPI_MADT4_FLAG_OFFSET (ProcessorId,0),     "Polarity"},
    {ACPI_DMT_FLAGS2,   ACPI_MADT4_FLAG_OFFSET (ProcessorId,0),     "Trigger Mode"},
    {ACPI_DMT_UINT8,    ACPI_MADT4_OFFSET (Lint),                   "Interrupt Input LINT"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};

/* 5: Address Override */

ACPI_DMTABLE_INFO           AcpiDmTableInfoMadt5[] =
{
    {ACPI_DMT_UINT16,   ACPI_MADT5_OFFSET (Reserved),               "Reserved"},
    {ACPI_DMT_UINT64,   ACPI_MADT5_OFFSET (Address),                "APIC Address"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};

/* 6: I/O Sapic */

ACPI_DMTABLE_INFO           AcpiDmTableInfoMadt6[] =
{
    {ACPI_DMT_UINT8,    ACPI_MADT6_OFFSET (IoSapicId),              "I/O Sapic ID"},
    {ACPI_DMT_UINT8,    ACPI_MADT6_OFFSET (Reserved),               "Reserved"},
    {ACPI_DMT_UINT32,   ACPI_MADT6_OFFSET (InterruptBase),          "Interrupt Base"},
    {ACPI_DMT_UINT64,   ACPI_MADT6_OFFSET (Address),                "Address"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};

/* 7: Local Sapic */

ACPI_DMTABLE_INFO           AcpiDmTableInfoMadt7[] =
{
    {ACPI_DMT_UINT8,    ACPI_MADT7_OFFSET (ProcessorId),            "Processor ID"},
    {ACPI_DMT_UINT8,    ACPI_MADT7_OFFSET (LocalSapicId),           "Local Sapic ID"},
    {ACPI_DMT_UINT8,    ACPI_MADT7_OFFSET (LocalSapicEid),          "Local Sapic EID"},
    {ACPI_DMT_UINT24,   ACPI_MADT7_OFFSET (Reserved),               "Reserved"},
    {ACPI_DMT_UINT32,   ACPI_MADT7_FLAG_OFFSET (Reserved,0),        "Flags (decoded below)"},
    {ACPI_DMT_FLAG0,    ACPI_MADT7_FLAG_OFFSET (Reserved,0),        "Processor Enabled"},
    {ACPI_DMT_UINT32,   ACPI_MADT7_OFFSET (Uid),                    "Processor UID"},
    {ACPI_DMT_STRING,   ACPI_MADT7_OFFSET (UidString),              "Processor UID"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};

/* 8: Platform Interrupt Source */

ACPI_DMTABLE_INFO           AcpiDmTableInfoMadt8[] =
{
    {ACPI_DMT_UINT16,   ACPI_MADT8_FLAG_OFFSET (Length,0),          "Flags (decoded below)"},
    {ACPI_DMT_FLAGS0,   ACPI_MADT8_FLAG_OFFSET (Length,0),          "Polarity"},
    {ACPI_DMT_FLAGS2,   ACPI_MADT8_FLAG_OFFSET (Length,0),          "Trigger Mode"},
    {ACPI_DMT_UINT8,    ACPI_MADT8_OFFSET (InterruptType),          "InterruptType"},
    {ACPI_DMT_UINT8,    ACPI_MADT8_OFFSET (ProcessorId),            "Processor ID"},
    {ACPI_DMT_UINT8,    ACPI_MADT8_OFFSET (ProcessorEid),           "Processor EID"},
    {ACPI_DMT_UINT8,    ACPI_MADT8_OFFSET (IoSapicVector),          "I/O Sapic Vector"},
    {ACPI_DMT_UINT32,   ACPI_MADT8_OFFSET (Interrupt),              "Interrupt"},
    {ACPI_DMT_UINT32,   ACPI_MADT8_OFFSET (Flags),                  "Flags (decoded below)"},
    {ACPI_DMT_FLAG0,    ACPI_MADT8_OFFSET (Flags),                  "CPEI Override"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};


/*******************************************************************************
 *
 * MCFG - PCI Memory Mapped Configuration table and sub-table
 *
 ******************************************************************************/

ACPI_DMTABLE_INFO           AcpiDmTableInfoMcfg[] =
{
    {ACPI_DMT_UINT64,   ACPI_MCFG_OFFSET (Reserved),                "Reserved"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};

ACPI_DMTABLE_INFO           AcpiDmTableInfoMcfg0[] =
{
    {ACPI_DMT_UINT64,   ACPI_MCFG0_OFFSET (BaseAddress),            "Base Address"},
    {ACPI_DMT_UINT16,   ACPI_MCFG0_OFFSET (PciSegment),             "Segment Group Number"},
    {ACPI_DMT_UINT8,    ACPI_MCFG0_OFFSET (StartBusNumber),         "Start Bus Number"},
    {ACPI_DMT_UINT8,    ACPI_MCFG0_OFFSET (EndBusNumber),           "End Bus Number"},
    {ACPI_DMT_UINT32,   ACPI_MCFG0_OFFSET (Reserved),               "Reserved"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};


/*******************************************************************************
 *
 * SBST - Smart Battery Specification Table
 *
 ******************************************************************************/

ACPI_DMTABLE_INFO           AcpiDmTableInfoSbst[] =
{
    {ACPI_DMT_UINT32,   ACPI_SBST_OFFSET (WarningLevel),            "Warning Level"},
    {ACPI_DMT_UINT32,   ACPI_SBST_OFFSET (LowLevel),                "Low Level"},
    {ACPI_DMT_UINT32,   ACPI_SBST_OFFSET (CriticalLevel),           "Critical Level"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};


/*******************************************************************************
 *
 * SLIT - System Locality Information Table
 *
 ******************************************************************************/

ACPI_DMTABLE_INFO           AcpiDmTableInfoSlit[] =
{
    {ACPI_DMT_UINT64,   ACPI_SLIT_OFFSET (LocalityCount),          "Localities"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};


/*******************************************************************************
 *
 * SPCR - Serial Port Console Redirection table
 *
 ******************************************************************************/

ACPI_DMTABLE_INFO           AcpiDmTableInfoSpcr[] =
{
    {ACPI_DMT_UINT8,    ACPI_SPCR_OFFSET (InterfaceType),           "Interface Type"},
    {ACPI_DMT_UINT24,   ACPI_SPCR_OFFSET (Reserved),                "Reserved"},
    {ACPI_DMT_GAS,      ACPI_SPCR_OFFSET (SerialPort),              "Serial Port Register"},
    {ACPI_DMT_UINT8,    ACPI_SPCR_OFFSET (InterruptType),           "Interrupt Type"},
    {ACPI_DMT_UINT8,    ACPI_SPCR_OFFSET (PcInterrupt),             "PCAT-compatible IRQ"},
    {ACPI_DMT_UINT32,   ACPI_SPCR_OFFSET (Interrupt),               "Interrupt"},
    {ACPI_DMT_UINT8,    ACPI_SPCR_OFFSET (BaudRate),                "Baud Rate"},
    {ACPI_DMT_UINT8,    ACPI_SPCR_OFFSET (Parity),                  "Parity"},
    {ACPI_DMT_UINT8,    ACPI_SPCR_OFFSET (StopBits),                "Stop Bits"},
    {ACPI_DMT_UINT8,    ACPI_SPCR_OFFSET (FlowControl),             "Flow Control"},
    {ACPI_DMT_UINT8,    ACPI_SPCR_OFFSET (TerminalType),            "Terminal Type"},
    {ACPI_DMT_UINT8,    ACPI_SPCR_OFFSET (Reserved2),               "Reserved"},
    {ACPI_DMT_UINT16,   ACPI_SPCR_OFFSET (PciDeviceId),             "PCI Device ID"},
    {ACPI_DMT_UINT16,   ACPI_SPCR_OFFSET (PciVendorId),             "PCI Vendor ID"},
    {ACPI_DMT_UINT8,    ACPI_SPCR_OFFSET (PciBus),                  "PCI Bus"},
    {ACPI_DMT_UINT8,    ACPI_SPCR_OFFSET (PciDevice),               "PCI Device"},
    {ACPI_DMT_UINT8,    ACPI_SPCR_OFFSET (PciFunction),             "PCI Function"},
    {ACPI_DMT_UINT32,   ACPI_SPCR_OFFSET (PciFlags),                "PCI Flags"},
    {ACPI_DMT_UINT8,    ACPI_SPCR_OFFSET (PciSegment),              "PCI Segment"},
    {ACPI_DMT_UINT32,   ACPI_SPCR_OFFSET (Reserved3),               "Reserved"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};


/*******************************************************************************
 *
 * SPMI - Server Platform Management Interface table
 *
 ******************************************************************************/

ACPI_DMTABLE_INFO           AcpiDmTableInfoSpmi[] =
{
    {ACPI_DMT_UINT8,    ACPI_SPMI_OFFSET (Reserved),                "Reserved"},
    {ACPI_DMT_UINT8,    ACPI_SPMI_OFFSET (InterfaceType),           "Interface Type"},
    {ACPI_DMT_UINT16,   ACPI_SPMI_OFFSET (SpecRevision),            "IPMI Spec Version"},
    {ACPI_DMT_UINT8,    ACPI_SPMI_OFFSET (InterruptType),           "Interrupt Type"},
    {ACPI_DMT_UINT8,    ACPI_SPMI_OFFSET (GpeNumber),               "GPE Number"},
    {ACPI_DMT_UINT8,    ACPI_SPMI_OFFSET (Reserved2),               "Reserved"},
    {ACPI_DMT_UINT8,    ACPI_SPMI_OFFSET (PciDeviceFlag),           "PCI Device Flag"},
    {ACPI_DMT_UINT32,   ACPI_SPMI_OFFSET (Interrupt),               "Interrupt"},
    {ACPI_DMT_GAS,      ACPI_SPMI_OFFSET (IpmiRegister),            "IPMI Register"},
    {ACPI_DMT_UINT8,    ACPI_SPMI_OFFSET (PciSegment),              "PCI Segment"},
    {ACPI_DMT_UINT8,    ACPI_SPMI_OFFSET (PciBus),                  "PCI Bus"},
    {ACPI_DMT_UINT8,    ACPI_SPMI_OFFSET (PciDevice),               "PCI Device"},
    {ACPI_DMT_UINT8,    ACPI_SPMI_OFFSET (PciFunction),             "PCI Function"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};


/*******************************************************************************
 *
 * SRAT - System Resource Affinity Table and sub-tables
 *
 ******************************************************************************/

ACPI_DMTABLE_INFO           AcpiDmTableInfoSrat[] =
{
    {ACPI_DMT_UINT32,   ACPI_SRAT_OFFSET (Reserved1),               "Reserved1"},
    {ACPI_DMT_UINT64,   ACPI_SRAT_OFFSET (Reserved2),               "Reserved2"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};

ACPI_DMTABLE_INFO           AcpiDmTableInfoSrat0[] =
{
    {ACPI_DMT_SRAT,     ACPI_SRAT0_OFFSET (Type),                   "Sub-Table Type"},
    {ACPI_DMT_UINT8,    ACPI_SRAT0_OFFSET (Length),                 "Length"},
    {ACPI_DMT_UINT8,    ACPI_SRAT0_OFFSET (ProximityDomainLo),      "Proximity Domain Low(8)"},
    {ACPI_DMT_UINT8,    ACPI_SRAT0_OFFSET (ApicId),                 "Apic ID"},
    {ACPI_DMT_UINT32,   ACPI_SRAT0_FLAG_OFFSET (ApicId,0),          "Flags (decoded below)"},
    {ACPI_DMT_FLAG0,    ACPI_SRAT0_FLAG_OFFSET (ApicId,0),          "Enabled"},
    {ACPI_DMT_UINT8,    ACPI_SRAT0_OFFSET (LocalSapicEid),          "Local Sapic EID"},
    {ACPI_DMT_UINT24,   ACPI_SRAT0_OFFSET (ProximityDomainHi),      "Proximity Domain High(24)"},
    {ACPI_DMT_UINT32,   ACPI_SRAT0_OFFSET (Reserved4),              "Reserved"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};

ACPI_DMTABLE_INFO           AcpiDmTableInfoSrat1[] =
{
    {ACPI_DMT_SRAT,     ACPI_SRAT1_OFFSET (Type),                   "Sub-Table Type"},
    {ACPI_DMT_UINT8,    ACPI_SRAT1_OFFSET (Length),                 "Length"},
    {ACPI_DMT_UINT32,   ACPI_SRAT1_OFFSET (ProximityDomain),        "Proximity Domain"},
    {ACPI_DMT_UINT16,   ACPI_SRAT1_OFFSET (Reserved3),              "Reserved"},
    {ACPI_DMT_UINT64,   ACPI_SRAT1_OFFSET (BaseAddress),            "Base Address"},
    {ACPI_DMT_UINT64,   ACPI_SRAT1_OFFSET (AddressLength),          "Address Length"},
    {ACPI_DMT_UINT32,   ACPI_SRAT1_OFFSET (Reserved4),              "Reserved"},
    {ACPI_DMT_UINT32,   ACPI_SRAT1_FLAG_OFFSET (Reserved4,0),       "Flags (decoded below)"},
    {ACPI_DMT_FLAG0,    ACPI_SRAT1_FLAG_OFFSET (Reserved4,0),       "Enabled"},
    {ACPI_DMT_FLAG1,    ACPI_SRAT1_FLAG_OFFSET (Reserved4,0),       "Hot Pluggable"},
    {ACPI_DMT_FLAG2,    ACPI_SRAT1_FLAG_OFFSET (Reserved4,0),       "Non-Volatile"},
    {ACPI_DMT_UINT64,   ACPI_SRAT1_OFFSET (Reserved6),              "Reserved"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};


/*******************************************************************************
 *
 * TCPA - Trusted Computing Platform Alliance table
 *
 ******************************************************************************/

ACPI_DMTABLE_INFO           AcpiDmTableInfoTcpa[] =
{
    {ACPI_DMT_UINT16,   ACPI_TCPA_OFFSET (Reserved),                "Reserved"},
    {ACPI_DMT_UINT32,   ACPI_TCPA_OFFSET (MaxLogLength),            "Max Event Log Length"},
    {ACPI_DMT_UINT64,   ACPI_TCPA_OFFSET (LogAddress),              "Event Log Address"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};


/*******************************************************************************
 *
 * WDRT - Watchdog Resource Table
 *
 ******************************************************************************/

ACPI_DMTABLE_INFO           AcpiDmTableInfoWdrt[] =
{
    {ACPI_DMT_UINT32,   ACPI_WDRT_OFFSET (HeaderLength),            "Header Length"},
    {ACPI_DMT_UINT8,    ACPI_WDRT_OFFSET (PciSegment),              "PCI Segment"},
    {ACPI_DMT_UINT8,    ACPI_WDRT_OFFSET (PciBus),                  "PCI Bus"},
    {ACPI_DMT_UINT8,    ACPI_WDRT_OFFSET (PciDevice),               "PCI Device"},
    {ACPI_DMT_UINT8,    ACPI_WDRT_OFFSET (PciFunction),             "PCI Function"},
    {ACPI_DMT_UINT32,   ACPI_WDRT_OFFSET (TimerPeriod),             "Timer Period"},
    {ACPI_DMT_UINT32,   ACPI_WDRT_OFFSET (MaxCount),                "Max Count"},
    {ACPI_DMT_UINT32,   ACPI_WDRT_OFFSET (MinCount),                "Min Count"},
    {ACPI_DMT_UINT8,    ACPI_WDRT_OFFSET (Flags),                   "Flags (decoded below)"},
    {ACPI_DMT_FLAG0,    ACPI_WDRT_OFFSET (Flags),                   "Enabled"},
    {ACPI_DMT_FLAG7,    ACPI_WDRT_OFFSET (Flags),                   "Stopped When Asleep"},
    {ACPI_DMT_UINT24,   ACPI_WDRT_OFFSET (Reserved),                "Reserved"},
    {ACPI_DMT_UINT32,   ACPI_WDRT_OFFSET (Entries),                 "Watchdog Entries"},
    {ACPI_DMT_EXIT,     0,                                          NULL}
};

