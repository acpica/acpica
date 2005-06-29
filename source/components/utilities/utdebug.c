/*
  __________________________________________________________________________
 |
 |
 |           Copyright (C) Intel Corporation 1994-1998
 |
 | All rights reserved. No part of this program or publication may be
 | reproduced, transmitted, transcribed, stored in a retrieval system, or
 | translated into any language or computer language, in any form or by any
 | means, electronic, mechanical, magnetic, optical, chemical, manual, or
 | otherwise, without the prior written permission of Intel Corporation.
 |__________________________________________________________________________
 |
 | excommon.c - Debug and error reporting routines
 | 
 |__________________________________________________________________________

*/

#define __EXCOMMON_C__
#define _THIS_MODULE        "excommon.c"

#include <acpi.h>
#include <acpiobj.h>
#include <amlexec.h>

#include <stdarg.h>


#define WIN_DS_REGISTER     0x0030

/* Globals */

char        * Why;
char        WhyBuf [WHYBUF_SIZE];
INT32       AcpiHook = 0;
INT32       __AcpiLibInitStatus = 0;


/* Debug switch */

#ifdef _DEBUG
INT32 DebugLevel = 0xFFFFFFFF;
#else
INT32 DebugLevel = GLOBAL_ALL;
#endif


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
SetDebugLevel (INT32 dl)
{

    DebugLevel = dl;
}

void 
DisplayTable (void *Header, INT32 DisplayBitFlags)
{
    OsdPrintf (NULL, "DisplayTable called, not supported **********\n");
    return;
}

LogHandle
GetMasterLogHandle (void)
{

/*  return NO_LOG_HANDLE; */

    return 1; /* stdout; TEMPORARY!!! */
}



/*****************************************************************************
 * 
 * FUNCTION:    FunctionTrace
 *
 * DESCRIPTION: Function entry trace
 *
 ****************************************************************************/

void
FunctionTrace (char *ModuleName, INT32 LineNumber, char * FunctionName)
{

    DebugPrint (ModuleName, LineNumber, TRACE_FUNCTIONS,
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
DebugPrint (char *ModuleName, INT32 LineNumber, INT32 PrintLevel, char *Format, ...)
{
    va_list         args;



    if (PrintLevel & DebugLevel)
    {
        va_start (args, Format);

        OsdPrintf (NULL, "%10s(%04d): ", ModuleName, LineNumber);
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
DebugPrintPrefix (char *ModuleName, INT32 LineNumber)
{


    OsdPrintf (NULL, "%10s(%04d): ", ModuleName, LineNumber);
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
_ReportError (char *ModuleName, INT32 LineNumber, ST_KEY_DESC_TABLE *KdtEntry)
{

    DebugPrint (ModuleName, LineNumber, GLOBAL_ERROR, 
                "*** Error [%s]: %s\n", KdtEntry->Key, KdtEntry->Description);

    _Kinc_error (KdtEntry->Key, 
                    PACRLF, LineNumber, ModuleName, 0, 0);
    Why = KdtEntry->Description;
}


/*****************************************************************************
 * 
 * FUNCTION:    _ReportWarning
 *
 * DESCRIPTION: Print warning message from KD table
 *
 ****************************************************************************/

void
_ReportWarning (char *ModuleName, INT32 LineNumber, ST_KEY_DESC_TABLE *KdtEntry)
{

    DebugPrint (ModuleName, LineNumber, GLOBAL_WARN, 
                "*** Warning [%s]: %s\n", KdtEntry->Key, KdtEntry->Description);

    _Kinc_warning (KdtEntry->Key, 
                    PACRLF, LineNumber, ModuleName, 0, 0);
    Why = KdtEntry->Description;
}


/*****************************************************************************
 * 
 * FUNCTION:    _ReportSuccess
 *
 * DESCRIPTION: Print warning message from KD table
 *
 ****************************************************************************/

void
_ReportSuccess (char *ModuleName, INT32 LineNumber, ST_KEY_DESC_TABLE *KdtEntry)
{

    DebugPrint (ModuleName, LineNumber, GLOBAL_SUCCESS, 
                "*** Success [%s] %s\n", KdtEntry->Key, KdtEntry->Description);

    Why = KdtEntry->Description;
}


/*****************************************************************************
 * 
 * FUNCTION:    _ReportInfo
 *
 * DESCRIPTION: Print information message from KD table
 *
 ****************************************************************************/

void
_ReportInfo (char *ModuleName, INT32 LineNumber, ST_KEY_DESC_TABLE *KdtEntry)
{

    DebugPrint (ModuleName, LineNumber, GLOBAL_INFO, 
                "*** Info [%s], %s\n", KdtEntry->Key, KdtEntry->Description);

    _Kinc_info (KdtEntry->Key, 
                    PACRLF, LineNumber, ModuleName, 0, 0);
    Why = KdtEntry->Description;
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
_AllocateObjectDesc (char *ModuleName, INT32 LineNumber, ST_KEY_DESC_TABLE *KdtEntry)
{
    OBJECT_DESCRIPTOR       *NewDesc;


    /* Attempt to allocate new descriptor */

    NewDesc = NEW (OBJECT_DESCRIPTOR);
    if (!NewDesc)
    {
        /* Allocation failed */
        
        _REPORT_ERROR (ModuleName, LineNumber, KdtEntry);
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
_LocalAllocate (char *ModuleName, INT32 LineNumber, INT32 AllocSize)
{
    ST_KEY_DESC_TABLE   AKDT = {"0000", '1', "LocalAllocate: Memory allocation failure", 
                                              "LocalAllocate: Memory allocation failure"};
    void                *Block;


    Block = OsdAllocate ((size_t) AllocSize);
    if (!Block)
    {
        /* Report allocation error */

        _REPORT_ERROR (ModuleName, LineNumber, &AKDT);
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
_LocalCallocate (char *ModuleName, INT32 LineNumber, INT32 AllocSize)
{
    ST_KEY_DESC_TABLE   AKDT = {"0000", '1', "LocalCallocate: Memory allocation failure", 
                                              "LocalCallocate: Memory allocation failure"};
    void                *Block;


    Block = OsdCallocate ((size_t) AllocSize);
    if (!Block)
    {
        /* Report allocation error */

        _REPORT_ERROR (ModuleName, LineNumber, &AKDT);
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


/*****************************************************************************
 * 
 * FUNCTION:    OFT functions
 *
 * RETURN:      none
 *
 * DESCRIPTION: Purpose unknown ?? TBD
 *
 ****************************************************************************/

void
CloseOFT (void)
{

    DEBUG_PRINT (TRACE_EXEC, ("CloseOFT called, not supported **********\n"));
    return;
}

void
RestoreOFT (void)
{

    DEBUG_PRINT (TRACE_EXEC, ("RestoreOFT called, not supported **********\n"));
    return;
}

void
SetNotSupported (void)
{
    DEBUG_PRINT (TRACE_EXEC, ("SetNotSupported called, not supported **********\n"));
    return;
}


/*****************************************************************************
 * 
 * FUNCTION:    Interrupt functions
 *
 * RETURN:      none
 *
 * DESCRIPTION: Install/deinstall
 *
 ****************************************************************************/

/* Interrupt handlers */

UINT32
InstallInterruptHandler (
    UINT8               InterruptNumber,
    INT32               (* Isr)(void),
    UINT8               InterruptTaskFlag,
    UINT32 *            ExceptPtr)
{

    UINT32 RetVal;


    OsdPrintf (NULL, "InstallInterruptHandler called, not supported **********\n");

    RetVal = (UINT32) OsdInstallInterruptHandler ((UINT32) InterruptNumber, 
                                                    Isr, ExceptPtr);

    
    return(RetVal);

}

INT32
RemoveInterruptHandler (UINT32 Key)
{

    OsdPrintf (NULL, "RemoveInterruptHandler called, not supported **********\n");
    return 0;
}


/*****************************************************************************
 * 
 * FUNCTION:    DumpBuf
 *
 * RETURN:      none
 *
 * DESCRIPTION: Generic dump buffer in hex and ascii.
 *
 ****************************************************************************/

void
DumpBuf (UINT8 *Buffer, UINT32 Count, INT32 Flags, LogHandle LogFile,
            INT32 iLogFlags)
{
    UINT32      i = 0;
    UINT32      j;
    UINT8       BufChar;


    /* Only dump the buffer if tracing is enabled */

    if (!(TRACE_TABLES & DebugLevel))
    {
        return;
    }


    /*
     * Nasty little dump buffer routine!
     */
    while (i <= Count)
    {
        /* Print current offset */

        OsdPrintf (NULL, "%05X    ", i);


        /* Print 16 hex chars */

        for (j = 0; j < 16; j++)
        {
            if (i + j >= Count)
                goto cleanup;

            OsdPrintf (NULL, "%02X ", Buffer[i + j]);
        }

        /* 
         * Print the ASCII equivalent characters
         * But watch out for the bad unprintable ones...
         */

        for (j = 0; j < 16; j++)
        {
            if (i + j >= Count)
                goto cleanup;

            BufChar = Buffer[i + j];
            if ((BufChar > 0x1F && BufChar < 0x2E) ||
                (BufChar > 0x2F && BufChar < 0x61) ||
                (BufChar > 0x60 && BufChar < 0x7F))

                OsdPrintf (NULL, "%c", BufChar);
            else
                OsdPrintf (NULL, ".");
                
        }

        /* Done with that line. */

        OsdPrintf (NULL, "\n");
        i += 16;
    }

    return;

cleanup:
    OsdPrintf (NULL, "\n");
    return;

}


