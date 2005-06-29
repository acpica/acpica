
/******************************************************************************
 * 
 * Module Name: psapi - Parser external interfaces
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

#define __PSAPI_C__

#include <acpi.h>
#include <parser.h>
#include <interpreter.h>
#include <amlcode.h>
#include <namespace.h>


#define _COMPONENT          PARSER
        MODULE_NAME         ("psapi");


char    *Gbl_ParserId = "Non-recursive AML Parser";


typedef struct InitWalkInfo
{
    UINT32                  MethodCount;
    UINT32                  OpRegionCount;

} INIT_WALK_INFO;



/*******************************************************************************
 *
 * FUNCTION:    PsxInitOneObject
 *
 * PARAMETERS:  ObjHandle       - NTE of the object
 *              Level           - Current nesting level
 *              Context         - Points to a init info struct
 *              ReturnValue     - Not used
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Callback from AcpiWalkNamespace.  Invoked for every object within
 *              the  namespace. 
 *
 *              Currently, the only objects that require initialization are:
 *              1) Methods
 *              2) Op Regions
 *
 ******************************************************************************/

ACPI_STATUS
PsxInitOneObject (
    ACPI_HANDLE             ObjHandle, 
    UINT32                  Level, 
    void                    *Context,
    void                    **ReturnValue)
{
    ACPI_OBJECT_TYPE        Type;


    Type = NsGetType (ObjHandle);

    switch (Type)
    {

    case ACPI_TYPE_Region:

        PsxInitializeRegion (ObjHandle);

        ((INIT_WALK_INFO *) Context)->OpRegionCount++;
        break;


    case ACPI_TYPE_Method:

        PsxParseMethod (ObjHandle);

        ((INIT_WALK_INFO *) Context)->MethodCount++;
        break;

    default:
        break;
    }

    /*
     * We ignore errors from above, and always return OK, since
     * we don't want to abort the walk on a single error.
     */
    return (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    PsxInitializeObjects
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Walk the entire namespace and perform any necessary initialization
 *              on the objects found therein
 *
 ******************************************************************************/

ACPI_STATUS
PsxInitializeObjects (void)
{
    ACPI_STATUS             Status;
    INIT_WALK_INFO          Info;


    FUNCTION_TRACE ("PsxInitializeObjects");


    DEBUG_PRINT (TRACE_PARSE, ("PsxInitializeObjects: **** Starting initialization of namespace objects ****\n"));

    Info.MethodCount = 0;
    Info.OpRegionCount = 0;


    /* Walk entire namespace from the root */

    Status = AcpiWalkNamespace (ACPI_TYPE_Any, Gbl_RootObject, ACPI_INT_MAX, PsxInitOneObject, 
                                &Info, NULL);
    if (ACPI_FAILURE (Status))
    {
        DEBUG_PRINT (ACPI_ERROR, ("PsxInitializeObjects: WalkNamespace failed! %x\n", Status));
    }

    DEBUG_PRINT (TRACE_PARSE, ("PsxInitializeObjects: %d Control Methods found\n", Info.MethodCount));
    DEBUG_PRINT (TRACE_PARSE, ("PsxInitializeObjects: %d Op Regions found\n", Info.OpRegionCount));

    return_ACPI_STATUS (AE_OK);
}


/*****************************************************************************
 *
 * FUNCTION:    PsxLoadTable
 *
 * PARAMETERS:  *PcodeAddr          - Address of pcode block
 *              PcodeLength         - Length of pcode block
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Mainline of the AML load/dump subsystem. Sets up the
 *              input engine, calls handler for outermost object type.
 *
 *
 ****************************************************************************/

ACPI_STATUS
PsxLoadTable (
    UINT8                   *PcodeAddr, 
    INT32                   PcodeLength)
{
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("PsxLoadTable");


    if (!PcodeAddr)
    {
        DEBUG_PRINT (ACPI_ERROR, ("PsxLoadTable: Null AML pointer\n"));
        return_ACPI_STATUS (AE_AML_ERROR);
    }

    DEBUG_PRINT (ACPI_INFO, ("PsxLoadTable: AML block at %p\n", PcodeAddr));


    if (!PcodeLength)
    {
        DEBUG_PRINT (ACPI_ERROR, ("PsxLoadTable: Zero-length AML block\n"));
        return_ACPI_STATUS (AE_AML_ERROR);
    }


    /*
     * Parse the table and load the namespace with all named objects found within.  
     * Control methods are NOT parsed at this time.  In fact, the control methods 
     * cannot be parsed until the entire namespace is loaded, because if a control 
     * method makes a forward reference (call) to another control method, we can't 
     * continue parsing because we don't know how many arguments to parse next!
     */

    DEBUG_PRINT (ACPI_INFO, ("PsxLoadTable: **** Begin Namespace Load ****\n"));
BREAKPOINT3;

    Status = PsParseTable (PcodeAddr, PcodeLength, PsxLoadBeginOp, PsxLoadEndOp, NULL);



    /* TBD: Check if we should parse all methods here, or parse late */
/*
   if (Gbl_MethodParsing = PARSE_EARLY)
   {
*/

    DEBUG_PRINT (ACPI_INFO, ("PsxLoadTable: **** Begin Object Initialization ****\n"));
BREAKPOINT3;

    Status = PsxInitializeObjects ();

    DEBUG_PRINT (ACPI_INFO, ("PsxLoadTable: **** Completed Object Initialization ****\n"));
BREAKPOINT3;

    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 *
 * FUNCTION:    PsxExecute
 *
 * PARAMETERS:  MthDesc             - A method object containing both the AML
 *                                    address and length.
 *              **Params            - List of parameters to pass to method, 
 *                                    terminated by NULL. Params itself may be 
 *                                    NULL if no parameters are being passed.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute a control method
 *
 ****************************************************************************/

ACPI_STATUS
PsxExecute (
    ACPI_OBJECT_INTERNAL    *MthDesc,
    ACPI_OBJECT_INTERNAL    **Params,
    ACPI_OBJECT_INTERNAL    **ReturnObjDesc)
{
    ACPI_STATUS             Status;
    UINT8                   *Pcode;
    UINT32                  PcodeLength;


    FUNCTION_TRACE ("PsxExecute");

    Pcode = MthDesc->Method.Pcode;
    PcodeLength = MthDesc->Method.PcodeLength;


    /* This is where we really execute the method */

    DEBUG_PRINT (ACPI_INFO, ("PsxExecute: **** Begin Execution **** code=%p len=%X\n",
                    Pcode, PcodeLength));

BREAKPOINT3;

/* TBD: if method not parsed, must parse it first !! */
/*
    Status = PsParseAml (MthDesc->Method.ParserOp, Pcode, PcodeLength, 
                            AmlBeginScopeForExecution, AmlEndScopeForExecution);
*/

    Status = PsWalkParsedAml (MthDesc->Method.ParserOp, MthDesc->Method.ParserOp, Params, ReturnObjDesc,
                                PsxExecBeginOp, PsxExecEndOp);
    /* 
     * Normal exit is with Status == AE_RETURN_VALUE when a ReturnOp has been executed,
     * or with Status == AE_PENDING at end of AML block (end of Method code)
     */

    if (*ReturnObjDesc)
    {
        DEBUG_PRINT (ACPI_INFO, ("Method returned ObjDesc=%X\n", *ReturnObjDesc));
        DUMP_STACK_ENTRY (*ReturnObjDesc);

        Status = AE_RETURN_VALUE;
    }

    else
    {
        /* Map PENDING (normal exit, no return value) to OK */

        if (AE_PENDING == Status)
        {
            Status = AE_OK;
        }
    }


    return_ACPI_STATUS (Status);
}




