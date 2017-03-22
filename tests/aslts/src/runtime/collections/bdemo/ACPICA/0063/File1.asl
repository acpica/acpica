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

	CH03("", 0, 0x200, 0, 0)

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

	CH03("", 0, 0x208, 0, 0)
	Add("0x1ab2cd340fe0567823456789123456789987", 0, Local0)
	CH03("", 0, 0x209, 0, 0)

	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x20b, 0, 0)
}

/*
 * Implicit String to Integer (<dec>)
 */
Method(mf98) {

	CH03("", 0, 0x200, 0, 0)

	Add("0", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x201, 0, 0)

	Add("0000000", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x202, 0, 0)

	Add("000000000000000000000000000000", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x203, 0, 0)

	Add("1", 0, Local0)
	if (LNotEqual(Local0, 1)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 1)
	}

	CH03("", 0, 0x204, 0, 0)

	Add("12345678", 0, Local0)
	if (LNotEqual(Local0, 0x12345678)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x12345678)
	}

	CH03("", 0, 0x205, 0, 0)
}

/*
 * Implicit String to Integer (<hex-dec>)
 */
Method(mf99) {

	CH03("", 0, 0x213, 0, 0)

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

	CH03("", 0, 0x219, 0, 0)
}

/*
 * No exceptions in special cases which force exceptions on ToInteger
 */
Method(mf9a) {

	// 5. "1234cd" (non-decimal character in dec-image)
	CH03("", 0, 0x220, 0, 0)
	Add("1234cd", 0, Local0)
	if (LNotEqual(Local0, 0x1234cd)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1234cd)
	}

	// 6. "000x1234" (non-decimal character in dec-image)
	CH03("", 0, 0x223, 0, 0)
	Add("000x1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 7. "0x1234cdQ" (non-hex character in '0x'-image)
	CH03("", 0, 0x225, 0, 0)
	Add("0x1234cdQ", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}
	CH03("", 0, 0x227, 0, 0)
	Add("1234cdQ", 0, Local0)
	if (LNotEqual(Local0, 0x1234cd)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1234cd)
	}

	CH03("", 0, 0x229, 0, 0)
	Add("0x0x12345", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 8. "1234 " (white space in dec image)
	CH03("", 0, 0x22b, 0, 0)
	Add("1234 ", 0, Local0)
	if (LNotEqual(Local0, 0x1234)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1234)
	}

	// 9. "0x1234cd " (white space in '0x'-image)
	CH03("", 0, 0x22d, 0, 0)
	Add("1234cd ", 0, Local0)
	if (LNotEqual(Local0, 0x1234cd)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1234cd)
	}

	// 10. "0x 1234cdQ" (white space after '0x')
	CH03("", 0, 0x22f, 0, 0)
	Add("0x 1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x231, 0, 0)
	Add("0x0x 1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x233, 0, 0)
	Add("0x0x 0x 1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x235, 0, 0)
	Add("0x 0x 1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 11. (decimal image exceeding maximal)
	//     32-bit mode – the value exceeding "4294967295"
	if (1) {
		CH03("", 0, 0x237, 0, 0)
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

		CH03("", 0, 0x23a, 0, 0)
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

		CH03("", 0, 0x23d, 0, 0)
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

		CH03("", 0, 0x240, 0, 0)
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

		CH03("", 0, 0x243, 0, 0)
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

		CH03("", 0, 0x246, 0, 0)
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

		CH03("", 0, 0x249, 0, 0)
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
	CH03("", 0, 0x24c, 0, 0)
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

	CH03("", 0, 0x24f, 0, 0)
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

	CH03("", 0, 0x252, 0, 0)
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

	CH03("", 0, 0x255, 0, 0)
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

	CH03("", 0, 0x258, 0, 0)
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
	CH03("", 0, 0x25b, 0, 0)
	Add("0x12345678901234567", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 13. "0x00000000000001234" (hex image exceeding maximal; no matter that zeros)
	CH03("", 0, 0x25e, 0, 0)
	Add("0x00000000000001234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x260, 0, 0)
	Add("0x0000000000000000000001234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 14. "0x123456789" (hex image exceeding maximal; for 32-bit mode only)
	if (1) {
		CH03("", 0, 0x262, 0, 0)
		Add("0x123456789", 0, Local0)
		if (LNotEqual(Local0, 0)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0)
		}
	}

	// 15. "0x" (incomplete '0x' image)
	CH03("", 0, 0x264, 0, 0)
	Add("0x", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}
	CH03("", 0, 0x266, 0, 0)
}

/*
 * 2. " 0x1234cd" (white space before image of Data is skipped)
 *
 * All the above examples but with the white space before image of Data.
 */
Method(mf9b) {

	// Hex: 0x - dec

	CH03("", 0, 0x267, 0, 0)

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

	CH03("", 0, 0x26f, 0, 0)
	Add("	 	 	 	 	 	0x1ab2cd340fe0567823456789123456789987", 0, Local0)
	CH03("", 0, 0x270, 0, 0)

	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x272, 0, 0)

	/*
	 * Implicit String to Integer (<dec>)
	 *
	 * Method(mf98)
	 */

	CH03("", 0, 0x273, 0, 0)

	Add("                       0", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x275, 0, 0)

	Add("						0000000", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x277, 0, 0)

	Add("                                 000000000000000000000000000000", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x279, 0, 0)

	Add("							000000000000000000000000000000", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x27b, 0, 0)

	Add(" 		 1", 0, Local0)
	if (LNotEqual(Local0, 1)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 1)
	}

	CH03("", 0, 0x27d, 0, 0)

	Add(" 	 	 	12345678", 0, Local0)
	if (LNotEqual(Local0, 0x12345678)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x12345678)
	}

	CH03("", 0, 0x27f, 0, 0)

	/*
	 * Implicit String to Integer (<hex-dec>)
	 *
	 * Method(mf99)
	 */

	CH03("", 0, 0x280, 0, 0)

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

	CH03("", 0, 0x28d, 0, 0)

	/*
	 * No exceptions in special cases which force exceptions on ToInteger
	 *
	 * Method(mf9a)
	 */

	// 5. "1234cd" (non-decimal character in dec-image)
	CH03("", 0, 0x28e, 0, 0)
	Add("	1234cd", 0, Local0)
	if (LNotEqual(Local0, 0x1234cd)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1234cd)
	}

	// 6. "000x1234" (non-decimal character in dec-image)
	CH03("", 0, 0x290, 0, 0)
	Add(" 	 			 000x1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 7. "0x1234cdQ" (non-hex character in '0x'-image)
	CH03("", 0, 0x292, 0, 0)
	Add(" 	  				 0x1234cdQ", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}
	CH03("", 0, 0x294, 0, 0)
	Add(" 1234cdQ", 0, Local0)
	if (LNotEqual(Local0, 0x1234cd)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1234cd)
	}

	CH03("", 0, 0x296, 0, 0)
	Add("   		0x0x12345", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 8. "1234 " (white space in dec image)
	CH03("", 0, 0x298, 0, 0)
	Add("   		1234 ", 0, Local0)
	if (LNotEqual(Local0, 0x1234)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1234)
	}

	// 9. "0x1234cd " (white space in '0x'-image)
	CH03("", 0, 0x29a, 0, 0)
	Add("			  1234cd ", 0, Local0)
	if (LNotEqual(Local0, 0x1234cd)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1234cd)
	}

	// 10. "0x 1234cdQ" (white space after '0x')
	CH03("", 0, 0x29c, 0, 0)
	Add("				   	 	 		0x 1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x29e, 0, 0)
	Add(" 	   	 		 	0x0x 1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x2a0, 0, 0)
	Add(" 	 	 	    		0x0x 0x 1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x2a2, 0, 0)
	Add("	 	    	      		 0x 0x 1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 11. (decimal image exceeding maximal)
	//     32-bit mode – the value exceeding "4294967295"
	if (1) {
		CH03("", 0, 0x2a4, 0, 0)
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

		CH03("", 0, 0x2a7, 0, 0)
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

		CH03("", 0, 0x2aa, 0, 0)
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

		CH03("", 0, 0x2ad, 0, 0)
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

		CH03("", 0, 0x2b0, 0, 0)
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

		CH03("", 0, 0x2b3, 0, 0)
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

		CH03("", 0, 0x2b6, 0, 0)
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
	CH03("", 0, 0x2b8, 0, 0)
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

	CH03("", 0, 0x2bb, 0, 0)
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

	CH03("", 0, 0x2be, 0, 0)
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

	CH03("", 0, 0x2c1, 0, 0)
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

	CH03("", 0, 0x2c4, 0, 0)
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
	CH03("", 0, 0x2c7, 0, 0)
	Add("		0x12345678901234567", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 13. "0x00000000000001234" (hex image exceeding maximal; no matter that zeros)
	CH03("", 0, 0x2ca, 0, 0)
	Add("           0x00000000000001234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x2cc, 0, 0)
	Add("          		0x0000000000000000000001234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 14. "0x123456789" (hex image exceeding maximal; for 32-bit mode only)
	if (1) {
		CH03("", 0, 0x2ce, 0, 0)
		Add("0x123456789", 0, Local0)
		if (LNotEqual(Local0, 0)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0)
		}
	}

	// 15. "0x" (incomplete '0x' image)
	CH03("", 0, 0x2d0, 0, 0)
	Add("	0x", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}
	CH03("", 0, 0x2d2, 0, 0)

	Add(" 0x", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}
	CH03("", 0, 0x2d4, 0, 0)
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

	CH03("", 0, 0x367, 0, 0)

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

	CH03("", 0, 0x36f, 0, 0)
	Add("	 	 	 	 	 	0000000000x1ab2cd340fe0567823456789123456789987", 0, Local0)
	CH03("", 0, 0x370, 0, 0)

	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x372, 0, 0)

	/*
	 * Implicit String to Integer (<dec>)
	 *
	 * Method(mf98)
	 */

	CH03("", 0, 0x373, 0, 0)

	Add("                       0000000000", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x375, 0, 0)

	Add("						0000000000000000", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x377, 0, 0)

	Add("                                 000000000000000000000000000000000000000", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x379, 0, 0)

	Add("							000000000000000000000000000000000000000", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x37b, 0, 0)

	Add(" 		 0000000001", 0, Local0)
	if (LNotEqual(Local0, 1)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 1)
	}

	CH03("", 0, 0x37d, 0, 0)

	Add(" 	 	 	00000000012345678", 0, Local0)
	if (LNotEqual(Local0, 0x12345678)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x12345678)
	}

	CH03("", 0, 0x37f, 0, 0)

	/*
	 * Implicit String to Integer (<hex-dec>)
	 *
	 * Method(mf99)
	 */

	CH03("", 0, 0x380, 0, 0)

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

	CH03("", 0, 0x38d, 0, 0)

	/*
	 * No exceptions in special cases which force exceptions on ToInteger
	 *
	 * Method(mf9a)
	 */

	// 5. "1234cd" (non-decimal character in dec-image)
	CH03("", 0, 0x38e, 0, 0)
	Add("	0000000001234cd", 0, Local0)
	if (LNotEqual(Local0, 0x1234cd)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1234cd)
	}

	// 6. "000x1234" (non-decimal character in dec-image)
	CH03("", 0, 0x390, 0, 0)
	Add(" 	 			 000000000000x1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 7. "0x1234cdQ" (non-hex character in '0x'-image)
	CH03("", 0, 0x392, 0, 0)
	Add(" 	  				 0000000000x1234cdQ", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}
	CH03("", 0, 0x394, 0, 0)
	Add(" 0000000001234cdQ", 0, Local0)
	if (LNotEqual(Local0, 0x1234cd)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1234cd)
	}

	CH03("", 0, 0x396, 0, 0)
	Add("   		0000000000x0x12345", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 8. "1234 " (white space in dec image)
	CH03("", 0, 0x398, 0, 0)
	Add("   		0000000001234 ", 0, Local0)
	if (LNotEqual(Local0, 0x1234)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1234)
	}

	// 9. "0x1234cd " (white space in '0x'-image)
	CH03("", 0, 0x39a, 0, 0)
	Add("			  0000000001234cd ", 0, Local0)
	if (LNotEqual(Local0, 0x1234cd)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0x1234cd)
	}

	// 10. "0x 1234cdQ" (white space after '0x')
	CH03("", 0, 0x39c, 0, 0)
	Add("				   	 	 		0000000000x 1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x39e, 0, 0)
	Add(" 	   	 		 	0000000000x0x 1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x3a0, 0, 0)
	Add(" 	 	 	    		0000000000x0x 0x 1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x3a2, 0, 0)
	Add("	 	    	      		 0000000000x 0x 1234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 11. (decimal image exceeding maximal)
	//     32-bit mode – the value exceeding "4294967295"
	if (1) {
		CH03("", 0, 0x3a4, 0, 0)
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

		CH03("", 0, 0x3a7, 0, 0)
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

		CH03("", 0, 0x3aa, 0, 0)
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

		CH03("", 0, 0x3ad, 0, 0)
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

		CH03("", 0, 0x3b0, 0, 0)
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

		CH03("", 0, 0x3b3, 0, 0)
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

		CH03("", 0, 0x3b6, 0, 0)
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
	CH03("", 0, 0x3b8, 0, 0)
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

	CH03("", 0, 0x3bb, 0, 0)
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

	CH03("", 0, 0x3be, 0, 0)
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

	CH03("", 0, 0x3c1, 0, 0)
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

	CH03("", 0, 0x3c4, 0, 0)
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
	CH03("", 0, 0x3c7, 0, 0)
	Add("		0000000000x12345678901234567", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 13. "0x00000000000001234" (hex image exceeding maximal; no matter that zeros)
	CH03("", 0, 0x3ca, 0, 0)
	Add("           0000000000x00000000000001234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	CH03("", 0, 0x3cc, 0, 0)
	Add("          		0000000000x0000000000000000000001234", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}

	// 14. "0x123456789" (hex image exceeding maximal; for 32-bit mode only)
	if (1) {
		CH03("", 0, 0x3ce, 0, 0)
		Add("0x123456789", 0, Local0)
		if (LNotEqual(Local0, 0)) {
			err("", zFFF, __LINE__, 0, 0, Local0, 0)
		}
	}

	// 15. "0x" (incomplete '0x' image)
	CH03("", 0, 0x3d0, 0, 0)
	Add("	0000000000x", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}
	CH03("", 0, 0x3d2, 0, 0)

	Add(" 0000000000x", 0, Local0)
	if (LNotEqual(Local0, 0)) {
		err("", zFFF, __LINE__, 0, 0, Local0, 0)
	}
	CH03("", 0, 0x3d4, 0, 0)
}
