
/******************************************************************************
 *
 * Module Name: aslanalyze.c - check for semantic errors
 *              $Revision: 1.46 $
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999, 2000, 2001, Intel Corp.
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


#include "aslcompiler.h"
#include "aslcompiler.y.h"
#include "acparser.h"
#include "amlcode.h"

#include <ctype.h>

#define _COMPONENT          ACPI_COMPILER
        MODULE_NAME         ("aslanalyze")


/*******************************************************************************
 *
 * FUNCTION:    AnMapArgTypeToBtype
 *
 * PARAMETERS:  ArgType      - The ARGI required type(s) for this argument,
 *                               from the opcode info table
 *
 * RETURN:      The corresponding Bit-encoded types
 *
 * DESCRIPTION: Convert an encoded ARGI required argument type code into a
 *              bitfield type code.  Implements the implicit source conversion
 *              rules.
 *
 ******************************************************************************/

UINT32
AnMapArgTypeToBtype (
    UINT32                  ArgType)
{

    switch (ArgType)
    {
    case ARGI_ANYTYPE:
        return (ACPI_BTYPE_OBJECTS_AND_REFS);

    case ARGI_TARGETREF:
    case ARGI_FIXED_TARGET:
    case ARGI_SIMPLE_TARGET:
        return (ACPI_BTYPE_OBJECTS_AND_REFS);

    case ARGI_REFERENCE:
        return (ACPI_BTYPE_REFERENCE);

    case ARGI_INTEGER_REF:
        return (ACPI_BTYPE_INTEGER);

    case ARGI_OBJECT_REF:
        return (ACPI_BTYPE_ALL_OBJECTS);

    case ARGI_DEVICE_REF:
        return (ACPI_BTYPE_DEVICE_OBJECTS);

    case ARGI_IF:
        return (ACPI_BTYPE_ANY);

    /*
     * Source conversion rules:
     * Integer, String, and Buffer are interchangable
     */
    case ARGI_INTEGER:
        return (ACPI_BTYPE_INTEGER | ACPI_BTYPE_STRING | ACPI_BTYPE_BUFFER);

    case ARGI_STRING:
        return (ACPI_BTYPE_INTEGER | ACPI_BTYPE_STRING | ACPI_BTYPE_BUFFER);

    case ARGI_BUFFER:
        return (ACPI_BTYPE_INTEGER | ACPI_BTYPE_STRING | ACPI_BTYPE_BUFFER);

    case ARGI_PACKAGE:
        return (ACPI_BTYPE_PACKAGE);

    case ARGI_COMPUTEDATA:
        return (ACPI_BTYPE_COMPUTE_DATA);

    case ARGI_DATAOBJECT:     /* Buffer, string, package or reference to a Node - Used only by SizeOf operator*/
        return (ACPI_BTYPE_STRING | ACPI_BTYPE_BUFFER | ACPI_BTYPE_PACKAGE | ACPI_BTYPE_REFERENCE);

    case ARGI_COMPLEXOBJ:    /* Buffer, String, or package */
        return (ACPI_BTYPE_STRING | ACPI_BTYPE_BUFFER | ACPI_BTYPE_PACKAGE);

    case ARGI_MUTEX:
        return (ACPI_BTYPE_MUTEX);

    case ARGI_EVENT:
        return (ACPI_BTYPE_EVENT);

    case ARGI_REGION:
        return (ACPI_BTYPE_REGION);

    case ARGI_DDBHANDLE:
        return (ACPI_BTYPE_DDB_HANDLE);
    }

    return (ACPI_BTYPE_OBJECTS_AND_REFS);
}


/*******************************************************************************
 *
 * FUNCTION:    AnMapEtypeToBtype
 *
 * PARAMETERS:  Etype           - Encoded ACPI Type
 *
 * RETURN:      Btype
 *
 * DESCRIPTION: Convert an encoded ACPI type to a bitfield type applying the
 *              operand conversion rules.  In other words, returns the type(s)
 *              this Etype is implicitly converted to during interpretation.
 *
 ******************************************************************************/

UINT32
AnMapEtypeToBtype (
    UINT32              Etype)
{


    if (Etype == ACPI_TYPE_ANY)
    {
        return ACPI_BTYPE_OBJECTS_AND_REFS;
    }

    /* Try the standard ACPI data types */

    if (Etype <= ACPI_TYPE_MAX)
    {
        /*
         * This switch statement implements the allowed operand conversion
         * rules as per the "ASL Data Types" section of the ACPI
         * specification.
         */
        switch (Etype)
        {
        case ACPI_TYPE_INTEGER:
            return (ACPI_BTYPE_COMPUTE_DATA | ACPI_BTYPE_DDB_HANDLE);

        case ACPI_TYPE_STRING:
        case ACPI_TYPE_BUFFER:
            return (ACPI_BTYPE_COMPUTE_DATA);

        case ACPI_TYPE_PACKAGE:
            return (ACPI_BTYPE_PACKAGE);

        case ACPI_TYPE_FIELD_UNIT:
            return (ACPI_BTYPE_COMPUTE_DATA | ACPI_BTYPE_FIELD_UNIT);

        case ACPI_TYPE_BUFFER_FIELD:
            return (ACPI_BTYPE_COMPUTE_DATA | ACPI_BTYPE_BUFFER_FIELD);

        case ACPI_TYPE_DDB_HANDLE:
            return (ACPI_BTYPE_INTEGER | ACPI_BTYPE_DDB_HANDLE);

        case ACPI_BTYPE_DEBUG_OBJECT:
            return (0);     /* Cannot be used as a source operand */

        default:
            return (1 << (Etype - 1));
        }
    }

    /* Try the internal data types */

    switch (Etype)
    {

    case INTERNAL_TYPE_REGION_FIELD:
    case INTERNAL_TYPE_BANK_FIELD:
    case INTERNAL_TYPE_INDEX_FIELD:

        /* Named fields can be either Integer/Buffer/String */

        return (ACPI_BTYPE_COMPUTE_DATA);

    case INTERNAL_TYPE_ALIAS:
        return (ACPI_BTYPE_INTEGER);


    case INTERNAL_TYPE_RESOURCE:
    case INTERNAL_TYPE_RESOURCE_FIELD:
        return (ACPI_BTYPE_REFERENCE);

    default:
        printf ("Unhandled encoded type: %X\n", Etype);
        return (0);
    }


    return 0;

}


/*******************************************************************************
 *
 * FUNCTION:    AnMapBtypeToEtype
 *
 * PARAMETERS:  Btype               - Bitfield of ACPI types
 *
 * RETURN:      none
 *
 * DESCRIPTION: Convert a bitfield type to an encoded type
 *
 ******************************************************************************/

UINT32
AnMapBtypeToEtype (
    UINT32              Btype)
{
    UINT32              i;
    UINT32              Etype;


    if (Btype == 0)
    {
        return 0;
    }

    Etype = 1;
    for (i = 1; i < Btype; i *= 2)
    {
        Etype++;
    }

    return (Etype);
}


/*******************************************************************************
 *
 * FUNCTION:    AnFormatBtype
 *
 * PARAMETERS:  Btype               - Bitfield of ACPI types
 *              Buffer              - Where to put the ascii string
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Convert a Btype to a string of ACPI types
 *
 ******************************************************************************/

void
AnFormatBtype (
    char                *Buffer,
    UINT32              Btype)
{
    UINT32              Type;
    BOOLEAN             First = TRUE;


    *Buffer = 0;

    if (Btype == 0)
    {
        strcat (Buffer, "NoReturnValue");
        return;
    }

    for (Type = 1; Type < ACPI_TYPE_MAX; Type++)
    {
        if (Btype & 0x00000001)
        {
            if (!First)
            {
                strcat (Buffer, "|");
            }
            First = FALSE;

            strcat (Buffer, AcpiUtGetTypeName (Type));
        }

        Btype >>= 1;
    }


    if (Btype & 0x00000001)
    {
        if (!First)
        {
            strcat (Buffer, "|");
        }
        First = FALSE;
        strcat (Buffer, "Reference");
    }

    Btype >>= 1;
    if (Btype & 0x00000001)
    {
        if (!First)
        {
            strcat (Buffer, "|");
        }
        First = FALSE;
        strcat (Buffer, "Resource");
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AnGetBtype
 *
 * PARAMETERS:
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Get the (bitfield) ACPI type associated with the parse node.
 *              Handles the case where the node is a name or method call and
 *              the actual type must be obtained from the namespace node.
 *
 ******************************************************************************/

UINT32
AnGetBtype (
    ASL_PARSE_NODE          *PsNode)
{
    ACPI_NAMESPACE_NODE     *NsNode;
    ASL_PARSE_NODE          *ReferencedNode;
    UINT32                  ThisNodeBtype = 0;


    if ((PsNode->ParseOpcode == NAMESEG)     ||
        (PsNode->ParseOpcode == NAMESTRING)  ||
        (PsNode->ParseOpcode == METHODCALL))
    {
        NsNode = PsNode->NsNode;
        if (!NsNode)
        {
            DbgPrint (ASL_DEBUG_OUTPUT,
                "Null attached Nsnode: [%s] at line %d\n",
                PsNode->ParseOpName, PsNode->LineNumber);
            return ACPI_UINT32_MAX;
        }

        ThisNodeBtype = AnMapEtypeToBtype (NsNode->Type);

        /*
         * Since it was a named reference, enable the
         * reference bit also
         */
        ThisNodeBtype |= ACPI_BTYPE_REFERENCE;

        if (PsNode->ParseOpcode == METHODCALL)
        {
            ReferencedNode = (ASL_PARSE_NODE *) NsNode->Object;
            if (!ReferencedNode)
            {
               printf ("No back ptr to PsNode: type %X\n", NsNode->Type);
               return ACPI_UINT32_MAX;
            }

            if (ReferencedNode->Flags & NODE_METHOD_TYPED)
            {
                ThisNodeBtype = ReferencedNode->AcpiBtype;
            }

            else
            {
                return (ACPI_UINT32_MAX -1);
            }
        }
    }

    else
    {
        ThisNodeBtype = PsNode->AcpiBtype;
    }


    return (ThisNodeBtype);
}


/*******************************************************************************
 *
 * FUNCTION:    AnCheckForReservedMethod
 *
 * PARAMETERS:  Node            - A parse node of type "METHOD".
 *              MethodInfo      - Saved info about this method
 *
 * RETURN:      None
 *
 * DESCRIPTION: If method is a reserved name, check that the number of arguments
 *              and the return type (returns a value or not) is correct.
 *
 ******************************************************************************/

void
AnCheckForReservedMethod (
    ASL_PARSE_NODE          *Node,
    ASL_METHOD_INFO         *MethodInfo)
{
    UINT32                  i;


    /* All reserved names are prefixed with a single underscore */

    if (Node->ExternalName[0] != '_')
    {
        return;
    }


    /* Check for a standard reserved method name */

    for (i = 0; ReservedMethods[i].Name; i++)
    {
        if (!STRCMP (Node->ExternalName, ReservedMethods[i].Name))
        {
            Gbl_ReservedMethods++;

            /* Matched a reserved method name */

            if (MethodInfo->NumArguments != ReservedMethods[i].NumArguments)
            {
                sprintf (MsgBuffer, " %s requires %d",
                            ReservedMethods[i].Name,
                            ReservedMethods[i].NumArguments);

                if (MethodInfo->NumArguments > ReservedMethods[i].NumArguments)
                {
                    AslError (ASL_WARNING, ASL_MSG_RESERVED_ARG_COUNT_HI, Node, MsgBuffer);
                }
                else
                {
                    AslError (ASL_WARNING, ASL_MSG_RESERVED_ARG_COUNT_LO, Node, MsgBuffer);
                }
            }

            if (MethodInfo->NumReturnNoValue &&
                ReservedMethods[i].Flags & ASL_RSVD_RETURN_VALUE)
            {
                sprintf (MsgBuffer, "%s",
                            ReservedMethods[i].Name);

                AslError (ASL_WARNING, ASL_MSG_RESERVED_RETURN_VALUE, Node, MsgBuffer);
            }

            return;
        }
    }

    /*
     * Now check for the "special" reserved names --
     * GPE:  _Lxx
     * GPE:  _Exx
     * EC:   _Qxx
     */

    if ((Node->ExternalName[1] == 'L') ||
        (Node->ExternalName[1] == 'E') ||
        (Node->ExternalName[1] == 'Q'))
    {

        Gbl_ReservedMethods++;

        /* The next two characters must be hex digits */

        if ((isxdigit (Node->ExternalName[2])) &&
            (isxdigit (Node->ExternalName[3])) &&
            (MethodInfo->NumArguments != 0))
        {
            sprintf (MsgBuffer, " %s requires %d",
                        Node->ExternalName, 0);

            AslError (ASL_WARNING, ASL_MSG_RESERVED_ARG_COUNT_HI, Node, MsgBuffer);
        }

        return;
    }


    /* Check for the names reserved for the compiler itself: _T_x */

    if ((Node->ExternalName[1] == 'T') &&
        (Node->ExternalName[2] == '_'))
    {
        AslError (ASL_ERROR, ASL_MSG_RESERVED_WORD, Node, Node->ExternalName);
        return;
    }


    /*
     * The name didn't match any of the known reserved names.  Flag it as a
     * warning, since the entire namespace starting with an underscore is
     * reserved by the ACPI spec.
     */

    AslError (ASL_WARNING, ASL_MSG_UNKNOWN_RESERVED_NAME, Node, Node->ExternalName);
    return;
}


/*******************************************************************************
 *
 * FUNCTION:    AnMethodAnalysisWalkBegin
 *
 * PARAMETERS:  ASL_WALK_CALLBACK
 *
 * RETURN:      none
 *
 * DESCRIPTION: Descending callback for the analysis walk.  Check methods for :
 *              1) Initialized local variables
 *              2) Valid arguments
 *              3) Return types
 *
 ******************************************************************************/

ACPI_STATUS
AnMethodAnalysisWalkBegin (
    ASL_PARSE_NODE          *Node,
    UINT32                  Level,
    void                    *Context)
{
    ASL_ANALYSIS_WALK_INFO  *WalkInfo = (ASL_ANALYSIS_WALK_INFO *) Context;
    ASL_METHOD_INFO         *MethodInfo = WalkInfo->MethodStack;
    ASL_PARSE_NODE          *Next;
    UINT32                  RegisterNumber;
    UINT32                  i;
    char                    LocalName[] = "Local0";
    char                    ArgName[] = "Arg0";


    PROC_NAME ("AnMethodAnalysisWalkBegin");


    switch (Node->ParseOpcode)
    {
    case METHOD:

        TotalMethods++;

        /*
         * Create and init method info
         */
        MethodInfo       = UtLocalCalloc (sizeof (ASL_METHOD_INFO));
        MethodInfo->Next = WalkInfo->MethodStack;
        MethodInfo->Node = Node;

        WalkInfo->MethodStack = MethodInfo;

        /* Get the NumArguments node */

        Next = Node->Child;
        Next = Next->Peer;
        MethodInfo->NumArguments = (UINT8) (Next->Value.Integer8 & 0x07);

        /*
         * Actual arguments are initialized at method entry.
         * All other ArgX "registers" can be used as locals, so we
         * track their initialization.
         */
        for (i = 0; i < MethodInfo->NumArguments; i++)
        {
            MethodInfo->ArgInitialized[i] = TRUE;
        }

        break;


    case METHODCALL:
        if (MethodInfo &&
           (Node->NsNode == MethodInfo->Node->NsNode))
        {
            AslError (ASL_REMARK, ASL_MSG_RECURSION, Node, Node->ExternalName);
        }

        break;

    case LOCAL0:
    case LOCAL1:
    case LOCAL2:
    case LOCAL3:
    case LOCAL4:
    case LOCAL5:
    case LOCAL6:
    case LOCAL7:

        if (!MethodInfo)
        {
            /* Probably was an error in the method declaration, no additional error here */

            ACPI_DEBUG_PRINT ((ACPI_DB_WARN, "%X, No parent method\n", Node));
            return (AE_ERROR);
        }

        RegisterNumber = (Node->AmlOpcode & 0x000F);

        /*
         * If the local is being used as a target, mark the local
         * initialized
         */
        if (Node->Flags & NODE_IS_TARGET)
        {
            MethodInfo->LocalInitialized[RegisterNumber] = TRUE;

        }

        /*
         * Otherwise, this is a reference, check if the local
         * has been previously initialized.
         */
        else if (!MethodInfo->LocalInitialized[RegisterNumber])
        {
            LocalName[strlen (LocalName) -1] = (UINT8) (RegisterNumber + 0x30);
            AslError (ASL_ERROR, ASL_MSG_LOCAL_INIT, Node, LocalName);
        }

        break;


    case ARG0:
    case ARG1:
    case ARG2:
    case ARG3:
    case ARG4:
    case ARG5:
    case ARG6:

        if (!MethodInfo)
        {
            /* Probably was an error in the method declaration, no additional error here */

            ACPI_DEBUG_PRINT ((ACPI_DB_WARN, "%X, No parent method\n", Node));
            return (AE_ERROR);
        }

        RegisterNumber = (Node->AmlOpcode & 0x000F) - 8;
        ArgName[strlen (ArgName) -1] = (UINT8) (RegisterNumber + 0x30);

        /*
         * If the Arg is being used as a target, mark the local
         * initialized
         */
        if (Node->Flags & NODE_IS_TARGET)
        {
            MethodInfo->ArgInitialized[RegisterNumber] = TRUE;

        }

        /*
         * Otherwise, this is a reference, check if the Arg
         * has been previously initialized.
         */
        else if (!MethodInfo->ArgInitialized[RegisterNumber])
        {
            AslError (ASL_ERROR, ASL_MSG_ARG_INIT, Node, ArgName);
        }


        /* Flag this arg if it is not a "real" argument to the method */

        if (RegisterNumber >= MethodInfo->NumArguments)
        {
            AslError (ASL_REMARK, ASL_MSG_NOT_PARAMETER, Node, ArgName);
        }

        break;


    case RETURN:

        if (!MethodInfo)
        {
            /* Probably was an error in the method declaration, no additional error here */

            ACPI_DEBUG_PRINT ((ACPI_DB_WARN, "%X, No parent method\n", Node));
            return (AE_ERROR);
        }

        /* Child indicates a return value */

        if ((Node->Child) &&
            (Node->Child->ParseOpcode != DEFAULT_ARG))
        {
            MethodInfo->NumReturnWithValue++;
        }

        else
        {
            MethodInfo->NumReturnNoValue++;
        }
        break;
    }

    return AE_OK;
}


/*******************************************************************************
 *
 * FUNCTION:    AnLastStatementIsReturn
 *
 * PARAMETERS:  Node            - A method node
 *
 * RETURN:      TRUE if last statement is an ASL RETURN.  False otherwise
 *
 * DESCRIPTION: Walk down the list of top level statements within a method
 *              to find the last one.  Check if that last statement is in
 *              fact a RETURN statement.
 *
 ******************************************************************************/

BOOLEAN
AnLastStatementIsReturn (
    ASL_PARSE_NODE          *Node)
{
    ASL_PARSE_NODE          *Next;


    /*
     * Check if last statement is a return
     */
    Next = ASL_GET_CHILD_NODE (Node);
    while (Next)
    {
        if ((!Next->Peer) &&
            (Next->ParseOpcode == RETURN))
        {
            return TRUE;
        }

        Next = ASL_GET_PEER_NODE (Next);
    }

    return FALSE;
}


/*******************************************************************************
 *
 * FUNCTION:    AnMethodAnalysisWalkEnd
 *
 * PARAMETERS:  ASL_WALK_CALLBACK
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Ascending callback for analysis walk.  Complete method
 *              return analysis.
 *
 ******************************************************************************/

ACPI_STATUS
AnMethodAnalysisWalkEnd (
    ASL_PARSE_NODE          *Node,
    UINT32                  Level,
    void                    *Context)
{
    ASL_ANALYSIS_WALK_INFO  *WalkInfo = (ASL_ANALYSIS_WALK_INFO *) Context;
    ASL_METHOD_INFO         *MethodInfo = WalkInfo->MethodStack;


    switch (Node->ParseOpcode)
    {
    case METHOD:
    case RETURN:
        if (!MethodInfo)
        {
            printf ("No method info for method! [%s]\n", Node->Namepath);
            AslError (ASL_ERROR, ASL_MSG_COMPILER_INTERNAL, Node, "No method info for this method");
            CmCleanupAndExit ();
        }
        break;
    }

    switch (Node->ParseOpcode)
    {
    case METHOD:

        WalkInfo->MethodStack = MethodInfo->Next;


        /*
         * Check if there is no return statement at the end of the
         * method AND we can actually get there -- i.e., the execution
         * of the method can possibly terminate without a return statement.
         */
        if ((!AnLastStatementIsReturn (Node)) &&
            (!(Node->Flags & NODE_HAS_NO_EXIT)))
        {
            /*
             * No return statement, and execution can possibly exit
             * via this path.  This is equivalent to Return ()
             */

            MethodInfo->NumReturnNoValue++;
        }


        /*
         * Check for case where some return statements have a return value
         * and some do not.  Exit without a return statement is a return with
         * no value
         */

        if (MethodInfo->NumReturnNoValue &&
            MethodInfo->NumReturnWithValue)
        {
            AslError (ASL_WARNING, ASL_MSG_RETURN_TYPES, Node, Node->ExternalName);
        }


        /*
         * If there are any RETURN() statements with no value, or there is a
         * control path that allows the method to exit without a return value,
         * we mark the method as a method that does not return a value.  This
         * knowledge can be used to check method invocations that expect a
         * returned value.
         */

        if (MethodInfo->NumReturnNoValue)
        {
            if (MethodInfo->NumReturnWithValue)
            {
                Node->Flags |= NODE_METHOD_SOME_NO_RETVAL;
            }
            else
            {
                Node->Flags |= NODE_METHOD_NO_RETVAL;
            }
        }

        /*
         * Check predefined method names for correct return behavior
         * and correct number of arguments
         */
        AnCheckForReservedMethod (Node, MethodInfo);
        ACPI_MEM_FREE (MethodInfo);

        break;


    case RETURN:

        Node->Parent->Flags |= NODE_HAS_NO_EXIT;
        Node->ParentMethod = MethodInfo->Node;      /* Used in the "typing" pass later */
        break;


    case IF:

        if ((Node->Flags & NODE_HAS_NO_EXIT) &&
            (Node->Peer) &&
            (Node->Peer->ParseOpcode == ELSE))
        {
            Node->Peer->Flags |= NODE_IF_HAS_NO_EXIT;
        }
        break;


    case ELSE:

        if ((Node->Flags & NODE_HAS_NO_EXIT) &&
            (Node->Flags & NODE_IF_HAS_NO_EXIT))
        {
            Node->Parent->Flags |= NODE_HAS_NO_EXIT;
        }
        break;


    default:

        if ((Node->Flags & NODE_HAS_NO_EXIT) &&
            (Node->Parent))
        {
            Node->Parent->Flags |= NODE_HAS_NO_EXIT;
        }
        break;
    }

    return AE_OK;
}


/*******************************************************************************
 *
 * FUNCTION:    AnMethodTypingWalkBegin
 *
 * PARAMETERS:  ASL_WALK_CALLBACK
 *
 * RETURN:      none
 *
 * DESCRIPTION: Descending callback for the typing walk.  
 *
 ******************************************************************************/

ACPI_STATUS
AnMethodTypingWalkBegin (
    ASL_PARSE_NODE          *Node,
    UINT32                  Level,
    void                    *Context)
{

    return AE_OK;
}


/*******************************************************************************
 *
 * FUNCTION:    AnMethodTypingWalkEnd
 *
 * PARAMETERS:  ASL_WALK_CALLBACK
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Ascending callback for typing walk.  Complete method
 *              return analysis.  Check methods for :
 *              1) Initialized local variables
 *              2) Valid arguments
 *              3) Return types
 *
 ******************************************************************************/

ACPI_STATUS
AnMethodTypingWalkEnd (
    ASL_PARSE_NODE          *Node,
    UINT32                  Level,
    void                    *Context)
{
    UINT32                  ThisNodeBtype;


    switch (Node->ParseOpcode)
    {
    case METHOD:
        Node->Flags |= NODE_METHOD_TYPED;
        break;

    case RETURN:
        if ((Node->Child) &&
            (Node->Child->ParseOpcode != DEFAULT_ARG))
        {
            ThisNodeBtype = AnGetBtype (Node->Child);

            if ((Node->Child->ParseOpcode == METHODCALL) &&
                (ThisNodeBtype == (ACPI_UINT32_MAX -1)))
            {
                /*
                 * The method is untyped at this time (typically a forward reference).
                 * We must recursively type the method here
                 */
                TrWalkParseTree ((ASL_PARSE_NODE *) Node->Child->NsNode->Object, 
                        ASL_WALK_VISIT_TWICE, AnMethodTypingWalkBegin,
                        AnMethodTypingWalkEnd, NULL);

                ThisNodeBtype = AnGetBtype (Node->Child);
            }

            /* Returns a value, get it's type */

            Node->ParentMethod->AcpiBtype |= ThisNodeBtype;
        }

        break;
    }

    return AE_OK;
}


/*******************************************************************************
 *
 * FUNCTION:    AnSemanticAnalysisWalkBegin
 *
 * PARAMETERS:  ASL_WALK_CALLBACK
 *
 * RETURN:      none
 *
 * DESCRIPTION: Descending callback for the analysis walk.  Check methods for :
 *              1) Initialized local variables
 *              2) Valid arguments
 *              3) Return types
 *
 ******************************************************************************/

ACPI_STATUS
AnSemanticAnalysisWalkBegin (
    ASL_PARSE_NODE          *Node,
    UINT32                  Level,
    void                    *Context)
{

    return AE_OK;
}


/*******************************************************************************
 *
 * FUNCTION:    AnSemanticAnalysisWalkEnd
 *
 * PARAMETERS:  ASL_WALK_CALLBACK
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Ascending callback for analysis walk.  Complete method
 *              return analysis.
 *
 ******************************************************************************/

ACPI_STATUS
AnSemanticAnalysisWalkEnd (
    ASL_PARSE_NODE          *Node,
    UINT32                  Level,
    void                    *Context)
{
    const ACPI_OPCODE_INFO  *OpInfo;
    UINT32                  ParseArgTypes;
    UINT32                  RuntimeArgTypes;
    UINT32                  RuntimeArgTypes2;
    UINT32                  RequiredBtypes;
    ASL_PARSE_NODE          *ArgNode;
    UINT32                  ArgType;
    UINT32                  ThisNodeBtype;
    UINT32                  AcpiEtype;
    UINT32                  OpcodeClass;
    UINT32                  i;
    UINT32                  CommonBtypes;


    switch (Node->AmlOpcode)
    {
    case AML_RAW_DATA_BYTE:
    case AML_RAW_DATA_WORD:
    case AML_RAW_DATA_DWORD:
    case AML_RAW_DATA_QWORD:
    case AML_RAW_DATA_BUFFER:
    case AML_RAW_DATA_CHAIN:
    case AML_PACKAGE_LENGTH:
    case AML_UNASSIGNED_OPCODE:
    case AML_DEFAULT_ARG_OP:
        return (AE_OK);

    }

    OpInfo = AcpiPsGetOpcodeInfo (Node->AmlOpcode);
    if (!OpInfo)
    {
        return (AE_OK);
    }


    ArgNode         = Node->Child;
    RuntimeArgTypes = OpInfo->RuntimeArgs;
    ParseArgTypes   = OpInfo->ParseArgs;
    OpcodeClass     = OpInfo->Class;

    /* Ignore the non-executable opcodes */

    if (RuntimeArgTypes == ARGI_INVALID_OPCODE)
    {
        return (AE_OK);
    }


    switch (OpcodeClass)
    {
    case AML_CLASS_EXECUTE:
    case AML_CLASS_CREATE:
    case AML_CLASS_CONTROL:
    case AML_CLASS_RETURN_VALUE:

        RuntimeArgTypes2 = 0;
        while ((ArgType = GET_CURRENT_ARG_TYPE (RuntimeArgTypes)))
        {
            RuntimeArgTypes2 <<= ARG_TYPE_WIDTH;
            RuntimeArgTypes2 |= ArgType;
            INCREMENT_ARG_LIST (RuntimeArgTypes);
        }

        i = 1;
        while ((ArgType = GET_CURRENT_ARG_TYPE (RuntimeArgTypes2)))
        {
            RequiredBtypes = AnMapArgTypeToBtype (ArgType);

            ThisNodeBtype = AnGetBtype (ArgNode);
            if (ThisNodeBtype == ACPI_UINT32_MAX)
            {
                goto NextArgument;
            }

            /* Examine the arg based on the required type of the arg */

            switch (ArgType)
            {
            case ARGI_TARGETREF:

                if (ArgNode->ParseOpcode == ZERO)
                {
                    /* ZERO is the placeholder for "don't store result" */

                    ThisNodeBtype = RequiredBtypes;
                    break;
                }

                if (ArgNode->ParseOpcode == INTEGER)
                {
                    /*
                     * This is the case where an original reference to a resource
                     * descriptor field has been replaced by an (Integer) offset.
                     * These named fields are supported at compile-time only;
                     * the names are not passed to the interpreter (via the AML).
                     */
                    if ((ArgNode->NsNode->Type == INTERNAL_TYPE_RESOURCE_FIELD) ||
                        (ArgNode->NsNode->Type == INTERNAL_TYPE_RESOURCE))
                    {
                        AslError (ASL_ERROR, ASL_MSG_RESOURCE_FIELD, ArgNode, NULL);
                    }

                    else
                    {
                        AslError (ASL_ERROR, ASL_MSG_INVALID_TYPE, ArgNode, NULL);
                    }
                    break;
                }

                if ((ArgNode->ParseOpcode == METHODCALL) ||
                    (ArgNode->ParseOpcode == DEREFOF))
                {
                    break;
                }

                ThisNodeBtype = RequiredBtypes;
                break;


            case ARGI_REFERENCE:            /* References */
            case ARGI_INTEGER_REF:
            case ARGI_OBJECT_REF:
            case ARGI_DEVICE_REF:

                switch (ArgNode->ParseOpcode)
                {
                case LOCAL0:
                case LOCAL1:
                case LOCAL2:
                case LOCAL3:
                case LOCAL4:
                case LOCAL5:
                case LOCAL6:
                case LOCAL7:

                    /* TBD: implement analysis of current value (type) of the local */
                    /* For now, just treat any local as a typematch */

                    //ThisNodeBtype = RequiredBtypes;
                    break;

                case ARG0:
                case ARG1:
                case ARG2:
                case ARG3:
                case ARG4:
                case ARG5:
                case ARG6:

                    /* Hard to analyze argument types, sow we won't */
                    /* For now, just treat any arg as a typematch */

                    //ThisNodeBtype = RequiredBtypes;
                    break;

                case DEBUG:
                    break;

                case REFOF:
                case INDEX:
                    break;

                }
                break;

            case ARGI_INTEGER:
                break;
            }


            CommonBtypes = ThisNodeBtype & RequiredBtypes;

            if (ArgNode->ParseOpcode == METHODCALL)
            {
                if (!CommonBtypes)
                {
                    AnFormatBtype (StringBuffer, ThisNodeBtype);
                    AnFormatBtype (StringBuffer2, RequiredBtypes);

                    /*
                     * The case where the method does not return any value at all
                     * was already handled in the namespace cross reference
                     * -- Only issue an error if the method in fact returns a value,
                     * but it is of the wrong type
                     */
                    if (ThisNodeBtype != 0)
                    {
                        sprintf (MsgBuffer, "Method returns [%s], %s operator requires [%s]",
                                    StringBuffer, OpInfo->Name, StringBuffer2);

                        AslError (ASL_ERROR, ASL_MSG_INVALID_TYPE, ArgNode, MsgBuffer);
                    }
                }
            }

            /*
             * Now check if the actual type(s) match at least one
             * bit to the required type
             */
            else if (!CommonBtypes)
            {
                /* TBD: Can an implicit conversion be performed? */

                AcpiEtype = AnMapBtypeToEtype (ThisNodeBtype);

                AnFormatBtype (StringBuffer, ThisNodeBtype);
                AnFormatBtype (StringBuffer2, RequiredBtypes);

                sprintf (MsgBuffer, "[%s] found, %s operator requires [%s]",
                            StringBuffer, OpInfo->Name, StringBuffer2);

                AslError (ASL_ERROR, ASL_MSG_INVALID_TYPE, ArgNode, MsgBuffer);
            }


        NextArgument:
            ArgNode = ArgNode->Peer;
            INCREMENT_ARG_LIST (RuntimeArgTypes2);
            i++;
        }
    }


    return (AE_OK);
}


