
/******************************************************************************
 * 
 * Name: acobject.h - Definition of ACPI_OBJECT_INTERNAL (Internal object only)
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

#ifndef _ACOBJECT_H
#define _ACOBJECT_H

#include <actypes.h>
#include <macros.h>
#include <internal.h>

/* 
 * TBD: This wastes memory.
 * TBD: Allow variable sized acpi objects
 * TBD: Must find and fix all code that assumes constant sized object
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


#define ACPI_OBJECT_COMMON                  /* Two 32-bit fields */\
    UINT8                   DataType;           /* To differentiate various internal objs */\
    UINT8                   Type;               /* ACPI_OBJECT_TYPE */\
    UINT8                   Size;               /* Size of entire descriptor */\
    UINT8                   Flags;\
    UINT16                  ReferenceCount;     /* For object deletion management */\
    UINT16                  CmFill2;\

/* Defines for flag byte above */

#define AO_STATIC_ALLOCATION        0x1



/* 
 * Common bitfield for the field objects
 */
#define ACPI_COMMON_FIELD_INFO              /* Three 32-bit values */\
    UINT32                  Offset;             /* Byte offset within containing object */\
    UINT16                  Length;             /* # of bits in buffer */ \
    UINT8                   Granularity;\
    UINT8                   BitOffset;          /* Bit offset within min read/write data unit */\
    UINT8                   Access;\
    UINT8                   LockRule;\
    UINT8                   UpdateRule;\
    UINT8                   ReservedF1;



/******************************************************************************
 * 
 * Individual Object Descriptors
 *
 *****************************************************************************/


typedef struct /* COMMON */
{
    ACPI_OBJECT_COMMON

} ACPI_OBJECT_Common;


typedef struct /* NUMBER - has value */
{
    ACPI_OBJECT_COMMON

    UINT32                  Value;
    UINT32                  Reserved2;
    UINT32                  Reserved3;
    UINT32                  Reserved4;

    void                    *Reserved_p1;
    void                    *Reserved_p2;
    void                    *Reserved_p3;
    void                    *Reserved_p4;
    void                    *Reserved_p5;

} ACPI_OBJECT_Number;


typedef struct /* STRING - has length and pointer */
{
    ACPI_OBJECT_COMMON

    UINT32                  Length;         /* # of bytes in string, excluding trailing null */
    UINT32                  Reserved2;
    UINT32                  Reserved3;
    UINT32                  Reserved4;

    UINT8                   *Pointer;       /* String value in AML stream or in allocated space */
    void                    *Reserved_p2;
    void                    *Reserved_p3;
    void                    *Reserved_p4;
    void                    *Reserved_p5;

} ACPI_OBJECT_String;


typedef struct /* BUFFER - has length, sequence, and pointer */
{
    ACPI_OBJECT_COMMON

    UINT32                  Length;         /* # of bytes in buffer */
    UINT32                  Sequence;       /* Sequential count of buffers created */
    UINT32                  Reserved3;
    UINT32                  Reserved4;

    UINT8                   *Pointer;       /* points to the buffer in allocated space */
    void                    *Reserved_p2;
    void                    *Reserved_p3;
    void                    *Reserved_p4;
    void                    *Reserved_p5;

} ACPI_OBJECT_Buffer;


typedef struct /* PACKAGE - has count, elements, next element */
{
    ACPI_OBJECT_COMMON

    UINT32                  Count;          /* # of elements in package */
    UINT32                  Reserved2;
    UINT32                  Reserved3;
    UINT32                  Reserved4;

    union AcpiObjInternal   **Elements;     /* Array of pointers to AcpiObjects */
    union AcpiObjInternal   **NextElement;  /* used only while initializing */
    void                    *Reserved_p3;
    void                    *Reserved_p4;
    void                    *Reserved_p5;

} ACPI_OBJECT_Package;


typedef struct /* FIELD UNIT */
{
    ACPI_OBJECT_COMMON

    ACPI_COMMON_FIELD_INFO        
    UINT32                  Sequence;           /* Container's sequence number */

    union AcpiObjInternal   *Container;         /* Containing object (Buffer) */
    void                    *Reserved_p2;
    void                    *Reserved_p3;
    void                    *Reserved_p4;
    void                    *Reserved_p5;

} ACPI_OBJECT_FieldUnit;


typedef struct /* DEVICE - has handle and notification handler/context */
{
    ACPI_OBJECT_COMMON

    UINT32                  Reserved1;
    UINT32                  Reserved2;
    UINT32                  Reserved3;
    UINT32                  Reserved4;

    ACPI_HANDLE             Handle;
    union AcpiObjInternal  *SysHandler;         /* Handler for system notifies */
    union AcpiObjInternal  *DrvHandler;         /* Handler for driver notifies */
    union AcpiObjInternal  *AddrHandler;        /* Handler for Address space */
    void                    *Reserved_p5;

} ACPI_OBJECT_Device;


typedef struct /* EVENT */
{
    ACPI_OBJECT_COMMON

    UINT32                  Semaphore;
    UINT16                  LockCount;
    UINT16                  ThreadId;
    UINT16                  SignalCount;
    UINT16                  Fill1;
    UINT32                  Reserved4;

    void                    *Reserved_p1;
    void                    *Reserved_p2;
    void                    *Reserved_p3;
    void                    *Reserved_p4;
    void                    *Reserved_p5;

} ACPI_OBJECT_Event;


typedef struct /* METHOD */
{
    ACPI_OBJECT_COMMON

    UINT16                  ParamCount;
    UINT8                   MethodFlags;
    UINT8                   Fill1;
    UINT32                  PcodeLength;
    UINT32                  TableLength;
    UINT32                  Reserved4;

    UINT8                   *Pcode;
    UINT8                   *AcpiTable;
    void                    *ParserOp;
    void                    *Reserved_p4;
    void                    *Reserved_p5;

} ACPI_OBJECT_Method;


typedef struct /* MUTEX */
{
    ACPI_OBJECT_COMMON

    UINT32                  Semaphore;
    UINT16                  LockCount;
    UINT16                  ThreadId;
    UINT16                  SyncLevel;
    UINT16                  Fill1;
    UINT32                  Reserved4;

    void                    *Reserved_p1;
    void                    *Reserved_p2;
    void                    *Reserved_p3;
    void                    *Reserved_p4;
    void                    *Reserved_p5;

} ACPI_OBJECT_Mutex;


typedef struct /* REGION */
{
    ACPI_OBJECT_COMMON

    UINT16                  SpaceId;
    UINT16                  DataValid;          /* 1 => Addr/Len are set */
    UINT32                  Address;
    UINT32                  Length;
    UINT32                  RegionData;         /* Region Specific data (PCI _ADR) */

    union AcpiObjInternal  *Method;             /* Associated control method */
    union AcpiObjInternal  *AddrHandler;        /* Handler for system notifies */
    union AcpiObjInternal  *Link;               /* Link in list of regions */
                                                /* list is owned by AddrHandler */
    NAME_TABLE_ENTRY       *REGMethod;          /* _REG method for this region (if any) */
    NAME_TABLE_ENTRY       *Nte;                /* containing object */

} ACPI_OBJECT_Region;


typedef struct /* POWER RESOURCE - has Handle and notification handler/context*/
{
    ACPI_OBJECT_COMMON

    UINT32                  SystemLevel;
    UINT32                  ResourceOrder;
    UINT32                  Reserved3;
    UINT32                  Reserved4;

    ACPI_HANDLE             Handle;
    union AcpiObjInternal   *SysHandler;        /* Handler for system notifies */
    union AcpiObjInternal   *DrvHandler;        /* Handler for driver notifies */
    void                    *Reserved_p4;
    void                    *Reserved_p5;

} ACPI_OBJECT_PowerResource;


typedef struct /* PROCESSOR - has Handle and notification handler/context*/
{
    ACPI_OBJECT_COMMON

    UINT32                  ProcId;
    UINT32                  PBLKAddress;
    UINT32                  PBLKLength;
    UINT32                  Reserved4;

    ACPI_HANDLE             Handle;
    union AcpiObjInternal   *SysHandler;        /* Handler for system notifies */
    union AcpiObjInternal   *DrvHandler;        /* Handler for driver notifies */
    union AcpiObjInternal   *AddrHandler;       /* Handler for Address space */
    void                    *Reserved_p5;

} ACPI_OBJECT_Processor;


typedef struct /* THERMAL ZONE - has Handle and Handler/Context */
{
    ACPI_OBJECT_COMMON

    UINT32                  Reserved1;
    UINT32                  Reserved2;
    UINT32                  Reserved3;
    UINT32                  Reserved4;

    ACPI_HANDLE             Handle;
    union AcpiObjInternal   *SysHandler;        /* Handler for system notifies */
    union AcpiObjInternal   *DrvHandler;        /* Handler for driver notifies */
    union AcpiObjInternal   *AddrHandler;       /* Handler for Address space */
    void                    *Reserved_p5;

} ACPI_OBJECT_ThermalZone;


/*
 * Internal types
 */

typedef struct /* FIELD */
{
    ACPI_OBJECT_COMMON

    ACPI_COMMON_FIELD_INFO        
    UINT32                  Reserved4;

    union AcpiObjInternal   *Container;         /* Containing object */
    void                    *Reserved_p2;
    void                    *Reserved_p3;
    void                    *Reserved_p4;
    void                    *Reserved_p5;

} ACPI_OBJECT_Field;


typedef struct /* BANK FIELD */
{
    ACPI_OBJECT_COMMON

    ACPI_COMMON_FIELD_INFO        
    UINT32                  Value;              /* Value to store into BankSelect */

    ACPI_HANDLE             BankSelect;         /* Bank select register */
    union AcpiObjInternal   *Container;         /* Containing object */
    void                    *Reserved_p3;
    void                    *Reserved_p4;
    void                    *Reserved_p5;

} ACPI_OBJECT_BankField;


typedef struct /* INDEX FIELD */
{
    /* 
     * No container pointer needed since the index and data register definitions
     * will define how to access the respective registers
     */
    ACPI_OBJECT_COMMON

    ACPI_COMMON_FIELD_INFO
    UINT32                  Value;              /* Value to store into Index register */
    
    ACPI_HANDLE             Index;              /* Index register */
    ACPI_HANDLE             Data;               /* Data register */
    void                    *Reserved_p3;
    void                    *Reserved_p4;
    void                    *Reserved_p5;

} ACPI_OBJECT_IndexField;


typedef struct /* Lvalue - Local object type */
{
    ACPI_OBJECT_COMMON

    UINT16                  OpCode;             /* Arg#, Local#, IndexOp, NameOp,
                                                 * ZeroOp, OneOp, OnesOp, Debug1 => DebugOp
                                                 */
    UINT16                  Fill1;
    UINT32                  Reserved2;
    UINT32                  Reserved3;
    UINT32                  Reserved4;

    void                    *Object;            /* OpCode   Use of Object field
                                                 * -------  ----------------------------
                                                 * NameOp   ACPI_HANDLE for referenced name
                                                 * IndexOp  ACPI_OBJECT_INTERNAL **
                                                 */
    void                    *Reserved_p2;
    void                    *Reserved_p3;
    void                    *Reserved_p4;
    void                    *Reserved_p5;

} ACPI_OBJECT_Lvalue;


typedef struct /* NOTIFY HANDLER */
{
    ACPI_OBJECT_COMMON

    UINT32                  Reserved1;
    UINT32                  Reserved2;
    UINT32                  Reserved3;
    UINT32                  Reserved4;

    NAME_TABLE_ENTRY        *Nte;               /* Parent device */
    NOTIFY_HANDLER          Handler;
    void                    *Context;
    void                    *Reserved_p4;
    void                    *Reserved_p5;

} ACPI_OBJECT_NotifyHandler;


typedef struct /* ADDRESS HANDLER */
{
    ACPI_OBJECT_COMMON

    UINT16                  SpaceId;
    UINT16                  Fill1;
    UINT32                  Reserved2;
    UINT32                  Reserved3;
    UINT32                  Reserved4;

    NAME_TABLE_ENTRY        *Nte;               /* Parent device */
    ADDRESS_SPACE_HANDLER   Handler;
    void                    *Context;
    union AcpiObjInternal   *Link;              /* Link to next handler on device */
    union AcpiObjInternal   *RegionList;        /* regions using this handler */

} ACPI_OBJECT_AddrHandler;





/******************************************************************************
 * 
 * ACPI_OBJECT_INTERNAL Descriptor - a giant union of all of the above
 *
 *****************************************************************************/

typedef union AcpiObjInternal           
{
    ACPI_OBJECT_Common          Common;
    ACPI_OBJECT_Number          Number;
    ACPI_OBJECT_String          String;
    ACPI_OBJECT_Buffer          Buffer;
    ACPI_OBJECT_Package         Package;
    ACPI_OBJECT_FieldUnit       FieldUnit;
    ACPI_OBJECT_Device          Device;
    ACPI_OBJECT_Event           Event;
    ACPI_OBJECT_Method          Method;
    ACPI_OBJECT_Mutex           Mutex;
    ACPI_OBJECT_Region          Region;
    ACPI_OBJECT_PowerResource   PowerResource;
    ACPI_OBJECT_Processor       Processor;
    ACPI_OBJECT_ThermalZone     ThermalZone;
    ACPI_OBJECT_Field           Field;
    ACPI_OBJECT_BankField       BankField;
    ACPI_OBJECT_IndexField      IndexField;
    ACPI_OBJECT_Lvalue          Lvalue;
    ACPI_OBJECT_NotifyHandler   NotifyHandler;
    ACPI_OBJECT_AddrHandler     AddrHandler;

} ACPI_OBJECT_INTERNAL;


/* 
 * The Lvalue case of ACPI_OBJECT_INTERNAL includes a one-byte field which
 * contains an AML opcode identifying the type of lvalue.  Debug1 is used
 * in this field as a stand-in for the (two-byte) AML encoding of DebugOp (0x5B31)
 */

#define Debug1          0x31



#endif /* _ACOBJECT_H */
