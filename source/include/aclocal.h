
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

#include <config.h>


#define WAIT_FOREVER        ((UINT32) -1)

typedef void*               ACPI_MUTEX;
typedef UINT32              ACPI_MUTEX_HANDLE;


/* Object descriptor types */

#define DESC_TYPE_NTE       0xEE
#define DESC_TYPE_ACPI_OBJ  0xAA
#define DESC_TYPE_PARSER    0xBB



/*****************************************************************************
 * 
 * Mutex typedefs and structs
 *
 ****************************************************************************/


/*
 * Predefined handles for the mutex objects used within the subsystem
 * All mutex objects are automatically created by CmMutexInitialize.
 * NOTE: any changes here must be reflected in the Gbl_MutexNames table also!
 */

#define MTX_EXECUTE         0
#define MTX_INTERPRETER     1
#define MTX_TABLES          2
#define MTX_NAMESPACE       3
#define MTX_MEMORY          4
#define MTX_EVENTS          5
#define MTX_OP_REGIONS      6
#define MTX_DEBUG_COMMAND   7
#define MTX_DEBUGGER        8

#define MAX_MTX             8
#define NUM_MTX             MAX_MTX+1


/* Table for the global mutexes */

typedef struct AcpiMutexInfo
{
    ACPI_MUTEX                  Mutex;
    UINT32                      UseCount;
    BOOLEAN                     Locked;

} ACPI_MUTEX_INFO;




#define TABLE_ID_DSDT           0xD1D1

/*****************************************************************************
 * 
 * Namespace typedefs and structs
 *
 ****************************************************************************/


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
 *
 * DataType is used to differentiate between internal descriptors, and MUST
 * be the first byte in this structure.
 */

typedef struct NameTableEntry
{
    UINT8                   DataType;
    UINT8                   Type;           /* Type associated with this name */
    UINT8                   Fill1;
    UINT8                   Flags;
    UINT32                  Name;           /* ACPI Name, always 4 chars per ACPI spec */


    void                    *Object;        /* Pointer to attached ACPI object (optional) */
    struct NameTableEntry   *Scope;         /* Scope owned by this name (optional) */
    struct NameTableEntry   *ParentEntry;   /* Parent NTE */
    struct NameTableEntry   *NextEntry;     /* Next NTE within this scope */
    struct NameTableEntry   *PrevEntry;     /* Previous NTE within this scope */

    UINT16                  TableId;        /* Owning ACPI Table */
    UINT16                  ReferenceCount; /* Current count of references and children */

    /* Align on 16-byte boundary for memory dump readability */
/*
    DEBUG_ONLY_MEMBERS (
    char                    *FillDebug) 
*/
} NAME_TABLE_ENTRY;


#define ENTRY_NOT_FOUND     NULL
#define INVALID_HANDLE      0
#define NULL_HANDLE         INVALID_HANDLE


/* NTE flags */

#define NTE_AML_ATTACHMENT  0x1

/* 
 * Stack of currently executing control methods 
 * Contains the arguments and local variables for each nested method.
 */

typedef struct Method_Stack
{
    union AcpiObjInternal   *Arguments[MTH_NUM_ARGS];
    union AcpiObjInternal   *LocalVariables[MTH_NUM_LOCALS];
    struct Method_Stack     *Next;

} METHOD_STACK;


/* Stack of currently-open scopes, and pointer to top of that stack */

typedef struct scope_stack
{
    NAME_TABLE_ENTRY        *Scope;
    /* 
     * Type of scope, typically the same as the type of its parent's entry 
     * (but not the same as the type of its parent's scope).
     */
    ACPI_OBJECT_TYPE        Type;   
    struct scope_stack      *Next;

} SCOPE_STACK;    



/*
 * ACPI Table Descriptor.  One per ACPI table
 */
typedef struct AcpiTableDesc
{
    struct AcpiTableDesc    *Prev;
    struct AcpiTableDesc    *Next;
    ACPI_TABLE_HEADER       *Pointer;
    void                    *BasePointer;
    NAME_TABLE_ENTRY        *RootEntry;
    UINT8                   *AmlPointer;
    UINT32                  AmlLength;
    UINT32                  Length;
    UINT32                  Count;
    UINT16                  TableId;
    UINT8                   Type;
    UINT8                   Allocation;
    BOOLEAN                 LoadedIntoNamespace;

} ACPI_TABLE_DESC;


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




/*****************************************************************************
 * 
 * Event typedefs and structs
 *
 ****************************************************************************/

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
    UINT8                   GpeBase;        /* Base GPE number */

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



/* Information used during field processing */

typedef struct
{
    UINT8                   SkipField;
    UINT8                   FieldFlag;
    UINT32                  PkgLength;

} FIELD_INFO;





/*****************************************************************************
 * 
 * Parser typedefs and structs
 *
 ****************************************************************************/


#define OP_INFO_TYPE                0x1F
#define OP_INFO_HAS_ARGS            0x20
#define OP_INFO_CHILD_LOCATION      0xC0

/*
 * AML opcode, name, and argument layout
 */
typedef struct acpi_op_info
{
    UINT16                  Opcode;         /* AML opcode */
    UINT8                   Flags;          /* Opcode type, HasArgs flag */
    UINT32                  ParseArgs;      /* Grammar/Parse time arguments */
    UINT32                  RuntimeArgs;    /* Interpret time arguments */

    DEBUG_ONLY_MEMBERS (
    char                    *Name)          /* op name (debug only) */

} ACPI_OP_INFO;


typedef union acpi_op_value
{
    UINT32                  Integer;        /* integer constant */
    UINT32                  Size;           /* bytelist or field size */
    char                    *String;        /* NULL terminated string */
    UINT8                   *Buffer;        /* buffer or string */
    char                    *Name;          /* NULL terminated string */
    struct acpi_generic_op  *Arg;           /* arguments and contained ops */
    NAME_TABLE_ENTRY        *Entry;         /* entry in interpreter namespace tbl */ 

} ACPI_OP_VALUE;


#define ACPI_COMMON_OP \
    UINT8                   DataType;       /* To differentiate various internal objs */\
    UINT8                   Flags;          /* Not used */\
    UINT16                  Opcode;         /* AML opcode */\
    UINT32                  AmlOffset;      /* offset of declaration in AML */\
    struct acpi_generic_op  *Parent;        /* parent op */\
    struct acpi_generic_op  *Next;          /* next op */\
    DEBUG_ONLY_MEMBERS (\
    char                    OpName[16])     /* op name (debug only) */\
                                            /* NON-DEBUG members below: */\
    void                    *NameTableEntry;/* for use by interpreter */\
    ACPI_OP_VALUE           Value;          /* Value or args associated with the opcode */\


/*
 * generic operation (eg. If, While, Store)
 */
typedef struct acpi_generic_op
{
    ACPI_COMMON_OP
} ACPI_GENERIC_OP;


/*
 * operation with a name (eg. Scope, Method, Name, NamedField, ...)
 */
typedef struct acpi_named_op
{
    ACPI_COMMON_OP
    UINT32                  Name;           /* 4-byte name or zero if no name */

} ACPI_NAMED_OP;


/*
 * special operation for methods and regions (parsing must be deferred
 * until a first pass parse is completed)
 */
typedef struct acpi_deferred_op
{
    ACPI_COMMON_OP
    UINT32                  Name;           /* 4-byte name or 0 if none */
    UINT32                  BodyLength;     /* AML body size */
    UINT8                   *Body;          /* AML body */

} ACPI_DEFERRED_OP;


/*
 * special operation for bytelists (ByteList only)
 */
typedef struct acpi_bytelist_op
{
    ACPI_COMMON_OP
    UINT8                   *Data;          /* bytelist data */

} ACPI_BYTELIST_OP;



/*
 * Parse state - one state per parser invocation and each control
 * method.
 */

typedef struct acpi_parse_state
{
    UINT8                   *AmlStart;      /* first AML byte */
    UINT8                   *Aml;           /* next AML byte */
    UINT8                   *AmlEnd;        /* (last + 1) AML byte */
    UINT8                   *PkgEnd;        /* current package end */
    ACPI_GENERIC_OP         *StartOp;       /* root of parse tree */
    struct acpi_parse_scope *Scope;         /* current scope */
    struct acpi_parse_scope *ScopeAvail;    /* unused (extra) scope structs */
    struct acpi_parse_state *Next;

} ACPI_PARSE_STATE;


/*
 * Parse scope - one per ACPI scope
 */

typedef struct acpi_parse_scope
{
    ACPI_GENERIC_OP         *Op;            /* current op being parsed */
    UINT8                   *ArgEnd;        /* current argument end */
    UINT8                   *PkgEnd;        /* current package end */
    struct acpi_parse_scope *Parent;        /* parent scope */
    UINT32                  ArgList;        /* next argument to parse */
    UINT32                  ArgCount;       /* Number of fixed arguments */

} ACPI_PARSE_SCOPE;




/*****************************************************************************
 * 
 * Tree walking typedefs and structs
 *
 ****************************************************************************/


#define CONTROL_NORMAL                        0xC0
#define CONTROL_CONDITIONAL_EXECUTING         0xC1
#define CONTROL_PREDICATE_EXECUTING           0xC2
#define CONTROL_PREDICATE_FALSE               0xC3
#define CONTROL_PREDICATE_TRUE                0xC4 



/*
 * Control state - one per if/else and while constructs.
 * Allows nesting of these constructs 
 */
typedef struct acpi_ctrl_state
{
    UINT8                   Exec;           /* Execution state */
    BOOLEAN                 Predicate;      /* Result of predicate evaluation */
    ACPI_GENERIC_OP         *PredicateOp;   /* Start of if/while predicate */
    struct acpi_ctrl_state  *Next;

} ACPI_CTRL_STATE;



/*
 * Walk state - current state of a parse tree walk.  Used for both a leisurely stroll through
 * the tree (for whatever reason), and for control method execution.
 */

#define NEXT_OP_DOWNWARD    1
#define NEXT_OP_UPWARD      2

typedef struct acpi_walk_state
{
    ACPI_GENERIC_OP         *Origin;                            /* Start of walk */
    ACPI_GENERIC_OP         *PrevOp;                            /* Last op that was processed */
    ACPI_GENERIC_OP         *NextOp;                            /* next op to be processed */
    ACPI_CTRL_STATE         *ControlState;                      /* List of control states (nested IFs) */
	SCOPE_STACK				*ScopeInfo;							/* Stack of nested scopes */
    struct NameTableEntry   Arguments[MTH_NUM_ARGS];            /* Control method arguments */
    struct NameTableEntry   LocalVariables[MTH_NUM_LOCALS];     /* Control method locals */
    union AcpiObjInternal   *Operands[OBJ_NUM_OPERANDS];        /* Operands passed to the interpreter */
    union AcpiObjInternal   *Results[OBJ_NUM_OPERANDS];         /* Accumulated results */
    union AcpiObjInternal   *ReturnDesc;                        /* Return object, if any */
    union AcpiObjInternal   *MethodDesc;                        /* Method descriptor if running a method */
    ACPI_GENERIC_OP         *MethodCallOp;                      /* MethodCall Op if running a method */
    ACPI_TABLE_DESC         *TableDesc;                         /* The ACPI table whose parse tree is being walked */
    struct acpi_walk_state  *Next;                              /* Next WalkState in list */

    BOOLEAN                 LastPredicate;                      /* Result of last predicate */
    UINT8                   NextOpInfo;                         /* Info about NextOp */
    UINT8                   NumOperands;                        /* Stack pointer for Operands[] array */
    UINT8                   NumResults;                         /* Stack pointer for Results[] array */
    UINT8                   CurrentResult;                      /* */

} ACPI_WALK_STATE;


/*
 * Walk list - head of a tree of walk states.  Multiple walk states are created when there
 * are nested control methods executing.
 */
typedef struct acpi_walk_list
{

    ACPI_WALK_STATE         *WalkState;

} ACPI_WALK_LIST;



typedef
ACPI_STATUS (*INTERPRETER_CALLBACK) (
    ACPI_WALK_STATE         *State,
    ACPI_GENERIC_OP         *Op);



/* Info used by PsInitObjects */

typedef struct InitWalkInfo
{
    UINT32                  MethodCount;
    UINT32                  OpRegionCount;
    ACPI_TABLE_DESC         *TableDesc;

} INIT_WALK_INFO;




/*****************************************************************************
 * 
 * Debug
 *
 ****************************************************************************/


/* Entry for a memory allocation (debug only) */

#ifdef ACPI_DEBUG

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

#endif
