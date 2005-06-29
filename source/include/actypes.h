
/******************************************************************************
 * 
 * Name: acpitypes.h - Common data types for the entire ACPI subsystem
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

#ifndef _ACPITYPES_H
#define _ACPITYPES_H


/* 
 * Data types - Fixed across all compilation models
 * 
 * BOOLEAN      Logical Boolean. 1 byte value containing a 0 for FALSE or a 1 for TRUE.  Other values are undefined.
 * INT          Signed value. (4 bytes on IA-32, 8 bytes on IA-64)
 * UINT         Unsigned value. (4 bytes on IA-32, 8 bytes on IA-64)
 * INT8         1 byte signed value
 * UINT8        1 byte unsigned value
 * INT16        2 byte signed value
 * UINT16       2 byte unsigned value
 * INT32        4 byte signed value
 * UINT32       4 byte unsigned value
 * INT64        8 byte signed value (not supported or used at this time)
 * UINT64       8 byte unsigned value (not supported or used at this time)
 * UCHAR        Character. 1 byte unsigned value. 
 * WCHAR        Wide Character. 2 byte unsigned value (not supported or used at this time) 
 */

/* 
 * TBD:  Need a 32-bit vs. 64-bit section !!! 
 */

/*  IA-32 type definitions */

typedef unsigned char                   BOOLEAN;
typedef int                             INT;
typedef unsigned int                    UINT;
typedef signed char                     INT8;
typedef unsigned char                   UINT8;
typedef short                           INT16;
typedef unsigned short                  UINT16;
typedef int                             INT32;
typedef unsigned int                    UINT32;
typedef unsigned char                   UCHAR;

typedef unsigned char                   UINT8_BIT;
typedef unsigned short                  UINT16_BIT;
typedef unsigned long                   UINT32_BIT;

typedef int                             BIT32;
typedef short int                       BIT16;
typedef char                            BIT8;

typedef int                             ACPI_PTRDIFF;
typedef unsigned int                    ACPI_SIZE;
    

/*
 * data type ranges
 */

#define ACPI_UCHAR_MAX                  0xFF
#define ACPI_INT_MAX                    0x7FFFFFFF
#define ACPI_UINT_MAX                   0xFFFFFFFF
#define ACPI_LONG_MAX                   0x7FFFFFFF
#define ACPI_ULONG_MAX                  0xFFFFFFFF

 

/* 
 * Useful defines 
 */

#ifdef FALSE
#undef FALSE
#endif
#define FALSE                           (1 == 0)

#ifdef TRUE
#undef TRUE
#endif
#define TRUE                            (1 == 1)

#ifndef NULL
#define NULL                            (void *) 0
#endif


/* 
 * Local datatypes 
 */


typedef UINT32                          ACPI_STATUS;    /* All ACPI Exceptions */
typedef UINT32                          ACPI_NAME;      /* 4-char ACPI name */
typedef char*                           ACPI_STRING;    /* Null terminated ASCII string */
typedef void*                           ACPI_HANDLE;    /* Actually a ptr to an NTE */


/*
 * Constants with special meanings
 */

#define ACPI_ROOT_OBJECT                (ACPI_HANDLE)(-1)


/*
 * Sleep state constants
 */
#define S0					            (UINT8) 0
#define S1					            (UINT8) 1
#define S2					            (UINT8) 2
#define S3					            (UINT8) 3
#define S4					            (UINT8) 4
#define S4BIOS				            (UINT8) 5
#define S5					            (UINT8) 6
#define ACPI_S_STATES_MAX	            S5


/*
 *  Table types.  These values are passed to the table related APIs
 */

typedef UINT32                          ACPI_TABLE_TYPE;

#define TABLE_RSDP                      (ACPI_TABLE_TYPE) 0
#define TABLE_APIC                      (ACPI_TABLE_TYPE) 1
#define TABLE_DSDT                      (ACPI_TABLE_TYPE) 2
#define TABLE_FACP                      (ACPI_TABLE_TYPE) 3
#define TABLE_FACS                      (ACPI_TABLE_TYPE) 4
#define TABLE_PSDT                      (ACPI_TABLE_TYPE) 5
#define TABLE_RSDT                      (ACPI_TABLE_TYPE) 6
#define TABLE_SSDT                      (ACPI_TABLE_TYPE) 7
#define TABLE_SBST                      (ACPI_TABLE_TYPE) 8
#define ACPI_TABLE_MAX                  8
#define NUM_ACPI_TABLES                 9


/* 
 * Types associated with names.  The first group of
 * values correspond to the definition of the ACPI ObjectType operator (See the ACPI Spec).
 * Therefore, only add to the first group if the spec changes!
 *
 * Types must be kept in sync with the NsProperties and NsTypeNames arrays
 */

typedef UINT32                          ACPI_OBJECT_TYPE;

#define ACPI_TYPE_Any                   (ACPI_OBJECT_TYPE) 0  /* 0x00  */
#define ACPI_TYPE_Number                (ACPI_OBJECT_TYPE) 1  /* 0x01  Byte/Word/Dword/Zero/One/Ones */
#define ACPI_TYPE_String                (ACPI_OBJECT_TYPE) 2  /* 0x02  */
#define ACPI_TYPE_Buffer                (ACPI_OBJECT_TYPE) 3  /* 0x03  */
#define ACPI_TYPE_Package               (ACPI_OBJECT_TYPE) 4  /* 0x04  ByteConst, multiple DataTerm/Constant/SuperName */
#define ACPI_TYPE_FieldUnit             (ACPI_OBJECT_TYPE) 5  /* 0x05  */
#define ACPI_TYPE_Device                (ACPI_OBJECT_TYPE) 6  /* 0x06  Name, multiple NamedObject */
#define ACPI_TYPE_Event                 (ACPI_OBJECT_TYPE) 7  /* 0x07  */
#define ACPI_TYPE_Method                (ACPI_OBJECT_TYPE) 8  /* 0x08  Name, ByteConst, multiple Code */
#define ACPI_TYPE_Mutex                 (ACPI_OBJECT_TYPE) 9  /* 0x09  */
#define ACPI_TYPE_Region                (ACPI_OBJECT_TYPE) 10 /* 0x0A  */
#define ACPI_TYPE_Power                 (ACPI_OBJECT_TYPE) 11 /* 0x0B  Name,ByteConst,WordConst,multi NamedObject */
#define ACPI_TYPE_Processor             (ACPI_OBJECT_TYPE) 12 /* 0x0C  Name,ByteConst,DWordConst,ByteConst,multi NmO */
#define ACPI_TYPE_Thermal               (ACPI_OBJECT_TYPE) 13 /* 0x0D  Name, multiple NamedObject */
#define ACPI_TYPE_BufferField           (ACPI_OBJECT_TYPE) 14 /* 0x0E  */
#define ACPI_TYPE_DdbHandle             (ACPI_OBJECT_TYPE) 15 /* 0x0F  */

#define ACPI_TYPE_MAX                   15

    /* 
     * This section contains object types that do not relate to the ACPI ObjectType operator.
     * They are used for various internal purposes only.  A numerical gap is provided in 
     * case additional "official" ObjectTypes are added in the future.  Also, values exceeding
     * the largest official ACPI ObjectType must not overlap with defined AML opcodes.
     */
#define INTERNAL_TYPE_DefField          (ACPI_OBJECT_TYPE) 25 /* 0x19  */
#define INTERNAL_TYPE_BankField         (ACPI_OBJECT_TYPE) 26 /* 0x1A  */
#define INTERNAL_TYPE_IndexField        (ACPI_OBJECT_TYPE) 27 /* 0x1B  */
#define INTERNAL_TYPE_DefFieldDefn      (ACPI_OBJECT_TYPE) 28 /* 0x1C  Name, ByteConst, multiple FieldElement */
#define INTERNAL_TYPE_BankFieldDefn     (ACPI_OBJECT_TYPE) 29 /* 0x1D  2 Name,DWordConst,ByteConst,multi FieldElement */
#define INTERNAL_TYPE_IndexFieldDefn    (ACPI_OBJECT_TYPE) 30 /* 0x1E  2 Name, ByteConst, multiple FieldElement */
#define INTERNAL_TYPE_If                (ACPI_OBJECT_TYPE) 31 /* 0x1F  OpCode, multiple Code */
#define INTERNAL_TYPE_Else              (ACPI_OBJECT_TYPE) 32 /* 0x20  multiple Code */
#define INTERNAL_TYPE_While             (ACPI_OBJECT_TYPE) 33 /* 0x21  OpCode, multiple Code */
#define INTERNAL_TYPE_Scope             (ACPI_OBJECT_TYPE) 34 /* 0x22  Name, multiple NamedObject */
#define INTERNAL_TYPE_DefAny            (ACPI_OBJECT_TYPE) 35 /* 0x23  type is Any, suppress search of enclosing scopes */
#define INTERNAL_TYPE_Lvalue            (ACPI_OBJECT_TYPE) 36 /* 0x24  Arg#, Local#, Name, Debug; used only in descriptors */
#define INTERNAL_TYPE_Alias             (ACPI_OBJECT_TYPE) 37 /* 0x25  */
#define INTERNAL_TYPE_Notify            (ACPI_OBJECT_TYPE) 38 /* 0x26  */
#define INTERNAL_TYPE_AddressHandler    (ACPI_OBJECT_TYPE) 39 /* 0x27  */

#define INTERNAL_TYPE_MAX               39

#define INTERNAL_TYPE_Invalid           (ACPI_OBJECT_TYPE) 40


/* 
 * Fixed event types 
 */

typedef UINT32                          ACPI_EVENT_TYPE;

#define EVENT_PMTIMER                   (ACPI_EVENT_TYPE) 0
    /* 
     * There's no bus master event so index 1 is used for IRQ's that are not
     * handled by the SCI handler 
     */
#define EVENT_NOT_USED                  (ACPI_EVENT_TYPE) 1
#define EVENT_GLOBAL                    (ACPI_EVENT_TYPE) 2
#define EVENT_POWER_BUTTON              (ACPI_EVENT_TYPE) 3
#define EVENT_SLEEP_BUTTON              (ACPI_EVENT_TYPE) 4
#define EVENT_RTC                       (ACPI_EVENT_TYPE) 5
#define EVENT_GENERAL                   (ACPI_EVENT_TYPE) 6
#define ACPI_EVENT_MAX                  6
#define NUM_FIXED_EVENTS                (ACPI_EVENT_TYPE) 7

#define GPE_INVALID                     0xFF
#define GPE_MAX                         0xFF
#define NUM_GPE                         256


/* Notify types */

#define ACPI_SYSTEM_NOTIFY              0
#define ACPI_DEVICE_NOTIFY              1
#define ACPI_MAX_NOTIFY_HANDLER_TYPE    1

#define MAX_SYS_NOTIFY                  0x7f

/* 
 * External ACPI object definition 
 */

typedef union AcpiObj 
{
    ACPI_OBJECT_TYPE            Type;   /* See definition of NsType for values */
    struct
    {
        ACPI_OBJECT_TYPE            Type;
        UINT32                      Value;      /* The actual number */
    } Number;

    struct
    {
        ACPI_OBJECT_TYPE            Type;
        UINT32                      Length;     /* # of bytes in string, excluding trailing null */
        UINT8                       *Pointer;   /* points to the string value */
    } String;

    struct
    {
        ACPI_OBJECT_TYPE            Type;
        UINT32                      Length;     /* # of bytes in buffer */
        UINT8                       *Pointer;   /* points to the buffer */
    } Buffer;

    struct

    {
        ACPI_OBJECT_TYPE            Type;
        UINT32                      Count;      /* # of elements in package */
        union AcpiObj               *Elements;  /* Pointer to an array of ACPI_OBJECTs */
    } Package;

} ACPI_OBJECT, *PACPI_OBJECT;



/*
 * List of objects, used as a parameter list for control method evaluation 
 */

typedef struct AcpiObjList
{
    UINT32                  Count;
    ACPI_OBJECT             *Pointer;

} ACPI_OBJECT_LIST, *PACPI_OBJECT_LIST;



/*
 * Miscellaneous common Data Structures used by the interfaces
 */

typedef struct 
{
    UINT32                  Length;         /* Length in bytes of the buffer */
    void                    *Pointer;       /* pointer to buffer */

} ACPI_BUFFER;


/*
 * Structure and flags for AcpiGetSystemInfo
 */

#define SYS_MODE_UNKNOWN    0x0000
#define SYS_MODE_ACPI       0x0001
#define SYS_MODE_LEGACY     0x0002
#define SYS_MODES_MASK      0x0003


/*
 * ACPI Table Info.  One per ACPI table _type_
 */
typedef struct AcpiTableInfo
{
    UINT32                  Count;

} ACPI_TABLE_INFO;


/*
 * System info returned by AcpiGetSystemInfo()
 */

typedef struct _AcpiSysInfo 
{
    UINT32                  Flags;

    UINT32                  TimerResolution;
    UINT32                  Reserved1;
    UINT32                  Reserved2;
    UINT32                  DebugLevel;
    UINT32                  DebugLayer;
    UINT32                  NumTableTypes;
    ACPI_TABLE_INFO         TableInfo [NUM_ACPI_TABLES];

} ACPI_SYSTEM_INFO;



/*
 * Various handlers and callback procedures
 */


typedef 
UINT32 (*FIXED_EVENT_HANDLER) (
    void                    *Context);

typedef
void (*GPE_HANDLER) (
    void                    *Context);

typedef
void (*NOTIFY_HANDLER) (
    UINT32                  Value,
    void                    *Context);

#define ADDRESS_SPACE_READ      1
#define ADDRESS_SPACE_WRITE     2

typedef
ACPI_STATUS (*ADDRESS_SPACE_HANDLER) (
    UINT32                  Function,
    UINT32                  Address,
    UINT32                  BitWidth,
    UINT32                  *Value,
    void                    *Context);

#define ACPI_DEFAULT_HANDLER     ((ADDRESS_SPACE_HANDLER) NULL)

typedef
ACPI_STATUS (*WALK_CALLBACK) (
    ACPI_HANDLE             ObjHandle,
    UINT32                  NestingLevel,
    void                    *Context,
    void                    **ReturnValue);

/* Interrupt handler return values (must be unique bits) */

#define INTERRUPT_HANDLED       0x01
#define INTERRUPT_NOT_HANDLED   0x02
#define INTERRUPT_ERROR         0x04



/* Structure and flags for AcpiGetDeviceInfo */

#define ACPI_VALID_HID          0x1
#define ACPI_VALID_UID          0x2
#define ACPI_VALID_ADR          0x4
#define ACPI_VALID_STA          0x8


#define ACPI_COMMON_OBJ_INFO \
    ACPI_OBJECT_TYPE        Type;           /* ACPI object type */\
    ACPI_NAME               Name;           /* ACPI object Name */\
    /*\
     *  BUGBUG:Do we want or need these next two??\
     */\
    ACPI_HANDLE             Parent;         /* Parent object */\
    ACPI_HANDLE             Children;       /* Linked list of children */\
    UINT32                  Valid           /* ?????    */

typedef struct 
{
    ACPI_COMMON_OBJ_INFO;
} ACPI_OBJ_INFO_HEADER;

typedef struct 
{
    ACPI_COMMON_OBJ_INFO;

    /*
     *  BUGBUG: a HID or a _UID can return either a number or a string
     */
    UINT32                  HardwareId;     /*  _HID value if any */
    UINT32                  UniqueId;       /*  _UID value if any */
    UINT32                  Address;        /*  _ADR value if any */
    UINT32                  CurrentStatus;  /*  _STA value */
} ACPI_DEVICE_INFO;




/* TBD: remove! */

//#include <internal.h>



/*
 * Definitions for Resource Attributes
 */

/* 
 *  Memory Attributes 
 */
#define READ_ONLY_MEMORY            (UINT8) 0x00
#define READ_WRITE_MEMORY           (UINT8) 0x01

#define NON_CACHEABLE_MEMORY        (UINT8) 0x00
#define CACHABLE_MEMORY             (UINT8) 0x01
#define WRITE_COMBINING_MEMORY      (UINT8) 0x02
#define PREFETCHABLE_MEMORY         (UINT8) 0x03

/* 
 *  IO Attributes 
 *  The ISA IO ranges are: n000-n0FFh,  n400-n4FFh, n800-n8FFh, nC00-nCFFh.
 *  The non-ISA IO ranges are: n100-n3FFh,  n500-n7FFh, n900-nBFFh, nCD0-nFFFh.
 */
#define NON_ISA_ONLY_RANGES         (UINT8) 0x01
#define ISA_ONLY_RANGES             (UINT8) 0x02
#define ENTIRE_RANGE                (NON_ISA_ONLY_RANGES | ISA_ONLY_RANGES)

/*
 *  IO Port Descriptor Decode
 */
#define DECODE_10                   (UINT8) 0x00    /* 10-bit IO address decode */
#define DECODE_16                   (UINT8) 0x01    /* 16-bit IO address decode */

/*
 *  IRQ Attributes
 */
#define EDGE_SENSITIVE              (UINT8) 0x00
#define LEVEL_SENSITIVE             (UINT8) 0x01

#define ACTIVE_HIGH                 (UINT8) 0x00
#define ACTIVE_LOW                  (UINT8) 0x01

#define EXCLUSIVE                   (UINT8) 0x00
#define SHARED                      (UINT8) 0x01

/* 
 *  DMA Attributes 
 */
#define COMPATIBILITY               (UINT8) 0x00
#define TYPE_A                      (UINT8) 0x01
#define TYPE_B                      (UINT8) 0x02
#define TYPE_F                      (UINT8) 0x03

#define NOT_BUS_MASTER              (UINT8) 0x00
#define BUS_MASTER                  (UINT8) 0x01

#define TRANSFER_8                  (UINT8) 0x00
#define TRANSFER_8_16               (UINT8) 0x01
#define TRANSFER_16                 (UINT8) 0x02

/*
 * Start Dependent Functions Priority definitions
 */
#define GOOD_CONFIGURATION          (UINT8) 0x00
#define ACCEPTABLE_CONFIGURATION    (UINT8) 0x01
#define SUB_OPTIMAL_CONFIGURATION   (UINT8) 0x02
 
/* 
 *  16, 32 and 64-bit Address Descriptor resource types 
 */
#define MEMORY_RANGE                (UINT8) 0x00
#define IO_RANGE                    (UINT8) 0x01
#define BUS_NUMBER_RANGE            (UINT8) 0x02

#define ADDRESS_NOT_FIXED           (UINT8) 0x00
#define ADDRESS_FIXED               (UINT8) 0x01

#define POS_DECODE                  (UINT8) 0x00
#define SUB_DECODE                  (UINT8) 0x01

#define PRODUCER                    (UINT8) 0x00
#define CONSUMER                    (UINT8) 0x01


/*
 *  Structures used to describe device resources
 */
typedef struct
{
    UINT32                  EdgeLevel;
    UINT32                  ActiveHighLow;
    UINT32                  SharedExclusive;
    UINT32                  NumberOfInterrupts;
    UINT32                  Interrupts[1];
} IRQ_RESOURCE;

typedef struct
{
    UINT32                  Type;
    UINT32                  BusMaster;
    UINT32                  Transfer;
    UINT32                  NumberOfChannels;
    UINT32                  Channels[1];
} DMA_RESOURCE;

typedef struct
{
    UINT32                  CompatibilityPriority;
    UINT32                  PerformanceRobustness;
} START_DEPENDENT_FUNCTIONS_RESOURCE;

/* 
 * END_DEPENDENT_FUNCTIONS_RESOURCE struct is not 
 *  needed because it has no fields
 */

typedef struct
{
    UINT32                  IoDecode;
    UINT32                  MinBaseAddress;
    UINT32                  MaxBaseAddress;
    UINT32                  Alignment;
    UINT32                  RangeLength;
} IO_RESOURCE;

typedef struct
{
    UINT32                  BaseAddress;
    UINT32                  RangeLength;
} FIXED_IO_RESOURCE;

typedef struct
{
    UINT32                  Length;
    UINT8                   Reserved[1];
} VENDOR_RESOURCE;

typedef struct
{
    UINT32                  ReadWriteAttribute;
    UINT32                  MinBaseAddress;
    UINT32                  MaxBaseAddress;
    UINT32                  Alignment;
    UINT32                  RangeLength;
} MEMORY24_RESOURCE;

typedef struct
{
    UINT32                  ReadWriteAttribute;
    UINT32                  MinBaseAddress;
    UINT32                  MaxBaseAddress;
    UINT32                  Alignment;
    UINT32                  RangeLength;
} MEMORY32_RESOURCE;

typedef struct
{
    UINT32                  ReadWriteAttribute;
    UINT32                  RangeBaseAddress;
    UINT32                  RangeLength;
} FIXED_MEMORY32_RESOURCE;

typedef struct
{
    UINT16                  CacheAttribute;
    UINT16                  ReadWriteAttribute;
} MEMORY_ATTRIBUTE;

typedef struct
{
    UINT16                  RangeAttribute;
    UINT16                  Reserved;
} IO_ATTRIBUTE;

typedef struct
{
    UINT16                  Reserved1;
    UINT16                  Reserved2;
} BUS_ATTRIBUTE; 

typedef union
{
    MEMORY_ATTRIBUTE        Memory;
    IO_ATTRIBUTE            Io;
    BUS_ATTRIBUTE           Bus;
} ATTRIBUTE_DATA;

typedef struct
{
    UINT32                  ResourceType;
    UINT32                  ProducerConsumer;
    UINT32                  Decode;
    UINT32                  MinAddressFixed;
    UINT32                  MaxAddressFixed;
    ATTRIBUTE_DATA          Attribute;
    UINT32                  Granularity;
    UINT32                  MinAddressRange;
    UINT32                  MaxAddressRange;
    UINT32                  AddressTranslationOffset;
    UINT32                  AddressLength;
    UINT32                  ResourceSourceIndex;
    UINT32                  ResourceSourceStringLength;
    UINT8                   ResourceSource[1];
    
} ADDRESS16_RESOURCE;

typedef struct  
{
    UINT32                  ResourceType;
    UINT32                  ProducerConsumer;
    UINT32                  Decode;
    UINT32                  MinAddressFixed;
    UINT32                  MaxAddressFixed;
    ATTRIBUTE_DATA          Attribute;
    UINT32                  Granularity;
    UINT32                  MinAddressRange;
    UINT32                  MaxAddressRange;
    UINT32                  AddressTranslationOffset;
    UINT32                  AddressLength;
    UINT32                  ResourceSourceIndex;
    UINT32                  ResourceSourceStringLength;
    UINT8                   ResourceSource[1];
    
} ADDRESS32_RESOURCE;

typedef struct
{
    UINT32                  ProducerConsumer;
    UINT32                  EdgeLevel;
    UINT32                  ActiveHighLow;
    UINT32                  SharedExclusive;
    UINT32                  NumberOfInterrupts;
    UINT32                  Interrupts[1];
    UINT32                  ResourceSourceIndex;
    UINT32                  ResourceSourceStringLength;
    UINT8                   ResourceSource[1];
} EXTENDED_IRQ_RESOURCE;

typedef enum
{
    Irq,
    Dma,
    StartDependentFunctions,
    EndDependentFunctions,
    Io,
    FixedIo,
    VendorSpecific,
    EndTag,
    Memory24,
    Memory32,
    FixedMemory32,
    Address16,
    Address32,
    ExtendedIrq
} RESOURCE_TYPE;

typedef union
{
    IRQ_RESOURCE                        Irq;
    DMA_RESOURCE                        Dma;
    START_DEPENDENT_FUNCTIONS_RESOURCE  StartDependentFunctions;
    IO_RESOURCE                         Io;
    FIXED_IO_RESOURCE                   FixedIo;
    VENDOR_RESOURCE                     VendorSpecific;
    MEMORY24_RESOURCE                   Memory24;
    MEMORY32_RESOURCE                   Memory32;
    FIXED_MEMORY32_RESOURCE             FixedMemory32;
    ADDRESS16_RESOURCE                  Address16;
    ADDRESS32_RESOURCE                  Address32;
    EXTENDED_IRQ_RESOURCE               ExtendedIrq;
} RESOURCE_DATA;

typedef struct _resource_tag
{
    RESOURCE_TYPE           Id;
    UINT32                  Length;
    RESOURCE_DATA           Data;
} RESOURCE;

#define RESOURCE_LENGTH             12
#define RESOURCE_LENGTH_NO_DATA     8

/*
 * END: Definitions for Resource Attributes
 */

/*
 * Definitions for PCI Routing tables
 */
typedef struct  
{
    UINT32                  Address;
    UINT32                  Pin;
    UINT32                  SourceIndex;
    UINT8                   Source[1];
} PRT_ENTRY;

typedef struct _prt_tag
{
    UINT32                  Length;
    PRT_ENTRY               Data;
} PCI_ROUTING_TABLE;

/*
 * END: Definitions for PCI Routing tables
 */

#endif /* ACPITYPES_H */
