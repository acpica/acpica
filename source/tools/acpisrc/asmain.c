
/******************************************************************************
 * 
 * Module Name: asmain - Main module for the acpi source processor utility
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


#include "acpisrc.h"

/* Globals */

UINT32                      Gbl_Tabs = 0;
UINT32                      Gbl_NonAnsiComments = 0;
UINT32                      Gbl_Files = 0;
UINT32                      Gbl_WhiteLines = 0;
UINT32                      Gbl_CommentLines = 0;
UINT32                      Gbl_SourceLines = 0;

struct stat                 Gbl_StatBuf;
char                        *Gbl_FileBuffer;
UINT32                      Gbl_FileSize;


/******************************************************************************
 *
 * Linux-specific translation tables
 *
 ******************************************************************************/

char                        LinuxHeader[] = 
"/*\n"
" *  Copyright (C) 2000 R. Byron Moore\n"
" *\n"
" *  This program is free software; you can redistribute it and/or modify\n"
" *  it under the terms of the GNU General Public License as published by\n"
" *  the Free Software Foundation; either version 2 of the License, or\n"
" *  (at your option) any later version.\n"
" *\n"
" *  This program is distributed in the hope that it will be useful,\n"
" *  but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
" *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
" *  GNU General Public License for more details.\n"
" *\n"
" *  You should have received a copy of the GNU General Public License\n"
" *  along with this program; if not, write to the Free Software\n"
" *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA\n"
" */\n";



ACPI_STRING_TABLE           LinuxReplacementStrings[] = {

    /* Declarations first */

    "UINT32_BIT  ",     "unsigned int",

    "UINT32      ",     "unsigned int",
    "UINT16        ",   "unsigned short",
    "UINT8        ",    "unsigned char",
    "BOOLEAN      ",    "unsigned char",

    /* Now do embedded typecasts */

    "UINT32",           "unsigned int",
    "UINT16",           "unsigned short",
    "UINT8",            "unsigned char",
    "BOOLEAN",          "unsigned char",

    "INT32  ",          "int    ",
    "INT32",            "int",
    "INT16",            "short",
    "INT8",             "char", 

    /* Put back anything we broke (such as anything with _INT32_ in it) */

    "_int_",            "_INT32_",
    "_unsigned int_",   "_UINT32_",
    NULL,               NULL
};


ACPI_LINE_TABLE             LinuxLineIdentifiers[] = {

    "#define __",
    NULL
};


ACPI_CONVERSION_TABLE       LinuxConversionTable = {

    LinuxHeader,
    FLG_NO_CARRIAGE_RETURNS,

    /* C source files */

    LinuxReplacementStrings,
    LinuxLineIdentifiers,
    (CVT_COUNT_TABS | CVT_COUNT_NON_ANSI_COMMENTS | CVT_COUNT_LINES | CVT_TRIM_LINES | CVT_BRACES_ON_SAME_LINE | 
     CVT_MIXED_CASE_TO_UNDERSCORES | CVT_LOWER_CASE_IDENTIFIERS | CVT_REMOVE_DEBUG_MACROS | CVT_TRIM_WHITESPACE),

    /* C header files */

    LinuxReplacementStrings,
    NULL,
    (CVT_COUNT_TABS | CVT_COUNT_NON_ANSI_COMMENTS | CVT_COUNT_LINES | CVT_TRIM_LINES | CVT_MIXED_CASE_TO_UNDERSCORES |
     CVT_LOWER_CASE_IDENTIFIERS | CVT_TRIM_WHITESPACE),
};



/******************************************************************************
 *
 * Code cleanup translation tables
 *
 ******************************************************************************/


ACPI_CONVERSION_TABLE       CleanupConversionTable = {

    NULL,
    FLG_DEFAULT_FLAGS,

    /* C source files */

    NULL,
    NULL,
    (CVT_COUNT_TABS | CVT_COUNT_NON_ANSI_COMMENTS | CVT_COUNT_LINES | CVT_TRIM_LINES | CVT_TRIM_WHITESPACE),

    /* C header files */

    NULL,
    NULL,
    (CVT_COUNT_TABS | CVT_COUNT_NON_ANSI_COMMENTS | CVT_COUNT_LINES | CVT_TRIM_LINES | CVT_TRIM_WHITESPACE),
};






/******************************************************************************
 *
 * FUNCTION:    AsDisplayStats
 *
 * DESCRIPTION: Display global statistics gathered during translation
 *
 ******************************************************************************/

void
AsDisplayStats (void)
{

    printf ("%d Files processed\n", Gbl_Files);
    printf ("%d Tabs found\n", Gbl_Tabs);
    printf ("%d Non-ANSI comments found\n", Gbl_NonAnsiComments);
    printf ("%d Lines of code\n", Gbl_SourceLines);
    printf ("%d Lines of non-comment whitespace\n", Gbl_WhiteLines);
    printf ("%d Lines of comments\n", Gbl_CommentLines);
    printf ("%f Ratio of code to whitespace\n", ((float) Gbl_SourceLines / (float) Gbl_WhiteLines));
    printf ("%f Ratio of code to comments\n", ((float) Gbl_SourceLines / (float) Gbl_CommentLines));

    return;
}


/******************************************************************************
 *
 * FUNCTION:    AsDisplayUsage  
 *
 * DESCRIPTION: Usage message
 *
 ******************************************************************************/

void
AsDisplayUsage (void)
{

    printf ("\n");
    printf ("Usage: acpisrc [-cl] <SourceDir> <DestinationDir>\n\n");
    printf ("Where: -l            Generate Linux version of the source\n");
    printf ("       -c            Generate cleaned version of the source\n");
    printf ("\n");
    return;
}


/******************************************************************************
 *
 * FUNCTION:    main
 *
 * DESCRIPTION: C main function
 *
 ******************************************************************************/

int 
main (
    NATIVE_UINT             argc, 
    char                    *argv[])
{
    int                     j;
    ACPI_CONVERSION_TABLE   *ConversionTable;
    UINT32                  i = 1;

    
    printf ("ACPI Source Code Conversion Utility ");
    printf ("version [%s]\n", __DATE__);

    if (argc < 2)
    {
        AsDisplayUsage ();
        return 0;
    }

    /* Command line options */

    while ((j = getopt (argc, argv, "lc")) != EOF) switch(j) 
    {
    case 'l':
        printf ("Creating Linux source code\n");
        ConversionTable = &LinuxConversionTable;
        i++;
        break;

    case 'c':
        printf ("Code cleanup\n");
        ConversionTable = &CleanupConversionTable;
        i++;
        break;

    default:    
        AsDisplayUsage ();
        return -1;
    }

    if (!ConversionTable)
    {
        printf ("Code cleanup\n");
        ConversionTable = &CleanupConversionTable;
        i++;
    }


    /* Process the directory tree */

    AsProcessTree (ConversionTable, argv[i], argv[i+1]);

    AsDisplayStats ();

	return 0;
}


