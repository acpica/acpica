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
     * Bug 242:
     *
     * SUMMARY: Releasing the mutex the first Acquired on the non-zero level makes Releasing the residuary mutexes of that level impossible
     */
    Method (M031, 0, Serialized)
    {
        Mutex (T000, 0x00)
        Mutex (T001, 0x00)
        Mutex (T002, 0x00)
        Mutex (T003, 0x00)
        Mutex (T100, 0x01)
        Mutex (T101, 0x01)
        Mutex (T102, 0x01)
        Mutex (T103, 0x01)
        /*
         * Direct order for mutexes of level 0
         *
         * STATUS: works correctly - no exceptions
         */
        Method (M000, 0, NotSerialized)
        {
            Debug = "******** Test 0, for mutexes of level 0"
            Debug = "Acquiring mutexes of level 0:"
            Local0 = Acquire (T000, 0xFFFF)
            If (Local0)
            {
                Debug = "ERROR: Acquire T000 (Level 0, index 0)"
                ERR ("", ZFFF, 0x3E, 0x00, 0x00, 0x00, 0x00)
            }
            Else
            {
                Debug = "Ok: Acquire T000 (Level 0, index 0)"
            }

            Local0 = Acquire (T001, 0xFFFF)
            If (Local0)
            {
                Debug = "ERROR: Acquire T001 (Level 0, index 1)"
                ERR ("", ZFFF, 0x46, 0x00, 0x00, 0x00, 0x00)
            }
            Else
            {
                Debug = "Ok: Acquire T001 (Level 0, index 1)"
            }

            Local0 = Acquire (T002, 0xFFFF)
            If (Local0)
            {
                Debug = "ERROR: Acquire T002 (Level 0, index 2)"
                ERR ("", ZFFF, 0x4E, 0x00, 0x00, 0x00, 0x00)
            }
            Else
            {
                Debug = "Ok: Acquire T002 (Level 0, index 2)"
            }

            Local0 = Acquire (T003, 0xFFFF)
            If (Local0)
            {
                Debug = "ERROR: Acquire T003 (Level 0, index 3)"
                ERR ("", ZFFF, 0x56, 0x00, 0x00, 0x00, 0x00)
            }
            Else
            {
                Debug = "Ok: Acquire T003 (Level 0, index 3)"
            }

            Debug = "Releasing mutexes of level 0:"
            Debug = "Release T000 (Level 0, index 0)"
            CH03 ("", 0x00, 0x04, 0x5F, 0x00)
            Release (T000)
            CH03 ("", 0x00, 0x05, 0x61, 0x00)
            Debug = "Release T001 (Level 0, index 1)"
            CH03 ("", 0x00, 0x06, 0x64, 0x00)
            Release (T001)
            CH03 ("", 0x00, 0x07, 0x66, 0x00)
            Debug = "Release T002 (Level 0, index 2)"
            CH03 ("", 0x00, 0x08, 0x69, 0x00)
            Release (T002)
            CH03 ("", 0x00, 0x09, 0x6B, 0x00)
            Debug = "Release T003 (Level 0, index 3)"
            CH03 ("", 0x00, 0x0A, 0x6E, 0x00)
            Release (T003)
            CH03 ("", 0x00, 0x0B, 0x70, 0x00)
        }

        /*
         * Direct order for mutexes of level 1
         *
         * STATUS: works incorrectly - has exceptions
         */
        Method (M001, 0, NotSerialized)
        {
            Debug = "******** Test 1, for mutexes of level 1"
            Debug = "Acquiring mutexes of level 1:"
            Local0 = Acquire (T100, 0xFFFF)
            If (Local0)
            {
                Debug = "ERROR: Acquire T100 (Level 1, index 0)"
                ERR ("", ZFFF, 0x81, 0x00, 0x00, 0x00, 0x00)
            }
            Else
            {
                Debug = "Ok: Acquire T100 (Level 1, index 0)"
            }

            Local0 = Acquire (T101, 0xFFFF)
            If (Local0)
            {
                Debug = "ERROR: Acquire T101 (Level 1, index 1)"
                ERR ("", ZFFF, 0x89, 0x00, 0x00, 0x00, 0x00)
            }
            Else
            {
                Debug = "Ok: Acquire T101 (Level 1, index 1)"
            }

            Local0 = Acquire (T102, 0xFFFF)
            If (Local0)
            {
                Debug = "ERROR: Acquire T102 (Level 1, index 2)"
                ERR ("", ZFFF, 0x91, 0x00, 0x00, 0x00, 0x00)
            }
            Else
            {
                Debug = "Ok: Acquire T102 (Level 1, index 2)"
            }

            Local0 = Acquire (T103, 0xFFFF)
            If (Local0)
            {
                Debug = "ERROR: Acquire T103 (Level 1, index 3)"
                ERR ("", ZFFF, 0x99, 0x00, 0x00, 0x00, 0x00)
            }
            Else
            {
                Debug = "Ok: Acquire T103 (Level 1, index 3)"
            }

            Debug = "Releasing mutexes of Level 1:"
            Debug = "Release T100 (Level 1, index 0)"
            CH03 ("", 0x00, 0x10, 0xA2, 0x00)
            Release (T100)
            CH03 ("", 0x00, 0x11, 0xA4, 0x00)
            Debug = "Release T101 (Level 1, index 1)"
            CH03 ("", 0x00, 0x12, 0xA7, 0x00)
            Release (T101)
            CH03 ("", 0x00, 0x13, 0xA9, 0x00)
            Debug = "Release T102 (Level 1, index 2)"
            CH03 ("", 0x00, 0x14, 0xAC, 0x00)
            Release (T102)
            CH03 ("", 0x00, 0x15, 0xAE, 0x00)
            Debug = "Release T103 (Level 1, index 3)"
            CH03 ("", 0x00, 0x16, 0xB1, 0x00)
            Release (T103)
            CH03 ("", 0x00, 0x17, 0xB3, 0x00)
        }

        /*
         * The test shows that no exception when the first
         * Acquired mutex is Released in the last turn.
         *
         * STATUS: works correctly - no exception
         */
        Method (M002, 0, NotSerialized)
        {
            Debug = "******** Test 2, for mutexes of level 1"
            Debug = "Acquiring mutexes of level 1:"
            Local0 = Acquire (T100, 0xFFFF)
            If (Local0)
            {
                Debug = "ERROR: Acquire T100 (Level 1, index 0)"
                ERR ("", ZFFF, 0xC5, 0x00, 0x00, 0x00, 0x00)
            }
            Else
            {
                Debug = "Ok: Acquire T100 (Level 1, index 0)"
            }

            Local0 = Acquire (T101, 0xFFFF)
            If (Local0)
            {
                Debug = "ERROR: Acquire T101 (Level 1, index 1)"
                ERR ("", ZFFF, 0xCD, 0x00, 0x00, 0x00, 0x00)
            }
            Else
            {
                Debug = "Ok: Acquire T101 (Level 1, index 1)"
            }

            Local0 = Acquire (T102, 0xFFFF)
            If (Local0)
            {
                Debug = "ERROR: Acquire T102 (Level 1, index 2)"
                ERR ("", ZFFF, 0xD5, 0x00, 0x00, 0x00, 0x00)
            }
            Else
            {
                Debug = "Ok: Acquire T102 (Level 1, index 2)"
            }

            Local0 = Acquire (T103, 0xFFFF)
            If (Local0)
            {
                Debug = "ERROR: Acquire T103 (Level 1, index 3)"
                ERR ("", ZFFF, 0xDD, 0x00, 0x00, 0x00, 0x00)
            }
            Else
            {
                Debug = "Ok: Acquire T103 (Level 1, index 3)"
            }

            Debug = "Releasing mutexes of Level 1:"
            Debug = "Release T101 (Level 1, index 1)"
            CH03 ("", 0x00, 0x1C, 0xE6, 0x00)
            Release (T101)
            CH03 ("", 0x00, 0x1D, 0xE8, 0x00)
            Debug = "Release T102 (Level 1, index 2)"
            CH03 ("", 0x00, 0x1E, 0xEB, 0x00)
            Release (T102)
            CH03 ("", 0x00, 0x1F, 0xED, 0x00)
            Debug = "Release T103 (Level 1, index 3)"
            CH03 ("", 0x00, 0x20, 0xF0, 0x00)
            Release (T103)
            CH03 ("", 0x00, 0x21, 0xF2, 0x00)
            Debug = "Release T100 (Level 1, index 0)"
            CH03 ("", 0x00, 0x22, 0xF5, 0x00)
            Release (T100)
            CH03 ("", 0x00, 0x23, 0xF7, 0x00)
        }

        Method (MM00, 0, NotSerialized)
        {
            M000 ()
            M001 ()
            M002 ()
        }

        CH03 ("", 0x00, 0x24, 0x0101, 0x00)
        MM00 ()
        CH03 ("", 0x00, 0x25, 0x0103, 0x00)
    }

