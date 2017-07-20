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
 *          (named objects, if present, are the global objects (from DefinitionBlock))
 *
 * TABLE 2: all the legal ways to generate references to the
 *          named objects
 * TABLE 4: all the legal ways to generate references to the
 *          named objects being elements of Package
 *
 * Producing Reference operators:
 *
 *    Index, RefOf, CondRefOf
 */

/*
??????????????
SEE: PUT everywhere APPROPREATE arg6 - number of checking for diagnostics
!!!!!!!!!!!!!!
SEE: add verification of Field Unit (in all files)
SEE: run the tests two times - to check that the data are not corrupted
SEE: uncomment runs after bug fixing
*/


Name(z080, 80)

// ///////////////////////////////////////////////////////////////////////////
//
// TABLE 2: all the legal ways to generate references to the named objects
//
// ///////////////////////////////////////////////////////////////////////////

// m169 but with global data
Method(m190)
{
	if (y100) {
		ts00("m190")
	} else {
		Store("m190", Debug)
	}

	// T2:I2-I4

	if (y114) {
		// Remove this after the bug fixing
		Store(Index(m902, 0), Local0)
		m1a0(Local0, c010, Ones, 0)
	}

	// Computational Data

	Store(Index(s900, 0), Local0)
	m1a2(Local0, c016, 0, 0, c009, 0x31, 1)

	Store(Index(s901, 2), Local0)
	m1a2(Local0, c016, 0, 0, c009, 0x72, 2)

	Store(Index(b900, 3), Local0)
	m1a2(Local0, c016, 0, 0, c009, 0xb3, 3)

	// Elements of Package are Uninitialized

	if (y104) {
		Store(Index(p900, 0), Local0)
		m1a0(Local0, c008, Ones, 4)
	}

	// Elements of Package are Computational Data

	Store(Index(p901, 0), Local0)
	m1a2(Local0, c009, 0, 0, c009, 0xabcd0004, 5)

	Store(Index(p901, 1), Local0)
	m1a2(Local0, c009, 0, 0, c009, 0x1122334455660005, 6)

	Store(Index(p902, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "12340006", 7)

	Store(Index(p902, 1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "q1w2e3r4t5y6u7i80007", 8)

	Store(Index(p903, 0), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "qwrtyuiop0008", 9)

	Store(Index(p903, 1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "1234567890abdef0250009", 10)

	Store(Index(p904, 0), Local0)
	m1a2(Local0, c00b, 0, 0, c00b, Buffer() {0xb5,0xb6,0xb7}, 11)

	Store(Index(p905, 0), Local0)
	m1a2(Local0, c00c, 1, 0, c009, 0xabc000a, 12)

	Store(Index(p905, 0), Local0)
	m1a2(Local0, c00c, 1, 1, c00a, "0xabc000b", 13)

	Store(Index(p906, 0), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "abc000d", 14)

	Store(Index(p907, 0), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "aqwevbgnm000e", 15)

	Store(Index(p908, 0), Local0)
	m1a2(Local0, c00c, 1, 0, c00b, Buffer() {0xba,0xbb,0xbc,0xbd,0xbe}, 16)

	Store(Index(p909, 0), Local0)
	m1a2(Local0, c00c, 2, 0, c009, 0xabc000f, 17)

	Store(Index(p90a, 0), Local0)
	m1a2(Local0, c00c, 2, 0, c00a, "12340010", 18)

	Store(Index(p90b, 0), Local0)
	m1a2(Local0, c00c, 2, 0, c00a, "zxswefas0011", 19)

	Store(Index(p90c, 0), Local0)
	m1a2(Local0, c00c, 2, 0, c00b, Buffer() {0xbf,0xc0,0xc1}, 20)

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
	m1a2(Local0, c00a, 0, 0, c00a, "M900", 37)

	// T2:IR2-IR4

	// Computational Data

	Store(Index(s900, 0, Local1), Local0)
	m1a2(Local0, c016, 0, 0, c009, 0x31, 91)
	m1a2(Local1, c016, 0, 0, c009, 0x31, 92)

	Store(Index(s901, 2, Local1), Local0)
	m1a2(Local0, c016, 0, 0, c009, 0x72, 93)
	m1a2(Local1, c016, 0, 0, c009, 0x72, 94)

	Store(Index(b900, 4, Local1), Local0)
	m1a2(Local0, c016, 0, 0, c009, 0xb4, 95)
	m1a2(Local1, c016, 0, 0, c009, 0xb4, 96)

	// Elements of Package are Uninitialized

	if (y104) {
		Store(Index(p900, 0, Local1), Local0)
		m1a0(Local0, c008, Ones, 97)
		m1a0(Local1, c008, Ones, 98)
	}

	// Elements of Package are Computational Data

	Store(Index(p901, 0, Local1), Local0)
	m1a2(Local0, c009, 0, 0, c009, 0xabcd0004, 99)
	m1a2(Local1, c009, 0, 0, c009, 0xabcd0004, 100)

	Store(Index(p901, 1, Local1), Local0)
	m1a2(Local0, c009, 0, 0, c009, 0x1122334455660005, 101)
	m1a2(Local1, c009, 0, 0, c009, 0x1122334455660005, 102)

	Store(Index(p902, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "12340006", 103)
	m1a2(Local1, c00a, 0, 0, c00a, "12340006", 104)

	Store(Index(p902, 1, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "q1w2e3r4t5y6u7i80007", 105)
	m1a2(Local1, c00a, 0, 0, c00a, "q1w2e3r4t5y6u7i80007", 106)

	Store(Index(p903, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "qwrtyuiop0008", 107)
	m1a2(Local1, c00a, 0, 0, c00a, "qwrtyuiop0008", 108)

	Store(Index(p903, 1, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "1234567890abdef0250009", 109)
	m1a2(Local1, c00a, 0, 0, c00a, "1234567890abdef0250009", 110)

	Store(Index(p904, 0, Local1), Local0)
	m1a2(Local0, c00b, 0, 0, c00b, Buffer() {0xb5,0xb6,0xb7}, 111)
	m1a2(Local1, c00b, 0, 0, c00b, Buffer() {0xb5,0xb6,0xb7}, 112)

	Store(Index(p905, 0, Local1), Local0)
	m1a2(Local0, c00c, 1, 0, c009, 0xabc000a, 113)
	m1a2(Local1, c00c, 1, 0, c009, 0xabc000a, 114)

	Store(Index(p905, 0, Local1), Local0)
	m1a2(Local0, c00c, 1, 1, c00a, "0xabc000b", 115)
	m1a2(Local1, c00c, 1, 1, c00a, "0xabc000b", 116)

	Store(Index(p906, 0, Local1), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "abc000d", 117)
	m1a2(Local1, c00c, 1, 0, c00a, "abc000d", 118)

	Store(Index(p907, 0, Local1), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "aqwevbgnm000e", 119)
	m1a2(Local1, c00c, 1, 0, c00a, "aqwevbgnm000e", 120)

	Store(Index(p908, 0, Local1), Local0)
	m1a2(Local0, c00c, 1, 0, c00b, Buffer() {0xba,0xbb,0xbc,0xbd,0xbe}, 121)
	m1a2(Local1, c00c, 1, 0, c00b, Buffer() {0xba,0xbb,0xbc,0xbd,0xbe}, 122)

	Store(Index(p909, 0, Local1), Local0)
	m1a2(Local0, c00c, 2, 0, c009, 0xabc000f, 123)
	m1a2(Local1, c00c, 2, 0, c009, 0xabc000f, 124)

	Store(Index(p90a, 0, Local1), Local0)
	m1a2(Local0, c00c, 2, 0, c00a, "12340010", 125)
	m1a2(Local1, c00c, 2, 0, c00a, "12340010", 126)

	Store(Index(p90b, 0, Local1), Local0)
	m1a2(Local0, c00c, 2, 0, c00a, "zxswefas0011", 127)
	m1a2(Local1, c00c, 2, 0, c00a, "zxswefas0011", 128)

	Store(Index(p90c, 0, Local1), Local0)
	m1a2(Local0, c00c, 2, 0, c00b, Buffer() {0xbf,0xc0,0xc1}, 129)
	m1a2(Local1, c00c, 2, 0, c00b, Buffer() {0xbf,0xc0,0xc1}, 130)

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

	m1a6()
}

// m16a but with global data
// arg0 - writing mode
Method(m191, 1)
{
	if (y100) {
		ts00("m191")
	} else {
		Store("m191", Debug)
	}

	// T2:R1-R14

	// Computational Data

	Store(RefOf(i900), Local0)
	m1a2(Local0, c009, 0, 0, c009, 0xfe7cb391d65a0000, 271)

	Store(RefOf(i901), Local0)
	m1a2(Local0, c009, 0, 0, c009, 0xc1790001, 272)

	Store(RefOf(s900), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "12340002", 273)

	Store(RefOf(s901), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "qwrtyu0003", 274)

	Store(RefOf(b900), Local0)
	m1a2(Local0, c00b, 0, 0, c00b, Buffer() {0xb0,0xb1,0xb2,0xb3,0xb4}, 275)

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
	m1a2(Local0, c00c, 1, 0, c009, 0xabcd0018, 1001)

	if (arg0) {
		m1ab()
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
	m1a2(Local0, c016, 0, 0, c009, 0xb0, 279)

	// Elements of Package are Uninitialized

	Store(RefOf(p900), Local0)
	m1a0(Local0, c00c, Ones, 287)

	// Elements of Package are Computational Data

	Store(RefOf(p901), Local0)
	m1a2(Local0, c00c, 1, 0, c009, 0xabcd0004, 288)
	m1a2(Local0, c00c, 1, 1, c009, 0x1122334455660005, 289)

	Store(RefOf(p902), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "12340006", 290)
	m1a2(Local0, c00c, 1, 1, c00a, "q1w2e3r4t5y6u7i80007", 291)

	Store(RefOf(p903), Local0)
	m1a2(Local0, c00c, 1, 0, c00a, "qwrtyuiop0008", 292)
	m1a2(Local0, c00c, 1, 1, c00a, "1234567890abdef0250009", 293)

	Store(RefOf(p904), Local0)
	m1a2(Local0, c00c, 1, 0, c00b, Buffer() {0xb5,0xb6,0xb7}, 294)

	Store(RefOf(p905), Local0)
	m1a2(Local0, c00c, 2, 0, c009, 0xabc000a, 295)
	m1a2(Local0, c00c, 2, 1, c00a, "0xabc000b", 296)

	Store(RefOf(p906), Local0)
	m1a2(Local0, c00c, 2, 0, c00a, "abc000d", 297)

	Store(RefOf(p907), Local0)
	m1a2(Local0, c00c, 2, 0, c00a, "aqwevbgnm000e", 298)

	Store(RefOf(p908), Local0)
	m1a2(Local0, c00c, 2, 0, c00b, Buffer() {0xba,0xbb,0xbc,0xbd,0xbe}, 299)

	Store(RefOf(p909), Local0)
	m1a2(Local0, c00c, 3, 0, c009, 0xabc000f, 300)

	Store(RefOf(p90a), Local0)
	m1a2(Local0, c00c, 3, 0, c00a, "12340010", 301)

	Store(RefOf(p90b), Local0)
	m1a2(Local0, c00c, 3, 0, c00a, "zxswefas0011", 302)

	Store(RefOf(p90c), Local0)
	m1a2(Local0, c00c, 3, 0, c00b, Buffer() {0xbf,0xc0,0xc1}, 303)

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

	m1a6()

	return
}

// m16b but with global data
Method(m192)
{
	if (y100) {
		ts00("m192")
	} else {
		Store("m192", Debug)
	}

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

	m1a6()
}

// m16c but with global data
// arg0 - writing mode
Method(m193, 1)
{
	if (y100) {
		ts00("m193")
	} else {
		Store("m193", Debug)
	}

	// T2:CR1-CR14

	// Computational Data

	Store(CondRefOf(i900, Local0), Local1)
	if (m1a4(Local1, 591)) {
		m1a2(Local0, c009, 0, 0, c009, 0xfe7cb391d65a0000, 592)
	}

	Store(CondRefOf(i901, Local0), Local1)
	if (m1a4(Local1, 593)) {
		m1a2(Local0, c009, 0, 0, c009, 0xc1790001, 594)
	}

	Store(CondRefOf(s900, Local0), Local1)
	if (m1a4(Local1, 595)) {
		m1a2(Local0, c00a, 0, 0, c00a, "12340002", 596)
	}

	Store(CondRefOf(s901, Local0), Local1)
	if (m1a4(Local1, 597)) {
		m1a2(Local0, c00a, 0, 0, c00a, "qwrtyu0003", 598)
	}

	Store(CondRefOf(b900, Local0), Local1)
	if (m1a4(Local1, 599)) {
		m1a2(Local0, c00b, 0, 0, c00b, Buffer() {0xb0,0xb1,0xb2,0xb3,0xb4}, 600)
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
		m1a2(Local0, c00c, 1, 0, c009, 0xabcd0018, 1006)
	}

	if (arg0) {
		m1ab()
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
		m1a2(Local0, c016, 0, 0, c009, 0xb0, 608)
	}

	// Elements of Package are Uninitialized

	Store(CondRefOf(p900, Local0), Local1)
	m1a0(Local0, c00c, Local1, 616)

	// Elements of Package are Computational Data

	Store(CondRefOf(p901, Local0), Local1)
	if (m1a4(Local1, 617)) {
		m1a2(Local0, c00c, 1, 0, c009, 0xabcd0004, 618)
		m1a2(Local0, c00c, 1, 1, c009, 0x1122334455660005, 619)
	}

	Store(CondRefOf(p902, Local0), Local1)
	if (m1a4(Local1, 620)) {
		m1a2(Local0, c00c, 1, 0, c00a, "12340006", 621)
		m1a2(Local0, c00c, 1, 1, c00a, "q1w2e3r4t5y6u7i80007", 622)
	}

	Store(CondRefOf(p903, Local0), Local1)
	if (m1a4(Local1, 623)) {
		m1a2(Local0, c00c, 1, 0, c00a, "qwrtyuiop0008", 624)
		m1a2(Local0, c00c, 1, 1, c00a, "1234567890abdef0250009", 625)
	}

	Store(CondRefOf(p904, Local0), Local1)
	if (m1a4(Local1, 626)) {
		m1a2(Local0, c00c, 1, 0, c00b, Buffer() {0xb5,0xb6,0xb7}, 627)
	}

	Store(CondRefOf(p905, Local0), Local1)
	if (m1a4(Local1, 628)) {
		m1a2(Local0, c00c, 2, 0, c009, 0xabc000a, 629)
		m1a2(Local0, c00c, 2, 1, c00a, "0xabc000b", 630)
	}

	Store(CondRefOf(p906, Local0), Local1)
	if (m1a4(Local1, 631)) {
		m1a2(Local0, c00c, 2, 0, c00a, "abc000d", 632)
	}

	Store(CondRefOf(p907, Local0), Local1)
	if (m1a4(Local1, 633)) {
		m1a2(Local0, c00c, 2, 0, c00a, "aqwevbgnm000e", 634)
	}

	Store(CondRefOf(p908, Local0), Local1)
	if (m1a4(Local1, 635)) {
		m1a2(Local0, c00c, 2, 0, c00b, Buffer() {0xba,0xbb,0xbc,0xbd,0xbe}, 636)
	}

	Store(CondRefOf(p909, Local0), Local1)
	if (m1a4(Local1, 637)) {
		m1a2(Local0, c00c, 3, 0, c009, 0xabc000f, 638)
	}

	Store(CondRefOf(p90a, Local0), Local1)
	if (m1a4(Local1, 639)) {
		m1a2(Local0, c00c, 3, 0, c00a, "12340010", 640)
	}

	Store(CondRefOf(p90b, Local0), Local1)
	if (m1a4(Local1, 641)) {
		m1a2(Local0, c00c, 3, 0, c00a, "zxswefas0011", 642)
	}

	Store(CondRefOf(p90c, Local0), Local1)
	if (m1a4(Local1, 643)) {
		m1a2(Local0, c00c, 3, 0, c00b, Buffer() {0xbf,0xc0,0xc1}, 644)
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

	m1a6()

	return
}

// ///////////////////////////////////////////////////////////////////////////
//
// TABLE 4: all the legal ways to generate references to the named objects
//          being elements of Package
//
// ///////////////////////////////////////////////////////////////////////////

// m16e but with global data
Method(m194)
{
	if (y100) {
		ts00("m194")
	} else {
		Store("m194", Debug)
	}

	if (LNot(y900)) {
		Store("Test m194 skipped!", Debug)
		return
	}

	// T4:x,I1-I14,x,x

	// In-package name strings are String typed, not ObjectReference
	// typed.

	// Computational Data

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

	// Not Computational Data

	Store(Index(Package(){e900}, 0), Local0)
	m1a0(Local0, c00a, Ones, 797)

	Store(Index(Package(){mx90}, 0), Local0)
	m1a0(Local0, c00a, Ones, 798)

	Store(Index(Package(){d900}, 0), Local0)
	m1a0(Local0, c00a, Ones, 799)

	Store(Index(Package(){tz90}, 0), Local0)
	m1a0(Local0, c00a, Ones, 800)

	Store(Index(Package(){pr90}, 0), Local0)
	m1a0(Local0, c00a, Ones, 801)

	Store(Index(Package(){r900}, 0), Local0)
	m1a0(Local0, c00a, Ones, 802)

	Store(Index(Package(){pw90}, 0), Local0)
	m1a0(Local0, c00a, Ones, 803)

	// Methods

	Store(Index(Package(){m900}, 0), Local0)
	m1a0(Local0, c00a, Ones, 891)

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

	Store(Index(Package(){m900}, 0, Local1), Local0)
	m1a2(Local0, c00a, 0, 0, c00a, "M900", 977)
	m1a2(Local1, c00a, 0, 0, c00a, "M900", 978)

	m1a6()
}

Method(m195, 5)
{
	Store(z080, c081)		// absolute index of file initiating the checking
	Store(1, c089)		// flag of Reference, object otherwise

/*
 *	Store(0xd7, f900)
 *	Store(0xd8, if90)
 */

	if (arg0) {
		m190()
	}
	if (arg1) {
		m191(c083)
	}
	if (arg2) {
		m192()
	}
	if (arg3) {
		m193(c083)
	}
	if (arg4) {
		m194()
	}
}

// Usual mode
Method(m196)
{
	Store(1, c084)	// run verification of references (reading)
	Store(0, c085)	// create the chain of references to LocalX, then dereference them

	Store("Usual mode:", Debug)

	m195(1, 1, 1, 1, 1)
}

// The mode with the chain of references to LocalX
Method(m197)
{
	Store(1, c084)	// run verification of references (reading)
	Store(1, c085)	// create the chain of references to LocalX, then dereference them

	Store("The mode with the chain of references to LocalX:", Debug)

	m195(1, 1, 1, 1, 1)
}

// Run-method
Method(REF4)
{
	Store("TEST: REF4, References", Debug)

	Store("REF4", c080)	// name of test
	Store(0, c082)		// flag of test of exceptions
	Store(0, c083)		// run verification of references (write/read)
	Store(0, c086)		// flag, run test till the first error
	Store(1, c087)		// apply DeRefOf to ArgX-ObjectReference

	m196()
	m197()
}
