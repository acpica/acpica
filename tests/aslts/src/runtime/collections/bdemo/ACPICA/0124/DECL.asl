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
     * Bug 124:
     *
     * SUMMARY: No exception when the Index argument on Index() operator is out of the Source
     */
    Method (MF06, 0, Serialized)
    {
        Name (P000, Package (0x02)
        {
            0x00, 
            0x01
        })
        Name (B000, Buffer (0x03)
        {
             0x02, 0x03, 0x04                                 // ...
        })
        Name (S000, "5678")
        /* a) Index > 0xffffffff */
        /* c) Modulo(Index, 0x100000000) < Size. */
        CH03 ("", 0x00, 0x00, 0x2C, 0x00)
        Store (P000 [0x0000000100000001], Local0)
        CH04 ("", 0x01, 0x37, 0x00, 0x2E, 0x00, 0x00) /* AE_AML_PACKAGE_LIMIT */
        CH03 ("", 0x00, 0x02, 0x30, 0x00)
        Store (B000 [0x0000000100000002], Local0)
        CH04 ("", 0x01, 0x36, 0x00, 0x32, 0x00, 0x00) /* AE_AML_BUFFER_LIMIT */
        CH03 ("", 0x00, 0x04, 0x34, 0x00)
        Store (S000 [0x0000000100000003], Local0)
        CH04 ("", 0x01, 0x3D, 0x00, 0x36, 0x00, 0x00) /* AE_AML_STRING_LIMIT */
    }

