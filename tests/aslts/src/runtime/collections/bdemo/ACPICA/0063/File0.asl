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
 * ToInteger(<0x-hex-dec>)
 */
Method(mf92) {

	// Hex: 0x - dec

	CH03("", 0, 0x100, __LINE__, 0)

	ToInteger("0x0", Local0)
	if (LNotEqual(Local0, 0x0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x0)
	}

	ToInteger("0x0000000", Local0)
	if (LNotEqual(Local0, 0x0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x0)
	}

	ToInteger("0x1", Local0)
	if (LNotEqual(Local0, 0x1)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1)
	}

	ToInteger("0x12345678", Local0)
	if (LNotEqual(Local0, 0x12345678)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x12345678)
	}

	ToInteger("0x12345", Local0)
	if (LNotEqual(Local0, 0x12345)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x12345)
	}

	if (F64) {
		Store("0x1234567890123456", Local1)
		ToInteger(Local1, Local0)
		if (LNotEqual(Local0, 0x1234567890123456)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1234567890123456)
		}

		Store("0x123456789012345", Local1)
		ToInteger(Local1, Local0)
		if (LNotEqual(Local0, 0x123456789012345)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x123456789012345)
		}
	}

	// Hex: 0x - hex

	ToInteger("0xabcdefef", Local0)
	if (LNotEqual(Local0, 0xabcdefef)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0xabcdefef)
	}

	ToInteger("0xabcdef", Local0)
	if (LNotEqual(Local0, 0xabcdef)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0xabcdef)
	}

	if (F64) {
		Store("0xabcdefefadefbcdf", Local1)
		ToInteger(Local1, Local0)
		if (LNotEqual(Local0, 0xabcdefefadefbcdf)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0xabcdefefadefbcdf)
		}

		Store("0xabcdefefadefbcd", Local1)
		ToInteger(Local1, Local0)
		if (LNotEqual(Local0, 0xabcdefefadefbcd)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0xabcdefefadefbcd)
		}
	}

	// Hex: 0x - dec/hex

	ToInteger("0x1ab2cd34", Local0)
	if (LNotEqual(Local0, 0x1ab2cd34)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1ab2cd34)
	}

	if (F64) {
		Store("0x1ab2cd340fe05678", Local1)
		ToInteger(Local1, Local0)
		if (LNotEqual(Local0, 0x1ab2cd340fe05678)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1ab2cd340fe05678)
		}

		Store("0x1ab2cd340fe0", Local1)
		ToInteger(Local1, Local0)
		if (LNotEqual(Local0, 0x1ab2cd340fe0)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1ab2cd340fe0)
		}
	}

	CH03("", 0, 0x219, __LINE__, 0)
}

/*
 * ToInteger(<dec>)
 */
Method(mf93) {

	CH03("", 0, 0x10f, __LINE__, 0)

	ToInteger("0", Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	ToInteger("0000000", Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	ToInteger("000000000000000", Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	ToInteger("000000000000000000000000000000000000000000", Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	ToInteger("1", Local0)
	if (LNotEqual(Local0, 1)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 1)
	}

	ToInteger("1234567890", Local0)
	if (LNotEqual(Local0, 1234567890)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 1234567890)
	}

	ToInteger("1234567", Local0)
	if (LNotEqual(Local0, 1234567)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 1234567)
	}

	ToInteger("4294967295", Local0)
	if (LNotEqual(Local0, 4294967295)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 4294967295)
	}

	if (F64) {
		Store("18446744073709551615", Local1)
		ToInteger(Local1, Local0)
		if (LNotEqual(Local0, 18446744073709551615)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 18446744073709551615)
		}
	}

	CH03("", 0, 0x119, __LINE__, 0)
}

/*
 * White space before image of Data is skipped
 * (all examples above).
 */
Method(mf94) {

	CH03("", 0, 0x11a, __LINE__, 0)

	ToInteger("                    0x0", Local0)
	if (LNotEqual(Local0, 0x0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x0)
	}

	ToInteger("                    0x00000", Local0)
	if (LNotEqual(Local0, 0x0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x0)
	}

	ToInteger(" 0x1", Local0)
	if (LNotEqual(Local0, 0x1)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1)
	}

	ToInteger("  0x12345678", Local0)
	if (LNotEqual(Local0, 0x12345678)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x12345678)
	}

	ToInteger("   0x12345", Local0)
	if (LNotEqual(Local0, 0x12345)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x12345)
	}

	if (F64) {
		Store("    0x1234567890123456", Local1)
		ToInteger(Local1, Local0)
		if (LNotEqual(Local0, 0x1234567890123456)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1234567890123456)
		}

		Store("    0x123456789012345", Local1)
		ToInteger(Local1, Local0)
		if (LNotEqual(Local0, 0x123456789012345)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x123456789012345)
		}
	}

	ToInteger("     0xabcdefef", Local0)
	if (LNotEqual(Local0, 0xabcdefef)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0xabcdefef)
	}

	ToInteger("      0xabcdef", Local0)
	if (LNotEqual(Local0, 0xabcdef)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0xabcdef)
	}

	ToInteger("	0xabcdef", Local0)
	if (LNotEqual(Local0, 0xabcdef)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0xabcdef)
	}

	if (F64) {
		Store("       0xabcdefefadefbcdf", Local1)
		ToInteger(Local1, Local0)
		if (LNotEqual(Local0, 0xabcdefefadefbcdf)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0xabcdefefadefbcdf)
		}

		Store("       0xabcdefefadefbcd", Local1)
		ToInteger(Local1, Local0)
		if (LNotEqual(Local0, 0xabcdefefadefbcd)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0xabcdefefadefbcd)
		}
	}

	ToInteger("        0x1ab2cd34", Local0)
	if (LNotEqual(Local0, 0x1ab2cd34)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1ab2cd34)
	}

	if (F64) {
		Store("         0x1ab2cd340fe05678", Local1)
		ToInteger(Local1, Local0)
		if (LNotEqual(Local0, 0x1ab2cd340fe05678)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1ab2cd340fe05678)
		}

		Store("         0x1ab2cd340fe0", Local1)
		ToInteger(Local1, Local0)
		if (LNotEqual(Local0, 0x1ab2cd340fe0)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1ab2cd340fe0)
		}
	}

	ToInteger("          0", Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	ToInteger(" 	0000000", Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	ToInteger("	000000000000000", Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	ToInteger(" 000000000000000000000000000000000000000000", Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	ToInteger("           1", Local0)
	if (LNotEqual(Local0, 1)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 1)
	}

	ToInteger("            1234567890", Local0)
	if (LNotEqual(Local0, 1234567890)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 1234567890)
	}

	ToInteger("	1234567890", Local0)
	if (LNotEqual(Local0, 1234567890)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 1234567890)
	}

	ToInteger("									1234567890", Local0)
	if (LNotEqual(Local0, 1234567890)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 1234567890)
	}

	ToInteger("  	           1234567", Local0)
	if (LNotEqual(Local0, 1234567)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 1234567)
	}

	ToInteger("     	         4294967295", Local0)
	if (LNotEqual(Local0, 4294967295)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 4294967295)
	}

	if (F64) {
		Store("               	18446744073709551615", Local1)
		ToInteger(Local1, Local0)
		if (LNotEqual(Local0, 18446744073709551615)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 18446744073709551615)
		}
	}

	CH03("", 0, 0x135, __LINE__, 0)
}

/*
 * Zeros before significant characters in image without '0x' are skipped).
 */
Method(mf95) {

	CH03("", 0, 0x136, __LINE__, 0)

	ToInteger("          0", Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	ToInteger("          2", Local0)
	if (LNotEqual(Local0, 2)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 2)
	}

	ToInteger("          0xa", Local0)
	if (LNotEqual(Local0, 0xa)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0xa)
	}

	ToInteger("          04294967295", Local0)
	if (LNotEqual(Local0, 4294967295)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 4294967295)
	}

	ToInteger("04294967295", Local0)
	if (LNotEqual(Local0, 4294967295)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 4294967295)
	}

	ToInteger("000000000000000000004294967295", Local0)
	if (LNotEqual(Local0, 4294967295)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 4294967295)
	}

	ToInteger(" 000000000000000000004294967295", Local0)
	if (LNotEqual(Local0, 4294967295)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 4294967295)
	}

	ToInteger("	000000000000000000004294967295", Local0)
	if (LNotEqual(Local0, 4294967295)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 4294967295)
	}

	ToInteger("	 	 	 	 	000000000000000000004294967295", Local0)
	if (LNotEqual(Local0, 4294967295)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 4294967295)
	}

	ToInteger("	 	 	 	 	04294967295", Local0)
	if (LNotEqual(Local0, 4294967295)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 4294967295)
	}

	ToInteger("	 	 	 	 	0123456789", Local0)
	if (LNotEqual(Local0, 123456789)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 123456789)
	}

	ToInteger("0123456789", Local0)
	if (LNotEqual(Local0, 123456789)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 123456789)
	}

	ToInteger("00123456789", Local0)
	if (LNotEqual(Local0, 123456789)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 123456789)
	}

	if (F64) {
		Store("               	018446744073709551615", Local1)
		ToInteger(Local1, Local0)
		if (LNotEqual(Local0, 18446744073709551615)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 18446744073709551615)
		}

		Store("018446744073709551615", Local1)
		ToInteger(Local1, Local0)
		if (LNotEqual(Local0, 18446744073709551615)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 18446744073709551615)
		}

		Store("000000000000000000000000000000000000000018446744073709551615", Local1)
		ToInteger(Local1, Local0)
		if (LNotEqual(Local0, 18446744073709551615)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 18446744073709551615)
		}
	}

	CH03("", 0, 0x219, __LINE__, 0)
}

/*
 * ToInteger, exceptions
 */
Method(mf96) {

	// 5. "1234cd" (non-decimal character in dec-image)
	CH03("", 0, 0x147, __LINE__, 0)
	Store("1234cd", Local1)
	ToInteger(Local1, Local0)
	CH04("", 0, 0xff, 0, __LINE__, 0, 0)

	// 6. "000x1234" (non-decimal character in dec-image)
	CH03("", 0, 0x149, __LINE__, 0)
	Store("000x1234", Local1)
	ToInteger(Local1, Local0)
	CH04("", 0, 0xff, 0, __LINE__, 0, 0)

	// 7. "0x1234cdQ" (non-hex character in '0x'-image)
	CH03("", 0, 0x14b, __LINE__, 0)
	Store("0x1234cdQ", Local1)
	ToInteger(Local1, Local0)
	CH04("", 0, 0xff, 0, __LINE__, 0, 0)

	CH03("", 0, 0x14d, __LINE__, 0)
	Store("0x0x12345", Local1)
	ToInteger(Local1, Local0)
	CH04("", 0, 0xff, 0, __LINE__, 0, 0)

	// 8. "1234 " (white space in dec image)
	CH03("", 0, 0x14f, __LINE__, 0)
	Store("1234 ", Local1)
	ToInteger(Local1, Local0)
	CH04("", 0, 0xff, 0, __LINE__, 0, 0)

	// 9. "0x1234cd " (white space in '0x'-image)
	CH03("", 0, 0x151, __LINE__, 0)
	Store("0x1234cd ", Local1)
	ToInteger(Local1, Local0)
	CH04("", 0, 0xff, 0, __LINE__, 0, 0)

	// 10. "0x 1234cdQ" (white space after '0x')
	CH03("", 0, 0x153, __LINE__, 0)
	Store("0x 1234", Local1)
	ToInteger(Local1, Local0)
	CH04("", 0, 0xff, 0, __LINE__, 0, 0)

	CH03("", 0, 0x155, __LINE__, 0)
	Store("0x0x 1234", Local1)
	ToInteger(Local1, Local0)
	CH04("", 0, 0xff, 0, __LINE__, 0, 0)

	CH03("", 0, 0x157, __LINE__, 0)
	Store("0x0x 0x 1234", Local1)
	ToInteger(Local1, Local0)
	CH04("", 0, 0xff, 0, __LINE__, 0, 0)

	CH03("", 0, 0x159, __LINE__, 0)
	Store("0x 0x 1234", Local1)
	ToInteger(Local1, Local0)
	CH04("", 0, 0xff, 0, __LINE__, 0, 0)

	// 11. (decimal image exceeding maximal)
	//     32-bit mode – the value exceeding "4294967295"
	if (LNot(F64)) {
		CH03("", 0, 0x15b, __LINE__, 0)
		Store("4294967296", Local1)
		ToInteger(Local1, Local0)
		CH04("", 0, 0xff, 0, __LINE__, 0, 0)

		CH03("", 0, 0x15d, __LINE__, 0)
	    Store("123456789012345678904294967296", Local1)
		ToInteger(Local1, Local0)
		CH04("", 0, 0xff, 0, __LINE__, 0, 0)

		CH03("", 0, 0x15f, __LINE__, 0)
		Store(" 	 		00004294967296", Local1)
		ToInteger(Local1, Local0)
		CH04("", 0, 0xff, 0, __LINE__, 0, 0)

		CH03("", 0, 0x161, __LINE__, 0)
		Store("	0123456789012345678904294967296", Local1)
		ToInteger(Local1, Local0)
		CH04("", 0, 0xff, 0, __LINE__, 0, 0)

		CH03("", 0, 0x163, __LINE__, 0)
		Store("0123456789012345678904294967296", Local1)
		ToInteger(Local1, Local0)
		CH04("", 0, 0xff, 0, __LINE__, 0, 0)

		CH03("", 0, 0x165, __LINE__, 0)
		Store(" 123456789012345678904294967296", Local1)
		ToInteger(Local1, Local0)
		CH04("", 0, 0xff, 0, __LINE__, 0, 0)

		CH03("", 0, 0x167, __LINE__, 0)
		Store("	123456789012345678904294967296", Local1)
		ToInteger(Local1, Local0)
		CH04("", 0, 0xff, 0, __LINE__, 0, 0)
	}

	//     64-bit mode – the value exceeding "18446744073709551615"
	CH03("", 0, 0x169, __LINE__, 0)
	Store("18446744073709551616", Local1)
	ToInteger(Local1, Local0)
	CH04("", 0, 0xff, 0, __LINE__, 0, 0)

	CH03("", 0, 0x16b, __LINE__, 0)
	Store("	18446744073709551616", Local1)
	ToInteger(Local1, Local0)
	CH04("", 0, 0xff, 0, __LINE__, 0, 0)

	CH03("", 0, 0x16d, __LINE__, 0)
	Store(" 18446744073709551616", Local1)
	ToInteger(Local1, Local0)
	CH04("", 0, 0xff, 0, __LINE__, 0, 0)

	CH03("", 0, 0x16f, __LINE__, 0)
	Store("018446744073709551616", Local1)
	ToInteger(Local1, Local0)
	CH04("", 0, 0xff, 0, __LINE__, 0, 0)

	CH03("", 0, 0x171, __LINE__, 0)
	Store(" 	000000000018446744073709551616", Local1)
	ToInteger(Local1, Local0)
	CH04("", 0, 0xff, 0, __LINE__, 0, 0)

	// 12. "0x12345678901234567" (hex image exceeding maximal)
	CH03("", 0, 0x173, __LINE__, 0)
	Store("0x12345678901234567", Local1)
	ToInteger(Local1, Local0)
	CH04("", 0, 0xff, 0, __LINE__, 0, 0)

	// 13. "0x00000000000001234" (hex image exceeding maximal; no matter that zeros)
	CH03("", 0, 0x175, __LINE__, 0)
	Store("0x00000000000001234", Local1)
	ToInteger(Local1, Local0)
	CH04("", 0, 0xff, 0, __LINE__, 0, 0)

	CH03("", 0, 0x178, __LINE__, 0)
	Store("0x0000000000000000000001234", Local1)
	ToInteger(Local1, Local0)
	CH04("", 0, 0xff, 0, __LINE__, 0, 0)

	// 14. "0x123456789" (hex image exceeding maximal; for 32-bit mode only)
	if (LNot(F64)) {
		CH03("", 0, 0x17a, __LINE__, 0)
		Store("0x123456789", Local1)
		ToInteger(Local1, Local0)
		CH04("", 0, 0xff, 0, __LINE__, 0, 0)
	}

	// 15. "0x" (incomplete '0x' image)
	CH03("", 0, 0x17c, __LINE__, 0)
	Store("0x", Local1)
	ToInteger(Local1, Local0)
	CH04("", 0, 0xff, 0, __LINE__, 0, 0)

	CH03("", 0, 0x17e, __LINE__, 0)
	Store("0x ", Local1)
	ToInteger(Local1, Local0)
	CH04("", 0, 0xff, 0, __LINE__, 0, 0)

	CH03("", 0, 0x180, __LINE__, 0)
	Store("0x	", Local1)
	ToInteger(Local1, Local0)
	CH04("", 0, 0xff, 0, __LINE__, 0, 0)

	CH03("", 0, 0x182, __LINE__, 0)
	Store("0x 1234", Local1)
	ToInteger(Local1, Local0)
	CH04("", 0, 0xff, 0, __LINE__, 0, 0)

	CH03("", 0, 0x184, __LINE__, 0)
	Store("0x	1234", Local1)
	ToInteger(Local1, Local0)
	CH04("", 0, 0xff, 0, __LINE__, 0, 0)

	// 16. Empty string
	CH03("", 0, 0x186, __LINE__, 0)
	Store("", Local1)
	ToInteger(Local1, Local0)
	CH04("", 0, 0xff, 0, __LINE__, 0, 0)
}


