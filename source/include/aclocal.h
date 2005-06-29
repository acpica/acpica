
/******************************************************************************
 * 
 * Name: internal.h - Internal data types used across the ACPI subsystem
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

#ifndef _ACPI_INTERNAL_H
#define _ACPI_INTERNAL_H

#include "config.h"


#define WAIT_FOREVER        -1

typedef void*               ACPI_MUTEX;
typedef UINT32              ACPI_MUTEX_HANDLE;


/*
 * Predefined handles for the mutex objects used within the subsystem
 * All mutex objects are automatically created by CmMutexInitialize.
 */

#define MTX_INTERPRETER     0
#define MTX_NAMESPACE       1
#define MTX_MEMORY          2
#define MTX_GP_EVENT        3
#define MTX_FIXED_EVENT     4
#define MTX_OP_REGIONS      5

#define MAX_MTX             5
#define NUM_MTX             MAX_MTX+1


/* Operational modes of the AML interpreter/scanner */

typedef enum 
{
    IMODE_LoadPass1 = 0x01,
    IMODE_LoadPass2 = 0x02,
    IMODE_Execute   = 0x0E

} OPERATING_MODE;


/* 
 * Typedef nte (name table entry) is private to avoid global
 * impact in the event of changes to it.  The externally-known type ACPI_HANDLE
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
    ACPI_OBJECT_TYPE        Type;           /* Type associated with this name */
    void                    *Object;        /* Pointer to attached ACPI object */

} NAME_TABLE_ENTRY;

#define ENTRY_NOT_FOUND     NULL
#define INVALID_HANDLE      0
#define NULL_HANDLE         INVALID_HANDLE


/* 
 * Stack of currently executing control methods 
 * Contains the arguments and local variables for each nested method.
 */

typedef struct
{
    union AcpiObjInternal   *Arguments[MTH_NUM_ARGS];
    union AcpiObjInternal   *LocalVariables[MTH_NUM_LOCALS];

} METHOD_STACK;


/* Stack of currently-open scopes, and pointer to top of that stack */

typedef struct
{
    NAME_TABLE_ENTRY        *Scope;
    /* 
     * Type of scope, typically the same as the type of its parent's entry 
     * (but not the same as the type of its parent's scope).
     */
    ACPI_OBJECT_TYPE        Type;   


} SCOPE_STACK;    


typedef struct 
{
    char                    *SearchFor;
    ACPI_HANDLE             *List;
    INT32                   *Count;

} FIND_CONTEXT;


typedef struct
{
    NAME_TABLE_ENTRY        *PreviousEntry;
    NAME_TABLE_ENTRY        *NameTable;
    UINT32                  Position;
    BOOLEAN                 TableFull;

} NS_SEARCH_DATA;


/*
 * Predefined Namespace items
 */
#define ACPI_MAX_ADDRESS_SPACE      255
#define ACPI_NUM_ADDRESS_SPACES     256


typedef struct
{
    char                    *Name;
    ACPI_OBJECT_TYPE        Type;
    char                    *Val;

} PREDEFINED_NAMES;


/* 
 * Entry in the AddressSpace (AKA Operation Region) table
 */

typedef struct
{
    ADDRESS_SPACE_HANDLER   Handler;
    void                    *Context;

} ADDRESS_SPACE_INFO;


/* Values and addresses of the GPE registers (both banks) */

typedef struct 
{
    UINT8                   Status;         /* Current value of status reg */
    UINT8                   Enable;         /* Current value of enable reg */
    UINT16                  StatusAddr;     /* Address of status reg */
    UINT16                  EnableAddr;     /* Address of enable reg */

} GPE_REGISTERS;


#define GPE_LEVEL_TRIGGERED         1
#define GPE_EDGE_TRIGGERED          2


/* Information about each particular GPE level */

typedef struct
{
    UINT8                   Type;           /* Level or Edge */
    ACPI_HANDLE             MethodHandle;   /* Method handle for direct (fast) execution */
    GPE_HANDLER             Handler;        /* Address of handler, if any */
    void                    *Context;       /* Context to be passed to handler */

} GPE_LEVEL_INFO;

/* Information about each particular fixed event */

typedef struct
{
	FIXED_EVENT_HANDLER		Handler;		/* Address of handler. */
	void					*Context;		/* Context to be passed to handler */
} FIXED_EVENT_INFO;


/* Entry for a memory allocation (debug only) */


#define MEM_MALLOC          0
#define MEM_CALLOC          1

typedef struct AllocationInfo 
{
    void                    *Address;
    UINT32                  Size;
    UINT8                   AllocType;
    UINT32                  Component;
    char                    Module[32];
    INT32                   Line;
    struct AllocationInfo   *Previous;
    struct AllocationInfo   *Next;

} ALLOCATION_INFO;


#endif
