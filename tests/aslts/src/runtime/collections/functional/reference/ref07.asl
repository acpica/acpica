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
     * References
     *
     * TEST, Package total
     */
    Name (Z116, 0x74)
    /*
     * Flags and values used by m1c3
     */
    Name (FL00, 0x00) /* flag of testing of exceptions */
    Name (V000, 0x00) /* type of the Standard Data object */
    Name (V001, 0x00) /* index of element of Package */
    /*
     * Read immediate image element of Package
     *
     * Package specified by the immediate
     * images {Integer, String, Buffer, Package}.
     * Perform all the ways reading element of
     * Package passed by ArgX.
     */
    Method (M1C1, 0, Serialized)
    {
        Name (PPP0, Package (0x04)
        {
            0x77, 
            "qwer0000", 
            Buffer (0x04)
            {
                 0x01, 0x77, 0x03, 0x04                           // .w..
            }, 

            Package (0x03)
            {
                0x05, 
                0x77, 
                0x07
            }
        })
        FL00 = 0x00    /* flag of testing of exceptions */
        V000 = C009 /* type of the Standard Data object */ /* \C009 */
        V001 = 0x00    /* index of element of Package */
        M1C3 (PPP0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
        V000 = C00A /* type of the Standard Data object */ /* \C00A */
        V001 = 0x01    /* index of element of Package */
        M1C3 (PPP0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
        V000 = C00B /* type of the Standard Data object */ /* \C00B */
        V001 = 0x02    /* index of element of Package */
        M1C3 (PPP0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
        V000 = C00C /* type of the Standard Data object */ /* \C00C */
        V001 = 0x03    /* index of element of Package */
        M1C3 (PPP0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
    }

    /*
     * Read NamedX element of Package
     * {Integer, String, Buffer, Package}.
     */
    Method (M1C2, 0, Serialized)
    {
        Name (TS, "m1c2")
        Name (I000, 0x77)
        Name (S000, "qwer0000")
        Name (B000, Buffer (0x04)
        {
             0x01, 0x77, 0x03, 0x04                           // .w..
        })
        Name (P000, Package (0x03)
        {
            0x05, 
            0x77, 
            0x07
        })
        Name (PPP0, Package (0x04)
        {
            I000, 
            S000, 
            B000, 
            P000
        })
        FL00 = 0x00    /* flag of testing of exceptions */
        V000 = C009 /* type of the Standard Data object */ /* \C009 */
        V001 = 0x00    /* index of element of Package */
        M1C3 (PPP0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
        V000 = C00A /* type of the Standard Data object */ /* \C00A */
        V001 = 0x01    /* index of element of Package */
        M1C3 (PPP0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
        V000 = C00B /* type of the Standard Data object */ /* \C00B */
        V001 = 0x02    /* index of element of Package */
        M1C3 (PPP0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
        V000 = C00C /* type of the Standard Data object */ /* \C00C */
        V001 = 0x03    /* index of element of Package */
        M1C3 (PPP0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
        M380 (TS, I000, 0x00, 0x00)
        M381 (TS, S000, 0x00, 0x01)
        M382 (TS, B000, 0x00, 0x02)
        M383 (TS, P000, 0x00, 0x03)
    }

    /* All the ways reading element of Package given by ArgX */
    /* arg0 - Package */
    /* arg1, */
    /* arg2, */
    /* arg3, */
    /* arg4, */
    /* arg5, */
    /* arg6 - auxiliary, for arbitrary use */
    Method (M1C3, 7, Serialized)
    {
        Name (TS, "m1c3")
        Name (I000, 0x00)
        Name (I001, 0x00)
        Name (I002, 0x00)
        Name (I003, 0x00)
        Name (I004, 0x00)
        Name (I005, 0x00)
        Name (I006, 0x00)
        Name (P000, Package (0x02){})
        Name (PPP0, Package (0x02){})
        /* LocalX */

        Store (Arg0 [V001], Local3)
        M390 (DerefOf (Local3), V000, 0x00, 0x04)
        Local4 = DerefOf (Local3)
        M390 (Local4, V000, 0x00, 0x05)
        M390 (DerefOf (Arg0 [V001]), V000, 0x00, 0x06)
        Local3 = Local2 = Arg0 [V001] /* \V001 */
        M390 (DerefOf (Local3), V000, 0x00, 0x07)
        Local4 = DerefOf (Local3)
        M390 (Local4, V000, 0x00, 0x08)
        M390 (DerefOf (Local2), V000, 0x00, 0x09)
        Local4 = DerefOf (Local2)
        M390 (Local4, V000, 0x00, 0x0A)
        /* ArgX */

        Store (Arg0 [V001], Arg3)
        M390 (DerefOf (Arg3), V000, 0x00, 0x0B)
        Arg4 = DerefOf (Arg3)
        M390 (Arg4, V000, 0x00, 0x0C)
        M390 (DerefOf (Arg0 [V001]), V000, 0x00, 0x0D)
        Arg3 = Arg2 = Arg0 [V001] /* \V001 */
        M390 (DerefOf (Arg3), V000, 0x00, 0x0E)
        Arg4 = DerefOf (Arg3)
        M390 (Arg4, V000, 0x00, 0x0F)
        M390 (DerefOf (Arg2), V000, 0x00, 0x10)
        Arg4 = DerefOf (Arg2)
        M390 (Arg4, V000, 0x00, 0x11)
        /* NamedX */

        If (Y127)
        {
            CopyObject (PPP0 [0x00], I003) /* \M1C3.I003 */
            Store (Arg0 [V001], I003) /* \M1C3.I003 */
            M390 (DerefOf (I003), V000, 0x00, 0x12)
            I004 = DerefOf (I003)
            M390 (I004, V000, 0x00, 0x13)
            M390 (DerefOf (Arg0 [V001]), V000, 0x00, 0x14)
            I003 = I002 = Arg0 [V001] /* \V001 */
            M390 (DerefOf (I003), V000, 0x00, 0x15)
            I004 = DerefOf (I003)
            M390 (I004, V000, 0x00, 0x16)
            M390 (DerefOf (I002), V000, 0x00, 0x17)
            I004 = DerefOf (I002)
            M390 (I004, V000, 0x00, 0x18)
        }

        /*
         * El_of_Package
         *
         * Identical to the first checking, but only
         * store intermediately the references to element
         * of Package arg0 Index(arg0, x) into Index(p000, y)
         * but not into LocalX.
         */
        P000 [0x01] = P000 [0x00] = Arg0 [V001] /* \V001 */
        /* DerefOf(DerefOf(Index(x,Destination))) */

        M390 (DerefOf (DerefOf (P000 [0x00])), V000, 0x00, 0x19)
        /* DerefOf(DerefOf(Index(x,Result))) */

        M390 (DerefOf (DerefOf (P000 [0x01])), V000, 0x00, 0x1A)
        /* El_of_Package, Destination, LocalX */
        /*
         * After Store(Index(p000, 0), Local5)
         * Local5 below - reference to element of
         * Package p000 containing reference to the
         * 0-th element of Arg0-Package.
         *
         * Correspondingly, after Store(DerefOf(Local5), Local3)
         * Local3 - reference to the 0-th element of Arg0-Package.
         *
         * Further, DerefOf(Local3) - 0-th element of Arg0-Package.
         */
        If (FL00)
        {
            Store (P000 [0x00], Local5)
            CH03 (TS, Z116, 0x00, 0xE2, 0x00)
            Local6 = (Local5 + 0x01)
            CH04 (TS, 0x00, 0xFF, Z116, 0xE4, 0x00, 0x00)
            CH03 (TS, Z116, 0x02, 0xE6, 0x00)
            Local6 = (DerefOf (Local5) + 0x01)
            CH04 (TS, 0x00, 0xFF, Z116, 0xE8, 0x00, 0x00)
            CH03 (TS, Z116, 0x04, 0xEA, 0x00)
            M390 (Local5, V000, 0x00, 0x00)
            CH04 (TS, 0x00, 0xFF, Z116, 0xEC, 0x00, 0x00)
            CH03 (TS, Z116, 0x06, 0xEE, 0x00)
            M390 (DerefOf (Local5), V000, 0x00, 0x00)
            CH04 (TS, 0x00, 0xFF, Z116, 0xF0, 0x00, 0x00)
            Local5 = Local2 = P000 [0x00]
            CH03 (TS, Z116, 0x08, 0xF4, 0x00)
            Local6 = (Local5 + 0x01)
            CH04 (TS, 0x00, 0xFF, Z116, 0xF6, 0x00, 0x00)
            CH03 (TS, Z116, 0x0A, 0xF8, 0x00)
            Local6 = (DerefOf (Local5) + 0x01)
            CH04 (TS, 0x00, 0xFF, Z116, 0xFA, 0x00, 0x00)
            CH03 (TS, Z116, 0x0C, 0xFC, 0x00)
            M390 (Local5, V000, 0x00, 0x00)
            CH04 (TS, 0x00, 0xFF, Z116, 0xFE, 0x00, 0x00)
            CH03 (TS, Z116, 0x0E, 0x0100, 0x00)
            M390 (DerefOf (Local5), V000, 0x00, 0x00)
            CH04 (TS, 0x00, 0xFF, Z116, 0x0102, 0x00, 0x00)
            CH03 (TS, Z116, 0x10, 0x0104, 0x00)
            Local6 = (Local2 + 0x01)
            CH04 (TS, 0x00, 0xFF, Z116, 0x0106, 0x00, 0x00)
            CH03 (TS, Z116, 0x12, 0x0108, 0x00)
            Local6 = (DerefOf (Local2) + 0x01)
            CH04 (TS, 0x00, 0xFF, Z116, 0x010A, 0x00, 0x00)
            CH03 (TS, Z116, 0x14, 0x010C, 0x00)
            M390 (Local2, V000, 0x00, 0x00)
            CH04 (TS, 0x00, 0xFF, Z116, 0x010E, 0x00, 0x00)
            CH03 (TS, Z116, 0x16, 0x0110, 0x00)
            M390 (DerefOf (Local2), V000, 0x00, 0x00)
            CH04 (TS, 0x00, 0xFF, Z116, 0x0112, 0x00, 0x00)
        }

        If (Q001)
        {
            Store (P000 [0x00], Local5)
            Local3 = DerefOf (Local5)
            M390 (DerefOf (Local3), V000, 0x00, 0x1B)
            Local4 = DerefOf (Local3)
            M390 (Local4, V000, 0x00, 0x1C)
            Local5 = Local2 = P000 [0x00]
            Local3 = DerefOf (Local5)
            M390 (DerefOf (Local3), V000, 0x00, 0x1D)
            Local4 = DerefOf (Local3)
            M390 (Local4, V000, 0x00, 0x1E)
            Local3 = DerefOf (Local2)
            M390 (DerefOf (Local3), V000, 0x00, 0x1F)
            Local4 = DerefOf (Local3)
            M390 (Local4, V000, 0x00, 0x20)
        }

        /* if(q001) */
        /* El_of_Package, Result, LocalX */
        If (FL00)
        {
            Store (P000 [0x01], Local5)
            CH03 (TS, Z116, 0x18, 0x0131, 0x00)
            Local6 = (Local5 + 0x01)
            CH04 (TS, 0x00, 0xFF, Z116, 0x0133, 0x00, 0x00)
            CH03 (TS, Z116, 0x1A, 0x0135, 0x00)
            Local6 = (DerefOf (Local5) + 0x01)
            CH04 (TS, 0x00, 0xFF, Z116, 0x0137, 0x00, 0x00)
            CH03 (TS, Z116, 0x1C, 0x0139, 0x00)
            M390 (Local5, V000, 0x00, 0x21)
            CH04 (TS, 0x00, 0xFF, Z116, 0x013B, 0x00, 0x00)
            CH03 (TS, Z116, 0x1E, 0x013D, 0x00)
            M390 (DerefOf (Local5), V000, 0x00, 0x22)
            CH04 (TS, 0x00, 0xFF, Z116, 0x013F, 0x00, 0x00)
            Local5 = Local2 = P000 [0x01]
            CH03 (TS, Z116, 0x20, 0x0143, 0x00)
            Local6 = (Local5 + 0x01)
            CH04 (TS, 0x00, 0xFF, Z116, 0x0145, 0x00, 0x00)
            CH03 (TS, Z116, 0x22, 0x0147, 0x00)
            Local6 = (DerefOf (Local5) + 0x01)
            CH04 (TS, 0x00, 0xFF, Z116, 0x0149, 0x00, 0x00)
            CH03 (TS, Z116, 0x24, 0x014B, 0x00)
            M390 (Local5, V000, 0x00, 0x23)
            CH04 (TS, 0x00, 0xFF, Z116, 0x014D, 0x00, 0x00)
            CH03 (TS, Z116, 0x26, 0x014F, 0x00)
            M390 (DerefOf (Local5), V000, 0x00, 0x24)
            CH04 (TS, 0x00, 0xFF, Z116, 0x0151, 0x00, 0x00)
            CH03 (TS, Z116, 0x28, 0x0153, 0x00)
            Local6 = (Local2 + 0x01)
            CH04 (TS, 0x00, 0xFF, Z116, 0x0155, 0x00, 0x00)
            CH03 (TS, Z116, 0x2A, 0x0157, 0x00)
            Local6 = (DerefOf (Local2) + 0x01)
            CH04 (TS, 0x00, 0xFF, Z116, 0x0159, 0x00, 0x00)
            CH03 (TS, Z116, 0x2C, 0x015B, 0x00)
            M390 (Local2, V000, 0x00, 0x25)
            CH04 (TS, 0x00, 0xFF, Z116, 0x015D, 0x00, 0x00)
            CH03 (TS, Z116, 0x2E, 0x015F, 0x00)
            M390 (DerefOf (Local2), V000, 0x00, 0x26)
            CH04 (TS, 0x00, 0xFF, Z116, 0x0161, 0x00, 0x00)
        }

        If (Q001)
        {
            Store (P000 [0x01], Local5)
            Local3 = DerefOf (Local5)
            M390 (DerefOf (Local3), V000, 0x00, 0x27)
            Local4 = DerefOf (Local3)
            M390 (Local4, V000, 0x00, 0x28)
            Local5 = Local2 = P000 [0x01]
            Local3 = DerefOf (Local5)
            M390 (DerefOf (Local3), V000, 0x00, 0x29)
            Local4 = DerefOf (Local3)
            M390 (Local4, V000, 0x00, 0x2A)
            Local3 = DerefOf (Local2)
            M390 (DerefOf (Local3), V000, 0x00, 0x2B)
            Local4 = DerefOf (Local3)
            M390 (Local4, V000, 0x00, 0x2C)
        }

        /* if(q001) */
        /* El_of_Package, Destination, argX */
        If (FL00)
        {
            Store (P000 [0x00], Arg5)
            CH03 (TS, Z116, 0x30, 0x0180, 0x00)
            Arg6 = (Arg5 + 0x01)
            CH04 (TS, 0x00, 0xFF, Z116, 0x0182, 0x00, 0x00)
            CH03 (TS, Z116, 0x32, 0x0184, 0x00)
            Arg6 = (DerefOf (Arg5) + 0x01)
            CH04 (TS, 0x00, 0xFF, Z116, 0x0186, 0x00, 0x00)
            CH03 (TS, Z116, 0x34, 0x0188, 0x00)
            M390 (Arg5, V000, 0x00, 0x2D)
            CH04 (TS, 0x00, 0xFF, Z116, 0x018A, 0x00, 0x00)
            CH03 (TS, Z116, 0x36, 0x018C, 0x00)
            M390 (DerefOf (Arg5), V000, 0x00, 0x2E)
            CH04 (TS, 0x00, 0xFF, Z116, 0x018E, 0x00, 0x00)
            Arg5 = Arg2 = P000 [0x00]
            CH03 (TS, Z116, 0x38, 0x0192, 0x00)
            Arg6 = (Arg5 + 0x01)
            CH04 (TS, 0x00, 0xFF, Z116, 0x0194, 0x00, 0x00)
            CH03 (TS, Z116, 0x3A, 0x0196, 0x00)
            Arg6 = (DerefOf (Arg5) + 0x01)
            CH04 (TS, 0x00, 0xFF, Z116, 0x0198, 0x00, 0x00)
            CH03 (TS, Z116, 0x3C, 0x019A, 0x00)
            M390 (Arg5, V000, 0x00, 0x2F)
            CH04 (TS, 0x00, 0xFF, Z116, 0x019C, 0x00, 0x00)
            CH03 (TS, Z116, 0x3E, 0x019E, 0x00)
            M390 (DerefOf (Arg5), V000, 0x00, 0x30)
            CH04 (TS, 0x00, 0xFF, Z116, 0x01A0, 0x00, 0x00)
            CH03 (TS, Z116, 0x40, 0x01A2, 0x00)
            Arg6 = (Arg2 + 0x01)
            CH04 (TS, 0x00, 0xFF, Z116, 0x01A4, 0x00, 0x00)
            CH03 (TS, Z116, 0x42, 0x01A6, 0x00)
            Arg6 = (DerefOf (Arg2) + 0x01)
            CH04 (TS, 0x00, 0xFF, Z116, 0x01A8, 0x00, 0x00)
            CH03 (TS, Z116, 0x44, 0x01AA, 0x00)
            M390 (Arg2, V000, 0x00, 0x31)
            CH04 (TS, 0x00, 0xFF, Z116, 0x01AC, 0x00, 0x00)
            CH03 (TS, Z116, 0x46, 0x01AE, 0x00)
            M390 (DerefOf (Arg2), V000, 0x00, 0x32)
            CH04 (TS, 0x00, 0xFF, Z116, 0x01B0, 0x00, 0x00)
        }

        If (Q001)
        {
            Store (P000 [0x00], Arg5)
            Arg3 = DerefOf (Arg5)
            M390 (DerefOf (Arg3), V000, 0x00, 0x33)
            Arg4 = DerefOf (Arg3)
            M390 (Arg4, V000, 0x00, 0x34)
            Arg5 = Arg2 = P000 [0x00]
            Arg3 = DerefOf (Arg5)
            M390 (DerefOf (Arg3), V000, 0x00, 0x35)
            Arg4 = DerefOf (Arg3)
            M390 (Arg4, V000, 0x00, 0x36)
            Arg3 = DerefOf (Arg2)
            M390 (DerefOf (Arg3), V000, 0x00, 0x37)
            Arg4 = DerefOf (Arg3)
            M390 (Arg4, V000, 0x00, 0x38)
        }

        /* if(q001) */
        /* El_of_Package, Result, argX */
        If (FL00)
        {
            Store (P000 [0x01], Arg5)
            CH03 (TS, Z116, 0x48, 0x01CF, 0x00)
            Arg6 = (Arg5 + 0x01)
            CH04 (TS, 0x00, 0xFF, Z116, 0x01D1, 0x00, 0x00)
            CH03 (TS, Z116, 0x4A, 0x01D3, 0x00)
            Arg6 = (DerefOf (Arg5) + 0x01)
            CH04 (TS, 0x00, 0xFF, Z116, 0x01D5, 0x00, 0x00)
            CH03 (TS, Z116, 0x4C, 0x01D7, 0x00)
            M390 (Arg5, V000, 0x00, 0x39)
            CH04 (TS, 0x00, 0xFF, Z116, 0x01D9, 0x00, 0x00)
            CH03 (TS, Z116, 0x4E, 0x01DB, 0x00)
            M390 (DerefOf (Arg5), V000, 0x00, 0x3A)
            CH04 (TS, 0x00, 0xFF, Z116, 0x01DD, 0x00, 0x00)
            Arg5 = Arg2 = P000 [0x01]
            CH03 (TS, Z116, 0x50, 0x01E1, 0x00)
            Arg6 = (Arg5 + 0x01)
            CH04 (TS, 0x00, 0xFF, Z116, 0x01E3, 0x00, 0x00)
            CH03 (TS, Z116, 0x52, 0x01E5, 0x00)
            Arg6 = (DerefOf (Arg5) + 0x01)
            CH04 (TS, 0x00, 0xFF, Z116, 0x01E7, 0x00, 0x00)
            CH03 (TS, Z116, 0x54, 0x01E9, 0x00)
            M390 (Arg5, V000, 0x00, 0x3B)
            CH04 (TS, 0x00, 0xFF, Z116, 0x01EB, 0x00, 0x00)
            CH03 (TS, Z116, 0x56, 0x01ED, 0x00)
            M390 (DerefOf (Arg5), V000, 0x00, 0x3C)
            CH04 (TS, 0x00, 0xFF, Z116, 0x01EF, 0x00, 0x00)
            CH03 (TS, Z116, 0x58, 0x01F1, 0x00)
            Arg6 = (Arg2 + 0x01)
            CH04 (TS, 0x00, 0xFF, Z116, 0x01F3, 0x00, 0x00)
            CH03 (TS, Z116, 0x5A, 0x01F5, 0x00)
            Arg6 = (DerefOf (Arg2) + 0x01)
            CH04 (TS, 0x00, 0xFF, Z116, 0x01F7, 0x00, 0x00)
            CH03 (TS, Z116, 0x5C, 0x01F9, 0x00)
            M390 (Arg2, V000, 0x00, 0x3D)
            CH04 (TS, 0x00, 0xFF, Z116, 0x01FB, 0x00, 0x00)
            CH03 (TS, Z116, 0x5E, 0x01FD, 0x00)
            M390 (DerefOf (Arg2), V000, 0x00, 0x3E)
            CH04 (TS, 0x00, 0xFF, Z116, 0x01FF, 0x00, 0x00)
        }

        If (Q001)
        {
            Store (P000 [0x01], Arg5)
            Arg3 = DerefOf (Arg5)
            M390 (DerefOf (Arg3), V000, 0x00, 0x3F)
            Arg4 = DerefOf (Arg3)
            M390 (Arg4, V000, 0x00, 0x40)
            Arg5 = Arg2 = P000 [0x01]
            Arg3 = DerefOf (Arg5)
            M390 (DerefOf (Arg3), V000, 0x00, 0x41)
            Arg4 = DerefOf (Arg3)
            M390 (Arg4, V000, 0x00, 0x42)
            Arg3 = DerefOf (Arg2)
            M390 (DerefOf (Arg3), V000, 0x00, 0x43)
            Arg4 = DerefOf (Arg3)
            M390 (Arg4, V000, 0x00, 0x44)
        }

        /* if(q001) */

        If (Y127)
        {
            /* El_of_Package, Destination, NamedX */

            If (FL00)
            {
                CopyObject (PPP0 [0x00], I005) /* \M1C3.I005 */
                Store (P000 [0x00], I005) /* \M1C3.I005 */
                CH03 (TS, Z116, 0x60, 0x0221, 0x00)
                I006 = (I005 + 0x01)
                CH04 (TS, 0x00, 0xFF, Z116, 0x0223, 0x00, 0x00)
                CH03 (TS, Z116, 0x62, 0x0225, 0x00)
                I006 = (DerefOf (I005) + 0x01)
                CH04 (TS, 0x00, 0xFF, Z116, 0x0227, 0x00, 0x00)
                CH03 (TS, Z116, 0x64, 0x0229, 0x00)
                M390 (I005, V000, 0x00, 0x45)
                CH04 (TS, 0x00, 0xFF, Z116, 0x022B, 0x00, 0x00)
                CH03 (TS, Z116, 0x66, 0x022D, 0x00)
                M390 (DerefOf (I005), V000, 0x00, 0x46)
                CH04 (TS, 0x00, 0xFF, Z116, 0x022F, 0x00, 0x00)
                I005 = I002 = P000 [0x00]
                CH03 (TS, Z116, 0x68, 0x0233, 0x00)
                I006 = (I005 + 0x01)
                CH04 (TS, 0x00, 0xFF, Z116, 0x0235, 0x00, 0x00)
                CH03 (TS, Z116, 0x6A, 0x0237, 0x00)
                I006 = (DerefOf (I005) + 0x01)
                CH04 (TS, 0x00, 0xFF, Z116, 0x0239, 0x00, 0x00)
                CH03 (TS, Z116, 0x6C, 0x023B, 0x00)
                M390 (I005, V000, 0x00, 0x47)
                CH04 (TS, 0x00, 0xFF, Z116, 0x023D, 0x00, 0x00)
                CH03 (TS, Z116, 0x6E, 0x023F, 0x00)
                M390 (DerefOf (I005), V000, 0x00, 0x48)
                CH04 (TS, 0x00, 0xFF, Z116, 0x0241, 0x00, 0x00)
                CH03 (TS, Z116, 0x70, 0x0243, 0x00)
                I006 = (I002 + 0x01)
                CH04 (TS, 0x00, 0xFF, Z116, 0x0245, 0x00, 0x00)
                CH03 (TS, Z116, 0x72, 0x0247, 0x00)
                I006 = (DerefOf (I002) + 0x01)
                CH04 (TS, 0x00, 0xFF, Z116, 0x0249, 0x00, 0x00)
                CH03 (TS, Z116, 0x74, 0x024B, 0x00)
                M390 (I002, V000, 0x00, 0x49)
                CH04 (TS, 0x00, 0xFF, Z116, 0x024D, 0x00, 0x00)
                CH03 (TS, Z116, 0x76, 0x024F, 0x00)
                M390 (DerefOf (I002), V000, 0x00, 0x4A)
                CH04 (TS, 0x00, 0xFF, Z116, 0x0251, 0x00, 0x00)
            }

            If (Q001)
            {
                Store (P000 [0x00], I005) /* \M1C3.I005 */
                I003 = DerefOf (I005)
                M390 (DerefOf (I003), V000, 0x00, 0x4B)
                I004 = DerefOf (I003)
                M390 (I004, V000, 0x00, 0x4C)
                I005 = I002 = P000 [0x00]
                I003 = DerefOf (I005)
                M390 (DerefOf (I003), V000, 0x00, 0x4D)
                I004 = DerefOf (I003)
                M390 (I004, V000, 0x00, 0x4E)
                I003 = DerefOf (I002)
                M390 (DerefOf (I003), V000, 0x00, 0x4F)
                I004 = DerefOf (I003)
                M390 (I004, V000, 0x00, 0x50)
            }

            /* if(q001) */
            /* El_of_Package, Result, NamedX */
            If (FL00)
            {
                Store (P000 [0x01], I005) /* \M1C3.I005 */
                CH03 (TS, Z116, 0x78, 0x0270, 0x00)
                I006 = (I005 + 0x01)
                CH04 (TS, 0x00, 0xFF, Z116, 0x0272, 0x00, 0x00)
                CH03 (TS, Z116, 0x7A, 0x0274, 0x00)
                I006 = (DerefOf (I005) + 0x01)
                CH04 (TS, 0x00, 0xFF, Z116, 0x0276, 0x00, 0x00)
                CH03 (TS, Z116, 0x7C, 0x0278, 0x00)
                M390 (I005, V000, 0x00, 0x51)
                CH04 (TS, 0x00, 0xFF, Z116, 0x027A, 0x00, 0x00)
                CH03 (TS, Z116, 0x7E, 0x027C, 0x00)
                M390 (DerefOf (I005), V000, 0x00, 0x52)
                CH04 (TS, 0x00, 0xFF, Z116, 0x027E, 0x00, 0x00)
                I005 = I002 = P000 [0x01]
                CH03 (TS, Z116, 0x80, 0x0282, 0x00)
                I006 = (I005 + 0x01)
                CH04 (TS, 0x00, 0xFF, Z116, 0x0284, 0x00, 0x00)
                CH03 (TS, Z116, 0x82, 0x0286, 0x00)
                I006 = (DerefOf (I005) + 0x01)
                CH04 (TS, 0x00, 0xFF, Z116, 0x0288, 0x00, 0x00)
                CH03 (TS, Z116, 0x84, 0x028A, 0x00)
                M390 (I005, V000, 0x00, 0x53)
                CH04 (TS, 0x00, 0xFF, Z116, 0x028C, 0x00, 0x00)
                CH03 (TS, Z116, 0x86, 0x028E, 0x00)
                M390 (DerefOf (I005), V000, 0x00, 0x54)
                CH04 (TS, 0x00, 0xFF, Z116, 0x0290, 0x00, 0x00)
                CH03 (TS, Z116, 0x88, 0x0292, 0x00)
                I006 = (I002 + 0x01)
                CH04 (TS, 0x00, 0xFF, Z116, 0x0294, 0x00, 0x00)
                CH03 (TS, Z116, 0x8A, 0x0296, 0x00)
                I006 = (DerefOf (I002) + 0x01)
                CH04 (TS, 0x00, 0xFF, Z116, 0x0298, 0x00, 0x00)
                CH03 (TS, Z116, 0x8C, 0x029A, 0x00)
                M390 (I002, V000, 0x00, 0x55)
                CH04 (TS, 0x00, 0xFF, Z116, 0x029C, 0x00, 0x00)
                CH03 (TS, Z116, 0x8E, 0x029E, 0x00)
                M390 (DerefOf (I002), V000, 0x00, 0x56)
                CH04 (TS, 0x00, 0xFF, Z116, 0x02A0, 0x00, 0x00)
            }

            If (Q001)
            {
                Store (P000 [0x01], I005) /* \M1C3.I005 */
                I003 = DerefOf (I005)
                M390 (DerefOf (I003), V000, 0x00, 0x57)
                I004 = DerefOf (I003)
                M390 (I004, V000, 0x00, 0x58)
                I005 = I002 = P000 [0x01]
                I003 = DerefOf (I005)
                M390 (DerefOf (I003), V000, 0x00, 0x59)
                I004 = DerefOf (I003)
                M390 (I004, V000, 0x00, 0x5A)
                I003 = DerefOf (I002)
                M390 (DerefOf (I003), V000, 0x00, 0x5B)
                I004 = DerefOf (I003)
                M390 (I004, V000, 0x00, 0x5C)
            }
                /* if(q001) */
        }
        /* if(y127) */
    }

    /* Check Uninitialized element of Package */

    Method (M1C4, 0, Serialized)
    {
        Name (PPP0, Package (0x0A)
        {
            0x77, 
            "qwer0000", 
            Buffer (0x04)
            {
                 0x01, 0x77, 0x03, 0x04                           // .w..
            }, 

            Package (0x03)
            {
                0x05, 
                0x77, 
                0x07
            }
        })
        Method (M000, 2, NotSerialized)
        {
            Store (Arg0 [Arg1], Local0)
            M1A3 (Local0, C008, Z116, "m1c4", 0x5D)
        }

        M000 (PPP0, 0x04)
        M000 (PPP0, 0x05)
        M000 (PPP0, 0x06)
        M000 (PPP0, 0x07)
        M000 (PPP0, 0x08)
        M000 (PPP0, 0x09)
    }

    /* The chain of Index_References */

    Method (M1C5, 0, Serialized)
    {
        Name (PPP0, Package (0x04)
        {
            0x77, 
            "qwer0000", 
            Buffer (0x04)
            {
                 0x01, 0x77, 0x03, 0x04                           // .w..
            }, 

            Package (0x03)
            {
                0x05, 
                0x77, 
                0x07
            }
        })
        Name (P000, Package (0x14){})
        Store (PPP0 [0x00], P000 [0x00])
        M390 (DerefOf (DerefOf (P000 [0x00])), C009, Z116, 0x5E)
        If (Q002)
        {
            Store (P000 [0x00], P000 [0x01])
            M390 (DerefOf (DerefOf (DerefOf (P000 [0x01]))), C009, Z116, 0x5F)
            Store (P000 [0x01], P000 [0x02])
            M390 (DerefOf (DerefOf (DerefOf (DerefOf (P000 [0x02])))), C009, Z116, 0x60)
            Store (P000 [0x02], P000 [0x03])
            M390 (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (P000 [0x03]))))), C009, Z116, 
                0x61)
            Store (P000 [0x03], P000 [0x04])
            M390 (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (P000 [0x04])))))), C009, 
                Z116, 0x62)
            Store (P000 [0x04], P000 [0x05])
            M390 (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (P000 [0x05]))))))), 
                C009, Z116, 0x63)
            Store (P000 [0x05], P000 [0x06])
            M390 (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (P000 [0x06]
                )))))))), C009, Z116, 0x64)
            Store (P000 [0x06], P000 [0x07])
            M390 (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (P000 [
                0x07]))))))))), C009, Z116, 0x65)
        }

        M390 (DerefOf (DerefOf (P000 [0x00])), C009, Z116, 0x66)
        If (Q002)
        {
            M390 (DerefOf (DerefOf (DerefOf (P000 [0x01]))), C009, Z116, 0x67)
            M390 (DerefOf (DerefOf (DerefOf (DerefOf (P000 [0x02])))), C009, Z116, 0x68)
            M390 (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (P000 [0x03]))))), C009, Z116, 
                0x69)
            M390 (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (P000 [0x04])))))), C009, 
                Z116, 0x6A)
            M390 (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (P000 [0x05]))))))), 
                C009, Z116, 0x6B)
            M390 (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (P000 [0x06]
                )))))))), C009, Z116, 0x6C)
            M390 (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (DerefOf (P000 [
                0x07]))))))))), C009, Z116, 0x6D)
        }
    }

    /* Access to the Method named object element of Package */
    /* Methods without parameters */
    Method (M1C7, 0, Serialized)
    {
        Name (TS, "m1c7")
        Name (I000, 0x77)
        Method (M000, 0, NotSerialized)
        {
            I000 = 0x00
        }

        Method (M001, 0, NotSerialized)
        {
            I000 = 0x01
            Return (0x12345678)
        }

        Method (M002, 0, NotSerialized)
        {
            I000 = 0x00
        }

        Method (M003, 0, NotSerialized)
        {
            I000 = 0x01
            Return (0x12345678)
        }

        Name (P000, Package (0x0A)
        {
            M000, 
            M001, 
            M002, 
            M003, 
            M000, 
            M001, 
            M002, 
            M003, 
            I000, 
            I000
        })
        Store (P000 [0x00], Local0)
        M1A3 (Local0, C010, Z116, TS, 0x6E)
        Store (P000 [0x01], Local0)
        M1A3 (Local0, C010, Z116, TS, 0x6F)
        Store (P000 [0x02], Local0)
        M1A3 (Local0, C010, Z116, TS, 0x70)
        Store (P000 [0x03], Local0)
        M1A3 (Local0, C010, Z116, TS, 0x71)
        Store (P000 [0x04], Local0)
        M1A3 (Local0, C010, Z116, TS, 0x72)
        Store (P000 [0x05], Local0)
        M1A3 (Local0, C010, Z116, TS, 0x73)
        Store (P000 [0x06], Local0)
        M1A3 (Local0, C010, Z116, TS, 0x74)
        Store (P000 [0x07], Local0)
        M1A3 (Local0, C010, Z116, TS, 0x75)
        Store (P000 [0x08], Local0)
        M1A3 (Local0, C009, Z116, TS, 0x76)
        Store (P000 [0x09], Local0)
        M1A3 (Local0, C009, Z116, TS, 0x77)
        M380 (TS, I000, 0x00, 0x00)
    }

    /* CURRENTLY: compiler failed, Too few arguments (M002 requires X) */
    /* Methods with parameters */
    Method (M1C8, 0, Serialized)
    {
        Name (TS, "m1c8")
        /*
     Name(i000, 0x77)
     Method(m000) {
     Store(0, i000)
     }
     Method(m001) {
     Store(1, i000)
     return (0x12345678)
     }
     Method(m002, 1) {
     Store(arg0, i000)
     Store(0, i000)
     }
     Method(m003, 7) {
     Store(arg0, i000)
     Store(arg1, i000)
     Store(arg2, i000)
     Store(arg3, i000)
     Store(arg4, i000)
     Store(arg5, i000)
     Store(arg6, i000)
     Store(1, i000)
     return (0x12345678)
     }
     Name(p000, Package() {m000, m001, m002, m003,
     m000, m001, m002, m003,
     i000, i000})
     Store(Index(p000, 0), Local0)
     m1a3(Local0, c010, z116, ts, `120)
     Store(Index(p000, 1), Local0)
     m1a3(Local0, c010, z116, ts, 121)
     Store(Index(p000, 2), Local0)
     m1a3(Local0, c010, z116, ts, 122)
     Store(Index(p000, 3), Local0)
     m1a3(Local0, c010, z116, ts, 123)
     Store(Index(p000, 4), Local0)
     m1a3(Local0, c010, z116, ts, 124)
     Store(Index(p000, 5), Local0)
     m1a3(Local0, c010, z116, ts, 125)
     Store(Index(p000, 6), Local0)
     m1a3(Local0, c010, z116, ts, 126)
     Store(Index(p000, 7), Local0)
     m1a3(Local0, c010, z116, ts, 127)
     Store(Index(p000, 8), Local0)
     m1a3(Local0, c009, z116, ts, 128)
     Store(Index(p000, 9), Local0)
     m1a3(Local0, c009, z116, ts, 129)
     m380(ts, i000, 0, 130)
     */
    }

    /* DerefOf of the Method named object element of Package */

    Method (M1C9, 0, Serialized)
    {
        Name (TS, "m1c9")
        Name (I000, 0x77)
        Method (M000, 0, NotSerialized)
        {
            I000 = 0x00
        }

        Method (M001, 0, NotSerialized)
        {
            I000 = 0x01
            Return (0x12345678)
        }

        Method (M002, 0, NotSerialized)
        {
            I000 = 0x00
        }

        Method (M003, 0, NotSerialized)
        {
            I000 = 0x01
            Return (0x12345678)
        }

        Name (P000, Package (0x0A)
        {
            M000, 
            M001, 
            M002, 
            M003, 
            M000, 
            M001, 
            M002, 
            M003, 
            I000, 
            I000
        })
        Store (P000 [0x00], Local0)
        M1A3 (Local0, C010, Z116, TS, 0x83)
        CH03 (TS, Z116, 0x90, 0x03A8, 0x00)
        Local1 = DerefOf (Local0)
        CH04 (TS, 0x00, 0xFF, Z116, 0x03AA, 0x00, 0x00)
        Store (P000 [0x01], Local0)
        M1A3 (Local0, C010, Z116, TS, 0x84)
        CH03 (TS, Z116, 0x92, 0x03AE, 0x00)
        Local1 = DerefOf (Local0)
        CH04 (TS, 0x00, 0xFF, Z116, 0x03B0, 0x00, 0x00)
        Store (P000 [0x02], Local0)
        M1A3 (Local0, C010, Z116, TS, 0x85)
        CH03 (TS, Z116, 0x94, 0x03B4, 0x00)
        Local1 = DerefOf (Local0)
        CH04 (TS, 0x00, 0xFF, Z116, 0x03B6, 0x00, 0x00)
        Store (P000 [0x03], Local0)
        M1A3 (Local0, C010, Z116, TS, 0x86)
        CH03 (TS, Z116, 0x96, 0x03BA, 0x00)
        Local1 = DerefOf (Local0)
        CH04 (TS, 0x00, 0xFF, Z116, 0x03BC, 0x00, 0x00)
        Store (P000 [0x04], Local0)
        M1A3 (Local0, C010, Z116, TS, 0x87)
        CH03 (TS, Z116, 0x98, 0x03C0, 0x00)
        Local1 = DerefOf (Local0)
        CH04 (TS, 0x00, 0xFF, Z116, 0x03C2, 0x00, 0x00)
        Store (P000 [0x05], Local0)
        M1A3 (Local0, C010, Z116, TS, 0x88)
        CH03 (TS, Z116, 0x9A, 0x03C6, 0x00)
        Local1 = DerefOf (Local0)
        CH04 (TS, 0x00, 0xFF, Z116, 0x03C8, 0x00, 0x00)
        Store (P000 [0x06], Local0)
        M1A3 (Local0, C010, Z116, TS, 0x89)
        CH03 (TS, Z116, 0x9C, 0x03CC, 0x00)
        Local1 = DerefOf (Local0)
        CH04 (TS, 0x00, 0xFF, Z116, 0x03CE, 0x00, 0x00)
        Store (P000 [0x07], Local0)
        M1A3 (Local0, C010, Z116, TS, 0x8A)
        CH03 (TS, Z116, 0x9E, 0x03D2, 0x00)
        Local1 = DerefOf (Local0)
        CH04 (TS, 0x00, 0xFF, Z116, 0x03D4, 0x00, 0x00)
        M380 (TS, I000, 0x00, 0x8B)
    }

    /* Size of Package */

    Method (M1CA, 0, Serialized)
    {
        Name (TS, "m1ca")
        Method (M000, 1, Serialized)
        {
            Name (P000, Package (Arg0){})
            CH03 (TS, Z116, 0xA0, 0x03E2, 0x00)
            Store (P000 [Arg0], Local0)
            CH04 (TS, 0x00, 0xFF, Z116, 0x03E4, 0x00, 0x00)
        }

        Method (M001, 1, Serialized)
        {
            Name (P000, Package (Arg0){})
            Name (LPN0, 0x00)
            Name (LPC0, 0x00)
            /* Write each element of Package with its index */

            LPN0 = Arg0
            LPC0 = 0x00
            While (LPN0)
            {
                P000 [LPC0] = LPC0 /* \M1CA.M001.LPC0 */
                LPN0--
                LPC0++
            }

            /* Verify each element of Package */

            LPN0 = Arg0
            LPC0 = 0x00
            While (LPN0)
            {
                Store (P000 [LPC0], Local0)
                Local1 = DerefOf (Local0)
                If ((Local1 != LPC0))
                {
                    ERR (TS, Z116, 0x0402, Z116, 0x00, Local1, LPC0)
                    Break
                }

                LPN0--
                LPC0++
            }
        }

        Method (M003, 0, Serialized)
        {
            Name (P000, Package (0x02){})
            CH03 (TS, Z116, 0xA2, 0x040E, 0x00)
            Store (P000 [0x02], Local0)
            CH04 (TS, 0x00, 0xFF, Z116, 0x0410, 0x00, 0x00)
        }

        Method (M004, 0, Serialized)
        {
            Name (P000, Package (0xFF){})
            CH03 (TS, Z116, 0xA4, 0x0417, 0x00)
            Store (P000 [0xFF], Local0)
            CH04 (TS, 0x00, 0xFF, Z116, 0x0419, 0x00, 0x00)
        }

        /* Size not greater than 255 */

        M000 (0x01)
        M000 (0x08)
        M000 (0x7F)
        M000 (0xFF)
        M003 ()
        M004 ()
        /* VarPackage: size of Package greater than 255 */
        /* (bug 129, not a bug) */
        M001 (0x0100)
    }

    /* Size of Package, see comma "6,})" */

    Method (M1CB, 0, Serialized)
    {
        Name (TS, "m1cb")
        Name (P000, Package (0x06)
        {
            0x01, 
            0x02, 
            0x03, 
            0x04, 
            0x05, 
            0x06
        })
        Local0 = SizeOf (P000)
        If ((Local0 != 0x06))
        {
            ERR (TS, Z116, 0x0435, 0x00, 0x00, Local0, 0x06)
        }
    }

    /* Check the read automatic dereference */
    /* arg0 - name of Method initiating the checking */
    /* arg1 - Oref or IRef */
    /* arg2 - expected value */
    /* arg3 - exception is expected */
    Method (M1CC, 4, NotSerialized)
    {
        CH03 (Arg0, Z116, 0xA6, 0x0440, 0x00)
        Local0 = Arg1
        Local7 = (Local0 + 0x01)
        If ((Local7 != Arg2))
        {
            ERR (Arg0, Z116, 0x0446, 0x00, 0x00, Local7, Arg2)
        }

        CH03 (Arg0, Z116, 0xA7, 0x0449, 0x00)
    }

    /* Check the read automatic dereference */
    /* arg0 - name of Method initiating the checking */
    /* arg1 - Oref or IRef */
    /* arg2 - expected value */
    /* arg3 - exception is expected */
    Method (M1CD, 4, NotSerialized)
    {
        CH03 (Arg0, Z116, 0xA8, 0x0453, 0x00)
        Local7 = (Arg1 + 0x01)
        If ((Local7 != Arg2))
        {
            ERR (Arg0, Z116, 0x0458, 0x00, 0x00, Local7, Arg2)
        }

        CH03 (Arg0, Z116, 0xA9, 0x045B, 0x00)
    }

    /* Check the read automatic dereference */
    /* when accessing element of Package. */
    Method (M1CE, 0, Serialized)
    {
        Name (TS, "m1ce")
        Name (P000, Package (0x01)
        {
            0x77
        })
        M1CC (TS, Local0 = P000 [0x00], 0x78, 0x00)
        M1CD (TS, P000 [0x00], 0x78, 0x00)
    }

    Method (M1CF, 0, Serialized)
    {
        Name (TS, "m1cf")
        Name (P000, Package (0x01)
        {
            0x77
        })
        Local0 = P000 [0x00]
        M1CC (TS, Local0, 0x78, 0x00)
        M1CD (TS, Local0, 0x78, 0x00)
        Local1 = Local0 = P000 [0x00]
        M1CC (TS, Local0, 0x78, 0x00)
        M1CD (TS, Local0, 0x78, 0x00)
        M1CC (TS, Local1, 0x78, 0x00)
        M1CD (TS, Local1, 0x78, 0x00)
    }

    Method (M1D0, 0, Serialized)
    {
        Name (TS, "m1d0")
        Name (P000, Package (0x01)
        {
            0x77
        })
        CopyObject (Local0 = P000 [0x00], Local1)
        M1CC (TS, Local0, 0x78, 0x00)
        M1CD (TS, Local0, 0x78, 0x00)
        M1CC (TS, Local1, 0x78, 0x00)
        M1CD (TS, Local1, 0x78, 0x00)
    }

    /* EXCEPTIONS */
    /* ref07.asl 1093: Add(Index(p000, 0, Local0), 1, Local7) */
    /* Error 1035 -    Invalid type ^  ([Reference] found, */
    /*                   Add operator requires [Integer|String|Buffer]) */
    /*
     * Method(m1d1)
     * {
     *	Name(p000, Package(1) {0x77})
     *	CH03(ts, z116, 170, __LINE__, 0)
     *	Add(Index(p000, 0, Local0), 1, Local7)
     *	CH04(ts, 0, 0xff, z116, __LINE__, 0, 0)
     * }
     */
    /* LocalX */
    Method (M1D1, 0, Serialized)
    {
        Name (TS, "m1d1")
        Name (P000, Package (0x01)
        {
            0x77
        })
        Local1 = Local0 = P000 [0x00]
        CH03 (TS, Z116, 0xAC, 0x04A6, 0x00)
        Local7 = (Local0 + 0x01)
        CH04 (TS, 0x00, 0xFF, Z116, 0x04AA, 0x00, 0x00)
        Local7 = (Local1 + 0x01)
        CH04 (TS, 0x00, 0xFF, Z116, 0x04AE, 0x00, 0x00)
    }

    Method (M1D2, 0, Serialized)
    {
        Name (TS, "m1d2")
        Name (P000, Package (0x01)
        {
            0x77
        })
        CopyObject (Local0 = P000 [0x00], Local1)
        CH03 (TS, Z116, 0xAF, 0x04B9, 0x00)
        Local7 = (Local0 + 0x01)
        CH04 (TS, 0x00, 0xFF, Z116, 0x04BD, 0x00, 0x00)
        Local7 = (Local1 + 0x01)
        CH04 (TS, 0x00, 0xFF, Z116, 0x04C1, 0x00, 0x00)
    }

    /* ArgX */

    Method (M1D3, 2, Serialized)
    {
        Name (TS, "m1d3")
        Name (P000, Package (0x01)
        {
            0x77
        })
        Arg1 = Arg0 = P000 [0x00]
        CH03 (TS, Z116, 0xB2, 0x04CE, 0x00)
        Local7 = (Arg0 + 0x01)
        CH04 (TS, 0x00, 0xFF, Z116, 0x04D2, 0x00, 0x00)
        Local7 = (Arg1 + 0x01)
        CH04 (TS, 0x00, 0xFF, Z116, 0x04D6, 0x00, 0x00)
    }

    Method (M1D4, 2, Serialized)
    {
        Name (TS, "m1d4")
        Name (P000, Package (0x01)
        {
            0x77
        })
        CopyObject (Arg0 = P000 [0x00], Arg1)
        CH03 (TS, Z116, 0xB5, 0x04E1, 0x00)
        Local7 = (Arg0 + 0x01)
        CH04 (TS, 0x00, 0xFF, Z116, 0x04E5, 0x00, 0x00)
        /* Type of Arg1 should be IRef here, */
        /* so, exception is expected. */
        Local7 = (Arg1 + 0x01)
        CH04 (TS, 0x00, 0xFF, Z116, 0x04EC, 0x00, 0x00)
    }

    /* NamedX */

    Method (M1D5, 0, Serialized)
    {
        Name (TS, "m1d5")
        Name (I001, 0x00)
        Name (P000, Package (0x02)
        {
            0x77, 
            0x88
        })
        Name (SW00, 0x01)
        Name (HG00, 0x00) /* if non-zero - the test hangs */
        Name (HG01, 0x00) /* if non-zero - the test hangs */
        Name (HG02, 0x00) /* if non-zero - the test hangs */
        CH03 (TS, Z116, 0xB8, 0x04FD, 0x00)
        CopyObject (Local0 = P000 [0x01], I001) /* \M1D5.I001 */
        CH03 (TS, Z116, 0xB9, 0x0501, 0x00)
        /* Type of i001 should be already IRef here, */
        /* so, don't expect exception. */
        I001 = Local0 = P000 [0x00]
        CH03 (TS, Z116, 0xBA, 0x0508, 0x00)
        Local7 = (Local0 + 0x01)
        If (Y248)
        {
            HG00 = 0x01
            HG01 = 0x01
            HG02 = 0x01
        }

        /*
         * To show visually the consequences of the anomaly
         * run one of code below. They cause hang.
         */
        If (HG00)
        {
            /* Infinite loop of printing */

            Local1 = 0x00
            Debug = Local0
        }

        If (HG01)
        {
            /* Infinite loop of printing */

            Debug = Local0
            Debug = Local0
        }

        If (HG02)
        {
            Local1 = 0x00
            Debug = "============== sit 2:"
            Local7 = ObjectType (Local0)
            Debug = Local7
        }

        CH04 (TS, 0x00, 0xFF, Z116, 0x0529, 0x00, 0x00)
        Local7 = (I001 + 0x01)
        CH04 (TS, 0x00, 0xFF, Z116, 0x052D, 0x00, 0x00)
        /*
         * Looks identical to b248: "Incorrect ReferenceCount on Switch operation":
         *
         * Reference count of Local0 is mistakenly zeroed there too.
         *
         * [ACPI Debug]  String: [0x0F] "<-------- 0000>"
         * [ACPI Debug]  Reference: [Debug]
         * [ACPI Debug]  String: [0x0F] "<-------- 1111>"
         *
         * [ACPI Debug]  String: [0x0F] "<-------- 0000>"
         * [ACPI Debug]  [ACPI Debug]  String: [0x0F] "<-------- 1111>"
         */
        Debug = "<-------- 0000>"
        Debug = Local0
        Debug = "<-------- 1111>"
    }

    Method (M1D6, 0, Serialized)
    {
        Name (TS, "m1d6")
        Name (I001, 0x00)
        Name (P000, Package (0x01)
        {
            0x77
        })
        CH03 (TS, Z116, 0xBD, 0x0548, 0x00)
        CopyObject (Local0 = P000 [0x00], I001) /* \M1D6.I001 */
        CH03 (TS, Z116, 0xBE, 0x054C, 0x00)
        Local7 = (I001 + 0x01)
        CH04 (TS, 0x00, 0xFF, Z116, 0x0550, 0x00, 0x00)
    }

    /* Out of Package */

    Method (M1D7, 0, Serialized)
    {
        Name (TS, "m1d7")
        Name (P000, Package (0x01)
        {
            0x77
        })
        CH03 (TS, Z116, 0xC1, 0x055B, 0x00)
        Store (P000 [0x01], Local0)
        CH04 (TS, 0x00, 0xFF, Z116, 0x055F, 0x00, 0x00)
        Local1 = Local0 = P000 [0x01]
        CH04 (TS, 0x00, 0xFF, Z116, 0x0563, 0x00, 0x00)
    }

    Method (M1D8, 0, Serialized)
    {
        Name (TS, "m1d8")
        Name (P000, Package (0x01)
        {
            0x77
        })
        CH03 (TS, Z116, 0xC4, 0x056C, 0x00)
        CopyObject (P000 [0x01], Local0)
        CH04 (TS, 0x00, 0xFF, Z116, 0x0570, 0x00, 0x00)
        CopyObject (Local0 = P000 [0x01], Local1)
        CH04 (TS, 0x00, 0xFF, Z116, 0x0574, 0x00, 0x00)
    }

    Method (M1DB, 0, Serialized)
    {
        Name (TS, "m1db")
        Name (I001, 0x00)
        Name (P000, Package (0x02)
        {
            0x77, 
            0x88
        })
        CH03 (TS, Z116, 0xC7, 0x057F, 0x00)
        CopyObject (P000 [0x01], I001) /* \M1DB.I001 */
        CH03 (TS, Z116, 0xC8, 0x0583, 0x00)
        /* Type of i001 should be already IRef here, */
        /* so, don't expect exception. Writing to i001 */
        /* is here identical to Store into it. */
        I001 = P000 [0x00]
        CH03 (TS, Z116, 0xC9, 0x058B, 0x00)
        Local7 = (I001 + 0x01)
        CH04 (TS, 0x00, 0xFF, Z116, 0x058F, 0x00, 0x00)
    }

    /* WRITE */

    Method (M1D9, 0, Serialized)
    {
        Name (P000, Package (0x03)
        {
            0x05, 
            0x00, 
            0x07
        })
        Method (M000, 1, NotSerialized)
        {
            Local0 = (0x76 + 0x01)
            Arg0 = Local0
        }

        M000 (P000 [0x01])
        M383 ("m1d9", P000, Z116, 0x8C)
    }

    Method (M1DA, 0, Serialized)
    {
        Name (P000, Package (0x03)
        {
            0x05, 
            0x00, 
            0x07
        })
        Method (M000, 1, NotSerialized)
        {
            Arg0 = (0x76 + 0x01)
        }

        M000 (P000 [0x01])
        M383 ("m1da", P000, Z116, 0x8D)
    }

