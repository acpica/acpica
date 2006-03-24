/******************************************************************************
 *
 * Name: actbl.h - Table data structures defined in ACPI specification
 *       $Revision: 1.75 $
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

#ifndef __ACTBL_H__
#define __ACTBL_H__


/*
 * Note about bitfields: The UINT8 type is used for bitfields in ACPI tables.
 * This is the only type that is even remotely portable. Anything else is not
 * portable, so do not use any other bitfield types.
 */


/*
 *  Values for description table header signatures
 */
#define RSDP_NAME               "RSDP"
#define RSDP_SIG                "RSD PTR "  /* RSDT Pointer signature */
#define APIC_SIG                "APIC"      /* Multiple APIC Description Table */
#define DSDT_SIG                "DSDT"      /* Differentiated System Description Table */
#define FADT_SIG                "FACP"      /* Fixed ACPI Description Table */
#define FACS_SIG                "FACS"      /* Firmware ACPI Control Structure */
#define PSDT_SIG                "PSDT"      /* Persistent System Description Table */
#define RSDT_SIG                "RSDT"      /* Root System Description Table */
#define XSDT_SIG                "XSDT"      /* Extended  System Description Table */
#define SSDT_SIG                "SSDT"      /* Secondary System Description Table */
#define SBST_SIG                "SBST"      /* Smart Battery Specification Table */
#define SPIC_SIG                "SPIC"      /* IOSAPIC table */
#define BOOT_SIG                "BOOT"      /* Boot table */

#define GL_OWNED                0x02        /* Ownership of global lock is bit 1 */


/*
 * Common table types.  The base code can remain
 * constant if the underlying tables are changed
 */
#define FADT_DESCRIPTOR         FADT_DESCRIPTOR_REV2


/*******************************************************************************
 *
 * ACPI Version-independent tables
 *
 * The tables that are specific to ACPI versions (1.0, 2.0, etc.)
 * are in separate files.
 *
 * The RSDP and FACS do not use the common ACPI table header. All other ACPI
 * tables use the header.
 *
 ******************************************************************************/

/*
 * All tables and structures must be byte-packed to match the ACPI
 * specification, since the tables are provided by the system BIOS
 */
#pragma pack(1)

/*
 * RSDP - Root System Description Pointer (Signature is "RSD PTR ")
 */
typedef struct rsdp_descriptor
{
    char                    Signature[8];           /* ACPI signature, contains "RSD PTR " */
    UINT8                   Checksum;               /* ACPI 1.0 checksum */
    char                    OemId[6];               /* OEM identification */
    UINT8                   Revision;               /* Must be (0) for ACPI 1.0 or (2) for ACPI 2.0+ */
    UINT32                  RsdtPhysicalAddress;    /* 32-bit physical address of the RSDT */
    UINT32                  Length;                 /* Table length in bytes, including header (ACPI 2.0+) */
    UINT64                  XsdtPhysicalAddress;    /* 64-bit physical address of the XSDT (ACPI 2.0+) */
    UINT8                   ExtendedChecksum;       /* Checksum of entire table (ACPI 2.0+) */
    char                    Reserved[3];            /* Reserved, must be zero */

} RSDP_DESCRIPTOR;


/*
 * FACS - Firmware ACPI Control Structure (FACS)
 */
typedef struct facs_descriptor
{
    char                    Signature[4];           /* ASCII table signature */
    UINT32                  Length;                 /* Length of structure, in bytes */
    UINT32                  HardwareSignature;      /* Hardware configuration signature */
    UINT32                  FirmwareWakingVector;   /* 32-bit physical address of the Firmware Waking Vector. */
    UINT32                  GlobalLock;             /* Global Lock used to synchronize access to shared hardware resources */

    struct /* Flags (32 bits) */
    {
        UINT8                   S4Bios_f        : 1;    /* 00:    S4BIOS support is present */
        UINT8                                   : 7;    /* 01-07: Reserved, must be zero */
        UINT8                   Reserved[3];            /* 08-31: Reserved, must be zero */
    } Flags;

    UINT64                  XFirmwareWakingVector;  /* 64-bit version of the Firmware Waking Vector (ACPI 2.0+) */
    UINT8                   Version;                /* Version of this table (ACPI 2.0+) */
    UINT8                   Reserved[31];           /* Reserved, must be zero */

} FACS_DESCRIPTOR;


/*
 * Common FACS - This is an FACS structure used for internal use only
 */
typedef struct acpi_common_facs 
{
    UINT32                  *GlobalLock;
    UINT64                  *FirmwareWakingVector;
    UINT8                   VectorWidth;

} ACPI_COMMON_FACS;


/*
 * ACPI Table Header. This common header is used by all tables
 * except the RSDP and FACS
 *
 * Macro for inclusion into other ACPI tables, struct definition for 
 * direct addressing of individual fields
 */
#define ACPI_TABLE_HEADER_DEF \
    char                    Signature[4];           /* ASCII table signature */\
    UINT32                  Length;                 /* Length of table in bytes, including this header */\
    UINT8                   Revision;               /* ACPI Specification minor version # */\
    UINT8                   Checksum;               /* To make sum of entire table == 0 */\
    char                    OemId[6];               /* ASCII OEM identification */\
    char                    OemTableId[8];          /* ASCII OEM table identification */\
    UINT32                  OemRevision;            /* OEM revision number */\
    char                    AslCompilerId[4];       /* ASCII ASL compiler vendor ID */\
    UINT32                  AslCompilerRevision;    /* ASL compiler version */

typedef struct acpi_table_header
{
    ACPI_TABLE_HEADER_DEF

} ACPI_TABLE_HEADER;


/*
 * GAS - Generic Address Structure (ACPI 2.0+)
 */
typedef struct acpi_generic_address
{
    UINT8                   AddressSpaceId;         /* Address space where struct or register exists. */
    UINT8                   RegisterBitWidth;       /* Size in bits of given register */
    UINT8                   RegisterBitOffset;      /* Bit offset within the register */
    UINT8                   AccessWidth;            /* Minimum Access size (ACPI 3.0) */
    UINT64                  Address;                /* 64-bit address of struct or register */

} ACPI_GENERIC_ADDRESS;


/*
 * RSDT - Root System Description Table
 */
typedef struct rsdt_descriptor
{
    ACPI_TABLE_HEADER_DEF
    UINT32                  TableOffsetEntry[1];    /* Array of pointers to ACPI tables */

} RSDT_DESCRIPTOR;


/*
 * XSDT - Extended System Description Table (ACPI 2.0+)
 */
typedef struct xsdt_descriptor
{
    ACPI_TABLE_HEADER_DEF
    UINT64                  TableOffsetEntry[1];    /* Array of pointers to ACPI tables */

} XSDT_DESCRIPTOR;


/*******************************************************************************
 *
 * Additional ACPI Tables
 *
 * These tables are not consumed directly by the ACPICA subsystem, but are
 * included here to support device drivers and the AML disassembler.
 *
 ******************************************************************************/

/*
 * BOOT - Simple Boot Flag Table
 */
typedef struct acpi_table_boot
{
    ACPI_TABLE_HEADER_DEF
    UINT8                   CmosIndex;          /* Index in CMOS RAM for the boot register */
    UINT8                   Reserved[3];

} ACPI_TABLE_BOOT;


/*
 * DBGP - Debug Port
 */
typedef struct acpi_table_dbgp
{
    ACPI_TABLE_HEADER_DEF
    UINT8                   InterfaceType;      /* 0=full 16550, 1=subset of 16550 */
    UINT8                   Reserved[3];
    ACPI_GENERIC_ADDRESS    DebugPort;

} ACPI_TABLE_DBGP;


/*
 * ECDT - Embedded Controller Boot Resources Table
 */
typedef struct ec_boot_resources
{
    ACPI_TABLE_HEADER_DEF
    ACPI_GENERIC_ADDRESS    EcControl;          /* Address of EC command/status register */
    ACPI_GENERIC_ADDRESS    EcData;             /* Address of EC data register */
    UINT32                  Uid;                /* Unique ID - must be same as the EC _UID method */
    UINT8                   GpeBit;             /* The GPE for the EC */
    UINT8                   EcId[1];            /* Full namepath of the EC in the ACPI namespace */

} EC_BOOT_RESOURCES;


/*
 * HPET - High Precision Event Timer table
 */
typedef struct acpi_hpet_table
{
    ACPI_TABLE_HEADER_DEF
    UINT32                  HardwareId;         /* Hardware ID of event timer block */
    ACPI_GENERIC_ADDRESS    BaseAddress;        /* Address of event timer block */
    UINT8                   HpetNumber;         /* HPET sequence number */
    UINT16                  ClockTick;          /* Main counter min tick, periodic mode */

    struct  /* Flags (8 bits) */
    {
        UINT8                   PageProtect     :1; /* 00:    No page protection */
        UINT8                   PageProtect4K   :1; /* 01:    4KB page protected */
        UINT8                   PageProtect64K  :1; /* 02:    64KB page protected */
        UINT8                                   :5; /* 03-07: Reserved, must be zero */
    } Flags;

} HPET_TABLE;


/*
 * MCFG - PCI Memory Mapped Configuration table
 */
typedef struct acpi_table_mcfg
{
    ACPI_TABLE_HEADER_DEF
    UINT8                   Reserved[8];

} ACPI_TABLE_MCFG;

typedef struct acpi_mcfg_allocation
{
    UINT64                  BaseAddress;        /* Base address, processor-relative */
    UINT16                  PciSegment;         /* PCI segment group number */
    UINT8                   StartBusNumber;     /* Starting PCI Bus number */
    UINT8                   EndBusNumber;       /* Final PCI Bus number */
    UINT32                  Reserved; 

} ACPI_MCFG_ALLOCATION;


/*
 * SBST - Smart Battery Specification Table
 */
typedef struct smart_battery_table
{
    ACPI_TABLE_HEADER_DEF
    UINT32                  WarningLevel;
    UINT32                  LowLevel;
    UINT32                  CriticalLevel;

} SMART_BATTERY_TABLE;


/*
 * SLIT - System Locality Distance Information Table
 */
typedef struct system_locality_info
{
    ACPI_TABLE_HEADER_DEF
    UINT64                  LocalityCount;
    UINT8                   Entry[1][1];

} SYSTEM_LOCALITY_INFO;


/*
 * TCPA - Trusted Computing Platform Alliance table
 */
typedef struct acpi_table_tcpa
{
    ACPI_TABLE_HEADER_DEF
    UINT16                  Reserved;
    UINT32                  MaxLogLength;       /* Maximum length for the event log area */
    UINT64                  LogAddress;         /* Address of the event log area */

} ACPI_TABLE_TCPA;


/*
 * SPCR - Serial Port Console Redirection table
 */
typedef struct acpi_table_spcr
{
    ACPI_TABLE_HEADER_DEF
    UINT8                   InterfaceType;      /* 0=full 16550, 1=subset of 16550 */
    UINT8                   Reserved[3];
    ACPI_GENERIC_ADDRESS    SerialPort;
    UINT8                   InterruptType;
    UINT8                   PcInterrupt;
    UINT32                  Interrupt;
    UINT8                   BaudRate;
    UINT8                   Parity;
    UINT8                   StopBits;
    UINT8                   FlowControl;
    UINT8                   TerminalType;
    UINT8                   Reserved2;
    UINT16                  PciDeviceId;
    UINT16                  PciVendorId;
    UINT8                   PciBus;
    UINT8                   PciDevice;
    UINT8                   PciFunction;
    UINT32                  PciFlags;
    UINT8                   PciSegment;
    UINT32                  Reserved3;

} ACPI_TABLE_SPCR;


/*
 * SPMI - Server Platform Management Interface table
 */
typedef struct acpi_table_spmi
{
    ACPI_TABLE_HEADER_DEF
    UINT8                   Reserved;
    UINT8                   InterfaceType;
    UINT16                  SpecRevision;       /* Version of IPMI */
    UINT8                   InterruptType;
    UINT8                   GpeNumber;          /* GPE assigned */
    UINT8                   Reserved2;
    UINT8                   PciDeviceFlag;
    UINT32                  Interrupt;
    ACPI_GENERIC_ADDRESS    IpmiRegister;
    UINT8                   PciSegment;
    UINT8                   PciBus;
    UINT8                   PciDevice;
    UINT8                   PciFunction;

} ACPI_TABLE_SPMI;


/*
 * WDRT - Watchdog Resource Table
 */
typedef struct acpi_table_wdrt
{
    ACPI_TABLE_HEADER_DEF
    UINT32                  HeaderLength;       /* Watchdog Header Length */
    UINT8                   PciSegment;         /* PCI Segment number */
    UINT8                   PciBus;             /* PCI Bus number */
    UINT8                   PciDevice;          /* PCI Device number */
    UINT8                   PciFunction;        /* PCI Function number */
    UINT32                  TimerPeriod;        /* Period of one timer count (msec) */
    UINT32                  MaxCount;           /* Maximum counter value supported */
    UINT32                  MinCount;           /* Minimum counter value */

    struct  /* Flags (8 bits) */
    {
        UINT8                   Enabled     :1; /* 00:    Timer enabled */
        UINT8                               :6; /* 01-06: Reserved */
        UINT8                   SleepStop   :1; /* 07:    Timer stopped in sleep state */
    } Flags;

    UINT8                   Reserved[3];
    UINT32                  Entries;            /* Number of watchdog entries that follow */

} ACPI_TABLE_WDRT;


/*******************************************************************************
 *
 * These complex ACPI tables have additional subtables
 *
 ******************************************************************************/

/*
 * MADT - Multiple APIC Description Table
 */
typedef struct multiple_apic_table
{
    ACPI_TABLE_HEADER_DEF
    UINT32                  LocalApicAddress;       /* Physical address of local APIC */

    struct /* Flags (32 bits) */
    {
        UINT8                   PCATCompat      : 1;    /* 00:    System also has dual 8259s */
        UINT8                                   : 7;    /* 01-07: Reserved, must be zero */
        UINT8                   Reserved[3];            /* 08-31: Reserved, must be zero */
    } Flags;

} MULTIPLE_APIC_TABLE;

/* Values for MADT PCATCompat */

#define DUAL_PIC                0
#define MULTIPLE_APIC           1


/* Common MADT Sub-table header */

#define APIC_HEADER_DEF \
    UINT8                   Type; \
    UINT8                   Length;

typedef struct apic_header
{
    APIC_HEADER_DEF

} APIC_HEADER;

/* Values for Type in APIC_HEADER */

#define APIC_PROCESSOR          0
#define APIC_IO                 1
#define APIC_XRUPT_OVERRIDE     2
#define APIC_NMI                3
#define APIC_LOCAL_NMI          4
#define APIC_ADDRESS_OVERRIDE   5
#define APIC_IO_SAPIC           6
#define APIC_LOCAL_SAPIC        7
#define APIC_XRUPT_SOURCE       8
#define APIC_RESERVED           9           /* 9 and greater are reserved */


/* Common flag definitions  */

#define MPS_INTI_FLAGS      /* 16 bits */\
    struct \
    { \
        UINT8                   Polarity        : 2;    /* 00-01: Polarity of APIC input signals */\
        UINT8                   TriggerMode     : 2;    /* 02-03: Trigger mode of APIC input signals */\
        UINT8                                   : 4;    /* 04-07: Reserved, must be zero */\
        UINT8                   Reserved;               /* 08-15: Reserved, must be zero */\
    } IntiFlags;

#define LOCAL_APIC_FLAGS    /* 32 bits */\
    struct \
    { \
        UINT8                   ProcessorEnabled: 1;    /* 00:    Processor is usable if set */\
        UINT8                                   : 7;    /* 01-07: Reserved, must be zero */\
        UINT8                   Reserved[3];            /* 08-31: Reserved, must be zero */\
    } LapicFlags;

/* Values for MPS INTI flags */

#define POLARITY_CONFORMS       0
#define POLARITY_ACTIVE_HIGH    1
#define POLARITY_RESERVED       2
#define POLARITY_ACTIVE_LOW     3

#define TRIGGER_CONFORMS        0
#define TRIGGER_EDGE            1
#define TRIGGER_RESERVED        2
#define TRIGGER_LEVEL           3


/* Common MADT Sub-tables, correspond to Type in APIC_HEADER */

typedef struct madt_processor_apic
{
    APIC_HEADER_DEF
    UINT8                   ProcessorId;            /* ACPI processor id */
    UINT8                   LocalApicId;            /* Processor's local APIC id */
    LOCAL_APIC_FLAGS

} MADT_PROCESSOR_APIC;

typedef struct madt_io_apic
{
    APIC_HEADER_DEF
    UINT8                   IoApicId;               /* I/O APIC ID */
    UINT8                   Reserved;               /* Reserved - must be zero */
    UINT32                  Address;                /* APIC physical address */
    UINT32                  Interrupt;              /* Global system interrupt where INTI
                                                     * lines start */
} MADT_IO_APIC;

typedef struct madt_interrupt_override
{
    APIC_HEADER_DEF
    UINT8                   Bus;                    /* 0 - ISA */
    UINT8                   Source;                 /* Interrupt source (IRQ) */
    UINT32                  Interrupt;              /* Global system interrupt */
    MPS_INTI_FLAGS

} MADT_INTERRUPT_OVERRIDE;

typedef struct madt_nmi_source
{
    APIC_HEADER_DEF
    MPS_INTI_FLAGS
    UINT32                  Interrupt;              /* Global system interrupt */

} MADT_NMI_SOURCE;

typedef struct madt_local_apic_nmi
{
    APIC_HEADER_DEF
    UINT8                   ProcessorId;            /* ACPI processor id */
    MPS_INTI_FLAGS
    UINT8                   Lint;                   /* LINTn to which NMI is connected */

} MADT_LOCAL_APIC_NMI;

typedef struct madt_address_override
{
    APIC_HEADER_DEF
    UINT16                  Reserved;               /* Reserved, must be zero */
    UINT64                  Address;                /* APIC physical address */

} MADT_ADDRESS_OVERRIDE;

typedef struct madt_io_sapic
{
    APIC_HEADER_DEF
    UINT8                   IoSapicId;              /* I/O SAPIC ID */
    UINT8                   Reserved;               /* Reserved, must be zero */
    UINT32                  InterruptBase;          /* Glocal interrupt for SAPIC start */
    UINT64                  Address;                /* SAPIC physical address */

} MADT_IO_SAPIC;

typedef struct madt_local_sapic
{
    APIC_HEADER_DEF
    UINT8                   ProcessorId;            /* ACPI processor id */
    UINT8                   LocalSapicId;           /* SAPIC ID */
    UINT8                   LocalSapicEid;          /* SAPIC EID */
    UINT8                   Reserved[3];            /* Reserved, must be zero */
    LOCAL_APIC_FLAGS
    UINT32                  Uid;                    /* Numeric UID - ACPI 3.0 */
    char                    UidString[1];           /* String UID  - ACPI 3.0 */

} MADT_LOCAL_SAPIC;

typedef struct madt_interrupt_source
{
    APIC_HEADER_DEF
    MPS_INTI_FLAGS
    UINT8                   InterruptType;          /* 1=PMI, 2=INIT, 3=corrected */
    UINT8                   ProcessorId;            /* Processor ID */
    UINT8                   ProcessorEid;           /* Processor EID */
    UINT8                   IoSapicVector;          /* Vector value for PMI interrupts */
    UINT32                  Interrupt;              /* Global system interrupt */

    struct /* Flags (32 bits) */
    {                                        /* Interrupt Source Flags */
        UINT8                   CpeiOverride    :1;
        UINT8                                   :7;
        UINT8                   Reserved[3];
    } Flags;

} MADT_INTERRUPT_SOURCE;


/*
 * SRAT - System Resource Affinity Table
 */
typedef struct system_resource_affinity
{
    ACPI_TABLE_HEADER_DEF
    UINT32                  Reserved1;          /* Must be value '1' */
    UINT64                  Reserved2;          /* Reserved, must be zero */

} SYSTEM_RESOURCE_AFFINITY;


/* SRAT common sub-table header */

#define SRAT_SUBTABLE_HEADER \
    UINT8                   Type; \
    UINT8                   Length;

/* Values for Type above */

#define SRAT_CPU_AFFINITY       0
#define SRAT_MEMORY_AFFINITY    1


/* SRAT sub-tables */

typedef struct static_resource_alloc
{
    SRAT_SUBTABLE_HEADER
    UINT8                   ProximityDomainLo;
    UINT8                   ApicId;

    struct /* Flags (32 bits) */
    {
        UINT8                   Enabled         :1; /* 00:    Use affinity structure */
        UINT8                                   :7; /* 01-07: Reserved, must be zero */
        UINT8                   Reserved3[3];       /* 08-31: Reserved, must be zero */
    } Flags;

    UINT8                   LocalSapicEid;
    UINT8                   ProximityDomainHi[3];
    UINT32                  Reserved4;          /* Reserved, must be zero */

} STATIC_RESOURCE_ALLOC;

typedef struct memory_affinity
{
    SRAT_SUBTABLE_HEADER
    UINT32                  ProximityDomain;
    UINT16                  Reserved3;
    UINT64                  BaseAddress;
    UINT64                  AddressLength;
    UINT32                  Reserved4;

    struct /* Flags (32 bits) */
    {
        UINT8                   Enabled         :1; /* 00:    Use affinity structure */
        UINT8                   HotPluggable    :1; /* 01:    Memory region is hot pluggable */
        UINT8                   NonVolatile     :1; /* 02:    Memory is non-volatile */
        UINT8                                   :5; /* 03-07: Reserved, must be zero */
        UINT8                   Reserved5[3];       /* 08-31: Reserved, must be zero */
    } Flags;

    UINT64                  Reserved6;          /* Reserved, must be zero */

} MEMORY_AFFINITY;


/* Reset to default packing */

#pragma pack()

/*
 * Get the ACPI version-specific tables
 */
#include "actbl1.h"   /* Acpi 1.0 table definitions */
#include "actbl2.h"   /* Acpi 2.0 table definitions */


/*
 * ACPI Table information.  We save the table address, length,
 * and type of memory allocation (mapped or allocated) for each
 * table for 1) when we exit, and 2) if a new table is installed
 */
#define ACPI_MEM_NOT_ALLOCATED  0
#define ACPI_MEM_ALLOCATED      1
#define ACPI_MEM_MAPPED         2

/* Definitions for the Flags bitfield member of ACPI_TABLE_SUPPORT */

#define ACPI_TABLE_SINGLE       0x00
#define ACPI_TABLE_MULTIPLE     0x01
#define ACPI_TABLE_EXECUTABLE   0x02

#define ACPI_TABLE_ROOT         0x00
#define ACPI_TABLE_PRIMARY      0x10
#define ACPI_TABLE_SECONDARY    0x20
#define ACPI_TABLE_ALL          0x30
#define ACPI_TABLE_TYPE_MASK    0x30

/* Data about each known table type */

typedef struct acpi_table_support
{
    char                    *Name;
    char                    *Signature;
    void                    **GlobalPtr;
    UINT8                   SigLength;
    UINT8                   Flags;

} ACPI_TABLE_SUPPORT;


/* Macros used to generate offsets to specific table fields */

#define ACPI_BOOT_OFFSET(f)             (UINT8) ACPI_OFFSET (ACPI_TABLE_BOOT,f)
#define ACPI_DBGP_OFFSET(f)             (UINT8) ACPI_OFFSET (ACPI_TABLE_DBGP,f)
#define ACPI_ECDT_OFFSET(f)             (UINT8) ACPI_OFFSET (EC_BOOT_RESOURCES,f)
#define ACPI_FACS_OFFSET(f)             (UINT8) ACPI_OFFSET (FACS_DESCRIPTOR,f)
#define ACPI_FADT_OFFSET(f)             (UINT8) ACPI_OFFSET (FADT_DESCRIPTOR, f)
#define ACPI_FADT2_OFFSET(f)            (UINT8) ACPI_OFFSET (FADT_DESCRIPTOR_REV2,f)
#define ACPI_GAS_OFFSET(f)              (UINT8) ACPI_OFFSET (ACPI_GENERIC_ADDRESS,f)
#define ACPI_HDR_OFFSET(f)              (UINT8) ACPI_OFFSET (ACPI_TABLE_HEADER,f)
#define ACPI_HPET_OFFSET(f)             (UINT8) ACPI_OFFSET (HPET_TABLE,f)
#define ACPI_MADT_OFFSET(f)             (UINT8) ACPI_OFFSET (MULTIPLE_APIC_TABLE,f)
#define ACPI_MADT0_OFFSET(f)            (UINT8) ACPI_OFFSET (MADT_PROCESSOR_APIC,f)
#define ACPI_MADT1_OFFSET(f)            (UINT8) ACPI_OFFSET (MADT_IO_APIC,f)
#define ACPI_MADT2_OFFSET(f)            (UINT8) ACPI_OFFSET (MADT_INTERRUPT_OVERRIDE,f)
#define ACPI_MADT3_OFFSET(f)            (UINT8) ACPI_OFFSET (MADT_NMI_SOURCE,f)
#define ACPI_MADT4_OFFSET(f)            (UINT8) ACPI_OFFSET (MADT_LOCAL_APIC_NMI,f)
#define ACPI_MADT5_OFFSET(f)            (UINT8) ACPI_OFFSET (MADT_ADDRESS_OVERRIDE,f)
#define ACPI_MADT6_OFFSET(f)            (UINT8) ACPI_OFFSET (MADT_IO_SAPIC,f)
#define ACPI_MADT7_OFFSET(f)            (UINT8) ACPI_OFFSET (MADT_LOCAL_SAPIC,f)
#define ACPI_MADT8_OFFSET(f)            (UINT8) ACPI_OFFSET (MADT_INTERRUPT_SOURCE,f)
#define ACPI_MADTH_OFFSET(f)            (UINT8) ACPI_OFFSET (APIC_HEADER,f)
#define ACPI_MCFG_OFFSET(f)             (UINT8) ACPI_OFFSET (ACPI_MCFG_ALLOCATION,f)
#define ACPI_RSDP_OFFSET(f)             (UINT8) ACPI_OFFSET (RSDP_DESCRIPTOR,f)
#define ACPI_SBST_OFFSET(f)             (UINT8) ACPI_OFFSET (SMART_BATTERY_TABLE,f)
#define ACPI_SLIT_OFFSET(f)             (UINT8) ACPI_OFFSET (SYSTEM_LOCALITY_INFO,f)
#define ACPI_SPCR_OFFSET(f)             (UINT8) ACPI_OFFSET (ACPI_TABLE_SPCR,f)
#define ACPI_SPMI_OFFSET(f)             (UINT8) ACPI_OFFSET (ACPI_TABLE_SPMI,f)
#define ACPI_SRATM_OFFSET(f)            (UINT8) ACPI_OFFSET (MEMORY_AFFINITY,f)
#define ACPI_SRATP_OFFSET(f)            (UINT8) ACPI_OFFSET (STATIC_RESOURCE_ALLOC,f)
#define ACPI_TCPA_OFFSET(f)             (UINT8) ACPI_OFFSET (ACPI_TABLE_TCPA,f)
#define ACPI_WDRT_OFFSET(f)             (UINT8) ACPI_OFFSET (ACPI_TABLE_WDRT,f)

#define ACPI_FADT2_FLAG_OFFSET(f,o)     (UINT8) (ACPI_OFFSET (FADT_DESCRIPTOR_REV2,f) + o)

#endif /* __ACTBL_H__ */
