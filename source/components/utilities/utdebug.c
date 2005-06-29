
/******************************************************************************
 * 
 * Module Name: excommon - Debug and error reporting routines
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


#define __EXCOMMON_C__

#include <acpi.h>
#include <acpiobj.h>
#include <interpreter.h>
#include <stdarg.h>


#define _THIS_MODULE        "excommon.c"
#define _COMPONENT          MISCELLANEOUS



/*****************************************************************************
 * 
 * FUNCTION:    Get/Set debug level
 *
 * DESCRIPTION: Get or set value of the debug flag
 *
 ****************************************************************************/


INT32
GetDebugLevel (void)
{

    return DebugLevel;
}

void
SetDebugLevel (INT32 NewDebugLevel)
{

    DebugLevel = NewDebugLevel;
}


/*****************************************************************************
 * 
 * FUNCTION:    FunctionTrace
 *
 * DESCRIPTION: Function entry trace
 *
 ****************************************************************************/

void
FunctionTrace (char *ModuleName, INT32 LineNumber, INT32 ComponentId, char * FunctionName)
{

    DebugPrint (ModuleName, LineNumber, ComponentId, TRACE_FUNCTIONS,
                "Entered Function: %s\n", FunctionName);
}


/*****************************************************************************
 * 
 * FUNCTION:    DebugPrint
 *
 * DESCRIPTION: Print error message 
 *
 ****************************************************************************/

void
DebugPrint (char *ModuleName, INT32 LineNumber, INT32 ComponentId, INT32 PrintLevel, char *Format, ...)
{
    va_list         args;



    /* Both the level and the component must be enabled */

    if ((PrintLevel & DebugLevel) && (ComponentId & DebugLayer))
    {
        va_start (args, Format);

        OsdPrintf (NULL, "%10s(%04d-%02x): ", ModuleName, LineNumber, ComponentId);
        OsdVprintf (NULL, Format, args);

        va_end (args);
    }
}


/*****************************************************************************
 * 
 * FUNCTION:    DebugPrintPrefix
 *
 * DESCRIPTION: Print error message 
 *
 ****************************************************************************/

void
DebugPrintPrefix (char *ModuleName, INT32 LineNumber, INT32 ComponentId)
{


    OsdPrintf (NULL, "%10s(%04d-%02x): ", ModuleName, LineNumber, ComponentId);
}


/*****************************************************************************
 * 
 * FUNCTION:    DebugPrintRaw
 *
 * DESCRIPTION: Print error message -- without module/line indentifiers 
 *
 ****************************************************************************/

void
DebugPrintRaw (char *Format, ...)
{
    va_list         args;


    va_start (args, Format);

    OsdVprintf (NULL, Format, args);

    va_end (args);
}


/*****************************************************************************
 * 
 * FUNCTION:    _ReportError
 *
 * DESCRIPTION: Print error message from KD table
 *
 ****************************************************************************/

void
_ReportError (char *ModuleName, INT32 LineNumber, INT32 ComponentId, ST_KEY_DESC_TABLE *KdtEntry)
{

    DebugPrint (ModuleName, LineNumber, ComponentId, ACPI_ERROR, 
                "*** Error [%s]: %s\n", KdtEntry->Key, KdtEntry->Description);

    _Kinc_error (KdtEntry->Key, 
                    PACRLF, LineNumber, ModuleName, 0, 0);
}


/*****************************************************************************
 * 
 * FUNCTION:    _ReportWarning
 *
 * DESCRIPTION: Print warning message from KD table
 *
 ****************************************************************************/

void
_ReportWarning (char *ModuleName, INT32 LineNumber, INT32 ComponentId, ST_KEY_DESC_TABLE *KdtEntry)
{

    DebugPrint (ModuleName, LineNumber, ComponentId, ACPI_WARN, 
                "*** Warning [%s]: %s\n", KdtEntry->Key, KdtEntry->Description);

    _Kinc_warning (KdtEntry->Key, 
                    PACRLF, LineNumber, ModuleName, 0, 0);
}


/*****************************************************************************
 * 
 * FUNCTION:    _ReportSuccess
 *
 * DESCRIPTION: Print warning message from KD table
 *
 ****************************************************************************/

void
_ReportSuccess (char *ModuleName, INT32 LineNumber, INT32 ComponentId, ST_KEY_DESC_TABLE *KdtEntry)
{

    DebugPrint (ModuleName, LineNumber, ComponentId, ACPI_SUCCESS, 
                "*** Success [%s] %s\n", KdtEntry->Key, KdtEntry->Description);
}


/*****************************************************************************
 * 
 * FUNCTION:    _ReportInfo
 *
 * DESCRIPTION: Print information message from KD table
 *
 ****************************************************************************/

void
_ReportInfo (char *ModuleName, INT32 LineNumber, INT32 ComponentId, ST_KEY_DESC_TABLE *KdtEntry)
{

    DebugPrint (ModuleName, LineNumber, ComponentId, ACPI_INFO, 
                "*** Info [%s], %s\n", KdtEntry->Key, KdtEntry->Description);

    _Kinc_info (KdtEntry->Key, 
                    PACRLF, LineNumber, ModuleName, 0, 0);
}


/*****************************************************************************
 * 
 * FUNCTION:    _AllocateObjectDesc
 *
 * RETURN:      Pointer to newly allocated object descriptor
 *
 * DESCRIPTION: Allocate a new object descriptor.  Gracefully handle
 *              error conditions.
 *
 ****************************************************************************/

void *
_AllocateObjectDesc (char *ModuleName, INT32 LineNumber, INT32 ComponentId, ST_KEY_DESC_TABLE *KdtEntry)
{
    OBJECT_DESCRIPTOR       *NewDesc;


    /* Attempt to allocate new descriptor */

    NewDesc = NEW (OBJECT_DESCRIPTOR);
    if (!NewDesc)
    {
        /* Allocation failed */
        
        _REPORT_ERROR (ModuleName, LineNumber, ComponentId, KdtEntry);
        OutOfMemory = TRUE;
    }

    return NewDesc;
}


/*****************************************************************************
 * 
 * FUNCTION:    _LocalAllocate 
 *
 * RETURN:      Pointer to newly allocated memory
 *
 * DESCRIPTION: Allocate memory.  Gracefully handle
 *              error conditions.
 *
 ****************************************************************************/

void *
_LocalAllocate (char *ModuleName, INT32 LineNumber, INT32 ComponentId, INT32 AllocSize)
{
    ST_KEY_DESC_TABLE   AKDT = {"0000", '1', "LocalAllocate: Memory allocation failure", 
                                              "LocalAllocate: Memory allocation failure"};
    void                *Block;


    Block = OsdAllocate ((size_t) AllocSize);
    if (!Block)
    {
        /* Report allocation error */

        _REPORT_ERROR (ModuleName, LineNumber, ComponentId, &AKDT);
        OutOfMemory = TRUE;
    }

    return Block;
}


/*****************************************************************************
 * 
 * FUNCTION:    _LocalCallocate 
 *
 * RETURN:      Pointer to newly allocated memory
 *
 * DESCRIPTION: Allocate memory via calloc (initialized to zero).  
 *              Gracefully handle error conditions.
 *
 ****************************************************************************/

void *
_LocalCallocate (char *ModuleName, INT32 LineNumber, INT32 ComponentId, INT32 AllocSize)
{
    ST_KEY_DESC_TABLE   AKDT = {"0000", '1', "LocalCallocate: Memory allocation failure", 
                                              "LocalCallocate: Memory allocation failure"};
    void                *Block;


    Block = OsdCallocate ((size_t) AllocSize);
    if (!Block)
    {
        /* Report allocation error */

        _REPORT_ERROR (ModuleName, LineNumber, ComponentId, &AKDT);
        OutOfMemory = TRUE;
    }

    return Block;
}


/*****************************************************************************
 * 
 * FUNCTION:    Kinc functions
 *
 * RETURN:      none
 *
 * DESCRIPTION: Increment global counters ?? TBD
 *              No error message printed here, done by the REPORT* functions
 *
 ****************************************************************************/


void
_Kinc_error (char *a, INT32 b, INT32 c, char * d, INT32 e, INT32 f)
{

/*    OsdPrintf (NULL, "%10s(%04d): *** Error %s\n", d, c, a);  */

    return;
}



void
_Kinc_info (char *a, INT32 b, INT32 c, char * d, INT32 e, INT32 f)
{

/*    OsdPrintf (NULL, "%10s(%04d): *** Info %s\n", d, c, a); */

    return;
}

void
_Kinc_warning (char *a, INT32 b, INT32 c, char * d, INT32 e, INT32 f)
{

/*    OsdPrintf (NULL, "%10s(%04d): *** Warning %s\n", d, c, a); */

    return;
}


/* Obsolete interfaces?? (but the simpler interface is what we want.*/

/*
void
Kinc_error (char *a, INT32 b)
{

    OsdPrintf (NULL, "*** Error %s\n", a);  

    return;
}
*/
/*
void
Kinc_info (char *a, INT32 b, INT32 c, char * d, INT32 e, INT32 f)
{

    OsdPrintf (NULL, "%10s(%04d): *** Info %s\n", d, c, a);

    return;
}
*/

/*
void
Kinc_warning (char *a, INT32 b)
{

     OsdPrintf (NULL, "*** Warning %s\n", a); 
    return;
}
*/

/*
void
KFatalError (char * a, char * b, ...)
{
    /* Optional parameters (...) not implemented


    OsdPrintf (NULL, "*** Fatal Error %s: %s\n", a, b);
    return;
}
*/


/* Misc stuff */

/* TBD: Need a real checksum routine here !! */


UINT8
checksum (void *pvBuf,UINT32 stBufSize)
{
    return 0;
}



/* TBD: Potentially obsolete stuff!! */


INT32
DecIndent (void)
{
    return 0;
}


INT32
IncIndent (void)
{
    return 0;
}





