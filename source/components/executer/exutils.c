/*__________________________________________________________________________
 |
 |           Copyright (C) Intel Corporation 1994-1998
 |
 | All rights reserved.  No part of this program or publication may be
 | reproduced, transmitted, transcribed, stored in a retrieval system, or
 | translated into any language or computer language, in any form or by any
 | means, electronic, mechanical, magnetic, optical, chemical, manual, or
 | otherwise, without the prior written permission of Intel Corporation.
 |__________________________________________________________________________
 |
 | ModuleName: isutils - interpreter/scanner utilities
 |__________________________________________________________________________
*/


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
 *  FUNCTION:       SetWhy
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
 *          
 ****************************************************************************/


void SetWhy (char *Function, char *Case, char *Description)
{

    if (Function)
    {
        sprintf (WhyBuf, "%s: ", Function);
    }

    if (Case)
    {
        strcat (WhyBuf, Case);
        strcat (WhyBuf, ": ");
    }

    if (Description)
    {
        strcat (WhyBuf, Description);
    }
    
    if (WhyFail)
    {   /*  WhyFail specifies failure, append it to WhyBuf  */

        strcat (WhyBuf, " [");
        strcat (WhyBuf, WhyFail);
        strcat (WhyBuf, "]");
        WhyFail = NULL;
    }

    Why = WhyBuf;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlAppendBlockOwner
 *
 * PARAMETERS:  void *Owner
 *
 * DESCRIPTION: Append block-owner data from bu_plumr to WhyBuf.
 *
 ****************************************************************************/

void
AmlAppendBlockOwner (void *Owner)
{

#ifdef PLUMBER
    if (Why != WhyBuf)
    {
        /* Copy message to WhyBuf */
        
        strcpy (WhyBuf, Why);
        Why = WhyBuf;
    }

#if 1
    vPlumber ("internal type mismatch", 3);
#endif

    sprintf (&WhyBuf[strlen (WhyBuf)], " %s", pcIdentifyOwner(Owner));

#endif  /* PLUMBER */
}



/*****************************************************************************
 * 
 * FUNCTION:    AmlAppendOperandDiag
 *
 * PARAMETERS:  char *  FileName    Name of source file
 *              INT32   LineNum     Line Number in file
 *              UINT16  OpCode      OpCode being executed
 *              INT32   NumOperands Number of operands PrepStack tried to check
 *
 * DESCRIPTION: Append diagnostic information about operands to WhyBuf
 *              This function is intended to be called after PrepStack
 *              has returned S_ERROR.
 *
 ****************************************************************************/

void
AmlAppendOperandDiag(char *FileName, INT32 LineNum, UINT16 OpCode, INT32 NumOperands)
{
    meth            Method;


    if (Why != WhyBuf)
    {
        /* Copy message to WhyBuf */
        
        strcpy (WhyBuf, Why);
        Why = WhyBuf;
    }

    GetCurrentLoc (&Method);

    sprintf (&WhyBuf[strlen (WhyBuf)], " [%s:%d, opcode = %s AML offset %04x]",
            FileName, LineNum,
            (OpCode > UCHAR_MAX)
                ? LongOps[OpCode & 0x00ff]
                : ShortOps[OpCode],
            Method.Offset);

    if (GetDebugLevel () > 0)
    {
/* !!!!!!!!!Clean this stuff up !!! */

/*        INT32       iTraceWas = Trace; */

        /* Turn on TraceExec to enable output from DumpStack() */
        
/*        Trace |= TraceExec; OBSOLETE !! */

        DUMP_STACK (Exec,
                      (OpCode > UCHAR_MAX)
                      ? LongOps[OpCode & 0x00ff]
                      : ShortOps[OpCode],
                      NumOperands,
                      "after PrepStack failed");

/*        Trace = iTraceWas;  */
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
 ****************************************************************************/

UINT32 
AmlBufSeq (void)
{
    static UINT32        BufSeq = (UINT32) 0;   /* Counts allocated Buffer descriptors */
    
    
    return ++BufSeq;
}


/*****************************************************************************
 * 
 * FUNCTION:    DeleteObject
 *
 * PARAMETERS:  OBJECT_DESCRIPTOR **ObjDesc    Descriptor to be deleted
 *
 * DESCRIPTION: If the passed descriptor pointer does not point into the
 *              AML block and is not an NsHandle, free the descriptor.
 *
 *              Note that the parameter is the address of the descriptor
 *              pointer, so that the descriptor pointer can be set to NULL
 *              after the descriptor is freed.
 *
 ****************************************************************************/

VOID
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
        !IsInPCodeBlock ((UINT8 *)    *ObjDesc) &&
        !IsNsHandle                  (*ObjDesc) &&
        !IsMethodValue               (*ObjDesc) &&
        !IsNsValue                   (*ObjDesc))
    {

        DEBUG_PRINT (ACPI_INFO, ("DeleteObject: Actually deleting %x\n", *ObjDesc));

        OsdFree (*ObjDesc);

        DEBUG_PRINT (ACPI_INFO, ("DeleteObject: Successfully deleted %x\n", *ObjDesc));

    }

}


#ifdef PLUMBER
/****************************************************************************
 * 
 * FUNCTION:    AmlMarkPackage
 *
 * PARAMETERS:  OBJECT_DESCRIPTOR *ObjDesc   Descriptor of package to be marked
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
}


/****************************************************************************
 *
 * FUNCTION:    AmlMarkObject
 *
 * PARAMETERS:  OBJECT_DESCRIPTOR *ObjDesc   Descriptor of object to be marked
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
}


/*****************************************************************************
 *
 * FUNCTION:    MarkObjectStack
 *
 * PARAMETERS:  INT32 *Count    Count of objects marked
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
            !IsNsHandle (ObjStack[Index]))
        {   
            /*  Mark value's storage    */
            
            if (Count)
            {
                ++*Count;
            }

            AmlMarkObject (ObjStack[Index]);
        }
    }
} 

#endif   /* PLUMBER */

/******************************************************************************
 * 
 * FUNCTION:    DigitsNeeded
 *
 * PARAMETERS:  INT32   val         value to be represented
 *              INT32   base        base of representation
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

    return NumDigits;
}


/******************************************************************************
 * 
 * FUNCTION:    LineSet
 *
 * PARAMETERS:  INT32   NumBytes        number of bytes needing to be printed
 *                                      0 => force a new line next time n != 0
 *              OpMode  LoadExecMode    Load or Exec (used in PRINT_L_D expansion)
 *
 * DESCRIPTION: Ensure that there is enough room on the current output line
 *              to print at least n characters; start a new line if needed.
 *              This function is also responsible for printing the offset
 *              within the AML block at the start of each line, and for
 *              indenting the AML according to its block structure while
 *              keeping the offset column vertical.
 *
 *****************************************************************************/

/* Used for keeping track of disassembly listing */

#define         AML_MAX_INDENT 80

static INT32    LinePos = 0;
static INT32    RightMargin = 74;
static INT32    LeftMargin = 0;
static char     LeftMarginChars[AML_MAX_INDENT + 1] = "\0";


VOID
LineSet (INT32 NumBytes, OpMode LoadExecMode)
{ 
    /* Offset in AML block of 1st byte in this line */
    
    static ptrdiff_t    LineOffset;
    static INT32        NewLineRequested = 1;
    static INT32        FirstLineNotDoneYet = 1;


    FUNCTION_TRACE ("LineSet");


    if ((Load1 == LoadExecMode) && (GetDebugLevel() < 1))
    {
        return;
    }

    if (0 == NumBytes)
    {
        NewLineRequested = 1;
        LineOffset = (INT32) (PCode - PCodeBase);
    }

    else if (NewLineRequested || LinePos + NumBytes > RightMargin)
    {
        /* Need a new line */

        if (FirstLineNotDoneYet || LinePos > LeftMargin)
        {
            if (NewLineRequested)
            {

                /* See DESCRIPTION of Indent() re LeftMarginChars[] */

                if (FirstLineNotDoneYet)
                {
                    DEBUG_PRINT (TRACE_LOAD,
                                ("%04x %s\n", LineOffset, LeftMarginChars));
                    FirstLineNotDoneYet = 0;
                }

                else
                {
                    DEBUG_PRINT (TRACE_LOAD,
                                ("%04x %s\n", LineOffset, LeftMarginChars));
                }
            }

            else
            {
                DEBUG_PRINT (TRACE_LOAD,
                            ("     %s\n", LeftMarginChars));
            }

            LinePos = LeftMargin;
        }

        NewLineRequested = 0;
    }

    LinePos += NumBytes;
}


/******************************************************************************
 * 
 * FUNCTION:    Indent
 *
 * PARAMETERS:  INT32   NumChars    Number of character positions to move the indent
 *
 * DESCRIPTION: Maintains LeftMargin position, and corresponding
 *              LeftMarginChars string (of spaces) which is printed
 *              following each line's offset field
 *
 *****************************************************************************/

VOID
Indent (INT32 NumChars)
{
    FUNCTION_TRACE ("Indent");


    if (NumChars < 0)
    {
        /* DEBUG_PRINT (ACPI_INFO, ("out(%d) \n", -n)); */

        LeftMargin += NumChars;                    /* Reduces LeftMargin, since n < 0 */
        if (LeftMargin < 0)
        {
            LeftMargin = 0;
        }
    }
    else
    {
        /* DEBUG_PRINT (ACPI_INFO, ("in(%d) \n", n)); */

        while (NumChars)
        {
            if (LeftMargin < AML_MAX_INDENT)
            {
                LeftMarginChars[LeftMargin] = ' ';
            }

            LeftMargin++;
            NumChars--;
        }
    }

    if (LeftMargin < AML_MAX_INDENT + 1)
    {
        LeftMarginChars[LeftMargin] = '\0';
    }

    LINE_SET (0, Load);
}

