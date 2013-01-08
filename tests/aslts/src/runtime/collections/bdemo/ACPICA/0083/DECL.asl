/*
 * Some or all of this work - Copyright (c) 2006 - 2013, Intel Corp.
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
 * Bug 0083:
 *
 * SUMMARY: No exception on DerefOf of an arbitrary Source
 */

	Method(me34)
	{
		Event(e000)
		Mutex(mx00, 0)
		ThermalZone(tz00) {}
		Processor(pr00, 0, 0xFFFFFFFF, 0) {}
		PowerResource(pw00, 1, 0) {Method(mmmm){return (0)}}
		OperationRegion(r000, SystemMemory, 0x100, 0x100)

		Name(b9Z0, Buffer() {0xb0,0xb1,0xb2,0xb3,0xb4})
		OperationRegion(r9Z0, SystemMemory, 0x100, 0x100)

		CreateField(b9Z0, 0, 8, bf90)
		Field(r9Z0, ByteAcc, NoLock, Preserve) {f900,8,f901,8,f902,8,f903,8}
		BankField(r9Z0, f901, 0, ByteAcc, NoLock, Preserve) {bn90,4}
		IndexField(f902, f903, ByteAcc, NoLock, Preserve) {if90,8,if91,8}

		Device(d000) {}
		Name(i000, 0x89abcdef)
		Name(b000, Buffer() {1,2,3,4})
		Name(p000, Package() {1,2,3,4})

/*
 *		Derefof(0x89abcdef)
 *              Invalid type ^  ([Integer] found, DerefOf operator requires [String|Reference])
 */


		// Expected exception for each DerefOf below

		CH03("", 0, 0x000, 0, 0)
		DerefOf(i000)
		CH04("", 0, 0xff, 0, 0x001, 0, 0)

		CH03("", 0, 0x000, 0, 0)
		DerefOf(b000)
		CH04("", 0, 0xff, 0, 0x001, 0, 0)

		CH03("", 0, 0x000, 0, 0)
		DerefOf(p000)
		CH04("", 0, 0xff, 0, 0x001, 0, 0)

		CH03("", 0, 0x000, 0, 0)
		DerefOf(d000)
		CH04("", 0, 0xff, 0, 0x001, 0, 0)


		CH03("", 0, 0x000, 0, 0)
		DerefOf(e000)
		CH04("", 0, 0xff, 0, 0x001, 0, 0)

		CH03("", 0, 0x000, 0, 0)
		DerefOf(mx00)
		CH04("", 0, 0xff, 0, 0x001, 0, 0)

		CH03("", 0, 0x000, 0, 0)
		DerefOf(tz00)
		CH04("", 0, 0xff, 0, 0x001, 0, 0)

		CH03("", 0, 0x000, 0, 0)
		DerefOf(pr00)
		CH04("", 0, 0xff, 0, 0x001, 0, 0)

		CH03("", 0, 0x000, 0, 0)
		DerefOf(pw00)
		CH04("", 0, 0xff, 0, 0x001, 0, 0)

		CH03("", 0, 0x000, 0, 0)
		DerefOf(r000)
		CH04("", 0, 0xff, 0, 0x001, 0, 0)


		CH03("", 0, 0x000, 0, 0)
		DerefOf(bf90)
		CH04("", 0, 0xff, 0, 0x001, 0, 0)

		CH03("", 0, 0x000, 0, 0)
		DerefOf(f900)
		CH04("", 0, 0xff, 0, 0x001, 0, 0)

		CH03("", 0, 0x000, 0, 0)
		DerefOf(f901)
		CH04("", 0, 0xff, 0, 0x001, 0, 0)

		CH03("", 0, 0x000, 0, 0)
		DerefOf(f902)
		CH04("", 0, 0xff, 0, 0x001, 0, 0)

		CH03("", 0, 0x000, 0, 0)
		DerefOf(f903)
		CH04("", 0, 0xff, 0, 0x001, 0, 0)

		CH03("", 0, 0x000, 0, 0)
		DerefOf(bn90)
		CH04("", 0, 0xff, 0, 0x001, 0, 0)

		CH03("", 0, 0x000, 0, 0)
		DerefOf(if90)
		CH04("", 0, 0xff, 0, 0x001, 0, 0)

		CH03("", 0, 0x000, 0, 0)
		DerefOf(if91)
		CH04("", 0, 0xff, 0, 0x001, 0, 0)


		// And so on..
	}
