
/******************************************************************************
 * 
 * Module Name: nsload - namespace loading procedures
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

#define __NSLOAD_C__

#include <acpi.h>
#include <acobject.h>
#include <interp.h>
#include <namesp.h>
#include <methods.h>
#include <amlcode.h>
#include <pnp.h>
#include <parser.h>
#include <dispatch.h>


#define _COMPONENT          NAMESPACE
        MODULE_NAME         ("nsload");


/*******************************************************************************
 *
 * FUNCTION:    NsParseTable
 *
 * PARAMETERS:  Aml                 - Pointer to the raw AML code to parse
 *              AmlSize             - Length of the AML to parse
 *              DescendingCallback  - Called as each opcode is encountered during
 *                                    descent of the parse tree
 *              AscendingCallback   - Called as each opcode is completed, during
 *                                    ascent of the parse tree
 *              RootObject          - TBD: REMOVE??
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Parse AML within an ACPI table and return a tree of ops
 *
 ******************************************************************************/

ACPI_STATUS
NsParseTable (
    ACPI_TABLE_DESC         *TableDesc,
    NAME_TABLE_ENTRY        *Scope)
{
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("NsParseTable");


    /* Create the root object */

    Gbl_ParsedNamespaceRoot = PsAllocOp (AML_ScopeOp);
    if (!Gbl_ParsedNamespaceRoot)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /* Initialize the root object */

    ((ACPI_NAMED_OP *) Gbl_ParsedNamespaceRoot)->Name = * (UINT32 *) NS_ROOT;

    /* Pass 1:  Parse everything except control method bodies */

    Status = PsParseAml (Gbl_ParsedNamespaceRoot, TableDesc->AmlPointer, TableDesc->AmlLength); 
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

#ifndef PARSER_ONLY

    DEBUG_PRINT (TRACE_PARSE, ("NsParseTable: Building Internal Namespace\n"));
BREAKPOINT3;

/* TBD: Temp only */

    PsWalkParsedAml (PsGetChild (Gbl_ParsedNamespaceRoot), Gbl_ParsedNamespaceRoot, NULL, Scope, NULL, NULL,
                        TableDesc, DsLoad1BeginOp, DsLoad1EndOp);


    PsWalkParsedAml (PsGetChild (Gbl_ParsedNamespaceRoot), Gbl_ParsedNamespaceRoot, NULL, Scope, NULL, NULL,
                        TableDesc, DsLoad2BeginOp, DsLoad2EndOp);


    /*
     * Now that the internal namespace has been constructed, we can delete the
     * parsed namespace, since it is no longer needed
     */

    DEBUG_PRINT (TRACE_PARSE, ("NsParseTable: Deleting Parsed Namespace\n"));
BREAKPOINT3;


    PsDeleteParseTree (Gbl_ParsedNamespaceRoot);
    Gbl_ParsedNamespaceRoot = NULL;
#endif


    return_ACPI_STATUS (AE_OK);
}




/*****************************************************************************
 *
 * FUNCTION:    NsLoadTable
 *
 * PARAMETERS:  *PcodeAddr          - Address of pcode block
 *              PcodeLength         - Length of pcode block
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Mainline of the AML load/dump subsystem. Sets up the
 *              input engine, calls handler for outermost object type.
 *
 ****************************************************************************/

ACPI_STATUS
NsLoadTable (
    ACPI_TABLE_DESC         *TableDesc,
    NAME_TABLE_ENTRY        *Entry)
{
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("NsLoadTable");


    if (!TableDesc->AmlPointer)
    {
        DEBUG_PRINT (ACPI_ERROR, ("NsLoadTable: Null AML pointer\n"));
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    DEBUG_PRINT (ACPI_INFO, ("NsLoadTable: AML block at %p\n", TableDesc->AmlPointer));


    if (!TableDesc->AmlLength)
    {
        DEBUG_PRINT (ACPI_ERROR, ("NsLoadTable: Zero-length AML block\n"));
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }


    /*
     * Parse the table and load the namespace with all named objects found within.  
     * Control methods are NOT parsed at this time.  In fact, the control methods 
     * cannot be parsed until the entire namespace is loaded, because if a control 
     * method makes a forward reference (call) to another control method, we can't 
     * continue parsing because we don't know how many arguments to parse next!
     */

    DEBUG_PRINT (ACPI_INFO, ("NsLoadTable: **** Loading table into namespace ****\n"));

    CmAcquireMutex (MTX_NAMESPACE);
    Status = NsParseTable (TableDesc, Entry->Scope);
    CmReleaseMutex (MTX_NAMESPACE);


    /*
     * Now we can parse the control methods.  We always parse them here for a sanity
     * check, and if configured for just-in-time parsing, we delete the control method
     * parse trees.
     */

    DEBUG_PRINT (ACPI_INFO, ("NsLoadTable: **** Begin Table Method Parsing and Object Initialization ****\n"));
BREAKPOINT3;

    Status = DsInitializeObjects (TableDesc, Entry);

    DEBUG_PRINT (ACPI_INFO, ("NsLoadTable: **** Completed Table Method Parsing and Object Initialization ****\n"));
BREAKPOINT3;

    return_ACPI_STATUS (Status);
}



/******************************************************************************
 * 
 * FUNCTION:    NsLoadTableByType
 *
 * PARAMETERS:  TableType           - Id of the table type to load
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Load an ACPI table or tables into the namespace.  All tables
 *              of the given type are loaded.  The mechanism allows this
 *              routine to be called repeatedly.
 *
 *****************************************************************************/

ACPI_STATUS
NsLoadTableByType (
    ACPI_TABLE_TYPE         TableType)
{
    UINT32                  i;
    ACPI_STATUS             Status = AE_OK;
    ACPI_TABLE_HEADER       *TablePtr;
    ACPI_TABLE_DESC         *TableDesc;

    
    FUNCTION_TRACE ("NsLoadTableByType");


    CmAcquireMutex (MTX_TABLES);


    /*
     * Table types supported are:
     * DSDT (one), SSDT/PSDT (multiple)
     */

    switch (TableType)
    {

    case TABLE_DSDT:

        DEBUG_PRINT (ACPI_INFO, ("NsLoadTableByType: Loading DSDT\n"));

        TableDesc = &Gbl_AcpiTables[TABLE_DSDT];

        /* If table already loaded into namespace, just return */

        if (TableDesc->LoadedIntoNamespace)
        {
            goto UnlockAndExit;
        }

        TableDesc->TableId = TABLE_ID_DSDT;

        /* Initialize the root of the namespace tree */
    
        Status = NsRootInitialize ();
        if (ACPI_FAILURE (Status))
        {
            goto UnlockAndExit;
        }

        /* Now load the single DSDT */

        Status = NsLoadTable (TableDesc, Gbl_RootObject);
        if (ACPI_SUCCESS (Status))
        {
            TableDesc->LoadedIntoNamespace = TRUE;
            TableDesc->RootEntry = Gbl_RootObject;
        }

        break;


    case TABLE_SSDT:

        DEBUG_PRINT (ACPI_INFO, ("NsLoadTableByType: Loading %d SSDTs\n",
                        Gbl_AcpiTables[TABLE_SSDT].Count));

        /*
         * Traverse list of SSDT tables
         */

        TableDesc = &Gbl_AcpiTables[TABLE_SSDT];
        for (i = 0; i < Gbl_AcpiTables[TABLE_SSDT].Count; i++)
        {
            TablePtr = TableDesc->Pointer;

            /* Only attempt to load table if it is not already loaded! */

            if (!TableDesc->LoadedIntoNamespace)
            {
                Status = NsLoadTable (TableDesc, Gbl_RootObject);
                if (ACPI_FAILURE (Status))
                {
                    break;
                }

                TableDesc->LoadedIntoNamespace = TRUE;
                TableDesc->RootEntry = Gbl_RootObject;
            }

            TableDesc = TableDesc->Next;
        }

        break;


    case TABLE_PSDT:

        DEBUG_PRINT (ACPI_INFO, ("NsLoadTableByType: Loading %d PSDTs\n",
                        Gbl_AcpiTables[TABLE_PSDT].Count));

        /*
         * Traverse list of PSDT tables
         */

        TableDesc = &Gbl_AcpiTables[TABLE_PSDT];
        for (i = 0; i < Gbl_AcpiTables[TABLE_PSDT].Count ; i++)
        {
            TablePtr = TableDesc->Pointer;

            /* Only attempt to load table if it is not already loaded! */

            if (!TableDesc->LoadedIntoNamespace)
            {
                Status = NsLoadTable (TableDesc, Gbl_RootObject);
                if (ACPI_FAILURE (Status))
                {
                    break;
                }

                TableDesc->LoadedIntoNamespace = TRUE;
                TableDesc->RootEntry = Gbl_RootObject;
            }

            TableDesc = TableDesc->Next;
        }

        break;


    default:
        Status = AE_SUPPORT;
    }


UnlockAndExit:

    CmReleaseMutex (MTX_TABLES);

    return_ACPI_STATUS (Status);

}





