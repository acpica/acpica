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
     * Bug 0050:
     *
     * SUMMARY: No exception on result of ToHexString longer than 210 bytes
     */
    Method (MDDA, 0, Serialized)
    {
        /* 68-byte long buffer */

        Name (B000, Buffer (0x44)
        {
            /* 0000 */  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,  // ........
            /* 0008 */  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,  // ........
            /* 0010 */  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,  // ........
            /* 0018 */  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,  // ........
            /* 0020 */  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,  // ........
            /* 0028 */  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,  // ........
            /* 0030 */  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,  // ........
            /* 0038 */  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,  // ........
            /* 0040 */  0x01, 0x01, 0x01, 0x01                           // ....
        })
        /* ToHexString for 68-byte long buffer attempt */
        /* to produce 203 byte long string and have to */
        /* result in AE_AML_STRING_LIMIT exception. */
        CH03 ("", 0x00, 0x00, 0x33, 0x00)
        ToHexString (B000, Local0)
        CH04 ("", 0x00, 0x3D, 0x00, 0x35, 0x00, 0x00) /* AE_AML_STRING_LIMIT */
    }

