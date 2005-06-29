
%{
/******************************************************************************
 *
 * Module Name: aslcompiler.l - Flex input file
 *              $Revision: 1.45 $
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2002, Intel Corp.
 * All rights reserved.
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

//    \"([^\"]|(\\\"))*\"         { literal (); return STRING_LITERAL; }


#include <stdlib.h>
#include <string.h>
#include "aslcompiler.h"
#include "aslcompiler.y.h"
YYSTYPE AslCompilerlval;

/*
 * Generation:  Use the following command line:
 *
 * flex.exe -PAslCompiler -i -o$(InputPath).c $(InputPath)
 *
 * -i: Scanner must be case-insensitive
 */

#define _COMPONENT          ACPI_COMPILER
        MODULE_NAME         ("aslscan")
void
comment (void);
void
comment2 (void);
void
count (int type);
void
literal (void);
void
copy (void);

%}


LeadNameChar                [A-Za-z_]
DigitChar                   [0-9]
HexDigitChar                [A-Fa-f0-9]
RootChar                    [\\]
Nothing                     []

NameChar                    [A-Za-z_0-9]
NameSeg1                    {LeadNameChar}{NameChar}
NameSeg2                    {LeadNameChar}{NameChar}{NameChar}
NameSeg3                    {LeadNameChar}{NameChar}{NameChar}{NameChar}
NameSeg                     {LeadNameChar}|{NameSeg1}|{NameSeg2}|{NameSeg3}

NameString                  {RootChar}|{RootChar}{NamePath}|[\^]+{NamePath}|{NonEmptyNamePath}
NamePath                    {NonEmptyNamePath}?
NonEmptyNamePath            {NameSeg}{NamePathTail}*
NamePathTail                [.]{NameSeg}

%%

[ ]                         { count (0); }
[\n]                        { count (0); }
[ \t]                       { count (0); }


"/*"                        { comment(); }
"//"                        { comment2(); }

"\""                        { literal (); return STRING_LITERAL; }


0[xX]{HexDigitChar}+ |
{DigitChar}+                { AslCompilerlval.i = UtStrtoul64 ((char *) AslCompilertext, NULL, 0);
                                count (1); return (INTEGER); }

"Include"                   { count (1); return (INCLUDE); }
"#include"                  { count (1); return (INCLUDE_CSTYLE); }
"External"                  { count (1); return (EXTERNAL); }


"Ones"                      { count (1); return (ONES); }
"One"                       { count (1); return (ONE); }
"Zero"                      { count (1); return (ZERO); }
"Revision"                  { count (1); return (REVISION); }

"Offset"                    { count (1); return (OFFSET); }
"AccessAs"                  { count (1); return (ACCESSAS); }
"BankField"                 { count (2); return (BANKFIELD); }
"CreateBitField"            { count (2); return (CREATEBITFIELD); }
"CreateByteField"           { count (2); return (CREATEBYTEFIELD); }
"CreateDWordField"          { count (2); return (CREATEDWORDFIELD); }
"CreateField"               { count (2); return (CREATEFIELD); }
"CreateQWordField"          { count (2); return (CREATEQWORDFIELD); }
"CreateWordField"           { count (2); return (CREATEWORDFIELD); }
"DataTableRegion"           { count (2); return (DATATABLEREGION); }
"Device"                    { count (2); return (DEVICE); }
"Event"                     { count (2); return (EVENT); }
"Field"                     { count (2); return (FIELD); }
"IndexField"                { count (2); return (INDEXFIELD); }
"Method"                    { count (2); return (METHOD); }
"Mutex"                     { count (2); return (MUTEX); }
"OperationRegion"           { count (2); return (OPERATIONREGION); }
"PowerResource"             { count (2); return (POWERRESOURCE); }
"Processor"                 { count (2); return (PROCESSOR); }
"ThermalZone"               { count (2); return (THERMALZONE); }
"Alias"                     { count (2); return (ALIAS); }
"Name"                      { count (2); return (NAME); }
"Scope"                     { count (2); return (SCOPE); }
"Break"                     { count (3); return (BREAK); }
"BreakPoint"                { count (3); return (BREAKPOINT); }
"Continue"                  { count (3); return (CONTINUE); }
"Fatal"                     { count (3); return (FATAL); }
"If"                        { count (3); return (IF); }
"Else"                      { count (3); return (ELSE); }
"ElseIf"                    { count (3); return (ELSEIF); }
"Load"                      { count (3); return (LOAD); }
"Noop"                      { count (3); return (NOOP); }
"Notify"                    { count (3); return (NOTIFY); }
"Release"                   { count (3); return (RELEASE); }
"Reset"                     { count (3); return (RESET); }
"Return"                    { count (3); return (RETURN); }
"Signal"                    { count (3); return (SIGNAL); }
"Sleep"                     { count (3); return (SLEEP); }
"Stall"                     { count (3); return (STALL); }
"Switch"                    { count (3); return (SWITCH); }
"Case"                      { count (3); return (CASE); }
"Default"                   { count (3); return (DEFAULT); }
"Unload"                    { count (3); return (UNLOAD); }
"While"                     { count (3); return (WHILE); }

"Acquire"                   { count (3); return (ACQUIRE); }
"Add"                       { count (3); return (ADD); }
"And"                       { count (3); return (AND); }
"Concatenate"               { count (3); return (CONCATENATE); }
"ConcatenateResTemplate"    { count (3); return (CONCATENATERESTEMPLATE); }
"CondRefOf"                 { count (3); return (CONDREFOF); }
"CopyObject"                { count (3); return (COPYOBJECT); }
"Decrement"                 { count (3); return (DECREMENT); }
"DeRefOf"                   { count (3); return (DEREFOF); }
"Divide"                    { count (3); return (DIVIDE); }
"FindSetLeftBit"            { count (3); return (FINDSETLEFTBIT); }
"FindSetRightBit"           { count (3); return (FINDSETRIGHTBIT); }
"FromBCD"                   { count (3); return (FROMBCD); }
"Increment"                 { count (3); return (INCREMENT); }
"Index"                     { count (3); return (INDEX); }
"LAnd"                      { count (3); return (LAND); }
"LEqual"                    { count (3); return (LEQUAL); }
"LGreater"                  { count (3); return (LGREATER); }
"LGreaterEqual"             { count (3); return (LGREATEREQUAL); }
"LLess"                     { count (3); return (LLESS); }
"LLessEqual"                { count (3); return (LLESSEQUAL); }
"LNot"                      { count (3); return (LNOT); }
"LNotEqual"                 { count (3); return (LNOTEQUAL); }
"LoadTable"                 { count (3); return (LOADTABLE); }
"LOr"                       { count (3); return (LOR); }
"Match"                     { count (3); return (MATCH); }
"Mid"                       { count (3); return (MID); }
"Mod"                       { count (3); return (MOD); }
"Multiply"                  { count (3); return (MULTIPLY); }
"NAnd"                      { count (3); return (NAND); }
"NOr"                       { count (3); return (NOR); }
"Not"                       { count (3); return (NOT); }
"ObjectType"                { count (3); return (OBJECTTYPE); }
"Or"                        { count (3); return (OR); }
"RefOf"                     { count (3); return (REFOF); }
"ShiftLeft"                 { count (3); return (SHIFTLEFT); }
"ShiftRight"                { count (3); return (SHIFTRIGHT); }
"SizeOf"                    { count (3); return (SIZEOF); }
"Store"                     { count (3); return (STORE); }
"Subtract"                  { count (3); return (SUBTRACT); }
"ToBCD"                     { count (3); return (TOBCD); }
"ToBuffer"                  { count (3); return (TOBUFFER); }
"ToDecimalString"           { count (3); return (TODECIMALSTRING); }
"ToHexString"               { count (3); return (TOHEXSTRING); }
"ToInteger"                 { count (3); return (TOINTEGER); }
"ToString"                  { count (3); return (TOSTRING); }
"Wait"                      { count (3); return (WAIT); }
"XOr"                       { count (3); return (XOR); }

"Arg0"                      { count (1); return (ARG0); }
"Arg1"                      { count (1); return (ARG1); }
"Arg2"                      { count (1); return (ARG2); }
"Arg3"                      { count (1); return (ARG3); }
"Arg4"                      { count (1); return (ARG4); }
"Arg5"                      { count (1); return (ARG5); }
"Arg6"                      { count (1); return (ARG6); }

"Local0"                    { count (1); return (LOCAL0); }
"Local1"                    { count (1); return (LOCAL1); }
"Local2"                    { count (1); return (LOCAL2); }
"Local3"                    { count (1); return (LOCAL3); }
"Local4"                    { count (1); return (LOCAL4); }
"Local5"                    { count (1); return (LOCAL5); }
"Local6"                    { count (1); return (LOCAL6); }
"Local7"                    { count (1); return (LOCAL7); }

"Debug"                     { count (1); return (DEBUG); }

"DefinitionBlock"           { count (1); return (DEFINITIONBLOCK); }
"Buffer"                    { count (1); return (BUFFER); }
"Package"                   { count (1); return (PACKAGE); }

"EISAID"                    { count (1); return (EISAID); }
"ResourceTemplate"          { count (1); return (RESOURCETEMPLATE); }
"Unicode"                   { count (1); return (UNICODE); }
"DMA"                       { count (1); return (DMA); }
"DWordIO"                   { count (1); return (DWORDIO); }
"DWordMemory"               { count (1); return (DWORDMEMORY); }
"EndDependentFn"            { count (1); return (ENDDEPENDENTFN); }
"FixedIO"                   { count (1); return (FIXEDIO); }
"Interrupt"                 { count (1); return (INTERRUPT); }
"IO"                        { count (1); return (IO); }
"IRQNoFlags"                { count (1); return (IRQNOFLAGS); }
"IRQ"                       { count (1); return (IRQ); }
"Memory24"                  { count (1); return (MEMORY24); }
"Memory32Fixed"             { count (1); return (MEMORY32FIXED); }
"Memory32"                  { count (1); return (MEMORY32); }
"QWordIO"                   { count (1); return (QWORDIO); }
"QWordMemory"               { count (1); return (QWORDMEMORY); }
"Register"                  { count (1); return (REGISTER); }
"StartDependentFn"          { count (1); return (STARTDEPENDENTFN); }
"StartDependentFnNoPri"     { count (1); return (STARTDEPENDENTFN_NOPRI); }
"VendorLong"                { count (1); return (VENDORLONG); }
"VendorShort"               { count (1); return (VENDORSHORT); }
"WordBusNumber"             { count (1); return (WORDBUSNUMBER); }
"WordIO"                    { count (1); return (WORDIO); }

"UnknownObj"                { count (0); return (OBJECTTYPE_UNK); }
"IntObj"                    { count (0); return (OBJECTTYPE_INT); }
"StrObj"                    { count (0); return (OBJECTTYPE_STR); }
"BuffObj"                   { count (0); return (OBJECTTYPE_BUF); }
"PkgObj"                    { count (0); return (OBJECTTYPE_PKG); }
"FieldUnitObj"              { count (0); return (OBJECTTYPE_FLD); }
"DeviceObj"                 { count (0); return (OBJECTTYPE_DEV); }
"EventObj"                  { count (0); return (OBJECTTYPE_EVT); }
"MethodObj"                 { count (0); return (OBJECTTYPE_MTH); }
"MutexObj"                  { count (0); return (OBJECTTYPE_MTX); }
"OpRegionObj"               { count (0); return (OBJECTTYPE_OPR); }
"PowerResObj"               { count (0); return (OBJECTTYPE_POW); }
"ThermalZoneObj"            { count (0); return (OBJECTTYPE_THZ); }
"BuffFieldObj"              { count (0); return (OBJECTTYPE_BFF); }
"DDBHandleObj"              { count (0); return (OBJECTTYPE_DDB); }

"AnyAcc"                    { count (0); return (ACCESSTYPE_ANY); }
"ByteAcc"                   { count (0); return (ACCESSTYPE_BYTE); }
"WordAcc"                   { count (0); return (ACCESSTYPE_WORD); }
"DWordAcc"                  { count (0); return (ACCESSTYPE_DWORD); }
"QWordAcc"                  { count (0); return (ACCESSTYPE_QWORD); }
"BufferAcc"                 { count (0); return (ACCESSTYPE_BUF); }

"Lock"                      { count (0); return (LOCKRULE_LOCK); }
"NoLock"                    { count (0); return (LOCKRULE_NOLOCK); }

"Preserve"                  { count (0); return (UPDATERULE_PRESERVE); }
"WriteAsOnes"               { count (0); return (UPDATERULE_ONES); }
"WriteAsZeros"              { count (0); return (UPDATERULE_ZEROS); }

"Serialized"                { count (0); return (SERIALIZERULE_SERIAL); }
"NotSerialized"             { count (0); return (SERIALIZERULE_NOTSERIAL); }

"SystemIO"                  { count (0); return (REGIONSPACE_IO); }
"SystemMemory"              { count (0); return (REGIONSPACE_MEM); }
"PCI_Config"                { count (0); return (REGIONSPACE_PCI); }
"EmbeddedControl"           { count (0); return (REGIONSPACE_EC); }
"SMBus"                     { count (0); return (REGIONSPACE_SMBUS); }
"SystemCMOS"                { count (0); return (REGIONSPACE_CMOS); }
"PciBarTarget"              { count (0); return (REGIONSPACE_PCIBAR); }

"FFixedHW"                  { count (0); return (ADDRESSSPACE_FFIXEDHW); }

"SMBQuick"                  { count (0); return (ACCESSATTRIB_QUICK); }
"SMBSendReceive"            { count (0); return (ACCESSATTRIB_SND_RCV); }
"SMBByte"                   { count (0); return (ACCESSATTRIB_BYTE); }
"SMBWord"                   { count (0); return (ACCESSATTRIB_WORD); }
"SMBBlock"                  { count (0); return (ACCESSATTRIB_BLOCK); }
"SMBProcessCall"            { count (0); return (ACCESSATTRIB_CALL); }

"MTR"                       { count (0); return (MATCHTYPE_MTR); }
"MEQ"                       { count (0); return (MATCHTYPE_MEQ); }
"MLE"                       { count (0); return (MATCHTYPE_MLE); }
"MLT"                       { count (0); return (MATCHTYPE_MLT); }
"MGE"                       { count (0); return (MATCHTYPE_MGE); }
"MGT"                       { count (0); return (MATCHTYPE_MGT); }

"Compatibility"             { count (0); return (DMATYPE_COMPATIBILITY); }
"TypeA"                     { count (0); return (DMATYPE_A); }
"TypeB"                     { count (0); return (DMATYPE_B); }
"TypeF"                     { count (0); return (DMATYPE_F); }

"BusMaster"                 { count (0); return (BUSMASTERTYPE_MASTER); }
"NotBusMaster"              { count (0); return (BUSMASTERTYPE_NOTMASTER); }

"Transfer8"                 { count (0); return (XFERTYPE_8); }
"Transfer8_16"              { count (0); return (XFERTYPE_8_16); }
"Transfer16"                { count (0); return (XFERTYPE_16); }

"ResourceConsumer"          { count (0); return (RESOURCETYPE_CONSUMER); }
"ResourceProducer"          { count (0); return (RESOURCETYPE_PRODUCER); }

"MinFixed"                  { count (0); return (MINTYPE_FIXED); }
"MinNotFixed"               { count (0); return (MINTYPE_NOTFIXED); }

"MaxFixed"                  { count (0); return (MAXTYPE_FIXED); }
"MaxNotFixed"               { count (0); return (MAXTYPE_NOTFIXED); }

"PosDecode"                 { count (0); return (DECODETYPE_POS); }
"SubDecode"                 { count (0); return (DECODETYPE_SUB); }

"ISAOnlyRanges"             { count (0); return (RANGETYPE_ISAONLY); }
"NonISAOnlyRanges"          { count (0); return (RANGETYPE_NONISAONLY); }
"EntireRange"               { count (0); return (RANGETYPE_ENTIRE); }

"Cacheable"                 { count (0); return (MEMTYPE_CACHEABLE); }
"WriteCombining"            { count (0); return (MEMTYPE_WRITECOMBINING); }
"Prefetchable"              { count (0); return (MEMTYPE_PREFETCHABLE); }
"NonCacheable"              { count (0); return (MEMTYPE_NONCACHEABLE); }

"ReadWrite"                 { count (0); return (READWRITETYPE_BOTH); }
"ReadOnly"                  { count (0); return (READWRITETYPE_READONLY); }

"Edge"                      { count (0); return (INTTYPE_EDGE); }
"Level"                     { count (0); return (INTTYPE_LEVEL); }

"ActiveHigh"                { count (0); return (INTLEVEL_ACTIVEHIGH); }
"ActiveLow"                 { count (0); return (INTLEVEL_ACTIVELOW); }

"Shared"                    { count (0); return (SHARETYPE_SHARED); }
"Exclusive"                 { count (0); return (SHARETYPE_EXCLUSIVE); }

"Decode10"                  { count (0); return (IODECODETYPE_10); }
"Decode16"                  { count (0); return (IODECODETYPE_16); }

"TypeTranslation"           { count (0); return (TYPE_TRANSLATION); }
"TypeStatic"                { count (0); return (TYPE_STATIC); }

"SparseTranslation"         { count (0); return (TRANSLATIONTYPE_SPARSE); }
"DenseTranslation"          { count (0); return (TRANSLATIONTYPE_DENSE); }

"AddressRangeMemory"        { count (0); return (ADDRESSTYPE_MEMORY); }
"AddressRangeReserved"      { count (0); return (ADDRESSTYPE_RESERVED); }
"AddressRangeNVS"           { count (0); return (ADDRESSTYPE_NVS); }
"AddressRangeACPI"          { count (0); return (ADDRESSTYPE_ACPI); }


"{"                         { count (0); return('{'); }
"}"                         { count (0); return('}'); }
","                         { count (0); return(','); }
"("                         { count (0); return('('); }
")"                         { count (0); return(')'); }


{NameSeg}                   { char *s;
                                count (0);
                                s=malloc (ACPI_NAME_SIZE + 1);
                                if (strcmp (AslCompilertext, "\\"))
                                {
                                    strcpy (s, "____");
                                    STRUPR (AslCompilertext);
                                }
                                memcpy (s, AslCompilertext, strlen (AslCompilertext));
                                AslCompilerlval.s = s;
                                DbgPrint (ASL_PARSE_OUTPUT, "NameSeg: %s\n", s);
                                return (NAMESEG); }

{NameString}                { char *s;
                                count (0);
                                s=malloc (strlen (AslCompilertext)+1);
                                STRUPR (AslCompilertext);
                                strcpy (s, AslCompilertext);
                                s[strlen (AslCompilertext)] = 0;
                                AslCompilerlval.s = s;
                                DbgPrint (ASL_PARSE_OUTPUT, "NameString: %s\n", s);
                                return (NAMESTRING); }

"*" |
"/"                         { count (1);
                                AslCompilererror ("Parse error, expecting ASL keyword or name");}

.                           { count (1);
                                AslCompilererror ("Invalid character, expecting ASL keyword or name");}

<<EOF>>                     { if (AslPopInputFileStack ())
                                yyterminate();
                              else
                                return (INCLUDE_END);};

%%


typedef struct asl_file_node
{
    FILE                    *File;
    UINT32                  CurrentLineNumber;
    YY_BUFFER_STATE         State;
    char                    *Filename;
    struct asl_file_node    *Next;

} ASL_FILE_NODE;

ASL_FILE_NODE               *InputStack = NULL;


/*******************************************************************************
 *
 * FUNCTION:    AslPopInputFileStack
 *
 * PARAMETERS:  None
 *
 * RETURN:      0 if a node was popped, -1 otherwise
 *
 * DESCRIPTION: Pop the top of the input file stack and point the parser to
 *              the saved parse buffer contained in the fnode.  Also, set the
 *              global line counters to the saved values.  This function is
 *              called when an include file reaches EOF.
 *
 ******************************************************************************/

int
AslPopInputFileStack (void)
{
    ASL_FILE_NODE           *Fnode;
    FILE                    *InputFile = NULL;


    Fnode = InputStack;
    DbgPrint (ASL_PARSE_OUTPUT, "\nPop InputFile Stack, Fnode %p\n\n", Fnode);


    if (!Fnode)
    {
        return -1;
    }

    /* Close the current include file */

    fclose (yyin);

    /* Update the top-of-stack */

    InputStack = Fnode->Next;
    InputFile = Fnode->File;

    /* Reset global line counter and filename */

    Gbl_Files[ASL_FILE_INPUT].Filename = Fnode->Filename;
    Gbl_CurrentLineNumber = Fnode->CurrentLineNumber;

    /* Point the parser to the popped file */

    yy_delete_buffer (YY_CURRENT_BUFFER);
    yy_switch_to_buffer (Fnode->State);

    /* All done with this node */

    ACPI_MEM_FREE (Fnode);
    return 0;
}


/*******************************************************************************
 *
 * FUNCTION:    AslPushInputFileStack
 *
 * PARAMETERS:  InputFile           - Open file pointer
 *              Filename            - Name of the file
 *
 * RETURN:      None
 *
 * DESCRIPTION: Push the InputFile onto the file stack, and point the parser
 *              to this file.  Called when an include file is successfully
 *              opened.
 *
 ******************************************************************************/

void
AslPushInputFileStack (
    FILE                    *InputFile,
    char                    *Filename)
{
    ASL_FILE_NODE           *Fnode;
    YY_BUFFER_STATE         State;


    /* Save the current state in an Fnode */

    Fnode = UtLocalCalloc (sizeof (ASL_FILE_NODE));

    Fnode->File                 = yyin;
    Fnode->Next                 = InputStack;
    Fnode->State                = YY_CURRENT_BUFFER;
    Fnode->CurrentLineNumber    = Gbl_CurrentLineNumber;
    Fnode->Filename             = Gbl_Files[ASL_FILE_INPUT].Filename;

    /* Push it on the stack */

    InputStack = Fnode;

    /* Point the parser to this file */

    State = yy_create_buffer (InputFile, YY_BUF_SIZE);
    yy_switch_to_buffer (State);

    DbgPrint (ASL_PARSE_OUTPUT, "\nPush InputFile Stack, returning %p\n\n", InputFile);

    /* Reset the global line count and filename */

    Gbl_Files[ASL_FILE_INPUT].Filename = Filename;
    Gbl_CurrentLineNumber = 1;
    yyin = InputFile;
}


/*******************************************************************************
 *
 * FUNCTION:    ResetCurrentLineBuffer
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Reset the Line Buffer to zero, increment global line numbers.
 *
 ******************************************************************************/

void
ResetCurrentLineBuffer (
    void)
{

    if (Gbl_Files[ASL_FILE_SOURCE_OUTPUT].Handle)
    {
        FlWriteFile (ASL_FILE_SOURCE_OUTPUT, Gbl_CurrentLineBuffer,
            Gbl_LineBufPtr - Gbl_CurrentLineBuffer);
    }

    Gbl_InputByteCount++; /* Account for the CR/linefeed */
    Gbl_CurrentLineOffset += Gbl_CurrentColumn + 1;

    Gbl_CurrentColumn = 0;

    Gbl_CurrentLineNumber++;
    Gbl_LogicalLineNumber++;
    Gbl_LineBufPtr = Gbl_CurrentLineBuffer;
}


/*******************************************************************************
 *
 * FUNCTION:    InsertLineBuffer
 *
 * PARAMETERS:  SourceChar      - One char from the input ASL source file
 *
 * RETURN:      None
 *
 * DESCRIPTION: Put one character of the source file into the temp line buffer
 *
 ******************************************************************************/

#define ASL_SPACES_PER_TAB  4

void
InsertLineBuffer (
    int                     SourceChar)
{
    UINT32                  i;
    UINT32                  Count = 1;


    if (SourceChar == EOF)
    {
        return;
    }

    Gbl_InputByteCount++;

    /* Handle tabs.  Convert to spaces */

    if (SourceChar == '\t')
    {
        SourceChar = ' ';
        Count = ASL_SPACES_PER_TAB -
                    (Gbl_CurrentColumn & (ASL_SPACES_PER_TAB-1));
    }


    for (i = 0; i < Count; i++)
    {
        Gbl_CurrentColumn++;

        /* Insert the character into the line buffer */

        *Gbl_LineBufPtr = (UINT8) SourceChar;
        Gbl_LineBufPtr++;

        if (Gbl_LineBufPtr > (Gbl_CurrentLineBuffer + (ASL_LINE_BUFFER_SIZE - 1)))
        {
            sprintf (MsgBuffer, "Max %d", ASL_LINE_BUFFER_SIZE);
            AslCommonError (ASL_WARNING, ASL_MSG_LONG_LINE,
                            Gbl_CurrentLineNumber, Gbl_LogicalLineNumber,
                            Gbl_CurrentLineOffset, Gbl_CurrentColumn,
                            Gbl_Files[ASL_FILE_INPUT].Filename, MsgBuffer);


            ResetCurrentLineBuffer ();
        }
        else if (SourceChar == '\n')
        {
            /* End of line */

            ResetCurrentLineBuffer ();
        }
    }
}


/*******************************************************************************
 *
 * FUNCTION:    count
 *
 * PARAMETERS:  yytext      - Contains the matched keyword.
 *              Type        - Keyword/Character type:
 *                             0 = anything except a keyword
 *                             1 = pseudo-keywords
 *                             2 = non-executable ASL keywords
 *                             3 = executable ASL keywords
 *
 * RETURN:      None
 *
 * DESCRIPTION: Count keywords and put them into the line buffer
 *
 ******************************************************************************/

void
count (
    int                 Type)
{
    int                 i;


    switch (Type)
    {
    case 2:
        TotalKeywords++;
        TotalNamedObjects++;
        break;

    case 3:
        TotalKeywords++;
        TotalExecutableOpcodes++;
        break;
    }

    for (i = 0; (yytext[i] != 0) && (yytext[i] != EOF); i++)
    {
        InsertLineBuffer (yytext[i]);
        *Gbl_LineBufPtr = 0;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    comment
 *
 * PARAMETERS:  none
 *
 * RETURN:      none
 *
 * DESCRIPTION: Process a standard comment.
 *
 ******************************************************************************/

void
comment (void)
{
    char                c;
    char                c1 = 0;


    InsertLineBuffer ('/');
    InsertLineBuffer ('*');

loop:

    /* Eat chars until end-of-comment */

    while ((c = (char) input()) != '*' && c != EOF)
    {
        InsertLineBuffer (c);
        c1 = c;
    }

    /*
     * Check for nested comment -- can help catch cases where a previous
     * comment was accidently left unterminated
     */
    if ((c1 == '/') && (c == '*'))
    {
        AslCommonError (ASL_WARNING, ASL_MSG_NESTED_COMMENT,
                        Gbl_CurrentLineNumber, Gbl_LogicalLineNumber,
                        Gbl_InputByteCount, Gbl_CurrentColumn,
                        Gbl_Files[ASL_FILE_INPUT].Filename, NULL);
    }

    /* Comment is closed only if the NEXT character is a slash */

    InsertLineBuffer (c);

    if ((c1 = (char) input()) != '/' && c1 != EOF)
    {
        unput(c1);
        goto loop;
    }

    InsertLineBuffer (c1);
}


/*******************************************************************************
 *
 * FUNCTION:    comment
 *
 * PARAMETERS:  none
 *
 * RETURN:      none
 *
 * DESCRIPTION: Process a new "//" comment.
 *
 ******************************************************************************/

void
comment2 (void)
{
    char                c;


    InsertLineBuffer ('/');
    InsertLineBuffer ('/');

    while ((c = (char) input()) != '\n' && c != EOF)
    {
        InsertLineBuffer (c);
    }

    InsertLineBuffer (c);
}


/*******************************************************************************
 *
 * FUNCTION:    literal
 *
 * PARAMETERS:  none
 *
 * RETURN:      none
 *
 * DESCRIPTION: Process a string literal (surrounded by quotes)
 *
 ******************************************************************************/

#define ASL_NORMAL_CHAR         0
#define ASL_ESCAPE_SEQUENCE     1
#define ASL_OCTAL_CONSTANT      2
#define ASL_HEX_CONSTANT        3

void
literal (void)
{
    char                *s = MsgBuffer;
    char                *CleanString;
    char                StringChar;
    UINT32              State = ASL_NORMAL_CHAR;
    UINT32              i;
    char                ConvertBuffer[4];


    /*
     * Eat chars until end-of-literal.
     * NOTE:  Put back the original surrounding quotes into the
     * source line buffer.
     */
    InsertLineBuffer ('\"');
    while ((StringChar = (char) input()) != EOF)
    {
        InsertLineBuffer (StringChar);

DoCharacter:

        switch (State)
        {
        case ASL_NORMAL_CHAR:

            switch (StringChar)
            {
            case '\\':
                /*
                 * Special handling for backslash-escape sequence.  We will
                 * toss the backslash and translate the escape char(s).
                 */
                State = ASL_ESCAPE_SEQUENCE;
                continue;

            case '\"':

                /* String terminator */

                goto CompletedString;
            }
            break;


        case ASL_ESCAPE_SEQUENCE:

            State = ASL_NORMAL_CHAR;
            switch (StringChar)
            {
            case 'a':
                StringChar = 0x07;      /* BELL */
                break;

            case 'b':
                StringChar = 0x08;      /* BACKSPACE */
                break;

            case 'f':
                StringChar = 0x0C;      /* FORMFEED */
                break;

            case 'n':
                StringChar = 0x0A;      /* LINEFEED */
                break;

            case 'r':
                StringChar = 0x0D;      /* CARRIAGE RETURN*/
                break;

            case 't':
                StringChar = 0x09;      /* HORIZONTAL TAB */
                break;

            case 'v':
                StringChar = 0x0B;      /* VERTICAL TAB */
                break;

            case 'x':
                State = ASL_HEX_CONSTANT;
                i = 0;
                continue;

            case '\'':                  /* Single Quote */
            case '\"':                  /* Double Quote */
            case '\\':                  /* Backslash */
                break;

            default:
            
                /* Check for an octal digit (0-7) */

                if (IS_OCTAL_DIGIT (StringChar))
                {
                    State = ASL_OCTAL_CONSTANT;
                    ConvertBuffer[0] = StringChar;
                    i = 1;
                    continue;
                }

                /* Unknown escape sequence */

                AslCommonError (ASL_ERROR, ASL_MSG_INVALID_ESCAPE,
                                Gbl_CurrentLineNumber, Gbl_LogicalLineNumber,
                                Gbl_CurrentLineOffset, Gbl_CurrentColumn,
                                Gbl_Files[ASL_FILE_INPUT].Filename, NULL);
                continue;
            }
            break;


        case ASL_OCTAL_CONSTANT:

            /* Up to three octal digits allowed */

            if (!IS_OCTAL_DIGIT (StringChar) ||
                (i > 2))
            {
                /*
                 * Reached end of the constant.  Convert the assembled ASCII
                 * string and resume processing of the next character
                 */
                ConvertBuffer[i] = 0;
                *s = (char) STRTOUL (ConvertBuffer, NULL, 8);
                s++;

                State = ASL_NORMAL_CHAR;
                goto DoCharacter;
                break;
            }

            /* Append another digit of the constant */

            ConvertBuffer[i] = StringChar;
            i++;
            continue;


        case ASL_HEX_CONSTANT:

            /* Up to two hex digits allowed */

            if (!IS_XDIGIT (StringChar) ||
                (i > 1))
            {
                /*
                 * Reached end of the constant.  Convert the assembled ASCII
                 * string and resume processing of the next character
                 */
                ConvertBuffer[i] = 0;
                *s = (char) STRTOUL (ConvertBuffer, NULL, 16);
                s++;

                State = ASL_NORMAL_CHAR;
                goto DoCharacter;
                break;
            }

            /* Append another digit of the constant */

            ConvertBuffer[i] = StringChar;
            i++;
            continue;
        }

        /* Save the finished character */

        *s = StringChar;
        s++;
    }


CompletedString:
    /*
     * Null terminate the input string and copy string to a new buffer
     */
    *s = 0;

    CleanString = UtGetStringBuffer (strlen (MsgBuffer) + 1);
    if (!CleanString)
    {
        AslCommonError (ASL_ERROR, ASL_MSG_MEMORY_ALLOCATION,
                        Gbl_CurrentLineNumber, Gbl_LogicalLineNumber,
                        Gbl_CurrentLineOffset, Gbl_CurrentColumn,
                        Gbl_Files[ASL_FILE_INPUT].Filename, NULL);
        return;
    }

    STRCPY (CleanString, MsgBuffer);
    AslCompilerlval.s = CleanString;
}


