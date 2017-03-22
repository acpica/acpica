/*
 * Some or all of this work - Copyright (c) 2006 - 2017, Intel Corp.
 * All rights reserved.
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
 * PinGroupFunction Resource Descriptor Macro
 */

Name (P462, Package() {
    ResourceTemplate () {
        PinGroupFunction(Exclusive, 0x1000, "\\_SB.GPO1", 0x0,
                         "group0", ResourceConsumer,,
                         RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupFunction(Exclusive, 0x1234, "\\_SB.GPO1", 0x0,
                         "group1", ResourceConsumer,,
                         RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupFunction(Shared, 0x1000, "\\_SB.GPO1", 0x0,
                         "group0", ResourceConsumer,,
                         RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupFunction(Shared, 0x1234, "\\_SB.GPO1", 0x0,
                         "group1", ResourceConsumer,,
                         RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupFunction(Shared, 0x1000, "\\_SB.GPO1", 0x0, "group0")
    },
    ResourceTemplate () {
        PinGroupFunction(Shared, 0x1234, "\\_SB.GPO1", 0x0, "group1")
    },
    ResourceTemplate () {
        PinGroupFunction(, 0x1234, "\\_SB.GPO1", 0x0, "group0")
    },
})

Name (P463, Package () {
    Buffer (0x28)
    {
        /* 0000 */  0x91, 0x23, 0x00, 0x01, 0x02, 0x00, 0x00, 0x10,  /* .#...... */
        /* 0008 */  0x00, 0x11, 0x00, 0x1B, 0x00, 0x22, 0x00, 0x04,  /* .....".. */
        /* 0010 */  0x00, 0x5C, 0x5F, 0x53, 0x42, 0x2E, 0x47, 0x50,  /* .\_SB.GP */
        /* 0018 */  0x4F, 0x31, 0x00, 0x67, 0x72, 0x6F, 0x75, 0x70,  /* O1.group */
        /* 0020 */  0x30, 0x00, 0x0A, 0x0B, 0x0C, 0x0D, 0x79, 0x00   /* 0.....y. */
    },
    Buffer (0x28)
    {
        /* 0000 */  0x91, 0x23, 0x00, 0x01, 0x02, 0x00, 0x34, 0x12,  /* .#....4. */
        /* 0008 */  0x00, 0x11, 0x00, 0x1B, 0x00, 0x22, 0x00, 0x04,  /* .....".. */
        /* 0010 */  0x00, 0x5C, 0x5F, 0x53, 0x42, 0x2E, 0x47, 0x50,  /* .\_SB.GP */
        /* 0018 */  0x4F, 0x31, 0x00, 0x67, 0x72, 0x6F, 0x75, 0x70,  /* O1.group */
        /* 0020 */  0x31, 0x00, 0x0A, 0x0B, 0x0C, 0x0D, 0x79, 0x00   /* 1.....y. */
    },
    Buffer (0x28)
    {
        /* 0000 */  0x91, 0x23, 0x00, 0x01, 0x03, 0x00, 0x00, 0x10,  /* .#...... */
        /* 0008 */  0x00, 0x11, 0x00, 0x1B, 0x00, 0x22, 0x00, 0x04,  /* .....".. */
        /* 0010 */  0x00, 0x5C, 0x5F, 0x53, 0x42, 0x2E, 0x47, 0x50,  /* .\_SB.GP */
        /* 0018 */  0x4F, 0x31, 0x00, 0x67, 0x72, 0x6F, 0x75, 0x70,  /* O1.group */
        /* 0020 */  0x30, 0x00, 0x0A, 0x0B, 0x0C, 0x0D, 0x79, 0x00   /* 0.....y. */
    },
    Buffer (0x28)
    {
        /* 0000 */  0x91, 0x23, 0x00, 0x01, 0x03, 0x00, 0x34, 0x12,  /* .#....4. */
        /* 0008 */  0x00, 0x11, 0x00, 0x1B, 0x00, 0x22, 0x00, 0x04,  /* .....".. */
        /* 0010 */  0x00, 0x5C, 0x5F, 0x53, 0x42, 0x2E, 0x47, 0x50,  /* .\_SB.GP */
        /* 0018 */  0x4F, 0x31, 0x00, 0x67, 0x72, 0x6F, 0x75, 0x70,  /* O1.group */
        /* 0020 */  0x31, 0x00, 0x0A, 0x0B, 0x0C, 0x0D, 0x79, 0x00   /* 1.....y. */
    },
    Buffer (0x24)
    {
        /* 0000 */  0x91, 0x1F, 0x00, 0x01, 0x03, 0x00, 0x00, 0x10,  /* ........ */
        /* 0008 */  0x00, 0x11, 0x00, 0x1B, 0x00, 0x22, 0x00, 0x00,  /* .....".. */
        /* 0010 */  0x00, 0x5C, 0x5F, 0x53, 0x42, 0x2E, 0x47, 0x50,  /* .\_SB.GP */
        /* 0018 */  0x4F, 0x31, 0x00, 0x67, 0x72, 0x6F, 0x75, 0x70,  /* O1.group */
        /* 0020 */  0x30, 0x00, 0x79, 0x00                           /* 0.y. */
    },
    Buffer (0x24)
    {
        /* 0000 */  0x91, 0x1F, 0x00, 0x01, 0x03, 0x00, 0x34, 0x12,  /* ......4. */
        /* 0008 */  0x00, 0x11, 0x00, 0x1B, 0x00, 0x22, 0x00, 0x00,  /* .....".. */
        /* 0010 */  0x00, 0x5C, 0x5F, 0x53, 0x42, 0x2E, 0x47, 0x50,  /* .\_SB.GP */
        /* 0018 */  0x4F, 0x31, 0x00, 0x67, 0x72, 0x6F, 0x75, 0x70,  /* O1.group */
        /* 0020 */  0x31, 0x00, 0x79, 0x00                           /* 1.y. */
    },
    Buffer (0x24)
    {
        /* 0000 */  0x91, 0x1F, 0x00, 0x01, 0x02, 0x00, 0x34, 0x12,  /* ......4. */
        /* 0008 */  0x00, 0x11, 0x00, 0x1B, 0x00, 0x22, 0x00, 0x00,  /* .....".. */
        /* 0010 */  0x00, 0x5C, 0x5F, 0x53, 0x42, 0x2E, 0x47, 0x50,  /* .\_SB.GP */
        /* 0018 */  0x4F, 0x31, 0x00, 0x67, 0x72, 0x6F, 0x75, 0x70,  /* O1.group */
        /* 0020 */  0x30, 0x00, 0x79, 0x00                           /* 0.y. */
    }
})

Method(RT29,, Serialized)
{
    Name(TS, "RT29")

    // Emit test header, set the filename

    THDR (TS, "PinGroupFunction Resource Descriptor Macro", __FILE__)

    // The main test packages must have the same number of entries

    If (LNotEqual (SizeOf (P462), SizeOf (P463)))
    {
        Err (TS, 179, 0, 0, 0, 0, "Incorrect package length")
        Return ()
    }

    // Main test case for packages above

    m330(TS, SizeOf (P462), "P462", P462, P463)

    // Check resource descriptor tag offsets
    Local0 = ResourceTemplate () {
        PinGroupFunction(Shared, 0x1234, "\\_SB.GPO1", 0x0, "group0",
            ResourceConsumer, FUN0, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
        PinGroupFunction(Shared, 0x1234, "\\_SB.GPO1", 0x0, "group0",
            ResourceConsumer, FUN1, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    }
    m331(TS, 1, FUN0._SHR, 0x20, FUN1._SHR, 0x150, "_SHR")
    m331(TS, 1, FUN0._FUN, 0x30, FUN1._FUN, 0x160, "_FUN")
    m331(TS, 1, FUN0._VEN, 0x110, FUN1._VEN, 0x240, "_VEN")
}
