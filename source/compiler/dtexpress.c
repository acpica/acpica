/******************************************************************************
 *
 * Module Name: dtexpress.c - Support for integer expressions and labels
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2011, Intel Corp.
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

#define __DTEXPRESS_C__

#include "aslcompiler.h"
#include "dtcompiler.h"

#define _COMPONENT          DT_COMPILER
        ACPI_MODULE_NAME    ("dtexpress")


/* Local prototypes */

static UINT64
DtResolveInteger (
    DT_FIELD                *Field,
    char                    *IntegerString);

static void
DtInsertLabelField (
    DT_FIELD                *Field);

static DT_FIELD *
DtLookupLabel (
    char                    *Name);


/******************************************************************************
 *
 * FUNCTION:    DtResolveIntegerExpression
 *
 * PARAMETERS:  Field               - Field object with Integer expression
 *
 * RETURN:      A 64-bit integer value
 *
 * DESCRIPTION: Resolve an integer expression to a single value. Supports
 *              both integer constants and labels. Supported operators are:
 *              +,-,*,/,%,|,&,^
 *
 *****************************************************************************/

UINT64
DtResolveIntegerExpression (
    DT_FIELD                *Field)
{
    char                    *IntegerString;
    char                    *Operator;
    UINT64                  Value;
    UINT64                  Value2;


    DbgPrint (ASL_DEBUG_OUTPUT, "Full Integer expression: %s\n",
        Field->Value);

    strcpy (MsgBuffer, Field->Value); /* Must take a copy for strtok() */

    /* Obtain and resolve the first operand */

    IntegerString = strtok (MsgBuffer, " ");
    if (!IntegerString)
    {
        DtError (ASL_ERROR, ASL_MSG_INVALID_EXPRESSION, Field, Field->Value);
        return (0);
    }

    Value = DtResolveInteger (Field, IntegerString);
    DbgPrint (ASL_DEBUG_OUTPUT, "Integer resolved to V1: %8.8X%8.8X\n",
        ACPI_FORMAT_UINT64 (Value));

    /*
     * Consume the entire expression string. For the rest of the
     * expression string, values are of the form:
     * <operator> <integer>
     */
    while (1)
    {
        Operator = strtok (NULL, " ");
        if (!Operator)
        {
            /* Normal exit */

            DbgPrint (ASL_DEBUG_OUTPUT, "Expression Resolved to: %8.8X%8.8X\n",
                ACPI_FORMAT_UINT64 (Value));

            return (Value);
        }

        IntegerString = strtok (NULL, " ");
        if (!IntegerString ||
            (strlen (Operator) > 1))
        {
            /* No corresponding operand for operator or invalid operator */

            DtError (ASL_ERROR, ASL_MSG_INVALID_EXPRESSION, Field, Field->Value);
            return (0);
        }

        Value2 = DtResolveInteger (Field, IntegerString);
        DbgPrint (ASL_DEBUG_OUTPUT, "Integer resolved to V2: %8.8X%8.8X\n",
            ACPI_FORMAT_UINT64 (Value2));

        /* Perform the requested operation */

        switch (*Operator)
        {
        case '-':
            Value -= Value2;
            break;

        case '+':
            Value += Value2;
            break;

        case '*':
            Value *= Value2;
            break;

        case '|':
            Value |= Value2;
            break;

        case '&':
            Value &= Value2;
            break;

        case '^':
            Value ^= Value2;
            break;

        case '/':
            if (!Value2)
            {
                DtError (ASL_ERROR, ASL_MSG_DIVIDE_BY_ZERO, Field, Field->Value);
                return (0);
            }
            Value /= Value2;
            break;

        case '%':
            if (!Value2)
            {
                DtError (ASL_ERROR, ASL_MSG_DIVIDE_BY_ZERO, Field, Field->Value);
                return (0);
            }
            Value %= Value2;
            break;

        default:

            /* Unknown operator */

            DtFatal (ASL_MSG_INVALID_EXPRESSION, Field, Field->Value);
            break;
        }
    }

    return (Value);
}


/******************************************************************************
 *
 * FUNCTION:    DtResolveInteger
 *
 * PARAMETERS:  Field               - Field object with string to be resolved
 *              IntegerString       - Integer to be resolved
 *
 * RETURN:      A 64-bit integer value
 *
 * DESCRIPTION: Resolve a single integer string to a value. Supports both
 *              integer constants and labels.
 *
 * NOTE:        References to labels must begin with a dollar sign ($)
 *
 *****************************************************************************/

static UINT64
DtResolveInteger (
    DT_FIELD                *Field,
    char                    *IntegerString)
{
    DT_FIELD                *LabelField;
    UINT64                  Value = 0;
    char                    *Message = NULL;
    ACPI_STATUS             Status;


    DbgPrint (ASL_DEBUG_OUTPUT, "Resolve Integer: %s\n", IntegerString);

    /* Resolve a label reference to an integer (table offset) */

    if (*IntegerString == '$')
    {
        LabelField = DtLookupLabel (IntegerString);
        if (!LabelField)
        {
            DtError (ASL_ERROR, ASL_MSG_UNKNOWN_LABEL, Field, IntegerString);
            return (0);
        }

        /* All we need from the label is the offset in the table */

        Value = LabelField->TableOffset;
        return (Value);
    }

    /* Convert string to an actual integer */

    Status = DtStrtoul64 (IntegerString, &Value);
    if (ACPI_FAILURE (Status))
    {
        if (Status == AE_LIMIT)
        {
            Message = "Constant larger than 64 bits";
        }
        else if (Status == AE_BAD_CHARACTER)
        {
            Message = "Invalid character in constant";
        }

        DtError (ASL_ERROR, ASL_MSG_INVALID_HEX_INTEGER, Field, Message);
    }

    return (Value);
}


/******************************************************************************
 *
 * FUNCTION:    DtDetectAllLabels
 *
 * PARAMETERS:  FieldList           - Field object at start of generic list
 *
 * RETURN:      None
 *
 * DESCRIPTION: Detect all labels in a list of "generic" opcodes (such as
 *              a UEFI table.) and insert them into the global label list.
 *
 *****************************************************************************/

void
DtDetectAllLabels (
    DT_FIELD                *FieldList)
{
    ACPI_DMTABLE_INFO       *Info;
    DT_FIELD                *GenericField;
    UINT32                  TableOffset;


    TableOffset = Gbl_CurrentTableOffset;
    GenericField = FieldList;

    /*
     * Process all "Label:" fields within the parse tree. We need
     * to know the offsets for all labels before we can compile
     * the parse tree in order to handle forward references. Traverse
     * tree and get/set all field lengths of all operators in order to
     * determine the label offsets.
     */
    while (GenericField)
    {
        Info = DtGetGenericTableInfo (GenericField->Name);
        if (Info)
        {
            /* Maintain table offsets */

            GenericField->TableOffset = TableOffset;
            TableOffset += DtGetFieldLength (GenericField, Info);

            /* Insert all labels in the global label list */

            if (Info->Opcode == ACPI_DMT_LABEL)
            {
                DtInsertLabelField (GenericField);
            }
        }

        GenericField = GenericField->Next;
    }
}


/******************************************************************************
 *
 * FUNCTION:    DtInsertLabelField
 *
 * PARAMETERS:  Field               - Field object with Label to be inserted
 *
 * RETURN:      None
 *
 * DESCRIPTION: Insert a label field into the global label list
 *
 *****************************************************************************/

static void
DtInsertLabelField (
    DT_FIELD                *Field)
{

    DbgPrint (ASL_DEBUG_OUTPUT,
        "DtInsertLabelField: Found Label : %s at output table offset %X\n",
        Field->Value, Field->TableOffset);

    Field->NextLabel = Gbl_LabelList;
    Gbl_LabelList = Field;
}


/******************************************************************************
 *
 * FUNCTION:    DtLookupLabel
 *
 * PARAMETERS:  Name                - Label to be resolved
 *
 * RETURN:      Field object associated with the label
 *
 * DESCRIPTION: Lookup a label in the global label list. Used during the
 *              resolution of integer expressions.
 *
 *****************************************************************************/

static DT_FIELD *
DtLookupLabel (
    char                    *Name)
{
    DT_FIELD                *LabelField;


    /* Skip a leading $ */

    if (*Name == '$')
    {
        Name++;
    }

    /* Search global list */

    LabelField = Gbl_LabelList;
    while (LabelField)
    {
        if (!ACPI_STRCMP (Name, LabelField->Value))
        {
            return (LabelField);
        }
        LabelField = LabelField->NextLabel;
    }

    return (NULL);
}
