#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "AslCompiler.y.h"
#include "AslCompiler.h"
#include "acpi.h"
#include "amlcode.h"


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

void
CgSetOptimalIntegerSize (
    ASL_PARSE_NODE          *Node)
{

    if (Node->Value.Integer <= 0xFF)
    {
        Node->AmlOpcode = AML_BYTE_OP;
    }
    else if (Node->Value.Integer <= 0xFFFF)
    {
        Node->AmlOpcode = AML_WORD_OP;
    }
    else
    {
        Node->AmlOpcode = AML_DWORD_OP;
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
CgDoMethod (
    ASL_PARSE_NODE              *Node)
{
    ASL_PARSE_NODE              *Next;

    /* Optional arguments for this opcode with defaults */
    
    UINT8                       NumArgs = 0;
    UINT8                       Serialized = 0;
    UINT8                       Concurrency = 0;
    UINT8                       MethodFlags;



    /* Opcode and package length first */
    /* Method name */

    Next = Node->Child;

    /* Num args */

    Next = Next->Peer;
    if (Next->ParseOpcode != DEFAULT_ARG)
    {
        NumArgs = Next->Value.Integer8;
        Next->ParseOpcode = DEFAULT_ARG;
    }

    /* Serialized Flag */

    Next = Next->Peer;
    if (Next->ParseOpcode != DEFAULT_ARG)
    {
        Serialized = Next->Value.Integer8;
        Next->ParseOpcode = DEFAULT_ARG;
    }

    /* Concurrency Flag */

    Next = Next->Peer;
    if (Next->ParseOpcode != DEFAULT_ARG)
    {
        Concurrency = Next->Value.Integer8;
    }

    /* Put the bits in their proper places */

    MethodFlags = (NumArgs & 0x7) | ((Serialized & 0x1) << 3) | ((Concurrency & 0xF) << 4); 

    /* Use the last node for the combined flags byte */

    Next->Value.Integer = MethodFlags;
    Next->AmlOpcode = AML_RAW_DATA_BYTE;
    Next->AmlLength = 1;
    Next->ParseOpcode = RAW_DATA;
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
CgDoFieldCommon (
    ASL_PARSE_NODE              *Node)
{
    ASL_PARSE_NODE              *Next;
    ASL_PARSE_NODE              *PkgLengthNode;
    UINT32                      CurrentBitOffset;
    UINT32                      NewBitOffset;
    UINT8                       AccessType;
    UINT8                       LockRule;
    UINT8                       UpdateRule;
    UINT8                       FieldFlags;


    /* AccessType -- not optional, so no need to check for DEFAULT_ARG */

    AccessType = Node->Value.Integer8;
    Node->ParseOpcode = DEFAULT_ARG;

    /* LockRule -- not optional, so no need to check for DEFAULT_ARG */

    Next = Node->Peer;
    LockRule = Next->Value.Integer8;
    Next->ParseOpcode = DEFAULT_ARG;

    /* UpdateRule -- not optional, so no need to check for DEFAULT_ARG */

    Next = Next->Peer;
    UpdateRule = Next->Value.Integer8;

    /* Generate the flags byte */

    FieldFlags = (AccessType & 0x0F) | ((LockRule & 0x01) << 4) | ((UpdateRule & 0x03) << 5);

    /* Use the previous node to be the FieldFlags node */

    /* Set the node to RAW_DATA */

    Next->Value.Integer = FieldFlags;
    Next->AmlOpcode = AML_RAW_DATA_BYTE;
    Next->AmlLength = 1;
    Next->ParseOpcode = RAW_DATA;

    /*  Process the FieldUnitList */

    Next = Next->Peer;
    CurrentBitOffset = 0;

    while (Next)
    {
        switch (Next->ParseOpcode)
        {
        case ACCESSAS:
            break;

        case OFFSET:
            PkgLengthNode = Next->Child;
            NewBitOffset = PkgLengthNode->Value.Integer * 8;
            if (NewBitOffset < CurrentBitOffset)
            {
                DbgPrint ("Offset less than current offset\n");
            }
    
            PkgLengthNode->Value.Integer = NewBitOffset - CurrentBitOffset;
            CurrentBitOffset = NewBitOffset;
            break;

        case NAMESEG:
        case RESERVED_BYTES:
            PkgLengthNode = Next->Child;
            NewBitOffset = PkgLengthNode->Value.Integer;
            CurrentBitOffset += NewBitOffset;
            break;

        }
        Next = Next->Peer;
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
CgDoField (
    ASL_PARSE_NODE              *Node)
{
    ASL_PARSE_NODE              *Next;


    /* Opcode is parent node */
    /* First child is field name */

    Next = Node->Child;

    /* Second child is the AccessType */

    CgDoFieldCommon (Next->Peer);

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
CgDoIndexField (
    ASL_PARSE_NODE              *Node)
{
    ASL_PARSE_NODE              *Next;



    /* Opcode is parent node */
    /* First child is the index name */

    Next = Node->Child;

    /* Second child is the data name */

    Next = Next->Peer;

    /* Third child is the AccessType */

    CgDoFieldCommon (Next->Peer);

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
CgDoBankField (
    ASL_PARSE_NODE              *Node)
{
    ASL_PARSE_NODE              *Next;



    /* Opcode is parent node */
    /* First child is the region name */

    Next = Node->Child;

    /* Second child is the bank name */

    Next = Next->Peer;

    /* Third child is the bank value */

    Next = Next->Peer;

    /* Fourth child is the AccessType */

    CgDoFieldCommon (Next->Peer);

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
CgDoBuffer (
    ASL_PARSE_NODE              *Node)
{
    ASL_PARSE_NODE              *InitializerNode;
    ASL_PARSE_NODE              *BufferLengthNode;

    /* Optional arguments for this opcode with defaults */
    
    UINT32                      BufferLength = 0;


    /* Opcode and package length first */
    /* Buffer Length is next, followed by the initializer list */

    BufferLengthNode = Node->Child;
    InitializerNode = BufferLengthNode->Peer;

    /*
     * We always count the number of items in the initializer list, because if
     * it is larger than the buffer length, we will define the buffer size
     * to be the size of the initializer list (Per ACPI Spec)
     */
    if (InitializerNode->ParseOpcode != DEFAULT_ARG)
    {
        /* The peer list contains the byte list (if any...) */

        while (InitializerNode)
        {
            /* For buffers, this is a list of raw bytes */

            InitializerNode->AmlOpcode = AML_RAW_DATA_BYTE;
            InitializerNode->AmlLength = 1;
            InitializerNode->ParseOpcode = RAW_DATA;

            BufferLength++;
            InitializerNode = InitializerNode->Peer;
        }
    }


    /* Check if initializer list is longer than the buffer length */

    if (BufferLengthNode->ParseOpcode == INTEGER)
    {
        if (BufferLengthNode->Value.Integer > BufferLength)
        {
            BufferLength = BufferLengthNode->Value.Integer;
        }
    }


    if (!BufferLength)
    {
        /* No length AND no items -- issue a warning */

        AslWarning (ASL_WARNING_BUFFER_LENGTH);

        /* But go ahead and put the buffer length of zero into the AML */
    }


    /* 
     * Just set the buffer size node to be the buffer length, regardless
     * of whether it was previously an integer or a default_arg placeholder
     */

    BufferLengthNode->ParseOpcode = INTEGER;
    BufferLengthNode->AmlOpcode = AML_DWORD_OP;
    BufferLengthNode->Value.Integer = BufferLength;

    CgSetOptimalIntegerSize (BufferLengthNode);

    /* Remaining nodes are handled via the tree walk */
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
CgDoPackage (
    ASL_PARSE_NODE              *Node)
{
    ASL_PARSE_NODE              *InitializerNode;
    ASL_PARSE_NODE              *PackageLengthNode;

    /* Optional arguments for this opcode with defaults */
    
    UINT32                      PackageLength = 0;


    /* Opcode and package length first */
    /* Buffer Length is next, followed by the initializer list */

    PackageLengthNode = Node->Child;
    InitializerNode = PackageLengthNode->Peer;

    /*
     * We always count the number of items in the initializer list, because if
     * it is larger than the buffer length, we will define the buffer size
     * to be the size of the initializer list (Per ACPI Spec)
     */
    if (InitializerNode->ParseOpcode != DEFAULT_ARG)
    {
        /* The peer list contains the byte list (if any...) */

        while (InitializerNode)
        {
            PackageLength++;
            InitializerNode = InitializerNode->Peer;
        }
    }


    /* Check if initializer list is longer than the buffer length */

    if (PackageLengthNode->ParseOpcode == INTEGER)
    {
        if (PackageLengthNode->Value.Integer > PackageLength)
        {
            PackageLength = PackageLengthNode->Value.Integer;
        }
    }


    if (!PackageLength)
    {
        /* No length AND no items -- issue a warning */

        AslWarning (ASL_WARNING_PACKAGE_LENGTH);

        /* But go ahead and put the buffer length of zero into the AML */
    }


    /* 
     * Just set the buffer size node to be the buffer length, regardless
     * of whether it was previously an integer or a default_arg placeholder
     */

    PackageLengthNode->AmlOpcode = AML_RAW_DATA_BYTE;
    PackageLengthNode->AmlLength = 1;
    PackageLengthNode->ParseOpcode = RAW_DATA;
    PackageLengthNode->Value.Integer = PackageLength;

    /* Remaining nodes are handled via the tree walk */
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
CgDoOffset (
    ASL_PARSE_NODE              *Node)
{
    ASL_PARSE_NODE              *InitializerNode;

    /* Entire proc unnecessarY? */

    Node->AmlOpcodeLength = 1;
    InitializerNode = Node->Child;
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
CgDoAccessAs (
    ASL_PARSE_NODE              *Node)
{
    ASL_PARSE_NODE              *Next;


    Node->AmlOpcodeLength = 1;
    Next = Node->Child;

    /* First child is the access type */

    Next->AmlOpcode = AML_RAW_DATA_BYTE;
    Next->ParseOpcode = RAW_DATA;
    
    /* Second child is the optional access attribute */

    Next = Next->Peer;
    if (Next->ParseOpcode == DEFAULT_ARG)
    {
        Next->Value.Integer = 0;
    }
    Next->AmlOpcode = AML_RAW_DATA_BYTE;
    Next->ParseOpcode = RAW_DATA;
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
        Node->AmlPkgLenBytes = CgGetPackageLenByteCount (Node->Value.Integer);
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
CgDoDefinitionBlock (
    ASL_PARSE_NODE              *Node)
{
    ASL_PARSE_NODE              *Child;
    


    /* 
     * These nodes get stuffed into the table header.  They are special
     * cased when the table is written to the output file.
     * 
     * Mark all of these nodes as non-usable so they won't get output
     * as AML opcodes!
     */


    /* AML filename */

    Child = Node->Child;
    Child->ParseOpcode = DEFAULT_ARG;

    /* Signature */

    Child = Child->Peer;
    Child->ParseOpcode = DEFAULT_ARG;

    /* Revision */

    Child = Child->Peer;
    Child->ParseOpcode = DEFAULT_ARG;

    /* OEMID */

    Child = Child->Peer;
    Child->ParseOpcode = DEFAULT_ARG;

    /* OEM TableID */

    Child = Child->Peer;
    Child->ParseOpcode = DEFAULT_ARG;

    /* OEM Revision */

    Child = Child->Peer;
    Child->ParseOpcode = DEFAULT_ARG;
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
CgGenerateAmlOperands (
    ASL_PARSE_NODE              *Node)
{


    if (Node->AmlOpcode == AML_RAW_DATA_BYTE)
    {
        return;
    }


    switch (Node->ParseOpcode)
    {
    case DEFINITIONBLOCK:
        CgDoDefinitionBlock (Node);
        break;

    case METHOD:
        CgDoMethod (Node);
        break;

    case FIELD:
        CgDoField (Node);
        break;

    case INDEXFIELD:
        CgDoIndexField (Node);
        break;

    case BANKFIELD:
        CgDoBankField (Node);
        break;

    case BUFFER:
        CgDoBuffer (Node);
        break;

    case PACKAGE:
        CgDoPackage (Node);
        break;

    case NAMESEG:
    case NAMESTRING:
    case STRING_LITERAL:
        break;

    default:
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
CgGenerateAmlOpcode (
    ASL_PARSE_NODE          *Node)
{

    UINT16                  Index = Node->ParseOpcode;


    Index = Node->ParseOpcode - ASL_PARSE_OPCODE_BASE;


    Node->AmlOpcode = AslKeywordMapping[Index].AmlOpcode;
    Node->Flags |= AslKeywordMapping[Index].Flags;

    if (!Node->Value.Integer)
    {
        Node->Value.Integer = AslKeywordMapping[Index].Value;
    }


    /* Special handling for some opcodes */

    switch (Node->ParseOpcode)
    {
    case INTEGER:
        /*
         * Set the opcode based on the size of the integer
         */
        CgSetOptimalIntegerSize (Node);
        break;

    case OFFSET:
        CgDoOffset (Node);
        break;

    case ACCESSAS:
        CgDoAccessAs (Node);
        break;

    case EISAID:
        /* TBD: implement real code */
        /* Free string */
        Node->Value.Integer = 0x12345678;
        break;
    }

    return;
}



/* 
 * TBD:
 * AccessAttrib
 * AccessType
 * AMlop for DMA?
 * ObjectType keywords
 * Register
 */

/*******************************************************************************
 *
 * DATA STRUCTURE:  AslKeywordMapping
 *
 * DESCRIPTION:     Maps the ParseOpcode to the actual AML opcode.  The parse
 *                  opcodes are generated from Bison, and this table must
 *                  track any additions to them.
 *
 * Each entry in the table contains the following items:
 *
 * AML opcode   - Opcode that is written to the AML file
 * Value        - Value of the object to be written (if applicable)
 * Flags        - 1) Whether this opcode opens an AML "package".
 *
 ******************************************************************************/

ASL_MAPPING_ENTRY AslKeywordMapping [] = 
{

/* ACCESSAS */                  OP_TABLE_ENTRY (AML_ACCESSFIELD_OP,                0,                  0),
/* ACCESSATTRIB_BLOCK */        OP_TABLE_ENTRY (AML_BYTE_OP,                ACCESS_BLOCK_ACC,   0),
/* ACCESSATTRIB_BYTE */         OP_TABLE_ENTRY (AML_BYTE_OP,                ACCESS_BYTE_ACC,    0),
/* ACCESSATTRIB_CALL */         OP_TABLE_ENTRY (AML_BYTE_OP,                ACCESS_BYTE_ACC,    0),
/* ACCESSATTRIB_QUICK */        OP_TABLE_ENTRY (AML_BYTE_OP,                ACCESS_BYTE_ACC,    0),
/* ACCESSATTRIB_SND_RCV */      OP_TABLE_ENTRY (AML_BYTE_OP,                ACCESS_BYTE_ACC,    0),
/* ACCESSATTRIB_WORD */         OP_TABLE_ENTRY (AML_BYTE_OP,                ACCESS_BYTE_ACC,    0),
/* ACCESSTYPE_ANY */            OP_TABLE_ENTRY (AML_BYTE_OP,                ACCESS_ANY_ACC,     0),
/* ACCESSTYPE_BUF */            OP_TABLE_ENTRY (AML_BYTE_OP,                ACCESS_ANY_ACC,     0),
/* ACCESSTYPE_BYTE */           OP_TABLE_ENTRY (AML_BYTE_OP,                ACCESS_BYTE_ACC,     0),
/* ACCESSTYPE_DWORD */          OP_TABLE_ENTRY (AML_BYTE_OP,                ACCESS_DWORD_ACC,     0),
/* ACCESSTYPE_QWORD */          OP_TABLE_ENTRY (AML_BYTE_OP,                ACCESS_DWORD_ACC,     0),
/* ACCESSTYPE_WORD */           OP_TABLE_ENTRY (AML_BYTE_OP,                ACCESS_WORD_ACC,     0),
/* ACQUIRE */                   OP_TABLE_ENTRY (AML_ACQUIRE_OP,             0,                  0),
/* ADD */                       OP_TABLE_ENTRY (AML_ADD_OP,                 0, 0),
/* ALIAS */                     OP_TABLE_ENTRY (AML_ALIAS_OP,               0, 0),
/* AND */                       OP_TABLE_ENTRY (AML_BIT_AND_OP,             0, 0),
/* ARG0 */                      OP_TABLE_ENTRY (AML_ARG0,                   0, 0),
/* ARG1 */                      OP_TABLE_ENTRY (AML_ARG1,                   0, 0),
/* ARG2 */                      OP_TABLE_ENTRY (AML_ARG2,                   0, 0),
/* ARG3 */                      OP_TABLE_ENTRY (AML_ARG3,                   0, 0),
/* ARG4 */                      OP_TABLE_ENTRY (AML_ARG4,                   0, 0),
/* ARG5 */                      OP_TABLE_ENTRY (AML_ARG5,                   0, 0),
/* ARG6 */                      OP_TABLE_ENTRY (AML_ARG6,                   0, 0),
/* BANKFIELD */                 OP_TABLE_ENTRY (AML_BANK_FIELD_OP,          0,                  NODE_AML_PACKAGE),
/* BREAK */                     OP_TABLE_ENTRY (AML_BREAK_OP,               0, 0),
/* BREAKPOINT */                OP_TABLE_ENTRY (AML_BREAKPOINT_OP,          0, 0),
/* BUFF */                      OP_TABLE_ENTRY (AML_BUFF_OP,                0, 0),
/* BUFFER */                    OP_TABLE_ENTRY (AML_BUFFER_OP,              0,                  NODE_AML_PACKAGE),
/* BYTECONST */                 OP_TABLE_ENTRY (AML_RAW_DATA_BYTE,          0, 0),
/* CASE */                      OP_TABLE_ENTRY (AML_CASE_OP,                0, 0),
/* CONCATENATE */               OP_TABLE_ENTRY (AML_CONCAT_OP,              0, 0),
/* CONCATENATERESTEMPLATE */    OP_TABLE_ENTRY (AML_CONCAT_TPL_OP,          0, 0),
/* CONDREFOF */                 OP_TABLE_ENTRY (AML_COND_REF_OF_OP,         0, 0),
/* CONTINUE */                  OP_TABLE_ENTRY (AML_CONTINUE_OP,            0, 0),
/* COPY */                      OP_TABLE_ENTRY (AML_COPY_OP,                0, 0),
/* CREATEBITFIELD */            OP_TABLE_ENTRY (AML_BIT_FIELD_OP,           0, 0),
/* CREATEBYTEFIELD */           OP_TABLE_ENTRY (AML_BYTE_FIELD_OP,          0, 0),
/* CREATEDWORDFIELD */          OP_TABLE_ENTRY (AML_DWORD_FIELD_OP,         0, 0),
/* CREATEFIELD */               OP_TABLE_ENTRY (AML_CREATE_FIELD_OP,        0, 0),
/* CREATEQWORDFIELD */          OP_TABLE_ENTRY (AML_QWORD_FIELD_OP,         0, 0),
/* CREATEWORDFIELD */           OP_TABLE_ENTRY (AML_WORD_FIELD_OP,          0, 0),
/* DATATABLEREGION */           OP_TABLE_ENTRY (AML_DATA_REGION_OP,         0, 0),
/* DEBUG */                     OP_TABLE_ENTRY (AML_DEBUG_OP,               0, 0),
/* DECREMENT */                 OP_TABLE_ENTRY (AML_DECREMENT_OP,           0, 0),
/* DECSTR */                    OP_TABLE_ENTRY (AML_DEC_STR_OP,             0, 0),
/* DEFAULT */                   OP_TABLE_ENTRY (AML_DEFAULT_OP,             0, 0),
/* DEFAULT_ARG */               OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0, 0),
/* DEFINITIONBLOCK */           OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0, 0),
/* DEREFOF */                   OP_TABLE_ENTRY (AML_DEREF_OF_OP,            0, 0),
/* DEVICE */                    OP_TABLE_ENTRY (AML_DEVICE_OP,              0,                  NODE_AML_PACKAGE),
/* DIVIDE */                    OP_TABLE_ENTRY (AML_DIVIDE_OP,              0, 0),
/* DMA */                       OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0, 0),
/* DWORDCONST */                OP_TABLE_ENTRY (AML_RAW_DATA_DWORD,         0, 0),
/* DWORDIO */                   OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0, 0),
/* DWORDMEMORY */               OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0, 0),
/* EISAID */                    OP_TABLE_ENTRY (AML_DWORD_OP,         0, 0),
/* ELSE */                      OP_TABLE_ENTRY (AML_ELSE_OP,                0,                  NODE_AML_PACKAGE),
/* ELSEIF */                    OP_TABLE_ENTRY (AML_ELSEIF_OP,              0,                  NODE_AML_PACKAGE),
/* ENDDEPENDENTFN */            OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0, 0),
/* EVENT */                     OP_TABLE_ENTRY (AML_EVENT_OP,               0, 0),
/* EXTERNAL */                  OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0, 0),
/* FATAL */                     OP_TABLE_ENTRY (AML_FATAL_OP,               0, 0),
/* FIELD */                     OP_TABLE_ENTRY (AML_DEF_FIELD_OP,           0,                  NODE_AML_PACKAGE),
/* FINDSETLEFTBIT */            OP_TABLE_ENTRY (AML_FIND_SET_LEFT_BIT_OP,   0, 0),
/* FINDSETRIGHTBIT */           OP_TABLE_ENTRY (AML_FIND_SET_LEFT_BIT_OP,   0, 0),
/* FROMBCD */                   OP_TABLE_ENTRY (AML_FROM_BCD_OP,            0, 0),
/* HEXSTR */                    OP_TABLE_ENTRY (AML_HEXSTR_OP,              0, 0),
/* IF */                        OP_TABLE_ENTRY (AML_IF_OP,                  0,                  NODE_AML_PACKAGE),
/* INCLUDE */                   OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0, 0),
/* INCREMENT */                 OP_TABLE_ENTRY (AML_INCREMENT_OP,           0, 0),
/* INDEX */                     OP_TABLE_ENTRY (AML_INDEX_OP,               0, 0),
/* INDEXFIELD */                OP_TABLE_ENTRY (AML_INDEX_FIELD_OP,         0,                  NODE_AML_PACKAGE),
/* INT */                       OP_TABLE_ENTRY (AML_INT_OP,                 0, 0),
/* INTEGER */                   OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* INTERRUPT */                 OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0, 0),
/* IO */                        OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0, 0),
/* IRQ */                       OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0, 0),
/* IRQNOFLAGS */                OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0, 0),
/* LAND */                      OP_TABLE_ENTRY (AML_LAND_OP,                0, 0),
/* LEQUAL */                    OP_TABLE_ENTRY (AML_LEQUAL_OP,              0, 0),
/* LGREATER */                  OP_TABLE_ENTRY (AML_LGREATER_OP,            0, 0),
/* LGREATEREQUAL */             OP_TABLE_ENTRY (AML_LGREATEREQUAL_OP,       0, 0),
/* LLESS */                     OP_TABLE_ENTRY (AML_LLESS_OP,               0, 0),
/* LLESSEQUAL */                OP_TABLE_ENTRY (AML_LLESSEQUAL_OP,          0, 0),
/* LNOT */                      OP_TABLE_ENTRY (AML_LNOT_OP,                0, 0),
/* LNOTEQUAL */                 OP_TABLE_ENTRY (AML_LNOTEQUAL_OP,           0, 0),
/* LOAD */                      OP_TABLE_ENTRY (AML_LOAD_OP,                0, 0),
/* LOADTABLE */                 OP_TABLE_ENTRY (AML_LOAD_TABLE_OP,          0, 0),
/* LOCAL0 */                    OP_TABLE_ENTRY (AML_LOCAL0,                 0, 0),
/* LOCAL1 */                    OP_TABLE_ENTRY (AML_LOCAL1,                 0, 0),
/* LOCAL2 */                    OP_TABLE_ENTRY (AML_LOCAL2,                 0, 0),
/* LOCAL3 */                    OP_TABLE_ENTRY (AML_LOCAL3,                 0, 0),
/* LOCAL4 */                    OP_TABLE_ENTRY (AML_LOCAL4,                 0, 0),
/* LOCAL5 */                    OP_TABLE_ENTRY (AML_LOCAL5,                 0, 0),
/* LOCAL6 */                    OP_TABLE_ENTRY (AML_LOCAL6,                 0, 0),
/* LOCAL7 */                    OP_TABLE_ENTRY (AML_LOCAL7,                 0, 0),
/* LOCKRULE_LOCK */             OP_TABLE_ENTRY (AML_BYTE_OP,                GLOCK_ALWAYS_LOCK, 0),
/* LOCKRULE_NOLOCK */           OP_TABLE_ENTRY (AML_BYTE_OP,                GLOCK_NEVER_LOCK, 0),
/* LOR */                       OP_TABLE_ENTRY (AML_LOR_OP,                 0, 0),
/* MATCH */                     OP_TABLE_ENTRY (AML_MATCH_OP,               0, 0),
/* MATCHTYPE_MEQ */             OP_TABLE_ENTRY (AML_RAW_DATA_BYTE,                MATCH_MEQ, 0),
/* MATCHTYPE_MGE */             OP_TABLE_ENTRY (AML_RAW_DATA_BYTE,                MATCH_MGE, 0),
/* MATCHTYPE_MGT */             OP_TABLE_ENTRY (AML_RAW_DATA_BYTE,                MATCH_MGT, 0),
/* MATCHTYPE_MLE */             OP_TABLE_ENTRY (AML_RAW_DATA_BYTE,                MATCH_MLE, 0),
/* MATCHTYPE_MLT */             OP_TABLE_ENTRY (AML_RAW_DATA_BYTE,                MATCH_MLT, 0),
/* MATCHTYPE_MTR */             OP_TABLE_ENTRY (AML_RAW_DATA_BYTE,                MATCH_MTR, 0),
/* MEMORY24 */                  OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0, 0),
/* MEMORY32 */                  OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0, 0),
/* MEMORY32FIXED */             OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0, 0),
/* METHOD */                    OP_TABLE_ENTRY (AML_METHOD_OP,              0,                  NODE_AML_PACKAGE),
/* MID */                       OP_TABLE_ENTRY (AML_MID_OP,                 0, 0),
/* MOD */                       OP_TABLE_ENTRY (AML_MOD_OP,                 0, 0),
/* MULTIPLY */                  OP_TABLE_ENTRY (AML_MULTIPLY_OP,            0, 0),
/* MUTEX */                     OP_TABLE_ENTRY (AML_MUTEX_OP,               0, 0),
/* NAME */                      OP_TABLE_ENTRY (AML_NAME_OP,                0, 0),
/* NAMESEG */                   OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* NAMESTRING */                OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* NAND */                      OP_TABLE_ENTRY (AML_BIT_NAND_OP,            0, 0),
/* NOOP */                      OP_TABLE_ENTRY (AML_NOOP_OP,                0, 0),
/* NOR */                       OP_TABLE_ENTRY (AML_BIT_NOR_OP,             0, 0),
/* NOT */                       OP_TABLE_ENTRY (AML_BIT_NOT_OP,             0, 0),
/* NOTIFY */                    OP_TABLE_ENTRY (AML_NOTIFY_OP,              0, 0),
/* OBJECTTYPE */                OP_TABLE_ENTRY (AML_TYPE_OP,                0, 0),
/* OBJECTTYPE_BFF */            OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* OBJECTTYPE_BUF */            OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* OBJECTTYPE_DDB */            OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* OBJECTTYPE_DEV */            OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* OBJECTTYPE_EVT */            OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* OBJECTTYPE_FLD */            OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* OBJECTTYPE_INT */            OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* OBJECTTYPE_MTH */            OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* OBJECTTYPE_MTX */            OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* OBJECTTYPE_OPR */            OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* OBJECTTYPE_PKG */            OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* OBJECTTYPE_POW */            OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* OBJECTTYPE_STR */            OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* OBJECTTYPE_THZ */            OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* OBJECTTYPE_UNK */            OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* OFFSET */                    OP_TABLE_ENTRY (AML_RESERVEDFIELD_OP,       0, 0),
/* ONE */                       OP_TABLE_ENTRY (AML_ONE_OP,                 0, 0),
/* ONES */                      OP_TABLE_ENTRY (AML_ONES_OP,                0, 0),
/* OPERATIONREGION */           OP_TABLE_ENTRY (AML_REGION_OP,              0, 0),
/* OR */                        OP_TABLE_ENTRY (AML_BIT_OR_OP,              0, 0),
/* PACKAGE */                   OP_TABLE_ENTRY (AML_PACKAGE_OP,             0,                  NODE_AML_PACKAGE),
/* PACKAGEP_LENGTH */           OP_TABLE_ENTRY (AML_PACKAGE_LENGTH,         0,                  NODE_AML_PACKAGE),
/* POWERRESOURCE */             OP_TABLE_ENTRY (AML_POWER_RES_OP,           0,                  NODE_AML_PACKAGE),
/* PROCESSOR */                 OP_TABLE_ENTRY (AML_PROCESSOR_OP,           0,                  NODE_AML_PACKAGE),
/* QWORDIO */                   OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* QWORDMEMORY */               OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* RAW_DATA */                  OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* REFOF */                     OP_TABLE_ENTRY (AML_REF_OF_OP,              0, 0),
/* REGIONSPACE_CMOS */          OP_TABLE_ENTRY (AML_RAW_DATA_BYTE,          REGION_CMOS, 0),
/* REGIONSPACE_EC */            OP_TABLE_ENTRY (AML_RAW_DATA_BYTE,          REGION_EC, 0),
/* REGIONSPACE_IO */            OP_TABLE_ENTRY (AML_RAW_DATA_BYTE,          REGION_IO, 0),
/* REGIONSPACE_MEM */           OP_TABLE_ENTRY (AML_RAW_DATA_BYTE,          REGION_MEMORY, 0),
/* REGIONSPACE_PCI */           OP_TABLE_ENTRY (AML_RAW_DATA_BYTE,          REGION_PCI_CONFIG, 0),
/* REGIONSPACE_PCIBAR */        OP_TABLE_ENTRY (AML_RAW_DATA_BYTE,          REGION_PCI_BAR, 0),
/* REGIONSPACE_SMBUS */         OP_TABLE_ENTRY (AML_RAW_DATA_BYTE,          REGION_SMBUS, 0),
/* REGISTER */                  OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* RELEASE */                   OP_TABLE_ENTRY (AML_RELEASE_OP,             0, 0),
/* RESERVED_BYTES */            OP_TABLE_ENTRY (AML_RESERVEDFIELD_OP,       0, 0),
/* RESET */                     OP_TABLE_ENTRY (AML_RESET_OP,               0, 0),
/* RESOURCETEMPLATE */          OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* RETURN */                    OP_TABLE_ENTRY (AML_RETURN_OP,              0, 0),
/* SCOPE */                     OP_TABLE_ENTRY (AML_SCOPE_OP,               0,                  NODE_AML_PACKAGE),
/* SERIALIZERULE_NOTSERIAL */   OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* SERIALIZERULE_SERIAL */      OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* SHIFTLEFT */                 OP_TABLE_ENTRY (AML_SHIFT_LEFT_OP,          0, 0),
/* SHIFTRIGHT */                OP_TABLE_ENTRY (AML_SHIFT_RIGHT_OP,         0, 0),
/* SIGNAL */                    OP_TABLE_ENTRY (AML_SIGNAL_OP,              0, 0),
/* SIZEOF */                    OP_TABLE_ENTRY (AML_SIZE_OF_OP,             0, 0),
/* SLEEP */                     OP_TABLE_ENTRY (AML_SLEEP_OP,               0, 0),
/* STALL */                     OP_TABLE_ENTRY (AML_STALL_OP,               0, 0),
/* STARTDEPENDENTFN */          OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* STARTDEPENDENTFN_NOPRI */    OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* STORE */                     OP_TABLE_ENTRY (AML_STORE_OP,               0, 0),
/* STRING */                    OP_TABLE_ENTRY (AML_STRING_OP,              0, 0),
/* STRING_LITERAL */            OP_TABLE_ENTRY (AML_STRING_OP,              0, 0),
/* SUBTRACT */                  OP_TABLE_ENTRY (AML_SUBTRACT_OP,            0, 0),
/* SWITCH */                    OP_TABLE_ENTRY (AML_SWITCH_OP,              0, 0),
/* THERMALZONE */               OP_TABLE_ENTRY (AML_THERMAL_ZONE_OP,        0,                  NODE_AML_PACKAGE),
/* TOBCD */                     OP_TABLE_ENTRY (AML_TO_BCD_OP,              0, 0),
/* UNICODE */                   OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* UNLOAD */                    OP_TABLE_ENTRY (AML_UNLOAD_OP,              0, 0),
/* UPDATERULE_ONES */           OP_TABLE_ENTRY (AML_BYTE_OP,                UPDATE_WRITE_AS_ONES, 0),
/* UPDATERULE_PRESERVE */       OP_TABLE_ENTRY (AML_BYTE_OP,                UPDATE_PRESERVE, 0),
/* UPDATERULE_ZEROS */          OP_TABLE_ENTRY (AML_BYTE_OP,                UPDATE_WRITE_AS_ZEROS, 0),
/* VENDORLONG */                OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* VENDORSHORT */               OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* WAIT */                      OP_TABLE_ENTRY (AML_WAIT_OP,                0, 0),
/* WHILE */                     OP_TABLE_ENTRY (AML_WHILE_OP,               0,                  NODE_AML_PACKAGE),
/* WORDBUSNUMBER */             OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* WORDCONST */                 OP_TABLE_ENTRY (AML_RAW_DATA_WORD,          0, 0),
/* WORDIO */                    OP_TABLE_ENTRY (AML_BYTE_OP,                0, 0),
/* XOR */                       OP_TABLE_ENTRY (AML_BIT_XOR_OP,             0, 0),
/* ZERO */                      OP_TABLE_ENTRY (AML_ZERO_OP,                0, 0),

};

