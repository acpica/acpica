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
 * GpioIO Resource Descriptor Macro
 */

Device (GPIO) {}

Name (p454, Package() {
	ResourceTemplate () {
        GpioIo (Exclusive, PullUp, 0x0DEB, 0xAAAA, IoRestrictionOutputOnly,
            "\\GPIO", 0xEE, ResourceConsumer, GIOX,
            RawDataBuffer (0x04) {0xC1, 0xC2, 0xC3, 0xC4})
            {0x11E1, 0x22E2, 0x33E3}
    },

    // Minimal invocation
	ResourceTemplate () {
        GpioIo (, PullUp, , , , "\\GPIO", , ,)
            {0x11E1, 0x22E2, 0x33E3}
    }
})


Name (p455, Package() {
    Buffer () {
        0x8C,0x24,0x00,0x01,
        0x01,0x01,0x00,0x02,0x00,0x01,0xAA,0xAA,
        0xEB,0x0D,0x17,0x00,0xEE,0x1D,0x00,0x23,
        0x00,0x04,0x00,0xE1,0x11,0xE2,0x22,0xE3,
        0x33,0x5C,0x47,0x50,0x49,0x4F,0x00,0xC1,
        0xC2,0xC3,0xC4,0x79,0x00
    },

    Buffer () {
        0x8C,0x20,0x00,0x01,0x01,
        0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,
        0x00,0x17,0x00,0x00,0x1D,0x00,0x23,0x00,
        0x00,0x00,0xE1,0x11,0xE2,0x22,0xE3,0x33,
        0x5C,0x47,0x50,0x49,0x4F,0x00,0x79,0x00
    }
})

Method(RT22)
{
	Name(ts, "RT22")

	Store("TEST: RT22, GpioIO Resource Descriptor Macro", Debug)

	m330(ts, 2, "p454", p454, p455)

    // Check resource descriptor tag offsets

	Store (
		ResourceTemplate () {
            GpioIo (Exclusive, PullUp, 0x0DEB, 0xAAAA, IoRestrictionOutputOnly,
                "\\GPIO", 0xEE, ResourceConsumer, GIO0,
                RawDataBuffer (0x04) {0xC1, 0xC2, 0xC3, 0xC4})
                {0x11E1, 0x22E2, 0x33E3}
            GpioIo (Exclusive, PullUp, 0x0DEB, 0xAAAA, IoRestrictionOutputOnly,
                "\\GPIO", 0xEE, ResourceConsumer, GIO1,
                RawDataBuffer (0x04) {0xC1, 0xC2, 0xC3, 0xC4})
                {0x11E1, 0x22E2, 0x33E3}
		}, Local0)

    m331(ts, 1, GIO0._SHR, 0x3b, GIO1._SHR, 0x173, "_SHR")
    m331(ts, 2, GIO0._PPI, 0x48, GIO1._PPI, 0x180, "_PPI")
    m331(ts, 3, GIO0._DBT, 0x60, GIO1._DBT, 0x198, "_DBT")
    m331(ts, 4, GIO0._DRS, 0x50, GIO1._DRS, 0x188, "_DRS")
    m331(ts, 5, GIO0._IOR, 0x38, GIO1._IOR, 0x170, "_IOR")
    m331(ts, 6, GIO0._PIN, 0xB8, GIO1._PIN, 0x1f0, "_PIN")
    m331(ts, 7, GIO0._VEN, 0x118, GIO1._VEN, 0x250, "_VEN")
}


