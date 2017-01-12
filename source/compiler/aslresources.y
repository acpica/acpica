NoEcho('
/******************************************************************************
 *
 * Module Name: aslresources.y - Bison/Yacc production rules for resources
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2017, Intel Corp.
 * All rights reserved.
 *
 * 2. License
 *
 * 2.1. This is your license from Intel Corp. under its intellectual property
 * rights. You may have additional license terms from the party that provided
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
 * to or modifications of the Original Intel Code. No other license or right
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
 * and the following Disclaimer and Export Compliance provision. In addition,
 * Licensee must cause all Covered Code to which Licensee contributes to
 * contain a file documenting the changes Licensee made to create that Covered
 * Code and the date of any change. Licensee must include in that file the
 * documentation of any changes made by any predecessor Licensee. Licensee
 * must include a prominent statement that the modification is derived,
 * directly or indirectly, from Original Intel Code.
 *
 * 3.2. Redistribution of Source with no Rights to Further Distribute Source.
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification without rights to further distribute source must
 * include the following Disclaimer and Export Compliance provision in the
 * documentation and/or other materials provided with distribution. In
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
 * HERE. ANY SOFTWARE ORIGINATING FROM INTEL OR DERIVED FROM INTEL SOFTWARE
 * IS PROVIDED "AS IS," AND INTEL WILL NOT PROVIDE ANY SUPPORT, ASSISTANCE,
 * INSTALLATION, TRAINING OR OTHER SERVICES. INTEL WILL NOT PROVIDE ANY
 * UPDATES, ENHANCEMENTS OR EXTENSIONS. INTEL SPECIFICALLY DISCLAIMS ANY
 * IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGEMENT AND FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * 4.2. IN NO EVENT SHALL INTEL HAVE ANY LIABILITY TO LICENSEE, ITS LICENSEES
 * OR ANY OTHER THIRD PARTY, FOR ANY LOST PROFITS, LOST DATA, LOSS OF USE OR
 * COSTS OF PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, OR FOR ANY INDIRECT,
 * SPECIAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THIS AGREEMENT, UNDER ANY
 * CAUSE OF ACTION OR THEORY OF LIABILITY, AND IRRESPECTIVE OF WHETHER INTEL
 * HAS ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES. THESE LIMITATIONS
 * SHALL APPLY NOTWITHSTANDING THE FAILURE OF THE ESSENTIAL PURPOSE OF ANY
 * LIMITED REMEDY.
 *
 * 4.3. Licensee shall not export, either directly or indirectly, any of this
 * software or system incorporating such software without first obtaining any
 * required license or other approval from the U. S. Department of Commerce or
 * any other agency or department of the United States Government. In the
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

')


/*******************************************************************************
 *
 * ASL Resource Template Terms
 *
 ******************************************************************************/

/*
 * Note: Create two default nodes to allow conversion to a Buffer AML opcode
 * Also, insert the EndTag at the end of the template.
 */
ResourceTemplateTerm
    : PARSEOP_RESOURCETEMPLATE
        OptionalParentheses
        '{'
        ResourceMacroList '}'       {$$ = TrCreateNode (PARSEOP_RESOURCETEMPLATE,4,
                                          TrCreateLeafNode (PARSEOP_DEFAULT_ARG),
                                          TrCreateLeafNode (PARSEOP_DEFAULT_ARG),
                                          $4,
                                          TrCreateLeafNode (PARSEOP_ENDTAG));}
    ;

OptionalParentheses
    :                               {$$ = NULL;}
    | PARSEOP_OPEN_PAREN
        PARSEOP_CLOSE_PAREN         {$$ = NULL;}
    ;

ResourceMacroList
    :                               {$$ = NULL;}
    | ResourceMacroList
        ResourceMacroTerm           {$$ = TrLinkPeerNode ($1,$2);}
    ;

ResourceMacroTerm
    : DMATerm                       {}
    | DWordIOTerm                   {}
    | DWordMemoryTerm               {}
    | DWordSpaceTerm                {}
    | EndDependentFnTerm            {}
    | ExtendedIOTerm                {}
    | ExtendedMemoryTerm            {}
    | ExtendedSpaceTerm             {}
    | FixedDmaTerm                  {}
    | FixedIOTerm                   {}
    | GpioIntTerm                   {}
    | GpioIoTerm                    {}
    | I2cSerialBusTerm              {}
    | I2cSerialBusTermV2            {}
    | InterruptTerm                 {}
    | IOTerm                        {}
    | IRQNoFlagsTerm                {}
    | IRQTerm                       {}
    | Memory24Term                  {}
    | Memory32FixedTerm             {}
    | Memory32Term                  {}
    | QWordIOTerm                   {}
    | QWordMemoryTerm               {}
    | QWordSpaceTerm                {}
    | RegisterTerm                  {}
    | SpiSerialBusTerm              {}
    | SpiSerialBusTermV2            {}
    | StartDependentFnNoPriTerm     {}
    | StartDependentFnTerm          {}
    | UartSerialBusTerm             {}
    | UartSerialBusTermV2           {}
    | VendorLongTerm                {}
    | VendorShortTerm               {}
    | WordBusNumberTerm             {}
    | WordIOTerm                    {}
    | WordSpaceTerm                 {}
    ;

DMATerm
    : PARSEOP_DMA
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_DMA);}
        DMATypeKeyword
        OptionalBusMasterKeyword
        ',' XferTypeKeyword
        OptionalNameString_Last
        PARSEOP_CLOSE_PAREN '{'
            ByteList '}'            {$$ = TrLinkChildren ($<n>3,5,$4,$5,$7,$8,$11);}
    | PARSEOP_DMA
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

DWordIOTerm
    : PARSEOP_DWORDIO
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_DWORDIO);}
        OptionalResourceType_First
        OptionalMinType
        OptionalMaxType
        OptionalDecodeType
        OptionalRangeType
        ',' DWordConstExpr
        ',' DWordConstExpr
        ',' DWordConstExpr
        ',' DWordConstExpr
        ',' DWordConstExpr
        OptionalByteConstExpr
        OptionalStringData
        OptionalNameString
        OptionalType
        OptionalTranslationType_Last
        PARSEOP_CLOSE_PAREN         {$$ = TrLinkChildren ($<n>3,15,
                                        $4,$5,$6,$7,$8,$10,$12,$14,$16,$18,$19,$20,$21,$22,$23);}
    | PARSEOP_DWORDIO
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

DWordMemoryTerm
    : PARSEOP_DWORDMEMORY
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_DWORDMEMORY);}
        OptionalResourceType_First
        OptionalDecodeType
        OptionalMinType
        OptionalMaxType
        OptionalMemType
        ',' OptionalReadWriteKeyword
        ',' DWordConstExpr
        ',' DWordConstExpr
        ',' DWordConstExpr
        ',' DWordConstExpr
        ',' DWordConstExpr
        OptionalByteConstExpr
        OptionalStringData
        OptionalNameString
        OptionalAddressRange
        OptionalType_Last
        PARSEOP_CLOSE_PAREN         {$$ = TrLinkChildren ($<n>3,16,
                                        $4,$5,$6,$7,$8,$10,$12,$14,$16,$18,$20,$21,$22,$23,$24,$25);}
    | PARSEOP_DWORDMEMORY
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

DWordSpaceTerm
    : PARSEOP_DWORDSPACE
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_DWORDSPACE);}
        ByteConstExpr               {UtCheckIntegerRange ($4, 0xC0, 0xFF);}
        OptionalResourceType
        OptionalDecodeType
        OptionalMinType
        OptionalMaxType
        ',' ByteConstExpr
        ',' DWordConstExpr
        ',' DWordConstExpr
        ',' DWordConstExpr
        ',' DWordConstExpr
        ',' DWordConstExpr
        OptionalByteConstExpr
        OptionalStringData
        OptionalNameString_Last
        PARSEOP_CLOSE_PAREN         {$$ = TrLinkChildren ($<n>3,14,
                                        $4,$6,$7,$8,$9,$11,$13,$15,$17,$19,$21,$22,$23,$24);}
    | PARSEOP_DWORDSPACE
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

EndDependentFnTerm
    : PARSEOP_ENDDEPENDENTFN
        PARSEOP_OPEN_PAREN
        PARSEOP_CLOSE_PAREN         {$$ = TrCreateLeafNode (PARSEOP_ENDDEPENDENTFN);}
    | PARSEOP_ENDDEPENDENTFN
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

ExtendedIOTerm
    : PARSEOP_EXTENDEDIO
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_EXTENDEDIO);}
        OptionalResourceType_First
        OptionalMinType
        OptionalMaxType
        OptionalDecodeType
        OptionalRangeType
        ',' QWordConstExpr
        ',' QWordConstExpr
        ',' QWordConstExpr
        ',' QWordConstExpr
        ',' QWordConstExpr
        OptionalQWordConstExpr
        OptionalNameString
        OptionalType
        OptionalTranslationType_Last
        PARSEOP_CLOSE_PAREN         {$$ = TrLinkChildren ($<n>3,14,
                                        $4,$5,$6,$7,$8,$10,$12,$14,$16,$18,$19,$20,$21,$22);}
    | PARSEOP_EXTENDEDIO
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

ExtendedMemoryTerm
    : PARSEOP_EXTENDEDMEMORY
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_EXTENDEDMEMORY);}
        OptionalResourceType_First
        OptionalDecodeType
        OptionalMinType
        OptionalMaxType
        OptionalMemType
        ',' OptionalReadWriteKeyword
        ',' QWordConstExpr
        ',' QWordConstExpr
        ',' QWordConstExpr
        ',' QWordConstExpr
        ',' QWordConstExpr
        OptionalQWordConstExpr
        OptionalNameString
        OptionalAddressRange
        OptionalType_Last
        PARSEOP_CLOSE_PAREN         {$$ = TrLinkChildren ($<n>3,15,
                                        $4,$5,$6,$7,$8,$10,$12,$14,$16,$18,$20,$21,$22,$23,$24);}
    | PARSEOP_EXTENDEDMEMORY
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

ExtendedSpaceTerm
    : PARSEOP_EXTENDEDSPACE PARSEOP_OPEN_PAREN     {$<n>$ = TrCreateLeafNode (PARSEOP_EXTENDEDSPACE);}
        ByteConstExpr               {UtCheckIntegerRange ($4, 0xC0, 0xFF);}
        OptionalResourceType
        OptionalDecodeType
        OptionalMinType
        OptionalMaxType
        ',' ByteConstExpr
        ',' QWordConstExpr
        ',' QWordConstExpr
        ',' QWordConstExpr
        ',' QWordConstExpr
        ',' QWordConstExpr
        OptionalQWordConstExpr
        OptionalNameString_Last
        PARSEOP_CLOSE_PAREN                         {$$ = TrLinkChildren ($<n>3,13,
                                        $4,$6,$7,$8,$9,$11,$13,$15,$17,$19,$21,$22,$23);}
    | PARSEOP_EXTENDEDSPACE
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN                   {$$ = AslDoError(); yyclearin;}
    ;

FixedDmaTerm
    : PARSEOP_FIXEDDMA
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_FIXEDDMA);}
        WordConstExpr               /* 04: DMA RequestLines */
        ',' WordConstExpr           /* 06: DMA Channels */
        OptionalXferSize            /* 07: DMA TransferSize */
        OptionalNameString          /* 08: DescriptorName */
        PARSEOP_CLOSE_PAREN                         {$$ = TrLinkChildren ($<n>3,4,$4,$6,$7,$8);}
    | PARSEOP_FIXEDDMA
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN                   {$$ = AslDoError(); yyclearin;}
    ;

FixedIOTerm
    : PARSEOP_FIXEDIO
        PARSEOP_OPEN_PAREN           {$<n>$ = TrCreateLeafNode (PARSEOP_FIXEDIO);}
        WordConstExpr
        ',' ByteConstExpr
        OptionalNameString_Last
        PARSEOP_CLOSE_PAREN                         {$$ = TrLinkChildren ($<n>3,3,$4,$6,$7);}
    | PARSEOP_FIXEDIO
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN                   {$$ = AslDoError(); yyclearin;}
    ;

GpioIntTerm
    : PARSEOP_GPIO_INT
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_GPIO_INT);}
        InterruptTypeKeyword        /* 04: InterruptType */
        ',' InterruptLevel          /* 06: InterruptLevel */
        OptionalShareType           /* 07: SharedType */
        ',' PinConfigByte           /* 09: PinConfig */
        OptionalWordConstExpr       /* 10: DebounceTimeout */
        ',' StringData              /* 12: ResourceSource */
        OptionalByteConstExpr       /* 13: ResourceSourceIndex */
        OptionalResourceType        /* 14: ResourceType */
        OptionalNameString          /* 15: DescriptorName */
        OptionalBuffer_Last         /* 16: VendorData */
        PARSEOP_CLOSE_PAREN '{'
            DWordConstExpr '}'      {$$ = TrLinkChildren ($<n>3,11,
                                        $4,$6,$7,$9,$10,$12,$13,$14,$15,$16,$19);}
    | PARSEOP_GPIO_INT
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

GpioIoTerm
    : PARSEOP_GPIO_IO
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_GPIO_IO);}
        OptionalShareType_First     /* 04: SharedType */
        ',' PinConfigByte           /* 06: PinConfig */
        OptionalWordConstExpr       /* 07: DebounceTimeout */
        OptionalWordConstExpr       /* 08: DriveStrength */
        OptionalIoRestriction       /* 09: IoRestriction */
        ',' StringData              /* 11: ResourceSource */
        OptionalByteConstExpr       /* 12: ResourceSourceIndex */
        OptionalResourceType        /* 13: ResourceType */
        OptionalNameString          /* 14: DescriptorName */
        OptionalBuffer_Last         /* 15: VendorData */
        PARSEOP_CLOSE_PAREN '{'
            DWordList '}'           {$$ = TrLinkChildren ($<n>3,11,
                                        $4,$6,$7,$8,$9,$11,$12,$13,$14,$15,$18);}
    | PARSEOP_GPIO_IO
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN                   {$$ = AslDoError(); yyclearin;}
    ;

I2cSerialBusTerm
    : PARSEOP_I2C_SERIALBUS
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_I2C_SERIALBUS);}
        WordConstExpr               /* 04: SlaveAddress */
        OptionalSlaveMode           /* 05: SlaveMode */
        ',' DWordConstExpr          /* 07: ConnectionSpeed */
        OptionalAddressingMode      /* 08: AddressingMode */
        ',' StringData              /* 10: ResourceSource */
        OptionalByteConstExpr       /* 11: ResourceSourceIndex */
        OptionalResourceType        /* 12: ResourceType */
        OptionalNameString          /* 13: DescriptorName */
        OptionalBuffer_Last         /* 14: VendorData */
        PARSEOP_CLOSE_PAREN         {$$ = TrLinkChildren ($<n>3,10,
                                        $4,$5,$7,$8,$10,$11,$12,$13,
                                        TrCreateLeafNode (PARSEOP_DEFAULT_ARG),$14);}
    | PARSEOP_I2C_SERIALBUS
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

I2cSerialBusTermV2
    : PARSEOP_I2C_SERIALBUS_V2
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_I2C_SERIALBUS_V2);}
        WordConstExpr               /* 04: SlaveAddress */
        OptionalSlaveMode           /* 05: SlaveMode */
        ',' DWordConstExpr          /* 07: ConnectionSpeed */
        OptionalAddressingMode      /* 08: AddressingMode */
        ',' StringData              /* 10: ResourceSource */
        OptionalByteConstExpr       /* 11: ResourceSourceIndex */
        OptionalResourceType        /* 12: ResourceType */
        OptionalNameString          /* 13: DescriptorName */
        OptionalShareType           /* 14: Share */
        OptionalBuffer_Last         /* 15: VendorData */
        PARSEOP_CLOSE_PAREN         {$$ = TrLinkChildren ($<n>3,10,
                                        $4,$5,$7,$8,$10,$11,$12,$13,$14,$15);}
    | PARSEOP_I2C_SERIALBUS_V2
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

InterruptTerm
    : PARSEOP_INTERRUPT
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_INTERRUPT);}
        OptionalResourceType_First
        ',' InterruptTypeKeyword
        ',' InterruptLevel
        OptionalShareType
        OptionalByteConstExpr
        OptionalStringData
        OptionalNameString_Last
        PARSEOP_CLOSE_PAREN '{'
            DWordList '}'           {$$ = TrLinkChildren ($<n>3,8,
                                        $4,$6,$8,$9,$10,$11,$12,$15);}
    | PARSEOP_INTERRUPT
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

IOTerm
    : PARSEOP_IO
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_IO);}
        IODecodeKeyword
        ',' WordConstExpr
        ',' WordConstExpr
        ',' ByteConstExpr
        ',' ByteConstExpr
        OptionalNameString_Last
        PARSEOP_CLOSE_PAREN         {$$ = TrLinkChildren ($<n>3,6,$4,$6,$8,$10,$12,$13);}
    | PARSEOP_IO
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

IRQNoFlagsTerm
    : PARSEOP_IRQNOFLAGS
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_IRQNOFLAGS);}
        OptionalNameString_First
        PARSEOP_CLOSE_PAREN '{'
            ByteList '}'            {$$ = TrLinkChildren ($<n>3,2,$4,$7);}
    | PARSEOP_IRQNOFLAGS
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

IRQTerm
    : PARSEOP_IRQ
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_IRQ);}
        InterruptTypeKeyword
        ',' InterruptLevel
        OptionalShareType
        OptionalNameString_Last
        PARSEOP_CLOSE_PAREN '{'
            ByteList '}'            {$$ = TrLinkChildren ($<n>3,5,$4,$6,$7,$8,$11);}
    | PARSEOP_IRQ
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

Memory24Term
    : PARSEOP_MEMORY24
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_MEMORY24);}
        OptionalReadWriteKeyword
        ',' WordConstExpr
        ',' WordConstExpr
        ',' WordConstExpr
        ',' WordConstExpr
        OptionalNameString_Last
        PARSEOP_CLOSE_PAREN         {$$ = TrLinkChildren ($<n>3,6,$4,$6,$8,$10,$12,$13);}
    | PARSEOP_MEMORY24
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

Memory32FixedTerm
    : PARSEOP_MEMORY32FIXED
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_MEMORY32FIXED);}
        OptionalReadWriteKeyword
        ',' DWordConstExpr
        ',' DWordConstExpr
        OptionalNameString_Last
        PARSEOP_CLOSE_PAREN         {$$ = TrLinkChildren ($<n>3,4,$4,$6,$8,$9);}
    | PARSEOP_MEMORY32FIXED
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

Memory32Term
    : PARSEOP_MEMORY32
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_MEMORY32);}
        OptionalReadWriteKeyword
        ',' DWordConstExpr
        ',' DWordConstExpr
        ',' DWordConstExpr
        ',' DWordConstExpr
        OptionalNameString_Last
        PARSEOP_CLOSE_PAREN         {$$ = TrLinkChildren ($<n>3,6,$4,$6,$8,$10,$12,$13);}
    | PARSEOP_MEMORY32
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

QWordIOTerm
    : PARSEOP_QWORDIO
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_QWORDIO);}
        OptionalResourceType_First
        OptionalMinType
        OptionalMaxType
        OptionalDecodeType
        OptionalRangeType
        ',' QWordConstExpr
        ',' QWordConstExpr
        ',' QWordConstExpr
        ',' QWordConstExpr
        ',' QWordConstExpr
        OptionalByteConstExpr
        OptionalStringData
        OptionalNameString
        OptionalType
        OptionalTranslationType_Last
        PARSEOP_CLOSE_PAREN         {$$ = TrLinkChildren ($<n>3,15,
                                        $4,$5,$6,$7,$8,$10,$12,$14,$16,$18,$19,$20,$21,$22,$23);}
    | PARSEOP_QWORDIO
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

QWordMemoryTerm
    : PARSEOP_QWORDMEMORY
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_QWORDMEMORY);}
        OptionalResourceType_First
        OptionalDecodeType
        OptionalMinType
        OptionalMaxType
        OptionalMemType
        ',' OptionalReadWriteKeyword
        ',' QWordConstExpr
        ',' QWordConstExpr
        ',' QWordConstExpr
        ',' QWordConstExpr
        ',' QWordConstExpr
        OptionalByteConstExpr
        OptionalStringData
        OptionalNameString
        OptionalAddressRange
        OptionalType_Last
        PARSEOP_CLOSE_PAREN         {$$ = TrLinkChildren ($<n>3,16,
                                        $4,$5,$6,$7,$8,$10,$12,$14,$16,$18,$20,$21,$22,$23,$24,$25);}
    | PARSEOP_QWORDMEMORY
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

QWordSpaceTerm
    : PARSEOP_QWORDSPACE
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_QWORDSPACE);}
        ByteConstExpr               {UtCheckIntegerRange ($4, 0xC0, 0xFF);}
        OptionalResourceType
        OptionalDecodeType
        OptionalMinType
        OptionalMaxType
        ',' ByteConstExpr
        ',' QWordConstExpr
        ',' QWordConstExpr
        ',' QWordConstExpr
        ',' QWordConstExpr
        ',' QWordConstExpr
        OptionalByteConstExpr
        OptionalStringData
        OptionalNameString_Last
        PARSEOP_CLOSE_PAREN         {$$ = TrLinkChildren ($<n>3,14,
                                        $4,$6,$7,$8,$9,$11,$13,$15,$17,$19,$21,$22,$23,$24);}
    | PARSEOP_QWORDSPACE
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

RegisterTerm
    : PARSEOP_REGISTER
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_REGISTER);}
        AddressSpaceKeyword
        ',' ByteConstExpr
        ',' ByteConstExpr
        ',' QWordConstExpr
        OptionalAccessSize
        OptionalNameString_Last
        PARSEOP_CLOSE_PAREN         {$$ = TrLinkChildren ($<n>3,6,$4,$6,$8,$10,$11,$12);}
    | PARSEOP_REGISTER
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

SpiSerialBusTerm
    : PARSEOP_SPI_SERIALBUS
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_SPI_SERIALBUS);}
        WordConstExpr               /* 04: DeviceSelection */
        OptionalDevicePolarity      /* 05: DevicePolarity */
        OptionalWireMode            /* 06: WireMode */
        ',' ByteConstExpr           /* 08: DataBitLength */
        OptionalSlaveMode           /* 09: SlaveMode */
        ',' DWordConstExpr          /* 11: ConnectionSpeed */
        ',' ClockPolarityKeyword    /* 13: ClockPolarity */
        ',' ClockPhaseKeyword       /* 15: ClockPhase */
        ',' StringData              /* 17: ResourceSource */
        OptionalByteConstExpr       /* 18: ResourceSourceIndex */
        OptionalResourceType        /* 19: ResourceType */
        OptionalNameString          /* 20: DescriptorName */
        OptionalBuffer_Last         /* 21: VendorData */
        PARSEOP_CLOSE_PAREN         {$$ = TrLinkChildren ($<n>3,14,
                                        $4,$5,$6,$8,$9,$11,$13,$15,$17,$18,$19,$20,
                                        TrCreateLeafNode (PARSEOP_DEFAULT_ARG),$21);}
    | PARSEOP_SPI_SERIALBUS
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

SpiSerialBusTermV2
    : PARSEOP_SPI_SERIALBUS_V2
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_SPI_SERIALBUS_V2);}
        WordConstExpr               /* 04: DeviceSelection */
        OptionalDevicePolarity      /* 05: DevicePolarity */
        OptionalWireMode            /* 06: WireMode */
        ',' ByteConstExpr           /* 08: DataBitLength */
        OptionalSlaveMode           /* 09: SlaveMode */
        ',' DWordConstExpr          /* 11: ConnectionSpeed */
        ',' ClockPolarityKeyword    /* 13: ClockPolarity */
        ',' ClockPhaseKeyword       /* 15: ClockPhase */
        ',' StringData              /* 17: ResourceSource */
        OptionalByteConstExpr       /* 18: ResourceSourceIndex */
        OptionalResourceType        /* 19: ResourceType */
        OptionalNameString          /* 20: DescriptorName */
        OptionalShareType           /* 21: Share */
        OptionalBuffer_Last         /* 22: VendorData */
        PARSEOP_CLOSE_PAREN         {$$ = TrLinkChildren ($<n>3,14,
                                        $4,$5,$6,$8,$9,$11,$13,$15,$17,$18,$19,$20,$21,$22);}
    | PARSEOP_SPI_SERIALBUS_V2
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

StartDependentFnNoPriTerm
    : PARSEOP_STARTDEPENDENTFN_NOPRI
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_STARTDEPENDENTFN_NOPRI);}
        PARSEOP_CLOSE_PAREN '{'
        ResourceMacroList '}'       {$$ = TrLinkChildren ($<n>3,1,$6);}
    | PARSEOP_STARTDEPENDENTFN_NOPRI
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

StartDependentFnTerm
    : PARSEOP_STARTDEPENDENTFN
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_STARTDEPENDENTFN);}
        ByteConstExpr
        ',' ByteConstExpr
        PARSEOP_CLOSE_PAREN '{'
        ResourceMacroList '}'       {$$ = TrLinkChildren ($<n>3,3,$4,$6,$9);}
    | PARSEOP_STARTDEPENDENTFN
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

UartSerialBusTerm
    : PARSEOP_UART_SERIALBUS
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_UART_SERIALBUS);}
        DWordConstExpr              /* 04: ConnectionSpeed */
        OptionalBitsPerByte         /* 05: BitsPerByte */
        OptionalStopBits            /* 06: StopBits */
        ',' ByteConstExpr           /* 08: LinesInUse */
        OptionalEndian              /* 09: Endianess */
        OptionalParityType          /* 10: Parity */
        OptionalFlowControl         /* 11: FlowControl */
        ',' WordConstExpr           /* 13: Rx BufferSize */
        ',' WordConstExpr           /* 15: Tx BufferSize */
        ',' StringData              /* 17: ResourceSource */
        OptionalByteConstExpr       /* 18: ResourceSourceIndex */
        OptionalResourceType        /* 19: ResourceType */
        OptionalNameString          /* 20: DescriptorName */
        OptionalBuffer_Last         /* 21: VendorData */
        PARSEOP_CLOSE_PAREN         {$$ = TrLinkChildren ($<n>3,15,
                                        $4,$5,$6,$8,$9,$10,$11,$13,$15,$17,$18,$19,$20,
                                        TrCreateLeafNode (PARSEOP_DEFAULT_ARG),$21);}
    | PARSEOP_UART_SERIALBUS
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

UartSerialBusTermV2
    : PARSEOP_UART_SERIALBUS_V2
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_UART_SERIALBUS_V2);}
        DWordConstExpr              /* 04: ConnectionSpeed */
        OptionalBitsPerByte         /* 05: BitsPerByte */
        OptionalStopBits            /* 06: StopBits */
        ',' ByteConstExpr           /* 08: LinesInUse */
        OptionalEndian              /* 09: Endianess */
        OptionalParityType          /* 10: Parity */
        OptionalFlowControl         /* 11: FlowControl */
        ',' WordConstExpr           /* 13: Rx BufferSize */
        ',' WordConstExpr           /* 15: Tx BufferSize */
        ',' StringData              /* 17: ResourceSource */
        OptionalByteConstExpr       /* 18: ResourceSourceIndex */
        OptionalResourceType        /* 19: ResourceType */
        OptionalNameString          /* 20: DescriptorName */
        OptionalShareType           /* 21: Share */
        OptionalBuffer_Last         /* 22: VendorData */
        PARSEOP_CLOSE_PAREN         {$$ = TrLinkChildren ($<n>3,15,
                                        $4,$5,$6,$8,$9,$10,$11,$13,$15,$17,$18,$19,$20,$21,$22);}
    | PARSEOP_UART_SERIALBUS_V2
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

VendorLongTerm
    : PARSEOP_VENDORLONG
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_VENDORLONG);}
        OptionalNameString_First
        PARSEOP_CLOSE_PAREN '{'
            ByteList '}'            {$$ = TrLinkChildren ($<n>3,2,$4,$7);}
    | PARSEOP_VENDORLONG
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

VendorShortTerm
    : PARSEOP_VENDORSHORT
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_VENDORSHORT);}
        OptionalNameString_First
        PARSEOP_CLOSE_PAREN '{'
            ByteList '}'            {$$ = TrLinkChildren ($<n>3,2,$4,$7);}
    | PARSEOP_VENDORSHORT
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

WordBusNumberTerm
    : PARSEOP_WORDBUSNUMBER
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_WORDBUSNUMBER);}
        OptionalResourceType_First
        OptionalMinType
        OptionalMaxType
        OptionalDecodeType
        ',' WordConstExpr
        ',' WordConstExpr
        ',' WordConstExpr
        ',' WordConstExpr
        ',' WordConstExpr
        OptionalByteConstExpr
        OptionalStringData
        OptionalNameString_Last
        PARSEOP_CLOSE_PAREN         {$$ = TrLinkChildren ($<n>3,12,
                                        $4,$5,$6,$7,$9,$11,$13,$15,$17,$18,$19,$20);}
    | PARSEOP_WORDBUSNUMBER
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

WordIOTerm
    : PARSEOP_WORDIO
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_WORDIO);}
        OptionalResourceType_First
        OptionalMinType
        OptionalMaxType
        OptionalDecodeType
        OptionalRangeType
        ',' WordConstExpr
        ',' WordConstExpr
        ',' WordConstExpr
        ',' WordConstExpr
        ',' WordConstExpr
        OptionalByteConstExpr
        OptionalStringData
        OptionalNameString
        OptionalType
        OptionalTranslationType_Last
        PARSEOP_CLOSE_PAREN         {$$ = TrLinkChildren ($<n>3,15,
                                        $4,$5,$6,$7,$8,$10,$12,$14,$16,$18,$19,$20,$21,$22,$23);}
    | PARSEOP_WORDIO
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;

WordSpaceTerm
    : PARSEOP_WORDSPACE
        PARSEOP_OPEN_PAREN          {$<n>$ = TrCreateLeafNode (PARSEOP_WORDSPACE);}
        ByteConstExpr               {UtCheckIntegerRange ($4, 0xC0, 0xFF);}
        OptionalResourceType
        OptionalDecodeType
        OptionalMinType
        OptionalMaxType
        ',' ByteConstExpr
        ',' WordConstExpr
        ',' WordConstExpr
        ',' WordConstExpr
        ',' WordConstExpr
        ',' WordConstExpr
        OptionalByteConstExpr
        OptionalStringData
        OptionalNameString_Last
        PARSEOP_CLOSE_PAREN         {$$ = TrLinkChildren ($<n>3,14,
                                        $4,$6,$7,$8,$9,$11,$13,$15,$17,$19,$21,$22,$23,$24);}
    | PARSEOP_WORDSPACE
        PARSEOP_OPEN_PAREN
        error PARSEOP_CLOSE_PAREN   {$$ = AslDoError(); yyclearin;}
    ;
