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
     * Bug 281:
     *
     * SUMMARY: Normal strings as the LoadTable parameters can cause
     *          the matching table to be not found
     */
    Device (D281)
    {
        Name (SOID, "Intel ")
        Name (STID, "Many    ")
        Name (PLDT, 0x00)
        Method (TST0, 0, Serialized)
        {
            Name (DDB0, 0x00)
            Name (DDB1, 0x00)
            /* Unhappy case: space-ended strings */

            PLDT = 0x00
            DDB0 = LoadTable ("OEM1", SOID, STID, "\\", "\\D281.PLDT", 0x01)
            If ((PLDT != 0x00))
            {
                Debug = PLDT /* \D281.PLDT */
                ERR ("", ZFFF, 0x38, 0x00, 0x00, PLDT, 0x00)
                Return (0x01)
            }

            If (CondRefOf (\_XT2, Local0))
            {
                ERR ("", ZFFF, 0x3D, 0x00, 0x00, "\\_XT2", 0x01)
            }

            /* Successful case: spaces is replaced with zeroes */

            PLDT = 0x00
            SOID [0x05] = 0x00
            STID [0x04] = 0x00
            STID [0x05] = 0x00
            STID [0x06] = 0x00
            STID [0x07] = 0x00
            DDB0 = LoadTable ("OEM1", SOID, STID, "\\", "\\D281.PLDT", 0x01)
            If ((PLDT != 0x01))
            {
                Debug = PLDT /* \D281.PLDT */
                ERR ("", ZFFF, 0x4F, 0x00, 0x00, PLDT, 0x01)
                Return (0x01)
            }

            Debug = "OEM1 loaded"
            If (CondRefOf (\_XT2, Local0)){}
            Else
            {
                ERR ("", ZFFF, 0x56, 0x00, 0x00, "\\_XT2", 0x00)
            }

            Unload (DDB0)
            Debug = "OEM1 unloaded"
            If (CondRefOf (\_XT2, Local0))
            {
                ERR ("", ZFFF, 0x5D, 0x00, 0x00, "\\_XT2", 0x01)
            }

            /* Unhappy case: normal strings */

            PLDT = 0x00
            DDB1 = LoadTable ("OEM1", "Intel", "Many", "\\", "\\D281.PLDT", 0x01)
            If ((PLDT != 0x01))
            {
                Debug = PLDT /* \D281.PLDT */
                ERR ("", ZFFF, 0x68, 0x00, 0x00, PLDT, 0x01)
                Return (0x01)
            }

            Debug = "OEM1 loaded"
            If (CondRefOf (\_XT2, Local0)){}
            Else
            {
                ERR ("", ZFFF, 0x6F, 0x00, 0x00, "\\_XT2", 0x00)
            }

            Unload (DDB1)
            Debug = "OEM1 unloaded"
            If (CondRefOf (\_XT2, Local0))
            {
                ERR ("", ZFFF, 0x76, 0x00, 0x00, "\\_XT2", 0x01)
            }

            Return (0x00)
        }
    }

    Method (M281, 0, NotSerialized)
    {
        \D281.TST0 ()
    }

