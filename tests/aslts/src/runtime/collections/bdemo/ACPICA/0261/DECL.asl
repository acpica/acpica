    /*
     * Some or all of this work - Copyright (c) 2006 - 2018, Intel Corp.
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
     * Bug 261:
     *
     * SUMMARY: Crash when DDBHandle parameter of Load is an Indexed Reference
     */
    Method (M028, 0, Serialized)
    {
        Name (BUF0, Buffer (0x4D)
        {
            /* 0000 */  0x53, 0x53, 0x44, 0x54, 0x4D, 0x00, 0x00, 0x00,  // SSDTM...
            /* 0008 */  0x02, 0x95, 0x49, 0x6E, 0x74, 0x65, 0x6C, 0x00,  // ..Intel.
            /* 0010 */  0x4D, 0x61, 0x6E, 0x79, 0x00, 0x00, 0x00, 0x00,  // Many....
            /* 0018 */  0x01, 0x00, 0x00, 0x00, 0x49, 0x4E, 0x54, 0x4C,  // ....INTL
            /* 0020 */  0x02, 0x11, 0x06, 0x20, 0x5B, 0x82, 0x1C, 0x41,  // ... [..A
            /* 0028 */  0x55, 0x58, 0x44, 0x14, 0x16, 0x4D, 0x30, 0x30,  // UXD..M00
            /* 0030 */  0x30, 0x00, 0x70, 0x0D, 0x5C, 0x41, 0x55, 0x58,  // 0.p.\AUX
            /* 0038 */  0x44, 0x2E, 0x4D, 0x30, 0x30, 0x30, 0x3A, 0x00,  // D.M000:.
            /* 0040 */  0x5B, 0x31, 0x10, 0x0A, 0x5C, 0x00, 0x08, 0x45,  // [1..\..E
            /* 0048 */  0x58, 0x53, 0x54, 0x0A, 0x02                     // XST..
        })
        OperationRegion (IST0, SystemMemory, 0x00, 0x4D)
        Field (IST0, ByteAcc, NoLock, Preserve)
        {
            RFU0,   616
        }

        External (\AUXZ, UnknownObj)
        Method (M000, 0, Serialized)
        {
            Name (PAC0, Package (0x01){})
            CH03 ("", 0x00, 0x00, 0x3F, 0x00)
            RFU0 = BUF0 /* \M028.BUF0 */
            If (CondRefOf (\AUXZ, Local0))
            {
                ERR ("", ZFFF, 0x44, 0x00, 0x00, Local0, 0x01777777)
                Return (Zero)
            }

            Load (RFU0, PAC0 [0x00])
            Debug = "SSDT loaded"
            If (CondRefOf (\AUXZ, Local0)){}
            Else
            {
                ERR ("", ZFFF, 0x4E, 0x00, 0x00, Local0, 0x01777777)
                Return (Zero)
            }

            Local1 = ObjectType (PAC0 [0x00])
            If ((Local1 != 0x0F))
            {
                Debug = Local1
                ERR ("", ZFFF, 0x55, 0x00, 0x00, Local0, 0x01777777)
                Return (Zero)
            }

            Unload (DerefOf (PAC0 [0x00]))
            Debug = "SSDT unloaded"
            If (CondRefOf (\AUXZ, Local0))
            {
                ERR ("", ZFFF, 0x5E, 0x00, 0x00, Local0, 0x01777777)
            }

            CH03 ("", 0x00, 0x05, 0x61, 0x00)
            Return (Zero)
        }

        M000 ()
    }

