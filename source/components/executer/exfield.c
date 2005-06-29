
/******************************************************************************
 * 
 * Module Name: iefield - ACPI AML (p-code) execution - field manipulation
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


#define __IEFIELD_C__

#include <acpi.h>
#include <interpreter.h>
#include <amlcode.h>
#include <namespace.h>
#include <devices.h>


#define _THIS_MODULE        "iefield.c"
#define _COMPONENT          INTERPRETER


/*****************************************************************************
 * 
 * FUNCTION:    SetupField
 *
 * PARAMETERS:  OBJECT_DESCRIPTOR * ObjDesc         Field to be read or written
 *              OBJECT_DESCRIPTOR * RgnDesc         Region containing field
 *              INT32               FieldBitWidth   Field Width in bits (8, 16, or 32)
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Common processing for ReadField and WriteField
 *
 *  ACPI SPECIFICATION REFERENCES:
 *  16.2.4.3    Each of the Type1Opcodes is defined as specified in in-line
 *              comments below. For each one, use the following definitions.
 *  16.2.4.2    DefBitField     :=  BitFieldOp      SourceBuff  BitIndex    Destination
 *  16.2.4.2    DefByteField    :=  ByteFieldOp     SourceBuff  ByteIndex   Destination
 *  16.2.4.2    DefCreateField  :=  CreateFieldOp   SourceBuff  BitIndex    NumBits     NameString
 *  16.2.4.2    DefDWordField   :=  DWordFieldOp    SourceBuff  ByteIndex   Destination
 *  16.2.4.2    DefWordField    :=  WordFieldOp     SourceBuff  ByteIndex   Destination
 *  16.2.4.2    BitIndex        :=  TermArg=>Integer
 *  16.2.4.2    ByteIndex       :=  TermArg=>Integer
 *  16.2.4.2    Destination     :=  NameString
 *  16.2.4.2    NumBits         :=  TermArg=>Integer
 *  16.2.4.2    SourceBuff      :=  TermArg=>Buffer
 *
 ****************************************************************************/

static INT32
SetupField (OBJECT_DESCRIPTOR *ObjDesc, OBJECT_DESCRIPTOR *RgnDesc, INT32 FieldBitWidth)
{
    OBJECT_DESCRIPTOR   *ObjValDesc = NULL;
    INT32               Excep = S_SUCCESS;
    INT32               FieldByteWidth;


    FUNCTION_TRACE ("SetupField");


    if (!ObjDesc || !RgnDesc)
    {
        DEBUG_PRINT (ACPI_ERROR, ("SetupField: internal error - null handle\n"));
        Excep = S_ERROR;
    }

    else if (TYPE_Region != RgnDesc->ValType)
    {
        DEBUG_PRINT (ACPI_ERROR, ("SetupFld: Needed Region, found %d %s\n",
                        RgnDesc->ValType, NsTypeNames[RgnDesc->ValType]));
        Excep = S_ERROR;
    }

    if (S_SUCCESS == Excep)
    {   
        /* ObjDesc, RgnDesc, and RgnDesc->ValType valid */
        
        FieldByteWidth = FieldBitWidth / 8;     /*  possible values are 1, 2, 4 */

        if ((FieldBitWidth != 8) && 
            (FieldBitWidth != 16) && 
            (FieldBitWidth != 32))
        {
            DEBUG_PRINT (ACPI_ERROR, ("SetupField:internal error: bad width %d\n", FieldBitWidth));
            Excep = S_ERROR;
        }
    }


    if (S_SUCCESS == Excep)
    {   
        /* Everything is valid */

        DEBUG_PRINT (ACPI_INFO, ("SetupField: \n"));

        /* 
         * If the address and length have not been previously evaluated,
         * evaluate them and save the results.
         */
        if (0 == RgnDesc->Region.AdrLenValid)
        {
            /*  address and length have not been previously evaluated   */
            /*  save PCode and PCodeLen on package stack    */

            Excep = PushExecLen (0L);

            if (S_SUCCESS == Excep)
            {   
                /*  PCode and PCodeLen preserved on package stack   */
                /*  Point to Address opcode in AML stream   */


                SetCurrentLoc (&RgnDesc->Region.AdrLoc);

                /* Evaluate the Address opcode */

                if ((Excep = DoOpCode (MODE_Exec)) == S_SUCCESS && 
                    (Excep = GetRvalue ((OBJECT_DESCRIPTOR **) &ObjStack[ObjStackTop]))
                                == S_SUCCESS)
                {
                    /* Capture the address */

                    ObjValDesc = ObjStack[ObjStackTop];


                    if (!ObjValDesc ||
                        ObjValDesc->ValType != (UINT8) TYPE_Number)
                    {
                        DEBUG_PRINT (ACPI_ERROR, ("SetupFld: Malformed Region/Address "
                                    "ObjValDesc = %p, ObjValDesc->ValType = %02Xh, Number = %02Xh\n",
                                    ObjValDesc, ObjValDesc->ValType, (UINT8) TYPE_Number));

                        Excep = S_ERROR;
                    }

                    else
                    {
                        RgnDesc->Region.Address = ObjValDesc->Number.Number;
                    }
                }

                if (S_SUCCESS == Excep)
                {   
                    /* Evaluate the Length opcode */

                    if ((Excep = DoOpCode (MODE_Exec)) == S_SUCCESS &&
                        (Excep = GetRvalue ((OBJECT_DESCRIPTOR **) &ObjStack[ObjStackTop]))
                                    == S_SUCCESS)
                    {
                        /* Capture the length */

                        ObjValDesc = ObjStack[ObjStackTop];

                        if (!ObjValDesc ||
                            ObjValDesc->ValType != (UINT8) TYPE_Number)
                        {

                            DEBUG_PRINT (ACPI_ERROR, ("SetupFld: Malformed Region/Length \n"));
                            Excep = S_ERROR;
                        }

                        else
                        {
                            /*  Region Length valid */

                            RgnDesc->Region.Length = ObjValDesc->Number.Number;

                            /* 
                             * Remember that both Address and Length
                             * have been successfully evaluated and saved.
                             */
                            RgnDesc->Region.AdrLenValid = 1;
                        }
                    }
                }
            }

            if (S_SUCCESS == Excep)
            {
                /*  restore PCode and PCodeLen  */

                Excep = PopExec ();
            }
        }
    }

    if (S_SUCCESS == Excep)
    {
        /* 
         * If (offset rounded up to next multiple of field width)
         * exceeds region length, indicate an error.
         */
        if (RgnDesc->Region.Length <
           (ObjDesc->Field.Offset & ~((UINT32) FieldByteWidth - 1)) + FieldByteWidth)
        {
            /*  
             * offset rounded up to next multiple of field width
             * exceeds region length, indicate an error
             */
            DEBUG_PRINT (ACPI_ERROR,
                    ("SetupField: Operation at %08lx width %d bits exceeds region bound %08lx\n",
                    ObjDesc->Field.Offset, FieldBitWidth, RgnDesc->Region.Length));

            DUMP_STACK_ENTRY (RgnDesc);
            DUMP_STACK_ENTRY (ObjDesc);

            Excep = S_ERROR;
        }
    }

    DEBUG_PRINT (TRACE_EXEC, ("Leave iSetupFld: %s\n", RV[Excep]));

    return Excep;
}


/*****************************************************************************
 * 
 * FUNCTION:    ReadField
 *
 * PARAMETERS:  OBJECT_DESCRIPTOR * ObjDesc         Field to be read
 *              UINT32*             Value           Where to store value
 *              INT32               FieldBitWidth   Field Width in bits (8, 16, or 32)
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Retrieve the value of the given field
 *
 ****************************************************************************/

static INT32
ReadField (OBJECT_DESCRIPTOR *ObjDesc, UINT32 *Value, INT32 FieldBitWidth)
{
    /* ObjDesc is validated by callers */

    OBJECT_DESCRIPTOR   *RgnDesc = NULL;
    UINT32              Address;
    UINT32              LocalValue = 0;
    INT32               FieldByteWidth;
    INT32               Excep;


    FUNCTION_TRACE ("ReadField");


    if (ObjDesc)
    {
        RgnDesc = ObjDesc->Field.Container;
    }


    FieldByteWidth = FieldBitWidth / 8;
    Excep = SetupField (ObjDesc, RgnDesc, FieldBitWidth);
    if (S_SUCCESS != Excep)
    {
        return Excep;
    }

    /*  SetupFld validated RgnDesc and FieldBitWidth    */

    if (!Value)
    {
        Value = &LocalValue;    /*  support reads without saving value  */
    }

    /* 
     * Round offset down to next multiple of
     * field width, and add region base address.
     */
    Address = RgnDesc->Region.Address
            + (ObjDesc->Field.Offset & ~((UINT32) FieldByteWidth - 1));

    if (OUTRANGE (RgnDesc->Region.SpaceId, RegionTypes))
    {
        DEBUG_PRINT (TRACE_OPREGION,
                    ("** ReadField: Read from unknown region SpaceID %d at %08lx width %d ** \n",
                    RgnDesc->Region.SpaceId, Address, FieldBitWidth));
    }

    else
    {
        DEBUG_PRINT (TRACE_OPREGION,
                    ("** Read from %s at %08lx width %d\n",
                    RegionTypes[RgnDesc->Region.SpaceId], Address, FieldBitWidth));
    }


    switch(RgnDesc->Region.SpaceId)
    {
        void *      PhysicalAddrPtr = NULL;
        UINT8       PciBus;
        UINT8       DevFunc;
        UINT8       PciReg;
        UINT8       PciExcep;

    case REGION_SystemMemory:

        /* System memory defined to be in first Mbyte  */
        /* XXX:  Is this true on all OS/platform combinations??  */
        /* RBM:  Do we need to worry about this in protected mode?? */

        if (Address & 0xFFF00000UL)
        {
            DEBUG_PRINT (ACPI_ERROR,
                    ("ReadField:implementation limitation: SystemMemory address %08lx over 1MB\n", Address));
            return S_ERROR;
        }

        /* XXX: was PhysicalAddrPtr = PHYStoFP(Address); */

        /* 
         * XXX: This may be too high an overhead to do every time.
         * Probably should have a mapping cached.
         */

        PhysicalAddrPtr = OsdMapMemory (Address, 4);

        switch (FieldBitWidth)
        {
        /* System memory width */

        case 8:
            *Value = (UINT32)* (UINT8 *) PhysicalAddrPtr;
            break;

        case 16:
            *Value = (UINT32)* (UINT16 *) PhysicalAddrPtr;
            break;

        case 32:
            *Value = * (UINT32 *) PhysicalAddrPtr;
            break;

        default:
            DEBUG_PRINT (ACPI_ERROR,
                    ("ReadField: invalid SystemMemory width %d\n", FieldBitWidth));
            OsdUnMapMemory (PhysicalAddrPtr, 4);
            return S_ERROR;
        }

        OsdUnMapMemory (PhysicalAddrPtr, 4);
        break;

    case REGION_SystemIO:
        switch (FieldBitWidth)
        {
        /* I/O Port width */

        case 8:
            *Value = (UINT32) OsdIn8 ((UINT16) Address);
            break;

        case 16:
            *Value = (UINT32) OsdIn16 ((UINT16) Address);
            break;

        case 32:
            *Value = OsdIn32 ((UINT16) Address);
            break;

        default:
            DEBUG_PRINT (ACPI_ERROR,
                    ("ReadField: invalid SystemIO width %d\n", FieldBitWidth));
            return S_ERROR;
        }
        break;

    case REGION_PCIConfig:
        PciBus = (UINT8) (Address >> 16);
        DevFunc = (UINT8) (Address >> 8);
        PciReg = (UINT8) ((Address >> 2) & 0x3f);

        switch (FieldBitWidth)
        {
        /* PCI Register width */

        case 8:
            PciExcep = OsdReadPciCfgByte (PciBus, DevFunc, PciReg, (UINT8 *) Value);
            break;

        case 16:
            PciExcep = OsdReadPciCfgWord (PciBus, DevFunc, PciReg, (UINT16 *) Value);
            break;

        case 32:
            PciExcep = OsdReadPciCfgDword (PciBus, DevFunc, PciReg, Value);
            break;

        default:
            DEBUG_PRINT (ACPI_ERROR,
                    ("ReadField: invalid PCIConfig width %d\n", FieldBitWidth));
            return S_ERROR;
        }
        if (PciExcep)
        {
            return S_ERROR;
        }
        break;

    case REGION_EmbeddedControl:
    case REGION_SMBus:

        /* XXX - Actual read should happen here */

        DEBUG_PRINT (ACPI_ERROR, ("ReadField: Region type %s not implemented\n",
                RegionTypes[RgnDesc->Region.SpaceId]));
        return S_ERROR;

    default:
        DEBUG_PRINT (ACPI_ERROR, ("ReadField: Unknown region SpaceID %d\n",
                RgnDesc->Region.SpaceId));
        return S_ERROR;
    }

    DEBUG_PRINT (TRACE_OPREGION, (" val %08lx \n", *Value));

    return S_SUCCESS;
}


/*****************************************************************************
 * 
 * FUNCTION:    WriteField
 *
 * PARAMETERS:  OBJECT_DESCRIPTOR * ObjDesc         Field to be set
 *              UINT32              Value           Value to store
 *              INT32               FieldBitWidth   Field Width in bits (8, 16, or 32)
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Store the value into the given field
 *
 ****************************************************************************/

static INT32
WriteField (OBJECT_DESCRIPTOR *ObjDesc, UINT32 Value, INT32 FieldBitWidth)
{
    /* ObjDesc is validated by callers */

    OBJECT_DESCRIPTOR *     RgnDesc = NULL;
    UINT32                  Address;
    INT32                   FieldByteWidth;
    INT32                   Excep = S_SUCCESS;


    FUNCTION_TRACE ("WriteField");

    if (ObjDesc)
    {
        RgnDesc = ObjDesc->Field.Container;
    }

    FieldByteWidth = FieldBitWidth / 8;
    Excep = SetupField (ObjDesc, RgnDesc, FieldBitWidth);
    if (S_SUCCESS != Excep)
    {
        return Excep;
    }

    Address = RgnDesc->Region.Address
                + (ObjDesc->Field.Offset & ~((UINT32) FieldByteWidth - 1));

    if (OUTRANGE (RgnDesc->Region.SpaceId, RegionTypes))
    {
        DEBUG_PRINT (TRACE_OPREGION,
                ("** WriteField: Store %lx in unknown region SpaceID %d at %08lx width %d ** \n",
                Value, RgnDesc->Region.SpaceId, Address, FieldBitWidth));
    }
    else
    {
        DEBUG_PRINT (TRACE_OPREGION,
                ("** Store %lx in %s at %08lx width %d\n",
                Value, RegionTypes[RgnDesc->Region.SpaceId], Address, FieldBitWidth));
    }


    /*  switch on region SpaceID    */

    switch(RgnDesc->Region.SpaceId)
    {
        void        *PhysicalAddrPtr;
        UINT8       PciBus;
        UINT8       DevFunc;
        UINT8       PciReg;
        UINT8       PciExcep;


    case REGION_SystemMemory:

        /* RBM:  Is this an issue in protected mode?  !!! */

        if (Address & 0xFFF00000UL)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "WriteField:implementation limitation: SystemMemory address %08lx over 1MB\n", Address));
            return S_ERROR;
        }


        /* XXX: was PhysicalAddrPtr = PHYStoFP(Address); */

        /* XXX: This may be too high an overhead to do every time.
         * Probably should have a mapping cached.
         */

        PhysicalAddrPtr = OsdMapMemory (Address, 4);
                
        switch (FieldBitWidth)
        {
        case 8:
            *(UINT8 *) PhysicalAddrPtr = (UINT8) Value;
            break;

        case 16:
            *(UINT16 *) PhysicalAddrPtr = (UINT16) Value;
            break;

        case 32:
            *(UINT32 *) PhysicalAddrPtr = Value;
            break;

        default:
            DEBUG_PRINT (ACPI_ERROR, (
                    "WriteField: invalid SystemMemory width %d\n", FieldBitWidth));
            OsdUnMapMemory (PhysicalAddrPtr, 4);
            Excep = S_ERROR;
        }

        OsdUnMapMemory (PhysicalAddrPtr, 4);
        break;

    case REGION_SystemIO:
        switch (FieldBitWidth)
        {
        case 8:
            OsdOut8 ((UINT16) Address, (UINT8) Value);
            break;

        case 16:
            OsdOut16 ((UINT16) Address, (UINT16) Value);
            break;

        case 32:
            OsdOut32 ((UINT16) Address, Value);
            break;

        default:
            DEBUG_PRINT (ACPI_ERROR, (
                    "WriteField: invalid SystemIO width %d\n", FieldBitWidth));
            Excep = S_ERROR;
        }
        break;

    case REGION_PCIConfig:
        PciBus = (UINT8) (Address >> 16);
        DevFunc = (UINT8) (Address >> 8);
        PciReg = (UINT8) ((Address >> 2) & 0x3f);

        switch (FieldBitWidth)
        {
        case 8:
            PciExcep = OsdWritePciCfgByte (PciBus, DevFunc, PciReg, *(UINT8 *)&Value);
            break;

        case 16:
            PciExcep = OsdWritePciCfgWord (PciBus, DevFunc, PciReg, *(UINT16 *)&Value);
            break;

        case 32:
            PciExcep = OsdWritePciCfgDword (PciBus, DevFunc, PciReg, Value);
            break;

        default:
            DEBUG_PRINT (ACPI_ERROR, (
                    "WriteField: invalid PCIConfig width %d\n", FieldBitWidth));
            Excep = S_ERROR;
        }

        if (PciExcep)
        {
            Excep = S_ERROR;
        }
        break;

    case REGION_EmbeddedControl:
    case REGION_SMBus:

        /* XXX - Actual write should happen here */

        DEBUG_PRINT (ACPI_ERROR, ("WriteField: Region type %s not implemented\n",
                        RegionTypes[RgnDesc->Region.SpaceId]));
        Excep = S_ERROR;

    default:
        DEBUG_PRINT (ACPI_ERROR, ("WriteField: Unknown region SpaceID %d\n",
                        RgnDesc->Region.SpaceId));
        Excep = S_ERROR;
    }

    return Excep;
}

/*****************************************************************************
 * 
 * FUNCTION:    AccessNamedField
 *
 * PARAMETERS:  INT32       Mode           ACPI_READ or ACPI_WRITE
 *              NsHandle    NamedField     Handle for field to be accessed
 *              UINT32      *Value          Value to be read or written
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Read or write a named field
 *
 ****************************************************************************/

static INT32
AccessNamedField (INT32 Mode, NsHandle NamedField, UINT32 *Value)
{
    OBJECT_DESCRIPTOR       *ObjDesc = NULL;
    char                    *Type = NULL;
    INT32                   Granularity;
    INT32                   Excep = S_ERROR;
    INT32                   MaxW;
    UINT32                  Mask = 0;
    UINT32                  dValue = 0;
    UINT32                  OldVal = 0;
    INT32                   Locked = FALSE;



    FUNCTION_TRACE ("AccessNamedField");

    ObjDesc = NsGetValue (NamedField);
    if (!ObjDesc)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AccessNamedField:internal error: null value pointer\n"));
    }

    else if (TYPE_DefField != NsGetType (NamedField))
    {
        DEBUG_PRINT (ACPI_ERROR, (
                  "AccessNamedField: Name %4.4s type %d is not a defined field\n",
                  NamedField, NsGetType (NamedField)));
    }

    else
    {
        /* ObjDesc valid and NamedField is defined field    */

        DEBUG_PRINT (ACPI_INFO,
                    ("in AccessNamedField: DefField type and ValPtr OK in nte \n"));
        DUMP_ENTRY (NamedField);

        DEBUG_PRINT (ACPI_INFO, ("ObjDesc = %p, ObjDesc->ValType = %d\n",
                    ObjDesc, ObjDesc->ValType));
        DEBUG_PRINT (ACPI_INFO, (" DatLen = %d, BitOffset = %d\n",
                    ObjDesc->FieldUnit.DatLen, ObjDesc->FieldUnit.BitOffset));

        if (TYPE_DefField != ObjDesc->ValType)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "AccessNamedField:internal error: Name %4.4s type %d does not match value-type %d at %p\n",
                    NamedField, NsGetType (NamedField), ObjDesc->ValType, ObjDesc));
            AmlAppendBlockOwner (ObjDesc);
        }
        else
        {
            Excep = S_SUCCESS;
        }
    }

    if (S_SUCCESS == Excep)
    {

        switch (ObjDesc->Field.Access)
        {
        case ACCESS_AnyAcc:
            Granularity     = 8;
            MaxW            = 32;
            Type            = "UINT32";
            break;

        case ACCESS_ByteAcc:
            Granularity     = 8;
            MaxW            = 8;
            Type            = "UINT8";
            break;

        case ACCESS_WordAcc:
            Granularity     = 16;
            MaxW            = 16;
            Type            = "UINT16";
            break;

        case ACCESS_DWordAcc:
            Granularity     = 32;
            MaxW            = 32;
            Type            = "UINT32";
            break;

        default:
            /*  invalid field access type   */

            DEBUG_PRINT (ACPI_ERROR, (
                        "AccessNamedField: unknown access type %d\n",
                        ObjDesc->Field.Access));
            Excep = S_ERROR;
        }
    }



    if (S_SUCCESS == Excep)
    {
        /*  field has valid access type */

        if (ObjDesc->FieldUnit.DatLen + ObjDesc->FieldUnit.BitOffset > (UINT16) MaxW)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AccessNamedField: Field exceeds %s\n", Type));
            return S_ERROR;
        }
    }

    if (S_SUCCESS == Excep)
    {
        /*  Check lock rule prior to modifing the field */
        
        if ((UINT16) GLOCK_AlwaysLock == ObjDesc->FieldUnit.LockRule)
        {   
            /*  Lock Rule is Lock   */
            
            if (S_ERROR == GetGlobalLock ())

                /*  
                 * lock ownership failed: this is a single threaded implementation
                 * so there is no way some other process should own this.
                 * This means something grabbed the global lock and did not
                 * release it.
                 */
                Excep = S_ERROR;
            else
                Locked = TRUE;
        }
    }


    if (S_SUCCESS == Excep)
    {
        /* 
         * As long as MaxW/2 is wide enough for the data and MaxW > Granularity,
         * divide MaxW by 2.
         */
        while (Granularity < MaxW && 
               ObjDesc->FieldUnit.DatLen + ObjDesc->FieldUnit.BitOffset
                    <= (UINT16) MaxW / 2)
        {
            MaxW /= 2;
        }

        if (ACPI_WRITE == Mode)
        {
            /* Write access */
            /* Construct Mask with 1 bits where the field is, 0 bits elsewhere */

            Mask = (((UINT32) 1 << ObjDesc->FieldUnit.DatLen) - (UINT32) 1)
                                << ObjDesc->Field.BitOffset;
            
            if (Value)
            {
                /* Shift and mask the value into the field position */

                dValue = (*Value << ObjDesc->Field.BitOffset) & Mask;
            }


            if (ObjDesc->FieldUnit.DatLen % Granularity || 
                ObjDesc->FieldUnit.BitOffset)
            {
                /* Write does not fill an integral number of naturally aligned units */

                switch (ObjDesc->Field.UpdateRule)
                {
                case UPDATE_Preserve:

                    /* 
                     * Read the current contents of the byte/word/dword containing
                     * the field, and merge with the new field value.
                     */
                    Excep = ReadField (ObjDesc, &OldVal, MaxW);
                    dValue |= OldVal & ~Mask;
                    break;

                case UPDATE_WriteAsOnes:

                    /* Set positions outside the field to 1's */

                    dValue |= ~Mask;
                    break;

                case UPDATE_WriteAsZeros:

                    /* 
                     * Positions outside the field are already 0
                     * due to "& Mask" above
                     */
                    break;

                default:
                    DEBUG_PRINT (ACPI_ERROR, (
                                "AccessNamedField: Unknown UpdateRule setting %d\n",
                                ObjDesc->Field.UpdateRule));
                    Excep = S_ERROR;
                }
            }


            if (S_SUCCESS == Excep)
            {

                DEBUG_PRINT (ACPI_INFO, (" invoking WriteField\n"));

                /* perform the update */

                Excep = WriteField (ObjDesc, dValue, MaxW);
            }
        }

        else
        {
            /* ACPI_READ access */

            Excep = ReadField (ObjDesc, Value, MaxW);

            if ((S_SUCCESS == Excep) &&
                 Value)
            {
                *Value >>= ObjDesc->Field.BitOffset;
                *Value &= (((UINT32) 1 << ObjDesc->FieldUnit.DatLen) - (UINT32) 1);
            }
        }
    }

    if (Locked)
    {
        ReleaseGlobalLock ();
    }


    return Excep;
}


/*****************************************************************************
 * 
 * FUNCTION:    SetNamedFieldValue
 *
 * PARAMETERS:  NsHandle    NamedField     Handle for field to be set
 *              UINT32      Value          Value to be stored in field
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Store the given value into the field
 *
 ****************************************************************************/

INT32
SetNamedFieldValue (NsHandle NamedField, UINT32 Value)
{
    INT32           Excep = S_ERROR;


    FUNCTION_TRACE ("SetNamedFieldValue");


    if (!NamedField)
    {
        DEBUG_PRINT (ACPI_ERROR, ("SetNamedFieldValue: internal error - null handle\n"));
    }
    else
    {
        Excep = AccessNamedField (ACPI_WRITE, NamedField, &Value);
    }

    return Excep;
}


/*****************************************************************************
 * 
 * FUNCTION:    GetNamedFieldValue
 *
 * PARAMETERS:  NsHandle    NamedField      Handle for field to be read
 *              UINT32      *Value          Where to store value read froom field
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Retrieve the value of the given field
 *
 ****************************************************************************/

INT32
GetNamedFieldValue (NsHandle NamedField, UINT32 *Value)
{
    INT32           Excep = S_ERROR;


    FUNCTION_TRACE ("GetNamedFieldValue");


    if (!NamedField)
    {
        DEBUG_PRINT (ACPI_ERROR, ("GetNamedFieldValue: internal error: null handle\n"));
    }
    else if (!Value)
    {
        DEBUG_PRINT (ACPI_ERROR, ("GetNamedFieldValue: internal error: null pointer\n"));
    }
    else
    {
        Excep = AccessNamedField (ACPI_READ, NamedField, Value);
    }

    return Excep;
}


