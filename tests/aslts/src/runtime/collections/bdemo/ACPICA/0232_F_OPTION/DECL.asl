/*
 * Some or all of this work - Copyright (c) 2006 - 2018, Intel Corp.
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
 * Bug 232:
 *
 * SUMMARY: no exception on the repeated declaration
 *
 * The test requires utilyzing of
 * the -f option on the ASL compilation
 * stage.
 *
 * ASL Compiler:
 *
 *   -f  -  Ignore errors, force creation of AML output file(s)
 */

/*
 *         Name(n000, 0)
 * Error 1034 - ^ Name already exists in scope (N000)
 */

Method(m15c,, Serialized)
{
	Name (VV, 0x1234)
	Store (32, Local0)

	CH03("", 0, 0x000, __LINE__, 0)

	Name (VV, 0xBBBBAAAA)
	Store (12, Local2)

	CH04("", 0, 0xff, 0, __LINE__, 0, 0)
}

Method(m15f)
{
	Method(m000) {}
	Store (32, Local0)

	CH03("", 0, 0x000, __LINE__, 0)

	Method(m000) {}
	Store (12, Local2)

	CH04("", 0, 0xff, 0, __LINE__, 0, 0)
}

Method(m160)
{
	SRMT("m15c")
	m15c()
	SRMT("m15f")
	m15f()
}
