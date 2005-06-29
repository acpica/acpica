
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
 * 2.1. Intel grants, free of charge, to any person ("Licensee") obtaining a 
 * copy of the source code appearing in this file ("Covered Code") a license 
 * under Intel's copyrights in the base code distributed originally by Intel 
 * ("Original Intel Code") to copy, make derivatives, distribute, use and 
 * display any portion of the Covered Code in any form; and
 *
 * 2.2. Intel grants Licensee a non-exclusive and non-transferable patent 
 * license (without the right to sublicense), under only those claims of Intel
 * patents that are infringed by the Original Intel Code, to make, use, sell, 
 * offer to sell, and import the Covered Code and derivative works thereof 
 * solely to the minimum extent necessary to exercise the above copyright 
 * license, and in no event shall the patent license extend to any additions to
 * or modifications of the Original Intel Code.  No other license or right is 
 * granted directly or by implication, estoppel or otherwise;
 *
 * the above copyright and patent license is granted only if the following 
 * conditions are met:
 *
 * 3. Conditions 
 *
 * 3.1. Redistribution of source code of any substantial portion of the Covered 
 * Code or modification must include the above Copyright Notice, the above 
 * License, this list of Conditions, and the following Disclaimer and Export 
 * Compliance provision.  In addition, Licensee must cause all Covered Code to 
 * which Licensee contributes to contain a file documenting the changes 
 * Licensee made to create that Covered Code and the date of any change.  
 * Licensee must include in that file the documentation of any changes made by
 * any predecessor Licensee.  Licensee must include a prominent statement that
 * the modification is derived, directly or indirectly, from Original Intel 
 * Code.
 *
 * 3.2. Redistribution in binary form of any substantial portion of the Covered 
 * Code or modification must reproduce the above Copyright Notice, and the 
 * following Disclaimer and Export Compliance provision in the documentation 
 * and/or other materials provided with the distribution.
 *
 * 3.3. Intel retains all right, title, and interest in and to the Original 
 * Intel Code.
 *
 * 3.4. Neither the name Intel nor any other trademark owned or controlled by 
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
 * event Licensee exports any such software from the United States or re-
 * exports any such software from a foreign destination, Licensee shall ensure
 * that the distribution and export/re-export of the software is in compliance 
 * with all laws, regulations, orders, or other restrictions of the U.S. Export 
 * Administration Regulations. Licensee agrees that neither it nor any of its 
 * subsidiaries will export/re-export any technical data, process, software, or 
 * service, directly or indirectly, to any country for which the United States 
 * government or any agency thereof requires an export license, other 
 * governmental approval, or letter of assurance, without first obtaining such
 * license, approval or letter.
 *
 *****************************************************************************/


#ifndef _DATATYPES_H
#define _DATATYPES_H

#include <stddef.h>


/* 
 * Data types - Fixed across all compilation models
 * 
 * BOOLEAN	    Logical Boolean. 1 byte value containing a 0 for FALSE or a 1 for TRUE.  Other values are undefined.
 * INT	        Signed value. (4 bytes on IA-32, 8 bytes on IA-64)
 * UINT	        Unsigned value. (4 bytes on IA-32, 8 bytes on IA-64)
 * INT8	        1 byte signed value
 * UINT8	    1 byte unsigned value
 * INT16	    2 byte signed value
 * UINT16	    2 byte unsigned value
 * INT32	    4 byte signed value
 * UINT32	    4 byte unsigned value
 * INT64        8 byte signed value (not supported or used at this time)
 * UINT64	    8 byte unsigned value (not supported or used at this time)
 * UCHAR	    Character. 1 byte unsigned value. 
 * WCHAR	    Wide Character. 2 byte unsigned value (not supported or used at this time) 
 */

/* 
 * TBD:  Need a 32-bit vs. 64-bit section !!! 
 */

/*  IA-32 type definitions */

typedef unsigned char   BOOLEAN;
typedef int             INT;
typedef unsigned int    UINT;
typedef signed char     INT8;
typedef unsigned char   UINT8;
typedef short           INT16;
typedef unsigned short  UINT16;
typedef int             INT32;
typedef unsigned int    UINT32;
typedef unsigned char   UCHAR;

typedef unsigned char   UINT8_BIT;
typedef unsigned short  UINT16_BIT;
typedef unsigned long   UINT32_BIT;

typedef int             BIT32;
typedef short int       BIT16;
typedef char            BIT8;

/* 
 * Data manipulation macros 
 */

#ifndef LOWORD
#define LOWORD(l)       ((UINT16)(UINT32)(l))
#endif

#ifndef HIWORD
#define HIWORD(l)       ((UINT16)((((UINT32)(l)) >> 16) & 0xFFFF))
#endif  

#ifndef LOBYTE
#define LOBYTE(l)       ((UINT8)(UINT16)(l))
#endif

#ifndef HIBYTE
#define HIBYTE(l)       ((UINT8)((((UINT16)(l)) >> 8) & 0xFF))
#endif

#define BIT0(x) 	    ((((x) & 0x01) > 0) ? 1 : 0)
#define BIT1(x)    	    ((((x) & 0x02) > 0) ? 1 : 0)
#define BIT2(x)   	    ((((x) & 0x04) > 0) ? 1 : 0)
#define BIT3(x)   	    ((((x) & 0x08) > 0) ? 1 : 0)
#define BIT4(x)   	    ((((x) & 0x10) > 0) ? 1 : 0)
#define BIT5(x)    	    ((((x) & 0x20) > 0) ? 1 : 0)
#define BIT6(x)  	    ((((x) & 0x40) > 0) ? 1 : 0)
#define BIT7(x)    	    ((((x) & 0x80) > 0) ? 1 : 0)

#define LOW_BASE(w)     ((UINT16) ((w) & 0x0000FFFF))
#define MID_BASE(b)     ((UINT8) (((b) & 0x00FF0000) >> 16))
#define HI_BASE(b)      ((UINT8) (((b) & 0xFF000000) >> 24))
#define LOW_LIMIT(w)  	((UINT16) ((w) & 0x0000FFFF))
#define HI_LIMIT(b)     ((UINT8) (((b) & 0x00FF0000) >> 16))


/* 
 * Useful defines 
 */

#ifdef FALSE
#undef FALSE
#endif
#define FALSE           (1 == 0)

#ifdef TRUE
#undef TRUE
#endif
#define TRUE            (1 == 1)

#ifndef NULL
#define NULL            (void *)0
#endif


/* 
 * Local datatypes 
 */

/* Types specific to the OS-independent subsystem interfaces */

typedef INT32           ACPI_STATUS;

/* Types specific to the OS-dependent interface */

typedef void            OSD_FILE;


/*
 * Debug/Error reporting table definition
 */

typedef struct
{
    char            *Key;
    char            Level;
    char            *Description;
    char            *Description2;

} ST_KEY_DESC_TABLE;


/*
 *  Table types.  These values are passed to the table related APIs
 */

typedef enum {
    RSDPTR_Ord    = 0,
    APIC_Ord,
    DSDT_Ord,
    FACP_Ord,
    FACS_Ord,
    PSDT_Ord,
    RSDT_Ord,
    SSDT_Ord,
    SBDT_Ord
} AcpiTableType;



/* Operational mode of AML scanner */

typedef enum {
    MODE_Load    = 0,
    MODE_Exec    = 1,
    MODE_Load1   = 2
} OpMode;


/* Control method information struct */

typedef struct
{
   ptrdiff_t            Offset;      /* offset to MethodFlags in AML pcode block */
   UINT32               Length;      /* length of method code including MethodFlags */

} METHOD_INFO;

/* NsHandle is actually an nte * */

typedef void*           NsHandle;


/* 
 * Types associated with names
 * Values correspond to the definition of the ObjectType operator.
 * Must coordinate with NsProperties and NsTypeNames in acpinmsp.c
 * The NsType type is also used in OBJECT_DESCRIPTOR defined in amlpriv.h
 */

typedef enum {
   TYPE_Any              =  0,
   TYPE_Number           =  1, /* Byte/Word/Dword/Zero/One/Ones */
   TYPE_String           =  2,
   TYPE_Buffer           =  3,
   TYPE_Package          =  4, /* ByteConst, multiple DataTerm/Constant/SuperName */
   TYPE_FieldUnit        =  5,
   TYPE_Device           =  6, /* Name, multiple NamedObject */
   TYPE_Event            =  7,
   TYPE_Method           =  8, /* Name, ByteConst, multiple Code */
   TYPE_Mutex            =  9,
   TYPE_Region           = 10,
   TYPE_Power            = 11, /* Name,ByteConst,WordConst,multi NamedObject */
   TYPE_Processor        = 12, /* Name,ByteConst,DWordConst,ByteConst,multi NmO */
   TYPE_Thermal          = 13, /* Name, multiple NamedObject */
   TYPE_Alias            = 14,

/* 
 * The remaining values do not relate to the ObjectType operator and are
 * used for various internal purposes.  A gap is provided in case more
 * official ObjectType's are added in the future.  Also, values exceeding
 * the largest ObjectType need to not overlap with defined AML opcodes.
 */
   TYPE_DefField         = 25,
   TYPE_BankField        = 26,
   TYPE_IndexField       = 27,
   TYPE_DefFieldDefn     = 28, /* Name, ByteConst, multiple FieldElement */
   TYPE_BankFieldDefn    = 29, /* 2 Name,DWordConst,ByteConst,multi FieldElement */
   TYPE_IndexFieldDefn   = 30, /* 2 Name, ByteConst, multiple FieldElement */
   TYPE_If               = 31, /* OpCode, multiple Code */
   TYPE_Else             = 32, /* multiple Code */
   TYPE_While            = 33, /* OpCode, multiple Code */
   TYPE_Scope            = 34, /* Name, multiple NamedObject */
   TYPE_DefAny           = 35, /* type is Any, suppress search of enclosing scopes */
   TYPE_Lvalue           = 36  /* Arg#, Local#, Name, Debug; used only in descriptors */
} NsType;




/* 
 * Typedef nte (name table entry) is private to acpinmsp.c to avoid global
 * impact in the event of changes to it.  The externally-known type NsHandle
 * is actually an (nte *).  If an external program needs to extract a field
 * from the nte, it should use an access function defined in acpinmsp.c
 *
 * If you need an access function not provided herein, add it to this module
 * rather than exporting the nte typedef.
 *
 * (nte *) are actually used in two different and not entirely compatible
 * ways: as pointer to an individual nte and as pointer to an entire name
 * table (which is an array of nte, sometimes referred to as a scope).  In
 * the latter case, the specific nte pointed to may be unused; however its
 * ParentScope member will be valid.
 */

typedef struct NAME_TABLE_ENTRY
{
    UINT32                  Name;           /* Name segment, always 4 chars per ACPI spec.
                                             * NameSeg must be the first field in the nte
                                             * -- see the IsNsHandle macro in acpinmsp.h
                                             */
    struct NAME_TABLE_ENTRY *Scope;         /* Scope owned by this name */
    struct NAME_TABLE_ENTRY *ParentScope;   /* Previous level of names */
    struct NAME_TABLE_ENTRY *ParentEntry;   /* Actual parent NTE */
    struct NAME_TABLE_ENTRY *NextEntry;     /* Next within this scope */
    struct NAME_TABLE_ENTRY *PrevEntry;     /* Previous within this scope */
    NsType                  Type;           /* Type associated with this name */
    void                    *Value;         /* Pointer to value associated with this name */

} NAME_TABLE_ENTRY;

#define ENTRY_NOT_FOUND     NULL
#define INVALID_HANDLE      0
#define NULL_HANDLE         INVALID_HANDLE


/* Stack of currently-open scopes, and pointer to top of that stack */

typedef struct
{
    NAME_TABLE_ENTRY        *Scope;
    /* 
     * Type of scope, typically the same as the type of its parent's entry 
     * (but not the same as the type of its parent's scope).
     */
    NsType                  Type;   
} SCOPE_STACK;    


typedef struct 
{
    char                    *SearchFor;
    NsHandle                *List;
    INT32                   *Count;
} FIND_CONTEXT;


typedef struct
{
    NAME_TABLE_ENTRY        *PreviousEntry;
    NAME_TABLE_ENTRY        *NameTable;
    UINT32                  Position;
    BOOLEAN                 TableFull;
} NS_SEARCH_DATA;


typedef struct
{
    char                    *Name;
    NsType                  Type;
    char                    *Val;
} PREDEFINED_NAMES;


/*
 * Various handlers and callback procedures
 */


typedef 
UINT32 (*FIXED_EVENT_HANDLER) (
    void            *Context);

typedef
void (*GPE_HANDLER) (
    void            *Context);

typedef
void (*NOTIFY_HANDLER) (
    UINT32          Value,
    void            *Context);


typedef
void (*OPREGION_HANDLER) (
    void            *Context);


typedef
void * (*WALK_CALLBACK) (
    NsHandle        ObjHandle,
    UINT32          NestingLevel,
    void            *Context);


/* Fixed event types */

enum 
{
    EVENT_PMTIMER = 0,
    /* 
     * There's no bus master event so index 1 is used for IRQ's that are not
     * handled by the SCI handler 
     */
    EVENT_NOT_USED,
    EVENT_GLOBAL, 
    EVENT_POWER_BUTTON, 
    EVENT_SLEEP_BUTTON, 
    EVENT_RTC, 
    EVENT_GENERAL,
    NUM_FIXED_EVENTS
};


/* Values and addresses of the GPE registers (both banks) */

typedef struct 
{
    UINT8           Status;         /* Current value of status reg */
    UINT8           Enable;         /* Current value of enable reg */
    UINT16          StatusAddr;     /* Address of status reg */
    UINT16          EnableAddr;     /* Address of enable reg */

} GPE_REGISTERS;


#define GPE_LEVEL_TRIGGERED         1
#define GPE_EDGE_TRIGGERED          2


/* Information about each particular GPE level */

typedef struct
{
    UINT8           Type;           /* Level or Edge */
    NsHandle        MethodHandle;   /* Method handle for direct (fast) execution */
    GPE_HANDLER     Handler;        /* Address of handler, if any */
    void            *Context;       /* Context to be passed to handler */

} GPE_LEVEL_INFO;




#endif /* DATATYPES_H */