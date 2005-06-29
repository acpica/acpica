
/******************************************************************************
 * 
 * Name: acpiobj.h - Definition of ACPI_OBJECT_INTERNAL (Internal object only)
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

#ifndef _ACPIOBJ_H
#define _ACPIOBJ_H

#include <acpitypes.h>

/* 
 * TBD: this wastes memory.
 *
 * All variants of the ACPI_OBJECT_INTERNAL are defined with the same
 * sequence of field types, with fields that are not used in a particular
 * variant being named "Reserved".  This is not strictly necessary, but
 * may in some circumstances simplify understanding if these structures
 * need to be displayed in a debugger having limited (or no) support for
 * union types.  It also simplifies some debug code in NsDumpTable() which
 * dumps multi-level values: fetching Buffer.Pointer suffices to pick up
 * the value or next level for any of several types.
 */

/******************************************************************************
 * 
 * Common Descriptors
 *
 *****************************************************************************/

/*
 * Common area for all objects.
 *
 * DataType is used to differentiate between internal descriptors, and MUST
 * be the first byte in this structure.
 */


#define ACPI_OBJECT_COMMON \
    UINT8                   DataType;       /* To differentiate various internal objs */\
    UINT8                   Type;           /* See definition of NsType for values */ \
    UINT8                   Flags;\
    UINT8                   CmFill1; \
    UINT16                  ReferenceCount; /* For object deletion management */\
    UINT16                  CmFill2;\
    char                    Name[8];        /* TBD: Temporary only, for debug */

/* Defines for flag byte above */

#define AO_STATIC_ALLOCATION        0x1



/* 
 * Common bitfield for the field objects
 */
#define ACPI_OBJECT_BITFIELD32 \
    BIT32                   Length          :13;    /* # of bits in buffer */ \
    BIT32                   BitOffset       : 3; \
    BIT32                   Access          : 4; \
    BIT32                   LockRule        : 1; \
    BIT32                   UpdateRule      : 2; \
    BIT32                   ReservedBits    : 9;



/******************************************************************************
 * 
 * Individual Object Descriptors
 *
 *****************************************************************************/


#define ACPI_OBJECT_Number      /* NUMBER - has value */\
    ACPI_OBJECT_COMMON \
    UINT32                  Value; \
    UINT32                  Reserved2; \
    UINT32                  Reserved3; \
    UINT32                  Reserved4; \
    void                    *Reserved_p1; \
    void                    *Reserved_p2; \
    void                    *Reserved_p3; \
    void                    *Reserved_p4; \
    void                    *Reserved_p5;


#define ACPI_OBJECT_String      /* STRING - has length and pointer */ \
    ACPI_OBJECT_COMMON \
    UINT32                  Length;         /* # of bytes in string, excluding trailing null */ \
    UINT32                  Reserved2; \
    UINT32                  Reserved3; \
    UINT32                  Reserved4; \
    UINT8                   *Pointer;       /* String value in AML stream or in allocated space */ \
    void                    *Reserved_p2; \
    void                    *Reserved_p3; \
    void                    *Reserved_p4; \
    void                    *Reserved_p5;


#define ACPI_OBJECT_Buffer      /* BUFFER - has length, sequence, and pointer */ \
    ACPI_OBJECT_COMMON \
    UINT32                  Length;         /* # of bytes in buffer */ \
    UINT32                  Sequence;       /* Sequential count of buffers created */ \
    UINT32                  Reserved3; \
    UINT32                  Reserved4; \
    UINT8                   *Pointer;       /* points to the buffer in allocated space */ \
    void                    *Reserved_p2; \
    void                    *Reserved_p3; \
    void                    *Reserved_p4; \
    void                    *Reserved_p5;


#define ACPI_OBJECT_Package     /* PACKAGE - has count, elements, next element */ \
    ACPI_OBJECT_COMMON \
    UINT32                  Count;          /* # of elements in package */ \
    UINT32                  Reserved2; \
    UINT32                  Reserved3; \
    UINT32                  Reserved4; \
    union AcpiObjInternal   **Elements;     /* Array of pointers to AcpiObjects */ \
    union AcpiObjInternal   **NextElement;  /* used only while initializing */ \
    void                    *Reserved_p3; \
    void                    *Reserved_p4; \
    void                    *Reserved_p5;


#define ACPI_OBJECT_FieldUnit  /* FIELD UNIT */ \
    ACPI_OBJECT_COMMON \
    ACPI_OBJECT_BITFIELD32 \
    UINT32                  Offset;             /* Byte offset within containing object */ \
    UINT32                  Sequence;           /* Container's sequence number */ \
    UINT32                  Reserved4; \
    union AcpiObjInternal   *Container;         /* Containing object (Buffer) */ \
    void                    *Reserved_p2; \
    void                    *Reserved_p3; \
    void                    *Reserved_p4; \
    void                    *Reserved_p5;


#define ACPI_OBJECT_Device      /* DEVICE - has handle and notification handler/context */ \
    ACPI_OBJECT_COMMON \
    UINT32                  Reserved1; \
    UINT32                  Reserved2; \
    union AcpiObjInternal   *AddrHandler;       /* Handler for Address space */ \
    UINT32                  Reserved4; \
    ACPI_HANDLE             Handle; \
    union AcpiObjInternal   *SysHandler;        /* Handler for system notifies */ \
    union AcpiObjInternal   *DrvHandler;        /* Handler for driver notifies */ \
    void                    *Reserved_p4; \
    void                    *Reserved_p5;


#define ACPI_OBJECT_Event       /* EVENT */ \
    ACPI_OBJECT_COMMON \
    UINT32                  Semaphore; \
    UINT16                  LockCount; \
    UINT16                  ThreadId; \
    UINT16                  SignalCount; \
    UINT16                  Fill1; \
    UINT32                  Reserved4; \
    void                    *Reserved_p1; \
    void                    *Reserved_p2; \
    void                    *Reserved_p3; \
    void                    *Reserved_p4; \
    void                    *Reserved_p5;


#define ACPI_OBJECT_Method      /* METHOD */ \
    ACPI_OBJECT_COMMON \
    UINT16                  ParamCount; \
    UINT16                  Fill1; \
    UINT32                  PcodeLength; \
    UINT32                  TableLength; \
    UINT32                  Reserved4; \
    UINT8                   *Pcode; \
    UINT8                   *AcpiTable; \
    void                    *Reserved_p3; \
    void                    *Reserved_p4; \
    void                    *Reserved_p5;


#define ACPI_OBJECT_Mutex       /* MUTEX */ \
    ACPI_OBJECT_COMMON \
    UINT32                  Semaphore; \
    UINT16                  LockCount; \
    UINT16                  ThreadId; \
    UINT16                  SyncLevel; \
    UINT16                  Fill1; \
    UINT32                  Reserved4; \
    void                    *Reserved_p1; \
    void                    *Reserved_p2; \
    void                    *Reserved_p3; \
    void                    *Reserved_p4; \
    void                    *Reserved_p5;


#define ACPI_OBJECT_Region      /* REGION */ \
    ACPI_OBJECT_COMMON \
    UINT16                  SpaceId; \
    UINT16                  DataValid;          /* 1 => Addr/Len are set */ \
    UINT32                  Address; \
    UINT32                  Length; \
    UINT32                  RegionData;         /* Region Specific data (PCI _ADR) */ \
    union AcpiObjInternal   *Method;            /* Associated control method */ \
    union AcpiObjInternal   *AddrHandler;       /* Handler for system notifies */ \
    union AcpiObjInternal   *Link;              /* Link in list of regions */ \
                                                /* list is owned by AddrHandler */ \
    NAME_TABLE_ENTRY        *REGMethod;         /* _REG method for this region (if any) */ \
    NAME_TABLE_ENTRY        *Nte;               /* containing object */



#define ACPI_OBJECT_AddrHandler /* ADDRESS HANDLER */ \
    ACPI_OBJECT_COMMON \
    UINT16                  SpaceId; \
    UINT16                  Reserved; \
    union AcpiObjInternal   *Link;              /* Link to next handler on device */ \
    union AcpiObjInternal   *RegionList;        /* regions using this handler */ \
    UINT32                  Reserved4; \
    NAME_TABLE_ENTRY        *Nte;               /* device handler was installed for */ \
    ADDRESS_SPACE_HANDLER   Handler; \
    void                    *Context; \
    void                    *Reserved_p4; \
    void                    *Reserved_p5; \


#define ACPI_OBJECT_NotifyHandler /* NOTIFY HANDLER */ \
    ACPI_OBJECT_COMMON \
    UINT32                  Reserved1; \
    UINT32                  Reserved2; \
    UINT32                  Reserved3; \
    UINT32                  Reserved4; \
    NAME_TABLE_ENTRY        *Nte;               /* device handler was installed for */ \
    NOTIFY_HANDLER          Handler; \
    void                    *Context; \
    void                    *Reserved_p4; \
    void                    *Reserved_p5;


#define ACPI_OBJECT_PowerResource /* POWER RESOURCE - has Handle and notification handler/context */ \
    ACPI_OBJECT_COMMON \
    UINT32                  Reserved1; \
    UINT32                  Reserved2; \
    UINT32                  Reserved3; \
    UINT32                  Reserved4; \
    ACPI_HANDLE             Handle; \
    union AcpiObjInternal   *SysHandler;        /* Handler for system notifies */ \
    union AcpiObjInternal   *DrvHandler;        /* Handler for driver notifies */ \
    void                    *Reserved_p4; \
    void                    *Reserved_p5;


#define ACPI_OBJECT_Processor   /* PROCESSOR - has Handle and notification handler/context */ \
    ACPI_OBJECT_COMMON \
    UINT32                  Reserved1; \
    UINT32                  Reserved2; \
    union AcpiObjInternal   *AddrHandler;       /* Handler for Address space */ \
    UINT32                  Reserved4; \
    ACPI_HANDLE             Handle; \
    union AcpiObjInternal   *SysHandler;        /* Handler for system notifies */ \
    union AcpiObjInternal   *DrvHandler;        /* Handler for driver notifies */ \
    void                    *Reserved_p4; \
    void                    *Reserved_p5;


#define ACPI_OBJECT_ThermalZone /* THERMAL ZONE - has Handle and Handler/Context */ \
    ACPI_OBJECT_COMMON \
    UINT32                  Reserved1; \
    UINT32                  Reserved2; \
    union AcpiObjInternal   *AddrHandler;       /* Handler for Address space */ \
    UINT32                  Reserved4; \
    ACPI_HANDLE             Handle; \
    union AcpiObjInternal   *SysHandler;        /* Handler for system notifies */ \
    union AcpiObjInternal   *DrvHandler;        /* Handler for driver notifies */ \
    void                    *Reserved_p4; \
    void                    *Reserved_p5;


#define ACPI_OBJECT_Field       /* FIELD */ \
    ACPI_OBJECT_COMMON \
    ACPI_OBJECT_BITFIELD32 \
    UINT32                  Offset;             /* Byte offset within containing object */ \
    UINT32                  Reserved3; \
    UINT32                  Reserved4; \
    union AcpiObjInternal   *Container;         /* Containing object */ \
    void                    *Reserved_p2; \
    void                    *Reserved_p3; \
    void                    *Reserved_p4; \
    void                    *Reserved_p5;


#define ACPI_OBJECT_BankField   /* BANK FIELD */ \
    ACPI_OBJECT_COMMON \
    ACPI_OBJECT_BITFIELD32 \
    UINT32                  Offset;             /* Byte offset within containing object */ \
    UINT32                  Value;              /* Value to store into BankSelect */ \
    UINT32                  Reserved4; \
    ACPI_HANDLE             BankSelect;         /* Bank select register */ \
    union AcpiObjInternal   *Container;         /* Containing object */ \
    void                    *Reserved_p3; \
    void                    *Reserved_p4; \
    void                    *Reserved_p5; \


/* 
 * No container pointer needed since the index and data register definitions
 * will define how to access the respective registers
 */
#define ACPI_OBJECT_IndexField  /* INDEX FIELD */ \
    ACPI_OBJECT_COMMON \
    ACPI_OBJECT_BITFIELD32 \
    UINT32                  Value;              /* Value to store into Index register */ \
    UINT32                  Reserved3; \
    UINT32                  Reserved4; \
    ACPI_HANDLE             Index;              /* Index register */ \
    ACPI_HANDLE             Data;               /* Data register */ \
    void                    *Reserved_p3; \
    void                    *Reserved_p4; \
    void                    *Reserved_p5;


#define ACPI_OBJECT_Lvalue  /* LVALUE - Local object type */ \
    ACPI_OBJECT_COMMON \
    UINT16                  OpCode;             /* Arg#, Local#, IndexOp, NameOp,*/ \
                                                /* ZeroOp, OneOp, OnesOp, Debug1 => DebugOp */ \
    UINT16                  Fill1; \
    UINT32                  Reserved2; \
    UINT32                  Reserved3; \
    UINT32                  Reserved4; \
    void                    *Object;            /* OpCode   Use of Object field */ \
                                                /* -------  ---------------------------- */ \
                                                /* NameOp   ACPI_HANDLE for referenced name */ \
                                                /* IndexOp  ACPI_OBJECT_INTERNAL ** */ \
    void                    *Reserved_p2; \
    void                    *Reserved_p3; \
    void                    *Reserved_p4; \
    void                    *Reserved_p5;



/******************************************************************************
 * 
 * ACPI_OBJECT_INTERNAL Descriptor - a giant union of all of the above
 *
 *****************************************************************************/

typedef union AcpiObjInternal           
{
    /* 
     * Fields that are common across all objects 
     */

    struct
    {
        ACPI_OBJECT_COMMON
    } Common;


    /*
     * Unique object structures (each includes common area again)
     */

    struct /* NUMBER - has value */
    {
        ACPI_OBJECT_Number
    } Number;


    struct /* STRING - has length and pointer */
    {
        ACPI_OBJECT_String
    } String;


    struct /* BUFFER - has length, sequence, and pointer */
    {
        ACPI_OBJECT_Buffer
    } Buffer;


    struct /* PACKAGE - has count, elements, next element */
    {
        ACPI_OBJECT_Package
    } Package;


    struct /* FIELD UNIT */
    {
        ACPI_OBJECT_FieldUnit
    } FieldUnit;

    struct /* DEVICE - has handle and notification handler/context */
    {
        ACPI_OBJECT_Device
    } Device;


    struct /* EVENT */
    {
        ACPI_OBJECT_Event
    } Event;


    struct /* METHOD */
    {
        ACPI_OBJECT_Method
    } Method;


    struct /* MUTEX */
    {
        ACPI_OBJECT_Mutex
    } Mutex;


    struct /* REGION */
    {
        ACPI_OBJECT_Region
    } Region;

    struct /* ADDRESS HANDLER */
    {
        ACPI_OBJECT_AddrHandler
    } AddrHandler;


    struct /* NOTIFY HANDLER */
    {
        ACPI_OBJECT_NotifyHandler
    } NotifyHandler;

    struct /* POWER RESOURCE - has Handle and notification handler/context*/
    {
        ACPI_OBJECT_PowerResource
    } PowerResource;


    struct /* PROCESSOR - has Handle and notification handler/context*/
    {
        ACPI_OBJECT_Processor
    } Processor;


    struct /* THERMAL ZONE - has Handle and Handler/Context */
    {
        ACPI_OBJECT_ThermalZone
    } ThermalZone;


    struct /* FIELD */
    {
        ACPI_OBJECT_Field
    } Field;


    struct /* BANK FIELD */
    {
        ACPI_OBJECT_BankField
    } BankField;


    struct /* INDEX FIELD */
    {
        ACPI_OBJECT_IndexField
    } IndexField;


    struct /* Lvalue - Local object type */
    {
        ACPI_OBJECT_Lvalue
    } Lvalue;

} ACPI_OBJECT_INTERNAL;


/* 
 * The sLvalue case of ACPI_OBJECT_INTERNAL includes a one-byte field which
 * contains an AML opcode identifying the type of lvalue.  Debug1 is used
 * in this field as a stand-in for the (two-byte) AML encoding of DebugOp.
 *
 * TBD: Obsolete?
 */

#define Debug1          0x31



#endif

 