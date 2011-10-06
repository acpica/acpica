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
 * SpiSerialBus Resource Descriptor Macro
 */
Device (SPI) {}

Name (p458, Package() {
	ResourceTemplate () {
        SpiSerialBus (0x6789, PolarityHigh, FourWireMode, 0x07,
            DeviceInitiated, 0xAABBCCDD, ClockPolarityLow,
            ClockPhaseSecond, "\\SPI",
            0xEE, ResourceConsumer, SPIx,
            RawDataBuffer (0x05) {0xF0, 0xF1, 0xF2, 0xF3, 0xF4})
    },

    // Minimal invocation
	ResourceTemplate () {
        SpiSerialBus (0x6789, , , 0x07, , 0xAABBCCDD, ClockPolarityLow,
            ClockPhaseSecond, "\\SPI", , , ,)
	}
})


Name (p459, Package() {
    Buffer () {
        0x8E,0x1C,0x00,0x01,0xEE,0x02,0x03,0x02,
        0x00,0x01,0x0E,0x00,0xDD,0xCC,0xBB,0xAA,
        0x07,0x01,0x00,0x89,0x67,0xF0,0xF1,0xF2,
        0xF3,0xF4,0x5C,0x53,0x50,0x49,0x00,0x79,
        0x00
    },

    Buffer () {
        0x8E,0x17,0x00,0x01,0x00,0x02,0x02,0x00,
        0x00,0x01,0x09,0x00,0xDD,0xCC,0xBB,0xAA,
        0x07,0x01,0x00,0x89,0x67,0x5C,0x53,0x50,
        0x49,0x00,0x79,0x00
    }
})

Method(RT24)
{
	Name(ts, "RT24")

	Store("TEST: RT24, SpiSerialBus Resource Descriptor Macro", Debug)

	m330(ts, 2, "p458", p458, p459)

    // Check resource descriptor tag offsets

	Store (
		ResourceTemplate () {
            SpiSerialBus (0x6789, PolarityHigh, FourWireMode, 0x07,
                DeviceInitiated, 0xAABBCCDD, ClockPolarityLow,
                ClockPhaseSecond, "\\SPI",
                0xEE, ResourceConsumer, SPI0,
                RawDataBuffer (0x05) {0xF0, 0xF1, 0xF2, 0xF3, 0xF4})
            SpiSerialBus (0x6789, PolarityHigh, FourWireMode, 0x07,
                DeviceInitiated, 0xAABBCCDD, ClockPolarityLow,
                ClockPhaseSecond, "\\SPI",
                0xEE, ResourceConsumer, SPI1,
                RawDataBuffer (0x05) {0xF0, 0xF1, 0xF2, 0xF3, 0xF4})
		}, Local0)


    m331(ts, 1, SPI0._SLV, 0x30, SPI1._SLV, 0x128, "_SLV")
    m331(ts, 2, SPI0._MOD, 0x38, SPI1._MOD, 0x130, "_MOD")
    m331(ts, 3, SPI0._DPL, 0x39, SPI1._DPL, 0x131, "_DPL")
    m331(ts, 4, SPI0._SPE, 0x60, SPI1._SPE, 0x158, "_SPE")
    m331(ts, 5, SPI0._LEN, 0x80, SPI1._LEN, 0x178, "_LEN")
    m331(ts, 6, SPI0._PHA, 0x88, SPI1._PHA, 0x180, "_PHA")
    m331(ts, 7, SPI0._POL, 0x90, SPI1._POL, 0x188, "_POL")
    m331(ts, 8, SPI0._ADR, 0x98, SPI1._ADR, 0x190, "_ADR")
    m331(ts, 9, SPI0._VEN, 0xA8, SPI1._VEN, 0x1A0, "_VEN")
}


