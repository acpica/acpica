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
 * Bug 0101:
 *
 * SUMMARY: The ASL compiler fails to create RefOf reference to Method not returning explicitly any object
 */

	// ////////

	Method(me5e) {}

	Method(me5f)
	{
		Store(RefOf(me5e), Local0)
		Store(ObjectType(Local0), Debug)

		Store(ObjectType(Local0), Local1)

		if (LNotEqual(Local1, c010)) {
			err("", zFFF, 0x000, 0, 0, Local1, c010)
		}

		return (0)
	}

	// ////////

	Method(me60) { return (1) }

	Method(me61)
	{
		Store("Start of test", Debug)

		Store(RefOf(me60), Local0)

		Store("ObjectType(Local0):", Debug)

		Store(ObjectType(Local0), Local1)

		Store(Local1, Debug)

		if (LNotEqual(Local1, c010)) {
			err("", zFFF, 0x001, 0, 0, Local1, c010)
		}

		Store("Finish of test", Debug)

		return (0)
	}

	Method(me62)
	{
		me5f()
		me61()
	}
