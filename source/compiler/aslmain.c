
/******************************************************************************
 *
 * Module Name: aslmain - compiler main and utilities
 *              $Revision: 1.11 $
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



#define _DECLARE_GLOBALS

#include "AslCompiler.h"
#include "acnamesp.h"
#include "acdebug.h"

FILE                    *DebugFile;
UINT8                   AcpiGbl_DbOutputFlags = DB_CONSOLE_OUTPUT;
ASL_ANALYSIS_WALK_INFO  AnalysisWalkInfo;
char                    hex[] = {'0','1','2','3','4','5','6','7',
                                 '8','9','A','B','C','D','E','F'};



/*
 * Stubs
 */

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
AcpiAmlDumpOperands (
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
AcpiAmlDumpOperand (
    ACPI_OPERAND_OBJECT     *EntryDesc)
{
    return AE_OK;
}



/*******************************************************************************
 *
 * FUNCTION:    Usage 
 *
 * PARAMETERS:  None
 *  
 * RETURN:      None      
 *
 * DESCRIPTION: Display help message
 *
 ******************************************************************************/

void 
Usage (
    void)
{
    printf ("Usage:    %s [-dhilno] <InputFile>\n\n", CompilerName);
    printf ("Options:  -d               Create debug/trace output file (*.txt)\n");
    printf ("          -h               Create ascii hex output file\n");
    printf ("          -i               Ignore errors, always create AML file\n");
    printf ("          -l               Create listing file (*.lst)\n");
    printf ("          -n               Create namespace file (*.nsp)\n");
    printf ("          -o <filename>    Specify output file (default is *.aml)\n");
}



/*******************************************************************************
 *
 * FUNCTION:    main    
 *
 * PARAMETERS:  Standard argc/argv
 *
 * RETURN:      Program termination code 
 *
 * DESCRIPTION: C main routine for the Asl Compiler
 *
 ******************************************************************************/


int
main (
    int                 argc, 
    char                **argv)
{
    UINT32              j;
    ACPI_STATUS         Status;
    UINT32              DebugLevel = AcpiDbgLevel;
    UINT8               FileByte;



    AcpiDbgLevel = 0;

    printf ("\n%s [Version %s, %s]\n\n", CompilerId, Version, __DATE__);

    /* Minimum command line contains at least the input file */

    if (argc < 2)
    {
        Usage ();
        return 0;
    }


    /* Get the command line options */

    while ((j = getopt (argc, argv, "dhiln")) != EOF) switch (j)
    {
    case 'd':
        Gbl_DebugFlag = TRUE;
        AslCompilerdebug = 1; /* same as yydebug */
        break;

    case 'h':
        Gbl_HexOutputFlag = TRUE;
        break;

    case 'i':
        Gbl_IgnoreErrors = TRUE;
        break;

    case 'l':
        Gbl_ListingFlag = TRUE;
        Gbl_SourceOutputFlag = TRUE;
        break;

    case 'n':
        Gbl_NsOutputFlag = TRUE;
        break;


    default:
        printf ("Unknown option %c\n", j);

        Usage ();
        return -1;
    }



    /* Next parameter must be the input filename */

    Gbl_InputFilename = argv[optind];
    Status = UtOpenAllFiles (Gbl_InputFilename);
    if (ACPI_FAILURE (Status))
    {
        return -1;
    }


    AcpiCmInitGlobals ();
    AcpiCmMutexInitialize ();
    AcpiNsRootInitialize ();

    /* Build the parse tree */

    AslCompilerparse();
    

    /* Generate AML opcodes corresponding to the parse tokens */

    DbgPrint ("\nGenerating AML opcodes\n\n");
    TgWalkParseTree (ASL_WALK_VISIT_UPWARD, NULL, CgAmlOpcodeWalk, NULL);

    /* Calculate all AML package lengths */

    DbgPrint ("\nGenerating Package lengths\n\n");
    TgWalkParseTree (ASL_WALK_VISIT_UPWARD, NULL, LnPackageLengthWalk, NULL);

    /* Semantic error checking */

    AnalysisWalkInfo.MethodStack = NULL;
    
    DbgPrint ("\nSemantic analysis\n\n");
    TgWalkParseTree (ASL_WALK_VISIT_TWICE, AnSemanticAnalysisWalkBegin, 
                        AnSemanticAnalysisWalkEnd, &AnalysisWalkInfo);


    /* Namespace loading */

    LdLoadNamespace ();


    /* Namespace lookup */

    LkCrossReferenceNamespace ();

    /* Calculate all AML package lengths */

    DbgPrint ("\nGenerating Package lengths\n\n");
    TgWalkParseTree (ASL_WALK_VISIT_UPWARD, NULL, LnInitLengthsWalk, NULL);
    TgWalkParseTree (ASL_WALK_VISIT_UPWARD, NULL, LnPackageLengthWalk, NULL);

    /* Code generation - emit the AML */

    if (Gbl_SourceOutputFlag)
    {
        fseek (Gbl_SourceOutputFile, 0, SEEK_SET);
    }

    Gbl_SourceLine = 0;

    if (Gbl_ListingFlag)
    {
        fprintf (Gbl_ListingFile, "%s [Version %s, %s]\n\n", CompilerId, Version, __DATE__);
        fprintf (Gbl_ListingFile, "Compilation of %s\n\n", Gbl_InputFilename); 
    }

    DbgPrint ("\nWriting AML\n\n");
    TgWalkParseTree (ASL_WALK_VISIT_DOWNWARD, CgAmlWriteWalk, NULL, NULL);


    CgCloseTable ();


    if (Gbl_HexOutputFlag)
    {
        fseek (Gbl_OutputAmlFile, 0, SEEK_SET);

        j = 0;
        while (fread (&FileByte, 1, 1, Gbl_OutputAmlFile))
        {
            fwrite ("0x", 2, 1, Gbl_HexFile);
            fwrite (&hex[FileByte >> 4], 1, 1, Gbl_HexFile);
            fwrite (&hex[FileByte & 0xF], 1, 1, Gbl_HexFile);
            fwrite (", ", 2, 1, Gbl_HexFile);
            j++;
            if (j >= 12)
            {
                fwrite ("\n", 1, 1, Gbl_HexFile);
                j = 0;
            }
        }
    fclose (Gbl_HexFile);
    }



    /* Dump the namespace to the .nsp file if requested */

    LsDisplayNamespace ();

    fclose (Gbl_OutputAmlFile);

    if ((ErrorCount > 0) && (!Gbl_IgnoreErrors))
    {
        unlink (Gbl_OutputFilename);
    }

    UtDisplaySummary ();


    return 0;
}



