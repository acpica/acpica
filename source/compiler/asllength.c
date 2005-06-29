
/******************************************************************************
 *
 * Module Name: asllength - Tree walk to determine package and opcode lengths
 *              $Revision: 1.2 $
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


#include "AslCompiler.h"
#include "AslCompiler.y.h"
#include "amlcode.h"



/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

void
CgAmlPackageLengthWalk (
    ASL_PARSE_NODE              *Node,
    UINT32                      Level,
    void                        *Context)
{



    /* TBD Do an "init nodes" walk */
/*
    Node->AmlLength = 0;
    Node->AmlOpcodeLength = 0;
    Node->AmlSubtreeLength = 0;
    Node->AmlPkgLenBytes = 0;
*/
    /* 
     * generate the subtree length and
     * bubble it up to the parent
     */
    CgGenerateAmlLengths (Node);
    if ((Node->Parent) &&
        (Node->ParseOpcode != DEFAULT_ARG))
    {
        Node->Parent->AmlSubtreeLength += (Node->AmlLength + 
                                            Node->AmlOpcodeLength +
                                            Node->AmlPkgLenBytes + 
                                            Node->AmlSubtreeLength);
    }
}



/*******************************************************************************
 *
 * FUNCTION:    AcpiNsValidRootPrefix
 *
 * PARAMETERS:  Prefix          - Character to be checked
 *
 * RETURN:      TRUE if a valid prefix
 *
 * DESCRIPTION: Check if a character is a valid ACPI Root prefix
 *
 ******************************************************************************/

BOOLEAN
AcpiNsValidRootPrefix (
    NATIVE_CHAR             Prefix)
{

    return ((BOOLEAN) (Prefix == '\\'));
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiNsValidPathSeparator
 *
 * PARAMETERS:  Sep              - Character to be checked
 *
 * RETURN:      TRUE if a valid path separator
 *
 * DESCRIPTION: Check if a character is a valid ACPI path separator
 *
 ******************************************************************************/

BOOLEAN
AcpiNsValidPathSeparator (
    NATIVE_CHAR             Sep)
{

    return ((BOOLEAN) (Sep == '.'));
}


/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

ACPI_STATUS
AcpiNsInternalizeName (
    NATIVE_CHAR             *ExternalName,
    NATIVE_CHAR             **ConvertedName)
{
    NATIVE_CHAR             *Result = NULL;
    NATIVE_CHAR             *InternalName;
    UINT32                  NumSegments;
    UINT32                  NumCarats;
    BOOLEAN                 FullyQualified = FALSE;
    UINT32                  i;


    FUNCTION_TRACE ("NsInternalizeName");


    if ((!ExternalName)      ||
        (*ExternalName == 0) ||
        (!ConvertedName))
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }


    /*
     * For the internal name, the required length is 4 bytes
     * per segment, plus 1 each for RootPrefix, MultiNamePrefixOp,
     * segment count, trailing null (which is not really needed,
     * but there's no harm in putting it there)
     *
     * strlen() + 1 covers the first NameSeg, which has no
     * path separator
     */

    if (AcpiNsValidRootPrefix (ExternalName[0]))
    {
        FullyQualified = TRUE;
        ExternalName++;
    }

    NumCarats = 0;
    while (*ExternalName == '^')
    {
        if (FullyQualified)
        {
            return_ACPI_STATUS (AE_BAD_PATHNAME);
        }

        NumCarats++;
        ExternalName++;
    }

    /*
     * Determine the number of ACPI name "segments" by counting
     * the number of path separators within the string.  Start
     * with one segment since the segment count is (# separators)
     * + 1, and zero separators is ok.
     */

    NumSegments = 1;
    for (i = 0; ExternalName[i]; i++)
    {
        if (AcpiNsValidPathSeparator (ExternalName[i]))
        {
            NumSegments++;
        }
    }


    /* We need a segment to store the internal version of the name */

    InternalName = calloc ((ACPI_NAME_SIZE * NumSegments) + 4 + NumCarats, 1);
    if (!InternalName)
    {
        DbgPrint ("Error - insufficient memory\n");
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /* Setup the correct prefixes, counts, and pointers */

    if (FullyQualified)
    {
        InternalName[0] = '\\';

        if (NumSegments == 1)
        {
            Result = &InternalName[1];
            if (!ExternalName[0])
            {
                *Result = 0;
                NumSegments = 0;
            }
        }
        else if (NumSegments == 2)
        {
            InternalName[1] = AML_DUAL_NAME_PREFIX;
            Result = &InternalName[2];
        }
        else
        {
            InternalName[1] = AML_MULTI_NAME_PREFIX_OP;
            InternalName[2] = (char) NumSegments;
            Result = &InternalName[3];
        }

    }
    else 
    {
        Result = InternalName;
        for (i = 0; i < NumCarats; i++)
        {
            *Result = '^';
            Result++;
        }

        if (NumSegments == 1)
        {
        }

        else if (NumSegments == 2)
        {
            *Result = AML_DUAL_NAME_PREFIX;
            Result++;
        }
        else
        {
            Result[0] = AML_MULTI_NAME_PREFIX_OP;
            Result[1] = (char) NumSegments;
            Result = &Result[2];
        }
    }


    /* Build the name (minus path separators) */

    for (; NumSegments; NumSegments--)
    {
        for (i = 0; i < ACPI_NAME_SIZE; i++)
        {
            if (AcpiNsValidPathSeparator (*ExternalName) ||
               (*ExternalName == 0))
            {
                /*
                 * Pad the segment with underscore(s) if
                 * segment is short
                 */

                Result[i] = '_';
            }

            else
            {
                /* Convert INT8 to uppercase and save it */

                Result[i] = (char) toupper (*ExternalName);
                ExternalName++;
            }

        }

        /* Now we must have a path separator, or the pathname is bad */

        if (!AcpiNsValidPathSeparator (*ExternalName) &&
            (*ExternalName != 0))
        {
            free(InternalName);
            return_ACPI_STATUS (AE_BAD_PARAMETER);
        }

        /* Move on the next segment */

        ExternalName++;
        Result += ACPI_NAME_SIZE;
    }


    /* Return the completed name */

    /* Terminate the string! */
    *Result = 0;
    *ConvertedName = InternalName;


    if (FullyQualified)
    {
        DEBUG_PRINT (TRACE_EXEC,
            ("NsInternalizeName: returning [%p] (abs) \"\\%s\"\n",
            InternalName, &InternalName[3]));
    }
    else
    {
        DEBUG_PRINT (TRACE_EXEC,
            ("NsInternalizeName: returning [%p] (rel) \"%s\"\n",
            InternalName, &InternalName[2]));
    }

    return_ACPI_STATUS (AE_OK);
}



/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

UINT8
CgGetPackageLenByteCount (
    UINT32                  PackageLength)
{

    /* 
     * Determine the number of bytes required to encode the package length
     * Note: the package length includes the number of bytes used to encode
     * the package length, so we must account for this also.
     */
    if (PackageLength <= (0x0000003F - 1)) 
    {
        return (1);
    }
    else if (PackageLength <= (0x00000FFF - 2))
    {
        return (2);
    }
    else if (PackageLength <= (0x000FFFFF - 3))
    {
        return (3);
    }
    else if (PackageLength <= (0x0FFFFFFF - 4))
    {
        return (4);
    }
    else
    {
        /* Fatal error - the package length is too large to encode */

        AslError (ASL_ERROR_ENCODING_LENGTH );
    }

    return (0);
}



/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

void
CgGenerateAmlOpcodeLength (
    ASL_PARSE_NODE          *Node)
{


    /* Check for two-byte opcode */

    if (Node->AmlOpcode > 0x00FF)
    {
        Node->AmlOpcodeLength = 2;
    }

    else
    {
        Node->AmlOpcodeLength = 1;
    }

    /* Does this opcode have an associated "PackageLength" field? */

    Node->AmlPkgLenBytes = 0;
    if (Node->Flags & NODE_AML_PACKAGE)
    {
        Node->AmlPkgLenBytes = CgGetPackageLenByteCount (Node->AmlSubtreeLength);
    }

    switch (Node->AmlOpcode)
    {
    case AML_BYTE_OP:
        Node->AmlLength += 1;
        break;

    case AML_WORD_OP:
        Node->AmlLength += 2;
        break;

    case AML_DWORD_OP:
        Node->AmlLength += 4;
        break;

    }
}



/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

void
CgGenerateAmlLengths (
    ASL_PARSE_NODE          *Node)
{
    char                    *Buffer;
    ACPI_STATUS             Status;
    


    switch (Node->AmlOpcode)
    {
    case AML_RAW_DATA_BYTE:
        Node->AmlOpcodeLength = 0;
        Node->AmlLength = 1;
        return;
    
    case AML_RAW_DATA_WORD:
        Node->AmlOpcodeLength = 0;
        Node->AmlLength = 2;
        return;
    
    case AML_RAW_DATA_DWORD:
        Node->AmlOpcodeLength = 0;
        Node->AmlLength = 4;
        return;
    
    case AML_RAW_DATA_QWORD:
        Node->AmlOpcodeLength = 0;
        Node->AmlLength = 8;
        return;

    case AML_RAW_DATA_BUFFER:
        /* Aml length set by creator */
        Node->AmlOpcodeLength = 0;
        return;
    }


    switch (Node->ParseOpcode)
    {
    case DEFINITIONBLOCK:
        TableLength = sizeof (ACPI_TABLE_HEADER) + Node->AmlSubtreeLength;
        break;

    case NAMESEG:
        Node->AmlOpcodeLength = 0;
        Node->AmlLength = 4;
        break;

    case NAMESTRING:
        Node->AmlOpcodeLength = 0;
        Status = AcpiNsInternalizeName (Node->Value.String, &Buffer);
        if (ACPI_FAILURE (Status))
        {
            DbgPrint ("Failure from internalize name %X\n", Status);
            break;
        }

        free (Node->Value.String);
        Node->Value.String = Buffer;

        Node->AmlLength = strlen (Buffer);
        
        /* 
         * Check for single backslash reference to root,
         * make it a null terminated string in the AML
         */
        if (Node->AmlLength == 1)
        {
            Node->AmlLength = 2;
        }
        break;

    case STRING_LITERAL:
        Node->AmlOpcodeLength = 1;
        Node->AmlLength = strlen (Node->Value.String) + 1; /* Get null terminator */
        break;

    case PACKAGE_LENGTH:
        Node->AmlOpcodeLength = 0;
        Node->AmlPkgLenBytes = CgGetPackageLenByteCount (Node->Value.Integer32);
        break;

    case RAW_DATA:
        Node->AmlOpcodeLength = 0;
        Node->AmlLength = 1;
        break;

    /* Ignore the "default arg" nodes, they are extraneous at this point */

    case DEFAULT_ARG:
        break;

    default:
        CgGenerateAmlOpcodeLength (Node);
        break;
    }
}




