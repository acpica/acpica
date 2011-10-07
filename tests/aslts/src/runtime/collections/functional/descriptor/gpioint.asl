/*
 * Some or all of this work - Copyright (c) 2006 - 2011, Intel Corp.
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
 * Resource Descriptor macros
 *
 * GpioInt Resource Descriptor Macro
 */

Device (GPII) {}

Name (p452, Package() {
	ResourceTemplate () {
        GpioInt (Edge, ActiveHigh, Exclusive, PullUp, 0x1234,
            "\\GPII", 0xBB, ResourceConsumer, GINX,
            RawDataBuffer () {0x11, 0x22, 0x33, 0x44})
            {0x00A3}
    },

    // Minimal invocation
	ResourceTemplate () {
        GpioInt (Edge, ActiveHigh, , PullUp, , "\\GPII", , , ,)
            {0xF1F2}
	},
})

Name (p453, Package() {
    Buffer () {
        0x8C, 0x20, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01,
        0x00, 0x01, 0x00, 0x00, 0x34, 0x12, 0x17, 0x00,
        0xBB, 0x19, 0x00, 0x1F, 0x00, 0x04, 0x00, 0xA3,
        0x00, 0x5C, 0x47, 0x50, 0x49, 0x49, 0x00, 0x11,
        0x22, 0x33, 0x44,
        0x79, 0x00
    },

    Buffer () {
        0x8C,0x1C,0x00,0x01,0x00,0x01,0x00,
        0x01,0x00,0x01,0x00,0x00,0x00,0x00,0x17,
        0x00,0x00,0x19,0x00,0x1F,0x00,0x00,0x00,
        0xF2,0xF1,0x5C,0x47,0x50,0x49,0x49,0x00,
        0x79,0x00
    }
})

Method(RT21)
{
	Name(ts, "RT21")

	// Emit test header, set the filename

	THDR (ts, "GpioInt Resource Descriptor Macro", __FILE__)

    // Main test case for packages above

	m330(ts, 2, "p452", p452, p453)
	
    // Check resource descriptor tag offsets

	Store (
		ResourceTemplate () {
            GpioInt (Edge, ActiveHigh, Exclusive, PullUp, 0x1234,
                "\\GPII", 0xBB, ResourceConsumer, GIN0,
                RawDataBuffer () {0x11, 0x22, 0x33, 0x44})
                {0x00A3}
            GpioInt (Edge, ActiveHigh, Exclusive, PullUp, 0x1234,
                "\\GPII", 0xBB, ResourceConsumer, GIN1,
                RawDataBuffer () {0x11, 0x22, 0x33, 0x44})
                {0x00A3}
		}, Local0)

    m331(ts, 1, GIN0._MOD, 0x38, GIN1._MOD, 0x150, "_MOD")
    m331(ts, 2, GIN0._POL, 0x39, GIN1._POL, 0x151, "_POL")
    m331(ts, 3, GIN0._SHR, 0x3b, GIN1._SHR, 0x153, "_SHR")
    m331(ts, 4, GIN0._PPI, 0x48, GIN1._PPI, 0x160, "_PPI")
    m331(ts, 5, GIN0._DBT, 0x60, GIN1._DBT, 0x178, "_DBT")
    m331(ts, 6, GIN0._PIN, 0xB8, GIN1._PIN, 0x1d0, "_PIN")
    m331(ts, 7, GIN0._VEN, 0xF8, GIN1._VEN, 0x210, "_VEN")
}


