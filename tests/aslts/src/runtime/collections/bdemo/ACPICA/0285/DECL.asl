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
     * Bug 285:
     *
     * SUMMARY: AE_AML_OPERAND_TYPE unexpectedly occurs when the Handle parameter
     *          of Unload is a Method call
     */
    Device (D285)
    {
        Name (BUF0, Buffer (0x34)
        {
            /* 0000 */  0x53, 0x53, 0x44, 0x54, 0x34, 0x00, 0x00, 0x00,  // SSDT4...
            /* 0008 */  0x02, 0xEB, 0x49, 0x6E, 0x74, 0x65, 0x6C, 0x00,  // ..Intel.
            /* 0010 */  0x4D, 0x61, 0x6E, 0x79, 0x00, 0x00, 0x00, 0x00,  // Many....
            /* 0018 */  0x01, 0x00, 0x00, 0x00, 0x49, 0x4E, 0x54, 0x4C,  // ....INTL
            /* 0020 */  0x08, 0x12, 0x06, 0x20, 0x14, 0x0F, 0x5C, 0x53,  // ... ..\S
            /* 0028 */  0x53, 0x30, 0x30, 0x00, 0xA4, 0x0D, 0x5C, 0x53,  // S00...\S
            /* 0030 */  0x53, 0x30, 0x30, 0x00                           // S00.
        })
        OperationRegion (IST0, SystemMemory, 0x00, 0x34)
        Field (IST0, ByteAcc, NoLock, Preserve)
        {
            RFU0,   416
        }

        Method (TST0, 0, Serialized)
        {
            Name (HI0, 0x00)
            Method (M000, 0, NotSerialized)
            {
                Return (HI0) /* \D285.TST0.HI0_ */
            }

            RFU0 = BUF0 /* \D285.BUF0 */
            Load (RFU0, HI0) /* \D285.TST0.HI0_ */
            Unload (M000 ())
            If (CH03 ("", 0x00, 0x01, 0x42, 0x00))
            {
                Unload (HI0)
                CH03 ("", 0x00, 0x02, 0x44, 0x00)
            }
        }
    }

    Method (M285, 0, NotSerialized)
    {
        \D285.TST0 ()
    }

