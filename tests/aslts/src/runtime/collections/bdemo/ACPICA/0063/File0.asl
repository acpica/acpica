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
     * ToInteger(<0x-hex-dec>)
     */
    Method (MF92, 0, NotSerialized)
    {
        /* Hex: 0x - dec */

        CH03 ("", 0x00, 0x0100, 0x25, 0x00)
        ToInteger ("0x0", Local0)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x29, 0x00, 0x00, Local0, 0x00)
        }

        ToInteger ("0x0000000", Local0)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x2E, 0x00, 0x00, Local0, 0x00)
        }

        ToInteger ("0x1", Local0)
        If ((Local0 != 0x01))
        {
            ERR ("", ZFFF, 0x33, 0x00, 0x00, Local0, 0x01)
        }

        ToInteger ("0x12345678", Local0)
        If ((Local0 != 0x12345678))
        {
            ERR ("", ZFFF, 0x38, 0x00, 0x00, Local0, 0x12345678)
        }

        ToInteger ("0x12345", Local0)
        If ((Local0 != 0x00012345))
        {
            ERR ("", ZFFF, 0x3D, 0x00, 0x00, Local0, 0x00012345)
        }

        If (F64)
        {
            Local1 = "0x1234567890123456"
            ToInteger (Local1, Local0)
            If ((Local0 != 0x1234567890123456))
            {
                ERR ("", ZFFF, 0x44, 0x00, 0x00, Local0, 0x1234567890123456)
            }

            Local1 = "0x123456789012345"
            ToInteger (Local1, Local0)
            If ((Local0 != 0x0123456789012345))
            {
                ERR ("", ZFFF, 0x4A, 0x00, 0x00, Local0, 0x0123456789012345)
            }
        }

        /* Hex: 0x - hex */

        ToInteger ("0xabcdefef", Local0)
        If ((Local0 != 0xABCDEFEF))
        {
            ERR ("", ZFFF, 0x52, 0x00, 0x00, Local0, 0xABCDEFEF)
        }

        ToInteger ("0xabcdef", Local0)
        If ((Local0 != 0x00ABCDEF))
        {
            ERR ("", ZFFF, 0x57, 0x00, 0x00, Local0, 0x00ABCDEF)
        }

        If (F64)
        {
            Local1 = "0xabcdefefadefbcdf"
            ToInteger (Local1, Local0)
            If ((Local0 != 0xABCDEFEFADEFBCDF))
            {
                ERR ("", ZFFF, 0x5E, 0x00, 0x00, Local0, 0xABCDEFEFADEFBCDF)
            }

            Local1 = "0xabcdefefadefbcd"
            ToInteger (Local1, Local0)
            If ((Local0 != 0x0ABCDEFEFADEFBCD))
            {
                ERR ("", ZFFF, 0x64, 0x00, 0x00, Local0, 0x0ABCDEFEFADEFBCD)
            }
        }

        /* Hex: 0x - dec/hex */

        ToInteger ("0x1ab2cd34", Local0)
        If ((Local0 != 0x1AB2CD34))
        {
            ERR ("", ZFFF, 0x6C, 0x00, 0x00, Local0, 0x1AB2CD34)
        }

        If (F64)
        {
            Local1 = "0x1ab2cd340fe05678"
            ToInteger (Local1, Local0)
            If ((Local0 != 0x1AB2CD340FE05678))
            {
                ERR ("", ZFFF, 0x73, 0x00, 0x00, Local0, 0x1AB2CD340FE05678)
            }

            Local1 = "0x1ab2cd340fe0"
            ToInteger (Local1, Local0)
            If ((Local0 != 0x00001AB2CD340FE0))
            {
                ERR ("", ZFFF, 0x79, 0x00, 0x00, Local0, 0x00001AB2CD340FE0)
            }
        }

        CH03 ("", 0x00, 0x0219, 0x7D, 0x00)
    }

    /*
     * ToInteger(<dec>)
     */
    Method (MF93, 0, NotSerialized)
    {
        CH03 ("", 0x00, 0x010F, 0x85, 0x00)
        ToInteger ("0", Local0)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x89, 0x00, 0x00, Local0, 0x00)
        }

        ToInteger ("0000000", Local0)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x8E, 0x00, 0x00, Local0, 0x00)
        }

        ToInteger ("000000000000000", Local0)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x93, 0x00, 0x00, Local0, 0x00)
        }

        ToInteger ("000000000000000000000000000000000000000000", Local0)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x98, 0x00, 0x00, Local0, 0x00)
        }

        ToInteger ("1", Local0)
        If ((Local0 != 0x01))
        {
            ERR ("", ZFFF, 0x9D, 0x00, 0x00, Local0, 0x01)
        }

        ToInteger ("1234567890", Local0)
        If ((Local0 != 0x499602D2))
        {
            ERR ("", ZFFF, 0xA2, 0x00, 0x00, Local0, 0x499602D2)
        }

        ToInteger ("1234567", Local0)
        If ((Local0 != 0x0012D687))
        {
            ERR ("", ZFFF, 0xA7, 0x00, 0x00, Local0, 0x0012D687)
        }

        ToInteger ("4294967295", Local0)
        If ((Local0 != 0xFFFFFFFF))
        {
            ERR ("", ZFFF, 0xAC, 0x00, 0x00, Local0, 0xFFFFFFFF)
        }

        If (F64)
        {
            Local1 = "18446744073709551615"
            ToInteger (Local1, Local0)
            If ((Local0 != 0xFFFFFFFFFFFFFFFF))
            {
                ERR ("", ZFFF, 0xB3, 0x00, 0x00, Local0, 0xFFFFFFFFFFFFFFFF)
            }
        }

        CH03 ("", 0x00, 0x0119, 0xB7, 0x00)
    }

    /*
     * White space before image of Data is skipped
     * (all examples above).
     */
    Method (MF94, 0, NotSerialized)
    {
        CH03 ("", 0x00, 0x011A, 0xC0, 0x00)
        ToInteger ("                    0x0", Local0)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0xC4, 0x00, 0x00, Local0, 0x00)
        }

        ToInteger ("                    0x00000", Local0)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0xC9, 0x00, 0x00, Local0, 0x00)
        }

        ToInteger (" 0x1", Local0)
        If ((Local0 != 0x01))
        {
            ERR ("", ZFFF, 0xCE, 0x00, 0x00, Local0, 0x01)
        }

        ToInteger ("  0x12345678", Local0)
        If ((Local0 != 0x12345678))
        {
            ERR ("", ZFFF, 0xD3, 0x00, 0x00, Local0, 0x12345678)
        }

        ToInteger ("   0x12345", Local0)
        If ((Local0 != 0x00012345))
        {
            ERR ("", ZFFF, 0xD8, 0x00, 0x00, Local0, 0x00012345)
        }

        If (F64)
        {
            Local1 = "    0x1234567890123456"
            ToInteger (Local1, Local0)
            If ((Local0 != 0x1234567890123456))
            {
                ERR ("", ZFFF, 0xDF, 0x00, 0x00, Local0, 0x1234567890123456)
            }

            Local1 = "    0x123456789012345"
            ToInteger (Local1, Local0)
            If ((Local0 != 0x0123456789012345))
            {
                ERR ("", ZFFF, 0xE5, 0x00, 0x00, Local0, 0x0123456789012345)
            }
        }

        ToInteger ("     0xabcdefef", Local0)
        If ((Local0 != 0xABCDEFEF))
        {
            ERR ("", ZFFF, 0xEB, 0x00, 0x00, Local0, 0xABCDEFEF)
        }

        ToInteger ("      0xabcdef", Local0)
        If ((Local0 != 0x00ABCDEF))
        {
            ERR ("", ZFFF, 0xF0, 0x00, 0x00, Local0, 0x00ABCDEF)
        }

        ToInteger ("\t0xabcdef", Local0)
        If ((Local0 != 0x00ABCDEF))
        {
            ERR ("", ZFFF, 0xF5, 0x00, 0x00, Local0, 0x00ABCDEF)
        }

        If (F64)
        {
            Local1 = "       0xabcdefefadefbcdf"
            ToInteger (Local1, Local0)
            If ((Local0 != 0xABCDEFEFADEFBCDF))
            {
                ERR ("", ZFFF, 0xFC, 0x00, 0x00, Local0, 0xABCDEFEFADEFBCDF)
            }

            Local1 = "       0xabcdefefadefbcd"
            ToInteger (Local1, Local0)
            If ((Local0 != 0x0ABCDEFEFADEFBCD))
            {
                ERR ("", ZFFF, 0x0102, 0x00, 0x00, Local0, 0x0ABCDEFEFADEFBCD)
            }
        }

        ToInteger ("        0x1ab2cd34", Local0)
        If ((Local0 != 0x1AB2CD34))
        {
            ERR ("", ZFFF, 0x0108, 0x00, 0x00, Local0, 0x1AB2CD34)
        }

        If (F64)
        {
            Local1 = "         0x1ab2cd340fe05678"
            ToInteger (Local1, Local0)
            If ((Local0 != 0x1AB2CD340FE05678))
            {
                ERR ("", ZFFF, 0x010F, 0x00, 0x00, Local0, 0x1AB2CD340FE05678)
            }

            Local1 = "         0x1ab2cd340fe0"
            ToInteger (Local1, Local0)
            If ((Local0 != 0x00001AB2CD340FE0))
            {
                ERR ("", ZFFF, 0x0115, 0x00, 0x00, Local0, 0x00001AB2CD340FE0)
            }
        }

        ToInteger ("          0", Local0)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x011B, 0x00, 0x00, Local0, 0x00)
        }

        ToInteger (" \t0000000", Local0)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x0120, 0x00, 0x00, Local0, 0x00)
        }

        ToInteger ("\t000000000000000", Local0)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x0125, 0x00, 0x00, Local0, 0x00)
        }

        ToInteger (" 000000000000000000000000000000000000000000", Local0)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x012A, 0x00, 0x00, Local0, 0x00)
        }

        ToInteger ("           1", Local0)
        If ((Local0 != 0x01))
        {
            ERR ("", ZFFF, 0x012F, 0x00, 0x00, Local0, 0x01)
        }

        ToInteger ("            1234567890", Local0)
        If ((Local0 != 0x499602D2))
        {
            ERR ("", ZFFF, 0x0134, 0x00, 0x00, Local0, 0x499602D2)
        }

        ToInteger ("\t1234567890", Local0)
        If ((Local0 != 0x499602D2))
        {
            ERR ("", ZFFF, 0x0139, 0x00, 0x00, Local0, 0x499602D2)
        }

        ToInteger ("\t\t\t\t\t\t\t\t\t1234567890", Local0)
        If ((Local0 != 0x499602D2))
        {
            ERR ("", ZFFF, 0x013E, 0x00, 0x00, Local0, 0x499602D2)
        }

        ToInteger ("  \t           1234567", Local0)
        If ((Local0 != 0x0012D687))
        {
            ERR ("", ZFFF, 0x0143, 0x00, 0x00, Local0, 0x0012D687)
        }

        ToInteger ("     \t         4294967295", Local0)
        If ((Local0 != 0xFFFFFFFF))
        {
            ERR ("", ZFFF, 0x0148, 0x00, 0x00, Local0, 0xFFFFFFFF)
        }

        If (F64)
        {
            Local1 = "               \t18446744073709551615"
            ToInteger (Local1, Local0)
            If ((Local0 != 0xFFFFFFFFFFFFFFFF))
            {
                ERR ("", ZFFF, 0x014F, 0x00, 0x00, Local0, 0xFFFFFFFFFFFFFFFF)
            }
        }

        CH03 ("", 0x00, 0x0135, 0x0153, 0x00)
    }

    /*
     * Zeros before significant characters in image without '0x' are skipped).
     */
    Method (MF95, 0, NotSerialized)
    {
        CH03 ("", 0x00, 0x0136, 0x015B, 0x00)
        ToInteger ("          0", Local0)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x015F, 0x00, 0x00, Local0, 0x00)
        }

        ToInteger ("          2", Local0)
        If ((Local0 != 0x02))
        {
            ERR ("", ZFFF, 0x0164, 0x00, 0x00, Local0, 0x02)
        }

        ToInteger ("          0xa", Local0)
        If ((Local0 != 0x0A))
        {
            ERR ("", ZFFF, 0x0169, 0x00, 0x00, Local0, 0x0A)
        }

        ToInteger ("          04294967295", Local0)
        If ((Local0 != 0xFFFFFFFF))
        {
            ERR ("", ZFFF, 0x016E, 0x00, 0x00, Local0, 0xFFFFFFFF)
        }

        ToInteger ("04294967295", Local0)
        If ((Local0 != 0xFFFFFFFF))
        {
            ERR ("", ZFFF, 0x0173, 0x00, 0x00, Local0, 0xFFFFFFFF)
        }

        ToInteger ("000000000000000000004294967295", Local0)
        If ((Local0 != 0xFFFFFFFF))
        {
            ERR ("", ZFFF, 0x0178, 0x00, 0x00, Local0, 0xFFFFFFFF)
        }

        ToInteger (" 000000000000000000004294967295", Local0)
        If ((Local0 != 0xFFFFFFFF))
        {
            ERR ("", ZFFF, 0x017D, 0x00, 0x00, Local0, 0xFFFFFFFF)
        }

        ToInteger ("\t000000000000000000004294967295", Local0)
        If ((Local0 != 0xFFFFFFFF))
        {
            ERR ("", ZFFF, 0x0182, 0x00, 0x00, Local0, 0xFFFFFFFF)
        }

        ToInteger ("\t \t \t \t \t000000000000000000004294967295", Local0)
        If ((Local0 != 0xFFFFFFFF))
        {
            ERR ("", ZFFF, 0x0187, 0x00, 0x00, Local0, 0xFFFFFFFF)
        }

        ToInteger ("\t \t \t \t \t04294967295", Local0)
        If ((Local0 != 0xFFFFFFFF))
        {
            ERR ("", ZFFF, 0x018C, 0x00, 0x00, Local0, 0xFFFFFFFF)
        }

        ToInteger ("\t \t \t \t \t0123456789", Local0)
        If ((Local0 != 0x075BCD15))
        {
            ERR ("", ZFFF, 0x0191, 0x00, 0x00, Local0, 0x075BCD15)
        }

        ToInteger ("0123456789", Local0)
        If ((Local0 != 0x075BCD15))
        {
            ERR ("", ZFFF, 0x0196, 0x00, 0x00, Local0, 0x075BCD15)
        }

        ToInteger ("00123456789", Local0)
        If ((Local0 != 0x075BCD15))
        {
            ERR ("", ZFFF, 0x019B, 0x00, 0x00, Local0, 0x075BCD15)
        }

        If (F64)
        {
            Local1 = "               \t018446744073709551615"
            ToInteger (Local1, Local0)
            If ((Local0 != 0xFFFFFFFFFFFFFFFF))
            {
                ERR ("", ZFFF, 0x01A2, 0x00, 0x00, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            Local1 = "018446744073709551615"
            ToInteger (Local1, Local0)
            If ((Local0 != 0xFFFFFFFFFFFFFFFF))
            {
                ERR ("", ZFFF, 0x01A8, 0x00, 0x00, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            Local1 = "000000000000000000000000000000000000000018446744073709551615"
            ToInteger (Local1, Local0)
            If ((Local0 != 0xFFFFFFFFFFFFFFFF))
            {
                ERR ("", ZFFF, 0x01AE, 0x00, 0x00, Local0, 0xFFFFFFFFFFFFFFFF)
            }
        }

        CH03 ("", 0x00, 0x0219, 0x01B2, 0x00)
    }

    /*
     * ToInteger, exceptions
     */
    Method (MF96, 0, NotSerialized)
    {
        /* 5. "1234cd" (non-decimal character in dec-image) */

        CH03 ("", 0x00, 0x0147, 0x01BB, 0x00)
        Local1 = "1234cd"
        ToInteger (Local1, Local0)
        CH04 ("", 0x00, 0xFF, 0x00, 0x01BE, 0x00, 0x00)
        /* 6. "000x1234" (non-decimal character in dec-image) */

        CH03 ("", 0x00, 0x0149, 0x01C1, 0x00)
        Local1 = "000x1234"
        ToInteger (Local1, Local0)
        CH04 ("", 0x00, 0xFF, 0x00, 0x01C4, 0x00, 0x00)
        /* 7. "0x1234cdQ" (non-hex character in '0x'-image) */

        CH03 ("", 0x00, 0x014B, 0x01C7, 0x00)
        Local1 = "0x1234cdQ"
        ToInteger (Local1, Local0)
        CH04 ("", 0x00, 0xFF, 0x00, 0x01CA, 0x00, 0x00)
        CH03 ("", 0x00, 0x014D, 0x01CC, 0x00)
        Local1 = "0x0x12345"
        ToInteger (Local1, Local0)
        CH04 ("", 0x00, 0xFF, 0x00, 0x01CF, 0x00, 0x00)
        /* 8. "1234 " (white space in dec image) */

        CH03 ("", 0x00, 0x014F, 0x01D2, 0x00)
        Local1 = "1234 "
        ToInteger (Local1, Local0)
        CH04 ("", 0x00, 0xFF, 0x00, 0x01D5, 0x00, 0x00)
        /* 9. "0x1234cd " (white space in '0x'-image) */

        CH03 ("", 0x00, 0x0151, 0x01D8, 0x00)
        Local1 = "0x1234cd "
        ToInteger (Local1, Local0)
        CH04 ("", 0x00, 0xFF, 0x00, 0x01DB, 0x00, 0x00)
        /* 10. "0x 1234cdQ" (white space after '0x') */

        CH03 ("", 0x00, 0x0153, 0x01DE, 0x00)
        Local1 = "0x 1234"
        ToInteger (Local1, Local0)
        CH04 ("", 0x00, 0xFF, 0x00, 0x01E1, 0x00, 0x00)
        CH03 ("", 0x00, 0x0155, 0x01E3, 0x00)
        Local1 = "0x0x 1234"
        ToInteger (Local1, Local0)
        CH04 ("", 0x00, 0xFF, 0x00, 0x01E6, 0x00, 0x00)
        CH03 ("", 0x00, 0x0157, 0x01E8, 0x00)
        Local1 = "0x0x 0x 1234"
        ToInteger (Local1, Local0)
        CH04 ("", 0x00, 0xFF, 0x00, 0x01EB, 0x00, 0x00)
        CH03 ("", 0x00, 0x0159, 0x01ED, 0x00)
        Local1 = "0x 0x 1234"
        ToInteger (Local1, Local0)
        CH04 ("", 0x00, 0xFF, 0x00, 0x01F0, 0x00, 0x00)
        /* 11. (decimal image exceeding maximal) */
        /*     32-bit mode – the value exceeding "4294967295" */
        If (!F64)
        {
            CH03 ("", 0x00, 0x015B, 0x01F5, 0x00)
            Local1 = "4294967296"
            ToInteger (Local1, Local0)
            CH04 ("", 0x00, 0xFF, 0x00, 0x01F8, 0x00, 0x00)
            CH03 ("", 0x00, 0x015D, 0x01FA, 0x00)
            Local1 = "123456789012345678904294967296"
            ToInteger (Local1, Local0)
            CH04 ("", 0x00, 0xFF, 0x00, 0x01FD, 0x00, 0x00)
            CH03 ("", 0x00, 0x015F, 0x01FF, 0x00)
            Local1 = " \t \t\t00004294967296"
            ToInteger (Local1, Local0)
            CH04 ("", 0x00, 0xFF, 0x00, 0x0202, 0x00, 0x00)
            CH03 ("", 0x00, 0x0161, 0x0204, 0x00)
            Local1 = "\t0123456789012345678904294967296"
            ToInteger (Local1, Local0)
            CH04 ("", 0x00, 0xFF, 0x00, 0x0207, 0x00, 0x00)
            CH03 ("", 0x00, 0x0163, 0x0209, 0x00)
            Local1 = "0123456789012345678904294967296"
            ToInteger (Local1, Local0)
            CH04 ("", 0x00, 0xFF, 0x00, 0x020C, 0x00, 0x00)
            CH03 ("", 0x00, 0x0165, 0x020E, 0x00)
            Local1 = " 123456789012345678904294967296"
            ToInteger (Local1, Local0)
            CH04 ("", 0x00, 0xFF, 0x00, 0x0211, 0x00, 0x00)
            CH03 ("", 0x00, 0x0167, 0x0213, 0x00)
            Local1 = "\t123456789012345678904294967296"
            ToInteger (Local1, Local0)
            CH04 ("", 0x00, 0xFF, 0x00, 0x0216, 0x00, 0x00)
        }

        /*     64-bit mode – the value exceeding "18446744073709551615" */

        CH03 ("", 0x00, 0x0169, 0x021A, 0x00)
        Local1 = "18446744073709551616"
        ToInteger (Local1, Local0)
        CH04 ("", 0x00, 0xFF, 0x00, 0x021D, 0x00, 0x00)
        CH03 ("", 0x00, 0x016B, 0x021F, 0x00)
        Local1 = "\t18446744073709551616"
        ToInteger (Local1, Local0)
        CH04 ("", 0x00, 0xFF, 0x00, 0x0222, 0x00, 0x00)
        CH03 ("", 0x00, 0x016D, 0x0224, 0x00)
        Local1 = " 18446744073709551616"
        ToInteger (Local1, Local0)
        CH04 ("", 0x00, 0xFF, 0x00, 0x0227, 0x00, 0x00)
        CH03 ("", 0x00, 0x016F, 0x0229, 0x00)
        Local1 = "018446744073709551616"
        ToInteger (Local1, Local0)
        CH04 ("", 0x00, 0xFF, 0x00, 0x022C, 0x00, 0x00)
        CH03 ("", 0x00, 0x0171, 0x022E, 0x00)
        Local1 = " \t000000000018446744073709551616"
        ToInteger (Local1, Local0)
        CH04 ("", 0x00, 0xFF, 0x00, 0x0231, 0x00, 0x00)
        /* 12. "0x12345678901234567" (hex image exceeding maximal) */

        CH03 ("", 0x00, 0x0173, 0x0234, 0x00)
        Local1 = "0x12345678901234567"
        ToInteger (Local1, Local0)
        CH04 ("", 0x00, 0xFF, 0x00, 0x0237, 0x00, 0x00)
        /* 13. "0x00000000000001234" (hex image exceeding maximal; no matter that zeros) */

        CH03 ("", 0x00, 0x0175, 0x023A, 0x00)
        Local1 = "0x00000000000001234"
        ToInteger (Local1, Local0)
        CH04 ("", 0x00, 0xFF, 0x00, 0x023D, 0x00, 0x00)
        CH03 ("", 0x00, 0x0178, 0x023F, 0x00)
        Local1 = "0x0000000000000000000001234"
        ToInteger (Local1, Local0)
        CH04 ("", 0x00, 0xFF, 0x00, 0x0242, 0x00, 0x00)
        /* 14. "0x123456789" (hex image exceeding maximal; for 32-bit mode only) */

        If (!F64)
        {
            CH03 ("", 0x00, 0x017A, 0x0246, 0x00)
            Local1 = "0x123456789"
            ToInteger (Local1, Local0)
            CH04 ("", 0x00, 0xFF, 0x00, 0x0249, 0x00, 0x00)
        }

        /* 15. "0x" (incomplete '0x' image) */

        CH03 ("", 0x00, 0x017C, 0x024D, 0x00)
        Local1 = "0x"
        ToInteger (Local1, Local0)
        CH04 ("", 0x00, 0xFF, 0x00, 0x0250, 0x00, 0x00)
        CH03 ("", 0x00, 0x017E, 0x0252, 0x00)
        Local1 = "0x "
        ToInteger (Local1, Local0)
        CH04 ("", 0x00, 0xFF, 0x00, 0x0255, 0x00, 0x00)
        CH03 ("", 0x00, 0x0180, 0x0257, 0x00)
        Local1 = "0x\t"
        ToInteger (Local1, Local0)
        CH04 ("", 0x00, 0xFF, 0x00, 0x025A, 0x00, 0x00)
        CH03 ("", 0x00, 0x0182, 0x025C, 0x00)
        Local1 = "0x 1234"
        ToInteger (Local1, Local0)
        CH04 ("", 0x00, 0xFF, 0x00, 0x025F, 0x00, 0x00)
        CH03 ("", 0x00, 0x0184, 0x0261, 0x00)
        Local1 = "0x\t1234"
        ToInteger (Local1, Local0)
        CH04 ("", 0x00, 0xFF, 0x00, 0x0264, 0x00, 0x00)
        /* 16. Empty string */

        CH03 ("", 0x00, 0x0186, 0x0267, 0x00)
        Local1 = ""
        ToInteger (Local1, Local0)
        CH04 ("", 0x00, 0xFF, 0x00, 0x026A, 0x00, 0x00)
    }

