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
     * Check implicit conversion being applied to ArgX Object
     */
    Name (Z121, 0x79)
    Method (M617, 0, Serialized)
    {
        Name (TS, "m617")
        /* Integer to String implicit conversion Cases. */
        /* Integer to String conversion of the Integer second operand of */
        /* Logical operators when the first operand is evaluated as String. */
        /* LEqual LGreater LGreaterEqual LLess LLessEqual LNotEqual */
        Method (M640, 2, NotSerialized)
        {
            /* LEqual */

            Local0 = ("FE7CB391D650A284" == Arg1)
            M600 (Arg0, 0x00, Local0, Ones)
            Local0 = ("fE7CB391D650A284" == Arg1)
            M600 (Arg0, 0x01, Local0, Zero)
            Local0 = (AUS4 == Arg1)
            M600 (Arg0, 0x02, Local0, Ones)
            Local0 = (AUS5 == Arg1)
            M600 (Arg0, 0x03, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUS4)) == Arg1)
                M600 (Arg0, 0x04, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUS5)) == Arg1)
                M600 (Arg0, 0x05, Local0, Zero)
            }

            Local0 = (DerefOf (PAUS [0x04]) == Arg1)
            M600 (Arg0, 0x06, Local0, Ones)
            Local0 = (DerefOf (PAUS [0x05]) == Arg1)
            M600 (Arg0, 0x07, Local0, Zero)
            /* Method returns String */

            Local0 = (M601 (0x02, 0x04) == Arg1)
            M600 (Arg0, 0x08, Local0, Ones)
            Local0 = (M601 (0x02, 0x05) == Arg1)
            M600 (Arg0, 0x09, Local0, Zero)
            /* Method returns Reference to String */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x02, 0x04, 0x01)) == Arg1)
                M600 (Arg0, 0x0A, Local0, Ones)
                Local0 = (DerefOf (M602 (0x02, 0x05, 0x01)) == Arg1)
                M600 (Arg0, 0x0B, Local0, Zero)
            }

            /* LGreater */

            Local0 = ("FE7CB391D650A284" > Arg1)
            M600 (Arg0, 0x0C, Local0, Zero)
            Local0 = ("fE7CB391D650A284" > Arg1)
            M600 (Arg0, 0x0D, Local0, Ones)
            Local0 = ("FE7CB391D650A28 " > Arg1)
            M600 (Arg0, 0x0E, Local0, Zero)
            Local0 = ("FE7CB391D650A284q" > Arg1)
            M600 (Arg0, 0x0F, Local0, Ones)
            Local0 = (AUS4 > Arg1)
            M600 (Arg0, 0x10, Local0, Zero)
            Local0 = (AUS5 > Arg1)
            M600 (Arg0, 0x11, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUS4)) > Arg1)
                M600 (Arg0, 0x12, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUS5)) > Arg1)
                M600 (Arg0, 0x13, Local0, Ones)
            }

            Local0 = (DerefOf (PAUS [0x04]) > Arg1)
            M600 (Arg0, 0x14, Local0, Zero)
            Local0 = (DerefOf (PAUS [0x05]) > Arg1)
            M600 (Arg0, 0x15, Local0, Ones)
            /* Method returns String */

            Local0 = (M601 (0x02, 0x04) > Arg1)
            M600 (Arg0, 0x16, Local0, Zero)
            Local0 = (M601 (0x02, 0x05) > Arg1)
            M600 (Arg0, 0x17, Local0, Ones)
            /* Method returns Reference to String */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x02, 0x04, 0x01)) > Arg1)
                M600 (Arg0, 0x18, Local0, Zero)
                Local0 = (DerefOf (M602 (0x02, 0x05, 0x01)) > Arg1)
                M600 (Arg0, 0x19, Local0, Ones)
            }

            /* LGreaterEqual */

            Local0 = ("FE7CB391D650A284" >= Arg1)
            M600 (Arg0, 0x1A, Local0, Ones)
            Local0 = ("fE7CB391D650A284" >= Arg1)
            M600 (Arg0, 0x1B, Local0, Ones)
            Local0 = ("FE7CB391D650A28 " >= Arg1)
            M600 (Arg0, 0x1C, Local0, Zero)
            Local0 = ("FE7CB391D650A284q" >= Arg1)
            M600 (Arg0, 0x1D, Local0, Ones)
            Local0 = (AUS4 >= Arg1)
            M600 (Arg0, 0x1E, Local0, Ones)
            Local0 = (AUS5 >= Arg1)
            M600 (Arg0, 0x1F, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUS4)) >= Arg1)
                M600 (Arg0, 0x20, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUS5)) >= Arg1)
                M600 (Arg0, 0x21, Local0, Ones)
            }

            Local0 = (DerefOf (PAUS [0x04]) >= Arg1)
            M600 (Arg0, 0x22, Local0, Ones)
            Local0 = (DerefOf (PAUS [0x05]) >= Arg1)
            M600 (Arg0, 0x23, Local0, Ones)
            /* Method returns String */

            Local0 = (M601 (0x02, 0x04) >= Arg1)
            M600 (Arg0, 0x24, Local0, Ones)
            Local0 = (M601 (0x02, 0x05) >= Arg1)
            M600 (Arg0, 0x25, Local0, Ones)
            /* Method returns Reference to String */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x02, 0x04, 0x01)) >= Arg1)
                M600 (Arg0, 0x26, Local0, Ones)
                Local0 = (DerefOf (M602 (0x02, 0x05, 0x01)) >= Arg1)
                M600 (Arg0, 0x27, Local0, Ones)
            }

            /* LLess */

            Local0 = ("FE7CB391D650A284" < Arg1)
            M600 (Arg0, 0x28, Local0, Zero)
            Local0 = ("fE7CB391D650A284" < Arg1)
            M600 (Arg0, 0x29, Local0, Zero)
            Local0 = ("FE7CB391D650A28 " < Arg1)
            M600 (Arg0, 0x2A, Local0, Ones)
            Local0 = ("FE7CB391D650A284q" < Arg1)
            M600 (Arg0, 0x2B, Local0, Zero)
            Local0 = (AUS4 < Arg1)
            M600 (Arg0, 0x2C, Local0, Zero)
            Local0 = (AUS5 < Arg1)
            M600 (Arg0, 0x2D, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUS4)) < Arg1)
                M600 (Arg0, 0x2E, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUS5)) < Arg1)
                M600 (Arg0, 0x2F, Local0, Zero)
            }

            Local0 = (DerefOf (PAUS [0x04]) < Arg1)
            M600 (Arg0, 0x30, Local0, Zero)
            Local0 = (DerefOf (PAUS [0x05]) < Arg1)
            M600 (Arg0, 0x31, Local0, Zero)
            /* Method returns String */

            Local0 = (M601 (0x02, 0x04) < Arg1)
            M600 (Arg0, 0x32, Local0, Zero)
            Local0 = (M601 (0x02, 0x05) < Arg1)
            M600 (Arg0, 0x33, Local0, Zero)
            /* Method returns Reference to String */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x02, 0x04, 0x01)) < Arg1)
                M600 (Arg0, 0x34, Local0, Zero)
                Local0 = (DerefOf (M602 (0x02, 0x05, 0x01)) < Arg1)
                M600 (Arg0, 0x35, Local0, Zero)
            }

            /* LLessEqual */

            Local0 = ("FE7CB391D650A284" <= Arg1)
            M600 (Arg0, 0x36, Local0, Ones)
            Local0 = ("fE7CB391D650A284" <= Arg1)
            M600 (Arg0, 0x37, Local0, Zero)
            Local0 = ("FE7CB391D650A28 " <= Arg1)
            M600 (Arg0, 0x38, Local0, Ones)
            Local0 = ("FE7CB391D650A284q" <= Arg1)
            M600 (Arg0, 0x39, Local0, Zero)
            Local0 = (AUS4 <= Arg1)
            M600 (Arg0, 0x3A, Local0, Ones)
            Local0 = (AUS5 <= Arg1)
            M600 (Arg0, 0x3B, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUS4)) <= Arg1)
                M600 (Arg0, 0x3C, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUS5)) <= Arg1)
                M600 (Arg0, 0x3D, Local0, Zero)
            }

            Local0 = (DerefOf (PAUS [0x04]) <= Arg1)
            M600 (Arg0, 0x3E, Local0, Ones)
            Local0 = (DerefOf (PAUS [0x05]) <= Arg1)
            M600 (Arg0, 0x3F, Local0, Zero)
            /* Method returns String */

            Local0 = (M601 (0x02, 0x04) <= Arg1)
            M600 (Arg0, 0x40, Local0, Ones)
            Local0 = (M601 (0x02, 0x05) <= Arg1)
            M600 (Arg0, 0x41, Local0, Zero)
            /* Method returns Reference to String */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x02, 0x04, 0x01)) <= Arg1)
                M600 (Arg0, 0x42, Local0, Ones)
                Local0 = (DerefOf (M602 (0x02, 0x05, 0x01)) <= Arg1)
                M600 (Arg0, 0x43, Local0, Zero)
            }

            /* LNotEqual */

            Local0 = ("FE7CB391D650A284" != Arg1)
            M600 (Arg0, 0x44, Local0, Zero)
            Local0 = ("fE7CB391D650A284" != Arg1)
            M600 (Arg0, 0x45, Local0, Ones)
            Local0 = ("FE7CB391D650A28 " != Arg1)
            M600 (Arg0, 0x46, Local0, Ones)
            Local0 = ("FE7CB391D650A284q" != Arg1)
            M600 (Arg0, 0x47, Local0, Ones)
            Local0 = (AUS4 != Arg1)
            M600 (Arg0, 0x48, Local0, Zero)
            Local0 = (AUS5 != Arg1)
            M600 (Arg0, 0x49, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUS4)) != Arg1)
                M600 (Arg0, 0x4A, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUS5)) != Arg1)
                M600 (Arg0, 0x4B, Local0, Ones)
            }

            Local0 = (DerefOf (PAUS [0x04]) != Arg1)
            M600 (Arg0, 0x4C, Local0, Zero)
            Local0 = (DerefOf (PAUS [0x05]) != Arg1)
            M600 (Arg0, 0x4D, Local0, Ones)
            /* Method returns String */

            Local0 = (M601 (0x02, 0x04) != Arg1)
            M600 (Arg0, 0x4E, Local0, Zero)
            Local0 = (M601 (0x02, 0x05) != Arg1)
            M600 (Arg0, 0x4F, Local0, Ones)
            /* Method returns Reference to String */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x02, 0x04, 0x01)) != Arg1)
                M600 (Arg0, 0x50, Local0, Zero)
                Local0 = (DerefOf (M602 (0x02, 0x05, 0x01)) != Arg1)
                M600 (Arg0, 0x51, Local0, Ones)
            }
        }

        Method (M320, 2, NotSerialized)
        {
            /* LEqual */

            Local0 = ("C179B3FE" == Arg1)
            M600 (Arg0, 0x00, Local0, Ones)
            Local0 = ("c179B3FE" == Arg1)
            M600 (Arg0, 0x01, Local0, Zero)
            Local0 = (AUS3 == Arg1)
            M600 (Arg0, 0x02, Local0, Ones)
            Local0 = (AUS2 == Arg1)
            M600 (Arg0, 0x03, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUS3)) == Arg1)
                M600 (Arg0, 0x04, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUS2)) == Arg1)
                M600 (Arg0, 0x05, Local0, Zero)
            }

            Local0 = (DerefOf (PAUS [0x03]) == Arg1)
            M600 (Arg0, 0x06, Local0, Ones)
            Local0 = (DerefOf (PAUS [0x02]) == Arg1)
            M600 (Arg0, 0x07, Local0, Zero)
            /* Method returns String */

            Local0 = (M601 (0x02, 0x03) == Arg1)
            M600 (Arg0, 0x08, Local0, Ones)
            Local0 = (M601 (0x02, 0x02) == Arg1)
            M600 (Arg0, 0x09, Local0, Zero)
            /* Method returns Reference to String */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x02, 0x03, 0x01)) == Arg1)
                M600 (Arg0, 0x0A, Local0, Ones)
                Local0 = (DerefOf (M602 (0x02, 0x02, 0x01)) == Arg1)
                M600 (Arg0, 0x0B, Local0, Zero)
            }

            /* LGreater */

            Local0 = ("C179B3FE" > Arg1)
            M600 (Arg0, 0x0C, Local0, Zero)
            Local0 = ("c179B3FE" > Arg1)
            M600 (Arg0, 0x0D, Local0, Ones)
            Local0 = ("C179B3F " > Arg1)
            M600 (Arg0, 0x0E, Local0, Zero)
            Local0 = ("C179B3FEq" > Arg1)
            M600 (Arg0, 0x0F, Local0, Ones)
            Local0 = (AUS3 > Arg1)
            M600 (Arg0, 0x10, Local0, Zero)
            Local0 = (AUS2 > Arg1)
            M600 (Arg0, 0x11, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUS3)) > Arg1)
                M600 (Arg0, 0x12, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUS2)) > Arg1)
                M600 (Arg0, 0x13, Local0, Ones)
            }

            Local0 = (DerefOf (PAUS [0x03]) > Arg1)
            M600 (Arg0, 0x14, Local0, Zero)
            Local0 = (DerefOf (PAUS [0x02]) > Arg1)
            M600 (Arg0, 0x15, Local0, Ones)
            /* Method returns String */

            Local0 = (M601 (0x02, 0x03) > Arg1)
            M600 (Arg0, 0x16, Local0, Zero)
            Local0 = (M601 (0x02, 0x02) > Arg1)
            M600 (Arg0, 0x17, Local0, Ones)
            /* Method returns Reference to String */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x02, 0x03, 0x01)) > Arg1)
                M600 (Arg0, 0x18, Local0, Zero)
                Local0 = (DerefOf (M602 (0x02, 0x02, 0x01)) > Arg1)
                M600 (Arg0, 0x19, Local0, Ones)
            }

            /* LGreaterEqual */

            Local0 = ("C179B3FE" >= Arg1)
            M600 (Arg0, 0x1A, Local0, Ones)
            Local0 = ("c179B3FE" >= Arg1)
            M600 (Arg0, 0x1B, Local0, Ones)
            Local0 = ("C179B3F " >= Arg1)
            M600 (Arg0, 0x1C, Local0, Zero)
            Local0 = ("C179B3FEq" >= Arg1)
            M600 (Arg0, 0x1D, Local0, Ones)
            Local0 = (AUS3 >= Arg1)
            M600 (Arg0, 0x1E, Local0, Ones)
            Local0 = (AUS2 >= Arg1)
            M600 (Arg0, 0x1F, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUS3)) >= Arg1)
                M600 (Arg0, 0x20, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUS2)) >= Arg1)
                M600 (Arg0, 0x21, Local0, Ones)
            }

            Local0 = (DerefOf (PAUS [0x03]) >= Arg1)
            M600 (Arg0, 0x22, Local0, Ones)
            Local0 = (DerefOf (PAUS [0x02]) >= Arg1)
            M600 (Arg0, 0x23, Local0, Ones)
            /* Method returns String */

            Local0 = (M601 (0x02, 0x03) >= Arg1)
            M600 (Arg0, 0x24, Local0, Ones)
            Local0 = (M601 (0x02, 0x02) >= Arg1)
            M600 (Arg0, 0x25, Local0, Ones)
            /* Method returns Reference to String */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x02, 0x03, 0x01)) >= Arg1)
                M600 (Arg0, 0x26, Local0, Ones)
                Local0 = (DerefOf (M602 (0x02, 0x02, 0x01)) >= Arg1)
                M600 (Arg0, 0x27, Local0, Ones)
            }

            /* LLess */

            Local0 = ("C179B3FE" < Arg1)
            M600 (Arg0, 0x28, Local0, Zero)
            Local0 = ("c179B3FE" < Arg1)
            M600 (Arg0, 0x29, Local0, Zero)
            Local0 = ("C179B3F " < Arg1)
            M600 (Arg0, 0x2A, Local0, Ones)
            Local0 = ("C179B3FEq" < Arg1)
            M600 (Arg0, 0x2B, Local0, Zero)
            Local0 = (AUS3 < Arg1)
            M600 (Arg0, 0x2C, Local0, Zero)
            Local0 = (AUS2 < Arg1)
            M600 (Arg0, 0x2D, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUS3)) < Arg1)
                M600 (Arg0, 0x2E, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUS2)) < Arg1)
                M600 (Arg0, 0x2F, Local0, Zero)
            }

            Local0 = (DerefOf (PAUS [0x03]) < Arg1)
            M600 (Arg0, 0x30, Local0, Zero)
            Local0 = (DerefOf (PAUS [0x02]) < Arg1)
            M600 (Arg0, 0x31, Local0, Zero)
            /* Method returns String */

            Local0 = (M601 (0x02, 0x03) < Arg1)
            M600 (Arg0, 0x32, Local0, Zero)
            Local0 = (M601 (0x02, 0x02) < Arg1)
            M600 (Arg0, 0x33, Local0, Zero)
            /* Method returns Reference to String */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x02, 0x03, 0x01)) < Arg1)
                M600 (Arg0, 0x34, Local0, Zero)
                Local0 = (DerefOf (M602 (0x02, 0x02, 0x01)) < Arg1)
                M600 (Arg0, 0x35, Local0, Zero)
            }

            /* LLessEqual */

            Local0 = ("C179B3FE" <= Arg1)
            M600 (Arg0, 0x36, Local0, Ones)
            Local0 = ("c179B3FE" <= Arg1)
            M600 (Arg0, 0x37, Local0, Zero)
            Local0 = ("C179B3F " <= Arg1)
            M600 (Arg0, 0x38, Local0, Ones)
            Local0 = ("C179B3FEq" <= Arg1)
            M600 (Arg0, 0x39, Local0, Zero)
            Local0 = (AUS3 <= Arg1)
            M600 (Arg0, 0x3A, Local0, Ones)
            Local0 = (AUS2 <= Arg1)
            M600 (Arg0, 0x3B, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUS3)) <= Arg1)
                M600 (Arg0, 0x3C, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUS2)) <= Arg1)
                M600 (Arg0, 0x3D, Local0, Zero)
            }

            Local0 = (DerefOf (PAUS [0x03]) <= Arg1)
            M600 (Arg0, 0x3E, Local0, Ones)
            Local0 = (DerefOf (PAUS [0x02]) <= Arg1)
            M600 (Arg0, 0x3F, Local0, Zero)
            /* Method returns String */

            Local0 = (M601 (0x02, 0x03) <= Arg1)
            M600 (Arg0, 0x40, Local0, Ones)
            Local0 = (M601 (0x02, 0x02) <= Arg1)
            M600 (Arg0, 0x41, Local0, Zero)
            /* Method returns Reference to String */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x02, 0x03, 0x01)) <= Arg1)
                M600 (Arg0, 0x42, Local0, Ones)
                Local0 = (DerefOf (M602 (0x02, 0x02, 0x01)) <= Arg1)
                M600 (Arg0, 0x43, Local0, Zero)
            }

            /* LNotEqual */

            Local0 = ("C179B3FE" != Arg1)
            M600 (Arg0, 0x44, Local0, Zero)
            Local0 = ("c179B3FE" != Arg1)
            M600 (Arg0, 0x45, Local0, Ones)
            Local0 = ("C179B3F " != Arg1)
            M600 (Arg0, 0x46, Local0, Ones)
            Local0 = ("C179B3FEq" != Arg1)
            M600 (Arg0, 0x47, Local0, Ones)
            Local0 = (AUS3 != Arg1)
            M600 (Arg0, 0x48, Local0, Zero)
            Local0 = (AUS2 != Arg1)
            M600 (Arg0, 0x49, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUS3)) != Arg1)
                M600 (Arg0, 0x4A, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUS2)) != Arg1)
                M600 (Arg0, 0x4B, Local0, Ones)
            }

            Local0 = (DerefOf (PAUS [0x03]) != Arg1)
            M600 (Arg0, 0x4C, Local0, Zero)
            Local0 = (DerefOf (PAUS [0x02]) != Arg1)
            M600 (Arg0, 0x4D, Local0, Ones)
            /* Method returns String */

            Local0 = (M601 (0x02, 0x03) != Arg1)
            M600 (Arg0, 0x4E, Local0, Zero)
            Local0 = (M601 (0x02, 0x02) != Arg1)
            M600 (Arg0, 0x4F, Local0, Ones)
            /* Method returns Reference to String */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x02, 0x03, 0x01)) != Arg1)
                M600 (Arg0, 0x50, Local0, Zero)
                Local0 = (DerefOf (M602 (0x02, 0x02, 0x01)) != Arg1)
                M600 (Arg0, 0x51, Local0, Ones)
            }
        }

        /* Integer to String conversion of the Integer second operand of */
        /* Concatenate operator when the first operand is evaluated as String */
        Method (M641, 2, NotSerialized)
        {
            Local0 = Concatenate ("", Arg1)
            M600 (Arg0, 0x00, Local0, BS10)
            Local0 = Concatenate ("1234q", Arg1)
            M600 (Arg0, 0x01, Local0, BS11)
            Local0 = Concatenate (AUS0, Arg1)
            M600 (Arg0, 0x02, Local0, BS10)
            Local0 = Concatenate (AUS1, Arg1)
            M600 (Arg0, 0x03, Local0, BS11)
            If (Y078)
            {
                Local0 = Concatenate (DerefOf (RefOf (AUS0)), Arg1)
                M600 (Arg0, 0x04, Local0, BS10)
                Local0 = Concatenate (DerefOf (RefOf (AUS1)), Arg1)
                M600 (Arg0, 0x05, Local0, BS11)
            }

            Local0 = Concatenate (DerefOf (PAUS [0x00]), Arg1)
            M600 (Arg0, 0x06, Local0, BS10)
            Local0 = Concatenate (DerefOf (PAUS [0x01]), Arg1)
            M600 (Arg0, 0x07, Local0, BS11)
            /* Method returns String */

            Local0 = Concatenate (M601 (0x02, 0x00), Arg1)
            M600 (Arg0, 0x08, Local0, BS10)
            Local0 = Concatenate (M601 (0x02, 0x01), Arg1)
            M600 (Arg0, 0x09, Local0, BS11)
            /* Method returns Reference to String */

            If (Y500)
            {
                Local0 = Concatenate (DerefOf (M602 (0x02, 0x00, 0x01)), Arg1)
                M600 (Arg0, 0x0A, Local0, BS10)
                Local0 = Concatenate (DerefOf (M602 (0x02, 0x01, 0x01)), Arg1)
                M600 (Arg0, 0x0B, Local0, BS11)
            }

            Concatenate ("", Arg1, Local0)
            M600 (Arg0, 0x0C, Local0, BS10)
            Concatenate ("1234q", Arg1, Local0)
            M600 (Arg0, 0x0D, Local0, BS11)
            Concatenate (AUS0, Arg1, Local0)
            M600 (Arg0, 0x0E, Local0, BS10)
            Concatenate (AUS1, Arg1, Local0)
            M600 (Arg0, 0x0F, Local0, BS11)
            If (Y078)
            {
                Concatenate (DerefOf (RefOf (AUS0)), Arg1, Local0)
                M600 (Arg0, 0x10, Local0, BS10)
                Concatenate (DerefOf (RefOf (AUS1)), Arg1, Local0)
                M600 (Arg0, 0x11, Local0, BS11)
            }

            Concatenate (DerefOf (PAUS [0x00]), Arg1, Local0)
            M600 (Arg0, 0x12, Local0, BS10)
            Concatenate (DerefOf (PAUS [0x01]), Arg1, Local0)
            M600 (Arg0, 0x13, Local0, BS11)
            /* Method returns String */

            Concatenate (M601 (0x02, 0x00), Arg1, Local0)
            M600 (Arg0, 0x14, Local0, BS10)
            Concatenate (M601 (0x02, 0x01), Arg1, Local0)
            M600 (Arg0, 0x15, Local0, BS11)
            /* Method returns Reference to String */

            If (Y500)
            {
                Concatenate (DerefOf (M602 (0x02, 0x00, 0x01)), Arg1, Local0)
                M600 (Arg0, 0x16, Local0, BS10)
                Concatenate (DerefOf (M602 (0x02, 0x01, 0x01)), Arg1, Local0)
                M600 (Arg0, 0x17, Local0, BS11)
            }
        }

        Method (M321, 3, NotSerialized)
        {
            Local0 = Concatenate ("", Arg2)
            M600 (Arg0, 0x00, Local0, BS12)
            Local0 = Concatenate ("1234q", Arg2)
            M600 (Arg0, 0x01, Local0, BS13)
            Local0 = Concatenate (AUS0, Arg2)
            M600 (Arg0, 0x02, Local0, BS12)
            Local0 = Concatenate (AUS1, Arg2)
            M600 (Arg0, 0x03, Local0, BS13)
            If (Y078)
            {
                Local0 = Concatenate (DerefOf (RefOf (AUS0)), Arg2)
                M600 (Arg0, 0x04, Local0, BS12)
                Local0 = Concatenate (DerefOf (RefOf (AUS1)), Arg2)
                M600 (Arg0, 0x05, Local0, BS13)
            }

            Local0 = Concatenate (DerefOf (PAUS [0x00]), Arg2)
            M600 (Arg0, 0x06, Local0, BS12)
            Local0 = Concatenate (DerefOf (PAUS [0x01]), Arg2)
            M600 (Arg0, 0x07, Local0, BS13)
            /* Method returns String */

            Local0 = Concatenate (M601 (0x02, 0x00), Arg2)
            M600 (Arg0, 0x08, Local0, BS12)
            Local0 = Concatenate (M601 (0x02, 0x01), Arg2)
            M600 (Arg0, 0x09, Local0, BS13)
            /* Method returns Reference to String */

            If (Y500)
            {
                Local0 = Concatenate (DerefOf (M602 (0x02, 0x00, 0x01)), Arg2)
                M600 (Arg0, 0x0A, Local0, BS12)
                Local0 = Concatenate (DerefOf (M602 (0x02, 0x01, 0x01)), Arg2)
                M600 (Arg0, 0x0B, Local0, BS13)
            }

            Local0 = Concatenate ("", Arg1)
            M600 (Arg0, 0x0C, Local0, BS14)
            Local0 = Concatenate ("1234q", Arg1)
            M600 (Arg0, 0x0D, Local0, BS15)
            Concatenate ("", Arg2, Local0)
            M600 (Arg0, 0x0E, Local0, BS12)
            Concatenate ("1234q", Arg2, Local0)
            M600 (Arg0, 0x0F, Local0, BS13)
            Concatenate (AUS0, Arg2, Local0)
            M600 (Arg0, 0x10, Local0, BS12)
            Concatenate (AUS1, Arg2, Local0)
            M600 (Arg0, 0x11, Local0, BS13)
            If (Y078)
            {
                Concatenate (DerefOf (RefOf (AUS0)), Arg2, Local0)
                M600 (Arg0, 0x12, Local0, BS12)
                Concatenate (DerefOf (RefOf (AUS1)), Arg2, Local0)
                M600 (Arg0, 0x13, Local0, BS13)
            }

            Concatenate (DerefOf (PAUS [0x00]), Arg2, Local0)
            M600 (Arg0, 0x14, Local0, BS12)
            Concatenate (DerefOf (PAUS [0x01]), Arg2, Local0)
            M600 (Arg0, 0x15, Local0, BS13)
            /* Method returns String */

            Concatenate (M601 (0x02, 0x00), Arg2, Local0)
            M600 (Arg0, 0x16, Local0, BS12)
            Concatenate (M601 (0x02, 0x01), Arg2, Local0)
            M600 (Arg0, 0x17, Local0, BS13)
            /* Method returns Reference to String */

            If (Y500)
            {
                Concatenate (DerefOf (M602 (0x02, 0x00, 0x01)), Arg2, Local0)
                M600 (Arg0, 0x18, Local0, BS12)
                Concatenate (DerefOf (M602 (0x02, 0x01, 0x01)), Arg2, Local0)
                M600 (Arg0, 0x19, Local0, BS13)
            }

            Concatenate ("", Arg1, Local0)
            M600 (Arg0, 0x1A, Local0, BS14)
            Concatenate ("1234q", Arg1, Local0)
            M600 (Arg0, 0x1B, Local0, BS15)
        }

        /*	Method(m642, 1) */
        /*	Method(m322, 1) */
        /*	Method(m643, 1) */
        /*	Method(m323, 1) */
        /* Integer to Buffer implicit conversion Cases. */
        /* Integer to Buffer conversion of the Integer second operand of */
        /* Logical operators when the first operand is evaluated as Buffer */
        /* (LEqual, LGreater, LGreaterEqual, LLess, LLessEqual, LNotEqual) */
        Method (M644, 2, NotSerialized)
        {
            /* LEqual */

            Local0 = (Buffer (0x08)
                    {
                         0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE   // ..P...|.
                    } == Arg1)
            M600 (Arg0, 0x00, Local0, Ones)
            Local0 = (Buffer (0x08)
                    {
                         0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFF   // ..P...|.
                    } == Arg1)
            M600 (Arg0, 0x01, Local0, Zero)
            Local0 = (AUB4 == Arg1)
            M600 (Arg0, 0x02, Local0, Ones)
            Local0 = (AUB3 == Arg1)
            M600 (Arg0, 0x03, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUB4)) == Arg1)
                M600 (Arg0, 0x04, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUB3)) == Arg1)
                M600 (Arg0, 0x05, Local0, Zero)
            }

            Local0 = (DerefOf (PAUB [0x04]) == Arg1)
            M600 (Arg0, 0x06, Local0, Ones)
            Local0 = (DerefOf (PAUB [0x03]) == Arg1)
            M600 (Arg0, 0x07, Local0, Zero)
            /* Method returns Buffer */

            Local0 = (M601 (0x03, 0x04) == Arg1)
            M600 (Arg0, 0x08, Local0, Ones)
            Local0 = (M601 (0x03, 0x03) == Arg1)
            M600 (Arg0, 0x09, Local0, Zero)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x03, 0x04, 0x01)) == Arg1)
                M600 (Arg0, 0x0A, Local0, Ones)
                Local0 = (DerefOf (M602 (0x03, 0x03, 0x01)) == Arg1)
                M600 (Arg0, 0x0B, Local0, Zero)
            }

            /* LGreater */

            Local0 = (Buffer (0x08)
                    {
                         0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE   // ..P...|.
                    } > Arg1)
            M600 (Arg0, 0x0C, Local0, Zero)
            Local0 = (Buffer (0x08)
                    {
                         0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFF   // ..P...|.
                    } > Arg1)
            M600 (Arg0, 0x0D, Local0, Ones)
            Local0 = (Buffer (0x08)
                    {
                         0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFD   // ..P...|.
                    } > Arg1)
            M600 (Arg0, 0x0E, Local0, Zero)
            Local0 = (Buffer (0x09)
                    {
                        /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                        /* 0008 */  0x01                                             // .
                    } > Arg1)
            M600 (Arg0, 0x0F, Local0, Ones)
            Local0 = (AUB4 > Arg1)
            M600 (Arg0, 0x10, Local0, Zero)
            Local0 = (AUB5 > Arg1)
            M600 (Arg0, 0x11, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUB4)) > Arg1)
                M600 (Arg0, 0x12, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUB5)) > Arg1)
                M600 (Arg0, 0x13, Local0, Ones)
            }

            Local0 = (DerefOf (PAUB [0x04]) > Arg1)
            M600 (Arg0, 0x14, Local0, Zero)
            Local0 = (DerefOf (PAUB [0x05]) > Arg1)
            M600 (Arg0, 0x15, Local0, Ones)
            /* Method returns Buffer */

            Local0 = (M601 (0x03, 0x04) > Arg1)
            M600 (Arg0, 0x16, Local0, Zero)
            Local0 = (M601 (0x03, 0x05) > Arg1)
            M600 (Arg0, 0x17, Local0, Ones)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x03, 0x04, 0x01)) > Arg1)
                M600 (Arg0, 0x18, Local0, Zero)
                Local0 = (DerefOf (M602 (0x03, 0x05, 0x01)) > Arg1)
                M600 (Arg0, 0x19, Local0, Ones)
            }

            /* LGreaterEqual */

            Local0 = (Buffer (0x08)
                        {
                             0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE   // ..P...|.
                        } >= Arg1)
            M600 (Arg0, 0x1A, Local0, Ones)
            Local0 = (Buffer (0x08)
                        {
                             0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFF   // ..P...|.
                        } >= Arg1)
            M600 (Arg0, 0x1B, Local0, Ones)
            Local0 = (Buffer (0x08)
                        {
                             0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFD   // ..P...|.
                        } >= Arg1)
            M600 (Arg0, 0x1C, Local0, Zero)
            Local0 = (Buffer (0x09)
                        {
                            /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                            /* 0008 */  0x01                                             // .
                        } >= Arg1)
            M600 (Arg0, 0x1D, Local0, Ones)
            Local0 = (AUB4 >= Arg1)
            M600 (Arg0, 0x1E, Local0, Ones)
            Local0 = (AUB5 >= Arg1)
            M600 (Arg0, 0x1F, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUB4)) >= Arg1)
                M600 (Arg0, 0x20, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUB5)) >= Arg1)
                M600 (Arg0, 0x21, Local0, Ones)
            }

            Local0 = (DerefOf (PAUB [0x04]) >= Arg1)
            M600 (Arg0, 0x22, Local0, Ones)
            Local0 = (DerefOf (PAUB [0x05]) >= Arg1)
            M600 (Arg0, 0x23, Local0, Ones)
            /* Method returns Buffer */

            Local0 = (M601 (0x03, 0x04) >= Arg1)
            M600 (Arg0, 0x24, Local0, Ones)
            Local0 = (M601 (0x03, 0x05) >= Arg1)
            M600 (Arg0, 0x25, Local0, Ones)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x03, 0x04, 0x01)) >= Arg1)
                M600 (Arg0, 0x26, Local0, Ones)
                Local0 = (DerefOf (M602 (0x03, 0x05, 0x01)) >= Arg1)
                M600 (Arg0, 0x27, Local0, Ones)
            }

            /* LLess */

            Local0 = (Buffer (0x08)
                    {
                         0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE   // ..P...|.
                    } < Arg1)
            M600 (Arg0, 0x28, Local0, Zero)
            Local0 = (Buffer (0x08)
                    {
                         0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFF   // ..P...|.
                    } < Arg1)
            M600 (Arg0, 0x29, Local0, Zero)
            Local0 = (Buffer (0x08)
                    {
                         0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFD   // ..P...|.
                    } < Arg1)
            M600 (Arg0, 0x2A, Local0, Ones)
            Local0 = (Buffer (0x09)
                    {
                        /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                        /* 0008 */  0x01                                             // .
                    } < Arg1)
            M600 (Arg0, 0x2B, Local0, Zero)
            Local0 = (AUB4 < Arg1)
            M600 (Arg0, 0x2C, Local0, Zero)
            Local0 = (AUB5 < Arg1)
            M600 (Arg0, 0x2D, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUB4)) < Arg1)
                M600 (Arg0, 0x2E, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUB5)) < Arg1)
                M600 (Arg0, 0x2F, Local0, Zero)
            }

            Local0 = (DerefOf (PAUB [0x04]) < Arg1)
            M600 (Arg0, 0x30, Local0, Zero)
            Local0 = (DerefOf (PAUB [0x05]) < Arg1)
            M600 (Arg0, 0x31, Local0, Zero)
            /* Method returns Buffer */

            Local0 = (M601 (0x03, 0x04) < Arg1)
            M600 (Arg0, 0x32, Local0, Zero)
            Local0 = (M601 (0x03, 0x05) < Arg1)
            M600 (Arg0, 0x33, Local0, Zero)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x03, 0x04, 0x01)) < Arg1)
                M600 (Arg0, 0x34, Local0, Zero)
                Local0 = (DerefOf (M602 (0x03, 0x05, 0x01)) < Arg1)
                M600 (Arg0, 0x35, Local0, Zero)
            }

            /* LLessEqual */

            Local0 = (Buffer (0x08)
                        {
                             0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE   // ..P...|.
                        } <= Arg1)
            M600 (Arg0, 0x36, Local0, Ones)
            Local0 = (Buffer (0x08)
                        {
                             0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFF   // ..P...|.
                        } <= Arg1)
            M600 (Arg0, 0x37, Local0, Zero)
            Local0 = (Buffer (0x08)
                        {
                             0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFD   // ..P...|.
                        } <= Arg1)
            M600 (Arg0, 0x38, Local0, Ones)
            Local0 = (Buffer (0x09)
                        {
                            /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                            /* 0008 */  0x01                                             // .
                        } <= Arg1)
            M600 (Arg0, 0x39, Local0, Zero)
            Local0 = (AUB4 <= Arg1)
            M600 (Arg0, 0x3A, Local0, Ones)
            Local0 = (AUB5 <= Arg1)
            M600 (Arg0, 0x3B, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUB4)) <= Arg1)
                M600 (Arg0, 0x3C, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUB5)) <= Arg1)
                M600 (Arg0, 0x3D, Local0, Zero)
            }

            Local0 = (DerefOf (PAUB [0x04]) <= Arg1)
            M600 (Arg0, 0x3E, Local0, Ones)
            Local0 = (DerefOf (PAUB [0x05]) <= Arg1)
            M600 (Arg0, 0x3F, Local0, Zero)
            /* Method returns Buffer */

            Local0 = (M601 (0x03, 0x04) <= Arg1)
            M600 (Arg0, 0x40, Local0, Ones)
            Local0 = (M601 (0x03, 0x05) <= Arg1)
            M600 (Arg0, 0x41, Local0, Zero)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x03, 0x04, 0x01)) <= Arg1)
                M600 (Arg0, 0x42, Local0, Ones)
                Local0 = (DerefOf (M602 (0x03, 0x05, 0x01)) <= Arg1)
                M600 (Arg0, 0x43, Local0, Zero)
            }

            /* LNotEqual */

            Local0 = (Buffer (0x08)
                        {
                             0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE   // ..P...|.
                        } != Arg1)
            M600 (Arg0, 0x44, Local0, Zero)
            Local0 = (Buffer (0x08)
                        {
                             0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFF   // ..P...|.
                        } != Arg1)
            M600 (Arg0, 0x45, Local0, Ones)
            Local0 = (Buffer (0x08)
                        {
                             0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFD   // ..P...|.
                        } != Arg1)
            M600 (Arg0, 0x46, Local0, Ones)
            Local0 = (Buffer (0x09)
                        {
                            /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                            /* 0008 */  0x01                                             // .
                        } != Arg1)
            M600 (Arg0, 0x47, Local0, Ones)
            Local0 = (AUB4 != Arg1)
            M600 (Arg0, 0x48, Local0, Zero)
            Local0 = (AUB5 != Arg1)
            M600 (Arg0, 0x49, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUB4)) != Arg1)
                M600 (Arg0, 0x4A, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUB5)) != Arg1)
                M600 (Arg0, 0x4B, Local0, Ones)
            }

            Local0 = (DerefOf (PAUB [0x04]) != Arg1)
            M600 (Arg0, 0x4C, Local0, Zero)
            Local0 = (DerefOf (PAUB [0x05]) != Arg1)
            M600 (Arg0, 0x4D, Local0, Ones)
            /* Method returns Buffer */

            Local0 = (M601 (0x03, 0x04) != Arg1)
            M600 (Arg0, 0x4E, Local0, Zero)
            Local0 = (M601 (0x03, 0x05) != Arg1)
            M600 (Arg0, 0x4F, Local0, Ones)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x03, 0x04, 0x01)) != Arg1)
                M600 (Arg0, 0x50, Local0, Zero)
                Local0 = (DerefOf (M602 (0x03, 0x05, 0x01)) != Arg1)
                M600 (Arg0, 0x51, Local0, Ones)
            }
        }

        Method (M324, 2, NotSerialized)
        {
            /* LEqual */

            Local0 = (Buffer (0x04)
                    {
                         0xFE, 0xB3, 0x79, 0xC1                           // ..y.
                    } == Arg1)
            M600 (Arg0, 0x00, Local0, Ones)
            Local0 = (Buffer (0x04)
                    {
                         0xFE, 0xB3, 0x79, 0xC0                           // ..y.
                    } == Arg1)
            M600 (Arg0, 0x01, Local0, Zero)
            Local0 = (AUB3 == Arg1)
            M600 (Arg0, 0x02, Local0, Ones)
            Local0 = (AUB2 == Arg1)
            M600 (Arg0, 0x03, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUB3)) == Arg1)
                M600 (Arg0, 0x04, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUB2)) == Arg1)
                M600 (Arg0, 0x05, Local0, Zero)
            }

            Local0 = (DerefOf (PAUB [0x03]) == Arg1)
            M600 (Arg0, 0x06, Local0, Ones)
            Local0 = (DerefOf (PAUB [0x02]) == Arg1)
            M600 (Arg0, 0x07, Local0, Zero)
            /* Method returns Buffer */

            Local0 = (M601 (0x03, 0x03) == Arg1)
            M600 (Arg0, 0x08, Local0, Ones)
            Local0 = (M601 (0x03, 0x02) == Arg1)
            M600 (Arg0, 0x09, Local0, Zero)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x03, 0x03, 0x01)) == Arg1)
                M600 (Arg0, 0x0A, Local0, Ones)
                Local0 = (DerefOf (M602 (0x03, 0x02, 0x01)) == Arg1)
                M600 (Arg0, 0x0B, Local0, Zero)
            }

            /* LGreater */

            Local0 = (Buffer (0x04)
                    {
                         0xFE, 0xB3, 0x79, 0xC1                           // ..y.
                    } > Arg1)
            M600 (Arg0, 0x0C, Local0, Zero)
            Local0 = (Buffer (0x04)
                    {
                         0xFE, 0xB3, 0x79, 0xC2                           // ..y.
                    } > Arg1)
            M600 (Arg0, 0x0D, Local0, Ones)
            Local0 = (Buffer (0x04)
                    {
                         0xFE, 0xB3, 0x79, 0xC0                           // ..y.
                    } > Arg1)
            M600 (Arg0, 0x0E, Local0, Zero)
            Local0 = (Buffer (0x05)
                    {
                         0xFE, 0xB3, 0x79, 0xC1, 0x01                     // ..y..
                    } > Arg1)
            M600 (Arg0, 0x0F, Local0, Ones)
            Local0 = (AUB3 > Arg1)
            M600 (Arg0, 0x10, Local0, Zero)
            Local0 = (AUB2 > Arg1)
            M600 (Arg0, 0x11, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUB3)) > Arg1)
                M600 (Arg0, 0x12, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUB2)) > Arg1)
                M600 (Arg0, 0x13, Local0, Ones)
            }

            Local0 = (DerefOf (PAUB [0x03]) > Arg1)
            M600 (Arg0, 0x14, Local0, Zero)
            Local0 = (DerefOf (PAUB [0x02]) > Arg1)
            M600 (Arg0, 0x15, Local0, Ones)
            /* Method returns Buffer */

            Local0 = (M601 (0x03, 0x03) > Arg1)
            M600 (Arg0, 0x16, Local0, Zero)
            Local0 = (M601 (0x03, 0x02) > Arg1)
            M600 (Arg0, 0x17, Local0, Ones)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x03, 0x03, 0x01)) > Arg1)
                M600 (Arg0, 0x18, Local0, Zero)
                Local0 = (DerefOf (M602 (0x03, 0x02, 0x01)) > Arg1)
                M600 (Arg0, 0x19, Local0, Ones)
            }

            /* LGreaterEqual */

            Local0 = (Buffer (0x04)
                        {
                             0xFE, 0xB3, 0x79, 0xC1                           // ..y.
                        } >= Arg1)
            M600 (Arg0, 0x1A, Local0, Ones)
            Local0 = (Buffer (0x04)
                        {
                             0xFE, 0xB3, 0x79, 0xC2                           // ..y.
                        } >= Arg1)
            M600 (Arg0, 0x1B, Local0, Ones)
            Local0 = (Buffer (0x04)
                        {
                             0xFE, 0xB3, 0x79, 0xC0                           // ..y.
                        } >= Arg1)
            M600 (Arg0, 0x1C, Local0, Zero)
            Local0 = (Buffer (0x05)
                        {
                             0xFE, 0xB3, 0x79, 0xC1, 0x01                     // ..y..
                        } >= Arg1)
            M600 (Arg0, 0x1D, Local0, Ones)
            Local0 = (AUB3 >= Arg1)
            M600 (Arg0, 0x1E, Local0, Ones)
            Local0 = (AUB2 >= Arg1)
            M600 (Arg0, 0x1F, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUB3)) >= Arg1)
                M600 (Arg0, 0x20, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUB2)) >= Arg1)
                M600 (Arg0, 0x21, Local0, Ones)
            }

            Local0 = (DerefOf (PAUB [0x03]) >= Arg1)
            M600 (Arg0, 0x22, Local0, Ones)
            Local0 = (DerefOf (PAUB [0x02]) >= Arg1)
            M600 (Arg0, 0x23, Local0, Ones)
            /* Method returns Buffer */

            Local0 = (M601 (0x03, 0x03) >= Arg1)
            M600 (Arg0, 0x24, Local0, Ones)
            Local0 = (M601 (0x03, 0x02) >= Arg1)
            M600 (Arg0, 0x25, Local0, Ones)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x03, 0x03, 0x01)) >= Arg1)
                M600 (Arg0, 0x26, Local0, Ones)
                Local0 = (DerefOf (M602 (0x03, 0x02, 0x01)) >= Arg1)
                M600 (Arg0, 0x27, Local0, Ones)
            }

            /* LLess */

            Local0 = (Buffer (0x04)
                    {
                         0xFE, 0xB3, 0x79, 0xC1                           // ..y.
                    } < Arg1)
            M600 (Arg0, 0x28, Local0, Zero)
            Local0 = (Buffer (0x04)
                    {
                         0xFE, 0xB3, 0x79, 0xC2                           // ..y.
                    } < Arg1)
            M600 (Arg0, 0x29, Local0, Zero)
            Local0 = (Buffer (0x04)
                    {
                         0xFE, 0xB3, 0x79, 0xC0                           // ..y.
                    } < Arg1)
            M600 (Arg0, 0x2A, Local0, Ones)
            Local0 = (Buffer (0x05)
                    {
                         0xFE, 0xB3, 0x79, 0xC1, 0x01                     // ..y..
                    } < Arg1)
            M600 (Arg0, 0x2B, Local0, Zero)
            Local0 = (AUB3 < Arg1)
            M600 (Arg0, 0x2C, Local0, Zero)
            Local0 = (AUB2 < Arg1)
            M600 (Arg0, 0x2D, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUB3)) < Arg1)
                M600 (Arg0, 0x2E, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUB2)) < Arg1)
                M600 (Arg0, 0x2F, Local0, Zero)
            }

            Local0 = (DerefOf (PAUB [0x03]) < Arg1)
            M600 (Arg0, 0x30, Local0, Zero)
            Local0 = (DerefOf (PAUB [0x02]) < Arg1)
            M600 (Arg0, 0x31, Local0, Zero)
            /* Method returns Buffer */

            Local0 = (M601 (0x03, 0x03) < Arg1)
            M600 (Arg0, 0x32, Local0, Zero)
            Local0 = (M601 (0x03, 0x02) < Arg1)
            M600 (Arg0, 0x33, Local0, Zero)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x03, 0x03, 0x01)) < Arg1)
                M600 (Arg0, 0x34, Local0, Zero)
                Local0 = (DerefOf (M602 (0x03, 0x02, 0x01)) < Arg1)
                M600 (Arg0, 0x35, Local0, Zero)
            }

            /* LLessEqual */

            Local0 = (Buffer (0x04)
                        {
                             0xFE, 0xB3, 0x79, 0xC1                           // ..y.
                        } <= Arg1)
            M600 (Arg0, 0x36, Local0, Ones)
            Local0 = (Buffer (0x04)
                        {
                             0xFE, 0xB3, 0x79, 0xC2                           // ..y.
                        } <= Arg1)
            M600 (Arg0, 0x37, Local0, Zero)
            Local0 = (Buffer (0x04)
                        {
                             0xFE, 0xB3, 0x79, 0xC0                           // ..y.
                        } <= Arg1)
            M600 (Arg0, 0x38, Local0, Ones)
            Local0 = (Buffer (0x05)
                        {
                             0xFE, 0xB3, 0x79, 0xC1, 0x01                     // ..y..
                        } <= Arg1)
            M600 (Arg0, 0x39, Local0, Zero)
            Local0 = (AUB3 <= Arg1)
            M600 (Arg0, 0x3A, Local0, Ones)
            Local0 = (AUB2 <= Arg1)
            M600 (Arg0, 0x3B, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUB3)) <= Arg1)
                M600 (Arg0, 0x3C, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUB2)) <= Arg1)
                M600 (Arg0, 0x3D, Local0, Zero)
            }

            Local0 = (DerefOf (PAUB [0x03]) <= Arg1)
            M600 (Arg0, 0x3E, Local0, Ones)
            Local0 = (DerefOf (PAUB [0x02]) <= Arg1)
            M600 (Arg0, 0x3F, Local0, Zero)
            /* Method returns Buffer */

            Local0 = (M601 (0x03, 0x03) <= Arg1)
            M600 (Arg0, 0x40, Local0, Ones)
            Local0 = (M601 (0x03, 0x02) <= Arg1)
            M600 (Arg0, 0x41, Local0, Zero)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x03, 0x03, 0x01)) <= Arg1)
                M600 (Arg0, 0x42, Local0, Ones)
                Local0 = (DerefOf (M602 (0x03, 0x02, 0x01)) <= Arg1)
                M600 (Arg0, 0x43, Local0, Zero)
            }

            /* LNotEqual */

            Local0 = (Buffer (0x04)
                        {
                             0xFE, 0xB3, 0x79, 0xC1                           // ..y.
                        } != Arg1)
            M600 (Arg0, 0x44, Local0, Zero)
            Local0 = (Buffer (0x04)
                        {
                             0xFE, 0xB3, 0x79, 0xC2                           // ..y.
                        } != Arg1)
            M600 (Arg0, 0x45, Local0, Ones)
            Local0 = (Buffer (0x04)
                        {
                             0xFE, 0xB3, 0x79, 0xC0                           // ..y.
                        } != Arg1)
            M600 (Arg0, 0x46, Local0, Ones)
            Local0 = (Buffer (0x05)
                        {
                             0xFE, 0xB3, 0x79, 0xC1, 0x01                     // ..y..
                        } != Arg1)
            M600 (Arg0, 0x47, Local0, Ones)
            Local0 = (AUB3 != Arg1)
            M600 (Arg0, 0x48, Local0, Zero)
            Local0 = (AUB2 != Arg1)
            M600 (Arg0, 0x49, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUB3)) != Arg1)
                M600 (Arg0, 0x4A, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUB2)) != Arg1)
                M600 (Arg0, 0x4B, Local0, Ones)
            }

            Local0 = (DerefOf (PAUB [0x03]) != Arg1)
            M600 (Arg0, 0x4C, Local0, Zero)
            Local0 = (DerefOf (PAUB [0x02]) != Arg1)
            M600 (Arg0, 0x4D, Local0, Ones)
            /* Method returns Buffer */

            Local0 = (M601 (0x03, 0x03) != Arg1)
            M600 (Arg0, 0x4E, Local0, Zero)
            Local0 = (M601 (0x03, 0x02) != Arg1)
            M600 (Arg0, 0x4F, Local0, Ones)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x03, 0x03, 0x01)) != Arg1)
                M600 (Arg0, 0x50, Local0, Zero)
                Local0 = (DerefOf (M602 (0x03, 0x02, 0x01)) != Arg1)
                M600 (Arg0, 0x51, Local0, Ones)
            }
        }

        /* Integer to Buffer conversion of the both Integer operands of */
        /* Concatenate operator */
        Method (M645, 2, NotSerialized)
        {
            Local0 = Concatenate (Arg1, Arg1)
            M600 (Arg0, 0x00, Local0, BB20)
            Local0 = Concatenate (0x0321, Arg1)
            M600 (Arg0, 0x01, Local0, BB21)
            Local0 = Concatenate (Arg1, 0x0321)
            M600 (Arg0, 0x01, Local0, BB22)
            Concatenate (Arg1, Arg1, Local0)
            M600 (Arg0, 0x00, Local0, BB20)
            Concatenate (0x0321, Arg1, Local0)
            M600 (Arg0, 0x01, Local0, BB21)
            Concatenate (Arg1, 0x0321, Local0)
            M600 (Arg0, 0x01, Local0, BB22)
        }

        Method (M325, 2, NotSerialized)
        {
            Local0 = Concatenate (Arg1, Arg1)
            M600 (Arg0, 0x00, Local0, BB23)
            Local0 = Concatenate (0x0321, Arg1)
            M600 (Arg0, 0x01, Local0, BB24)
            Local0 = Concatenate (Arg1, 0x0321)
            M600 (Arg0, 0x01, Local0, BB25)
            Concatenate (Arg1, Arg1, Local0)
            M600 (Arg0, 0x00, Local0, BB23)
            Concatenate (0x0321, Arg1, Local0)
            M600 (Arg0, 0x01, Local0, BB24)
            Concatenate (Arg1, 0x0321, Local0)
            M600 (Arg0, 0x01, Local0, BB25)
        }

        /* Integer to Buffer conversion of the Integer second operand of */
        /* Concatenate operator when the first operand is evaluated as Buffer */
        Method (M646, 2, NotSerialized)
        {
            Local0 = Concatenate (Buffer (0x01)
                    {
                         0x5A                                             // Z
                    }, Arg1)
            M600 (Arg0, 0x00, Local0, BB10)
            Local0 = Concatenate (Buffer (0x02)
                    {
                        "Z"
                    }, Arg1)
            M600 (Arg0, 0x01, Local0, BB11)
            Local0 = Concatenate (AUB0, Arg1)
            M600 (Arg0, 0x02, Local0, BB10)
            Local0 = Concatenate (AUB1, Arg1)
            M600 (Arg0, 0x03, Local0, BB11)
            If (Y078)
            {
                Local0 = Concatenate (DerefOf (RefOf (AUB0)), Arg1)
                M600 (Arg0, 0x04, Local0, BB10)
                Local0 = Concatenate (DerefOf (RefOf (AUB1)), Arg1)
                M600 (Arg0, 0x05, Local0, BB11)
            }

            Local0 = Concatenate (DerefOf (PAUB [0x00]), Arg1)
            M600 (Arg0, 0x06, Local0, BB10)
            Local0 = Concatenate (DerefOf (PAUB [0x01]), Arg1)
            M600 (Arg0, 0x07, Local0, BB11)
            /* Method returns Buffer */

            Local0 = Concatenate (M601 (0x03, 0x00), Arg1)
            M600 (Arg0, 0x08, Local0, BB10)
            Local0 = Concatenate (M601 (0x03, 0x01), Arg1)
            M600 (Arg0, 0x09, Local0, BB11)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Local0 = Concatenate (DerefOf (M602 (0x03, 0x00, 0x01)), Arg1)
                M600 (Arg0, 0x0A, Local0, BB10)
                Local0 = Concatenate (DerefOf (M602 (0x03, 0x01, 0x01)), Arg1)
                M600 (Arg0, 0x0B, Local0, BB11)
            }

            Concatenate (Buffer (0x01)
                {
                     0x5A                                             // Z
                }, Arg1, Local0)
            M600 (Arg0, 0x0C, Local0, BB10)
            Concatenate (Buffer (0x02)
                {
                    "Z"
                }, Arg1, Local0)
            M600 (Arg0, 0x0D, Local0, BB11)
            Concatenate (AUB0, Arg1, Local0)
            M600 (Arg0, 0x0E, Local0, BB10)
            Concatenate (AUB1, Arg1, Local0)
            M600 (Arg0, 0x0F, Local0, BB11)
            If (Y078)
            {
                Concatenate (DerefOf (RefOf (AUB0)), Arg1, Local0)
                M600 (Arg0, 0x10, Local0, BB10)
                Concatenate (DerefOf (RefOf (AUB1)), Arg1, Local0)
                M600 (Arg0, 0x11, Local0, BB11)
            }

            Concatenate (DerefOf (PAUB [0x00]), Arg1, Local0)
            M600 (Arg0, 0x12, Local0, BB10)
            Concatenate (DerefOf (PAUB [0x01]), Arg1, Local0)
            M600 (Arg0, 0x13, Local0, BB11)
            /* Method returns Buffer */

            Concatenate (M601 (0x03, 0x00), Arg1, Local0)
            M600 (Arg0, 0x14, Local0, BB10)
            Concatenate (M601 (0x03, 0x01), Arg1, Local0)
            M600 (Arg0, 0x15, Local0, BB11)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Concatenate (DerefOf (M602 (0x03, 0x00, 0x01)), Arg1, Local0)
                M600 (Arg0, 0x16, Local0, BB10)
                Concatenate (DerefOf (M602 (0x03, 0x01, 0x01)), Arg1, Local0)
                M600 (Arg0, 0x17, Local0, BB11)
            }
        }

        Method (M326, 3, NotSerialized)
        {
            Local0 = Concatenate (Buffer (0x01)
                    {
                         0x5A                                             // Z
                    }, Arg2)
            M600 (Arg0, 0x00, Local0, BB12)
            Local0 = Concatenate (Buffer (0x02)
                    {
                        "Z"
                    }, Arg2)
            M600 (Arg0, 0x01, Local0, BB13)
            Local0 = Concatenate (AUB0, Arg2)
            M600 (Arg0, 0x02, Local0, BB12)
            Local0 = Concatenate (AUB1, Arg2)
            M600 (Arg0, 0x03, Local0, BB13)
            If (Y078)
            {
                Local0 = Concatenate (DerefOf (RefOf (AUB0)), Arg2)
                M600 (Arg0, 0x04, Local0, BB12)
                Local0 = Concatenate (DerefOf (RefOf (AUB1)), Arg2)
                M600 (Arg0, 0x05, Local0, BB13)
            }

            Local0 = Concatenate (DerefOf (PAUB [0x00]), Arg2)
            M600 (Arg0, 0x06, Local0, BB12)
            Local0 = Concatenate (DerefOf (PAUB [0x01]), Arg2)
            M600 (Arg0, 0x07, Local0, BB13)
            /* Method returns Buffer */

            Local0 = Concatenate (M601 (0x03, 0x00), Arg2)
            M600 (Arg0, 0x08, Local0, BB12)
            Local0 = Concatenate (M601 (0x03, 0x01), Arg2)
            M600 (Arg0, 0x09, Local0, BB13)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Local0 = Concatenate (DerefOf (M602 (0x03, 0x00, 0x01)), Arg2)
                M600 (Arg0, 0x0A, Local0, BB12)
                Local0 = Concatenate (DerefOf (M602 (0x03, 0x01, 0x01)), Arg2)
                M600 (Arg0, 0x0B, Local0, BB13)
            }

            Local0 = Concatenate (Buffer (0x01)
                    {
                         0x5A                                             // Z
                    }, Arg1)
            M600 (Arg0, 0x0C, Local0, BB14)
            Local0 = Concatenate (Buffer (0x02)
                    {
                        "Z"
                    }, Arg1)
            M600 (Arg0, 0x0D, Local0, BB15)
            Concatenate (Buffer (0x01)
                {
                     0x5A                                             // Z
                }, Arg2, Local0)
            M600 (Arg0, 0x0E, Local0, BB12)
            Concatenate (Buffer (0x02)
                {
                    "Z"
                }, Arg2, Local0)
            M600 (Arg0, 0x0F, Local0, BB13)
            Concatenate (AUB0, Arg2, Local0)
            M600 (Arg0, 0x10, Local0, BB12)
            Concatenate (AUB1, Arg2, Local0)
            M600 (Arg0, 0x11, Local0, BB13)
            If (Y078)
            {
                Concatenate (DerefOf (RefOf (AUB0)), Arg2, Local0)
                M600 (Arg0, 0x12, Local0, BB12)
                Concatenate (DerefOf (RefOf (AUB1)), Arg2, Local0)
                M600 (Arg0, 0x13, Local0, BB13)
            }

            Concatenate (DerefOf (PAUB [0x00]), Arg2, Local0)
            M600 (Arg0, 0x14, Local0, BB12)
            Concatenate (DerefOf (PAUB [0x01]), Arg2, Local0)
            M600 (Arg0, 0x15, Local0, BB13)
            /* Method returns Buffer */

            Concatenate (M601 (0x03, 0x00), Arg2, Local0)
            M600 (Arg0, 0x16, Local0, BB12)
            Concatenate (M601 (0x03, 0x01), Arg2, Local0)
            M600 (Arg0, 0x17, Local0, BB13)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Concatenate (DerefOf (M602 (0x03, 0x00, 0x01)), Arg2, Local0)
                M600 (Arg0, 0x18, Local0, BB12)
                Concatenate (DerefOf (M602 (0x03, 0x01, 0x01)), Arg2, Local0)
                M600 (Arg0, 0x19, Local0, BB13)
            }

            Concatenate (Buffer (0x01)
                {
                     0x5A                                             // Z
                }, Arg1, Local0)
            M600 (Arg0, 0x1A, Local0, BB14)
            Concatenate (Buffer (0x02)
                {
                    "Z"
                }, Arg1, Local0)
            M600 (Arg0, 0x1B, Local0, BB15)
        }

        /* Integer to Buffer conversion of the Integer Source operand of */
        /* ToString operator */
        Method (M647, 3, NotSerialized)
        {
            Local0 = ToString (Arg1, Ones)
            M600 (Arg0, 0x00, Local0, BS18)
            Local0 = ToString (Arg1, 0x03)
            M600 (Arg0, 0x01, Local0, BS19)
            Local0 = ToString (Arg2, Ones)
            M600 (Arg0, 0x02, Local0, BS1A)
            Local0 = ToString (Arg1, AUI0)
            M600 (Arg0, 0x03, Local0, BS18)
            Local0 = ToString (Arg1, AUI7)
            M600 (Arg0, 0x04, Local0, BS19)
            Local0 = ToString (Arg2, AUI0)
            M600 (Arg0, 0x05, Local0, BS1A)
            If (Y078)
            {
                Local0 = ToString (Arg1, DerefOf (RefOf (AUI0)))
                M600 (Arg0, 0x06, Local0, BS18)
                Local0 = ToString (Arg1, DerefOf (RefOf (AUI7)))
                M600 (Arg0, 0x07, Local0, BS19)
                Local0 = ToString (Arg2, DerefOf (RefOf (AUI0)))
                M600 (Arg0, 0x08, Local0, BS1A)
            }

            Local0 = ToString (Arg1, DerefOf (PAUI [0x00]))
            M600 (Arg0, 0x09, Local0, BS18)
            Local0 = ToString (Arg1, DerefOf (PAUI [0x07]))
            M600 (Arg0, 0x0A, Local0, BS19)
            Local0 = ToString (Arg2, DerefOf (PAUI [0x00]))
            M600 (Arg0, 0x0B, Local0, BS1A)
            /* Method returns Length parameter */

            Local0 = ToString (Arg1, M601 (0x01, 0x00))
            M600 (Arg0, 0x0C, Local0, BS18)
            Local0 = ToString (Arg1, M601 (0x01, 0x07))
            M600 (Arg0, 0x0D, Local0, BS19)
            Local0 = ToString (Arg2, M601 (0x01, 0x00))
            M600 (Arg0, 0x0E, Local0, BS1A)
            /* Method returns Reference to Length parameter */

            If (Y500)
            {
                Local0 = ToString (Arg1, DerefOf (M601 (0x01, 0x00)))
                M600 (Arg0, 0x0F, Local0, BS18)
                Local0 = ToString (Arg1, DerefOf (M601 (0x01, 0x07)))
                M600 (Arg0, 0x10, Local0, BS19)
                Local0 = ToString (Arg2, DerefOf (M601 (0x01, 0x00)))
                M600 (Arg0, 0x11, Local0, BS1A)
            }

            ToString (Arg1, Ones, Local0)
            M600 (Arg0, 0x12, Local0, BS18)
            ToString (Arg1, 0x03, Local0)
            M600 (Arg0, 0x13, Local0, BS19)
            ToString (Arg2, Ones, Local0)
            M600 (Arg0, 0x14, Local0, BS1A)
            ToString (Arg1, AUI0, Local0)
            M600 (Arg0, 0x15, Local0, BS18)
            ToString (Arg1, AUI7, Local0)
            M600 (Arg0, 0x16, Local0, BS19)
            ToString (Arg2, AUI0, Local0)
            M600 (Arg0, 0x17, Local0, BS1A)
            If (Y078)
            {
                ToString (Arg1, DerefOf (RefOf (AUI0)), Local0)
                M600 (Arg0, 0x18, Local0, BS18)
                ToString (Arg1, DerefOf (RefOf (AUI7)), Local0)
                M600 (Arg0, 0x19, Local0, BS19)
                ToString (Arg2, DerefOf (RefOf (AUI0)), Local0)
                M600 (Arg0, 0x1A, Local0, BS1A)
            }

            ToString (Arg1, DerefOf (PAUI [0x00]), Local0)
            M600 (Arg0, 0x1B, Local0, BS18)
            ToString (Arg1, DerefOf (PAUI [0x07]), Local0)
            M600 (Arg0, 0x1C, Local0, BS19)
            ToString (Arg2, DerefOf (PAUI [0x00]), Local0)
            M600 (Arg0, 0x1D, Local0, BS1A)
            /* Method returns Length parameter */

            ToString (Arg1, M601 (0x01, 0x00), Local0)
            M600 (Arg0, 0x1E, Local0, BS18)
            ToString (Arg1, M601 (0x01, 0x07), Local0)
            M600 (Arg0, 0x1F, Local0, BS19)
            ToString (Arg2, M601 (0x01, 0x00), Local0)
            M600 (Arg0, 0x20, Local0, BS1A)
            /* Method returns Reference to Length parameter */

            If (Y500)
            {
                ToString (Arg1, DerefOf (M601 (0x01, 0x00)), Local0)
                M600 (Arg0, 0x21, Local0, BS18)
                ToString (Arg1, DerefOf (M601 (0x01, 0x07)), Local0)
                M600 (Arg0, 0x22, Local0, BS19)
                ToString (Arg2, DerefOf (M601 (0x01, 0x00)), Local0)
                M600 (Arg0, 0x23, Local0, BS1A)
            }
        }

        Method (M327, 3, NotSerialized)
        {
            Local0 = ToString (Arg1, Ones)
            M600 (Arg0, 0x00, Local0, BS16)
            Local0 = ToString (Arg1, 0x03)
            M600 (Arg0, 0x01, Local0, BS17)
            Local0 = ToString (Arg2, Ones)
            M600 (Arg0, 0x02, Local0, BS1A)
            Local0 = ToString (Arg1, AUI0)
            M600 (Arg0, 0x03, Local0, BS16)
            Local0 = ToString (Arg1, AUI7)
            M600 (Arg0, 0x04, Local0, BS17)
            Local0 = ToString (Arg2, AUI0)
            M600 (Arg0, 0x05, Local0, BS1A)
            If (Y078)
            {
                Local0 = ToString (Arg1, DerefOf (RefOf (AUI0)))
                M600 (Arg0, 0x06, Local0, BS16)
                Local0 = ToString (Arg1, DerefOf (RefOf (AUI7)))
                M600 (Arg0, 0x07, Local0, BS17)
                Local0 = ToString (Arg2, DerefOf (RefOf (AUI0)))
                M600 (Arg0, 0x08, Local0, BS1A)
            }

            Local0 = ToString (Arg1, DerefOf (PAUI [0x00]))
            M600 (Arg0, 0x09, Local0, BS16)
            Local0 = ToString (Arg1, DerefOf (PAUI [0x07]))
            M600 (Arg0, 0x0A, Local0, BS17)
            Local0 = ToString (Arg2, DerefOf (PAUI [0x00]))
            M600 (Arg0, 0x0B, Local0, BS1A)
            /* Method returns Length parameter */

            Local0 = ToString (Arg1, M601 (0x01, 0x00))
            M600 (Arg0, 0x0C, Local0, BS16)
            Local0 = ToString (Arg1, M601 (0x01, 0x07))
            M600 (Arg0, 0x0D, Local0, BS17)
            Local0 = ToString (Arg2, M601 (0x01, 0x00))
            M600 (Arg0, 0x0E, Local0, BS1A)
            /* Method returns Reference to Length parameter */

            If (Y500)
            {
                Local0 = ToString (Arg1, DerefOf (M601 (0x01, 0x00)))
                M600 (Arg0, 0x0F, Local0, BS16)
                Local0 = ToString (Arg1, DerefOf (M601 (0x01, 0x07)))
                M600 (Arg0, 0x10, Local0, BS17)
                Local0 = ToString (Arg2, DerefOf (M601 (0x01, 0x00)))
                M600 (Arg0, 0x11, Local0, BS1A)
            }

            ToString (Arg1, Ones, Local0)
            M600 (Arg0, 0x12, Local0, BS16)
            ToString (Arg1, 0x03, Local0)
            M600 (Arg0, 0x13, Local0, BS17)
            ToString (Arg2, Ones, Local0)
            M600 (Arg0, 0x14, Local0, BS1A)
            ToString (Arg1, AUI0, Local0)
            M600 (Arg0, 0x15, Local0, BS16)
            ToString (Arg1, AUI7, Local0)
            M600 (Arg0, 0x16, Local0, BS17)
            ToString (Arg2, AUI0, Local0)
            M600 (Arg0, 0x17, Local0, BS1A)
            If (Y078)
            {
                ToString (Arg1, DerefOf (RefOf (AUI0)), Local0)
                M600 (Arg0, 0x18, Local0, BS16)
                ToString (Arg1, DerefOf (RefOf (AUI7)), Local0)
                M600 (Arg0, 0x19, Local0, BS17)
                ToString (Arg2, DerefOf (RefOf (AUI0)), Local0)
                M600 (Arg0, 0x1A, Local0, BS1A)
            }

            ToString (Arg1, DerefOf (PAUI [0x00]), Local0)
            M600 (Arg0, 0x1B, Local0, BS16)
            ToString (Arg1, DerefOf (PAUI [0x07]), Local0)
            M600 (Arg0, 0x1C, Local0, BS17)
            ToString (Arg2, DerefOf (PAUI [0x00]), Local0)
            M600 (Arg0, 0x1D, Local0, BS1A)
            /* Method returns Length parameter */

            ToString (Arg1, M601 (0x01, 0x00), Local0)
            M600 (Arg0, 0x1E, Local0, BS16)
            ToString (Arg1, M601 (0x01, 0x07), Local0)
            M600 (Arg0, 0x1F, Local0, BS17)
            ToString (Arg2, M601 (0x01, 0x00), Local0)
            M600 (Arg0, 0x20, Local0, BS1A)
            /* Method returns Reference to Length parameter */

            If (Y500)
            {
                ToString (Arg1, DerefOf (M601 (0x01, 0x00)), Local0)
                M600 (Arg0, 0x21, Local0, BS16)
                ToString (Arg1, DerefOf (M601 (0x01, 0x07)), Local0)
                M600 (Arg0, 0x22, Local0, BS17)
                ToString (Arg2, DerefOf (M601 (0x01, 0x00)), Local0)
                M600 (Arg0, 0x23, Local0, BS1A)
            }
        }

        /* Integer to Buffer conversion of the Integer Source operand of */
        /* Mid operator */
        Method (M648, 3, NotSerialized)
        {
            Local0 = Mid (Arg1, 0x00, 0x09)
            M600 (Arg0, 0x00, Local0, BB1D)
            Local0 = Mid (Arg2, 0x01, 0x08)
            M600 (Arg0, 0x01, Local0, BB30)
            Local0 = Mid (Arg1, AUI5, AUIB)
            M600 (Arg0, 0x02, Local0, BB1D)
            Local0 = Mid (Arg2, AUI6, AUIA)
            M600 (Arg0, 0x03, Local0, BB30)
            If (Y078)
            {
                Local0 = Mid (Arg1, DerefOf (RefOf (AUI5)), DerefOf (RefOf (AUIB)))
                M600 (Arg0, 0x04, Local0, BB1D)
                Local0 = Mid (Arg2, DerefOf (RefOf (AUI6)), DerefOf (RefOf (AUIA)))
                M600 (Arg0, 0x05, Local0, BB30)
            }

            Local0 = Mid (Arg1, DerefOf (PAUI [0x05]), DerefOf (PAUI [
                0x0B]))
            M600 (Arg0, 0x06, Local0, BB1D)
            Local0 = Mid (Arg2, DerefOf (PAUI [0x06]), DerefOf (PAUI [
                0x0A]))
            M600 (Arg0, 0x07, Local0, BB30)
            /* Method returns Index and Length parameters */

            Local0 = Mid (Arg1, M601 (0x01, 0x05), M601 (0x01, 0x0B))
            M600 (Arg0, 0x08, Local0, BB1D)
            Local0 = Mid (Arg2, M601 (0x01, 0x06), M601 (0x01, 0x0A))
            M600 (Arg0, 0x09, Local0, BB30)
            /* Method returns Reference to Index and Length parameters */

            If (Y500)
            {
                Local0 = Mid (Arg1, DerefOf (M601 (0x01, 0x05)), DerefOf (M601 (0x01, 0x0B))
                    )
                M600 (Arg0, 0x0A, Local0, BB1D)
                Local0 = Mid (Arg2, DerefOf (M601 (0x01, 0x06)), DerefOf (M601 (0x01, 0x0A))
                    )
                M600 (Arg0, 0x0B, Local0, BB30)
            }

            Mid (Arg1, 0x00, 0x09, Local0)
            M600 (Arg0, 0x0C, Local0, BB1D)
            Mid (Arg2, 0x01, 0x08, Local0)
            M600 (Arg0, 0x0D, Local0, BB30)
            Mid (Arg1, AUI5, AUIB, Local0)
            M600 (Arg0, 0x0E, Local0, BB1D)
            Mid (Arg2, AUI6, AUIA, Local0)
            M600 (Arg0, 0x0F, Local0, BB30)
            If (Y078)
            {
                Mid (Arg1, DerefOf (RefOf (AUI5)), DerefOf (RefOf (AUIB)), Local0)
                M600 (Arg0, 0x10, Local0, BB1D)
                Mid (Arg2, DerefOf (RefOf (AUI6)), DerefOf (RefOf (AUIA)), Local0)
                M600 (Arg0, 0x11, Local0, BB30)
            }

            Mid (Arg1, DerefOf (PAUI [0x05]), DerefOf (PAUI [0x0B]), 
                Local0)
            M600 (Arg0, 0x12, Local0, BB1D)
            Mid (Arg2, DerefOf (PAUI [0x06]), DerefOf (PAUI [0x0A]), 
                Local0)
            M600 (Arg0, 0x13, Local0, BB30)
            /* Method returns Index and Length parameters */

            Mid (Arg1, M601 (0x01, 0x05), M601 (0x01, 0x0B), Local0)
            M600 (Arg0, 0x14, Local0, BB1D)
            Mid (Arg2, M601 (0x01, 0x06), M601 (0x01, 0x0A), Local0)
            M600 (Arg0, 0x15, Local0, BB30)
            /* Method returns Reference to Index and Length parameters */

            If (Y500)
            {
                Mid (Arg1, DerefOf (M601 (0x01, 0x05)), DerefOf (M601 (0x01, 0x0B)), Local0)
                M600 (Arg0, 0x16, Local0, BB1D)
                Mid (Arg2, DerefOf (M601 (0x01, 0x06)), DerefOf (M601 (0x01, 0x0A)), Local0)
                M600 (Arg0, 0x17, Local0, BB30)
            }
        }

        Method (M328, 3, NotSerialized)
        {
            Local0 = Mid (Arg1, 0x00, 0x05)
            M600 (Arg0, 0x00, Local0, BB1C)
            Local0 = Mid (Arg2, 0x01, 0x04)
            M600 (Arg0, 0x01, Local0, BB31)
            Local0 = Mid (Arg1, AUI5, AUI9)
            M600 (Arg0, 0x02, Local0, BB1C)
            Local0 = Mid (Arg2, AUI6, AUI8)
            M600 (Arg0, 0x03, Local0, BB31)
            If (Y078)
            {
                Local0 = Mid (Arg1, DerefOf (RefOf (AUI5)), DerefOf (RefOf (AUI9)))
                M600 (Arg0, 0x04, Local0, BB1C)
                Local0 = Mid (Arg2, DerefOf (RefOf (AUI6)), DerefOf (RefOf (AUI8)))
                M600 (Arg0, 0x05, Local0, BB31)
            }

            Local0 = Mid (Arg1, DerefOf (PAUI [0x05]), DerefOf (PAUI [
                0x09]))
            M600 (Arg0, 0x06, Local0, BB1C)
            Local0 = Mid (Arg2, DerefOf (PAUI [0x06]), DerefOf (PAUI [
                0x08]))
            M600 (Arg0, 0x07, Local0, BB31)
            /* Method returns Index and Length parameters */

            Local0 = Mid (Arg1, M601 (0x01, 0x05), M601 (0x01, 0x09))
            M600 (Arg0, 0x08, Local0, BB1C)
            Local0 = Mid (Arg2, M601 (0x01, 0x06), M601 (0x01, 0x08))
            M600 (Arg0, 0x09, Local0, BB31)
            /* Method returns Reference to Index and Length parameters */

            If (Y500)
            {
                Local0 = Mid (Arg1, DerefOf (M601 (0x01, 0x05)), DerefOf (M601 (0x01, 0x09))
                    )
                M600 (Arg0, 0x0A, Local0, BB1C)
                Local0 = Mid (Arg2, DerefOf (M601 (0x01, 0x06)), DerefOf (M601 (0x01, 0x08))
                    )
                M600 (Arg0, 0x0B, Local0, BB31)
            }

            Mid (Arg1, 0x00, 0x05, Local0)
            M600 (Arg0, 0x0C, Local0, BB1C)
            Mid (Arg2, 0x01, 0x04, Local0)
            M600 (Arg0, 0x0D, Local0, BB31)
            Mid (Arg1, AUI5, AUI9, Local0)
            M600 (Arg0, 0x0E, Local0, BB1C)
            Mid (Arg2, AUI6, AUI8, Local0)
            M600 (Arg0, 0x0F, Local0, BB31)
            If (Y078)
            {
                Mid (Arg1, DerefOf (RefOf (AUI5)), DerefOf (RefOf (AUI9)), Local0)
                M600 (Arg0, 0x10, Local0, BB1C)
                Mid (Arg2, DerefOf (RefOf (AUI6)), DerefOf (RefOf (AUI8)), Local0)
                M600 (Arg0, 0x11, Local0, BB31)
            }

            Mid (Arg1, DerefOf (PAUI [0x05]), DerefOf (PAUI [0x09]), 
                Local0)
            M600 (Arg0, 0x12, Local0, BB1C)
            Mid (Arg2, DerefOf (PAUI [0x06]), DerefOf (PAUI [0x08]), 
                Local0)
            M600 (Arg0, 0x13, Local0, BB31)
            /* Method returns Index and Length parameters */

            Mid (Arg1, M601 (0x01, 0x05), M601 (0x01, 0x09), Local0)
            M600 (Arg0, 0x14, Local0, BB1C)
            Mid (Arg2, M601 (0x01, 0x06), M601 (0x01, 0x08), Local0)
            M600 (Arg0, 0x15, Local0, BB31)
            /* Method returns Reference to Index and Length parameters */

            If (Y500)
            {
                Mid (Arg1, DerefOf (M601 (0x01, 0x05)), DerefOf (M601 (0x01, 0x09)), Local0)
                M600 (Arg0, 0x16, Local0, BB1C)
                Mid (Arg2, DerefOf (M601 (0x01, 0x06)), DerefOf (M601 (0x01, 0x08)), Local0)
                M600 (Arg0, 0x17, Local0, BB31)
            }
        }

        /*	Method(m649, 1) */
        /*	Method(m329, 1) */
        /*	Method(m64a, 1) */
        /*	Method(m32a, 1) */
        /* String to Integer implicit conversion Cases. */
        /* String to Integer conversion of the String sole operand */
        /* of the 1-parameter Integer arithmetic operators */
        /* (Decrement, Increment, FindSetLeftBit, FindSetRightBit, Not) */
        Method (M64B, 3, NotSerialized)
        {
            /* Decrement */

            If (Y501)
            {
                Local0 = Arg1--
                M600 (Arg0, 0x00, Local0, BI12)
                Local0 = Arg2--
                M600 (Arg0, 0x01, Local0, BI16)
            }

            /* Increment */

            If (Y501)
            {
                Local0 = Arg1++
                M600 (Arg0, 0x02, Local0, BI13)
                Local0 = Arg2++
                M600 (Arg0, 0x03, Local0, BI17)
            }

            /* FindSetLeftBit */

            Local0 = FindSetLeftBit (Arg1)
            M600 (Arg0, 0x04, Local0, 0x0A)
            Local0 = FindSetLeftBit (Arg2)
            M600 (Arg0, 0x05, Local0, 0x40)
            /* FindSetRightBit */

            Local0 = FindSetRightBit (Arg1)
            M600 (Arg0, 0x06, Local0, 0x01)
            Local0 = FindSetRightBit (Arg2)
            M600 (Arg0, 0x07, Local0, 0x03)
            /* Not */

            Store (~Arg1, Local0)
            M600 (Arg0, 0x08, Local0, 0xFFFFFFFFFFFFFCDE)
            Store (~Arg2, Local0)
            M600 (Arg0, 0x09, Local0, 0x01834C6E29AF5D7B)
        }

        Method (M32B, 3, NotSerialized)
        {
            /* Decrement */

            If (Y501)
            {
                Local0 = Arg1--
                M600 (Arg0, 0x00, Local0, BI12)
                Local0 = Arg2--
                M600 (Arg0, 0x01, Local0, BI14)
            }

            /* Increment */

            If (Y501)
            {
                Local0 = Arg1++
                M600 (Arg0, 0x02, Local0, BI13)
                Local0 = Arg2++
                M600 (Arg0, 0x03, Local0, BI15)
            }

            /* FindSetLeftBit */

            Local0 = FindSetLeftBit (Arg1)
            M600 (Arg0, 0x04, Local0, 0x0A)
            Local0 = FindSetLeftBit (Arg2)
            M600 (Arg0, 0x05, Local0, 0x20)
            /* FindSetRightBit */

            Local0 = FindSetRightBit (Arg1)
            M600 (Arg0, 0x06, Local0, 0x01)
            Local0 = FindSetRightBit (Arg2)
            M600 (Arg0, 0x07, Local0, 0x02)
            /* Not */

            Store (~Arg1, Local0)
            M600 (Arg0, 0x08, Local0, 0xFFFFFCDE)
            Store (~Arg2, Local0)
            M600 (Arg0, 0x09, Local0, 0x3E864C01)
        }

        /* String to Integer conversion of the String sole operand */
        /* of the LNot Logical Integer operator */
        Method (M000, 5, NotSerialized)
        {
            Local0 = !Arg4
            M600 (Arg0, 0x00, Local0, Ones)
            Local0 = !Arg1
            M600 (Arg0, 0x01, Local0, Zero)
            If (F64)
            {
                Local0 = !Arg2
                M600 (Arg0, 0x02, Local0, Zero)
            }
            Else
            {
                Local0 = !Arg3
                M600 (Arg0, 0x03, Local0, Zero)
            }
        }

        /* String to Integer conversion of the String sole operand */
        /* of the FromBCD and ToBCD conversion operators */
        Method (M64C, 5, NotSerialized)
        {
            /* FromBCD */

            Local0 = FromBCD (Arg1)
            M600 (Arg0, 0x02, Local0, 0x0141)
            Local0 = FromBCD (Arg3)
            M600 (Arg0, 0x03, Local0, 0x000D76162EE9EC35)
            FromBCD (Arg1, Local0)
            M600 (Arg0, 0x02, Local0, 0x0141)
            FromBCD (Arg3, Local0)
            M600 (Arg0, 0x03, Local0, 0x000D76162EE9EC35)
            /* ToBCD */

            Local0 = ToBCD (Arg1)
            M600 (Arg0, 0x04, Local0, 0x0801)
            /* Error of iASL on constant folding
             Store(ToBCD(arg4), Local0)
             m600(arg0, 5, Local0, 0x3789012345678901)
             */
            ToBCD (Arg1, Local0)
            M600 (Arg0, 0x04, Local0, 0x0801)
            ToBCD (Arg4, Local0)
            M600 (Arg0, 0x05, Local0, 0x3789012345678901)
        }

        Method (M32C, 5, NotSerialized)
        {
            /* FromBCD */

            Local0 = FromBCD (Arg1)
            M600 (Arg0, 0x02, Local0, 0x0141)
            Local0 = FromBCD (Arg3)
            M600 (Arg0, 0x03, Local0, 0x055F2CC0)
            FromBCD (Arg1, Local0)
            M600 (Arg0, 0x02, Local0, 0x0141)
            FromBCD (Arg3, Local0)
            M600 (Arg0, 0x03, Local0, 0x055F2CC0)
            /* ToBCD */

            Local0 = ToBCD (Arg1)
            M600 (Arg0, 0x04, Local0, 0x0801)
            Local0 = ToBCD (Arg4)
            M600 (Arg0, 0x05, Local0, 0x90123456)
            ToBCD (Arg1, Local0)
            M600 (Arg0, 0x04, Local0, 0x0801)
            ToBCD (Arg4, Local0)
            M600 (Arg0, 0x05, Local0, 0x90123456)
        }

        /* String to Integer conversion of each String operand */
        /* of the 2-parameter Integer arithmetic operators */
        /* Add, And, Divide, Mod, Multiply, NAnd, NOr, Or, */
        /* ShiftLeft, ShiftRight, Subtract, Xor */
        /* Add, common 32-bit/64-bit test */
        Method (M001, 2, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg1 + 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0x0321)
            Store ((Arg1 + 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0x0322)
            Store ((Arg1 + AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0x0321)
            Store ((Arg1 + AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0x0322)
            If (Y078)
            {
                Store ((Arg1 + DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0x0321)
                Store ((Arg1 + DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0x0322)
            }

            Store ((Arg1 + DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0x0321)
            Store ((Arg1 + DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0x0322)
            /* Method returns Integer */

            Store ((Arg1 + M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0x0321)
            Store ((Arg1 + M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0x0322)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg1 + DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0x0321)
                Store ((Arg1 + DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x0322)
            }

            Local0 = (Arg1 + 0x00)
            M600 (Arg0, 0x0C, Local0, 0x0321)
            Local0 = (Arg1 + 0x01)
            M600 (Arg0, 0x0D, Local0, 0x0322)
            Local0 = (Arg1 + AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0x0321)
            Local0 = (Arg1 + AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0x0322)
            If (Y078)
            {
                Local0 = (Arg1 + DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0x0321)
                Local0 = (Arg1 + DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0x0322)
            }

            Local0 = (Arg1 + DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0x0321)
            Local0 = (Arg1 + DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0x0322)
            /* Method returns Integer */

            Local0 = (Arg1 + M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0x0321)
            Local0 = (Arg1 + M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0x0322)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg1 + DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0x0321)
                Local0 = (Arg1 + DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0x0322)
            }

            /* Conversion of the second operand */

            Store ((0x00 + Arg1), Local0)
            M600 (Arg0, 0x18, Local0, 0x0321)
            Store ((0x01 + Arg1), Local0)
            M600 (Arg0, 0x19, Local0, 0x0322)
            Store ((AUI5 + Arg1), Local0)
            M600 (Arg0, 0x1A, Local0, 0x0321)
            Store ((AUI6 + Arg1), Local0)
            M600 (Arg0, 0x1B, Local0, 0x0322)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) + Arg1), Local0)
                M600 (Arg0, 0x1C, Local0, 0x0321)
                Store ((DerefOf (RefOf (AUI6)) + Arg1), Local0)
                M600 (Arg0, 0x1D, Local0, 0x0322)
            }

            Store ((DerefOf (PAUI [0x05]) + Arg1), Local0)
            M600 (Arg0, 0x1E, Local0, 0x0321)
            Store ((DerefOf (PAUI [0x06]) + Arg1), Local0)
            M600 (Arg0, 0x1F, Local0, 0x0322)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) + Arg1), Local0)
            M600 (Arg0, 0x20, Local0, 0x0321)
            Store ((M601 (0x01, 0x06) + Arg1), Local0)
            M600 (Arg0, 0x21, Local0, 0x0322)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) + Arg1), Local0)
                M600 (Arg0, 0x22, Local0, 0x0321)
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) + Arg1), Local0)
                M600 (Arg0, 0x23, Local0, 0x0322)
            }

            Local0 = (0x00 + Arg1)
            M600 (Arg0, 0x24, Local0, 0x0321)
            Local0 = (0x01 + Arg1)
            M600 (Arg0, 0x25, Local0, 0x0322)
            Local0 = (AUI5 + Arg1)
            M600 (Arg0, 0x26, Local0, 0x0321)
            Local0 = (AUI6 + Arg1)
            M600 (Arg0, 0x27, Local0, 0x0322)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) + Arg1)
                M600 (Arg0, 0x28, Local0, 0x0321)
                Local0 = (DerefOf (RefOf (AUI6)) + Arg1)
                M600 (Arg0, 0x29, Local0, 0x0322)
            }

            Local0 = (DerefOf (PAUI [0x05]) + Arg1)
            M600 (Arg0, 0x2A, Local0, 0x0321)
            Local0 = (DerefOf (PAUI [0x06]) + Arg1)
            M600 (Arg0, 0x2B, Local0, 0x0322)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) + Arg1)
            M600 (Arg0, 0x2C, Local0, 0x0321)
            Local0 = (M601 (0x01, 0x06) + Arg1)
            M600 (Arg0, 0x2D, Local0, 0x0322)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) + Arg1)
                M600 (Arg0, 0x2E, Local0, 0x0321)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) + Arg1)
                M600 (Arg0, 0x2F, Local0, 0x0322)
            }
        }

        /* Add, 64-bit */

        Method (M002, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 + 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 + 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0xFE7CB391D650A285)
            Store ((Arg2 + AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 + AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0xFE7CB391D650A285)
            If (Y078)
            {
                Store ((Arg2 + DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 + DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0xFE7CB391D650A285)
            }

            Store ((Arg2 + DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 + DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0xFE7CB391D650A285)
            /* Method returns Integer */

            Store ((Arg2 + M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 + M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0xFE7CB391D650A285)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 + DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 + DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0xFE7CB391D650A285)
            }

            Local0 = (Arg2 + 0x00)
            M600 (Arg0, 0x0C, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 + 0x01)
            M600 (Arg0, 0x0D, Local0, 0xFE7CB391D650A285)
            Local0 = (Arg2 + AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 + AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0xFE7CB391D650A285)
            If (Y078)
            {
                Local0 = (Arg2 + DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0xFE7CB391D650A284)
                Local0 = (Arg2 + DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0xFE7CB391D650A285)
            }

            Local0 = (Arg2 + DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 + DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0xFE7CB391D650A285)
            /* Method returns Integer */

            Local0 = (Arg2 + M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 + M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0xFE7CB391D650A285)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 + DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0xFE7CB391D650A284)
                Local0 = (Arg2 + DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0xFE7CB391D650A285)
            }

            /* Conversion of the second operand */

            Store ((0x00 + Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0xFE7CB391D650A284)
            Store ((0x01 + Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0xFE7CB391D650A285)
            Store ((AUI5 + Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0xFE7CB391D650A284)
            Store ((AUI6 + Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0xFE7CB391D650A285)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) + Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0xFE7CB391D650A284)
                Store ((DerefOf (RefOf (AUI6)) + Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0xFE7CB391D650A285)
            }

            Store ((DerefOf (PAUI [0x05]) + Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0xFE7CB391D650A284)
            Store ((DerefOf (PAUI [0x06]) + Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0xFE7CB391D650A285)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) + Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0xFE7CB391D650A284)
            Store ((M601 (0x01, 0x06) + Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0xFE7CB391D650A285)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) + Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0xFE7CB391D650A284)
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) + Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0xFE7CB391D650A285)
            }

            Local0 = (0x00 + Arg2)
            M600 (Arg0, 0x24, Local0, 0xFE7CB391D650A284)
            Local0 = (0x01 + Arg2)
            M600 (Arg0, 0x25, Local0, 0xFE7CB391D650A285)
            Local0 = (AUI5 + Arg2)
            M600 (Arg0, 0x26, Local0, 0xFE7CB391D650A284)
            Local0 = (AUI6 + Arg2)
            M600 (Arg0, 0x27, Local0, 0xFE7CB391D650A285)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) + Arg2)
                M600 (Arg0, 0x28, Local0, 0xFE7CB391D650A284)
                Local0 = (DerefOf (RefOf (AUI6)) + Arg2)
                M600 (Arg0, 0x29, Local0, 0xFE7CB391D650A285)
            }

            Local0 = (DerefOf (PAUI [0x05]) + Arg2)
            M600 (Arg0, 0x2A, Local0, 0xFE7CB391D650A284)
            Local0 = (DerefOf (PAUI [0x06]) + Arg2)
            M600 (Arg0, 0x2B, Local0, 0xFE7CB391D650A285)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) + Arg2)
            M600 (Arg0, 0x2C, Local0, 0xFE7CB391D650A284)
            Local0 = (M601 (0x01, 0x06) + Arg2)
            M600 (Arg0, 0x2D, Local0, 0xFE7CB391D650A285)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) + Arg2)
                M600 (Arg0, 0x2E, Local0, 0xFE7CB391D650A284)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) + Arg2)
                M600 (Arg0, 0x2F, Local0, 0xFE7CB391D650A285)
            }

            /* Conversion of the both operands */

            Store ((Arg1 + Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0xFE7CB391D650A5A5)
            Store ((Arg2 + Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0xFE7CB391D650A5A5)
            Local0 = (Arg1 + Arg2)
            M600 (Arg0, 0x32, Local0, 0xFE7CB391D650A5A5)
            Local0 = (Arg2 + Arg1)
            M600 (Arg0, 0x33, Local0, 0xFE7CB391D650A5A5)
        }

        /* Add, 32-bit */

        Method (M003, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 + 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0xC179B3FE)
            Store ((Arg2 + 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0xC179B3FF)
            Store ((Arg2 + AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0xC179B3FE)
            Store ((Arg2 + AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0xC179B3FF)
            If (Y078)
            {
                Store ((Arg2 + DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0xC179B3FE)
                Store ((Arg2 + DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0xC179B3FF)
            }

            Store ((Arg2 + DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0xC179B3FE)
            Store ((Arg2 + DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0xC179B3FF)
            /* Method returns Integer */

            Store ((Arg2 + M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0xC179B3FE)
            Store ((Arg2 + M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0xC179B3FF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 + DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xC179B3FE)
                Store ((Arg2 + DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0xC179B3FF)
            }

            Local0 = (Arg2 + 0x00)
            M600 (Arg0, 0x0C, Local0, 0xC179B3FE)
            Local0 = (Arg2 + 0x01)
            M600 (Arg0, 0x0D, Local0, 0xC179B3FF)
            Local0 = (Arg2 + AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0xC179B3FE)
            Local0 = (Arg2 + AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0xC179B3FF)
            If (Y078)
            {
                Local0 = (Arg2 + DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0xC179B3FE)
                Local0 = (Arg2 + DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0xC179B3FF)
            }

            Local0 = (Arg2 + DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0xC179B3FE)
            Local0 = (Arg2 + DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0xC179B3FF)
            /* Method returns Integer */

            Local0 = (Arg2 + M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0xC179B3FE)
            Local0 = (Arg2 + M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0xC179B3FF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 + DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0xC179B3FE)
                Local0 = (Arg2 + DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0xC179B3FF)
            }

            /* Conversion of the second operand */

            Store ((0x00 + Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0xC179B3FE)
            Store ((0x01 + Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0xC179B3FF)
            Store ((AUI5 + Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0xC179B3FE)
            Store ((AUI6 + Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0xC179B3FF)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) + Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0xC179B3FE)
                Store ((DerefOf (RefOf (AUI6)) + Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0xC179B3FF)
            }

            Store ((DerefOf (PAUI [0x05]) + Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0xC179B3FE)
            Store ((DerefOf (PAUI [0x06]) + Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0xC179B3FF)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) + Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0xC179B3FE)
            Store ((M601 (0x01, 0x06) + Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0xC179B3FF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) + Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0xC179B3FE)
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) + Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0xC179B3FF)
            }

            Local0 = (0x00 + Arg2)
            M600 (Arg0, 0x24, Local0, 0xC179B3FE)
            Local0 = (0x01 + Arg2)
            M600 (Arg0, 0x25, Local0, 0xC179B3FF)
            Local0 = (AUI5 + Arg2)
            M600 (Arg0, 0x26, Local0, 0xC179B3FE)
            Local0 = (AUI6 + Arg2)
            M600 (Arg0, 0x27, Local0, 0xC179B3FF)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) + Arg2)
                M600 (Arg0, 0x28, Local0, 0xC179B3FE)
                Local0 = (DerefOf (RefOf (AUI6)) + Arg2)
                M600 (Arg0, 0x29, Local0, 0xC179B3FF)
            }

            Local0 = (DerefOf (PAUI [0x05]) + Arg2)
            M600 (Arg0, 0x2A, Local0, 0xC179B3FE)
            Local0 = (DerefOf (PAUI [0x06]) + Arg2)
            M600 (Arg0, 0x2B, Local0, 0xC179B3FF)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) + Arg2)
            M600 (Arg0, 0x2C, Local0, 0xC179B3FE)
            Local0 = (M601 (0x01, 0x06) + Arg2)
            M600 (Arg0, 0x2D, Local0, 0xC179B3FF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) + Arg2)
                M600 (Arg0, 0x2E, Local0, 0xC179B3FE)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) + Arg2)
                M600 (Arg0, 0x2F, Local0, 0xC179B3FF)
            }

            /* Conversion of the both operands */

            Store ((Arg1 + Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0xC179B71F)
            Store ((Arg2 + Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0xC179B71F)
            Local0 = (Arg1 + Arg2)
            M600 (Arg0, 0x32, Local0, 0xC179B71F)
            Local0 = (Arg2 + Arg1)
            M600 (Arg0, 0x33, Local0, 0xC179B71F)
        }

        /* And, common 32-bit/64-bit test */

        Method (M004, 2, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg1 & 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0x00)
            Store ((Arg1 & 0xFFFFFFFFFFFFFFFF), Local0)
            M600 (Arg0, 0x01, Local0, 0x0321)
            Store ((Arg1 & AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0x00)
            Store ((Arg1 & AUIJ), Local0)
            M600 (Arg0, 0x03, Local0, 0x0321)
            If (Y078)
            {
                Store ((Arg1 & DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0x00)
                Store ((Arg1 & DerefOf (RefOf (AUIJ))), Local0)
                M600 (Arg0, 0x05, Local0, 0x0321)
            }

            Store ((Arg1 & DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0x00)
            Store ((Arg1 & DerefOf (PAUI [0x13])), Local0)
            M600 (Arg0, 0x07, Local0, 0x0321)
            /* Method returns Integer */

            Store ((Arg1 & M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0x00)
            Store ((Arg1 & M601 (0x01, 0x13)), Local0)
            M600 (Arg0, 0x09, Local0, 0x0321)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg1 & DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0x00)
                Store ((Arg1 & DerefOf (M602 (0x01, 0x13, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x0321)
            }

            Local0 = (Arg1 & 0x00)
            M600 (Arg0, 0x0C, Local0, 0x00)
            Local0 = (Arg1 & 0xFFFFFFFFFFFFFFFF)
            M600 (Arg0, 0x0D, Local0, 0x0321)
            Local0 = (Arg1 & AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0x00)
            Local0 = (Arg1 & AUIJ) /* \AUIJ */
            M600 (Arg0, 0x0F, Local0, 0x0321)
            If (Y078)
            {
                Local0 = (Arg1 & DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0x00)
                Local0 = (Arg1 & DerefOf (RefOf (AUIJ)))
                M600 (Arg0, 0x11, Local0, 0x0321)
            }

            Local0 = (Arg1 & DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0x00)
            Local0 = (Arg1 & DerefOf (PAUI [0x13]))
            M600 (Arg0, 0x13, Local0, 0x0321)
            /* Method returns Integer */

            Local0 = (Arg1 & M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0x00)
            Local0 = (Arg1 & M601 (0x01, 0x13))
            M600 (Arg0, 0x15, Local0, 0x0321)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg1 & DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0x00)
                Local0 = (Arg1 & DerefOf (M602 (0x01, 0x13, 0x01)))
                M600 (Arg0, 0x17, Local0, 0x0321)
            }

            /* Conversion of the second operand */

            Store ((0x00 & Arg1), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0xFFFFFFFFFFFFFFFF & Arg1), Local0)
            M600 (Arg0, 0x19, Local0, 0x0321)
            Store ((AUI5 & Arg1), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUIJ & Arg1), Local0)
            M600 (Arg0, 0x1B, Local0, 0x0321)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) & Arg1), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUIJ)) & Arg1), Local0)
                M600 (Arg0, 0x1D, Local0, 0x0321)
            }

            Store ((DerefOf (PAUI [0x05]) & Arg1), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x13]) & Arg1), Local0)
            M600 (Arg0, 0x1F, Local0, 0x0321)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) & Arg1), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x13) & Arg1), Local0)
            M600 (Arg0, 0x21, Local0, 0x0321)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) & Arg1), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x13, 0x01)) & Arg1), Local0)
                M600 (Arg0, 0x23, Local0, 0x0321)
            }

            Local0 = (0x00 & Arg1)
            M600 (Arg0, 0x24, Local0, 0x00)
            Local0 = (0xFFFFFFFFFFFFFFFF & Arg1)
            M600 (Arg0, 0x25, Local0, 0x0321)
            Local0 = (AUI5 & Arg1)
            M600 (Arg0, 0x26, Local0, 0x00)
            Local0 = (AUIJ & Arg1)
            M600 (Arg0, 0x27, Local0, 0x0321)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) & Arg1)
                M600 (Arg0, 0x28, Local0, 0x00)
                Local0 = (DerefOf (RefOf (AUIJ)) & Arg1)
                M600 (Arg0, 0x29, Local0, 0x0321)
            }

            Local0 = (DerefOf (PAUI [0x05]) & Arg1)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Local0 = (DerefOf (PAUI [0x13]) & Arg1)
            M600 (Arg0, 0x2B, Local0, 0x0321)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) & Arg1)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Local0 = (M601 (0x01, 0x13) & Arg1)
            M600 (Arg0, 0x2D, Local0, 0x0321)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) & Arg1)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Local0 = (DerefOf (M602 (0x01, 0x13, 0x01)) & Arg1)
                M600 (Arg0, 0x2F, Local0, 0x0321)
            }
        }

        /* And, 64-bit */

        Method (M005, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 & 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0x00)
            Store ((Arg2 & 0xFFFFFFFFFFFFFFFF), Local0)
            M600 (Arg0, 0x01, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 & AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0x00)
            Store ((Arg2 & AUIJ), Local0)
            M600 (Arg0, 0x03, Local0, 0xFE7CB391D650A284)
            If (Y078)
            {
                Store ((Arg2 & DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0x00)
                Store ((Arg2 & DerefOf (RefOf (AUIJ))), Local0)
                M600 (Arg0, 0x05, Local0, 0xFE7CB391D650A284)
            }

            Store ((Arg2 & DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0x00)
            Store ((Arg2 & DerefOf (PAUI [0x13])), Local0)
            M600 (Arg0, 0x07, Local0, 0xFE7CB391D650A284)
            /* Method returns Integer */

            Store ((Arg2 & M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0x00)
            Store ((Arg2 & M601 (0x01, 0x13)), Local0)
            M600 (Arg0, 0x09, Local0, 0xFE7CB391D650A284)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 & DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0x00)
                Store ((Arg2 & DerefOf (M602 (0x01, 0x13, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0xFE7CB391D650A284)
            }

            Local0 = (Arg2 & 0x00)
            M600 (Arg0, 0x0C, Local0, 0x00)
            Local0 = (Arg2 & 0xFFFFFFFFFFFFFFFF)
            M600 (Arg0, 0x0D, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 & AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0x00)
            Local0 = (Arg2 & AUIJ) /* \AUIJ */
            M600 (Arg0, 0x0F, Local0, 0xFE7CB391D650A284)
            If (Y078)
            {
                Local0 = (Arg2 & DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0x00)
                Local0 = (Arg2 & DerefOf (RefOf (AUIJ)))
                M600 (Arg0, 0x11, Local0, 0xFE7CB391D650A284)
            }

            Local0 = (Arg2 & DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0x00)
            Local0 = (Arg2 & DerefOf (PAUI [0x13]))
            M600 (Arg0, 0x13, Local0, 0xFE7CB391D650A284)
            /* Method returns Integer */

            Local0 = (Arg2 & M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0x00)
            Local0 = (Arg2 & M601 (0x01, 0x13))
            M600 (Arg0, 0x15, Local0, 0xFE7CB391D650A284)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 & DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0x00)
                Local0 = (Arg2 & DerefOf (M602 (0x01, 0x13, 0x01)))
                M600 (Arg0, 0x17, Local0, 0xFE7CB391D650A284)
            }

            /* Conversion of the second operand */

            Store ((0x00 & Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0xFFFFFFFFFFFFFFFF & Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0xFE7CB391D650A284)
            Store ((AUI5 & Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUIJ & Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0xFE7CB391D650A284)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) & Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUIJ)) & Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0xFE7CB391D650A284)
            }

            Store ((DerefOf (PAUI [0x05]) & Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x13]) & Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0xFE7CB391D650A284)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) & Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x13) & Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0xFE7CB391D650A284)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) & Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x13, 0x01)) & Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0xFE7CB391D650A284)
            }

            Local0 = (0x00 & Arg2)
            M600 (Arg0, 0x24, Local0, 0x00)
            Local0 = (0xFFFFFFFFFFFFFFFF & Arg2)
            M600 (Arg0, 0x25, Local0, 0xFE7CB391D650A284)
            Local0 = (AUI5 & Arg2)
            M600 (Arg0, 0x26, Local0, 0x00)
            Local0 = (AUIJ & Arg2)
            M600 (Arg0, 0x27, Local0, 0xFE7CB391D650A284)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) & Arg2)
                M600 (Arg0, 0x28, Local0, 0x00)
                Local0 = (DerefOf (RefOf (AUIJ)) & Arg2)
                M600 (Arg0, 0x29, Local0, 0xFE7CB391D650A284)
            }

            Local0 = (DerefOf (PAUI [0x05]) & Arg2)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Local0 = (DerefOf (PAUI [0x13]) & Arg2)
            M600 (Arg0, 0x2B, Local0, 0xFE7CB391D650A284)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) & Arg2)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Local0 = (M601 (0x01, 0x13) & Arg2)
            M600 (Arg0, 0x2D, Local0, 0xFE7CB391D650A284)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) & Arg2)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Local0 = (DerefOf (M602 (0x01, 0x13, 0x01)) & Arg2)
                M600 (Arg0, 0x2F, Local0, 0xFE7CB391D650A284)
            }

            /* Conversion of the both operands */

            Store ((Arg1 & Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0x0200)
            Store ((Arg2 & Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0x0200)
            Local0 = (Arg1 & Arg2)
            M600 (Arg0, 0x32, Local0, 0x0200)
            Local0 = (Arg2 & Arg1)
            M600 (Arg0, 0x33, Local0, 0x0200)
        }

        /* And, 32-bit */

        Method (M006, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 & 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0x00)
            Store ((Arg2 & 0xFFFFFFFF), Local0)
            M600 (Arg0, 0x01, Local0, 0xC179B3FE)
            Store ((Arg2 & AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0x00)
            Store ((Arg2 & AUII), Local0)
            M600 (Arg0, 0x03, Local0, 0xC179B3FE)
            If (Y078)
            {
                Store ((Arg2 & DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0x00)
                Store ((Arg2 & DerefOf (RefOf (AUII))), Local0)
                M600 (Arg0, 0x05, Local0, 0xC179B3FE)
            }

            Store ((Arg2 & DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0x00)
            Store ((Arg2 & DerefOf (PAUI [0x12])), Local0)
            M600 (Arg0, 0x07, Local0, 0xC179B3FE)
            /* Method returns Integer */

            Store ((Arg2 & M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0x00)
            Store ((Arg2 & M601 (0x01, 0x12)), Local0)
            M600 (Arg0, 0x09, Local0, 0xC179B3FE)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 & DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0x00)
                Store ((Arg2 & DerefOf (M602 (0x01, 0x12, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0xC179B3FE)
            }

            Local0 = (Arg2 & 0x00)
            M600 (Arg0, 0x0C, Local0, 0x00)
            Local0 = (Arg2 & 0xFFFFFFFF)
            M600 (Arg0, 0x0D, Local0, 0xC179B3FE)
            Local0 = (Arg2 & AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0x00)
            Local0 = (Arg2 & AUII) /* \AUII */
            M600 (Arg0, 0x0F, Local0, 0xC179B3FE)
            If (Y078)
            {
                Local0 = (Arg2 & DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0x00)
                Local0 = (Arg2 & DerefOf (RefOf (AUII)))
                M600 (Arg0, 0x11, Local0, 0xC179B3FE)
            }

            Local0 = (Arg2 & DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0x00)
            Local0 = (Arg2 & DerefOf (PAUI [0x12]))
            M600 (Arg0, 0x13, Local0, 0xC179B3FE)
            /* Method returns Integer */

            Local0 = (Arg2 & M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0x00)
            Local0 = (Arg2 & M601 (0x01, 0x12))
            M600 (Arg0, 0x15, Local0, 0xC179B3FE)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 & DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0x00)
                Local0 = (Arg2 & DerefOf (M602 (0x01, 0x12, 0x01)))
                M600 (Arg0, 0x17, Local0, 0xC179B3FE)
            }

            /* Conversion of the second operand */

            Store ((0x00 & Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0xFFFFFFFF & Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0xC179B3FE)
            Store ((AUI5 & Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUII & Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0xC179B3FE)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) & Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUII)) & Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0xC179B3FE)
            }

            Store ((DerefOf (PAUI [0x05]) & Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x12]) & Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0xC179B3FE)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) & Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x12) & Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0xC179B3FE)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) & Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x12, 0x01)) & Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0xC179B3FE)
            }

            Local0 = (0x00 & Arg2)
            M600 (Arg0, 0x24, Local0, 0x00)
            Local0 = (0xFFFFFFFF & Arg2)
            M600 (Arg0, 0x25, Local0, 0xC179B3FE)
            Local0 = (AUI5 & Arg2)
            M600 (Arg0, 0x26, Local0, 0x00)
            Local0 = (AUII & Arg2)
            M600 (Arg0, 0x27, Local0, 0xC179B3FE)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) & Arg2)
                M600 (Arg0, 0x28, Local0, 0x00)
                Local0 = (DerefOf (RefOf (AUII)) & Arg2)
                M600 (Arg0, 0x29, Local0, 0xC179B3FE)
            }

            Local0 = (DerefOf (PAUI [0x05]) & Arg2)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Local0 = (DerefOf (PAUI [0x12]) & Arg2)
            M600 (Arg0, 0x2B, Local0, 0xC179B3FE)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) & Arg2)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Local0 = (M601 (0x01, 0x12) & Arg2)
            M600 (Arg0, 0x2D, Local0, 0xC179B3FE)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) & Arg2)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Local0 = (DerefOf (M602 (0x01, 0x12, 0x01)) & Arg2)
                M600 (Arg0, 0x2F, Local0, 0xC179B3FE)
            }

            /* Conversion of the both operands */

            Store ((Arg1 & Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0x0320)
            Store ((Arg2 & Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0x0320)
            Local0 = (Arg1 & Arg2)
            M600 (Arg0, 0x32, Local0, 0x0320)
            Local0 = (Arg2 & Arg1)
            M600 (Arg0, 0x33, Local0, 0x0320)
        }

        /* Divide, common 32-bit/64-bit test */

        Method (M007, 2, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg1 / 0x01), Local0)
            M600 (Arg0, 0x00, Local0, 0x0321)
            Store ((Arg1 / 0x0321), Local0)
            M600 (Arg0, 0x01, Local0, 0x01)
            Store ((Arg1 / AUI6), Local0)
            M600 (Arg0, 0x02, Local0, 0x0321)
            Store ((Arg1 / AUI1), Local0)
            M600 (Arg0, 0x03, Local0, 0x01)
            If (Y078)
            {
                Store ((Arg1 / DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x04, Local0, 0x0321)
                Store ((Arg1 / DerefOf (RefOf (AUI1))), Local0)
                M600 (Arg0, 0x05, Local0, 0x01)
            }

            Store ((Arg1 / DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x06, Local0, 0x0321)
            Store ((Arg1 / DerefOf (PAUI [0x01])), Local0)
            M600 (Arg0, 0x07, Local0, 0x01)
            /* Method returns Integer */

            Store ((Arg1 / M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x08, Local0, 0x0321)
            Store ((Arg1 / M601 (0x01, 0x01)), Local0)
            M600 (Arg0, 0x09, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg1 / DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0x0321)
                Store ((Arg1 / DerefOf (M602 (0x01, 0x01, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x01)
            }

            Divide (Arg1, 0x01, Local1, Local0)
            M600 (Arg0, 0x0C, Local0, 0x0321)
            Divide (Arg1, 0x0321, Local1, Local0)
            M600 (Arg0, 0x0D, Local0, 0x01)
            Divide (Arg1, AUI6, Local1, Local0)
            M600 (Arg0, 0x0E, Local0, 0x0321)
            Divide (Arg1, AUI1, Local1, Local0)
            M600 (Arg0, 0x0F, Local0, 0x01)
            If (Y078)
            {
                Divide (Arg1, DerefOf (RefOf (AUI6)), Local1, Local0)
                M600 (Arg0, 0x10, Local0, 0x0321)
                Divide (Arg1, DerefOf (RefOf (AUI1)), Local1, Local0)
                M600 (Arg0, 0x11, Local0, 0x01)
            }

            Divide (Arg1, DerefOf (PAUI [0x06]), Local1, Local0)
            M600 (Arg0, 0x12, Local0, 0x0321)
            Divide (Arg1, DerefOf (PAUI [0x01]), Local1, Local0)
            M600 (Arg0, 0x13, Local0, 0x01)
            /* Method returns Integer */

            Divide (Arg1, M601 (0x01, 0x06), Local1, Local0)
            M600 (Arg0, 0x14, Local0, 0x0321)
            Divide (Arg1, M601 (0x01, 0x01), Local1, Local0)
            M600 (Arg0, 0x15, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Divide (Arg1, DerefOf (M602 (0x01, 0x06, 0x01)), Local1, Local0)
                M600 (Arg0, 0x16, Local0, 0x0321)
                Divide (Arg1, DerefOf (M602 (0x01, 0x01, 0x01)), Local1, Local0)
                M600 (Arg0, 0x17, Local0, 0x01)
            }

            /* Conversion of the second operand */

            Store ((0x01 / Arg1), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0x0321 / Arg1), Local0)
            M600 (Arg0, 0x19, Local0, 0x01)
            Store ((AUI6 / Arg1), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUI1 / Arg1), Local0)
            M600 (Arg0, 0x1B, Local0, 0x01)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI6)) / Arg1), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUI1)) / Arg1), Local0)
                M600 (Arg0, 0x1D, Local0, 0x01)
            }

            Store ((DerefOf (PAUI [0x06]) / Arg1), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x01]) / Arg1), Local0)
            M600 (Arg0, 0x1F, Local0, 0x01)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x06) / Arg1), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x01) / Arg1), Local0)
            M600 (Arg0, 0x21, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) / Arg1), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x01, 0x01)) / Arg1), Local0)
                M600 (Arg0, 0x23, Local0, 0x01)
            }

            Divide (0x01, Arg1, Local1, Local0)
            M600 (Arg0, 0x24, Local0, 0x00)
            Divide (0x0321, Arg1, Local1, Local0)
            M600 (Arg0, 0x25, Local0, 0x01)
            Divide (AUI6, Arg1, Local1, Local0)
            M600 (Arg0, 0x26, Local0, 0x00)
            Divide (AUI1, Arg1, Local1, Local0)
            M600 (Arg0, 0x27, Local0, 0x01)
            If (Y078)
            {
                Divide (DerefOf (RefOf (AUI6)), Arg1, Local1, Local0)
                M600 (Arg0, 0x28, Local0, 0x00)
                Divide (DerefOf (RefOf (AUI1)), Arg1, Local1, Local0)
                M600 (Arg0, 0x29, Local0, 0x01)
            }

            Divide (DerefOf (PAUI [0x06]), Arg1, Local1, Local0)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Divide (DerefOf (PAUI [0x01]), Arg1, Local1, Local0)
            M600 (Arg0, 0x2B, Local0, 0x01)
            /* Method returns Integer */

            Divide (M601 (0x01, 0x06), Arg1, Local1, Local0)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Divide (M601 (0x01, 0x01), Arg1, Local1, Local0)
            M600 (Arg0, 0x2D, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Divide (DerefOf (M602 (0x01, 0x06, 0x01)), Arg1, Local1, Local0)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Divide (DerefOf (M602 (0x01, 0x01, 0x01)), Arg1, Local1, Local0)
                M600 (Arg0, 0x2F, Local0, 0x01)
            }
        }

        /* Divide, 64-bit */

        Method (M008, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 / 0x01), Local0)
            M600 (Arg0, 0x00, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 / 0xFE7CB391D650A284), Local0)
            M600 (Arg0, 0x01, Local0, 0x01)
            Store ((Arg2 / AUI6), Local0)
            M600 (Arg0, 0x02, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 / AUI4), Local0)
            M600 (Arg0, 0x03, Local0, 0x01)
            If (Y078)
            {
                Store ((Arg2 / DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x04, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 / DerefOf (RefOf (AUI4))), Local0)
                M600 (Arg0, 0x05, Local0, 0x01)
            }

            Store ((Arg2 / DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x06, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 / DerefOf (PAUI [0x04])), Local0)
            M600 (Arg0, 0x07, Local0, 0x01)
            /* Method returns Integer */

            Store ((Arg2 / M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x08, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 / M601 (0x01, 0x04)), Local0)
            M600 (Arg0, 0x09, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 / DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 / DerefOf (M602 (0x01, 0x04, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x01)
            }

            Divide (Arg2, 0x01, Local1, Local0)
            M600 (Arg0, 0x0C, Local0, 0xFE7CB391D650A284)
            Divide (Arg2, 0xFE7CB391D650A284, Local1, Local0)
            M600 (Arg0, 0x0D, Local0, 0x01)
            Divide (Arg2, AUI6, Local1, Local0)
            M600 (Arg0, 0x0E, Local0, 0xFE7CB391D650A284)
            Divide (Arg2, AUI4, Local1, Local0)
            M600 (Arg0, 0x0F, Local0, 0x01)
            If (Y078)
            {
                Divide (Arg2, DerefOf (RefOf (AUI6)), Local1, Local0)
                M600 (Arg0, 0x10, Local0, 0xFE7CB391D650A284)
                Divide (Arg2, DerefOf (RefOf (AUI4)), Local1, Local0)
                M600 (Arg0, 0x11, Local0, 0x01)
            }

            Divide (Arg2, DerefOf (PAUI [0x06]), Local1, Local0)
            M600 (Arg0, 0x12, Local0, 0xFE7CB391D650A284)
            Divide (Arg2, DerefOf (PAUI [0x04]), Local1, Local0)
            M600 (Arg0, 0x13, Local0, 0x01)
            /* Method returns Integer */

            Divide (Arg2, M601 (0x01, 0x06), Local1, Local0)
            M600 (Arg0, 0x14, Local0, 0xFE7CB391D650A284)
            Divide (Arg2, M601 (0x01, 0x04), Local1, Local0)
            M600 (Arg0, 0x15, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Divide (Arg2, DerefOf (M602 (0x01, 0x06, 0x01)), Local1, Local0)
                M600 (Arg0, 0x16, Local0, 0xFE7CB391D650A284)
                Divide (Arg2, DerefOf (M602 (0x01, 0x04, 0x01)), Local1, Local0)
                M600 (Arg0, 0x17, Local0, 0x01)
            }

            /* Conversion of the second operand */

            Store ((0x01 / Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0xFE7CB391D650A284 / Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0x01)
            Store ((AUI6 / Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUI4 / Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0x01)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI6)) / Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUI4)) / Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0x01)
            }

            Store ((DerefOf (PAUI [0x06]) / Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x04]) / Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0x01)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x06) / Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x04) / Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) / Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x04, 0x01)) / Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0x01)
            }

            Divide (0x01, Arg2, Local1, Local0)
            M600 (Arg0, 0x24, Local0, 0x00)
            Divide (0xFE7CB391D650A284, Arg2, Local1, Local0)
            M600 (Arg0, 0x25, Local0, 0x01)
            Divide (AUI6, Arg2, Local1, Local0)
            M600 (Arg0, 0x26, Local0, 0x00)
            Divide (AUI4, Arg2, Local1, Local0)
            M600 (Arg0, 0x27, Local0, 0x01)
            If (Y078)
            {
                Divide (DerefOf (RefOf (AUI6)), Arg2, Local1, Local0)
                M600 (Arg0, 0x28, Local0, 0x00)
                Divide (DerefOf (RefOf (AUI4)), Arg2, Local1, Local0)
                M600 (Arg0, 0x29, Local0, 0x01)
            }

            Divide (DerefOf (PAUI [0x06]), Arg2, Local1, Local0)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Divide (DerefOf (PAUI [0x04]), Arg2, Local1, Local0)
            M600 (Arg0, 0x2B, Local0, 0x01)
            /* Method returns Integer */

            Divide (M601 (0x01, 0x06), Arg2, Local1, Local0)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Divide (M601 (0x01, 0x04), Arg2, Local1, Local0)
            M600 (Arg0, 0x2D, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Divide (DerefOf (M602 (0x01, 0x06, 0x01)), Arg2, Local1, Local0)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Divide (DerefOf (M602 (0x01, 0x04, 0x01)), Arg2, Local1, Local0)
                M600 (Arg0, 0x2F, Local0, 0x01)
            }

            /* Conversion of the both operands */

            Store ((Arg1 / Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0x00)
            Store ((Arg2 / Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0x0051558EB950F5A7)
            Divide (Arg1, Arg2, Local1, Local0)
            M600 (Arg0, 0x32, Local0, 0x00)
            Divide (Arg2, Arg1, Local1, Local0)
            M600 (Arg0, 0x33, Local0, 0x0051558EB950F5A7)
        }

        /* Divide, 32-bit */

        Method (M009, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 / 0x01), Local0)
            M600 (Arg0, 0x00, Local0, 0xC179B3FE)
            Store ((Arg2 / 0xC179B3FE), Local0)
            M600 (Arg0, 0x01, Local0, 0x01)
            Store ((Arg2 / AUI6), Local0)
            M600 (Arg0, 0x02, Local0, 0xC179B3FE)
            Store ((Arg2 / AUI3), Local0)
            M600 (Arg0, 0x03, Local0, 0x01)
            If (Y078)
            {
                Store ((Arg2 / DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x04, Local0, 0xC179B3FE)
                Store ((Arg2 / DerefOf (RefOf (AUI3))), Local0)
                M600 (Arg0, 0x05, Local0, 0x01)
            }

            Store ((Arg2 / DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x06, Local0, 0xC179B3FE)
            Store ((Arg2 / DerefOf (PAUI [0x03])), Local0)
            M600 (Arg0, 0x07, Local0, 0x01)
            /* Method returns Integer */

            Store ((Arg2 / M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x08, Local0, 0xC179B3FE)
            Store ((Arg2 / M601 (0x01, 0x03)), Local0)
            M600 (Arg0, 0x09, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 / DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xC179B3FE)
                Store ((Arg2 / DerefOf (M602 (0x01, 0x03, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x01)
            }

            Divide (Arg2, 0x01, Local1, Local0)
            M600 (Arg0, 0x0C, Local0, 0xC179B3FE)
            Divide (Arg2, 0xC179B3FE, Local1, Local0)
            M600 (Arg0, 0x0D, Local0, 0x01)
            Divide (Arg2, AUI6, Local1, Local0)
            M600 (Arg0, 0x0E, Local0, 0xC179B3FE)
            Divide (Arg2, AUI3, Local1, Local0)
            M600 (Arg0, 0x0F, Local0, 0x01)
            If (Y078)
            {
                Divide (Arg2, DerefOf (RefOf (AUI6)), Local1, Local0)
                M600 (Arg0, 0x10, Local0, 0xC179B3FE)
                Divide (Arg2, DerefOf (RefOf (AUI3)), Local1, Local0)
                M600 (Arg0, 0x11, Local0, 0x01)
            }

            Divide (Arg2, DerefOf (PAUI [0x06]), Local1, Local0)
            M600 (Arg0, 0x12, Local0, 0xC179B3FE)
            Divide (Arg2, DerefOf (PAUI [0x03]), Local1, Local0)
            M600 (Arg0, 0x13, Local0, 0x01)
            /* Method returns Integer */

            Divide (Arg2, M601 (0x01, 0x06), Local1, Local0)
            M600 (Arg0, 0x14, Local0, 0xC179B3FE)
            Divide (Arg2, M601 (0x01, 0x03), Local1, Local0)
            M600 (Arg0, 0x15, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Divide (Arg2, DerefOf (M602 (0x01, 0x06, 0x01)), Local1, Local0)
                M600 (Arg0, 0x16, Local0, 0xC179B3FE)
                Divide (Arg2, DerefOf (M602 (0x01, 0x03, 0x01)), Local1, Local0)
                M600 (Arg0, 0x17, Local0, 0x01)
            }

            /* Conversion of the second operand */

            Store ((0x01 / Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0xC179B3FE / Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0x01)
            Store ((AUI6 / Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUI3 / Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0x01)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI6)) / Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUI3)) / Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0x01)
            }

            Store ((DerefOf (PAUI [0x06]) / Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x03]) / Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0x01)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x06) / Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x03) / Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) / Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x03, 0x01)) / Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0x01)
            }

            Divide (0x01, Arg2, Local1, Local0)
            M600 (Arg0, 0x24, Local0, 0x00)
            Divide (0xC179B3FE, Arg2, Local1, Local0)
            M600 (Arg0, 0x25, Local0, 0x01)
            Divide (AUI6, Arg2, Local1, Local0)
            M600 (Arg0, 0x26, Local0, 0x00)
            Divide (AUI3, Arg2, Local1, Local0)
            M600 (Arg0, 0x27, Local0, 0x01)
            If (Y078)
            {
                Divide (DerefOf (RefOf (AUI6)), Arg2, Local1, Local0)
                M600 (Arg0, 0x28, Local0, 0x00)
                Divide (DerefOf (RefOf (AUI3)), Arg2, Local1, Local0)
                M600 (Arg0, 0x29, Local0, 0x01)
            }

            Divide (DerefOf (PAUI [0x06]), Arg2, Local1, Local0)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Divide (DerefOf (PAUI [0x03]), Arg2, Local1, Local0)
            M600 (Arg0, 0x2B, Local0, 0x01)
            /* Method returns Integer */

            Divide (M601 (0x01, 0x06), Arg2, Local1, Local0)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Divide (M601 (0x01, 0x03), Arg2, Local1, Local0)
            M600 (Arg0, 0x2D, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Divide (DerefOf (M602 (0x01, 0x06, 0x01)), Arg2, Local1, Local0)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Divide (DerefOf (M602 (0x01, 0x03, 0x01)), Arg2, Local1, Local0)
                M600 (Arg0, 0x2F, Local0, 0x01)
            }

            /* Conversion of the both operands */

            Store ((Arg1 / Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0x00)
            Store ((Arg2 / Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0x003DD5B7)
            Divide (Arg1, Arg2, Local1, Local0)
            M600 (Arg0, 0x32, Local0, 0x00)
            Divide (Arg2, Arg1, Local1, Local0)
            M600 (Arg0, 0x33, Local0, 0x003DD5B7)
        }

        /* Mod, common 32-bit/64-bit test */

        Method (M00A, 2, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg1 % 0x0322), Local0)
            M600 (Arg0, 0x00, Local0, 0x0321)
            Store ((Arg1 % 0x0320), Local0)
            M600 (Arg0, 0x01, Local0, 0x01)
            Store ((Arg1 % AUIG), Local0)
            M600 (Arg0, 0x02, Local0, 0x0321)
            Store ((Arg1 % AUIH), Local0)
            M600 (Arg0, 0x03, Local0, 0x01)
            If (Y078)
            {
                Store ((Arg1 % DerefOf (RefOf (AUIG))), Local0)
                M600 (Arg0, 0x04, Local0, 0x0321)
                Store ((Arg1 % DerefOf (RefOf (AUIH))), Local0)
                M600 (Arg0, 0x05, Local0, 0x01)
            }

            Store ((Arg1 % DerefOf (PAUI [0x10])), Local0)
            M600 (Arg0, 0x06, Local0, 0x0321)
            Store ((Arg1 % DerefOf (PAUI [0x11])), Local0)
            M600 (Arg0, 0x07, Local0, 0x01)
            /* Method returns Integer */

            Store ((Arg1 % M601 (0x01, 0x10)), Local0)
            M600 (Arg0, 0x08, Local0, 0x0321)
            Store ((Arg1 % M601 (0x01, 0x11)), Local0)
            M600 (Arg0, 0x09, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg1 % DerefOf (M602 (0x01, 0x10, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0x0321)
                Store ((Arg1 % DerefOf (M602 (0x01, 0x11, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x01)
            }

            Local0 = (Arg1 % 0x0322)
            M600 (Arg0, 0x0C, Local0, 0x0321)
            Local0 = (Arg1 % 0x0320)
            M600 (Arg0, 0x0D, Local0, 0x01)
            Local0 = (Arg1 % AUIG) /* \AUIG */
            M600 (Arg0, 0x0E, Local0, 0x0321)
            Local0 = (Arg1 % AUIH) /* \AUIH */
            M600 (Arg0, 0x0F, Local0, 0x01)
            If (Y078)
            {
                Local0 = (Arg1 % DerefOf (RefOf (AUIG)))
                M600 (Arg0, 0x10, Local0, 0x0321)
                Local0 = (Arg1 % DerefOf (RefOf (AUIH)))
                M600 (Arg0, 0x11, Local0, 0x01)
            }

            Local0 = (Arg1 % DerefOf (PAUI [0x10]))
            M600 (Arg0, 0x12, Local0, 0x0321)
            Local0 = (Arg1 % DerefOf (PAUI [0x11]))
            M600 (Arg0, 0x13, Local0, 0x01)
            /* Method returns Integer */

            Local0 = (Arg1 % M601 (0x01, 0x10))
            M600 (Arg0, 0x14, Local0, 0x0321)
            Local0 = (Arg1 % M601 (0x01, 0x11))
            M600 (Arg0, 0x15, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg1 % DerefOf (M602 (0x01, 0x10, 0x01)))
                M600 (Arg0, 0x16, Local0, 0x0321)
                Local0 = (Arg1 % DerefOf (M602 (0x01, 0x11, 0x01)))
                M600 (Arg0, 0x17, Local0, 0x01)
            }

            /* Conversion of the second operand */

            Store ((0x0322 % Arg1), Local0)
            M600 (Arg0, 0x18, Local0, 0x01)
            Store ((0x0320 % Arg1), Local0)
            M600 (Arg0, 0x19, Local0, 0x0320)
            Store ((AUIG % Arg1), Local0)
            M600 (Arg0, 0x1A, Local0, 0x01)
            Store ((AUIH % Arg1), Local0)
            M600 (Arg0, 0x1B, Local0, 0x0320)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUIG)) % Arg1), Local0)
                M600 (Arg0, 0x1C, Local0, 0x01)
                Store ((DerefOf (RefOf (AUIH)) % Arg1), Local0)
                M600 (Arg0, 0x1D, Local0, 0x0320)
            }

            Store ((DerefOf (PAUI [0x10]) % Arg1), Local0)
            M600 (Arg0, 0x1E, Local0, 0x01)
            Store ((DerefOf (PAUI [0x11]) % Arg1), Local0)
            M600 (Arg0, 0x1F, Local0, 0x0320)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x10) % Arg1), Local0)
            M600 (Arg0, 0x20, Local0, 0x01)
            Store ((M601 (0x01, 0x11) % Arg1), Local0)
            M600 (Arg0, 0x21, Local0, 0x0320)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x10, 0x01)) % Arg1), Local0)
                M600 (Arg0, 0x22, Local0, 0x01)
                Store ((DerefOf (M602 (0x01, 0x11, 0x01)) % Arg1), Local0)
                M600 (Arg0, 0x23, Local0, 0x0320)
            }

            Local0 = (0x0322 % Arg1)
            M600 (Arg0, 0x24, Local0, 0x01)
            Local0 = (0x0320 % Arg1)
            M600 (Arg0, 0x25, Local0, 0x0320)
            Local0 = (AUIG % Arg1)
            M600 (Arg0, 0x26, Local0, 0x01)
            Local0 = (AUIH % Arg1)
            M600 (Arg0, 0x27, Local0, 0x0320)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUIG)) % Arg1)
                M600 (Arg0, 0x28, Local0, 0x01)
                Local0 = (DerefOf (RefOf (AUIH)) % Arg1)
                M600 (Arg0, 0x29, Local0, 0x0320)
            }

            Local0 = (DerefOf (PAUI [0x10]) % Arg1)
            M600 (Arg0, 0x2A, Local0, 0x01)
            Local0 = (DerefOf (PAUI [0x11]) % Arg1)
            M600 (Arg0, 0x2B, Local0, 0x0320)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x10) % Arg1)
            M600 (Arg0, 0x2C, Local0, 0x01)
            Local0 = (M601 (0x01, 0x11) % Arg1)
            M600 (Arg0, 0x2D, Local0, 0x0320)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x10, 0x01)) % Arg1)
                M600 (Arg0, 0x2E, Local0, 0x01)
                Local0 = (DerefOf (M602 (0x01, 0x11, 0x01)) % Arg1)
                M600 (Arg0, 0x2F, Local0, 0x0320)
            }
        }

        /* Mod, 64-bit */

        Method (M00B, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 % 0xFE7CB391D650A285), Local0)
            M600 (Arg0, 0x00, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 % 0xFE7CB391D650A283), Local0)
            M600 (Arg0, 0x01, Local0, 0x01)
            Store ((Arg2 % AUID), Local0)
            M600 (Arg0, 0x02, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 % AUIF), Local0)
            M600 (Arg0, 0x03, Local0, 0x01)
            If (Y078)
            {
                Store ((Arg2 % DerefOf (RefOf (AUID))), Local0)
                M600 (Arg0, 0x04, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 % DerefOf (RefOf (AUIF))), Local0)
                M600 (Arg0, 0x05, Local0, 0x01)
            }

            Store ((Arg2 % DerefOf (PAUI [0x0D])), Local0)
            M600 (Arg0, 0x0D, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 % DerefOf (PAUI [0x0F])), Local0)
            M600 (Arg0, 0x07, Local0, 0x01)
            /* Method returns Integer */

            Store ((Arg2 % M601 (0x01, 0x0D)), Local0)
            M600 (Arg0, 0x08, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 % M601 (0x01, 0x0F)), Local0)
            M600 (Arg0, 0x09, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 % DerefOf (M602 (0x01, 0x0D, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 % DerefOf (M602 (0x01, 0x0F, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x01)
            }

            Local0 = (Arg2 % 0xFE7CB391D650A285)
            M600 (Arg0, 0x0C, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 % 0xFE7CB391D650A283)
            M600 (Arg0, 0x0D, Local0, 0x01)
            Local0 = (Arg2 % AUID) /* \AUID */
            M600 (Arg0, 0x0E, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 % AUIF) /* \AUIF */
            M600 (Arg0, 0x0F, Local0, 0x01)
            If (Y078)
            {
                Local0 = (Arg2 % DerefOf (RefOf (AUID)))
                M600 (Arg0, 0x10, Local0, 0xFE7CB391D650A284)
                Local0 = (Arg2 % DerefOf (RefOf (AUIF)))
                M600 (Arg0, 0x11, Local0, 0x01)
            }

            Local0 = (Arg2 % DerefOf (PAUI [0x0D]))
            M600 (Arg0, 0x12, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 % DerefOf (PAUI [0x0F]))
            M600 (Arg0, 0x13, Local0, 0x01)
            /* Method returns Integer */

            Local0 = (Arg2 % M601 (0x01, 0x0D))
            M600 (Arg0, 0x14, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 % M601 (0x01, 0x0F))
            M600 (Arg0, 0x15, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 % DerefOf (M602 (0x01, 0x0D, 0x01)))
                M600 (Arg0, 0x16, Local0, 0xFE7CB391D650A284)
                Local0 = (Arg2 % DerefOf (M602 (0x01, 0x0F, 0x01)))
                M600 (Arg0, 0x17, Local0, 0x01)
            }

            /* Conversion of the second operand */

            Store ((0xFE7CB391D650A285 % Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0x01)
            Store ((0xFE7CB391D650A283 % Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0xFE7CB391D650A283)
            Store ((AUID % Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0x01)
            Store ((AUIF % Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0xFE7CB391D650A283)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUID)) % Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0x01)
                Store ((DerefOf (RefOf (AUIF)) % Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0xFE7CB391D650A283)
            }

            Store ((DerefOf (PAUI [0x0D]) % Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0x01)
            Store ((DerefOf (PAUI [0x0F]) % Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0xFE7CB391D650A283)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x0D) % Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0x01)
            Store ((M601 (0x01, 0x0F) % Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0xFE7CB391D650A283)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x0D, 0x01)) % Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0x01)
                Store ((DerefOf (M602 (0x01, 0x0F, 0x01)) % Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0xFE7CB391D650A283)
            }

            Local0 = (0xFE7CB391D650A285 % Arg2)
            M600 (Arg0, 0x24, Local0, 0x01)
            Local0 = (0xFE7CB391D650A283 % Arg2)
            M600 (Arg0, 0x25, Local0, 0xFE7CB391D650A283)
            Local0 = (AUID % Arg2)
            M600 (Arg0, 0x26, Local0, 0x01)
            Local0 = (AUIF % Arg2)
            M600 (Arg0, 0x27, Local0, 0xFE7CB391D650A283)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUID)) % Arg2)
                M600 (Arg0, 0x28, Local0, 0x01)
                Local0 = (DerefOf (RefOf (AUIF)) % Arg2)
                M600 (Arg0, 0x29, Local0, 0xFE7CB391D650A283)
            }

            Local0 = (DerefOf (PAUI [0x0D]) % Arg2)
            M600 (Arg0, 0x2A, Local0, 0x01)
            Local0 = (DerefOf (PAUI [0x0F]) % Arg2)
            M600 (Arg0, 0x2B, Local0, 0xFE7CB391D650A283)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x0D) % Arg2)
            M600 (Arg0, 0x2C, Local0, 0x01)
            Local0 = (M601 (0x01, 0x0F) % Arg2)
            M600 (Arg0, 0x2D, Local0, 0xFE7CB391D650A283)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x0D, 0x01)) % Arg2)
                M600 (Arg0, 0x2E, Local0, 0x01)
                Local0 = (DerefOf (M602 (0x01, 0x0F, 0x01)) % Arg2)
                M600 (Arg0, 0x2F, Local0, 0xFE7CB391D650A283)
            }

            /* Conversion of the both operands */

            Store ((Arg1 % Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0x0321)
            Store ((Arg2 % Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0x02FD)
            Local0 = (Arg1 % Arg2)
            M600 (Arg0, 0x32, Local0, 0x0321)
            Local0 = (Arg2 % Arg1)
            M600 (Arg0, 0x33, Local0, 0x02FD)
        }

        /* Mod, 32-bit */

        Method (M00C, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 % 0xC179B3FF), Local0)
            M600 (Arg0, 0x00, Local0, 0xC179B3FE)
            Store ((Arg2 % 0xC179B3FD), Local0)
            M600 (Arg0, 0x01, Local0, 0x01)
            Store ((Arg2 % AUIC), Local0)
            M600 (Arg0, 0x02, Local0, 0xC179B3FE)
            Store ((Arg2 % AUIE), Local0)
            M600 (Arg0, 0x0E, Local0, 0x01)
            If (Y078)
            {
                Store ((Arg2 % DerefOf (RefOf (AUIC))), Local0)
                M600 (Arg0, 0x04, Local0, 0xC179B3FE)
                Store ((Arg2 % DerefOf (RefOf (AUIE))), Local0)
                M600 (Arg0, 0x05, Local0, 0x01)
            }

            Store ((Arg2 % DerefOf (PAUI [0x0C])), Local0)
            M600 (Arg0, 0x0C, Local0, 0xC179B3FE)
            Store ((Arg2 % DerefOf (PAUI [0x0E])), Local0)
            M600 (Arg0, 0x07, Local0, 0x01)
            /* Method returns Integer */

            Store ((Arg2 % M601 (0x01, 0x0C)), Local0)
            M600 (Arg0, 0x08, Local0, 0xC179B3FE)
            Store ((Arg2 % M601 (0x01, 0x0E)), Local0)
            M600 (Arg0, 0x09, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 % DerefOf (M602 (0x01, 0x0C, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xC179B3FE)
                Store ((Arg2 % DerefOf (M602 (0x01, 0x0E, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x01)
            }

            Local0 = (Arg2 % 0xC179B3FF)
            M600 (Arg0, 0x0C, Local0, 0xC179B3FE)
            Local0 = (Arg2 % 0xC179B3FD)
            M600 (Arg0, 0x0D, Local0, 0x01)
            Local0 = (Arg2 % AUIC) /* \AUIC */
            M600 (Arg0, 0x0E, Local0, 0xC179B3FE)
            Local0 = (Arg2 % AUIE) /* \AUIE */
            M600 (Arg0, 0x0F, Local0, 0x01)
            If (Y078)
            {
                Local0 = (Arg2 % DerefOf (RefOf (AUIC)))
                M600 (Arg0, 0x10, Local0, 0xC179B3FE)
                Local0 = (Arg2 % DerefOf (RefOf (AUIE)))
                M600 (Arg0, 0x11, Local0, 0x01)
            }

            Local0 = (Arg2 % DerefOf (PAUI [0x0C]))
            M600 (Arg0, 0x12, Local0, 0xC179B3FE)
            Local0 = (Arg2 % DerefOf (PAUI [0x0E]))
            M600 (Arg0, 0x13, Local0, 0x01)
            /* Method returns Integer */

            Local0 = (Arg2 % M601 (0x01, 0x0C))
            M600 (Arg0, 0x14, Local0, 0xC179B3FE)
            Local0 = (Arg2 % M601 (0x01, 0x0E))
            M600 (Arg0, 0x15, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 % DerefOf (M602 (0x01, 0x0C, 0x01)))
                M600 (Arg0, 0x16, Local0, 0xC179B3FE)
                Local0 = (Arg2 % DerefOf (M602 (0x01, 0x0E, 0x01)))
                M600 (Arg0, 0x17, Local0, 0x01)
            }

            /* Conversion of the second operand */

            Store ((0xC179B3FF % Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0x01)
            Store ((0xC179B3FD % Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0xC179B3FD)
            Store ((AUIC % Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0x01)
            Store ((AUIE % Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0xC179B3FD)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUIC)) % Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0x01)
                Store ((DerefOf (RefOf (AUIE)) % Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0xC179B3FD)
            }

            Store ((DerefOf (PAUI [0x0C]) % Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0x01)
            Store ((DerefOf (PAUI [0x0E]) % Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0xC179B3FD)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x0C) % Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0x01)
            Store ((M601 (0x01, 0x0E) % Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0xC179B3FD)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x0C, 0x01)) % Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0x01)
                Store ((DerefOf (M602 (0x01, 0x0E, 0x01)) % Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0xC179B3FD)
            }

            Local0 = (0xC179B3FF % Arg2)
            M600 (Arg0, 0x24, Local0, 0x01)
            Local0 = (0xC179B3FD % Arg2)
            M600 (Arg0, 0x25, Local0, 0xC179B3FD)
            Local0 = (AUIC % Arg2)
            M600 (Arg0, 0x26, Local0, 0x01)
            Local0 = (AUIE % Arg2)
            M600 (Arg0, 0x27, Local0, 0xC179B3FD)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUIC)) % Arg2)
                M600 (Arg0, 0x28, Local0, 0x01)
                Local0 = (DerefOf (RefOf (AUIE)) % Arg2)
                M600 (Arg0, 0x29, Local0, 0xC179B3FD)
            }

            Local0 = (DerefOf (PAUI [0x0C]) % Arg2)
            M600 (Arg0, 0x2A, Local0, 0x01)
            Local0 = (DerefOf (PAUI [0x0E]) % Arg2)
            M600 (Arg0, 0x2B, Local0, 0xC179B3FD)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x0C) % Arg2)
            M600 (Arg0, 0x2C, Local0, 0x01)
            Local0 = (M601 (0x01, 0x0E) % Arg2)
            M600 (Arg0, 0x2D, Local0, 0xC179B3FD)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x0C, 0x01)) % Arg2)
                M600 (Arg0, 0x2E, Local0, 0x01)
                Local0 = (DerefOf (M602 (0x01, 0x0E, 0x01)) % Arg2)
                M600 (Arg0, 0x2F, Local0, 0xC179B3FD)
            }

            /* Conversion of the both operands */

            Store ((Arg1 % Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0x0321)
            Store ((Arg2 % Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0x0267)
            Local0 = (Arg1 % Arg2)
            M600 (Arg0, 0x32, Local0, 0x0321)
            Local0 = (Arg2 % Arg1)
            M600 (Arg0, 0x33, Local0, 0x0267)
        }

        /* Multiply, common 32-bit/64-bit test */

        Method (M00D, 2, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg1 * 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0x00)
            Store ((Arg1 * 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0x0321)
            Store ((Arg1 * AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0x00)
            Store ((Arg1 * AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0x0321)
            If (Y078)
            {
                Store ((Arg1 * DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0x00)
                Store ((Arg1 * DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0x0321)
            }

            Store ((Arg1 * DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0x00)
            Store ((Arg1 * DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0x0321)
            /* Method returns Integer */

            Store ((Arg1 * M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0x00)
            Store ((Arg1 * M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0x0321)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg1 * DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0x00)
                Store ((Arg1 * DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x0321)
            }

            Local0 = (Arg1 * 0x00)
            M600 (Arg0, 0x0C, Local0, 0x00)
            Local0 = (Arg1 * 0x01)
            M600 (Arg0, 0x0D, Local0, 0x0321)
            Local0 = (Arg1 * AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0x00)
            Local0 = (Arg1 * AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0x0321)
            If (Y078)
            {
                Local0 = (Arg1 * DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0x00)
                Local0 = (Arg1 * DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0x0321)
            }

            Local0 = (Arg1 * DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0x00)
            Local0 = (Arg1 * DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0x0321)
            /* Method returns Integer */

            Local0 = (Arg1 * M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0x00)
            Local0 = (Arg1 * M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0x0321)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg1 * DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0x00)
                Local0 = (Arg1 * DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0x0321)
            }

            /* Conversion of the second operand */

            Store ((0x00 * Arg1), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0x01 * Arg1), Local0)
            M600 (Arg0, 0x19, Local0, 0x0321)
            Store ((AUI5 * Arg1), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUI6 * Arg1), Local0)
            M600 (Arg0, 0x1B, Local0, 0x0321)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) * Arg1), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUI6)) * Arg1), Local0)
                M600 (Arg0, 0x1D, Local0, 0x0321)
            }

            Store ((DerefOf (PAUI [0x05]) * Arg1), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x06]) * Arg1), Local0)
            M600 (Arg0, 0x1F, Local0, 0x0321)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) * Arg1), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x06) * Arg1), Local0)
            M600 (Arg0, 0x21, Local0, 0x0321)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) * Arg1), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) * Arg1), Local0)
                M600 (Arg0, 0x23, Local0, 0x0321)
            }

            Local0 = (0x00 * Arg1)
            M600 (Arg0, 0x24, Local0, 0x00)
            Local0 = (0x01 * Arg1)
            M600 (Arg0, 0x25, Local0, 0x0321)
            Local0 = (AUI5 * Arg1)
            M600 (Arg0, 0x26, Local0, 0x00)
            Local0 = (AUI6 * Arg1)
            M600 (Arg0, 0x27, Local0, 0x0321)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) * Arg1)
                M600 (Arg0, 0x28, Local0, 0x00)
                Local0 = (DerefOf (RefOf (AUI6)) * Arg1)
                M600 (Arg0, 0x29, Local0, 0x0321)
            }

            Local0 = (DerefOf (PAUI [0x05]) * Arg1)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Local0 = (DerefOf (PAUI [0x06]) * Arg1)
            M600 (Arg0, 0x2B, Local0, 0x0321)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) * Arg1)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Local0 = (M601 (0x01, 0x06) * Arg1)
            M600 (Arg0, 0x2D, Local0, 0x0321)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) * Arg1)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) * Arg1)
                M600 (Arg0, 0x2F, Local0, 0x0321)
            }
        }

        /* Multiply, 64-bit */

        Method (M00E, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 * 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0x00)
            Store ((Arg2 * 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 * AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0x00)
            Store ((Arg2 * AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0xFE7CB391D650A284)
            If (Y078)
            {
                Store ((Arg2 * DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0x00)
                Store ((Arg2 * DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0xFE7CB391D650A284)
            }

            Store ((Arg2 * DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0x00)
            Store ((Arg2 * DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0xFE7CB391D650A284)
            /* Method returns Integer */

            Store ((Arg2 * M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0x00)
            Store ((Arg2 * M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0xFE7CB391D650A284)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 * DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0x00)
                Store ((Arg2 * DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0xFE7CB391D650A284)
            }

            Local0 = (Arg2 * 0x00)
            M600 (Arg0, 0x0C, Local0, 0x00)
            Local0 = (Arg2 * 0x01)
            M600 (Arg0, 0x0D, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 * AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0x00)
            Local0 = (Arg2 * AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0xFE7CB391D650A284)
            If (Y078)
            {
                Local0 = (Arg2 * DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0x00)
                Local0 = (Arg2 * DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0xFE7CB391D650A284)
            }

            Local0 = (Arg2 * DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0x00)
            Local0 = (Arg2 * DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0xFE7CB391D650A284)
            /* Method returns Integer */

            Local0 = (Arg2 * M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0x00)
            Local0 = (Arg2 * M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0xFE7CB391D650A284)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 * DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0x00)
                Local0 = (Arg2 * DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0xFE7CB391D650A284)
            }

            /* Conversion of the second operand */

            Store ((0x00 * Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0x01 * Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0xFE7CB391D650A284)
            Store ((AUI5 * Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUI6 * Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0xFE7CB391D650A284)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) * Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUI6)) * Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0xFE7CB391D650A284)
            }

            Store ((DerefOf (PAUI [0x05]) * Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x06]) * Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0xFE7CB391D650A284)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) * Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x06) * Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0xFE7CB391D650A284)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) * Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) * Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0xFE7CB391D650A284)
            }

            Local0 = (0x00 * Arg2)
            M600 (Arg0, 0x24, Local0, 0x00)
            Local0 = (0x01 * Arg2)
            M600 (Arg0, 0x25, Local0, 0xFE7CB391D650A284)
            Local0 = (AUI5 * Arg2)
            M600 (Arg0, 0x26, Local0, 0x00)
            Local0 = (AUI6 * Arg2)
            M600 (Arg0, 0x27, Local0, 0xFE7CB391D650A284)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) * Arg2)
                M600 (Arg0, 0x28, Local0, 0x00)
                Local0 = (DerefOf (RefOf (AUI6)) * Arg2)
                M600 (Arg0, 0x29, Local0, 0xFE7CB391D650A284)
            }

            Local0 = (DerefOf (PAUI [0x05]) * Arg2)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Local0 = (DerefOf (PAUI [0x06]) * Arg2)
            M600 (Arg0, 0x2B, Local0, 0xFE7CB391D650A284)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) * Arg2)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Local0 = (M601 (0x01, 0x06) * Arg2)
            M600 (Arg0, 0x2D, Local0, 0xFE7CB391D650A284)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) * Arg2)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) * Arg2)
                M600 (Arg0, 0x2F, Local0, 0xFE7CB391D650A284)
            }

            /* Conversion of the both operands */

            Store ((Arg1 * Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0x442DDB4F924C7F04)
            Store ((Arg2 * Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0x442DDB4F924C7F04)
            Local0 = (Arg1 * Arg2)
            M600 (Arg0, 0x32, Local0, 0x442DDB4F924C7F04)
            Local0 = (Arg2 * Arg1)
            M600 (Arg0, 0x33, Local0, 0x442DDB4F924C7F04)
        }

        /* Multiply, 32-bit */

        Method (M00F, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 * 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0x00)
            Store ((Arg2 * 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0xC179B3FE)
            Store ((Arg2 * AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0x00)
            Store ((Arg2 * AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0xC179B3FE)
            If (Y078)
            {
                Store ((Arg2 * DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0x00)
                Store ((Arg2 * DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0xC179B3FE)
            }

            Store ((Arg2 * DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0x00)
            Store ((Arg2 * DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0xC179B3FE)
            /* Method returns Integer */

            Store ((Arg2 * M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0x00)
            Store ((Arg2 * M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0xC179B3FE)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 * DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0x00)
                Store ((Arg2 * DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0xC179B3FE)
            }

            Local0 = (Arg2 * 0x00)
            M600 (Arg0, 0x0C, Local0, 0x00)
            Local0 = (Arg2 * 0x01)
            M600 (Arg0, 0x0D, Local0, 0xC179B3FE)
            Local0 = (Arg2 * AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0x00)
            Local0 = (Arg2 * AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0xC179B3FE)
            If (Y078)
            {
                Local0 = (Arg2 * DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0x00)
                Local0 = (Arg2 * DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0xC179B3FE)
            }

            Local0 = (Arg2 * DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0x00)
            Local0 = (Arg2 * DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0xC179B3FE)
            /* Method returns Integer */

            Local0 = (Arg2 * M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0x00)
            Local0 = (Arg2 * M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0xC179B3FE)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 * DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0x00)
                Local0 = (Arg2 * DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0xC179B3FE)
            }

            /* Conversion of the second operand */

            Store ((0x00 * Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0x01 * Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0xC179B3FE)
            Store ((AUI5 * Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUI6 * Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0xC179B3FE)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) * Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUI6)) * Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0xC179B3FE)
            }

            Store ((DerefOf (PAUI [0x05]) * Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x06]) * Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0xC179B3FE)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) * Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x06) * Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0xC179B3FE)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) * Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) * Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0xC179B3FE)
            }

            Local0 = (0x00 * Arg2)
            M600 (Arg0, 0x24, Local0, 0x00)
            Local0 = (0x01 * Arg2)
            M600 (Arg0, 0x25, Local0, 0xC179B3FE)
            Local0 = (AUI5 * Arg2)
            M600 (Arg0, 0x26, Local0, 0x00)
            Local0 = (AUI6 * Arg2)
            M600 (Arg0, 0x27, Local0, 0xC179B3FE)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) * Arg2)
                M600 (Arg0, 0x28, Local0, 0x00)
                Local0 = (DerefOf (RefOf (AUI6)) * Arg2)
                M600 (Arg0, 0x29, Local0, 0xC179B3FE)
            }

            Local0 = (DerefOf (PAUI [0x05]) * Arg2)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Local0 = (DerefOf (PAUI [0x06]) * Arg2)
            M600 (Arg0, 0x2B, Local0, 0xC179B3FE)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) * Arg2)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Local0 = (M601 (0x01, 0x06) * Arg2)
            M600 (Arg0, 0x2D, Local0, 0xC179B3FE)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) * Arg2)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) * Arg2)
                M600 (Arg0, 0x2F, Local0, 0xC179B3FE)
            }

            /* Conversion of the both operands */

            Store ((Arg1 * Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0x5DCC2DBE)
            Store ((Arg2 * Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0x5DCC2DBE)
            Local0 = (Arg1 * Arg2)
            M600 (Arg0, 0x32, Local0, 0x5DCC2DBE)
            Local0 = (Arg2 * Arg1)
            M600 (Arg0, 0x33, Local0, 0x5DCC2DBE)
        }

        /* NAnd, common 32-bit/64-bit test */

        Method (M010, 2, NotSerialized)
        {
            /* Conversion of the first operand */

            Local0 = NAnd (Arg1, 0x00)
            M600 (Arg0, 0x00, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (Arg1, 0xFFFFFFFFFFFFFFFF)
            M600 (Arg0, 0x01, Local0, 0xFFFFFFFFFFFFFCDE)
            Local0 = NAnd (Arg1, AUI5)
            M600 (Arg0, 0x02, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (Arg1, AUIJ)
            M600 (Arg0, 0x03, Local0, 0xFFFFFFFFFFFFFCDE)
            If (Y078)
            {
                Local0 = NAnd (Arg1, DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x04, Local0, 0xFFFFFFFFFFFFFFFF)
                Local0 = NAnd (Arg1, DerefOf (RefOf (AUIJ)))
                M600 (Arg0, 0x05, Local0, 0xFFFFFFFFFFFFFCDE)
            }

            Local0 = NAnd (Arg1, DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x06, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (Arg1, DerefOf (PAUI [0x13]))
            M600 (Arg0, 0x07, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Integer */

            Local0 = NAnd (Arg1, M601 (0x01, 0x05))
            M600 (Arg0, 0x08, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (Arg1, M601 (0x01, 0x13))
            M600 (Arg0, 0x09, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = NAnd (Arg1, DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x0A, Local0, 0xFFFFFFFFFFFFFFFF)
                Local0 = NAnd (Arg1, DerefOf (M602 (0x01, 0x13, 0x01)))
                M600 (Arg0, 0x0B, Local0, 0xFFFFFFFFFFFFFCDE)
            }

            NAnd (Arg1, 0x00, Local0)
            M600 (Arg0, 0x0C, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (Arg1, 0xFFFFFFFFFFFFFFFF, Local0)
            M600 (Arg0, 0x0D, Local0, 0xFFFFFFFFFFFFFCDE)
            NAnd (Arg1, AUI5, Local0)
            M600 (Arg0, 0x0E, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (Arg1, AUIJ, Local0)
            M600 (Arg0, 0x0F, Local0, 0xFFFFFFFFFFFFFCDE)
            If (Y078)
            {
                NAnd (Arg1, DerefOf (RefOf (AUI5)), Local0)
                M600 (Arg0, 0x10, Local0, 0xFFFFFFFFFFFFFFFF)
                NAnd (Arg1, DerefOf (RefOf (AUIJ)), Local0)
                M600 (Arg0, 0x11, Local0, 0xFFFFFFFFFFFFFCDE)
            }

            NAnd (Arg1, DerefOf (PAUI [0x05]), Local0)
            M600 (Arg0, 0x12, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (Arg1, DerefOf (PAUI [0x13]), Local0)
            M600 (Arg0, 0x13, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Integer */

            NAnd (Arg1, M601 (0x01, 0x05), Local0)
            M600 (Arg0, 0x14, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (Arg1, M601 (0x01, 0x13), Local0)
            M600 (Arg0, 0x15, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                NAnd (Arg1, DerefOf (M602 (0x01, 0x05, 0x01)), Local0)
                M600 (Arg0, 0x16, Local0, 0xFFFFFFFFFFFFFFFF)
                NAnd (Arg1, DerefOf (M602 (0x01, 0x13, 0x01)), Local0)
                M600 (Arg0, 0x17, Local0, 0xFFFFFFFFFFFFFCDE)
            }

            /* Conversion of the second operand */

            Local0 = NAnd (0x00, Arg1)
            M600 (Arg0, 0x18, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (0xFFFFFFFFFFFFFFFF, Arg1)
            M600 (Arg0, 0x19, Local0, 0xFFFFFFFFFFFFFCDE)
            Local0 = NAnd (AUI5, Arg1)
            M600 (Arg0, 0x1A, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (AUIJ, Arg1)
            M600 (Arg0, 0x1B, Local0, 0xFFFFFFFFFFFFFCDE)
            If (Y078)
            {
                Local0 = NAnd (DerefOf (RefOf (AUI5)), Arg1)
                M600 (Arg0, 0x1C, Local0, 0xFFFFFFFFFFFFFFFF)
                Local0 = NAnd (DerefOf (RefOf (AUIJ)), Arg1)
                M600 (Arg0, 0x1D, Local0, 0xFFFFFFFFFFFFFCDE)
            }

            Local0 = NAnd (DerefOf (PAUI [0x05]), Arg1)
            M600 (Arg0, 0x1E, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (DerefOf (PAUI [0x13]), Arg1)
            M600 (Arg0, 0x1F, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Integer */

            Local0 = NAnd (M601 (0x01, 0x05), Arg1)
            M600 (Arg0, 0x20, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (M601 (0x01, 0x13), Arg1)
            M600 (Arg0, 0x21, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = NAnd (DerefOf (M602 (0x01, 0x05, 0x01)), Arg1)
                M600 (Arg0, 0x22, Local0, 0xFFFFFFFFFFFFFFFF)
                Local0 = NAnd (DerefOf (M602 (0x01, 0x13, 0x01)), Arg1)
                M600 (Arg0, 0x23, Local0, 0xFFFFFFFFFFFFFCDE)
            }

            NAnd (0x00, Arg1, Local0)
            M600 (Arg0, 0x24, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (0xFFFFFFFFFFFFFFFF, Arg1, Local0)
            M600 (Arg0, 0x25, Local0, 0xFFFFFFFFFFFFFCDE)
            NAnd (AUI5, Arg1, Local0)
            M600 (Arg0, 0x26, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (AUIJ, Arg1, Local0)
            M600 (Arg0, 0x27, Local0, 0xFFFFFFFFFFFFFCDE)
            If (Y078)
            {
                NAnd (DerefOf (RefOf (AUI5)), Arg1, Local0)
                M600 (Arg0, 0x28, Local0, 0xFFFFFFFFFFFFFFFF)
                NAnd (DerefOf (RefOf (AUIJ)), Arg1, Local0)
                M600 (Arg0, 0x29, Local0, 0xFFFFFFFFFFFFFCDE)
            }

            NAnd (DerefOf (PAUI [0x05]), Arg1, Local0)
            M600 (Arg0, 0x2A, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (DerefOf (PAUI [0x13]), Arg1, Local0)
            M600 (Arg0, 0x2B, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Integer */

            NAnd (M601 (0x01, 0x05), Arg1, Local0)
            M600 (Arg0, 0x2C, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (M601 (0x01, 0x13), Arg1, Local0)
            M600 (Arg0, 0x2D, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                NAnd (DerefOf (M602 (0x01, 0x05, 0x01)), Arg1, Local0)
                M600 (Arg0, 0x2E, Local0, 0xFFFFFFFFFFFFFFFF)
                NAnd (DerefOf (M602 (0x01, 0x13, 0x01)), Arg1, Local0)
                M600 (Arg0, 0x2F, Local0, 0xFFFFFFFFFFFFFCDE)
            }
        }

        /* NAnd, 64-bit */

        Method (M011, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Local0 = NAnd (Arg2, 0x00)
            M600 (Arg0, 0x00, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (Arg2, 0xFFFFFFFFFFFFFFFF)
            M600 (Arg0, 0x01, Local0, 0x01834C6E29AF5D7B)
            Local0 = NAnd (Arg2, AUI5)
            M600 (Arg0, 0x02, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (Arg2, AUIJ)
            M600 (Arg0, 0x03, Local0, 0x01834C6E29AF5D7B)
            If (Y078)
            {
                Local0 = NAnd (Arg2, DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x04, Local0, 0xFFFFFFFFFFFFFFFF)
                Local0 = NAnd (Arg2, DerefOf (RefOf (AUIJ)))
                M600 (Arg0, 0x05, Local0, 0x01834C6E29AF5D7B)
            }

            Local0 = NAnd (Arg2, DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x06, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (Arg2, DerefOf (PAUI [0x13]))
            M600 (Arg0, 0x07, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Integer */

            Local0 = NAnd (Arg2, M601 (0x01, 0x05))
            M600 (Arg0, 0x08, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (Arg2, M601 (0x01, 0x13))
            M600 (Arg0, 0x09, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = NAnd (Arg2, DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x0A, Local0, 0xFFFFFFFFFFFFFFFF)
                Local0 = NAnd (Arg2, DerefOf (M602 (0x01, 0x13, 0x01)))
                M600 (Arg0, 0x0B, Local0, 0x01834C6E29AF5D7B)
            }

            NAnd (Arg2, 0x00, Local0)
            M600 (Arg0, 0x0C, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (Arg2, 0xFFFFFFFFFFFFFFFF, Local0)
            M600 (Arg0, 0x0D, Local0, 0x01834C6E29AF5D7B)
            NAnd (Arg2, AUI5, Local0)
            M600 (Arg0, 0x0E, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (Arg2, AUIJ, Local0)
            M600 (Arg0, 0x0F, Local0, 0x01834C6E29AF5D7B)
            If (Y078)
            {
                NAnd (Arg2, DerefOf (RefOf (AUI5)), Local0)
                M600 (Arg0, 0x10, Local0, 0xFFFFFFFFFFFFFFFF)
                NAnd (Arg2, DerefOf (RefOf (AUIJ)), Local0)
                M600 (Arg0, 0x11, Local0, 0x01834C6E29AF5D7B)
            }

            NAnd (Arg2, DerefOf (PAUI [0x05]), Local0)
            M600 (Arg0, 0x12, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (Arg2, DerefOf (PAUI [0x13]), Local0)
            M600 (Arg0, 0x13, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Integer */

            NAnd (Arg2, M601 (0x01, 0x05), Local0)
            M600 (Arg0, 0x14, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (Arg2, M601 (0x01, 0x13), Local0)
            M600 (Arg0, 0x15, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                NAnd (Arg2, DerefOf (M602 (0x01, 0x05, 0x01)), Local0)
                M600 (Arg0, 0x16, Local0, 0xFFFFFFFFFFFFFFFF)
                NAnd (Arg2, DerefOf (M602 (0x01, 0x13, 0x01)), Local0)
                M600 (Arg0, 0x17, Local0, 0x01834C6E29AF5D7B)
            }

            /* Conversion of the second operand */

            Local0 = NAnd (0x00, Arg2)
            M600 (Arg0, 0x18, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (0xFFFFFFFFFFFFFFFF, Arg2)
            M600 (Arg0, 0x19, Local0, 0x01834C6E29AF5D7B)
            Local0 = NAnd (AUI5, Arg2)
            M600 (Arg0, 0x1A, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (AUIJ, Arg2)
            M600 (Arg0, 0x1B, Local0, 0x01834C6E29AF5D7B)
            If (Y078)
            {
                Local0 = NAnd (DerefOf (RefOf (AUI5)), Arg2)
                M600 (Arg0, 0x1C, Local0, 0xFFFFFFFFFFFFFFFF)
                Local0 = NAnd (DerefOf (RefOf (AUIJ)), Arg2)
                M600 (Arg0, 0x1D, Local0, 0x01834C6E29AF5D7B)
            }

            Local0 = NAnd (DerefOf (PAUI [0x05]), Arg2)
            M600 (Arg0, 0x1E, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (DerefOf (PAUI [0x13]), Arg2)
            M600 (Arg0, 0x1F, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Integer */

            Local0 = NAnd (M601 (0x01, 0x05), Arg2)
            M600 (Arg0, 0x20, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (M601 (0x01, 0x13), Arg2)
            M600 (Arg0, 0x21, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = NAnd (DerefOf (M602 (0x01, 0x05, 0x01)), Arg2)
                M600 (Arg0, 0x22, Local0, 0xFFFFFFFFFFFFFFFF)
                Local0 = NAnd (DerefOf (M602 (0x01, 0x13, 0x01)), Arg2)
                M600 (Arg0, 0x23, Local0, 0x01834C6E29AF5D7B)
            }

            NAnd (0x00, Arg2, Local0)
            M600 (Arg0, 0x24, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (0xFFFFFFFFFFFFFFFF, Arg2, Local0)
            M600 (Arg0, 0x25, Local0, 0x01834C6E29AF5D7B)
            NAnd (AUI5, Arg2, Local0)
            M600 (Arg0, 0x26, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (AUIJ, Arg2, Local0)
            M600 (Arg0, 0x27, Local0, 0x01834C6E29AF5D7B)
            If (Y078)
            {
                NAnd (DerefOf (RefOf (AUI5)), Arg2, Local0)
                M600 (Arg0, 0x28, Local0, 0xFFFFFFFFFFFFFFFF)
                NAnd (DerefOf (RefOf (AUIJ)), Arg2, Local0)
                M600 (Arg0, 0x29, Local0, 0x01834C6E29AF5D7B)
            }

            NAnd (DerefOf (PAUI [0x05]), Arg2, Local0)
            M600 (Arg0, 0x2A, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (DerefOf (PAUI [0x13]), Arg2, Local0)
            M600 (Arg0, 0x2B, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Integer */

            NAnd (M601 (0x01, 0x05), Arg2, Local0)
            M600 (Arg0, 0x2C, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (M601 (0x01, 0x13), Arg2, Local0)
            M600 (Arg0, 0x2D, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                NAnd (DerefOf (M602 (0x01, 0x05, 0x01)), Arg2, Local0)
                M600 (Arg0, 0x2E, Local0, 0xFFFFFFFFFFFFFFFF)
                NAnd (DerefOf (M602 (0x01, 0x13, 0x01)), Arg2, Local0)
                M600 (Arg0, 0x2F, Local0, 0x01834C6E29AF5D7B)
            }

            /* Conversion of the both operands */

            Local0 = NAnd (Arg1, Arg2)
            M600 (Arg0, 0x30, Local0, 0xFFFFFFFFFFFFFDFF)
            Local0 = NAnd (Arg2, Arg1)
            M600 (Arg0, 0x31, Local0, 0xFFFFFFFFFFFFFDFF)
            NAnd (Arg1, Arg2, Local0)
            M600 (Arg0, 0x32, Local0, 0xFFFFFFFFFFFFFDFF)
            NAnd (Arg2, Arg1, Local0)
            M600 (Arg0, 0x33, Local0, 0xFFFFFFFFFFFFFDFF)
        }

        /* NAnd, 32-bit */

        Method (M012, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Local0 = NAnd (Arg2, 0x00)
            M600 (Arg0, 0x00, Local0, 0xFFFFFFFF)
            Local0 = NAnd (Arg2, 0xFFFFFFFF)
            M600 (Arg0, 0x01, Local0, 0x3E864C01)
            Local0 = NAnd (Arg2, AUI5)
            M600 (Arg0, 0x02, Local0, 0xFFFFFFFF)
            Local0 = NAnd (Arg2, AUII)
            M600 (Arg0, 0x03, Local0, 0x3E864C01)
            If (Y078)
            {
                Local0 = NAnd (Arg2, DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x04, Local0, 0xFFFFFFFF)
                Local0 = NAnd (Arg2, DerefOf (RefOf (AUII)))
                M600 (Arg0, 0x05, Local0, 0x3E864C01)
            }

            Local0 = NAnd (Arg2, DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x06, Local0, 0xFFFFFFFF)
            Local0 = NAnd (Arg2, DerefOf (PAUI [0x12]))
            M600 (Arg0, 0x07, Local0, 0x3E864C01)
            /* Method returns Integer */

            Local0 = NAnd (Arg2, M601 (0x01, 0x05))
            M600 (Arg0, 0x08, Local0, 0xFFFFFFFF)
            Local0 = NAnd (Arg2, M601 (0x01, 0x12))
            M600 (Arg0, 0x09, Local0, 0x3E864C01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = NAnd (Arg2, DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x0A, Local0, 0xFFFFFFFF)
                Local0 = NAnd (Arg2, DerefOf (M602 (0x01, 0x12, 0x01)))
                M600 (Arg0, 0x0B, Local0, 0x3E864C01)
            }

            NAnd (Arg2, 0x00, Local0)
            M600 (Arg0, 0x0C, Local0, 0xFFFFFFFF)
            NAnd (Arg2, 0xFFFFFFFF, Local0)
            M600 (Arg0, 0x0D, Local0, 0x3E864C01)
            NAnd (Arg2, AUI5, Local0)
            M600 (Arg0, 0x0E, Local0, 0xFFFFFFFF)
            NAnd (Arg2, AUII, Local0)
            M600 (Arg0, 0x0F, Local0, 0x3E864C01)
            If (Y078)
            {
                NAnd (Arg2, DerefOf (RefOf (AUI5)), Local0)
                M600 (Arg0, 0x10, Local0, 0xFFFFFFFF)
                NAnd (Arg2, DerefOf (RefOf (AUII)), Local0)
                M600 (Arg0, 0x11, Local0, 0x3E864C01)
            }

            NAnd (Arg2, DerefOf (PAUI [0x05]), Local0)
            M600 (Arg0, 0x12, Local0, 0xFFFFFFFF)
            NAnd (Arg2, DerefOf (PAUI [0x12]), Local0)
            M600 (Arg0, 0x13, Local0, 0x3E864C01)
            /* Method returns Integer */

            NAnd (Arg2, M601 (0x01, 0x05), Local0)
            M600 (Arg0, 0x14, Local0, 0xFFFFFFFF)
            NAnd (Arg2, M601 (0x01, 0x12), Local0)
            M600 (Arg0, 0x15, Local0, 0x3E864C01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                NAnd (Arg2, DerefOf (M602 (0x01, 0x05, 0x01)), Local0)
                M600 (Arg0, 0x16, Local0, 0xFFFFFFFF)
                NAnd (Arg2, DerefOf (M602 (0x01, 0x12, 0x01)), Local0)
                M600 (Arg0, 0x17, Local0, 0x3E864C01)
            }

            /* Conversion of the second operand */

            Local0 = NAnd (0x00, Arg2)
            M600 (Arg0, 0x18, Local0, 0xFFFFFFFF)
            Local0 = NAnd (0xFFFFFFFF, Arg2)
            M600 (Arg0, 0x19, Local0, 0x3E864C01)
            Local0 = NAnd (AUI5, Arg2)
            M600 (Arg0, 0x1A, Local0, 0xFFFFFFFF)
            Local0 = NAnd (AUII, Arg2)
            M600 (Arg0, 0x1B, Local0, 0x3E864C01)
            If (Y078)
            {
                Local0 = NAnd (DerefOf (RefOf (AUI5)), Arg2)
                M600 (Arg0, 0x1C, Local0, 0xFFFFFFFF)
                Local0 = NAnd (DerefOf (RefOf (AUII)), Arg2)
                M600 (Arg0, 0x1D, Local0, 0x3E864C01)
            }

            Local0 = NAnd (DerefOf (PAUI [0x05]), Arg2)
            M600 (Arg0, 0x1E, Local0, 0xFFFFFFFF)
            Local0 = NAnd (DerefOf (PAUI [0x12]), Arg2)
            M600 (Arg0, 0x1F, Local0, 0x3E864C01)
            /* Method returns Integer */

            Local0 = NAnd (M601 (0x01, 0x05), Arg2)
            M600 (Arg0, 0x20, Local0, 0xFFFFFFFF)
            Local0 = NAnd (M601 (0x01, 0x12), Arg2)
            M600 (Arg0, 0x21, Local0, 0x3E864C01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = NAnd (DerefOf (M602 (0x01, 0x05, 0x01)), Arg2)
                M600 (Arg0, 0x22, Local0, 0xFFFFFFFF)
                Local0 = NAnd (DerefOf (M602 (0x01, 0x12, 0x01)), Arg2)
                M600 (Arg0, 0x23, Local0, 0x3E864C01)
            }

            NAnd (0x00, Arg2, Local0)
            M600 (Arg0, 0x24, Local0, 0xFFFFFFFF)
            NAnd (0xFFFFFFFF, Arg2, Local0)
            M600 (Arg0, 0x25, Local0, 0x3E864C01)
            NAnd (AUI5, Arg2, Local0)
            M600 (Arg0, 0x26, Local0, 0xFFFFFFFF)
            NAnd (AUII, Arg2, Local0)
            M600 (Arg0, 0x27, Local0, 0x3E864C01)
            If (Y078)
            {
                NAnd (DerefOf (RefOf (AUI5)), Arg2, Local0)
                M600 (Arg0, 0x28, Local0, 0xFFFFFFFF)
                NAnd (DerefOf (RefOf (AUII)), Arg2, Local0)
                M600 (Arg0, 0x29, Local0, 0x3E864C01)
            }

            NAnd (DerefOf (PAUI [0x05]), Arg2, Local0)
            M600 (Arg0, 0x2A, Local0, 0xFFFFFFFF)
            NAnd (DerefOf (PAUI [0x12]), Arg2, Local0)
            M600 (Arg0, 0x2B, Local0, 0x3E864C01)
            /* Method returns Integer */

            NAnd (M601 (0x01, 0x05), Arg2, Local0)
            M600 (Arg0, 0x2C, Local0, 0xFFFFFFFF)
            NAnd (M601 (0x01, 0x12), Arg2, Local0)
            M600 (Arg0, 0x2D, Local0, 0x3E864C01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                NAnd (DerefOf (M602 (0x01, 0x05, 0x01)), Arg2, Local0)
                M600 (Arg0, 0x2E, Local0, 0xFFFFFFFF)
                NAnd (DerefOf (M602 (0x01, 0x12, 0x01)), Arg2, Local0)
                M600 (Arg0, 0x2F, Local0, 0x3E864C01)
            }

            /* Conversion of the both operands */

            Local0 = NAnd (Arg1, Arg2)
            M600 (Arg0, 0x30, Local0, 0xFFFFFCDF)
            Local0 = NAnd (Arg2, Arg1)
            M600 (Arg0, 0x31, Local0, 0xFFFFFCDF)
            NAnd (Arg1, Arg2, Local0)
            M600 (Arg0, 0x32, Local0, 0xFFFFFCDF)
            NAnd (Arg2, Arg1, Local0)
            M600 (Arg0, 0x33, Local0, 0xFFFFFCDF)
        }

        /* NOr, common 32-bit/64-bit test */

        Method (M013, 2, NotSerialized)
        {
            /* Conversion of the first operand */

            Local0 = NOr (Arg1, 0x00)
            M600 (Arg0, 0x00, Local0, 0xFFFFFFFFFFFFFCDE)
            Local0 = NOr (Arg1, 0xFFFFFFFFFFFFFFFF)
            M600 (Arg0, 0x01, Local0, 0x00)
            Local0 = NOr (Arg1, AUI5)
            M600 (Arg0, 0x02, Local0, 0xFFFFFFFFFFFFFCDE)
            Local0 = NOr (Arg1, AUIJ)
            M600 (Arg0, 0x03, Local0, 0x00)
            If (Y078)
            {
                Local0 = NOr (Arg1, DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x04, Local0, 0xFFFFFFFFFFFFFCDE)
                Local0 = NOr (Arg1, DerefOf (RefOf (AUIJ)))
                M600 (Arg0, 0x05, Local0, 0x00)
            }

            Local0 = NOr (Arg1, DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x06, Local0, 0xFFFFFFFFFFFFFCDE)
            Local0 = NOr (Arg1, DerefOf (PAUI [0x13]))
            M600 (Arg0, 0x07, Local0, 0x00)
            /* Method returns Integer */

            Local0 = NOr (Arg1, M601 (0x01, 0x05))
            M600 (Arg0, 0x08, Local0, 0xFFFFFFFFFFFFFCDE)
            Local0 = NOr (Arg1, M601 (0x01, 0x13))
            M600 (Arg0, 0x09, Local0, 0x00)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = NOr (Arg1, DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x0A, Local0, 0xFFFFFFFFFFFFFCDE)
                Local0 = NOr (Arg1, DerefOf (M602 (0x01, 0x13, 0x01)))
                M600 (Arg0, 0x0B, Local0, 0x00)
            }

            NOr (Arg1, 0x00, Local0)
            M600 (Arg0, 0x0C, Local0, 0xFFFFFFFFFFFFFCDE)
            NOr (Arg1, 0xFFFFFFFFFFFFFFFF, Local0)
            M600 (Arg0, 0x0D, Local0, 0x00)
            NOr (Arg1, AUI5, Local0)
            M600 (Arg0, 0x0E, Local0, 0xFFFFFFFFFFFFFCDE)
            NOr (Arg1, AUIJ, Local0)
            M600 (Arg0, 0x0F, Local0, 0x00)
            If (Y078)
            {
                NOr (Arg1, DerefOf (RefOf (AUI5)), Local0)
                M600 (Arg0, 0x10, Local0, 0xFFFFFFFFFFFFFCDE)
                NOr (Arg1, DerefOf (RefOf (AUIJ)), Local0)
                M600 (Arg0, 0x11, Local0, 0x00)
            }

            NOr (Arg1, DerefOf (PAUI [0x05]), Local0)
            M600 (Arg0, 0x12, Local0, 0xFFFFFFFFFFFFFCDE)
            NOr (Arg1, DerefOf (PAUI [0x13]), Local0)
            M600 (Arg0, 0x13, Local0, 0x00)
            /* Method returns Integer */

            NOr (Arg1, M601 (0x01, 0x05), Local0)
            M600 (Arg0, 0x14, Local0, 0xFFFFFFFFFFFFFCDE)
            NOr (Arg1, M601 (0x01, 0x13), Local0)
            M600 (Arg0, 0x15, Local0, 0x00)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                NOr (Arg1, DerefOf (M602 (0x01, 0x05, 0x01)), Local0)
                M600 (Arg0, 0x16, Local0, 0xFFFFFFFFFFFFFCDE)
                NOr (Arg1, DerefOf (M602 (0x01, 0x13, 0x01)), Local0)
                M600 (Arg0, 0x17, Local0, 0x00)
            }

            /* Conversion of the second operand */

            Local0 = NOr (0x00, Arg1)
            M600 (Arg0, 0x18, Local0, 0xFFFFFFFFFFFFFCDE)
            Local0 = NOr (0xFFFFFFFFFFFFFFFF, Arg1)
            M600 (Arg0, 0x19, Local0, 0x00)
            Local0 = NOr (AUI5, Arg1)
            M600 (Arg0, 0x1A, Local0, 0xFFFFFFFFFFFFFCDE)
            Local0 = NOr (AUIJ, Arg1)
            M600 (Arg0, 0x1B, Local0, 0x00)
            If (Y078)
            {
                Local0 = NOr (DerefOf (RefOf (AUI5)), Arg1)
                M600 (Arg0, 0x1C, Local0, 0xFFFFFFFFFFFFFCDE)
                Local0 = NOr (DerefOf (RefOf (AUIJ)), Arg1)
                M600 (Arg0, 0x1D, Local0, 0x00)
            }

            Local0 = NOr (DerefOf (PAUI [0x05]), Arg1)
            M600 (Arg0, 0x1E, Local0, 0xFFFFFFFFFFFFFCDE)
            Local0 = NOr (DerefOf (PAUI [0x13]), Arg1)
            M600 (Arg0, 0x1F, Local0, 0x00)
            /* Method returns Integer */

            Local0 = NOr (M601 (0x01, 0x05), Arg1)
            M600 (Arg0, 0x20, Local0, 0xFFFFFFFFFFFFFCDE)
            Local0 = NOr (M601 (0x01, 0x13), Arg1)
            M600 (Arg0, 0x21, Local0, 0x00)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = NOr (DerefOf (M602 (0x01, 0x05, 0x01)), Arg1)
                M600 (Arg0, 0x22, Local0, 0xFFFFFFFFFFFFFCDE)
                Local0 = NOr (DerefOf (M602 (0x01, 0x13, 0x01)), Arg1)
                M600 (Arg0, 0x23, Local0, 0x00)
            }

            NOr (0x00, Arg1, Local0)
            M600 (Arg0, 0x24, Local0, 0xFFFFFFFFFFFFFCDE)
            NOr (0xFFFFFFFFFFFFFFFF, Arg1, Local0)
            M600 (Arg0, 0x25, Local0, 0x00)
            NOr (AUI5, Arg1, Local0)
            M600 (Arg0, 0x26, Local0, 0xFFFFFFFFFFFFFCDE)
            NOr (AUIJ, Arg1, Local0)
            M600 (Arg0, 0x27, Local0, 0x00)
            If (Y078)
            {
                NOr (DerefOf (RefOf (AUI5)), Arg1, Local0)
                M600 (Arg0, 0x28, Local0, 0xFFFFFFFFFFFFFCDE)
                NOr (DerefOf (RefOf (AUIJ)), Arg1, Local0)
                M600 (Arg0, 0x29, Local0, 0x00)
            }

            NOr (DerefOf (PAUI [0x05]), Arg1, Local0)
            M600 (Arg0, 0x2A, Local0, 0xFFFFFFFFFFFFFCDE)
            NOr (DerefOf (PAUI [0x13]), Arg1, Local0)
            M600 (Arg0, 0x2B, Local0, 0x00)
            /* Method returns Integer */

            NOr (M601 (0x01, 0x05), Arg1, Local0)
            M600 (Arg0, 0x2C, Local0, 0xFFFFFFFFFFFFFCDE)
            NOr (M601 (0x01, 0x13), Arg1, Local0)
            M600 (Arg0, 0x2D, Local0, 0x00)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                NOr (DerefOf (M602 (0x01, 0x05, 0x01)), Arg1, Local0)
                M600 (Arg0, 0x2E, Local0, 0xFFFFFFFFFFFFFCDE)
                NOr (DerefOf (M602 (0x01, 0x13, 0x01)), Arg1, Local0)
                M600 (Arg0, 0x2F, Local0, 0x00)
            }
        }

        /* NOr, 64-bit */

        Method (M014, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Local0 = NOr (Arg2, 0x00)
            M600 (Arg0, 0x00, Local0, 0x01834C6E29AF5D7B)
            Local0 = NOr (Arg2, 0xFFFFFFFFFFFFFFFF)
            M600 (Arg0, 0x01, Local0, 0x00)
            Local0 = NOr (Arg2, AUI5)
            M600 (Arg0, 0x02, Local0, 0x01834C6E29AF5D7B)
            Local0 = NOr (Arg2, AUIJ)
            M600 (Arg0, 0x03, Local0, 0x00)
            If (Y078)
            {
                Local0 = NOr (Arg2, DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x04, Local0, 0x01834C6E29AF5D7B)
                Local0 = NOr (Arg2, DerefOf (RefOf (AUIJ)))
                M600 (Arg0, 0x05, Local0, 0x00)
            }

            Local0 = NOr (Arg2, DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x06, Local0, 0x01834C6E29AF5D7B)
            Local0 = NOr (Arg2, DerefOf (PAUI [0x13]))
            M600 (Arg0, 0x07, Local0, 0x00)
            /* Method returns Integer */

            Local0 = NOr (Arg2, M601 (0x01, 0x05))
            M600 (Arg0, 0x08, Local0, 0x01834C6E29AF5D7B)
            Local0 = NOr (Arg2, M601 (0x01, 0x13))
            M600 (Arg0, 0x09, Local0, 0x00)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = NOr (Arg2, DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x0A, Local0, 0x01834C6E29AF5D7B)
                Local0 = NOr (Arg2, DerefOf (M602 (0x01, 0x13, 0x01)))
                M600 (Arg0, 0x0B, Local0, 0x00)
            }

            NOr (Arg2, 0x00, Local0)
            M600 (Arg0, 0x0C, Local0, 0x01834C6E29AF5D7B)
            NOr (Arg2, 0xFFFFFFFFFFFFFFFF, Local0)
            M600 (Arg0, 0x0D, Local0, 0x00)
            NOr (Arg2, AUI5, Local0)
            M600 (Arg0, 0x0E, Local0, 0x01834C6E29AF5D7B)
            NOr (Arg2, AUIJ, Local0)
            M600 (Arg0, 0x0F, Local0, 0x00)
            If (Y078)
            {
                NOr (Arg2, DerefOf (RefOf (AUI5)), Local0)
                M600 (Arg0, 0x10, Local0, 0x01834C6E29AF5D7B)
                NOr (Arg2, DerefOf (RefOf (AUIJ)), Local0)
                M600 (Arg0, 0x11, Local0, 0x00)
            }

            NOr (Arg2, DerefOf (PAUI [0x05]), Local0)
            M600 (Arg0, 0x12, Local0, 0x01834C6E29AF5D7B)
            NOr (Arg2, DerefOf (PAUI [0x13]), Local0)
            M600 (Arg0, 0x13, Local0, 0x00)
            /* Method returns Integer */

            NOr (Arg2, M601 (0x01, 0x05), Local0)
            M600 (Arg0, 0x14, Local0, 0x01834C6E29AF5D7B)
            NOr (Arg2, M601 (0x01, 0x13), Local0)
            M600 (Arg0, 0x15, Local0, 0x00)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                NOr (Arg2, DerefOf (M602 (0x01, 0x05, 0x01)), Local0)
                M600 (Arg0, 0x16, Local0, 0x01834C6E29AF5D7B)
                NOr (Arg2, DerefOf (M602 (0x01, 0x13, 0x01)), Local0)
                M600 (Arg0, 0x17, Local0, 0x00)
            }

            /* Conversion of the second operand */

            Local0 = NOr (0x00, Arg2)
            M600 (Arg0, 0x18, Local0, 0x01834C6E29AF5D7B)
            Local0 = NOr (0xFFFFFFFFFFFFFFFF, Arg2)
            M600 (Arg0, 0x19, Local0, 0x00)
            Local0 = NOr (AUI5, Arg2)
            M600 (Arg0, 0x1A, Local0, 0x01834C6E29AF5D7B)
            Local0 = NOr (AUIJ, Arg2)
            M600 (Arg0, 0x1B, Local0, 0x00)
            If (Y078)
            {
                Local0 = NOr (DerefOf (RefOf (AUI5)), Arg2)
                M600 (Arg0, 0x1C, Local0, 0x01834C6E29AF5D7B)
                Local0 = NOr (DerefOf (RefOf (AUIJ)), Arg2)
                M600 (Arg0, 0x1D, Local0, 0x00)
            }

            Local0 = NOr (DerefOf (PAUI [0x05]), Arg2)
            M600 (Arg0, 0x1E, Local0, 0x01834C6E29AF5D7B)
            Local0 = NOr (DerefOf (PAUI [0x13]), Arg2)
            M600 (Arg0, 0x1F, Local0, 0x00)
            /* Method returns Integer */

            Local0 = NOr (M601 (0x01, 0x05), Arg2)
            M600 (Arg0, 0x20, Local0, 0x01834C6E29AF5D7B)
            Local0 = NOr (M601 (0x01, 0x13), Arg2)
            M600 (Arg0, 0x21, Local0, 0x00)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = NOr (DerefOf (M602 (0x01, 0x05, 0x01)), Arg2)
                M600 (Arg0, 0x22, Local0, 0x01834C6E29AF5D7B)
                Local0 = NOr (DerefOf (M602 (0x01, 0x13, 0x01)), Arg2)
                M600 (Arg0, 0x23, Local0, 0x00)
            }

            NOr (0x00, Arg2, Local0)
            M600 (Arg0, 0x24, Local0, 0x01834C6E29AF5D7B)
            NOr (0xFFFFFFFFFFFFFFFF, Arg2, Local0)
            M600 (Arg0, 0x25, Local0, 0x00)
            NOr (AUI5, Arg2, Local0)
            M600 (Arg0, 0x26, Local0, 0x01834C6E29AF5D7B)
            NOr (AUIJ, Arg2, Local0)
            M600 (Arg0, 0x27, Local0, 0x00)
            If (Y078)
            {
                NOr (DerefOf (RefOf (AUI5)), Arg2, Local0)
                M600 (Arg0, 0x28, Local0, 0x01834C6E29AF5D7B)
                NOr (DerefOf (RefOf (AUIJ)), Arg2, Local0)
                M600 (Arg0, 0x29, Local0, 0x00)
            }

            NOr (DerefOf (PAUI [0x05]), Arg2, Local0)
            M600 (Arg0, 0x2A, Local0, 0x01834C6E29AF5D7B)
            NOr (DerefOf (PAUI [0x13]), Arg2, Local0)
            M600 (Arg0, 0x2B, Local0, 0x00)
            /* Method returns Integer */

            NOr (M601 (0x01, 0x05), Arg2, Local0)
            M600 (Arg0, 0x2C, Local0, 0x01834C6E29AF5D7B)
            NOr (M601 (0x01, 0x13), Arg2, Local0)
            M600 (Arg0, 0x2D, Local0, 0x00)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                NOr (DerefOf (M602 (0x01, 0x05, 0x01)), Arg2, Local0)
                M600 (Arg0, 0x2E, Local0, 0x01834C6E29AF5D7B)
                NOr (DerefOf (M602 (0x01, 0x13, 0x01)), Arg2, Local0)
                M600 (Arg0, 0x2F, Local0, 0x00)
            }

            /* Conversion of the both operands */

            Local0 = NOr (Arg1, Arg2)
            M600 (Arg0, 0x30, Local0, 0x01834C6E29AF5C5A)
            Local0 = NOr (Arg2, Arg1)
            M600 (Arg0, 0x31, Local0, 0x01834C6E29AF5C5A)
            NOr (Arg1, Arg2, Local0)
            M600 (Arg0, 0x32, Local0, 0x01834C6E29AF5C5A)
            NOr (Arg2, Arg1, Local0)
            M600 (Arg0, 0x33, Local0, 0x01834C6E29AF5C5A)
        }

        /* NOr, 32-bit */

        Method (M015, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Local0 = NOr (Arg2, 0x00)
            M600 (Arg0, 0x00, Local0, 0x3E864C01)
            Local0 = NOr (Arg2, 0xFFFFFFFF)
            M600 (Arg0, 0x01, Local0, 0x00)
            Local0 = NOr (Arg2, AUI5)
            M600 (Arg0, 0x02, Local0, 0x3E864C01)
            Local0 = NOr (Arg2, AUII)
            M600 (Arg0, 0x03, Local0, 0x00)
            If (Y078)
            {
                Local0 = NOr (Arg2, DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x04, Local0, 0x3E864C01)
                Local0 = NOr (Arg2, DerefOf (RefOf (AUII)))
                M600 (Arg0, 0x05, Local0, 0x00)
            }

            Local0 = NOr (Arg2, DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x06, Local0, 0x3E864C01)
            Local0 = NOr (Arg2, DerefOf (PAUI [0x12]))
            M600 (Arg0, 0x07, Local0, 0x00)
            /* Method returns Integer */

            Local0 = NOr (Arg2, M601 (0x01, 0x05))
            M600 (Arg0, 0x08, Local0, 0x3E864C01)
            Local0 = NOr (Arg2, M601 (0x01, 0x12))
            M600 (Arg0, 0x09, Local0, 0x00)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = NOr (Arg2, DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x0A, Local0, 0x3E864C01)
                Local0 = NOr (Arg2, DerefOf (M602 (0x01, 0x12, 0x01)))
                M600 (Arg0, 0x0B, Local0, 0x00)
            }

            NOr (Arg2, 0x00, Local0)
            M600 (Arg0, 0x0C, Local0, 0x3E864C01)
            NOr (Arg2, 0xFFFFFFFF, Local0)
            M600 (Arg0, 0x0D, Local0, 0x00)
            NOr (Arg2, AUI5, Local0)
            M600 (Arg0, 0x0E, Local0, 0x3E864C01)
            NOr (Arg2, AUII, Local0)
            M600 (Arg0, 0x0F, Local0, 0x00)
            If (Y078)
            {
                NOr (Arg2, DerefOf (RefOf (AUI5)), Local0)
                M600 (Arg0, 0x10, Local0, 0x3E864C01)
                NOr (Arg2, DerefOf (RefOf (AUII)), Local0)
                M600 (Arg0, 0x11, Local0, 0x00)
            }

            NOr (Arg2, DerefOf (PAUI [0x05]), Local0)
            M600 (Arg0, 0x12, Local0, 0x3E864C01)
            NOr (Arg2, DerefOf (PAUI [0x12]), Local0)
            M600 (Arg0, 0x13, Local0, 0x00)
            /* Method returns Integer */

            NOr (Arg2, M601 (0x01, 0x05), Local0)
            M600 (Arg0, 0x14, Local0, 0x3E864C01)
            NOr (Arg2, M601 (0x01, 0x12), Local0)
            M600 (Arg0, 0x15, Local0, 0x00)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                NOr (Arg2, DerefOf (M602 (0x01, 0x05, 0x01)), Local0)
                M600 (Arg0, 0x16, Local0, 0x3E864C01)
                NOr (Arg2, DerefOf (M602 (0x01, 0x12, 0x01)), Local0)
                M600 (Arg0, 0x17, Local0, 0x00)
            }

            /* Conversion of the second operand */

            Local0 = NOr (0x00, Arg2)
            M600 (Arg0, 0x18, Local0, 0x3E864C01)
            Local0 = NOr (0xFFFFFFFF, Arg2)
            M600 (Arg0, 0x19, Local0, 0x00)
            Local0 = NOr (AUI5, Arg2)
            M600 (Arg0, 0x1A, Local0, 0x3E864C01)
            Local0 = NOr (AUII, Arg2)
            M600 (Arg0, 0x1B, Local0, 0x00)
            If (Y078)
            {
                Local0 = NOr (DerefOf (RefOf (AUI5)), Arg2)
                M600 (Arg0, 0x1C, Local0, 0x3E864C01)
                Local0 = NOr (DerefOf (RefOf (AUII)), Arg2)
                M600 (Arg0, 0x1D, Local0, 0x00)
            }

            Local0 = NOr (DerefOf (PAUI [0x05]), Arg2)
            M600 (Arg0, 0x1E, Local0, 0x3E864C01)
            Local0 = NOr (DerefOf (PAUI [0x12]), Arg2)
            M600 (Arg0, 0x1F, Local0, 0x00)
            /* Method returns Integer */

            Local0 = NOr (M601 (0x01, 0x05), Arg2)
            M600 (Arg0, 0x20, Local0, 0x3E864C01)
            Local0 = NOr (M601 (0x01, 0x12), Arg2)
            M600 (Arg0, 0x21, Local0, 0x00)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = NOr (DerefOf (M602 (0x01, 0x05, 0x01)), Arg2)
                M600 (Arg0, 0x22, Local0, 0x3E864C01)
                Local0 = NOr (DerefOf (M602 (0x01, 0x12, 0x01)), Arg2)
                M600 (Arg0, 0x23, Local0, 0x00)
            }

            NOr (0x00, Arg2, Local0)
            M600 (Arg0, 0x24, Local0, 0x3E864C01)
            NOr (0xFFFFFFFF, Arg2, Local0)
            M600 (Arg0, 0x25, Local0, 0x00)
            NOr (AUI5, Arg2, Local0)
            M600 (Arg0, 0x26, Local0, 0x3E864C01)
            NOr (AUII, Arg2, Local0)
            M600 (Arg0, 0x27, Local0, 0x00)
            If (Y078)
            {
                NOr (DerefOf (RefOf (AUI5)), Arg2, Local0)
                M600 (Arg0, 0x28, Local0, 0x3E864C01)
                NOr (DerefOf (RefOf (AUII)), Arg2, Local0)
                M600 (Arg0, 0x29, Local0, 0x00)
            }

            NOr (DerefOf (PAUI [0x05]), Arg2, Local0)
            M600 (Arg0, 0x2A, Local0, 0x3E864C01)
            NOr (DerefOf (PAUI [0x12]), Arg2, Local0)
            M600 (Arg0, 0x2B, Local0, 0x00)
            /* Method returns Integer */

            NOr (M601 (0x01, 0x05), Arg2, Local0)
            M600 (Arg0, 0x2C, Local0, 0x3E864C01)
            NOr (M601 (0x01, 0x12), Arg2, Local0)
            M600 (Arg0, 0x2D, Local0, 0x00)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                NOr (DerefOf (M602 (0x01, 0x05, 0x01)), Arg2, Local0)
                M600 (Arg0, 0x2E, Local0, 0x3E864C01)
                NOr (DerefOf (M602 (0x01, 0x12, 0x01)), Arg2, Local0)
                M600 (Arg0, 0x2F, Local0, 0x00)
            }

            /* Conversion of the both operands */

            Local0 = NOr (Arg1, Arg2)
            M600 (Arg0, 0x30, Local0, 0x3E864C00)
            Local0 = NOr (Arg2, Arg1)
            M600 (Arg0, 0x31, Local0, 0x3E864C00)
            NOr (Arg1, Arg2, Local0)
            M600 (Arg0, 0x32, Local0, 0x3E864C00)
            NOr (Arg2, Arg1, Local0)
            M600 (Arg0, 0x33, Local0, 0x3E864C00)
        }

        /* Or, common 32-bit/64-bit test */

        Method (M016, 2, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg1 | 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0x0321)
            Store ((Arg1 | 0xFFFFFFFFFFFFFFFF), Local0)
            M600 (Arg0, 0x01, Local0, 0xFFFFFFFFFFFFFFFF)
            Store ((Arg1 | AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0x0321)
            Store ((Arg1 | AUIJ), Local0)
            M600 (Arg0, 0x03, Local0, 0xFFFFFFFFFFFFFFFF)
            If (Y078)
            {
                Store ((Arg1 | DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0x0321)
                Store ((Arg1 | DerefOf (RefOf (AUIJ))), Local0)
                M600 (Arg0, 0x05, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            Store ((Arg1 | DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0x0321)
            Store ((Arg1 | DerefOf (PAUI [0x13])), Local0)
            M600 (Arg0, 0x07, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Integer */

            Store ((Arg1 | M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0x0321)
            Store ((Arg1 | M601 (0x01, 0x13)), Local0)
            M600 (Arg0, 0x09, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg1 | DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0x0321)
                Store ((Arg1 | DerefOf (M602 (0x01, 0x13, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            Local0 = (Arg1 | 0x00)
            M600 (Arg0, 0x0C, Local0, 0x0321)
            Local0 = (Arg1 | 0xFFFFFFFFFFFFFFFF)
            M600 (Arg0, 0x0D, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = (Arg1 | AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0x0321)
            Local0 = (Arg1 | AUIJ) /* \AUIJ */
            M600 (Arg0, 0x0F, Local0, 0xFFFFFFFFFFFFFFFF)
            If (Y078)
            {
                Local0 = (Arg1 | DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0x0321)
                Local0 = (Arg1 | DerefOf (RefOf (AUIJ)))
                M600 (Arg0, 0x11, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            Local0 = (Arg1 | DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0x0321)
            Local0 = (Arg1 | DerefOf (PAUI [0x13]))
            M600 (Arg0, 0x13, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Integer */

            Local0 = (Arg1 | M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0x0321)
            Local0 = (Arg1 | M601 (0x01, 0x13))
            M600 (Arg0, 0x15, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg1 | DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0x0321)
                Local0 = (Arg1 | DerefOf (M602 (0x01, 0x13, 0x01)))
                M600 (Arg0, 0x17, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            /* Conversion of the second operand */

            Store ((0x00 | Arg1), Local0)
            M600 (Arg0, 0x18, Local0, 0x0321)
            Store ((0xFFFFFFFFFFFFFFFF | Arg1), Local0)
            M600 (Arg0, 0x19, Local0, 0xFFFFFFFFFFFFFFFF)
            Store ((AUI5 | Arg1), Local0)
            M600 (Arg0, 0x1A, Local0, 0x0321)
            Store ((AUIJ | Arg1), Local0)
            M600 (Arg0, 0x1B, Local0, 0xFFFFFFFFFFFFFFFF)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) | Arg1), Local0)
                M600 (Arg0, 0x1C, Local0, 0x0321)
                Store ((DerefOf (RefOf (AUIJ)) | Arg1), Local0)
                M600 (Arg0, 0x1D, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            Store ((DerefOf (PAUI [0x05]) | Arg1), Local0)
            M600 (Arg0, 0x1E, Local0, 0x0321)
            Store ((DerefOf (PAUI [0x13]) | Arg1), Local0)
            M600 (Arg0, 0x1F, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) | Arg1), Local0)
            M600 (Arg0, 0x20, Local0, 0x0321)
            Store ((M601 (0x01, 0x13) | Arg1), Local0)
            M600 (Arg0, 0x21, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) | Arg1), Local0)
                M600 (Arg0, 0x22, Local0, 0x0321)
                Store ((DerefOf (M602 (0x01, 0x13, 0x01)) | Arg1), Local0)
                M600 (Arg0, 0x23, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            Local0 = (0x00 | Arg1)
            M600 (Arg0, 0x24, Local0, 0x0321)
            Local0 = (0xFFFFFFFFFFFFFFFF | Arg1)
            M600 (Arg0, 0x25, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = (AUI5 | Arg1)
            M600 (Arg0, 0x26, Local0, 0x0321)
            Local0 = (AUIJ | Arg1)
            M600 (Arg0, 0x27, Local0, 0xFFFFFFFFFFFFFFFF)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) | Arg1)
                M600 (Arg0, 0x28, Local0, 0x0321)
                Local0 = (DerefOf (RefOf (AUIJ)) | Arg1)
                M600 (Arg0, 0x29, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            Local0 = (DerefOf (PAUI [0x05]) | Arg1)
            M600 (Arg0, 0x2A, Local0, 0x0321)
            Local0 = (DerefOf (PAUI [0x13]) | Arg1)
            M600 (Arg0, 0x2B, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) | Arg1)
            M600 (Arg0, 0x2C, Local0, 0x0321)
            Local0 = (M601 (0x01, 0x13) | Arg1)
            M600 (Arg0, 0x2D, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) | Arg1)
                M600 (Arg0, 0x2E, Local0, 0x0321)
                Local0 = (DerefOf (M602 (0x01, 0x13, 0x01)) | Arg1)
                M600 (Arg0, 0x2F, Local0, 0xFFFFFFFFFFFFFFFF)
            }
        }

        /* Or, 64-bit */

        Method (M017, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 | 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 | 0xFFFFFFFFFFFFFFFF), Local0)
            M600 (Arg0, 0x01, Local0, 0xFFFFFFFFFFFFFFFF)
            Store ((Arg2 | AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 | AUIJ), Local0)
            M600 (Arg0, 0x03, Local0, 0xFFFFFFFFFFFFFFFF)
            If (Y078)
            {
                Store ((Arg2 | DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 | DerefOf (RefOf (AUIJ))), Local0)
                M600 (Arg0, 0x05, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            Store ((Arg2 | DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 | DerefOf (PAUI [0x13])), Local0)
            M600 (Arg0, 0x07, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Integer */

            Store ((Arg2 | M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 | M601 (0x01, 0x13)), Local0)
            M600 (Arg0, 0x09, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 | DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 | DerefOf (M602 (0x01, 0x13, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            Local0 = (Arg2 | 0x00)
            M600 (Arg0, 0x0C, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 | 0xFFFFFFFFFFFFFFFF)
            M600 (Arg0, 0x0D, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = (Arg2 | AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 | AUIJ) /* \AUIJ */
            M600 (Arg0, 0x0F, Local0, 0xFFFFFFFFFFFFFFFF)
            If (Y078)
            {
                Local0 = (Arg2 | DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0xFE7CB391D650A284)
                Local0 = (Arg2 | DerefOf (RefOf (AUIJ)))
                M600 (Arg0, 0x11, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            Local0 = (Arg2 | DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 | DerefOf (PAUI [0x13]))
            M600 (Arg0, 0x13, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Integer */

            Local0 = (Arg2 | M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 | M601 (0x01, 0x13))
            M600 (Arg0, 0x15, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 | DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0xFE7CB391D650A284)
                Local0 = (Arg2 | DerefOf (M602 (0x01, 0x13, 0x01)))
                M600 (Arg0, 0x17, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            /* Conversion of the second operand */

            Store ((0x00 | Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0xFE7CB391D650A284)
            Store ((0xFFFFFFFFFFFFFFFF | Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0xFFFFFFFFFFFFFFFF)
            Store ((AUI5 | Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0xFE7CB391D650A284)
            Store ((AUIJ | Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0xFFFFFFFFFFFFFFFF)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) | Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0xFE7CB391D650A284)
                Store ((DerefOf (RefOf (AUIJ)) | Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            Store ((DerefOf (PAUI [0x05]) | Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0xFE7CB391D650A284)
            Store ((DerefOf (PAUI [0x13]) | Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) | Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0xFE7CB391D650A284)
            Store ((M601 (0x01, 0x13) | Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) | Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0xFE7CB391D650A284)
                Store ((DerefOf (M602 (0x01, 0x13, 0x01)) | Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            Local0 = (0x00 | Arg2)
            M600 (Arg0, 0x24, Local0, 0xFE7CB391D650A284)
            Local0 = (0xFFFFFFFFFFFFFFFF | Arg2)
            M600 (Arg0, 0x25, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = (AUI5 | Arg2)
            M600 (Arg0, 0x26, Local0, 0xFE7CB391D650A284)
            Local0 = (AUIJ | Arg2)
            M600 (Arg0, 0x27, Local0, 0xFFFFFFFFFFFFFFFF)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) | Arg2)
                M600 (Arg0, 0x28, Local0, 0xFE7CB391D650A284)
                Local0 = (DerefOf (RefOf (AUIJ)) | Arg2)
                M600 (Arg0, 0x29, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            Local0 = (DerefOf (PAUI [0x05]) | Arg2)
            M600 (Arg0, 0x2A, Local0, 0xFE7CB391D650A284)
            Local0 = (DerefOf (PAUI [0x13]) | Arg2)
            M600 (Arg0, 0x2B, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) | Arg2)
            M600 (Arg0, 0x2C, Local0, 0xFE7CB391D650A284)
            Local0 = (M601 (0x01, 0x13) | Arg2)
            M600 (Arg0, 0x2D, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) | Arg2)
                M600 (Arg0, 0x2E, Local0, 0xFE7CB391D650A284)
                Local0 = (DerefOf (M602 (0x01, 0x13, 0x01)) | Arg2)
                M600 (Arg0, 0x2F, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            /* Conversion of the both operands */

            Store ((Arg1 | Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0xFE7CB391D650A3A5)
            Store ((Arg2 | Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0xFE7CB391D650A3A5)
            Local0 = (Arg1 | Arg2)
            M600 (Arg0, 0x32, Local0, 0xFE7CB391D650A3A5)
            Local0 = (Arg2 | Arg1)
            M600 (Arg0, 0x33, Local0, 0xFE7CB391D650A3A5)
        }

        /* Or, 32-bit */

        Method (M018, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 | 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0xC179B3FE)
            Store ((Arg2 | 0xFFFFFFFF), Local0)
            M600 (Arg0, 0x01, Local0, 0xFFFFFFFF)
            Store ((Arg2 | AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0xC179B3FE)
            Store ((Arg2 | AUII), Local0)
            M600 (Arg0, 0x03, Local0, 0xFFFFFFFF)
            If (Y078)
            {
                Store ((Arg2 | DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0xC179B3FE)
                Store ((Arg2 | DerefOf (RefOf (AUII))), Local0)
                M600 (Arg0, 0x05, Local0, 0xFFFFFFFF)
            }

            Store ((Arg2 | DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0xC179B3FE)
            Store ((Arg2 | DerefOf (PAUI [0x12])), Local0)
            M600 (Arg0, 0x07, Local0, 0xFFFFFFFF)
            /* Method returns Integer */

            Store ((Arg2 | M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0xC179B3FE)
            Store ((Arg2 | M601 (0x01, 0x12)), Local0)
            M600 (Arg0, 0x09, Local0, 0xFFFFFFFF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 | DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xC179B3FE)
                Store ((Arg2 | DerefOf (M602 (0x01, 0x12, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0xFFFFFFFF)
            }

            Local0 = (Arg2 | 0x00)
            M600 (Arg0, 0x0C, Local0, 0xC179B3FE)
            Local0 = (Arg2 | 0xFFFFFFFF)
            M600 (Arg0, 0x0D, Local0, 0xFFFFFFFF)
            Local0 = (Arg2 | AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0xC179B3FE)
            Local0 = (Arg2 | AUII) /* \AUII */
            M600 (Arg0, 0x0F, Local0, 0xFFFFFFFF)
            If (Y078)
            {
                Local0 = (Arg2 | DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0xC179B3FE)
                Local0 = (Arg2 | DerefOf (RefOf (AUII)))
                M600 (Arg0, 0x11, Local0, 0xFFFFFFFF)
            }

            Local0 = (Arg2 | DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0xC179B3FE)
            Local0 = (Arg2 | DerefOf (PAUI [0x12]))
            M600 (Arg0, 0x13, Local0, 0xFFFFFFFF)
            /* Method returns Integer */

            Local0 = (Arg2 | M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0xC179B3FE)
            Local0 = (Arg2 | M601 (0x01, 0x12))
            M600 (Arg0, 0x15, Local0, 0xFFFFFFFF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 | DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0xC179B3FE)
                Local0 = (Arg2 | DerefOf (M602 (0x01, 0x12, 0x01)))
                M600 (Arg0, 0x17, Local0, 0xFFFFFFFF)
            }

            /* Conversion of the second operand */

            Store ((0x00 | Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0xC179B3FE)
            Store ((0xFFFFFFFF | Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0xFFFFFFFF)
            Store ((AUI5 | Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0xC179B3FE)
            Store ((AUII | Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0xFFFFFFFF)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) | Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0xC179B3FE)
                Store ((DerefOf (RefOf (AUII)) | Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0xFFFFFFFF)
            }

            Store ((DerefOf (PAUI [0x05]) | Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0xC179B3FE)
            Store ((DerefOf (PAUI [0x12]) | Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0xFFFFFFFF)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) | Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0xC179B3FE)
            Store ((M601 (0x01, 0x12) | Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0xFFFFFFFF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) | Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0xC179B3FE)
                Store ((DerefOf (M602 (0x01, 0x12, 0x01)) | Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0xFFFFFFFF)
            }

            Local0 = (0x00 | Arg2)
            M600 (Arg0, 0x24, Local0, 0xC179B3FE)
            Local0 = (0xFFFFFFFF | Arg2)
            M600 (Arg0, 0x25, Local0, 0xFFFFFFFF)
            Local0 = (AUI5 | Arg2)
            M600 (Arg0, 0x26, Local0, 0xC179B3FE)
            Local0 = (AUII | Arg2)
            M600 (Arg0, 0x27, Local0, 0xFFFFFFFF)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) | Arg2)
                M600 (Arg0, 0x28, Local0, 0xC179B3FE)
                Local0 = (DerefOf (RefOf (AUII)) | Arg2)
                M600 (Arg0, 0x29, Local0, 0xFFFFFFFF)
            }

            Local0 = (DerefOf (PAUI [0x05]) | Arg2)
            M600 (Arg0, 0x2A, Local0, 0xC179B3FE)
            Local0 = (DerefOf (PAUI [0x12]) | Arg2)
            M600 (Arg0, 0x2B, Local0, 0xFFFFFFFF)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) | Arg2)
            M600 (Arg0, 0x2C, Local0, 0xC179B3FE)
            Local0 = (M601 (0x01, 0x12) | Arg2)
            M600 (Arg0, 0x2D, Local0, 0xFFFFFFFF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) | Arg2)
                M600 (Arg0, 0x2E, Local0, 0xC179B3FE)
                Local0 = (DerefOf (M602 (0x01, 0x12, 0x01)) | Arg2)
                M600 (Arg0, 0x2F, Local0, 0xFFFFFFFF)
            }

            /* Conversion of the both operands */

            Store ((Arg1 | Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0xC179B3FF)
            Store ((Arg2 | Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0xC179B3FF)
            Local0 = (Arg1 | Arg2)
            M600 (Arg0, 0x32, Local0, 0xC179B3FF)
            Local0 = (Arg2 | Arg1)
            M600 (Arg0, 0x33, Local0, 0xC179B3FF)
        }

        /* ShiftLeft, common 32-bit/64-bit test */

        Method (M019, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg1 << 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0x0321)
            Store ((Arg1 << 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0x0642)
            Store ((Arg1 << AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0x0321)
            Store ((Arg1 << AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0x0642)
            If (Y078)
            {
                Store ((Arg1 << DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0x0321)
                Store ((Arg1 << DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0x0642)
            }

            Store ((Arg1 << DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0x0321)
            Store ((Arg1 << DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0x0642)
            /* Method returns Integer */

            Store ((Arg1 << M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0x0321)
            Store ((Arg1 << M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0x0642)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg1 << DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0x0321)
                Store ((Arg1 << DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x0642)
            }

            Local0 = (Arg1 << 0x00)
            M600 (Arg0, 0x0C, Local0, 0x0321)
            Local0 = (Arg1 << 0x01)
            M600 (Arg0, 0x0D, Local0, 0x0642)
            Local0 = (Arg1 << AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0x0321)
            Local0 = (Arg1 << AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0x0642)
            If (Y078)
            {
                Local0 = (Arg1 << DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0x0321)
                Local0 = (Arg1 << DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0x0642)
            }

            Local0 = (Arg1 << DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0x0321)
            Local0 = (Arg1 << DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0x0642)
            /* Method returns Integer */

            Local0 = (Arg1 << M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0x0321)
            Local0 = (Arg1 << M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0x0642)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg1 << DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0x0321)
                Local0 = (Arg1 << DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0x0642)
            }

            /* Conversion of the second operand */

            Store ((0x00 << Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0x01 << Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0x0800)
            Store ((AUI5 << Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUI6 << Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0x0800)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) << Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUI6)) << Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0x0800)
            }

            Store ((DerefOf (PAUI [0x05]) << Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x06]) << Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0x0800)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) << Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x06) << Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0x0800)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) << Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) << Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0x0800)
            }

            Local0 = (0x00 << Arg2)
            M600 (Arg0, 0x24, Local0, 0x00)
            Local0 = (0x01 << Arg2)
            M600 (Arg0, 0x25, Local0, 0x0800)
            Local0 = (AUI5 << Arg2)
            M600 (Arg0, 0x26, Local0, 0x00)
            Local0 = (AUI6 << Arg2)
            M600 (Arg0, 0x27, Local0, 0x0800)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) << Arg2)
                M600 (Arg0, 0x28, Local0, 0x00)
                Local0 = (DerefOf (RefOf (AUI6)) << Arg2)
                M600 (Arg0, 0x29, Local0, 0x0800)
            }

            Local0 = (DerefOf (PAUI [0x05]) << Arg2)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Local0 = (DerefOf (PAUI [0x06]) << Arg2)
            M600 (Arg0, 0x2B, Local0, 0x0800)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) << Arg2)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Local0 = (M601 (0x01, 0x06) << Arg2)
            M600 (Arg0, 0x2D, Local0, 0x0800)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) << Arg2)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) << Arg2)
                M600 (Arg0, 0x2F, Local0, 0x0800)
            }
        }

        /* ShiftLeft, 64-bit */

        Method (M01A, 4, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 << 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 << 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0xFCF96723ACA14508)
            Store ((Arg2 << AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 << AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0xFCF96723ACA14508)
            If (Y078)
            {
                Store ((Arg2 << DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 << DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0xFCF96723ACA14508)
            }

            Store ((Arg2 << DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 << DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0xFCF96723ACA14508)
            /* Method returns Integer */

            Store ((Arg2 << M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 << M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0xFCF96723ACA14508)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 << DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 << DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0xFCF96723ACA14508)
            }

            Local0 = (Arg2 << 0x00)
            M600 (Arg0, 0x0C, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 << 0x01)
            M600 (Arg0, 0x0D, Local0, 0xFCF96723ACA14508)
            Local0 = (Arg2 << AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 << AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0xFCF96723ACA14508)
            If (Y078)
            {
                Local0 = (Arg2 << DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0xFE7CB391D650A284)
                Local0 = (Arg2 << DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0xFCF96723ACA14508)
            }

            Local0 = (Arg2 << DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 << DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0xFCF96723ACA14508)
            /* Method returns Integer */

            Local0 = (Arg2 << M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 << M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0xFCF96723ACA14508)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 << DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0xFE7CB391D650A284)
                Local0 = (Arg2 << DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0xFCF96723ACA14508)
            }

            /* Conversion of the second operand */

            Store ((0x00 << Arg3), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0x01 << Arg3), Local0)
            M600 (Arg0, 0x19, Local0, 0x0800)
            Store ((AUI5 << Arg3), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUI6 << Arg3), Local0)
            M600 (Arg0, 0x1B, Local0, 0x0800)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) << Arg3), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUI6)) << Arg3), Local0)
                M600 (Arg0, 0x1D, Local0, 0x0800)
            }

            Store ((DerefOf (PAUI [0x05]) << Arg3), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x06]) << Arg3), Local0)
            M600 (Arg0, 0x1F, Local0, 0x0800)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) << Arg3), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x06) << Arg3), Local0)
            M600 (Arg0, 0x21, Local0, 0x0800)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) << Arg3), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) << Arg3), Local0)
                M600 (Arg0, 0x23, Local0, 0x0800)
            }

            Local0 = (0x00 << Arg3)
            M600 (Arg0, 0x24, Local0, 0x00)
            Local0 = (0x01 << Arg3)
            M600 (Arg0, 0x25, Local0, 0x0800)
            Local0 = (AUI5 << Arg3)
            M600 (Arg0, 0x26, Local0, 0x00)
            Local0 = (AUI6 << Arg3)
            M600 (Arg0, 0x27, Local0, 0x0800)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) << Arg3)
                M600 (Arg0, 0x28, Local0, 0x00)
                Local0 = (DerefOf (RefOf (AUI6)) << Arg3)
                M600 (Arg0, 0x29, Local0, 0x0800)
            }

            Local0 = (DerefOf (PAUI [0x05]) << Arg3)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Local0 = (DerefOf (PAUI [0x06]) << Arg3)
            M600 (Arg0, 0x2B, Local0, 0x0800)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) << Arg3)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Local0 = (M601 (0x01, 0x06) << Arg3)
            M600 (Arg0, 0x2D, Local0, 0x0800)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) << Arg3)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) << Arg3)
                M600 (Arg0, 0x2F, Local0, 0x0800)
            }

            /* Conversion of the both operands */

            Store ((Arg1 << Arg3), Local0)
            M600 (Arg0, 0x30, Local0, 0x00190800)
            Store ((Arg2 << Arg3), Local0)
            M600 (Arg0, 0x31, Local0, 0xE59C8EB285142000)
            Local0 = (Arg1 << Arg3)
            M600 (Arg0, 0x32, Local0, 0x00190800)
            Local0 = (Arg2 << Arg3)
            M600 (Arg0, 0x33, Local0, 0xE59C8EB285142000)
        }

        /* ShiftLeft, 32-bit */

        Method (M01B, 4, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 << 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0xC179B3FE)
            Store ((Arg2 << 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0x82F367FC)
            Store ((Arg2 << AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0xC179B3FE)
            Store ((Arg2 << AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0x82F367FC)
            If (Y078)
            {
                Store ((Arg2 << DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0xC179B3FE)
                Store ((Arg2 << DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0x82F367FC)
            }

            Store ((Arg2 << DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0xC179B3FE)
            Store ((Arg2 << DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0x82F367FC)
            /* Method returns Integer */

            Store ((Arg2 << M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0xC179B3FE)
            Store ((Arg2 << M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0x82F367FC)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 << DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xC179B3FE)
                Store ((Arg2 << DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x82F367FC)
            }

            Local0 = (Arg2 << 0x00)
            M600 (Arg0, 0x0C, Local0, 0xC179B3FE)
            Local0 = (Arg2 << 0x01)
            M600 (Arg0, 0x0D, Local0, 0x82F367FC)
            Local0 = (Arg2 << AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0xC179B3FE)
            Local0 = (Arg2 << AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0x82F367FC)
            If (Y078)
            {
                Local0 = (Arg2 << DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0xC179B3FE)
                Local0 = (Arg2 << DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0x82F367FC)
            }

            Local0 = (Arg2 << DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0xC179B3FE)
            Local0 = (Arg2 << DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0x82F367FC)
            /* Method returns Integer */

            Local0 = (Arg2 << M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0xC179B3FE)
            Local0 = (Arg2 << M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0x82F367FC)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 << DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0xC179B3FE)
                Local0 = (Arg2 << DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0x82F367FC)
            }

            /* Conversion of the second operand */

            Store ((0x00 << Arg3), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0x01 << Arg3), Local0)
            M600 (Arg0, 0x19, Local0, 0x0800)
            Store ((AUI5 << Arg3), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUI6 << Arg3), Local0)
            M600 (Arg0, 0x1B, Local0, 0x0800)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) << Arg3), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUI6)) << Arg3), Local0)
                M600 (Arg0, 0x1D, Local0, 0x0800)
            }

            Store ((DerefOf (PAUI [0x05]) << Arg3), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x06]) << Arg3), Local0)
            M600 (Arg0, 0x1F, Local0, 0x0800)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) << Arg3), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x06) << Arg3), Local0)
            M600 (Arg0, 0x21, Local0, 0x0800)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) << Arg3), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) << Arg3), Local0)
                M600 (Arg0, 0x23, Local0, 0x0800)
            }

            Local0 = (0x00 << Arg3)
            M600 (Arg0, 0x24, Local0, 0x00)
            Local0 = (0x01 << Arg3)
            M600 (Arg0, 0x25, Local0, 0x0800)
            Local0 = (AUI5 << Arg3)
            M600 (Arg0, 0x26, Local0, 0x00)
            Local0 = (AUI6 << Arg3)
            M600 (Arg0, 0x27, Local0, 0x0800)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) << Arg3)
                M600 (Arg0, 0x28, Local0, 0x00)
                Local0 = (DerefOf (RefOf (AUI6)) << Arg3)
                M600 (Arg0, 0x29, Local0, 0x0800)
            }

            Local0 = (DerefOf (PAUI [0x05]) << Arg3)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Local0 = (DerefOf (PAUI [0x06]) << Arg3)
            M600 (Arg0, 0x2B, Local0, 0x0800)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) << Arg3)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Local0 = (M601 (0x01, 0x06) << Arg3)
            M600 (Arg0, 0x2D, Local0, 0x0800)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) << Arg3)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) << Arg3)
                M600 (Arg0, 0x2F, Local0, 0x0800)
            }

            /* Conversion of the both operands */

            Store ((Arg1 << Arg3), Local0)
            M600 (Arg0, 0x30, Local0, 0x00190800)
            Store ((Arg2 << Arg3), Local0)
            M600 (Arg0, 0x31, Local0, 0xCD9FF000)
            Local0 = (Arg1 << Arg3)
            M600 (Arg0, 0x32, Local0, 0x00190800)
            Local0 = (Arg2 << Arg3)
            M600 (Arg0, 0x33, Local0, 0xCD9FF000)
        }

        /* ShiftRight, common 32-bit/64-bit test */

        Method (M01C, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg1 >> 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0x0321)
            Store ((Arg1 >> 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0x0190)
            Store ((Arg1 >> AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0x0321)
            Store ((Arg1 >> AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0x0190)
            If (Y078)
            {
                Store ((Arg1 >> DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0x0321)
                Store ((Arg1 >> DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0x0190)
            }

            Store ((Arg1 >> DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0x0321)
            Store ((Arg1 >> DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0x0190)
            /* Method returns Integer */

            Store ((Arg1 >> M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0x0321)
            Store ((Arg1 >> M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0x0190)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg1 >> DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0x0321)
                Store ((Arg1 >> DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x0190)
            }

            Local0 = (Arg1 >> 0x00)
            M600 (Arg0, 0x0C, Local0, 0x0321)
            Local0 = (Arg1 >> 0x01)
            M600 (Arg0, 0x0D, Local0, 0x0190)
            Local0 = (Arg1 >> AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0x0321)
            Local0 = (Arg1 >> AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0x0190)
            If (Y078)
            {
                Local0 = (Arg1 >> DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0x0321)
                Local0 = (Arg1 >> DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0x0190)
            }

            Local0 = (Arg1 >> DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0x0321)
            Local0 = (Arg1 >> DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0x0190)
            /* Method returns Integer */

            Local0 = (Arg1 >> M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0x0321)
            Local0 = (Arg1 >> M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0x0190)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg1 >> DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0x0321)
                Local0 = (Arg1 >> DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0x0190)
            }

            /* Conversion of the second operand */

            Store ((0x0321 >> Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0xC179B3FE >> Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0x00182F36)
            Store ((AUI1 >> Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUI3 >> Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0x00182F36)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI1)) >> Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUI3)) >> Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0x00182F36)
            }

            Store ((DerefOf (PAUI [0x01]) >> Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x03]) >> Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0x00182F36)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x01) >> Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x03) >> Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0x00182F36)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x01, 0x01)) >> Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x03, 0x01)) >> Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0x00182F36)
            }

            Local0 = (0x0321 >> Arg2)
            M600 (Arg0, 0x24, Local0, 0x00)
            Local0 = (0xC179B3FE >> Arg2)
            M600 (Arg0, 0x25, Local0, 0x00182F36)
            Local0 = (AUI1 >> Arg2)
            M600 (Arg0, 0x26, Local0, 0x00)
            Local0 = (AUI3 >> Arg2)
            M600 (Arg0, 0x27, Local0, 0x00182F36)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI1)) >> Arg2)
                M600 (Arg0, 0x28, Local0, 0x00)
                Local0 = (DerefOf (RefOf (AUI3)) >> Arg2)
                M600 (Arg0, 0x29, Local0, 0x00182F36)
            }

            Local0 = (DerefOf (PAUI [0x01]) >> Arg2)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Local0 = (DerefOf (PAUI [0x03]) >> Arg2)
            M600 (Arg0, 0x2B, Local0, 0x00182F36)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x01) >> Arg2)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Local0 = (M601 (0x01, 0x03) >> Arg2)
            M600 (Arg0, 0x2D, Local0, 0x00182F36)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x01, 0x01)) >> Arg2)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Local0 = (DerefOf (M602 (0x01, 0x03, 0x01)) >> Arg2)
                M600 (Arg0, 0x2F, Local0, 0x00182F36)
            }
        }

        /* ShiftRight, 64-bit */

        Method (M01D, 4, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 >> 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 >> 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0x7F3E59C8EB285142)
            Store ((Arg2 >> AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 >> AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0x7F3E59C8EB285142)
            If (Y078)
            {
                Store ((Arg2 >> DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 >> DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0x7F3E59C8EB285142)
            }

            Store ((Arg2 >> DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 >> DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0x7F3E59C8EB285142)
            /* Method returns Integer */

            Store ((Arg2 >> M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 >> M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0x7F3E59C8EB285142)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 >> DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 >> DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x7F3E59C8EB285142)
            }

            Local0 = (Arg2 >> 0x00)
            M600 (Arg0, 0x0C, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 >> 0x01)
            M600 (Arg0, 0x0D, Local0, 0x7F3E59C8EB285142)
            Local0 = (Arg2 >> AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 >> AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0x7F3E59C8EB285142)
            If (Y078)
            {
                Local0 = (Arg2 >> DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0xFE7CB391D650A284)
                Local0 = (Arg2 >> DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0x7F3E59C8EB285142)
            }

            Local0 = (Arg2 >> DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 >> DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0x7F3E59C8EB285142)
            /* Method returns Integer */

            Local0 = (Arg2 >> M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 >> M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0x7F3E59C8EB285142)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 >> DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0xFE7CB391D650A284)
                Local0 = (Arg2 >> DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0x7F3E59C8EB285142)
            }

            /* Conversion of the second operand */

            Store ((0x0321 >> Arg3), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0xFE7CB391D650A284 >> Arg3), Local0)
            M600 (Arg0, 0x19, Local0, 0x001FCF96723ACA14)
            Store ((AUI1 >> Arg3), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUI4 >> Arg3), Local0)
            M600 (Arg0, 0x1B, Local0, 0x001FCF96723ACA14)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI1)) >> Arg3), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUI4)) >> Arg3), Local0)
                M600 (Arg0, 0x1D, Local0, 0x001FCF96723ACA14)
            }

            Store ((DerefOf (PAUI [0x01]) >> Arg3), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x04]) >> Arg3), Local0)
            M600 (Arg0, 0x1F, Local0, 0x001FCF96723ACA14)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x01) >> Arg3), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x04) >> Arg3), Local0)
            M600 (Arg0, 0x21, Local0, 0x001FCF96723ACA14)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x01, 0x01)) >> Arg3), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x04, 0x01)) >> Arg3), Local0)
                M600 (Arg0, 0x23, Local0, 0x001FCF96723ACA14)
            }

            Local0 = (0x0321 >> Arg3)
            M600 (Arg0, 0x24, Local0, 0x00)
            Local0 = (0xFE7CB391D650A284 >> Arg3)
            M600 (Arg0, 0x25, Local0, 0x001FCF96723ACA14)
            Local0 = (AUI1 >> Arg3)
            M600 (Arg0, 0x26, Local0, 0x00)
            Local0 = (AUI4 >> Arg3)
            M600 (Arg0, 0x27, Local0, 0x001FCF96723ACA14)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI1)) >> Arg3)
                M600 (Arg0, 0x28, Local0, 0x00)
                Local0 = (DerefOf (RefOf (AUI4)) >> Arg3)
                M600 (Arg0, 0x29, Local0, 0x001FCF96723ACA14)
            }

            Local0 = (DerefOf (PAUI [0x01]) >> Arg3)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Local0 = (DerefOf (PAUI [0x04]) >> Arg3)
            M600 (Arg0, 0x2B, Local0, 0x001FCF96723ACA14)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x01) >> Arg3)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Local0 = (M601 (0x01, 0x04) >> Arg3)
            M600 (Arg0, 0x2D, Local0, 0x001FCF96723ACA14)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x01, 0x01)) >> Arg3)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Local0 = (DerefOf (M602 (0x01, 0x04, 0x01)) >> Arg3)
                M600 (Arg0, 0x2F, Local0, 0x001FCF96723ACA14)
            }

            /* Conversion of the both operands */

            Store ((Arg1 >> Arg3), Local0)
            M600 (Arg0, 0x30, Local0, 0x00)
            Store ((Arg2 >> Arg3), Local0)
            M600 (Arg0, 0x31, Local0, 0x001FCF96723ACA14)
            Local0 = (Arg1 >> Arg3)
            M600 (Arg0, 0x32, Local0, 0x00)
            Local0 = (Arg2 >> Arg3)
            M600 (Arg0, 0x33, Local0, 0x001FCF96723ACA14)
        }

        /* ShiftRight, 32-bit */

        Method (M01E, 4, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 >> 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0xC179B3FE)
            Store ((Arg2 >> 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0x60BCD9FF)
            Store ((Arg2 >> AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0xC179B3FE)
            Store ((Arg2 >> AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0x60BCD9FF)
            If (Y078)
            {
                Store ((Arg2 >> DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0xC179B3FE)
                Store ((Arg2 >> DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0x60BCD9FF)
            }

            Store ((Arg2 >> DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0xC179B3FE)
            Store ((Arg2 >> DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0x60BCD9FF)
            /* Method returns Integer */

            Store ((Arg2 >> M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0xC179B3FE)
            Store ((Arg2 >> M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0x60BCD9FF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 >> DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xC179B3FE)
                Store ((Arg2 >> DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x60BCD9FF)
            }

            Local0 = (Arg2 >> 0x00)
            M600 (Arg0, 0x0C, Local0, 0xC179B3FE)
            Local0 = (Arg2 >> 0x01)
            M600 (Arg0, 0x0D, Local0, 0x60BCD9FF)
            Local0 = (Arg2 >> AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0xC179B3FE)
            Local0 = (Arg2 >> AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0x60BCD9FF)
            If (Y078)
            {
                Local0 = (Arg2 >> DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0xC179B3FE)
                Local0 = (Arg2 >> DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0x60BCD9FF)
            }

            Local0 = (Arg2 >> DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0xC179B3FE)
            Local0 = (Arg2 >> DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0x60BCD9FF)
            /* Method returns Integer */

            Local0 = (Arg2 >> M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0xC179B3FE)
            Local0 = (Arg2 >> M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0x60BCD9FF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 >> DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0xC179B3FE)
                Local0 = (Arg2 >> DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0x60BCD9FF)
            }

            /* Conversion of the second operand */

            Store ((0x0321 >> Arg3), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0xC179B3FE >> Arg3), Local0)
            M600 (Arg0, 0x19, Local0, 0x00182F36)
            Store ((AUI1 >> Arg3), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUI3 >> Arg3), Local0)
            M600 (Arg0, 0x1B, Local0, 0x00182F36)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI1)) >> Arg3), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUI3)) >> Arg3), Local0)
                M600 (Arg0, 0x1D, Local0, 0x00182F36)
            }

            Store ((DerefOf (PAUI [0x01]) >> Arg3), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x03]) >> Arg3), Local0)
            M600 (Arg0, 0x1F, Local0, 0x00182F36)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x01) >> Arg3), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x03) >> Arg3), Local0)
            M600 (Arg0, 0x21, Local0, 0x00182F36)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x01, 0x01)) >> Arg3), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x03, 0x01)) >> Arg3), Local0)
                M600 (Arg0, 0x23, Local0, 0x00182F36)
            }

            Local0 = (0x0321 >> Arg3)
            M600 (Arg0, 0x24, Local0, 0x00)
            Local0 = (0xC179B3FE >> Arg3)
            M600 (Arg0, 0x25, Local0, 0x00182F36)
            Local0 = (AUI1 >> Arg3)
            M600 (Arg0, 0x26, Local0, 0x00)
            Local0 = (AUI3 >> Arg3)
            M600 (Arg0, 0x27, Local0, 0x00182F36)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI1)) >> Arg3)
                M600 (Arg0, 0x28, Local0, 0x00)
                Local0 = (DerefOf (RefOf (AUI3)) >> Arg3)
                M600 (Arg0, 0x29, Local0, 0x00182F36)
            }

            Local0 = (DerefOf (PAUI [0x01]) >> Arg3)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Local0 = (DerefOf (PAUI [0x03]) >> Arg3)
            M600 (Arg0, 0x2B, Local0, 0x00182F36)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x01) >> Arg3)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Local0 = (M601 (0x01, 0x03) >> Arg3)
            M600 (Arg0, 0x2D, Local0, 0x00182F36)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x01, 0x01)) >> Arg3)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Local0 = (DerefOf (M602 (0x01, 0x03, 0x01)) >> Arg3)
                M600 (Arg0, 0x2F, Local0, 0x00182F36)
            }

            /* Conversion of the both operands */

            Store ((Arg1 >> Arg3), Local0)
            M600 (Arg0, 0x30, Local0, 0x00)
            Store ((Arg2 >> Arg3), Local0)
            M600 (Arg0, 0x31, Local0, 0x00182F36)
            Local0 = (Arg1 >> Arg3)
            M600 (Arg0, 0x32, Local0, 0x00)
            Local0 = (Arg2 >> Arg3)
            M600 (Arg0, 0x33, Local0, 0x00182F36)
        }

        /* Subtract, common 32-bit/64-bit test */

        Method (M01F, 2, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg1 - 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0x0321)
            Store ((Arg1 - 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0x0320)
            Store ((Arg1 - AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0x0321)
            Store ((Arg1 - AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0x0320)
            If (Y078)
            {
                Store ((Arg1 - DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0x0321)
                Store ((Arg1 - DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0x0320)
            }

            Store ((Arg1 - DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0x0321)
            Store ((Arg1 - DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0x0320)
            /* Method returns Integer */

            Store ((Arg1 - M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0x0321)
            Store ((Arg1 - M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0x0320)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg1 - DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0x0321)
                Store ((Arg1 - DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x0320)
            }

            Local0 = (Arg1 - 0x00)
            M600 (Arg0, 0x0C, Local0, 0x0321)
            Local0 = (Arg1 - 0x01)
            M600 (Arg0, 0x0D, Local0, 0x0320)
            Local0 = (Arg1 - AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0x0321)
            Local0 = (Arg1 - AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0x0320)
            If (Y078)
            {
                Local0 = (Arg1 - DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0x0321)
                Local0 = (Arg1 - DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0x0320)
            }

            Local0 = (Arg1 - DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0x0321)
            Local0 = (Arg1 - DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0x0320)
            /* Method returns Integer */

            Local0 = (Arg1 - M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0x0321)
            Local0 = (Arg1 - M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0x0320)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg1 - DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0x0321)
                Local0 = (Arg1 - DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0x0320)
            }

            /* Conversion of the second operand */

            Store ((0x00 - Arg1), Local0)
            M600 (Arg0, 0x18, Local0, 0xFFFFFFFFFFFFFCDF)
            Store ((0x01 - Arg1), Local0)
            M600 (Arg0, 0x19, Local0, 0xFFFFFFFFFFFFFCE0)
            Store ((AUI5 - Arg1), Local0)
            M600 (Arg0, 0x1A, Local0, 0xFFFFFFFFFFFFFCDF)
            Store ((AUI6 - Arg1), Local0)
            M600 (Arg0, 0x1B, Local0, 0xFFFFFFFFFFFFFCE0)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) - Arg1), Local0)
                M600 (Arg0, 0x1C, Local0, 0xFFFFFFFFFFFFFCDF)
                Store ((DerefOf (RefOf (AUI6)) - Arg1), Local0)
                M600 (Arg0, 0x1D, Local0, 0xFFFFFFFFFFFFFCE0)
            }

            Store ((DerefOf (PAUI [0x05]) - Arg1), Local0)
            M600 (Arg0, 0x1E, Local0, 0xFFFFFFFFFFFFFCDF)
            Store ((DerefOf (PAUI [0x06]) - Arg1), Local0)
            M600 (Arg0, 0x1F, Local0, 0xFFFFFFFFFFFFFCE0)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) - Arg1), Local0)
            M600 (Arg0, 0x20, Local0, 0xFFFFFFFFFFFFFCDF)
            Store ((M601 (0x01, 0x06) - Arg1), Local0)
            M600 (Arg0, 0x21, Local0, 0xFFFFFFFFFFFFFCE0)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) - Arg1), Local0)
                M600 (Arg0, 0x22, Local0, 0xFFFFFFFFFFFFFCDF)
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) - Arg1), Local0)
                M600 (Arg0, 0x23, Local0, 0xFFFFFFFFFFFFFCE0)
            }

            Local0 = (0x00 - Arg1)
            M600 (Arg0, 0x24, Local0, 0xFFFFFFFFFFFFFCDF)
            Local0 = (0x01 - Arg1)
            M600 (Arg0, 0x25, Local0, 0xFFFFFFFFFFFFFCE0)
            Local0 = (AUI5 - Arg1)
            M600 (Arg0, 0x26, Local0, 0xFFFFFFFFFFFFFCDF)
            Local0 = (AUI6 - Arg1)
            M600 (Arg0, 0x27, Local0, 0xFFFFFFFFFFFFFCE0)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) - Arg1)
                M600 (Arg0, 0x28, Local0, 0xFFFFFFFFFFFFFCDF)
                Local0 = (DerefOf (RefOf (AUI6)) - Arg1)
                M600 (Arg0, 0x29, Local0, 0xFFFFFFFFFFFFFCE0)
            }

            Local0 = (DerefOf (PAUI [0x05]) - Arg1)
            M600 (Arg0, 0x2A, Local0, 0xFFFFFFFFFFFFFCDF)
            Local0 = (DerefOf (PAUI [0x06]) - Arg1)
            M600 (Arg0, 0x2B, Local0, 0xFFFFFFFFFFFFFCE0)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) - Arg1)
            M600 (Arg0, 0x2C, Local0, 0xFFFFFFFFFFFFFCDF)
            Local0 = (M601 (0x01, 0x06) - Arg1)
            M600 (Arg0, 0x2D, Local0, 0xFFFFFFFFFFFFFCE0)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) - Arg1)
                M600 (Arg0, 0x2E, Local0, 0xFFFFFFFFFFFFFCDF)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) - Arg1)
                M600 (Arg0, 0x2F, Local0, 0xFFFFFFFFFFFFFCE0)
            }
        }

        /* Subtract, 64-bit */

        Method (M020, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 - 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 - 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0xFE7CB391D650A283)
            Store ((Arg2 - AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 - AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0xFE7CB391D650A283)
            If (Y078)
            {
                Store ((Arg2 - DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 - DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0xFE7CB391D650A283)
            }

            Store ((Arg2 - DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 - DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0xFE7CB391D650A283)
            /* Method returns Integer */

            Store ((Arg2 - M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 - M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0xFE7CB391D650A283)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 - DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 - DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0xFE7CB391D650A283)
            }

            Local0 = (Arg2 - 0x00)
            M600 (Arg0, 0x0C, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 - 0x01)
            M600 (Arg0, 0x0D, Local0, 0xFE7CB391D650A283)
            Local0 = (Arg2 - AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 - AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0xFE7CB391D650A283)
            If (Y078)
            {
                Local0 = (Arg2 - DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0xFE7CB391D650A284)
                Local0 = (Arg2 - DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0xFE7CB391D650A283)
            }

            Local0 = (Arg2 - DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 - DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0xFE7CB391D650A283)
            /* Method returns Integer */

            Local0 = (Arg2 - M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 - M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0xFE7CB391D650A283)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 - DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0xFE7CB391D650A284)
                Local0 = (Arg2 - DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0xFE7CB391D650A283)
            }

            /* Conversion of the second operand */

            Store ((0x00 - Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0x01834C6E29AF5D7C)
            Store ((0x01 - Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0x01834C6E29AF5D7D)
            Store ((AUI5 - Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0x01834C6E29AF5D7C)
            Store ((AUI6 - Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0x01834C6E29AF5D7D)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) - Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0x01834C6E29AF5D7C)
                Store ((DerefOf (RefOf (AUI6)) - Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0x01834C6E29AF5D7D)
            }

            Store ((DerefOf (PAUI [0x05]) - Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0x01834C6E29AF5D7C)
            Store ((DerefOf (PAUI [0x06]) - Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0x01834C6E29AF5D7D)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) - Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0x01834C6E29AF5D7C)
            Store ((M601 (0x01, 0x06) - Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0x01834C6E29AF5D7D)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) - Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0x01834C6E29AF5D7C)
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) - Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0x01834C6E29AF5D7D)
            }

            Local0 = (0x00 - Arg2)
            M600 (Arg0, 0x24, Local0, 0x01834C6E29AF5D7C)
            Local0 = (0x01 - Arg2)
            M600 (Arg0, 0x25, Local0, 0x01834C6E29AF5D7D)
            Local0 = (AUI5 - Arg2)
            M600 (Arg0, 0x26, Local0, 0x01834C6E29AF5D7C)
            Local0 = (AUI6 - Arg2)
            M600 (Arg0, 0x27, Local0, 0x01834C6E29AF5D7D)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) - Arg2)
                M600 (Arg0, 0x28, Local0, 0x01834C6E29AF5D7C)
                Local0 = (DerefOf (RefOf (AUI6)) - Arg2)
                M600 (Arg0, 0x29, Local0, 0x01834C6E29AF5D7D)
            }

            Local0 = (DerefOf (PAUI [0x05]) - Arg2)
            M600 (Arg0, 0x2A, Local0, 0x01834C6E29AF5D7C)
            Local0 = (DerefOf (PAUI [0x06]) - Arg2)
            M600 (Arg0, 0x2B, Local0, 0x01834C6E29AF5D7D)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) - Arg2)
            M600 (Arg0, 0x2C, Local0, 0x01834C6E29AF5D7C)
            Local0 = (M601 (0x01, 0x06) - Arg2)
            M600 (Arg0, 0x2D, Local0, 0x01834C6E29AF5D7D)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) - Arg2)
                M600 (Arg0, 0x2E, Local0, 0x01834C6E29AF5D7C)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) - Arg2)
                M600 (Arg0, 0x2F, Local0, 0x01834C6E29AF5D7D)
            }

            /* Conversion of the both operands */

            Store ((Arg1 - Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0x01834C6E29AF609D)
            Store ((Arg2 - Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0xFE7CB391D6509F63)
            Local0 = (Arg1 - Arg2)
            M600 (Arg0, 0x32, Local0, 0x01834C6E29AF609D)
            Local0 = (Arg2 - Arg1)
            M600 (Arg0, 0x33, Local0, 0xFE7CB391D6509F63)
        }

        /* Subtract, 32-bit */

        Method (M021, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 - 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0xC179B3FE)
            Store ((Arg2 - 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0xC179B3FD)
            Store ((Arg2 - AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0xC179B3FE)
            Store ((Arg2 - AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0xC179B3FD)
            If (Y078)
            {
                Store ((Arg2 - DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0xC179B3FE)
                Store ((Arg2 - DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0xC179B3FD)
            }

            Store ((Arg2 - DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0xC179B3FE)
            Store ((Arg2 - DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0xC179B3FD)
            /* Method returns Integer */

            Store ((Arg2 - M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0xC179B3FE)
            Store ((Arg2 - M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0xC179B3FD)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 - DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xC179B3FE)
                Store ((Arg2 - DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0xC179B3FD)
            }

            Local0 = (Arg2 - 0x00)
            M600 (Arg0, 0x0C, Local0, 0xC179B3FE)
            Local0 = (Arg2 - 0x01)
            M600 (Arg0, 0x0D, Local0, 0xC179B3FD)
            Local0 = (Arg2 - AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0xC179B3FE)
            Local0 = (Arg2 - AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0xC179B3FD)
            If (Y078)
            {
                Local0 = (Arg2 - DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0xC179B3FE)
                Local0 = (Arg2 - DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0xC179B3FD)
            }

            Local0 = (Arg2 - DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0xC179B3FE)
            Local0 = (Arg2 - DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0xC179B3FD)
            /* Method returns Integer */

            Local0 = (Arg2 - M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0xC179B3FE)
            Local0 = (Arg2 - M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0xC179B3FD)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 - DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0xC179B3FE)
                Local0 = (Arg2 - DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0xC179B3FD)
            }

            /* Conversion of the second operand */

            Store ((0x00 - Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0x3E864C02)
            Store ((0x01 - Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0x3E864C03)
            Store ((AUI5 - Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0x3E864C02)
            Store ((AUI6 - Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0x3E864C03)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) - Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0x3E864C02)
                Store ((DerefOf (RefOf (AUI6)) - Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0x3E864C03)
            }

            Store ((DerefOf (PAUI [0x05]) - Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0x3E864C02)
            Store ((DerefOf (PAUI [0x06]) - Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0x3E864C03)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) - Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0x3E864C02)
            Store ((M601 (0x01, 0x06) - Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0x3E864C03)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) - Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0x3E864C02)
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) - Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0x3E864C03)
            }

            Local0 = (0x00 - Arg2)
            M600 (Arg0, 0x24, Local0, 0x3E864C02)
            Local0 = (0x01 - Arg2)
            M600 (Arg0, 0x25, Local0, 0x3E864C03)
            Local0 = (AUI5 - Arg2)
            M600 (Arg0, 0x26, Local0, 0x3E864C02)
            Local0 = (AUI6 - Arg2)
            M600 (Arg0, 0x27, Local0, 0x3E864C03)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) - Arg2)
                M600 (Arg0, 0x28, Local0, 0x3E864C02)
                Local0 = (DerefOf (RefOf (AUI6)) - Arg2)
                M600 (Arg0, 0x29, Local0, 0x3E864C03)
            }

            Local0 = (DerefOf (PAUI [0x05]) - Arg2)
            M600 (Arg0, 0x2A, Local0, 0x3E864C02)
            Local0 = (DerefOf (PAUI [0x06]) - Arg2)
            M600 (Arg0, 0x2B, Local0, 0x3E864C03)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) - Arg2)
            M600 (Arg0, 0x2C, Local0, 0x3E864C02)
            Local0 = (M601 (0x01, 0x06) - Arg2)
            M600 (Arg0, 0x2D, Local0, 0x3E864C03)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) - Arg2)
                M600 (Arg0, 0x2E, Local0, 0x3E864C02)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) - Arg2)
                M600 (Arg0, 0x2F, Local0, 0x3E864C03)
            }

            /* Conversion of the both operands */

            Store ((Arg1 - Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0x3E864F23)
            Store ((Arg2 - Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0xC179B0DD)
            Local0 = (Arg1 - Arg2)
            M600 (Arg0, 0x32, Local0, 0x3E864F23)
            Local0 = (Arg2 - Arg1)
            M600 (Arg0, 0x33, Local0, 0xC179B0DD)
        }

        /* XOr, common 32-bit/64-bit test */

        Method (M022, 2, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg1 ^ 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0x0321)
            Store ((Arg1 ^ 0xFFFFFFFFFFFFFFFF), Local0)
            M600 (Arg0, 0x01, Local0, 0xFFFFFFFFFFFFFCDE)
            Store ((Arg1 ^ AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0x0321)
            Store ((Arg1 ^ AUIJ), Local0)
            M600 (Arg0, 0x03, Local0, 0xFFFFFFFFFFFFFCDE)
            If (Y078)
            {
                Store ((Arg1 ^ DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0x0321)
                Store ((Arg1 ^ DerefOf (RefOf (AUIJ))), Local0)
                M600 (Arg0, 0x05, Local0, 0xFFFFFFFFFFFFFCDE)
            }

            Store ((Arg1 ^ DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0x0321)
            Store ((Arg1 ^ DerefOf (PAUI [0x13])), Local0)
            M600 (Arg0, 0x07, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Integer */

            Store ((Arg1 ^ M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0x0321)
            Store ((Arg1 ^ M601 (0x01, 0x13)), Local0)
            M600 (Arg0, 0x09, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg1 ^ DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0x0321)
                Store ((Arg1 ^ DerefOf (M602 (0x01, 0x13, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0xFFFFFFFFFFFFFCDE)
            }

            Local0 = (Arg1 ^ 0x00)
            M600 (Arg0, 0x0C, Local0, 0x0321)
            Local0 = (Arg1 ^ 0xFFFFFFFFFFFFFFFF)
            M600 (Arg0, 0x0D, Local0, 0xFFFFFFFFFFFFFCDE)
            Local0 = (Arg1 ^ AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0x0321)
            Local0 = (Arg1 ^ AUIJ) /* \AUIJ */
            M600 (Arg0, 0x0F, Local0, 0xFFFFFFFFFFFFFCDE)
            If (Y078)
            {
                Local0 = (Arg1 ^ DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0x0321)
                Local0 = (Arg1 ^ DerefOf (RefOf (AUIJ)))
                M600 (Arg0, 0x11, Local0, 0xFFFFFFFFFFFFFCDE)
            }

            Local0 = (Arg1 ^ DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0x0321)
            Local0 = (Arg1 ^ DerefOf (PAUI [0x13]))
            M600 (Arg0, 0x13, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Integer */

            Local0 = (Arg1 ^ M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0x0321)
            Local0 = (Arg1 ^ M601 (0x01, 0x13))
            M600 (Arg0, 0x15, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg1 ^ DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0x0321)
                Local0 = (Arg1 ^ DerefOf (M602 (0x01, 0x13, 0x01)))
                M600 (Arg0, 0x17, Local0, 0xFFFFFFFFFFFFFCDE)
            }

            /* Conversion of the second operand */

            Store ((0x00 ^ Arg1), Local0)
            M600 (Arg0, 0x18, Local0, 0x0321)
            Store ((0xFFFFFFFFFFFFFFFF ^ Arg1), Local0)
            M600 (Arg0, 0x19, Local0, 0xFFFFFFFFFFFFFCDE)
            Store ((AUI5 ^ Arg1), Local0)
            M600 (Arg0, 0x1A, Local0, 0x0321)
            Store ((AUIJ ^ Arg1), Local0)
            M600 (Arg0, 0x1B, Local0, 0xFFFFFFFFFFFFFCDE)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) ^ Arg1), Local0)
                M600 (Arg0, 0x1C, Local0, 0x0321)
                Store ((DerefOf (RefOf (AUIJ)) ^ Arg1), Local0)
                M600 (Arg0, 0x1D, Local0, 0xFFFFFFFFFFFFFCDE)
            }

            Store ((DerefOf (PAUI [0x05]) ^ Arg1), Local0)
            M600 (Arg0, 0x1E, Local0, 0x0321)
            Store ((DerefOf (PAUI [0x13]) ^ Arg1), Local0)
            M600 (Arg0, 0x1F, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) ^ Arg1), Local0)
            M600 (Arg0, 0x20, Local0, 0x0321)
            Store ((M601 (0x01, 0x13) ^ Arg1), Local0)
            M600 (Arg0, 0x21, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) ^ Arg1), Local0)
                M600 (Arg0, 0x22, Local0, 0x0321)
                Store ((DerefOf (M602 (0x01, 0x13, 0x01)) ^ Arg1), Local0)
                M600 (Arg0, 0x23, Local0, 0xFFFFFFFFFFFFFCDE)
            }

            Local0 = (0x00 ^ Arg1)
            M600 (Arg0, 0x24, Local0, 0x0321)
            Local0 = (0xFFFFFFFFFFFFFFFF ^ Arg1)
            M600 (Arg0, 0x25, Local0, 0xFFFFFFFFFFFFFCDE)
            Local0 = (AUI5 ^ Arg1)
            M600 (Arg0, 0x26, Local0, 0x0321)
            Local0 = (AUIJ ^ Arg1)
            M600 (Arg0, 0x27, Local0, 0xFFFFFFFFFFFFFCDE)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) ^ Arg1)
                M600 (Arg0, 0x28, Local0, 0x0321)
                Local0 = (DerefOf (RefOf (AUIJ)) ^ Arg1)
                M600 (Arg0, 0x29, Local0, 0xFFFFFFFFFFFFFCDE)
            }

            Local0 = (DerefOf (PAUI [0x05]) ^ Arg1)
            M600 (Arg0, 0x2A, Local0, 0x0321)
            Local0 = (DerefOf (PAUI [0x13]) ^ Arg1)
            M600 (Arg0, 0x2B, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) ^ Arg1)
            M600 (Arg0, 0x2C, Local0, 0x0321)
            Local0 = (M601 (0x01, 0x13) ^ Arg1)
            M600 (Arg0, 0x2D, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) ^ Arg1)
                M600 (Arg0, 0x2E, Local0, 0x0321)
                Local0 = (DerefOf (M602 (0x01, 0x13, 0x01)) ^ Arg1)
                M600 (Arg0, 0x2F, Local0, 0xFFFFFFFFFFFFFCDE)
            }
        }

        /* XOr, 64-bit */

        Method (M023, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 ^ 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 ^ 0xFFFFFFFFFFFFFFFF), Local0)
            M600 (Arg0, 0x01, Local0, 0x01834C6E29AF5D7B)
            Store ((Arg2 ^ AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 ^ AUIJ), Local0)
            M600 (Arg0, 0x03, Local0, 0x01834C6E29AF5D7B)
            If (Y078)
            {
                Store ((Arg2 ^ DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 ^ DerefOf (RefOf (AUIJ))), Local0)
                M600 (Arg0, 0x05, Local0, 0x01834C6E29AF5D7B)
            }

            Store ((Arg2 ^ DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 ^ DerefOf (PAUI [0x13])), Local0)
            M600 (Arg0, 0x07, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Integer */

            Store ((Arg2 ^ M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 ^ M601 (0x01, 0x13)), Local0)
            M600 (Arg0, 0x09, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 ^ DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 ^ DerefOf (M602 (0x01, 0x13, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x01834C6E29AF5D7B)
            }

            Local0 = (Arg2 ^ 0x00)
            M600 (Arg0, 0x0C, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 ^ 0xFFFFFFFFFFFFFFFF)
            M600 (Arg0, 0x0D, Local0, 0x01834C6E29AF5D7B)
            Local0 = (Arg2 ^ AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 ^ AUIJ) /* \AUIJ */
            M600 (Arg0, 0x0F, Local0, 0x01834C6E29AF5D7B)
            If (Y078)
            {
                Local0 = (Arg2 ^ DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0xFE7CB391D650A284)
                Local0 = (Arg2 ^ DerefOf (RefOf (AUIJ)))
                M600 (Arg0, 0x11, Local0, 0x01834C6E29AF5D7B)
            }

            Local0 = (Arg2 ^ DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 ^ DerefOf (PAUI [0x13]))
            M600 (Arg0, 0x13, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Integer */

            Local0 = (Arg2 ^ M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 ^ M601 (0x01, 0x13))
            M600 (Arg0, 0x15, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 ^ DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0xFE7CB391D650A284)
                Local0 = (Arg2 ^ DerefOf (M602 (0x01, 0x13, 0x01)))
                M600 (Arg0, 0x17, Local0, 0x01834C6E29AF5D7B)
            }

            /* Conversion of the second operand */

            Store ((0x00 ^ Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0xFE7CB391D650A284)
            Store ((0xFFFFFFFFFFFFFFFF ^ Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0x01834C6E29AF5D7B)
            Store ((AUI5 ^ Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0xFE7CB391D650A284)
            Store ((AUIJ ^ Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0x01834C6E29AF5D7B)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) ^ Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0xFE7CB391D650A284)
                Store ((DerefOf (RefOf (AUIJ)) ^ Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0x01834C6E29AF5D7B)
            }

            Store ((DerefOf (PAUI [0x05]) ^ Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0xFE7CB391D650A284)
            Store ((DerefOf (PAUI [0x13]) ^ Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) ^ Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0xFE7CB391D650A284)
            Store ((M601 (0x01, 0x13) ^ Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) ^ Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0xFE7CB391D650A284)
                Store ((DerefOf (M602 (0x01, 0x13, 0x01)) ^ Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0x01834C6E29AF5D7B)
            }

            Local0 = (0x00 ^ Arg2)
            M600 (Arg0, 0x24, Local0, 0xFE7CB391D650A284)
            Local0 = (0xFFFFFFFFFFFFFFFF ^ Arg2)
            M600 (Arg0, 0x25, Local0, 0x01834C6E29AF5D7B)
            Local0 = (AUI5 ^ Arg2)
            M600 (Arg0, 0x26, Local0, 0xFE7CB391D650A284)
            Local0 = (AUIJ ^ Arg2)
            M600 (Arg0, 0x27, Local0, 0x01834C6E29AF5D7B)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) ^ Arg2)
                M600 (Arg0, 0x28, Local0, 0xFE7CB391D650A284)
                Local0 = (DerefOf (RefOf (AUIJ)) ^ Arg2)
                M600 (Arg0, 0x29, Local0, 0x01834C6E29AF5D7B)
            }

            Local0 = (DerefOf (PAUI [0x05]) ^ Arg2)
            M600 (Arg0, 0x2A, Local0, 0xFE7CB391D650A284)
            Local0 = (DerefOf (PAUI [0x13]) ^ Arg2)
            M600 (Arg0, 0x2B, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) ^ Arg2)
            M600 (Arg0, 0x2C, Local0, 0xFE7CB391D650A284)
            Local0 = (M601 (0x01, 0x13) ^ Arg2)
            M600 (Arg0, 0x2D, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) ^ Arg2)
                M600 (Arg0, 0x2E, Local0, 0xFE7CB391D650A284)
                Local0 = (DerefOf (M602 (0x01, 0x13, 0x01)) ^ Arg2)
                M600 (Arg0, 0x2F, Local0, 0x01834C6E29AF5D7B)
            }

            /* Conversion of the both operands */

            Store ((Arg1 ^ Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0xFE7CB391D650A1A5)
            Store ((Arg2 ^ Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0xFE7CB391D650A1A5)
            Local0 = (Arg1 ^ Arg2)
            M600 (Arg0, 0x32, Local0, 0xFE7CB391D650A1A5)
            Local0 = (Arg2 ^ Arg1)
            M600 (Arg0, 0x33, Local0, 0xFE7CB391D650A1A5)
        }

        /* XOr, 32-bit */

        Method (M024, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 ^ 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0xC179B3FE)
            Store ((Arg2 ^ 0xFFFFFFFF), Local0)
            M600 (Arg0, 0x01, Local0, 0x3E864C01)
            Store ((Arg2 ^ AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0xC179B3FE)
            Store ((Arg2 ^ AUII), Local0)
            M600 (Arg0, 0x03, Local0, 0x3E864C01)
            If (Y078)
            {
                Store ((Arg2 ^ DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0xC179B3FE)
                Store ((Arg2 ^ DerefOf (RefOf (AUII))), Local0)
                M600 (Arg0, 0x05, Local0, 0x3E864C01)
            }

            Store ((Arg2 ^ DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0xC179B3FE)
            Store ((Arg2 ^ DerefOf (PAUI [0x12])), Local0)
            M600 (Arg0, 0x07, Local0, 0x3E864C01)
            /* Method returns Integer */

            Store ((Arg2 ^ M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0xC179B3FE)
            Store ((Arg2 ^ M601 (0x01, 0x12)), Local0)
            M600 (Arg0, 0x09, Local0, 0x3E864C01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 ^ DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xC179B3FE)
                Store ((Arg2 ^ DerefOf (M602 (0x01, 0x12, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x3E864C01)
            }

            Local0 = (Arg2 ^ 0x00)
            M600 (Arg0, 0x0C, Local0, 0xC179B3FE)
            Local0 = (Arg2 ^ 0xFFFFFFFF)
            M600 (Arg0, 0x0D, Local0, 0x3E864C01)
            Local0 = (Arg2 ^ AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0xC179B3FE)
            Local0 = (Arg2 ^ AUII) /* \AUII */
            M600 (Arg0, 0x0F, Local0, 0x3E864C01)
            If (Y078)
            {
                Local0 = (Arg2 ^ DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0xC179B3FE)
                Local0 = (Arg2 ^ DerefOf (RefOf (AUII)))
                M600 (Arg0, 0x11, Local0, 0x3E864C01)
            }

            Local0 = (Arg2 ^ DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0xC179B3FE)
            Local0 = (Arg2 ^ DerefOf (PAUI [0x12]))
            M600 (Arg0, 0x13, Local0, 0x3E864C01)
            /* Method returns Integer */

            Local0 = (Arg2 ^ M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0xC179B3FE)
            Local0 = (Arg2 ^ M601 (0x01, 0x12))
            M600 (Arg0, 0x15, Local0, 0x3E864C01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 ^ DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0xC179B3FE)
                Local0 = (Arg2 ^ DerefOf (M602 (0x01, 0x12, 0x01)))
                M600 (Arg0, 0x17, Local0, 0x3E864C01)
            }

            /* Conversion of the second operand */

            Store ((0x00 ^ Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0xC179B3FE)
            Store ((0xFFFFFFFF ^ Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0x3E864C01)
            Store ((AUI5 ^ Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0xC179B3FE)
            Store ((AUII ^ Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0x3E864C01)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) ^ Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0xC179B3FE)
                Store ((DerefOf (RefOf (AUII)) ^ Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0x3E864C01)
            }

            Store ((DerefOf (PAUI [0x05]) ^ Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0xC179B3FE)
            Store ((DerefOf (PAUI [0x12]) ^ Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0x3E864C01)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) ^ Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0xC179B3FE)
            Store ((M601 (0x01, 0x12) ^ Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0x3E864C01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) ^ Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0xC179B3FE)
                Store ((DerefOf (M602 (0x01, 0x12, 0x01)) ^ Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0x3E864C01)
            }

            Local0 = (0x00 ^ Arg2)
            M600 (Arg0, 0x24, Local0, 0xC179B3FE)
            Local0 = (0xFFFFFFFF ^ Arg2)
            M600 (Arg0, 0x25, Local0, 0x3E864C01)
            Local0 = (AUI5 ^ Arg2)
            M600 (Arg0, 0x26, Local0, 0xC179B3FE)
            Local0 = (AUII ^ Arg2)
            M600 (Arg0, 0x27, Local0, 0x3E864C01)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) ^ Arg2)
                M600 (Arg0, 0x28, Local0, 0xC179B3FE)
                Local0 = (DerefOf (RefOf (AUII)) ^ Arg2)
                M600 (Arg0, 0x29, Local0, 0x3E864C01)
            }

            Local0 = (DerefOf (PAUI [0x05]) ^ Arg2)
            M600 (Arg0, 0x2A, Local0, 0xC179B3FE)
            Local0 = (DerefOf (PAUI [0x12]) ^ Arg2)
            M600 (Arg0, 0x2B, Local0, 0x3E864C01)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) ^ Arg2)
            M600 (Arg0, 0x2C, Local0, 0xC179B3FE)
            Local0 = (M601 (0x01, 0x12) ^ Arg2)
            M600 (Arg0, 0x2D, Local0, 0x3E864C01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) ^ Arg2)
                M600 (Arg0, 0x2E, Local0, 0xC179B3FE)
                Local0 = (DerefOf (M602 (0x01, 0x12, 0x01)) ^ Arg2)
                M600 (Arg0, 0x2F, Local0, 0x3E864C01)
            }

            /* Conversion of the both operands */

            Store ((Arg1 ^ Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0xC179B0DF)
            Store ((Arg2 ^ Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0xC179B0DF)
            Local0 = (Arg1 ^ Arg2)
            M600 (Arg0, 0x32, Local0, 0xC179B0DF)
            Local0 = (Arg2 ^ Arg1)
            M600 (Arg0, 0x33, Local0, 0xC179B0DF)
        }

        /* Add, And, Divide, Mod, Multiply, NAnd, NOr, Or, */
        /* ShiftLeft, ShiftRight, Subtract, Xor */
        Method (M64D, 1, NotSerialized)
        {
            /* Add */

            Concatenate (Arg0, "-m001", Local0)
            SRMT (Local0)
            M001 (Local0, "0321")
            Concatenate (Arg0, "-m002", Local0)
            SRMT (Local0)
            M002 (Local0, "0321", "FE7CB391D650A284")
            /* And */

            Concatenate (Arg0, "-m004", Local0)
            SRMT (Local0)
            M004 (Local0, "0321")
            Concatenate (Arg0, "-m005", Local0)
            SRMT (Local0)
            M005 (Local0, "0321", "FE7CB391D650A284")
            /* Divide */

            Concatenate (Arg0, "-m007", Local0)
            SRMT (Local0)
            M007 (Local0, "0321")
            Concatenate (Arg0, "-m008", Local0)
            SRMT (Local0)
            M008 (Local0, "0321", "FE7CB391D650A284")
            /* Mod */

            Concatenate (Arg0, "-m00a", Local0)
            SRMT (Local0)
            M00A (Local0, "0321")
            Concatenate (Arg0, "-m00b", Local0)
            SRMT (Local0)
            M00B (Local0, "0321", "FE7CB391D650A284")
            /* Multiply */

            Concatenate (Arg0, "-m00d", Local0)
            SRMT (Local0)
            M00D (Local0, "0321")
            Concatenate (Arg0, "-m00e", Local0)
            SRMT (Local0)
            M00E (Local0, "0321", "FE7CB391D650A284")
            /* NAnd */

            Concatenate (Arg0, "-m010", Local0)
            SRMT (Local0)
            M010 (Local0, "0321")
            Concatenate (Arg0, "-m011", Local0)
            SRMT (Local0)
            M011 (Local0, "0321", "FE7CB391D650A284")
            /* NOr */

            Concatenate (Arg0, "-m013", Local0)
            SRMT (Local0)
            M013 (Local0, "0321")
            Concatenate (Arg0, "-m014", Local0)
            SRMT (Local0)
            M014 (Local0, "0321", "FE7CB391D650A284")
            /* Or */

            Concatenate (Arg0, "-m016", Local0)
            SRMT (Local0)
            M016 (Local0, "0321")
            Concatenate (Arg0, "-m017", Local0)
            SRMT (Local0)
            M017 (Local0, "0321", "FE7CB391D650A284")
            /* ShiftLeft */

            Concatenate (Arg0, "-m019", Local0)
            SRMT (Local0)
            M019 (Local0, "0321", "B")
            Concatenate (Arg0, "-m01a", Local0)
            SRMT (Local0)
            M01A (Local0, "0321", "FE7CB391D650A284", "B")
            /* ShiftRight */

            Concatenate (Arg0, "-m01c", Local0)
            SRMT (Local0)
            M01C (Local0, "0321", "B")
            Concatenate (Arg0, "-m01d", Local0)
            SRMT (Local0)
            M01D (Local0, "0321", "FE7CB391D650A284", "B")
            /* Subtract */

            Concatenate (Arg0, "-m01f", Local0)
            SRMT (Local0)
            M01F (Local0, "0321")
            Concatenate (Arg0, "-m020", Local0)
            SRMT (Local0)
            M020 (Local0, "0321", "FE7CB391D650A284")
            /* XOr */

            Concatenate (Arg0, "-m022", Local0)
            SRMT (Local0)
            M022 (Local0, "0321")
            Concatenate (Arg0, "-m023", Local0)
            SRMT (Local0)
            M023 (Local0, "0321", "FE7CB391D650A284")
        }

        Method (M32D, 1, NotSerialized)
        {
            /* Add */

            Concatenate (Arg0, "-m001", Local0)
            SRMT (Local0)
            M001 (Local0, "0321")
            Concatenate (Arg0, "-m003", Local0)
            SRMT (Local0)
            M003 (Local0, "0321", "C179B3FE")
            /* And */

            Concatenate (Arg0, "-m004", Local0)
            SRMT (Local0)
            M004 (Local0, "0321")
            Concatenate (Arg0, "-m006", Local0)
            SRMT (Local0)
            M006 (Local0, "0321", "C179B3FE")
            /* Divide */

            Concatenate (Arg0, "-m007", Local0)
            SRMT (Local0)
            M007 (Local0, "0321")
            Concatenate (Arg0, "-m009", Local0)
            SRMT (Local0)
            M009 (Local0, "0321", "C179B3FE")
            /* Mod */

            Concatenate (Arg0, "-m00a", Local0)
            SRMT (Local0)
            M00A (Local0, "0321")
            Concatenate (Arg0, "-m00c", Local0)
            SRMT (Local0)
            M00C (Local0, "0321", "C179B3FE")
            /* Multiply */

            Concatenate (Arg0, "-m00d", Local0)
            SRMT (Local0)
            M00D (Local0, "0321")
            Concatenate (Arg0, "-m00f", Local0)
            SRMT (Local0)
            M00F (Local0, "0321", "C179B3FE")
            /* NAnd */

            Concatenate (Arg0, "-m010", Local0)
            SRMT (Local0)
            If (Y119)
            {
                M010 (Local0, "0321")
            }
            Else
            {
                BLCK ()
            }

            Concatenate (Arg0, "-m012", Local0)
            SRMT (Local0)
            M012 (Local0, "0321", "C179B3FE")
            /* NOr */

            Concatenate (Arg0, "-m013", Local0)
            SRMT (Local0)
            If (Y119)
            {
                M013 (Local0, "0321")
            }
            Else
            {
                BLCK ()
            }

            Concatenate (Arg0, "-m015", Local0)
            SRMT (Local0)
            M015 (Local0, "0321", "C179B3FE")
            /* Or */

            Concatenate (Arg0, "-m016", Local0)
            SRMT (Local0)
            If (Y119)
            {
                M016 (Local0, "0321")
            }
            Else
            {
                BLCK ()
            }

            Concatenate (Arg0, "-m018", Local0)
            SRMT (Local0)
            M018 (Local0, "0321", "C179B3FE")
            /* ShiftLeft */

            Concatenate (Arg0, "-m019", Local0)
            SRMT (Local0)
            M019 (Local0, "0321", "B")
            Concatenate (Arg0, "-m01b", Local0)
            SRMT (Local0)
            M01B (Local0, "0321", "C179B3FE", "B")
            /* ShiftRight */

            Concatenate (Arg0, "-m01c", Local0)
            SRMT (Local0)
            M01C (Local0, "0321", "B")
            Concatenate (Arg0, "-m01e", Local0)
            SRMT (Local0)
            M01E (Local0, "0321", "C179B3FE", "B")
            /* Subtract */

            Concatenate (Arg0, "-m01f", Local0)
            SRMT (Local0)
            If (Y119)
            {
                M01F (Local0, "0321")
            }
            Else
            {
                BLCK ()
            }

            Concatenate (Arg0, "-m021", Local0)
            SRMT (Local0)
            M021 (Local0, "0321", "C179B3FE")
            /* XOr */

            Concatenate (Arg0, "-m022", Local0)
            SRMT (Local0)
            If (Y119)
            {
                M022 (Local0, "0321")
            }
            Else
            {
                BLCK ()
            }

            Concatenate (Arg0, "-m024", Local0)
            SRMT (Local0)
            M024 (Local0, "0321", "C179B3FE")
        }

        /* String to Integer conversion of each String operand */
        /* of the 2-parameter Logical Integer operators LAnd and LOr */
        /* LAnd, common 32-bit/64-bit test */
        Method (M025, 2, NotSerialized)
        {
            /* Conversion of the first operand */

            Local0 = (Arg1 && 0x00)
            M600 (Arg0, 0x00, Local0, Zero)
            Local0 = (Arg1 && 0x01)
            M600 (Arg0, 0x01, Local0, Ones)
            Local0 = (Arg1 && AUI5)
            M600 (Arg0, 0x02, Local0, Zero)
            Local0 = (Arg1 && AUI6)
            M600 (Arg0, 0x03, Local0, Ones)
            If (Y078)
            {
                Local0 = (Arg1 && DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x04, Local0, Zero)
                Local0 = (Arg1 && DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x05, Local0, Ones)
            }

            Local0 = (Arg1 && DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x06, Local0, Zero)
            Local0 = (Arg1 && DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x07, Local0, Ones)
            /* Method returns Integer */

            Local0 = (Arg1 && M601 (0x01, 0x05))
            M600 (Arg0, 0x08, Local0, Zero)
            Local0 = (Arg1 && M601 (0x01, 0x06))
            M600 (Arg0, 0x09, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg1 && DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x0A, Local0, Zero)
                Local0 = (Arg1 && DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x0B, Local0, Ones)
            }

            /* Conversion of the second operand */

            Local0 = (0x00 && Arg1)
            M600 (Arg0, 0x0C, Local0, Zero)
            Local0 = (0x01 && Arg1)
            M600 (Arg0, 0x0D, Local0, Ones)
            Local0 = (AUI5 && Arg1)
            M600 (Arg0, 0x0E, Local0, Zero)
            Local0 = (AUI6 && Arg1)
            M600 (Arg0, 0x0F, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) && Arg1)
                M600 (Arg0, 0x10, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUI6)) && Arg1)
                M600 (Arg0, 0x11, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x05]) && Arg1)
            M600 (Arg0, 0x12, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x06]) && Arg1)
            M600 (Arg0, 0x13, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) && Arg1)
            M600 (Arg0, 0x14, Local0, Zero)
            Local0 = (M601 (0x01, 0x06) && Arg1)
            M600 (Arg0, 0x15, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) && Arg1)
                M600 (Arg0, 0x16, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) && Arg1)
                M600 (Arg0, 0x17, Local0, Ones)
            }
        }

        /* LAnd, 64-bit */

        Method (M026, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Local0 = (Arg2 && 0x00)
            M600 (Arg0, 0x00, Local0, Zero)
            Local0 = (Arg2 && 0x01)
            M600 (Arg0, 0x01, Local0, Ones)
            Local0 = (Arg2 && AUI5)
            M600 (Arg0, 0x02, Local0, Zero)
            Local0 = (Arg2 && AUI6)
            M600 (Arg0, 0x03, Local0, Ones)
            If (Y078)
            {
                Local0 = (Arg2 && DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x04, Local0, Zero)
                Local0 = (Arg2 && DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x05, Local0, Ones)
            }

            Local0 = (Arg2 && DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x06, Local0, Zero)
            Local0 = (Arg2 && DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x07, Local0, Ones)
            /* Method returns Integer */

            Local0 = (Arg2 && M601 (0x01, 0x05))
            M600 (Arg0, 0x08, Local0, Zero)
            Local0 = (Arg2 && M601 (0x01, 0x06))
            M600 (Arg0, 0x09, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 && DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x0A, Local0, Zero)
                Local0 = (Arg2 && DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x0B, Local0, Ones)
            }

            /* Conversion of the second operand */

            Local0 = (0x00 && Arg2)
            M600 (Arg0, 0x0C, Local0, Zero)
            Local0 = (0x01 && Arg2)
            M600 (Arg0, 0x0D, Local0, Ones)
            Local0 = (AUI5 && Arg2)
            M600 (Arg0, 0x0E, Local0, Zero)
            Local0 = (AUI6 && Arg2)
            M600 (Arg0, 0x0F, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) && Arg2)
                M600 (Arg0, 0x10, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUI6)) && Arg2)
                M600 (Arg0, 0x11, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x05]) && Arg2)
            M600 (Arg0, 0x12, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x06]) && Arg2)
            M600 (Arg0, 0x13, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) && Arg2)
            M600 (Arg0, 0x14, Local0, Zero)
            Local0 = (M601 (0x01, 0x06) && Arg2)
            M600 (Arg0, 0x15, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) && Arg2)
                M600 (Arg0, 0x16, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) && Arg2)
                M600 (Arg0, 0x17, Local0, Ones)
            }

            /* Conversion of the both operands */

            Local0 = (Arg1 && Arg2)
            M600 (Arg0, 0x18, Local0, Ones)
            Local0 = (Arg2 && Arg1)
            M600 (Arg0, 0x19, Local0, Ones)
        }

        /* LAnd, 32-bit */

        Method (M027, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Local0 = (Arg2 && 0x00)
            M600 (Arg0, 0x00, Local0, Zero)
            Local0 = (Arg2 && 0x01)
            M600 (Arg0, 0x01, Local0, Ones)
            Local0 = (Arg2 && AUI5)
            M600 (Arg0, 0x02, Local0, Zero)
            Local0 = (Arg2 && AUI6)
            M600 (Arg0, 0x03, Local0, Ones)
            If (Y078)
            {
                Local0 = (Arg2 && DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x04, Local0, Zero)
                Local0 = (Arg2 && DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x05, Local0, Ones)
            }

            Local0 = (Arg2 && DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x06, Local0, Zero)
            Local0 = (Arg2 && DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x07, Local0, Ones)
            /* Method returns Integer */

            Local0 = (Arg2 && M601 (0x01, 0x05))
            M600 (Arg0, 0x08, Local0, Zero)
            Local0 = (Arg2 && M601 (0x01, 0x06))
            M600 (Arg0, 0x09, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 && DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x0A, Local0, Zero)
                Local0 = (Arg2 && DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x0B, Local0, Ones)
            }

            /* Conversion of the second operand */

            Local0 = (0x00 && Arg2)
            M600 (Arg0, 0x0C, Local0, Zero)
            Local0 = (0x01 && Arg2)
            M600 (Arg0, 0x0D, Local0, Ones)
            Local0 = (AUI5 && Arg2)
            M600 (Arg0, 0x0E, Local0, Zero)
            Local0 = (AUI6 && Arg2)
            M600 (Arg0, 0x0F, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) && Arg2)
                M600 (Arg0, 0x10, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUI6)) && Arg2)
                M600 (Arg0, 0x11, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x05]) && Arg2)
            M600 (Arg0, 0x12, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x06]) && Arg2)
            M600 (Arg0, 0x13, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) && Arg2)
            M600 (Arg0, 0x14, Local0, Zero)
            Local0 = (M601 (0x01, 0x06) && Arg2)
            M600 (Arg0, 0x15, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) && Arg2)
                M600 (Arg0, 0x16, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) && Arg2)
                M600 (Arg0, 0x17, Local0, Ones)
            }

            /* Conversion of the both operands */

            Local0 = (Arg1 && Arg2)
            M600 (Arg0, 0x18, Local0, Ones)
            Local0 = (Arg2 && Arg1)
            M600 (Arg0, 0x19, Local0, Ones)
        }

        /* Lor, common 32-bit/64-bit test */

        Method (M028, 2, NotSerialized)
        {
            /* Conversion of the first operand */

            Local0 = (Arg1 || 0x00)
            M600 (Arg0, 0x00, Local0, Zero)
            Local0 = (Arg1 || 0x01)
            M600 (Arg0, 0x01, Local0, Ones)
            Local0 = (Arg1 || AUI5)
            M600 (Arg0, 0x02, Local0, Zero)
            Local0 = (Arg1 || AUI6)
            M600 (Arg0, 0x03, Local0, Ones)
            If (Y078)
            {
                Local0 = (Arg1 || DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x04, Local0, Zero)
                Local0 = (Arg1 || DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x05, Local0, Ones)
            }

            Local0 = (Arg1 || DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x06, Local0, Zero)
            Local0 = (Arg1 || DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x07, Local0, Ones)
            /* Method returns Integer */

            Local0 = (Arg1 || M601 (0x01, 0x05))
            M600 (Arg0, 0x08, Local0, Zero)
            Local0 = (Arg1 || M601 (0x01, 0x06))
            M600 (Arg0, 0x09, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg1 || DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x0A, Local0, Zero)
                Local0 = (Arg1 || DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x0B, Local0, Ones)
            }

            /* Conversion of the second operand */

            Local0 = (0x00 || Arg1)
            M600 (Arg0, 0x0C, Local0, Zero)
            Local0 = (0x01 || Arg1)
            M600 (Arg0, 0x0D, Local0, Ones)
            Local0 = (AUI5 || Arg1)
            M600 (Arg0, 0x0E, Local0, Zero)
            Local0 = (AUI6 || Arg1)
            M600 (Arg0, 0x0F, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) || Arg1)
                M600 (Arg0, 0x10, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUI6)) || Arg1)
                M600 (Arg0, 0x11, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x05]) || Arg1)
            M600 (Arg0, 0x12, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x06]) || Arg1)
            M600 (Arg0, 0x13, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) || Arg1)
            M600 (Arg0, 0x14, Local0, Zero)
            Local0 = (M601 (0x01, 0x06) || Arg1)
            M600 (Arg0, 0x15, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) || Arg1)
                M600 (Arg0, 0x16, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) || Arg1)
                M600 (Arg0, 0x17, Local0, Ones)
            }
        }

        /* Lor, 64-bit */

        Method (M029, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Local0 = (Arg1 || 0x00)
            M600 (Arg0, 0x00, Local0, Ones)
            Local0 = (Arg1 || 0x01)
            M600 (Arg0, 0x01, Local0, Ones)
            Local0 = (Arg1 || AUI5)
            M600 (Arg0, 0x02, Local0, Ones)
            Local0 = (Arg1 || AUI6)
            M600 (Arg0, 0x03, Local0, Ones)
            If (Y078)
            {
                Local0 = (Arg1 || DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x04, Local0, Ones)
                Local0 = (Arg1 || DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x05, Local0, Ones)
            }

            Local0 = (Arg1 || DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x06, Local0, Ones)
            Local0 = (Arg1 || DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x07, Local0, Ones)
            /* Method returns Integer */

            Local0 = (Arg1 || M601 (0x01, 0x05))
            M600 (Arg0, 0x08, Local0, Ones)
            Local0 = (Arg1 || M601 (0x01, 0x06))
            M600 (Arg0, 0x09, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg1 || DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x0A, Local0, Ones)
                Local0 = (Arg1 || DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x0B, Local0, Ones)
            }

            /* Conversion of the second operand */

            Local0 = (0x00 || Arg1)
            M600 (Arg0, 0x0C, Local0, Ones)
            Local0 = (0x01 || Arg1)
            M600 (Arg0, 0x0D, Local0, Ones)
            Local0 = (AUI5 || Arg1)
            M600 (Arg0, 0x0E, Local0, Ones)
            Local0 = (AUI6 || Arg1)
            M600 (Arg0, 0x0F, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) || Arg1)
                M600 (Arg0, 0x10, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUI6)) || Arg1)
                M600 (Arg0, 0x11, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x05]) || Arg1)
            M600 (Arg0, 0x12, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x06]) || Arg1)
            M600 (Arg0, 0x13, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) || Arg1)
            M600 (Arg0, 0x14, Local0, Ones)
            Local0 = (M601 (0x01, 0x06) || Arg1)
            M600 (Arg0, 0x15, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) || Arg1)
                M600 (Arg0, 0x16, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) || Arg1)
                M600 (Arg0, 0x17, Local0, Ones)
            }

            /* Conversion of the both operands */

            Local0 = (Arg2 || Arg1)
            M600 (Arg0, 0x18, Local0, Ones)
            Local0 = (Arg1 || Arg2)
            M600 (Arg0, 0x19, Local0, Ones)
        }

        /* Lor, 32-bit */

        Method (M02A, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Local0 = (Arg1 || 0x00)
            M600 (Arg0, 0x00, Local0, Ones)
            Local0 = (Arg1 || 0x01)
            M600 (Arg0, 0x01, Local0, Ones)
            Local0 = (Arg1 || AUI5)
            M600 (Arg0, 0x02, Local0, Ones)
            Local0 = (Arg1 || AUI6)
            M600 (Arg0, 0x03, Local0, Ones)
            If (Y078)
            {
                Local0 = (Arg1 || DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x04, Local0, Ones)
                Local0 = (Arg1 || DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x05, Local0, Ones)
            }

            Local0 = (Arg1 || DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x06, Local0, Ones)
            Local0 = (Arg1 || DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x07, Local0, Ones)
            /* Method returns Integer */

            Local0 = (Arg1 || M601 (0x01, 0x05))
            M600 (Arg0, 0x08, Local0, Ones)
            Local0 = (Arg1 || M601 (0x01, 0x06))
            M600 (Arg0, 0x09, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg1 || DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x0A, Local0, Ones)
                Local0 = (Arg1 || DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x0B, Local0, Ones)
            }

            /* Conversion of the second operand */

            Local0 = (0x00 || Arg1)
            M600 (Arg0, 0x0C, Local0, Ones)
            Local0 = (0x01 || Arg1)
            M600 (Arg0, 0x0D, Local0, Ones)
            Local0 = (AUI5 || Arg1)
            M600 (Arg0, 0x0E, Local0, Ones)
            Local0 = (AUI6 || Arg1)
            M600 (Arg0, 0x0F, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) || Arg1)
                M600 (Arg0, 0x10, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUI6)) || Arg1)
                M600 (Arg0, 0x11, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x05]) || Arg1)
            M600 (Arg0, 0x12, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x06]) || Arg1)
            M600 (Arg0, 0x13, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) || Arg1)
            M600 (Arg0, 0x14, Local0, Ones)
            Local0 = (M601 (0x01, 0x06) || Arg1)
            M600 (Arg0, 0x15, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) || Arg1)
                M600 (Arg0, 0x16, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) || Arg1)
                M600 (Arg0, 0x17, Local0, Ones)
            }

            /* Conversion of the both operands */

            Local0 = (Arg2 || Arg1)
            M600 (Arg0, 0x18, Local0, Ones)
            Local0 = (Arg1 || Arg2)
            M600 (Arg0, 0x19, Local0, Ones)
        }

        Method (M64E, 1, NotSerialized)
        {
            /* LAnd */

            Concatenate (Arg0, "-m025", Local0)
            SRMT (Local0)
            M025 (Local0, "0321")
            Concatenate (Arg0, "-m026", Local0)
            SRMT (Local0)
            M026 (Local0, "0321", "FE7CB391D650A284")
            /* LOr */

            Concatenate (Arg0, "-m028", Local0)
            SRMT (Local0)
            M028 (Local0, "0")
            Concatenate (Arg0, "-m029", Local0)
            SRMT (Local0)
            M029 (Local0, "FE7CB391D650A284", "0")
        }

        Method (M32E, 1, NotSerialized)
        {
            /* LAnd */

            Concatenate (Arg0, "-m025", Local0)
            SRMT (Local0)
            M025 (Local0, "0321")
            Concatenate (Arg0, "-m027", Local0)
            SRMT (Local0)
            M027 (Local0, "0321", "C179B3FE")
            /* LOr */

            Concatenate (Arg0, "-m028", Local0)
            SRMT (Local0)
            M028 (Local0, "0")
            Concatenate (Arg0, "-m02a", Local0)
            SRMT (Local0)
            M02A (Local0, "C179B3FE", "0")
        }

        /* String to Integer conversion of the String second operand of */
        /* Logical operators when the first operand is evaluated as Integer */
        /* (LEqual, LGreater, LGreaterEqual, LLess, LLessEqual, LNotEqual) */
        Method (M64F, 2, NotSerialized)
        {
            /* LEqual */

            Local0 = (0xFE7CB391D650A284 == Arg1)
            M600 (Arg0, 0x00, Local0, Ones)
            Local0 = (0xFE7CB391D650A285 == Arg1)
            M600 (Arg0, 0x01, Local0, Zero)
            Local0 = (0xFE7CB391D650A283 == Arg1)
            M600 (Arg0, 0x02, Local0, Zero)
            Local0 = (AUI4 == Arg1)
            M600 (Arg0, 0x03, Local0, Ones)
            Local0 = (AUID == Arg1)
            M600 (Arg0, 0x04, Local0, Zero)
            Local0 = (AUIF == Arg1)
            M600 (Arg0, 0x05, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI4)) == Arg1)
                M600 (Arg0, 0x06, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUID)) == Arg1)
                M600 (Arg0, 0x07, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIF)) == Arg1)
                M600 (Arg0, 0x08, Local0, Zero)
            }

            Local0 = (DerefOf (PAUI [0x04]) == Arg1)
            M600 (Arg0, 0x09, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x0D]) == Arg1)
            M600 (Arg0, 0x0A, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x0F]) == Arg1)
            M600 (Arg0, 0x0B, Local0, Zero)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x04) == Arg1)
            M600 (Arg0, 0x0C, Local0, Ones)
            Local0 = (M601 (0x01, 0x0D) == Arg1)
            M600 (Arg0, 0x0D, Local0, Zero)
            Local0 = (M601 (0x01, 0x0F) == Arg1)
            M600 (Arg0, 0x0E, Local0, Zero)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x04, 0x01)) == Arg1)
                M600 (Arg0, 0x0F, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x0D, 0x01)) == Arg1)
                M600 (Arg0, 0x10, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x0F, 0x01)) == Arg1)
                M600 (Arg0, 0x11, Local0, Zero)
            }

            /* LGreater */

            Local0 = (0xFE7CB391D650A284 > Arg1)
            M600 (Arg0, 0x12, Local0, Zero)
            Local0 = (0xFE7CB391D650A285 > Arg1)
            M600 (Arg0, 0x13, Local0, Ones)
            Local0 = (0xFE7CB391D650A283 > Arg1)
            M600 (Arg0, 0x14, Local0, Zero)
            Local0 = (AUI4 > Arg1)
            M600 (Arg0, 0x15, Local0, Zero)
            Local0 = (AUID > Arg1)
            M600 (Arg0, 0x16, Local0, Ones)
            Local0 = (AUIF > Arg1)
            M600 (Arg0, 0x17, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI4)) > Arg1)
                M600 (Arg0, 0x18, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUID)) > Arg1)
                M600 (Arg0, 0x19, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIF)) > Arg1)
                M600 (Arg0, 0x1A, Local0, Zero)
            }

            Local0 = (DerefOf (PAUI [0x04]) > Arg1)
            M600 (Arg0, 0x1B, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x0D]) > Arg1)
            M600 (Arg0, 0x1C, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x0F]) > Arg1)
            M600 (Arg0, 0x1D, Local0, Zero)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x04) > Arg1)
            M600 (Arg0, 0x1E, Local0, Zero)
            Local0 = (M601 (0x01, 0x0D) > Arg1)
            M600 (Arg0, 0x1F, Local0, Ones)
            Local0 = (M601 (0x01, 0x0F) > Arg1)
            M600 (Arg0, 0x20, Local0, Zero)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x04, 0x01)) > Arg1)
                M600 (Arg0, 0x21, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x0D, 0x01)) > Arg1)
                M600 (Arg0, 0x22, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x0F, 0x01)) > Arg1)
                M600 (Arg0, 0x23, Local0, Zero)
            }

            /* LGreaterEqual */

            Local0 = (0xFE7CB391D650A284 >= Arg1)
            M600 (Arg0, 0x24, Local0, Ones)
            Local0 = (0xFE7CB391D650A285 >= Arg1)
            M600 (Arg0, 0x25, Local0, Ones)
            Local0 = (0xFE7CB391D650A283 >= Arg1)
            M600 (Arg0, 0x26, Local0, Zero)
            Local0 = (AUI4 >= Arg1)
            M600 (Arg0, 0x27, Local0, Ones)
            Local0 = (AUID >= Arg1)
            M600 (Arg0, 0x28, Local0, Ones)
            Local0 = (AUIF >= Arg1)
            M600 (Arg0, 0x29, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI4)) >= Arg1)
                M600 (Arg0, 0x2A, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUID)) >= Arg1)
                M600 (Arg0, 0x2B, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIF)) >= Arg1)
                M600 (Arg0, 0x2C, Local0, Zero)
            }

            Local0 = (DerefOf (PAUI [0x04]) >= Arg1)
            M600 (Arg0, 0x2D, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x0D]) >= Arg1)
            M600 (Arg0, 0x2E, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x0F]) >= Arg1)
            M600 (Arg0, 0x2F, Local0, Zero)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x04) >= Arg1)
            M600 (Arg0, 0x30, Local0, Ones)
            Local0 = (M601 (0x01, 0x0D) >= Arg1)
            M600 (Arg0, 0x31, Local0, Ones)
            Local0 = (M601 (0x01, 0x0F) >= Arg1)
            M600 (Arg0, 0x32, Local0, Zero)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x04, 0x01)) >= Arg1)
                M600 (Arg0, 0x33, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x0D, 0x01)) >= Arg1)
                M600 (Arg0, 0x34, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x0F, 0x01)) >= Arg1)
                M600 (Arg0, 0x35, Local0, Zero)
            }

            /* LLess */

            Local0 = (0xFE7CB391D650A284 < Arg1)
            M600 (Arg0, 0x36, Local0, Zero)
            Local0 = (0xFE7CB391D650A285 < Arg1)
            M600 (Arg0, 0x37, Local0, Zero)
            Local0 = (0xFE7CB391D650A283 < Arg1)
            M600 (Arg0, 0x38, Local0, Ones)
            Local0 = (AUI4 < Arg1)
            M600 (Arg0, 0x39, Local0, Zero)
            Local0 = (AUID < Arg1)
            M600 (Arg0, 0x3A, Local0, Zero)
            Local0 = (AUIF < Arg1)
            M600 (Arg0, 0x3B, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI4)) < Arg1)
                M600 (Arg0, 0x3C, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUID)) < Arg1)
                M600 (Arg0, 0x3D, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIF)) < Arg1)
                M600 (Arg0, 0x3E, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x04]) < Arg1)
            M600 (Arg0, 0x3F, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x0D]) < Arg1)
            M600 (Arg0, 0x40, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x0F]) < Arg1)
            M600 (Arg0, 0x41, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x04) < Arg1)
            M600 (Arg0, 0x42, Local0, Zero)
            Local0 = (M601 (0x01, 0x0D) < Arg1)
            M600 (Arg0, 0x43, Local0, Zero)
            Local0 = (M601 (0x01, 0x0F) < Arg1)
            M600 (Arg0, 0x44, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x04, 0x01)) < Arg1)
                M600 (Arg0, 0x45, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x0D, 0x01)) < Arg1)
                M600 (Arg0, 0x46, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x0F, 0x01)) < Arg1)
                M600 (Arg0, 0x47, Local0, Ones)
            }

            /* LLessEqual */

            Local0 = (0xFE7CB391D650A284 <= Arg1)
            M600 (Arg0, 0x48, Local0, Ones)
            Local0 = (0xFE7CB391D650A285 <= Arg1)
            M600 (Arg0, 0x49, Local0, Zero)
            Local0 = (0xFE7CB391D650A283 <= Arg1)
            M600 (Arg0, 0x4A, Local0, Ones)
            Local0 = (AUI4 <= Arg1)
            M600 (Arg0, 0x4B, Local0, Ones)
            Local0 = (AUID <= Arg1)
            M600 (Arg0, 0x4C, Local0, Zero)
            Local0 = (AUIF <= Arg1)
            M600 (Arg0, 0x4D, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI4)) <= Arg1)
                M600 (Arg0, 0x4E, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUID)) <= Arg1)
                M600 (Arg0, 0x4F, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIF)) <= Arg1)
                M600 (Arg0, 0x50, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x04]) <= Arg1)
            M600 (Arg0, 0x51, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x0D]) <= Arg1)
            M600 (Arg0, 0x52, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x0F]) <= Arg1)
            M600 (Arg0, 0x53, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x04) <= Arg1)
            M600 (Arg0, 0x54, Local0, Ones)
            Local0 = (M601 (0x01, 0x0D) <= Arg1)
            M600 (Arg0, 0x55, Local0, Zero)
            Local0 = (M601 (0x01, 0x0F) <= Arg1)
            M600 (Arg0, 0x56, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x04, 0x01)) <= Arg1)
                M600 (Arg0, 0x57, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x0D, 0x01)) <= Arg1)
                M600 (Arg0, 0x58, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x0F, 0x01)) <= Arg1)
                M600 (Arg0, 0x59, Local0, Ones)
            }

            /* LNotEqual */

            Local0 = (0xFE7CB391D650A284 != Arg1)
            M600 (Arg0, 0x5A, Local0, Zero)
            Local0 = (0xFE7CB391D650A285 != Arg1)
            M600 (Arg0, 0x5B, Local0, Ones)
            Local0 = (0xFE7CB391D650A283 != Arg1)
            M600 (Arg0, 0x5C, Local0, Ones)
            Local0 = (AUI4 != Arg1)
            M600 (Arg0, 0x5D, Local0, Zero)
            Local0 = (AUID != Arg1)
            M600 (Arg0, 0x5E, Local0, Ones)
            Local0 = (AUIF != Arg1)
            M600 (Arg0, 0x5F, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI4)) != Arg1)
                M600 (Arg0, 0x60, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUID)) != Arg1)
                M600 (Arg0, 0x61, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIF)) != Arg1)
                M600 (Arg0, 0x62, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x04]) != Arg1)
            M600 (Arg0, 0x63, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x0D]) != Arg1)
            M600 (Arg0, 0x64, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x0F]) != Arg1)
            M600 (Arg0, 0x65, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x04) != Arg1)
            M600 (Arg0, 0x66, Local0, Zero)
            Local0 = (M601 (0x01, 0x0D) != Arg1)
            M600 (Arg0, 0x67, Local0, Ones)
            Local0 = (M601 (0x01, 0x0F) != Arg1)
            M600 (Arg0, 0x68, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x04, 0x01)) != Arg1)
                M600 (Arg0, 0x69, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x0D, 0x01)) != Arg1)
                M600 (Arg0, 0x6A, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x0F, 0x01)) != Arg1)
                M600 (Arg0, 0x6B, Local0, Ones)
            }
        }

        Method (M32F, 2, NotSerialized)
        {
            /* LEqual */

            Local0 = (0xC179B3FE == Arg1)
            M600 (Arg0, 0x00, Local0, Ones)
            Local0 = (0xC179B3FF == Arg1)
            M600 (Arg0, 0x01, Local0, Zero)
            Local0 = (0xC179B3FD == Arg1)
            M600 (Arg0, 0x02, Local0, Zero)
            Local0 = (AUI3 == Arg1)
            M600 (Arg0, 0x03, Local0, Ones)
            Local0 = (AUIC == Arg1)
            M600 (Arg0, 0x04, Local0, Zero)
            Local0 = (AUIE == Arg1)
            M600 (Arg0, 0x05, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI3)) == Arg1)
                M600 (Arg0, 0x06, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIC)) == Arg1)
                M600 (Arg0, 0x07, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIE)) == Arg1)
                M600 (Arg0, 0x08, Local0, Zero)
            }

            Local0 = (DerefOf (PAUI [0x03]) == Arg1)
            M600 (Arg0, 0x09, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x0C]) == Arg1)
            M600 (Arg0, 0x0A, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x0E]) == Arg1)
            M600 (Arg0, 0x0B, Local0, Zero)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x03) == Arg1)
            M600 (Arg0, 0x0C, Local0, Ones)
            Local0 = (M601 (0x01, 0x0C) == Arg1)
            M600 (Arg0, 0x0D, Local0, Zero)
            Local0 = (M601 (0x01, 0x0E) == Arg1)
            M600 (Arg0, 0x0E, Local0, Zero)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x03, 0x01)) == Arg1)
                M600 (Arg0, 0x0F, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x0C, 0x01)) == Arg1)
                M600 (Arg0, 0x10, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x0E, 0x01)) == Arg1)
                M600 (Arg0, 0x11, Local0, Zero)
            }

            /* LGreater */

            Local0 = (0xC179B3FE > Arg1)
            M600 (Arg0, 0x12, Local0, Zero)
            Local0 = (0xC179B3FF > Arg1)
            M600 (Arg0, 0x13, Local0, Ones)
            Local0 = (0xC179B3FD > Arg1)
            M600 (Arg0, 0x14, Local0, Zero)
            Local0 = (AUI3 > Arg1)
            M600 (Arg0, 0x15, Local0, Zero)
            Local0 = (AUIC > Arg1)
            M600 (Arg0, 0x16, Local0, Ones)
            Local0 = (AUIE > Arg1)
            M600 (Arg0, 0x17, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI3)) > Arg1)
                M600 (Arg0, 0x18, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIC)) > Arg1)
                M600 (Arg0, 0x19, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIE)) > Arg1)
                M600 (Arg0, 0x1A, Local0, Zero)
            }

            Local0 = (DerefOf (PAUI [0x03]) > Arg1)
            M600 (Arg0, 0x1B, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x0C]) > Arg1)
            M600 (Arg0, 0x1C, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x0E]) > Arg1)
            M600 (Arg0, 0x1D, Local0, Zero)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x03) > Arg1)
            M600 (Arg0, 0x1E, Local0, Zero)
            Local0 = (M601 (0x01, 0x0C) > Arg1)
            M600 (Arg0, 0x1F, Local0, Ones)
            Local0 = (M601 (0x01, 0x0E) > Arg1)
            M600 (Arg0, 0x20, Local0, Zero)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x03, 0x01)) > Arg1)
                M600 (Arg0, 0x21, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x0C, 0x01)) > Arg1)
                M600 (Arg0, 0x22, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x0E, 0x01)) > Arg1)
                M600 (Arg0, 0x23, Local0, Zero)
            }

            /* LGreaterEqual */

            Local0 = (0xC179B3FE >= Arg1)
            M600 (Arg0, 0x24, Local0, Ones)
            Local0 = (0xC179B3FF >= Arg1)
            M600 (Arg0, 0x25, Local0, Ones)
            Local0 = (0xC179B3FD >= Arg1)
            M600 (Arg0, 0x26, Local0, Zero)
            Local0 = (AUI3 >= Arg1)
            M600 (Arg0, 0x27, Local0, Ones)
            Local0 = (AUIC >= Arg1)
            M600 (Arg0, 0x28, Local0, Ones)
            Local0 = (AUIE >= Arg1)
            M600 (Arg0, 0x29, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI3)) >= Arg1)
                M600 (Arg0, 0x2A, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIC)) >= Arg1)
                M600 (Arg0, 0x2B, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIE)) >= Arg1)
                M600 (Arg0, 0x2C, Local0, Zero)
            }

            Local0 = (DerefOf (PAUI [0x03]) >= Arg1)
            M600 (Arg0, 0x2D, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x0C]) >= Arg1)
            M600 (Arg0, 0x2E, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x0E]) >= Arg1)
            M600 (Arg0, 0x2F, Local0, Zero)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x03) >= Arg1)
            M600 (Arg0, 0x30, Local0, Ones)
            Local0 = (M601 (0x01, 0x0C) >= Arg1)
            M600 (Arg0, 0x31, Local0, Ones)
            Local0 = (M601 (0x01, 0x0E) >= Arg1)
            M600 (Arg0, 0x32, Local0, Zero)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x03, 0x01)) >= Arg1)
                M600 (Arg0, 0x33, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x0C, 0x01)) >= Arg1)
                M600 (Arg0, 0x34, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x0E, 0x01)) >= Arg1)
                M600 (Arg0, 0x35, Local0, Zero)
            }

            /* LLess */

            Local0 = (0xC179B3FE < Arg1)
            M600 (Arg0, 0x36, Local0, Zero)
            Local0 = (0xC179B3FF < Arg1)
            M600 (Arg0, 0x37, Local0, Zero)
            Local0 = (0xC179B3FD < Arg1)
            M600 (Arg0, 0x38, Local0, Ones)
            Local0 = (AUI3 < Arg1)
            M600 (Arg0, 0x39, Local0, Zero)
            Local0 = (AUIC < Arg1)
            M600 (Arg0, 0x3A, Local0, Zero)
            Local0 = (AUIE < Arg1)
            M600 (Arg0, 0x3B, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI3)) < Arg1)
                M600 (Arg0, 0x3C, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIC)) < Arg1)
                M600 (Arg0, 0x3D, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIE)) < Arg1)
                M600 (Arg0, 0x3E, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x03]) < Arg1)
            M600 (Arg0, 0x3F, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x0C]) < Arg1)
            M600 (Arg0, 0x40, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x0E]) < Arg1)
            M600 (Arg0, 0x41, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x03) < Arg1)
            M600 (Arg0, 0x42, Local0, Zero)
            Local0 = (M601 (0x01, 0x0C) < Arg1)
            M600 (Arg0, 0x43, Local0, Zero)
            Local0 = (M601 (0x01, 0x0E) < Arg1)
            M600 (Arg0, 0x44, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x03, 0x01)) < Arg1)
                M600 (Arg0, 0x45, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x0C, 0x01)) < Arg1)
                M600 (Arg0, 0x46, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x0E, 0x01)) < Arg1)
                M600 (Arg0, 0x47, Local0, Ones)
            }

            /* LLessEqual */

            Local0 = (0xC179B3FE <= Arg1)
            M600 (Arg0, 0x48, Local0, Ones)
            Local0 = (0xC179B3FF <= Arg1)
            M600 (Arg0, 0x49, Local0, Zero)
            Local0 = (0xC179B3FD <= Arg1)
            M600 (Arg0, 0x4A, Local0, Ones)
            Local0 = (AUI3 <= Arg1)
            M600 (Arg0, 0x4B, Local0, Ones)
            Local0 = (AUIC <= Arg1)
            M600 (Arg0, 0x4C, Local0, Zero)
            Local0 = (AUIE <= Arg1)
            M600 (Arg0, 0x4D, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI3)) <= Arg1)
                M600 (Arg0, 0x4E, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIC)) <= Arg1)
                M600 (Arg0, 0x4F, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIE)) <= Arg1)
                M600 (Arg0, 0x50, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x03]) <= Arg1)
            M600 (Arg0, 0x51, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x0C]) <= Arg1)
            M600 (Arg0, 0x52, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x0E]) <= Arg1)
            M600 (Arg0, 0x53, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x03) <= Arg1)
            M600 (Arg0, 0x54, Local0, Ones)
            Local0 = (M601 (0x01, 0x0C) <= Arg1)
            M600 (Arg0, 0x55, Local0, Zero)
            Local0 = (M601 (0x01, 0x0E) <= Arg1)
            M600 (Arg0, 0x56, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x03, 0x01)) <= Arg1)
                M600 (Arg0, 0x57, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x0C, 0x01)) <= Arg1)
                M600 (Arg0, 0x58, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x0E, 0x01)) <= Arg1)
                M600 (Arg0, 0x59, Local0, Ones)
            }

            /* LNotEqual */

            Local0 = (0xC179B3FE != Arg1)
            M600 (Arg0, 0x5A, Local0, Zero)
            Local0 = (0xC179B3FF != Arg1)
            M600 (Arg0, 0x5B, Local0, Ones)
            Local0 = (0xC179B3FD != Arg1)
            M600 (Arg0, 0x5C, Local0, Ones)
            Local0 = (AUI3 != Arg1)
            M600 (Arg0, 0x5D, Local0, Zero)
            Local0 = (AUIC != Arg1)
            M600 (Arg0, 0x5E, Local0, Ones)
            Local0 = (AUIE != Arg1)
            M600 (Arg0, 0x5F, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI3)) != Arg1)
                M600 (Arg0, 0x60, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIC)) != Arg1)
                M600 (Arg0, 0x61, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIE)) != Arg1)
                M600 (Arg0, 0x62, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x03]) != Arg1)
            M600 (Arg0, 0x63, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x0C]) != Arg1)
            M600 (Arg0, 0x64, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x0E]) != Arg1)
            M600 (Arg0, 0x65, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x03) != Arg1)
            M600 (Arg0, 0x66, Local0, Zero)
            Local0 = (M601 (0x01, 0x0C) != Arg1)
            M600 (Arg0, 0x67, Local0, Ones)
            Local0 = (M601 (0x01, 0x0E) != Arg1)
            M600 (Arg0, 0x68, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x03, 0x01)) != Arg1)
                M600 (Arg0, 0x69, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x0C, 0x01)) != Arg1)
                M600 (Arg0, 0x6A, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x0E, 0x01)) != Arg1)
                M600 (Arg0, 0x6B, Local0, Ones)
            }
        }

        Method (M02B, 2, NotSerialized)
        {
            /* LEqual */

            Local0 = (0x0321 == Arg1)
            M600 (Arg0, 0x00, Local0, Ones)
            Local0 = (0x0322 == Arg1)
            M600 (Arg0, 0x01, Local0, Zero)
            Local0 = (0x0320 == Arg1)
            M600 (Arg0, 0x02, Local0, Zero)
            Local0 = (AUI1 == Arg1)
            M600 (Arg0, 0x03, Local0, Ones)
            Local0 = (AUIG == Arg1)
            M600 (Arg0, 0x04, Local0, Zero)
            Local0 = (AUIH == Arg1)
            M600 (Arg0, 0x05, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI1)) == Arg1)
                M600 (Arg0, 0x06, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIG)) == Arg1)
                M600 (Arg0, 0x07, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIH)) == Arg1)
                M600 (Arg0, 0x08, Local0, Zero)
            }

            Local0 = (DerefOf (PAUI [0x01]) == Arg1)
            M600 (Arg0, 0x09, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x10]) == Arg1)
            M600 (Arg0, 0x0A, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x11]) == Arg1)
            M600 (Arg0, 0x0B, Local0, Zero)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x01) == Arg1)
            M600 (Arg0, 0x0C, Local0, Ones)
            Local0 = (M601 (0x01, 0x10) == Arg1)
            M600 (Arg0, 0x0D, Local0, Zero)
            Local0 = (M601 (0x01, 0x11) == Arg1)
            M600 (Arg0, 0x0E, Local0, Zero)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x01, 0x01)) == Arg1)
                M600 (Arg0, 0x0F, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x10, 0x01)) == Arg1)
                M600 (Arg0, 0x10, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x11, 0x01)) == Arg1)
                M600 (Arg0, 0x11, Local0, Zero)
            }

            /* LGreater */

            Local0 = (0x0321 > Arg1)
            M600 (Arg0, 0x12, Local0, Zero)
            Local0 = (0x0322 > Arg1)
            M600 (Arg0, 0x13, Local0, Ones)
            Local0 = (0x0320 > Arg1)
            M600 (Arg0, 0x14, Local0, Zero)
            Local0 = (AUI1 > Arg1)
            M600 (Arg0, 0x15, Local0, Zero)
            Local0 = (AUIG > Arg1)
            M600 (Arg0, 0x16, Local0, Ones)
            Local0 = (AUIH > Arg1)
            M600 (Arg0, 0x17, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI1)) > Arg1)
                M600 (Arg0, 0x18, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIG)) > Arg1)
                M600 (Arg0, 0x19, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIH)) > Arg1)
                M600 (Arg0, 0x1A, Local0, Zero)
            }

            Local0 = (DerefOf (PAUI [0x01]) > Arg1)
            M600 (Arg0, 0x1B, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x10]) > Arg1)
            M600 (Arg0, 0x1C, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x11]) > Arg1)
            M600 (Arg0, 0x1D, Local0, Zero)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x01) > Arg1)
            M600 (Arg0, 0x1E, Local0, Zero)
            Local0 = (M601 (0x01, 0x10) > Arg1)
            M600 (Arg0, 0x1F, Local0, Ones)
            Local0 = (M601 (0x01, 0x11) > Arg1)
            M600 (Arg0, 0x20, Local0, Zero)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x01, 0x01)) > Arg1)
                M600 (Arg0, 0x21, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x10, 0x01)) > Arg1)
                M600 (Arg0, 0x22, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x11, 0x01)) > Arg1)
                M600 (Arg0, 0x23, Local0, Zero)
            }

            /* LGreaterEqual */

            Local0 = (0x0321 >= Arg1)
            M600 (Arg0, 0x24, Local0, Ones)
            Local0 = (0x0322 >= Arg1)
            M600 (Arg0, 0x25, Local0, Ones)
            Local0 = (0x0320 >= Arg1)
            M600 (Arg0, 0x26, Local0, Zero)
            Local0 = (AUI1 >= Arg1)
            M600 (Arg0, 0x27, Local0, Ones)
            Local0 = (AUIG >= Arg1)
            M600 (Arg0, 0x28, Local0, Ones)
            Local0 = (AUIH >= Arg1)
            M600 (Arg0, 0x29, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI1)) >= Arg1)
                M600 (Arg0, 0x2A, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIG)) >= Arg1)
                M600 (Arg0, 0x2B, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIH)) >= Arg1)
                M600 (Arg0, 0x2C, Local0, Zero)
            }

            Local0 = (DerefOf (PAUI [0x01]) >= Arg1)
            M600 (Arg0, 0x2D, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x10]) >= Arg1)
            M600 (Arg0, 0x2E, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x11]) >= Arg1)
            M600 (Arg0, 0x2F, Local0, Zero)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x01) >= Arg1)
            M600 (Arg0, 0x30, Local0, Ones)
            Local0 = (M601 (0x01, 0x10) >= Arg1)
            M600 (Arg0, 0x31, Local0, Ones)
            Local0 = (M601 (0x01, 0x11) >= Arg1)
            M600 (Arg0, 0x32, Local0, Zero)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x01, 0x01)) >= Arg1)
                M600 (Arg0, 0x33, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x10, 0x01)) >= Arg1)
                M600 (Arg0, 0x34, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x11, 0x01)) >= Arg1)
                M600 (Arg0, 0x35, Local0, Zero)
            }

            /* LLess */

            Local0 = (0x0321 < Arg1)
            M600 (Arg0, 0x36, Local0, Zero)
            Local0 = (0x0322 < Arg1)
            M600 (Arg0, 0x37, Local0, Zero)
            Local0 = (0x0320 < Arg1)
            M600 (Arg0, 0x38, Local0, Ones)
            Local0 = (AUI1 < Arg1)
            M600 (Arg0, 0x39, Local0, Zero)
            Local0 = (AUIG < Arg1)
            M600 (Arg0, 0x3A, Local0, Zero)
            Local0 = (AUIH < Arg1)
            M600 (Arg0, 0x3B, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI1)) < Arg1)
                M600 (Arg0, 0x3C, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIG)) < Arg1)
                M600 (Arg0, 0x3D, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIH)) < Arg1)
                M600 (Arg0, 0x3E, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x01]) < Arg1)
            M600 (Arg0, 0x3F, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x10]) < Arg1)
            M600 (Arg0, 0x40, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x11]) < Arg1)
            M600 (Arg0, 0x41, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x01) < Arg1)
            M600 (Arg0, 0x42, Local0, Zero)
            Local0 = (M601 (0x01, 0x10) < Arg1)
            M600 (Arg0, 0x43, Local0, Zero)
            Local0 = (M601 (0x01, 0x11) < Arg1)
            M600 (Arg0, 0x44, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x01, 0x01)) < Arg1)
                M600 (Arg0, 0x45, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x10, 0x01)) < Arg1)
                M600 (Arg0, 0x46, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x11, 0x01)) < Arg1)
                M600 (Arg0, 0x47, Local0, Ones)
            }

            /* LLessEqual */

            Local0 = (0x0321 <= Arg1)
            M600 (Arg0, 0x48, Local0, Ones)
            Local0 = (0x0322 <= Arg1)
            M600 (Arg0, 0x49, Local0, Zero)
            Local0 = (0x0320 <= Arg1)
            M600 (Arg0, 0x4A, Local0, Ones)
            Local0 = (AUI1 <= Arg1)
            M600 (Arg0, 0x4B, Local0, Ones)
            Local0 = (AUIG <= Arg1)
            M600 (Arg0, 0x4C, Local0, Zero)
            Local0 = (AUIH <= Arg1)
            M600 (Arg0, 0x4D, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI1)) <= Arg1)
                M600 (Arg0, 0x4E, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIG)) <= Arg1)
                M600 (Arg0, 0x4F, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIH)) <= Arg1)
                M600 (Arg0, 0x50, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x01]) <= Arg1)
            M600 (Arg0, 0x51, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x10]) <= Arg1)
            M600 (Arg0, 0x52, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x11]) <= Arg1)
            M600 (Arg0, 0x53, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x01) <= Arg1)
            M600 (Arg0, 0x54, Local0, Ones)
            Local0 = (M601 (0x01, 0x10) <= Arg1)
            M600 (Arg0, 0x55, Local0, Zero)
            Local0 = (M601 (0x01, 0x11) <= Arg1)
            M600 (Arg0, 0x56, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x01, 0x01)) <= Arg1)
                M600 (Arg0, 0x57, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x10, 0x01)) <= Arg1)
                M600 (Arg0, 0x58, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x11, 0x01)) <= Arg1)
                M600 (Arg0, 0x59, Local0, Ones)
            }

            /* LNotEqual */

            Local0 = (0x0321 != Arg1)
            M600 (Arg0, 0x5A, Local0, Zero)
            Local0 = (0x0322 != Arg1)
            M600 (Arg0, 0x5B, Local0, Ones)
            Local0 = (0x0320 != Arg1)
            M600 (Arg0, 0x5C, Local0, Ones)
            Local0 = (AUI1 != Arg1)
            M600 (Arg0, 0x5D, Local0, Zero)
            Local0 = (AUIG != Arg1)
            M600 (Arg0, 0x5E, Local0, Ones)
            Local0 = (AUIH != Arg1)
            M600 (Arg0, 0x5F, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI1)) != Arg1)
                M600 (Arg0, 0x60, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIG)) != Arg1)
                M600 (Arg0, 0x61, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIH)) != Arg1)
                M600 (Arg0, 0x62, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x01]) != Arg1)
            M600 (Arg0, 0x63, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x10]) != Arg1)
            M600 (Arg0, 0x64, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x11]) != Arg1)
            M600 (Arg0, 0x65, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x01) != Arg1)
            M600 (Arg0, 0x66, Local0, Zero)
            Local0 = (M601 (0x01, 0x10) != Arg1)
            M600 (Arg0, 0x67, Local0, Ones)
            Local0 = (M601 (0x01, 0x11) != Arg1)
            M600 (Arg0, 0x68, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x01, 0x01)) != Arg1)
                M600 (Arg0, 0x69, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x10, 0x01)) != Arg1)
                M600 (Arg0, 0x6A, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x11, 0x01)) != Arg1)
                M600 (Arg0, 0x6B, Local0, Ones)
            }
        }

        /* String to Integer intermediate conversion of the String second */
        /* operand of Concatenate operator in case the first one is Integer */
        Method (M64G, 3, NotSerialized)
        {
            Local0 = Concatenate (0x0321, Arg1)
            M600 (Arg0, 0x00, Local0, BB26)
            Local0 = Concatenate (0x0321, Arg2)
            M600 (Arg0, 0x01, Local0, BB21)
            Local0 = Concatenate (AUI1, Arg1)
            M600 (Arg0, 0x02, Local0, BB26)
            Local0 = Concatenate (AUI1, Arg2)
            M600 (Arg0, 0x03, Local0, BB21)
            If (Y078)
            {
                Local0 = Concatenate (DerefOf (RefOf (AUI1)), Arg1)
                M600 (Arg0, 0x04, Local0, BB26)
                Local0 = Concatenate (DerefOf (RefOf (AUI1)), Arg2)
                M600 (Arg0, 0x05, Local0, BB21)
            }

            Local0 = Concatenate (DerefOf (PAUI [0x01]), Arg1)
            M600 (Arg0, 0x06, Local0, BB26)
            Local0 = Concatenate (DerefOf (PAUI [0x01]), Arg2)
            M600 (Arg0, 0x07, Local0, BB21)
            /* Method returns Integer */

            Local0 = Concatenate (M601 (0x01, 0x01), Arg1)
            M600 (Arg0, 0x08, Local0, BB26)
            Local0 = Concatenate (M601 (0x01, 0x01), Arg2)
            M600 (Arg0, 0x09, Local0, BB21)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = Concatenate (DerefOf (M602 (0x01, 0x01, 0x01)), Arg1)
                M600 (Arg0, 0x0A, Local0, BB26)
                Local0 = Concatenate (DerefOf (M602 (0x01, 0x01, 0x01)), Arg2)
                M600 (Arg0, 0x0B, Local0, BB21)
            }

            Concatenate (0x0321, Arg1, Local0)
            M600 (Arg0, 0x0C, Local0, BB26)
            Concatenate (0x0321, Arg2, Local0)
            M600 (Arg0, 0x0D, Local0, BB21)
            Concatenate (AUI1, Arg1, Local0)
            M600 (Arg0, 0x0E, Local0, BB26)
            Concatenate (AUI1, Arg2, Local0)
            M600 (Arg0, 0x0F, Local0, BB21)
            If (Y078)
            {
                Concatenate (DerefOf (RefOf (AUI1)), Arg1, Local0)
                M600 (Arg0, 0x10, Local0, BB26)
                Concatenate (DerefOf (RefOf (AUI1)), Arg2, Local0)
                M600 (Arg0, 0x11, Local0, BB21)
            }

            Concatenate (DerefOf (PAUI [0x01]), Arg1, Local0)
            M600 (Arg0, 0x12, Local0, BB26)
            Concatenate (DerefOf (PAUI [0x01]), Arg2, Local0)
            M600 (Arg0, 0x13, Local0, BB21)
            /* Method returns Integer */

            Concatenate (M601 (0x01, 0x01), Arg1, Local0)
            M600 (Arg0, 0x14, Local0, BB26)
            Concatenate (M601 (0x01, 0x01), Arg2, Local0)
            M600 (Arg0, 0x15, Local0, BB21)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Concatenate (DerefOf (M602 (0x01, 0x01, 0x01)), Arg1, Local0)
                M600 (Arg0, 0x16, Local0, BB26)
                Concatenate (DerefOf (M602 (0x01, 0x01, 0x01)), Arg2, Local0)
                M600 (Arg0, 0x17, Local0, BB21)
            }
        }

        Method (M32G, 3, NotSerialized)
        {
            Local0 = Concatenate (0x0321, Arg1)
            M600 (Arg0, 0x00, Local0, BB27)
            Local0 = Concatenate (0x0321, Arg2)
            M600 (Arg0, 0x01, Local0, BB24)
            Local0 = Concatenate (AUI1, Arg1)
            M600 (Arg0, 0x02, Local0, BB27)
            Local0 = Concatenate (AUI1, Arg2)
            M600 (Arg0, 0x03, Local0, BB24)
            If (Y078)
            {
                Local0 = Concatenate (DerefOf (RefOf (AUI1)), Arg1)
                M600 (Arg0, 0x04, Local0, BB27)
                Local0 = Concatenate (DerefOf (RefOf (AUI1)), Arg2)
                M600 (Arg0, 0x05, Local0, BB24)
            }

            Local0 = Concatenate (DerefOf (PAUI [0x01]), Arg1)
            M600 (Arg0, 0x06, Local0, BB27)
            Local0 = Concatenate (DerefOf (PAUI [0x01]), Arg2)
            M600 (Arg0, 0x07, Local0, BB24)
            /* Method returns Integer */

            Local0 = Concatenate (M601 (0x01, 0x01), Arg1)
            M600 (Arg0, 0x08, Local0, BB27)
            Local0 = Concatenate (M601 (0x01, 0x01), Arg2)
            M600 (Arg0, 0x09, Local0, BB24)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = Concatenate (DerefOf (M602 (0x01, 0x01, 0x01)), Arg1)
                M600 (Arg0, 0x0A, Local0, BB27)
                Local0 = Concatenate (DerefOf (M602 (0x01, 0x01, 0x01)), Arg2)
                M600 (Arg0, 0x0B, Local0, BB24)
            }

            Concatenate (0x0321, Arg1, Local0)
            M600 (Arg0, 0x0C, Local0, BB27)
            Concatenate (0x0321, Arg2, Local0)
            M600 (Arg0, 0x0D, Local0, BB24)
            Concatenate (AUI1, Arg1, Local0)
            M600 (Arg0, 0x0E, Local0, BB27)
            Concatenate (AUI1, Arg2, Local0)
            M600 (Arg0, 0x0F, Local0, BB24)
            If (Y078)
            {
                Concatenate (DerefOf (RefOf (AUI1)), Arg1, Local0)
                M600 (Arg0, 0x10, Local0, BB27)
                Concatenate (DerefOf (RefOf (AUI1)), Arg2, Local0)
                M600 (Arg0, 0x11, Local0, BB24)
            }

            Concatenate (DerefOf (PAUI [0x01]), Arg1, Local0)
            M600 (Arg0, 0x12, Local0, BB27)
            Concatenate (DerefOf (PAUI [0x01]), Arg2, Local0)
            M600 (Arg0, 0x14, Local0, BB24)
            /* Method returns Integer */

            Concatenate (M601 (0x01, 0x01), Arg1, Local0)
            M600 (Arg0, 0x15, Local0, BB27)
            Concatenate (M601 (0x01, 0x01), Arg2, Local0)
            M600 (Arg0, 0x16, Local0, BB24)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Concatenate (DerefOf (M602 (0x01, 0x01, 0x01)), Arg1, Local0)
                M600 (Arg0, 0x17, Local0, BB27)
                Concatenate (DerefOf (M602 (0x01, 0x01, 0x01)), Arg2, Local0)
                M600 (Arg0, 0x18, Local0, BB24)
            }
        }

        /* String to Integer conversion of the String Length (second) */
        /* operand of the ToString operator */
        /* Common 32-bit/64-bit test */
        Method (M02C, 3, NotSerialized)
        {
            Local0 = ToString (Buffer (0x19)
                    {
                        "This is auxiliary Buffer"
                    }, Arg2)
            M600 (Arg0, 0x00, Local0, BS1B)
            Local0 = ToString (Buffer (0x19)
                    {
                        "This is auxiliary Buffer"
                    }, Arg1)
            M600 (Arg0, 0x01, Local0, BS1C)
            Local0 = ToString (AUB6, Arg2)
            M600 (Arg0, 0x02, Local0, BS1B)
            Local0 = ToString (AUB6, Arg1)
            M600 (Arg0, 0x03, Local0, BS1C)
            If (Y078)
            {
                Local0 = ToString (DerefOf (RefOf (AUB6)), Arg2)
                M600 (Arg0, 0x04, Local0, BS1B)
                Local0 = ToString (DerefOf (RefOf (AUB6)), Arg1)
                M600 (Arg0, 0x05, Local0, BS1C)
            }

            Local0 = ToString (DerefOf (PAUB [0x06]), Arg2)
            M600 (Arg0, 0x06, Local0, BS1B)
            Local0 = ToString (DerefOf (PAUB [0x06]), Arg1)
            M600 (Arg0, 0x07, Local0, BS1C)
            /* Method returns Buffer */

            Local0 = ToString (M601 (0x03, 0x06), Arg2)
            M600 (Arg0, 0x08, Local0, BS1B)
            Local0 = ToString (M601 (0x03, 0x06), Arg1)
            M600 (Arg0, 0x09, Local0, BS1C)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Local0 = ToString (DerefOf (M602 (0x03, 0x06, 0x01)), Arg2)
                M600 (Arg0, 0x0A, Local0, BS1B)
                Local0 = ToString (DerefOf (M602 (0x03, 0x06, 0x01)), Arg1)
                M600 (Arg0, 0x0B, Local0, BS1C)
            }

            ToString (Buffer (0x19)
                {
                    "This is auxiliary Buffer"
                }, Arg2, Local0)
            M600 (Arg0, 0x0C, Local0, BS1B)
            ToString (Buffer (0x19)
                {
                    "This is auxiliary Buffer"
                }, Arg1, Local0)
            M600 (Arg0, 0x0D, Local0, BS1C)
            ToString (AUB6, Arg2, Local0)
            M600 (Arg0, 0x0E, Local0, BS1B)
            ToString (AUB6, Arg1, Local0)
            M600 (Arg0, 0x0F, Local0, BS1C)
            If (Y078)
            {
                ToString (DerefOf (RefOf (AUB6)), Arg2, Local0)
                M600 (Arg0, 0x10, Local0, BS1B)
                ToString (DerefOf (RefOf (AUB6)), Arg1, Local0)
                M600 (Arg0, 0x11, Local0, BS1C)
            }

            ToString (DerefOf (PAUB [0x06]), Arg2, Local0)
            M600 (Arg0, 0x12, Local0, BS1B)
            ToString (DerefOf (PAUB [0x06]), Arg1, Local0)
            M600 (Arg0, 0x13, Local0, BS1C)
            /* Method returns Buffer */

            ToString (M601 (0x03, 0x06), Arg2, Local0)
            M600 (Arg0, 0x14, Local0, BS1B)
            ToString (M601 (0x03, 0x06), Arg1, Local0)
            M600 (Arg0, 0x15, Local0, BS1C)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                ToString (DerefOf (M602 (0x03, 0x06, 0x01)), Arg2, Local0)
                M600 (Arg0, 0x16, Local0, BS1B)
                ToString (DerefOf (M602 (0x03, 0x06, 0x01)), Arg1, Local0)
                M600 (Arg0, 0x17, Local0, BS1C)
            }
        }

        Method (M64H, 2, NotSerialized)
        {
            Local0 = ToString (Buffer (0x19)
                    {
                        "This is auxiliary Buffer"
                    }, Arg1)
            M600 (Arg0, 0x00, Local0, BS1C)
            Local0 = ToString (AUB6, Arg1)
            M600 (Arg0, 0x01, Local0, BS1C)
            If (Y078)
            {
                Local0 = ToString (DerefOf (RefOf (AUB6)), Arg1)
                M600 (Arg0, 0x02, Local0, BS1C)
            }

            Local0 = ToString (DerefOf (PAUB [0x06]), Arg1)
            M600 (Arg0, 0x03, Local0, BS1C)
            /* Method returns Buffer */

            Local0 = ToString (M601 (0x03, 0x06), Arg1)
            M600 (Arg0, 0x04, Local0, BS1C)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Local0 = ToString (DerefOf (M602 (0x03, 0x06, 0x01)), Arg1)
                M600 (Arg0, 0x05, Local0, BS1C)
            }

            ToString (Buffer (0x19)
                {
                    "This is auxiliary Buffer"
                }, Arg1, Local0)
            M600 (Arg0, 0x06, Local0, BS1C)
            ToString (AUB6, Arg1, Local0)
            M600 (Arg0, 0x07, Local0, BS1C)
            If (Y078)
            {
                ToString (DerefOf (RefOf (AUB6)), Arg1, Local0)
                M600 (Arg0, 0x08, Local0, BS1C)
            }

            ToString (DerefOf (PAUB [0x06]), Arg1, Local0)
            M600 (Arg0, 0x09, Local0, BS1C)
            /* Method returns Buffer */

            ToString (M601 (0x03, 0x06), Arg1, Local0)
            M600 (Arg0, 0x0A, Local0, BS1C)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                ToString (DerefOf (M602 (0x03, 0x06, 0x01)), Arg1, Local0)
                M600 (Arg0, 0x0B, Local0, BS1C)
            }
        }

        Method (M32H, 2, NotSerialized)
        {
            Local0 = ToString (Buffer (0x19)
                    {
                        "This is auxiliary Buffer"
                    }, Arg1)
            M600 (Arg0, 0x00, Local0, BS1C)
            Local0 = ToString (AUB6, Arg1)
            M600 (Arg0, 0x01, Local0, BS1C)
            If (Y078)
            {
                Local0 = ToString (DerefOf (RefOf (AUB6)), Arg1)
                M600 (Arg0, 0x02, Local0, BS1C)
            }

            Local0 = ToString (DerefOf (PAUB [0x06]), Arg1)
            M600 (Arg0, 0x03, Local0, BS1C)
            /* Method returns Buffer */

            Local0 = ToString (M601 (0x03, 0x06), Arg1)
            M600 (Arg0, 0x04, Local0, BS1C)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Local0 = ToString (DerefOf (M602 (0x03, 0x06, 0x01)), Arg1)
                M600 (Arg0, 0x05, Local0, BS1C)
            }

            ToString (Buffer (0x19)
                {
                    "This is auxiliary Buffer"
                }, Arg1, Local0)
            M600 (Arg0, 0x06, Local0, BS1C)
            ToString (AUB6, Arg1, Local0)
            M600 (Arg0, 0x07, Local0, BS1C)
            If (Y078)
            {
                ToString (DerefOf (RefOf (AUB6)), Arg1, Local0)
                M600 (Arg0, 0x08, Local0, BS1C)
            }

            ToString (DerefOf (PAUB [0x06]), Arg1, Local0)
            M600 (Arg0, 0x09, Local0, BS1C)
            /* Method returns Buffer */

            ToString (M601 (0x03, 0x06), Arg1, Local0)
            M600 (Arg0, 0x0A, Local0, BS1C)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                ToString (DerefOf (M602 (0x03, 0x06, 0x01)), Arg1, Local0)
                M600 (Arg0, 0x0B, Local0, BS1C)
            }
        }

        /* String to Integer conversion of the String Index (second) */
        /* operand of the Index operator */
        Method (M02D, 2, NotSerialized)
        {
            Store (AUS6 [Arg1], Local0)
            M600 (Arg0, 0x00, DerefOf (Local0), BI10)
            Store (AUB6 [Arg1], Local0)
            M600 (Arg0, 0x01, DerefOf (Local0), BI10)
            Store (AUP0 [Arg1], Local0)
            M600 (Arg0, 0x02, DerefOf (Local0), BI11)
            If (Y078)
            {
                Store (DerefOf (RefOf (AUS6)) [Arg1], Local0)
                M600 (Arg0, 0x03, DerefOf (Local0), BI10)
                Store (DerefOf (RefOf (AUB6)) [Arg1], Local0)
                M600 (Arg0, 0x04, DerefOf (Local0), BI10)
                Store (DerefOf (RefOf (AUP0)) [Arg1], Local0)
                M600 (Arg0, 0x05, DerefOf (Local0), BI11)
            }

            Store (DerefOf (PAUS [0x06]) [Arg1], Local0)
            M600 (Arg0, 0x06, DerefOf (Local0), BI10)
            Store (DerefOf (PAUB [0x06]) [Arg1], Local0)
            M600 (Arg0, 0x07, DerefOf (Local0), BI10)
            Store (DerefOf (PAUP [0x00]) [Arg1], Local0)
            M600 (Arg0, 0x08, DerefOf (Local0), BI11)
            /* Method returns Object */

            If (Y900)
            {
                Store (M601 (0x02, 0x06) [Arg1], Local0)
                M600 (Arg0, 0x09, DerefOf (Local0), BI10)
                Store (M601 (0x03, 0x06) [Arg1], Local0)
                M600 (Arg0, 0x0A, DerefOf (Local0), BI10)
                Store (M601 (0x04, 0x00) [Arg1], Local0)
                M600 (Arg0, 0x0B, DerefOf (Local0), BI11)
            }
            Else
            {
                CH03 (Arg0, Z121, 0x00, 0x2E2A, 0x00)
                Store (M601 (0x02, 0x06) [Arg1], Local3)
                CH04 (Arg0, 0x00, 0x55, Z121, 0x2E2D, 0x00, 0x00) /* AE_INDEX_TO_NOT_ATTACHED */
                Store (M601 (0x03, 0x06) [Arg1], Local3)
                CH04 (Arg0, 0x00, 0x55, Z121, 0x2E30, 0x00, 0x00) /* AE_INDEX_TO_NOT_ATTACHED */
                Store (M601 (0x04, 0x00) [Arg1], Local3)
                CH04 (Arg0, 0x00, 0x55, Z121, 0x2E33, 0x00, 0x00) /* AE_INDEX_TO_NOT_ATTACHED */
            }

            /* Method returns Reference */

            If (Y500)
            {
                Store (DerefOf (M602 (0x02, 0x06, 0x01)) [Arg1], Local0)
                M600 (Arg0, 0x0C, DerefOf (Local0), BI10)
                Store (DerefOf (M602 (0x03, 0x06, 0x01)) [Arg1], Local0)
                M600 (Arg0, 0x0D, DerefOf (Local0), BI10)
                Store (DerefOf (M602 (0x04, 0x00, 0x01)) [Arg1], Local0)
                M600 (Arg0, 0x0E, DerefOf (Local0), BI11)
            }

            Local0 = AUS6 [Arg1]
            M600 (Arg0, 0x0F, DerefOf (Local0), BI10)
            Local0 = AUB6 [Arg1]
            M600 (Arg0, 0x10, DerefOf (Local0), BI10)
            Local0 = AUP0 [Arg1]
            M600 (Arg0, 0x11, DerefOf (Local0), BI11)
            If (Y078)
            {
                Local0 = DerefOf (RefOf (AUS6)) [Arg1]
                M600 (Arg0, 0x12, DerefOf (Local0), BI10)
                Local0 = DerefOf (RefOf (AUB6)) [Arg1]
                M600 (Arg0, 0x13, DerefOf (Local0), BI10)
                Local0 = DerefOf (RefOf (AUP0)) [Arg1]
                M600 (Arg0, 0x14, DerefOf (Local0), BI11)
            }

            Local0 = DerefOf (PAUS [0x06]) [Arg1]
            M600 (Arg0, 0x15, DerefOf (Local0), BI10)
            Local0 = DerefOf (PAUB [0x06]) [Arg1]
            M600 (Arg0, 0x16, DerefOf (Local0), BI10)
            Local0 = DerefOf (PAUP [0x00]) [Arg1]
            M600 (Arg0, 0x17, DerefOf (Local0), BI11)
            /* Method returns Object */

            If (Y900)
            {
                Local0 = M601 (0x02, 0x06) [Arg1]
                M600 (Arg0, 0x18, DerefOf (Local0), BI10)
                Local0 = M601 (0x03, 0x06) [Arg1]
                M600 (Arg0, 0x19, DerefOf (Local0), BI10)
                Local0 = M601 (0x04, 0x00) [Arg1]
                M600 (Arg0, 0x1A, DerefOf (Local0), BI11)
            }
            Else
            {
                CH03 (Arg0, Z121, 0x00, 0x2E6E, 0x00)
                Local0 = M601 (0x02, 0x06) [Arg1]
                CH04 (Arg0, 0x00, 0x55, Z121, 0x2E71, 0x00, 0x00) /* AE_INDEX_TO_NOT_ATTACHED */
                Local0 = M601 (0x03, 0x06) [Arg1]
                CH04 (Arg0, 0x00, 0x55, Z121, 0x2E74, 0x00, 0x00) /* AE_INDEX_TO_NOT_ATTACHED */
                Local0 = M601 (0x04, 0x00) [Arg1]
                CH04 (Arg0, 0x00, 0x55, Z121, 0x2E77, 0x00, 0x00) /* AE_INDEX_TO_NOT_ATTACHED */
            }

            /* Method returns Reference */

            If (Y500)
            {
                Local0 = DerefOf (M602 (0x02, 0x06, 0x01)) [Arg1]
                M600 (Arg0, 0x1B, DerefOf (Local0), BI10)
                Local0 = DerefOf (M602 (0x03, 0x06, 0x01)) [Arg1]
                M600 (Arg0, 0x1C, DerefOf (Local0), BI10)
                Local0 = DerefOf (M602 (0x04, 0x00, 0x01)) [Arg1]
                M600 (Arg0, 0x1D, DerefOf (Local0), BI11)
            }

            If (Y098)
            {
                Local0 = Local1 = AUS6 [Arg1]
                M600 (Arg0, 0x1E, DerefOf (Local0), BI10)
                Local0 = Local1 = AUB6 [Arg1]
                M600 (Arg0, 0x1F, DerefOf (Local0), BI10)
                Local0 = Local1 = AUP0 [Arg1]
                M600 (Arg0, 0x20, DerefOf (Local0), BI11)
            }

            If (Y078)
            {
                Local0 = Local1 = DerefOf (RefOf (AUS6)) [Arg1]
                M600 (Arg0, 0x21, DerefOf (Local0), BI10)
                Local0 = Local1 = DerefOf (RefOf (AUB6)) [Arg1]
                M600 (Arg0, 0x22, DerefOf (Local0), BI10)
                Local0 = Local1 = DerefOf (RefOf (AUP0)) [Arg1]
                M600 (Arg0, 0x23, DerefOf (Local0), BI11)
            }

            If (Y098)
            {
                Local0 = Local1 = DerefOf (PAUS [0x06]) [Arg1]
                M600 (Arg0, 0x24, DerefOf (Local0), BI10)
                Local0 = Local1 = DerefOf (PAUB [0x06]) [Arg1]
                M600 (Arg0, 0x25, DerefOf (Local0), BI10)
                Local0 = Local1 = DerefOf (PAUP [0x00]) [Arg1]
                M600 (Arg0, 0x26, DerefOf (Local0), BI11)
            }

            /* Method returns Object */

            If ((Y900 && Y098))
            {
                Local0 = Local1 = M601 (0x02, 0x06) [Arg1]
                M600 (Arg0, 0x27, DerefOf (Local0), BI10)
                Local0 = Local1 = M601 (0x03, 0x06) [Arg1]
                M600 (Arg0, 0x28, DerefOf (Local0), BI10)
                Local0 = Local1 = M601 (0x04, 0x00) [Arg1]
                M600 (Arg0, 0x29, DerefOf (Local0), BI11)
            }

            /* Method returns Reference */

            If (Y500)
            {
                Local0 = Local1 = DerefOf (M602 (0x02, 0x06, 0x01)) [Arg1]
                M600 (Arg0, 0x2A, DerefOf (Local0), BI10)
                Local0 = Local1 = DerefOf (M602 (0x03, 0x06, 0x01)) [Arg1]
                M600 (Arg0, 0x2B, DerefOf (Local0), BI10)
                Local0 = Local1 = DerefOf (M602 (0x04, 0x00, 0x01)) [Arg1]
                M600 (Arg0, 0x2C, DerefOf (Local0), BI11)
            }
        }

        /* String to Integer conversion of the String Arg (third) */
        /* operand of the Fatal operator */
        /* (it can only be checked an exception does not occur) */
        Method (M02E, 4, NotSerialized)
        {
            CH03 (Arg0, Z121, 0x00, 0x2EC8, 0x00)
            Fatal (0xFF, 0xFFFFFFFF, Arg1)
            If (F64)
            {
                Fatal (0xFF, 0xFFFFFFFF, Arg2)
            }
            Else
            {
                Fatal (0xFF, 0xFFFFFFFF, Arg3)
            }

            CH03 (Arg0, Z121, 0x01, 0x2ECF, 0x00)
        }

        /* String to Integer conversion of the String Index and Length */
        /* operands of the Mid operator */
        /* Common 32-bit/64-bit test */
        Method (M02F, 2, NotSerialized)
        {
            /* String to Integer conversion of the String Index operand */

            Local0 = Mid ("This is auxiliary String", Arg1, 0x0A)
            M600 (Arg0, 0x00, Local0, BS1D)
            Local0 = Mid (Buffer (0x19)
                    {
                        "This is auxiliary Buffer"
                    }, Arg1, 0x0A)
            M600 (Arg0, 0x01, Local0, BB32)
            Local0 = Mid (AUS6, Arg1, 0x0A)
            M600 (Arg0, 0x02, Local0, BS1D)
            Local0 = Mid (AUB6, Arg1, 0x0A)
            M600 (Arg0, 0x03, Local0, BB32)
            If (Y078)
            {
                Local0 = Mid (DerefOf (RefOf (AUS6)), Arg1, 0x0A)
                M600 (Arg0, 0x04, Local0, BS1D)
                Local0 = Mid (DerefOf (RefOf (AUB6)), Arg1, 0x0A)
                M600 (Arg0, 0x05, Local0, BB32)
            }

            Local0 = Mid (DerefOf (PAUS [0x06]), Arg1, 0x0A)
            M600 (Arg0, 0x06, Local0, BS1D)
            Local0 = Mid (DerefOf (PAUB [0x06]), Arg1, 0x0A)
            M600 (Arg0, 0x07, Local0, BB32)
            /* Method returns Object */

            Local0 = Mid (M601 (0x02, 0x06), Arg1, 0x0A)
            M600 (Arg0, 0x08, Local0, BS1D)
            Local0 = Mid (M601 (0x03, 0x06), Arg1, 0x0A)
            M600 (Arg0, 0x09, Local0, BB32)
            /* Method returns Reference */

            If (Y500)
            {
                Local0 = Mid (DerefOf (M602 (0x02, 0x06, 0x01)), Arg1, 0x0A)
                M600 (Arg0, 0x0A, Local0, BS1D)
                Local0 = Mid (DerefOf (M602 (0x03, 0x06, 0x01)), Arg1, 0x0A)
                M600 (Arg0, 0x0B, Local0, BB32)
            }

            Mid ("This is auxiliary String", Arg1, 0x0A, Local0)
            M600 (Arg0, 0x0C, Local0, BS1D)
            Mid (Buffer (0x19)
                {
                    "This is auxiliary Buffer"
                }, Arg1, 0x0A, Local0)
            M600 (Arg0, 0x0D, Local0, BB32)
            Mid (AUS6, Arg1, 0x0A, Local0)
            M600 (Arg0, 0x0E, Local0, BS1D)
            Mid (AUB6, Arg1, 0x0A, Local0)
            M600 (Arg0, 0x0F, Local0, BB32)
            If (Y078)
            {
                Mid (DerefOf (RefOf (AUS6)), Arg1, 0x0A, Local0)
                M600 (Arg0, 0x10, Local0, BS1D)
                Mid (DerefOf (RefOf (AUB6)), Arg1, 0x0A, Local0)
                M600 (Arg0, 0x11, Local0, BB32)
            }

            Mid (DerefOf (PAUS [0x06]), Arg1, 0x0A, Local0)
            M600 (Arg0, 0x12, Local0, BS1D)
            Mid (DerefOf (PAUB [0x06]), Arg1, 0x0A, Local0)
            M600 (Arg0, 0x13, Local0, BB32)
            /* Method returns Object */

            Mid (M601 (0x02, 0x06), Arg1, 0x0A, Local0)
            M600 (Arg0, 0x14, Local0, BS1D)
            Mid (M601 (0x03, 0x06), Arg1, 0x0A, Local0)
            M600 (Arg0, 0x15, Local0, BB32)
            /* Method returns Reference */

            If (Y500)
            {
                Mid (DerefOf (M602 (0x02, 0x06, 0x01)), Arg1, 0x0A, Local0)
                M600 (Arg0, 0x16, Local0, BS1D)
                Mid (DerefOf (M602 (0x03, 0x06, 0x01)), Arg1, 0x0A, Local0)
                M600 (Arg0, 0x17, Local0, BB32)
            }

            /* String to Integer conversion of the String Length operand */

            Local0 = Mid ("This is auxiliary String", 0x00, Arg1)
            M600 (Arg0, 0x18, Local0, BS1B)
            Local0 = Mid (Buffer (0x19)
                    {
                        "This is auxiliary Buffer"
                    }, 0x00, Arg1)
            M600 (Arg0, 0x19, Local0, BB33)
            Local0 = Mid (AUS6, 0x00, Arg1)
            M600 (Arg0, 0x1A, Local0, BS1B)
            Local0 = Mid (AUB6, 0x00, Arg1)
            M600 (Arg0, 0x1B, Local0, BB33)
            If (Y078)
            {
                Local0 = Mid (DerefOf (RefOf (AUS6)), 0x00, Arg1)
                M600 (Arg0, 0x1C, Local0, BS1B)
                Local0 = Mid (DerefOf (RefOf (AUB6)), 0x00, Arg1)
                M600 (Arg0, 0x1D, Local0, BB33)
            }

            Local0 = Mid (DerefOf (PAUS [0x06]), 0x00, Arg1)
            M600 (Arg0, 0x1E, Local0, BS1B)
            Local0 = Mid (DerefOf (PAUB [0x06]), 0x00, Arg1)
            M600 (Arg0, 0x1F, Local0, BB33)
            /* Method returns Object */

            Local0 = Mid (M601 (0x02, 0x06), 0x00, Arg1)
            M600 (Arg0, 0x20, Local0, BS1B)
            Local0 = Mid (M601 (0x03, 0x06), 0x00, Arg1)
            M600 (Arg0, 0x21, Local0, BB33)
            /* Method returns Reference */

            If (Y500)
            {
                Local0 = Mid (DerefOf (M602 (0x02, 0x06, 0x01)), 0x00, Arg1)
                M600 (Arg0, 0x22, Local0, BS1B)
                Local0 = Mid (DerefOf (M602 (0x03, 0x06, 0x01)), 0x00, Arg1)
                M600 (Arg0, 0x23, Local0, BB33)
            }

            Mid ("This is auxiliary String", 0x00, Arg1, Local0)
            M600 (Arg0, 0x24, Local0, BS1B)
            Mid (Buffer (0x19)
                {
                    "This is auxiliary Buffer"
                }, 0x00, Arg1, Local0)
            M600 (Arg0, 0x25, Local0, BB33)
            Mid (AUS6, 0x00, Arg1, Local0)
            M600 (Arg0, 0x25, Local0, BS1B)
            Mid (AUB6, 0x00, Arg1, Local0)
            M600 (Arg0, 0x27, Local0, BB33)
            If (Y078)
            {
                Mid (DerefOf (RefOf (AUS6)), 0x00, Arg1, Local0)
                M600 (Arg0, 0x28, Local0, BS1B)
                Mid (DerefOf (RefOf (AUB6)), 0x00, Arg1, Local0)
                M600 (Arg0, 0x29, Local0, BB33)
            }

            Mid (DerefOf (PAUS [0x06]), 0x00, Arg1, Local0)
            M600 (Arg0, 0x2A, Local0, BS1B)
            Mid (DerefOf (PAUB [0x06]), 0x00, Arg1, Local0)
            M600 (Arg0, 0x2B, Local0, BB33)
            /* Method returns Object */

            Mid (M601 (0x02, 0x06), 0x00, Arg1, Local0)
            M600 (Arg0, 0x2C, Local0, BS1B)
            Mid (M601 (0x03, 0x06), 0x00, Arg1, Local0)
            M600 (Arg0, 0x2D, Local0, BB33)
            /* Method returns Reference */

            If (Y500)
            {
                Mid (DerefOf (M602 (0x02, 0x06, 0x01)), 0x00, Arg1, Local0)
                M600 (Arg0, 0x2E, Local0, BS1B)
                Mid (DerefOf (M602 (0x03, 0x06, 0x01)), 0x00, Arg1, Local0)
                M600 (Arg0, 0x2F, Local0, BB33)
            }
        }

        Method (M64I, 3, NotSerialized)
        {
            /* String to Integer conversion of the String Length operand */

            Local0 = Mid ("This is auxiliary String", 0x00, Arg1)
            M600 (Arg0, 0x00, Local0, BS1E)
            Local0 = Mid (Buffer (0x19)
                    {
                        "This is auxiliary Buffer"
                    }, 0x00, Arg1)
            M600 (Arg0, 0x01, Local0, BB34)
            Local0 = Mid (AUS6, 0x00, Arg1)
            M600 (Arg0, 0x02, Local0, BS1E)
            Local0 = Mid (AUB6, 0x00, Arg1)
            M600 (Arg0, 0x03, Local0, BB34)
            If (Y078)
            {
                Local0 = Mid (DerefOf (RefOf (AUS6)), 0x00, Arg1)
                M600 (Arg0, 0x04, Local0, BS1E)
                Local0 = Mid (DerefOf (RefOf (AUB6)), 0x00, Arg1)
                M600 (Arg0, 0x05, Local0, BB34)
            }

            Local0 = Mid (DerefOf (PAUS [0x06]), 0x00, Arg1)
            M600 (Arg0, 0x06, Local0, BS1E)
            Local0 = Mid (DerefOf (PAUB [0x06]), 0x00, Arg1)
            M600 (Arg0, 0x07, Local0, BB34)
            /* Method returns Object */

            Local0 = Mid (M601 (0x02, 0x06), 0x00, Arg1)
            M600 (Arg0, 0x08, Local0, BS1E)
            Local0 = Mid (M601 (0x03, 0x06), 0x00, Arg1)
            M600 (Arg0, 0x09, Local0, BB34)
            /* Method returns Reference */

            If (Y500)
            {
                Local0 = Mid (DerefOf (M602 (0x02, 0x06, 0x01)), 0x00, Arg1)
                M600 (Arg0, 0x0A, Local0, BS1E)
                Local0 = Mid (DerefOf (M602 (0x03, 0x06, 0x01)), 0x00, Arg1)
                M600 (Arg0, 0x0B, Local0, BB34)
            }

            Mid ("This is auxiliary String", 0x00, Arg1, Local0)
            M600 (Arg0, 0x0C, Local0, BS1E)
            Mid (Buffer (0x19)
                {
                    "This is auxiliary Buffer"
                }, 0x00, Arg1, Local0)
            M600 (Arg0, 0x0D, Local0, BB34)
            Mid (AUS6, 0x00, Arg1, Local0)
            M600 (Arg0, 0x0E, Local0, BS1E)
            Mid (AUB6, 0x00, Arg1, Local0)
            M600 (Arg0, 0x0F, Local0, BB34)
            If (Y078)
            {
                Mid (DerefOf (RefOf (AUS6)), 0x00, Arg1, Local0)
                M600 (Arg0, 0x10, Local0, BS1E)
                Mid (DerefOf (RefOf (AUB6)), 0x00, Arg1, Local0)
                M600 (Arg0, 0x11, Local0, BB34)
            }

            Mid (DerefOf (PAUS [0x06]), 0x00, Arg1, Local0)
            M600 (Arg0, 0x12, Local0, BS1E)
            Mid (DerefOf (PAUB [0x06]), 0x00, Arg1, Local0)
            M600 (Arg0, 0x13, Local0, BB34)
            /* Method returns Object */

            Mid (M601 (0x02, 0x06), 0x00, Arg1, Local0)
            M600 (Arg0, 0x14, Local0, BS1E)
            Mid (M601 (0x03, 0x06), 0x00, Arg1, Local0)
            M600 (Arg0, 0x15, Local0, BB34)
            /* Method returns Reference */

            If (Y500)
            {
                Mid (DerefOf (M602 (0x02, 0x06, 0x01)), 0x00, Arg1, Local0)
                M600 (Arg0, 0x16, Local0, BS1E)
                Mid (DerefOf (M602 (0x03, 0x06, 0x01)), 0x00, Arg1, Local0)
                M600 (Arg0, 0x17, Local0, BB34)
            }

            /* String to Integer conversion of the both String operands */

            Local0 = Mid ("This is auxiliary String", Arg2, Arg1)
            M600 (Arg0, 0x18, Local0, BS1F)
            Local0 = Mid (Buffer (0x19)
                    {
                        "This is auxiliary Buffer"
                    }, Arg2, Arg1)
            M600 (Arg0, 0x19, Local0, BB35)
            Local0 = Mid (AUS6, Arg2, Arg1)
            M600 (Arg0, 0x1A, Local0, BS1F)
            Local0 = Mid (AUB6, Arg2, Arg1)
            M600 (Arg0, 0x1B, Local0, BB35)
            If (Y078)
            {
                Local0 = Mid (DerefOf (RefOf (AUS6)), Arg2, Arg1)
                M600 (Arg0, 0x1C, Local0, BS1F)
                Local0 = Mid (DerefOf (RefOf (AUB6)), Arg2, Arg1)
                M600 (Arg0, 0x1D, Local0, BB35)
            }

            Local0 = Mid (DerefOf (PAUS [0x06]), Arg2, Arg1)
            M600 (Arg0, 0x1E, Local0, BS1F)
            Local0 = Mid (DerefOf (PAUB [0x06]), Arg2, Arg1)
            M600 (Arg0, 0x1F, Local0, BB35)
            /* Method returns Object */

            Local0 = Mid (M601 (0x02, 0x06), Arg2, Arg1)
            M600 (Arg0, 0x20, Local0, BS1F)
            Local0 = Mid (M601 (0x03, 0x06), Arg2, Arg1)
            M600 (Arg0, 0x21, Local0, BB35)
            /* Method returns Reference */

            If (Y500)
            {
                Local0 = Mid (DerefOf (M602 (0x02, 0x06, 0x01)), Arg2, Arg1)
                M600 (Arg0, 0x22, Local0, BS1F)
                Local0 = Mid (DerefOf (M602 (0x03, 0x06, 0x01)), Arg2, Arg1)
                M600 (Arg0, 0x23, Local0, BB35)
            }

            Mid ("This is auxiliary String", Arg2, Arg1, Local0)
            M600 (Arg0, 0x24, Local0, BS1F)
            Mid (Buffer (0x19)
                {
                    "This is auxiliary Buffer"
                }, Arg2, Arg1, Local0)
            M600 (Arg0, 0x25, Local0, BB35)
            Mid (AUS6, Arg2, Arg1, Local0)
            M600 (Arg0, 0x26, Local0, BS1F)
            Mid (AUB6, Arg2, Arg1, Local0)
            M600 (Arg0, 0x27, Local0, BB35)
            If (Y078)
            {
                Mid (DerefOf (RefOf (AUS6)), Arg2, Arg1, Local0)
                M600 (Arg0, 0x28, Local0, BS1F)
                Mid (DerefOf (RefOf (AUB6)), Arg2, Arg1, Local0)
                M600 (Arg0, 0x29, Local0, BB35)
            }

            Mid (DerefOf (PAUS [0x06]), Arg2, Arg1, Local0)
            M600 (Arg0, 0x2A, Local0, BS1F)
            Mid (DerefOf (PAUB [0x06]), Arg2, Arg1, Local0)
            M600 (Arg0, 0x2B, Local0, BB35)
            /* Method returns Object */

            Mid (M601 (0x02, 0x06), Arg2, Arg1, Local0)
            M600 (Arg0, 0x2C, Local0, BS1F)
            Mid (M601 (0x03, 0x06), Arg2, Arg1, Local0)
            M600 (Arg0, 0x2D, Local0, BB35)
            /* Method returns Reference */

            If (Y500)
            {
                Mid (DerefOf (M602 (0x02, 0x06, 0x01)), Arg2, Arg1, Local0)
                M600 (Arg0, 0x2E, Local0, BS1F)
                Mid (DerefOf (M602 (0x03, 0x06, 0x01)), Arg2, Arg1, Local0)
                M600 (Arg0, 0x2F, Local0, BB35)
            }
        }

        Method (M32I, 3, NotSerialized)
        {
            /* String to Integer conversion of the String Length operand */

            Local0 = Mid ("This is auxiliary String", 0x00, Arg1)
            M600 (Arg0, 0x00, Local0, BS1E)
            Local0 = Mid (Buffer (0x19)
                    {
                        "This is auxiliary Buffer"
                    }, 0x00, Arg1)
            M600 (Arg0, 0x01, Local0, BB34)
            Local0 = Mid (AUS6, 0x00, Arg1)
            M600 (Arg0, 0x02, Local0, BS1E)
            Local0 = Mid (AUB6, 0x00, Arg1)
            M600 (Arg0, 0x03, Local0, BB34)
            If (Y078)
            {
                Local0 = Mid (DerefOf (RefOf (AUS6)), 0x00, Arg1)
                M600 (Arg0, 0x04, Local0, BS1E)
                Local0 = Mid (DerefOf (RefOf (AUB6)), 0x00, Arg1)
                M600 (Arg0, 0x05, Local0, BB34)
            }

            Local0 = Mid (DerefOf (PAUS [0x06]), 0x00, Arg1)
            M600 (Arg0, 0x06, Local0, BS1E)
            Local0 = Mid (DerefOf (PAUB [0x06]), 0x00, Arg1)
            M600 (Arg0, 0x07, Local0, BB34)
            /* Method returns Object */

            Local0 = Mid (M601 (0x02, 0x06), 0x00, Arg1)
            M600 (Arg0, 0x08, Local0, BS1E)
            Local0 = Mid (M601 (0x03, 0x06), 0x00, Arg1)
            M600 (Arg0, 0x09, Local0, BB34)
            /* Method returns Reference */

            If (Y500)
            {
                Local0 = Mid (DerefOf (M602 (0x02, 0x06, 0x01)), 0x00, Arg1)
                M600 (Arg0, 0x0A, Local0, BS1E)
                Local0 = Mid (DerefOf (M602 (0x03, 0x06, 0x01)), 0x00, Arg1)
                M600 (Arg0, 0x0B, Local0, BB34)
            }

            Mid ("This is auxiliary String", 0x00, Arg1, Local0)
            M600 (Arg0, 0x0C, Local0, BS1E)
            Mid (Buffer (0x19)
                {
                    "This is auxiliary Buffer"
                }, 0x00, Arg1, Local0)
            M600 (Arg0, 0x0D, Local0, BB34)
            Mid (AUS6, 0x00, Arg1, Local0)
            M600 (Arg0, 0x0E, Local0, BS1E)
            Mid (AUB6, 0x00, Arg1, Local0)
            M600 (Arg0, 0x0F, Local0, BB34)
            If (Y078)
            {
                Mid (DerefOf (RefOf (AUS6)), 0x00, Arg1, Local0)
                M600 (Arg0, 0x10, Local0, BS1E)
                Mid (DerefOf (RefOf (AUB6)), 0x00, Arg1, Local0)
                M600 (Arg0, 0x11, Local0, BB34)
            }

            Mid (DerefOf (PAUS [0x06]), 0x00, Arg1, Local0)
            M600 (Arg0, 0x12, Local0, BS1E)
            Mid (DerefOf (PAUB [0x06]), 0x00, Arg1, Local0)
            M600 (Arg0, 0x13, Local0, BB34)
            /* Method returns Object */

            Mid (M601 (0x02, 0x06), 0x00, Arg1, Local0)
            M600 (Arg0, 0x14, Local0, BS1E)
            Mid (M601 (0x03, 0x06), 0x00, Arg1, Local0)
            M600 (Arg0, 0x15, Local0, BB34)
            /* Method returns Reference */

            If (Y500)
            {
                Mid (DerefOf (M602 (0x02, 0x06, 0x01)), 0x00, Arg1, Local0)
                M600 (Arg0, 0x16, Local0, BS1E)
                Mid (DerefOf (M602 (0x03, 0x06, 0x01)), 0x00, Arg1, Local0)
                M600 (Arg0, 0x17, Local0, BB34)
            }

            /* String to Integer conversion of the both String operands */

            Local0 = Mid ("This is auxiliary String", Arg2, Arg1)
            M600 (Arg0, 0x18, Local0, BS1F)
            Local0 = Mid (Buffer (0x19)
                    {
                        "This is auxiliary Buffer"
                    }, Arg2, Arg1)
            M600 (Arg0, 0x19, Local0, BB35)
            Local0 = Mid (AUS6, Arg2, Arg1)
            M600 (Arg0, 0x1A, Local0, BS1F)
            Local0 = Mid (AUB6, Arg2, Arg1)
            M600 (Arg0, 0x1B, Local0, BB35)
            If (Y078)
            {
                Local0 = Mid (DerefOf (RefOf (AUS6)), Arg2, Arg1)
                M600 (Arg0, 0x1C, Local0, BS1F)
                Local0 = Mid (DerefOf (RefOf (AUB6)), Arg2, Arg1)
                M600 (Arg0, 0x1D, Local0, BB35)
            }

            Local0 = Mid (DerefOf (PAUS [0x06]), Arg2, Arg1)
            M600 (Arg0, 0x1E, Local0, BS1F)
            Local0 = Mid (DerefOf (PAUB [0x06]), Arg2, Arg1)
            M600 (Arg0, 0x1F, Local0, BB35)
            /* Method returns Object */

            Local0 = Mid (M601 (0x02, 0x06), Arg2, Arg1)
            M600 (Arg0, 0x20, Local0, BS1F)
            Local0 = Mid (M601 (0x03, 0x06), Arg2, Arg1)
            M600 (Arg0, 0x21, Local0, BB35)
            /* Method returns Reference */

            If (Y500)
            {
                Local0 = Mid (DerefOf (M602 (0x02, 0x06, 0x01)), Arg2, Arg1)
                M600 (Arg0, 0x22, Local0, BS1F)
                Local0 = Mid (DerefOf (M602 (0x03, 0x06, 0x01)), Arg2, Arg1)
                M600 (Arg0, 0x23, Local0, BB35)
            }

            Mid ("This is auxiliary String", Arg2, Arg1, Local0)
            M600 (Arg0, 0x24, Local0, BS1F)
            Mid (Buffer (0x19)
                {
                    "This is auxiliary Buffer"
                }, Arg2, Arg1, Local0)
            M600 (Arg0, 0x25, Local0, BB35)
            Mid (AUS6, Arg2, Arg1, Local0)
            M600 (Arg0, 0x26, Local0, BS1F)
            Mid (AUB6, Arg2, Arg1, Local0)
            M600 (Arg0, 0x27, Local0, BB35)
            If (Y078)
            {
                Mid (DerefOf (RefOf (AUS6)), Arg2, Arg1, Local0)
                M600 (Arg0, 0x28, Local0, BS1F)
                Mid (DerefOf (RefOf (AUB6)), Arg2, Arg1, Local0)
                M600 (Arg0, 0x29, Local0, BB35)
            }

            Mid (DerefOf (PAUS [0x06]), Arg2, Arg1, Local0)
            M600 (Arg0, 0x2A, Local0, BS1F)
            Mid (DerefOf (PAUB [0x06]), Arg2, Arg1, Local0)
            M600 (Arg0, 0x2B, Local0, BB35)
            /* Method returns Object */

            Mid (M601 (0x02, 0x06), Arg2, Arg1, Local0)
            M600 (Arg0, 0x2C, Local0, BS1F)
            Mid (M601 (0x03, 0x06), Arg2, Arg1, Local0)
            M600 (Arg0, 0x2D, Local0, BB35)
            /* Method returns Reference */

            If (Y500)
            {
                Mid (DerefOf (M602 (0x02, 0x06, 0x01)), Arg2, Arg1, Local0)
                M600 (Arg0, 0x2E, Local0, BS1F)
                Mid (DerefOf (M602 (0x03, 0x06, 0x01)), Arg2, Arg1, Local0)
                M600 (Arg0, 0x2F, Local0, BB35)
            }
        }

        /* String to Integer conversion of the String StartIndex */
        /* operand of the Match operator */
        Method (M030, 2, NotSerialized)
        {
            Local0 = Match (Package (0x0F)
                    {
                        0x0A50, 
                        0x0A51, 
                        0x0A52, 
                        0x0A53, 
                        0x0A54, 
                        0x0A55, 
                        0x0A56, 
                        0x0A57, 
                        0x0A58, 
                        0x0A59, 
                        0x0A5A, 
                        0x0A5B, 
                        0x0A5C, 
                        0x0A5D, 
                        0x0A5E
                    }, MEQ, 0x0A5D, MTR, 0x00, Arg1)
            M600 (Arg0, 0x00, Local0, 0x0D)
            Local0 = Match (Package (0x0F)
                    {
                        0x0A50, 
                        0x0A51, 
                        0x0A52, 
                        0x0A53, 
                        0x0A54, 
                        0x0A55, 
                        0x0A56, 
                        0x0A57, 
                        0x0A58, 
                        0x0A59, 
                        0x0A5A, 
                        0x0A5B, 
                        0x0A5C, 
                        0x0A5D, 
                        0x0A5E
                    }, MEQ, 0x0A5A, MTR, 0x00, Arg1)
            M600 (Arg0, 0x01, Local0, Ones)
            Local0 = Match (AUP0, MEQ, 0x0A5D, MTR, 0x00, Arg1)
            M600 (Arg0, 0x02, Local0, 0x0D)
            Local0 = Match (AUP0, MEQ, 0x0A5A, MTR, 0x00, Arg1)
            M600 (Arg0, 0x03, Local0, Ones)
            If (Y078)
            {
                Local0 = Match (DerefOf (RefOf (AUP0)), MEQ, 0x0A5D, MTR, 0x00, Arg1)
                M600 (Arg0, 0x04, Local0, 0x0D)
                Local0 = Match (DerefOf (RefOf (AUP0)), MEQ, 0x0A5A, MTR, 0x00, Arg1)
                M600 (Arg0, 0x05, Local0, Ones)
            }

            Local0 = Match (DerefOf (PAUP [0x00]), MEQ, 0x0A5D, MTR, 0x00, 
                Arg1)
            M600 (Arg0, 0x06, Local0, 0x0D)
            Local0 = Match (DerefOf (PAUP [0x00]), MEQ, 0x0A5A, MTR, 0x00, 
                Arg1)
            M600 (Arg0, 0x07, Local0, Ones)
            /* Method returns Object */

            Local0 = Match (M601 (0x04, 0x00), MEQ, 0x0A5D, MTR, 0x00, Arg1)
            M600 (Arg0, 0x08, Local0, 0x0D)
            Local0 = Match (M601 (0x04, 0x00), MEQ, 0x0A5A, MTR, 0x00, Arg1)
            M600 (Arg0, 0x09, Local0, Ones)
            /* Method returns Reference */

            If (Y500)
            {
                Local0 = Match (DerefOf (M602 (0x04, 0x00, 0x01)), MEQ, 0x0A5D, MTR, 0x00, 
                    Arg1)
                M600 (Arg0, 0x0A, Local0, 0x0D)
                Local0 = Match (DerefOf (M602 (0x04, 0x00, 0x01)), MEQ, 0x0A5A, MTR, 0x00, 
                    Arg1)
                M600 (Arg0, 0x0B, Local0, Ones)
            }
        }

        /*	Method(m64j, 1) */
        /*	Method(m32j, 1) */
        /* String to Integer conversion of the String sole operand */
        /* of the Method execution control operators (Sleep, Stall) */
        Method (M031, 3, NotSerialized)
        {
            CH03 (Arg0, Z121, 0x02, 0x3143, 0x00)
            /* Sleep */

            Local0 = Timer
            Sleep (Arg1)
            CH03 (Arg0, Z121, 0x03, 0x314A, 0x00)
            Local1 = Timer
            Local2 = (Local1 - Local0)
            If ((Local2 < C08C))
            {
                ERR (Arg0, Z121, 0x314F, 0x00, 0x00, Local2, C08C)
            }

            /* Stall */

            Local0 = Timer
            Stall (Arg2)
            CH03 (Arg0, Z121, 0x04, 0x3157, 0x00)
            Local1 = Timer
            Local2 = (Local1 - Local0)
            If ((Local2 < 0x03DE))
            {
                ERR (Arg0, Z121, 0x315C, 0x00, 0x00, Local2, 0x03DE)
            }
        }

        /* String to Integer conversion of the String TimeoutValue */
        /* (second) operand of the Acquire operator ??? */
        Method (M032, 2, Serialized)
        {
            Mutex (MTX0, 0x00)
            Acquire (MTX0, 0x0000)
            CH03 (Arg0, Z121, 0x05, 0x3167, 0x00)
            Local0 = Timer
            /* Compiler allows only Integer constant as TimeoutValue (Bug 1)
             Acquire(MTX0, arg1)
             */
            CH03 (Arg0, Z121, 0x06, 0x316E, 0x00)
            Local1 = Timer
            Local2 = (Local1 - Local0)
            If ((Local2 < C08C))
            {
                ERR (Arg0, Z121, 0x3173, 0x00, 0x00, Local2, C08C)
            }
        }

        /* String to Integer conversion of the String TimeoutValue */
        /* (second) operand of the Wait operator */
        Method (M033, 2, Serialized)
        {
            Event (EVT0)
            CH03 (Arg0, Z121, 0x07, 0x317D, 0x00)
            Local0 = Timer
            Wait (EVT0, Arg1)
            CH03 (Arg0, Z121, 0x08, 0x3182, 0x00)
            Local1 = Timer
            Local2 = (Local1 - Local0)
            If ((Local2 < C08C))
            {
                ERR (Arg0, Z121, 0x3187, 0x00, 0x00, Local2, C08C)
            }
        }

        /* String to Integer conversion of the String value */
        /* of Predicate of the Method execution control statements */
        /* (If, ElseIf, While) */
        Method (M034, 5, Serialized)
        {
            Name (IST0, 0x00)
            Method (M001, 1, NotSerialized)
            {
                If (Arg0)
                {
                    IST0 = 0x00
                }
            }

            Method (M002, 1, NotSerialized)
            {
                If (Arg0)
                {
                    IST0 = 0x02
                }
            }

            Method (M003, 1, NotSerialized)
            {
                If (Arg0)
                {
                    IST0 = 0x03
                }
            }

            Method (M004, 1, NotSerialized)
            {
                If (Arg0)
                {
                    IST0 = 0x04
                }
            }

            Method (M005, 2, NotSerialized)
            {
                If (Arg0)
                {
                    IST0 = 0xFF
                }
                ElseIf (Arg1)
                {
                    IST0 = 0x00
                }
            }

            Method (M006, 2, NotSerialized)
            {
                If (Arg0)
                {
                    IST0 = 0xFF
                }
                ElseIf (Arg1)
                {
                    IST0 = 0x06
                }
            }

            Method (M007, 2, NotSerialized)
            {
                If (Arg0)
                {
                    IST0 = 0xFF
                }
                ElseIf (Arg1)
                {
                    IST0 = 0x07
                }
            }

            Method (M008, 2, NotSerialized)
            {
                If (Arg0)
                {
                    IST0 = 0xFF
                }
                ElseIf (Arg1)
                {
                    IST0 = 0x08
                }
            }

            Method (M009, 1, NotSerialized)
            {
                While (Arg0)
                {
                    IST0 = 0x00
                    Break
                }
            }

            /* If */

            IST0 = 0x01
            M001 (Arg4)
            M600 (Arg0, 0x00, IST0, 0x01)
            M002 (Arg1)
            M600 (Arg0, 0x01, IST0, 0x02)
            M003 (Arg3)
            M600 (Arg0, 0x02, IST0, 0x03)
            M004 (Arg2)
            M600 (Arg0, 0x03, IST0, 0x04)
            /* ElseIf */

            IST0 = 0x05
            M005 (0x00, Arg4)
            M600 (Arg0, 0x04, IST0, 0x05)
            M006 (0x00, Arg1)
            M600 (Arg0, 0x05, IST0, 0x06)
            M007 (0x00, Arg3)
            M600 (Arg0, 0x06, IST0, 0x07)
            M008 (0x00, Arg2)
            M600 (Arg0, 0x07, IST0, 0x08)
            /* While */

            IST0 = 0x09
            M009 (Arg4)
            M600 (Arg0, 0x08, IST0, 0x09)
        }

        /*	Method(m64k, 1) */
        /*	Method(m32k, 1) */
        /* String to Buffer implicit conversion Cases. */
        /* String to Buffer conversion of the String second operand of */
        /* Logical operators when the first operand is evaluated as Buffer */
        /* (LEqual, LGreater, LGreaterEqual, LLess, LLessEqual, LNotEqual) */
        Method (M035, 4, NotSerialized)
        {
            /* LEqual */

            Local0 = (Buffer (0x05)
                    {
                        "0321"
                    } == Arg1)
            M600 (Arg0, 0x00, Local0, Ones)
            Local0 = (Buffer (0x05)
                    {
                         0x30, 0x33, 0x32, 0x31, 0x01                     // 0321.
                    } == Arg1)
            M600 (Arg0, 0x01, Local0, Zero)
            Local0 = (AUB7 == Arg1)
            M600 (Arg0, 0x02, Local0, Ones)
            Local0 = (AUB3 == Arg1)
            M600 (Arg0, 0x03, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUB7)) == Arg1)
                M600 (Arg0, 0x04, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUB3)) == Arg1)
                M600 (Arg0, 0x05, Local0, Zero)
            }

            Local0 = (DerefOf (PAUB [0x07]) == Arg1)
            M600 (Arg0, 0x06, Local0, Ones)
            Local0 = (DerefOf (PAUB [0x03]) == Arg1)
            M600 (Arg0, 0x07, Local0, Zero)
            /* Method returns Buffer */

            Local0 = (M601 (0x03, 0x07) == Arg1)
            M600 (Arg0, 0x08, Local0, Ones)
            Local0 = (M601 (0x03, 0x03) == Arg1)
            M600 (Arg0, 0x09, Local0, Zero)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x03, 0x07, 0x01)) == Arg1)
                M600 (Arg0, 0x0A, Local0, Ones)
                Local0 = (DerefOf (M602 (0x03, 0x03, 0x01)) == Arg1)
                M600 (Arg0, 0x0B, Local0, Zero)
            }

            /* LGreater */

            Local0 = (Buffer (0x05)
                    {
                        "0321"
                    } > Arg1)
            M600 (Arg0, 0x0C, Local0, Zero)
            Local0 = (Buffer (0x05)
                    {
                         0x30, 0x33, 0x32, 0x31, 0x01                     // 0321.
                    } > Arg1)
            M600 (Arg0, 0x0D, Local0, Ones)
            Local0 = (Buffer (0x04)
                    {
                         0x30, 0x33, 0x32, 0x31                           // 0321
                    } > Arg1)
            M600 (Arg0, 0x0E, Local0, Zero)
            Local0 = (Buffer (0x06)
                    {
                         0x30, 0x33, 0x32, 0x31, 0x00, 0x01               // 0321..
                    } > Arg1)
            M600 (Arg0, 0x0F, Local0, Ones)
            Local0 = (AUB7 > Arg1)
            M600 (Arg0, 0x10, Local0, Zero)
            Local0 = (AUB8 > Arg1)
            M600 (Arg0, 0x11, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUB7)) > Arg1)
                M600 (Arg0, 0x12, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUB8)) > Arg1)
                M600 (Arg0, 0x13, Local0, Ones)
            }

            Local0 = (DerefOf (PAUB [0x07]) > Arg1)
            M600 (Arg0, 0x14, Local0, Zero)
            Local0 = (DerefOf (PAUB [0x08]) > Arg1)
            M600 (Arg0, 0x15, Local0, Ones)
            /* Method returns Buffer */

            Local0 = (M601 (0x03, 0x07) > Arg1)
            M600 (Arg0, 0x16, Local0, Zero)
            Local0 = (M601 (0x03, 0x08) > Arg1)
            M600 (Arg0, 0x17, Local0, Ones)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x03, 0x07, 0x01)) > Arg1)
                M600 (Arg0, 0x18, Local0, Zero)
                Local0 = (DerefOf (M602 (0x03, 0x08, 0x01)) > Arg1)
                M600 (Arg0, 0x19, Local0, Ones)
            }

            /* LGreaterEqual */

            Local0 = (Buffer (0x05)
                        {
                            "0321"
                        } >= Arg1)
            M600 (Arg0, 0x1A, Local0, Ones)
            Local0 = (Buffer (0x05)
                        {
                             0x30, 0x33, 0x32, 0x31, 0x01                     // 0321.
                        } >= Arg1)
            M600 (Arg0, 0x1B, Local0, Ones)
            Local0 = (Buffer (0x04)
                        {
                             0x30, 0x33, 0x32, 0x31                           // 0321
                        } >= Arg1)
            M600 (Arg0, 0x1C, Local0, Zero)
            Local0 = (Buffer (0x06)
                        {
                             0x30, 0x33, 0x32, 0x31, 0x00, 0x01               // 0321..
                        } >= Arg1)
            M600 (Arg0, 0x1D, Local0, Ones)
            Local0 = (AUB7 >= Arg1)
            M600 (Arg0, 0x1E, Local0, Ones)
            Local0 = (AUB8 >= Arg1)
            M600 (Arg0, 0x1F, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUB7)) >= Arg1)
                M600 (Arg0, 0x20, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUB8)) >= Arg1)
                M600 (Arg0, 0x21, Local0, Ones)
            }

            Local0 = (DerefOf (PAUB [0x07]) >= Arg1)
            M600 (Arg0, 0x22, Local0, Ones)
            Local0 = (DerefOf (PAUB [0x08]) >= Arg1)
            M600 (Arg0, 0x23, Local0, Ones)
            /* Method returns Buffer */

            Local0 = (M601 (0x03, 0x07) >= Arg1)
            M600 (Arg0, 0x24, Local0, Ones)
            Local0 = (M601 (0x03, 0x08) >= Arg1)
            M600 (Arg0, 0x25, Local0, Ones)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x03, 0x07, 0x01)) >= Arg1)
                M600 (Arg0, 0x26, Local0, Ones)
                Local0 = (DerefOf (M602 (0x03, 0x08, 0x01)) >= Arg1)
                M600 (Arg0, 0x27, Local0, Ones)
            }

            /* LLess */

            Local0 = (Buffer (0x05)
                    {
                        "0321"
                    } < Arg1)
            M600 (Arg0, 0x28, Local0, Zero)
            Local0 = (Buffer (0x05)
                    {
                         0x30, 0x33, 0x32, 0x31, 0x01                     // 0321.
                    } < Arg1)
            M600 (Arg0, 0x29, Local0, Zero)
            Local0 = (Buffer (0x04)
                    {
                         0x30, 0x33, 0x32, 0x31                           // 0321
                    } < Arg1)
            M600 (Arg0, 0x2A, Local0, Ones)
            Local0 = (Buffer (0x06)
                    {
                         0x30, 0x33, 0x32, 0x31, 0x00, 0x01               // 0321..
                    } < Arg1)
            M600 (Arg0, 0x2B, Local0, Zero)
            Local0 = (AUB7 < Arg1)
            M600 (Arg0, 0x2C, Local0, Zero)
            Local0 = (AUB8 < Arg1)
            M600 (Arg0, 0x2D, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUB7)) < Arg1)
                M600 (Arg0, 0x2E, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUB8)) < Arg1)
                M600 (Arg0, 0x2F, Local0, Zero)
            }

            Local0 = (DerefOf (PAUB [0x07]) < Arg1)
            M600 (Arg0, 0x30, Local0, Zero)
            Local0 = (DerefOf (PAUB [0x08]) < Arg1)
            M600 (Arg0, 0x31, Local0, Zero)
            /* Method returns Buffer */

            Local0 = (M601 (0x03, 0x07) < Arg1)
            M600 (Arg0, 0x32, Local0, Zero)
            Local0 = (M601 (0x03, 0x08) < Arg1)
            M600 (Arg0, 0x33, Local0, Zero)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x03, 0x07, 0x01)) < Arg1)
                M600 (Arg0, 0x34, Local0, Zero)
                Local0 = (DerefOf (M602 (0x03, 0x08, 0x01)) < Arg1)
                M600 (Arg0, 0x35, Local0, Zero)
            }

            /* LLessEqual */

            Local0 = (Buffer (0x05)
                        {
                            "0321"
                        } <= Arg1)
            M600 (Arg0, 0x36, Local0, Ones)
            Local0 = (Buffer (0x05)
                        {
                             0x30, 0x33, 0x32, 0x31, 0x01                     // 0321.
                        } <= Arg1)
            M600 (Arg0, 0x37, Local0, Zero)
            Local0 = (Buffer (0x04)
                        {
                             0x30, 0x33, 0x32, 0x31                           // 0321
                        } <= Arg1)
            M600 (Arg0, 0x38, Local0, Ones)
            Local0 = (Buffer (0x06)
                        {
                             0x30, 0x33, 0x32, 0x31, 0x00, 0x01               // 0321..
                        } <= Arg1)
            M600 (Arg0, 0x39, Local0, Zero)
            Local0 = (AUB7 <= Arg1)
            M600 (Arg0, 0x3A, Local0, Ones)
            Local0 = (AUB8 <= Arg1)
            M600 (Arg0, 0x3B, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUB7)) <= Arg1)
                M600 (Arg0, 0x3C, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUB8)) <= Arg1)
                M600 (Arg0, 0x3D, Local0, Zero)
            }

            Local0 = (DerefOf (PAUB [0x07]) <= Arg1)
            M600 (Arg0, 0x3E, Local0, Ones)
            Local0 = (DerefOf (PAUB [0x08]) <= Arg1)
            M600 (Arg0, 0x3F, Local0, Zero)
            /* Method returns Buffer */

            Local0 = (M601 (0x03, 0x07) <= Arg1)
            M600 (Arg0, 0x40, Local0, Ones)
            Local0 = (M601 (0x03, 0x08) <= Arg1)
            M600 (Arg0, 0x41, Local0, Zero)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x03, 0x07, 0x01)) <= Arg1)
                M600 (Arg0, 0x42, Local0, Ones)
                Local0 = (DerefOf (M602 (0x03, 0x08, 0x01)) <= Arg1)
                M600 (Arg0, 0x43, Local0, Zero)
            }

            /* LNotEqual */

            Local0 = (Buffer (0x05)
                        {
                            "0321"
                        } != Arg1)
            M600 (Arg0, 0x44, Local0, Zero)
            Local0 = (Buffer (0x05)
                        {
                             0x30, 0x33, 0x32, 0x31, 0x01                     // 0321.
                        } != Arg1)
            M600 (Arg0, 0x45, Local0, Ones)
            Local0 = (Buffer (0x04)
                        {
                             0x30, 0x33, 0x32, 0x31                           // 0321
                        } != Arg1)
            M600 (Arg0, 0x46, Local0, Ones)
            Local0 = (Buffer (0x06)
                        {
                             0x30, 0x33, 0x32, 0x31, 0x00, 0x01               // 0321..
                        } != Arg1)
            M600 (Arg0, 0x47, Local0, Ones)
            Local0 = (AUB7 != Arg1)
            M600 (Arg0, 0x48, Local0, Zero)
            Local0 = (AUB8 != Arg1)
            M600 (Arg0, 0x49, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUB7)) != Arg1)
                M600 (Arg0, 0x4A, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUB8)) != Arg1)
                M600 (Arg0, 0x4B, Local0, Ones)
            }

            Local0 = (DerefOf (PAUB [0x07]) != Arg1)
            M600 (Arg0, 0x4C, Local0, Zero)
            Local0 = (DerefOf (PAUB [0x08]) != Arg1)
            M600 (Arg0, 0x4D, Local0, Ones)
            /* Method returns Buffer */

            Local0 = (M601 (0x03, 0x07) != Arg1)
            M600 (Arg0, 0x4E, Local0, Zero)
            Local0 = (M601 (0x03, 0x08) != Arg1)
            M600 (Arg0, 0x4F, Local0, Ones)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x03, 0x07, 0x01)) != Arg1)
                M600 (Arg0, 0x50, Local0, Zero)
                Local0 = (DerefOf (M602 (0x03, 0x08, 0x01)) != Arg1)
                M600 (Arg0, 0x51, Local0, Ones)
            }

            /* Boundary Cases */

            Local0 = (Buffer (0x01)
                    {
                         0x00                                             // .
                    } == Arg2)
            M600 (Arg0, 0x52, Local0, Ones)
            Local0 = (Buffer (0x01)
                    {
                         0x01                                             // .
                    } == Arg2)
            M600 (Arg0, 0x53, Local0, Zero)
            Local0 = (Buffer (0x01)
                    {
                         0x00                                             // .
                    } > Arg2)
            M600 (Arg0, 0x54, Local0, Zero)
            Local0 = (Buffer (0x01)
                    {
                         0x01                                             // .
                    } > Arg2)
            M600 (Arg0, 0x55, Local0, Ones)
            Local0 = (Buffer (0x01)
                        {
                             0x00                                             // .
                        } >= Arg2)
            M600 (Arg0, 0x56, Local0, Ones)
            Local0 = (Buffer (0x01)
                    {
                         0x01                                             // .
                    } > Arg2)
            M600 (Arg0, 0x57, Local0, Ones)
            Local0 = (Buffer (0x01)
                    {
                         0x00                                             // .
                    } < Arg2)
            M600 (Arg0, 0x58, Local0, Zero)
            Local0 = (Buffer (0x01)
                    {
                         0x01                                             // .
                    } < Arg2)
            M600 (Arg0, 0x59, Local0, Zero)
            Local0 = (Buffer (0x01)
                        {
                             0x00                                             // .
                        } <= Arg2)
            M600 (Arg0, 0x5A, Local0, Ones)
            Local0 = (Buffer (0x01)
                        {
                             0x01                                             // .
                        } <= Arg2)
            M600 (Arg0, 0x5B, Local0, Zero)
            Local0 = (Buffer (0x01)
                        {
                             0x00                                             // .
                        } != Arg2)
            M600 (Arg0, 0x5C, Local0, Zero)
            Local0 = (Buffer (0x01)
                        {
                             0x01                                             // .
                        } != Arg2)
            M600 (Arg0, 0x5D, Local0, Ones)
            Local0 = (Buffer (0xC9)
                    {
                        "!\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ !\"#$%&\'()*"
                    } == Arg3)
            M600 (Arg0, 0x5E, Local0, Ones)
            Local0 = (Buffer (0xC9)
                    {
                        /* 0000 */  0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,  // !"#$%&'(
                        /* 0008 */  0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30,  // )*+,-./0
                        /* 0010 */  0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,  // 12345678
                        /* 0018 */  0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40,  // 9:;<=>?@
                        /* 0020 */  0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,  // ABCDEFGH
                        /* 0028 */  0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,  // IJKLMNOP
                        /* 0030 */  0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,  // QRSTUVWX
                        /* 0038 */  0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60,  // YZ[\]^_`
                        /* 0040 */  0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,  // abcdefgh
                        /* 0048 */  0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70,  // ijklmnop
                        /* 0050 */  0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,  // qrstuvwx
                        /* 0058 */  0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x20, 0x21,  // yz{|}~ !
                        /* 0060 */  0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,  // "#$%&'()
                        /* 0068 */  0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31,  // *+,-./01
                        /* 0070 */  0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,  // 23456789
                        /* 0078 */  0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41,  // :;<=>?@A
                        /* 0080 */  0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,  // BCDEFGHI
                        /* 0088 */  0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51,  // JKLMNOPQ
                        /* 0090 */  0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,  // RSTUVWXY
                        /* 0098 */  0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61,  // Z[\]^_`a
                        /* 00A0 */  0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,  // bcdefghi
                        /* 00A8 */  0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71,  // jklmnopq
                        /* 00B0 */  0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79,  // rstuvwxy
                        /* 00B8 */  0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x20, 0x21, 0x22,  // z{|}~ !"
                        /* 00C0 */  0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A,  // #$%&'()*
                        /* 00C8 */  0x01                                             // .
                    } == Arg3)
            M600 (Arg0, 0x5F, Local0, Zero)
            Local0 = (Buffer (0xC9)
                    {
                        "!\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ !\"#$%&\'()*"
                    } > Arg3)
            M600 (Arg0, 0x60, Local0, Zero)
            Local0 = (Buffer (0xC9)
                    {
                        /* 0000 */  0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,  // !"#$%&'(
                        /* 0008 */  0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30,  // )*+,-./0
                        /* 0010 */  0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,  // 12345678
                        /* 0018 */  0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40,  // 9:;<=>?@
                        /* 0020 */  0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,  // ABCDEFGH
                        /* 0028 */  0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,  // IJKLMNOP
                        /* 0030 */  0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,  // QRSTUVWX
                        /* 0038 */  0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60,  // YZ[\]^_`
                        /* 0040 */  0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,  // abcdefgh
                        /* 0048 */  0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70,  // ijklmnop
                        /* 0050 */  0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,  // qrstuvwx
                        /* 0058 */  0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x20, 0x21,  // yz{|}~ !
                        /* 0060 */  0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,  // "#$%&'()
                        /* 0068 */  0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31,  // *+,-./01
                        /* 0070 */  0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,  // 23456789
                        /* 0078 */  0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41,  // :;<=>?@A
                        /* 0080 */  0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,  // BCDEFGHI
                        /* 0088 */  0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51,  // JKLMNOPQ
                        /* 0090 */  0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,  // RSTUVWXY
                        /* 0098 */  0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61,  // Z[\]^_`a
                        /* 00A0 */  0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,  // bcdefghi
                        /* 00A8 */  0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71,  // jklmnopq
                        /* 00B0 */  0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79,  // rstuvwxy
                        /* 00B8 */  0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x20, 0x21, 0x22,  // z{|}~ !"
                        /* 00C0 */  0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A,  // #$%&'()*
                        /* 00C8 */  0x01                                             // .
                    } > Arg3)
            M600 (Arg0, 0x61, Local0, Ones)
            Local0 = (Buffer (0xC9)
                        {
                            "!\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ !\"#$%&\'()*"
                        } >= Arg3)
            M600 (Arg0, 0x62, Local0, Ones)
            Local0 = (Buffer (0xC9)
                    {
                        /* 0000 */  0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,  // !"#$%&'(
                        /* 0008 */  0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30,  // )*+,-./0
                        /* 0010 */  0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,  // 12345678
                        /* 0018 */  0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40,  // 9:;<=>?@
                        /* 0020 */  0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,  // ABCDEFGH
                        /* 0028 */  0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,  // IJKLMNOP
                        /* 0030 */  0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,  // QRSTUVWX
                        /* 0038 */  0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60,  // YZ[\]^_`
                        /* 0040 */  0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,  // abcdefgh
                        /* 0048 */  0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70,  // ijklmnop
                        /* 0050 */  0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,  // qrstuvwx
                        /* 0058 */  0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x20, 0x21,  // yz{|}~ !
                        /* 0060 */  0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,  // "#$%&'()
                        /* 0068 */  0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31,  // *+,-./01
                        /* 0070 */  0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,  // 23456789
                        /* 0078 */  0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41,  // :;<=>?@A
                        /* 0080 */  0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,  // BCDEFGHI
                        /* 0088 */  0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51,  // JKLMNOPQ
                        /* 0090 */  0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,  // RSTUVWXY
                        /* 0098 */  0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61,  // Z[\]^_`a
                        /* 00A0 */  0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,  // bcdefghi
                        /* 00A8 */  0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71,  // jklmnopq
                        /* 00B0 */  0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79,  // rstuvwxy
                        /* 00B8 */  0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x20, 0x21, 0x22,  // z{|}~ !"
                        /* 00C0 */  0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A,  // #$%&'()*
                        /* 00C8 */  0x01                                             // .
                    } > Arg3)
            M600 (Arg0, 0x63, Local0, Ones)
            Local0 = (Buffer (0xC9)
                    {
                        "!\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ !\"#$%&\'()*"
                    } < Arg3)
            M600 (Arg0, 0x64, Local0, Zero)
            Local0 = (Buffer (0xC9)
                    {
                        /* 0000 */  0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,  // !"#$%&'(
                        /* 0008 */  0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30,  // )*+,-./0
                        /* 0010 */  0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,  // 12345678
                        /* 0018 */  0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40,  // 9:;<=>?@
                        /* 0020 */  0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,  // ABCDEFGH
                        /* 0028 */  0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,  // IJKLMNOP
                        /* 0030 */  0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,  // QRSTUVWX
                        /* 0038 */  0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60,  // YZ[\]^_`
                        /* 0040 */  0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,  // abcdefgh
                        /* 0048 */  0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70,  // ijklmnop
                        /* 0050 */  0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,  // qrstuvwx
                        /* 0058 */  0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x20, 0x21,  // yz{|}~ !
                        /* 0060 */  0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,  // "#$%&'()
                        /* 0068 */  0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31,  // *+,-./01
                        /* 0070 */  0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,  // 23456789
                        /* 0078 */  0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41,  // :;<=>?@A
                        /* 0080 */  0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,  // BCDEFGHI
                        /* 0088 */  0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51,  // JKLMNOPQ
                        /* 0090 */  0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,  // RSTUVWXY
                        /* 0098 */  0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61,  // Z[\]^_`a
                        /* 00A0 */  0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,  // bcdefghi
                        /* 00A8 */  0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71,  // jklmnopq
                        /* 00B0 */  0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79,  // rstuvwxy
                        /* 00B8 */  0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x20, 0x21, 0x22,  // z{|}~ !"
                        /* 00C0 */  0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A,  // #$%&'()*
                        /* 00C8 */  0x01                                             // .
                    } < Arg3)
            M600 (Arg0, 0x65, Local0, Zero)
            Local0 = (Buffer (0xC9)
                        {
                            "!\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ !\"#$%&\'()*"
                        } <= Arg3)
            M600 (Arg0, 0x66, Local0, Ones)
            Local0 = (Buffer (0xC9)
                        {
                            /* 0000 */  0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,  // !"#$%&'(
                            /* 0008 */  0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30,  // )*+,-./0
                            /* 0010 */  0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,  // 12345678
                            /* 0018 */  0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40,  // 9:;<=>?@
                            /* 0020 */  0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,  // ABCDEFGH
                            /* 0028 */  0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,  // IJKLMNOP
                            /* 0030 */  0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,  // QRSTUVWX
                            /* 0038 */  0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60,  // YZ[\]^_`
                            /* 0040 */  0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,  // abcdefgh
                            /* 0048 */  0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70,  // ijklmnop
                            /* 0050 */  0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,  // qrstuvwx
                            /* 0058 */  0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x20, 0x21,  // yz{|}~ !
                            /* 0060 */  0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,  // "#$%&'()
                            /* 0068 */  0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31,  // *+,-./01
                            /* 0070 */  0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,  // 23456789
                            /* 0078 */  0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41,  // :;<=>?@A
                            /* 0080 */  0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,  // BCDEFGHI
                            /* 0088 */  0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51,  // JKLMNOPQ
                            /* 0090 */  0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,  // RSTUVWXY
                            /* 0098 */  0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61,  // Z[\]^_`a
                            /* 00A0 */  0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,  // bcdefghi
                            /* 00A8 */  0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71,  // jklmnopq
                            /* 00B0 */  0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79,  // rstuvwxy
                            /* 00B8 */  0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x20, 0x21, 0x22,  // z{|}~ !"
                            /* 00C0 */  0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A,  // #$%&'()*
                            /* 00C8 */  0x01                                             // .
                        } <= Arg3)
            M600 (Arg0, 0x67, Local0, Zero)
            Local0 = (Buffer (0xC9)
                        {
                            "!\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ !\"#$%&\'()*"
                        } != Arg3)
            M600 (Arg0, 0x68, Local0, Zero)
            Local0 = (Buffer (0xC9)
                        {
                            /* 0000 */  0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,  // !"#$%&'(
                            /* 0008 */  0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30,  // )*+,-./0
                            /* 0010 */  0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,  // 12345678
                            /* 0018 */  0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40,  // 9:;<=>?@
                            /* 0020 */  0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,  // ABCDEFGH
                            /* 0028 */  0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,  // IJKLMNOP
                            /* 0030 */  0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,  // QRSTUVWX
                            /* 0038 */  0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60,  // YZ[\]^_`
                            /* 0040 */  0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,  // abcdefgh
                            /* 0048 */  0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70,  // ijklmnop
                            /* 0050 */  0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,  // qrstuvwx
                            /* 0058 */  0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x20, 0x21,  // yz{|}~ !
                            /* 0060 */  0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,  // "#$%&'()
                            /* 0068 */  0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31,  // *+,-./01
                            /* 0070 */  0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,  // 23456789
                            /* 0078 */  0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41,  // :;<=>?@A
                            /* 0080 */  0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,  // BCDEFGHI
                            /* 0088 */  0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51,  // JKLMNOPQ
                            /* 0090 */  0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,  // RSTUVWXY
                            /* 0098 */  0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61,  // Z[\]^_`a
                            /* 00A0 */  0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,  // bcdefghi
                            /* 00A8 */  0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71,  // jklmnopq
                            /* 00B0 */  0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79,  // rstuvwxy
                            /* 00B8 */  0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x20, 0x21, 0x22,  // z{|}~ !"
                            /* 00C0 */  0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A,  // #$%&'()*
                            /* 00C8 */  0x01                                             // .
                        } != Arg3)
            M600 (Arg0, 0x69, Local0, Ones)
        }

        /* String to Buffer conversion of the String second operand of */
        /* Concatenate operator when the first operand is evaluated as Buffer */
        Method (M036, 4, NotSerialized)
        {
            Local0 = Concatenate (Buffer (0x01)
                    {
                         0x5A                                             // Z
                    }, Arg1)
            M600 (Arg0, 0x00, Local0, BB29)
            Local0 = Concatenate (Buffer (0x02)
                    {
                        "Z"
                    }, Arg1)
            M600 (Arg0, 0x01, Local0, BB2A)
            Local0 = Concatenate (AUB0, Arg1)
            M600 (Arg0, 0x02, Local0, BB29)
            Local0 = Concatenate (AUB1, Arg1)
            M600 (Arg0, 0x03, Local0, BB2A)
            If (Y078)
            {
                Local0 = Concatenate (DerefOf (RefOf (AUB0)), Arg1)
                M600 (Arg0, 0x04, Local0, BB29)
                Local0 = Concatenate (DerefOf (RefOf (AUB1)), Arg1)
                M600 (Arg0, 0x05, Local0, BB2A)
            }

            Local0 = Concatenate (DerefOf (PAUB [0x00]), Arg1)
            M600 (Arg0, 0x06, Local0, BB29)
            Local0 = Concatenate (DerefOf (PAUB [0x01]), Arg1)
            M600 (Arg0, 0x07, Local0, BB2A)
            /* Method returns Buffer */

            Local0 = Concatenate (M601 (0x03, 0x00), Arg1)
            M600 (Arg0, 0x08, Local0, BB29)
            Local0 = Concatenate (M601 (0x03, 0x01), Arg1)
            M600 (Arg0, 0x09, Local0, BB2A)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Local0 = Concatenate (DerefOf (M602 (0x03, 0x00, 0x01)), Arg1)
                M600 (Arg0, 0x0A, Local0, BB29)
                Local0 = Concatenate (DerefOf (M602 (0x03, 0x01, 0x01)), Arg1)
                M600 (Arg0, 0x0B, Local0, BB2A)
            }

            Concatenate (Buffer (0x01)
                {
                     0x5A                                             // Z
                }, Arg1, Local0)
            M600 (Arg0, 0x0C, Local0, BB29)
            Concatenate (Buffer (0x02)
                {
                    "Z"
                }, Arg1, Local0)
            M600 (Arg0, 0x0D, Local0, BB2A)
            Concatenate (AUB0, Arg1, Local0)
            M600 (Arg0, 0x0E, Local0, BB29)
            Concatenate (AUB1, Arg1, Local0)
            M600 (Arg0, 0x0F, Local0, BB2A)
            If (Y078)
            {
                Concatenate (DerefOf (RefOf (AUB0)), Arg1, Local0)
                M600 (Arg0, 0x10, Local0, BB29)
                Concatenate (DerefOf (RefOf (AUB1)), Arg1, Local0)
                M600 (Arg0, 0x11, Local0, BB2A)
            }

            Concatenate (DerefOf (PAUB [0x00]), Arg1, Local0)
            M600 (Arg0, 0x12, Local0, BB29)
            Concatenate (DerefOf (PAUB [0x01]), Arg1, Local0)
            M600 (Arg0, 0x13, Local0, BB2A)
            /* Method returns Buffer */

            Concatenate (M601 (0x03, 0x00), Arg1, Local0)
            M600 (Arg0, 0x14, Local0, BB29)
            Concatenate (M601 (0x03, 0x01), Arg1, Local0)
            M600 (Arg0, 0x15, Local0, BB2A)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Concatenate (DerefOf (M602 (0x03, 0x00, 0x01)), Arg1, Local0)
                M600 (Arg0, 0x16, Local0, BB29)
                Concatenate (DerefOf (M602 (0x03, 0x01, 0x01)), Arg1, Local0)
                M600 (Arg0, 0x17, Local0, BB2A)
            }

            /* Boundary Cases */

            Local0 = Concatenate (Buffer (0x01)
                    {
                         0x5A                                             // Z
                    }, Arg2)
            M600 (Arg0, 0x18, Local0, BB2B)
            Local0 = Concatenate (Buffer (0x02)
                    {
                        "Z"
                    }, Arg2)
            M600 (Arg0, 0x19, Local0, BB2C)
            Local1 = 0x00
            Local0 = Concatenate (Buffer (Local1){}, Arg3)
            M600 (Arg0, 0x1A, Local0, BB2D)
        }

        /* String to Buffer conversion of the String Source operand of */
        /* ToString operator (has a visual effect in shortening of the */
        /* String taken the null character, that is impossible to show */
        /* with an immediate String constant). */
        Method (M037, 4, NotSerialized)
        {
            Local0 = ToString (Arg1, Ones)
            M600 (Arg0, 0x00, Local0, BS20)
            Local0 = ToString (Arg1, 0x03)
            M600 (Arg0, 0x01, Local0, BS21)
            Local0 = ToString (Arg1, AUI0)
            M600 (Arg0, 0x02, Local0, BS20)
            Local0 = ToString (Arg1, AUI7)
            M600 (Arg0, 0x03, Local0, BS21)
            If (Y078)
            {
                Local0 = ToString (Arg1, DerefOf (RefOf (AUI0)))
                M600 (Arg0, 0x04, Local0, BS20)
                Local0 = ToString (Arg1, DerefOf (RefOf (AUI7)))
                M600 (Arg0, 0x05, Local0, BS21)
            }

            Local0 = ToString (Arg1, DerefOf (PAUI [0x00]))
            M600 (Arg0, 0x06, Local0, BS20)
            Local0 = ToString (Arg1, DerefOf (PAUI [0x07]))
            M600 (Arg0, 0x07, Local0, BS21)
            /* Method returns Length parameter */

            Local0 = ToString (Arg1, M601 (0x01, 0x00))
            M600 (Arg0, 0x08, Local0, BS20)
            Local0 = ToString (Arg1, M601 (0x01, 0x07))
            M600 (Arg0, 0x09, Local0, BS21)
            /* Method returns Reference to Length parameter */

            If (Y500)
            {
                Local0 = ToString (Arg1, DerefOf (M601 (0x01, 0x00)))
                M600 (Arg0, 0x0A, Local0, BS20)
                Local0 = ToString (Arg1, DerefOf (M601 (0x01, 0x07)))
                M600 (Arg0, 0x0B, Local0, BS21)
            }

            ToString (Arg1, Ones, Local0)
            M600 (Arg0, 0x0C, Local0, BS20)
            ToString (Arg1, 0x03, Local0)
            M600 (Arg0, 0x0D, Local0, BS21)
            ToString (Arg1, AUI0, Local0)
            M600 (Arg0, 0x0E, Local0, BS20)
            ToString (Arg1, AUI7, Local0)
            M600 (Arg0, 0x0F, Local0, BS21)
            If (Y078)
            {
                ToString (Arg1, DerefOf (RefOf (AUI0)), Local0)
                M600 (Arg0, 0x10, Local0, BS20)
                ToString (Arg1, DerefOf (RefOf (AUI7)), Local0)
                M600 (Arg0, 0x11, Local0, BS21)
            }

            ToString (Arg1, DerefOf (PAUI [0x00]), Local0)
            M600 (Arg0, 0x12, Local0, BS20)
            ToString (Arg1, DerefOf (PAUI [0x07]), Local0)
            M600 (Arg0, 0x13, Local0, BS21)
            /* Method returns Length parameter */

            ToString (Arg1, M601 (0x01, 0x00), Local0)
            M600 (Arg0, 0x14, Local0, BS20)
            ToString (Arg1, M601 (0x01, 0x07), Local0)
            M600 (Arg0, 0x15, Local0, BS21)
            /* Method returns Reference to Length parameter */

            If (Y500)
            {
                ToString (Arg1, DerefOf (M601 (0x01, 0x00)), Local0)
                M600 (Arg0, 0x16, Local0, BS20)
                ToString (Arg1, DerefOf (M601 (0x01, 0x07)), Local0)
                M600 (Arg0, 0x17, Local0, BS21)
            }

            /* Boundary Cases */

            Local0 = ToString (Arg2, Ones)
            M600 (Arg0, 0x18, Local0, BS22)
            Local0 = ToString (Arg2, 0x03)
            M600 (Arg0, 0x19, Local0, BS22)
            Local0 = ToString (Arg3, Ones)
            M600 (Arg0, 0x1A, Local0, BS23)
            Local0 = ToString (Arg3, 0x03)
            M600 (Arg0, 0x1B, Local0, BS24)
        }

        /*	Method(m038, 1) */
        /*	Method(m039, 1) */
        /* Buffer to Integer implicit conversion Cases. */
        /* Buffer to Integer conversion of the Buffer sole operand */
        /* of the 1-parameter Integer arithmetic operators */
        /* (Decrement, Increment, FindSetLeftBit, FindSetRightBit, Not) */
        Method (M64L, 3, NotSerialized)
        {
            /* Decrement */

            If (Y501)
            {
                Local0 = Arg1--
                M600 (Arg0, 0x00, Local0, BI12)
                Local0 = Arg2--
                M600 (Arg0, 0x01, Local0, BI16)
            }

            /* Increment */

            If (Y501)
            {
                Local0 = Arg1++
                M600 (Arg0, 0x02, Local0, BI13)
                Local0 = Arg2++
                M600 (Arg0, 0x03, Local0, BI17)
            }

            /* FindSetLeftBit */

            Local0 = FindSetLeftBit (Arg1)
            M600 (Arg0, 0x04, Local0, 0x0A)
            Local0 = FindSetLeftBit (Arg2)
            M600 (Arg0, 0x05, Local0, 0x40)
            /* FindSetRightBit */

            Local0 = FindSetRightBit (Arg1)
            M600 (Arg0, 0x06, Local0, 0x01)
            Local0 = FindSetRightBit (Arg2)
            M600 (Arg0, 0x07, Local0, 0x03)
            /* Not */

            Store (~Arg1, Local0)
            M600 (Arg0, 0x08, Local0, 0xFFFFFFFFFFFFFCDE)
            Store (~Arg2, Local0)
            M600 (Arg0, 0x09, Local0, 0x01834C6E29AF5D7B)
        }

        Method (M32L, 3, NotSerialized)
        {
            /* Decrement */

            If (Y501)
            {
                Local0 = Arg1--
                M600 (Arg0, 0x00, Local0, BI12)
                Local0 = Arg2--
                M600 (Arg0, 0x01, Local0, BI18)
            }

            /* Increment */

            If (Y501)
            {
                Local0 = Arg1++
                M600 (Arg0, 0x02, Local0, BI13)
                Local0 = Arg2++
                M600 (Arg0, 0x03, Local0, BI19)
            }

            /* FindSetLeftBit */

            Local0 = FindSetLeftBit (Arg1)
            M600 (Arg0, 0x04, Local0, 0x0A)
            Local0 = FindSetLeftBit (Arg2)
            M600 (Arg0, 0x05, Local0, 0x20)
            /* FindSetRightBit */

            Local0 = FindSetRightBit (Arg1)
            M600 (Arg0, 0x06, Local0, 0x01)
            Local0 = FindSetRightBit (Arg2)
            M600 (Arg0, 0x07, Local0, 0x03)
            /* Not */

            Store (~Arg1, Local0)
            M600 (Arg0, 0x08, Local0, 0xFFFFFCDE)
            Store (~Arg2, Local0)
            M600 (Arg0, 0x09, Local0, 0x29AF5D7B)
        }

        /* Buffer to Integer conversion of the Buffer sole operand */
        /* of the LNot Logical Integer operator */
        Method (M03A, 4, NotSerialized)
        {
            Local0 = !Arg3
            M600 (Arg0, 0x00, Local0, Ones)
            Local0 = !Arg1
            M600 (Arg0, 0x01, Local0, Zero)
            If (F64)
            {
                Local0 = !Arg2
                M600 (Arg0, 0x02, Local0, Zero)
            }
            Else
            {
                Local0 = !Arg2
                M600 (Arg0, 0x03, Local0, Zero)
            }
        }

        /* Buffer to Integer conversion of the Buffer sole operand */
        /* of the FromBCD and ToBCD conversion operators */
        Method (M64M, 4, NotSerialized)
        {
            /* FromBCD */

            Local0 = FromBCD (Arg1)
            M600 (Arg0, 0x02, Local0, 0x0141)
            Local0 = FromBCD (Arg2)
            M600 (Arg0, 0x03, Local0, 0x000D76162EE9EC35)
            FromBCD (Arg1, Local0)
            M600 (Arg0, 0x02, Local0, 0x0141)
            FromBCD (Arg2, Local0)
            M600 (Arg0, 0x03, Local0, 0x000D76162EE9EC35)
            /* ToBCD */

            Local0 = ToBCD (Arg1)
            M600 (Arg0, 0x04, Local0, 0x0801)
            /* ??? No error of iASL on constant folding */

            Local0 = ToBCD (Arg3)
            M600 (Arg0, 0x05, Local0, 0x3789012345678901)
            ToBCD (Arg1, Local0)
            M600 (Arg0, 0x04, Local0, 0x0801)
            ToBCD (Arg3, Local0)
            M600 (Arg0, 0x05, Local0, 0x3789012345678901)
        }

        Method (M32M, 4, NotSerialized)
        {
            /* FromBCD */

            Local0 = FromBCD (Arg1)
            M600 (Arg0, 0x02, Local0, 0x0141)
            Local0 = FromBCD (Arg2)
            M600 (Arg0, 0x03, Local0, 0x055F2CC0)
            FromBCD (Arg1, Local0)
            M600 (Arg0, 0x02, Local0, 0x0141)
            FromBCD (Arg2, Local0)
            M600 (Arg0, 0x03, Local0, 0x055F2CC0)
            /* ToBCD */

            Local0 = ToBCD (Arg1)
            M600 (Arg0, 0x04, Local0, 0x0801)
            Local0 = ToBCD (Arg3)
            M600 (Arg0, 0x05, Local0, 0x90123456)
            ToBCD (Arg1, Local0)
            M600 (Arg0, 0x04, Local0, 0x0801)
            ToBCD (Arg3, Local0)
            M600 (Arg0, 0x05, Local0, 0x90123456)
        }

        /* Buffer to Integer conversion of each Buffer operand */
        /* of the 2-parameter Integer arithmetic operators */
        /* Add, And, Divide, Mod, Multiply, NAnd, NOr, Or, */
        /* ShiftLeft, ShiftRight, Subtract, Xor */
        /* Add, common 32-bit/64-bit test */
        Method (M03B, 2, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg1 + 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0x0321)
            Store ((Arg1 + 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0x0322)
            Store ((Arg1 + AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0x0321)
            Store ((Arg1 + AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0x0322)
            If (Y078)
            {
                Store ((Arg1 + DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0x0321)
                Store ((Arg1 + DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0x0322)
            }

            Store ((Arg1 + DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0x0321)
            Store ((Arg1 + DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0x0322)
            /* Method returns Integer */

            Store ((Arg1 + M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0x0321)
            Store ((Arg1 + M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0x0322)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg1 + DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0x0321)
                Store ((Arg1 + DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x0322)
            }

            Local0 = (Arg1 + 0x00)
            M600 (Arg0, 0x0C, Local0, 0x0321)
            Local0 = (Arg1 + 0x01)
            M600 (Arg0, 0x0D, Local0, 0x0322)
            Local0 = (Arg1 + AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0x0321)
            Local0 = (Arg1 + AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0x0322)
            If (Y078)
            {
                Local0 = (Arg1 + DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0x0321)
                Local0 = (Arg1 + DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0x0322)
            }

            Local0 = (Arg1 + DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0x0321)
            Local0 = (Arg1 + DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0x0322)
            /* Method returns Integer */

            Local0 = (Arg1 + M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0x0321)
            Local0 = (Arg1 + M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0x0322)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg1 + DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0x0321)
                Local0 = (Arg1 + DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0x0322)
            }

            /* Conversion of the second operand */

            Store ((0x00 + Arg1), Local0)
            M600 (Arg0, 0x18, Local0, 0x0321)
            Store ((0x01 + Arg1), Local0)
            M600 (Arg0, 0x19, Local0, 0x0322)
            Store ((AUI5 + Arg1), Local0)
            M600 (Arg0, 0x1A, Local0, 0x0321)
            Store ((AUI6 + Arg1), Local0)
            M600 (Arg0, 0x1B, Local0, 0x0322)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) + Arg1), Local0)
                M600 (Arg0, 0x1C, Local0, 0x0321)
                Store ((DerefOf (RefOf (AUI6)) + Arg1), Local0)
                M600 (Arg0, 0x1D, Local0, 0x0322)
            }

            Store ((DerefOf (PAUI [0x05]) + Arg1), Local0)
            M600 (Arg0, 0x1E, Local0, 0x0321)
            Store ((DerefOf (PAUI [0x06]) + Arg1), Local0)
            M600 (Arg0, 0x1F, Local0, 0x0322)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) + Arg1), Local0)
            M600 (Arg0, 0x20, Local0, 0x0321)
            Store ((M601 (0x01, 0x06) + Arg1), Local0)
            M600 (Arg0, 0x21, Local0, 0x0322)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) + Arg1), Local0)
                M600 (Arg0, 0x22, Local0, 0x0321)
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) + Arg1), Local0)
                M600 (Arg0, 0x23, Local0, 0x0322)
            }

            Local0 = (0x00 + Arg1)
            M600 (Arg0, 0x24, Local0, 0x0321)
            Local0 = (0x01 + Arg1)
            M600 (Arg0, 0x25, Local0, 0x0322)
            Local0 = (AUI5 + Arg1)
            M600 (Arg0, 0x26, Local0, 0x0321)
            Local0 = (AUI6 + Arg1)
            M600 (Arg0, 0x27, Local0, 0x0322)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) + Arg1)
                M600 (Arg0, 0x28, Local0, 0x0321)
                Local0 = (DerefOf (RefOf (AUI6)) + Arg1)
                M600 (Arg0, 0x29, Local0, 0x0322)
            }

            Local0 = (DerefOf (PAUI [0x05]) + Arg1)
            M600 (Arg0, 0x2A, Local0, 0x0321)
            Local0 = (DerefOf (PAUI [0x06]) + Arg1)
            M600 (Arg0, 0x2B, Local0, 0x0322)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) + Arg1)
            M600 (Arg0, 0x2C, Local0, 0x0321)
            Local0 = (M601 (0x01, 0x06) + Arg1)
            M600 (Arg0, 0x2D, Local0, 0x0322)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) + Arg1)
                M600 (Arg0, 0x2E, Local0, 0x0321)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) + Arg1)
                M600 (Arg0, 0x2F, Local0, 0x0322)
            }
        }

        /* Add, 64-bit */

        Method (M03C, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 + 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 + 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0xFE7CB391D650A285)
            Store ((Arg2 + AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 + AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0xFE7CB391D650A285)
            If (Y078)
            {
                Store ((Arg2 + DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 + DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0xFE7CB391D650A285)
            }

            Store ((Arg2 + DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 + DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0xFE7CB391D650A285)
            /* Method returns Integer */

            Store ((Arg2 + M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 + M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0xFE7CB391D650A285)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 + DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 + DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0xFE7CB391D650A285)
            }

            Local0 = (Arg2 + 0x00)
            M600 (Arg0, 0x0C, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 + 0x01)
            M600 (Arg0, 0x0D, Local0, 0xFE7CB391D650A285)
            Local0 = (Arg2 + AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 + AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0xFE7CB391D650A285)
            If (Y078)
            {
                Local0 = (Arg2 + DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0xFE7CB391D650A284)
                Local0 = (Arg2 + DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0xFE7CB391D650A285)
            }

            Local0 = (Arg2 + DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 + DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0xFE7CB391D650A285)
            /* Method returns Integer */

            Local0 = (Arg2 + M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 + M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0xFE7CB391D650A285)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 + DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0xFE7CB391D650A284)
                Local0 = (Arg2 + DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0xFE7CB391D650A285)
            }

            /* Conversion of the second operand */

            Store ((0x00 + Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0xFE7CB391D650A284)
            Store ((0x01 + Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0xFE7CB391D650A285)
            Store ((AUI5 + Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0xFE7CB391D650A284)
            Store ((AUI6 + Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0xFE7CB391D650A285)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) + Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0xFE7CB391D650A284)
                Store ((DerefOf (RefOf (AUI6)) + Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0xFE7CB391D650A285)
            }

            Store ((DerefOf (PAUI [0x05]) + Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0xFE7CB391D650A284)
            Store ((DerefOf (PAUI [0x06]) + Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0xFE7CB391D650A285)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) + Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0xFE7CB391D650A284)
            Store ((M601 (0x01, 0x06) + Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0xFE7CB391D650A285)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) + Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0xFE7CB391D650A284)
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) + Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0xFE7CB391D650A285)
            }

            Local0 = (0x00 + Arg2)
            M600 (Arg0, 0x24, Local0, 0xFE7CB391D650A284)
            Local0 = (0x01 + Arg2)
            M600 (Arg0, 0x25, Local0, 0xFE7CB391D650A285)
            Local0 = (AUI5 + Arg2)
            M600 (Arg0, 0x26, Local0, 0xFE7CB391D650A284)
            Local0 = (AUI6 + Arg2)
            M600 (Arg0, 0x27, Local0, 0xFE7CB391D650A285)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) + Arg2)
                M600 (Arg0, 0x28, Local0, 0xFE7CB391D650A284)
                Local0 = (DerefOf (RefOf (AUI6)) + Arg2)
                M600 (Arg0, 0x29, Local0, 0xFE7CB391D650A285)
            }

            Local0 = (DerefOf (PAUI [0x05]) + Arg2)
            M600 (Arg0, 0x2A, Local0, 0xFE7CB391D650A284)
            Local0 = (DerefOf (PAUI [0x06]) + Arg2)
            M600 (Arg0, 0x2B, Local0, 0xFE7CB391D650A285)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) + Arg2)
            M600 (Arg0, 0x2C, Local0, 0xFE7CB391D650A284)
            Local0 = (M601 (0x01, 0x06) + Arg2)
            M600 (Arg0, 0x2D, Local0, 0xFE7CB391D650A285)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) + Arg2)
                M600 (Arg0, 0x2E, Local0, 0xFE7CB391D650A284)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) + Arg2)
                M600 (Arg0, 0x2F, Local0, 0xFE7CB391D650A285)
            }

            /* Conversion of the both operands */

            Store ((Arg1 + Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0xFE7CB391D650A5A5)
            Store ((Arg2 + Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0xFE7CB391D650A5A5)
            Local0 = (Arg1 + Arg2)
            M600 (Arg0, 0x32, Local0, 0xFE7CB391D650A5A5)
            Local0 = (Arg2 + Arg1)
            M600 (Arg0, 0x33, Local0, 0xFE7CB391D650A5A5)
        }

        /* Add, 32-bit */

        Method (M03D, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 + 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0xD650A284)
            Store ((Arg2 + 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0xD650A285)
            Store ((Arg2 + AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0xD650A284)
            Store ((Arg2 + AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0xD650A285)
            If (Y078)
            {
                Store ((Arg2 + DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0xD650A284)
                Store ((Arg2 + DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0xD650A285)
            }

            Store ((Arg2 + DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0xD650A284)
            Store ((Arg2 + DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0xD650A285)
            /* Method returns Integer */

            Store ((Arg2 + M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0xD650A284)
            Store ((Arg2 + M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0xD650A285)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 + DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xD650A284)
                Store ((Arg2 + DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0xD650A285)
            }

            Local0 = (Arg2 + 0x00)
            M600 (Arg0, 0x0C, Local0, 0xD650A284)
            Local0 = (Arg2 + 0x01)
            M600 (Arg0, 0x0D, Local0, 0xD650A285)
            Local0 = (Arg2 + AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0xD650A284)
            Local0 = (Arg2 + AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0xD650A285)
            If (Y078)
            {
                Local0 = (Arg2 + DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0xD650A284)
                Local0 = (Arg2 + DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0xD650A285)
            }

            Local0 = (Arg2 + DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0xD650A284)
            Local0 = (Arg2 + DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0xD650A285)
            /* Method returns Integer */

            Local0 = (Arg2 + M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0xD650A284)
            Local0 = (Arg2 + M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0xD650A285)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 + DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0xD650A284)
                Local0 = (Arg2 + DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0xD650A285)
            }

            /* Conversion of the second operand */

            Store ((0x00 + Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0xD650A284)
            Store ((0x01 + Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0xD650A285)
            Store ((AUI5 + Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0xD650A284)
            Store ((AUI6 + Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0xD650A285)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) + Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0xD650A284)
                Store ((DerefOf (RefOf (AUI6)) + Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0xD650A285)
            }

            Store ((DerefOf (PAUI [0x05]) + Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0xD650A284)
            Store ((DerefOf (PAUI [0x06]) + Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0xD650A285)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) + Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0xD650A284)
            Store ((M601 (0x01, 0x06) + Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0xD650A285)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) + Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0xD650A284)
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) + Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0xD650A285)
            }

            Local0 = (0x00 + Arg2)
            M600 (Arg0, 0x24, Local0, 0xD650A284)
            Local0 = (0x01 + Arg2)
            M600 (Arg0, 0x25, Local0, 0xD650A285)
            Local0 = (AUI5 + Arg2)
            M600 (Arg0, 0x26, Local0, 0xD650A284)
            Local0 = (AUI6 + Arg2)
            M600 (Arg0, 0x27, Local0, 0xD650A285)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) + Arg2)
                M600 (Arg0, 0x28, Local0, 0xD650A284)
                Local0 = (DerefOf (RefOf (AUI6)) + Arg2)
                M600 (Arg0, 0x29, Local0, 0xD650A285)
            }

            Local0 = (DerefOf (PAUI [0x05]) + Arg2)
            M600 (Arg0, 0x2A, Local0, 0xD650A284)
            Local0 = (DerefOf (PAUI [0x06]) + Arg2)
            M600 (Arg0, 0x2B, Local0, 0xD650A285)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) + Arg2)
            M600 (Arg0, 0x2C, Local0, 0xD650A284)
            Local0 = (M601 (0x01, 0x06) + Arg2)
            M600 (Arg0, 0x2D, Local0, 0xD650A285)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) + Arg2)
                M600 (Arg0, 0x2E, Local0, 0xD650A284)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) + Arg2)
                M600 (Arg0, 0x2F, Local0, 0xD650A285)
            }

            /* Conversion of the both operands */

            Store ((Arg1 + Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0xD650A5A5)
            Store ((Arg2 + Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0xD650A5A5)
            Local0 = (Arg1 + Arg2)
            M600 (Arg0, 0x32, Local0, 0xD650A5A5)
            Local0 = (Arg2 + Arg1)
            M600 (Arg0, 0x33, Local0, 0xD650A5A5)
        }

        /* And, common 32-bit/64-bit test */

        Method (M03E, 2, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg1 & 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0x00)
            Store ((Arg1 & 0xFFFFFFFFFFFFFFFF), Local0)
            M600 (Arg0, 0x01, Local0, 0x0321)
            Store ((Arg1 & AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0x00)
            Store ((Arg1 & AUIJ), Local0)
            M600 (Arg0, 0x03, Local0, 0x0321)
            If (Y078)
            {
                Store ((Arg1 & DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0x00)
                Store ((Arg1 & DerefOf (RefOf (AUIJ))), Local0)
                M600 (Arg0, 0x05, Local0, 0x0321)
            }

            Store ((Arg1 & DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0x00)
            Store ((Arg1 & DerefOf (PAUI [0x13])), Local0)
            M600 (Arg0, 0x07, Local0, 0x0321)
            /* Method returns Integer */

            Store ((Arg1 & M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0x00)
            Store ((Arg1 & M601 (0x01, 0x13)), Local0)
            M600 (Arg0, 0x09, Local0, 0x0321)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg1 & DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0x00)
                Store ((Arg1 & DerefOf (M602 (0x01, 0x13, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x0321)
            }

            Local0 = (Arg1 & 0x00)
            M600 (Arg0, 0x0C, Local0, 0x00)
            Local0 = (Arg1 & 0xFFFFFFFFFFFFFFFF)
            M600 (Arg0, 0x0D, Local0, 0x0321)
            Local0 = (Arg1 & AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0x00)
            Local0 = (Arg1 & AUIJ) /* \AUIJ */
            M600 (Arg0, 0x0F, Local0, 0x0321)
            If (Y078)
            {
                Local0 = (Arg1 & DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0x00)
                Local0 = (Arg1 & DerefOf (RefOf (AUIJ)))
                M600 (Arg0, 0x11, Local0, 0x0321)
            }

            Local0 = (Arg1 & DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0x00)
            Local0 = (Arg1 & DerefOf (PAUI [0x13]))
            M600 (Arg0, 0x13, Local0, 0x0321)
            /* Method returns Integer */

            Local0 = (Arg1 & M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0x00)
            Local0 = (Arg1 & M601 (0x01, 0x13))
            M600 (Arg0, 0x15, Local0, 0x0321)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg1 & DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0x00)
                Local0 = (Arg1 & DerefOf (M602 (0x01, 0x13, 0x01)))
                M600 (Arg0, 0x17, Local0, 0x0321)
            }

            /* Conversion of the second operand */

            Store ((0x00 & Arg1), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0xFFFFFFFFFFFFFFFF & Arg1), Local0)
            M600 (Arg0, 0x19, Local0, 0x0321)
            Store ((AUI5 & Arg1), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUIJ & Arg1), Local0)
            M600 (Arg0, 0x1B, Local0, 0x0321)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) & Arg1), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUIJ)) & Arg1), Local0)
                M600 (Arg0, 0x1D, Local0, 0x0321)
            }

            Store ((DerefOf (PAUI [0x05]) & Arg1), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x13]) & Arg1), Local0)
            M600 (Arg0, 0x1F, Local0, 0x0321)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) & Arg1), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x13) & Arg1), Local0)
            M600 (Arg0, 0x21, Local0, 0x0321)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) & Arg1), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x13, 0x01)) & Arg1), Local0)
                M600 (Arg0, 0x23, Local0, 0x0321)
            }

            Local0 = (0x00 & Arg1)
            M600 (Arg0, 0x24, Local0, 0x00)
            Local0 = (0xFFFFFFFFFFFFFFFF & Arg1)
            M600 (Arg0, 0x25, Local0, 0x0321)
            Local0 = (AUI5 & Arg1)
            M600 (Arg0, 0x26, Local0, 0x00)
            Local0 = (AUIJ & Arg1)
            M600 (Arg0, 0x27, Local0, 0x0321)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) & Arg1)
                M600 (Arg0, 0x28, Local0, 0x00)
                Local0 = (DerefOf (RefOf (AUIJ)) & Arg1)
                M600 (Arg0, 0x29, Local0, 0x0321)
            }

            Local0 = (DerefOf (PAUI [0x05]) & Arg1)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Local0 = (DerefOf (PAUI [0x13]) & Arg1)
            M600 (Arg0, 0x2B, Local0, 0x0321)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) & Arg1)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Local0 = (M601 (0x01, 0x13) & Arg1)
            M600 (Arg0, 0x2D, Local0, 0x0321)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) & Arg1)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Local0 = (DerefOf (M602 (0x01, 0x13, 0x01)) & Arg1)
                M600 (Arg0, 0x2F, Local0, 0x0321)
            }
        }

        /* And, 64-bit */

        Method (M03F, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 & 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0x00)
            Store ((Arg2 & 0xFFFFFFFFFFFFFFFF), Local0)
            M600 (Arg0, 0x01, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 & AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0x00)
            Store ((Arg2 & AUIJ), Local0)
            M600 (Arg0, 0x03, Local0, 0xFE7CB391D650A284)
            If (Y078)
            {
                Store ((Arg2 & DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0x00)
                Store ((Arg2 & DerefOf (RefOf (AUIJ))), Local0)
                M600 (Arg0, 0x05, Local0, 0xFE7CB391D650A284)
            }

            Store ((Arg2 & DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0x00)
            Store ((Arg2 & DerefOf (PAUI [0x13])), Local0)
            M600 (Arg0, 0x07, Local0, 0xFE7CB391D650A284)
            /* Method returns Integer */

            Store ((Arg2 & M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0x00)
            Store ((Arg2 & M601 (0x01, 0x13)), Local0)
            M600 (Arg0, 0x09, Local0, 0xFE7CB391D650A284)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 & DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0x00)
                Store ((Arg2 & DerefOf (M602 (0x01, 0x13, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0xFE7CB391D650A284)
            }

            Local0 = (Arg2 & 0x00)
            M600 (Arg0, 0x0C, Local0, 0x00)
            Local0 = (Arg2 & 0xFFFFFFFFFFFFFFFF)
            M600 (Arg0, 0x0D, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 & AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0x00)
            Local0 = (Arg2 & AUIJ) /* \AUIJ */
            M600 (Arg0, 0x0F, Local0, 0xFE7CB391D650A284)
            If (Y078)
            {
                Local0 = (Arg2 & DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0x00)
                Local0 = (Arg2 & DerefOf (RefOf (AUIJ)))
                M600 (Arg0, 0x11, Local0, 0xFE7CB391D650A284)
            }

            Local0 = (Arg2 & DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0x00)
            Local0 = (Arg2 & DerefOf (PAUI [0x13]))
            M600 (Arg0, 0x13, Local0, 0xFE7CB391D650A284)
            /* Method returns Integer */

            Local0 = (Arg2 & M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0x00)
            Local0 = (Arg2 & M601 (0x01, 0x13))
            M600 (Arg0, 0x15, Local0, 0xFE7CB391D650A284)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 & DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0x00)
                Local0 = (Arg2 & DerefOf (M602 (0x01, 0x13, 0x01)))
                M600 (Arg0, 0x17, Local0, 0xFE7CB391D650A284)
            }

            /* Conversion of the second operand */

            Store ((0x00 & Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0xFFFFFFFFFFFFFFFF & Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0xFE7CB391D650A284)
            Store ((AUI5 & Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUIJ & Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0xFE7CB391D650A284)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) & Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUIJ)) & Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0xFE7CB391D650A284)
            }

            Store ((DerefOf (PAUI [0x05]) & Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x13]) & Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0xFE7CB391D650A284)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) & Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x13) & Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0xFE7CB391D650A284)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) & Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x13, 0x01)) & Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0xFE7CB391D650A284)
            }

            Local0 = (0x00 & Arg2)
            M600 (Arg0, 0x24, Local0, 0x00)
            Local0 = (0xFFFFFFFFFFFFFFFF & Arg2)
            M600 (Arg0, 0x25, Local0, 0xFE7CB391D650A284)
            Local0 = (AUI5 & Arg2)
            M600 (Arg0, 0x26, Local0, 0x00)
            Local0 = (AUIJ & Arg2)
            M600 (Arg0, 0x27, Local0, 0xFE7CB391D650A284)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) & Arg2)
                M600 (Arg0, 0x28, Local0, 0x00)
                Local0 = (DerefOf (RefOf (AUIJ)) & Arg2)
                M600 (Arg0, 0x29, Local0, 0xFE7CB391D650A284)
            }

            Local0 = (DerefOf (PAUI [0x05]) & Arg2)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Local0 = (DerefOf (PAUI [0x13]) & Arg2)
            M600 (Arg0, 0x2B, Local0, 0xFE7CB391D650A284)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) & Arg2)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Local0 = (M601 (0x01, 0x13) & Arg2)
            M600 (Arg0, 0x2D, Local0, 0xFE7CB391D650A284)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) & Arg2)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Local0 = (DerefOf (M602 (0x01, 0x13, 0x01)) & Arg2)
                M600 (Arg0, 0x2F, Local0, 0xFE7CB391D650A284)
            }

            /* Conversion of the both operands */

            Store ((Arg1 & Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0x0200)
            Store ((Arg2 & Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0x0200)
            Local0 = (Arg1 & Arg2)
            M600 (Arg0, 0x32, Local0, 0x0200)
            Local0 = (Arg2 & Arg1)
            M600 (Arg0, 0x33, Local0, 0x0200)
        }

        /* And, 32-bit */

        Method (M040, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 & 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0x00)
            Store ((Arg2 & 0xFFFFFFFF), Local0)
            M600 (Arg0, 0x01, Local0, 0xD650A284)
            Store ((Arg2 & AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0x00)
            Store ((Arg2 & AUII), Local0)
            M600 (Arg0, 0x03, Local0, 0xD650A284)
            If (Y078)
            {
                Store ((Arg2 & DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0x00)
                Store ((Arg2 & DerefOf (RefOf (AUII))), Local0)
                M600 (Arg0, 0x05, Local0, 0xD650A284)
            }

            Store ((Arg2 & DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0x00)
            Store ((Arg2 & DerefOf (PAUI [0x12])), Local0)
            M600 (Arg0, 0x07, Local0, 0xD650A284)
            /* Method returns Integer */

            Store ((Arg2 & M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0x00)
            Store ((Arg2 & M601 (0x01, 0x12)), Local0)
            M600 (Arg0, 0x09, Local0, 0xD650A284)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 & DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0x00)
                Store ((Arg2 & DerefOf (M602 (0x01, 0x12, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0xD650A284)
            }

            Local0 = (Arg2 & 0x00)
            M600 (Arg0, 0x0C, Local0, 0x00)
            Local0 = (Arg2 & 0xFFFFFFFF)
            M600 (Arg0, 0x0D, Local0, 0xD650A284)
            Local0 = (Arg2 & AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0x00)
            Local0 = (Arg2 & AUII) /* \AUII */
            M600 (Arg0, 0x0F, Local0, 0xD650A284)
            If (Y078)
            {
                Local0 = (Arg2 & DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0x00)
                Local0 = (Arg2 & DerefOf (RefOf (AUII)))
                M600 (Arg0, 0x11, Local0, 0xD650A284)
            }

            Local0 = (Arg2 & DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0x00)
            Local0 = (Arg2 & DerefOf (PAUI [0x12]))
            M600 (Arg0, 0x13, Local0, 0xD650A284)
            /* Method returns Integer */

            Local0 = (Arg2 & M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0x00)
            Local0 = (Arg2 & M601 (0x01, 0x12))
            M600 (Arg0, 0x15, Local0, 0xD650A284)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 & DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0x00)
                Local0 = (Arg2 & DerefOf (M602 (0x01, 0x12, 0x01)))
                M600 (Arg0, 0x17, Local0, 0xD650A284)
            }

            /* Conversion of the second operand */

            Store ((0x00 & Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0xFFFFFFFF & Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0xD650A284)
            Store ((AUI5 & Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUII & Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0xD650A284)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) & Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUII)) & Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0xD650A284)
            }

            Store ((DerefOf (PAUI [0x05]) & Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x12]) & Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0xD650A284)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) & Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x12) & Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0xD650A284)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) & Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x12, 0x01)) & Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0xD650A284)
            }

            Local0 = (0x00 & Arg2)
            M600 (Arg0, 0x24, Local0, 0x00)
            Local0 = (0xFFFFFFFF & Arg2)
            M600 (Arg0, 0x25, Local0, 0xD650A284)
            Local0 = (AUI5 & Arg2)
            M600 (Arg0, 0x26, Local0, 0x00)
            Local0 = (AUII & Arg2)
            M600 (Arg0, 0x27, Local0, 0xD650A284)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) & Arg2)
                M600 (Arg0, 0x28, Local0, 0x00)
                Local0 = (DerefOf (RefOf (AUII)) & Arg2)
                M600 (Arg0, 0x29, Local0, 0xD650A284)
            }

            Local0 = (DerefOf (PAUI [0x05]) & Arg2)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Local0 = (DerefOf (PAUI [0x12]) & Arg2)
            M600 (Arg0, 0x2B, Local0, 0xD650A284)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) & Arg2)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Local0 = (M601 (0x01, 0x12) & Arg2)
            M600 (Arg0, 0x2D, Local0, 0xD650A284)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) & Arg2)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Local0 = (DerefOf (M602 (0x01, 0x12, 0x01)) & Arg2)
                M600 (Arg0, 0x2F, Local0, 0xD650A284)
            }

            /* Conversion of the both operands */

            Store ((Arg1 & Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0x0200)
            Store ((Arg2 & Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0x0200)
            Local0 = (Arg1 & Arg2)
            M600 (Arg0, 0x32, Local0, 0x0200)
            Local0 = (Arg2 & Arg1)
            M600 (Arg0, 0x33, Local0, 0x0200)
        }

        /* Divide, common 32-bit/64-bit test */

        Method (M041, 2, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg1 / 0x01), Local0)
            M600 (Arg0, 0x00, Local0, 0x0321)
            Store ((Arg1 / 0x0321), Local0)
            M600 (Arg0, 0x01, Local0, 0x01)
            Store ((Arg1 / AUI6), Local0)
            M600 (Arg0, 0x02, Local0, 0x0321)
            Store ((Arg1 / AUI1), Local0)
            M600 (Arg0, 0x03, Local0, 0x01)
            If (Y078)
            {
                Store ((Arg1 / DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x04, Local0, 0x0321)
                Store ((Arg1 / DerefOf (RefOf (AUI1))), Local0)
                M600 (Arg0, 0x05, Local0, 0x01)
            }

            Store ((Arg1 / DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x06, Local0, 0x0321)
            Store ((Arg1 / DerefOf (PAUI [0x01])), Local0)
            M600 (Arg0, 0x07, Local0, 0x01)
            /* Method returns Integer */

            Store ((Arg1 / M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x08, Local0, 0x0321)
            Store ((Arg1 / M601 (0x01, 0x01)), Local0)
            M600 (Arg0, 0x09, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg1 / DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0x0321)
                Store ((Arg1 / DerefOf (M602 (0x01, 0x01, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x01)
            }

            Divide (Arg1, 0x01, Local1, Local0)
            M600 (Arg0, 0x0C, Local0, 0x0321)
            Divide (Arg1, 0x0321, Local1, Local0)
            M600 (Arg0, 0x0D, Local0, 0x01)
            Divide (Arg1, AUI6, Local1, Local0)
            M600 (Arg0, 0x0E, Local0, 0x0321)
            Divide (Arg1, AUI1, Local1, Local0)
            M600 (Arg0, 0x0F, Local0, 0x01)
            If (Y078)
            {
                Divide (Arg1, DerefOf (RefOf (AUI6)), Local1, Local0)
                M600 (Arg0, 0x10, Local0, 0x0321)
                Divide (Arg1, DerefOf (RefOf (AUI1)), Local1, Local0)
                M600 (Arg0, 0x11, Local0, 0x01)
            }

            Divide (Arg1, DerefOf (PAUI [0x06]), Local1, Local0)
            M600 (Arg0, 0x12, Local0, 0x0321)
            Divide (Arg1, DerefOf (PAUI [0x01]), Local1, Local0)
            M600 (Arg0, 0x13, Local0, 0x01)
            /* Method returns Integer */

            Divide (Arg1, M601 (0x01, 0x06), Local1, Local0)
            M600 (Arg0, 0x14, Local0, 0x0321)
            Divide (Arg1, M601 (0x01, 0x01), Local1, Local0)
            M600 (Arg0, 0x15, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Divide (Arg1, DerefOf (M602 (0x01, 0x06, 0x01)), Local1, Local0)
                M600 (Arg0, 0x16, Local0, 0x0321)
                Divide (Arg1, DerefOf (M602 (0x01, 0x01, 0x01)), Local1, Local0)
                M600 (Arg0, 0x17, Local0, 0x01)
            }

            /* Conversion of the second operand */

            Store ((0x01 / Arg1), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0x0321 / Arg1), Local0)
            M600 (Arg0, 0x19, Local0, 0x01)
            Store ((AUI6 / Arg1), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUI1 / Arg1), Local0)
            M600 (Arg0, 0x1B, Local0, 0x01)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI6)) / Arg1), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUI1)) / Arg1), Local0)
                M600 (Arg0, 0x1D, Local0, 0x01)
            }

            Store ((DerefOf (PAUI [0x06]) / Arg1), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x01]) / Arg1), Local0)
            M600 (Arg0, 0x1F, Local0, 0x01)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x06) / Arg1), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x01) / Arg1), Local0)
            M600 (Arg0, 0x21, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) / Arg1), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x01, 0x01)) / Arg1), Local0)
                M600 (Arg0, 0x23, Local0, 0x01)
            }

            Divide (0x01, Arg1, Local1, Local0)
            M600 (Arg0, 0x24, Local0, 0x00)
            Divide (0x0321, Arg1, Local1, Local0)
            M600 (Arg0, 0x25, Local0, 0x01)
            Divide (AUI6, Arg1, Local1, Local0)
            M600 (Arg0, 0x26, Local0, 0x00)
            Divide (AUI1, Arg1, Local1, Local0)
            M600 (Arg0, 0x27, Local0, 0x01)
            If (Y078)
            {
                Divide (DerefOf (RefOf (AUI6)), Arg1, Local1, Local0)
                M600 (Arg0, 0x28, Local0, 0x00)
                Divide (DerefOf (RefOf (AUI1)), Arg1, Local1, Local0)
                M600 (Arg0, 0x29, Local0, 0x01)
            }

            Divide (DerefOf (PAUI [0x06]), Arg1, Local1, Local0)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Divide (DerefOf (PAUI [0x01]), Arg1, Local1, Local0)
            M600 (Arg0, 0x2B, Local0, 0x01)
            /* Method returns Integer */

            Divide (M601 (0x01, 0x06), Arg1, Local1, Local0)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Divide (M601 (0x01, 0x01), Arg1, Local1, Local0)
            M600 (Arg0, 0x2D, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Divide (DerefOf (M602 (0x01, 0x06, 0x01)), Arg1, Local1, Local0)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Divide (DerefOf (M602 (0x01, 0x01, 0x01)), Arg1, Local1, Local0)
                M600 (Arg0, 0x2F, Local0, 0x01)
            }
        }

        /* Divide, 64-bit */

        Method (M042, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 / 0x01), Local0)
            M600 (Arg0, 0x00, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 / 0xFE7CB391D650A284), Local0)
            M600 (Arg0, 0x01, Local0, 0x01)
            Store ((Arg2 / AUI6), Local0)
            M600 (Arg0, 0x02, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 / AUI4), Local0)
            M600 (Arg0, 0x03, Local0, 0x01)
            If (Y078)
            {
                Store ((Arg2 / DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x04, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 / DerefOf (RefOf (AUI4))), Local0)
                M600 (Arg0, 0x05, Local0, 0x01)
            }

            Store ((Arg2 / DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x06, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 / DerefOf (PAUI [0x04])), Local0)
            M600 (Arg0, 0x07, Local0, 0x01)
            /* Method returns Integer */

            Store ((Arg2 / M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x08, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 / M601 (0x01, 0x04)), Local0)
            M600 (Arg0, 0x09, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 / DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 / DerefOf (M602 (0x01, 0x04, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x01)
            }

            Divide (Arg2, 0x01, Local1, Local0)
            M600 (Arg0, 0x0C, Local0, 0xFE7CB391D650A284)
            Divide (Arg2, 0xFE7CB391D650A284, Local1, Local0)
            M600 (Arg0, 0x0D, Local0, 0x01)
            Divide (Arg2, AUI6, Local1, Local0)
            M600 (Arg0, 0x0E, Local0, 0xFE7CB391D650A284)
            Divide (Arg2, AUI4, Local1, Local0)
            M600 (Arg0, 0x0F, Local0, 0x01)
            If (Y078)
            {
                Divide (Arg2, DerefOf (RefOf (AUI6)), Local1, Local0)
                M600 (Arg0, 0x10, Local0, 0xFE7CB391D650A284)
                Divide (Arg2, DerefOf (RefOf (AUI4)), Local1, Local0)
                M600 (Arg0, 0x11, Local0, 0x01)
            }

            Divide (Arg2, DerefOf (PAUI [0x06]), Local1, Local0)
            M600 (Arg0, 0x12, Local0, 0xFE7CB391D650A284)
            Divide (Arg2, DerefOf (PAUI [0x04]), Local1, Local0)
            M600 (Arg0, 0x13, Local0, 0x01)
            /* Method returns Integer */

            Divide (Arg2, M601 (0x01, 0x06), Local1, Local0)
            M600 (Arg0, 0x14, Local0, 0xFE7CB391D650A284)
            Divide (Arg2, M601 (0x01, 0x04), Local1, Local0)
            M600 (Arg0, 0x15, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Divide (Arg2, DerefOf (M602 (0x01, 0x06, 0x01)), Local1, Local0)
                M600 (Arg0, 0x16, Local0, 0xFE7CB391D650A284)
                Divide (Arg2, DerefOf (M602 (0x01, 0x04, 0x01)), Local1, Local0)
                M600 (Arg0, 0x17, Local0, 0x01)
            }

            /* Conversion of the second operand */

            Store ((0x01 / Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0xFE7CB391D650A284 / Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0x01)
            Store ((AUI6 / Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUI4 / Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0x01)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI6)) / Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUI4)) / Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0x01)
            }

            Store ((DerefOf (PAUI [0x06]) / Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x04]) / Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0x01)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x06) / Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x04) / Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) / Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x04, 0x01)) / Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0x01)
            }

            Divide (0x01, Arg2, Local1, Local0)
            M600 (Arg0, 0x24, Local0, 0x00)
            Divide (0xFE7CB391D650A284, Arg2, Local1, Local0)
            M600 (Arg0, 0x25, Local0, 0x01)
            Divide (AUI6, Arg2, Local1, Local0)
            M600 (Arg0, 0x26, Local0, 0x00)
            Divide (AUI4, Arg2, Local1, Local0)
            M600 (Arg0, 0x27, Local0, 0x01)
            If (Y078)
            {
                Divide (DerefOf (RefOf (AUI6)), Arg2, Local1, Local0)
                M600 (Arg0, 0x28, Local0, 0x00)
                Divide (DerefOf (RefOf (AUI4)), Arg2, Local1, Local0)
                M600 (Arg0, 0x29, Local0, 0x01)
            }

            Divide (DerefOf (PAUI [0x06]), Arg2, Local1, Local0)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Divide (DerefOf (PAUI [0x04]), Arg2, Local1, Local0)
            M600 (Arg0, 0x2B, Local0, 0x01)
            /* Method returns Integer */

            Divide (M601 (0x01, 0x06), Arg2, Local1, Local0)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Divide (M601 (0x01, 0x04), Arg2, Local1, Local0)
            M600 (Arg0, 0x2D, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Divide (DerefOf (M602 (0x01, 0x06, 0x01)), Arg2, Local1, Local0)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Divide (DerefOf (M602 (0x01, 0x04, 0x01)), Arg2, Local1, Local0)
                M600 (Arg0, 0x2F, Local0, 0x01)
            }

            /* Conversion of the both operands */

            Store ((Arg1 / Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0x00)
            Store ((Arg2 / Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0x0051558EB950F5A7)
            Divide (Arg1, Arg2, Local1, Local0)
            M600 (Arg0, 0x32, Local0, 0x00)
            Divide (Arg2, Arg1, Local1, Local0)
            M600 (Arg0, 0x33, Local0, 0x0051558EB950F5A7)
        }

        /* Divide, 32-bit */

        Method (M043, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 / 0x01), Local0)
            M600 (Arg0, 0x00, Local0, 0xD650A284)
            Store ((Arg2 / 0xD650A284), Local0)
            M600 (Arg0, 0x01, Local0, 0x01)
            Store ((Arg2 / AUI6), Local0)
            M600 (Arg0, 0x02, Local0, 0xD650A284)
            Store ((Arg2 / AUIK), Local0)
            M600 (Arg0, 0x03, Local0, 0x01)
            If (Y078)
            {
                Store ((Arg2 / DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x04, Local0, 0xD650A284)
                Store ((Arg2 / DerefOf (RefOf (AUIK))), Local0)
                M600 (Arg0, 0x05, Local0, 0x01)
            }

            Store ((Arg2 / DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x06, Local0, 0xD650A284)
            Store ((Arg2 / DerefOf (PAUI [0x14])), Local0)
            M600 (Arg0, 0x07, Local0, 0x01)
            /* Method returns Integer */

            Store ((Arg2 / M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x08, Local0, 0xD650A284)
            Store ((Arg2 / M601 (0x01, 0x14)), Local0)
            M600 (Arg0, 0x09, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 / DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xD650A284)
                Store ((Arg2 / DerefOf (M602 (0x01, 0x14, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x01)
            }

            Divide (Arg2, 0x01, Local1, Local0)
            M600 (Arg0, 0x0C, Local0, 0xD650A284)
            Divide (Arg2, 0xD650A284, Local1, Local0)
            M600 (Arg0, 0x0D, Local0, 0x01)
            Divide (Arg2, AUI6, Local1, Local0)
            M600 (Arg0, 0x0E, Local0, 0xD650A284)
            Divide (Arg2, AUIK, Local1, Local0)
            M600 (Arg0, 0x0F, Local0, 0x01)
            If (Y078)
            {
                Divide (Arg2, DerefOf (RefOf (AUI6)), Local1, Local0)
                M600 (Arg0, 0x10, Local0, 0xD650A284)
                Divide (Arg2, DerefOf (RefOf (AUIK)), Local1, Local0)
                M600 (Arg0, 0x11, Local0, 0x01)
            }

            Divide (Arg2, DerefOf (PAUI [0x06]), Local1, Local0)
            M600 (Arg0, 0x12, Local0, 0xD650A284)
            Divide (Arg2, DerefOf (PAUI [0x14]), Local1, Local0)
            M600 (Arg0, 0x13, Local0, 0x01)
            /* Method returns Integer */

            Divide (Arg2, M601 (0x01, 0x06), Local1, Local0)
            M600 (Arg0, 0x14, Local0, 0xD650A284)
            Divide (Arg2, M601 (0x01, 0x14), Local1, Local0)
            M600 (Arg0, 0x15, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Divide (Arg2, DerefOf (M602 (0x01, 0x06, 0x01)), Local1, Local0)
                M600 (Arg0, 0x16, Local0, 0xD650A284)
                Divide (Arg2, DerefOf (M602 (0x01, 0x14, 0x01)), Local1, Local0)
                M600 (Arg0, 0x17, Local0, 0x01)
            }

            /* Conversion of the second operand */

            Store ((0x01 / Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0xD650A284 / Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0x01)
            Store ((AUI6 / Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUIK / Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0x01)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI6)) / Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUIK)) / Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0x01)
            }

            Store ((DerefOf (PAUI [0x06]) / Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x14]) / Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0x01)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x06) / Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x14) / Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) / Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x14, 0x01)) / Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0x01)
            }

            Divide (0x01, Arg2, Local1, Local0)
            M600 (Arg0, 0x24, Local0, 0x00)
            Divide (0xD650A284, Arg2, Local1, Local0)
            M600 (Arg0, 0x25, Local0, 0x01)
            Divide (AUI6, Arg2, Local1, Local0)
            M600 (Arg0, 0x26, Local0, 0x00)
            Divide (AUIK, Arg2, Local1, Local0)
            M600 (Arg0, 0x27, Local0, 0x01)
            If (Y078)
            {
                Divide (DerefOf (RefOf (AUI6)), Arg2, Local1, Local0)
                M600 (Arg0, 0x28, Local0, 0x00)
                Divide (DerefOf (RefOf (AUIK)), Arg2, Local1, Local0)
                M600 (Arg0, 0x29, Local0, 0x01)
            }

            Divide (DerefOf (PAUI [0x06]), Arg2, Local1, Local0)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Divide (DerefOf (PAUI [0x14]), Arg2, Local1, Local0)
            M600 (Arg0, 0x2B, Local0, 0x01)
            /* Method returns Integer */

            Divide (M601 (0x01, 0x06), Arg2, Local1, Local0)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Divide (M601 (0x01, 0x14), Arg2, Local1, Local0)
            M600 (Arg0, 0x2D, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Divide (DerefOf (M602 (0x01, 0x06, 0x01)), Arg2, Local1, Local0)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Divide (DerefOf (M602 (0x01, 0x14, 0x01)), Arg2, Local1, Local0)
                M600 (Arg0, 0x2F, Local0, 0x01)
            }

            /* Conversion of the both operands */

            Store ((Arg1 / Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0x00)
            Store ((Arg2 / Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0x00447EC3)
            Divide (Arg1, Arg2, Local1, Local0)
            M600 (Arg0, 0x32, Local0, 0x00)
            Divide (Arg2, Arg1, Local1, Local0)
            M600 (Arg0, 0x33, Local0, 0x00447EC3)
        }

        /* Mod, common 32-bit/64-bit test */

        Method (M044, 2, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg1 % 0x0322), Local0)
            M600 (Arg0, 0x00, Local0, 0x0321)
            Store ((Arg1 % 0x0320), Local0)
            M600 (Arg0, 0x01, Local0, 0x01)
            Store ((Arg1 % AUIG), Local0)
            M600 (Arg0, 0x02, Local0, 0x0321)
            Store ((Arg1 % AUIH), Local0)
            M600 (Arg0, 0x03, Local0, 0x01)
            If (Y078)
            {
                Store ((Arg1 % DerefOf (RefOf (AUIG))), Local0)
                M600 (Arg0, 0x04, Local0, 0x0321)
                Store ((Arg1 % DerefOf (RefOf (AUIH))), Local0)
                M600 (Arg0, 0x05, Local0, 0x01)
            }

            Store ((Arg1 % DerefOf (PAUI [0x10])), Local0)
            M600 (Arg0, 0x06, Local0, 0x0321)
            Store ((Arg1 % DerefOf (PAUI [0x11])), Local0)
            M600 (Arg0, 0x07, Local0, 0x01)
            /* Method returns Integer */

            Store ((Arg1 % M601 (0x01, 0x10)), Local0)
            M600 (Arg0, 0x08, Local0, 0x0321)
            Store ((Arg1 % M601 (0x01, 0x11)), Local0)
            M600 (Arg0, 0x09, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg1 % DerefOf (M602 (0x01, 0x10, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0x0321)
                Store ((Arg1 % DerefOf (M602 (0x01, 0x11, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x01)
            }

            Local0 = (Arg1 % 0x0322)
            M600 (Arg0, 0x0C, Local0, 0x0321)
            Local0 = (Arg1 % 0x0320)
            M600 (Arg0, 0x0D, Local0, 0x01)
            Local0 = (Arg1 % AUIG) /* \AUIG */
            M600 (Arg0, 0x0E, Local0, 0x0321)
            Local0 = (Arg1 % AUIH) /* \AUIH */
            M600 (Arg0, 0x0F, Local0, 0x01)
            If (Y078)
            {
                Local0 = (Arg1 % DerefOf (RefOf (AUIG)))
                M600 (Arg0, 0x10, Local0, 0x0321)
                Local0 = (Arg1 % DerefOf (RefOf (AUIH)))
                M600 (Arg0, 0x11, Local0, 0x01)
            }

            Local0 = (Arg1 % DerefOf (PAUI [0x10]))
            M600 (Arg0, 0x12, Local0, 0x0321)
            Local0 = (Arg1 % DerefOf (PAUI [0x11]))
            M600 (Arg0, 0x13, Local0, 0x01)
            /* Method returns Integer */

            Local0 = (Arg1 % M601 (0x01, 0x10))
            M600 (Arg0, 0x14, Local0, 0x0321)
            Local0 = (Arg1 % M601 (0x01, 0x11))
            M600 (Arg0, 0x15, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg1 % DerefOf (M602 (0x01, 0x10, 0x01)))
                M600 (Arg0, 0x16, Local0, 0x0321)
                Local0 = (Arg1 % DerefOf (M602 (0x01, 0x11, 0x01)))
                M600 (Arg0, 0x17, Local0, 0x01)
            }

            /* Conversion of the second operand */

            Store ((0x0322 % Arg1), Local0)
            M600 (Arg0, 0x18, Local0, 0x01)
            Store ((0x0320 % Arg1), Local0)
            M600 (Arg0, 0x19, Local0, 0x0320)
            Store ((AUIG % Arg1), Local0)
            M600 (Arg0, 0x1A, Local0, 0x01)
            Store ((AUIH % Arg1), Local0)
            M600 (Arg0, 0x1B, Local0, 0x0320)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUIG)) % Arg1), Local0)
                M600 (Arg0, 0x1C, Local0, 0x01)
                Store ((DerefOf (RefOf (AUIH)) % Arg1), Local0)
                M600 (Arg0, 0x1D, Local0, 0x0320)
            }

            Store ((DerefOf (PAUI [0x10]) % Arg1), Local0)
            M600 (Arg0, 0x1E, Local0, 0x01)
            Store ((DerefOf (PAUI [0x11]) % Arg1), Local0)
            M600 (Arg0, 0x1F, Local0, 0x0320)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x10) % Arg1), Local0)
            M600 (Arg0, 0x20, Local0, 0x01)
            Store ((M601 (0x01, 0x11) % Arg1), Local0)
            M600 (Arg0, 0x21, Local0, 0x0320)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x10, 0x01)) % Arg1), Local0)
                M600 (Arg0, 0x22, Local0, 0x01)
                Store ((DerefOf (M602 (0x01, 0x11, 0x01)) % Arg1), Local0)
                M600 (Arg0, 0x23, Local0, 0x0320)
            }

            Local0 = (0x0322 % Arg1)
            M600 (Arg0, 0x24, Local0, 0x01)
            Local0 = (0x0320 % Arg1)
            M600 (Arg0, 0x25, Local0, 0x0320)
            Local0 = (AUIG % Arg1)
            M600 (Arg0, 0x26, Local0, 0x01)
            Local0 = (AUIH % Arg1)
            M600 (Arg0, 0x27, Local0, 0x0320)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUIG)) % Arg1)
                M600 (Arg0, 0x28, Local0, 0x01)
                Local0 = (DerefOf (RefOf (AUIH)) % Arg1)
                M600 (Arg0, 0x29, Local0, 0x0320)
            }

            Local0 = (DerefOf (PAUI [0x10]) % Arg1)
            M600 (Arg0, 0x2A, Local0, 0x01)
            Local0 = (DerefOf (PAUI [0x11]) % Arg1)
            M600 (Arg0, 0x2B, Local0, 0x0320)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x10) % Arg1)
            M600 (Arg0, 0x2C, Local0, 0x01)
            Local0 = (M601 (0x01, 0x11) % Arg1)
            M600 (Arg0, 0x2D, Local0, 0x0320)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x10, 0x01)) % Arg1)
                M600 (Arg0, 0x2E, Local0, 0x01)
                Local0 = (DerefOf (M602 (0x01, 0x11, 0x01)) % Arg1)
                M600 (Arg0, 0x2F, Local0, 0x0320)
            }
        }

        /* Mod, 64-bit */

        Method (M045, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 % 0xFE7CB391D650A285), Local0)
            M600 (Arg0, 0x00, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 % 0xFE7CB391D650A283), Local0)
            M600 (Arg0, 0x01, Local0, 0x01)
            Store ((Arg2 % AUID), Local0)
            M600 (Arg0, 0x02, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 % AUIF), Local0)
            M600 (Arg0, 0x03, Local0, 0x01)
            If (Y078)
            {
                Store ((Arg2 % DerefOf (RefOf (AUID))), Local0)
                M600 (Arg0, 0x04, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 % DerefOf (RefOf (AUIF))), Local0)
                M600 (Arg0, 0x05, Local0, 0x01)
            }

            Store ((Arg2 % DerefOf (PAUI [0x0D])), Local0)
            M600 (Arg0, 0x0D, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 % DerefOf (PAUI [0x0F])), Local0)
            M600 (Arg0, 0x07, Local0, 0x01)
            /* Method returns Integer */

            Store ((Arg2 % M601 (0x01, 0x0D)), Local0)
            M600 (Arg0, 0x08, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 % M601 (0x01, 0x0F)), Local0)
            M600 (Arg0, 0x09, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 % DerefOf (M602 (0x01, 0x0D, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 % DerefOf (M602 (0x01, 0x0F, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x01)
            }

            Local0 = (Arg2 % 0xFE7CB391D650A285)
            M600 (Arg0, 0x0C, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 % 0xFE7CB391D650A283)
            M600 (Arg0, 0x0D, Local0, 0x01)
            Local0 = (Arg2 % AUID) /* \AUID */
            M600 (Arg0, 0x0E, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 % AUIF) /* \AUIF */
            M600 (Arg0, 0x0F, Local0, 0x01)
            If (Y078)
            {
                Local0 = (Arg2 % DerefOf (RefOf (AUID)))
                M600 (Arg0, 0x10, Local0, 0xFE7CB391D650A284)
                Local0 = (Arg2 % DerefOf (RefOf (AUIF)))
                M600 (Arg0, 0x11, Local0, 0x01)
            }

            Local0 = (Arg2 % DerefOf (PAUI [0x0D]))
            M600 (Arg0, 0x12, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 % DerefOf (PAUI [0x0F]))
            M600 (Arg0, 0x13, Local0, 0x01)
            /* Method returns Integer */

            Local0 = (Arg2 % M601 (0x01, 0x0D))
            M600 (Arg0, 0x14, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 % M601 (0x01, 0x0F))
            M600 (Arg0, 0x15, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 % DerefOf (M602 (0x01, 0x0D, 0x01)))
                M600 (Arg0, 0x16, Local0, 0xFE7CB391D650A284)
                Local0 = (Arg2 % DerefOf (M602 (0x01, 0x0F, 0x01)))
                M600 (Arg0, 0x17, Local0, 0x01)
            }

            /* Conversion of the second operand */

            Store ((0xFE7CB391D650A285 % Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0x01)
            Store ((0xFE7CB391D650A283 % Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0xFE7CB391D650A283)
            Store ((AUID % Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0x01)
            Store ((AUIF % Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0xFE7CB391D650A283)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUID)) % Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0x01)
                Store ((DerefOf (RefOf (AUIF)) % Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0xFE7CB391D650A283)
            }

            Store ((DerefOf (PAUI [0x0D]) % Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0x01)
            Store ((DerefOf (PAUI [0x0F]) % Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0xFE7CB391D650A283)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x0D) % Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0x01)
            Store ((M601 (0x01, 0x0F) % Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0xFE7CB391D650A283)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x0D, 0x01)) % Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0x01)
                Store ((DerefOf (M602 (0x01, 0x0F, 0x01)) % Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0xFE7CB391D650A283)
            }

            Local0 = (0xFE7CB391D650A285 % Arg2)
            M600 (Arg0, 0x24, Local0, 0x01)
            Local0 = (0xFE7CB391D650A283 % Arg2)
            M600 (Arg0, 0x25, Local0, 0xFE7CB391D650A283)
            Local0 = (AUID % Arg2)
            M600 (Arg0, 0x26, Local0, 0x01)
            Local0 = (AUIF % Arg2)
            M600 (Arg0, 0x27, Local0, 0xFE7CB391D650A283)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUID)) % Arg2)
                M600 (Arg0, 0x28, Local0, 0x01)
                Local0 = (DerefOf (RefOf (AUIF)) % Arg2)
                M600 (Arg0, 0x29, Local0, 0xFE7CB391D650A283)
            }

            Local0 = (DerefOf (PAUI [0x0D]) % Arg2)
            M600 (Arg0, 0x2A, Local0, 0x01)
            Local0 = (DerefOf (PAUI [0x0F]) % Arg2)
            M600 (Arg0, 0x2B, Local0, 0xFE7CB391D650A283)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x0D) % Arg2)
            M600 (Arg0, 0x2C, Local0, 0x01)
            Local0 = (M601 (0x01, 0x0F) % Arg2)
            M600 (Arg0, 0x2D, Local0, 0xFE7CB391D650A283)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x0D, 0x01)) % Arg2)
                M600 (Arg0, 0x2E, Local0, 0x01)
                Local0 = (DerefOf (M602 (0x01, 0x0F, 0x01)) % Arg2)
                M600 (Arg0, 0x2F, Local0, 0xFE7CB391D650A283)
            }

            /* Conversion of the both operands */

            Store ((Arg1 % Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0x0321)
            Store ((Arg2 % Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0x02FD)
            Local0 = (Arg1 % Arg2)
            M600 (Arg0, 0x32, Local0, 0x0321)
            Local0 = (Arg2 % Arg1)
            M600 (Arg0, 0x33, Local0, 0x02FD)
        }

        /* Mod, 32-bit */

        Method (M046, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 % 0xD650A285), Local0)
            M600 (Arg0, 0x00, Local0, 0xD650A284)
            Store ((Arg2 % 0xD650A283), Local0)
            M600 (Arg0, 0x01, Local0, 0x01)
            Store ((Arg2 % AUIL), Local0)
            M600 (Arg0, 0x02, Local0, 0xD650A284)
            Store ((Arg2 % AUIM), Local0)
            M600 (Arg0, 0x0E, Local0, 0x01)
            If (Y078)
            {
                Store ((Arg2 % DerefOf (RefOf (AUIL))), Local0)
                M600 (Arg0, 0x04, Local0, 0xD650A284)
                Store ((Arg2 % DerefOf (RefOf (AUIM))), Local0)
                M600 (Arg0, 0x05, Local0, 0x01)
            }

            Store ((Arg2 % DerefOf (PAUI [0x15])), Local0)
            M600 (Arg0, 0x0C, Local0, 0xD650A284)
            Store ((Arg2 % DerefOf (PAUI [0x16])), Local0)
            M600 (Arg0, 0x07, Local0, 0x01)
            /* Method returns Integer */

            Store ((Arg2 % M601 (0x01, 0x15)), Local0)
            M600 (Arg0, 0x08, Local0, 0xD650A284)
            Store ((Arg2 % M601 (0x01, 0x16)), Local0)
            M600 (Arg0, 0x09, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 % DerefOf (M602 (0x01, 0x15, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xD650A284)
                Store ((Arg2 % DerefOf (M602 (0x01, 0x16, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x01)
            }

            Local0 = (Arg2 % 0xD650A285)
            M600 (Arg0, 0x0C, Local0, 0xD650A284)
            Local0 = (Arg2 % 0xD650A283)
            M600 (Arg0, 0x0D, Local0, 0x01)
            Local0 = (Arg2 % AUIL) /* \AUIL */
            M600 (Arg0, 0x0E, Local0, 0xD650A284)
            Local0 = (Arg2 % AUIM) /* \AUIM */
            M600 (Arg0, 0x0F, Local0, 0x01)
            If (Y078)
            {
                Local0 = (Arg2 % DerefOf (RefOf (AUIL)))
                M600 (Arg0, 0x10, Local0, 0xD650A284)
                Local0 = (Arg2 % DerefOf (RefOf (AUIM)))
                M600 (Arg0, 0x11, Local0, 0x01)
            }

            Local0 = (Arg2 % DerefOf (PAUI [0x15]))
            M600 (Arg0, 0x12, Local0, 0xD650A284)
            Local0 = (Arg2 % DerefOf (PAUI [0x16]))
            M600 (Arg0, 0x13, Local0, 0x01)
            /* Method returns Integer */

            Local0 = (Arg2 % M601 (0x01, 0x15))
            M600 (Arg0, 0x14, Local0, 0xD650A284)
            Local0 = (Arg2 % M601 (0x01, 0x16))
            M600 (Arg0, 0x15, Local0, 0x01)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 % DerefOf (M602 (0x01, 0x15, 0x01)))
                M600 (Arg0, 0x16, Local0, 0xD650A284)
                Local0 = (Arg2 % DerefOf (M602 (0x01, 0x16, 0x01)))
                M600 (Arg0, 0x17, Local0, 0x01)
            }

            /* Conversion of the second operand */

            Store ((0xD650A285 % Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0x01)
            Store ((0xD650A283 % Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0xD650A283)
            Store ((AUIL % Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0x01)
            Store ((AUIM % Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0xD650A283)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUIL)) % Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0x01)
                Store ((DerefOf (RefOf (AUIM)) % Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0xD650A283)
            }

            Store ((DerefOf (PAUI [0x15]) % Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0x01)
            Store ((DerefOf (PAUI [0x16]) % Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0xD650A283)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x15) % Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0x01)
            Store ((M601 (0x01, 0x16) % Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0xD650A283)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x15, 0x01)) % Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0x01)
                Store ((DerefOf (M602 (0x01, 0x16, 0x01)) % Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0xD650A283)
            }

            Local0 = (0xD650A285 % Arg2)
            M600 (Arg0, 0x24, Local0, 0x01)
            Local0 = (0xD650A283 % Arg2)
            M600 (Arg0, 0x25, Local0, 0xD650A283)
            Local0 = (AUIL % Arg2)
            M600 (Arg0, 0x26, Local0, 0x01)
            Local0 = (AUIM % Arg2)
            M600 (Arg0, 0x27, Local0, 0xD650A283)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUIL)) % Arg2)
                M600 (Arg0, 0x28, Local0, 0x01)
                Local0 = (DerefOf (RefOf (AUIM)) % Arg2)
                M600 (Arg0, 0x29, Local0, 0xD650A283)
            }

            Local0 = (DerefOf (PAUI [0x15]) % Arg2)
            M600 (Arg0, 0x2A, Local0, 0x01)
            Local0 = (DerefOf (PAUI [0x16]) % Arg2)
            M600 (Arg0, 0x2B, Local0, 0xD650A283)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x15) % Arg2)
            M600 (Arg0, 0x2C, Local0, 0x01)
            Local0 = (M601 (0x01, 0x16) % Arg2)
            M600 (Arg0, 0x2D, Local0, 0xD650A283)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x15, 0x01)) % Arg2)
                M600 (Arg0, 0x2E, Local0, 0x01)
                Local0 = (DerefOf (M602 (0x01, 0x16, 0x01)) % Arg2)
                M600 (Arg0, 0x2F, Local0, 0xD650A283)
            }

            /* Conversion of the both operands */

            Store ((Arg1 % Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0x0321)
            Store ((Arg2 % Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0x0261)
            Local0 = (Arg1 % Arg2)
            M600 (Arg0, 0x32, Local0, 0x0321)
            Local0 = (Arg2 % Arg1)
            M600 (Arg0, 0x33, Local0, 0x0261)
        }

        /* Multiply, common 32-bit/64-bit test */

        Method (M047, 2, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg1 * 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0x00)
            Store ((Arg1 * 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0x0321)
            Store ((Arg1 * AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0x00)
            Store ((Arg1 * AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0x0321)
            If (Y078)
            {
                Store ((Arg1 * DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0x00)
                Store ((Arg1 * DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0x0321)
            }

            Store ((Arg1 * DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0x00)
            Store ((Arg1 * DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0x0321)
            /* Method returns Integer */

            Store ((Arg1 * M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0x00)
            Store ((Arg1 * M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0x0321)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg1 * DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0x00)
                Store ((Arg1 * DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x0321)
            }

            Local0 = (Arg1 * 0x00)
            M600 (Arg0, 0x0C, Local0, 0x00)
            Local0 = (Arg1 * 0x01)
            M600 (Arg0, 0x0D, Local0, 0x0321)
            Local0 = (Arg1 * AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0x00)
            Local0 = (Arg1 * AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0x0321)
            If (Y078)
            {
                Local0 = (Arg1 * DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0x00)
                Local0 = (Arg1 * DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0x0321)
            }

            Local0 = (Arg1 * DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0x00)
            Local0 = (Arg1 * DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0x0321)
            /* Method returns Integer */

            Local0 = (Arg1 * M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0x00)
            Local0 = (Arg1 * M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0x0321)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg1 * DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0x00)
                Local0 = (Arg1 * DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0x0321)
            }

            /* Conversion of the second operand */

            Store ((0x00 * Arg1), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0x01 * Arg1), Local0)
            M600 (Arg0, 0x19, Local0, 0x0321)
            Store ((AUI5 * Arg1), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUI6 * Arg1), Local0)
            M600 (Arg0, 0x1B, Local0, 0x0321)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) * Arg1), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUI6)) * Arg1), Local0)
                M600 (Arg0, 0x1D, Local0, 0x0321)
            }

            Store ((DerefOf (PAUI [0x05]) * Arg1), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x06]) * Arg1), Local0)
            M600 (Arg0, 0x1F, Local0, 0x0321)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) * Arg1), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x06) * Arg1), Local0)
            M600 (Arg0, 0x21, Local0, 0x0321)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) * Arg1), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) * Arg1), Local0)
                M600 (Arg0, 0x23, Local0, 0x0321)
            }

            Local0 = (0x00 * Arg1)
            M600 (Arg0, 0x24, Local0, 0x00)
            Local0 = (0x01 * Arg1)
            M600 (Arg0, 0x25, Local0, 0x0321)
            Local0 = (AUI5 * Arg1)
            M600 (Arg0, 0x26, Local0, 0x00)
            Local0 = (AUI6 * Arg1)
            M600 (Arg0, 0x27, Local0, 0x0321)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) * Arg1)
                M600 (Arg0, 0x28, Local0, 0x00)
                Local0 = (DerefOf (RefOf (AUI6)) * Arg1)
                M600 (Arg0, 0x29, Local0, 0x0321)
            }

            Local0 = (DerefOf (PAUI [0x05]) * Arg1)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Local0 = (DerefOf (PAUI [0x06]) * Arg1)
            M600 (Arg0, 0x2B, Local0, 0x0321)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) * Arg1)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Local0 = (M601 (0x01, 0x06) * Arg1)
            M600 (Arg0, 0x2D, Local0, 0x0321)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) * Arg1)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) * Arg1)
                M600 (Arg0, 0x2F, Local0, 0x0321)
            }
        }

        /* Multiply, 64-bit */

        Method (M048, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 * 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0x00)
            Store ((Arg2 * 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 * AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0x00)
            Store ((Arg2 * AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0xFE7CB391D650A284)
            If (Y078)
            {
                Store ((Arg2 * DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0x00)
                Store ((Arg2 * DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0xFE7CB391D650A284)
            }

            Store ((Arg2 * DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0x00)
            Store ((Arg2 * DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0xFE7CB391D650A284)
            /* Method returns Integer */

            Store ((Arg2 * M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0x00)
            Store ((Arg2 * M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0xFE7CB391D650A284)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 * DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0x00)
                Store ((Arg2 * DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0xFE7CB391D650A284)
            }

            Local0 = (Arg2 * 0x00)
            M600 (Arg0, 0x0C, Local0, 0x00)
            Local0 = (Arg2 * 0x01)
            M600 (Arg0, 0x0D, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 * AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0x00)
            Local0 = (Arg2 * AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0xFE7CB391D650A284)
            If (Y078)
            {
                Local0 = (Arg2 * DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0x00)
                Local0 = (Arg2 * DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0xFE7CB391D650A284)
            }

            Local0 = (Arg2 * DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0x00)
            Local0 = (Arg2 * DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0xFE7CB391D650A284)
            /* Method returns Integer */

            Local0 = (Arg2 * M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0x00)
            Local0 = (Arg2 * M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0xFE7CB391D650A284)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 * DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0x00)
                Local0 = (Arg2 * DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0xFE7CB391D650A284)
            }

            /* Conversion of the second operand */

            Store ((0x00 * Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0x01 * Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0xFE7CB391D650A284)
            Store ((AUI5 * Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUI6 * Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0xFE7CB391D650A284)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) * Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUI6)) * Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0xFE7CB391D650A284)
            }

            Store ((DerefOf (PAUI [0x05]) * Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x06]) * Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0xFE7CB391D650A284)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) * Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x06) * Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0xFE7CB391D650A284)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) * Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) * Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0xFE7CB391D650A284)
            }

            Local0 = (0x00 * Arg2)
            M600 (Arg0, 0x24, Local0, 0x00)
            Local0 = (0x01 * Arg2)
            M600 (Arg0, 0x25, Local0, 0xFE7CB391D650A284)
            Local0 = (AUI5 * Arg2)
            M600 (Arg0, 0x26, Local0, 0x00)
            Local0 = (AUI6 * Arg2)
            M600 (Arg0, 0x27, Local0, 0xFE7CB391D650A284)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) * Arg2)
                M600 (Arg0, 0x28, Local0, 0x00)
                Local0 = (DerefOf (RefOf (AUI6)) * Arg2)
                M600 (Arg0, 0x29, Local0, 0xFE7CB391D650A284)
            }

            Local0 = (DerefOf (PAUI [0x05]) * Arg2)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Local0 = (DerefOf (PAUI [0x06]) * Arg2)
            M600 (Arg0, 0x2B, Local0, 0xFE7CB391D650A284)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) * Arg2)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Local0 = (M601 (0x01, 0x06) * Arg2)
            M600 (Arg0, 0x2D, Local0, 0xFE7CB391D650A284)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) * Arg2)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) * Arg2)
                M600 (Arg0, 0x2F, Local0, 0xFE7CB391D650A284)
            }

            /* Conversion of the both operands */

            Store ((Arg1 * Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0x442DDB4F924C7F04)
            Store ((Arg2 * Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0x442DDB4F924C7F04)
            Local0 = (Arg1 * Arg2)
            M600 (Arg0, 0x32, Local0, 0x442DDB4F924C7F04)
            Local0 = (Arg2 * Arg1)
            M600 (Arg0, 0x33, Local0, 0x442DDB4F924C7F04)
        }

        /* Multiply, 32-bit */

        Method (M049, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 * 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0x00)
            Store ((Arg2 * 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0xD650A284)
            Store ((Arg2 * AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0x00)
            Store ((Arg2 * AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0xD650A284)
            If (Y078)
            {
                Store ((Arg2 * DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0x00)
                Store ((Arg2 * DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0xD650A284)
            }

            Store ((Arg2 * DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0x00)
            Store ((Arg2 * DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0xD650A284)
            /* Method returns Integer */

            Store ((Arg2 * M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0x00)
            Store ((Arg2 * M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0xD650A284)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 * DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0x00)
                Store ((Arg2 * DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0xD650A284)
            }

            Local0 = (Arg2 * 0x00)
            M600 (Arg0, 0x0C, Local0, 0x00)
            Local0 = (Arg2 * 0x01)
            M600 (Arg0, 0x0D, Local0, 0xD650A284)
            Local0 = (Arg2 * AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0x00)
            Local0 = (Arg2 * AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0xD650A284)
            If (Y078)
            {
                Local0 = (Arg2 * DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0x00)
                Local0 = (Arg2 * DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0xD650A284)
            }

            Local0 = (Arg2 * DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0x00)
            Local0 = (Arg2 * DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0xD650A284)
            /* Method returns Integer */

            Local0 = (Arg2 * M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0x00)
            Local0 = (Arg2 * M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0xD650A284)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 * DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0x00)
                Local0 = (Arg2 * DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0xD650A284)
            }

            /* Conversion of the second operand */

            Store ((0x00 * Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0x01 * Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0xD650A284)
            Store ((AUI5 * Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUI6 * Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0xD650A284)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) * Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUI6)) * Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0xD650A284)
            }

            Store ((DerefOf (PAUI [0x05]) * Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x06]) * Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0xD650A284)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) * Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x06) * Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0xD650A284)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) * Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) * Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0xD650A284)
            }

            Local0 = (0x00 * Arg2)
            M600 (Arg0, 0x24, Local0, 0x00)
            Local0 = (0x01 * Arg2)
            M600 (Arg0, 0x25, Local0, 0xD650A284)
            Local0 = (AUI5 * Arg2)
            M600 (Arg0, 0x26, Local0, 0x00)
            Local0 = (AUI6 * Arg2)
            M600 (Arg0, 0x27, Local0, 0xD650A284)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) * Arg2)
                M600 (Arg0, 0x28, Local0, 0x00)
                Local0 = (DerefOf (RefOf (AUI6)) * Arg2)
                M600 (Arg0, 0x29, Local0, 0xD650A284)
            }

            Local0 = (DerefOf (PAUI [0x05]) * Arg2)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Local0 = (DerefOf (PAUI [0x06]) * Arg2)
            M600 (Arg0, 0x2B, Local0, 0xD650A284)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) * Arg2)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Local0 = (M601 (0x01, 0x06) * Arg2)
            M600 (Arg0, 0x2D, Local0, 0xD650A284)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) * Arg2)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) * Arg2)
                M600 (Arg0, 0x2F, Local0, 0xD650A284)
            }

            /* Conversion of the both operands */

            Store ((Arg1 * Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0x924C7F04)
            Store ((Arg2 * Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0x924C7F04)
            Local0 = (Arg1 * Arg2)
            M600 (Arg0, 0x32, Local0, 0x924C7F04)
            Local0 = (Arg2 * Arg1)
            M600 (Arg0, 0x33, Local0, 0x924C7F04)
        }

        /* NAnd, common 32-bit/64-bit test */

        Method (M04A, 2, NotSerialized)
        {
            /* Conversion of the first operand */

            Local0 = NAnd (Arg1, 0x00)
            M600 (Arg0, 0x00, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (Arg1, 0xFFFFFFFFFFFFFFFF)
            M600 (Arg0, 0x01, Local0, 0xFFFFFFFFFFFFFCDE)
            Local0 = NAnd (Arg1, AUI5)
            M600 (Arg0, 0x02, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (Arg1, AUIJ)
            M600 (Arg0, 0x03, Local0, 0xFFFFFFFFFFFFFCDE)
            If (Y078)
            {
                Local0 = NAnd (Arg1, DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x04, Local0, 0xFFFFFFFFFFFFFFFF)
                Local0 = NAnd (Arg1, DerefOf (RefOf (AUIJ)))
                M600 (Arg0, 0x05, Local0, 0xFFFFFFFFFFFFFCDE)
            }

            Local0 = NAnd (Arg1, DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x06, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (Arg1, DerefOf (PAUI [0x13]))
            M600 (Arg0, 0x07, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Integer */

            Local0 = NAnd (Arg1, M601 (0x01, 0x05))
            M600 (Arg0, 0x08, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (Arg1, M601 (0x01, 0x13))
            M600 (Arg0, 0x09, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = NAnd (Arg1, DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x0A, Local0, 0xFFFFFFFFFFFFFFFF)
                Local0 = NAnd (Arg1, DerefOf (M602 (0x01, 0x13, 0x01)))
                M600 (Arg0, 0x0B, Local0, 0xFFFFFFFFFFFFFCDE)
            }

            NAnd (Arg1, 0x00, Local0)
            M600 (Arg0, 0x0C, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (Arg1, 0xFFFFFFFFFFFFFFFF, Local0)
            M600 (Arg0, 0x0D, Local0, 0xFFFFFFFFFFFFFCDE)
            NAnd (Arg1, AUI5, Local0)
            M600 (Arg0, 0x0E, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (Arg1, AUIJ, Local0)
            M600 (Arg0, 0x0F, Local0, 0xFFFFFFFFFFFFFCDE)
            If (Y078)
            {
                NAnd (Arg1, DerefOf (RefOf (AUI5)), Local0)
                M600 (Arg0, 0x10, Local0, 0xFFFFFFFFFFFFFFFF)
                NAnd (Arg1, DerefOf (RefOf (AUIJ)), Local0)
                M600 (Arg0, 0x11, Local0, 0xFFFFFFFFFFFFFCDE)
            }

            NAnd (Arg1, DerefOf (PAUI [0x05]), Local0)
            M600 (Arg0, 0x12, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (Arg1, DerefOf (PAUI [0x13]), Local0)
            M600 (Arg0, 0x13, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Integer */

            NAnd (Arg1, M601 (0x01, 0x05), Local0)
            M600 (Arg0, 0x14, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (Arg1, M601 (0x01, 0x13), Local0)
            M600 (Arg0, 0x15, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                NAnd (Arg1, DerefOf (M602 (0x01, 0x05, 0x01)), Local0)
                M600 (Arg0, 0x16, Local0, 0xFFFFFFFFFFFFFFFF)
                NAnd (Arg1, DerefOf (M602 (0x01, 0x13, 0x01)), Local0)
                M600 (Arg0, 0x17, Local0, 0xFFFFFFFFFFFFFCDE)
            }

            /* Conversion of the second operand */

            Local0 = NAnd (0x00, Arg1)
            M600 (Arg0, 0x18, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (0xFFFFFFFFFFFFFFFF, Arg1)
            M600 (Arg0, 0x19, Local0, 0xFFFFFFFFFFFFFCDE)
            Local0 = NAnd (AUI5, Arg1)
            M600 (Arg0, 0x1A, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (AUIJ, Arg1)
            M600 (Arg0, 0x1B, Local0, 0xFFFFFFFFFFFFFCDE)
            If (Y078)
            {
                Local0 = NAnd (DerefOf (RefOf (AUI5)), Arg1)
                M600 (Arg0, 0x1C, Local0, 0xFFFFFFFFFFFFFFFF)
                Local0 = NAnd (DerefOf (RefOf (AUIJ)), Arg1)
                M600 (Arg0, 0x1D, Local0, 0xFFFFFFFFFFFFFCDE)
            }

            Local0 = NAnd (DerefOf (PAUI [0x05]), Arg1)
            M600 (Arg0, 0x1E, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (DerefOf (PAUI [0x13]), Arg1)
            M600 (Arg0, 0x1F, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Integer */

            Local0 = NAnd (M601 (0x01, 0x05), Arg1)
            M600 (Arg0, 0x20, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (M601 (0x01, 0x13), Arg1)
            M600 (Arg0, 0x21, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = NAnd (DerefOf (M602 (0x01, 0x05, 0x01)), Arg1)
                M600 (Arg0, 0x22, Local0, 0xFFFFFFFFFFFFFFFF)
                Local0 = NAnd (DerefOf (M602 (0x01, 0x13, 0x01)), Arg1)
                M600 (Arg0, 0x23, Local0, 0xFFFFFFFFFFFFFCDE)
            }

            NAnd (0x00, Arg1, Local0)
            M600 (Arg0, 0x24, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (0xFFFFFFFFFFFFFFFF, Arg1, Local0)
            M600 (Arg0, 0x25, Local0, 0xFFFFFFFFFFFFFCDE)
            NAnd (AUI5, Arg1, Local0)
            M600 (Arg0, 0x26, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (AUIJ, Arg1, Local0)
            M600 (Arg0, 0x27, Local0, 0xFFFFFFFFFFFFFCDE)
            If (Y078)
            {
                NAnd (DerefOf (RefOf (AUI5)), Arg1, Local0)
                M600 (Arg0, 0x28, Local0, 0xFFFFFFFFFFFFFFFF)
                NAnd (DerefOf (RefOf (AUIJ)), Arg1, Local0)
                M600 (Arg0, 0x29, Local0, 0xFFFFFFFFFFFFFCDE)
            }

            NAnd (DerefOf (PAUI [0x05]), Arg1, Local0)
            M600 (Arg0, 0x2A, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (DerefOf (PAUI [0x13]), Arg1, Local0)
            M600 (Arg0, 0x2B, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Integer */

            NAnd (M601 (0x01, 0x05), Arg1, Local0)
            M600 (Arg0, 0x2C, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (M601 (0x01, 0x13), Arg1, Local0)
            M600 (Arg0, 0x2D, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                NAnd (DerefOf (M602 (0x01, 0x05, 0x01)), Arg1, Local0)
                M600 (Arg0, 0x2E, Local0, 0xFFFFFFFFFFFFFFFF)
                NAnd (DerefOf (M602 (0x01, 0x13, 0x01)), Arg1, Local0)
                M600 (Arg0, 0x2F, Local0, 0xFFFFFFFFFFFFFCDE)
            }
        }

        /* NAnd, 64-bit */

        Method (M04B, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Local0 = NAnd (Arg2, 0x00)
            M600 (Arg0, 0x00, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (Arg2, 0xFFFFFFFFFFFFFFFF)
            M600 (Arg0, 0x01, Local0, 0x01834C6E29AF5D7B)
            Local0 = NAnd (Arg2, AUI5)
            M600 (Arg0, 0x02, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (Arg2, AUIJ)
            M600 (Arg0, 0x03, Local0, 0x01834C6E29AF5D7B)
            If (Y078)
            {
                Local0 = NAnd (Arg2, DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x04, Local0, 0xFFFFFFFFFFFFFFFF)
                Local0 = NAnd (Arg2, DerefOf (RefOf (AUIJ)))
                M600 (Arg0, 0x05, Local0, 0x01834C6E29AF5D7B)
            }

            Local0 = NAnd (Arg2, DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x06, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (Arg2, DerefOf (PAUI [0x13]))
            M600 (Arg0, 0x07, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Integer */

            Local0 = NAnd (Arg2, M601 (0x01, 0x05))
            M600 (Arg0, 0x08, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (Arg2, M601 (0x01, 0x13))
            M600 (Arg0, 0x09, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = NAnd (Arg2, DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x0A, Local0, 0xFFFFFFFFFFFFFFFF)
                Local0 = NAnd (Arg2, DerefOf (M602 (0x01, 0x13, 0x01)))
                M600 (Arg0, 0x0B, Local0, 0x01834C6E29AF5D7B)
            }

            NAnd (Arg2, 0x00, Local0)
            M600 (Arg0, 0x0C, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (Arg2, 0xFFFFFFFFFFFFFFFF, Local0)
            M600 (Arg0, 0x0D, Local0, 0x01834C6E29AF5D7B)
            NAnd (Arg2, AUI5, Local0)
            M600 (Arg0, 0x0E, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (Arg2, AUIJ, Local0)
            M600 (Arg0, 0x0F, Local0, 0x01834C6E29AF5D7B)
            If (Y078)
            {
                NAnd (Arg2, DerefOf (RefOf (AUI5)), Local0)
                M600 (Arg0, 0x10, Local0, 0xFFFFFFFFFFFFFFFF)
                NAnd (Arg2, DerefOf (RefOf (AUIJ)), Local0)
                M600 (Arg0, 0x11, Local0, 0x01834C6E29AF5D7B)
            }

            NAnd (Arg2, DerefOf (PAUI [0x05]), Local0)
            M600 (Arg0, 0x12, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (Arg2, DerefOf (PAUI [0x13]), Local0)
            M600 (Arg0, 0x13, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Integer */

            NAnd (Arg2, M601 (0x01, 0x05), Local0)
            M600 (Arg0, 0x14, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (Arg2, M601 (0x01, 0x13), Local0)
            M600 (Arg0, 0x15, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                NAnd (Arg2, DerefOf (M602 (0x01, 0x05, 0x01)), Local0)
                M600 (Arg0, 0x16, Local0, 0xFFFFFFFFFFFFFFFF)
                NAnd (Arg2, DerefOf (M602 (0x01, 0x13, 0x01)), Local0)
                M600 (Arg0, 0x17, Local0, 0x01834C6E29AF5D7B)
            }

            /* Conversion of the second operand */

            Local0 = NAnd (0x00, Arg2)
            M600 (Arg0, 0x18, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (0xFFFFFFFFFFFFFFFF, Arg2)
            M600 (Arg0, 0x19, Local0, 0x01834C6E29AF5D7B)
            Local0 = NAnd (AUI5, Arg2)
            M600 (Arg0, 0x1A, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (AUIJ, Arg2)
            M600 (Arg0, 0x1B, Local0, 0x01834C6E29AF5D7B)
            If (Y078)
            {
                Local0 = NAnd (DerefOf (RefOf (AUI5)), Arg2)
                M600 (Arg0, 0x1C, Local0, 0xFFFFFFFFFFFFFFFF)
                Local0 = NAnd (DerefOf (RefOf (AUIJ)), Arg2)
                M600 (Arg0, 0x1D, Local0, 0x01834C6E29AF5D7B)
            }

            Local0 = NAnd (DerefOf (PAUI [0x05]), Arg2)
            M600 (Arg0, 0x1E, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (DerefOf (PAUI [0x13]), Arg2)
            M600 (Arg0, 0x1F, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Integer */

            Local0 = NAnd (M601 (0x01, 0x05), Arg2)
            M600 (Arg0, 0x20, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = NAnd (M601 (0x01, 0x13), Arg2)
            M600 (Arg0, 0x21, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = NAnd (DerefOf (M602 (0x01, 0x05, 0x01)), Arg2)
                M600 (Arg0, 0x22, Local0, 0xFFFFFFFFFFFFFFFF)
                Local0 = NAnd (DerefOf (M602 (0x01, 0x13, 0x01)), Arg2)
                M600 (Arg0, 0x23, Local0, 0x01834C6E29AF5D7B)
            }

            NAnd (0x00, Arg2, Local0)
            M600 (Arg0, 0x24, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (0xFFFFFFFFFFFFFFFF, Arg2, Local0)
            M600 (Arg0, 0x25, Local0, 0x01834C6E29AF5D7B)
            NAnd (AUI5, Arg2, Local0)
            M600 (Arg0, 0x26, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (AUIJ, Arg2, Local0)
            M600 (Arg0, 0x27, Local0, 0x01834C6E29AF5D7B)
            If (Y078)
            {
                NAnd (DerefOf (RefOf (AUI5)), Arg2, Local0)
                M600 (Arg0, 0x28, Local0, 0xFFFFFFFFFFFFFFFF)
                NAnd (DerefOf (RefOf (AUIJ)), Arg2, Local0)
                M600 (Arg0, 0x29, Local0, 0x01834C6E29AF5D7B)
            }

            NAnd (DerefOf (PAUI [0x05]), Arg2, Local0)
            M600 (Arg0, 0x2A, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (DerefOf (PAUI [0x13]), Arg2, Local0)
            M600 (Arg0, 0x2B, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Integer */

            NAnd (M601 (0x01, 0x05), Arg2, Local0)
            M600 (Arg0, 0x2C, Local0, 0xFFFFFFFFFFFFFFFF)
            NAnd (M601 (0x01, 0x13), Arg2, Local0)
            M600 (Arg0, 0x2D, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                NAnd (DerefOf (M602 (0x01, 0x05, 0x01)), Arg2, Local0)
                M600 (Arg0, 0x2E, Local0, 0xFFFFFFFFFFFFFFFF)
                NAnd (DerefOf (M602 (0x01, 0x13, 0x01)), Arg2, Local0)
                M600 (Arg0, 0x2F, Local0, 0x01834C6E29AF5D7B)
            }

            /* Conversion of the both operands */

            Local0 = NAnd (Arg1, Arg2)
            M600 (Arg0, 0x30, Local0, 0xFFFFFFFFFFFFFDFF)
            Local0 = NAnd (Arg2, Arg1)
            M600 (Arg0, 0x31, Local0, 0xFFFFFFFFFFFFFDFF)
            NAnd (Arg1, Arg2, Local0)
            M600 (Arg0, 0x32, Local0, 0xFFFFFFFFFFFFFDFF)
            NAnd (Arg2, Arg1, Local0)
            M600 (Arg0, 0x33, Local0, 0xFFFFFFFFFFFFFDFF)
        }

        /* NAnd, 32-bit */

        Method (M04C, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Local0 = NAnd (Arg2, 0x00)
            M600 (Arg0, 0x00, Local0, 0xFFFFFFFF)
            Local0 = NAnd (Arg2, 0xFFFFFFFF)
            M600 (Arg0, 0x01, Local0, 0x29AF5D7B)
            Local0 = NAnd (Arg2, AUI5)
            M600 (Arg0, 0x02, Local0, 0xFFFFFFFF)
            Local0 = NAnd (Arg2, AUII)
            M600 (Arg0, 0x03, Local0, 0x29AF5D7B)
            If (Y078)
            {
                Local0 = NAnd (Arg2, DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x04, Local0, 0xFFFFFFFF)
                Local0 = NAnd (Arg2, DerefOf (RefOf (AUII)))
                M600 (Arg0, 0x05, Local0, 0x29AF5D7B)
            }

            Local0 = NAnd (Arg2, DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x06, Local0, 0xFFFFFFFF)
            Local0 = NAnd (Arg2, DerefOf (PAUI [0x12]))
            M600 (Arg0, 0x07, Local0, 0x29AF5D7B)
            /* Method returns Integer */

            Local0 = NAnd (Arg2, M601 (0x01, 0x05))
            M600 (Arg0, 0x08, Local0, 0xFFFFFFFF)
            Local0 = NAnd (Arg2, M601 (0x01, 0x12))
            M600 (Arg0, 0x09, Local0, 0x29AF5D7B)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = NAnd (Arg2, DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x0A, Local0, 0xFFFFFFFF)
                Local0 = NAnd (Arg2, DerefOf (M602 (0x01, 0x12, 0x01)))
                M600 (Arg0, 0x0B, Local0, 0x29AF5D7B)
            }

            NAnd (Arg2, 0x00, Local0)
            M600 (Arg0, 0x0C, Local0, 0xFFFFFFFF)
            NAnd (Arg2, 0xFFFFFFFF, Local0)
            M600 (Arg0, 0x0D, Local0, 0x29AF5D7B)
            NAnd (Arg2, AUI5, Local0)
            M600 (Arg0, 0x0E, Local0, 0xFFFFFFFF)
            NAnd (Arg2, AUII, Local0)
            M600 (Arg0, 0x0F, Local0, 0x29AF5D7B)
            If (Y078)
            {
                NAnd (Arg2, DerefOf (RefOf (AUI5)), Local0)
                M600 (Arg0, 0x10, Local0, 0xFFFFFFFF)
                NAnd (Arg2, DerefOf (RefOf (AUII)), Local0)
                M600 (Arg0, 0x11, Local0, 0x29AF5D7B)
            }

            NAnd (Arg2, DerefOf (PAUI [0x05]), Local0)
            M600 (Arg0, 0x12, Local0, 0xFFFFFFFF)
            NAnd (Arg2, DerefOf (PAUI [0x12]), Local0)
            M600 (Arg0, 0x13, Local0, 0x29AF5D7B)
            /* Method returns Integer */

            NAnd (Arg2, M601 (0x01, 0x05), Local0)
            M600 (Arg0, 0x14, Local0, 0xFFFFFFFF)
            NAnd (Arg2, M601 (0x01, 0x12), Local0)
            M600 (Arg0, 0x15, Local0, 0x29AF5D7B)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                NAnd (Arg2, DerefOf (M602 (0x01, 0x05, 0x01)), Local0)
                M600 (Arg0, 0x16, Local0, 0xFFFFFFFF)
                NAnd (Arg2, DerefOf (M602 (0x01, 0x12, 0x01)), Local0)
                M600 (Arg0, 0x17, Local0, 0x29AF5D7B)
            }

            /* Conversion of the second operand */

            Local0 = NAnd (0x00, Arg2)
            M600 (Arg0, 0x18, Local0, 0xFFFFFFFF)
            Local0 = NAnd (0xFFFFFFFF, Arg2)
            M600 (Arg0, 0x19, Local0, 0x29AF5D7B)
            Local0 = NAnd (AUI5, Arg2)
            M600 (Arg0, 0x1A, Local0, 0xFFFFFFFF)
            Local0 = NAnd (AUII, Arg2)
            M600 (Arg0, 0x1B, Local0, 0x29AF5D7B)
            If (Y078)
            {
                Local0 = NAnd (DerefOf (RefOf (AUI5)), Arg2)
                M600 (Arg0, 0x1C, Local0, 0xFFFFFFFF)
                Local0 = NAnd (DerefOf (RefOf (AUII)), Arg2)
                M600 (Arg0, 0x1D, Local0, 0x29AF5D7B)
            }

            Local0 = NAnd (DerefOf (PAUI [0x05]), Arg2)
            M600 (Arg0, 0x1E, Local0, 0xFFFFFFFF)
            Local0 = NAnd (DerefOf (PAUI [0x12]), Arg2)
            M600 (Arg0, 0x1F, Local0, 0x29AF5D7B)
            /* Method returns Integer */

            Local0 = NAnd (M601 (0x01, 0x05), Arg2)
            M600 (Arg0, 0x20, Local0, 0xFFFFFFFF)
            Local0 = NAnd (M601 (0x01, 0x12), Arg2)
            M600 (Arg0, 0x21, Local0, 0x29AF5D7B)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = NAnd (DerefOf (M602 (0x01, 0x05, 0x01)), Arg2)
                M600 (Arg0, 0x22, Local0, 0xFFFFFFFF)
                Local0 = NAnd (DerefOf (M602 (0x01, 0x12, 0x01)), Arg2)
                M600 (Arg0, 0x23, Local0, 0x29AF5D7B)
            }

            NAnd (0x00, Arg2, Local0)
            M600 (Arg0, 0x24, Local0, 0xFFFFFFFF)
            NAnd (0xFFFFFFFF, Arg2, Local0)
            M600 (Arg0, 0x25, Local0, 0x29AF5D7B)
            NAnd (AUI5, Arg2, Local0)
            M600 (Arg0, 0x26, Local0, 0xFFFFFFFF)
            NAnd (AUII, Arg2, Local0)
            M600 (Arg0, 0x27, Local0, 0x29AF5D7B)
            If (Y078)
            {
                NAnd (DerefOf (RefOf (AUI5)), Arg2, Local0)
                M600 (Arg0, 0x28, Local0, 0xFFFFFFFF)
                NAnd (DerefOf (RefOf (AUII)), Arg2, Local0)
                M600 (Arg0, 0x29, Local0, 0x29AF5D7B)
            }

            NAnd (DerefOf (PAUI [0x05]), Arg2, Local0)
            M600 (Arg0, 0x2A, Local0, 0xFFFFFFFF)
            NAnd (DerefOf (PAUI [0x12]), Arg2, Local0)
            M600 (Arg0, 0x2B, Local0, 0x29AF5D7B)
            /* Method returns Integer */

            NAnd (M601 (0x01, 0x05), Arg2, Local0)
            M600 (Arg0, 0x2C, Local0, 0xFFFFFFFF)
            NAnd (M601 (0x01, 0x12), Arg2, Local0)
            M600 (Arg0, 0x2D, Local0, 0x29AF5D7B)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                NAnd (DerefOf (M602 (0x01, 0x05, 0x01)), Arg2, Local0)
                M600 (Arg0, 0x2E, Local0, 0xFFFFFFFF)
                NAnd (DerefOf (M602 (0x01, 0x12, 0x01)), Arg2, Local0)
                M600 (Arg0, 0x2F, Local0, 0x29AF5D7B)
            }

            /* Conversion of the both operands */

            Local0 = NAnd (Arg1, Arg2)
            M600 (Arg0, 0x30, Local0, 0xFFFFFDFF)
            Local0 = NAnd (Arg2, Arg1)
            M600 (Arg0, 0x31, Local0, 0xFFFFFDFF)
            NAnd (Arg1, Arg2, Local0)
            M600 (Arg0, 0x32, Local0, 0xFFFFFDFF)
            NAnd (Arg2, Arg1, Local0)
            M600 (Arg0, 0x33, Local0, 0xFFFFFDFF)
        }

        /* NOr, common 32-bit/64-bit test */

        Method (M04D, 2, NotSerialized)
        {
            /* Conversion of the first operand */

            Local0 = NOr (Arg1, 0x00)
            M600 (Arg0, 0x00, Local0, 0xFFFFFFFFFFFFFCDE)
            Local0 = NOr (Arg1, 0xFFFFFFFFFFFFFFFF)
            M600 (Arg0, 0x01, Local0, 0x00)
            Local0 = NOr (Arg1, AUI5)
            M600 (Arg0, 0x02, Local0, 0xFFFFFFFFFFFFFCDE)
            Local0 = NOr (Arg1, AUIJ)
            M600 (Arg0, 0x03, Local0, 0x00)
            If (Y078)
            {
                Local0 = NOr (Arg1, DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x04, Local0, 0xFFFFFFFFFFFFFCDE)
                Local0 = NOr (Arg1, DerefOf (RefOf (AUIJ)))
                M600 (Arg0, 0x05, Local0, 0x00)
            }

            Local0 = NOr (Arg1, DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x06, Local0, 0xFFFFFFFFFFFFFCDE)
            Local0 = NOr (Arg1, DerefOf (PAUI [0x13]))
            M600 (Arg0, 0x07, Local0, 0x00)
            /* Method returns Integer */

            Local0 = NOr (Arg1, M601 (0x01, 0x05))
            M600 (Arg0, 0x08, Local0, 0xFFFFFFFFFFFFFCDE)
            Local0 = NOr (Arg1, M601 (0x01, 0x13))
            M600 (Arg0, 0x09, Local0, 0x00)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = NOr (Arg1, DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x0A, Local0, 0xFFFFFFFFFFFFFCDE)
                Local0 = NOr (Arg1, DerefOf (M602 (0x01, 0x13, 0x01)))
                M600 (Arg0, 0x0B, Local0, 0x00)
            }

            NOr (Arg1, 0x00, Local0)
            M600 (Arg0, 0x0C, Local0, 0xFFFFFFFFFFFFFCDE)
            NOr (Arg1, 0xFFFFFFFFFFFFFFFF, Local0)
            M600 (Arg0, 0x0D, Local0, 0x00)
            NOr (Arg1, AUI5, Local0)
            M600 (Arg0, 0x0E, Local0, 0xFFFFFFFFFFFFFCDE)
            NOr (Arg1, AUIJ, Local0)
            M600 (Arg0, 0x0F, Local0, 0x00)
            If (Y078)
            {
                NOr (Arg1, DerefOf (RefOf (AUI5)), Local0)
                M600 (Arg0, 0x10, Local0, 0xFFFFFFFFFFFFFCDE)
                NOr (Arg1, DerefOf (RefOf (AUIJ)), Local0)
                M600 (Arg0, 0x11, Local0, 0x00)
            }

            NOr (Arg1, DerefOf (PAUI [0x05]), Local0)
            M600 (Arg0, 0x12, Local0, 0xFFFFFFFFFFFFFCDE)
            NOr (Arg1, DerefOf (PAUI [0x13]), Local0)
            M600 (Arg0, 0x13, Local0, 0x00)
            /* Method returns Integer */

            NOr (Arg1, M601 (0x01, 0x05), Local0)
            M600 (Arg0, 0x14, Local0, 0xFFFFFFFFFFFFFCDE)
            NOr (Arg1, M601 (0x01, 0x13), Local0)
            M600 (Arg0, 0x15, Local0, 0x00)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                NOr (Arg1, DerefOf (M602 (0x01, 0x05, 0x01)), Local0)
                M600 (Arg0, 0x16, Local0, 0xFFFFFFFFFFFFFCDE)
                NOr (Arg1, DerefOf (M602 (0x01, 0x13, 0x01)), Local0)
                M600 (Arg0, 0x17, Local0, 0x00)
            }

            /* Conversion of the second operand */

            Local0 = NOr (0x00, Arg1)
            M600 (Arg0, 0x18, Local0, 0xFFFFFFFFFFFFFCDE)
            Local0 = NOr (0xFFFFFFFFFFFFFFFF, Arg1)
            M600 (Arg0, 0x19, Local0, 0x00)
            Local0 = NOr (AUI5, Arg1)
            M600 (Arg0, 0x1A, Local0, 0xFFFFFFFFFFFFFCDE)
            Local0 = NOr (AUIJ, Arg1)
            M600 (Arg0, 0x1B, Local0, 0x00)
            If (Y078)
            {
                Local0 = NOr (DerefOf (RefOf (AUI5)), Arg1)
                M600 (Arg0, 0x1C, Local0, 0xFFFFFFFFFFFFFCDE)
                Local0 = NOr (DerefOf (RefOf (AUIJ)), Arg1)
                M600 (Arg0, 0x1D, Local0, 0x00)
            }

            Local0 = NOr (DerefOf (PAUI [0x05]), Arg1)
            M600 (Arg0, 0x1E, Local0, 0xFFFFFFFFFFFFFCDE)
            Local0 = NOr (DerefOf (PAUI [0x13]), Arg1)
            M600 (Arg0, 0x1F, Local0, 0x00)
            /* Method returns Integer */

            Local0 = NOr (M601 (0x01, 0x05), Arg1)
            M600 (Arg0, 0x20, Local0, 0xFFFFFFFFFFFFFCDE)
            Local0 = NOr (M601 (0x01, 0x13), Arg1)
            M600 (Arg0, 0x21, Local0, 0x00)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = NOr (DerefOf (M602 (0x01, 0x05, 0x01)), Arg1)
                M600 (Arg0, 0x22, Local0, 0xFFFFFFFFFFFFFCDE)
                Local0 = NOr (DerefOf (M602 (0x01, 0x13, 0x01)), Arg1)
                M600 (Arg0, 0x23, Local0, 0x00)
            }

            NOr (0x00, Arg1, Local0)
            M600 (Arg0, 0x24, Local0, 0xFFFFFFFFFFFFFCDE)
            NOr (0xFFFFFFFFFFFFFFFF, Arg1, Local0)
            M600 (Arg0, 0x25, Local0, 0x00)
            NOr (AUI5, Arg1, Local0)
            M600 (Arg0, 0x26, Local0, 0xFFFFFFFFFFFFFCDE)
            NOr (AUIJ, Arg1, Local0)
            M600 (Arg0, 0x27, Local0, 0x00)
            If (Y078)
            {
                NOr (DerefOf (RefOf (AUI5)), Arg1, Local0)
                M600 (Arg0, 0x28, Local0, 0xFFFFFFFFFFFFFCDE)
                NOr (DerefOf (RefOf (AUIJ)), Arg1, Local0)
                M600 (Arg0, 0x29, Local0, 0x00)
            }

            NOr (DerefOf (PAUI [0x05]), Arg1, Local0)
            M600 (Arg0, 0x2A, Local0, 0xFFFFFFFFFFFFFCDE)
            NOr (DerefOf (PAUI [0x13]), Arg1, Local0)
            M600 (Arg0, 0x2B, Local0, 0x00)
            /* Method returns Integer */

            NOr (M601 (0x01, 0x05), Arg1, Local0)
            M600 (Arg0, 0x2C, Local0, 0xFFFFFFFFFFFFFCDE)
            NOr (M601 (0x01, 0x13), Arg1, Local0)
            M600 (Arg0, 0x2D, Local0, 0x00)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                NOr (DerefOf (M602 (0x01, 0x05, 0x01)), Arg1, Local0)
                M600 (Arg0, 0x2E, Local0, 0xFFFFFFFFFFFFFCDE)
                NOr (DerefOf (M602 (0x01, 0x13, 0x01)), Arg1, Local0)
                M600 (Arg0, 0x2F, Local0, 0x00)
            }
        }

        /* NOr, 64-bit */

        Method (M04E, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Local0 = NOr (Arg2, 0x00)
            M600 (Arg0, 0x00, Local0, 0x01834C6E29AF5D7B)
            Local0 = NOr (Arg2, 0xFFFFFFFFFFFFFFFF)
            M600 (Arg0, 0x01, Local0, 0x00)
            Local0 = NOr (Arg2, AUI5)
            M600 (Arg0, 0x02, Local0, 0x01834C6E29AF5D7B)
            Local0 = NOr (Arg2, AUIJ)
            M600 (Arg0, 0x03, Local0, 0x00)
            If (Y078)
            {
                Local0 = NOr (Arg2, DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x04, Local0, 0x01834C6E29AF5D7B)
                Local0 = NOr (Arg2, DerefOf (RefOf (AUIJ)))
                M600 (Arg0, 0x05, Local0, 0x00)
            }

            Local0 = NOr (Arg2, DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x06, Local0, 0x01834C6E29AF5D7B)
            Local0 = NOr (Arg2, DerefOf (PAUI [0x13]))
            M600 (Arg0, 0x07, Local0, 0x00)
            /* Method returns Integer */

            Local0 = NOr (Arg2, M601 (0x01, 0x05))
            M600 (Arg0, 0x08, Local0, 0x01834C6E29AF5D7B)
            Local0 = NOr (Arg2, M601 (0x01, 0x13))
            M600 (Arg0, 0x09, Local0, 0x00)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = NOr (Arg2, DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x0A, Local0, 0x01834C6E29AF5D7B)
                Local0 = NOr (Arg2, DerefOf (M602 (0x01, 0x13, 0x01)))
                M600 (Arg0, 0x0B, Local0, 0x00)
            }

            NOr (Arg2, 0x00, Local0)
            M600 (Arg0, 0x0C, Local0, 0x01834C6E29AF5D7B)
            NOr (Arg2, 0xFFFFFFFFFFFFFFFF, Local0)
            M600 (Arg0, 0x0D, Local0, 0x00)
            NOr (Arg2, AUI5, Local0)
            M600 (Arg0, 0x0E, Local0, 0x01834C6E29AF5D7B)
            NOr (Arg2, AUIJ, Local0)
            M600 (Arg0, 0x0F, Local0, 0x00)
            If (Y078)
            {
                NOr (Arg2, DerefOf (RefOf (AUI5)), Local0)
                M600 (Arg0, 0x10, Local0, 0x01834C6E29AF5D7B)
                NOr (Arg2, DerefOf (RefOf (AUIJ)), Local0)
                M600 (Arg0, 0x11, Local0, 0x00)
            }

            NOr (Arg2, DerefOf (PAUI [0x05]), Local0)
            M600 (Arg0, 0x12, Local0, 0x01834C6E29AF5D7B)
            NOr (Arg2, DerefOf (PAUI [0x13]), Local0)
            M600 (Arg0, 0x13, Local0, 0x00)
            /* Method returns Integer */

            NOr (Arg2, M601 (0x01, 0x05), Local0)
            M600 (Arg0, 0x14, Local0, 0x01834C6E29AF5D7B)
            NOr (Arg2, M601 (0x01, 0x13), Local0)
            M600 (Arg0, 0x15, Local0, 0x00)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                NOr (Arg2, DerefOf (M602 (0x01, 0x05, 0x01)), Local0)
                M600 (Arg0, 0x16, Local0, 0x01834C6E29AF5D7B)
                NOr (Arg2, DerefOf (M602 (0x01, 0x13, 0x01)), Local0)
                M600 (Arg0, 0x17, Local0, 0x00)
            }

            /* Conversion of the second operand */

            Local0 = NOr (0x00, Arg2)
            M600 (Arg0, 0x18, Local0, 0x01834C6E29AF5D7B)
            Local0 = NOr (0xFFFFFFFFFFFFFFFF, Arg2)
            M600 (Arg0, 0x19, Local0, 0x00)
            Local0 = NOr (AUI5, Arg2)
            M600 (Arg0, 0x1A, Local0, 0x01834C6E29AF5D7B)
            Local0 = NOr (AUIJ, Arg2)
            M600 (Arg0, 0x1B, Local0, 0x00)
            If (Y078)
            {
                Local0 = NOr (DerefOf (RefOf (AUI5)), Arg2)
                M600 (Arg0, 0x1C, Local0, 0x01834C6E29AF5D7B)
                Local0 = NOr (DerefOf (RefOf (AUIJ)), Arg2)
                M600 (Arg0, 0x1D, Local0, 0x00)
            }

            Local0 = NOr (DerefOf (PAUI [0x05]), Arg2)
            M600 (Arg0, 0x1E, Local0, 0x01834C6E29AF5D7B)
            Local0 = NOr (DerefOf (PAUI [0x13]), Arg2)
            M600 (Arg0, 0x1F, Local0, 0x00)
            /* Method returns Integer */

            Local0 = NOr (M601 (0x01, 0x05), Arg2)
            M600 (Arg0, 0x20, Local0, 0x01834C6E29AF5D7B)
            Local0 = NOr (M601 (0x01, 0x13), Arg2)
            M600 (Arg0, 0x21, Local0, 0x00)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = NOr (DerefOf (M602 (0x01, 0x05, 0x01)), Arg2)
                M600 (Arg0, 0x22, Local0, 0x01834C6E29AF5D7B)
                Local0 = NOr (DerefOf (M602 (0x01, 0x13, 0x01)), Arg2)
                M600 (Arg0, 0x23, Local0, 0x00)
            }

            NOr (0x00, Arg2, Local0)
            M600 (Arg0, 0x24, Local0, 0x01834C6E29AF5D7B)
            NOr (0xFFFFFFFFFFFFFFFF, Arg2, Local0)
            M600 (Arg0, 0x25, Local0, 0x00)
            NOr (AUI5, Arg2, Local0)
            M600 (Arg0, 0x26, Local0, 0x01834C6E29AF5D7B)
            NOr (AUIJ, Arg2, Local0)
            M600 (Arg0, 0x27, Local0, 0x00)
            If (Y078)
            {
                NOr (DerefOf (RefOf (AUI5)), Arg2, Local0)
                M600 (Arg0, 0x28, Local0, 0x01834C6E29AF5D7B)
                NOr (DerefOf (RefOf (AUIJ)), Arg2, Local0)
                M600 (Arg0, 0x29, Local0, 0x00)
            }

            NOr (DerefOf (PAUI [0x05]), Arg2, Local0)
            M600 (Arg0, 0x2A, Local0, 0x01834C6E29AF5D7B)
            NOr (DerefOf (PAUI [0x13]), Arg2, Local0)
            M600 (Arg0, 0x2B, Local0, 0x00)
            /* Method returns Integer */

            NOr (M601 (0x01, 0x05), Arg2, Local0)
            M600 (Arg0, 0x2C, Local0, 0x01834C6E29AF5D7B)
            NOr (M601 (0x01, 0x13), Arg2, Local0)
            M600 (Arg0, 0x2D, Local0, 0x00)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                NOr (DerefOf (M602 (0x01, 0x05, 0x01)), Arg2, Local0)
                M600 (Arg0, 0x2E, Local0, 0x01834C6E29AF5D7B)
                NOr (DerefOf (M602 (0x01, 0x13, 0x01)), Arg2, Local0)
                M600 (Arg0, 0x2F, Local0, 0x00)
            }

            /* Conversion of the both operands */

            Local0 = NOr (Arg1, Arg2)
            M600 (Arg0, 0x30, Local0, 0x01834C6E29AF5C5A)
            Local0 = NOr (Arg2, Arg1)
            M600 (Arg0, 0x31, Local0, 0x01834C6E29AF5C5A)
            NOr (Arg1, Arg2, Local0)
            M600 (Arg0, 0x32, Local0, 0x01834C6E29AF5C5A)
            NOr (Arg2, Arg1, Local0)
            M600 (Arg0, 0x33, Local0, 0x01834C6E29AF5C5A)
        }

        /* NOr, 32-bit */

        Method (M04F, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Local0 = NOr (Arg2, 0x00)
            M600 (Arg0, 0x00, Local0, 0x29AF5D7B)
            Local0 = NOr (Arg2, 0xFFFFFFFF)
            M600 (Arg0, 0x01, Local0, 0x00)
            Local0 = NOr (Arg2, AUI5)
            M600 (Arg0, 0x02, Local0, 0x29AF5D7B)
            Local0 = NOr (Arg2, AUII)
            M600 (Arg0, 0x03, Local0, 0x00)
            If (Y078)
            {
                Local0 = NOr (Arg2, DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x04, Local0, 0x29AF5D7B)
                Local0 = NOr (Arg2, DerefOf (RefOf (AUII)))
                M600 (Arg0, 0x05, Local0, 0x00)
            }

            Local0 = NOr (Arg2, DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x06, Local0, 0x29AF5D7B)
            Local0 = NOr (Arg2, DerefOf (PAUI [0x12]))
            M600 (Arg0, 0x07, Local0, 0x00)
            /* Method returns Integer */

            Local0 = NOr (Arg2, M601 (0x01, 0x05))
            M600 (Arg0, 0x08, Local0, 0x29AF5D7B)
            Local0 = NOr (Arg2, M601 (0x01, 0x12))
            M600 (Arg0, 0x09, Local0, 0x00)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = NOr (Arg2, DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x0A, Local0, 0x29AF5D7B)
                Local0 = NOr (Arg2, DerefOf (M602 (0x01, 0x12, 0x01)))
                M600 (Arg0, 0x0B, Local0, 0x00)
            }

            NOr (Arg2, 0x00, Local0)
            M600 (Arg0, 0x0C, Local0, 0x29AF5D7B)
            NOr (Arg2, 0xFFFFFFFF, Local0)
            M600 (Arg0, 0x0D, Local0, 0x00)
            NOr (Arg2, AUI5, Local0)
            M600 (Arg0, 0x0E, Local0, 0x29AF5D7B)
            NOr (Arg2, AUII, Local0)
            M600 (Arg0, 0x0F, Local0, 0x00)
            If (Y078)
            {
                NOr (Arg2, DerefOf (RefOf (AUI5)), Local0)
                M600 (Arg0, 0x10, Local0, 0x29AF5D7B)
                NOr (Arg2, DerefOf (RefOf (AUII)), Local0)
                M600 (Arg0, 0x11, Local0, 0x00)
            }

            NOr (Arg2, DerefOf (PAUI [0x05]), Local0)
            M600 (Arg0, 0x12, Local0, 0x29AF5D7B)
            NOr (Arg2, DerefOf (PAUI [0x12]), Local0)
            M600 (Arg0, 0x13, Local0, 0x00)
            /* Method returns Integer */

            NOr (Arg2, M601 (0x01, 0x05), Local0)
            M600 (Arg0, 0x14, Local0, 0x29AF5D7B)
            NOr (Arg2, M601 (0x01, 0x12), Local0)
            M600 (Arg0, 0x15, Local0, 0x00)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                NOr (Arg2, DerefOf (M602 (0x01, 0x05, 0x01)), Local0)
                M600 (Arg0, 0x16, Local0, 0x29AF5D7B)
                NOr (Arg2, DerefOf (M602 (0x01, 0x12, 0x01)), Local0)
                M600 (Arg0, 0x17, Local0, 0x00)
            }

            /* Conversion of the second operand */

            Local0 = NOr (0x00, Arg2)
            M600 (Arg0, 0x18, Local0, 0x29AF5D7B)
            Local0 = NOr (0xFFFFFFFF, Arg2)
            M600 (Arg0, 0x19, Local0, 0x00)
            Local0 = NOr (AUI5, Arg2)
            M600 (Arg0, 0x1A, Local0, 0x29AF5D7B)
            Local0 = NOr (AUII, Arg2)
            M600 (Arg0, 0x1B, Local0, 0x00)
            If (Y078)
            {
                Local0 = NOr (DerefOf (RefOf (AUI5)), Arg2)
                M600 (Arg0, 0x1C, Local0, 0x29AF5D7B)
                Local0 = NOr (DerefOf (RefOf (AUII)), Arg2)
                M600 (Arg0, 0x1D, Local0, 0x00)
            }

            Local0 = NOr (DerefOf (PAUI [0x05]), Arg2)
            M600 (Arg0, 0x1E, Local0, 0x29AF5D7B)
            Local0 = NOr (DerefOf (PAUI [0x12]), Arg2)
            M600 (Arg0, 0x1F, Local0, 0x00)
            /* Method returns Integer */

            Local0 = NOr (M601 (0x01, 0x05), Arg2)
            M600 (Arg0, 0x20, Local0, 0x29AF5D7B)
            Local0 = NOr (M601 (0x01, 0x12), Arg2)
            M600 (Arg0, 0x21, Local0, 0x00)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = NOr (DerefOf (M602 (0x01, 0x05, 0x01)), Arg2)
                M600 (Arg0, 0x22, Local0, 0x29AF5D7B)
                Local0 = NOr (DerefOf (M602 (0x01, 0x12, 0x01)), Arg2)
                M600 (Arg0, 0x23, Local0, 0x00)
            }

            NOr (0x00, Arg2, Local0)
            M600 (Arg0, 0x24, Local0, 0x29AF5D7B)
            NOr (0xFFFFFFFF, Arg2, Local0)
            M600 (Arg0, 0x25, Local0, 0x00)
            NOr (AUI5, Arg2, Local0)
            M600 (Arg0, 0x26, Local0, 0x29AF5D7B)
            NOr (AUII, Arg2, Local0)
            M600 (Arg0, 0x27, Local0, 0x00)
            If (Y078)
            {
                NOr (DerefOf (RefOf (AUI5)), Arg2, Local0)
                M600 (Arg0, 0x28, Local0, 0x29AF5D7B)
                NOr (DerefOf (RefOf (AUII)), Arg2, Local0)
                M600 (Arg0, 0x29, Local0, 0x00)
            }

            NOr (DerefOf (PAUI [0x05]), Arg2, Local0)
            M600 (Arg0, 0x2A, Local0, 0x29AF5D7B)
            NOr (DerefOf (PAUI [0x12]), Arg2, Local0)
            M600 (Arg0, 0x2B, Local0, 0x00)
            /* Method returns Integer */

            NOr (M601 (0x01, 0x05), Arg2, Local0)
            M600 (Arg0, 0x2C, Local0, 0x29AF5D7B)
            NOr (M601 (0x01, 0x12), Arg2, Local0)
            M600 (Arg0, 0x2D, Local0, 0x00)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                NOr (DerefOf (M602 (0x01, 0x05, 0x01)), Arg2, Local0)
                M600 (Arg0, 0x2E, Local0, 0x29AF5D7B)
                NOr (DerefOf (M602 (0x01, 0x12, 0x01)), Arg2, Local0)
                M600 (Arg0, 0x2F, Local0, 0x00)
            }

            /* Conversion of the both operands */

            Local0 = NOr (Arg1, Arg2)
            M600 (Arg0, 0x30, Local0, 0x29AF5C5A)
            Local0 = NOr (Arg2, Arg1)
            M600 (Arg0, 0x31, Local0, 0x29AF5C5A)
            NOr (Arg1, Arg2, Local0)
            M600 (Arg0, 0x32, Local0, 0x29AF5C5A)
            NOr (Arg2, Arg1, Local0)
            M600 (Arg0, 0x33, Local0, 0x29AF5C5A)
        }

        /* Or, common 32-bit/64-bit test */

        Method (M050, 2, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg1 | 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0x0321)
            Store ((Arg1 | 0xFFFFFFFFFFFFFFFF), Local0)
            M600 (Arg0, 0x01, Local0, 0xFFFFFFFFFFFFFFFF)
            Store ((Arg1 | AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0x0321)
            Store ((Arg1 | AUIJ), Local0)
            M600 (Arg0, 0x03, Local0, 0xFFFFFFFFFFFFFFFF)
            If (Y078)
            {
                Store ((Arg1 | DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0x0321)
                Store ((Arg1 | DerefOf (RefOf (AUIJ))), Local0)
                M600 (Arg0, 0x05, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            Store ((Arg1 | DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0x0321)
            Store ((Arg1 | DerefOf (PAUI [0x13])), Local0)
            M600 (Arg0, 0x07, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Integer */

            Store ((Arg1 | M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0x0321)
            Store ((Arg1 | M601 (0x01, 0x13)), Local0)
            M600 (Arg0, 0x09, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg1 | DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0x0321)
                Store ((Arg1 | DerefOf (M602 (0x01, 0x13, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            Local0 = (Arg1 | 0x00)
            M600 (Arg0, 0x0C, Local0, 0x0321)
            Local0 = (Arg1 | 0xFFFFFFFFFFFFFFFF)
            M600 (Arg0, 0x0D, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = (Arg1 | AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0x0321)
            Local0 = (Arg1 | AUIJ) /* \AUIJ */
            M600 (Arg0, 0x0F, Local0, 0xFFFFFFFFFFFFFFFF)
            If (Y078)
            {
                Local0 = (Arg1 | DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0x0321)
                Local0 = (Arg1 | DerefOf (RefOf (AUIJ)))
                M600 (Arg0, 0x11, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            Local0 = (Arg1 | DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0x0321)
            Local0 = (Arg1 | DerefOf (PAUI [0x13]))
            M600 (Arg0, 0x13, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Integer */

            Local0 = (Arg1 | M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0x0321)
            Local0 = (Arg1 | M601 (0x01, 0x13))
            M600 (Arg0, 0x15, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg1 | DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0x0321)
                Local0 = (Arg1 | DerefOf (M602 (0x01, 0x13, 0x01)))
                M600 (Arg0, 0x17, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            /* Conversion of the second operand */

            Store ((0x00 | Arg1), Local0)
            M600 (Arg0, 0x18, Local0, 0x0321)
            Store ((0xFFFFFFFFFFFFFFFF | Arg1), Local0)
            M600 (Arg0, 0x19, Local0, 0xFFFFFFFFFFFFFFFF)
            Store ((AUI5 | Arg1), Local0)
            M600 (Arg0, 0x1A, Local0, 0x0321)
            Store ((AUIJ | Arg1), Local0)
            M600 (Arg0, 0x1B, Local0, 0xFFFFFFFFFFFFFFFF)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) | Arg1), Local0)
                M600 (Arg0, 0x1C, Local0, 0x0321)
                Store ((DerefOf (RefOf (AUIJ)) | Arg1), Local0)
                M600 (Arg0, 0x1D, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            Store ((DerefOf (PAUI [0x05]) | Arg1), Local0)
            M600 (Arg0, 0x1E, Local0, 0x0321)
            Store ((DerefOf (PAUI [0x13]) | Arg1), Local0)
            M600 (Arg0, 0x1F, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) | Arg1), Local0)
            M600 (Arg0, 0x20, Local0, 0x0321)
            Store ((M601 (0x01, 0x13) | Arg1), Local0)
            M600 (Arg0, 0x21, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) | Arg1), Local0)
                M600 (Arg0, 0x22, Local0, 0x0321)
                Store ((DerefOf (M602 (0x01, 0x13, 0x01)) | Arg1), Local0)
                M600 (Arg0, 0x23, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            Local0 = (0x00 | Arg1)
            M600 (Arg0, 0x24, Local0, 0x0321)
            Local0 = (0xFFFFFFFFFFFFFFFF | Arg1)
            M600 (Arg0, 0x25, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = (AUI5 | Arg1)
            M600 (Arg0, 0x26, Local0, 0x0321)
            Local0 = (AUIJ | Arg1)
            M600 (Arg0, 0x27, Local0, 0xFFFFFFFFFFFFFFFF)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) | Arg1)
                M600 (Arg0, 0x28, Local0, 0x0321)
                Local0 = (DerefOf (RefOf (AUIJ)) | Arg1)
                M600 (Arg0, 0x29, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            Local0 = (DerefOf (PAUI [0x05]) | Arg1)
            M600 (Arg0, 0x2A, Local0, 0x0321)
            Local0 = (DerefOf (PAUI [0x13]) | Arg1)
            M600 (Arg0, 0x2B, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) | Arg1)
            M600 (Arg0, 0x2C, Local0, 0x0321)
            Local0 = (M601 (0x01, 0x13) | Arg1)
            M600 (Arg0, 0x2D, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) | Arg1)
                M600 (Arg0, 0x2E, Local0, 0x0321)
                Local0 = (DerefOf (M602 (0x01, 0x13, 0x01)) | Arg1)
                M600 (Arg0, 0x2F, Local0, 0xFFFFFFFFFFFFFFFF)
            }
        }

        /* Or, 64-bit */

        Method (M051, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 | 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 | 0xFFFFFFFFFFFFFFFF), Local0)
            M600 (Arg0, 0x01, Local0, 0xFFFFFFFFFFFFFFFF)
            Store ((Arg2 | AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 | AUIJ), Local0)
            M600 (Arg0, 0x03, Local0, 0xFFFFFFFFFFFFFFFF)
            If (Y078)
            {
                Store ((Arg2 | DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 | DerefOf (RefOf (AUIJ))), Local0)
                M600 (Arg0, 0x05, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            Store ((Arg2 | DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 | DerefOf (PAUI [0x13])), Local0)
            M600 (Arg0, 0x07, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Integer */

            Store ((Arg2 | M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 | M601 (0x01, 0x13)), Local0)
            M600 (Arg0, 0x09, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 | DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 | DerefOf (M602 (0x01, 0x13, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            Local0 = (Arg2 | 0x00)
            M600 (Arg0, 0x0C, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 | 0xFFFFFFFFFFFFFFFF)
            M600 (Arg0, 0x0D, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = (Arg2 | AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 | AUIJ) /* \AUIJ */
            M600 (Arg0, 0x0F, Local0, 0xFFFFFFFFFFFFFFFF)
            If (Y078)
            {
                Local0 = (Arg2 | DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0xFE7CB391D650A284)
                Local0 = (Arg2 | DerefOf (RefOf (AUIJ)))
                M600 (Arg0, 0x11, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            Local0 = (Arg2 | DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 | DerefOf (PAUI [0x13]))
            M600 (Arg0, 0x13, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Integer */

            Local0 = (Arg2 | M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 | M601 (0x01, 0x13))
            M600 (Arg0, 0x15, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 | DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0xFE7CB391D650A284)
                Local0 = (Arg2 | DerefOf (M602 (0x01, 0x13, 0x01)))
                M600 (Arg0, 0x17, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            /* Conversion of the second operand */

            Store ((0x00 | Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0xFE7CB391D650A284)
            Store ((0xFFFFFFFFFFFFFFFF | Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0xFFFFFFFFFFFFFFFF)
            Store ((AUI5 | Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0xFE7CB391D650A284)
            Store ((AUIJ | Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0xFFFFFFFFFFFFFFFF)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) | Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0xFE7CB391D650A284)
                Store ((DerefOf (RefOf (AUIJ)) | Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            Store ((DerefOf (PAUI [0x05]) | Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0xFE7CB391D650A284)
            Store ((DerefOf (PAUI [0x13]) | Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) | Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0xFE7CB391D650A284)
            Store ((M601 (0x01, 0x13) | Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) | Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0xFE7CB391D650A284)
                Store ((DerefOf (M602 (0x01, 0x13, 0x01)) | Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            Local0 = (0x00 | Arg2)
            M600 (Arg0, 0x24, Local0, 0xFE7CB391D650A284)
            Local0 = (0xFFFFFFFFFFFFFFFF | Arg2)
            M600 (Arg0, 0x25, Local0, 0xFFFFFFFFFFFFFFFF)
            Local0 = (AUI5 | Arg2)
            M600 (Arg0, 0x26, Local0, 0xFE7CB391D650A284)
            Local0 = (AUIJ | Arg2)
            M600 (Arg0, 0x27, Local0, 0xFFFFFFFFFFFFFFFF)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) | Arg2)
                M600 (Arg0, 0x28, Local0, 0xFE7CB391D650A284)
                Local0 = (DerefOf (RefOf (AUIJ)) | Arg2)
                M600 (Arg0, 0x29, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            Local0 = (DerefOf (PAUI [0x05]) | Arg2)
            M600 (Arg0, 0x2A, Local0, 0xFE7CB391D650A284)
            Local0 = (DerefOf (PAUI [0x13]) | Arg2)
            M600 (Arg0, 0x2B, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) | Arg2)
            M600 (Arg0, 0x2C, Local0, 0xFE7CB391D650A284)
            Local0 = (M601 (0x01, 0x13) | Arg2)
            M600 (Arg0, 0x2D, Local0, 0xFFFFFFFFFFFFFFFF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) | Arg2)
                M600 (Arg0, 0x2E, Local0, 0xFE7CB391D650A284)
                Local0 = (DerefOf (M602 (0x01, 0x13, 0x01)) | Arg2)
                M600 (Arg0, 0x2F, Local0, 0xFFFFFFFFFFFFFFFF)
            }

            /* Conversion of the both operands */

            Store ((Arg1 | Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0xFE7CB391D650A3A5)
            Store ((Arg2 | Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0xFE7CB391D650A3A5)
            Local0 = (Arg1 | Arg2)
            M600 (Arg0, 0x32, Local0, 0xFE7CB391D650A3A5)
            Local0 = (Arg2 | Arg1)
            M600 (Arg0, 0x33, Local0, 0xFE7CB391D650A3A5)
        }

        /* Or, 32-bit */

        Method (M052, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 | 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0xD650A284)
            Store ((Arg2 | 0xFFFFFFFF), Local0)
            M600 (Arg0, 0x01, Local0, 0xFFFFFFFF)
            Store ((Arg2 | AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0xD650A284)
            Store ((Arg2 | AUII), Local0)
            M600 (Arg0, 0x03, Local0, 0xFFFFFFFF)
            If (Y078)
            {
                Store ((Arg2 | DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0xD650A284)
                Store ((Arg2 | DerefOf (RefOf (AUII))), Local0)
                M600 (Arg0, 0x05, Local0, 0xFFFFFFFF)
            }

            Store ((Arg2 | DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0xD650A284)
            Store ((Arg2 | DerefOf (PAUI [0x12])), Local0)
            M600 (Arg0, 0x07, Local0, 0xFFFFFFFF)
            /* Method returns Integer */

            Store ((Arg2 | M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0xD650A284)
            Store ((Arg2 | M601 (0x01, 0x12)), Local0)
            M600 (Arg0, 0x09, Local0, 0xFFFFFFFF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 | DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xD650A284)
                Store ((Arg2 | DerefOf (M602 (0x01, 0x12, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0xFFFFFFFF)
            }

            Local0 = (Arg2 | 0x00)
            M600 (Arg0, 0x0C, Local0, 0xD650A284)
            Local0 = (Arg2 | 0xFFFFFFFF)
            M600 (Arg0, 0x0D, Local0, 0xFFFFFFFF)
            Local0 = (Arg2 | AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0xD650A284)
            Local0 = (Arg2 | AUII) /* \AUII */
            M600 (Arg0, 0x0F, Local0, 0xFFFFFFFF)
            If (Y078)
            {
                Local0 = (Arg2 | DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0xD650A284)
                Local0 = (Arg2 | DerefOf (RefOf (AUII)))
                M600 (Arg0, 0x11, Local0, 0xFFFFFFFF)
            }

            Local0 = (Arg2 | DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0xD650A284)
            Local0 = (Arg2 | DerefOf (PAUI [0x12]))
            M600 (Arg0, 0x13, Local0, 0xFFFFFFFF)
            /* Method returns Integer */

            Local0 = (Arg2 | M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0xD650A284)
            Local0 = (Arg2 | M601 (0x01, 0x12))
            M600 (Arg0, 0x15, Local0, 0xFFFFFFFF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 | DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0xD650A284)
                Local0 = (Arg2 | DerefOf (M602 (0x01, 0x12, 0x01)))
                M600 (Arg0, 0x17, Local0, 0xFFFFFFFF)
            }

            /* Conversion of the second operand */

            Store ((0x00 | Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0xD650A284)
            Store ((0xFFFFFFFF | Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0xFFFFFFFF)
            Store ((AUI5 | Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0xD650A284)
            Store ((AUII | Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0xFFFFFFFF)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) | Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0xD650A284)
                Store ((DerefOf (RefOf (AUII)) | Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0xFFFFFFFF)
            }

            Store ((DerefOf (PAUI [0x05]) | Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0xD650A284)
            Store ((DerefOf (PAUI [0x12]) | Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0xFFFFFFFF)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) | Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0xD650A284)
            Store ((M601 (0x01, 0x12) | Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0xFFFFFFFF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) | Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0xD650A284)
                Store ((DerefOf (M602 (0x01, 0x12, 0x01)) | Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0xFFFFFFFF)
            }

            Local0 = (0x00 | Arg2)
            M600 (Arg0, 0x24, Local0, 0xD650A284)
            Local0 = (0xFFFFFFFF | Arg2)
            M600 (Arg0, 0x25, Local0, 0xFFFFFFFF)
            Local0 = (AUI5 | Arg2)
            M600 (Arg0, 0x26, Local0, 0xD650A284)
            Local0 = (AUII | Arg2)
            M600 (Arg0, 0x27, Local0, 0xFFFFFFFF)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) | Arg2)
                M600 (Arg0, 0x28, Local0, 0xD650A284)
                Local0 = (DerefOf (RefOf (AUII)) | Arg2)
                M600 (Arg0, 0x29, Local0, 0xFFFFFFFF)
            }

            Local0 = (DerefOf (PAUI [0x05]) | Arg2)
            M600 (Arg0, 0x2A, Local0, 0xD650A284)
            Local0 = (DerefOf (PAUI [0x12]) | Arg2)
            M600 (Arg0, 0x2B, Local0, 0xFFFFFFFF)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) | Arg2)
            M600 (Arg0, 0x2C, Local0, 0xD650A284)
            Local0 = (M601 (0x01, 0x12) | Arg2)
            M600 (Arg0, 0x2D, Local0, 0xFFFFFFFF)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) | Arg2)
                M600 (Arg0, 0x2E, Local0, 0xD650A284)
                Local0 = (DerefOf (M602 (0x01, 0x12, 0x01)) | Arg2)
                M600 (Arg0, 0x2F, Local0, 0xFFFFFFFF)
            }

            /* Conversion of the both operands */

            Store ((Arg1 | Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0xD650A3A5)
            Store ((Arg2 | Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0xD650A3A5)
            Local0 = (Arg1 | Arg2)
            M600 (Arg0, 0x32, Local0, 0xD650A3A5)
            Local0 = (Arg2 | Arg1)
            M600 (Arg0, 0x33, Local0, 0xD650A3A5)
        }

        /* ShiftLeft, common 32-bit/64-bit test */

        Method (M053, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg1 << 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0x0321)
            Store ((Arg1 << 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0x0642)
            Store ((Arg1 << AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0x0321)
            Store ((Arg1 << AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0x0642)
            If (Y078)
            {
                Store ((Arg1 << DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0x0321)
                Store ((Arg1 << DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0x0642)
            }

            Store ((Arg1 << DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0x0321)
            Store ((Arg1 << DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0x0642)
            /* Method returns Integer */

            Store ((Arg1 << M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0x0321)
            Store ((Arg1 << M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0x0642)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg1 << DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0x0321)
                Store ((Arg1 << DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x0642)
            }

            Local0 = (Arg1 << 0x00)
            M600 (Arg0, 0x0C, Local0, 0x0321)
            Local0 = (Arg1 << 0x01)
            M600 (Arg0, 0x0D, Local0, 0x0642)
            Local0 = (Arg1 << AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0x0321)
            Local0 = (Arg1 << AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0x0642)
            If (Y078)
            {
                Local0 = (Arg1 << DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0x0321)
                Local0 = (Arg1 << DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0x0642)
            }

            Local0 = (Arg1 << DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0x0321)
            Local0 = (Arg1 << DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0x0642)
            /* Method returns Integer */

            Local0 = (Arg1 << M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0x0321)
            Local0 = (Arg1 << M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0x0642)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg1 << DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0x0321)
                Local0 = (Arg1 << DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0x0642)
            }

            /* Conversion of the second operand */

            Store ((0x00 << Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0x01 << Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0x0800)
            Store ((AUI5 << Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUI6 << Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0x0800)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) << Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUI6)) << Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0x0800)
            }

            Store ((DerefOf (PAUI [0x05]) << Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x06]) << Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0x0800)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) << Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x06) << Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0x0800)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) << Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) << Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0x0800)
            }

            Local0 = (0x00 << Arg2)
            M600 (Arg0, 0x24, Local0, 0x00)
            Local0 = (0x01 << Arg2)
            M600 (Arg0, 0x25, Local0, 0x0800)
            Local0 = (AUI5 << Arg2)
            M600 (Arg0, 0x26, Local0, 0x00)
            Local0 = (AUI6 << Arg2)
            M600 (Arg0, 0x27, Local0, 0x0800)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) << Arg2)
                M600 (Arg0, 0x28, Local0, 0x00)
                Local0 = (DerefOf (RefOf (AUI6)) << Arg2)
                M600 (Arg0, 0x29, Local0, 0x0800)
            }

            Local0 = (DerefOf (PAUI [0x05]) << Arg2)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Local0 = (DerefOf (PAUI [0x06]) << Arg2)
            M600 (Arg0, 0x2B, Local0, 0x0800)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) << Arg2)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Local0 = (M601 (0x01, 0x06) << Arg2)
            M600 (Arg0, 0x2D, Local0, 0x0800)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) << Arg2)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) << Arg2)
                M600 (Arg0, 0x2F, Local0, 0x0800)
            }
        }

        /* ShiftLeft, 64-bit */

        Method (M054, 4, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 << 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 << 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0xFCF96723ACA14508)
            Store ((Arg2 << AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 << AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0xFCF96723ACA14508)
            If (Y078)
            {
                Store ((Arg2 << DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 << DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0xFCF96723ACA14508)
            }

            Store ((Arg2 << DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 << DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0xFCF96723ACA14508)
            /* Method returns Integer */

            Store ((Arg2 << M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 << M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0xFCF96723ACA14508)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 << DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 << DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0xFCF96723ACA14508)
            }

            Local0 = (Arg2 << 0x00)
            M600 (Arg0, 0x0C, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 << 0x01)
            M600 (Arg0, 0x0D, Local0, 0xFCF96723ACA14508)
            Local0 = (Arg2 << AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 << AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0xFCF96723ACA14508)
            If (Y078)
            {
                Local0 = (Arg2 << DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0xFE7CB391D650A284)
                Local0 = (Arg2 << DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0xFCF96723ACA14508)
            }

            Local0 = (Arg2 << DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 << DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0xFCF96723ACA14508)
            /* Method returns Integer */

            Local0 = (Arg2 << M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 << M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0xFCF96723ACA14508)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 << DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0xFE7CB391D650A284)
                Local0 = (Arg2 << DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0xFCF96723ACA14508)
            }

            /* Conversion of the second operand */

            Store ((0x00 << Arg3), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0x01 << Arg3), Local0)
            M600 (Arg0, 0x19, Local0, 0x0800)
            Store ((AUI5 << Arg3), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUI6 << Arg3), Local0)
            M600 (Arg0, 0x1B, Local0, 0x0800)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) << Arg3), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUI6)) << Arg3), Local0)
                M600 (Arg0, 0x1D, Local0, 0x0800)
            }

            Store ((DerefOf (PAUI [0x05]) << Arg3), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x06]) << Arg3), Local0)
            M600 (Arg0, 0x1F, Local0, 0x0800)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) << Arg3), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x06) << Arg3), Local0)
            M600 (Arg0, 0x21, Local0, 0x0800)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) << Arg3), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) << Arg3), Local0)
                M600 (Arg0, 0x23, Local0, 0x0800)
            }

            Local0 = (0x00 << Arg3)
            M600 (Arg0, 0x24, Local0, 0x00)
            Local0 = (0x01 << Arg3)
            M600 (Arg0, 0x25, Local0, 0x0800)
            Local0 = (AUI5 << Arg3)
            M600 (Arg0, 0x26, Local0, 0x00)
            Local0 = (AUI6 << Arg3)
            M600 (Arg0, 0x27, Local0, 0x0800)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) << Arg3)
                M600 (Arg0, 0x28, Local0, 0x00)
                Local0 = (DerefOf (RefOf (AUI6)) << Arg3)
                M600 (Arg0, 0x29, Local0, 0x0800)
            }

            Local0 = (DerefOf (PAUI [0x05]) << Arg3)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Local0 = (DerefOf (PAUI [0x06]) << Arg3)
            M600 (Arg0, 0x2B, Local0, 0x0800)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) << Arg3)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Local0 = (M601 (0x01, 0x06) << Arg3)
            M600 (Arg0, 0x2D, Local0, 0x0800)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) << Arg3)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) << Arg3)
                M600 (Arg0, 0x2F, Local0, 0x0800)
            }

            /* Conversion of the both operands */

            Store ((Arg1 << Arg3), Local0)
            M600 (Arg0, 0x30, Local0, 0x00190800)
            Store ((Arg2 << Arg3), Local0)
            M600 (Arg0, 0x31, Local0, 0xE59C8EB285142000)
            Local0 = (Arg1 << Arg3)
            M600 (Arg0, 0x32, Local0, 0x00190800)
            Local0 = (Arg2 << Arg3)
            M600 (Arg0, 0x33, Local0, 0xE59C8EB285142000)
        }

        /* ShiftLeft, 32-bit */

        Method (M055, 4, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 << 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0xD650A284)
            Store ((Arg2 << 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0xACA14508)
            Store ((Arg2 << AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0xD650A284)
            Store ((Arg2 << AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0xACA14508)
            If (Y078)
            {
                Store ((Arg2 << DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0xD650A284)
                Store ((Arg2 << DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0xACA14508)
            }

            Store ((Arg2 << DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0xD650A284)
            Store ((Arg2 << DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0xACA14508)
            /* Method returns Integer */

            Store ((Arg2 << M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0xD650A284)
            Store ((Arg2 << M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0xACA14508)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 << DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xD650A284)
                Store ((Arg2 << DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0xACA14508)
            }

            Local0 = (Arg2 << 0x00)
            M600 (Arg0, 0x0C, Local0, 0xD650A284)
            Local0 = (Arg2 << 0x01)
            M600 (Arg0, 0x0D, Local0, 0xACA14508)
            Local0 = (Arg2 << AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0xD650A284)
            Local0 = (Arg2 << AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0xACA14508)
            If (Y078)
            {
                Local0 = (Arg2 << DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0xD650A284)
                Local0 = (Arg2 << DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0xACA14508)
            }

            Local0 = (Arg2 << DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0xD650A284)
            Local0 = (Arg2 << DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0xACA14508)
            /* Method returns Integer */

            Local0 = (Arg2 << M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0xD650A284)
            Local0 = (Arg2 << M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0xACA14508)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 << DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0xD650A284)
                Local0 = (Arg2 << DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0xACA14508)
            }

            /* Conversion of the second operand */

            Store ((0x00 << Arg3), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0x01 << Arg3), Local0)
            M600 (Arg0, 0x19, Local0, 0x0800)
            Store ((AUI5 << Arg3), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUI6 << Arg3), Local0)
            M600 (Arg0, 0x1B, Local0, 0x0800)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) << Arg3), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUI6)) << Arg3), Local0)
                M600 (Arg0, 0x1D, Local0, 0x0800)
            }

            Store ((DerefOf (PAUI [0x05]) << Arg3), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x06]) << Arg3), Local0)
            M600 (Arg0, 0x1F, Local0, 0x0800)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) << Arg3), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x06) << Arg3), Local0)
            M600 (Arg0, 0x21, Local0, 0x0800)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) << Arg3), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) << Arg3), Local0)
                M600 (Arg0, 0x23, Local0, 0x0800)
            }

            Local0 = (0x00 << Arg3)
            M600 (Arg0, 0x24, Local0, 0x00)
            Local0 = (0x01 << Arg3)
            M600 (Arg0, 0x25, Local0, 0x0800)
            Local0 = (AUI5 << Arg3)
            M600 (Arg0, 0x26, Local0, 0x00)
            Local0 = (AUI6 << Arg3)
            M600 (Arg0, 0x27, Local0, 0x0800)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) << Arg3)
                M600 (Arg0, 0x28, Local0, 0x00)
                Local0 = (DerefOf (RefOf (AUI6)) << Arg3)
                M600 (Arg0, 0x29, Local0, 0x0800)
            }

            Local0 = (DerefOf (PAUI [0x05]) << Arg3)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Local0 = (DerefOf (PAUI [0x06]) << Arg3)
            M600 (Arg0, 0x2B, Local0, 0x0800)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) << Arg3)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Local0 = (M601 (0x01, 0x06) << Arg3)
            M600 (Arg0, 0x2D, Local0, 0x0800)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) << Arg3)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) << Arg3)
                M600 (Arg0, 0x2F, Local0, 0x0800)
            }

            /* Conversion of the both operands */

            Store ((Arg1 << Arg3), Local0)
            M600 (Arg0, 0x30, Local0, 0x00190800)
            Store ((Arg2 << Arg3), Local0)
            M600 (Arg0, 0x31, Local0, 0x85142000)
            Local0 = (Arg1 << Arg3)
            M600 (Arg0, 0x32, Local0, 0x00190800)
            Local0 = (Arg2 << Arg3)
            M600 (Arg0, 0x33, Local0, 0x85142000)
        }

        /* ShiftRight, common 32-bit/64-bit test */

        Method (M056, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg1 >> 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0x0321)
            Store ((Arg1 >> 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0x0190)
            Store ((Arg1 >> AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0x0321)
            Store ((Arg1 >> AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0x0190)
            If (Y078)
            {
                Store ((Arg1 >> DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0x0321)
                Store ((Arg1 >> DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0x0190)
            }

            Store ((Arg1 >> DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0x0321)
            Store ((Arg1 >> DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0x0190)
            /* Method returns Integer */

            Store ((Arg1 >> M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0x0321)
            Store ((Arg1 >> M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0x0190)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg1 >> DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0x0321)
                Store ((Arg1 >> DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x0190)
            }

            Local0 = (Arg1 >> 0x00)
            M600 (Arg0, 0x0C, Local0, 0x0321)
            Local0 = (Arg1 >> 0x01)
            M600 (Arg0, 0x0D, Local0, 0x0190)
            Local0 = (Arg1 >> AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0x0321)
            Local0 = (Arg1 >> AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0x0190)
            If (Y078)
            {
                Local0 = (Arg1 >> DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0x0321)
                Local0 = (Arg1 >> DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0x0190)
            }

            Local0 = (Arg1 >> DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0x0321)
            Local0 = (Arg1 >> DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0x0190)
            /* Method returns Integer */

            Local0 = (Arg1 >> M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0x0321)
            Local0 = (Arg1 >> M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0x0190)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg1 >> DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0x0321)
                Local0 = (Arg1 >> DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0x0190)
            }

            /* Conversion of the second operand */

            Store ((0x0321 >> Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0xD650A284 >> Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0x001ACA14)
            Store ((AUI1 >> Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUIK >> Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0x001ACA14)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI1)) >> Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUIK)) >> Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0x001ACA14)
            }

            Store ((DerefOf (PAUI [0x01]) >> Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x14]) >> Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0x001ACA14)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x01) >> Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x14) >> Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0x001ACA14)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x01, 0x01)) >> Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x14, 0x01)) >> Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0x001ACA14)
            }

            Local0 = (0x0321 >> Arg2)
            M600 (Arg0, 0x24, Local0, 0x00)
            Local0 = (0xD650A284 >> Arg2)
            M600 (Arg0, 0x25, Local0, 0x001ACA14)
            Local0 = (AUI1 >> Arg2)
            M600 (Arg0, 0x26, Local0, 0x00)
            Local0 = (AUIK >> Arg2)
            M600 (Arg0, 0x27, Local0, 0x001ACA14)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI1)) >> Arg2)
                M600 (Arg0, 0x28, Local0, 0x00)
                Local0 = (DerefOf (RefOf (AUIK)) >> Arg2)
                M600 (Arg0, 0x29, Local0, 0x001ACA14)
            }

            Local0 = (DerefOf (PAUI [0x01]) >> Arg2)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Local0 = (DerefOf (PAUI [0x14]) >> Arg2)
            M600 (Arg0, 0x2B, Local0, 0x001ACA14)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x01) >> Arg2)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Local0 = (M601 (0x01, 0x14) >> Arg2)
            M600 (Arg0, 0x2D, Local0, 0x001ACA14)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x01, 0x01)) >> Arg2)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Local0 = (DerefOf (M602 (0x01, 0x14, 0x01)) >> Arg2)
                M600 (Arg0, 0x2F, Local0, 0x001ACA14)
            }
        }

        /* ShiftRight, 64-bit */

        Method (M057, 4, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 >> 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 >> 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0x7F3E59C8EB285142)
            Store ((Arg2 >> AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 >> AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0x7F3E59C8EB285142)
            If (Y078)
            {
                Store ((Arg2 >> DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 >> DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0x7F3E59C8EB285142)
            }

            Store ((Arg2 >> DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 >> DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0x7F3E59C8EB285142)
            /* Method returns Integer */

            Store ((Arg2 >> M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 >> M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0x7F3E59C8EB285142)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 >> DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 >> DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x7F3E59C8EB285142)
            }

            Local0 = (Arg2 >> 0x00)
            M600 (Arg0, 0x0C, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 >> 0x01)
            M600 (Arg0, 0x0D, Local0, 0x7F3E59C8EB285142)
            Local0 = (Arg2 >> AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 >> AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0x7F3E59C8EB285142)
            If (Y078)
            {
                Local0 = (Arg2 >> DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0xFE7CB391D650A284)
                Local0 = (Arg2 >> DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0x7F3E59C8EB285142)
            }

            Local0 = (Arg2 >> DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 >> DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0x7F3E59C8EB285142)
            /* Method returns Integer */

            Local0 = (Arg2 >> M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 >> M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0x7F3E59C8EB285142)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 >> DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0xFE7CB391D650A284)
                Local0 = (Arg2 >> DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0x7F3E59C8EB285142)
            }

            /* Conversion of the second operand */

            Store ((0x0321 >> Arg3), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0xFE7CB391D650A284 >> Arg3), Local0)
            M600 (Arg0, 0x19, Local0, 0x001FCF96723ACA14)
            Store ((AUI1 >> Arg3), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUI4 >> Arg3), Local0)
            M600 (Arg0, 0x1B, Local0, 0x001FCF96723ACA14)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI1)) >> Arg3), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUI4)) >> Arg3), Local0)
                M600 (Arg0, 0x1D, Local0, 0x001FCF96723ACA14)
            }

            Store ((DerefOf (PAUI [0x01]) >> Arg3), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x04]) >> Arg3), Local0)
            M600 (Arg0, 0x1F, Local0, 0x001FCF96723ACA14)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x01) >> Arg3), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x04) >> Arg3), Local0)
            M600 (Arg0, 0x21, Local0, 0x001FCF96723ACA14)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x01, 0x01)) >> Arg3), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x04, 0x01)) >> Arg3), Local0)
                M600 (Arg0, 0x23, Local0, 0x001FCF96723ACA14)
            }

            Local0 = (0x0321 >> Arg3)
            M600 (Arg0, 0x24, Local0, 0x00)
            Local0 = (0xFE7CB391D650A284 >> Arg3)
            M600 (Arg0, 0x25, Local0, 0x001FCF96723ACA14)
            Local0 = (AUI1 >> Arg3)
            M600 (Arg0, 0x26, Local0, 0x00)
            Local0 = (AUI4 >> Arg3)
            M600 (Arg0, 0x27, Local0, 0x001FCF96723ACA14)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI1)) >> Arg3)
                M600 (Arg0, 0x28, Local0, 0x00)
                Local0 = (DerefOf (RefOf (AUI4)) >> Arg3)
                M600 (Arg0, 0x29, Local0, 0x001FCF96723ACA14)
            }

            Local0 = (DerefOf (PAUI [0x01]) >> Arg3)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Local0 = (DerefOf (PAUI [0x04]) >> Arg3)
            M600 (Arg0, 0x2B, Local0, 0x001FCF96723ACA14)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x01) >> Arg3)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Local0 = (M601 (0x01, 0x04) >> Arg3)
            M600 (Arg0, 0x2D, Local0, 0x001FCF96723ACA14)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x01, 0x01)) >> Arg3)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Local0 = (DerefOf (M602 (0x01, 0x04, 0x01)) >> Arg3)
                M600 (Arg0, 0x2F, Local0, 0x001FCF96723ACA14)
            }

            /* Conversion of the both operands */

            Store ((Arg1 >> Arg3), Local0)
            M600 (Arg0, 0x30, Local0, 0x00)
            Store ((Arg2 >> Arg3), Local0)
            M600 (Arg0, 0x31, Local0, 0x001FCF96723ACA14)
            Local0 = (Arg1 >> Arg3)
            M600 (Arg0, 0x32, Local0, 0x00)
            Local0 = (Arg2 >> Arg3)
            M600 (Arg0, 0x33, Local0, 0x001FCF96723ACA14)
        }

        /* ShiftRight, 32-bit */

        Method (M058, 4, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 >> 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0xD650A284)
            Store ((Arg2 >> 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0x6B285142)
            Store ((Arg2 >> AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0xD650A284)
            Store ((Arg2 >> AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0x6B285142)
            If (Y078)
            {
                Store ((Arg2 >> DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0xD650A284)
                Store ((Arg2 >> DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0x6B285142)
            }

            Store ((Arg2 >> DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0xD650A284)
            Store ((Arg2 >> DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0x6B285142)
            /* Method returns Integer */

            Store ((Arg2 >> M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0xD650A284)
            Store ((Arg2 >> M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0x6B285142)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 >> DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xD650A284)
                Store ((Arg2 >> DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x6B285142)
            }

            Local0 = (Arg2 >> 0x00)
            M600 (Arg0, 0x0C, Local0, 0xD650A284)
            Local0 = (Arg2 >> 0x01)
            M600 (Arg0, 0x0D, Local0, 0x6B285142)
            Local0 = (Arg2 >> AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0xD650A284)
            Local0 = (Arg2 >> AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0x6B285142)
            If (Y078)
            {
                Local0 = (Arg2 >> DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0xD650A284)
                Local0 = (Arg2 >> DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0x6B285142)
            }

            Local0 = (Arg2 >> DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0xD650A284)
            Local0 = (Arg2 >> DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0x6B285142)
            /* Method returns Integer */

            Local0 = (Arg2 >> M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0xD650A284)
            Local0 = (Arg2 >> M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0x6B285142)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 >> DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0xD650A284)
                Local0 = (Arg2 >> DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0x6B285142)
            }

            /* Conversion of the second operand */

            Store ((0x0321 >> Arg3), Local0)
            M600 (Arg0, 0x18, Local0, 0x00)
            Store ((0xD650A284 >> Arg3), Local0)
            M600 (Arg0, 0x19, Local0, 0x001ACA14)
            Store ((AUI1 >> Arg3), Local0)
            M600 (Arg0, 0x1A, Local0, 0x00)
            Store ((AUIK >> Arg3), Local0)
            M600 (Arg0, 0x1B, Local0, 0x001ACA14)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI1)) >> Arg3), Local0)
                M600 (Arg0, 0x1C, Local0, 0x00)
                Store ((DerefOf (RefOf (AUIK)) >> Arg3), Local0)
                M600 (Arg0, 0x1D, Local0, 0x001ACA14)
            }

            Store ((DerefOf (PAUI [0x01]) >> Arg3), Local0)
            M600 (Arg0, 0x1E, Local0, 0x00)
            Store ((DerefOf (PAUI [0x14]) >> Arg3), Local0)
            M600 (Arg0, 0x1F, Local0, 0x001ACA14)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x01) >> Arg3), Local0)
            M600 (Arg0, 0x20, Local0, 0x00)
            Store ((M601 (0x01, 0x14) >> Arg3), Local0)
            M600 (Arg0, 0x21, Local0, 0x001ACA14)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x01, 0x01)) >> Arg3), Local0)
                M600 (Arg0, 0x22, Local0, 0x00)
                Store ((DerefOf (M602 (0x01, 0x14, 0x01)) >> Arg3), Local0)
                M600 (Arg0, 0x23, Local0, 0x001ACA14)
            }

            Local0 = (0x0321 >> Arg3)
            M600 (Arg0, 0x24, Local0, 0x00)
            Local0 = (0xD650A284 >> Arg3)
            M600 (Arg0, 0x25, Local0, 0x001ACA14)
            Local0 = (AUI1 >> Arg3)
            M600 (Arg0, 0x26, Local0, 0x00)
            Local0 = (AUIK >> Arg3)
            M600 (Arg0, 0x27, Local0, 0x001ACA14)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI1)) >> Arg3)
                M600 (Arg0, 0x28, Local0, 0x00)
                Local0 = (DerefOf (RefOf (AUIK)) >> Arg3)
                M600 (Arg0, 0x29, Local0, 0x001ACA14)
            }

            Local0 = (DerefOf (PAUI [0x01]) >> Arg3)
            M600 (Arg0, 0x2A, Local0, 0x00)
            Local0 = (DerefOf (PAUI [0x14]) >> Arg3)
            M600 (Arg0, 0x2B, Local0, 0x001ACA14)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x01) >> Arg3)
            M600 (Arg0, 0x2C, Local0, 0x00)
            Local0 = (M601 (0x01, 0x14) >> Arg3)
            M600 (Arg0, 0x2D, Local0, 0x001ACA14)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x01, 0x01)) >> Arg3)
                M600 (Arg0, 0x2E, Local0, 0x00)
                Local0 = (DerefOf (M602 (0x01, 0x14, 0x01)) >> Arg3)
                M600 (Arg0, 0x2F, Local0, 0x001ACA14)
            }

            /* Conversion of the both operands */

            Store ((Arg1 >> Arg3), Local0)
            M600 (Arg0, 0x30, Local0, 0x00)
            Store ((Arg2 >> Arg3), Local0)
            M600 (Arg0, 0x31, Local0, 0x001ACA14)
            Local0 = (Arg1 >> Arg3)
            M600 (Arg0, 0x32, Local0, 0x00)
            Local0 = (Arg2 >> Arg3)
            M600 (Arg0, 0x33, Local0, 0x001ACA14)
        }

        /* Subtract, common 32-bit/64-bit test */

        Method (M059, 2, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg1 - 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0x0321)
            Store ((Arg1 - 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0x0320)
            Store ((Arg1 - AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0x0321)
            Store ((Arg1 - AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0x0320)
            If (Y078)
            {
                Store ((Arg1 - DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0x0321)
                Store ((Arg1 - DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0x0320)
            }

            Store ((Arg1 - DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0x0321)
            Store ((Arg1 - DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0x0320)
            /* Method returns Integer */

            Store ((Arg1 - M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0x0321)
            Store ((Arg1 - M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0x0320)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg1 - DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0x0321)
                Store ((Arg1 - DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x0320)
            }

            Local0 = (Arg1 - 0x00)
            M600 (Arg0, 0x0C, Local0, 0x0321)
            Local0 = (Arg1 - 0x01)
            M600 (Arg0, 0x0D, Local0, 0x0320)
            Local0 = (Arg1 - AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0x0321)
            Local0 = (Arg1 - AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0x0320)
            If (Y078)
            {
                Local0 = (Arg1 - DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0x0321)
                Local0 = (Arg1 - DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0x0320)
            }

            Local0 = (Arg1 - DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0x0321)
            Local0 = (Arg1 - DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0x0320)
            /* Method returns Integer */

            Local0 = (Arg1 - M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0x0321)
            Local0 = (Arg1 - M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0x0320)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg1 - DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0x0321)
                Local0 = (Arg1 - DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0x0320)
            }

            /* Conversion of the second operand */

            Store ((0x00 - Arg1), Local0)
            M600 (Arg0, 0x18, Local0, 0xFFFFFFFFFFFFFCDF)
            Store ((0x01 - Arg1), Local0)
            M600 (Arg0, 0x19, Local0, 0xFFFFFFFFFFFFFCE0)
            Store ((AUI5 - Arg1), Local0)
            M600 (Arg0, 0x1A, Local0, 0xFFFFFFFFFFFFFCDF)
            Store ((AUI6 - Arg1), Local0)
            M600 (Arg0, 0x1B, Local0, 0xFFFFFFFFFFFFFCE0)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) - Arg1), Local0)
                M600 (Arg0, 0x1C, Local0, 0xFFFFFFFFFFFFFCDF)
                Store ((DerefOf (RefOf (AUI6)) - Arg1), Local0)
                M600 (Arg0, 0x1D, Local0, 0xFFFFFFFFFFFFFCE0)
            }

            Store ((DerefOf (PAUI [0x05]) - Arg1), Local0)
            M600 (Arg0, 0x1E, Local0, 0xFFFFFFFFFFFFFCDF)
            Store ((DerefOf (PAUI [0x06]) - Arg1), Local0)
            M600 (Arg0, 0x1F, Local0, 0xFFFFFFFFFFFFFCE0)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) - Arg1), Local0)
            M600 (Arg0, 0x20, Local0, 0xFFFFFFFFFFFFFCDF)
            Store ((M601 (0x01, 0x06) - Arg1), Local0)
            M600 (Arg0, 0x21, Local0, 0xFFFFFFFFFFFFFCE0)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) - Arg1), Local0)
                M600 (Arg0, 0x22, Local0, 0xFFFFFFFFFFFFFCDF)
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) - Arg1), Local0)
                M600 (Arg0, 0x23, Local0, 0xFFFFFFFFFFFFFCE0)
            }

            Local0 = (0x00 - Arg1)
            M600 (Arg0, 0x24, Local0, 0xFFFFFFFFFFFFFCDF)
            Local0 = (0x01 - Arg1)
            M600 (Arg0, 0x25, Local0, 0xFFFFFFFFFFFFFCE0)
            Local0 = (AUI5 - Arg1)
            M600 (Arg0, 0x26, Local0, 0xFFFFFFFFFFFFFCDF)
            Local0 = (AUI6 - Arg1)
            M600 (Arg0, 0x27, Local0, 0xFFFFFFFFFFFFFCE0)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) - Arg1)
                M600 (Arg0, 0x28, Local0, 0xFFFFFFFFFFFFFCDF)
                Local0 = (DerefOf (RefOf (AUI6)) - Arg1)
                M600 (Arg0, 0x29, Local0, 0xFFFFFFFFFFFFFCE0)
            }

            Local0 = (DerefOf (PAUI [0x05]) - Arg1)
            M600 (Arg0, 0x2A, Local0, 0xFFFFFFFFFFFFFCDF)
            Local0 = (DerefOf (PAUI [0x06]) - Arg1)
            M600 (Arg0, 0x2B, Local0, 0xFFFFFFFFFFFFFCE0)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) - Arg1)
            M600 (Arg0, 0x2C, Local0, 0xFFFFFFFFFFFFFCDF)
            Local0 = (M601 (0x01, 0x06) - Arg1)
            M600 (Arg0, 0x2D, Local0, 0xFFFFFFFFFFFFFCE0)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) - Arg1)
                M600 (Arg0, 0x2E, Local0, 0xFFFFFFFFFFFFFCDF)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) - Arg1)
                M600 (Arg0, 0x2F, Local0, 0xFFFFFFFFFFFFFCE0)
            }
        }

        /* Subtract, 64-bit */

        Method (M05A, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 - 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 - 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0xFE7CB391D650A283)
            Store ((Arg2 - AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 - AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0xFE7CB391D650A283)
            If (Y078)
            {
                Store ((Arg2 - DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 - DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0xFE7CB391D650A283)
            }

            Store ((Arg2 - DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 - DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0xFE7CB391D650A283)
            /* Method returns Integer */

            Store ((Arg2 - M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 - M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0xFE7CB391D650A283)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 - DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 - DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0xFE7CB391D650A283)
            }

            Local0 = (Arg2 - 0x00)
            M600 (Arg0, 0x0C, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 - 0x01)
            M600 (Arg0, 0x0D, Local0, 0xFE7CB391D650A283)
            Local0 = (Arg2 - AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 - AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0xFE7CB391D650A283)
            If (Y078)
            {
                Local0 = (Arg2 - DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0xFE7CB391D650A284)
                Local0 = (Arg2 - DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0xFE7CB391D650A283)
            }

            Local0 = (Arg2 - DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 - DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0xFE7CB391D650A283)
            /* Method returns Integer */

            Local0 = (Arg2 - M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 - M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0xFE7CB391D650A283)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 - DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0xFE7CB391D650A284)
                Local0 = (Arg2 - DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0xFE7CB391D650A283)
            }

            /* Conversion of the second operand */

            Store ((0x00 - Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0x01834C6E29AF5D7C)
            Store ((0x01 - Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0x01834C6E29AF5D7D)
            Store ((AUI5 - Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0x01834C6E29AF5D7C)
            Store ((AUI6 - Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0x01834C6E29AF5D7D)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) - Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0x01834C6E29AF5D7C)
                Store ((DerefOf (RefOf (AUI6)) - Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0x01834C6E29AF5D7D)
            }

            Store ((DerefOf (PAUI [0x05]) - Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0x01834C6E29AF5D7C)
            Store ((DerefOf (PAUI [0x06]) - Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0x01834C6E29AF5D7D)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) - Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0x01834C6E29AF5D7C)
            Store ((M601 (0x01, 0x06) - Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0x01834C6E29AF5D7D)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) - Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0x01834C6E29AF5D7C)
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) - Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0x01834C6E29AF5D7D)
            }

            Local0 = (0x00 - Arg2)
            M600 (Arg0, 0x24, Local0, 0x01834C6E29AF5D7C)
            Local0 = (0x01 - Arg2)
            M600 (Arg0, 0x25, Local0, 0x01834C6E29AF5D7D)
            Local0 = (AUI5 - Arg2)
            M600 (Arg0, 0x26, Local0, 0x01834C6E29AF5D7C)
            Local0 = (AUI6 - Arg2)
            M600 (Arg0, 0x27, Local0, 0x01834C6E29AF5D7D)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) - Arg2)
                M600 (Arg0, 0x28, Local0, 0x01834C6E29AF5D7C)
                Local0 = (DerefOf (RefOf (AUI6)) - Arg2)
                M600 (Arg0, 0x29, Local0, 0x01834C6E29AF5D7D)
            }

            Local0 = (DerefOf (PAUI [0x05]) - Arg2)
            M600 (Arg0, 0x2A, Local0, 0x01834C6E29AF5D7C)
            Local0 = (DerefOf (PAUI [0x06]) - Arg2)
            M600 (Arg0, 0x2B, Local0, 0x01834C6E29AF5D7D)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) - Arg2)
            M600 (Arg0, 0x2C, Local0, 0x01834C6E29AF5D7C)
            Local0 = (M601 (0x01, 0x06) - Arg2)
            M600 (Arg0, 0x2D, Local0, 0x01834C6E29AF5D7D)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) - Arg2)
                M600 (Arg0, 0x2E, Local0, 0x01834C6E29AF5D7C)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) - Arg2)
                M600 (Arg0, 0x2F, Local0, 0x01834C6E29AF5D7D)
            }

            /* Conversion of the both operands */

            Store ((Arg1 - Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0x01834C6E29AF609D)
            Store ((Arg2 - Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0xFE7CB391D6509F63)
            Local0 = (Arg1 - Arg2)
            M600 (Arg0, 0x32, Local0, 0x01834C6E29AF609D)
            Local0 = (Arg2 - Arg1)
            M600 (Arg0, 0x33, Local0, 0xFE7CB391D6509F63)
        }

        /* Subtract, 32-bit */

        Method (M05B, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 - 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0xD650A284)
            Store ((Arg2 - 0x01), Local0)
            M600 (Arg0, 0x01, Local0, 0xD650A283)
            Store ((Arg2 - AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0xD650A284)
            Store ((Arg2 - AUI6), Local0)
            M600 (Arg0, 0x03, Local0, 0xD650A283)
            If (Y078)
            {
                Store ((Arg2 - DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0xD650A284)
                Store ((Arg2 - DerefOf (RefOf (AUI6))), Local0)
                M600 (Arg0, 0x05, Local0, 0xD650A283)
            }

            Store ((Arg2 - DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0xD650A284)
            Store ((Arg2 - DerefOf (PAUI [0x06])), Local0)
            M600 (Arg0, 0x07, Local0, 0xD650A283)
            /* Method returns Integer */

            Store ((Arg2 - M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0xD650A284)
            Store ((Arg2 - M601 (0x01, 0x06)), Local0)
            M600 (Arg0, 0x09, Local0, 0xD650A283)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 - DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xD650A284)
                Store ((Arg2 - DerefOf (M602 (0x01, 0x06, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0xD650A283)
            }

            Local0 = (Arg2 - 0x00)
            M600 (Arg0, 0x0C, Local0, 0xD650A284)
            Local0 = (Arg2 - 0x01)
            M600 (Arg0, 0x0D, Local0, 0xD650A283)
            Local0 = (Arg2 - AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0xD650A284)
            Local0 = (Arg2 - AUI6) /* \AUI6 */
            M600 (Arg0, 0x0F, Local0, 0xD650A283)
            If (Y078)
            {
                Local0 = (Arg2 - DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0xD650A284)
                Local0 = (Arg2 - DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x11, Local0, 0xD650A283)
            }

            Local0 = (Arg2 - DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0xD650A284)
            Local0 = (Arg2 - DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x13, Local0, 0xD650A283)
            /* Method returns Integer */

            Local0 = (Arg2 - M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0xD650A284)
            Local0 = (Arg2 - M601 (0x01, 0x06))
            M600 (Arg0, 0x15, Local0, 0xD650A283)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 - DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0xD650A284)
                Local0 = (Arg2 - DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x17, Local0, 0xD650A283)
            }

            /* Conversion of the second operand */

            Store ((0x00 - Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0x29AF5D7C)
            Store ((0x01 - Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0x29AF5D7D)
            Store ((AUI5 - Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0x29AF5D7C)
            Store ((AUI6 - Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0x29AF5D7D)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) - Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0x29AF5D7C)
                Store ((DerefOf (RefOf (AUI6)) - Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0x29AF5D7D)
            }

            Store ((DerefOf (PAUI [0x05]) - Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0x29AF5D7C)
            Store ((DerefOf (PAUI [0x06]) - Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0x29AF5D7D)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) - Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0x29AF5D7C)
            Store ((M601 (0x01, 0x06) - Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0x29AF5D7D)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) - Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0x29AF5D7C)
                Store ((DerefOf (M602 (0x01, 0x06, 0x01)) - Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0x29AF5D7D)
            }

            Local0 = (0x00 - Arg2)
            M600 (Arg0, 0x24, Local0, 0x29AF5D7C)
            Local0 = (0x01 - Arg2)
            M600 (Arg0, 0x25, Local0, 0x29AF5D7D)
            Local0 = (AUI5 - Arg2)
            M600 (Arg0, 0x26, Local0, 0x29AF5D7C)
            Local0 = (AUI6 - Arg2)
            M600 (Arg0, 0x27, Local0, 0x29AF5D7D)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) - Arg2)
                M600 (Arg0, 0x28, Local0, 0x29AF5D7C)
                Local0 = (DerefOf (RefOf (AUI6)) - Arg2)
                M600 (Arg0, 0x29, Local0, 0x29AF5D7D)
            }

            Local0 = (DerefOf (PAUI [0x05]) - Arg2)
            M600 (Arg0, 0x2A, Local0, 0x29AF5D7C)
            Local0 = (DerefOf (PAUI [0x06]) - Arg2)
            M600 (Arg0, 0x2B, Local0, 0x29AF5D7D)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) - Arg2)
            M600 (Arg0, 0x2C, Local0, 0x29AF5D7C)
            Local0 = (M601 (0x01, 0x06) - Arg2)
            M600 (Arg0, 0x2D, Local0, 0x29AF5D7D)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) - Arg2)
                M600 (Arg0, 0x2E, Local0, 0x29AF5D7C)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) - Arg2)
                M600 (Arg0, 0x2F, Local0, 0x29AF5D7D)
            }

            /* Conversion of the both operands */

            Store ((Arg1 - Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0x29AF609D)
            Store ((Arg2 - Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0xD6509F63)
            Local0 = (Arg1 - Arg2)
            M600 (Arg0, 0x32, Local0, 0x29AF609D)
            Local0 = (Arg2 - Arg1)
            M600 (Arg0, 0x33, Local0, 0xD6509F63)
        }

        /* XOr, common 32-bit/64-bit test */

        Method (M05C, 2, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg1 ^ 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0x0321)
            Store ((Arg1 ^ 0xFFFFFFFFFFFFFFFF), Local0)
            M600 (Arg0, 0x01, Local0, 0xFFFFFFFFFFFFFCDE)
            Store ((Arg1 ^ AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0x0321)
            Store ((Arg1 ^ AUIJ), Local0)
            M600 (Arg0, 0x03, Local0, 0xFFFFFFFFFFFFFCDE)
            If (Y078)
            {
                Store ((Arg1 ^ DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0x0321)
                Store ((Arg1 ^ DerefOf (RefOf (AUIJ))), Local0)
                M600 (Arg0, 0x05, Local0, 0xFFFFFFFFFFFFFCDE)
            }

            Store ((Arg1 ^ DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0x0321)
            Store ((Arg1 ^ DerefOf (PAUI [0x13])), Local0)
            M600 (Arg0, 0x07, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Integer */

            Store ((Arg1 ^ M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0x0321)
            Store ((Arg1 ^ M601 (0x01, 0x13)), Local0)
            M600 (Arg0, 0x09, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg1 ^ DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0x0321)
                Store ((Arg1 ^ DerefOf (M602 (0x01, 0x13, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0xFFFFFFFFFFFFFCDE)
            }

            Local0 = (Arg1 ^ 0x00)
            M600 (Arg0, 0x0C, Local0, 0x0321)
            Local0 = (Arg1 ^ 0xFFFFFFFFFFFFFFFF)
            M600 (Arg0, 0x0D, Local0, 0xFFFFFFFFFFFFFCDE)
            Local0 = (Arg1 ^ AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0x0321)
            Local0 = (Arg1 ^ AUIJ) /* \AUIJ */
            M600 (Arg0, 0x0F, Local0, 0xFFFFFFFFFFFFFCDE)
            If (Y078)
            {
                Local0 = (Arg1 ^ DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0x0321)
                Local0 = (Arg1 ^ DerefOf (RefOf (AUIJ)))
                M600 (Arg0, 0x11, Local0, 0xFFFFFFFFFFFFFCDE)
            }

            Local0 = (Arg1 ^ DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0x0321)
            Local0 = (Arg1 ^ DerefOf (PAUI [0x13]))
            M600 (Arg0, 0x13, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Integer */

            Local0 = (Arg1 ^ M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0x0321)
            Local0 = (Arg1 ^ M601 (0x01, 0x13))
            M600 (Arg0, 0x15, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg1 ^ DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0x0321)
                Local0 = (Arg1 ^ DerefOf (M602 (0x01, 0x13, 0x01)))
                M600 (Arg0, 0x17, Local0, 0xFFFFFFFFFFFFFCDE)
            }

            /* Conversion of the second operand */

            Store ((0x00 ^ Arg1), Local0)
            M600 (Arg0, 0x18, Local0, 0x0321)
            Store ((0xFFFFFFFFFFFFFFFF ^ Arg1), Local0)
            M600 (Arg0, 0x19, Local0, 0xFFFFFFFFFFFFFCDE)
            Store ((AUI5 ^ Arg1), Local0)
            M600 (Arg0, 0x1A, Local0, 0x0321)
            Store ((AUIJ ^ Arg1), Local0)
            M600 (Arg0, 0x1B, Local0, 0xFFFFFFFFFFFFFCDE)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) ^ Arg1), Local0)
                M600 (Arg0, 0x1C, Local0, 0x0321)
                Store ((DerefOf (RefOf (AUIJ)) ^ Arg1), Local0)
                M600 (Arg0, 0x1D, Local0, 0xFFFFFFFFFFFFFCDE)
            }

            Store ((DerefOf (PAUI [0x05]) ^ Arg1), Local0)
            M600 (Arg0, 0x1E, Local0, 0x0321)
            Store ((DerefOf (PAUI [0x13]) ^ Arg1), Local0)
            M600 (Arg0, 0x1F, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) ^ Arg1), Local0)
            M600 (Arg0, 0x20, Local0, 0x0321)
            Store ((M601 (0x01, 0x13) ^ Arg1), Local0)
            M600 (Arg0, 0x21, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) ^ Arg1), Local0)
                M600 (Arg0, 0x22, Local0, 0x0321)
                Store ((DerefOf (M602 (0x01, 0x13, 0x01)) ^ Arg1), Local0)
                M600 (Arg0, 0x23, Local0, 0xFFFFFFFFFFFFFCDE)
            }

            Local0 = (0x00 ^ Arg1)
            M600 (Arg0, 0x24, Local0, 0x0321)
            Local0 = (0xFFFFFFFFFFFFFFFF ^ Arg1)
            M600 (Arg0, 0x25, Local0, 0xFFFFFFFFFFFFFCDE)
            Local0 = (AUI5 ^ Arg1)
            M600 (Arg0, 0x26, Local0, 0x0321)
            Local0 = (AUIJ ^ Arg1)
            M600 (Arg0, 0x27, Local0, 0xFFFFFFFFFFFFFCDE)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) ^ Arg1)
                M600 (Arg0, 0x28, Local0, 0x0321)
                Local0 = (DerefOf (RefOf (AUIJ)) ^ Arg1)
                M600 (Arg0, 0x29, Local0, 0xFFFFFFFFFFFFFCDE)
            }

            Local0 = (DerefOf (PAUI [0x05]) ^ Arg1)
            M600 (Arg0, 0x2A, Local0, 0x0321)
            Local0 = (DerefOf (PAUI [0x13]) ^ Arg1)
            M600 (Arg0, 0x2B, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) ^ Arg1)
            M600 (Arg0, 0x2C, Local0, 0x0321)
            Local0 = (M601 (0x01, 0x13) ^ Arg1)
            M600 (Arg0, 0x2D, Local0, 0xFFFFFFFFFFFFFCDE)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) ^ Arg1)
                M600 (Arg0, 0x2E, Local0, 0x0321)
                Local0 = (DerefOf (M602 (0x01, 0x13, 0x01)) ^ Arg1)
                M600 (Arg0, 0x2F, Local0, 0xFFFFFFFFFFFFFCDE)
            }
        }

        /* XOr, 64-bit */

        Method (M05D, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 ^ 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 ^ 0xFFFFFFFFFFFFFFFF), Local0)
            M600 (Arg0, 0x01, Local0, 0x01834C6E29AF5D7B)
            Store ((Arg2 ^ AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 ^ AUIJ), Local0)
            M600 (Arg0, 0x03, Local0, 0x01834C6E29AF5D7B)
            If (Y078)
            {
                Store ((Arg2 ^ DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 ^ DerefOf (RefOf (AUIJ))), Local0)
                M600 (Arg0, 0x05, Local0, 0x01834C6E29AF5D7B)
            }

            Store ((Arg2 ^ DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 ^ DerefOf (PAUI [0x13])), Local0)
            M600 (Arg0, 0x07, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Integer */

            Store ((Arg2 ^ M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0xFE7CB391D650A284)
            Store ((Arg2 ^ M601 (0x01, 0x13)), Local0)
            M600 (Arg0, 0x09, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 ^ DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xFE7CB391D650A284)
                Store ((Arg2 ^ DerefOf (M602 (0x01, 0x13, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x01834C6E29AF5D7B)
            }

            Local0 = (Arg2 ^ 0x00)
            M600 (Arg0, 0x0C, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 ^ 0xFFFFFFFFFFFFFFFF)
            M600 (Arg0, 0x0D, Local0, 0x01834C6E29AF5D7B)
            Local0 = (Arg2 ^ AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 ^ AUIJ) /* \AUIJ */
            M600 (Arg0, 0x0F, Local0, 0x01834C6E29AF5D7B)
            If (Y078)
            {
                Local0 = (Arg2 ^ DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0xFE7CB391D650A284)
                Local0 = (Arg2 ^ DerefOf (RefOf (AUIJ)))
                M600 (Arg0, 0x11, Local0, 0x01834C6E29AF5D7B)
            }

            Local0 = (Arg2 ^ DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 ^ DerefOf (PAUI [0x13]))
            M600 (Arg0, 0x13, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Integer */

            Local0 = (Arg2 ^ M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0xFE7CB391D650A284)
            Local0 = (Arg2 ^ M601 (0x01, 0x13))
            M600 (Arg0, 0x15, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 ^ DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0xFE7CB391D650A284)
                Local0 = (Arg2 ^ DerefOf (M602 (0x01, 0x13, 0x01)))
                M600 (Arg0, 0x17, Local0, 0x01834C6E29AF5D7B)
            }

            /* Conversion of the second operand */

            Store ((0x00 ^ Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0xFE7CB391D650A284)
            Store ((0xFFFFFFFFFFFFFFFF ^ Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0x01834C6E29AF5D7B)
            Store ((AUI5 ^ Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0xFE7CB391D650A284)
            Store ((AUIJ ^ Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0x01834C6E29AF5D7B)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) ^ Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0xFE7CB391D650A284)
                Store ((DerefOf (RefOf (AUIJ)) ^ Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0x01834C6E29AF5D7B)
            }

            Store ((DerefOf (PAUI [0x05]) ^ Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0xFE7CB391D650A284)
            Store ((DerefOf (PAUI [0x13]) ^ Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) ^ Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0xFE7CB391D650A284)
            Store ((M601 (0x01, 0x13) ^ Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) ^ Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0xFE7CB391D650A284)
                Store ((DerefOf (M602 (0x01, 0x13, 0x01)) ^ Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0x01834C6E29AF5D7B)
            }

            Local0 = (0x00 ^ Arg2)
            M600 (Arg0, 0x24, Local0, 0xFE7CB391D650A284)
            Local0 = (0xFFFFFFFFFFFFFFFF ^ Arg2)
            M600 (Arg0, 0x25, Local0, 0x01834C6E29AF5D7B)
            Local0 = (AUI5 ^ Arg2)
            M600 (Arg0, 0x26, Local0, 0xFE7CB391D650A284)
            Local0 = (AUIJ ^ Arg2)
            M600 (Arg0, 0x27, Local0, 0x01834C6E29AF5D7B)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) ^ Arg2)
                M600 (Arg0, 0x28, Local0, 0xFE7CB391D650A284)
                Local0 = (DerefOf (RefOf (AUIJ)) ^ Arg2)
                M600 (Arg0, 0x29, Local0, 0x01834C6E29AF5D7B)
            }

            Local0 = (DerefOf (PAUI [0x05]) ^ Arg2)
            M600 (Arg0, 0x2A, Local0, 0xFE7CB391D650A284)
            Local0 = (DerefOf (PAUI [0x13]) ^ Arg2)
            M600 (Arg0, 0x2B, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) ^ Arg2)
            M600 (Arg0, 0x2C, Local0, 0xFE7CB391D650A284)
            Local0 = (M601 (0x01, 0x13) ^ Arg2)
            M600 (Arg0, 0x2D, Local0, 0x01834C6E29AF5D7B)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) ^ Arg2)
                M600 (Arg0, 0x2E, Local0, 0xFE7CB391D650A284)
                Local0 = (DerefOf (M602 (0x01, 0x13, 0x01)) ^ Arg2)
                M600 (Arg0, 0x2F, Local0, 0x01834C6E29AF5D7B)
            }

            /* Conversion of the both operands */

            Store ((Arg1 ^ Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0xFE7CB391D650A1A5)
            Store ((Arg2 ^ Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0xFE7CB391D650A1A5)
            Local0 = (Arg1 ^ Arg2)
            M600 (Arg0, 0x32, Local0, 0xFE7CB391D650A1A5)
            Local0 = (Arg2 ^ Arg1)
            M600 (Arg0, 0x33, Local0, 0xFE7CB391D650A1A5)
        }

        /* XOr, 32-bit */

        Method (M05E, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Store ((Arg2 ^ 0x00), Local0)
            M600 (Arg0, 0x00, Local0, 0xD650A284)
            Store ((Arg2 ^ 0xFFFFFFFF), Local0)
            M600 (Arg0, 0x01, Local0, 0x29AF5D7B)
            Store ((Arg2 ^ AUI5), Local0)
            M600 (Arg0, 0x02, Local0, 0xD650A284)
            Store ((Arg2 ^ AUII), Local0)
            M600 (Arg0, 0x03, Local0, 0x29AF5D7B)
            If (Y078)
            {
                Store ((Arg2 ^ DerefOf (RefOf (AUI5))), Local0)
                M600 (Arg0, 0x04, Local0, 0xD650A284)
                Store ((Arg2 ^ DerefOf (RefOf (AUII))), Local0)
                M600 (Arg0, 0x05, Local0, 0x29AF5D7B)
            }

            Store ((Arg2 ^ DerefOf (PAUI [0x05])), Local0)
            M600 (Arg0, 0x06, Local0, 0xD650A284)
            Store ((Arg2 ^ DerefOf (PAUI [0x12])), Local0)
            M600 (Arg0, 0x07, Local0, 0x29AF5D7B)
            /* Method returns Integer */

            Store ((Arg2 ^ M601 (0x01, 0x05)), Local0)
            M600 (Arg0, 0x08, Local0, 0xD650A284)
            Store ((Arg2 ^ M601 (0x01, 0x12)), Local0)
            M600 (Arg0, 0x09, Local0, 0x29AF5D7B)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((Arg2 ^ DerefOf (M602 (0x01, 0x05, 0x01))), Local0)
                M600 (Arg0, 0x0A, Local0, 0xD650A284)
                Store ((Arg2 ^ DerefOf (M602 (0x01, 0x12, 0x01))), Local0)
                M600 (Arg0, 0x0B, Local0, 0x29AF5D7B)
            }

            Local0 = (Arg2 ^ 0x00)
            M600 (Arg0, 0x0C, Local0, 0xD650A284)
            Local0 = (Arg2 ^ 0xFFFFFFFF)
            M600 (Arg0, 0x0D, Local0, 0x29AF5D7B)
            Local0 = (Arg2 ^ AUI5) /* \AUI5 */
            M600 (Arg0, 0x0E, Local0, 0xD650A284)
            Local0 = (Arg2 ^ AUII) /* \AUII */
            M600 (Arg0, 0x0F, Local0, 0x29AF5D7B)
            If (Y078)
            {
                Local0 = (Arg2 ^ DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x10, Local0, 0xD650A284)
                Local0 = (Arg2 ^ DerefOf (RefOf (AUII)))
                M600 (Arg0, 0x11, Local0, 0x29AF5D7B)
            }

            Local0 = (Arg2 ^ DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x12, Local0, 0xD650A284)
            Local0 = (Arg2 ^ DerefOf (PAUI [0x12]))
            M600 (Arg0, 0x13, Local0, 0x29AF5D7B)
            /* Method returns Integer */

            Local0 = (Arg2 ^ M601 (0x01, 0x05))
            M600 (Arg0, 0x14, Local0, 0xD650A284)
            Local0 = (Arg2 ^ M601 (0x01, 0x12))
            M600 (Arg0, 0x15, Local0, 0x29AF5D7B)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 ^ DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x16, Local0, 0xD650A284)
                Local0 = (Arg2 ^ DerefOf (M602 (0x01, 0x12, 0x01)))
                M600 (Arg0, 0x17, Local0, 0x29AF5D7B)
            }

            /* Conversion of the second operand */

            Store ((0x00 ^ Arg2), Local0)
            M600 (Arg0, 0x18, Local0, 0xD650A284)
            Store ((0xFFFFFFFF ^ Arg2), Local0)
            M600 (Arg0, 0x19, Local0, 0x29AF5D7B)
            Store ((AUI5 ^ Arg2), Local0)
            M600 (Arg0, 0x1A, Local0, 0xD650A284)
            Store ((AUII ^ Arg2), Local0)
            M600 (Arg0, 0x1B, Local0, 0x29AF5D7B)
            If (Y078)
            {
                Store ((DerefOf (RefOf (AUI5)) ^ Arg2), Local0)
                M600 (Arg0, 0x1C, Local0, 0xD650A284)
                Store ((DerefOf (RefOf (AUII)) ^ Arg2), Local0)
                M600 (Arg0, 0x1D, Local0, 0x29AF5D7B)
            }

            Store ((DerefOf (PAUI [0x05]) ^ Arg2), Local0)
            M600 (Arg0, 0x1E, Local0, 0xD650A284)
            Store ((DerefOf (PAUI [0x12]) ^ Arg2), Local0)
            M600 (Arg0, 0x1F, Local0, 0x29AF5D7B)
            /* Method returns Integer */

            Store ((M601 (0x01, 0x05) ^ Arg2), Local0)
            M600 (Arg0, 0x20, Local0, 0xD650A284)
            Store ((M601 (0x01, 0x12) ^ Arg2), Local0)
            M600 (Arg0, 0x21, Local0, 0x29AF5D7B)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Store ((DerefOf (M602 (0x01, 0x05, 0x01)) ^ Arg2), Local0)
                M600 (Arg0, 0x22, Local0, 0xD650A284)
                Store ((DerefOf (M602 (0x01, 0x12, 0x01)) ^ Arg2), Local0)
                M600 (Arg0, 0x23, Local0, 0x29AF5D7B)
            }

            Local0 = (0x00 ^ Arg2)
            M600 (Arg0, 0x24, Local0, 0xD650A284)
            Local0 = (0xFFFFFFFF ^ Arg2)
            M600 (Arg0, 0x25, Local0, 0x29AF5D7B)
            Local0 = (AUI5 ^ Arg2)
            M600 (Arg0, 0x26, Local0, 0xD650A284)
            Local0 = (AUII ^ Arg2)
            M600 (Arg0, 0x27, Local0, 0x29AF5D7B)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) ^ Arg2)
                M600 (Arg0, 0x28, Local0, 0xD650A284)
                Local0 = (DerefOf (RefOf (AUII)) ^ Arg2)
                M600 (Arg0, 0x29, Local0, 0x29AF5D7B)
            }

            Local0 = (DerefOf (PAUI [0x05]) ^ Arg2)
            M600 (Arg0, 0x2A, Local0, 0xD650A284)
            Local0 = (DerefOf (PAUI [0x12]) ^ Arg2)
            M600 (Arg0, 0x2B, Local0, 0x29AF5D7B)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) ^ Arg2)
            M600 (Arg0, 0x2C, Local0, 0xD650A284)
            Local0 = (M601 (0x01, 0x12) ^ Arg2)
            M600 (Arg0, 0x2D, Local0, 0x29AF5D7B)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) ^ Arg2)
                M600 (Arg0, 0x2E, Local0, 0xD650A284)
                Local0 = (DerefOf (M602 (0x01, 0x12, 0x01)) ^ Arg2)
                M600 (Arg0, 0x2F, Local0, 0x29AF5D7B)
            }

            /* Conversion of the both operands */

            Store ((Arg1 ^ Arg2), Local0)
            M600 (Arg0, 0x30, Local0, 0xD650A1A5)
            Store ((Arg2 ^ Arg1), Local0)
            M600 (Arg0, 0x31, Local0, 0xD650A1A5)
            Local0 = (Arg1 ^ Arg2)
            M600 (Arg0, 0x32, Local0, 0xD650A1A5)
            Local0 = (Arg2 ^ Arg1)
            M600 (Arg0, 0x33, Local0, 0xD650A1A5)
        }

        /* Add, And, Divide, Mod, Multiply, NAnd, NOr, Or, */
        /* ShiftLeft, ShiftRight, Subtract, Xor */
        Method (M64N, 1, NotSerialized)
        {
            /* Add */

            Concatenate (Arg0, "-m03b", Local0)
            SRMT (Local0)
            M03B (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                })
            Concatenate (Arg0, "-m03c", Local0)
            SRMT (Local0)
            M03C (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
            /* And */

            Concatenate (Arg0, "-m03e", Local0)
            SRMT (Local0)
            M03E (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                })
            Concatenate (Arg0, "-m03f", Local0)
            SRMT (Local0)
            M03F (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
            /* Divide */

            Concatenate (Arg0, "-m041", Local0)
            SRMT (Local0)
            M041 (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                })
            Concatenate (Arg0, "-m042", Local0)
            SRMT (Local0)
            M042 (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
            /* Mod */

            Concatenate (Arg0, "-m044", Local0)
            SRMT (Local0)
            M044 (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                })
            Concatenate (Arg0, "-m045", Local0)
            SRMT (Local0)
            M045 (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
            /* Multiply */

            Concatenate (Arg0, "-m047", Local0)
            SRMT (Local0)
            M047 (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                })
            Concatenate (Arg0, "-m048", Local0)
            SRMT (Local0)
            M048 (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
            /* NAnd */

            Concatenate (Arg0, "-m04a", Local0)
            SRMT (Local0)
            M04A (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                })
            Concatenate (Arg0, "-m04b", Local0)
            SRMT (Local0)
            M04B (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
            /* NOr */

            Concatenate (Arg0, "-m04d", Local0)
            SRMT (Local0)
            M04D (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                })
            Concatenate (Arg0, "-m04e", Local0)
            SRMT (Local0)
            M04E (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
            /* Or */

            Concatenate (Arg0, "-m050", Local0)
            SRMT (Local0)
            M050 (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                })
            Concatenate (Arg0, "-m051", Local0)
            SRMT (Local0)
            M051 (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
            /* ShiftLeft */

            Concatenate (Arg0, "-m053", Local0)
            SRMT (Local0)
            M053 (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x01)
                {
                     0x0B                                             // .
                })
            Concatenate (Arg0, "-m054", Local0)
            SRMT (Local0)
            M054 (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                }, Buffer (0x01)
                {
                     0x0B                                             // .
                })
            /* ShiftRight */

            Concatenate (Arg0, "-m056", Local0)
            SRMT (Local0)
            M056 (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x01)
                {
                     0x0B                                             // .
                })
            Concatenate (Arg0, "-m057", Local0)
            SRMT (Local0)
            M057 (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                }, Buffer (0x01)
                {
                     0x0B                                             // .
                })
            /* Subtract */

            Concatenate (Arg0, "-m059", Local0)
            SRMT (Local0)
            M059 (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                })
            Concatenate (Arg0, "-m05a", Local0)
            SRMT (Local0)
            M05A (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
            /* XOr */

            Concatenate (Arg0, "-m05c", Local0)
            SRMT (Local0)
            M05C (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                })
            Concatenate (Arg0, "-m05d", Local0)
            SRMT (Local0)
            M05D (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
        }

        Method (M32N, 1, NotSerialized)
        {
            /* Add */

            Concatenate (Arg0, "-m03b", Local0)
            SRMT (Local0)
            M03B (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                })
            Concatenate (Arg0, "-m03d", Local0)
            SRMT (Local0)
            M03D (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
            /* And */

            Concatenate (Arg0, "-m03e", Local0)
            SRMT (Local0)
            M03E (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                })
            Concatenate (Arg0, "-m040", Local0)
            SRMT (Local0)
            M040 (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
            /* Divide */

            Concatenate (Arg0, "-m041", Local0)
            SRMT (Local0)
            M041 (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                })
            Concatenate (Arg0, "-m043", Local0)
            SRMT (Local0)
            M043 (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
            /* Mod */

            Concatenate (Arg0, "-m044", Local0)
            SRMT (Local0)
            M044 (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                })
            Concatenate (Arg0, "-m046", Local0)
            SRMT (Local0)
            M046 (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
            /* Multiply */

            Concatenate (Arg0, "-m047", Local0)
            SRMT (Local0)
            M047 (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                })
            Concatenate (Arg0, "-m049", Local0)
            SRMT (Local0)
            M049 (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
            /* NAnd */

            Concatenate (Arg0, "-m04a", Local0)
            SRMT (Local0)
            If (Y119)
            {
                M04A (Local0, Buffer (0x03)
                    {
                         0x21, 0x03, 0x00                                 // !..
                    })
            }
            Else
            {
                BLCK ()
            }

            Concatenate (Arg0, "-m04c", Local0)
            SRMT (Local0)
            M04C (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
            /* NOr */

            Concatenate (Arg0, "-m04d", Local0)
            SRMT (Local0)
            If (Y119)
            {
                M04D (Local0, Buffer (0x03)
                    {
                         0x21, 0x03, 0x00                                 // !..
                    })
            }
            Else
            {
                BLCK ()
            }

            Concatenate (Arg0, "-m04f", Local0)
            SRMT (Local0)
            M04F (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
            /* Or */

            Concatenate (Arg0, "-m050", Local0)
            SRMT (Local0)
            If (Y119)
            {
                M050 (Local0, Buffer (0x03)
                    {
                         0x21, 0x03, 0x00                                 // !..
                    })
            }
            Else
            {
                BLCK ()
            }

            Concatenate (Arg0, "-m052", Local0)
            SRMT (Local0)
            M052 (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
            /* ShiftLeft */

            Concatenate (Arg0, "-m053", Local0)
            SRMT (Local0)
            M053 (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x01)
                {
                     0x0B                                             // .
                })
            Concatenate (Arg0, "-m055", Local0)
            SRMT (Local0)
            M055 (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                }, Buffer (0x01)
                {
                     0x0B                                             // .
                })
            /* ShiftRight */

            Concatenate (Arg0, "-m056", Local0)
            SRMT (Local0)
            M056 (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x01)
                {
                     0x0B                                             // .
                })
            Concatenate (Arg0, "-m058", Local0)
            SRMT (Local0)
            M058 (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                }, Buffer (0x01)
                {
                     0x0B                                             // .
                })
            /* Subtract */

            Concatenate (Arg0, "-m059", Local0)
            SRMT (Local0)
            If (Y119)
            {
                M059 (Local0, Buffer (0x03)
                    {
                         0x21, 0x03, 0x00                                 // !..
                    })
            }
            Else
            {
                BLCK ()
            }

            Concatenate (Arg0, "-m05b", Local0)
            SRMT (Local0)
            M05B (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
            /* XOr */

            Concatenate (Arg0, "-m05c", Local0)
            SRMT (Local0)
            If (Y119)
            {
                M05C (Local0, Buffer (0x03)
                    {
                         0x21, 0x03, 0x00                                 // !..
                    })
            }
            Else
            {
                BLCK ()
            }

            Concatenate (Arg0, "-m05e", Local0)
            SRMT (Local0)
            M05E (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
        }

        /* Buffer to Integer conversion of each Buffer operand */
        /* of the 2-parameter Logical Integer operators LAnd and LOr */
        /* LAnd, common 32-bit/64-bit test */
        Method (M05F, 2, NotSerialized)
        {
            /* Conversion of the first operand */

            Local0 = (Arg1 && 0x00)
            M600 (Arg0, 0x00, Local0, Zero)
            Local0 = (Arg1 && 0x01)
            M600 (Arg0, 0x01, Local0, Ones)
            Local0 = (Arg1 && AUI5)
            M600 (Arg0, 0x02, Local0, Zero)
            Local0 = (Arg1 && AUI6)
            M600 (Arg0, 0x03, Local0, Ones)
            If (Y078)
            {
                Local0 = (Arg1 && DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x04, Local0, Zero)
                Local0 = (Arg1 && DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x05, Local0, Ones)
            }

            Local0 = (Arg1 && DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x06, Local0, Zero)
            Local0 = (Arg1 && DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x07, Local0, Ones)
            /* Method returns Integer */

            Local0 = (Arg1 && M601 (0x01, 0x05))
            M600 (Arg0, 0x08, Local0, Zero)
            Local0 = (Arg1 && M601 (0x01, 0x06))
            M600 (Arg0, 0x09, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg1 && DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x0A, Local0, Zero)
                Local0 = (Arg1 && DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x0B, Local0, Ones)
            }

            /* Conversion of the second operand */

            Local0 = (0x00 && Arg1)
            M600 (Arg0, 0x0C, Local0, Zero)
            Local0 = (0x01 && Arg1)
            M600 (Arg0, 0x0D, Local0, Ones)
            Local0 = (AUI5 && Arg1)
            M600 (Arg0, 0x0E, Local0, Zero)
            Local0 = (AUI6 && Arg1)
            M600 (Arg0, 0x0F, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) && Arg1)
                M600 (Arg0, 0x10, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUI6)) && Arg1)
                M600 (Arg0, 0x11, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x05]) && Arg1)
            M600 (Arg0, 0x12, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x06]) && Arg1)
            M600 (Arg0, 0x13, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) && Arg1)
            M600 (Arg0, 0x14, Local0, Zero)
            Local0 = (M601 (0x01, 0x06) && Arg1)
            M600 (Arg0, 0x15, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) && Arg1)
                M600 (Arg0, 0x16, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) && Arg1)
                M600 (Arg0, 0x17, Local0, Ones)
            }
        }

        /* LAnd, 64-bit */

        Method (M060, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Local0 = (Arg2 && 0x00)
            M600 (Arg0, 0x00, Local0, Zero)
            Local0 = (Arg2 && 0x01)
            M600 (Arg0, 0x01, Local0, Ones)
            Local0 = (Arg2 && AUI5)
            M600 (Arg0, 0x02, Local0, Zero)
            Local0 = (Arg2 && AUI6)
            M600 (Arg0, 0x03, Local0, Ones)
            If (Y078)
            {
                Local0 = (Arg2 && DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x04, Local0, Zero)
                Local0 = (Arg2 && DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x05, Local0, Ones)
            }

            Local0 = (Arg2 && DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x06, Local0, Zero)
            Local0 = (Arg2 && DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x07, Local0, Ones)
            /* Method returns Integer */

            Local0 = (Arg2 && M601 (0x01, 0x05))
            M600 (Arg0, 0x08, Local0, Zero)
            Local0 = (Arg2 && M601 (0x01, 0x06))
            M600 (Arg0, 0x09, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 && DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x0A, Local0, Zero)
                Local0 = (Arg2 && DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x0B, Local0, Ones)
            }

            /* Conversion of the second operand */

            Local0 = (0x00 && Arg2)
            M600 (Arg0, 0x0C, Local0, Zero)
            Local0 = (0x01 && Arg2)
            M600 (Arg0, 0x0D, Local0, Ones)
            Local0 = (AUI5 && Arg2)
            M600 (Arg0, 0x0E, Local0, Zero)
            Local0 = (AUI6 && Arg2)
            M600 (Arg0, 0x0F, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) && Arg2)
                M600 (Arg0, 0x10, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUI6)) && Arg2)
                M600 (Arg0, 0x11, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x05]) && Arg2)
            M600 (Arg0, 0x12, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x06]) && Arg2)
            M600 (Arg0, 0x13, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) && Arg2)
            M600 (Arg0, 0x14, Local0, Zero)
            Local0 = (M601 (0x01, 0x06) && Arg2)
            M600 (Arg0, 0x15, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) && Arg2)
                M600 (Arg0, 0x16, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) && Arg2)
                M600 (Arg0, 0x17, Local0, Ones)
            }

            /* Conversion of the both operands */

            Local0 = (Arg1 && Arg2)
            M600 (Arg0, 0x18, Local0, Ones)
            Local0 = (Arg2 && Arg1)
            M600 (Arg0, 0x19, Local0, Ones)
        }

        /* LAnd, 32-bit */

        Method (M061, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Local0 = (Arg2 && 0x00)
            M600 (Arg0, 0x00, Local0, Zero)
            Local0 = (Arg2 && 0x01)
            M600 (Arg0, 0x01, Local0, Ones)
            Local0 = (Arg2 && AUI5)
            M600 (Arg0, 0x02, Local0, Zero)
            Local0 = (Arg2 && AUI6)
            M600 (Arg0, 0x03, Local0, Ones)
            If (Y078)
            {
                Local0 = (Arg2 && DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x04, Local0, Zero)
                Local0 = (Arg2 && DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x05, Local0, Ones)
            }

            Local0 = (Arg2 && DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x06, Local0, Zero)
            Local0 = (Arg2 && DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x07, Local0, Ones)
            /* Method returns Integer */

            Local0 = (Arg2 && M601 (0x01, 0x05))
            M600 (Arg0, 0x08, Local0, Zero)
            Local0 = (Arg2 && M601 (0x01, 0x06))
            M600 (Arg0, 0x09, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg2 && DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x0A, Local0, Zero)
                Local0 = (Arg2 && DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x0B, Local0, Ones)
            }

            /* Conversion of the second operand */

            Local0 = (0x00 && Arg2)
            M600 (Arg0, 0x0C, Local0, Zero)
            Local0 = (0x01 && Arg2)
            M600 (Arg0, 0x0D, Local0, Ones)
            Local0 = (AUI5 && Arg2)
            M600 (Arg0, 0x0E, Local0, Zero)
            Local0 = (AUI6 && Arg2)
            M600 (Arg0, 0x0F, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) && Arg2)
                M600 (Arg0, 0x10, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUI6)) && Arg2)
                M600 (Arg0, 0x11, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x05]) && Arg2)
            M600 (Arg0, 0x12, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x06]) && Arg2)
            M600 (Arg0, 0x13, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) && Arg2)
            M600 (Arg0, 0x14, Local0, Zero)
            Local0 = (M601 (0x01, 0x06) && Arg2)
            M600 (Arg0, 0x15, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) && Arg2)
                M600 (Arg0, 0x16, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) && Arg2)
                M600 (Arg0, 0x17, Local0, Ones)
            }

            /* Conversion of the both operands */

            Local0 = (Arg1 && Arg2)
            M600 (Arg0, 0x18, Local0, Ones)
            Local0 = (Arg2 && Arg1)
            M600 (Arg0, 0x19, Local0, Ones)
        }

        /* Lor, common 32-bit/64-bit test */

        Method (M062, 2, NotSerialized)
        {
            /* Conversion of the first operand */

            Local0 = (Arg1 || 0x00)
            M600 (Arg0, 0x00, Local0, Zero)
            Local0 = (Arg1 || 0x01)
            M600 (Arg0, 0x01, Local0, Ones)
            Local0 = (Arg1 || AUI5)
            M600 (Arg0, 0x02, Local0, Zero)
            Local0 = (Arg1 || AUI6)
            M600 (Arg0, 0x03, Local0, Ones)
            If (Y078)
            {
                Local0 = (Arg1 || DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x04, Local0, Zero)
                Local0 = (Arg1 || DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x05, Local0, Ones)
            }

            Local0 = (Arg1 || DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x06, Local0, Zero)
            Local0 = (Arg1 || DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x07, Local0, Ones)
            /* Method returns Integer */

            Local0 = (Arg1 || M601 (0x01, 0x05))
            M600 (Arg0, 0x08, Local0, Zero)
            Local0 = (Arg1 || M601 (0x01, 0x06))
            M600 (Arg0, 0x09, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg1 || DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x0A, Local0, Zero)
                Local0 = (Arg1 || DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x0B, Local0, Ones)
            }

            /* Conversion of the second operand */

            Local0 = (0x00 || Arg1)
            M600 (Arg0, 0x0C, Local0, Zero)
            Local0 = (0x01 || Arg1)
            M600 (Arg0, 0x0D, Local0, Ones)
            Local0 = (AUI5 || Arg1)
            M600 (Arg0, 0x0E, Local0, Zero)
            Local0 = (AUI6 || Arg1)
            M600 (Arg0, 0x0F, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) || Arg1)
                M600 (Arg0, 0x10, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUI6)) || Arg1)
                M600 (Arg0, 0x11, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x05]) || Arg1)
            M600 (Arg0, 0x12, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x06]) || Arg1)
            M600 (Arg0, 0x13, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) || Arg1)
            M600 (Arg0, 0x14, Local0, Zero)
            Local0 = (M601 (0x01, 0x06) || Arg1)
            M600 (Arg0, 0x15, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) || Arg1)
                M600 (Arg0, 0x16, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) || Arg1)
                M600 (Arg0, 0x17, Local0, Ones)
            }
        }

        /* Lor, 64-bit */

        Method (M063, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Local0 = (Arg1 || 0x00)
            M600 (Arg0, 0x00, Local0, Ones)
            Local0 = (Arg1 || 0x01)
            M600 (Arg0, 0x01, Local0, Ones)
            Local0 = (Arg1 || AUI5)
            M600 (Arg0, 0x02, Local0, Ones)
            Local0 = (Arg1 || AUI6)
            M600 (Arg0, 0x03, Local0, Ones)
            If (Y078)
            {
                Local0 = (Arg1 || DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x04, Local0, Ones)
                Local0 = (Arg1 || DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x05, Local0, Ones)
            }

            Local0 = (Arg1 || DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x06, Local0, Ones)
            Local0 = (Arg1 || DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x07, Local0, Ones)
            /* Method returns Integer */

            Local0 = (Arg1 || M601 (0x01, 0x05))
            M600 (Arg0, 0x08, Local0, Ones)
            Local0 = (Arg1 || M601 (0x01, 0x06))
            M600 (Arg0, 0x09, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg1 || DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x0A, Local0, Ones)
                Local0 = (Arg1 || DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x0B, Local0, Ones)
            }

            /* Conversion of the second operand */

            Local0 = (0x00 || Arg1)
            M600 (Arg0, 0x0C, Local0, Ones)
            Local0 = (0x01 || Arg1)
            M600 (Arg0, 0x0D, Local0, Ones)
            Local0 = (AUI5 || Arg1)
            M600 (Arg0, 0x0E, Local0, Ones)
            Local0 = (AUI6 || Arg1)
            M600 (Arg0, 0x0F, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) || Arg1)
                M600 (Arg0, 0x10, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUI6)) || Arg1)
                M600 (Arg0, 0x11, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x05]) || Arg1)
            M600 (Arg0, 0x12, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x06]) || Arg1)
            M600 (Arg0, 0x13, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) || Arg1)
            M600 (Arg0, 0x14, Local0, Ones)
            Local0 = (M601 (0x01, 0x06) || Arg1)
            M600 (Arg0, 0x15, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) || Arg1)
                M600 (Arg0, 0x16, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) || Arg1)
                M600 (Arg0, 0x17, Local0, Ones)
            }

            /* Conversion of the both operands */

            Local0 = (Arg2 || Arg1)
            M600 (Arg0, 0x18, Local0, Ones)
            Local0 = (Arg1 || Arg2)
            M600 (Arg0, 0x19, Local0, Ones)
        }

        /* Lor, 32-bit */

        Method (M064, 3, NotSerialized)
        {
            /* Conversion of the first operand */

            Local0 = (Arg1 || 0x00)
            M600 (Arg0, 0x00, Local0, Ones)
            Local0 = (Arg1 || 0x01)
            M600 (Arg0, 0x01, Local0, Ones)
            Local0 = (Arg1 || AUI5)
            M600 (Arg0, 0x02, Local0, Ones)
            Local0 = (Arg1 || AUI6)
            M600 (Arg0, 0x03, Local0, Ones)
            If (Y078)
            {
                Local0 = (Arg1 || DerefOf (RefOf (AUI5)))
                M600 (Arg0, 0x04, Local0, Ones)
                Local0 = (Arg1 || DerefOf (RefOf (AUI6)))
                M600 (Arg0, 0x05, Local0, Ones)
            }

            Local0 = (Arg1 || DerefOf (PAUI [0x05]))
            M600 (Arg0, 0x06, Local0, Ones)
            Local0 = (Arg1 || DerefOf (PAUI [0x06]))
            M600 (Arg0, 0x07, Local0, Ones)
            /* Method returns Integer */

            Local0 = (Arg1 || M601 (0x01, 0x05))
            M600 (Arg0, 0x08, Local0, Ones)
            Local0 = (Arg1 || M601 (0x01, 0x06))
            M600 (Arg0, 0x09, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (Arg1 || DerefOf (M602 (0x01, 0x05, 0x01)))
                M600 (Arg0, 0x0A, Local0, Ones)
                Local0 = (Arg1 || DerefOf (M602 (0x01, 0x06, 0x01)))
                M600 (Arg0, 0x0B, Local0, Ones)
            }

            /* Conversion of the second operand */

            Local0 = (0x00 || Arg1)
            M600 (Arg0, 0x0C, Local0, Ones)
            Local0 = (0x01 || Arg1)
            M600 (Arg0, 0x0D, Local0, Ones)
            Local0 = (AUI5 || Arg1)
            M600 (Arg0, 0x0E, Local0, Ones)
            Local0 = (AUI6 || Arg1)
            M600 (Arg0, 0x0F, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI5)) || Arg1)
                M600 (Arg0, 0x10, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUI6)) || Arg1)
                M600 (Arg0, 0x11, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x05]) || Arg1)
            M600 (Arg0, 0x12, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x06]) || Arg1)
            M600 (Arg0, 0x13, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x05) || Arg1)
            M600 (Arg0, 0x14, Local0, Ones)
            Local0 = (M601 (0x01, 0x06) || Arg1)
            M600 (Arg0, 0x15, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x05, 0x01)) || Arg1)
                M600 (Arg0, 0x16, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x06, 0x01)) || Arg1)
                M600 (Arg0, 0x17, Local0, Ones)
            }

            /* Conversion of the both operands */

            Local0 = (Arg2 || Arg1)
            M600 (Arg0, 0x18, Local0, Ones)
            Local0 = (Arg1 || Arg2)
            M600 (Arg0, 0x19, Local0, Ones)
        }

        Method (M64O, 1, NotSerialized)
        {
            /* LAnd */

            Concatenate (Arg0, "-m05f", Local0)
            SRMT (Local0)
            M05F (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                })
            Concatenate (Arg0, "-m060", Local0)
            SRMT (Local0)
            M060 (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
            /* LOr */

            Concatenate (Arg0, "-m062", Local0)
            SRMT (Local0)
            M062 (Local0, Buffer (0x01)
                {
                     0x00                                             // .
                })
            Concatenate (Arg0, "-m063", Local0)
            SRMT (Local0)
            M063 (Local0, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                }, Buffer (0x01)
                {
                     0x00                                             // .
                })
        }

        Method (M32O, 1, NotSerialized)
        {
            /* LAnd */

            Concatenate (Arg0, "-m05f", Local0)
            SRMT (Local0)
            M05F (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                })
            Concatenate (Arg0, "-m061", Local0)
            SRMT (Local0)
            M061 (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
            /* LOr */

            Concatenate (Arg0, "-m062", Local0)
            SRMT (Local0)
            M062 (Local0, Buffer (0x01)
                {
                     0x00                                             // .
                })
            Concatenate (Arg0, "-m064", Local0)
            SRMT (Local0)
            M064 (Local0, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                }, Buffer (0x01)
                {
                     0x00                                             // .
                })
        }

        /* Buffer to Integer conversion of the Buffer second operand of */
        /* Logical operators when the first operand is evaluated as Integer */
        /* (LEqual, LGreater, LGreaterEqual, LLess, LLessEqual, LNotEqual) */
        Method (M64P, 2, NotSerialized)
        {
            /* LEqual */

            Local0 = (0xFE7CB391D650A284 == Arg1)
            M600 (Arg0, 0x00, Local0, Ones)
            Local0 = (0xFE7CB391D650A285 == Arg1)
            M600 (Arg0, 0x01, Local0, Zero)
            Local0 = (0xFE7CB391D650A283 == Arg1)
            M600 (Arg0, 0x02, Local0, Zero)
            Local0 = (AUI4 == Arg1)
            M600 (Arg0, 0x03, Local0, Ones)
            Local0 = (AUID == Arg1)
            M600 (Arg0, 0x04, Local0, Zero)
            Local0 = (AUIF == Arg1)
            M600 (Arg0, 0x05, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI4)) == Arg1)
                M600 (Arg0, 0x06, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUID)) == Arg1)
                M600 (Arg0, 0x07, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIF)) == Arg1)
                M600 (Arg0, 0x08, Local0, Zero)
            }

            Local0 = (DerefOf (PAUI [0x04]) == Arg1)
            M600 (Arg0, 0x09, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x0D]) == Arg1)
            M600 (Arg0, 0x0A, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x0F]) == Arg1)
            M600 (Arg0, 0x0B, Local0, Zero)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x04) == Arg1)
            M600 (Arg0, 0x0C, Local0, Ones)
            Local0 = (M601 (0x01, 0x0D) == Arg1)
            M600 (Arg0, 0x0D, Local0, Zero)
            Local0 = (M601 (0x01, 0x0F) == Arg1)
            M600 (Arg0, 0x0E, Local0, Zero)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x04, 0x01)) == Arg1)
                M600 (Arg0, 0x0F, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x0D, 0x01)) == Arg1)
                M600 (Arg0, 0x10, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x0F, 0x01)) == Arg1)
                M600 (Arg0, 0x11, Local0, Zero)
            }

            /* LGreater */

            Local0 = (0xFE7CB391D650A284 > Arg1)
            M600 (Arg0, 0x12, Local0, Zero)
            Local0 = (0xFE7CB391D650A285 > Arg1)
            M600 (Arg0, 0x13, Local0, Ones)
            Local0 = (0xFE7CB391D650A283 > Arg1)
            M600 (Arg0, 0x14, Local0, Zero)
            Local0 = (AUI4 > Arg1)
            M600 (Arg0, 0x15, Local0, Zero)
            Local0 = (AUID > Arg1)
            M600 (Arg0, 0x16, Local0, Ones)
            Local0 = (AUIF > Arg1)
            M600 (Arg0, 0x17, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI4)) > Arg1)
                M600 (Arg0, 0x18, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUID)) > Arg1)
                M600 (Arg0, 0x19, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIF)) > Arg1)
                M600 (Arg0, 0x1A, Local0, Zero)
            }

            Local0 = (DerefOf (PAUI [0x04]) > Arg1)
            M600 (Arg0, 0x1B, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x0D]) > Arg1)
            M600 (Arg0, 0x1C, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x0F]) > Arg1)
            M600 (Arg0, 0x1D, Local0, Zero)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x04) > Arg1)
            M600 (Arg0, 0x1E, Local0, Zero)
            Local0 = (M601 (0x01, 0x0D) > Arg1)
            M600 (Arg0, 0x1F, Local0, Ones)
            Local0 = (M601 (0x01, 0x0F) > Arg1)
            M600 (Arg0, 0x20, Local0, Zero)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x04, 0x01)) > Arg1)
                M600 (Arg0, 0x21, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x0D, 0x01)) > Arg1)
                M600 (Arg0, 0x22, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x0F, 0x01)) > Arg1)
                M600 (Arg0, 0x23, Local0, Zero)
            }

            /* LGreaterEqual */

            Local0 = (0xFE7CB391D650A284 >= Arg1)
            M600 (Arg0, 0x24, Local0, Ones)
            Local0 = (0xFE7CB391D650A285 >= Arg1)
            M600 (Arg0, 0x25, Local0, Ones)
            Local0 = (0xFE7CB391D650A283 >= Arg1)
            M600 (Arg0, 0x26, Local0, Zero)
            Local0 = (AUI4 >= Arg1)
            M600 (Arg0, 0x27, Local0, Ones)
            Local0 = (AUID >= Arg1)
            M600 (Arg0, 0x28, Local0, Ones)
            Local0 = (AUIF >= Arg1)
            M600 (Arg0, 0x29, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI4)) >= Arg1)
                M600 (Arg0, 0x2A, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUID)) >= Arg1)
                M600 (Arg0, 0x2B, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIF)) >= Arg1)
                M600 (Arg0, 0x2C, Local0, Zero)
            }

            Local0 = (DerefOf (PAUI [0x04]) >= Arg1)
            M600 (Arg0, 0x2D, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x0D]) >= Arg1)
            M600 (Arg0, 0x2E, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x0F]) >= Arg1)
            M600 (Arg0, 0x2F, Local0, Zero)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x04) >= Arg1)
            M600 (Arg0, 0x30, Local0, Ones)
            Local0 = (M601 (0x01, 0x0D) >= Arg1)
            M600 (Arg0, 0x31, Local0, Ones)
            Local0 = (M601 (0x01, 0x0F) >= Arg1)
            M600 (Arg0, 0x32, Local0, Zero)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x04, 0x01)) >= Arg1)
                M600 (Arg0, 0x33, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x0D, 0x01)) >= Arg1)
                M600 (Arg0, 0x34, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x0F, 0x01)) >= Arg1)
                M600 (Arg0, 0x35, Local0, Zero)
            }

            /* LLess */

            Local0 = (0xFE7CB391D650A284 < Arg1)
            M600 (Arg0, 0x36, Local0, Zero)
            Local0 = (0xFE7CB391D650A285 < Arg1)
            M600 (Arg0, 0x37, Local0, Zero)
            Local0 = (0xFE7CB391D650A283 < Arg1)
            M600 (Arg0, 0x38, Local0, Ones)
            Local0 = (AUI4 < Arg1)
            M600 (Arg0, 0x39, Local0, Zero)
            Local0 = (AUID < Arg1)
            M600 (Arg0, 0x3A, Local0, Zero)
            Local0 = (AUIF < Arg1)
            M600 (Arg0, 0x3B, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI4)) < Arg1)
                M600 (Arg0, 0x3C, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUID)) < Arg1)
                M600 (Arg0, 0x3D, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIF)) < Arg1)
                M600 (Arg0, 0x3E, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x04]) < Arg1)
            M600 (Arg0, 0x3F, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x0D]) < Arg1)
            M600 (Arg0, 0x40, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x0F]) < Arg1)
            M600 (Arg0, 0x41, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x04) < Arg1)
            M600 (Arg0, 0x42, Local0, Zero)
            Local0 = (M601 (0x01, 0x0D) < Arg1)
            M600 (Arg0, 0x43, Local0, Zero)
            Local0 = (M601 (0x01, 0x0F) < Arg1)
            M600 (Arg0, 0x44, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x04, 0x01)) < Arg1)
                M600 (Arg0, 0x45, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x0D, 0x01)) < Arg1)
                M600 (Arg0, 0x46, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x0F, 0x01)) < Arg1)
                M600 (Arg0, 0x47, Local0, Ones)
            }

            /* LLessEqual */

            Local0 = (0xFE7CB391D650A284 <= Arg1)
            M600 (Arg0, 0x48, Local0, Ones)
            Local0 = (0xFE7CB391D650A285 <= Arg1)
            M600 (Arg0, 0x49, Local0, Zero)
            Local0 = (0xFE7CB391D650A283 <= Arg1)
            M600 (Arg0, 0x4A, Local0, Ones)
            Local0 = (AUI4 <= Arg1)
            M600 (Arg0, 0x4B, Local0, Ones)
            Local0 = (AUID <= Arg1)
            M600 (Arg0, 0x4C, Local0, Zero)
            Local0 = (AUIF <= Arg1)
            M600 (Arg0, 0x4D, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI4)) <= Arg1)
                M600 (Arg0, 0x4E, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUID)) <= Arg1)
                M600 (Arg0, 0x4F, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIF)) <= Arg1)
                M600 (Arg0, 0x50, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x04]) <= Arg1)
            M600 (Arg0, 0x51, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x0D]) <= Arg1)
            M600 (Arg0, 0x52, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x0F]) <= Arg1)
            M600 (Arg0, 0x53, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x04) <= Arg1)
            M600 (Arg0, 0x54, Local0, Ones)
            Local0 = (M601 (0x01, 0x0D) <= Arg1)
            M600 (Arg0, 0x55, Local0, Zero)
            Local0 = (M601 (0x01, 0x0F) <= Arg1)
            M600 (Arg0, 0x56, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x04, 0x01)) <= Arg1)
                M600 (Arg0, 0x57, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x0D, 0x01)) <= Arg1)
                M600 (Arg0, 0x58, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x0F, 0x01)) <= Arg1)
                M600 (Arg0, 0x59, Local0, Ones)
            }

            /* LNotEqual */

            Local0 = (0xFE7CB391D650A284 != Arg1)
            M600 (Arg0, 0x5A, Local0, Zero)
            Local0 = (0xFE7CB391D650A285 != Arg1)
            M600 (Arg0, 0x5B, Local0, Ones)
            Local0 = (0xFE7CB391D650A283 != Arg1)
            M600 (Arg0, 0x5C, Local0, Ones)
            Local0 = (AUI4 != Arg1)
            M600 (Arg0, 0x5D, Local0, Zero)
            Local0 = (AUID != Arg1)
            M600 (Arg0, 0x5E, Local0, Ones)
            Local0 = (AUIF != Arg1)
            M600 (Arg0, 0x5F, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI4)) != Arg1)
                M600 (Arg0, 0x60, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUID)) != Arg1)
                M600 (Arg0, 0x61, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIF)) != Arg1)
                M600 (Arg0, 0x62, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x04]) != Arg1)
            M600 (Arg0, 0x63, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x0D]) != Arg1)
            M600 (Arg0, 0x64, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x0F]) != Arg1)
            M600 (Arg0, 0x65, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x04) != Arg1)
            M600 (Arg0, 0x66, Local0, Zero)
            Local0 = (M601 (0x01, 0x0D) != Arg1)
            M600 (Arg0, 0x67, Local0, Ones)
            Local0 = (M601 (0x01, 0x0F) != Arg1)
            M600 (Arg0, 0x68, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x04, 0x01)) != Arg1)
                M600 (Arg0, 0x69, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x0D, 0x01)) != Arg1)
                M600 (Arg0, 0x6A, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x0F, 0x01)) != Arg1)
                M600 (Arg0, 0x6B, Local0, Ones)
            }
        }

        Method (M32P, 2, NotSerialized)
        {
            /* LEqual */

            Local0 = (0xD650A284 == Arg1)
            M600 (Arg0, 0x00, Local0, Ones)
            Local0 = (0xD650A285 == Arg1)
            M600 (Arg0, 0x01, Local0, Zero)
            Local0 = (0xD650A283 == Arg1)
            M600 (Arg0, 0x02, Local0, Zero)
            Local0 = (AUIK == Arg1)
            M600 (Arg0, 0x03, Local0, Ones)
            Local0 = (AUIL == Arg1)
            M600 (Arg0, 0x04, Local0, Zero)
            Local0 = (AUIM == Arg1)
            M600 (Arg0, 0x05, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUIK)) == Arg1)
                M600 (Arg0, 0x06, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIL)) == Arg1)
                M600 (Arg0, 0x07, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIM)) == Arg1)
                M600 (Arg0, 0x08, Local0, Zero)
            }

            Local0 = (DerefOf (PAUI [0x14]) == Arg1)
            M600 (Arg0, 0x09, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x15]) == Arg1)
            M600 (Arg0, 0x0A, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x16]) == Arg1)
            M600 (Arg0, 0x0B, Local0, Zero)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x14) == Arg1)
            M600 (Arg0, 0x0C, Local0, Ones)
            Local0 = (M601 (0x01, 0x15) == Arg1)
            M600 (Arg0, 0x0D, Local0, Zero)
            Local0 = (M601 (0x01, 0x16) == Arg1)
            M600 (Arg0, 0x0E, Local0, Zero)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x14, 0x01)) == Arg1)
                M600 (Arg0, 0x0F, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x15, 0x01)) == Arg1)
                M600 (Arg0, 0x10, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x16, 0x01)) == Arg1)
                M600 (Arg0, 0x11, Local0, Zero)
            }

            /* LGreater */

            Local0 = (0xD650A284 > Arg1)
            M600 (Arg0, 0x12, Local0, Zero)
            Local0 = (0xD650A285 > Arg1)
            M600 (Arg0, 0x13, Local0, Ones)
            Local0 = (0xD650A283 > Arg1)
            M600 (Arg0, 0x14, Local0, Zero)
            Local0 = (AUIK > Arg1)
            M600 (Arg0, 0x15, Local0, Zero)
            Local0 = (AUIL > Arg1)
            M600 (Arg0, 0x16, Local0, Ones)
            Local0 = (AUIM > Arg1)
            M600 (Arg0, 0x17, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUIK)) > Arg1)
                M600 (Arg0, 0x18, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIL)) > Arg1)
                M600 (Arg0, 0x19, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIM)) > Arg1)
                M600 (Arg0, 0x1A, Local0, Zero)
            }

            Local0 = (DerefOf (PAUI [0x14]) > Arg1)
            M600 (Arg0, 0x1B, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x15]) > Arg1)
            M600 (Arg0, 0x1C, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x16]) > Arg1)
            M600 (Arg0, 0x1D, Local0, Zero)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x14) > Arg1)
            M600 (Arg0, 0x1E, Local0, Zero)
            Local0 = (M601 (0x01, 0x15) > Arg1)
            M600 (Arg0, 0x1F, Local0, Ones)
            Local0 = (M601 (0x01, 0x16) > Arg1)
            M600 (Arg0, 0x20, Local0, Zero)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x14, 0x01)) > Arg1)
                M600 (Arg0, 0x21, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x15, 0x01)) > Arg1)
                M600 (Arg0, 0x22, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x16, 0x01)) > Arg1)
                M600 (Arg0, 0x23, Local0, Zero)
            }

            /* LGreaterEqual */

            Local0 = (0xD650A284 >= Arg1)
            M600 (Arg0, 0x24, Local0, Ones)
            Local0 = (0xD650A285 >= Arg1)
            M600 (Arg0, 0x25, Local0, Ones)
            Local0 = (0xD650A283 >= Arg1)
            M600 (Arg0, 0x26, Local0, Zero)
            Local0 = (AUIK >= Arg1)
            M600 (Arg0, 0x27, Local0, Ones)
            Local0 = (AUIL >= Arg1)
            M600 (Arg0, 0x28, Local0, Ones)
            Local0 = (AUIM >= Arg1)
            M600 (Arg0, 0x29, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUIK)) >= Arg1)
                M600 (Arg0, 0x2A, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIL)) >= Arg1)
                M600 (Arg0, 0x2B, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIM)) >= Arg1)
                M600 (Arg0, 0x2C, Local0, Zero)
            }

            Local0 = (DerefOf (PAUI [0x14]) >= Arg1)
            M600 (Arg0, 0x2D, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x15]) >= Arg1)
            M600 (Arg0, 0x2E, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x16]) >= Arg1)
            M600 (Arg0, 0x2F, Local0, Zero)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x14) >= Arg1)
            M600 (Arg0, 0x30, Local0, Ones)
            Local0 = (M601 (0x01, 0x15) >= Arg1)
            M600 (Arg0, 0x31, Local0, Ones)
            Local0 = (M601 (0x01, 0x16) >= Arg1)
            M600 (Arg0, 0x32, Local0, Zero)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x14, 0x01)) >= Arg1)
                M600 (Arg0, 0x33, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x15, 0x01)) >= Arg1)
                M600 (Arg0, 0x34, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x16, 0x01)) >= Arg1)
                M600 (Arg0, 0x35, Local0, Zero)
            }

            /* LLess */

            Local0 = (0xD650A284 < Arg1)
            M600 (Arg0, 0x36, Local0, Zero)
            Local0 = (0xD650A285 < Arg1)
            M600 (Arg0, 0x37, Local0, Zero)
            Local0 = (0xD650A283 < Arg1)
            M600 (Arg0, 0x38, Local0, Ones)
            Local0 = (AUIK < Arg1)
            M600 (Arg0, 0x39, Local0, Zero)
            Local0 = (AUIL < Arg1)
            M600 (Arg0, 0x3A, Local0, Zero)
            Local0 = (AUIM < Arg1)
            M600 (Arg0, 0x3B, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUIK)) < Arg1)
                M600 (Arg0, 0x3C, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIL)) < Arg1)
                M600 (Arg0, 0x3D, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIM)) < Arg1)
                M600 (Arg0, 0x3E, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x14]) < Arg1)
            M600 (Arg0, 0x3F, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x15]) < Arg1)
            M600 (Arg0, 0x40, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x16]) < Arg1)
            M600 (Arg0, 0x41, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x14) < Arg1)
            M600 (Arg0, 0x42, Local0, Zero)
            Local0 = (M601 (0x01, 0x15) < Arg1)
            M600 (Arg0, 0x43, Local0, Zero)
            Local0 = (M601 (0x01, 0x16) < Arg1)
            M600 (Arg0, 0x44, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x14, 0x01)) < Arg1)
                M600 (Arg0, 0x45, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x15, 0x01)) < Arg1)
                M600 (Arg0, 0x46, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x16, 0x01)) < Arg1)
                M600 (Arg0, 0x47, Local0, Ones)
            }

            /* LLessEqual */

            Local0 = (0xD650A284 <= Arg1)
            M600 (Arg0, 0x48, Local0, Ones)
            Local0 = (0xD650A285 <= Arg1)
            M600 (Arg0, 0x49, Local0, Zero)
            Local0 = (0xD650A283 <= Arg1)
            M600 (Arg0, 0x4A, Local0, Ones)
            Local0 = (AUIK <= Arg1)
            M600 (Arg0, 0x4B, Local0, Ones)
            Local0 = (AUIL <= Arg1)
            M600 (Arg0, 0x4C, Local0, Zero)
            Local0 = (AUIM <= Arg1)
            M600 (Arg0, 0x4D, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUIK)) <= Arg1)
                M600 (Arg0, 0x4E, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIL)) <= Arg1)
                M600 (Arg0, 0x4F, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIM)) <= Arg1)
                M600 (Arg0, 0x50, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x14]) <= Arg1)
            M600 (Arg0, 0x51, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x15]) <= Arg1)
            M600 (Arg0, 0x52, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x16]) <= Arg1)
            M600 (Arg0, 0x53, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x14) <= Arg1)
            M600 (Arg0, 0x54, Local0, Ones)
            Local0 = (M601 (0x01, 0x15) <= Arg1)
            M600 (Arg0, 0x55, Local0, Zero)
            Local0 = (M601 (0x01, 0x16) <= Arg1)
            M600 (Arg0, 0x56, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x14, 0x01)) <= Arg1)
                M600 (Arg0, 0x57, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x15, 0x01)) <= Arg1)
                M600 (Arg0, 0x58, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x16, 0x01)) <= Arg1)
                M600 (Arg0, 0x59, Local0, Ones)
            }

            /* LNotEqual */

            Local0 = (0xD650A284 != Arg1)
            M600 (Arg0, 0x5A, Local0, Zero)
            Local0 = (0xD650A285 != Arg1)
            M600 (Arg0, 0x5B, Local0, Ones)
            Local0 = (0xD650A283 != Arg1)
            M600 (Arg0, 0x5C, Local0, Ones)
            Local0 = (AUIK != Arg1)
            M600 (Arg0, 0x5D, Local0, Zero)
            Local0 = (AUIL != Arg1)
            M600 (Arg0, 0x5E, Local0, Ones)
            Local0 = (AUIM != Arg1)
            M600 (Arg0, 0x5F, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUIK)) != Arg1)
                M600 (Arg0, 0x60, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIL)) != Arg1)
                M600 (Arg0, 0x61, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIM)) != Arg1)
                M600 (Arg0, 0x62, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x14]) != Arg1)
            M600 (Arg0, 0x63, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x15]) != Arg1)
            M600 (Arg0, 0x64, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x16]) != Arg1)
            M600 (Arg0, 0x65, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x14) != Arg1)
            M600 (Arg0, 0x66, Local0, Zero)
            Local0 = (M601 (0x01, 0x15) != Arg1)
            M600 (Arg0, 0x67, Local0, Ones)
            Local0 = (M601 (0x01, 0x16) != Arg1)
            M600 (Arg0, 0x68, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x14, 0x01)) != Arg1)
                M600 (Arg0, 0x69, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x15, 0x01)) != Arg1)
                M600 (Arg0, 0x6A, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x16, 0x01)) != Arg1)
                M600 (Arg0, 0x6B, Local0, Ones)
            }
        }

        Method (M065, 2, NotSerialized)
        {
            /* LEqual */

            Local0 = (0x0321 == Arg1)
            M600 (Arg0, 0x00, Local0, Ones)
            Local0 = (0x0322 == Arg1)
            M600 (Arg0, 0x01, Local0, Zero)
            Local0 = (0x0320 == Arg1)
            M600 (Arg0, 0x02, Local0, Zero)
            Local0 = (AUI1 == Arg1)
            M600 (Arg0, 0x03, Local0, Ones)
            Local0 = (AUIG == Arg1)
            M600 (Arg0, 0x04, Local0, Zero)
            Local0 = (AUIH == Arg1)
            M600 (Arg0, 0x05, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI1)) == Arg1)
                M600 (Arg0, 0x06, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIG)) == Arg1)
                M600 (Arg0, 0x07, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIH)) == Arg1)
                M600 (Arg0, 0x08, Local0, Zero)
            }

            Local0 = (DerefOf (PAUI [0x01]) == Arg1)
            M600 (Arg0, 0x09, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x10]) == Arg1)
            M600 (Arg0, 0x0A, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x11]) == Arg1)
            M600 (Arg0, 0x0B, Local0, Zero)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x01) == Arg1)
            M600 (Arg0, 0x0C, Local0, Ones)
            Local0 = (M601 (0x01, 0x10) == Arg1)
            M600 (Arg0, 0x0D, Local0, Zero)
            Local0 = (M601 (0x01, 0x11) == Arg1)
            M600 (Arg0, 0x0E, Local0, Zero)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x01, 0x01)) == Arg1)
                M600 (Arg0, 0x0F, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x10, 0x01)) == Arg1)
                M600 (Arg0, 0x10, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x11, 0x01)) == Arg1)
                M600 (Arg0, 0x11, Local0, Zero)
            }

            /* LGreater */

            Local0 = (0x0321 > Arg1)
            M600 (Arg0, 0x12, Local0, Zero)
            Local0 = (0x0322 > Arg1)
            M600 (Arg0, 0x13, Local0, Ones)
            Local0 = (0x0320 > Arg1)
            M600 (Arg0, 0x14, Local0, Zero)
            Local0 = (AUI1 > Arg1)
            M600 (Arg0, 0x15, Local0, Zero)
            Local0 = (AUIG > Arg1)
            M600 (Arg0, 0x16, Local0, Ones)
            Local0 = (AUIH > Arg1)
            M600 (Arg0, 0x17, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI1)) > Arg1)
                M600 (Arg0, 0x18, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIG)) > Arg1)
                M600 (Arg0, 0x19, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIH)) > Arg1)
                M600 (Arg0, 0x1A, Local0, Zero)
            }

            Local0 = (DerefOf (PAUI [0x01]) > Arg1)
            M600 (Arg0, 0x1B, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x10]) > Arg1)
            M600 (Arg0, 0x1C, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x11]) > Arg1)
            M600 (Arg0, 0x1D, Local0, Zero)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x01) > Arg1)
            M600 (Arg0, 0x1E, Local0, Zero)
            Local0 = (M601 (0x01, 0x10) > Arg1)
            M600 (Arg0, 0x1F, Local0, Ones)
            Local0 = (M601 (0x01, 0x11) > Arg1)
            M600 (Arg0, 0x20, Local0, Zero)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x01, 0x01)) > Arg1)
                M600 (Arg0, 0x21, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x10, 0x01)) > Arg1)
                M600 (Arg0, 0x22, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x11, 0x01)) > Arg1)
                M600 (Arg0, 0x23, Local0, Zero)
            }

            /* LGreaterEqual */

            Local0 = (0x0321 >= Arg1)
            M600 (Arg0, 0x24, Local0, Ones)
            Local0 = (0x0322 >= Arg1)
            M600 (Arg0, 0x25, Local0, Ones)
            Local0 = (0x0320 >= Arg1)
            M600 (Arg0, 0x26, Local0, Zero)
            Local0 = (AUI1 >= Arg1)
            M600 (Arg0, 0x27, Local0, Ones)
            Local0 = (AUIG >= Arg1)
            M600 (Arg0, 0x28, Local0, Ones)
            Local0 = (AUIH >= Arg1)
            M600 (Arg0, 0x29, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI1)) >= Arg1)
                M600 (Arg0, 0x2A, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIG)) >= Arg1)
                M600 (Arg0, 0x2B, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIH)) >= Arg1)
                M600 (Arg0, 0x2C, Local0, Zero)
            }

            Local0 = (DerefOf (PAUI [0x01]) >= Arg1)
            M600 (Arg0, 0x2D, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x10]) >= Arg1)
            M600 (Arg0, 0x2E, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x11]) >= Arg1)
            M600 (Arg0, 0x2F, Local0, Zero)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x01) >= Arg1)
            M600 (Arg0, 0x30, Local0, Ones)
            Local0 = (M601 (0x01, 0x10) >= Arg1)
            M600 (Arg0, 0x31, Local0, Ones)
            Local0 = (M601 (0x01, 0x11) >= Arg1)
            M600 (Arg0, 0x32, Local0, Zero)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x01, 0x01)) >= Arg1)
                M600 (Arg0, 0x33, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x10, 0x01)) >= Arg1)
                M600 (Arg0, 0x34, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x11, 0x01)) >= Arg1)
                M600 (Arg0, 0x35, Local0, Zero)
            }

            /* LLess */

            Local0 = (0x0321 < Arg1)
            M600 (Arg0, 0x36, Local0, Zero)
            Local0 = (0x0322 < Arg1)
            M600 (Arg0, 0x37, Local0, Zero)
            Local0 = (0x0320 < Arg1)
            M600 (Arg0, 0x38, Local0, Ones)
            Local0 = (AUI1 < Arg1)
            M600 (Arg0, 0x39, Local0, Zero)
            Local0 = (AUIG < Arg1)
            M600 (Arg0, 0x3A, Local0, Zero)
            Local0 = (AUIH < Arg1)
            M600 (Arg0, 0x3B, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI1)) < Arg1)
                M600 (Arg0, 0x3C, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIG)) < Arg1)
                M600 (Arg0, 0x3D, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIH)) < Arg1)
                M600 (Arg0, 0x3E, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x01]) < Arg1)
            M600 (Arg0, 0x3F, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x10]) < Arg1)
            M600 (Arg0, 0x40, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x11]) < Arg1)
            M600 (Arg0, 0x41, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x01) < Arg1)
            M600 (Arg0, 0x42, Local0, Zero)
            Local0 = (M601 (0x01, 0x10) < Arg1)
            M600 (Arg0, 0x43, Local0, Zero)
            Local0 = (M601 (0x01, 0x11) < Arg1)
            M600 (Arg0, 0x44, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x01, 0x01)) < Arg1)
                M600 (Arg0, 0x45, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x10, 0x01)) < Arg1)
                M600 (Arg0, 0x46, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x11, 0x01)) < Arg1)
                M600 (Arg0, 0x47, Local0, Ones)
            }

            /* LLessEqual */

            Local0 = (0x0321 <= Arg1)
            M600 (Arg0, 0x48, Local0, Ones)
            Local0 = (0x0322 <= Arg1)
            M600 (Arg0, 0x49, Local0, Zero)
            Local0 = (0x0320 <= Arg1)
            M600 (Arg0, 0x4A, Local0, Ones)
            Local0 = (AUI1 <= Arg1)
            M600 (Arg0, 0x4B, Local0, Ones)
            Local0 = (AUIG <= Arg1)
            M600 (Arg0, 0x4C, Local0, Zero)
            Local0 = (AUIH <= Arg1)
            M600 (Arg0, 0x4D, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI1)) <= Arg1)
                M600 (Arg0, 0x4E, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIG)) <= Arg1)
                M600 (Arg0, 0x4F, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIH)) <= Arg1)
                M600 (Arg0, 0x50, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x01]) <= Arg1)
            M600 (Arg0, 0x51, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x10]) <= Arg1)
            M600 (Arg0, 0x52, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x11]) <= Arg1)
            M600 (Arg0, 0x53, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x01) <= Arg1)
            M600 (Arg0, 0x54, Local0, Ones)
            Local0 = (M601 (0x01, 0x10) <= Arg1)
            M600 (Arg0, 0x55, Local0, Zero)
            Local0 = (M601 (0x01, 0x11) <= Arg1)
            M600 (Arg0, 0x56, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x01, 0x01)) <= Arg1)
                M600 (Arg0, 0x57, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x10, 0x01)) <= Arg1)
                M600 (Arg0, 0x58, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x11, 0x01)) <= Arg1)
                M600 (Arg0, 0x59, Local0, Ones)
            }

            /* LNotEqual */

            Local0 = (0x0321 != Arg1)
            M600 (Arg0, 0x5A, Local0, Zero)
            Local0 = (0x0322 != Arg1)
            M600 (Arg0, 0x5B, Local0, Ones)
            Local0 = (0x0320 != Arg1)
            M600 (Arg0, 0x5C, Local0, Ones)
            Local0 = (AUI1 != Arg1)
            M600 (Arg0, 0x5D, Local0, Zero)
            Local0 = (AUIG != Arg1)
            M600 (Arg0, 0x5E, Local0, Ones)
            Local0 = (AUIH != Arg1)
            M600 (Arg0, 0x5F, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUI1)) != Arg1)
                M600 (Arg0, 0x60, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUIG)) != Arg1)
                M600 (Arg0, 0x61, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUIH)) != Arg1)
                M600 (Arg0, 0x62, Local0, Ones)
            }

            Local0 = (DerefOf (PAUI [0x01]) != Arg1)
            M600 (Arg0, 0x63, Local0, Zero)
            Local0 = (DerefOf (PAUI [0x10]) != Arg1)
            M600 (Arg0, 0x64, Local0, Ones)
            Local0 = (DerefOf (PAUI [0x11]) != Arg1)
            M600 (Arg0, 0x65, Local0, Ones)
            /* Method returns Integer */

            Local0 = (M601 (0x01, 0x01) != Arg1)
            M600 (Arg0, 0x66, Local0, Zero)
            Local0 = (M601 (0x01, 0x10) != Arg1)
            M600 (Arg0, 0x67, Local0, Ones)
            Local0 = (M601 (0x01, 0x11) != Arg1)
            M600 (Arg0, 0x68, Local0, Ones)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x01, 0x01, 0x01)) != Arg1)
                M600 (Arg0, 0x69, Local0, Zero)
                Local0 = (DerefOf (M602 (0x01, 0x10, 0x01)) != Arg1)
                M600 (Arg0, 0x6A, Local0, Ones)
                Local0 = (DerefOf (M602 (0x01, 0x11, 0x01)) != Arg1)
                M600 (Arg0, 0x6B, Local0, Ones)
            }
        }

        /* Buffer to Integer intermediate conversion of the Buffer second */
        /* operand of Concatenate operator in case the first one is Integer */
        Method (M64Q, 3, NotSerialized)
        {
            Local0 = Concatenate (0x0321, Arg1)
            M600 (Arg0, 0x00, Local0, BB26)
            Local0 = Concatenate (0x0321, Arg2)
            M600 (Arg0, 0x01, Local0, BB21)
            Local0 = Concatenate (AUI1, Arg1)
            M600 (Arg0, 0x02, Local0, BB26)
            Local0 = Concatenate (AUI1, Arg2)
            M600 (Arg0, 0x03, Local0, BB21)
            If (Y078)
            {
                Local0 = Concatenate (DerefOf (RefOf (AUI1)), Arg1)
                M600 (Arg0, 0x04, Local0, BB26)
                Local0 = Concatenate (DerefOf (RefOf (AUI1)), Arg2)
                M600 (Arg0, 0x05, Local0, BB21)
            }

            Local0 = Concatenate (DerefOf (PAUI [0x01]), Arg1)
            M600 (Arg0, 0x06, Local0, BB26)
            Local0 = Concatenate (DerefOf (PAUI [0x01]), Arg2)
            M600 (Arg0, 0x07, Local0, BB21)
            /* Method returns Integer */

            Local0 = Concatenate (M601 (0x01, 0x01), Arg1)
            M600 (Arg0, 0x08, Local0, BB26)
            Local0 = Concatenate (M601 (0x01, 0x01), Arg2)
            M600 (Arg0, 0x09, Local0, BB21)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = Concatenate (DerefOf (M602 (0x01, 0x01, 0x01)), Arg1)
                M600 (Arg0, 0x0A, Local0, BB26)
                Local0 = Concatenate (DerefOf (M602 (0x01, 0x01, 0x01)), Arg2)
                M600 (Arg0, 0x0B, Local0, BB21)
            }

            Concatenate (0x0321, Arg1, Local0)
            M600 (Arg0, 0x0C, Local0, BB26)
            Concatenate (0x0321, Arg2, Local0)
            M600 (Arg0, 0x0D, Local0, BB21)
            Concatenate (AUI1, Arg1, Local0)
            M600 (Arg0, 0x0E, Local0, BB26)
            Concatenate (AUI1, Arg2, Local0)
            M600 (Arg0, 0x0F, Local0, BB21)
            If (Y078)
            {
                Concatenate (DerefOf (RefOf (AUI1)), Arg1, Local0)
                M600 (Arg0, 0x10, Local0, BB26)
                Concatenate (DerefOf (RefOf (AUI1)), Arg2, Local0)
                M600 (Arg0, 0x11, Local0, BB21)
            }

            Concatenate (DerefOf (PAUI [0x01]), Arg1, Local0)
            M600 (Arg0, 0x12, Local0, BB26)
            Concatenate (DerefOf (PAUI [0x01]), Arg2, Local0)
            M600 (Arg0, 0x13, Local0, BB21)
            /* Method returns Integer */

            Concatenate (M601 (0x01, 0x01), Arg1, Local0)
            M600 (Arg0, 0x14, Local0, BB26)
            Concatenate (M601 (0x01, 0x01), Arg2, Local0)
            M600 (Arg0, 0x15, Local0, BB21)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Concatenate (DerefOf (M602 (0x01, 0x01, 0x01)), Arg1, Local0)
                M600 (Arg0, 0x16, Local0, BB26)
                Concatenate (DerefOf (M602 (0x01, 0x01, 0x01)), Arg2, Local0)
                M600 (Arg0, 0x17, Local0, BB21)
            }
        }

        Method (M32Q, 3, NotSerialized)
        {
            Local0 = Concatenate (0x0321, Arg1)
            M600 (Arg0, 0x00, Local0, BB27)
            Local0 = Concatenate (0x0321, Arg2)
            M600 (Arg0, 0x01, Local0, BB28)
            Local0 = Concatenate (AUI1, Arg1)
            M600 (Arg0, 0x02, Local0, BB27)
            Local0 = Concatenate (AUI1, Arg2)
            M600 (Arg0, 0x03, Local0, BB28)
            If (Y078)
            {
                Local0 = Concatenate (DerefOf (RefOf (AUI1)), Arg1)
                M600 (Arg0, 0x04, Local0, BB27)
                Local0 = Concatenate (DerefOf (RefOf (AUI1)), Arg2)
                M600 (Arg0, 0x05, Local0, BB28)
            }

            Local0 = Concatenate (DerefOf (PAUI [0x01]), Arg1)
            M600 (Arg0, 0x06, Local0, BB27)
            Local0 = Concatenate (DerefOf (PAUI [0x01]), Arg2)
            M600 (Arg0, 0x07, Local0, BB28)
            /* Method returns Integer */

            Local0 = Concatenate (M601 (0x01, 0x01), Arg1)
            M600 (Arg0, 0x08, Local0, BB27)
            Local0 = Concatenate (M601 (0x01, 0x01), Arg2)
            M600 (Arg0, 0x09, Local0, BB28)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Local0 = Concatenate (DerefOf (M602 (0x01, 0x01, 0x01)), Arg1)
                M600 (Arg0, 0x0A, Local0, BB27)
                Local0 = Concatenate (DerefOf (M602 (0x01, 0x01, 0x01)), Arg2)
                M600 (Arg0, 0x0B, Local0, BB28)
            }

            Concatenate (0x0321, Arg1, Local0)
            M600 (Arg0, 0x0C, Local0, BB27)
            Concatenate (0x0321, Arg2, Local0)
            M600 (Arg0, 0x0D, Local0, BB28)
            Concatenate (AUI1, Arg1, Local0)
            M600 (Arg0, 0x0E, Local0, BB27)
            Concatenate (AUI1, Arg2, Local0)
            M600 (Arg0, 0x0F, Local0, BB28)
            If (Y078)
            {
                Concatenate (DerefOf (RefOf (AUI1)), Arg1, Local0)
                M600 (Arg0, 0x10, Local0, BB27)
                Concatenate (DerefOf (RefOf (AUI1)), Arg2, Local0)
                M600 (Arg0, 0x11, Local0, BB28)
            }

            Concatenate (DerefOf (PAUI [0x01]), Arg1, Local0)
            M600 (Arg0, 0x12, Local0, BB27)
            Concatenate (DerefOf (PAUI [0x01]), Arg2, Local0)
            M600 (Arg0, 0x14, Local0, BB28)
            /* Method returns Integer */

            Concatenate (M601 (0x01, 0x01), Arg1, Local0)
            M600 (Arg0, 0x15, Local0, BB27)
            Concatenate (M601 (0x01, 0x01), Arg2, Local0)
            M600 (Arg0, 0x16, Local0, BB28)
            /* Method returns Reference to Integer */

            If (Y500)
            {
                Concatenate (DerefOf (M602 (0x01, 0x01, 0x01)), Arg1, Local0)
                M600 (Arg0, 0x17, Local0, BB27)
                Concatenate (DerefOf (M602 (0x01, 0x01, 0x01)), Arg2, Local0)
                M600 (Arg0, 0x18, Local0, BB28)
            }
        }

        /* Buffer to Integer conversion of the Buffer Length (second) */
        /* operand of the ToString operator */
        /* Common 32-bit/64-bit test */
        Method (M066, 3, NotSerialized)
        {
            Local0 = ToString (Buffer (0x19)
                    {
                        "This is auxiliary Buffer"
                    }, Arg2)
            M600 (Arg0, 0x00, Local0, BS1B)
            Local0 = ToString (Buffer (0x19)
                    {
                        "This is auxiliary Buffer"
                    }, Arg1)
            M600 (Arg0, 0x01, Local0, BS1C)
            Local0 = ToString (AUB6, Arg2)
            M600 (Arg0, 0x02, Local0, BS1B)
            Local0 = ToString (AUB6, Arg1)
            M600 (Arg0, 0x03, Local0, BS1C)
            If (Y078)
            {
                Local0 = ToString (DerefOf (RefOf (AUB6)), Arg2)
                M600 (Arg0, 0x04, Local0, BS1B)
                Local0 = ToString (DerefOf (RefOf (AUB6)), Arg1)
                M600 (Arg0, 0x05, Local0, BS1C)
            }

            Local0 = ToString (DerefOf (PAUB [0x06]), Arg2)
            M600 (Arg0, 0x06, Local0, BS1B)
            Local0 = ToString (DerefOf (PAUB [0x06]), Arg1)
            M600 (Arg0, 0x07, Local0, BS1C)
            /* Method returns Buffer */

            Local0 = ToString (M601 (0x03, 0x06), Arg2)
            M600 (Arg0, 0x08, Local0, BS1B)
            Local0 = ToString (M601 (0x03, 0x06), Arg1)
            M600 (Arg0, 0x09, Local0, BS1C)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Local0 = ToString (DerefOf (M602 (0x03, 0x06, 0x01)), Arg2)
                M600 (Arg0, 0x0A, Local0, BS1B)
                Local0 = ToString (DerefOf (M602 (0x03, 0x06, 0x01)), Arg1)
                M600 (Arg0, 0x0B, Local0, BS1C)
            }

            ToString (Buffer (0x19)
                {
                    "This is auxiliary Buffer"
                }, Arg2, Local0)
            M600 (Arg0, 0x0C, Local0, BS1B)
            ToString (Buffer (0x19)
                {
                    "This is auxiliary Buffer"
                }, Arg1, Local0)
            M600 (Arg0, 0x0D, Local0, BS1C)
            ToString (AUB6, Arg2, Local0)
            M600 (Arg0, 0x0E, Local0, BS1B)
            ToString (AUB6, Arg1, Local0)
            M600 (Arg0, 0x0F, Local0, BS1C)
            If (Y078)
            {
                ToString (DerefOf (RefOf (AUB6)), Arg2, Local0)
                M600 (Arg0, 0x10, Local0, BS1B)
                ToString (DerefOf (RefOf (AUB6)), Arg1, Local0)
                M600 (Arg0, 0x11, Local0, BS1C)
            }

            ToString (DerefOf (PAUB [0x06]), Arg2, Local0)
            M600 (Arg0, 0x12, Local0, BS1B)
            ToString (DerefOf (PAUB [0x06]), Arg1, Local0)
            M600 (Arg0, 0x13, Local0, BS1C)
            /* Method returns Buffer */

            ToString (M601 (0x03, 0x06), Arg2, Local0)
            M600 (Arg0, 0x14, Local0, BS1B)
            ToString (M601 (0x03, 0x06), Arg1, Local0)
            M600 (Arg0, 0x15, Local0, BS1C)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                ToString (DerefOf (M602 (0x03, 0x06, 0x01)), Arg2, Local0)
                M600 (Arg0, 0x16, Local0, BS1B)
                ToString (DerefOf (M602 (0x03, 0x06, 0x01)), Arg1, Local0)
                M600 (Arg0, 0x17, Local0, BS1C)
            }
        }

        Method (M64R, 2, NotSerialized)
        {
            Local0 = ToString (Buffer (0x19)
                    {
                        "This is auxiliary Buffer"
                    }, Arg1)
            M600 (Arg0, 0x00, Local0, BS1C)
            Local0 = ToString (AUB6, Arg1)
            M600 (Arg0, 0x01, Local0, BS1C)
            If (Y078)
            {
                Local0 = ToString (DerefOf (RefOf (AUB6)), Arg1)
                M600 (Arg0, 0x02, Local0, BS1C)
            }

            Local0 = ToString (DerefOf (PAUB [0x06]), Arg1)
            M600 (Arg0, 0x03, Local0, BS1C)
            /* Method returns Buffer */

            Local0 = ToString (M601 (0x03, 0x06), Arg1)
            M600 (Arg0, 0x04, Local0, BS1C)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Local0 = ToString (DerefOf (M602 (0x03, 0x06, 0x01)), Arg1)
                M600 (Arg0, 0x05, Local0, BS1C)
            }

            ToString (Buffer (0x19)
                {
                    "This is auxiliary Buffer"
                }, Arg1, Local0)
            M600 (Arg0, 0x06, Local0, BS1C)
            ToString (AUB6, Arg1, Local0)
            M600 (Arg0, 0x07, Local0, BS1C)
            If (Y078)
            {
                ToString (DerefOf (RefOf (AUB6)), Arg1, Local0)
                M600 (Arg0, 0x08, Local0, BS1C)
            }

            ToString (DerefOf (PAUB [0x06]), Arg1, Local0)
            M600 (Arg0, 0x09, Local0, BS1C)
            /* Method returns Buffer */

            ToString (M601 (0x03, 0x06), Arg1, Local0)
            M600 (Arg0, 0x0A, Local0, BS1C)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                ToString (DerefOf (M602 (0x03, 0x06, 0x01)), Arg1, Local0)
                M600 (Arg0, 0x0B, Local0, BS1C)
            }
        }

        Method (M32R, 2, NotSerialized)
        {
            Local0 = ToString (Buffer (0x19)
                    {
                        "This is auxiliary Buffer"
                    }, Arg1)
            M600 (Arg0, 0x00, Local0, BS1C)
            Local0 = ToString (AUB6, Arg1)
            M600 (Arg0, 0x01, Local0, BS1C)
            If (Y078)
            {
                Local0 = ToString (DerefOf (RefOf (AUB6)), Arg1)
                M600 (Arg0, 0x02, Local0, BS1C)
            }

            Local0 = ToString (DerefOf (PAUB [0x06]), Arg1)
            M600 (Arg0, 0x03, Local0, BS1C)
            /* Method returns Buffer */

            Local0 = ToString (M601 (0x03, 0x06), Arg1)
            M600 (Arg0, 0x04, Local0, BS1C)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                Local0 = ToString (DerefOf (M602 (0x03, 0x06, 0x01)), Arg1)
                M600 (Arg0, 0x05, Local0, BS1C)
            }

            ToString (Buffer (0x19)
                {
                    "This is auxiliary Buffer"
                }, Arg1, Local0)
            M600 (Arg0, 0x06, Local0, BS1C)
            ToString (AUB6, Arg1, Local0)
            M600 (Arg0, 0x07, Local0, BS1C)
            If (Y078)
            {
                ToString (DerefOf (RefOf (AUB6)), Arg1, Local0)
                M600 (Arg0, 0x08, Local0, BS1C)
            }

            ToString (DerefOf (PAUB [0x06]), Arg1, Local0)
            M600 (Arg0, 0x09, Local0, BS1C)
            /* Method returns Buffer */

            ToString (M601 (0x03, 0x06), Arg1, Local0)
            M600 (Arg0, 0x0A, Local0, BS1C)
            /* Method returns Reference to Buffer */

            If (Y500)
            {
                ToString (DerefOf (M602 (0x03, 0x06, 0x01)), Arg1, Local0)
                M600 (Arg0, 0x0B, Local0, BS1C)
            }
        }

        /* Buffer to Integer conversion of the Buffer Index (second) */
        /* operand of the Index operator */
        Method (M067, 2, NotSerialized)
        {
            Store (AUS6 [Arg1], Local0)
            M600 (Arg0, 0x00, DerefOf (Local0), BI10)
            Store (AUB6 [Arg1], Local0)
            M600 (Arg0, 0x01, DerefOf (Local0), BI10)
            Store (AUP0 [Arg1], Local0)
            M600 (Arg0, 0x02, DerefOf (Local0), BI11)
            If (Y078)
            {
                Store (DerefOf (RefOf (AUS6)) [Arg1], Local0)
                M600 (Arg0, 0x03, DerefOf (Local0), BI10)
                Store (DerefOf (RefOf (AUB6)) [Arg1], Local0)
                M600 (Arg0, 0x04, DerefOf (Local0), BI10)
                Store (DerefOf (RefOf (AUP0)) [Arg1], Local0)
                M600 (Arg0, 0x05, DerefOf (Local0), BI11)
            }

            Store (DerefOf (PAUS [0x06]) [Arg1], Local0)
            M600 (Arg0, 0x06, DerefOf (Local0), BI10)
            Store (DerefOf (PAUB [0x06]) [Arg1], Local0)
            M600 (Arg0, 0x07, DerefOf (Local0), BI10)
            Store (DerefOf (PAUP [0x00]) [Arg1], Local0)
            M600 (Arg0, 0x08, DerefOf (Local0), BI11)
            /* Method returns Object */

            If (Y900)
            {
                Store (M601 (0x02, 0x06) [Arg1], Local0)
                M600 (Arg0, 0x09, DerefOf (Local0), BI10)
                Store (M601 (0x03, 0x06) [Arg1], Local0)
                M600 (Arg0, 0x0A, DerefOf (Local0), BI10)
                Store (M601 (0x04, 0x00) [Arg1], Local0)
                M600 (Arg0, 0x0B, DerefOf (Local0), BI11)
            }

            /* Method returns Reference */

            If (Y500)
            {
                Store (DerefOf (M602 (0x02, 0x06, 0x01)) [Arg1], Local0)
                M600 (Arg0, 0x0C, DerefOf (Local0), BI10)
                Store (DerefOf (M602 (0x03, 0x06, 0x01)) [Arg1], Local0)
                M600 (Arg0, 0x0D, DerefOf (Local0), BI10)
                Store (DerefOf (M602 (0x04, 0x00, 0x01)) [Arg1], Local0)
                M600 (Arg0, 0x0E, DerefOf (Local0), BI11)
            }

            Local0 = AUS6 [Arg1]
            M600 (Arg0, 0x0F, DerefOf (Local0), BI10)
            Local0 = AUB6 [Arg1]
            M600 (Arg0, 0x10, DerefOf (Local0), BI10)
            Local0 = AUP0 [Arg1]
            M600 (Arg0, 0x11, DerefOf (Local0), BI11)
            If (Y078)
            {
                Local0 = DerefOf (RefOf (AUS6)) [Arg1]
                M600 (Arg0, 0x12, DerefOf (Local0), BI10)
                Local0 = DerefOf (RefOf (AUB6)) [Arg1]
                M600 (Arg0, 0x13, DerefOf (Local0), BI10)
                Local0 = DerefOf (RefOf (AUP0)) [Arg1]
                M600 (Arg0, 0x14, DerefOf (Local0), BI11)
            }

            Local0 = DerefOf (PAUS [0x06]) [Arg1]
            M600 (Arg0, 0x15, DerefOf (Local0), BI10)
            Local0 = DerefOf (PAUB [0x06]) [Arg1]
            M600 (Arg0, 0x16, DerefOf (Local0), BI10)
            Local0 = DerefOf (PAUP [0x00]) [Arg1]
            M600 (Arg0, 0x17, DerefOf (Local0), BI11)
            /* Method returns Object */

            If (Y900)
            {
                Local0 = M601 (0x02, 0x06) [Arg1]
                M600 (Arg0, 0x18, DerefOf (Local0), BI10)
                Local0 = M601 (0x03, 0x06) [Arg1]
                M600 (Arg0, 0x19, DerefOf (Local0), BI10)
                Local0 = M601 (0x04, 0x00) [Arg1]
                M600 (Arg0, 0x1A, DerefOf (Local0), BI11)
            }

            /* Method returns Reference */

            If (Y500)
            {
                Local0 = DerefOf (M602 (0x02, 0x06, 0x01)) [Arg1]
                M600 (Arg0, 0x1B, DerefOf (Local0), BI10)
                Local0 = DerefOf (M602 (0x03, 0x06, 0x01)) [Arg1]
                M600 (Arg0, 0x1C, DerefOf (Local0), BI10)
                Local0 = DerefOf (M602 (0x04, 0x00, 0x01)) [Arg1]
                M600 (Arg0, 0x1D, DerefOf (Local0), BI11)
            }

            If (Y098)
            {
                Local0 = Local1 = AUS6 [Arg1]
                M600 (Arg0, 0x1E, DerefOf (Local0), BI10)
                Local0 = Local1 = AUB6 [Arg1]
                M600 (Arg0, 0x1F, DerefOf (Local0), BI10)
                Local0 = Local1 = AUP0 [Arg1]
                M600 (Arg0, 0x20, DerefOf (Local0), BI11)
            }

            If (Y078)
            {
                Local0 = Local1 = DerefOf (RefOf (AUS6)) [Arg1]
                M600 (Arg0, 0x21, DerefOf (Local0), BI10)
                Local0 = Local1 = DerefOf (RefOf (AUB6)) [Arg1]
                M600 (Arg0, 0x22, DerefOf (Local0), BI10)
                Local0 = Local1 = DerefOf (RefOf (AUP0)) [Arg1]
                M600 (Arg0, 0x23, DerefOf (Local0), BI11)
            }

            If (Y098)
            {
                Local0 = Local1 = DerefOf (PAUS [0x06]) [Arg1]
                M600 (Arg0, 0x24, DerefOf (Local0), BI10)
                Local0 = Local1 = DerefOf (PAUB [0x06]) [Arg1]
                M600 (Arg0, 0x25, DerefOf (Local0), BI10)
                Local0 = Local1 = DerefOf (PAUP [0x00]) [Arg1]
                M600 (Arg0, 0x26, DerefOf (Local0), BI11)
            }

            /* Method returns Object */

            If ((Y900 && Y098))
            {
                Local0 = Local1 = M601 (0x02, 0x06) [Arg1]
                M600 (Arg0, 0x27, DerefOf (Local0), BI10)
                Local0 = Local1 = M601 (0x03, 0x06) [Arg1]
                M600 (Arg0, 0x28, DerefOf (Local0), BI10)
                Local0 = Local1 = M601 (0x04, 0x00) [Arg1]
                M600 (Arg0, 0x29, DerefOf (Local0), BI11)
            }

            /* Method returns Reference */

            If (Y500)
            {
                Local0 = Local1 = DerefOf (M602 (0x02, 0x06, 0x01)) [Arg1]
                M600 (Arg0, 0x2A, DerefOf (Local0), BI10)
                Local0 = Local1 = DerefOf (M602 (0x03, 0x06, 0x01)) [Arg1]
                M600 (Arg0, 0x2B, DerefOf (Local0), BI10)
                Local0 = Local1 = DerefOf (M602 (0x04, 0x00, 0x01)) [Arg1]
                M600 (Arg0, 0x2C, DerefOf (Local0), BI11)
            }
        }

        /* Buffer to Integer conversion of the String Arg (third) */
        /* operand of the Fatal operator */
        /* (it can only be checked an exception does not occur) */
        Method (M068, 3, NotSerialized)
        {
            CH03 (Arg0, Z121, 0x09, 0x5B70, 0x00)
            Fatal (0xFF, 0xFFFFFFFF, Arg1)
            If (F64)
            {
                Fatal (0xFF, 0xFFFFFFFF, Arg2)
            }
            Else
            {
                Fatal (0xFF, 0xFFFFFFFF, Arg2)
            }

            CH03 (Arg0, Z121, 0x0A, 0x5B77, 0x00)
        }

        /* Buffer to Integer conversion of the Buffer Index and Length */
        /* operands of the Mid operator */
        /* Common 32-bit/64-bit test */
        Method (M069, 2, NotSerialized)
        {
            /* String to Integer conversion of the String Index operand */

            Local0 = Mid ("This is auxiliary String", Arg1, 0x0A)
            M600 (Arg0, 0x00, Local0, BS1D)
            Local0 = Mid (Buffer (0x19)
                    {
                        "This is auxiliary Buffer"
                    }, Arg1, 0x0A)
            M600 (Arg0, 0x01, Local0, BB32)
            Local0 = Mid (AUS6, Arg1, 0x0A)
            M600 (Arg0, 0x02, Local0, BS1D)
            Local0 = Mid (AUB6, Arg1, 0x0A)
            M600 (Arg0, 0x03, Local0, BB32)
            If (Y078)
            {
                Local0 = Mid (DerefOf (RefOf (AUS6)), Arg1, 0x0A)
                M600 (Arg0, 0x04, Local0, BS1D)
                Local0 = Mid (DerefOf (RefOf (AUB6)), Arg1, 0x0A)
                M600 (Arg0, 0x05, Local0, BB32)
            }

            Local0 = Mid (DerefOf (PAUS [0x06]), Arg1, 0x0A)
            M600 (Arg0, 0x06, Local0, BS1D)
            Local0 = Mid (DerefOf (PAUB [0x06]), Arg1, 0x0A)
            M600 (Arg0, 0x07, Local0, BB32)
            /* Method returns Object */

            Local0 = Mid (M601 (0x02, 0x06), Arg1, 0x0A)
            M600 (Arg0, 0x08, Local0, BS1D)
            Local0 = Mid (M601 (0x03, 0x06), Arg1, 0x0A)
            M600 (Arg0, 0x09, Local0, BB32)
            /* Method returns Reference */

            If (Y500)
            {
                Local0 = Mid (DerefOf (M602 (0x02, 0x06, 0x01)), Arg1, 0x0A)
                M600 (Arg0, 0x0A, Local0, BS1D)
                Local0 = Mid (DerefOf (M602 (0x03, 0x06, 0x01)), Arg1, 0x0A)
                M600 (Arg0, 0x0B, Local0, BB32)
            }

            Mid ("This is auxiliary String", Arg1, 0x0A, Local0)
            M600 (Arg0, 0x0C, Local0, BS1D)
            Mid (Buffer (0x19)
                {
                    "This is auxiliary Buffer"
                }, Arg1, 0x0A, Local0)
            M600 (Arg0, 0x0D, Local0, BB32)
            Mid (AUS6, Arg1, 0x0A, Local0)
            M600 (Arg0, 0x0E, Local0, BS1D)
            Mid (AUB6, Arg1, 0x0A, Local0)
            M600 (Arg0, 0x0F, Local0, BB32)
            If (Y078)
            {
                Mid (DerefOf (RefOf (AUS6)), Arg1, 0x0A, Local0)
                M600 (Arg0, 0x10, Local0, BS1D)
                Mid (DerefOf (RefOf (AUB6)), Arg1, 0x0A, Local0)
                M600 (Arg0, 0x11, Local0, BB32)
            }

            Mid (DerefOf (PAUS [0x06]), Arg1, 0x0A, Local0)
            M600 (Arg0, 0x12, Local0, BS1D)
            Mid (DerefOf (PAUB [0x06]), Arg1, 0x0A, Local0)
            M600 (Arg0, 0x13, Local0, BB32)
            /* Method returns Object */

            Mid (M601 (0x02, 0x06), Arg1, 0x0A, Local0)
            M600 (Arg0, 0x14, Local0, BS1D)
            Mid (M601 (0x03, 0x06), Arg1, 0x0A, Local0)
            M600 (Arg0, 0x15, Local0, BB32)
            /* Method returns Reference */

            If (Y500)
            {
                Mid (DerefOf (M602 (0x02, 0x06, 0x01)), Arg1, 0x0A, Local0)
                M600 (Arg0, 0x16, Local0, BS1D)
                Mid (DerefOf (M602 (0x03, 0x06, 0x01)), Arg1, 0x0A, Local0)
                M600 (Arg0, 0x17, Local0, BB32)
            }

            /* String to Integer conversion of the String Length operand */

            Local0 = Mid ("This is auxiliary String", 0x00, Arg1)
            M600 (Arg0, 0x18, Local0, BS1B)
            Local0 = Mid (Buffer (0x19)
                    {
                        "This is auxiliary Buffer"
                    }, 0x00, Arg1)
            M600 (Arg0, 0x19, Local0, BB33)
            Local0 = Mid (AUS6, 0x00, Arg1)
            M600 (Arg0, 0x1A, Local0, BS1B)
            Local0 = Mid (AUB6, 0x00, Arg1)
            M600 (Arg0, 0x1B, Local0, BB33)
            If (Y078)
            {
                Local0 = Mid (DerefOf (RefOf (AUS6)), 0x00, Arg1)
                M600 (Arg0, 0x1C, Local0, BS1B)
                Local0 = Mid (DerefOf (RefOf (AUB6)), 0x00, Arg1)
                M600 (Arg0, 0x1D, Local0, BB33)
            }

            Local0 = Mid (DerefOf (PAUS [0x06]), 0x00, Arg1)
            M600 (Arg0, 0x1E, Local0, BS1B)
            Local0 = Mid (DerefOf (PAUB [0x06]), 0x00, Arg1)
            M600 (Arg0, 0x1F, Local0, BB33)
            /* Method returns Object */

            Local0 = Mid (M601 (0x02, 0x06), 0x00, Arg1)
            M600 (Arg0, 0x20, Local0, BS1B)
            Local0 = Mid (M601 (0x03, 0x06), 0x00, Arg1)
            M600 (Arg0, 0x21, Local0, BB33)
            /* Method returns Reference */

            If (Y500)
            {
                Local0 = Mid (DerefOf (M602 (0x02, 0x06, 0x01)), 0x00, Arg1)
                M600 (Arg0, 0x22, Local0, BS1B)
                Local0 = Mid (DerefOf (M602 (0x03, 0x06, 0x01)), 0x00, Arg1)
                M600 (Arg0, 0x23, Local0, BB33)
            }

            Mid ("This is auxiliary String", 0x00, Arg1, Local0)
            M600 (Arg0, 0x24, Local0, BS1B)
            Mid (Buffer (0x19)
                {
                    "This is auxiliary Buffer"
                }, 0x00, Arg1, Local0)
            M600 (Arg0, 0x25, Local0, BB33)
            Mid (AUS6, 0x00, Arg1, Local0)
            M600 (Arg0, 0x25, Local0, BS1B)
            Mid (AUB6, 0x00, Arg1, Local0)
            M600 (Arg0, 0x27, Local0, BB33)
            If (Y078)
            {
                Mid (DerefOf (RefOf (AUS6)), 0x00, Arg1, Local0)
                M600 (Arg0, 0x28, Local0, BS1B)
                Mid (DerefOf (RefOf (AUB6)), 0x00, Arg1, Local0)
                M600 (Arg0, 0x29, Local0, BB33)
            }

            Mid (DerefOf (PAUS [0x06]), 0x00, Arg1, Local0)
            M600 (Arg0, 0x2A, Local0, BS1B)
            Mid (DerefOf (PAUB [0x06]), 0x00, Arg1, Local0)
            M600 (Arg0, 0x2B, Local0, BB33)
            /* Method returns Object */

            Mid (M601 (0x02, 0x06), 0x00, Arg1, Local0)
            M600 (Arg0, 0x2C, Local0, BS1B)
            Mid (M601 (0x03, 0x06), 0x00, Arg1, Local0)
            M600 (Arg0, 0x2D, Local0, BB33)
            /* Method returns Reference */

            If (Y500)
            {
                Mid (DerefOf (M602 (0x02, 0x06, 0x01)), 0x00, Arg1, Local0)
                M600 (Arg0, 0x2E, Local0, BS1B)
                Mid (DerefOf (M602 (0x03, 0x06, 0x01)), 0x00, Arg1, Local0)
                M600 (Arg0, 0x2F, Local0, BB33)
            }
        }

        Method (M64S, 3, NotSerialized)
        {
            /* String to Integer conversion of the String Length operand */

            Local0 = Mid ("This is auxiliary String", 0x00, Arg1)
            M600 (Arg0, 0x00, Local0, BS1E)
            Local0 = Mid (Buffer (0x19)
                    {
                        "This is auxiliary Buffer"
                    }, 0x00, Arg1)
            M600 (Arg0, 0x01, Local0, BB34)
            Local0 = Mid (AUS6, 0x00, Arg1)
            M600 (Arg0, 0x02, Local0, BS1E)
            Local0 = Mid (AUB6, 0x00, Arg1)
            M600 (Arg0, 0x03, Local0, BB34)
            If (Y078)
            {
                Local0 = Mid (DerefOf (RefOf (AUS6)), 0x00, Arg1)
                M600 (Arg0, 0x04, Local0, BS1E)
                Local0 = Mid (DerefOf (RefOf (AUB6)), 0x00, Arg1)
                M600 (Arg0, 0x05, Local0, BB34)
            }

            Local0 = Mid (DerefOf (PAUS [0x06]), 0x00, Arg1)
            M600 (Arg0, 0x06, Local0, BS1E)
            Local0 = Mid (DerefOf (PAUB [0x06]), 0x00, Arg1)
            M600 (Arg0, 0x07, Local0, BB34)
            /* Method returns Object */

            Local0 = Mid (M601 (0x02, 0x06), 0x00, Arg1)
            M600 (Arg0, 0x08, Local0, BS1E)
            Local0 = Mid (M601 (0x03, 0x06), 0x00, Arg1)
            M600 (Arg0, 0x09, Local0, BB34)
            /* Method returns Reference */

            If (Y500)
            {
                Local0 = Mid (DerefOf (M602 (0x02, 0x06, 0x01)), 0x00, Arg1)
                M600 (Arg0, 0x0A, Local0, BS1E)
                Local0 = Mid (DerefOf (M602 (0x03, 0x06, 0x01)), 0x00, Arg1)
                M600 (Arg0, 0x0B, Local0, BB34)
            }

            Mid ("This is auxiliary String", 0x00, Arg1, Local0)
            M600 (Arg0, 0x0C, Local0, BS1E)
            Mid (Buffer (0x19)
                {
                    "This is auxiliary Buffer"
                }, 0x00, Arg1, Local0)
            M600 (Arg0, 0x0D, Local0, BB34)
            Mid (AUS6, 0x00, Arg1, Local0)
            M600 (Arg0, 0x0E, Local0, BS1E)
            Mid (AUB6, 0x00, Arg1, Local0)
            M600 (Arg0, 0x0F, Local0, BB34)
            If (Y078)
            {
                Mid (DerefOf (RefOf (AUS6)), 0x00, Arg1, Local0)
                M600 (Arg0, 0x10, Local0, BS1E)
                Mid (DerefOf (RefOf (AUB6)), 0x00, Arg1, Local0)
                M600 (Arg0, 0x11, Local0, BB34)
            }

            Mid (DerefOf (PAUS [0x06]), 0x00, Arg1, Local0)
            M600 (Arg0, 0x12, Local0, BS1E)
            Mid (DerefOf (PAUB [0x06]), 0x00, Arg1, Local0)
            M600 (Arg0, 0x13, Local0, BB34)
            /* Method returns Object */

            Mid (M601 (0x02, 0x06), 0x00, Arg1, Local0)
            M600 (Arg0, 0x14, Local0, BS1E)
            Mid (M601 (0x03, 0x06), 0x00, Arg1, Local0)
            M600 (Arg0, 0x15, Local0, BB34)
            /* Method returns Reference */

            If (Y500)
            {
                Mid (DerefOf (M602 (0x02, 0x06, 0x01)), 0x00, Arg1, Local0)
                M600 (Arg0, 0x16, Local0, BS1E)
                Mid (DerefOf (M602 (0x03, 0x06, 0x01)), 0x00, Arg1, Local0)
                M600 (Arg0, 0x17, Local0, BB34)
            }

            /* String to Integer conversion of the both String operands */

            Local0 = Mid ("This is auxiliary String", Arg2, Arg1)
            M600 (Arg0, 0x18, Local0, BS1F)
            Local0 = Mid (Buffer (0x19)
                    {
                        "This is auxiliary Buffer"
                    }, Arg2, Arg1)
            M600 (Arg0, 0x19, Local0, BB35)
            Local0 = Mid (AUS6, Arg2, Arg1)
            M600 (Arg0, 0x1A, Local0, BS1F)
            Local0 = Mid (AUB6, Arg2, Arg1)
            M600 (Arg0, 0x1B, Local0, BB35)
            If (Y078)
            {
                Local0 = Mid (DerefOf (RefOf (AUS6)), Arg2, Arg1)
                M600 (Arg0, 0x1C, Local0, BS1F)
                Local0 = Mid (DerefOf (RefOf (AUB6)), Arg2, Arg1)
                M600 (Arg0, 0x1D, Local0, BB35)
            }

            Local0 = Mid (DerefOf (PAUS [0x06]), Arg2, Arg1)
            M600 (Arg0, 0x1E, Local0, BS1F)
            Local0 = Mid (DerefOf (PAUB [0x06]), Arg2, Arg1)
            M600 (Arg0, 0x1F, Local0, BB35)
            /* Method returns Object */

            Local0 = Mid (M601 (0x02, 0x06), Arg2, Arg1)
            M600 (Arg0, 0x20, Local0, BS1F)
            Local0 = Mid (M601 (0x03, 0x06), Arg2, Arg1)
            M600 (Arg0, 0x21, Local0, BB35)
            /* Method returns Reference */

            If (Y500)
            {
                Local0 = Mid (DerefOf (M602 (0x02, 0x06, 0x01)), Arg2, Arg1)
                M600 (Arg0, 0x22, Local0, BS1F)
                Local0 = Mid (DerefOf (M602 (0x03, 0x06, 0x01)), Arg2, Arg1)
                M600 (Arg0, 0x23, Local0, BB35)
            }

            Mid ("This is auxiliary String", Arg2, Arg1, Local0)
            M600 (Arg0, 0x24, Local0, BS1F)
            Mid (Buffer (0x19)
                {
                    "This is auxiliary Buffer"
                }, Arg2, Arg1, Local0)
            M600 (Arg0, 0x25, Local0, BB35)
            Mid (AUS6, Arg2, Arg1, Local0)
            M600 (Arg0, 0x26, Local0, BS1F)
            Mid (AUB6, Arg2, Arg1, Local0)
            M600 (Arg0, 0x27, Local0, BB35)
            If (Y078)
            {
                Mid (DerefOf (RefOf (AUS6)), Arg2, Arg1, Local0)
                M600 (Arg0, 0x28, Local0, BS1F)
                Mid (DerefOf (RefOf (AUB6)), Arg2, Arg1, Local0)
                M600 (Arg0, 0x29, Local0, BB35)
            }

            Mid (DerefOf (PAUS [0x06]), Arg2, Arg1, Local0)
            M600 (Arg0, 0x2A, Local0, BS1F)
            Mid (DerefOf (PAUB [0x06]), Arg2, Arg1, Local0)
            M600 (Arg0, 0x2B, Local0, BB35)
            /* Method returns Object */

            Mid (M601 (0x02, 0x06), Arg2, Arg1, Local0)
            M600 (Arg0, 0x2C, Local0, BS1F)
            Mid (M601 (0x03, 0x06), Arg2, Arg1, Local0)
            M600 (Arg0, 0x2D, Local0, BB35)
            /* Method returns Reference */

            If (Y500)
            {
                Mid (DerefOf (M602 (0x02, 0x06, 0x01)), Arg2, Arg1, Local0)
                M600 (Arg0, 0x2E, Local0, BS1F)
                Mid (DerefOf (M602 (0x03, 0x06, 0x01)), Arg2, Arg1, Local0)
                M600 (Arg0, 0x2F, Local0, BB35)
            }
        }

        Method (M32S, 3, NotSerialized)
        {
            /* String to Integer conversion of the String Length operand */

            Local0 = Mid ("This is auxiliary String", 0x00, Arg1)
            M600 (Arg0, 0x00, Local0, BS1E)
            Local0 = Mid (Buffer (0x19)
                    {
                        "This is auxiliary Buffer"
                    }, 0x00, Arg1)
            M600 (Arg0, 0x01, Local0, BB34)
            Local0 = Mid (AUS6, 0x00, Arg1)
            M600 (Arg0, 0x02, Local0, BS1E)
            Local0 = Mid (AUB6, 0x00, Arg1)
            M600 (Arg0, 0x03, Local0, BB34)
            If (Y078)
            {
                Local0 = Mid (DerefOf (RefOf (AUS6)), 0x00, Arg1)
                M600 (Arg0, 0x04, Local0, BS1E)
                Local0 = Mid (DerefOf (RefOf (AUB6)), 0x00, Arg1)
                M600 (Arg0, 0x05, Local0, BB34)
            }

            Local0 = Mid (DerefOf (PAUS [0x06]), 0x00, Arg1)
            M600 (Arg0, 0x06, Local0, BS1E)
            Local0 = Mid (DerefOf (PAUB [0x06]), 0x00, Arg1)
            M600 (Arg0, 0x07, Local0, BB34)
            /* Method returns Object */

            Local0 = Mid (M601 (0x02, 0x06), 0x00, Arg1)
            M600 (Arg0, 0x08, Local0, BS1E)
            Local0 = Mid (M601 (0x03, 0x06), 0x00, Arg1)
            M600 (Arg0, 0x09, Local0, BB34)
            /* Method returns Reference */

            If (Y500)
            {
                Local0 = Mid (DerefOf (M602 (0x02, 0x06, 0x01)), 0x00, Arg1)
                M600 (Arg0, 0x0A, Local0, BS1E)
                Local0 = Mid (DerefOf (M602 (0x03, 0x06, 0x01)), 0x00, Arg1)
                M600 (Arg0, 0x0B, Local0, BB34)
            }

            Mid ("This is auxiliary String", 0x00, Arg1, Local0)
            M600 (Arg0, 0x0C, Local0, BS1E)
            Mid (Buffer (0x19)
                {
                    "This is auxiliary Buffer"
                }, 0x00, Arg1, Local0)
            M600 (Arg0, 0x0D, Local0, BB34)
            Mid (AUS6, 0x00, Arg1, Local0)
            M600 (Arg0, 0x0E, Local0, BS1E)
            Mid (AUB6, 0x00, Arg1, Local0)
            M600 (Arg0, 0x0F, Local0, BB34)
            If (Y078)
            {
                Mid (DerefOf (RefOf (AUS6)), 0x00, Arg1, Local0)
                M600 (Arg0, 0x10, Local0, BS1E)
                Mid (DerefOf (RefOf (AUB6)), 0x00, Arg1, Local0)
                M600 (Arg0, 0x11, Local0, BB34)
            }

            Mid (DerefOf (PAUS [0x06]), 0x00, Arg1, Local0)
            M600 (Arg0, 0x12, Local0, BS1E)
            Mid (DerefOf (PAUB [0x06]), 0x00, Arg1, Local0)
            M600 (Arg0, 0x13, Local0, BB34)
            /* Method returns Object */

            Mid (M601 (0x02, 0x06), 0x00, Arg1, Local0)
            M600 (Arg0, 0x14, Local0, BS1E)
            Mid (M601 (0x03, 0x06), 0x00, Arg1, Local0)
            M600 (Arg0, 0x15, Local0, BB34)
            /* Method returns Reference */

            If (Y500)
            {
                Mid (DerefOf (M602 (0x02, 0x06, 0x01)), 0x00, Arg1, Local0)
                M600 (Arg0, 0x16, Local0, BS1E)
                Mid (DerefOf (M602 (0x03, 0x06, 0x01)), 0x00, Arg1, Local0)
                M600 (Arg0, 0x17, Local0, BB34)
            }

            /* String to Integer conversion of the both String operands */

            Local0 = Mid ("This is auxiliary String", Arg2, Arg1)
            M600 (Arg0, 0x18, Local0, BS1F)
            Local0 = Mid (Buffer (0x19)
                    {
                        "This is auxiliary Buffer"
                    }, Arg2, Arg1)
            M600 (Arg0, 0x19, Local0, BB35)
            Local0 = Mid (AUS6, Arg2, Arg1)
            M600 (Arg0, 0x1A, Local0, BS1F)
            Local0 = Mid (AUB6, Arg2, Arg1)
            M600 (Arg0, 0x1B, Local0, BB35)
            If (Y078)
            {
                Local0 = Mid (DerefOf (RefOf (AUS6)), Arg2, Arg1)
                M600 (Arg0, 0x1C, Local0, BS1F)
                Local0 = Mid (DerefOf (RefOf (AUB6)), Arg2, Arg1)
                M600 (Arg0, 0x1D, Local0, BB35)
            }

            Local0 = Mid (DerefOf (PAUS [0x06]), Arg2, Arg1)
            M600 (Arg0, 0x1E, Local0, BS1F)
            Local0 = Mid (DerefOf (PAUB [0x06]), Arg2, Arg1)
            M600 (Arg0, 0x1F, Local0, BB35)
            /* Method returns Object */

            Local0 = Mid (M601 (0x02, 0x06), Arg2, Arg1)
            M600 (Arg0, 0x20, Local0, BS1F)
            Local0 = Mid (M601 (0x03, 0x06), Arg2, Arg1)
            M600 (Arg0, 0x21, Local0, BB35)
            /* Method returns Reference */

            If (Y500)
            {
                Local0 = Mid (DerefOf (M602 (0x02, 0x06, 0x01)), Arg2, Arg1)
                M600 (Arg0, 0x22, Local0, BS1F)
                Local0 = Mid (DerefOf (M602 (0x03, 0x06, 0x01)), Arg2, Arg1)
                M600 (Arg0, 0x23, Local0, BB35)
            }

            Mid ("This is auxiliary String", Arg2, Arg1, Local0)
            M600 (Arg0, 0x24, Local0, BS1F)
            Mid (Buffer (0x19)
                {
                    "This is auxiliary Buffer"
                }, Arg2, Arg1, Local0)
            M600 (Arg0, 0x25, Local0, BB35)
            Mid (AUS6, Arg2, Arg1, Local0)
            M600 (Arg0, 0x26, Local0, BS1F)
            Mid (AUB6, Arg2, Arg1, Local0)
            M600 (Arg0, 0x27, Local0, BB35)
            If (Y078)
            {
                Mid (DerefOf (RefOf (AUS6)), Arg2, Arg1, Local0)
                M600 (Arg0, 0x28, Local0, BS1F)
                Mid (DerefOf (RefOf (AUB6)), Arg2, Arg1, Local0)
                M600 (Arg0, 0x29, Local0, BB35)
            }

            Mid (DerefOf (PAUS [0x06]), Arg2, Arg1, Local0)
            M600 (Arg0, 0x2A, Local0, BS1F)
            Mid (DerefOf (PAUB [0x06]), Arg2, Arg1, Local0)
            M600 (Arg0, 0x2B, Local0, BB35)
            /* Method returns Object */

            Mid (M601 (0x02, 0x06), Arg2, Arg1, Local0)
            M600 (Arg0, 0x2C, Local0, BS1F)
            Mid (M601 (0x03, 0x06), Arg2, Arg1, Local0)
            M600 (Arg0, 0x2D, Local0, BB35)
            /* Method returns Reference */

            If (Y500)
            {
                Mid (DerefOf (M602 (0x02, 0x06, 0x01)), Arg2, Arg1, Local0)
                M600 (Arg0, 0x2E, Local0, BS1F)
                Mid (DerefOf (M602 (0x03, 0x06, 0x01)), Arg2, Arg1, Local0)
                M600 (Arg0, 0x2F, Local0, BB35)
            }
        }

        /* Buffer to Integer conversion of the Buffer StartIndex */
        /* operand of the Match operator */
        Method (M06A, 2, NotSerialized)
        {
            Local0 = Match (Package (0x0F)
                    {
                        0x0A50, 
                        0x0A51, 
                        0x0A52, 
                        0x0A53, 
                        0x0A54, 
                        0x0A55, 
                        0x0A56, 
                        0x0A57, 
                        0x0A58, 
                        0x0A59, 
                        0x0A5A, 
                        0x0A5B, 
                        0x0A5C, 
                        0x0A5D, 
                        0x0A5E
                    }, MEQ, 0x0A5D, MTR, 0x00, Arg1)
            M600 (Arg0, 0x00, Local0, 0x0D)
            Local0 = Match (Package (0x0F)
                    {
                        0x0A50, 
                        0x0A51, 
                        0x0A52, 
                        0x0A53, 
                        0x0A54, 
                        0x0A55, 
                        0x0A56, 
                        0x0A57, 
                        0x0A58, 
                        0x0A59, 
                        0x0A5A, 
                        0x0A5B, 
                        0x0A5C, 
                        0x0A5D, 
                        0x0A5E
                    }, MEQ, 0x0A5A, MTR, 0x00, Arg1)
            M600 (Arg0, 0x01, Local0, Ones)
            Local0 = Match (AUP0, MEQ, 0x0A5D, MTR, 0x00, Arg1)
            M600 (Arg0, 0x02, Local0, 0x0D)
            Local0 = Match (AUP0, MEQ, 0x0A5A, MTR, 0x00, Arg1)
            M600 (Arg0, 0x03, Local0, Ones)
            If (Y078)
            {
                Local0 = Match (DerefOf (RefOf (AUP0)), MEQ, 0x0A5D, MTR, 0x00, Arg1)
                M600 (Arg0, 0x04, Local0, 0x0D)
                Local0 = Match (DerefOf (RefOf (AUP0)), MEQ, 0x0A5A, MTR, 0x00, Arg1)
                M600 (Arg0, 0x05, Local0, Ones)
            }

            Local0 = Match (DerefOf (PAUP [0x00]), MEQ, 0x0A5D, MTR, 0x00, 
                Arg1)
            M600 (Arg0, 0x06, Local0, 0x0D)
            Local0 = Match (DerefOf (PAUP [0x00]), MEQ, 0x0A5A, MTR, 0x00, 
                Arg1)
            M600 (Arg0, 0x07, Local0, Ones)
            /* Method returns Object */

            Local0 = Match (M601 (0x04, 0x00), MEQ, 0x0A5D, MTR, 0x00, Arg1)
            M600 (Arg0, 0x08, Local0, 0x0D)
            Local0 = Match (M601 (0x04, 0x00), MEQ, 0x0A5A, MTR, 0x00, Arg1)
            M600 (Arg0, 0x09, Local0, Ones)
            /* Method returns Reference */

            If (Y500)
            {
                Local0 = Match (DerefOf (M602 (0x04, 0x00, 0x01)), MEQ, 0x0A5D, MTR, 0x00, 
                    Arg1)
                M600 (Arg0, 0x0A, Local0, 0x0D)
                Local0 = Match (DerefOf (M602 (0x04, 0x00, 0x01)), MEQ, 0x0A5A, MTR, 0x00, 
                    Arg1)
                M600 (Arg0, 0x0B, Local0, Ones)
            }
        }

        /*	Method(m64t, 1) */
        /*	Method(m32t, 1) */
        /* Buffer to Integer conversion of the Buffer sole operand */
        /* of the Method execution control operators (Sleep, Stall) */
        Method (M06B, 3, NotSerialized)
        {
            CH03 (Arg0, Z121, 0x0B, 0x5DEB, 0x00)
            /* Sleep */

            Local0 = Timer
            Sleep (Arg1)
            CH03 (Arg0, Z121, 0x0C, 0x5DF2, 0x00)
            Local1 = Timer
            Local2 = (Local1 - Local0)
            If ((Local2 < C08C))
            {
                ERR (Arg0, Z121, 0x5DF7, 0x00, 0x00, Local2, C08C)
            }

            /* Stall */

            Local0 = Timer
            Stall (Arg2)
            CH03 (Arg0, Z121, 0x0D, 0x5DFF, 0x00)
            Local1 = Timer
            Local2 = (Local1 - Local0)
            If ((Local2 < 0x03DE))
            {
                ERR (Arg0, Z121, 0x5E04, 0x00, 0x00, Local2, 0x03DE)
            }
        }

        /* Buffer to Integer conversion of the Buffer TimeoutValue */
        /* (second) operand of the Acquire operator */
        Method (M06C, 2, Serialized)
        {
            Mutex (MTX0, 0x00)
            Acquire (MTX0, 0x0000)
            CH03 (Arg0, Z121, 0x0E, 0x5E10, 0x00)
            Local0 = Timer
            /* Compiler allows only Integer constant as TimeoutValue (Bug 1)
             Acquire(MTX0, arg1)
             */
            CH03 (Arg0, Z121, 0x0F, 0x5E17, 0x00)
            Local1 = Timer
            Local2 = (Local1 - Local0)
            If ((Local2 < C08C))
            {
                ERR (Arg0, Z121, 0x5E1C, 0x00, 0x00, Local2, C08C)
            }
        }

        /* Buffer to Integer conversion of the Buffer TimeoutValue */
        /* (second) operand of the Wait operator */
        Method (M06D, 2, Serialized)
        {
            Event (EVT0)
            CH03 (Arg0, Z121, 0x10, 0x5E26, 0x00)
            Local0 = Timer
            Wait (EVT0, Arg1)
            CH03 (Arg0, Z121, 0x11, 0x5E2B, 0x00)
            Local1 = Timer
            Local2 = (Local1 - Local0)
            If ((Local2 < C08C))
            {
                ERR (Arg0, Z121, 0x5E30, 0x00, 0x00, Local2, C08C)
            }
        }

        /* Buffer to Integer conversion of the Buffer value */
        /* of Predicate of the Method execution control statements */
        /* (If, ElseIf, While) */
        Method (M06E, 4, Serialized)
        {
            Name (IST0, 0x00)
            Method (M001, 1, NotSerialized)
            {
                If (Arg0)
                {
                    IST0 = 0x00
                }
            }

            Method (M002, 1, NotSerialized)
            {
                If (Arg0)
                {
                    IST0 = 0x02
                }
            }

            Method (M003, 1, NotSerialized)
            {
                If (Arg0)
                {
                    IST0 = 0x03
                }
            }

            Method (M004, 1, NotSerialized)
            {
                If (Arg0)
                {
                    IST0 = 0x04
                }
            }

            Method (M005, 2, NotSerialized)
            {
                If (Arg0)
                {
                    IST0 = 0xFF
                }
                ElseIf (Arg1)
                {
                    IST0 = 0x00
                }
            }

            Method (M006, 2, NotSerialized)
            {
                If (Arg0)
                {
                    IST0 = 0xFF
                }
                ElseIf (Arg1)
                {
                    IST0 = 0x06
                }
            }

            Method (M007, 2, NotSerialized)
            {
                If (Arg0)
                {
                    IST0 = 0xFF
                }
                ElseIf (Arg1)
                {
                    IST0 = 0x07
                }
            }

            Method (M008, 2, NotSerialized)
            {
                If (Arg0)
                {
                    IST0 = 0xFF
                }
                ElseIf (Arg1)
                {
                    IST0 = 0x08
                }
            }

            Method (M009, 1, NotSerialized)
            {
                While (Arg0)
                {
                    IST0 = 0x00
                    Break
                }
            }

            /* If */

            IST0 = 0x01
            M001 (Arg3)
            M600 (Arg0, 0x00, IST0, 0x01)
            M002 (Arg1)
            M600 (Arg0, 0x01, IST0, 0x02)
            M003 (Arg2)
            M600 (Arg0, 0x02, IST0, 0x03)
            M004 (Arg2)
            M600 (Arg0, 0x03, IST0, 0x04)
            /* ElseIf */

            IST0 = 0x05
            M005 (0x00, Arg3)
            M600 (Arg0, 0x04, IST0, 0x05)
            M006 (0x00, Arg1)
            M600 (Arg0, 0x05, IST0, 0x06)
            M007 (0x00, Arg2)
            M600 (Arg0, 0x06, IST0, 0x07)
            M008 (0x00, Arg2)
            M600 (Arg0, 0x07, IST0, 0x08)
            /* While */

            IST0 = 0x09
            M009 (Arg3)
            M600 (Arg0, 0x08, IST0, 0x09)
        }

        /*	Method(m64u, 1) */
        /*	Method(m32u, 1) */
        /* Buffer to String implicit conversion Cases. */
        /* Buffer to String conversion of the Buffer second operand of */
        /* Logical operators when the first operand is evaluated as String. */
        /* LEqual LGreater LGreaterEqual LLess LLessEqual LNotEqual */
        Method (M06F, 3, NotSerialized)
        {
            /* LEqual */

            Local0 = ("21 03 00" == Arg1)
            M600 (Arg0, 0x00, Local0, Ones)
            Local0 = ("21 03 01" == Arg1)
            M600 (Arg0, 0x01, Local0, Zero)
            Local0 = (AUS9 == Arg1)
            M600 (Arg0, 0x02, Local0, Ones)
            Local0 = (AUSA == Arg1)
            M600 (Arg0, 0x03, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUS9)) == Arg1)
                M600 (Arg0, 0x04, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUSA)) == Arg1)
                M600 (Arg0, 0x05, Local0, Zero)
            }

            Local0 = (DerefOf (PAUS [0x09]) == Arg1)
            M600 (Arg0, 0x06, Local0, Ones)
            Local0 = (DerefOf (PAUS [0x0A]) == Arg1)
            M600 (Arg0, 0x07, Local0, Zero)
            /* Method returns String */

            Local0 = (M601 (0x02, 0x09) == Arg1)
            M600 (Arg0, 0x08, Local0, Ones)
            Local0 = (M601 (0x02, 0x0A) == Arg1)
            M600 (Arg0, 0x09, Local0, Zero)
            /* Method returns Reference to String */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x02, 0x09, 0x01)) == Arg1)
                M600 (Arg0, 0x0A, Local0, Ones)
                Local0 = (DerefOf (M602 (0x02, 0x0A, 0x01)) == Arg1)
                M600 (Arg0, 0x0B, Local0, Zero)
            }

            /* LGreater */

            Local0 = ("21 03 00" > Arg1)
            M600 (Arg0, 0x0C, Local0, Zero)
            Local0 = ("21 03 01" > Arg1)
            M600 (Arg0, 0x0D, Local0, Ones)
            Local0 = ("21 03 0 " > Arg1)
            M600 (Arg0, 0x0E, Local0, Zero)
            Local0 = ("21 03 00q" > Arg1)
            M600 (Arg0, 0x0F, Local0, Ones)
            Local0 = (AUS9 > Arg1)
            M600 (Arg0, 0x10, Local0, Zero)
            Local0 = (AUSA > Arg1)
            M600 (Arg0, 0x11, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUS9)) > Arg1)
                M600 (Arg0, 0x12, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUSA)) > Arg1)
                M600 (Arg0, 0x13, Local0, Ones)
            }

            Local0 = (DerefOf (PAUS [0x09]) > Arg1)
            M600 (Arg0, 0x14, Local0, Zero)
            Local0 = (DerefOf (PAUS [0x0A]) > Arg1)
            M600 (Arg0, 0x15, Local0, Ones)
            /* Method returns String */

            Local0 = (M601 (0x02, 0x09) > Arg1)
            M600 (Arg0, 0x16, Local0, Zero)
            Local0 = (M601 (0x02, 0x0A) > Arg1)
            M600 (Arg0, 0x17, Local0, Ones)
            /* Method returns Reference to String */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x02, 0x09, 0x01)) > Arg1)
                M600 (Arg0, 0x18, Local0, Zero)
                Local0 = (DerefOf (M602 (0x02, 0x0A, 0x01)) > Arg1)
                M600 (Arg0, 0x19, Local0, Ones)
            }

            /* LGreaterEqual */

            Local0 = ("21 03 00" >= Arg1)
            M600 (Arg0, 0x1A, Local0, Ones)
            Local0 = ("21 03 01" >= Arg1)
            M600 (Arg0, 0x1B, Local0, Ones)
            Local0 = ("21 03 0 " >= Arg1)
            M600 (Arg0, 0x1C, Local0, Zero)
            Local0 = ("21 03 00q" >= Arg1)
            M600 (Arg0, 0x1D, Local0, Ones)
            Local0 = (AUS9 >= Arg1)
            M600 (Arg0, 0x1E, Local0, Ones)
            Local0 = (AUSA >= Arg1)
            M600 (Arg0, 0x1F, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUS9)) >= Arg1)
                M600 (Arg0, 0x20, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUSA)) >= Arg1)
                M600 (Arg0, 0x21, Local0, Ones)
            }

            Local0 = (DerefOf (PAUS [0x09]) >= Arg1)
            M600 (Arg0, 0x22, Local0, Ones)
            Local0 = (DerefOf (PAUS [0x0A]) >= Arg1)
            M600 (Arg0, 0x23, Local0, Ones)
            /* Method returns String */

            Local0 = (M601 (0x02, 0x09) >= Arg1)
            M600 (Arg0, 0x24, Local0, Ones)
            Local0 = (M601 (0x02, 0x0A) >= Arg1)
            M600 (Arg0, 0x25, Local0, Ones)
            /* Method returns Reference to String */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x02, 0x09, 0x01)) >= Arg1)
                M600 (Arg0, 0x26, Local0, Ones)
                Local0 = (DerefOf (M602 (0x02, 0x0A, 0x01)) >= Arg1)
                M600 (Arg0, 0x27, Local0, Ones)
            }

            /* LLess */

            Local0 = ("21 03 00" < Arg1)
            M600 (Arg0, 0x28, Local0, Zero)
            Local0 = ("21 03 01" < Arg1)
            M600 (Arg0, 0x29, Local0, Zero)
            Local0 = ("21 03 0 " < Arg1)
            M600 (Arg0, 0x2A, Local0, Ones)
            Local0 = ("21 03 00q" < Arg1)
            M600 (Arg0, 0x2B, Local0, Zero)
            Local0 = (AUS9 < Arg1)
            M600 (Arg0, 0x2C, Local0, Zero)
            Local0 = (AUSA < Arg1)
            M600 (Arg0, 0x2D, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUS9)) < Arg1)
                M600 (Arg0, 0x2E, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUSA)) < Arg1)
                M600 (Arg0, 0x2F, Local0, Zero)
            }

            Local0 = (DerefOf (PAUS [0x09]) < Arg1)
            M600 (Arg0, 0x30, Local0, Zero)
            Local0 = (DerefOf (PAUS [0x0A]) < Arg1)
            M600 (Arg0, 0x31, Local0, Zero)
            /* Method returns String */

            Local0 = (M601 (0x02, 0x09) < Arg1)
            M600 (Arg0, 0x32, Local0, Zero)
            Local0 = (M601 (0x02, 0x0A) < Arg1)
            M600 (Arg0, 0x33, Local0, Zero)
            /* Method returns Reference to String */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x02, 0x09, 0x01)) < Arg1)
                M600 (Arg0, 0x34, Local0, Zero)
                Local0 = (DerefOf (M602 (0x02, 0x0A, 0x01)) < Arg1)
                M600 (Arg0, 0x35, Local0, Zero)
            }

            /* LLessEqual */

            Local0 = ("21 03 00" <= Arg1)
            M600 (Arg0, 0x36, Local0, Ones)
            Local0 = ("21 03 01" <= Arg1)
            M600 (Arg0, 0x37, Local0, Zero)
            Local0 = ("21 03 0 " <= Arg1)
            M600 (Arg0, 0x38, Local0, Ones)
            Local0 = ("21 03 00q" <= Arg1)
            M600 (Arg0, 0x39, Local0, Zero)
            Local0 = (AUS9 <= Arg1)
            M600 (Arg0, 0x3A, Local0, Ones)
            Local0 = (AUSA <= Arg1)
            M600 (Arg0, 0x3B, Local0, Zero)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUS9)) <= Arg1)
                M600 (Arg0, 0x3C, Local0, Ones)
                Local0 = (DerefOf (RefOf (AUSA)) <= Arg1)
                M600 (Arg0, 0x3D, Local0, Zero)
            }

            Local0 = (DerefOf (PAUS [0x09]) <= Arg1)
            M600 (Arg0, 0x3E, Local0, Ones)
            Local0 = (DerefOf (PAUS [0x0A]) <= Arg1)
            M600 (Arg0, 0x3F, Local0, Zero)
            /* Method returns String */

            Local0 = (M601 (0x02, 0x09) <= Arg1)
            M600 (Arg0, 0x40, Local0, Ones)
            Local0 = (M601 (0x02, 0x0A) <= Arg1)
            M600 (Arg0, 0x41, Local0, Zero)
            /* Method returns Reference to String */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x02, 0x09, 0x01)) <= Arg1)
                M600 (Arg0, 0x42, Local0, Ones)
                Local0 = (DerefOf (M602 (0x02, 0x0A, 0x01)) <= Arg1)
                M600 (Arg0, 0x43, Local0, Zero)
            }

            /* LNotEqual */

            Local0 = ("21 03 00" != Arg1)
            M600 (Arg0, 0x44, Local0, Zero)
            Local0 = ("21 03 01" != Arg1)
            M600 (Arg0, 0x45, Local0, Ones)
            Local0 = ("21 03 0 " != Arg1)
            M600 (Arg0, 0x46, Local0, Ones)
            Local0 = ("21 03 00q" != Arg1)
            M600 (Arg0, 0x47, Local0, Ones)
            Local0 = (AUS9 != Arg1)
            M600 (Arg0, 0x48, Local0, Zero)
            Local0 = (AUSA != Arg1)
            M600 (Arg0, 0x49, Local0, Ones)
            If (Y078)
            {
                Local0 = (DerefOf (RefOf (AUS9)) != Arg1)
                M600 (Arg0, 0x4A, Local0, Zero)
                Local0 = (DerefOf (RefOf (AUSA)) != Arg1)
                M600 (Arg0, 0x4B, Local0, Ones)
            }

            Local0 = (DerefOf (PAUS [0x09]) != Arg1)
            M600 (Arg0, 0x4C, Local0, Zero)
            Local0 = (DerefOf (PAUS [0x0A]) != Arg1)
            M600 (Arg0, 0x4D, Local0, Ones)
            /* Method returns String */

            Local0 = (M601 (0x02, 0x09) != Arg1)
            M600 (Arg0, 0x4E, Local0, Zero)
            Local0 = (M601 (0x02, 0x0A) != Arg1)
            M600 (Arg0, 0x4F, Local0, Ones)
            /* Method returns Reference to String */

            If (Y500)
            {
                Local0 = (DerefOf (M602 (0x02, 0x09, 0x01)) != Arg1)
                M600 (Arg0, 0x50, Local0, Zero)
                Local0 = (DerefOf (M602 (0x02, 0x0A, 0x01)) != Arg1)
                M600 (Arg0, 0x51, Local0, Ones)
            }

            /* Boundary Cases */

            Local0 = ("21 22 23 24 25 26 27 28 29 2A 2B 2C 2D 2E 2F 30 31 32 33 34 35 36 37 38 39 3A 3B 3C 3D 3E 3F 40 41 42 43 44 45 46 47 48 49 4A 4B 4C 4D 4E 4F 50 51 52 53 54 55 56 57 58 59 5A 5B 5C 5D 5E 5F 60 61 62 63" == Arg2)
            M600 (Arg0, 0x52, Local0, Ones)
            Local0 = ("21 22 23 24 25 26 27 28 29 2A 2B 2C 2D 2E 2F 30 31 32 33 34 35 36 37 38 39 3A 3B 3C 3D 3E 3F 40 41 42 43 44 45 46 47 48 49 4A 4B 4C 4D 4E 4F 50 51 52 53 54 55 56 57 58 59 5A 5B 5C 5D 5E 5F 60 61 62 64" == Arg2)
            M600 (Arg0, 0x53, Local0, Zero)
            Local0 = ("21 22 23 24 25 26 27 28 29 2A 2B 2C 2D 2E 2F 30 31 32 33 34 35 36 37 38 39 3A 3B 3C 3D 3E 3F 40 41 42 43 44 45 46 47 48 49 4A 4B 4C 4D 4E 4F 50 51 52 53 54 55 56 57 58 59 5A 5B 5C 5D 5E 5F 60 61 62 63" > Arg2)
            M600 (Arg0, 0x54, Local0, Zero)
            Local0 = ("21 22 23 24 25 26 27 28 29 2A 2B 2C 2D 2E 2F 30 31 32 33 34 35 36 37 38 39 3A 3B 3C 3D 3E 3F 40 41 42 43 44 45 46 47 48 49 4A 4B 4C 4D 4E 4F 50 51 52 53 54 55 56 57 58 59 5A 5B 5C 5D 5E 5F 60 61 62 64" > Arg2)
            M600 (Arg0, 0x55, Local0, Ones)
            Local0 = ("21 22 23 24 25 26 27 28 29 2A 2B 2C 2D 2E 2F 30 31 32 33 34 35 36 37 38 39 3A 3B 3C 3D 3E 3F 40 41 42 43 44 45 46 47 48 49 4A 4B 4C 4D 4E 4F 50 51 52 53 54 55 56 57 58 59 5A 5B 5C 5D 5E 5F 60 61 62 63" >= Arg2)
            M600 (Arg0, 0x56, Local0, Ones)
            Local0 = ("21 22 23 24 25 26 27 28 29 2A 2B 2C 2D 2E 2F 30 31 32 33 34 35 36 37 38 39 3A 3B 3C 3D 3E 3F 40 41 42 43 44 45 46 47 48 49 4A 4B 4C 4D 4E 4F 50 51 52 53 54 55 56 57 58 59 5A 5B 5C 5D 5E 5F 60 61 62 64" >= Arg2)
            M600 (Arg0, 0x57, Local0, Ones)
            Local0 = ("21 22 23 24 25 26 27 28 29 2A 2B 2C 2D 2E 2F 30 31 32 33 34 35 36 37 38 39 3A 3B 3C 3D 3E 3F 40 41 42 43 44 45 46 47 48 49 4A 4B 4C 4D 4E 4F 50 51 52 53 54 55 56 57 58 59 5A 5B 5C 5D 5E 5F 60 61 62 63" < Arg2)
            M600 (Arg0, 0x58, Local0, Zero)
            Local0 = ("21 22 23 24 25 26 27 28 29 2A 2B 2C 2D 2E 2F 30 31 32 33 34 35 36 37 38 39 3A 3B 3C 3D 3E 3F 40 41 42 43 44 45 46 47 48 49 4A 4B 4C 4D 4E 4F 50 51 52 53 54 55 56 57 58 59 5A 5B 5C 5D 5E 5F 60 61 62 64" < Arg2)
            M600 (Arg0, 0x59, Local0, Zero)
            Local0 = ("21 22 23 24 25 26 27 28 29 2A 2B 2C 2D 2E 2F 30 31 32 33 34 35 36 37 38 39 3A 3B 3C 3D 3E 3F 40 41 42 43 44 45 46 47 48 49 4A 4B 4C 4D 4E 4F 50 51 52 53 54 55 56 57 58 59 5A 5B 5C 5D 5E 5F 60 61 62 63" <= Arg2)
            M600 (Arg0, 0x5A, Local0, Ones)
            Local0 = ("21 22 23 24 25 26 27 28 29 2A 2B 2C 2D 2E 2F 30 31 32 33 34 35 36 37 38 39 3A 3B 3C 3D 3E 3F 40 41 42 43 44 45 46 47 48 49 4A 4B 4C 4D 4E 4F 50 51 52 53 54 55 56 57 58 59 5A 5B 5C 5D 5E 5F 60 61 62 64" <= Arg2)
            M600 (Arg0, 0x5B, Local0, Zero)
            Local0 = ("21 22 23 24 25 26 27 28 29 2A 2B 2C 2D 2E 2F 30 31 32 33 34 35 36 37 38 39 3A 3B 3C 3D 3E 3F 40 41 42 43 44 45 46 47 48 49 4A 4B 4C 4D 4E 4F 50 51 52 53 54 55 56 57 58 59 5A 5B 5C 5D 5E 5F 60 61 62 63" != Arg2)
            M600 (Arg0, 0x5C, Local0, Zero)
            Local0 = ("21 22 23 24 25 26 27 28 29 2A 2B 2C 2D 2E 2F 30 31 32 33 34 35 36 37 38 39 3A 3B 3C 3D 3E 3F 40 41 42 43 44 45 46 47 48 49 4A 4B 4C 4D 4E 4F 50 51 52 53 54 55 56 57 58 59 5A 5B 5C 5D 5E 5F 60 61 62 64" != Arg2)
            M600 (Arg0, 0x5D, Local0, Ones)
        }

        /* Buffer to String conversion of the Buffer second operand of */
        /* Concatenate operator when the first operand is evaluated as String */
        Method (M070, 3, NotSerialized)
        {
            Local0 = Concatenate ("", Arg1)
            M600 (Arg0, 0x00, Local0, BS25)
            Local0 = Concatenate ("1234q", Arg1)
            M600 (Arg0, 0x01, Local0, BS26)
            Local0 = Concatenate (AUS0, Arg1)
            M600 (Arg0, 0x02, Local0, BS25)
            Local0 = Concatenate (AUS1, Arg1)
            M600 (Arg0, 0x03, Local0, BS26)
            If (Y078)
            {
                Local0 = Concatenate (DerefOf (RefOf (AUS0)), Arg1)
                M600 (Arg0, 0x04, Local0, BS25)
                Local0 = Concatenate (DerefOf (RefOf (AUS1)), Arg1)
                M600 (Arg0, 0x05, Local0, BS26)
            }

            Local0 = Concatenate (DerefOf (PAUS [0x00]), Arg1)
            M600 (Arg0, 0x06, Local0, BS25)
            Local0 = Concatenate (DerefOf (PAUS [0x01]), Arg1)
            M600 (Arg0, 0x07, Local0, BS26)
            /* Method returns String */

            Local0 = Concatenate (M601 (0x02, 0x00), Arg1)
            M600 (Arg0, 0x08, Local0, BS25)
            Local0 = Concatenate (M601 (0x02, 0x01), Arg1)
            M600 (Arg0, 0x09, Local0, BS26)
            /* Method returns Reference to String */

            If (Y500)
            {
                Local0 = Concatenate (DerefOf (M602 (0x02, 0x00, 0x01)), Arg1)
                M600 (Arg0, 0x0A, Local0, BS25)
                Local0 = Concatenate (DerefOf (M602 (0x02, 0x01, 0x01)), Arg1)
                M600 (Arg0, 0x0B, Local0, BS26)
            }

            Concatenate ("", Arg1, Local0)
            M600 (Arg0, 0x0C, Local0, BS25)
            Concatenate ("1234q", Arg1, Local0)
            M600 (Arg0, 0x0D, Local0, BS26)
            Concatenate (AUS0, Arg1, Local0)
            M600 (Arg0, 0x0E, Local0, BS25)
            Concatenate (AUS1, Arg1, Local0)
            M600 (Arg0, 0x0F, Local0, BS26)
            If (Y078)
            {
                Concatenate (DerefOf (RefOf (AUS0)), Arg1, Local0)
                M600 (Arg0, 0x10, Local0, BS25)
                Concatenate (DerefOf (RefOf (AUS1)), Arg1, Local0)
                M600 (Arg0, 0x11, Local0, BS26)
            }

            Concatenate (DerefOf (PAUS [0x00]), Arg1, Local0)
            M600 (Arg0, 0x12, Local0, BS25)
            Concatenate (DerefOf (PAUS [0x01]), Arg1, Local0)
            M600 (Arg0, 0x13, Local0, BS26)
            /* Method returns String */

            Concatenate (M601 (0x02, 0x00), Arg1, Local0)
            M600 (Arg0, 0x14, Local0, BS25)
            Concatenate (M601 (0x02, 0x01), Arg1, Local0)
            M600 (Arg0, 0x15, Local0, BS26)
            /* Method returns Reference to String */

            If (Y500)
            {
                Concatenate (DerefOf (M602 (0x02, 0x00, 0x01)), Arg1, Local0)
                M600 (Arg0, 0x16, Local0, BS25)
                Concatenate (DerefOf (M602 (0x02, 0x01, 0x01)), Arg1, Local0)
                M600 (Arg0, 0x17, Local0, BS26)
            }

            /* Boundary Cases */

            Local0 = Concatenate ("", Arg2)
            M600 (Arg0, 0x18, Local0, BS27)
        }

        /*	Method(m071, 1) */
        /*	Method(m072, 1) */
        /*
         * Begin of the test body
         */
        /* Integer to String implicit conversion Cases. */
        /* Integer to String conversion of the Integer second operand of */
        /* Logical operators when the first operand is evaluated as String. */
        /* LEqual LGreater LGreaterEqual LLess LLessEqual LNotEqual */
        If (F64)
        {
            Concatenate (TS, "-m640", Local0)
            SRMT (Local0)
            M640 (Local0, 0xFE7CB391D650A284)
        }
        Else
        {
            Concatenate (TS, "-m320", Local0)
            SRMT (Local0)
            M320 (Local0, 0xC179B3FE)
        }

        /* Integer to String conversion of the Integer second operand of */
        /* Concatenate operator when the first operand is evaluated as String */
        If (F64)
        {
            Concatenate (TS, "-m641", Local0)
            SRMT (Local0)
            M641 (Local0, 0xFE7CB391D650A284)
        }
        Else
        {
            Concatenate (TS, "-m321", Local0)
            SRMT (Local0)
            M321 (Local0, 0xFE7CB391D650A284, 0xC179B3FE)
        }

        /* Integer to String conversion of the Integer value */
        /* of Expression of Case statement when Expression in */
        /* Switch is either static String data or explicitly */
        /* converted to String by ToDecimalString, ToHexString */
        /* or ToString */
        /* */
        /* Note: Expression of Case can be only static data */
        /* Integer to Buffer implicit conversion Cases. */
        /* Integer to Buffer conversion of the Integer second operand of */
        /* Logical operators when the first operand is evaluated as Buffer */
        /* (LEqual, LGreater, LGreaterEqual, LLess, LLessEqual, LNotEqual) */
        If (F64)
        {
            Concatenate (TS, "-m644", Local0)
            SRMT (Local0)
            M644 (Local0, 0xFE7CB391D650A284)
        }
        Else
        {
            Concatenate (TS, "-m324", Local0)
            SRMT (Local0)
            M324 (Local0, 0xC179B3FE)
        }

        /* Integer to Buffer conversion of the both Integer operands of */
        /* Concatenate operator */
        If (F64)
        {
            Concatenate (TS, "-m645", Local0)
            SRMT (Local0)
            M645 (Local0, 0xFE7CB391D650A284)
        }
        Else
        {
            Concatenate (TS, "-m325", Local0)
            SRMT (Local0)
            M325 (Local0, 0xC179B3FE)
        }

        /* Integer to Buffer conversion of the Integer second operand of */
        /* Concatenate operator when the first operand is evaluated as Buffer */
        If (F64)
        {
            Concatenate (TS, "-m646", Local0)
            SRMT (Local0)
            M646 (Local0, 0xFE7CB391D650A284)
        }
        Else
        {
            Concatenate (TS, "-m326", Local0)
            SRMT (Local0)
            M326 (Local0, 0xFE7CB391D650A284, 0xC179B3FE)
        }

        /* Integer to Buffer conversion of the Integer Source operand of */
        /* ToString operator */
        If (F64)
        {
            Concatenate (TS, "-m647", Local0)
            SRMT (Local0)
            M647 (Local0, 0x6E7C534136502214, 0x6E00534136002214)
        }
        Else
        {
            Concatenate (TS, "-m327", Local0)
            SRMT (Local0)
            M327 (Local0, 0x6179534E, 0x6E7C534136002214)
        }

        /* Integer to Buffer conversion of the Integer Source operand of */
        /* Mid operator */
        If (F64)
        {
            Concatenate (TS, "-m648", Local0)
            SRMT (Local0)
            M648 (Local0, 0xFE7CB391D650A284, 0x6E7C534136002214)
        }
        Else
        {
            Concatenate (TS, "-m328", Local0)
            SRMT (Local0)
            M328 (Local0, 0xC179B3FE, 0x6E7C534136002214)
        }

        /* Integer to Buffer conversion of the Integer value of */
        /* Expression of Case statement when Expression in Switch */
        /* is either static Buffer data or explicitly converted to */
        /* Buffer by ToBuffer */
        /* */
        /* Note: Expression of Case can be only static data */
        /* String to Integer implicit conversion Cases. */
        /* String to Integer conversion of the String sole operand */
        /* of the 1-parameter Integer arithmetic operators */
        /* (Decrement, Increment, FindSetLeftBit, FindSetRightBit, Not) */
        If (F64)
        {
            Concatenate (TS, "-m64b", Local0)
            SRMT (Local0)
            M64B (Local0, "0321", "FE7CB391D650A284")
        }
        Else
        {
            Concatenate (TS, "-m32b", Local0)
            SRMT (Local0)
            M32B (Local0, "0321", "C179B3FE")
        }

        /* String to Integer conversion of the String sole operand */
        /* of the LNot Logical Integer operator */
        Concatenate (TS, "-m000", Local0)
        SRMT (Local0)
        M000 (Local0, "0321", "FE7CB391D650A284", "C179B3FE", "0")
        /* String to Integer conversion of the String sole operand */
        /* of the FromBCD and ToBCD conversion operators */
        If (F64)
        {
            Concatenate (TS, "-m64c", Local0)
            SRMT (Local0)
            M64C (Local0, "0321", "FE7CB391D650A284", "3789012345678901", "D76162EE9EC35")
        }
        Else
        {
            Concatenate (TS, "-m32c", Local0)
            SRMT (Local0)
            M32C (Local0, "0321", "FE7CB391D650A284", "90123456", "55F2CC0")
        }

        /* String to Integer conversion of each String operand */
        /* of the 2-parameter Integer arithmetic operators */
        /* Add, And, Divide, Mod, Multiply, NAnd, NOr, Or, */
        /* ShiftLeft, ShiftRight, Subtract, Xor */
        If (F64)
        {
            M64D (Concatenate (TS, "-m64d"))
        }
        Else
        {
            M32D (Concatenate (TS, "-m32d"))
        }

        /* String to Integer conversion of each String operand */
        /* of the 2-parameter Logical Integer operators LAnd and LOr */
        If (F64)
        {
            M64E (Concatenate (TS, "-m64e"))
        }
        Else
        {
            M32E (Concatenate (TS, "-m32e"))
        }

        /* String to Integer conversion of the String second operand of */
        /* Logical operators when the first operand is evaluated as Integer */
        /* (LEqual, LGreater, LGreaterEqual, LLess, LLessEqual, LNotEqual) */
        Concatenate (TS, "-m02b", Local0)
        SRMT (Local0)
        M02B (Local0, "0321")
        If (F64)
        {
            Concatenate (TS, "-m64f", Local0)
            SRMT (Local0)
            M64F (Local0, "FE7CB391D650A284")
        }
        Else
        {
            Concatenate (TS, "-m32f", Local0)
            SRMT (Local0)
            M32F (Local0, "C179B3FE")
        }

        /* String to Integer intermediate conversion of the String second */
        /* operand of Concatenate operator in case the first one is Integer */
        If (F64)
        {
            Concatenate (TS, "-m64g", Local0)
            SRMT (Local0)
            M64G (Local0, "0321", "FE7CB391D650A284")
        }
        Else
        {
            Concatenate (TS, "-m32g", Local0)
            SRMT (Local0)
            M32G (Local0, "0321", "C179B3FE")
        }

        /* String to Integer conversion of the String Length (second) */
        /* operand of the ToString operator */
        Concatenate (TS, "-m02c", Local0)
        SRMT (Local0)
        M02C (Local0, "0321", "B")
        If (F64)
        {
            Concatenate (TS, "-m64h", Local0)
            SRMT (Local0)
            M64H (Local0, "FE7CB391D650A284")
        }
        Else
        {
            Concatenate (TS, "-m32h", Local0)
            SRMT (Local0)
            M32H (Local0, "C179B3FE")
        }

        /* String to Integer conversion of the String Index (second) */
        /* operand of the Index operator */
        Concatenate (TS, "-m02d", Local0)
        SRMT (Local0)
        M02D (Local0, "B")
        /* String to Integer conversion of the String Arg (third) */
        /* operand of the Fatal operator */
        /* (it can only be checked an exception does not occur) */
        Concatenate (TS, "-m02e", Local0)
        SRMT (Local0)
        M02E (Local0, "0321", "FE7CB391D650A284", "C179B3FE")
        /* String to Integer conversion of the String Index and Length */
        /* operands of the Mid operator */
        Concatenate (TS, "-m02f", Local0)
        SRMT (Local0)
        M02F (Local0, "B")
        If (F64)
        {
            Concatenate (TS, "-m64i", Local0)
            SRMT (Local0)
            M64I (Local0, "FE7CB391D650A284", "B")
        }
        Else
        {
            Concatenate (TS, "-m32i", Local0)
            SRMT (Local0)
            M32I (Local0, "C179B3FE", "B")
        }

        /* String to Integer conversion of the String StartIndex */
        /* operand of the Match operator */
        Concatenate (TS, "-m030", Local0)
        SRMT (Local0)
        M030 (Local0, "B")
        /* String to Integer conversion of the String sole operand */
        /* of the Method execution control operators (Sleep, Stall) */
        Concatenate (TS, "-m031", Local0)
        SRMT (Local0)
        M031 (Local0, "0321", "63")
        /* String to Integer conversion of the String TimeoutValue */
        /* (second) operand of the Acquire operator */
        /* Compiler allows only Integer constant as TimeoutValue (Bug 1)
         Concatenate(ts, "-m032", Local0)
         SRMT(Local0)
         m032(Local0, "0321")
         */
        /* String to Integer conversion of the String TimeoutValue */
        /* (second) operand of the Wait operator */
        Concatenate (TS, "-m033", Local0)
        SRMT (Local0)
        M033 (Local0, "0321")
        /* String to Integer conversion of the String value */
        /* of Predicate of the Method execution control statements */
        /* (If, ElseIf, While) */
        Concatenate (TS, "-m034", Local0)
        SRMT (Local0)
        M034 (Local0, "0321", "FE7CB391D650A284", "C179B3FE", "0")
        /* String to Integer conversion of the String value */
        /* of Expression of Case statement when Expression in */
        /* Switch is evaluated as Integer */
        /* */
        /* Note: Expression of Case can be only static data */
        /* String to Buffer implicit conversion Cases. */
        /* String to Buffer conversion of the String second operand of */
        /* Logical operators when the first operand is evaluated as Buffer */
        /* (LEqual, LGreater, LGreaterEqual, LLess, LLessEqual, LNotEqual) */
        Concatenate (TS, "-m035", Local0)
        SRMT (Local0)
        M035 (Local0, "0321", "", "!\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ !\"#$%&\'()*")
        /* String to Buffer conversion of the String second operand of */
        /* Concatenate operator when the first operand is evaluated as Buffer */
        Concatenate (TS, "-m036", Local0)
        SRMT (Local0)
        M036 (Local0, "0321", "", "!\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ !\"#$%&\'()*")
        /* String to Buffer conversion of the String Source operand of */
        /* ToString operator (has a visual effect in shortening of the */
        /* String taken the null character) */
        Concatenate (TS, "-m037", Local0)
        SRMT (Local0)
        M037 (Local0, "0321", "", "!\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ !\"#$%&\'()*")
        /* Buffer to Integer implicit conversion Cases. */
        /* Buffer to Integer conversion of the Buffer sole operand */
        /* of the 1-parameter Integer arithmetic operators */
        /* (Decrement, Increment, FindSetLeftBit, FindSetRightBit, Not) */
        If (F64)
        {
            Concatenate (TS, "-m64l", Local0)
            SRMT (Local0)
            M64L (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
        }
        Else
        {
            Concatenate (TS, "-m32l", Local0)
            SRMT (Local0)
            M32L (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
        }

        /* Buffer to Integer conversion of the Buffer sole operand */
        /* of the LNot Logical Integer operator */
        Concatenate (TS, "-m03a", Local0)
        SRMT (Local0)
        M03A (Local0, Buffer (0x03)
            {
                 0x21, 0x03, 0x00                                 // !..
            }, Buffer (0x09)
            {
                /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                /* 0008 */  0xA5                                             // .
            }, Buffer (0x01)
            {
                 0x00                                             // .
            })
        /* Buffer to Integer conversion of the Buffer sole operand */
        /* of the FromBCD and ToBCD conversion operators */
        If (F64)
        {
            Concatenate (TS, "-m64m", Local0)
            SRMT (Local0)
            M64M (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x08)
                {
                     0x01, 0x89, 0x67, 0x45, 0x23, 0x01, 0x89, 0x37   // ..gE#..7
                }, Buffer (0x07)
                {
                     0x35, 0xEC, 0xE9, 0x2E, 0x16, 0x76, 0x0D         // 5....v.
                })
        }
        Else
        {
            Concatenate (TS, "-m32m", Local0)
            SRMT (Local0)
            M32M (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x04)
                {
                     0x56, 0x34, 0x12, 0x90                           // V4..
                }, Buffer (0x04)
                {
                     0xC0, 0x2C, 0x5F, 0x05                           // .,_.
                })
        }

        /* Buffer to Integer conversion of each Buffer operand */
        /* of the 2-parameter Integer arithmetic operators */
        /* Add, And, Divide, Mod, Multiply, NAnd, NOr, Or, */
        /* ShiftLeft, ShiftRight, Subtract, Xor */
        If (F64)
        {
            M64N (Concatenate (TS, "-m64n"))
        }
        Else
        {
            M32N (Concatenate (TS, "-m32n"))
        }

        /* Buffer to Integer conversion of each Buffer operand */
        /* of the 2-parameter Logical Integer operators LAnd and LOr */
        If (F64)
        {
            M64O (Concatenate (TS, "-m64o"))
        }
        Else
        {
            M32O (Concatenate (TS, "-m32o"))
        }

        /* Buffer to Integer conversion of the Buffer second operand of */
        /* Logical operators when the first operand is evaluated as Integer */
        /* (LEqual, LGreater, LGreaterEqual, LLess, LLessEqual, LNotEqual) */
        Concatenate (TS, "-m065", Local0)
        SRMT (Local0)
        M065 (Local0, Buffer (0x03)
            {
                 0x21, 0x03, 0x00                                 // !..
            })
        If (F64)
        {
            Concatenate (TS, "-m64p", Local0)
            SRMT (Local0)
            M64P (Local0, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
        }
        Else
        {
            Concatenate (TS, "-m32p", Local0)
            SRMT (Local0)
            M32P (Local0, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
        }

        /* Buffer to Integer intermediate conversion of the Buffer second */
        /* operand of Concatenate operator in case the first one is Integer */
        If (F64)
        {
            Concatenate (TS, "-m64q", Local0)
            SRMT (Local0)
            M64Q (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
        }
        Else
        {
            Concatenate (TS, "-m32q", Local0)
            SRMT (Local0)
            M32Q (Local0, Buffer (0x03)
                {
                     0x21, 0x03, 0x00                                 // !..
                }, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
        }

        /* Buffer to Integer conversion of the Buffer Length (second) */
        /* operand of the ToString operator */
        Concatenate (TS, "-m066", Local0)
        SRMT (Local0)
        M066 (Local0, Buffer (0x03)
            {
                 0x21, 0x03, 0x00                                 // !..
            }, Buffer (0x01)
            {
                 0x0B                                             // .
            })
        If (F64)
        {
            Concatenate (TS, "-m64r", Local0)
            SRMT (Local0)
            M64R (Local0, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
        }
        Else
        {
            Concatenate (TS, "-m32r", Local0)
            SRMT (Local0)
            M32R (Local0, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                })
        }

        /* Buffer to Integer conversion of the Buffer Index (second) */
        /* operand of the Index operator */
        Concatenate (TS, "-m067", Local0)
        SRMT (Local0)
        M067 (Local0, Buffer (0x01)
            {
                 0x0B                                             // .
            })
        /* Buffer to Integer conversion of the String Arg (third) */
        /* operand of the Fatal operator */
        /* (it can only be checked an exception does not occur) */
        Concatenate (TS, "-m068", Local0)
        SRMT (Local0)
        M068 (Local0, Buffer (0x03)
            {
                 0x21, 0x03, 0x00                                 // !..
            }, Buffer (0x09)
            {
                /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                /* 0008 */  0xA5                                             // .
            })
        /* Buffer to Integer conversion of the Buffer Index and Length */
        /* operands of the Mid operator */
        Concatenate (TS, "-m069", Local0)
        SRMT (Local0)
        M069 (Local0, Buffer (0x01)
            {
                 0x0B                                             // .
            })
        If (F64)
        {
            Concatenate (TS, "-m64s", Local0)
            SRMT (Local0)
            M64S (Local0, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                }, Buffer (0x01)
                {
                     0x0B                                             // .
                })
        }
        Else
        {
            Concatenate (TS, "-m32s", Local0)
            SRMT (Local0)
            M32S (Local0, Buffer (0x09)
                {
                    /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                    /* 0008 */  0xA5                                             // .
                }, Buffer (0x01)
                {
                     0x0B                                             // .
                })
        }

        /* Buffer to Integer conversion of the Buffer StartIndex */
        /* operand of the Match operator */
        Concatenate (TS, "-m06a", Local0)
        SRMT (Local0)
        M06A (Local0, Buffer (0x01)
            {
                 0x0B                                             // .
            })
        /* Buffer to Integer conversion of the Buffer sole operand */
        /* of the Method execution control operators (Sleep, Stall) */
        Concatenate (TS, "-m06b", Local0)
        SRMT (Local0)
        M06B (Local0, Buffer (0x03)
            {
                 0x21, 0x03, 0x00                                 // !..
            }, Buffer (0x01)
            {
                 0x3F                                             // ?
            })
        /* Buffer to Integer conversion of the Buffer TimeoutValue */
        /* (second) operand of the Acquire operator */
        /* Compiler allows only Integer constant as TimeoutValue (Bug 1)
         Concatenate(ts, "-m06c", Local0)
         SRMT(Local0)
         m06c(Local0, Buffer(3){0x21, 0x03, 0x00})
         */
        /* Buffer to Integer conversion of the Buffer TimeoutValue */
        /* (second) operand of the Wait operator */
        Concatenate (TS, "-m06d", Local0)
        SRMT (Local0)
        M06D (Local0, Buffer (0x03)
            {
                 0x21, 0x03, 0x00                                 // !..
            })
        /* Buffer to Integer conversion of the Buffer value */
        /* of Predicate of the Method execution control statements */
        /* (If, ElseIf, While) */
        Concatenate (TS, "-m06e", Local0)
        SRMT (Local0)
        M06E (Local0, Buffer (0x03)
            {
                 0x21, 0x03, 0x00                                 // !..
            }, Buffer (0x09)
            {
                /* 0000 */  0x84, 0xA2, 0x50, 0xD6, 0x91, 0xB3, 0x7C, 0xFE,  // ..P...|.
                /* 0008 */  0xA5                                             // .
            }, Buffer (0x01)
            {
                 0x00                                             // .
            })
        /* Buffer to Integer conversion of the Buffer value */
        /* of Expression of Case statement when Expression in */
        /* Switch is evaluated as Integer */
        /* */
        /* Note: Expression of Case can be only static data */
        /* Buffer to String implicit conversion Cases. */
        /* Buffer to String conversion of the Buffer second operand of */
        /* Logical operators when the first operand is evaluated as String. */
        /* LEqual LGreater LGreaterEqual LLess LLessEqual LNotEqual */
        Concatenate (TS, "-m06f", Local0)
        SRMT (Local0)
        M06F (Local0, Buffer (0x03)
            {
                 0x21, 0x03, 0x00                                 // !..
            }, Buffer (0x43)
            {
                /* 0000 */  0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,  // !"#$%&'(
                /* 0008 */  0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30,  // )*+,-./0
                /* 0010 */  0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,  // 12345678
                /* 0018 */  0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40,  // 9:;<=>?@
                /* 0020 */  0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,  // ABCDEFGH
                /* 0028 */  0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,  // IJKLMNOP
                /* 0030 */  0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,  // QRSTUVWX
                /* 0038 */  0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60,  // YZ[\]^_`
                /* 0040 */  0x61, 0x62, 0x63                                 // abc
            })
        /* Buffer to String conversion of the Buffer second operand of */
        /* Concatenate operator when the first operand is evaluated as String */
        Concatenate (TS, "-m070", Local0)
        SRMT (Local0)
        M070 (Local0, Buffer (0x03)
            {
                 0x21, 0x03, 0x00                                 // !..
            }, Buffer (0x43)
            {
                /* 0000 */  0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,  // !"#$%&'(
                /* 0008 */  0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30,  // )*+,-./0
                /* 0010 */  0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,  // 12345678
                /* 0018 */  0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40,  // 9:;<=>?@
                /* 0020 */  0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,  // ABCDEFGH
                /* 0028 */  0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,  // IJKLMNOP
                /* 0030 */  0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,  // QRSTUVWX
                /* 0038 */  0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60,  // YZ[\]^_`
                /* 0040 */  0x61, 0x62, 0x63                                 // abc
            })
    }

    /* Run-method */

    Method (OPR5, 0, NotSerialized)
    {
        Debug = "TEST: OPR5, Source Operand"
        M617 ()
    }

