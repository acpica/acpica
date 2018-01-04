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
     * Bug 183:
     *
     * SUMMARY: Stack OverFlow of ASL compiler on processing the specific recursive method call
     */
    Method (MF79, 1, NotSerialized)
    {
        If (Arg0)
        {
            Return (MF79 ((Arg0 - 0x01)))
        }
        Else
        {
            Return (0x00)
        }
    }

    Method (MF7A, 0, NotSerialized)
    {
        CH03 ("", 0x00, 0x00, 0x2E, 0x00)
        Debug = "mf79(250):"
        Debug = MF79 (0xFA)
        CH03 ("", 0x00, 0x01, 0x33, 0x00)
    }

    Method (M27E, 0, NotSerialized)
    {
        CH03 ("", 0x00, 0x02, 0x38, 0x00)
        Debug = "mf79(248):"
        Debug = MF79 (0xF8)
        CH03 ("", 0x00, 0x03, 0x3D, 0x00)
    }

