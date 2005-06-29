
/******************************************************************************
 * 
 * Module Name: isnames - interpreter/scanner name load/execute
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

#define __ISNAMES_C__

#include <acpi.h>
#include <interp.h>
#include <amlcode.h>
#include <namesp.h>

#define _COMPONENT          INTERPRETER
        MODULE_NAME         ("isnames");


#define PKG_Type1   64              /*  or 0x40 Max encoding size = 0x3F    */
#define PKG_Type2   16384           /*  or 0x4000 Max encoding size = 0xFFF */
#define PKG_Type3   4194304         /*  or 0x400000 Max encoding size = 0xFFFFF */
#define PKG_Type4   1073741824      /*  or 0x40000000 Max encoding size = 0xFFFFFFF */


/*****************************************************************************
 *
 * FUNCTION:    AmlAllocateNameString
 *
 * PARAMETERS:  PrefixCount         - Count of parent levels. Special cases:
 *                                    (-1) = root,  0 = none
 *              NumNameSegs         - count of 4-character name segments
 *
 * RETURN:      A pointer to the allocated string segment.  This segment must
 *              be deleted by the caller.
 *
 * DESCRIPTION: Ensure allocated name string is long enough,
 *              and set up prefix if any.
 *
 ****************************************************************************/

char *
AmlAllocateNameString (
    INT32                   PrefixCount, 
    INT32                   NumNameSegs)
{
    char                    *TempPtr;
    char                    *NameString;
    INT32                   SizeNeeded;


    FUNCTION_TRACE ("AmlAllocateNameString");

    /* 
     * Allow room for all \ and ^ prefixes, all segments, and a MultiNamePrefix.
     * This may actually be somewhat longer than needed.
     */

    if (PrefixCount < 0)
    {
        SizeNeeded = 1 /* root */ +  (ACPI_NAME_SIZE * NumNameSegs) + 2 +1; /* zero terminate */
    }
    else
    {
        SizeNeeded = PrefixCount + (ACPI_NAME_SIZE * NumNameSegs) + 2 +1; /* zero terminate */
    }

    /* 
     * Allocate a buffer for the name.
     * This buffer must be deleted by the caller!
     */

    NameString = CmAllocate ((ACPI_SIZE) SizeNeeded);
    if (!NameString)
    {
        /* Allocation failure  */

        REPORT_ERROR ("AmlAllocateNameString: name allocation failure");
        return_VALUE (NULL);
    }

    TempPtr = NameString;

    /* Set up Root or Parent prefixes if needed */

    if (PrefixCount < 0)
    {
        *TempPtr++ = AML_RootPrefix;
    }

    else
    {
        while (PrefixCount--)
        {
            *TempPtr++ = AML_ParentPrefix;
        }
    }


    /* Set up Dual or Multi prefixes if needed */
    
    if (NumNameSegs > 2)
    {
        /* Set up multi prefixes   */

        *TempPtr++ = AML_MultiNamePrefixOp;
        *TempPtr++ = (char) NumNameSegs;
    }

    else if (2 == NumNameSegs)
    {
        /* Set up dual prefixes */

        *TempPtr++ = AML_DualNamePrefix;
    }

    /* Terminate string following prefixes. AmlExecNameSegment() will append the segment(s) */

    *TempPtr = 0;

    return_VALUE (NameString);
}


/*****************************************************************************
 *
 * FUNCTION:    AmlGoodName
 *
 * PARAMETERS:  Character           - The character to be examined
 *
 * RETURN:      1 if Character may appear in a name, else 0
 *
 * DESCRIPTION: Check for a printable character
 *
 ****************************************************************************/

BOOLEAN 
AmlGoodName (
    UINT32                  Name)
{
    char                    *NamePtr = (char *) &Name;
    UINT32                  i;

    

    for (i = 0; i < ACPI_NAME_SIZE; i++)
    {
        if (!((NamePtr[i] == '_') || 
              (NamePtr[i] >= 'A' && NamePtr[i] <= 'Z') ||
              (NamePtr[i] >= '0' && NamePtr[i] <= '9')))
        {
            return FALSE;
        }
    }


    return TRUE;
}


/*****************************************************************************
 *
 * FUNCTION:    AmlGoodChar
 *
 * PARAMETERS:  Character           - The character to be examined
 *
 * RETURN:      1 if Character may appear in a name, else 0
 *
 * DESCRIPTION: Check for a printable character
 *
 ****************************************************************************/

INT32 
AmlGoodChar (
    INT32                   Character)
{

    return ((Character == '_') || 
            (Character >= 'A' && Character <= 'Z') ||
            (Character >= '0' && Character <= '9'));
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlDecodePackageLength
 *
 * PARAMETERS:  LastPkgLen          - latest value decoded by DoPkgLength() for
 *                                    most recently examined package or field
 *
 * RETURN:      Number of bytes contained in package length encoding
 *
 * DESCRIPTION: Decodes the Package Length. Upper 2 bits are are used to
 *              tell if type 1, 2, 3, or 4.
 *                  0x3F        = Max 1 byte encoding,
 *                  0xFFF       = Max 2 byte encoding,
 *                  0xFFFFF     = Max 3 Byte encoding,
 *                  0xFFFFFFFFF = Max 4 Byte encoding.
 *
 ****************************************************************************/

INT32 
AmlDecodePackageLength (
    INT32                   LastPkgLen)
{
    INT32                   NumBytes = 0;


    FUNCTION_TRACE ("AmlDecodePackageLength");


    if (LastPkgLen < PKG_Type1)
    {
        NumBytes = 1;
    }

    else if (LastPkgLen < PKG_Type2)
    {
        NumBytes = 2;
    }

    else if (LastPkgLen < PKG_Type3)
    {
        NumBytes = 3;
    }

    else if (LastPkgLen < PKG_Type4)
    {
        NumBytes = 4;
    }

    return_VALUE (NumBytes);
}


/*****************************************************************************
 *
 * FUNCTION:    AmlExecNameSegment
 *
 * PARAMETERS:  InterpreterMode     - Current running mode (load1/Load2/Exec)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute a name segment (4 bytes)
 *
 ****************************************************************************/

ACPI_STATUS
AmlExecNameSegment (
    UINT8                   **InAmlAddress,
    char                    *NameString)
{
    UINT8                   *AmlAddress = *InAmlAddress;
    ACPI_STATUS             Status = AE_OK;
    INT32                   Index;
    char                    CharBuf[5];


    FUNCTION_TRACE ("AmlExecNameSegment");


    /* If first character is a digit, we aren't looking at a valid name segment    */

    CharBuf[0] = *AmlAddress;

    if ('0' <= CharBuf[0] && CharBuf[0] <= '9')
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecNameSegment: leading digit: %c\n", CharBuf[0]));
        return_ACPI_STATUS (AE_PENDING);
    }

    DEBUG_PRINT (TRACE_LOAD, ("AmlExecNameSegment: Bytes from stream:\n"));

    for (Index = 4; Index > 0 && AmlGoodChar (*AmlAddress); --Index)
    {
        CharBuf[4 - Index] = *AmlAddress++;
        DEBUG_PRINT (TRACE_LOAD, ("%c\n", CharBuf[4 - Index]));
    }


    /* Valid name segment  */

    if (0 == Index)
    {
        /* Found 4 valid characters */
    
        CharBuf[4] = '\0';

        if (NameString)
        {
            STRCAT (NameString, CharBuf);
            DEBUG_PRINT (TRACE_NAMES, ("AmlExecNameSegment: Appended to - %s \n", NameString));
        }

        else
        {
            DEBUG_PRINT (TRACE_NAMES, ("AmlExecNameSegment: No Name string - %s \n", CharBuf));
        }
    }

    else if (4 == Index)
    {
        /* 
         * First character was not a valid name character,
         * so we are looking at something other than a name.
         */
        DEBUG_PRINT (ACPI_INFO, ("AmlExecNameSegment: Leading char not alpha: %02Xh (not a name)\n", CharBuf[0]));
        Status = AE_PENDING;
    }

    else
    {
        /* Segment started with one or more valid characters, but fewer than 4 */
    
        Status = AE_AML_ERROR;
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecNameSegment: Bad char %02x in name, at %p\n", *AmlAddress, AmlAddress));
    }   

    DEBUG_PRINT (TRACE_EXEC, ("Leave AmlExecNameSegment %s \n", CmFormatException (Status)));

    *InAmlAddress = AmlAddress;

    return_ACPI_STATUS (Status);
}



/*****************************************************************************
 *
 * FUNCTION:    AmlGetNameString
 *
 * PARAMETERS:  DataType            - Data type to be associated with this name
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Get a name, including any prefixes.
 *
 ****************************************************************************/


ACPI_STATUS
AmlGetNameString (
    ACPI_OBJECT_TYPE        DataType, 
    UINT8                   *InAmlAddress,
    char                    **OutNameString,
    UINT32                  *OutNameLength)   
{
    ACPI_STATUS             Status = AE_OK;
    UINT8                   *AmlAddress = InAmlAddress;
    char                    *NameString = NULL;
    INT32                   NumSegments;
    INT32                   PrefixCount = 0;
    UINT8                   Prefix = 0;


    FUNCTION_TRACE_PTR ("AmlGetNameString", AmlAddress);


    if (INTERNAL_TYPE_DefField == DataType    || 
        INTERNAL_TYPE_BankField == DataType   || 
        INTERNAL_TYPE_IndexField == DataType)
    {   
        /* Disallow prefixes for types associated with field names */

        NameString = AmlAllocateNameString (0, 1);
        if (!NameString)
        {
            Status = AE_NO_MEMORY;
        }
        else
        {
            Status = AmlExecNameSegment (&AmlAddress, NameString);
        }
    }

    else
    {   
        /* DataType is not a field name   */

        switch (*AmlAddress)
        {   
            /* Examine first character of name for root or parent prefix operators */

        case AML_RootPrefix:

            Prefix = *AmlAddress++;
            DEBUG_PRINT (TRACE_LOAD, ("RootPrefix: %x\n", Prefix));

            /* 
             * Remember that we have a RootPrefix --
             * see comment in AmlAllocateNameString()
             */
            PrefixCount = -1;
            break;


        case AML_ParentPrefix:

            do
            {
                Prefix = *AmlAddress++;
                DEBUG_PRINT (TRACE_LOAD, ("ParentPrefix: %x\n", Prefix));

                ++PrefixCount;

            } while (*AmlAddress == AML_ParentPrefix);
            
            break;


        default:

            break;
        }



        switch (*AmlAddress)
        {
            /* Examine first character of name for name segment prefix operator */
            
        case AML_DualNamePrefix:

            Prefix = *AmlAddress++;
            DEBUG_PRINT (TRACE_LOAD, ("DualNamePrefix: %x\n", Prefix));

            NameString = AmlAllocateNameString (PrefixCount, 2);
            if (!NameString)
            {
                Status = AE_NO_MEMORY;
                break;
            }

            /* Ensure PrefixCount != 0 to remember processing a prefix */
            
            PrefixCount += 2;

            if ((Status = AmlExecNameSegment (&AmlAddress, NameString)) == AE_OK)
            {
                Status = AmlExecNameSegment (&AmlAddress, NameString);
            }
            break;


        case AML_MultiNamePrefixOp:

            Prefix = *AmlAddress++;
            DEBUG_PRINT (TRACE_LOAD, ("MultiNamePrefix: %x\n", Prefix));

            NumSegments = *AmlAddress++;                      /* fetch count of segments */

            NameString = AmlAllocateNameString (PrefixCount, NumSegments);
            if (!NameString)
            {
                Status = AE_NO_MEMORY;
                break;
            }

            /* Ensure PrefixCount != 0 to remember processing a prefix */
            
            PrefixCount += 2;

            while (NumSegments && (Status = AmlExecNameSegment (&AmlAddress, NameString)) == AE_OK)
            {
                --NumSegments;
            }

            break;


        case 0: 
            
            /* NullName valid as of 8-12-98 ASL/AML Grammar Update */
            
            if (-1 == PrefixCount)  
            {
                /* RootPrefix followed by NULL */
            
                DEBUG_PRINT (TRACE_EXEC,
                                ("AmlDoName: NameSeg is \"\\\" followed by NULL\n"));
            }

            AmlAddress++;    /*  consume NULL byte   */
            NameString = AmlAllocateNameString (PrefixCount, 0);
            if (!NameString)
            {
                Status = AE_NO_MEMORY;
                break;
            }

            break;


        default:

            /* Name segment string */

            NameString = AmlAllocateNameString (PrefixCount, 1);
            if (!NameString)
            {
                Status = AE_NO_MEMORY;
                break;
            }

            Status = AmlExecNameSegment (&AmlAddress, NameString);
            break;

        }   /* Switch (PeekOp ())    */
    }


    if (AE_PENDING == Status && PrefixCount != 0)
    {
        /* Ran out of segments after processing a prefix */

        DEBUG_PRINT (ACPI_ERROR, ("AmlDoName: Malformed Name\n"));
        REPORT_ERROR ("Ran out of segments after processing a prefix");

        Status = AE_AML_ERROR;
    }


    *OutNameString = NameString;
    *OutNameLength = (UINT32) (AmlAddress - InAmlAddress);

    return_ACPI_STATUS (Status);
}




