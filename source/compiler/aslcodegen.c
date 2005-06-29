
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "AslCompiler.y.h"
#include "AslCompiler.h"
#include "acpi.h"
#include "amlcode.h"



extern const char * const       yytname[];





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
CgOpenOutputFile (
    char                    *InputFilename)
{
    char                    *Position;


    OutputFilename = calloc (strlen (InputFilename) + 4, 1);

    Position = strrchr (InputFilename, '.');
    if (Position)
    {
        *Position = 0;
    }

    strcpy (OutputFilename, InputFilename);
    strcat (OutputFilename, ".aml");

    /* We must open the file in binary mode! */

	AmlFile = fopen (OutputFilename, "w+b");
    if (!AmlFile)
    {
        return AE_ERROR;
    }

    return AE_OK;
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
CgGenerateOutput(
    char                    *InputFilename)
{


    if (!RootNode)
    {
        return;
    }

    CgOpenOutputFile (InputFilename);


    DbgPrint ("\nGenerating AML opcodes\n\n");
    TgWalkParseTree (ASL_WALK_VISIT_UPWARD, CgAmlOpcodeWalk, NULL);

    DbgPrint ("\nGenerating Package lengths\n\n");
    TgWalkParseTree (ASL_WALK_VISIT_UPWARD, CgAmlPackageLengthWalk, NULL);


    DbgPrint ("\nWriting AML\n\n");
    TgWalkParseTree (ASL_WALK_VISIT_DOWNWARD, CgAmlWriteWalk, NULL);


    CgCloseTable ();
    fclose (AmlFile);
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

    default:
        Aml.Opcode = Node->AmlOpcode;
        break;
    }


    switch (Aml.Opcode)
    {
    case AML_PACKAGE_LENGTH:

        /* Value is the length to be encoded (Used in field definitions) */

        PkgLen.Len = (UINT32) Node->Value;
        break;

    default:

        /* Check for two-byte opcode */

        if (Aml.Opcode > 0x00FF)
        {
            /* Write the high byte first */

            fwrite (&Aml.OpcodeBytes[1], 1, 1, AmlFile);
        }

        fwrite (&Aml.OpcodeBytes[0], 1, 1, AmlFile);

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

            fwrite (&PkgLen.LenBytes[0], 1, 1, AmlFile);
        }

        else
        {
            /* 
             * Encode the "bytes to follow" in the first byte, top two bits.
             * The low-order nybble of the length is in the bottom 4 bits
             */

            PkgLenFirstByte = ((Node->AmlPkgLenBytes - 1) << 6) |
                                (PkgLen.LenBytes[0] & 0x0F);

            fwrite (&PkgLenFirstByte, 1, 1, AmlFile);

            /* Shift the length over by the 4 bits we just stuffed in the first byte */

            PkgLen.Len >>= 4;

            /* Now we can write the remaining bytes - either 1, 2, or 3 bytes */

            for (i = 0; i < (UINT32) (Node->AmlPkgLenBytes - 1); i++)
            {
                fwrite (&PkgLen.LenBytes[i], 1, 1, AmlFile);
            }
        }   
    }

    switch (Aml.Opcode)
    {
    case AML_BYTE_OP:
        fwrite (&Node->Value, 1, 1, AmlFile);
        break;

    case AML_WORD_OP:
        fwrite (&Node->Value, 2, 1, AmlFile);
       break;

    case AML_DWORD_OP:
        fwrite (&Node->Value, 4, 1, AmlFile);
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
CgWriteTableHeader (
    ASL_PARSE_NODE              *Node)
{
    ASL_PARSE_NODE              *Child;
    

    /* AML filename */

    Child = Node->Child;


    /* Signature */

    Child = Child->Peer;
    strncpy (TableHeader.Signature, Child->Value, 4);

    /* Revision */

    Child = Child->Peer;
    TableHeader.Revision = (UINT8) Child->Value;

    /* OEMID */

    Child = Child->Peer;
    strncpy (TableHeader.OemId, Child->Value, 6);

    /* OEM TableID */

    Child = Child->Peer;
    strncpy (TableHeader.OemTableId, Child->Value, 8);

    /* OEM Revision */

    Child = Child->Peer;
    TableHeader.OemRevision = (UINT32) Child->Value;

    /* Compiler ID */

    strncpy (TableHeader.AslCompilerId, "iASL", 4);

    /* Compiler version */

    TableHeader.AslCompilerRevision = 0x00020001;


    fwrite (&TableHeader, sizeof (ACPI_TABLE_HEADER), 1, AmlFile);
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
    TableHeader.Length = TableLength;

    fseek (AmlFile, 0, SEEK_SET);
    fwrite (&TableHeader, sizeof (ACPI_TABLE_HEADER), 1, AmlFile);

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
    ASL_PARSE_NODE              *Node)
{


    if (Node->AmlOpcode == AML_RAW_DATA_BYTE)
    {
        fwrite (&Node->Value, 1, 1, AmlFile);
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
    case STRING_LITERAL:
        fwrite (Node->Value, Node->AmlLength, 1, AmlFile);
        break;

    default:
        CgWriteAmlOpcode (Node);
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


#define TEXT_OFFSET 10


void
CgPrintFormattedName (
    UINT16                      ParseOpcode,
    UINT32                      Level)
{
    UINT32                      i;

    
    for (i = 0; i < Level; i++)
    {
        DbgPrint ("    ");
    }


    DbgPrint ("%-16.16s", yytname[ParseOpcode-255]);
        
    
    if (Level < TEXT_OFFSET)
    {
        for (i = 0; i < (TEXT_OFFSET - Level); i++)
        {
            DbgPrint ("    ");
        }
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
CgAmlOpcodeWalk (
    ASL_PARSE_NODE              *Node,
    UINT32                      Level,
    void                        *Context)
{

    CgGenerateAmlOpcode (Node);
    CgGenerateAmlOperands (Node);
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



    CgPrintFormattedName (Node->ParseOpcode, Level);

    DbgPrint ("Value %08X ParseOp 0x%04X AmlOp %04X OpLen %01X PByts %01X Len %04X SubLen %04X ParentSubLen %04X\n",
                Node->Value,
                Node->ParseOpcode,
                Node->AmlOpcode,
                Node->AmlOpcodeLength,
                Node->AmlPkgLenBytes,
                Node->AmlLength,
                Node->AmlSubtreeLength,
                Node->Parent ? Node->Parent->AmlSubtreeLength : 0);

    CgWriteNode (Node);
}








