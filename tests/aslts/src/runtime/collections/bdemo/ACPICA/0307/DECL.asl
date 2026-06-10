    /*
     * Some or all of this work - Copyright (c) 2006 - 2021, Intel Corp.
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
     * Bug 307:
     *
     * SUMMARY: Verify ACPICA namespace lookup correctly resolves unqualified
     *          single-segment names when same name exists in both root (\)
     *          and a sub-namespace (\_SB), per ACPI spec section 5.3.
     *
     * SPEC: ACPI 6.x §5.3 - Name Space Lookup Rules
     *       "A name is located by finding the matching name in the current
     *        name space, and then in the parent name space. If the parent
     *        name space does not contain the name, the search continues
     *        recursively until either the name is found or the name space
     *        does not have a parent (the root of the name space)."
     *
     * Issue #1157: ASUS Vivobook DSDT defines both \ASMI and \_SB.ASMI.
     *              Unqualified ASMI calls from within \_SB should resolve to
     *              \_SB.ASMI (current scope) not \ASMI (root). ACPICA is
     *              confirmed spec-compliant for this case.
     */

    /*
     * Namespace result tracking globals.
     * RSLR: set to 1 when the root-level XYZM is invoked.
     * RSLS: set to 2 when the \_SB-level XYZM is invoked.
     */
    Name (RSLR, 0x00)

    /*
     * Root-level method XYZM.
     * When called, sets RSLR=1 to indicate root-level method was resolved.
     */
    Method (XYZM, 1, Serialized)
    {
        Store (0x01, RSLR)
    }

    Scope (\_SB)
    {
        Name (RSLS, 0x00)

        /*
         * \_SB-level method with the same name XYZM as the root-level one.
         * When called, sets RSLS=2 to indicate \_SB method was resolved.
         */
        Method (XYZM, 1, Serialized)
        {
            Store (0x02, RSLS)
        }

        /*
         * Test: unqualified call to XYZM from within \_SB scope.
         * Per ACPI spec §5.3, the search starts in current scope (\_SB),
         * finds \_SB.XYZM, and should NOT fall through to \XYZM.
         */
        Method (TST0, 0, NotSerialized)
        {
            /* Reset tracking variables */
            Store (0x00, \_SB.RSLS)
            Store (0x00, \RSLR)

            /* Unqualified call - must resolve to \_SB.XYZM, not \XYZM */
            XYZM (0x80)

            /* RSLS==2 means \_SB.XYZM was called (correct per spec) */
            If ((\_SB.RSLS != 0x02))
            {
                ERR (__METHOD__, ZFFF, __LINE__, 0x00, 0x00, \_SB.RSLS, 0x02)
            }

            /* RSLR must remain 0 (root method must NOT have been called) */
            If ((\RSLR != 0x00))
            {
                ERR (__METHOD__, ZFFF, __LINE__, 0x00, 0x00, \RSLR, 0x00)
            }
        }

        /*
         * Test: fully-qualified call to \_SB.XYZM.
         * Should always resolve to \_SB.XYZM.
         */
        Method (TST1, 0, NotSerialized)
        {
            Store (0x00, \_SB.RSLS)
            Store (0x00, \RSLR)

            \_SB.XYZM (0x80)

            If ((\_SB.RSLS != 0x02))
            {
                ERR (__METHOD__, ZFFF, __LINE__, 0x00, 0x00, \_SB.RSLS, 0x02)
            }

            If ((\RSLR != 0x00))
            {
                ERR (__METHOD__, ZFFF, __LINE__, 0x00, 0x00, \RSLR, 0x00)
            }
        }

        /*
         * Test: fully-qualified call to \XYZM (root).
         * Should always resolve to \XYZM.
         */
        Method (TST2, 0, NotSerialized)
        {
            Store (0x00, \_SB.RSLS)
            Store (0x00, \RSLR)

            \XYZM (0x80)

            If ((\RSLR != 0x01))
            {
                ERR (__METHOD__, ZFFF, __LINE__, 0x00, 0x00, \RSLR, 0x01)
            }

            If ((\_SB.RSLS != 0x00))
            {
                ERR (__METHOD__, ZFFF, __LINE__, 0x00, 0x00, \_SB.RSLS, 0x00)
            }
        }
    }

    /*
     * Main entry point for bdemo test 307.
     */
    Method (MFF4, 0, NotSerialized)
    {
        CH03 (__METHOD__, 0x00, __LINE__, 0x00, 0x00)

        /* Unqualified call from \_SB scope must resolve to \_SB.XYZM */
        SRMT ("TST0")
        \_SB.TST0 ()

        /* Fully-qualified \_SB.XYZM call */
        SRMT ("TST1")
        \_SB.TST1 ()

        /* Fully-qualified \XYZM (root) call */
        SRMT ("TST2")
        \_SB.TST2 ()

        CH03 (__METHOD__, 0x00, __LINE__, 0x00, 0x00)
    }
