/*******************************************************************************
 *
 * Module Name: dbdisasm - AML disassembler display routines
 *              $Revision: 1.69 $
 *
 ******************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2002, Intel Corp.
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


#include "acpi.h"
#include "acparser.h"
#include "amlcode.h"
#include "acnamesp.h"
#include "acdisasm.h"
#include "acdebug.h"


#ifdef ACPI_DISASSEMBLER

#define _COMPONENT          ACPI_DEBUGGER
        ACPI_MODULE_NAME    ("dbdisasm")


#define BLOCK_NONE          0
#define BLOCK_PAREN         1
#define BLOCK_BRACE         2
#define BLOCK_COMMA_LIST    4


NATIVE_CHAR                 *AcpiGbl_DbDisasmIndent = "....";



/*******************************************************************************
 *
 * FUNCTION:    AcpiDmDoByteList
 *
 * PARAMETERS:  Resource            - Pointer to the resource descriptor
 *              Length              - Length of the descriptor in bytes
 *              Level               - Current source code indentation level
 *
 * RETURN:      Status
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

void
AcpiDmDoByteList (
    ACPI_OP_WALK_INFO       *Info,    
    ACPI_PARSE_OBJECT       *Op)
{
    UINT8                   *ByteData;
    UINT32                  ByteCount;
    UINT32                  WordCount;
    ACPI_STATUS             Status;



    ByteData = Op->Named.Data;
    ByteCount = Op->Common.Value.Integer32;
    WordCount = ACPI_DIV_2 (ByteCount);


    switch (Op->Common.Parent->Common.DisasmOpcode)
    {
    case ACPI_DASM_RESOURCE:

        Status = AcpiDmDoResourceDescriptor (Info, ByteData, ByteCount);
        break;

    case ACPI_DASM_STRING:

        AcpiDmIndent (Info->Level);
        AcpiDmDoString ((char *) ByteData);
        break;
  
    case ACPI_DASM_UNICODE:

        AcpiDmDoUnicode (Op);
        break;

    case ACPI_DASM_BUFFER:
    default:

        /*
         * Not a resource, string, or unicode string.
         * Just dump the buffer
         */  
        AcpiDmDisasmByteList (Info->Level, ByteData, ByteCount);
        break;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  Op              - Object to be examined
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Decode control method flags
 *
 ******************************************************************************/

BOOLEAN
AcpiDmIsUnicodeBuffer (
    ACPI_PARSE_OBJECT       *Op)
{
    UINT8                   *ByteData;
    UINT32                  ByteCount;
    UINT32                  WordCount;
    ACPI_PARSE_OBJECT       *SizeOp;
    ACPI_PARSE_OBJECT       *NextOp;
    UINT32                  i;


    SizeOp = Op->Common.Value.Arg;

    NextOp = SizeOp->Common.Next;
    if (!NextOp)
    {
        return (FALSE);
    }

    ByteData = NextOp->Named.Data;
    ByteCount = NextOp->Common.Value.Integer32;
    WordCount = ACPI_DIV_2 (ByteCount);

    /* Check for a unicode string */

    if ((!ByteCount) ||
         (ByteCount & 1) ||
        ((UINT16 *) ByteData)[WordCount - 1] != 0)
    {
        return (FALSE);
    }

    for (i = 0; i < (ByteCount - 2); i += 2)
    {
        if ((!isprint (ByteData[i])) ||
            (ByteData[i + 1] != 0))
        {
            return (FALSE);
        }
    }

    SizeOp->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE;
    return (TRUE);
}


/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  Op              - Object to be examined
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Decode control method flags
 *
 ******************************************************************************/

BOOLEAN
AcpiDmIsStringBuffer (
    ACPI_PARSE_OBJECT       *Op)
{
    UINT8                   *ByteData;
    UINT32                  ByteCount;
    ACPI_PARSE_OBJECT       *SizeOp;
    ACPI_PARSE_OBJECT       *NextOp;
    UINT32                  i;


    SizeOp = Op->Common.Value.Arg;

    NextOp = SizeOp->Common.Next;
    if (!NextOp)
    {
        return (FALSE);
    }

    ByteData = NextOp->Named.Data;
    ByteCount = NextOp->Common.Value.Integer32;

    /* Check buffer for an ASCII string */

    if (ByteData[ByteCount-1] != 0)
    {
        return (FALSE);
    }

    for (i = 0; i < (ByteCount - 1); i++)
    {
        /* TBD: allow some escapes (non-ascii chars).
         * they will be handled in the string output routine 
         */

        if (!isprint (ByteData[i]))
        {
            return (FALSE);
        }
    }

    SizeOp->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE;
    return (TRUE);
}


/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  Op              - Object to be examined
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Decode control method flags
 *
 ******************************************************************************/

void
AcpiDmDoString (
    char                    *String)
{
    UINT32                  i;


    if (!String)
    {
        AcpiOsPrintf ("<\"NULL STRING PTR\">");
        return;
    }

    AcpiOsPrintf ("\"");
    for (i = 0; String[i]; i++)
    {
        switch (String[i])
        {
        case '"':
            AcpiOsPrintf ("\\");
            break;

        /* TBD: Handle escapes here */
        default:
            break;
        }

        AcpiOsPrintf ("%c", String[i]);
    }
    AcpiOsPrintf ("\"");
}


/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  Op              - Object to be examined
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Decode control method flags
 *
 ******************************************************************************/

void
AcpiDmDoUnicode (
    ACPI_PARSE_OBJECT       *Op)
{
    UINT16                  *WordData;
    UINT32                  WordCount;
    UINT32                  i;


    WordData = (UINT16 *) Op->Named.Data;
    WordCount = ACPI_DIV_2 (Op->Common.Value.Integer32);


    AcpiOsPrintf ("\"");
    for (i = 0; i < (WordCount - 1); i++)
    {
        AcpiOsPrintf ("%c", WordData[i]);
    }

    AcpiOsPrintf ("\")");
}


/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  Op              - Object to be examined
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Decode control method flags
 *
 ******************************************************************************/

void
AcpiDmDoEisaId (
    UINT32                  EncodedId)
{
    UINT32                  BigEndianId;


    /* Swap from little-endian to big-endian to simplify conversion */

    BigEndianId = AcpiUtDwordByteSwap (EncodedId);


    /* Split to form "AAANNNN" string */

    AcpiOsPrintf ("EisaId (\"%c%c%c%4.4X\")",

        /* Alpha characters (AAA), 5 bits each */

        ((BigEndianId >> 26) & 0x1F) + 0x40,
        ((BigEndianId >> 21) & 0x1F) + 0x40,
        ((BigEndianId >> 16) & 0x1F) + 0x40,

        /* Numeric part (NNNN) is simply the lower 16 bits */

        (BigEndianId & 0xFFFF));
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmDoMethodFlags
 *
 * PARAMETERS:  Op              - Object to be examined
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Decode control method flags
 *
 ******************************************************************************/

ACPI_PARSE_OBJECT *
AcpiDmDoMethodFlags (
    ACPI_PARSE_OBJECT       *Op)
{
    UINT32                  Flags;
    UINT32                  Args;


    /* The next Op contains the flags */

    Op = AcpiPsGetDepthNext (NULL, Op);
    Flags = Op->Common.Value.Integer8;
    Args = Flags & 0x7;

    /* Mark the Op as completed */

    Op->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE;

    /* 1) Method argument count */

    AcpiOsPrintf (", %d, ", Args);

    /* 2) Serialize rule */

    if (!(Flags & 0x4))
    {
        AcpiOsPrintf ("Not");
    }

    AcpiOsPrintf ("Serialized");

    /* 3) SyncLevel */

    if (Flags & 0xF0)
    {
        AcpiOsPrintf (", %d", Flags >> 4);
    }

    return (Op);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmDoFieldFlags
 *
 * PARAMETERS:  Op              - Object to be examined
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Decode control method flags
 *
 ******************************************************************************/

ACPI_PARSE_OBJECT *
AcpiDmDoFieldFlags (
    ACPI_PARSE_OBJECT       *Op)
{
    UINT32                  Flags;


    /* The next Op contains the flags */

    Op = AcpiPsGetDepthNext (NULL, Op);
    Flags = Op->Common.Value.Integer8;

    /* Mark the Op as completed */

    Op->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE;

    AcpiOsPrintf ("%s, ", AcpiGbl_AccessTypes [Flags & 0x0F]);
    AcpiOsPrintf ("%s, ", AcpiGbl_LockRule [(Flags & 0x10) >> 5]);
    AcpiOsPrintf ("%s)",  AcpiGbl_UpdateRules [(Flags & 0x60) >> 6]);


    return (Op);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmDoRegionFlags
 *
 * PARAMETERS:  Op              - Object to be examined
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Decode region flags
 *
 ******************************************************************************/

ACPI_PARSE_OBJECT *
AcpiDmDoRegionFlags (
    ACPI_PARSE_OBJECT       *Op)
{
    UINT32                  SpaceId;



    /* The next Op contains the SpaceId */

    Op = AcpiPsGetDepthNext (NULL, Op);
    SpaceId = Op->Common.Value.Integer8;

    /* Mark the Op as completed */

    Op->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE;

    if (SpaceId > ACPI_NUM_PREDEFINED_REGIONS)
    {
        AcpiOsPrintf (", 0x%.2X, ", SpaceId);
    }
    else
    {
        AcpiOsPrintf (", %s, ", AcpiGbl_RegionTypes [SpaceId]);
    }


    return (Op);
}



/*******************************************************************************
 *
 * FUNCTION:    AcpiDmDoMethodOp
 *
 * PARAMETERS:  Op              - Object to be examined
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Decode region flags
 *
 ******************************************************************************/

ACPI_PARSE_OBJECT *
AcpiDmDoMethodOp (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *NextOp;


    NextOp = AcpiPsGetDepthNext (NULL, Op);
    NextOp = NextOp->Common.Next;

    NextOp->Common.AmlOpcode = AML_INT_STATICSTRING_OP;
    NextOp->Common.Value.String = (char *) AcpiGbl_MatchOps[NextOp->Common.Value.Integer32];

    NextOp = NextOp->Common.Next;
    NextOp = NextOp->Common.Next;
    NextOp->Common.AmlOpcode = AML_INT_STATICSTRING_OP;
    NextOp->Common.Value.String = (char *) AcpiGbl_MatchOps[NextOp->Common.Value.Integer32];

    return (Op);
}



/*******************************************************************************
 *
 * FUNCTION:    AcpiDmCommaIfListMember 
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: Insert a comma if this Op is a member of an argument list.
 *
 ******************************************************************************/

BOOLEAN
AcpiDmCommaIfListMember (
    ACPI_PARSE_OBJECT       *Op)
{

    if (!Op->Common.Next)
    {
        return FALSE;
    }

    if (AcpiDmListType (Op->Common.Parent) & BLOCK_COMMA_LIST)
    {
        /* Check for a NULL target operand */

        if ((Op->Common.Next->Common.AmlOpcode == AML_INT_NAMEPATH_OP) &&
            (!Op->Common.Next->Common.Value.String))
        {
            return FALSE;
        }

        if ((Op->Common.DisasmFlags & ACPI_PARSEOP_PARAMLIST) &&
            (!(Op->Common.Next->Common.DisasmFlags & ACPI_PARSEOP_PARAMLIST)))
        {
            return FALSE;
        }

        AcpiOsPrintf (", ");
        return (TRUE);
    }

    else if ((Op->Common.DisasmFlags & ACPI_PARSEOP_PARAMLIST) &&
        (Op->Common.Next->Common.DisasmFlags & ACPI_PARSEOP_PARAMLIST))
    {
        AcpiOsPrintf (", ");
        return (TRUE);
    }

    return (FALSE);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmCommaIfFieldMember 
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: Insert a comma if this Op is a member of an argument list.
 *
 ******************************************************************************/

void 
AcpiDmCommaIfFieldMember (
    ACPI_PARSE_OBJECT       *Op)
{
    if (Op->Common.Next)
    {
        AcpiOsPrintf (", ");
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmDisplayOpcode
 *
 * PARAMETERS:  Op                  - Op that is to be printed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Store printed op in a Buffer and return its length
 *              (or -1 if out of space)
 *
 * NOTE: Terse mode prints out ASL-like code.  Verbose mode adds more info.
 *
 ******************************************************************************/

ACPI_PARSE_OBJECT *
AcpiDmDisplayOpcode (
    ACPI_WALK_STATE         *WalkState,
    ACPI_OP_WALK_INFO       *Info,    
    ACPI_PARSE_OBJECT       *Op)
{
    const ACPI_OPCODE_INFO  *OpInfo = NULL;
    UINT32                  Offset;
    UINT32                  Length;


    if (!Op)
    {
        AcpiOsPrintf ("<NULL OP PTR>");
        return (Op);
    }

    /* op and arguments */

    switch (Op->Common.AmlOpcode)
    {
    case AML_ZERO_OP:

        AcpiOsPrintf ("Zero");
        break;


    case AML_ONE_OP:

        AcpiOsPrintf ("One");
        break;


    case AML_ONES_OP:

        AcpiOsPrintf ("Ones");
        break;


    case AML_REVISION_OP:

        AcpiOsPrintf ("Revision");
        break;


    case AML_BYTE_OP:

        AcpiOsPrintf ("0x%.2X", (UINT32) Op->Common.Value.Integer8);
        break;


    case AML_WORD_OP:

        AcpiOsPrintf ("0x%.2X", (UINT32) Op->Common.Value.Integer16);
        break;


    case AML_DWORD_OP:

        if (Op->Common.DisasmFlags & ACPI_PARSEOP_SPECIAL)
        {
            AcpiDmDoEisaId (Op->Common.Value.Integer32);
        }
        else
        {
            if ((Op->Common.Value.Integer32 == 0xFFFFFFFF) &&
                (AcpiGbl_DSDT->Revision < 2))
            {
                AcpiOsPrintf ("Ones");
            }
            else
            {
                AcpiOsPrintf ("0x%.2X", Op->Common.Value.Integer32);
            }
        }
        break;


    case AML_QWORD_OP:

        if ((Op->Common.Value.Integer == 0xFFFFFFFFFFFFFFFF) &&
            (AcpiGbl_DSDT->Revision >= 2))
        {
            AcpiOsPrintf ("Ones");
        }
        else
        {
            AcpiOsPrintf ("0x%X%8.8X", Op->Common.Value.Integer64.Hi,
                                       Op->Common.Value.Integer64.Lo);
        }
        break;


    case AML_STRING_OP:

        AcpiDmDoString (Op->Common.Value.String);
        break;


    case AML_BUFFER_OP:

        /* 
         * Determine the type of buffer.  We can have one of the following:
         *
         * 1) ResourceTemplate containing Resource Descriptors.
         * 2) Unicode String buffer
         * 3) ASCII String buffer
         * 4) Raw data buffer (if none of the above)
         *
         * Since there are no special AML opcodes to differentiate these
         * types of buffers, we have to closely look at the data in the
         * buffer to determine the type.
         */

        if (AcpiDmIsResourceDescriptor (Op))
        {
            Op->Common.DisasmOpcode = ACPI_DASM_RESOURCE;
            AcpiOsPrintf ("ResourceTemplate");
        }
        else if (AcpiDmIsUnicodeBuffer (Op))
        {
            Op->Common.DisasmOpcode = ACPI_DASM_UNICODE;
            AcpiOsPrintf ("Unicode (");
        }
        else if (AcpiDmIsStringBuffer (Op))
        {
            Op->Common.DisasmOpcode = ACPI_DASM_STRING;
            AcpiOsPrintf ("Buffer");
        }
        else
        {
            Op->Common.DisasmOpcode = ACPI_DASM_BUFFER;
            AcpiOsPrintf ("Buffer");
        }
        break;


    case AML_INT_STATICSTRING_OP:

        if (Op->Common.Value.String)
        {
            AcpiOsPrintf ("%s", Op->Common.Value.String);
        }
        else
        {
            AcpiOsPrintf ("\"<NULL STATIC STRING PTR>\"");
        }
        break;


    case AML_INT_NAMEPATH_OP:

        AcpiDmDisplayNamestring (Op->Common.Value.Name);
        break;


    case AML_INT_NAMEDFIELD_OP:

        Length = AcpiDmDumpName ((char *) &Op->Named.Name);
        AcpiOsPrintf (",%*.s  %d", 5 - Length, " ", Op->Common.Value.Integer32);
        AcpiDmCommaIfFieldMember (Op);
        AcpiOsPrintf ("\n");

        Info->BitOffset += Op->Common.Value.Integer32;
        break;


    case AML_INT_RESERVEDFIELD_OP:

        /* Offset() -- Must account for previous offsets */

        Offset = Op->Common.Value.Integer32;
        Info->BitOffset += Offset;

        if (Info->BitOffset % 8 == 0)
        {
            AcpiOsPrintf ("Offset (0x%.2X)", ACPI_DIV_8 (Info->BitOffset));
        }
        else
        {
            AcpiOsPrintf ("    ,   %d", Offset);
        }

        AcpiDmCommaIfFieldMember (Op);
        AcpiOsPrintf ("\n");
        break;


    case AML_INT_ACCESSFIELD_OP:

        AcpiOsPrintf ("AccessAs (%s, 0x%.2X)", 
            AcpiGbl_AccessTypes [Op->Common.Value.Integer32 >> 8], 
            Op->Common.Value.Integer32 & 0x0F);

        AcpiDmCommaIfFieldMember (Op);
        AcpiOsPrintf ("\n");
        break;


    case AML_INT_BYTELIST_OP:

        AcpiDmDoByteList (Info, Op);
        break;


    case AML_INT_METHODCALL_OP:

        OpInfo = AcpiPsGetOpcodeInfo (Op->Common.AmlOpcode);
        Op = AcpiPsGetDepthNext (NULL, Op);
        Op->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE;

        AcpiDmDisplayNamestring (Op->Common.Value.Name);
        break;


    default:

        /* Just get the opcode name and print it */

        OpInfo = AcpiPsGetOpcodeInfo (Op->Common.AmlOpcode);
        AcpiOsPrintf ("%s", OpInfo->Name);


#ifndef PARSER_ONLY
        if ((Op->Common.AmlOpcode == AML_INT_RETURN_VALUE_OP) &&
            (WalkState) &&
            (WalkState->Results) &&
            (WalkState->Results->Results.NumResults))
        {
            AcpiDbDecodeInternalObject (
                WalkState->Results->Results.ObjDesc [WalkState->Results->Results.NumResults-1]);
        }
#endif
        break;
    }

    return (Op);
}

#endif  /* ACPI_DISASSEMBLER */
