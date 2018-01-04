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
     * Bug 0092:
     *
     * SUMMARY: Invalid result of Index operator passed with the immediate image of Package
     */
    Method (ME40, 1, Serialized)
    {
        Name (P000, Package (0x08)
        {
            0x01, 
            0x02, 
            0x03, 
            0x04, 
            0x05, 
            0x06, 
            0x07, 
            0x08
        })
        If ((Arg0 == 0x00))
        {
            Debug = "Package as a named object:"
            CH03 ("", 0x00, 0x00, 0x2B, 0x00)
            Local0 = DerefOf (P000 [0x05])
            If ((Local0 != 0x06))
            {
                ERR ("", ZFFF, 0x2E, 0x00, 0x00, Local0, 0x06)
            }

            CH03 ("", 0x00, 0x02, 0x30, 0x00)
        }
        ElseIf ((Arg0 == 0x01))
        {
            Debug = "The same Package but substituted immediately:"
            CH03 ("", 0x00, 0x03, 0x35, 0x00)
            Store (Index (Package (0x08)
                    {
                        0x01, 
                        0x02, 
                        0x03, 
                        0x04, 
                        0x05, 
                        0x06, 
                        0x07, 
                        0x08
                    }, 0x05), Local1)
            If (Y900)
            {
                Local0 = DerefOf (Local1)
                If ((Local0 != 0x06))
                {
                    ERR ("", ZFFF, 0x3A, 0x00, 0x00, Local0, 0x06)
                }

                CH03 ("", 0x00, 0x05, 0x3C, 0x00)
            }
            Else
            {
                CH04 ("", 0x00, 0xFF, 0x00, 0x3E, 0x00, 0x00) /* AE_INDEX_TO_NOT_ATTACHED */
            }
        }
        Else
        {
            CH03 ("", 0x00, 0x07, 0x42, 0x00)
            Local0 = DerefOf (Index (Package (0x08)
                        {
                            0x01, 
                            0x02, 
                            0x03, 
                            0x04, 
                            0x05, 
                            0x06, 
                            0x07, 
                            0x08
                        }, 0x05))
            If (Y900)
            {
                If ((Local0 != 0x06))
                {
                    ERR ("", ZFFF, 0x46, 0x00, 0x00, Local0, 0x06)
                }

                CH03 ("", 0x00, 0x09, 0x48, 0x00)
            }
            Else
            {
                CH04 ("", 0x00, 0xFF, 0x00, 0x4A, 0x00, 0x00) /* AE_INDEX_TO_NOT_ATTACHED */
            }
        }
    }

    Method (ME41, 0, NotSerialized)
    {
        /* 0,1 - success,   2 - crash */

        ME40 (0x00)
        ME40 (0x01)
        ME40 (0x02)
    }

