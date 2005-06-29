
%{
/******************************************************************************
 *
 * Module Name: aslcompiler.l - Flex input file
 *              $Revision: 1.10 $
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

#include <stdlib.h>
#include <string.h>
#include "AslCompiler.y.h"
#include "AslCompiler.h"
YYSTYPE AslCompilerlval;

/*
 * Generation:  Use the following command line:
 *
 * flex.exe -PAslCompiler -i -o$(InputPath).c $(InputPath)
 *
 * -i: Scanner must be case-insensitive
 */



#undef xxYY_INPUT
#define xxYY_INPUT(buf,result,max_size) \
	   if ( ((result = fread( buf, 1, max_size, yyin )) == 0) \
		    && ferror( yyin ) ) \
        {\
		    YY_FATAL_ERROR( "input in flex scanner failed" );\
        }\
        else if (Gbl_SourceOutputFile)\
        {\
            fwrite (buf, result, 1, Gbl_SourceOutputFile);\
        }


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



LeadNameChar        [A-Za-z_]
DigitChar           [0-9]
HexDigitChar        [A-Fa-f0-9]
RootChar            [\\]
Nothing             []

NameChar            [A-Za-z_0-9]
NameSeg1            {LeadNameChar}{NameChar}
NameSeg2            {LeadNameChar}{NameChar}{NameChar}
NameSeg3            {LeadNameChar}{NameChar}{NameChar}{NameChar}
NameSeg             {LeadNameChar}|{NameSeg1}|{NameSeg2}|{NameSeg3}

NameString          {RootChar}|{RootChar}{NamePath}|[\^]+{NamePath}|{NonEmptyNamePath}
NamePath            {NonEmptyNamePath}?
NonEmptyNamePath    {NameSeg}{NamePathTail}*
NamePathTail        [.]{NameSeg}  

%%

[ ]                         { copy(); count (0); }
[\n]                        { copy(); count (0); }
[ \t]                       { copy(); count (0); }



"/*"			            { copy(); comment(); }
"//"                        { copy(); comment2(); }

\"([^\"]|(\\\"))*\"	        { literal (); return STRING_LITERAL; }


0[xX]{HexDigitChar}+ |
{DigitChar}+                { AslCompilerlval.l = strtoul((char *)AslCompilertext, (char **) 0, 0);
                                copy(); count (1); 
                                return (INTEGER); }

"Include"                   { copy(); count (1); return (INCLUDE); }
"#include"                  { copy(); count (1); return (INCLUDE_CSTYLE); }


"Ones"                      { copy(); count (1); return (ONES); }
"One"                       { copy(); count (1); return (ONE); }
"Zero"                      { copy(); count (1); return (ZERO); }
                                
"Offset"                    { copy(); count (1); return (OFFSET); }
"AccessAs"                  { copy(); count (1); return (ACCESSAS); }
"BankField"                 { copy(); count (2); return (BANKFIELD); }
"CreateBitField"            { copy(); count (2); return (CREATEBITFIELD); }
"CreateByteField"           { copy(); count (2); return (CREATEBYTEFIELD); }
"CreateDWordField"          { copy(); count (2); return (CREATEDWORDFIELD); }
"CreateField"               { copy(); count (2); return (CREATEFIELD); }
"CreateQWordField"          { copy(); count (2); return (CREATEQWORDFIELD); }
"CreateWordField"           { copy(); count (2); return (CREATEWORDFIELD); }
"DataTableRegion"           { copy(); count (2); return (DATATABLEREGION); }
"Device"                    { copy(); count (2); return (DEVICE); }
"Event"                     { copy(); count (2); return (EVENT); }
"Field"                     { copy(); count (2); return (FIELD); }
"IndexField"                { copy(); count (2); return (INDEXFIELD); }
"Method"                    { copy(); count (2); return (METHOD); }
"Mutex"                     { copy(); count (2); return (MUTEX); }
"OperationRegion"           { copy(); count (2); return (OPERATIONREGION); }
"PowerResource"             { copy(); count (2); return (POWERRESOURCE); }
"Processor"                 { copy(); count (2); return (PROCESSOR); }
"ThermalZone"               { copy(); count (2); return (THERMALZONE); }
"Alias"                     { copy(); count (2); return (ALIAS); }
"Name"                      { copy(); count (2); return (NAME); }
"Scope"                     { copy(); count (2); return (SCOPE); }
"Break"                     { copy(); count (3); return (BREAK); }
"BreakPoint"                { copy(); count (3); return (BREAKPOINT); }
"Continue"                  { copy(); count (3); return (CONTINUE); }
"Fatal"                     { copy(); count (3); return (FATAL); }
"If"                        { copy(); count (3); return (IF); }
"Else"                      { copy(); count (3); return (ELSE); }
"ElseIf"                    { copy(); count (3); return (ELSEIF); }
"Load"                      { copy(); count (3); return (LOAD); }
"Noop"                      { copy(); count (3); return (NOOP); }
"Notify"                    { copy(); count (3); return (NOTIFY); }
"Release"                   { copy(); count (3); return (RELEASE); }
"Reset"                     { copy(); count (3); return (RESET); }
"Return"                    { copy(); count (3); return (RETURN); }
"Signal"                    { copy(); count (3); return (SIGNAL); }
"Sleep"                     { copy(); count (3); return (SLEEP); }
"Stall"                     { copy(); count (3); return (STALL); }
"Switch"                    { copy(); count (3); return (SWITCH); }
"Case"                      { copy(); count (3); return (CASE); }
"Default"                   { copy(); count (3); return (DEFAULT); }
"Unload"                    { copy(); count (3); return (UNLOAD); }
"While"                     { copy(); count (3); return (WHILE); }

"Acquire"                   { copy(); count (3); return (ACQUIRE); }
"Add"                       { copy(); count (3); return (ADD); }
"And"                       { copy(); count (3); return (AND); }
"Concatenate"               { copy(); count (3); return (CONCATENATE); }
"ConcatenateResTemplate"    { copy(); count (3); return (CONCATENATERESTEMPLATE); }
"CondRefOf"                 { copy(); count (3); return (CONDREFOF); }
"Copy"                      { copy(); count (3); return (COPY); }
"Decrement"                 { copy(); count (3); return (DECREMENT); }
"DeRefOf"                   { copy(); count (3); return (DEREFOF); }
"Divide"                    { copy(); count (3); return (DIVIDE); }
"FindSetLeftBit"            { copy(); count (3); return (FINDSETLEFTBIT); }
"FindSetRightBit"           { copy(); count (3); return (FINDSETRIGHTBIT); }
"FromBCD"                   { copy(); count (3); return (FROMBCD); }
"Increment"                 { copy(); count (3); return (INCREMENT); }
"Index"                     { copy(); count (3); return (INDEX); }
"LAnd"                      { copy(); count (3); return (LAND); }
"LEqual"                    { copy(); count (3); return (LEQUAL); }
"LGreater"                  { copy(); count (3); return (LGREATER); }
"LGreaterEqual"             { copy(); count (3); return (LGREATEREQUAL); }
"LLess"                     { copy(); count (3); return (LLESS); }
"LLessEqual"                { copy(); count (3); return (LLESSEQUAL); }
"LNot"                      { copy(); count (3); return (LNOT); }
"LNotEqual"                 { copy(); count (3); return (LNOTEQUAL); }
"LoadTable"                 { copy(); count (3); return (LOADTABLE); }
"LOr"                       { copy(); count (3); return (LOR); }
"Match"                     { copy(); count (3); return (MATCH); }
"Mid"                       { copy(); count (3); return (MID); }
"Mod"                       { copy(); count (3); return (MOD); }
"Multiply"                  { copy(); count (3); return (MULTIPLY); }
"NAnd"                      { copy(); count (3); return (NAND); }
"NOr"                       { copy(); count (3); return (NOR); }
"Not"                       { copy(); count (3); return (NOT); }
"ObjectType"                { copy(); count (3); return (OBJECTTYPE); }
"Or"                        { copy(); count (3); return (OR); }
"RefOf"                     { copy(); count (3); return (REFOF); }
"ShiftLeft"                 { copy(); count (3); return (SHIFTLEFT); }
"ShiftRight"                { copy(); count (3); return (SHIFTRIGHT); }
"SizeOf"                    { copy(); count (3); return (SIZEOF); }
"Store"                     { copy(); count (3); return (STORE); }
"String"                    { copy(); count (3); return (STRING); }
"Subtract"                  { copy(); count (3); return (SUBTRACT); }
"ToBCD"                     { copy(); count (3); return (TOBCD); }
"ToBuffer"                  { copy(); count (3); return (TOBUFFER); }
"ToDecimalString"           { copy(); count (3); return (TODECIMALSTRING); }
"ToHexString"               { copy(); count (3); return (TOHEXSTRING); }
"ToInteger"                 { copy(); count (3); return (TOINTEGER); }
"Wait"                      { copy(); count (3); return (WAIT); }
"XOr"                       { copy(); count (3); return (XOR); }

"Arg0"                      { copy(); count (1); return (ARG0); }
"Arg1"                      { copy(); count (1); return (ARG1); }
"Arg2"                      { copy(); count (1); return (ARG2); }
"Arg3"                      { copy(); count (1); return (ARG3); }
"Arg4"                      { copy(); count (1); return (ARG4); }
"Arg5"                      { copy(); count (1); return (ARG5); }
"Arg6"                      { copy(); count (1); return (ARG6); }

"Local0"                    { copy(); count (1); return (LOCAL0); }
"Local1"                    { copy(); count (1); return (LOCAL1); }
"Local2"                    { copy(); count (1); return (LOCAL2); }
"Local3"                    { copy(); count (1); return (LOCAL3); }
"Local4"                    { copy(); count (1); return (LOCAL4); }
"Local5"                    { copy(); count (1); return (LOCAL5); }
"Local6"                    { copy(); count (1); return (LOCAL6); }
"Local7"                    { copy(); count (1); return (LOCAL7); }

"Debug"                     { copy(); count (1); return (DEBUG); }

"DefinitionBlock"           { copy(); count (1); return (DEFINITIONBLOCK); }
"Buffer"                    { copy(); count (1); return (BUFFER); }
"Package"                   { copy(); count (1); return (PACKAGE); }

"EISAID"                    { copy(); count (1); return (EISAID); }
"ResourceTemplate"          { copy(); count (1); return (RESOURCETEMPLATE); }
"Unicode"                   { copy(); count (1); return (UNICODE); }
"DMA"                       { copy(); count (1); return (DMA); }
"DWordIO"                   { copy(); count (1); return (DWORDIO); }
"DWordMemory"               { copy(); count (1); return (DWORDMEMORY); }
"EndDependentFn"            { copy(); count (1); return (ENDDEPENDENTFN); }
"FixedIO"                   { copy(); count (1); return (FIXEDIO); }
"Interrupt"                 { copy(); count (1); return (INTERRUPT); }
"IO"                        { copy(); count (1); return (IO); }
"IRQNoFlags"                { copy(); count (1); return (IRQNOFLAGS); }
"IRQ"                       { copy(); count (1); return (IRQ); }
"Memory24"                  { copy(); count (1); return (MEMORY24); }
"Memory32Fixed"             { copy(); count (1); return (MEMORY32FIXED); }
"Memory32"                  { copy(); count (1); return (MEMORY32); }
"QWordIO"                   { copy(); count (1); return (QWORDIO); }
"QWordMemory"               { copy(); count (1); return (QWORDMEMORY); }
"Register"                  { copy(); count (1); return (REGISTER); }
"StartDependentFn"          { copy(); count (1); return (STARTDEPENDENTFN); }
"StartDependentFnNoPri"     { copy(); count (1); return (STARTDEPENDENTFN_NOPRI); }
"VendorLong"                { copy(); count (1); return (VENDORLONG); }
"VendorShort"               { copy(); count (1); return (VENDORSHORT); }
"WordBusNumber"             { copy(); count (1); return (WORDBUSNUMBER); }
"WordIO"                    { copy(); count (1); return (WORDIO); }

"UnknownObj"                { copy(); count (0); return (OBJECTTYPE_UNK); }
"IntObj"                    { copy(); count (0); return (OBJECTTYPE_INT); }
"StrObj"                    { copy(); count (0); return (OBJECTTYPE_STR); }
"BuffObj"                   { copy(); count (0); return (OBJECTTYPE_BUF); }
"PkgObj"                    { copy(); count (0); return (OBJECTTYPE_PKG); }
"FieldUnitObj"              { copy(); count (0); return (OBJECTTYPE_FLD); }
"DeviceObj"                 { copy(); count (0); return (OBJECTTYPE_DEV); }
"EventObj"                  { copy(); count (0); return (OBJECTTYPE_EVT); }
"MethodObj"                 { copy(); count (0); return (OBJECTTYPE_MTH); }
"MutexObj"                  { copy(); count (0); return (OBJECTTYPE_MTX); }
"OpRegionObj"               { copy(); count (0); return (OBJECTTYPE_OPR); }
"PowerResObj"               { copy(); count (0); return (OBJECTTYPE_POW); }
"ThermalZoneObj"            { copy(); count (0); return (OBJECTTYPE_THZ); }
"BuffFieldObj"              { copy(); count (0); return (OBJECTTYPE_BFF); }
"DDBHandleObj"              { copy(); count (0); return (OBJECTTYPE_DDB); }

"AnyAcc"                    { copy(); count (0); return (ACCESSTYPE_ANY); }
"ByteAcc"                   { copy(); count (0); return (ACCESSTYPE_BYTE); }
"WordAcc"                   { copy(); count (0); return (ACCESSTYPE_WORD); }
"DWordAcc"                  { copy(); count (0); return (ACCESSTYPE_DWORD); }
"QWordAcc"                  { copy(); count (0); return (ACCESSTYPE_QWORD); }
"BufferAcc"                 { copy(); count (0); return (ACCESSTYPE_BUF); }

"Lock"                      { copy(); count (0); return (LOCKRULE_LOCK); }
"NoLock"                    { copy(); count (0); return (LOCKRULE_NOLOCK); }

"Preserve"                  { copy(); count (0); return (UPDATERULE_PRESERVE); }
"WriteAsOnes"               { copy(); count (0); return (UPDATERULE_ONES); }
"WriteAsZeros"              { copy(); count (0); return (UPDATERULE_ZEROS); }

"Serialized"                { copy(); count (0); return (SERIALIZERULE_SERIAL); }
"NotSerialized"             { copy(); count (0); return (SERIALIZERULE_NOTSERIAL); }

"SystemIO"                  { copy(); count (0); return (REGIONSPACE_IO); }
"SystemMemory"              { copy(); count (0); return (REGIONSPACE_MEM); }
"PCI_Config"                { copy(); count (0); return (REGIONSPACE_PCI); }
"EmbeddedControl"           { copy(); count (0); return (REGIONSPACE_EC); }
"SMBus"                     { copy(); count (0); return (REGIONSPACE_SMBUS); }
"CMOS"                      { copy(); count (0); return (REGIONSPACE_CMOS); }
"PciBarTarget"              { copy(); count (0); return (REGIONSPACE_PCIBAR); }

"FFixedHW"                  { copy(); count (0); return (ADDRESSSPACE_FFIXEDHW); }

"SMBQuick"                  { copy(); count (0); return (ACCESSATTRIB_QUICK); }
"SMBSendReceive"            { copy(); count (0); return (ACCESSATTRIB_SND_RCV); }
"SMBByte"                   { copy(); count (0); return (ACCESSATTRIB_BYTE); }
"SMBWord"                   { copy(); count (0); return (ACCESSATTRIB_WORD); }
"SMBBlock"                  { copy(); count (0); return (ACCESSATTRIB_BLOCK); }
"SMBProcessCall"            { copy(); count (0); return (ACCESSATTRIB_CALL); }

"MTR"                       { copy(); count (0); return (MATCHTYPE_MTR); }
"MEQ"                       { copy(); count (0); return (MATCHTYPE_MEQ); }
"MLE"                       { copy(); count (0); return (MATCHTYPE_MLE); }
"MLT"                       { copy(); count (0); return (MATCHTYPE_MLT); }
"MGE"                       { copy(); count (0); return (MATCHTYPE_MGE); }
"MGT"                       { copy(); count (0); return (MATCHTYPE_MGT); }

"Compatibility"             { copy(); count (0); return (DMATYPE_COMPATIBILITY); }
"TypeA"                     { copy(); count (0); return (DMATYPE_A); }
"TypeB"                     { copy(); count (0); return (DMATYPE_B); }
"TypeF"                     { copy(); count (0); return (DMATYPE_F); }

"BusMaster"                 { copy(); count (0); return (BUSMASTERTYPE_MASTER); }
"NotBusMaster"              { copy(); count (0); return (BUSMASTERTYPE_NOTMASTER); }

"Transfer8"                 { copy(); count (0); return (XFERTYPE_8); }
"Transfer8_16"              { copy(); count (0); return (XFERTYPE_8_16); }
"Transfer16"                { copy(); count (0); return (XFERTYPE_16); }

"ResourceConsumer"          { copy(); count (0); return (RESOURCETYPE_CONSUMER); }
"ResourceProducer"          { copy(); count (0); return (RESOURCETYPE_PRODUCER); }

"MinFixed"                  { copy(); count (0); return (MINTYPE_FIXED); }
"MinNotFixed"               { copy(); count (0); return (MINTYPE_NOTFIXED); }

"MaxFixed"                  { copy(); count (0); return (MAXTYPE_FIXED); }
"MaxNotFixed"               { copy(); count (0); return (MAXTYPE_NOTFIXED); }

"PosDecode"                 { copy(); count (0); return (DECODETYPE_POS); }
"SubDecode"                 { copy(); count (0); return (DECODETYPE_SUB); }

"ISAOnlyRanges"             { copy(); count (0); return (RANGETYPE_ISAONLY); }
"NonISAOnlyRanges"          { copy(); count (0); return (RANGETYPE_NONISAONLY); }
"EntireRange"               { copy(); count (0); return (RANGETYPE_ENTIRE); }

"Cacheable"                 { copy(); count (0); return (MEMTYPE_CACHEABLE); }
"WriteCombining"            { copy(); count (0); return (MEMTYPE_WRITECOMBINING); }
"Prefetchable"              { copy(); count (0); return (MEMTYPE_PREFETCHABLE); }
"NonCacheable"              { copy(); count (0); return (MEMTYPE_NONCACHEABLE); }

"ReadWrite"                 { copy(); count (0); return (READWRITETYPE_BOTH); }
"ReadOnly"                  { copy(); count (0); return (READWRITETYPE_READONLY); }

"Edge"                      { copy(); count (0); return (INTTYPE_EDGE); }
"Level"                     { copy(); count (0); return (INTTYPE_LEVEL); }

"ActiveHigh"                { copy(); count (0); return (INTLEVEL_ACTIVEHIGH); }
"ActiveLow"                 { copy(); count (0); return (INTLEVEL_ACTIVELOW); }

"Shared"                    { copy(); count (0); return (SHARETYPE_SHARED); }
"Exclusive"                 { copy(); count (0); return (SHARETYPE_EXCLUSIVE); }

"Decode10"                  { copy(); count (0); return (IODECODETYPE_10); }
"Decode16"                  { copy(); count (0); return (IODECODETYPE_16); }

"TypeTranslation"           { copy(); count (0); return (TYPE_TRANSLATION); }
"TypeStatic"                { copy(); count (0); return (TYPE_STATIC); }

"SparseTranslation"         { copy(); count (0); return (TRANSLATIONTYPE_SPARSE); }
"DenseTranslation"          { copy(); count (0); return (TRANSLATIONTYPE_DENSE); }

"AddressRangeMemory"        { copy(); count (0); return (ADDRESSTYPE_MEMORY); }
"AddressRangeReserved"      { copy(); count (0); return (ADDRESSTYPE_RESERVED); }
"AddressRangeNVS"           { copy(); count (0); return (ADDRESSTYPE_NVS); }
"AddressRangeACPI"          { copy(); count (0); return (ADDRESSTYPE_ACPI); }



"{"			                { copy(); count (0); return('{'); }
"}"			                { copy(); count (0); return('}'); }
","			                { copy(); count (0); return(','); }
"("			                { copy(); count (0); return('('); }
")"			                { copy(); count (0); return(')'); }


{NameSeg}                   { char *s;
                                copy(); count (0);
			                    s=malloc (ACPI_NAME_SIZE + 1);
                                if (strcmp (AslCompilertext, "\\"))
                                {
                                    strcpy (s, "____");
                                    strupr (AslCompilertext);
                                }
			                    memcpy (s, AslCompilertext, strlen (AslCompilertext));
			                    AslCompilerlval.s = s;
                                DbgPrint ("NameSeg: %s\n", s);
                                return (NAMESEG); }

{NameString}                { char *s;
                                copy(); count (0);
			                    s=malloc (strlen (AslCompilertext)+1);
                                strupr (AslCompilertext);
			                    strcpy (s, AslCompilertext);
			                    s[strlen (AslCompilertext)] = 0;
			                    AslCompilerlval.s = s;
                                DbgPrint ("NameString: %s\n", s);
                                return (NAMESTRING); }


<<EOF>>                     { if (AslPopInputFileStack ()) yyterminate();};

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


void
copy (void)
{


    if (Gbl_SourceOutputFlag)
    {
       fwrite (yytext, strlen(yytext), 1, Gbl_SourceOutputFile);
    }
}


void
copy_one (int c)
{

    if (Gbl_SourceOutputFlag)
    {
       fwrite (&c, 1, 1, Gbl_SourceOutputFile);
    }

}


/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

int
AslPopInputFileStack (void)
{
    ASL_FILE_NODE           *Node;
    FILE                    *InputFile = NULL;
  

    Node = InputStack;
    DbgPrint ("\nPop InputFile Stack, Node %p\n\n", Node);

    if (Node)
    {
        fclose (yyin);

        InputStack = Node->Next;
        InputFile = Node->File;


        Gbl_InputFilename = Node->Filename;
        Gbl_CurrentLineNumber = Node->CurrentLineNumber;

        yy_delete_buffer (YY_CURRENT_BUFFER);

        yy_switch_to_buffer (Node->State);

        free (Node);
        return 0;
    }

    return -1;
}


/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

void
AslPushInputFileStack (
    FILE                    *InputFile,
    char                    *Filename)
{
    ASL_FILE_NODE           *Node;
    YY_BUFFER_STATE         State;
      

          
    Node = calloc (sizeof (ASL_FILE_NODE), 1);
//    if (!Node)
//    {
//    }

    Node->File = yyin;
    Node->Next = InputStack;
    Node->State = YY_CURRENT_BUFFER;
    Node->CurrentLineNumber = Gbl_CurrentLineNumber;
    Node->Filename = Gbl_InputFilename;

    InputStack = Node;


    State = yy_create_buffer (InputFile, YY_BUF_SIZE);
    yy_switch_to_buffer (State);

    DbgPrint ("\nPush InputFile Stack, returning %p\n\n", InputFile);

    Gbl_InputFilename = Filename;
    Gbl_CurrentLineNumber = 1;

    yyin = InputFile;
}


/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

void
ResetCurrentLineBuffer (
    void)
{

	Gbl_CurrentColumn = 0;
	Gbl_CurrentLineNumber++;
	Gbl_LogicalLineNumber++;
	Gbl_LineBufPtr = Gbl_CurrentLineBuffer;
}


/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/


void 
DoOneChar (
    int                     c)
{

    Gbl_InputByteCount++;

    copy_one (c);

    if (c == '\n')
    {
        ResetCurrentLineBuffer ();
    }

    else if (c == '\t')
        Gbl_CurrentColumn += 8 - (Gbl_CurrentColumn & (8-1));
    
    else
        Gbl_CurrentColumn++;
}


/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
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



	for (i = 0; yytext[i] != 0; i++)
	{
		if (yytext[i] == '\n')
		{
            ResetCurrentLineBuffer ();
        }

		else
		{
			*Gbl_LineBufPtr = yytext[i];
            Gbl_LineBufPtr++;

            if (Gbl_LineBufPtr > (Gbl_CurrentLineBuffer + 255))
            {
                printf ("Line buf overflow at line %d\n", Gbl_CurrentLineNumber);
                ResetCurrentLineBuffer ();
            }

            if (yytext[i] == '\t')
                Gbl_CurrentColumn += 8 - (Gbl_CurrentColumn & (8-1));
    
            else
                Gbl_CurrentColumn++;
		}

        Gbl_InputByteCount++;
		*Gbl_LineBufPtr = 0;
	}
}



/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

void
comment (void)
{
	char                c, c1;


loop:
	while ((c = input()) != '*' && c != 0)
    {
        DoOneChar (c);
    }

    DoOneChar (c);

	if ((c1 = input()) != '/' && c != 0)
	{
		unput(c1);
		goto loop;
	}

    DoOneChar (c1);
}


/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

void
comment2 (void)
{
	char                c;


	while ((c = input()) != '\n' && c != 0)
    {
        DoOneChar (c);
    }

    DoOneChar (c);
}


/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

void
literal (void)
{
    char                *d;
    char                *s;
    char                *CleanString;


    CleanString = malloc (strlen (AslCompilertext));
    d = CleanString;

    s = AslCompilertext;
    DoOneChar (*s);
    s++;

    while (*s)
    {
        if (*s != '\\')
        {
            *d = *s;
            d++;
            DoOneChar (*s);
            s++;
        }

        else /* (*s == backslash escape) */
        {
            DoOneChar (*s);
            s++;

            switch (*s)
            {
            case 'n':
                *d = 0x0A;      /* LF */
                break;

            case 't':
                *d = 0x20;
                break;

            default:
                *d = *s;
                break;
            }

            d++;
            DoOneChar (*s);
            s++;
        }
    }

    d--;
    *d = 0;

    AslCompilerlval.s = CleanString;
}

