    /*
     * Some or all of this work - Copyright (c) 2006 - 2018, Intel Corp.
     *
     * Redistribution and use in source and binary forms, with or without modification,
     * are permitted provided that the following conditions are met:
     *
     * Redistributions of source code must retain the above copyright notice,
     * this list of conditions and the following disclaimer.
     * Redistributions in binary form must reproduce the above copyright notice,
     * this list of conditions and the following disclaimer in the documentation
     * and/or other materials provided with the distribution.
     * Neither the name of Intel Corporation nor the names of its contributors
     * may be used to endorse or promote products derived from this software
     * without specific prior written permission.
     *
     * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
     * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
     * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
     * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
     * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
     * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
     * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
     * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
     * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
     * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
     */
    /*
     * Resource Descriptor macros
     *
     * Word Bus Number Resource Descriptor Macro
     */
    Name (P428, Package (0x19)
    {
        ResourceTemplate ()
        {
            WordBusNumber (ResourceProducer, MinNotFixed, MaxNotFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceProducer, MinNotFixed, MaxNotFixed, SubDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceProducer, MinNotFixed, MaxFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceProducer, MinNotFixed, MaxFixed, SubDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceProducer, MinFixed, MaxNotFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceProducer, MinFixed, MaxNotFixed, SubDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceProducer, MinFixed, MaxFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceProducer, MinFixed, MaxFixed, SubDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinNotFixed, MaxNotFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinNotFixed, MaxNotFixed, SubDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinNotFixed, MaxFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinNotFixed, MaxFixed, SubDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinFixed, MaxNotFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinFixed, MaxNotFixed, SubDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinFixed, MaxFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinFixed, MaxFixed, SubDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinNotFixed, MaxNotFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinNotFixed, MaxNotFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinNotFixed, MaxNotFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                0x01, "", )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinNotFixed, MaxNotFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                0x0F, "P", )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinNotFixed, MaxNotFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                0xF0, "PATH", )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinNotFixed, MaxNotFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                0xFF, "!\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ !\"#$%&\'()*", )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinFixed, MaxFixed, SubDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                0xFF, "PATHPATHPATH", )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinFixed, MaxFixed, SubDecode,
                0x0000,             // Granularity
                0x0000,             // Range Minimum
                0x0000,             // Range Maximum
                0x0000,             // Translation Offset
                0x0000,             // Length
                0xFF, "PATHPATHPATH", )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinNotFixed, MaxNotFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                0x0F,, )
        }
    })
    /*
     ACPI Specification, Revision 3.0, September 2, 2004
     6.4.3.5.3   Word Address Space Descriptor
     Bus Number Word Address Space Descriptor layout:
     Byte 0 (Tag Bits): Value=10001000B (0x88) (Type = 1, Large item name = 0x8)
     Byte 1 (Length, bits[7:0]): Variable: Value = 13 (minimum)
     Byte 2 (Length, bits[15:8]): Variable: Value = 0 (minimum)
     Byte 3 (Resource Type):
     2		Bus number range
     Byte 4 (General Flags):
     Bits[7:4] 	Reserved (must be 0)
     Bit[3] 		Min Address Fixed, _MAF:
     1	The specified maximum address is fixed
     0	The specified maximum address is not fixed
     and can be changed
     Bit[2] 		Max Address Fixed,_MIF:
     1	The specified minimum address is fixed
     0	The specified minimum address is not fixed
     and can be changed
     Bit[1] 		Decode Type, _DEC:
     1	This bridge subtractively decodes this address
     (top level bridges only)
     0	This bridge positively decodes this address
     Bit[0] 		Consumer/Producer:
     1-This device consumes this resource
     0-This device produces and consumes this resource
     Byte 5 (Type Specific Flags):
     Flags that are specific to each resource type. The meaning of the flags
     in this field depends on the value of the Resource Type field (see above)
     Bit[7:0]	Reserved (must be 0)
     Byte 6 (Address space granularity, _GRA bits[7:0]):
     A set bit in this mask means that this bit is decoded. All bits less
     significant than the most significant set bit must be set. (in other
     words, the value of the full Address Space Granularity field (all 16
     bits) must be a number (2**n-1).
     Byte 7 (Address space granularity, _GRA bits[15:8])
     Byte 8 (Address range minimum, _MIN bits [7:0]):
     For bridges that translate addresses, this is the address space
     on the secondary side of the bridge
     Byte 9 (Address range minimum, _MIN bits[15:8])
     Byte 10 (Address range maximum, _MAX bits [7:0]): See comment for _MIN
     Byte 11 (Address range maximum, _MAX bits[15:8])
     Byte 12 (Address Translation offset, _TRA bits [7:0]):
     For bridges that translate addresses across the bridge, this is the
     offset that must be added to the address on the secondary side to obtain
     the address on the primary side. Non-bridge devices must list 0 for all
     Address Translation offset bits
     Byte 13 (Address Translation offset, _TRA bits[15:8])
     Byte 14 (Address Length, _LEN bits [7:0])
     Byte 15 (Address Length, _LEN bits[15:8])
     Byte 16 (Resource Source Index):
     (Optional) Only present if Resource Source (below) is present. This
     field gives an index to the specific resource descriptor that this
     device consumes from in the current resource template for the device
     object pointed to in Resource Source
     String (Resource Source):
     (Optional) If present, the device that uses this descriptor consumes
     its resources from the resources produced by the named device object.
     If not present, the device consumes its resources out of a global pool.
     If not present, the device consumes this resource from its hierarchical
     parent.
     */
    Name (P429, Package (0x19)
    {
        /* Byte 4 (General Flags) of Word Address Space Descriptor */

        ResourceTemplate ()
        {
            WordBusNumber (ResourceProducer, MinNotFixed, MaxNotFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceProducer, MinNotFixed, MaxNotFixed, SubDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceProducer, MinNotFixed, MaxFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceProducer, MinNotFixed, MaxFixed, SubDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceProducer, MinFixed, MaxNotFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceProducer, MinFixed, MaxNotFixed, SubDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceProducer, MinFixed, MaxFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceProducer, MinFixed, MaxFixed, SubDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinNotFixed, MaxNotFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinNotFixed, MaxNotFixed, SubDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinNotFixed, MaxFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinNotFixed, MaxFixed, SubDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinFixed, MaxNotFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinFixed, MaxNotFixed, SubDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinFixed, MaxFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinFixed, MaxFixed, SubDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        /* Particular cases */

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinNotFixed, MaxNotFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinNotFixed, MaxNotFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                ,, )
        }, 

        /* Resource Source */

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinNotFixed, MaxNotFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                0x01, "", )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinNotFixed, MaxNotFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                0x0F, "P", )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinNotFixed, MaxNotFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                0xF0, "PATH", )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinNotFixed, MaxNotFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                0xFF, "!\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ !\"#$%&\'()*", )
        }, 

        /* Particular cases */

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinFixed, MaxFixed, SubDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                0xFF, "PATHPATHPATH", )
        }, 

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinFixed, MaxFixed, SubDecode,
                0x0000,             // Granularity
                0x0000,             // Range Minimum
                0x0000,             // Range Maximum
                0x0000,             // Translation Offset
                0x0000,             // Length
                0xFF, "PATHPATHPATH", )
        }, 

        /* 20051021, relaxation for omitted ResourceSource (bug-fix 70 rejection) */

        ResourceTemplate ()
        {
            WordBusNumber (ResourceConsumer, MinNotFixed, MaxNotFixed, PosDecode,
                0xF6F7,             // Granularity
                0xF8F9,             // Range Minimum
                0xFAFB,             // Range Maximum
                0xFCFD,             // Translation Offset
                0xFEFF,             // Length
                0x0F,, )
        }
    })
    Method (RT12, 0, Serialized)
    {
        Name (TS, "RT12")
        /* Emit test header, set the filename */

        THDR (TS, "WordBusNumber Resource Descriptor Macro", "wordbusnumber.asl")
        /* Main test case for packages above */

        M330 (TS, 0x19, "p428", P428, P429)
        /* Check resource descriptor tag offsets */

        Local0 = ResourceTemplate ()
            {
                WordBusNumber (ResourceProducer, MinNotFixed, MaxNotFixed, PosDecode,
                    0xF6F7,             // Granularity
                    0xF8F9,             // Range Minimum
                    0xFAFB,             // Range Maximum
                    0xFCFD,             // Translation Offset
                    0xFEFF,             // Length
                    ,, )
                WordBusNumber (ResourceConsumer, MinNotFixed, MaxNotFixed, PosDecode,
                    0xF6F7,             // Granularity
                    0xF8F9,             // Range Minimum
                    0xFAFB,             // Range Maximum
                    0xFCFD,             // Translation Offset
                    0xFEFF,             // Length
                    ,, )
            }
        M331 (TS, 0x01, 0x21, 0x21, 0xA1, 0xA1, "_DEC")
        M331 (TS, 0x02, 0x22, 0x22, 0xA2, 0xA2, "_MIF")
        M331 (TS, 0x03, 0x23, 0x23, 0xA3, 0xA3, "_MAF")
        M331 (TS, 0x07, 0x30, 0x30, 0xB0, 0xB0, "_GRA")
        M331 (TS, 0x08, 0x40, 0x40, 0xC0, 0xC0, "_MIN")
        M331 (TS, 0x09, 0x50, 0x50, 0xD0, 0xD0, "_MAX")
        M331 (TS, 0x0A, 0x60, 0x60, 0xE0, 0xE0, "_TRA")
        M331 (TS, 0x0B, 0x70, 0x70, 0xF0, 0xF0, "_LEN")
    }

