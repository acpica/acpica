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
 * Store Integer/String/Buffer/Package to ThermalZone
 */

// Integer

Method(md5a,, Serialized)
{
	Name(i000, 0xe0385bcd)
	ThermalZone(OOO2) {}

	Store(i000, OOO2)
	Store (0x61, OOO2)

	Store(DeRefof(Refof(OOO2)), Local1)

	if (LNotEqual(Local1, 0x61)) {
		err("", zFFF, 0xc00, 0, 0, Local1, 0x61)
	}
	if (LNotEqual(i000, 0xe0385bcd)) {
		err("", zFFF, 0xc01, 0, 0, i000, 0xe0385bcd)
	}
}

// String

Method(md51,, Serialized)
{
	Name(s000, "String")
	ThermalZone(OOO2) {}

	Store(s000, OOO2)
	Store(Refof(OOO2), Local0)
	Store (0x61, Index(DeRefof(Local0), 3))

	Store(Refof(OOO2), Local0)
	Store(DeRefof(Local0), Local1)

	if (LNotEqual(Local1, "Strang")) {
		err("", zFFF, 0xc02, 0, 0, Local1, "Strang")
	}
	if (LNotEqual(s000, "String")) {
		err("", zFFF, 0xc03, 0, 0, s000, "String")
	}
}

// Buffer

Method(md52,, Serialized)
{
	Name(b000, Buffer() {1,2,3,4})
	ThermalZone(OOO2) {}

	Store(b000, OOO2)

	Store(Refof(OOO2), Local0)
	Store (0x61, Index(DeRefof(Local0), 3))
	Store(DeRefof(Local0), Local1)

	if (LNotEqual(Local1, Buffer() {1,2,3,0x61})) {
		err("", zFFF, 0xc04, 0, 0, Local1, Buffer() {1,2,3,0x61})
	}
	if (LNotEqual(b000, Buffer() {1,2,3,4})) {
		err("", zFFF, 0xc05, 0, 0, b000, Buffer() {1,2,3,4})
	}
}

// Package

Method(md53,, Serialized)
{
	Name(pppp, Package(1){Buffer() {1,2,3,4}})
	ThermalZone(OOO2) {}

	Store(pppp, OOO2)
	Store(Refof(OOO2), Local0)
	Store (0x61, Index(DerefOf(Index(DeRefof(Local0), 0)), 3))

	// OOO2

	Store(DeRefof(Index(DerefOf(Index(DeRefof(Local0), 0)), 0)), Local1)
	if (LNotEqual(Local1, 1)) {
		err("", zFFF, 0xc06, 0, 0, Local1, 1)
	}
	Store(DeRefof(Index(DerefOf(Index(DeRefof(Local0), 0)), 1)), Local1)
	if (LNotEqual(Local1, 2)) {
		err("", zFFF, 0xc07, 0, 0, Local1, 2)
	}
	Store(DeRefof(Index(DerefOf(Index(DeRefof(Local0), 0)), 2)), Local1)
	if (LNotEqual(Local1, 3)) {
		err("", zFFF, 0xc08, 0, 0, Local1, 3)
	}
	Store(DeRefof(Index(DerefOf(Index(DeRefof(Local0), 0)), 3)), Local1)
	if (LNotEqual(Local1, 0x61)) {
		err("", zFFF, 0xc09, 0, 0, Local1, 0x61)
	}

	// pppp

	Store(DeRefof(Index(DerefOf(Index(pppp, 0)), 0)), Local0)
	if (LNotEqual(Local0, 1)) {
		err("", zFFF, 0xc0a, 0, 0, Local0, 1)
	}
	Store(DeRefof(Index(DerefOf(Index(pppp, 0)), 1)), Local0)
	if (LNotEqual(Local0, 2)) {
		err("", zFFF, 0xc0b, 0, 0, Local0, 2)
	}
	Store(DeRefof(Index(DerefOf(Index(pppp, 0)), 2)), Local0)
	if (LNotEqual(Local0, 3)) {
		err("", zFFF, 0xc0c, 0, 0, Local0, 3)
	}
	Store(DeRefof(Index(DerefOf(Index(pppp, 0)), 3)), Local0)
	if (LNotEqual(Local0, 4)) {
		err("", zFFF, 0xc0d, 0, 0, Local0, 4)
	}
}

/* Constant */

// Integer

Method(md54,, Serialized)
{
	ThermalZone(OOO2) {}

	Store(0xe0385bcd, OOO2)
	Store (0x61, OOO2)

	Store(DeRefof(Refof(OOO2)), Local1)

	if (LNotEqual(Local1, 0x61)) {
		err("", zFFF, 0xc0e, 0, 0, Local1, 0x61)
	}
}

// String

Method(md55,, Serialized)
{
	ThermalZone(OOO2) {}

	Store("String", OOO2)
	Store(Refof(OOO2), Local0)
	Store (0x61, Index(DeRefof(Local0), 3))

	Store(Refof(OOO2), Local0)
	Store(DeRefof(Local0), Local1)

	if (LNotEqual(Local1, "Strang")) {
		err("", zFFF, 0xc0f, 0, 0, Local1, "Strang")
	}
}

// Buffer

Method(md56,, Serialized)
{
	ThermalZone(OOO2) {}

	Store(Buffer() {1,2,3,4}, OOO2)

	Store(Refof(OOO2), Local0)
	Store (0x61, Index(DeRefof(Local0), 3))
	Store(DeRefof(Local0), Local1)

	if (LNotEqual(Local1, Buffer() {1,2,3,0x61})) {
		err("", zFFF, 0xc10, 0, 0, Local1, Buffer() {1,2,3,0x61})
	}
}

// Package

Method(md57,, Serialized)
{
	ThermalZone(OOO2) {}

	Store(Package(1){Buffer() {1,2,3,4}}, OOO2)
	Store(Refof(OOO2), Local0)
	Store (0x61, Index(DerefOf(Index(DeRefof(Local0), 0)), 3))

	// OOO2

	Store(DeRefof(Index(DerefOf(Index(DeRefof(Local0), 0)), 0)), Local1)
	if (LNotEqual(Local1, 1)) {
		err("", zFFF, 0xc11, 0, 0, Local1, 1)
	}
	Store(DeRefof(Index(DerefOf(Index(DeRefof(Local0), 0)), 1)), Local1)
	if (LNotEqual(Local1, 2)) {
		err("", zFFF, 0xc12, 0, 0, Local1, 2)
	}
	Store(DeRefof(Index(DerefOf(Index(DeRefof(Local0), 0)), 2)), Local1)
	if (LNotEqual(Local1, 3)) {
		err("", zFFF, 0xc13, 0, 0, Local1, 3)
	}
	Store(DeRefof(Index(DerefOf(Index(DeRefof(Local0), 0)), 3)), Local1)
	if (LNotEqual(Local1, 0x61)) {
		err("", zFFF, 0xc14, 0, 0, Local1, 0x61)
	}
}

Method(md58)
{
	CH03("", 0, 0xf1a, 0, 0)
	md5a()
	md51()
	md52()
	md53()
	md54()
	md55()
	md56()
	md57()
	CH03("", 0, 0xf1b, 0, 0)
}
