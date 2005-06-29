/*
  __________________________________________________________________________
 |
 |
 |               Copyright (C) Intel Corporation 1994-1996
 |
 | All rights reserved.  No part of this program or publication may be
 | reproduced, transmitted, transcribed, stored in a retrieval system, or
 | translated into any language or computer language, in any form or by any
 | means, electronic, mechanical, magnetic, optical, chemical, manual, or
 | otherwise, without the prior written permission of Intel Corporation.
 |__________________________________________________________________________
 |
 | FILENAME: aml.h - Definitions for AML, as included in "definition blocks"
 | Declarations and definitions contained herein are derived directly from
 | the ACPI specification.
 |__________________________________________________________________________
//
//      Rev 1.0  Feb 26 1997 09:53:22   KBRANNOC
// Initial revision.
 |__________________________________________________________________________

*/

#ifndef __AMLCODE_H__
#define __AMLCODE_H__


/* primary opcodes */

#define NullChar                0x00

#define ZeroOp                  0x00
#define OneOp                   0x01
#define UNASSIGNED              0x02
#define AliasOp                 0x06
#define NameOp                  0x08
#define ByteOp                  0x0a
#define WordOp                  0x0b
#define DWordOp                 0x0c
#define StringOp                0x0d
#define ScopeOp                 0x10
#define BufferOp                0x11
#define PackageOp               0x12
#define MethodOp                0x14
#define DualNamePrefix          0x2e
#define MultiNamePrefixOp       0x2f
#define NameCharSubseq          0x30
#define NameCharFirst           0x41
#define OpPrefix                0x5b
#define RootPrefix              0x5c
#define ParentPrefix            0x5e
#define Local_Op                0x60
#define Local0                  0x60
#define Local1                  0x61
#define Local2                  0x62
#define Local3                  0x63
#define Local4                  0x64
#define Local5                  0x65
#define Local6                  0x66
#define Local7                  0x67
#define Arg_Op                  0x68
#define Arg0                    0x68
#define Arg1                    0x69
#define Arg2                    0x6a
#define Arg3                    0x6b
#define Arg4                    0x6c
#define Arg5                    0x6d
#define Arg6                    0x6e
#define StoreOp                 0x70
#define RefOfOp                 0x71
#define AddOp                   0x72
#define ConcatOp                0x73
#define SubtractOp              0x74
#define IncrementOp             0x75
#define DecrementOp             0x76
#define MultiplyOp              0x77
#define DivideOp                0x78
#define ShiftLeftOp             0x79
#define ShiftRightOp            0x7a
#define BitAndOp                0x7b
#define BitNandOp               0x7c
#define BitOrOp                 0x7d
#define BitNorOp                0x7e
#define BitXorOp                0x7f
#define BitNotOp                0x80
#define FindSetLeftBitOp        0x81
#define FindSetRightBitOp       0x82
#define DerefOfOp               0x83
#define NotifyOp                0x86
#define SizeOfOp                0x87
#define IndexOp                 0x88
#define MatchOp                 0x89
#define DWordFieldOp            0x8a
#define WordFieldOp             0x8b
#define ByteFieldOp             0x8c
#define BitFieldOp              0x8d
#define TypeOp                  0x8e
#define LAndOp                  0x90
#define LOrOp                   0x91
#define LNotOp                  0x92
#define LEqualOp                0x93
#define LGreaterOp              0x94
#define LLessOp                 0x95
#define IfOp                    0xa0
#define ElseOp                  0xa1
#define WhileOp                 0xa2
#define NoopCode                0xa3
#define ReturnOp                0xa4
#define BreakOp                 0xa5
#define BreakPointOp            0xcc
#define OnesOp                  0xff

/* prefixed opcodes */

#define MutexOp                 0x5b01
#define EventOp                 0x5b02
#define ShiftRightBitOp         0x5b10
#define ShiftLeftBitOp          0x5b11
#define CondRefOfOp             0x5b12
#define CreateFieldOp           0x5b13
#define LoadOp                  0x5b20
#define StallOp                 0x5b21
#define SleepOp                 0x5b22
#define AcquireOp               0x5b23
#define SignalOp                0x5b24
#define WaitOp                  0x5b25
#define ResetOp                 0x5b26
#define ReleaseOp               0x5b27
#define FromBCDOp               0x5b28
#define ToBCDOp                 0x5b29
#define UnLoadOp                0x5b2a
#define RevisionOp              0x5b30
#define DebugOp                 0x5b31
#define FatalOp                 0x5b32
#define RegionOp                0x5b80
#define DefFieldOp              0x5b81
#define DeviceOp                0x5b82
#define ProcessorOp             0x5b83
#define PowerResOp              0x5b84
#define ThermalZoneOp           0x5b85
#define IndexFieldOp            0x5b86
#define BankFieldOp             0x5b87

/* Comparison operation codes for MatchOp operator */

typedef enum {
    MTR             = 0,
    MEQ             = 1,
    MLE             = 2,
    MLT             = 3,
    MGE             = 4,
    MGT             = 5
} MatchCompOp;

/* Field Access Types */

#define ACCESS_TYPE_MASK    0x0f
#define ACCESS_TYPE_SHIFT   0

typedef enum {
    AnyAcc          = 0,
    ByteAcc         = 1,
    WordAcc         = 2,
    DWordAcc        = 3,
    BlockAcc        = 4,
    SMBSendRecvAcc  = 5,
    SMBQuickAcc     = 6
} AccessType;

/* Field Lock Rules */

#define LOCK_RULE_MASK      0x10
#define LOCK_RULE_SHIFT 4

typedef enum {
    NoLock          = 0,
    Lock            = 1
} LockRule;

/* Field Update Rules */

#define UPDATE_RULE_MASK    0x060
#define UPDATE_RULE_SHIFT   5

typedef enum {
    Preserve        = 0,
    WriteAsOnes     = 1,
    WriteAsZeros    = 2
} UpdateRule;


/* Region Space ID values */

typedef enum {
    SystemMemory    = 0,
    SystemIO        = 1,
    PCIConfig       = 2,
    EmbeddedControl = 3,
    SMBus           = 4
} RegionSpace;


/* bit fields in MethodFlags byte */

#define METHOD_ARG_COUNT_MASK   7
#define METHOD_ARG_COUNT_SHIFT  0
#define METHOD_SYNCHRONIZED     8


#ifndef DEFINE_GLOBALS
extern UINT8    Aml[256];
extern UINT16   Pfx[256];
extern char     *ShortOps[256];
extern char     *LongOps[256];
extern char     *RegionTypes[5];
extern char     *MatchOps[];
extern char     *AccessTypes[];
extern char     *UpdateRules[];
#else

/* primary decoder */

UINT8 Aml[256] = {
    /*      x0                  x1                  x2                  x3          */
    /*      x4                  x5                  x6                  x7          */
    /*      x8                  x9                  xa                  xb          */
    /*      xc                  xd                  xe                  xf          */
/* 0x */    ZeroOp,             OneOp,              UNASSIGNED,         UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         AliasOp,            UNASSIGNED,
            NameOp,             UNASSIGNED,         ByteOp,             WordOp,
            DWordOp,            StringOp,           UNASSIGNED,         UNASSIGNED,
/* 1x */    ScopeOp,            BufferOp,           PackageOp,          UNASSIGNED,
            MethodOp,           UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
/* 2x */    UNASSIGNED,         UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         DualNamePrefix,     MultiNamePrefixOp,
/* 3x */    NameCharSubseq,     NameCharSubseq,     NameCharSubseq,     NameCharSubseq,
            NameCharSubseq,     NameCharSubseq,     NameCharSubseq,     NameCharSubseq,
            NameCharSubseq,     NameCharSubseq,     UNASSIGNED,         UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
/* 4x */    UNASSIGNED,         NameCharFirst,      NameCharFirst,      NameCharFirst,
            NameCharFirst,      NameCharFirst,      NameCharFirst,      NameCharFirst,
            NameCharFirst,      NameCharFirst,      NameCharFirst,      NameCharFirst,
            NameCharFirst,      NameCharFirst,      NameCharFirst,      NameCharFirst,
/* 5x */    NameCharFirst,      NameCharFirst,      NameCharFirst,      NameCharFirst,
            NameCharFirst,      NameCharFirst,      NameCharFirst,      NameCharFirst,
            NameCharFirst,      NameCharFirst,      NameCharFirst,      OpPrefix,
            RootPrefix,         UNASSIGNED,         ParentPrefix,       NameCharFirst,
/* 6x */    Local_Op,           Local_Op,           Local_Op,           Local_Op,
            Local_Op,           Local_Op,           Local_Op,           Local_Op,
            Arg_Op,             Arg_Op,             Arg_Op,             Arg_Op,
            Arg_Op,             Arg_Op,             Arg_Op,             UNASSIGNED,
/* 7x */    StoreOp,            RefOfOp,            AddOp,              ConcatOp,
            SubtractOp,         IncrementOp,        DecrementOp,        MultiplyOp,
            DivideOp,           ShiftLeftOp,        ShiftRightOp,       BitAndOp,
            BitNandOp,          BitOrOp,            BitNorOp,           BitXorOp,
/* 8x */    BitNotOp,           FindSetLeftBitOp,   FindSetRightBitOp,  DerefOfOp,
            UNASSIGNED,         UNASSIGNED,         NotifyOp,           SizeOfOp,
            IndexOp,            MatchOp,            DWordFieldOp,       WordFieldOp,
            ByteFieldOp,        BitFieldOp,         TypeOp,             UNASSIGNED,
/* 9x */    LAndOp,             LOrOp,              LNotOp,             LEqualOp,
            LGreaterOp,         LLessOp,            UNASSIGNED,         UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
/* ax */    IfOp,               ElseOp,             WhileOp,            NoopCode,
            ReturnOp,           BreakOp,            UNASSIGNED,         UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
/* bx */    UNASSIGNED,         UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
/* cx */    UNASSIGNED,         UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
            BreakPointOp,       UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
/* dx */    UNASSIGNED,         UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
/* ex */    UNASSIGNED,         UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
/* fx */    UNASSIGNED,         UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,         UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,         OnesOp
};

/* prefixed decoder */

UINT16 Pfx[256] = {
    /*      x0                  x1                  x2                  x3          */
    /*      x4                  x5                  x6                  x7          */
    /*      x8                  x9                  xa                  xb          */
    /*      xc                  xd                  xe                  xf          */
/* 0x */    UNASSIGNED,         MutexOp,            EventOp,           UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
/* 1x */    ShiftRightBitOp,    ShiftLeftBitOp,     CondRefOfOp,       CreateFieldOp,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
/* 2x */    LoadOp,             StallOp,            SleepOp,           AcquireOp,
            SignalOp,           WaitOp,             ResetOp,           ReleaseOp,
            FromBCDOp,          ToBCDOp,            UnLoadOp,          UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
/* 3x */    RevisionOp,         DebugOp,            FatalOp,           UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
/* 4x */    UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
/* 5x */    UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
/* 6x */    UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
/* 7x */    UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
/* 8x */    RegionOp,           DefFieldOp,         DeviceOp,          ProcessorOp,
            PowerResOp,         ThermalZoneOp,      IndexFieldOp,      BankFieldOp,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
/* 9x */    UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
/* ax */    UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
/* bx */    UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
/* cx */    UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
/* dx */    UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
/* ex */    UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
/* fx */    UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED,
            UNASSIGNED,         UNASSIGNED,         UNASSIGNED,        UNASSIGNED
};

/* primary op names */

char *ShortOps[256] = {
    /*      x0                  x1                  x2                  x3          */
    /*      x4                  x5                  x6                  x7          */
    /*      x8                  x9                  xa                  xb          */
    /*      xc                  xd                  xe                  xf          */
/* 0x */    "ZeroOp",           "OneOp",            "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "AliasOp",          "*ERROR*",
            "NameOp",           "*ERROR*",          "ByteOp",           "WordOp",
            "DWordOp",          "StringOp",         "*ERROR*",          "*ERROR*",
/* 1x */    "ScopeOp",          "BufferOp",         "PackageOp",        "*ERROR*",
            "MethodOp",         "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
/* 2x */    "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "DualNamePrefix",   "MultiNamePrefixOp",
/* 3x */    "*NAME*",           "*NAME*",           "*NAME*",           "*NAME*",
            "*NAME*",           "*NAME*",           "*NAME*",           "*NAME*",
            "*NAME*",           "*NAME*",           "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
/* 4x */    "*ERROR*",          "*NAME*",           "*NAME*",           "*NAME*",
            "*NAME*",           "*NAME*",           "*NAME*",           "*NAME*",
            "*NAME*",           "*NAME*",           "*NAME*",           "*NAME*",
            "*NAME*",           "*NAME*",           "*NAME*",           "*NAME*",
/* 5x */    "*NAME*",           "*NAME*",           "*NAME*",           "*NAME*",
            "*NAME*",           "*NAME*",           "*NAME*",           "*NAME*",
            "*NAME*",           "*NAME*",           "*NAME*",           "*PREFIX*",
            "RootPrefix",       "*ERROR*",          "ParentPrefix",     "*NAME*",
/* 6x */    "Lcl0",             "Lcl1",             "Lcl2",             "Lcl3",
            "Lcl4",             "Lcl5",             "Lcl6",             "Lcl7",
            "Arg0",             "Arg1",             "Arg2",             "Arg3",
            "Arg4",             "Arg5",             "Arg6",             "*ERROR*",
/* 7x */    "StoreOp",          "RefOfOp",          "AddOp",            "ConcatOp",
            "SubtractOp",       "IncrementOp",      "DecrementOp",      "MultiplyOp",
            "DivideOp",         "ShiftLeftOp",      "ShiftRightOp",     "AndOp",
            "NandOp",           "OrOp",             "NorOp",            "XorOp",
/* 8x */    "NotOp",            "FindSetLeftBitOp", "FindSetRightBitOp",    "DerefOfOp",
            "*ERROR*",          "*ERROR*",          "NotifyOp",         "SizeOfOp",
            "IndexOp",          "MatchOp",          "DWordFieldOp",     "WordFieldOp",
            "ByteFieldOp",      "BitFieldOp",       "TypeOp",           "*ERROR*",
/* 9x */    "LAndOp",           "LOrOp",            "LNotOp",           "LEqualOp",
            "LGreaterOp",       "LLessOp",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
/* ax */    "IfOp",             "ElseOp",           "WhileOp",          "NoOp",
            "ReturnOp",         "BreakOp",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
/* bx */    "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
/* cx */    "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "BreakPointOp",     "*ERROR*",          "*ERROR*",          "*ERROR*",
/* dx */    "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
/* ex */    "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
/* fx */    "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "OnesOp"
};

/* prefixed op names */

char *LongOps[256] = {
    /*      x0                  x1                      x2                      x3          */
    /*      x4                  x5                      x6                      x7          */
    /*      x8                  x9                      xa                      xb          */
    /*      xc                  xd                      xe                      xf          */
/* 0x */    "*ERROR*",          "MutexOp",          "EventOp",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
/* 1x */    "ShiftRightBitOp", "ShiftLeftBitOp",    "CondRefOfOp",      "CreateFieldOp",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
/* 2x */    "LoadOp",           "StallOp",          "SleepOp",          "AcquireOp",
            "SignalOp",         "WaitOp",           "ResetOp",          "ReleaseOp",
            "FromBCDOp",        "ToBCDOp",           "UnLoadOp",        "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
/* 3x */    "RevisionOp",       "DebugOp",          "FatalOp",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
/* 4x */    "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
/* 5x */    "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
/* 6x */    "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
/* 7x */    "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
/* 8x */    "OpRegionOp",       "FieldOp",          "DeviceOp",     "ProcessorOp",
            "PowerResOp",       "ThermalZoneOp", "IndexFieldOp",    "BankFieldOp",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
/* 9x */    "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
/* ax */    "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
/* bx */    "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
/* cx */    "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
/* dx */    "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
/* ex */    "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
/* fx */    "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*ERROR*",
            "*ERROR*",          "*ERROR*",          "*ERROR*",          "*RESERVED*"
};

char *RegionTypes[5] = {   /* Region type decoding */
    "SystemMemory",
    "SystemIO",
    "PCIConfig",
    "EmbeddedControl",
    "SMBus"
};

char *MatchOps[] = { "Error", "MTR", "MEQ", "MLE", "MLT", "MGE", "MGT" };

char *AccessTypes[] = {   /* Access type decoding */
    "AnyAcc",
    "ByteAcc",
    "WordAcc",
    "DWordAcc",
    "BlockAcc",
    "SMBSendRecvAcc",
    "SMBQuickAcc"
};

char *UpdateRules[] = {   /* Update rule decoding */
    "Preserve",
    "WriteAsOnes",
    "WriteAsZeros"
};

#endif /* DEFINE_GLOBALS */

#endif /* __AMLCODE_H__ */
