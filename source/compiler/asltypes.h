
/******************************************************************************
 *
 * Module Name: asltypes.h - compiler data types and struct definitions
 *              $Revision: 1.8 $
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999, 2000, Intel Corp.
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


#ifndef __ASLTYPES_H
#define __ASLTYPES_H


/*******************************************************************************
 *
 * Structure definitions
 *
 ******************************************************************************/


/* Value union for the parse node */

typedef union asl_node_value
{
    UINT64                      Integer;        /* Generic integer is largest integer */
    UINT64                      Integer64;
    UINT32                      Integer32;
    UINT16                      Integer16;
    UINT8                       Integer8;
    void                        *Pointer;
    char                        *String;

} ASL_NODE_VALUE;


/* The parse node is the fundamental element of the parse tree */

typedef struct asl_parse_node
{
    struct asl_parse_node       *Parent;
    struct asl_parse_node       *Peer;
    struct asl_parse_node       *Child;
    struct asl_parse_node       *ParentMethod;
    ACPI_NAMESPACE_NODE         *NsNode;
    union asl_node_value        Value;
    char                        *Filename;
    char                        *ExternalName;
    char                        *Namepath;
    UINT32                      LineNumber;
    UINT32                      LogicalLineNumber;
    UINT32                      EndLine;
    UINT32                      EndLogicalLine;
    UINT16                      AmlOpcode;
    UINT16                      ParseOpcode;
    UINT32                      AcpiBtype;
    UINT32                      AmlLength;
    UINT32                      AmlSubtreeLength;
    UINT8                       AmlOpcodeLength;
    UINT8                       AmlPkgLenBytes;
    UINT16                      Flags;
    UINT8                       Extra;
    char                        ParseOpName[12];
    char                        AmlOpName[12];

} ASL_PARSE_NODE;

/* Node flags for the ASL_PARSE_NODE */

#define NODE_VISITED                0x0001
#define NODE_AML_PACKAGE            0x0002
#define NODE_IS_TARGET              0x0004
#define NODE_IS_RESOURCE_DESC       0x0008
#define NODE_IS_RESOURCE_FIELD      0x0010
#define NODE_HAS_NO_EXIT            0x0020
#define NODE_IF_HAS_NO_EXIT         0x0040
#define NODE_NAME_INTERNALIZED      0x0080
#define NODE_METHOD_NO_RETVAL       0x0100
#define NODE_METHOD_SOME_NO_RETVAL  0x0200
#define NODE_RESULT_NOT_USED        0x0400
#define NODE_METHOD_TYPED           0x0800

/* Keeps information about individual control methods */

typedef struct asl_method_info
{
    UINT8                   NumArguments;
    UINT8                   LocalInitialized[8];
    UINT32                  NumReturnNoValue;
    UINT32                  NumReturnWithValue;
    ASL_PARSE_NODE          *Node;
    struct asl_method_info  *Next;
    UINT8                   HasBeenTyped;

} ASL_METHOD_INFO;


/* Parse tree walk info for control method analysis */

typedef struct asl_analysis_walk_info
{
    ASL_METHOD_INFO         *MethodStack;

} ASL_ANALYSIS_WALK_INFO;


/* An entry in the ParseOpcode to AmlOpcode mapping table */

typedef struct asl_mapping_entry
{
    UINT32                      Value;
    UINT32                      AcpiBtype;   /* Object type or return type */
    UINT16                      AmlOpcode;
    UINT8                       Flags;

} ASL_MAPPING_ENTRY;


/* An entry in the Reserved Name information table */

#define ASL_RSVD_RETURN_VALUE   0x01

typedef struct
{
    char                        *Name;
    UINT8                       NumArguments;
    UINT8                       Flags;

} ASL_RESERVED_INFO;


/* Parse tree walk info structure */

typedef struct asl_walk_info
{
    ASL_PARSE_NODE              **NodePtr;
    UINT32                      *LevelPtr;

} ASL_WALK_INFO;


/* An entry in the exception list, one for each error/warning */

typedef struct asl_error_msg
{
    UINT32                      LineNumber;
    UINT32                      LogicalLineNumber;
    UINT32                      Column;
    char                        *Message;
    struct asl_error_msg        *Next;
    char                        *Filename;
    UINT8                       MessageId;
    UINT8                       Level;

} ASL_ERROR_MSG;


/* An entry in the listing file stack (for include files) */

typedef struct asl_listing_node
{
    char                        *Filename;
    UINT32                      LineNumber;
    struct asl_listing_node     *Next;

} ASL_LISTING_NODE;


/* Callback interface for a parse tree walk */

typedef
void (*ASL_WALK_CALLBACK) (
    ASL_PARSE_NODE              *Node,
    UINT32                      Level,
    void                        *Context);


#define ASL_ERROR               0
#define ASL_WARNING             1


typedef enum
{
    ASL_MSG_NULL = 0,
    ASL_MSG_MEMORY_ALLOCATION,
    ASL_MSG_INPUT_FILE_OPEN,
    ASL_MSG_OUTPUT_FILENAME,
    ASL_MSG_OUTPUT_FILE_OPEN,
    ASL_MSG_LISTING_FILENAME,
    ASL_MSG_LISTING_FILE_OPEN,
    ASL_MSG_DEBUG_FILENAME,
    ASL_MSG_DEBUG_FILE_OPEN,
    ASL_MSG_INCLUDE_FILE_OPEN,
    ASL_MSG_ENCODING_LENGTH,
    ASL_MSG_INVALID_PRIORITY,
    ASL_MSG_INVALID_PERFORMANCE,
    ASL_MSG_LOCAL_INIT,
    ASL_MSG_ARG_INVALID,
    ASL_MSG_UNSUPPORTED,
    ASL_MSG_RESERVED_WORD,
    ASL_MSG_BUFFER_LENGTH,
    ASL_MSG_PACKAGE_LENGTH,
    ASL_MSG_RETURN_TYPES,
    ASL_MSG_NOT_FOUND,
    ASL_MSG_NESTED_COMMENT,
    ASL_MSG_RESERVED_ARG_COUNT_HI,
    ASL_MSG_RESERVED_ARG_COUNT_LO,
    ASL_MSG_RESERVED_RETURN_VALUE,
    ASL_MSG_ARG_COUNT_HI,
    ASL_MSG_ARG_COUNT_LO,
    ASL_MSG_NO_RETVAL,
    ASL_MSG_SOME_NO_RETVAL,
    ASL_MSG_INTERNAL,
    ASL_MSG_BACKWARDS_OFFSET,
    ASL_MSG_UNKNOWN_RESERVED_NAME,
    ASL_MSG_NAME_EXISTS,
    ASL_MSG_INVALID_TYPE,
    ASL_MSG_MULTIPLE_TYPES,

} ASL_MESSAGE_IDS;


#endif  /* __ASLTYPES_H */
