/*******************************************************************************
 *
 * Module Name: utnonansi - Non-ansi C library functions
 *
 ******************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2016, Intel Corp.
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


#define _COMPONENT          ACPI_UTILITIES
        ACPI_MODULE_NAME    ("utnonansi")

/* Local prototypes */

static ACPI_STATUS
AcpiUtStrtoulBase10 (
    char                    *String,
    UINT32                  MaxIntegerByteWidth,
    UINT64                  *RetInteger);

static ACPI_STATUS
AcpiUtStrtoulBase16 (
    char                    *String,
    UINT32                  MaxIntegerByteWidth,
    UINT64                  *RetInteger);


/*
 * Non-ANSI C library functions - strlwr, strupr, stricmp, and a 64-bit
 * version of strtoul.
 */

/*******************************************************************************
 *
 * FUNCTION:    AcpiUtStrlwr (strlwr)
 *
 * PARAMETERS:  SrcString       - The source string to convert
 *
 * RETURN:      None
 *
 * DESCRIPTION: Convert a string to lowercase
 *
 ******************************************************************************/

void
AcpiUtStrlwr (
    char                    *SrcString)
{
    char                    *String;


    ACPI_FUNCTION_ENTRY ();


    if (!SrcString)
    {
        return;
    }

    /* Walk entire string, lowercasing the letters */

    for (String = SrcString; *String; String++)
    {
        *String = (char) tolower ((int) *String);
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiUtStrupr (strupr)
 *
 * PARAMETERS:  SrcString       - The source string to convert
 *
 * RETURN:      None
 *
 * DESCRIPTION: Convert a string to uppercase
 *
 ******************************************************************************/

void
AcpiUtStrupr (
    char                    *SrcString)
{
    char                    *String;


    ACPI_FUNCTION_ENTRY ();


    if (!SrcString)
    {
        return;
    }

    /* Walk entire string, uppercasing the letters */

    for (String = SrcString; *String; String++)
    {
        *String = (char) toupper ((int) *String);
    }
}


/******************************************************************************
 *
 * FUNCTION:    AcpiUtStricmp (stricmp)
 *
 * PARAMETERS:  String1             - first string to compare
 *              String2             - second string to compare
 *
 * RETURN:      int that signifies string relationship. Zero means strings
 *              are equal.
 *
 * DESCRIPTION: Case-insensitive string compare. Implementation of the
 *              non-ANSI stricmp function.
 *
 ******************************************************************************/

int
AcpiUtStricmp (
    char                    *String1,
    char                    *String2)
{
    int                     c1;
    int                     c2;


    do
    {
        c1 = tolower ((int) *String1);
        c2 = tolower ((int) *String2);

        String1++;
        String2++;
    }
    while ((c1 == c2) && (c1));

    return (c1 - c2);
}


#if defined (ACPI_DEBUGGER) || defined (ACPI_APPLICATION)
/*******************************************************************************
 *
 * FUNCTION:    AcpiUtSafeStrcpy, AcpiUtSafeStrcat, AcpiUtSafeStrncat
 *
 * PARAMETERS:  Adds a "DestSize" parameter to each of the standard string
 *              functions. This is the size of the Destination buffer.
 *
 * RETURN:      TRUE if the operation would overflow the destination buffer.
 *
 * DESCRIPTION: Safe versions of standard Clib string functions. Ensure that
 *              the result of the operation will not overflow the output string
 *              buffer.
 *
 * NOTE:        These functions are typically only helpful for processing
 *              user input and command lines. For most ACPICA code, the
 *              required buffer length is precisely calculated before buffer
 *              allocation, so the use of these functions is unnecessary.
 *
 ******************************************************************************/

BOOLEAN
AcpiUtSafeStrcpy (
    char                    *Dest,
    ACPI_SIZE               DestSize,
    char                    *Source)
{

    if (strlen (Source) >= DestSize)
    {
        return (TRUE);
    }

    strcpy (Dest, Source);
    return (FALSE);
}

BOOLEAN
AcpiUtSafeStrcat (
    char                    *Dest,
    ACPI_SIZE               DestSize,
    char                    *Source)
{

    if ((strlen (Dest) + strlen (Source)) >= DestSize)
    {
        return (TRUE);
    }

    strcat (Dest, Source);
    return (FALSE);
}

BOOLEAN
AcpiUtSafeStrncat (
    char                    *Dest,
    ACPI_SIZE               DestSize,
    char                    *Source,
    ACPI_SIZE               MaxTransferLength)
{
    ACPI_SIZE               ActualTransferLength;


    ActualTransferLength = ACPI_MIN (MaxTransferLength, strlen (Source));

    if ((strlen (Dest) + ActualTransferLength) >= DestSize)
    {
        return (TRUE);
    }

    strncat (Dest, Source, MaxTransferLength);
    return (FALSE);
}
#endif


/*******************************************************************************
 *
 * FUNCTION:    AcpiUtStrtoul64
 *
 * PARAMETERS:  String                  - Null terminated input string
 *              Base                    - Radix of the string: 16 or 10 or
 *                                        ACPI_ANY_BASE
 *              MaxIntegerByteWidth     - Maximum allowable integer, in bytes:
 *                                        4 or 8 (32 or 64 bits)
 *              RetInteger              - Where the converted integer is
 *                                        returned
 *
 * RETURN:      Status and Converted value
 *
 * DESCRIPTION: Convert a string into an unsigned value. Performs either a
 *              32-bit or 64-bit conversion, depending on the input integer
 *              size (often the current mode of the interpreter).
 *
 * NOTES:       Negative numbers are not supported, as they are not supported
 *              by ACPI.
 *
 *              Supports only base 16 or base 10 strings/values. Does not
 *              support Octal strings, not needed at this time.
 *
 *              AcpiGbl_IntegerByteWidth should be set to the proper width.
 *              For the core ACPICA code, this width depends on the DSDT
 *              version. For iASL, the default byte width is always 8 for the
 *              parser, but error checking is performed later to flag cases
 *              where a 64-bit constant is defined in a 32-bit DSDT/SSDT.
 *
 *              Unlike Clib, this function aborts with an error for any
 *              malformed input string.
 *
 *              Currently used by:
 *              iASL/Preprocessor - Expression evaluation
 *              iASL/DataTableCompiler - Expression evaluation
 *              Debugger - input string conversion
 *              Interpreter - Implicit and explicit conversions
 *              Tools - acpidump, acpiexec
 *
 ******************************************************************************/

ACPI_STATUS
AcpiUtStrtoul64 (
    char                    *String,
    UINT32                  Base,
    UINT32                  MaxIntegerByteWidth,
    UINT64                  *RetInteger)
{
    ACPI_FUNCTION_TRACE_STR (UtStrtoul64, String);


    /* Parameter validation */

    if (!String || !RetInteger)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    if ((Base != ACPI_ANY_BASE) &&
        (Base != 10) &&
        (Base != 16))
    {
        /* Invalid Base */

        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Skip over any white space at start of string */

    while (isspace ((int) *String))
    {
        String++;
    }

    if (*String == 0)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Determine base if necessary (10 or 16) */

    if (Base == ACPI_ANY_BASE)
    {
        /*
         * (Base == ACPI_ANY_BASE) means "Either decimal or hex";
         * determine which one.
         * NOTE: there is no octal or arbitary base support.
         */
        if ((*String == '0') &&
            (tolower ((int) *(String + 1)) == 'x'))
        {
            /* Found a "0x" prefix -- the string is hex */

            Base = 16;
        }
        else
        {
            Base = 10;
        }
    }

    /* Perform the base 16 or 10 conversion */

    if (Base == 16)
    {
        return (AcpiUtStrtoulBase16 (String, MaxIntegerByteWidth, RetInteger));
    }
    else
    {
        return (AcpiUtStrtoulBase10 (String, MaxIntegerByteWidth, RetInteger));
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiUtStrtoulBase10
 *
 * PARAMETERS:  String                  - Null terminated input string
 *              MaxIntegerByteWidth     - Maximum allowable integer, in bytes:
 *                                        4 or 8 (32 or 64 bits)
 *              RetInteger              - Where the converted integer is
 *                                        returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Performs a base 10 conversion of the input string to an
 *              integer value, either 32 or 64 bits.
 *              Note: String must be valid and non-null.
 *
 ******************************************************************************/

static ACPI_STATUS
AcpiUtStrtoulBase10 (
    char                    *String,
    UINT32                  MaxIntegerByteWidth,
    UINT64                  *RetInteger)
{
    UINT32                  ThisDigit;
    UINT32                  ValidDigits = 0;
    UINT64                  ReturnValue = 0;
    UINT64                  NextValue;


    /* Main loop: convert each ASCII byte in the input string */

    while (*String)
    {
        /* Skip all leading zeros */

        if ((ValidDigits == 0) && (*String == ACPI_ASCII_ZERO))
        {
            String++;
            continue;
        }

        ThisDigit = (UINT8) toupper ((int) *String);
        if (!isdigit ((int) ThisDigit))
        {
            /* Not ASCII 0-9, terminate */

            return (AE_BAD_DECIMAL_CONSTANT);
        }

        /* Convert and insert(add) the decimal digit */

        NextValue = (ReturnValue * 10) + (ThisDigit - '0');

        /* Check for overflow (32 or 64 bit) */

        if (((MaxIntegerByteWidth <= ACPI_MAX32_BYTE_WIDTH) &&
                (NextValue > ACPI_UINT32_MAX)) ||
            (NextValue < ReturnValue)) /* 64-bit overflow case */
        {
            return (AE_CONVERSION_OVERFLOW);
        }

        ReturnValue = NextValue;
        String++;
        ValidDigits++;
    }

    *RetInteger = ReturnValue;
    return (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiUtStrtoulBase16
 *
 * PARAMETERS:  String                  - Null terminated input string
 *              MaxIntegerByteWidth     - Maximum allowable integer, in bytes:
 *                                        4 or 8 (32 or 64 bits)
 *              RetInteger              - Where the converted integer is
 *                                        returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Performs a base 16 conversion of the input string to an
 *              integer value, either 32 or 64 bits.
 *              Note: String must be valid and non-null.
 *
 ******************************************************************************/

static ACPI_STATUS
AcpiUtStrtoulBase16 (
    char                    *String,
    UINT32                  MaxIntegerByteWidth,
    UINT64                  *RetInteger)
{
    UINT32                  ThisDigit;
    UINT32                  ValidDigits = 0;
    UINT64                  ReturnValue = 0;


    /* Allow "0x" prefix for all hex constants */

    if ((*String == '0') &&
        (tolower ((int) *(String + 1)) == 'x'))
    {
        String += 2;    /* Go past the 0x */
        if (*String == 0)
        {
            return (AE_BAD_HEX_CONSTANT);
        }
    }

    /* Main loop: convert each ASCII byte in the input string */

    while (*String)
    {
        /* Skip all leading zeros */

        if ((ValidDigits == 0) && (*String == ACPI_ASCII_ZERO))
        {
            String++;
            continue;
        }

        /* Check for overflow (32 or 64 bit) */

        if ((ValidDigits > 16) ||
            ((ValidDigits > 8) && (MaxIntegerByteWidth <= ACPI_MAX32_BYTE_WIDTH)))
        {
            /*
             * This is ToInteger operation case.
             * No restrictions for string-to-integer conversion,
             * see ACPI spec.
             */
            return (AE_CONVERSION_OVERFLOW);
        }

        ThisDigit = (UINT8) toupper ((int) *String);
        if (!isxdigit ((int) ThisDigit))
        {
            /* Not Hex ASCII A-F or 0-9, terminate */

            return (AE_BAD_HEX_CONSTANT);
        }

        /* Convert and insert the hex digit */

        ThisDigit = AcpiUtAsciiCharToHex (ThisDigit);
        ReturnValue = (ReturnValue << 4) | ThisDigit;

        String++;
        ValidDigits++;
    }

    *RetInteger = ReturnValue;
    return (AE_OK);
}
