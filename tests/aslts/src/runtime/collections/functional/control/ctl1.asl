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
 * Method execution control
 *
 * Simple checkings for {if,elseif,else} operators
 * Two levels embedded {if,elseif,else}
 */

Name(z004, 4)

/////////////// {if}

Method(m080, 1)
{
	Store(0x12345678, Local0)

	if (RNG0(arg0, 0, 1)) {
		Store(0, Local0)
		if (LEqual(arg0, 1)) {
			Store(1, Local0)
		}
	}

	return (Local0)
}

Method(m081, 1)
{
	Store(0x12345678, Local0)

	if (RNG0(arg0, 0, 2)) {
		Store(0, Local0)
		if (LEqual(arg0, 1)) {
			Store(1, Local0)
		} else {
			Store(2, Local0)
		}
	}

	return (Local0)
}

Method(m082, 1)
{
	Store(0x12345678, Local0)

	if (RNG0(arg0, 0, 2)) {
		Store(0, Local0)
		if (LEqual(arg0, 1)) {
			Store(1, Local0)
		} elseif (LEqual(arg0, 2)) {
			Store(2, Local0)
		}
	}

	return (Local0)
}

Method(m083, 1)
{
	Store(0x12345678, Local0)

	if (RNG0(arg0, 0, 3)) {
		Store(0, Local0)
		if (LEqual(arg0, 1)) {
			Store(1, Local0)
		} elseif (LEqual(arg0, 2)) {
			Store(2, Local0)
		} else {
			Store(3, Local0)
		}
	}

	return (Local0)
}

/////////////// {if,else} {if}

Method(m090, 1)
{
	Store(0x12345678, Local0)

	if (RNG0(arg0, 0, 1)) {
		Store(0, Local0)
		if (LEqual(arg0, 1)) {
			Store(1, Local0)
		}
	} else {
		Store(2, Local0)
	}

	return (Local0)
}

Method(m091, 1)
{
	Store(0x12345678, Local0)

	if (LEqual(arg0, 0)) {
		Store(0, Local0)
	} else {
		Store(1, Local0)
		if (LEqual(arg0, 2)) {
			Store(2, Local0)
		}
	}

	return (Local0)
}

Method(m092, 1)
{
	Store(0x12345678, Local0)

	if (RNG0(arg0, 0, 1)) {
		Store(0, Local0)
		if (LEqual(arg0, 1)) {
			Store(1, Local0)
		}
	} else {
		Store(2, Local0)
		if (LEqual(arg0, 3)) {
			Store(3, Local0)
		}
	}

	return (Local0)
}

/////////////// {if,else} {if,else}

Method(m093, 1)
{
	Store(0x12345678, Local0)

	if (RNG0(arg0, 0, 2)) {
		Store(0, Local0)
		if (LEqual(arg0, 1)) {
			Store(1, Local0)
		} else {
			Store(2, Local0)
		}
	} else {
		Store(3, Local0)
	}

	return (Local0)
}

Method(m094, 1)
{
	Store(0x12345678, Local0)

	if (LEqual(arg0, 0)) {
		Store(0, Local0)
	} else {
		Store(1, Local0)
		if (LEqual(arg0, 2)) {
			Store(2, Local0)
		} else {
			Store(3, Local0)
		}
	}

	return (Local0)
}

Method(m095, 1)
{
	Store(0x12345678, Local0)

	if (RNG0(arg0, 0, 2)) {
		Store(0, Local0)
		if (LEqual(arg0, 1)) {
			Store(1, Local0)
		} else {
			Store(2, Local0)
		}
	} else {
		Store(3, Local0)
		if (LEqual(arg0, 4)) {
			Store(4, Local0)
		} else {
			Store(5, Local0)
		}
	}

	return (Local0)
}

/////////////// {if,else} {if,elseif}

Method(m096, 1)
{
	Store(0x12345678, Local0)

	if (RNG0(arg0, 0, 2)) {
		Store(0, Local0)
		if (LEqual(arg0, 1)) {
			Store(1, Local0)
		} elseif (LEqual(arg0, 2)) {
			Store(2, Local0)
		}
	} else {
		Store(3, Local0)
	}

	return (Local0)
}

Method(m097, 1)
{
	Store(0x12345678, Local0)

	if (LEqual(arg0, 0)) {
		Store(0, Local0)
	} else {
		Store(1, Local0)
		if (LEqual(arg0, 2)) {
			Store(2, Local0)
		} elseif (LEqual(arg0, 3)) {
			Store(3, Local0)
		}
	}

	return (Local0)
}

Method(m098, 1)
{
	Store(0x12345678, Local0)

	if (RNG0(arg0, 0, 2)) {
		Store(0, Local0)
		if (LEqual(arg0, 1)) {
			Store(1, Local0)
		} elseif (LEqual(arg0, 2)) {
			Store(2, Local0)
		}
	} else {
		Store(3, Local0)
		if (LEqual(arg0, 4)) {
			Store(4, Local0)
		} elseif (LEqual(arg0, 5)) {
			Store(5, Local0)
		}
	}

	return (Local0)
}

/////////////// {if,else} {if,elseif,else}

Method(m099, 1)
{
	Store(0x12345678, Local0)

	if (RNG0(arg0, 0, 3)) {
		Store(0, Local0)
		if (LEqual(arg0, 1)) {
			Store(1, Local0)
		} elseif (LEqual(arg0, 2)) {
			Store(2, Local0)
		} else {
			Store(3, Local0)
		}
	} else {
		Store(4, Local0)
	}

	return (Local0)
}

Method(m09a, 1)
{
	Store(0x12345678, Local0)

	if (LEqual(arg0, 0)) {
		Store(0, Local0)
	} else {
		Store(1, Local0)
		if (LEqual(arg0, 2)) {
			Store(2, Local0)
		} elseif (LEqual(arg0, 3)) {
			Store(3, Local0)
		} else {
			Store(4, Local0)
		}
	}

	return (Local0)
}

Method(m09b, 1)
{
	Store(0x12345678, Local0)

	if (RNG0(arg0, 0, 3)) {
		Store(0, Local0)
		if (LEqual(arg0, 1)) {
			Store(1, Local0)
		} elseif (LEqual(arg0, 2)) {
			Store(2, Local0)
		} else {
			Store(3, Local0)
		}
	} else {
		Store(4, Local0)
		if (LEqual(arg0, 5)) {
			Store(5, Local0)
		} elseif (LEqual(arg0, 6)) {
			Store(6, Local0)
		} else {
			Store(7, Local0)
		}
	}

	return (Local0)
}

/////////////// {if,elseif} {if}

Method(m09c, 1)
{
	Store(0x12345678, Local0)

	if (RNG0(arg0, 0, 1)) {
		Store(0, Local0)
		if (LEqual(arg0, 1)) {
			Store(1, Local0)
		}
	} elseif (LEqual(arg0, 2)) {
		Store(2, Local0)
	}

	return (Local0)
}

Method(m09d, 1)
{
	Store(0x12345678, Local0)

	if (LEqual(arg0, 0)) {
		Store(0, Local0)
	} elseif (RNG0(arg0, 1, 2)) {
		Store(1, Local0)
		if (LEqual(arg0, 2)) {
			Store(2, Local0)
		}
	}

	return (Local0)
}

Method(m09e, 1)
{
	Store(0x12345678, Local0)

	if (RNG0(arg0, 0, 1)) {
		Store(0, Local0)
		if (LEqual(arg0, 1)) {
			Store(1, Local0)
		}
	} elseif (RNG0(arg0, 2, 3)) {
		Store(2, Local0)
		if (LEqual(arg0, 3)) {
			Store(3, Local0)
		}
	}

	return (Local0)
}

/////////////// {if,elseif} {if,else}

Method(m09f, 1)
{
	Store(0x12345678, Local0)

	if (RNG0(arg0, 0, 2)) {
		Store(0, Local0)
		if (LEqual(arg0, 1)) {
			Store(1, Local0)
		} else {
			Store(2, Local0)
		}
	} elseif (LEqual(arg0, 3)) {
		Store(3, Local0)
	}

	return (Local0)
}

Method(m0a0, 1)
{
	Store(0x12345678, Local0)

	if (LEqual(arg0, 0)) {
		Store(0, Local0)
	} elseif (RNG0(arg0, 1, 3)) {
		Store(1, Local0)
		if (LEqual(arg0, 2)) {
			Store(2, Local0)
		} else {
			Store(3, Local0)
		}
	}

	return (Local0)
}

Method(m0a1, 1)
{
	Store(0x12345678, Local0)

	if (RNG0(arg0, 0, 2)) {
		Store(0, Local0)
		if (LEqual(arg0, 1)) {
			Store(1, Local0)
		} else {
			Store(2, Local0)
		}
	} elseif (RNG0(arg0, 3, 5)) {
		Store(3, Local0)
		if (LEqual(arg0, 4)) {
			Store(4, Local0)
		} else {
			Store(5, Local0)
		}
	}

	return (Local0)
}

/////////////// {if,elseif} {if,elseif}

Method(m0a2, 1)
{
	Store(0x12345678, Local0)

	if (RNG0(arg0, 0, 2)) {
		Store(0, Local0)
		if (LEqual(arg0, 1)) {
			Store(1, Local0)
		} elseif (LEqual(arg0, 2)) {
			Store(2, Local0)
		}
	} elseif (LEqual(arg0, 3)) {
		Store(3, Local0)
	}

	return (Local0)
}

Method(m0a3, 1)
{
	Store(0x12345678, Local0)

	if (LEqual(arg0, 0)) {
		Store(0, Local0)
	} elseif (RNG0(arg0, 1, 3)) {
		Store(1, Local0)
		if (LEqual(arg0, 2)) {
			Store(2, Local0)
		} elseif (LEqual(arg0, 3)) {
			Store(3, Local0)
		}
	}

	return (Local0)
}

Method(m0a4, 1)
{
	Store(0x12345678, Local0)

	if (RNG0(arg0, 0, 2)) {
		Store(0, Local0)
		if (LEqual(arg0, 1)) {
			Store(1, Local0)
		} elseif (LEqual(arg0, 2)) {
			Store(2, Local0)
		}
	} elseif (RNG0(arg0, 3, 5)) {
		Store(3, Local0)
		if (LEqual(arg0, 4)) {
			Store(4, Local0)
		} elseif (LEqual(arg0, 5)) {
			Store(5, Local0)
		}
	}

	return (Local0)
}

/////////////// {if,elseif} {if,elseif,else}

Method(m0a5, 1)
{
	Store(0x12345678, Local0)

	if (RNG0(arg0, 0, 3)) {
		Store(0, Local0)
		if (LEqual(arg0, 1)) {
			Store(1, Local0)
		} elseif (LEqual(arg0, 2)) {
			Store(2, Local0)
		} else {
			Store(3, Local0)
		}
	} elseif (LEqual(arg0, 4)) {
		Store(4, Local0)
	}

	return (Local0)
}

Method(m0a6, 1)
{
	Store(0x12345678, Local0)

	if (LEqual(arg0, 0)) {
		Store(0, Local0)
	} elseif (RNG0(arg0, 1, 4)) {
		Store(1, Local0)
		if (LEqual(arg0, 2)) {
			Store(2, Local0)
		} elseif (LEqual(arg0, 3)) {
			Store(3, Local0)
		} else {
			Store(4, Local0)
		}
	}

	return (Local0)
}

Method(m0a7, 1)
{
	Store(0x12345678, Local0)

	if (RNG0(arg0, 0, 3)) {
		Store(0, Local0)
		if (LEqual(arg0, 1)) {
			Store(1, Local0)
		} elseif (LEqual(arg0, 2)) {
			Store(2, Local0)
		} else {
			Store(3, Local0)
		}
	} elseif (RNG0(arg0, 4, 7)) {
		Store(4, Local0)
		if (LEqual(arg0, 5)) {
			Store(5, Local0)
		} elseif (LEqual(arg0, 6)) {
			Store(6, Local0)
		} else {
			Store(7, Local0)
		}
	}

	return (Local0)
}

/////////////// {if,elseif,else} {if} (restricted)

Method(m0a8, 1)
{
	Store(0x12345678, Local0)

	if (RNG0(arg0, 0, 1)) {
		Store(0, Local0)
		if (LEqual(arg0, 1)) {
			Store(1, Local0)
		}
	} elseif (LEqual(arg0, 2)) {
		Store(2, Local0)
	} else {
		Store(3, Local0)
	}

	return (Local0)
}

Method(m0a9, 1)
{
	Store(0x12345678, Local0)

	if (LEqual(arg0, 0)) {
		Store(0, Local0)
	} elseif (RNG0(arg0, 1, 2)) {
		Store(1, Local0)
		if (LEqual(arg0, 2)) {
			Store(2, Local0)
		}
	} else {
		Store(3, Local0)
	}

	return (Local0)
}

Method(m0aa, 1)
{
	Store(0x12345678, Local0)

	if (LEqual(arg0, 0)) {
		Store(0, Local0)
	} elseif (LEqual(arg0, 1)) {
		Store(1, Local0)
	} else {
		Store(2, Local0)
		if (LEqual(arg0, 3)) {
			Store(3, Local0)
		}
	}

	return (Local0)
}

Method(m0ab, 1)
{
	Store(0x12345678, Local0)

	if (RNG0(arg0, 0, 1)) {
		Store(0, Local0)
		if (LEqual(arg0, 1)) {
			Store(1, Local0)
		}
	} elseif (RNG0(arg0, 2, 3)) {
		Store(2, Local0)
		if (LEqual(arg0, 3)) {
			Store(3, Local0)
		}
	} else {
		Store(4, Local0)
		if (LEqual(arg0, 5)) {
			Store(5, Local0)
		}
	}

	return (Local0)
}

/////////////// {if,elseif,else} {if,else} (restricted)

Method(m0ac, 1)
{
	Store(0x12345678, Local0)

	if (RNG0(arg0, 0, 2)) {
		Store(0, Local0)
		if (LEqual(arg0, 1)) {
			Store(1, Local0)
		} else {
			Store(2, Local0)
		}
	} elseif (LEqual(arg0, 3)) {
		Store(3, Local0)
	} else {
		Store(4, Local0)
	}

	return (Local0)
}

Method(m0ad, 1)
{
	Store(0x12345678, Local0)

	if (LEqual(arg0, 0)) {
		Store(0, Local0)
	} elseif (RNG0(arg0, 1, 3)) {
		Store(1, Local0)
		if (LEqual(arg0, 2)) {
			Store(2, Local0)
		} else {
			Store(3, Local0)
		}
	} else {
		Store(4, Local0)
	}

	return (Local0)
}

Method(m0ae, 1)
{
	Store(0x12345678, Local0)

	if (LEqual(arg0, 0)) {
		Store(0, Local0)
	} elseif (LEqual(arg0, 1)) {
		Store(1, Local0)
	} else {
		Store(2, Local0)
		if (LEqual(arg0, 3)) {
			Store(3, Local0)
		} else {
			Store(4, Local0)
		}
	}

	return (Local0)
}

Method(m0af, 1)
{
	Store(0x12345678, Local0)

	if (RNG0(arg0, 0, 2)) {
		Store(0, Local0)
		if (LEqual(arg0, 1)) {
			Store(1, Local0)
		} else {
			Store(2, Local0)
		}
	} elseif (RNG0(arg0, 3, 5)) {
		Store(3, Local0)
		if (LEqual(arg0, 4)) {
			Store(4, Local0)
		} else {
			Store(5, Local0)
		}
	} else {
		Store(6, Local0)
		if (LEqual(arg0, 7)) {
			Store(7, Local0)
		} else {
			Store(8, Local0)
		}
	}

	return (Local0)
}

/////////////// {if,elseif,else} {if,elseif} (restricted)

Method(m0b0, 1)
{
	Store(0x12345678, Local0)

	if (RNG0(arg0, 0, 2)) {
		Store(0, Local0)
		if (LEqual(arg0, 1)) {
			Store(1, Local0)
		} elseif (LEqual(arg0, 2)) {
			Store(2, Local0)
		}
	} elseif (LEqual(arg0, 3)) {
		Store(3, Local0)
	} else {
		Store(4, Local0)
	}

	return (Local0)
}

Method(m0b1, 1)
{
	Store(0x12345678, Local0)

	if (LEqual(arg0, 0)) {
		Store(0, Local0)
	} elseif (RNG0(arg0, 1, 3)) {
		Store(1, Local0)
		if (LEqual(arg0, 2)) {
			Store(2, Local0)
		} elseif (LEqual(arg0, 3)) {
			Store(3, Local0)
		}
	} else {
		Store(4, Local0)
	}

	return (Local0)
}

Method(m0b2, 1)
{
	Store(0x12345678, Local0)

	if (LEqual(arg0, 0)) {
		Store(0, Local0)
	} elseif (LEqual(arg0, 1)) {
		Store(1, Local0)
	} else {
		Store(2, Local0)
		if (LEqual(arg0, 3)) {
			Store(3, Local0)
		} elseif (LEqual(arg0, 4)) {
			Store(4, Local0)
		}
	}

	return (Local0)
}

Method(m0b3, 1)
{
	Store(0x12345678, Local0)

	if (RNG0(arg0, 0, 2)) {
		Store(0, Local0)
		if (LEqual(arg0, 1)) {
			Store(1, Local0)
		} elseif (LEqual(arg0, 2)) {
			Store(2, Local0)
		}
	} elseif (RNG0(arg0, 3, 5)) {
		Store(3, Local0)
		if (LEqual(arg0, 4)) {
			Store(4, Local0)
		} elseif (LEqual(arg0, 5)) {
			Store(5, Local0)
		}
	} else {
		Store(6, Local0)
		if (LEqual(arg0, 7)) {
			Store(7, Local0)
		} elseif (LEqual(arg0, 8)) {
			Store(8, Local0)
		}
	}

	return (Local0)
}

/////////////// {if,elseif,else} {if,elseif,else} (restricted)

Method(m0b4, 1)
{
	Store(0x12345678, Local0)

	if (RNG0(arg0, 0, 3)) {
		Store(0, Local0)
		if (LEqual(arg0, 1)) {
			Store(1, Local0)
		} elseif (LEqual(arg0, 2)) {
			Store(2, Local0)
		} else {
			Store(3, Local0)
		}
	} elseif (LEqual(arg0, 4)) {
		Store(4, Local0)
	} else {
		Store(5, Local0)
	}

	return (Local0)
}

Method(m0b5, 1)
{
	Store(0x12345678, Local0)

	if (LEqual(arg0, 0)) {
		Store(0, Local0)
	} elseif (RNG0(arg0, 1, 4)) {
		Store(1, Local0)
		if (LEqual(arg0, 2)) {
			Store(2, Local0)
		} elseif (LEqual(arg0, 3)) {
			Store(3, Local0)
		} else {
			Store(4, Local0)
		}
	} else {
		Store(5, Local0)
	}

	return (Local0)
}

Method(m0b6, 1)
{
	Store(0x12345678, Local0)

	if (LEqual(arg0, 0)) {
		Store(0, Local0)
	} elseif (LEqual(arg0, 1)) {
		Store(1, Local0)
	} else {
		Store(2, Local0)
		if (LEqual(arg0, 3)) {
			Store(3, Local0)
		} elseif (LEqual(arg0, 4)) {
			Store(4, Local0)
		} else {
			Store(5, Local0)
		}
	}

	return (Local0)
}

Method(m0b7, 1)
{
	Store(0x12345678, Local0)

	if (RNG0(arg0, 0, 3)) {
		Store(0, Local0)
		if (LEqual(arg0, 1)) {
			Store(1, Local0)
		} elseif (LEqual(arg0, 2)) {
			Store(2, Local0)
		} else {
			Store(3, Local0)
		}
	} elseif (RNG0(arg0, 4, 7)) {
		Store(4, Local0)
		if (LEqual(arg0, 5)) {
			Store(5, Local0)
		} elseif (LEqual(arg0, 6)) {
			Store(6, Local0)
		} else {
			Store(7, Local0)
		}
	} elseif (RNG0(arg0, 8, 11)) {
		Store(8, Local0)
		if (LEqual(arg0, 9)) {
			Store(9, Local0)
		} elseif (LEqual(arg0, 10)) {
			Store(10, Local0)
		} else {
			Store(11, Local0)
		}
	} else {
		Store(12, Local0)
		if (LEqual(arg0, 13)) {
			Store(13, Local0)
		} elseif (LEqual(arg0, 14)) {
			Store(14, Local0)
		} else {
			Store(15, Local0)
		}
	}

	return (Local0)
}

//////////////////////////////////////////////////////

// Run verify methods
// NOTE: use here as few control operators as possible
Method(m0b8,, Serialized)
{
	Name(ts, "m0b8")

	Store("TEST: m0b8, Two levels embedded {if, elseif, else}", Debug)

	// m080

	Store(0, Local7)
	While(LLessEqual(Local7, 1)) {
		Store(m080(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 0, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m080(Local7), Local0)
	if (LNotEqual(Local0, Local7)){
		err(ts, z004, 1, 0, 0, Local7, 0)
	}

	// m081

	Store(0, Local7)
	Store(m081(Local7), Local0)
	if (LNotEqual(Local0, 2)){
		err(ts, z004, 2, 0, 0, Local7, 0)
	}

	Store(1, Local7)
	While(LLessEqual(Local7, 2)) {
		Store(m081(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 3, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m081(Local7), Local0)
	if (LNotEqual(Local0, Local7)){
		err(ts, z004, 4, 0, 0, Local7, 0)
	}

	// m082

	Store(0, Local7)
	While(LLessEqual(Local7, 2)) {
		Store(m082(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 5, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m082(Local7), Local0)
	if (LNotEqual(Local0, Local7)){
		err(ts, z004, 6, 0, 0, Local7, 0)
	}

	// m083

	Store(0, Local7)
	Store(m083(Local7), Local0)
	if (LNotEqual(Local0, 3)){
		err(ts, z004, 7, 0, 0, Local7, 0)
	}

	Store(1, Local7)
	While(LLessEqual(Local7, 3)) {
		Store(m083(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 8, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m083(Local7), Local0)
	if (LNotEqual(Local0, Local7)){
		err(ts, z004, 9, 0, 0, Local7, 0)
	}

	// m090

	Store(0, Local7)
	While(LLessEqual(Local7, 2)) {
		Store(m090(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 10, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m090(Local7), Local0)
	if (LNotEqual(Local0, 2)){
		err(ts, z004, 11, 0, 0, Local7, 0)
	}

	// m091

	Store(0, Local7)
	While(LLessEqual(Local7, 2)) {
		Store(m091(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 12, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m091(Local7), Local0)
	if (LNotEqual(Local0, 1)){
		err(ts, z004, 13, 0, 0, Local7, 0)
	}

	// m092

	Store(0, Local7)
	While(LLessEqual(Local7, 3)) {
		Store(m092(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 14, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m092(Local7), Local0)
	if (LNotEqual(Local0, 2)){
		err(ts, z004, 15, 0, 0, Local7, 0)
	}

	// m093

	Store(0, Local7)
	Store(m093(Local7), Local0)
	if (LNotEqual(Local0, 2)){
		err(ts, z004, 16, 0, 0, Local7, 0)
	}

	Store(1, Local7)
	While(LLessEqual(Local7, 3)) {
		Store(m093(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 17, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m093(Local7), Local0)
	if (LNotEqual(Local0, 3)){
		err(ts, z004, 18, 0, 0, Local7, 0)
	}

	// m094

	Store(0, Local7)
	Store(m094(Local7), Local0)
	if (LNotEqual(Local0, Local7)){
		err(ts, z004, 19, 0, 0, Local7, 0)
	}

	Store(1, Local7)
	Store(m094(Local7), Local0)
	if (LNotEqual(Local0, 3)){
		err(ts, z004, 20, 0, 0, Local7, 0)
	}

	Store(2, Local7)
	While(LLessEqual(Local7, 3)) {
		Store(m094(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 21, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m094(Local7), Local0)
	if (LNotEqual(Local0, 3)){
		err(ts, z004, 22, 0, 0, Local7, 0)
	}

	// m095

	Store(0, Local7)
	Store(m095(Local7), Local0)
	if (LNotEqual(Local0, 2)){
		err(ts, z004, 23, 0, 0, Local7, 0)
	}

	Store(1, Local7)
	While(LLessEqual(Local7, 2)) {
		Store(m095(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 24, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}


	Store(3, Local7)
	Store(m095(Local7), Local0)
	if (LNotEqual(Local0, 5)){
		err(ts, z004, 25, 0, 0, Local7, 0)
	}

	Store(4, Local7)
	While(LLessEqual(Local7, 5)) {
		Store(m095(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 26, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}


	Store(0x12345678, Local7)
	Store(m095(Local7), Local0)
	if (LNotEqual(Local0, 5)){
		err(ts, z004, 27, 0, 0, Local7, 0)
	}

	// m096

	Store(0, Local7)
	While(LLessEqual(Local7, 3)) {
		Store(m096(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 28, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m096(Local7), Local0)
	if (LNotEqual(Local0, 3)){
		err(ts, z004, 29, 0, 0, Local7, 0)
	}

	// m097

	Store(0, Local7)
	While(LLessEqual(Local7, 3)) {
		Store(m097(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 30, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m097(Local7), Local0)
	if (LNotEqual(Local0, 1)){
		err(ts, z004, 31, 0, 0, Local7, 0)
	}

	// m098

	Store(0, Local7)
	While(LLessEqual(Local7, 5)) {
		Store(m098(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 32, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m098(Local7), Local0)
	if (LNotEqual(Local0, 3)){
		err(ts, z004, 33, 0, 0, Local7, 0)
	}

	// m099

	Store(0, Local7)
	Store(m099(Local7), Local0)
	if (LNotEqual(Local0, 3)){
		err(ts, z004, 34, 0, 0, Local7, 0)
	}

	Store(1, Local7)
	While(LLessEqual(Local7, 4)) {
		Store(m099(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 35, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m099(Local7), Local0)
	if (LNotEqual(Local0, 4)){
		err(ts, z004, 36, 0, 0, Local7, 0)
	}

	// m09a

	Store(0, Local7)
	Store(m09a(Local7), Local0)
	if (LNotEqual(Local0, Local7)){
		err(ts, z004, 37, 0, 0, Local7, 0)
	}

	Store(1, Local7)
	Store(m09a(Local7), Local0)
	if (LNotEqual(Local0, 4)){
		err(ts, z004, 38, 0, 0, Local7, 0)
	}

	Store(2, Local7)
	While(LLessEqual(Local7, 4)) {
		Store(m09a(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 39, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m09a(Local7), Local0)
	if (LNotEqual(Local0, 4)){
		err(ts, z004, 40, 0, 0, Local7, 0)
	}

	// m09b

	Store(0, Local7)
	Store(m09b(Local7), Local0)
	if (LNotEqual(Local0, 3)){
		err(ts, z004, 41, 0, 0, Local7, 0)
	}

	Store(1, Local7)
	While(LLessEqual(Local7, 3)) {
		Store(m09b(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 42, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(4, Local7)
	Store(m09b(Local7), Local0)
	if (LNotEqual(Local0, 7)){
		err(ts, z004, 43, 0, 0, Local7, 0)
	}

	Store(5, Local7)
	While(LLessEqual(Local7, 7)) {
		Store(m09b(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 44, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m09b(Local7), Local0)
	if (LNotEqual(Local0, 7)){
		err(ts, z004, 45, 0, 0, Local7, 0)
	}

	// m09c

	Store(0, Local7)
	While(LLessEqual(Local7, 2)) {
		Store(m09c(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 46, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m09c(Local7), Local0)
	if (LNotEqual(Local0, Local7)){
		err(ts, z004, 47, 0, 0, Local7, 0)
	}

	// m09d

	Store(0, Local7)
	While(LLessEqual(Local7, 2)) {
		Store(m09d(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 48, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m09d(Local7), Local0)
	if (LNotEqual(Local0, Local7)){
		err(ts, z004, 49, 0, 0, Local7, 0)
	}

	// m09e

	Store(0, Local7)
	While(LLessEqual(Local7, 3)) {
		Store(m09e(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 50, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m09e(Local7), Local0)
	if (LNotEqual(Local0, Local7)){
		err(ts, z004, 51, 0, 0, Local7, 0)
	}

	// m09f

	Store(0, Local7)
	Store(m09f(Local7), Local0)
	if (LNotEqual(Local0, 2)){
		err(ts, z004, 52, 0, 0, Local7, 0)
	}

	Store(1, Local7)
	While(LLessEqual(Local7, 3)) {
		Store(m09f(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 53, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m09f(Local7), Local0)
	if (LNotEqual(Local0, Local7)){
		err(ts, z004, 54, 0, 0, Local7, 0)
	}

	// m0a0

	Store(0, Local7)
	Store(m0a0(Local7), Local0)
	if (LNotEqual(Local0, Local7)){
		err(ts, z004, 55, 0, 0, Local7, 0)
	}

	Store(1, Local7)
	Store(m0a0(Local7), Local0)
	if (LNotEqual(Local0, 3)){
		err(ts, z004, 56, 0, 0, Local7, 0)
	}

	Store(2, Local7)
	While(LLessEqual(Local7, 3)) {
		Store(m0a0(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 57, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m0a0(Local7), Local0)
	if (LNotEqual(Local0, Local7)){
		err(ts, z004, 58, 0, 0, Local7, 0)
	}

	// m0a1

	Store(0, Local7)
	Store(m0a1(Local7), Local0)
	if (LNotEqual(Local0, 2)){
		err(ts, z004, 59, 0, 0, Local7, 0)
	}

	Store(1, Local7)
	While(LLessEqual(Local7, 2)) {
		Store(m0a1(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 60, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(3, Local7)
	Store(m0a1(Local7), Local0)
	if (LNotEqual(Local0, 5)){
		err(ts, z004, 61, 0, 0, Local7, 0)
	}

	Store(4, Local7)
	While(LLessEqual(Local7, 5)) {
		Store(m0a1(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 62, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m0a1(Local7), Local0)
	if (LNotEqual(Local0, Local7)){
		err(ts, z004, 63, 0, 0, Local7, 0)
	}

	// m0a2

	Store(0, Local7)
	While(LLessEqual(Local7, 3)) {
		Store(m0a2(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 64, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m0a2(Local7), Local0)
	if (LNotEqual(Local0, Local7)){
		err(ts, z004, 65, 0, 0, Local7, 0)
	}

	// m0a3

	Store(0, Local7)
	While(LLessEqual(Local7, 3)) {
		Store(m0a3(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 66, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m0a3(Local7), Local0)
	if (LNotEqual(Local0, Local7)){
		err(ts, z004, 67, 0, 0, Local7, 0)
	}

	// m0a4

	Store(0, Local7)
	While(LLessEqual(Local7, 5)) {
		Store(m0a4(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 68, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m0a4(Local7), Local0)
	if (LNotEqual(Local0, Local7)){
		err(ts, z004, 69, 0, 0, Local7, 0)
	}

	// m0a5

	Store(0, Local7)
	Store(m0a5(Local7), Local0)
	if (LNotEqual(Local0, 3)){
		err(ts, z004, 70, 0, 0, Local7, 0)
	}

	Store(1, Local7)
	While(LLessEqual(Local7, 4)) {
		Store(m0a5(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 71, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m0a5(Local7), Local0)
	if (LNotEqual(Local0, Local7)){
		err(ts, z004, 72, 0, 0, Local7, 0)
	}

	// m0a6

	Store(0, Local7)
	Store(m0a6(Local7), Local0)
	if (LNotEqual(Local0, Local7)){
		err(ts, z004, 73, 0, 0, Local7, 0)
	}

	Store(1, Local7)
	Store(m0a6(Local7), Local0)
	if (LNotEqual(Local0, 4)){
		err(ts, z004, 74, 0, 0, Local7, 0)
	}

	Store(2, Local7)
	While(LLessEqual(Local7, 4)) {
		Store(m0a6(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 75, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m0a6(Local7), Local0)
	if (LNotEqual(Local0, Local7)){
		err(ts, z004, 76, 0, 0, Local7, 0)
	}

	// m0a7

	Store(0, Local7)
	Store(m0a7(Local7), Local0)
	if (LNotEqual(Local0, 3)){
		err(ts, z004, 77, 0, 0, Local7, 0)
	}

	Store(1, Local7)
	While(LLessEqual(Local7, 3)) {
		Store(m0a7(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 78, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(4, Local7)
	Store(m0a7(Local7), Local0)
	if (LNotEqual(Local0, 7)){
		err(ts, z004, 79, 0, 0, Local7, 0)
	}

	Store(5, Local7)
	While(LLessEqual(Local7, 7)) {
		Store(m0a7(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 80, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m0a7(Local7), Local0)
	if (LNotEqual(Local0, Local7)){
		err(ts, z004, 81, 0, 0, Local7, 0)
	}

	// m0a8

	Store(0, Local7)
	While(LLessEqual(Local7, 3)) {
		Store(m0a8(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 82, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m0a8(Local7), Local0)
	if (LNotEqual(Local0, 3)){
		err(ts, z004, 83, 0, 0, Local7, 0)
	}

	// m0a9

	Store(0, Local7)
	While(LLessEqual(Local7, 3)) {
		Store(m0a9(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 84, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m0a9(Local7), Local0)
	if (LNotEqual(Local0, 3)){
		err(ts, z004, 85, 0, 0, Local7, 0)
	}

	// m0aa

	Store(0, Local7)
	While(LLessEqual(Local7, 3)) {
		Store(m0aa(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 86, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m0aa(Local7), Local0)
	if (LNotEqual(Local0, 2)){
		err(ts, z004, 87, 0, 0, Local7, 0)
	}

	// m0ab

	Store(0, Local7)
	While(LLessEqual(Local7, 5)) {
		Store(m0ab(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 88, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m0ab(Local7), Local0)
	if (LNotEqual(Local0, 4)){
		err(ts, z004, 89, 0, 0, Local7, 0)
	}
	// m0ac

	Store(0, Local7)
	Store(m0ac(Local7), Local0)
	if (LNotEqual(Local0, 2)){
		err(ts, z004, 90, 0, 0, Local7, 0)
	}

	Store(1, Local7)
	While(LLessEqual(Local7, 4)) {
		Store(m0ac(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 91, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m0ac(Local7), Local0)
	if (LNotEqual(Local0, 4)){
		err(ts, z004, 92, 0, 0, Local7, 0)
	}

	// m0ad

	Store(0, Local7)
	Store(m0ad(Local7), Local0)
	if (LNotEqual(Local0, Local7)){
		err(ts, z004, 93, 0, 0, Local7, 0)
	}

	Store(1, Local7)
	Store(m0ad(Local7), Local0)
	if (LNotEqual(Local0, 3)){
		err(ts, z004, 94, 0, 0, Local7, 0)
	}

	Store(2, Local7)
	While(LLessEqual(Local7, 4)) {
		Store(m0ad(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 95, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m0ad(Local7), Local0)
	if (LNotEqual(Local0, 4)){
		err(ts, z004, 96, 0, 0, Local7, 0)
	}

	// m0ae

	Store(0, Local7)
	While(LLessEqual(Local7, 1)) {
		Store(m0ae(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 97, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(2, Local7)
	Store(m0ae(Local7), Local0)
	if (LNotEqual(Local0, 4)){
		err(ts, z004, 98, 0, 0, Local7, 0)
	}

	Store(3, Local7)
	While(LLessEqual(Local7, 4)) {
		Store(m0ae(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 99, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m0ae(Local7), Local0)
	if (LNotEqual(Local0, 4)){
		err(ts, z004, 100, 0, 0, Local7, 0)
	}

	// m0af


	Store(0, Local7)
	Store(m0af(Local7), Local0)
	if (LNotEqual(Local0, 2)){
		err(ts, z004, 101, 0, 0, Local7, 0)
	}

	Store(1, Local7)
	While(LLessEqual(Local7, 2)) {
		Store(m0af(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 102, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(3, Local7)
	Store(m0af(Local7), Local0)
	if (LNotEqual(Local0, 5)){
		err(ts, z004, 103, 0, 0, Local7, 0)
	}

	Store(4, Local7)
	While(LLessEqual(Local7, 5)) {
		Store(m0af(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 104, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}


	Store(6, Local7)
	Store(m0af(Local7), Local0)
	if (LNotEqual(Local0, 8)){
		err(ts, z004, 105, 0, 0, Local7, 0)
	}

	Store(7, Local7)
	While(LLessEqual(Local7, 8)) {
		Store(m0af(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 106, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m0af(Local7), Local0)
	if (LNotEqual(Local0, 8)){
		err(ts, z004, 107, 0, 0, Local7, 0)
	}

	// m0b0

	Store(0, Local7)
	While(LLessEqual(Local7, 4)) {
		Store(m0b0(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 108, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m0b0(Local7), Local0)
	if (LNotEqual(Local0, 4)){
		err(ts, z004, 109, 0, 0, Local7, 0)
	}

	// m0b1

	Store(0, Local7)
	While(LLessEqual(Local7, 4)) {
		Store(m0b1(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 110, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m0b1(Local7), Local0)
	if (LNotEqual(Local0, 4)){
		err(ts, z004, 111, 0, 0, Local7, 0)
	}

	// m0b2

	Store(0, Local7)
	While(LLessEqual(Local7, 4)) {
		Store(m0b2(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 112, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m0b2(Local7), Local0)
	if (LNotEqual(Local0, 2)){
		err(ts, z004, 113, 0, 0, Local7, 0)
	}

	// m0b3

	Store(0, Local7)
	While(LLessEqual(Local7, 4)) {
		Store(m0b3(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 114, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m0b3(Local7), Local0)
	if (LNotEqual(Local0, 6)){
		err(ts, z004, 115, 0, 0, Local7, 0)
	}

	// m0b4

	Store(0, Local7)
	Store(m0b4(Local7), Local0)
	if (LNotEqual(Local0, 3)){
		err(ts, z004, 116, 0, 0, Local7, 0)
	}

	Store(1, Local7)
	While(LLessEqual(Local7, 5)) {
		Store(m0b4(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 117, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m0b4(Local7), Local0)
	if (LNotEqual(Local0, 5)){
		err(ts, z004, 118, 0, 0, Local7, 0)
	}

	// m0b5

	Store(0, Local7)
	Store(m0b5(Local7), Local0)
	if (LNotEqual(Local0, Local7)){
		err(ts, z004, 119, 0, 0, Local7, 0)
	}

	Store(1, Local7)
	Store(m0b5(Local7), Local0)
	if (LNotEqual(Local0, 4)){
		err(ts, z004, 120, 0, 0, Local7, 0)
	}

	Store(2, Local7)
	While(LLessEqual(Local7, 5)) {
		Store(m0b5(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 121, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m0b5(Local7), Local0)
	if (LNotEqual(Local0, 5)){
		err(ts, z004, 122, 0, 0, Local7, 0)
	}

	// m0b6

	Store(0, Local7)
	While(LLessEqual(Local7, 1)) {
		Store(m0b6(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 123, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(2, Local7)
	Store(m0b6(Local7), Local0)
	if (LNotEqual(Local0, 5)){
		err(ts, z004, 124, 0, 0, Local7, 0)
	}

	Store(3, Local7)
	While(LLessEqual(Local7, 5)) {
		Store(m0b6(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 125, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m0b6(Local7), Local0)
	if (LNotEqual(Local0, 5)){
		err(ts, z004, 126, 0, 0, Local7, 0)
	}

	// m0b7

	Store(0, Local7)
	Store(m0b7(Local7), Local0)
	if (LNotEqual(Local0, 3)){
		err(ts, z004, 127, 0, 0, Local7, 0)
	}

	Store(1, Local7)
	While(LLessEqual(Local7, 3)) {
		Store(m0b7(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 128, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(4, Local7)
	Store(m0b7(Local7), Local0)
	if (LNotEqual(Local0, 7)){
		err(ts, z004, 129, 0, 0, Local7, 0)
	}

	Store(5, Local7)
	While(LLessEqual(Local7, 7)) {
		Store(m0b7(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 130, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(8, Local7)
	Store(m0b7(Local7), Local0)
	if (LNotEqual(Local0, 11)){
		err(ts, z004, 131, 0, 0, Local7, 0)
	}

	Store(9, Local7)
	While(LLessEqual(Local7, 11)) {
		Store(m0b7(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 132, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(12, Local7)
	Store(m0b7(Local7), Local0)
	if (LNotEqual(Local0, 15)){
		err(ts, z004, 133, 0, 0, Local7, 0)
	}

	Store(13, Local7)
	While(LLessEqual(Local7, 15)) {
		Store(m0b7(Local7), Local0)
		if (LNotEqual(Local0, Local7)){
			err(ts, z004, 134, 0, 0, Local7, 0)
		}
		Increment(Local7)
	}

	Store(0x12345678, Local7)
	Store(m0b7(Local7), Local0)
	if (LNotEqual(Local0, 15)){
		err(ts, z004, 135, 0, 0, Local7, 0)
	}
}

// Run-method
Method(CTL1)
{
	Store("TEST: CTL1, Conditional execution", Debug)

	m0b8()
}

