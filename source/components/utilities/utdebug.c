
/*
 *  Common stuff that may move later
 */


#pragma pack(1)
#include <bu.h>
#include <acpi.h>
#include "acpiosd.h"


#define WIN_DS_REGISTER     0x0030

char        * Why;
char        WhyBuf [WhyBuf_SIZE];
int         AcpiHook = 0;
int         __AcpiLibInitStatus = 0;
selector    FlatSeg;


/* Debug switch */

int DebugLevel = 0x7FFFFFFF;

int
debug_level (void)
{
    return DebugLevel;
}

void
set_debug_level (int dl)
{
    DebugLevel = dl;
}


void
_Kinc_error (char *a, int b, int c, char * d, int e, int f)
{
    OsdPrintf (NULL, "*** Error %s at line %d, file %s\n", a, c, d); 
    return;
}


void
Kinc_error (char *a, int b)
{
    OsdPrintf (NULL, "*** Error %s\n", a); 
    return;
}


void
_Kinc_info (char *a, int b, int c, char * d, int e, int f)
{
    OsdPrintf (NULL, "*** Info %s at line %d, file %s\n", a, c, d); 
    return;
}

void
Kinc_info (char *a, int b, int c, char * d, int e, int f)
{
    OsdPrintf (NULL, "*** Info %s at line %d, file %s\n", a, c, d); 
    return;
}

void
_Kinc_warning (char *a, int b, int c, char * d, int e, int f)
{
    OsdPrintf (NULL, "*** Warning %s at line %d, file %s\n", a, c, d); 
    return;
}

void
Kinc_warning (char *a, int b)
{
    OsdPrintf (NULL, "*** Warning %s\n", a); 
    return;
}

void
KFatalError (char * a, char * b)
{
    OsdPrintf (NULL, "*** Fatal Error %s: %s\n", a, b);
    return;
}

void
CloseOFT (void)
{
    OsdPrintf (NULL, "CloseOFT called, not supported **********\n");
    return;
}

void
RestoreOFT (void)
{
    OsdPrintf (NULL, "RestoreOFT called, not supported **********\n");
    return;
}

void
DumpBuf (BYTE *Buffer, size_t Count, int Flags, LogHandle LogFile,
    int iLogFlags)
{
    unsigned int    i = 0;
    unsigned int    j;
    unsigned char   BufChar;


    /*
     Nasty little dump buffer routine!
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

        /* Print the ASCII equivalent characters
           But watch out for the bad unprintable ones...
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

void
SetNotSupported (void)
{
    OsdPrintf (NULL, "SetNotSupported called, not supported **********\n");
    return;
}

void 
DisplayTable (void *Header, int DisplayBitFlags)
{
    OsdPrintf (NULL, "DisplayTable called, not supported **********\n");
    return;
}

void
FunctionTrace (char * FileName, char * FunctionName)
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
/*  return NO_LOG_HANDLE; */

    return 1; /* stdout; */
}


/* Pointer stuff, must get rid of this eventually */

size_t
PtrOffset (void *Ptr)
{
    OsdPrintf (NULL, "PtrOffset called, not supported **********\n");
    return (size_t) Ptr;
}

selector
PtrSelector (void *Ptr)
{
    OsdPrintf (NULL, "PtrSelector called, not supported **********\n");
    return (selector) WIN_DS_REGISTER;
}

void *
BuildPtr (selector Seg, size_t Offset)
{
    OsdPrintf (NULL, "BuildPtr called, not supported **********\n");
    return (void *) Offset;
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

/* Interrupt handlers */

DWORD
InstallInterruptHandler (
    BYTE                InterruptNumber,
    int                 (* Isr)(void),
    BYTE                InterruptTaskFlag,
    selector            InterruptHandlerDS,
    WORD *              ExceptPtr)
{

    OsdPrintf (NULL, "InstallInterruptHandler called, not supported **********\n");

    return (DWORD) OsdInstallInterruptHandler (InterruptNumber, Isr, ExceptPtr);

}

int
RemoveInterruptHandler (DWORD wKey)
{
    OsdPrintf (NULL, "RemoveInterruptHandler called, not supported **********\n");
    return 0;
}

