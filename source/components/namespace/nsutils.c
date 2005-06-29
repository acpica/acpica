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
 | ModuleName: nsutils - Utilities for accessing ACPI namespace
 |__________________________________________________________________________
*/

#define __NSUTILS_C__

#include <acpi.h>
#include <namespace.h>
#include <string.h>


#define _THIS_MODULE        "nsutils.c"
#define _COMPONENT          NAMESPACE



static ST_KEY_DESC_TABLE KDT[] = {
    {"0000", 'W', "NsValType: Null handle", "NsValType: Null handle"},
    {"0001", 'W', "NsValPtr: Null handle", "NsValPtr: Null handle"},
    {NULL, 'I', NULL, NULL}
};




/****************************************************************************
 *
 * FUNCTION:    AllocateNteDesc
 *
 * PARAMETERS:  INT32 Size       # of nte in table
 *
 * DESCRIPTION: Allocate an array of nte, including prepended link space
 *
 * RETURN:      The address of the first nte in the array, or NULL
 *
 ***************************************************************************/

nte *
AllocateNteDesc (INT32 Size)
{
    nte             *NewNteDesc = NULL;
    size_t          AllocSize;


    FUNCTION_TRACE ("AllocateNteDesc");


    AllocSize = (size_t) Size * sizeof (nte);

    
    /* Allow room for link to appendage */
    
#ifndef USE_HASHING
    AllocSize += sizeof (nte *);
#endif

  
    NewNteDesc = LocalCallocate (AllocSize);

#ifndef USE_HASHING
    if (NewNteDesc)
    {
        /* Move past the appendage pointer */
    
        NewNteDesc = (nte *) (((UINT8 *) NewNteDesc) + sizeof (nte *));
    }

    DEBUG_PRINT (TRACE_EXEC, ("AllocateNteDesc: NewNteDesc=%p\n", NewNteDesc));
#endif

    return NewNteDesc;
}



/****************************************************************************
 *
 * FUNCTION:    NsValType
 *
 * PARAMETERS:  NsHandle Handle          Handle of nte to be examined
 *
 * RETURN:      Type field from nte whose handle is passed
 *
 ***************************************************************************/

NsType
NsValType (NsHandle handle)
{
    FUNCTION_TRACE ("NsValType");


    if (!handle)
    {
        /*  Handle invalid  */

        REPORT_WARNING (&KDT[0]);
        return Any;
    }

    return ((nte *) handle)->NtType;
}


/****************************************************************************
 *
 * FUNCTION:    NsValPtr
 *
 * PARAMETERS:  NsHandle Handle              Handle of nte to be examined
 *
 * RETURN:      ptrVal field from nte whose handle is passed
 *
 ***************************************************************************/

void *
NsValPtr (NsHandle handle)
{
    FUNCTION_TRACE ("NsValPtr");


    if (!handle)
    {
        /* handle invalid */

        REPORT_WARNING (&KDT[1]);
        return NULL;
    }

    return ((nte *) handle)->ptrVal;
}


/*****************************************************************************
 *
 * FUNCTION:    IsNsValue
 *
 * PARAMETERS:  OBJECT_DESCRIPTOR *ObjDesc
 *
 * RETURN:      TRUE if the passed descriptor is the value of a Name in
 *              the name space, else FALSE
 *
 ****************************************************************************/

INT32
IsNsValue (OBJECT_DESCRIPTOR *ObjDesc)
{

    FUNCTION_TRACE ("IsNsValue");


    return ((NsHandle) 0 != NsFindpVal (ObjDesc, NS_ALL, INT_MAX));
}



/****************************************************************************
 *
 * FUNCTION:    InternalizeName
 *
 * PARAMETERS:  char *DottedName -        external representation of name
 *
 * RETURN:      Internal representation of name
 *
 * DESCRIPTION: Convert an external representation (e.g. "\_PR_.CPU0")
 *              to internal form (e.g. 5c 2f 02 5f 50 52 5f 43 50 55 30)
 *
 * ALLOCATION:
 * Reference   Size              Pool  Owner                Description
 * pcIN{sl}    INsiz{sl:HWM}     bu    InternalizeName      Internal name
 *
 ****************************************************************************/

char *
InternalizeName (char *DottedName)
{
    char            *Result = NULL;
    static char     *IN = NULL;
    static size_t   INsize = 0;
    size_t          i;


    FUNCTION_TRACE ("InternalizeName");


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

    DEBUG_PRINT (TRACE_EXEC,("InternalizeName: returning %p=>\"%s\"\n", IN, IN ? IN : ""));     
    
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
 * PARAMETERS:  void    **BlkPtr         Addr of static pointer to be registered
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
 * PARAMETERS:  INT32 *Count        Count of blocks marked
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
 * PARAMETERS:  nte     *ThisEntry  table to be marked
 *              INT32   Size        size of table
 *              INT32   *Count      output count of blocks marked
 *                                  Outermost caller should preset to 0
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

            switch (NsValType (ThisEntry))
            {
                OBJECT_DESCRIPTOR       *ptrVal;
                meth                    *Method;


            case String:
                ptrVal = (OBJECT_DESCRIPTOR *) NsValPtr (ThisEntry);
                
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
                ptrVal = (OBJECT_DESCRIPTOR *) NsValPtr (ThisEntry);
                
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
                ptrVal = (OBJECT_DESCRIPTOR *) NsValPtr (ThisEntry);
                
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
                Method = (meth *) NsValPtr (ThisEntry);
                if (Method)
                {
                    MarkBlock(Method);
                }

            case BankField:
            case DefField:
            case FieldUnit:
            case IndexField:
            case Region:
                ptrVal = (OBJECT_DESCRIPTOR *) NsValPtr (ThisEntry);
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


