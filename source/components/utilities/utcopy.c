
/******************************************************************************
 * 
 * Module Name: cmobject - Internal to external object translation utilities
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
 * license (without the right to sublicense), under only those claims of Intel
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

#define __CMOBJECT_C__

#include <acpi.h>
#include <interpreter.h>
#include <namespace.h>
#include <acpiobj.h>
#include <pnp.h>


#define _THIS_MODULE        "cmobject.c"
#define _COMPONENT          MISCELLANEOUS

struct Search_st 
{
    ACPI_OBJECT_INTERNAL        *CAObj;
    UINT32                      Index;
    ACPI_OBJECT                 *UserObj;

} Level[MAX_OBJECT_DEPTH];


/******************************************************************************
 *
 * FUNCTION:    CmGetSimpleObjectSize
 *
 * PARAMETERS:  *Obj            - Pointer to the object we are examining
 *              *RetLength      - a pointer to a variabl to recieve the
 *                                length
 * 
 * RETURN:      Status          - the status of the call
 * 
 * DESCRIPTION: This function is called to determine the space required to
 *              contain a simple object for return to an API user.
 *
 *              The length includes the object structure plus any additional
 *              needed space.
 * 
 ******************************************************************************/

ACPI_STATUS
CmGetSimpleObjectSize (
    ACPI_OBJECT_INTERNAL    *Obj, 
    UINT32                  *ObjLength)
{
    UINT32                  Length;


    Length = sizeof (ACPI_OBJECT);

    switch (Obj->ValType)
    {

    case TYPE_String:

        Length += Obj->String.StrLen;
        break;


    case TYPE_Buffer:

        Length += Obj->Buffer.BufLen;
        break;


    case TYPE_Number:
        /*
         *  Number is included in the object itself
         */
        break;


    default:
        return AE_TYPE;
        break;
    }

    *ObjLength = Length;
    return AE_OK;
}


/******************************************************************************
 *
 * FUNCTION:    CmGetPackageObjectSize
 *
 * PARAMETERS:  *Obj            - Pointer to the object we are examining
 *              *RetLength      - a pointer to a variabl to recieve the
 *                                length
 * 
 * RETURN:      Status          - the status of the call
 * 
 * DESCRIPTION: This function is called to determine the space required to contain
 *              a package object for return to an API user.
 *
 *              This is moderately complex since a package contains other objects
 *              including packages.
 * 
 ******************************************************************************/

ACPI_STATUS
CmGetPackageObjectSize (
    ACPI_OBJECT_INTERNAL    *Obj, 
    UINT32                  *ObjLength)
{

    ACPI_OBJECT_INTERNAL    *ThisObj;
    ACPI_OBJECT_INTERNAL    *ParentObj[MAX_OBJECT_DEPTH] = { 0,0,0,0,0 };
    ACPI_OBJECT_INTERNAL    *ThisParent;
    UINT32                  ThisIndex;
    UINT32                  Index[MAX_OBJECT_DEPTH] = { 0,0,0,0,0 };
    UINT32                  Length = 0;
    UINT32                  Temp;
    UINT32                  CurrentDepth = 0;
    UINT32                  PackageCount = 1;
    ACPI_STATUS             Status;
    

    ParentObj[0] = Obj;

    while (1)
    {
        ThisParent = ParentObj[CurrentDepth];
        ThisIndex = Index[CurrentDepth];
        ThisObj = ThisParent->Package.PackageElems[ThisIndex];

        if (ThisObj->ValType == TYPE_Package)
        {
            /*
             *  If this object is a package then we go one deeper
             */
            PackageCount++;
            if (CurrentDepth < MAX_OBJECT_DEPTH-1)
            {
                CurrentDepth++;
                ParentObj[CurrentDepth] = ThisObj;
                Index[CurrentDepth] = 0;
            }

            else
            {
                /*
                 *  Too many nested levels of packages for us to handle
                 */
                
                DEBUG_PRINT (ACPI_ERROR, ("CmGetPackageObjectSize: Pkg nested too deep (max %d)\n",
                                            MAX_OBJECT_DEPTH));
                return AE_LIMIT;
            }
        }   /* if object is a package */

        else
        {
            Status = CmGetSimpleObjectSize(ThisObj, &Temp);
            if (Status != AE_OK) 
            {
                /*
                 *  Failure get out
                 */
                return Status;
            }

            Length += Temp;

            Index[CurrentDepth]++;
            while (Index[CurrentDepth] >= ParentObj[CurrentDepth]->Package.PkgCount)
            {
                /*
                 *  We've handled all of the objects at this level,  This means that we
                 *  have just completed a package.  That package may have contained one
                 *  or more packages itself
                 */
                if (CurrentDepth == 0)
                {
                    /*
                     *  We have handled all of the objects in the top level package
                     *  just add the length of the package objects and get out
                     */
                    Length += sizeof(ACPI_OBJECT) * PackageCount;
                    *ObjLength = Length;
                    return AE_OK;
                }

                /*
                 *  go back up a level and move the index past the just completed
                 *  package object.
                 */
                CurrentDepth--;
                Index[CurrentDepth]++;
            }
        }   /* else object is NOT a package */
    }   /*  while (1)  */

    /*
     *  We'll never get here, but the compiler whines about return value
     */
    return AE_OK;
}


/******************************************************************************
 *
 * FUNCTION:    CmGetObjectSize
 *
 * PARAMETERS:  *Obj            - Pointer to the object we are examining
 *              *RetLength      - Where the length will be returned
 * 
 * RETURN:      Status          - the status of the call
 * 
 * DESCRIPTION: This function is called to determine the space required to
 *              contain an object for return to an API user.
 *
 ******************************************************************************/

ACPI_STATUS
CmGetObjectSize(
    ACPI_OBJECT_INTERNAL    *Obj, 
    UINT32                  *ObjLength)
{
    ACPI_STATUS             Status;


    if (Obj->ValType == TYPE_Package)
    {
        Status = CmGetPackageObjectSize (Obj, ObjLength);
    }

    else
    {
        Status = CmGetSimpleObjectSize (Obj, ObjLength);
    }

    return Status;
}


/******************************************************************************
 *
 * FUNCTION:    CmBuildExternalSimpleObject
 *
 * PARAMETERS:  *Obj            - Pointer to the object we are examining
 *              *Buffer         - a pointer to the caller's buffer to place
 *                                the object in
 *              *SpaceUsed      - a pointer to a dword to return the data length
 * 
 * RETURN:      Status          - the status of the call
 * 
 * DESCRIPTION: This function is called to place a simple object in a user buffer.
 *
 *              The buffer is assumed to have sufficient space for the object.
 * 
 ******************************************************************************/

ACPI_STATUS
CmBuildExternalSimpleObject(
    ACPI_OBJECT_INTERNAL    *Obj,
    ACPI_OBJECT             *UserObj,
    char                    *DataSpace,
    UINT32                  *BufferSpaceUsed)
{
    UINT32                  Length = 0;
    char                    *SourcePtr;


    UserObj->Type = Obj->ValType;

    switch (UserObj->Type)
    {

    case TYPE_String:

        Length = Obj->String.StrLen;
        UserObj->String.Length = Obj->String.StrLen;
        UserObj->String.Pointer = DataSpace;
        SourcePtr = (char *) Obj->String.String;
        break;


    case TYPE_Buffer:

        Length = Obj->Buffer.BufLen;
        UserObj->Buffer.Length = Obj->Buffer.BufLen;
        UserObj->Buffer.Pointer = DataSpace;
        SourcePtr = (char *) Obj->Buffer.Buffer;
        break;


    case TYPE_Number:

        UserObj->Number.Value= Obj->Number.Number;
        break;


    default:
        return AE_RETURN_VALUE;
        break;
    }


    if (Length)
    {
        /*
         *  Copy the return data to the caller's buffer
         */
        memcpy ((void *) DataSpace, (void *) SourcePtr, Length);
    }

    *BufferSpaceUsed = Length;
    return AE_OK;
}


/******************************************************************************
 *
 * FUNCTION:    CmBuildExternalPackageObject
 *
 * PARAMETERS:  *Obj            - Pointer to the object we are returning
 *              *Buffer         - a pointer to the caller's buffer to place
 *                                the object in
 *              *SpaceUsed      - a pointer to a dword to return the number
 *                                of bytes used to build the object(s)
 * 
 * RETURN:      Status          - the status of the call
 * 
 * DESCRIPTION: This function is called to place a package object in a user
 *              buffer.  A package object by definition contains other objects.
 *
 *              The buffer is assumed to have sufficient space for the object.
 *              The caller must have verified the buffer length needed using the
 *              CmGetObjectSize function before calling this function.
 * 
 ******************************************************************************/

ACPI_STATUS
CmBuildExternalPackageObject (
    ACPI_OBJECT_INTERNAL    *Obj, 
    char                    *Buffer, 
    UINT32                  *SpaceUsed)
{
    char                    *FreeSpace;
    ACPI_OBJECT             *UserObj;
    UINT32                  CurrentDepth = 0;
    ACPI_STATUS             Status;
    UINT32                  Length = 0;
    UINT32                  ThisIndex;
    UINT32                  Temp;
    ACPI_OBJECT_INTERNAL    *ThisObj;
    ACPI_OBJECT             *ThisUObj;
    register struct Search_st  *LevelPtr;
    

    /*
     *  First package at head of the buffer
     */
    UserObj = (ACPI_OBJECT *)Buffer;

    /*
     *  Free space begins right after the first package
     */
    FreeSpace = Buffer + sizeof(ACPI_OBJECT);


    /*
     *  Initialize the working variables
     */
    
    Level[0].CAObj = Obj;
    Level[0].UserObj = UserObj;
    CurrentDepth = 0;

    memset ((void *) Level, 0, sizeof (Level));

    UserObj->Type = Obj->ValType;
    UserObj->Package.Count = Obj->Package.PkgCount;
    UserObj->Package.Elements = (ACPI_OBJECT *) FreeSpace;


    /*
     *  Build an array of ACPI_OBJECTS in the buffer
     *  and move the free space past it
     */

    FreeSpace += UserObj->Package.Count * sizeof (ACPI_OBJECT);

    LevelPtr = &Level[CurrentDepth];

    while (1)
    {
        ThisIndex   = LevelPtr->Index;
        ThisObj     = (ACPI_OBJECT_INTERNAL *) &LevelPtr->CAObj->Package.PackageElems[ThisIndex];
        ThisUObj    = (ACPI_OBJECT *) &LevelPtr->UserObj->Package.Elements[ThisIndex];

        if (ThisObj->ValType == TYPE_Package)
        {
            /*
             *  If this object is a package then we go one deeper
             */
            if (CurrentDepth >= MAX_OBJECT_DEPTH-1)
            {
                /*
                 *  Too many nested levels of packages for us to handle
                 */
                DEBUG_PRINT (ACPI_ERROR, ("CmBuildPackageObject: Pkg nested too deep (max %d)\n",
                                            MAX_OBJECT_DEPTH));
                return AE_LIMIT;
            }

            /*
             *  Build the package object
             */
            ThisUObj->Type = TYPE_Package;
            ThisUObj->Package.Count = ThisObj->Package.PkgCount;
            ThisUObj->Package.Elements = (ACPI_OBJECT *) FreeSpace;

            /*
             *  Save space for the array of objects (Package elements)
             *  update the buffer length counter
             */
            Temp = ThisUObj->Package.Count * sizeof(ACPI_OBJECT);
            FreeSpace += Temp;
            Length += Temp;

            CurrentDepth++;
            LevelPtr = &Level[CurrentDepth];
            LevelPtr->CAObj = ThisObj;
            LevelPtr->UserObj = ThisUObj;
            LevelPtr->Index = 0;

        }   /* if object is a package */
        
        else
        {
            Status = CmBuildExternalSimpleObject(ThisObj, ThisUObj, FreeSpace, &Temp);
            if (Status != AE_OK) {
                /*
                 *  Failure get out
                 */
                return Status;
            }

            FreeSpace += Temp;
            Length +=Temp;

            LevelPtr->Index++;
            while (LevelPtr->Index >= LevelPtr->CAObj->Package.PkgCount)
            {
                /*
                 *  We've handled all of the objects at this level,  This means that we
                 *  have just completed a package.  That package may have contained one
                 *  or more packages itself
                 */
                if (CurrentDepth == 0)
                {
                    /*
                     *  We have handled all of the objects in the top level package
                     *  just add the length of the package objects and get out
                     */
                    *SpaceUsed = Length;
                    return AE_OK;
                }

                /*
                 *  go back up a level and move the index past the just completed
                 *  package object.
                 */
                CurrentDepth--;
                LevelPtr = &Level[CurrentDepth];
                LevelPtr->Index++;
            }
        }   /* else object is NOT a package */
    }   /*  while (1)  */


    /*
     *  We'll never get here, but the compiler whines about return value
     */
    return AE_OK;
}


/******************************************************************************
 *
 * FUNCTION:    CmBuildExternalObject
 *
 * PARAMETERS:  *Obj            - Pointer to the object we are building from
 *              *BufferPtr      - a pointer to a the caller's return buffer
 * 
 * RETURN:      Status          - the status of the call
 * 
 * DESCRIPTION: This function is called to build an API object to be returned to
 *              the caller.
 *
 ******************************************************************************/

ACPI_STATUS
CmBuildExternalObject (
    ACPI_OBJECT_INTERNAL    *Obj, 
    ACPI_BUFFER             *RetBuffer)
{
    ACPI_STATUS             Status;


    if (Obj->ValType == TYPE_Package)
    {
        /*
         *  Package objects contain other objects (which can be objects)
         *  buildpackage does it all
         */
        Status = CmBuildExternalPackageObject(Obj, RetBuffer->Pointer,
                        &RetBuffer->Length);
    }

    else
    {
        /*
         *  Build a simple object (no nested objects)
         */
        Status = CmBuildExternalSimpleObject(Obj,
                        (ACPI_OBJECT *) RetBuffer->Pointer,
                        ((char *) RetBuffer->Pointer + sizeof (ACPI_OBJECT)),
                        &RetBuffer->Length);
        /*
         *  build simple does not include the object size in the length
         *  so we add it in here
         */
        RetBuffer->Length += sizeof (ACPI_OBJECT);
    }

    return Status;
}

/******************************************************************************
 *
 * FUNCTION:    CmBuildInternalSimpleObject
 *
 * PARAMETERS:  *UserObj        - Pointer to the external object
 *              *Obj            - Pointer to the internal object
 * 
 * RETURN:      Status          - the status of the call
 * 
 * DESCRIPTION: This function copies an external object to an internal one.
 *              NOTE: Pointers can be copied, we don't need to copy data.
 *              (The pointers have to be valid in our address space no matter
 *              what we do with them!)
 *
 ******************************************************************************/

ACPI_STATUS
CmBuildInternalSimpleObject(
    ACPI_OBJECT             *UserObj,
    ACPI_OBJECT_INTERNAL    *Obj)
{


    Obj->ValType = UserObj->Type;

    switch (UserObj->Type)
    {

    case TYPE_String:

        Obj->String.StrLen = UserObj->String.Length;
        Obj->String.String = UserObj->String.Pointer;
        break;


    case TYPE_Buffer:

        Obj->Buffer.BufLen = UserObj->Buffer.Length;
        Obj->Buffer.Buffer = UserObj->Buffer.Pointer;
        break;


    case TYPE_Number:
        /*
         *  Number is included in the object itself
         */
        Obj->Number.Number = UserObj->Number.Value;
        break;


    default:
        return AE_RETURN_VALUE;
        break;
    }


    return AE_OK;
}


/******************************************************************************
 *
 * FUNCTION:    CmBuildInternalPackageObject
 *
 * PARAMETERS:  *Obj            - Pointer to the object we are returning
 *              *Buffer         - a pointer to the caller's buffer to place
 *                                the object in
 *              *SpaceUsed      - a pointer to a dword to return the number
 *                                of bytes used to build the object(s)
 * 
 * RETURN:      Status          - the status of the call
 * 
 * DESCRIPTION: This function is called to place a package object in a user
 *              buffer.  A package object by definition contains other objects.
 *
 *              The buffer is assumed to have sufficient space for the object.
 *              The caller must have verified the buffer length needed using the
 *              CmGetObjectSize function before calling this function.
 * 
 ******************************************************************************/

ACPI_STATUS
CmBuildInternalPackageObject (
    ACPI_OBJECT_INTERNAL    *Obj, 
    char                    *Buffer, 
    UINT32                  *SpaceUsed)
{
    char                    *FreeSpace;
    ACPI_OBJECT             *UserObj;
    UINT32                  CurrentDepth = 0;
    ACPI_STATUS             Status;
    UINT32                  Length = 0;
    UINT32                  ThisIndex;
    UINT32                  Temp;
    ACPI_OBJECT_INTERNAL    *ThisObj;
    ACPI_OBJECT             *ThisUObj;
    register struct Search_st  *LevelPtr;
    

    /*
     *  First package at head of the buffer
     */
    UserObj = (ACPI_OBJECT *)Buffer;

    /*
     *  Free space begins right after the first package
     */
    FreeSpace = Buffer + sizeof(ACPI_OBJECT);


    /*
     *  Initialize the working variables
     */
    
    Level[0].CAObj = Obj;
    Level[0].UserObj = UserObj;
    CurrentDepth = 0;

    memset ((void *) Level, 0, sizeof(Level));

    UserObj->Type = Obj->ValType;
    UserObj->Package.Count = Obj->Package.PkgCount;
    UserObj->Package.Elements = (ACPI_OBJECT *)FreeSpace;


    /*
     *  Build an array of ACPI_OBJECTS in the buffer
     *  and move the free space past it
     */

    FreeSpace += UserObj->Package.Count * sizeof(ACPI_OBJECT);

    LevelPtr = &Level[CurrentDepth];

    while (1)
    {
        ThisIndex   = LevelPtr->Index;
        ThisObj     = (ACPI_OBJECT_INTERNAL *) &LevelPtr->CAObj->Package.PackageElems[ThisIndex];
        ThisUObj    = (ACPI_OBJECT *) &LevelPtr->UserObj->Package.Elements[ThisIndex];

        if (ThisObj->ValType == TYPE_Package)
        {
            /*
             *  If this object is a package then we go one deeper
             */
            if (CurrentDepth >= MAX_OBJECT_DEPTH-1)
            {
                /*
                 *  Too many nested levels of packages for us to handle
                 */
                DEBUG_PRINT (ACPI_ERROR, ("CmBuildPackageObject: Pkg nested too deep (max %d)\n",
                                            MAX_OBJECT_DEPTH));
                return AE_LIMIT;
            }

            /*
             *  Build the package object
             */
            ThisUObj->Type = TYPE_Package;
            ThisUObj->Package.Count = ThisObj->Package.PkgCount;
            ThisUObj->Package.Elements = (ACPI_OBJECT *) FreeSpace;

            /*
             *  Save space for the array of objects (Package elements)
             *  update the buffer length counter
             */
            Temp = ThisUObj->Package.Count * sizeof(ACPI_OBJECT);
            FreeSpace += Temp;
            Length += Temp;

            CurrentDepth++;
            LevelPtr = &Level[CurrentDepth];
            LevelPtr->CAObj = ThisObj;
            LevelPtr->UserObj = ThisUObj;
            LevelPtr->Index = 0;

        }   /* if object is a package */
        
        else
        {
/*            Status = CmBuildSimpleObject(ThisObj, ThisUObj, FreeSpace, &Temp);
*/
            if (Status != AE_OK) {
                /*
                 *  Failure get out
                 */
                return Status;
            }

            FreeSpace += Temp;
            Length +=Temp;

            LevelPtr->Index++;
            while (LevelPtr->Index >= LevelPtr->CAObj->Package.PkgCount)
            {
                /*
                 *  We've handled all of the objects at this level,  This means that we
                 *  have just completed a package.  That package may have contained one
                 *  or more packages itself
                 */
                if (CurrentDepth == 0)
                {
                    /*
                     *  We have handled all of the objects in the top level package
                     *  just add the length of the package objects and get out
                     */
                    *SpaceUsed = Length;
                    return AE_OK;
                }

                /*
                 *  go back up a level and move the index past the just completed
                 *  package object.
                 */
                CurrentDepth--;
                LevelPtr = &Level[CurrentDepth];
                LevelPtr->Index++;
            }
        }   /* else object is NOT a package */
    }   /*  while (1)  */


    /*
     *  We'll never get here, but the compiler whines about return value
     */
    return AE_OK;
}


/******************************************************************************
 *
 * FUNCTION:    CmBuildInternalObject
 *
 * PARAMETERS:  *Obj            - Pointer to the object we are building from
 *              *BufferPtr      - a pointer to a the caller's return buffer
 * 
 * RETURN:      Status          - the status of the call
 * 
 * DESCRIPTION: This function is called to build an API object to be returned to
 *              the caller.
 *
 ******************************************************************************/

ACPI_STATUS
CmBuildInternalObject (
    ACPI_OBJECT             *Obj, 
    ACPI_OBJECT_INTERNAL    *InternalObj)
{
    ACPI_STATUS             Status;


    if (Obj->Type == TYPE_Package)
    {
        /*
         *  Package objects contain other objects (which can be objects)
         *  buildpackage does it all
         */
/*
        Status = CmBuildInternalPackageObject(Obj, RetBuffer->Pointer,
                        &RetBuffer->Length);
*/
        DEBUG_PRINT (ACPI_ERROR, ("CmBuildInternalObject: Packages as parameters not implemented!\n"));
        return AE_NOT_IMPLEMENTED;
    }

    else
    {
        /*
         *  Build a simple object (no nested objects)
         */
        Status = CmBuildInternalSimpleObject(Obj, InternalObj);
        /*
         *  build simple does not include the object size in the length
         *  so we add it in here
         */
    }

    return Status;
}


/******************************************************************************
 *
 * FUNCTION:    CmDeleteInternalObjectList
 *
 * PARAMETERS:  *ObjList        - Pointer to the list to be deleted
 * 
 * RETURN:      Status          - the status of the call
 * 
 * DESCRIPTION: This function deletes an internal object list, including both
 *              simple objects and package objects
 *
 ******************************************************************************/

ACPI_STATUS
CmDeleteInternalObjectList (
    ACPI_OBJECT_INTERNAL    **ObjList)
{
    ACPI_OBJECT_INTERNAL    **Obj;


    /* Walk the null-terminated internal list */

    for (Obj = ObjList; *Obj; Obj++)
    {
        if ((*Obj)->ValType == TYPE_Package)
        {
            /* Delete the package */

            /* TBD: Not implemented yet! */

            DEBUG_PRINT (ACPI_ERROR, ("CmDeleteInternalObjectList: Package deletion not implemented!\n"));
        }

    }


    /* 
     * Free the object block.  The object block base will be the first
     * pointer in the parameter list.
     */

    OsdFree (ObjList[0]);

    /* Now free the parameter pointer list */

    OsdFree (ObjList);

    return AE_OK;
}


