
/******************************************************************************
 *
 * Module Name: aslcodegen - AML code generation
 *              $Revision: 1.6 $
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
CgAmlWriteWalk (
    ASL_PARSE_NODE              *Node,
    UINT32                      Level,
    void                        *Context)
{



    UtPrintFormattedName (Node->ParseOpcode, Level);

	if (Node->ParseOpcode == NAMESEG ||
		Node->ParseOpcode == NAMESTRING)
	{
		DbgPrint ("%4.4s      ", Node->Value.String);
	}

	else
	{
		DbgPrint ("          ");
	}

    DbgPrint ("Value-%08X ParseOp-0x%04X AmlOp-%04X OpLen-%01X PByts-%01X Len-%04X SubLen-%04X ParentSubLen-%04X Node-%08X Chld-%08X Paren-%08X\n",
                Node->Value.Integer32,
                Node->ParseOpcode,
                Node->AmlOpcode,
                Node->AmlOpcodeLength,
                Node->AmlPkgLenBytes,
                Node->AmlLength,
                Node->AmlSubtreeLength,
                Node->Parent ? Node->Parent->AmlSubtreeLength : 0,
				Node,
				Node->Child,
				Node->Parent);

    CgWriteNode (Node);
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
CgWriteAmlOpcode (
    ASL_PARSE_NODE              *Node)
{
    union {
        UINT16                      Opcode;
        UINT8                       OpcodeBytes[2];
    } Aml;
    union {
        UINT32                      Len;
        UINT8                       LenBytes[4];
    } PkgLen;

    UINT8                       PkgLenFirstByte;
    UINT32                      i;



    /* We expect some DEFAULT_ARGs, just ignore them */

    if (Node->ParseOpcode == DEFAULT_ARG)
    {
        return;
    }


    switch (Node->AmlOpcode)
    {
    case AML_UNASSIGNED_OPCODE:

        /* These opcodes should not get here */

        printf ("Found a node with an unassigned AML opcode\n");
        fprintf (stderr, "Found a node with an unassigned AML opcode\n");
        return;
        break;

    case AML_RESERVEDFIELD_OP:

        /* Special opcodes for within a field definition */

        Aml.Opcode = 0x00;  
        break;

    case AML_ACCESSFIELD_OP:

        Aml.Opcode = 0x01;
        break;

    default:
        Aml.Opcode = Node->AmlOpcode;
        break;
    }


    switch (Aml.Opcode)
    {
    case AML_PACKAGE_LENGTH:

        /* Value is the length to be encoded (Used in field definitions) */

        PkgLen.Len = Node->Value.Integer32;
        break;

    default:

        /* Check for two-byte opcode */

        if (Aml.Opcode > 0x00FF)
        {
            /* Write the high byte first */

            fwrite (&Aml.OpcodeBytes[1], 1, 1, Gbl_OutputAmlFile);
        }

        fwrite (&Aml.OpcodeBytes[0], 1, 1, Gbl_OutputAmlFile);

        /* Subtreelength doesn't include length of package length bytes */

        PkgLen.Len = Node->AmlSubtreeLength + Node->AmlPkgLenBytes;
        break;
    }


    /* Does this opcode have an associated "PackageLength" field? */

    if (Node->Flags & NODE_AML_PACKAGE)
    {
        if (Node->AmlPkgLenBytes == 1)
        {
            /* Simplest case -- no bytes to follow, just write the count */

            fwrite (&PkgLen.LenBytes[0], 1, 1, Gbl_OutputAmlFile);
        }

        else
        {
            /* 
             * Encode the "bytes to follow" in the first byte, top two bits.
             * The low-order nybble of the length is in the bottom 4 bits
             */

            PkgLenFirstByte = ((Node->AmlPkgLenBytes - 1) << 6) |
                                (PkgLen.LenBytes[0] & 0x0F);

            fwrite (&PkgLenFirstByte, 1, 1, Gbl_OutputAmlFile);

            /* Shift the length over by the 4 bits we just stuffed in the first byte */

            PkgLen.Len >>= 4;

            /* Now we can write the remaining bytes - either 1, 2, or 3 bytes */

            for (i = 0; i < (UINT32) (Node->AmlPkgLenBytes - 1); i++)
            {
                fwrite (&PkgLen.LenBytes[i], 1, 1, Gbl_OutputAmlFile);
            }
        }   
    }

    switch (Aml.Opcode)
    {
    case AML_BYTE_OP:
        fwrite (&Node->Value.Integer8, 1, 1, Gbl_OutputAmlFile);
        break;

    case AML_WORD_OP:
        fwrite (&Node->Value.Integer16, 2, 1, Gbl_OutputAmlFile);
       break;

    case AML_DWORD_OP:
        fwrite (&Node->Value.Integer32, 4, 1, Gbl_OutputAmlFile);
        break;

    case AML_QWORD_OP:
        fwrite (&Node->Value.Integer64, 8, 1, Gbl_OutputAmlFile);
        break;

    case AML_STRING_OP:
        fwrite (Node->Value.String, Node->AmlLength, 1, Gbl_OutputAmlFile);
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
CgWriteTableHeader (
    ASL_PARSE_NODE              *Node)
{
    ASL_PARSE_NODE              *Child;
    

    /* AML filename */

    Child = Node->Child;


    /* Signature */

    Child = Child->Peer;
    strncpy (TableHeader.Signature, Child->Value.String, 4);

    /* Revision */

    Child = Child->Peer;
    TableHeader.Revision = Child->Value.Integer8;

    /* OEMID */

    Child = Child->Peer;
    strncpy (TableHeader.OemId, Child->Value.String, 6);

    /* OEM TableID */

    Child = Child->Peer;
    strncpy (TableHeader.OemTableId, Child->Value.String, 8);

    /* OEM Revision */

    Child = Child->Peer;
    TableHeader.OemRevision = Child->Value.Integer32;

    /* Compiler ID */

    strncpy (TableHeader.AslCompilerId, "iASL", 4);

    /* Compiler version */

    TableHeader.AslCompilerRevision = 0x22221111;


    fwrite (&TableHeader, sizeof (ACPI_TABLE_HEADER), 1, Gbl_OutputAmlFile);
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
CgCloseTable (void)
{
    signed char         Sum;
    UINT8               FileByte;


    TableHeader.Length = TableLength;
    TableHeader.Checksum = 0;

    /* Write the header at the start of the file */

    fseek (Gbl_OutputAmlFile, 0, SEEK_SET);
    fwrite (&TableHeader, sizeof (ACPI_TABLE_HEADER), 1, Gbl_OutputAmlFile);

    /* Calculate the checksum over the entire file */

    fseek (Gbl_OutputAmlFile, 0, SEEK_SET);

    Sum = 0;
    while (fread (&FileByte, 1, 1, Gbl_OutputAmlFile))
    {
        Sum += FileByte;
    }

    /* Re-write the table header with the checksum */

    TableHeader.Checksum = (0 - Sum);

    fseek (Gbl_OutputAmlFile, 0, SEEK_SET);
    fwrite (&TableHeader, sizeof (ACPI_TABLE_HEADER), 1, Gbl_OutputAmlFile);
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
CgWriteNode (
    ASL_PARSE_NODE          *Node)
{

    /* TEMP FIX: always check for DEFAULT_ARG */

    if (Node->ParseOpcode == DEFAULT_ARG)
    {
        return;
    }

    if ((Node->AmlOpcode == AML_RAW_DATA_BYTE) ||
        (Node->AmlOpcode == AML_RAW_DATA_WORD) ||
        (Node->AmlOpcode == AML_RAW_DATA_DWORD) ||
        (Node->AmlOpcode == AML_RAW_DATA_QWORD))
    {
        fwrite (&Node->Value.Integer, Node->AmlLength, 1, Gbl_OutputAmlFile);
        return;
    }

    if (Node->AmlOpcode == AML_RAW_DATA_BUFFER)
    {
        fwrite (Node->Value.Pointer, Node->AmlLength, 1, Gbl_OutputAmlFile);
        return;
    }


    switch (Node->ParseOpcode)
    {
    case DEFAULT_ARG:
        break;

    case DEFINITIONBLOCK:
        CgWriteTableHeader (Node);
        break;

    case NAMESEG:
    case NAMESTRING:
        fwrite (Node->Value.String, Node->AmlLength, 1, Gbl_OutputAmlFile);
        break;

    default:
        CgWriteAmlOpcode (Node);
        break;
    }
}







