/*******************************************************************************
 *
 * Module Name: dmbuffer - AML disassembler, buffer and string support
 *
 ******************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2014, Intel Corp.
 * All rights reserved.
 *
 * 2. License
 *
 * 2.1. This is your license from Intel Corp. under its intellectual property
 * rights. You may have additional license terms from the party that provided
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
 * to or modifications of the Original Intel Code. No other license or right
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
 * and the following Disclaimer and Export Compliance provision. In addition,
 * Licensee must cause all Covered Code to which Licensee contributes to
 * contain a file documenting the changes Licensee made to create that Covered
 * Code and the date of any change. Licensee must include in that file the
 * documentation of any changes made by any predecessor Licensee. Licensee
 * must include a prominent statement that the modification is derived,
 * directly or indirectly, from Original Intel Code.
 *
 * 3.2. Redistribution of Source with no Rights to Further Distribute Source.
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification without rights to further distribute source must
 * include the following Disclaimer and Export Compliance provision in the
 * documentation and/or other materials provided with distribution. In
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
 * HERE. ANY SOFTWARE ORIGINATING FROM INTEL OR DERIVED FROM INTEL SOFTWARE
 * IS PROVIDED "AS IS," AND INTEL WILL NOT PROVIDE ANY SUPPORT, ASSISTANCE,
 * INSTALLATION, TRAINING OR OTHER SERVICES. INTEL WILL NOT PROVIDE ANY
 * UPDATES, ENHANCEMENTS OR EXTENSIONS. INTEL SPECIFICALLY DISCLAIMS ANY
 * IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGEMENT AND FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * 4.2. IN NO EVENT SHALL INTEL HAVE ANY LIABILITY TO LICENSEE, ITS LICENSEES
 * OR ANY OTHER THIRD PARTY, FOR ANY LOST PROFITS, LOST DATA, LOSS OF USE OR
 * COSTS OF PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, OR FOR ANY INDIRECT,
 * SPECIAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THIS AGREEMENT, UNDER ANY
 * CAUSE OF ACTION OR THEORY OF LIABILITY, AND IRRESPECTIVE OF WHETHER INTEL
 * HAS ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES. THESE LIMITATIONS
 * SHALL APPLY NOTWITHSTANDING THE FAILURE OF THE ESSENTIAL PURPOSE OF ANY
 * LIMITED REMEDY.
 *
 * 4.3. Licensee shall not export, either directly or indirectly, any of this
 * software or system incorporating such software without first obtaining any
 * required license or other approval from the U. S. Department of Commerce or
 * any other agency or department of the United States Government. In the
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
#include "accommon.h"
#include "acutils.h"
#include "acdisasm.h"
#include "acparser.h"
#include "amlcode.h"
#include "acinterp.h"


#ifdef ACPI_DISASSEMBLER

#define _COMPONENT          ACPI_CA_DEBUGGER
        ACPI_MODULE_NAME    ("dmbuffer")

/* Local prototypes */

static void
AcpiDmUuid (
    ACPI_PARSE_OBJECT       *Op);

static void
AcpiDmUnicode (
    ACPI_PARSE_OBJECT       *Op);

static void
AcpiDmGetHardwareIdType (
    ACPI_PARSE_OBJECT       *Op);

static void
AcpiDmPldBuffer (
    UINT32                  Level,
    UINT8                   *ByteData,
    UINT32                  ByteCount);

static char *
AcpiDmMatchUuid (
    UINT8                   *Data);

/* Table of "known" (ACPI-specific) UUIDs */

typedef struct ah_uuid
{
    char                    *Description;
    UINT8                   Value[UUID_BUFFER_LENGTH];

} AH_UUID;

static const AH_UUID  AslUuids[] =
{
    /* 33db4d5b-1ff7-401c-9657-7441c03dd766 */

    {"PCI Host Bridge Device",
        {0x5B,0x4D,0xDB,0x33,0xF7,0x1F,0x1C,0x40,
         0x96,0x57,0x74,0x41,0xC0,0x3D,0xD7,0x66}},

    /* 0811b06e-4a27-44f9-8d60-3cbbc22e7b48 */

    {"Platform-wide Capabilities",
        {0x6E,0xB0,0x11,0x08,0x27,0x4A,0xF9,0x44,
         0x8D,0x60,0x3C,0xBB,0xC2,0x2E,0x7B,0x48}},

    /* d8c1a3a6-be9b-4c9b-91bf-c3cb81fc5daf */

    {"Dynamic Enumeration",
        {0xA6,0xA3,0xC1,0xD8,0x9B,0xBE,0x9B,0x4C,
         0x91,0xBF,0xC3,0xCB,0x81,0xFC,0x5D,0xAF}},

    /* 4f248f40-d5e2-499f-834c-27758ea1cd3f */

    {"GPIO Controller",
        {0x40,0x8F,0x24,0x4F,0xE2,0xD5,0x9F,0x49,
         0x83,0x4C,0x27,0x75,0x8E,0xA1,0xCD,0x3F}},

    /* 4c2067e3-887d-475c-9720-4af1d3ed602e */

    {"Battery Thermal Limit",
        {0xE3,0x67,0x20,0x4C,0x7D,0x88,0x5C,0x47,
         0x97,0x20,0x4A,0xF1,0xD3,0xED,0x60,0x2E}},

    /* 14d399cd-7a27-4b18-8fb4-7cb7b9f4e500 */

    {"Thermal Extensions",
        {0xCD,0x99,0xD3,0x14,0x27,0x7A,0x18,0x4B,
         0x8F,0xB4,0x7C,0xB7,0xB9,0xF4,0xE5,0x00}},

    /* ce2ee385-00e6-48cb-9f05-2edb927c4899 */

    {"USB Controller",
        {0x85,0xE3,0x2E,0xCE,0xE6,0x00,0xCB,0x48,
         0x9F,0x05,0x2E,0xDB,0x92,0x7C,0x48,0x99}},

    /* 3cdff6f7-4267-4555-ad05-b30a3d8938de */

    {"HID I2C Device",
        {0xF7,0xF6,0xDF,0x3C,0x67,0x42,0x55,0x45,
         0xAD,0x05,0xB3,0x0A,0x3D,0x89,0x38,0xDE}},

    /* dfbcf3c5-e7a5-44e6-9c1f-29c76f6e059c */

    {"Power Button Device",
        {0xC5,0xF3,0xBC,0xDF,0xA5,0xE7,0xE6,0x44,
         0x9C,0x1F,0x29,0xC7,0x6F,0x6E,0x05,0x9C}},

    /* e5c937d0-3553-4d7a-9117-ea4d19c3434d */

    {"Ignore PCI Device Boot Configuration",
        {0xD0,0x37,0xC9,0xE5,0x53,0x35,0x7A,0x4D,
         0x91,0x17,0xEA,0x4D,0x19,0xC3,0x43,0x4D}},

    /* e4db149b-fcfe-425b-a6d8-92357d78fc7f */

    {"SATA Controller",
        {0x9B,0x14,0xDB,0xE4,0xFE,0xFC,0x5B,0x42,
         0xA6,0xD8,0x92,0x35,0x7D,0x78,0xFC,0x7F}},

    {NULL}
};


#define ACPI_BUFFER_BYTES_PER_LINE      8


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmDisasmByteList
 *
 * PARAMETERS:  Level               - Current source code indentation level
 *              ByteData            - Pointer to the byte list
 *              ByteCount           - Length of the byte list
 *
 * RETURN:      None
 *
 * DESCRIPTION: Dump an AML "ByteList" in Hex format. 8 bytes per line, prefixed
 *              with the hex buffer offset.
 *
 ******************************************************************************/

void
AcpiDmDisasmByteList (
    UINT32                  Level,
    UINT8                   *ByteData,
    UINT32                  ByteCount)
{
    UINT32                  i;
    UINT32                  j;
    UINT32                  CurrentIndex;
    UINT8                   BufChar;


    if (!ByteCount)
    {
        return;
    }

    for (i = 0; i < ByteCount; i += ACPI_BUFFER_BYTES_PER_LINE)
    {
        /* Line indent and offset prefix for each new line */

        AcpiDmIndent (Level);
        if (ByteCount > ACPI_BUFFER_BYTES_PER_LINE)
        {
            AcpiOsPrintf ("/* %04X */ ", i);
        }

        /* Dump the actual hex values */

        for (j = 0; j < ACPI_BUFFER_BYTES_PER_LINE; j++)
        {
            CurrentIndex = i + j;
            if (CurrentIndex >= ByteCount)
            {
                /* Dump fill spaces */

                AcpiOsPrintf ("      ");
                continue;
            }

            AcpiOsPrintf (" 0x%2.2X", ByteData[CurrentIndex]);

            /* Add comma if there are more bytes to display */

            if (CurrentIndex < (ByteCount - 1))
            {
                AcpiOsPrintf (",");
            }
            else
            {
                AcpiOsPrintf (" ");
            }
        }

        /* Dump the ASCII equivalents within a comment */

        AcpiOsPrintf ("  /* ");
        for (j = 0; j < ACPI_BUFFER_BYTES_PER_LINE; j++)
        {
            CurrentIndex = i + j;
            if (CurrentIndex >= ByteCount)
            {
                break;
            }

            BufChar = ByteData[CurrentIndex];
            if (ACPI_IS_PRINT (BufChar))
            {
                AcpiOsPrintf ("%c", BufChar);
            }
            else
            {
                AcpiOsPrintf (".");
            }
        }

        /* Finished with this line */

        AcpiOsPrintf (" */\n");
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmByteList
 *
 * PARAMETERS:  Info            - Parse tree walk info
 *              Op              - Byte list op
 *
 * RETURN:      None
 *
 * DESCRIPTION: Dump a buffer byte list, handling the various types of buffers.
 *              Buffer type must be already set in the Op DisasmOpcode.
 *
 ******************************************************************************/

void
AcpiDmByteList (
    ACPI_OP_WALK_INFO       *Info,
    ACPI_PARSE_OBJECT       *Op)
{
    UINT8                   *ByteData;
    UINT32                  ByteCount;


    ByteData = Op->Named.Data;
    ByteCount = (UINT32) Op->Common.Value.Integer;

    /*
     * The byte list belongs to a buffer, and can be produced by either
     * a ResourceTemplate, Unicode, quoted string, or a plain byte list.
     */
    switch (Op->Common.Parent->Common.DisasmOpcode)
    {
    case ACPI_DASM_RESOURCE:

        AcpiDmResourceTemplate (Info, Op->Common.Parent, ByteData, ByteCount);
        break;

    case ACPI_DASM_STRING:

        AcpiDmIndent (Info->Level);
        AcpiUtPrintString ((char *) ByteData, ACPI_UINT16_MAX);
        AcpiOsPrintf ("\n");
        break;

    case ACPI_DASM_UUID:

        AcpiDmUuid (Op);
        break;

    case ACPI_DASM_UNICODE:

        AcpiDmUnicode (Op);
        break;

    case ACPI_DASM_PLD_METHOD:

        AcpiDmDisasmByteList (Info->Level, ByteData, ByteCount);
        AcpiDmPldBuffer (Info->Level, ByteData, ByteCount);
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
 * FUNCTION:    AcpiDmIsUuidBuffer
 *
 * PARAMETERS:  Op              - Buffer Object to be examined
 *
 * RETURN:      TRUE if buffer contains a UUID
 *
 * DESCRIPTION: Determine if a buffer Op contains a UUID
 *
 * To help determine whether the buffer is a UUID versus a raw data buffer,
 * there a are a couple bytes we can look at:
 *
 *    xxxxxxxx-xxxx-Mxxx-Nxxx-xxxxxxxxxxxx
 *
 * The variant covered by the UUID specification is indicated by the two most
 * significant bits of N being 1 0 (i.e., the hexadecimal N will always be
 * 8, 9, A, or B).
 *
 * The variant covered by the UUID specification has five versions. For this
 * variant, the four bits of M indicates the UUID version (i.e., the
 * hexadecimal M will be either 1, 2, 3, 4, or 5).
 *
 ******************************************************************************/

BOOLEAN
AcpiDmIsUuidBuffer (
    ACPI_PARSE_OBJECT       *Op)
{
    UINT8                   *ByteData;
    UINT32                  ByteCount;
    ACPI_PARSE_OBJECT       *SizeOp;
    ACPI_PARSE_OBJECT       *NextOp;


    /* Buffer size is the buffer argument */

    SizeOp = Op->Common.Value.Arg;

    /* Next, the initializer byte list to examine */

    NextOp = SizeOp->Common.Next;
    if (!NextOp)
    {
        return (FALSE);
    }

    /* Extract the byte list info */

    ByteData = NextOp->Named.Data;
    ByteCount = (UINT32) NextOp->Common.Value.Integer;

    /* Byte count must be exactly 16 */

    if (ByteCount != UUID_BUFFER_LENGTH)
    {
        return (FALSE);
    }

    /* Check for valid "M" and "N" values (see function header above) */

    if (((ByteData[7] & 0xF0) == 0x00) || /* M={1,2,3,4,5} */
        ((ByteData[7] & 0xF0) > 0x50)  ||
        ((ByteData[8] & 0xF0) < 0x80)  || /* N={8,9,A,B} */
        ((ByteData[8] & 0xF0) > 0xB0))
    {
        return (FALSE);
    }

    /* Ignore the Size argument in the disassembly of this buffer op */

    SizeOp->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE;
    return (TRUE);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmUuid
 *
 * PARAMETERS:  Op              - Byte List op containing a UUID
 *
 * RETURN:      None
 *
 * DESCRIPTION: Dump a buffer containing a UUID as a standard ASCII string.
 *
 * Output Format:
 * In its canonical form, the UUID is represented by a string containing 32
 * lowercase hexadecimal digits, displayed in 5 groups separated by hyphens.
 * The complete form is 8-4-4-4-12 for a total of 36 characters (32
 * alphanumeric characters representing hex digits and 4 hyphens). In bytes,
 * 4-2-2-2-6. Example:
 *
 *    ToUUID ("107ededd-d381-4fd7-8da9-08e9a6c79644")
 *
 ******************************************************************************/

static void
AcpiDmUuid (
    ACPI_PARSE_OBJECT       *Op)
{
    UINT8                   *Data;
    char                    *Description;


    Data = ACPI_CAST_PTR (UINT8, Op->Named.Data);

    /* Emit the 36-byte UUID string in the proper format/order */

    AcpiOsPrintf (
        "\"%2.2x%2.2x%2.2x%2.2x-"
        "%2.2x%2.2x-"
        "%2.2x%2.2x-"
        "%2.2x%2.2x-"
        "%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x\")",
        Data[3], Data[2], Data[1], Data[0],
        Data[5], Data[4],
        Data[7], Data[6],
        Data[8], Data[9],
        Data[10], Data[11], Data[12], Data[13], Data[14], Data[15]);

    /* Dump the UUID description string if available */

    Description = AcpiDmMatchUuid (Data);
    if (Description)
    {
        AcpiOsPrintf (" /* %s */", Description);
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmMatchUuid
 *
 * PARAMETERS:  Data                - Data buffer containing a UUID
 *
 * RETURN:      ASCII description string for the UUID if it is found.
 *
 * DESCRIPTION: Returns a description string for "known" UUIDs, which are
 *              are defined here to be UUIDs that are defined by ACPI.
 *
 ******************************************************************************/

static char *
AcpiDmMatchUuid (
    UINT8                   *Data)
{
    const AH_UUID           *Info;


    for (Info = AslUuids; Info->Description; Info++)
    {
        if (!ACPI_MEMCMP (Data, Info->Value, UUID_BUFFER_LENGTH))
        {
            return (Info->Description);
        }
    }

    return (NULL);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmIsUnicodeBuffer
 *
 * PARAMETERS:  Op              - Buffer Object to be examined
 *
 * RETURN:      TRUE if buffer contains a UNICODE string
 *
 * DESCRIPTION: Determine if a buffer Op contains a Unicode string
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


    /* Buffer size is the buffer argument */

    SizeOp = Op->Common.Value.Arg;

    /* Next, the initializer byte list to examine */

    NextOp = SizeOp->Common.Next;
    if (!NextOp)
    {
        return (FALSE);
    }

    /* Extract the byte list info */

    ByteData = NextOp->Named.Data;
    ByteCount = (UINT32) NextOp->Common.Value.Integer;
    WordCount = ACPI_DIV_2 (ByteCount);

    /*
     * Unicode string must have an even number of bytes and last
     * word must be zero
     */
    if ((!ByteCount)     ||
         (ByteCount < 4) ||
         (ByteCount & 1) ||
        ((UINT16 *) (void *) ByteData)[WordCount - 1] != 0)
    {
        return (FALSE);
    }

    /* For each word, 1st byte must be ascii, 2nd byte must be zero */

    for (i = 0; i < (ByteCount - 2); i += 2)
    {
        if ((!ACPI_IS_PRINT (ByteData[i])) ||
            (ByteData[(ACPI_SIZE) i + 1] != 0))
        {
            return (FALSE);
        }
    }

    /* Ignore the Size argument in the disassembly of this buffer op */

    SizeOp->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE;
    return (TRUE);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmIsStringBuffer
 *
 * PARAMETERS:  Op              - Buffer Object to be examined
 *
 * RETURN:      TRUE if buffer contains a ASCII string, FALSE otherwise
 *
 * DESCRIPTION: Determine if a buffer Op contains a ASCII string
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


    /* Buffer size is the buffer argument */

    SizeOp = Op->Common.Value.Arg;

    /* Next, the initializer byte list to examine */

    NextOp = SizeOp->Common.Next;
    if (!NextOp)
    {
        return (FALSE);
    }

    /* Extract the byte list info */

    ByteData = NextOp->Named.Data;
    ByteCount = (UINT32) NextOp->Common.Value.Integer;

    /* Last byte must be the null terminator */

    if ((!ByteCount)     ||
         (ByteCount < 2) ||
         (ByteData[ByteCount-1] != 0))
    {
        return (FALSE);
    }

    for (i = 0; i < (ByteCount - 1); i++)
    {
        /* TBD: allow some escapes (non-ascii chars).
         * they will be handled in the string output routine
         */

        if (!ACPI_IS_PRINT (ByteData[i]))
        {
            return (FALSE);
        }
    }

    return (TRUE);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmIsPldBuffer
 *
 * PARAMETERS:  Op                  - Buffer Object to be examined
 *
 * RETURN:      TRUE if buffer contains a ASCII string, FALSE otherwise
 *
 * DESCRIPTION: Determine if a buffer Op contains a _PLD structure
 *
 ******************************************************************************/

BOOLEAN
AcpiDmIsPldBuffer (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_NAMESPACE_NODE     *Node;
    ACPI_PARSE_OBJECT       *ParentOp;


    ParentOp = Op->Common.Parent;
    if (!ParentOp)
    {
        return (FALSE);
    }

    /* Check for form: Name(_PLD, Buffer() {}). Not legal, however */

    if (ParentOp->Common.AmlOpcode == AML_NAME_OP)
    {
        Node = ParentOp->Common.Node;

        if (ACPI_COMPARE_NAME (Node->Name.Ascii, METHOD_NAME__PLD))
        {
            return (TRUE);
        }

        return (FALSE);
    }

    /* Check for proper form: Name(_PLD, Package() {Buffer() {}}) */

    if (ParentOp->Common.AmlOpcode == AML_PACKAGE_OP)
    {
        ParentOp = ParentOp->Common.Parent;
        if (!ParentOp)
        {
            return (FALSE);
        }

        if (ParentOp->Common.AmlOpcode == AML_NAME_OP)
        {
            Node = ParentOp->Common.Node;

            if (ACPI_COMPARE_NAME (Node->Name.Ascii, METHOD_NAME__PLD))
            {
                return (TRUE);
            }
        }
    }

    return (FALSE);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmPldBuffer
 *
 * PARAMETERS:  Level               - Current source code indentation level
 *              ByteData            - Pointer to the byte list
 *              ByteCount           - Length of the byte list
 *
 * RETURN:      None
 *
 * DESCRIPTION: Dump and format the contents of a _PLD buffer object
 *
 ******************************************************************************/

#define ACPI_PLD_OUTPUT08     "%*.s/* %18s : %-6.2X */\n", ACPI_MUL_4 (Level), " "
#define ACPI_PLD_OUTPUT16   "%*.s/* %18s : %-6.4X */\n", ACPI_MUL_4 (Level), " "
#define ACPI_PLD_OUTPUT24   "%*.s/* %18s : %-6.6X */\n", ACPI_MUL_4 (Level), " "

static void
AcpiDmPldBuffer (
    UINT32                  Level,
    UINT8                   *ByteData,
    UINT32                  ByteCount)
{
    ACPI_PLD_INFO           *PldInfo;
    ACPI_STATUS             Status;


    /* Check for valid byte count */

    if (ByteCount < ACPI_PLD_REV1_BUFFER_SIZE)
    {
        return;
    }

    /* Convert _PLD buffer to local _PLD struct */

    Status = AcpiDecodePldBuffer (ByteData, ByteCount, &PldInfo);
    if (ACPI_FAILURE (Status))
    {
        return;
    }

    /* First 32-bit dword */

    AcpiOsPrintf (ACPI_PLD_OUTPUT08,  "Revision", PldInfo->Revision);
    AcpiOsPrintf (ACPI_PLD_OUTPUT08,  "IgnoreColor", PldInfo->IgnoreColor);
    AcpiOsPrintf (ACPI_PLD_OUTPUT24,"Color", PldInfo->Color);

    /* Second 32-bit dword */

    AcpiOsPrintf (ACPI_PLD_OUTPUT16,"Width", PldInfo->Width);
    AcpiOsPrintf (ACPI_PLD_OUTPUT16,"Height", PldInfo->Height);

    /* Third 32-bit dword */

    AcpiOsPrintf (ACPI_PLD_OUTPUT08,  "UserVisible", PldInfo->UserVisible);
    AcpiOsPrintf (ACPI_PLD_OUTPUT08,  "Dock", PldInfo->Dock);
    AcpiOsPrintf (ACPI_PLD_OUTPUT08,  "Lid", PldInfo->Lid);
    AcpiOsPrintf (ACPI_PLD_OUTPUT08,  "Panel", PldInfo->Panel);
    AcpiOsPrintf (ACPI_PLD_OUTPUT08,  "VerticalPosition", PldInfo->VerticalPosition);
    AcpiOsPrintf (ACPI_PLD_OUTPUT08,  "HorizontalPosition", PldInfo->HorizontalPosition);
    AcpiOsPrintf (ACPI_PLD_OUTPUT08,  "Shape", PldInfo->Shape);
    AcpiOsPrintf (ACPI_PLD_OUTPUT08,  "GroupOrientation", PldInfo->GroupOrientation);
    AcpiOsPrintf (ACPI_PLD_OUTPUT08,  "GroupToken", PldInfo->GroupToken);
    AcpiOsPrintf (ACPI_PLD_OUTPUT08,  "GroupPosition", PldInfo->GroupPosition);
    AcpiOsPrintf (ACPI_PLD_OUTPUT08,  "Bay", PldInfo->Bay);

    /* Fourth 32-bit dword */

    AcpiOsPrintf (ACPI_PLD_OUTPUT08,  "Ejectable", PldInfo->Ejectable);
    AcpiOsPrintf (ACPI_PLD_OUTPUT08,  "OspmEjectRequired", PldInfo->OspmEjectRequired);
    AcpiOsPrintf (ACPI_PLD_OUTPUT08,  "CabinetNumber", PldInfo->CabinetNumber);
    AcpiOsPrintf (ACPI_PLD_OUTPUT08,  "CardCageNumber", PldInfo->CardCageNumber);
    AcpiOsPrintf (ACPI_PLD_OUTPUT08,  "Reference", PldInfo->Reference);
    AcpiOsPrintf (ACPI_PLD_OUTPUT08,  "Rotation", PldInfo->Rotation);
    AcpiOsPrintf (ACPI_PLD_OUTPUT08,  "Order", PldInfo->Order);

    /* Fifth 32-bit dword */

    if (ByteCount >= ACPI_PLD_REV1_BUFFER_SIZE)
    {
        AcpiOsPrintf (ACPI_PLD_OUTPUT16,"VerticalOffset", PldInfo->VerticalOffset);
        AcpiOsPrintf (ACPI_PLD_OUTPUT16,"HorizontalOffset", PldInfo->HorizontalOffset);
    }

    ACPI_FREE (PldInfo);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmUnicode
 *
 * PARAMETERS:  Op              - Byte List op containing Unicode string
 *
 * RETURN:      None
 *
 * DESCRIPTION: Dump Unicode string as a standard ASCII string. (Remove
 *              the extra zero bytes).
 *
 ******************************************************************************/

static void
AcpiDmUnicode (
    ACPI_PARSE_OBJECT       *Op)
{
    UINT16                  *WordData;
    UINT32                  WordCount;
    UINT32                  i;


    /* Extract the buffer info as a WORD buffer */

    WordData = ACPI_CAST_PTR (UINT16, Op->Named.Data);
    WordCount = ACPI_DIV_2 (((UINT32) Op->Common.Value.Integer));

    /* Write every other byte as an ASCII character */

    AcpiOsPrintf ("\"");
    for (i = 0; i < (WordCount - 1); i++)
    {
        AcpiOsPrintf ("%c", (int) WordData[i]);
    }

    AcpiOsPrintf ("\")");
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmGetHardwareIdType
 *
 * PARAMETERS:  Op              - Op to be examined
 *
 * RETURN:      None
 *
 * DESCRIPTION: Determine the type of the argument to a _HID or _CID
 *              1) Strings are allowed
 *              2) If Integer, determine if it is a valid EISAID
 *
 ******************************************************************************/

static void
AcpiDmGetHardwareIdType (
    ACPI_PARSE_OBJECT       *Op)
{
    UINT32                  BigEndianId;
    UINT32                  Prefix[3];
    UINT32                  i;


    switch (Op->Common.AmlOpcode)
    {
    case AML_STRING_OP:

        /* Mark this string as an _HID/_CID string */

        Op->Common.DisasmOpcode = ACPI_DASM_HID_STRING;
        break;

    case AML_WORD_OP:
    case AML_DWORD_OP:

        /* Determine if a Word/Dword is a valid encoded EISAID */

        /* Swap from little-endian to big-endian to simplify conversion */

        BigEndianId = AcpiUtDwordByteSwap ((UINT32) Op->Common.Value.Integer);

        /* Create the 3 leading ASCII letters */

        Prefix[0] = ((BigEndianId >> 26) & 0x1F) + 0x40;
        Prefix[1] = ((BigEndianId >> 21) & 0x1F) + 0x40;
        Prefix[2] = ((BigEndianId >> 16) & 0x1F) + 0x40;

        /* Verify that all 3 are ascii and alpha */

        for (i = 0; i < 3; i++)
        {
            if (!ACPI_IS_ASCII (Prefix[i]) ||
                !ACPI_IS_ALPHA (Prefix[i]))
            {
                return;
            }
        }

        /* Mark this node as convertable to an EISA ID string */

        Op->Common.DisasmOpcode = ACPI_DASM_EISAID;
        break;

    default:
        break;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmCheckForHardwareId
 *
 * PARAMETERS:  Op              - Op to be examined
 *
 * RETURN:      None
 *
 * DESCRIPTION: Determine if a Name() Op is a _HID/_CID.
 *
 ******************************************************************************/

void
AcpiDmCheckForHardwareId (
    ACPI_PARSE_OBJECT       *Op)
{
    UINT32                  Name;
    ACPI_PARSE_OBJECT       *NextOp;


    /* Get the NameSegment */

    Name = AcpiPsGetName (Op);
    if (!Name)
    {
        return;
    }

    NextOp = AcpiPsGetDepthNext (NULL, Op);
    if (!NextOp)
    {
        return;
    }

    /* Check for _HID - has one argument */

    if (ACPI_COMPARE_NAME (&Name, METHOD_NAME__HID))
    {
        AcpiDmGetHardwareIdType (NextOp);
        return;
    }

    /* Exit if not _CID */

    if (!ACPI_COMPARE_NAME (&Name, METHOD_NAME__CID))
    {
        return;
    }

    /* _CID can contain a single argument or a package */

    if (NextOp->Common.AmlOpcode != AML_PACKAGE_OP)
    {
        AcpiDmGetHardwareIdType (NextOp);
        return;
    }

    /* _CID with Package: get the package length, check all elements */

    NextOp = AcpiPsGetDepthNext (NULL, NextOp);

    /* Don't need to use the length, just walk the peer list */

    NextOp = NextOp->Common.Next;
    while (NextOp)
    {
        AcpiDmGetHardwareIdType (NextOp);
        NextOp = NextOp->Common.Next;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmDecompressEisaId
 *
 * PARAMETERS:  EncodedId       - Raw encoded EISA ID.
 *
 * RETURN:      None
 *
 * DESCRIPTION: Convert an encoded EISAID back to the original ASCII String
 *              and emit the correct ASL statement. If the ID is known, emit
 *              a description of the ID as a comment.
 *
 ******************************************************************************/

void
AcpiDmDecompressEisaId (
    UINT32                  EncodedId)
{
    char                    IdBuffer[ACPI_EISAID_STRING_SIZE];
    const AH_DEVICE_ID      *Info;


    /* Convert EISAID to a string an emit the statement */

    AcpiExEisaIdToString (IdBuffer, EncodedId);
    AcpiOsPrintf ("EisaId (\"%s\")", IdBuffer);

    /* If we know about the ID, emit the description */

    Info = AcpiAhMatchHardwareId (IdBuffer);
    if (Info)
    {
        AcpiOsPrintf (" /* %s */", Info->Description);
    }
}

#endif
