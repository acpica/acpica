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
 *  Package
 *
 * (verify exceptions caused by the imprope use of Package type objects)
 */

Name(z096, 96)

Name(p100, Package(){0x61})

// Expected exceptions:
//
// 47 - AE_AML_OPERAND_TYPE
// Note: Package can be used with Index
Method(m4b4, 1)
{
	Name(ts, "m4b4")

	Name(p000, Package(){0x62})

	Event(e000)

	Name(i000, 0)

	// Local Named Object
	// ASL compiler prohibits to use Pakage
	// Named Objects in the most of operators
	Method(m000, 1)
	{
		Name(p000, Package(){0x63})

		// CondRefOf
		
		CondRefOf(p000)
		CH03(ts, z096, 0, 0, 0)

		CondRefOf(p000, Local1)
		CH03(ts, z096, 1, 0, 0)

		// CopyObject

		CopyObject(p000, Local1)
		CH03(ts, z096, 2, 0, 0)

		// Decrement

		// DerefOf

		if (y083) {
			DerefOf(p000)
			CH06(arg0, 0, 47)
		}

		// FindSetLeftBit

		// FindSetRightBit

		// FromBCD

		// Increment

		// LNot

		// Not

		// ObjectType

		ObjectType(p000)
		CH03(ts, z096, 3, 0, 0)

		// RefOf

		RefOf(p000)
		CH03(ts, z096, 4, 0, 0)

		// Release

		// Reset

		// Signal

		// SizeOf

		SizeOf(p000)
		CH03(ts, z096, 5, 0, 0)

		// Sleep

		// Stall

		// Store

		Store(p000, Local1)
		CH03(ts, z096, 6, 0, 0)

		// ToBCD

		// ToBuffer

		// ToDecimalString

		// ToHexString

		// ToInteger

		// Acquire

		// Add

		// And

		// Concatenate

		// ConcatenateResTemplate

		// Divide

		// Fatal

		// Index

		Index(p000, 0)
		CH03(ts, z096, 7, 0, 0)

		Index(p000, 0, Local1)
		CH03(ts, z096, 8, 0, 0)

		// LEqual

		// LGreater

		// LGreaterEqual

		// LLess

		// LLessEqual

		// LNotEqual

		// LOr

		// Mod

		// Multiply

		// NAnd

		// NOr

		// Or

		// ShiftLeft

		// ShiftRight

		// Subtract

		// ToString

		// Wait

		// XOr

		// Mid

		// Match

		Match(p000, MTR, 0, MTR, 0, 0)
		CH03(ts, z096, 9, 0, 0)
	}

	// Global Named Object
	Method(m001, 1)
	{
		// CondRefOf
		
		CondRefOf(p100)
		CH03(ts, z096, 10, 0, 0)

		CondRefOf(p100, Local1)
		CH03(ts, z096, 11, 0, 0)

		// CopyObject

		CopyObject(p100, Local1)
		CH03(ts, z096, 12, 0, 0)

		// Decrement

		// DerefOf

		if (y083) {
			DerefOf(p100)
			CH06(arg0, 1, 47)
		}

		// FindSetLeftBit

		// FindSetRightBit

		// FromBCD

		// Increment

		// LNot

		// Not

		// ObjectType

		ObjectType(p100)
		CH03(ts, z096, 13, 0, 0)

		// RefOf

		RefOf(p100)
		CH03(ts, z096, 14, 0, 0)

		// Release

		// Reset

		// Signal

		// SizeOf

		SizeOf(p100)
		CH03(ts, z096, 15, 0, 0)

		// Sleep

		// Stall

		// Store

		Store(p100, Local1)
		CH03(ts, z096, 16, 0, 0)

		// ToBCD

		// ToBuffer

		// ToDecimalString

		// ToHexString

		// ToInteger

		// Acquire

		// Add

		// And

		// Concatenate

		// ConcatenateResTemplate

		// Divide

		// Fatal

		// Index

		Index(p100, 0)
		CH03(ts, z096, 17, 0, 0)

		Index(p100, 0, Local1)
		CH03(ts, z096, 18, 0, 0)

		// LEqual

		// LGreater

		// LGreaterEqual

		// LLess

		// LLessEqual

		// LNotEqual

		// LOr

		// Mod

		// Multiply

		// NAnd

		// NOr

		// Or

		// ShiftLeft

		// ShiftRight

		// Subtract

		// ToString

		// Wait

		// XOr

		// Mid

		// Match

		Match(p100, MTR, 0, MTR, 0, 0)
		CH03(ts, z096, 19, 0, 0)
	}

	// Argument
	Method(m002, 2)
	{
		Event(e000)

		// CondRefOf
		
		CondRefOf(arg1)
		CH03(ts, z096, 20, 0, 0)

		CondRefOf(arg1, Local1)
		CH03(ts, z096, 21, 0, 0)

		// CopyObject

		CopyObject(arg1, Local1)
		CH03(ts, z096, 22, 0, 0)

		// Decrement

		Decrement(arg1)
		CH06(arg0, 2, 47)

		// DerefOf

		DerefOf(arg1)
		CH06(arg0, 3, 47)

		// FindSetLeftBit

		FindSetLeftBit(arg1)
		CH06(arg0, 4, 47)

		FindSetLeftBit(arg1, Local1)
		CH06(arg0, 5, 47)

		// FindSetRightBit

		FindSetRightBit(arg1)
		CH06(arg0, 6, 47)

		FindSetRightBit(arg1, Local1)
		CH06(arg0, 7, 47)

		// FromBCD

		FromBCD(arg1)
		CH06(arg0, 8, 47)

		FromBCD(arg1, Local1)
		CH06(arg0, 9, 47)

		// Increment

		Increment(arg1)
		CH06(arg0, 10, 47)

		// LNot

		LNot(arg1)
		CH06(arg0, 11, 47)

		// Not

		Not(arg1)
		CH06(arg0, 12, 47)

		Not(arg1, Local1)
		CH06(arg0, 13, 47)

		// ObjectType

		ObjectType(arg1)
		CH03(ts, z096, 23, 0, 0)

		// RefOf

		RefOf(arg1)
		CH03(ts, z096, 24, 0, 0)

		// Release

		Release(arg1)
		CH06(arg0, 14, 47)

		// Reset

		Reset(arg1)
		CH06(arg0, 15, 47)

		// Signal

		Signal(arg1)
		CH06(arg0, 16, 47)

		// SizeOf

		SizeOf(arg1)
		CH03(ts, z096, 25, 0, 0)

		// Sleep

		Sleep(arg1)
		CH06(arg0, 17, 47)

		// Stall

		Stall(arg1)
		CH06(arg0, 18, 47)

		// Store

		Store(arg1, Local1)
		CH03(ts, z096, 26, 0, 0)

		// ToBCD

		ToBCD(arg1)
		CH06(arg0, 20, 47)

		ToBCD(arg1, Local1)
		CH06(arg0, 21, 47)

		// ToBuffer

		ToBuffer(arg1)
		CH06(arg0, 22, 47)

		ToBuffer(arg1, Local1)
		CH06(arg0, 23, 47)

		// ToDecimalString

		ToDecimalString(arg1)
		CH06(arg0, 24, 47)

		ToDecimalString(arg1, Local1)
		CH06(arg0, 25, 47)

		// ToHexString

		ToHexString(arg1)
		CH06(arg0, 26, 47)

		ToHexString(arg1, Local1)
		CH06(arg0, 27, 47)

		// ToInteger

		ToInteger(arg1)
		CH06(arg0, 28, 47)

		ToInteger(arg1, Local1)
		CH06(arg0, 29, 47)

		// Acquire

		Acquire(arg1, 100)
		CH06(arg0, 30, 47)

		// Add

		Add(arg1, i000)
		CH06(arg0, 31, 47)

		Add(i000, arg1)
		CH06(arg0, 32, 47)

		Add(arg1, i000, Local1)
		CH06(arg0, 33, 47)

		Add(i000, arg1, Local1)
		CH06(arg0, 34, 47)

		// And

		And(arg1, i000)
		CH06(arg0, 35, 47)

		And(i000, arg1)
		CH06(arg0, 36, 47)

		And(arg1, i000, Local1)
		CH06(arg0, 37, 47)

		And(i000, arg1, Local1)
		CH06(arg0, 38, 47)

		// Concatenate

		Concatenate(arg1, i000)
		CH06(arg0, 39, 47)

		Concatenate(i000, arg1)
		CH06(arg0, 40, 47)

		Concatenate(arg1, i000, Local1)
		CH06(arg0, 41, 47)

		Concatenate(i000, arg1, Local1)
		CH06(arg0, 42, 47)

		// ConcatenateResTemplate

		ConcatenateResTemplate(arg1, ResourceTemplate(){})
		CH06(arg0, 43, 47)

		ConcatenateResTemplate(ResourceTemplate(){}, arg1)
		CH06(arg0, 44, 47)

		ConcatenateResTemplate(arg1, ResourceTemplate(){}, Local1)
		CH06(arg0, 45, 47)

		ConcatenateResTemplate(ResourceTemplate(){}, arg1, Local1)
		CH06(arg0, 46, 47)

		// Divide

		Divide(arg1, i000)
		CH06(arg0, 47, 47)

		Divide(i000, arg1)
		CH06(arg0, 48, 47)

		Divide(arg1, i000, Local2)
		CH06(arg0, 49, 47)

		Divide(i000, arg1, Local2)
		CH06(arg0, 50, 47)

		Divide(arg1, i000, Local2, Local1)
		CH06(arg0, 51, 47)

		Divide(i000, arg1, Local2, Local1)
		CH06(arg0, 52, 47)

		// Fatal

		Fatal(0xff, 0xffffffff, arg1)
		CH06(arg0, 53, 47)

		// Index

		Index(arg1, 0)
		CH03(ts, z096, 27, 0, 0)

		Index("0", arg1)
		CH06(arg0, 55, 47)

		Index(arg1, 0, Local1)
		CH03(ts, z096, 28, 0, 0)

		Index("0", arg1, Local1)
		CH06(arg0, 57, 47)

		// LEqual

		LEqual(arg1, i000)
		CH06(arg0, 58, 47)

		LEqual(i000, arg1)
		CH06(arg0, 59, 47)

		// LGreater

		LGreater(arg1, i000)
		CH06(arg0, 60, 47)

		LGreater(i000, arg1)
		CH06(arg0, 61, 47)

		// LGreaterEqual

		LGreaterEqual(arg1, i000)
		CH06(arg0, 62, 0xff)

		LGreaterEqual(i000, arg1)
		CH06(arg0, 63, 0xff)

		// LLess

		LLess(arg1, i000)
		CH06(arg0, 64, 47)

		LLess(i000, arg1)
		CH06(arg0, 65, 47)

		// LLessEqual

		LLessEqual(arg1, i000)
		CH06(arg0, 66, 0xff)

		LLessEqual(i000, arg1)
		CH06(arg0, 67, 0xff)

		// LNotEqual

		LNotEqual(arg1, i000)
		CH06(arg0, 68, 0xff)

		LNotEqual(i000, arg1)
		CH06(arg0, 69, 0xff)

		// LOr

		LOr(arg1, i000)
		CH06(arg0, 70, 47)

		LOr(i000, arg1)
		CH06(arg0, 71, 47)

		// Mod

		Mod(arg1, i000)
		CH06(arg0, 72, 47)

		Mod(i000, arg1)
		CH06(arg0, 73, 47)

		Mod(arg1, i000, Local1)
		CH06(arg0, 74, 47)

		Mod(i000, arg1, Local1)
		CH06(arg0, 75, 47)

		// Multiply

		Multiply(arg1, i000)
		CH06(arg0, 76, 47)

		Multiply(i000, arg1)
		CH06(arg0, 77, 47)

		Multiply(arg1, i000, Local1)
		CH06(arg0, 78, 47)

		Multiply(i000, arg1, Local1)
		CH06(arg0, 79, 47)

		// NAnd

		NAnd(arg1, i000)
		CH06(arg0, 80, 47)

		NAnd(i000, arg1)
		CH06(arg0, 81, 47)

		NAnd(arg1, i000, Local1)
		CH06(arg0, 82, 47)

		NAnd(i000, arg1, Local1)
		CH06(arg0, 83, 47)

		// NOr

		NOr(arg1, i000)
		CH06(arg0, 84, 47)

		NOr(i000, arg1)
		CH06(arg0, 85, 47)

		NOr(arg1, i000, Local1)
		CH06(arg0, 86, 47)

		NOr(i000, arg1, Local1)
		CH06(arg0, 87, 47)

		// Or

		Or(arg1, i000)
		CH06(arg0, 88, 47)

		Or(i000, arg1)
		CH06(arg0, 89, 47)

		Or(arg1, i000, Local1)
		CH06(arg0, 90, 47)

		Or(i000, arg1, Local1)
		CH06(arg0, 91, 47)

		// ShiftLeft

		ShiftLeft(arg1, i000)
		CH06(arg0, 92, 47)

		ShiftLeft(i000, arg1)
		CH06(arg0, 93, 47)

		ShiftLeft(arg1, i000, Local1)
		CH06(arg0, 94, 47)

		ShiftLeft(i000, arg1, Local1)
		CH06(arg0, 95, 47)

		// ShiftRight

		ShiftRight(arg1, i000)
		CH06(arg0, 96, 47)

		ShiftRight(i000, arg1)
		CH06(arg0, 97, 47)

		ShiftRight(arg1, i000, Local1)
		CH06(arg0, 98, 47)

		ShiftRight(i000, arg1, Local1)
		CH06(arg0, 99, 47)

		// Subtract

		Subtract(arg1, i000)
		CH06(arg0, 100, 47)

		Subtract(i000, arg1)
		CH06(arg0, 101, 47)

		Subtract(arg1, i000, Local1)
		CH06(arg0, 102, 47)

		Subtract(i000, arg1, Local1)
		CH06(arg0, 103, 47)

		// ToString

		ToString(arg1, 1)
		CH06(arg0, 104, 47)

		ToString(i000, arg1)
		CH06(arg0, 105, 47)

		ToString(arg1, 1, Local1)
		CH06(arg0, 106, 47)

		ToString(i000, arg1, Local1)
		CH06(arg0, 107, 47)

		// Wait

		Wait(arg1, i000)
		CH06(arg0, 108, 47)

		Wait(e000, arg1)
		CH06(arg0, 109, 47)

		// XOr

		XOr(arg1, i000)
		CH06(arg0, 110, 47)

		XOr(i000, arg1)
		CH06(arg0, 111, 47)

		XOr(arg1, i000, Local1)
		CH06(arg0, 112, 47)

		XOr(i000, arg1, Local1)
		CH06(arg0, 113, 47)

		// Mid

		Mid(arg1, 1, 1)
		CH06(arg0, 114, 47)

		Mid("123", arg1, 1)
		CH06(arg0, 115, 47)

		Mid("123", 1, arg1)
		CH06(arg0, 116, 47)

		Mid(arg1, 1, 1, Local1)
		CH06(arg0, 117, 47)

		Mid("123", arg1, 1, Local1)
		CH06(arg0, 118, 47)

		Mid("123", 1, arg1, Local1)
		CH06(arg0, 119, 47)

		// Match

		Match(arg1, MTR, 0, MTR, 0, 0)
		CH03(ts, z096, 29, 0, 0)

		Match(Package(){1}, MTR, arg1, MTR, 0, 0)
		CH06(arg0, 121, 47)

		Match(Package(){1}, MTR, 0, MTR, arg1, 0)
		CH06(arg0, 122, 47)

		Match(Package(){1}, MTR, 0, MTR, 0, arg1)
		CH06(arg0, 123, 47)
	}

	// Local
	Method(m003, 1)
	{
		Store(Package(){0x63}, Local0)

		// CondRefOf
		
		CondRefOf(Local0)
		CH03(ts, z096, 30, 0, 0)

		CondRefOf(Local0, Local1)
		CH03(ts, z096, 31, 0, 0)

		// CopyObject

		CopyObject(Local0, Local1)
		CH03(ts, z096, 32, 0, 0)

		// Decrement

		Decrement(Local0)
		CH06(arg0, 1, 47)

		// DerefOf

		DerefOf(Local0)
		CH06(arg0, 2, 47)

		// FindSetLeftBit

		FindSetLeftBit(Local0)
		CH06(arg0, 3, 47)

		FindSetLeftBit(Local0, Local1)
		CH06(arg0, 4, 47)

		// FindSetRightBit

		FindSetRightBit(Local0)
		CH06(arg0, 5, 47)

		FindSetRightBit(Local0, Local1)
		CH06(arg0, 6, 47)

		// FromBCD

		FromBCD(Local0)
		CH06(arg0, 7, 47)

		FromBCD(Local0, Local1)
		CH06(arg0, 8, 47)

		// Increment

		Increment(Local0)
		CH06(arg0, 9, 47)

		// LNot

		LNot(Local0)
		CH06(arg0, 10, 47)

		// Not

		Not(Local0)
		CH06(arg0, 11, 47)

		Not(Local0, Local1)
		CH06(arg0, 12, 47)

		// ObjectType

		ObjectType(Local0)
		CH03(ts, z096, 33, 0, 0)

		// RefOf

		RefOf(Local0)
		CH03(ts, z096, 34, 0, 0)

		// Release

		Release(Local0)
		CH06(arg0, 13, 47)

		// Reset

		Reset(Local0)
		CH06(arg0, 14, 47)

		// Signal

		Signal(Local0)
		CH06(arg0, 15, 47)

		// SizeOf

		SizeOf(Local0)
		CH03(ts, z096, 35, 0, 0)

		// Sleep

		Sleep(Local0)
		CH06(arg0, 17, 47)

		// Stall

		Stall(Local0)
		CH06(arg0, 18, 47)

		// Store

		Store(Local0, Local1)
		CH03(ts, z096, 36, 0, 0)

		// ToBCD

		ToBCD(Local0)
		CH06(arg0, 20, 47)

		ToBCD(Local0, Local1)
		CH06(arg0, 21, 47)

		// ToBuffer

		ToBuffer(Local0)
		CH06(arg0, 22, 47)

		ToBuffer(Local0, Local1)
		CH06(arg0, 23, 47)

		// ToDecimalString

		ToDecimalString(Local0)
		CH06(arg0, 24, 47)

		ToDecimalString(Local0, Local1)
		CH06(arg0, 25, 47)

		// ToHexString

		ToHexString(Local0)
		CH06(arg0, 26, 47)

		ToHexString(Local0, Local1)
		CH06(arg0, 27, 47)

		// ToInteger

		ToInteger(Local0)
		CH06(arg0, 28, 47)

		ToInteger(Local0, Local1)
		CH06(arg0, 29, 47)

		// Acquire

		Acquire(Local0, 100)
		CH06(arg0, 30, 47)

		// Add

		Add(Local0, i000)
		CH06(arg0, 31, 47)

		Add(i000, Local0)
		CH06(arg0, 32, 47)

		Add(Local0, i000, Local1)
		CH06(arg0, 33, 47)

		Add(i000, Local0, Local1)
		CH06(arg0, 34, 47)

		// And

		And(Local0, i000)
		CH06(arg0, 35, 47)

		And(i000, Local0)
		CH06(arg0, 36, 47)

		And(Local0, i000, Local1)
		CH06(arg0, 37, 47)

		And(i000, Local0, Local1)
		CH06(arg0, 38, 47)

		// Concatenate

		Concatenate(Local0, i000)
		CH06(arg0, 39, 47)

		Concatenate(i000, Local0)
		CH06(arg0, 40, 47)

		Concatenate(Local0, i000, Local1)
		CH06(arg0, 41, 47)

		Concatenate(i000, Local0, Local1)
		CH06(arg0, 42, 47)

		// ConcatenateResTemplate

		ConcatenateResTemplate(Local0, ResourceTemplate(){})
		CH06(arg0, 43, 47)

		ConcatenateResTemplate(ResourceTemplate(){}, Local0)
		CH06(arg0, 44, 47)

		ConcatenateResTemplate(Local0, ResourceTemplate(){}, Local1)
		CH06(arg0, 45, 47)

		ConcatenateResTemplate(ResourceTemplate(){}, Local0, Local1)
		CH06(arg0, 46, 47)

		// Divide

		Divide(Local0, i000)
		CH06(arg0, 47, 47)

		Divide(i000, Local0)
		CH06(arg0, 48, 47)

		Divide(Local0, i000, Local2)
		CH06(arg0, 49, 47)

		Divide(i000, Local0, Local2)
		CH06(arg0, 50, 47)

		Divide(Local0, i000, Local2, Local1)
		CH06(arg0, 51, 47)

		Divide(i000, Local0, Local2, Local1)
		CH06(arg0, 52, 47)

		// Fatal

		Fatal(0xff, 0xffffffff, Local0)
		CH06(arg0, 53, 47)

		// Index

		Index(Local0, 0)
		CH03(ts, z096, 37, 0, 0)

		Index("0", Local0)
		CH06(arg0, 55, 47)

		Index(Local0, 0, Local1)
		CH03(ts, z096, 38, 0, 0)

		Index("0", Local0, Local1)
		CH06(arg0, 57, 47)

		// LEqual

		LEqual(Local0, i000)
		CH06(arg0, 58, 47)

		LEqual(i000, Local0)
		CH06(arg0, 59, 47)

		// LGreater

		LGreater(Local0, i000)
		CH06(arg0, 60, 47)

		LGreater(i000, Local0)
		CH06(arg0, 61, 47)

		// LGreaterEqual

		LGreaterEqual(Local0, i000)
		CH06(arg0, 62, 0xff)

		LGreaterEqual(i000, Local0)
		CH06(arg0, 63, 0xff)

		// LLess

		LLess(Local0, i000)
		CH06(arg0, 64, 47)

		LLess(i000, Local0)
		CH06(arg0, 65, 47)

		// LLessEqual

		LLessEqual(Local0, i000)
		CH06(arg0, 66, 0xff)

		LLessEqual(i000, Local0)
		CH06(arg0, 67, 0xff)

		// LNotEqual

		LNotEqual(Local0, i000)
		CH06(arg0, 68, 0xff)

		LNotEqual(i000, Local0)
		CH06(arg0, 69, 0xff)

		// LOr

		LOr(Local0, i000)
		CH06(arg0, 70, 47)

		LOr(i000, Local0)
		CH06(arg0, 71, 47)

		// Mod

		Mod(Local0, i000)
		CH06(arg0, 72, 47)

		Mod(i000, Local0)
		CH06(arg0, 73, 47)

		Mod(Local0, i000, Local1)
		CH06(arg0, 74, 47)

		Mod(i000, Local0, Local1)
		CH06(arg0, 75, 47)

		// Multiply

		Multiply(Local0, i000)
		CH06(arg0, 76, 47)

		Multiply(i000, Local0)
		CH06(arg0, 77, 47)

		Multiply(Local0, i000, Local1)
		CH06(arg0, 78, 47)

		Multiply(i000, Local0, Local1)
		CH06(arg0, 79, 47)

		// NAnd

		NAnd(Local0, i000)
		CH06(arg0, 80, 47)

		NAnd(i000, Local0)
		CH06(arg0, 81, 47)

		NAnd(Local0, i000, Local1)
		CH06(arg0, 82, 47)

		NAnd(i000, Local0, Local1)
		CH06(arg0, 83, 47)

		// NOr

		NOr(Local0, i000)
		CH06(arg0, 84, 47)

		NOr(i000, Local0)
		CH06(arg0, 85, 47)

		NOr(Local0, i000, Local1)
		CH06(arg0, 86, 47)

		NOr(i000, Local0, Local1)
		CH06(arg0, 87, 47)

		// Or

		Or(Local0, i000)
		CH06(arg0, 88, 47)

		Or(i000, Local0)
		CH06(arg0, 89, 47)

		Or(Local0, i000, Local1)
		CH06(arg0, 90, 47)

		Or(i000, Local0, Local1)
		CH06(arg0, 91, 47)

		// ShiftLeft

		ShiftLeft(Local0, i000)
		CH06(arg0, 92, 47)

		ShiftLeft(i000, Local0)
		CH06(arg0, 93, 47)

		ShiftLeft(Local0, i000, Local1)
		CH06(arg0, 94, 47)

		ShiftLeft(i000, Local0, Local1)
		CH06(arg0, 95, 47)

		// ShiftRight

		ShiftRight(Local0, i000)
		CH06(arg0, 96, 47)

		ShiftRight(i000, Local0)
		CH06(arg0, 97, 47)

		ShiftRight(Local0, i000, Local1)
		CH06(arg0, 98, 47)

		ShiftRight(i000, Local0, Local1)
		CH06(arg0, 99, 47)

		// Subtract

		Subtract(Local0, i000)
		CH06(arg0, 100, 47)

		Subtract(i000, Local0)
		CH06(arg0, 101, 47)

		Subtract(Local0, i000, Local1)
		CH06(arg0, 102, 47)

		Subtract(i000, Local0, Local1)
		CH06(arg0, 103, 47)

		// ToString

		ToString(Local0, 1)
		CH06(arg0, 104, 47)

		ToString(i000, Local0)
		CH06(arg0, 105, 47)

		ToString(Local0, 1, Local1)
		CH06(arg0, 106, 47)

		ToString(i000, Local0, Local1)
		CH06(arg0, 107, 47)

		// Wait

		Wait(Local0, i000)
		CH06(arg0, 108, 47)

		Wait(e000, Local0)
		CH06(arg0, 109, 47)

		// XOr

		XOr(Local0, i000)
		CH06(arg0, 110, 47)

		XOr(i000, Local0)
		CH06(arg0, 111, 47)

		XOr(Local0, i000, Local1)
		CH06(arg0, 112, 47)

		XOr(i000, Local0, Local1)
		CH06(arg0, 113, 47)

		// Mid

		Mid(Local0, 1, 1)
		CH06(arg0, 114, 47)

		Mid("123", Local0, 1)
		CH06(arg0, 115, 47)

		Mid("123", 1, Local0)
		CH06(arg0, 116, 47)

		Mid(Local0, 1, 1, Local1)
		CH06(arg0, 117, 47)

		Mid("123", Local0, 1, Local1)
		CH06(arg0, 118, 47)

		Mid("123", 1, Local0, Local1)
		CH06(arg0, 119, 47)

		// Match

		Match(Local0, MTR, 0, MTR, 0, 0)
		CH03(ts, z096, 39, 0, 0)

		Match(Package(){1}, MTR, Local0, MTR, 0, 0)
		CH06(arg0, 121, 47)

		Match(Package(){1}, MTR, 0, MTR, Local0, 0)
		CH06(arg0, 122, 47)

		Match(Package(){1}, MTR, 0, MTR, 0, Local0)
		CH06(arg0, 123, 47)
	}

	// An element of Package
	Method(m004, 1)
	{
		Name(p000, Package(){Package(){0x63}})

		// DeRefOf(Index(Package, Ind))

		// CondRefOf
		
		CondRefOf(DeRefOf(Index(p000, 0)))
		CH06(arg0, 0, 47)

		CondRefOf(DeRefOf(Index(p000, 0)), Local1)
		CH06(arg0, 1, 47)

		// CopyObject

		CopyObject(DeRefOf(Index(p000, 0)), Local1)
		CH03(ts, z096, 40, 0, 0)

		// Decrement

		Decrement(DeRefOf(Index(p000, 0)))
		CH06(arg0, 2, 47)

		// DerefOf

		DerefOf(DeRefOf(Index(p000, 0)))
		CH06(arg0, 3, 47)

		// FindSetLeftBit

		FindSetLeftBit(DeRefOf(Index(p000, 0)))
		CH06(arg0, 4, 47)

		FindSetLeftBit(DeRefOf(Index(p000, 0)), Local1)
		CH06(arg0, 5, 47)

		// FindSetRightBit

		FindSetRightBit(DeRefOf(Index(p000, 0)))
		CH06(arg0, 6, 47)

		FindSetRightBit(DeRefOf(Index(p000, 0)), Local1)
		CH06(arg0, 7, 47)

		// FromBCD

		FromBCD(DeRefOf(Index(p000, 0)))
		CH06(arg0, 8, 47)

		FromBCD(DeRefOf(Index(p000, 0)), Local1)
		CH06(arg0, 9, 47)

		// Increment

		Increment(DeRefOf(Index(p000, 0)))
		CH06(arg0, 10, 47)

		// LNot

		LNot(DeRefOf(Index(p000, 0)))
		CH06(arg0, 11, 47)

		// Not

		Not(DeRefOf(Index(p000, 0)))
		CH06(arg0, 12, 47)

		Not(DeRefOf(Index(p000, 0)), Local1)
		CH06(arg0, 13, 47)

		// ObjectType

		ObjectType(DeRefOf(Index(p000, 0)))
		CH03(ts, z096, 41, 0, 0)

		// RefOf

		RefOf(DeRefOf(Index(p000, 0)))
		CH06(arg0, 14, 47)

		// Release

		// Reset

		// Signal

		// SizeOf

		SizeOf(DeRefOf(Index(p000, 0)))
		CH03(ts, z096, 42, 0, 0)

		// Sleep

		Sleep(DeRefOf(Index(p000, 0)))
		CH06(arg0, 17, 47)

		// Stall

		Stall(DeRefOf(Index(p000, 0)))
		CH06(arg0, 18, 47)

		// Store

		Store(DeRefOf(Index(p000, 0)), Local1)
		CH03(ts, z096, 43, 0, 0)

		// ToBCD

		ToBCD(DeRefOf(Index(p000, 0)))
		CH06(arg0, 20, 47)

		ToBCD(DeRefOf(Index(p000, 0)), Local1)
		CH06(arg0, 21, 47)

		// ToBuffer

		ToBuffer(DeRefOf(Index(p000, 0)))
		CH06(arg0, 22, 47)

		ToBuffer(DeRefOf(Index(p000, 0)), Local1)
		CH06(arg0, 23, 47)

		// ToDecimalString

		ToDecimalString(DeRefOf(Index(p000, 0)))
		CH06(arg0, 24, 47)

		ToDecimalString(DeRefOf(Index(p000, 0)), Local1)
		CH06(arg0, 25, 47)

		// ToHexString

		ToHexString(DeRefOf(Index(p000, 0)))
		CH06(arg0, 26, 47)

		ToHexString(DeRefOf(Index(p000, 0)), Local1)
		CH06(arg0, 27, 47)

		// ToInteger

		ToInteger(DeRefOf(Index(p000, 0)))
		CH06(arg0, 28, 47)

		ToInteger(DeRefOf(Index(p000, 0)), Local1)
		CH06(arg0, 29, 47)

		// Acquire

		// Add

		Add(DeRefOf(Index(p000, 0)), i000)
		CH06(arg0, 31, 47)

		Add(i000, DeRefOf(Index(p000, 0)))
		CH06(arg0, 32, 47)

		Add(DeRefOf(Index(p000, 0)), i000, Local1)
		CH06(arg0, 33, 47)

		Add(i000, DeRefOf(Index(p000, 0)), Local1)
		CH06(arg0, 34, 47)

		// And

		And(DeRefOf(Index(p000, 0)), i000)
		CH06(arg0, 35, 47)

		And(i000, DeRefOf(Index(p000, 0)))
		CH06(arg0, 36, 47)

		And(DeRefOf(Index(p000, 0)), i000, Local1)
		CH06(arg0, 37, 47)

		And(i000, DeRefOf(Index(p000, 0)), Local1)
		CH06(arg0, 38, 47)

		// Concatenate

		Concatenate(DeRefOf(Index(p000, 0)), i000)
		CH06(arg0, 39, 47)

		Concatenate(i000, DeRefOf(Index(p000, 0)))
		CH06(arg0, 40, 47)

		Concatenate(DeRefOf(Index(p000, 0)), i000, Local1)
		CH06(arg0, 41, 47)

		Concatenate(i000, DeRefOf(Index(p000, 0)), Local1)
		CH06(arg0, 42, 47)

		// ConcatenateResTemplate

		ConcatenateResTemplate(DeRefOf(Index(p000, 0)), ResourceTemplate(){})
		CH06(arg0, 43, 47)

		ConcatenateResTemplate(ResourceTemplate(){}, DeRefOf(Index(p000, 0)))
		CH06(arg0, 44, 47)

		ConcatenateResTemplate(DeRefOf(Index(p000, 0)), ResourceTemplate(){}, Local1)
		CH06(arg0, 45, 47)

		ConcatenateResTemplate(ResourceTemplate(){}, DeRefOf(Index(p000, 0)), Local1)
		CH06(arg0, 46, 47)

		// Divide

		Divide(DeRefOf(Index(p000, 0)), i000)
		CH06(arg0, 47, 47)

		Divide(i000, DeRefOf(Index(p000, 0)))
		CH06(arg0, 48, 47)

		Divide(DeRefOf(Index(p000, 0)), i000, Local2)
		CH06(arg0, 49, 47)

		Divide(i000, DeRefOf(Index(p000, 0)), Local2)
		CH06(arg0, 50, 47)

		Divide(DeRefOf(Index(p000, 0)), i000, Local2, Local1)
		CH06(arg0, 51, 47)

		Divide(i000, DeRefOf(Index(p000, 0)), Local2, Local1)
		CH06(arg0, 52, 47)

		// Fatal

		Fatal(0xff, 0xffffffff, DeRefOf(Index(p000, 0)))
		CH06(arg0, 53, 47)

		// Index

		Index(DeRefOf(Index(p000, 0)), 0)
		CH03(ts, z096, 44, 0, 0)

		Index("0", DeRefOf(Index(p000, 0)))
		CH06(arg0, 55, 47)

		Index(DeRefOf(Index(p000, 0)), 0, Local1)
		CH03(ts, z096, 45, 0, 0)

		Index("0", DeRefOf(Index(p000, 0)), Local1)
		CH06(arg0, 57, 47)

		// LEqual

		LEqual(DeRefOf(Index(p000, 0)), i000)
		CH06(arg0, 58, 47)

		LEqual(i000, DeRefOf(Index(p000, 0)))
		CH06(arg0, 59, 47)

		// LGreater

		LGreater(DeRefOf(Index(p000, 0)), i000)
		CH06(arg0, 60, 47)

		LGreater(i000, DeRefOf(Index(p000, 0)))
		CH06(arg0, 61, 47)

		// LGreaterEqual

		LGreaterEqual(DeRefOf(Index(p000, 0)), i000)
		CH06(arg0, 62, 0xff)

		LGreaterEqual(i000, DeRefOf(Index(p000, 0)))
		CH06(arg0, 63, 0xff)

		// LLess

		LLess(DeRefOf(Index(p000, 0)), i000)
		CH06(arg0, 64, 47)

		LLess(i000, DeRefOf(Index(p000, 0)))
		CH06(arg0, 65, 47)

		// LLessEqual

		LLessEqual(DeRefOf(Index(p000, 0)), i000)
		CH06(arg0, 66, 0xff)

		LLessEqual(i000, DeRefOf(Index(p000, 0)))
		CH06(arg0, 67, 0xff)

		// LNotEqual

		LNotEqual(DeRefOf(Index(p000, 0)), i000)
		CH06(arg0, 68, 0xff)

		LNotEqual(i000, DeRefOf(Index(p000, 0)))
		CH06(arg0, 69, 0xff)

		// LOr

		LOr(DeRefOf(Index(p000, 0)), i000)
		CH06(arg0, 70, 47)

		LOr(i000, DeRefOf(Index(p000, 0)))
		CH06(arg0, 71, 47)

		// Mod

		Mod(DeRefOf(Index(p000, 0)), i000)
		CH06(arg0, 72, 47)

		Mod(i000, DeRefOf(Index(p000, 0)))
		CH06(arg0, 73, 47)

		Mod(DeRefOf(Index(p000, 0)), i000, Local1)
		CH06(arg0, 74, 47)

		Mod(i000, DeRefOf(Index(p000, 0)), Local1)
		CH06(arg0, 75, 47)

		// Multiply

		Multiply(DeRefOf(Index(p000, 0)), i000)
		CH06(arg0, 76, 47)

		Multiply(i000, DeRefOf(Index(p000, 0)))
		CH06(arg0, 77, 47)

		Multiply(DeRefOf(Index(p000, 0)), i000, Local1)
		CH06(arg0, 78, 47)

		Multiply(i000, DeRefOf(Index(p000, 0)), Local1)
		CH06(arg0, 79, 47)

		// NAnd

		NAnd(DeRefOf(Index(p000, 0)), i000)
		CH06(arg0, 80, 47)

		NAnd(i000, DeRefOf(Index(p000, 0)))
		CH06(arg0, 81, 47)

		NAnd(DeRefOf(Index(p000, 0)), i000, Local1)
		CH06(arg0, 82, 47)

		NAnd(i000, DeRefOf(Index(p000, 0)), Local1)
		CH06(arg0, 83, 47)

		// NOr

		NOr(DeRefOf(Index(p000, 0)), i000)
		CH06(arg0, 84, 47)

		NOr(i000, DeRefOf(Index(p000, 0)))
		CH06(arg0, 85, 47)

		NOr(DeRefOf(Index(p000, 0)), i000, Local1)
		CH06(arg0, 86, 47)

		NOr(i000, DeRefOf(Index(p000, 0)), Local1)
		CH06(arg0, 87, 47)

		// Or

		Or(DeRefOf(Index(p000, 0)), i000)
		CH06(arg0, 88, 47)

		Or(i000, DeRefOf(Index(p000, 0)))
		CH06(arg0, 89, 47)

		Or(DeRefOf(Index(p000, 0)), i000, Local1)
		CH06(arg0, 90, 47)

		Or(i000, DeRefOf(Index(p000, 0)), Local1)
		CH06(arg0, 91, 47)

		// ShiftLeft

		ShiftLeft(DeRefOf(Index(p000, 0)), i000)
		CH06(arg0, 92, 47)

		ShiftLeft(i000, DeRefOf(Index(p000, 0)))
		CH06(arg0, 93, 47)

		ShiftLeft(DeRefOf(Index(p000, 0)), i000, Local1)
		CH06(arg0, 94, 47)

		ShiftLeft(i000, DeRefOf(Index(p000, 0)), Local1)
		CH06(arg0, 95, 47)

		// ShiftRight

		ShiftRight(DeRefOf(Index(p000, 0)), i000)
		CH06(arg0, 96, 47)

		ShiftRight(i000, DeRefOf(Index(p000, 0)))
		CH06(arg0, 97, 47)

		ShiftRight(DeRefOf(Index(p000, 0)), i000, Local1)
		CH06(arg0, 98, 47)

		ShiftRight(i000, DeRefOf(Index(p000, 0)), Local1)
		CH06(arg0, 99, 47)

		// Subtract

		Subtract(DeRefOf(Index(p000, 0)), i000)
		CH06(arg0, 100, 47)

		Subtract(i000, DeRefOf(Index(p000, 0)))
		CH06(arg0, 101, 47)

		Subtract(DeRefOf(Index(p000, 0)), i000, Local1)
		CH06(arg0, 102, 47)

		Subtract(i000, DeRefOf(Index(p000, 0)), Local1)
		CH06(arg0, 103, 47)

		// ToString

		ToString(DeRefOf(Index(p000, 0)), 1)
		CH06(arg0, 104, 47)

		ToString(i000, DeRefOf(Index(p000, 0)))
		CH06(arg0, 105, 47)

		ToString(DeRefOf(Index(p000, 0)), 1, Local1)
		CH06(arg0, 106, 47)

		ToString(i000, DeRefOf(Index(p000, 0)), Local1)
		CH06(arg0, 107, 47)

		// Wait

		Wait(e000, DeRefOf(Index(p000, 0)))
		CH06(arg0, 109, 47)

		// XOr

		XOr(DeRefOf(Index(p000, 0)), i000)
		CH06(arg0, 110, 47)

		XOr(i000, DeRefOf(Index(p000, 0)))
		CH06(arg0, 111, 47)

		XOr(DeRefOf(Index(p000, 0)), i000, Local1)
		CH06(arg0, 112, 47)

		XOr(i000, DeRefOf(Index(p000, 0)), Local1)
		CH06(arg0, 113, 47)

		// Mid

		Mid(DeRefOf(Index(p000, 0)), 1, 1)
		CH06(arg0, 114, 47)

		Mid("123", DeRefOf(Index(p000, 0)), 1)
		CH06(arg0, 115, 47)

		Mid("123", 1, DeRefOf(Index(p000, 0)))
		CH06(arg0, 116, 47)

		Mid(DeRefOf(Index(p000, 0)), 1, 1, Local1)
		CH06(arg0, 117, 47)

		Mid("123", DeRefOf(Index(p000, 0)), 1, Local1)
		CH06(arg0, 118, 47)

		Mid("123", 1, DeRefOf(Index(p000, 0)), Local1)
		CH06(arg0, 119, 47)

		// Match

		Match(DeRefOf(Index(p000, 0)), MTR, 0, MTR, 0, 0)
		CH03(ts, z096, 46, 0, 0)

		Match(Package(){1}, MTR, DeRefOf(Index(p000, 0)), MTR, 0, 0)
		CH06(arg0, 121, 47)

		Match(Package(){1}, MTR, 0, MTR, DeRefOf(Index(p000, 0)), 0)
		CH06(arg0, 122, 47)

		Match(Package(){1}, MTR, 0, MTR, 0, DeRefOf(Index(p000, 0)))
		CH06(arg0, 123, 47)


		// DeRefOf(Index(Package, Ind, Dest))

		// CondRefOf
		
		CondRefOf(DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 203, 47)

		CondRefOf(DeRefOf(Index(p000, 0, Local0)), Local1)
		CH06(arg0, 204, 47)

		// CopyObject

		CopyObject(DeRefOf(Index(p000, 0, Local0)), Local1)
		CH03(ts, z096, 47, 0, 0)

		// Decrement

		Decrement(DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 1, 47)

		// DerefOf

		DerefOf(DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 2, 47)

		// FindSetLeftBit

		FindSetLeftBit(DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 3, 47)

		FindSetLeftBit(DeRefOf(Index(p000, 0, Local0)), Local1)
		CH06(arg0, 4, 47)

		// FindSetRightBit

		FindSetRightBit(DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 5, 47)

		FindSetRightBit(DeRefOf(Index(p000, 0, Local0)), Local1)
		CH06(arg0, 6, 47)

		// FromBCD

		FromBCD(DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 7, 47)

		FromBCD(DeRefOf(Index(p000, 0, Local0)), Local1)
		CH06(arg0, 8, 47)

		// Increment

		Increment(DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 9, 47)

		// LNot

		LNot(DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 10, 47)

		// Not

		Not(DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 11, 47)

		Not(DeRefOf(Index(p000, 0, Local0)), Local1)
		CH06(arg0, 12, 47)

		// ObjectType

		ObjectType(DeRefOf(Index(p000, 0, Local0)))
		CH03(ts, z096, 48, 0, 0)

		// RefOf

		RefOf(DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 205, 47)

		// Release

		// Reset

		// Signal

		// SizeOf

		SizeOf(DeRefOf(Index(p000, 0, Local0)))
		CH03(ts, z096, 49, 0, 0)

		// Sleep

		Sleep(DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 17, 47)

		// Stall

		Stall(DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 18, 47)

		// Store

		Store(DeRefOf(Index(p000, 0, Local0)), Local1)
		CH03(ts, z096, 50, 0, 0)

		// ToBCD

		ToBCD(DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 20, 47)

		ToBCD(DeRefOf(Index(p000, 0, Local0)), Local1)
		CH06(arg0, 21, 47)

		// ToBuffer

		ToBuffer(DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 22, 47)

		ToBuffer(DeRefOf(Index(p000, 0, Local0)), Local1)
		CH06(arg0, 23, 47)

		// ToDecimalString

		ToDecimalString(DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 24, 47)

		ToDecimalString(DeRefOf(Index(p000, 0, Local0)), Local1)
		CH06(arg0, 25, 47)

		// ToHexString

		ToHexString(DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 26, 47)

		ToHexString(DeRefOf(Index(p000, 0, Local0)), Local1)
		CH06(arg0, 27, 47)

		// ToInteger

		ToInteger(DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 28, 47)

		ToInteger(DeRefOf(Index(p000, 0, Local0)), Local1)
		CH06(arg0, 29, 47)

		// Acquire

		// Add

		Add(DeRefOf(Index(p000, 0, Local0)), i000)
		CH06(arg0, 31, 47)

		Add(i000, DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 32, 47)

		Add(DeRefOf(Index(p000, 0, Local0)), i000, Local1)
		CH06(arg0, 33, 47)

		Add(i000, DeRefOf(Index(p000, 0, Local0)), Local1)
		CH06(arg0, 34, 47)

		// And

		And(DeRefOf(Index(p000, 0, Local0)), i000)
		CH06(arg0, 35, 47)

		And(i000, DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 36, 47)

		And(DeRefOf(Index(p000, 0, Local0)), i000, Local1)
		CH06(arg0, 37, 47)

		And(i000, DeRefOf(Index(p000, 0, Local0)), Local1)
		CH06(arg0, 38, 47)

		// Concatenate

		Concatenate(DeRefOf(Index(p000, 0, Local0)), i000)
		CH06(arg0, 39, 47)

		Concatenate(i000, DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 40, 47)

		Concatenate(DeRefOf(Index(p000, 0, Local0)), i000, Local1)
		CH06(arg0, 41, 47)

		Concatenate(i000, DeRefOf(Index(p000, 0, Local0)), Local1)
		CH06(arg0, 42, 47)

		// ConcatenateResTemplate

		ConcatenateResTemplate(DeRefOf(Index(p000, 0, Local0)), ResourceTemplate(){})
		CH06(arg0, 43, 47)

		ConcatenateResTemplate(ResourceTemplate(){}, DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 44, 47)

		ConcatenateResTemplate(DeRefOf(Index(p000, 0, Local0)), ResourceTemplate(){}, Local1)
		CH06(arg0, 45, 47)

		ConcatenateResTemplate(ResourceTemplate(){}, DeRefOf(Index(p000, 0, Local0)), Local1)
		CH06(arg0, 46, 47)

		// Divide

		Divide(DeRefOf(Index(p000, 0, Local0)), i000)
		CH06(arg0, 47, 47)

		Divide(i000, DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 48, 47)

		Divide(DeRefOf(Index(p000, 0, Local0)), i000, Local2)
		CH06(arg0, 49, 47)

		Divide(i000, DeRefOf(Index(p000, 0, Local0)), Local2)
		CH06(arg0, 50, 47)

		Divide(DeRefOf(Index(p000, 0, Local0)), i000, Local2, Local1)
		CH06(arg0, 51, 47)

		Divide(i000, DeRefOf(Index(p000, 0, Local0)), Local2, Local1)
		CH06(arg0, 52, 47)

		// Fatal

		Fatal(0xff, 0xffffffff, DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 53, 47)

		// Index

		Index(DeRefOf(Index(p000, 0, Local0)), 0)
		CH03(ts, z096, 51, 0, 0)

		Index("0", DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 55, 47)

		Index(DeRefOf(Index(p000, 0, Local0)), 0, Local1)
		CH03(ts, z096, 52, 0, 0)

		Index("0", DeRefOf(Index(p000, 0, Local0)), Local1)
		CH06(arg0, 57, 47)

		// LEqual

		LEqual(DeRefOf(Index(p000, 0, Local0)), i000)
		CH06(arg0, 58, 47)

		LEqual(i000, DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 59, 47)

		// LGreater

		LGreater(DeRefOf(Index(p000, 0, Local0)), i000)
		CH06(arg0, 60, 47)

		LGreater(i000, DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 61, 47)

		// LGreaterEqual

		LGreaterEqual(DeRefOf(Index(p000, 0, Local0)), i000)
		CH06(arg0, 62, 0xff)

		LGreaterEqual(i000, DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 63, 0xff)

		// LLess

		LLess(DeRefOf(Index(p000, 0, Local0)), i000)
		CH06(arg0, 64, 47)

		LLess(i000, DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 65, 47)

		// LLessEqual

		LLessEqual(DeRefOf(Index(p000, 0, Local0)), i000)
		CH06(arg0, 66, 0xff)

		LLessEqual(i000, DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 67, 0xff)

		// LNotEqual

		LNotEqual(DeRefOf(Index(p000, 0, Local0)), i000)
		CH06(arg0, 68, 0xff)

		LNotEqual(i000, DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 69, 0xff)

		// LOr

		LOr(DeRefOf(Index(p000, 0, Local0)), i000)
		CH06(arg0, 70, 47)

		LOr(i000, DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 71, 47)

		// Mod

		Mod(DeRefOf(Index(p000, 0, Local0)), i000)
		CH06(arg0, 72, 47)

		Mod(i000, DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 73, 47)

		Mod(DeRefOf(Index(p000, 0, Local0)), i000, Local1)
		CH06(arg0, 74, 47)

		Mod(i000, DeRefOf(Index(p000, 0, Local0)), Local1)
		CH06(arg0, 75, 47)

		// Multiply

		Multiply(DeRefOf(Index(p000, 0, Local0)), i000)
		CH06(arg0, 76, 47)

		Multiply(i000, DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 77, 47)

		Multiply(DeRefOf(Index(p000, 0, Local0)), i000, Local1)
		CH06(arg0, 78, 47)

		Multiply(i000, DeRefOf(Index(p000, 0, Local0)), Local1)
		CH06(arg0, 79, 47)

		// NAnd

		NAnd(DeRefOf(Index(p000, 0, Local0)), i000)
		CH06(arg0, 80, 47)

		NAnd(i000, DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 81, 47)

		NAnd(DeRefOf(Index(p000, 0, Local0)), i000, Local1)
		CH06(arg0, 82, 47)

		NAnd(i000, DeRefOf(Index(p000, 0, Local0)), Local1)
		CH06(arg0, 83, 47)

		// NOr

		NOr(DeRefOf(Index(p000, 0, Local0)), i000)
		CH06(arg0, 84, 47)

		NOr(i000, DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 85, 47)

		NOr(DeRefOf(Index(p000, 0, Local0)), i000, Local1)
		CH06(arg0, 86, 47)

		NOr(i000, DeRefOf(Index(p000, 0, Local0)), Local1)
		CH06(arg0, 87, 47)

		// Or

		Or(DeRefOf(Index(p000, 0, Local0)), i000)
		CH06(arg0, 88, 47)

		Or(i000, DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 89, 47)

		Or(DeRefOf(Index(p000, 0, Local0)), i000, Local1)
		CH06(arg0, 90, 47)

		Or(i000, DeRefOf(Index(p000, 0, Local0)), Local1)
		CH06(arg0, 91, 47)

		// ShiftLeft

		ShiftLeft(DeRefOf(Index(p000, 0, Local0)), i000)
		CH06(arg0, 92, 47)

		ShiftLeft(i000, DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 93, 47)

		ShiftLeft(DeRefOf(Index(p000, 0, Local0)), i000, Local1)
		CH06(arg0, 94, 47)

		ShiftLeft(i000, DeRefOf(Index(p000, 0, Local0)), Local1)
		CH06(arg0, 95, 47)

		// ShiftRight

		ShiftRight(DeRefOf(Index(p000, 0, Local0)), i000)
		CH06(arg0, 96, 47)

		ShiftRight(i000, DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 97, 47)

		ShiftRight(DeRefOf(Index(p000, 0, Local0)), i000, Local1)
		CH06(arg0, 98, 47)

		ShiftRight(i000, DeRefOf(Index(p000, 0, Local0)), Local1)
		CH06(arg0, 99, 47)

		// Subtract

		Subtract(DeRefOf(Index(p000, 0, Local0)), i000)
		CH06(arg0, 100, 47)

		Subtract(i000, DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 101, 47)

		Subtract(DeRefOf(Index(p000, 0, Local0)), i000, Local1)
		CH06(arg0, 102, 47)

		Subtract(i000, DeRefOf(Index(p000, 0, Local0)), Local1)
		CH06(arg0, 103, 47)

		// ToString

		ToString(DeRefOf(Index(p000, 0, Local0)), 1)
		CH06(arg0, 104, 47)

		ToString(i000, DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 105, 47)

		ToString(DeRefOf(Index(p000, 0, Local0)), 1, Local1)
		CH06(arg0, 106, 47)

		ToString(i000, DeRefOf(Index(p000, 0, Local0)), Local1)
		CH06(arg0, 107, 47)

		// Wait

		Wait(e000, DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 109, 47)

		// XOr

		XOr(DeRefOf(Index(p000, 0, Local0)), i000)
		CH06(arg0, 110, 47)

		XOr(i000, DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 111, 47)

		XOr(DeRefOf(Index(p000, 0, Local0)), i000, Local1)
		CH06(arg0, 112, 47)

		XOr(i000, DeRefOf(Index(p000, 0, Local0)), Local1)
		CH06(arg0, 113, 47)

		// Mid

		Mid(DeRefOf(Index(p000, 0, Local0)), 1, 1)
		CH06(arg0, 114, 47)

		Mid("123", DeRefOf(Index(p000, 0, Local0)), 1)
		CH06(arg0, 115, 47)

		Mid("123", 1, DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 116, 47)

		Mid(DeRefOf(Index(p000, 0, Local0)), 1, 1, Local1)
		CH06(arg0, 117, 47)

		Mid("123", DeRefOf(Index(p000, 0, Local0)), 1, Local1)
		CH06(arg0, 118, 47)

		Mid("123", 1, DeRefOf(Index(p000, 0, Local0)), Local1)
		CH06(arg0, 119, 47)

		// Match

		Match(DeRefOf(Index(p000, 0, Local0)), MTR, 0, MTR, 0, 0)
		CH03(ts, z096, 53, 0, 0)

		Match(Package(){1}, MTR, DeRefOf(Index(p000, 0, Local0)), MTR, 0, 0)
		CH06(arg0, 121, 47)

		Match(Package(){1}, MTR, 0, MTR, DeRefOf(Index(p000, 0, Local0)), 0)
		CH06(arg0, 122, 47)

		Match(Package(){1}, MTR, 0, MTR, 0, DeRefOf(Index(p000, 0, Local0)))
		CH06(arg0, 123, 47)
	}

	// Reference to Object
	Method(m005, 2)
	{
		Store(arg0, Debug)
		Store(arg1, Debug)

		Store(ObjectType(arg1), Local0)
		if (LNotEqual(Local0, 4)) {
			err(arg0, z096, 0, 0, 0, Local0, 4)
			return (1)
		}

		DerefOf(arg1)
		CH03(ts, z096, 54, 0, 0)

		// CondRefOf
		
		CondRefOf(DerefOf(arg1))
		CH06(arg0, 1, 47)

		CondRefOf(DerefOf(arg1), Local1)
		CH06(arg0, 2, 47)

		// CopyObject

		CopyObject(DerefOf(arg1), Local1)
		CH03(ts, z096, 55, 0, 0)

		// Decrement

		Decrement(DerefOf(arg1))
		CH06(arg0, 3, 47)

		// DerefOf

		DerefOf(DerefOf(arg1))
		CH06(arg0, 4, 47)

		// FindSetLeftBit

		FindSetLeftBit(DerefOf(arg1))
		CH06(arg0, 5, 47)

		FindSetLeftBit(DerefOf(arg1), Local1)
		CH06(arg0, 6, 47)

		// FindSetRightBit

		FindSetRightBit(DerefOf(arg1))
		CH06(arg0, 7, 47)

		FindSetRightBit(DerefOf(arg1), Local1)
		CH06(arg0, 8, 47)

		// FromBCD

		FromBCD(DerefOf(arg1))
		CH06(arg0, 9, 47)

		FromBCD(DerefOf(arg1), Local1)
		CH06(arg0, 10, 47)

		// Increment

		Increment(DerefOf(arg1))
		CH06(arg0, 11, 47)

		// LNot

		LNot(DerefOf(arg1))
		CH06(arg0, 12, 47)

		// Not

		Not(DerefOf(arg1))
		CH06(arg0, 13, 47)

		Not(DerefOf(arg1), Local1)
		CH06(arg0, 14, 47)

		// ObjectType

		ObjectType(DerefOf(arg1))
		CH03(ts, z096, 56, 0, 0)

		// RefOf

		RefOf(DerefOf(arg1))
		CH06(arg0, 15, 47)

		// Release

		// Reset

		// Signal

		// SizeOf

		SizeOf(DerefOf(arg1))
		CH03(ts, z096, 57, 0, 0)

		// Sleep

		Sleep(DerefOf(arg1))
		CH06(arg0, 17, 47)

		// Stall

		Stall(DerefOf(arg1))
		CH06(arg0, 18, 47)

		// Store

		Store(DerefOf(arg1), Local1)
		CH03(ts, z096, 58, 0, 0)

		// ToBCD

		ToBCD(DerefOf(arg1))
		CH06(arg0, 20, 47)

		ToBCD(DerefOf(arg1), Local1)
		CH06(arg0, 21, 47)

		// ToBuffer

		ToBuffer(DerefOf(arg1))
		CH06(arg0, 22, 47)

		ToBuffer(DerefOf(arg1), Local1)
		CH06(arg0, 23, 47)

		// ToDecimalString

		ToDecimalString(DerefOf(arg1))
		CH06(arg0, 24, 47)

		ToDecimalString(DerefOf(arg1), Local1)
		CH06(arg0, 25, 47)

		// ToHexString

		ToHexString(DerefOf(arg1))
		CH06(arg0, 26, 47)

		ToHexString(DerefOf(arg1), Local1)
		CH06(arg0, 27, 47)

		// ToInteger

		ToInteger(DerefOf(arg1))
		CH06(arg0, 28, 47)

		ToInteger(DerefOf(arg1), Local1)
		CH06(arg0, 29, 47)

		// Acquire

		// Add

		Add(DerefOf(arg1), i000)
		CH06(arg0, 31, 47)

		Add(i000, DerefOf(arg1))
		CH06(arg0, 32, 47)

		Add(DerefOf(arg1), i000, Local1)
		CH06(arg0, 33, 47)

		Add(i000, DerefOf(arg1), Local1)
		CH06(arg0, 34, 47)

		// And

		And(DerefOf(arg1), i000)
		CH06(arg0, 35, 47)

		And(i000, DerefOf(arg1))
		CH06(arg0, 36, 47)

		And(DerefOf(arg1), i000, Local1)
		CH06(arg0, 37, 47)

		And(i000, DerefOf(arg1), Local1)
		CH06(arg0, 38, 47)

		// Concatenate

		Concatenate(DerefOf(arg1), i000)
		CH06(arg0, 39, 47)

		Concatenate(i000, DerefOf(arg1))
		CH06(arg0, 40, 47)

		Concatenate(DerefOf(arg1), i000, Local1)
		CH06(arg0, 41, 47)

		Concatenate(i000, DerefOf(arg1), Local1)
		CH06(arg0, 42, 47)

		// ConcatenateResTemplate

		ConcatenateResTemplate(DerefOf(arg1), ResourceTemplate(){})
		CH06(arg0, 43, 47)

		ConcatenateResTemplate(ResourceTemplate(){}, DerefOf(arg1))
		CH06(arg0, 44, 47)

		ConcatenateResTemplate(DerefOf(arg1), ResourceTemplate(){}, Local1)
		CH06(arg0, 45, 47)

		ConcatenateResTemplate(ResourceTemplate(){}, DerefOf(arg1), Local1)
		CH06(arg0, 46, 47)

		// Divide

		Divide(DerefOf(arg1), i000)
		CH06(arg0, 47, 47)

		Divide(i000, DerefOf(arg1))
		CH06(arg0, 48, 47)

		Divide(DerefOf(arg1), i000, Local2)
		CH06(arg0, 49, 47)

		Divide(i000, DerefOf(arg1), Local2)
		CH06(arg0, 50, 47)

		Divide(DerefOf(arg1), i000, Local2, Local1)
		CH06(arg0, 51, 47)

		Divide(i000, DerefOf(arg1), Local2, Local1)
		CH06(arg0, 52, 47)

		// Fatal

		Fatal(0xff, 0xffffffff, DerefOf(arg1))
		CH06(arg0, 53, 47)

		// Index

		Index(DerefOf(arg1), 0)
		CH03(ts, z096, 59, 0, 0)

		Index("0", DerefOf(arg1))
		CH06(arg0, 55, 47)

		Index(DerefOf(arg1), 0, Local1)
		CH03(ts, z096, 60, 0, 0)

		Index("0", DerefOf(arg1), Local1)
		CH06(arg0, 57, 47)

		// LEqual

		LEqual(DerefOf(arg1), i000)
		CH06(arg0, 58, 47)

		LEqual(i000, DerefOf(arg1))
		CH06(arg0, 59, 47)

		// LGreater

		LGreater(DerefOf(arg1), i000)
		CH06(arg0, 60, 47)

		LGreater(i000, DerefOf(arg1))
		CH06(arg0, 61, 47)

		// LGreaterEqual

		LGreaterEqual(DerefOf(arg1), i000)
		CH06(arg0, 62, 0xff)

		LGreaterEqual(i000, DerefOf(arg1))
		CH06(arg0, 63, 0xff)

		// LLess

		LLess(DerefOf(arg1), i000)
		CH06(arg0, 64, 47)

		LLess(i000, DerefOf(arg1))
		CH06(arg0, 65, 47)

		// LLessEqual

		LLessEqual(DerefOf(arg1), i000)
		CH06(arg0, 66, 0xff)

		LLessEqual(i000, DerefOf(arg1))
		CH06(arg0, 67, 0xff)

		// LNotEqual

		LNotEqual(DerefOf(arg1), i000)
		CH06(arg0, 68, 0xff)

		LNotEqual(i000, DerefOf(arg1))
		CH06(arg0, 69, 0xff)

		// LOr

		LOr(DerefOf(arg1), i000)
		CH06(arg0, 70, 47)

		LOr(i000, DerefOf(arg1))
		CH06(arg0, 71, 47)

		// Mod

		Mod(DerefOf(arg1), i000)
		CH06(arg0, 72, 47)

		Mod(i000, DerefOf(arg1))
		CH06(arg0, 73, 47)

		Mod(DerefOf(arg1), i000, Local1)
		CH06(arg0, 74, 47)

		Mod(i000, DerefOf(arg1), Local1)
		CH06(arg0, 75, 47)

		// Multiply

		Multiply(DerefOf(arg1), i000)
		CH06(arg0, 76, 47)

		Multiply(i000, DerefOf(arg1))
		CH06(arg0, 77, 47)

		Multiply(DerefOf(arg1), i000, Local1)
		CH06(arg0, 78, 47)

		Multiply(i000, DerefOf(arg1), Local1)
		CH06(arg0, 79, 47)

		// NAnd

		NAnd(DerefOf(arg1), i000)
		CH06(arg0, 80, 47)

		NAnd(i000, DerefOf(arg1))
		CH06(arg0, 81, 47)

		NAnd(DerefOf(arg1), i000, Local1)
		CH06(arg0, 82, 47)

		NAnd(i000, DerefOf(arg1), Local1)
		CH06(arg0, 83, 47)

		// NOr

		NOr(DerefOf(arg1), i000)
		CH06(arg0, 84, 47)

		NOr(i000, DerefOf(arg1))
		CH06(arg0, 85, 47)

		NOr(DerefOf(arg1), i000, Local1)
		CH06(arg0, 86, 47)

		NOr(i000, DerefOf(arg1), Local1)
		CH06(arg0, 87, 47)

		// Or

		Or(DerefOf(arg1), i000)
		CH06(arg0, 88, 47)

		Or(i000, DerefOf(arg1))
		CH06(arg0, 89, 47)

		Or(DerefOf(arg1), i000, Local1)
		CH06(arg0, 90, 47)

		Or(i000, DerefOf(arg1), Local1)
		CH06(arg0, 91, 47)

		// ShiftLeft

		ShiftLeft(DerefOf(arg1), i000)
		CH06(arg0, 92, 47)

		ShiftLeft(i000, DerefOf(arg1))
		CH06(arg0, 93, 47)

		ShiftLeft(DerefOf(arg1), i000, Local1)
		CH06(arg0, 94, 47)

		ShiftLeft(i000, DerefOf(arg1), Local1)
		CH06(arg0, 95, 47)

		// ShiftRight

		ShiftRight(DerefOf(arg1), i000)
		CH06(arg0, 96, 47)

		ShiftRight(i000, DerefOf(arg1))
		CH06(arg0, 97, 47)

		ShiftRight(DerefOf(arg1), i000, Local1)
		CH06(arg0, 98, 47)

		ShiftRight(i000, DerefOf(arg1), Local1)
		CH06(arg0, 99, 47)

		// Subtract

		Subtract(DerefOf(arg1), i000)
		CH06(arg0, 100, 47)

		Subtract(i000, DerefOf(arg1))
		CH06(arg0, 101, 47)

		Subtract(DerefOf(arg1), i000, Local1)
		CH06(arg0, 102, 47)

		Subtract(i000, DerefOf(arg1), Local1)
		CH06(arg0, 103, 47)

		// ToString

		ToString(DerefOf(arg1), 1)
		CH06(arg0, 104, 47)

		ToString(i000, DerefOf(arg1))
		CH06(arg0, 105, 47)

		ToString(DerefOf(arg1), 1, Local1)
		CH06(arg0, 106, 47)

		ToString(i000, DerefOf(arg1), Local1)
		CH06(arg0, 107, 47)

		// Wait

		Wait(e000, DerefOf(arg1))
		CH06(arg0, 109, 47)

		// XOr

		XOr(DerefOf(arg1), i000)
		CH06(arg0, 110, 47)

		XOr(i000, DerefOf(arg1))
		CH06(arg0, 111, 47)

		XOr(DerefOf(arg1), i000, Local1)
		CH06(arg0, 112, 47)

		XOr(i000, DerefOf(arg1), Local1)
		CH06(arg0, 113, 47)

		// Mid

		Mid(DerefOf(arg1), 1, 1)
		CH06(arg0, 114, 47)

		Mid("123", DerefOf(arg1), 1)
		CH06(arg0, 115, 47)

		Mid("123", 1, DerefOf(arg1))
		CH06(arg0, 116, 47)

		Mid(DerefOf(arg1), 1, 1, Local1)
		CH06(arg0, 117, 47)

		Mid("123", DerefOf(arg1), 1, Local1)
		CH06(arg0, 118, 47)

		Mid("123", 1, DerefOf(arg1), Local1)
		CH06(arg0, 119, 47)

		// Match

		Match(DerefOf(arg1), MTR, 0, MTR, 0, 0)
		CH03(ts, z096, 61, 0, 0)

		Match(Package(){1}, MTR, DerefOf(arg1), MTR, 0, 0)
		CH06(arg0, 121, 47)

		Match(Package(){1}, MTR, 0, MTR, DerefOf(arg1), 0)
		CH06(arg0, 122, 47)

		Match(Package(){1}, MTR, 0, MTR, 0, DerefOf(arg1))
		CH06(arg0, 123, 47)

		return (0)
	}

	// Result of Method invocation
	Method(m006, 1)
	{
		Method(m000)
		{
			// intermediate storing to force ASL compiler
			// not report "Invalid type (Method returns)"
			Store(Package(){0x63}, Local0)
			Return (Local0)
		}

		Name(ss00, "0")

		// CondRefOf

		if (y601) {
			CondRefOf(m000())
			CH06(arg0, 0, 47)

			CondRefOf(m000(), Local1)
			CH06(arg0, 1, 47)
		}

		// CopyObject

		CopyObject(m000(), Local1)
		CH03(ts, z096, 62, 0, 0)

		// Decrement

		Decrement(m000())
		CH06(arg0, 2, 47)

		// DerefOf

		DerefOf(m000())
		CH06(arg0, 3, 47)

		// FindSetLeftBit

		FindSetLeftBit(m000())
		CH06(arg0, 4, 47)

		FindSetLeftBit(m000(), Local1)
		CH06(arg0, 5, 47)

		// FindSetRightBit

		FindSetRightBit(m000())
		CH06(arg0, 6, 47)

		FindSetRightBit(m000(), Local1)
		CH06(arg0, 7, 47)

		// FromBCD

		FromBCD(m000())
		CH06(arg0, 8, 47)

		FromBCD(m000(), Local1)
		CH06(arg0, 9, 47)

		// Increment

		Increment(m000())
		CH06(arg0, 10, 47)

		// LNot

		LNot(m000())
		CH06(arg0, 11, 47)

		// Not

		Not(m000())
		CH06(arg0, 12, 47)

		Not(m000(), Local1)
		CH06(arg0, 13, 47)

		// ObjectType
        /* Nov. 2012: Method invocation as arg to ObjectType is now illegal */
//
//		ObjectType(m000())
//		CH03(ts, z096, 63, 0, 0)

		// RefOf

		if (y601) {
			RefOf(m000())
			CH06(arg0, 14, 47)
		}

		// Release

		Release(m000())
		CH06(arg0, 13, 47)

		// Reset

		Reset(m000())
		CH06(arg0, 14, 47)

		// Signal

		Signal(m000())
		CH06(arg0, 15, 47)

		// SizeOf

		SizeOf(m000())
		CH06(arg0, 16, 47)

		// Sleep

		Sleep(m000())
		CH06(arg0, 17, 47)

		// Stall

		Stall(m000())
		CH06(arg0, 18, 47)

		// Store

		// ToBCD

		ToBCD(m000())
		CH06(arg0, 20, 47)

		ToBCD(m000(), Local1)
		CH06(arg0, 21, 47)

		// ToBuffer

		ToBuffer(m000())
		CH06(arg0, 22, 47)

		ToBuffer(m000(), Local1)
		CH06(arg0, 23, 47)

		// ToDecimalString

		ToDecimalString(m000())
		CH06(arg0, 24, 47)

		ToDecimalString(m000(), Local1)
		CH06(arg0, 25, 47)

		// ToHexString

		ToHexString(m000())
		CH06(arg0, 26, 47)

		ToHexString(m000(), Local1)
		CH06(arg0, 27, 47)

		// ToInteger

		ToInteger(m000())
		CH06(arg0, 28, 47)

		ToInteger(m000(), Local1)
		CH06(arg0, 29, 47)

		// Acquire

		Acquire(m000(), 100)
		CH06(arg0, 30, 47)

		// Add

		Add(m000(), i000)
		CH06(arg0, 31, 47)

		Add(i000, m000())
		CH06(arg0, 32, 47)

		Add(m000(), i000, Local1)
		CH06(arg0, 33, 47)

		Add(i000, m000(), Local1)
		CH06(arg0, 34, 47)

		// And

		And(m000(), i000)
		CH06(arg0, 35, 47)

		And(i000, m000())
		CH06(arg0, 36, 47)

		And(m000(), i000, Local1)
		CH06(arg0, 37, 47)

		And(i000, m000(), Local1)
		CH06(arg0, 38, 47)

		// Concatenate

		Concatenate(m000(), i000)
		CH06(arg0, 39, 47)

		Concatenate(i000, m000())
		CH06(arg0, 40, 47)

		Concatenate(m000(), i000, Local1)
		CH06(arg0, 41, 47)

		Concatenate(i000, m000(), Local1)
		CH06(arg0, 42, 47)

		// ConcatenateResTemplate

		ConcatenateResTemplate(m000(), ResourceTemplate(){})
		CH06(arg0, 43, 47)

		ConcatenateResTemplate(ResourceTemplate(){}, m000())
		CH06(arg0, 44, 47)

		ConcatenateResTemplate(m000(), ResourceTemplate(){}, Local1)
		CH06(arg0, 45, 47)

		ConcatenateResTemplate(ResourceTemplate(){}, m000(), Local1)
		CH06(arg0, 46, 47)

		// Divide

		Divide(m000(), i000)
		CH06(arg0, 47, 47)

		Divide(i000, m000())
		CH06(arg0, 48, 47)

		Divide(m000(), i000, Local2)
		CH06(arg0, 49, 47)

		Divide(i000, m000(), Local2)
		CH06(arg0, 50, 47)

		Divide(m000(), i000, Local2, Local1)
		CH06(arg0, 51, 47)

		Divide(i000, m000(), Local2, Local1)
		CH06(arg0, 52, 47)

		// Fatal

		Fatal(0xff, 0xffffffff, m000())
		CH06(arg0, 53, 47)

		// Index

		if (y900) {
			Index(m000(), 0)
			CH03(ts, z096, 64, 0, 0)

			Index("0", m000())
			CH06(arg0, 55, 47)

			Index(m000(), 0, Local1)
			CH03(ts, z096, 65, 0, 0)

			Index("0", m000(), Local1)
			CH06(arg0, 57, 47)
		} else {
			CH03(ts, z096, 0x123, 0, 0)
			Index(m000(), 0)
			CH04(ts, 0, 85, z094, 0x124, 0, 0) // AE_INDEX_TO_NOT_ATTACHED

			CH03(ts, z096, 0x125, 0, 0)
			Index("0", m000())
			CH04(ts, 0, 0xff, z094, 0x126, 0, 0) // AE_INDEX_TO_NOT_ATTACHED

			CH03(ts, z096, 0x127, 0, 0)
			Index(m000(), 0, Local1)
			CH04(ts, 0, 85, z094, 0x128, 0, 0) // AE_INDEX_TO_NOT_ATTACHED

			CH03(ts, z096, 0x129, 0, 0)
			Index("0", m000(), Local1)
			CH04(ts, 0, 0xff, z094, 0x12a, 0, 0) // AE_INDEX_TO_NOT_ATTACHED


			CH03(ts, z096, 0x125, 0, 0)
			Index(ss00, m000())
			CH04(ts, 0, 47, z094, 0x126, 0, 0) // AE_INDEX_TO_NOT_ATTACHED

			CH03(ts, z096, 0x129, 0, 0)
			Index(ss00, m000(), Local1)
			CH04(ts, 0, 47, z094, 0x12a, 0, 0) // AE_INDEX_TO_NOT_ATTACHED
		}

		// LEqual

		LEqual(m000(), i000)
		CH06(arg0, 58, 47)

		LEqual(i000, m000())
		CH06(arg0, 59, 47)

		// LGreater

		LGreater(m000(), i000)
		CH06(arg0, 60, 47)

		LGreater(i000, m000())
		CH06(arg0, 61, 47)

		// LGreaterEqual

		LGreaterEqual(m000(), i000)
		CH06(arg0, 62, 0xff)

		LGreaterEqual(i000, m000())
		CH06(arg0, 63, 0xff)

		// LLess

		LLess(m000(), i000)
		CH06(arg0, 64, 47)

		LLess(i000, m000())
		CH06(arg0, 65, 47)

		// LLessEqual

		LLessEqual(m000(), i000)
		CH06(arg0, 66, 0xff)

		LLessEqual(i000, m000())
		CH06(arg0, 67, 0xff)

		// LNotEqual

		LNotEqual(m000(), i000)
		CH06(arg0, 68, 0xff)

		LNotEqual(i000, m000())
		CH06(arg0, 69, 0xff)

		// LOr

		LOr(m000(), i000)
		CH06(arg0, 70, 47)

		LOr(i000, m000())
		CH06(arg0, 71, 47)

		// Mod

		Mod(m000(), i000)
		CH06(arg0, 72, 47)

		Mod(i000, m000())
		CH06(arg0, 73, 47)

		Mod(m000(), i000, Local1)
		CH06(arg0, 74, 47)

		Mod(i000, m000(), Local1)
		CH06(arg0, 75, 47)

		// Multiply

		Multiply(m000(), i000)
		CH06(arg0, 76, 47)

		Multiply(i000, m000())
		CH06(arg0, 77, 47)

		Multiply(m000(), i000, Local1)
		CH06(arg0, 78, 47)

		Multiply(i000, m000(), Local1)
		CH06(arg0, 79, 47)

		// NAnd

		NAnd(m000(), i000)
		CH06(arg0, 80, 47)

		NAnd(i000, m000())
		CH06(arg0, 81, 47)

		NAnd(m000(), i000, Local1)
		CH06(arg0, 82, 47)

		NAnd(i000, m000(), Local1)
		CH06(arg0, 83, 47)

		// NOr

		NOr(m000(), i000)
		CH06(arg0, 84, 47)

		NOr(i000, m000())
		CH06(arg0, 85, 47)

		NOr(m000(), i000, Local1)
		CH06(arg0, 86, 47)

		NOr(i000, m000(), Local1)
		CH06(arg0, 87, 47)

		// Or

		Or(m000(), i000)
		CH06(arg0, 88, 47)

		Or(i000, m000())
		CH06(arg0, 89, 47)

		Or(m000(), i000, Local1)
		CH06(arg0, 90, 47)

		Or(i000, m000(), Local1)
		CH06(arg0, 91, 47)

		// ShiftLeft

		ShiftLeft(m000(), i000)
		CH06(arg0, 92, 47)

		ShiftLeft(i000, m000())
		CH06(arg0, 93, 47)

		ShiftLeft(m000(), i000, Local1)
		CH06(arg0, 94, 47)

		ShiftLeft(i000, m000(), Local1)
		CH06(arg0, 95, 47)

		// ShiftRight

		ShiftRight(m000(), i000)
		CH06(arg0, 96, 47)

		ShiftRight(i000, m000())
		CH06(arg0, 97, 47)

		ShiftRight(m000(), i000, Local1)
		CH06(arg0, 98, 47)

		ShiftRight(i000, m000(), Local1)
		CH06(arg0, 99, 47)

		// Subtract

		Subtract(m000(), i000)
		CH06(arg0, 100, 47)

		Subtract(i000, m000())
		CH06(arg0, 101, 47)

		Subtract(m000(), i000, Local1)
		CH06(arg0, 102, 47)

		Subtract(i000, m000(), Local1)
		CH06(arg0, 103, 47)

		// ToString

		ToString(m000(), 1)
		CH06(arg0, 104, 47)

		ToString(i000, m000())
		CH06(arg0, 105, 47)

		ToString(m000(), 1, Local1)
		CH06(arg0, 106, 47)

		ToString(i000, m000(), Local1)
		CH06(arg0, 107, 47)

		// Wait

		Wait(m000(), i000)
		CH06(arg0, 108, 47)

		Wait(e000, m000())
		CH06(arg0, 109, 47)

		// XOr

		XOr(m000(), i000)
		CH06(arg0, 110, 47)

		XOr(i000, m000())
		CH06(arg0, 111, 47)

		XOr(m000(), i000, Local1)
		CH06(arg0, 112, 47)

		XOr(i000, m000(), Local1)
		CH06(arg0, 113, 47)

		// Mid

		Mid(m000(), 1, 1)
		CH06(arg0, 114, 47)

		Mid("123", m000(), 1)
		CH06(arg0, 115, 47)

		Mid("123", 1, m000())
		CH06(arg0, 116, 47)

		Mid(m000(), 1, 1, Local1)
		CH06(arg0, 117, 47)

		Mid("123", m000(), 1, Local1)
		CH06(arg0, 118, 47)

		Mid("123", 1, m000(), Local1)
		CH06(arg0, 119, 47)

		// Match

		Match(m000(), MTR, 0, MTR, 0, 0)
		CH03(ts, z096, 66, 0, 0)

		Match(Package(){1}, MTR, m000(), MTR, 0, 0)
		CH06(arg0, 121, 47)

		Match(Package(){1}, MTR, 0, MTR, m000(), 0)
		CH06(arg0, 122, 47)

		Match(Package(){1}, MTR, 0, MTR, 0, m000())
		CH06(arg0, 123, 47)
	}

	// Reference to Object as Result of Method invocation
	Method(m007, 1)
	{
		Name(p000, Package(){0x63})

		Name(i000, 0) // Label to check m000 invocations

		Method(m000, 2)
		{
			Store(arg0, i000)
			if (LEqual(arg1, 0)) {
				Store(Refof(p100), Local0)
			} elseif (LEqual(arg1, 1)) {
				Store(Refof(p000), Local0)
			}
			Return (Local0)
		}

		Method(CH00, 2)
		{
			if (LNotEqual(i000, arg1)) {
				err(arg0, z096, 0, 0, 0, i000, arg1)
			}
		}

		Name(lpN0, 2)
		Name(lpC0, 0)

		While (lpN0) {
			Multiply(3, lpC0, Local0)

			Store(0, i000)

			DerefOf(m000(1, lpC0))
			CH03(ts, z096, Add(67, lpC0), 0, 0)
			CH00(arg0, 1)

			DerefOf(DerefOf(m000(2, lpC0)))
			CH06(arg0, Add(1, Local0), 47)
			CH00(arg0, 2)

			Index(DerefOf(m000(3, lpC0)), 0)
			CH06(arg0, Add(2, Local0), 47)
			CH00(arg0, 3)

			Match(DerefOf(m000(4, lpC0)), MTR, 0, MTR, 0, 0)
			CH06(arg0, Add(3, Local0), 47)
			CH00(arg0, 4)

			Decrement(lpN0)
			Increment(lpC0)
		}
	}

	// Result of Method with checking of invocation
	Method(m008, 1)
	{
		Name(i000, 0) // Label to check m000 invocations

		Method(m000, 1)
		{
			Store(arg0, i000)
			Store(Package(){0x63}, Local0)
			Return (Local0)
		}

		Method(CH00, 2)
		{
			if (LNotEqual(i000, arg1)) {
				err(arg0, z096, 0, 0, 0, i000, arg1)
			}
		}

		// CondRefOf
		
		if (y601) {
			CondRefOf(m000(1))
			CH06(arg0, 1, 47)
			CH00(arg0, 1)
		}

		CondRefOf(m000(2), Local1)
		CH06(arg0, 2, 47)
		if (y600) {
			CH00(arg0, 2)
		}

		// DerefOf

		DerefOf(m000(3))
		CH06(arg0, 3, 47)
		CH00(arg0, 3)

		// RefOf

		if (y601) {
			RefOf(m000(4))
			CH06(arg0, 4, 47)
			CH00(arg0, 4)
		}

		// Release

		Release(m000(5))
		CH06(arg0, 5, 47)
		if (y600) {
			CH00(arg0, 5)
		}

		// Reset

		Reset(m000(6))
		CH06(arg0, 6, 47)
		if (y600) {
			CH00(arg0, 6)
		}

		// Signal

		Signal(m000(7))
		CH06(arg0, 7, 47)
		if (y600) {
			CH00(arg0, 7)
		}

		// Acquire

		Acquire(m000(8), 0)
		CH06(arg0, 8, 47)
		if (y600) {
			CH00(arg0, 8)
		}

		// Index

		CH03(ts, z094, 0x123, 0, 0)
		Index(m000(9), 0)
		if (y900) {
			CH03(ts, z096, 69, 0, 0)
			CH00(arg0, 9)
		} else {
			CH04(ts, 0, 85, z094, 0x124, 0, 0) // AE_INDEX_TO_NOT_ATTACHED
		}

		// Wait

		Wait(m000(10), 0)
		CH06(arg0, 9, 47)
		if (y600) {
			CH00(arg0, 10)
		}

		// Match

		Match(m000(11), MTR, 0, MTR, 0, 0)
		CH03(ts, z096, 70, 0, 0)
		CH00(arg0, 11)
	}

	SET0(z096, ts, 0)

	CH03(ts, z096, 70, 0, 0)

	// Local Named Object
	m000(ts)

	// Global Named Object
	m001(ts)

	// Argument
	m002(ts, Package(){0x62})

	// Local
	m003(Concatenate(ts, "-m003"))

	// An element of Package
	m004(Concatenate(ts, "-m004"))


	// Reference to Local Named Object

	m005(Concatenate(ts, "-m005-RefLocName"), RefOf(p000))

	Store(RefOf(p000), Local0)
	m005(Concatenate(ts, "-m005-RefLocName2"), Local0)

	CondRefOf(p000, Local0)
	m005(Concatenate(ts, "-m005-CondRefLocName"), Local0)

	m005(Concatenate(ts, "-m005-RefGlobName"), RefOf(p100))

	Store(RefOf(p100), Local0)
	m005(Concatenate(ts, "-m005-RefGlobName2"), Local0)

	CondRefOf(p100, Local0)
	m005(Concatenate(ts, "-m005-CondRefGlobName"), Local0)


	// Reference to Local

	Store(Package(){0x62}, Local0)

	m005(Concatenate(ts, "-m005-RefLocal"), RefOf(Local0))

	Store(RefOf(Local0), Local1)
	m005(Concatenate(ts, "-m005-RefLocal2"), Local1)

	CondRefOf(Local0, Local1)
	m005(Concatenate(ts, "-m005-CondRefLocal"), Local1)


	// Reference to Arg

	m005(Concatenate(ts, "-m005-RefArg"), RefOf(arg0))

	Store(RefOf(arg0), Local0)
	m005(Concatenate(ts, "-m005-RefArg2"), Local0)

	CondRefOf(arg0, Local0)
	m005(Concatenate(ts, "-m005-CondRefArg"), Local0)


	// Index to Package

	Name(pp00, Package(){Package(){0x62}})

	if (y113) {
		m005(Concatenate(ts, "-m005-Index"), Index(pp00, 0))
	}

	Store(Index(pp00, 0), Local0)
	m005(Concatenate(ts, "-m005-Index2"), Local0)

	if (y113) {
		m005(Concatenate(ts, "-m005-Index3"), Index(pp00, 0, Local0))
	}

	Index(pp00, 0, Local0)
	m005(Concatenate(ts, "-m005-Index4"), Local0)

	Store(Index(pp00, 0, Local0), Local1)
	m005(Concatenate(ts, "-m005-Index5"), Local1)

	// Result of Method invocation
	m006(Concatenate(ts, "-m006"))

	// Reference to Object as Result of Method invocation
	if (y500) {
		m007(Concatenate(ts, "-m007"))
	}

	// Result of Method with checking of invocation
	m008(Concatenate(ts, "-m008"))

	RST0()
}
