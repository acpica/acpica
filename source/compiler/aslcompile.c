/******************************************************************************
 *
 * Module Name: aslcompile - top level compile module
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2017, Intel Corp.
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

#include "aslcompiler.h"
#include "dtcompiler.h"
#include "acnamesp.h"

#include <stdio.h>
#include <time.h>
#include <acapps.h>

#define _COMPONENT          ACPI_COMPILER
        ACPI_MODULE_NAME    ("aslcompile")

/*
 * Main parser entry
 * External is here in case the parser emits the same external in the
 * generated header. (Newer versions of Bison)
 */
int
AslCompilerparse(
    void);

/* Local prototypes */

static void
CmFlushSourceCode (
    void);

static void
CmDumpAllEvents (
    void);


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
CmDoCompile (
    void)
{
    ACPI_STATUS             Status;
    UINT8                   FullCompile;
    UINT8                   Event;


    FullCompile = UtBeginEvent ("*** Total Compile time ***");
    Event = UtBeginEvent ("Open input and output files");
    UtEndEvent (Event);

    Event = UtBeginEvent ("Preprocess input file");
    if (Gbl_PreprocessFlag)
    {
        /* Enter compiler name as a #define */

        PrAddDefine (ASL_DEFINE, "", FALSE);

        /* Preprocessor */

        PrDoPreprocess ();
        Gbl_CurrentLineNumber = 1;
        Gbl_LogicalLineNumber = 1;

        if (Gbl_PreprocessOnly)
        {
            UtEndEvent (Event);
            CmCleanupAndExit ();
            return (0);
        }
    }
    UtEndEvent (Event);


    /* Build the parse tree */

    Event = UtBeginEvent ("Parse source code and build parse tree");
    AslCompilerparse();
    UtEndEvent (Event);

    /* Check for parser-detected syntax errors */

    if (Gbl_SyntaxError)
    {
        fprintf (stderr,
            "Compiler aborting due to parser-detected syntax error(s)\n");
        LsDumpParseTree ();
        goto ErrorExit;
    }

    /* Did the parse tree get successfully constructed? */

    if (!Gbl_ParseTreeRoot)
    {
        /*
         * If there are no errors, then we have some sort of
         * internal problem.
         */
        AslError (ASL_ERROR, ASL_MSG_COMPILER_INTERNAL,
            NULL, "- Could not resolve parse tree root node");

        goto ErrorExit;
    }

    /* Flush out any remaining source after parse tree is complete */

    Event = UtBeginEvent ("Flush source input");
    CmFlushSourceCode ();

    /* Prune the parse tree if requested (debug purposes only) */

    if (Gbl_PruneParseTree)
    {
        AslPruneParseTree (Gbl_PruneDepth, Gbl_PruneType);
    }

    /* Optional parse tree dump, compiler debug output only */

    LsDumpParseTree ();

    OpcGetIntegerWidth (Gbl_ParseTreeRoot->Asl.Child);
    UtEndEvent (Event);

    /* Pre-process parse tree for any operator transforms */

    Event = UtBeginEvent ("Parse tree transforms");
    DbgPrint (ASL_DEBUG_OUTPUT, "\nParse tree transforms\n\n");
    TrWalkParseTree (Gbl_ParseTreeRoot, ASL_WALK_VISIT_TWICE,
        TrAmlTransformWalkBegin, TrAmlTransformWalkEnd, NULL);
    UtEndEvent (Event);

    /* Generate AML opcodes corresponding to the parse tokens */

    Event = UtBeginEvent ("Generate AML opcodes");
    DbgPrint (ASL_DEBUG_OUTPUT, "Generating AML opcodes\n\n");
    TrWalkParseTree (Gbl_ParseTreeRoot, ASL_WALK_VISIT_UPWARD, NULL,
        OpcAmlOpcodeWalk, NULL);
    UtEndEvent (Event);

    /*
     * Now that the input is parsed, we can open the AML output file.
     * Note: by default, the name of this file comes from the table
     * descriptor within the input file.
     */
    Event = UtBeginEvent ("Open AML output file");
    Status = FlOpenAmlOutputFile (Gbl_OutputFilenamePrefix);
    UtEndEvent (Event);
    if (ACPI_FAILURE (Status))
    {
        AePrintErrorLog (ASL_FILE_STDERR);
        return (-1);
    }

    /* Interpret and generate all compile-time constants */

    Event = UtBeginEvent ("Constant folding via AML interpreter");
    DbgPrint (ASL_DEBUG_OUTPUT,
        "Interpreting compile-time constant expressions\n\n");

    if (Gbl_FoldConstants)
    {
        TrWalkParseTree (Gbl_ParseTreeRoot, ASL_WALK_VISIT_UPWARD,
            NULL, OpcAmlConstantWalk, NULL);
    }
    else
    {
        DbgPrint (ASL_PARSE_OUTPUT, "    Optional folding disabled\n");
    }
    UtEndEvent (Event);

    /* Update AML opcodes if necessary, after constant folding */

    Event = UtBeginEvent ("Updating AML opcodes after constant folding");
    DbgPrint (ASL_DEBUG_OUTPUT,
        "Updating AML opcodes after constant folding\n\n");
    TrWalkParseTree (Gbl_ParseTreeRoot, ASL_WALK_VISIT_UPWARD,
        NULL, OpcAmlOpcodeUpdateWalk, NULL);
    UtEndEvent (Event);

    /* Calculate all AML package lengths */

    Event = UtBeginEvent ("Generate AML package lengths");
    DbgPrint (ASL_DEBUG_OUTPUT, "Generating Package lengths\n\n");
    TrWalkParseTree (Gbl_ParseTreeRoot, ASL_WALK_VISIT_UPWARD, NULL,
        LnPackageLengthWalk, NULL);
    UtEndEvent (Event);

    if (Gbl_ParseOnlyFlag)
    {
        AePrintErrorLog (ASL_FILE_STDERR);
        UtDisplaySummary (ASL_FILE_STDERR);
        if (Gbl_DebugFlag)
        {
            /* Print error summary to the stdout also */

            AePrintErrorLog (ASL_FILE_STDOUT);
            UtDisplaySummary (ASL_FILE_STDOUT);
        }
        UtEndEvent (FullCompile);
        return (0);
    }

    /*
     * Create an internal namespace and use it as a symbol table
     */

    /* Namespace loading */

    Event = UtBeginEvent ("Create ACPI Namespace");
    DbgPrint (ASL_DEBUG_OUTPUT, "Creating ACPI Namespace\n\n");
    Status = LdLoadNamespace (Gbl_ParseTreeRoot);
    UtEndEvent (Event);
    if (ACPI_FAILURE (Status))
    {
        goto ErrorExit;
    }

    /* Namespace cross-reference */

    AslGbl_NamespaceEvent = UtBeginEvent (
        "Cross reference parse tree and Namespace");
    DbgPrint (ASL_DEBUG_OUTPUT, "Cross referencing namespace\n\n");
    Status = XfCrossReferenceNamespace ();
    if (ACPI_FAILURE (Status))
    {
        goto ErrorExit;
    }

    /* Namespace - Check for non-referenced objects */

    LkFindUnreferencedObjects ();
    UtEndEvent (AslGbl_NamespaceEvent);

    /* Resolve External Declarations */

    if (Gbl_DoExternals)
    {
        Event = UtBeginEvent ("Resolve all Externals");
        DbgPrint (ASL_DEBUG_OUTPUT, "\nResolve Externals\n\n");
        TrWalkParseTree (Gbl_ParseTreeRoot, ASL_WALK_VISIT_TWICE,
            ExAmlExternalWalkBegin, ExAmlExternalWalkEnd, NULL);
        UtEndEvent (Event);
    }

    /*
     * Semantic analysis. This can happen only after the
     * namespace has been loaded and cross-referenced.
     *
     * part one - check control methods
     */
    Event = UtBeginEvent ("Analyze control method return types");
    AnalysisWalkInfo.MethodStack = NULL;

    DbgPrint (ASL_DEBUG_OUTPUT, "Semantic analysis - Method analysis\n\n");

    if (Gbl_CrossReferenceOutput)
    {
        OtPrintHeaders ("Part 1: Object Reference Map "
            "(Object references from within each control method)");
    }

    TrWalkParseTree (Gbl_ParseTreeRoot, ASL_WALK_VISIT_TWICE,
        MtMethodAnalysisWalkBegin,
        MtMethodAnalysisWalkEnd, &AnalysisWalkInfo);
    UtEndEvent (Event);

    /* Generate the object cross-reference file if requested */

    Event = UtBeginEvent ("Generate cross-reference file");
    OtCreateXrefFile ();
    UtEndEvent (Event);

    /* Semantic error checking part two - typing of method returns */

    Event = UtBeginEvent ("Determine object types returned by methods");
    DbgPrint (ASL_DEBUG_OUTPUT, "Semantic analysis - Method typing\n\n");
    TrWalkParseTree (Gbl_ParseTreeRoot, ASL_WALK_VISIT_UPWARD,
        NULL, AnMethodTypingWalkEnd, NULL);
    UtEndEvent (Event);

    /* Semantic error checking part three - operand type checking */

    Event = UtBeginEvent ("Analyze AML operand types");
    DbgPrint (ASL_DEBUG_OUTPUT,
        "Semantic analysis - Operand type checking\n\n");
    if (Gbl_DoTypechecking)
    {
        TrWalkParseTree (Gbl_ParseTreeRoot, ASL_WALK_VISIT_UPWARD,
            NULL, AnOperandTypecheckWalkEnd, &AnalysisWalkInfo);
    }
    UtEndEvent (Event);

    /* Semantic error checking part four - other miscellaneous checks */

    Event = UtBeginEvent ("Miscellaneous analysis");
    DbgPrint (ASL_DEBUG_OUTPUT, "Semantic analysis - miscellaneous\n\n");
    TrWalkParseTree (Gbl_ParseTreeRoot, ASL_WALK_VISIT_DOWNWARD,
        AnOtherSemanticAnalysisWalkBegin,
        NULL, &AnalysisWalkInfo);
    UtEndEvent (Event);

    /* Calculate all AML package lengths */

    Event = UtBeginEvent ("Finish AML package length generation");
    DbgPrint (ASL_DEBUG_OUTPUT, "Generating Package lengths\n\n");
    TrWalkParseTree (Gbl_ParseTreeRoot, ASL_WALK_VISIT_UPWARD, NULL,
        LnInitLengthsWalk, NULL);
    TrWalkParseTree (Gbl_ParseTreeRoot, ASL_WALK_VISIT_UPWARD, NULL,
        LnPackageLengthWalk, NULL);
    UtEndEvent (Event);

    /* Code generation - emit the AML */

    Event = UtBeginEvent ("Generate AML code and write output files");
    DbgPrint (ASL_DEBUG_OUTPUT, "Writing AML byte code\n\n");
    CgGenerateAmlOutput ();
    UtEndEvent (Event);

    Event = UtBeginEvent ("Write optional output files");
    CmDoOutputFiles ();
    UtEndEvent (Event);

    UtEndEvent (FullCompile);
    CmCleanupAndExit ();
    return (0);

ErrorExit:
    UtEndEvent (FullCompile);
    CmCleanupAndExit ();
    return (-1);
}


/*******************************************************************************
 *
 * FUNCTION:    AslCompilerSignon
 *
 * PARAMETERS:  FileId      - ID of the output file
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
    char                    *Prefix = "";
    char                    *UtilityName;


    /* Set line prefix depending on the destination file type */

    switch (FileId)
    {
    case ASL_FILE_ASM_SOURCE_OUTPUT:
    case ASL_FILE_ASM_INCLUDE_OUTPUT:

        Prefix = "; ";
        break;

    case ASL_FILE_HEX_OUTPUT:

        if (Gbl_HexOutputFlag == HEX_OUTPUT_ASM)
        {
            Prefix = "; ";
        }
        else if ((Gbl_HexOutputFlag == HEX_OUTPUT_C) ||
                 (Gbl_HexOutputFlag == HEX_OUTPUT_ASL))
        {
            FlPrintFile (ASL_FILE_HEX_OUTPUT, "/*\n");
            Prefix = " * ";
        }
        break;

    case ASL_FILE_C_SOURCE_OUTPUT:
    case ASL_FILE_C_OFFSET_OUTPUT:
    case ASL_FILE_C_INCLUDE_OUTPUT:

        Prefix = " * ";
        break;

    default:

        /* No other output types supported */

        break;
    }

    /* Running compiler or disassembler? */

    if (Gbl_DisasmFlag)
    {
        UtilityName = AML_DISASSEMBLER_NAME;
    }
    else
    {
        UtilityName = ASL_COMPILER_NAME;
    }

    /* Compiler signon with copyright */

    FlPrintFile (FileId, "%s\n", Prefix);
    FlPrintFile (FileId, ACPI_COMMON_HEADER (UtilityName, Prefix));
}


/*******************************************************************************
 *
 * FUNCTION:    AslCompilerFileHeader
 *
 * PARAMETERS:  FileId      - ID of the output file
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
    struct tm               *NewTime;
    time_t                  Aclock;
    char                    *Prefix = "";


    /* Set line prefix depending on the destination file type */

    switch (FileId)
    {
    case ASL_FILE_ASM_SOURCE_OUTPUT:
    case ASL_FILE_ASM_INCLUDE_OUTPUT:

        Prefix = "; ";
        break;

    case ASL_FILE_HEX_OUTPUT:

        if (Gbl_HexOutputFlag == HEX_OUTPUT_ASM)
        {
            Prefix = "; ";
        }
        else if ((Gbl_HexOutputFlag == HEX_OUTPUT_C) ||
                 (Gbl_HexOutputFlag == HEX_OUTPUT_ASL))
        {
            Prefix = " * ";
        }
        break;

    case ASL_FILE_C_SOURCE_OUTPUT:
    case ASL_FILE_C_OFFSET_OUTPUT:
    case ASL_FILE_C_INCLUDE_OUTPUT:

        Prefix = " * ";
        break;

    default:

        /* No other output types supported */

        break;
    }

    /* Compilation header with timestamp */

    (void) time (&Aclock);
    NewTime = localtime (&Aclock);

    FlPrintFile (FileId,
        "%sCompilation of \"%s\" - %s%s\n",
        Prefix, Gbl_Files[ASL_FILE_INPUT].Filename, asctime (NewTime),
        Prefix);

    switch (FileId)
    {
    case ASL_FILE_C_SOURCE_OUTPUT:
    case ASL_FILE_C_OFFSET_OUTPUT:
    case ASL_FILE_C_INCLUDE_OUTPUT:

        FlPrintFile (FileId, " */\n");
        break;

    default:

        /* Nothing to do for other output types */

        break;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    CmFlushSourceCode
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Read in any remaining source code after the parse tree
 *              has been constructed.
 *
 ******************************************************************************/

static void
CmFlushSourceCode (
    void)
{
    char                    Buffer;


    while (FlReadFile (ASL_FILE_INPUT, &Buffer, 1) != AE_ERROR)
    {
        AslInsertLineBuffer ((int) Buffer);
    }

    AslResetCurrentLineBuffer ();
}


/*******************************************************************************
 *
 * FUNCTION:    CmDoOutputFiles
 *
 * PARAMETERS:  None
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Create all "listing" type files
 *
 ******************************************************************************/

void
CmDoOutputFiles (
    void)
{

    /* Create listings and hex files */

    LsDoListings ();
    HxDoHexOutput ();

    /* Dump the namespace to the .nsp file if requested */

    (void) NsDisplayNamespace ();

    /* Dump the device mapping file */

    MpEmitMappingInfo ();
}


/*******************************************************************************
 *
 * FUNCTION:    CmDumpAllEvents
 *
 * PARAMETERS:  None
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Dump all compiler events
 *
 ******************************************************************************/

static void
CmDumpAllEvents (
    void)
{
    ASL_EVENT_INFO          *Event;
    UINT32                  Delta;
    UINT32                  MicroSeconds;
    UINT32                  MilliSeconds;
    UINT32                  i;


    Event = AslGbl_Events;

    DbgPrint (ASL_DEBUG_OUTPUT, "\n\nElapsed time for major events\n\n");
    if (Gbl_CompileTimesFlag)
    {
        printf ("\nElapsed time for major events\n\n");
    }

    for (i = 0; i < AslGbl_NextEvent; i++)
    {
        if (Event->Valid)
        {
            /* Delta will be in 100-nanosecond units */

            Delta = (UINT32) (Event->EndTime - Event->StartTime);

            MicroSeconds = Delta / ACPI_100NSEC_PER_USEC;
            MilliSeconds = Delta / ACPI_100NSEC_PER_MSEC;

            /* Round milliseconds up */

            if ((MicroSeconds - (MilliSeconds * ACPI_USEC_PER_MSEC)) >= 500)
            {
                MilliSeconds++;
            }

            DbgPrint (ASL_DEBUG_OUTPUT, "%8u usec %8u msec - %s\n",
                MicroSeconds, MilliSeconds, Event->EventName);

            if (Gbl_CompileTimesFlag)
            {
                printf ("%8u usec %8u msec - %s\n",
                    MicroSeconds, MilliSeconds, Event->EventName);
            }
        }

        Event++;
    }
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
CmCleanupAndExit (
    void)
{
    UINT32                  i;
    BOOLEAN                 DeleteAmlFile = FALSE;


    AePrintErrorLog (ASL_FILE_STDERR);
    if (Gbl_DebugFlag)
    {
        /* Print error summary to stdout also */

        AePrintErrorLog (ASL_FILE_STDOUT);
    }

    /* Emit compile times if enabled */

    CmDumpAllEvents ();

    if (Gbl_CompileTimesFlag)
    {
        printf ("\nMiscellaneous compile statistics\n\n");
        printf ("%11u : %s\n", TotalParseNodes, "Parse nodes");
        printf ("%11u : %s\n", Gbl_NsLookupCount, "Namespace searches");
        printf ("%11u : %s\n", TotalNamedObjects, "Named objects");
        printf ("%11u : %s\n", TotalMethods, "Control methods");
        printf ("%11u : %s\n", TotalAllocations, "Memory Allocations");
        printf ("%11u : %s\n", TotalAllocated, "Total allocated memory");
        printf ("%11u : %s\n", TotalFolds, "Constant subtrees folded");
        printf ("\n");
    }

    if (Gbl_NsLookupCount)
    {
        DbgPrint (ASL_DEBUG_OUTPUT,
            "\n\nMiscellaneous compile statistics\n\n");

        DbgPrint (ASL_DEBUG_OUTPUT,
            "%32s : %u\n", "Total Namespace searches",
            Gbl_NsLookupCount);

        DbgPrint (ASL_DEBUG_OUTPUT,
            "%32s : %u usec\n", "Time per search", ((UINT32)
            (AslGbl_Events[AslGbl_NamespaceEvent].EndTime -
                AslGbl_Events[AslGbl_NamespaceEvent].StartTime) / 10) /
                Gbl_NsLookupCount);
    }

    if (Gbl_ExceptionCount[ASL_ERROR] > ASL_MAX_ERROR_COUNT)
    {
        printf ("\nMaximum error count (%u) exceeded\n",
            ASL_MAX_ERROR_COUNT);
    }

    UtDisplaySummary (ASL_FILE_STDOUT);

    /*
     * We will delete the AML file if there are errors and the
     * force AML output option has not been used.
     */
    if ((Gbl_ExceptionCount[ASL_ERROR] > 0) &&
        (!Gbl_IgnoreErrors) &&
        Gbl_Files[ASL_FILE_AML_OUTPUT].Handle)
    {
        DeleteAmlFile = TRUE;
    }

    /* Close all open files */

    /*
     * Take care with the preprocessor file (.pre), it might be the same
     * as the "input" file, depending on where the compiler has terminated
     * or aborted. Prevent attempt to close the same file twice in
     * loop below.
     */
    if (Gbl_Files[ASL_FILE_PREPROCESSOR].Handle ==
        Gbl_Files[ASL_FILE_INPUT].Handle)
    {
        Gbl_Files[ASL_FILE_PREPROCESSOR].Handle = NULL;
    }

    /* Close the standard I/O files */

    for (i = ASL_FILE_INPUT; i < ASL_MAX_FILE_TYPE; i++)
    {
        FlCloseFile (i);
    }

    /* Delete AML file if there are errors */

    if (DeleteAmlFile)
    {
        FlDeleteFile (ASL_FILE_AML_OUTPUT);
    }

    /* Delete the preprocessor temp file unless full debug was specified */

    if (Gbl_PreprocessFlag && !Gbl_KeepPreprocessorTempFile)
    {
        FlDeleteFile (ASL_FILE_PREPROCESSOR);
    }

    /*
     * Delete intermediate ("combined") source file (if -ls flag not set)
     * This file is created during normal ASL/AML compiles. It is not
     * created by the data table compiler.
     *
     * If the -ls flag is set, then the .SRC file should not be deleted.
     * In this case, Gbl_SourceOutputFlag is set to TRUE.
     *
     * Note: Handles are cleared by FlCloseFile above, so we look at the
     * filename instead, to determine if the .SRC file was actually
     * created.
     */
    if (!Gbl_SourceOutputFlag)
    {
        FlDeleteFile (ASL_FILE_SOURCE_OUTPUT);
    }

    /* Final cleanup after compiling one file */

    CmDeleteCaches ();
}


/*******************************************************************************
 *
 * FUNCTION:    CmDeleteCaches
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Delete all local cache buffer blocks
 *
 ******************************************************************************/

void
CmDeleteCaches (
    void)
{
    UINT32                  BufferCount;
    ASL_CACHE_INFO          *Next;


    /* Parse Op cache */

    BufferCount = 0;
    while (Gbl_ParseOpCacheList)
    {
        Next = Gbl_ParseOpCacheList->Next;
        ACPI_FREE (Gbl_ParseOpCacheList);
        Gbl_ParseOpCacheList = Next;
        BufferCount++;
    }

    DbgPrint (ASL_DEBUG_OUTPUT,
        "%u ParseOps, Buffer size: %u ops (%u bytes), %u Buffers\n",
        Gbl_ParseOpCount, ASL_PARSEOP_CACHE_SIZE,
        (sizeof (ACPI_PARSE_OBJECT) * ASL_PARSEOP_CACHE_SIZE), BufferCount);

    Gbl_ParseOpCount = 0;
    Gbl_ParseOpCacheNext = NULL;
    Gbl_ParseOpCacheLast = NULL;
    Gbl_ParseTreeRoot = NULL;

    /* Generic string cache */

    BufferCount = 0;
    while (Gbl_StringCacheList)
    {
        Next = Gbl_StringCacheList->Next;
        ACPI_FREE (Gbl_StringCacheList);
        Gbl_StringCacheList = Next;
        BufferCount++;
    }

    DbgPrint (ASL_DEBUG_OUTPUT,
        "%u Strings (%u bytes), Buffer size: %u bytes, %u Buffers\n",
        Gbl_StringCount, Gbl_StringSize, ASL_STRING_CACHE_SIZE, BufferCount);

    Gbl_StringSize = 0;
    Gbl_StringCount = 0;
    Gbl_StringCacheNext = NULL;
    Gbl_StringCacheLast = NULL;
}
