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
 * Alias
 */

Name(z205, 205)


Mutex (OBJ0, 0)
Processor (OBJ1,0,0,0) {}
ThermalZone (OBJ2) {}
Device(OBJ3) {Name (_HID, 0)}
Name(OBJ4, "abc123234")
Name(OBJ5, 0x1234)
Method (OBJ6) {}
Name (OBJ7, Buffer() {1})
Event (OBJ8)
PowerResource (OBJ9, 0, 0) {}
OperationRegion (OBJA, SystemMemory, 0, 0)
CreateByteField (OBJ7, 0, OBJB)

Alias (OBJ0, xxx0)
Alias (OBJ1, xxx1)
Alias (OBJ2, xxx2)
Alias (OBJ3, xxx3)
Alias (OBJ4, xxx4)
Alias (OBJ5, xxx5)
Alias (OBJ6, xxx6)
Alias (OBJ7, xxx7)
Alias (OBJ8, xxx8)
Alias (OBJ9, xxx9)
Alias (OBJA, xxxA)
Alias (OBJB, xxxB)

Name (px00, package() {xxx0})
Name (px01, package() {xxx1})
Name (px02, package() {xxx2})
Name (px03, package() {xxx3})
Name (px04, package() {xxx4})
Name (px05, package() {xxx5})
Name (px06, package() {xxx6})
Name (px07, package() {xxx7})
Name (px08, package() {xxx8})
Name (px09, package() {xxx9})
Name (px0A, package() {xxxA})
Name (px0B, package() {xxxB})

Name (P000, Package() {OBJ0})
Name (P001, Package() {OBJ1})
Name (P002, Package() {OBJ2})
Name (P003, Package() {OBJ3})
Name (P004, Package() {OBJ4})
Name (P005, Package() {OBJ5})
Name (P006, Package() {OBJ6})
Name (P007, Package() {OBJ7})
Name (P008, Package() {OBJ8})
Name (P009, Package() {OBJ9})
Name (P00A, Package() {OBJA})
Name (P00B, Package() {OBJB})


Method(ALI1,, Serialized)
{
    ALI2(OBJ1,xxx1,p001,px01)
    ALI2(OBJ2,xxx2,p002,px02)
    ALI2(OBJ3,xxx3,p003,px03)
    ALI2(OBJ4,xxx4,p004,px04)
    ALI2(OBJ5,xxx5,p005,px05)
    ALI2(OBJ7,xxx7,p007,px07)
    ALI2(OBJ8,xxx8,p008,px08)
    ALI2(OBJ9,xxx9,p009,px09)
    ALI2(OBJA,xxxA,p00A,px0A)
    ALI2(OBJB,xxxB,p00B,px0B)
}

/*
 * ALI2 compares types of objects that are actual objects, alias-ed objects,
 * objects within packages, and alias of objects in packages.
 *
 * Arg0 - actual object
 * Arg1 - alias of object
 * Arg2 - package containing actual object
 * Arg3 - package containing object alias
 */
Method(ALI2, 4, Serialized)
{
	if (ObjectType(Arg0) != ObjectType(deRefOf(Arg2[0]))){
		err(__METHOD__, z205, __LINE__, 0, 0, ObjectType(Arg0), ObjectType(deRefOf(Arg2[0])))
	}
        ElseIf (ObjectType(Arg0) != ObjectType(Arg1)){
		err(__METHOD__, z205, __LINE__, 0, 0, ObjectType(Arg0), ObjectType(Arg1))
	}
        ElseIf (ObjectType(Arg1) != ObjectType(deRefOf(Arg2[0]))){
		err(__METHOD__, z205, __LINE__, 0, 0, ObjectType(Arg1), ObjectType(deRefOf(Arg2[0])))
	}
	ElseIf (ObjectType(deRefOf(Arg2[0])) != ObjectType(deRefOf(Arg3[0]))){
		err(__METHOD__, z205, __LINE__, 0, 0, ObjectType(deRefOf(Arg2[0])), ObjectType(deRefOf(Arg3[0])))
	}
}

