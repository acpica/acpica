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
 * Source file ns_0010.asl
 *
 * The tests differ those from ns_0010.asl by that the objects are
 * passed to methods as argument (Arg) but not directly by name.
 */

Name(z166, 166)

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
Method(in30,, Serialized)
{
	Name(ts, "in30")
	Name(p000, Package() {0xabcd0000, 0xabcd0001, 0xabcd0002})

	Method(m000, 2)
	{
		Method(m001, 2)
		{
			Store(DerefOf(Index(arg0, 0)), Local0)
			if (LNotEqual(Local0, 0xabcd0000)) {
				err(ts, z166, 0x000, 0, 0, Local0, 0xabcd0000)
			}

			Store(0x11112222, Index(arg0, 0))

			Store(DerefOf(Index(arg0, 0)), Local0)
			if (LNotEqual(Local0, 0x11112222)) {
				err(ts, z166, 0x000, 0, 0, Local0, 0x11112222)
			}
		}
		m001(arg0, arg1)
	}

	m000(p000, RefOf(p000))

	Store(DerefOf(Index(p000, 0)), Local0)
	if (LNotEqual(Local0, 0x11112222)) {
		err(ts, z166, 0x000, 0, 0, Local0, 0x11112222)
	}

	Store(DerefOf(Index(p000, 1)), Local0)
	if (LNotEqual(Local0, 0xabcd0001)) {
		err(ts, z166, 0x000, 0, 0, Local0, 0xabcd0001)
	}
}

/*
 * Package is passed by ArgX to method:
 * - by ORef
 */
Method(in31,, Serialized)
{
	Name(ts, "in31")
	Name(p000, Package() {0xabcd0000, 0xabcd0001, 0xabcd0002})

	Method(m000, 2)
	{
		Method(m001, 2)
		{
			Store(DerefOf(arg1), Local7)

			Store(DerefOf(Index(Local7, 1)), Local0)
			if (LNotEqual(Local0, 0xabcd0001)) {
				err(ts, z166, 0x000, 0, 0, Local0, 0xabcd0001)
			}

			Store(0x33334444, Index(Local7, 1))

			Store(DerefOf(Index(Local7, 1)), Local0)
			if (LNotEqual(Local0, 0x33334444)) {
				err(ts, z166, 0x000, 0, 0, Local0, 0x33334444)
			}
		}
		m001(arg0, arg1)
	}

	m000(p000, RefOf(p000))

	Store(DerefOf(Index(p000, 0)), Local0)
	if (LNotEqual(Local0, 0xabcd0000)) {
		err(ts, z166, 0x000, 0, 0, Local0, 0xabcd0000)
	}

	Store(DerefOf(Index(p000, 1)), Local0)
	if (LNotEqual(Local0, 0xabcd0001)) {
		err(ts, z166, 0x000, 0, 0, Local0, 0xabcd0001)
	}
}

/*
 * Package is passed by ArgX to method:
 * - directly
 * - by ORef
 */
Method(in32,, Serialized)
{
	Name(ts, "in32")
	Name(p000, Package() {0xabcd0000, 0xabcd0001, 0xabcd0002})

	Method(m000, 2)
	{
		Method(m001, 2)
		{
			Store(0x11112222, Index(arg0, 0))

			Store(DerefOf(Index(arg0, 0)), Local0)
			if (LNotEqual(Local0, 0x11112222)) {
				err(ts, z166, 0x000, 0, 0, Local0, 0x11112222)
			}

			Store(DerefOf(arg1), Local7)
			Store(0x33334444, Index(Local7, 1))

			Store(DerefOf(Index(Local7, 1)), Local0)
			if (LNotEqual(Local0, 0x33334444)) {
				err(ts, z166, 0x000, 0, 0, Local0, 0x33334444)
			}
		}
		m001(arg0, arg1)
	}

	m000(p000, RefOf(p000))

	Store(DerefOf(Index(p000, 0)), Local0)
	if (LNotEqual(Local0, 0x11112222)) {
		err(ts, z166, 0x000, 0, 0, Local0, 0x11112222)
	}

	Store(DerefOf(Index(p000, 1)), Local0)
	if (LNotEqual(Local0, 0xabcd0001)) {
		err(ts, z166, 0x000, 0, 0, Local0, 0xabcd0001)
	}
}

/*
 * Package is given directly by name:
 * - do ORef and pass to LocalX
 * - do DerefOf and pass to LocalX
 */
Method(in33,, Serialized)
{
	Name(ts, "in33")
	Name(p000, Package() {0xabcd0000, 0xabcd0001, 0xabcd0002})

	Method(m000, 2)
	{
		Method(m001, 2)
		{
			Store(RefOf(arg0), Local6)
			Store(DerefOf(Local6), Local7)

			Store(DerefOf(Index(Local7, 1)), Local0)
			if (LNotEqual(Local0, 0xabcd0001)) {
				err(ts, z166, 0x000, 0, 0, Local0, 0xabcd0001)
			}

			Store(0x33334444, Index(Local7, 1))

			Store(DerefOf(Index(Local7, 1)), Local0)
			if (LNotEqual(Local0, 0x33334444)) {
				err(ts, z166, 0x000, 0, 0, Local0, 0x33334444)
			}
		}
		m001(arg0, arg1)
	}

	m000(p000, RefOf(p000))

	Store(DerefOf(Index(p000, 0)), Local0)
	if (LNotEqual(Local0, 0xabcd0000)) {
		err(ts, z166, 0x000, 0, 0, Local0, 0xabcd0000)
	}
	Store(DerefOf(Index(p000, 1)), Local0)
	if (LNotEqual(Local0, 0xabcd0001)) {
		err(ts, z166, 0x000, 0, 0, Local0, 0xabcd0001)
	}
	Store(DerefOf(Index(p000, 2)), Local0)
	if (LNotEqual(Local0, 0xabcd0002)) {
		err(ts, z166, 0x000, 0, 0, Local0, 0xabcd0002)
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
 * fail
 *
 * Note:
 *   Named element of Package is simply not implemented by MS,
 *   i000 in Package(){i000} is, on MS, the same as Package(){"i000"}.
 */
Method(in34,, Serialized)
{
	Name(ts, "in34")

	Name(i000, 0xabcd0000)
	Name(ii00, 0x11112222)

	// 0: TRUE ObjectReference
	// 1: NameString -> String
	// 2: TRUE String
	Name(p000, Package() {i000, i000, "i000"})
	Store(RefOf(i000), Index(p000, 0))

	Method(m000, 2)
	{
		Method(m001, 2)
		{
			Store(DerefOf(DerefOf(Index(arg0, 0))), Local0)
			if (LNotEqual(Local0, 0xabcd0000)) {
				err(ts, z166, 0x000, 0, 0, Local0, 0xabcd0000)
			}

			Store(DerefOf(Index(arg0, 1)), Local0)
			if (LEqual(Local0, 0xabcd000)) {
				err(ts, z166, 0x000, 0, 0, Local0, 0xabcd0000)
			}
			if (LNotEqual(Local0, "I000")) {
				err(ts, z166, 0x000, 0, 0, Local0, "I000")
			}

			Store(DerefOf(Index(arg0, 2)), Local0)
			if (LNotEqual(Local0, "i000")) {
				err(ts, z166, 0x000, 0, 0, Local0, "i000")
			}

			Store(RefOf(ii00), Index(arg0, 0))

			Store(DerefOf(DerefOf(Index(arg0, 0))), Local0)
			if (LNotEqual(Local0, 0x11112222)) {
				err(ts, z166, 0x000, 0, 0, Local0, 0x11112222)
			}
		}
		m001(arg0, arg1)
	}

	m000(p000, RefOf(p000))

	Store(DerefOf(DerefOf(Index(p000, 0))), Local0)
	if (LNotEqual(Local0, 0x11112222)) {
		err(ts, z166, 0x000, 0, 0, Local0, 0x11112222)
	}

	Store(DerefOf(Index(p000, 1)), Local0)
	if (LEqual(Local0, 0xabcd0000)) {
		err(ts, z166, 0x000, 0, 0, Local0, 0xabcd0000)
	}
	if (LNotEqual(Local0, "I000")) {
		err(ts, z166, 0x000, 0, 0, Local0, "I000")
	}

	Store(DerefOf(Index(p000, 2)), Local0)
	if (LNotEqual(Local0, "i000")) {
		err(ts, z166, 0x000, 0, 0, Local0, "i000")
	}
}

/*
 * Buffer
 */

Method(in36,, Serialized)
{
	Name(ts, "in36")
	Name(b000, Buffer() {0x10, 0x11, 0x12})

	Method(m000, 2)
	{
		Method(m001, 2)
		{
			// arg0 - b000
			Store(DerefOf(Index(arg0, 0)), Local0)
			if (LNotEqual(Local0, 0x10)) {
				err(ts, z166, 0x000, 0, 0, Local0, 0x10)
			}

			Store(0x67, Index(arg0, 0))

			Store(DerefOf(Index(arg0, 0)), Local0)
			if (LNotEqual(Local0, 0x67)) {
				err(ts, z166, 0x000, 0, 0, Local0, 0x67)
			}

			// arg1 - RefOf(b000)

			Store(DerefOf(arg1), Local7)
			Store(0x55, Index(Local7, 1))

			Store(DerefOf(Index(Local7, 1)), Local0)
			if (LNotEqual(Local0, 0x55)) {
				err(ts, z166, 0x000, 0, 0, Local0, 0x55)
			}
		}
		m001(arg0, arg1)
	}

	m000(b000, RefOf(b000))

	Store(DerefOf(Index(b000, 0)), Local0)
	if (LNotEqual(Local0, 0x67)) {
		err(ts, z166, 0x002, 0, 0, Local0, 0x67)
	}

	Store(DerefOf(Index(b000, 1)), Local0)
	if (LNotEqual(Local0, 0x11)) {
		err(ts, z166, 0x002, 0, 0, Local0, 0x11)
	}

	Store(DerefOf(Index(b000, 2)), Local0)
	if (LNotEqual(Local0, 0x12)) {
		err(ts, z166, 0x002, 0, 0, Local0, 0x12)
	}
}

/*
 * Element of Package instead of i000 (in in02)
 *
 * Recursive call to m001
 */
Method(in37,, Serialized)
{
	Name(ts, "in37")
	Name(i001, 0)
	Name(pp00, Package() {0x11111111, 0x00100000, 0x22223333})

	Method(m000, 1)
	{
		Method(m001, 1)
		{
			/*
			 * Because of the stack overflow issues on MS the number
			 * of repetitions was changed from 100 to 9 here.
			 */
			if (LLess(i001, 9)) {

				Store(DerefOf(Index(arg0, 1)), Local0)
				Increment(Local0)
				Store(Local0, Index(arg0, 1))
				Increment(i001)
				Add(DerefOf(Index(arg0, 1)), m001(arg0), Local0)
				Return (Local0)
			}
			Return (0)
		}
		Store(Add(DerefOf(Index(arg0, 1)), m001(arg0)), Local0)
		Return (Local0)
	}

	Store(m000(pp00), Local0)

	if (LNotEqual(Local0, 0x00a0002d)) {
		err(ts, z166, 0x00a, 0, 0, Local0, 0x00a0002d)
	}

	Store(DerefOf(Index(pp00, 1)), Local0)

	if (LNotEqual(Local0, 0x00100009)) {
		err(ts, z166, 0x00b, 0, 0, Local0, 0x00100009)
	}

	CH03(ts, z166, 0x00c, 0, 0)
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
Method(in38, 1, Serialized)
{
	Name(ts, "in38")
	Name(i001, 0)
	OperationRegion(r000, SystemMemory, 0x100, 0x100)
	Field(r000, ByteAcc, NoLock, Preserve) { f000,32, f001,32 }

	CH03(ts, z166, 0x011, 0, 0)

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
							/*
							 * To exclude stack overflow
							 * >>>>>>>>>>>>>>>>
								Method(m008, 1)
								{
									if (i001)
									{
										Store(0x11223344, arg0)
									}
									Return (0)
								}
								Store(0x80000000, arg0)
								Return (Add(arg0, m008(arg0)))
							 * <<<<<<<<<<<<<<<<
							 */
								Return (0)
							}
							Store(0x07000000, arg0)
							Return (Add(arg0, m007(arg0)))
						}
						Store(0x00600000, arg0)
						Return (Add(arg0, m006(arg0)))
					}
					Store(0x00050000, arg0)
					Return (Add(arg0, m005(arg0)))
				}
				Store(0x00004000, arg0)
				Return (Add(arg0, m004(arg0)))
			}
			Store(0x00000300, arg0)
			Return (Add(arg0, m003(arg0)))
		}
		Store(0x00000020, arg0)
		Return (Add(arg0, m002(arg0)))
	}

	Store(0x00000001, arg0)
	Store(Add(arg0, m001(arg0)), Local0)
	Return (Local0)
	}

	Store(0xabcd9876, f001)

	Store(m000(f001), Local0)

	if (LNotEqual(Local0, 0x07654321)) {
		err(ts, z166, 0x012, 0, 0, Local0, 0x07654321)
	}

	if (arg0) {
		Store(0x11223344, Local1)
	} else {
		Store(0xabcd9876, Local1)
	}

	if (LNotEqual(f001, Local1)) {
		err(ts, z166, 0x013, 0, 0, f001, Local1)
	}

	CH03(ts, z166, 0x014, 0, 0)
}

/*
 * Bank Field instead of i000 (in in01)
 *
 * (is this test correct?)
 */
Method(in39, 1, Serialized)
{
	Name(ts, "in39")
	Name(i001, 0)
	OperationRegion(r000, SystemMemory, 0x100, 0x100)
	Field(r000, ByteAcc, NoLock, Preserve) { f000,32, f001,32 }
	BankField(r000, f001, 0, ByteAcc, NoLock, Preserve) { bnk0, 32 }

	CH03(ts, z166, 0x015, 0, 0)

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
							/*
							 * To exclude stack overflow
							 * >>>>>>>>>>>>>>>>
								Method(m008, 1)
								{
									if (i001)
									{
										Store(0x11223344, arg0)
									}
									Return (0)
								}
								Store(0x80000000, arg0)
								Return (Add(arg0, m008(arg0)))
							 * <<<<<<<<<<<<<<<<
							 */
								Return (0)
							}
							Store(0x07000000, arg0)
							Return (Add(arg0, m007(arg0)))
						}
						Store(0x00600000, arg0)
						Return (Add(arg0, m006(arg0)))
					}
					Store(0x00050000, arg0)
					Return (Add(arg0, m005(arg0)))
				}
				Store(0x00004000, arg0)
				Return (Add(arg0, m004(arg0)))
			}
			Store(0x00000300, arg0)
			Return (Add(arg0, m003(arg0)))
		}
		Store(0x00000020, arg0)
		Return (Add(arg0, m002(arg0)))
	}

	Store(0x00000001, arg0)
	Store(Add(arg0, m001(arg0)), Local0)
	Return (Local0)
	}

	Store(0xaabbccdd, bnk0)
	Store(m000(bnk0), Local0)

	if (LNotEqual(Local0, 0x07654321)) {
		err(ts, z166, 0x016, 0, 0, Local0, 0x07654321)
	}

	if (arg0) {
		Store(0x11223344, Local1)
	} else {
		Store(0xaabbccdd, Local1)
	}

	if (LNotEqual(bnk0, Local1)) {
		err(ts, z166, 0x017, 0, 0, bnk0, Local1)
	}

	CH03(ts, z166, 0x018, 0, 0)
}

/*
 * Index Field instead of i000 (in in01)
 *
 * (is this test correct?)
 */
Method(in3a, 1, Serialized)
{
	Name(ts, "in3a")
	Name(i001, 0)
	OperationRegion(r000, SystemMemory, 0x100, 0x100)
	Field(r000, ByteAcc, NoLock, Preserve) { f000,32, f001,32 }
	IndexField(f000, f001, ByteAcc, NoLock, Preserve) { if00, 32 }

	CH03(ts, z166, 0x019, 0, 0)

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
							/*
							 * To exclude stack overflow
							 * >>>>>>>>>>>>>>>>
								Method(m008, 1)
								{
									if (i001)
									{
										Store(0x11223344, if00)
									}
									Return (0)
								}
								Store(0x80000000, if00)
								Return (Add(if00, m008(if00)))
							 * <<<<<<<<<<<<<<<<
							 */
								Return (0)
							}
							Store(0x07000000, if00)
							Return (Add(if00, m007(if00)))
						}
						Store(0x00600000, if00)
						Return (Add(if00, m006(if00)))
					}
					Store(0x00050000, if00)
					Return (Add(if00, m005(if00)))
				}
				Store(0x00004000, if00)
				Return (Add(if00, m004(if00)))
			}
			Store(0x00000300, if00)
			Return (Add(if00, m003(if00)))
		}
		Store(0x00000020, if00)
		Return (Add(if00, m002(if00)))
	}

	Store(0x00000001, if00)
	Store(Add(if00, m001(if00)), Local0)
	Return (Local0)
	}

	Store(0xabababab, if00)
	Store(m000(if00), Local0)

	/*
	 * The benchmark values for arg0==0 below
	 * are how MS actually works.
	 */

	if (LNotEqual(Local0, 0x07070707)) {
		err(ts, z166, 0x01a, 0, 0, Local0, 0x07070707)
	}

	if (arg0) {
		Store(0x11223344, Local1)
	} else {
		Store(0x07070707, Local1)
	}

	if (LNotEqual(if00, Local1)) {
		err(ts, z166, 0x01b, 0, 0, if00, Local1)
	}

	CH03(ts, z166, 0x01c, 0, 0)
}

/*
 * Element of Buffer instead of i000 (in in01)
 *
 * see in3c below
 *
 * Method(in3b, 1)
 * {
 * }
 */

/*
 * Element of Buffer instead of i000 (in in01)
 *
 * m01b+:
 *   added argument to methods and b000 passed without any use of that
 *   parameter inside the methods
 */
Method(in3c, 1, Serialized)
{
	Name(ts, "in3c")
	Name(i001, 0)
	Name(b000, Buffer() {0x11, 0x01, 0x22})

	CH03(ts, z166, 0x01d, 0, 0)

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
							Store(0x07, Index(arg0, 1))
							Return (Add(DerefOf(Index(arg0, 1)), m007(arg0)))
						}
						Store(0x06, Index(arg0, 1))
						Return (Add(DerefOf(Index(arg0, 1)), m006(arg0)))
					}
					Store(0x05, Index(arg0, 1))
					Return (Add(DerefOf(Index(arg0, 1)), m005(arg0)))
				}
				Store(0x04, Index(arg0, 1))
				Return (Add(DerefOf(Index(arg0, 1)), m004(arg0)))
			}
			Store(0x03, Index(arg0, 1))
			Return (Add(DerefOf(Index(arg0, 1)), m003(arg0)))
		}
		Store(0x02, Index(arg0, 1))
		Return (Add(DerefOf(Index(arg0, 1)), m002(arg0)))
	}
	Store(Add(DerefOf(Index(arg0, 1)), m001(arg0)), Local0)
	Return (Local0)
	}

	Store(m000(b000), Local0)

	if (LNotEqual(Local0, 0x1c)) {
		err(ts, z166, 0x01e, 0, 0, Local0, 0x1c)
	}

	Store(DerefOf(Index(b000, 1)), Local0)

	if (arg0) {
		Store(0xff, Local1)
	} else {
		Store(0x07, Local1)
	}

	if (LNotEqual(Local0, Local1)) {
		err(ts, z166, 0x01f, 0, 0, Local0, Local1)
	}

	CH03(ts, z166, 0x020, 0, 0)
}

/*
 * Element of Package instead of i000 (in in01)
 *
 * see in3e below
 *
 * Method(in3d)
 * {
 * }
 */

/*
 * Element of Package instead of i000 (in in01)
 *
 * m01d+:
 *   added argument to methods and b000 passed without any use of that
 *   parameter inside the methods
 */
Method(in3e,, Serialized)
{
	Name(ts, "in3e")
	Name(i001, 0)
	Name(p000, Package() {1,2,3,4})
	Name(pp00, Package() {0x11111111, 0x00000001, 0x22223333})

	CH03(ts, z166, 0x006, 0, 0)

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
							Store(0x07000000, Index(arg0, 1))
							Return (Add(DerefOf(Index(arg0, 1)), m007(arg0)))
						}
						Store(0x00600000, Index(arg0, 1))
						Return (Add(DerefOf(Index(arg0, 1)), m006(arg0)))
					}
					Store(0x00050000, Index(arg0, 1))
					Return (Add(DerefOf(Index(arg0, 1)), m005(arg0)))
				}
				Store(0x00004000, Index(arg0, 1))
				Return (Add(DerefOf(Index(arg0, 1)), m004(arg0)))
			}
			Store(0x00000300, Index(arg0, 1))
			Return (Add(DerefOf(Index(arg0, 1)), m003(arg0)))
		}
		Store(0x00000020, Index(arg0, 1))
		Return (Add(DerefOf(Index(arg0, 1)), m002(arg0)))
	}
	Store(Add(DerefOf(Index(arg0, 1)), m001(arg0)), Local0)
	Return (Local0)
	}

	Store(m000(pp00), Local0)

	if (LNotEqual(Local0, 0x07654321)) {
		err(ts, z166, 0x007, 0, 0, Local0, 0x07654321)
	}

	Store(DerefOf(Index(pp00, 1)), Local0)

	if (LNotEqual(Local0, 0x07000000)) {
		err(ts, z166, 0x008, 0, 0, Local0, 0x07000000)
	}

	CH03(ts, z166, 0x009, 0, 0)
}

Method(ini3)
{
	SRMT("in30")
	in30()
	SRMT("in31")
	in31()
	SRMT("in32")
	in32()
	SRMT("in33")
	in33()
	SRMT("in34")
	if (chk0) {
		in34()
	} else {
		BLCK()
	}
	SRMT("in36")
	in36()
	SRMT("in37")
	in37()
	SRMT("in38-0")
	in38(0)
	SRMT("in39-0")
	in39(0)
	SRMT("in3a-0")
	in3a(0)
	SRMT("in3c-0")
	in3c(0)
	SRMT("in3e")
	in3e()

	CH03("ini3", z166, 0x000, 0, 0)
}

