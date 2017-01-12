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
 *  Buffer
 *
 * (verify exceptions caused by the imprope use of Buffer type objects)
 */

Name(z095, 95)

Name(b100, Buffer(){0x61})

// Expected exceptions:
//
// 47 - AE_AML_OPERAND_TYPE
// Note: Buffer can be used with Index
Method(m4b3, 1, Serialized)
{
	Name(ts, "m4b3")

	Name(b000, Buffer(){0x62})

	// Local Named Object
	Method(m000, 1, Serialized)
	{
		Name(b000, Buffer(){0x63})

		if (y083) {
			Store (DerefOf(b000), Local1)
			CH06(arg0, 0, 47)
		}

		Store (Index(b000, 0), Local1)
		CH03(ts, z095, 0, 0, 0)
	}

	// Global Named Object
	Method(m001, 1)
	{
		if (y083) {
			Store (DerefOf(b100), Local1)
			CH06(arg0, 1, 47)
		}

		Store (Index(b100, 0), Local1)
		CH03(ts, z095, 1, 0, 0)
	}

	// Argument
	Method(m002, 2)
	{
		Store (DerefOf(arg1), Local1)
		CH06(arg0, 2, 47)

		Release(arg1)
		CH06(arg0, 3, 47)

		Reset(arg1)
		CH06(arg0, 4, 47)

		Signal(arg1)
		CH06(arg0, 5, 47)

		Store(Acquire(arg1, 0), Local1)
		CH06(arg0, 6, 47)

		Store (Index(arg1, 0), Local1)
		CH03(ts, z095, 2, 0, 0)

		Store(Wait(arg1, 0), Local1)
		CH06(arg0, 7, 47)

		Store (Match(arg1, MTR, 0, MTR, 0, 0), Local1)
		CH06(arg0, 8, 47)
	}

	// Local
	Method(m003, 1)
	{
		Store(Buffer(){0x63}, Local0)

		Store (DerefOf(Local0), Local1)
		CH06(arg0, 9, 47)

		Release(Local0)
		CH06(arg0, 10, 47)

		Reset(Local0)
		CH06(arg0, 11, 47)

		Signal(Local0)
		CH06(arg0, 12, 47)

		Store(Acquire(Local0, 0), Local1)
		CH06(arg0, 13, 47)

		Store (Index(Local0, 0), Local1)
		CH03(ts, z095, 3, 0, 0)

		Store(Wait(Local0, 0), Local1)
		CH06(arg0, 14, 47)

		Store (Match(Local0, MTR, 0, MTR, 0, 0), Local1)
		CH06(arg0, 15, 47)
	}

	// An element of Package
	Method(m004, 1, Serialized)
	{
		Name(p000, Package(){Buffer(){0x63}})

		// DeRefOf(Index(Package, Ind, Dest))

		Store (DerefOf(DeRefOf(Index(p000, 0, Local0))), Local1)
		CH06(arg0, 18, 47)

		Store (Index(DeRefOf(Index(p000, 0, Local0)), 0), Local1)
		CH03(ts, z095, 5, 0, 0)

		Store (Match(DeRefOf(Index(p000, 0, Local0)), MTR, 0, MTR, 0, 0), Local1)
		CH06(arg0, 19, 47)
	}

	// Reference to Object
	Method(m005, 2)
	{
		Store(arg0, Debug)
		Store(arg1, Debug)

		Store(ObjectType(arg1), Local0)
		if (LNotEqual(Local0, 3)) {
			err(arg0, z095, 20, 0, 0, Local0, 3)
			return (1)
		}

		Store (DerefOf(arg1), Local1)
		CH03(ts, z095, 6, 0, 0)

		Store (DerefOf(DerefOf(arg1)), Local1)
		CH06(arg0, 21, 47)

		Store (Index(DerefOf(arg1), 0), Local1)
		CH03(ts, z095, 7, 0, 0)

		Store (Match(DerefOf(arg1), MTR, 0, MTR, 0, 0), Local1)
		CH06(arg0, 22, 47)

		return (0)
	}

	// Result of Method invocation
	Method(m006, 1, Serialized)
	{
		Name(i000, 0) // Label to check m000 invocations

		Method(m000, 1)
		{
			Store(arg0, i000)
			Store(Buffer(){0x63}, Local0)
			Return (Local0)
		}

		Method(CH00, 2)
		{
			if (LNotEqual(i000, arg1)) {
				err(arg0, z095, 23, 0, 0, i000, arg1)
			}
		}

		Store (DerefOf(m000(1)), Local1)
		CH06(arg0, 24, 47)
		CH00(arg0, 1)

		Release(m000(2))
		CH06(arg0, 25, 47)
		if (y600) {
			CH00(arg0, 2)
		}

		Reset(m000(3))
		CH06(arg0, 26, 47)
		if (y600) {
			CH00(arg0, 3)
		}

		Signal(m000(4))
		CH06(arg0, 27, 47)
		if (y600) {
			CH00(arg0, 4)
		}

		Store(Acquire(m000(5), 0), Local1)
		CH06(arg0, 28, 47)
		if (y600) {
			CH00(arg0, 5)
		}

		CH03(ts, z095, 12, 0, 0)
		Store (Index(m000(6), 0), Local1)
		if (y900) {
			CH03(ts, z095, 8, 0, 0)
			CH00(arg0, 6)
		} else {
			CH04(ts, 0, 85, z095, 0x123, 0, 0) // AE_INDEX_TO_NOT_ATTACHED
		}

		Store(Wait(m000(7), 0), Local1)
		CH06(arg0, 29, 47)
		if (y600) {
			CH00(arg0, 7)
		}

		Store (Match(m000(8), MTR, 0, MTR, 0, 0), Local1)
		CH06(arg0, 30, 47)
		CH00(arg0, 8)
	}

	// Reference to Object as Result of Method invocation
	Method(m007, 1, Serialized)
	{
		Name(b000, Buffer(){0x63})

		Name(i000, 0) // Label to check m000 invocations

		Method(m000, 2)
		{
			Store(arg0, i000)
			if (LEqual(arg1, 0)) {
				Store(Refof(b100), Local0)
			} elseif (LEqual(arg1, 1)) {
				Store(Refof(b000), Local0)
			}
			Return (Local0)
		}

		Method(CH00, 2)
		{
			if (LNotEqual(i000, arg1)) {
				err(arg0, z095, 31, 0, 0, i000, arg1)
			}
		}

		Name(lpN0, 2)
		Name(lpC0, 0)

		While (lpN0) {
			Multiply(3, lpC0, Local0)

			Store(0, i000)

			Store (DerefOf(m000(1, lpC0)), Local1)
			CH03(ts, z095, Add(9, lpC0), 0, 0)
			CH00(arg0, 1)

			Store (DerefOf(DerefOf(m000(2, lpC0))), Local1)
			CH06(arg0, Add(32, Local0), 47)
			CH00(arg0, 2)

			Store (Index(DerefOf(m000(3, lpC0)), 0), Local1)
			CH06(arg0, Add(33, Local0), 47)
			CH00(arg0, 3)

			Store (Match(DerefOf(m000(4, lpC0)), MTR, 0, MTR, 0, 0), Local1)
			CH06(arg0, Add(34, Local0), 47)
			CH00(arg0, 4)

			Decrement(lpN0)
			Increment(lpC0)
		}
	}

	CH03(ts, z095, 11, 0, 0)

	// Local Named Object
	m000(ts)

	// Global Named Object
	m001(ts)

	// Argument
	m002(ts, Buffer(){0x62})

	// Local
	m003(ts)

	// An element of Package
	m004(ts)


	// Reference to Local Named Object

	m005(Concatenate(ts, "-m005-RefLocName"), RefOf(b000))

	Store(RefOf(b000), Local0)
	m005(Concatenate(ts, "-m005-RefLocName2"), Local0)

	CondRefOf(b000, Local0)
	m005(Concatenate(ts, "-m005-CondRefLocName"), Local0)

	m005(Concatenate(ts, "-m005-RefGlobName"), RefOf(b100))

	Store(RefOf(b100), Local0)
	m005(Concatenate(ts, "-m005-RefGlobName2"), Local0)

	CondRefOf(b100, Local0)
	m005(Concatenate(ts, "-m005-CondRefGlobName"), Local0)


	// Reference to Local

	Store(Buffer(){0x62}, Local0)

	m005(Concatenate(ts, "-m005-RefLocal"), RefOf(Local0))

	Store(RefOf(Local0), Local1)
	m005(Concatenate(ts, "-m005-RefLocal2"), Local1)

	CondRefOf(Local0, Local1)
	m005(Concatenate(ts, "-m005-CondRefLocal"), Local1)


	// Reference to Arg

	m005(Concatenate(ts, "-m005-RefArg"), RefOf(arg0))

	Store(RefOf(arg0), Local0)
	m005(Concatenate(ts, "-m005-RefArg2"), Local0)

	CondRefOf(arg0, Local0)
	m005(Concatenate(ts, "-m005-CondRefArg"), Local0)


	// Index to Package

	Name(p000, Package(){Buffer(){0x62}})

	if (y113) {
		m005(Concatenate(ts, "-m005-Index"), Index(p000, 0))
	}

	Store(Index(p000, 0), Local0)
	m005(Concatenate(ts, "-m005-Index2"), Local0)

	if (y113) {
		m005(Concatenate(ts, "-m005-Index3"), Index(p000, 0, Local0))
	}

	Index(p000, 0, Local0)
	m005(Concatenate(ts, "-m005-Index4"), Local0)

	Store(Index(p000, 0, Local0), Local1)
	m005(Concatenate(ts, "-m005-Index5"), Local1)

	// Result of Method invocation
	m006(ts)

	// Reference to Object as Result of Method invocation
	if (y500) {
		m007(ts)
	}
}
