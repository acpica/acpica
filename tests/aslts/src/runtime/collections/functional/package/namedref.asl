/*
 * Some or all of this work - Copyright (c) 2006 - 2016, Intel Corp.
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
 * Named References to non-Data Objects for the objects in a Package.
 */

/*
 * According to the ACPI 6.1 specification, Named References to Data Objects
 * (e.g. Integer reference) are resolved at runtime and Named References to
 * non-Data Objects are returned as references.

 * At least Windows 10 seems to interpret "references" as a string which will be
 * resolved at runtime and not during table loading.
 */

Name(z183, 183)

PowerResource(PWR1, 0, 0) {
	Name(_STA, 1)
	Method(_ON) {}
	Method(_OFF) {}
}
Name(INT1, 1)

Name(PKG1, Package() {
	PWR1,
	PWR2,
	INT1
})

PowerResource(PWR2, 0, 0) {
	Name(_STA, 1)
	Method(_ON) {}
	Method(_OFF) {}
}

// TEST: check whether a named reference in a Package is stored as String (2).
Method(CHKR)
{
	// PWR1
	Store(ObjectType (Index (PKG1, 0)), Local0)
	if (LNotEqual (Local0, 2)) {
		err("CHKR", z183, 0, 0, 0, Local0, 2)
	}

	// PWR2 (forward reference)
	Store(ObjectType (Index (PKG1, 1)), Local0)
	if (LNotEqual (Local0, 2)) {
		err("CHKR", z183, 1, 0, 0, Local0, 2)
	}

	// INT1
	Store(ObjectType (Index (PKG1, 2)), Local0)
	if (LNotEqual (Local0, 2)) {
		err("CHKR", z183, 2, 0, 0, Local0, 2)
	}
}
