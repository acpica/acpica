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
 * Bug 244:
 *
 * SUMMARY: Acquire/Release in a global level AML code is not valid,
 * removed from test suite.
 */

	//Mutex(T804, 8)
	//Mutex(T805, 8)
	//Mutex(T806, 8)
	//Mutex(T807, 8)

	/*
	 * These declarations are used for to check the Acquire
	 * and Release operations in a global level AML code.
	 */
	//Name(i101, 0) // non-zero means that this test was run
	//Name(i104, 1)
	//Name(i105, 1)
	//Name(i106, 1)
	//Name(i107, 1)

	/*
	Method(m137)
	{
		Store(1, i101)

		Store("m137 started", Debug)

		if (LNot(i104)) {
			Release(T804)
		}

		Store("m137 completed", Debug)

		return (1)
	}

	Method(m13e)
	{
		Store(1, i101)

		Store("m13e started", Debug)

		Store(Acquire(T805, 0xffff), i105)

		Store("m13e completed", Debug)

		return (1)
	}

	Method(m13f)
	{
		Store(1, i101)

		Store("m13f started", Debug)

		if (LNot(i105)) {
			Release(T805)
		}

		Store("m13f completed", Debug)

		return (1)
	}

	Method(m140)
	{
		Store(1, i101)

		Store("m140 started", Debug)

		Store(Acquire(T807, 0xffff), i107)

		Store("m140 completed", Debug)

		return (1)
	}
	*/
	/* Acquire/Release T804 */

	//Name(b11c, Buffer(Add(1, Store(Acquire(T804, 0xffff), i104))){0})
	//Name(b11d, Buffer(m137()){0})


	/* Acquire/Release T805 */

	//Name(b11e, Buffer(m13e()){0})
	//Name(b11f, Buffer(m13f()){0})

	/* Acquire T806 */

	//Name(b120, Buffer(Add(1, Store(Acquire(T806, 0xffff), i106))){0})

	/* Acquire T807 */

	//Name(b121, Buffer(m140()){0})


/*
 * m03c - check, register errors and reset the global level execution exception,
 *        set up id01 to non-zero in error case.
 */
//Name(i108, 0)
//Name(BUF2, Buffer(m03c()){})
/*
Method(m03c)
{
	if (CH03("", 0, 0x000, 0, 0))
	{
		Store(1, i108)
	}
}
*/
Method(m02e)
{
/*
	Method(m0b9)
	{
		if (i108) {
			err("", zFFF, 0x126, 0, 0, 0, 0)
		}

		if (LNot(i101)) {
			Store("******** Test was not run !!!!!!!!!!!!!", Debug)
			err("", zFFF, 0x002, 0, 0, 0, 0)
			return
		}

		Store("******** Test started", Debug)

		CH03("", 0, 0x003, 0, 0)


		if (i104) {
			Store("!!!!!!!! ERROR 1: Acquire(T804, 0xffff) failed", Debug)
			err("", zFFF, 0x004, 0, 0, 0, 0)
		} else {
			Store("Ok: Acquire(T804, 0xffff)", Debug)
		}

		if (i105) {
			Store("!!!!!!!! ERROR 2: Acquire(T805, 0xffff) failed", Debug)
			err("", zFFF, 0x005, 0, 0, 0, 0)
		} else {
			Store("Ok: Acquire(T805, 0xffff)", Debug)
		}

		Release(T804)
		CH04("", 0, 65, 0, 0x006, 0, 0) // AE_AML_MUTEX_NOT_ACQUIRED

		Release(T805)
		CH04("", 0, 65, 0, 0x007, 0, 0) // AE_AML_MUTEX_NOT_ACQUIRED

		// Release T807

		if (LNot(i107)) {
			Release(T807)
		} else {
			Store("!!!!!!!! ERROR 7: Acquire(T807, 0xffff) failed", Debug)
			err("", zFFF, 0x008, 0, 0, 0, 0)
		}
		CH03("", 0, 0x009, 0, 0)

		// Release T806

		if (LNot(i106)) {
			Release(T806)
		} else {
			Store("!!!!!!!! ERROR 5: Acquire(T806, 0xffff) failed", Debug)
			err("", zFFF, 0x00a, 0, 0, 0, 0)
		}
		CH03("", 0, 0x00b, 0, 0)

		Store("******** Test finished", Debug)
	}

	Method(mm00)
	{
		m0b9()
	}

	mm00()
*/
}

Method(m030,, Serialized)
{

	Mutex(T804, 8)
	Mutex(T805, 8)
	Mutex(T806, 8)
	Mutex(T807, 8)

	/*
	 * These declarations are used for to check the Acquire
	 * and Release operations in a global level AML code.
	 */
	Name(i101, 0) // non-zero means that this test was run
	Name(i104, 1)
	Name(i105, 1)
	Name(i106, 1)
	Name(i107, 1)

	Method(m137)
	{
		Store(1, i101)

		Store("m137 started", Debug)

		if (LNot(i104)) {
			Release(T804)
		}

		Store("m137 completed", Debug)

		return (1)
	}

	Method(m13e)
	{
		Store(1, i101)

		Store("m13e started", Debug)

		Store(Acquire(T805, 0xffff), i105)

		Store("m13e completed", Debug)

		return (1)
	}

	Method(m13f)
	{
		Store(1, i101)

		Store("m13f started", Debug)

		if (LNot(i105)) {
			Release(T805)
		}

		Store("m13f completed", Debug)

		return (1)
	}

	Method(m140)
	{
		Store(1, i101)

		Store("m140 started", Debug)

		Store(Acquire(T807, 0xffff), i107)

		Store("m140 completed", Debug)

		return (1)
	}

	/* Acquire/Release T804 */

	Name(b11c, Buffer(Add(1, Store(Acquire(T804, 0xffff), i104))){0})
	Name(b11d, Buffer(m137()){0})


	/* Acquire/Release T805 */

	Name(b11e, Buffer(m13e()){0})
	Name(b11f, Buffer(m13f()){0})

	/* Acquire T806 */

	Name(b120, Buffer(Add(1, Store(Acquire(T806, 0xffff), i106))){0})

	/* Acquire T807 */

	Name(b121, Buffer(m140()){0})


	Method(m0b9)
	{
		if (LNot(i101)) {
			Store("******** Test was not run !!!!!!!!!!!!!", Debug)
			err("", zFFF, 0x000, 0, 0, 0, 0)
			return
		}

		Store("******** Test started", Debug)

		CH03("", 0, 0x001, 0, 0)


		if (i104) {
			Store("!!!!!!!! ERROR 1: Acquire(T804, 0xffff) failed", Debug)
			err("", zFFF, 0x002, 0, 0, 0, 0)
		} else {
			Store("Ok: Acquire(T804, 0xffff)", Debug)
		}

		if (i105) {
			Store("!!!!!!!! ERROR 2: Acquire(T805, 0xffff) failed", Debug)
			err("", zFFF, 0x003, 0, 0, 0, 0)
		} else {
			Store("Ok: Acquire(T805, 0xffff)", Debug)
		}

		Release(T804)
		CH04("", 0, 65, 0, 0x004, 0, 0) // AE_AML_MUTEX_NOT_ACQUIRED

		Release(T805)
		CH04("", 0, 65, 0, 0x005, 0, 0) // AE_AML_MUTEX_NOT_ACQUIRED

		/* Release T807 */

		if (LNot(i107)) {
			Release(T807)
		} else {
			Store("!!!!!!!! ERROR 7: Acquire(T807, 0xffff) failed", Debug)
			err("", zFFF, 0x006, 0, 0, 0, 0)
		}
		CH03("", 0, 0x007, 0, 0)

		/* Release T806 */

		if (LNot(i106)) {
			Release(T806)
		} else {
			Store("!!!!!!!! ERROR 5: Acquire(T806, 0xffff) failed", Debug)
			err("", zFFF, 0x008, 0, 0, 0, 0)
		}
		CH03("", 0, 0x009, 0, 0)

		Store("******** Test finished", Debug)
	}

	Method(mm00)
	{
		m0b9()
	}

	mm00()
}

