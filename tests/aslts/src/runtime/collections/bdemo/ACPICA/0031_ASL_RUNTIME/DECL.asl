    /*
     * Some or all of this work - Copyright (c) 2006 - 2018, Intel Corp.
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
     * Bug 0031:
     *
     * SUMMARY: The ASL Compiler doesn't try to detect and reject attempts to use object before its declaration is evaluated
     *
     * ASL-compiler doesnt result in Error
     *
     * ATTENTION:
     *
     * Note 1: This test now is a run-time test because the ASL compiler doesn't
     *         actually detect and prohibit (my mistake) use of object before its
     *         declaration. After this bug of ASL compiler is fixed move this bdemo
     *         to non-run-time bug tests but dont forget to move all positive checkings
     *         of it in other run-time tests.
     *
     * Note 2: Since the ability itself to tun this test is error
     *         the test returns Error inconditionally (Method m1dc).
     *         But only one that error is expected. When the bug is
     *         fixed we will encounter that the test is no more
     *         compiled and fix it (see Note 1).
     */
    Name (ID28, 0x00)
    Method (MDC7, 0, Serialized)
    {
        CH03 ("", 0x00, 0x00, 0x37, 0x00)
        I000 = 0x12345678
        Name (I000, 0x00)
        CH04 ("", 0x00, 0xFF, 0x00, 0x3A, 0x00, 0x00)
    }

    Method (M800, 0, Serialized)
    {
        Name (I000, 0x00)
        Method (M000, 0, Serialized)
        {
            Debug = I000 /* \M800.M000.I000 */
            Name (I000, 0xFFFFFFFF)
        }
    }

    Method (M801, 0, NotSerialized)
    {
        Method (M000, 0, Serialized)
        {
            Debug = ID28 /* \M801.M000.ID28 */
            Name (ID28, 0xFFFFFFFF)
        }
    }

    Method (M802, 0, Serialized)
    {
        Name (I000, 0x00)
        I000 = 0xABCD0000
        CH03 ("", 0x00, 0x02, 0x55, 0x00)
        Name (I001, 0x00)
        I001 = 0xABCD0001
        CH03 ("", 0x00, 0x03, 0x5A, 0x00)
        Name (I002, 0xABCD0002)
        CH03 ("", 0x00, 0x03, 0x5E, 0x00)
        If (Y084)
        {
            CH03 ("", 0x00, 0x04, 0x62, 0x00)
            Method (M000, 0, Serialized)
            {
                Name (I000, 0xABCD0003)
                If ((I000 != 0xABCD0003))
                {
                    ERR ("", ZFFF, 0x68, 0x00, 0x00, I000, 0xABCD0003)
                }
            }

            CH03 ("", 0x00, 0x05, 0x6C, 0x00)
            Method (M001, 0, Serialized)
            {
                Name (I000, 0xABCD0004)
                I000 = 0xABCD0005
                If ((I000 != 0xABCD0005))
                {
                    ERR ("", ZFFF, 0x73, 0x00, 0x00, I000, 0xABCD0005)
                }
            }

            CH03 ("", 0x00, 0x06, 0x77, 0x00)
            Method (M002, 0, Serialized)
            {
                Debug = I000 /* \M802.M002.I000 */
                Name (I000, 0xABCD0006)
                I000 = 0xABCD0007
                If ((I000 != 0xABCD0007))
                {
                    ERR ("", ZFFF, 0x7F, 0x00, 0x00, I000, 0xABCD0007)
                }
            }

            CH03 ("", 0x00, 0x07, 0x83, 0x00)
            Method (M003, 0, Serialized)
            {
                Debug = "------------------------------ 000000000"
                Debug = ID28 /* \M802.M003.ID28 */
                Name (ID28, 0xABCD0008)
                If ((ID28 != 0xABCD0008))
                {
                    ERR ("", ZFFF, 0x8B, 0x00, 0x00, ID28, 0xABCD0008)
                }
            }

            CH03 ("", 0x00, 0x08, 0x8F, 0x00)
        }

        CH03 ("", 0x00, 0x09, 0x92, 0x00)
        If ((I000 != 0xABCD0000))
        {
            ERR ("", ZFFF, 0x95, 0x00, 0x00, I000, 0xABCD0000)
        }

        If ((I001 != 0xABCD0001))
        {
            ERR ("", ZFFF, 0x98, 0x00, 0x00, I001, 0xABCD0001)
        }

        If ((I002 != 0xABCD0002))
        {
            ERR ("", ZFFF, 0x9B, 0x00, 0x00, I002, 0xABCD0002)
        }

        If (Y084)
        {
            CH03 ("", 0x00, 0x0D, 0x9F, 0x00)
            M000 ()
            CH03 ("", 0x00, 0x0E, 0xA1, 0x00)
            M001 ()
            CH03 ("", 0x00, 0x0F, 0xA3, 0x00)
            M002 ()
            CH03 ("", 0x00, 0x10, 0xA5, 0x00)
            M003 ()
            CH03 ("", 0x00, 0x11, 0xA7, 0x00)
        }
        Else
        {
            SRMT ("sub-tests-of-m802")
            BLCK ()
        }

        CH03 ("", 0x00, 0x12, 0xAD, 0x00)
        II99 = 0xABCD0009
        Name (II99, 0x00)
        CH04 ("", 0x00, 0xFF, 0x00, 0xB2, 0x00, 0x00)
    }

    Method (M1DC, 0, NotSerialized)
    {
        /* Successful compilation itself of this test is error */

        ERR ("", ZFFF, 0xB8, 0x00, 0x00, 0x00, 0x00)
    }

    Method (MDC6, 0, NotSerialized)
    {
        SRMT ("mdc7")
        MDC7 ()
        SRMT ("m800")
        M800 ()
        SRMT ("m801")
        M801 ()
        SRMT ("m802")
        M802 ()
        SRMT ("m1dc")
        M1DC ()
    }

