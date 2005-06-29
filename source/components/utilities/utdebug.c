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
 |__________________________________________________________________________

*/

#define __EXCOMMON_C__

#include <acpi.h>
#include <acpiobj.h>
#include <interpreter.h>
#include <stdarg.h>


#define _THIS_MODULE        "excommon.c"
#define _COMPONENT          MISCELLANEOUS

#define WIN_DS_REGISTER     0x0030

/* Globals */

char        * Why;
char        WhyBuf [WHYBUF_SIZE];
INT32       AcpiHook = 0;
INT32       __AcpiLibInitStatus = 0;


/* Debug switch - level mask */

#ifdef _DEBUG
INT32 DebugLevel = TRACE_ALL | ACPI_ALL;
#else
INT32 DebugLevel = ACPI_ALL;
#endif


/* Debug switch - layer mask */

INT32 DebugLayer = ALL_COMPONENTS;

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
 * FUNCTION:    DumpObjectDescriptor
 *
 * DESCRIPTION: Dumps the members of the object descriptor given.
 *
 ****************************************************************************/
void
DumpObjectDescriptor (OBJECT_DESCRIPTOR *Object)
{
	
	FUNCTION_TRACE ("DumpObjectDescriptor");

		
	switch (Object->ValType)
	{
	case Number:

		DEBUG_PRINT (ACPI_INFO, ("%20s : %s\n", "ValType", "Number"));
        DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved1", Object->Number.Reserved1));
        DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved2", Object->Number.Reserved2));
        DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Number", Object->Number.Number));
        DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved3", Object->Number.Reserved3));
        DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved4", Object->Number.Reserved4));
        DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved5", Object->Number.Reserved5));
		break;
    
	case String:

	    DEBUG_PRINT (ACPI_INFO, ("%20s : %s\n", "ValType", "String"));
        DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved1", Object->String.Reserved1));
        DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "StrLen", Object->String.StrLen));
        DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved2", Object->String.Reserved2));
        DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved3", Object->String.Reserved3));
        DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "String", Object->String.String));
        DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved4", Object->String.Reserved4));
		break;

	case Buffer:

		DEBUG_PRINT (ACPI_INFO, ("%20s : %s\n", "ValType", "Buffer"));
        DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved1", Object->Buffer.Reserved1));
		DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "BufLen", Object->Buffer.BufLen));
        DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved2", Object->Buffer.Reserved2));
        DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Sequence", Object->Buffer.Sequence));
        DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Buffer", Object->Buffer.Buffer));
        DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved4", Object->Buffer.Reserved4));
		break;
        
        
	case Package:

		DEBUG_PRINT (ACPI_INFO, ("%20s : %s\n", "ValType", "Package"));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved1", Object->Package.Reserved1));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "PkgCount", Object->Package.PkgCount));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved2", Object->Package.Reserved2));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved3", Object->Package.Reserved3));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "PackageElems", Object->Package.PackageElems));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "NextElement", Object->Package.NextElement));
		break;
        
	case FieldUnit:

		DEBUG_PRINT (ACPI_INFO, ("%20s : %s\n", "ValType", "FieldUnit"));
		DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Access", Object->FieldUnit.Access));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "LockRule", Object->FieldUnit.LockRule));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "UpdateRule", Object->FieldUnit.UpdateRule));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved1", Object->FieldUnit.Reserved1));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "DatLen", Object->FieldUnit.DatLen));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "BitOffset", Object->FieldUnit.BitOffset));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Offset", Object->FieldUnit.Offset));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "ConSeq", Object->FieldUnit.ConSeq));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Container", Object->FieldUnit.Container));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved3", Object->FieldUnit.Reserved3));
	    break;
        
	case Device:

		DEBUG_PRINT (ACPI_INFO, ("%20s : %s\n", "ValType", "Device"));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved1", Object->Device.Reserved1));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved2", Object->Device.Reserved2));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved3", Object->Device.Reserved3));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved4", Object->Device.Reserved4));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Device", Object->Device.Device));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved5", Object->Device.Reserved5));
        break;

	case Event:

		DEBUG_PRINT (ACPI_INFO, ("%20s : %s\n", "ValType", "Event"));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved1", Object->Event.Reserved1));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "SignalCount", Object->Event.SignalCount));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Semaphore", Object->Event.Semaphore));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "LockCount", Object->Event.LockCount));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "ThreadId", Object->Event.ThreadId));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved4", Object->Event.Reserved4));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved5", Object->Event.Reserved5));
	    break;

	case Method:

		DEBUG_PRINT (ACPI_INFO, ("%20s : %s\n", "ValType", "Method"));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "NumParam", Object->Method.NumParam));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Length", Object->Method.Length));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "AmlOffset", Object->Method.AmlOffset));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved3", Object->Method.Reserved3));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "AmlBase", Object->Method.AmlBase));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved4", Object->Method.Reserved4));
	    break;
	
	case Mutex:

		DEBUG_PRINT (ACPI_INFO, ("%20s : %s\n", "ValType", "Mutex"));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "SyncLevel", Object->Mutex.SyncLevel));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved2", Object->Mutex.Reserved2));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Semaphore", Object->Mutex.Semaphore));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "LockCount", Object->Mutex.LockCount));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "ThreadId", Object->Mutex.ThreadId));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved4", Object->Mutex.Reserved4));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved5", Object->Mutex.Reserved5));
	    break;

	case Region:

		DEBUG_PRINT (ACPI_INFO, ("%20s : %s\n", "ValType", "Region"));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "SpaceId", Object->Region.SpaceId));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "AdrLenValid", Object->Region.AdrLenValid));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Address", Object->Region.Address));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Length", Object->Region.Length));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "AdrLoc", Object->Region.AdrLoc));
	    break;

	case Power:

		DEBUG_PRINT (ACPI_INFO, ("%20s : %s\n", "ValType", "PowerResource"));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved1", Object->PowerResource.Reserved1));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved2", Object->PowerResource.Reserved2));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved3", Object->PowerResource.Reserved3));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved4", Object->PowerResource.Reserved4));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "PowerResource", Object->PowerResource.PowerResource));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved5", Object->PowerResource.Reserved5));
	    break;

	case Processor:

		DEBUG_PRINT (ACPI_INFO, ("%20s : %s\n", "ValType", "Processor"));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved1", Object->Processor.Reserved1));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved2", Object->Processor.Reserved2));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved3", Object->Processor.Reserved3));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved4", Object->Processor.Reserved4));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Processor", Object->Processor.Processor));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved5", Object->Processor.Reserved5));
	    break;

	case Thermal:

		DEBUG_PRINT (ACPI_INFO, ("%20s : %s\n", "ValType", "ThermalZone"));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved1", Object->ThermalZone.Reserved1));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved2", Object->ThermalZone.Reserved2));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved3", Object->ThermalZone.Reserved3));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved4", Object->ThermalZone.Reserved4));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "ThermalZone", Object->ThermalZone.ThermalZone));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved5", Object->ThermalZone.Reserved5));
	    break;

	case BankField:

		DEBUG_PRINT (ACPI_INFO, ("%20s : %s\n", "ValType", "BankField"));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Access", Object->BankField.Access));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "LockRule", Object->BankField.LockRule));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "UpdateRule", Object->BankField.UpdateRule));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved1", Object->BankField.Reserved1));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "DatLen", Object->BankField.DatLen));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "BitOffset", Object->BankField.BitOffset));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Offset", Object->BankField.Offset));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "BankVal", Object->BankField.BankVal));
		DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Container", Object->BankField.Container));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "BankSelect", Object->BankField.BankSelect));
	    break;

	case IndexField:

		DEBUG_PRINT (ACPI_INFO, ("%20s : %s\n", "ValType", "IndexField"));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Access", Object->IndexField.Access));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "LockRule", Object->IndexField.LockRule));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "UpdateRule", Object->IndexField.UpdateRule));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved1", Object->IndexField.Reserved1));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "DatLen", Object->IndexField.DatLen));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "BitOffset", Object->IndexField.BitOffset));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "IndexVal", Object->IndexField.IndexVal));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved2", Object->IndexField.Reserved2));
		DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Index", Object->IndexField.Index));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Data", Object->IndexField.Data));
	    break;

	case Lvalue:

		DEBUG_PRINT (ACPI_INFO, ("%20s : %s\n", "ValType", "Lvalue"));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "OpCode", Object->Lvalue.OpCode));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved1", Object->Lvalue.Reserved1));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved2", Object->Lvalue.Reserved2));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved3", Object->Lvalue.Reserved3));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Ref", Object->Lvalue.Ref));
	    DEBUG_PRINT (ACPI_INFO, ("%20s : %x\n", "Reserved4", Object->Lvalue.Reserved4));
		break;
	
	case Alias:
	case DefField:
	case DefFieldDefn:
	case BankFieldDefn:
	case IndexFieldDefn:
	case If:
	case Else:
	case While:
	case Scope:
	case DefAny:
	default:

		DEBUG_PRINT (ACPI_ERROR, ("*** No definition for this structure! ***\n"));
		break;


	}

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
_ReportWarning (char *ModuleName, INT32 LineNumber, INT32 ComponentId, ST_KEY_DESC_TABLE *KdtEntry)
{

    DebugPrint (ModuleName, LineNumber, ComponentId, ACPI_WARN, 
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
_ReportSuccess (char *ModuleName, INT32 LineNumber, INT32 ComponentId, ST_KEY_DESC_TABLE *KdtEntry)
{

    DebugPrint (ModuleName, LineNumber, ComponentId, ACPI_SUCCESS, 
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
_ReportInfo (char *ModuleName, INT32 LineNumber, INT32 ComponentId, ST_KEY_DESC_TABLE *KdtEntry)
{

    DebugPrint (ModuleName, LineNumber, ComponentId, ACPI_INFO, 
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
 * FUNCTION:    DumpBuf
 *
 * RETURN:      none
 *
 * DESCRIPTION: Generic dump buffer in hex and ascii.
 *
 ****************************************************************************/

void
DumpBuf (char *Buffer, UINT32 Count, INT32 Flags, INT32 ComponentId)
{
    UINT32      i = 0;
    UINT32      j;
    UINT8       BufChar;


    /* Only dump the buffer if tracing is enabled */

    if (!((TRACE_TABLES & DebugLevel) && (ComponentId & DebugLayer)))
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


            /* Make sure that the char doesn't get sign-extended! */

            BufChar = Buffer[i + j];
            OsdPrintf (NULL, "%02X ", BufChar);
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





