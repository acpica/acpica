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
 * References
 *
 *          (named objects, if present, are the local objects of Method)
 *
 * TABLE 1: all the legal ways to generate references to the
 *          immediate images (constants)
 * TABLE 2: all the legal ways to generate references to the
 *          named objects
 * TABLE 3: all the legal ways to generate references to the
 *          immediate images (constants) being elements of Package
 * TABLE 4: all the legal ways to generate references to the
 *          named objects being elements of Package
 *
 * Producing Reference operators:
 *
 *    Index, RefOf, CondRefOf
 */

/*
???????????????????????????????????????
SEE: after fixing bug 118 of ACPICA change all the local data
     so that they differ the relevant global ones.
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/


Name(z077, 77)


// ///////////////////////////////////////////////////////////////////////////
//
// TABLE 1: all the legal ways to generate references
//          to the immediate images (constants)
//
// ///////////////////////////////////////////////////////////////////////////

Method(m168)
{
	if (y100) {
		ts00("m168")
	} else {
		Store("m168", Debug)
	}

	if (LNot(y900)) {
		Store("Test m168 skipped!", Debug)
		return
	}

	// T1:I2-I4

	Store(Index("123456789", 5), Local0)
	m1a2(Local0, c016, 0, 0, c009, 0x36, 1260)

	Store(Index("qwrtyuiop", 5), Local0)
	m1a2(Local0, c016, 0, 0, c009, 0x75, 1261)

	Store(Index(Buffer() {1,2,3,4,5,6,7,8}, 5), Local0)
	m1a2(Local0, c016, 0, 0, c009, 0x06, 1262)

	Store(Index(Package() {0xabcdef}, 0), Local0)
	m1a2(Local0, c009, 0, 0, c009, 0xabcdef, 1263)

	Store(Index(Package() {"123456789"}, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "123456789", 1264)

	Store(Index(Package() {"qwrtyuiop"}, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "qwrtyuiop", 1265)

	Store(Index(Package() {Buffer() {1,2,3,4,5,6,7,8,9}}, 0), Local0)
	m1a2(Local0, c00b, 0, 0, c00b, Buffer() {1,2,3,4,5,6,7,8,9}, 1266)

	Store(Index(Package() {Package() {0xabcdef}}, 0), Local0)
	m1a2(Local0, c00c, 1, 0, c009, 0xabcdef, 1267)

	Store(Index(Package() {Package() {"123456789"}}, 0), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "123456789", 1268)

	Store(Index(Package() {Package() {"qwrtyuiop"}}, 0), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "qwrtyuiop", 1269)

	Store(Index(Package() {Package() {Buffer() {1,2,3,4,5,6,7,8,9}}}, 0), Local0)
	m1a2(Local0, c00c, 1, 0, c00b, Buffer() {1,2,3,4,5,6,7,8,9}, 1270)

	Store(Index(Package() {Package() {Package() {0xabcdef}}}, 0), Local0)
	m1a2(Local0, c00c, 2, 0, c009, 0xabcdef, 1271)

	Store(Index(Package() {Package() {Package() {"123456789"}}}, 0), Local0)
	m1a2(Local0, c00c, 2, 0, c00a, "123456789", 1272)

	Store(Index(Package() {Package() {Package() {"qwrtyuiop"}}}, 0), Local0)
	m1a2(Local0, c00c, 2, 0, c00a, "qwrtyuiop", 1273)

	Store(Index(Package() {Package() {Package() {Buffer() {1,2,3,4,5,6,7,8,9}}}}, 0), Local0)
	m1a2(Local0, c00c, 2, 0, c00b, Buffer() {1,2,3,4,5,6,7,8,9}, 1274)

	// T1:IR2-IR4

	if (y098) {
		Store(Index("qwrtyuiop", 5, Local1), Local0)
		m1a2(Local0, c016, 0, 0, c009, 0x75, 1275)
		m1a2(Local1, c016, 0, 0, c009, 0x75, 1276)

		Store(Index(Buffer() {1,2,3,4,5,6,7,8}, 5, Local1), Local0)
		m1a2(Local0, c016, 0, 0, c009, 0x06, 1277)
		m1a2(Local1, c016, 0, 0, c009, 0x06, 1278)

		Store(Index(Package() {1,2,3,4,5,6,7,8}, 5, Local1), Local0)
		m1a2(Local0, c009, 0, 0, c009, 0x06, 1279)
		m1a2(Local1, c009, 0, 0, c009, 0x06, 1280)
	}
}

// ///////////////////////////////////////////////////////////////////////////
//
// TABLE 2: all the legal ways to generate references to the named objects
//
// ///////////////////////////////////////////////////////////////////////////

Method(m169,, Serialized)
{
	if (y100) {
		ts00("m169")
	} else {
		Store("m169", Debug)
	}

	// Not Computational Data

	Event(e900)
	Event(e9Z0)
	Mutex(mx90, 0)
	Mutex(mx91, 0)
	Device(d900) { Name(i900, 0xabcd1017) }
	Device(d9Z0) { Name(i900, 0xabcd1017) }
	ThermalZone(tz90) {}
	ThermalZone(tz91) {}
	Processor(pr90, 0, 0xFFFFFFFF, 0) {}
	Processor(pr91, 0, 0xFFFFFFFF, 0) {}
	OperationRegion(r900, SystemMemory, 0x100, 0x100)
	OperationRegion(r9Z0, SystemMemory, 0x100, 0x100)
	PowerResource(pw90, 1, 0) {Method(mmmm){return (0)}}
	PowerResource(pw91, 1, 0) {Method(mmmm){return (0)}}

	// Computational Data

	Name(i900, 0xfe7cb391d65a1000)
	Name(i9Z0, 0xfe7cb391d65a1000)
	Name(i901, 0xc1791001)
	Name(i9Z1, 0xc1791001)
	Name(i902, 0)
	Name(i903, 0xffffffffffffffff)
	Name(i904, 0xffffffff)
	Name(s900, "12341002")
	Name(s9Z0, "12341002")
	Name(s901, "qwrtyu1003")
	Name(s9Z1, "qwrtyu1003")
	Name(b900, Buffer() {0x10,0x11,0x12,0x13,0x14})
	Name(b9Z0, Buffer() {0x10,0x11,0x12,0x13,0x14})

	CreateField(b9Z0, 0, 8, bf90)
	Field(r9Z0, ByteAcc, NoLock, Preserve) {f900,8,f901,8,f902,8,f903,8}
	BankField(r9Z0, f901, 0, ByteAcc, NoLock, Preserve) {bn90,4}
	IndexField(f902, f903, ByteAcc, NoLock, Preserve) {if90,8,if91,8}

	// Elements of Package are Uninitialized

	Name(p900, Package(1) {})

	// Elements of Package are Computational Data

	Name(p901, Package() {0xabcd1004, 0x1122334455661005})
	Name(p902, Package() {"12341006", "q1w2e3r4t5y6u7i81007"})
	Name(p903, Package() {"qwrtyuiop1008", "1234567890abdef0251009"})
	Name(p904, Package() {Buffer() {0xa0,0xa1,0xa2}, Buffer() {0xa3,0xa4}})
	Name(p905, Package() {Package() {0xabc100a, "0xabc100b", "abc100c"}})
	Name(p906, Package() {Package() {"abc100d"}})
	Name(p907, Package() {Package() {"aqwevbgnm100e"}})
	Name(p908, Package() {Package() {Buffer() {0xa5,0xa6,0xa7,0xa8,0xa9}}})
	Name(p909, Package() {Package() {Package() {0xabc100f}}})
	Name(p90a, Package() {Package() {Package() {"12341010"}}})
	Name(p90b, Package() {Package() {Package() {"zxswefas1011"}}})
	Name(p90c, Package() {Package() {Package() {Buffer() {0xaa,0xab,0xac}}}})

	Name(p90d, Package() {i900})
	Name(p90e, Package() {i901})
	Name(p90f, Package() {s900})
	Name(p910, Package() {s901})
	Name(p911, Package() {b9Z0})
	Name(p912, Package() {f900})
	Name(p913, Package() {bn90})
	Name(p914, Package() {if90})
	Name(p915, Package() {bf90})

	// Elements of Package are NOT Computational Data

	Name(p916, Package() {d900})
	Name(p917, Package() {e900})
	Name(p918, Package() {mx90})
	Name(p919, Package() {r9Z0})
	Name(p91a, Package() {pw90})
	Name(p91b, Package() {pr90})
	Name(p91c, Package() {tz90})

	// Methods

	Method(m900) {}

	// Elements of Package are Methods

	Name(p91d, Package() {m900})

	Name(p953, Package() {0xabcd1018, 0xabcd1019})
	Name(p954, Package() {0xabcd1018, 0xabcd1019})


	// Check that all the data (local) are not corrupted
	Method(m000)
	{
	// Computational Data

	// Integer

	Store(ObjectType(i900), Local0)
	if (LNotEqual(Local0, c009)) {
		err(c080, z077, 0x100, 0, 0, Local0, c009)
	}
	if (LNotEqual(i900, 0xfe7cb391d65a1000)) {
		err(c080, z077, 0x101, 0, 0, i900, 0xfe7cb391d65a1000)
	}

	Store(ObjectType(i901), Local0)
	if (LNotEqual(Local0, c009)) {
		err(c080, z077, 0x102, 0, 0, Local0, c009)
	}
	if (LNotEqual(i901, 0xc1791001)) {
		err(c080, z077, 0x103, 0, 0, i901, 0xc1791001)
	}

	Store(ObjectType(i902), Local0)
	if (LNotEqual(Local0, c009)) {
		err(c080, z077, 0x104, 0, 0, Local0, c009)
	}
	if (LNotEqual(i902, 0)) {
		err(c080, z077, 0x105, 0, 0, i902, 0)
	}

	Store(ObjectType(i903), Local0)
	if (LNotEqual(Local0, c009)) {
		err(c080, z077, 0x106, 0, 0, Local0, c009)
	}
	if (LNotEqual(i903, 0xffffffffffffffff)) {
		err(c080, z077, 0x107, 0, 0, i903, 0xffffffffffffffff)
	}

	Store(ObjectType(i904), Local0)
	if (LNotEqual(Local0, c009)) {
		err(c080, z077, 0x108, 0, 0, Local0, c009)
	}
	if (LNotEqual(i904, 0xffffffff)) {
		err(c080, z077, 0x109, 0, 0, i904, 0xffffffff)
	}

	// String

	Store(ObjectType(s900), Local0)
	if (LNotEqual(Local0, c00a)) {
		err(c080, z077, 0x10a, 0, 0, Local0, c00a)
	}
	if (LNotEqual(s900, "12341002")) {
		err(c080, z077, 0x10b, 0, 0, s900, "12341002")
	}

	Store(ObjectType(s901), Local0)
	if (LNotEqual(Local0, c00a)) {
		err(c080, z077, 0x10c, 0, 0, Local0, c00a)
	}
	if (LNotEqual(s901, "qwrtyu1003")) {
		err(c080, z077, 0x10d, 0, 0, s901, "qwrtyu1003")
	}

	// Buffer

	Store(ObjectType(b900), Local0)
	if (LNotEqual(Local0, c00b)) {
		err(c080, z077, 0x10e, 0, 0, Local0, c00b)
	}
	if (LNotEqual(b900, Buffer() {0x10,0x11,0x12,0x13,0x14})) {
		err(c080, z077, 0x10f, 0, 0, b900, Buffer() {0x10,0x11,0x12,0x13,0x14})
	}

	// Buffer Field

	Store(ObjectType(bf90), Local0)
	if (LNotEqual(Local0, c016)) {
		err(c080, z077, 0x110, 0, 0, Local0, c016)
	}
	if (LNotEqual(bf90, 0x10)) {
		err(c080, z077, 0x111, 0, 0, bf90, 0x10)
	}

	// One level Package

	Store(Index(p900, 0), Local0)
	Store(ObjectType(Local0), Local1)
	if (LNotEqual(Local1, c008)) {
		err(c080, z077, 0x112, 0, 0, Local1, c008)
	}

	Store(Index(p901, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c009)) {
		err(c080, z077, 0x113, 0, 0, Local2, c009)
	}
	if (LNotEqual(Local1, 0xabcd1004)) {
		err(c080, z077, 0x114, 0, 0, Local1, 0xabcd1004)
	}

	Store(Index(p901, 1), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c009)) {
		err(c080, z077, 0x115, 0, 0, Local2, c009)
	}
	if (LNotEqual(Local1, 0x1122334455661005)) {
		err(c080, z077, 0x116, 0, 0, Local1, 0x1122334455661005)
	}

	Store(Index(p902, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00a)) {
		err(c080, z077, 0x117, 0, 0, Local2, c00a)
	}
	if (LNotEqual(Local1, "12341006")) {
		err(c080, z077, 0x118, 0, 0, Local1, "12341006")
	}

	Store(Index(p902, 1), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00a)) {
		err(c080, z077, 0x119, 0, 0, Local2, c00a)
	}
	if (LNotEqual(Local1, "q1w2e3r4t5y6u7i81007")) {
		err(c080, z077, 0x11a, 0, 0, Local1, "q1w2e3r4t5y6u7i81007")
	}

	Store(Index(p903, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00a)) {
		err(c080, z077, 0x11b, 0, 0, Local2, c00a)
	}
	if (LNotEqual(Local1, "qwrtyuiop1008")) {
		err(c080, z077, 0x11c, 0, 0, Local1, "qwrtyuiop1008")
	}

	Store(Index(p903, 1), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00a)) {
		err(c080, z077, 0x11d, 0, 0, Local2, c00a)
	}
	if (LNotEqual(Local1, "1234567890abdef0251009")) {
		err(c080, z077, 0x11e, 0, 0, Local1, "1234567890abdef0251009")
	}

	Store(Index(p904, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00b)) {
		err(c080, z077, 0x11f, 0, 0, Local2, c00b)
	}
	if (LNotEqual(Local1, Buffer() {0xa0,0xa1,0xa2})) {
		err(c080, z077, 0x120, 0, 0, Local1, Buffer() {0xa0,0xa1,0xa2})
	}

	Store(Index(p904, 1), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00b)) {
		err(c080, z077, 0x121, 0, 0, Local2, c00b)
	}
	if (LNotEqual(Local1, Buffer() {0xa3,0xa4})) {
		err(c080, z077, 0x122, 0, 0, Local1, Buffer() {0xa3,0xa4})
	}

	// Two level Package

	Store(Index(p905, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c009)) {
		err(c080, z077, 0x123, 0, 0, Local4, c009)
	}
	if (LNotEqual(Local3, 0xabc100a)) {
		err(c080, z077, 0x124, 0, 0, Local3, 0xabc100a)
	}

	Store(Index(p905, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 1), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c00a)) {
		err(c080, z077, 0x125, 0, 0, Local4, c00a)
	}
	if (LNotEqual(Local3, "0xabc100b")) {
		err(c080, z077, 0x126, 0, 0, Local3, "0xabc100b")
	}

	Store(Index(p905, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 2), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c00a)) {
		err(c080, z077, 0x127, 0, 0, Local4, c00a)
	}
	if (LNotEqual(Local3, "abc100c")) {
		err(c080, z077, 0x128, 0, 0, Local3, "abc100c")
	}

	Store(Index(p906, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c00a)) {
		err(c080, z077, 0x129, 0, 0, Local4, c00a)
	}
	if (LNotEqual(Local3, "abc100d")) {
		err(c080, z077, 0x12a, 0, 0, Local3, "abc100d")
	}

	Store(Index(p907, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c00a)) {
		err(c080, z077, 0x12b, 0, 0, Local4, c00a)
	}
	if (LNotEqual(Local3, "aqwevbgnm100e")) {
		err(c080, z077, 0x12c, 0, 0, Local3, "aqwevbgnm100e")
	}

	Store(Index(p908, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c00b)) {
		err(c080, z077, 0x12d, 0, 0, Local4, c00b)
	}
	if (LNotEqual(Local3, Buffer() {0xa5,0xa6,0xa7,0xa8,0xa9})) {
		err(c080, z077, 0x12e, 0, 0, Local3, Buffer() {0xa5,0xa6,0xa7,0xa8,0xa9})
	}

	// Three level Package

	Store(Index(p909, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(Index(Local3, 0), Local4)
	Store(DerefOf(Local4), Local5)
	Store(ObjectType(Local5), Local6)
	if (LNotEqual(Local6, c009)) {
		err(c080, z077, 0x12f, 0, 0, Local6, c009)
	}
	if (LNotEqual(Local5, 0xabc100f)) {
		err(c080, z077, 0x130, 0, 0, Local5, 0xabc100f)
	}

	Store(Index(p90a, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(Index(Local3, 0), Local4)
	Store(DerefOf(Local4), Local5)
	Store(ObjectType(Local5), Local6)
	if (LNotEqual(Local6, c00a)) {
		err(c080, z077, 0x131, 0, 0, Local6, c00a)
	}
	if (LNotEqual(Local5, "12341010")) {
		err(c080, z077, 0x132, 0, 0, Local5, "12341010")
	}

	Store(Index(p90b, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(Index(Local3, 0), Local4)
	Store(DerefOf(Local4), Local5)
	Store(ObjectType(Local5), Local6)
	if (LNotEqual(Local6, c00a)) {
		err(c080, z077, 0x133, 0, 0, Local6, c00a)
	}
	if (LNotEqual(Local5, "zxswefas1011")) {
		err(c080, z077, 0x134, 0, 0, Local5, "zxswefas1011")
	}

	Store(Index(p90c, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(Index(Local3, 0), Local4)
	Store(DerefOf(Local4), Local5)
	Store(ObjectType(Local5), Local6)
	if (LNotEqual(Local6, c00b)) {
		err(c080, z077, 0x135, 0, 0, Local6, c00b)
	}
	if (LNotEqual(Local5, Buffer() {0xaa,0xab,0xac})) {
		err(c080, z077, 0x136, 0, 0, Local5, Buffer() {0xaa,0xab,0xac})
	}

	Store(Index(p953, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c009)) {
		err(c080, z077, 0x137, 0, 0, Local2, c009)
	}
	if (LNotEqual(Local1, 0xabcd1018)) {
		err(c080, z077, 0x138, 0, 0, Local1, 0xabcd1018)
	}

	Store(Index(p953, 1), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c009)) {
		err(c080, z077, 0x139, 0, 0, Local2, c009)
	}
	if (LNotEqual(Local1, 0xabcd1019)) {
		err(c080, z077, 0x13a, 0, 0, Local1, 0xabcd1019)
	}

	// Not Computational Data

	m1aa(c080, e900, c00f, 0, 0x13b)
	m1aa(c080, mx90, c011, 0, 0x13c)
	m1aa(c080, d900, c00e, 0, 0x13d)
	if (y508) {
		m1aa(c080, tz90, c015, 0, 0x13e)
	}
	m1aa(c080, pr90, c014, 0, 0x13f)
	m1aa(c080, r900, c012, 0, 0x140)
	m1aa(c080, pw90, c013, 0, 0x141)

/*
 *	// Field Unit (Field)
 *
 *	if (LNotEqual(f900, 0xd7)) {
 *		err(c080, z077, 0x137, 0, 0, f900, 0xd7)
 *	}
 *
 *	// Field Unit (IndexField)
 *
 *	if (LNotEqual(if90, 0xd7)) {
 *		err(c080, z077, 0x138, 0, 0, if90, 0xd7)
 *	}
 */
	} /* m000 */


	// T2:I2-I4

	if (y114) {
		Store(Index(m902, 0), Local0)
		m1a0(Local0, c010, Ones, 0)
	}

	// Computational Data

	Store(Index(s900, 0), Local0)
	m1a2(Local0, c016, 0, 0, c009, 0x31, 1)

	Store(Index(s901, 2), Local0)
	m1a2(Local0, c016, 0, 0, c009, 0x72, 2)

	Store(Index(b900, 3), Local0)
	m1a2(Local0, c016, 0, 0, c009, 0x13, 3)

	// Package

	Store(Index(p953, 0), Local0)
	m1a2(Local0, c009, 0, 0, c009, 0xabcd1018, 1006)

	// Elements of Package are Uninitialized

	if (y104) {
		Store(Index(p900, 0), Local0)
		m1a0(Local0, c008, Ones, 4)
	}

	// Elements of Package are Computational Data

	Store(Index(p901, 0), Local0)
	m1a2(Local0, c009, 0, 0, c009, 0xabcd1004, 5)

	Store(Index(p901, 1), Local0)
	m1a2(Local0, c009, 0, 0, c009, 0x1122334455661005, 6)

	Store(Index(p902, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "12341006", 7)

	Store(Index(p902, 1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "q1w2e3r4t5y6u7i81007", 8)

	Store(Index(p903, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "qwrtyuiop1008", 9)

	Store(Index(p903, 1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "1234567890abdef0251009", 10)

	Store(Index(p904, 0), Local0)
	m1a2(Local0, c00b, 0, 0, c00b, Buffer() {0xa0,0xa1,0xa2}, 11)

	Store(Index(p905, 0), Local0)
	m1a2(Local0, c00c, 1, 0, c009, 0xabc100a, 12)

	Store(Index(p905, 0), Local0)
	m1a2(Local0, c00c, 1, 1, c00a, "0xabc100b", 13)

	Store(Index(p906, 0), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "abc100d", 14)

	Store(Index(p907, 0), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "aqwevbgnm100e", 15)

	Store(Index(p908, 0), Local0)
	m1a2(Local0, c00c, 1, 0, c00b, Buffer() {0xa5,0xa6,0xa7,0xa8,0xa9}, 16)

	Store(Index(p909, 0), Local0)
	m1a2(Local0, c00c, 2, 0, c009, 0xabc100f, 17)

	Store(Index(p90a, 0), Local0)
	m1a2(Local0, c00c, 2, 0, c00a, "12341010", 18)

	Store(Index(p90b, 0), Local0)
	m1a2(Local0, c00c, 2, 0, c00a, "zxswefas1011", 19)

	Store(Index(p90c, 0), Local0)
	m1a2(Local0, c00c, 2, 0, c00b, Buffer() {0xaa,0xab,0xac}, 20)

	// In-package name strings are String typed, not ObjectReference
	// typed.

	// Elements of Package are NameString

	Store(Index(p90d, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "I900", 21)

	Store(Index(p90e, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "I901", 22)

	Store(Index(p90f, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "S900", 23)

	Store(Index(p910, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "S901", 24)

	Store(Index(p911, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "B9Z0", 25)

	Store(Index(p912, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "F900", 26)

	Store(Index(p913, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "BN90", 27)

	Store(Index(p914, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "IF90", 28)

	Store(Index(p915, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "BF90", 29)

	Store(Index(p916, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "D900", 30)

	Store(Index(p917, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "E900", 31)

	Store(Index(p918, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "MX90", 32)

	Store(Index(p919, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "R9Z0", 33)

	Store(Index(p91a, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "PW90", 34)

	Store(Index(p91b, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "PR90", 35)

	Store(Index(p91c, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "TZ90", 36)

	Store(Index(p91d, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "M900", 36)

	// T2:IR2-IR4

	// Computational Data

	Store(Index(s900, 0, Local1), Local0)
	m1a2(Local0, c016, 0, 0, c009, 0x31, 91)
	m1a2(Local1, c016, 0, 0, c009, 0x31, 92)

	Store(Index(s901, 2, Local1), Local0)
	m1a2(Local0, c016, 0, 0, c009, 0x72, 93)
	m1a2(Local1, c016, 0, 0, c009, 0x72, 94)

	Store(Index(b900, 4, Local1), Local0)
	m1a2(Local0, c016, 0, 0, c009, 0x14, 95)
	m1a2(Local1, c016, 0, 0, c009, 0x14, 96)

	// Elements of Package are Uninitialized

	if (y104) {
		Store(Index(p900, 0, Local1), Local0)
		m1a0(Local0, c008, Ones, 97)
		m1a0(Local1, c008, Ones, 98)
	}

	// Elements of Package are Computational Data

	Store(Index(p901, 0, Local1), Local0)
	m1a2(Local0, c009, 0, 0, c009, 0xabcd1004, 99)
	m1a2(Local1, c009, 0, 0, c009, 0xabcd1004, 100)

	Store(Index(p901, 1, Local1), Local0)
	m1a2(Local0, c009, 0, 0, c009, 0x1122334455661005, 101)
	m1a2(Local1, c009, 0, 0, c009, 0x1122334455661005, 102)

	Store(Index(p902, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "12341006", 103)
	m1a2(Local1, c00a, 0, 0, c00a, "12341006", 104)

	Store(Index(p902, 1, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "q1w2e3r4t5y6u7i81007", 105)
	m1a2(Local1, c00a, 0, 0, c00a, "q1w2e3r4t5y6u7i81007", 106)

	Store(Index(p903, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "qwrtyuiop1008", 107)
	m1a2(Local1, c00a, 0, 0, c00a, "qwrtyuiop1008", 108)

	Store(Index(p903, 1, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "1234567890abdef0251009", 109)
	m1a2(Local1, c00a, 0, 0, c00a, "1234567890abdef0251009", 110)

	Store(Index(p904, 0, Local1), Local0)
	m1a2(Local0, c00b, 0, 0, c00b, Buffer() {0xa0,0xa1,0xa2}, 111)
	m1a2(Local1, c00b, 0, 0, c00b, Buffer() {0xa0,0xa1,0xa2}, 112)

	Store(Index(p905, 0, Local1), Local0)
	m1a2(Local0, c00c, 1, 0, c009, 0xabc100a, 113)
	m1a2(Local1, c00c, 1, 0, c009, 0xabc100a, 114)

	Store(Index(p905, 0, Local1), Local0)
	m1a2(Local0, c00c, 1, 1, c00a, "0xabc100b", 115)
	m1a2(Local1, c00c, 1, 1, c00a, "0xabc100b", 116)

	Store(Index(p906, 0, Local1), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "abc100d", 117)
	m1a2(Local1, c00c, 1, 0, c00a, "abc100d", 118)

	Store(Index(p907, 0, Local1), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "aqwevbgnm100e", 119)
	m1a2(Local1, c00c, 1, 0, c00a, "aqwevbgnm100e", 120)

	Store(Index(p908, 0, Local1), Local0)
	m1a2(Local0, c00c, 1, 0, c00b, Buffer() {0xa5,0xa6,0xa7,0xa8,0xa9}, 121)
	m1a2(Local1, c00c, 1, 0, c00b, Buffer() {0xa5,0xa6,0xa7,0xa8,0xa9}, 122)

	Store(Index(p909, 0, Local1), Local0)
	m1a2(Local0, c00c, 2, 0, c009, 0xabc100f, 123)
	m1a2(Local1, c00c, 2, 0, c009, 0xabc100f, 124)

	Store(Index(p90a, 0, Local1), Local0)
	m1a2(Local0, c00c, 2, 0, c00a, "12341010", 125)
	m1a2(Local1, c00c, 2, 0, c00a, "12341010", 126)

	Store(Index(p90b, 0, Local1), Local0)
	m1a2(Local0, c00c, 2, 0, c00a, "zxswefas1011", 127)
	m1a2(Local1, c00c, 2, 0, c00a, "zxswefas1011", 128)

	Store(Index(p90c, 0, Local1), Local0)
	m1a2(Local0, c00c, 2, 0, c00b, Buffer() {0xaa,0xab,0xac}, 129)
	m1a2(Local1, c00c, 2, 0, c00b, Buffer() {0xaa,0xab,0xac}, 130)

	// In-package name strings are String typed, not ObjectReference
	// typed.

	// Elements of Package are NameString

	Store(Index(p90d, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "I900", 131)
	m1a2(Local1, c00a, 0, 0, c00a, "I900", 132)

	Store(Index(p90e, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "I901", 133)
	m1a2(Local1, c00a, 0, 0, c00a, "I901", 134)

	Store(Index(p90f, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "S900", 135)
	m1a2(Local1, c00a, 0, 0, c00a, "S900", 136)

	Store(Index(p910, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "S901", 137)
	m1a2(Local1, c00a, 0, 0, c00a, "S901", 138)

	Store(Index(p911, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "B9Z0", 139)
	m1a2(Local1, c00a, 0, 0, c00a, "B9Z0", 140)

	Store(Index(p912, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "F900", 141)
	m1a2(Local1, c00a, 0, 0, c00a, "F900", 142)

	Store(Index(p913, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "BN90", 143)
	m1a2(Local1, c00a, 0, 0, c00a, "BN90", 144)

	Store(Index(p914, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "IF90", 145)
	m1a2(Local1, c00a, 0, 0, c00a, "IF90", 146)

	Store(Index(p915, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "BF90", 147)
	m1a2(Local1, c00a, 0, 0, c00a, "BF90", 148)

	Store(Index(p916, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "D900", 149)
	m1a2(Local1, c00a, 0, 0, c00a, "D900", 150)

	Store(Index(p917, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "E900", 151)
	m1a2(Local1, c00a, 0, 0, c00a, "E900", 152)

	Store(Index(p918, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "MX90", 153)
	m1a2(Local1, c00a, 0, 0, c00a, "MX90", 154)

	Store(Index(p919, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "R9Z0", 155)
	m1a2(Local1, c00a, 0, 0, c00a, "R9Z0", 156)

	Store(Index(p91a, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "PW90", 157)
	m1a2(Local1, c00a, 0, 0, c00a, "PW90", 158)

	Store(Index(p91b, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "PR90", 159)
	m1a2(Local1, c00a, 0, 0, c00a, "PR90", 160)

	Store(Index(p91c, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "TZ90", 161)
	m1a2(Local1, c00a, 0, 0, c00a, "TZ90", 162)

	Store(Index(p91d, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "M900", 163)
	m1a2(Local1, c00a, 0, 0, c00a, "M900", 164)

	m000()
	m1a6()
}

// arg0 - writing mode
Method(m16a, 1, Serialized)
{
	if (y100) {
		ts00("m16a")
	} else {
		Store("m16a", Debug)
	}

	// Not Computational Data

	Event(e900)
	Event(e9Z0)
	Mutex(mx90, 0)
	Mutex(mx91, 0)
	Device(d900) { Name(i900, 0xabcd2017) }
	Device(d9Z0) { Name(i900, 0xabcd2017) }
	ThermalZone(tz90) {}
	ThermalZone(tz91) {}
	Processor(pr90, 0, 0xFFFFFFFF, 0) {}
	Processor(pr91, 0, 0xFFFFFFFF, 0) {}
	OperationRegion(r900, SystemMemory, 0x100, 0x100)
	OperationRegion(r9Z0, SystemMemory, 0x100, 0x100)
	PowerResource(pw90, 1, 0) {Method(mmmm){return (0)}}
	PowerResource(pw91, 1, 0) {Method(mmmm){return (0)}}

	// Computational Data

	Name(i900, 0xfe7cb391d65a2000)
	Name(i9Z0, 0xfe7cb391d65a2000)
	Name(i901, 0xc1792001)
	Name(i9Z1, 0xc1792001)
	Name(i902, 0)
	Name(i903, 0xffffffffffffffff)
	Name(i904, 0xffffffff)
	Name(s900, "12342002")
	Name(s9Z0, "12342002")
	Name(s901, "qwrtyu2003")
	Name(s9Z1, "qwrtyu2003")
	Name(b900, Buffer() {0xc0,0xc1,0xc2,0xc3,0xc4})
	Name(b9Z0, Buffer() {0xc0,0xc1,0xc2,0xc3,0xc4})

	CreateField(b9Z0, 0, 8, bf90)
	Field(r9Z0, ByteAcc, NoLock, Preserve) {f900,8,f901,8,f902,8,f903,8}
	BankField(r9Z0, f901, 0, ByteAcc, NoLock, Preserve) {bn90,4}
	IndexField(f902, f903, ByteAcc, NoLock, Preserve) {if90,8,if91,8}

	// Elements of Package are Uninitialized

	Name(p900, Package(1) {})

	// Elements of Package are Computational Data

	Name(p901, Package() {0xabcd2004, 0x1122334455662005})
	Name(p902, Package() {"12342006", "q1w2e3r4t5y6u7i82007"})
	Name(p903, Package() {"qwrtyuiop2008", "1234567890abdef0252009"})
	Name(p904, Package() {Buffer() {0xc5,0xc6,0xc7}, Buffer() {0xc8,0xc9}})
	Name(p905, Package() {Package() {0xabc200a, "0xabc200b", "abc200c"}})
	Name(p906, Package() {Package() {"abc200d"}})
	Name(p907, Package() {Package() {"aqwevbgnm200e"}})
	Name(p908, Package() {Package() {Buffer() {0xca,0xcb,0xcc,0xcd,0xce}}})
	Name(p909, Package() {Package() {Package() {0xabc200f}}})
	Name(p90a, Package() {Package() {Package() {"12342010"}}})
	Name(p90b, Package() {Package() {Package() {"zxswefas2011"}}})
	Name(p90c, Package() {Package() {Package() {Buffer() {0xcf,0xd0,0xd1}}}})

	Name(p90d, Package() {i900})
	Name(p90e, Package() {i901})
	Name(p90f, Package() {s900})
	Name(p910, Package() {s901})
	Name(p911, Package() {b9Z0})
	Name(p912, Package() {f900})
	Name(p913, Package() {bn90})
	Name(p914, Package() {if90})
	Name(p915, Package() {bf90})

	// Elements of Package are NOT Computational Data

	Name(p916, Package() {d900})
	Name(p917, Package() {e900})
	Name(p918, Package() {mx90})
	Name(p919, Package() {r9Z0})
	Name(p91a, Package() {pw90})
	Name(p91b, Package() {pr90})
	Name(p91c, Package() {tz90})

	// Methods

	Method(m900) {}

	// Elements of Package are Methods

	Name(p91d, Package() {m900})

	Name(p953, Package() {0xabcd2018, 0xabcd2019})
	Name(p954, Package() {0xabcd2018, 0xabcd2019})


	// Check that all the data (local) are not corrupted
	Method(m000)
	{
	// Computational Data

	// Integer

	Store(ObjectType(i900), Local0)
	if (LNotEqual(Local0, c009)) {
		err(c080, z077, 0x100, 0, 0, Local0, c009)
	}
	if (LNotEqual(i900, 0xfe7cb391d65a2000)) {
		err(c080, z077, 0x101, 0, 0, i900, 0xfe7cb391d65a2000)
	}

	Store(ObjectType(i901), Local0)
	if (LNotEqual(Local0, c009)) {
		err(c080, z077, 0x102, 0, 0, Local0, c009)
	}
	if (LNotEqual(i901, 0xc1792001)) {
		err(c080, z077, 0x103, 0, 0, i901, 0xc1792001)
	}

	Store(ObjectType(i902), Local0)
	if (LNotEqual(Local0, c009)) {
		err(c080, z077, 0x104, 0, 0, Local0, c009)
	}
	if (LNotEqual(i902, 0)) {
		err(c080, z077, 0x105, 0, 0, i902, 0)
	}

	Store(ObjectType(i903), Local0)
	if (LNotEqual(Local0, c009)) {
		err(c080, z077, 0x106, 0, 0, Local0, c009)
	}
	if (LNotEqual(i903, 0xffffffffffffffff)) {
		err(c080, z077, 0x107, 0, 0, i903, 0xffffffffffffffff)
	}

	Store(ObjectType(i904), Local0)
	if (LNotEqual(Local0, c009)) {
		err(c080, z077, 0x108, 0, 0, Local0, c009)
	}
	if (LNotEqual(i904, 0xffffffff)) {
		err(c080, z077, 0x109, 0, 0, i904, 0xffffffff)
	}

	// String

	Store(ObjectType(s900), Local0)
	if (LNotEqual(Local0, c00a)) {
		err(c080, z077, 0x10a, 0, 0, Local0, c00a)
	}
	if (LNotEqual(s900, "12342002")) {
		err(c080, z077, 0x10b, 0, 0, s900, "12342002")
	}

	Store(ObjectType(s901), Local0)
	if (LNotEqual(Local0, c00a)) {
		err(c080, z077, 0x10c, 0, 0, Local0, c00a)
	}
	if (LNotEqual(s901, "qwrtyu2003")) {
		err(c080, z077, 0x10d, 0, 0, s901, "qwrtyu2003")
	}

	// Buffer

	Store(ObjectType(b900), Local0)
	if (LNotEqual(Local0, c00b)) {
		err(c080, z077, 0x10e, 0, 0, Local0, c00b)
	}
	if (LNotEqual(b900, Buffer() {0xc0,0xc1,0xc2,0xc3,0xc4})) {
		err(c080, z077, 0x10f, 0, 0, b900, Buffer() {0xc0,0xc1,0xc2,0xc3,0xc4})
	}

	// Buffer Field

	Store(ObjectType(bf90), Local0)
	if (LNotEqual(Local0, c016)) {
		err(c080, z077, 0x110, 0, 0, Local0, c016)
	}
	if (LNotEqual(bf90, 0xc0)) {
		err(c080, z077, 0x111, 0, 0, bf90, 0xc0)
	}

	// One level Package

	Store(Index(p900, 0), Local0)
	Store(ObjectType(Local0), Local1)
	if (LNotEqual(Local1, c008)) {
		err(c080, z077, 0x112, 0, 0, Local1, c008)
	}

	Store(Index(p901, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c009)) {
		err(c080, z077, 0x113, 0, 0, Local2, c009)
	}
	if (LNotEqual(Local1, 0xabcd2004)) {
		err(c080, z077, 0x114, 0, 0, Local1, 0xabcd2004)
	}

	Store(Index(p901, 1), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c009)) {
		err(c080, z077, 0x115, 0, 0, Local2, c009)
	}
	if (LNotEqual(Local1, 0x1122334455662005)) {
		err(c080, z077, 0x116, 0, 0, Local1, 0x1122334455662005)
	}

	Store(Index(p902, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00a)) {
		err(c080, z077, 0x117, 0, 0, Local2, c00a)
	}
	if (LNotEqual(Local1, "12342006")) {
		err(c080, z077, 0x118, 0, 0, Local1, "12342006")
	}

	Store(Index(p902, 1), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00a)) {
		err(c080, z077, 0x119, 0, 0, Local2, c00a)
	}
	if (LNotEqual(Local1, "q1w2e3r4t5y6u7i82007")) {
		err(c080, z077, 0x11a, 0, 0, Local1, "q1w2e3r4t5y6u7i82007")
	}

	Store(Index(p903, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00a)) {
		err(c080, z077, 0x11b, 0, 0, Local2, c00a)
	}
	if (LNotEqual(Local1, "qwrtyuiop2008")) {
		err(c080, z077, 0x11c, 0, 0, Local1, "qwrtyuiop2008")
	}

	Store(Index(p903, 1), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00a)) {
		err(c080, z077, 0x11d, 0, 0, Local2, c00a)
	}
	if (LNotEqual(Local1, "1234567890abdef0252009")) {
		err(c080, z077, 0x11e, 0, 0, Local1, "1234567890abdef0252009")
	}

	Store(Index(p904, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00b)) {
		err(c080, z077, 0x11f, 0, 0, Local2, c00b)
	}
	if (LNotEqual(Local1, Buffer() {0xc5,0xc6,0xc7})) {
		err(c080, z077, 0x120, 0, 0, Local1, Buffer() {0xc5,0xc6,0xc7})
	}

	Store(Index(p904, 1), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00b)) {
		err(c080, z077, 0x121, 0, 0, Local2, c00b)
	}
	if (LNotEqual(Local1, Buffer() {0xc8,0xc9})) {
		err(c080, z077, 0x122, 0, 0, Local1, Buffer() {0xc8,0xc9})
	}

	// Two level Package

	Store(Index(p905, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c009)) {
		err(c080, z077, 0x123, 0, 0, Local4, c009)
	}
	if (LNotEqual(Local3, 0xabc200a)) {
		err(c080, z077, 0x124, 0, 0, Local3, 0xabc200a)
	}

	Store(Index(p905, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 1), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c00a)) {
		err(c080, z077, 0x125, 0, 0, Local4, c00a)
	}
	if (LNotEqual(Local3, "0xabc200b")) {
		err(c080, z077, 0x126, 0, 0, Local3, "0xabc200b")
	}

	Store(Index(p905, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 2), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c00a)) {
		err(c080, z077, 0x127, 0, 0, Local4, c00a)
	}
	if (LNotEqual(Local3, "abc200c")) {
		err(c080, z077, 0x128, 0, 0, Local3, "abc200c")
	}

	Store(Index(p906, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c00a)) {
		err(c080, z077, 0x129, 0, 0, Local4, c00a)
	}
	if (LNotEqual(Local3, "abc200d")) {
		err(c080, z077, 0x12a, 0, 0, Local3, "abc200d")
	}

	Store(Index(p907, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c00a)) {
		err(c080, z077, 0x12b, 0, 0, Local4, c00a)
	}
	if (LNotEqual(Local3, "aqwevbgnm200e")) {
		err(c080, z077, 0x12c, 0, 0, Local3, "aqwevbgnm200e")
	}

	Store(Index(p908, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c00b)) {
		err(c080, z077, 0x12d, 0, 0, Local4, c00b)
	}
	if (LNotEqual(Local3, Buffer() {0xca,0xcb,0xcc,0xcd,0xce})) {
		err(c080, z077, 0x12e, 0, 0, Local3, Buffer() {0xca,0xcb,0xcc,0xcd,0xce})
	}

	// Three level Package

	Store(Index(p909, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(Index(Local3, 0), Local4)
	Store(DerefOf(Local4), Local5)
	Store(ObjectType(Local5), Local6)
	if (LNotEqual(Local6, c009)) {
		err(c080, z077, 0x12f, 0, 0, Local6, c009)
	}
	if (LNotEqual(Local5, 0xabc200f)) {
		err(c080, z077, 0x130, 0, 0, Local5, 0xabc200f)
	}

	Store(Index(p90a, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(Index(Local3, 0), Local4)
	Store(DerefOf(Local4), Local5)
	Store(ObjectType(Local5), Local6)
	if (LNotEqual(Local6, c00a)) {
		err(c080, z077, 0x131, 0, 0, Local6, c00a)
	}
	if (LNotEqual(Local5, "12342010")) {
		err(c080, z077, 0x132, 0, 0, Local5, "12342010")
	}

	Store(Index(p90b, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(Index(Local3, 0), Local4)
	Store(DerefOf(Local4), Local5)
	Store(ObjectType(Local5), Local6)
	if (LNotEqual(Local6, c00a)) {
		err(c080, z077, 0x133, 0, 0, Local6, c00a)
	}
	if (LNotEqual(Local5, "zxswefas2011")) {
		err(c080, z077, 0x134, 0, 0, Local5, "zxswefas2011")
	}

	Store(Index(p90c, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(Index(Local3, 0), Local4)
	Store(DerefOf(Local4), Local5)
	Store(ObjectType(Local5), Local6)
	if (LNotEqual(Local6, c00b)) {
		err(c080, z077, 0x135, 0, 0, Local6, c00b)
	}
	if (LNotEqual(Local5, Buffer() {0xcf,0xd0,0xd1})) {
		err(c080, z077, 0x136, 0, 0, Local5, Buffer() {0xcf,0xd0,0xd1})
	}

	Store(Index(p953, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c009)) {
		err(c080, z077, 0x137, 0, 0, Local2, c009)
	}
	if (LNotEqual(Local1, 0xabcd2018)) {
		err(c080, z077, 0x138, 0, 0, Local1, 0xabcd2018)
	}

	Store(Index(p953, 1), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c009)) {
		err(c080, z077, 0x139, 0, 0, Local2, c009)
	}
	if (LNotEqual(Local1, 0xabcd2019)) {
		err(c080, z077, 0x13a, 0, 0, Local1, 0xabcd2019)
	}

	// Not Computational Data

	m1aa(c080, e900, c00f, 0, 0x13b)
	m1aa(c080, mx90, c011, 0, 0x13c)
	m1aa(c080, d900, c00e, 0, 0x13d)
	if (y508) {
		m1aa(c080, tz90, c015, 0, 0x13e)
	}
	m1aa(c080, pr90, c014, 0, 0x13f)
	m1aa(c080, r900, c012, 0, 0x140)
	m1aa(c080, pw90, c013, 0, 0x141)

/*
 *	// Field Unit (Field)
 *
 *	if (LNotEqual(f900, 0xd7)) {
 *		err(c080, z077, 0x137, 0, 0, f900, 0xd7)
 *	}
 *
 *	// Field Unit (IndexField)
 *
 *	if (LNotEqual(if90, 0xd7)) {
 *		err(c080, z077, 0x138, 0, 0, if90, 0xd7)
 *	}
 */
	} /* m000 */

	// Check and restore the global data after writing into them
	Method(m001)
	{

	// Computational Data

	m1aa(c080, i900, c009, c08a, 0x144)
	CopyObject(i9Z0, i900)

	m1aa(c080, i901, c009, c08a, 0x145)
	CopyObject(i9Z1, i901)

	m1aa(c080, s900, c009, c08a, 0x146)
	CopyObject(s9Z0, s900)

	m1aa(c080, s901, c009, c08a, 0x147)
	CopyObject(s9Z1, s901)

	m1aa(c080, b900, c009, c08a, 0x148)
	CopyObject(b9Z0, b900)

	// Package

	m1aa(c080, p953, c009, c08a, 0x149)
	CopyObject(p954, p953)

	// Not Computational Data

	m1aa(c080, e900, c009, c08a, 0x14a)
	CopyObject(e9Z0, e900)

	m1aa(c080, mx90, c009, c08a, 0x14b)
	CopyObject(mx91, mx90)

	m1aa(c080, d900, c009, c08a, 0x14c)
	CopyObject(d9Z0, d900)

	if (y508) {
		m1aa(c080, tz90, c009, c08a, 0x14d)
		CopyObject(tz91, tz90)
	}

	m1aa(c080, pr90, c009, c08a, 0x14e)
	CopyObject(pr91, pr90)

	if (y510) {
		m1aa(c080, r900, c009, c08a, 0x14f)
		CopyObject(r9Z0, r900)
	}

	m1aa(c080, pw90, c009, c08a, 0x150)
	CopyObject(pw91, pw90)

	m000()
	} /* m001 */


	// T2:R1-R14

	// Computational Data

	Store(RefOf(i900), Local0)
	m1a2(Local0, c009, 0, 0, c009, 0xfe7cb391d65a2000, 271)

	Store(RefOf(i901), Local0)
	m1a2(Local0, c009, 0, 0, c009, 0xc1792001, 272)

	Store(RefOf(s900), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "12342002", 273)

	Store(RefOf(s901), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "qwrtyu2003", 274)

	Store(RefOf(b900), Local0)
	m1a2(Local0, c00b, 0, 0, c00b, Buffer() {0xc0,0xc1,0xc2,0xc3,0xc4}, 275)

	// Not Computational Data

	Store(RefOf(e900), Local0)
	m1a0(Local0, c00f, Ones, 280)

	Store(RefOf(mx90), Local0)
	m1a0(Local0, c011, Ones, 281)

	Store(RefOf(d900), Local0)
	m1a0(Local0, c00e, Ones, 282)

	if (arg0) {
		if (y508) {
			Store(RefOf(tz90), Local0)
			m1a0(Local0, c015, Ones, 283)
		}
	} else {
		Store(RefOf(tz90), Local0)
		m1a0(Local0, c015, Ones, 283)
	}

	Store(RefOf(pr90), Local0)
	m1a0(Local0, c014, Ones, 284)

	if (arg0) {
		if (y510) {
			Store(RefOf(r900), Local0)
			m1a0(Local0, c012, Ones, 285)
		}
	} else {
		Store(RefOf(r900), Local0)
		m1a0(Local0, c012, Ones, 1002)
	}

	Store(RefOf(pw90), Local0)
	m1a0(Local0, c013, Ones, 286)

	// Package

	Store(RefOf(p953), Local0)
	m1a2(Local0, c00c, 1, 0, c009, 0xabcd2018, 1001)

	if (arg0) {
		m001()
		return
	}

	// Computational Data (Field Unit and Buffer Field)

	Store(RefOf(f900), Local0)
	m1a2(Local0, c00d, 0, 0, c009, 0, 276)

	Store(RefOf(bn90), Local0)
	m1a2(Local0, c00d, 0, 0, c009, 0, 277)

	Store(RefOf(if90), Local0)
	m1a2(Local0, c00d, 0, 0, c009, 0, 278)

	Store(RefOf(bf90), Local0)
	m1a2(Local0, c016, 0, 0, c009, 0xc0, 279)

	// Elements of Package are Uninitialized

	Store(RefOf(p900), Local0)
	m1a0(Local0, c00c, Ones, 287)

	// Elements of Package are Computational Data

	Store(RefOf(p901), Local0)
	m1a2(Local0, c00c, 1, 0, c009, 0xabcd2004, 288)
	m1a2(Local0, c00c, 1, 1, c009, 0x1122334455662005, 289)

	Store(RefOf(p902), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "12342006", 290)
	m1a2(Local0, c00c, 1, 1, c00a, "q1w2e3r4t5y6u7i82007", 291)

	Store(RefOf(p903), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "qwrtyuiop2008", 292)
	m1a2(Local0, c00c, 1, 1, c00a, "1234567890abdef0252009", 293)

	Store(RefOf(p904), Local0)
	m1a2(Local0, c00c, 1, 0, c00b, Buffer() {0xc5,0xc6,0xc7}, 294)

	Store(RefOf(p905), Local0)
	m1a2(Local0, c00c, 2, 0, c009, 0xabc200a, 295)
	m1a2(Local0, c00c, 2, 1, c00a, "0xabc200b", 296)

	Store(RefOf(p906), Local0)
	m1a2(Local0, c00c, 2, 0, c00a, "abc200d", 297)

	Store(RefOf(p907), Local0)
	m1a2(Local0, c00c, 2, 0, c00a, "aqwevbgnm200e", 298)

	Store(RefOf(p908), Local0)
	m1a2(Local0, c00c, 2, 0, c00b, Buffer() {0xca,0xcb,0xcc,0xcd,0xce}, 299)

	Store(RefOf(p909), Local0)
	m1a2(Local0, c00c, 3, 0, c009, 0xabc200f, 300)

	Store(RefOf(p90a), Local0)
	m1a2(Local0, c00c, 3, 0, c00a, "12342010", 301)

	Store(RefOf(p90b), Local0)
	m1a2(Local0, c00c, 3, 0, c00a, "zxswefas2011", 302)

	Store(RefOf(p90c), Local0)
	m1a2(Local0, c00c, 3, 0, c00b, Buffer() {0xcf,0xd0,0xd1}, 303)

	// In-package name strings are String typed, not ObjectReference
	// typed.

	// Elements of Package are NameString

	Store(RefOf(p90d), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "I900", 304)

	Store(RefOf(p90e), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "I901", 305)

	Store(RefOf(p90f), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "S900", 306)

	Store(RefOf(p910), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "S901", 307)

	Store(RefOf(p911), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "B9Z0", 308)

	Store(RefOf(p912), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "F900", 309)

	Store(RefOf(p913), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "BN90", 310)

	Store(RefOf(p914), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "IF90", 311)

	Store(RefOf(p915), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "BF90", 312)

	Store(RefOf(p916), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "D900", 313)

	Store(RefOf(p917), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "E900", 314)

	Store(RefOf(p918), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "MX90", 315)

	Store(RefOf(p919), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "R9Z0", 316)

	Store(RefOf(p91a), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "PW90", 317)

	Store(RefOf(p91b), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "PR90", 318)

	Store(RefOf(p91c), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "TZ90", 319)

	Store(RefOf(p91d), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "M900", 320)

	// Methods

	Store(RefOf(m900), Local0)
	m1a0(Local0, c010, Ones, 374)

	m000()
	m1a6()

	return
}

Method(m16b,, Serialized)
{
	if (y100) {
		ts00("m16b")
	} else {
		Store("m16b", Debug)
	}

	// Not Computational Data

	Event(e900)
	Mutex(mx90, 0)
	Device(d900) {}
	ThermalZone(tz90) {}
	Processor(pr90, 0, 0xFFFFFFFF, 0) {}
	OperationRegion(r900, SystemMemory, 0x100, 0x100)
	OperationRegion(r9Z0, SystemMemory, 0x100, 0x100)
	PowerResource(pw90, 1, 0) {Method(mmmm){return (0)}}

	// Computational Data

	Name(i900, 0xfe7cb391d65a3000)
	Name(i901, 0x21793001)
	Name(i902, 0)
	Name(i903, 0xffffffffffffffff)
	Name(i904, 0xffffffff)
	Name(s900, "12343002")
	Name(s901, "qwrtyu3003")
	Name(b900, Buffer() {0xd0,0xd1,0xd2,0xd3,0xd4})
	Name(b9Z0, Buffer() {0xd0,0xd1,0xd2,0xd3,0xd4})

	CreateField(b900, 0, 8, bf90)
	Field(r900, ByteAcc, NoLock, Preserve) {f900,8,f901,8,f902,8,f903,8}
	BankField(r900, f901, 0, ByteAcc, NoLock, Preserve) {bn90,4}
	IndexField(f902, f903, ByteAcc, NoLock, Preserve) {if90,8,if91,8}

	// Elements of Package are Uninitialized

	Name(p900, Package(1) {})

	// Elements of Package are Computational Data

	Name(p901, Package() {0xabcd3004, 0x1122334455663005})
	Name(p902, Package() {"12343006", "q1w2e3r4t5y6u7i83007"})
	Name(p903, Package() {"qwrtyuiop3008", "1234567890abdef0253009"})
	Name(p904, Package() {Buffer() {0xd5,0xd6,0xd7}, Buffer() {0xd8,0xd9}})
	Name(p905, Package() {Package() {0xabc300a, "0xabc300b", "abc300c"}})
	Name(p906, Package() {Package() {"abc300d"}})
	Name(p907, Package() {Package() {"aqwevbgnm300e"}})
	Name(p908, Package() {Package() {Buffer() {0xda,0xdb,0xdc,0xdd,0xde}}})
	Name(p909, Package() {Package() {Package() {0xabc300f}}})
	Name(p90a, Package() {Package() {Package() {"12343010"}}})
	Name(p90b, Package() {Package() {Package() {"zxswefas3011"}}})
	Name(p90c, Package() {Package() {Package() {Buffer() {0xdf,0x20,0x21}}}})

	Name(p90d, Package() {i900})
	Name(p90e, Package() {i901})
	Name(p90f, Package() {s900})
	Name(p910, Package() {s901})
	Name(p911, Package() {b9Z0})
	Name(p912, Package() {f900})
	Name(p913, Package() {bn90})
	Name(p914, Package() {if90})
	Name(p915, Package() {bf90})

	// Elements of Package are NOT Computational Data

	Name(p916, Package() {d900})
	Name(p917, Package() {e900})
	Name(p918, Package() {mx90})
	Name(p919, Package() {r900})
	Name(p91a, Package() {pw90})
	Name(p91b, Package() {pr90})
	Name(p91c, Package() {tz90})

	// Methods

	Method(m900) {}
	Method(m901) { return (0xabc3012) }
	Method(m902) { return ("zxvgswquiy3013") }
	Method(m903) { return (Buffer() {0x22}) }
	Method(m904) { return (Package() {0xabc3014}) }
	Method(m905) { return (Package() {"lkjhgtre3015"}) }
	Method(m906) { return (Package() {Buffer() {0x23}}) }
	Method(m907) { return (Package() {Package() {0xabc3016}}) }

	Method(m908) { return (i900) }
	Method(m909) { return (i901) }
	Method(m90a) { return (s900) }
	Method(m90b) { return (s901) }
	Method(m90c) { return (b9Z0) }
	Method(m90d) { return (f900) }
	Method(m90e) { return (bn90) }
	Method(m90f) { return (if90) }
	Method(m910) { return (bf90) }

	Method(m911) { return (d900) }
	Method(m912) { return (e900) }
	Method(m913) { return (m901) }
	Method(m914) { return (mx90) }
	Method(m915) { return (r900) }
	Method(m916) { return (pw90) }
	Method(m917) { return (pr90) }
	Method(m918) { return (tz90) }

	Method(m919) { return (p900) }
	Method(m91a) { return (p901) }
	Method(m91b) { return (p902) }
	Method(m91c) { return (p903) }
	Method(m91d) { return (p904) }
	Method(m91e) { return (p905) }
	Method(m91f) { return (p906) }
	Method(m920) { return (p907) }
	Method(m921) { return (p908) }
	Method(m922) { return (p909) }
	Method(m923) { return (p90a) }
	Method(m924) { return (p90b) }
	Method(m925) { return (p90c) }
	Method(m926) { return (p90d) }
	Method(m927) { return (p90e) }
	Method(m928) { return (p90f) }
	Method(m929) { return (p910) }
	Method(m92a) { return (p911) }
	Method(m92b) { return (p912) }
	Method(m92c) { return (p913) }
	Method(m92d) { return (p914) }
	Method(m92e) { return (p915) }
	Method(m92f) { return (p916) }
	Method(m930) { return (p917) }
	Method(m931) { return (p918) }
	Method(m932) { return (p919) }
	Method(m933) { return (p91a) }
	Method(m934) { return (p91b) }
	Method(m935) { return (p91c) }

	// Elements of Package are Methods

	Name(p91d, Package() {m900})
	Name(p91e, Package() {m901})
	Name(p91f, Package() {m902})
	Name(p920, Package() {m903})
	Name(p921, Package() {m904})
	Name(p922, Package() {m905})
	Name(p923, Package() {m906})
	Name(p924, Package() {m907})
	Name(p925, Package() {m908})
	Name(p926, Package() {m909})
	Name(p927, Package() {m90a})
	Name(p928, Package() {m90b})
	Name(p929, Package() {m90c})
	Name(p92a, Package() {m90d})
	Name(p92b, Package() {m90e})
	Name(p92c, Package() {m90f})
	Name(p92d, Package() {m910})
	Name(p92e, Package() {m911})
	Name(p92f, Package() {m912})
	Name(p930, Package() {m913})
	Name(p931, Package() {m914})
	Name(p932, Package() {m915})
	Name(p933, Package() {m916})
	Name(p934, Package() {m917})
	if (y103) {
		Name(p935, Package() {m918})
	}
	Name(p936, Package() {m919})
	Name(p937, Package() {m91a})
	Name(p938, Package() {m91b})
	Name(p939, Package() {m91c})
	Name(p93a, Package() {m91d})
	Name(p93b, Package() {m91e})
	Name(p93c, Package() {m91f})
	Name(p93d, Package() {m920})
	Name(p93e, Package() {m921})
	Name(p93f, Package() {m922})
	Name(p940, Package() {m923})
	Name(p941, Package() {m924})
	Name(p942, Package() {m925})
	Name(p943, Package() {m926})
	Name(p944, Package() {m927})
	Name(p945, Package() {m928})
	Name(p946, Package() {m929})
	Name(p947, Package() {m92a})
	Name(p948, Package() {m92b})
	Name(p949, Package() {m92c})
	Name(p94a, Package() {m92d})
	Name(p94b, Package() {m92e})
	Name(p94c, Package() {m92f})
	Name(p94d, Package() {m930})
	Name(p94e, Package() {m931})
	Name(p94f, Package() {m932})
	Name(p950, Package() {m933})
	Name(p951, Package() {m934})
	Name(p952, Package() {m935})

	Name(p953, Package() {0xabcd3018, 0xabcd3019})
	Name(p954, Package() {0xabcd3018, 0xabcd3019})

	// Check that all the data (local) are not corrupted
	Method(m000)
	{
	// Computational Data

	// Integer

	Store(ObjectType(i900), Local0)
	if (LNotEqual(Local0, c009)) {
		err(c080, z077, 0x100, 0, 0, Local0, c009)
	}
	if (LNotEqual(i900, 0xfe7cb391d65a3000)) {
		err(c080, z077, 0x101, 0, 0, i900, 0xfe7cb391d65a3000)
	}

	Store(ObjectType(i901), Local0)
	if (LNotEqual(Local0, c009)) {
		err(c080, z077, 0x102, 0, 0, Local0, c009)
	}
	if (LNotEqual(i901, 0x21793001)) {
		err(c080, z077, 0x103, 0, 0, i901, 0x21793001)
	}

	Store(ObjectType(i902), Local0)
	if (LNotEqual(Local0, c009)) {
		err(c080, z077, 0x104, 0, 0, Local0, c009)
	}
	if (LNotEqual(i902, 0)) {
		err(c080, z077, 0x105, 0, 0, i902, 0)
	}

	Store(ObjectType(i903), Local0)
	if (LNotEqual(Local0, c009)) {
		err(c080, z077, 0x106, 0, 0, Local0, c009)
	}
	if (LNotEqual(i903, 0xffffffffffffffff)) {
		err(c080, z077, 0x107, 0, 0, i903, 0xffffffffffffffff)
	}

	Store(ObjectType(i904), Local0)
	if (LNotEqual(Local0, c009)) {
		err(c080, z077, 0x108, 0, 0, Local0, c009)
	}
	if (LNotEqual(i904, 0xffffffff)) {
		err(c080, z077, 0x109, 0, 0, i904, 0xffffffff)
	}

	// String

	Store(ObjectType(s900), Local0)
	if (LNotEqual(Local0, c00a)) {
		err(c080, z077, 0x10a, 0, 0, Local0, c00a)
	}
	if (LNotEqual(s900, "12343002")) {
		err(c080, z077, 0x10b, 0, 0, s900, "12343002")
	}

	Store(ObjectType(s901), Local0)
	if (LNotEqual(Local0, c00a)) {
		err(c080, z077, 0x10c, 0, 0, Local0, c00a)
	}
	if (LNotEqual(s901, "qwrtyu3003")) {
		err(c080, z077, 0x10d, 0, 0, s901, "qwrtyu3003")
	}

	// Buffer

	Store(ObjectType(b900), Local0)
	if (LNotEqual(Local0, c00b)) {
		err(c080, z077, 0x10e, 0, 0, Local0, c00b)
	}
	if (LNotEqual(b900, Buffer() {0xd0,0xd1,0xd2,0xd3,0xd4})) {
		err(c080, z077, 0x10f, 0, 0, b900, Buffer() {0xd0,0xd1,0xd2,0xd3,0xd4})
	}

	// Buffer Field

	Store(ObjectType(bf90), Local0)
	if (LNotEqual(Local0, c016)) {
		err(c080, z077, 0x110, 0, 0, Local0, c016)
	}
	if (LNotEqual(bf90, 0xd0)) {
		err(c080, z077, 0x111, 0, 0, bf90, 0xd0)
	}

	// One level Package

	Store(Index(p900, 0), Local0)
	Store(ObjectType(Local0), Local1)
	if (LNotEqual(Local1, c008)) {
		err(c080, z077, 0x112, 0, 0, Local1, c008)
	}

	Store(Index(p901, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c009)) {
		err(c080, z077, 0x113, 0, 0, Local2, c009)
	}
	if (LNotEqual(Local1, 0xabcd3004)) {
		err(c080, z077, 0x114, 0, 0, Local1, 0xabcd3004)
	}

	Store(Index(p901, 1), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c009)) {
		err(c080, z077, 0x115, 0, 0, Local2, c009)
	}
	if (LNotEqual(Local1, 0x1122334455663005)) {
		err(c080, z077, 0x116, 0, 0, Local1, 0x1122334455663005)
	}

	Store(Index(p902, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00a)) {
		err(c080, z077, 0x117, 0, 0, Local2, c00a)
	}
	if (LNotEqual(Local1, "12343006")) {
		err(c080, z077, 0x118, 0, 0, Local1, "12343006")
	}

	Store(Index(p902, 1), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00a)) {
		err(c080, z077, 0x119, 0, 0, Local2, c00a)
	}
	if (LNotEqual(Local1, "q1w2e3r4t5y6u7i83007")) {
		err(c080, z077, 0x11a, 0, 0, Local1, "q1w2e3r4t5y6u7i83007")
	}

	Store(Index(p903, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00a)) {
		err(c080, z077, 0x11b, 0, 0, Local2, c00a)
	}
	if (LNotEqual(Local1, "qwrtyuiop3008")) {
		err(c080, z077, 0x11c, 0, 0, Local1, "qwrtyuiop3008")
	}

	Store(Index(p903, 1), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00a)) {
		err(c080, z077, 0x11d, 0, 0, Local2, c00a)
	}
	if (LNotEqual(Local1, "1234567890abdef0253009")) {
		err(c080, z077, 0x11e, 0, 0, Local1, "1234567890abdef0253009")
	}

	Store(Index(p904, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00b)) {
		err(c080, z077, 0x11f, 0, 0, Local2, c00b)
	}
	if (LNotEqual(Local1, Buffer() {0xd5,0xd6,0xd7})) {
		err(c080, z077, 0x120, 0, 0, Local1, Buffer() {0xd5,0xd6,0xd7})
	}

	Store(Index(p904, 1), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00b)) {
		err(c080, z077, 0x121, 0, 0, Local2, c00b)
	}
	if (LNotEqual(Local1, Buffer() {0xd8,0xd9})) {
		err(c080, z077, 0x122, 0, 0, Local1, Buffer() {0xd8,0xd9})
	}

	// Two level Package

	Store(Index(p905, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c009)) {
		err(c080, z077, 0x123, 0, 0, Local4, c009)
	}
	if (LNotEqual(Local3, 0xabc300a)) {
		err(c080, z077, 0x124, 0, 0, Local3, 0xabc300a)
	}

	Store(Index(p905, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 1), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c00a)) {
		err(c080, z077, 0x125, 0, 0, Local4, c00a)
	}
	if (LNotEqual(Local3, "0xabc300b")) {
		err(c080, z077, 0x126, 0, 0, Local3, "0xabc300b")
	}

	Store(Index(p905, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 2), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c00a)) {
		err(c080, z077, 0x127, 0, 0, Local4, c00a)
	}
	if (LNotEqual(Local3, "abc300c")) {
		err(c080, z077, 0x128, 0, 0, Local3, "abc300c")
	}

	Store(Index(p906, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c00a)) {
		err(c080, z077, 0x129, 0, 0, Local4, c00a)
	}
	if (LNotEqual(Local3, "abc300d")) {
		err(c080, z077, 0x12a, 0, 0, Local3, "abc300d")
	}

	Store(Index(p907, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c00a)) {
		err(c080, z077, 0x12b, 0, 0, Local4, c00a)
	}
	if (LNotEqual(Local3, "aqwevbgnm300e")) {
		err(c080, z077, 0x12c, 0, 0, Local3, "aqwevbgnm300e")
	}

	Store(Index(p908, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c00b)) {
		err(c080, z077, 0x12d, 0, 0, Local4, c00b)
	}
	if (LNotEqual(Local3, Buffer() {0xda,0xdb,0xdc,0xdd,0xde})) {
		err(c080, z077, 0x12e, 0, 0, Local3, Buffer() {0xda,0xdb,0xdc,0xdd,0xde})
	}

	// Three level Package

	Store(Index(p909, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(Index(Local3, 0), Local4)
	Store(DerefOf(Local4), Local5)
	Store(ObjectType(Local5), Local6)
	if (LNotEqual(Local6, c009)) {
		err(c080, z077, 0x12f, 0, 0, Local6, c009)
	}
	if (LNotEqual(Local5, 0xabc300f)) {
		err(c080, z077, 0x130, 0, 0, Local5, 0xabc300f)
	}

	Store(Index(p90a, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(Index(Local3, 0), Local4)
	Store(DerefOf(Local4), Local5)
	Store(ObjectType(Local5), Local6)
	if (LNotEqual(Local6, c00a)) {
		err(c080, z077, 0x131, 0, 0, Local6, c00a)
	}
	if (LNotEqual(Local5, "12343010")) {
		err(c080, z077, 0x132, 0, 0, Local5, "12343010")
	}

	Store(Index(p90b, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(Index(Local3, 0), Local4)
	Store(DerefOf(Local4), Local5)
	Store(ObjectType(Local5), Local6)
	if (LNotEqual(Local6, c00a)) {
		err(c080, z077, 0x133, 0, 0, Local6, c00a)
	}
	if (LNotEqual(Local5, "zxswefas3011")) {
		err(c080, z077, 0x134, 0, 0, Local5, "zxswefas3011")
	}

	Store(Index(p90c, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(Index(Local3, 0), Local4)
	Store(DerefOf(Local4), Local5)
	Store(ObjectType(Local5), Local6)
	if (LNotEqual(Local6, c00b)) {
		err(c080, z077, 0x135, 0, 0, Local6, c00b)
	}
	if (LNotEqual(Local5, Buffer() {0xdf,0x20,0x21})) {
		err(c080, z077, 0x136, 0, 0, Local5, Buffer() {0xdf,0x20,0x21})
	}

	Store(Index(p953, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c009)) {
		err(c080, z077, 0x137, 0, 0, Local2, c009)
	}
	if (LNotEqual(Local1, 0xabcd3018)) {
		err(c080, z077, 0x138, 0, 0, Local1, 0xabcd3018)
	}

	Store(Index(p953, 1), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c009)) {
		err(c080, z077, 0x139, 0, 0, Local2, c009)
	}
	if (LNotEqual(Local1, 0xabcd3019)) {
		err(c080, z077, 0x13a, 0, 0, Local1, 0xabcd3019)
	}

	// Not Computational Data

	m1aa(c080, e900, c00f, 0, 0x13b)
	m1aa(c080, mx90, c011, 0, 0x13c)
	m1aa(c080, d900, c00e, 0, 0x13d)
	if (y508) {
		m1aa(c080, tz90, c015, 0, 0x13e)
	}
	m1aa(c080, pr90, c014, 0, 0x13f)
	m1aa(c080, r900, c012, 0, 0x140)
	m1aa(c080, pw90, c013, 0, 0x141)

/*
 *	// Field Unit (Field)
 *
 *	if (LNotEqual(f900, 0xd7)) {
 *		err(c080, z077, 0x137, 0, 0, f900, 0xd7)
 *	}
 *
 *	// Field Unit (IndexField)
 *
 *	if (LNotEqual(if90, 0xd7)) {
 *		err(c080, z077, 0x138, 0, 0, if90, 0xd7)
 *	}
 */
	} /* m000 */


	// T2:C1-C14

	// Computational Data

	Store(CondRefOf(i900), Local0)
	m1a4(Local0, 428)

	Store(CondRefOf(i901), Local0)
	m1a4(Local0, 429)

	Store(CondRefOf(s900), Local0)
	m1a4(Local0, 430)

	Store(CondRefOf(s901), Local0)
	m1a4(Local0, 431)

	Store(CondRefOf(b900), Local0)
	m1a4(Local0, 432)

	Store(CondRefOf(f900), Local0)
	m1a4(Local0, 433)

	Store(CondRefOf(bn90), Local0)
	m1a4(Local0, 434)

	Store(CondRefOf(if90), Local0)
	m1a4(Local0, 435)

	Store(CondRefOf(bf90), Local0)
	m1a4(Local0, 436)

	// Not Computational Data

	Store(CondRefOf(e900), Local0)
	m1a4(Local0, 437)

	Store(CondRefOf(mx90), Local0)
	m1a4(Local0, 438)

	Store(CondRefOf(d900), Local0)
	m1a4(Local0, 439)

	Store(CondRefOf(tz90), Local0)
	m1a4(Local0, 450)

	Store(CondRefOf(pr90), Local0)
	m1a4(Local0, 451)

	Store(CondRefOf(r900), Local0)
	m1a4(Local0, 452)

	Store(CondRefOf(pw90), Local0)
	m1a4(Local0, 453)

	// Elements of Package are Uninitialized

	Store(CondRefOf(p900), Local0)
	m1a4(Local0, 454)

	// Elements of Package are Computational Data

	Store(CondRefOf(p901), Local0)
	m1a4(Local0, 455)

	Store(CondRefOf(p902), Local0)
	m1a4(Local0, 456)

	Store(CondRefOf(p903), Local0)
	m1a4(Local0, 457)

	Store(CondRefOf(p904), Local0)
	m1a4(Local0, 458)

	Store(CondRefOf(p905), Local0)
	m1a4(Local0, 459)

	Store(CondRefOf(p906), Local0)
	m1a4(Local0, 460)

	Store(CondRefOf(p907), Local0)
	m1a4(Local0, 461)

	Store(CondRefOf(p908), Local0)
	m1a4(Local0, 462)

	Store(CondRefOf(p909), Local0)
	m1a4(Local0, 463)

	Store(CondRefOf(p90a), Local0)
	m1a4(Local0, 464)

	Store(CondRefOf(p90b), Local0)
	m1a4(Local0, 465)

	Store(CondRefOf(p90c), Local0)
	m1a4(Local0, 466)

	Store(CondRefOf(p90d), Local0)
	m1a4(Local0, 467)

	Store(CondRefOf(p90e), Local0)
	m1a4(Local0, 468)

	Store(CondRefOf(p90f), Local0)
	m1a4(Local0, 469)

	Store(CondRefOf(p910), Local0)
	m1a4(Local0, 470)

	Store(CondRefOf(p911), Local0)
	m1a4(Local0, 471)

	Store(CondRefOf(p912), Local0)
	m1a4(Local0, 472)

	Store(CondRefOf(p913), Local0)
	m1a4(Local0, 473)

	Store(CondRefOf(p914), Local0)
	m1a4(Local0, 474)

	Store(CondRefOf(p915), Local0)
	m1a4(Local0, 475)

	// Elements of Package are NOT Computational Data

	Store(CondRefOf(p916), Local0)
	m1a4(Local0, 476)

	Store(CondRefOf(p917), Local0)
	m1a4(Local0, 477)

	Store(CondRefOf(p918), Local0)
	m1a4(Local0, 478)

	Store(CondRefOf(p919), Local0)
	m1a4(Local0, 479)

	Store(CondRefOf(p91a), Local0)
	m1a4(Local0, 480)

	Store(CondRefOf(p91b), Local0)
	m1a4(Local0, 481)

	Store(CondRefOf(p91c), Local0)
	m1a4(Local0, 482)

	// Elements of Package are Methods

	Store(CondRefOf(p91d), Local0)
	m1a4(Local0, 483)

	Store(CondRefOf(p91e), Local0)
	m1a4(Local0, 484)

	Store(CondRefOf(p91f), Local0)
	m1a4(Local0, 485)

	Store(CondRefOf(p920), Local0)
	m1a4(Local0, 486)

	Store(CondRefOf(p921), Local0)
	m1a4(Local0, 487)

	Store(CondRefOf(p922), Local0)
	m1a4(Local0, 488)

	Store(CondRefOf(p923), Local0)
	m1a4(Local0, 489)

	Store(CondRefOf(p924), Local0)
	m1a4(Local0, 490)

	Store(CondRefOf(p925), Local0)
	m1a4(Local0, 491)

	Store(CondRefOf(p926), Local0)
	m1a4(Local0, 492)

	Store(CondRefOf(p927), Local0)
	m1a4(Local0, 493)

	Store(CondRefOf(p928), Local0)
	m1a4(Local0, 494)

	Store(CondRefOf(p929), Local0)
	m1a4(Local0, 495)

	Store(CondRefOf(p92a), Local0)
	m1a4(Local0, 496)

	Store(CondRefOf(p92b), Local0)
	m1a4(Local0, 497)

	Store(CondRefOf(p92c), Local0)
	m1a4(Local0, 498)

	Store(CondRefOf(p92d), Local0)
	m1a4(Local0, 499)

	Store(CondRefOf(p92e), Local0)
	m1a4(Local0, 500)

	Store(CondRefOf(p92f), Local0)
	m1a4(Local0, 501)

	Store(CondRefOf(p930), Local0)
	m1a4(Local0, 502)

	Store(CondRefOf(p931), Local0)
	m1a4(Local0, 503)

	Store(CondRefOf(p932), Local0)
	m1a4(Local0, 504)

	Store(CondRefOf(p933), Local0)
	m1a4(Local0, 505)

	Store(CondRefOf(p934), Local0)
	m1a4(Local0, 506)

	Store(CondRefOf(p935), Local0)
	m1a4(Local0, 507)

	Store(CondRefOf(p936), Local0)
	m1a4(Local0, 508)

	Store(CondRefOf(p937), Local0)
	m1a4(Local0, 509)

	Store(CondRefOf(p938), Local0)
	m1a4(Local0, 510)

	Store(CondRefOf(p939), Local0)
	m1a4(Local0, 511)

	Store(CondRefOf(p93a), Local0)
	m1a4(Local0, 512)

	Store(CondRefOf(p93b), Local0)
	m1a4(Local0, 513)

	Store(CondRefOf(p93c), Local0)
	m1a4(Local0, 514)

	Store(CondRefOf(p93d), Local0)
	m1a4(Local0, 515)

	Store(CondRefOf(p93e), Local0)
	m1a4(Local0, 516)

	Store(CondRefOf(p93f), Local0)
	m1a4(Local0, 517)

	Store(CondRefOf(p940), Local0)
	m1a4(Local0, 518)

	Store(CondRefOf(p941), Local0)
	m1a4(Local0, 519)

	Store(CondRefOf(p942), Local0)
	m1a4(Local0, 520)

	Store(CondRefOf(p943), Local0)
	m1a4(Local0, 521)

	Store(CondRefOf(p944), Local0)
	m1a4(Local0, 522)

	Store(CondRefOf(p945), Local0)
	m1a4(Local0, 523)

	Store(CondRefOf(p946), Local0)
	m1a4(Local0, 524)

	Store(CondRefOf(p947), Local0)
	m1a4(Local0, 525)

	Store(CondRefOf(p948), Local0)
	m1a4(Local0, 526)

	Store(CondRefOf(p949), Local0)
	m1a4(Local0, 527)

	Store(CondRefOf(p94a), Local0)
	m1a4(Local0, 528)

	Store(CondRefOf(p94b), Local0)
	m1a4(Local0, 529)

	Store(CondRefOf(p94c), Local0)
	m1a4(Local0, 530)

	Store(CondRefOf(p94d), Local0)
	m1a4(Local0, 531)

	Store(CondRefOf(p94e), Local0)
	m1a4(Local0, 532)

	Store(CondRefOf(p94f), Local0)
	m1a4(Local0, 533)

	Store(CondRefOf(p950), Local0)
	m1a4(Local0, 534)

	Store(CondRefOf(p951), Local0)
	m1a4(Local0, 535)

	Store(CondRefOf(p952), Local0)
	m1a4(Local0, 536)

	// Methods

	Store(CondRefOf(m900), Local0)
	m1a4(Local0, 537)

	Store(CondRefOf(m901), Local0)
	m1a4(Local0, 538)

	Store(CondRefOf(m902), Local0)
	m1a4(Local0, 539)

	Store(CondRefOf(m903), Local0)
	m1a4(Local0, 540)

	Store(CondRefOf(m904), Local0)
	m1a4(Local0, 541)

	Store(CondRefOf(m905), Local0)
	m1a4(Local0, 542)

	Store(CondRefOf(m906), Local0)
	m1a4(Local0, 543)

	Store(CondRefOf(m907), Local0)
	m1a4(Local0, 544)

	Store(CondRefOf(m908), Local0)
	m1a4(Local0, 545)

	Store(CondRefOf(m909), Local0)
	m1a4(Local0, 546)

	Store(CondRefOf(m90a), Local0)
	m1a4(Local0, 547)

	Store(CondRefOf(m90b), Local0)
	m1a4(Local0, 548)

	Store(CondRefOf(m90c), Local0)
	m1a4(Local0, 549)

	Store(CondRefOf(m90d), Local0)
	m1a4(Local0, 550)

	Store(CondRefOf(m90e), Local0)
	m1a4(Local0, 551)

	Store(CondRefOf(m90f), Local0)
	m1a4(Local0, 552)

	Store(CondRefOf(m910), Local0)
	m1a4(Local0, 553)

	Store(CondRefOf(m911), Local0)
	m1a4(Local0, 554)

	Store(CondRefOf(m912), Local0)
	m1a4(Local0, 555)

	Store(CondRefOf(m913), Local0)
	m1a4(Local0, 556)

	Store(CondRefOf(m914), Local0)
	m1a4(Local0, 557)

	Store(CondRefOf(m915), Local0)
	m1a4(Local0, 558)

	Store(CondRefOf(m916), Local0)
	m1a4(Local0, 559)

	Store(CondRefOf(m917), Local0)
	m1a4(Local0, 560)

	Store(CondRefOf(m918), Local0)
	m1a4(Local0, 561)

	Store(CondRefOf(m919), Local0)
	m1a4(Local0, 562)

	Store(CondRefOf(m91a), Local0)
	m1a4(Local0, 563)

	Store(CondRefOf(m91b), Local0)
	m1a4(Local0, 564)

	Store(CondRefOf(m91c), Local0)
	m1a4(Local0, 565)

	Store(CondRefOf(m91d), Local0)
	m1a4(Local0, 566)

	Store(CondRefOf(m91e), Local0)
	m1a4(Local0, 567)

	Store(CondRefOf(m91f), Local0)
	m1a4(Local0, 568)

	Store(CondRefOf(m920), Local0)
	m1a4(Local0, 569)

	Store(CondRefOf(m921), Local0)
	m1a4(Local0, 570)

	Store(CondRefOf(m922), Local0)
	m1a4(Local0, 571)

	Store(CondRefOf(m923), Local0)
	m1a4(Local0, 572)

	Store(CondRefOf(m924), Local0)
	m1a4(Local0, 573)

	Store(CondRefOf(m925), Local0)
	m1a4(Local0, 574)

	Store(CondRefOf(m926), Local0)
	m1a4(Local0, 575)

	Store(CondRefOf(m927), Local0)
	m1a4(Local0, 576)

	Store(CondRefOf(m928), Local0)
	m1a4(Local0, 577)

	Store(CondRefOf(m929), Local0)
	m1a4(Local0, 578)

	Store(CondRefOf(m92a), Local0)
	m1a4(Local0, 579)

	Store(CondRefOf(m92b), Local0)
	m1a4(Local0, 580)

	Store(CondRefOf(m92c), Local0)
	m1a4(Local0, 581)

	Store(CondRefOf(m92d), Local0)
	m1a4(Local0, 582)

	Store(CondRefOf(m92e), Local0)
	m1a4(Local0, 583)

	Store(CondRefOf(m92f), Local0)
	m1a4(Local0, 584)

	Store(CondRefOf(m930), Local0)
	m1a4(Local0, 585)

	Store(CondRefOf(m931), Local0)
	m1a4(Local0, 586)

	Store(CondRefOf(m932), Local0)
	m1a4(Local0, 587)

	Store(CondRefOf(m933), Local0)
	m1a4(Local0, 588)

	Store(CondRefOf(m934), Local0)
	m1a4(Local0, 589)

	Store(CondRefOf(m935), Local0)
	m1a4(Local0, 590)

	m000()
	m1a6()
}

// arg0 - writing mode
Method(m16c, 1, Serialized)
{
	if (y100) {
		ts00("m16c")
	} else {
		Store("m16c", Debug)
	}

	// Not Computational Data

	Event(e900)
	Event(e9Z0)
	Mutex(mx90, 0)
	Mutex(mx91, 0)
	Device(d900) { Name(i900, 0xabcd4017) }
	Device(d9Z0) { Name(i900, 0xabcd4017) }
	ThermalZone(tz90) {}
	ThermalZone(tz91) {}
	Processor(pr90, 0, 0xFFFFFFFF, 0) {}
	Processor(pr91, 0, 0xFFFFFFFF, 0) {}
	OperationRegion(r900, SystemMemory, 0x100, 0x100)
	OperationRegion(r9Z0, SystemMemory, 0x100, 0x100)
	PowerResource(pw90, 1, 0) {Method(mmmm){return (0)}}
	PowerResource(pw91, 1, 0) {Method(mmmm){return (0)}}

	// Computational Data

	Name(i900, 0xfe7cb391d65a4000)
	Name(i9Z0, 0xfe7cb391d65a4000)
	Name(i901, 0xc1794001)
	Name(i9Z1, 0xc1794001)
	Name(i902, 0)
	Name(i903, 0xffffffffffffffff)
	Name(i904, 0xffffffff)
	Name(s900, "12344002")
	Name(s9Z0, "12344002")
	Name(s901, "qwrtyu4003")
	Name(s9Z1, "qwrtyu4003")
	Name(b900, Buffer() {0xe0,0xe1,0xe2,0xe3,0xe4})
	Name(b9Z0, Buffer() {0xe0,0xe1,0xe2,0xe3,0xe4})

	CreateField(b9Z0, 0, 8, bf90)
	Field(r9Z0, ByteAcc, NoLock, Preserve) {f900,8,f901,8,f902,8,f903,8}
	BankField(r9Z0, f901, 0, ByteAcc, NoLock, Preserve) {bn90,4}
	IndexField(f902, f903, ByteAcc, NoLock, Preserve) {if90,8,if91,8}

	// Elements of Package are Uninitialized

	Name(p900, Package(1) {})

	// Elements of Package are Computational Data

	Name(p901, Package() {0xabcd4004, 0x1122334455664005})
	Name(p902, Package() {"12344006", "q1w2e3r4t5y6u7i84007"})
	Name(p903, Package() {"qwrtyuiop4008", "1234567890abdef0254009"})
	Name(p904, Package() {Buffer() {0xe5,0xe6,0xe7}, Buffer() {0xe8,0xe9}})
	Name(p905, Package() {Package() {0xabc400a, "0xabc400b", "abc400c"}})
	Name(p906, Package() {Package() {"abc400d"}})
	Name(p907, Package() {Package() {"aqwevbgnm400e"}})
	Name(p908, Package() {Package() {Buffer() {0xea,0xeb,0xec,0xed,0xee}}})
	Name(p909, Package() {Package() {Package() {0xabc400f}}})
	Name(p90a, Package() {Package() {Package() {"12344010"}}})
	Name(p90b, Package() {Package() {Package() {"zxswefas4011"}}})
	Name(p90c, Package() {Package() {Package() {Buffer() {0xef,0x30,0x31}}}})

	Name(p90d, Package() {i900})
	Name(p90e, Package() {i901})
	Name(p90f, Package() {s900})
	Name(p910, Package() {s901})
	Name(p911, Package() {b9Z0})
	Name(p912, Package() {f900})
	Name(p913, Package() {bn90})
	Name(p914, Package() {if90})
	Name(p915, Package() {bf90})

	// Elements of Package are NOT Computational Data

	Name(p916, Package() {d900})
	Name(p917, Package() {e900})
	Name(p918, Package() {mx90})
	Name(p919, Package() {r9Z0})
	Name(p91a, Package() {pw90})
	Name(p91b, Package() {pr90})
	Name(p91c, Package() {tz90})

	// Methods

	Method(m900) {}

	// Elements of Package are Methods

	Name(p91d, Package() {m900})

	Name(p953, Package() {0xabcd4018, 0xabcd4019})
	Name(p954, Package() {0xabcd4018, 0xabcd4019})


	// Check that all the data (local) are not corrupted
	Method(m000)
	{
	// Computational Data

	// Integer

	Store(ObjectType(i900), Local0)
	if (LNotEqual(Local0, c009)) {
		err(c080, z077, 0x100, 0, 0, Local0, c009)
	}
	if (LNotEqual(i900, 0xfe7cb391d65a4000)) {
		err(c080, z077, 0x101, 0, 0, i900, 0xfe7cb391d65a4000)
	}

	Store(ObjectType(i901), Local0)
	if (LNotEqual(Local0, c009)) {
		err(c080, z077, 0x102, 0, 0, Local0, c009)
	}
	if (LNotEqual(i901, 0xc1794001)) {
		err(c080, z077, 0x103, 0, 0, i901, 0xc1794001)
	}

	Store(ObjectType(i902), Local0)
	if (LNotEqual(Local0, c009)) {
		err(c080, z077, 0x104, 0, 0, Local0, c009)
	}
	if (LNotEqual(i902, 0)) {
		err(c080, z077, 0x105, 0, 0, i902, 0)
	}

	Store(ObjectType(i903), Local0)
	if (LNotEqual(Local0, c009)) {
		err(c080, z077, 0x106, 0, 0, Local0, c009)
	}
	if (LNotEqual(i903, 0xffffffffffffffff)) {
		err(c080, z077, 0x107, 0, 0, i903, 0xffffffffffffffff)
	}

	Store(ObjectType(i904), Local0)
	if (LNotEqual(Local0, c009)) {
		err(c080, z077, 0x108, 0, 0, Local0, c009)
	}
	if (LNotEqual(i904, 0xffffffff)) {
		err(c080, z077, 0x109, 0, 0, i904, 0xffffffff)
	}

	// String

	Store(ObjectType(s900), Local0)
	if (LNotEqual(Local0, c00a)) {
		err(c080, z077, 0x10a, 0, 0, Local0, c00a)
	}
	if (LNotEqual(s900, "12344002")) {
		err(c080, z077, 0x10b, 0, 0, s900, "12344002")
	}

	Store(ObjectType(s901), Local0)
	if (LNotEqual(Local0, c00a)) {
		err(c080, z077, 0x10c, 0, 0, Local0, c00a)
	}
	if (LNotEqual(s901, "qwrtyu4003")) {
		err(c080, z077, 0x10d, 0, 0, s901, "qwrtyu4003")
	}

	// Buffer

	Store(ObjectType(b900), Local0)
	if (LNotEqual(Local0, c00b)) {
		err(c080, z077, 0x10e, 0, 0, Local0, c00b)
	}
	if (LNotEqual(b900, Buffer() {0xe0,0xe1,0xe2,0xe3,0xe4})) {
		err(c080, z077, 0x10f, 0, 0, b900, Buffer() {0xe0,0xe1,0xe2,0xe3,0xe4})
	}

	// Buffer Field

	Store(ObjectType(bf90), Local0)
	if (LNotEqual(Local0, c016)) {
		err(c080, z077, 0x110, 0, 0, Local0, c016)
	}
	if (LNotEqual(bf90, 0xe0)) {
		err(c080, z077, 0x111, 0, 0, bf90, 0xe0)
	}

	// One level Package

	Store(Index(p900, 0), Local0)
	Store(ObjectType(Local0), Local1)
	if (LNotEqual(Local1, c008)) {
		err(c080, z077, 0x112, 0, 0, Local1, c008)
	}

	Store(Index(p901, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c009)) {
		err(c080, z077, 0x113, 0, 0, Local2, c009)
	}
	if (LNotEqual(Local1, 0xabcd4004)) {
		err(c080, z077, 0x114, 0, 0, Local1, 0xabcd4004)
	}

	Store(Index(p901, 1), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c009)) {
		err(c080, z077, 0x115, 0, 0, Local2, c009)
	}
	if (LNotEqual(Local1, 0x1122334455664005)) {
		err(c080, z077, 0x116, 0, 0, Local1, 0x1122334455664005)
	}

	Store(Index(p902, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00a)) {
		err(c080, z077, 0x117, 0, 0, Local2, c00a)
	}
	if (LNotEqual(Local1, "12344006")) {
		err(c080, z077, 0x118, 0, 0, Local1, "12344006")
	}

	Store(Index(p902, 1), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00a)) {
		err(c080, z077, 0x119, 0, 0, Local2, c00a)
	}
	if (LNotEqual(Local1, "q1w2e3r4t5y6u7i84007")) {
		err(c080, z077, 0x11a, 0, 0, Local1, "q1w2e3r4t5y6u7i84007")
	}

	Store(Index(p903, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00a)) {
		err(c080, z077, 0x11b, 0, 0, Local2, c00a)
	}
	if (LNotEqual(Local1, "qwrtyuiop4008")) {
		err(c080, z077, 0x11c, 0, 0, Local1, "qwrtyuiop4008")
	}

	Store(Index(p903, 1), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00a)) {
		err(c080, z077, 0x11d, 0, 0, Local2, c00a)
	}
	if (LNotEqual(Local1, "1234567890abdef0254009")) {
		err(c080, z077, 0x11e, 0, 0, Local1, "1234567890abdef0254009")
	}

	Store(Index(p904, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00b)) {
		err(c080, z077, 0x11f, 0, 0, Local2, c00b)
	}
	if (LNotEqual(Local1, Buffer() {0xe5,0xe6,0xe7})) {
		err(c080, z077, 0x120, 0, 0, Local1, Buffer() {0xe5,0xe6,0xe7})
	}

	Store(Index(p904, 1), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00b)) {
		err(c080, z077, 0x121, 0, 0, Local2, c00b)
	}
	if (LNotEqual(Local1, Buffer() {0xe8,0xe9})) {
		err(c080, z077, 0x122, 0, 0, Local1, Buffer() {0xe8,0xe9})
	}

	// Two level Package

	Store(Index(p905, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c009)) {
		err(c080, z077, 0x123, 0, 0, Local4, c009)
	}
	if (LNotEqual(Local3, 0xabc400a)) {
		err(c080, z077, 0x124, 0, 0, Local3, 0xabc400a)
	}

	Store(Index(p905, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 1), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c00a)) {
		err(c080, z077, 0x125, 0, 0, Local4, c00a)
	}
	if (LNotEqual(Local3, "0xabc400b")) {
		err(c080, z077, 0x126, 0, 0, Local3, "0xabc400b")
	}

	Store(Index(p905, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 2), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c00a)) {
		err(c080, z077, 0x127, 0, 0, Local4, c00a)
	}
	if (LNotEqual(Local3, "abc400c")) {
		err(c080, z077, 0x128, 0, 0, Local3, "abc400c")
	}

	Store(Index(p906, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c00a)) {
		err(c080, z077, 0x129, 0, 0, Local4, c00a)
	}
	if (LNotEqual(Local3, "abc400d")) {
		err(c080, z077, 0x12a, 0, 0, Local3, "abc400d")
	}

	Store(Index(p907, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c00a)) {
		err(c080, z077, 0x12b, 0, 0, Local4, c00a)
	}
	if (LNotEqual(Local3, "aqwevbgnm400e")) {
		err(c080, z077, 0x12c, 0, 0, Local3, "aqwevbgnm400e")
	}

	Store(Index(p908, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c00b)) {
		err(c080, z077, 0x12d, 0, 0, Local4, c00b)
	}
	if (LNotEqual(Local3, Buffer() {0xea,0xeb,0xec,0xed,0xee})) {
		err(c080, z077, 0x12e, 0, 0, Local3, Buffer() {0xea,0xeb,0xec,0xed,0xee})
	}

	// Three level Package

	Store(Index(p909, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(Index(Local3, 0), Local4)
	Store(DerefOf(Local4), Local5)
	Store(ObjectType(Local5), Local6)
	if (LNotEqual(Local6, c009)) {
		err(c080, z077, 0x12f, 0, 0, Local6, c009)
	}
	if (LNotEqual(Local5, 0xabc400f)) {
		err(c080, z077, 0x130, 0, 0, Local5, 0xabc400f)
	}

	Store(Index(p90a, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(Index(Local3, 0), Local4)
	Store(DerefOf(Local4), Local5)
	Store(ObjectType(Local5), Local6)
	if (LNotEqual(Local6, c00a)) {
		err(c080, z077, 0x131, 0, 0, Local6, c00a)
	}
	if (LNotEqual(Local5, "12344010")) {
		err(c080, z077, 0x132, 0, 0, Local5, "12344010")
	}

	Store(Index(p90b, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(Index(Local3, 0), Local4)
	Store(DerefOf(Local4), Local5)
	Store(ObjectType(Local5), Local6)
	if (LNotEqual(Local6, c00a)) {
		err(c080, z077, 0x133, 0, 0, Local6, c00a)
	}
	if (LNotEqual(Local5, "zxswefas4011")) {
		err(c080, z077, 0x134, 0, 0, Local5, "zxswefas4011")
	}

	Store(Index(p90c, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(Index(Local3, 0), Local4)
	Store(DerefOf(Local4), Local5)
	Store(ObjectType(Local5), Local6)
	if (LNotEqual(Local6, c00b)) {
		err(c080, z077, 0x135, 0, 0, Local6, c00b)
	}
	if (LNotEqual(Local5, Buffer() {0xef,0x30,0x31})) {
		err(c080, z077, 0x136, 0, 0, Local5, Buffer() {0xef,0x30,0x31})
	}

	Store(Index(p953, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c009)) {
		err(c080, z077, 0x137, 0, 0, Local2, c009)
	}
	if (LNotEqual(Local1, 0xabcd4018)) {
		err(c080, z077, 0x138, 0, 0, Local1, 0xabcd4018)
	}

	Store(Index(p953, 1), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c009)) {
		err(c080, z077, 0x139, 0, 0, Local2, c009)
	}
	if (LNotEqual(Local1, 0xabcd4019)) {
		err(c080, z077, 0x13a, 0, 0, Local1, 0xabcd4019)
	}

	// Not Computational Data

	m1aa(c080, e900, c00f, 0, 0x13b)
	m1aa(c080, mx90, c011, 0, 0x13c)
	m1aa(c080, d900, c00e, 0, 0x13d)
	if (y508) {
		m1aa(c080, tz90, c015, 0, 0x13e)
	}
	m1aa(c080, pr90, c014, 0, 0x13f)
	m1aa(c080, r900, c012, 0, 0x140)
	m1aa(c080, pw90, c013, 0, 0x141)

/*
 *	// Field Unit (Field)
 *
 *	if (LNotEqual(f900, 0xd7)) {
 *		err(c080, z077, 0x137, 0, 0, f900, 0xd7)
 *	}
 *
 *	// Field Unit (IndexField)
 *
 *	if (LNotEqual(if90, 0xd7)) {
 *		err(c080, z077, 0x138, 0, 0, if90, 0xd7)
 *	}
 */
	} /* m000 */

	// Check and restore the global data after writing into them
	Method(m001)
	{

	// Computational Data

	m1aa(c080, i900, c009, c08a, 0x144)
	CopyObject(i9Z0, i900)

	m1aa(c080, i901, c009, c08a, 0x145)
	CopyObject(i9Z1, i901)

	m1aa(c080, s900, c009, c08a, 0x146)
	CopyObject(s9Z0, s900)

	m1aa(c080, s901, c009, c08a, 0x147)
	CopyObject(s9Z1, s901)

	m1aa(c080, b900, c009, c08a, 0x148)
	CopyObject(b9Z0, b900)

	// Package

	m1aa(c080, p953, c009, c08a, 0x149)
	CopyObject(p954, p953)

	// Not Computational Data

	m1aa(c080, e900, c009, c08a, 0x14a)
	CopyObject(RefOf (e9Z0), e900)

	m1aa(c080, mx90, c009, c08a, 0x14b)
	CopyObject(RefOf (mx91), mx90)

	m1aa(c080, d900, c009, c08a, 0x14c)
	CopyObject(RefOf (d9Z0), d900)

	if (y508) {
		m1aa(c080, tz90, c009, c08a, 0x14d)
		CopyObject(RefOf (tz91), tz90)
	}

	m1aa(c080, pr90, c009, c08a, 0x14e)
	CopyObject(RefOf (pr91), pr90)

	if (y510) {
		m1aa(c080, r900, c009, c08a, 0x14f)
		CopyObject(RefOf (r9Z0), r900)
	}

	m1aa(c080, pw90, c009, c08a, 0x150)
	CopyObject(RefOf (pw91), pw90)

	m000()
	} /* m001 */


	// T2:CR1-CR14

	// Computational Data

	Store(CondRefOf(i900, Local0), Local1)
	if (m1a4(Local1, 591)) {
		m1a2(Local0, c009, 0, 0, c009, 0xfe7cb391d65a4000, 592)
	}

	Store(CondRefOf(i901, Local0), Local1)
	if (m1a4(Local1, 593)) {
		m1a2(Local0, c009, 0, 0, c009, 0xc1794001, 594)
	}

	Store(CondRefOf(s900, Local0), Local1)
	if (m1a4(Local1, 595)) {
		m1a2(Local0, c00a, 0, 0, c00a, "12344002", 596)
	}

	Store(CondRefOf(s901, Local0), Local1)
	if (m1a4(Local1, 597)) {
		m1a2(Local0, c00a, 0, 0, c00a, "qwrtyu4003", 598)
	}

	Store(CondRefOf(b900, Local0), Local1)
	if (m1a4(Local1, 599)) {
		m1a2(Local0, c00b, 0, 0, c00b, Buffer() {0xe0,0xe1,0xe2,0xe3,0xe4}, 600)
	}

	// Not Computational Data

	Store(CondRefOf(e900, Local0), Local1)
	m1a0(Local0, c00f, Local1, 609)

	Store(CondRefOf(mx90, Local0), Local1)
	m1a0(Local0, c011, Local1, 610)

	Store(CondRefOf(d900, Local0), Local1)
	m1a0(Local0, c00e, Local1, 611)

	if (arg0) {
		if (y508) {
			Store(CondRefOf(tz90, Local0), Local1)
			m1a0(Local0, c015, Local1, 612)
		}
	} else {
		Store(CondRefOf(tz90, Local0), Local1)
		m1a0(Local0, c015, Local1, 1004)
	}

	Store(CondRefOf(pr90, Local0), Local1)
	m1a0(Local0, c014, Local1, 613)

	if (arg0) {
		if (y510) {
			Store(CondRefOf(r900, Local0), Local1)
			m1a0(Local0, c012, Local1, 614)
		}
	} else {
		Store(CondRefOf(r900, Local0), Local1)
		m1a0(Local0, c012, Local1, 614)
	}

	Store(CondRefOf(pw90, Local0), Local1)
	m1a0(Local0, c013, Local1, 615)

	// Package

	Store(CondRefOf(p953, Local0), Local1)
	if (m1a4(Local1, 1005)) {
		m1a2(Local0, c00c, 1, 0, c009, 0xabcd4018, 1006)
	}

	if (arg0) {
		m001()
		return
	}

	// Computational Data (Field Unit and Buffer Field)

	Store(CondRefOf(f900, Local0), Local1)
	if (m1a4(Local1, 601)) {
		m1a2(Local0, c00d, 0, 0, c009, 0, 602)
	}

	Store(CondRefOf(bn90, Local0), Local1)
	if (m1a4(Local1, 603)) {
		m1a2(Local0, c00d, 0, 0, c009, 0, 604)
	}

	Store(CondRefOf(if90, Local0), Local1)
	if (m1a4(Local1, 605)) {
		m1a2(Local0, c00d, 0, 0, c009, 0, 606)
	}

	Store(CondRefOf(bf90, Local0), Local1)
	if (m1a4(Local1, 607)) {
		m1a2(Local0, c016, 0, 0, c009, 0xe0, 608)
	}

	// Elements of Package are Uninitialized

	Store(CondRefOf(p900, Local0), Local1)
	m1a0(Local0, c00c, Local1, 616)

	// Elements of Package are Computational Data

	Store(CondRefOf(p901, Local0), Local1)
	if (m1a4(Local1, 617)) {
		m1a2(Local0, c00c, 1, 0, c009, 0xabcd4004, 618)
		m1a2(Local0, c00c, 1, 1, c009, 0x1122334455664005, 619)
	}

	Store(CondRefOf(p902, Local0), Local1)
	if (m1a4(Local1, 620)) {
		m1a2(Local0, c00c, 1, 0, c00a, "12344006", 621)
		m1a2(Local0, c00c, 1, 1, c00a, "q1w2e3r4t5y6u7i84007", 622)
	}

	Store(CondRefOf(p903, Local0), Local1)
	if (m1a4(Local1, 623)) {
		m1a2(Local0, c00c, 1, 0, c00a, "qwrtyuiop4008", 624)
		m1a2(Local0, c00c, 1, 1, c00a, "1234567890abdef0254009", 625)
	}

	Store(CondRefOf(p904, Local0), Local1)
	if (m1a4(Local1, 626)) {
		m1a2(Local0, c00c, 1, 0, c00b, Buffer() {0xe5,0xe6,0xe7}, 627)
	}

	Store(CondRefOf(p905, Local0), Local1)
	if (m1a4(Local1, 628)) {
		m1a2(Local0, c00c, 2, 0, c009, 0xabc400a, 629)
		m1a2(Local0, c00c, 2, 1, c00a, "0xabc400b", 630)
	}

	Store(CondRefOf(p906, Local0), Local1)
	if (m1a4(Local1, 631)) {
		m1a2(Local0, c00c, 2, 0, c00a, "abc400d", 632)
	}

	Store(CondRefOf(p907, Local0), Local1)
	if (m1a4(Local1, 633)) {
		m1a2(Local0, c00c, 2, 0, c00a, "aqwevbgnm400e", 634)
	}

	Store(CondRefOf(p908, Local0), Local1)
	if (m1a4(Local1, 635)) {
		m1a2(Local0, c00c, 2, 0, c00b, Buffer() {0xea,0xeb,0xec,0xed,0xee}, 636)
	}

	Store(CondRefOf(p909, Local0), Local1)
	if (m1a4(Local1, 637)) {
		m1a2(Local0, c00c, 3, 0, c009, 0xabc400f, 638)
	}

	Store(CondRefOf(p90a, Local0), Local1)
	if (m1a4(Local1, 639)) {
		m1a2(Local0, c00c, 3, 0, c00a, "12344010", 640)
	}

	Store(CondRefOf(p90b, Local0), Local1)
	if (m1a4(Local1, 641)) {
		m1a2(Local0, c00c, 3, 0, c00a, "zxswefas4011", 642)
	}

	Store(CondRefOf(p90c, Local0), Local1)
	if (m1a4(Local1, 643)) {
		m1a2(Local0, c00c, 3, 0, c00b, Buffer() {0xef,0x30,0x31}, 644)
	}

	// In-package name strings are String typed, not ObjectReference
	// typed.

	// Elements of Package are NameString

	Store(CondRefOf(p90d, Local0), Local1)
	if (m1a4(Local1, 645)) {
		m1a2(Local0, c00c, 1, 0, c00a, "I900", 646)
	}

	Store(CondRefOf(p90e, Local0), Local1)
	if (m1a4(Local1, 647)) {
		m1a2(Local0, c00c, 1, 0, c00a, "I901", 648)
	}

	Store(CondRefOf(p90f, Local0), Local1)
	if (m1a4(Local1, 649)) {
		m1a2(Local0, c00c, 1, 0, c00a, "S900", 650)
	}

	Store(CondRefOf(p910, Local0), Local1)
	if (m1a4(Local1, 651)) {
		m1a2(Local0, c00c, 1, 0, c00a, "S901", 652)
	}

	Store(CondRefOf(p911, Local0), Local1)
	if (m1a4(Local1, 653)) {
		m1a2(Local0, c00c, 1, 0, c00a, "B9Z0", 654)
	}

	Store(CondRefOf(p912, Local0), Local1)
	if (m1a4(Local1, 655)) {
		m1a2(Local0, c00c, 1, 0, c00a, "F900", 656)
	}

	Store(CondRefOf(p913, Local0), Local1)
	if (m1a4(Local1, 657)) {
		m1a2(Local0, c00c, 1, 0, c00a, "BN90", 658)
	}

	Store(CondRefOf(p914, Local0), Local1)
	if (m1a4(Local1, 659)) {
		m1a2(Local0, c00c, 1, 0, c00a, "IF90", 660)
	}

	Store(CondRefOf(p915, Local0), Local1)
	if (m1a4(Local1, 661)) {
		m1a2(Local0, c00c, 1, 0, c00a, "BF90", 662)
	}

	Store(CondRefOf(p916, Local0), Local1)
	if (m1a4(Local1, 663)) {
		m1a2(Local0, c00c, 1, 0, c00a, "D900", 664)
	}

	Store(CondRefOf(p917, Local0), Local1)
	if (m1a4(Local1, 665)) {
		m1a2(Local0, c00c, 1, 0, c00a, "E900", 666)
	}

	Store(CondRefOf(p918, Local0), Local1)
	if (m1a4(Local1, 667)) {
		m1a2(Local0, c00c, 1, 0, c00a, "MX90", 668)
	}

	Store(CondRefOf(p919, Local0), Local1)
	if (m1a4(Local1, 669)) {
		m1a2(Local0, c00c, 1, 0, c00a, "R9Z0", 670)
	}

	Store(CondRefOf(p91a, Local0), Local1)
	if (m1a4(Local1, 671)) {
		m1a2(Local0, c00c, 1, 0, c00a, "PW90", 672)
	}

	Store(CondRefOf(p91b, Local0), Local1)
	if (m1a4(Local1, 673)) {
		m1a2(Local0, c00c, 1, 0, c00a, "PR90", 674)
	}

	Store(CondRefOf(p91c, Local0), Local1)
	if (m1a4(Local1, 675)) {
		m1a2(Local0, c00c, 1, 0, c00a, "TZ90", 676)
	}

	Store(CondRefOf(p91d, Local0), Local1)
	if (m1a4(Local1, 677)) {
		m1a2(Local0, c00c, 1, 0, c00a, "M900", 678)
	}

	// Methods

	Store(CondRefOf(m900, Local0), Local1)
	m1a0(Local0, c010, Local1, 724)

	m000()
	m1a6()

	return
}

// ///////////////////////////////////////////////////////////////////////////
//
// TABLE 3: all the legal ways to generate references to the
//          immediate images (constants) being elements of Package
//
// ///////////////////////////////////////////////////////////////////////////

Method(m16d)
{

	if (y100) {
		ts00("m16d")
	} else {
		Store("m16d", Debug)
	}

	if (LNot(y900)) {
		Store("Test m16d skipped!", Debug)
		return
	}

	// T3:I0-I4

	if (y104) {
		Store(Index(Package(1){}, 0), Local0)
		m1a0(Local0, c008, Ones, 1281)
	}

	Store(Index(Package(){0xabcdef}, 0), Local0)
	m1a2(Local0, c009, 0, 0, c009, 0xabcdef, 1282)

	Store(Index(Package(){"123456789"}, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "123456789", 1283)

	Store(Index(Package(){"qwrtyuiop"}, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "qwrtyuiop", 1284)

	Store(Index(Package(){Buffer() {1,2,3,4,5,6,7,8}}, 0), Local0)
	m1a2(Local0, c00b, 0, 0, c00b, Buffer() {1,2,3,4,5,6,7,8}, 1285)

	Store(Index(Package(){Package() {0xabcdef}}, 0), Local0)
	m1a2(Local0, c00c, 1, 0, c009, 0xabcdef, 1286)

	Store(Index(Package(){Package() {"123456789"}}, 0), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "123456789", 1287)

	Store(Index(Package(){Package() {"qwrtyuiop"}}, 0), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "qwrtyuiop", 1288)

	Store(Index(Package(){Package() {Buffer() {1,2,3,4,5,6,7,8,9}}}, 0), Local0)
	m1a2(Local0, c00c, 1, 0, c00b, Buffer() {1,2,3,4,5,6,7,8,9}, 1289)

	Store(Index(Package(){Package() {Package() {0xabcdef}}}, 0), Local0)
	m1a2(Local0, c00c, 2, 0, c009, 0xabcdef, 1290)

	Store(Index(Package(){Package() {Package() {"123456789"}}}, 0), Local0)
	m1a2(Local0, c00c, 2, 0, c00a, "123456789", 1291)

	Store(Index(Package(){Package() {Package() {"qwrtyuiop"}}}, 0), Local0)
	m1a2(Local0, c00c, 2, 0, c00a, "qwrtyuiop", 1292)

	Store(Index(Package(){Package() {Package() {Buffer() {1,2,3,4,5,6,7,8,9}}}}, 0), Local0)
	m1a2(Local0, c00c, 2, 0, c00b, Buffer() {1,2,3,4,5,6,7,8,9}, 1293)

	Store(Index(Package(){Package() {Package() {Package() {0xabcdef}}}}, 0), Local0)
	m1a2(Local0, c00c, 3, 0, c009, 0xabcdef, 1294)

	Store(Index(Package(){Package() {Package() {Package() {"123456789"}}}}, 0), Local0)
	m1a2(Local0, c00c, 3, 0, c00a, "123456789", 1295)

	Store(Index(Package(){Package() {Package() {Package() {"qwrtyuiop"}}}}, 0), Local0)
	m1a2(Local0, c00c, 3, 0, c00a, "qwrtyuiop", 1296)

	Store(Index(Package(){Package() {Package() {Package() {Buffer() {1,2,3,4,5,6,7,8,9}}}}}, 0), Local0)
	m1a2(Local0, c00c, 3, 0, c00b, Buffer() {1,2,3,4,5,6,7,8,9}, 1297)

	// T3:IR0-IR4

	if (y104) {
		Store(Index(Package(1){}, 0, Local1), Local0)
		m1a0(Local0, c008, Ones, 1298)
		m1a0(Local1, c008, Ones, 1299)
	}

	Store(Index(Package(){0xabcdef}, 0, Local1), Local0)
	m1a2(Local0, c009, 0, 0, c009, 0xabcdef, 1300)
	m1a2(Local1, c009, 0, 0, c009, 0xabcdef, 1301)

	Store(Index(Package(){"123456789"}, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "123456789", 1302)
	m1a2(Local1, c00a, 0, 0, c00a, "123456789", 1303)

	Store(Index(Package(){"qwrtyuiop"}, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "qwrtyuiop", 1304)
	m1a2(Local1, c00a, 0, 0, c00a, "qwrtyuiop", 1305)

	Store(Index(Package(){Buffer() {1,2,3,4,5,6,7,8}}, 0, Local1), Local0)
	m1a2(Local0, c00b, 0, 0, c00b, Buffer() {1,2,3,4,5,6,7,8}, 1306)
	m1a2(Local1, c00b, 0, 0, c00b, Buffer() {1,2,3,4,5,6,7,8}, 1307)

	Store(Index(Package(){Package() {0xabcdef}}, 0, Local1), Local0)
	m1a2(Local0, c00c, 1, 0, c009, 0xabcdef, 1308)
	m1a2(Local1, c00c, 1, 0, c009, 0xabcdef, 1309)

	Store(Index(Package(){Package() {"123456789"}}, 0, Local1), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "123456789", 1310)
	m1a2(Local1, c00c, 1, 0, c00a, "123456789", 1311)

	Store(Index(Package(){Package() {"qwrtyuiop"}}, 0, Local1), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "qwrtyuiop", 1312)
	m1a2(Local1, c00c, 1, 0, c00a, "qwrtyuiop", 1313)

	Store(Index(Package(){Package() {Buffer() {1,2,3,4,5,6,7,8,9}}}, 0, Local1), Local0)
	m1a2(Local0, c00c, 1, 0, c00b, Buffer() {1,2,3,4,5,6,7,8,9}, 1314)
	m1a2(Local1, c00c, 1, 0, c00b, Buffer() {1,2,3,4,5,6,7,8,9}, 1315)

	Store(Index(Package(){Package() {Package() {0xabcdef}}}, 0, Local1), Local0)
	m1a2(Local0, c00c, 2, 0, c009, 0xabcdef, 1316)
	m1a2(Local1, c00c, 2, 0, c009, 0xabcdef, 1317)

	Store(Index(Package(){Package() {Package() {"123456789"}}}, 0, Local1), Local0)
	m1a2(Local0, c00c, 2, 0, c00a, "123456789", 1318)
	m1a2(Local1, c00c, 2, 0, c00a, "123456789", 1319)

	Store(Index(Package(){Package() {Package() {"qwrtyuiop"}}}, 0, Local1), Local0)
	m1a2(Local0, c00c, 2, 0, c00a, "qwrtyuiop", 1320)
	m1a2(Local1, c00c, 2, 0, c00a, "qwrtyuiop", 1321)

	Store(Index(Package(){Package() {Package() {Buffer() {1,2,3,4,5,6,7,8,9}}}}, 0, Local1), Local0)
	m1a2(Local0, c00c, 2, 0, c00b, Buffer() {1,2,3,4,5,6,7,8,9}, 1322)
	m1a2(Local1, c00c, 2, 0, c00b, Buffer() {1,2,3,4,5,6,7,8,9}, 1323)

	Store(Index(Package(){Package() {Package() {Package() {0xabcdef}}}}, 0, Local1), Local0)
	m1a2(Local0, c00c, 3, 0, c009, 0xabcdef, 1324)
	m1a2(Local1, c00c, 3, 0, c009, 0xabcdef, 1325)

	Store(Index(Package(){Package() {Package() {Package() {"123456789"}}}}, 0, Local1), Local0)
	m1a2(Local0, c00c, 3, 0, c00a, "123456789", 1326)
	m1a2(Local1, c00c, 3, 0, c00a, "123456789", 1327)

	Store(Index(Package(){Package() {Package() {Package() {"qwrtyuiop"}}}}, 0, Local1), Local0)
	m1a2(Local0, c00c, 3, 0, c00a, "qwrtyuiop", 1328)
	m1a2(Local1, c00c, 3, 0, c00a, "qwrtyuiop", 1329)

	Store(Index(Package(){Package() {Package() {Package() {Buffer() {1,2,3,4,5,6,7,8,9}}}}}, 0, Local1), Local0)
	m1a2(Local0, c00c, 3, 0, c00b, Buffer() {1,2,3,4,5,6,7,8,9}, 1330)
	m1a2(Local1, c00c, 3, 0, c00b, Buffer() {1,2,3,4,5,6,7,8,9}, 1331)
}

// ///////////////////////////////////////////////////////////////////////////
//
// TABLE 4: all the legal ways to generate references to the named objects
//          being elements of Package
//
// ///////////////////////////////////////////////////////////////////////////

Method(m16e,, Serialized)
{
	if (y100) {
		ts00("m16e")
	} else {
		Store("m16e", Debug)
	}

	if (LNot(y900)) {
		Store("Test m16e skipped!", Debug)
		return
	}

	// Not Computational Data

	Event(e900)
	Mutex(mx90, 0)
	Device(d900) {}
	ThermalZone(tz90) {}
	Processor(pr90, 0, 0xFFFFFFFF, 0) {}
	OperationRegion(r900, SystemMemory, 0x100, 0x100)
	OperationRegion(r9Z0, SystemMemory, 0x100, 0x100)
	PowerResource(pw90, 1, 0) {Method(mmmm){return (0)}}

	// Computational Data

	Name(i900, 0xfe7cb391d65a5000)
	Name(i901, 0x41795001)
	Name(i902, 0)
	Name(i903, 0xffffffffffffffff)
	Name(i904, 0xffffffff)
	Name(s900, "12345002")
	Name(s901, "qwrtyu5003")
	Name(b900, Buffer() {0xf0,0xf1,0xf2,0xf3,0xf4})
	Name(b9Z0, Buffer() {0xf0,0xf1,0xf2,0xf3,0xf4})

	CreateField(b900, 0, 8, bf90)
	Field(r900, ByteAcc, NoLock, Preserve) {f900,8,f901,8,f902,8,f903,8}
	BankField(r900, f901, 0, ByteAcc, NoLock, Preserve) {bn90,4}
	IndexField(f902, f903, ByteAcc, NoLock, Preserve) {if90,8,if91,8}

	// Elements of Package are Uninitialized

	Name(p900, Package(1) {})

	// Elements of Package are Computational Data

	Name(p901, Package() {0xabcd5004, 0x1122334455665005})
	Name(p902, Package() {"12345006", "q1w2e3r4t5y6u7i85007"})
	Name(p903, Package() {"qwrtyuiop5008", "1234567890abdef0255009"})
	Name(p904, Package() {Buffer() {0xf5,0xf6,0xf7}, Buffer() {0xf8,0xf9}})
	Name(p905, Package() {Package() {0xabc500a, "0xabc500b", "abc500c"}})
	Name(p906, Package() {Package() {"abc500d"}})
	Name(p907, Package() {Package() {"aqwevbgnm500e"}})
	Name(p908, Package() {Package() {Buffer() {0xfa,0xfb,0xfc,0xfd,0xfe}}})
	Name(p909, Package() {Package() {Package() {0xabc500f}}})
	Name(p90a, Package() {Package() {Package() {"12345010"}}})
	Name(p90b, Package() {Package() {Package() {"zxswefas5011"}}})
	Name(p90c, Package() {Package() {Package() {Buffer() {0xff,0x40,0x41}}}})

	Name(p90d, Package() {i900})
	Name(p90e, Package() {i901})
	Name(p90f, Package() {s900})
	Name(p910, Package() {s901})
	Name(p911, Package() {b9Z0})
	Name(p912, Package() {f900})
	Name(p913, Package() {bn90})
	Name(p914, Package() {if90})
	Name(p915, Package() {bf90})

	// Elements of Package are NOT Computational Data

	Name(p916, Package() {d900})
	Name(p917, Package() {e900})
	Name(p918, Package() {mx90})
	Name(p919, Package() {r900})
	Name(p91a, Package() {pw90})
	Name(p91b, Package() {pr90})
	Name(p91c, Package() {tz90})

	// Methods

	Method(m900) {}

	// Elements of Package are Methods

	Name(p91d, Package() {m900})

	Name(p953, Package() {0xabcd5018, 0xabcd5019})
	Name(p954, Package() {0xabcd5018, 0xabcd5019})

	// Check that all the data (local) are not corrupted
	Method(m000)
	{
	// Computational Data

	// Integer

	Store(ObjectType(i900), Local0)
	if (LNotEqual(Local0, c009)) {
		err(c080, z077, 0x100, 0, 0, Local0, c009)
	}
	if (LNotEqual(i900, 0xfe7cb391d65a5000)) {
		err(c080, z077, 0x101, 0, 0, i900, 0xfe7cb391d65a5000)
	}

	Store(ObjectType(i901), Local0)
	if (LNotEqual(Local0, c009)) {
		err(c080, z077, 0x102, 0, 0, Local0, c009)
	}
	if (LNotEqual(i901, 0x41795001)) {
		err(c080, z077, 0x103, 0, 0, i901, 0x41795001)
	}

	Store(ObjectType(i902), Local0)
	if (LNotEqual(Local0, c009)) {
		err(c080, z077, 0x104, 0, 0, Local0, c009)
	}
	if (LNotEqual(i902, 0)) {
		err(c080, z077, 0x105, 0, 0, i902, 0)
	}

	Store(ObjectType(i903), Local0)
	if (LNotEqual(Local0, c009)) {
		err(c080, z077, 0x106, 0, 0, Local0, c009)
	}
	if (LNotEqual(i903, 0xffffffffffffffff)) {
		err(c080, z077, 0x107, 0, 0, i903, 0xffffffffffffffff)
	}

	Store(ObjectType(i904), Local0)
	if (LNotEqual(Local0, c009)) {
		err(c080, z077, 0x108, 0, 0, Local0, c009)
	}
	if (LNotEqual(i904, 0xffffffff)) {
		err(c080, z077, 0x109, 0, 0, i904, 0xffffffff)
	}

	// String

	Store(ObjectType(s900), Local0)
	if (LNotEqual(Local0, c00a)) {
		err(c080, z077, 0x10a, 0, 0, Local0, c00a)
	}
	if (LNotEqual(s900, "12345002")) {
		err(c080, z077, 0x10b, 0, 0, s900, "12345002")
	}

	Store(ObjectType(s901), Local0)
	if (LNotEqual(Local0, c00a)) {
		err(c080, z077, 0x10c, 0, 0, Local0, c00a)
	}
	if (LNotEqual(s901, "qwrtyu5003")) {
		err(c080, z077, 0x10d, 0, 0, s901, "qwrtyu5003")
	}

	// Buffer

	Store(ObjectType(b900), Local0)
	if (LNotEqual(Local0, c00b)) {
		err(c080, z077, 0x10e, 0, 0, Local0, c00b)
	}
	if (LNotEqual(b900, Buffer() {0xf0,0xf1,0xf2,0xf3,0xf4})) {
		err(c080, z077, 0x10f, 0, 0, b900, Buffer() {0xf0,0xf1,0xf2,0xf3,0xf4})
	}

	// Buffer Field

	Store(ObjectType(bf90), Local0)
	if (LNotEqual(Local0, c016)) {
		err(c080, z077, 0x110, 0, 0, Local0, c016)
	}
	if (LNotEqual(bf90, 0xf0)) {
		err(c080, z077, 0x111, 0, 0, bf90, 0xf0)
	}

	// One level Package

	Store(Index(p900, 0), Local0)
	Store(ObjectType(Local0), Local1)
	if (LNotEqual(Local1, c008)) {
		err(c080, z077, 0x112, 0, 0, Local1, c008)
	}

	Store(Index(p901, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c009)) {
		err(c080, z077, 0x113, 0, 0, Local2, c009)
	}
	if (LNotEqual(Local1, 0xabcd5004)) {
		err(c080, z077, 0x114, 0, 0, Local1, 0xabcd5004)
	}

	Store(Index(p901, 1), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c009)) {
		err(c080, z077, 0x115, 0, 0, Local2, c009)
	}
	if (LNotEqual(Local1, 0x1122334455665005)) {
		err(c080, z077, 0x116, 0, 0, Local1, 0x1122334455665005)
	}

	Store(Index(p902, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00a)) {
		err(c080, z077, 0x117, 0, 0, Local2, c00a)
	}
	if (LNotEqual(Local1, "12345006")) {
		err(c080, z077, 0x118, 0, 0, Local1, "12345006")
	}

	Store(Index(p902, 1), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00a)) {
		err(c080, z077, 0x119, 0, 0, Local2, c00a)
	}
	if (LNotEqual(Local1, "q1w2e3r4t5y6u7i85007")) {
		err(c080, z077, 0x11a, 0, 0, Local1, "q1w2e3r4t5y6u7i85007")
	}

	Store(Index(p903, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00a)) {
		err(c080, z077, 0x11b, 0, 0, Local2, c00a)
	}
	if (LNotEqual(Local1, "qwrtyuiop5008")) {
		err(c080, z077, 0x11c, 0, 0, Local1, "qwrtyuiop5008")
	}

	Store(Index(p903, 1), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00a)) {
		err(c080, z077, 0x11d, 0, 0, Local2, c00a)
	}
	if (LNotEqual(Local1, "1234567890abdef0255009")) {
		err(c080, z077, 0x11e, 0, 0, Local1, "1234567890abdef0255009")
	}

	Store(Index(p904, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00b)) {
		err(c080, z077, 0x11f, 0, 0, Local2, c00b)
	}
	if (LNotEqual(Local1, Buffer() {0xf5,0xf6,0xf7})) {
		err(c080, z077, 0x120, 0, 0, Local1, Buffer() {0xf5,0xf6,0xf7})
	}

	Store(Index(p904, 1), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c00b)) {
		err(c080, z077, 0x121, 0, 0, Local2, c00b)
	}
	if (LNotEqual(Local1, Buffer() {0xf8,0xf9})) {
		err(c080, z077, 0x122, 0, 0, Local1, Buffer() {0xf8,0xf9})
	}

	// Two level Package

	Store(Index(p905, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c009)) {
		err(c080, z077, 0x123, 0, 0, Local4, c009)
	}
	if (LNotEqual(Local3, 0xabc500a)) {
		err(c080, z077, 0x124, 0, 0, Local3, 0xabc500a)
	}

	Store(Index(p905, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 1), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c00a)) {
		err(c080, z077, 0x125, 0, 0, Local4, c00a)
	}
	if (LNotEqual(Local3, "0xabc500b")) {
		err(c080, z077, 0x126, 0, 0, Local3, "0xabc500b")
	}

	Store(Index(p905, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 2), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c00a)) {
		err(c080, z077, 0x127, 0, 0, Local4, c00a)
	}
	if (LNotEqual(Local3, "abc500c")) {
		err(c080, z077, 0x128, 0, 0, Local3, "abc500c")
	}

	Store(Index(p906, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c00a)) {
		err(c080, z077, 0x129, 0, 0, Local4, c00a)
	}
	if (LNotEqual(Local3, "abc500d")) {
		err(c080, z077, 0x12a, 0, 0, Local3, "abc500d")
	}

	Store(Index(p907, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c00a)) {
		err(c080, z077, 0x12b, 0, 0, Local4, c00a)
	}
	if (LNotEqual(Local3, "aqwevbgnm500e")) {
		err(c080, z077, 0x12c, 0, 0, Local3, "aqwevbgnm500e")
	}

	Store(Index(p908, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(ObjectType(Local3), Local4)
	if (LNotEqual(Local4, c00b)) {
		err(c080, z077, 0x12d, 0, 0, Local4, c00b)
	}
	if (LNotEqual(Local3, Buffer() {0xfa,0xfb,0xfc,0xfd,0xfe})) {
		err(c080, z077, 0x12e, 0, 0, Local3, Buffer() {0xfa,0xfb,0xfc,0xfd,0xfe})
	}

	// Three level Package

	Store(Index(p909, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(Index(Local3, 0), Local4)
	Store(DerefOf(Local4), Local5)
	Store(ObjectType(Local5), Local6)
	if (LNotEqual(Local6, c009)) {
		err(c080, z077, 0x12f, 0, 0, Local6, c009)
	}
	if (LNotEqual(Local5, 0xabc500f)) {
		err(c080, z077, 0x130, 0, 0, Local5, 0xabc500f)
	}

	Store(Index(p90a, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(Index(Local3, 0), Local4)
	Store(DerefOf(Local4), Local5)
	Store(ObjectType(Local5), Local6)
	if (LNotEqual(Local6, c00a)) {
		err(c080, z077, 0x131, 0, 0, Local6, c00a)
	}
	if (LNotEqual(Local5, "12345010")) {
		err(c080, z077, 0x132, 0, 0, Local5, "12345010")
	}

	Store(Index(p90b, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(Index(Local3, 0), Local4)
	Store(DerefOf(Local4), Local5)
	Store(ObjectType(Local5), Local6)
	if (LNotEqual(Local6, c00a)) {
		err(c080, z077, 0x133, 0, 0, Local6, c00a)
	}
	if (LNotEqual(Local5, "zxswefas5011")) {
		err(c080, z077, 0x134, 0, 0, Local5, "zxswefas5011")
	}

	Store(Index(p90c, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(Index(Local1, 0), Local2)
	Store(DerefOf(Local2), Local3)
	Store(Index(Local3, 0), Local4)
	Store(DerefOf(Local4), Local5)
	Store(ObjectType(Local5), Local6)
	if (LNotEqual(Local6, c00b)) {
		err(c080, z077, 0x135, 0, 0, Local6, c00b)
	}
	if (LNotEqual(Local5, Buffer() {0xff,0x40,0x41})) {
		err(c080, z077, 0x136, 0, 0, Local5, Buffer() {0xff,0x40,0x41})
	}

	Store(Index(p953, 0), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c009)) {
		err(c080, z077, 0x137, 0, 0, Local2, c009)
	}
	if (LNotEqual(Local1, 0xabcd5018)) {
		err(c080, z077, 0x138, 0, 0, Local1, 0xabcd5018)
	}

	Store(Index(p953, 1), Local0)
	Store(DerefOf(Local0), Local1)
	Store(ObjectType(Local1), Local2)
	if (LNotEqual(Local2, c009)) {
		err(c080, z077, 0x139, 0, 0, Local2, c009)
	}
	if (LNotEqual(Local1, 0xabcd5019)) {
		err(c080, z077, 0x13a, 0, 0, Local1, 0xabcd5019)
	}

	// Not Computational Data

	m1aa(c080, e900, c00f, 0, 0x13b)
	m1aa(c080, mx90, c011, 0, 0x13c)
	m1aa(c080, d900, c00e, 0, 0x13d)
	if (y508) {
		m1aa(c080, tz90, c015, 0, 0x13e)
	}
	m1aa(c080, pr90, c014, 0, 0x13f)
	m1aa(c080, r900, c012, 0, 0x140)
	m1aa(c080, pw90, c013, 0, 0x141)

/*
 *	// Field Unit (Field)
 *
 *	if (LNotEqual(f900, 0xd7)) {
 *		err(c080, z077, 0x137, 0, 0, f900, 0xd7)
 *	}
 *
 *	// Field Unit (IndexField)
 *
 *	if (LNotEqual(if90, 0xd7)) {
 *		err(c080, z077, 0x138, 0, 0, if90, 0xd7)
 *	}
 */
	} /* m000 */


	// T4:x,I1-I14,x,x

	// In-package name strings are String typed, not ObjectReference
	// typed.

	// NameString

	Store(Index(Package(){i900}, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "I900", 788)

	Store(Index(Package(){i901}, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "I901", 789)

	Store(Index(Package(){s900}, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "S900", 790)

	Store(Index(Package(){s901}, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "S901", 791)

	Store(Index(Package(){b900}, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "B900", 792)

	Store(Index(Package(){f900}, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "F900", 793)

	Store(Index(Package(){bn90}, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "BN90", 794)

	Store(Index(Package(){if90}, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "IF90", 795)

	Store(Index(Package(){bf90}, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "BF90", 796)

	Store(Index(Package(){d900}, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "D900", 797)

	Store(Index(Package(){e900}, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "E900", 798)

	Store(Index(Package(){mx90}, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "MX90", 799)

	Store(Index(Package(){r900}, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "R900", 800)

	Store(Index(Package(){pw90}, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "PW90", 801)

	Store(Index(Package(){pr90}, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "PR90", 802)

	Store(Index(Package(){tz90}, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "TZ90", 803)

	Store(Index(Package(){p900}, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "P900", 804)

	Store(Index(Package(){m900}, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "M900", 805)

	// T4:x,IR1-IR14,x,x

	// In-package name strings are String typed, not ObjectReference
	// typed.

	// NameString

	Store(Index(Package(){i900}, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "I900", 945)
	m1a2(Local1, c00a, 0, 0, c00a, "I900", 946)

	Store(Index(Package(){i901}, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "I901", 947)
	m1a2(Local1, c00a, 0, 0, c00a, "I901", 948)

	Store(Index(Package(){s900}, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "S900", 949)
	m1a2(Local1, c00a, 0, 0, c00a, "S900", 950)

	Store(Index(Package(){s901}, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "S901", 951)
	m1a2(Local1, c00a, 0, 0, c00a, "S901", 952)

	Store(Index(Package(){b900}, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "B900", 953)
	m1a2(Local1, c00a, 0, 0, c00a, "B900", 954)

	Store(Index(Package(){f900}, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "F900", 955)
	m1a2(Local1, c00a, 0, 0, c00a, "F900", 956)

	Store(Index(Package(){bn90}, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "BN90", 957)
	m1a2(Local1, c00a, 0, 0, c00a, "BN90", 958)

	Store(Index(Package(){if90}, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "IF90", 959)
	m1a2(Local1, c00a, 0, 0, c00a, "IF90", 960)

	Store(Index(Package(){bf90}, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "BF90", 961)
	m1a2(Local1, c00a, 0, 0, c00a, "BF90", 962)

	Store(Index(Package(){d900}, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "D900", 963)
	m1a2(Local1, c00a, 0, 0, c00a, "D900", 964)

	Store(Index(Package(){e900}, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "E900", 965)
	m1a2(Local1, c00a, 0, 0, c00a, "E900", 966)

	Store(Index(Package(){mx90}, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "MX90", 967)
	m1a2(Local1, c00a, 0, 0, c00a, "MX90", 968)

	Store(Index(Package(){r900}, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "R900", 969)
	m1a2(Local1, c00a, 0, 0, c00a, "R900", 970)

	Store(Index(Package(){pw90}, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "PW90", 971)
	m1a2(Local1, c00a, 0, 0, c00a, "PW90", 972)

	Store(Index(Package(){pr90}, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "PR90", 973)
	m1a2(Local1, c00a, 0, 0, c00a, "PR90", 974)

	Store(Index(Package(){tz90}, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "TZ90", 975)
	m1a2(Local1, c00a, 0, 0, c00a, "TZ90", 976)

	Store(Index(Package(){p900}, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "P900", 977)
	m1a2(Local1, c00a, 0, 0, c00a, "P900", 978)

	Store(Index(Package(){m900}, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "M900", 979)
	m1a2(Local1, c00a, 0, 0, c00a, "M900", 980)

	m000()
	m1a6()
}

Method(m16f, 7)
{
	Store(z077, c081)		// absolute index of file initiating the checking
	Store(1, c089)		// flag of Reference, object otherwise

	if (arg0) {
		m168()
	}
	if (arg1) {
		m169()
	}
	if (arg2) {
		m16a(c083)
	}
	if (arg3) {
		m16b()
	}
	if (arg4) {
		m16c(c083)
	}
	if (arg5) {
		m16d()
	}
	if (arg6) {
		m16e()
	}
}

// Usual mode
Method(m178)
{
	Store(1, c084)	// run verification of references (reading)
	Store(0, c085)	// create the chain of references to LocalX, then dereference them

	Store("Usual mode:", Debug)

	m16f(1, 1, 1, 1, 1, 1, 1)
}

// The mode with the chain of references to LocalX
Method(m179)
{
	Store(1, c084)	// run verification of references (reading)
	Store(1, c085)	// create the chain of references to LocalX, then dereference them

	Store("The mode with the chain of references to LocalX:", Debug)

	m16f(1, 1, 1, 1, 1, 1, 1)
}

// Run-method
Method(REF1)
{
	Store("TEST: REF1, References", Debug)

	Store("REF1", c080)	// name of test
	Store(0, c082)		// flag of test of exceptions
	Store(0, c083)		// run verification of references (write/read)
	Store(0, c086)		// flag, run test till the first error
	Store(1, c087)		// apply DeRefOf to ArgX-ObjectReference

	m178()
	m179()
}
