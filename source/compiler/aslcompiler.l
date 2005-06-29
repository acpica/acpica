
%{
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


void
comment (void);
void
comment2 (void);
void
count (int type);

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

[\n]                       { count (0); }
[ \t] ;



"/*"			            { comment(); }
"//"                        { comment2(); }

\"([^\"]|(\\\"))*\"	        { char *s;
                                count (0);
			                    s=malloc (strlen (AslCompilertext));
			                    strcpy (s, AslCompilertext+1);
			                    s[strlen (AslCompilertext+1)-1] = 0;
			                    AslCompilerlval.s = s;
			                    return STRING_LITERAL; }


0[xX]{HexDigitChar}+ |
{DigitChar}+                {AslCompilerlval.l = strtoul((char *)AslCompilertext, (char **) 0, 0);
                                count (1); 
                                return (INTEGER); }

"Ones"                      { count (1); return (ONES); }
"One"                       { count (1); return (ONE); }
"Zero"                      { count (1); return (ZERO); }
                                
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
"Buff"                      { count (3); return (BUFF); }
"Concatenate"               { count (3); return (CONCATENATE); }
"ConcatenateResTemplate"    { count (3); return (CONCATENATERESTEMPLATE); }
"CondRefOf"                 { count (3); return (CONDREFOF); }
"Copy"                      { count (3); return (COPY); }
"Decrement"                 { count (3); return (DECREMENT); }
"DecStr"                    { count (3); return (DECSTR); }
"DeRefOf"                   { count (3); return (DEREFOF); }
"Divide"                    { count (3); return (DIVIDE); }
"FindSetLeftBit"            { count (3); return (FINDSETLEFTBIT); }
"FindSetRightBit"           { count (3); return (FINDSETRIGHTBIT); }
"FromBCD"                   { count (3); return (FROMBCD); }
"HexStr"                    { count (3); return (HEXSTR); }
"Increment"                 { count (3); return (INCREMENT); }
"Index"                     { count (3); return (INDEX); }
"Int"                       { count (3); return (INT); }
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
"String"                    { count (3); return (STRING); }
"Subtract"                  { count (3); return (SUBTRACT); }
"ToBCD"                     { count (3); return (TOBCD); }
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
"CMOS"                      { count (0); return (REGIONSPACE_CMOS); }
"PciBarTarget"              { count (0); return (REGIONSPACE_PCIBAR); }

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



"{"			                { count (0); return('{'); }
"}"			                { count (0); return('}'); }
","			                { count (0); return(','); }
"("			                { count (0); return('('); }
")"			                { count (0); return(')'); }


{NameSeg}                   { char *s;
                                count (0);
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
                                count (0);
			                    s=malloc (strlen (AslCompilertext)+1);
                                strupr (AslCompilertext);
			                    strcpy (s, AslCompilertext);
			                    s[strlen (AslCompilertext)] = 0;
			                    AslCompilerlval.s = s;
                                DbgPrint ("NameString: %s\n", s);
                                return (NAMESTRING); }





%%




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
			Gbl_CurrentColumn = 0;
			Gbl_CurrentLineNumber++;
			Gbl_LineBufPtr = Gbl_CurrentLineBuffer;
		}
		else
		{
			*Gbl_LineBufPtr++ = yytext[i];
			if (yytext[i] == '\t')
				Gbl_CurrentColumn += 8 - (Gbl_CurrentColumn & (8-1));
			else
				Gbl_CurrentColumn++;
		}
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
DoOneChar (
    int                     c)
{

    if (c == '\n')
    {
        Gbl_CurrentColumn = 0;
        Gbl_CurrentLineNumber++;
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
comment (void)
{
	char                c, c1;


loop:
	while ((c = input()) != '*' && c != 0)
    {
        DoOneChar (c);
    }

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






