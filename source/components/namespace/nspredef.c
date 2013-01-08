/******************************************************************************
 *
 * Module Name: nspredef - Validation of ACPI predefined methods and objects
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2013, Intel Corp.
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

#define ACPI_CREATE_PREDEFINED_TABLE

#include "acpi.h"
#include "accommon.h"
#include "acnamesp.h"
#include "acpredef.h"


#define _COMPONENT          ACPI_NAMESPACE
        ACPI_MODULE_NAME    ("nspredef")


/*******************************************************************************
 *
 * This module validates predefined ACPI objects that appear in the namespace,
 * at the time they are evaluated (via AcpiEvaluateObject). The purpose of this
 * validation is to detect problems with BIOS-exposed predefined ACPI objects
 * before the results are returned to the ACPI-related drivers.
 *
 * There are several areas that are validated:
 *
 *  1) The number of input arguments as defined by the method/object in the
 *      ASL is validated against the ACPI specification.
 *  2) The type of the return object (if any) is validated against the ACPI
 *      specification.
 *  3) For returned package objects, the count of package elements is
 *      validated, as well as the type of each package element. Nested
 *      packages are supported.
 *
 * For any problems found, a warning message is issued.
 *
 ******************************************************************************/


/* Local prototypes */

static ACPI_STATUS
AcpiNsCheckReference (
    ACPI_PREDEFINED_DATA        *Data,
    ACPI_OPERAND_OBJECT         *ReturnObject);

static void
AcpiNsGetExpectedTypes (
    char                        *Buffer,
    UINT32                      ExpectedBtypes);

/*
 * Names for the types that can be returned by the predefined objects.
 * Used for warning messages. Must be in the same order as the ACPI_RTYPEs
 */
static const char   *AcpiRtypeNames[] =
{
    "/Integer",
    "/String",
    "/Buffer",
    "/Package",
    "/Reference",
};


/*******************************************************************************
 *
 * FUNCTION:    AcpiNsCheckPredefinedNames
 *
 * PARAMETERS:  Node            - Namespace node for the method/object
 *              UserParamCount  - Number of parameters actually passed
 *              ReturnStatus    - Status from the object evaluation
 *              ReturnObjectPtr - Pointer to the object returned from the
 *                                evaluation of a method or object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Check an ACPI name for a match in the predefined name list.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiNsCheckPredefinedNames (
    ACPI_NAMESPACE_NODE         *Node,
    UINT32                      UserParamCount,
    ACPI_STATUS                 ReturnStatus,
    ACPI_OPERAND_OBJECT         **ReturnObjectPtr)
{
    ACPI_OPERAND_OBJECT         *ReturnObject = *ReturnObjectPtr;
    ACPI_STATUS                 Status = AE_OK;
    const ACPI_PREDEFINED_INFO  *Predefined;
    char                        *Pathname;
    ACPI_PREDEFINED_DATA        *Data;


    /* Match the name for this method/object against the predefined list */

    Predefined = AcpiNsCheckForPredefinedName (Node);

    /* Get the full pathname to the object, for use in warning messages */

    Pathname = AcpiNsGetExternalPathname (Node);
    if (!Pathname)
    {
        return (AE_OK); /* Could not get pathname, ignore */
    }

    /*
     * Check that the parameter count for this method matches the ASL
     * definition. For predefined names, ensure that both the caller and
     * the method itself are in accordance with the ACPI specification.
     */
    AcpiNsCheckParameterCount (Pathname, Node, UserParamCount, Predefined);

    /* If not a predefined name, we cannot validate the return object */

    if (!Predefined)
    {
        goto Cleanup;
    }

    /*
     * If the method failed or did not actually return an object, we cannot
     * validate the return object
     */
    if ((ReturnStatus != AE_OK) && (ReturnStatus != AE_CTRL_RETURN_VALUE))
    {
        goto Cleanup;
    }

    /*
     * If there is no return value, check if we require a return value for
     * this predefined name. Either one return value is expected, or none,
     * for both methods and other objects.
     *
     * Exit now if there is no return object. Warning if one was expected.
     */
    if (!ReturnObject)
    {
        if ((Predefined->Info.ExpectedBtypes) &&
            (!(Predefined->Info.ExpectedBtypes & ACPI_RTYPE_NONE)))
        {
            ACPI_WARN_PREDEFINED ((AE_INFO, Pathname, ACPI_WARN_ALWAYS,
                "Missing expected return value"));

            Status = AE_AML_NO_RETURN_VALUE;
        }
        goto Cleanup;
    }

    /*
     * Return value validation and possible repair.
     *
     * 1) Don't perform return value validation/repair if this feature
     * has been disabled via a global option.
     *
     * 2) We have a return value, but if one wasn't expected, just exit,
     * this is not a problem. For example, if the "Implicit Return"
     * feature is enabled, methods will always return a value.
     *
     * 3) If the return value can be of any type, then we cannot perform
     * any validation, just exit.
     */
    if (AcpiGbl_DisableAutoRepair ||
        (!Predefined->Info.ExpectedBtypes) ||
        (Predefined->Info.ExpectedBtypes == ACPI_RTYPE_ALL))
    {
        goto Cleanup;
    }

    /* Create the parameter data block for object validation */

    Data = ACPI_ALLOCATE_ZEROED (sizeof (ACPI_PREDEFINED_DATA));
    if (!Data)
    {
        goto Cleanup;
    }
    Data->Predefined = Predefined;
    Data->Node = Node;
    Data->NodeFlags = Node->Flags;
    Data->Pathname = Pathname;

    /*
     * Check that the type of the main return object is what is expected
     * for this predefined name
     */
    Status = AcpiNsCheckObjectType (Data, ReturnObjectPtr,
                Predefined->Info.ExpectedBtypes, ACPI_NOT_PACKAGE_ELEMENT);
    if (ACPI_FAILURE (Status))
    {
        goto Exit;
    }

    /*
     * For returned Package objects, check the type of all sub-objects.
     * Note: Package may have been newly created by call above.
     */
    if ((*ReturnObjectPtr)->Common.Type == ACPI_TYPE_PACKAGE)
    {
        Data->ParentPackage = *ReturnObjectPtr;
        Status = AcpiNsCheckPackage (Data, ReturnObjectPtr);
        if (ACPI_FAILURE (Status))
        {
            goto Exit;
        }
    }

    /*
     * The return object was OK, or it was successfully repaired above.
     * Now make some additional checks such as verifying that package
     * objects are sorted correctly (if required) or buffer objects have
     * the correct data width (bytes vs. dwords). These repairs are
     * performed on a per-name basis, i.e., the code is specific to
     * particular predefined names.
     */
    Status = AcpiNsComplexRepairs (Data, Node, Status, ReturnObjectPtr);

Exit:
    /*
     * If the object validation failed or if we successfully repaired one
     * or more objects, mark the parent node to suppress further warning
     * messages during the next evaluation of the same method/object.
     */
    if (ACPI_FAILURE (Status) || (Data->Flags & ACPI_OBJECT_REPAIRED))
    {
        Node->Flags |= ANOBJ_EVALUATED;
    }
    ACPI_FREE (Data);

Cleanup:
    ACPI_FREE (Pathname);
    return (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiNsCheckParameterCount
 *
 * PARAMETERS:  Pathname        - Full pathname to the node (for error msgs)
 *              Node            - Namespace node for the method/object
 *              UserParamCount  - Number of args passed in by the caller
 *              Predefined      - Pointer to entry in predefined name table
 *
 * RETURN:      None
 *
 * DESCRIPTION: Check that the declared (in ASL/AML) parameter count for a
 *              predefined name is what is expected (i.e., what is defined in
 *              the ACPI specification for this predefined name.)
 *
 ******************************************************************************/

void
AcpiNsCheckParameterCount (
    char                        *Pathname,
    ACPI_NAMESPACE_NODE         *Node,
    UINT32                      UserParamCount,
    const ACPI_PREDEFINED_INFO  *Predefined)
{
    UINT32                      ParamCount;
    UINT32                      RequiredParamsCurrent;
    UINT32                      RequiredParamsOld;


    /* Methods have 0-7 parameters. All other types have zero. */

    ParamCount = 0;
    if (Node->Type == ACPI_TYPE_METHOD)
    {
        ParamCount = Node->Object->Method.ParamCount;
    }

    if (!Predefined)
    {
        /*
         * Check the parameter count for non-predefined methods/objects.
         *
         * Warning if too few or too many arguments have been passed by the
         * caller. An incorrect number of arguments may not cause the method
         * to fail. However, the method will fail if there are too few
         * arguments and the method attempts to use one of the missing ones.
         */
        if (UserParamCount < ParamCount)
        {
            ACPI_WARN_PREDEFINED ((AE_INFO, Pathname, ACPI_WARN_ALWAYS,
                "Insufficient arguments - needs %u, found %u",
                ParamCount, UserParamCount));
        }
        else if (UserParamCount > ParamCount)
        {
            ACPI_WARN_PREDEFINED ((AE_INFO, Pathname, ACPI_WARN_ALWAYS,
                "Excess arguments - needs %u, found %u",
                ParamCount, UserParamCount));
        }
        return;
    }

    /*
     * Validate the user-supplied parameter count.
     * Allow two different legal argument counts (_SCP, etc.)
     */
    RequiredParamsCurrent = Predefined->Info.ParamCount & 0x0F;
    RequiredParamsOld = Predefined->Info.ParamCount >> 4;

    if (UserParamCount != ACPI_UINT32_MAX)
    {
        if ((UserParamCount != RequiredParamsCurrent) &&
            (UserParamCount != RequiredParamsOld))
        {
            ACPI_WARN_PREDEFINED ((AE_INFO, Pathname, ACPI_WARN_ALWAYS,
                "Parameter count mismatch - "
                "caller passed %u, ACPI requires %u",
                UserParamCount, RequiredParamsCurrent));
        }
    }

    /*
     * Check that the ASL-defined parameter count is what is expected for
     * this predefined name (parameter count as defined by the ACPI
     * specification)
     */
    if ((ParamCount != RequiredParamsCurrent) &&
        (ParamCount != RequiredParamsOld))
    {
        ACPI_WARN_PREDEFINED ((AE_INFO, Pathname, Node->Flags,
            "Parameter count mismatch - ASL declared %u, ACPI requires %u",
            ParamCount, RequiredParamsCurrent));
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiNsCheckForPredefinedName
 *
 * PARAMETERS:  Node            - Namespace node for the method/object
 *
 * RETURN:      Pointer to entry in predefined table. NULL indicates not found.
 *
 * DESCRIPTION: Check an object name against the predefined object list.
 *
 ******************************************************************************/

const ACPI_PREDEFINED_INFO *
AcpiNsCheckForPredefinedName (
    ACPI_NAMESPACE_NODE         *Node)
{
    const ACPI_PREDEFINED_INFO  *ThisName;


    /* Quick check for a predefined name, first character must be underscore */

    if (Node->Name.Ascii[0] != '_')
    {
        return (NULL);
    }

    /* Search info table for a predefined method/object name */

    ThisName = PredefinedNames;
    while (ThisName->Info.Name[0])
    {
        if (ACPI_COMPARE_NAME (Node->Name.Ascii, ThisName->Info.Name))
        {
            return (ThisName);
        }

        /*
         * Skip next entry in the table if this name returns a Package
         * (next entry contains the package info)
         */
        if (ThisName->Info.ExpectedBtypes & ACPI_RTYPE_PACKAGE)
        {
            ThisName++;
        }

        ThisName++;
    }

    return (NULL); /* Not found */
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiNsCheckObjectType
 *
 * PARAMETERS:  Data            - Pointer to validation data structure
 *              ReturnObjectPtr - Pointer to the object returned from the
 *                                evaluation of a method or object
 *              ExpectedBtypes  - Bitmap of expected return type(s)
 *              PackageIndex    - Index of object within parent package (if
 *                                applicable - ACPI_NOT_PACKAGE_ELEMENT
 *                                otherwise)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Check the type of the return object against the expected object
 *              type(s). Use of Btype allows multiple expected object types.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiNsCheckObjectType (
    ACPI_PREDEFINED_DATA        *Data,
    ACPI_OPERAND_OBJECT         **ReturnObjectPtr,
    UINT32                      ExpectedBtypes,
    UINT32                      PackageIndex)
{
    ACPI_OPERAND_OBJECT         *ReturnObject = *ReturnObjectPtr;
    ACPI_STATUS                 Status = AE_OK;
    UINT32                      ReturnBtype;
    char                        TypeBuffer[48]; /* Room for 5 types */


    /*
     * If we get a NULL ReturnObject here, it is a NULL package element.
     * Since all extraneous NULL package elements were removed earlier by a
     * call to AcpiNsRemoveNullElements, this is an unexpected NULL element.
     * We will attempt to repair it.
     */
    if (!ReturnObject)
    {
        Status = AcpiNsRepairNullElement (Data, ExpectedBtypes,
                    PackageIndex, ReturnObjectPtr);
        if (ACPI_SUCCESS (Status))
        {
            return (AE_OK); /* Repair was successful */
        }
        goto TypeErrorExit;
    }

    /* A Namespace node should not get here, but make sure */

    if (ACPI_GET_DESCRIPTOR_TYPE (ReturnObject) == ACPI_DESC_TYPE_NAMED)
    {
        ACPI_WARN_PREDEFINED ((AE_INFO, Data->Pathname, Data->NodeFlags,
            "Invalid return type - Found a Namespace node [%4.4s] type %s",
            ReturnObject->Node.Name.Ascii,
            AcpiUtGetTypeName (ReturnObject->Node.Type)));
        return (AE_AML_OPERAND_TYPE);
    }

    /*
     * Convert the object type (ACPI_TYPE_xxx) to a bitmapped object type.
     * The bitmapped type allows multiple possible return types.
     *
     * Note, the cases below must handle all of the possible types returned
     * from all of the predefined names (including elements of returned
     * packages)
     */
    switch (ReturnObject->Common.Type)
    {
    case ACPI_TYPE_INTEGER:
        ReturnBtype = ACPI_RTYPE_INTEGER;
        break;

    case ACPI_TYPE_BUFFER:
        ReturnBtype = ACPI_RTYPE_BUFFER;
        break;

    case ACPI_TYPE_STRING:
        ReturnBtype = ACPI_RTYPE_STRING;
        break;

    case ACPI_TYPE_PACKAGE:
        ReturnBtype = ACPI_RTYPE_PACKAGE;
        break;

    case ACPI_TYPE_LOCAL_REFERENCE:
        ReturnBtype = ACPI_RTYPE_REFERENCE;
        break;

    default:
        /* Not one of the supported objects, must be incorrect */

        goto TypeErrorExit;
    }

    /* Is the object one of the expected types? */

    if (ReturnBtype & ExpectedBtypes)
    {
        /* For reference objects, check that the reference type is correct */

        if (ReturnObject->Common.Type == ACPI_TYPE_LOCAL_REFERENCE)
        {
            Status = AcpiNsCheckReference (Data, ReturnObject);
        }

        return (Status);
    }

    /* Type mismatch -- attempt repair of the returned object */

    Status = AcpiNsRepairObject (Data, ExpectedBtypes,
                PackageIndex, ReturnObjectPtr);
    if (ACPI_SUCCESS (Status))
    {
        return (AE_OK); /* Repair was successful */
    }


TypeErrorExit:

    /* Create a string with all expected types for this predefined object */

    AcpiNsGetExpectedTypes (TypeBuffer, ExpectedBtypes);

    if (PackageIndex == ACPI_NOT_PACKAGE_ELEMENT)
    {
        ACPI_WARN_PREDEFINED ((AE_INFO, Data->Pathname, Data->NodeFlags,
            "Return type mismatch - found %s, expected %s",
            AcpiUtGetObjectTypeName (ReturnObject), TypeBuffer));
    }
    else
    {
        ACPI_WARN_PREDEFINED ((AE_INFO, Data->Pathname, Data->NodeFlags,
            "Return Package type mismatch at index %u - "
            "found %s, expected %s", PackageIndex,
            AcpiUtGetObjectTypeName (ReturnObject), TypeBuffer));
    }

    return (AE_AML_OPERAND_TYPE);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiNsCheckReference
 *
 * PARAMETERS:  Data            - Pointer to validation data structure
 *              ReturnObject    - Object returned from the evaluation of a
 *                                method or object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Check a returned reference object for the correct reference
 *              type. The only reference type that can be returned from a
 *              predefined method is a named reference. All others are invalid.
 *
 ******************************************************************************/

static ACPI_STATUS
AcpiNsCheckReference (
    ACPI_PREDEFINED_DATA        *Data,
    ACPI_OPERAND_OBJECT         *ReturnObject)
{

    /*
     * Check the reference object for the correct reference type (opcode).
     * The only type of reference that can be converted to an ACPI_OBJECT is
     * a reference to a named object (reference class: NAME)
     */
    if (ReturnObject->Reference.Class == ACPI_REFCLASS_NAME)
    {
        return (AE_OK);
    }

    ACPI_WARN_PREDEFINED ((AE_INFO, Data->Pathname, Data->NodeFlags,
        "Return type mismatch - unexpected reference object type [%s] %2.2X",
        AcpiUtGetReferenceName (ReturnObject),
        ReturnObject->Reference.Class));

    return (AE_AML_OPERAND_TYPE);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiNsGetExpectedTypes
 *
 * PARAMETERS:  Buffer          - Pointer to where the string is returned
 *              ExpectedBtypes  - Bitmap of expected return type(s)
 *
 * RETURN:      Buffer is populated with type names.
 *
 * DESCRIPTION: Translate the expected types bitmap into a string of ascii
 *              names of expected types, for use in warning messages.
 *
 ******************************************************************************/

static void
AcpiNsGetExpectedTypes (
    char                        *Buffer,
    UINT32                      ExpectedBtypes)
{
    UINT32                      ThisRtype;
    UINT32                      i;
    UINT32                      j;


    j = 1;
    Buffer[0] = 0;
    ThisRtype = ACPI_RTYPE_INTEGER;

    for (i = 0; i < ACPI_NUM_RTYPES; i++)
    {
        /* If one of the expected types, concatenate the name of this type */

        if (ExpectedBtypes & ThisRtype)
        {
            ACPI_STRCAT (Buffer, &AcpiRtypeNames[i][j]);
            j = 0;              /* Use name separator from now on */
        }
        ThisRtype <<= 1;    /* Next Rtype */
    }
}
