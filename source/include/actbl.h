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
 | $Revision: 1.1 $
 | $Date: 2005/06/29 20:06:24 $
 | $Log: actbl.h,v $
 | Revision 1.1  2005/06/29 20:06:24  aystarik
 | Subsystem headers
 |
 |
 | 
 | date	99.01.11.22.10.00;	author rmoore1;	state Exp;
 |
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
//   ACPI_TABLE_HEADER *entry[1] to DWORD adTableOffsetEntry[1]
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

#include <bu.h>

typedef DWORD IOADDR;							/* Only for clarity in declarations */

typedef void * ACPI_OBJECT_HANDLE;			/* ptr to an ACPI data object */

/* Values for description table header signatures */
#define RSDP_SIG "RSD PTR " 				/* RSDT Pointer signature */
#define APIC_SIG "APIC"						/* Multiple APIC Description Table */
#define DSDT_SIG "DSDT"						/* Differentiated Sys Descrip Table */
#define FACP_SIG "FACP"						/* Fixed ACPI Description Table */
#define FACS_SIG "FACS"						/* Firmware ACPI Control Structure */
#define PSDT_SIG "PSDT"						/* Persistent Sys Description Table */
#define RSDT_SIG "RSDT"						/* Root System Description Table */
#define SSDT_SIG "SSDT"						/* Secondary Sys Description Table */
#define SBDT_SIG "SBDT"						/* Smart Batter Description Table */

typedef struct
{														/* Root System Descriptor Pointer */
	char acSignature[8];							/* contains "RSD PTR " */
	BYTE bChecksum;								/* to make sum of struct == 0 */
	char acOemId[6];								/* OEM identification */
	BYTE bReserved;								/* reserved - must be zero */
	DWORD dRsdtPhysicalAddress;				/* physical address of RSDT */
} ROOT_SYSTEM_DESCRIPTOR_POINTER;

typedef struct
{														/* ACPI common table header */
	char acSignature[4];							/* identifies type of table */
	DWORD dLength;									/* length of table, in bytes,
														 * including header */
	BYTE bRevision;								/* specification minor version # */
	BYTE bChecksum;								/* to make sum of entire table == 0 */
	char acOemId[6];								/* OEM identification */
	char acOemTableId[8];						/* OEM table identification */
	DWORD dOemRevision;							/* OEM revision number */
	char acAslCompilerId[4];					/* ASL compiler vendor ID */
	DWORD dAslCompilerRevision;				/* ASL compiler revision number */
} ACPI_TABLE_HEADER;

typedef struct
{														/* Root System Description Table */
	ACPI_TABLE_HEADER header;					/* table header */
	DWORD adTableOffsetEntry[1];				/* array of pointers to other
														 * tables' headers */
} ROOT_SYSTEM_DESCRIPTION_TABLE;


#define GL_OWNED	0x02							/* Ownership of global lock is bit 1 */
typedef struct
{														/* Firmware ACPI Control Structure */
	char acSignature[4];							/* signature "FACS" */
	DWORD dLength;									/* length of structure, in bytes */
	DWORD dHardwareSignature;					/* hardware configuration signature */
	DWORD dFirmwareWakingVector;				/* ACPI OS waking vector */
	DWORD dGlobalLock;							/* Global Lock */
	WORD_BIT S4Bios_f		: 1;					/* Indicates whether or not S4BIOS
														 * support is present */
	WORD_BIT Reserved1	: 15;					/* must be 0 */
	WORD 	wReserved2;								/* must be 0 */
	BYTE abResverved3[40];						/* reserved - must be zero */
} FIRMWARE_ACPI_CONTROL_STRUCTURE;

/* values of bIntModel */
#define DUAL_PIC  0
#define MULTIPLE_APIC  1

typedef struct
{														/* Fixed ACPI Description Table */
	ACPI_TABLE_HEADER header;					/* table header */
	DWORD dFirmwareCtrl;							/* Physical addesss of FACS */
	DWORD dDsdt;									/* Physical address of DSDT */
	BYTE bIntModel;								/* System Interrupt Model */
	BYTE bReserved1;								/* reserved */
	WORD wSciInt;									/* System vector of SCI interrupt */
	IOADDR dSmiCmd;								/* Port address of SMI command port */
	BYTE bAcpiEnable;								/* value to write to port smi_cmd to
														 * enable ACPI */
	BYTE bAcpiDisable;							/* value to write to port smi_cmd to
														 * disable ACPI */
	BYTE bS4BiosReq;								/* Value to write to SMI CMD port to
														 * enter the S4BIOS state */
	BYTE bReserved2;								/* reserved - must be zero */
	IOADDR dPm1aEvtBlk;							/* Port address of Power Mgt 1a
														 * Event Reg Blk */
	IOADDR dPm1bEvtBlk;							/* Port address of Power Mgt 1b
														 * Event Reg Blk */
	IOADDR dPm1aCntBlk;							/* Port address of Power Mgt 1a
														 * Control Reg Blk */
	IOADDR dPm1bCntBlk;							/* Port address of Power Mgt 1b
														 * Control Reg Blk */
	IOADDR dPm2CntBlk;							/* Port address of Power Mgt 2
														 * Control Reg Blk */
	IOADDR dPmTmrBlk;								/* Port address of Power Mgt Timer
														 * Ctrl Reg Blk */
	IOADDR dGpe0Blk;								/* Port addr of General Purpose
														 * Event 0 Reg Blk */
	IOADDR dGpe1Blk;								/* Port addr of General Purpose
														 * Event 1 Reg Blk */
	BYTE bPm1EvtLen;								/* Byte Length of ports at
														 * pm1X_evt_blk */
	BYTE bPm1CntLen;								/* Byte Length of ports at
														 * pm1X_cnt_blk */
	BYTE bPm2CntLen;								/* Byte Length of ports at
														 * pm2_cnt_blk */
	BYTE bPmTmLen;									/* Byte Length of ports at pm_tm_blk */
	BYTE bGpe0BlkLen;								/* Byte Length of ports at gpe0_blk */
	BYTE bGpe1BlkLen;								/* Byte Length of ports at gpe1_blk */
	BYTE bGpe1Base;								/* offset in gpe model where gpe1
														 * events start */
	BYTE bReserved3;								/* reserved */
	WORD wPLvl2Lat;								/* worst case HW latency to
														 * enter/exit C2 state */
	WORD wPLvl3Lat;								/* worst case HW latency to
														 * enter/exit C3 state */
	WORD wFlushSize;								/* Size of area read to flush caches */
	WORD wFlushStride;							/* Stride used in flushing caches */
	BYTE bDutyOffset;								/* bit location of duty cycle field
														 * in p_cnt reg */
	BYTE bDutyWidth;								/* bit width of duty cycle field in
														 * p_cnt reg */
	BYTE bDayAlrm;									/* index to day-of-month alarm in
														 * RTC CMOS RAM */
	BYTE bMonAlrm;									/* index to month-of-year alarm in
														 * RTC CMOS RAM */
	BYTE bCentury;									/* index to century in RTC CMOS RAM */
	BYTE bReserved4;								/* reserved */
	BYTE bReserved4a;								/* reserved */
	BYTE bReserved4b;								/* reserved */
	WORD_BIT WBInvd		: 1;					/* wbinvd instruction works properly */
	WORD_BIT WBInvdFlush	: 1;					/* wbinvd flushes but does not
														 * invalidate */
	WORD_BIT ProcC1		: 1;					/* all processors support C1 state */
	WORD_BIT PLvl2Up		: 1;					/* C2 state works on MP system */
	WORD_BIT PwrButton	: 1;					/* Power button is handled as a
														 * generic feature */
	WORD_BIT SleepButton	: 1;					/* Sleep button is handled as a
														 * generic feature, or no button
														 * present */
	WORD_BIT FixedRTC		: 1;					/* RTC wakeup stat not in fixed
														 * register space */
	WORD_BIT RTCS4			: 1;					/* RTC wakeup stat not possible from
														 * S4 */
	WORD_BIT TmrValExt	: 1;					/* tmr_val is 32 bits */
	WORD_BIT Reserved5	: 7;					/* reserved - must be zero */
	WORD wReserved6;								/* reserved - must be zero */
}  FIXED_ACPI_DESCRIPTION_TABLE;

typedef struct
{														/* APIC Table */
	ACPI_TABLE_HEADER header;					/* table header */
	DWORD dLocalApicAddress;					/* Physical address for accessing
														 * local APICs */
	WORD_BIT PCATCompat : 1;					/* a one indicates system also has
														 * dual 8259s */
	WORD_BIT Reserved1 : 15;
	WORD wReserved2;
} APIC_TABLE;

/* values of bType in APIC_HEADER */
#define APIC_PROC  0
#define APIC_IO    1

typedef struct
{
	BYTE bType;										/* APIC type.  Either APIC_PROC or
														 * APIC_IO */
	BYTE bLength;									/* Length of APIC structure */
} APIC_HEADER;

typedef struct
{
	APIC_HEADER header;
	BYTE bProcessorApicId;					/* ACPI processor id */
	BYTE bLocalApicId;						/* processor's local APIC id */
	WORD_BIT ProcessorEnabled : 1;		/* Processor is usable if set */
	WORD_BIT Reserved1 : 15;
	WORD Reserved2;
} PROCESSOR_APIC;

typedef struct
{
	APIC_HEADER header;
	BYTE bIOApicId;							/* io APIC id */
	BYTE Reserved;								/* reserved - must be zero */
	DWORD dIOApicAddress;					/* APIC's physical address */
	DWORD dVector;								/* interrupt vector index where INTI
													 * lines start */
} IO_APIC;

typedef struct
{
	ACPI_TABLE_HEADER header;
	DWORD dWarningLevel;
	DWORD dLowLeve;
	DWORD dCriticalLevel;
}	SMART_BATTERT_DESCRIPTION_TABLE;

#endif /* __ACPITYPE_H__ */
