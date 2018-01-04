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
     * Bug 271:
     *
     * SUMMARY: CopyObject of Device works incorrectly
     */
    Method (M021, 0, Serialized)
    {
        Name (I000, 0xABCD0000)
        Name (I001, 0xABCD0001)
        Name (I002, 0xABCD0002)
        Device (D000)
        {
            Name (I002, 0xABCD0002)
        }

        Method (M123, 1, NotSerialized)
        {
            CopyObject (D000, Arg0)
            CopyObject (D000, Local0)
            CopyObject (D000, I001) /* \M021.I001 */
            Debug = "------------------------- Resulting devices:"
            Debug = Arg0
            Debug = Local0
            Debug = I001 /* \M021.I001 */
            Debug = "-------------------------."
        }

        CH03 ("", 0x00, 0x00, 0x36, 0x00)
        M123 (I000)
        Local0 = ObjectType (I001)
        If ((Local0 != C00E))
        {
            ERR ("", ZFFF, 0x3C, 0x00, 0x00, Local0, C00E)
        }

        CH03 ("", 0x00, 0x02, 0x3E, 0x00)
        CopyObject (I002, I001) /* \M021.I001 */
        Local0 = ObjectType (I001)
        If ((Local0 != C009))
        {
            ERR ("", ZFFF, 0x44, 0x00, 0x00, Local0, C009)
        }

        CH03 ("", 0x00, 0x04, 0x46, 0x00)
    }

