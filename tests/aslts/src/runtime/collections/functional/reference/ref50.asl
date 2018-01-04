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
     * Test of the Object and Index References
     * and the call-by-reference convention.
     *
     * SPEC2 file contains specification of the tests.
     */
    /*
     ??????????????????
     SEE: current number of errors (17.04.2005): 0x26
     SEE: report the name of each started test
     SEE: q000,q001...
     SEE: extend in every possible way the "total tests",
     see top of this spec, as far as fixing the bugs.
     SEE: continue to work on "Package total"
     SEE: extend the test "The chain of Index_References" after bug fixing
     SEE: CURRENTLY: compiler failed, Too few arguments (M002 requires X)
     SEE: test ref70 now works in accordance with the current behaviour -
     expects exceptions when dealing with ArgX-ORef & ArgX-IRef.
     should be re-dericted: when read autimatic dereference will
     be done properly.
     ??????????????????????
     */
    Name (Z111, 0x6F)
    /* TEST 1: Read of ArgX-ORef with DerefOf */

    Method (M221, 0, Serialized)
    {
        Name (TS, "m221")
        TS00 (TS)
        M1AD (TS, 0x00, 0x01, 0x01, 0x01, 0x00)
        M341 ()
        If (C088)
        {
            M4D0 ()
        }
    }

    /* TEST 2: Read of ArgX-ORef without DerefOf (automatic dereference) */

    Method (M222, 0, Serialized)
    {
        Name (TS, "m222")
        TS00 (TS)
        M1AD (TS, 0x00, 0x01, 0x01, 0x00, 0x00)
        If (Y507)
        {
            M342 ()
            If (C088)
            {
                M4D0 ()
            }
        }
        Else
        {
            M1AE (TS, "read of ArgX-ORef without DerefOf", "AE_AML_OPERAND_TYPE exception instead of automatic dereference")
        }
    }

    /* TEST 3: Read of ArgX-IRef with DerefOf */

    Method (M223, 0, Serialized)
    {
        Name (TS, "m223")
        TS00 (TS)
        M1AD (TS, 0x00, 0x01, 0x01, 0x01, 0x00)
        M343 ()
        If (C088)
        {
            M4D1 ()
        }
    }

    /* TEST 4: Read of ArgX-IRef without DerefOf */

    Method (M224, 0, Serialized)
    {
        Name (TS, "m224")
        TS00 (TS)
        M1AD (TS, 0x00, 0x01, 0x01, 0x00, 0x00)
        If (Y507)
        {
            M344 ()
            If (C088)
            {
                M4D1 ()
            }
        }
        Else
        {
            M1AE (TS, "read of ArgX-IRef without DerefOf", "AE_AML_OPERAND_TYPE exception instead of automatic dereference")
        }
    }

    /* TEST 5.0: Store into ArgX-object doesn't change original data */

    Method (M225, 0, Serialized)
    {
        Name (TS, "m225")
        TS00 (TS)
        M1AD (TS, 0x01, 0x01, 0x00, 0x00, 0x00)
        M1C0 ()
    }

    /* TEST 5.1: CopyObject into ArgX-object doesn't change original data */

    Method (M226, 0, Serialized)
    {
        Name (TS, "m226")
        TS00 (TS)
        M1AD (TS, 0x02, 0x01, 0x00, 0x00, 0x00)
        M1C0 ()
    }

    /* TEST 6.0: Store into ArgX-ORef changes original data */

    Method (M227, 0, Serialized)
    {
        Name (TS, "m227")
        TS00 (TS)
        M362 ()
        M363 ()
        M364 ()
        If (C088)
        {
            M1AD (TS, 0x01, 0x01, 0x01, 0x01, 0x00)
            M4D0 ()
        }
    }

    /* TEST 6.1: CopyObject into ArgX-ORef changes original data */

    Method (M228, 0, Serialized)
    {
        Name (TS, "m228")
        TS00 (TS)
        M1AD (TS, 0x02, 0x01, 0x01, 0x01, 0x00)
        M4D0 ()
    }

    /* TEST 7.0: Store into ArgX-IRef */
    /* */
    /* ACTUALLY: doesn't write to the original object. */
    Method (M229, 0, Serialized)
    {
        Name (TS, "m229")
        TS00 (TS)
        M1AD (TS, 0x01, 0x01, 0x01, 0x01, 0x00)
        M4D1 ()
    }

    /* TEST 7.1: CopyObject into ArgX-IRef */
    /* */
    /* ACTUALLY: doesn't write to the original object. */
    Method (M22A, 0, Serialized)
    {
        Name (TS, "m22a")
        TS00 (TS)
        M1AD (TS, 0x02, 0x01, 0x01, 0x01, 0x00)
        M4D1 ()
    }

    /* TEST 8: */
    /* ArgX-object is one of String, Buffer and Package. */
    /* Create IRef to the elements of the */
    /* ArgX-object inside the Method and write to them. */
    /* */
    /* ACTUALLY: writes to the original object. */
    Method (M22B, 0, NotSerialized)
    {
        TS00 ("m22b")
        /* Store and CopyObject */

        M345 ()
    }

    /* TEST 10: Check Buffer passed as a parameter. */
    /* Create Buffer Field inside Method and write to it. */
    /* */
    /* ACTUALLY: writes to the original object. */
    Method (M22C, 0, Serialized)
    {
        Name (TS, "m22c")
        If (Y100)
        {
            TS00 (TS)
        }
        Else
        {
            Debug = TS /* \M22C.TS__ */
        }

        Name (B000, Buffer (0x04)
        {
             0x01, 0x77, 0x03, 0x04                           // .w..
        })
        Name (B010, Buffer (0x04)
        {
             0x01, 0x77, 0x03, 0x04                           // .w..
        })
        Method (M000, 1, NotSerialized)
        {
            CreateField (Arg0, 0x08, 0x08, BF90)
            If ((BF90 != 0x77))
            {
                ERR (TS, Z111, 0xEF, 0x00, 0x00, BF90, 0x77)
            }

            BF90 = 0x9999992B
            If ((BF90 != 0x2B))
            {
                ERR (TS, Z111, 0xF3, 0x00, 0x00, BF90, 0x2B)
            }
        }

        Method (M001, 1, NotSerialized)
        {
            CreateField (Arg0, 0x08, 0x08, BF90)
            If ((BF90 != 0x77))
            {
                ERR (TS, Z111, 0xFB, 0x00, 0x00, BF90, 0x77)
            }

            BF90 = 0x2B
            CopyObject (0x9999992B, BF90) /* \M22C.M001.BF90 */
            If ((BF90 != 0x2B))
            {
                ERR (TS, Z111, 0x0101, 0x00, 0x00, BF90, 0x2B)
            }
        }

        BEG0 (Z111, TS)
        M000 (B000)
        If (X191)
        {
            M001 (B010)
        }

        M386 (TS, B000, 0x00, 0x04)
        If (X191)
        {
            M386 (TS, B010, 0x00, 0x05)
        }

        END0 ()
    }

    /* TEST 11: Check RefOf of ArgX-Object (ArgX is any type Object) */

    Method (M22D, 0, Serialized)
    {
        Name (TS, "m22d")
        TS00 (TS)
        M346 ()
        If (C088)
        {
            /* RefOf */

            C08B = 0x01 /* do RefOf(ArgX) checkings */
            M1AD (TS, 0x00, 0x01, 0x00, 0x00, 0x00)
            M1C0 ()
            /* CondRefOf */

            C08B = 0x02 /* do RefOf(ArgX) checkings */
            M1AD (TS, 0x00, 0x01, 0x00, 0x00, 0x00)
            M1C0 ()
            C08B = 0x00 /* do RefOf(ArgX) checkings */
        }
    }

    /* TEST 12: Check DerefOf(RefOf) of ArgX-Object (ArgX is any type Object) */

    Method (M22E, 0, NotSerialized)
    {
        TS00 ("m22e")
        M347 ()
    }

    /* TEST 13: Check RefOf of ArgX-ORef */

    Method (M22F, 0, NotSerialized)
    {
        TS00 ("m22f")
        M348 ()
    }

    /* TEST 14: Check DerefOf(RefOf) of ArgX-ORef */
    /* */
    /* ACTUALLY: writes to the original object. */
    Method (M230, 0, NotSerialized)
    {
        TS00 ("m230")
        M349 ()
    }

    /* TEST 15: Check RefOf of ArgX-IRef */

    Method (M231, 0, NotSerialized)
    {
        TS00 ("m231")
        M34A ()
    }

    /* TEST 16: Check DerefOf(RefOf) of ArgX-IRef */

    Method (M232, 0, NotSerialized)
    {
        TS00 ("m232")
        M34B ()
    }

    /* TEST 17: Check RefOf of ArgX-String, ArgX-Buffer, ArgX-Package */
    /* */
    /* ACTUALLY: */
    /* */
    /* ArgX-String  - writes to the original String */
    /* ArgX-Buffer  - doesnt */
    /* ArgX-Package - doesnt */
    Method (M233, 0, NotSerialized)
    {
        TS00 ("m233")
        M34C ()
    }

    /* TEST 19: Check RefOf of ArgX-Buffer (check its Buffer Field) */
    /* */
    /* ACTUALLY: doesn't write to the original object. */
    Method (M234, 0, Serialized)
    {
        Name (TS, "m234")
        If (Y100)
        {
            TS00 (TS)
        }
        Else
        {
            Debug = TS /* \M234.TS__ */
        }

        Name (B000, Buffer (0x04)
        {
             0x01, 0x77, 0x03, 0x04                           // .w..
        })
        Method (M000, 1, NotSerialized)
        {
            Local2 = DerefOf (Arg0)
            CreateField (Local2, 0x08, 0x08, BF90)
            If ((BF90 != 0x77))
            {
                ERR (TS, Z111, 0x0178, 0x00, 0x00, BF90, 0x77)
            }

            BF90 = 0x9999992B
            If ((BF90 != 0x2B))
            {
                ERR (TS, Z111, 0x017C, 0x00, 0x00, BF90, 0x2B)
            }
        }

        Method (M001, 1, NotSerialized)
        {
            Local2 = DerefOf (Arg0)
            CreateField (Local2, 0x08, 0x08, BF90)
            If ((BF90 != 0x77))
            {
                ERR (TS, Z111, 0x0186, 0x00, 0x00, BF90, 0x77)
            }

            CopyObject (0x9999992B, BF90) /* \M234.M001.BF90 */
            If ((BF90 != 0x2B))
            {
                ERR (TS, Z111, 0x018A, 0x00, 0x00, BF90, 0x2B)
            }
        }

        Method (M010, 2, NotSerialized)
        {
            Local0 = RefOf (Arg0)
            M000 (Local0)
            If ((Arg1 == C00A))
            {
                M381 (TS, Arg0, 0x00, 0x0100)
            }
            ElseIf ((Arg1 == C00B))
            {
                M382 (TS, Arg0, 0x00, 0x0101)
            }
            ElseIf ((Arg1 == C00C))
            {
                M383 (TS, Arg0, 0x00, 0x0102)
            }
        }

        Method (M020, 2, NotSerialized)
        {
            M000 (RefOf (Arg0))
            If ((Arg1 == C00A))
            {
                M381 (TS, Arg0, 0x00, 0x0103)
            }
            ElseIf ((Arg1 == C00B))
            {
                M382 (TS, Arg0, 0x00, 0x0104)
            }
            ElseIf ((Arg1 == C00C))
            {
                M383 (TS, Arg0, 0x00, 0x0105)
            }
        }

        Method (M011, 2, NotSerialized)
        {
            Local0 = RefOf (Arg0)
            M001 (Local0)
            If ((Arg1 == C00A))
            {
                M381 (TS, Arg0, 0x00, 0x0106)
            }
            ElseIf ((Arg1 == C00B))
            {
                M382 (TS, Arg0, 0x00, 0x0107)
            }
            ElseIf ((Arg1 == C00C))
            {
                M383 (TS, Arg0, 0x00, 0x0108)
            }
        }

        Method (M021, 2, NotSerialized)
        {
            M001 (RefOf (Arg0))
            If ((Arg1 == C00A))
            {
                M381 (TS, Arg0, 0x00, 0x0109)
            }
            ElseIf ((Arg1 == C00B))
            {
                M382 (TS, Arg0, 0x00, 0x010A)
            }
            ElseIf ((Arg1 == C00C))
            {
                M383 (TS, Arg0, 0x00, 0x010B)
            }
        }

        BEG0 (Z111, TS)
        M010 (B000, C00B)
        M382 (TS, B000, 0x00, 0x010C)
        M020 (B000, C00B)
        M382 (TS, B000, 0x00, 0x010D)
        If (X191)
        {
            M011 (B000, C00B)
            M382 (TS, B000, 0x00, 0x010E)
        }

        If (X191)
        {
            M021 (B000, C00B)
            M382 (TS, B000, 0x00, 0x010F)
        }

        END0 ()
    }

    /*
     * TEST 20: Check writing from ArgX to ArgY
     *
     * ACTUALLY:
     *
     *   '+' writes
     *   '-' not writes
     *   'e' exceptions occurs
     *
     *
     *   - from ArgX-Object to ArgY-Object
     *   + from ArgX-Object to ArgY-ORef
     *   - from ArgX-Object to ArgY-IRef
     *
     *   - from ArgX-ORef to ArgY-Object
     *   e from ArgX-ORef to ArgY-ORef
     *   - from ArgX-ORef to ArgY-IRef
     *
     *   - from ArgX-IRef to ArgY-Object
     *   e from ArgX-IRef to ArgY-ORef
     *   - from ArgX-IRef to ArgY-IRef
     */
    Method (M235, 0, Serialized)
    {
        Name (TS, "m235")
        If (Y100)
        {
            TS00 (TS)
        }
        Else
        {
            Debug = TS /* \M235.TS__ */
        }

        Name (I000, 0x77)
        Name (I010, 0x77)
        Name (I020, 0x77)
        Name (S000, "qwer0000")
        Name (S010, "qwer0000")
        Name (S021, "q+er0000")
        Name (S031, "q+er0000")
        Name (I001, 0x2B)
        Name (I011, 0x2B)
        Name (I021, 0x2B)
        Name (I031, 0x2B)
        Name (I041, 0x2B)
        Name (I051, 0x2B)
        Name (I061, 0x2B)
        Method (M000, 3, NotSerialized)
        {
            Arg1 = Arg0
            If ((Arg2 == C009))
            {
                M380 (TS, Arg1, 0x00, 0x00)
            }
            ElseIf ((Arg2 == C00A))
            {
                M381 (TS, Arg1, 0x00, 0x01)
            }
            ElseIf ((Arg2 == C00B))
            {
                M382 (TS, Arg1, 0x00, 0x02)
            }
            ElseIf ((Arg2 == C00C))
            {
                M383 (TS, Arg1, 0x00, 0x03)
            }
        }

        Method (M001, 3, NotSerialized)
        {
            CopyObject (Arg0, Arg1)
            If ((Arg2 == C009))
            {
                M380 (TS, Arg1, 0x00, 0x04)
            }
            ElseIf ((Arg2 == C00A))
            {
                M381 (TS, Arg1, 0x00, 0x05)
            }
            ElseIf ((Arg2 == C00B))
            {
                M382 (TS, Arg1, 0x00, 0x06)
            }
            ElseIf ((Arg2 == C00C))
            {
                M383 (TS, Arg1, 0x00, 0x07)
            }
        }

        Method (M002, 3, NotSerialized)
        {
            Arg1 = Arg0
            Local2 = DerefOf (Arg1)
            If ((Arg2 == C009))
            {
                M380 (TS, Local2, 0x00, 0x08)
            }
            ElseIf ((Arg2 == C00A))
            {
                M381 (TS, Local2, 0x00, 0x09)
            }
            ElseIf ((Arg2 == C00B))
            {
                M382 (TS, Local2, 0x00, 0x0A)
            }
            ElseIf ((Arg2 == C00C))
            {
                M383 (TS, Local2, 0x00, 0x0B)
            }
        }

        Method (M003, 3, NotSerialized)
        {
            CopyObject (Arg0, Arg1)
            Local2 = DerefOf (Arg1)
            If ((Arg2 == C009))
            {
                M380 (TS, Local2, 0x00, 0x0C)
            }
            ElseIf ((Arg2 == C00A))
            {
                M381 (TS, Local2, 0x00, 0x0D)
            }
            ElseIf ((Arg2 == C00B))
            {
                M382 (TS, Local2, 0x00, 0x0E)
            }
            ElseIf ((Arg2 == C00C))
            {
                M383 (TS, Local2, 0x00, 0x0F)
            }
        }

        Method (M004, 2, NotSerialized)
        {
            Arg1 = Arg0
            M380 (TS, Arg1, 0x00, 0x10)
        }

        Method (M005, 2, NotSerialized)
        {
            Arg1 = Arg0
        }

        BEG0 (Z111, TS)
        /* ArgX-Object -->> ArgY-Object */

        M000 (I000, I001, C009)
        M380 (TS, I000, 0x00, 0x11)
        M384 (TS, I001, 0x00, 0x12)
        M001 (I000, I001, C009)
        M380 (TS, I000, 0x00, 0x13)
        M384 (TS, I001, 0x00, 0x14)
        /* ArgX-Object -->> ArgY-ORef */

        M002 (I000, RefOf (I001), C009)
        M380 (TS, I000, 0x00, 0x15)
        M380 (TS, I001, 0x00, 0x16)
        M003 (I000, RefOf (I021), C009)
        M380 (TS, I000, 0x00, 0x17)
        M380 (TS, I021, 0x00, 0x18)
        Local0 = RefOf (I031)
        M002 (I000, Local0, C009)
        M380 (TS, I000, 0x00, 0x19)
        M380 (TS, I031, 0x00, 0x1A)
        Local2 = DerefOf (Local0)
        M380 (TS, Local2, 0x00, 0x1B)
        Local0 = RefOf (I041)
        M003 (I000, Local0, C009)
        M380 (TS, I000, 0x00, 0x1C)
        M380 (TS, I041, 0x00, 0x1D)
        Local2 = DerefOf (Local0)
        M380 (TS, Local2, 0x00, 0x1E)
        /* ArgX-Object -->> ArgY-IRef */

        M004 (I000, Local0 = S021 [0x01])
        M380 (TS, I000, 0x00, 0x1F)
        M385 (TS, S021, 0x00, 0x20)
        Local2 = DerefOf (Local0)
        M384 (TS, Local2, 0x00, 0x21)
        Local1 = Local0 = S021 [0x01]
        M004 (I000, Local0)
        M380 (TS, I000, 0x00, 0x22)
        M385 (TS, S021, 0x00, 0x23)
        Local2 = DerefOf (Local0)
        M384 (TS, Local2, 0x00, 0x24)
        M004 (I000, Local1)
        M380 (TS, I000, 0x00, 0x25)
        M385 (TS, S021, 0x00, 0x26)
        Local2 = DerefOf (Local1)
        M384 (TS, Local2, 0x00, 0x27)
        /* ArgX-ORef -->> ArgY-Object */

        M005 (RefOf (I000), S000)
        M380 (TS, I000, 0x00, 0x28)
        M381 (TS, S000, 0x00, 0x29)
        M005 (RefOf (I000), I051)
        M380 (TS, I000, 0x00, 0x2A)
        M384 (TS, I051, 0x00, 0x2B)
        Local0 = RefOf (I000)
        M005 (Local0, S000)
        M380 (TS, I000, 0x00, 0x2C)
        M381 (TS, S000, 0x00, 0x2D)
        M005 (Local0, I051)
        M380 (TS, I000, 0x00, 0x2E)
        M384 (TS, I051, 0x00, 0x2F)
        /* ArgX-IRef -->> ArgY-Object */

        M005 (Local0 = S000 [0x01], I000)
        M381 (TS, S000, 0x00, 0x30)
        M380 (TS, I000, 0x00, 0x31)
        /* The entire expression (exercised below): */
        /* m005(Index(s021, 1, Local0), RefOf(i010)) */
        /* here is executed step by step: */
        M385 (TS, S021, 0x00, 0x32)
        M380 (TS, I010, 0x00, 0x33)
        M005 (Local0 = S021 [0x01], I010)
        M385 (TS, S021, 0x00, 0x34)
        M380 (TS, I010, 0x00, 0x35)
        M005 (I051, RefOf (I010))
        M385 (TS, S021, 0x00, 0x36)
        M384 (TS, I051, 0x00, 0x37)
        M384 (TS, I010, 0x00, 0x38)
        If (Y513)
        {
            /* ArgX-IRef -->> ArgY-ORef */

            M005 (Local0 = S021 [0x01], RefOf (I020))
            M385 (TS, S021, 0x00, 0x39)
            M384 (TS, I020, 0x00, 0x3A)
            Local1 = DerefOf (Local0)
            M384 (TS, Local1, 0x00, 0x3B)
        }

        /* ArgX-IRef -->> ArgY-IRef */

        M005 (Local0 = S021 [0x01], Local1 = S010 [0x01])
        M385 (TS, S021, 0x00, 0x3C)
        M381 (TS, S010, 0x00, 0x3D)
        Local2 = DerefOf (Local0)
        M384 (TS, Local2, 0x00, 0x3E)
        Local2 = DerefOf (Local1)
        M380 (TS, Local2, 0x00, 0x3F)
        If (Y513)
        {
            /* ArgX-ORef -->> ArgY-ORef */

            M005 (RefOf (I000), RefOf (I061))
            M380 (TS, I000, 0x00, 0x40)
            M380 (TS, I061, 0x00, 0x41)
        }

        /* ArgX-ORef -->> ArgY-IRef */

        M005 (RefOf (I000), Local0 = S031 [0x01])
        M380 (TS, I000, 0x00, 0x42)
        M385 (TS, S031, 0x00, 0x43)
        Local2 = DerefOf (Local0)
        M384 (TS, Local2, 0x00, 0x44)
        END0 ()
    }

    /*
     * TEST 21: Check writing from ArgX to LocalX
     *
     * ACTUALLY:
     *
     *   - from ArgX-Object to LocalX
     *   - from ArgX-ORef to LocalX
     *   - from ArgX-IRef to LocalX
     */
    Method (M236, 0, Serialized)
    {
        Name (TS, "m236")
        If (Y100)
        {
            TS00 (TS)
        }
        Else
        {
            Debug = TS /* \M236.TS__ */
        }

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
        Name (I001, 0x2B)
        Name (S001, "q+er0000")
        Method (M000, 2, NotSerialized)
        {
            Local0 = Arg0
            If ((Arg1 == C009))
            {
                M380 (TS, Local0, 0x00, 0x00)
            }
            ElseIf ((Arg1 == C00A))
            {
                M381 (TS, Local0, 0x00, 0x01)
            }
            ElseIf ((Arg1 == C00B))
            {
                M382 (TS, Local0, 0x00, 0x02)
            }
            ElseIf ((Arg1 == C00C))
            {
                M383 (TS, Local0, 0x00, 0x03)
            }

            Local0 = 0x11
        }

        Method (M001, 2, NotSerialized)
        {
            Local0 = Arg0
            Local0 = ObjectType (Arg0)
            If ((Local0 != Arg1))
            {
                ERR (TS, Z111, 0x0318, 0x00, 0x00, Local0, Arg1)
            }

            /* Overwrite LocalX which contains either */
            /* Object or ORef or IRef. */
            Local0 = 0x11
        }

        BEG0 (Z111, TS)
        /* ArgX-Object -->> LocalX */

        M000 (I000, C009)
        M000 (S000, C00A)
        M000 (B000, C00B)
        M000 (P000, C00C)
        M380 (TS, I000, 0x00, 0x04)
        M381 (TS, S000, 0x00, 0x05)
        M382 (TS, B000, 0x00, 0x06)
        M383 (TS, P000, 0x00, 0x07)
        /* ArgX-ORef -->> LocalX */

        M001 (RefOf (I000), C009)
        M001 (RefOf (S000), C00A)
        M001 (RefOf (B000), C00B)
        M001 (RefOf (P000), C00C)
        M380 (TS, I000, 0x00, 0x08)
        M381 (TS, S000, 0x00, 0x09)
        M382 (TS, B000, 0x00, 0x0A)
        M383 (TS, P000, 0x00, 0x0B)
        /* ArgX-IRef -->> LocalX */

        M001 (S000 [0x01], C016)
        M001 (B000 [0x01], C016)
        M001 (P000 [0x01], C009)
        M380 (TS, I000, 0x00, 0x0C)
        M381 (TS, S000, 0x00, 0x0D)
        M382 (TS, B000, 0x00, 0x0E)
        M383 (TS, P000, 0x00, 0x0F)
        END0 ()
    }

    /*
     * TEST 23: Generate LocalX-ORef and write to it
     *
     * ACTUALLY: doesn't write to the original object
     */
    Method (M237, 0, Serialized)
    {
        Name (TS, "m237")
        If (Y100)
        {
            TS00 (TS)
        }
        Else
        {
            Debug = TS /* \M237.TS__ */
        }

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
        /* Overwrite LocalX-ORef */

        Method (M000, 1, NotSerialized)
        {
            Local0 = RefOf (Arg0)
            Local0 = 0x11
            Local0 = RefOf (I000)
            Local0 = 0x11
            Local0 = RefOf (S000)
            Local0 = 0x11
            Local0 = RefOf (B000)
            Local0 = 0x11
            Local0 = RefOf (P000)
            Local0 = 0x11
        }

        BEG0 (Z111, TS)
        M000 (I000)
        M000 (S000)
        M000 (B000)
        M000 (P000)
        M380 (TS, I000, 0x00, 0x00)
        M381 (TS, S000, 0x00, 0x01)
        M382 (TS, B000, 0x00, 0x02)
        M383 (TS, P000, 0x00, 0x03)
        END0 ()
    }

    /*
     * TEST 24: Generate LocalX-IRef and write to it
     *
     * ACTUALLY: doesn't write to the original object
     */
    Method (M238, 0, Serialized)
    {
        Name (TS, "m238")
        If (Y100)
        {
            TS00 (TS)
        }
        Else
        {
            Debug = TS /* \M238.TS__ */
        }

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
        /* Overwrite LocalX-ORef */

        Method (M000, 1, NotSerialized)
        {
            Local1 = Local0 = Arg0 [0x01]
            Local0 = 0x11
            Local1 = 0x22
            Local1 = Local0 = S000 [0x01]
            Local0 = 0x11
            Local1 = 0x22
            Local1 = Local0 = B000 [0x01]
            Local0 = 0x11
            Local1 = 0x22
            Local1 = Local0 = P000 [0x01]
            Local0 = 0x11
            Local1 = 0x22
        }

        Method (M001, 1, NotSerialized)
        {
            Local1 = Local0 = Arg0 [0x01]
            CopyObject (0x11, Local0)
            CopyObject (0x22, Local1)
            Local1 = Local0 = S000 [0x01]
            CopyObject (0x11, Local0)
            CopyObject (0x22, Local1)
            Local1 = Local0 = B000 [0x01]
            CopyObject (0x11, Local0)
            CopyObject (0x22, Local1)
            Local1 = Local0 = P000 [0x01]
            CopyObject (0x11, Local0)
            CopyObject (0x22, Local1)
        }

        BEG0 (Z111, TS)
        M000 (S000)
        M000 (B000)
        M000 (P000)
        M380 (TS, I000, 0x00, 0x00)
        M381 (TS, S000, 0x00, 0x01)
        M382 (TS, B000, 0x00, 0x02)
        M383 (TS, P000, 0x00, 0x03)
        M001 (S000)
        M001 (B000)
        M001 (P000)
        M380 (TS, I000, 0x00, 0x04)
        M381 (TS, S000, 0x00, 0x05)
        M382 (TS, B000, 0x00, 0x06)
        M383 (TS, P000, 0x00, 0x07)
        END0 ()
    }

    /*
     * TEST 25: Generate ORef to global Object into ArgX and write to it
     *
     * ACTUALLY:
     *
     *    - doesn't write to the original object
     *    - the repeated attempts to overwrite ORef-ArgX cause exceptions
     */
    Method (M239, 0, Serialized)
    {
        Name (TS, "m239")
        If (Y100)
        {
            TS00 (TS)
        }
        Else
        {
            Debug = TS /* \M239.TS__ */
        }

        /* Local Objects */

        Method (M000, 2, NotSerialized)
        {
            Arg1 = RefOf (Arg0)
            Arg1 = 0x11
        }

        Method (M001, 2, NotSerialized)
        {
            Arg1 = RefOf (Arg0)
            Arg1 = 0x11
            Arg1 = RefOf (IA00)
            Arg1 = 0x11
            Arg1 = RefOf (SA00)
            Arg1 = 0x11
            Arg1 = RefOf (BA00)
            Arg1 = 0x11
            Arg1 = RefOf (PA00)
            Arg1 = 0x11
        }

        Method (M002, 2, NotSerialized)
        {
            Arg1 = RefOf (Arg0)
            CopyObject (0x11, Arg1)
            Arg1 = RefOf (IA00)
            CopyObject (0x11, Arg1)
            Arg1 = RefOf (SA00)
            CopyObject (0x11, Arg1)
            Arg1 = RefOf (BA00)
            CopyObject (0x11, Arg1)
            Arg1 = RefOf (PA00)
            CopyObject (0x11, Arg1)
        }

        Method (M003, 2, NotSerialized)
        {
            CopyObject (RefOf (Arg0), Arg1)
            CopyObject (0x11, Arg1)
            CopyObject (RefOf (IA00), Arg1)
            CopyObject (0x11, Arg1)
            CopyObject (RefOf (SA00), Arg1)
            CopyObject (0x11, Arg1)
            CopyObject (RefOf (BA00), Arg1)
            CopyObject (0x11, Arg1)
            CopyObject (RefOf (PA00), Arg1)
            CopyObject (0x11, Arg1)
        }

        BEG0 (Z111, TS)
        /* m000 */

        M000 (IA00, IA10)
        M000 (SA00, SA10)
        M000 (BA00, BA10)
        M000 (PA00, PA10)
        M380 (TS, IA00, 0x00, 0x00)
        M381 (TS, SA00, 0x00, 0x01)
        M382 (TS, BA00, 0x00, 0x02)
        M383 (TS, PA00, 0x00, 0x03)
        M380 (TS, IA10, 0x00, 0x04)
        M381 (TS, SA10, 0x00, 0x05)
        M382 (TS, BA10, 0x00, 0x06)
        M383 (TS, PA10, 0x00, 0x07)
        If (Y514)
        {
            /* m001 */

            M001 (IA00, IA10)
            M001 (SA00, SA10)
            M001 (BA00, BA10)
            M001 (PA00, PA10)
            M380 (TS, IA00, 0x00, 0x08)
            M381 (TS, SA00, 0x00, 0x09)
            M382 (TS, BA00, 0x00, 0x0A)
            M383 (TS, PA00, 0x00, 0x0B)
            M380 (TS, IA10, 0x00, 0x0C)
            M381 (TS, SA10, 0x00, 0x0D)
            M382 (TS, BA10, 0x00, 0x0E)
            M383 (TS, PA10, 0x00, 0x0F)
            /* m002 */

            M002 (IA00, IA10)
            M002 (SA00, SA10)
            M002 (BA00, BA10)
            M002 (PA00, PA10)
            M380 (TS, IA00, 0x00, 0x10)
            M381 (TS, SA00, 0x00, 0x11)
            M382 (TS, BA00, 0x00, 0x12)
            M383 (TS, PA00, 0x00, 0x13)
            M380 (TS, IA10, 0x00, 0x14)
            M381 (TS, SA10, 0x00, 0x15)
            M382 (TS, BA10, 0x00, 0x16)
            M383 (TS, PA10, 0x00, 0x17)
        }

        /* m003 */

        M003 (IA00, IA10)
        M003 (SA00, SA10)
        M003 (BA00, BA10)
        M003 (PA00, PA10)
        M380 (TS, IA00, 0x00, 0x18)
        M381 (TS, SA00, 0x00, 0x19)
        M382 (TS, BA00, 0x00, 0x1A)
        M383 (TS, PA00, 0x00, 0x1B)
        M380 (TS, IA10, 0x00, 0x1C)
        M381 (TS, SA10, 0x00, 0x1D)
        M382 (TS, BA10, 0x00, 0x1E)
        M383 (TS, PA10, 0x00, 0x1F)
        END0 ()
    }

    /*
     * TEST 26: Generate ORef to local Object into ArgX and write to it
     *
     * ACTUALLY:
     *
     *    - doesn't write to the original object
     *    - the repeated attempts to overwrite ORef-ArgX cause exceptions
     */
    Method (M23A, 0, Serialized)
    {
        Name (TS, "m23a")
        If (Y100)
        {
            TS00 (TS)
        }
        Else
        {
            Debug = TS /* \M23A.TS__ */
        }

        /* Local Objects */

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
        Name (I010, 0x77)
        Name (S010, "qwer0000")
        Name (B010, Buffer (0x04)
        {
             0x01, 0x77, 0x03, 0x04                           // .w..
        })
        Name (P010, Package (0x03)
        {
            0x05, 
            0x77, 
            0x07
        })
        Method (M000, 2, NotSerialized)
        {
            Arg1 = RefOf (Arg0)
            Arg1 = 0x11
        }

        Method (M001, 2, NotSerialized)
        {
            Arg1 = RefOf (Arg0)
            Arg1 = 0x11
            Arg1 = RefOf (I000)
            Arg1 = 0x11
            Arg1 = RefOf (S000)
            Arg1 = 0x11
            Arg1 = RefOf (B000)
            Arg1 = 0x11
            Arg1 = RefOf (P000)
            Arg1 = 0x11
        }

        Method (M002, 2, NotSerialized)
        {
            Arg1 = RefOf (Arg0)
            CopyObject (0x11, Arg1)
            Arg1 = RefOf (I000)
            CopyObject (0x11, Arg1)
            Arg1 = RefOf (S000)
            CopyObject (0x11, Arg1)
            Arg1 = RefOf (B000)
            CopyObject (0x11, Arg1)
            Arg1 = RefOf (P000)
            CopyObject (0x11, Arg1)
        }

        Method (M003, 2, NotSerialized)
        {
            CopyObject (RefOf (Arg0), Arg1)
            CopyObject (0x11, Arg1)
            CopyObject (RefOf (I000), Arg1)
            CopyObject (0x11, Arg1)
            CopyObject (RefOf (S000), Arg1)
            CopyObject (0x11, Arg1)
            CopyObject (RefOf (B000), Arg1)
            CopyObject (0x11, Arg1)
            CopyObject (RefOf (P000), Arg1)
            CopyObject (0x11, Arg1)
        }

        BEG0 (Z111, TS)
        /* m000 */

        M000 (I000, I010)
        M000 (S000, S010)
        M000 (B000, B010)
        M000 (P000, P010)
        M380 (TS, I000, 0x00, 0x00)
        M381 (TS, S000, 0x00, 0x01)
        M382 (TS, B000, 0x00, 0x02)
        M383 (TS, P000, 0x00, 0x03)
        M380 (TS, I010, 0x00, 0x04)
        M381 (TS, S010, 0x00, 0x05)
        M382 (TS, B010, 0x00, 0x06)
        M383 (TS, P010, 0x00, 0x07)
        If (Y514)
        {
            /* m001 */

            M001 (I000, I010)
            M001 (S000, S010)
            M001 (B000, B010)
            M001 (P000, P010)
            M380 (TS, I000, 0x00, 0x08)
            M381 (TS, S000, 0x00, 0x09)
            M382 (TS, B000, 0x00, 0x0A)
            M383 (TS, P000, 0x00, 0x0B)
            M380 (TS, I010, 0x00, 0x0C)
            M381 (TS, S010, 0x00, 0x0D)
            M382 (TS, B010, 0x00, 0x0E)
            M383 (TS, P010, 0x00, 0x0F)
            /* m002 */

            M002 (I000, I010)
            M002 (S000, S010)
            M002 (B000, B010)
            M002 (P000, P010)
            M380 (TS, I000, 0x00, 0x10)
            M381 (TS, S000, 0x00, 0x11)
            M382 (TS, B000, 0x00, 0x12)
            M383 (TS, P000, 0x00, 0x13)
            M380 (TS, I010, 0x00, 0x14)
            M381 (TS, S010, 0x00, 0x15)
            M382 (TS, B010, 0x00, 0x16)
            M383 (TS, P010, 0x00, 0x17)
        }

        /* m003 */

        M003 (I000, I010)
        M003 (S000, S010)
        M003 (B000, B010)
        M003 (P000, P010)
        M380 (TS, I000, 0x00, 0x18)
        M381 (TS, S000, 0x00, 0x19)
        M382 (TS, B000, 0x00, 0x1A)
        M383 (TS, P000, 0x00, 0x1B)
        M380 (TS, I010, 0x00, 0x1C)
        M381 (TS, S010, 0x00, 0x1D)
        M382 (TS, B010, 0x00, 0x1E)
        M383 (TS, P010, 0x00, 0x1F)
        END0 ()
    }

    /*
     * TEST 27: Check CopyObject to LocalX
     *
     * Local0-Local7 can be written with any type object without any conversion
     *
     * Check each type after each one
     */
    Method (M23B, 0, NotSerialized)
    {
        TS00 ("m23b")
        M1B1 ()
    }

    /*
     * TEST 28: Check Store to LocalX
     *
     * Local0-Local7 can be written without any conversion
     *
     * Check each type after each one
     */
    Method (M23C, 0, NotSerialized)
    {
        TS00 ("m23c")
        M1B2 ()
    }

    /*
     * TEST 29: CopyObject the result of RefOf to LocalX
     *
     * References to any type Objects are available.
     */
    Method (M23D, 0, NotSerialized)
    {
        TS00 ("m23d")
        M1B4 ()
    }

    /*
     * TEST 30: Store the result of RefOf to LocalX
     *
     * ACTUALLY: references to any type Objects are available
     */
    Method (M23E, 0, NotSerialized)
    {
        TS00 ("m23e")
        M1B5 ()
    }

    /*
     * TEST 31: CopyObject the result of Index to LocalX
     */
    Method (M23F, 0, NotSerialized)
    {
        TS00 ("m23f")
        M1B6 ()
    }

    /*
     * TEST 32: Store the result of Index to LocalX
     */
    Method (M250, 0, NotSerialized)
    {
        TS00 ("m250")
        M1B7 ()
    }

    /*
     * TEST 33: mix of all the legal ways (enumerated in
     *          tests TEST 27 - TEST 35) of initializing
     *          the LocalX.
     */
    Method (M251, 0, NotSerialized)
    {
        TS00 ("m251")
        /* Strategies: */
        /* 1 - mix of groups, 2 - Mod-6 strategy, otherwise - linear */
        M1E0 (0x01)
    }

    /*
     * TEST 34: Obtain the NamedX objects of all the types
     *          and check their {type,size,value}.
     *
     * SEE: it is implemented in name/name.asl
     */
    /*
     * TEST 35
     *
     * Obtain and verify the ORef
     * and IRef to named objects
     * {type,size,value}.
     */
    Method (M252, 0, Serialized)
    {
        Name (TS, "m252")
        TS00 (TS)
        M1AD (TS, 0x00, 0x01, 0x01, 0x01, 0x00)
        /* NamedX-ORef */

        M4D2 ()
        /* NamedX-IRef */

        M4D3 ()
    }

    /*
     * TEST 36: Check ArgX-ORef being passed further to another Method
     *
     * ACTUALLY: writes to the original object
     *           Object:RefOf:ORef:ArgX-ORef:M2:M3:...:M*:write
     *           ^ Changed
     *
     * A set of available for Store types for to write into is restricted
     */
    Method (M253, 0, NotSerialized)
    {
        TS00 ("m253")
        /* Store */

        M34D (0x00)
        /* CopyObject */

        M34D (0x01)
    }

    /*
     * TEST 37: Check ArgX-IRef being passed further to another Method
     *
     * ACTUALLY: doesn't write to the original object
     */
    Method (M254, 0, NotSerialized)
    {
        TS00 ("m254")
        /* Store */

        M34E (0x00)
        /* CopyObject */

        M34E (0x01)
    }

    /*
     * TEST 38: Check write(x, RefOf(y))
     */
    Method (M255, 0, NotSerialized)
    {
        TS00 ("m255")
        /* Store */

        M34F ()
        /* CopyObject */
    /* CURRENTLY: compiler failed CopyObject(xx, RefOf(xx)) */
    /* m350() */
    }

    /*
     * TEST 39: Check write(x, Index(String))
     */
    Method (M256, 0, Serialized)
    {
        Name (TS, "m256")
        TS00 (TS)
        Name (S000, "qwer0000")
        Name (S010, "qwer0000")
        BEG0 (Z111, TS)
        /* Store */

        S000 [0x01] = 0x2B
        M385 (TS, S000, 0x00, 0x00)
        Local0 = S010 [0x01]
        S010 [0x01] = 0x2B
        M385 (TS, S010, 0x00, 0x01)
        /* CopyObject */
        /* CURRENTLY: compiler failed CopyObject(xx, Index(xx,xx)) */
        /* CopyObject(0x2b, Index(s020, 1)) */
        /* m385(ts, s020, 0, 2) */
        END0 ()
    }

    /*
     * TEST 40: Check write(x, Index(Buffer))
     */
    Method (M257, 0, Serialized)
    {
        Name (TS, "m257")
        TS00 (TS)
        Name (B000, Buffer (0x04)
        {
             0x01, 0x77, 0x03, 0x04                           // .w..
        })
        Name (B010, Buffer (0x04)
        {
             0x01, 0x77, 0x03, 0x04                           // .w..
        })
        BEG0 (Z111, TS)
        /* Store */

        B000 [0x01] = 0x2B
        M386 (TS, B000, 0x00, 0x00)
        Local0 = B010 [0x01]
        B010 [0x01] = 0x2B
        M386 (TS, B010, 0x00, 0x01)
        END0 ()
    }

    /*
     * TEST 41: Check Store(Object, Index(Package(){Uninitialized}))
     */
    Method (M258, 1, Serialized)
    {
        Name (TS, "m258")
        TS00 (TS)
        Name (P100, Package (0x12){})
        P100 [0x00] = 0x00
        P100 [0x01] = I900 /* \I900 */
        P100 [0x02] = S900 /* \S900 */
        P100 [0x03] = B900 /* \B900 */
        P100 [0x04] = P953 /* \P953 */
        P100 [0x05] = F900 /* \F900 */
        /*
         // Removed 09/2015. iASL now disallows these stores
         if (arg0) {
         // Check these for exceptions but not there
         Store(d900, Index(p100, 6))
         Store(e900, Index(p100, 7))
         Store(m914, Index(p100, 8))
         Store(mx90, Index(p100, 9))
         Store(r900, Index(p100, 10))
         Store(pw90, Index(p100, 11))
         Store(pr90, Index(p100, 12))
         Store(tz90, Index(p100, 13))
         }
         */
        P100 [0x0E] = BF90 /* \BF90 */
        P100 [0x0F] = 0x0F
        P100 [0x10] = 0x10
        /* Verify p955-like Package */

        M1AF (P100, 0x00, 0x00, 0x00)
        M1A6 ()
    }

    /*
     * TEST 42: Check CopyObject(Object, Index(Package(){Uninitialized}))
     *
     * CURRENTLY: compiler failed CopyObject(xx, Index(xx,xx))
     */
    Method (M259, 0, Serialized)
    {
        TS00 ("m259")
        Name (P100, Package (0x12){})
        /*
     *	CopyObject(i900, Index(p100, 1))
     *	CopyObject(s900, Index(p100, 2))
     *	CopyObject(b900, Index(p100, 3))
     *	CopyObject(p953, Index(p100, 4))
     *	CopyObject(f900, Index(p100, 5))
     *	CopyObject(d900, Index(p100, 6))
     *	CopyObject(e900, Index(p100, 7))
     *	CopyObject(m914, Index(p100, 8))
     *	CopyObject(mx90, Index(p100, 9))
     *	CopyObject(r900, Index(p100, 10))
     *	CopyObject(pw90, Index(p100, 11))
     *	CopyObject(pr90, Index(p100, 12))
     *	CopyObject(tz90, Index(p100, 13))
     *	CopyObject(bf90, Index(p100, 14))
     *
     *	m1af(p100, 1, 0, 0)
     *
     *
     *	m1a6()
     */
    }

    /*
     * TEST 43: Check Store(RefOf(Object), Index(Package(){Uninitialized}))
     */
    Method (M25A, 0, Serialized)
    {
        TS00 ("m25a")
        Name (P100, Package (0x12){})
        M352 (P100)
        M1AF (P100, 0x01, 0x01, 0x01)
        M1A6 ()
    }

    /*
     * TEST 44: Check Store(Index(Object,x), Index(Package(){Uninitialized}))
     */
    Method (M25B, 0, Serialized)
    {
        TS00 ("m25b")
        Name (P100, Package (0x12){})
        /* Store IRef (Index(p955, x)) into Package */

        M353 (P100, 0x00)
        /* Verify p955-like Package */

        M1AF (P100, 0x01, 0x00, 0x01)
        M1A6 ()
    }

    /*
     * TEST 45: Check write(x, Index(Package(){Constant}))
     */
    Method (M25C, 0, Serialized)
    {
        Name (TS, "m25c")
        TS00 (TS)
        Name (P000, Package (0x03)
        {
            0x05, 
            0x77, 
            0x07
        })
        Name (P010, Package (0x03)
        {
            0x05, 
            0x77, 
            0x07
        })
        BEG0 (Z111, TS)
        /* Store */

        P000 [0x01] = 0x2B
        M387 (TS, P000, 0x00, 0x00)
        Local0 = P010 [0x01]
        P010 [0x01] = 0x2B
        M387 (TS, P010, 0x00, 0x01)
        END0 ()
    }

    /*
     * TEST 46: Check write(x, Index(Package(){NamedX}))
     */
    Method (M25D, 0, NotSerialized)
    {
        TS00 ("m25d")
        /* Write Integer into Package and verify the obtained contents */

        M351 (P955)
        /* Restore p955 Package */

        M1C6 ()
        /* Check that the original data (i900,...) */
        /* are unchanged: */
        M1A6 ()
    }

    /*
     * TEST 47: Check Store(Object, Index(Package(){ORef}))
     */
    Method (M25E, 0, Serialized)
    {
        TS00 ("m25e")
        Name (P100, Package (0x12){})
        /* Prepare Package with ORef elements */
        /* pointing to the global *9** data: */
        M352 (P100)
        /* Verify p955-like Package */

        M1AF (P100, 0x01, 0x01, 0x01)
        /* Check the global *9** data are safe: */

        M1A6 ()
        /* Write Integer into Package over the ORef */
        /* and verify the obtained contents */
        M351 (P100)
        /* Check the global *9** data are safe: */

        M1A6 ()
    }

    /*
     * TEST 48: Check Store(Object, Index(Package(){IRef}))
     */
    Method (M25F, 0, Serialized)
    {
        TS00 ("m25f")
        Name (P100, Package (0x12){})
        /* Store IRef (Index(p955, x)) into Package */
        /* (p955 belongs to *9** data): */
        M353 (P100, 0x00)
        /* Verify p955-like Package */

        M1AF (P100, 0x01, 0x00, 0x01)
        M1A6 ()
        /* Write Integer into Package over the IRef */
        /* and verify the obtained contents */
        M351 (P100)
        /* Check the global *9** data are safe: */

        M1A6 ()
    }

    /*
     * TEST 49: ORef-LocalX
     */
    Method (M260, 0, NotSerialized)
    {
        TS00 ("m260")
        /* Store */

        M354 ()
        /* CopyObject */

        M355 ()
    }

    Method (M354, 0, Serialized)
    {
        Name (TS, "m354")
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
        Device (D000)
        {
            Name (I000, 0xABCD0017)
        }

        Method (M000, 1, NotSerialized)
        {
            Arg0 = 0x2B
        }

        BEG0 (Z111, TS)
        Local0 = RefOf (I000)
        If (0x00)
        {
            /* This is a reference */

            CH03 (TS, 0x00, 0x00, 0x06F1, 0x00)
            Local7 = (Local0 + 0x01)
            CH04 (TS, 0x00, 0xFF, 0x00, 0x06F3, 0x00, 0x00)
        }

        M1A3 (Local0, C009, 0x00, 0x00, 0x02)
        M380 (TS, DerefOf (Local0), 0x00, 0x03)
        M000 (Local0)
        M384 (TS, DerefOf (Local0), 0x00, 0x04)
        Local0 = RefOf (S000)
        M1A3 (Local0, C00A, 0x00, 0x00, 0x05)
        M381 (TS, DerefOf (Local0), 0x00, 0x06)
        M000 (Local0)
        M384 (TS, DerefOf (Local0), 0x00, 0x07)
        Local0 = RefOf (B000)
        M1A3 (Local0, C00B, 0x00, 0x00, 0x08)
        M382 (TS, DerefOf (Local0), 0x00, 0x09)
        M000 (Local0)
        M384 (TS, DerefOf (Local0), 0x00, 0x0A)
        Local0 = RefOf (P000)
        M1A3 (Local0, C00C, 0x00, 0x00, 0x0B)
        M383 (TS, DerefOf (Local0), 0x00, 0x0C)
        M000 (Local0)
        M384 (TS, DerefOf (Local0), 0x00, 0x0D)
        Local0 = RefOf (D000)
        M1A3 (Local0, C00E, 0x00, 0x00, 0x0E)
        M000 (Local0)
        M384 (TS, DerefOf (Local0), 0x00, 0x0F)
        END0 ()
    }

    Method (M355, 0, Serialized)
    {
        Name (TS, "m355")
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
        Device (D000)
        {
            Name (I000, 0xABCD0017)
        }

        Method (M000, 1, NotSerialized)
        {
            CopyObject (0x2B, Arg0)
        }

        BEG0 (Z111, TS)
        CopyObject (RefOf (I000), Local0)
        If (0x00)
        {
            /* This is a reference */

            CH03 (TS, 0x00, 0x02, 0x0729, 0x00)
            Local7 = (Local0 + 0x01)
            CH04 (TS, 0x00, 0xFF, 0x00, 0x072B, 0x00, 0x00)
        }

        M1A3 (Local0, C009, 0x00, 0x00, 0x00)
        M380 (TS, DerefOf (Local0), 0x00, 0x01)
        M000 (Local0)
        M384 (TS, DerefOf (Local0), 0x00, 0x02)
        CopyObject (RefOf (S000), Local0)
        M1A3 (Local0, C00A, 0x00, 0x00, 0x03)
        M381 (TS, DerefOf (Local0), 0x00, 0x04)
        M000 (Local0)
        M384 (TS, DerefOf (Local0), 0x00, 0x05)
        CopyObject (RefOf (B000), Local0)
        M1A3 (Local0, C00B, 0x00, 0x00, 0x06)
        M382 (TS, DerefOf (Local0), 0x00, 0x07)
        M000 (Local0)
        M384 (TS, DerefOf (Local0), 0x00, 0x08)
        CopyObject (RefOf (P000), Local0)
        M1A3 (Local0, C00C, 0x00, 0x00, 0x09)
        M383 (TS, DerefOf (Local0), 0x00, 0x0A)
        M000 (Local0)
        M384 (TS, DerefOf (Local0), 0x00, 0x0B)
        CopyObject (RefOf (D000), Local0)
        M1A3 (Local0, C00E, 0x00, 0x00, 0x0C)
        M000 (Local0)
        M384 (TS, DerefOf (Local0), 0x00, 0x0D)
        END0 ()
    }

    /*
     * TEST 50: ORef-ArgX
     */
    Method (M261, 0, Serialized)
    {
        Name (TS, "m261")
        TS00 (TS)
        Name (I000, 0x77)
        Name (I001, 0x77)
        BEG0 (Z111, TS)
        /* Store */

        If (Y519)
        {
            M356 (I000)
            M380 (TS, I000, 0x00, 0x00)
        }
        Else
        {
            M1AE (TS, "Store ORef to ArgX", "AE_AML_OPERAND_TYPE exception occurs")
        }

        /* CopyObject */

        If (Y520)
        {
            M357 (I001)
            M380 (TS, I001, 0x00, 0x01)
        }
        Else
        {
            M1AE (TS, "CopyObject ORef to ArgX", "AE_AML_OPERAND_TYPE exception occurs")
        }

        END0 ()
    }

    Method (M356, 1, Serialized)
    {
        Name (TS, "m356")
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
        Device (D000)
        {
            Name (I000, 0xABCD0017)
        }

        Method (M000, 1, NotSerialized)
        {
            Arg0 = 0x2B
        }

        BEG0 (Z111, TS)
        Arg0 = RefOf (I000)
        If (0x00)
        {
            /* This is a reference */

            CH03 (TS, 0x00, 0x04, 0x0784, 0x00)
            Local7 = (Arg0 + 0x01)
            CH04 (TS, 0x00, 0xFF, 0x00, 0x0786, 0x00, 0x00)
        }

        M1A3 (Arg0, C009, 0x00, 0x00, 0x00)
        M380 (TS, DerefOf (Arg0), 0x00, 0x01)
        M000 (Arg0)
        M384 (TS, DerefOf (Arg0), 0x00, 0x02)
        Arg0 = RefOf (S000)
        M1A3 (Arg0, C00A, 0x00, 0x00, 0x03)
        M381 (TS, DerefOf (Arg0), 0x00, 0x04)
        M000 (Arg0)
        M384 (TS, DerefOf (Arg0), 0x00, 0x05)
        Arg0 = RefOf (B000)
        M1A3 (Arg0, C00B, 0x00, 0x00, 0x06)
        M382 (TS, DerefOf (Arg0), 0x00, 0x07)
        M000 (Arg0)
        M384 (TS, DerefOf (Arg0), 0x00, 0x08)
        Arg0 = RefOf (P000)
        M1A3 (Arg0, C00C, 0x00, 0x00, 0x09)
        M383 (TS, DerefOf (Arg0), 0x00, 0x0A)
        M000 (Arg0)
        M384 (TS, DerefOf (Arg0), 0x00, 0x0B)
        Arg0 = RefOf (D000)
        M1A3 (Arg0, C00E, 0x00, 0x00, 0x0C)
        M000 (Arg0)
        M384 (TS, DerefOf (Arg0), 0x00, 0x0D)
        END0 ()
    }

    Method (M357, 1, Serialized)
    {
        Name (TS, "m357")
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
        Device (D000)
        {
            Name (I000, 0xABCD0017)
        }

        Method (M000, 1, NotSerialized)
        {
            CopyObject (0x2B, Arg0)
        }

        BEG0 (Z111, TS)
        CopyObject (RefOf (I000), Arg0)
        If (0x00)
        {
            /* This is a reference */

            CH03 (TS, 0x00, 0x06, 0x07BC, 0x00)
            Local7 = (Arg0 + 0x01)
            CH04 (TS, 0x00, 0xFF, 0x00, 0x07BE, 0x00, 0x00)
        }

        M1A3 (Arg0, C009, 0x00, 0x00, 0x00)
        M380 (TS, DerefOf (Arg0), 0x00, 0x01)
        M000 (Arg0)
        M384 (TS, DerefOf (Arg0), 0x00, 0x02)
        CopyObject (RefOf (S000), Arg0)
        M1A3 (Arg0, C00A, 0x00, 0x00, 0x03)
        M381 (TS, DerefOf (Arg0), 0x00, 0x04)
        M000 (Arg0)
        M384 (TS, DerefOf (Arg0), 0x00, 0x05)
        CopyObject (RefOf (B000), Arg0)
        M1A3 (Arg0, C00B, 0x00, 0x00, 0x06)
        M382 (TS, DerefOf (Arg0), 0x00, 0x07)
        M000 (Arg0)
        M384 (TS, DerefOf (Arg0), 0x00, 0x08)
        CopyObject (RefOf (P000), Arg0)
        M1A3 (Arg0, C00C, 0x00, 0x00, 0x09)
        M383 (TS, DerefOf (Arg0), 0x00, 0x0A)
        M000 (Arg0)
        M384 (TS, DerefOf (Arg0), 0x00, 0x0B)
        CopyObject (RefOf (D000), Arg0)
        M1A3 (Arg0, C00E, 0x00, 0x00, 0x0C)
        M000 (Arg0)
        M384 (TS, DerefOf (Arg0), 0x00, 0x0D)
        END0 ()
    }

    /*
     * TEST 51: ORef-NamedX
     */
    Method (M262, 0, Serialized)
    {
        Name (TS, "m262")
        TS00 (TS)
        /* Store */

        If (Y521)
        {
            M358 ()
        }
        Else
        {
            M1AE (TS, "Store ORef to NamedX", "AE_AML_OPERAND_TYPE exception occurs")
        }

        /* CopyObject */

        If (Y522)
        {
            M359 ()
        }
        Else
        {
            M1AE (TS, "CopyObject ORef to NamedX", "AE_AML_OPERAND_TYPE exception occurs")
        }
    }

    Method (M358, 0, Serialized)
    {
        Name (TS, "m358")
        Name (III0, 0x00)
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
        Device (D000)
        {
            Name (I000, 0xABCD0017)
        }

        Method (M000, 1, NotSerialized)
        {
            Arg0 = 0x2B
        }

        BEG0 (Z111, TS)
        III0 = RefOf (I000)
        If (0x00)
        {
            /* This is a reference */

            CH03 (TS, 0x00, 0x08, 0x0810, 0x00)
            Local7 = (III0 + 0x01)
            CH04 (TS, 0x00, 0xFF, 0x00, 0x0812, 0x00, 0x00)
        }

        M1A3 (III0, C009, 0x00, 0x00, 0x00)
        M380 (TS, DerefOf (III0), 0x00, 0x01)
        M000 (III0)
        M384 (TS, DerefOf (III0), 0x00, 0x02)
        III0 = RefOf (S000)
        M1A3 (III0, C00A, 0x00, 0x00, 0x03)
        M381 (TS, DerefOf (III0), 0x00, 0x04)
        M000 (III0)
        M384 (TS, DerefOf (III0), 0x00, 0x05)
        III0 = RefOf (B000)
        M1A3 (III0, C00B, 0x00, 0x00, 0x06)
        M382 (TS, DerefOf (III0), 0x00, 0x07)
        M000 (III0)
        M384 (TS, DerefOf (III0), 0x00, 0x08)
        III0 = RefOf (P000)
        M1A3 (III0, C00C, 0x00, 0x00, 0x09)
        M383 (TS, DerefOf (III0), 0x00, 0x0A)
        M000 (III0)
        M384 (TS, DerefOf (III0), 0x00, 0x0B)
        III0 = RefOf (D000)
        M1A3 (III0, C00E, 0x00, 0x00, 0x0C)
        M000 (III0)
        M384 (TS, DerefOf (III0), 0x00, 0x0D)
        END0 ()
    }

    Method (M359, 0, Serialized)
    {
        Name (TS, "m359")
        Name (III0, 0x00)
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
        Device (D000)
        {
            Name (I000, 0xABCD0017)
        }

        Method (M000, 1, NotSerialized)
        {
            CopyObject (0x2B, Arg0)
        }

        BEG0 (Z111, TS)
        CopyObject (RefOf (I000), III0) /* \M359.III0 */
        If (0x00)
        {
            /* This is a reference */

            CH03 (TS, 0x00, 0x0A, 0x084A, 0x00)
            Local7 = (III0 + 0x01)
            CH04 (TS, 0x00, 0xFF, 0x00, 0x084C, 0x00, 0x00)
        }

        M1A3 (III0, C009, 0x00, 0x00, 0x00)
        M380 (TS, DerefOf (III0), 0x00, 0x01)
        M000 (III0)
        M384 (TS, DerefOf (III0), 0x00, 0x02)
        CopyObject (RefOf (S000), III0) /* \M359.III0 */
        M1A3 (III0, C00A, 0x00, 0x00, 0x03)
        M381 (TS, DerefOf (III0), 0x00, 0x04)
        M000 (III0)
        M384 (TS, DerefOf (III0), 0x00, 0x05)
        CopyObject (RefOf (B000), III0) /* \M359.III0 */
        M1A3 (III0, C00B, 0x00, 0x00, 0x06)
        M382 (TS, DerefOf (III0), 0x00, 0x07)
        M000 (III0)
        M384 (TS, DerefOf (III0), 0x00, 0x08)
        CopyObject (RefOf (P000), III0) /* \M359.III0 */
        M1A3 (III0, C00C, 0x00, 0x00, 0x09)
        M383 (TS, DerefOf (III0), 0x00, 0x0A)
        M000 (III0)
        M384 (TS, DerefOf (III0), 0x00, 0x0B)
        CopyObject (RefOf (D000), III0) /* \M359.III0 */
        M1A3 (III0, C00E, 0x00, 0x00, 0x0C)
        M000 (III0)
        M384 (TS, DerefOf (III0), 0x00, 0x0D)
        END0 ()
    }

    /*
     * TEST 52: ORef-El_of_Package
     */
    Method (M263, 0, NotSerialized)
    {
        TS00 ("m263")
        /* Store */

        M35A ()
        /* CopyObject */

        M35B ()
    }

    Method (M35A, 0, Serialized)
    {
        Name (TS, "m35a")
        Name (PPP0, Package (0x05){})
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
        Device (D000)
        {
            Name (I000, 0xABCD0017)
        }

        BEG0 (Z111, TS)
        PPP0 [0x00] = RefOf (I000)
        PPP0 [0x01] = RefOf (S000)
        PPP0 [0x02] = RefOf (B000)
        PPP0 [0x03] = RefOf (P000)
        PPP0 [0x04] = RefOf (D000)
        Local0 = DerefOf (PPP0 [0x00])
        M1A3 (Local0, C009, 0x00, 0x00, 0x00)
        M380 (TS, DerefOf (Local0), 0x00, 0x01)
        Local0 = DerefOf (PPP0 [0x01])
        M1A3 (Local0, C00A, 0x00, 0x00, 0x02)
        M381 (TS, DerefOf (Local0), 0x00, 0x03)
        Local0 = DerefOf (PPP0 [0x02])
        M1A3 (Local0, C00B, 0x00, 0x00, 0x04)
        M382 (TS, DerefOf (Local0), 0x00, 0x05)
        Local0 = DerefOf (PPP0 [0x03])
        M1A3 (Local0, C00C, 0x00, 0x00, 0x06)
        M383 (TS, DerefOf (Local0), 0x00, 0x07)
        Local0 = DerefOf (PPP0 [0x04])
        M1A3 (Local0, C00E, 0x00, 0x00, 0x08)
        /* Replace */

        PPP0 [0x00] = RefOf (I000)
        Local0 = DerefOf (PPP0 [0x00])
        M1A3 (Local0, C009, 0x00, 0x00, 0x09)
        M380 (TS, DerefOf (Local0), 0x00, 0x0A)
        PPP0 [0x00] = RefOf (S000)
        Local0 = DerefOf (PPP0 [0x00])
        M1A3 (Local0, C00A, 0x00, 0x00, 0x0B)
        M381 (TS, DerefOf (Local0), 0x00, 0x0C)
        PPP0 [0x00] = RefOf (B000)
        Local0 = DerefOf (PPP0 [0x00])
        M1A3 (Local0, C00B, 0x00, 0x00, 0x0D)
        M382 (TS, DerefOf (Local0), 0x00, 0x0E)
        PPP0 [0x00] = RefOf (P000)
        Local0 = DerefOf (PPP0 [0x00])
        M1A3 (Local0, C00C, 0x00, 0x00, 0x0F)
        M383 (TS, DerefOf (Local0), 0x00, 0x10)
        PPP0 [0x00] = RefOf (D000)
        Local0 = DerefOf (PPP0 [0x00])
        M1A3 (Local0, C00E, 0x00, 0x00, 0x11)
        END0 ()
    }

    /* CURRENTLY: compiler failed CopyObject(xx, Index(xx,xx)) */

    Method (M35B, 0, NotSerialized)
    {
        /*
     Name(ts, "m35b")
     Name(ppp0, Package(5) {})
     Name(i000, 0x77)
     Name(s000, "qwer0000")
     Name(b000, Buffer(4) {1,0x77,3,4})
     Name(p000, Package(3) {5,0x77,7})
     Device(d000) { Name(i000, 0xabcd0017) }
     BEG0(z111, ts)
     CopyObject(RefOf(i000), Index(ppp0, 0))
     CopyObject(RefOf(s000), Index(ppp0, 1))
     CopyObject(RefOf(b000), Index(ppp0, 2))
     CopyObject(RefOf(p000), Index(ppp0, 3))
     CopyObject(RefOf(d000), Index(ppp0, 4))
     CopyObject(DerefOf(Index(ppp0, 0)), Local0)
     m1a3(Local0, c009, 0, 0, 0)
     m380(ts, DerefOf(Local0), 0, 1)
     CopyObject(DerefOf(Index(ppp0, 1)), Local0)
     m1a3(Local0, c00a, 0, 0, 2)
     m381(ts, DerefOf(Local0), 0, 3)
     CopyObject(DerefOf(Index(ppp0, 2)), Local0)
     m1a3(Local0, c00b, 0, 0, 4)
     m382(ts, DerefOf(Local0), 0, 5)
     CopyObject(DerefOf(Index(ppp0, 3)), Local0)
     m1a3(Local0, c00c, 0, 0, 6)
     m383(ts, DerefOf(Local0), 0, 7)
     CopyObject(DerefOf(Index(ppp0, 4)), Local0)
     m1a3(Local0, c00e, 0, 0, 8)
     // Replace
     CopyObject(RefOf(i000), Index(ppp0, 0))
     CopyObject(DerefOf(Index(ppp0, 0)), Local0)
     m1a3(Local0, c009, 0, 0, 9)
     m380(ts, DerefOf(Local0), 0, 10)
     CopyObject(RefOf(s000), Index(ppp0, 0))
     CopyObject(DerefOf(Index(ppp0, 0)), Local0)
     m1a3(Local0, c00a, 0, 0, 11)
     m381(ts, DerefOf(Local0), 0, 12)
     CopyObject(RefOf(b000), Index(ppp0, 0))
     CopyObject(DerefOf(Index(ppp0, 0)), Local0)
     m1a3(Local0, c00b, 0, 0, 13)
     m382(ts, DerefOf(Local0), 0, 14)
     CopyObject(RefOf(p000), Index(ppp0, 0))
     CopyObject(DerefOf(Index(ppp0, 0)), Local0)
     m1a3(Local0, c00c, 0, 0, 15)
     m383(ts, DerefOf(Local0), 0, 16)
     CopyObject(RefOf(d000), Index(ppp0, 0))
     CopyObject(DerefOf(Index(ppp0, 0)), Local0)
     m1a3(Local0, c00e, 0, 0, 17)
     END0()
     */
    }

    /*
     * TEST 53: IRef-LocalX
     */
    Method (M264, 0, NotSerialized)
    {
        TS00 ("m264")
        /* Store */

        M35C ()
        /* CopyObject */

        M35D ()
    }

    Method (M35C, 0, Serialized)
    {
        Name (TS, "m35c")
        Name (P000, Package (0x12){})
        BEG0 (Z111, TS)
        /* Construct the p955-like Package p000 applying LocalX-IRef */

        Store (P956 [0x00], Local0)
        P000 [0x00] = Local0
        Store (P956 [0x01], Local0)
        P000 [0x01] = Local0
        Store (P956 [0x02], Local0)
        P000 [0x02] = Local0
        Store (P956 [0x03], Local0)
        P000 [0x03] = Local0
        Store (P956 [0x04], Local0)
        P000 [0x04] = Local0
        Store (P956 [0x05], Local0)
        P000 [0x05] = Local0
        Store (P956 [0x06], Local0)
        P000 [0x06] = Local0
        Store (P956 [0x07], Local0)
        P000 [0x07] = Local0
        Store (P956 [0x08], Local0)
        P000 [0x08] = Local0
        Store (P956 [0x09], Local0)
        P000 [0x09] = Local0
        Store (P956 [0x0A], Local0)
        P000 [0x0A] = Local0
        Store (P956 [0x0B], Local0)
        P000 [0x0B] = Local0
        Store (P956 [0x0C], Local0)
        P000 [0x0C] = Local0
        Store (P956 [0x0D], Local0)
        P000 [0x0D] = Local0
        Store (P956 [0x0E], Local0)
        P000 [0x0E] = Local0
        Store (P956 [0x0F], Local0)
        P000 [0x0F] = Local0
        Store (P956 [0x10], Local0)
        P000 [0x10] = Local0
        P000 [0x00] = 0x00
        P000 [0x0F] = 0x0F
        P000 [0x10] = 0x10
        /* Verify p955-like Package */

        M1AF (P000, 0x01, 0x00, 0x01)
        M1A6 ()
        END0 ()
    }

    /* CURRENTLY: compiler failed CopyObject(xx, Index(xx,xx)) */

    Method (M35D, 0, NotSerialized)
    {
        /*
     Name(ts, "m35d")
     Name(p000, Package(18) {})
     BEG0(z111, ts)
     // Construct the p955-like Package p000 applying LocalX-IRef
     CopyObject(Index(p956, 0), Local0)
     CopyObject(Local0, Index(p000, 0))
     CopyObject(Index(p956, 1), Local0)
     CopyObject(Local0, Index(p000, 1))
     CopyObject(Index(p956, 2), Local0)
     CopyObject(Local0, Index(p000, 2))
     CopyObject(Index(p956, 3), Local0)
     CopyObject(Local0, Index(p000, 3))
     CopyObject(Index(p956, 4), Local0)
     CopyObject(Local0, Index(p000, 4))
     CopyObject(Index(p956, 5), Local0)
     CopyObject(Local0, Index(p000, 5))
     CopyObject(Index(p956, 6), Local0)
     CopyObject(Local0, Index(p000, 6))
     CopyObject(Index(p956, 7), Local0)
     CopyObject(Local0, Index(p000, 7))
     CopyObject(Index(p956, 8), Local0)
     CopyObject(Local0, Index(p000, 8))
     CopyObject(Index(p956, 9), Local0)
     CopyObject(Local0, Index(p000, 9))
     CopyObject(Index(p956, 10), Local0)
     CopyObject(Local0, Index(p000, 10))
     CopyObject(Index(p956, 11), Local0)
     CopyObject(Local0, Index(p000, 11))
     CopyObject(Index(p956, 12), Local0)
     CopyObject(Local0, Index(p000, 12))
     CopyObject(Index(p956, 13), Local0)
     CopyObject(Local0, Index(p000, 13))
     CopyObject(Index(p956, 14), Local0)
     CopyObject(Local0, Index(p000, 14))
     CopyObject(Index(p956, 15), Local0)
     CopyObject(Local0, Index(p000, 15))
     CopyObject(Index(p956, 16), Local0)
     CopyObject(Local0, Index(p000, 16))
     CopyObject(0, Index(p000, 0))
     CopyObject(15, Index(p000, 15))
     CopyObject(16, Index(p000, 16))
     // Verify p955-like Package
     m1af(p000, 1, 0, 1)
     m1a6()
     END0()
     */
    }

    /*
     * TEST 54: IRef-ArgX
     */
    Method (M265, 0, Serialized)
    {
        Name (TS, "m265")
        TS00 (TS)
        Name (I000, 0x77)
        Name (I010, 0x77)
        /* Store */

        M35E (I000)
        M380 (TS, I000, Z111, 0x00)
        /* CopyObject */

        M35F (I010)
        M380 (TS, I010, Z111, 0x01)
    }

    Method (M35E, 1, Serialized)
    {
        Name (TS, "m35e")
        Name (P000, Package (0x12){})
        BEG0 (Z111, TS)
        /* Construct the p955-like Package p000 applying LocalX-IRef */

        Store (P956 [0x00], Arg0)
        P000 [0x00] = Arg0
        Store (P956 [0x01], Arg0)
        P000 [0x01] = Arg0
        Store (P956 [0x02], Arg0)
        P000 [0x02] = Arg0
        Store (P956 [0x03], Arg0)
        P000 [0x03] = Arg0
        Store (P956 [0x04], Arg0)
        P000 [0x04] = Arg0
        Store (P956 [0x05], Arg0)
        P000 [0x05] = Arg0
        Store (P956 [0x06], Arg0)
        P000 [0x06] = Arg0
        Store (P956 [0x07], Arg0)
        P000 [0x07] = Arg0
        Store (P956 [0x08], Arg0)
        P000 [0x08] = Arg0
        Store (P956 [0x09], Arg0)
        P000 [0x09] = Arg0
        Store (P956 [0x0A], Arg0)
        P000 [0x0A] = Arg0
        Store (P956 [0x0B], Arg0)
        P000 [0x0B] = Arg0
        Store (P956 [0x0C], Arg0)
        P000 [0x0C] = Arg0
        Store (P956 [0x0D], Arg0)
        P000 [0x0D] = Arg0
        Store (P956 [0x0E], Arg0)
        P000 [0x0E] = Arg0
        Store (P956 [0x0F], Arg0)
        P000 [0x0F] = Arg0
        Store (P956 [0x10], Arg0)
        P000 [0x10] = Arg0
        P000 [0x00] = 0x00
        P000 [0x0F] = 0x0F
        P000 [0x10] = 0x10
        /* Verify p955-like Package */

        M1AF (P000, 0x01, 0x00, 0x01)
        M1A6 ()
        END0 ()
    }

    /* CURRENTLY: compiler failed CopyObject(xx, Index(xx,xx)) */

    Method (M35F, 1, NotSerialized)
    {
        /*
     Name(ts, "m35f")
     Name(p000, Package(18) {})
     BEG0(z111, ts)
     // Construct the p955-like Package p000 applying LocalX-IRef
     CopyObject(Index(p956, 0), Arg0)
     CopyObject(Arg0, Index(p000, 0))
     CopyObject(Index(p956, 1), Arg0)
     CopyObject(Arg0, Index(p000, 1))
     CopyObject(Index(p956, 2), Arg0)
     CopyObject(Arg0, Index(p000, 2))
     CopyObject(Index(p956, 3), Arg0)
     CopyObject(Arg0, Index(p000, 3))
     CopyObject(Index(p956, 4), Arg0)
     CopyObject(Arg0, Index(p000, 4))
     CopyObject(Index(p956, 5), Arg0)
     CopyObject(Arg0, Index(p000, 5))
     CopyObject(Index(p956, 6), Arg0)
     CopyObject(Arg0, Index(p000, 6))
     CopyObject(Index(p956, 7), Arg0)
     CopyObject(Arg0, Index(p000, 7))
     CopyObject(Index(p956, 8), Arg0)
     CopyObject(Arg0, Index(p000, 8))
     CopyObject(Index(p956, 9), Arg0)
     CopyObject(Arg0, Index(p000, 9))
     CopyObject(Index(p956, 10), Arg0)
     CopyObject(Arg0, Index(p000, 10))
     CopyObject(Index(p956, 11), Arg0)
     CopyObject(Arg0, Index(p000, 11))
     CopyObject(Index(p956, 12), Arg0)
     CopyObject(Arg0, Index(p000, 12))
     CopyObject(Index(p956, 13), Arg0)
     CopyObject(Arg0, Index(p000, 13))
     CopyObject(Index(p956, 14), Arg0)
     CopyObject(Arg0, Index(p000, 14))
     CopyObject(Index(p956, 15), Arg0)
     CopyObject(Arg0, Index(p000, 15))
     CopyObject(Index(p956, 16), Arg0)
     CopyObject(Arg0, Index(p000, 16))
     CopyObject(0, Index(p000, 0))
     CopyObject(15, Index(p000, 15))
     CopyObject(16, Index(p000, 16))
     // Verify p955-like Package
     m1af(p000, 1, 0, 1)
     m1a6()
     END0()
     */
    }

    /*
     * TEST 55: IRef-NamedX
     */
    Method (M266, 0, Serialized)
    {
        Name (TS, "m266")
        TS00 (TS)
        /* Store */

        If (Y521)
        {
            M360 ()
        }
        Else
        {
            M1AE (TS, "Store IRef to NamedX", "AE_AML_OPERAND_TYPE exception occurs")
        }

        /* CopyObject */

        M361 ()
    }

    Method (M360, 0, Serialized)
    {
        Name (TS, "m360")
        Name (III0, 0x00)
        Name (P000, Package (0x12){})
        BEG0 (Z111, TS)
        /* Construct the p955-like Package p000 applying LocalX-IRef */

        Store (P956 [0x00], III0) /* \M360.III0 */
        P000 [0x00] = III0 /* \M360.III0 */
        Store (P956 [0x01], III0) /* \M360.III0 */
        P000 [0x01] = III0 /* \M360.III0 */
        Store (P956 [0x02], III0) /* \M360.III0 */
        P000 [0x02] = III0 /* \M360.III0 */
        Store (P956 [0x03], III0) /* \M360.III0 */
        P000 [0x03] = III0 /* \M360.III0 */
        Store (P956 [0x04], III0) /* \M360.III0 */
        P000 [0x04] = III0 /* \M360.III0 */
        Store (P956 [0x05], III0) /* \M360.III0 */
        P000 [0x05] = III0 /* \M360.III0 */
        Store (P956 [0x06], III0) /* \M360.III0 */
        P000 [0x06] = III0 /* \M360.III0 */
        Store (P956 [0x07], III0) /* \M360.III0 */
        P000 [0x07] = III0 /* \M360.III0 */
        Store (P956 [0x08], III0) /* \M360.III0 */
        P000 [0x08] = III0 /* \M360.III0 */
        Store (P956 [0x09], III0) /* \M360.III0 */
        P000 [0x09] = III0 /* \M360.III0 */
        Store (P956 [0x0A], III0) /* \M360.III0 */
        P000 [0x0A] = III0 /* \M360.III0 */
        Store (P956 [0x0B], III0) /* \M360.III0 */
        P000 [0x0B] = III0 /* \M360.III0 */
        Store (P956 [0x0C], III0) /* \M360.III0 */
        P000 [0x0C] = III0 /* \M360.III0 */
        Store (P956 [0x0D], III0) /* \M360.III0 */
        P000 [0x0D] = III0 /* \M360.III0 */
        Store (P956 [0x0E], III0) /* \M360.III0 */
        P000 [0x0E] = III0 /* \M360.III0 */
        Store (P956 [0x0F], III0) /* \M360.III0 */
        P000 [0x0F] = III0 /* \M360.III0 */
        Store (P956 [0x10], III0) /* \M360.III0 */
        P000 [0x10] = III0 /* \M360.III0 */
        P000 [0x00] = 0x00
        P000 [0x0F] = 0x0F
        P000 [0x10] = 0x10
        /* Verify p955-like Package */

        M1AF (P000, 0x01, 0x00, 0x01)
        M1A6 ()
        END0 ()
    }

    /* CURRENTLY: compiler failed CopyObject(xx, Index(xx,xx)) */

    Method (M361, 0, NotSerialized)
    {
        /*
     Name(ts, "m361")
     Name(iii0, 0)
     Name(p000, Package(18) {})
     BEG0(z111, ts)
     // Construct the p955-like Package p000 applying LocalX-IRef
     CopyObject(Index(p956, 0), iii0)
     CopyObject(iii0, Index(p000, 0))
     CopyObject(Index(p956, 1), iii0)
     CopyObject(iii0, Index(p000, 1))
     CopyObject(Index(p956, 2), iii0)
     CopyObject(iii0, Index(p000, 2))
     CopyObject(Index(p956, 3), iii0)
     CopyObject(iii0, Index(p000, 3))
     CopyObject(Index(p956, 4), iii0)
     CopyObject(iii0, Index(p000, 4))
     CopyObject(Index(p956, 5), iii0)
     CopyObject(iii0, Index(p000, 5))
     CopyObject(Index(p956, 6), iii0)
     CopyObject(iii0, Index(p000, 6))
     CopyObject(Index(p956, 7), iii0)
     CopyObject(iii0, Index(p000, 7))
     CopyObject(Index(p956, 8), iii0)
     CopyObject(iii0, Index(p000, 8))
     CopyObject(Index(p956, 9), iii0)
     CopyObject(iii0, Index(p000, 9))
     CopyObject(Index(p956, 10), iii0)
     CopyObject(iii0, Index(p000, 10))
     CopyObject(Index(p956, 11), iii0)
     CopyObject(iii0, Index(p000, 11))
     CopyObject(Index(p956, 12), iii0)
     CopyObject(iii0, Index(p000, 12))
     CopyObject(Index(p956, 13), iii0)
     CopyObject(iii0, Index(p000, 13))
     CopyObject(Index(p956, 14), iii0)
     CopyObject(iii0, Index(p000, 14))
     CopyObject(Index(p956, 15), iii0)
     CopyObject(iii0, Index(p000, 15))
     CopyObject(Index(p956, 16), iii0)
     CopyObject(iii0, Index(p000, 16))
     CopyObject(0, Index(p000, 0))
     CopyObject(15, Index(p000, 15))
     CopyObject(16, Index(p000, 16))
     // Verify p955-like Package
     m1af(p000, 1, 0, 1)
     m1a6()
     END0()
     */
    }

    /*
     * TEST 56: IRef-El_of_Package
     */
    Method (M267, 0, Serialized)
    {
        TS00 ("m267")
        Name (P100, Package (0x12){})
        /* Store */

        M25B ()
        If (Q003)
        {
            /* CopyObject */
            /* CopyObject IRef (Index(p955, x)) into Package */
            M353 (P100, 0x01)
            /* Verify p955-like Package */

            M1AF (P100, 0x01, 0x00, 0x01)
            M1A6 ()
        }
    }

    /*
     * TEST 57: Store total
     */
    Method (M268, 0, NotSerialized)
    {
        M1AE ("m268", "Store total", "Not implemented yet")
    }

    /*
     * TEST 58: CopyObject total
     */
    Method (M269, 0, NotSerialized)
    {
        M1AE ("m269", "CopyObject total", "Not implemented yet")
    }

    /*
     * TEST 59: Mix of Store and CopyObject total
     */
    Method (M26A, 0, NotSerialized)
    {
        M1AE ("m26a", "Mix of Store and CopyObject total", "Not implemented yet")
    }

    /*
     * TEST 60: Package total
     */
    Method (M26B, 0, Serialized)
    {
        Name (TS, "m26b")
        TS00 (TS)
        Name (I000, 0x77)
        Name (I001, 0x77)
        /* READ */
        /* m1c1 & m1c2 - perform all the ways reading */
        /* element of Package passed by ArgX. */
        /* Read immediate image element of Package */
        /* */
        /* Package specified by the immediate */
        /* images of {Integer, String, Buffer, Package}. */
        M1C1 ()
        /* Read NamedX element of Package */
        /* {Integer, String, Buffer, Package}. */
        M1C2 ()
        /* Read any type named object element of Package */

        M1AF (P955, 0x01, 0x01, 0x00)
        /* Check Uninitialized element of Package */

        M1C4 ()
        /* The chain of Index_References */

        M1C5 ()
        /* Access to the Method named object element of Package */

        M1C7 ()
        M1C8 ()
        /* Read automatic dereference expected */
        /* when accessing element of Package. */
        M1CE ()
        If (X132)
        {
            M1CF () /* bug 132 */
            M1D0 () /* bug 132 */
        }

        /* WRITE */
        /* Write to element of Package specified as */
        /* immediate IRef passed to method. */
        If (X133)
        {
            M1D9 () /* bug 133 */
            M1DA () /* bug 133 */
        }

        /* EXCEPTIONS */
        /* No read automatic dereference expected */
        M1D1 ()
        If (X127)
        {
            M1D2 () /* bug 127 */
        }

        M1D3 (I000, I001)
        M380 (TS, I000, 0x00, 0x00)
        M380 (TS, I001, 0x00, 0x01)
        If (X127)
        {
            M1D4 (I000, I001) /* bug 127 */
        }

        M380 (TS, I000, 0x00, 0x02)
        M380 (TS, I001, 0x00, 0x03)
        If (X127)
        {
            M1D5 () /* bug 127 */
            M1D6 () /* bug 127 */
            M1DB () /* bug 127 */
        }

        /* Other */

        M1D7 ()
        M1D8 ()
        /* DerefOf of the Method named object element of Package */

        M1C9 ()
        /* Size of Package */
        /* m1ca: bug 129 (not a bug, in case of */
        /* dynamically created Package non-limited */
        /* size Package is allowed. Handled by the */
        /* particular AML opcode VarPackage). */
        M1CA ()
        M1CB ()
    }

    /*
     * TEST 61: String total
     */
    Method (M26C, 0, NotSerialized)
    {
        M1AE ("m26c", "String total", "Not implemented yet")
    }

    /*
     * TEST 62: Buffer total
     */
    Method (M26D, 0, NotSerialized)
    {
        CH03 ("m26d", 0x00, 0x00, 0x0BB5, 0x00)
        M1AE ("m26d", "Buffer total", "Not implemented yet")
        CH03 ("m26d", 0x00, 0x01, 0x0BB7, 0x00)
    }

    /*
     * TEST 63: All the legal ways of WRITING ORef reference to some target location
     */
    Method (M26E, 0, Serialized)
    {
        Name (TS, "m26e")
        If (Y100)
        {
            TS00 (TS)
        }
        Else
        {
            Debug = TS /* \M26E.TS__ */
        }

        CH03 (TS, 0x00, 0x00, 0x0BC7, 0x00)
        /* Store */

        M365 ()
        /* CopyObject */

        M366 ()
        CH03 (TS, 0x00, 0x01, 0x0BCF, 0x00)
    }

    Method (M365, 0, Serialized)
    {
        Name (TS, "m365")
        Name (I000, 0x77)
        Name (I001, 0x77)
        Name (I002, 0x77)
        Name (I003, 0x00)
        Name (I004, 0x77)
        Name (III0, 0x11)
        Name (III1, 0x22)
        Name (III2, 0x33)
        Name (III3, 0x44)
        Name (III4, 0x55)
        Name (III5, 0x66)
        Name (III6, 0x88)
        Name (III7, 0x99)
        Name (PPP0, Package (0x01)
        {
            0x11
        })
        Name (PPP1, Package (0x01){})
        Method (M000, 1, Serialized)
        {
            Name (I002, 0x77)
            Arg0 = RefOf (I002)
            M380 (TS, DerefOf (Arg0), 0x00, 0x00)
            M380 (TS, I002, 0x00, 0x01)
        }

        Method (M001, 1, NotSerialized)
        {
            Arg0 = RefOf (I000)
        }

        Method (M002, 2, NotSerialized)
        {
            Arg0 = 0x00
            M001 (RefOf (Arg0))
            Arg1 = DerefOf (Arg0)
            M380 (TS, Arg1, 0x00, 0x02)
        }

        Method (M003, 0, NotSerialized)
        {
            Local0 = RefOf (III1)
            Return (Local0)
        }

        Method (M004, 1, NotSerialized)
        {
            Local0 = RefOf (III2)
            Return (Local0)
        }

        Method (M009, 0, NotSerialized)
        {
            Return (RefOf (III7))
        }

        Method (M005, 1, NotSerialized)
        {
            DerefOf (Arg0) = RefOf (I000)
        }

        Method (M006, 2, NotSerialized)
        {
            Arg0 = 0x00
            M005 (RefOf (Arg0))
            Arg1 = DerefOf (Arg0)
            M380 (TS, Arg1, 0x00, 0x03)
        }

        Method (M007, 1, NotSerialized)
        {
            Arg0 = RefOf (I004)
        }

        Method (M008, 1, NotSerialized)
        {
            DerefOf (Arg0) = RefOf (I004)
        }

        BEG0 (Z111, TS)
        /* 1. */

        Local0 = RefOf (I000)
        Local1 = DerefOf (Local0)
        M380 (TS, Local1, 0x00, 0x04)
        M380 (TS, I000, 0x00, 0x05)
        /* 2. */

        M000 (I001)
        M380 (TS, I001, 0x00, 0x06)
        /* 3. */

        CopyObject (RefOf (I000), III0) /* \M365.III0 */
        III0 = RefOf (I001)
        Local1 = DerefOf (III0)
        M380 (TS, I001, 0x00, 0x07)
        If (Y523)
        {
            M380 (TS, Local1, 0x00, 0x08)
        }

        /* 4. */

        Local0 = 0x00
        M001 (RefOf (Local0))
        Local1 = DerefOf (Local0)
        M380 (TS, Local1, 0x00, 0x09)
        /* 5. */

        M002 (I001, I002)
        M380 (TS, I001, 0x00, 0x0A)
        M380 (TS, I002, 0x00, 0x0B)
        /* 6. */

        If (Y526)
        {
            CopyObject (RefOf (I003), III5) /* \M365.III5 */
            M007 (RefOf (III5))
            Local1 = DerefOf (III5)
            M380 (TS, Local1, 0x00, 0x0C)
        }

        /* 7. */

        If (Y113)
        {
            M001 (PPP0 [0x00])
            Store (PPP0 [0x00], Local0)
            Local1 = DerefOf (Local0)
            Local2 = DerefOf (Local1)
            M380 (TS, Local2, 0x00, 0x0D)
        }

        /* 8. */

        If (Y525)
        {
            CopyObject (RefOf (III3), III4) /* \M365.III4 */
            RefOf (III4) = RefOf (I000)
            Local1 = DerefOf (III4)
            M380 (TS, I000, 0x00, 0x0E)
            M380 (TS, Local1, 0x00, 0x0F)
        }

        /* 9. */

        PPP1 [0x00] = RefOf (I000)
        Local2 = DerefOf (PPP1 [0x00])
        Local1 = DerefOf (Local2)
        M380 (TS, Local1, 0x00, 0x10)
        M380 (TS, I000, 0x00, 0x11)
        /* 10. */
        /*
         * There are some statements try to pass a value of an integer to a LocalX via reference,
         * But they all use the wrong expression, so they are removed from here.
         */
        /* 11. */
        /* 12. */
        If (Y524)
        {
            Local7 = 0x12
            Local6 = RefOf (Local7)
            DerefOf (Local6) = RefOf (I000)
            Local0 = DerefOf (Local7)
            M380 (TS, Local0, 0x00, 0x18)
            M380 (TS, I000, 0x00, 0x19)
        }

        /* Particular cases of (12): */

        If (Y524)
        {
            /* 13. (4) */

            Local0 = 0x00
            M005 (RefOf (Local0))
            Local1 = DerefOf (Local0)
            M380 (TS, Local1, 0x00, 0x1A)
            /* 14. (5) */

            M006 (I001, I002)
            M380 (TS, I001, 0x00, 0x1B)
            M380 (TS, I002, 0x00, 0x1C)
            /* 15. (6) */

            If (Y526)
            {
                CopyObject (RefOf (I003), III6) /* \M365.III6 */
                M008 (RefOf (III6))
                Local1 = DerefOf (III6)
                M380 (TS, Local1, 0x00, 0x1D)
            }

            /* 16. (7) */

            If (Y113)
            {
                M005 (PPP0 [0x00])
                Store (PPP0 [0x00], Local0)
                Local1 = DerefOf (Local0)
                Local2 = DerefOf (Local1)
                M380 (TS, Local2, 0x00, 0x1E)
            }

            /* 17. (8) */

            If (Y525)
            {
                CopyObject (RefOf (III3), III4) /* \M365.III4 */
                DerefOf (RefOf (III4)) = RefOf (I000)
                Local1 = DerefOf (III4)
                M380 (TS, I000, 0x00, 0x1F)
                M380 (TS, Local1, 0x00, 0x20)
            }

            /* 18. (9) */

            DerefOf (PPP1 [0x00]) = RefOf (I000)
            Local2 = DerefOf (PPP1 [0x00])
            Local1 = DerefOf (Local2)
            M380 (TS, Local1, 0x00, 0x21)
            M380 (TS, I000, 0x00, 0x22)
            /* 19. (10) */

            DerefOf (M003 ()) = RefOf (I000)
            Local1 = DerefOf (III1)
            M380 (TS, I000, 0x00, 0x23)
            M380 (TS, Local1, 0x00, 0x24)
            /* 20. (11) */

            DerefOf (M004 (0x00)) = RefOf (I000)
            Local1 = DerefOf (III2)
            M380 (TS, I000, 0x00, 0x25)
            M380 (TS, Local1, 0x00, 0x26)
        }

        END0 ()
    }

    Method (M366, 0, Serialized)
    {
        Name (TS, "m366")
        Name (I000, 0x77)
        Name (I001, 0x77)
        Name (I002, 0x77)
        Name (III0, 0x00)
        Name (III1, 0x00)
        Name (PPP0, Package (0x01){})
        Name (PPP1, Package (0x01)
        {
            0x00
        })
        Method (M000, 1, Serialized)
        {
            Name (I002, 0x77)
            CopyObject (RefOf (I002), Arg0)
            M380 (TS, DerefOf (Arg0), 0x00, 0x00)
            M380 (TS, I002, 0x00, 0x01)
        }

        Method (M001, 1, NotSerialized)
        {
            CopyObject (RefOf (I000), Arg0)
        }

        Method (M002, 2, NotSerialized)
        {
            Arg0 = 0x00
            M001 (RefOf (Arg0))
            Arg1 = DerefOf (Arg0)
            M380 (TS, Arg1, 0x00, 0x02)
        }

        BEG0 (Z111, TS)
        /* 21. */

        CopyObject (RefOf (I000), Local0)
        Local1 = DerefOf (Local0)
        M380 (TS, Local1, 0x00, 0x03)
        M380 (TS, I000, 0x00, 0x04)
        /* 22. */

        M000 (I001)
        M380 (TS, I001, 0x00, 0x05)
        /* 23. */

        If (Y128)
        {
            CopyObject (RefOf (I000), III0) /* \M366.III0 */
            Local1 = DerefOf (III0)
            M380 (TS, Local1, 0x00, 0x06)
            M380 (TS, I000, 0x00, 0x07)
        }

        /* 24. */

        Local0 = 0x00
        M001 (RefOf (Local0))
        Local1 = DerefOf (Local0)
        M380 (TS, Local1, 0x00, 0x08)
        /* 25. */

        M002 (I001, I002)
        M380 (TS, I001, 0x00, 0x09)
        M380 (TS, I002, 0x00, 0x0A)
        /* 26. */

        If (Y526)
        {
            III1 = 0x00
            M001 (RefOf (III1))
            Local1 = DerefOf (III1)
            M380 (TS, Local1, 0x00, 0x0B)
        }

        /* 27. */

        If (Y113)
        {
            M001 (PPP1 [0x00])
            Store (PPP1 [0x00], Local0)
            Local1 = DerefOf (Local0)
            Local2 = DerefOf (Local1)
            M380 (TS, Local2, 0x00, 0x0C)
        }

        /*
         * 28. (Compiler failed)
         *
         * CopyObject(RefOf(i000), Index(ppp0, 0))
         * Store(DerefOf(Index(ppp0, 0)), Local2)
         * Store(DerefOf(Local2), Local1)
         * m380(ts, Local1, 0, 13)
         * m380(ts, i000, 0, 14)
         */
        END0 ()
    }

    /*
     * TEST 64: All the legal ways of WRITING IRef reference to some target location
     */
    Method (M26F, 0, NotSerialized)
    {
        CH03 ("m26f", 0x00, 0x00, 0x0D1E, 0x00)
        M1AE ("m26f", "All the legal ways of writing IRef reference to some target location", "Not implemented yet")
        CH03 ("m26f", 0x00, 0x01, 0x0D23, 0x00)
    }

    /*
     * TEST 65: All the legal SOURCES of references (both ORef and IRef)
     */
    Method (M270, 0, Serialized)
    {
        Name (TS, "m270")
        CH03 (TS, 0x00, 0x00, 0x0D2D, 0x00)
        If (Y100)
        {
            TS00 (TS)
        }
        Else
        {
            Debug = TS /* \M270.TS__ */
        }

        CH03 (TS, 0x00, 0x01, 0x0D35, 0x00)
        /* Store */

        M367 ()
        CH03 (TS, 0x00, 0x02, 0x0D3A, 0x00)
        /* CopyObject */

        M368 ()
        CH03 (TS, 0x00, 0x03, 0x0D3F, 0x00)
        M1AE ("m270", "All the legal sources of references (ORef and IRef)", "Started, but not implemented yet")
        CH03 (TS, 0x00, 0x04, 0x0D44, 0x00)
    }

    Method (M367, 0, Serialized)
    {
        Name (TS, "m367")
        Name (I000, 0x77)
        Name (I001, 0x77)
        Name (I002, 0x77)
        Name (I003, 0x77)
        Name (I004, 0x77)
        Name (I005, 0x77)
        Name (I006, 0x77)
        Name (III0, 0x11)
        Name (III1, 0x22)
        Method (M001, 7, NotSerialized)
        {
            Local0 = RefOf (I000)
            Arg0 = Local0
            Arg1 = Local0
            Arg2 = Local0
            Arg3 = Local0
            Arg4 = Local0
            Arg5 = Local0
            Arg6 = Local0
            Local7 = DerefOf (Arg0)
            M380 (TS, Local7, 0x00, 0x00)
            Local7 = DerefOf (Arg1)
            M380 (TS, Local7, 0x00, 0x01)
            Local7 = DerefOf (Arg2)
            M380 (TS, Local7, 0x00, 0x02)
            Local7 = DerefOf (Arg3)
            M380 (TS, Local7, 0x00, 0x03)
            Local7 = DerefOf (Arg4)
            M380 (TS, Local7, 0x00, 0x04)
            Local7 = DerefOf (Arg5)
            M380 (TS, Local7, 0x00, 0x05)
            Local7 = DerefOf (Arg6)
            M380 (TS, Local7, 0x00, 0x06)
        }

        Method (M002, 7, NotSerialized)
        {
            Arg0 = RefOf (I000)
            Arg1 = Arg0
            Arg2 = Arg1
            Arg3 = Arg2
            Arg4 = Arg3
            Arg5 = Arg4
            Arg6 = Arg5
            M380 (TS, DerefOf (Arg6), 0x00, 0x07)
            Arg6 = DerefOf (Arg0)
            M380 (TS, Arg6, 0x00, 0x08)
            Arg6 = DerefOf (Arg1)
            M380 (TS, Arg6, 0x00, 0x09)
            Arg6 = DerefOf (Arg2)
            M380 (TS, Arg6, 0x00, 0x0A)
            Arg6 = DerefOf (Arg3)
            M380 (TS, Arg6, 0x00, 0x0B)
            Arg6 = DerefOf (Arg4)
            M380 (TS, Arg6, 0x00, 0x0C)
            Arg6 = DerefOf (Arg5)
            M380 (TS, Arg6, 0x00, 0x0D)
        }

        BEG0 (Z111, TS)
        /* 1. ORef-LocalX */

        Local0 = RefOf (I000)
        Local1 = Local0
        Local2 = Local1
        Local3 = Local2
        Local4 = Local3
        Local5 = Local4
        Local6 = Local5
        Local7 = Local6
        M380 (TS, DerefOf (Local7), 0x00, 0x0E)
        Local7 = DerefOf (Local0)
        M380 (TS, Local7, 0x00, 0x0F)
        Local7 = DerefOf (Local1)
        M380 (TS, Local7, 0x00, 0x10)
        Local7 = DerefOf (Local2)
        M380 (TS, Local7, 0x00, 0x11)
        Local7 = DerefOf (Local3)
        M380 (TS, Local7, 0x00, 0x12)
        Local7 = DerefOf (Local4)
        M380 (TS, Local7, 0x00, 0x13)
        Local7 = DerefOf (Local5)
        M380 (TS, Local7, 0x00, 0x14)
        Local7 = DerefOf (Local6)
        M380 (TS, Local7, 0x00, 0x15)
        /* 2. ORef-LocalX */

        M001 (I000, I001, I002, I003, I004, I005, I006)
        M380 (TS, I000, 0x00, 0x16)
        M380 (TS, I001, 0x00, 0x17)
        M380 (TS, I002, 0x00, 0x18)
        M380 (TS, I003, 0x00, 0x19)
        M380 (TS, I004, 0x00, 0x1A)
        M380 (TS, I005, 0x00, 0x1B)
        M380 (TS, I006, 0x00, 0x1C)
        If (Y134)
        {
            /* 2. ORef-ArgX */

            M002 (I000, I001, I002, I003, I004, I005, I006)
            M380 (TS, I000, 0x00, 0x1D)
            M380 (TS, I001, 0x00, 0x1E)
            M380 (TS, I002, 0x00, 0x1F)
            M380 (TS, I003, 0x00, 0x20)
            M380 (TS, I004, 0x00, 0x21)
            M380 (TS, I005, 0x00, 0x22)
            M380 (TS, I006, 0x00, 0x23)
        }

        /* 3. ORef-LocalX */

        If (X128)
        {
            /* This operation causes Bug 128 */

            CopyObject (RefOf (III1), III0) /* \M367.III0 */
            Local0 = RefOf (I000)
            III0 = Local0
            Local1 = DerefOf (III0)
            M380 (TS, I000, 0x00, 0x24)
            If (Y523)
            {
                M380 (TS, Local1, 0x00, 0x25)
            }
        }

        END0 ()
    }

    Method (M368, 0, Serialized)
    {
        Name (TS, "m368")
        Name (I000, 0x77)
        BEG0 (Z111, TS)
        /* 21. ORef-LocalX */

        CopyObject (RefOf (I000), Local0)
        CopyObject (Local0, Local1)
        CopyObject (Local1, Local2)
        CopyObject (Local2, Local3)
        CopyObject (Local3, Local4)
        CopyObject (Local4, Local5)
        CopyObject (Local5, Local6)
        CopyObject (Local6, Local7)
        M380 (TS, DerefOf (Local7), 0x00, 0x00)
        CopyObject (DerefOf (Local0), Local7)
        M380 (TS, Local7, 0x00, 0x01)
        CopyObject (DerefOf (Local1), Local7)
        M380 (TS, Local7, 0x00, 0x02)
        CopyObject (DerefOf (Local2), Local7)
        M380 (TS, Local7, 0x00, 0x03)
        CopyObject (DerefOf (Local3), Local7)
        M380 (TS, Local7, 0x00, 0x04)
        CopyObject (DerefOf (Local4), Local7)
        M380 (TS, Local7, 0x00, 0x05)
        CopyObject (DerefOf (Local5), Local7)
        M380 (TS, Local7, 0x00, 0x06)
        CopyObject (DerefOf (Local6), Local7)
        M380 (TS, Local7, 0x00, 0x07)
        END0 ()
    }

    /*
     * Separately (though such are already):
     * put reference into element of Package
     * and then write another reference into
     * that element of that Package.
     * No any correlation must be.
     */
    Name (I003, 0x12345678)
    Name (P090, Package (0x09){})
    Name (P091, Package (0x09)
    {
        0x01, 
        0x02, 
        0x03, 
        0x04, 
        0x05, 
        0x06, 
        0x07, 
        0x08, 
        0x09
    })
    Method (M271, 2, NotSerialized)
    {
        P090 [Arg1] = Arg0
    }

    /* IRef upon IRef */

    Method (M272, 0, NotSerialized)
    {
        M271 (P091 [0x01], 0x03)
        M271 (P091 [0x01], 0x03)
    }

    /* IRef upon ORef */

    Method (M273, 0, NotSerialized)
    {
        M271 (RefOf (I003), 0x04)
        M271 (P091 [0x01], 0x04)
    }

    /* ORef upon IRef */

    Method (M274, 0, NotSerialized)
    {
        M271 (P091 [0x01], 0x05)
        M271 (RefOf (I003), 0x05)
    }

    /* ORef upon ORef */

    Method (M275, 0, NotSerialized)
    {
        M271 (RefOf (I003), 0x06)
        M271 (RefOf (I003), 0x06)
    }

    Method (M276, 0, NotSerialized)
    {
        M272 ()
        M273 ()
        M274 ()
        M275 ()
    }

    /*
     *
     * Simple Tests
     *
     */
    /* Simple TEST 1: read of ArgX-ORef with DerefOf */
    Method (M341, 0, Serialized)
    {
        Name (TS, "m341")
        Name (I000, 0x19283746)
        Local0 = RefOf (I000)
        Method (M000, 1, NotSerialized)
        {
            Local0 = DerefOf (Arg0)
            Local7 = (Local0 + 0x05)
            If ((Local7 != 0x1928374B))
            {
                ERR (TS, Z111, 0x0E3E, 0x00, 0x00, Local7, 0x1928374B)
            }
        }

        M000 (Local0)
    }

    /* Simple TEST 2: read of ArgX-ORef without DerefOf */

    Method (M342, 0, Serialized)
    {
        Name (TS, "m342")
        Name (I000, 0x00)
        BEG0 (Z111, TS)
        Local0 = RefOf (I000)
        M1CC (TS, Local0, 0x01, 0x00)
        M1CD (TS, Local0, 0x01, 0x00)
        M1CC (TS, RefOf (I000), 0x01, 0x00)
        M1CD (TS, RefOf (I000), 0x01, 0x00)
        END0 ()
    }

    /* Simple TEST 3: read of ArgX-IRef with DerefOf */

    Method (M343, 0, Serialized)
    {
        Name (TS, "m343")
        Name (P000, Package (0x05)
        {
            0x0B, 
            0x0C, 
            0x0D, 
            0x0E, 
            0x0F
        })
        Store (P000 [0x03], Local0)
        Method (M000, 1, NotSerialized)
        {
            Local0 = DerefOf (Arg0)
            Local7 = (Local0 + 0x05)
            If ((Local7 != 0x13))
            {
                ERR (TS, Z111, 0x0E66, 0x00, 0x00, Local7, 0x13)
            }
        }

        M000 (Local0)
    }

    /* Simple TEST 4: read of ArgX-IRef without DerefOf */

    Method (M344, 0, Serialized)
    {
        Name (TS, "m344")
        Name (P000, Package (0x05)
        {
            0x0B, 
            0x0C, 
            0x0D, 
            0x0E, 
            0x0F
        })
        Store (P000 [0x03], Local0)
        Method (M000, 1, NotSerialized)
        {
            Local7 = (Arg0 + 0x05)
            If ((Local7 != 0x13))
            {
                ERR (TS, Z111, 0x0E79, 0x00, 0x00, Local7, 0x13)
            }
        }

        M000 (Local0)
    }

    /* Simple TEST 8 */

    Method (M345, 0, Serialized)
    {
        Name (TS, "m345")
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
        Name (S010, "qwer0000")
        Name (B010, Buffer (0x04)
        {
             0x01, 0x77, 0x03, 0x04                           // .w..
        })
        Name (P010, Package (0x03)
        {
            0x05, 
            0x77, 
            0x07
        })
        /* Store to reference keeping in LocalX */

        Method (M000, 1, NotSerialized)
        {
            Local1 = Local0 = Arg0 [0x01]
            Local0 = 0x90
            If ((Local0 != 0x90))
            {
                ERR (TS, Z111, 0x0E94, 0x00, 0x00, Local0, 0x90)
            }

            Local1 = 0x91
            If ((Local1 != 0x91))
            {
                ERR (TS, Z111, 0x0E98, 0x00, 0x00, Local1, 0x91)
            }
        }

        /* CopyObject to reference keeping in LocalX */

        Method (M001, 1, NotSerialized)
        {
            Local1 = Local0 = Arg0 [0x01]
            CopyObject (0x94, Local0)
            If ((Local0 != 0x94))
            {
                ERR (TS, Z111, 0x0EA3, 0x00, 0x00, Local0, 0x94)
            }

            CopyObject (0x95, Local1)
            If ((Local1 != 0x95))
            {
                ERR (TS, Z111, 0x0EA7, 0x00, 0x00, Local1, 0x95)
            }
        }

        /* Store to reference immediately */

        Method (M002, 1, NotSerialized)
        {
            Arg0 [0x01] = 0x2B
        }

        /* Store to reference immediately */

        Method (M003, 1, NotSerialized)
        {
            Local0 = Arg0 [0x01]
            Arg0 [0x01] = 0x2B
        }

        /* CopyObject to reference immediately */

        Method (M004, 1, NotSerialized)
        {
                /* CopyObject(0x96, Index(arg0, 1)) */
        /* CopyObject(0x97, Index(arg0, 1, Local0)) */
        }

        BEG0 (Z111, TS)
        M000 (S000)
        M000 (B000)
        M000 (P000)
        M381 (TS, S000, 0x00, 0x00)
        M382 (TS, B000, 0x00, 0x01)
        M383 (TS, P000, 0x00, 0x02)
        M001 (S000)
        M001 (B000)
        M001 (P000)
        M381 (TS, S000, 0x00, 0x03)
        M382 (TS, B000, 0x00, 0x04)
        M383 (TS, P000, 0x00, 0x05)
        M002 (S000)
        M002 (B000)
        M002 (P000)
        M385 (TS, S000, 0x00, 0x06)
        M386 (TS, B000, 0x00, 0x07)
        M387 (TS, P000, 0x00, 0x08)
        M003 (S010)
        M003 (B010)
        M003 (P010)
        M385 (TS, S010, 0x00, 0x09)
        M386 (TS, B010, 0x00, 0x0A)
        M387 (TS, P010, 0x00, 0x0B)
        END0 ()
    }

    Method (M346, 0, Serialized)
    {
        Name (TS, "m346")
        Name (I000, 0xABCD0000)
        Method (M000, 1, NotSerialized)
        {
            Local0 = RefOf (Arg0)
            Local6 = DerefOf (Local0)
            RefOf (Arg0) = 0x11111111
            /* CopyObject(0x11111111, RefOf(arg0)) */

            Local7 = DerefOf (Local0)
            Local1 = ObjectType (Local0)
            If ((Local1 != C009))
            {
                ERR (TS, Z111, 0x0EF6, 0x00, 0x00, Local1, C009)
            }
            Else
            {
                Local1 = SizeOf (Local0)
                If ((Local1 != ISZ0))
                {
                    ERR (TS, Z111, 0x0EFA, 0x00, 0x00, Local1, ISZ0)
                }

                If ((Local6 != 0xABCD0000))
                {
                    ERR (TS, Z111, 0x0EFD, 0x00, 0x00, Local6, 0xABCD0000)
                }

                If ((Local7 != 0x11111111))
                {
                    ERR (TS, Z111, 0x0F00, 0x00, 0x00, Local7, 0x11111111)
                }
            }
        }

        M000 (I000)
        If ((I000 != 0xABCD0000))
        {
            ERR (TS, Z111, 0x0F07, 0x00, 0x00, I000, 0xABCD0000)
        }
    }

    Method (M347, 0, Serialized)
    {
        Name (TS, "m347")
        Name (I000, 0xABCD0000)
        Method (M000, 1, NotSerialized)
        {
            Local0 = DerefOf (RefOf (Arg0))
            Local1 = ObjectType (Local0)
            If ((Local1 != C009))
            {
                ERR (TS, Z111, 0x0F16, 0x00, 0x00, Local1, C009)
            }
            Else
            {
                Local1 = SizeOf (Local0)
                If ((Local1 != ISZ0))
                {
                    ERR (TS, Z111, 0x0F1A, 0x00, 0x00, Local1, ISZ0)
                }

                If ((Local0 != 0xABCD0000))
                {
                    ERR (TS, Z111, 0x0F1D, 0x00, 0x00, Local0, 0xABCD0000)
                }
            }
        }

        M000 (I000)
        If ((I000 != 0xABCD0000))
        {
            ERR (TS, Z111, 0x0F24, 0x00, 0x00, I000, 0xABCD0000)
        }
    }

    Method (M348, 0, Serialized)
    {
        Name (TS, "m348")
        Name (I000, 0xABCD0000)
        Method (M000, 1, NotSerialized)
        {
            Local0 = RefOf (Arg0)
            Local1 = DerefOf (Local0)
            Local2 = DerefOf (Local1)
            If ((Local2 != 0xABCD0000))
            {
                ERR (TS, Z111, 0x0F34, 0x00, 0x00, Local2, 0xABCD0000)
            }

            RefOf (Arg0) = 0x11111111
            Local0 = RefOf (Arg0)
            Local0 = 0x11111111
            If ((Local0 != 0x11111111))
            {
                ERR (TS, Z111, 0x0F3C, 0x00, 0x00, Local0, 0x11111111)
            }
        }

        M000 (RefOf (I000))
        If ((I000 != 0xABCD0000))
        {
            ERR (TS, Z111, 0x0F42, 0x00, 0x00, I000, 0xABCD0000)
        }

        Local0 = RefOf (I000)
        M000 (Local0)
        If ((I000 != 0xABCD0000))
        {
            ERR (TS, Z111, 0x0F48, 0x00, 0x00, I000, 0xABCD0000)
        }

        Local2 = DerefOf (Local0)
        If ((Local2 != 0xABCD0000))
        {
            ERR (TS, Z111, 0x0F4C, 0x00, 0x00, Local2, 0xABCD0000)
        }
    }

    Method (M349, 0, Serialized)
    {
        Name (TS, "m349")
        Name (I000, 0xABCD0000)
        Name (I001, 0xABCD0001)
        Method (M000, 1, NotSerialized)
        {
            Local1 = DerefOf (RefOf (Arg0))
            Local2 = DerefOf (Local1)
            If ((Local2 != 0xABCD0000))
            {
                ERR (TS, Z111, 0x0F5C, 0x00, 0x00, Local2, 0xABCD0000)
            }
        }

        Method (M001, 1, NotSerialized)
        {
            DerefOf (RefOf (Arg0)) = 0x11111111
                /* CopyObject(0x11111111, DerefOf(RefOf(arg0))) */
        }

        /* Reading */

        M000 (RefOf (I000))
        If ((I000 != 0xABCD0000))
        {
            ERR (TS, Z111, 0x0F6A, 0x00, 0x00, I000, 0xABCD0000)
        }

        Local0 = RefOf (I000)
        M000 (Local0)
        If ((I000 != 0xABCD0000))
        {
            ERR (TS, Z111, 0x0F70, 0x00, 0x00, I000, 0xABCD0000)
        }

        If (Y512)
        {
            Local2 = DerefOf (Local0)
            If ((Local2 != 0xABCD0000))
            {
                ERR (TS, Z111, 0x0F75, 0x00, 0x00, Local2, 0xABCD0000)
            }
        }

        /* Writing */

        M001 (RefOf (I001))
        If ((I001 != 0x11111111))
        {
            ERR (TS, Z111, 0x0F7D, 0x00, 0x00, I001, 0x11111111)
        }

        Local0 = RefOf (I001)
        M001 (Local0)
        If ((I001 != 0x11111111))
        {
            ERR (TS, Z111, 0x0F83, 0x00, 0x00, I001, 0x11111111)
        }

        If (Y512)
        {
            Local2 = DerefOf (Local0)
            If ((Local2 != 0x11111111))
            {
                ERR (TS, Z111, 0x0F88, 0x00, 0x00, Local2, 0x11111111)
            }
        }
    }

    Method (M34A, 0, Serialized)
    {
        Name (TS, "m34a")
        Name (B000, Buffer (0x05)
        {
             0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
        })
        Method (M000, 1, NotSerialized)
        {
            Local2 = DerefOf (Arg0)
            If ((Local2 != 0x69))
            {
                ERR (TS, Z111, 0x0F97, 0x00, 0x00, Local2, 0x69)
            }
        }

        /* The same but use RefOf and than back DerefOf */

        Method (M001, 1, NotSerialized)
        {
            Local0 = RefOf (Arg0)
            Local1 = DerefOf (Local0)
            Local2 = DerefOf (Local1)
            If ((Local2 != 0x69))
            {
                ERR (TS, Z111, 0x0FA3, 0x00, 0x00, Local2, 0x69)
            }
        }

        Method (M002, 1, NotSerialized)
        {
            RefOf (Arg0) = 0x11111111
            Local0 = RefOf (Arg0)
            Local0 = 0x11111111
            If ((Local0 != 0x11111111))
            {
                ERR (TS, Z111, 0x0FAE, 0x00, 0x00, Local0, 0x11111111)
            }
        }

        /* m000 */

        M000 (B000 [0x02])
        If ((B000 != Buffer (0x05)
                    {
                         0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                    }))
        {
            ERR (TS, Z111, 0x0FB6, 0x00, 0x00, B000, Buffer (0x05)
                {
                     0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                })
        }

        Store (B000 [0x02], Local0)
        M000 (Local0)
        If ((B000 != Buffer (0x05)
                    {
                         0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                    }))
        {
            ERR (TS, Z111, 0x0FBC, 0x00, 0x00, B000, Buffer (0x05)
                {
                     0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                })
        }

        Local2 = DerefOf (Local0)
        If ((Local2 != 0x69))
        {
            ERR (TS, Z111, 0x0FC0, 0x00, 0x00, Local2, 0x69)
        }

        Local1 = Local0 = B000 [0x02]
        M000 (Local0)
        If ((B000 != Buffer (0x05)
                    {
                         0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                    }))
        {
            ERR (TS, Z111, 0x0FC6, 0x00, 0x00, B000, Buffer (0x05)
                {
                     0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                })
        }

        Local2 = DerefOf (Local0)
        If ((Local2 != 0x69))
        {
            ERR (TS, Z111, 0x0FCA, 0x00, 0x00, Local2, 0x69)
        }

        M000 (Local1)
        If ((B000 != Buffer (0x05)
                    {
                         0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                    }))
        {
            ERR (TS, Z111, 0x0FCE, 0x00, 0x00, B000, Buffer (0x05)
                {
                     0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                })
        }

        Local2 = DerefOf (Local1)
        If ((Local2 != 0x69))
        {
            ERR (TS, Z111, 0x0FD2, 0x00, 0x00, Local2, 0x69)
        }

        /* m001 */

        M001 (B000 [0x02])
        If ((B000 != Buffer (0x05)
                    {
                         0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                    }))
        {
            ERR (TS, Z111, 0x0FD9, 0x00, 0x00, B000, Buffer (0x05)
                {
                     0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                })
        }

        Store (B000 [0x02], Local0)
        M001 (Local0)
        If ((B000 != Buffer (0x05)
                    {
                         0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                    }))
        {
            ERR (TS, Z111, 0x0FDF, 0x00, 0x00, B000, Buffer (0x05)
                {
                     0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                })
        }

        Local2 = DerefOf (Local0)
        If ((Local2 != 0x69))
        {
            ERR (TS, Z111, 0x0FE3, 0x00, 0x00, Local2, 0x69)
        }

        Local1 = Local0 = B000 [0x02]
        M001 (Local0)
        If ((B000 != Buffer (0x05)
                    {
                         0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                    }))
        {
            ERR (TS, Z111, 0x0FE9, 0x00, 0x00, B000, Buffer (0x05)
                {
                     0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                })
        }

        Local2 = DerefOf (Local0)
        If ((Local2 != 0x69))
        {
            ERR (TS, Z111, 0x0FED, 0x00, 0x00, Local2, 0x69)
        }

        M001 (Local1)
        If ((B000 != Buffer (0x05)
                    {
                         0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                    }))
        {
            ERR (TS, Z111, 0x0FF1, 0x00, 0x00, B000, Buffer (0x05)
                {
                     0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                })
        }

        Local2 = DerefOf (Local1)
        If ((Local2 != 0x69))
        {
            ERR (TS, Z111, 0x0FF5, 0x00, 0x00, Local2, 0x69)
        }

        /* m002 */

        M002 (B000 [0x02])
        If ((B000 != Buffer (0x05)
                    {
                         0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                    }))
        {
            ERR (TS, Z111, 0x0FFC, 0x00, 0x00, B000, Buffer (0x05)
                {
                     0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                })
        }

        Store (B000 [0x02], Local0)
        M002 (Local0)
        If ((B000 != Buffer (0x05)
                    {
                         0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                    }))
        {
            ERR (TS, Z111, 0x1002, 0x00, 0x00, B000, Buffer (0x05)
                {
                     0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                })
        }

        Local2 = DerefOf (Local0)
        If ((Local2 != 0x69))
        {
            ERR (TS, Z111, 0x1006, 0x00, 0x00, Local2, 0x69)
        }

        Local1 = Local0 = B000 [0x02]
        M002 (Local0)
        If ((B000 != Buffer (0x05)
                    {
                         0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                    }))
        {
            ERR (TS, Z111, 0x100C, 0x00, 0x00, B000, Buffer (0x05)
                {
                     0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                })
        }

        Local2 = DerefOf (Local0)
        If ((Local2 != 0x69))
        {
            ERR (TS, Z111, 0x1010, 0x00, 0x00, Local2, 0x69)
        }

        M002 (Local1)
        If ((B000 != Buffer (0x05)
                    {
                         0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                    }))
        {
            ERR (TS, Z111, 0x1014, 0x00, 0x00, B000, Buffer (0x05)
                {
                     0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                })
        }

        Local2 = DerefOf (Local1)
        If ((Local2 != 0x69))
        {
            ERR (TS, Z111, 0x1018, 0x00, 0x00, Local2, 0x69)
        }
    }

    Method (M34B, 0, Serialized)
    {
        Name (TS, "m34b")
        Name (B000, Buffer (0x05)
        {
             0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
        })
        Name (B001, Buffer (0x05)
        {
             0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
        })
        Method (M000, 1, NotSerialized)
        {
            Local2 = DerefOf (Arg0)
            If ((Local2 != 0x69))
            {
                ERR (TS, Z111, 0x1027, 0x00, 0x00, Local2, 0x69)
            }
        }

        /* The same but use RefOf and than back DerefOf */

        Method (M001, 1, NotSerialized)
        {
            Local1 = DerefOf (RefOf (Arg0))
            Local2 = DerefOf (Local1)
            If ((Local2 != 0x69))
            {
                ERR (TS, Z111, 0x1032, 0x00, 0x00, Local2, 0x69)
            }
        }

        Method (M002, 1, NotSerialized)
        {
            DerefOf (RefOf (Arg0)) = 0x11111111
                /* CopyObject(0x11111111, DerefOf(RefOf(arg0))) */
        }

        /* m000 */

        M000 (B000 [0x02])
        If ((B000 != Buffer (0x05)
                    {
                         0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                    }))
        {
            ERR (TS, Z111, 0x1040, 0x00, 0x00, B000, Buffer (0x05)
                {
                     0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                })
        }

        Store (B000 [0x02], Local0)
        M000 (Local0)
        If ((B000 != Buffer (0x05)
                    {
                         0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                    }))
        {
            ERR (TS, Z111, 0x1046, 0x00, 0x00, B000, Buffer (0x05)
                {
                     0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                })
        }

        Local2 = DerefOf (Local0)
        If ((Local2 != 0x69))
        {
            ERR (TS, Z111, 0x104A, 0x00, 0x00, Local2, 0x69)
        }

        Local1 = Local0 = B000 [0x02]
        M000 (Local0)
        If ((B000 != Buffer (0x05)
                    {
                         0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                    }))
        {
            ERR (TS, Z111, 0x1050, 0x00, 0x00, B000, Buffer (0x05)
                {
                     0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                })
        }

        Local2 = DerefOf (Local0)
        If ((Local2 != 0x69))
        {
            ERR (TS, Z111, 0x1054, 0x00, 0x00, Local2, 0x69)
        }

        M000 (Local1)
        If ((B000 != Buffer (0x05)
                    {
                         0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                    }))
        {
            ERR (TS, Z111, 0x1058, 0x00, 0x00, B000, Buffer (0x05)
                {
                     0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                })
        }

        Local2 = DerefOf (Local1)
        If ((Local2 != 0x69))
        {
            ERR (TS, Z111, 0x105C, 0x00, 0x00, Local2, 0x69)
        }

        /* m001 */

        M001 (B000 [0x02])
        If ((B000 != Buffer (0x05)
                    {
                         0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                    }))
        {
            ERR (TS, Z111, 0x1063, 0x00, 0x00, B000, Buffer (0x05)
                {
                     0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                })
        }

        Store (B000 [0x02], Local0)
        M001 (Local0)
        If ((B000 != Buffer (0x05)
                    {
                         0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                    }))
        {
            ERR (TS, Z111, 0x1069, 0x00, 0x00, B000, Buffer (0x05)
                {
                     0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                })
        }

        If (Y512)
        {
            Local2 = DerefOf (Local0)
            If ((Local2 != 0x69))
            {
                ERR (TS, Z111, 0x106E, 0x00, 0x00, Local2, 0x69)
            }
        }

        Local1 = Local0 = B000 [0x02]
        M001 (Local0)
        If ((B000 != Buffer (0x05)
                    {
                         0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                    }))
        {
            ERR (TS, Z111, 0x1075, 0x00, 0x00, B000, Buffer (0x05)
                {
                     0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                })
        }

        If (Y512)
        {
            Local2 = DerefOf (Local0)
            If ((Local2 != 0x69))
            {
                ERR (TS, Z111, 0x107A, 0x00, 0x00, Local2, 0x69)
            }
        }

        M001 (Local1)
        If ((B000 != Buffer (0x05)
                    {
                         0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                    }))
        {
            ERR (TS, Z111, 0x107F, 0x00, 0x00, B000, Buffer (0x05)
                {
                     0x01, 0x02, 0x69, 0x04, 0x05                     // ..i..
                })
        }

        If (Y512)
        {
            Local2 = DerefOf (Local1)
            If ((Local2 != 0x69))
            {
                ERR (TS, Z111, 0x1084, 0x00, 0x00, Local2, 0x69)
            }
        }

        /* m002 */

        M002 (B000 [0x02])
        If ((B000 != Buffer (0x05)
                    {
                         0x01, 0x02, 0x11, 0x04, 0x05                     // .....
                    }))
        {
            ERR (TS, Z111, 0x108C, 0x00, 0x00, B000, Buffer (0x05)
                {
                     0x01, 0x02, 0x11, 0x04, 0x05                     // .....
                })
        }

        Store (B000 [0x02], Local0)
        M002 (Local0)
        If ((B000 != Buffer (0x05)
                    {
                         0x01, 0x02, 0x11, 0x04, 0x05                     // .....
                    }))
        {
            ERR (TS, Z111, 0x1092, 0x00, 0x00, B000, Buffer (0x05)
                {
                     0x01, 0x02, 0x11, 0x04, 0x05                     // .....
                })
        }

        If (Y512)
        {
            Local2 = DerefOf (Local0)
            If ((Local2 != 0x11))
            {
                ERR (TS, Z111, 0x1097, 0x00, 0x00, Local2, 0x11)
            }
        }

        Local1 = Local0 = B000 [0x02]
        M002 (Local0)
        If ((B000 != Buffer (0x05)
                    {
                         0x01, 0x02, 0x11, 0x04, 0x05                     // .....
                    }))
        {
            ERR (TS, Z111, 0x109E, 0x00, 0x00, B000, Buffer (0x05)
                {
                     0x01, 0x02, 0x11, 0x04, 0x05                     // .....
                })
        }

        If (Y512)
        {
            Local2 = DerefOf (Local0)
            If ((Local2 != 0x11))
            {
                ERR (TS, Z111, 0x10A3, 0x00, 0x00, Local2, 0x11)
            }
        }

        M002 (Local1)
        If ((B000 != Buffer (0x05)
                    {
                         0x01, 0x02, 0x11, 0x04, 0x05                     // .....
                    }))
        {
            ERR (TS, Z111, 0x10A8, 0x00, 0x00, B000, Buffer (0x05)
                {
                     0x01, 0x02, 0x11, 0x04, 0x05                     // .....
                })
        }

        If (Y512)
        {
            Local2 = DerefOf (Local1)
            If ((Local2 != 0x11))
            {
                ERR (TS, Z111, 0x10AD, 0x00, 0x00, Local2, 0x11)
            }
        }
    }

    /* Simple TEST 17 */

    Method (M34C, 0, Serialized)
    {
        Name (TS, "m34c")
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
        Name (S010, "qwer0000")
        Name (B010, Buffer (0x04)
        {
             0x01, 0x77, 0x03, 0x04                           // .w..
        })
        Name (P010, Package (0x03)
        {
            0x05, 
            0x77, 
            0x07
        })
        Name (S020, "qwer0000")
        Name (B020, Buffer (0x04)
        {
             0x01, 0x77, 0x03, 0x04                           // .w..
        })
        Name (P020, Package (0x03)
        {
            0x05, 
            0x77, 
            0x07
        })
        Name (S030, "qwer0000")
        Name (B030, Buffer (0x04)
        {
             0x01, 0x77, 0x03, 0x04                           // .w..
        })
        Name (P030, Package (0x03)
        {
            0x05, 
            0x77, 
            0x07
        })
        /* Store to reference keeping in LocalX */

        Method (M000, 2, NotSerialized)
        {
            Local2 = DerefOf (Arg0)
            Local3 = ObjectType (Local2)
            If ((Local3 != Arg1))
            {
                ERR (TS, Z111, 0x10CE, 0x00, 0x00, Local3, Arg1)
            }

            Local1 = Local0 = Local2 [0x01]
            Local0 = 0x90
            If ((Local0 != 0x90))
            {
                ERR (TS, Z111, 0x10D5, 0x00, 0x00, Local0, 0x90)
            }

            Local1 = 0x91
            If ((Local1 != 0x91))
            {
                ERR (TS, Z111, 0x10D9, 0x00, 0x00, Local1, 0x91)
            }
        }

        /* CopyObject to reference keeping in LocalX */

        Method (M001, 1, NotSerialized)
        {
            Local2 = DerefOf (Arg0)
            Local1 = Local0 = Local2 [0x01]
            CopyObject (0x94, Local0)
            If ((Local0 != 0x94))
            {
                ERR (TS, Z111, 0x10E6, 0x00, 0x00, Local0, 0x94)
            }

            CopyObject (0x95, Local1)
            If ((Local1 != 0x95))
            {
                ERR (TS, Z111, 0x10EA, 0x00, 0x00, Local1, 0x95)
            }
        }

        /* Store to reference immediately */

        Method (M002, 2, NotSerialized)
        {
            Local2 = DerefOf (Arg0)
            Local2 [0x01] = 0x2B
            If ((Arg1 == C00A))
            {
                M385 (TS, Local2, 0x00, 0x00)
            }
            ElseIf ((Arg1 == C00B))
            {
                M386 (TS, Local2, 0x00, 0x01)
            }
            ElseIf ((Arg1 == C00C))
            {
                M387 (TS, Local2, 0x00, 0x02)
            }
        }

        /* Store to reference immediately */

        Method (M003, 2, NotSerialized)
        {
            Local2 = DerefOf (Arg0)
            Local0 = Local2 [0x01]
            Local2 [0x01] = 0x2B
            If ((Arg1 == C00A))
            {
                M385 (TS, Local2, 0x00, 0x03)
            }
            ElseIf ((Arg1 == C00B))
            {
                M386 (TS, Local2, 0x00, 0x04)
            }
            ElseIf ((Arg1 == C00C))
            {
                M387 (TS, Local2, 0x00, 0x05)
            }

            Local2 = DerefOf (Local0)
            If ((Local2 != 0x2B))
            {
                ERR (TS, Z111, 0x1110, 0x00, 0x00, Local2, 0x2B)
            }
        }

        Method (M010, 2, NotSerialized)
        {
            Local0 = RefOf (Arg0)
            M000 (Local0, Arg1)
            M000 (RefOf (Arg0), Arg1)
            If ((Arg1 == C00A))
            {
                M381 (TS, Arg0, 0x00, 0x06)
            }
            ElseIf ((Arg1 == C00B))
            {
                M382 (TS, Arg0, 0x00, 0x07)
            }
            ElseIf ((Arg1 == C00C))
            {
                M383 (TS, Arg0, 0x00, 0x08)
            }
        }

        Method (M011, 2, NotSerialized)
        {
            Local0 = RefOf (Arg0)
            M001 (Local0)
            M001 (RefOf (Arg0))
            If ((Arg1 == C00A))
            {
                M381 (TS, Arg0, 0x00, 0x09)
            }
            ElseIf ((Arg1 == C00B))
            {
                M382 (TS, Arg0, 0x00, 0x0A)
            }
            ElseIf ((Arg1 == C00C))
            {
                M383 (TS, Arg0, 0x00, 0x0B)
            }
        }

        Method (M012, 2, NotSerialized)
        {
            Local0 = RefOf (Arg0)
            M002 (Local0, Arg1)
            If ((Arg1 == C00A))
            {
                M381 (TS, Arg0, 0x00, 0x0C)
            }
            ElseIf ((Arg1 == C00B))
            {
                M382 (TS, Arg0, 0x00, 0x0D)
            }
            ElseIf ((Arg1 == C00C))
            {
                M383 (TS, Arg0, 0x00, 0x0E)
            }
        }

        Method (M022, 2, NotSerialized)
        {
            M002 (RefOf (Arg0), Arg1)
            If ((Arg1 == C00A))
            {
                M381 (TS, Arg0, 0x00, 0x0F)
            }
            ElseIf ((Arg1 == C00B))
            {
                M382 (TS, Arg0, 0x00, 0x10)
            }
            ElseIf ((Arg1 == C00C))
            {
                M383 (TS, Arg0, 0x00, 0x11)
            }
        }

        Method (M013, 2, NotSerialized)
        {
            Local0 = RefOf (Arg0)
            M003 (Local0, Arg1)
            If ((Arg1 == C00A))
            {
                M381 (TS, Arg0, 0x00, 0x12)
            }
            ElseIf ((Arg1 == C00B))
            {
                M382 (TS, Arg0, 0x00, 0x13)
            }
            ElseIf ((Arg1 == C00C))
            {
                M383 (TS, Arg0, 0x00, 0x14)
            }
        }

        Method (M023, 2, NotSerialized)
        {
            M003 (RefOf (Arg0), Arg1)
            If ((Arg1 == C00A))
            {
                M381 (TS, Arg0, 0x00, 0x15)
            }
            ElseIf ((Arg1 == C00B))
            {
                M382 (TS, Arg0, 0x00, 0x16)
            }
            ElseIf ((Arg1 == C00C))
            {
                M383 (TS, Arg0, 0x00, 0x17)
            }
        }

        BEG0 (Z111, TS)
        M010 (S000, C00A)
        M010 (B000, C00B)
        M010 (P000, C00C)
        M381 (TS, S000, 0x00, 0x18)
        M382 (TS, B000, 0x00, 0x19)
        M383 (TS, P000, 0x00, 0x1A)
        M011 (S000, C00A)
        M011 (B000, C00B)
        M011 (P000, C00C)
        M381 (TS, S000, 0x00, 0x1B)
        M382 (TS, B000, 0x00, 0x1C)
        M383 (TS, P000, 0x00, 0x1D)
        M012 (S000, C00A)
        M012 (B000, C00B)
        M012 (P000, C00C)
        M381 (TS, S000, 0x00, 0x1E)
        M382 (TS, B000, 0x00, 0x1F)
        M383 (TS, P000, 0x00, 0x20)
        M022 (S010, C00A)
        M022 (B010, C00B)
        M022 (P010, C00C)
        M381 (TS, S010, 0x00, 0x21)
        M382 (TS, B010, 0x00, 0x22)
        M383 (TS, P010, 0x00, 0x23)
        M013 (S020, C00A)
        M013 (B020, C00B)
        M013 (P020, C00C)
        M381 (TS, S020, 0x00, 0x24)
        M382 (TS, B020, 0x00, 0x25)
        M383 (TS, P020, 0x00, 0x26)
        M023 (S030, C00A)
        M023 (B030, C00B)
        M023 (P030, C00C)
        M381 (TS, S030, 0x00, 0x27)
        M382 (TS, B030, 0x00, 0x28)
        M383 (TS, P030, 0x00, 0x29)
        END0 ()
    }

    Method (M34D, 1, Serialized)
    {
        Name (TS, "m34d")
        Name (OP00, 0x00)
        Name (OP01, 0x01)
        OP00 = Arg0
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
        Name (I010, 0x77)
        Name (S010, "qwer0000")
        Name (B010, Buffer (0x04)
        {
             0x01, 0x77, 0x03, 0x04                           // .w..
        })
        Name (P010, Package (0x03)
        {
            0x05, 
            0x77, 
            0x07
        })
        Name (I020, 0x77)
        Name (S020, "qwer0000")
        Name (B020, Buffer (0x04)
        {
             0x01, 0x77, 0x03, 0x04                           // .w..
        })
        Name (P020, Package (0x03)
        {
            0x05, 
            0x77, 
            0x07
        })
        Name (I030, 0x77)
        Name (S030, "qwer0000")
        Name (B030, Buffer (0x04)
        {
             0x01, 0x77, 0x03, 0x04                           // .w..
        })
        Name (P030, Package (0x03)
        {
            0x05, 
            0x77, 
            0x07
        })
        Name (I040, 0x77)
        Name (S040, "qwer0000")
        Name (B040, Buffer (0x04)
        {
             0x01, 0x77, 0x03, 0x04                           // .w..
        })
        Name (P040, Package (0x03)
        {
            0x05, 
            0x77, 
            0x07
        })
        Name (I050, 0x77)
        Name (S050, "qwer0000")
        Name (B050, Buffer (0x04)
        {
             0x01, 0x77, 0x03, 0x04                           // .w..
        })
        Name (P050, Package (0x03)
        {
            0x05, 
            0x77, 
            0x07
        })
        Name (I060, 0x77)
        Name (S060, "qwer0000")
        Name (B060, Buffer (0x04)
        {
             0x01, 0x77, 0x03, 0x04                           // .w..
        })
        Name (P060, Package (0x03)
        {
            0x05, 
            0x77, 
            0x07
        })
        Name (I070, 0x77)
        Name (S070, "qwer0000")
        Name (B070, Buffer (0x04)
        {
             0x01, 0x77, 0x03, 0x04                           // .w..
        })
        Name (P070, Package (0x03)
        {
            0x05, 
            0x77, 
            0x07
        })
        Name (I001, 0x2B)
        Name (S001, "q+er0000")
        Name (B001, Buffer (0x04)
        {
             0x01, 0x2B, 0x03, 0x04                           // .+..
        })
        Name (P001, Package (0x03)
        {
            0x05, 
            0x2B, 
            0x07
        })
        Method (M000, 3, NotSerialized)
        {
            Method (M000, 3, NotSerialized)
            {
                Method (M000, 3, NotSerialized)
                {
                    Method (M000, 3, NotSerialized)
                    {
                        Local0 = ObjectType (Arg0)
                        If ((Local0 != Arg2))
                        {
                            ERR (TS, Z111, 0x11DE, 0x00, 0x00, Local0, Arg2)
                        }

                        If (OP00)
                        {
                            /* CopyObject */

                            If ((Arg1 == C009))
                            {
                                CopyObject (0x2B, Arg0)
                            }
                            ElseIf ((Arg1 == C00A))
                            {
                                CopyObject ("q+er0000", Arg0)
                            }
                            ElseIf ((Arg1 == C00B))
                            {
                                CopyObject (Buffer (0x04)
                                    {
                                         0x01, 0x2B, 0x03, 0x04                           // .+..
                                    }, Arg0)
                            }
                            ElseIf ((Arg1 == C00C))
                            {
                                CopyObject (Package (0x03)
                                    {
                                        0x05, 
                                        0x2B, 
                                        0x07
                                    }, Arg0)
                            }
                        }
                        ElseIf                        /* Store */

 ((Arg1 == C009))
                        {
                            Arg0 = 0x2B
                        }
                        ElseIf ((Arg1 == C00A))
                        {
                            Arg0 = "q+er0000"
                        }
                        ElseIf ((Arg1 == C00B))
                        {
                            Arg0 = Buffer (0x04)
                                {
                                     0x01, 0x2B, 0x03, 0x04                           // .+..
                                }
                        }
                        ElseIf ((Arg1 == C00C))
                        {
                            Arg0 = Package (0x03)
                                {
                                    0x05, 
                                    0x2B, 
                                    0x07
                                }
                        }

                        Local0 = DerefOf (Arg0)
                        M391 (Local0, Arg1, 0x00, 0x00)
                    }

                    M000 (Arg0, Arg1, Arg2)
                    Local0 = DerefOf (Arg0)
                    M391 (Local0, Arg1, 0x00, 0x01)
                }

                M000 (Arg0, Arg1, Arg2)
                Local0 = DerefOf (Arg0)
                M391 (Local0, Arg1, 0x00, 0x02)
            }

            M000 (Arg0, Arg1, Arg2)
            Local0 = DerefOf (Arg0)
            M391 (Local0, Arg1, 0x00, 0x03)
        }

        BEG0 (Z111, TS)
        /* Write Integer */

        Local0 = RefOf (I000)
        M000 (Local0, C009, C009)
        M391 (I000, C009, 0x00, 0x04)
        Local2 = DerefOf (Local0)
        M391 (Local2, C009, 0x00, 0x05)
        Local0 = RefOf (S000)
        M000 (Local0, C009, C00A)
        M391 (S000, C009, 0x00, 0x06)
        Local2 = DerefOf (Local0)
        M391 (Local2, C009, 0x00, 0x07)
        Local0 = RefOf (B000)
        M000 (Local0, C009, C00B)
        M391 (B000, C009, 0x00, 0x08)
        Local2 = DerefOf (Local0)
        M391 (Local2, C009, 0x00, 0x09)
        /* Write String */

        Local0 = RefOf (I010)
        M000 (Local0, C00A, C009)
        M391 (I010, C00A, 0x00, 0x0C)
        Local2 = DerefOf (Local0)
        M391 (Local2, C00A, 0x00, 0x0D)
        Local0 = RefOf (S010)
        M000 (Local0, C00A, C00A)
        M391 (S010, C00A, 0x00, 0x0E)
        Local2 = DerefOf (Local0)
        M391 (Local2, C00A, 0x00, 0x0F)
        Local0 = RefOf (B010)
        M000 (Local0, C00A, C00B)
        M391 (B010, C00A, 0x00, 0x10)
        Local2 = DerefOf (Local0)
        M391 (Local2, C00A, 0x00, 0x11)
        /* Write Buffer */

        Local0 = RefOf (I020)
        M000 (Local0, C00B, C009)
        M391 (I020, C00B, 0x00, 0x14)
        Local2 = DerefOf (Local0)
        M391 (Local2, C00B, 0x00, 0x15)
        Local0 = RefOf (S020)
        M000 (Local0, C00B, C00A)
        M391 (S020, C00B, 0x00, 0x16)
        Local2 = DerefOf (Local0)
        M391 (Local2, C00B, 0x00, 0x17)
        Local0 = RefOf (B020)
        M000 (Local0, C00B, C00B)
        M391 (B020, C00B, 0x00, 0x18)
        Local2 = DerefOf (Local0)
        M391 (Local2, C00B, 0x00, 0x19)
        /* Write Package */

        If (!OP00)
        {
            If (!Y516)
            {
                OP01 = 0x00
            }
        }

        If (OP01)
        {
            Local0 = RefOf (I030)
            M000 (Local0, C00C, C009)
            M391 (I030, C00C, 0x00, 0x1C)
            Local2 = DerefOf (Local0)
            M391 (Local2, C00C, 0x00, 0x1D)
            Local0 = RefOf (S030)
            M000 (Local0, C00C, C00A)
            M391 (S030, C00C, 0x00, 0x1E)
            Local2 = DerefOf (Local0)
            M391 (Local2, C00C, 0x00, 0x1F)
            Local0 = RefOf (B030)
            M000 (Local0, C00C, C00B)
            M391 (B030, C00C, 0x00, 0x20)
            Local2 = DerefOf (Local0)
            M391 (Local2, C00C, 0x00, 0x21)
            Local0 = RefOf (P030)
            M000 (Local0, C00C, C00C)
            M391 (P030, C00C, 0x00, 0x22)
            Local2 = DerefOf (Local0)
            M391 (Local2, C00C, 0x00, 0x23)
        }

        /* Write Integer */

        M000 (RefOf (I040), C009, C009)
        M391 (I040, C009, 0x00, 0x24)
        M000 (RefOf (S040), C009, C00A)
        M391 (I040, C009, 0x00, 0x25)
        M000 (RefOf (B040), C009, C00B)
        M391 (I040, C009, 0x00, 0x26)
        /* Write String */

        M000 (RefOf (I050), C00A, C009)
        M391 (I050, C00A, 0x00, 0x28)
        M000 (RefOf (S050), C00A, C00A)
        M391 (I050, C00A, 0x00, 0x29)
        M000 (RefOf (B050), C00A, C00B)
        M391 (I050, C00A, 0x00, 0x2A)
        /* Write Bufer */

        M000 (RefOf (I060), C00B, C009)
        M391 (I060, C00B, 0x00, 0x2C)
        M000 (RefOf (S060), C00B, C00A)
        M391 (I060, C00B, 0x00, 0x2D)
        M000 (RefOf (B060), C00B, C00B)
        M391 (I060, C00B, 0x00, 0x2E)
        /* Write Package */

        If (OP01)
        {
            M000 (RefOf (I070), C00C, C009)
            M391 (I070, C00C, 0x00, 0x30)
            M000 (RefOf (S070), C00C, C00A)
            M391 (I070, C00C, 0x00, 0x31)
            M000 (RefOf (B070), C00C, C00B)
            M391 (I070, C00C, 0x00, 0x32)
            M000 (RefOf (P070), C00C, C00C)
            M391 (I070, C00C, 0x00, 0x33)
        }

        END0 ()
    }

    Method (M34E, 1, Serialized)
    {
        Name (TS, "m34e")
        Name (OP00, 0x00)
        OP00 = Arg0
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
        Method (M000, 3, NotSerialized)
        {
            Method (M000, 3, NotSerialized)
            {
                Method (M000, 3, NotSerialized)
                {
                    Method (M000, 3, NotSerialized)
                    {
                        Local0 = ObjectType (Arg0)
                        If ((Local0 != Arg2))
                        {
                            ERR (TS, Z111, 0x12B0, 0x00, 0x00, Local0, Arg2)
                        }

                        If (OP00)
                        {
                            CopyObject (0x2B, Arg0)
                        }
                        Else
                        {
                            Arg0 = 0x2B
                        }

                        M391 (Arg0, Arg1, 0x00, 0x00)
                    }

                    M000 (Arg0, Arg1, Arg2)
                    Local0 = DerefOf (Arg0)
                    M390 (Local0, Arg1, 0x00, 0x01)
                }

                M000 (Arg0, Arg1, Arg2)
                Local0 = DerefOf (Arg0)
                M390 (Local0, Arg1, 0x00, 0x02)
            }

            M000 (Arg0, Arg1, Arg2)
            Local0 = DerefOf (Arg0)
            M390 (Local0, Arg1, 0x00, 0x03)
        }

        BEG0 (Z111, TS)
        /* String */

        Store (S000 [0x01], Local0)
        M000 (Local0, C009, C016)
        M390 (S000, C00A, 0x00, 0x04)
        Local2 = DerefOf (Local0)
        M380 (TS, Local2, 0x00, 0x05)
        /* Buffer */

        Store (B000 [0x01], Local0)
        M000 (Local0, C009, C016)
        M390 (B000, C00B, 0x00, 0x06)
        Local2 = DerefOf (Local0)
        M380 (TS, Local2, 0x00, 0x07)
        /* Package */

        Store (P000 [0x01], Local0)
        M000 (Local0, C009, C009)
        M390 (P000, C00C, 0x00, 0x08)
        Local2 = DerefOf (Local0)
        M380 (TS, Local2, 0x00, 0x09)
        END0 ()
    }

    Method (M34F, 0, Serialized)
    {
        Name (TS, "m34f")
        BEG0 (Z111, TS)
        RefOf (I900) = 0x77
        M380 (TS, I900, 0x00, 0x00)
        RefOf (S900) = 0x77
        M4C0 (TS, S900, "0000000000000077", "00000077")
        RefOf (B900) = 0x77
        M1AA (TS, B900, C00B, Buffer (0x05)
            {
                 0x77, 0x00, 0x00, 0x00, 0x00                     // w....
            }, 0x01)
        RefOf (P953) = 0x77
        M380 (TS, P953, 0x00, 0x02)
        RefOf (E900) = 0x77
        M380 (TS, E900, 0x00, 0x03)
        RefOf (MX90) = 0x77
        M380 (TS, MX90, 0x00, 0x04)
        RefOf (D900) = 0x77
        M380 (TS, D900, 0x00, 0x05)
        If (Y508)
        {
            RefOf (TZ90) = 0x77
            M380 (TS, TZ90, 0x00, 0x06)
        }

        RefOf (PR90) = 0x77
        M380 (TS, PR90, 0x00, 0x07)
        If (Y510)
        {
            RefOf (R900) = 0x77
            M380 (TS, R900, 0x00, 0x08)
        }

        RefOf (PW90) = 0x77
        M380 (TS, PW90, 0x00, 0x09)
        M1AC ()
        M1A6 ()
        END0 ()
    }

    /* CURRENTLY: compiler failed CopyObject(xx, RefOf(xx)) */

    Method (M350, 0, Serialized)
    {
        Name (TS, "m350")
        /* CopyObject(0x77, RefOf(i900)) */
    }

    /* Write Integer into Package and verify the obtained contents */
    /* arg0 - Package */
    Method (M351, 1, Serialized)
    {
        Name (TS, "m351")
        Name (LPN0, 0x11)
        Name (LPC0, 0x00)
        Local6 = 0x10
        While (LPN0)
        {
            Arg0 [LPC0] = Local6
            Local6++
            LPN0--
            LPC0++
        }

        /* Check that elements of Package are properly changed */

        LPN0 = 0x11
        LPC0 = 0x00
        Local6 = 0x10
        While (LPN0)
        {
            Store (Arg0 [LPC0], Local0)
            Local1 = ObjectType (Local0)
            If ((Local1 != C009))
            {
                ERR (TS, Z111, 0x1334, 0x00, 0x00, Local1, C009)
            }
            Else
            {
                Local1 = DerefOf (Local0)
                If ((Local1 != Local6))
                {
                    ERR (TS, Z111, 0x1338, 0x00, 0x00, Local1, Local6)
                }
            }

            Local6++
            LPN0--
            LPC0++
        }
    }

    /* Write ORef into Package */
    /* arg0 - Package */
    Method (M352, 1, NotSerialized)
    {
        Arg0 [0x00] = 0x00
        Arg0 [0x01] = RefOf (I900)
        Arg0 [0x02] = RefOf (S900)
        Arg0 [0x03] = RefOf (B900)
        Arg0 [0x04] = RefOf (P953)
        Arg0 [0x05] = RefOf (F900)
        Arg0 [0x06] = RefOf (D900)
        Arg0 [0x07] = RefOf (E900)
        Arg0 [0x08] = RefOf (M914)
        Arg0 [0x09] = RefOf (MX90)
        Arg0 [0x0A] = RefOf (R900)
        Arg0 [0x0B] = RefOf (PW90)
        Arg0 [0x0C] = RefOf (PR90)
        Arg0 [0x0D] = RefOf (TZ90)
        Arg0 [0x0E] = RefOf (BF90)
        Arg0 [0x0F] = 0x0F
        Arg0 [0x10] = 0x10
    }

    /* Write IRef (Index(p955, x)) into Package */
    /* arg0 - Package */
    /* arg1 - 0 - Store, otherwise - CopyObject */
    Method (M353, 2, Serialized)
    {
        Name (LPN0, 0x11)
        Name (LPC0, 0x00)
        If (Arg1){        /*
         * While (lpN0) {
         *	CopyObject(Index(p955, lpC0), Index(arg0, lpC0))
         *	Decrement(lpN0)
         *	Increment(lpC0)
         * }
         * CopyObject(0, Index(arg0, 0))
         * CopyObject(15, Index(arg0, 15))
         * CopyObject(16, Index(arg0, 16))
         */
        }
        Else
        {
            While (LPN0)
            {
                Store (P955 [LPC0], Arg0 [LPC0])
                LPN0--
                LPC0++
            }

            Arg0 [0x00] = 0x00
            Arg0 [0x0F] = 0x0F
            Arg0 [0x10] = 0x10
        }
    }

    Method (M362, 0, Serialized)
    {
        Name (I000, 0x00)
        Method (M000, 1, NotSerialized)
        {
            Local0 = (0x76 + 0x01)
            Arg0 = Local0
        }

        M000 (RefOf (I000))
        M380 ("m362", I000, Z111, 0x00)
    }

    Method (M363, 0, Serialized)
    {
        Name (I000, 0x00)
        Method (M000, 1, NotSerialized)
        {
            Arg0 = (0x76 + 0x01)
        }

        M000 (RefOf (I000))
        M380 ("m363", I000, Z111, 0x00)
    }

    Method (M364, 0, Serialized)
    {
        Name (I000, 0x00)
        Method (M000, 1, NotSerialized)
        {
            Arg0 = (0x76 + 0x01)
        }

        Local0 = RefOf (I000)
        M000 (Local0)
        M380 ("m364", I000, Z111, 0x00)
    }

    /*
     *
     * Auxiliary Methods
     *
     */
    /* Run all the ORef relevant Methods of ref1-ref4 */
    Method (M4D0, 0, NotSerialized)
    {
        M16F (0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00)
        M175 (0x00, 0x01, 0x01)
        M185 (0x00, 0x01, 0x01)
        M195 (0x00, 0x01, 0x01, 0x01, 0x00)
    }

    /* Run all the IRef relevant Methods of ref1-ref4 */

    Method (M4D1, 0, NotSerialized)
    {
        M16F (0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01)
        M175 (0x01, 0x00, 0x00)
        M185 (0x01, 0x00, 0x00)
        M195 (0x01, 0x00, 0x00, 0x00, 0x01)
    }

    /* Run all the NamedX-ORef relevant Methods of ref1-ref4 */

    Method (M4D2, 0, NotSerialized)
    {
        M16F (0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00)
        M175 (0x00, 0x01, 0x01)
        M185 (0x00, 0x01, 0x01)
        M195 (0x00, 0x01, 0x01, 0x01, 0x00)
    }

    /* Run all the NamedX-IRef relevant Methods of ref1-ref4 */

    Method (M4D3, 0, NotSerialized)
    {
        M16F (0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01)
        M175 (0x01, 0x00, 0x00)
        M185 (0x01, 0x00, 0x00)
        M195 (0x01, 0x00, 0x00, 0x00, 0x01)
    }

    /*
     Method(m4d0) {}
     Method(m4d1) {}
     Method(m4d2) {}
     Method(m4d3) {}
     Method(m1e0, 1) {}
     */
    Method (MFAB, 0, Serialized)
    {
        /*
         * Update required: do this test for different type target objects
         * and reference elements (Iref/Oref; LocalX/ArgX/NamedX/...).
         */
        Name (PP00, Package (0x08)
        {
            0x80, 
            0x81, 
            0x82, 
            0x83, 
            0x84, 
            0x85, 
            0x86, 
            0x87
        })
        Name (P000, Package (0x10)
        {
            0x00, 
            0x01, 
            0x02, 
            0x03, 
            0x04, 
            0x05, 
            0x06, 
            0x07, 
            0x08, 
            0x09, 
            0x0A, 
            0x0B, 
            0x0C, 
            0x0D, 
            0x0E, 
            0x0F
        })
        /* Over Integers */

        P000 [0x00] = RefOf (PP00)
        Store (P000 [0x00], P000 [0x01])
        Store (P000 [0x01], P000 [0x02])
        Store (P000 [0x02], P000 [0x03])
        Store (P000 [0x03], P000 [0x04])
        Store (P000 [0x04], P000 [0x05])
        Store (P000 [0x05], P000 [0x06])
        Store (P000 [0x06], P000 [0x07])
        Store (P000 [0x07], P000 [0x08])
        Store (P000 [0x08], P000 [0x09])
        Store (P000 [0x09], P000 [0x0A])
        Store (P000 [0x0A], P000 [0x0B])
        Store (P000 [0x0B], P000 [0x0C])
        Store (P000 [0x0C], P000 [0x0D])
        Store (P000 [0x0D], P000 [0x0E])
        Store (P000 [0x0E], P000 [0x0F])
        Local0 = P000 [0x0F]
        Local1 = ObjectType (Local0)
        If ((Local1 != C01C))
        {
            ERR ("mfab", Z111, 0x13FB, 0x00, 0x00, Local1, C01C)
        }

        Local1 = ObjectType (DerefOf (Local0))
        If ((Local1 != C01C))
        {
            ERR ("mfab", Z111, 0x1400, 0x00, 0x00, Local1, C01C)
        }
    }

    Method (MFAD, 0, Serialized)
    {
        /*
         * Update required: do this test for different type target objects
         * and reference elements (Iref/Oref; LocalX/ArgX/NamedX/...).
         */
        Name (I000, 0xABCD0000)
        Name (P000, Package (0x10)
        {
            0x00, 
            0x01, 
            0x02, 
            0x03, 
            0x04, 
            0x05, 
            0x06, 
            0x07, 
            0x08, 
            0x09, 
            0x0A, 
            0x0B, 
            0x0C, 
            0x0D, 
            0x0E, 
            0x0F
        })
        /* Over Integers */

        P000 [0x00] = RefOf (I000)
        Store (P000 [0x00], P000 [0x01])
        Store (P000 [0x01], P000 [0x02])
        Store (P000 [0x02], P000 [0x03])
        Store (P000 [0x03], P000 [0x04])
        Store (P000 [0x04], P000 [0x05])
        Store (P000 [0x05], P000 [0x06])
        Store (P000 [0x06], P000 [0x07])
        Store (P000 [0x07], P000 [0x08])
        Store (P000 [0x08], P000 [0x09])
        Store (P000 [0x09], P000 [0x0A])
        Store (P000 [0x0A], P000 [0x0B])
        Store (P000 [0x0B], P000 [0x0C])
        Store (P000 [0x0C], P000 [0x0D])
        Store (P000 [0x0D], P000 [0x0E])
        Store (P000 [0x0E], P000 [0x0F])
        Store (P000 [0x0F], P000 [0x00])
        Local0 = P000 [0x0F]
        Debug = Local0
        If (0x00)
        {
            Local1 = ObjectType (Local0)
            Debug = Local1
            If ((Local1 != C01C))
            {
                ERR ("mfad", Z111, 0x142B, 0x00, 0x00, Local1, C01C)
            }
        }
        Else
        {
            /*
             * ObjectType here falls into the infinitive loop.
             * Sort this out!
             */
            ERR ("mfad", Z111, 0x1432, 0x00, 0x00, 0x00, 0x00)
        }
    }

    Method (MFC3, 0, Serialized)
    {
        /*
         * Update required: do this test for different type target objects
         * and reference elements (Iref/Oref; LocalX/ArgX/NamedX/...).
         */
        Name (I000, 0xABCD0000)
        Name (P000, Package (0x10)
        {
            0x00, 
            0x01, 
            0x02, 
            0x03, 
            0x04, 
            0x05, 
            0x06, 
            0x07, 
            0x08, 
            0x09, 
            0x0A, 
            0x0B, 
            0x0C, 
            0x0D, 
            0x0E, 
            0x0F
        })
        /* Over Integers */

        P000 [0x00] = RefOf (I000)
        Store (P000 [0x00], P000 [0x01])
        Store (P000 [0x01], P000 [0x02])
        Store (P000 [0x02], P000 [0x03])
        Store (P000 [0x03], P000 [0x04])
        Store (P000 [0x04], P000 [0x05])
        Store (P000 [0x05], P000 [0x06])
        Store (P000 [0x06], P000 [0x07])
        Store (P000 [0x07], P000 [0x08])
        Store (P000 [0x08], P000 [0x09])
        Store (P000 [0x09], P000 [0x0A])
        Store (P000 [0x0A], P000 [0x0B])
        Store (P000 [0x0B], P000 [0x0C])
        Store (P000 [0x0C], P000 [0x0D])
        Store (P000 [0x0D], P000 [0x0E])
        Store (P000 [0x0E], P000 [0x0F])
        Store (P000 [0x0F], P000 [0x00])
        Local0 = P000 [0x0F]
        Debug = Local0
        If (0x00)
        {
            Local1 = SizeOf (Local0)
            Debug = Local1
            If ((Local1 != 0x64))
            {
                ERR ("mfc3", Z111, 0x145D, 0x00, 0x00, Local1, 0x64)
            }
        }
        Else
        {
            /*
             * SizeOf here falls into the infinitive loop.
             * Sort this out!
             */
            ERR ("mfc3", Z111, 0x1464, 0x00, 0x00, 0x00, 0x00)
        }
    }

    Method (MFC4, 0, Serialized)
    {
        /*
         * Update required: do this test for different type target objects
         * and reference elements (Iref/Oref; LocalX/ArgX/NamedX/...).
         */
        Name (I000, 0xABCD0000)
        Name (P000, Package (0x10)
        {
            0x00, 
            0x01, 
            0x02, 
            0x03, 
            0x04, 
            0x05, 
            0x06, 
            0x07, 
            0x08, 
            0x09, 
            0x0A, 
            0x0B, 
            0x0C, 
            0x0D, 
            0x0E, 
            0x0F
        })
        /* Over Integers */

        P000 [0x00] = RefOf (I000)
        Store (P000 [0x00], P000 [0x01])
        Store (P000 [0x01], P000 [0x02])
        Store (P000 [0x02], P000 [0x03])
        Store (P000 [0x03], P000 [0x04])
        Store (P000 [0x04], P000 [0x05])
        Store (P000 [0x05], P000 [0x06])
        Store (P000 [0x06], P000 [0x07])
        Store (P000 [0x07], P000 [0x08])
        Store (P000 [0x08], P000 [0x09])
        Store (P000 [0x09], P000 [0x0A])
        Store (P000 [0x0A], P000 [0x0B])
        Store (P000 [0x0B], P000 [0x0C])
        Store (P000 [0x0C], P000 [0x0D])
        Store (P000 [0x0D], P000 [0x0E])
        Store (P000 [0x0E], P000 [0x0F])
        Store (P000 [0x0F], P000 [0x00])
        Local0 = P000 [0x0F]
        Debug = Local0
        If (0x01)
        {
            Local1 = DerefOf (Local0)
            Debug = Local1
            If ((Local1 != 0x64))
            {
                ERR ("mfc4", Z111, 0x1490, 0x00, 0x00, Local1, 0x64)
            }
        }
        Else
        {
            /*
             * SizeOf here falls into the infinitive loop.
             * Sort this out!
             */
            ERR ("mfc4", Z111, 0x1497, 0x00, 0x00, 0x00, 0x00)
        }
    }

    /*
     !!!!!!!!!!!!!!!!!!!!!!!
     Do this test, like this - run Derefof for the chain of references (IR/OR)
     and for ring of them.
     I dont remember if we have already such test.
     !!!!!!!!!!!!!!!!!!!!!!!
     Method(m000)
     {
     *
     * Printing excluded while bug 206 (Store-to-Debug operation
     * falls into infinite loop for ring of RefOf references) is
     * not fixed.
     *
     Store(RefOf(Local0), Local1)
     Store(RefOf(Local1), Local2)
     Store(RefOf(Local2), Local0)
     Store(DerefOf(Local0), Local7)
     Store(Local7, Debug)
     Store(DerefOf(Local7), Local6)
     Store(Local6, Debug)
     Store(DerefOf(Local6), Local5)
     Store(Local5, Debug)
     }
     */
    /* Run-method */
    Method (REF9, 0, NotSerialized)
    {
        Debug = "TEST: REF9, Object and Index References and the call-by-reference convention"
        C085 = 0x01 /* create the chain of references to LocalX, then dereference them */
        C086 = 0x00 /* flag, run test till the first error */
        C088 = 0x01 /* test run mode */
        C089 = 0x00 /* flag of Reference, object otherwise */
        C08B = 0x00 /* do RefOf(ArgX) checkings */
        If (!C088)
        {
            Debug = "A T T E N T I O N: simple mode!"
        }

        If (0x01)
        {
            SRMT ("m221")
            M221 ()
            SRMT ("m222")
            M222 ()
            SRMT ("m223")
            M223 ()
            SRMT ("m224")
            M224 ()
            SRMT ("m225")
            M225 ()
            SRMT ("m226")
            M226 ()
            SRMT ("m227")
            M227 ()
            SRMT ("m228")
            M228 ()
            SRMT ("m229")
            M229 ()
            SRMT ("m22a")
            M22A ()
            SRMT ("m22b")
            M22B ()
            SRMT ("m22c")
            M22C ()
            SRMT ("m22d")
            If (Y164)
            {
                M22D ()
            }
            Else
            {
                BLCK ()
            }

            SRMT ("m22e")
            M22E ()
            SRMT ("m22f")
            M22F ()
            SRMT ("m230")
            M230 ()
            SRMT ("m231")
            M231 ()
            SRMT ("m232")
            M232 ()
            SRMT ("m233")
            M233 () /* bug 130 (m34c) */
            SRMT ("m234")
            M234 ()
            SRMT ("m235")
            M235 ()
            SRMT ("m236")
            M236 ()
            SRMT ("m237")
            M237 ()
            SRMT ("m238")
            M238 ()
            SRMT ("m239")
            M239 ()
            SRMT ("m23a")
            M23A ()
            SRMT ("m23b")
            M23B ()
            SRMT ("m23c")
            M23C ()
            SRMT ("m23d")
            M23D ()
            SRMT ("m23e")
            M23E ()
            SRMT ("m23f")
            M23F ()
            SRMT ("m250")
            M250 ()
            SRMT ("m251")
            M251 ()
            SRMT ("m252")
            M252 ()
            SRMT ("m253")
            M253 ()
            SRMT ("m254")
            M254 ()
            SRMT ("m255")
            M255 ()
            SRMT ("m256")
            M256 ()
            SRMT ("m257")
            M257 ()
            SRMT ("m258")
            M258 (0x00)
            SRMT ("m259")
            M259 ()
            SRMT ("m25a")
            M25A ()
            SRMT ("m25b")
            M25B ()
            SRMT ("m25c")
            M25C ()
            SRMT ("m25d")
            M25D ()
            SRMT ("m25e")
            M25E ()
            SRMT ("m25f")
            M25F ()
            SRMT ("m260")
            M260 ()
            SRMT ("m261")
            M261 ()
            SRMT ("m262")
            M262 ()
            SRMT ("m263")
            M263 ()
            SRMT ("m264")
            M264 ()
            SRMT ("m265")
            M265 ()
            SRMT ("m266")
            M266 ()
            SRMT ("m267")
            M267 ()
            SRMT ("m268")
            M268 ()
            SRMT ("m269")
            M269 ()
            SRMT ("m26a")
            M26A ()
            SRMT ("m26b")
            If (Y164)
            {
                M26B () /* bugs, see inside */
            }
            Else
            {
                BLCK ()
            }

            SRMT ("m26c")
            M26C ()
            SRMT ("m26d")
            M26D ()
            SRMT ("m26e")
            M26E () /* bug 131 (m365) */
            SRMT ("m26f")
            M26F ()
            SRMT ("m270")
            M270 () /* bug 134 */
            SRMT ("m276")
            M276 ()
            SRMT ("mfab")
            If (Y603)
            {
                MFAB ()
            }
            Else
            {
                BLCK ()
            }

            SRMT ("mfad")
            If (Y603)
            {
                MFAD ()
            }
            Else
            {
                BLCK ()
            }

            SRMT ("mfc3")
            If (Y603)
            {
                MFC3 ()
            }
            Else
            {
                BLCK ()
            }

            SRMT ("mfc4")
            If (Y603)
            {
                MFC4 ()
            }
            Else
            {
                BLCK ()
            }
        }
        /*
         SRMT("m23b")
         m23b()
         SRMT("m251")
         m251()
         */
        /*
         SRMT("mfab")
         mfab()
         SRMT("mfad")
         mfad()
         SRMT("mfc3")
         mfc3()
         SRMT("mfc4")
         mfc4()
         //	SRMT("m234")
         //	m234()
         //	SRMT("m26b")
         //	m26b()
         //	m251()
         //	m22d()
         //	m26b()
         //	m276()
         */
        Else
        {
            /* To run particular sub-tests here */

            SRMT ("m1d5")
            M1D5 ()
        }
        /* SEE and do these below: */
    /*
     1. See bug 130, add this checking:
     see this when worked on m233()
     Method(m000, 1)
     {
     //		Store(DerefOf(arg0), Local2)
     //		Store(0x2b, Index(Local2, 1))
     Store(0x2b, Index(DerefOf(arg0), 1))
     }
     2. do many enclosed method calls
     to show that index to Str,Buf,Pckg
     changes the intial object nevertheless
     */
    /*
     Method (M001)
     {
     Name(P004, Package(Add (128, 3)) {})
     Name(P005, Package(Add (128, 1024)) {})
     }
     */
    /*
     Use the same object in several operands and results
     */
    }

