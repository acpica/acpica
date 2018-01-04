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
     * Bug 126:
     *
     * SUMMARY: The Read access automatic dereference for RefOf reference doesn't work
     */
    Method (MF0F, 1, NotSerialized)
    {
        Debug = "m000 started, apply DerefOf()"
        Local0 = DerefOf (Arg0)
        Local7 = (Local0 + 0x01)
        If ((Local0 != 0x07))
        {
            ERR ("", ZFFF, 0x2C, 0x00, 0x00, Local0, 0x07)
        }

        If ((Local7 != 0x08))
        {
            ERR ("", ZFFF, 0x2F, 0x00, 0x00, Local7, 0x08)
        }

        Debug = "m000 finished"
    }

    Method (MF10, 1, Serialized)
    {
        Name (I001, 0x00)
        Debug = "m001 started, DONT apply DerefOf()"
        Local7 = (Arg0 + 0x01)
        If ((Arg0 != 0x07))
        {
            ERR ("", ZFFF, 0x3E, 0x00, 0x00, Arg0, 0x07)
        }

        If ((Local7 != 0x08))
        {
            ERR ("", ZFFF, 0x41, 0x00, 0x00, Arg0, 0x08)
        }

        Debug = "m001 finished"
    }

    Method (MF11, 0, Serialized)
    {
        Name (I000, 0x07)
        MF0F (RefOf (I000))
    }

    Method (MF12, 0, Serialized)
    {
        Name (I000, 0x07)
        MF10 (RefOf (I000))
    }

