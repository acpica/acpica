/******************************************************************************
 *
 * Module Name: ahmain - Main module for the acpi help utility
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2011, Intel Corp.
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

#define ACPI_CREATE_PREDEFINED_TABLE
#include "acpihelp.h"
#include "acapps.h"
#include "acpredef.h"
#include "ahops.h"


#define     AH_MAX_LINE_LENGTH      70
char        TypeBuffer[64];

static const char   *AcpiRtypeNames[] =
{
    "/Integer",
    "/String",
    "/Buffer",
    "/Package",
    "/Reference",
};


/* Local prototypes */

static void
AhStrupr (
    char                    *SrcString);

static void
AhGetExpectedTypes (
    char                    *Buffer,
    UINT32                  ExpectedBtypes);

static void
AhFindMethods (
    char                    *Name);

static void
AhFindOperators (
    char                    *Name);

static void
AhDisplayOperator (
    const char              *Op);

static void
AhDisplayUsage (
    void);


/******************************************************************************
 *
 * FUNCTION:    AhDisplayUsage
 *
 * DESCRIPTION: Usage message
 *
 ******************************************************************************/

static void
AhDisplayUsage (
    void)
{

    printf ("\n");
    printf ("Usage: acpihelp <NamePrefix>\n\n");
    printf ("Where: NamePrefix   Initial substring for ASL operator(s)\n");
    printf ("       _NamePrefix  Initial substring for predefined name(s)\n");
    printf ("\n");
    return;
}


/******************************************************************************
 *
 * FUNCTION:    main
 *
 * DESCRIPTION: C main function for AcpiHelp utility.
 *
 ******************************************************************************/

int ACPI_SYSTEM_XFACE
main (
    int                     argc,
    char                    *argv[])
{
    int                     j;
    char                    *Name;


    printf (ACPI_COMMON_SIGNON ("ACPI Help Utility"));

    if (argc < 2)
    {
        AhDisplayUsage ();
        return (0);
    }

    /* Command line options */

    while ((j = AcpiGetopt (argc, argv, "h")) != EOF) switch (j)
    {
    case 'h':
    default:
        AhDisplayUsage ();
        return (-1);
    }

    Name = argv[AcpiGbl_Optind];
    if (!Name)
    {
        printf ("Missing Name\n");
        AhDisplayUsage ();
        return (-1);
    }

    if (Name[0] == 0)
    {
        return (0);
    }

    AhStrupr (Name);
    if (*Name == '_')
    {
        AhFindMethods (Name);
    }
    else
    {
        AhFindOperators (Name);
    }
    return (0);
}


/*******************************************************************************
 *
 * FUNCTION:    AhStrupr (strupr)
 *
 * PARAMETERS:  SrcString           - The source string to convert
 *
 * RETURN:      None
 *
 * DESCRIPTION: Convert string to uppercase
 *
 * NOTE: This is not a POSIX function, so it appears here, not in utclib.c
 *
 ******************************************************************************/

static void
AhStrupr (
    char                    *SrcString)
{
    char                    *String;


    if (!SrcString)
    {
        return;
    }

    /* Walk entire string, uppercasing the letters */

    for (String = SrcString; *String; String++)
    {
        *String = (char) toupper ((int) *String);
    }

    return;
}


/*******************************************************************************
 *
 * FUNCTION:    AhFindMethods
 *
 * PARAMETERS:  Name                - Name or prefix to find. Must start with
 *                                    an underscore
 *
 * RETURN:      None
 *
 * DESCRIPTION: Find and display all ACPI predefined names that match the
 *              input name or prefix. Includes the required number of arguments
 *              and the expected return type, if any.
 *
 ******************************************************************************/

static void
AhFindMethods (
    char                    *Name)
{
    const ACPI_PREDEFINED_INFO  *ThisName;
    UINT32                      Length;
    UINT32                      i;


    Length = strlen (Name);
    if (Length > 4)
    {
        printf ("Predefined name must be 4 characters maximum\n");
        return;
    }

    /* Find all predefined names that match the name/prefix */

    ThisName = PredefinedNames;
    while (ThisName->Info.Name[0])
    {
        for (i = 0; i < Length; i++)
        {
            if (ThisName->Info.Name[i] != Name[i])
            {
                goto Continue;
            }
        }

        AhGetExpectedTypes (TypeBuffer, ThisName->Info.ExpectedBtypes);

        printf ("%4.4s: %u arguments, Returns: %s\n",
            ThisName->Info.Name, ThisName->Info.ParamCount,
            ThisName->Info.ExpectedBtypes ? TypeBuffer : "Nothing");

Continue:
        if (ThisName->Info.ExpectedBtypes & ACPI_RTYPE_PACKAGE)
        {
            ThisName++;
        }

        ThisName++;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AhGetExpectedTypes
 *
 * PARAMETERS:  Buffer              - Where the formatted string is returned
 *              ExpectedBTypes      - Bitfield of expected data types
 *
 * RETURN:      Formatted string in Buffer.
 *
 * DESCRIPTION: Format the expected object types into a printable string.
 *
 ******************************************************************************/

static void
AhGetExpectedTypes (
    char                    *Buffer,
    UINT32                  ExpectedBtypes)
{
    UINT32                  ThisRtype;
    UINT32                  i;
    UINT32                  j;


    j = 1;
    Buffer[0] = 0;
    ThisRtype = ACPI_RTYPE_INTEGER;

    for (i = 0; i < ACPI_NUM_RTYPES; i++)
    {
        /* If one of the expected types, concatenate the name of this type */

        if (ExpectedBtypes & ThisRtype)
        {
            strcat (Buffer, &AcpiRtypeNames[i][j]);
            j = 0;              /* Use name separator from now on */
        }
        ThisRtype <<= 1;    /* Next Rtype */
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AhFindOperators
 *
 * PARAMETERS:  Name                - Name or prefix for an ASL operator
 *
 * RETURN:      None
 *
 * DESCRIPTION: Find all ASL operators that match the input Name or name
 *              prefix.
 *
 ******************************************************************************/

static void
AhFindOperators (
    char                    *Name)
{
    UINT32                  i;


    for (i = 0; AslOperatorNames[i]; i++)
    {
        if (strstr (AslOperatorNames[i], Name) ==
            AslOperatorNames[i])
        {
            AhDisplayOperator (AslOperatorSyntax[i]);
        }
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AhDisplayOperator
 *
 * PARAMETERS:  Op                  - Pointer to ASL operator with syntax info
 *
 * RETURN:      None
 *
 * DESCRIPTION: Format and display syntax info for an ASL operator. Splits
 *              long lines appropriately for reading.
 *
 ******************************************************************************/

static void
AhDisplayOperator (
    const char              *Op)
{
    size_t                  TokenLength = 0;
    size_t                  Position = 0;
    const char              *This = Op;
    const char              *Next;
    const char              *Last;


    Last = This + strlen (This);
    while ((Next = strpbrk (This, " ")))
    {
        TokenLength = Next - This;
        Position += TokenLength;

        /* Split long lines */

        if (Position > AH_MAX_LINE_LENGTH)
        {
            printf ("\n    ");
            Position = TokenLength;
        }

        printf ("%.*s ", (int) TokenLength, This);
        This = Next + 1;
    }

    /* Handle last token on the input line */

    TokenLength = Last - This;
    if (TokenLength > 0)
    {
        Position += TokenLength;
        if (Position > AH_MAX_LINE_LENGTH)
        {
            printf ("\n    ");
        }
        printf ("%s\n", This);
    }
}
