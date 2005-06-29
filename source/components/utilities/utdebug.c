
//
// Common stuff that may move later
//

#include <stdio.h>
#include <stdarg.h>
//include <varargs.h>

#pragma pack(1)
#include <bu.h>
#include "acpiosd.h"
#include <acpi.h>


#define WIN_DS_REGISTER     0x0030

char * pcWhy;
char acWhyBuf [ACWHYBUF_SIZE];

int         iAcpiHook = 0;
int         __iAcpiLibInitStatus = 0;
selector    sFlatSeg;


// Debug switch

int DebugLevel = 0x7FFFFFFF;

int debug_level (void)
{
    return DebugLevel;
}

void set_debug_level (int dl)
{
    DebugLevel = dl;
}



void _dKinc_error (char *a, int b, int c, char * d, int e, int f)
{
    OsdPrintf (NULL, "*** Error %s at line %d, file %s\n", a, c, d); 
    return;
}


void dKinc_error (char *a, int b)
{
    OsdPrintf (NULL, "*** Error %s\n", a); 
    return;
}


void _dKinc_info (char *a, int b, int c, char * d, int e, int f)
{
    OsdPrintf (NULL, "*** Info %s at line %d, file %s\n", a, c, d); 
    return;
}

void dKinc_info (char *a, int b, int c, char * d, int e, int f)
{
    OsdPrintf (NULL, "*** Info %s at line %d, file %s\n", a, c, d); 
    return;
}

void _dKinc_warning (char *a, int b, int c, char * d, int e, int f)
{
    OsdPrintf (NULL, "*** Warning %s at line %d, file %s\n", a, c, d); 
    return;
}

void dKinc_warning (char *a, int b)
{
    OsdPrintf (NULL, "*** Warning %s\n", a); 
    return;
}

void vKFatalError (char * a, char * b)
{
    OsdPrintf (NULL, "*** Fatal Error %s: %s\n", a, b);
    return;
}

void
vCloseOFT (void)
{
    OsdPrintf (NULL, "vCloseOFT called, not supported **********\n");
    return;
}

void
vRestoreOFT (void)
{
    OsdPrintf (NULL, "vRestoreOFT called, not supported **********\n");
    return;
}

void vDumpBuf(BYTE *pbBuffer, size_t sCount, int iFlags, LogHandle hLogFile,
    int iLogFlags)
{
    unsigned int            i = 0;
    unsigned int            j;
    unsigned char           BufChar;


    //
    // Nasty little dump buffer routine!
    //
    while (i <= sCount)
    {

        // Print 16 hex chars

        for (j = 0; j < 16; j++)
        {
            if (i + j >= sCount)
                goto cleanup;

            OsdPrintf (NULL, "%02X ", pbBuffer[i + j]);
        }

        // Print the ASCII equivalent characters
        // But watch out for the bad unprintable ones...

        for (j = 0; j < 16; j++)
        {
            if (i + j >= sCount)
                goto cleanup;

            BufChar = pbBuffer[i + j];
            if ((BufChar > 0x1F && BufChar < 0x2E) ||
                (BufChar > 0x2F && BufChar < 0x61) ||
                (BufChar > 0x60 && BufChar < 0x7F))

                OsdPrintf (NULL, "%c", BufChar);
            else
                OsdPrintf (NULL, ".");
                
        }

        // Done with that line.

        OsdPrintf (NULL, "\n");
        i += 16;
    }

    return;

cleanup:
    OsdPrintf (NULL, "\n");
    return;

}

void
vSetNotSupported (void)
{
    OsdPrintf (NULL, "vSetNotSupported called, not supported **********\n");
    return;
}

void 
vDisplayTable (void *pHeader, int iDisplayBitFlags)
{
    OsdPrintf (NULL, "vDisplayTable called, not supported **********\n");
    return;
}

void
vFunctionHello (char * FileName, char * FunctionName)
{

    OsdPrintf (NULL, "Enter Module: %10s, Function: %s\n", FileName, FunctionName);
}

/*

int
vm86 (void)
{
    return 0;
}

int
iIrqToInt (WORD wIrq)
{
    return 0;
}


// Output format

int
iDecIndent (void)
{
    return 0;
}


int
iIncIndent (void)
{
    return 0;
}

**************/

LogHandle
GetMasterLogHandle (void)
{
//  return NO_LOG_HANDLE;

    return 1; // stdout;
}


// Pointer stuff, must get rid of this eventually

size_t sPtrOffset (void *pvPtr)
{
    OsdPrintf (NULL, "sPtrOffset called, not supported **********\n");
    return (size_t) pvPtr;
}

selector sPtrSelector (void *pvPtr)
{
    OsdPrintf (NULL, "sPtrSelector called, not supported **********\n");
    return (selector) WIN_DS_REGISTER;
}

void * pvBuildPtr (selector sSeg, size_t sOffset)
{
    OsdPrintf (NULL, "pvBuildPtr called, not supported **********\n");
    return (void *) sOffset;
}

void *
PHYStoFP (DWORD phys)
{
    OsdPrintf (NULL, "PHYStoFP called, not supported **********\n");
    return 0;
}

DWORD
FPtoPHYS (void *fp)
{
    OsdPrintf (NULL, "FPtoPHYS called, not supported **********\n");
    return 0;
}

selector
ebds (void)
{
    return 0;
}

// Interrupt handlers

DWORD
wInstallInterruptHandler (
    BYTE                InterruptNumber,
    int                 (* Isr)(void),
    BYTE                InterruptTaskFlag,
    selector            InterruptHandlerDS,
    WORD *              ExceptPtr)
{

    OsdPrintf (NULL, "wInstallInterruptHandler called, not supported **********\n");

    return (DWORD) OsdInstallInterruptHandler (InterruptNumber, Isr, ExceptPtr);

}

int
iRemoveInterruptHandler (DWORD wKey)
{
    OsdPrintf (NULL, "iRemoveInterruptHandler called, not supported **********\n");
    return 0;
}

