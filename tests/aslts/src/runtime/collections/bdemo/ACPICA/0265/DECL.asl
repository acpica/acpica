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
 * Bug 265:
 *
 * SUMMARY: The second run to method calculating the IRef-to-String expression is evaluated incorrectly
 */

Method(m024)
{
	Method(mm00,, Serialized)
	{
		Name(i001, 0)
		Name(s000, "q\001ertyuiop")

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
										Return (0)
									}
									Store(0x08, Index(s000, 1))
									Return (Add(DerefOf(Index(s000, 1)), m008()))
								}
								Store(0x07, Index(s000, 1))
								Return (Add(DerefOf(Index(s000, 1)), m007()))
							}
							Store(0x06, Index(s000, 1))
							Return (Add(DerefOf(Index(s000, 1)), m006()))
						}
						Store(0x05, Index(s000, 1))
						Return (Add(DerefOf(Index(s000, 1)), m005()))
					}
					Store(0x04, Index(s000, 1))
					Return (Add(DerefOf(Index(s000, 1)), m004()))
				}
				Store(0x03, Index(s000, 1))
				Return (Add(DerefOf(Index(s000, 1)), m003()))
			}
			Store(0x02, Index(s000, 1))
			Return (Add(DerefOf(Index(s000, 1)), m002()))
		}
		Store(Add(DerefOf(Index(s000, 1)), m001()), Local0)

		if (LNotEqual(Local0, 0x24)) {
			err("", zFFF, 0x000, 0, 0, Local0, 0x24)
		}

		Store(DerefOf(Index(s000, 1)), Local0)

		Store(0x08, Local1)

		if (LNotEqual(Local0, Local1)) {
			err("", zFFF, 0x000, 0, 0, Local0, Local1)
		}
	}

	Method(mm01)
	{
		Store("The first run to mm00:", Debug)
		mm00()

		Store("The second run to mm00:", Debug)
		mm00()

		Store("The third run to mm00:", Debug)
		mm00()
	}

	mm01()
}


