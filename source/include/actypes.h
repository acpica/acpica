
/******************************************************************************
 * 
 * Name: datatypes.h - Common data types for the entire ACPI subsystem
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

#ifndef _DATATYPES_H
#define _DATATYPES_H

#include <environment.h>


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

typedef unsigned char       BOOLEAN;
typedef int                 INT;
typedef unsigned int        UINT;
typedef signed char         INT8;
typedef unsigned char       UINT8;
typedef short               INT16;
typedef unsigned short      UINT16;
typedef int                 INT32;
typedef unsigned int        UINT32;
typedef unsigned char       UCHAR;

typedef unsigned char       UINT8_BIT;
typedef unsigned short      UINT16_BIT;
typedef unsigned long       UINT32_BIT;

typedef int                 BIT32;
typedef short int           BIT16;
typedef char                BIT8;

typedef int                 ACPI_PTRDIFF;
typedef unsigned int        ACPI_SIZE;


/* 
 * Local datatypes 
 */


typedef UINT32              ACPI_STATUS;    /* All ACPI Exceptions */
typedef UINT32              ACPI_NAME;      /* 4-char ACPI name */
typedef char*               ACPI_STRING;    /* Null terminated ASCII string */
typedef void*               ACPI_HANDLE;    /* Actually a ptr to an NTE */


/*
 *  Table types.  These values are passed to the table related APIs
 */

typedef UINT32              ACPI_TABLE_TYPE;

#define TABLE_RSDPTR        (ACPI_TABLE_TYPE) 0
#define TABLE_APIC          (ACPI_TABLE_TYPE) 1
#define TABLE_DSDT          (ACPI_TABLE_TYPE) 2
#define TABLE_FACP          (ACPI_TABLE_TYPE) 3
#define TABLE_FACS          (ACPI_TABLE_TYPE) 4
#define TABLE_PSDT          (ACPI_TABLE_TYPE) 5
#define TABLE_RSDT          (ACPI_TABLE_TYPE) 6
#define TABLE_SSDT          (ACPI_TABLE_TYPE) 7
#define TABLE_SBDT          (ACPI_TABLE_TYPE) 8
#define ACPI_TABLE_MAX      8
#define NUM_ACPI_TABLES     9


/* 
 * Types associated with names
 * Values correspond to the definition of the ObjectType operator.
 * Must coordinate with NsProperties and NsTypeNames in acpinmsp.c
 * The ACPI_OBJECT_TYPE type is also used in OBJECT_DESCRIPTOR defined in amlpriv.h
 */

typedef UINT32              ACPI_OBJECT_TYPE;

#define TYPE_Any            (ACPI_OBJECT_TYPE) 0
#define TYPE_Number         (ACPI_OBJECT_TYPE) 1  /* Byte/Word/Dword/Zero/One/Ones */
#define TYPE_String         (ACPI_OBJECT_TYPE) 2
#define TYPE_Buffer         (ACPI_OBJECT_TYPE) 3
#define TYPE_Package        (ACPI_OBJECT_TYPE) 4  /* ByteConst, multiple DataTerm/Constant/SuperName */
#define TYPE_FieldUnit      (ACPI_OBJECT_TYPE) 5
#define TYPE_Device         (ACPI_OBJECT_TYPE) 6  /* Name, multiple NamedObject */
#define TYPE_Event          (ACPI_OBJECT_TYPE) 7
#define TYPE_Method         (ACPI_OBJECT_TYPE) 8  /* Name, ByteConst, multiple Code */
#define TYPE_Mutex          (ACPI_OBJECT_TYPE) 9
#define TYPE_Region         (ACPI_OBJECT_TYPE) 10
#define TYPE_Power          (ACPI_OBJECT_TYPE) 11 /* Name,ByteConst,WordConst,multi NamedObject */
#define TYPE_Processor      (ACPI_OBJECT_TYPE) 12 /* Name,ByteConst,DWordConst,ByteConst,multi NmO */
#define TYPE_Thermal        (ACPI_OBJECT_TYPE) 13 /* Name, multiple NamedObject */
#define TYPE_Alias          (ACPI_OBJECT_TYPE) 14
#define ACPI_TYPE_MAX       14
    /* 
     * The remaining values do not relate to the ObjectType operator and are
     * used for various internal purposes only.  A gap is provided in case more
     * official ObjectTypes are added in the future.  Also, values exceeding
     * the largest ObjectType must not overlap with defined AML opcodes.
     */
#define TYPE_DefField       (ACPI_OBJECT_TYPE) 25
#define TYPE_BankField      (ACPI_OBJECT_TYPE) 26
#define TYPE_IndexField     (ACPI_OBJECT_TYPE) 27
#define TYPE_DefFieldDefn   (ACPI_OBJECT_TYPE) 28 /* Name, ByteConst, multiple FieldElement */
#define TYPE_BankFieldDefn  (ACPI_OBJECT_TYPE) 29 /* 2 Name,DWordConst,ByteConst,multi FieldElement */
#define TYPE_IndexFieldDefn (ACPI_OBJECT_TYPE) 30 /* 2 Name, ByteConst, multiple FieldElement */
#define TYPE_If             (ACPI_OBJECT_TYPE) 31 /* OpCode, multiple Code */
#define TYPE_Else           (ACPI_OBJECT_TYPE) 32 /* multiple Code */
#define TYPE_While          (ACPI_OBJECT_TYPE) 33 /* OpCode, multiple Code */
#define TYPE_Scope          (ACPI_OBJECT_TYPE) 34 /* Name, multiple NamedObject */
#define TYPE_DefAny         (ACPI_OBJECT_TYPE) 35 /* type is Any, suppress search of enclosing scopes */
#define TYPE_Lvalue         (ACPI_OBJECT_TYPE) 36 /* Arg#, Local#, Name, Debug; used only in descriptors */
#define INTERNAL_TYPE_MAX   36

#define TYPE_Invalid        (ACPI_OBJECT_TYPE) 0xFF


/* 
 * Fixed event types 
 */

typedef UINT32              ACPI_EVENT_TYPE;

#define EVENT_PMTIMER       (ACPI_EVENT_TYPE) 0
    /* 
     * There's no bus master event so index 1 is used for IRQ's that are not
     * handled by the SCI handler 
     */
#define EVENT_NOT_USED      (ACPI_EVENT_TYPE) 1
#define EVENT_GLOBAL        (ACPI_EVENT_TYPE) 2
#define EVENT_POWER_BUTTON  (ACPI_EVENT_TYPE) 3
#define EVENT_SLEEP_BUTTON  (ACPI_EVENT_TYPE) 4
#define EVENT_RTC           (ACPI_EVENT_TYPE) 5
#define EVENT_GENERAL       (ACPI_EVENT_TYPE) 6
#define ACPI_EVENT_MAX      6
#define NUM_FIXED_EVENTS    (ACPI_EVENT_TYPE) 7



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

#define SYS_MODE_ACPI       0x0001
#define SYS_MODE_LEGACY     0x0002
#define SYS_MODES_MASK      0x0003


typedef struct _AcpiSysInfo 
{
    UINT32                  Flags;
    UINT32                  TimerResolution;
    UINT32                  Reserved1;
    UINT32                  Reserved2;
    UINT32                  DebugLevel;
    UINT32                  DebugLayer;

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


typedef
void (*OPREGION_HANDLER) (
    void                    *Context);


typedef
void * (*WALK_CALLBACK) (
    ACPI_HANDLE             ObjHandle,
    UINT32                  NestingLevel,
    void                    *Context);



/* Interrupt handler return values (must be unique bits) */

#define INTERRUPT_HANDLED       0x01
#define INTERRUPT_NOT_HANDLED   0x02
#define INTERRUPT_ERROR         0x04



/* Structure and flags for AcpiGetDeviceInfo */

#define ACPI_VALID_HID          0x1
#define ACPI_VALID_UID          0x2
#define ACPI_VALID_ADR          0x4
#define ACPI_VALID_STA          0x8

typedef struct 
{
    UINT32                  Valid;
    UINT32                  HardwareId;
    UINT32                  UniqueId;
    UINT32                  Address;
    UINT32                  CurrentStatus;

} ACPI_DEVICE_INFO;


/* Control method information struct */
/* Not really public, but appears in the ACPI_OBJECT_INTERNAL definition */

typedef struct
{
   ACPI_PTRDIFF             Offset;      /* offset to MethodFlags in AML pcode block */
   UINT32                   Length;      /* length of method code including MethodFlags */

} METHOD_INFO;


/*
 * data type ranges
 */

#define ACPI_UCHAR_MAX      0xFF
#define ACPI_INT_MAX        0x7FFFFFFF
#define ACPI_UINT_MAX       0xFFFFFFFF
#define ACPI_LONG_MAX       0x7FFFFFFF
#define ACPI_ULONG_MAX      0xFFFFFFFF

 
 /* 
 * Data manipulation macros 
 */

#ifndef LOWORD
#define LOWORD(l)           ((UINT16)(UINT32)(l))
#endif

#ifndef HIWORD
#define HIWORD(l)           ((UINT16)((((UINT32)(l)) >> 16) & 0xFFFF))
#endif  

#ifndef LOBYTE
#define LOBYTE(l)           ((UINT8)(UINT16)(l))
#endif

#ifndef HIBYTE
#define HIBYTE(l)           ((UINT8)((((UINT16)(l)) >> 8) & 0xFF))
#endif

#define BIT0(x)             ((((x) & 0x01) > 0) ? 1 : 0)
#define BIT1(x)             ((((x) & 0x02) > 0) ? 1 : 0)
#define BIT2(x)             ((((x) & 0x04) > 0) ? 1 : 0)
#define BIT3(x)             ((((x) & 0x08) > 0) ? 1 : 0)
#define BIT4(x)             ((((x) & 0x10) > 0) ? 1 : 0)
#define BIT5(x)             ((((x) & 0x20) > 0) ? 1 : 0)
#define BIT6(x)             ((((x) & 0x40) > 0) ? 1 : 0)
#define BIT7(x)             ((((x) & 0x80) > 0) ? 1 : 0)

#define LOW_BASE(w)         ((UINT16) ((w) & 0x0000FFFF))
#define MID_BASE(b)         ((UINT8) (((b) & 0x00FF0000) >> 16))
#define HI_BASE(b)          ((UINT8) (((b) & 0xFF000000) >> 24))
#define LOW_LIMIT(w)        ((UINT16) ((w) & 0x0000FFFF))
#define HI_LIMIT(b)         ((UINT8) (((b) & 0x00FF0000) >> 16))


/*
 * Fast power-of-two math for non-optimized compilers
 */

#define DIV_2(a)            ((a)>>1)
#define MUL_2(a)            ((a)<<1)
#define MOD_2(a)            ((a)&0x01)

#define DIV_4(a)            ((a)>>2)
#define MUL_4(a)            ((a)<<2)
#define MOD_4(a)            ((a)&0x03)

#define DIV_8(a)            ((a)>>3)
#define MUL_8(a)            ((a)<<3)
#define MOD_8(a)            ((a)&0x07)

#define DIV_16(a)           ((a)>>4)
#define MUL_16(a)           ((a)<<4)
#define MOD_16(a)           ((a)&0x0F)


/* 
 * Useful defines 
 */

#ifdef FALSE
#undef FALSE
#endif
#define FALSE               (1 == 0)

#ifdef TRUE
#undef TRUE
#endif
#define TRUE                (1 == 1)

#ifndef NULL
#define NULL                (void *) 0
#endif




/* TBD: remove! */

#include <internal.h>


#endif /* DATATYPES_H */
