
/******************************************************************************
 * 
 * Module Name: nsstack - Scope stack manipulation
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


#define __NSSTACK_C__

#include <acpi.h>
#include <interpreter.h>
#include <namespace.h>


#define _THIS_MODULE        "nsstack.c"
#define _COMPONENT          NAMESPACE


static ST_KEY_DESC_TABLE KDT[] = {
    {"0000", '1', "NsPushCurrentScope: null scope passed", "NsPushCurrentScope: null scope passed"},
    {"0001", 'W', "NsPushCurrentScope: type code out of range", "NsPushCurrentScope: type code out of range"},
    {"0002", '1', "Scope stack overflow", "Scope stack overflow"},
    {"0003", '1', "NsPushMethodScope: null scope passed", "NsPushMethodScope: null scope passed"},
    {"0004", '1', "Scope stack overflow", "Scope stack overflow"},
    {"0005", 'W', "NsPopCurrent: type code out of range", "NsPopCurrent: type code out of range"},
    {NULL, 'I', NULL, NULL}
};



/****************************************************************************
 *
 * FUNCTION:    NsPushCurrentScope
 *
 * PARAMETERS:  *NewScope,              - Name to be made current
 *              Type,                   - Type of frame being pushed
 *
 * DESCRIPTION: Push the current scope on the scope stack, and make the
 *              passed nte current.
 *
 ***************************************************************************/

void
NsPushCurrentScope (nte *NewScope, NsType Type)
{

    FUNCTION_TRACE ("NsPushCurrentScope");


    if (!NewScope)
    {
        /*  invalid scope   */

        REPORT_ERROR (&KDT[0]);
    }

    else
    {
        if (OUTRANGE (Type, NsTypeNames) || 
            BadType == NsTypeNames[Type])
        {
            /*  type code out of range  */

            REPORT_WARNING (&KDT[1]);
        }

        if (CurrentScope < &ScopeStack[MAX_SCOPE_NESTING-1])   /* check for overflow */
        {
            /*  no Scope stack overflow */

            CurrentScope++;
            CurrentScope->Scope = NewScope;
            CurrentScope->Type = Type;

            if (CurrentScope->Scope == RootObject->Scope)
            {
                NsCurrentSize = NsRootSize;
            }
        
            else
            {
                NsCurrentSize = NS_DEFAULT_TABLE_SIZE;
            }
        }
    
        else
        {
            /*  Scope stack overflow    */

            REPORT_ERROR (&KDT[2]);
        }
    }
}


/****************************************************************************
 *
 * FUNCTION:    NsPushMethodScope
 *
 * PARAMETERS:  NewScope,               - Name to be made current
 *
 * DESCRIPTION: Push the current scope on the scope stack, and make the
 *              passed nte current.
 *
 ***************************************************************************/

void
NsPushMethodScope (NsHandle NewScope)
{

    FUNCTION_TRACE ("NsPushMethodScope");


    if (!NewScope || 
       (nte *) 0 == ((nte *) NewScope)->Scope)
    {
        /*  NewScope or NewScope->Scope invalid    */

        REPORT_ERROR (&KDT[3]);
    }

    else
    {
        if (CurrentScope < &ScopeStack[MAX_SCOPE_NESTING-1])   /* check for overflow */
        {
            NsPushCurrentScope (((nte *) NewScope)->Scope, TYPE_Method);
        }
    
        else
        {
            /*  scope stack overflow    */

            REPORT_ERROR (&KDT[4]);
        }
    }
}

/****************************************************************************
 *
 * FUNCTION:    NsPopCurrent
 *
 * PARAMETERS:  Type                - The type of frame to be found
 *
 * DESCRIPTION: Pop the scope stack until a frame of the requested type
 *              is found.
 *
 * RETURN:      Count of frames popped.  If no frame of the requested type
 *              was found, the count is returned as a negative number and
 *              the scope stack is emptied (which sets the current scope
 *              to the root).  If the scope stack was empty at entry, the
 *              function is a no-op and returns 0.
 *
 ***************************************************************************/

INT32
NsPopCurrent (NsType Type)
{
    INT32           Count = 0;


    FUNCTION_TRACE ("NsPopCurrent");


    if (OUTRANGE (Type, NsTypeNames) || BadType == NsTypeNames[Type])
    {
        /*  type code out of range  */

        REPORT_WARNING (&KDT[5]);
    }

    DEBUG_PRINT (TRACE_EXEC, ("Popping Scope till type (%d) is found\n", Type));

    while (CurrentScope > &ScopeStack[0])
    {
        CurrentScope--;

        if (RootObject->Scope == CurrentScope->Scope)
        {
            NsCurrentSize = NsRootSize;
        }
        else
        {
            NsCurrentSize = NS_DEFAULT_TABLE_SIZE;
        }

        Count++;


        DEBUG_PRINT (TRACE_EXEC, ("Popped %d\n", (CurrentScope+1)->Type));

        if ((TYPE_Any == Type) || (Type == (CurrentScope + 1)->Type))
        {
            DEBUG_PRINT (TRACE_EXEC, ("Found %d\n", Type));
            return Count;
        }
    }

    DEBUG_PRINT (TRACE_EXEC,("%d Not Found\n", Type));
    return -Count;
}



