/******************************************************************************
 * 
 * Module Name: dispatch.h
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




#ifndef _DISPATCH_H_
#define _DISPATCH_H_


#define NAMEOF_LOCAL_NTE    "__L0"
#define NAMEOF_ARG_NTE      "__A0"


/* For DsMethodDataSetValue */

#define MTH_TYPE_LOCAL              0
#define MTH_TYPE_ARG                1



/* Common interfaces */

ACPI_STATUS
DsObjStackPush (
    void                    *Object,
    ACPI_WALK_STATE         *WalkState);

ACPI_STATUS
DsObjStackPop (
    UINT32                  PopCount,
    ACPI_WALK_STATE         *WalkState);

void *
DsObjStackGetValue (
    UINT32                  Index,
    ACPI_WALK_STATE         *WalkState);

ACPI_STATUS
DsObjStackPopObject (
    ACPI_OBJECT_INTERNAL    **Object,
    ACPI_WALK_STATE         *WalkState);


/* dsregion - Op region support */

ACPI_STATUS
DsGetRegionData (
    ACPI_OBJECT_INTERNAL    *RgnDesc);


/* dsctrl - Parser/Interpreter interface, control stack routines */

ACPI_CTRL_STATE *
DsCreateControlState (void);

void
DsPushControlState (
    ACPI_CTRL_STATE         *ControlState,
    ACPI_WALK_STATE         *WalkState);

ACPI_CTRL_STATE *
DsPopControlState (
    ACPI_WALK_STATE         *WalkState);

ACPI_STATUS 
DsExecBeginControlOp (
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *Op);

ACPI_STATUS 
DsExecEndControlOp (
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *Op);


/* dsexec - Parser/Interpreter interface, method execution callbacks */

ACPI_STATUS
DsExecBeginOp (
    ACPI_WALK_STATE         *State,
    ACPI_GENERIC_OP         *Op);

ACPI_STATUS
DsExecEndOp (
    ACPI_WALK_STATE         *State,
    ACPI_GENERIC_OP         *Op);


/* dsfield - Parser/Interpreter interface for AML fields */


ACPI_STATUS
DsCreateField (
    ACPI_GENERIC_OP         *Op,
    ACPI_HANDLE             Region,
    ACPI_WALK_STATE         *WalkState);

ACPI_STATUS
DsCreateBankField (
    ACPI_GENERIC_OP         *Op,
    ACPI_HANDLE             Region,
    ACPI_WALK_STATE         *WalkState);

ACPI_STATUS
DsCreateIndexField (
    ACPI_GENERIC_OP         *Op,
    ACPI_HANDLE             Region,
    ACPI_WALK_STATE         *WalkState);


/* dsload - Parser/Interpreter interface, namespace load callbacks */

ACPI_STATUS
DsLoad1BeginOp (
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *Op);

ACPI_STATUS
DsLoad1EndOp (
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *Op);

ACPI_STATUS
DsLoad2BeginOp (
    ACPI_WALK_STATE         *State,
    ACPI_GENERIC_OP         *Op);

ACPI_STATUS
DsLoad2EndOp (
    ACPI_WALK_STATE         *State,
    ACPI_GENERIC_OP         *Op);


/* dsmthdat - method data (locals/args) */


ACPI_STATUS
DsMethodDataDeleteAll (
    ACPI_WALK_STATE         *WalkState);

BOOLEAN
DsIsMethodValue (
    ACPI_OBJECT_INTERNAL    *ObjDesc);

ACPI_OBJECT_TYPE
DsMethodDataGetType (
    UINT32                  Type,
    UINT32                  Index);

ACPI_STATUS
DsMethodDataGetValue (
    UINT32                  Type,
    UINT32                  Index, 
    ACPI_OBJECT_INTERNAL    **ObjDesc);

ACPI_STATUS
DsMethodDataSetValue (
    UINT32                  Type,
    UINT32                  Index, 
    ACPI_OBJECT_INTERNAL    *ObjDesc); 

ACPI_STATUS
DsMethodDataDeleteValue (
    UINT32                  Type,
    UINT32                  Index);

ACPI_STATUS
DsMethodDataInitArgs (
    ACPI_OBJECT_INTERNAL    **Params,
    UINT32                  ParamCount);

NAME_TABLE_ENTRY *
DsMethodDataGetNte (
    UINT32                  Type,
    UINT32                  Index);

ACPI_STATUS
DsMethodDataInit (
    ACPI_WALK_STATE         *WalkState);


/* dsmethod - Parser/Interpreter interface - control method parsing */

ACPI_STATUS
DsParseMethod (
    ACPI_HANDLE             ObjHandle);

ACPI_STATUS
DsCallControlMethod (
    ACPI_WALK_LIST          *WalkList,
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *Op);

ACPI_STATUS
DsRestartControlMethod (
    ACPI_WALK_STATE         *WalkState,
    ACPI_OBJECT_INTERNAL    *ReturnDesc);


/* dsobj - Parser/Interpreter interface - object initialization and conversion */

ACPI_STATUS
DsInitOneObject (
    ACPI_HANDLE             ObjHandle, 
    UINT32                  Level, 
    void                    *Context,
    void                    **ReturnValue);

ACPI_STATUS
DsInitializeObjects (
    ACPI_TABLE_DESC         *TableDesc,
    NAME_TABLE_ENTRY        *StartEntry);

ACPI_STATUS
DsBuildInternalPackageObj (
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *op,
    ACPI_OBJECT_INTERNAL    **ObjDesc);

ACPI_STATUS
DsBuildInternalObject (
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *op,
    ACPI_OBJECT_INTERNAL    **ObjDescPtr);

ACPI_STATUS
DsInitObjectFromOp (
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *Op,
    UINT16                  Opcode,
    ACPI_OBJECT_INTERNAL    *ObjDesc);

ACPI_STATUS
DsCreateNamedObject (
    ACPI_WALK_STATE         *WalkState,
    NAME_TABLE_ENTRY        *Entry,
    ACPI_GENERIC_OP         *Op);


/* dsregn - Parser/Interpreter interface - Op Region parsing */

ACPI_STATUS
DsEvalRegionOperands (
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *Op);

ACPI_STATUS
DsInitializeRegion (
    ACPI_HANDLE             ObjHandle);

    
/* dsutils - Parser/Interpreter interface utility routines */

void
DsDeleteResultIfNotUsed (
    ACPI_GENERIC_OP         *Op,
    ACPI_OBJECT_INTERNAL    *ResultObj,
    ACPI_WALK_STATE         *WalkState);

ACPI_STATUS
DsCreateOperand (
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *Arg);

ACPI_STATUS
DsCreateOperands (
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *FirstArg);

ACPI_STATUS
DsResolveOperands (
    ACPI_WALK_STATE         *WalkState);

ACPI_OBJECT_TYPE
DsMapOpcodeToDataType (
    UINT16                  Opcode,
    UINT32                  *OutFlags);

ACPI_OBJECT_TYPE 
DsMapNamedOpcodeToDataType (
    UINT16                  Opcode);


/*
 * dswscope - Scope Stack manipulation
 */

ACPI_STATUS
DsScopeStackPush (
    NAME_TABLE_ENTRY        *NewScope, 
    ACPI_OBJECT_TYPE        Type,
	ACPI_WALK_STATE			*WalkState);


ACPI_STATUS
DsScopeStackPop (
	ACPI_WALK_STATE			*WalkState);

void
DsScopeStackClear (
	ACPI_WALK_STATE			*WalkState);


/* Dswstate - parser WALK_STATE management routines */

ACPI_WALK_STATE *
DsCreateWalkState (
    ACPI_GENERIC_OP         *Origin,
    ACPI_OBJECT_INTERNAL    *MthDesc,
    ACPI_WALK_LIST          *WalkList);

ACPI_STATUS
DsObjStackDeleteAll (
    ACPI_WALK_STATE         *WalkState);

ACPI_STATUS
DsObjStackPopAndDelete (
    UINT32                  PopCount,
    ACPI_WALK_STATE         *WalkState);

void
DsDeleteWalkState (
    ACPI_WALK_STATE         *WalkState);

ACPI_WALK_STATE *
DsPopWalkState (
    ACPI_WALK_LIST          *WalkList);

ACPI_STATUS
DsResultStackPop (
    ACPI_OBJECT_INTERNAL    **Object,
    ACPI_WALK_STATE         *WalkState);

ACPI_STATUS
DsResultStackPush (
    void                    *Object,
    ACPI_WALK_STATE         *WalkState);

ACPI_STATUS
DsResultStackClear (
    ACPI_WALK_STATE         *WalkState);

ACPI_WALK_STATE *
DsGetCurrentWalkState (
    ACPI_WALK_LIST          *WalkList);




#endif /* _DISPATCH_H_ */