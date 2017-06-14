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
 * Tests originated from namespace/ns1
 */

/*
 * Package/Buffer/String/Field/IndexField/BankField/BufferField
 *
 * Tests below are here
 * as specific type arguments passing -
 * arguments though passed directly to method, not as references,
 * nevertheless allow access to the elements of original objects.
 */

Name(z164, 164)

/*
 *
 * Read/write access to elemens of Package passed to method.
 *
 */

/*
 *
 * Elements of Package are constant Integer (0xabcd0000)
 *
 */

/*
 * Package is passed by ArgX to method:
 * - directly
 */
Method(in10,, Serialized)
{
	Name(ts, "in10")
	Name(p000, Package() {0xabcd0000, 0xabcd0001, 0xabcd0002})
	Method(m001, 2)
	{
		Store(DerefOf(Index(arg0, 0)), Local0)
		if (LNotEqual(Local0, 0xabcd0000)) {
			err(ts, z164, 0x000, 0, 0, Local0, 0xabcd0000)
		}

		Store(0x11112222, Index(arg0, 0))

		Store(DerefOf(Index(arg0, 0)), Local0)
		if (LNotEqual(Local0, 0x11112222)) {
			err(ts, z164, 0x000, 0, 0, Local0, 0x11112222)
		}
	}

	m001(p000, RefOf(p000))

	Store(DerefOf(Index(p000, 0)), Local0)
	if (LNotEqual(Local0, 0x11112222)) {
		err(ts, z164, 0x000, 0, 0, Local0, 0x11112222)
	}

	Store(DerefOf(Index(p000, 1)), Local0)
	if (LNotEqual(Local0, 0xabcd0001)) {
		err(ts, z164, 0x000, 0, 0, Local0, 0xabcd0001)
	}
}

/*
 * Package is passed by ArgX to method:
 * - by ORef
 */
Method(in11,, Serialized)
{
	Name(ts, "in11")
	Name(p000, Package() {0xabcd0000, 0xabcd0001, 0xabcd0002})
	Method(m001, 2)
	{
		Store(DerefOf(arg1), Local7)

		Store(DerefOf(Index(Local7, 1)), Local0)
		if (LNotEqual(Local0, 0xabcd0001)) {
			err(ts, z164, 0x000, 0, 0, Local0, 0xabcd0001)
		}

		Store(0x33334444, Index(Local7, 1))

		Store(DerefOf(Index(Local7, 1)), Local0)
		if (LNotEqual(Local0, 0x33334444)) {
			err(ts, z164, 0x000, 0, 0, Local0, 0x33334444)
		}
	}

	m001(p000, RefOf(p000))

	Store(DerefOf(Index(p000, 0)), Local0)
	if (LNotEqual(Local0, 0xabcd0000)) {
		err(ts, z164, 0x000, 0, 0, Local0, 0xabcd0000)
	}

	Store(DerefOf(Index(p000, 1)), Local0)
	if (LNotEqual(Local0, 0xabcd0001)) {
		err(ts, z164, 0x000, 0, 0, Local0, 0xabcd0001)
	}
}

/*
 * Package is passed by ArgX to method:
 * - directly
 * - by ORef
 */
Method(in12,, Serialized)
{
	Name(ts, "in12")
	Name(p000, Package() {0xabcd0000, 0xabcd0001, 0xabcd0002})
	Method(m001, 2)
	{
		Store(0x11112222, Index(arg0, 0))

		Store(DerefOf(Index(arg0, 0)), Local0)
		if (LNotEqual(Local0, 0x11112222)) {
			err(ts, z164, 0x000, 0, 0, Local0, 0x11112222)
		}

		Store(DerefOf(arg1), Local7)
		Store(0x33334444, Index(Local7, 1))

		Store(DerefOf(Index(Local7, 1)), Local0)
		if (LNotEqual(Local0, 0x33334444)) {
			err(ts, z164, 0x000, 0, 0, Local0, 0x33334444)
		}
	}

	m001(p000, RefOf(p000))

	Store(DerefOf(Index(p000, 0)), Local0)
	if (LNotEqual(Local0, 0x11112222)) {
		err(ts, z164, 0x000, 0, 0, Local0, 0x11112222)
	}

	Store(DerefOf(Index(p000, 1)), Local0)
	if (LNotEqual(Local0, 0xabcd0001)) {
		err(ts, z164, 0x000, 0, 0, Local0, 0xabcd0001)
	}
}

/*
 * Package is given directly by name:
 * - do ORef and pass to LocalX
 * - do DerefOf and pass to LocalX
 */
Method(in13,, Serialized)
{
	Name(ts, "in13")
	Name(p000, Package() {0xabcd0000, 0xabcd0001, 0xabcd0002})
	Method(m001, 2)
	{
		Store(RefOf(p000), Local6)
		Store(DerefOf(Local6), Local7)

		Store(DerefOf(Index(Local7, 1)), Local0)
		if (LNotEqual(Local0, 0xabcd0001)) {
			err(ts, z164, 0x000, 0, 0, Local0, 0xabcd0001)
		}

		Store(0x33334444, Index(Local7, 1))

		Store(DerefOf(Index(Local7, 1)), Local0)
		if (LNotEqual(Local0, 0x33334444)) {
			err(ts, z164, 0x000, 0, 0, Local0, 0x33334444)
		}
	}

	m001(p000, RefOf(p000))

	Store(DerefOf(Index(p000, 0)), Local0)
	if (LNotEqual(Local0, 0xabcd0000)) {
		err(ts, z164, 0x000, 0, 0, Local0, 0xabcd0000)
	}
	Store(DerefOf(Index(p000, 1)), Local0)
	if (LNotEqual(Local0, 0xabcd0001)) {
		err(ts, z164, 0x000, 0, 0, Local0, 0xabcd0001)
	}
	Store(DerefOf(Index(p000, 2)), Local0)
	if (LNotEqual(Local0, 0xabcd0002)) {
		err(ts, z164, 0x000, 0, 0, Local0, 0xabcd0002)
	}
}

/*
 *
 * Elements of Package are Named Integer (i000)
 *
 */

/*
 * Package is passed by ArgX to method
 *
 * Note:
 *   Named element of Package is simply not implemented by MS,
 *   i000 in Package(){i000} is, on MS, the same as Package(){"i000"}.
 */
Method(in14,, Serialized)
{
	Name(ts, "in14")

	Name(i000, 0xabcd0000)
	Name(ii00, 0x11112222)

	// 0: TRUE ObjectReference
	// 1: NameString -> String
	// 2: TRUE String
	Name(p000, Package() {i000, i000, "i000"})
	Store(RefOf(i000), Index(p000, 0))

	Method(m001, 2)
	{
		Store(DerefOf(DerefOf(Index(arg0, 0))), Local0)
		if (LNotEqual(Local0, 0xabcd0000)) {
			err(ts, z164, 0x000, 0, 0, Local0, 0xabcd0000)
		}

		Store(DerefOf(Index(arg0, 1)), Local0)
		if (LEqual(Local0, 0xabcd0000)) {
			err(ts, z164, 0x000, 0, 0, Local0, 0xabcd0000)
		}
		if (LNotEqual(Local0, "I000")) {
			err(ts, z164, 0x000, 0, 0, Local0, "I000")
		}

		Store(DerefOf(Index(arg0, 2)), Local0)
		if (LNotEqual(Local0, "i000")) {
			err(ts, z164, 0x000, 0, 0, Local0, "i000")
		}

		Store(RefOf(ii00), Index(arg0, 0))

		Store(DerefOf(DerefOf(Index(arg0, 0))), Local0)
		if (LNotEqual(Local0, 0x11112222)) {
			err(ts, z164, 0x000, 0, 0, Local0, 0x11112222)
		}
	}

	m001(p000, RefOf(p000))

	Store(DerefOf(DerefOf(Index(p000, 0))), Local0)
	if (LNotEqual(Local0, 0x11112222)) {
		err(ts, z164, 0x000, 0, 0, Local0, 0x11112222)
	}

	Store(DerefOf(Index(p000, 1)), Local0)
	if (LEqual(Local0, 0xabcd0000)) {
		err(ts, z164, 0x000, 0, 0, Local0, 0xabcd0000)
	}
	if (LNotEqual(Local0, "I000")) {
		err(ts, z164, 0x000, 0, 0, Local0, "I000")
	}

	Store(DerefOf(Index(p000, 2)), Local0)
	if (LNotEqual(Local0, "i000")) {
		err(ts, z164, 0x000, 0, 0, Local0, "i000")
	}
}

/*
 * Package is used directly by Name
 *
 * Example to show behaviour of MS for Package(){i000}
 *
 * Note:
 *   Named element of Package is simply not implemented by MS,
 *   i000 in Package(){i000} is, on MS, the same as Package(){"i000"}.
 */
Method(in15,, Serialized)
{
	Name(ts, "in15")
	Name(i000, 0xabcd0000)
	Name(i001, 0xabcd0001)
	Name(i002, 0xabcd0002)

	Name(ii00, 0x11112222)

	Name(p000, Package() {i000, i001, i002, "i000"})

	Store(DerefOf(Index(p000, 0)), Local0)
	OUTP(Local0)
	Store(DerefOf(Index(p000, 1)), Local0)
	OUTP(Local0)
	Store(DerefOf(Index(p000, 2)), Local0)
	OUTP(Local0)
	Store(DerefOf(Index(p000, 3)), Local0)
	OUTP(Local0)

	Store(ii00, Index(p000, 1))

	OUTP("After re-write 1-th element:")

	Store(DerefOf(Index(p000, 0)), Local0)
	OUTP(Local0)
	Store(DerefOf(Index(p000, 1)), Local0)
	OUTP(Local0)
	Store(DerefOf(Index(p000, 2)), Local0)
	OUTP(Local0)
	Store(DerefOf(Index(p000, 3)), Local0)
	OUTP(Local0)
}

/*
 * Buffer
 */

Method(in16,, Serialized)
{
	Name(ts, "in16")
	Name(b000, Buffer() {0x10, 0x11, 0x12})
	Method(m001, 2)
	{
		// arg0 - b000
		Store(DerefOf(Index(arg0, 0)), Local0)
		if (LNotEqual(Local0, 0x10)) {
			err(ts, z164, 0x000, 0, 0, Local0, 0x10)
		}

		Store(0x67, Index(arg0, 0))

		Store(DerefOf(Index(arg0, 0)), Local0)
		if (LNotEqual(Local0, 0x67)) {
			err(ts, z164, 0x000, 0, 0, Local0, 0x67)
		}

		// arg1 - RefOf(b000)

		Store(DerefOf(arg1), Local7)
		Store(0x55, Index(Local7, 1))

		Store(DerefOf(Index(Local7, 1)), Local0)
		if (LNotEqual(Local0, 0x55)) {
			err(ts, z164, 0x000, 0, 0, Local0, 0x55)
		}
	}

	m001(b000, RefOf(b000))

	Store(DerefOf(Index(b000, 0)), Local0)
	if (LNotEqual(Local0, 0x67)) {
		err(ts, z164, 0x002, 0, 0, Local0, 0x67)
	}

	Store(DerefOf(Index(b000, 1)), Local0)
	if (LNotEqual(Local0, 0x11)) {
		err(ts, z164, 0x002, 0, 0, Local0, 0x11)
	}

	Store(DerefOf(Index(b000, 2)), Local0)
	if (LNotEqual(Local0, 0x12)) {
		err(ts, z164, 0x002, 0, 0, Local0, 0x12)
	}
}

/*
 * Element of Package instead of i000 (in in02)
 *
 * Recursive call to m001
 */
Method(in17,, Serialized)
{
	Name(ts, "in17")
	Name(i001, 0)
	Name(pp00, Package() {0x11111111, 0x00100000, 0x22223333})

	Method(m001)
	{
		/*
		 * Because of the stack overflow issues on MS the number
		 * of repetitions was changed from 100 to 11 here.
		 */
		if (LLess(i001, 11)) {

			Store(DerefOf(Index(pp00, 1)), Local0)
			Increment(Local0)
			Store(Local0, Index(pp00, 1))
			Increment(i001)
			Add(DerefOf(Index(pp00, 1)), m001(), Local0)
			Return (Local0)
		}
		Return (0)
	}
	Store(Add(DerefOf(Index(pp00, 1)), m001()), Local0)

	if (LNotEqual(Local0, 0x00c00042)) {
		err(ts, z164, 0x00a, 0, 0, Local0, 0x00c00042)
	}

	Store(DerefOf(Index(pp00, 1)), Local0)

	if (LNotEqual(Local0, 0x0010000b)) {
		err(ts, z164, 0x00b, 0, 0, Local0, 0x0010000b)
	}

	CH03(ts, z164, 0x00c, 0, 0)
}

/*
 * Buffer Field instead of i000 (in in01)
 *
 * fail
 *
 * Note: Buffer Field in expressions is not supported by MS,
 *       see msfail.asl
 */

/*
 * Field instead of i000 (in in01)
 */
Method(in18, 1, Serialized)
{
	Name(ts, "in18")
	Name(i001, 0)
	OperationRegion(r000, SystemMemory, 0x100, 0x100)
	Field(r000, ByteAcc, NoLock, Preserve) { f000,32, f001,32 }

	CH03(ts, z164, 0x011, 0, 0)

	Store(arg0, i001)

	Method(m001)
	{
		Method(m002)
		{
			Method(m003)
			{
				Method(m004)
				{
					Method(m005)
					{
						Method(m006)
						{
							Method(m007)
							{
								Method(m008)
								{
									if (i001)
									{
										Store(0x11223344, f001)
									}
									Return (0)
								}
								Store(0x80000000, f001)
								Return (Add(f001, m008()))
							}
							Store(0x07000000, f001)
							Return (Add(f001, m007()))
						}
						Store(0x00600000, f001)
						Return (Add(f001, m006()))
					}
					Store(0x00050000, f001)
					Return (Add(f001, m005()))
				}
				Store(0x00004000, f001)
				Return (Add(f001, m004()))
			}
			Store(0x00000300, f001)
			Return (Add(f001, m003()))
		}
		Store(0x00000020, f001)
		Return (Add(f001, m002()))
	}

	Store(0x00000001, f001)

	Store(Add(f001, m001()), Local0)

	if (LNotEqual(Local0, 0x87654321)) {
		err(ts, z164, 0x012, 0, 0, Local0, 0x87654321)
	}

	if (arg0) {
		Store(0x11223344, Local1)
	} else {
		Store(0x80000000, Local1)
	}

	if (LNotEqual(f001, Local1)) {
		err(ts, z164, 0x013, 0, 0, f001, Local1)
	}

	CH03(ts, z164, 0x014, 0, 0)
}

/*
 * Bank Field instead of i000 (in in01)
 *
 * (is this test correct?)
 */
Method(in19, 1, Serialized)
{
	Name(ts, "in19")
	Name(i001, 0)
	OperationRegion(r000, SystemMemory, 0x100, 0x100)
	Field(r000, ByteAcc, NoLock, Preserve) { f000,32, f001,32 }
	BankField(r000, f001, 0, ByteAcc, NoLock, Preserve) { bnk0, 32 }

	CH03(ts, z164, 0x015, 0, 0)

	Store(arg0, i001)

	Method(m001)
	{
		Method(m002)
		{
			Method(m003)
			{
				Method(m004)
				{
					Method(m005)
					{
						Method(m006)
						{
							Method(m007)
							{
								Method(m008)
								{
									if (i001)
									{
										Store(0x11223344, bnk0)
									}
									Return (0)
								}
								Store(0x80000000, bnk0)
								Return (Add(bnk0, m008()))
							}
							Store(0x07000000, bnk0)
							Return (Add(bnk0, m007()))
						}
						Store(0x00600000, bnk0)
						Return (Add(bnk0, m006()))
					}
					Store(0x00050000, bnk0)
					Return (Add(bnk0, m005()))
				}
				Store(0x00004000, bnk0)
				Return (Add(bnk0, m004()))
			}
			Store(0x00000300, bnk0)
			Return (Add(bnk0, m003()))
		}
		Store(0x00000020, bnk0)
		Return (Add(bnk0, m002()))
	}

	Store(0x00000001, bnk0)

	Store(Add(bnk0, m001()), Local0)

	if (LNotEqual(Local0, 0x87654321)) {
		err(ts, z164, 0x016, 0, 0, Local0, 0x87654321)
	}

	if (arg0) {
		Store(0x11223344, Local1)
	} else {
		Store(0x80000000, Local1)
	}

	if (LNotEqual(bnk0, Local1)) {
		err(ts, z164, 0x017, 0, 0, bnk0, Local1)
	}

	CH03(ts, z164, 0x018, 0, 0)
}

/*
 * Index Field instead of i000 (in in01)
 *
 * (is this test correct?)
 */
Method(in1a, 1, Serialized)
{
	Name(ts, "in1a")
	Name(i001, 0)
	OperationRegion(r000, SystemMemory, 0x100, 0x100)
	Field(r000, ByteAcc, NoLock, Preserve) { f000,32, f001,32 }
	IndexField(f000, f001, ByteAcc, NoLock, Preserve) { if00, 32 }

	CH03(ts, z164, 0x019, 0, 0)

	Store(arg0, i001)

	Method(m001)
	{
		Method(m002)
		{
			Method(m003)
			{
				Method(m004)
				{
					Method(m005)
					{
						Method(m006)
						{
							Method(m007)
							{
								Method(m008)
								{
									if (i001)
									{
										Store(0x11223344, if00)
									}
									Return (0)
								}
								Store(0x80000000, if00)
								Return (Add(if00, m008()))
							}
							Store(0x07000000, if00)
							Return (Add(if00, m007()))
						}
						Store(0x00600000, if00)
						Return (Add(if00, m006()))
					}
					Store(0x00050000, if00)
					Return (Add(if00, m005()))
				}
				Store(0x00004000, if00)
				Return (Add(if00, m004()))
			}
			Store(0x00000300, if00)
			Return (Add(if00, m003()))
		}
		Store(0x00000020, if00)
		Return (Add(if00, m002()))
	}

	Store(0x00000001, if00)

	Store(Add(if00, m001()), Local0)

	/*
	 * The benchmark values for arg0==0 below
	 * are how MS actually works.
	 */

	if (LNotEqual(Local0, 0x87878787)) {
		err(ts, z164, 0x01a, 0, 0, Local0, 0x87878787)
	}

	if (arg0) {
		Store(0x11223344, Local1)
	} else {
		Store(0x80808080, Local1)
	}

	if (LNotEqual(if00, Local1)) {
		err(ts, z164, 0x01b, 0, 0, if00, Local1)
	}

	CH03(ts, z164, 0x01c, 0, 0)
}

/*
 * Element of Buffer instead of i000 (in in01)
 */
Method(in1b, 1, Serialized)
{
	Name(ts, "in1b")
	Name(i001, 0)
	Name(b000, Buffer() {0x11, 0x01, 0x22})

	CH03(ts, z164, 0x01d, 0, 0)

	Store(arg0, i001)

	Method(m001)
	{
		Method(m002)
		{
			Method(m003)
			{
				Method(m004)
				{
					Method(m005)
					{
						Method(m006)
						{
							Method(m007)
							{
								Return (0)
							}
							Store(0x07, Index(b000, 1))
							Return (Add(DerefOf(Index(b000, 1)), m007()))
						}
						Store(0x06, Index(b000, 1))
						Return (Add(DerefOf(Index(b000, 1)), m006()))
					}
					Store(0x05, Index(b000, 1))
					Return (Add(DerefOf(Index(b000, 1)), m005()))
				}
				Store(0x04, Index(b000, 1))
				Return (Add(DerefOf(Index(b000, 1)), m004()))
			}
			Store(0x03, Index(b000, 1))
			Return (Add(DerefOf(Index(b000, 1)), m003()))
		}
		Store(0x02, Index(b000, 1))
		Return (Add(DerefOf(Index(b000, 1)), m002()))
	}
	Store(Add(DerefOf(Index(b000, 1)), m001()), Local0)

	if (LNotEqual(Local0, 0x1c)) {
		err(ts, z164, 0x01e, 0, 0, Local0, 0x1c)
	}

	Store(DerefOf(Index(b000, 1)), Local0)

	if (arg0) {
		Store(0xff, Local1)
	} else {
		Store(0x07, Local1)
	}

	if (LNotEqual(Local0, Local1)) {
		err(ts, z164, 0x01f, 0, 0, Local0, Local1)
	}

	CH03(ts, z164, 0x020, 0, 0)
}

/*
 * Element of Buffer instead of i000 (in in01)
 *
 * in1b+:
 *   added argument to methods and b000 passed without any use of that
 *   parameter inside the methods
 */
Method(in1c, 1, Serialized)
{
	Name(ts, "in1c")
	Name(i001, 0)
	Name(b000, Buffer() {0x11, 0x01, 0x22})

	CH03(ts, z164, 0x01d, 0, 0)

	Store(arg0, i001)

	Method(m000, 1)
	{

	Method(m001, 1)
	{
		Method(m002, 1)
		{
			Method(m003, 1)
			{
				Method(m004, 1)
				{
					Method(m005, 1)
					{
						Method(m006, 1)
						{
							Method(m007, 1)
							{
								Return (0)
							}
							Store(0x07, Index(b000, 1))
							Return (Add(DerefOf(Index(b000, 1)), m007(b000)))
						}
						Store(0x06, Index(b000, 1))
						Return (Add(DerefOf(Index(b000, 1)), m006(b000)))
					}
					Store(0x05, Index(b000, 1))
					Return (Add(DerefOf(Index(b000, 1)), m005(b000)))
				}
				Store(0x04, Index(b000, 1))
				Return (Add(DerefOf(Index(b000, 1)), m004(b000)))
			}
			Store(0x03, Index(b000, 1))
			Return (Add(DerefOf(Index(b000, 1)), m003(b000)))
		}
		Store(0x02, Index(b000, 1))
		Return (Add(DerefOf(Index(b000, 1)), m002(b000)))
	}
	Store(Add(DerefOf(Index(b000, 1)), m001(b000)), Local0)
	Return (Local0)
	}

	CH03(ts, z164, 0x000, 0, 0)

	Store(m000(b000), Local0)

	if (LNotEqual(Local0, 0x1c)) {
		err(ts, z164, 0x01e, 0, 0, Local0, 0x1c)
	}

	Store(DerefOf(Index(b000, 1)), Local0)

	if (arg0) {
		Store(0xff, Local1)
	} else {
		Store(0x07, Local1)
	}

	if (LNotEqual(Local0, Local1)) {
		err(ts, z164, 0x01f, 0, 0, Local0, Local1)
	}

	CH03(ts, z164, 0x020, 0, 0)
}


/*
 * Element of Package instead of i000 (in in01)
 */
Method(in1d,, Serialized)
{
	Name(ts, "in1d")
	Name(i001, 0)
	Name(p000, Package() {1,2,3,4})
	Name(pp00, Package() {0x11111111, 0x00000001, 0x22223333})

	CH03(ts, z164, 0x006, 0, 0)

	Method(m001)
	{
		Method(m002)
		{
			Method(m003)
			{
				Method(m004)
				{
					Method(m005)
					{
						Method(m006)
						{
							Method(m007)
							{
								Return (0)
							}
							Store(0x07000000, Index(pp00, 1))
							Return (Add(DerefOf(Index(pp00, 1)), m007()))
						}
						Store(0x00600000, Index(pp00, 1))
						Return (Add(DerefOf(Index(pp00, 1)), m006()))
					}
					Store(0x00050000, Index(pp00, 1))
					Return (Add(DerefOf(Index(pp00, 1)), m005()))
				}
				Store(0x00004000, Index(pp00, 1))
				Return (Add(DerefOf(Index(pp00, 1)), m004()))
			}
			Store(0x00000300, Index(pp00, 1))
			Return (Add(DerefOf(Index(pp00, 1)), m003()))
		}
		Store(0x00000020, Index(pp00, 1))
		Return (Add(DerefOf(Index(pp00, 1)), m002()))
	}
	Store(Add(DerefOf(Index(pp00, 1)), m001()), Local0)

	if (LNotEqual(Local0, 0x07654321)) {
		err(ts, z164, 0x007, 0, 0, Local0, 0x07654321)
	}

	Store(DerefOf(Index(pp00, 1)), Local0)

	if (LNotEqual(Local0, 0x07000000)) {
		err(ts, z164, 0x008, 0, 0, Local0, 0x07000000)
	}

	CH03(ts, z164, 0x009, 0, 0)
}

/*
 * Element of Package instead of i000 (in in01)
 *
 * in1d+:
 *   added argument to methods and b000 passed without any use of that
 *   parameter inside the methods
 */
Method(in1e,, Serialized)
{
	Name(ts, "in1e")
	Name(i001, 0)
	Name(p000, Package() {1,2,3,4})
	Name(pp00, Package() {0x11111111, 0x00000001, 0x22223333})

	CH03(ts, z164, 0x006, 0, 0)

	Method(m000, 1)
	{

	Method(m001, 1)
	{
		Method(m002, 1)
		{
			Method(m003, 1)
			{
				Method(m004, 1)
				{
					Method(m005, 1)
					{
						Method(m006, 1)
						{
							Method(m007, 1)
							{
								Return (0)
							}
							Store(0x07000000, Index(pp00, 1))
							Return (Add(DerefOf(Index(pp00, 1)), m007(pp00)))
						}
						Store(0x00600000, Index(pp00, 1))
						Return (Add(DerefOf(Index(pp00, 1)), m006(pp00)))
					}
					Store(0x00050000, Index(pp00, 1))
					Return (Add(DerefOf(Index(pp00, 1)), m005(pp00)))
				}
				Store(0x00004000, Index(pp00, 1))
				Return (Add(DerefOf(Index(pp00, 1)), m004(pp00)))
			}
			Store(0x00000300, Index(pp00, 1))
			Return (Add(DerefOf(Index(pp00, 1)), m003(pp00)))
		}
		Store(0x00000020, Index(pp00, 1))
		Return (Add(DerefOf(Index(pp00, 1)), m002(pp00)))
	}
	Store(Add(DerefOf(Index(pp00, 1)), m001(pp00)), Local0)
	Return (Local0)
	}

	CH03(ts, z164, 0x000, 0, 0)

	Store(m000(pp00), Local0)

	if (LNotEqual(Local0, 0x07654321)) {
		err(ts, z164, 0x007, 0, 0, Local0, 0x07654321)
	}

	Store(DerefOf(Index(pp00, 1)), Local0)

	if (LNotEqual(Local0, 0x07000000)) {
		err(ts, z164, 0x008, 0, 0, Local0, 0x07000000)
	}

	CH03(ts, z164, 0x009, 0, 0)
}

Method(ini1)
{
	SRMT("in10")
	in10()
	SRMT("in11")
	in11()
	SRMT("in12")
	in12()
	SRMT("in13")
	in13()
	SRMT("in14")
	if (chk0) {
		in14()
	} else {
		BLCK()
	}
	SRMT("in15")
	if (chk0) {
		in15()
	} else {
		BLCK()
	}
	SRMT("in16")
	in16()
	SRMT("in17")
	in17()
	SRMT("in18-0")
	in18(0)
	SRMT("in19-0")
	in19(0)
	SRMT("in1a-0")
	in1a(0)
	SRMT("in1b-0")
	in1b(0)
	SRMT("in1c-0")
	if (y275) {
		in1c(0)
	} else {
		BLCK()
	}
	SRMT("in1d")
	in1d()
	SRMT("in1e")
	if (LAnd(fix0, y275)) {
		in1e()
	} else {
		BLCK()
	}

	CH03("ini1", z164, 0x000, 0, 0)
}

