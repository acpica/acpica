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
     * Bug 0005:
     *
     * SUMMARY: Switch operator doesn't provide Default branch
     *
     * Default is not yet implemented at all.
     */
    Method (MDA1, 1, Serialized)
    {
        Local7 = 0x00
        Switch (ToInteger (Arg0))
        {
            Case (0x05)
            {
                Local7 = 0x1234
            }
            Default
            {
                Local7 = 0x5678
            }

        }

        If ((Arg0 == 0x05))
        {
            If ((Local7 != 0x1234))
            {
                ERR ("", ZFFF, 0x34, 0x00, 0x00, Local7, 0x1234)
            }
        }
        ElseIf ((Local7 != 0x5678))
        {
            ERR ("", ZFFF, 0x38, 0x00, 0x00, Local7, 0x5678)
        }
    }

    Method (MDA2, 0, NotSerialized)
    {
        MDA1 (0x05)
        MDA1 (0x00)
    }

