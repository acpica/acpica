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
 * External declarations
 */

Name(z204, 204)

External(E000, UnknownObj)
External(E001, IntObj)
External(E002, StrObj)
External(E003, BuffObj)
External(E004, PkgObj)
External(E005, FieldUnitObj)
External(E006, DeviceObj)
External(E007, EventObj)
External(E008, MethodObj)
External(E009, MutexObj)
External(E010, OpRegionObj)
External(E011, PowerResObj)
External(E012, ProcessorObj)
External(E013, ThermalZoneObj)
External(E014, BuffFieldObj)
External(E015, DDBHandleObj)

Name(NM01, 1)
Name(NM02, "test string")
Name(NM03, buffer(1){0})
Name(NM04, package(){})
Device(NM06){}
Event(NM07)
Method(NM08)
{
	return(500)
}
Mutex(NM09, 0)

OperationRegion (NM10, PCI_Config, Zero, 0xFF)
Field (NM10, AnyAcc, NoLock, Preserve)
{
	NM05, 8
}
PowerResource(NM11, 0, 0){}
Processor(NM12, 0, 1, 2){}
ThermalZone(NM13){}
CreateBitField(NM03,0, NM14)


/*
 * Check that arg2 and arg3 have the same type
 * arg0 - diagnostic message
 * arg1 - index of checking
 * arg2 - arg5 of err, "received value"
 * arg3 - arg6 of err, "expected value"
 */
Method(EXT0, 4)
{
	Local1 = ObjectType (arg2)
	Local2 = ObjectType (arg3)
	if (Local1 != Local2){
		err(derefof(arg0), z204, 1, z204, arg1, Local1, Local2)
	}
}


// Run-method
Method(EXT1,, Serialized)
{
	Name(ts, "EXT1")

        Local1 = ObjectType (E000)
	if (Local1 != 1){
		err(ts, z204, 0, 0, 0, Local1, 1)
	}

	EXT0(ts, 1, E001, NM01)
	EXT0(ts, 2, E002, NM02)
	EXT0(ts, 3, E003, NM03)
	EXT0(ts, 4, E004, NM04)
	EXT0(ts, 5, E005, NM05)
	EXT0(ts, 6, E006, NM06)
	EXT0(ts, 7, E007, NM07)
	EXT0(ts, 8, E008, NM08)
	EXT0(ts, 9, E009, NM09)
	EXT0(ts,10, E010, NM10)
	EXT0(ts,11, E011, NM11)
	EXT0(ts,12, E012, NM12)
	EXT0(ts,13, E013, NM13)
	EXT0(ts,14, E014, NM14)

	return (0)
}
