/*
 * __________________________________________________________________________
 *
 *
 *           Copyright (C) Intel Corporation 1994-1996
 *
 * All rights reserved.  No part of this program or publication may be
 * reproduced, transmitted, transcribed, stored in a retrieval system, or
 * translated into any language or computer language, in any form or by any
 * means, electronic, mechanical, magnetic, optical, chemical, manual, or
 * otherwise, without the prior written permission of Intel Corporation.
 *__________________________________________________________________________
 *
 * FILENAME: acpiobj.h - Definition of OBJECT_DESCRIPTOR
 *__________________________________________________________________________
 *
 *
 *__________________________________________________________________________
 */

#ifndef _ACPIOBJ_H
#define _ACPIOBJ_H

#include <stddef.h>
#include "datatypes.h"

/*
 * Some necessary typedefs
 */

typedef struct
{
   ptrdiff_t   Offset;      /* offset to MethodFlags in AML pcode block */
   UINT32      Length;      /* length of method code including MethodFlags */
} meth;

/* NsHandle is actually an nte *, which is private to acpinmsp.c */

typedef void * NsHandle;


/* 
 * Types associated with names
 * Values correspond to the definition of the ObjectType operator.
 * Must coordinate with NsProperties and NsTypeNames in acpinmsp.c
 * The NsType type is also used in OBJECT_DESCRIPTOR defined in amlpriv.h
 */

typedef enum {
   Any              =  0,
   Number           =  1, /* Byte/Word/Dword/Zero/One/Ones */
   String           =  2,
   Buffer           =  3,
   Package          =  4, /* ByteConst, multiple DataTerm/Constant/SuperName */
   FieldUnit        =  5,
   Device           =  6, /* Name, multiple NamedObject */
   Event            =  7,
   Method           =  8, /* Name, ByteConst, multiple Code */
   Mutex            =  9,
   Region           = 10,
   Power            = 11, /* Name,ByteConst,WordConst,multi NamedObject */
   Processor        = 12, /* Name,ByteConst,DWordConst,ByteConst,multi NmO */
   Thermal          = 13, /* Name, multiple NamedObject */
   Alias            = 14,

/* 
 * The remaining values do not relate to the ObjectType operator and are
 * used for various internal purposes.  A gap is provided in case more
 * official ObjectType's are added in the future.  Also, values exceeding
 * the largest ObjectType need to not overlap with defined AML opcodes.
 */
   DefField         = 25,
   BankField        = 26,
   IndexField       = 27,
   DefFieldDefn     = 28, /* Name, ByteConst, multiple FieldElement */
   BankFieldDefn    = 29, /* 2 Name,DWordConst,ByteConst,multi FieldElement */
   IndexFieldDefn   = 30, /* 2 Name, ByteConst, multiple FieldElement */
   If               = 31, /* OpCode, multiple Code */
   Else             = 32, /* multiple Code */
   While            = 33, /* OpCode, multiple Code */
   Scope            = 34, /* Name, multiple NamedObject */
   DefAny           = 35, /* type is Any, suppress search of enclosing scopes */
   Lvalue           = 36  /* Arg#, Local#, Name, Debug; used only in descriptors */
} NsType;



/* 
 * All variants of the OBJECT_DESCRIPTOR are defined with the same
 * sequence of field types, with fields that are not used in a particular
 * variant being named "Reserved".  This is not strictly necessary, but
 * may in some circumstances simplify understanding if these structures
 * need to be displayed in a debugger having limited (or no) support for
 * union types.  It also simplifies some debug code in vNsDumpTable() which
 * dumps multi-level values: fetching sBuffer.pbBuffer suffices to pick up
 * the value or next level for any of several types.
 */


typedef union od                /* OBJECT DESCRIPTOR */
{
    UINT8           ValType;        /* See NsType in acpinmsp.h for values */

    struct
    {
        UINT8       ValType;
        UINT8       Reserved1;
        UINT16      Reserved2;
        UINT32      Number;
        UINT32      Reserved3;
        void        *Reserved4;
        void        *Reserved5;
    } Number;

    struct
    {
        UINT8       ValType;
        UINT8       Reserved1;
        UINT16      StrLen;         /* # of bytes in string, excluding trailing null */
        UINT32      Reserved2;
        UINT32      Reserved3;
        UINT8       *String;        /* points to the string value in the AML stream
                                     * or in allocated space
                                     */
        void        *Reserved4;
    } String;

    struct
    {
        UINT8       ValType;
        UINT8       Reserved1;
        UINT16      BufLen;         /* # of bytes in buffer */
        UINT32      Reserved2;
        UINT32      Sequence;       /* Sequential count of buffers created */
        UINT8       *Buffer;        /* points to the buffer in allocated space */
        void        *Reserved4;
    } Buffer;

    struct
    {
        UINT8       ValType;
        UINT8       Reserved1;
        UINT16      PkgCount;       /* # of elements in package */
        UINT32      Reserved2;
        UINT32      Reserved3;
        union od    **PackageElems; /* Addr of an allocated array of pointers
                                     * to the OBJECT_DESCRIPTORs representing
                                     * the elements
                                     */
        union od    **NextElement;  /* used only while initializing */
    } Package;

    struct
    {
        /* Using WORD_BIT instead of BYTE_BIT here because the wDatLen field
         * is larger than a UINT8.  It is possible that some implementations
         * may map this in an unexpected way -- see code and comments in
         * amlexec.c:iPrep*FieldValue() -- but it works properly in IC386
         * and in MS Visual C++
         */
        UINT16_BIT  ValType     : 8;
        UINT16_BIT  Access      : 4;
        UINT16_BIT  LockRule    : 1;
        UINT16_BIT  UpdateRule  : 2;
        UINT16_BIT  Reserved1   : 1;
        UINT16_BIT  DatLen      :13;    /* # of bits in buffer */
        UINT16_BIT  BitOffset   : 3;
        UINT32      Offset;         /* Byte offset within containing object */
        UINT32      ConSeq;         /* Container's sequence number */
        union od    *Container;     /* Containing object (Buffer) */
        void        *Reserved3;
    } FieldUnit;

    struct
    {
        UINT8       ValType;
        UINT8       Reserved1;
        UINT16      Reserved2;
        UINT32      Reserved3;
        UINT32      Reserved4;
        NsHandle    Device;
        void        *Reserved5;
    } Device;

    struct
    {
        UINT8       ValType;
        UINT8       Reserved1;
        UINT16      SignalCount;
        UINT32      Semaphore;
        UINT16      LockCount;
        UINT16      ThreadId;
        void        *Reserved4;
        void        *Reserved5;
    } Event;

    struct
    {
        UINT8       ValType;
        UINT8       NumParam;
        UINT16      Length;
        UINT32      AmlOffset;
        UINT32      Reserved3;
        UINT8       *AmlBase;
        void        *Reserved4;
    } Method;

    struct
    {
        UINT8       ValType;
        UINT8       SyncLevel;
        UINT16      Reserved2;
        UINT32      Semaphore;
        UINT16      LockCount;
        UINT16      ThreadId;
        void        *Reserved4;
        void        *Reserved5;
    } Mutex;

    struct
    {
        UINT8       ValType;
        UINT8       SpaceId;
        UINT16      AdrLenValid;    /* 1 => dAddress & dLength have been set
                                     * 0 => dAddress & dLength have not been set,
                                     *        and should be obtained via sAdrLoc
                                     */
        UINT32      Address;
        UINT32      Length;
        meth        AdrLoc;         /* Loc of 1st (address) OpCode in AML stream */
    } Region;

    struct
    {
        UINT8       ValType;
        UINT8       Reserved1;
        UINT16      Reserved2;
        UINT32      Reserved3;
        UINT32      Reserved4;
        NsHandle    PowerResource;
        void        *Reserved5;
    } PowerResource;

    struct
    {
        UINT8       ValType;
        UINT8       Reserved1;
        UINT16      Reserved2;
        UINT32      Reserved3;
        UINT32      Reserved4;
        NsHandle    Processor;
        void        *Reserved5;
    } Processor;

    struct
    {
        UINT8       ValType;
        UINT8       Reserved1;
        UINT16      Reserved2;
        UINT32      Reserved3;
        UINT32      Reserved4;
        NsHandle    ThermalZone;
        void        *Reserved5;
    } ThermalZone;

    struct
    {
        /* See comments in sFieldUnit re use of WORD_BIT */

        UINT16_BIT  ValType     : 8;
        UINT16_BIT  Access      : 4;
        UINT16_BIT  LockRule    : 1;
        UINT16_BIT  UpdateRule  : 2;
        UINT16_BIT  Reserved1   : 1;
        UINT16_BIT  DatLen      :13;    /* # of bits in buffer */
        UINT16_BIT  BitOffset   : 3;
        UINT32      Offset;         /* Byte offset within containing object */
        UINT32      Reserved2;
        union od    *Container;     /* Containing object */
        void        *Reserved3;
    } Field;

    struct
    {
        /* See comments in sFieldUnit re use of WORD_BIT */

        UINT16_BIT  ValType     : 8;
        UINT16_BIT  Access      : 4;
        UINT16_BIT  LockRule    : 1;
        UINT16_BIT  UpdateRule  : 2;
        UINT16_BIT  Reserved1   : 1;
        UINT16_BIT  DatLen      :13;    /* # of bits in buffer */
        UINT16_BIT  BitOffset   : 3;
        UINT32      Offset;         /* Byte offset within containing object */
        UINT32      BankVal;        /* Value to store into pBankSelect */
        union od    *Container;     /* Containing object */
        NsHandle    BankSelect;     /* Bank select register */
    } BankField;

    struct
    {
        /* See comments in sFieldUnit re use of WORD_BIT */

        UINT16_BIT  ValType     : 8;
        UINT16_BIT  Access      : 4;
        UINT16_BIT  LockRule    : 1;
        UINT16_BIT  UpdateRule  : 2;
        UINT16_BIT  Reserved1   : 1;
        UINT16_BIT  DatLen      :13;    /* # of bits in buffer */
        UINT16_BIT  BitOffset   : 3;
        UINT32      IndexVal;       /* Value to store into Index register */
        UINT32      Reserved2;      /* No container pointer needed since the index
                                     * and data register definitions will define
                                     * how to access the respective registers
                                     */
        NsHandle    Index;          /* Index register */
        NsHandle    Data;           /* Data register */
    } IndexField;

    struct
    {
        UINT8       ValType;
        UINT8       OpCode;         /* Arg#, Local#, IndexOp, NameOp,
                                     * ZeroOp, OneOp, OnesOp, Debug1 => DebugOp
                                     */
        UINT16      Reserved1;
        UINT32      Reserved2;
        UINT32      Reserved3;
        void        *Ref;           /* bOpCode  Use of pvRef field
                                     * -------  ----------------------------
                                     * NameOp   NsHandle for referenced name
                                     * IndexOp  OBJECT_DESCRIPTOR **
                                     */
        void        *Reserved4;
    } Lvalue;

} OBJECT_DESCRIPTOR;


/*
 * This appears to be obsolete!!
 */

/* 
 * The sLvalue case of OBJECT_DESCRIPTOR includes a one-byte field which
 * contains an AML opcode identifying the type of lvalue.  Debug1 is used
 * in this field as a stand-in for the (two-byte) AML encoding of DebugOp.
 */

#define Debug1 0x31



#endif

