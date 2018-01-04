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
     * Bug 144:
     *
     * SUMMARY: The ASL Compiler doesn't support multiple type list for particular ParameterType of Method
     */
    Method (MF34, 1, Serialized)
    {
        Return (Arg0)
    }

    Method (MF35, 1, Serialized)
    {
        Return (Arg0)
    }

    Method (MF36, 1, Serialized)
    {
        Return (Arg0)
    }

    Method (MF37, 1, Serialized)
    {
        Return (Arg0)
    }

    Method (MF38, 0, NotSerialized)
    {
        Local0 = MF34 (0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x3A, 0x00, 0x00, Local0, 0x00)
        }

        Local0 = MF35 (0x01)
        If ((Local0 != 0x01))
        {
            ERR ("", ZFFF, 0x3F, 0x00, 0x00, Local0, 0x01)
        }

        Local0 = MF36 (0x02)
        If ((Local0 != 0x02))
        {
            ERR ("", ZFFF, 0x44, 0x00, 0x00, Local0, 0x02)
        }

        Local0 = MF37 ("3")
        If ((Local0 != "3"))
        {
            ERR ("", ZFFF, 0x49, 0x00, 0x00, Local0, "3")
        }
    }

