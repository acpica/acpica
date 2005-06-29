
/******************************************************************************
 * 
 * Module Name: isutils - interpreter/scanner utilities
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
 * 2.1. Intel grants, free of charge, to any person ("Licensee") obtaining a 
 * copy of the source code appearing in this file ("Covered Code") a license 
 * under Intel's copyrights in the base code distributed originally by Intel 
 * ("Original Intel Code") to copy, make derivatives, distribute, use and 
 * display any portion of the Covered Code in any form; and
 *
 * 2.2. Intel grants Licensee a non-exclusive and non-transferable patent 
 * license (without the right to sublicense), under only those claims of Intel
 * patents that are infringed by the Original Intel Code, to make, use, sell, 
 * offer to sell, and import the Covered Code and derivative works thereof 
 * solely to the minimum extent necessary to exercise the above copyright 
 * license, and in no event shall the patent license extend to any additions to
 * or modifications of the Original Intel Code.  No other license or right is 
 * granted directly or by implication, estoppel or otherwise;
 *
 * the above copyright and patent license is granted only if the following 
 * conditions are met:
 *
 * 3. Conditions 
 *
 * 3.1. Redistribution of source code of any substantial portion of the Covered 
 * Code or modification must include the above Copyright Notice, the above 
 * License, this list of Conditions, and the following Disclaimer and Export 
 * Compliance provision.  In addition, Licensee must cause all Covered Code to 
 * which Licensee contributes to contain a file documenting the changes 
 * Licensee made to create that Covered Code and the date of any change.  
 * Licensee must include in that file the documentation of any changes made by
 * any predecessor Licensee.  Licensee must include a prominent statement that
 * the modification is derived, directly or indirectly, from Original Intel 
 * Code.
 *
 * 3.2. Redistribution in binary form of any substantial portion of the Covered 
 * Code or modification must reproduce the above Copyright Notice, and the 
 * following Disclaimer and Export Compliance provision in the documentation 
 * and/or other materials provided with the distribution.
 *
 * 3.3. Intel retains all right, title, and interest in and to the Original 
 * Intel Code.
 *
 * 3.4. Neither the name Intel nor any other trademark owned or controlled by 
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
 * event Licensee exports any such software from the United States or re-
 * exports any such software from a foreign destination, Licensee shall ensure
 * that the distribution and export/re-export of the software is in compliance 
 * with all laws, regulations, orders, or other restrictions of the U.S. Export 
 * Administration Regulations. Licensee agrees that neither it nor any of its 
 * subsidiaries will export/re-export any technical data, process, software, or 
 * service, directly or indirectly, to any country for which the United States 
 * government or any agency thereof requires an export license, other 
 * governmental approval, or letter of assurance, without first obtaining such
 * license, approval or letter.
 *
 *****************************************************************************/


#define __ISEXPRS_C__

#include <acpi.h>
#include <interpreter.h>
#include <amlcode.h>
#include <namespace.h>
#include <string.h>

#define _THIS_MODULE        "isutils.c"
#define _COMPONENT          INTERPRETER


static ST_KEY_DESC_TABLE KDT[] = {
    {"0000", '1', "DigitsNeeded: impossible base", "DigitsNeeded: impossible base"},
    {NULL, 'I', NULL, NULL}
};



/*****************************************************************************
 * 
 * FUNCTION:    AmlAppendBlockOwner
 *
 * PARAMETERS:  *Owner
 *
 * DESCRIPTION: Print block-owner data
 *
 ****************************************************************************/

void
AmlAppendBlockOwner (void *Owner)
{

#ifdef PLUMBER

#if 1
    vPlumber ("internal type mismatch", 3);
#endif

    DEBUG_PRINT (ACPI_ERROR, ("Block Owner: %s\n", pcIdentifyOwner (Owner)));

#endif  /* PLUMBER */
}



/*****************************************************************************
 * 
 * FUNCTION:    AmlAppendOperandDiag
 *
 * PARAMETERS:  *FileName       - Name of source file
 *              LineNum         - Line Number in file
 *              OpCode          - OpCode being executed
 *              NumOperands     - Number of operands PrepStack tried to check
 *
 * DESCRIPTION: Print diagnostic information about operands.
 *              This function is intended to be called after PrepStack
 *              has returned S_ERROR.
 *
 ****************************************************************************/

void
AmlAppendOperandDiag(char *FileName, INT32 LineNum, UINT16 OpCode, INT32 NumOperands)
{
    meth            Method;


    AmlGetCurrentLocation (&Method);

    DEBUG_PRINT (ACPI_ERROR, (" [%s:%d, opcode = %s AML offset %04x]\n",
                    FileName, LineNum,
                    (OpCode > UCHAR_MAX)
                        ? LongOps[OpCode & 0x00ff]
                        : ShortOps[OpCode],
                    Method.Offset));

    if (GetDebugLevel () > 0)
    {
        DUMP_STACK (MODE_Exec,
                      (OpCode > UCHAR_MAX)
                      ? LongOps[OpCode & 0x00ff]
                      : ShortOps[OpCode],
                      NumOperands,
                      "after PrepStack failed");
    }
}



/*****************************************************************************
 *
 * FUNCTION:    AmlBufSeq
 *
 * RETURN:      The next buffer descriptor sequence number
 *
 * DESCRIPTION: Provide a unique sequence number for each Buffer descriptor
 *              allocated during the interpreter's existence.  These numbers
 *              are used to relate FieldUnit descriptors to the Buffers
 *              within which the fields are defined.
 *
 *              Just increment the global counter and return it.
 *
 ****************************************************************************/

UINT32 
AmlBufSeq (void)
{
    
    return ++BufSeq;
}


/*****************************************************************************
 * 
 * FUNCTION:    DeleteObject
 *
 * PARAMETERS:  **ObjDesc           - Descriptor to be deleted
 *
 * DESCRIPTION: If the passed descriptor pointer does not point into the
 *              AML block and is not an NsHandle, free the descriptor.
 *
 *              Note that the parameter is the address of the descriptor
 *              pointer, so that the descriptor pointer can be set to NULL
 *              after the descriptor is freed.
 *
 ****************************************************************************/

void
DeleteObject (OBJECT_DESCRIPTOR **ObjDesc)
{

    FUNCTION_TRACE ("DeleteObject");
    DEBUG_PRINT (ACPI_INFO, ("DeleteObject: %x\n", *ObjDesc));


    /*
     * Be very careful about what we delete
     */

    /* 
     * XXX: This is not the best solution!
     * XXX: And may not work in all cases!!
     */


    if ((OBJECT_DESCRIPTOR **) 0 !=    ObjDesc  &&
        (OBJECT_DESCRIPTOR *) 0 !=    *ObjDesc  &&
        !AmlIsInPCodeBlock ((UINT8 *) *ObjDesc) &&
        !IS_NS_HANDLE                  (*ObjDesc) &&
        !AmlIsMethodValue            (*ObjDesc) &&
        !IsNsValue                   (*ObjDesc))
    {

        DEBUG_PRINT (ACPI_INFO, ("DeleteObject: Actually deleting %x\n", *ObjDesc));

        OsdFree (*ObjDesc);

        DEBUG_PRINT (ACPI_INFO, ("DeleteObject: Successfully deleted %x\n", *ObjDesc));

    }

    FUNCTION_EXIT;
}


#ifdef PLUMBER
/****************************************************************************
 * 
 * FUNCTION:    AmlMarkPackage
 *
 * PARAMETERS:  *ObjDesc        - Descriptor of package to be marked
 *
 * DESCRIPTION: "Mark" all storage belonging to a package, including
 *              contained packages.
 *
 ***************************************************************************/

void 
AmlMarkPackage (OBJECT_DESCRIPTOR *ObjDesc)
{
    UINT16          Count;


    FUNCTION_TRACE ("AmlMarkPackage");


    if (ObjDesc)
    {   
        /*  ObjDesc valid  */
        
        if (ObjDesc->Package.PackageElems)
        {    
            /*  ObjDesc->Package.PackageElems valid  */
            
            OBJECT_DESCRIPTOR           **Elems = ObjDesc->Package.PackageElems;

            for (Count = ObjDesc->Package.PkgCount; Count; --Count)
            {
                if ((*Elems) && (Package == (*Elems)->ValType))
                {
                    AmlMarkPackage (*Elems);
                }

                ++Elems;
            }
            
            MarkBlock (ObjDesc->Package.PackageElems);
        }
        
        MarkBlock (ObjDesc);
    } 

    FUNCTION_EXIT;
}


/****************************************************************************
 *
 * FUNCTION:    AmlMarkObject
 *
 * PARAMETERS:  *ObjDesc        - Descriptor of object to be marked
 *
 * DESCRIPTION: "Mark" all storage belonging to an object
 *
 ***************************************************************************/

void 
AmlMarkObject (OBJECT_DESCRIPTOR *ObjDesc)
{
    FUNCTION_TRACE ("AmlMarkObject");


    if (ObjDesc)
    {   
        /*  ObjDesc valid  */
        
        MarkBlock(ObjDesc);

        switch (ObjDesc->ValType)
        {
            case String:
                
                /* Avoid marking value if it is in the AML stream */
                
                if (!iIsInPCodeBlock (ObjDesc->String.String))
                {
                    MarkBlock (ObjDesc->String.String);
                }
                break;

            case Buffer:
                
                /* Avoid marking value if it is in the AML stream */
                
                if (!iIsInPCodeBlock (ObjDesc->Buffer.Buffer))
                {
                    MarkBlock (ObjDesc->Buffer.Buffer);
                }
                break;

            case Package:
                AmlMarkPackage (ObjDesc);
                break;

            case BankField:
                if (ObjDesc->BankField.Container)
                {
                    AmlMarkObject (ObjDesc->BankField.Container);
                }
                break;

            case DefField:
                if (ObjDesc->Field.Container)
                {
                    AmlMarkObject (ObjDesc->Field.Container);
                }
                break;

            case FieldUnit:
                if (ObjDesc->FieldUnit.Container)
                {
                    AmlMarkObject (ObjDesc->FieldUnit.Container);
                }
                break;


            case Lvalue:
                
                /* XXX - ? mark something if ObjDesc->Lvalue.OpCode == IndexOp ? */
                break;

            default:
                break;
        }
    } 

    FUNCTION_EXIT;
}


/*****************************************************************************
 *
 * FUNCTION:    MarkObjectStack
 *
 * PARAMETERS:  *Count          - Count of objects marked
 *
 * DESCRIPTION: Mark blocks occupied by currently-active objects on stack
 *
 ****************************************************************************/

void 
MarkObjectStack (INT32 *Count)
{
    INT32           Index;


    FUNCTION_TRACE ("MarkObjectStack");


    for (Index = 0; Index <= ObjStackTop; ++Index)
    {   
        /*  For each entry on the stack */

        if (ObjStack[Index] &&
            !IS_NS_HANDLE (ObjStack[Index]))
        {   
            /*  Mark value's storage    */
            
            if (Count)
            {
                ++*Count;
            }

            AmlMarkObject (ObjStack[Index]);
        }
    }

    FUNCTION_EXIT;
} 

#endif   /* PLUMBER */

/******************************************************************************
 * 
 * FUNCTION:    DigitsNeeded
 *
 * PARAMETERS:  val             - Value to be represented
 *              base            - Base of representation
 *
 * RETURN:      the number of digits needed to represent val in base
 *
 *****************************************************************************/

INT32
DigitsNeeded (INT32 val, INT32 base)
{
    INT32       NumDigits = 0;


    FUNCTION_TRACE ("DigitsNeeded");


    if (base < 1)
    {   
        /*  impossible base */

        REPORT_ERROR (&KDT[0]);
    }

    else
    {
        for (NumDigits = 1 + (val < 0) ; val /= base ; ++NumDigits)
        { ; }
    }

    FUNCTION_EXIT;
    return NumDigits;
}


