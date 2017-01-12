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
 * Data type conversion and manipulation
 */

// Convert String to UUID Macro

Name(p356, Package()
{
	ToUUID("0a1b2c3d-4e5f-6071-8293-a4b5c6d7e8f9"),
	ToUUID("A0B1C2D3-E4F5-0617-2839-4A5B6C7D8E9F"),
})

Name(p357, Package()
{
	Buffer(16) {
		  0x3d, 0x2c, 0x1b, 0x0a, 0x5f, 0x4e, 0x71, 0x60,
		  0x82, 0x93, 0xa4, 0xb5, 0xc6, 0xd7, 0xe8, 0xf9},
	Buffer(16) {
		  0xd3, 0xc2, 0xb1, 0xa0, 0xf5, 0xe4, 0x17, 0x06,
		  0x28, 0x39, 0x4a, 0x5b, 0x6c, 0x7d, 0x8e, 0x9f},
})

// Run-method
Method(TOU0,, Serialized)
{
	Name(ts, "TOU0")

	Store("TEST: TOU0, Convert String to UUID Macro", Debug)

	m302(ts, 2, "p356", p356, p357, 7)
}
