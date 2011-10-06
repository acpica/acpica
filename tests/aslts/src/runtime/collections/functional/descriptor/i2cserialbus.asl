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
 * I2cSerialBus Resource Descriptor Macro
 */
Device (I2C) {}

Name (p456, Package() {
	ResourceTemplate () {
        I2cSerialBus (0x1234, DeviceInitiated, 0x88775544,
            AddressingMode10Bit, "\\I2C",
            0xEE, ResourceConsumer, I2Cx,
            RawDataBuffer (4) {0xB1, 0xB2, 0xB3, 0xB4})
    },

    // Minimal invocation
	ResourceTemplate () {
        I2cSerialBus (0x1234, , 0x88775544, , "\\I2C", , , ,)
    }
})


Name (p457, Package() {
    Buffer () {
        0x8E,0x18,0x00,0x01,0xEE,
        0x01,0x03,0x01,0x00,0x01,0x0A,0x00,0x44,
        0x55,0x77,0x88,0x34,0x12,0xB1,0xB2,0xB3,
        0xB4,0x5C,0x49,0x32,0x43,0x00,0x79,0x00
    },

    Buffer () {
        0x8E,0x14,
        0x00,0x01,0x00,0x01,0x02,0x00,0x00,0x01,
        0x06,0x00,0x44,0x55,0x77,0x88,0x34,0x12,
        0x5C,0x49,0x32,0x43,0x00,0x79,0x00
    }
})

Method(RT23)
{
	Name(ts, "RT23")

	Store("TEST: RT23, I2cSerialBus Resource Descriptor Macro", Debug)

	m330(ts, 2, "p456", p456, p457)

    // Check resource descriptor tag offsets

	Store (
		ResourceTemplate () {
            I2cSerialBus (0x1234, DeviceInitiated, 0x88775544,
                AddressingMode10Bit, "\\I2C",
                0xEE, ResourceConsumer, I2C0,
                RawDataBuffer (4) {0xB1, 0xB2, 0xB3, 0xB4})
            I2cSerialBus (0x1234, DeviceInitiated, 0x88775544,
                AddressingMode10Bit, "\\I2C",
                0xEE, ResourceConsumer, I2C1,
                RawDataBuffer (4) {0xB1, 0xB2, 0xB3, 0xB4})
		}, Local0)

    m331(ts, 1, I2C0._SLV, 0x30, I2C1._SLV, 0x108, "_SLV")
    m331(ts, 2, I2C0._MOD, 0x38, I2C1._MOD, 0x110, "_MOD")
    m331(ts, 3, I2C0._SPE, 0x60, I2C1._SPE, 0x138, "_SPE")
    m331(ts, 4, I2C0._ADR, 0x80, I2C1._ADR, 0x158, "_ADR")
    m331(ts, 5, I2C0._VEN, 0x90, I2C1._VEN, 0x168, "_VEN")
}


