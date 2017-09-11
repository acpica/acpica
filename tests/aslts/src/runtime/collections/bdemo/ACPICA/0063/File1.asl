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
     * Implicit String to Integer (<0x-hex-dec>)
     */
    Method (MF97, 0, NotSerialized)
    {
        /* Hex: 0x - dec */

        CH03 ("", 0x00, 0x0200, 0x25, 0x00)
        Local0 = ("" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x29, 0x00, 0x00, Local0, 0x00)
        }

        Local0 = ("0x0" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x2E, 0x00, 0x00, Local0, 0x00)
        }

        Local0 = ("0x1" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x33, 0x00, 0x00, Local0, 0x00)
        }

        Local0 = ("0x12345678" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x38, 0x00, 0x00, Local0, 0x00)
        }

        Local0 = ("0x1234567890123456" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x3D, 0x00, 0x00, Local0, 0x00)
        }

        /* Hex: 0x - hex */

        Local0 = ("0xabcdefef" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x44, 0x00, 0x00, Local0, 0x00)
        }

        Local0 = ("0xabcdefefadefbcdf" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x49, 0x00, 0x00, Local0, 0x00)
        }

        /* Hex: 0x - dec/hex */

        Local0 = ("0x1ab2cd340fe05678" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x50, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x0208, 0x53, 0x00)
        Local0 = ("0x1ab2cd340fe0567823456789123456789987" + 0x00)
        CH03 ("", 0x00, 0x0209, 0x55, 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x58, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x020B, 0x5B, 0x00)
    }

    /*
     * Implicit String to Integer (<dec>)
     */
    Method (MF98, 0, NotSerialized)
    {
        CH03 ("", 0x00, 0x0200, 0x63, 0x00)
        Local0 = ("0" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x67, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x0201, 0x6A, 0x00)
        Local0 = ("0000000" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x6E, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x0202, 0x71, 0x00)
        Local0 = ("000000000000000000000000000000" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x75, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x0203, 0x78, 0x00)
        Local0 = ("1" + 0x00)
        If ((Local0 != 0x01))
        {
            ERR ("", ZFFF, 0x7C, 0x00, 0x00, Local0, 0x01)
        }

        CH03 ("", 0x00, 0x0204, 0x7F, 0x00)
        Local0 = ("12345678" + 0x00)
        If ((Local0 != 0x12345678))
        {
            ERR ("", ZFFF, 0x83, 0x00, 0x00, Local0, 0x12345678)
        }

        CH03 ("", 0x00, 0x0205, 0x86, 0x00)
    }

    /*
     * Implicit String to Integer (<hex-dec>)
     */
    Method (MF99, 0, NotSerialized)
    {
        CH03 ("", 0x00, 0x0213, 0x8E, 0x00)
        /* Hex: 0x - dec */

        Local0 = ("1234567890123456" + 0x00)
        If (F64)
        {
            If ((Local0 != 0x1234567890123456))
            {
                ERR ("", ZFFF, 0x95, 0x00, 0x00, Local0, 0x1234567890123456)
            }
        }
        ElseIf ((Local0 != 0x12345678))
        {
            ERR ("", ZFFF, 0x99, 0x00, 0x00, Local0, 0x12345678)
        }

        /* Hex: 0x - hex */

        Local0 = ("abcdefef" + 0x00)
        If ((Local0 != 0xABCDEFEF))
        {
            ERR ("", ZFFF, 0xA1, 0x00, 0x00, Local0, 0xABCDEFEF)
        }

        Local0 = ("abcdefe" + 0x00)
        If ((Local0 != 0x0ABCDEFE))
        {
            ERR ("", ZFFF, 0xA6, 0x00, 0x00, Local0, 0x0ABCDEFE)
        }

        Local0 = ("abcdefefadefbcdf" + 0x00)
        If (F64)
        {
            If ((Local0 != 0xABCDEFEFADEFBCDF))
            {
                ERR ("", ZFFF, 0xAC, 0x00, 0x00, Local0, 0xABCDEFEFADEFBCDF)
            }
        }
        ElseIf ((Local0 != 0xABCDEFEF))
        {
            ERR ("", ZFFF, 0xB0, 0x00, 0x00, Local0, 0xABCDEFEF)
        }

        /* Hex: 0x - dec/hex */

        Local0 = ("1ab2cd340fe05678" + 0x00)
        If (F64)
        {
            If ((Local0 != 0x1AB2CD340FE05678))
            {
                ERR ("", ZFFF, 0xB9, 0x00, 0x00, Local0, 0x1AB2CD340FE05678)
            }
        }
        ElseIf ((Local0 != 0x1AB2CD34))
        {
            ERR ("", ZFFF, 0xBD, 0x00, 0x00, Local0, 0x1AB2CD34)
        }

        Local0 = ("1ab2cd340fe05" + 0x00)
        If (F64)
        {
            If ((Local0 != 0x0001AB2CD340FE05))
            {
                ERR ("", ZFFF, 0xC4, 0x00, 0x00, Local0, 0x0001AB2CD340FE05)
            }
        }
        ElseIf ((Local0 != 0x1AB2CD34))
        {
            ERR ("", ZFFF, 0xC8, 0x00, 0x00, Local0, 0x1AB2CD34)
        }

        Local0 = ("1a" + 0x00)
        If ((Local0 != 0x1A))
        {
            ERR ("", ZFFF, 0xCE, 0x00, 0x00, Local0, 0x1A)
        }

        CH03 ("", 0x00, 0x0219, 0xD1, 0x00)
    }

    /*
     * No exceptions in special cases which force exceptions on ToInteger
     */
    Method (MF9A, 0, NotSerialized)
    {
        /* 5. "1234cd" (non-decimal character in dec-image) */

        CH03 ("", 0x00, 0x0220, 0xDA, 0x00)
        Local0 = ("1234cd" + 0x00)
        If ((Local0 != 0x001234CD))
        {
            ERR ("", ZFFF, 0xDD, 0x00, 0x00, Local0, 0x001234CD)
        }

        /* 6. "000x1234" (non-decimal character in dec-image) */

        CH03 ("", 0x00, 0x0223, 0xE1, 0x00)
        Local0 = ("000x1234" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0xE4, 0x00, 0x00, Local0, 0x00)
        }

        /* 7. "0x1234cdQ" (non-hex character in '0x'-image) */

        CH03 ("", 0x00, 0x0225, 0xE8, 0x00)
        Local0 = ("0x1234cdQ" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0xEB, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x0227, 0xED, 0x00)
        Local0 = ("1234cdQ" + 0x00)
        If ((Local0 != 0x001234CD))
        {
            ERR ("", ZFFF, 0xF0, 0x00, 0x00, Local0, 0x001234CD)
        }

        CH03 ("", 0x00, 0x0229, 0xF3, 0x00)
        Local0 = ("0x0x12345" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0xF6, 0x00, 0x00, Local0, 0x00)
        }

        /* 8. "1234 " (white space in dec image) */

        CH03 ("", 0x00, 0x022B, 0xFA, 0x00)
        Local0 = ("1234 " + 0x00)
        If ((Local0 != 0x1234))
        {
            ERR ("", ZFFF, 0xFD, 0x00, 0x00, Local0, 0x1234)
        }

        /* 9. "0x1234cd " (white space in '0x'-image) */

        CH03 ("", 0x00, 0x022D, 0x0101, 0x00)
        Local0 = ("1234cd " + 0x00)
        If ((Local0 != 0x001234CD))
        {
            ERR ("", ZFFF, 0x0104, 0x00, 0x00, Local0, 0x001234CD)
        }

        /* 10. "0x 1234cdQ" (white space after '0x') */

        CH03 ("", 0x00, 0x022F, 0x0108, 0x00)
        Local0 = ("0x 1234" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x010B, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x0231, 0x010E, 0x00)
        Local0 = ("0x0x 1234" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x0111, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x0233, 0x0114, 0x00)
        Local0 = ("0x0x 0x 1234" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x0117, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x0235, 0x011A, 0x00)
        Local0 = ("0x 0x 1234" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x011D, 0x00, 0x00, Local0, 0x00)
        }

        /* 11. (decimal image exceeding maximal) */
        /*     32-bit mode – the value exceeding "4294967295" */
        If (0x01)
        {
            CH03 ("", 0x00, 0x0237, 0x0123, 0x00)
            Local0 = ("4294967296" + 0x00)
            If (F64)
            {
                If ((Local0 != 0x0000004294967296))
                {
                    ERR ("", ZFFF, 0x0127, 0x00, 0x00, Local0, 0x0000004294967296)
                }
            }
            ElseIf ((Local0 != 0x42949672))
            {
                ERR ("", ZFFF, 0x012B, 0x00, 0x00, Local0, 0x42949672)
            }

            CH03 ("", 0x00, 0x023A, 0x012F, 0x00)
            Local0 = ("123456789012345678904294967296" + 0x00)
            If (F64)
            {
                If ((Local0 != 0x1234567890123456))
                {
                    ERR ("", ZFFF, 0x0133, 0x00, 0x00, Local0, 0x1234567890123456)
                }
            }
            ElseIf ((Local0 != 0x12345678))
            {
                ERR ("", ZFFF, 0x0137, 0x00, 0x00, Local0, 0x12345678)
            }

            CH03 ("", 0x00, 0x023D, 0x013B, 0x00)
            Local0 = (" \t \t\t00004294967296" + 0x00)
            If (F64)
            {
                If ((Local0 != 0x0000004294967296))
                {
                    ERR ("", ZFFF, 0x013F, 0x00, 0x00, Local0, 0x0000004294967296)
                }
            }
            ElseIf ((Local0 != 0x42949672))
            {
                ERR ("", ZFFF, 0x0143, 0x00, 0x00, Local0, 0x42949672)
            }

            CH03 ("", 0x00, 0x0240, 0x0147, 0x00)
            Local0 = ("\t0123456789012345678904294967296" + 0x00)
            If (F64)
            {
                If ((Local0 != 0x1234567890123456))
                {
                    ERR ("", ZFFF, 0x014B, 0x00, 0x00, Local0, 0x1234567890123456)
                }
            }
            ElseIf ((Local0 != 0x12345678))
            {
                ERR ("", ZFFF, 0x014F, 0x00, 0x00, Local0, 0x12345678)
            }

            CH03 ("", 0x00, 0x0243, 0x0153, 0x00)
            Local0 = ("0123456789012345678904294967296" + 0x00)
            If (F64)
            {
                If ((Local0 != 0x1234567890123456))
                {
                    ERR ("", ZFFF, 0x0157, 0x00, 0x00, Local0, 0x1234567890123456)
                }
            }
            ElseIf ((Local0 != 0x12345678))
            {
                ERR ("", ZFFF, 0x015B, 0x00, 0x00, Local0, 0x12345678)
            }

            CH03 ("", 0x00, 0x0246, 0x015F, 0x00)
            Local0 = (" 123456789012345678904294967296" + 0x00)
            If (F64)
            {
                If ((Local0 != 0x1234567890123456))
                {
                    ERR ("", ZFFF, 0x0163, 0x00, 0x00, Local0, 0x1234567890123456)
                }
            }
            ElseIf ((Local0 != 0x12345678))
            {
                ERR ("", ZFFF, 0x0167, 0x00, 0x00, Local0, 0x12345678)
            }

            CH03 ("", 0x00, 0x0249, 0x016B, 0x00)
            Local0 = ("\t123456789012345678904294967296" + 0x00)
            If (F64)
            {
                If ((Local0 != 0x1234567890123456))
                {
                    ERR ("", ZFFF, 0x016F, 0x00, 0x00, Local0, 0x1234567890123456)
                }
            }
            ElseIf ((Local0 != 0x12345678))
            {
                ERR ("", ZFFF, 0x0173, 0x00, 0x00, Local0, 0x12345678)
            }
        }

        /*     64-bit mode – the value exceeding "18446744073709551615" */

        CH03 ("", 0x00, 0x024C, 0x0179, 0x00)
        Local0 = ("18446744073709551616" + 0x00)
        If (F64)
        {
            If ((Local0 != 0x1844674407370955))
            {
                ERR ("", ZFFF, 0x017D, 0x00, 0x00, Local0, 0x1844674407370955)
            }
        }
        ElseIf ((Local0 != 0x18446744))
        {
            ERR ("", ZFFF, 0x0181, 0x00, 0x00, Local0, 0x18446744)
        }

        CH03 ("", 0x00, 0x024F, 0x0185, 0x00)
        Local0 = ("\t18446744073709551616" + 0x00)
        If (F64)
        {
            If ((Local0 != 0x1844674407370955))
            {
                ERR ("", ZFFF, 0x0189, 0x00, 0x00, Local0, 0x1844674407370955)
            }
        }
        ElseIf ((Local0 != 0x18446744))
        {
            ERR ("", ZFFF, 0x018D, 0x00, 0x00, Local0, 0x18446744)
        }

        CH03 ("", 0x00, 0x0252, 0x0191, 0x00)
        Local0 = (" 18446744073709551616" + 0x00)
        If (F64)
        {
            If ((Local0 != 0x1844674407370955))
            {
                ERR ("", ZFFF, 0x0195, 0x00, 0x00, Local0, 0x1844674407370955)
            }
        }
        ElseIf ((Local0 != 0x18446744))
        {
            ERR ("", ZFFF, 0x0199, 0x00, 0x00, Local0, 0x18446744)
        }

        CH03 ("", 0x00, 0x0255, 0x019D, 0x00)
        Local0 = ("018446744073709551616" + 0x00)
        If (F64)
        {
            If ((Local0 != 0x1844674407370955))
            {
                ERR ("", ZFFF, 0x01A1, 0x00, 0x00, Local0, 0x1844674407370955)
            }
        }
        ElseIf ((Local0 != 0x18446744))
        {
            ERR ("", ZFFF, 0x01A5, 0x00, 0x00, Local0, 0x18446744)
        }

        CH03 ("", 0x00, 0x0258, 0x01A9, 0x00)
        Local0 = (" \t000000000018446744073709551616" + 0x00)
        If (F64)
        {
            If ((Local0 != 0x1844674407370955))
            {
                ERR ("", ZFFF, 0x01AD, 0x00, 0x00, Local0, 0x1844674407370955)
            }
        }
        ElseIf ((Local0 != 0x18446744))
        {
            ERR ("", ZFFF, 0x01B1, 0x00, 0x00, Local0, 0x18446744)
        }

        /* 12. "0x12345678901234567" (hex image exceeding maximal) */

        CH03 ("", 0x00, 0x025B, 0x01B6, 0x00)
        Local0 = ("0x12345678901234567" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x01B9, 0x00, 0x00, Local0, 0x00)
        }

        /* 13. "0x00000000000001234" (hex image exceeding maximal; no matter that zeros) */

        CH03 ("", 0x00, 0x025E, 0x01BD, 0x00)
        Local0 = ("0x00000000000001234" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x01C0, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x0260, 0x01C3, 0x00)
        Local0 = ("0x0000000000000000000001234" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x01C6, 0x00, 0x00, Local0, 0x00)
        }

        /* 14. "0x123456789" (hex image exceeding maximal; for 32-bit mode only) */

        If (0x01)
        {
            CH03 ("", 0x00, 0x0262, 0x01CB, 0x00)
            Local0 = ("0x123456789" + 0x00)
            If ((Local0 != 0x00))
            {
                ERR ("", ZFFF, 0x01CE, 0x00, 0x00, Local0, 0x00)
            }
        }

        /* 15. "0x" (incomplete '0x' image) */

        CH03 ("", 0x00, 0x0264, 0x01D3, 0x00)
        Local0 = ("0x" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x01D6, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x0266, 0x01D8, 0x00)
    }

    /*
     * 2. " 0x1234cd" (white space before image of Data is skipped)
     *
     * All the above examples but with the white space before image of Data.
     */
    Method (MF9B, 0, NotSerialized)
    {
        /* Hex: 0x - dec */

        CH03 ("", 0x00, 0x0267, 0x01E4, 0x00)
        Local0 = (" 0x0" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x01E8, 0x00, 0x00, Local0, 0x00)
        }

        Local0 = ("\t0x1" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x01ED, 0x00, 0x00, Local0, 0x00)
        }

        Local0 = ("\t 0x12345678" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x01F2, 0x00, 0x00, Local0, 0x00)
        }

        Local0 = (" \t0x1234567890123456" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x01F7, 0x00, 0x00, Local0, 0x00)
        }

        /* Hex: 0x - hex */

        Local0 = ("  0xabcdefef" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x01FE, 0x00, 0x00, Local0, 0x00)
        }

        Local0 = ("\t\t0xabcdefefadefbcdf" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x0203, 0x00, 0x00, Local0, 0x00)
        }

        /* Hex: 0x - dec/hex */

        Local0 = (" \t \t \t \t \t0x1ab2cd340fe05678" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x020A, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x026F, 0x020D, 0x00)
        Local0 = ("\t \t \t \t \t \t0x1ab2cd340fe0567823456789123456789987" + 0x00)
        CH03 ("", 0x00, 0x0270, 0x020F, 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x0212, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x0272, 0x0215, 0x00)
        /*
         * Implicit String to Integer (<dec>)
         *
         * Method(mf98)
         */
        CH03 ("", 0x00, 0x0273, 0x021D, 0x00)
        Local0 = ("                       0" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x0221, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x0275, 0x0224, 0x00)
        Local0 = ("\t\t\t\t\t\t0000000" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x0228, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x0277, 0x022B, 0x00)
        Local0 = ("                                 000000000000000000000000000000" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x022F, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x0279, 0x0232, 0x00)
        Local0 = ("\t\t\t\t\t\t\t000000000000000000000000000000" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x0236, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x027B, 0x0239, 0x00)
        Local0 = (" \t\t 1" + 0x00)
        If ((Local0 != 0x01))
        {
            ERR ("", ZFFF, 0x023D, 0x00, 0x00, Local0, 0x01)
        }

        CH03 ("", 0x00, 0x027D, 0x0240, 0x00)
        Local0 = (" \t \t \t12345678" + 0x00)
        If ((Local0 != 0x12345678))
        {
            ERR ("", ZFFF, 0x0244, 0x00, 0x00, Local0, 0x12345678)
        }

        CH03 ("", 0x00, 0x027F, 0x0247, 0x00)
        /*
         * Implicit String to Integer (<hex-dec>)
         *
         * Method(mf99)
         */
        CH03 ("", 0x00, 0x0280, 0x024F, 0x00)
        /* Hex: 0x - dec */

        Local0 = ("\t\t\t\t1234567890123456" + 0x00)
        If (F64)
        {
            If ((Local0 != 0x1234567890123456))
            {
                ERR ("", ZFFF, 0x0256, 0x00, 0x00, Local0, 0x1234567890123456)
            }
        }
        ElseIf ((Local0 != 0x12345678))
        {
            ERR ("", ZFFF, 0x025A, 0x00, 0x00, Local0, 0x12345678)
        }

        /* Hex: 0x - hex */

        Local0 = ("\t\t\t\tabcdefef" + 0x00)
        If ((Local0 != 0xABCDEFEF))
        {
            ERR ("", ZFFF, 0x0262, 0x00, 0x00, Local0, 0xABCDEFEF)
        }

        Local0 = ("     abcdefe" + 0x00)
        If ((Local0 != 0x0ABCDEFE))
        {
            ERR ("", ZFFF, 0x0267, 0x00, 0x00, Local0, 0x0ABCDEFE)
        }

        Local0 = ("             abcdefefadefbcdf" + 0x00)
        If (F64)
        {
            If ((Local0 != 0xABCDEFEFADEFBCDF))
            {
                ERR ("", ZFFF, 0x026D, 0x00, 0x00, Local0, 0xABCDEFEFADEFBCDF)
            }
        }
        ElseIf ((Local0 != 0xABCDEFEF))
        {
            ERR ("", ZFFF, 0x0271, 0x00, 0x00, Local0, 0xABCDEFEF)
        }

        /* Hex: 0x - dec/hex */

        Local0 = ("\t     \t\t\t \t   1ab2cd340fe05678" + 0x00)
        If (F64)
        {
            If ((Local0 != 0x1AB2CD340FE05678))
            {
                ERR ("", ZFFF, 0x027A, 0x00, 0x00, Local0, 0x1AB2CD340FE05678)
            }
        }
        ElseIf ((Local0 != 0x1AB2CD34))
        {
            ERR ("", ZFFF, 0x027E, 0x00, 0x00, Local0, 0x1AB2CD34)
        }

        Local0 = (" 1ab2cd340fe05" + 0x00)
        If (F64)
        {
            If ((Local0 != 0x0001AB2CD340FE05))
            {
                ERR ("", ZFFF, 0x0285, 0x00, 0x00, Local0, 0x0001AB2CD340FE05)
            }
        }
        ElseIf ((Local0 != 0x1AB2CD34))
        {
            ERR ("", ZFFF, 0x0289, 0x00, 0x00, Local0, 0x1AB2CD34)
        }

        Local0 = ("\t1a" + 0x00)
        If ((Local0 != 0x1A))
        {
            ERR ("", ZFFF, 0x028F, 0x00, 0x00, Local0, 0x1A)
        }

        CH03 ("", 0x00, 0x028D, 0x0292, 0x00)
        /*
         * No exceptions in special cases which force exceptions on ToInteger
         *
         * Method(mf9a)
         */
        /* 5. "1234cd" (non-decimal character in dec-image) */
        CH03 ("", 0x00, 0x028E, 0x029B, 0x00)
        Local0 = ("\t1234cd" + 0x00)
        If ((Local0 != 0x001234CD))
        {
            ERR ("", ZFFF, 0x029E, 0x00, 0x00, Local0, 0x001234CD)
        }

        /* 6. "000x1234" (non-decimal character in dec-image) */

        CH03 ("", 0x00, 0x0290, 0x02A2, 0x00)
        Local0 = (" \t \t\t\t 000x1234" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x02A5, 0x00, 0x00, Local0, 0x00)
        }

        /* 7. "0x1234cdQ" (non-hex character in '0x'-image) */

        CH03 ("", 0x00, 0x0292, 0x02A9, 0x00)
        Local0 = (" \t  \t\t\t\t 0x1234cdQ" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x02AC, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x0294, 0x02AE, 0x00)
        Local0 = (" 1234cdQ" + 0x00)
        If ((Local0 != 0x001234CD))
        {
            ERR ("", ZFFF, 0x02B1, 0x00, 0x00, Local0, 0x001234CD)
        }

        CH03 ("", 0x00, 0x0296, 0x02B4, 0x00)
        Local0 = ("   \t\t0x0x12345" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x02B7, 0x00, 0x00, Local0, 0x00)
        }

        /* 8. "1234 " (white space in dec image) */

        CH03 ("", 0x00, 0x0298, 0x02BB, 0x00)
        Local0 = ("   \t\t1234 " + 0x00)
        If ((Local0 != 0x1234))
        {
            ERR ("", ZFFF, 0x02BE, 0x00, 0x00, Local0, 0x1234)
        }

        /* 9. "0x1234cd " (white space in '0x'-image) */

        CH03 ("", 0x00, 0x029A, 0x02C2, 0x00)
        Local0 = ("\t\t\t  1234cd " + 0x00)
        If ((Local0 != 0x001234CD))
        {
            ERR ("", ZFFF, 0x02C5, 0x00, 0x00, Local0, 0x001234CD)
        }

        /* 10. "0x 1234cdQ" (white space after '0x') */

        CH03 ("", 0x00, 0x029C, 0x02C9, 0x00)
        Local0 = ("\t\t\t\t   \t \t \t\t0x 1234" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x02CC, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x029E, 0x02CF, 0x00)
        Local0 = (" \t   \t \t\t \t0x0x 1234" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x02D2, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x02A0, 0x02D5, 0x00)
        Local0 = (" \t \t \t    \t\t0x0x 0x 1234" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x02D8, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x02A2, 0x02DB, 0x00)
        Local0 = ("\t \t    \t      \t\t 0x 0x 1234" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x02DE, 0x00, 0x00, Local0, 0x00)
        }

        /* 11. (decimal image exceeding maximal) */
        /*     32-bit mode – the value exceeding "4294967295" */
        If (0x01)
        {
            CH03 ("", 0x00, 0x02A4, 0x02E4, 0x00)
            Local0 = ("\t\t4294967296" + 0x00)
            If (F64)
            {
                If ((Local0 != 0x0000004294967296))
                {
                    ERR ("", ZFFF, 0x02E8, 0x00, 0x00, Local0, 0x0000004294967296)
                }
            }
            ElseIf ((Local0 != 0x42949672))
            {
                ERR ("", ZFFF, 0x02EC, 0x00, 0x00, Local0, 0x42949672)
            }

            CH03 ("", 0x00, 0x02A7, 0x02F0, 0x00)
            Local0 = ("    \t\t    \t\t\t123456789012345678904294967296" + 0x00)
            If (F64)
            {
                If ((Local0 != 0x1234567890123456))
                {
                    ERR ("", ZFFF, 0x02F4, 0x00, 0x00, Local0, 0x1234567890123456)
                }
            }
            ElseIf ((Local0 != 0x12345678))
            {
                ERR ("", ZFFF, 0x02F8, 0x00, 0x00, Local0, 0x12345678)
            }

            CH03 ("", 0x00, 0x02AA, 0x02FC, 0x00)
            Local0 = (" \t \t\t00004294967296" + 0x00)
            If (F64)
            {
                If ((Local0 != 0x0000004294967296))
                {
                    ERR ("", ZFFF, 0x0300, 0x00, 0x00, Local0, 0x0000004294967296)
                }
            }
            ElseIf ((Local0 != 0x42949672))
            {
                ERR ("", ZFFF, 0x0304, 0x00, 0x00, Local0, 0x42949672)
            }

            CH03 ("", 0x00, 0x02AD, 0x0308, 0x00)
            Local0 = ("\t0123456789012345678904294967296" + 0x00)
            If (F64)
            {
                If ((Local0 != 0x1234567890123456))
                {
                    ERR ("", ZFFF, 0x030C, 0x00, 0x00, Local0, 0x1234567890123456)
                }
            }
            ElseIf ((Local0 != 0x12345678))
            {
                ERR ("", ZFFF, 0x0310, 0x00, 0x00, Local0, 0x12345678)
            }

            CH03 ("", 0x00, 0x02B0, 0x0314, 0x00)
            Local0 = ("\t0123456789012345678904294967296" + 0x00)
            If (F64)
            {
                If ((Local0 != 0x1234567890123456))
                {
                    ERR ("", ZFFF, 0x0318, 0x00, 0x00, Local0, 0x1234567890123456)
                }
            }
            ElseIf ((Local0 != 0x12345678))
            {
                ERR ("", ZFFF, 0x031C, 0x00, 0x00, Local0, 0x12345678)
            }

            CH03 ("", 0x00, 0x02B3, 0x0320, 0x00)
            Local0 = (" 123456789012345678904294967296" + 0x00)
            If (F64)
            {
                If ((Local0 != 0x1234567890123456))
                {
                    ERR ("", ZFFF, 0x0324, 0x00, 0x00, Local0, 0x1234567890123456)
                }
            }
            ElseIf ((Local0 != 0x12345678))
            {
                ERR ("", ZFFF, 0x0328, 0x00, 0x00, Local0, 0x12345678)
            }

            CH03 ("", 0x00, 0x02B6, 0x032C, 0x00)
            Local0 = ("\t123456789012345678904294967296" + 0x00)
            If (F64)
            {
                If ((Local0 != 0x1234567890123456))
                {
                    ERR ("", ZFFF, 0x0330, 0x00, 0x00, Local0, 0x1234567890123456)
                }
            }
            ElseIf ((Local0 != 0x12345678))
            {
                ERR ("", ZFFF, 0x0334, 0x00, 0x00, Local0, 0x12345678)
            }
        }

        /*     64-bit mode – the value exceeding "18446744073709551615" */

        CH03 ("", 0x00, 0x02B8, 0x033A, 0x00)
        Local0 = ("\t\t\t18446744073709551616" + 0x00)
        If (F64)
        {
            If ((Local0 != 0x1844674407370955))
            {
                ERR ("", ZFFF, 0x033E, 0x00, 0x00, Local0, 0x1844674407370955)
            }
        }
        ElseIf ((Local0 != 0x18446744))
        {
            ERR ("", ZFFF, 0x0342, 0x00, 0x00, Local0, 0x18446744)
        }

        CH03 ("", 0x00, 0x02BB, 0x0346, 0x00)
        Local0 = ("\t18446744073709551616" + 0x00)
        If (F64)
        {
            If ((Local0 != 0x1844674407370955))
            {
                ERR ("", ZFFF, 0x034A, 0x00, 0x00, Local0, 0x1844674407370955)
            }
        }
        ElseIf ((Local0 != 0x18446744))
        {
            ERR ("", ZFFF, 0x034E, 0x00, 0x00, Local0, 0x18446744)
        }

        CH03 ("", 0x00, 0x02BE, 0x0352, 0x00)
        Local0 = (" 18446744073709551616" + 0x00)
        If (F64)
        {
            If ((Local0 != 0x1844674407370955))
            {
                ERR ("", ZFFF, 0x0356, 0x00, 0x00, Local0, 0x1844674407370955)
            }
        }
        ElseIf ((Local0 != 0x18446744))
        {
            ERR ("", ZFFF, 0x035A, 0x00, 0x00, Local0, 0x18446744)
        }

        CH03 ("", 0x00, 0x02C1, 0x035E, 0x00)
        Local0 = ("   \t018446744073709551616" + 0x00)
        If (F64)
        {
            If ((Local0 != 0x1844674407370955))
            {
                ERR ("", ZFFF, 0x0362, 0x00, 0x00, Local0, 0x1844674407370955)
            }
        }
        ElseIf ((Local0 != 0x18446744))
        {
            ERR ("", ZFFF, 0x0366, 0x00, 0x00, Local0, 0x18446744)
        }

        CH03 ("", 0x00, 0x02C4, 0x036A, 0x00)
        Local0 = (" \t000000000018446744073709551616" + 0x00)
        If (F64)
        {
            If ((Local0 != 0x1844674407370955))
            {
                ERR ("", ZFFF, 0x036E, 0x00, 0x00, Local0, 0x1844674407370955)
            }
        }
        ElseIf ((Local0 != 0x18446744))
        {
            ERR ("", ZFFF, 0x0372, 0x00, 0x00, Local0, 0x18446744)
        }

        /* 12. "0x12345678901234567" (hex image exceeding maximal) */

        CH03 ("", 0x00, 0x02C7, 0x0377, 0x00)
        Local0 = ("\t\t0x12345678901234567" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x037A, 0x00, 0x00, Local0, 0x00)
        }

        /* 13. "0x00000000000001234" (hex image exceeding maximal; no matter that zeros) */

        CH03 ("", 0x00, 0x02CA, 0x037E, 0x00)
        Local0 = ("           0x00000000000001234" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x0381, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x02CC, 0x0384, 0x00)
        Local0 = ("          \t\t0x0000000000000000000001234" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x0387, 0x00, 0x00, Local0, 0x00)
        }

        /* 14. "0x123456789" (hex image exceeding maximal; for 32-bit mode only) */

        If (0x01)
        {
            CH03 ("", 0x00, 0x02CE, 0x038C, 0x00)
            Local0 = ("0x123456789" + 0x00)
            If ((Local0 != 0x00))
            {
                ERR ("", ZFFF, 0x038F, 0x00, 0x00, Local0, 0x00)
            }
        }

        /* 15. "0x" (incomplete '0x' image) */

        CH03 ("", 0x00, 0x02D0, 0x0394, 0x00)
        Local0 = ("\t0x" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x0397, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x02D2, 0x0399, 0x00)
        Local0 = (" 0x" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x039D, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x02D4, 0x039F, 0x00)
    }

    /*
     * 4. "0000000000000000000000001234"
     * (zeros before significant characters in image without '0x' are skipped).
     *
     * Exampples: mf9b + 000000000
     *
     * All the above examples but
     *
     *    with the white space before image of Data
     *  + 000000000 zeros before image
     */
    Method (MF9C, 0, NotSerialized)
    {
        /* Hex: 0x - dec */

        CH03 ("", 0x00, 0x0367, 0x03B1, 0x00)
        Local0 = (" 0000000000x0" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x03B5, 0x00, 0x00, Local0, 0x00)
        }

        Local0 = ("\t0000000000x1" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x03BA, 0x00, 0x00, Local0, 0x00)
        }

        Local0 = ("\t 0000000000x12345678" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x03BF, 0x00, 0x00, Local0, 0x00)
        }

        Local0 = (" \t0000000000x1234567890123456" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x03C4, 0x00, 0x00, Local0, 0x00)
        }

        /* Hex: 0x - hex */

        Local0 = ("  0000000000xabcdefef" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x03CB, 0x00, 0x00, Local0, 0x00)
        }

        Local0 = ("\t\t0000000000xabcdefefadefbcdf" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x03D0, 0x00, 0x00, Local0, 0x00)
        }

        /* Hex: 0x - dec/hex */

        Local0 = (" \t \t \t \t \t0000000000x1ab2cd340fe05678" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x03D7, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x036F, 0x03DA, 0x00)
        Local0 = ("\t \t \t \t \t \t0000000000x1ab2cd340fe0567823456789123456789987" + 0x00)
        CH03 ("", 0x00, 0x0370, 0x03DC, 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x03DF, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x0372, 0x03E2, 0x00)
        /*
         * Implicit String to Integer (<dec>)
         *
         * Method(mf98)
         */
        CH03 ("", 0x00, 0x0373, 0x03EA, 0x00)
        Local0 = ("                       0000000000" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x03EE, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x0375, 0x03F1, 0x00)
        Local0 = ("\t\t\t\t\t\t0000000000000000" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x03F5, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x0377, 0x03F8, 0x00)
        Local0 = ("                                 000000000000000000000000000000000000000" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x03FC, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x0379, 0x03FF, 0x00)
        Local0 = ("\t\t\t\t\t\t\t000000000000000000000000000000000000000" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x0403, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x037B, 0x0406, 0x00)
        Local0 = (" \t\t 0000000001" + 0x00)
        If ((Local0 != 0x01))
        {
            ERR ("", ZFFF, 0x040A, 0x00, 0x00, Local0, 0x01)
        }

        CH03 ("", 0x00, 0x037D, 0x040D, 0x00)
        Local0 = (" \t \t \t00000000012345678" + 0x00)
        If ((Local0 != 0x12345678))
        {
            ERR ("", ZFFF, 0x0411, 0x00, 0x00, Local0, 0x12345678)
        }

        CH03 ("", 0x00, 0x037F, 0x0414, 0x00)
        /*
         * Implicit String to Integer (<hex-dec>)
         *
         * Method(mf99)
         */
        CH03 ("", 0x00, 0x0380, 0x041C, 0x00)
        /* Hex: 0x - dec */

        Local0 = ("\t\t\t\t0000000001234567890123456" + 0x00)
        If (F64)
        {
            If ((Local0 != 0x1234567890123456))
            {
                ERR ("", ZFFF, 0x0423, 0x00, 0x00, Local0, 0x1234567890123456)
            }
        }
        ElseIf ((Local0 != 0x12345678))
        {
            ERR ("", ZFFF, 0x0427, 0x00, 0x00, Local0, 0x12345678)
        }

        /* Hex: 0x - hex */

        Local0 = ("\t\t\t\t000000000abcdefef" + 0x00)
        If ((Local0 != 0xABCDEFEF))
        {
            ERR ("", ZFFF, 0x042F, 0x00, 0x00, Local0, 0xABCDEFEF)
        }

        Local0 = ("     000000000abcdefe" + 0x00)
        If ((Local0 != 0x0ABCDEFE))
        {
            ERR ("", ZFFF, 0x0434, 0x00, 0x00, Local0, 0x0ABCDEFE)
        }

        Local0 = ("             000000000abcdefefadefbcdf" + 0x00)
        If (F64)
        {
            If ((Local0 != 0xABCDEFEFADEFBCDF))
            {
                ERR ("", ZFFF, 0x043A, 0x00, 0x00, Local0, 0xABCDEFEFADEFBCDF)
            }
        }
        ElseIf ((Local0 != 0xABCDEFEF))
        {
            ERR ("", ZFFF, 0x043E, 0x00, 0x00, Local0, 0xABCDEFEF)
        }

        /* Hex: 0x - dec/hex */

        Local0 = ("\t     \t\t\t \t   0000000001ab2cd340fe05678" + 0x00)
        If (F64)
        {
            If ((Local0 != 0x1AB2CD340FE05678))
            {
                ERR ("", ZFFF, 0x0447, 0x00, 0x00, Local0, 0x1AB2CD340FE05678)
            }
        }
        ElseIf ((Local0 != 0x1AB2CD34))
        {
            ERR ("", ZFFF, 0x044B, 0x00, 0x00, Local0, 0x1AB2CD34)
        }

        Local0 = (" 0000000001ab2cd340fe05" + 0x00)
        If (F64)
        {
            If ((Local0 != 0x0001AB2CD340FE05))
            {
                ERR ("", ZFFF, 0x0452, 0x00, 0x00, Local0, 0x0001AB2CD340FE05)
            }
        }
        ElseIf ((Local0 != 0x1AB2CD34))
        {
            ERR ("", ZFFF, 0x0456, 0x00, 0x00, Local0, 0x1AB2CD34)
        }

        Local0 = ("\t0000000001a" + 0x00)
        If ((Local0 != 0x1A))
        {
            ERR ("", ZFFF, 0x045C, 0x00, 0x00, Local0, 0x1A)
        }

        CH03 ("", 0x00, 0x038D, 0x045F, 0x00)
        /*
         * No exceptions in special cases which force exceptions on ToInteger
         *
         * Method(mf9a)
         */
        /* 5. "1234cd" (non-decimal character in dec-image) */
        CH03 ("", 0x00, 0x038E, 0x0468, 0x00)
        Local0 = ("\t0000000001234cd" + 0x00)
        If ((Local0 != 0x001234CD))
        {
            ERR ("", ZFFF, 0x046B, 0x00, 0x00, Local0, 0x001234CD)
        }

        /* 6. "000x1234" (non-decimal character in dec-image) */

        CH03 ("", 0x00, 0x0390, 0x046F, 0x00)
        Local0 = (" \t \t\t\t 000000000000x1234" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x0472, 0x00, 0x00, Local0, 0x00)
        }

        /* 7. "0x1234cdQ" (non-hex character in '0x'-image) */

        CH03 ("", 0x00, 0x0392, 0x0476, 0x00)
        Local0 = (" \t  \t\t\t\t 0000000000x1234cdQ" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x0479, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x0394, 0x047B, 0x00)
        Local0 = (" 0000000001234cdQ" + 0x00)
        If ((Local0 != 0x001234CD))
        {
            ERR ("", ZFFF, 0x047E, 0x00, 0x00, Local0, 0x001234CD)
        }

        CH03 ("", 0x00, 0x0396, 0x0481, 0x00)
        Local0 = ("   \t\t0000000000x0x12345" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x0484, 0x00, 0x00, Local0, 0x00)
        }

        /* 8. "1234 " (white space in dec image) */

        CH03 ("", 0x00, 0x0398, 0x0488, 0x00)
        Local0 = ("   \t\t0000000001234 " + 0x00)
        If ((Local0 != 0x1234))
        {
            ERR ("", ZFFF, 0x048B, 0x00, 0x00, Local0, 0x1234)
        }

        /* 9. "0x1234cd " (white space in '0x'-image) */

        CH03 ("", 0x00, 0x039A, 0x048F, 0x00)
        Local0 = ("\t\t\t  0000000001234cd " + 0x00)
        If ((Local0 != 0x001234CD))
        {
            ERR ("", ZFFF, 0x0492, 0x00, 0x00, Local0, 0x001234CD)
        }

        /* 10. "0x 1234cdQ" (white space after '0x') */

        CH03 ("", 0x00, 0x039C, 0x0496, 0x00)
        Local0 = ("\t\t\t\t   \t \t \t\t0000000000x 1234" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x0499, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x039E, 0x049C, 0x00)
        Local0 = (" \t   \t \t\t \t0000000000x0x 1234" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x049F, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x03A0, 0x04A2, 0x00)
        Local0 = (" \t \t \t    \t\t0000000000x0x 0x 1234" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x04A5, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x03A2, 0x04A8, 0x00)
        Local0 = ("\t \t    \t      \t\t 0000000000x 0x 1234" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x04AB, 0x00, 0x00, Local0, 0x00)
        }

        /* 11. (decimal image exceeding maximal) */
        /*     32-bit mode – the value exceeding "4294967295" */
        If (0x01)
        {
            CH03 ("", 0x00, 0x03A4, 0x04B1, 0x00)
            Local0 = ("\t\t0000000004294967296" + 0x00)
            If (F64)
            {
                If ((Local0 != 0x0000004294967296))
                {
                    ERR ("", ZFFF, 0x04B5, 0x00, 0x00, Local0, 0x0000004294967296)
                }
            }
            ElseIf ((Local0 != 0x42949672))
            {
                ERR ("", ZFFF, 0x04B9, 0x00, 0x00, Local0, 0x42949672)
            }

            CH03 ("", 0x00, 0x03A7, 0x04BD, 0x00)
            Local0 = ("    \t\t    \t\t\t000000000123456789012345678904294967296" + 0x00)
            If (F64)
            {
                If ((Local0 != 0x1234567890123456))
                {
                    ERR ("", ZFFF, 0x04C1, 0x00, 0x00, Local0, 0x1234567890123456)
                }
            }
            ElseIf ((Local0 != 0x12345678))
            {
                ERR ("", ZFFF, 0x04C5, 0x00, 0x00, Local0, 0x12345678)
            }

            CH03 ("", 0x00, 0x03AA, 0x04C9, 0x00)
            Local0 = (" \t \t\t00000000000004294967296" + 0x00)
            If (F64)
            {
                If ((Local0 != 0x0000004294967296))
                {
                    ERR ("", ZFFF, 0x04CD, 0x00, 0x00, Local0, 0x0000004294967296)
                }
            }
            ElseIf ((Local0 != 0x42949672))
            {
                ERR ("", ZFFF, 0x04D1, 0x00, 0x00, Local0, 0x42949672)
            }

            CH03 ("", 0x00, 0x03AD, 0x04D5, 0x00)
            Local0 = ("\t0000000000123456789012345678904294967296" + 0x00)
            If (F64)
            {
                If ((Local0 != 0x1234567890123456))
                {
                    ERR ("", ZFFF, 0x04D9, 0x00, 0x00, Local0, 0x1234567890123456)
                }
            }
            ElseIf ((Local0 != 0x12345678))
            {
                ERR ("", ZFFF, 0x04DD, 0x00, 0x00, Local0, 0x12345678)
            }

            CH03 ("", 0x00, 0x03B0, 0x04E1, 0x00)
            Local0 = ("\t0000000000123456789012345678904294967296" + 0x00)
            If (F64)
            {
                If ((Local0 != 0x1234567890123456))
                {
                    ERR ("", ZFFF, 0x04E5, 0x00, 0x00, Local0, 0x1234567890123456)
                }
            }
            ElseIf ((Local0 != 0x12345678))
            {
                ERR ("", ZFFF, 0x04E9, 0x00, 0x00, Local0, 0x12345678)
            }

            CH03 ("", 0x00, 0x03B3, 0x04ED, 0x00)
            Local0 = (" 000000000123456789012345678904294967296" + 0x00)
            If (F64)
            {
                If ((Local0 != 0x1234567890123456))
                {
                    ERR ("", ZFFF, 0x04F1, 0x00, 0x00, Local0, 0x1234567890123456)
                }
            }
            ElseIf ((Local0 != 0x12345678))
            {
                ERR ("", ZFFF, 0x04F5, 0x00, 0x00, Local0, 0x12345678)
            }

            CH03 ("", 0x00, 0x03B6, 0x04F9, 0x00)
            Local0 = ("\t000000000123456789012345678904294967296" + 0x00)
            If (F64)
            {
                If ((Local0 != 0x1234567890123456))
                {
                    ERR ("", ZFFF, 0x04FD, 0x00, 0x00, Local0, 0x1234567890123456)
                }
            }
            ElseIf ((Local0 != 0x12345678))
            {
                ERR ("", ZFFF, 0x0501, 0x00, 0x00, Local0, 0x12345678)
            }
        }

        /*     64-bit mode – the value exceeding "18446744073709551615" */

        CH03 ("", 0x00, 0x03B8, 0x0507, 0x00)
        Local0 = ("\t\t\t00000000018446744073709551616" + 0x00)
        If (F64)
        {
            If ((Local0 != 0x1844674407370955))
            {
                ERR ("", ZFFF, 0x050B, 0x00, 0x00, Local0, 0x1844674407370955)
            }
        }
        ElseIf ((Local0 != 0x18446744))
        {
            ERR ("", ZFFF, 0x050F, 0x00, 0x00, Local0, 0x18446744)
        }

        CH03 ("", 0x00, 0x03BB, 0x0513, 0x00)
        Local0 = ("\t00000000018446744073709551616" + 0x00)
        If (F64)
        {
            If ((Local0 != 0x1844674407370955))
            {
                ERR ("", ZFFF, 0x0517, 0x00, 0x00, Local0, 0x1844674407370955)
            }
        }
        ElseIf ((Local0 != 0x18446744))
        {
            ERR ("", ZFFF, 0x051B, 0x00, 0x00, Local0, 0x18446744)
        }

        CH03 ("", 0x00, 0x03BE, 0x051F, 0x00)
        Local0 = (" 00000000018446744073709551616" + 0x00)
        If (F64)
        {
            If ((Local0 != 0x1844674407370955))
            {
                ERR ("", ZFFF, 0x0523, 0x00, 0x00, Local0, 0x1844674407370955)
            }
        }
        ElseIf ((Local0 != 0x18446744))
        {
            ERR ("", ZFFF, 0x0527, 0x00, 0x00, Local0, 0x18446744)
        }

        CH03 ("", 0x00, 0x03C1, 0x052B, 0x00)
        Local0 = ("   \t000000000018446744073709551616" + 0x00)
        If (F64)
        {
            If ((Local0 != 0x1844674407370955))
            {
                ERR ("", ZFFF, 0x052F, 0x00, 0x00, Local0, 0x1844674407370955)
            }
        }
        ElseIf ((Local0 != 0x18446744))
        {
            ERR ("", ZFFF, 0x0533, 0x00, 0x00, Local0, 0x18446744)
        }

        CH03 ("", 0x00, 0x03C4, 0x0537, 0x00)
        Local0 = (" \t000000000000000000018446744073709551616" + 0x00)
        If (F64)
        {
            If ((Local0 != 0x1844674407370955))
            {
                ERR ("", ZFFF, 0x053B, 0x00, 0x00, Local0, 0x1844674407370955)
            }
        }
        ElseIf ((Local0 != 0x18446744))
        {
            ERR ("", ZFFF, 0x053F, 0x00, 0x00, Local0, 0x18446744)
        }

        /* 12. "0x12345678901234567" (hex image exceeding maximal) */

        CH03 ("", 0x00, 0x03C7, 0x0544, 0x00)
        Local0 = ("\t\t0000000000x12345678901234567" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x0547, 0x00, 0x00, Local0, 0x00)
        }

        /* 13. "0x00000000000001234" (hex image exceeding maximal; no matter that zeros) */

        CH03 ("", 0x00, 0x03CA, 0x054B, 0x00)
        Local0 = ("           0000000000x00000000000001234" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x054E, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x03CC, 0x0551, 0x00)
        Local0 = ("          \t\t0000000000x0000000000000000000001234" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x0554, 0x00, 0x00, Local0, 0x00)
        }

        /* 14. "0x123456789" (hex image exceeding maximal; for 32-bit mode only) */

        If (0x01)
        {
            CH03 ("", 0x00, 0x03CE, 0x0559, 0x00)
            Local0 = ("0x123456789" + 0x00)
            If ((Local0 != 0x00))
            {
                ERR ("", ZFFF, 0x055C, 0x00, 0x00, Local0, 0x00)
            }
        }

        /* 15. "0x" (incomplete '0x' image) */

        CH03 ("", 0x00, 0x03D0, 0x0561, 0x00)
        Local0 = ("\t0000000000x" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x0564, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x03D2, 0x0566, 0x00)
        Local0 = (" 0000000000x" + 0x00)
        If ((Local0 != 0x00))
        {
            ERR ("", ZFFF, 0x056A, 0x00, 0x00, Local0, 0x00)
        }

        CH03 ("", 0x00, 0x03D4, 0x056C, 0x00)
    }

