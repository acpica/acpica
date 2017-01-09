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
 * Bug 258:
 *
 * SUMMARY: Load operator should fail if its Object parameter being a Region
 *          is not in SystemMemory
 */

Name(B258, Buffer() {

		0x53,0x53,0x44,0x54,0x42,0x00,0x00,0x00,  /* 00000000    "SSDTB..." */
		0x02,0x81,0x49,0x6E,0x74,0x65,0x6C,0x00,  /* 00000008    "..Intel." */
		0x4D,0x61,0x6E,0x79,0x00,0x00,0x00,0x00,  /* 00000010    "Many...." */
		0x01,0x00,0x00,0x00,0x49,0x4E,0x54,0x4C,  /* 00000018    "....INTL" */
		0x11,0x10,0x06,0x20,0x5B,0x82,0x1C,0x41,  /* 00000020    "... [..A" */
		0x55,0x58,0x44,0x14,0x16,0x4D,0x30,0x30,  /* 00000028    "UXD..M00" */
		0x30,0x00,0xA4,0x0D,0x5C,0x41,0x55,0x58,  /* 00000030    "0...\AUX" */
		0x44,0x2E,0x4D,0x30,0x30,0x30,0x20,0x28,  /* 00000038    "D.M000 (" */
		0x29,0x00,
})

Name (H258, 0)

OperationRegion (R258, 0x80, 0, 0x42)

Field(R258, ByteAcc, NoLock, Preserve) {
	F258, 0x210,
}

Method(m17e)
{
	Store(B258, F258)

	if (CondRefof(\AUXD, Local0)) {
		err("", zFFF, 0x000, 0, 0, "\\AUXD", 1)
		return
	}

	if (CH03("", 0, 0x001, 0, 0)) {
		return
	}

	Load(R258, H258)

	if (CH04("", 0, 8, 0, 0x002, 0, 0)) { // AE_TYPE
		return
	}

	if (CondRefof(\AUXD, Local0)) {
	} else {
		err("", zFFF, 0x003, 0, 0, "\\AUXD", 0)
		return
	}

	Store (ObjectType(Local0), Local1)

	if (LNotEqual(Local1, 6)) {
		err("", zFFF, 0x004, 0, 0, Local1, 6)
		return
	}

	Store(ObjectType(\AUXD.M000), Local0)
	if (LNotEqual(Local0, 8)) {
		err("", zFFF, 0x005, 0, 0, Local0, 8)
		return
	}

	UnLoad(H258)

	if (CondRefof(\AUXD, Local0)) {
		err("", zFFF, 0x006, 0, 0, "\\AUXD", 1)
	}
}
