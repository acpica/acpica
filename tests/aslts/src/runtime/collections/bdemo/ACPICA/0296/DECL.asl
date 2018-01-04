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
     * Bug 296:
     *
     * SUMMARY: AE_AML_INTERNAL unexpectedly occurs when the Loadtable ParameterData
     *          and its Target differ in the types
     */
    Device (D296)
    {
        Name (PLDT, 0x00)
        Method (TST0, 0, NotSerialized)
        {
            Local0 = LoadTable ("OEM1", "", "", "", "\\PLDT", "1")
            If (CH03 ("", 0x00, 0x01, 0x2C, 0x00))
            {
                Return (Zero)
            }

            Local1 = ObjectType (PLDT)
            If ((Local1 != 0x01))
            {
                ERR ("", ZFFF, 0x33, 0x00, 0x00, Local1, 0x01)
            }
            ElseIf ((0x01 != PLDT))
            {
                ERR ("", ZFFF, 0x35, 0x00, 0x00, 0x01, PLDT)
            }

            Unload (Local0)
            CH03 ("", 0x00, 0x04, 0x39, 0x00)
        }
    }

    Method (M296, 0, NotSerialized)
    {
        \D296.TST0 ()
    }

