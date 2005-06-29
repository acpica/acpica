
/******************************************************************************
 * 
 * Module Name: nsaccess - Top-level functions for accessing ACPI namespace
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


#define __NSACCESS_C__

#include <acpi.h>
#include <amlcode.h>
#include <interpreter.h>
#include <namespace.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>


#define _THIS_MODULE        "nsaccess.c"
#define _COMPONENT          NAMESPACE


/* Scope stack */

SCOPE_STACK     ScopeStack[MAXNEST];
SCOPE_STACK     *CurrentScope;

/* 
 * Elements of NsProperties are bit significant
 * and should be one-to-one with values of NsType in acpinmsp.h
 */

INT32 NsProperties[] = {     /* properties of types */
    0,                      /* Any              */
    0,                      /* Number           */
    0,                      /* String           */
    0,                      /* Buffer           */
    LOCAL,                  /* Package          */
    0,                      /* FieldUnit        */
    NEWSCOPE | LOCAL,       /* Device           */
    LOCAL,                  /* Event            */
    NEWSCOPE | LOCAL,       /* Method           */
    LOCAL,                  /* Mutex            */
    LOCAL,                  /* Region           */
    NEWSCOPE | LOCAL,       /* Power            */
    NEWSCOPE | LOCAL,       /* Processor        */
    NEWSCOPE | LOCAL,       /* Thermal          */
    0,                      /* Alias            */
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0,
    0,                      /* DefField         */
    0,                      /* BankField        */
    0,                      /* IndexField       */
    0,                      /* DefFieldDefn     */
    0,                      /* BankFieldDefn    */
    0,                      /* IndexFieldDefn   */
    0,                      /* If               */
    0,                      /* Else             */
    0,                      /* While            */
    NEWSCOPE,               /* Scope            */
    LOCAL,                  /* DefAny           */
    0                       /* Lvalue           */
};

char BadType[] = "ERROR: unused type encoding found in table";


/* 
 * Elements of NsTypeNames should be
 * one-to-one with values of NsType in acpinmsp.h
 */

/* 
 * The type Any is used as a "don't care" when searching; when stored in a
 * table it really means that we have thus far seen no evidence to indicate
 * what type is actually going to be stored for this entry.
 */

char *NsTypeNames[] = { /* printable names of types */
    "Unknown",
    "Number",
    "String",
    "Buffer",
    "Package",
    "FieldUnit",
    "Device",
    "Event",
    "Method",
    "Mutex",
    "Region",
    "Power",
    "Processor",
    "Thermal",
    "Alias",
    BadType, 
    BadType, 
    BadType, 
    BadType, 
    BadType,
    BadType, 
    BadType, 
    BadType, 
    BadType, 
    BadType,
    "DefField",
    "BankField",
    "IndexField",
    "DefFieldDefn",
    "BankFieldDefn",
    "IndexFieldDefn",
    "If",
    "Else",
    "While",
    "Scope",
    "ERROR: DefAny found in table", /* should never happen */
    "ERROR: Lvalue found in table"  /* should never happen */
};



static ST_KEY_DESC_TABLE KDT[] = {
    {"0000", 'I', "Package stack not empty at method exit", "Package stack not empty at method exit"},
    {"0001", '1', "Method stack not empty at method exit", "Method stack not empty at method exit"},
    {"0002", 'I', "Object stack not empty at method exit", "Object stack not empty at method exit"},
    {"0003", '1', "Descriptor Allocation Failure", "Descriptor Allocation Failure"},
    {"0004", '1', "root name table allocation failure", "root name table allocation failure"},
    {"0005", '1', "Initial value descriptor allocation failure", "Initial value descriptor allocation failure"},
    {"0006", '1', "Initial value string allocation failure", "Initial value string allocation failure"},
    {"0007", '1', "Scope has no parent", "Scope has no parent"},
    {"0008", '1', "name table overflow", "name table overflow"},
    {"0009", '1', "A name was not found in given scope", "A name was not found in given scope"},
    {"0010", 'W', "Type mismatch", "Type mismatch"},
    {"0011", '1', "Name Table allocation failure", "Name Table allocation failure"},
    {"0012", '1', " Name not found", " Name not found"},
    {NULL, 'I', NULL, NULL}
};



/****************************************************************************
 *
 *  FUNCTION:       PriUnloadNameSpace (void)
 *
 *  PARAMETERS:     none
 *
 *  RETURN:         E_OK or E_ERROR
 *
 *  DESCRIPTION:    Contracts namespace, typically in response to an undocking
 *                      event
 *
 ****************************************************************************/

INT32
PriUnloadNameSpace (void)
{
    FUNCTION_TRACE ("PriUnloadNameSpace");


    if (!Root)
    {
        return E_ERROR;
    }
    
    return (E_OK);
}

/****************************************************************************
 *
 * FUNCTION:    AcpiExecuteMethod
 *
 * PARAMETERS:  char *MethodName        name of method to execute
 *              OBJECT_DESCRIPTOR       where to put method's return
 *              **ReturnValue           value (if any).
 *                                      ReturnValue must not be
 *                                      passed in as NULL because
 *                                      *ReturnValue will always
 *                                      be set (to NULL if there is
 *                                      no return value).
 *              OBJECT_DESCRIPTOR 
 *              **Params                list of parameters to pass to
 *                                      method, terminated by NULL.
 *                                      Params itself may be NULL
 *                                      if no parameters are being
 *                                      passed.
 *
 * RETURN:      E_OK or E_ERROR
 *
 * DESCRIPTION: Find and execute the requested method passing the given
 *              parameters
 *
 * ALLOCATION:
 * Reference       Size                 Pool Owner       Description
 * *ReturnValue    s(OBJECT_DESCRIPTOR) bu   CALLER      returned value
 *
 ****************************************************************************/

INT32
AcpiExecuteMethod (char * MethodName, OBJECT_DESCRIPTOR **ReturnValue,
                    OBJECT_DESCRIPTOR **Params)
{
    nte             *MethodPtr = NULL;
    char            *FullyQualifiedName = NULL;
    INT32           Excep = E_ERROR;


    FUNCTION_TRACE ("AcpiExecuteMethod");


BREAKPOINT3;

    if (ReturnValue)
    {
        *ReturnValue = NULL;
    }

    if (!Root)
    {
        /* 
         * If the name space has not been initialized, the Method has surely
         * not been defined and there is nothing to execute.
         */

        DEBUG_PRINT (ACPI_ERROR, ("Name space not initialized ==> method not defined\n"));
    }
    else if (!MethodName)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AcpiExecuteMethod: MethodName is NULL\n"));
    }


    if (Root && MethodName)
    {   
        /*  Root and MethodName valid   */

        if (MethodName[0] != '\\' || MethodName[1] != '/')
        {
            MethodName = InternalizeName (MethodName);
        }

        /* See comment near top of file re significance of FETCH_VALUES */

#ifdef FETCH_VALUES
        MethodPtr = (nte *) NsEnter (MethodName, Any, Exec);
#else 
        MethodPtr = (nte *) NsEnter (MethodName, Method, Exec);
#endif

        if (NOTFOUND == MethodPtr)
        {
            DEBUG_PRINT (ACPI_ERROR, ("Method [%s] was not found\n", MethodName));
        }
    }

    if (Root && MethodName && (NOTFOUND != MethodPtr))
    {   
        /*  Root, MethodName, and Method valid  */

#ifdef FETCH_VALUES
        if (NsValType (MethodPtr) == Method)
        {
            /* Method points to a method name */
        
            LINE_SET (55, Exec);
            DEBUG_PRINT (ACPI_INFO,
                        ("[%s Method %p ptrVal %p\n",
                        MethodName, MethodPtr, MethodPtr->ptrVal));

            if (MethodPtr->ptrVal)
            {
                DEBUG_PRINT (ACPI_INFO,
                            ("Offset %x Length %lx]\n",
                            ((meth *) MethodPtr->ptrVal)->Offset + 1,
                            ((meth *) MethodPtr->ptrVal)->Length - 1));
            }
        
            else
            {
                DEBUG_PRINT (ACPI_INFO, ("*Undefined*]\n"));
            }
#endif

            /* 
             * Here if not FETCH_VALUES (and hence only Method was looked for), or
             * FETCH_VALUES and the name found was in fact a Method.  In either
             * case, set the current scope to that of the Method, and execute it.
             */

            if (!MethodPtr->ptrVal)
            {
                DEBUG_PRINT (ACPI_ERROR, ("Method is undefined\n"));
            }

            else
            {
                DEBUG_EXEC ((FullyQualifiedName = NsFullyQualifiedName(MethodPtr->ChildScope)));
                DEBUG_PRINT (TRACE_NAMES, ("Set scope %s \n", FullyQualifiedName));
        
                /*  reset current scope to beginning of scope stack */

                CurrentScope = &ScopeStack[0];

                /*  push current scope on scope stack and make hMethod->ChildScope current  */

                NsPushCurrentScope (MethodPtr->ChildScope, Method);

                DEBUG_EXEC ((FullyQualifiedName = NsFullyQualifiedName (MethodPtr)));
                DEBUG_PRINT (TRACE_NAMES, ("Exec Method %s at offset %8XH\n",
                                  FullyQualifiedName, 
                                  ((meth *) MethodPtr->ptrVal)->Offset + 1));
        
                ClearPkgStack ();
                ObjStackTop = 0;                                           /* Clear object stack */
                
                /* Excecute the method here */

                Excep = AmlExec (((meth *) MethodPtr->ptrVal)->Offset + 1,
                                    ((meth *) MethodPtr->ptrVal)->Length - 1,
                                    Params);

                if (PkgNested ())
                {
                    /*  Package stack not empty at method exit  */

                    REPORT_INFO (&KDT[0]);
                }

                if (GetMethodDepth () > -1)
                {
                    /*  Method stack not empty at method exit   */

                    REPORT_ERROR (&KDT[1]);
                }

                if (ObjStackTop)
                {
                    /*  Object stack not empty at method exit   */

                    /* OBSOLETE!!  INT32           SaveTrace = Trace; */

                    REPORT_INFO (&KDT[2]);
            
                    /* OBSOLETE:  Trace |= TraceExec;  */        
                    /* enable output from DumpStack */
                    DumpStack (Exec, "Remaining Object Stack entries", -1, "");
                }

                DEBUG_PRINT (ACPI_INFO, ("*** Completed execution of method %s ***\n",
                                FullyQualifiedName));
            }

#ifdef FETCH_VALUES
        }
    
        else
        {
            /*
             * Method points to a name that is not a method
             * Here if FETCH_VALUES and the name found was not a Method.
             * Return its value.
             */
            OBJECT_DESCRIPTOR           *ObjDesc;


            DEBUG_PRINT (ACPI_INFO, ("Value: \n"));
            DUMP_ENTRY (MethodPtr);

            ObjDesc = AllocateObjectDesc (&KDT[3]);
            if (!ObjDesc)
            {               
                DEBUG_PRINT (ACPI_ERROR, ("AcpiExecuteMethod: Descriptor Allocation Failure\n"));
            }
            
            else
            {
                /* Construct a descriptor pointing to the name */
            
                ObjDesc->Lvalue.ValType = (UINT8) Lvalue;
                ObjDesc->Lvalue.OpCode  = (UINT8) NameOp;
                ObjDesc->Lvalue.Ref     = (void *) MethodPtr;

                /* 
                 * Put it on the stack, and use GetRvalue() to get the value.
                 * Note that ObjStackTop points to the top valid entry, not to
                 * the first unused position.
                 */

                DeleteObject ((OBJECT_DESCRIPTOR **) &ObjStack[ObjStackTop]);
                ObjStack[ObjStackTop] = (void *) ObjDesc;
                Excep = GetRvalue ((OBJECT_DESCRIPTOR **) &ObjStack[ObjStackTop]);

                /* 
                 * If GetRvalue() succeeded, treat the top stack entry as
                 * a return value.
                 */

                if (S_SUCCESS == Excep)
                {
                    Excep = S_RETURN;
                }
            }
        }
#endif


BREAKPOINT3;

        if (S_ERROR == Excep)
        {
            Excep = E_ERROR;
        }
    
        if (S_RETURN == Excep)
        {
            /* 
             * If the Method returned a value and the caller provided a place
             * to store a returned value, pass back the returned value.
             */

            if (ReturnValue)
            {
                *ReturnValue = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];
            }
        
            else
            {
                DELETE (ObjStack[ObjStackTop]);
            }

            Excep = E_OK;
        }
    }

    return Excep;
}


/****************************************************************************
 *
 * FUNCTION:    AcpiLoadTableInNameSpace
 *
 * PARAMETERS:  none
 *
 * RETURN:      E_OK or E_ERROR
 *
 * DESCRIPTION: Expands namespace, typically in response to a docking event
 *
 ****************************************************************************/

INT32
AcpiLoadTableInNameSpace (void)
{
    FUNCTION_TRACE ("AcpiLoadTableInNameSpace");


    if (!Root)
    {
        return E_ERROR;
    }
    
    return (E_OK);
}



/****************************************************************************
 * 
 * FUNCTION:    NsSetup()
 *
 * PARAMETERS:  none
 *
 * DESCRIPTION: Allocate and initialize the root name table
 *
 * ALLOCATION:
 * Reference        Size                 Pool  Owner       Description
 * Root             NsRootSize*s(nte)    bu    acpinmsp    Root Name Table
 * nte.ptrVal       s(OBJECT_DESCRIPTOR) bu    acpinmsp    initialized value
 * ptrVal->String   varies               bu    acpinmsp    string value
 *
 ***************************************************************************/

void
NsSetup (void)
{
    struct InitVal          *InitVal = NULL;


    FUNCTION_TRACE ("NsSetup");


    /* 
     * Root is initially NULL, so a non-NULL value indicates
     * that NsSetup() has already been called; just return.
     */

    if (Root)
    {
        return;
    }

    NsCurrentSize = NsRootSize = ROOTSIZE;
    Root = AllocateNteDesc (NsRootSize);
    if (!Root)
    {
        /*  root name table allocation failure  */

        REPORT_ERROR (&KDT[4]);
    }

    /* Push the root name table on the scope stack */
    
    ScopeStack[0].Scope = Root;
    ScopeStack[0].Type = Any;
    CurrentScope = &ScopeStack[0];

#ifdef NSLOGFILE
    LogFile = OsdOpen ("ns.log", "wtc");
    OsdPrintf (LogFile, "root = %08x size %d\n", Root, NsRootSize);
#endif

    /* Enter the pre-defined names in the name table */
    
    DEBUG_PRINT (ACPI_INFO, ("Entering predefined name table into namespace\n"));

    for (InitVal = PreDefinedNames; InitVal->Name; InitVal++)
    {
        NsHandle handle = NsEnter (InitVal->Name, InitVal->Type, Load);

        /* 
         * if name entered successfully
         *  && its entry in PreDefinedNames[] specifies an initial value
         */
        
        if (handle && InitVal->Val)
        {
            /* Entry requests an initial value, allocate a descriptor for it. */
            
            OBJECT_DESCRIPTOR       *ObjDesc = AllocateObjectDesc (&KDT[5]);

            if (ObjDesc)
            {
                ObjDesc->ValType = (UINT8) InitVal->Type;

                /* 
                 * Convert value string from table entry to internal representation.
                 * Only types actually used for initial values are implemented here.
                 */

                switch (InitVal->Type)
                {
                case Number:
                    ObjDesc->Number.Number = (UINT32) atol (InitVal->Val);
                    break;

                case String:
                    ObjDesc->String.StrLen = (UINT16) strlen (InitVal->Val);

                    /* 
                     * XXX - if this OsdAllocate() causes a garbage collection pass,
                     * XXX - ObjDesc will get deleted since no NT points to it yet.
                     * XXX - This "should not happen" during initialization.
                     */

                    ObjDesc->String.String = OsdAllocate ((size_t) (ObjDesc->String.StrLen + 1));
                    if (!ObjDesc->String.String)
                    {
                        REPORT_ERROR (&KDT[6]);
                    }
                    else
                    {
                        strcpy ((char *) ObjDesc->String.String, InitVal->Val);
                    }
                    
                    break;

                default:
                    DELETE (ObjDesc);
                    continue;
                }

                /* Store pointer to value descriptor in nte */
            
                NsSetValue(handle, ObjDesc, ObjDesc->ValType);
            }
        }
    }

#ifdef PLUMBER
    RegisterMarkingFunction (NsMarkNS);
#endif
}


/****************************************************************************
 *
 * FUNCTION:    NsEnter
 *
 * PARAMETERS:  char    *Name       name to be entered, in internal format
 *                                  as represented in the AML stream
 *              NsType  Type        type associated with name
 *              OpMode  LoadMode    Load => add name if not found
 *
 * RETURN:      Handle to the nte for the passed name
 *
 * DESCRIPTION: Find or enter the passed name in the name space.
 *              Log an error if name not found in Exec mode.
 *
 * ALLOCATION:
 * Reference        Size                 Pool  Owner       Description
 * nte.ChildScope   TABLSIZE*s(nte)      bu    acpinmsp    Name Table
 *
 ***************************************************************************/

NsHandle
NsEnter (char *Name, NsType Type, OpMode LoadMode)
{
    nte             *EntryToSearch = NULL;
    nte             *ThisEntry = NULL;
    nte             *ScopeToPush = NULL;
    INT32           Size;
    INT32           NumSegments;
    INT32           NullNamePath = FALSE;
    NsType          TypeToCheckFor;              /* Type To Check For */


    FUNCTION_TRACE ("NsEnter");


    if (!Root)
    {
        /* 
         * If the name space has not been initialized:
         * -  In Pass1 of Load mode, we need to initialize it
         *    before trying to define a name.
         * -  In Exec mode, there are no names to be found.
         */

        if (Load1 == LoadMode)
        {
            NsSetup ();
        }
        else
        {
            return NOTFOUND;
        }
    }

    if (!Name)
    {
        /* Invalid parameter */

        return NOTFOUND;
    }

    DEBUG_PRINT (TRACE_NAMES,
                    ("NsEnter: Name[0-5] - %02x %02x %02x %02x %02x %02x \n",
                    Name[0], Name[1], Name[2], Name[3], Name[4], Name[5]));

    CheckTrash ("enter NsEnter");

    /* DefFieldDefn and BankFieldDefn define fields in a Region */
    
    if (DefFieldDefn == Type || BankFieldDefn == Type)
    {
        TypeToCheckFor = Region;
    }
    else
    {
        TypeToCheckFor = Type;
    }

    /* 
     * Check for prefixes.  As represented in the AML stream, a Name consists
     * of an optional scope prefix followed by a segment part.
     *
     * If present, the scope prefix is either a RootPrefix (in which case the
     * name is fully qualified), or one or more ParentPrefixes (in which case
     * the name's scope is relative to the current scope).
     *
     * The segment part consists of:
     *  + a single 4-byte name segment, or
     *  + a DualNamePrefix followed by two 4-byte name segments, or
     *  + a MultiNamePrefixOp, followed by a byte indicating the number of
     *    segments and the segments themselves.
     */

    if (*Name == RootPrefix)
    {
        /* Name is fully qualified, look in root name table */
        
        DEBUG_PRINT (TRACE_NAMES, ("root \n"));
        
        EntryToSearch = Root;
        Size = NsRootSize;
        Name++;                 /* point to segment part */
    }
    
    else
    {
        char        *OrigName = Name;


        /* Name is relative to current scope, start there */
        
        EntryToSearch = CurrentScope->Scope;
        Size = NsCurrentSize;

        while (*Name == ParentPrefix)
        {
            /*  recursively search in parent's name scope   */

            DEBUG_PRINT (TRACE_NAMES, ("parent \n"));
            
            Name++;                   /* point to segment part or next ParentPrefix */
            EntryToSearch = EntryToSearch->ParentScope;
            
            if (!EntryToSearch)
            {
                /* Scope has no parent */
                
                LINE_SET ((INT32) strlen (OrigName) + 18, LoadMode);
                REPORT_ERROR (&KDT[7]);
                LINE_SET (0, LoadMode);
                CheckTrash ("leave NsEnter NOTFOUND 1");

                return (NsHandle) NOTFOUND;
            }
        }

        if (EntryToSearch->ParentScope == (nte *) 0)
        {
            /* backed up all the way to the root */
            
            Size = NsRootSize;
        }
    }

    if (*Name == DualNamePrefix)
    {
        DEBUG_PRINT (TRACE_NAMES, ("Dual Name \n"));

        NumSegments = 2;
        Name++;                             /* point to first segment */
    }
    
    else if (*Name == MultiNamePrefixOp)
    {
        DEBUG_PRINT (TRACE_NAMES, ("Multi Name %d \n", Name[1]));
        
        NumSegments = (INT32)* (UINT8 *) ++Name;
        Name++;                             /* point to first segment */
    }

    else if (!Name)
    {
        /*  8-12-98 ASL Grammar Update supports null NamePath   */

        NullNamePath = TRUE;
        NumSegments = 0;
        ThisEntry = Root;
        Size = NsRootSize;
    }

    else
    {
        /* 
         * No Dual or Multi prefix, hence there is only one
         * segment and Name is already pointing to it.
         */
        NumSegments = 1;
    }

    DEBUG_PRINT (TRACE_NAMES, ("Segments = %d \n", NumSegments));

    while (NumSegments-- && EntryToSearch)
    {
        /*  loop through and verify/add each name segment   */
        
        CheckTrash ("before SearchTable");
        
        /* 
         * Search for the current segment in the table where it should be.
         * Type is significant only at the last level.
         */

        ThisEntry = SearchTable (Name, EntryToSearch, Size, LoadMode,
                                NumSegments == 0 ? Type : Any);
        CheckTrash ("after SearchTable");

        if (ThisEntry == NOTFOUND)
        {
            /*  name not in ACPI namespace  */

            if (Load1 == LoadMode || Load == LoadMode)
            {
                REPORT_ERROR (&KDT[8]);
            }

            else
            {
                REPORT_ERROR (&KDT[9]);
            }

            CheckTrash ("leave NsEnter NOTFOUND 2");
            return (NsHandle) NOTFOUND;
        }

        if (NumSegments         == 0  &&                /* if last segment                  */
            TypeToCheckFor      != Any &&               /* and looking for a specific type  */
            TypeToCheckFor      != DefAny &&            /* which is not a phoney type       */
            TypeToCheckFor      != Scope &&             /*   "   "   "  "   "     "         */
            TypeToCheckFor      != IndexFieldDefn &&    /*   "   "   "  "   "     "         */
            ThisEntry->NtType   != Any &&               /* and type of entry is known       */
            ThisEntry->NtType   != TypeToCheckFor)      /* and entry does not match request */
        {                                               /* complain.                        */
            /*  complain about type mismatch    */

            REPORT_WARNING (&KDT[10]);
        }

        /*
         * If last segment and not looking for a specific type, but type of
         * found entry is known, use that type to see if it opens a scope.
         */

        if ((0 == NumSegments) && (Any == Type))
        {
            Type = ThisEntry->NtType;
        }

        if ((NumSegments || NsOpensScope (Type)) &&
            (ThisEntry->ChildScope == (nte *) 0))
        {
            /* 
             * more segments or the type implies enclosed scope, 
             * and the next scope has not been allocated ...
             */

            DEBUG_PRINT (ACPI_INFO, ("Load mode= %d  ThisEntry= %x\n", LoadMode, ThisEntry));

            if ((Load1 == LoadMode) || (Load == LoadMode))
            {   
                /*  first or second pass load mode ==> locate the next scope    */
                
                DEBUG_PRINT (TRACE_NAMES, ("add level \n"));
                ThisEntry->ChildScope = AllocateNteDesc (TABLSIZE);
            }

            /* Now complain if there is no next scope */
            
            if (ThisEntry->ChildScope == (nte *) 0)
            {
                DEBUG_PRINT (ACPI_ERROR, ("No child scope at entry %p\n", ThisEntry));

                if (Load1 == LoadMode || Load == LoadMode)
                {
                    REPORT_ERROR (&KDT[11]);
                    return (NsHandle) NOTFOUND;
                }

                REPORT_ERROR (&KDT[12]);
                CheckTrash ("leave NsEnter NOTFOUND 3");
                return (NsHandle) NOTFOUND;
            }


#ifdef NSLOGFILE
            OsdPrintf (LogFile, "%s = %08x size %d\n",
                        Name, ThisEntry->ChildScope, TABLSIZE);
#endif

            if (Load1 == LoadMode || Load == LoadMode)
            {
                /* Set newly-created child scope's parent scope */
                
                ThisEntry->ChildScope->ParentScope = EntryToSearch;
            }
        }

        Size = TABLSIZE;
        EntryToSearch = ThisEntry->ChildScope;
        Name += 4;                        /* point to next name segment */
    }

    /* 
     * If entry is a type which opens a scope,
     * push the new scope on the scope stack.
     */

    if (NsOpensScope (TypeToCheckFor))
    {
        /*  8-12-98 ASL Grammar Update supports null NamePath   */

        if (NullNamePath)   
            ScopeToPush = ThisEntry;
        else
            ScopeToPush = ThisEntry->ChildScope;


        CheckTrash ("before NsPushCurrentScope");
        NsPushCurrentScope (ScopeToPush, Type);
        CheckTrash ("after  NsPushCurrentScope");
    }

    return (NsHandle) ThisEntry;
}


