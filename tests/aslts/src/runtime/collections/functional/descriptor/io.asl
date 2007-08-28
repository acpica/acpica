/*
 * Copyright (c) 2006, Intel Corp.
 * Copyright (C) 2006, Valery Podrezov <valery.a.podrezov@intel.com>
 * Copyright (C) 2006, Fiodor Suietov <fiodor.f.suietov@intel.com>
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
 * IO Resource Descriptor Macro
 */

Name (p408, Package() {
	ResourceTemplate () {
		IO (Decode10, 0xf0f1, 0xf2f3, 0xf4, 0xf5)
	},
	ResourceTemplate () {
		IO (Decode16, 0xf0f1, 0xf2f3, 0xf4, 0xf5)
	},
	ResourceTemplate () {
		IO (Decode16, 0, 0, 0, 0)
	},
})

/*
ACPI Specification, Revision 3.0, September 2, 2004
6.4.2.5   I/O Port Descriptor 

I/O Port Descriptor layout:

Byte 0 (Tag Bits): Value = 01000111B (0x47) (Type = 0, Small item name = 0x8, Length = 7)

Byte 1 (Information): 0000000dB
Bits[7:1] 	Reserved and must be 0
Bit[0] 	 	(_DEC)
			1	The logical device decodes 16-bit addresses
			0	The logical device only decodes address bits[9:0]

Byte 2 (Range minimum base address, _MIN bits[7:0])
Byte 3 (Range minimum base address, _MIN bits[15:8])

Byte 4 (Range maximum base address, _MAX bits[7:0])
Byte 5 (Range maximum base address, _MAX bits[15:8])

Byte 6 (Base alignment, _ALN): Alignment for minimum base address,
                               increment in 1-byte blocks.

Byte 7 (Range length, _LEN): The number of contiguous I/O ports requested.
*/

Name (p409, Package() {
	Buffer () {0x47, 0x00, 0xf1, 0xf0, 0xf3, 0xf2, 0xf4, 0xf5, 0x79, 0x00},
	Buffer () {0x47, 0x01, 0xf1, 0xf0, 0xf3, 0xf2, 0xf4, 0xf5, 0x79, 0x00},
	Buffer () {0x47, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79, 0x00},
})

Method(RT05)
{
	Name(ts, "RT05")

	Store("TEST: RT05, IO Resource Descriptor Macro", Debug)

	m330(ts, 3, "p408", p408, p409)

	Store (
		ResourceTemplate () {
			IO (Decode16, 0xf0f1, 0xf2f3, 0xf4, 0xf5, IO0)
			IO (Decode16, 0xf0f1, 0xf2f3, 0xf4, 0xf5, IO1)
		}, Local0)

	m331(ts, 1, IO0._DEC, 0x08, IO1._DEC, 0x48, "_DEC")
	m331(ts, 2, IO0._MIN, 2, IO1._MIN, 10, "_MIN")
	m331(ts, 3, IO0._MAX, 4, IO1._MAX, 12, "_MAX")
	m331(ts, 4, IO0._ALN, 6, IO1._ALN, 14, "_ALN")
	m331(ts, 5, IO0._LEN, 7, IO1._LEN, 15, "_LEN")
}
