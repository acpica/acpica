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

Name(z179, 179)

/*
 !!!!!!!!!!!!!!!!    It is in progress, just started !!!!!!!!!!!!!!!!
 */

/*
 * Check full path Name declarations performed from inside Methods
 */

Method(fp00,, Serialized)
{
	Name(ts, "fp00")

	Method(m000,, Serialized)
	{
		Name(\i4z0, 0xabcd0000)

		if (LNotEqual(i4z0, 0xabcd0000)) {
			err(ts, z179, 0x000, 0, 0, i4z0, 0xabcd0000)
		}
		if (LNotEqual(\i4z0, 0xabcd0000)) {
			err(ts, z179, 0x001, 0, 0, \i4z0, 0xabcd0000)
		}
		m001()
	}

	Method(m001)
	{
		if (LNotEqual(i4z0, 0xabcd0000)) {
			err(ts, z179, 0x002, 0, 0, i4z0, 0xabcd0000)
		}
		if (LNotEqual(\i4z0, 0xabcd0000)) {
			err(ts, z179, 0x003, 0, 0, \i4z0, 0xabcd0000)
		}
	}

	CH03(ts, z179, 0x044, 0, 0)
	m000()
	CH03(ts, z179, 0x045, 0, 0)
}

Method(fp01,, Serialized)
{
	Name(ts, "fp01")

	Method(m000, 1, Serialized)
	{
		if (LNot(arg0)) {
			Name(\i4z1, 0xabcd0000)
		}

		if (LNotEqual(i4z1, 0xabcd0000)) {
			err(ts, z179, 0x000, 0, 0, i4z1, 0xabcd0000)
		}
		if (LNotEqual(\i4z1, 0xabcd0000)) {
			err(ts, z179, 0x001, 0, 0, \i4z1, 0xabcd0000)
		}
		m001()
	}

	Method(m001)
	{
		if (LNotEqual(i4z1, 0xabcd0000)) {
			err(ts, z179, 0x002, 0, 0, i4z1, 0xabcd0000)
		}
		if (LNotEqual(\i4z1, 0xabcd0000)) {
			err(ts, z179, 0x003, 0, 0, \i4z1, 0xabcd0000)
		}
	}

	CH03(ts, z179, 0x044, 0, 0)
	m000(0)
	CH03(ts, z179, 0x045, 0, 0)
}


Method(fpd0)
{
	SRMT("fp00")
	fp00()

	SRMT("fp01")
	fp01()
}

