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
     * Bug 64:
     *
     * SUMMARY: Specific operations should initiate AE_BAD_HEX_CONSTANT exceptions
     */
    Method (MF61, 1, NotSerialized)
    {
        CH03 ("", 0x00, 0x00, 0x26, 0x00)
        Local0 = ("" + 0xABCD0000)
        If ((Local0 != 0xABCD0000))
        {
            ERR ("", ZFFF, 0x29, 0x00, 0x00, Local0, 0xABCD0000)
        }

        CH03 ("", 0x00, 0x02, 0x2B, 0x00)
        CH03 ("", 0x00, 0x03, 0x2D, 0x00)
        Local0 = ("                      " + 0xABCD0001)
        If ((Local0 != 0xABCD0001))
        {
            ERR ("", ZFFF, 0x30, 0x00, 0x00, Local0, 0xABCD0001)
        }

        CH03 ("", 0x00, 0x05, 0x32, 0x00)
        CH03 ("", 0x00, 0x06, 0x34, 0x00)
        Local1 = ""
        ToInteger (Local1, Local0)
        CH04 ("", 0x00, 0x24, 0x00, 0x37, 0x00, 0x00) /* AE_BAD_DECIMAL_CONSTANT */
        CH03 ("", 0x00, 0x08, 0x39, 0x00)
        Local1 = "                 "
        ToInteger (Local1, Local0)
        CH04 ("", 0x00, 0x24, 0x00, 0x3C, 0x00, 0x00) /* AE_BAD_DECIMAL_CONSTANT */
        CH03 ("", 0x00, 0x0A, 0x3E, 0x00)
        Local0 = ("q" + 0xABCD0002)
        If ((Local0 != 0xABCD0002))
        {
            ERR ("", ZFFF, 0x41, 0x00, 0x00, Local0, 0xABCD0002)
        }

        CH03 ("", 0x00, 0x0C, 0x43, 0x00)
        CH03 ("", 0x00, 0x0D, 0x45, 0x00)
        Local0 = ("q                      " + 0xABCD0003)
        If ((Local0 != 0xABCD0003))
        {
            ERR ("", ZFFF, 0x48, 0x00, 0x00, Local0, 0xABCD0003)
        }

        CH03 ("", 0x00, 0x0F, 0x4A, 0x00)
        CH03 ("", 0x00, 0x10, 0x4C, 0x00)
        Local1 = "q"
        ToInteger (Local1, Local0)
        CH04 ("", 0x00, 0x24, 0x00, 0x4F, 0x00, 0x00) /* AE_BAD_DECIMAL_CONSTANT */
        CH03 ("", 0x00, 0x12, 0x51, 0x00)
        Local1 = "q                 "
        ToInteger (Local1, Local0)
        CH04 ("", 0x00, 0x24, 0x00, 0x54, 0x00, 0x00) /* AE_BAD_DECIMAL_CONSTANT */
    }

