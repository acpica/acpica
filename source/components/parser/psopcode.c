/******************************************************************************
 * 
 * Module Name: psopcode - Parser opcode information table
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
 * 2.1. This is your license from Intel Corp. under its intellectual property
 * rights.  You may have additional license terms from the party that provided
 * you this software, covering your right to use that party's intellectual
 * property rights.
 *
 * 2.2. Intel grants, free of charge, to any person ("Licensee") obtaining a
 * copy of the source code appearing in this file ("Covered Code") an
 * irrevocable, perpetual, worldwide license under Intel's copyrights in the
 * base code distributed originally by Intel ("Original Intel Code") to copy,
 * make derivatives, distribute, use and display any portion of the Covered
 * Code in any form, with the right to sublicense such rights; and
 *
 * 2.3. Intel grants Licensee a non-exclusive and non-transferable patent
 * license (with the right to sublicense), under only those claims of Intel
 * patents that are infringed by the Original Intel Code, to make, use, sell,
 * offer to sell, and import the Covered Code and derivative works thereof
 * solely to the minimum extent necessary to exercise the above copyright
 * license, and in no event shall the patent license extend to any additions
 * to or modifications of the Original Intel Code.  No other license or right
 * is granted directly or by implication, estoppel or otherwise;
 *
 * The above copyright and patent license is granted only if the following
 * conditions are met:
 *
 * 3. Conditions 
 *
 * 3.1. Redistribution of Source with Rights to Further Distribute Source.  
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification with rights to further distribute source must include
 * the above Copyright Notice, the above License, this list of Conditions,
 * and the following Disclaimer and Export Compliance provision.  In addition,
 * Licensee must cause all Covered Code to which Licensee contributes to
 * contain a file documenting the changes Licensee made to create that Covered
 * Code and the date of any change.  Licensee must include in that file the
 * documentation of any changes made by any predecessor Licensee.  Licensee 
 * must include a prominent statement that the modification is derived,
 * directly or indirectly, from Original Intel Code.
 *
 * 3.2. Redistribution of Source with no Rights to Further Distribute Source.  
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification without rights to further distribute source must
 * include the following Disclaimer and Export Compliance provision in the
 * documentation and/or other materials provided with distribution.  In
 * addition, Licensee may not authorize further sublicense of source of any
 * portion of the Covered Code, and must include terms to the effect that the
 * license from Licensee to its licensee is limited to the intellectual
 * property embodied in the software Licensee provides to its licensee, and
 * not to intellectual property embodied in modifications its licensee may
 * make.
 *
 * 3.3. Redistribution of Executable. Redistribution in executable form of any
 * substantial portion of the Covered Code or modification must reproduce the
 * above Copyright Notice, and the following Disclaimer and Export Compliance
 * provision in the documentation and/or other materials provided with the
 * distribution.
 *
 * 3.4. Intel retains all right, title, and interest in and to the Original
 * Intel Code.
 *
 * 3.5. Neither the name Intel nor any other trademark owned or controlled by
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
 * event Licensee exports any such software from the United States or
 * re-exports any such software from a foreign destination, Licensee shall
 * ensure that the distribution and export/re-export of the software is in
 * compliance with all laws, regulations, orders, or other restrictions of the
 * U.S. Export Administration Regulations. Licensee agrees that neither it nor
 * any of its subsidiaries will export/re-export any technical data, process,
 * software, or service, directly or indirectly, to any country for which the
 * United States government or any agency thereof requires an export license,
 * other governmental approval, or letter of assurance, without first obtaining
 * such license, approval or letter.
 *
 *****************************************************************************/


#include <acpi.h>
#include <parser.h>
#include <amlcode.h>



#define _COMPONENT          PARSER
        MODULE_NAME         ("psopcode");






/*******************************************************************************
 *
 * FUNCTION:    PsGetOpcodeInfo
 *
 * PARAMETERS:  Opcode              - The AML opcode
 *
 * RETURN:      A pointer to the info about the opcode.  NULL if the opcode was
 *              not found in the table.
 *
 * DESCRIPTION: Find AML opcode description based on the opcode
 *
 ******************************************************************************/

ACPI_OP_INFO *
PsGetOpcodeInfo (
    UINT16                  Opcode)
{
    ACPI_OP_INFO             *Op;
    INT32                   Hash;


    /* compute hash/index into the AcpiAmlOpIndex table */

    switch (Opcode >> 8)
    {
    case 0:

        /* Simple (8-bit) opcode */

        Hash = Opcode;
        break;


    case AML_EXTOP:

        /* Extended (16-bit, prefix+opcode) opcode */

        Hash = (Opcode + AML_EXTOP_HASH_OFFSET) & 0xff;
        break;



    case AML_LNotOp:

        /* This case is for the bogus opcodes LNOTEQUAL, LLESSEQUAL, LGREATEREQUAL */

        Hash = (Opcode + AML_LNOT_HASH_OFFSET) & 0xff;
        break;


    default:

        DEBUG_PRINT (ACPI_ERROR, ("PsGetOpcodeInfo: Unknown extended Opcode=%X\n",
                Opcode));
    
        return NULL;
    }


    /* Get the Op info pointer for this opcode */

    Op = &Gbl_AmlOpInfo [(INT32) Gbl_AmlOpInfoIndex [Hash]];


    /* If the returned opcode matches, we have a valid opcode */

    if (Op->Opcode == Opcode)
    {
        return Op;
    }

    /* Otherwise, the opcode is an ASCII char or other non-opcode value */

    return NULL;
}


/*******************************************************************************
 *
 * FUNCTION:    PsGetOpcodeName
 *
 * PARAMETERS:  Opcode              - The AML opcode
 *
 * RETURN:      A pointer to the name of the opcode (ASCII String)
 *              Note: Never returns NULL.
 *
 * DESCRIPTION: Translate an opcode into a human-readable string
 *
 ******************************************************************************/

char *
PsGetOpcodeName (
    UINT16                  Opcode)
{
    ACPI_OP_INFO             *Op;


    Op = PsGetOpcodeInfo (Opcode);

    if (!Op)
    {
        return "*ERROR*";
    }

    DEBUG_EXEC (return Op->Name);
    NORMAL_EXEC (return "AE_NOT_CONFIGURED");
}


/*******************************************************************************
 *
 * NAME:        Gbl_AmlOpInfo
 *
 * DESCRIPTION: Opcode table. Each entry contains <opcode, type, name, operands>
 *              The name is a simple ascii string, the operand specifier is an 
 *              ascii string with one letter per operand.  The letter specifies 
 *              the operand type.
 *
 ******************************************************************************/


/*
 * Flags byte: 0-4 (5 bits) = Opcode Type
 *             5   (1 bit)  = Has arguments flag
 *             6-7 (2 bits) = Reserved
 */
#define AML_NO_ARGS         0
#define AML_HAS_ARGS        OP_INFO_HAS_ARGS

/*
 * All AML opcodes and the parse-time arguments for each.  Used by the AML parser  Each list is compressed
 * into a 32-bit number and stored in the master opcode table at the end of this file.
 */

#define ARGP_ZeroOp                     ARG_NONE
#define ARGP_OneOp                      ARG_NONE
#define ARGP_AliasOp                    ARGP_LIST2 (ARGP_NAMESTRING, ARGP_NAME)    
#define ARGP_NameOp                     ARGP_LIST2 (ARGP_NAME,       ARGP_DATAOBJ)
#define ARGP_ByteOp                     ARGP_LIST1 (ARGP_BYTEDATA)
#define ARGP_WordOp                     ARGP_LIST1 (ARGP_WORDDATA)
#define ARGP_DWordOp                    ARGP_LIST1 (ARGP_DWORDDATA)
#define ARGP_StringOp                   ARGP_LIST1 (ARGP_CHARLIST)
#define ARGP_ScopeOp                    ARGP_LIST3 (ARGP_PKGLENGTH,  ARGP_NAME,          ARGP_TERMLIST)
#define ARGP_BufferOp                   ARGP_LIST3 (ARGP_PKGLENGTH,  ARGP_TERMARG,       ARGP_BYTELIST)
#define ARGP_PackageOp                  ARGP_LIST3 (ARGP_PKGLENGTH,  ARGP_BYTEDATA,      ARGP_DATAOBJLIST)
#define ARGP_MethodOp                   ARGP_LIST4 (ARGP_PKGLENGTH,  ARGP_NAME,          ARGP_BYTEDATA,      ARGP_TERMLIST)
#define ARGP_Local0                     ARG_NONE
#define ARGP_Local1                     ARG_NONE
#define ARGP_Local2                     ARG_NONE
#define ARGP_Local3                     ARG_NONE
#define ARGP_Local4                     ARG_NONE
#define ARGP_Local5                     ARG_NONE
#define ARGP_Local6                     ARG_NONE
#define ARGP_Local7                     ARG_NONE
#define ARGP_Arg0                       ARG_NONE
#define ARGP_Arg1                       ARG_NONE
#define ARGP_Arg2                       ARG_NONE
#define ARGP_Arg3                       ARG_NONE
#define ARGP_Arg4                       ARG_NONE
#define ARGP_Arg5                       ARG_NONE
#define ARGP_Arg6                       ARG_NONE
#define ARGP_StoreOp                    ARGP_LIST2 (ARGP_TERMARG,    ARGP_SUPERNAME)
#define ARGP_RefOfOp                    ARGP_LIST1 (ARGP_SUPERNAME)
#define ARGP_AddOp                      ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
#define ARGP_ConcatOp                   ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
#define ARGP_SubtractOp                 ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
#define ARGP_IncrementOp                ARGP_LIST1 (ARGP_SUPERNAME)
#define ARGP_DecrementOp                ARGP_LIST1 (ARGP_SUPERNAME)
#define ARGP_MultiplyOp                 ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
#define ARGP_DivideOp                   ARGP_LIST4 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET,    ARGP_TARGET)
#define ARGP_ShiftLeftOp                ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
#define ARGP_ShiftRightOp               ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
#define ARGP_BitAndOp                   ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
#define ARGP_BitNandOp                  ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
#define ARGP_BitOrOp                    ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
#define ARGP_BitNorOp                   ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
#define ARGP_BitXorOp                   ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
#define ARGP_BitNotOp                   ARGP_LIST2 (ARGP_TERMARG,    ARGP_TARGET)
#define ARGP_FindSetLeftBitOp           ARGP_LIST2 (ARGP_TERMARG,    ARGP_TARGET)
#define ARGP_FindSetRightBitOp          ARGP_LIST2 (ARGP_TERMARG,    ARGP_TARGET)
#define ARGP_DerefOfOp                  ARGP_LIST1 (ARGP_TERMARG)
#define ARGP_NotifyOp                   ARGP_LIST2 (ARGP_SUPERNAME,  ARGP_TERMARG)
#define ARGP_SizeOfOp                   ARGP_LIST1 (ARGP_SUPERNAME)
#define ARGP_IndexOp                    ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
#define ARGP_MatchOp                    ARGP_LIST6 (ARGP_TERMARG,    ARGP_BYTEDATA,      ARGP_TERMARG,   ARGP_BYTEDATA,  ARGP_TERMARG,   ARGP_TERMARG)
#define ARGP_DWordFieldOp               ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_NAME)
#define ARGP_WordFieldOp                ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_NAME)
#define ARGP_ByteFieldOp                ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_NAME)
#define ARGP_BitFieldOp                 ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_NAME)
#define ARGP_TypeOp                     ARGP_LIST1 (ARGP_SUPERNAME)
#define ARGP_LAndOp                     ARGP_LIST2 (ARGP_TERMARG,    ARGP_TERMARG)
#define ARGP_LOrOp                      ARGP_LIST2 (ARGP_TERMARG,    ARGP_TERMARG)
#define ARGP_LNotOp                     ARGP_LIST1 (ARGP_TERMARG)
#define ARGP_LEqualOp                   ARGP_LIST2 (ARGP_TERMARG,    ARGP_TERMARG)
#define ARGP_LGreaterOp                 ARGP_LIST2 (ARGP_TERMARG,    ARGP_TERMARG)
#define ARGP_LLessOp                    ARGP_LIST2 (ARGP_TERMARG,    ARGP_TERMARG)
#define ARGP_IfOp                       ARGP_LIST3 (ARGP_PKGLENGTH,  ARGP_TERMARG, ARGP_TERMLIST)
#define ARGP_ElseOp                     ARGP_LIST2 (ARGP_PKGLENGTH,  ARGP_TERMLIST)
#define ARGP_WhileOp                    ARGP_LIST3 (ARGP_PKGLENGTH,  ARGP_TERMARG, ARGP_TERMLIST)
#define ARGP_NoopCode                   ARG_NONE
#define ARGP_ReturnOp                   ARGP_LIST1 (ARGP_TERMARG)
#define ARGP_BreakOp                    ARG_NONE
#define ARGP_BreakPointOp               ARG_NONE
#define ARGP_OnesOp                     ARG_NONE
#define ARGP_MutexOp                    ARGP_LIST2 (ARGP_NAME,       ARGP_BYTEDATA)
#define ARGP_EventOp                    ARGP_LIST1 (ARGP_NAME)
#define ARGP_CondRefOfOp                ARGP_LIST2 (ARGP_SUPERNAME,  ARGP_SUPERNAME)
#define ARGP_CreateFieldOp              ARGP_LIST4 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TERMARG,   ARGP_NAME)
#define ARGP_LoadOp                     ARGP_LIST2 (ARGP_NAMESTRING, ARGP_SUPERNAME)
#define ARGP_StallOp                    ARGP_LIST1 (ARGP_TERMARG)
#define ARGP_SleepOp                    ARGP_LIST1 (ARGP_TERMARG)
#define ARGP_AcquireOp                  ARGP_LIST2 (ARGP_SUPERNAME,  ARGP_WORDDATA)
#define ARGP_SignalOp                   ARGP_LIST1 (ARGP_SUPERNAME)
#define ARGP_WaitOp                     ARGP_LIST2 (ARGP_SUPERNAME,  ARGP_TERMARG)
#define ARGP_ResetOp                    ARGP_LIST1 (ARGP_SUPERNAME)
#define ARGP_ReleaseOp                  ARGP_LIST1 (ARGP_SUPERNAME)
#define ARGP_FromBCDOp                  ARGP_LIST2 (ARGP_TERMARG,    ARGP_TARGET)
#define ARGP_ToBCDOp                    ARGP_LIST2 (ARGP_TERMARG,    ARGP_TARGET)
#define ARGP_UnLoadOp                   ARGP_LIST1 (ARGP_SUPERNAME)
#define ARGP_RevisionOp                 ARG_NONE
#define ARGP_DebugOp                    ARG_NONE
#define ARGP_FatalOp                    ARGP_LIST3 (ARGP_BYTEDATA,   ARGP_DWORDDATA,     ARGP_TERMARG)
#define ARGP_RegionOp                   ARGP_LIST4 (ARGP_NAME,       ARGP_BYTEDATA,      ARGP_TERMARG,   ARGP_TERMARG) 
#define ARGP_DefFieldOp                 ARGP_LIST4 (ARGP_PKGLENGTH,  ARGP_NAMESTRING,    ARGP_BYTEDATA,  ARGP_FIELDLIST)  
#define ARGP_DeviceOp                   ARGP_LIST3 (ARGP_PKGLENGTH,  ARGP_NAME,          ARGP_OBJLIST)  
#define ARGP_ProcessorOp                ARGP_LIST6 (ARGP_PKGLENGTH,  ARGP_NAME,          ARGP_BYTEDATA,  ARGP_DWORDDATA, ARGP_BYTEDATA,  ARGP_OBJLIST)  
#define ARGP_PowerResOp                 ARGP_LIST5 (ARGP_PKGLENGTH,  ARGP_NAME,          ARGP_BYTEDATA,  ARGP_WORDDATA,  ARGP_OBJLIST)  
#define ARGP_ThermalZoneOp              ARGP_LIST3 (ARGP_PKGLENGTH,  ARGP_NAME,          ARGP_OBJLIST)
#define ARGP_IndexFieldOp               ARGP_LIST5 (ARGP_PKGLENGTH,  ARGP_NAMESTRING,    ARGP_NAMESTRING,ARGP_BYTEDATA,  ARGP_FIELDLIST)  
#define ARGP_BankFieldOp                ARGP_LIST6 (ARGP_PKGLENGTH,  ARGP_NAMESTRING,    ARGP_NAMESTRING,ARGP_TERMARG,   ARGP_BYTEDATA,  ARGP_FIELDLIST)  
#define ARGP_LNOTEQUAL_OP               ARGP_LIST2 (ARGP_TERMARG,    ARGP_TERMARG)
#define ARGP_LLESSEQUAL_OP              ARGP_LIST2 (ARGP_TERMARG,    ARGP_TERMARG)
#define ARGP_LGREATEREQUAL_OP           ARGP_LIST2 (ARGP_TERMARG,    ARGP_TERMARG)
#define ARGP_NAMEPATH_OP                ARGP_LIST1 (ARGP_NAMESTRING)
#define ARGP_METHODCALL_OP              ARGP_LIST1 (ARGP_NAMESTRING)
#define ARGP_BYTELIST_OP                ARGP_LIST1 (ARGP_NAMESTRING)
#define ARGP_RESERVEDFIELD_OP           ARGP_LIST1 (ARGP_NAMESTRING)
#define ARGP_NAMEDFIELD_OP              ARGP_LIST1 (ARGP_NAMESTRING)
#define ARGP_ACCESSFIELD_OP             ARGP_LIST1 (ARGP_NAMESTRING)
#define ARGP_STATICSTRING_OP            ARGP_LIST1 (ARGP_NAMESTRING)



/*
 * All AML opcodes and the runtime arguments for each.  Used by the AML interpreter  Each list is compressed
 * into a 32-bit number and stored in the master opcode table at the end of this file.
 *
 * TBD: These lists will be used to develop a better AmlPrepOperands procedure
 */

#define ARGI_ZeroOp                     ARG_NONE
#define ARGI_OneOp                      ARG_NONE
#define ARGI_AliasOp                    ARGI_INVALID_OPCODE 
#define ARGI_NameOp                     ARGI_INVALID_OPCODE 
#define ARGI_ByteOp                     ARGI_INVALID_OPCODE 
#define ARGI_WordOp                     ARGI_INVALID_OPCODE 
#define ARGI_DWordOp                    ARGI_INVALID_OPCODE 
#define ARGI_StringOp                   ARGI_INVALID_OPCODE 
#define ARGI_ScopeOp                    ARGI_INVALID_OPCODE 
#define ARGI_BufferOp                   ARGI_INVALID_OPCODE 
#define ARGI_PackageOp                  ARGI_INVALID_OPCODE 
#define ARGI_MethodOp                   ARGI_INVALID_OPCODE 
#define ARGI_Local0                     ARG_NONE
#define ARGI_Local1                     ARG_NONE
#define ARGI_Local2                     ARG_NONE
#define ARGI_Local3                     ARG_NONE
#define ARGI_Local4                     ARG_NONE
#define ARGI_Local5                     ARG_NONE
#define ARGI_Local6                     ARG_NONE
#define ARGI_Local7                     ARG_NONE
#define ARGI_Arg0                       ARG_NONE
#define ARGI_Arg1                       ARG_NONE
#define ARGI_Arg2                       ARG_NONE
#define ARGI_Arg3                       ARG_NONE
#define ARGI_Arg4                       ARG_NONE
#define ARGI_Arg5                       ARG_NONE
#define ARGI_Arg6                       ARG_NONE
#define ARGI_StoreOp                    ARGI_LIST2 (ARGI_ANYTYPE,    ARGI_TARGETREF)
#define ARGI_RefOfOp                    ARGI_LIST1 (ARGI_LVALUE)
#define ARGI_AddOp                      ARGI_LIST3 (ARGI_NUMBER,     ARGI_NUMBER,        ARGI_TARGETREF)
#define ARGI_ConcatOp                   ARGI_LIST3 (ARGI_STRING,     ARGI_STRING,        ARGI_TARGETREF)
#define ARGI_SubtractOp                 ARGI_LIST3 (ARGI_NUMBER,     ARGI_NUMBER,        ARGI_TARGETREF)
#define ARGI_IncrementOp                ARGI_LIST1 (ARGI_LVALUE)
#define ARGI_DecrementOp                ARGI_LIST1 (ARGI_LVALUE)
#define ARGI_MultiplyOp                 ARGI_LIST3 (ARGI_NUMBER,     ARGI_NUMBER,        ARGI_TARGETREF)
#define ARGI_DivideOp                   ARGI_LIST4 (ARGI_NUMBER,     ARGI_NUMBER,        ARGI_TARGETREF,    ARGI_TARGETREF)
#define ARGI_ShiftLeftOp                ARGI_LIST3 (ARGI_NUMBER,     ARGI_NUMBER,        ARGI_TARGETREF)
#define ARGI_ShiftRightOp               ARGI_LIST3 (ARGI_NUMBER,     ARGI_NUMBER,        ARGI_TARGETREF)
#define ARGI_BitAndOp                   ARGI_LIST3 (ARGI_NUMBER,     ARGI_NUMBER,        ARGI_TARGETREF)
#define ARGI_BitNandOp                  ARGI_LIST3 (ARGI_NUMBER,     ARGI_NUMBER,        ARGI_TARGETREF)
#define ARGI_BitOrOp                    ARGI_LIST3 (ARGI_NUMBER,     ARGI_NUMBER,        ARGI_TARGETREF)
#define ARGI_BitNorOp                   ARGI_LIST3 (ARGI_NUMBER,     ARGI_NUMBER,        ARGI_TARGETREF)
#define ARGI_BitXorOp                   ARGI_LIST3 (ARGI_NUMBER,     ARGI_NUMBER,        ARGI_TARGETREF)
#define ARGI_BitNotOp                   ARGI_LIST2 (ARGI_NUMBER,     ARGI_TARGETREF)
#define ARGI_FindSetLeftBitOp           ARGI_LIST2 (ARGI_NUMBER,     ARGI_TARGETREF)
#define ARGI_FindSetRightBitOp          ARGI_LIST2 (ARGI_NUMBER,     ARGI_TARGETREF)
#define ARGI_DerefOfOp                  ARGI_LIST1 (ARGI_LVALUE)
#define ARGI_NotifyOp                   ARGI_LIST2 (ARGI_LVALUE,     ARGI_NUMBER)
#define ARGI_SizeOfOp                   ARGI_LIST1 (ARGI_DATAOBJECT)
#define ARGI_IndexOp                    ARGI_LIST3 (ARGI_COMPLEXOBJ, ARGI_NUMBER,        ARGI_TARGETREF)
#define ARGI_MatchOp                    ARGI_LIST6 (ARGI_PACKAGE,    ARGI_NUMBER,        ARGI_NUMBER,       ARGI_NUMBER,    ARGI_NUMBER,    ARGI_NUMBER)
#define ARGI_DWordFieldOp               ARGI_LIST3 (ARGI_BUFFER,     ARGI_NUMBER,        ARGI_LVALUE)
#define ARGI_WordFieldOp                ARGI_LIST3 (ARGI_BUFFER,     ARGI_NUMBER,        ARGI_LVALUE)
#define ARGI_ByteFieldOp                ARGI_LIST3 (ARGI_BUFFER,     ARGI_NUMBER,        ARGI_LVALUE)
#define ARGI_BitFieldOp                 ARGI_LIST3 (ARGI_BUFFER,     ARGI_NUMBER,        ARGI_LVALUE)
#define ARGI_TypeOp                     ARGI_LIST1 (ARGI_ANYTYPE)
#define ARGI_LAndOp                     ARGI_LIST2 (ARGI_NUMBER,     ARGI_NUMBER)
#define ARGI_LOrOp                      ARGI_LIST2 (ARGI_NUMBER,     ARGI_NUMBER)
#define ARGI_LNotOp                     ARGI_LIST1 (ARGI_NUMBER)
#define ARGI_LEqualOp                   ARGI_LIST2 (ARGI_NUMBER,     ARGI_NUMBER)
#define ARGI_LGreaterOp                 ARGI_LIST2 (ARGI_NUMBER,     ARGI_NUMBER)
#define ARGI_LLessOp                    ARGI_LIST2 (ARGI_NUMBER,     ARGI_NUMBER)
#define ARGI_IfOp                       ARGI_INVALID_OPCODE 
#define ARGI_ElseOp                     ARGI_INVALID_OPCODE 
#define ARGI_WhileOp                    ARGI_INVALID_OPCODE 
#define ARGI_NoopCode                   ARG_NONE
#define ARGI_ReturnOp                   ARGI_INVALID_OPCODE
#define ARGI_BreakOp                    ARG_NONE
#define ARGI_BreakPointOp               ARG_NONE
#define ARGI_OnesOp                     ARG_NONE
#define ARGI_MutexOp                    ARGI_INVALID_OPCODE
#define ARGI_EventOp                    ARGI_INVALID_OPCODE
#define ARGI_CondRefOfOp                ARGI_LIST2 (ARGI_LVALUE,     ARGI_TARGETREF)
#define ARGI_CreateFieldOp              ARGI_LIST4 (ARGI_BUFFER,     ARGI_NUMBER,        ARGI_NUMBER,       ARGI_LVALUE)
#define ARGI_LoadOp                     ARGI_LIST2 (ARGP_NAMESTRING, ARGP_SUPERNAME)
#define ARGI_StallOp                    ARGI_LIST1 (ARGI_NUMBER)
#define ARGI_SleepOp                    ARGI_LIST1 (ARGI_NUMBER)
#define ARGI_AcquireOp                  ARGI_LIST2 (ARGI_MUTEX,      ARGI_NUMBER)
#define ARGI_SignalOp                   ARGI_LIST1 (ARGI_EVENT)
#define ARGI_WaitOp                     ARGI_LIST2 (ARGI_EVENT,      ARGI_NUMBER)
#define ARGI_ResetOp                    ARGI_LIST1 (ARGI_EVENT)
#define ARGI_ReleaseOp                  ARGI_LIST1 (ARGI_MUTEX)
#define ARGI_FromBCDOp                  ARGI_LIST2 (ARGI_NUMBER,     ARGI_TARGETREF)
#define ARGI_ToBCDOp                    ARGI_LIST2 (ARGI_NUMBER,     ARGI_TARGETREF)
#define ARGI_UnLoadOp                   ARGI_LIST1 (ARGP_SUPERNAME)
#define ARGI_RevisionOp                 ARG_NONE
#define ARGI_DebugOp                    ARG_NONE
#define ARGI_FatalOp                    ARGI_LIST3 (ARGI_NUMBER,     ARGI_NUMBER,        ARGI_NUMBER)
#define ARGI_RegionOp                   ARGI_INVALID_OPCODE
#define ARGI_DefFieldOp                 ARGI_INVALID_OPCODE
#define ARGI_DeviceOp                   ARGI_INVALID_OPCODE
#define ARGI_ProcessorOp                ARGI_INVALID_OPCODE
#define ARGI_PowerResOp                 ARGI_INVALID_OPCODE
#define ARGI_ThermalZoneOp              ARGI_INVALID_OPCODE
#define ARGI_IndexFieldOp               ARGI_INVALID_OPCODE
#define ARGI_BankFieldOp                ARGI_INVALID_OPCODE
#define ARGI_LNOTEQUAL_OP               ARGI_INVALID_OPCODE
#define ARGI_LLESSEQUAL_OP              ARGI_INVALID_OPCODE
#define ARGI_LGREATEREQUAL_OP           ARGI_INVALID_OPCODE
#define ARGI_NAMEPATH_OP                ARGI_INVALID_OPCODE
#define ARGI_METHODCALL_OP              ARGI_INVALID_OPCODE
#define ARGI_BYTELIST_OP                ARGI_INVALID_OPCODE
#define ARGI_RESERVEDFIELD_OP           ARGI_INVALID_OPCODE
#define ARGI_NAMEDFIELD_OP              ARGI_INVALID_OPCODE
#define ARGI_ACCESSFIELD_OP             ARGI_INVALID_OPCODE
#define ARGI_STATICSTRING_OP            ARGI_INVALID_OPCODE






/*
 * Master Opcode information table.  A summary of everything we know about each opcode, all in one place.
 */


ACPI_OP_INFO        Gbl_AmlOpInfo[] =
{
/*                          Opcode                 Opcode Type           Has Arguments? Child  Name                 Parser Args             Interpreter Args */
 
/*  00 */   OP_INFO_ENTRY (AML_ZeroOp,            OPTYPE_CONSTANT|        AML_NO_ARGS|    0,  "ZeroOp",             ARGP_ZeroOp,            ARGI_ZeroOp),
/*  01 */   OP_INFO_ENTRY (AML_OneOp,             OPTYPE_CONSTANT|        AML_NO_ARGS|    0,  "OneOp",              ARGP_OneOp,             ARGI_OneOp),
/*  02 */   OP_INFO_ENTRY (AML_AliasOp,           OPTYPE_NAMED_OBJECT|    AML_HAS_ARGS|   0,  "Alias",              ARGP_AliasOp,           ARGI_AliasOp),
/*  03 */   OP_INFO_ENTRY (AML_NameOp,            OPTYPE_NAMED_OBJECT|    AML_HAS_ARGS|   0,  "Name",               ARGP_NameOp,            ARGI_NameOp),
/*  04 */   OP_INFO_ENTRY (AML_ByteOp,            OPTYPE_LITERAL|         AML_NO_ARGS|    0,  "ByteConst",          ARGP_ByteOp,            ARGI_ByteOp),
/*  05 */   OP_INFO_ENTRY (AML_WordOp,            OPTYPE_LITERAL|         AML_NO_ARGS|    0,  "WordConst",          ARGP_WordOp,            ARGI_WordOp),
/*  06 */   OP_INFO_ENTRY (AML_DWordOp,           OPTYPE_LITERAL|         AML_NO_ARGS|    0,  "DwordConst",         ARGP_DWordOp,           ARGI_DWordOp),
/*  07 */   OP_INFO_ENTRY (AML_StringOp,          OPTYPE_LITERAL|         AML_NO_ARGS|    0,  "String",             ARGP_StringOp,          ARGI_StringOp),
/*  08 */   OP_INFO_ENTRY (AML_ScopeOp,           OPTYPE_NAMED_OBJECT|    AML_HAS_ARGS|   0,  "Scope",              ARGP_ScopeOp,           ARGI_ScopeOp),
/*  09 */   OP_INFO_ENTRY (AML_BufferOp,          OPTYPE_DATA_TERM|       AML_HAS_ARGS|   0,  "Buffer",             ARGP_BufferOp,          ARGI_BufferOp),
/*  0A */   OP_INFO_ENTRY (AML_PackageOp,         OPTYPE_DATA_TERM|       AML_HAS_ARGS|   0,  "Package",            ARGP_PackageOp,         ARGI_PackageOp),
/*  0B */   OP_INFO_ENTRY (AML_MethodOp,          OPTYPE_NAMED_OBJECT|    AML_HAS_ARGS|   0,  "Method",             ARGP_MethodOp,          ARGI_MethodOp),
/*  0C */   OP_INFO_ENTRY (AML_Local0,            OPTYPE_LOCAL_VARIABLE|  AML_NO_ARGS|    0,  "Local0",             ARGP_Local0,            ARGI_Local0),
/*  0D */   OP_INFO_ENTRY (AML_Local1,            OPTYPE_LOCAL_VARIABLE|  AML_NO_ARGS|    0,  "Local1",             ARGP_Local1,            ARGI_Local1),
/*  0E */   OP_INFO_ENTRY (AML_Local2,            OPTYPE_LOCAL_VARIABLE|  AML_NO_ARGS|    0,  "Local2",             ARGP_Local2,            ARGI_Local2),
/*  0F */   OP_INFO_ENTRY (AML_Local3,            OPTYPE_LOCAL_VARIABLE|  AML_NO_ARGS|    0,  "Local3",             ARGP_Local3,            ARGI_Local3),
/*  10 */   OP_INFO_ENTRY (AML_Local4,            OPTYPE_LOCAL_VARIABLE|  AML_NO_ARGS|    0,  "Local4",             ARGP_Local4,            ARGI_Local4),
/*  11 */   OP_INFO_ENTRY (AML_Local5,            OPTYPE_LOCAL_VARIABLE|  AML_NO_ARGS|    0,  "Local5",             ARGP_Local5,            ARGI_Local5),
/*  12 */   OP_INFO_ENTRY (AML_Local6,            OPTYPE_LOCAL_VARIABLE|  AML_NO_ARGS|    0,  "Local6",             ARGP_Local6,            ARGI_Local6),
/*  13 */   OP_INFO_ENTRY (AML_Local7,            OPTYPE_LOCAL_VARIABLE|  AML_NO_ARGS|    0,  "Local7",             ARGP_Local7,            ARGI_Local7),
/*  14 */   OP_INFO_ENTRY (AML_Arg0,              OPTYPE_METHOD_ARGUMENT| AML_NO_ARGS|    0,  "Arg0",               ARGP_Arg0,              ARGI_Arg0),
/*  15 */   OP_INFO_ENTRY (AML_Arg1,              OPTYPE_METHOD_ARGUMENT| AML_NO_ARGS|    0,  "Arg1",               ARGP_Arg1,              ARGI_Arg1),
/*  16 */   OP_INFO_ENTRY (AML_Arg2,              OPTYPE_METHOD_ARGUMENT| AML_NO_ARGS|    0,  "Arg2",               ARGP_Arg2,              ARGI_Arg2),
/*  17 */   OP_INFO_ENTRY (AML_Arg3,              OPTYPE_METHOD_ARGUMENT| AML_NO_ARGS|    0,  "Arg3",               ARGP_Arg3,              ARGI_Arg3),
/*  18 */   OP_INFO_ENTRY (AML_Arg4,              OPTYPE_METHOD_ARGUMENT| AML_NO_ARGS|    0,  "Arg4",               ARGP_Arg4,              ARGI_Arg4),
/*  19 */   OP_INFO_ENTRY (AML_Arg5,              OPTYPE_METHOD_ARGUMENT| AML_NO_ARGS|    0,  "Arg5",               ARGP_Arg5,              ARGI_Arg5),
/*  1A */   OP_INFO_ENTRY (AML_Arg6,              OPTYPE_METHOD_ARGUMENT| AML_NO_ARGS|    0,  "Arg6",               ARGP_Arg6,              ARGI_Arg6),
/*  1B */   OP_INFO_ENTRY (AML_StoreOp,           OPTYPE_MONADIC2R|       AML_HAS_ARGS|   0,  "Store",              ARGP_StoreOp,           ARGI_StoreOp),
/*  1C */   OP_INFO_ENTRY (AML_RefOfOp,           OPTYPE_MONADIC2|        AML_HAS_ARGS|   0,  "RefOf",              ARGP_RefOfOp,           ARGI_RefOfOp),
/*  1D */   OP_INFO_ENTRY (AML_AddOp,             OPTYPE_DYADIC2R|        AML_HAS_ARGS|   0,  "Add",                ARGP_AddOp,             ARGI_AddOp),
/*  1E */   OP_INFO_ENTRY (AML_ConcatOp,          OPTYPE_DYADIC2R|        AML_HAS_ARGS|   0,  "Concat",             ARGP_ConcatOp,          ARGI_ConcatOp),
/*  1F */   OP_INFO_ENTRY (AML_SubtractOp,        OPTYPE_DYADIC2R|        AML_HAS_ARGS|   0,  "Subtract",           ARGP_SubtractOp,        ARGI_SubtractOp),
/*  20 */   OP_INFO_ENTRY (AML_IncrementOp,       OPTYPE_MONADIC2|        AML_HAS_ARGS|   0,  "Increment",          ARGP_IncrementOp,       ARGI_IncrementOp),
/*  21 */   OP_INFO_ENTRY (AML_DecrementOp,       OPTYPE_MONADIC2|        AML_HAS_ARGS|   0,  "Decrement",          ARGP_DecrementOp,       ARGI_DecrementOp),
/*  22 */   OP_INFO_ENTRY (AML_MultiplyOp,        OPTYPE_DYADIC2R|        AML_HAS_ARGS|   0,  "Multiply",           ARGP_MultiplyOp,        ARGI_MultiplyOp),
/*  23 */   OP_INFO_ENTRY (AML_DivideOp,          OPTYPE_DYADIC2R|        AML_HAS_ARGS|   0,  "Divide",             ARGP_DivideOp,          ARGI_DivideOp),
/*  24 */   OP_INFO_ENTRY (AML_ShiftLeftOp,       OPTYPE_DYADIC2R|        AML_HAS_ARGS|   0,  "ShiftLeft",          ARGP_ShiftLeftOp,       ARGI_ShiftLeftOp),
/*  25 */   OP_INFO_ENTRY (AML_ShiftRightOp,      OPTYPE_DYADIC2R|        AML_HAS_ARGS|   0,  "ShiftRight",         ARGP_ShiftRightOp,      ARGI_ShiftRightOp),
/*  26 */   OP_INFO_ENTRY (AML_BitAndOp,          OPTYPE_DYADIC2R|        AML_HAS_ARGS|   0,  "And",                ARGP_BitAndOp,          ARGI_BitAndOp),
/*  27 */   OP_INFO_ENTRY (AML_BitNandOp,         OPTYPE_DYADIC2R|        AML_HAS_ARGS|   0,  "NAnd",               ARGP_BitNandOp,         ARGI_BitNandOp),
/*  28 */   OP_INFO_ENTRY (AML_BitOrOp,           OPTYPE_DYADIC2R|        AML_HAS_ARGS|   0,  "Or",                 ARGP_BitOrOp,           ARGI_BitOrOp),
/*  29 */   OP_INFO_ENTRY (AML_BitNorOp,          OPTYPE_DYADIC2R|        AML_HAS_ARGS|   0,  "NOr",                ARGP_BitNorOp,          ARGI_BitNorOp),
/*  2A */   OP_INFO_ENTRY (AML_BitXorOp,          OPTYPE_DYADIC2R|        AML_HAS_ARGS|   0,  "XOr",                ARGP_BitXorOp,          ARGI_BitXorOp),
/*  2B */   OP_INFO_ENTRY (AML_BitNotOp,          OPTYPE_MONADIC2R|       AML_HAS_ARGS|   0,  "Not",                ARGP_BitNotOp,          ARGI_BitNotOp),
/*  2C */   OP_INFO_ENTRY (AML_FindSetLeftBitOp,  OPTYPE_MONADIC2R|       AML_HAS_ARGS|   0,  "FindSetLeftBit",     ARGP_FindSetLeftBitOp,  ARGI_FindSetLeftBitOp),
/*  2D */   OP_INFO_ENTRY (AML_FindSetRightBitOp, OPTYPE_MONADIC2R|       AML_HAS_ARGS|   0,  "FindSetRightBit",    ARGP_FindSetRightBitOp, ARGI_FindSetRightBitOp),
/*  2E */   OP_INFO_ENTRY (AML_DerefOfOp,         OPTYPE_MONADIC2|        AML_HAS_ARGS|   0,  "DerefOf",            ARGP_DerefOfOp,         ARGI_DerefOfOp),
/*  2F */   OP_INFO_ENTRY (AML_NotifyOp,          OPTYPE_DYADIC1|         AML_HAS_ARGS|   0,  "Notify",             ARGP_NotifyOp,          ARGI_NotifyOp),
/*  30 */   OP_INFO_ENTRY (AML_SizeOfOp,          OPTYPE_MONADIC2|        AML_HAS_ARGS|   0,  "SizeOf",             ARGP_SizeOfOp,          ARGI_SizeOfOp),
/*  31 */   OP_INFO_ENTRY (AML_IndexOp,           OPTYPE_INDEX|           AML_HAS_ARGS|   0,  "Index",              ARGP_IndexOp,           ARGI_IndexOp),
/*  32 */   OP_INFO_ENTRY (AML_MatchOp,           OPTYPE_MATCH|           AML_HAS_ARGS|   0,  "Match",              ARGP_MatchOp,           ARGI_MatchOp),
/*  33 */   OP_INFO_ENTRY (AML_DWordFieldOp,      OPTYPE_CREATE_FIELD|    AML_HAS_ARGS|   0,  "CreateDWordField",   ARGP_DWordFieldOp,      ARGI_DWordFieldOp),
/*  34 */   OP_INFO_ENTRY (AML_WordFieldOp,       OPTYPE_CREATE_FIELD|    AML_HAS_ARGS|   0,  "CreateWordField",    ARGP_WordFieldOp,       ARGI_WordFieldOp),
/*  35 */   OP_INFO_ENTRY (AML_ByteFieldOp,       OPTYPE_CREATE_FIELD|    AML_HAS_ARGS|   0,  "CreateByteField",    ARGP_ByteFieldOp,       ARGI_ByteFieldOp),
/*  36 */   OP_INFO_ENTRY (AML_BitFieldOp,        OPTYPE_CREATE_FIELD|    AML_HAS_ARGS|   0,  "CreateBitField",     ARGP_BitFieldOp,        ARGI_BitFieldOp),
/*  37 */   OP_INFO_ENTRY (AML_TypeOp,            OPTYPE_MONADIC2|        AML_HAS_ARGS|   0,  "ObjectType",         ARGP_TypeOp,            ARGI_TypeOp),
/*  38 */   OP_INFO_ENTRY (AML_LAndOp,            OPTYPE_DYADIC2|         AML_HAS_ARGS|   0,  "LAnd",               ARGP_LAndOp,            ARGI_LAndOp),
/*  39 */   OP_INFO_ENTRY (AML_LOrOp,             OPTYPE_DYADIC2|         AML_HAS_ARGS|   0,  "LOr",                ARGP_LOrOp,             ARGI_LOrOp),
/*  3A */   OP_INFO_ENTRY (AML_LNotOp,            OPTYPE_MONADIC2|        AML_HAS_ARGS|   0,  "LNot",               ARGP_LNotOp,            ARGI_LNotOp),
/*  3B */   OP_INFO_ENTRY (AML_LEqualOp,          OPTYPE_DYADIC2|         AML_HAS_ARGS|   0,  "LEqual",             ARGP_LEqualOp,          ARGI_LEqualOp),
/*  3C */   OP_INFO_ENTRY (AML_LGreaterOp,        OPTYPE_DYADIC2|         AML_HAS_ARGS|   0,  "LGreater",           ARGP_LGreaterOp,        ARGI_LGreaterOp),
/*  3D */   OP_INFO_ENTRY (AML_LLessOp,           OPTYPE_DYADIC2|         AML_HAS_ARGS|   0,  "LLess",              ARGP_LLessOp,           ARGI_LLessOp),
/*  3E */   OP_INFO_ENTRY (AML_IfOp,              OPTYPE_CONTROL|         AML_HAS_ARGS|   0,  "If",                 ARGP_IfOp,              ARGI_IfOp),
/*  3F */   OP_INFO_ENTRY (AML_ElseOp,            OPTYPE_CONTROL|         AML_HAS_ARGS|   0,  "Else",               ARGP_ElseOp,            ARGI_ElseOp),
/*  40 */   OP_INFO_ENTRY (AML_WhileOp,           OPTYPE_CONTROL|         AML_HAS_ARGS|   0,  "While",              ARGP_WhileOp,           ARGI_WhileOp),
/*  41 */   OP_INFO_ENTRY (AML_NoopCode,          OPTYPE_CONTROL|         AML_NO_ARGS|    0,  "Noop",               ARGP_NoopCode,          ARGI_NoopCode),
/*  42 */   OP_INFO_ENTRY (AML_ReturnOp,          OPTYPE_CONTROL|         AML_HAS_ARGS|   0,  "Return",             ARGP_ReturnOp,          ARGI_ReturnOp),
/*  43 */   OP_INFO_ENTRY (AML_BreakOp,           OPTYPE_CONTROL|         AML_NO_ARGS|    0,  "Break",              ARGP_BreakOp,           ARGI_BreakOp),
/*  44 */   OP_INFO_ENTRY (AML_BreakPointOp,      OPTYPE_CONTROL|         AML_NO_ARGS|    0,  "BreakPoint",         ARGP_BreakPointOp,      ARGI_BreakPointOp),
/*  45 */   OP_INFO_ENTRY (AML_OnesOp,            OPTYPE_CONSTANT|        AML_NO_ARGS|    0,  "OnesOp",             ARGP_OnesOp,            ARGI_OnesOp),

/* Prefixed opcodes (Two-byte opcodes with a prefix op) */
    
/*  46 */   OP_INFO_ENTRY (AML_MutexOp,           OPTYPE_NAMED_OBJECT|    AML_HAS_ARGS|   0,  "Mutex",              ARGP_MutexOp,           ARGI_MutexOp),
/*  47 */   OP_INFO_ENTRY (AML_EventOp,           OPTYPE_NAMED_OBJECT|    AML_NO_ARGS|    0,  "Event",              ARGP_EventOp,           ARGI_EventOp),
/*  48 */   OP_INFO_ENTRY (AML_CondRefOfOp,       OPTYPE_MONADIC2R|       AML_HAS_ARGS|   0,  "CondRefOf",          ARGP_CondRefOfOp,       ARGI_CondRefOfOp),
/*  49 */   OP_INFO_ENTRY (AML_CreateFieldOp,     OPTYPE_CREATE_FIELD|    AML_HAS_ARGS|   0,  "CreateField",        ARGP_CreateFieldOp,     ARGI_CreateFieldOp),
/*  4A */   OP_INFO_ENTRY (AML_LoadOp,            OPTYPE_RECONFIGURATION| AML_HAS_ARGS|   0,  "Load",               ARGP_LoadOp,            ARGI_LoadOp),
/*  4B */   OP_INFO_ENTRY (AML_StallOp,           OPTYPE_MONADIC1|        AML_HAS_ARGS|   0,  "Stall",              ARGP_StallOp,           ARGI_StallOp),
/*  4C */   OP_INFO_ENTRY (AML_SleepOp,           OPTYPE_MONADIC1|        AML_HAS_ARGS|   0,  "Sleep",              ARGP_SleepOp,           ARGI_SleepOp),
/*  4D */   OP_INFO_ENTRY (AML_AcquireOp,         OPTYPE_DYADIC2S|        AML_HAS_ARGS|   0,  "Acquire",            ARGP_AcquireOp,         ARGI_AcquireOp),
/*  4E */   OP_INFO_ENTRY (AML_SignalOp,          OPTYPE_MONADIC1|        AML_HAS_ARGS|   0,  "Signal",             ARGP_SignalOp,          ARGI_SignalOp),
/*  4F */   OP_INFO_ENTRY (AML_WaitOp,            OPTYPE_DYADIC2S|        AML_HAS_ARGS|   0,  "Wait",               ARGP_WaitOp,            ARGI_WaitOp),
/*  50 */   OP_INFO_ENTRY (AML_ResetOp,           OPTYPE_MONADIC1|        AML_HAS_ARGS|   0,  "Reset",              ARGP_ResetOp,           ARGI_ResetOp),
/*  51 */   OP_INFO_ENTRY (AML_ReleaseOp,         OPTYPE_MONADIC1|        AML_HAS_ARGS|   0,  "Release",            ARGP_ReleaseOp,         ARGI_ReleaseOp),
/*  52 */   OP_INFO_ENTRY (AML_FromBCDOp,         OPTYPE_MONADIC2R|       AML_HAS_ARGS|   0,  "FromBCD",            ARGP_FromBCDOp,         ARGI_FromBCDOp),
/*  53 */   OP_INFO_ENTRY (AML_ToBCDOp,           OPTYPE_MONADIC2R|       AML_HAS_ARGS|   0,  "ToBCD",              ARGP_ToBCDOp,           ARGI_ToBCDOp),
/*  54 */   OP_INFO_ENTRY (AML_UnLoadOp,          OPTYPE_RECONFIGURATION| AML_HAS_ARGS|   0,  "Unload",             ARGP_UnLoadOp,          ARGI_UnLoadOp),
/*  55 */   OP_INFO_ENTRY (AML_RevisionOp,        OPTYPE_CONSTANT|        AML_NO_ARGS|    0,  "Revision",           ARGP_RevisionOp,        ARGI_RevisionOp),
/*  56 */   OP_INFO_ENTRY (AML_DebugOp,           OPTYPE_CONSTANT|        AML_NO_ARGS|    0,  "Debug",              ARGP_DebugOp,           ARGI_DebugOp),
/*  57 */   OP_INFO_ENTRY (AML_FatalOp,           OPTYPE_FATAL|           AML_HAS_ARGS|   0,  "Fatal",              ARGP_FatalOp,           ARGI_FatalOp),
/*  58 */   OP_INFO_ENTRY (AML_RegionOp,          OPTYPE_NAMED_OBJECT|    AML_HAS_ARGS|   0,  "OpRegion",           ARGP_RegionOp,          ARGI_RegionOp),
/*  59 */   OP_INFO_ENTRY (AML_DefFieldOp,        OPTYPE_NAMED_OBJECT|    AML_HAS_ARGS|   0,  "Field",              ARGP_DefFieldOp,        ARGI_DefFieldOp),
/*  5A */   OP_INFO_ENTRY (AML_DeviceOp,          OPTYPE_NAMED_OBJECT|    AML_HAS_ARGS|   0,  "Device",             ARGP_DeviceOp,          ARGI_DeviceOp),
/*  5B */   OP_INFO_ENTRY (AML_ProcessorOp,       OPTYPE_NAMED_OBJECT|    AML_HAS_ARGS|   0,  "Processor",          ARGP_ProcessorOp,       ARGI_ProcessorOp),
/*  5C */   OP_INFO_ENTRY (AML_PowerResOp,        OPTYPE_NAMED_OBJECT|    AML_HAS_ARGS|   0,  "PowerRes",           ARGP_PowerResOp,        ARGI_PowerResOp),
/*  5D */   OP_INFO_ENTRY (AML_ThermalZoneOp,     OPTYPE_NAMED_OBJECT|    AML_HAS_ARGS|   0,  "ThermalZone",        ARGP_ThermalZoneOp,     ARGI_ThermalZoneOp),
/*  5E */   OP_INFO_ENTRY (AML_IndexFieldOp,      OPTYPE_NAMED_OBJECT|    AML_HAS_ARGS|   0,  "IndexField",         ARGP_IndexFieldOp,      ARGI_IndexFieldOp),
/*  5F */   OP_INFO_ENTRY (AML_BankFieldOp,       OPTYPE_NAMED_OBJECT|    AML_HAS_ARGS|   0,  "BankField",          ARGP_BankFieldOp,       ARGI_BankFieldOp),

/* Internal opcodes that map to invalid AML opcodes */

/*  60 */   OP_INFO_ENTRY (AML_LNOTEQUAL_OP,      OPTYPE_BOGUS|           AML_HAS_ARGS|   0,  "LNotEqual",          ARGP_LNOTEQUAL_OP,      ARGI_LNOTEQUAL_OP),
/*  61 */   OP_INFO_ENTRY (AML_LLESSEQUAL_OP,     OPTYPE_BOGUS|           AML_HAS_ARGS|   0,  "LLessEqual",         ARGP_LLESSEQUAL_OP,     ARGI_LLESSEQUAL_OP),
/*  62 */   OP_INFO_ENTRY (AML_LGREATEREQUAL_OP,  OPTYPE_BOGUS|           AML_HAS_ARGS|   0,  "LGreaterEqual",      ARGP_LGREATEREQUAL_OP,  ARGI_LGREATEREQUAL_OP),
/*  63 */   OP_INFO_ENTRY (AML_NAMEPATH_OP,       OPTYPE_LITERAL|         AML_NO_ARGS|    0,  "NamePath",           ARGP_NAMEPATH_OP,       ARGI_NAMEPATH_OP),
/*  64 */   OP_INFO_ENTRY (AML_METHODCALL_OP,     OPTYPE_METHOD_CALL|     AML_HAS_ARGS|   0,  "MethodCall",         ARGP_METHODCALL_OP,     ARGI_METHODCALL_OP),
/*  65 */   OP_INFO_ENTRY (AML_BYTELIST_OP,       OPTYPE_LITERAL|         AML_NO_ARGS|    0,  "ByteList",           ARGP_BYTELIST_OP,       ARGI_BYTELIST_OP),
/*  66 */   OP_INFO_ENTRY (AML_RESERVEDFIELD_OP,  OPTYPE_BOGUS|           AML_NO_ARGS|    0,  "ReservedField",      ARGP_RESERVEDFIELD_OP,  ARGI_RESERVEDFIELD_OP),
/*  67 */   OP_INFO_ENTRY (AML_NAMEDFIELD_OP,     OPTYPE_BOGUS|           AML_NO_ARGS|    0,  "NamedField",         ARGP_NAMEDFIELD_OP,     ARGI_NAMEDFIELD_OP),
/*  68 */   OP_INFO_ENTRY (AML_ACCESSFIELD_OP,    OPTYPE_BOGUS|           AML_NO_ARGS|    0,  "AccessField",        ARGP_ACCESSFIELD_OP,    ARGI_ACCESSFIELD_OP),
/*  69 */   OP_INFO_ENTRY (AML_STATICSTRING_OP,   OPTYPE_BOGUS|           AML_NO_ARGS|    0,  "StaticString",       ARGP_STATICSTRING_OP,   ARGI_STATICSTRING_OP),
/*  6A */   OP_INFO_ENTRY (0,                     OPTYPE_BOGUS|           AML_HAS_ARGS|   0,  "UNKNOWN_OP!",        ARG_NONE,               ARG_NONE),
            OP_INFO_ENTRY (0,                     0|                      AML_HAS_ARGS|   0,  NULL,                 ARG_NONE,               ARG_NONE)
};

#define _UNK                0x6A
#define _UNKNOWN_OPCODE     0x02    /* An example unknown opcode */

/*
 * This table is directly indexed by the opcodes, and returns an
 * index into the table above
 */

UINT8 Gbl_AmlOpInfoIndex[256] =
{
/*              0     1     2     3     4     5     6     7  */
/* 0x00 */    0x00, 0x01, _UNK, _UNK, _UNK, _UNK, 0x02, _UNK,
/* 0x08 */    0x03, _UNK, 0x04, 0x05, 0x06, 0x07, _UNK, _UNK,
/* 0x10 */    0x08, 0x09, 0x0a, _UNK, 0x0b, _UNK, _UNK, 0x46,
/* 0x18 */    0x47, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x20 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x28 */    0x48, 0x49, _UNK, _UNK, _UNK, 0x63, _UNK, _UNK,
/* 0x30 */    0x67, 0x66, 0x68, 0x65, 0x69, 0x64, 0x4a, 0x4b,
/* 0x38 */    0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53,
/* 0x40 */    0x54, _UNK, _UNK, _UNK, _UNK, _UNK, 0x55, 0x56,
/* 0x48 */    0x57, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x50 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x58 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x60 */    0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13,
/* 0x68 */    0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, _UNK,
/* 0x70 */    0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22,
/* 0x78 */    0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a,
/* 0x80 */    0x2b, 0x2c, 0x2d, 0x2e, _UNK, _UNK, 0x2f, 0x30,
/* 0x88 */    0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, _UNK,
/* 0x90 */    0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x58, 0x59,
/* 0x98 */    0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f, _UNK, _UNK,
/* 0xA0 */    0x3e, 0x3f, 0x40, 0x41, 0x42, 0x43, 0x60, 0x61,
/* 0xA8 */    0x62, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xB0 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xB8 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xC0 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xC8 */    _UNK, _UNK, _UNK, _UNK, 0x44, _UNK, _UNK, _UNK,
/* 0xD0 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xD8 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xE0 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xE8 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xF0 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xF8 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, 0x45,
};
