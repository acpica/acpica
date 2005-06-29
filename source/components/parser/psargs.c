/******************************************************************************
 * 
 * Module Name: psargs - Parse AML opcode arguments
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

#define __PSARGS_C__

#include <acpi.h>
#include <parser.h>
#include <amlcode.h>
#include <namesp.h>

#define _COMPONENT          PARSER
        MODULE_NAME         ("psargs");


/*******************************************************************************
 *
 * FUNCTION:    PsGetNextPackageLength
 *
 * PARAMETERS:  ParserState         - Current parser state object
 *
 * RETURN:      Decoded package length.  On completion, the AML pointer points 
 *              past the length byte or bytes.
 *
 * DESCRIPTION: Decode and return a package length field
 *
 ******************************************************************************/

UINT32
PsGetNextPackageLength (
    ACPI_PARSE_STATE        *ParserState)
{
    INT32                   EncodedLength;
    INT32                   Length = 0;


    FUNCTION_TRACE ("PsGetNextPackageLength");


    EncodedLength = (INT32) GET8 (ParserState->Aml);
    ParserState->Aml++;


    switch (EncodedLength >> 6) /* bits 6-7 contain encoding scheme */
    {
    case 0: /* 1-byte encoding (bits 0-5) */

        Length = (EncodedLength & 0x3f);
        break;


    case 1: /* 2-byte encoding (next byte + bits 0-3) */

        Length = (GET8 (ParserState->Aml) << 4) | (EncodedLength & 0xf);
        ParserState->Aml++;
        break;


    case 2: /* 3-byte encoding (next 2 bytes + bits 0-3) */

        Length = ( (GET8 (ParserState->Aml + 1) << 12)
               | (GET8 (ParserState->Aml) << 4)
               | (EncodedLength & 0xf));
        ParserState->Aml += 2;
        break;


    case 3: /* 4-byte encoding (next 3 bytes + bits 0-3) */

        Length = ( (GET8 (ParserState->Aml + 2) << 20)
               | (GET8 (ParserState->Aml + 1) << 12)
               | (GET8 (ParserState->Aml) << 4)
               | (EncodedLength & 0xf));
        ParserState->Aml += 3;
        break;
    }

    return_VALUE (Length);
}


/*******************************************************************************
 *
 * FUNCTION:    PsGetNextPackageEnd
 *
 * PARAMETERS:  ParserState         - Current parser state object
 *
 * RETURN:      Pointer to end-of-package +1
 *
 * DESCRIPTION: Get next package length and return a pointer past the end of 
 *              the package.  Consumes the package length field
 *
 ******************************************************************************/

UINT8 *
PsGetNextPackageEnd (
    ACPI_PARSE_STATE        *ParserState)
{
    UINT8                   *Start = ParserState->Aml;
    NATIVE_UINT             Length;


    FUNCTION_TRACE ("PsGetNextPackageEnd");


    Length = (NATIVE_UINT) PsGetNextPackageLength (ParserState);

    return_PTR (Start + Length); /* end of package */
}


/*******************************************************************************
 *
 * FUNCTION:    PsGetNextNamestring
 *
 * PARAMETERS:  ParserState         - Current parser state object
 *
 * RETURN:      Pointer to the start of the name string (pointer points into
 *              the AML.
 *
 * DESCRIPTION: Get next raw namestring within the AML stream.  Handles all name 
 *              prefix characters.  Set parser state to point past the string.
 *              (Name is consumed from the AML.)
 *
 ******************************************************************************/

char *
PsGetNextNamestring (
    ACPI_PARSE_STATE        *ParserState)
{
    char                    *Start = (char *) ParserState->Aml;
    char                    *End = (char *) ParserState->Aml;
    INT32                   Length;


    FUNCTION_TRACE ("PsGetNextNamestring");


    /* Handle multiple prefix characters */

    while (PsIsPrefixChar (GET8 (End)))
    {
        /* include prefix '\\' or '^' */

        End++;
    }

    /* Decode the path */

    switch (GET8 (End))
    {
    case 0:
        
        /* NullName */

        if (End == Start)
        {
            Start = NULL;
        }
        End++;
        break;


    case AML_DualNamePrefix:

        /* two name segments */

        End += 9;
        break;


    case AML_MultiNamePrefixOp:

        /* multiple name segments */

        Length = (INT32) GET8 (End + 1) * 4;
        End += 2 + Length;
        break;


    default:

        /* single name segment */
        /* assert (PsIsLead (GET8 (End))); */

        End += 4;
        break;
    }

    ParserState->Aml = (UINT8*) End;

    return_PTR (Start);
}


/*******************************************************************************
 *
 * FUNCTION:    PsGetNextNamepath
 *
 * PARAMETERS:  ParserState         - Current parser state object
 *              Arg                 - Where the namepath will be stored
 *              ArgCount            - If the namepath points to a control method,
 *                                    the method's argument is returned here.
 *              MethodCall          - Whether the namepath can be the start
 *                                    of a method call
 *
 * RETURN:      None
 *
 * DESCRIPTION: Get next name (if method call, push appropriate # args).  Names
 *              are looked up in either the parsed or internal namespace to 
 *              determine if the name represents a control method.  If a method
 *              is found, the number of arguments to the method is returned.  This
 *              information is critical for parsing to continue correctly.
 *
 ******************************************************************************/

void
PsGetNextNamepath (
    ACPI_PARSE_STATE        *ParserState,
    ACPI_GENERIC_OP         *Arg,
    UINT32                  *ArgCount,
    BOOLEAN                 MethodCall)
{
    char                    *Path;
    ACPI_GENERIC_OP         *Name;



    FUNCTION_TRACE ("PsGetNextNamepath");


    Path = PsGetNextNamestring (ParserState);
    if (!Path || !MethodCall)
    {
        /* Null name case, create a null namepath object */

        PsInitOp (Arg, AML_NAMEPATH_OP);        
        Arg->Value.Name = Path;
        return_VOID;
    }


#ifdef PARSER_ONLY
    if (Gbl_ParsedNamespaceRoot)
    {
        ACPI_GENERIC_OP         *MethodOp;
        ACPI_GENERIC_OP         *Count;

        /*
         * Lookup the name in the parsed namespace 
         */

        MethodOp = MethodCall ? PsFind (PsGetParentScope (ParserState), Path, AML_MethodOp, 0):NULL;
        if (MethodOp)
        {
            DEBUG_PRINT (TRACE_PARSE, ("PsGetNextNamepath: Found a method while parsed namespace still valid!\n"));

            Count = PsGetArg (MethodOp, 0);
            if (Count && Count->Opcode == AML_ByteOp)
            {
                Name = PsAllocOp (AML_NAMEPATH_OP);
                if (Name)
                {
                    /* Change arg into a METHOD CALL and attach the name to it */

                    PsInitOp (Arg, AML_METHODCALL_OP);

                    Name->Value.Name        = Path;
                    Name->NameTableEntry    = MethodOp;          /* Point METHODCALL/NAME to the METHOD NTE */
                    PsAppendArg (Arg, Name);
                    
                    *ArgCount = Count->Value.Integer & METHOD_FLAGS_ARG_COUNT;
                }
            }

            return_VOID;
        }
    }

#else
    {
        /*
         * The full parse tree has already been deleted -- therefore, we are parsing
         * a control method.  We can lookup the name in the namespace instead of
         * the parse tree!
         */

        ACPI_STATUS             Status;
        NAME_TABLE_ENTRY        *Method = NULL;
        NAME_TABLE_ENTRY        *Nte;
        ACPI_GENERIC_STATE      ScopeInfo;


        /* 
         * Lookup the name in the internal namespace
         */
        ScopeInfo.Scope.Entry = NULL;
        Nte = ParserState->StartOp->NameTableEntry;
        if (Nte)
        {
            ScopeInfo.Scope.Entry = Nte->Scope;
        }

        /* 
         * Lookup object.  We don't want to add anything new to the namespace here, however.
         * So we use MODE_EXECUTE.
         */

        Status = NsLookup (&ScopeInfo, Path, ACPI_TYPE_Any, IMODE_Execute, /* MUST BE mode EXECUTE to perform upsearch */ 
                                NS_SEARCH_PARENT | NS_DONT_OPEN_SCOPE, NULL, &Nte);
        if (ACPI_SUCCESS (Status))
        {
            if (Nte->Type == ACPI_TYPE_Method)
            {
                Method = Nte;
                DEBUG_PRINT (TRACE_PARSE, ("PsGetNextNamepath: method - %p Path=%p\n", Method, Path));

                Name = PsAllocOp (AML_NAMEPATH_OP);
                if (Name)
                {
                    /* Change arg into a METHOD CALL and attach the name to it */

                    PsInitOp (Arg, AML_METHODCALL_OP);

                    Name->Value.Name        = Path;
                    Name->NameTableEntry    = Method;           /* Point METHODCALL/NAME to the METHOD NTE */
                    PsAppendArg (Arg, Name);

                    *ArgCount = ((ACPI_OBJECT_INTERNAL *) Method->Object)->Method.ParamCount;
                }
            
                return_VOID;
            }
        }
    }
#endif

    /* Everything else has failed */
    /* variable dereference */

    PsInitOp (Arg, AML_NAMEPATH_OP);        
    Arg->Value.Name = Path;


    return_VOID;
}


/*******************************************************************************
 *
 * FUNCTION:    PsGetNextSimpleArg 
 *
 * PARAMETERS:  ParserState         - Current parser state object
 *              ArgType             - The argument type (AML_*_ARG)
 *              Arg                 - Where the argument is returned
 *
 * RETURN:      None
 *
 * DESCRIPTION: Get the next simple argument (constant, string, or namestring)
 *
 ******************************************************************************/

void
PsGetNextSimpleArg (
    ACPI_PARSE_STATE        *ParserState,
    INT32                   ArgType,
    ACPI_GENERIC_OP         *Arg)
{


    FUNCTION_TRACE_U32 ("PsGetNextSimpleArg", ArgType);


    switch (ArgType)
    {

    case ARGP_BYTEDATA:

        PsInitOp (Arg, AML_ByteOp);
        Arg->Value.Integer = (UINT32) GET8 (ParserState->Aml);
        ParserState->Aml++;
        break;


    case ARGP_WORDDATA:

        PsInitOp (Arg, AML_WordOp);
        Arg->Value.Integer = (UINT32) GET16 (ParserState->Aml);
        ParserState->Aml += 2;
        break;


    case ARGP_DWORDDATA:

        PsInitOp (Arg, AML_DWordOp);
        Arg->Value.Integer = (UINT32) GET32 (ParserState->Aml);
        ParserState->Aml += 4;
        break;


    case ARGP_CHARLIST:

        PsInitOp (Arg, AML_StringOp);
        Arg->Value.String = (char*) ParserState->Aml;

        while (GET8 (ParserState->Aml) != '\0')
        {
            ParserState->Aml++;
        }
        ParserState->Aml++;
        break;


    case ARGP_NAME:
    case ARGP_NAMESTRING:

        PsInitOp (Arg, AML_NAMEPATH_OP);
        Arg->Value.Name = PsGetNextNamestring (ParserState);
        break;
    }

    return_VOID;
}


/*******************************************************************************
 *
 * FUNCTION:    PsGetNextField
 *
 * PARAMETERS:  ParserState         - Current parser state object
 *
 * RETURN:      A newly allocated FIELD op
 *
 * DESCRIPTION: Get next field (NamedField, ReservedField, or AccessField)
 *
 ******************************************************************************/

ACPI_GENERIC_OP *
PsGetNextField (
    ACPI_PARSE_STATE        *ParserState)
{
    ACPI_PTRDIFF            AmlOffset = ParserState->Aml - ParserState->AmlStart;
    ACPI_GENERIC_OP         *Field;
    UINT16                  Opcode;


    FUNCTION_TRACE ("PsGetNextField");


    /* determine field type */

    switch (GET8 (ParserState->Aml))
    {

    default:

        Opcode = AML_NAMEDFIELD_OP;
        break;


    case 0x00:

        Opcode = AML_RESERVEDFIELD_OP;
        ParserState->Aml++;
        break;


    case 0x01:

        Opcode = AML_ACCESSFIELD_OP;
        ParserState->Aml++;
        break;
    }


    /* Allocate a new field op */

    Field = PsAllocOp (Opcode);
    if (Field)
    {
        Field->AmlOffset = AmlOffset;

        /* Decode the field type */

        switch (Opcode)
        {
        case AML_NAMEDFIELD_OP:

            /* Get the name */

            PsSetName (Field, GET32 (ParserState->Aml));
            ParserState->Aml += 4;

            /* Get the length which is encoded as a package length */

            Field->Value.Size = PsGetNextPackageLength (ParserState);
            break;


        case AML_RESERVEDFIELD_OP:

            /* Get the length which is encoded as a package length */

            Field->Value.Size = PsGetNextPackageLength (ParserState);
            break;


        case AML_ACCESSFIELD_OP:

            /* Get the AccessType and AccessAtrib and merge them into the field Op */

            Field->Value.Integer = ((GET8 (ParserState->Aml) << 8) | 
                                     GET8 (ParserState->Aml));
            ParserState->Aml += 2;
            break;
        }
    }

    return_PTR (Field);
}


/*******************************************************************************
 *
 * FUNCTION:    PsGetNextArg
 *
 * PARAMETERS:  ParserState         - Current parser state object
 *              ArgType             - The argument type (AML_*_ARG)
 *              ArgCount            - If the argument points to a control method,
 *                                    the method's argument is returned here.
 *
 * RETURN:      An op object containing the next argument.
 *
 * DESCRIPTION: Get next argument (including complex list arguments that require
 *              pushing the parser stack)
 *
 ******************************************************************************/

ACPI_GENERIC_OP *
PsGetNextArg (
    ACPI_PARSE_STATE        *ParserState, 
    INT32                   ArgType, 
    UINT32                  *ArgCount)
{
    ACPI_GENERIC_OP         *Arg = NULL;
    ACPI_GENERIC_OP         *Prev = NULL;
    ACPI_GENERIC_OP         *Field;
    INT32                   Subop;



    FUNCTION_TRACE_PTR ("PsGetNextArg", ParserState);


    switch (ArgType)
    {
    case ARGP_BYTEDATA:
    case ARGP_WORDDATA:
    case ARGP_DWORDDATA:
    case ARGP_CHARLIST:
    case ARGP_NAME:
    case ARGP_NAMESTRING:

        /* constants, strings, and namestrings are all the same size */

        Arg = PsAllocOp (AML_ByteOp);
        if (Arg)
        {
            PsGetNextSimpleArg (ParserState, ArgType, Arg);
        }
        break;


    case ARGP_PKGLENGTH:

        /* package length, nothing returned */

        ParserState->PkgEnd = PsGetNextPackageEnd (ParserState);
        break;


    case ARGP_FIELDLIST:

        if (ParserState->Aml < ParserState->PkgEnd)
        {
            /* non-empty list */

            while (ParserState->Aml < ParserState->PkgEnd)
            {
                Field = PsGetNextField (ParserState);
                if (!Field)
                {
                    break;
                }

                if (Prev)
                {
                    Prev->Next = Field;
                }

                else
                {
                    Arg = Field;
                }

                Prev = Field;
            }

            /* skip to End of byte data */

            ParserState->Aml = ParserState->PkgEnd;
        }
        break;


    case ARGP_BYTELIST:

        if (ParserState->Aml < ParserState->PkgEnd)
        {
            /* non-empty list */

            Arg = PsAllocOp (AML_BYTELIST_OP);
            if (Arg)
            {
                /* fill in bytelist data */

                Arg->Value.Size = (ParserState->PkgEnd - ParserState->Aml);
                PsToBytelistOp (Arg)->Data = ParserState->Aml;
            }

            /* skip to End of byte data */

            ParserState->Aml = ParserState->PkgEnd;
        }
        break;


    case ARGP_TARGET:
    case ARGP_SUPERNAME:
        {
            Subop = PsPeekOpcode (ParserState);
            if (Subop == 0              || 
                PsIsLeadingChar (Subop) || 
                PsIsPrefixChar (Subop))
            {
                /* NullName or NameString */

                Arg = PsAllocOp (AML_NAMEPATH_OP);
                if (Arg)
                {
                    PsGetNextNamepath (ParserState, Arg, ArgCount, 0);
                }
            }

            else
            {
                /* single complex argument, nothing returned */

                *ArgCount = 1;
            }
        }
        break;
            

    case ARGP_DATAOBJ:
    case ARGP_TERMARG:

        /* single complex argument, nothing returned */

        *ArgCount = 1;
        break;


    case ARGP_DATAOBJLIST:
    case ARGP_TERMLIST:
    case ARGP_OBJLIST:

        if (ParserState->Aml < ParserState->PkgEnd)
        {
            /* non-empty list of variable arguments, nothing returned */

            *ArgCount = ACPI_VAR_ARGS;
        }
        break;
    }

    return_PTR (Arg);
}
