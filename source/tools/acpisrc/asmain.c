
/******************************************************************************
 *
 * Module Name: asmain - Main module for the acpi source processor utility
 *              $Revision: 1.30 $
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999, 2000, 2001, Intel Corp.
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


#include "acpisrc.h"


/* Globals */

UINT32                  Gbl_Tabs = 0;
UINT32                  Gbl_MissingBraces = 0;
UINT32                  Gbl_NonAnsiComments = 0;
UINT32                  Gbl_Files = 0;
UINT32                  Gbl_WhiteLines = 0;
UINT32                  Gbl_CommentLines = 0;
UINT32                  Gbl_SourceLines = 0;
UINT32                  Gbl_LongLines = 0;
UINT32                  Gbl_TotalLines = 0;

struct stat             Gbl_StatBuf;
char                    *Gbl_FileBuffer;
UINT32                  Gbl_FileSize;
BOOLEAN                 Gbl_VerboseMode = FALSE;
BOOLEAN                 Gbl_BatchMode = FALSE;
BOOLEAN                 Gbl_DebugStatementsMode = FALSE;
BOOLEAN                 Gbl_MadeChanges = FALSE;
BOOLEAN                 Gbl_Overwrite = FALSE;


/******************************************************************************
 *
 * Standard/Common translation tables
 *
 ******************************************************************************/


ACPI_STRING_TABLE           StandardDataTypes[] = {

    /* Declarations first */

    "UINT32_BIT  ",     "unsigned int",     REPLACE_SUBSTRINGS,

    "UINT32      ",     "unsigned int",     REPLACE_SUBSTRINGS,
    "UINT16        ",   "unsigned short",   REPLACE_SUBSTRINGS,
    "UINT8        ",    "unsigned char",    REPLACE_SUBSTRINGS,
    "BOOLEAN      ",    "unsigned char",    REPLACE_SUBSTRINGS,

    /* Now do embedded typecasts */

    "UINT32",           "unsigned int",     REPLACE_SUBSTRINGS,
    "UINT16",           "unsigned short",   REPLACE_SUBSTRINGS,
    "UINT8",            "unsigned char",    REPLACE_SUBSTRINGS,
    "BOOLEAN",          "unsigned char",    REPLACE_SUBSTRINGS,

    "INT32  ",          "int    ",          REPLACE_SUBSTRINGS,
    "INT32",            "int",              REPLACE_SUBSTRINGS,
    "INT16",            "short",            REPLACE_SUBSTRINGS,
    "INT8",             "char",             REPLACE_SUBSTRINGS,

    /* Put back anything we broke (such as anything with _INT32_ in it) */

    "_int_",            "_INT32_",          REPLACE_SUBSTRINGS,
    "_unsigned int_",   "_UINT32_",         REPLACE_SUBSTRINGS,
    NULL,               NULL,               0
};


/******************************************************************************
 *
 * Linux-specific translation tables
 *
 ******************************************************************************/

char                        LinuxHeader[] =
"/*\n"
" *  Copyright (C) 2000, 2001 R. Byron Moore\n"
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


ACPI_STRING_TABLE           LinuxDataTypes[] = {

    /* Declarations first */

    "UINT32_BIT  ",             "u32         ",             REPLACE_WHOLE_WORD,

    "UINT32      ",             "u32         ",             REPLACE_WHOLE_WORD,
    "UINT16      ",             "u16         ",             REPLACE_WHOLE_WORD,
    "UINT8       ",             "u8          ",             REPLACE_WHOLE_WORD,
    "BOOLEAN     ",             "u8          ",             REPLACE_WHOLE_WORD,

    /* Now do embedded typecasts */

    "UINT32",                   "u32",                      REPLACE_WHOLE_WORD,
    "UINT16",                   "u16",                      REPLACE_WHOLE_WORD,
    "UINT8",                    "u8",                       REPLACE_WHOLE_WORD,
    "BOOLEAN",                  "u8",                       REPLACE_WHOLE_WORD,

    "INT32  ",                  "s32    ",                  REPLACE_WHOLE_WORD,
    "INT32",                    "s32",                      REPLACE_WHOLE_WORD,
    "INT16  ",                  "s16    ",                  REPLACE_WHOLE_WORD,
    "INT8   ",                  "s8     ",                  REPLACE_WHOLE_WORD,
    "INT16",                    "s16",                      REPLACE_WHOLE_WORD,
    "INT8",                     "s8",                       REPLACE_WHOLE_WORD,

    /* Put back anything we broke (such as anything with _INTxx_ in it) */

/* No longer needed?

    "_s32_",                    "_INT32_",          REPLACE_SUBSTRINGS,
    "_u32_",                    "_UINT32_",          REPLACE_SUBSTRINGS,
    "_s16_",                    "_INT16_",          REPLACE_SUBSTRINGS,
    "_u16_",                    "_UINT16_",          REPLACE_SUBSTRINGS,
    "_s8_",                     "_INT8_",          REPLACE_SUBSTRINGS,
    "_u8_",                     "_UINT8_",          REPLACE_SUBSTRINGS,
*/


    "ACPI_STATUS",              "acpi_status",                  REPLACE_WHOLE_WORD,
    /*"ACPI_IO_ADDRESS  ",        "acpi_io_address  ",*/
    /*"ACPI_PHYSICAL_ADDRESS  ",  "acpi_physical_address  ",*/
    /*"NATIVE_UINT  ",            "native_uint  ",*/
    /*"NATIVE_INT  ",             "native_int  ",*/
    /*"NATIVE_CHAR  ",            "native_char  ",*/
    "ACPI_NAME",                "acpi_name",                  REPLACE_WHOLE_WORD,
    "ACPI_STRING",              "acpi_string",                REPLACE_WHOLE_WORD,
    "ACPI_HANDLE",              "acpi_handle",                REPLACE_WHOLE_WORD,
    "ACPI_INTEGER",             "acpi_integer",               REPLACE_WHOLE_WORD,
    "ACPI_OBJECT_TYPE",         "acpi_object_type",           REPLACE_WHOLE_WORD,
    "ACPI_OBJECT_TYPE8",        "acpi_object_type8",          REPLACE_WHOLE_WORD,
    "OPERATING_MODE",           "operating_mode",             REPLACE_WHOLE_WORD,
    "ACPI_EVENT_STATUS",        "acpi_event_status",          REPLACE_WHOLE_WORD,
    "ACPI_OWNER_ID",            "acpi_owner_id",              REPLACE_WHOLE_WORD,
    "ACPI_TABLE_TYPE",          "acpi_table_type",            REPLACE_WHOLE_WORD,

    "ACPI_NAMESPACE_NODE",      "acpi_namespace_node",          REPLACE_WHOLE_WORD,
    "ACPI_OPERAND_OBJECT",      "acpi_operand_object",          REPLACE_WHOLE_WORD,
    "ACPI_GENERIC_STATE",       "acpi_generic_state",           REPLACE_WHOLE_WORD,
    "ACPI_WALK_STATE",          "acpi_walk_state",              REPLACE_WHOLE_WORD,
    "ACPI_GPE_LEVEL_INFO",      "acpi_gpe_level_info",          REPLACE_WHOLE_WORD,
    "ACPI_PARSE_OBJECT",        "acpi_parse_object",            REPLACE_WHOLE_WORD,
    "ACPI_WALK_LIST",           "acpi_walk_list",               REPLACE_WHOLE_WORD,
    "ACPI_PARSE_STATE",         "acpi_parse_state",             REPLACE_WHOLE_WORD,
    "ACPI_BUFFER",              "acpi_buffer",                  REPLACE_WHOLE_WORD,
    "ACPI_OBJECT_LIST",         "acpi_object_list",             REPLACE_WHOLE_WORD,
    "ACPI_OPCODE_INFO",         "acpi_opcode_info",             REPLACE_WHOLE_WORD,
    "PREDEFINED_NAMES",         "predefined_names",             REPLACE_WHOLE_WORD,
    "DB_METHOD_INFO",           "db_method_info",               REPLACE_WHOLE_WORD,
    "ACPI_PARSE2_OBJECT",       "acpi_parse2_object",           REPLACE_WHOLE_WORD,
    "ACPI_PARSE_DOWNWARDS",     "acpi_parse_downwards",         REPLACE_WHOLE_WORD,
    "ACPI_PARSE_UPWARDS",       "acpi_parse_upwards",           REPLACE_WHOLE_WORD,
    "ACPI_GENERIC_ADDRESS",     "acpi_generic_address",         REPLACE_WHOLE_WORD,
    "PCI_ROUTING_TABLE",        "pci_routing_table",            REPLACE_WHOLE_WORD,
    "ACPI_RESOURCE_DATA",       "acpi_resource_data",           REPLACE_WHOLE_WORD,
    "ACPI_RESOURCE_IRQ",        "acpi_resource_irq",            REPLACE_WHOLE_WORD,
    "ACPI_RESOURCE_DMA",        "acpi_resource_dma",            REPLACE_WHOLE_WORD,
    "ACPI_RESOURCE_START_DPF",  "acpi_resource_start_dpf",      REPLACE_WHOLE_WORD,
    "ACPI_RESOURCE_IO",         "acpi_resource_io",             REPLACE_WHOLE_WORD,
    "ACPI_RESOURCE_FIXED_IO",   "acpi_resource_fixed_io",       REPLACE_WHOLE_WORD,
    "ACPI_RESOURCE_VENDOR",     "acpi_resource_vendor",         REPLACE_WHOLE_WORD,
    "ACPI_RESOURCE_MEM24",      "acpi_resource_mem24",          REPLACE_WHOLE_WORD,
    "ACPI_RESOURCE_MEM32",      "acpi_resource_mem32",          REPLACE_WHOLE_WORD,
    "ACPI_RESOURCE_FIXED_MEM32","acpi_resource_fixed_mem32",    REPLACE_WHOLE_WORD,
    "ACPI_RESOURCE_TYPE",       "acpi_resource_type",           REPLACE_WHOLE_WORD,
    "ACPI_MEMORY_ATTRIBUTE",	"acpi_memory_attribute",        REPLACE_WHOLE_WORD,
    "ACPI_IO_ATTRIBUTE",        "acpi_io_attribute",            REPLACE_WHOLE_WORD,
    "ACPI_BUS_ATTRIBUTE",       "acpi_bus_attribute",           REPLACE_WHOLE_WORD,
    "ACPI_RESOURCE_ATTRIBUTE",	"acpi_resource_attribute",      REPLACE_WHOLE_WORD,
    "ACPI_RESOURCE_SOURCE",     "acpi_resource_source",         REPLACE_WHOLE_WORD,
    "ACPI_RESOURCE_ADDRESS16",  "acpi_resource_address16",      REPLACE_WHOLE_WORD,
    "ACPI_RESOURCE_ADDRESS32",  "acpi_resource_address32",      REPLACE_WHOLE_WORD,
    "ACPI_RESOURCE_ADDRESS64",  "acpi_resource_address64",      REPLACE_WHOLE_WORD,
    "ACPI_RESOURCE_EXT_IRQ",    "acpi_resource_ext_irq",        REPLACE_WHOLE_WORD,
    "ACPI_RESOURCE ",           "acpi_resource ",               REPLACE_WHOLE_WORD,/* Must be last resource desc */
    "ACPI_SYSTEM_INFO",         "acpi_system_info",             REPLACE_WHOLE_WORD,
    "ACPI_TABLE_DESC",          "acpi_table_desc",              REPLACE_WHOLE_WORD,
    "XSDT_DESCRIPTOR",          "xsdt_descriptor",              REPLACE_WHOLE_WORD,
    "FADT_DESCRIPTOR_REV071",   "fadt_descriptor_rev071",       REPLACE_WHOLE_WORD,
    "FADT_DESCRIPTOR_REV1",     "fadt_descriptor_rev1",         REPLACE_WHOLE_WORD,
    "FADT_DESCRIPTOR_REV2",     "fadt_descriptor_rev2",         REPLACE_WHOLE_WORD,
    "ACPI_COMMON_FACS",         "acpi_common_facs",             REPLACE_WHOLE_WORD,
    "FACS_DESCRIPTOR_REV071",   "facs_descriptor_rev071",       REPLACE_WHOLE_WORD,
    "FACS_DESCRIPTOR_REV1",     "facs_descriptor_rev1",         REPLACE_WHOLE_WORD,
    "FACS_DESCRIPTOR_REV2",     "facs_descriptor_rev2",         REPLACE_WHOLE_WORD,
    "ACPI_TABLE_HEADER",        "acpi_table_header",            REPLACE_WHOLE_WORD,
    "ACPI_PKG_INFO",            "acpi_pkg_info",                REPLACE_WHOLE_WORD,
    "ACPI_EVENT_TYPE",          "acpi_event_type",              REPLACE_WHOLE_WORD,
    "ACPI_DEVICE_INFO",         "acpi_device_info",             REPLACE_WHOLE_WORD,
    "ACPI_PCI_ID",              "acpi_pci_id",                  REPLACE_WHOLE_WORD,
    "ACPI_MEM_SPACE_CONTEXT",   "acpi_mem_space_context",       REPLACE_WHOLE_WORD,
    "ACPI_OBJ_INFO_HEADER",     "acpi_obj_info_header",         REPLACE_WHOLE_WORD,
    "UINT64_STRUCT",            "uint64_struct",                REPLACE_WHOLE_WORD,

    /* Typecasts */

    "ACPI_STATUS",              "acpi_status",                  REPLACE_WHOLE_WORD,
    /*"ACPI_IO_ADDRESS)",         "acpi_io_address)",*/
    /*"ACPI_PHYSICAL_ADDRESS)",   "acpi_physical_address)",*/
    /*"NATIVE_UINT)",             "native_uint)",*/
    /*"NATIVE_INT)",              "native_int)",*/
    /*"NATIVE_CHAR)",             "native_char)",*/
    "ACPI_NAME",               "acpi_name",                     REPLACE_WHOLE_WORD,
    "ACPI_STRING",             "acpi_string",                   REPLACE_WHOLE_WORD,
    "ACPI_HANDLE",             "acpi_handle",                   REPLACE_WHOLE_WORD,
    "ACPI_INTEGER",            "acpi_integer",                  REPLACE_WHOLE_WORD,
    "ACPI_OBJECT_TYPE",        "acpi_object_type",              REPLACE_WHOLE_WORD,
    "ACPI_OBJECT_TYPE8",       "acpi_object_type8",             REPLACE_WHOLE_WORD,
    "OPERATING_MODE",          "operating_mode",                REPLACE_WHOLE_WORD,
    "ACPI_EVENT_STATUS",       "acpi_event_status",             REPLACE_WHOLE_WORD,
    "ACPI_OWNER_ID",           "acpi_owner_id",                 REPLACE_WHOLE_WORD,
    "ACPI_TABLE_TYPE",         "acpi_table_type",               REPLACE_WHOLE_WORD,
    "ACPI_RESOURCE",           "acpi_resource",                 REPLACE_WHOLE_WORD,


    /*
     * Function return values.
     * This is fragile. We have to put these in to get it to compile, BUT
     * we can't put all tokens here, because that will break strings where
     * we want to convert FOO but not FOO_MAX_LEN, for example.
     */
    "ACPI_OWNER_ID",           "acpi_owner_id",                 REPLACE_WHOLE_WORD,
    "ACPI_OBJECT_TYPE8",       "acpi_object_type8",             REPLACE_WHOLE_WORD,
    "ACPI_HANDLE",             "acpi_handle",                   REPLACE_WHOLE_WORD,
    "ACPI_NAME\n",             "acpi_name\n",                   REPLACE_WHOLE_WORD,
    "ACPI_NAME ",              "acpi_name ",                    REPLACE_WHOLE_WORD,
    "ACPI_OBJECT",             "acpi_object",                   REPLACE_WHOLE_WORD,
    "ACPI_RESOURCE,",          "acpi_resource,",                REPLACE_WHOLE_WORD,

    NULL,                       NULL
};


ACPI_IDENTIFIER_TABLE       LinuxLineIdentifiers[] = {

    "#define __",
    NULL
};


ACPI_IDENTIFIER_TABLE       LinuxConditionalIdentifiers[] = {

//    "ACPI_USE_STANDARD_HEADERS",
    "WIN32",
    "_MSC_VER",
    NULL
};

ACPI_CONVERSION_TABLE       LinuxConversionTable = {

    LinuxHeader,
    FLG_NO_CARRIAGE_RETURNS | FLG_LOWERCASE_DIRNAMES,

    /* C source files */

    LinuxDataTypes,
    LinuxLineIdentifiers,
    NULL,
    (CVT_COUNT_TABS | CVT_COUNT_NON_ANSI_COMMENTS | CVT_COUNT_LINES | CVT_CHECK_BRACES | CVT_TRIM_LINES | CVT_BRACES_ON_SAME_LINE |
     CVT_MIXED_CASE_TO_UNDERSCORES | CVT_LOWER_CASE_IDENTIFIERS | CVT_REMOVE_DEBUG_MACROS | CVT_TRIM_WHITESPACE |
     CVT_REMOVE_EMPTY_BLOCKS | CVT_SPACES_TO_TABS8),

    /* C header files */

    LinuxDataTypes,
    NULL,
    LinuxConditionalIdentifiers,
    (CVT_COUNT_TABS | CVT_COUNT_NON_ANSI_COMMENTS | CVT_COUNT_LINES | CVT_TRIM_LINES | CVT_MIXED_CASE_TO_UNDERSCORES |
     CVT_LOWER_CASE_IDENTIFIERS | CVT_TRIM_WHITESPACE |
     CVT_REMOVE_EMPTY_BLOCKS| CVT_SPACES_TO_TABS8),
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
    NULL,
    (CVT_COUNT_TABS | CVT_COUNT_NON_ANSI_COMMENTS | CVT_COUNT_LINES | CVT_CHECK_BRACES | CVT_TRIM_LINES | CVT_TRIM_WHITESPACE),

    /* C header files */

    NULL,
    NULL,
    NULL,
    (CVT_COUNT_TABS | CVT_COUNT_NON_ANSI_COMMENTS | CVT_COUNT_LINES | CVT_TRIM_LINES | CVT_TRIM_WHITESPACE),
};


ACPI_CONVERSION_TABLE       StatsConversionTable = {

    NULL,
    FLG_NO_FILE_OUTPUT,

    /* C source files */

    NULL,
    NULL,
    NULL,
    (CVT_COUNT_TABS | CVT_COUNT_NON_ANSI_COMMENTS | CVT_COUNT_LINES),

    /* C header files */

    NULL,
    NULL,
    NULL,
    (CVT_COUNT_TABS | CVT_COUNT_NON_ANSI_COMMENTS | CVT_COUNT_LINES),
};


/******************************************************************************
 *
 * Customizable translation tables
 *
 ******************************************************************************/

ACPI_STRING_TABLE           CustomReplacements[] = {


    "2000, 2001, Intel Corp",     "2000, 2001, Intel Corp",     REPLACE_WHOLE_WORD,
    "ACPI_TYPE_INTEGER",     "ACPI_TYPE_INTEGER",               REPLACE_WHOLE_WORD,
    "ARGI_INTEGER",          "ARGI_INTEGER",                    REPLACE_WHOLE_WORD,
    "ARGP_INTEGER",          "ARGP_INTEGER",                    REPLACE_WHOLE_WORD,
    "ACPI_BTYPE_INTEGER",    "ACPI_BTYPE_INTEGER",              REPLACE_WHOLE_WORD,
    "ACPI_OBJECT_INTEGER",   "ACPI_OBJECT_INTEGER",             REPLACE_WHOLE_WORD,
    "->Integer",             "->Integer",                       REPLACE_WHOLE_WORD,
    NULL,                   NULL, 0
};


ACPI_CONVERSION_TABLE       CustomConversionTable = {

    NULL,
    FLG_DEFAULT_FLAGS,

    /* C source files */

    CustomReplacements,
    NULL,
    NULL,
    (CVT_COUNT_TABS | CVT_COUNT_NON_ANSI_COMMENTS | CVT_COUNT_LINES | CVT_TRIM_LINES | CVT_TRIM_WHITESPACE),

    /* C header files */

    CustomReplacements,
    NULL,
    NULL,
    (CVT_COUNT_TABS | CVT_COUNT_NON_ANSI_COMMENTS | CVT_COUNT_LINES | CVT_TRIM_LINES | CVT_TRIM_WHITESPACE),
};


/******************************************************************************
 *
 * FUNCTION:    AsExaminePaths
 *
 * DESCRIPTION: Source and Target pathname verification and handling
 *
 ******************************************************************************/

int
AsExaminePaths (
    ACPI_CONVERSION_TABLE   *ConversionTable,
    char                    *Source,
    char                    *Target,
    UINT32                  *SourceFileType)
{
    int                     Status;
    int                     Response;


    Status = stat (Source, &Gbl_StatBuf);
    if (Status)
    {
        printf ("Source path \"%s\" does not exist\n", Source);
        return -1;
    }

    /* Return the filetype -- file or a directory */

    *SourceFileType = 0;
    if (Gbl_StatBuf.st_mode & _S_IFDIR)
    {
        *SourceFileType = _S_IFDIR;
    }

    /*
     * If we are in no-output mode or in batch mode, we are done
     */
    if ((ConversionTable->Flags & FLG_NO_FILE_OUTPUT) ||
        (Gbl_BatchMode))
    {
        return 0;
    }


    if (!stricmp (Source, Target))
    {
        printf ("Target path is the same as the source path, overwrite?\n");
        scanf ("%c", &Response);

        /* Check response */

        if ((char) Response != 'y')
        {
            return -1;
        }

        Gbl_Overwrite = TRUE;
    }

    else
    {
        Status = stat (Target, &Gbl_StatBuf);
        if (!Status)
        {
            printf ("Target path already exists, overwrite?\n");
            scanf ("%c", &Response);

            /* Check response */

            if ((char) Response != 'y')
            {
                return -1;
            }
        }
    }

    return 0;
}


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

    printf ("\nAcpiSrc statistics:\n\n");
    printf ("%6d Files processed\n", Gbl_Files);
    printf ("%6d Tabs found\n", Gbl_Tabs);
    printf ("%6d Missing if/else braces\n", Gbl_MissingBraces);
    printf ("%6d Non-ANSI comments found\n", Gbl_NonAnsiComments);
    printf ("%6d Total Lines\n", Gbl_TotalLines);
    printf ("%6d Lines of code\n", Gbl_SourceLines);
    printf ("%6d Lines of non-comment whitespace\n", Gbl_WhiteLines);
    printf ("%6d Lines of comments\n", Gbl_CommentLines);
    printf ("%6d Long lines found\n", Gbl_LongLines);
    printf ("%6.1f Ratio of code to whitespace\n", ((float) Gbl_SourceLines / (float) Gbl_WhiteLines));
    printf ("%6.1f Ratio of code to comments\n", ((float) Gbl_SourceLines / (float) Gbl_CommentLines));

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
    printf ("Usage: acpisrc [-c|l|u] [-dsvy] <SourceDir> <DestinationDir>\n\n");
    printf ("Where: -c          Generate cleaned version of the source\n");
    printf ("       -l          Generate Linux version of the source\n");
    printf ("       -u          Generate Custom source translation\n");
    printf ("\n");
    printf ("       -d          Leave debug statements in code\n");
    printf ("       -s          Generate source statistics only\n");
    printf ("       -v          Verbose mode\n");
    printf ("       -y          Suppress file overwrite prompts\n");
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
    ACPI_CONVERSION_TABLE   *ConversionTable = NULL;
    char                    *SourcePath;
    char                    *TargetPath;
    UINT32                  FileType;


    printf ("ACPI Source Code Conversion Utility ");
    printf ("version [%s]\n", __DATE__);

    if (argc < 2)
    {
        AsDisplayUsage ();
        return 0;
    }

    /* Command line options */

    while ((j = getopt (argc, argv, "lcsuvyd")) != EOF) switch(j)
    {
    case 'l':
        /* Linux code generation */

        printf ("Creating Linux source code\n");
        ConversionTable = &LinuxConversionTable;
        break;

    case 'c':
        /* Cleanup code */

        printf ("Code cleanup\n");
        ConversionTable = &CleanupConversionTable;
        break;

    case 's':
        /* Statistics only */

        break;

    case 'u':
        /* custom conversion  */

        printf ("Custom source translation\n");
        ConversionTable = &CustomConversionTable;
        break;

    case 'v':
        /* Verbose mode */

        Gbl_VerboseMode = TRUE;
        break;

    case 'y':
        /* Batch mode */

        Gbl_BatchMode = TRUE;
        break;

    case 'd':
        /* Leave debug statements in */

        Gbl_DebugStatementsMode = TRUE;
        break;

    default:
        AsDisplayUsage ();
        return -1;
    }


    SourcePath = argv[optind];
    if (!SourcePath)
    {
        printf ("Missing source path\n");
        AsDisplayUsage ();
        return -1;
    }

    TargetPath = argv[optind+1];

    if (!ConversionTable)
    {
        /* Just generate statistics.  Ignore target path */

        TargetPath = SourcePath;

        printf ("Source code statistics only\n");
        ConversionTable = &StatsConversionTable;
    }

    else if (!TargetPath)
    {
        TargetPath = SourcePath;
    }

    if (Gbl_DebugStatementsMode)
    {
        ConversionTable->SourceFunctions &= ~CVT_REMOVE_DEBUG_MACROS;
    }


    /* Check source and target paths and files */

    if (AsExaminePaths (ConversionTable, SourcePath, TargetPath, &FileType))
    {
        return -1;
    }

    /* Source/target can be either directories or a files */

    if (FileType == _S_IFDIR)
    {
        /* Process the directory tree */

        AsProcessTree (ConversionTable, SourcePath, TargetPath);
    }

    else
    {
        /* Process a single file */

        /* TBD: Need to differentiate between source and header files !! */

        AsProcessOneFile (ConversionTable, NULL, TargetPath, 0, SourcePath, FILE_TYPE_SOURCE);
    }

    /* Always display final summary and stats */

    AsDisplayStats ();

    return 0;
}
