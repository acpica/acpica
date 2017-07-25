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
 * Implicit String to Integer (<0x-hex-dec>)
 */
Method(mf97) {

	// Hex: 0x - dec

	CH03("", 0, 0x200, __LINE__, 0)

	Add("", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	Add("0x0", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	Add("0x1", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	Add("0x12345678", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	Add("0x1234567890123456", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// Hex: 0x - hex

	Add("0xabcdefef", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	Add("0xabcdefefadefbcdf", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// Hex: 0x - dec/hex

	Add("0x1ab2cd340fe05678", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x208, __LINE__, 0)
	Add("0x1ab2cd340fe0567823456789123456789987", 0, Local0)
	CH03("", 0, 0x209, __LINE__, 0)

	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x20b, __LINE__, 0)
}

/*
 * Implicit String to Integer (<dec>)
 */
Method(mf98) {

	CH03("", 0, 0x200, __LINE__, 0)

	Add("0", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x201, __LINE__, 0)

	Add("0000000", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x202, __LINE__, 0)

	Add("000000000000000000000000000000", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x203, __LINE__, 0)

	Add("1", 0, Local0)
	if (LNotEqual(Local0, 1)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 1)
	}

	CH03("", 0, 0x204, __LINE__, 0)

	Add("12345678", 0, Local0)
	if (LNotEqual(Local0, 0x12345678)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x12345678)
	}

	CH03("", 0, 0x205, __LINE__, 0)
}

/*
 * Implicit String to Integer (<hex-dec>)
 */
Method(mf99) {

	CH03("", 0, 0x213, __LINE__, 0)

	// Hex: 0x - dec

	Add("1234567890123456", 0, Local0)
	if (F64) {
		if (LNotEqual(Local0, 0x1234567890123456)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1234567890123456)
		}
	} else {
		if (LNotEqual(Local0, 0x12345678)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x12345678)
		}
	}

	// Hex: 0x - hex

	Add("abcdefef", 0, Local0)
	if (LNotEqual(Local0, 0xabcdefef)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0xabcdefef)
	}

	Add("abcdefe", 0, Local0)
	if (LNotEqual(Local0, 0xabcdefe)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0xabcdefe)
	}

	Add("abcdefefadefbcdf", 0, Local0)
	if (F64) {
		if (LNotEqual(Local0, 0xabcdefefadefbcdf)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0xabcdefefadefbcdf)
		}
	} else {
		if (LNotEqual(Local0, 0xabcdefef)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0xabcdefef)
		}
	}

	// Hex: 0x - dec/hex

	Add("1ab2cd340fe05678", 0, Local0)
	if (F64) {
		if (LNotEqual(Local0, 0x1ab2cd340fe05678)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1ab2cd340fe05678)
		}
	} else {
		if (LNotEqual(Local0, 0x1ab2cd34)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1ab2cd34)
		}
	}

	Add("1ab2cd340fe05", 0, Local0)
	if (F64) {
		if (LNotEqual(Local0, 0x1ab2cd340fe05)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1ab2cd340fe05)
		}
	} else {
		if (LNotEqual(Local0, 0x1ab2cd34)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1ab2cd34)
		}
	}

	Add("1a", 0, Local0)
	if (LNotEqual(Local0, 0x1a)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1a)
	}

	CH03("", 0, 0x219, __LINE__, 0)
}

/*
 * No exceptions in special cases which force exceptions on ToInteger
 */
Method(mf9a) {

	// 5. "1234cd" (non-decimal character in dec-image)
	CH03("", 0, 0x220, __LINE__, 0)
	Add("1234cd", 0, Local0)
	if (LNotEqual(Local0, 0x1234cd)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1234cd)
	}

	// 6. "000x1234" (non-decimal character in dec-image)
	CH03("", 0, 0x223, __LINE__, 0)
	Add("000x1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 7. "0x1234cdQ" (non-hex character in '0x'-image)
	CH03("", 0, 0x225, __LINE__, 0)
	Add("0x1234cdQ", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}
	CH03("", 0, 0x227, __LINE__, 0)
	Add("1234cdQ", 0, Local0)
	if (LNotEqual(Local0, 0x1234cd)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1234cd)
	}

	CH03("", 0, 0x229, __LINE__, 0)
	Add("0x0x12345", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 8. "1234 " (white space in dec image)
	CH03("", 0, 0x22b, __LINE__, 0)
	Add("1234 ", 0, Local0)
	if (LNotEqual(Local0, 0x1234)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1234)
	}

	// 9. "0x1234cd " (white space in '0x'-image)
	CH03("", 0, 0x22d, __LINE__, 0)
	Add("1234cd ", 0, Local0)
	if (LNotEqual(Local0, 0x1234cd)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1234cd)
	}

	// 10. "0x 1234cdQ" (white space after '0x')
	CH03("", 0, 0x22f, __LINE__, 0)
	Add("0x 1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x231, __LINE__, 0)
	Add("0x0x 1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x233, __LINE__, 0)
	Add("0x0x 0x 1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x235, __LINE__, 0)
	Add("0x 0x 1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 11. (decimal image exceeding maximal)
	//     32-bit mode – the value exceeding "4294967295"
	if (1) {
		CH03("", 0, 0x237, __LINE__, 0)
		Add("4294967296", 0, Local0)
		if (F64) {
			if (LNotEqual(Local0, 0x4294967296)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x4294967296)
			}
		} else {
			if (LNotEqual(Local0, 0x42949672)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x42949672)
			}
		}

		CH03("", 0, 0x23a, __LINE__, 0)
		Add("123456789012345678904294967296", 0, Local0)
		if (F64) {
			if (LNotEqual(Local0, 0x1234567890123456)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x1234567890123456)
			}
		} else {
			if (LNotEqual(Local0, 0x12345678)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x12345678)
			}
		}

		CH03("", 0, 0x23d, __LINE__, 0)
		Add(" 	 		00004294967296", 0, Local0)
		if (F64) {
			if (LNotEqual(Local0, 0x4294967296)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x4294967296)
			}
		} else {
			if (LNotEqual(Local0, 0x42949672)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x42949672)
			}
		}

		CH03("", 0, 0x240, __LINE__, 0)
		Add("	0123456789012345678904294967296", 0, Local0)
		if (F64) {
			if (LNotEqual(Local0, 0x1234567890123456)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x1234567890123456)
			}
		} else {
			if (LNotEqual(Local0, 0x12345678)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x12345678)
			}
		}

		CH03("", 0, 0x243, __LINE__, 0)
		Add("0123456789012345678904294967296", 0, Local0)
		if (F64) {
			if (LNotEqual(Local0, 0x1234567890123456)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x1234567890123456)
			}
		} else {
			if (LNotEqual(Local0, 0x12345678)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x12345678)
			}
		}

		CH03("", 0, 0x246, __LINE__, 0)
		Add(" 123456789012345678904294967296", 0, Local0)
		if (F64) {
			if (LNotEqual(Local0, 0x1234567890123456)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x1234567890123456)
			}
		} else {
			if (LNotEqual(Local0, 0x12345678)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x12345678)
			}
		}

		CH03("", 0, 0x249, __LINE__, 0)
		Add("	123456789012345678904294967296", 0, Local0)
		if (F64) {
			if (LNotEqual(Local0, 0x1234567890123456)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x1234567890123456)
			}
		} else {
			if (LNotEqual(Local0, 0x12345678)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x12345678)
			}
		}
	}

	//     64-bit mode – the value exceeding "18446744073709551615"
	CH03("", 0, 0x24c, __LINE__, 0)
	Add("18446744073709551616", 0, Local0)
	if (F64) {
		if (LNotEqual(Local0, 0x1844674407370955)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1844674407370955)
		}
	} else {
		if (LNotEqual(Local0, 0x18446744)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x18446744)
		}
	}

	CH03("", 0, 0x24f, __LINE__, 0)
	Add("	18446744073709551616", 0, Local0)
	if (F64) {
		if (LNotEqual(Local0, 0x1844674407370955)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1844674407370955)
		}
	} else {
		if (LNotEqual(Local0, 0x18446744)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x18446744)
		}
	}

	CH03("", 0, 0x252, __LINE__, 0)
	Add(" 18446744073709551616", 0, Local0)
	if (F64) {
		if (LNotEqual(Local0, 0x1844674407370955)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1844674407370955)
		}
	} else {
		if (LNotEqual(Local0, 0x18446744)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x18446744)
		}
	}

	CH03("", 0, 0x255, __LINE__, 0)
	Add("018446744073709551616", 0, Local0)
	if (F64) {
		if (LNotEqual(Local0, 0x1844674407370955)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1844674407370955)
		}
	} else {
		if (LNotEqual(Local0, 0x18446744)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x18446744)
		}
	}

	CH03("", 0, 0x258, __LINE__, 0)
	Add(" 	000000000018446744073709551616", 0, Local0)
	if (F64) {
		if (LNotEqual(Local0, 0x1844674407370955)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1844674407370955)
		}
	} else {
		if (LNotEqual(Local0, 0x18446744)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x18446744)
		}
	}

	// 12. "0x12345678901234567" (hex image exceeding maximal)
	CH03("", 0, 0x25b, __LINE__, 0)
	Add("0x12345678901234567", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 13. "0x00000000000001234" (hex image exceeding maximal; no matter that zeros)
	CH03("", 0, 0x25e, __LINE__, 0)
	Add("0x00000000000001234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x260, __LINE__, 0)
	Add("0x0000000000000000000001234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 14. "0x123456789" (hex image exceeding maximal; for 32-bit mode only)
	if (1) {
		CH03("", 0, 0x262, __LINE__, 0)
		Add("0x123456789", 0, Local0)
		if (LNotEqual(Local0, 0)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0)
		}
	}

	// 15. "0x" (incomplete '0x' image)
	CH03("", 0, 0x264, __LINE__, 0)
	Add("0x", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}
	CH03("", 0, 0x266, __LINE__, 0)
}

/*
 * 2. " 0x1234cd" (white space before image of Data is skipped)
 *
 * All the above examples but with the white space before image of Data.
 */
Method(mf9b) {

	// Hex: 0x - dec

	CH03("", 0, 0x267, __LINE__, 0)

	Add(" 0x0", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	Add("	0x1", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	Add("	 0x12345678", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	Add(" 	0x1234567890123456", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// Hex: 0x - hex

	Add("  0xabcdefef", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	Add("		0xabcdefefadefbcdf", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// Hex: 0x - dec/hex

	Add(" 	 	 	 	 	0x1ab2cd340fe05678", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x26f, __LINE__, 0)
	Add("	 	 	 	 	 	0x1ab2cd340fe0567823456789123456789987", 0, Local0)
	CH03("", 0, 0x270, __LINE__, 0)

	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x272, __LINE__, 0)

	/*
	 * Implicit String to Integer (<dec>)
	 *
	 * Method(mf98)
	 */

	CH03("", 0, 0x273, __LINE__, 0)

	Add("                       0", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x275, __LINE__, 0)

	Add("						0000000", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x277, __LINE__, 0)

	Add("                                 000000000000000000000000000000", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x279, __LINE__, 0)

	Add("							000000000000000000000000000000", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x27b, __LINE__, 0)

	Add(" 		 1", 0, Local0)
	if (LNotEqual(Local0, 1)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 1)
	}

	CH03("", 0, 0x27d, __LINE__, 0)

	Add(" 	 	 	12345678", 0, Local0)
	if (LNotEqual(Local0, 0x12345678)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x12345678)
	}

	CH03("", 0, 0x27f, __LINE__, 0)

	/*
	 * Implicit String to Integer (<hex-dec>)
	 *
	 * Method(mf99)
	 */

	CH03("", 0, 0x280, __LINE__, 0)

	// Hex: 0x - dec

	Add("				1234567890123456", 0, Local0)
	if (F64) {
		if (LNotEqual(Local0, 0x1234567890123456)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1234567890123456)
		}
	} else {
		if (LNotEqual(Local0, 0x12345678)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x12345678)
		}
	}

	// Hex: 0x - hex

	Add("				abcdefef", 0, Local0)
	if (LNotEqual(Local0, 0xabcdefef)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0xabcdefef)
	}

	Add("     abcdefe", 0, Local0)
	if (LNotEqual(Local0, 0xabcdefe)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0xabcdefe)
	}

	Add("             abcdefefadefbcdf", 0, Local0)
	if (F64) {
		if (LNotEqual(Local0, 0xabcdefefadefbcdf)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0xabcdefefadefbcdf)
		}
	} else {
		if (LNotEqual(Local0, 0xabcdefef)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0xabcdefef)
		}
	}

	// Hex: 0x - dec/hex

	Add("	     			 	   1ab2cd340fe05678", 0, Local0)
	if (F64) {
		if (LNotEqual(Local0, 0x1ab2cd340fe05678)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1ab2cd340fe05678)
		}
	} else {
		if (LNotEqual(Local0, 0x1ab2cd34)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1ab2cd34)
		}
	}

	Add(" 1ab2cd340fe05", 0, Local0)
	if (F64) {
		if (LNotEqual(Local0, 0x1ab2cd340fe05)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1ab2cd340fe05)
		}
	} else {
		if (LNotEqual(Local0, 0x1ab2cd34)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1ab2cd34)
		}
	}

	Add("	1a", 0, Local0)
	if (LNotEqual(Local0, 0x1a)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1a)
	}

	CH03("", 0, 0x28d, __LINE__, 0)

	/*
	 * No exceptions in special cases which force exceptions on ToInteger
	 *
	 * Method(mf9a)
	 */

	// 5. "1234cd" (non-decimal character in dec-image)
	CH03("", 0, 0x28e, __LINE__, 0)
	Add("	1234cd", 0, Local0)
	if (LNotEqual(Local0, 0x1234cd)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1234cd)
	}

	// 6. "000x1234" (non-decimal character in dec-image)
	CH03("", 0, 0x290, __LINE__, 0)
	Add(" 	 			 000x1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 7. "0x1234cdQ" (non-hex character in '0x'-image)
	CH03("", 0, 0x292, __LINE__, 0)
	Add(" 	  				 0x1234cdQ", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}
	CH03("", 0, 0x294, __LINE__, 0)
	Add(" 1234cdQ", 0, Local0)
	if (LNotEqual(Local0, 0x1234cd)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1234cd)
	}

	CH03("", 0, 0x296, __LINE__, 0)
	Add("   		0x0x12345", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 8. "1234 " (white space in dec image)
	CH03("", 0, 0x298, __LINE__, 0)
	Add("   		1234 ", 0, Local0)
	if (LNotEqual(Local0, 0x1234)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1234)
	}

	// 9. "0x1234cd " (white space in '0x'-image)
	CH03("", 0, 0x29a, __LINE__, 0)
	Add("			  1234cd ", 0, Local0)
	if (LNotEqual(Local0, 0x1234cd)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1234cd)
	}

	// 10. "0x 1234cdQ" (white space after '0x')
	CH03("", 0, 0x29c, __LINE__, 0)
	Add("				   	 	 		0x 1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x29e, __LINE__, 0)
	Add(" 	   	 		 	0x0x 1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x2a0, __LINE__, 0)
	Add(" 	 	 	    		0x0x 0x 1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x2a2, __LINE__, 0)
	Add("	 	    	      		 0x 0x 1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 11. (decimal image exceeding maximal)
	//     32-bit mode – the value exceeding "4294967295"
	if (1) {
		CH03("", 0, 0x2a4, __LINE__, 0)
		Add("		4294967296", 0, Local0)
		if (F64) {
			if (LNotEqual(Local0, 0x4294967296)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x4294967296)
			}
		} else {
			if (LNotEqual(Local0, 0x42949672)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x42949672)
			}
		}

		CH03("", 0, 0x2a7, __LINE__, 0)
		Add("    		    			123456789012345678904294967296", 0, Local0)
		if (F64) {
			if (LNotEqual(Local0, 0x1234567890123456)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x1234567890123456)
			}
		} else {
			if (LNotEqual(Local0, 0x12345678)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x12345678)
			}
		}

		CH03("", 0, 0x2aa, __LINE__, 0)
		Add(" 	 		00004294967296", 0, Local0)
		if (F64) {
			if (LNotEqual(Local0, 0x4294967296)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x4294967296)
			}
		} else {
			if (LNotEqual(Local0, 0x42949672)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x42949672)
			}
		}

		CH03("", 0, 0x2ad, __LINE__, 0)
		Add("	0123456789012345678904294967296", 0, Local0)
		if (F64) {
			if (LNotEqual(Local0, 0x1234567890123456)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x1234567890123456)
			}
		} else {
			if (LNotEqual(Local0, 0x12345678)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x12345678)
			}
		}

		CH03("", 0, 0x2b0, __LINE__, 0)
		Add("	0123456789012345678904294967296", 0, Local0)
		if (F64) {
			if (LNotEqual(Local0, 0x1234567890123456)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x1234567890123456)
			}
		} else {
			if (LNotEqual(Local0, 0x12345678)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x12345678)
			}
		}

		CH03("", 0, 0x2b3, __LINE__, 0)
		Add(" 123456789012345678904294967296", 0, Local0)
		if (F64) {
			if (LNotEqual(Local0, 0x1234567890123456)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x1234567890123456)
			}
		} else {
			if (LNotEqual(Local0, 0x12345678)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x12345678)
			}
		}

		CH03("", 0, 0x2b6, __LINE__, 0)
		Add("	123456789012345678904294967296", 0, Local0)
		if (F64) {
			if (LNotEqual(Local0, 0x1234567890123456)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x1234567890123456)
			}
		} else {
			if (LNotEqual(Local0, 0x12345678)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x12345678)
			}
		}
	}

	//     64-bit mode – the value exceeding "18446744073709551615"
	CH03("", 0, 0x2b8, __LINE__, 0)
	Add("			18446744073709551616", 0, Local0)
	if (F64) {
		if (LNotEqual(Local0, 0x1844674407370955)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1844674407370955)
		}
	} else {
		if (LNotEqual(Local0, 0x18446744)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x18446744)
		}
	}

	CH03("", 0, 0x2bb, __LINE__, 0)
	Add("	18446744073709551616", 0, Local0)
	if (F64) {
		if (LNotEqual(Local0, 0x1844674407370955)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1844674407370955)
		}
	} else {
		if (LNotEqual(Local0, 0x18446744)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x18446744)
		}
	}

	CH03("", 0, 0x2be, __LINE__, 0)
	Add(" 18446744073709551616", 0, Local0)
	if (F64) {
		if (LNotEqual(Local0, 0x1844674407370955)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1844674407370955)
		}
	} else {
		if (LNotEqual(Local0, 0x18446744)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x18446744)
		}
	}

	CH03("", 0, 0x2c1, __LINE__, 0)
	Add("   	018446744073709551616", 0, Local0)
	if (F64) {
		if (LNotEqual(Local0, 0x1844674407370955)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1844674407370955)
		}
	} else {
		if (LNotEqual(Local0, 0x18446744)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x18446744)
		}
	}

	CH03("", 0, 0x2c4, __LINE__, 0)
	Add(" 	000000000018446744073709551616", 0, Local0)
	if (F64) {
		if (LNotEqual(Local0, 0x1844674407370955)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1844674407370955)
		}
	} else {
		if (LNotEqual(Local0, 0x18446744)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x18446744)
		}
	}

	// 12. "0x12345678901234567" (hex image exceeding maximal)
	CH03("", 0, 0x2c7, __LINE__, 0)
	Add("		0x12345678901234567", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 13. "0x00000000000001234" (hex image exceeding maximal; no matter that zeros)
	CH03("", 0, 0x2ca, __LINE__, 0)
	Add("           0x00000000000001234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x2cc, __LINE__, 0)
	Add("          		0x0000000000000000000001234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 14. "0x123456789" (hex image exceeding maximal; for 32-bit mode only)
	if (1) {
		CH03("", 0, 0x2ce, __LINE__, 0)
		Add("0x123456789", 0, Local0)
		if (LNotEqual(Local0, 0)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0)
		}
	}

	// 15. "0x" (incomplete '0x' image)
	CH03("", 0, 0x2d0, __LINE__, 0)
	Add("	0x", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}
	CH03("", 0, 0x2d2, __LINE__, 0)

	Add(" 0x", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}
	CH03("", 0, 0x2d4, __LINE__, 0)
}

/*
 * 4. "0000000000000000000000001234"
 * (zeros before significant characters in image without '0x' are skipped).
 *
 * Exampples: mf9b + 000000000
 *
 * All the above examples but
 *
 *    with the white space before image of Data
 *  + 000000000 zeros before image
 */
Method(mf9c) {

	// Hex: 0x - dec

	CH03("", 0, 0x367, __LINE__, 0)

	Add(" 0000000000x0", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	Add("	0000000000x1", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	Add("	 0000000000x12345678", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	Add(" 	0000000000x1234567890123456", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// Hex: 0x - hex

	Add("  0000000000xabcdefef", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	Add("		0000000000xabcdefefadefbcdf", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// Hex: 0x - dec/hex

	Add(" 	 	 	 	 	0000000000x1ab2cd340fe05678", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x36f, __LINE__, 0)
	Add("	 	 	 	 	 	0000000000x1ab2cd340fe0567823456789123456789987", 0, Local0)
	CH03("", 0, 0x370, __LINE__, 0)

	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x372, __LINE__, 0)

	/*
	 * Implicit String to Integer (<dec>)
	 *
	 * Method(mf98)
	 */

	CH03("", 0, 0x373, __LINE__, 0)

	Add("                       0000000000", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x375, __LINE__, 0)

	Add("						0000000000000000", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x377, __LINE__, 0)

	Add("                                 000000000000000000000000000000000000000", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x379, __LINE__, 0)

	Add("							000000000000000000000000000000000000000", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x37b, __LINE__, 0)

	Add(" 		 0000000001", 0, Local0)
	if (LNotEqual(Local0, 1)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 1)
	}

	CH03("", 0, 0x37d, __LINE__, 0)

	Add(" 	 	 	00000000012345678", 0, Local0)
	if (LNotEqual(Local0, 0x12345678)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x12345678)
	}

	CH03("", 0, 0x37f, __LINE__, 0)

	/*
	 * Implicit String to Integer (<hex-dec>)
	 *
	 * Method(mf99)
	 */

	CH03("", 0, 0x380, __LINE__, 0)

	// Hex: 0x - dec

	Add("				0000000001234567890123456", 0, Local0)
	if (F64) {
		if (LNotEqual(Local0, 0x1234567890123456)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1234567890123456)
		}
	} else {
		if (LNotEqual(Local0, 0x12345678)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x12345678)
		}
	}

	// Hex: 0x - hex

	Add("				000000000abcdefef", 0, Local0)
	if (LNotEqual(Local0, 0xabcdefef)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0xabcdefef)
	}

	Add("     000000000abcdefe", 0, Local0)
	if (LNotEqual(Local0, 0xabcdefe)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0xabcdefe)
	}

	Add("             000000000abcdefefadefbcdf", 0, Local0)
	if (F64) {
		if (LNotEqual(Local0, 0xabcdefefadefbcdf)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0xabcdefefadefbcdf)
		}
	} else {
		if (LNotEqual(Local0, 0xabcdefef)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0xabcdefef)
		}
	}

	// Hex: 0x - dec/hex

	Add("	     			 	   0000000001ab2cd340fe05678", 0, Local0)
	if (F64) {
		if (LNotEqual(Local0, 0x1ab2cd340fe05678)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1ab2cd340fe05678)
		}
	} else {
		if (LNotEqual(Local0, 0x1ab2cd34)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1ab2cd34)
		}
	}

	Add(" 0000000001ab2cd340fe05", 0, Local0)
	if (F64) {
		if (LNotEqual(Local0, 0x1ab2cd340fe05)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1ab2cd340fe05)
		}
	} else {
		if (LNotEqual(Local0, 0x1ab2cd34)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1ab2cd34)
		}
	}

	Add("	0000000001a", 0, Local0)
	if (LNotEqual(Local0, 0x1a)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1a)
	}

	CH03("", 0, 0x38d, __LINE__, 0)

	/*
	 * No exceptions in special cases which force exceptions on ToInteger
	 *
	 * Method(mf9a)
	 */

	// 5. "1234cd" (non-decimal character in dec-image)
	CH03("", 0, 0x38e, __LINE__, 0)
	Add("	0000000001234cd", 0, Local0)
	if (LNotEqual(Local0, 0x1234cd)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1234cd)
	}

	// 6. "000x1234" (non-decimal character in dec-image)
	CH03("", 0, 0x390, __LINE__, 0)
	Add(" 	 			 000000000000x1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 7. "0x1234cdQ" (non-hex character in '0x'-image)
	CH03("", 0, 0x392, __LINE__, 0)
	Add(" 	  				 0000000000x1234cdQ", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}
	CH03("", 0, 0x394, __LINE__, 0)
	Add(" 0000000001234cdQ", 0, Local0)
	if (LNotEqual(Local0, 0x1234cd)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1234cd)
	}

	CH03("", 0, 0x396, __LINE__, 0)
	Add("   		0000000000x0x12345", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 8. "1234 " (white space in dec image)
	CH03("", 0, 0x398, __LINE__, 0)
	Add("   		0000000001234 ", 0, Local0)
	if (LNotEqual(Local0, 0x1234)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1234)
	}

	// 9. "0x1234cd " (white space in '0x'-image)
	CH03("", 0, 0x39a, __LINE__, 0)
	Add("			  0000000001234cd ", 0, Local0)
	if (LNotEqual(Local0, 0x1234cd)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1234cd)
	}

	// 10. "0x 1234cdQ" (white space after '0x')
	CH03("", 0, 0x39c, __LINE__, 0)
	Add("				   	 	 		0000000000x 1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x39e, __LINE__, 0)
	Add(" 	   	 		 	0000000000x0x 1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x3a0, __LINE__, 0)
	Add(" 	 	 	    		0000000000x0x 0x 1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x3a2, __LINE__, 0)
	Add("	 	    	      		 0000000000x 0x 1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 11. (decimal image exceeding maximal)
	//     32-bit mode – the value exceeding "4294967295"
	if (1) {
		CH03("", 0, 0x3a4, __LINE__, 0)
		Add("		0000000004294967296", 0, Local0)
		if (F64) {
			if (LNotEqual(Local0, 0x4294967296)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x4294967296)
			}
		} else {
			if (LNotEqual(Local0, 0x42949672)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x42949672)
			}
		}

		CH03("", 0, 0x3a7, __LINE__, 0)
		Add("    		    			000000000123456789012345678904294967296", 0, Local0)
		if (F64) {
			if (LNotEqual(Local0, 0x1234567890123456)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x1234567890123456)
			}
		} else {
			if (LNotEqual(Local0, 0x12345678)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x12345678)
			}
		}

		CH03("", 0, 0x3aa, __LINE__, 0)
		Add(" 	 		00000000000004294967296", 0, Local0)
		if (F64) {
			if (LNotEqual(Local0, 0x4294967296)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x4294967296)
			}
		} else {
			if (LNotEqual(Local0, 0x42949672)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x42949672)
			}
		}

		CH03("", 0, 0x3ad, __LINE__, 0)
		Add("	0000000000123456789012345678904294967296", 0, Local0)
		if (F64) {
			if (LNotEqual(Local0, 0x1234567890123456)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x1234567890123456)
			}
		} else {
			if (LNotEqual(Local0, 0x12345678)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x12345678)
			}
		}

		CH03("", 0, 0x3b0, __LINE__, 0)
		Add("	0000000000123456789012345678904294967296", 0, Local0)
		if (F64) {
			if (LNotEqual(Local0, 0x1234567890123456)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x1234567890123456)
			}
		} else {
			if (LNotEqual(Local0, 0x12345678)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x12345678)
			}
		}

		CH03("", 0, 0x3b3, __LINE__, 0)
		Add(" 000000000123456789012345678904294967296", 0, Local0)
		if (F64) {
			if (LNotEqual(Local0, 0x1234567890123456)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x1234567890123456)
			}
		} else {
			if (LNotEqual(Local0, 0x12345678)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x12345678)
			}
		}

		CH03("", 0, 0x3b6, __LINE__, 0)
		Add("	000000000123456789012345678904294967296", 0, Local0)
		if (F64) {
			if (LNotEqual(Local0, 0x1234567890123456)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x1234567890123456)
			}
		} else {
			if (LNotEqual(Local0, 0x12345678)) {
				err("", zFFF, __LINE__, 0, 0, Local0, 0x12345678)
			}
		}
	}

	//     64-bit mode – the value exceeding "18446744073709551615"
	CH03("", 0, 0x3b8, __LINE__, 0)
	Add("			00000000018446744073709551616", 0, Local0)
	if (F64) {
		if (LNotEqual(Local0, 0x1844674407370955)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1844674407370955)
		}
	} else {
		if (LNotEqual(Local0, 0x18446744)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x18446744)
		}
	}

	CH03("", 0, 0x3bb, __LINE__, 0)
	Add("	00000000018446744073709551616", 0, Local0)
	if (F64) {
		if (LNotEqual(Local0, 0x1844674407370955)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1844674407370955)
		}
	} else {
		if (LNotEqual(Local0, 0x18446744)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x18446744)
		}
	}

	CH03("", 0, 0x3be, __LINE__, 0)
	Add(" 00000000018446744073709551616", 0, Local0)
	if (F64) {
		if (LNotEqual(Local0, 0x1844674407370955)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1844674407370955)
		}
	} else {
		if (LNotEqual(Local0, 0x18446744)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x18446744)
		}
	}

	CH03("", 0, 0x3c1, __LINE__, 0)
	Add("   	000000000018446744073709551616", 0, Local0)
	if (F64) {
		if (LNotEqual(Local0, 0x1844674407370955)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1844674407370955)
		}
	} else {
		if (LNotEqual(Local0, 0x18446744)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x18446744)
		}
	}

	CH03("", 0, 0x3c4, __LINE__, 0)
	Add(" 	000000000000000000018446744073709551616", 0, Local0)
	if (F64) {
		if (LNotEqual(Local0, 0x1844674407370955)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x1844674407370955)
		}
	} else {
		if (LNotEqual(Local0, 0x18446744)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0x18446744)
		}
	}

	// 12. "0x12345678901234567" (hex image exceeding maximal)
	CH03("", 0, 0x3c7, __LINE__, 0)
	Add("		0000000000x12345678901234567", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 13. "0x00000000000001234" (hex image exceeding maximal; no matter that zeros)
	CH03("", 0, 0x3ca, __LINE__, 0)
	Add("           0000000000x00000000000001234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x3cc, __LINE__, 0)
	Add("          		0000000000x0000000000000000000001234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 14. "0x123456789" (hex image exceeding maximal; for 32-bit mode only)
	if (1) {
		CH03("", 0, 0x3ce, __LINE__, 0)
		Add("0x123456789", 0, Local0)
		if (LNotEqual(Local0, 0)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0)
		}
	}

	// 15. "0x" (incomplete '0x' image)
	CH03("", 0, 0x3d0, __LINE__, 0)
	Add("	0000000000x", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}
	CH03("", 0, 0x3d2, __LINE__, 0)

	Add(" 0000000000x", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}
	CH03("", 0, 0x3d4, __LINE__, 0)
}
