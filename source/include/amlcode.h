
/******************************************************************************
 * 
 * Name: amlcode.h - Definitions for AML, as included in "definition blocks"
 *                   Declarations and definitions contained herein are derived 
 *                   directly from the ACPI specification.
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


#ifndef __AMLCODE_H__
#define __AMLCODE_H__


/* primary opcodes */

#define AML_NullChar                0x00

#define AML_ZeroOp                  0x00
#define AML_OneOp                   0x01
#define AML_UNASSIGNED              0x02
#define AML_AliasOp                 0x06
#define AML_NameOp                  0x08
#define AML_ByteOp                  0x0a
#define AML_WordOp                  0x0b
#define AML_DWordOp                 0x0c
#define AML_StringOp                0x0d
#define AML_ScopeOp                 0x10
#define AML_BufferOp                0x11
#define AML_PackageOp               0x12
#define AML_MethodOp                0x14
#define AML_DualNamePrefix          0x2e
#define AML_MultiNamePrefixOp       0x2f
#define AML_NameCharSubseq          0x30
#define AML_NameCharFirst           0x41
#define AML_OpPrefix                0x5b
#define AML_RootPrefix              0x5c
#define AML_ParentPrefix            0x5e
#define AML_Local_Op                0x60
#define AML_Local0                  0x60
#define AML_Local1                  0x61
#define AML_Local2                  0x62
#define AML_Local3                  0x63
#define AML_Local4                  0x64
#define AML_Local5                  0x65
#define AML_Local6                  0x66
#define AML_Local7                  0x67
#define AML_Arg_Op                  0x68
#define AML_Arg0                    0x68
#define AML_Arg1                    0x69
#define AML_Arg2                    0x6a
#define AML_Arg3                    0x6b
#define AML_Arg4                    0x6c
#define AML_Arg5                    0x6d
#define AML_Arg6                    0x6e
#define AML_StoreOp                 0x70
#define AML_RefOfOp                 0x71
#define AML_AddOp                   0x72
#define AML_ConcatOp                0x73
#define AML_SubtractOp              0x74
#define AML_IncrementOp             0x75
#define AML_DecrementOp             0x76
#define AML_MultiplyOp              0x77
#define AML_DivideOp                0x78
#define AML_ShiftLeftOp             0x79
#define AML_ShiftRightOp            0x7a
#define AML_BitAndOp                0x7b
#define AML_BitNandOp               0x7c
#define AML_BitOrOp                 0x7d
#define AML_BitNorOp                0x7e
#define AML_BitXorOp                0x7f
#define AML_BitNotOp                0x80
#define AML_FindSetLeftBitOp        0x81
#define AML_FindSetRightBitOp       0x82
#define AML_DerefOfOp               0x83
#define AML_NotifyOp                0x86
#define AML_SizeOfOp                0x87
#define AML_IndexOp                 0x88
#define AML_MatchOp                 0x89
#define AML_DWordFieldOp            0x8a
#define AML_WordFieldOp             0x8b
#define AML_ByteFieldOp             0x8c
#define AML_BitFieldOp              0x8d
#define AML_TypeOp                  0x8e
#define AML_LAndOp                  0x90
#define AML_LOrOp                   0x91
#define AML_LNotOp                  0x92
#define AML_LEqualOp                0x93
#define AML_LGreaterOp              0x94
#define AML_LLessOp                 0x95
#define AML_IfOp                    0xa0
#define AML_ElseOp                  0xa1
#define AML_WhileOp                 0xa2
#define AML_NoopCode                0xa3
#define AML_ReturnOp                0xa4
#define AML_BreakOp                 0xa5
#define AML_BreakPointOp            0xcc
#define AML_OnesOp                  0xff

/* prefixed opcodes */

#define AML_MutexOp                 0x5b01
#define AML_EventOp                 0x5b02
#define AML_ShiftRightBitOp         0x5b10
#define AML_ShiftLeftBitOp          0x5b11
#define AML_CondRefOfOp             0x5b12
#define AML_CreateFieldOp           0x5b13
#define AML_LoadOp                  0x5b20
#define AML_StallOp                 0x5b21
#define AML_SleepOp                 0x5b22
#define AML_AcquireOp               0x5b23
#define AML_SignalOp                0x5b24
#define AML_WaitOp                  0x5b25
#define AML_ResetOp                 0x5b26
#define AML_ReleaseOp               0x5b27
#define AML_FromBCDOp               0x5b28
#define AML_ToBCDOp                 0x5b29
#define AML_UnLoadOp                0x5b2a
#define AML_RevisionOp              0x5b30
#define AML_DebugOp                 0x5b31
#define AML_FatalOp                 0x5b32
#define AML_RegionOp                0x5b80
#define AML_DefFieldOp              0x5b81
#define AML_DeviceOp                0x5b82
#define AML_ProcessorOp             0x5b83
#define AML_PowerResOp              0x5b84
#define AML_ThermalZoneOp           0x5b85
#define AML_IndexFieldOp            0x5b86
#define AML_BankFieldOp             0x5b87

/* Comparison operation codes for MatchOp operator */

typedef enum {
    MATCH_MTR                   = 0,
    MATCH_MEQ                   = 1,
    MATCH_MLE                   = 2,
    MATCH_MLT                   = 3,
    MATCH_MGE                   = 4,
    MATCH_MGT                   = 5
} MatchCompOp;

/* Field Access Types */

#define ACCESS_TYPE_MASK        0x0f
#define ACCESS_TYPE_SHIFT       0

typedef enum {
    ACCESS_AnyAcc               = 0,
    ACCESS_ByteAcc              = 1,
    ACCESS_WordAcc              = 2,
    ACCESS_DWordAcc             = 3,
    ACCESS_BlockAcc             = 4,
    ACCESS_SMBSendRecvAcc       = 5,
    ACCESS_SMBQuickAcc          = 6
} AccessType;

/* Field Lock Rules */

#define LOCK_RULE_MASK          0x10
#define LOCK_RULE_SHIFT         4

typedef enum {
    GLOCK_NeverLock             = 0,
    GLOCK_AlwaysLock            = 1
} LockRule;

/* Field Update Rules */

#define UPDATE_RULE_MASK        0x060
#define UPDATE_RULE_SHIFT       5

typedef enum {
    UPDATE_Preserve             = 0,
    UPDATE_WriteAsOnes          = 1,
    UPDATE_WriteAsZeros         = 2
} UpdateRule;


/* Region Space ID values */

typedef enum {
    REGION_SystemMemory         = 0,
    REGION_SystemIO             = 1,
    REGION_PCIConfig            = 2,
    REGION_EmbeddedControl      = 3,
    REGION_SMBus                = 4
} RegionSpace;


/* bit fields in MethodFlags byte */

#define METHOD_ARG_COUNT_MASK   7
#define METHOD_ARG_COUNT_SHIFT  0
#define METHOD_SYNCHRONIZED     8


#ifndef DEFINE_AML_GLOBALS
extern UINT8        Aml[256];
extern UINT16       Pfx[256];
extern char         *ShortOps[256];
extern char         *LongOps[256];
extern char         *RegionTypes[5];
extern char         *MatchOps[];
extern char         *AccessTypes[];
extern char         *UpdateRules[];


#else
#pragma message ("AML Globals defined in this module.")


/* 
 * Human-readable decode of rv values, mostly for debugging
 * These need to match the corresponding definitions in amlpriv.h
 * Note that S_FAILURE is not an error, but indicates
 * that other alternatives should be checked.
 */
char            *RV[] = 
{ 
    "S_SUCCESS", 
    "S_FAILURE", 
    "S_ERROR",
    "S_RETURN" 
};


/* Data used in keeping track of fields */

char            *FENames[] = 
{ 
    "skip", 
    "?access?" 
};              /* FE = Field Element */



/* Region type decoding */

char *RegionTypes[5] = 
{   
    "SystemMemory",
    "SystemIO",
    "PCIConfig",
    "EmbeddedControl",
    "SMBus"
};


char *MatchOps[] = 
{   "Error", 
    "MTR", 
    "MEQ", 
    "MLE", 
    "MLT", 
    "MGE", 
    "MGT" 
};


/* Access type decoding */

char *AccessTypes[] = 
{   
    "AnyAcc",
    "ByteAcc",
    "WordAcc",
    "DWordAcc",
    "BlockAcc",
    "SMBSendRecvAcc",
    "SMBQuickAcc"
};


/* Update rule decoding */

char *UpdateRules[] = 
{   
    "Preserve",
    "WriteAsOnes",
    "WriteAsZeros"
};


/* primary decoder */

UINT8 Aml[256] = 
{
    /*      x0                      x1                      x2                      x3          */
    /*      x4                      x5                      x6                      x7          */
    /*      x8                      x9                      xa                      xb          */
    /*      xc                      xd                      xe                      xf          */
/* 0x */    AML_ZeroOp,             AML_OneOp,              AML_UNASSIGNED,         AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_AliasOp,            AML_UNASSIGNED,
            AML_NameOp,             AML_UNASSIGNED,         AML_ByteOp,             AML_WordOp,
            AML_DWordOp,            AML_StringOp,           AML_UNASSIGNED,         AML_UNASSIGNED,
/* 1x */    AML_ScopeOp,            AML_BufferOp,           AML_PackageOp,          AML_UNASSIGNED,
            AML_MethodOp,           AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
/* 2x */    AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_DualNamePrefix,     AML_MultiNamePrefixOp,
/* 3x */    AML_NameCharSubseq,     AML_NameCharSubseq,     AML_NameCharSubseq,     AML_NameCharSubseq,
            AML_NameCharSubseq,     AML_NameCharSubseq,     AML_NameCharSubseq,     AML_NameCharSubseq,
            AML_NameCharSubseq,     AML_NameCharSubseq,     AML_UNASSIGNED,         AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
/* 4x */    AML_UNASSIGNED,         AML_NameCharFirst,      AML_NameCharFirst,      AML_NameCharFirst,
            AML_NameCharFirst,      AML_NameCharFirst,      AML_NameCharFirst,      AML_NameCharFirst,
            AML_NameCharFirst,      AML_NameCharFirst,      AML_NameCharFirst,      AML_NameCharFirst,
            AML_NameCharFirst,      AML_NameCharFirst,      AML_NameCharFirst,      AML_NameCharFirst,
/* 5x */    AML_NameCharFirst,      AML_NameCharFirst,      AML_NameCharFirst,      AML_NameCharFirst,
            AML_NameCharFirst,      AML_NameCharFirst,      AML_NameCharFirst,      AML_NameCharFirst,
            AML_NameCharFirst,      AML_NameCharFirst,      AML_NameCharFirst,      AML_OpPrefix,
            AML_RootPrefix,         AML_UNASSIGNED,         AML_ParentPrefix,       AML_NameCharFirst,
/* 6x */    AML_Local_Op,           AML_Local_Op,           AML_Local_Op,           AML_Local_Op,
            AML_Local_Op,           AML_Local_Op,           AML_Local_Op,           AML_Local_Op,
            AML_Arg_Op,             AML_Arg_Op,             AML_Arg_Op,             AML_Arg_Op,
            AML_Arg_Op,             AML_Arg_Op,             AML_Arg_Op,             AML_UNASSIGNED,
/* 7x */    AML_StoreOp,            AML_RefOfOp,            AML_AddOp,              AML_ConcatOp,
            AML_SubtractOp,         AML_IncrementOp,        AML_DecrementOp,        AML_MultiplyOp,
            AML_DivideOp,           AML_ShiftLeftOp,        AML_ShiftRightOp,       AML_BitAndOp,
            AML_BitNandOp,          AML_BitOrOp,            AML_BitNorOp,           AML_BitXorOp,
/* 8x */    AML_BitNotOp,           AML_FindSetLeftBitOp,   AML_FindSetRightBitOp,  AML_DerefOfOp,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_NotifyOp,           AML_SizeOfOp,
            AML_IndexOp,            AML_MatchOp,            AML_DWordFieldOp,       AML_WordFieldOp,
            AML_ByteFieldOp,        AML_BitFieldOp,         AML_TypeOp,             AML_UNASSIGNED,
/* 9x */    AML_LAndOp,             AML_LOrOp,              AML_LNotOp,             AML_LEqualOp,
            AML_LGreaterOp,         AML_LLessOp,            AML_UNASSIGNED,         AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
/* ax */    AML_IfOp,               AML_ElseOp,             AML_WhileOp,            AML_NoopCode,
            AML_ReturnOp,           AML_BreakOp,            AML_UNASSIGNED,         AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
/* bx */    AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
/* cx */    AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
            AML_BreakPointOp,       AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
/* dx */    AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
/* ex */    AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
/* fx */    AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,         AML_OnesOp
};


/* prefixed decoder */

UINT16 Pfx[256] = 
{
    /*      x0                      x1                      x2                      x3          */
    /*      x4                      x5                      x6                      x7          */
    /*      x8                      x9                      xa                      xb          */
    /*      xc                      xd                      xe                      xf          */
/* 0x */    AML_UNASSIGNED,         AML_MutexOp,            AML_EventOp,           AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
/* 1x */    AML_ShiftRightBitOp,    AML_ShiftLeftBitOp,     AML_CondRefOfOp,       AML_CreateFieldOp,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
/* 2x */    AML_LoadOp,             AML_StallOp,            AML_SleepOp,           AML_AcquireOp,
            AML_SignalOp,           AML_WaitOp,             AML_ResetOp,           AML_ReleaseOp,
            AML_FromBCDOp,          AML_ToBCDOp,            AML_UnLoadOp,          AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
/* 3x */    AML_RevisionOp,         AML_DebugOp,            AML_FatalOp,           AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
/* 4x */    AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
/* 5x */    AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
/* 6x */    AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
/* 7x */    AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
/* 8x */    AML_RegionOp,           AML_DefFieldOp,         AML_DeviceOp,          AML_ProcessorOp,
            AML_PowerResOp,         AML_ThermalZoneOp,      AML_IndexFieldOp,      AML_BankFieldOp,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
/* 9x */    AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
/* ax */    AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
/* bx */    AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
/* cx */    AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
/* dx */    AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
/* ex */    AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
/* fx */    AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED,
            AML_UNASSIGNED,         AML_UNASSIGNED,         AML_UNASSIGNED,        AML_UNASSIGNED
};


/* primary op names */

char *ShortOps[256] = 
{
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

char *LongOps[256] = 
{
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

#endif /* DEFINE_AML_GLOBALS */

#endif /* __AMLCODE_H__ */
