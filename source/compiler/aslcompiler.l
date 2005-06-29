
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

/*
 * Custom input routine gathers statistics
 * 
 * TBD: If input needs to be upper cased, do it here.
 */

#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
	if ( yy_current_buffer->yy_is_interactive ) \
		{ \
		int c = '*', n; \
		for ( n = 0; n < max_size && \
			     (c = getc( yyin )) != EOF && c != '\n'; ++n ) \
			{buf[n] = (char) c; InputChars++;}\
		if ( c == '\n' ) {InputLines++;\
			buf[n++] = (char) c;} \
		if ( c == EOF && ferror( yyin ) ) \
			YY_FATAL_ERROR( "input in flex scanner failed" ); \
		result = n; \
		} \
	else {\
        int i;\
        if ( ((result = fread( buf, 1, max_size, yyin )) == 0) \
		  && ferror( yyin ) ) \
		    {YY_FATAL_ERROR( "input in flex scanner failed" );} \
        for (i = 0; i < result; i++) \
        { if (buf[i] == '\n') InputLines++; } \
        InputChars += result; \
        }


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


[ \t\n] ;



"/*"			            { comment(); }
"//"                        { comment2(); }

\"([^\"]|(\\\"))*\"	        { char *s;
			                    s=malloc (strlen (AslCompilertext));
			                    strcpy (s, AslCompilertext+1);
			                    s[strlen (AslCompilertext+1)-1] = 0;
			                    AslCompilerlval.s = s;
			                    return STRING_LITERAL; }


0[xX]{HexDigitChar}+ |
{DigitChar}+                {AslCompilerlval.l = strtoul((char *)AslCompilertext, (char **) 0, 0);
                                count (0); 
                                return (INTEGER); }

"Ones"                      { count (0); return (ONES); }
"One"                       { count (0); return (ONE); }
"Zero"                      { count (0); return (ZERO); }
                                
"Offset"                    { count (0); return (OFFSET); }
"AccessAs"                  { count (0); return (ACCESSAS); }
"BankField"                 { count (1); return (BANKFIELD); }
"CreateBitField"            { count (1); return (CREATEBITFIELD); }
"CreateByteField"           { count (1); return (CREATEBYTEFIELD); }
"CreateDWordField"          { count (1); return (CREATEDWORDFIELD); }
"CreateField"               { count (1); return (CREATEFIELD); }
"CreateQWordField"          { count (1); return (CREATEQWORDFIELD); }
"CreateWordField"           { count (1); return (CREATEWORDFIELD); }
"DataTableRegion"           { count (1); return (DATATABLEREGION); }
"Device"                    { count (1); return (DEVICE); }
"Event"                     { count (1); return (EVENT); }
"Field"                     { count (1); return (FIELD); }
"IndexField"                { count (1); return (INDEXFIELD); }
"Method"                    { count (1); return (METHOD); }
"Mutex"                     { count (1); return (MUTEX); }
"OperationRegion"           { count (1); return (OPERATIONREGION); }
"PowerResource"             { count (1); return (POWERRESOURCE); }
"Processor"                 { count (1); return (PROCESSOR); }
"ThermalZone"               { count (1); return (THERMALZONE); }
"Alias"                     { count (1); return (ALIAS); }
"Name"                      { count (1); return (NAME); }
"Scope"                     { count (1); return (SCOPE); }
"Break"                     { count (2); return (BREAK); }
"BreakPoint"                { count (2); return (BREAKPOINT); }
"Continue"                  { count (2); return (CONTINUE); }
"Fatal"                     { count (2); return (FATAL); }
"If"                        { count (2); return (IF); }
"Else"                      { count (2); return (ELSE); }
"ElseIf"                    { count (2); return (ELSEIF); }
"Load"                      { count (2); return (LOAD); }
"Noop"                      { count (2); return (NOOP); }
"Notify"                    { count (2); return (NOTIFY); }
"Release"                   { count (2); return (RELEASE); }
"Reset"                     { count (2); return (RESET); }
"Return"                    { count (2); return (RETURN); }
"Signal"                    { count (2); return (SIGNAL); }
"Sleep"                     { count (2); return (SLEEP); }
"Stall"                     { count (2); return (STALL); }
"Switch"                    { count (2); return (SWITCH); }
"Case"                      { count (2); return (CASE); }
"Default"                   { count (2); return (DEFAULT); }
"Unload"                    { count (2); return (UNLOAD); }
"While"                     { count (2); return (WHILE); }

"Acquire"                   { count (2); return (ACQUIRE); }
"Add"                       { count (2); return (ADD); }
"And"                       { count (2); return (AND); }
"Buff"                      { count (2); return (BUFF); }
"Concatenate"               { count (2); return (CONCATENATE); }
"ConcatenateResTemplate"    { count (2); return (CONCATENATERESTEMPLATE); }
"CondRefOf"                 { count (2); return (CONDREFOF); }
"Copy"                      { count (2); return (COPY); }
"Decrement"                 { count (2); return (DECREMENT); }
"DecStr"                    { count (2); return (DECSTR); }
"DeRefOf"                   { count (2); return (DEREFOF); }
"Divide"                    { count (2); return (DIVIDE); }
"FindSetLeftBit"            { count (2); return (FINDSETLEFTBIT); }
"FindSetRightBit"           { count (2); return (FINDSETRIGHTBIT); }
"FromBCD"                   { count (2); return (FROMBCD); }
"HexStr"                    { count (2); return (HEXSTR); }
"Increment"                 { count (2); return (INCREMENT); }
"Index"                     { count (2); return (INDEX); }
"Int"                       { count (2); return (INT); }
"LAnd"                      { count (2); return (LAND); }
"LEqual"                    { count (2); return (LEQUAL); }
"LGreater"                  { count (2); return (LGREATER); }
"LGreaterEqual"             { count (2); return (LGREATEREQUAL); }
"LLess"                     { count (2); return (LLESS); }
"LLessEqual"                { count (2); return (LLESSEQUAL); }
"LNot"                      { count (2); return (LNOT); }
"LNotEqual"                 { count (2); return (LNOTEQUAL); }
"LoadTable"                 { count (2); return (LOADTABLE); }
"LOr"                       { count (2); return (LOR); }
"Match"                     { count (2); return (MATCH); }
"Mid"                       { count (2); return (MID); }
"Mod"                       { count (2); return (MOD); }
"Multiply"                  { count (2); return (MULTIPLY); }
"NAnd"                      { count (2); return (NAND); }
"NOr"                       { count (2); return (NOR); }
"Not"                       { count (2); return (NOT); }
"ObjectType"                { count (2); return (OBJECTTYPE); }
"Or"                        { count (2); return (OR); }
"RefOf"                     { count (2); return (REFOF); }
"ShiftLeft"                 { count (2); return (SHIFTLEFT); }
"ShiftRight"                { count (2); return (SHIFTRIGHT); }
"SizeOf"                    { count (2); return (SIZEOF); }
"Store"                     { count (2); return (STORE); }
"String"                    { count (2); return (STRING); }
"Subtract"                  { count (2); return (SUBTRACT); }
"ToBCD"                     { count (2); return (TOBCD); }
"Wait"                      { count (2); return (WAIT); }
"XOr"                       { count (2); return (XOR); }

"Arg0"                      { count (0); return (ARG0); }
"Arg1"                      { count (0); return (ARG1); }
"Arg2"                      { count (0); return (ARG2); }
"Arg3"                      { count (0); return (ARG3); }
"Arg4"                      { count (0); return (ARG4); }
"Arg5"                      { count (0); return (ARG5); }
"Arg6"                      { count (0); return (ARG6); }

"Local0"                    { count (0); return (LOCAL0); }
"Local1"                    { count (0); return (LOCAL1); }
"Local2"                    { count (0); return (LOCAL2); }
"Local3"                    { count (0); return (LOCAL3); }
"Local4"                    { count (0); return (LOCAL4); }
"Local5"                    { count (0); return (LOCAL5); }
"Local6"                    { count (0); return (LOCAL6); }
"Local7"                    { count (0); return (LOCAL7); }

"Debug"                     { count (0); return (DEBUG); }

"DefinitionBlock"           { count (0); return (DEFINITIONBLOCK); }
"Buffer"                    { count (0); return (BUFFER); }
"Package"                   { count (0); return (PACKAGE); }

"EISAID"                    { count (0); return (EISAID); }
"ResourceTemplate"          { count (0); return (RESOURCETEMPLATE); }
"Unicode"                   { count (0); return (UNICODE); }
"DMA"                       { count (0); return (DMA); }
"DWordIO"                   { count (0); return (DWORDIO); }
"DWordMemory"               { count (0); return (DWORDMEMORY); }
"EndDependentFn"            { count (0); return (ENDDEPENDENTFN); }
"Interrupt"                 { count (0); return (INTERRUPT); }
"IO"                        { count (0); return (IO); }
"IRQNoFlags"                { count (0); return (IRQNOFLAGS); }
"IRQ"                       { count (0); return (IRQ); }
"Memory24"                  { count (0); return (MEMORY24); }
"Memory32Fixed"             { count (0); return (MEMORY32FIXED); }
"Memory32"                  { count (0); return (MEMORY32); }
"QWordIO"                   { count (0); return (QWORDIO); }
"QWordMemory"               { count (0); return (QWORDMEMORY); }
"Register"                  { count (0); return (REGISTER); }
"StartDependentFn"          { count (0); return (STARTDEPENDENTFN); }
"StartDependentFnNoPri"     { count (0); return (STARTDEPENDENTFN_NOPRI); }
"VendorLong"                { count (0); return (VENDORLONG); }
"VendorShort"               { count (0); return (VENDORSHORT); }
"WordBusNumber"             { count (0); return (WORDBUSNUMBER); }
"WordIO"                    { count (0); return (WORDIO); }

"UnknownObj"                { return (OBJECTTYPE_UNK); }
"IntObj"                    { return (OBJECTTYPE_INT); }
"StrObj"                    { return (OBJECTTYPE_STR); }
"BuffObj"                   { return (OBJECTTYPE_BUF); }
"PkgObj"                    { return (OBJECTTYPE_PKG); }
"FieldUnitObj"              { return (OBJECTTYPE_FLD); }
"DeviceObj"                 { return (OBJECTTYPE_DEV); }
"EventObj"                  { return (OBJECTTYPE_EVT); }
"MethodObj"                 { return (OBJECTTYPE_MTH); }
"MutexObj"                  { return (OBJECTTYPE_MTX); }
"OpRegionObj"               { return (OBJECTTYPE_OPR); }
"PowerResObj"               { return (OBJECTTYPE_POW); }
"ThermalZoneObj"            { return (OBJECTTYPE_THZ); }
"BuffFieldObj"              { return (OBJECTTYPE_BFF); }
"DDBHandleObj"              { return (OBJECTTYPE_DDB); }

"AnyAcc"                    { return (ACCESSTYPE_ANY); }
"ByteAcc"                   { return (ACCESSTYPE_BYTE); }
"WordAcc"                   { return (ACCESSTYPE_WORD); }
"DWordAcc"                  { return (ACCESSTYPE_DWORD); }
"QWordAcc"                  { return (ACCESSTYPE_QWORD); }
"BufferAcc"                 { return (ACCESSTYPE_BUF); }

"Lock"                      { return (LOCKRULE_LOCK); }
"NoLock"                    { return (LOCKRULE_NOLOCK); }

"Preserve"                  { return (UPDATERULE_PRESERVE); }
"WriteAsOnes"               { return (UPDATERULE_ONES); }
"WriteAsZeros"              { return (UPDATERULE_ZEROS); }

"Serialized"                { return (SERIALIZERULE_SERIAL); }
"NotSerialized"             { return (SERIALIZERULE_NOTSERIAL); }

"SystemIO"                  { return (REGIONSPACE_IO); }
"SystemMemory"              { return (REGIONSPACE_MEM); }
"PCI_Config"                { return (REGIONSPACE_PCI); }
"EmbeddedControl"           { return (REGIONSPACE_EC); }
"SMBus"                     { return (REGIONSPACE_SMBUS); }
"CMOS"                      { return (REGIONSPACE_CMOS); }
"PciBarTarget"              { return (REGIONSPACE_PCIBAR); }

"SMBQuick"                  { return (ACCESSATTRIB_QUICK); }
"SMBSendReceive"            { return (ACCESSATTRIB_SND_RCV); }
"SMBByte"                   { return (ACCESSATTRIB_BYTE); }
"SMBWord"                   { return (ACCESSATTRIB_WORD); }
"SMBBlock"                  { return (ACCESSATTRIB_BLOCK); }
"SMBProcessCall"            { return (ACCESSATTRIB_CALL); }

"MTR"                       { return (MATCHTYPE_MTR); }
"MEQ"                       { return (MATCHTYPE_MEQ); }
"MLE"                       { return (MATCHTYPE_MLE); }
"MLT"                       { return (MATCHTYPE_MLT); }
"MGE"                       { return (MATCHTYPE_MGE); }
"MGT"                       { return (MATCHTYPE_MGT); }



"{"			                { return('{'); }
"}"			                { return('}'); }
","			                { return(','); }
"("			                { return('('); }
")"			                { return(')'); }


{NameSeg}                   { char *s;
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
			                    s=malloc (strlen (AslCompilertext)+1);
                                strupr (AslCompilertext);
			                    strcpy (s, AslCompilertext);
			                    s[strlen (AslCompilertext)] = 0;
			                    AslCompilerlval.s = s;
                                DbgPrint ("NameString: %s\n", s);
                                return (NAMESTRING); }





%%

void
count (int Type)
{
    TotalKeywords++;

    switch (Type)
    {
    case 1:
        TotalNamedObjects++;
        break;
    case 2:
        TotalExecutableOpcodes++;
        break;
    }
}


void
comment (void)
{
	char c, c1;

loop:
	while ((c = input()) != '*' && c != 0)
		{;}

	if ((c1 = input()) != '/' && c != 0)
	{
		unput(c1);
		goto loop;
	}
}

void
comment2 (void)
{
	char c;

	while ((c = input()) != '\n' && c != 0)
		{;}
}


extern int AslCompilerdebug;

void
ErrorContext (void)
{

    fprintf (stderr, "at line %d\n", InputLines);
    fprintf (stderr, "%s\n", yy_current_buffer->yy_buf_pos);

    if (AslCompilerdebug)
    {
        printf ("at line %d\n", InputLines);
        printf ("%s\n", yy_current_buffer->yy_buf_pos);
    }
}






