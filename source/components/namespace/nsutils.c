
/******************************************************************************
 * 
 * Module Name: nsutils - Utilities for accessing ACPI namespace
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


#define __NSUTILS_C__

#include <acpi.h>
#include <namespace.h>
#include <interpreter.h>
#include <string.h>


#define _THIS_MODULE        "nsutils.c"
#define _COMPONENT          NAMESPACE



static ST_KEY_DESC_TABLE KDT[] = {
    {"0000", 'W', "NsGetType: Null handle", "NsGetType: Null handle"},
    {"0001", 'W', "NsGetValue: Null handle", "NsGetValue: Null handle"},
    {NULL, 'I', NULL, NULL}
};


/******************************************************************************
 *
 * FUNCTION:    NsWalkNamespace
 *
 * PARAMETERS:  Type                - NsType to search for
 *              StartHandle         - Handle in namespace where search begins
 *              MaxDepth            - Depth to which search is to reach
 *              UserFunction        - Called when an object of "Type" is found
 *              Context             - Passed to user function
 *
 * RETURNS      Return value from the UserFunction if terminated early.
 *              Otherwise, returns NULL.
 *
 * DESCRIPTION: Performs a modified depth-first walk of the namespace tree,
 *              starting (and ending) at the object specified by StartHandle.
 *              The UserFunction is called whenever an object that matches
 *              the type parameter is found.  If the user function returns
 *              a non-zero value, the search is terminated immediately and this
 *              value is returned to the caller.
 *
 *              The point of this procedure is to provide a generic namespace
 *              walk routine that can be called from multiple places to 
 *              provide multiple services;  the User Function can be tailored
 *              to each task, whether it is a print function, a compare 
 *              function, etc.
 *
 ******************************************************************************/


void *
NsWalkNamespace (NsType Type, NsHandle StartHandle, UINT32 MaxDepth,
                 void *(* UserFunction)(NsHandle,UINT32,void *), void *Context)
{
    NsHandle            ObjHandle = 0;
    NsHandle            Scope;
    NsHandle            NewScope;
    void                *UserReturnVal;
    UINT32              Level = 1;


    FUNCTION_TRACE ("NsWalkNamespace");


    /* Parameter validation */

    if (OUTRANGE (Type, NsTypeNames))
    {
        return NULL;
    }

BREAKPOINT3;
    /* Begin search in the scope owned by the starting object */
    /* Failure could be bad scope or simply *no* scope */

    if (ACPI_FAILURE (AcpiGetScope (StartHandle, &Scope)))
    {
        return NULL;
    }

    /* 
     * Traverse the tree of objects until we bubble back up 
     * to where we started.
     */

    while (ObjHandle != StartHandle)
    {
        /* Get the next typed object in this scope.  Null returned if not found */

        if (ACPI_SUCCESS (AcpiGetNextObject (Type, Scope, ObjHandle, &ObjHandle)))
        {
            /* Found an object - process by calling the user function */

            if ((UserReturnVal = UserFunction (ObjHandle, Level, Context)) != 0)
            {
                /* Non-zero from user function means "exit now" */

                return UserReturnVal;
            }

            /* Go down another level if we are allowed to */

            if (Level < MaxDepth)
            {
                /* Check for a valid scope for this object */

                if (ACPI_SUCCESS (AcpiGetScope (ObjHandle, &NewScope)))
                {
                    /* There is a valid scope, we will check for child objects */

                    Level++;
                    ObjHandle = 0;
                    Scope = NewScope;
                }
            }
        }

        else
        {
            /* 
             * No more objects in this scope, go back up to the parent and the 
             * parent's scope (But only back up to where we started the search)
             */
            Level--;
            AcpiGetParent (Scope, &ObjHandle);
            AcpiGetContainingScope (ObjHandle, &Scope);
        }
    }

    return NULL; /* Complete walk, not terminated by user function */
}



/******************************************************************************
 *
 * FUNCTION:    NsChecksum
 *
 * PARAMETERS:  Buffer              - Buffer to checksum
 *              Length              - Size of the buffer
 *
 * RETURNS      8 bit checksum of buffer
 *
 * DESCRIPTION: Computes an 8 bit checksum of the buffer(length) and returns it. 
 *
 ******************************************************************************/

UINT8
NsChecksum (void *Buffer, UINT32 Length)
{
    UINT8       *limit;
    UINT8       *rover;
    UINT8       sum = 0;


    if (Buffer && Length)
    {   
        /*  Buffer and Length are valid   */
        
        limit = (UINT8 *) Buffer + Length;

        for (rover = Buffer; rover < limit; rover++)
            sum += *rover;
    }

    return sum;
}


/****************************************************************************
 *
 * FUNCTION:    NsAllocateNteDesc
 *
 * PARAMETERS:  NteCount            - Count of NTEs to allocate
 *
 * DESCRIPTION: Allocate an array of nte, including prepended link space
 *              Array is set to all zeros via OsdCallcate().
 *
 * RETURN:      The address of the first nte in the array, or NULL
 *
 ***************************************************************************/

nte *
NsAllocateNteDesc (INT32 NteCount)
{
    nte             *NewNteDesc = NULL;
    size_t          AllocSize;


    FUNCTION_TRACE ("AllocateNteDesc");


    AllocSize = (size_t) NteCount * sizeof (nte);

    
    /* Allow room for link to appendage */
    
    AllocSize += sizeof (nte *);

  
    NewNteDesc = LocalCallocate (AllocSize);
    if (NewNteDesc)
    {
        /* Move past the appendage pointer */
    
        NewNteDesc = (nte *) (((UINT8 *) NewNteDesc) + sizeof (nte *));
    }

    DEBUG_PRINT (TRACE_EXEC, ("AllocateNteDesc: NewNteDesc=%p\n", NewNteDesc));

    return NewNteDesc;
}



/****************************************************************************
 *
 * FUNCTION:    NsGetType
 *
 * PARAMETERS:  Handle              - Handle of nte to be examined
 *
 * RETURN:      Type field from nte whose handle is passed
 *
 ***************************************************************************/

NsType
NsGetType (NsHandle handle)
{
    FUNCTION_TRACE ("NsGetType");


    if (!handle)
    {
        /*  Handle invalid  */

        REPORT_WARNING (&KDT[0]);
        return TYPE_Any;
    }

    return ((nte *) handle)->Type;
}


/****************************************************************************
 *
 * FUNCTION:    NsGetValue
 *
 * PARAMETERS:  Handle              - Handle of nte to be examined
 *
 * RETURN:      Value field from nte whose handle is passed
 *
 ***************************************************************************/

void *
NsGetValue (NsHandle handle)
{
    FUNCTION_TRACE ("NsGetValue");


    if (!handle)
    {
        /* handle invalid */

        REPORT_WARNING (&KDT[1]);
        return NULL;
    }

    return ((nte *) handle)->Value;
}


/*****************************************************************************
 *
 * FUNCTION:    IsNsValue
 *
 * PARAMETERS:  *ObjDesc            - An object descriptor
 *
 * RETURN:      TRUE if the passed descriptor is the value of a Name in
 *              the name space, else FALSE
 *
 ****************************************************************************/

INT32
IsNsValue (OBJECT_DESCRIPTOR *ObjDesc)
{

    FUNCTION_TRACE ("IsNsValue");


    return ((NsHandle) 0 != NsFindValue (ObjDesc, NS_ALL, INT_MAX));
}


/****************************************************************************
 *
 * FUNCTION:    NsLocal
 *
 * PARAMETERS:  Type            - A namespace object type
 *
 * RETURN:      LOCAL if names must be found locally in objects of the
 *              passed type, 0 if enclosing scopes should be searched
 *
 ***************************************************************************/

INT32
NsLocal (NsType Type)
{
    FUNCTION_TRACE ("NsLocal");


    if (OUTRANGE (Type, NsProperties))
    {
        /*  type code out of range  */

        REPORT_WARNING (&KDT[1]);
        return 0;
    }

    return NsProperties[Type] & LOCAL;
}


/****************************************************************************
 *
 * FUNCTION:    NsInternalizeName
 *
 * PARAMETERS:  *DottedName             - external representation of name
 *
 * RETURN:      Internal representation of name
 *
 * DESCRIPTION: Convert an external representation (e.g. "\_PR_.CPU0")
 *              to internal form (e.g. 5c 2f 02 5f 50 52 5f 43 50 55 30)
 *
 ****************************************************************************/

char *
NsInternalizeName (char *DottedName)
{
    char            *Result = NULL;
    static char     *IN = NULL;
    static size_t   INsize = 0;
    size_t          i;


    FUNCTION_TRACE ("NsInternalizeName");


    if (DottedName)
    {
        i = strlen (DottedName++) / 5;

        /* 
         * Required length is 4 bytes per segment, plus 1 each for RootPrefix,
         * MultiNamePrefixOp, segment count, trailing null (which is not really
         * needed, but no there's harm in putting it there)
         */

        if (INsize < 4 * i + 4)
        {
            if (IN)
            {
                OsdFree (IN);
            }
            else
            {   /* Buffer Tracking */

                RegisterStaticBlockPtr(&IN);
            }

            INsize = 4 * i + 4;
            IN = LocalCallocate (INsize);
        }

        if (IN)
        {
            strcpy (IN, "\\/");
            for (IN[2] = i, Result = &IN[3]; i; i--)
            {
                strncpy (Result, DottedName, 4);
                Result += 4;
                DottedName += 5;
            }

            if (Result)
            {
                *Result = '\0';
            }
        }
    }

    DEBUG_PRINT (TRACE_EXEC,("NsInternalizeName: returning %p=>\"%s\"\n", IN, IN ? IN : ""));     
    
    return IN;
}









#ifdef PLUMBER

#define MAX_STATIC_BLOCKS 10

static void     **StaticBlockList[MAX_STATIC_BLOCKS];
static INT32    NumStaticBlocks = 0;



/****************************************************************************
 *
 * FUNCTION:    RegisterStaticBlockPtr
 *
 * PARAMETERS:  **BlkPtr            - Addr of static pointer to be registered
 *
 * DESCRIPTION: If compiled with bu_plumr.h, add the pointer whose address
 *              is passed to the registry.  MarkStaticBlocks() will then
 *              "mark" each block pointed to by a registered pointer.
 *
 ***************************************************************************/

void
RegisterStaticBlockPtr (void **BlkPtr)
{


    if (NumStaticBlocks < MAX_STATIC_BLOCKS)
    {
        StaticBlockList[NumStaticBlocks++] = (void **) BlkPtr;
    }

    else
    {
        REPORT_WARNING (&KDT[1]);
    }
}


/****************************************************************************
 *
 * FUNCTION:    MarkStaticBlocks
 *
 * PARAMETERS:  *Count          - Count of blocks marked
 *
 * DESCRIPTION: "Mark" all blocks pointed to by registered static pointers
 *
 ***************************************************************************/

void
MarkStaticBlocks (INT32 *Count)
{
    INT32           i;


    for (i = 0; i < NumStaticBlocks; i++)
    {
        if (Count)
        {
            ++*Count;
        }

        MarkBlock (*StaticBlockList[i]);
    }
}

#endif /* PLUMBER */

#ifdef PLUMBER


/****************************************************************************
 *
 * FUNCTION:    NsMarkNT
 *
 * PARAMETERS:  *ThisEntry          - table to be marked
 *              Size                - size of table
 *              *Count              - output count of blocks marked
 *                                    Outermost caller should preset to 0
 *
 * DESCRIPTION: "Mark" a name table and its reachable values,
 *              including descendents.
 *
 ***************************************************************************/

static void
NsMarkNT (nte *ThisEntry, INT32 Size, INT32 *Count)
{
    nte                 *Appendage;


    FUNCTION_TRACE ("NsMarkNT");


    if (!ThisEntry)
    {
        return;
    }

    if (Count)
    {
        ++*Count;
    }

    MarkBlock ((void *) &NEXTSEG (ThisEntry));


    /* Locate appendage, if any, before losing original scope pointer */
    
    Appendage = NEXTSEG (ThisEntry);

    /* for all entries in this NT */
    
    while (Size--)
    {
        if (ThisEntry->NameSeg)
        {
            /* non-empty entry -- mark anything it points to */

            switch (NsGetType (ThisEntry))
            {
                OBJECT_DESCRIPTOR       *ptrVal;
                meth                    *Method;


            case String:
                ptrVal = (OBJECT_DESCRIPTOR *) NsGetValue (ThisEntry);
                
                /* 
                 * Check for the value pointer in the name table entry
                 * pointing to a string definition in the AML stream,
                 * in which case no allocated storage is involved.
                 */

                if (ptrVal && StringOp != *(UINT8 *) ptrVal)
                {
                    /* Avoid marking value if it is in the AML stream */
                    
                    if (!IsInPCodeBlock (ptrVal->String.String))
                    {
                        MarkBlock (ptrVal->String.String);
                    }
                    MarkBlock (ptrVal);
                }
                break;

            case Buffer:
                ptrVal = (OBJECT_DESCRIPTOR *) NsGetValue (ThisEntry);
                
                /* 
                 * Check for the value pointer in the name table entry
                 * pointing to a buffer definition in the AML stream,
                 * in which case no allocated storage is involved.
                 */
                
                if (ptrVal && BufferOp != *(UINT8 *) ptrVal)
                { 
                    MarkBlock (ptrVal->sBuffer.pbBuffer);
                    MarkBlock (ptrVal);
                }
                break;

            case Package:
                ptrVal = (OBJECT_DESCRIPTOR *) NsGetValue (ThisEntry);
                
                /* 
                 * Check for the value pointer in the name table entry
                 * pointing to a package definition in the AML stream,
                 * in which case no allocated storage is involved.
                 */

                if (ptrVal && PackageOp != *(UINT8 *) ptrVal)
                {
                    AmlMarkPackage (ptrVal);
                }
                break;

            case Method:
                Method = (meth *) NsGetValue (ThisEntry);
                if (Method)
                {
                    MarkBlock(Method);
                }

            case BankField:
            case DefField:
            case FieldUnit:
            case IndexField:
            case Region:
                ptrVal = (OBJECT_DESCRIPTOR *) NsGetValue (ThisEntry);
                if (ptrVal)
                {
                    AmlMarkObject (ptrVal);
                }

            default:
                
                /* No other types should own storage beyond the nte itself */
                
                break;

            }   /* switch */


            if (ThisEntry->ChildScope)
            {
                NsMarkNT (ThisEntry->ChildScope, TABLSIZE, Count);
            }
        }

        if (0 == Size && Appendage)
        {
            /* Just examined last entry, but table has an appendage.  */
            
            ThisEntry = Appendage;
            Size += TABLSIZE;

            if (Count)
            {
                ++*Count;
            }

            MarkBlock ((void *) &NEXTSEG (ThisEntry));
            Appendage = NEXTSEG (ThisEntry);
        }
        
        else
        {
            ThisEntry++;
        }
    
    } /* while */
}


/****************************************************************************
 *
 * FUNCTION:    NsMarkNS()
 *
 * PARAMETERS:  none
 *
 * DESCRIPTION: If compiled with bu_plumr.h, traverse the name space
 *              "marking" all name tables and reachable values.
 *
 * RETURN:      The number of blocks marked
 *
 ***************************************************************************/

INT32
NsMarkNS (void)
{
    INT32           Count = 0;


    FUNCTION_TRACE ("NsMarkNS");


    if (!Root)
    {
        /* 
         * If the name space has not been initialized,
         * there is nothing to mark.
         */
        return 0;
    }

    NsMarkNT (Root, NsRootSize, &Count);
    MarkStaticBlocks (&Count);
    MarkMethodValues (&Count);
    MarkObjectStack (&Count);


    return Count;
}


#endif  /* PLUMBER */


