
/*
 *  Common stuff that may move later
 */


#pragma pack(1)
#include <bu.h>
#include <acpi.h>
#include "acpiosd.h"


#define WIN_DS_REGISTER     0x0030

/* Globals */

char        * Why;
char        WhyBuf [WHYBUF_SIZE];
INT32       AcpiHook = 0;
INT32       __AcpiLibInitStatus = 0;


/* Debug switch */

INT32 DebugLevel = 0x7FFFFFFF;


INT32
debug_level (void)
{

    return DebugLevel;
}

void
set_debug_level (INT32 dl)
{

    DebugLevel = dl;
}


void
_Kinc_error (char *a, INT32 b, INT32 c, char * d, INT32 e, INT32 f)
{

    OsdPrintf (NULL, "*** Error %s at line %d, file %s\n", a, c, d); 
    return;
}


void
Kinc_error (char *a, INT32 b)
{

    OsdPrintf (NULL, "*** Error %s\n", a); 
    return;
}


void
_Kinc_info (char *a, INT32 b, INT32 c, char * d, INT32 e, INT32 f)
{

    OsdPrintf (NULL, "*** Info %s at line %d, file %s\n", a, c, d); 
    return;
}

void
Kinc_info (char *a, INT32 b, INT32 c, char * d, INT32 e, INT32 f)
{

    OsdPrintf (NULL, "*** Info %s at line %d, file %s\n", a, c, d); 
    return;
}

void
_Kinc_warning (char *a, INT32 b, INT32 c, char * d, INT32 e, INT32 f)
{

    OsdPrintf (NULL, "*** Warning %s at line %d, file %s\n", a, c, d); 
    return;
}

void
Kinc_warning (char *a, INT32 b)
{

    OsdPrintf (NULL, "*** Warning %s\n", a); 
    return;
}

void
KFatalError (char * a, char * b, ...)
{
    /* Optional parameters (...) not implemented */


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
SetNotSupported (void)
{
    OsdPrintf (NULL, "SetNotSupported called, not supported **********\n");
    return;
}

void 
DisplayTable (void *Header, INT32 DisplayBitFlags)
{
    OsdPrintf (NULL, "DisplayTable called, not supported **********\n");
    return;
}

void
FunctionTrace (char * FileName, char * FunctionName)
{

    OsdPrintf (NULL, "Enter Module: %10s, Function: %s\n", FileName, FunctionName);
}


LogHandle
GetMasterLogHandle (void)
{

/*  return NO_LOG_HANDLE; */

    return 1; /* stdout; TEMPORARY!!! */
}


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


void
DumpBuf (UINT8 *Buffer, size_t Count, INT32 Flags, LogHandle LogFile,
            INT32 iLogFlags)
{
    UINT32      i = 0;
    UINT32      j;
    UINT8       BufChar;


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


