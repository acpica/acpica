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
     *  String
     *
     * (verify exceptions caused by the imprope use of String type objects)
     */
    Name (Z094, 0x5E)
    Name (S100, "1")
    /* Expected exceptions: */
    /* */
    /* 47 - AE_AML_OPERAND_TYPE */
    /*  5 - AE_NOT_FOUND (when DerefOf(String)) */
    /* */
    /* Note: String can be used with DerefOf and Index */
    Method (M4B2, 1, Serialized)
    {
        Name (S000, "2")
        /* Local Named Object */

        Method (M000, 1, Serialized)
        {
            Name (S000, "3")
            /* DerefOf */

            If (Y083)
            {
                Local1 = DerefOf (S000)
                CH06 (Arg0, 0x00, 0x2F)
            }

            /* Index */

            Local1 = S000 [0x00]
            CH03 (__METHOD__, Z094, 0x01, 0x42, 0x00)
            /* ConcatenateResTemplate */

            ConcatenateResTemplate (S000, Buffer (0x02)
                {
                     0x79, 0x00                                       // y.
                }, Local1)
            CH06 (Arg0, 0x03, 0x2F)
            ConcatenateResTemplate (Buffer (0x02)
                {
                     0x79, 0x00                                       // y.
                }, S000, Local1)
            CH06 (Arg0, 0x04, 0x2F)
        }

        /* Global Named Object */

        Method (M001, 1, NotSerialized)
        {
            If (Y083)
            {
                Local1 = DerefOf (S100)
                CH06 (Arg0, 0x05, 0x2F)
            }

            /* Index */

            Local1 = S100 [0x00]
            CH03 (__METHOD__, Z094, 0x03, 0x59, 0x00)
            /* ConcatenateResTemplate */

            ConcatenateResTemplate (S100, Buffer (0x02)
                {
                     0x79, 0x00                                       // y.
                }, Local1)
            CH06 (Arg0, 0x08, 0x2F)
            ConcatenateResTemplate (Buffer (0x02)
                {
                     0x79, 0x00                                       // y.
                }, S100, Local1)
            CH06 (Arg0, 0x09, 0x2F)
        }

        /* Argument */

        Method (M002, 2, NotSerialized)
        {
            /* DerefOf */

            Local1 = DerefOf (Arg1)
            CH06 (Arg0, 0x0A, 0x2F)
            /* Release */

            Release (Arg1)
            CH06 (Arg0, 0x0B, 0x2F)
            /* Reset */

            Reset (Arg1)
            CH06 (Arg0, 0x0C, 0x2F)
            /* Signal */

            Signal (Arg1)
            CH06 (Arg0, 0x0D, 0x2F)
            /* Acquire */

            Local1 = Acquire (Arg1, 0x0000)
            CH06 (Arg0, 0x0E, 0x2F)
            /* ConcatenateResTemplate */

            ConcatenateResTemplate (Arg1, Buffer (0x02)
                {
                     0x79, 0x00                                       // y.
                }, Local1)
            CH06 (Arg0, 0x11, 0x2F)
            ConcatenateResTemplate (Buffer (0x02)
                {
                     0x79, 0x00                                       // y.
                }, Arg1, Local1)
            CH06 (Arg0, 0x12, 0x2F)
            /* Index */

            Local1 = Arg1 [0x00]
            CH03 (__METHOD__, Z094, 0x05, 0x8C, 0x00)
            /* Wait */

            Local1 = Wait (Arg1, 0x00)
            CH06 (Arg0, 0x13, 0x2F)
            /* Match */

            Local1 = Match (Arg1, MTR, 0x00, MTR, 0x00, 0x00)
            CH06 (Arg0, 0x14, 0x2F)
        }

        /* Local */

        Method (M003, 1, NotSerialized)
        {
            Local0 = "3"
            /* DerefOf */

            Local1 = DerefOf (Local0)
            CH06 (Arg0, 0x15, 0x2F)
            /* Release */

            Release (Local0)
            CH06 (Arg0, 0x16, 0x2F)
            /* Reset */

            Reset (Local0)
            CH06 (Arg0, 0x17, 0x2F)
            /* Signal */

            Signal (Local0)
            CH06 (Arg0, 0x18, 0x2F)
            /* Acquire */

            Local1 = Acquire (Local0, 0x0000)
            CH06 (Arg0, 0x19, 0x2F)
            /* ConcatenateResTemplate */

            ConcatenateResTemplate (Local0, Buffer (0x02)
                {
                     0x79, 0x00                                       // y.
                }, Local1)
            CH06 (Arg0, 0x1C, 0x2F)
            ConcatenateResTemplate (Buffer (0x02)
                {
                     0x79, 0x00                                       // y.
                }, Local0, Local1)
            CH06 (Arg0, 0x1D, 0x2F)
            /* Index */

            Local1 = Local0 [0x00]
            CH03 (__METHOD__, Z094, 0x07, 0xC2, 0x00)
            /* Wait */

            Local1 = Wait (Local0, 0x00)
            CH06 (Arg0, 0x1E, 0x2F)
            /* Match */

            Local1 = Match (Local0, MTR, 0x00, MTR, 0x00, 0x00)
            CH06 (Arg0, 0x1F, 0x2F)
        }

        /* An element of Package */

        Method (M004, 1, Serialized)
        {
            Name (P000, Package (0x01)
            {
                "3"
            })
            /* DeRefOf(Index(Package, Ind)) */

            Local1 = DerefOf (DerefOf (P000 [0x00]))
            CH06 (Arg0, 0x20, 0x05)
            Store (DerefOf (P000 [0x00]) [0x00], Local1)
            CH03 (__METHOD__, Z094, 0x08, 0xDA, 0x00)
            Local1 = Match (DerefOf (P000 [0x00]), MTR, 0x00, MTR, 0x00, 
                0x00)
            CH06 (Arg0, 0x21, 0x2F)
            /* DeRefOf(Index(Package, Ind, Dest)) */

            Local1 = DerefOf (DerefOf (Local0 = P000 [0x00]))
            CH06 (Arg0, 0x22, 0x05)
            Store (DerefOf (Local0 = P000 [0x00]) [0x00], Local1)
            CH03 (__METHOD__, Z094, 0x09, 0xE5, 0x00)
            Local1 = Match (DerefOf (Local0 = P000 [0x00]), MTR, 0x00, MTR, 0x00, 
                0x00)
            CH06 (Arg0, 0x23, 0x2F)
        }

        /* Reference to Object */

        Method (M005, 2, NotSerialized)
        {
            Debug = Arg0
            Debug = Arg1
            Local0 = ObjectType (Arg1)
            If ((Local0 != 0x02))
            {
                ERR (Arg0, Z094, 0xF3, 0x00, 0x00, Local0, 0x02)
                Return (0x01)
            }

            Local1 = DerefOf (Arg1)
            CH03 (__METHOD__, Z094, 0x0A, 0xF8, 0x00)
            Local1 = DerefOf (DerefOf (Arg1))
            CH06 (Arg0, 0x25, 0x05)
            Store (DerefOf (Arg1) [0x00], Local1)
            CH03 (__METHOD__, Z094, 0x0B, 0xFE, 0x00)
            Local1 = Match (DerefOf (Arg1), MTR, 0x00, MTR, 0x00, 0x00)
            CH06 (Arg0, 0x26, 0x2F)
            Return (0x00)
        }

        /* Result of Method invocation */

        Method (M006, 1, Serialized)
        {
            Name (I000, 0x00) /* Label to check m000 invocations */
            Method (M000, 1, NotSerialized)
            {
                I000 = Arg0
                Local0 = "3"
                Return (Local0)
            }

            Method (CH00, 2, NotSerialized)
            {
                If ((I000 != Arg1))
                {
                    ERR (Arg0, Z094, 0x0115, 0x00, 0x00, I000, Arg1)
                }
            }

            Local1 = DerefOf (M000 (0x01))
            CH06 (Arg0, 0x28, 0x05)
            CH00 (Arg0, 0x01)
            Release (M000 (0x02))
            CH06 (Arg0, 0x29, 0x2F)
            If (Y600)
            {
                CH00 (Arg0, 0x02)
            }

            Reset (M000 (0x03))
            CH06 (Arg0, 0x2A, 0x2F)
            If (Y600)
            {
                CH00 (Arg0, 0x03)
            }

            Signal (M000 (0x04))
            CH06 (Arg0, 0x2B, 0x2F)
            If (Y600)
            {
                CH00 (Arg0, 0x04)
            }

            Local1 = Acquire (M000 (0x05), 0x0000)
            CH06 (Arg0, 0x2C, 0x2F)
            If (Y600)
            {
                CH00 (Arg0, 0x05)
            }

            CH03 (__METHOD__, Z094, 0x0C, 0x0135, 0x00)
            Store (M000 (0x06) [0x00], Local1)
            If (Y900)
            {
                CH03 (__METHOD__, Z094, 0x0C, 0x0138, 0x00)
                CH00 (Arg0, 0x06)
            }
            Else
            {
                CH04 (__METHOD__, 0x00, 0x55, Z094, 0x013B, 0x00, 0x00) /* AE_INDEX_TO_NOT_ATTACHED */
            }

            Local1 = Wait (M000 (0x07), 0x00)
            CH06 (Arg0, 0x2D, 0x2F)
            If (Y600)
            {
                CH00 (Arg0, 0x07)
            }

            Local1 = Match (M000 (0x08), MTR, 0x00, MTR, 0x00, 0x00)
            CH06 (Arg0, 0x2E, 0x2F)
            CH00 (Arg0, 0x08)
        }

        /* Reference to Object as Result of Method invocation */

        Method (M007, 1, Serialized)
        {
            Name (S000, "3")
            Name (I000, 0x00) /* Label to check m000 invocations */
            Method (M000, 2, NotSerialized)
            {
                I000 = Arg0
                If ((Arg1 == 0x00))
                {
                    Local0 = RefOf (S100)
                }
                ElseIf ((Arg1 == 0x01))
                {
                    Local0 = RefOf (S000)
                }

                Return (Local0)
            }

            Method (CH00, 2, NotSerialized)
            {
                If ((I000 != Arg1))
                {
                    ERR (Arg0, Z094, 0x015E, 0x00, 0x00, I000, Arg1)
                }
            }

            Name (LPN0, 0x02)
            Name (LPC0, 0x00)
            While (LPN0)
            {
                Local0 = (0x03 * LPC0) /* \M4B2.M007.LPC0 */
                I000 = 0x00
                Local1 = DerefOf (M000 (0x01, LPC0))
                CH03 (__METHOD__, Z094, 0x016B, 0x00, 0x00)
                CH00 (Arg0, 0x01)
                Local1 = DerefOf (DerefOf (M000 (0x02, LPC0)))
                CH06 (Arg0, (0x30 + Local0), 0x2F)
                CH00 (Arg0, 0x02)
                Store (DerefOf (M000 (0x03, LPC0)) [0x00], Local1)
                CH06 (Arg0, (0x31 + Local0), 0x2F)
                CH00 (Arg0, 0x03)
                Local1 = Match (DerefOf (M000 (0x04, LPC0)), MTR, 0x00, MTR, 0x00, 0x00)
                CH06 (Arg0, (0x32 + Local0), 0x2F)
                CH00 (Arg0, 0x04)
                LPN0--
                LPC0++
            }
        }

        CH03 (__METHOD__, Z094, 0x0F, 0x017F, 0x00)
        /* Local Named Object */

        M000 (__METHOD__)
        /* Global Named Object */

        M001 (__METHOD__)
        /* Argument */

        M002 (__METHOD__, "2")
        /* Local */

        M003 (__METHOD__)
        /* An element of Package */

        M004 (__METHOD__)
        /* Reference to Local Named Object */

        M005 (Concatenate (__METHOD__, "-m005-RefLocName"), RefOf (S000))
        Local0 = RefOf (S000)
        M005 (Concatenate (__METHOD__, "-m005-RefLocName2"), Local0)
        CondRefOf (S000, Local0)
        M005 (Concatenate (__METHOD__, "-m005-CondRefLocName"), Local0)
        M005 (Concatenate (__METHOD__, "-m005-RefGlobName"), RefOf (S100))
        Local0 = RefOf (S100)
        M005 (Concatenate (__METHOD__, "-m005-RefGlobName2"), Local0)
        CondRefOf (S100, Local0)
        M005 (Concatenate (__METHOD__, "-m005-CondRefGlobName"), Local0)
        /* Reference to Local */

        Local0 = "2"
        M005 (Concatenate (__METHOD__, "-m005-RefLocal"), RefOf (Local0))
        Local1 = RefOf (Local0)
        M005 (Concatenate (__METHOD__, "-m005-RefLocal2"), Local1)
        CondRefOf (Local0, Local1)
        M005 (Concatenate (__METHOD__, "-m005-CondRefLocal"), Local1)
        /* Reference to Arg */

        M005 (Concatenate (__METHOD__, "-m005-RefArg"), RefOf (Arg0))
        Local0 = RefOf (Arg0)
        M005 (Concatenate (__METHOD__, "-m005-RefArg2"), Local0)
        CondRefOf (Arg0, Local0)
        M005 (Concatenate (__METHOD__, "-m005-CondRefArg"), Local0)
        /* Index to Package */

        Name (P000, Package (0x01)
        {
            "2"
        })
        If (Y113)
        {
            M005 (Concatenate (__METHOD__, "-m005-Index"), P000 [0x00])
        }

        Store (P000 [0x00], Local0)
        M005 (Concatenate (__METHOD__, "-m005-Index2"), Local0)
        If (Y113)
        {
            M005 (Concatenate (__METHOD__, "-m005-Index3"), Local0 = P000 [0x00])
        }

        Local0 = P000 [0x00]
        M005 (Concatenate (__METHOD__, "-m005-Index4"), Local0)
        Local1 = Local0 = P000 [0x00]
        M005 (Concatenate (__METHOD__, "-m005-Index5"), Local1)
        /* Result of Method invocation */

        M006 (__METHOD__)
        /* Reference to Object as Result of Method invocation */

        If (Y500)
        {
            M007 (__METHOD__)
        }
    }

