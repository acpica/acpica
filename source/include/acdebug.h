
/******************************************************************************
 * 
 * Name: debugger.h - ACPI/AML debugger
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

#ifndef __DEBUGGER_H__
#define __DEBUGGER_H__


#define DB_MAX_ARGS             8  /* Must be max method args + 1 */

#define DB_COMMAND_PROMPT      '-'
#define DB_EXECUTE_PROMPT      '%'


extern int                      optind;
extern char                     *optarg;
extern UINT8                    *AmlPtr;
extern UINT32                   AmlLength;

extern BOOLEAN                  opt_tables;
extern BOOLEAN                  opt_disasm;
extern BOOLEAN                  opt_stats;
extern BOOLEAN                  opt_parse_jit;
extern BOOLEAN					opt_verbose;
   

extern char                     *Args[DB_MAX_ARGS];
extern char                     LineBuf[80];
extern char                     ScopeBuf[40];
extern char                     DebugFilename[40];
extern BOOLEAN                  OutputToFile;
extern char                     *Buffer;
extern char                     *Filename;
extern char					    *INDENT_STRING;
extern UINT32                   Gbl_MethodBreakpoint;
extern UINT8                    Gbl_DbOutputFlags;
extern UINT32                   Gbl_DbDebugLevel;
extern UINT32                   Gbl_DbConsoleDebugLevel;

extern UINT32                   NumNames;
extern UINT32                   NumMethods;
extern UINT32                   NumRegions;
extern UINT32                   NumPackages;
extern UINT32                   NumAliases;
extern UINT32                   NumDevices;
extern UINT32                   NumFieldDefs;
extern UINT32                   NumThermalZones;
extern UINT32                   NumNamedObjects;
extern UINT32                   NumGrammarElements;
extern UINT32                   NumMethodElements ;
extern UINT32                   NumMutexes;
extern UINT32                   NumPowerResources;
extern UINT32                   NumBankFields ;
extern UINT32                   NumIndexFields;
extern UINT32                   NumEvents;

extern UINT32                   SizeOfParseTree;
extern UINT32                   SizeOfMethodTrees;
extern UINT32                   SizeOfNTEs;
extern UINT32                   SizeOfAcpiObjects;


#define BUFFER_SIZE             4196

#define DB_REDIRECTABLE_OUTPUT  0x01
#define DB_CONSOLE_OUTPUT       0x02
#define DB_DUPLICATE_OUTPUT     0x03



typedef struct CommandInfo
{
    char                    *Name;          /* Command Name */
    char                    MinArgs;        /* Minimum arguments required */

} COMMAND_INFO;


typedef struct ArgumentInfo
{
    char                    *Name;          /* Argument Name */

} ARGUMENT_INFO;



#define PARAM_LIST(pl)                  pl

#define DBTEST_OUTPUT_LEVEL(lvl)        if (opt_verbose)

#define VERBOSE_PRINT(fp)               DBTEST_OUTPUT_LEVEL(lvl) {\
                                            OsdPrintf PARAM_LIST(fp);}

#define EX_NO_SINGLE_STEP       1
#define EX_SINGLE_STEP          2


INT32
DbMatchArgument (
    char                    *UserArgument,
    ARGUMENT_INFO           *Arguments);

void
DbDumpNamespaceByOwner (
    char                    *OwnerArg,
    char                    *DepthArg);

void
DbDisplayTableInfo (
    char                    *TableArg);

void
DbUnloadAcpiTable (
    char                    *TableArg,
    char                    *InstanceArg);


void
DbGenerateStatistics (
    ACPI_GENERIC_OP         *Root,
    BOOLEAN                 IsMethod);

void
DbAddToHistory (
    char                    *CommandLine);

void
DbDisplayHistory (void);

char *
DbGetFromHistory (
    char                    *CommandNumArg);

void
DbDisplayArgumentObject (
    ACPI_OBJECT_INTERNAL    *ObjDesc);

ACPI_STATUS
DbDisplayObjects (
    char                    *ObjTypeArg,
    char                    *DisplayCountArg);

ACPI_STATUS
DbFindNameInNamespace (
    char                    *NameArg);
void
DbSetOutputDestination (
    INT32                   Where);
    
void
DbSetMethodCallBreakpoint (
    ACPI_GENERIC_OP         *Op);

int
DbInitialize (void);

ACPI_STATUS
DbCommandDispatch (
    char                    *InputBuffer,
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *Op);

void
DbExecuteThread (
    void                    *Context);

ACPI_STATUS
DbUserCommands (
    char                    Prompt,
    ACPI_GENERIC_OP         *Op);

NAME_TABLE_ENTRY *
DbLocalNsLookup (
    char                    *Name);

ACPI_STATUS
DbExecuter (
    char                    Prompt,
    ACPI_GENERIC_OP         *Op);

void
DbPrepNamestring (
    char                    *Name);

void
DbDisplayMethodInfo (
    ACPI_GENERIC_OP         *Op);

ACPI_STATUS
DbSecondPassParse (
    ACPI_GENERIC_OP         *Root);

ACPI_STATUS
DbSingleStep (
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *Op,
    UINT8                   OpType);

void
DbDisassembleAml (
    char                    *Statements,
    ACPI_GENERIC_OP         *Op);

void
DbDecodeAndDisplayObject (
    char                    *Target,
    char                    *OutputType);

void
DbDisplayResultObject (
    ACPI_OBJECT_INTERNAL    *RetDesc);

ACPI_STATUS
DbDisplayStatistics (
    char                    *TypeArg);

void
DbSetMethodBreakpoint (
    char                    *Location,
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *Op);

void
DbSendNotify (
    char                    *Name,
    UINT32                  Value);

void
DbSetMethodData (
    char                    *TypeArg,
    char                    *IndexArg,
    char                    *ValueArg);

void
DbDumpBuffer (
    UINT32                  Address);

void
DbDumpObject (
    ACPI_OBJECT             *ObjDesc,
    UINT32                  Level);

ACPI_STATUS
DbDisplayAllMethods (
    char                    *DisplayCountArg);

void 
DbDisplayInternalObject (
    ACPI_OBJECT_INTERNAL    *ObjDesc);

ACPI_STATUS
DbLoadAcpiTable (
    char                    *Filename);

void
DbDisplayArguments (void);

void
DbDisplayLocals (void);

void
DbDisplayResults (void);

void
DbDisplayCallingTree (void);

void
DbDisplayOp (
    ACPI_GENERIC_OP         *origin,
    UINT32                  NumOpcodes);

INT32
DbSafeSprintf (
    char                    *Buffer,
    INT32                   BufferSize,
    INT32                   ExpandedSize,
    char                    *Format,
    ...);

INT32
DbSprintName (
    char                    *Buffer, 
    UINT32                  BufferSize, 
    UINT32                  Name);

INT32
DbSprintNamestring (
    char                    *BufferStart, 
    INT32                   BufferSize, 
    UINT8                   *Name);

INT32
DbSprintPath (
    char                    *BufferStart,
    UINT32                  BufferSize,
    ACPI_GENERIC_OP         *Op);

INT32
DbSprintOp (
    char                    *BufferStart, 
    UINT32                  BufferSize, 
    ACPI_GENERIC_OP         *Op);


void
DbDumpNamespace (
    char                    *StartArg,
    char                    *DepthArg);

void
DbExecute (
    char                    *Name,
    char                    **Args,
    UINT32                  Flags);

void
DbSetScope (
    char                    *Name);

void
DbCloseDebugFile (
    void);

void
DbOpenDebugFile (
    char                    *Name);










#endif  /* __DEBUGGER_H__ */
