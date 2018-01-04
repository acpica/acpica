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
     * Bug 257:
     *
     * SUMMARY: Unexpected AE_AML_OPERAND_TYPE when the Object in Load is a Region Field
     */
    /*
     * Original source code:
     DefinitionBlock("ssdt.aml", "SSDT", 0x02, "Intel", "Many", 0x00000001)
     {
     Device(AUXD)
     {
     Method(M000)
     {
     Return ("\\AUXD.M000 ()")
     }
     }
     }
     */
    Name (B257, Buffer (0x42)
    {
        /* 0000 */  0x53, 0x53, 0x44, 0x54, 0x42, 0x00, 0x00, 0x00,  // SSDTB...
        /* 0008 */  0x02, 0x81, 0x49, 0x6E, 0x74, 0x65, 0x6C, 0x00,  // ..Intel.
        /* 0010 */  0x4D, 0x61, 0x6E, 0x79, 0x00, 0x00, 0x00, 0x00,  // Many....
        /* 0018 */  0x01, 0x00, 0x00, 0x00, 0x49, 0x4E, 0x54, 0x4C,  // ....INTL
        /* 0020 */  0x11, 0x10, 0x06, 0x20, 0x5B, 0x82, 0x1C, 0x41,  // ... [..A
        /* 0028 */  0x55, 0x58, 0x44, 0x14, 0x16, 0x4D, 0x30, 0x30,  // UXD..M00
        /* 0030 */  0x30, 0x00, 0xA4, 0x0D, 0x5C, 0x41, 0x55, 0x58,  // 0...\AUX
        /* 0038 */  0x44, 0x2E, 0x4D, 0x30, 0x30, 0x30, 0x20, 0x28,  // D.M000 (
        /* 0040 */  0x29, 0x00                                       // ).
    })
    Name (H257, 0x00)
    OperationRegion (R257, SystemMemory, 0x00, 0x42)
    Field (R257, ByteAcc, NoLock, Preserve)
    {
        F257,   528
    }

    Method (M17D, 0, NotSerialized)
    {
        External (\AUXD.M000, UnknownObj)
        F257 = B257 /* \B257 */
        If (CondRefOf (\AUXD, Local0))
        {
            ERR ("", ZFFF, 0x4F, 0x00, 0x00, "\\AUXD", 0x01)
            Return (Zero)
        }

        If (CH03 ("", 0x00, 0x01, 0x53, 0x00))
        {
            Return (Zero)
        }

        Load (F257, H257) /* \H257 */
        If (CH03 ("", 0x00, 0x02, 0x59, 0x00))
        {
            Return (Zero)
        }

        If (CondRefOf (\AUXD, Local0)){}
        Else
        {
            ERR ("", ZFFF, 0x5F, 0x00, 0x00, "\\AUXD", 0x00)
            Return (Zero)
        }

        Local1 = ObjectType (Local0)
        If ((Local1 != 0x06))
        {
            ERR ("", ZFFF, 0x66, 0x00, 0x00, Local1, 0x06)
            Return (Zero)
        }

        Local0 = ObjectType (\AUXD.M000)
        If ((Local0 != 0x08))
        {
            ERR ("", ZFFF, 0x6C, 0x00, 0x00, Local0, 0x08)
            Return (Zero)
        }

        Unload (H257)
        If (CondRefOf (\AUXD, Local0))
        {
            ERR ("", ZFFF, 0x73, 0x00, 0x00, "\\AUXD", 0x01)
        }
    }

