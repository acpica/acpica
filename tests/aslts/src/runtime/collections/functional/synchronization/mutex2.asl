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
     * Check for exceptions on mutexes
     */
    Name (Z150, 0x96)
    /*
     * Run checking that all mutexes are actually Released.
     * To be used while debugging the tests mainly.
     */
    Name (FL03, 0x00)
    /* Counter for m08e */

    Name (CN00, 0x00)
    /*
     * These declarations are used for to check the Acquire
     * and Release operations in a global level AML code.
     */
    Name (I101, 0x00) /* non-zero means that this test was run */
    /*
     * Valid sequence of requests, no exceptions expected.
     *
     * Acquire mutexes of monotone increasing level (Global lock
     * on level 0 too) for all available levels from 0 up to 15,
     * then Release them all in the inverse order.
     */
    Method (M301, 0, Serialized)
    {
        Mutex (MT00, 0x00)
        Mutex (MT10, 0x01)
        Mutex (MT20, 0x02)
        Mutex (MT30, 0x03)
        Mutex (MT40, 0x04)
        Mutex (MT50, 0x05)
        Mutex (MT60, 0x06)
        Mutex (MT70, 0x07)
        Mutex (MT80, 0x08)
        Mutex (MT90, 0x09)
        Mutex (MTA0, 0x0A)
        Mutex (MTB0, 0x0B)
        Mutex (MTC0, 0x0C)
        Mutex (MTD0, 0x0D)
        Mutex (MTE0, 0x0E)
        Mutex (MTF0, 0x0F)
        Name (TS, "m301")
        CH03 (TS, Z150, 0x00, 0x4F, 0x00)
        Local0 = Acquire (MT00, 0xFFFF)
        If (Local0)
        {
            ERR (TS, Z150, 0x53, 0x00, 0x00, 0x00, Local0)
        }
        Else
        {
            Local0 = Acquire (\_GL, 0xFFFF)
            /* GL */

            If (Local0)
            {
                ERR (TS, Z150, 0x57, 0x00, 0x00, 0x00, Local0)
            }
            Else
            {
                Local0 = Acquire (MT10, 0xFFFF)
                If (Local0)
                {
                    ERR (TS, Z150, 0x5B, 0x00, 0x00, 0x00, Local0)
                }
                Else
                {
                    Local0 = Acquire (MT20, 0xFFFF)
                    If (Local0)
                    {
                        ERR (TS, Z150, 0x5F, 0x00, 0x00, 0x00, Local0)
                    }
                    Else
                    {
                        Local0 = Acquire (MT30, 0xFFFF)
                        If (Local0)
                        {
                            ERR (TS, Z150, 0x63, 0x00, 0x00, 0x00, Local0)
                        }
                        Else
                        {
                            Local0 = Acquire (MT40, 0xFFFF)
                            If (Local0)
                            {
                                ERR (TS, Z150, 0x67, 0x00, 0x00, 0x00, Local0)
                            }
                            Else
                            {
                                Local0 = Acquire (MT50, 0xFFFF)
                                If (Local0)
                                {
                                    ERR (TS, Z150, 0x6B, 0x00, 0x00, 0x00, Local0)
                                }
                                Else
                                {
                                    Local0 = Acquire (MT60, 0xFFFF)
                                    If (Local0)
                                    {
                                        ERR (TS, Z150, 0x6F, 0x00, 0x00, 0x00, Local0)
                                    }
                                    Else
                                    {
                                        Local0 = Acquire (MT70, 0xFFFF)
                                        If (Local0)
                                        {
                                            ERR (TS, Z150, 0x73, 0x00, 0x00, 0x00, Local0)
                                        }
                                        Else
                                        {
                                            Local0 = Acquire (MT80, 0xFFFF)
                                            If (Local0)
                                            {
                                                ERR (TS, Z150, 0x77, 0x00, 0x00, 0x00, Local0)
                                            }
                                            Else
                                            {
                                                Local0 = Acquire (MT90, 0xFFFF)
                                                If (Local0)
                                                {
                                                    ERR (TS, Z150, 0x7B, 0x00, 0x00, 0x00, Local0)
                                                }
                                                Else
                                                {
                                                    Local0 = Acquire (MTA0, 0xFFFF)
                                                    If (Local0)
                                                    {
                                                        ERR (TS, Z150, 0x7F, 0x00, 0x00, 0x00, Local0)
                                                    }
                                                    Else
                                                    {
                                                        Local0 = Acquire (MTB0, 0xFFFF)
                                                        If (Local0)
                                                        {
                                                            ERR (TS, Z150, 0x83, 0x00, 0x00, 0x00, Local0)
                                                        }
                                                        Else
                                                        {
                                                            Local0 = Acquire (MTC0, 0xFFFF)
                                                            If (Local0)
                                                            {
                                                                ERR (TS, Z150, 0x87, 0x00, 0x00, 0x00, Local0)
                                                            }
                                                            Else
                                                            {
                                                                Local0 = Acquire (MTD0, 0xFFFF)
                                                                If (Local0)
                                                                {
                                                                    ERR (TS, Z150, 0x8B, 0x00, 0x00, 0x00, Local0)
                                                                }
                                                                Else
                                                                {
                                                                    Local0 = Acquire (MTE0, 0xFFFF)
                                                                    If (Local0)
                                                                    {
                                                                        ERR (TS, Z150, 0x8F, 0x00, 0x00, 0x00, Local0)
                                                                    }
                                                                    Else
                                                                    {
                                                                        Local0 = Acquire (MTF0, 0xFFFF)
                                                                        If (Local0)
                                                                        {
                                                                            ERR (TS, Z150, 0x93, 0x00, 0x00, 0x00, Local0)
                                                                        }
                                                                        Else
                                                                        {
                                                                            Release (MTF0)
                                                                            Release (MTE0)
                                                                            Release (MTD0)
                                                                            Release (MTC0)
                                                                            Release (MTB0)
                                                                            Release (MTA0)
                                                                            Release (MT90)
                                                                            Release (MT80)
                                                                            Release (MT70)
                                                                            Release (MT60)
                                                                            Release (MT50)
                                                                            Release (MT40)
                                                                            Release (MT30)
                                                                            Release (MT20)
                                                                            Release (MT10)
                                                                            Release (\_GL)
                                                                            Release (MT00)
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        CH03 (TS, Z150, 0x11, 0xB8, 0x00)
    }

    /*
     * Valid sequence of requests, no exceptions expected.
     *
     * Acquire mutexes of monotone increasing level (Global lock on level 0 too)
     * for all available levels from 0 up to 15, Acquire 2 mutexes of each level,
     * then Release them all in the inverse order (keep the exactly inverse order
     * for Releasing mutexes of the same level too).
     *
     * arg0 - if to force AE_LIMIT by exceeding the maximal number of created mutexes
     */
    Method (M369, 1, Serialized)
    {
        Name (TS, "m369")
        CH03 (TS, Z150, 0x22, 0xC9, 0x00)
        Mutex (MT00, 0x00)
        Mutex (MT10, 0x01)
        Mutex (MT20, 0x02)
        Mutex (MT30, 0x03)
        Mutex (MT40, 0x04)
        Mutex (MT50, 0x05)
        Mutex (MT60, 0x06)
        Mutex (MT70, 0x07)
        Mutex (MT80, 0x08)
        Mutex (MT90, 0x09)
        Mutex (MTA0, 0x0A)
        Mutex (MTB0, 0x0B)
        Mutex (MTC0, 0x0C)
        Mutex (MTD0, 0x0D)
        Mutex (MTE0, 0x0E)
        Mutex (MTF0, 0x0F)
        Mutex (MT01, 0x00)
        Mutex (MT11, 0x01)
        Mutex (MT21, 0x02)
        Mutex (MT31, 0x03)
        Mutex (MT41, 0x04)
        Mutex (MT51, 0x05)
        Mutex (MT61, 0x06)
        Mutex (MT71, 0x07)
        Mutex (MT81, 0x08)
        Mutex (MT91, 0x09)
        Mutex (MTA1, 0x0A)
        Mutex (MTB1, 0x0B)
        Mutex (MTC1, 0x0C)
        Mutex (MTD1, 0x0D)
        Mutex (MTE1, 0x0E)
        If (Arg0)
        {
            /* Should be enough to exceed the maximal available number of mutexes */

            Mutex (MTF1, 0x0F)
            Mutex (MTF2, 0x0F)
            Mutex (MTF3, 0x0F)
            Mutex (MTF4, 0x0F)
        }

        Local0 = Acquire (MT00, 0xFFFF)
        If (Local0)
        {
            ERR (TS, Z150, 0xF6, 0x00, 0x00, 0x00, Local0)
        }
        Else
        {
            Local0 = Acquire (MT01, 0xFFFF)
            /* the same level */

            If (Local0)
            {
                ERR (TS, Z150, 0xFA, 0x00, 0x00, 0x00, Local0)
            }
            Else
            {
                Local0 = Acquire (\_GL, 0xFFFF)
                /* GL */

                If (Local0)
                {
                    ERR (TS, Z150, 0xFE, 0x00, 0x00, 0x00, Local0)
                }
                Else
                {
                    Local0 = Acquire (MT10, 0xFFFF)
                    If (Local0)
                    {
                        ERR (TS, Z150, 0x0102, 0x00, 0x00, 0x00, Local0)
                    }
                    Else
                    {
                        Local0 = Acquire (MT11, 0xFFFF)
                        If (Local0)
                        {
                            ERR (TS, Z150, 0x0106, 0x00, 0x00, 0x00, Local0)
                        }
                        Else
                        {
                            Local0 = Acquire (MT20, 0xFFFF)
                            If (Local0)
                            {
                                ERR (TS, Z150, 0x010A, 0x00, 0x00, 0x00, Local0)
                            }
                            Else
                            {
                                Local0 = Acquire (MT21, 0xFFFF)
                                If (Local0)
                                {
                                    ERR (TS, Z150, 0x010E, 0x00, 0x00, 0x00, Local0)
                                }
                                Else
                                {
                                    Local0 = Acquire (MT30, 0xFFFF)
                                    If (Local0)
                                    {
                                        ERR (TS, Z150, 0x0112, 0x00, 0x00, 0x00, Local0)
                                    }
                                    Else
                                    {
                                        Local0 = Acquire (MT31, 0xFFFF)
                                        If (Local0)
                                        {
                                            ERR (TS, Z150, 0x0116, 0x00, 0x00, 0x00, Local0)
                                        }
                                        Else
                                        {
                                            Local0 = Acquire (MT40, 0xFFFF)
                                            If (Local0)
                                            {
                                                ERR (TS, Z150, 0x011A, 0x00, 0x00, 0x00, Local0)
                                            }
                                            Else
                                            {
                                                Local0 = Acquire (MT41, 0xFFFF)
                                                If (Local0)
                                                {
                                                    ERR (TS, Z150, 0x011E, 0x00, 0x00, 0x00, Local0)
                                                }
                                                Else
                                                {
                                                    Local0 = Acquire (MT50, 0xFFFF)
                                                    If (Local0)
                                                    {
                                                        ERR (TS, Z150, 0x0122, 0x00, 0x00, 0x00, Local0)
                                                    }
                                                    Else
                                                    {
                                                        Local0 = Acquire (MT51, 0xFFFF)
                                                        If (Local0)
                                                        {
                                                            ERR (TS, Z150, 0x0126, 0x00, 0x00, 0x00, Local0)
                                                        }
                                                        Else
                                                        {
                                                            Local0 = Acquire (MT60, 0xFFFF)
                                                            If (Local0)
                                                            {
                                                                ERR (TS, Z150, 0x012A, 0x00, 0x00, 0x00, Local0)
                                                            }
                                                            Else
                                                            {
                                                                Local0 = Acquire (MT61, 0xFFFF)
                                                                If (Local0)
                                                                {
                                                                    ERR (TS, Z150, 0x012E, 0x00, 0x00, 0x00, Local0)
                                                                }
                                                                Else
                                                                {
                                                                    Local0 = Acquire (MT70, 0xFFFF)
                                                                    If (Local0)
                                                                    {
                                                                        ERR (TS, Z150, 0x0132, 0x00, 0x00, 0x00, Local0)
                                                                    }
                                                                    Else
                                                                    {
                                                                        Local0 = Acquire (MT71, 0xFFFF)
                                                                        If (Local0)
                                                                        {
                                                                            ERR (TS, Z150, 0x0136, 0x00, 0x00, 0x00, Local0)
                                                                        }
                                                                        Else
                                                                        {
                                                                            Local0 = Acquire (MT80, 0xFFFF)
                                                                            If (Local0)
                                                                            {
                                                                                ERR (TS, Z150, 0x013A, 0x00, 0x00, 0x00, Local0)
                                                                            }
                                                                            Else
                                                                            {
                                                                                Local0 = Acquire (MT81, 0xFFFF)
                                                                                If (Local0)
                                                                                {
                                                                                    ERR (TS, Z150, 0x013E, 0x00, 0x00, 0x00, Local0)
                                                                                }
                                                                                Else
                                                                                {
                                                                                    Local0 = Acquire (MT90, 0xFFFF)
                                                                                    If (Local0)
                                                                                    {
                                                                                        ERR (TS, Z150, 0x0142, 0x00, 0x00, 0x00, Local0)
                                                                                    }
                                                                                    Else
                                                                                    {
                                                                                        Local0 = Acquire (MT91, 0xFFFF)
                                                                                        If (Local0)
                                                                                        {
                                                                                            ERR (TS, Z150, 0x0146, 0x00, 0x00, 0x00, Local0)
                                                                                        }
                                                                                        Else
                                                                                        {
                                                                                            Local0 = Acquire (MTA0, 0xFFFF)
                                                                                            If (Local0)
                                                                                            {
                                                                                                ERR (TS, Z150, 0x014A, 0x00, 0x00, 0x00, Local0)
                                                                                            }
                                                                                            Else
                                                                                            {
                                                                                                Local0 = Acquire (MTA1, 0xFFFF)
                                                                                                If (Local0)
                                                                                                {
                                                                                                    ERR (TS, Z150, 0x014E, 0x00, 0x00, 0x00, Local0)
                                                                                                }
                                                                                                Else
                                                                                                {
                                                                                                    Local0 = Acquire (MTB0, 0xFFFF)
                                                                                                    If (Local0)
                                                                                                    {
                                                                                                        ERR (TS, Z150, 0x0152, 0x00, 0x00, 0x00, Local0)
                                                                                                    }
                                                                                                    Else
                                                                                                    {
                                                                                                        Local0 = Acquire (MTB1, 0xFFFF)
                                                                                                        If (Local0)
                                                                                                        {
                                                                                                            ERR (TS, Z150, 0x0156, 0x00, 0x00, 0x00, Local0)
                                                                                                        }
                                                                                                        Else
                                                                                                        {
                                                                                                            Local0 = Acquire (MTC0, 0xFFFF)
                                                                                                            If (Local0)
                                                                                                            {
                                                                                                                ERR (TS, Z150, 0x015A, 0x00, 0x00, 0x00, Local0)
                                                                                                            }
                                                                                                            Else
                                                                                                            {
                                                                                                                Local0 = Acquire (MTC1, 0xFFFF)
                                                                                                                If (Local0)
                                                                                                                {
                                                                                                                    ERR (TS, Z150, 0x015E, 0x00, 0x00, 0x00, Local0)
                                                                                                                }
                                                                                                                Else
                                                                                                                {
                                                                                                                    Local0 = Acquire (MTD0, 0xFFFF)
                                                                                                                    If (Local0)
                                                                                                                    {
                                                                                                                        ERR (TS, Z150, 0x0162, 0x00, 0x00, 0x00, Local0)
                                                                                                                    }
                                                                                                                    Else
                                                                                                                    {
                                                                                                                        Local0 = Acquire (MTD1, 0xFFFF)
                                                                                                                        If (Local0)
                                                                                                                        {
                                                                                                                            ERR (TS, Z150, 0x0166, 0x00, 0x00, 0x00, Local0)
                                                                                                                        }
                                                                                                                        Else
                                                                                                                        {
                                                                                                                            Local0 = Acquire (MTE0, 0xFFFF)
                                                                                                                            If (Local0)
                                                                                                                            {
                                                                                                                                ERR (TS, Z150, 0x016A, 0x00, 0x00, 0x00, Local0)
                                                                                                                            }
                                                                                                                            Else
                                                                                                                            {
                                                                                                                                Local0 = Acquire (MTE1, 0xFFFF)
                                                                                                                                If (Local0)
                                                                                                                                {
                                                                                                                                    ERR (TS, Z150, 0x016E, 0x00, 0x00, 0x00, Local0)
                                                                                                                                }
                                                                                                                                Else
                                                                                                                                {
                                                                                                                                    Local0 = Acquire (MTF0, 0xFFFF)
                                                                                                                                    If (Local0)
                                                                                                                                    {
                                                                                                                                        ERR (TS, Z150, 0x0172, 0x00, 0x00, 0x00, Local0)
                                                                                                                                    }
                                                                                                                                    Else
                                                                                                                                    {
                                                                                                                                        If (Arg0)
                                                                                                                                        {
                                                                                                                                            Local0 = Acquire (MTF1, 0xFFFF)
                                                                                                                                        }
                                                                                                                                        Else
                                                                                                                                        {
                                                                                                                                            Local0 = 0x00
                                                                                                                                        }

                                                                                                                                        If (Local0)
                                                                                                                                        {
                                                                                                                                            ERR (TS, Z150, 0x017A, 0x00, 0x00, 0x00, Local0)
                                                                                                                                        }
                                                                                                                                        Else
                                                                                                                                        {
                                                                                                                                            If (Arg0)
                                                                                                                                            {
                                                                                                                                                Release (MTF1)
                                                                                                                                            }

                                                                                                                                            Release (MTF0)
                                                                                                                                            Release (MTE1)
                                                                                                                                            Release (MTE0)
                                                                                                                                            Release (MTD1)
                                                                                                                                            Release (MTD0)
                                                                                                                                            Release (MTC1)
                                                                                                                                            Release (MTC0)
                                                                                                                                            Release (MTB1)
                                                                                                                                            Release (MTB0)
                                                                                                                                            Release (MTA1)
                                                                                                                                            Release (MTA0)
                                                                                                                                            Release (MT91)
                                                                                                                                            Release (MT90)
                                                                                                                                            Release (MT81)
                                                                                                                                            Release (MT80)
                                                                                                                                            Release (MT71)
                                                                                                                                            Release (MT70)
                                                                                                                                            Release (MT61)
                                                                                                                                            Release (MT60)
                                                                                                                                            Release (MT51)
                                                                                                                                            Release (MT50)
                                                                                                                                            Release (MT41)
                                                                                                                                            Release (MT40)
                                                                                                                                            Release (MT31)
                                                                                                                                            Release (MT30)
                                                                                                                                            Release (MT21)
                                                                                                                                            Release (MT20)
                                                                                                                                            Release (MT11)
                                                                                                                                            Release (MT10)
                                                                                                                                            Release (\_GL)
                                                                                                                                            Release (MT01)
                                                                                                                                            Release (MT00)
                                                                                                                                        }
                                                                                                                                    }
                                                                                                                                }
                                                                                                                            }
                                                                                                                        }
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        If (Arg0)
        {
            CH04 (TS, 0x01, 0x12, Z150, 0x01C2, 0x00, 0x00) /* AE_LIMIT */
        }
        Else
        {
            CH03 (TS, Z150, 0x0123, 0x01C4, 0x00)
        }
    }

    /*
     * Valid sequence of requests, no exceptions expected.
     *
     * Acquire mutexes of monotone increasing level (Global lock
     * on level 0 too) for all available levels from 0 up to 15,
     * then Release them all in the inverse order.
     *
     * Exactly m301 but additioanlly:
     *    all Release opreations are located into separate method.
     */
    Method (M36A, 0, Serialized)
    {
        Mutex (MT00, 0x00)
        Mutex (MT10, 0x01)
        Mutex (MT20, 0x02)
        Mutex (MT30, 0x03)
        Mutex (MT40, 0x04)
        Mutex (MT50, 0x05)
        Mutex (MT60, 0x06)
        Mutex (MT70, 0x07)
        Mutex (MT80, 0x08)
        Mutex (MT90, 0x09)
        Mutex (MTA0, 0x0A)
        Mutex (MTB0, 0x0B)
        Mutex (MTC0, 0x0C)
        Mutex (MTD0, 0x0D)
        Mutex (MTE0, 0x0E)
        Mutex (MTF0, 0x0F)
        Name (TS, "m36a")
        Method (M000, 0, NotSerialized)
        {
            Local0 = Acquire (MT00, 0xFFFF)
            If (Local0)
            {
                ERR (TS, Z150, 0x01EC, 0x00, 0x00, 0x00, Local0)
            }
            Else
            {
                Local0 = Acquire (\_GL, 0xFFFF)
                If (Local0)
                {
                    ERR (TS, Z150, 0x01F0, 0x00, 0x00, 0x00, Local0)
                }
                Else
                {
                    Local0 = Acquire (MT10, 0xFFFF)
                    If (Local0)
                    {
                        ERR (TS, Z150, 0x01F4, 0x00, 0x00, 0x00, Local0)
                    }
                    Else
                    {
                        Local0 = Acquire (MT20, 0xFFFF)
                        If (Local0)
                        {
                            ERR (TS, Z150, 0x01F8, 0x00, 0x00, 0x00, Local0)
                        }
                        Else
                        {
                            Local0 = Acquire (MT30, 0xFFFF)
                            If (Local0)
                            {
                                ERR (TS, Z150, 0x01FC, 0x00, 0x00, 0x00, Local0)
                            }
                            Else
                            {
                                Local0 = Acquire (MT40, 0xFFFF)
                                If (Local0)
                                {
                                    ERR (TS, Z150, 0x0200, 0x00, 0x00, 0x00, Local0)
                                }
                                Else
                                {
                                    Local0 = Acquire (MT50, 0xFFFF)
                                    If (Local0)
                                    {
                                        ERR (TS, Z150, 0x0204, 0x00, 0x00, 0x00, Local0)
                                    }
                                    Else
                                    {
                                        Local0 = Acquire (MT60, 0xFFFF)
                                        If (Local0)
                                        {
                                            ERR (TS, Z150, 0x0208, 0x00, 0x00, 0x00, Local0)
                                        }
                                        Else
                                        {
                                            Local0 = Acquire (MT70, 0xFFFF)
                                            If (Local0)
                                            {
                                                ERR (TS, Z150, 0x020C, 0x00, 0x00, 0x00, Local0)
                                            }
                                            Else
                                            {
                                                Local0 = Acquire (MT80, 0xFFFF)
                                                If (Local0)
                                                {
                                                    ERR (TS, Z150, 0x0210, 0x00, 0x00, 0x00, Local0)
                                                }
                                                Else
                                                {
                                                    Local0 = Acquire (MT90, 0xFFFF)
                                                    If (Local0)
                                                    {
                                                        ERR (TS, Z150, 0x0214, 0x00, 0x00, 0x00, Local0)
                                                    }
                                                    Else
                                                    {
                                                        Local0 = Acquire (MTA0, 0xFFFF)
                                                        If (Local0)
                                                        {
                                                            ERR (TS, Z150, 0x0218, 0x00, 0x00, 0x00, Local0)
                                                        }
                                                        Else
                                                        {
                                                            Local0 = Acquire (MTB0, 0xFFFF)
                                                            If (Local0)
                                                            {
                                                                ERR (TS, Z150, 0x021C, 0x00, 0x00, 0x00, Local0)
                                                            }
                                                            Else
                                                            {
                                                                Local0 = Acquire (MTC0, 0xFFFF)
                                                                If (Local0)
                                                                {
                                                                    ERR (TS, Z150, 0x0220, 0x00, 0x00, 0x00, Local0)
                                                                }
                                                                Else
                                                                {
                                                                    Local0 = Acquire (MTD0, 0xFFFF)
                                                                    If (Local0)
                                                                    {
                                                                        ERR (TS, Z150, 0x0224, 0x00, 0x00, 0x00, Local0)
                                                                    }
                                                                    Else
                                                                    {
                                                                        Local0 = Acquire (MTE0, 0xFFFF)
                                                                        If (Local0)
                                                                        {
                                                                            ERR (TS, Z150, 0x0228, 0x00, 0x00, 0x00, Local0)
                                                                        }
                                                                        Else
                                                                        {
                                                                            Local0 = Acquire (MTF0, 0xFFFF)
                                                                            If (Local0)
                                                                            {
                                                                                ERR (TS, Z150, 0x022C, 0x00, 0x00, 0x00, Local0)
                                                                            }
                                                                            Else
                                                                            {
                                                                                M001 ()
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        /* m000 */

        Method (M001, 0, NotSerialized)
        {
            Release (MTF0)
            Release (MTE0)
            Release (MTD0)
            Release (MTC0)
            Release (MTB0)
            Release (MTA0)
            Release (MT90)
            Release (MT80)
            Release (MT70)
            Release (MT60)
            Release (MT50)
            Release (MT40)
            Release (MT30)
            Release (MT20)
            Release (MT10)
            Release (\_GL)
            Release (MT00)
        }

        CH03 (TS, Z150, 0x12, 0x0257, 0x00)
        M000 ()
        CH03 (TS, Z150, 0x13, 0x0259, 0x00)
    }

    /*
     * Valid sequence of requests, no exceptions expected.
     *
     * Acquire mutexes of monotone increasing level (Global lock
     * on level 0 too) for all available levels from 0 up to 15,
     * then Release them all in the inverse order.
     *
     * Exactly m301 but additioanlly:
     *    all Acquire and Release opreations are located into separate methods.
     */
    Method (M36B, 0, Serialized)
    {
        Mutex (MT00, 0x00)
        Mutex (MT10, 0x01)
        Mutex (MT20, 0x02)
        Mutex (MT30, 0x03)
        Mutex (MT40, 0x04)
        Mutex (MT50, 0x05)
        Mutex (MT60, 0x06)
        Mutex (MT70, 0x07)
        Mutex (MT80, 0x08)
        Mutex (MT90, 0x09)
        Mutex (MTA0, 0x0A)
        Mutex (MTB0, 0x0B)
        Mutex (MTC0, 0x0C)
        Mutex (MTD0, 0x0D)
        Mutex (MTE0, 0x0E)
        Mutex (MTF0, 0x0F)
        Name (TS, "m36b")
        Method (M000, 0, NotSerialized)
        {
            Local0 = Acquire (MT00, 0xFFFF)
            If (Local0)
            {
                ERR (TS, Z150, 0x0280, 0x00, 0x00, 0x00, Local0)
            }
            Else
            {
                Local0 = Acquire (\_GL, 0xFFFF)
                If (Local0)
                {
                    ERR (TS, Z150, 0x0284, 0x00, 0x00, 0x00, Local0)
                }
                Else
                {
                    Local0 = Acquire (MT10, 0xFFFF)
                    If (Local0)
                    {
                        ERR (TS, Z150, 0x0288, 0x00, 0x00, 0x00, Local0)
                    }
                    Else
                    {
                        Local0 = Acquire (MT20, 0xFFFF)
                        If (Local0)
                        {
                            ERR (TS, Z150, 0x028C, 0x00, 0x00, 0x00, Local0)
                        }
                        Else
                        {
                            Local0 = Acquire (MT30, 0xFFFF)
                            If (Local0)
                            {
                                ERR (TS, Z150, 0x0290, 0x00, 0x00, 0x00, Local0)
                            }
                            Else
                            {
                                Local0 = Acquire (MT40, 0xFFFF)
                                If (Local0)
                                {
                                    ERR (TS, Z150, 0x0294, 0x00, 0x00, 0x00, Local0)
                                }
                                Else
                                {
                                    Local0 = Acquire (MT50, 0xFFFF)
                                    If (Local0)
                                    {
                                        ERR (TS, Z150, 0x0298, 0x00, 0x00, 0x00, Local0)
                                    }
                                    Else
                                    {
                                        Local0 = Acquire (MT60, 0xFFFF)
                                        If (Local0)
                                        {
                                            ERR (TS, Z150, 0x029C, 0x00, 0x00, 0x00, Local0)
                                        }
                                        Else
                                        {
                                            Local0 = Acquire (MT70, 0xFFFF)
                                            If (Local0)
                                            {
                                                ERR (TS, Z150, 0x02A0, 0x00, 0x00, 0x00, Local0)
                                            }
                                            Else
                                            {
                                                Local0 = Acquire (MT80, 0xFFFF)
                                                If (Local0)
                                                {
                                                    ERR (TS, Z150, 0x02A4, 0x00, 0x00, 0x00, Local0)
                                                }
                                                Else
                                                {
                                                    Local0 = Acquire (MT90, 0xFFFF)
                                                    If (Local0)
                                                    {
                                                        ERR (TS, Z150, 0x02A8, 0x00, 0x00, 0x00, Local0)
                                                    }
                                                    Else
                                                    {
                                                        Local0 = Acquire (MTA0, 0xFFFF)
                                                        If (Local0)
                                                        {
                                                            ERR (TS, Z150, 0x02AC, 0x00, 0x00, 0x00, Local0)
                                                        }
                                                        Else
                                                        {
                                                            Local0 = Acquire (MTB0, 0xFFFF)
                                                            If (Local0)
                                                            {
                                                                ERR (TS, Z150, 0x02B0, 0x00, 0x00, 0x00, Local0)
                                                            }
                                                            Else
                                                            {
                                                                Local0 = Acquire (MTC0, 0xFFFF)
                                                                If (Local0)
                                                                {
                                                                    ERR (TS, Z150, 0x02B4, 0x00, 0x00, 0x00, Local0)
                                                                }
                                                                Else
                                                                {
                                                                    Local0 = Acquire (MTD0, 0xFFFF)
                                                                    If (Local0)
                                                                    {
                                                                        ERR (TS, Z150, 0x02B8, 0x00, 0x00, 0x00, Local0)
                                                                    }
                                                                    Else
                                                                    {
                                                                        Local0 = Acquire (MTE0, 0xFFFF)
                                                                        If (Local0)
                                                                        {
                                                                            ERR (TS, Z150, 0x02BC, 0x00, 0x00, 0x00, Local0)
                                                                        }
                                                                        Else
                                                                        {
                                                                            Local0 = Acquire (MTF0, 0xFFFF)
                                                                            If (Local0)
                                                                            {
                                                                                ERR (TS, Z150, 0x02C0, 0x00, 0x00, 0x00, Local0)
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        /* m000 */

        Method (M001, 0, NotSerialized)
        {
            Release (MTF0)
            Release (MTE0)
            Release (MTD0)
            Release (MTC0)
            Release (MTB0)
            Release (MTA0)
            Release (MT90)
            Release (MT80)
            Release (MT70)
            Release (MT60)
            Release (MT50)
            Release (MT40)
            Release (MT30)
            Release (MT20)
            Release (MT10)
            Release (\_GL)
            Release (MT00)
        }

        CH03 (TS, Z150, 0x12, 0x02E9, 0x00)
        M000 ()
        CH03 (TS, Z150, 0x13, 0x02EB, 0x00)
        M001 ()
        CH03 (TS, Z150, 0x14, 0x02ED, 0x00)
    }

    /*
     * Invalid sequence of Acquire operations:
     *
     *   1) Acquire N-th level mutex (N>=1):
     *   2) Acquire:
     *      - mutexes from 0 up to (N-1)-levels
     *      - Global lock
     *   3) exception AE_AML_MUTEX_ORDER is expected for each Acquire of (2)
     */
    Method (M36C, 0, Serialized)
    {
        Name (TS, "m36c")
        Name (LPN0, 0x00)
        Name (LPC0, 0x00)
        /*
         * arg0 - level of mutex to be acquired first
         * arg1 - level of mutex to be acquired second
         * arg2 - 1 - acquire 0-level mutex instead of arg1
         *        2 - acquire Global lock   instead of arg1
         */
        Method (M000, 3, Serialized)
        {
            /* Acquire the first mutex */

            CH03 (TS, Z150, 0x00, 0x0309, 0x00)
            M36F (Arg0, 0x00, 0x00, 0x00) /* Acquire N-level mutex */
            CH03 (TS, Z150, 0x01, 0x030B, 0x00)
            /*
             * Attempt to Acquire the second mutex (exception is expected).
             *
             * It is supposed that the second acquired
             * is a mutex of level not greater than (N-1)
             */
            Switch (ToInteger (Arg2))
            {
                Case (0x01)
                {
                    M36F (0x00, 0x00, 0x01, 0x00) /* Acquire 0 level mux */
                }
                Case (0x02)
                {
                    M36F (GLLL, GLIX, 0x01, 0x00) /* Acquire GL */
                }
                Default
                {
                    M36F (Arg1, 0x00, 0x01, 0x00) /* Acquire arg1-level mux */
                }

            }

            CH04 (TS, 0x00, 0x40, Z150, 0x031E, 0x00, 0x00) /* AE_AML_MUTEX_ORDER */
            M388 (Arg0, 0x00, 0x00) /* Release */
            CH03 (TS, Z150, 0x03, 0x0322, 0x00)
        }

        /*
         * The second Acquires are run in range from 0 up to (N-1) levels
         *
         * arg0 - N level (to be in range from 1 up to 15)
         */
        Method (M001, 1, Serialized)
        {
            Name (LPN0, 0x00)
            Name (LPC0, 0x00)
            LPN0 = Arg0
            LPC0 = 0x00
            While (LPN0)
            {
                M000 (Arg0, LPC0, 0x00)
                LPN0--
                LPC0++
            }
        }

        /* From 1 up to 15 levels */

        LPN0 = (MAX0 - 0x01)
        LPC0 = 0x01
        While (LPN0)
        {
            If (LPC0)
            {
                M001 (LPC0)
                M000 (LPC0, 0x00, 0x01) /* 0 level mux */
                M000 (LPC0, 0x00, 0x02) /* GL */
            }

            LPN0--
            LPC0++
        }
    }

    /*
     * Exception on Release.
     * Release mutex twice.
     *
     * Attempt to Release free mutex: Acquire, Release, Release.
     * Exception is expected on the second Release.
     * Do it for all level mutexes and Global lock too.
     */
    Method (M389, 0, Serialized)
    {
        Name (TS, "m389")
        Name (LPN0, 0x00)
        Name (LPC0, 0x00)
        /* arg0 - level of mutex */

        Method (M000, 1, NotSerialized)
        {
            CH03 (TS, Z150, 0x00, 0x0358, 0x00)
            M36F (Arg0, 0x00, 0x00, 0x00) /* Acquire */
            M388 (Arg0, 0x00, 0x00) /* Release */
            CH03 (TS, Z150, 0x01, 0x035B, 0x00)
            /* Attempt to Release free mutex */

            M388 (Arg0, 0x00, 0x00) /* Release */
            CH04 (TS, 0x00, 0x41, Z150, 0x035F, 0x00, 0x00) /* AE_AML_MUTEX_NOT_ACQUIRED */
            CH03 (TS, Z150, 0x03, 0x0361, 0x00)
            M36F (Arg0, 0x00, 0x00, 0x00) /* Acquire */
            M388 (Arg0, 0x00, 0x00) /* Release */
            CH03 (TS, Z150, 0x04, 0x0364, 0x00)
        }

        LPN0 = MAX0 /* \MAX0 */
        LPC0 = 0x00
        While (LPN0)
        {
            M000 (LPC0)
            LPN0--
            LPC0++
        }

        /* Separately for GL */

        CH03 (TS, Z150, 0x05, 0x0371, 0x00)
        M36F (GLLL, GLIX, 0x00, 0x00) /* Acquire */
        M388 (GLLL, GLIX, 0x00) /* Release */
        CH03 (TS, Z150, 0x06, 0x0374, 0x00)
        /* Attempt to Release free mutex */

        M388 (GLLL, GLIX, 0x00) /* Release */
        CH04 (TS, 0x00, 0x41, Z150, 0x0378, 0x00, 0x00) /* AE_AML_MUTEX_NOT_ACQUIRED */
        CH03 (TS, Z150, 0x08, 0x037A, 0x00)
        M36F (GLLL, GLIX, 0x00, 0x00) /* Acquire */
        M388 (GLLL, GLIX, 0x00) /* Release */
        CH03 (TS, Z150, 0x09, 0x037D, 0x00)
    }

    /*
     * Exception on Release.
     * Attempt ot Release clean mutex which was never Acquired.
     */
    Method (M07B, 0, Serialized)
    {
        Name (TS, "m07b")
        Mutex (T000, 0x00)
        Mutex (T100, 0x01)
        Mutex (T200, 0x02)
        Mutex (T300, 0x03)
        Mutex (T400, 0x04)
        Mutex (T500, 0x05)
        Mutex (T600, 0x06)
        Mutex (T700, 0x07)
        Mutex (T800, 0x08)
        Mutex (T900, 0x09)
        Mutex (TA00, 0x0A)
        Mutex (TB00, 0x0B)
        Mutex (TC00, 0x0C)
        Mutex (TD00, 0x0D)
        Mutex (TE00, 0x0E)
        Mutex (TF00, 0x0F)
        /* First time */

        CH03 (TS, Z150, 0x00, 0x039B, 0x00)
        Release (T000)
        CH04 (TS, 0x00, 0x41, Z150, 0x039D, 0x00, 0x00) /* AE_AML_MUTEX_NOT_ACQUIRED */
        CH03 (TS, Z150, 0x02, 0x039F, 0x00)
        Release (\_GL)
        CH04 (TS, 0x00, 0x41, Z150, 0x03A1, 0x00, 0x00)
        CH03 (TS, Z150, 0x04, 0x03A3, 0x00)
        Release (T100)
        CH04 (TS, 0x00, 0x41, Z150, 0x03A5, 0x00, 0x00)
        CH03 (TS, Z150, 0x06, 0x03A7, 0x00)
        Release (T200)
        CH04 (TS, 0x00, 0x41, Z150, 0x03A9, 0x00, 0x00)
        CH03 (TS, Z150, 0x08, 0x03AB, 0x00)
        Release (T300)
        CH04 (TS, 0x00, 0x41, Z150, 0x03AD, 0x00, 0x00)
        CH03 (TS, Z150, 0x0A, 0x03AF, 0x00)
        Release (T400)
        CH04 (TS, 0x00, 0x41, Z150, 0x03B1, 0x00, 0x00)
        CH03 (TS, Z150, 0x0C, 0x03B3, 0x00)
        Release (T500)
        CH04 (TS, 0x00, 0x41, Z150, 0x03B5, 0x00, 0x00)
        CH03 (TS, Z150, 0x0E, 0x03B7, 0x00)
        Release (T600)
        CH04 (TS, 0x00, 0x41, Z150, 0x03B9, 0x00, 0x00)
        CH03 (TS, Z150, 0x10, 0x03BB, 0x00)
        Release (T700)
        CH04 (TS, 0x00, 0x41, Z150, 0x03BD, 0x00, 0x00)
        CH03 (TS, Z150, 0x12, 0x03BF, 0x00)
        Release (T800)
        CH04 (TS, 0x00, 0x41, Z150, 0x03C1, 0x00, 0x00)
        CH03 (TS, Z150, 0x14, 0x03C3, 0x00)
        Release (T900)
        CH04 (TS, 0x00, 0x41, Z150, 0x03C5, 0x00, 0x00)
        CH03 (TS, Z150, 0x16, 0x03C7, 0x00)
        Release (TA00)
        CH04 (TS, 0x00, 0x41, Z150, 0x03C9, 0x00, 0x00)
        CH03 (TS, Z150, 0x18, 0x03CB, 0x00)
        Release (TB00)
        CH04 (TS, 0x00, 0x41, Z150, 0x03CD, 0x00, 0x00)
        CH03 (TS, Z150, 0x1A, 0x03CF, 0x00)
        Release (TC00)
        CH04 (TS, 0x00, 0x41, Z150, 0x03D1, 0x00, 0x00)
        CH03 (TS, Z150, 0x1C, 0x03D3, 0x00)
        Release (TD00)
        CH04 (TS, 0x00, 0x41, Z150, 0x03D5, 0x00, 0x00)
        CH03 (TS, Z150, 0x1E, 0x03D7, 0x00)
        Release (TE00)
        CH04 (TS, 0x00, 0x41, Z150, 0x03D9, 0x00, 0x00)
        CH03 (TS, Z150, 0x20, 0x03DB, 0x00)
        Release (TF00)
        CH04 (TS, 0x00, 0x41, Z150, 0x03DD, 0x00, 0x00)
        /* Second time */

        CH03 (TS, Z150, 0x22, 0x03E2, 0x00)
        Release (T000)
        CH04 (TS, 0x00, 0x41, Z150, 0x03E4, 0x00, 0x00) /* AE_AML_MUTEX_NOT_ACQUIRED */
        CH03 (TS, Z150, 0x24, 0x03E6, 0x00)
        Release (T100)
        CH04 (TS, 0x00, 0x41, Z150, 0x03E8, 0x00, 0x00)
        CH03 (TS, Z150, 0x26, 0x03EA, 0x00)
        Release (T200)
        CH04 (TS, 0x00, 0x41, Z150, 0x03EC, 0x00, 0x00)
        CH03 (TS, Z150, 0x28, 0x03EE, 0x00)
        Release (T300)
        CH04 (TS, 0x00, 0x41, Z150, 0x03F0, 0x00, 0x00)
        CH03 (TS, Z150, 0x2A, 0x03F2, 0x00)
        Release (T400)
        CH04 (TS, 0x00, 0x41, Z150, 0x03F4, 0x00, 0x00)
        CH03 (TS, Z150, 0x2C, 0x03F6, 0x00)
        Release (T500)
        CH04 (TS, 0x00, 0x41, Z150, 0x03F8, 0x00, 0x00)
        CH03 (TS, Z150, 0x2E, 0x03FA, 0x00)
        Release (T600)
        CH04 (TS, 0x00, 0x41, Z150, 0x03FC, 0x00, 0x00)
        CH03 (TS, Z150, 0x30, 0x03FE, 0x00)
        Release (T700)
        CH04 (TS, 0x00, 0x41, Z150, 0x0400, 0x00, 0x00)
        CH03 (TS, Z150, 0x32, 0x0402, 0x00)
        Release (T800)
        CH04 (TS, 0x00, 0x41, Z150, 0x0404, 0x00, 0x00)
        CH03 (TS, Z150, 0x34, 0x0406, 0x00)
        Release (T900)
        CH04 (TS, 0x00, 0x41, Z150, 0x0408, 0x00, 0x00)
        CH03 (TS, Z150, 0x36, 0x040A, 0x00)
        Release (TA00)
        CH04 (TS, 0x00, 0x41, Z150, 0x040C, 0x00, 0x00)
        CH03 (TS, Z150, 0x38, 0x040E, 0x00)
        Release (TB00)
        CH04 (TS, 0x00, 0x41, Z150, 0x0410, 0x00, 0x00)
        CH03 (TS, Z150, 0x3A, 0x0412, 0x00)
        Release (TC00)
        CH04 (TS, 0x00, 0x41, Z150, 0x0414, 0x00, 0x00)
        CH03 (TS, Z150, 0x3C, 0x0416, 0x00)
        Release (TD00)
        CH04 (TS, 0x00, 0x41, Z150, 0x0418, 0x00, 0x00)
        CH03 (TS, Z150, 0x3E, 0x041A, 0x00)
        Release (TE00)
        CH04 (TS, 0x00, 0x41, Z150, 0x041C, 0x00, 0x00)
        CH03 (TS, Z150, 0x40, 0x041E, 0x00)
        Release (TF00)
        CH04 (TS, 0x00, 0x41, Z150, 0x0420, 0x00, 0x00)
    }

    /*
     * Exception on Release.
     * Break the sequence of Acquiring mutexes while Releasing them,
     * jump over the level.
     *
     * Invalid sequence of Releases:
     *
     *   1) Take level from range (N>=1 & N<=15)
     *   2) Acquire mutexes of all levels from 0 up to N
     *   3) Try to Release any mutex:
     *      - in the level range from (N-1) down to 0
     *      - Global lock
     *   4) Do 1-3 for all levels in range (N>=1 & N<=15)
     */
    Method (M38A, 0, Serialized)
    {
        Name (LPN0, 0x00)
        Name (LPC0, 0x00)
        Name (BR00, 0x00)
        LPN0 = (MAX0 - 0x01)
        LPC0 = 0x02
        While (LPN0)
        {
            /* Acquire lpC0 levels from 0 level */

            M38B (0x00, LPC0, 0x01, 0x00)
            /*
             * Exception is expected on each Release there.
             *
             * Break the sequence of Acquiring mutexes while Releasing them,
             * jump over the level.
             * Run Releasing mutexes NOT from (lpC0-1) level which whould be
             * correct but from (lpC0-2) level down to 0 level so jumping over
             * the mutex of (lpC0-1) level which is Acquired which should cause
             * each of these Releases to generate AE_AML_MUTEX_ORDER exception.
             */
            Local0 = (LPC0 - 0x02)
            Local1 = (LPC0 - 0x01)
            If (M38C (Local0, Local1, 0x01, 0x40))
            {
                /* AE_AML_MUTEX_ORDER */
                /*
                 * Break for the first bunch of errors encountered,
                 * dont waste log.
                 */
                BR00 = 0x01
            }

            /*
             * Correct sequence of Releases.
             * Release lpC0 levels from (lpC0-1) down to 0 level.
             */
            If (BR00)
            {
                M36F (HLMX, 0x00, 0x00, 0x00)
                M388 (HLMX, 0x00, 0x00)
            }

            Local0 = (LPC0 - 0x01)
            M38C (Local0, LPC0, 0x01, 0x00)
            If (BR00)
            {
                Break
            }

            LPN0--
            LPC0++
        }

        CH03 ("m38a", Z150, 0x00, 0x046B, 0x00)
    }

    /*
     * Manager for m38d.
     *
     * arg0 - the value of flag of GL
     * arg1 - order of Releasing bitmap (see m089)
     */
    Method (M08C, 2, Serialized)
    {
        Name (LPN0, 0x00)
        Name (LPC0, 0x00)
        /*
         * arg0 - Level of mutex
         * arg1 - the value of flag of GL
         * arg2 - order of Releasing bitmap (see m089)
         */
        Method (M000, 3, NotSerialized)
        {
            /* Set up the value of flag of Global lock */

            Local7 = M078 (Arg1)
            /*
             * min0 - number of mutexes existent for each level
             *
             * Acquire mutexes of level arg0
             * in the order from 0 index up
             * to (min0-1) one, then Release
             * them in the order specified
             * by arg2.
             */
            M088 (Arg0, 0x01, 0x00, MIN0, 0x00, 0x00, 0x00)    /* Acquire */
            M089 (Arg0, 0x01, 0x00, MIN0, 0x00, 0x00, Arg2) /* Release */
            /* Restore the value of flag of Global lock */

            M078 (Local7)
        }

        /* For each level */

        LPN0 = MAX0 /* \MAX0 */
        LPC0 = 0x00
        While (LPN0)
        {
            M000 (LPC0, Arg0, Arg1)
            LPN0--
            LPC0++
        }
    }

    /*
     * Check up that the Releasing of the same level mutexes
     * can be performed in an arbitrary order, independently
     * on the order they were Acquired.
     *
     * For each level separately, one by one.
     */
    Method (M38D, 0, NotSerialized)
    {
        M08C (0x00, 0x00) /* direct  order of Releasing, Mutex(0,1) is usual mutex */
        M08C (0x00, 0x01) /* inverse order of Releasing, Mutex(0,1) is usual mutex */
        M08C (0x01, 0x00) /* direct  order of Releasing, Mutex(0,1) is GL */
        M08C (0x01, 0x01) /* inverse order of Releasing, Mutex(0,1) is GL */
        /* Check that all mutexes are Released */

        M08A ()
    }

    /*
     * Check up that the Releasing of the same level mutexes
     * can be performed in an arbitrary order, independently
     * on the order they were Acquired.
     *
     * Cross through all the levels.
     *
     * arg0 - order of Releasing bitmap (see m089)
     */
    Method (M07D, 1, NotSerialized)
    {
        M088 (0x00, MAX0, 0x00, MIN0, 0x00, 0x00, 0x00)    /* Acquire all mutexes on all levels */
        M089 (0x00, MAX0, 0x00, MIN0, 0x00, 0x00, Arg0) /* Release all mutexes on all levels */
    }

    /*
     * ACPI allows multiply own the same mutex
     *
     * arg0 - the value of flag of GL
     */
    Method (M07A, 1, NotSerialized)
    {
        M079 (0x0A, Arg0)
    }

    /*
     * Multiply owning the same ACPI mutex.
     * Acquire the same mutex arg2 times, then Release it (arg2+1) times,
     * expect exception on the last Release.
     * The repeated Acquire are made with TimeoutValue equal to zero.
     *
     * arg0 - how many times to Acquire it
     * arg1 - the value of flag of GL
     */
    Method (M079, 2, Serialized)
    {
        Name (TS, "m079")
        Name (LPN0, 0x00)
        Name (LPC0, 0x00)
        Name (LPN1, 0x00)
        Name (LPC1, 0x00)
        Name (TOUT, 0x00)
        Name (IX00, 0x01)
        /* Set up the value of flag of Global lock */

        Local7 = M078 (Arg1)
        /* Acquire */
        /* levels */
        LPN0 = MAX0 /* \MAX0 */
        LPC0 = 0x00
        While (LPN0)
        {
            /* repetitions */

            LPN1 = Arg0
            LPC1 = 0x00
            While (LPN1)
            {
                If (LPC1)
                {
                    TOUT = TOV0 /* TimeOutValue equal to 0 */ /* \TOV0 */
                }
                Else
                {
                    TOUT = 0x00 /* TimeOutValue equal to 0xffff (once for the first Acquire) */
                }

                M36F (LPC0, IX00, 0x00, TOUT)
                LPN1--
                LPC1++
            }

            LPN0--
            LPC0++
        }

        /* Release */

        CH03 (TS, Z150, 0x00, 0x04FA, 0x00)
        LPN0 = MAX0 /* \MAX0 */
        LPC0 = (MAX0 - 0x01)
        While (LPN0)
        {
            /* repetitions */

            LPN1 = Arg0
            LPC1 = 0x00
            While (LPN1)
            {
                M388 (LPC0, IX00, 0x00)
                LPN1--
                LPC1++
            }

            LPN0--
            LPC0--
        }

        /* The 'owning counters' are exhausted, so exceptions are expected */

        LPN0 = MAX0 /* \MAX0 */
        LPC0 = (MAX0 - 0x01)
        While (LPN0)
        {
            CH03 (TS, Z150, 0x01, 0x0510, 0x00)
            M388 (LPC0, IX00, 0x00)
            CH04 (TS, 0x00, 0x41, Z150, 0x0512, 0x00, 0x00) /* AE_AML_MUTEX_NOT_ACQUIRED */
            LPN0--
            LPC0--
        }

        /* Restore the value of flag of Global lock */

        M078 (Local7)
    }

    /*
     * /////////////////////////////////////////
     *
     *    The tests below examine different ways
     *    to Acquire/Release mutexes
     *
     * /////////////////////////////////////////
     */
    /*
     * ATTENTION: this test must be run the first
     *
     * Different ways to Acquire/Release mutexes
     *
     * 1) Acquire and Release operations are in a global level AML code
     *
     * See m07c.
     */
    Method (M0B9, 0, Serialized)
    {
        Name (TS, "m0b9")
        /* i101 - non-zero means that the test was run */

        If (!I101)
        {
            Return (Zero)
        }

        CH03 (TS, Z150, 0x00, 0x0537, 0x00)
    }

    /*
     * The same operations as m0b9 (the test for global level AML code)
     * but enclosed into Method.
     */
    Method (M0BB, 0, Serialized)
    {
        Name (TS, "m0bb")
        CH03 (TS, Z150, 0x00, 0x0543, 0x00)
        Method (M137, 0, NotSerialized)
        {
            Debug = "m137 started"
            If (!I102)
            {
                Release (T804)
            }

            Debug = "m137 completed"
            Return (0x01)
        }

        Method (M13E, 0, NotSerialized)
        {
            Debug = "m13e started"
            I103 = Acquire (T805, 0xFFFF)
            If (I103)
            {
                ERR (TS, Z150, 0x0557, 0x00, 0x00, 0x00, I103)
            }

            Debug = "m13e completed"
            Return (0x01)
        }

        Method (M13F, 0, NotSerialized)
        {
            Debug = "m13f started"
            If (!I103)
            {
                Release (T805)
            }

            Debug = "m13f completed"
            Return (0x01)
        }

        Name (I102, 0x01)
        Name (I103, 0x01)
        Name (B11C, Buffer ((0x01 + I102 = Acquire (T804, 0xFFFF)))
        {
             0x00                                             // .
        })
        Name (B11D, Buffer (M137 ())
        {
             0x00                                             // .
        })
        Name (B11E, Buffer (M13E ())
        {
             0x00                                             // .
        })
        Name (B11F, Buffer (M13F ())
        {
             0x00                                             // .
        })
        If (I102)
        {
            Debug = "Acquire(T804, 0xffff) failed"
            ERR (TS, Z150, 0x0575, 0x00, 0x00, 0x00, I102)
        }

        If (I103)
        {
            Debug = "Acquire(T805, 0xffff) failed"
            ERR (TS, Z150, 0x057A, 0x00, 0x00, 0x00, I103)
        }

        CH03 (TS, Z150, 0x04, 0x057D, 0x00)
    }

    /*
     * Different ways to Acquire/Release mutexes
     *
     * 2) Acquire and Release operations are in the same method
     * 3) Acquire and Release operations are in different methods
     *
     * See m0b9.
     */
    Method (M07C, 0, Serialized)
    {
        Name (TS, "m07c")
        /* Acquire and Release operations are in the same method */

        Method (M000, 0, NotSerialized)
        {
            CH03 (TS, Z150, 0x00, 0x058F, 0x00)
            /* Acquire all */

            Local0 = Acquire (\_GL, 0xFFFF)
            If (Local0)
            {
                ERR (TS, Z150, 0x0595, 0x00, 0x00, 0x00, Local0)
            }

            Local0 = Acquire (T000, 0xFFFF)
            If (Local0)
            {
                ERR (TS, Z150, 0x059A, 0x00, 0x00, 0x00, Local0)
            }

            Local0 = Acquire (T100, 0xFFFF)
            If (Local0)
            {
                ERR (TS, Z150, 0x059F, 0x00, 0x00, 0x00, Local0)
            }

            Local0 = Acquire (T200, 0xFFFF)
            If (Local0)
            {
                ERR (TS, Z150, 0x05A4, 0x00, 0x00, 0x00, Local0)
            }

            Local0 = Acquire (T300, 0xFFFF)
            If (Local0)
            {
                ERR (TS, Z150, 0x05A9, 0x00, 0x00, 0x00, Local0)
            }

            Local0 = Acquire (T400, 0xFFFF)
            If (Local0)
            {
                ERR (TS, Z150, 0x05AE, 0x00, 0x00, 0x00, Local0)
            }

            Local0 = Acquire (T500, 0xFFFF)
            If (Local0)
            {
                ERR (TS, Z150, 0x05B3, 0x00, 0x00, 0x00, Local0)
            }

            Local0 = Acquire (T600, 0xFFFF)
            If (Local0)
            {
                ERR (TS, Z150, 0x05B8, 0x00, 0x00, 0x00, Local0)
            }

            Local0 = Acquire (T700, 0xFFFF)
            If (Local0)
            {
                ERR (TS, Z150, 0x05BD, 0x00, 0x00, 0x00, Local0)
            }

            Local0 = Acquire (T800, 0xFFFF)
            If (Local0)
            {
                ERR (TS, Z150, 0x05C2, 0x00, 0x00, 0x00, Local0)
            }

            Local0 = Acquire (T900, 0xFFFF)
            If (Local0)
            {
                ERR (TS, Z150, 0x05C7, 0x00, 0x00, 0x00, Local0)
            }

            Local0 = Acquire (TA00, 0xFFFF)
            If (Local0)
            {
                ERR (TS, Z150, 0x05CC, 0x00, 0x00, 0x00, Local0)
            }

            Local0 = Acquire (TB00, 0xFFFF)
            If (Local0)
            {
                ERR (TS, Z150, 0x05D1, 0x00, 0x00, 0x00, Local0)
            }

            Local0 = Acquire (TC00, 0xFFFF)
            If (Local0)
            {
                ERR (TS, Z150, 0x05D6, 0x00, 0x00, 0x00, Local0)
            }

            Local0 = Acquire (TD00, 0xFFFF)
            If (Local0)
            {
                ERR (TS, Z150, 0x05DB, 0x00, 0x00, 0x00, Local0)
            }

            Local0 = Acquire (TE00, 0xFFFF)
            If (Local0)
            {
                ERR (TS, Z150, 0x05E0, 0x00, 0x00, 0x00, Local0)
            }

            Local0 = Acquire (TF00, 0xFFFF)
            If (Local0)
            {
                ERR (TS, Z150, 0x05E5, 0x00, 0x00, 0x00, Local0)
            }

            CH03 (TS, Z150, 0x00, 0x05E8, 0x00)
            /* Release all */

            Release (TF00)
            Release (TE00)
            Release (TD00)
            Release (TC00)
            Release (TB00)
            Release (TA00)
            Release (T900)
            Release (T800)
            Release (T700)
            Release (T600)
            Release (T500)
            Release (T400)
            Release (T300)
            Release (T200)
            Release (T100)
            Release (T000)
            Release (\_GL)
            CH03 (TS, Z150, 0x00, 0x05FE, 0x00)
        }

        /* Acquire and Release operations are in different methods */

        Method (M001, 0, NotSerialized)
        {
            Method (MM00, 0, NotSerialized)
            {
                CH03 (TS, Z150, 0x00, 0x0606, 0x00)
                Local0 = Acquire (\_GL, 0xFFFF)
                If (Local0)
                {
                    ERR (TS, Z150, 0x060A, 0x00, 0x00, 0x00, Local0)
                }

                Local0 = Acquire (T000, 0xFFFF)
                If (Local0)
                {
                    ERR (TS, Z150, 0x060F, 0x00, 0x00, 0x00, Local0)
                }

                Local0 = Acquire (T100, 0xFFFF)
                If (Local0)
                {
                    ERR (TS, Z150, 0x0614, 0x00, 0x00, 0x00, Local0)
                }

                Local0 = Acquire (T200, 0xFFFF)
                If (Local0)
                {
                    ERR (TS, Z150, 0x0619, 0x00, 0x00, 0x00, Local0)
                }

                Local0 = Acquire (T300, 0xFFFF)
                If (Local0)
                {
                    ERR (TS, Z150, 0x061E, 0x00, 0x00, 0x00, Local0)
                }

                Local0 = Acquire (T400, 0xFFFF)
                If (Local0)
                {
                    ERR (TS, Z150, 0x0623, 0x00, 0x00, 0x00, Local0)
                }

                Local0 = Acquire (T500, 0xFFFF)
                If (Local0)
                {
                    ERR (TS, Z150, 0x0628, 0x00, 0x00, 0x00, Local0)
                }

                Local0 = Acquire (T600, 0xFFFF)
                If (Local0)
                {
                    ERR (TS, Z150, 0x062D, 0x00, 0x00, 0x00, Local0)
                }

                Local0 = Acquire (T700, 0xFFFF)
                If (Local0)
                {
                    ERR (TS, Z150, 0x0632, 0x00, 0x00, 0x00, Local0)
                }

                Local0 = Acquire (T800, 0xFFFF)
                If (Local0)
                {
                    ERR (TS, Z150, 0x0637, 0x00, 0x00, 0x00, Local0)
                }

                Local0 = Acquire (T900, 0xFFFF)
                If (Local0)
                {
                    ERR (TS, Z150, 0x063C, 0x00, 0x00, 0x00, Local0)
                }

                Local0 = Acquire (TA00, 0xFFFF)
                If (Local0)
                {
                    ERR (TS, Z150, 0x0641, 0x00, 0x00, 0x00, Local0)
                }

                Local0 = Acquire (TB00, 0xFFFF)
                If (Local0)
                {
                    ERR (TS, Z150, 0x0646, 0x00, 0x00, 0x00, Local0)
                }

                Local0 = Acquire (TC00, 0xFFFF)
                If (Local0)
                {
                    ERR (TS, Z150, 0x064B, 0x00, 0x00, 0x00, Local0)
                }

                Local0 = Acquire (TD00, 0xFFFF)
                If (Local0)
                {
                    ERR (TS, Z150, 0x0650, 0x00, 0x00, 0x00, Local0)
                }

                Local0 = Acquire (TE00, 0xFFFF)
                If (Local0)
                {
                    ERR (TS, Z150, 0x0655, 0x00, 0x00, 0x00, Local0)
                }

                Local0 = Acquire (TF00, 0xFFFF)
                If (Local0)
                {
                    ERR (TS, Z150, 0x065A, 0x00, 0x00, 0x00, Local0)
                }

                CH03 (TS, Z150, 0x00, 0x065D, 0x00)
            }

            Method (MM01, 0, NotSerialized)
            {
                CH03 (TS, Z150, 0x00, 0x0662, 0x00)
                Release (TF00)
                Release (TE00)
                Release (TD00)
                Release (TC00)
                Release (TB00)
                Release (TA00)
                Release (T900)
                Release (T800)
                Release (T700)
                Release (T600)
                Release (T500)
                Release (T400)
                Release (T300)
                Release (T200)
                Release (T100)
                Release (T000)
                Release (\_GL)
                CH03 (TS, Z150, 0x00, 0x0676, 0x00)
            }

            Method (MM02, 0, NotSerialized)
            {
                CH03 (TS, Z150, 0x00, 0x067B, 0x00)
                Release (TF00)
                CH04 (TS, 0x00, 0x41, Z150, 0x067D, 0x00, 0x00) /* AE_AML_MUTEX_NOT_ACQUIRED */
                CH03 (TS, Z150, 0x02, 0x067E, 0x00)
                Release (TE00)
                CH04 (TS, 0x00, 0x41, Z150, 0x0680, 0x00, 0x00) /* AE_AML_MUTEX_NOT_ACQUIRED */
                CH03 (TS, Z150, 0x04, 0x0681, 0x00)
                Release (TD00)
                CH04 (TS, 0x00, 0x41, Z150, 0x0683, 0x00, 0x00) /* AE_AML_MUTEX_NOT_ACQUIRED */
                CH03 (TS, Z150, 0x06, 0x0684, 0x00)
                Release (TC00)
                CH04 (TS, 0x00, 0x41, Z150, 0x0686, 0x00, 0x00) /* AE_AML_MUTEX_NOT_ACQUIRED */
                CH03 (TS, Z150, 0x08, 0x0687, 0x00)
                Release (TB00)
                CH04 (TS, 0x00, 0x41, Z150, 0x0689, 0x00, 0x00) /* AE_AML_MUTEX_NOT_ACQUIRED */
                CH03 (TS, Z150, 0x0A, 0x068A, 0x00)
                Release (TA00)
                CH04 (TS, 0x00, 0x41, Z150, 0x068C, 0x00, 0x00) /* AE_AML_MUTEX_NOT_ACQUIRED */
                CH03 (TS, Z150, 0x0C, 0x068D, 0x00)
                Release (T900)
                CH04 (TS, 0x00, 0x41, Z150, 0x068F, 0x00, 0x00) /* AE_AML_MUTEX_NOT_ACQUIRED */
                CH03 (TS, Z150, 0x0E, 0x0690, 0x00)
                Release (T800)
                CH04 (TS, 0x00, 0x41, Z150, 0x0692, 0x00, 0x00) /* AE_AML_MUTEX_NOT_ACQUIRED */
                CH03 (TS, Z150, 0x10, 0x0693, 0x00)
                Release (T700)
                CH04 (TS, 0x00, 0x41, Z150, 0x0695, 0x00, 0x00) /* AE_AML_MUTEX_NOT_ACQUIRED */
                CH03 (TS, Z150, 0x12, 0x0696, 0x00)
                Release (T600)
                CH04 (TS, 0x00, 0x41, Z150, 0x0698, 0x00, 0x00) /* AE_AML_MUTEX_NOT_ACQUIRED */
                CH03 (TS, Z150, 0x14, 0x0699, 0x00)
                Release (T500)
                CH04 (TS, 0x00, 0x41, Z150, 0x069B, 0x00, 0x00) /* AE_AML_MUTEX_NOT_ACQUIRED */
                CH03 (TS, Z150, 0x16, 0x069C, 0x00)
                Release (T400)
                CH04 (TS, 0x00, 0x41, Z150, 0x069E, 0x00, 0x00) /* AE_AML_MUTEX_NOT_ACQUIRED */
                CH03 (TS, Z150, 0x18, 0x069F, 0x00)
                Release (T300)
                CH04 (TS, 0x00, 0x41, Z150, 0x06A1, 0x00, 0x00) /* AE_AML_MUTEX_NOT_ACQUIRED */
                CH03 (TS, Z150, 0x1A, 0x06A2, 0x00)
                Release (T200)
                CH04 (TS, 0x00, 0x41, Z150, 0x06A4, 0x00, 0x00) /* AE_AML_MUTEX_NOT_ACQUIRED */
                CH03 (TS, Z150, 0x1C, 0x06A5, 0x00)
                Release (T100)
                CH04 (TS, 0x00, 0x41, Z150, 0x06A7, 0x00, 0x00) /* AE_AML_MUTEX_NOT_ACQUIRED */
                CH03 (TS, Z150, 0x1E, 0x06A8, 0x00)
                Release (T000)
                CH04 (TS, 0x00, 0x41, Z150, 0x06AA, 0x00, 0x00) /* AE_AML_MUTEX_NOT_ACQUIRED */
                CH03 (TS, Z150, 0x20, 0x06AB, 0x00)
                Release (\_GL)
                CH04 (TS, 0x00, 0x41, Z150, 0x06AD, 0x00, 0x00) /* AE_AML_MUTEX_NOT_ACQUIRED */
            }

            MM00 ()
            MM01 ()
            MM02 ()
        }

        /* Acquire and Release operations are in the same method */

        M000 ()
        /* Acquire and Release operations are in different methods */

        M001 ()
    }

    /*
     * Acquire/Release operations enclosed in other operations
     */
    Method (M0BA, 0, Serialized)
    {
        Name (TS, "m0ba")
        CH03 (TS, Z150, 0x00, 0x06C3, 0x00)
        /* Add */

        Local0 = (Acquire (\_GL, 0xFFFF) + 0x01)
        If ((Local0 != 0x01))
        {
            ERR (TS, Z150, 0x06C9, 0x00, 0x00, 0x00, Local0)
        }

        Local0 = (Acquire (T500, 0xFFFF) + 0x01)
        If ((Local0 != 0x01))
        {
            ERR (TS, Z150, 0x06CE, 0x00, 0x00, 0x00, Local0)
        }

        Release (T500)
        Release (\_GL)
        /* Subtract */

        Local0 = (0x01 - Acquire (\_GL, 0xFFFF))
        If ((Local0 != 0x01))
        {
            ERR (TS, Z150, 0x06D8, 0x00, 0x00, 0x00, Local0)
        }

        Local0 = (0x01 - Acquire (T500, 0xFFFF))
        If ((Local0 != 0x01))
        {
            ERR (TS, Z150, 0x06DD, 0x00, 0x00, 0x00, Local0)
        }

        Release (T500)
        Release (\_GL)
        /* LEqual */

        If ((Acquire (T500, 0xFFFF) != 0x00))
        {
            ERR (TS, Z150, 0x06E6, 0x00, 0x00, 0x00, Local0)
        }

        Release (T500)
        If (FL03)
        {
            /* Check that all mutexes are Released (doesn't check T804..) */

            M08A ()
        }

        CH04 (TS, 0x01, 0x40, Z150, 0x01, 0x00, 0x00)
    }

    /*
     * /////////////////////////////////////////////
     *
     *    The tests below generate some combinations
     *    of Acquire/Release operations
     *
     * /////////////////////////////////////////////
     */
    /*
     * Get 0 or 1 value pseudo randomly
     *
     * arg0 - input Integer
     */
    Method (M08E, 0, NotSerialized)
    {
        /* To be improved */

        Local0 = (CN00 & 0x01)
        CN00++
        If (!Y242)
        {
            /* Always inverse order untill the bug 242 is fixes */

            Local0 = 0x01
        }

        Return (Local0)
    }

    /*
     * Acquire/Release combination #1
     */
    Method (M07E, 0, Serialized)
    {
        Name (NUM, 0x04)
        Name (RPT0, 0x00)
        Name (RPT1, 0x03)
        Name (LPN0, 0x00)
        Name (LPC0, 0x00)
        /* Set up the value of flag of Global lock */

        Local7 = M078 (0x00)
        LPN0 = NUM /* \M07E.NUM_ */
        LPC0 = 0x00
        While (LPN0)
        {
            /* Set up the value of flag of Global lock */

            Divide (LPC0, 0x02, Local0)
            M078 (Local0)
            If (Local0)
            {
                RPT0 = RPT1 /* \M07E.RPT1 */
            }
            Else
            {
                RPT0 = 0x01
            }

            M088 (0x00, 0x03, 0x00, 0x04, 0x00, RPT0, 0x00)      /* Step  0, Acquire */
            M088 (0x03, 0x03, 0x01, 0x02, 0x00, RPT0, 0x00)      /* Step  1, Acquire */
            M089 (0x04, 0x02, 0x01, 0x02, 0x00, RPT0, M08E ()) /* Step  1, Release */
            M088 (0x05, 0x03, 0x00, 0x04, 0x00, RPT0, 0x00)      /* Step  2, Acquire */
            M089 (0x07, 0x01, 0x01, 0x03, 0x00, RPT0, M08E ()) /* Step  2, Release */
            M089 (0x07, 0x01, 0x00, 0x01, 0x00, RPT0, M08E ()) /* Step  2, Release */
            M089 (0x06, 0x01, 0x00, 0x04, 0x00, RPT0, M08E ()) /* Step  2, Release */
            M088 (0x09, 0x02, 0x02, 0x02, 0x00, RPT0, 0x00)      /* Step  3, Acquire */
            M089 (0x0A, 0x01, 0x03, 0x01, 0x00, RPT0, M08E ()) /* Step  3, Release */
            M089 (0x0A, 0x01, 0x02, 0x01, 0x00, RPT0, M08E ()) /* Step  3, Release */
            M089 (0x09, 0x01, 0x03, 0x01, 0x00, RPT0, M08E ()) /* Step  3, Release */
            M088 (0x0A, 0x02, 0x00, 0x03, 0x00, RPT0, 0x00)      /* Step  4, Acquire */
            M089 (0x0A, 0x02, 0x00, 0x03, 0x00, RPT0, M08E ()) /* Step  4, Release */
            M088 (0x0A, 0x02, 0x00, 0x03, 0x00, RPT0, 0x00)      /* Step  5, Acquire */
            M089 (0x0A, 0x02, 0x00, 0x03, 0x00, RPT0, M08E ()) /* Step  5, Release */
            M088 (0x0C, 0x02, 0x00, 0x03, 0x00, RPT0, 0x00)      /* Step  6, Acquire */
            M089 (0x0C, 0x02, 0x00, 0x03, 0x00, RPT0, M08E ()) /* Step  6, Release */
            M088 (0x0A, 0x06, 0x00, 0x04, 0x00, RPT0, 0x00)      /* Step  7, Acquire */
            M089 (0x0A, 0x06, 0x00, 0x04, 0x00, RPT0, M08E ()) /* Step  7, Release */
            M088 (0x0C, 0x02, 0x00, 0x03, 0x00, RPT0, 0x00)      /* Step  8, Acquire */
            M089 (0x0C, 0x02, 0x00, 0x03, 0x00, RPT0, M08E ()) /* Step  8, Release */
            M089 (0x09, 0x01, 0x02, 0x01, 0x00, RPT0, M08E ()) /* Step  3, Release */
            M089 (0x05, 0x01, 0x00, 0x04, 0x00, RPT0, M08E ()) /* Step  2, Release */
            M089 (0x03, 0x01, 0x01, 0x02, 0x00, RPT0, M08E ()) /* Step  1, Release */
            M089 (0x01, 0x02, 0x00, 0x04, 0x00, RPT0, M08E ()) /* Step  0, Release */
            M088 (0x01, 0x0F, 0x01, 0x02, 0x00, RPT0, 0x00)      /* Step  9, Acquire */
            M089 (0x01, 0x0F, 0x01, 0x02, 0x00, RPT0, M08E ()) /* Step  9, Release */
            M089 (0x00, 0x01, 0x01, 0x01, 0x00, RPT0, M08E ()) /* Step  0, Release */
            M089 (0x00, 0x01, 0x03, 0x01, 0x00, RPT0, M08E ()) /* Step  0, Release */
            M089 (0x00, 0x01, 0x02, 0x01, 0x00, RPT0, M08E ()) /* Step  0, Release */
            M089 (0x00, 0x01, 0x00, 0x01, 0x00, RPT0, M08E ()) /* Step  0, Release */
            M088 (0x00, 0x10, 0x01, 0x02, 0x00, RPT0, 0x00)      /* Step 10, Acquire */
            M089 (0x00, 0x10, 0x01, 0x02, 0x00, RPT0, M08E ()) /* Step 10, Release */
            LPN0--
            LPC0++
        }

        /* Restore the value of flag of Global lock */

        M078 (Local7)
        If (FL03)
        {
            /* Check that all mutexes are Released */

            M08A ()
        }
    }

    /*
     * ///////////////////////////////////////////////////
     *
     *    The tests below check behaviour after exceptions
     *
     * ///////////////////////////////////////////////////
     */
    /*
     * Check the life after AE_AML_MUTEX_ORDER exception on Acquire
     *
     *  1)     Acquire     N-th level mutex MUX-N
     *  2) run Acquire (N-2)-th level mutex MUX-(N-2) and get AE_AML_MUTEX_ORDER exception
     *  3) run Acquire (N-1)-th level mutex MUX-(N-1) and get AE_AML_MUTEX_ORDER exception
     *  4)     Acquire                mutex MUX-N and check that no exception on this operation
     *  5)     Release                mutex MUX-N and check that no exception on this operation
     *  6)     Release                mutex MUX-N and check that no exception on this operation
     *  7)     do 1-6 for all N in range 2-15 levels
     *  8)     check additionally that all the mutexes are free (run Release and
     *         get AE_AML_MUTEX_NOT_ACQUIRED exception for all the mutexes of all levels)
     *  9)     Acquire all mutexes of all levels and check that no exceptions
     * 10)     Release all mutexes of all levels and check that no exceptions
     * 11)     check additionally that all the mutexes are free (see 8)
     *
     * 12)     do it for GL mode too
     * 13)     do additional Acquire of MUX-(N-2) and MUX-(N-1) before Acquire of MUX-N (Release them later)
     *
     * arg0 - the value of flag of GL
     * arg1 - if non-zero do additional Acquire of MUX-(N-2) and MUX-(N-1) before Acquire of MUX-N
     */
    Method (M08B, 2, Serialized)
    {
        Name (RPT0, 0x01)
        Name (ORD0, 0x01)
        Name (LPN0, 0x00) /* level */
        Name (LPC0, 0x00)
        /* Set up the value of flag of Global lock */

        Local7 = M078 (Arg0)
        LPN0 = (MAX0 - 0x02)
        LPC0 = 0x02
        While (LPN0)
        {
            Local0 = (LPC0 - 0x01)
            Local1 = (LPC0 - 0x02)
            If (Arg1)
            {
                M088 (Local1, 0x01, 0x00, 0x04, 0x00, RPT0, 0x00)    /* Step -2, Acquire */
                M088 (Local0, 0x01, 0x00, 0x04, 0x00, RPT0, 0x00)    /* Step -1, Acquire */
            }

            M088 (LPC0, 0x01, 0x00, 0x01, 0x00, RPT0, 0x00)    /* Step  0, Acquire */
            M088 (Local1, 0x01, 0x00, 0x04, 0x40, RPT0, 0x00)    /* Step  1, Acquire, AE_AML_MUTEX_ORDER */
            M088 (Local0, 0x01, 0x00, 0x04, 0x40, RPT0, 0x00)    /* Step  2, Acquire, AE_AML_MUTEX_ORDER */
            M088 (LPC0, 0x01, 0x00, 0x04, 0x00, RPT0, 0x00)    /* Step  3, Acquire */
            M089 (LPC0, 0x01, 0x00, 0x04, 0x00, RPT0, ORD0) /* Step  3, Release */
            M089 (LPC0, 0x01, 0x00, 0x01, 0x00, RPT0, ORD0) /* Step  0, Release */
            If (Arg1)
            {
                M089 (Local0, 0x01, 0x00, 0x04, 0x00, RPT0, ORD0) /* Step -1, Release */
                M089 (Local1, 0x01, 0x00, 0x04, 0x00, RPT0, ORD0) /* Step -2, Release */
            }

            LPN0--
            LPC0++
        }

        /* Check that all mutexes are Released */

        M08A ()
        M088 (0x00, MAX0, 0x00, MIN0, 0x00, RPT0, 0x00)    /* Step  4, Acquire */
        M089 (0x00, MAX0, 0x00, MIN0, 0x00, RPT0, ORD0) /* Step  4, Release */
        /* Check that all mutexes are Released */

        M08A ()
        /* Restore the value of flag of Global lock */

        M078 (Local7)
    }

    /*
     * Check the life after AE_AML_MUTEX_ORDER exception on Release
     *
     *  1)     Acquire     (N-1)-th level mutex MUX-(N-1)
     *  2)     Acquire       (N)-th level mutex MUX-N
     *  3) run Release     (N-1)-th level mutex MUX-(N-1) and get AE_AML_MUTEX_ORDER exception
     *  4)     Release       (N)-th level mutex MUX-N     and check that no exception on this operation
     *  5)     Release     (N-1)-th level mutex MUX-(N-1) and check that no exception on this operation
     *  6)     do 1-5 for all N in range 1-15 levels
     *  7)     check additionally that all the mutexes are free (run Release and
     *         get AE_AML_MUTEX_NOT_ACQUIRED exception for all the mutexes of all levels)
     *  8)     Acquire all mutexes of all levels and check that no exceptions
     *  9)     Release all mutexes of all levels and check that no exceptions
     * 10)     check additionally that all the mutexes are free (see 7)
     *
     * 11)     do it for GL mode too
     *
     * arg0 - the value of flag of GL
     */
    Method (M08D, 1, Serialized)
    {
        Name (RPT0, 0x01)
        Name (ORD0, 0x01)
        Name (LPN0, 0x00) /* level */
        Name (LPC0, 0x00)
        /* Set up the value of flag of Global lock */

        Local7 = M078 (Arg0)
        LPN0 = (MAX0 - 0x01)
        LPC0 = 0x01
        While (LPN0)
        {
            Local0 = (LPC0 - 0x01)
            M088 (Local0, 0x01, 0x00, MIN0, 0x00, RPT0, 0x00)    /* Step  0, Acquire */
            M088 (LPC0, 0x01, 0x00, MIN0, 0x00, RPT0, 0x00)    /* Step  1, Acquire */
            /* Jump over the level */

            M089 (Local0, 0x01, 0x00, MIN0, 0x40, RPT0, ORD0) /* Step  2, Release, AE_AML_MUTEX_ORDER */
            M089 (LPC0, 0x01, 0x00, MIN0, 0x00, RPT0, ORD0) /* Step  1, Release */
            M089 (Local0, 0x01, 0x00, MIN0, 0x00, RPT0, ORD0) /* Step  0, Release */
            LPN0--
            LPC0++
        }

        /* Check that all mutexes are Released */

        M08A ()
        M088 (0x00, MAX0, 0x00, MIN0, 0x00, RPT0, 0x00)    /* Step  3, Acquire */
        M089 (0x00, MAX0, 0x00, MIN0, 0x00, RPT0, ORD0) /* Step  3, Release */
        /* Check that all mutexes are Released */

        M08A ()
        /* Restore the value of flag of Global lock */

        M078 (Local7)
    }

    /*
     * Check the life after AE_AML_MUTEX_ORDER exception on Release
     *
     * Similar to the m08d but trying to heal situation by
     * Acquiring/Release operations applied to the greater
     * level so changing the current level upper than all the
     * currently Acquired levels so don't expect exceptions on
     * the following Release operations applied in the correct
     * inverse order to all the Acquired mutexes.
     *
     * (for the current 20060828 ACPICA this doesn't help).
     */
    Method (M07F, 0, Serialized)
    {
        Name (RPT0, 0x01)
        Name (ORD0, 0x01)
        Name (LPN0, 0x00) /* level */
        Name (LPC0, 0x00)
        LPN0 = (MAX0 - 0x02)
        LPC0 = 0x01
        While (LPN0)
        {
            Local0 = (LPC0 - 0x01)
            Local1 = (LPC0 + 0x01)
            M088 (Local0, 0x01, 0x00, MIN0, 0x00, RPT0, 0x00)    /* Step  0, Acquire */
            M088 (LPC0, 0x01, 0x00, MIN0, 0x00, RPT0, 0x00)    /* Step  1, Acquire */
            /* Jump over the level on Releasing */

            M089 (Local0, 0x01, 0x00, MIN0, 0x40, RPT0, ORD0) /* Step  2, Release, AE_AML_MUTEX_ORDER */
            /*
             * Additional attempt is made to restore the normal calculation -
             * Acquire the mutex M0 of level greater than all the levels
             * touched at that moment so changing the current level by the
             * succeeded operation. Then do Release operations for all
             * the Acquired mutexes in the correct inverse order starting
             * with the M0 mutex expecting no exceptions on them.
             *
             * (for the current 20060828 ACPICA this doesn't help).
             */
            M088 (LPC0, 0x01, 0x00, 0x01, 0x00, RPT0, 0x00)    /* Step  3, Acquire */
            M088 (Local1, 0x01, 0x00, 0x01, 0x00, RPT0, 0x00)    /* Step  4, Acquire */
            M088 (LPC0, 0x01, 0x00, 0x01, 0x40, RPT0, 0x00)    /* Step  5, Acquire, AE_AML_MUTEX_ORDER */
            M089 (Local1, 0x01, 0x00, 0x01, 0x00, RPT0, ORD0) /* Step  4, Release */
            M089 (LPC0, 0x01, 0x00, 0x01, 0x00, RPT0, ORD0) /* Step  3, Release */
            M089 (LPC0, 0x01, 0x00, MIN0, 0x00, RPT0, ORD0) /* Step  1, Release */
            M089 (Local0, 0x01, 0x00, MIN0, 0x00, RPT0, ORD0) /* Step  0, Release */
            LPN0--
            LPC0++
        }

        /* Check that all mutexes are Released */

        M08A ()
        M088 (0x00, MAX0, 0x00, MIN0, 0x00, RPT0, 0x00)    /* Step  6, Acquire */
        M089 (0x00, MAX0, 0x00, MIN0, 0x00, RPT0, ORD0) /* Step  6, Release */
        /* Check that all mutexes are Released */

        M08A ()
    }

    /* ############################################### Run-method: */

    Method (M300, 0, NotSerialized)
    {
        If (FL03)
        {
            /* Check that all mutexes are Released (doesn't check T804..) */

            M08A ()
        }

        SRMT ("m300")
        If (ERR7)
        {
            ERR ("ERRORS were detected during the loading stage", Z150, 0x083C, 0x00, 0x00, 0x00, ERR7)
        }

        /* ATTENTION: this test must be run the first */

        SRMT ("m0b9")
        M0B9 ()
        SRMT ("m0bb")
        M0BB ()
        SRMT ("m301")
        M301 ()
        SRMT ("m369-0")
        M369 (0x00)
        SRMT ("m369-1")
        If (Y297)
        {
            M369 (0x01)
        }
        Else
        {
            BLCK ()
        }

        SRMT ("m369-0")
        M369 (0x00)
        SRMT ("m36a")
        M36A ()
        SRMT ("m36b")
        M36B ()
        SRMT ("m36c")
        M36C ()
        SRMT ("m389")
        M389 ()
        SRMT ("m07b")
        M07B ()
        SRMT ("m38a")
        If (Y238)
        {
            M38A ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("m38d")
        If (Y242)
        {
            M38D ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("m07d-direct")
        If (Y242)
        {
            M07D (0x00)
        }
        Else
        {
            BLCK ()
        }

        SRMT ("m07d-inverse")
        M07D (0x01)
        SRMT ("m07a-no-GL")
        M07A (0x00)
        SRMT ("m07a-GL")
        M07A (0x01)
        SRMT ("m07e")
        M07E ()
        SRMT ("m08b-no-GL-0")
        M08B (0x00, 0x00)
        SRMT ("m08b-no-GL-1")
        M08B (0x00, 0x01)
        SRMT ("m08b-GL-0")
        M08B (0x01, 0x00)
        SRMT ("m08b-GL-1")
        M08B (0x01, 0x01)
        SRMT ("m08d-no-GL")
        If (Y238)
        {
            M08D (0x00)
        }
        Else
        {
            BLCK ()
        }

        SRMT ("m08d-GL")
        If (Y238)
        {
            M08D (0x01)
        }
        Else
        {
            BLCK ()
        }

        SRMT ("m07f")
        If (Y243)
        {
            M07F ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("m07c")
        M07C ()
        SRMT ("m0ba")
        M0BA ()
        /*
         * To see if the mutex-es framework can continue working after AE_LIMIT.
         * Now, after AE_LIMIT, it looks can't actually restore -- many messages
         * during the all further execution of tests, and even the tests
         * "TEST: WAI0, Wait for Events" somewhere hangs forever:
         *
         * **** AcpiExec: Exception AE_LIMIT during execution of method [M369] Opcode [Mutex] @E2
         * ACPI Exception (utmutex-0376): AE_BAD_PARAMETER, Thread 1475 could not acquire Mutex [0] [20074403]
         * ACPI Error (exutils-0180): Could not acquire AML Interpreter mutex [20074403]
         * ACPI Error (utmutex-0421): Mutex [0] is not acquired, cannot release [20074403]
         * ACPI Error (exutils-0250): Could not release AML Interpreter mutex [20074403]
         * **** AcpiExec: Exception override, new status AE_OK
         */
        SRMT ("m369-0")
        M369 (0x00)
        SRMT ("m369-1")
        If (Y297)
        {
            M369 (0x01)
        }
        Else
        {
            BLCK ()
        }

        SRMT ("m369-0")
        M369 (0x00)
        If (FL03)
        {
            /* Check that all mutexes are Released */

            M08A ()
        }

        CH03 ("m300", Z150, 0x00, 0x08CA, 0x00)
    }

