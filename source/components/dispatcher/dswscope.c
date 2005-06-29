/*_________________________________________________________________________
 |
 |
 |           Copyright (C) Intel Corporation 1994-1997
 |
 | All rights reserved.  No part of this program or publication may be
 | reproduced, transmitted, transcribed, stored in a retrieval system, or
 | translated into any language or computer language, in any form or by any
 | means, electronic, mechanical, magnetic, optical, chemical, manual, or
 | otherwise, without the prior written permission of Intel Corporation.
 |__________________________________________________________________________
 |
 | ModuleName: nsstack - Scope stack manipulation
 |__________________________________________________________________________
*/

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
 * PARAMETERS:  nte     *NewScope,             name to be made current
 *              NsType  Type,                  type of frame being pushed
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

        if (CurrentScope < &ScopeStack[MAXNEST-1])   /* check for overflow */
        {
            /*  no Scope stack overflow */

            CurrentScope++;
            CurrentScope->Scope = NewScope;
            CurrentScope->Type = Type;

            if (CurrentScope->Scope == Root)
            {
                NsCurrentSize = NsRootSize;
            }
        
            else
            {
                NsCurrentSize = TABLSIZE;
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
 * PARAMETERS:  NsHandle NewScope,             name to be made current
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
       (nte *) 0 == ((nte *) NewScope)->ChildScope)
    {
        /*  NewScope or NewScope->ChildScope invalid    */

        REPORT_ERROR (&KDT[3]);
    }

    else
    {
        if (CurrentScope < &ScopeStack[MAXNEST-1])   /* check for overflow */
        {
            NsPushCurrentScope (((nte *) NewScope)->ChildScope, Method);
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
 * PARAMETERS:  NsType Type    The type of frame to be found
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

    DEBUG_PRINT (TRACE_EXEC, ("Popping Scope till type (%i) is found\n", Type));

    while (CurrentScope > &ScopeStack[0])
    {
        CurrentScope--;

        if (Root == CurrentScope->Scope)
        {
            NsCurrentSize = NsRootSize;
        }
        else
        {
            NsCurrentSize = TABLSIZE;
        }

        Count++;


        DEBUG_PRINT (TRACE_EXEC, ("Popped %i ", (CurrentScope+1)->Type));

        if ((Any == Type) || (Type == (CurrentScope + 1)->Type))
        {
            DEBUG_PRINT (TRACE_EXEC, ("Found %i\n", Type));
            return Count;
        }
    }

    DEBUG_PRINT (TRACE_EXEC,("%i Not Found\n", Type));
    return -Count;
}



