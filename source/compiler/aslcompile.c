
/******************************************************************************
 *
 * Module Name: aslcompile - top level compile module
 *              $Revision: 1.28 $
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


#include "aslcompiler.h"
#include "acnamesp.h"
#include "acdebug.h"

#define _COMPONENT          ACPI_COMPILER
        MODULE_NAME         ("aslcompile")


#undef HIWORD
#undef LOWORD
#undef HIBYTE
#undef LOBYTE
#include <time.h>
#ifdef WIN32
#include <windows.h>
#include <winbase.h>
#endif

struct tm                   *NewTime;
time_t                      Aclock;

#ifdef WIN32
SYSTEMTIME                 SysTime;
#endif

typedef struct
{
    time_t                  StartTime;
    time_t                  EndTime;
    char                    *EventName;

} ASL_EVENT_INFO;

ASL_EVENT_INFO              AslGbl_Events[20];


#ifdef WIN32

#define ASL_START_EVENT(a,b)    {AslGbl_Events[a].StartTime = AnGetTimeMs();\
                                  AslGbl_Events[a].EventName = b;}
#define ASL_END_EVENT(a)        {AslGbl_Events[a].EndTime = AnGetTimeMs();}


UINT32
AnGetTimeMs (void)
{
    GetSystemTime (&SysTime);
    return ((SysTime.wMinute * 60000) +
        (SysTime.wSecond * 1000) +
        SysTime.wMilliseconds);
}

#else

#define ASL_START_EVENT(a,b)
#define ASL_END_EVENT(a)

#endif

/*
 * Stubs to simplify linkage to the
 * ACPI Namespace Manager (Unused functions).
 */


void
AcpiExUnlinkMutex (
    ACPI_OPERAND_OBJECT     *ObjDesc)
{
}

void
AcpiTbDeleteAcpiTables (void)
{
}


BOOLEAN
AcpiTbSystemTablePointer (
    void                    *Where)
{
    return FALSE;

}

void
AcpiExDumpOperands (
    ACPI_OPERAND_OBJECT     **Operands,
    OPERATING_MODE          InterpreterMode,
    NATIVE_CHAR             *Ident,
    UINT32                  NumLevels,
    NATIVE_CHAR             *Note,
    NATIVE_CHAR             *ModuleName,
    UINT32                  LineNumber)
{
}

ACPI_STATUS
AcpiExDumpOperand (
    ACPI_OPERAND_OBJECT     *EntryDesc)
{
    return AE_OK;
}


/*******************************************************************************
 *
 * FUNCTION:    AslCompilerSignon
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display compiler signon
 *
 ******************************************************************************/

void
AslCompilerSignon (
    UINT32                  FileId)
{

    FlPrintFile (FileId,
        "\n%s %s [%s]\n%s\nSupports ACPI Specification Revision 2.0\n\n",
        CompilerId, CompilerVersion, __DATE__, CompilerCopyright);

}


/*******************************************************************************
 *
 * FUNCTION:    AslCompilerFileHeader
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Header used at the beginning of output files
 *
 ******************************************************************************/

void
AslCompilerFileHeader (
    UINT32                  FileId)
{

    time (&Aclock);
    NewTime = localtime (&Aclock);

    FlPrintFile (FileId,
        "Compilation of \"%s\" - %s\n",
        Gbl_Files[ASL_FILE_INPUT].Filename, asctime (NewTime));

}


/*******************************************************************************
 *
 * FUNCTION:    CmDoCompile
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status (0 = OK)
 *
 * DESCRIPTION: This procedure performs the entire compile
 *
 ******************************************************************************/

int
CmDoCompile (void)
{
    ACPI_STATUS             Status;


    ASL_START_EVENT (12, "Total Compile time");
    ASL_START_EVENT (0, "Open files");

    /* Open the required input and output files */

    Status = FlOpenInputFile (Gbl_Files[ASL_FILE_INPUT].Filename);
    if (ACPI_FAILURE (Status))
    {
        AePrintErrorLog (ASL_FILE_STDERR);
        return -1;
    }

    Status = FlOpenMiscOutputFiles (Gbl_OutputFilenamePrefix);
    if (ACPI_FAILURE (Status))
    {
        AePrintErrorLog (ASL_FILE_STDERR);
        return -1;
    }


    ASL_END_EVENT (0);

    /* ACPI CA subsystem initialization */

    ASL_START_EVENT (1, "ACPI CA Init");
    AcpiUtInitGlobals ();
    AcpiUtMutexInitialize ();
    AcpiNsRootInitialize ();
    ASL_END_EVENT (1);

    /* Build the parse tree */

    ASL_START_EVENT (2, "Build parse tree");

    AslCompilerparse();
    ASL_END_EVENT (2);


    /* Generate AML opcodes corresponding to the parse tokens */

    ASL_START_EVENT (3, "Generate AML opcodes");
    DbgPrint (ASL_DEBUG_OUTPUT, "\nGenerating AML opcodes\n\n");
    TrWalkParseTree (RootNode, ASL_WALK_VISIT_UPWARD, NULL, OpcAmlOpcodeWalk, NULL);
    ASL_END_EVENT (3);


    /* Calculate all AML package lengths */

    ASL_START_EVENT (4, "Generate AML package lengths");
    DbgPrint (ASL_DEBUG_OUTPUT, "\nGenerating Package lengths\n\n");
    TrWalkParseTree (RootNode, ASL_WALK_VISIT_UPWARD, NULL, LnPackageLengthWalk, NULL);
    ASL_END_EVENT (4);


    if (Gbl_ParseOnlyFlag)
    {
        AePrintErrorLog (ASL_FILE_STDOUT);
        UtDisplaySummary (ASL_FILE_STDOUT);
        if (Gbl_DebugFlag)
        {
            /* Print error summary to the debug file */

            AePrintErrorLog (ASL_FILE_STDERR);
            UtDisplaySummary (ASL_FILE_STDERR);
        }
        return 0;
    }


    /*
     * Create an internal namespace and use it as a symbol table
     */

    /* Namespace loading */

    ASL_START_EVENT (5, "Load ACPI Namespace");
    LdLoadNamespace ();
    ASL_END_EVENT (5);


    /* Namespace lookup */

    ASL_START_EVENT (6, "Cross reference ACPI Namespace");
    LkCrossReferenceNamespace ();
    ASL_END_EVENT (6);

    /*
     * Semantic error checking.  This must happen only after the
     * namespace has been loaded and cross-referenced.
     *
     * part one - check control methods
     */

    ASL_START_EVENT (7, "Check method return types");
    AnalysisWalkInfo.MethodStack = NULL;

    DbgPrint (ASL_DEBUG_OUTPUT, "\nSemantic analysis - Method analysis\n\n");
    TrWalkParseTree (RootNode, ASL_WALK_VISIT_TWICE, AnMethodAnalysisWalkBegin,
                        AnMethodAnalysisWalkEnd, &AnalysisWalkInfo);
    ASL_END_EVENT (7);


    /* Semantic error checking part two - typing of method returns */

    ASL_START_EVENT (8, "Determine type(s) returned by methods");
    DbgPrint (ASL_DEBUG_OUTPUT, "\nSemantic analysis - Method typing \n\n");
    TrWalkParseTree (RootNode, ASL_WALK_VISIT_TWICE, AnMethodTypingWalkBegin,
                        AnMethodTypingWalkEnd, NULL);
    ASL_END_EVENT (8);

    /* Semantic error checking part three - operand type checking */

    ASL_START_EVENT (9, "Operand type checking");
    DbgPrint (ASL_DEBUG_OUTPUT, "\nSemantic analysis - Operand type checking \n\n");
    TrWalkParseTree (RootNode, ASL_WALK_VISIT_TWICE, AnSemanticAnalysisWalkBegin,
                        AnSemanticAnalysisWalkEnd, &AnalysisWalkInfo);
    ASL_END_EVENT (9);


    /* Calculate all AML package lengths */

    ASL_START_EVENT (10, "Finish AML package length generation");
    DbgPrint (ASL_DEBUG_OUTPUT, "\nGenerating Package lengths\n\n");
    TrWalkParseTree (RootNode, ASL_WALK_VISIT_UPWARD, NULL, LnInitLengthsWalk, NULL);
    TrWalkParseTree (RootNode, ASL_WALK_VISIT_UPWARD, NULL, LnPackageLengthWalk, NULL);
    ASL_END_EVENT (10);


    /*
     * Now that the input is parsed, we can open the AML output file.
     * Note: by default, the name of this file comes from the table descriptor
     * within the input file.
     */
    Status = FlOpenAmlOutputFile (Gbl_OutputFilenamePrefix);
    if (ACPI_FAILURE (Status))
    {
        AePrintErrorLog (ASL_FILE_STDERR);
        return -1;
    }


    /* Code generation - emit the AML */

    ASL_START_EVENT (11, "AML code generation");
    CgGenerateAmlOutput ();
    ASL_END_EVENT (11);


    /* Dump the AML as hex if requested */

    LsDoHexOutput ();

    /* Dump the namespace to the .nsp file if requested */

    LsDisplayNamespace ();
    ASL_END_EVENT (12);


    CmCleanupAndExit ();

    return 0;
}


/*******************************************************************************
 *
 * FUNCTION:    CmCleanupAndExit
 *
 * PARAMETERS:  None
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Close all open files and exit the compiler
 *
 ******************************************************************************/

void
CmCleanupAndExit (void)
{
    UINT32                  i;


    AePrintErrorLog (ASL_FILE_STDOUT);
    if (Gbl_DebugFlag)
    {
        /* Print error summary to the debug file */

        AePrintErrorLog (ASL_FILE_STDERR);
    }

    DbgPrint (ASL_DEBUG_OUTPUT, "\n\nElapsed time for major events\n\n");
    for (i = 0; i < 13; i++)
    {
        DbgPrint (ASL_DEBUG_OUTPUT, "%8d ms - %s\n",
            AslGbl_Events[i].EndTime -
            AslGbl_Events[i].StartTime,
            AslGbl_Events[i].EventName);
    }

    if (Gbl_CompileTimesFlag)
    {
        printf ("\nElapsed time for major events\n\n");
        for (i = 0; i < 13; i++)
        {
            printf ("%8d ms - %s\n",
                AslGbl_Events[i].EndTime -
                AslGbl_Events[i].StartTime,
                AslGbl_Events[i].EventName);
        }
    }

    if (Gbl_NsLookupCount)
    {
        DbgPrint (ASL_DEBUG_OUTPUT, "\n\nMiscellaneous compile statistics\n\n");
        DbgPrint (ASL_DEBUG_OUTPUT, "%32s : %d\n", "Total Namespace searches", Gbl_NsLookupCount);
        DbgPrint (ASL_DEBUG_OUTPUT, "%32s : %d\n", "Time per search",
                        ((AslGbl_Events[7].EndTime - AslGbl_Events[7].StartTime) * 1000) /
                        Gbl_NsLookupCount);
    }


    if (Gbl_ListingFlag)
    {
        /* Flush any final AML in the buffer */

        LsFlushListingBuffer ();

        /* Print a summary of the compile exceptions */

        FlPrintFile (ASL_FILE_LISTING_OUTPUT, "\n\nSummary of errors and warnings\n\n");
        AePrintErrorLog (ASL_FILE_LISTING_OUTPUT);
        FlPrintFile (ASL_FILE_LISTING_OUTPUT, "\n\n");
        UtDisplaySummary (ASL_FILE_LISTING_OUTPUT);
        FlPrintFile (ASL_FILE_LISTING_OUTPUT, "\n\n");
    }


    /* Close all open files */

    for (i = 2; i < ASL_MAX_FILE; i++)
    {
        FlCloseFile (i);
    }


    /*
     * TBD: SourceOutput should be .TMP, then rename if we want to keep it?
     */
    if (!Gbl_SourceOutputFlag)
    {
        unlink (Gbl_Files[ASL_FILE_SOURCE_OUTPUT].Filename);
    }

    /* Delete AML file if there are errors */

    if ((Gbl_ExceptionCount[ASL_ERROR] > 0) && (!Gbl_IgnoreErrors))
    {
        unlink (Gbl_Files[ASL_FILE_AML_OUTPUT].Filename);
    }

    UtDisplaySummary (ASL_FILE_STDOUT);

    exit (0);
}


