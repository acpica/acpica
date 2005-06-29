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
 | ModuleName: isnames - interpreter/scanner name load/execute
 |__________________________________________________________________________
*/


#define __ISNAMES_C__

#include <acpi.h>
#include <interpreter.h>
#include <amlcode.h>
#include <namespace.h>
#include <string.h>

#define _THIS_MODULE        "isnames.c"
#define _COMPONENT          INTERPRETER


static ST_KEY_DESC_TABLE KDT[] = {
   {"0000", '1', "LastFQN: Allocation failure requesting", "LastFQN: Allocation failure requesting"},
   {"0001", '1', "AllocateNameString: name allocation failure", "AllocateNameString: name allocation failure"},
   {"0002", '1', "NamedObject/NameSpaceModifier Failure with at least one more byte available in package", "NamedObject/NameSpaceModifier Failure with at least one more byte available in package"},
   {"0003", '1', "During LOAD this segment started with one or more valid characters, but fewer than 4", "During LOAD this segment started with one or more valid characters, but fewer than 4"},
   {"0004", '1', "*UNEXPECTED END* [Name]", "*UNEXPECTED END* [Name]"},
   {"0005", '1', "Ran out of segments after processing a prefix", "Ran out of segments after processing a prefix (See Log for details)"},
   {NULL, 'I', NULL, NULL}
};


/* |-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
 *
 * Functions that Load/Dump/Execute Names
 *
 * |-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
 */

/*****************************************************************************
 *
 * FUNCTION:    LastFullyQualifiedName
 *
 * PARAMETERS:  none
 *
 * RETURN:      A pointer to storage containing the last name encountered,
 *              in fully qualified form.  Used to create labels when
 *              generating an assembly output file.
 *
 * ALLOCATION:
 * Reference   Size                 Pool  Owner                  Description
 * FQN_ptr{sl} FQN_Length{sl:HWM}   bu    LastFullyQualifiedName Last Name seen
 *
 ****************************************************************************/

char *
LastFullyQualifiedName (void)
{
    char                *CurrentScope;
    char                *TempPtr;
    size_t              MaxLength;
    size_t              Length;
    static  char        *FQN_ptr = NULL;
    static  size_t      FQN_Length = 0;


    FUNCTION_TRACE ("LastFullyQualifiedName");


    /* If NameString is fully qualified, just return a pointer to it. */

    if (RootPrefix == NameString[0])
    {
        return NameString;
    }

    /* Get the current scope */

    CurrentScope = NsNameOfCurrentScope();

    if (CurrentScope)
    {

        /* Max length of FQN = length of scope + length of name + trailing null */

        MaxLength = strlen (CurrentScope) + strlen (NameString) + 1;


        /* 
         * TBD: FIX WEIRD CODE:  both FQN_Length and FQN_ptr are locals 
         * initialized to zero (null)
         */
        if (FQN_Length < MaxLength)
        {
            if (FQN_ptr)
            {
                OsdFree (FQN_ptr);
            }
            else
            {
                RegisterStaticBlockPtr (&FQN_ptr);
            }

            FQN_ptr = LocalCallocate (MaxLength);
            if (!FQN_ptr)
            {
                /* allocation failed */

                REPORT_ERROR (&KDT[0]);
            }
        
            FQN_Length = MaxLength;
        }

        if (FQN_ptr)
        {
            /* Copy scope into FQN_ptr string; set Length to its length */

            strcpy (FQN_ptr, CurrentScope);
            Length = strlen (FQN_ptr);

            /* 
             * For each ParentPrefix at the front of NameString,
             * remove one segment (4 bytes) from the end of the scope.
             */
            for (TempPtr = NameString ; ParentPrefix == *TempPtr ; ++TempPtr )
            {
                Length -= 4;
                if (Length < 0)
                {
                    Length = 0;
                }

                FQN_ptr[Length] = '\0';
            }

            /* 
             * Append NameString (with ParentPrefixes removed)
             * to what is left of the scope.
             */
            strcat (FQN_ptr, TempPtr);
        }
    }

    return FQN_ptr;

}


/*****************************************************************************
 *
 * FUNCTION:    AllocateNameString
 *
 * PARAMETERS:  INT32 PrefixCount   -1  => root
 *                                  0   => none
 *                                  else count of parent levels
 *              INT32 NumNameSegs   count of 4-character name segments
 *
 * DESCRIPTION: Ensure allocated name string is long enough,
 *              and set up prefix if any.
 *
 * ALLOCATION:
 * Reference    Size                 Pool  Owner       Description
 * NameString   NameStringSize{HWM}  bu    amlscan     Last AML Name seen
 *
 ****************************************************************************/

void 
AllocateNameString (INT32 PrefixCount, INT32 NumNameSegs)
{
    char            *TempPtr;
    INT32           SizeNeeded;


    FUNCTION_TRACE ("AllocateNameString");

    /* 
     * Room for all \ and ^ prefixes, all segments, and a MultiNamePrefix.
     * This may actually be somewhat longer than needed.
     */

    /* !!!Commented out for now, until we link INT32 a library with ABS
     * Fix below may or may not be sufficient !!!

    SizeNeeded = abs(PrefixCount) + 4 * NumNameSegs + 2;
    */

    if (PrefixCount < 0)
    {
        SizeNeeded = 1 /* root */ +  4 * NumNameSegs + 2;
    }
    else
    {
        SizeNeeded = PrefixCount + 4 * NumNameSegs + 2;
    }

#if 0
    if (2 == PrefixCount)
    {
        Trace |= TraceNames;
    }
    else
    {
        Trace &= ~TraceNames;
    }
#endif

    if (SizeNeeded < INITIAL_NAME_BUF_SIZE)
    {
        SizeNeeded = INITIAL_NAME_BUF_SIZE;
    }

    /* If need > current size, free and allocate a new one. */
    
    if (SizeNeeded > NameStringSize)
    {
        if (NameString)
        {
            OsdFree (NameString);
        }
        else
        {
            RegisterStaticBlockPtr (&NameString);
        }

        NameString = OsdAllocate ((size_t) SizeNeeded);

        if (NameString)
        {
            NameStringSize = SizeNeeded;
        }
        else
        {
            /*  allocation failure  */

            REPORT_ERROR (&KDT[1]);
            OutOfMemory = TRUE;
            NameStringSize = 0;
            return;
        }
    }

    TempPtr = NameString;

    /* Set up Root or Parent prefixes if needed */

    if (PrefixCount < 0)
    {
        *TempPtr++ = RootPrefix;
    }
    else
    {
        while (PrefixCount--)
        {
            *TempPtr++ = ParentPrefix;
        }
    }

    /* Set up Dual or Multi prefixes if needed */
    
    if (NumNameSegs > 2)
    {
        /*  set up multi prefixes   */

        *TempPtr++ = MultiNamePrefixOp;
        *TempPtr++ = (char) NumNameSegs;
    }

    else if (2 == NumNameSegs)
    {
        /* Set up dual prefixes */

        *TempPtr++ = DualNamePrefix;
    }

    /*  Terminate string following prefixes. DoSeg() will append the segment(s) */

    *TempPtr = 0;

    if (LstFileHandle != NO_LOG_HANDLE)
    {
        DEBUG_PRINT (TRACE_NAMES, ("AllocateNameString: "));
        
        for (TempPtr = NameString; *TempPtr; ++TempPtr)
        {
            DEBUG_PRINT_RAW (TRACE_NAMES, ("%02x ", *TempPtr));
        }

        DEBUG_PRINT_RAW (TRACE_NAMES, (" %s\n", NameString));
    }
}


/*****************************************************************************
 *
 * FUNCTION:    NcOK
 *
 * PARAMETERS:  INT32   Character       the character to be examined
 *
 * RETURN:      1 if Character may appear in a name, else 0
 *
 ****************************************************************************/

INT32 
NcOK (INT32 Character)
{

    return ((Character == '_') || (Character >= 'A' && Character <= 'Z') ||
                (Character >= '0' && Character <= '9'));
}


/*****************************************************************************
 * 
 * FUNCTION:    GetEncodedPkgLen
 *
 * PARAMETERS:  long    LastPkgLen  latest value decoded by DoPkgLength() for
 *                                  most recently examined package or field
 *
 * RETURN:      int NumBytes        Number of bytes contained in package length encoding
 *
 * DESCRIPTION: Decodes the Package Length. Upper 2 bits are are used to
 *              tell if type 1, 2, 3, or 4.
 *                  0x3F = Max 1 byte encoding,
 *                  0xFFF = Max 2 byte encoding,
 *                  0xFFFFF = Max 3 Byte encoding,
 *                  0xFFFFFFFFF = Max 4 Byte encoding.
 *
 ****************************************************************************/


#define Type1   64              /*  or 0x40 Max encoding size = 0x3F    */
#define Type2   16384           /*  or 0x4000 Max encoding size = 0xFFF */
#define Type3   4194304         /*  or 0x400000 Max encoding size = 0xFFFFF */
#define Type4   1073741824      /*  or 0x40000000 Max encoding size = 0xFFFFFFF */


INT32 
GetEncodedPkgLen (INT32 LastPkgLen)
{
    INT32           NumBytes = 0;

    FUNCTION_TRACE ("GetEncodedPkgLen");


    if (LastPkgLen < Type1)
        NumBytes = 1;
    
    else if (LastPkgLen < Type2)
        NumBytes = 2;
    
    else if (LastPkgLen < Type3)
        NumBytes = 3;
    
    else if (LastPkgLen < Type4)
        NumBytes = 4;

    return NumBytes;
}


/*****************************************************************************
 *
 * FUNCTION:    DoSeg
 *
 * PARAMETERS:  OpMode      LoadExecMode      Load or Exec
 *
 * RETURN:      S_SUCCESS, S_FAILURE, or S_ERROR
 *
 * DESCRIPTION: Print/exec a name segment (4 bytes)
 *
 ****************************************************************************/

static INT32 
DoSeg (OpMode LoadExecMode)
{
    INT32           Index;
    INT32           Excep = S_SUCCESS;
    char            CharBuf[5];


    FUNCTION_TRACE ("DoSeg");


    LINE_SET (4, LoadExecMode);

    /*  If first character is a digit, we aren't looking at a valid name segment    */

    CharBuf[0] = Peek ();

    if ('0' <= CharBuf[0] && CharBuf[0] <= '9')
    {
        sprintf (WhyBuf, "DoSeg: leading digit: %c\n", CharBuf[0]);
        WhyFail = WhyBuf;
        Excep = S_FAILURE;
    }

    else 
    {
        DEBUG_PRINT (TRACE_LOAD, ("DoSeg: \n"));

        for (Index = 4; Index > 0 && NcOK (Peek ()); --Index)
        {
            ConsumeAMLStreamBytes (1, (UINT8 *) &CharBuf[4 - Index]);
            DEBUG_PRINT (TRACE_LOAD, ("%c\n", CharBuf[4 - Index]));
        }
    }


    if (S_SUCCESS == Excep)
    {
        /*  valid name segment  */

        if (0 == Index)
        {
            /* Found 4 valid characters */
        
            CharBuf[4] = '\0';

            if (NameStringSize)
            {
                strcat (NameString, CharBuf);
            }

            if (fAsmFile && Load1 != LoadExecMode)
            {
                OsdPrintf (fAsmFile, " \"%s\",", CharBuf);
            }

            DEBUG_PRINT (TRACE_NAMES, ("DoSeg: %s \n", CharBuf));
        }

        else if (4 == Index)
        {
            /* 
             * First character was not a valid name character,
             * so we are looking at something other than a name.
             */
            sprintf (WhyBuf, "Leading char not alpha: %02Xh", CharBuf[0]);
            WhyFail = WhyBuf;
            Excep = S_FAILURE;
        }

        else
        {
            /* Segment started with one or more valid characters, but fewer than 4 */
        
            Excep = S_ERROR;
            LINE_SET (22, LoadExecMode);
            DEBUG_PRINT (TRACE_LOAD, (" *Bad char %02x in name*\n", Peek ()));

            if (Load == LoadExecMode)
            {
                /*  second pass load mode   */

                LINE_SET (strlen (KDT[3].Description), LoadExecMode);
                REPORT_ERROR (&KDT[3]);
                LINE_SET (0, LoadExecMode);
            }

            else
            {
                sprintf (WhyBuf, "DoSeg: Bad char %02x in name", Peek ());
                Why = WhyBuf;
            }
        }
    
    }

    DEBUG_PRINT (TRACE_EXEC, ("Leave DoSeg %s \n", RV[Excep]));

    return Excep;
}


/*****************************************************************************
 *
 * FUNCTION:    DoName
 *
 * PARAMETERS:  NsType  DataType        Data type to be associated with this name
 *              OpMode  LoadExecMode    Load or Exec
 *
 * RETURN:      S_SUCCESS, S_FAILURE, or S_ERROR
 *
 * DESCRIPTION: Print a name, including any prefixes, enter it in the
 *              name space, and put its handle on the stack.
 *
 * ALLOCATION:
 * Reference   Size                 Pool  Owner       Description
 * ObjStack    s(OBJECT_DESCRIPTOR) bu    amlexec     Name(Lvalue)
 *
 ****************************************************************************/

INT32 
DoName (NsType DataType, OpMode LoadExecMode)
{
    INT32           NumSegments;
    INT32           PrefixCount = 0;
    INT32           Excep = S_SUCCESS;
    UINT8           Prefix = 0;


    FUNCTION_TRACE ("DoName");


BREAKPOINT3;

    CheckTrash ("enter DoName");
    LINE_SET (1, LoadExecMode);
/*     DEBUG_PRINT (TRACE_LOAD, (" ")); REMOVE !! */

    if (DefField == DataType || 
        BankField == DataType || 
        IndexField == DataType)
    {   
        /*  Disallow prefixes for types associated with field names */

        AllocateNameString (0, 1);
        Excep = DoSeg (LoadExecMode);
    }

    else
    {   
        /*  DataType is not a field name   */

        switch (PeekOp ())
        {   
            /*  examine first character of name for root or parent prefix operators */

        case RootPrefix:
            LINE_SET (1, LoadExecMode);
            ConsumeAMLStreamBytes (1, &Prefix);
            DEBUG_PRINT (TRACE_LOAD, ("RootPrefix: %x\n", Prefix));

            /* 
             * Remember that we have a RootPrefix --
             * see comment in AllocateNameString()
             */
            PrefixCount = -1;
            if (fAsmFile && Load1 != LoadExecMode)
            {
                OsdPrintf (fAsmFile, " \"%c\",", RootPrefix);
            }

            break;

        case ParentPrefix:
            do
            {
                LINE_SET (1, LoadExecMode);
                ConsumeAMLStreamBytes (1, &Prefix);
                DEBUG_PRINT (TRACE_LOAD, ("ParentPrefix: %x\n", Prefix));

                ++PrefixCount;
                if (fAsmFile && Load1 != LoadExecMode)
                {
                    OsdPrintf (fAsmFile, " \"%c\",", ParentPrefix);
                }

            } while (PeekOp () == ParentPrefix);
            
            break;

        default:
            break;
        }

        switch (PeekOp ())
        {
            /* examine first character of name for name segment prefix operator */
            
        case DualNamePrefix:
            LINE_SET (1, LoadExecMode);
            ConsumeAMLStreamBytes (1, &Prefix);
            DEBUG_PRINT (TRACE_LOAD, ("DualNamePrefix: %x\n", Prefix));

            if (fAsmFile && Load1 != LoadExecMode)
            {
                OsdPrintf (fAsmFile, " \"%c\",", DualNamePrefix);
            }

            AllocateNameString (PrefixCount, 2);

            /* Ensure PrefixCount != 0 to remember processing a prefix */
            
            PrefixCount += 2;

            if ((Excep = DoSeg (LoadExecMode)) == S_SUCCESS)
            {
                Excep = DoSeg (LoadExecMode);
            }

            break;

        case MultiNamePrefixOp:
            LINE_SET (1, LoadExecMode);
            ConsumeAMLStreamBytes (1, &Prefix);
            DEBUG_PRINT (TRACE_LOAD, ("MultiNamePrefix: %x\n", Prefix));

            if (fAsmFile && Load1 != LoadExecMode)
            {
                OsdPrintf (fAsmFile, " \"%c\",", MultiNamePrefixOp);
            }

            NumSegments = Peek ();                      /* fetch count of segments */

            if (DoByteConst (Load, 0) != S_SUCCESS)
            {
                /* unexpected end of AML */

                LINE_SET (23, LoadExecMode);
                REPORT_ERROR (&KDT[4]);
                
                LINE_SET (0, LoadExecMode);
                Excep = S_ERROR;
                break;
            }

            AllocateNameString (PrefixCount, NumSegments);

            /* Ensure PrefixCount != 0 to remember processing a prefix */
            
            PrefixCount += 2;

            while (NumSegments && (Excep = DoSeg (LoadExecMode)) == S_SUCCESS)
            {
                --NumSegments;
            }

            break;

        case 0: 
            
            /*  NullName valid as of 8-12-98 ASL/AML Grammar Update */
            
            if (-1 == PrefixCount)  
            {
                /*  RootPrefix followed by NULL */
            
                DEBUG_PRINT (TRACE_EXEC,
                                ("DoName: NameSeg is \"\\\" followed by NULL\n"));
            }

            ConsumeAMLStreamBytes (1, NULL);    /*  consume NULL byte   */
            
            if (fAsmFile && (Load1 != LoadExecMode))
            {
                /* This is probably not the right thing to do!! */

                OsdWrite (" \"00\",", 1, 4, fAsmFile);
            }

            AllocateNameString (PrefixCount, 0);
            break;

        default:

            /*  name segment string */

            AllocateNameString (PrefixCount, 1);
            Excep = DoSeg (LoadExecMode);
            break;

        }   /*  switch (PeekOp ())    */
    }

    if (S_SUCCESS == Excep)
    {
        NsHandle        handle;

        /* All prefixes have been handled, and the name is in NameString */

        DeleteObject ((OBJECT_DESCRIPTOR **) &ObjStack[ObjStackTop]);
        ObjStack[ObjStackTop] = NsEnter (NameString, DataType, LoadExecMode);

        /* Help view ObjStack during debugging */

        handle = ObjStack[ObjStackTop];

        /* Globally set this handle for use later */

        if (Load1 == LoadExecMode)
        {
            LastMethod = handle;
        }

        if (Exec == LoadExecMode && !ObjStack[ObjStackTop])
        {
            Why = "DoName: Name Lookup Failure";
            Excep = S_ERROR;
        }

        else if (Load1 != LoadExecMode)
        {   
            /*  not first pass load */

            if (Any == DataType && Method == NsValType (ObjStack[ObjStackTop]))
            {   
                /* 
                 * Method reference call 
                 * The name just looked up is a Method that was already
                 * defined, so this is a reference (call).  Scan the args.
                 * The arg count is in the MethodFlags, which is the first
                 * byte of the Method's AML.
                 */
                meth        *MethodPtr = (meth *) NsValPtr (ObjStack[ObjStackTop]);

                if (MethodPtr)
                {   
                    /*  MethodPtr valid   */
                    
                    INT32       MethodFlags;

                    MethodFlags = GetPCodeByte (MethodPtr->Offset);

                    if (AML_END_OF_BLOCK == MethodFlags)
                    {
                        sprintf (WhyBuf, "DoName: invoked Method %s has no AML",
                                    NameString);
                        Why = WhyBuf;
                        Excep = S_ERROR;
                    }

                    else
                    {   
                        /*  MethodPtr points at valid method  */
                        
                        INT32       ArgCount = (MethodFlags & METHOD_ARG_COUNT_MASK)
                                                >> METHOD_ARG_COUNT_SHIFT;
                        INT32       StackBeforeArgs = ObjStackTop;


                        if (((Excep = PushIfExec (Exec)) == S_SUCCESS) &&
                             (ArgCount > 0))
                        {   
                            /*  get arguments   */
                            
                            Indent (3); /*  increment log display indentation level */
                            
                            while (ArgCount-- && (S_SUCCESS == Excep))
                            {   
                                /*  get each argument   */
                                
                                if (S_SUCCESS == (Excep = DoOpCode (LoadExecMode)))    /*  get argument    */
                                {   
                                    /*  argument on object stack    */
                                    
                                    /*  
                                     * Arguments (e.g., local variables and control
                                     * method arguments) passed to control methods
                                     * are values, not references.
                                     * TBD:    RefOf problem with iGetRvalue() conversion.
                                     */
                                    if (Exec == LoadExecMode)
                                    {
                                        Excep = GetRvalue ((OBJECT_DESCRIPTOR **)
                                            &ObjStack[ObjStackTop]);
                                    }

                                    if (S_SUCCESS == Excep)
                                    {
                                        Excep = PushIfExec (LoadExecMode);    /*  inc iObjStackTop    */
                                    }
                                } 
                            }

                            Indent (-3);    /*  decrement log display indentation level */
                        } 

                        if ((S_SUCCESS == Excep) && (Exec == LoadExecMode))
                        {   
                            /* execution mode  */
                            /* Mark end of arg list */

                            DeleteObject ((OBJECT_DESCRIPTOR **) &ObjStack[ObjStackTop]);
                            ObjStack[ObjStackTop] = NULL;

                            /* Establish Method's scope as current */

                            NsPushMethodScope ((NsHandle) ObjStack[StackBeforeArgs]);

                            DEBUG_PRINT (TRACE_LOAD,
                                        ("Calling %4.4s, StackBeforeArgs %d  ObjStackTop %d\n",
                                        ObjStack[StackBeforeArgs], StackBeforeArgs,
                                        ObjStackTop));

                            /* Execute the Method, passing the stacked args */
                            
                            Excep = AmlExec (
                                        MethodPtr->Offset + 1, MethodPtr->Length - 1,
                                        (OBJECT_DESCRIPTOR **)&ObjStack[StackBeforeArgs + 1]);

                            DEBUG_PRINT (TRACE_LOAD,
                                    ("AmlExec Excep=%s, StackBeforeArgs %d  ObjStackTop %d\n",
                                    RV[Excep], StackBeforeArgs, ObjStackTop));

                            if (S_RETURN == Excep)
                            {
                                /* recover returned value */

                                if (StackBeforeArgs < ObjStackTop)
                                {
                                    DeleteObject ((OBJECT_DESCRIPTOR **) &ObjStack[StackBeforeArgs]);
                                    ObjStack[StackBeforeArgs] = ObjStack[ObjStackTop--];
                                }

                                Excep = S_SUCCESS;
                            }

                            /* Pop scope stack */
                            
                            NsPopCurrent (Any);

                        }   /*  execution mode  */

                        /* Clean up object stack */
                        
                        while (ObjStackTop > StackBeforeArgs)
                        {
                            DeleteObject ((OBJECT_DESCRIPTOR **) &ObjStack[ObjStackTop]);

                            /* Zero out the slot and move on */

                            ObjStack[ObjStackTop] = NULL;
                            ObjStackTop--;
                        }
                    }
                } 
            }
        } 
    }

    else if (S_FAILURE == Excep && PrefixCount != 0)
    {
        /* Ran out of segments after processing a prefix */

        if (Load1 == LoadExecMode || Load == LoadExecMode)
        {
            LINE_SET (16, LoadExecMode);
            DEBUG_PRINT (ACPI_INFO, ("*Malformed Name*"));

            if (WhyFail)
            {
                LINE_SET (3 + strlen (WhyFail), LoadExecMode);
                DEBUG_PRINT (ACPI_INFO, (" [%s]", WhyFail));
            }

            REPORT_ERROR (&KDT[5]);
            LINE_SET (0, LoadExecMode);
        }

        else
        {
            if (!WhyFail)
            {
                WhyFail = "???";
            }

            sprintf (WhyBuf, "DoName: Malformed Name [%s]", WhyFail);
            Why = WhyBuf;
        }

        WhyFail = NULL;
        Excep = S_ERROR;
    }

    CheckTrash ("leave DoName");

    DEBUG_PRINT (TRACE_EXEC, ("Leave DoName %s \n", RV[Excep]));

    return Excep;
}


/*****************************************************************************
 *
 * FUNCTION:    GenLabel
 *
 * PARAMETERS:  char    *Name     The name to be generated
 *
 * DESCRIPTION: If generating assembly output, generate a label.
 *              As of 3/5/97, this generates a comment instead so we don't
 *              need to worry about multiple definitions.
 *
 ****************************************************************************/

void 
GenLabel (char *Name)
{
    FUNCTION_TRACE ("GenLabel");


    if (fAsmFile)
    {
        OsdPrintf (fAsmFile, "\n; %s", Name);
    }

}

