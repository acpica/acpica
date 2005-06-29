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
 | FILENAME: acpitype.h - Data structures defined in ACPI specification
 |__________________________________________________________________________
 |
 | $Revision: 1.6 $
 | $Date: 2005/06/29 20:06:31 $
 | $Log: actbl.h,v $
 | Revision 1.6  2005/06/29 20:06:31  aystarik
 | Integrated with 03/99 OPSD code
 |
 | 
 | date	99.03.31.22.30.00;	author rmoore1;	state Exp;
 |
 * 
 * 6     3/31/99 2:30p Rmoore1
 * Integrated with 03/99 OPSD code
 * 
 * 5     3/09/99 4:04p Rmoore1
 * 16/32/64-bit common data types
 * 
 * 4     2/12/99 11:10a Rmosgrov
 * Anti-Polish clean up
 * 
 * 3     1/13/99 10:50a Grsmith1
 * First BeOS compatible check-in.
 * 
 * 2     1/11/99 4:15p Grsmith1
 * 
 * 1     1/11/99 2:10p Rmoore1
 * Subsystem headers
// 
//    Rev 1.5   28 Apr 1998 10:18:56   calingle
// Added a #define for GL_OWNED
//
//    Rev 1.4   24 Sep 1997 13:12:04   calingle
// Added 2 more Reserved fields to the FIXED_ACPI_DESCRIPTION_TABLE
// which were missing prior to the flags, after the Century byte.
// This corrects a problem in determining if the sleep button is
// a fixed event or not, which in the PIIX4 it is not because
// hardware support is not available for this.
//
//    Rev 1.3   Mar 24 1997 16:53:50   KBRANNOC
// Changed #defines for table signatures from {'x', 'y', 'z'} to "xyz"
// Changed data entry in ROOT_SYSTEM_DESCTIPTION_TABLE from
//   ACPI_TABLE_HEADER *entry[1] to DWORD TableOffsetEntry[1]
// Added typedef for smart battery description table
//
//    Rev 1.2   05 Mar 1997 13:28:46   phutchis
// Added typedef for ACPI_OBJECT_HANDLE
//
//    Rev 1.1   Feb 28 1997 08:58:02   KBRANNOC
// Corrected some inconsistencies with ACPI specification and ETDE coding
// standard
//
//    Rev 1.0   Feb 26 1997 14:35:36   KBRANNOC
// Initial revision.
 |__________________________________________________________________________

*/

#ifndef __ACPITYPE_H__
#define __ACPITYPE_H__

typedef UINT32      IOADDR;                 /* Only for clarity in declarations */

typedef void * ACPI_OBJECT_HANDLE;          /* ptr to an ACPI data object */

/*
 *  Values for description table header signatures
 */

#define RSDP_SIG "RSD PTR "                 /* RSDT Pointer signature */
#define APIC_SIG "APIC"                     /* Multiple APIC Description Table */
#define DSDT_SIG "DSDT"                     /* Differentiated Sys Descrip Table */
#define FACP_SIG "FACP"                     /* Fixed ACPI Description Table */
#define FACS_SIG "FACS"                     /* Firmware ACPI Control Structure */
#define PSDT_SIG "PSDT"                     /* Persistent Sys Description Table */
#define RSDT_SIG "RSDT"                     /* Root System Description Table */
#define SSDT_SIG "SSDT"                     /* Secondary Sys Description Table */
#define SBDT_SIG "SBDT"                     /* Smart Batter Description Table */

typedef struct
{                                           /* Root System Descriptor Pointer */
    char        Signature [8];              /* contains "RSD PTR " */
    UINT8       Checksum;                   /* to make sum of struct == 0 */
    char        OemId [6];                  /* OEM identification */
    UINT8       Reserved;                   /* reserved - must be zero */
    UINT32      RsdtPhysicalAddress;        /* physical address of RSDT */

} ROOT_SYSTEM_DESCRIPTOR_POINTER;

typedef struct
{                                           /* ACPI common table header */
    char        Signature [4];              /* identifies type of table */
    UINT32      Length;                     /* length of table, in bytes,
                                             * including header */
    UINT8       Revision;                   /* specification minor version # */
    UINT8       bChecksum;                  /* to make sum of entire table == 0 */
    char        OemId [6];                  /* OEM identification */
    char        OemTableId [8];             /* OEM table identification */
    UINT32      OemRevision;                /* OEM revision number */
    char        AslCompilerId [4];          /* ASL compiler vendor ID */
    UINT32      AslCompilerRevision;        /* ASL compiler revision number */

} ACPI_TABLE_HEADER;

typedef struct
{                                           /* Root System Description Table */
    ACPI_TABLE_HEADER header;               /* table header */
    UINT32      TableOffsetEntry [1];       /* array of pointers to other
                                             * tables' headers */
} ROOT_SYSTEM_DESCRIPTION_TABLE;


#define GL_OWNED        0x02                /* Ownership of global lock is bit 1 */

typedef struct
{                                           /* Firmware ACPI Control Structure */
    char        Signature[4];               /* signature "FACS" */
    UINT32      Length;                     /* length of structure, in bytes */
    UINT32      HardwareSignature;          /* hardware configuration signature */
    UINT32      FirmwareWakingVector;       /* ACPI OS waking vector */
    UINT32      GlobalLock;                 /* Global Lock */
    UINT16_BIT  S4Bios_f        : 1;        /* Indicates whether or not S4BIOS
                                             * support is present */
    UINT16_BIT  Reserved1       : 15;       /* must be 0 */
    UINT16      Reserved2;                  /* must be 0 */
    UINT8       Resverved3 [40];            /* reserved - must be zero */

} FIRMWARE_ACPI_CONTROL_STRUCTURE;



/* values of Model */

#define DUAL_PIC        0
#define MULTIPLE_APIC   1

typedef struct
{                                           /* Fixed ACPI Description Table */
    ACPI_TABLE_HEADER header;               /* table header */
    UINT32      FirmwareCtrl;               /* Physical addesss of FACS */
    UINT32      Dsdt;                       /* Physical address of DSDT */
    UINT8       Model;                      /* System Interrupt Model */
    UINT8       Reserved1;                  /* reserved */
    UINT16      SciInt;                     /* System vector of SCI interrupt */
    IOADDR      SmiCmd;                     /* Port address of SMI command port */
    UINT8       AcpiEnable;                 /* value to write to port smi_cmd to
                                             * enable ACPI */
    UINT8       AcpiDisable;                /* value to write to port smi_cmd to
                                             * disable ACPI */
    UINT8       S4BiosReq;                  /* Value to write to SMI CMD port to
                                             * enter the S4BIOS state */
    UINT8       Reserved2;                  /* reserved - must be zero */
    IOADDR      Pm1aEvtBlk;                 /* Port address of Power Mgt 1a
                                             * Event Reg Blk */
    IOADDR      Pm1bEvtBlk;                 /* Port address of Power Mgt 1b
                                             * Event Reg Blk */
    IOADDR      Pm1aCntBlk;                 /* Port address of Power Mgt 1a
                                             * Control Reg Blk */
    IOADDR      Pm1bCntBlk;                 /* Port address of Power Mgt 1b
                                             * Control Reg Blk */
    IOADDR      Pm2CntBlk;                  /* Port address of Power Mgt 2
                                             * Control Reg Blk */
    IOADDR      PmTmrBlk;                   /* Port address of Power Mgt Timer
                                             * Ctrl Reg Blk */
    IOADDR      Gpe0Blk;                    /* Port addr of General Purpose
                                             * Event 0 Reg Blk */
    IOADDR      Gpe1Blk;                    /* Port addr of General Purpose
                                             * Event 1 Reg Blk */
    UINT8       Pm1EvtLen;                  /* Byte Length of ports at
                                             * pm1X_evt_blk */
    UINT8       Pm1CntLen;                  /* Byte Length of ports at
                                             * pm1X_cnt_blk */
    UINT8       Pm2CntLen;                  /* Byte Length of ports at
                                             * pm2_cnt_blk */
    UINT8       PmTmLen;                    /* Byte Length of ports at pm_tm_blk */
    UINT8       Gpe0BlkLen;                 /* Byte Length of ports at gpe0_blk */
    UINT8       Gpe1BlkLen;                 /* Byte Length of ports at gpe1_blk */
    UINT8       Gpe1Base;                   /* offset in gpe model where gpe1
                                             * events start */
    UINT8       Reserved3;                  /* reserved */
    UINT16      PLvl2Lat;                   /* worst case HW latency to
                                             * enter/exit C2 state */
    UINT16      PLvl3Lat;                   /* worst case HW latency to
                                             * enter/exit C3 state */
    UINT16      FlushSize;                  /* Size of area read to flush caches */
    UINT16      FlushStride;                /* Stride used in flushing caches */
    UINT8       DutyOffset;                 /* bit location of duty cycle field
                                             * in p_cnt reg */
    UINT8       DutyWidth;                  /* bit width of duty cycle field in
                                             * p_cnt reg */
    UINT8       DayAlrm;                    /* index to day-of-month alarm in
                                             * RTC CMOS RAM */
    UINT8       MonAlrm;                    /* index to month-of-year alarm in
                                             * RTC CMOS RAM */
    UINT8       Century;                    /* index to century in RTC CMOS RAM */
    UINT8       Reserved4;                  /* reserved */
    UINT8       Reserved4a;                 /* reserved */
    UINT8       Reserved4b;                 /* reserved */
    UINT16_BIT  WBInvd          : 1;        /* wbinvd instruction works properly */
    UINT16_BIT  WBInvdFlush     : 1;        /* wbinvd flushes but does not
                                             * invalidate */
    UINT16_BIT  ProcC1          : 1;        /* all processors support C1 state */
    UINT16_BIT  PLvl2Up         : 1;        /* C2 state works on MP system */
    UINT16_BIT  PwrButton       : 1;        /* Power button is handled as a
                                             * generic feature */
    UINT16_BIT  SleepButton     : 1;        /* Sleep button is handled as a
                                             * generic feature, or no button
                                             * present */
    UINT16_BIT  FixedRTC        : 1;        /* RTC wakeup stat not in fixed
                                             * register space */
    UINT16_BIT  RTCS4           : 1;        /* RTC wakeup stat not possible from
                                             * S4 */
    UINT16_BIT  TmrValExt       : 1;        /* tmr_val is 32 bits */
    UINT16_BIT  Reserved5       : 7;        /* reserved - must be zero */
    UINT16      Reserved6;                  /* reserved - must be zero */

}  FIXED_ACPI_DESCRIPTION_TABLE;

typedef struct
{                                           /* APIC Table */
    ACPI_TABLE_HEADER header;               /* table header */
    UINT32      LocalApicAddress;           /* Physical address for accessing
                                             * local APICs */
    UINT16_BIT  PCATCompat      : 1;        /* a one indicates system also has
                                             * dual 8259s */
    UINT16_BIT  Reserved1       : 15;
    UINT16      Reserved2;

} APIC_TABLE;



/* values of bType in APIC_HEADER */

#define APIC_PROC   0
#define APIC_IO     1

typedef struct
{
    UINT8       Type;                       /* APIC type.  Either APIC_PROC or
                                             * APIC_IO */
    UINT8       Length;                     /* Length of APIC structure */

} APIC_HEADER;

typedef struct
{
    APIC_HEADER header;
    UINT8       ProcessorApicId;            /* ACPI processor id */
    UINT8       LocalApicId;                /* processor's local APIC id */
    UINT16_BIT  ProcessorEnabled: 1;        /* Processor is usable if set */
    UINT16_BIT  Reserved1       : 15;
    UINT16      Reserved2;

} PROCESSOR_APIC;

typedef struct
{
    APIC_HEADER header;
    UINT8       IOApicId;                   /* io APIC id */
    UINT8       Reserved;                   /* reserved - must be zero */
    UINT32      IOApicAddress;              /* APIC's physical address */
    UINT32      Vector;                     /* interrupt vector index where INTI
                                             * lines start */
} IO_APIC;

typedef struct
{
    ACPI_TABLE_HEADER header;
    UINT32      WarningLevel;
    UINT32      LowLeve;
    UINT32      CriticalLevel;

} SMART_BATTERT_DESCRIPTION_TABLE;

#endif /* __ACPITYPE_H__ */
