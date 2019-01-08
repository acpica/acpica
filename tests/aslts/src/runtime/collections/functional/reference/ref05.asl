    /*
     * Some or all of this work - Copyright (c) 2006 - 2019, Intel Corp.
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
     * References
     */
    Name (Z108, 0x6C)
    /* m16a */

    Method (M1B0, 0, NotSerialized)
    {
        If (Y100)
        {
            TS00 ("m1b0")
        }
        Else
        {
            Debug = "m1b0"
        }

        /* T2:R1-R14 */
        /* Computational Data */
        M1A2 (I900, C009, 0x00, 0x00, C009, 0xFE7CB391D65A0000, 0x00)
        M1A2 (I901, C009, 0x00, 0x00, C009, 0xC1790001, 0x01)
        M1A2 (S900, C00A, 0x00, 0x00, C00A, "12340002", 0x02)
        M1A2 (S901, C00A, 0x00, 0x00, C00A, "qwrtyu0003", 0x03)
        M1A2 (B900, C00B, 0x00, 0x00, C00B, Buffer (0x05)
            {
                 0xB0, 0xB1, 0xB2, 0xB3, 0xB4                     // .....
            }, 0x04)
        M1A2 (F900, C009, 0x00, 0x00, C009, 0x00, 0x05)
        M1A2 (BN90, C009, 0x00, 0x00, C009, 0x00, 0x06)
        M1A2 (IF90, C009, 0x00, 0x00, C009, 0x00, 0x07)
        M1A2 (BF90, C009, 0x00, 0x00, C009, 0xB0, 0x08)
        /* Not Computational Data */

        M1A0 (E900, C00F, Ones, 0x09)
        M1A0 (MX90, C011, Ones, 0x0A)
        If (Y511)
        {
            M1A0 (D900, C00E, Ones, 0x0B)
        }

        If (Y508)
        {
            M1A0 (TZ90, C015, Ones, 0x0C)
        }

        M1A0 (PR90, C014, Ones, 0x0D)
        M1A0 (R900, C012, Ones, 0x0E)
        M1A0 (PW90, C013, Ones, 0x0F)
        /* Elements of Package are Uninitialized */

        M1A0 (P900, C00C, Ones, 0x10)
        /* Elements of Package are Computational Data */

        M1A2 (P901, C00C, 0x01, 0x00, C009, 0xABCD0004, 0x11)
        M1A2 (P901, C00C, 0x01, 0x01, C009, 0x1122334455660005, 0x12)
        M1A2 (P902, C00C, 0x01, 0x00, C00A, "12340006", 0x13)
        M1A2 (P902, C00C, 0x01, 0x01, C00A, "q1w2e3r4t5y6u7i80007", 0x14)
        M1A2 (P903, C00C, 0x01, 0x00, C00A, "qwrtyuiop0008", 0x15)
        M1A2 (P903, C00C, 0x01, 0x01, C00A, "1234567890abdef0250009", 0x16)
        M1A2 (P904, C00C, 0x01, 0x00, C00B, Buffer (0x03)
            {
                 0xB5, 0xB6, 0xB7                                 // ...
            }, 0x17)
        M1A2 (P905, C00C, 0x02, 0x00, C009, 0x0ABC000A, 0x18)
        M1A2 (P905, C00C, 0x02, 0x01, C00A, "0xabc000b", 0x19)
        M1A2 (P906, C00C, 0x02, 0x00, C00A, "abc000d", 0x1A)
        M1A2 (P907, C00C, 0x02, 0x00, C00A, "aqwevbgnm000e", 0x1B)
        M1A2 (P908, C00C, 0x02, 0x00, C00B, Buffer (0x05)
            {
                 0xBA, 0xBB, 0xBC, 0xBD, 0xBE                     // .....
            }, 0x1C)
        M1A2 (P909, C00C, 0x03, 0x00, C009, 0x0ABC000F, 0x1D)
        M1A2 (P90A, C00C, 0x03, 0x00, C00A, "12340010", 0x1E)
        M1A2 (P90B, C00C, 0x03, 0x00, C00A, "zxswefas0011", 0x1F)
        M1A2 (P90C, C00C, 0x03, 0x00, C00B, Buffer (0x03)
            {
                 0xBF, 0xC0, 0xC1                                 // ...
            }, 0x20)
        M1A2 (P90D, C00C, 0x01, 0x00, C009, 0xFE7CB391D65A0000, 0x21)
        M1A2 (P90E, C00C, 0x01, 0x00, C009, 0xC1790001, 0x22)
        M1A2 (P90F, C00C, 0x01, 0x00, C00A, "12340002", 0x23)
        M1A2 (P910, C00C, 0x01, 0x00, C00A, "qwrtyu0003", 0x24)
        M1A2 (P911, C00C, 0x01, 0x00, C00B, Buffer (0x05)
            {
                 0xB0, 0xB1, 0xB2, 0xB3, 0xB4                     // .....
            }, 0x25)
        If (Y118)
        {
            M1A2 (P912, C00C, 0x01, 0x00, C00D, 0x00, 0x26)
            M1A2 (P913, C00C, 0x01, 0x00, C00D, 0x00, 0x27)
            M1A2 (P914, C00C, 0x01, 0x00, C00D, 0x00, 0x28)
            M1A2 (P915, C00C, 0x01, 0x00, C016, 0xB0, 0x29)
        }

        /* Elements of Package are NOT Computational Data */

        M1A0 (P916, C00C, Ones, 0x2A)
        M1A0 (P917, C00C, Ones, 0x2B)
        M1A0 (P918, C00C, Ones, 0x2C)
        M1A0 (P919, C00C, Ones, 0x2D)
        M1A0 (P91A, C00C, Ones, 0x2E)
        M1A0 (P91B, C00C, Ones, 0x2F)
        M1A0 (P91C, C00C, Ones, 0x30)
        /* Elements of Package are Methods */

        M1A0 (P91D, C00C, Ones, 0x31)
        M1A0 (P91E, C00C, Ones, 0x32)
        M1A0 (P91F, C00C, Ones, 0x33)
        M1A0 (P920, C00C, Ones, 0x34)
        M1A0 (P921, C00C, Ones, 0x35)
        M1A0 (P922, C00C, Ones, 0x36)
        M1A0 (P923, C00C, Ones, 0x37)
        M1A0 (P924, C00C, Ones, 0x38)
        M1A0 (P925, C00C, Ones, 0x39)
        M1A0 (P926, C00C, Ones, 0x3A)
        M1A0 (P927, C00C, Ones, 0x3B)
        M1A0 (P928, C00C, Ones, 0x3C)
        M1A0 (P929, C00C, Ones, 0x3D)
        M1A0 (P92A, C00C, Ones, 0x3E)
        M1A0 (P92B, C00C, Ones, 0x3F)
        M1A0 (P92C, C00C, Ones, 0x40)
        M1A0 (P92D, C00C, Ones, 0x41)
        M1A0 (P92E, C00C, Ones, 0x42)
        M1A0 (P92F, C00C, Ones, 0x43)
        M1A0 (P930, C00C, Ones, 0x44)
        M1A0 (P931, C00C, Ones, 0x45)
        M1A0 (P932, C00C, Ones, 0x46)
        M1A0 (P933, C00C, Ones, 0x47)
        M1A0 (P934, C00C, Ones, 0x48)
        M1A0 (P935, C00C, Ones, 0x49)
        M1A0 (P936, C00C, Ones, 0x4A)
        M1A0 (P937, C00C, Ones, 0x4B)
        M1A0 (P938, C00C, Ones, 0x4C)
        M1A0 (P939, C00C, Ones, 0x4D)
        M1A0 (P93A, C00C, Ones, 0x4E)
        M1A0 (P93B, C00C, Ones, 0x4F)
        M1A0 (P93C, C00C, Ones, 0x50)
        M1A0 (P93D, C00C, Ones, 0x51)
        M1A0 (P93E, C00C, Ones, 0x52)
        M1A0 (P93F, C00C, Ones, 0x53)
        M1A0 (P940, C00C, Ones, 0x54)
        M1A0 (P941, C00C, Ones, 0x55)
        M1A0 (P942, C00C, Ones, 0x56)
        M1A0 (P943, C00C, Ones, 0x57)
        M1A0 (P944, C00C, Ones, 0x58)
        M1A0 (P945, C00C, Ones, 0x59)
        M1A0 (P946, C00C, Ones, 0x5A)
        M1A0 (P947, C00C, Ones, 0x5B)
        M1A0 (P948, C00C, Ones, 0x5C)
        M1A0 (P949, C00C, Ones, 0x5D)
        M1A0 (P94A, C00C, Ones, 0x5E)
        M1A0 (P94B, C00C, Ones, 0x5F)
        M1A0 (P94C, C00C, Ones, 0x60)
        M1A0 (P94D, C00C, Ones, 0x61)
        M1A0 (P94E, C00C, Ones, 0x62)
        M1A0 (P94F, C00C, Ones, 0x63)
        M1A0 (P950, C00C, Ones, 0x64)
        M1A0 (P951, C00C, Ones, 0x65)
        M1A0 (P952, C00C, Ones, 0x66)
        M1A0 (P953, C00C, Ones, 0x67)
        /* Methods */

        If (Y509)
        {
            M1A0 (M900 (), C010, Ones, 0x68)
            M1A0 (M901 (), C010, Ones, 0x69)
            M1A0 (M902 (), C010, Ones, 0x6A)
            M1A0 (M903 (), C010, Ones, 0x6B)
            M1A0 (M904 (), C010, Ones, 0x6C)
            M1A0 (M905 (), C010, Ones, 0x6D)
            M1A0 (M906 (), C010, Ones, 0x6E)
            M1A0 (M907 (), C010, Ones, 0x6F)
            M1A0 (M908 (), C010, Ones, 0x70)
            M1A0 (M909 (), C010, Ones, 0x71)
            M1A0 (M90A (), C010, Ones, 0x72)
            M1A0 (M90B (), C010, Ones, 0x73)
            M1A0 (M90C (), C010, Ones, 0x74)
            M1A0 (M90D (), C010, Ones, 0x75)
            M1A0 (M90E (), C010, Ones, 0x76)
            M1A0 (M90F (), C010, Ones, 0x77)
            M1A0 (M910 (), C010, Ones, 0x78)
            M1A0 (M911 (), C010, Ones, 0x79)
            M1A0 (M912 (), C010, Ones, 0x7A)
            M1A0 (M913 (), C010, Ones, 0x7B)
            M1A0 (M914 (), C010, Ones, 0x7C)
            M1A0 (M915 (), C010, Ones, 0x7D)
            M1A0 (M916 (), C010, Ones, 0x7E)
            M1A0 (M917 (), C010, Ones, 0x7F)
            M1A0 (M918 (), C010, Ones, 0x80)
            M1A0 (M919 (), C010, Ones, 0x81)
            M1A0 (M91A (), C010, Ones, 0x82)
            M1A0 (M91B (), C010, Ones, 0x83)
            M1A0 (M91C (), C010, Ones, 0x84)
            M1A0 (M91D (), C010, Ones, 0x85)
            M1A0 (M91E (), C010, Ones, 0x86)
            M1A0 (M91F (), C010, Ones, 0x87)
            M1A0 (M920 (), C010, Ones, 0x88)
            M1A0 (M921 (), C010, Ones, 0x89)
            M1A0 (M922 (), C010, Ones, 0x8A)
            M1A0 (M923 (), C010, Ones, 0x8B)
            M1A0 (M924 (), C010, Ones, 0x8C)
            M1A0 (M925 (), C010, Ones, 0x8D)
            M1A0 (M926 (), C010, Ones, 0x8E)
            M1A0 (M927 (), C010, Ones, 0x8F)
            M1A0 (M928 (), C010, Ones, 0x90)
            M1A0 (M929 (), C010, Ones, 0x91)
            M1A0 (M92A (), C010, Ones, 0x92)
            M1A0 (M92B (), C010, Ones, 0x93)
            M1A0 (M92C (), C010, Ones, 0x94)
            M1A0 (M92D (), C010, Ones, 0x95)
            M1A0 (M92E (), C010, Ones, 0x96)
            M1A0 (M92F (), C010, Ones, 0x97)
            M1A0 (M930 (), C010, Ones, 0x98)
            M1A0 (M931 (), C010, Ones, 0x99)
            M1A0 (M932 (), C010, Ones, 0x9A)
            M1A0 (M933 (), C010, Ones, 0x9B)
            M1A0 (M934 (), C010, Ones, 0x9C)
            M1A0 (M935 (), C010, Ones, 0x9D)
        }

        M1A6 ()
    }

    /*
     * CopyObject of Object to LocalX:
     *
     * Local0-Local7 can be written with any
     * type object without any conversion.
     *
     * Check each type after each one.
     */
    Method (M1B1, 0, Serialized)
    {
        C081 = Z108 /* absolute index of file initiating the checking */ /* \Z108 */
        /* All types */

        CopyObject (I900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x9E)
        CopyObject (S900, Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x9F)
        CopyObject (B900, Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0xA0)
        CopyObject (P900, Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0xA1)
        CopyObject (F900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0xA2)
        CopyObject (D900, Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0xA3)
        CopyObject (E900, Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0xA4)
        If (RN06)
        {
            CopyObject (M901 (), Local0)
        }
        Else
        {
            CopyObject (DerefOf (RefOf (M901)), Local0)
        }

        M1A3 (Local0, C010, Z108, __METHOD__, 0xA5)
        CopyObject (MX90, Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0xA6)
        If (Y510)
        {
            CopyObject (R900, Local0)
            M1A3 (Local0, C012, Z108, __METHOD__, 0xA7)
        }

        CopyObject (PW90, Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0xA8)
        CopyObject (PR90, Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0xA9)
        If (Y508)
        {
            CopyObject (TZ90, Local0)
            M1A3 (Local0, C015, Z108, __METHOD__, 0xAA)
        }

        CopyObject (BF90, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0xAB)
        /*///////////////////// All after Integer */

        CopyObject (I900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0xAC)
        CopyObject (I900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0xAD)
        CopyObject (S900, Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0xAE)
        CopyObject (I900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0xAF)
        CopyObject (B900, Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0xB0)
        CopyObject (I900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0xB1)
        CopyObject (P900, Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0xB2)
        CopyObject (I900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0xB3)
        CopyObject (F900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0xB4)
        CopyObject (I900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0xB5)
        CopyObject (D900, Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0xB6)
        CopyObject (I900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0xB7)
        CopyObject (E900, Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0xB8)
        CopyObject (I900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0xB9)
        If (RN06)
        {
            CopyObject (M901 (), Local0)
        }
        Else
        {
            CopyObject (DerefOf (RefOf (M901)), Local0)
        }

        M1A3 (Local0, C010, Z108, __METHOD__, 0xBA)
        CopyObject (I900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0xBB)
        CopyObject (MX90, Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0xBC)
        CopyObject (I900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0xBD)
        If (Y510)
        {
            CopyObject (R900, Local0)
            M1A3 (Local0, C012, Z108, __METHOD__, 0xBE)
        }

        CopyObject (I900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0xBF)
        CopyObject (PW90, Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0xC0)
        CopyObject (I900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0xC1)
        CopyObject (PR90, Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0xC2)
        CopyObject (I900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0xC3)
        If (Y508)
        {
            CopyObject (TZ90, Local0)
            M1A3 (Local0, C015, Z108, __METHOD__, 0xC4)
        }

        CopyObject (I900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0xC5)
        CopyObject (BF90, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0xC6)
        CopyObject (I900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0xC7)
        /*///////////////////// All-Integer after String */

        CopyObject (S900, Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0xC8)
        CopyObject (S900, Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0xC9)
        CopyObject (B900, Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0xCA)
        CopyObject (S900, Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0xCB)
        CopyObject (P900, Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0xCC)
        CopyObject (S900, Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0xCD)
        CopyObject (F900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0xCE)
        CopyObject (S900, Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0xCF)
        CopyObject (D900, Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0xD0)
        CopyObject (S900, Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0xD1)
        CopyObject (E900, Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0xD2)
        CopyObject (S900, Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0xD3)
        If (RN06)
        {
            CopyObject (M901 (), Local0)
        }
        Else
        {
            CopyObject (DerefOf (RefOf (M901)), Local0)
        }

        M1A3 (Local0, C010, Z108, __METHOD__, 0xD4)
        CopyObject (S900, Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0xD5)
        CopyObject (MX90, Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0xD6)
        CopyObject (S900, Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0xD7)
        If (Y510)
        {
            CopyObject (R900, Local0)
            M1A3 (Local0, C012, Z108, __METHOD__, 0xD8)
        }

        CopyObject (S900, Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0xD9)
        CopyObject (PW90, Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0xDA)
        CopyObject (S900, Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0xDB)
        CopyObject (PR90, Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0xDC)
        CopyObject (S900, Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0xDD)
        If (Y508)
        {
            CopyObject (TZ90, Local0)
            M1A3 (Local0, C015, Z108, __METHOD__, 0xDE)
        }

        CopyObject (S900, Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0xDF)
        CopyObject (BF90, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0xE0)
        CopyObject (S900, Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0xE1)
        /*///////////////////// All-(Integer+String) after Buffer */

        CopyObject (B900, Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0xE2)
        CopyObject (B900, Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0xE3)
        CopyObject (P900, Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0xE4)
        CopyObject (B900, Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0xE5)
        CopyObject (F900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0xE6)
        CopyObject (B900, Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0xE7)
        CopyObject (D900, Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0xE8)
        CopyObject (B900, Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0xE9)
        CopyObject (E900, Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0xEA)
        CopyObject (B900, Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0xEB)
        If (RN06)
        {
            CopyObject (M901 (), Local0)
        }
        Else
        {
            CopyObject (DerefOf (RefOf (M901)), Local0)
        }

        M1A3 (Local0, C010, Z108, __METHOD__, 0xEC)
        CopyObject (B900, Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0xED)
        CopyObject (MX90, Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0xEE)
        CopyObject (B900, Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0xEF)
        If (Y510)
        {
            CopyObject (R900, Local0)
            M1A3 (Local0, C012, Z108, __METHOD__, 0xF0)
        }

        CopyObject (B900, Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0xF1)
        CopyObject (PW90, Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0xF2)
        CopyObject (B900, Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0xF3)
        CopyObject (PR90, Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0xF4)
        CopyObject (B900, Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0xF5)
        If (Y508)
        {
            CopyObject (TZ90, Local0)
            M1A3 (Local0, C015, Z108, __METHOD__, 0xF6)
        }

        CopyObject (B900, Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0xF7)
        CopyObject (BF90, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0xF7)
        CopyObject (B900, Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0xF9)
        /*///////////////////// All-(...) after Package */

        CopyObject (P900, Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0xFA)
        CopyObject (P900, Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0xFB)
        CopyObject (F900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0xFC)
        CopyObject (P900, Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0xFD)
        CopyObject (D900, Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0xFE)
        CopyObject (P900, Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0xFF)
        CopyObject (E900, Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x0100)
        CopyObject (P900, Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x0101)
        If (RN06)
        {
            CopyObject (M901 (), Local0)
        }
        Else
        {
            CopyObject (DerefOf (RefOf (M901)), Local0)
        }

        M1A3 (Local0, C010, Z108, __METHOD__, 0x0102)
        CopyObject (P900, Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x0103)
        CopyObject (MX90, Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x0104)
        CopyObject (P900, Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x0105)
        If (Y510)
        {
            CopyObject (R900, Local0)
            M1A3 (Local0, C012, Z108, __METHOD__, 0x0106)
        }

        CopyObject (P900, Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x0107)
        CopyObject (PW90, Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x0108)
        CopyObject (P900, Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x0109)
        CopyObject (PR90, Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x010A)
        CopyObject (P900, Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x010B)
        If (Y508)
        {
            CopyObject (TZ90, Local0)
            M1A3 (Local0, C015, Z108, __METHOD__, 0x010C)
        }

        CopyObject (P900, Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x010D)
        CopyObject (BF90, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x010E)
        CopyObject (P900, Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x010F)
        /*///////////////////// All-(...) after Field Unit */

        CopyObject (F900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x0110)
        CopyObject (F900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x0111)
        CopyObject (D900, Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x0112)
        CopyObject (F900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x0113)
        CopyObject (E900, Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x0114)
        CopyObject (F900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x0115)
        If (RN06)
        {
            CopyObject (M901 (), Local0)
        }
        Else
        {
            CopyObject (DerefOf (RefOf (M901)), Local0)
        }

        M1A3 (Local0, C010, Z108, __METHOD__, 0x0116)
        CopyObject (F900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x0117)
        CopyObject (MX90, Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x0118)
        CopyObject (F900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x0119)
        If (Y510)
        {
            CopyObject (R900, Local0)
            M1A3 (Local0, C012, Z108, __METHOD__, 0x011A)
        }

        CopyObject (F900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x011B)
        CopyObject (PW90, Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x011C)
        CopyObject (F900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x011D)
        CopyObject (PR90, Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x011E)
        CopyObject (F900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x011F)
        If (Y508)
        {
            CopyObject (TZ90, Local0)
            M1A3 (Local0, C015, Z108, __METHOD__, 0x0120)
        }

        CopyObject (F900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x0121)
        CopyObject (BF90, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x0122)
        CopyObject (F900, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x0123)
        /*///////////////////// All-(...) after Device */

        CopyObject (D900, Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x0124)
        CopyObject (D900, Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x0125)
        CopyObject (E900, Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x0126)
        CopyObject (D900, Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x0127)
        If (RN06)
        {
            CopyObject (M901 (), Local0)
        }
        Else
        {
            CopyObject (DerefOf (RefOf (M901)), Local0)
        }

        M1A3 (Local0, C010, Z108, __METHOD__, 0x0128)
        CopyObject (D900, Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x0129)
        CopyObject (MX90, Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x012A)
        CopyObject (D900, Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x012B)
        If (Y510)
        {
            CopyObject (R900, Local0)
            M1A3 (Local0, C012, Z108, __METHOD__, 0x012C)
        }

        CopyObject (D900, Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x012D)
        CopyObject (PW90, Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x012E)
        CopyObject (D900, Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x012F)
        CopyObject (PR90, Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x0130)
        CopyObject (D900, Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x0131)
        If (Y508)
        {
            CopyObject (TZ90, Local0)
            M1A3 (Local0, C015, Z108, __METHOD__, 0x0132)
        }

        CopyObject (D900, Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x0133)
        CopyObject (BF90, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x0134)
        CopyObject (D900, Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x0135)
        /*///////////////////// All-(...) after Event */

        CopyObject (E900, Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x0136)
        CopyObject (E900, Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x0137)
        If (RN06)
        {
            CopyObject (M901 (), Local0)
        }
        Else
        {
            CopyObject (DerefOf (RefOf (M901)), Local0)
        }

        M1A3 (Local0, C010, Z108, __METHOD__, 0x0138)
        CopyObject (E900, Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x0139)
        CopyObject (MX90, Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x013A)
        CopyObject (E900, Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x013B)
        If (Y510)
        {
            CopyObject (R900, Local0)
            M1A3 (Local0, C012, Z108, __METHOD__, 0x013C)
        }

        CopyObject (E900, Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x013D)
        CopyObject (PW90, Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x013E)
        CopyObject (E900, Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x013F)
        CopyObject (PR90, Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x0140)
        CopyObject (E900, Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x0141)
        If (Y508)
        {
            CopyObject (TZ90, Local0)
            M1A3 (Local0, C015, Z108, __METHOD__, 0x0142)
        }

        CopyObject (E900, Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x0143)
        CopyObject (BF90, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x0144)
        CopyObject (E900, Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x0145)
        /*///////////////////// All-(...) after Method */

        If (RN06)
        {
            CopyObject (M901 (), Local0)
        }
        Else
        {
            CopyObject (DerefOf (RefOf (M901)), Local0)
        }

        M1A3 (Local0, C010, Z108, __METHOD__, 0x0146)
        If (RN06)
        {
            CopyObject (M901 (), Local0)
        }
        Else
        {
            CopyObject (DerefOf (RefOf (M901)), Local0)
        }

        M1A3 (Local0, C010, Z108, __METHOD__, 0x0147)
        CopyObject (MX90, Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x0148)
        If (RN06)
        {
            CopyObject (M901 (), Local0)
        }
        Else
        {
            CopyObject (DerefOf (RefOf (M901)), Local0)
        }

        M1A3 (Local0, C010, Z108, __METHOD__, 0x0149)
        If (Y510)
        {
            CopyObject (R900, Local0)
            M1A3 (Local0, C012, Z108, __METHOD__, 0x014A)
        }

        If (RN06)
        {
            CopyObject (M901 (), Local0)
        }
        Else
        {
            CopyObject (DerefOf (RefOf (M901)), Local0)
        }

        M1A3 (Local0, C010, Z108, __METHOD__, 0x014B)
        CopyObject (PW90, Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x014C)
        If (RN06)
        {
            CopyObject (M901 (), Local0)
        }
        Else
        {
            CopyObject (DerefOf (RefOf (M901)), Local0)
        }

        M1A3 (Local0, C010, Z108, __METHOD__, 0x014D)
        CopyObject (PR90, Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x014E)
        If (RN06)
        {
            CopyObject (M901 (), Local0)
        }
        Else
        {
            CopyObject (DerefOf (RefOf (M901)), Local0)
        }

        M1A3 (Local0, C010, Z108, __METHOD__, 0x014F)
        If (Y508)
        {
            CopyObject (TZ90, Local0)
            M1A3 (Local0, C015, Z108, __METHOD__, 0x0150)
        }

        If (RN06)
        {
            CopyObject (M901 (), Local0)
        }
        Else
        {
            CopyObject (DerefOf (RefOf (M901)), Local0)
        }

        M1A3 (Local0, C010, Z108, __METHOD__, 0x0151)
        CopyObject (BF90, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x0152)
        If (RN06)
        {
            CopyObject (M901 (), Local0)
        }
        Else
        {
            CopyObject (DerefOf (RefOf (M901)), Local0)
        }

        M1A3 (Local0, C010, Z108, __METHOD__, 0x0153)
        /*///////////////////// All-(...) after Mutex */

        CopyObject (MX90, Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x0154)
        CopyObject (MX90, Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x0155)
        If (Y510)
        {
            CopyObject (R900, Local0)
            M1A3 (Local0, C012, Z108, __METHOD__, 0x0156)
        }

        CopyObject (MX90, Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x0157)
        CopyObject (PW90, Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x0158)
        CopyObject (MX90, Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x0159)
        CopyObject (PR90, Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x015A)
        CopyObject (MX90, Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x015B)
        If (Y508)
        {
            CopyObject (TZ90, Local0)
            M1A3 (Local0, C015, Z108, __METHOD__, 0x015C)
        }

        CopyObject (MX90, Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x015D)
        CopyObject (BF90, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x015E)
        CopyObject (MX90, Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x015F)
        /*///////////////////// All-(...) after Operation Region */

        If (Y510)
        {
            CopyObject (R900, Local0)
            M1A3 (Local0, C012, Z108, __METHOD__, 0x0160)
        }

        If (Y510)
        {
            CopyObject (R900, Local0)
            M1A3 (Local0, C012, Z108, __METHOD__, 0x0161)
        }

        CopyObject (PW90, Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x0162)
        If (Y510)
        {
            CopyObject (R900, Local0)
            M1A3 (Local0, C012, Z108, __METHOD__, 0x0163)
        }

        CopyObject (PR90, Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x0164)
        If (Y510)
        {
            CopyObject (R900, Local0)
            M1A3 (Local0, C012, Z108, __METHOD__, 0x0165)
        }

        If (Y508)
        {
            CopyObject (TZ90, Local0)
            M1A3 (Local0, C015, Z108, __METHOD__, 0x0166)
        }

        If (Y510)
        {
            CopyObject (R900, Local0)
            M1A3 (Local0, C012, Z108, __METHOD__, 0x0167)
        }

        CopyObject (BF90, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x0168)
        If (Y510)
        {
            CopyObject (R900, Local0)
            M1A3 (Local0, C012, Z108, __METHOD__, 0x0169)
        }

        /*///////////////////// All-(...) after Power Resource */

        CopyObject (PW90, Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x016A)
        CopyObject (PW90, Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x016B)
        CopyObject (PR90, Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x016C)
        CopyObject (PW90, Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x016D)
        If (Y508)
        {
            CopyObject (TZ90, Local0)
            M1A3 (Local0, C015, Z108, __METHOD__, 0x016E)
        }

        CopyObject (PW90, Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x016F)
        CopyObject (BF90, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x0170)
        CopyObject (PW90, Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x0171)
        /*///////////////////// All-(...) after Processor */

        CopyObject (PR90, Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x0172)
        CopyObject (PR90, Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x0173)
        If (Y508)
        {
            CopyObject (TZ90, Local0)
            M1A3 (Local0, C015, Z108, __METHOD__, 0x0174)
        }

        CopyObject (PR90, Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x0175)
        CopyObject (BF90, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x0176)
        CopyObject (PR90, Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x0177)
        /*///////////////////// All-(...) after Thermal Zone */

        If (Y508)
        {
            CopyObject (TZ90, Local0)
            M1A3 (Local0, C015, Z108, __METHOD__, 0x0178)
        }

        CopyObject (BF90, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x0179)
        If (Y508)
        {
            CopyObject (TZ90, Local0)
            M1A3 (Local0, C015, Z108, __METHOD__, 0x017A)
        }

        /*///////////////////// All-(...) after Buffer Field */

        CopyObject (BF90, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x017B)
        CopyObject (BF90, Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x017C)
    }

    /*
     * Store of Object to LocalX:
     *
     * Local0-Local7 can be written without any conversion
     *
     * A set of available for Store types is restricted
     *
     * Check each available type after each one
     */
    Method (M1B2, 0, Serialized)
    {
        C081 = Z108 /* absolute index of file initiating the checking */ /* \Z108 */
        /* All available for Store types */

        Local0 = I900 /* \I900 */
        M1A3 (Local0, C009, Z108, __METHOD__, 0x017D)
        Local0 = S900 /* \S900 */
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x017E)
        Local0 = B900 /* \B900 */
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x017F)
        Local0 = P900 /* \P900 */
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x0180)
        Local0 = F900 /* \F900 */
        M1A3 (Local0, C009, Z108, __METHOD__, 0x0181)
        Local0 = BF90 /* \BF90 */
        M1A3 (Local0, C009, Z108, __METHOD__, 0x0182)
        /*///////////////////// All after Integer */

        Local0 = I900 /* \I900 */
        M1A3 (Local0, C009, Z108, __METHOD__, 0x0183)
        Local0 = I900 /* \I900 */
        M1A3 (Local0, C009, Z108, __METHOD__, 0x0184)
        Local0 = S900 /* \S900 */
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x0185)
        Local0 = I900 /* \I900 */
        M1A3 (Local0, C009, Z108, __METHOD__, 0x0186)
        Local0 = B900 /* \B900 */
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x0187)
        Local0 = I900 /* \I900 */
        M1A3 (Local0, C009, Z108, __METHOD__, 0x0188)
        Local0 = P900 /* \P900 */
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x0189)
        Local0 = I900 /* \I900 */
        M1A3 (Local0, C009, Z108, __METHOD__, 0x018A)
        Local0 = F900 /* \F900 */
        M1A3 (Local0, C009, Z108, __METHOD__, 0x018B)
        Local0 = I900 /* \I900 */
        M1A3 (Local0, C009, Z108, __METHOD__, 0x018C)
        Local0 = BF90 /* \BF90 */
        M1A3 (Local0, C009, Z108, __METHOD__, 0x018D)
        Local0 = I900 /* \I900 */
        M1A3 (Local0, C009, Z108, __METHOD__, 0x018E)
        /*///////////////////// All-Integer after String */

        Local0 = S900 /* \S900 */
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x018F)
        Local0 = S900 /* \S900 */
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x0190)
        Local0 = B900 /* \B900 */
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x0191)
        Local0 = S900 /* \S900 */
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x0192)
        Local0 = P900 /* \P900 */
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x0193)
        Local0 = S900 /* \S900 */
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x0194)
        Local0 = F900 /* \F900 */
        M1A3 (Local0, C009, Z108, __METHOD__, 0x0195)
        Local0 = S900 /* \S900 */
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x0196)
        Local0 = BF90 /* \BF90 */
        M1A3 (Local0, C009, Z108, __METHOD__, 0x0197)
        Local0 = S900 /* \S900 */
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x0198)
        /*///////////////////// All-(Integer+String) after Buffer */

        Local0 = B900 /* \B900 */
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x0199)
        Local0 = B900 /* \B900 */
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x019A)
        Local0 = P900 /* \P900 */
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x019B)
        Local0 = B900 /* \B900 */
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x019C)
        Local0 = F900 /* \F900 */
        M1A3 (Local0, C009, Z108, __METHOD__, 0x019D)
        Local0 = B900 /* \B900 */
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x019E)
        Local0 = BF90 /* \BF90 */
        M1A3 (Local0, C009, Z108, __METHOD__, 0x019F)
        Local0 = B900 /* \B900 */
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x01A0)
        /*///////////////////// All-(...) after Package */

        Local0 = P900 /* \P900 */
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x01A1)
        Local0 = P900 /* \P900 */
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x01A2)
        Local0 = F900 /* \F900 */
        M1A3 (Local0, C009, Z108, __METHOD__, 0x01A3)
        Local0 = P900 /* \P900 */
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x01A4)
        Local0 = BF90 /* \BF90 */
        M1A3 (Local0, C009, Z108, __METHOD__, 0x01A5)
        Local0 = P900 /* \P900 */
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x01A6)
        /*///////////////////// All-(...) after Field Unit */

        Local0 = F900 /* \F900 */
        M1A3 (Local0, C009, Z108, __METHOD__, 0x01A7)
        Local0 = F900 /* \F900 */
        M1A3 (Local0, C009, Z108, __METHOD__, 0x01A8)
        Local0 = BF90 /* \BF90 */
        M1A3 (Local0, C009, Z108, __METHOD__, 0x01A9)
        Local0 = F900 /* \F900 */
        M1A3 (Local0, C009, Z108, __METHOD__, 0x01AA)
        /*///////////////////// All-(...) after Buffer Field */

        Local0 = BF90 /* \BF90 */
        M1A3 (Local0, C009, Z108, __METHOD__, 0x01AB)
        Local0 = BF90 /* \BF90 */
        M1A3 (Local0, C009, Z108, __METHOD__, 0x01AC)
    }

    /*
     * CopyObject the result of RefOf/CondRefOf to LocalX
     *
     * Local0-Local7 can be written with RefOf_References
     * to any type object without any conversion.
     *
     * Check each type after each one.
     *
     * The same as m1b1 but RefOf() added.
     */
    Method (M1B4, 0, Serialized)
    {
        C081 = Z108 /* absolute index of file initiating the checking */ /* \Z108 */
        /* All types */

        CopyObject (RefOf (I900), Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x01AD)
        CopyObject (RefOf (S900), Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x01AE)
        CopyObject (RefOf (B900), Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x01AF)
        CopyObject (RefOf (P900), Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x01B0)
        CopyObject (RefOf (F900), Local0)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x01B1)
        CopyObject (RefOf (D900), Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x01B2)
        CopyObject (RefOf (E900), Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x01B3)
        CopyObject (RefOf (M901), Local0)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x01B4)
        CopyObject (RefOf (MX90), Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x01B5)
        CopyObject (RefOf (R900), Local0)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x01B6)
        CopyObject (RefOf (PW90), Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x01B7)
        CopyObject (RefOf (PR90), Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x01B8)
        CopyObject (RefOf (TZ90), Local0)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x01B9)
        CopyObject (RefOf (BF90), Local0)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x01BA)
        /*///////////////////// All after Integer */

        CopyObject (RefOf (I900), Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x01BB)
        CopyObject (RefOf (I900), Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x01BC)
        CopyObject (RefOf (S900), Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x01BD)
        CopyObject (RefOf (I900), Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x01BE)
        CopyObject (RefOf (B900), Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x01BF)
        CopyObject (RefOf (I900), Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x01C0)
        CopyObject (RefOf (P900), Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x01C1)
        CopyObject (RefOf (I900), Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x01C2)
        CopyObject (RefOf (F900), Local0)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x01C3)
        CopyObject (RefOf (I900), Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x01C4)
        CopyObject (RefOf (D900), Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x01C5)
        CopyObject (RefOf (I900), Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x01C6)
        CopyObject (RefOf (E900), Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x01C7)
        CopyObject (RefOf (I900), Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x01C8)
        CopyObject (RefOf (M901), Local0)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x01C9)
        CopyObject (RefOf (I900), Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x01CA)
        CopyObject (RefOf (MX90), Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x01CB)
        CopyObject (RefOf (I900), Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x01CC)
        CopyObject (RefOf (R900), Local0)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x01CD)
        CopyObject (RefOf (I900), Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x01CE)
        CopyObject (RefOf (PW90), Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x01CF)
        CopyObject (RefOf (I900), Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x01D0)
        CopyObject (RefOf (PR90), Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x01D1)
        CopyObject (RefOf (I900), Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x01D2)
        CopyObject (RefOf (TZ90), Local0)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x01D3)
        CopyObject (RefOf (I900), Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x01D4)
        CopyObject (RefOf (BF90), Local0)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x01D5)
        CopyObject (RefOf (I900), Local0)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x01D6)
        /*///////////////////// All-Integer after String */

        CopyObject (RefOf (S900), Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x01D7)
        CopyObject (RefOf (S900), Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x01D8)
        CopyObject (RefOf (B900), Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x01D9)
        CopyObject (RefOf (S900), Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x01DA)
        CopyObject (RefOf (P900), Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x01DB)
        CopyObject (RefOf (S900), Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x01DC)
        CopyObject (RefOf (F900), Local0)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x01DD)
        CopyObject (RefOf (S900), Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x01DE)
        CopyObject (RefOf (D900), Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x01DF)
        CopyObject (RefOf (S900), Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x01E0)
        CopyObject (RefOf (E900), Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x01E1)
        CopyObject (RefOf (S900), Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x01E2)
        CopyObject (RefOf (M901), Local0)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x01E3)
        CopyObject (RefOf (S900), Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x01E4)
        CopyObject (RefOf (MX90), Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x01E5)
        CopyObject (RefOf (S900), Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x01E6)
        CopyObject (RefOf (R900), Local0)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x01E7)
        CopyObject (RefOf (S900), Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x01E8)
        CopyObject (RefOf (PW90), Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x01E9)
        CopyObject (RefOf (S900), Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x01EA)
        CopyObject (RefOf (PR90), Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x01EB)
        CopyObject (RefOf (S900), Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x01EC)
        CopyObject (RefOf (TZ90), Local0)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x01ED)
        CopyObject (RefOf (S900), Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x01EE)
        CopyObject (RefOf (BF90), Local0)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x01EF)
        CopyObject (RefOf (S900), Local0)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x01F0)
        /*///////////////////// All-(Integer+String) after Buffer */

        CopyObject (RefOf (B900), Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x01F1)
        CopyObject (RefOf (B900), Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x01F2)
        CopyObject (RefOf (P900), Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x01F3)
        CopyObject (RefOf (B900), Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x01F4)
        CopyObject (RefOf (F900), Local0)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x01F5)
        CopyObject (RefOf (B900), Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x01F6)
        CopyObject (RefOf (D900), Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x01F7)
        CopyObject (RefOf (B900), Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x01F8)
        CopyObject (RefOf (E900), Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x01F9)
        CopyObject (RefOf (B900), Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x01FA)
        CopyObject (RefOf (M901), Local0)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x01FB)
        CopyObject (RefOf (B900), Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x01FC)
        CopyObject (RefOf (MX90), Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x01FD)
        CopyObject (RefOf (B900), Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x01FE)
        CopyObject (RefOf (R900), Local0)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x01FF)
        CopyObject (RefOf (B900), Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x0200)
        CopyObject (RefOf (PW90), Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x0201)
        CopyObject (RefOf (B900), Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x0202)
        CopyObject (RefOf (PR90), Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x0203)
        CopyObject (RefOf (B900), Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x0204)
        CopyObject (RefOf (TZ90), Local0)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x0205)
        CopyObject (RefOf (B900), Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x0206)
        CopyObject (RefOf (BF90), Local0)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x0207)
        CopyObject (RefOf (B900), Local0)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x0208)
        /*///////////////////// All-(...) after Package */

        CopyObject (RefOf (P900), Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x0209)
        CopyObject (RefOf (P900), Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x020A)
        CopyObject (RefOf (F900), Local0)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x020B)
        CopyObject (RefOf (P900), Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x020C)
        CopyObject (RefOf (D900), Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x020D)
        CopyObject (RefOf (P900), Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x020E)
        CopyObject (RefOf (E900), Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x020F)
        CopyObject (RefOf (P900), Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x0210)
        CopyObject (RefOf (M901), Local0)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0211)
        CopyObject (RefOf (P900), Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x0230)
        CopyObject (RefOf (MX90), Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x0231)
        CopyObject (RefOf (P900), Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x0232)
        CopyObject (RefOf (R900), Local0)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x0233)
        CopyObject (RefOf (P900), Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x0234)
        CopyObject (RefOf (PW90), Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x0235)
        CopyObject (RefOf (P900), Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x0236)
        CopyObject (RefOf (PR90), Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x0237)
        CopyObject (RefOf (P900), Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x0238)
        CopyObject (RefOf (TZ90), Local0)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x0239)
        CopyObject (RefOf (P900), Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x023A)
        CopyObject (RefOf (BF90), Local0)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x023B)
        CopyObject (RefOf (P900), Local0)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x023C)
        /*///////////////////// All-(...) after Field Unit */

        CopyObject (RefOf (F900), Local0)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x023D)
        CopyObject (RefOf (F900), Local0)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x023E)
        CopyObject (RefOf (D900), Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x023F)
        CopyObject (RefOf (F900), Local0)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x0240)
        CopyObject (RefOf (E900), Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x0241)
        CopyObject (RefOf (F900), Local0)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x0242)
        CopyObject (RefOf (M901), Local0)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0243)
        CopyObject (RefOf (F900), Local0)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x0244)
        CopyObject (RefOf (MX90), Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x0245)
        CopyObject (RefOf (F900), Local0)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x0246)
        CopyObject (RefOf (R900), Local0)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x0247)
        CopyObject (RefOf (F900), Local0)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x0248)
        CopyObject (RefOf (PW90), Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x0249)
        CopyObject (RefOf (F900), Local0)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x024A)
        CopyObject (RefOf (PR90), Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x024B)
        CopyObject (RefOf (F900), Local0)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x024C)
        CopyObject (RefOf (TZ90), Local0)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x024D)
        CopyObject (RefOf (F900), Local0)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x024E)
        CopyObject (RefOf (BF90), Local0)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x024F)
        CopyObject (RefOf (F900), Local0)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x0250)
        /*///////////////////// All-(...) after Device */

        CopyObject (RefOf (D900), Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x0251)
        CopyObject (RefOf (D900), Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x0252)
        CopyObject (RefOf (E900), Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x0253)
        CopyObject (RefOf (D900), Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x0254)
        CopyObject (RefOf (M901), Local0)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0255)
        CopyObject (RefOf (D900), Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x0256)
        CopyObject (RefOf (MX90), Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x0257)
        CopyObject (RefOf (D900), Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x0258)
        CopyObject (RefOf (R900), Local0)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x0259)
        CopyObject (RefOf (D900), Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x025A)
        CopyObject (RefOf (PW90), Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x025B)
        CopyObject (RefOf (D900), Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x025C)
        CopyObject (RefOf (PR90), Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x025D)
        CopyObject (RefOf (D900), Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x025E)
        CopyObject (RefOf (TZ90), Local0)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x025F)
        CopyObject (RefOf (D900), Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x0260)
        CopyObject (RefOf (BF90), Local0)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x0261)
        CopyObject (RefOf (D900), Local0)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x0262)
        /*///////////////////// All-(...) after Event */

        CopyObject (RefOf (E900), Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x0263)
        CopyObject (RefOf (E900), Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x0264)
        CopyObject (RefOf (M901), Local0)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0265)
        CopyObject (RefOf (E900), Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x0266)
        CopyObject (RefOf (MX90), Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x0267)
        CopyObject (RefOf (E900), Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x0268)
        CopyObject (RefOf (R900), Local0)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x0269)
        CopyObject (RefOf (E900), Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x026A)
        CopyObject (RefOf (PW90), Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x026B)
        CopyObject (RefOf (E900), Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x026C)
        CopyObject (RefOf (PR90), Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x026D)
        CopyObject (RefOf (E900), Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x026E)
        CopyObject (RefOf (TZ90), Local0)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x026F)
        CopyObject (RefOf (E900), Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x0270)
        CopyObject (RefOf (BF90), Local0)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x0271)
        CopyObject (RefOf (E900), Local0)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x0272)
        /*///////////////////// All-(...) after Method */

        CopyObject (RefOf (M901), Local0)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0273)
        CopyObject (RefOf (M901), Local0)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0274)
        CopyObject (RefOf (MX90), Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x0275)
        CopyObject (RefOf (M901), Local0)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0276)
        CopyObject (RefOf (R900), Local0)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x0277)
        CopyObject (RefOf (M901), Local0)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0278)
        CopyObject (RefOf (PW90), Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x0279)
        CopyObject (RefOf (M901), Local0)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x027A)
        CopyObject (RefOf (PR90), Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x027B)
        CopyObject (RefOf (M901), Local0)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x027C)
        CopyObject (RefOf (TZ90), Local0)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x027D)
        CopyObject (RefOf (M901), Local0)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x027E)
        CopyObject (RefOf (BF90), Local0)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x027F)
        CopyObject (RefOf (M901), Local0)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0280)
        /*///////////////////// All-(...) after Mutex */

        CopyObject (RefOf (MX90), Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x0281)
        CopyObject (RefOf (MX90), Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x0282)
        CopyObject (RefOf (R900), Local0)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x0283)
        CopyObject (RefOf (MX90), Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x0284)
        CopyObject (RefOf (PW90), Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x0285)
        CopyObject (RefOf (MX90), Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x0286)
        CopyObject (RefOf (PR90), Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x0287)
        CopyObject (RefOf (MX90), Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x0288)
        CopyObject (RefOf (TZ90), Local0)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x0289)
        CopyObject (RefOf (MX90), Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x028A)
        CopyObject (RefOf (BF90), Local0)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x028B)
        CopyObject (RefOf (MX90), Local0)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x028C)
        /*///////////////////// All-(...) after Operation Region */

        CopyObject (RefOf (R900), Local0)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x028D)
        CopyObject (RefOf (R900), Local0)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x028E)
        CopyObject (RefOf (PW90), Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x028F)
        CopyObject (RefOf (R900), Local0)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x0290)
        CopyObject (RefOf (PR90), Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x0291)
        CopyObject (RefOf (R900), Local0)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x0292)
        CopyObject (RefOf (TZ90), Local0)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x0293)
        CopyObject (RefOf (R900), Local0)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x0294)
        CopyObject (RefOf (BF90), Local0)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x0295)
        CopyObject (RefOf (R900), Local0)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x0296)
        /*///////////////////// All-(...) after Power Resource */

        CopyObject (RefOf (PW90), Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x0297)
        CopyObject (RefOf (PW90), Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x0298)
        CopyObject (RefOf (PR90), Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x0299)
        CopyObject (RefOf (PW90), Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x029A)
        CopyObject (RefOf (TZ90), Local0)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x029B)
        CopyObject (RefOf (PW90), Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x029C)
        CopyObject (RefOf (BF90), Local0)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x029D)
        CopyObject (RefOf (PW90), Local0)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x029E)
        /*///////////////////// All-(...) after Processor */

        CopyObject (RefOf (PR90), Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x029F)
        CopyObject (RefOf (PR90), Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x02A0)
        CopyObject (RefOf (TZ90), Local0)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x02A1)
        CopyObject (RefOf (PR90), Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x02A2)
        CopyObject (RefOf (BF90), Local0)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x02A3)
        CopyObject (RefOf (PR90), Local0)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x02A4)
        /*///////////////////// All-(...) after Thermal Zone */

        CopyObject (RefOf (TZ90), Local0)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x02A5)
        CopyObject (RefOf (BF90), Local0)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x02A6)
        CopyObject (RefOf (TZ90), Local0)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x02A7)
        /*///////////////////// All-(...) after Buffer Field */

        CopyObject (RefOf (BF90), Local0)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x02A8)
        CopyObject (RefOf (BF90), Local0)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x02A9)
    }

    /*
     * Store the result of RefOf/CondRefOf to LocalX
     *
     * The same as m1b4 but Store instead of CopyObject.
     */
    Method (M1B5, 0, Serialized)
    {
        C081 = Z108 /* absolute index of file initiating the checking */ /* \Z108 */
        /* All types */

        Local0 = RefOf (I900)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x02AA)
        Local0 = RefOf (S900)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x02AB)
        Local0 = RefOf (B900)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x02AC)
        Local0 = RefOf (P900)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x02AD)
        Local0 = RefOf (F900)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x02AE)
        Local0 = RefOf (D900)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x02AF)
        Local0 = RefOf (E900)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x02B0)
        Local0 = RefOf (M901)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x02B1)
        Local0 = RefOf (MX90)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x02B2)
        Local0 = RefOf (R900)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x02B3)
        Local0 = RefOf (PW90)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x02B4)
        Local0 = RefOf (PR90)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x02B5)
        Local0 = RefOf (TZ90)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x02B6)
        Local0 = RefOf (BF90)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x02B7)
        /*///////////////////// All after Integer */

        Local0 = RefOf (I900)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x02B8)
        Local0 = RefOf (I900)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x02B9)
        Local0 = RefOf (S900)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x02BA)
        Local0 = RefOf (I900)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x02BB)
        Local0 = RefOf (B900)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x02BC)
        Local0 = RefOf (I900)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x02BD)
        Local0 = RefOf (P900)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x02BE)
        Local0 = RefOf (I900)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x02BF)
        Local0 = RefOf (F900)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x02C0)
        Local0 = RefOf (I900)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x02C1)
        Local0 = RefOf (D900)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x02C2)
        Local0 = RefOf (I900)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x02C3)
        Local0 = RefOf (E900)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x02C4)
        Local0 = RefOf (I900)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x02C5)
        Local0 = RefOf (M901)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x02C6)
        Local0 = RefOf (I900)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x02C7)
        Local0 = RefOf (MX90)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x02C8)
        Local0 = RefOf (I900)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x02C9)
        Local0 = RefOf (R900)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x02CA)
        Local0 = RefOf (I900)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x02CB)
        Local0 = RefOf (PW90)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x02CC)
        Local0 = RefOf (I900)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x02CD)
        Local0 = RefOf (PR90)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x02CE)
        Local0 = RefOf (I900)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x02CF)
        Local0 = RefOf (TZ90)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x02D0)
        Local0 = RefOf (I900)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x02D1)
        Local0 = RefOf (BF90)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x02D2)
        Local0 = RefOf (I900)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x02D3)
        /*///////////////////// All-Integer after String */

        Local0 = RefOf (S900)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x02D4)
        Local0 = RefOf (S900)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x02D5)
        Local0 = RefOf (B900)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x02D6)
        Local0 = RefOf (S900)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x02D7)
        Local0 = RefOf (P900)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x02D8)
        Local0 = RefOf (S900)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x02D9)
        Local0 = RefOf (F900)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x02DA)
        Local0 = RefOf (S900)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x02DB)
        Local0 = RefOf (D900)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x02DC)
        Local0 = RefOf (S900)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x02DD)
        Local0 = RefOf (E900)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x02DE)
        Local0 = RefOf (S900)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x02DF)
        Local0 = RefOf (M901)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x02E0)
        Local0 = RefOf (S900)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x02E1)
        Local0 = RefOf (MX90)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x02E2)
        Local0 = RefOf (S900)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x02E3)
        Local0 = RefOf (R900)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x02E4)
        Local0 = RefOf (S900)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x02E5)
        Local0 = RefOf (PW90)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x02E6)
        Local0 = RefOf (S900)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x02E7)
        Local0 = RefOf (PR90)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x02E8)
        Local0 = RefOf (S900)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x02E9)
        Local0 = RefOf (TZ90)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x02EA)
        Local0 = RefOf (S900)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x02EB)
        Local0 = RefOf (BF90)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x02EC)
        Local0 = RefOf (S900)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x02ED)
        /*///////////////////// All-(Integer+String) after Buffer */

        Local0 = RefOf (B900)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x02EE)
        Local0 = RefOf (B900)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x02EF)
        Local0 = RefOf (P900)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x02F0)
        Local0 = RefOf (B900)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x02F1)
        Local0 = RefOf (F900)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x02F2)
        Local0 = RefOf (B900)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x02F3)
        Local0 = RefOf (D900)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x02F4)
        Local0 = RefOf (B900)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x02F5)
        Local0 = RefOf (E900)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x02F6)
        Local0 = RefOf (B900)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x02F7)
        Local0 = RefOf (M901)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x02F8)
        Local0 = RefOf (B900)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x02F9)
        Local0 = RefOf (MX90)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x02FA)
        Local0 = RefOf (B900)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x02FB)
        Local0 = RefOf (R900)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x02FC)
        Local0 = RefOf (B900)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x02FD)
        Local0 = RefOf (PW90)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x02FE)
        Local0 = RefOf (B900)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x02FF)
        Local0 = RefOf (PR90)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x0300)
        Local0 = RefOf (B900)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x0301)
        Local0 = RefOf (TZ90)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x0302)
        Local0 = RefOf (B900)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x0303)
        Local0 = RefOf (BF90)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x0304)
        Local0 = RefOf (B900)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x0305)
        /*///////////////////// All-(...) after Package */

        Local0 = RefOf (P900)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x0306)
        Local0 = RefOf (P900)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x0307)
        Local0 = RefOf (F900)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x0308)
        Local0 = RefOf (P900)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x0309)
        Local0 = RefOf (D900)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x030A)
        Local0 = RefOf (P900)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x030B)
        Local0 = RefOf (E900)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x030C)
        Local0 = RefOf (P900)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x030D)
        Local0 = RefOf (M901)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x030E)
        Local0 = RefOf (P900)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x030F)
        Local0 = RefOf (MX90)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x0310)
        Local0 = RefOf (P900)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x0311)
        Local0 = RefOf (R900)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x0312)
        Local0 = RefOf (P900)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x0313)
        Local0 = RefOf (PW90)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x0314)
        Local0 = RefOf (P900)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x0315)
        Local0 = RefOf (PR90)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x0316)
        Local0 = RefOf (P900)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x0317)
        Local0 = RefOf (TZ90)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x0318)
        Local0 = RefOf (P900)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x0319)
        Local0 = RefOf (BF90)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x031A)
        Local0 = RefOf (P900)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x031B)
        /*///////////////////// All-(...) after Field Unit */

        Local0 = RefOf (F900)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x031C)
        Local0 = RefOf (F900)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x031D)
        Local0 = RefOf (D900)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x031E)
        Local0 = RefOf (F900)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x031F)
        Local0 = RefOf (E900)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x0320)
        Local0 = RefOf (F900)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x0321)
        Local0 = RefOf (M901)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0322)
        Local0 = RefOf (F900)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x0323)
        Local0 = RefOf (MX90)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x0324)
        Local0 = RefOf (F900)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x0325)
        Local0 = RefOf (R900)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x0326)
        Local0 = RefOf (F900)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x0327)
        Local0 = RefOf (PW90)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x0328)
        Local0 = RefOf (F900)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x0329)
        Local0 = RefOf (PR90)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x032A)
        Local0 = RefOf (F900)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x032B)
        Local0 = RefOf (TZ90)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x032C)
        Local0 = RefOf (F900)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x032D)
        Local0 = RefOf (BF90)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x032E)
        Local0 = RefOf (F900)
        M1A3 (Local0, C00D, Z108, __METHOD__, 0x032F)
        /*///////////////////// All-(...) after Device */

        Local0 = RefOf (D900)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x0330)
        Local0 = RefOf (D900)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x0331)
        Local0 = RefOf (E900)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x0332)
        Local0 = RefOf (D900)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x0333)
        Local0 = RefOf (M901)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0334)
        Local0 = RefOf (D900)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x0335)
        Local0 = RefOf (MX90)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x0336)
        Local0 = RefOf (D900)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x0337)
        Local0 = RefOf (R900)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x0338)
        Local0 = RefOf (D900)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x0339)
        Local0 = RefOf (PW90)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x033A)
        Local0 = RefOf (D900)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x033B)
        Local0 = RefOf (PR90)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x033C)
        Local0 = RefOf (D900)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x033D)
        Local0 = RefOf (TZ90)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x033E)
        Local0 = RefOf (D900)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x033F)
        Local0 = RefOf (BF90)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x0340)
        Local0 = RefOf (D900)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x0341)
        /*///////////////////// All-(...) after Event */

        Local0 = RefOf (E900)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x0342)
        Local0 = RefOf (E900)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x0343)
        Local0 = RefOf (M901)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0344)
        Local0 = RefOf (E900)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x0345)
        Local0 = RefOf (MX90)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x0346)
        Local0 = RefOf (E900)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x0347)
        Local0 = RefOf (R900)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x0348)
        Local0 = RefOf (E900)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x0349)
        Local0 = RefOf (PW90)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x034A)
        Local0 = RefOf (E900)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x034B)
        Local0 = RefOf (PR90)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x034C)
        Local0 = RefOf (E900)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x034D)
        Local0 = RefOf (TZ90)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x034E)
        Local0 = RefOf (E900)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x034F)
        Local0 = RefOf (BF90)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x0350)
        Local0 = RefOf (E900)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x0351)
        /*///////////////////// All-(...) after Method */

        Local0 = RefOf (M901)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0352)
        Local0 = RefOf (M901)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0353)
        Local0 = RefOf (MX90)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x0354)
        Local0 = RefOf (M901)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0355)
        Local0 = RefOf (R900)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x0356)
        Local0 = RefOf (M901)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0357)
        Local0 = RefOf (PW90)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x03BC)
        Local0 = RefOf (M901)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0359)
        Local0 = RefOf (PR90)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x035A)
        Local0 = RefOf (M901)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x035B)
        Local0 = RefOf (TZ90)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x035C)
        Local0 = RefOf (M901)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x035D)
        Local0 = RefOf (BF90)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x035E)
        Local0 = RefOf (M901)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x035F)
        /*///////////////////// All-(...) after Mutex */

        Local0 = RefOf (MX90)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x0360)
        Local0 = RefOf (MX90)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x0361)
        Local0 = RefOf (R900)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x0362)
        Local0 = RefOf (MX90)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x0363)
        Local0 = RefOf (PW90)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x0364)
        Local0 = RefOf (MX90)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x0365)
        Local0 = RefOf (PR90)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x0366)
        Local0 = RefOf (MX90)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x0367)
        Local0 = RefOf (TZ90)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x0368)
        Local0 = RefOf (MX90)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x0369)
        Local0 = RefOf (BF90)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x036A)
        Local0 = RefOf (MX90)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x036B)
        /*///////////////////// All-(...) after Operation Region */

        Local0 = RefOf (R900)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x036C)
        Local0 = RefOf (R900)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x036D)
        Local0 = RefOf (PW90)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x036E)
        Local0 = RefOf (R900)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x036F)
        Local0 = RefOf (PR90)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x0370)
        Local0 = RefOf (R900)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x0371)
        Local0 = RefOf (TZ90)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x0372)
        Local0 = RefOf (R900)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x0373)
        Local0 = RefOf (BF90)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x0374)
        Local0 = RefOf (R900)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x0375)
        /*///////////////////// All-(...) after Power Resource */

        Local0 = RefOf (PW90)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x0376)
        Local0 = RefOf (PW90)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x0377)
        Local0 = RefOf (PR90)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x0378)
        Local0 = RefOf (PW90)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x0379)
        Local0 = RefOf (TZ90)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x037A)
        Local0 = RefOf (PW90)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x037B)
        Local0 = RefOf (BF90)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x037C)
        Local0 = RefOf (PW90)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x037D)
        /*///////////////////// All-(...) after Processor */

        Local0 = RefOf (PR90)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x037E)
        Local0 = RefOf (PR90)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x037F)
        Local0 = RefOf (TZ90)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x0380)
        Local0 = RefOf (PR90)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x0381)
        Local0 = RefOf (BF90)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x0382)
        Local0 = RefOf (PR90)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x0383)
        /*///////////////////// All-(...) after Thermal Zone */

        Local0 = RefOf (TZ90)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x0384)
        Local0 = RefOf (BF90)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x0385)
        Local0 = RefOf (TZ90)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x0386)
        /*///////////////////// All-(...) after Buffer Field */

        Local0 = RefOf (BF90)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x0387)
        Local0 = RefOf (BF90)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x0388)
    }

    /* CopyObject the result of Index to LocalX */

    Method (M1B6, 0, Serialized)
    {
        C081 = Z108 /* absolute index of file initiating the checking */ /* \Z108 */
        /* Computational Data */

        CopyObject (Local0 = S900 [0x01], Local1)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x0389)
        M1A3 (Local1, C016, Z108, __METHOD__, 0x038A)
        CopyObject (Local0 = B900 [0x01], Local1)
        M1A3 (Local0, C016, Z108, __METHOD__, 0x038B)
        M1A3 (Local1, C016, Z108, __METHOD__, 0x038C)
        /* Elements of Package are Uninitialized */

        If (Y127)
        {
            CopyObject (Local0 = P900 [0x00], Local1)
            M1A3 (Local0, C008, Z108, __METHOD__, 0x038D)
            M1A3 (Local1, C008, Z108, __METHOD__, 0x038E)
        }

        /* Elements of Package are Computational Data */

        CopyObject (Local0 = P901 [0x01], Local1)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x038F)
        M1A3 (Local1, C009, Z108, __METHOD__, 0x0390)
        CopyObject (Local0 = P904 [0x01], Local1)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x0391)
        M1A3 (Local1, C00B, Z108, __METHOD__, 0x0392)
        CopyObject (Local0 = P905 [0x00], Local1)
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x0393)
        M1A3 (Local1, C00C, Z108, __METHOD__, 0x0394)
        CopyObject (Local0 = P90D [0x00], Local1)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x0395)
        M1A3 (Local1, C009, Z108, __METHOD__, 0x0396)
        CopyObject (Local0 = P90E [0x00], Local1)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x0397)
        M1A3 (Local1, C009, Z108, __METHOD__, 0x0398)
        CopyObject (Local0 = P90F [0x00], Local1)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x0399)
        M1A3 (Local1, C00A, Z108, __METHOD__, 0x039A)
        CopyObject (Local0 = P910 [0x00], Local1)
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x039B)
        M1A3 (Local1, C00A, Z108, __METHOD__, 0x039C)
        CopyObject (Local0 = P911 [0x00], Local1)
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x039D)
        M1A3 (Local1, C00B, Z108, __METHOD__, 0x039E)
        /* These objects become an integer in a package */

        CopyObject (Local0 = P912 [0x00], Local1)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x039F)
        M1A3 (Local1, C009, Z108, __METHOD__, 0x03A0)
        CopyObject (Local0 = P913 [0x00], Local1)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x03A1)
        M1A3 (Local1, C009, Z108, __METHOD__, 0x03A2)
        CopyObject (Local0 = P914 [0x00], Local1)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x03A3)
        M1A3 (Local1, C009, Z108, __METHOD__, 0x03A4)
        CopyObject (Local0 = P915 [0x00], Local1)
        M1A3 (Local0, C009, Z108, __METHOD__, 0x03A5)
        M1A3 (Local1, C009, Z108, __METHOD__, 0x03A6)
        /* Elements of Package are NOT Computational Data */

        CopyObject (Local0 = P916 [0x00], Local1)
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x03A7)
        M1A3 (Local1, C00E, Z108, __METHOD__, 0x03A8)
        CopyObject (Local0 = P917 [0x00], Local1)
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x03A9)
        M1A3 (Local1, C00F, Z108, __METHOD__, 0x03AA)
        CopyObject (Local0 = P918 [0x00], Local1)
        M1A3 (Local0, C011, Z108, __METHOD__, 0x03AB)
        M1A3 (Local1, C011, Z108, __METHOD__, 0x03AC)
        CopyObject (Local0 = P919 [0x00], Local1)
        M1A3 (Local0, C012, Z108, __METHOD__, 0x03AD)
        M1A3 (Local1, C012, Z108, __METHOD__, 0x03AE)
        CopyObject (Local0 = P91A [0x00], Local1)
        M1A3 (Local0, C013, Z108, __METHOD__, 0x03AF)
        M1A3 (Local1, C013, Z108, __METHOD__, 0x03B0)
        CopyObject (Local0 = P91B [0x00], Local1)
        M1A3 (Local0, C014, Z108, __METHOD__, 0x03B1)
        M1A3 (Local1, C014, Z108, __METHOD__, 0x03B2)
        CopyObject (Local0 = P91C [0x00], Local1)
        M1A3 (Local0, C015, Z108, __METHOD__, 0x03B3)
        M1A3 (Local1, C015, Z108, __METHOD__, 0x03B4)
        /* Elements of Package are Methods */

        CopyObject (Local0 = P91D [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03B5)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03B6)
        CopyObject (Local0 = P91E [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03B7)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03B8)
        CopyObject (Local0 = P91F [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03B9)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03BA)
        CopyObject (Local0 = P920 [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03BB)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03BC)
        CopyObject (Local0 = P921 [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03BD)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03BE)
        CopyObject (Local0 = P922 [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03BF)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03C0)
        CopyObject (Local0 = P923 [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03C1)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03C2)
        CopyObject (Local0 = P924 [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03C3)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03C4)
        CopyObject (Local0 = P925 [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03C5)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03C6)
        CopyObject (Local0 = P926 [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03C7)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03C8)
        CopyObject (Local0 = P927 [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03C9)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03CA)
        CopyObject (Local0 = P928 [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03CB)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03CC)
        CopyObject (Local0 = P929 [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03CD)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03CE)
        CopyObject (Local0 = P92A [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03CF)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03D0)
        CopyObject (Local0 = P92B [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03D1)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03D2)
        CopyObject (Local0 = P92C [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03D3)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03D4)
        CopyObject (Local0 = P92D [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03D5)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03D6)
        CopyObject (Local0 = P92E [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03D7)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03D8)
        CopyObject (Local0 = P92F [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03D9)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03DA)
        CopyObject (Local0 = P930 [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03DB)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03DC)
        CopyObject (Local0 = P931 [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03DD)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03DE)
        CopyObject (Local0 = P932 [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03DF)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03E0)
        CopyObject (Local0 = P933 [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03E1)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03E2)
        CopyObject (Local0 = P934 [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03E3)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03E4)
        CopyObject (Local0 = P935 [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03E5)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03E6)
        CopyObject (Local0 = P936 [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03E7)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03E8)
        CopyObject (Local0 = P937 [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03E9)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03EA)
        CopyObject (Local0 = P938 [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03EB)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03EC)
        CopyObject (Local0 = P939 [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03ED)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03EE)
        CopyObject (Local0 = P93A [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03EF)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03F0)
        CopyObject (Local0 = P93B [0x00], Local1)
        M1A3 (Local0, C010, Z108, __METHOD__, 0x03F1)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x03F2)
        M1A6 ()
    }

    /* Store the result of Index to LocalX. */
    /* */
    /* The same as m1b6 but Store instead of CopyObject. */
    Method (M1B7, 0, Serialized)
    {
        C081 = Z108 /* absolute index of file initiating the checking */ /* \Z108 */
        /* Computational Data */

        Local1 = Local0 = S900 [0x01]
        M1A3 (Local0, C016, Z108, __METHOD__, 0x03F3)
        M1A3 (Local1, C016, Z108, __METHOD__, 0x03F4)
        Local1 = Local0 = B900 [0x01]
        M1A3 (Local0, C016, Z108, __METHOD__, 0x03F5)
        M1A3 (Local1, C016, Z108, __METHOD__, 0x03F6)
        /* Elements of Package are Uninitialized */

        Local1 = Local0 = P900 [0x00]
        M1A3 (Local0, C008, Z108, __METHOD__, 0x03F7)
        M1A3 (Local1, C008, Z108, __METHOD__, 0x03F8)
        /* Elements of Package are Computational Data */

        Local1 = Local0 = P901 [0x01]
        M1A3 (Local0, C009, Z108, __METHOD__, 0x03F9)
        M1A3 (Local1, C009, Z108, __METHOD__, 0x03FA)
        Local1 = Local0 = P904 [0x01]
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x03FB)
        M1A3 (Local1, C00B, Z108, __METHOD__, 0x03FC)
        Local1 = Local0 = P905 [0x00]
        M1A3 (Local0, C00C, Z108, __METHOD__, 0x03FD)
        M1A3 (Local1, C00C, Z108, __METHOD__, 0x03FE)
        Local1 = Local0 = P90D [0x00]
        M1A3 (Local0, C009, Z108, __METHOD__, 0x03FF)
        M1A3 (Local1, C009, Z108, __METHOD__, 0x0400)
        Local1 = Local0 = P90E [0x00]
        M1A3 (Local0, C009, Z108, __METHOD__, 0x0401)
        M1A3 (Local1, C009, Z108, __METHOD__, 0x0402)
        Local1 = Local0 = P90F [0x00]
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x0403)
        M1A3 (Local1, C00A, Z108, __METHOD__, 0x0404)
        Local1 = Local0 = P910 [0x00]
        M1A3 (Local0, C00A, Z108, __METHOD__, 0x0405)
        M1A3 (Local1, C00A, Z108, __METHOD__, 0x0406)
        Local1 = Local0 = P911 [0x00]
        M1A3 (Local0, C00B, Z108, __METHOD__, 0x0407)
        M1A3 (Local1, C00B, Z108, __METHOD__, 0x0408)
        /* These objects become an integer in a package */

        Local1 = Local0 = P912 [0x00]
        M1A3 (Local0, C009, Z108, __METHOD__, 0x0409)
        M1A3 (Local1, C009, Z108, __METHOD__, 0x040A)
        Local1 = Local0 = P913 [0x00]
        M1A3 (Local0, C009, Z108, __METHOD__, 0x040B)
        M1A3 (Local1, C009, Z108, __METHOD__, 0x040C)
        Local1 = Local0 = P914 [0x00]
        M1A3 (Local0, C009, Z108, __METHOD__, 0x040D)
        M1A3 (Local1, C009, Z108, __METHOD__, 0x040E)
        Local1 = Local0 = P915 [0x00]
        M1A3 (Local0, C009, Z108, __METHOD__, 0x040F)
        M1A3 (Local1, C009, Z108, __METHOD__, 0x0410)
        /* Elements of Package are NOT Computational Data */

        Local1 = Local0 = P916 [0x00]
        M1A3 (Local0, C00E, Z108, __METHOD__, 0x0411)
        M1A3 (Local1, C00E, Z108, __METHOD__, 0x0412)
        Local1 = Local0 = P917 [0x00]
        M1A3 (Local0, C00F, Z108, __METHOD__, 0x0413)
        M1A3 (Local1, C00F, Z108, __METHOD__, 0x0414)
        Local1 = Local0 = P918 [0x00]
        M1A3 (Local0, C011, Z108, __METHOD__, 0x0415)
        M1A3 (Local1, C011, Z108, __METHOD__, 0x0416)
        Local1 = Local0 = P919 [0x00]
        M1A3 (Local0, C012, Z108, __METHOD__, 0x0417)
        M1A3 (Local1, C012, Z108, __METHOD__, 0x0418)
        Local1 = Local0 = P91A [0x00]
        M1A3 (Local0, C013, Z108, __METHOD__, 0x0419)
        M1A3 (Local1, C013, Z108, __METHOD__, 0x041A)
        Local1 = Local0 = P91B [0x00]
        M1A3 (Local0, C014, Z108, __METHOD__, 0x041B)
        M1A3 (Local1, C014, Z108, __METHOD__, 0x041C)
        Local1 = Local0 = P91C [0x00]
        M1A3 (Local0, C015, Z108, __METHOD__, 0x041D)
        M1A3 (Local1, C015, Z108, __METHOD__, 0x041E)
        /* Elements of Package are Methods */

        Local1 = Local0 = P91D [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x041F)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x0420)
        Local1 = Local0 = P91E [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0421)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x0422)
        Local1 = Local0 = P91F [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0423)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x0424)
        Local1 = Local0 = P920 [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0425)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x0426)
        Local1 = Local0 = P921 [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0427)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x0428)
        Local1 = Local0 = P922 [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0429)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x042A)
        Local1 = Local0 = P923 [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x042B)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x042C)
        Local1 = Local0 = P924 [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x042D)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x042E)
        Local1 = Local0 = P925 [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x042F)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x0430)
        Local1 = Local0 = P926 [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0431)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x0432)
        Local1 = Local0 = P927 [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0433)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x0434)
        Local1 = Local0 = P928 [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0435)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x0436)
        Local1 = Local0 = P929 [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0437)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x0438)
        Local1 = Local0 = P92A [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0439)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x043A)
        Local1 = Local0 = P92B [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x043B)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x043C)
        Local1 = Local0 = P92C [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x043D)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x043E)
        Local1 = Local0 = P92D [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x043F)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x0440)
        Local1 = Local0 = P92E [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0441)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x0442)
        Local1 = Local0 = P92F [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0443)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x0444)
        Local1 = Local0 = P930 [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0445)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x0446)
        Local1 = Local0 = P931 [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0447)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x0448)
        Local1 = Local0 = P932 [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0449)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x044A)
        Local1 = Local0 = P933 [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x044B)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x044C)
        Local1 = Local0 = P934 [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x044D)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x044E)
        Local1 = Local0 = P935 [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x044F)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x0450)
        Local1 = Local0 = P936 [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0451)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x0452)
        Local1 = Local0 = P937 [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0453)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x0454)
        Local1 = Local0 = P938 [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0455)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x0456)
        Local1 = Local0 = P939 [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0457)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x0458)
        Local1 = Local0 = P93A [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x0459)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x045A)
        Local1 = Local0 = P93B [0x00]
        M1A3 (Local0, C010, Z108, __METHOD__, 0x045B)
        M1A3 (Local1, C010, Z108, __METHOD__, 0x045C)
        M1A6 ()
    }

    Method (M1C0, 0, NotSerialized)
    {
        C081 = Z108       /* absolute index of file initiating the checking */ /* \Z108 */
        C089 = 0x00      /* flag of Reference, object otherwise */
        M1B0 ()
    }
