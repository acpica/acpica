
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


#define _THIS_MODULE        "nsutils.c"
#define _COMPONENT          NAMESPACE



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
NsChecksum (
    void                    *Buffer, 
    UINT32                  Length)
{
    UINT8                   *limit;
    UINT8                   *rover;
    UINT8                   sum = 0;


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

NAME_TABLE_ENTRY *
NsAllocateNteDesc (
    INT32                   NteCount)
{
    NAME_TABLE_ENTRY        *NewNteDesc = NULL;
    size_t                  AllocSize;


    FUNCTION_TRACE ("AllocateNteDesc");


    AllocSize = (size_t) NteCount * sizeof (NAME_TABLE_ENTRY);

    
    /* Allow room for link to appendage */
    
    AllocSize += sizeof (NAME_TABLE_ENTRY *);

  
    NewNteDesc = LocalCallocate (AllocSize);
    if (NewNteDesc)
    {
        /* Move past the appendage pointer */
    
        NewNteDesc = (NAME_TABLE_ENTRY *) (((UINT8 *) NewNteDesc) + 
                        sizeof (NAME_TABLE_ENTRY *));
    }

    DEBUG_PRINT (TRACE_EXEC, ("AllocateNteDesc: NewNteDesc=%p\n", NewNteDesc));

    FUNCTION_EXIT;
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

ACPI_OBJECT_TYPE
NsGetType (
    ACPI_HANDLE             handle)
{
    FUNCTION_TRACE ("NsGetType");


    if (!handle)
    {
        /*  Handle invalid  */

        REPORT_WARNING ("NsGetType: Null handle");
        FUNCTION_EXIT;
        return TYPE_Any;
    }

    FUNCTION_EXIT;
    return ((NAME_TABLE_ENTRY *) handle)->Type;
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
NsGetValue (
    ACPI_HANDLE             handle)
{
    FUNCTION_TRACE ("NsGetValue");


    if (!handle)
    {
        /* handle invalid */

        REPORT_WARNING ("NsGetValue: Null handle");
        FUNCTION_EXIT;
        return NULL;
    }

    FUNCTION_EXIT;
    return ((NAME_TABLE_ENTRY *) handle)->Value;
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
IsNsValue (
    ACPI_OBJECT             *ObjDesc)
{
    ACPI_HANDLE             RetHandle;


    FUNCTION_TRACE ("IsNsValue");

    RetHandle = NsFindValue (ObjDesc, NS_ALL, INT_MAX);

    FUNCTION_EXIT;
    return (RetHandle != (ACPI_HANDLE) 0);
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
NsLocal (
    ACPI_OBJECT_TYPE        Type)
{
    FUNCTION_TRACE ("NsLocal");


    if (OUTRANGE (Type, NsProperties))
    {
        /*  type code out of range  */

        REPORT_WARNING ("NsLocal: Type code out of range");
        FUNCTION_EXIT;
        return 0;
    }

    FUNCTION_EXIT;
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
NsInternalizeName (
    char                    *DottedName)
{
    char                    *Result = NULL;
    static char             *IN = NULL;
    static size_t           INsize = 0;
    size_t                  i;


    /* TBD: remove static variables above !! */

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
    
    FUNCTION_EXIT;
    return IN;
}


/****************************************************************************
 *
 * FUNCTION:    NsConvertHandleToEntry
 *
 * PARAMETERS:  Handle          - Handle to be converted to an NTE
 *
 * RETURN:      A Name table entry pointer
 *
 * DESCRIPTION: Convert a namespace handle to a real NTE
 *
 ****************************************************************************/

NAME_TABLE_ENTRY *
NsConvertHandleToEntry (
    ACPI_HANDLE             Handle)
{

    /* 
     * Simple implementation for now;
     * TBD: Real integer handles allow for more verification 
     * and keep all pointers within this subsystem!
     */

    if (!Handle)
    {
        return NULL;
    }

    return (NAME_TABLE_ENTRY *) Handle;
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
RegisterStaticBlockPtr (
    void                    **BlkPtr)
{


    if (NumStaticBlocks < MAX_STATIC_BLOCKS)
    {
        StaticBlockList[NumStaticBlocks++] = (void **) BlkPtr;
    }

    else
    {
        REPORT_WARNING ("Too many static blocks");
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
MarkStaticBlocks (
    INT32                   *Count)
{
    INT32                   i;


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
NsMarkNT (
    nte                 *ThisEntry, 
    INT32               Size, 
    INT32               *Count)
{
    nte                 *Appendage;


    FUNCTION_TRACE ("NsMarkNT");


    if (!ThisEntry)
    {
        FUNCTION_EXIT;
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
                ACPI_OBJECT             *ptrVal;
                meth                    *Method;


            case String:
                ptrVal = (ACPI_OBJECT *) NsGetValue (ThisEntry);
                
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
                ptrVal = (ACPI_OBJECT *) NsGetValue (ThisEntry);
                
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
                ptrVal = (ACPI_OBJECT *) NsGetValue (ThisEntry);
                
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
                ptrVal = (ACPI_OBJECT *) NsGetValue (ThisEntry);
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

    FUNCTION_EXIT;
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
        FUNCTION_EXIT;
        return 0;
    }

    NsMarkNT (Root, NsRootSize, &Count);
    MarkStaticBlocks (&Count);
    MarkMethodValues (&Count);
    MarkObjectStack (&Count);


    FUNCTION_EXIT;
    return Count;
}


#endif  /* PLUMBER */


