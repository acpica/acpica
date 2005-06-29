
/******************************************************************************
 * 
 * Module Name: psxfield- Parser/Interpreter interface field routines
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

#define __PSXFIELD_C__

#include <acpi.h>
#include <amlcode.h>
#include <parser.h>
#include <interp.h>
#include <namesp.h>


#define _COMPONENT          PARSER
        MODULE_NAME         ("psxfield");



/*****************************************************************************
 *
 * FUNCTION:    PsxCreateField 
 *
 * PARAMETERS:  Op              - Op containing the Field definition and args
 *              Region          - NTE for the containing Operation Region
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create a new field in the specified operation region
 *
 ****************************************************************************/

ACPI_STATUS
PsxCreateField (
    ACPI_GENERIC_OP         *Op,
    ACPI_HANDLE             Region,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_STATUS             Status = AE_AML_ERROR;
    ACPI_GENERIC_OP         *Arg;
    NAME_TABLE_ENTRY        *Entry;
    char                    Buffer[5];
    UINT8                   FieldFlags;
    UINT32                  FieldBitPosition = 0;


    FUNCTION_TRACE_PTR ("PsxCreateField", Op);
    

    Arg = Op->Value.Arg;

    /* First arg is the field flags */

    FieldFlags = (UINT8) Arg->Value.Integer;
    Arg = Arg->Next;

    /* Each remaining arg is a Named Field */

    while (Arg)
    {
        switch (Arg->Opcode)
        {
        case AML_RESERVEDFIELD:

            FieldBitPosition += Arg->Value.Size;
            break;


        case AML_ACCESSFIELD:

            /* TBD: Arg->Value.Integer contains both AccessType and AccessAttrib */
            break;


        case AML_NAMEDFIELD:

            *(UINT32 *) Buffer = (((ACPI_NAMED_OP *)Arg)->Name);
            Buffer[4] = 0;

            Status = NsLookup (WalkState->ScopeInfo, Buffer, INTERNAL_TYPE_DefField, IMODE_LoadPass1, 
                                        NS_NO_UPSEARCH | NS_DONT_OPEN_SCOPE, NULL, &Entry);
            if (ACPI_FAILURE (Status))
            {
                break;
            }

            /* Initialize an object for the new NTE that is on the object stack */

            Status = AmlPrepDefFieldValue (Entry, Region, FieldFlags, FieldBitPosition, Arg->Value.Size);

            /* Keep track of bit position for the *next* field */

            FieldBitPosition += Arg->Value.Size;
            break;
        }

        Arg = Arg->Next;
    }

    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 *
 * FUNCTION:    PsxCreateBankField
 *
 * PARAMETERS:  Op              - Op containing the Field definition and args
 *              Region          - NTE for the containing Operation Region
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create a new bank field in the specified operation region
 *
 ****************************************************************************/

ACPI_STATUS
PsxCreateBankField (
    ACPI_GENERIC_OP         *Op,
    ACPI_HANDLE             Region,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_STATUS             Status = AE_AML_ERROR;
    ACPI_GENERIC_OP         *Arg;
    NAME_TABLE_ENTRY        *BankReg;
    NAME_TABLE_ENTRY        *Entry;
    UINT32                  BankValue;
    char                    Buffer[5];
    UINT8                   FieldFlags;
    UINT32                  FieldBitPosition = 0;

    
    FUNCTION_TRACE_PTR ("PsxCreateBankField", Op);


    /* First arg is the Bank Register */

    Arg = Op->Value.Arg;

    Status = NsLookup (WalkState->ScopeInfo, Arg->Value.String, INTERNAL_TYPE_BankFieldDefn, IMODE_LoadPass1, 
                                NS_NO_UPSEARCH | NS_DONT_OPEN_SCOPE, NULL, &BankReg);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Second arg is the BankValue */
    
    Arg = Arg->Next;
    BankValue = Arg->Value.Integer;


    /* Next arg is the field flags */

    Arg = Arg->Next;
    FieldFlags = (UINT8) Arg->Value.Integer;

    /* Each remaining arg is a Named Field */

    Arg = Arg->Next;
    while (Arg)
    {
        switch (Arg->Opcode)
        {
        case AML_RESERVEDFIELD:

            FieldBitPosition += Arg->Value.Size;
            break;


        case AML_ACCESSFIELD:

            /* TBD: Arg->Value.Integer contains both AccessType and AccessAttrib */
            break;


        case AML_NAMEDFIELD:

            *(UINT32 *) Buffer = (((ACPI_NAMED_OP *)Arg)->Name);
            Buffer[4] = 0;

            Status = NsLookup (WalkState->ScopeInfo, Buffer, INTERNAL_TYPE_DefField, IMODE_LoadPass1, 
                                        NS_NO_UPSEARCH | NS_DONT_OPEN_SCOPE, NULL, &Entry);
            if (ACPI_FAILURE (Status))
            {
                break;
            }

            /* Initialize an object for the new NTE that is on the object stack */

            Status = AmlPrepBankFieldValue (Entry, Region, BankReg, BankValue, FieldFlags, FieldBitPosition, Arg->Value.Size);

            /* Keep track of bit position for the *next* field */

            FieldBitPosition += Arg->Value.Size;
            break;

        }

        Arg = Arg->Next;
    }

    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 *
 * FUNCTION:    PsxCreateIndexField
 *
 * PARAMETERS:  Op              - Op containing the Field definition and args
 *              Region          - NTE for the containing Operation Region
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create a new index field in the specified operation region
 *
 ****************************************************************************/

ACPI_STATUS
PsxCreateIndexField (
    ACPI_GENERIC_OP         *Op,
    ACPI_HANDLE             Region,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_STATUS             Status;
    ACPI_GENERIC_OP         *Arg;
    NAME_TABLE_ENTRY        *Entry;
    char                    Buffer[5];
    NAME_TABLE_ENTRY        *IndexReg;
    NAME_TABLE_ENTRY        *DataReg;
    UINT8                   FieldFlags;
    UINT32                  FieldBitPosition = 0;

    
    FUNCTION_TRACE_PTR ("PsxCreateIndexField", Op);



    /* Name (in Op) is the Index register */

    *(UINT32 *) Buffer = (((ACPI_NAMED_OP *)Op)->Name);
    Buffer[4] = 0;

    Status = NsLookup (WalkState->ScopeInfo, Buffer, ACPI_TYPE_Any, IMODE_LoadPass1, 
                                NS_NO_UPSEARCH | NS_DONT_OPEN_SCOPE, NULL, &IndexReg);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* First arg is the data register */

    Arg = Op->Value.Arg;

    Status = NsLookup (WalkState->ScopeInfo, Arg->Value.String, INTERNAL_TYPE_IndexFieldDefn, IMODE_LoadPass1, 
                                NS_NO_UPSEARCH | NS_DONT_OPEN_SCOPE, NULL, &DataReg);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }


    /* Next arg is the field flags */

    Arg = Arg->Next;
    FieldFlags = (UINT8) Arg->Value.Integer;


    /* Each remaining arg is a Named Field */

    Arg = Arg->Next;
    while (Arg)
    {
        switch (Arg->Opcode)
        {
        case AML_RESERVEDFIELD:

            FieldBitPosition += Arg->Value.Size;
            break;


        case AML_ACCESSFIELD:

            /* TBD: Arg->Value.Integer contains both AccessType and AccessAttrib */
            break;


        case AML_NAMEDFIELD:

            *(UINT32 *) Buffer = (((ACPI_NAMED_OP *)Arg)->Name);
            Buffer[4] = 0;

            Status = NsLookup (WalkState->ScopeInfo, Buffer, INTERNAL_TYPE_IndexField, IMODE_LoadPass1, 
                                        NS_NO_UPSEARCH | NS_DONT_OPEN_SCOPE, NULL, &Entry);
            if (ACPI_FAILURE (Status))
            {
                break;
            }

            /* Initialize an object for the new NTE that is on the object stack */

            Status = AmlPrepIndexFieldValue (Entry, IndexReg, DataReg, FieldFlags, FieldBitPosition, Arg->Value.Size);

            /* Keep track of bit position for the *next* field */

            FieldBitPosition += Arg->Value.Size;
            break;


        default:

            DEBUG_PRINT (ACPI_ERROR, ("PsxEnterIndexField: Invalid opcode in field list: %X\n", Arg->Opcode));
            Status = AE_AML_ERROR;
            break;
        }

        Arg = Arg->Next;
    }

    return_ACPI_STATUS (Status);
}





