/******************************************************************************
 * 
 * Module Name: dbdisasm - parser op tree display routines
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


#include <acpi.h>
#include <parser.h>
#include <amlcode.h>
#include <namesp.h>
#include <debugger.h>


#ifdef ACPI_DEBUG

#define _COMPONENT          DEBUGGER
        MODULE_NAME         ("dbdisasm");


#define MAX_SHOW_ENTRY      128


char						*INDENT_STRING = "....";



/*******************************************************************************
 *
 * FUNCTION:    DbBlockType
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Type of block for this op (parens or braces)
 *
 ******************************************************************************/

#define BLOCK_PAREN 1
#define BLOCK_BRACE 2

INT32
DbBlockType (
    ACPI_GENERIC_OP *Op)
{

    switch (Op->Opcode)
    {
    case AML_MethodOp:
        return BLOCK_BRACE;
        break;

    default:
        break;
    }

    return BLOCK_PAREN;

}

/*******************************************************************************
 *
 * FUNCTION:    PsDisplayObjectPathname
 *
 * PARAMETERS:  Op              - Object whose pathname is to be obtained
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Diplay the pathname associated with a named object.  Two versions.
 *              One searches the parse tree (for parser-only applications such
 *              as AcpiDump), and the other searches the ACPI namespace (the
 *              parse tree is probably deleted)
 *
 ******************************************************************************/

#ifdef PARSER_ONLY

ACPI_STATUS
PsDisplayObjectPathname (
    ACPI_GENERIC_OP         *Op)
{
    ACPI_GENERIC_OP         *TargetOp;


    OsdPrintf ("  (Path ");

    /* Search parent tree up to the root if necessary */

    TargetOp = PsFind (Op, Op->Value.Name, 0, 0);
    if (!TargetOp)
    {
        /*
         * Didn't find the name in the parse tree.  This may be
         * a problem, or it may simply be one of the predefined names
         * (such as _OS_).  Rather than worry about looking up all
         * the predefined names, just display the name as given
         */

        DbDisplayNamestring (Op->Value.Name);
    }

    else
    {
        /* The target was found, print the name and complete path */

        DbDisplayPath (TargetOp);
    }

    OsdPrintf (")");
    return AE_OK;
}

#else

ACPI_STATUS
PsDisplayObjectPathname (
    ACPI_GENERIC_OP         *Op)
{
    ACPI_STATUS             Status;
    NAME_TABLE_ENTRY        *Nte;
    char                    Buffer[MAX_SHOW_ENTRY];
    UINT32                  BufferSize = MAX_SHOW_ENTRY;


    OsdPrintf ("  (Path ");

    /* Just get the NTE out of the Op object */

    Nte = Op->NameTableEntry;
    if (!Nte)
    {
        /*
         * No NTE, so we can't get the pathname since the object
         * is not in the namespace.  This can happen during single
         * stepping where a dynamic named object is *about* to be created.
         */
        return AE_OK;
    }

    /* Convert NTE/handle to a full pathname */

    Status = NsHandleToPathname (Nte, &BufferSize, Buffer);
    if (ACPI_FAILURE (Status))
    {
        OsdPrintf ("****Could not get pathname****)");
        return Status;
    }

    OsdPrintf ("%s)", Buffer);
    return AE_OK;
}

#endif



/*******************************************************************************
 *
 * FUNCTION:    DbDisplayOp
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Show op and its children
 *
 ******************************************************************************/

#define DB_NO_OP_INFO       "            [%2.2d]  "
#define DB_FULL_OP_INFO     "%5.5X #%4.4X [%2.2d]  "

void
DbDisplayOp (
    ACPI_GENERIC_OP         *Origin,
    UINT32                  NumOpcodes)
{
    ACPI_GENERIC_OP         *Op = Origin;
    ACPI_GENERIC_OP         *arg;
    ACPI_GENERIC_OP         *depth;
    UINT32                  DepthCount = 0;
    UINT32                  LastDepth = 0;
    UINT32                  i;
    UINT32                  j;


    if (Op)
    {
        while (Op)
        {
			/* indentation */

			DepthCount = 0;
            if (!opt_verbose)
            {
                DepthCount++;
            }

            /* Determine the nesting depth of this argument */

			for (depth = Op->Parent; depth; depth = depth->Parent)
			{
				arg = PsGetArg (depth, 0);
				while (arg && arg != Origin)
				{
					arg = arg->Next;
				}

				if (arg)
				{
					break;
				}

				DepthCount++;
			}
            

            /* Open a new block if we are nested further than last time */

			if (DepthCount > LastDepth)
			{
				VERBOSE_PRINT ((DB_NO_OP_INFO, LastDepth));
				for (i = 0; i < LastDepth; i++)
				{
					OsdPrintf (INDENT_STRING);
				}

                if (DbBlockType (Op) == BLOCK_PAREN)
				    OsdPrintf ("(\n");
                else
				    OsdPrintf ("{\n");
			}

            /* Close a block if we are nested less than last time */

			else if (DepthCount < LastDepth)
			{
				for (j = 0; j < (LastDepth - DepthCount); j++)
				{
                    VERBOSE_PRINT ((DB_NO_OP_INFO, LastDepth - j));
					for (i = 0; i < (LastDepth - j - 1); i++)
					{
						OsdPrintf (INDENT_STRING);
					}

                    if (DbBlockType (Op) == BLOCK_PAREN)
					    OsdPrintf (")\n");
                    else
					    OsdPrintf ("}\n");
				}
			}

            /* In verbose mode, print the AML offset, opcode and depth count */

			VERBOSE_PRINT ((DB_FULL_OP_INFO, (unsigned) Op->AmlOffset, Op->Opcode, DepthCount));


            /* Indent the output according to the depth count */

            for (i = 0; i < DepthCount; i++)
            {
                OsdPrintf (INDENT_STRING);
            }


            /* Now print the opcode */

            DbDisplayOpcode (Op);

            /* Resolve a name reference */

            if ((Op->Opcode == AML_NAMEPATH_OP && Op->Value.Name)  &&
                (Op->Parent) &&
                (opt_verbose))
			{
                PsDisplayObjectPathname (Op);
            }

            OsdPrintf ("\n");

            /* Get the next node in the tree */

            Op = PsGetDepthNext (Origin, Op);
            LastDepth = DepthCount;

            NumOpcodes--;
            if (!NumOpcodes)
            {
                Op = NULL;
            }
        }

        /* Close the last block(s) */

        DepthCount = LastDepth -1;
        for (i = 0; i < LastDepth; i++)
        {
			VERBOSE_PRINT ((DB_NO_OP_INFO, LastDepth - i));
			for (j = 0; j < DepthCount; j++)
			{
				OsdPrintf (INDENT_STRING);
			}
			OsdPrintf ("}\n");
            DepthCount--;
        }

    }

    else
    {
        DbDisplayOpcode (Op);
    }
}


/*******************************************************************************
 *
 * FUNCTION:    DbDisplayNamestring
 *
 * PARAMETERS:  Name                - ACPI Name string to store
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display namestring. Handles prefix characters
 *
 ******************************************************************************/

void
DbDisplayNamestring (
    UINT8                   *Name)
{
    UINT32                  SegCount;
    BOOLEAN                 DoDot = FALSE;


    if (!Name)
    {
        OsdPrintf ("<NULL NAME PTR>");
        return;
    }

    if (PsIsPrefixChar (GET8 (Name)))
    {
        /* append prefix character */

        OsdPrintf ("%1c", GET8 (Name));
        Name++;
    }

    switch (GET8 (Name))
    {
    case AML_DualNamePrefix:
        SegCount = 2;
        Name++;
        break;

    case AML_MultiNamePrefixOp:
        SegCount = (INT32) GET8 (Name + 1);
        Name += 2;
        break;

    default:
        SegCount = 1;
        break;
    }

    while (SegCount--)
    {
        /* append Name segment */

        if (DoDot)
        {
            /* append dot */

            OsdPrintf (".");
        }

        OsdPrintf ("%4.4s", Name);
        DoDot = TRUE;

        Name += 4;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    DbDisplayPath
 *
 * PARAMETERS:  Op                  - Named Op whose path is to be constructed
 *
 * RETURN:      None
 *
 * DESCRIPTION: Walk backwards from current scope and display the name
 *              of each previous level of scope up to the root scope
 *              (like "pwd" does with file systems)
 *
 ******************************************************************************/

void
DbDisplayPath (
    ACPI_GENERIC_OP         *Op)
{
    ACPI_GENERIC_OP         *Prev;
    ACPI_GENERIC_OP         *Search;
    UINT32                  Name;
    BOOLEAN                 DoDot = FALSE;
    ACPI_GENERIC_OP         *NamePath;


    /* We are only interested in named objects */

    if (!PsIsNamedObjectOp (Op->Opcode))
    {
        return;
    }


    if (PsIsCreateFieldOp (Op->Opcode))
    {
        /* Field creation - check for a fully qualified namepath */

        if (Op->Opcode == AML_CreateFieldOp)
        {
            NamePath = PsGetArg (Op, 3);
        }
        else
        {
            NamePath = PsGetArg (Op, 2);
        }

        if ((NamePath) &&
            (NamePath->Value.String) &&
            (NamePath->Value.String[0] == '\\'))
        {
            DbDisplayNamestring ((UINT8 *) NamePath->Value.String);
            return;
        }
    }

    Prev = NULL;            /* Start with root object */

    while (Prev != Op)
    {
        /* Search upwards in the tree to find scope with "prev" as its parent */

        Search = Op;
        for (; ;)
        {
            if (Search->Parent == Prev)
            {
                break;
            }

            /* Go up one level */

            Search = Search->Parent;
        }
        
        if (Prev && !PsIsFieldOp (Search->Opcode))
        {
            /* below root scope, append scope name */

            if (DoDot)
            {
                /* append dot */

                OsdPrintf (".");
            }

            if (PsIsCreateFieldOp (Search->Opcode))
            {
                if (Op->Opcode == AML_CreateFieldOp)
                {
                    NamePath = PsGetArg (Op, 3);
                }
                else
                {
                    NamePath = PsGetArg (Op, 2);
                }
                
                if ((NamePath) &&
                    (NamePath->Value.String))
                {
                    OsdPrintf ("%4.4s", NamePath->Value.String);
                }
            }

            else
            {
                Name = PsGetName (Search);
                OsdPrintf ("%4.4s", &Name);
            }
            
            DoDot = TRUE;
        }
        
        Prev = Search;
    }
}



/*******************************************************************************
 *
 * FUNCTION:    DbDisplayOpcode
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

void
DbDisplayOpcode (
    ACPI_GENERIC_OP         *Op)
{
    UINT8                   *ByteData;
    UINT32                  ByteCount;
    UINT32                  i;
    ACPI_OP_INFO            *Opc = NULL;
    UINT32                  Name;



    if (!Op)
    {
        OsdPrintf ("<NULL OP PTR>");
    }


    /* op and arguments */

    switch (Op->Opcode)
    {

    case AML_ByteOp:

		if (opt_verbose)
        {
			OsdPrintf ("(UINT8)  0x%2.2X", Op->Value.Integer & 0xff);
        }
        
        else
        {
            OsdPrintf ("0x%2.2X", Op->Value.Integer & 0xff);
        }

        break;


    case AML_WordOp:

		if (opt_verbose)
        {
			OsdPrintf ("(UINT16) 0x%4.4X", Op->Value.Integer & 0xffff);
        }
        
        else
        {
            OsdPrintf ("0x%4.4X", Op->Value.Integer & 0xffff);
        }
        
        break;


    case AML_DWordOp:

		if (opt_verbose)
        {
            OsdPrintf ("(UINT32) 0x%8.8X", Op->Value.Integer);
        }
        
        else
        {
            OsdPrintf ("0x%8.8X", Op->Value.Integer);
        }
        
        break;


    case AML_StringOp:

        if (Op->Value.String)
        {
            OsdPrintf ("\"%s\"", Op->Value.String);
        }
        
        else
        {
            OsdPrintf ("<\"NULL STRING PTR\">");
        }
        
        break;


    case AML_STATICSTRING_OP:

        if (Op->Value.String)
        {
            OsdPrintf ("\"%s\"", Op->Value.String);
        }
        
        else
        {
            OsdPrintf ("\"<NULL STATIC STRING PTR>\"");
        }
        
        break;


    case AML_NAMEPATH_OP:

        DbDisplayNamestring (Op->Value.Buffer);
        break;


    case AML_NAMEDFIELD_OP:

        OsdPrintf ("NamedField    (Length 0x%8.8X)  ", Op->Value.Integer);
        break;


    case AML_RESERVEDFIELD_OP:

        OsdPrintf ("ReservedField (Length 0x%8.8X)  ", Op->Value.Integer);
        break;


    case AML_ACCESSFIELD_OP:

        OsdPrintf ("AccessField   (Length 0x%8.8X)  ", Op->Value.Integer);
        break;


    case AML_BYTELIST_OP:

        if (opt_verbose)
        {
            OsdPrintf ("ByteList      (Length 0x%8.8X)  ", Op->Value.Integer);
        }

        else
        {
            OsdPrintf ("0x%2.2X", Op->Value.Integer);

            ByteCount = Op->Value.Integer;
            ByteData = ((ACPI_BYTELIST_OP *) Op)->Data;

            for (i = 0; i < ByteCount; i++)
            {
                OsdPrintf (", 0x%2.2X", ByteData[i]);
            }
        }

        break;


    default:

        /* Just get the opcode name and print it */

        Opc = PsGetOpcodeInfo (Op->Opcode);
        if (Opc)
        {
            DEBUG_ONLY_MEMBERS ((OsdPrintf ("%s", Opc->Name)));
        }

        else
        {
            OsdPrintf ("<Opcode 0x%04x>", Op->Opcode);
        }

        break;
    }


    if (!Opc)
    {
        /* If there is another element in the list, add a comma */

        if (Op->Next)
        {
			OsdPrintf (",");
        }
    }


    /*
     * If this is a named opcode, print the associated name value
     */

    if (Op && PsIsNamedOp (Op->Opcode))
    {
        Name = PsGetName (Op);
        OsdPrintf (" %4.4s", &Name);

		if (opt_verbose)
		{
			OsdPrintf ("  (Path \\");
			DbDisplayPath (Op);
            OsdPrintf (")");
		}    
    }
}


#endif  /* ACPI_DEBUG */

