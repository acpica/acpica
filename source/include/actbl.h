
/******************************************************************************
 * 
 * Name: acpitables.h - Table data structures defined in ACPI specification
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

#ifndef __ACPITYPE_H__
#define __ACPITYPE_H__

typedef UINT32              IO_ADDRESS;             /* Only for clarity in declarations */

/*
 *  Values for description table header signatures
 */

#define RSDP_SIG            "RSD PTR "              /* RSDT Pointer signature */
#define APIC_SIG            "APIC"                  /* Multiple APIC Description Table */
#define DSDT_SIG            "DSDT"                  /* Differentiated Sys Descrip Table */
#define FACP_SIG            "FACP"                  /* Fixed ACPI Description Table */
#define FACS_SIG            "FACS"                  /* Firmware ACPI Control Structure */
#define PSDT_SIG            "PSDT"                  /* Persistent Sys Description Table */
#define RSDT_SIG            "RSDT"                  /* Root System Description Table */
#define SSDT_SIG            "SSDT"                  /* Secondary Sys Description Table */
#define SBDT_SIG            "SBDT"                  /* Smart Batter Description Table */


#define GL_OWNED            0x02                    /* Ownership of global lock is bit 1 */

/* values of Mapic.Model */

#define DUAL_PIC            0
#define MULTIPLE_APIC       1

/* values of Type in APIC_HEADER */

#define APIC_PROC           0
#define APIC_IO             1



typedef struct  /* Root System Descriptor Pointer */
{                                           
    char                    Signature [8];          /* contains "RSD PTR " */
    UINT8                   Checksum;               /* to make sum of struct == 0 */
    char                    OemId [6];              /* OEM identification */
    UINT8                   Reserved;               /* reserved - must be zero */
    UINT32                  RsdtPhysicalAddress;    /* physical address of RSDT */

} ROOT_SYSTEM_DESCRIPTOR_POINTER;


typedef struct  /* ACPI common table header */
{                                           
    char                    Signature [4];          /* identifies type of table */
    UINT32                  Length;                 /* length of table, in bytes,
                                                     * including header */
    UINT8                   Revision;               /* specification minor version # */
    UINT8                   Checksum;               /* to make sum of entire table == 0 */
    char                    OemId [6];              /* OEM identification */
    char                    OemTableId [8];         /* OEM table identification */
    UINT32                  OemRevision;            /* OEM revision number */
    char                    AslCompilerId [4];      /* ASL compiler vendor ID */
    UINT32                  AslCompilerRevision;    /* ASL compiler revision number */

} ACPI_TABLE_HEADER;


typedef struct  /* Root System Description Table */
{                                                   
    ACPI_TABLE_HEADER       header;                 /* table header */
    UINT32                  TableOffsetEntry [1];   /* array of pointers to other
                                                     * tables' headers */
} ROOT_SYSTEM_DESCRIPTION_TABLE;



typedef struct  /* Firmware ACPI Control Structure */
{                                           
    char                    Signature[4];           /* signature "FACS" */
    UINT32                  Length;                 /* length of structure, in bytes */
    UINT32                  HardwareSignature;      /* hardware configuration signature */
    UINT32                  FirmwareWakingVector;   /* ACPI OS waking vector */
    UINT32                  GlobalLock;             /* Global Lock */
    UINT16_BIT              S4Bios_f        : 1;    /* Indicates if S4BIOS support is present */
    UINT16_BIT              Reserved1       : 15;   /* must be 0 */
    UINT16                  Reserved2;              /* must be 0 */
    UINT8                   Resverved3 [40];        /* reserved - must be zero */

} FIRMWARE_ACPI_CONTROL_STRUCTURE;



typedef struct  /* Fixed ACPI Description Table */
{                                           
    ACPI_TABLE_HEADER       header;                 /* table header */
    UINT32                  FirmwareCtrl;           /* Physical addesss of FACS */
    UINT32                  Dsdt;                   /* Physical address of DSDT */
    UINT8                   Model;                  /* System Interrupt Model */
    UINT8                   Reserved1;              /* reserved */
    UINT16                  SciInt;                 /* System vector of SCI interrupt */
    IO_ADDRESS              SmiCmd;                 /* Port address of SMI command port */
    UINT8                   AcpiEnable;             /* value to write to smi_cmd to enable ACPI */
    UINT8                   AcpiDisable;            /* value to write to smi_cmd to disable ACPI */
    UINT8                   S4BiosReq;              /* Value to write to SMI CMD to enter S4BIOS state */
    UINT8                   Reserved2;              /* reserved - must be zero */
    IO_ADDRESS              Pm1aEvtBlk;             /* Port address of Power Mgt 1a Event Reg Blk */
    IO_ADDRESS              Pm1bEvtBlk;             /* Port address of Power Mgt 1b Event Reg Blk */
    IO_ADDRESS              Pm1aCntBlk;             /* Port address of Power Mgt 1a Control Reg Blk */
    IO_ADDRESS              Pm1bCntBlk;             /* Port address of Power Mgt 1b Control Reg Blk */
    IO_ADDRESS              Pm2CntBlk;              /* Port address of Power Mgt 2 Control Reg Blk */
    IO_ADDRESS              PmTmrBlk;               /* Port address of Power Mgt Timer Ctrl Reg Blk */
    IO_ADDRESS              Gpe0Blk;                /* Port addr of General Purpose Event 0 Reg Blk */
    IO_ADDRESS              Gpe1Blk;                /* Port addr of General Purpose Event 1 Reg Blk */
    UINT8                   Pm1EvtLen;              /* Byte Length of ports at pm1X_evt_blk */
    UINT8                   Pm1CntLen;              /* Byte Length of ports at pm1X_cnt_blk */
    UINT8                   Pm2CntLen;              /* Byte Length of ports at pm2_cnt_blk */
    UINT8                   PmTmLen;                /* Byte Length of ports at pm_tm_blk */
    UINT8                   Gpe0BlkLen;             /* Byte Length of ports at gpe0_blk */
    UINT8                   Gpe1BlkLen;             /* Byte Length of ports at gpe1_blk */
    UINT8                   Gpe1Base;               /* offset in gpe model where gpe1 events start */
    UINT8                   Reserved3;              /* reserved */
    UINT16                  PLvl2Lat;               /* worst case HW latency to enter/exit C2 state */
    UINT16                  PLvl3Lat;               /* worst case HW latency to enter/exit C3 state */
    UINT16                  FlushSize;              /* Size of area read to flush caches */
    UINT16                  FlushStride;            /* Stride used in flushing caches */
    UINT8                   DutyOffset;             /* bit location of duty cycle field in p_cnt reg */
    UINT8                   DutyWidth;              /* bit width of duty cycle field in p_cnt reg */
    UINT8                   DayAlrm;                /* index to day-of-month alarm in RTC CMOS RAM */
    UINT8                   MonAlrm;                /* index to month-of-year alarm in RTC CMOS RAM */
    UINT8                   Century;                /* index to century in RTC CMOS RAM */
    UINT8                   Reserved4;              /* reserved */
    UINT8                   Reserved4a;             /* reserved */
    UINT8                   Reserved4b;             /* reserved */
    UINT16_BIT              WBInvd          : 1;    /* wbinvd instruction works properly */
    UINT16_BIT              WBInvdFlush     : 1;    /* wbinvd flushes but does not invalidate */
    UINT16_BIT              ProcC1          : 1;    /* all processors support C1 state */
    UINT16_BIT              PLvl2Up         : 1;    /* C2 state works on MP system */
    UINT16_BIT              PwrButton       : 1;    /* Power button is handled as a generic feature */
    UINT16_BIT              SleepButton     : 1;    /* Sleep button is handled as a generic feature, or not present */
    UINT16_BIT              FixedRTC        : 1;    /* RTC wakeup stat not in fixed register space */
    UINT16_BIT              RTCS4           : 1;    /* RTC wakeup stat not possible from S4 */
    UINT16_BIT              TmrValExt       : 1;    /* tmr_val is 32 bits */
    UINT16_BIT              Reserved5       : 7;    /* reserved - must be zero */
    UINT16                  Reserved6;              /* reserved - must be zero */

}  FIXED_ACPI_DESCRIPTION_TABLE;


typedef struct  /* APIC Table */
{                                           
    ACPI_TABLE_HEADER       header;                 /* table header */
    UINT32                  LocalApicAddress;       /* Physical address for accessing local APICs */
    UINT16_BIT              PCATCompat      : 1;    /* a one indicates system also has dual 8259s */
    UINT16_BIT              Reserved1       : 15;
    UINT16                  Reserved2;

} APIC_TABLE;


typedef struct  /* APIC Header */
{
    UINT8                   Type;                   /* APIC type.  Either APIC_PROC or APIC_IO */
    UINT8                   Length;                 /* Length of APIC structure */

} APIC_HEADER;


typedef struct  /* Processor APIC */
{
    APIC_HEADER             header;
    UINT8                   ProcessorApicId;        /* ACPI processor id */
    UINT8                   LocalApicId;            /* processor's local APIC id */
    UINT16_BIT              ProcessorEnabled: 1;    /* Processor is usable if set */
    UINT16_BIT              Reserved1       : 15;
    UINT16                  Reserved2;

} PROCESSOR_APIC;


typedef struct  /* IO APIC */
{
    APIC_HEADER             header;
    UINT8                   IoApicId;               /* I/O APIC ID */
    UINT8                   Reserved;               /* reserved - must be zero */
    UINT32                  IoApicAddress;          /* APIC's physical address */
    UINT32                  Vector;                 /* interrupt vector index where INTI
                                                     * lines start */
} IO_APIC;


typedef struct  /* Smart Battery Description Table */
{
    ACPI_TABLE_HEADER       header;
    UINT32                  WarningLevel;
    UINT32                  LowLevel;
    UINT32                  CriticalLevel;

} SMART_BATTERY_DESCRIPTION_TABLE;



#endif /* __ACPITYPE_H__ */
