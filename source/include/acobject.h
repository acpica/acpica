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

/*
 * Some necessary typedefs
 */

typedef struct
{
   ptrdiff_t   iOffset;    /* offset to MethodFlags in AML pcode block */
   long        lLength;    /* length of method code including MethodFlags */
} meth;

/* NsHandle is actually an nte *, which is private to acpinmsp.c */

typedef void * NsHandle;


/* 
 * Types associated with names
 * Values correspond to the definition of the ObjectType operator.
 * Must coordinate with aiNsProperties and apcNsTypeNames in acpinmsp.c
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
    BYTE            bValTyp;        /* See NsType in acpinmsp.h for values */

    struct
    {
        BYTE        bValTyp;
        BYTE        bReserved1;
        WORD        wReserved2;
        DWORD       dNumber;
        DWORD       dReserved3;
        void        *pvReserved4;
        void        *pvReserved5;
    } sNumber;

    struct
    {
        BYTE        bValTyp;
        BYTE        bReserved1;
        WORD        wStrLen;        /* # of bytes in string, excluding trailing null */
        DWORD       dReserved2;
        DWORD       dReserved3;
        BYTE        *pbString;      /* points to the string value in the AML stream
                                     * or in allocated space
                                     */
        void        *pvReserved4;
    } sString;

    struct
    {
        BYTE        bValTyp;
        BYTE        bReserved1;
        WORD        wBufLen;        /* # of bytes in buffer */
        DWORD       dReserved2;
        DWORD       dSequence;      /* Sequential count of buffers created */
        BYTE        *pbBuffer;      /* points to the buffer in allocated space */
        void        *pvReserved4;
    } sBuffer;

    struct
    {
        BYTE        bValTyp;
        BYTE        bReserved1;
        WORD        wPkgCount;      /* # of elements in package */
        DWORD       dReserved2;
        DWORD       dReserved3;
        union od    **ppPackage;    /* Addr of an allocated array of pointers
                                     * to the OBJECT_DESCRIPTORs representing
                                     * the elements
                                     */
        union od    **ppNextElement;/* used only while initializing */
    } sPackage;

    struct
    {
        /* Using WORD_BIT instead of BYTE_BIT here because the wDatLen field
         * is larger than a BYTE.  It is possible that some implementations
         * may map this in an unexpected way -- see code and comments in
         * amlexec.c:iPrep*FieldValue() -- but it works properly in IC386
         * and in MS Visual C++
         */
        WORD_BIT    bValTyp     : 8;
        WORD_BIT    wAccess     : 4;
        WORD_BIT    wLockRule   : 1;
        WORD_BIT    wUpdateRule : 2;
        WORD_BIT    wReserved1  : 1;
        WORD_BIT    wDatLen     :13;    /* # of bits in buffer */
        WORD_BIT    wBitOffset  : 3;
        DWORD       dOffset;        /* Byte offset within containing object */
        DWORD       dConSeq;        /* Container's sequence number */
        union od    *pContainer;    /* Containing object (Buffer) */
        void        *pvReserved3;
    } sFieldUnit;

    struct
    {
        BYTE        bValTyp;
        BYTE        bReserved1;
        WORD        wReserved2;
        DWORD       dReserved3;
        DWORD       dReserved4;
        NsHandle    nDevice;
        void        *pvReserved5;
    } sDevice;

    struct
    {
        BYTE        bValTyp;
        BYTE        bReserved1;
        WORD        wSignalCount;
        DWORD       dSemaphore;
        WORD        wLockCount;
        WORD        wThreadId;
        void        *pvReserved4;
        void        *pvReserved5;
    } sEvent;

    struct
    {
        BYTE        bValTyp;
        BYTE        bNumParam;
        WORD        wLength;
        DWORD       dAmlOffset;
        DWORD       dReserved3;
        BYTE        *pbAmlBase;
        void        *pvReserved4;
    } sMethod;

    struct
    {
        BYTE        bValTyp;
        BYTE        bSyncLevel;
        WORD        wReserved2;
        DWORD       dSemaphore;
        WORD        wLockCount;
        WORD        wThreadId;
        void        *pvReserved4;
        void        *pvReserved5;
    } sMutex;

    struct
    {
        BYTE        bValTyp;
        BYTE        bSpaceId;
        WORD        wAdrLenValid;   /* 1 => dAddress & dLength have been set
                                     * 0 => dAddress & dLength have not been set,
                                     *        and should be obtained via sAdrLoc
                                     */
        DWORD       dAddress;
        DWORD       dLength;
        meth        sAdrLoc;        /* Loc of 1st (address) OpCode in AML stream */
    } sRegion;

    struct
    {
        BYTE        bValTyp;
        BYTE        bReserved1;
        WORD        wReserved2;
        DWORD       dReserved3;
        DWORD       dReserved4;
        NsHandle    nPowerResource;
        void        *pvReserved5;
    } sPowerResource;

    struct
    {
        BYTE        bValTyp;
        BYTE        bReserved1;
        WORD        wReserved2;
        DWORD       dReserved3;
        DWORD       dReserved4;
        NsHandle    nProcessor;
        void        *pvReserved5;
    } sProcessor;

    struct
    {
        BYTE        bValTyp;
        BYTE        bReserved1;
        WORD        wReserved2;
        DWORD       dReserved3;
        DWORD       dReserved4;
        NsHandle    nThermalZone;
        void        *pvReserved5;
    } sThermalZone;

    struct
    {
        /* See comments in sFieldUnit re use of WORD_BIT */

        WORD_BIT    bValTyp     : 8;
        WORD_BIT    wAccess     : 4;
        WORD_BIT    wLockRule   : 1;
        WORD_BIT    wUpdateRule : 2;
        WORD_BIT    wReserved1  : 1;
        WORD_BIT    wDatLen     :13;    /* # of bits in buffer */
        WORD_BIT    wBitOffset  : 3;
        DWORD       dOffset;        /* Byte offset within containing object */
        DWORD       dReserved2;
        union od    *pContainer;     /* Containing object */
        void        *pvReserved3;
    } sField;

    struct
    {
        /* See comments in sFieldUnit re use of WORD_BIT */

        WORD_BIT    bValTyp     : 8;
        WORD_BIT    wAccess     : 4;
        WORD_BIT    wLockRule   : 1;
        WORD_BIT    wUpdateRule : 2;
        WORD_BIT    wReserved1  : 1;
        WORD_BIT    wDatLen     :13;    /* # of bits in buffer */
        WORD_BIT    wBitOffset  : 3;
        DWORD       dOffset;        /* Byte offset within containing object */
        DWORD       dBankVal;       /* Value to store into pBankSelect */
        union od    *pContainer;    /* Containing object */
        NsHandle    hBankSelect;    /* Bank select register */
    } sBankField;

    struct
    {
        /* See comments in sFieldUnit re use of WORD_BIT */

        WORD_BIT    bValTyp     : 8;
        WORD_BIT    wAccess     : 4;
        WORD_BIT    wLockRule   : 1;
        WORD_BIT    wUpdateRule : 2;
        WORD_BIT    wReserved1  : 1;
        WORD_BIT    wDatLen     :13;    /* # of bits in buffer */
        WORD_BIT    wBitOffset  : 3;
        DWORD       dIndexVal;      /* Value to store into Index register */
        DWORD       dReserved2;     /* No container pointer needed since the index
                                     * and data register definitions will define
                                     * how to access the respective registers
                                     */
        NsHandle    hIndex;         /* Index register */
        NsHandle    hData;          /* Data register */
    } sIndexField;

    struct
    {
        BYTE        bValTyp;
        BYTE        bOpCode;        /* Arg#, Local#, IndexOp, NameOp,
                                     * ZeroOp, OneOp, OnesOp, Debug1 => DebugOp
                                     */
        WORD        wReserved1;
        DWORD       dReserved2;
        DWORD       dReserved3;
        void        *pvRef;         /* bOpCode  Use of pvRef field
                                     * -------  ----------------------------
                                     * NameOp   NsHandle for referenced name
                                     * IndexOp  OBJECT_DESCRIPTOR **
                                     */
        void        *pvReserved4;
    } sLvalue;

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

